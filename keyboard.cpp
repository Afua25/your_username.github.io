#include "keyboard.h"
#include "dictionary.h"
#include "doubly_linked_list.h"
#include <string>


DLinkedList* keyboard;
LLNode* current;
LLNode* prev_current;
LLNode* next_current;
int move = 0;
char letters[5];
char guess[5];
char Yellow[5];
int i = 0;
int counter = 0;
int num_guesses = 0;
int letters_guessed = 0;
int xMove = 0;
int xPos = 0;
int num_matches = 0; 
//int y_line_print_num = 4;

int compareChar(void* input1, void* input2){
    if(*(char*)input1 == *(char*)input2){
        return 1;
    }
    else{
        return 0;
    }
}


void init_keyboard(){
    keyboard = create_dlinkedlist(compareChar);
    
    //pc.printf("%d is current\n\r", current);
//    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    
    for (int i = 0; i < 26; i++){
        char* box =(char*)malloc(sizeof(char));
        *box = 'a'+i;
        insertTail(keyboard, box);
    }
    getHead(keyboard)->prev = getTail(keyboard);
    getTail(keyboard)->next = getHead(keyboard);
        
    current = keyboard->head;
    prev_current = current->prev;
    next_current = current->next; 
    uLCD.locate(8,15);
    char* letter = (char*) keyboard->head->data;
    uLCD.text_bold(1);
    uLCD.printf("%c\n", *letter);
    char* prev_letter = (char*)prev_current->data;
    char* next_letter = (char*)next_current->data;
    uLCD.printf("%c\n", *letter);
    uLCD.locate(7,15);
    uLCD.printf("%c\n", *prev_letter);
    uLCD.locate(9,15);
    uLCD.printf("%c\n", *next_letter);
//    getData(getHead(keyboard));
    int word_index = rand()%10;
    for (int i = 0; i < 5; i++) {
        letters[i] = dictionary[word_index].unique[i];
        pc.printf("%c", letters[i]);
    }
 //       dictionary word_index = "0,1,2,3,4,5,6,7,8,9"
}


void moveleft()
{
//    pc.printf("moveleft\n\r"); 
//    pc.printf("the current node address is %d\n\r",current);
    if(current)
    {
    if (current->prev) {
        current = current->prev;
        uLCD.locate(8,15);
        uLCD.printf("%c\n", *(char*)getData(current));
        //pc.printf((char*) getData(current)); 
             
    }
    }
}

void moveright()
{
//        pc.printf("moveright\n\r");
//        pc.printf("the current node address is %d\n\r",current);
        if(current)
        {
        if (current->next) {
        current = current->next;
        uLCD.locate(8,15);
        uLCD.text_bold(1);
        uLCD.printf("%c\n", *(char*)getData(current));
        
    }
    }
    if(prev_current)
        {
        if (prev_current->next) {
        prev_current = prev_current->next;
        uLCD.locate(7,15);
        uLCD.printf("%c\n", *(char*)getData(prev_current));
        
    }
    }
    if(next_current)
        {
        if (next_current->next) {
        next_current = next_current->next;
        uLCD.locate(9,15);
        uLCD.printf("%c\n", *(char*)getData(next_current));
        
    }
    }
}


void select_letter()
{   
        uLCD.locate(5 + letters_guessed, 4 + num_guesses);
//        pc.printf("Sel %c\n", letters_guessed);
        uLCD.printf ("%c\n", *(char*)getData(current));
        guess[letters_guessed] = *(char*)getData(current);
//        pc.printf("%c\n", guess[i-1]);
//        pc.printf("%c\n", *(char*)getData(current));

}


void remove_letter()
{  
        uLCD.locate(5 + letters_guessed , 4 + num_guesses);
        uLCD.printf (" ");
}

char semi_correct[6] = "     ";

int check_word()
{
     num_guesses++;
     num_matches = 0;
     xPos = 0;
     counter = 0;
     pc.printf("CHECK WORD\n");
     for (int i = 0; i < 5; i++){
         pc.printf("Guess: %c\n",(guess[i]));
         
         if (guess[i] == letters[i]) {
            uLCD.locate(5 + letters_guessed - 5 + i, 4 + num_guesses-1);
             uLCD.printf("%c", guess[i]);
         } else {
            uLCD.locate(5 + letters_guessed - 5 + i, 4 + num_guesses-1);
            uLCD.printf(" ");
         
         }
         
         
         
         
         if ((guess[i]) == letters[i]){
             semi_correct[i] = guess[i];
             counter++;
             num_matches++;
             pc.printf("Counter: %d\n", counter);
             if (num_matches == 1) {
                 xPos = i;
            }
        }
        else
        {
            
                //uLCD.locate(5 + letters_guessed - i - 1, 3 + num_guesses);  
//                uLCD.printf(" ");               
            bool letter_check = false;           
            for(int j = 0; j<5; j++)
            {
                if(guess[i] == letters[j])
                {
                   uLCD.locate(4 + num_guesses, 2); // put this wherever you want 
                   uLCD.printf("%c",guess[i]);//letter at guess[i] is contained in the target word, but was put in the wrong spot
                   letter_check = true; 
                   xMove++;
                   
                }
            } 
            if (!letter_check)
            {
                LLNode* missLetter = findNode(keyboard,(char*)&guess[i]);
                pc.printf("%x\n", missLetter);
                pc.printf("sel %c\n", (char*)guess[i]);
                if (missLetter != NULL)
                {
                    pc.printf("MORE %x\n",missLetter);
                    deleteNode(keyboard, missLetter);
                    pc.printf("DELETED \n");
                } 
            }
        } 
     }
     if (counter == 5)
     {
         return 1;
     }
     else if(num_guesses>5)
     {
        return 0; // game over
        }
     else
     {
        letters_guessed = 0;
        //uLCD.locate(5 + xPos,4 + num_guesses);
                        //uLCD.locate(5 + letters_guessed, 3 + num_guesses);
        //uLCD.printf("%s", semi_correct);
        for(int i = 0; i<5; i++)
        {
            guess[i] = ' ';
            semi_correct[i] = ' ';
            }
    }
       
    /*
     
     for(int guessword = 0; guessword < 5; guessword ++)
     { 
        for(int targetWord = 0; targetword < 5; targetword++)
        {
            if(guessword[0])
            {
                
            }
        }
     }
} 


//        if ((guess[0]) == letters[0]){
//            counter++;
//            if(guess[1] == letters[1]){
//                counter++;                
//                if(guess[2] == letters[2]){
//                    counter++;                   
//                    if(guess[3] == letters[3]){
//                        counter++;                     
//                        if(guess[4] == letters[4]){
//                            counter++;                          
//                            }else{return 0;}
//                        }else{return 0;}
//                    }else{return 0;}
//                }else{return 0;}
//            }else{return 0;}
*/
}