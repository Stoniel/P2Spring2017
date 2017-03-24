
//Includes
#include <ncurses.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <menu.h>
#include <form.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 4

using std::cout;
using std::string;
using std::ifstream;
using std::endl;

int ch,rows1,cols1;
char const *choices[] = {"Open","Save","Save As", "Exit"};
ITEM **my_items;
MENU *my_menu;
WINDOW *menuWin;
WINDOW *popup;
WINDOW *my_form_win;
int n_choices;
ITEM * cur;
FIELD *field;
FORM *my_form;

void openFile();
void saveFile();
void saveAs();
void cleanUp();




void makeForm(){
  echo();
  //  field[0] = new_field(1, 12, 0, 0, 0, 0);

  /* Create the form and post it */
  my_form = new_form(&field);
  set_form_win(my_form, my_form_win);

  /* Calculate the area required for the form */
  int formRows, formCols;
  formRows = rows1/8-2;
  formCols = cols1/2-4;
  scale_form(my_form, &formRows, &formRows);

  /* Create the window to be associated with the form */
  my_form_win = newwin(rows1/2, cols1/2, 4, 4);
  keypad(my_form_win, TRUE);

  /* Set main window and sub window */
  set_form_sub(my_form, derwin(my_form_win, formRows/2, formCols/2, 6, 2));
  box(my_form_win, 0, 0);
  post_form(my_form);
  wrefresh(my_form_win);

  /* Loop through to get user requests */
  while((ch = getch()) != '\n')
    {
      switch(ch)
	{
	case '\b':	
	case KEY_BACKSPACE:
	  form_driver(my_form, REQ_DEL_PREV);
	  break;
	default:
	  form_driver(my_form, ch);	  
	}
    }
}

void closeMenu(){
unpost_menu(my_menu);				  

 for(int i = 0; i < n_choices; ++i)
 {				      
   free_item(my_items[i]);
 }

 free_menu(my_menu);
 wclear(menuWin);	
 wrefresh(menuWin);
 delwin(menuWin);

}


void showMenu()
{
	noecho();
	getmaxyx(stdscr,rows1,cols1);

	//initialize items
	n_choices = ARRAY_SIZE(choices);
	my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
	for(int i = 0; i < n_choices; ++i)
	{
	  my_items[i] = new_item(choices[i], " "); //choices[i]);
	}
	my_items[n_choices] = (ITEM *)NULL;
	menuWin =  newwin(10,40,4,4);//Change
	keypad(menuWin,TRUE);
	box(menuWin,0,0);

	item_opts_off(my_items[4], O_SELECTABLE);
	//item_opts_off(my_items[6], O_SELECTABLE);

	// Create menu
	my_menu = new_menu((ITEM **)my_items);

	/* Set main window and sub window */
	set_menu_win(my_menu, menuWin);
	set_menu_sub(my_menu, derwin(menuWin, 6, 38, 3, 1));

	/* Set menu mark to the string */
	set_menu_mark(my_menu, " > ");

	/* Print a border around the main window and print a title */
	box(menuWin, 0, 0);
	mvwprintw(menuWin, 1, 1, "  My Menu  F1 to exit Menu");
	mvwaddch(menuWin, 2, 0, ACS_LTEE);
	mvwhline(menuWin, 2, 1, ACS_HLINE, 38);
	mvwaddch(menuWin, 2, 39, ACS_RTEE);
	//mvprintw(LINES - 2, 0, "F1 to exit ");
	refresh();
	
	/* Post the menu */
	post_menu(my_menu);
	wrefresh(menuWin);
	//While Loop which controls the Menu    
	while(ch = wgetch(menuWin)){
	  switch(ch){
		case KEY_DOWN:
			  menu_driver(my_menu, REQ_DOWN_ITEM);
			  break;

	  case KEY_UP:
	    menu_driver(my_menu, REQ_UP_ITEM);
	    break;
	  case KEY_F(1):
	    closeMenu();
	    break;
	  case '\n':
	    cur = current_item(my_menu);
	    char openChar = '\0';
	    if(cur == my_items[0])
	      {//if user presses enter on open
		closeMenu();
		getmaxyx(stdscr,rows1,cols1);
		makeForm();
	      }//End if option = Open
	    
	    
	    if(false)//If option was save
	      {}
	    if(false)//If option was saveAs
	      {}
	    if(false)//If option was Exit
	      {}
	    // break;
	  }//End switch(ch) which looks for up down or enter of menu
	}//Ends While loop which sets ch
	
}//end showMenu()



int main(int argc, char *argv[])
{
	//Declaration of scrollPad,menu,menuWin,popup(used for open and saveAs
	string line;
	WINDOW *pad;

	int pos{0};
	int ch{0};
	int padKey{0};
	int c;
	char buffer[1024];
	int rows,cols,fd,size;
	int tX,tY,bX,bY;
	ifstream file;
	initscr();
	getmaxyx(stdscr,rows,cols);
	tX = rows/2 - (rows-3.5)/2;
	tY = cols/2 - (cols-1)/2;
	bX = rows + tX;
	bY = cols + tY;
	pad = newpad(rows+10000,cols);
	keypad(pad,TRUE);

	printw("F1:Menu");
	refresh();
	box(pad,0,0);
	
	
	prefresh(pad,0,0,3,2,rows-4,cols-4);
	if(argc==2)
	  {
	    file.open(argv[1]);
	    while(getline(file,line))
	      {
		wprintw(pad,"%s\n",line.c_str());
	      }
	    file.close();
	    prefresh(pad,0,0,3,2,rows-4,cols-4);
	    //prefresh(pad,0,0,tX,tY,bX,bY);

	  }
	//While + Switch Statement which listens for direction keys and F1.
	while(padKey = wgetch(pad))
	{
		switch(padKey)
		{
			//Arrow keys function as cursor movements
			//case KEY_LEFT:
			// break;
		case KEY_UP://check if up arrow is pressed
		  if(pos >= 0){
		    pos--;
		  }
		  		  
		  break;

		case KEY_DOWN://check if down arrows are pressed
		  pos++;
		  
		  break;

	        case KEY_F(1):
		  showMenu();
		  break;
		}//End Switch for Scroll Pad
		prefresh(pad, pos, 0, 3, 2, rows-4, cols-4);//refresh pad
	}//End While For Scroll Pad


	return 0;
}
