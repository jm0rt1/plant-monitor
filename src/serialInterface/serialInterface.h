#include <dht.h>
#include <DHT_U.h>
float readSensorVoltage(int averages);
enum UnitsTemperatures
{
    C = 0,
    F = 1
};
class SerialInterface
{
public:
    String printTemperature(UnitsTemperatures unit);
    SerialInterface();
    void readCommand();
    void onOn();
    void onOff();
    void onGetData();
    void onAllSensors();
    void setLightPercent(float val);
    float getLightPercent();

private:
    DHT *mDht;
    float mLightPercent = 50.0;
};
