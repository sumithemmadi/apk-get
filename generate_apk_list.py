import requests
import os

apk_list = requests.get('https://gitlab.com/fdroid/fdroiddata/-/raw/master/stats/known_apks.txt')
data = apk_list.text
lines = data.split("\n")
tempName = ""
allApks = ""
for line in lines:
    app_info = line.split()
    if len(app_info) != 0:
        appName = app_info[0]
        print(appName)
        if tempName != appName:
            allApks += appName + "\n"
            
os.makedirs(os.environ['PWD'] + "/.config/apk-get", exist_ok=True)

with open(".config/apk-get/apklist1.txt", "w") as output:
    output.write(allApks)