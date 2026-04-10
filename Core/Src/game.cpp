/*
 * game.cpp
 *
 *  Created on: Apr 10, 2026
 *      Author: bylka
 */

#include "game.hpp"
#include <stdio.h>
#include <cstdlib>

SafeGame::SafeGame(Keypad& k, LCD& l) : keypad(k), lcd(l) {}

void SafeGame::GenerateCode() {

    srand(HAL_GetTick());

    for(int i = 0; i < CODE_LENGTH; i++) {
        secretCode[i] = (rand() % 10) + '0';
    }
    secretCode[CODE_LENGTH] = '\0';

}

int SafeGame::CountBulls() {
    int bulls = 0;
    for (int i = 0; i < CODE_LENGTH; i++) {
        if (secretCode[i] == userGuess[i]) bulls++;
    }
    return bulls;
}

int SafeGame::CountCows() {
    int cows = 0;
    for (int i = 0; i < CODE_LENGTH; i++) {
        for (int j = 0; j < CODE_LENGTH; j++) {
            if (i != j && secretCode[i] == userGuess[j]) cows++;
        }
    }
    return cows;
}

void SafeGame::Play() {
    GenerateCode();
    lcd.Clear();
    lcd.Print("Safe Locked!");
    HAL_Delay(1000);

    while(true) {
        lcd.Clear();
        lcd.Print("Enter code:");

        for(int i = 0; i < CODE_LENGTH; i++) {
            char key = 0;

            while(key == 0) key = keypad.GetKey();

            userGuess[i] = key;
            lcd.SetCursor(1, i);
            lcd.Print(key);
            while(keypad.GetKey() != 0);
            HAL_Delay(30);
        }

        HAL_Delay(500);
        int b = CountBulls();
        int c = CountCows();

        lcd.Clear();
        if(b == CODE_LENGTH) {
            lcd.Print("WIN! Open!");
            HAL_Delay(3000);
            return;
        } else {
            char buf[16];
            sprintf(buf, "B:%d C:%d", b, c);
            lcd.Print("Wrong!");
            lcd.SetCursor(1, 0);
            lcd.Print(buf);
            HAL_Delay(2000);
        }
    }
}
