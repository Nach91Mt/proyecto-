import requests
import json
import time

url = "https://nach.pythonanywhere.com/json"
while True:
    response =requests.get(url)

    if(response.status_code == 200):
        data =json.loads(response.text)

        color=data["color"]
        ilu=data['ilu']
        led=data['leds']
        pro=data['pro']
        print(color)
        print(ilu)
        print(led)
        print(pro)
    time.sleep(2)