/*
    ChibiOS - Copyright (C) 2006..2015 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef _BOARD_H_
#define _BOARD_H_

/*
 * Setup for STMicroelectronics NUCLEO-F030R8 board.
 */

/*
 * Board identifier.
 */
#define BOARD_ST_NUCLEO_F030R8
#define BOARD_NAME                  "STMicroelectronics NUCLEO-F070RB"

/*
 * Board oscillators-related settings.
 * NOTE: LSE not fitted.
 * NOTE: HSE not fitted.
 */
#if !defined(STM32_LSECLK)
#define STM32_LSECLK                0U
#endif

#define STM32_LSEDRV                (3U << 3U)

#if !defined(STM32_HSECLK)
#define STM32_HSECLK                0U
#endif

#define STM32_HSE_BYPASS

/*
 * MCU type as defined in the ST header.
 */
#define STM32F030
#define STM32F030x8

/*
 * IO pins assignments
 */

// PORT A
#define PPIN_LCD_RS              GPIOA,0
#define PIN_LCD_RS               0
#define PPIN_LCD_RW              GPIOA,1
#define PIN_LCD_RW               1
#define PPIN_LCD_E               GPIOA,2
#define PIN_LCD_E                2
#define PPIN_LCD_BKL_EN          GPIOA,3
#define PIN_LCD_BKL_EN           3
#define PPIN_LCD_DB4             GPIOA,4
#define PIN_LCD_DB4              4
#define PPIN_LCD_DB5             GPIOA,5
#define PIN_LCD_DB5              5
#define PPIN_LCD_DB6             GPIOA,6
#define PIN_LCD_DB6              6
#define PPIN_LCD_DB7             GPIOA,7
#define PIN_LCD_DB7              7
#define PPIN_HUMID_DATA1         GPIOA,8
#define PIN_HUMID_DATA1          8
#define PPIN_BAROM_SDA           GPIOA,9
#define PIN_BAROM_SDA            9
#define PPIN_BAROM_SCL           GPIOA,10
#define PIN_BAROM_SCL            10
#define PPIN_ADC_A1              GPIOA,11
#define PIN_ADC_A1               11
#define PPIN_ADC_A0              GPIOA,12
#define PIN_ADC_A0               12
#define PPIN_SWDIO               GPIOA,13
#define PIN_SWDIO                13
#define PPIN_SWCLK               GPIOA,14
#define PIN_SWCLK                14
#define PPIN_HUMID_DATA2         GPIOA,15
#define PIN_HUMID_DATA2          15

// PORT B
#define PPIN_ADC_DOUT            GPIOB,0
#define PIN_ADC_DOUT             0
#define PPIN_ADC_SCLK            GPIOB,1
#define PIN_ADC_SCLK             1
#define PPIN_ENC_CLICK           GPIOB,2
#define PIN_ENC_CLICK            2
#define PPIN_ENC_A               GPIOB,3
#define PIN_ENC_A                3
#define PPIN_TRST                GPIOB,4 // NC
#define PIN_TRST                 4 // NC
#define PPIN_ENC_B               GPIOB,5
#define PIN_ENC_B                5
#define PPIN_DBG_TX              GPIOB,6
#define PIN_DBG_TX               6
#define PPIN_DBG_RX              GPIOB,7
#define PIN_DBG_RX               7
#define PPIN_SCL                 GPIOB,8
#define PIN_SCL                  8
#define PPIN_SDA                 GPIOB,9
#define PIN_SDA                  9
#define PPIN_ADC_PDWN            GPIOB,10
#define PIN_ADC_PDWN             10
#define PPIN_STEAM               GPIOB,11
#define PIN_STEAM                11
#define PPIN_VACUUM              GPIOB,12
#define PIN_VACUUM               12
#define PPIN_FAN                 GPIOB,13
#define PIN_FAN                  13
#define PPIN_DEHUM               GPIOB,14
#define PIN_DEHUM                14
#define PPIN_HEATER              GPIOB,15
#define PIN_HEATER               15

// PORT C
#define PPIN_MENU                GPIOC,13
#define PIN_MENU                 13
#define PPIN_OSC32_IN            GPIOC,14
#define PIN_OSC32_IN             14
#define PPIN_OSC32_OUT           GPIOC,15
#define PIN_OSC32_OUT            15

// PORT D
// none

// PORT E
// none

// PORT F
#define PPIN_RESET              GPIOF,0
#define PIN_RESET               0
#define PPIN_MANUAL             GPIOF,1
#define PIN_MANUAL              1

// redirection required for passing port and bit num
#define setPin(PIN)             palSetPad(PIN)
#define clearPin(PIN)           palClearPad(PIN)
#define togglePin(PIN)          palTogglePad(PIN)
#define readPin(PIN)            palReadPad(PIN)
#define modePin(PIN,mode)       palSetPadMode(PIN,mode)

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 * Please refer to the STM32 Reference Manual for details.
 */
#define PIN_MODE_INPUT(n)           (0U << ((n) * 2U))
#define PIN_MODE_OUTPUT(n)          (1U << ((n) * 2U))
#define PIN_MODE_ALTERNATE(n)       (2U << ((n) * 2U))
#define PIN_MODE_ANALOG(n)          (3U << ((n) * 2U))
#define PIN_ODR_LOW(n)              (0U << (n))
#define PIN_ODR_HIGH(n)             (1U << (n))
#define PIN_OTYPE_PUSHPULL(n)       (0U << (n))
#define PIN_OTYPE_OPENDRAIN(n)      (1U << (n))
#define PIN_OSPEED_2M(n)            (0U << ((n) * 2U))
#define PIN_OSPEED_10M(n)           (1U << ((n) * 2U))
#define PIN_OSPEED_40M(n)           (3U << ((n) * 2U))
#define PIN_PUPDR_FLOATING(n)       (0U << ((n) * 2U))
#define PIN_PUPDR_PULLUP(n)         (1U << ((n) * 2U))
#define PIN_PUPDR_PULLDOWN(n)       (2U << ((n) * 2U))
#define PIN_AFIO_AF(n, v)           ((v) << (((n) % 8U) * 4U))

/*
 * GPIOA setup:
 */
#define VAL_GPIOA_MODER             (PIN_MODE_OUTPUT((PIN_LCD_RS)) |          \
                                     PIN_MODE_OUTPUT((PIN_LCD_RW)) |          \
                                     PIN_MODE_OUTPUT((PIN_LCD_E)) |           \
                                     PIN_MODE_OUTPUT((PIN_LCD_BKL_EN)) |      \
                                     PIN_MODE_INPUT((PIN_LCD_DB4)) |          \
                                     PIN_MODE_INPUT((PIN_LCD_DB5)) |          \
                                     PIN_MODE_INPUT((PIN_LCD_DB6)) |          \
                                     PIN_MODE_INPUT((PIN_LCD_DB7)) |          \
                                     PIN_MODE_INPUT((PIN_HUMID_DATA1)) |      \
                                     PIN_MODE_INPUT((PIN_BAROM_SDA)) |        \
                                     PIN_MODE_INPUT((PIN_BAROM_SCL)) |        \
                                     PIN_MODE_INPUT((PIN_ADC_A1)) |           \
                                     PIN_MODE_INPUT((PIN_ADC_A0)) |           \
                                     PIN_MODE_INPUT((PIN_SWDIO)) |            \
                                     PIN_MODE_INPUT((PIN_SWCLK)) |            \
                                     PIN_MODE_INPUT((PIN_HUMID_DATA2)))
#define VAL_GPIOA_OTYPER            (PIN_OTYPE_PUSHPULL((PIN_LCD_RS)) |       \
                                     PIN_OTYPE_PUSHPULL((PIN_LCD_RW)) |       \
                                     PIN_OTYPE_PUSHPULL((PIN_LCD_E)) |        \
                                     PIN_OTYPE_PUSHPULL((PIN_LCD_BKL_EN)) |   \
                                     PIN_OTYPE_PUSHPULL((PIN_LCD_DB4)) |      \
                                     PIN_OTYPE_PUSHPULL((PIN_LCD_DB5)) |      \
                                     PIN_OTYPE_PUSHPULL((PIN_LCD_DB6)) |      \
                                     PIN_OTYPE_PUSHPULL((PIN_LCD_DB7)) |      \
                                     PIN_OTYPE_PUSHPULL((PIN_HUMID_DATA1)) |  \
                                     PIN_OTYPE_PUSHPULL((PIN_BAROM_SDA)) |    \
                                     PIN_OTYPE_PUSHPULL((PIN_BAROM_SCL)) |    \
                                     PIN_OTYPE_PUSHPULL((PIN_ADC_A1)) |       \
                                     PIN_OTYPE_PUSHPULL((PIN_ADC_A0)) |       \
                                     PIN_OTYPE_PUSHPULL((PIN_SWDIO)) |        \
                                     PIN_OTYPE_PUSHPULL((PIN_SWCLK)) |        \
                                     PIN_OTYPE_PUSHPULL((PIN_HUMID_DATA2)))
#define VAL_GPIOA_OSPEEDR           (PIN_OSPEED_40M((PIN_LCD_RS)) |           \
                                     PIN_OSPEED_40M((PIN_LCD_RW)) |           \
                                     PIN_OSPEED_40M((PIN_LCD_E)) |            \
                                     PIN_OSPEED_40M((PIN_LCD_BKL_EN)) |       \
                                     PIN_OSPEED_40M((PIN_LCD_DB4)) |          \
                                     PIN_OSPEED_40M((PIN_LCD_DB5)) |          \
                                     PIN_OSPEED_40M((PIN_LCD_DB6)) |          \
                                     PIN_OSPEED_40M((PIN_LCD_DB7)) |          \
                                     PIN_OSPEED_40M((PIN_HUMID_DATA1)) |      \
                                     PIN_OSPEED_40M((PIN_BAROM_SDA)) |        \
                                     PIN_OSPEED_40M((PIN_BAROM_SCL)) |        \
                                     PIN_OSPEED_40M((PIN_ADC_A1)) |           \
                                     PIN_OSPEED_40M((PIN_ADC_A0)) |           \
                                     PIN_OSPEED_40M((PIN_SWDIO)) |            \
                                     PIN_OSPEED_40M((PIN_SWCLK)) |            \
                                     PIN_OSPEED_40M((PIN_HUMID_DATA2)))
#define VAL_GPIOA_PUPDR             (PIN_PUPDR_PULLUP((PIN_LCD_RS)) |         \
                                     PIN_PUPDR_PULLUP((PIN_LCD_RW)) |         \
                                     PIN_PUPDR_PULLUP((PIN_LCD_E)) |          \
                                     PIN_PUPDR_PULLUP((PIN_LCD_BKL_EN)) |     \
                                     PIN_PUPDR_PULLUP((PIN_LCD_DB4)) |        \
                                     PIN_PUPDR_PULLUP((PIN_LCD_DB5)) |        \
                                     PIN_PUPDR_PULLUP((PIN_LCD_DB6)) |        \
                                     PIN_PUPDR_PULLUP((PIN_LCD_DB7)) |        \
                                     PIN_PUPDR_PULLUP((PIN_HUMID_DATA1)) |    \
                                     PIN_PUPDR_PULLUP((PIN_BAROM_SDA)) |      \
                                     PIN_PUPDR_PULLUP((PIN_BAROM_SCL)) |      \
                                     PIN_PUPDR_PULLUP((PIN_ADC_A1)) |         \
                                     PIN_PUPDR_PULLUP((PIN_ADC_A0)) |         \
                                     PIN_PUPDR_PULLUP((PIN_SWDIO)) |          \
                                     PIN_PUPDR_PULLUP((PIN_SWCLK)) |          \
                                     PIN_PUPDR_PULLUP((PIN_HUMID_DATA2)))
#define VAL_GPIOA_ODR               (PIN_ODR_LOW((PIN_LCD_RS)) |             \
                                     PIN_ODR_LOW((PIN_LCD_RW)) |             \
                                     PIN_ODR_LOW((PIN_LCD_E)) |              \
                                     PIN_ODR_LOW((PIN_LCD_BKL_EN)) |         \
                                     PIN_ODR_HIGH((PIN_LCD_DB4)) |            \
                                     PIN_ODR_HIGH((PIN_LCD_DB5)) |            \
                                     PIN_ODR_HIGH((PIN_LCD_DB6)) |            \
                                     PIN_ODR_HIGH((PIN_LCD_DB7)) |            \
                                     PIN_ODR_HIGH((PIN_HUMID_DATA1)) |        \
                                     PIN_ODR_HIGH((PIN_BAROM_SDA)) |          \
                                     PIN_ODR_HIGH((PIN_BAROM_SCL)) |          \
                                     PIN_ODR_HIGH((PIN_ADC_A1)) |             \
                                     PIN_ODR_HIGH((PIN_ADC_A0)) |             \
                                     PIN_ODR_HIGH((PIN_SWDIO)) |              \
                                     PIN_ODR_HIGH((PIN_SWCLK)) |              \
                                     PIN_ODR_HIGH((PIN_HUMID_DATA2)))
#define VAL_GPIOA_AFRL              (PIN_AFIO_AF((PIN_LCD_RS), 0) |           \
                                     PIN_AFIO_AF((PIN_LCD_RW), 0) |           \
                                     PIN_AFIO_AF((PIN_LCD_E), 0) |            \
                                     PIN_AFIO_AF((PIN_LCD_BKL_EN), 0) |       \
                                     PIN_AFIO_AF((PIN_LCD_DB4), 0) |          \
                                     PIN_AFIO_AF((PIN_LCD_DB5), 0) |          \
                                     PIN_AFIO_AF((PIN_LCD_DB6), 0) |          \
                                     PIN_AFIO_AF((PIN_LCD_DB7), 0) |          \
                                     PIN_AFIO_AF((PIN_HUMID_DATA1), 0) |      \
                                     PIN_AFIO_AF((PIN_BAROM_SDA), 0) |        \
                                     PIN_AFIO_AF((PIN_BAROM_SCL), 0) |        \
                                     PIN_AFIO_AF((PIN_ADC_A1), 0) |           \
                                     PIN_AFIO_AF((PIN_ADC_A0), 0) |           \
                                     PIN_AFIO_AF((PIN_SWDIO), 0) |            \
                                     PIN_AFIO_AF((PIN_SWCLK), 0) |            \
                                     PIN_AFIO_AF((PIN_HUMID_DATA2), 0))
#define VAL_GPIOA_AFRH              (PIN_AFIO_AF((PIN_LCD_RS), 0) |           \
                                     PIN_AFIO_AF((PIN_LCD_RW), 0) |           \
                                     PIN_AFIO_AF((PIN_LCD_E), 0) |            \
                                     PIN_AFIO_AF((PIN_LCD_BKL_EN), 0) |       \
                                     PIN_AFIO_AF((PIN_LCD_DB4), 0) |          \
                                     PIN_AFIO_AF((PIN_LCD_DB5), 0) |          \
                                     PIN_AFIO_AF((PIN_LCD_DB6), 0) |          \
                                     PIN_AFIO_AF((PIN_LCD_DB7), 0) |          \
                                     PIN_AFIO_AF((PIN_HUMID_DATA1), 0) |      \
                                     PIN_AFIO_AF((PIN_BAROM_SDA), 0) |        \
                                     PIN_AFIO_AF((PIN_BAROM_SCL), 0) |        \
                                     PIN_AFIO_AF((PIN_ADC_A1), 0) |           \
                                     PIN_AFIO_AF((PIN_ADC_A0), 0) |           \
                                     PIN_AFIO_AF((PIN_SWDIO), 0) |            \
                                     PIN_AFIO_AF((PIN_SWCLK), 0) |            \
                                     PIN_AFIO_AF((PIN_HUMID_DATA2), 0))

/*
 * GPIOB setup:
 */

#define VAL_GPIOB_MODER             (PIN_MODE_INPUT((PIN_ADC_DOUT)) |           \
                                     PIN_MODE_INPUT((PIN_ADC_SCLK)) |           \
                                     PIN_MODE_INPUT((PIN_ENC_CLICK)) |          \
                                     PIN_MODE_INPUT((PIN_ENC_A)) |              \
                                     PIN_MODE_INPUT((PIN_TRST)) |               \
                                     PIN_MODE_INPUT((PIN_ENC_B)) |              \
                                     PIN_MODE_ALTERNATE((PIN_DBG_TX)) |         \
                                     PIN_MODE_ALTERNATE((PIN_DBG_RX)) |         \
                                     PIN_MODE_ALTERNATE((PIN_SCL)) |            \
                                     PIN_MODE_ALTERNATE((PIN_SDA)) |            \
                                     PIN_MODE_INPUT((PIN_ADC_PDWN)) |           \
                                     PIN_MODE_OUTPUT((PIN_STEAM)) |             \
                                     PIN_MODE_OUTPUT((PIN_VACUUM)) |            \
                                     PIN_MODE_OUTPUT((PIN_FAN)) |               \
                                     PIN_MODE_OUTPUT((PIN_DEHUM)) |             \
                                     PIN_MODE_OUTPUT((PIN_HEATER)))
#define VAL_GPIOB_OTYPER            (PIN_OTYPE_PUSHPULL((PIN_ADC_DOUT)) |       \
                                     PIN_OTYPE_PUSHPULL((PIN_ADC_SCLK)) |       \
                                     PIN_OTYPE_PUSHPULL((PIN_ENC_CLICK)) |      \
                                     PIN_OTYPE_PUSHPULL((PIN_ENC_A)) |          \
                                     PIN_OTYPE_PUSHPULL((PIN_TRST)) |           \
                                     PIN_OTYPE_PUSHPULL((PIN_ENC_B)) |          \
                                     PIN_OTYPE_PUSHPULL((PIN_DBG_TX)) |         \
                                     PIN_OTYPE_PUSHPULL((PIN_DBG_RX)) |         \
                                     PIN_OTYPE_PUSHPULL((PIN_SCL)) |            \
                                     PIN_OTYPE_PUSHPULL((PIN_SDA)) |            \
                                     PIN_OTYPE_PUSHPULL((PIN_ADC_PDWN)) |       \
                                     PIN_OTYPE_PUSHPULL((PIN_STEAM)) |          \
                                     PIN_OTYPE_PUSHPULL((PIN_VACUUM)) |         \
                                     PIN_OTYPE_PUSHPULL((PIN_FAN)) |            \
                                     PIN_OTYPE_PUSHPULL((PIN_DEHUM)) |          \
                                     PIN_OTYPE_PUSHPULL((PIN_HEATER)))
#define VAL_GPIOB_OSPEEDR           (PIN_OSPEED_40M((PIN_ADC_DOUT)) |            \
                                     PIN_OSPEED_40M((PIN_ADC_SCLK)) |       \
                                     PIN_OSPEED_40M((PIN_ENC_CLICK)) |      \
                                     PIN_OSPEED_40M((PIN_ENC_A)) |          \
                                     PIN_OSPEED_40M((PIN_TRST)) |           \
                                     PIN_OSPEED_40M((PIN_ENC_B)) |          \
                                     PIN_OSPEED_40M((PIN_DBG_TX)) |         \
                                     PIN_OSPEED_40M((PIN_DBG_RX)) |         \
                                     PIN_OSPEED_40M((PIN_SCL)) |            \
                                     PIN_OSPEED_40M((PIN_SDA)) |            \
                                     PIN_OSPEED_40M((PIN_ADC_PDWN)) |       \
                                     PIN_OSPEED_40M((PIN_STEAM)) |          \
                                     PIN_OSPEED_40M((PIN_VACUUM)) |         \
                                     PIN_OSPEED_40M((PIN_FAN)) |            \
                                     PIN_OSPEED_40M((PIN_DEHUM)) |          \
                                     PIN_OSPEED_40M((PIN_HEATER)))
#define VAL_GPIOB_PUPDR             (PIN_PUPDR_PULLUP((PIN_ADC_DOUT)) |         \
                                     PIN_PUPDR_PULLUP((PIN_ADC_SCLK)) |       \
                                     PIN_PUPDR_PULLUP((PIN_ENC_CLICK)) |      \
                                     PIN_PUPDR_PULLUP((PIN_ENC_A)) |          \
                                     PIN_PUPDR_PULLUP((PIN_TRST)) |           \
                                     PIN_PUPDR_PULLUP((PIN_ENC_B)) |          \
                                     PIN_PUPDR_PULLUP((PIN_DBG_TX)) |         \
                                     PIN_PUPDR_PULLUP((PIN_DBG_RX)) |         \
                                     PIN_PUPDR_PULLUP((PIN_SCL)) |            \
                                     PIN_PUPDR_PULLUP((PIN_SDA)) |            \
                                     PIN_PUPDR_PULLUP((PIN_ADC_PDWN)) |       \
                                     PIN_PUPDR_PULLUP((PIN_STEAM)) |          \
                                     PIN_PUPDR_PULLUP((PIN_VACUUM)) |         \
                                     PIN_PUPDR_PULLUP((PIN_FAN)) |            \
                                     PIN_PUPDR_PULLUP((PIN_DEHUM)) |          \
                                     PIN_PUPDR_PULLUP((PIN_HEATER)))
#define VAL_GPIOB_ODR               (PIN_ODR_HIGH((PIN_ADC_DOUT)) |             \
                                     PIN_ODR_HIGH((PIN_ADC_SCLK)) |       \
                                     PIN_ODR_HIGH((PIN_ENC_CLICK)) |      \
                                     PIN_ODR_HIGH((PIN_ENC_A)) |          \
                                     PIN_ODR_HIGH((PIN_TRST)) |           \
                                     PIN_ODR_HIGH((PIN_ENC_B)) |          \
                                     PIN_ODR_HIGH((PIN_DBG_TX)) |         \
                                     PIN_ODR_HIGH((PIN_DBG_RX)) |         \
                                     PIN_ODR_HIGH((PIN_SCL)) |            \
                                     PIN_ODR_HIGH((PIN_SDA)) |            \
                                     PIN_ODR_HIGH((PIN_ADC_PDWN)) |       \
                                     PIN_ODR_LOW((PIN_STEAM)) |          \
                                     PIN_ODR_LOW((PIN_VACUUM)) |         \
                                     PIN_ODR_LOW((PIN_FAN)) |            \
                                     PIN_ODR_LOW((PIN_DEHUM)) |          \
                                     PIN_ODR_LOW((PIN_HEATER)))
#define VAL_GPIOB_AFRL              (PIN_AFIO_AF((PIN_ADC_DOUT), 0) |           \
                                     PIN_AFIO_AF((PIN_ADC_SCLK), 0) |       \
                                     PIN_AFIO_AF((PIN_ENC_CLICK), 0) |      \
                                     PIN_AFIO_AF((PIN_ENC_A), 0) |          \
                                     PIN_AFIO_AF((PIN_TRST), 0) |           \
                                     PIN_AFIO_AF((PIN_ENC_B), 0) |          \
                                     PIN_AFIO_AF((PIN_DBG_TX), 0) |         \
                                     PIN_AFIO_AF((PIN_DBG_RX), 0))
#define VAL_GPIOB_AFRH              (PIN_AFIO_AF((PIN_SCL), 0) |           \
                                     PIN_AFIO_AF((PIN_SDA), 0) |            \
                                     PIN_AFIO_AF((PIN_ADC_PDWN), 0) |       \
                                     PIN_AFIO_AF((PIN_STEAM), 0) |          \
                                     PIN_AFIO_AF((PIN_VACUUM), 0) |         \
                                     PIN_AFIO_AF((PIN_FAN), 0) |            \
                                     PIN_AFIO_AF((PIN_DEHUM), 0) |          \
                                     PIN_AFIO_AF((PIN_HEATER), 0))

/*
 * GPIOC setup:
 */

#define VAL_GPIOC_MODER             (PIN_MODE_INPUT((PIN_MENU)) |       \
                                     PIN_MODE_INPUT((PIN_OSC32_IN)) |   \
                                     PIN_MODE_INPUT((PIN_OSC32_OUT)))
#define VAL_GPIOC_OTYPER            (PIN_OTYPE_PUSHPULL((PIN_MENU)) |       \
                                     PIN_OTYPE_PUSHPULL((PIN_OSC32_IN)) |       \
                                     PIN_OTYPE_PUSHPULL((PIN_OSC32_OUT)))
#define VAL_GPIOC_OSPEEDR           (PIN_OSPEED_40M((PIN_MENU)) |           \
                                     PIN_OSPEED_40M((PIN_OSC32_IN)) |           \
                                     PIN_OSPEED_40M((PIN_OSC32_OUT)))
#define VAL_GPIOC_PUPDR             (PIN_PUPDR_PULLUP((PIN_MENU)) |         \
                                     PIN_PUPDR_PULLUP((PIN_OSC32_IN)) |        \
                                     PIN_PUPDR_PULLUP((PIN_OSC32_OUT)))
#define VAL_GPIOC_ODR               (PIN_ODR_HIGH((PIN_MENU)) |             \
                                     PIN_ODR_HIGH((PIN_OSC32_IN)) |            \
                                     PIN_ODR_HIGH((PIN_OSC32_OUT)))
#define VAL_GPIOC_AFRL              0
#define VAL_GPIOC_AFRH              (PIN_AFIO_AF((PIN_MENU), 0) |           \
                                     PIN_AFIO_AF((PIN_OSC32_IN), 0) |           \
                                     PIN_AFIO_AF((PIN_OSC32_OUT), 0))

/*
 * GPIOD setup:
 */
#define VAL_GPIOD_MODER             0
#define VAL_GPIOD_OTYPER            0
#define VAL_GPIOD_OSPEEDR           0
#define VAL_GPIOD_PUPDR             0
#define VAL_GPIOD_ODR               0
#define VAL_GPIOD_AFRL              0
#define VAL_GPIOD_AFRH              0

/*
 * GPIOF setup:
 */
#define VAL_GPIOF_MODER             (PIN_MODE_INPUT((PIN_RESET)) |         \
                                     PIN_MODE_INPUT((PIN_MANUAL)))
#define VAL_GPIOF_OTYPER            (PIN_OTYPE_PUSHPULL((PIN_RESET)) |     \
                                     PIN_OTYPE_PUSHPULL((PIN_MANUAL)))
#define VAL_GPIOF_OSPEEDR           (PIN_OSPEED_2M((PIN_RESET)) |          \
                                     PIN_OSPEED_2M((PIN_MANUAL)))
#define VAL_GPIOF_PUPDR             (PIN_PUPDR_PULLUP((PIN_RESET)) |     \
                                     PIN_PUPDR_PULLUP((PIN_MANUAL)))
#define VAL_GPIOF_ODR               (PIN_ODR_HIGH((PIN_RESET)) |           \
                                     PIN_ODR_HIGH((PIN_MANUAL)))
#define VAL_GPIOF_AFRL              (PIN_AFIO_AF((PIN_RESET), 0) |         \
                                     PIN_AFIO_AF((PIN_MANUAL), 0))
#define VAL_GPIOF_AFRH              0


#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* _BOARD_H_ */
