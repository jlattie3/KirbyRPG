#include "graphics.h"

#include "globals.h"

#define YELLOW 0xFFFF00
#define BROWN  0xD2691E
#define DIRT   0x3F2A14
#define PINK   0xF76E9C
#define WHITE  0xFFFFFF
#define ORANGE 0xFF3300

////////////////////////////////////////////////////////////
//items on map
///////////////////////////////////////////////////////////
void draw_player(int u, int v, int key)
{
    uLCD.line(u,v+10,u+5,v+10, DGREY);
    uLCD.line(u+7,v+10,u+11,v+10, DGREY);
    uLCD.pixel(u,v+9, DGREY);
    uLCD.pixel(u+10,v+9, DGREY);
    uLCD.line(u+5,v+9,u+7,v+9, DGREY);
    uLCD.pixel(u+1,v+8, DGREY);
    uLCD.line(u+3,v+8,u+5,v+8, DGREY);
    uLCD.line(u+7,v+8,u+10,v+8, DGREY);
    uLCD.line(u+1,v+7,u+3,v+7, DGREY);
    uLCD.pixel(u+9,v+7, DGREY);
    uLCD.line(u,v+3,u,v+7, DGREY);
    uLCD.line(u+10,v+3,u+10,v+7, DGREY);
    uLCD.pixel(u+3,v+6, DGREY);
    uLCD.pixel(u+8,v+6, DGREY);
    uLCD.pixel(u+1,v+2, DGREY);
    uLCD.pixel(u+9,v+2, DGREY);
    uLCD.pixel(u+2,v+1, DGREY);
    uLCD.line(u+7,v+1,u+9,v+1, DGREY);
    uLCD.line(u+3,v,u+7,v, DGREY);
    // kirby pink
    uLCD.line(u+1,v+9,u+5,v+9, PINK);
    uLCD.line(u+7,v+9,u+10,v+9, PINK);
    uLCD.pixel(u+2,v+8, PINK);
    uLCD.line(u+5,v+8,u+7,v+8, PINK);
    uLCD.line(u+3,v+7,u+9,v+7, PINK);
    uLCD.line(u+1,v+6,u+3,v+6, PINK);
    uLCD.line(u+4,v+6,u+8,v+6, PINK);
    uLCD.pixel(u+9,v+6, PINK);
    uLCD.line(u+1,v+5,u+10,v+5, PINK);
    uLCD.line(u+1,v+4,u+10,v+4, PINK);
    uLCD.line(u+1,v+3,u+10,v+3, PINK);
    uLCD.line(u+2,v+2,u+9,v+2, PINK);
    uLCD.line(u+3,v+1,u+7,v+1, PINK);
    // mouth anmd eyes
    uLCD.pixel(u+6,v+6, BLACK);
    uLCD.line(u+5,v+3,u+5,v+5, BLACK);
    uLCD.line(u+7,v+3,u+7,v+5, BLACK);
}

void draw_player_orb(int u, int v, int key)
{
    uLCD.line(u,v+10,u+5,v+10, DGREY);
    uLCD.line(u+7,v+10,u+11,v+10, DGREY);
    uLCD.pixel(u,v+9, DGREY);
    uLCD.pixel(u+10,v+9, DGREY);
    uLCD.line(u+5,v+9,u+7,v+9, DGREY);
    uLCD.pixel(u+1,v+8, DGREY);
    uLCD.line(u+3,v+8,u+5,v+8, DGREY);
    uLCD.line(u+7,v+8,u+10,v+8, DGREY);
    uLCD.line(u+1,v+7,u+3,v+7, DGREY);
    uLCD.pixel(u+9,v+7, DGREY);
    uLCD.line(u,v+3,u,v+7, DGREY);
    uLCD.line(u+10,v+3,u+10,v+7, DGREY);
    uLCD.pixel(u+3,v+6, DGREY);
    uLCD.pixel(u+8,v+6, DGREY);
    uLCD.pixel(u+1,v+2, DGREY);
    uLCD.pixel(u+9,v+2, DGREY);
    uLCD.pixel(u+2,v+1, DGREY);
    uLCD.line(u+7,v+1,u+9,v+1, DGREY);
    uLCD.line(u+3,v,u+7,v, DGREY);
    // kirby pink
    uLCD.line(u+1,v+9,u+5,v+9, YELLOW);
    uLCD.line(u+7,v+9,u+10,v+9, YELLOW);
    uLCD.pixel(u+2,v+8, YELLOW);
    uLCD.line(u+5,v+8,u+7,v+8, YELLOW);
    uLCD.line(u+3,v+7,u+9,v+7, YELLOW);
    uLCD.line(u+1,v+6,u+3,v+6, YELLOW);
    uLCD.line(u+4,v+6,u+8,v+6, YELLOW);
    uLCD.pixel(u+9,v+6, YELLOW);
    uLCD.line(u+1,v+5,u+10,v+5, YELLOW);
    uLCD.line(u+1,v+4,u+10,v+4, YELLOW);
    uLCD.line(u+1,v+3,u+10,v+3, YELLOW);
    uLCD.line(u+2,v+2,u+9,v+2, YELLOW);
    uLCD.line(u+3,v+1,u+7,v+1, YELLOW);
    // mouth anmd eyes
    uLCD.pixel(u+6,v+6, BLACK);
    uLCD.line(u+5,v+3,u+5,v+5, BLACK);
    uLCD.line(u+7,v+3,u+7,v+5, BLACK);
}


void draw_img(int u, int v, const char* img)
{
    int colors[11*11];
    for (int i = 0; i < 11*11; i++)
    {
        if (img[i] == 'R') colors[i] = RED;
        else if (img[i] == 'Y') colors[i] = YELLOW;
        else if (img[i] == 'G') colors[i] = GREEN;
        else if (img[i] == 'D') colors[i] = BROWN;
        else if (img[i] == '5') colors[i] = LGREY;
        else if (img[i] == '3') colors[i] = DGREY;
        else colors[i] = BLACK;
    }
    uLCD.BLIT(u, v, 11, 11, colors);
    wait_us(250); // Recovery time!
}

void draw_nothing(int u, int v)
{
    // Fill a tile with blackness
    uLCD.filled_rectangle(u, v, u+10, v+10, BLACK);
}

void draw_wall(int u, int v)
{
    uLCD.line(u,v,u+10,v, DGREY);
    uLCD.line(u,v+10,u+10,v+10, DGREY);
    uLCD.line(u,v,u,v+10, DGREY);
    uLCD.line(u+10,v,u+10,v+10, DGREY);
    uLCD.filled_rectangle(u+1,v+1,u+9,v+9, LGREY);
}

void draw_water(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, BLUE);
}

void draw_dirt(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, DIRT);
}

void draw_npc(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, YELLOW);
}

void draw_npc2(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, ORANGE);
}

void draw_npc3(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, GREEN);
}

void draw_npc4(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, WHITE);
}

void draw_npc5(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, WHITE);
}

void draw_shoes(int u, int v)
{
    uLCD.filled_rectangle(u+5, v+5, u+10, v+10, BROWN);
}

void draw_plant(int u, int v)
{
    //uLCD.filled_rectangle(u, v, u+10, v+10, GREEN);
    // trunk
    uLCD.line(u+4,v+10,u+7,v+10, BROWN);
    uLCD.line(u+4,v+9,u+7,v+9, BROWN);
    uLCD.line(u+4,v+8,u+7,v+8, BROWN);
    // fir
    uLCD.line(u,v+7,u+11,v+7, GREEN);
    uLCD.line(u,v+6,u+11,v+6, GREEN);
    uLCD.line(u+1,v+5,u+10,v+5, GREEN);
    uLCD.line(u+2,v+4,u+9,v+4, GREEN);
    uLCD.line(u+3,v+3,u+8,v+3, GREEN);
    uLCD.line(u+4,v+2,u+7,v+2, GREEN);
    uLCD.pixel(u+5,v+1, GREEN);
}

void draw_door(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, BLACK);
    uLCD.filled_rectangle(u, v+4, u+10, v+7, BROWN);
}

void draw_heart(int u, int v)
{
    //border
    uLCD.line(u+2, v, u+4, v, BLACK);
    uLCD.line(u+7, v, u+9, v, BLACK);
    uLCD.pixel(u+1,v+1,BLACK);
    uLCD.pixel(u+4,v+1,BLACK);
    uLCD.pixel(u+6,v+1,BLACK);
    uLCD.pixel(u+9,v+1,BLACK);
    uLCD.pixel(u+5,v+2,BLACK);
    uLCD.line(u,v+2,u,v+6,BLACK);
    uLCD.line(u+10,v+2,u+10,v+6,BLACK);
    uLCD.pixel(u+1,v+6,BLACK);
    uLCD.pixel(u+2,v+7,BLACK);
    uLCD.pixel(u+3,v+8,BLACK);
    uLCD.pixel(u+4,v+9,BLACK);
    uLCD.pixel(u+5,v+10,BLACK);
    uLCD.pixel(u+6,v+9,BLACK);
    uLCD.pixel(u+7,v+8,BLACK); 
    uLCD.pixel(u+8,v+7,BLACK);
    uLCD.pixel(u+9,v+6,BLACK);
    //fill
    uLCD.pixel(u+5,v+9,RED);
    uLCD.line(u+4,v+8, u+7,v+8, RED);
    uLCD.line(u+3,v+7, u+8,v+7, RED);
    uLCD.line(u+2,v+6, u+9,v+6, RED);
    uLCD.line(u+1,v+5, u+10,v+5, RED);
    uLCD.line(u+1,v+4, u+10,v+4, RED);
    uLCD.line(u+1,v+3, u+10,v+3, RED);
    uLCD.line(u+1,v+2, u+5,v+2, RED);
    uLCD.line(u+6,v+2, u+10,v+2, RED);
    uLCD.line(u+2,v+1, u+4,v+1, RED);
    uLCD.line(u+7,v+1, u+9,v+1, RED);
}

void draw_empty_heart(int u, int v)
{
    //border
    uLCD.line(u+2, v, u+4, v, BLACK);
    uLCD.line(u+7, v, u+9, v, BLACK);
    uLCD.pixel(u+1,v+1,BLACK);
    uLCD.pixel(u+4,v+1,BLACK);
    uLCD.pixel(u+6,v+1,BLACK);
    uLCD.pixel(u+9,v+1,BLACK);
    uLCD.pixel(u+5,v+2,BLACK);
    uLCD.line(u,v+2,u,v+6,BLACK);
    uLCD.line(u+10,v+2,u+10,v+6,BLACK);
    uLCD.pixel(u+1,v+6,BLACK);
    uLCD.pixel(u+2,v+7,BLACK);
    uLCD.pixel(u+3,v+8,BLACK);
    uLCD.pixel(u+4,v+9,BLACK);
    uLCD.pixel(u+5,v+10,BLACK);
    uLCD.pixel(u+6,v+9,BLACK);
    uLCD.pixel(u+7,v+8,BLACK); 
    uLCD.pixel(u+8,v+7,BLACK);
    uLCD.pixel(u+9,v+6,BLACK);
    //fill
    uLCD.pixel(u+5,v+9,WHITE);
    uLCD.line(u+4,v+8, u+7,v+8, WHITE);
    uLCD.line(u+3,v+7, u+8,v+7, WHITE);
    uLCD.line(u+2,v+6, u+9,v+6, WHITE);
    uLCD.line(u+1,v+5, u+10,v+5, WHITE);
    uLCD.line(u+1,v+4, u+10,v+4, WHITE);
    uLCD.line(u+1,v+3, u+10,v+3, WHITE);
    uLCD.line(u+1,v+2, u+5,v+2, WHITE);
    uLCD.line(u+6,v+2, u+10,v+2, WHITE);
    uLCD.line(u+2,v+1, u+4,v+1, WHITE);
    uLCD.line(u+7,v+1, u+9,v+1, WHITE);
}

void draw_health_bar(int health) {
    switch (health) {
        case 3:
            draw_heart(116,8);
            draw_heart(104,8);
            draw_heart(92,8);
            break;
        case 2:
            draw_heart(116,8);
            draw_heart(104,8);
            draw_empty_heart(92,8);
            break;
        case 1:
            draw_heart(116,8);
            draw_empty_heart(104,8);
            draw_empty_heart(92,8);
            break;
    }
}

void draw_life_bar(int lives) {
    uLCD.locate(8,1);
    uLCD.color(BLACK);
    uLCD.textbackground_color(WHITE);
    uLCD.set_font(FONT_7X8);
    uLCD.text_mode(OPAQUE);
    uLCD.printf("L:%d", lives);
}

void draw_trap(int u, int v) {
    uLCD.filled_circle(u+5,v+6,4,DGREY);
    uLCD.pixel(u+5,v+2,WHITE);
    uLCD.pixel(u+5,v+1,WHITE);
    uLCD.line(u+5,v,u+7,v,WHITE);
    uLCD.pixel(u+7,v,ORANGE);
    uLCD.pixel(u+6,v,ORANGE);
}

void draw_key(int u, int v) {
    uLCD.circle(u+5,v+7,3,YELLOW);
    uLCD.circle(u+5,v+7,2,YELLOW);
    uLCD.line(u+5,v,u+5,v+4,YELLOW);
    uLCD.pixel(u+6,v,YELLOW);
    uLCD.pixel(u+7,v,YELLOW);
    uLCD.pixel(u+6,v+2,YELLOW);
}

void draw_orb(int u, int v) {
    uLCD.circle(u+5,v+5,4,YELLOW);
    uLCD.pixel(u+3,v+4,WHITE);
    uLCD.pixel(u+4,v+4,WHITE);
    uLCD.pixel(u+4,v+3,WHITE);
}

void draw_sword(int u, int v) {
    uLCD.filled_rectangle(u+5,v+8,u+6,v+10,BROWN);
    uLCD.line(u+3,v+7,u+9,v+7,BROWN);
    uLCD.line(u+5,v,u+5,v+7,WHITE);
    uLCD.line(u+6,v+1,u+6,v+7,WHITE);
}

void draw_food(int u, int v) {
    uLCD.filled_circle(u+5,v+6,4,BROWN);
}

void draw_monster(int u, int v) {
    uLCD.triangle(u, v+10, u+10, v+10, u+5, v, DGREY);
}
//////////////////////////////////////////////////////////////////////


void draw_upper_status()
{
    // Draw bottom border of status bar
    uLCD.filled_rectangle(0,9,127,18,WHITE);
}

void draw_lower_status()
{
    // Draw top border of status bar
    uLCD.line(0, 118, 127, 118, GREEN);
    // Add other status info drawing code here
}

void draw_coord(int x, int y) {
    uLCD.locate(0,1);
    uLCD.color(BLACK);
    uLCD.textbackground_color(WHITE);
    uLCD.set_font(FONT_7X8);
    uLCD.text_mode(OPAQUE);
    uLCD.printf("[%D,%D]",x,y);
}
///////////////////////////////////////////////////////
// text and other stuff
/////////////////////////////////////////////////////
void draw_start() {
    uLCD.background_color(PINK);
    uLCD.cls();
    uLCD.color(BLACK);
    uLCD.textbackground_color(PINK);
    uLCD.locate(5,5);
    uLCD.printf("Kirby's");
    uLCD.locate(5,6);
    uLCD.printf("Grand");
    uLCD.locate(5,7);
    uLCD.printf("Adventure");
    uLCD.line(0, 70, 127, 70, BLACK);
    
    uLCD.locate(3,11);
    uLCD.printf("Press Action ");
    uLCD.locate(5,12);
    uLCD.printf("To Begin");
    
}
///////////////////////////////////////////////////////
//NPC1
//////////////////////////////////////////////////////
void draw_intro() {
    uLCD.filled_rectangle(0,109,127,130,BLACK);
    uLCD.filled_rectangle(2,111,125,128,WHITE);
    uLCD.locate(1,14);
    uLCD.color(BLACK);
    uLCD.textbackground_color(WHITE);
    uLCD.set_font_size(3, 3); 
    uLCD.set_font(FONT_7X8);
    uLCD.text_mode(OPAQUE);
    uLCD.printf("I have a ");
    uLCD.locate(1,15);
    uLCD.printf("key for you!");
}

void draw_intro1() {
    uLCD.filled_rectangle(0,98,127,130,BLACK);
    uLCD.filled_rectangle(2,100,125,128,WHITE);
    uLCD.locate(1,13);
    uLCD.color(BLACK);
    uLCD.textbackground_color(WHITE);
    uLCD.set_font_size(3, 3); 
    uLCD.set_font(FONT_7X8);
    uLCD.text_mode(OPAQUE);
    uLCD.printf("First, you must");
    uLCD.locate(1,14);
    uLCD.printf("arm yourself!");
    uLCD.locate(1,15);
    uLCD.printf("Get my sword.");
}

void draw_repeat() {
    uLCD.filled_rectangle(0,109,127,130,BLACK);
    uLCD.filled_rectangle(2,111,125,128,WHITE);
    uLCD.locate(1,14);
    uLCD.color(BLACK);
    uLCD.textbackground_color(WHITE);
    uLCD.set_font_size(3, 3); 
    uLCD.set_font(FONT_7X8);
    uLCD.text_mode(OPAQUE);
    uLCD.printf("Get my sword!");
}

void draw_complete() {
    uLCD.filled_rectangle(0,98,127,130,BLACK);
    uLCD.filled_rectangle(2,100,125,128,WHITE);
    uLCD.locate(1,13);
    uLCD.color(BLACK);
    uLCD.textbackground_color(WHITE);
    uLCD.set_font_size(3, 3); 
    uLCD.set_font(FONT_7X8);
    uLCD.text_mode(OPAQUE);
    uLCD.printf("Take this key.");
    uLCD.locate(1,14);
    uLCD.printf("Travel to the");
    uLCD.locate(1,15);
    uLCD.printf("old bridge!");
}

void draw_complete1() {
    uLCD.filled_rectangle(0,98,127,130,BLACK);
    uLCD.filled_rectangle(2,100,125,128,WHITE);
    uLCD.locate(1,13);
    uLCD.color(BLACK);
    uLCD.textbackground_color(WHITE);
    uLCD.set_font_size(3, 3); 
    uLCD.set_font(FONT_7X8);
    uLCD.text_mode(OPAQUE);
    uLCD.printf("Now, fulfill");
    uLCD.locate(1,14);
    uLCD.printf("your destiny!");
    uLCD.locate(1,15);
    uLCD.printf("Good Luck!");
}
///////////////////////////////////////////////////////
//NPC2
//////////////////////////////////////////////////////
void draw_intro2() {
    uLCD.filled_rectangle(0,109,127,130,BLACK);
    uLCD.filled_rectangle(2,111,125,128,WHITE);
    uLCD.locate(1,14);
    uLCD.color(BLACK);
    uLCD.textbackground_color(WHITE);
    uLCD.set_font_size(3, 3); 
    uLCD.set_font(FONT_7X8);
    uLCD.text_mode(OPAQUE);
    uLCD.printf("Kirby!");
    uLCD.locate(1,15);
    uLCD.printf("You're awake!");
}

void draw_intro21() {
    uLCD.filled_rectangle(0,109,127,130,BLACK);
    uLCD.filled_rectangle(2,111,125,128,WHITE);
    uLCD.locate(1,14);
    uLCD.color(BLACK);
    uLCD.textbackground_color(WHITE);
    uLCD.set_font_size(3, 3); 
    uLCD.set_font(FONT_7X8);
    uLCD.text_mode(OPAQUE);
    uLCD.printf("I'm hungry...");
    uLCD.locate(1,15);
    uLCD.printf("Find us food!");
}

void draw_no_food() {
    uLCD.filled_rectangle(0,109,127,130,BLACK);
    uLCD.filled_rectangle(2,111,125,128,WHITE);
    uLCD.locate(1,14);
    uLCD.color(BLACK);
    uLCD.textbackground_color(WHITE);
    uLCD.set_font_size(3, 3); 
    uLCD.set_font(FONT_7X8);
    uLCD.text_mode(OPAQUE);
    uLCD.printf("Look in the ");
    uLCD.locate(1,15);
    uLCD.printf("forest. DUH!");
}

void draw_has_food() {
    uLCD.filled_rectangle(0,109,127,130,BLACK);
    uLCD.filled_rectangle(2,111,125,128,WHITE);
    uLCD.locate(1,14);
    uLCD.color(BLACK);
    uLCD.textbackground_color(WHITE);
    uLCD.set_font_size(3, 3); 
    uLCD.set_font(FONT_7X8);
    uLCD.text_mode(OPAQUE);
    uLCD.printf("Yummy! Now go");
    uLCD.locate(1,15);
    uLCD.printf("talk to dad!");
}

void draw_has_food2() {
    uLCD.filled_rectangle(0,109,127,130,BLACK);
    uLCD.filled_rectangle(2,111,125,128,WHITE);
    uLCD.locate(1,14);
    uLCD.color(BLACK);
    uLCD.textbackground_color(WHITE);
    uLCD.set_font_size(3, 3); 
    uLCD.set_font(FONT_7X8);
    uLCD.text_mode(OPAQUE);
    uLCD.printf("He lives to");
    uLCD.locate(1,15);
    uLCD.printf("the East!");
}
//////////////////////////////////////////////
// NPC3
////////////////////////////////////////////
void draw_no_kills() {
    uLCD.filled_rectangle(0,109,127,130,BLACK);
    uLCD.filled_rectangle(2,111,125,128,WHITE);
    uLCD.locate(1,14);
    uLCD.color(BLACK);
    uLCD.textbackground_color(WHITE);
    uLCD.set_font_size(3, 3); 
    uLCD.set_font(FONT_7X8);
    uLCD.text_mode(OPAQUE);
    uLCD.printf("Help! Kill the");
    uLCD.locate(1,15);
    uLCD.printf("3 monsters!");
}

void draw_all_kills() {
    uLCD.filled_rectangle(0,109,127,130,BLACK);
    uLCD.filled_rectangle(2,111,125,128,WHITE);
    uLCD.locate(1,14);
    uLCD.color(BLACK);
    uLCD.textbackground_color(WHITE);
    uLCD.set_font_size(3, 3); 
    uLCD.set_font(FONT_7X8);
    uLCD.text_mode(OPAQUE);
    uLCD.printf("Thank you!");
    uLCD.locate(1,15);
    uLCD.printf("I am safe now.");
}
/////////////////////////////////////////////////////////
// door stuff
///////////////////////////////////////////////////////
void draw_no_unlock() {
    uLCD.filled_rectangle(0,109,127,130,BLACK);
    uLCD.filled_rectangle(2,111,125,128,WHITE);
    uLCD.locate(1,14);
    uLCD.color(BLACK);
    uLCD.textbackground_color(WHITE);
    uLCD.set_font_size(3, 3); 
    uLCD.set_font(FONT_7X8);
    uLCD.text_mode(OPAQUE);
    uLCD.printf("You seem to ");
    uLCD.locate(1,15);
    uLCD.printf("need a key.");
}

void draw_unlock() {
    uLCD.filled_rectangle(0,109,127,130,BLACK);
    uLCD.filled_rectangle(2,111,125,128,WHITE);
    uLCD.locate(1,14);
    uLCD.color(BLACK);
    uLCD.textbackground_color(WHITE);
    uLCD.set_font_size(3, 3); 
    uLCD.set_font(FONT_7X8);
    uLCD.text_mode(OPAQUE);
    uLCD.printf("Unlocking the ");
    uLCD.locate(1,15);
    uLCD.printf("door!");
}
////////////////// 
// items stuff
void draw_shoes_text() {
    uLCD.filled_rectangle(0,109,127,130,BLACK);
    uLCD.filled_rectangle(2,111,125,128,WHITE);
    uLCD.locate(1,14);
    uLCD.color(BLACK);
    uLCD.textbackground_color(WHITE);
    uLCD.set_font_size(3, 3); 
    uLCD.set_font(FONT_7X8);
    uLCD.text_mode(OPAQUE);
    uLCD.printf("You see");
    uLCD.locate(1,15);
    uLCD.printf("running shoes!");
}

void draw_food_text() {
    uLCD.filled_rectangle(0,109,127,130,BLACK);
    uLCD.filled_rectangle(2,111,125,128,WHITE);
    uLCD.locate(1,14);
    uLCD.color(BLACK);
    uLCD.textbackground_color(WHITE);
    uLCD.set_font_size(3, 3); 
    uLCD.set_font(FONT_7X8);
    uLCD.text_mode(OPAQUE);
    uLCD.printf("You found");
    uLCD.locate(1,15);
    uLCD.printf("some food!");
}

void draw_sword_text() {
    uLCD.filled_rectangle(0,109,127,130,BLACK);
    uLCD.filled_rectangle(2,111,125,128,WHITE);
    uLCD.locate(1,14);
    uLCD.color(BLACK);
    uLCD.textbackground_color(WHITE);
    uLCD.set_font_size(3, 3); 
    uLCD.set_font(FONT_7X8);
    uLCD.text_mode(OPAQUE);
    uLCD.printf("Look.. its a");
    uLCD.locate(1,15);
    uLCD.printf("sword...");
}

void draw_monster_text() {
    uLCD.filled_rectangle(0,109,127,130,BLACK);
    uLCD.filled_rectangle(2,111,125,128,WHITE);
    uLCD.locate(1,14);
    uLCD.color(BLACK);
    uLCD.textbackground_color(WHITE);
    uLCD.set_font_size(3, 3); 
    uLCD.set_font(FONT_7X8);
    uLCD.text_mode(OPAQUE);
    uLCD.printf("You struck");
    uLCD.locate(1,15);
    uLCD.printf("the monster!");
}
/////////////////////////////////////////////////
// secret room stroy 
/////////////////////////////////////////////////
void secret_room_text() {
    uLCD.filled_rectangle(0,109,127,130,BLACK);
    uLCD.filled_rectangle(2,111,125,128,WHITE);
    uLCD.locate(1,14);
    uLCD.color(BLACK);
    uLCD.textbackground_color(WHITE);
    uLCD.set_font_size(3, 3); 
    uLCD.set_font(FONT_7X8);
    uLCD.text_mode(OPAQUE);
    uLCD.printf("You found a");
    uLCD.locate(1,15);
    uLCD.printf("secret room!");
}

void npc4_text() {
    uLCD.filled_rectangle(0,109,127,130,BLACK);
    uLCD.filled_rectangle(2,111,125,128,WHITE);
    uLCD.locate(1,14);
    uLCD.color(BLACK);
    uLCD.textbackground_color(WHITE);
    uLCD.set_font_size(3, 3); 
    uLCD.set_font(FONT_7X8);
    uLCD.text_mode(OPAQUE);
    uLCD.printf("Welcome Kirby!");
    uLCD.locate(1,15);
    uLCD.printf("Grab the orb!");
}

void npc5_text() {
    uLCD.filled_rectangle(0,109,127,130,BLACK);
    uLCD.filled_rectangle(2,111,125,128,WHITE);
    uLCD.locate(1,14);
    uLCD.color(BLACK);
    uLCD.textbackground_color(WHITE);
    uLCD.set_font_size(3, 3); 
    uLCD.set_font(FONT_7X8);
    uLCD.text_mode(OPAQUE);
    uLCD.printf("Welcome Kirby!");
    uLCD.locate(1,15);
    uLCD.printf("Grab the orb!");
}

void npc4_text1() {
    uLCD.filled_rectangle(0,109,127,130,BLACK);
    uLCD.filled_rectangle(2,111,125,128,WHITE);
    uLCD.locate(1,14);
    uLCD.color(BLACK);
    uLCD.textbackground_color(WHITE);
    uLCD.set_font_size(3, 3); 
    uLCD.set_font(FONT_7X8);
    uLCD.text_mode(OPAQUE);
    uLCD.printf("You are now");
    uLCD.locate(1,15);
    uLCD.printf("invicible!");
}

void npc5_text1() {
    uLCD.filled_rectangle(0,109,127,130,BLACK);
    uLCD.filled_rectangle(2,111,125,128,WHITE);
    uLCD.locate(1,14);
    uLCD.color(BLACK);
    uLCD.textbackground_color(WHITE);
    uLCD.set_font_size(3, 3); 
    uLCD.set_font(FONT_7X8);
    uLCD.text_mode(OPAQUE);
    uLCD.printf("You can now walk");
    uLCD.locate(1,15);
    uLCD.printf("through objects!");
}

void npc5_text2() {
    uLCD.filled_rectangle(0,109,127,130,BLACK);
    uLCD.filled_rectangle(2,111,125,128,WHITE);
    uLCD.locate(1,14);
    uLCD.color(BLACK);
    uLCD.textbackground_color(WHITE);
    uLCD.set_font_size(3, 3); 
    uLCD.set_font(FONT_7X8);
    uLCD.text_mode(OPAQUE);
    uLCD.printf("Go tell your dad");
    uLCD.locate(1,15);
    uLCD.printf("what you found!");
}

void draw_orb_text() {
    uLCD.filled_rectangle(0,109,127,130,BLACK);
    uLCD.filled_rectangle(2,111,125,128,WHITE);
    uLCD.locate(1,14);
    uLCD.color(BLACK);
    uLCD.textbackground_color(WHITE);
    uLCD.set_font_size(3, 3); 
    uLCD.set_font(FONT_7X8);
    uLCD.text_mode(OPAQUE);
    uLCD.printf("You feel a");
    uLCD.locate(1,15);
    uLCD.printf("strange energy.");
}

void draw_done() {
    uLCD.filled_rectangle(0,98,127,130,BLACK);
    uLCD.filled_rectangle(2,100,125,128,WHITE);
    uLCD.locate(1,13);
    uLCD.color(BLACK);
    uLCD.textbackground_color(WHITE);
    uLCD.set_font_size(3, 3); 
    uLCD.set_font(FONT_7X8);
    uLCD.text_mode(OPAQUE);
    uLCD.printf("You fulfilled");
    uLCD.locate(1,14);
    uLCD.printf("your destiny!");
    uLCD.locate(1,15);
    uLCD.printf("Go rest up!");
}

void draw_done2() {
    uLCD.filled_rectangle(0,98,127,130,BLACK);
    uLCD.filled_rectangle(2,100,125,128,WHITE);
    uLCD.locate(1,13);
    uLCD.color(BLACK);
    uLCD.textbackground_color(WHITE);
    uLCD.set_font_size(3, 3); 
    uLCD.set_font(FONT_7X8);
    uLCD.text_mode(OPAQUE);
    uLCD.printf("Woah you are");
    uLCD.locate(1,14);
    uLCD.printf("glowing! Get");
    uLCD.locate(1,15);
    uLCD.printf("some rest!");
}

//////////////////////////////////
// inventory
//////////////////////////////////
void draw_inventory(int has_food, int has_sword, int has_key, int has_shoes, int has_orb) {
    uLCD.filled_rectangle(0,98,127,130,BLACK);
    uLCD.filled_rectangle(2,100,125,128,LGREY);
    uLCD.textbackground_color(LGREY);
    uLCD.locate(5,13);
    uLCD.printf("Inventory");
    if (has_food == 2) {
        draw_food(11, 113);
    }
    if (has_sword == 2) {
        draw_sword(33, 113);
    }
    if (has_key == 1) {
        draw_key(55, 113);
    }
    if (has_shoes == 2) {
        draw_shoes(77, 113);
    }
    if (has_orb == 1) {
        draw_orb(99, 113);
    }
}

/////////////////////////////////////
void draw_game_over() {
    uLCD.background_color(PINK);
    uLCD.cls();
    uLCD.color(BLACK);
    uLCD.textbackground_color(PINK);
    uLCD.locate(5,7);
    uLCD.printf("GAME OVER");
    uLCD.locate(5,8);
    uLCD.printf("You died...");
    uLCD.locate(5,9);
    uLCD.printf("GGEZ");
}

void draw_win_game() {
    uLCD.background_color(PINK);
    uLCD.cls();
    uLCD.color(BLACK);
    uLCD.textbackground_color(PINK);
    uLCD.locate(5,7);
    uLCD.printf("GAME OVER");
    uLCD.locate(5,8);
    uLCD.printf("You won!");
    uLCD.locate(5,9);
    uLCD.printf("GGEZ");
}

void draw_clear() {
    uLCD.cls();
    return;
}

void draw_border()
{
    uLCD.filled_rectangle(0,     9, 127,  14, WHITE); // Top
    uLCD.filled_rectangle(0,    13,   2, 114, WHITE); // Left
    uLCD.filled_rectangle(0,   114, 127, 117, WHITE); // Bottom
    uLCD.filled_rectangle(124,  14, 127, 117, WHITE); // Right
}


