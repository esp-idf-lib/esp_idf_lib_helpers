# Example for `esp_idf_lib_helpers`

## What the example does

The example shows what the component provides on the current target and does
not need any external hardware.

On startup it logs:

* the ESP-IDF (or ESP8266 RTOS SDK) version and the minimum version the
  component supports, both reported through `HELPER_ESP32_MIN_VER` or
  `HELPER_ESP8266_MIN_VER`;
* the target family, selected with `HELPER_TARGET_IS_ESP32` and
  `HELPER_TARGET_IS_ESP8266`;
* the value of `HELPER_SPI_HOST_DEFAULT`, the SPI host to use by default on
  the current chip;
* the FreeRTOS tick rate, so the next part of the output can be compared
  against it.

After that, the example runs a loop that calls `ets_delay_us(200)` from
`<ets_sys.h>` and measures the real duration with `esp_timer_get_time()`. The
component ships `<ets_sys.h>` for every supported target, so the example does
not include any target specific ROM header. The delay is a busy wait and its
duration does not depend on the tick rate printed above.

## Building and running

```sh
idf.py set-target esp32
idf.py build
idf.py -p PORT flash monitor
```

## Expected output

On ESP32 with ESP-IDF 6.1 the output looks like this:

```text
I (249) example: ESP-IDF version: 6.1.0
I (249) example: Target family: ESP32
I (259) example: Minimum supported ESP-IDF: 3.3.5
I (259) example: HELPER_SPI_HOST_DEFAULT = 0
I (269) example: FreeRTOS tick rate: 100 Hz
I (269) example: ets_delay_us(200): measured 201 us
I (1269) example: ets_delay_us(200): measured 200 us
I (2269) example: ets_delay_us(200): measured 200 us
```

`HELPER_SPI_HOST_DEFAULT` is printed as a number because its symbolic name
depends on the chip: it is `SPI1_HOST` on most targets and `SPI2_HOST` on
ESP32-S2, ESP32-S3 and ESP32-S31. The example includes
`<driver/spi_master.h>` to get the enum, the same way a component that talks
to an SPI device does.

## Configuration

No configuration is available. The tick rate is left at the default value of
the target; the example works with any `CONFIG_FREERTOS_HZ`.
