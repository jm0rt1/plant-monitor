1. Disconnect the USB cable of the Nano ESP32 from your computer.
2. **Use a jumper wire** to connect the pin marked **"B1"** on the board to the pin marked **"GND"** on the board.
3. **Connect the Nano ESP32** to your computer with a USB cable.
4. **Select** `File > New Sketch` from the Arduino IDE menus.
    - The basic sketch will open in a new Arduino IDE window.
5. **Open** the `Tools > Port` menu in Arduino IDE.
    - You should see a new port in the menu. **Select that port**.
    - This port might be labeled as being any random ESP32 board instead of **"(Arduino Nano ESP32)"** as usual. This is normal and doesn't indicate a problem.
6. **Select** `Tools > Board > Arduino ESP32 Boards > Arduino Nano ESP32` from the Arduino IDE menus.
    - Alternatively, if you installed the **"esp32"** boards platform instead of Arduino ESP32 Boards, you should select `Tools > Board > esp32 > Arduino Nano ESP32`.
7. **Select** `Tools > Programmer > Esptool` from the Arduino IDE menus.
8. **Select** `Sketch > Upload Using Programmer` from the Arduino IDE menus.
    - An upload operation will start.
9. **Wait** for the operation to finish successfully.
10. **Disconnect** the USB cable of the Nano ESP32 from your computer.
11. **Disconnect** the jumper wire from the **"B1"** and **"GND"** pins on the board.
12. **Connect** the Nano ESP32 to your computer with a USB cable.