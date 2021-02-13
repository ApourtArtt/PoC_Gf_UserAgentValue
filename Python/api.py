import requests
import binascii
import hashlib
import uuid
from OpenSSL import crypto
from datetime import datetime
from requests_pkcs12 import post

class NtLauncher:
    def __init__(self, locale, gfLang, installation_id=None):
        self.locale = locale
        self.gfLang = gfLang
        self.installation_id = installation_id
        self.token = None
        self.code=None
        self.version=None

    def auth(self, username, password):
        self.username = username
        self.password = password
        
        if not self.installation_id:
            m = hashlib.md5((username + password).encode()).digest()
            self.installation_id="..."
        URL = "https://spark.gameforge.com/api/v1/auth/sessions"
        HEADERS = {
            "User-Agent" : "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/72.0.3626.121 Safari/537.36",
            "TNT-Installation-Id" : self.installation_id,
            "Origin" : "spark://www.gameforge.com",
        }

        CONTENT = {
            "email" : self.username,
            "locale" : self.locale,
            "password" : self.password,
        }

        r = requests.post(URL, headers=HEADERS, json=CONTENT)
        if r.status_code != 201:
            return False
        
        response = r.json()
        self.token = response["token"]

        return True
        
    def getAccounts(self):
        if not self.token:
            return False
        
        URL = "https://spark.gameforge.com/api/v1/user/accounts"

        HEADERS = {
            "User-Agent" : "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/72.0.3626.121 Safari/537.36",
            "TNT-Installation-Id" : self.installation_id,
            "Origin" : "spark://www.gameforge.com",
            "Authorization" : "Bearer {}".format(self.token),
            "Connection" : "Keep-Alive"
        }

        r = requests.get(URL, headers=HEADERS)
        
        if r.status_code != 200:
            return False
            
        accounts = []
        response = r.json()
        
        for key in response.keys():
            accounts.append((key, response[key]["displayName"]))

        return accounts

    def _convertToken(self, guid):
        return binascii.hexlify(guid.encode()).decode()
   
    def _getuseragent(self,account):
        URL = "http://dl.tnt.gameforge.com/tnt/final-ms3/clientversioninfo.json"
        r = requests.get(URL)
        reponse = r.json()
        gfversion=hashlib.sha1(bytes("C"+reponse["version"], 'utf-8')).hexdigest()
        self.version="C"+reponse["version"]
        encryptionkey = "edd76c5219499d00da2c5a9e2b703c03d5aaf67d1f16c7ecd3165869921148f7"
        platformGameUserId= account
        platformGameUserIdcrypted = hashlib.sha1(bytes(platformGameUserId, 'utf-8')).hexdigest()
        installationId = hashlib.sha256(bytes(self.installation_id, 'utf-8')).hexdigest()
        pre_code = (encryptionkey + gfversion + installationId + platformGameUserIdcrypted)
        pre_code = hashlib.sha256(bytes(pre_code,'utf-8')).hexdigest()
        self.code = platformGameUserId[:2] + pre_code[:8]
    
    def opengf(self,account):
        pkcs12_filename = '/home/pi/Documents/nostale/NosTale-Auth-master/nosauth/from_ram.p12'
        pkcs12_password = "WTjXEnSGpj49Ba44"
        
        self._getuseragent(account)
        now =datetime.now()
        dt_string = now.strftime("%Y-%m-%dT%H:%M:%SZ")
        client_version_info={
            "branch":"master",
            "commit_id":"27942713",
            "version": self.version
        }
        URL="https://events2.gameforge.com"
        user ="Chrome/"+self.version+" ("+self.code+") GameforgeClient/2.1.22"
        HEADERS = {
            "User-Agent" : user,
            "TNT-Installation-Id" : self.installation_id,
            "Host" : "spark.gameforge.com",
            "Authorization" : "Bearer {}".format(self.token)
        }
        CONTENT = {
            "client_installation_id":self.installation_id,
            "client_locale":"usa_eng",
            "client_session_id":"...",
            "client_version_info": client_version_info,
            "id":1,
            "localtime":dt_string,
            "start_count":1,
            "start_time":7000,
            "type":"start_time"

        }
        r = post(URL, headers=HEADERS, json=CONTENT,verify=False,pkcs12_filename=pkcs12_filename,pkcs12_password=pkcs12_password)
        
        
    def getToken(self, account, raw=False):
        if not self.token:
            return False
        self.opengf(account)
        user ="Chrome/"+self.version+" ("+self.code+") GameforgeClient/2.1.22"
        URL = "https://spark.gameforge.com/api/v1/auth/thin/codes"

        HEADERS = {
            "User-Agent" : user,
            "TNT-Installation-Id" : self.installation_id,
            "Origin" : "spark://www.gameforge.com",
            "Authorization" : "Bearer {}".format(self.token),
            "Connection" : "Keep-Alive"
        }

        CONTENT = {
            "platformGameAccountId" : account
        }
        
        r = requests.post(URL, headers=HEADERS, json=CONTENT)
        if r.status_code != 201:
            return False
        if raw:
            return r.json()["code"]
        
        return self._convertToken(r.json()["code"])
