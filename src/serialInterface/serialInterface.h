#include <dht.h>
#include <DHT_U.h>

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

private:
    DHT *mDht;
};
