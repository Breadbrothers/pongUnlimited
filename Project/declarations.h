//Declaration for display-related functions used outside game
void display_image(int x, const uint8_t* data);
void display_init(void);
void display_string(int line, char* s);
void display_update(void);
void display_debug(volatile int* const addr);
uint8_t spi_send_recv(uint8_t data);
void menu(void);
void init(void);
void quicksleep(int cyc);
//Declaration for other functions


//Declare bitmap array containing font
extern const uint8_t const font[128*8];

//Declare bitmap array containing icon
extern const uint8_t const icon[128];

//Declare bitmap array containing startscreen

extern uint8_t screenbuffer[512];

extern uint8_t screen[512];

//Declare text buffer for display
extern char textbuffer[4][16];

extern const uint8_t  const bread_icon[128];
//Declare speed of the game for difficulty
extern int modes;

extern int sw;


//Declare variable to check winner of the game
extern int winner;

//Declare get buttons, get switches and enable interrupt
int getbtns(void);
int getsw(void);
void enable_interrupt(void);
void delay(int ms);
