import os

# Define the directory structure with file names
project_structure = {
    "MyESP32System": {
        "src": {
            "main.cpp": None,
            "SystemController": {
                "SystemController.h": None,
                "SystemController.cpp": None,
            },
            "OTAUpdate": {
                "OTAUpdate.h": None,
                "OTAUpdate.cpp": None,
            },
            "SecureStorage": {
                "SecureStorage.h": None,
                "SecureStorage.cpp": None,
            },
            "TCPLogger": {
                "TCPLogger.h": None,
                "TCPLogger.cpp": None,
            },
            "WiFiManager": {
                "WiFiManager.h": None,
                "WiFiManager.cpp": None,
            },
            "WebService": {
                "WebService.h": None,
                "WebService.cpp": None,
            },
            "ConfigService": {
                "ConfigService.h": None,
                "ConfigService.cpp": None,
            },
            "Sensors": {
                "Sensor.h": None,
                "TemperatureSensor.h": None,
                "TemperatureSensor.cpp": None,
                "HumiditySensor.h": None,
                "HumiditySensor.cpp": None,
            },
            "HomeKitService": {
                "HomeKitService.h": None,
                "HomeKitService.cpp": None,
            },
        },
        "config": {
            "wifi_config.json": None,
        },
        "data": {
            "wifi_config.html": None,
        },
        "platformio.ini": None,
        "README.md": None,
    }
}


def create_structure(base_path, structure):
    for name, content in structure.items():
        path = os.path.join(base_path, name)
        if content is None:  # It's a file
            with open(path, 'w') as file:
                pass  # Create an empty file
        else:  # It's a directory
            os.makedirs(path, exist_ok=True)
            create_structure(path, content)


# Set the base path for the project
base_path = "./"

# Create the structure
create_structure(base_path, project_structure)

print("Project structure created successfully.")
