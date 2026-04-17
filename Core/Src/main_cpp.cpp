#include "servo.hpp"
#include "main_cpp.hpp"
#include "lcd.hpp"
#include "keypad.hpp"
#include "game.hpp"
#include "hcsr04.hpp"
#include "cstdio"



extern "C" {
    extern volatile uint8_t ble_command_received;
    extern volatile uint8_t last_cmd;
    extern TIM_HandleTypeDef htim4;
    extern I2C_HandleTypeDef hi2c1;
    extern TIM_HandleTypeDef htim2;
}

Servo myServo(&htim4, TIM_CHANNEL_3);
LCD lcd(&hi2c1, (0x27 << 1));

pinStruct_t rowPins[] = {
    {GPIOC, GPIO_PIN_1},
    {GPIOA, GPIO_PIN_3},
    {GPIOC, GPIO_PIN_0},
    {GPIOC, GPIO_PIN_5}
};

pinStruct_t colPins[] = {
    {GPIOC, GPIO_PIN_4},
    {GPIOB, GPIO_PIN_0},
    {GPIOC, GPIO_PIN_3}
};

Keypad keypad(rowPins, colPins);
SafeGame game(keypad, lcd, myServo);


static HCSR04 sonar(&htim2);

extern "C" void main_cpp_init(void) {
    myServo.Start();
    myServo.TurnShaft(SERVO_MIDPOSITION);
    lcd.Init();
    lcd.Clear();
    lcd.Print("System Ready");
    sonar.Start();
}


extern "C" void main_cpp_loop(void) {

	char key = keypad.GetKey();

    if (key != 0) {
    	if(key == '*') {
    		game.Play();
    	} else if(key == '#') {
    	    uint32_t dist = sonar.GetDistance();
    	    lcd.Clear();
    	    lcd.SetCursor(0, 0);
    	    lcd.Print("Dist: ");
    	    lcd.Print(dist);
    	    lcd.Print(" cm ");
    	} else {
    		lcd.Clear();
    		lcd.SetCursor(0, 0);
    		lcd.Print("Key Pressed:");
    		lcd.SetCursor(1, 0);
    		lcd.Print(key);
    		if (key == '7') myServo.TurnShaft(SERVO_LEFTPOSITION);
    		else if (key == '0') myServo.TurnShaft(SERVO_MIDPOSITION);
    		else if (key == '9') myServo.TurnShaft(SERVO_RIGHTPOSITION);
    	}
    }
}

extern "C" void receiveData(uint8_t* data_buffer, uint8_t Nb_bytes)
{
    lcd.Clear();
    lcd.SetCursor(0, 0);
    lcd.Print("Received:");
    lcd.SetCursor(1, 0);
    for (int i = 0; i < Nb_bytes; i++) {
        lcd.Print((char)data_buffer[i]);

        uint8_t cmd = data_buffer[i];

			if (cmd == 'L') myServo.TurnShaft(SERVO_LEFTPOSITION);
			if (cmd == 'M') myServo.TurnShaft(SERVO_MIDPOSITION);
			if (cmd == 'R') myServo.TurnShaft(SERVO_RIGHTPOSITION);

    }
}
