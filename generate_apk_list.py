import requests
import os

apk_list = requests.get(
    'https://gitlab.com/fdroid/fdroiddata/-/raw/master/stats/known_apks.txt')
data = apk_list.text
lines = data.split("\n")
tempName = ""
allApks = ""
for line in lines:
    app_info = line.split()
    if len(app_info) != 0:
        appName = app_info[1]
        print(appName)
        if tempName != appName:
            os.makedirs(os.environ['PWD'] + "/apps/" + appName, exist_ok=True)
            if os.path.exists("/apps/{}/app.txt".format(appName)):
                os.remove("/apps/{}/app.txt".format(appName))
            tempName = appName
        
        with open(os.environ['PWD'] + "/apps/{}/app.txt".format(appName), "a") as output:
            output.write(app_info[0] + "\n")



