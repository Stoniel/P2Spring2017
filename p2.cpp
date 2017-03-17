#include <ncurses.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

using std::cout;
using std::string;
using std::ifstream;
using std::endl;


int main(const int argc, const char * argv []){
  string fName{argv[1]};
  ifstream myFile(fName);
  string line;
  int row, col;
  int x, y;
  WINDOW *pad;
  WINDOW *menu;
  int pos{0};
  //int pos1{0};
  int ch{0};
  //int ch1{0};
   if(argc != 2){//if there are not two arguments, print an error
     cout <<"Error, try again" << endl;
   }

   else{//else do the below
     initscr();
     curs_set(0);//setting the cursor to not be visible
     getmaxyx(stdscr, row, col);
    
     x=row-5;
     y=col-5;
     pad = newpad(x, y); //adding extra lines to ensure that the window is large enough for the file
     keypad(pad, TRUE);
     box(pad, 0, 0);
     wrefresh(pad);
     if(myFile.is_open()){
       while(getline(myFile, line)){
	 //wprintw(pad, "%s\n", line.c_str()); 
       }
     }
     int tX,tY,bX,bY;
     tX = row/2 - x/2;
     tY = col/2 - y/2;
     bX = row + tX;
     bY = col + tY;

     prefresh(pad,0,0,tX,tY,bX,bY);//refresh pad
     while(true){
       ch = wgetch(pad);
       switch(ch){//using switch statement to get the user's input
	 /*
	 case KEY_UP://check if up arrow is pressed
	 if(pos >= 0){
	   pos--;
	 }
	 prefresh(pad, pos, 0, 0, 0, row-1, col);//refresh pad
	 break;

       case KEY_DOWN://check if down arrows are pressed
	 prefresh(pad, pos, 0, 0, 0, row-1, col);//refresh pad
	 break;	
	 */
       case KEY_F(1):
	 int mRow, mCol;
	 mRow = x/1.5;
	 mCol = y/1.5;
	 menu = newpad(mRow, mCol);
	 box(menu, 0, 0);
	 wrefresh(menu);
	 keypad(menu, TRUE);

	 /*tX = row/4;
	 tY = col/4 - mCol/4;
	 bX = mRow + tX;
	 bY = mCol + tY;
	 */

	 tX = tX*2;
	 tY = tY+4;
	 bX = row + tX;
	 bY = col + tY;

	 prefresh(menu, 0, 0, tX, tY, bX, bY);
	 /*while(true){
	   ch1 = wgetch(menu);

	  switch(ch1){//using switch statement to get the user's input

	 case KEY_UP://check if up arrow is pressed
	 if(pos1 >= 0){
	   pos1--;
	   }
	   prefresh(menu, pos1, 0, 0, 0, row-1, col);//refresh pad
	   break;

	 case KEY_DOWN://check if down arrows are pressed
	   pos1++;
	   prefresh(menu, pos1, 0, 0, 0, row-1, col);//refresh pad
	   break;	
	   
	 }//end while for F1
	 //prefresh(menu, posMenu, 0, 0, 0, row/4 - 1, col);//refresh pad
	
	 }*/
       if(ch!=KEY_UP && ch!=KEY_DOWN && ch!=KEY_F(1)){//if key entered does not equal up or down, break out of the while loop
       break;
	}
    }
   }
   delwin(pad);//delete pad
   endwin();//close ncurses mode
   myFile.close();//close file
  return EXIT_SUCCESS;    
  
   }
}    
    







