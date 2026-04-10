/*
 * game.hpp
 *
 *  Created on: Apr 10, 2026
 *      Author: bylka
 */

#ifndef INC_GAME_HPP_
#define INC_GAME_HPP_


#include "keypad.hpp"
#include "lcd.hpp"

#define CODE_LENGTH 2

class SafeGame {
private:
    Keypad& keypad;
    LCD& lcd;

    char secretCode[CODE_LENGTH + 1];
    char userGuess[CODE_LENGTH + 1];

    void GenerateCode();
    int CountBulls();
    int CountCows();

public:
    SafeGame(Keypad& k, LCD& l);
    void Play();
};


#endif /* INC_GAME_HPP_ */
