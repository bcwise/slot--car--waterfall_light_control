/*******************************************************************************
 * SlotCarLightControl
 *
 * Comment
 *  Used for the slot car track.
 *
 *  Setup:
 *
 */

//*****************************************************************************
// HEADER FILES
//*****************************************************************************
#include <FastLED.h>


//*****************************************************************************
// CONSTANTS
//*****************************************************************************

// The track will be sectioned off into block.
// Each block will have a separate data line running to it.
// Here are the sections (mostly for street lights):
//   * WINDING_START
//   * BEFORE_STRAIGHT
//   * STRAIGHT_AWAY
//   * CURVE_TO_WATERFALLS
//   * WATERFALL_TUNNEL
//   * DOWN_TO_HAIRPIN
//   * HAIRPIN
//   * HAIRPIN_TUNNEL
//   * BACK_UPPER
//   * BRIDGE_AREA
//   * FINISH_LINE
// Some additional areas
//   * WATERFALL_UPPER_BACKGROUND
//   * WATERFALL_MID_BACKGROUND
//   * WATERFALL_LOWER_BACKGROUND
//   * WATERFALL_BRIDGE_UNDER
//   * WATERFALL_UPPER_ROCKS
//   * WATERFALL_LOWER_ROCKS
//   * WATERFALL_TUNNEL_INSIDE
//   * WATERFALL_TUNNEL_ENTRANCE  (probably combine the entrance & exit)
//   * WATERFALL_TUNNEL_EXIT
//   * PLANETARIUM_OUTER_LIGHTS
//   * HAIRPIN_TUNNEL_ENTRANCE  (probably combine the entrance & exit)
//   * HAIRPIN_TUNNEL_EXIT
// For led chips like WS2812, which have a data line, ground, and power, you just
// need to define DATA_PIN_A.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN_A and CLOCK_PIN
// Clock pin only needed for SPI based chipsets when not using hardware SPI

// Here are the pin assignments:
// Pin 13: an LED connected that is on the Arduino
// Pin  5: The data pin for the first strand of LED lights
// Pin  6: The data pin for the second strand of LED lights

#define LEDPIN 13

// TABLE #1 & 2
// Actually, it's the first 3-tables
// From the finish line straightaway to the road going under the finish line
// This will also include Hogwarts
// Here's the order (which will correspond to the data pin -- starting w/ 2)
// Hogwart's will add additional lighting:
//  * behind Hogwarts
//  * Hogwarts Interiors
//  * Hogwarts Entrance

/* #define FIRST_CURVES_DATA_PIN         3 */
/* #define FIRST_CURVES_NUM_LEDS         6 */
/* #define FIRST_CURVES_BRIGHTNESS       200 */

/* #define ROAD_TO_HOGWARTS_DATA_PIN     4 */
/* #define ROAD_TO_HOGWARTS_NUM_LEDS     8 */
/* #define ROAD_TO_HOGWARTS_BRIGHTNESS   200 */

/* #define UNDER_OVERPASS_DATA_PIN       5 */
/* #define UNDER_OVERPASS_NUM_LEDS       6 */
/* #define UNDER_OVERPASS_BRIGHTNESS     200 */

/* #define HOGWARTS_DATA_PIN             6 */
/* #define HOGWARTS_NUM_LEDS             10 */
/* #define HOGWARTS_BRIGHTNESS           200 */

/* #define HOGWARTS_BEHIND_DATA_PIN      7 */
/* #define HOGWARTS_BEHIND_NUM_LEDS      10 */
/* #define HOGWARTS_BEHIND_BRIGHTNESS    200 */

/* #define HOGWARTS_INTERIORS_DATA_PIN   8 */
/* #define HOGWARTS_INTERIORS_NUM_LEDS   10 */
/* #define HOGWARTS_INTERIORS_BRIGHTNESS 200 */

/* #define HOGWARTS_ENTRANCE_DATA_PIN    9 */
/* #define HOGWARTS_ENTRANCE_NUM_LEDS    10 */
/* #define HOGWARTS_ENTRANCE_BRIGHTNESS  200 */



// First set of digital pins (31--37)
#define UPPER_ROAD_DATA_PIN         31
#define UPPER_ROAD_NUM_LEDS         6
#define UPPER_ROAD_BRIGHTNESS       200

#define LOWER_ROAD_DATA_PIN         32
#define LOWER_ROAD_NUM_LEDS         6
#define LOWER_ROAD_BRIGHTNESS       200

#define PLANETARIUM_DATA_PIN         33
#define PLANETARIUM_NUM_LEDS         6
#define PLANETARIUM_BRIGHTNESS       200

#define BACK_STRAIGHT_DATA_PIN      34
#define UPPER_ROAD_LEDS      6
#define BACK_STRAIGHT_BRIGHTNESS    200

#define THE_HILLS_DATA_PIN          35
#define THE_HILLS_NUM_LEDS          6
#define THE_HILLS_BRIGHTNESS        200

#define CLIMBING_CURVE_DATA_PIN         36
#define CLIMBING_CURVE_NUM_LEDS         6
#define CLIMBING_CURVE_BRIGHTNESS       200

#define BRIDGE_DATA_PIN             37
#define BRIDGE_NUM_LEDS             10
#define BRIDGE_BRIGHTNESS           200

// First set of digital pins (47--53)
#define UPPER_ROAD_DATA_PIN2         47
#define UPPER_ROAD_NUM_LEDS2         25
#define UPPER_ROAD_BRIGHTNESS2       200

#define LOWER_ROAD_DATA_PIN2         48
#define LOWER_ROAD_NUM_LEDS2         6
#define LOWER_ROAD_BRIGHTNESS2       200

#define PLANETARIUM_DATA_PIN2         49
#define PLANETARIUM_NUM_LEDS2         6
#define PLANETARIUM_BRIGHTNESS2       200

#define BACK_STRAIGHT_DATA_PIN2      50
#define BACK_STRAIGHT_NUM_LEDS2      6
#define BACK_STRAIGHT_BRIGHTNESS2    200

#define THE_HILLS_DATA_PIN2          51
#define THE_HILLS_NUM_LEDS2          6
#define THE_HILLS_BRIGHTNESS2        200

#define CLIMBING_CURVE_DATA_PIN2         52
#define CLIMBING_CURVE_NUM_LEDS2         6
#define CLIMBING_CURVE_BRIGHTNESS2       200

#define BRIDGE_DATA_PIN2             53
#define BRIDGE_NUM_LEDS2             10
#define BRIDGE_BRIGHTNESS2           200

// You will also have several areas with additional lighting, as follows:
//  * Upper waterfalls
//  * Mid waterfalls
//  * Lower waterfalls
//  * Upper rocks
//  * Mid rocks
//  * Lower rocks
//  * Under bridge
//  * In front of bridge
//  * Water pond
//  *


#if 0
typedef struct {
    const int brightness;
    const CRGB& init_color;
} t_light_block;

t_light_block light_block = {
    BACK_STRAIGHT_BRIGHTNESS,
    CRGB::White,
};

t_light_block light_block__finish_line = {
    FINISH_LINE_BRIGHTNESS,
    CRGB::White,
};

t_light_block light_block__hogwarts = {
    HOGWARTS_BRIGHTNESS,
    CRGB::Orange,
};

t_light_block light_block__road_to_hogwarts = {
    ROAD_TO_HOGWARTS_BRIGHTNESS,
    CRGB::White,
};
#endif
//*****************************************************************************
// DATA
//*****************************************************************************
CRGB upper_road_leds[UPPER_ROAD_NUM_LEDS];
CRGB lower_road_leds[LOWER_ROAD_NUM_LEDS];

//*****************************************************************************
// FUNCTIONS
//*****************************************************************************

/*------------------------------------------------
 * Function: setup
 */
void setup() {
    int i;

    delay(3000); // sanity delay

    // Setup the serial line
    Serial.begin(9600);
    Serial.println("********************************");
    Serial.println("Starting slot_car--light_control--waterfall....");
    Serial.println("********************************");
    delay(3000); // sanity delay

    // How bright?
    FastLED.setBrightness(  200 );

    // Uncomment/edit one of the following lines for your leds arrangement.
    // ## Clockless types ##
    FastLED.addLeds<NEOPIXEL, UPPER_ROAD_DATA_PIN>(upper_road_leds, UPPER_ROAD_NUM_LEDS);  // GRB ordering is assumed);  // GRB ordering is assumed
    FastLED.addLeds<NEOPIXEL, LOWER_ROAD_DATA_PIN>(lower_road_leds, LOWER_ROAD_NUM_LEDS);  // GRB ordering is assumed);  // GRB ordering is assumed

    // Clear out the LED array to a dim background blue-green
    fill_solid( upper_road_leds,    UPPER_ROAD_LEDS,    CRGB( 12, 7, 3));
    fill_solid( lower_road_leds,      LOWER_ROAD_NUM_LEDS,      CRGB( 3,  7, 12));
    FastLED.show();
    Serial.println("Set all LEDs to a dim background blue-green, pause 3 seconds");
    delay(3000);

    // Setup the following to be white:
    //  * road_to_hogwarts_leds
    //  * lower_road_leds
    //  * upper_road_leds

    fill_solid( upper_road_leds,    UPPER_ROAD_LEDS,    CRGB::White);
    fill_solid( lower_road_leds,      LOWER_ROAD_NUM_LEDS,      CRGB::White);
    FastLED.show();
    Serial.println("Finish Line, backstraight away, and road to Hogwarts: set to white, pause 3 seconds");
    delay(3000);

    Serial.println("Loop...");
}


/*------------------------------------------------
 * Function: loop
 */
void loop() {
    // Refresh colors
    fill_solid( upper_road_leds,      UPPER_ROAD_LEDS,      CRGB::White);
    fill_solid( lower_road_leds,      LOWER_ROAD_NUM_LEDS,      CRGB::White);
    FastLED.show();
    delay(500);
}
