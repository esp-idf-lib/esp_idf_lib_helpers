/*
 * Copyright (c) 2025 esp-idf-lib contributors
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <inttypes.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <driver/spi_master.h>
#include <esp_log.h>
#include <esp_timer.h>

#include <esp_idf_lib_helpers.h>
#include <ets_sys.h>

static const char *TAG = "example";

/* ESP_IDF_VERSION and the HELPER_*_MIN_VER macros are packed with
 * ESP_IDF_VERSION_VAL(): major in the highest byte, then minor and patch */
static void log_version(const char *name, int version)
{
    ESP_LOGI(TAG, "%s: %d.%d.%d", name,
             (version >> 16) & 0xff, (version >> 8) & 0xff, version & 0xff);
}

static void log_target_info(void)
{
    log_version("ESP-IDF version", ESP_IDF_VERSION);

#if HELPER_TARGET_IS_ESP32
    ESP_LOGI(TAG, "Target family: ESP32");
    log_version("Minimum supported ESP-IDF", HELPER_ESP32_MIN_VER);
#elif HELPER_TARGET_IS_ESP8266
    ESP_LOGI(TAG, "Target family: ESP8266");
    log_version("Minimum supported ESP8266 RTOS SDK", HELPER_ESP8266_MIN_VER);
#endif

    /* HELPER_SPI_HOST_DEFAULT is a spi_host_device_t value: SPI1_HOST on the
     * original ESP32 and on the newer chips, SPI2_HOST on ESP32-S2/S3 */
    ESP_LOGI(TAG, "HELPER_SPI_HOST_DEFAULT = %d", (int)HELPER_SPI_HOST_DEFAULT);
    ESP_LOGI(TAG, "FreeRTOS tick rate: %d Hz", configTICK_RATE_HZ);
}

/* The helpers component provides <ets_sys.h> on every supported target, so
 * ets_delay_us() can be used without including target specific ROM headers.
 * The delay is a busy wait, it does not depend on the FreeRTOS tick rate. */
static void log_microsecond_delay(uint32_t delay_us)
{
    int64_t start = esp_timer_get_time();
    ets_delay_us(delay_us);
    int64_t elapsed = esp_timer_get_time() - start;

    ESP_LOGI(TAG, "ets_delay_us(%" PRIu32 "): measured %" PRId64 " us",
             delay_us, elapsed);
}

void app_main()
{
    log_target_info();

    while (1)
    {
        log_microsecond_delay(200);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
