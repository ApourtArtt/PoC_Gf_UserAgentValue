# PoC_Gf_UserAgentValue
Gameforge please stop

Generate the UserAgent string by using that way :
```cpp
CodeCreator c("PlatformGameAccountId", "InstallationId", "ChromeVersion", "cert.p12");
bool validated = c.ValidateEndpoint("RandomUuid");
QString your_user_argent_code = c.CreateCode();
```

cert.p12 is gfclient.exe's certificate.
