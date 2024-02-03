#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define BUTTON1_PIN 51

#define STRIP1_PIN 9
#define STRIP2_PIN 7
#define STRIP3_PIN 11
#define STRIP4_PIN 13
#define UNDERGLOW_PIN 5

enum LightMode
{
    AllOrange,
    AllRed,
    AllBlue,
    UnderglowOrange,
    UnderglowRed,
    UnderglowBlue
};

Adafruit_NeoPixel pixels1(       100,    STRIP1_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2(       100,    STRIP2_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels3(       100,    STRIP3_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels4(       100,    STRIP4_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel underglowStrip(100, UNDERGLOW_PIN, NEO_GRB + NEO_KHZ800);

const uint32_t BLACK      = pixels1.Color(  0,        0,    0);     // 255 110 0
const uint32_t TEAM_COLOR = pixels1.Color(255, 110 * 0.48,  0);     // 255 110 0
const uint32_t RED        = pixels1.Color(255,        0,    0);     // 255 70 0
const uint32_t BLUE       = pixels1.Color(  0,         0, 255);     // 255 70 0

bool button = true;

uint32_t color = TEAM_COLOR;
bool underOnly = false;

LightMode lightMode = AllOrange;

void setup()
{
    pinMode(BUTTON1_PIN, INPUT_PULLUP);

    pixels1.begin();
    pixels2.begin();
    pixels3.begin();
    pixels4.begin();
    underglowStrip.begin();

    pixels1.show();
    pixels2.show();
    pixels3.show();
    pixels4.show();
    underglowStrip.show();
}

void loop()
{
    bool newButton = digitalRead(BUTTON1_PIN);

    if (button && !newButton)// check for rising edge (when the button is released, since the button is high when not pressed)
    {
        switch (lightMode)
        {
        case AllOrange:
            lightMode = AllRed;
            color = RED;
            underOnly = false;
            break;

        case AllRed:
            lightMode = AllBlue;
            color = BLUE;
            underOnly = false;
            break;

        case AllBlue:
            lightMode = UnderglowOrange;
            color = TEAM_COLOR;
            underOnly = true;
            break;

        case UnderglowOrange:
            lightMode = UnderglowRed;
            color = RED;
            underOnly = true;
            break;

        case UnderglowRed:
            lightMode = UnderglowBlue;
            color = BLUE;
            underOnly = true;
            break;

        case UnderglowBlue:
        default:
            lightMode = AllOrange;
            color = TEAM_COLOR;
            underOnly = false;
        }
    }

    button = newButton;

    if (underOnly)
    {
        pixels1.fill(BLACK, 0, 100);
        pixels2.fill(BLACK, 0, 100);
        pixels3.fill(BLACK, 0, 100);
        pixels4.fill(BLACK, 0, 100);
        underglowStrip.fill(color, 0, 100);
    }
    else
    {
        pixels1.fill(color, 0, 100);
        pixels2.fill(color, 0, 100);
        pixels3.fill(color, 0, 100);
        pixels4.fill(color, 0, 100);
        underglowStrip.fill(color, 0, 100);
    }

    // display new colors
    pixels1.show();
    pixels2.show();
    pixels3.show();
    pixels4.show();
    underglowStrip.show();
}
