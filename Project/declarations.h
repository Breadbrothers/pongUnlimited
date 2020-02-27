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
extern const uint8_t const startscreen[512];
extern uint8_t screenbuffer[512];

//Declare bitmap array containing the game
extern const uint8_t gamescreen[512];

//Declare text buffer for display
extern char textbuffer[4][16];

//Declare speed of the game for difficulty
extern int modes;

//Declare get buttons, get switches and enable interrupt
int getbtns(void);
int getsw(void);
void enable_interrupt(void);
