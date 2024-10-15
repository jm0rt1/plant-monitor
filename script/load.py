import requests

url = "http://192.168.4.58/live-data"
response = requests.get(url)

if response.status_code == 200:
    data = response.json()
    print(f"Temperature: {data['temperature']}°C")
    print(f"Humidity: {data['humidity']}%")
else:
    print("Failed to retrieve data")
