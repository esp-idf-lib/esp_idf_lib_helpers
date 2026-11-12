# esp_driver_spi was split out of driver in ESP-IDF 5.3
if(EXISTS "$ENV{IDF_PATH}/components/esp_driver_spi")
    set(SPI_COMPONENT esp_driver_spi)
else()
    set(SPI_COMPONENT driver)
endif()

idf_component_register(SRCS "main.c"
                    REQUIRES esp_timer ${SPI_COMPONENT})
