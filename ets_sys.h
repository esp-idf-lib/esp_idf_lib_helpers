/* The target selection below needs CONFIG_IDF_TARGET_* from sdkconfig.h. Pull it
 * in explicitly, so that this header works no matter what the including file
 * has included before.
 */
#include <sdkconfig.h>

#if CONFIG_IDF_TARGET_ESP32
#include <esp32/rom/ets_sys.h>
#elif CONFIG_IDF_TARGET_ESP32C2
#include <esp32c2/rom/ets_sys.h>
#elif CONFIG_IDF_TARGET_ESP32C3
#include <esp32c3/rom/ets_sys.h>
#elif CONFIG_IDF_TARGET_ESP32C5
#include <esp32c5/rom/ets_sys.h>
#elif CONFIG_IDF_TARGET_ESP32C6
#include <esp32c6/rom/ets_sys.h>
#elif CONFIG_IDF_TARGET_ESP32C61
#include <esp32c61/rom/ets_sys.h>
#elif CONFIG_IDF_TARGET_ESP32H2
#include <esp32h2/rom/ets_sys.h>
#elif CONFIG_IDF_TARGET_ESP32H4
#include <esp32h4/rom/ets_sys.h>
#elif CONFIG_IDF_TARGET_ESP32S2
#include <esp32s2/rom/ets_sys.h>
#elif CONFIG_IDF_TARGET_ESP32S3
#include <esp32s3/rom/ets_sys.h>
#elif CONFIG_IDF_TARGET_ESP32S31
#include <esp32s31/rom/ets_sys.h>
#elif CONFIG_IDF_TARGET_ESP32P4
#include <esp32p4/rom/ets_sys.h>
#elif CONFIG_IDF_TARGET_ESP8266
#include <rom/ets_sys.h>
#else
#error "ets_sys: Unknown target"
#endif

#include <esp_idf_version.h>

/* ESP-IDF 4.3 renamed the ROM delay function to esp_rom_delay_us() and moved it
 * to <esp_rom_sys.h>. The old ets_delay_us() name is still declared by every
 * <target>/rom/ets_sys.h and still resolves to the same ROM code: the linker
 * scripts alias esp_rom_delay_us to ets_delay_us, so this mapping changes
 * nothing in behaviour. It keeps the components on the documented name. The ets_
 * symbols are ROM internals that ESP-IDF reserves for itself and replaces when a
 * ROM implementation has to be fixed: on ESP32-C5 and ESP32-C61 with TEE,
 * esp_rom/patches/esp_rom_sys.c defines its own ets_delay_us and redirects the
 * ROM ops table to it. ESP8266 has no esp_rom_delay_us().
 */
#if !defined(CONFIG_IDF_TARGET_ESP8266) && defined(ESP_IDF_VERSION_VAL) \
        && ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 3, 0)
#include <esp_rom_sys.h>
#define ets_delay_us(us) esp_rom_delay_us(us)
#endif
