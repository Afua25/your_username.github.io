//=================================================================
// The main program file.
//
// Copyright 2022 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//==================================================================

// External libs
#include <stdlib.h>

// Project includes
#include "globals.h"
#include "hardware.h"
#include "graphics.h"
#include "keyboard.h"
#include "doubly_linked_list.h"



//some LED's to use for debugging.
DigitalOut myled1(LED1);
DigitalOut myled2(LED2);
DigitalOut myled3(LED3);
DigitalOut myled4(LED4);
int run_time = 900000; 

void set_random_seed(Timer);
void start();

/*
* This function handles the main logic of the game. You should
* initialize the hardware in this function, make calls to 
* functions that update the keyboard and your guess of 
* the word. 
*/
int main()
{
while(1) {
    GameInputs inputs = read_inputs();
    // First things first: initialize hardware
    ASSERT_P(hardware_init() == ERROR_NONE, "Hardware init failed!");
    pc.printf("Program Starting\n");
    //led1 hardware initialization
    
    myled1=1;  
    Timer t;
    int dt; // delta time
    
/* Put code here to initialize the game state:
   1) you will need to use a psuedo random number generator such as
     rand() to randomly select a goal word from the dictionary.
     The random function needs to be seeded before you call rand(),
     otherwise, rand() will always generate the same series of numbers.
     Call the function set_random_seed -- you need to complete its
     definition below.*/
    set_random_seed(t);
    //goalWord = 
    
/*
   2) call init_keyboard() and show start screen
   
   
   3) initialize any other game state that you add.
*/
    init_keyboard();
    draw_sprite();
    draw_sprite2();
    draw_sprite3();
    draw_sprite4();
    draw_sprite5();
    draw_sprite6();
    draw_sprite7();
    draw_sprite8();
    draw_sprite9();
    draw_sprite10();
    draw_sprite11();
    remove_letter();
    
//    isecret = rand()% 10;
    
/* Insert code into this game loop to complete its implementation:
*/

    while(1){
        t.start(); //start a timer
        draw_lower_status(); //draw the lower status bar
        
        inputs = read_inputs(); //read the inputs of the game
        
//            pc.printf("guess# %d\n", letters_guessed);
        
        if (!button3) {
//            moveleft();
            break; //moves letter to left of string 
        } 
        if(!button4){
                moveright(); //moves letter to right of string 
                }
        if (!button2){
            //pc.printf("here!");
            select_letter();
            letters_guessed++;
//            pc.printf("sel %d\n", letters_guessed);
            }
            
        if (!button1){ 
            remove_letter();
            letters_guessed--;
//            pc.printf("rem %d\n", letters_guessed);
            }
        if(letters_guessed == 5)
        {
            int check = check_word();
            num_guesses++;
            if(check == 1)
            {
                uLCD.cls();
                uLCD.printf("you win!");
                break;
            }
            else if(check == 0)
            {
                uLCD.cls();
                uLCD.printf("Game Over!");
                break;
                
            }
            letters_guessed = 0;
        }
        //pc.printf("x:%lf   y:%lf z:%lf\r\n",inputs.ax,inputs.ay,inputs.az);
        wait(0.5);
            

        /*
        your code here, make decisions based on those inputs, update the keyboard
        make selections, update words etc.
        */
//        if( () {
//            uLCD.locate(0,0);
//            uLCD.printf("GAME OVER");
//            break;   
//        }
        
        //if player score >=6, win the game!
//        if(6<=().score)
//        {
//            uLCD.locate(0,0);
//            uLCD.printf("YOU WON!");
//            break;
//        }        
        run_time = run_time - dt; //adding the run time 
        uLCD.locate(12,0); // locate the timer 
        uLCD.printf("%d",run_time/1000); // print time
        if (run_time < 0) // runtime conditional 
        {
            uLCD.cls(); // clear screen 
            while(1) {
                uLCD.locate(0,0);
                uLCD.printf("Times Up!");
                if (!button3) {
                    break;
                }
            }
        }
        // compute update time 
        t.stop();
           dt = t.read_ms();
        if (dt < 100) wait_ms(100 - dt);
        
        }
//        destroyList(());

//        return 0;
uLCD.cls();
}
}



/* This should be called in the main function above.
*
* This function sets the random seed for the game using srand(seed).
* One incomplete way to do this is given below: start a Timer and sample it
* to get a seed. The problem is that the same exact time will be read
* every time you reset the mbed.  You need to add code to introduce
* variability into when the timer is stopped.  An easy way to do this
* is to get the user to press a push button to stop the timer at a random
* time.  You can print a prompt to the screen to ask the user to push
* any button to start, then run an infinite while loop that waits for a push 
* button press to break. The Timer is then stopped and read and elapsed time
* used as the seed. (This requires using read_inputs() into a GameInputs variable.)
*/
void select_level(void) {
    
    wait_ms(1000);
int noChoice = 1; 
    //GameInputs inputs;
    uLCD.cls();
    uLCD.locate(0,0);
    uLCD.printf("Press button to\nselect level.\n1. Normal\n2. Sudden death\n3. Medium");  
    while(noChoice){
//      if (inputs.b1 || inputs.b2 || inputs.b3) break;
        if(!button1)
        {
            noChoice = 0;
            run_time = 900000; 
        } else if(!button2)
        {
            noChoice = 0;
            run_time = 100000; 
        } else if(!button3)
        {
            noChoice = 0;
            run_time = 500000; 
        }



    }
//    
//
////    else if(inputs.b2)
////
////    else
//
}

void set_random_seed(Timer t) {
    //GameInputs inputs;
    //Timer t;
    t.start(); // start the timer
    uLCD.printf("Push any button to start.\n");
    //wait_ms(1000);
    while(button3)
    {
        speaker.period(1.0/500.0); // 500hz period
        speaker =0.5; //50% duty cycle - max volume
        wait(1);
        speaker=0.0; // turn off audio
    }
    
//    while(1){
// //       inputs = read_inputs();
//        if (inputs.b1 || inputs.b2 || inputs.b3)break;
//    }
    draw_sprite12();
    draw_sprite12();
    draw_sprite12();
    draw_sprite13();
    draw_sprite13();
    draw_sprite13();
    draw_sprite14();
    draw_sprite14();
    draw_sprite14();
    draw_sprite15();
    draw_sprite15();
    draw_sprite15();
    draw_sprite16();
    draw_sprite16();
    draw_sprite16();
    draw_sprite17();
    draw_sprite17();
    draw_sprite17();
    draw_sprite18();
    draw_sprite18();
    draw_sprite18();
    draw_sprite12();
    draw_sprite12();
    draw_sprite12();
    select_level();
    
    uLCD.cls();
    t.stop();  //  end the timer
    int seed = t.read_ms(); //read the number of milliseconds elapsed between the start and stop
    srand(seed); // use elapsed time as the seed
    
//    uLCD.printf("seed: %d\n", seed); // TEMP: delete this
}
// ===User implementations end===
void start() {
    GameInputs inputs;
    uLCD.cls();
    uLCD.printf("Try again?\n");
    do {
    inputs = read_inputs();
    } while (!inputs.b3);
}

// ===User implementations begin===


