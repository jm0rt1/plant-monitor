#include "SecureStorage.h"

bool SecureStorage::begin()
{
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    return err == ESP_OK;
}

bool SecureStorage::saveString(const char *key, const char *value)
{
    nvs_handle_t my_handle;
    esp_err_t err = nvs_open("storage", NVS_READWRITE, &my_handle);
    if (err != ESP_OK)
        return false;

    err = nvs_set_str(my_handle, key, value);
    if (err == ESP_OK)
    {
        nvs_commit(my_handle);
    }
    nvs_close(my_handle);
    return err == ESP_OK;
}

bool SecureStorage::getString(const char *key, char *value, size_t maxLength)
{
    nvs_handle_t my_handle;
    esp_err_t err = nvs_open("storage", NVS_READONLY, &my_handle);
    if (err != ESP_OK)
        return false;

    err = nvs_get_str(my_handle, key, value, &maxLength);
    nvs_close(my_handle);
    return err == ESP_OK;
}
