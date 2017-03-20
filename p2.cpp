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
  int ch{0};

  char *choices[] = {"Open","Save","Save As", "Exit"};
  ITEM **my_items;
  int c;
  MENU *my_menu;
  int n_choices, i;
  ITEM *cur_item;

  /* Initialize items */
  n_choices = ARRAY_SIZE(choices);
  my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
  for(i = 0; i < n_choices; ++i)
    my_items[i] = new_item(choices[i], choices[i]);
  my_items[n_choices] = (ITEM *)NULL;
  item_opts_off(my_items[3], O_SELECTABLE);
  item_opts_off(my_items[6], O_SELECTABLE);
  /* Create menu */
  my_menu = new_menu((ITEM **)my_items);
   if(argc != 2){//if there are not two arguments, print an error
     cout <<"Error, try again" << endl;
   }

   else{//else do the below
     initscr();
     curs_set(0);//setting the cursor to not be visible
     getmaxyx(stdscr, row, col);
     x=row-3.5;
     y=col-1;
     pad = newpad(x, y); //adding extra lines to ensure that the window is large enough for the file
     keypad(pad, TRUE);
     printw("F1: Menu");
     refresh();
     box(pad, 0, 0);
     wrefresh(pad);

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
	 mRow = x/1.5;//initially divided by 2
	 mCol = y/1.5;//initially divided by 2
	 menu = newpad(mRow, mCol);
	 box(menu, 0, 0);
	 wrefresh(menu);
	 keypad(menu, TRUE);

	 tX = tX*2;
	 tY = tY+4;
	 bX = row + tX;
	 bY = col + tY;

	 prefresh(menu, 0, 0, tX, tY, bX, bY);
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
    







