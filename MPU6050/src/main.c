#include<stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "MPU6050.h"
#include "hardware/adc.h"

#define SCL 19
#define SDA 18

int main()
{

    //intialize stdio
    stdio_init_all();
    // Make sure GPIO is high-impedance, no pullups etc
    adc_init();
    adc_gpio_init(26);
    // Select ADC input 0 (GPIO26)
    adc_select_input(0);
    //intialize i2c1
    i2c_init(I2C_PORT, 100*1000);
    gpio_set_function(SCL, GPIO_FUNC_I2C);
    gpio_set_function(SDA, GPIO_FUNC_I2C);

    // need to enable the pullups
    gpio_pull_up(SCL);
    gpio_pull_up(SDA);

    int16_t accelerometer[3], gyro[3], temp;
    MPU6050_Reset();
    while(1)
    {  
        // 12-bit conversion, assume max value == ADC_VREF == 3.3 V
        const float conversion_factor = 3.3f / (1 << 12);
        uint16_t result = adc_read();
        MPU6050_ReadData(accelerometer, gyro, &temp);
        //printf("Raw value: 0x%03x, voltage: %f V\n", result, result * conversion_factor);
        //printf("Accelerometer   X_OUT= %d   Y_OUT= %d   Z_OUT= %d\r\n",accelerometer[0], accelerometer[1], accelerometer[2] );
        //printf("Gyro   X_OUT= %d   Y_OUT= %d   Z_OUT= %d\r\n",gyro[0], gyro[1], gyro[2] );
        //printf("Temperature= %2f \r\n",(temp/340.0) + 36.53 );
        printf("%03x, %f, %d, %d, %d, %d, %d, %d, %f\r\n", 
            result, result * conversion_factor,
            accelerometer[0], accelerometer[1], accelerometer[2],
            gyro[0], gyro[1], gyro[2],
            (temp / 340.0) + 36.53);

        sleep_ms(500);
    }

    return 0;
}