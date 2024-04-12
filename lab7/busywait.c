#include <stdint.h>
#include "stm32f10x.h"

void SPIOutCommand(uint8_t command, SPI_TypeDef *spi, GPIO_TypeDef *gpio, uint16_t dc_pin) {
    while ((spi->SR & SPI_SR_BSY) != 0) {} // Ch? SPI tr? n�n kh�ng b?n

    gpio->BRR = (1U << dc_pin); // X�a ch�n D/C

    spi->DR = command;

    while ((spi->SR & SPI_SR_BSY) != 0) {} // Ch? SPI tr? n�n kh�ng b?n
}

void SPIOutData(uint8_t data, SPI_TypeDef *spi, GPIO_TypeDef *gpio, uint16_t dc_pin) {
    while ((spi->SR & SPI_SR_TXE) == 0) {} // Ch? SPI tr? n�n tr?ng

    gpio->BSRR = (1U << dc_pin); // �?t ch�n D/C

    spi->DR = data;
}
