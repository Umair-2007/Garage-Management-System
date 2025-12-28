#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "FreeRTOS.h"
#include "task.h"

#define IR_PIN PA0
#define SERVO_PIN PB1

TaskHandle_t ServoTaskHandle;

void servo_init(){
    DDRB |= (1 << SERVO_PIN);
    TCCR1A = (1 << COM1A1) | (1 << WGM11);
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11);
    ICR1 = 39999;
}

void servo_angle(uint8_t angle){
    uint16_t PWM_value;

    PWM_value = 2000 + ((uint32_t)angle * 2000) / 180;
    OCR1A = PWM_value;
}

void vIRTask(void *pvParameters){
    DDRA &= ~(1 << IR_PIN);
    PORTA |= (1 << IR_PIN);

    while(1){
        if(!(PINA & (1 << IR_PIN))){
            xTaskNotifyGive(ServoTaskHandle);
            vTaskDelay(pdMS_TO_TICKS(500));
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void vServoTask(void *pvParameters){
    servo_init();

    while(1){
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        servo_angle(90);
        vTaskDelay(pdMS_TO_TICKS(5000));
        servo_angle(0);
    }
}

int main(void){
    sei();

    xTaskCreate(vIRTask, "IR Task", 128, NULL, 1, NULL);
    xTaskCreate(vServoTask, "Servo Task", 128, NULL, 2, &ServoTaskHandle);

    vTaskStartScheduler();

    while(1);
}