#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EmbAJAX.h>
#define BUFLEN 30



#include <DNSServer.h>
const byte DNS_PORT = 53;
DNSServer dnsServer;

String Welcome = ""
                      "<!DOCTYPE html><html><head><title>CaptivePortal</title></head><body>"
                      "<h1>Hello World!</h1><p>This is a captive portal example. All requests will "
                      "be redirected here.</p></body></html>";


 #include <FastLED.h>
    #define LED_PIN     13
    #define NUM_LEDS    30
    CRGB leds[NUM_LEDS];
    int num = 0; 
    int num1 = 0; 
    //int freq = 100;
    int tick = 1000;
    int lum = 100;
    int minn = 0;
    int maxx = 30;
    float r = 0;
    float g = 255;
    float b = 0;
    float bright = 1;

// Set up web server, and register it with EmbAJAX
ESP8266WebServer server(80);
EmbAJAXOutputDriverESP8266 driver(&server);

// Define the main elements of interest as variables, so we can access to them later in our sketch.
EmbAJAXColorPicker color("color", 0, 255, 0);
EmbAJAXMutableSpan color_d("color_d");
char color_d_buf[BUFLEN];

EmbAJAXSlider numen("numen", 0, 30,0);   // slider, from 0 to 500, initial value 400
EmbAJAXMutableSpan numen_d("numen_d");

EmbAJAXSlider lumen("lum", 0, 100, 1);   // slider, from 0 to 500, initial value 400
EmbAJAXMutableSpan lum_d("lum_d");
EmbAJAXSlider blinkfreqs("tick", 1, 100, 100);   // slider, from 0 to 500, initial value 400
EmbAJAXSlider blinkfreqm("tick", 50, 500, 100);
EmbAJAXSlider blinkfreqf("tick", 500, 1000, 100);
EmbAJAXMutableSpan tick_d("tick_d");
char tick_d_buf[BUFLEN];

// Define a page (named "page") with our elements of interest, above, interspersed by some uninteresting
// static HTML. Note: MAKE_EmbAJAXPage is just a convenience macro around the EmbAJAXPage###>-class.
MAKE_EmbAJAXPage(page, "EMDR Controller Page", "",

  new EmbAJAXStatic("<h1>EMDR Panel V0.2</h1><p>Choose the color: "),
  &color,
  new EmbAJAXStatic("</p><p>Brightness:"),
  &lumen,
  &lum_d,
  new EmbAJAXStatic("</p><p>Width:"),
  &numen,
  new EmbAJAXStatic("</p><p>Current number:"),
  &numen_d,
  new EmbAJAXStatic("</p><p>Current color:"),
  &color_d,
  new EmbAJAXStatic("</p><p>Blink frequency: <i>FAST</i>"),
  &blinkfreqs,
  &blinkfreqm,
  &blinkfreqf,
  new EmbAJAXStatic("<i>SLOW</i></p><p>Vitesse actuelle:"),
  &tick_d,
  new EmbAJAXStatic("</p>")
)

void handlePage() {
  if(server.method() == HTTP_POST) { // AJAX request
    page.handleRequest(updateUI);
  } else {  // Page load
    page.print();
  }
}

void setup() {
  // Example WIFI setup as an access point. Change this to whatever suits you, best.
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig (IPAddress (192,168,4,1), IPAddress (192,168,4,1), IPAddress (255,255,255,0));
  WiFi.softAP("EMDR_Marie", "12345678");
  // Tell the server to serve our EmbAJAX test page on root
  server.on("/", handlePage);
  server.begin();

   FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);

   dnsServer.start(DNS_PORT, "*", IPAddress (192,168,4,1));

  // replay to all requests with same HTML
    server.onNotFound([]() {
    server.send(200, "text/html", Welcome);
  });
    
}

void updateUI() {
  // Enabled / disable the slider. Note that you could simply do this inside the loop. However,
  // placing it here makes the client UI more responsive (try it).
  color_d.setValue(strncpy(color_d_buf, color.value(), BUFLEN));  // r, g, b, are also available, numerically.
}

void loop() {
  // handle network
  dnsServer.processNextRequest();
  server.handleClient();
  // handle network. loopHook() simply calls server.handleClient(), in most but not all server implementations.
  driver.loopHook();

  bright = lumen.intValue(); 
  r = color.red() / bright;
  g = color.green() / bright;
  b = color.blue() / bright;
  minn = numen.intValue();
  maxx = 30 - minn;

if(num < maxx){
  num1 = num - 1;
  leds[num] = CRGB(r, g, b);
  leds[num1] = CRGB(0, 0, 0);
  FastLED.show();
  num++;
  delay(blinkfreqs.intValue());
    }
else{
while(num > minn){ 
       num1 = num - 1;
       leds[num] = CRGB(0, 0, 0);
       leds[num1] = CRGB(r, g, b);
       FastLED.show();
       num--;
       delay(blinkfreqs.intValue());
    }
}
}

