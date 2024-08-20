#ifndef SECURE_STORAGE_H
#define SECURE_STORAGE_H

#include <nvs.h>
#include <nvs_flash.h>

class SecureStorage
{
public:
    bool begin();
    bool saveString(const char *key, const char *value);
    bool getString(const char *key, char *value, size_t maxLength);
};

#endif // SECURE_STORAGE_H
