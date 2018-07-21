// Project includes
#include "globals.h"
#include "hardware.h"
#include "map.h"
#include "graphics.h"
#include "speech.h"

// Functions in this file
int get_action (GameInputs inputs);
int update_game (int action);
void draw_game (int init);
void init_main_map ();
void npc1_interaction(int has_key);
void npc2_interaction(int has_key);
void npc3_interaction(int has_key);
void npc4_interaction(int has_orb);
void npc5_interaction(int has_orb);
int delete_door(int has_key);
void init_start();
void game_over();
void wait_for_action1();
int monster_contact();
int main ();

static int GodMode = 0; // global god mode variable;
static int InText = 0;  // 1 means in speech mode
static int Start = 1;
static int Health = 3;
static int Lives = 3;
static int Shoes = 0;
static int CheckPoint = 0;
static int Kills = 0;
static int Secret = 0;
static int Win = 0;
static int M1 = 1;
static int M2 = 1;
static int M3 = 1;
//static int HealthPrev = 3;
/**
 * The main game state. Must include Player locations and previous locations for
 * drawing to work properly. Other items can be added as needed.
 */
struct {
    int x,y;    // Current locations
    int px, py; // Previous locations
    int has_key;
    int has_food;
    int has_sword;
    int has_shoes;
    int has_orb;
} Player;

/**
 * Given the game inputs, determine what kind of update needs to happen.
 * Possbile return values are defined below.
 */
#define NO_ACTION 0
#define ACTION_BUTTON 1
#define MENU_BUTTON 2
#define GO_LEFT 3
#define GO_RIGHT 4
#define GO_UP 5
#define GO_DOWN 6
#define GOD_MODE 7
#define END_GOD_MODE 8
#define WIN         9
int get_action(GameInputs inputs)
{
    int returnVal = 0;
    if (inputs.b4 == 0) {
        if (GodMode == 1) {
            speaker = 0.1;
            speaker.period(1.0/500.0);
            wait(.1);
            speaker.period(1.0/300.0);
            wait(.1);
            speaker.period(1.0/100.0);
            wait(.1);
            speaker = 0.0;
            GodMode = 0;
        } else {
            speaker = 0.1;
            speaker.period(1.0/100.0);
            wait(.1);
            speaker.period(1.0/300.0);
            wait(.1);
            speaker.period(1.0/500.0);
            wait(.1);
            speaker = 0.0;
            GodMode = 1;
        }
        return GOD_MODE;
    }
    //accel inputs
    if (Shoes == 1 && GodMode == 0) {
        if (inputs.ay > 0.1) {
        return GO_UP;
        } else if (inputs.ay < -0.1) {
            return GO_DOWN;
        } else if (inputs.ax > 0.1) {
            return GO_RIGHT;
        } else if (inputs.ax < -0.1) {
            return GO_LEFT;
        }
    }
    if (inputs.ay > 0.25) {
        return GO_UP;
    } else if (inputs.ay < -0.25) {
        return GO_DOWN;
    } else if (inputs.ax > 0.25) {
        return GO_RIGHT;
    } else if (inputs.ax < -0.25) {
        return GO_LEFT;
    }
    
    if (Secret == 0 && Player.x == 29 && Player.y == 50) {
        Secret = 1;
        secret_room_text();
        wait_ms(400);
        wait_for_action1();
        draw_clear();
        init_main_map();
        draw_game(true);
    }
    
    //pc.printf("HAS KEY??? %d\n", Player.has_key);
    //pc.printf("IN TEXT?? %d \n", InText);
    //button 1 input
    if (inputs.b1 == 0) {
        
        if (Start == 1) {
            Start = 0;
            return ACTION_BUTTON;
        }
        if (InText == 0 && get_east(Player.x, Player.y)->type == NPC) {
            npc1_interaction(Player.has_sword);
        }
        if (InText == 0 && get_east(Player.x, Player.y)->type == NPC2) {
            npc2_interaction(Player.has_food);
        }
        if (InText == 0 && get_south(Player.x, Player.y)->type == NPC3) {
            npc3_interaction(Kills);
        }
        if (InText == 0 && get_north(Player.x, Player.y)->type == NPC4) {
            npc4_interaction(Player.has_orb);
        }
        if (InText == 0 && get_north(Player.x, Player.y)->type == NPC5) {
            npc5_interaction(Player.has_orb);
        }
        if (InText == 0 && get_south(Player.x, Player.y)->type == DOOR) {
            int doorVal = delete_door(Player.has_key);
        }
        if (InText == 0 && get_south(Player.x, Player.y)->type == MONSTER) {
            Kills = Kills + 1;
            if (Player.x == 19 && Player.y == 37) {
                M3 = 0;
            } else if (Player.x == 11 && Player.y == 41) {
                M1 = 0;   
            } else if (Player.x == 5 && Player.y == 49) {
                M2 = 0;   
            }
            get_south(Player.x, Player.y)->type = DIRT;
            get_south(Player.x, Player.y)->walkable = true;
            get_south(Player.x, Player.y)->draw = draw_nothing;
            draw_monster_text();
            wait_ms(400);
            wait_for_action1();
            draw_clear();
            init_main_map();
            draw_game(true);
        }
        if (InText == 0 && (Player.has_food < 2) && get_east(Player.x, Player.y)->type == FOOD) {
            Player.has_food = 2;
            get_east(Player.x, Player.y)->walkable = true;
            get_east(Player.x, Player.y)->draw = draw_nothing;
            draw_food_text();
            wait_ms(400);
            wait_for_action1();
            draw_clear();
            init_main_map();
            draw_game(true);
        }
        if (InText == 0 && (Player.has_sword < 2) && get_east(Player.x, Player.y)->type == SWORD) {
            Player.has_sword = 2;
            get_east(Player.x, Player.y)->walkable = true;
            get_east(Player.x, Player.y)->draw = draw_nothing;
            draw_sword_text();
            wait_ms(400);
            wait_for_action1();
            draw_clear();
            init_main_map();
            draw_game(true);
        }
        if (InText == 0 && Player.has_orb == 0 && get_north(Player.x, Player.y)->type == ORB) {
            Player.has_orb = 1;
            get_north(Player.x, Player.y)->walkable = true;
            get_north(Player.x, Player.y)->draw = draw_nothing;
            draw_orb_text();
            GodMode = 1;
            wait_ms(400);
            wait_for_action1();
            draw_clear();
            init_main_map();
            draw_game(true);
        }
        if (InText == 0 && Player.has_orb == 1 && get_north(Player.x, Player.y)->type == DIRT) {
            Win = 1;
        }
        return ACTION_BUTTON;  
    }
    //button 2 input
    if (inputs.b2 == 0) {
        return MENU_BUTTON;
    }
    //button 4 input
    
    if (inputs.b3 == 0) {
        GodMode = 0;
        button3.mode(PullUp);
        returnVal = END_GOD_MODE;
    }
    //if (inputs.b3 == 1) {
//        button3.mode(PullUp);
//        returnVal = END_GOD_MODE;
//    }
    return returnVal;
}

/**
 * Update the game state based on the user action. For example, if the user
 * requests GO_UP, then this function should determine if that is possible by
 * consulting the map, and update the Player position accordingly.
 * 
 * Return values are defined below. FULL_DRAW indicates that for this frame,
 * draw_game should not optimize drawing and should draw every tile, even if
 * the player has not moved.
 */
#define NO_RESULT 0
#define GAME_OVER 1
#define FULL_DRAW 2
#define LOSE_LIFE 3
int update_game(int action)
{
    // Save player previous location before updating
    pc.printf("ACTION IS %d\n", action);
    Player.px = Player.x;
    Player.py = Player.y;
    int returnVal;
    
    // Do different things based on the each action.
    // You can define functions like "go_up()" that get called for each case.
    switch(action)
    {
        case GOD_MODE:
            pc.printf("GODDDDD MODEEEEEE\n");
            break;
        case END_GOD_MODE:
            pc.printf("END GOD MODE\n");
            break;
        case GO_UP:
            if ((GodMode == 0) && (!get_north(Player.x, Player.y)-> walkable)) {
                if (get_north(Player.x, Player.y)->type == MONSTER) {
                    returnVal = monster_contact();
                    return returnVal;
                }
                speaker.period(1.0/100.0);
                speaker = 0.3;
                wait(.1);
                speaker = 0.0;
                break;
            }
            Player.y = Player.py - 1;
            Player.x = Player.px;
            break;
        case GO_LEFT:
            if ((GodMode == 0) && (!get_west(Player.x, Player.y)-> walkable)) {
                if (get_west(Player.x, Player.y)->type == MONSTER) {
                    returnVal = monster_contact();
                    return returnVal;
                }
                speaker.period(1.0/100.0);
                speaker = 0.3;
                wait(.2);
                speaker = 0.0;
                break;
            }
            Player.y = Player.py;
            Player.x = Player.px - 1;
            break;            
        case GO_DOWN:
            if ((GodMode == 0) && (!get_south(Player.x, Player.y)-> walkable)) {
                if (get_south(Player.x, Player.y)->type == MONSTER) {
                    returnVal = monster_contact();
                    return returnVal;
                }
                speaker.period(1.0/100.0);
                speaker = 0.3;
                wait(.2);
                speaker = 0.0;
                break;
            }
            Player.y = Player.py + 1;
            Player.x = Player.px;
            break;
        case GO_RIGHT:
            if ((GodMode == 0) && (!get_east(Player.x, Player.y)-> walkable)) {
                if (get_east(Player.x, Player.y)->type == MONSTER) {
                    returnVal = monster_contact();
                    return returnVal;
                }
                speaker.period(1.0/100.0);
                speaker = 0.3;
                wait(.2);
                speaker = 0.0;
                break;
            }
            Player.y = Player.py;
            Player.x = Player.px + 1;
            break;
        case ACTION_BUTTON: break;
        case MENU_BUTTON: 
            InText = 1;
            draw_inventory(Player.has_food, Player.has_sword, Player.has_key, Player.has_shoes, Player.has_orb);
            wait_ms(400);
            wait_for_action1();
            draw_clear();
            init_main_map();
            draw_game(true);
            InText = 0;
            break;
        default:        break;
    }
    if (GodMode == 0 && get_here(Player.x, Player.y)->type == TRAP) {
//        HealthPrev = Health;
        speaker.period(1.0/700.0);
        speaker = 0.3;
        wait(.05);
        speaker = 0.0;
        get_here(Player.x, Player.y)->draw = draw_nothing;
        get_here(Player.x, Player.y)->type = DIRT;
        Health = Health - 1;
        if (Health == 0) {
            Lives = Lives - 1;
            if (Lives == 0) {
                return GAME_OVER;
            } else {
                return LOSE_LIFE;
            }
        }
    }
    if (GodMode == 0 && Shoes == 0 && get_here(Player.x, Player.y)->type == SHOES) {
        Shoes = 1;
        Player.has_shoes = 2;
        get_here(Player.x, Player.y)->draw = draw_nothing;
        get_here(Player.x, Player.y)->type = DIRT;
        draw_shoes_text();
        wait_ms(400);
        wait_for_action1();
        Shoes = 1;
        draw_clear();
        init_main_map();
        draw_game(true);
    } 
    return NO_ACTION;
}

int monster_contact() {
    speaker.period(1.0/700.0);
    speaker = 0.3;
    wait(.05);
    speaker = 0.0;
    Health = Health - 1; 
    if (Health == 0) {
        Lives = Lives - 1;
        if (Lives == 0) {
            return GAME_OVER;
        } else {
            return LOSE_LIFE;
        }
    } 
    return NO_ACTION;
}

void wait_for_action1() {
    while(1) {
        Timer t; t.start();
        GameInputs inputs = read_inputs(); 
        int action = get_action(inputs);
        if (action == 1) {
            break;
        }
        t.stop();
        int dt = t.read_ms();
        if (dt < 100) wait_ms(100 - dt);
    }
}

void npc1_interaction(int has_sword) {
    InText = 1;
    if (Player.has_orb == 1) {
        draw_done();
        wait_ms(400);
        wait_for_action1();
        draw_clear();
        init_main_map();
        draw_game(true);
    } else if (has_sword == 0) {
        draw_intro();
        wait_ms(400);
        wait_for_action1();
        draw_intro1();
        wait_ms(400);
        wait_for_action1();
        Player.has_sword = 1;
        draw_clear();
        init_main_map();
        draw_game(true);
    } else if (Player.has_sword == 1) {
        draw_repeat();
        wait_ms(400);
        wait_for_action1();
        draw_clear();
        init_main_map();
        draw_game(true);
    } else if (Player.has_sword == 2) {
        draw_complete();
        wait_ms(400);
        wait_for_action1();
        draw_complete1();
        wait_ms(400);
        wait_for_action1();
        draw_clear();
        Player.has_key = 1;
        Player.has_sword = 2;
        init_main_map();
        draw_game(true);
        CheckPoint = 1;
    }
    InText = 0;
}

void npc2_interaction(int has_food) {
    InText = 1;
    if (Player.has_orb == 1) {
        draw_done2();
        wait_ms(400);
        wait_for_action1();
        draw_clear();
        init_main_map();
        draw_game(true);
    } else if (has_food == 0) {
        draw_intro2();
        wait_ms(400);
        wait_for_action1();
        draw_intro21();
        wait_ms(400);
        wait_for_action1();
        Player.has_food = 1;
        draw_clear();
        init_main_map();
        draw_game(true);
    } else if (has_food == 1) {
        draw_no_food();
        wait_ms(400);
        wait_for_action1();
        draw_clear();
        Player.has_food = 1;
        init_main_map();
        draw_game(true);
    } else if (has_food == 2) {
        draw_has_food();
        wait_ms(400);
        wait_for_action1();
        draw_has_food2();
        wait_ms(400);
        wait_for_action1();
        draw_clear();
        init_main_map();
        draw_game(true);
    }
    InText = 0;
}

void npc3_interaction(int kills) {
    InText = 1;
    if (kills == 0) {
        draw_no_kills();
        wait_ms(400);
        wait_for_action1();
        draw_clear();
        init_main_map();
        draw_game(true);
        CheckPoint = 2;
    } else if (kills >= 3) {
        draw_all_kills();
        wait_ms(400);
        wait_for_action1();
        draw_clear();
        init_main_map();
        draw_game(true);
    }
    InText = 0;
} 

void npc4_interaction(int has_orb) {
    InText = 1;
    if (has_orb == 0) {
        npc4_text();
        wait_ms(400);
        wait_for_action1();
        draw_clear();
        init_main_map();
        draw_game(true);
        CheckPoint = 3;
    } else if (has_orb == 1) {
        npc4_text1();
        wait_ms(400);
        wait_for_action1();
        draw_clear();
        init_main_map();
        draw_game(true);
    }
    InText = 0;
} 

void npc5_interaction(int has_orb) {
    InText = 1;
    if (has_orb == 0) {
        npc5_text();
        wait_ms(400);
        wait_for_action1();
        draw_clear();
        init_main_map();
        draw_game(true);
        CheckPoint = 3;
    } else if (has_orb == 1) {
        npc5_text1();
        wait_ms(400);
        wait_for_action1();
        npc5_text2();
        wait_ms(400);
        wait_for_action1();
        draw_clear();
        init_main_map();
        draw_game(true);
    }
    InText = 0;
} 

int delete_door(int has_key) {
    InText = 1;
    int doorVal = 0;
    if (has_key == 0) {
        draw_no_unlock();
        doorVal = 0;
        while(1) {
            Timer t; t.start();
            GameInputs inputs = read_inputs(); 
            int action = get_action(inputs);
            if (action == 1) {
                break;
            }
            t.stop();
            int dt = t.read_ms();
            if (dt < 100) wait_ms(500 - dt);
        }
        draw_clear();
        init_main_map();
        draw_game(true);
    } else if (has_key == 1) {
        doorVal = 1;
        draw_unlock();
        while(1) {
            Timer t; t.start();
            GameInputs inputs = read_inputs(); 
            int action = get_action(inputs);
            if (action == 1) {
                break;
            }
            t.stop();
            int dt = t.read_ms();
            if (dt < 100) wait_ms(500 - dt);
        }
        draw_clear();
        init_main_map();
        add_dirt(10, 20, HORIZONTAL, 6);
        draw_game(true);
    }
    InText = 0;
    return doorVal;
}

/**
 * Entry point for frame drawing. This should be called once per iteration of
 * the game loop. This draws all tiles on the screen, followed by the status 
 * bars. Unless init is nonzero, this function will optimize drawing by only 
 * drawing tiles that have changed from the previous frame.
 */
void draw_game(int init)
{
    // Draw game border first
    if(init) {
        draw_border();
    }
    // Iterate over all visible map tiles
    for (int i = -5; i <= 5; i++) // Iterate over columns of tiles
    {
        for (int j = -4; j <= 4; j++) // Iterate over one column of tiles
        {
            // Here, we have a given (i,j)
            
            // Compute the current map (x,y) of this tile
            int x = i + Player.x;
            int y = j + Player.y;
            
            // Compute the previous map (px, py) of this tile
            int px = i + Player.px;
            int py = j + Player.py;
                        
            // Compute u,v coordinates for drawing
            int u = (i+5)*11 + 3;
            int v = (j+4)*11 + 15;
            
            // Figure out what to draw
            DrawFunc draw = NULL;
            if (init && i == 0 && j == 0) // Only draw the player on init
            {
                if (Player.has_orb == 1) {
                    draw_player_orb(u, v, Player.has_key);
                } else {
                    draw_player(u, v, Player.has_key);
                }
                continue;
            }
            else if (x >= 0 && y >= 0 && x < map_width() && y < map_height()) // Current (i,j) in the map
            {
                if (!(x == Player.x && Player.y == y)) {
                
                    MapItem* curr_item = get_here(x, y);
                    MapItem* prev_item = get_here(px, py);
                    if (init || curr_item != prev_item) // Only draw if they're different
                    {   
                        if (curr_item) {      // There's something here! Draw it
                            draw = curr_item->draw;
                        } else { // There used to be something, but now there isn't
                            draw = draw_nothing;
                        }
                    }
                }
            }
            else if (init) // If doing a full draw, but we're out of bounds, draw the walls.
            {
                draw = draw_wall;
            }
            // Actually draw the tile
            if (draw) draw(u, v);
        }
    }
    // Draw status bars   
    draw_life_bar(Lives);
    draw_health_bar(Health);
    // Draw player coordinates
    draw_coord(Player.x, Player.y);
}


/**
 * Initialize the main world map. Add walls around the edges, interior chambers,
 * and plants in the background so you can see motion.
 */
void init_main_map()
{
    // "Random" plants
    Map* map = set_active_map(0);
    for(int i = map_width() + 5; i < map_area()/3; i += 51) {
        if (i > 130) {
            add_plant(i % map_width(), i / map_width());
        }
    }
    pc.printf("Plants done!\r\n");
        
    pc.printf("Adding walls!\r\n");
    // outside walls
    add_wall(0, 0,   HORIZONTAL, map_width());
    add_wall(0,map_height()-1, HORIZONTAL, map_width());
    add_wall(0,  0,   VERTICAL,  map_height());
    add_wall(map_width()-1,  0,              VERTICAL,   map_height());
    // create NPC house
    add_wall(47, 7, HORIZONTAL, 12);
    add_wall(47, 1, VERTICAL, 4);
    // create character house
    add_dirt(2, 2, HORIZONTAL, 2);
    add_wall(5, 1, VERTICAL, 5);
    add_wall(1, 5, HORIZONTAL, 1);
    add_wall(4, 5, HORIZONTAL, 1);
    // create river
    add_water(1, 22, HORIZONTAL, map_width() - 2);
    add_water(1, 23, HORIZONTAL, map_width() - 2);
    add_water(1, 24, HORIZONTAL, map_width() - 2);
    add_water(5, 21, HORIZONTAL, 5);
    add_water(16, 21, HORIZONTAL, 5);
    add_water(28, 21, HORIZONTAL, 5);
    add_water(40, 21, HORIZONTAL, 5);
    add_water(50, 21, HORIZONTAL, 5);
    add_water(2, 25, HORIZONTAL, 5);
    add_water(12, 25, HORIZONTAL, 4);
    add_water(23, 25, HORIZONTAL, 5);
    add_water(34, 25, HORIZONTAL, 5);
    add_water(45, 25, HORIZONTAL, 5);
    add_water(52, 25, HORIZONTAL, 5);
    // create bridge 1 WEST
    add_wall(9, 26, HORIZONTAL, 1);
    add_wall(9, 20, HORIZONTAL, 1);
    add_wall(10, 21, VERTICAL, 5);
    add_wall(16, 20, HORIZONTAL, 1);
    add_wall(16, 26, HORIZONTAL, 1);
    add_wall(15, 21, VERTICAL, 5);
    add_dirt(11, 21, VERTICAL, 5);
    add_dirt(12, 21, VERTICAL, 5);
    add_dirt(13, 21, VERTICAL, 5);
    add_dirt(14, 21, VERTICAL, 5);
    add_dirt(10, 26, HORIZONTAL, 6);
    // all coridoor 2
    add_wall(23, 26, VERTICAL, 25);
    add_wall(24, 50, HORIZONTAL, 5);
    add_wall(30, 25, VERTICAL, 34);
    add_npc4(25,30);
    add_npc5(27,30);
    if (Player.has_orb == 0) {
        add_orb(26,28);
    }
    // add door
    if (Player.has_key == 0) {
        add_door(10, 20, HORIZONTAL, 6);
    }
    //add traps
    add_trap(15,15);
    add_trap(16,15);
    add_trap(17,15);
    add_trap(18,15);
    add_trap(19,15);
    add_trap(20,15);
    add_trap(21,15);
    if (Shoes == 0) {
        add_shoes(13, 28);
    }
    add_trap(8,14);
    add_trap(43,9);
    add_trap(35,13);
    add_trap(23,10);
    add_trap(17,8);
    add_trap(8,17);
    // add food
    if (Player.has_food == 0) {
        add_food(15,7);
    }
    if (Player.has_sword == 0) {
        add_sword(57,5);
    }
    // create mountain and caves
    
    // add npc1
    add_npc(55,3);
    // add npc2
    add_npc2(4,4);
    // add npc3
    add_npc3(11, 34);
    if (M1 == 1) add_monster(11, 42);
    if (M2 == 1) add_monster(5, 50);
    if (M3 == 1) add_monster(19, 38);
    pc.printf("Map creation done!\r\n");

    print_map();
}

void init_start() {
    draw_start();
    while(1) {
            Timer t; t.start();
            GameInputs inputs = read_inputs(); 
            int action = get_action(inputs);
            if (action == 1) {
                break;
            }
            t.stop();
            int dt = t.read_ms();
            if (dt < 100) wait_ms(200 - dt);
    }
    uLCD.background_color(BLACK);
    uLCD.cls();
}

void game_over() {
    uLCD.cls();
}
/**
 * Program entry point! This is where it all begins.
 * This function orchestrates all the parts of the game. Most of your
 * implementation should be elsewhere - this holds the game loop, and should
 * read like a road map for the rest of the code.
 */
int main()
{   
    // First things first: initialize hardware
    ASSERT_P(hardware_init() == ERROR_NONE, "Hardware init failed!");
    pc.printf("UNO\r\n");
    // Start screen
    init_start();
    // Initialize the maps
    speaker = 0.1;
    speaker.period(1.0/200.0);
    wait(.2);
    speaker.period(1.0/400.0);
    wait(.2);
    speaker.period(1.0/600.0);
    wait(.2);
    speaker = 0.0;
    GodMode = 0;
    maps_init();
    pc.printf("DOS\r\n");
    init_main_map();
    
    // Initialize game state
    set_active_map(0);
    Player.x = Player.y = 1;
    pc.printf("Drawing game next!\r\n");
    // Initial drawing
    draw_game(true);

    // Main game loop
    while(1)
    {
        // Timer to measure game update speed
        Timer t; t.start();
        
        // Actuall do the game update:
        // 1. Read inputs
        pc.printf("Getting hardware inputs\r\n");
        GameInputs inputs = read_inputs();        
        // 2. Determine action (get_action)
        pc.printf("Deciding action\r\n");
        int action = get_action(inputs);        
        // 3. Update game (update_game)
        int result = update_game(action);
        // 3b. Check for game over
        if (result == LOSE_LIFE) {
            switch (CheckPoint) {
                case 0:
                    Player.x = 1;
                    Player.y = 1;
                    break;
                case 1:
                    Player.x = 54;
                    Player.y = 3;
                    break;       
                case 2:
                    Player.x = 11;
                    Player.y = 33;
                    break;
                case 3:
                    Player.x = 25;
                    Player.y = 31;
                    break;
            }
            Health = 3;
        }
        // 4. Draw frame (draw_game)
        draw_game(result);
        if (Win == 1) {
            break;
        }
        if (result == GAME_OVER) {
            break;
        }
        // 5. Frame delay
        t.stop();
        int dt = t.read_ms();
        if (dt < 100) wait_ms(100 - dt);
    }
    wait_ms(100);
    if (Win == 1) {
        draw_win_game();
        speaker = 0.1;
        speaker.period(1.0/200.0);
        wait(.1);
        speaker.period(1.0/400.0);
        wait(.1);
        speaker.period(1.0/600.0);
        wait(.4);
        speaker = 0.0;
    } else {
        draw_game_over();
        speaker = 0.1;
        speaker.period(1.0/700.0);
        wait(.1);
        speaker.period(1.0/300.0);
        wait(.1);
        speaker.period(1.0/100.0);
        wait(.4);
        speaker = 0.0;
    }
}
