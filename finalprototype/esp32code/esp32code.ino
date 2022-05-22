
#include <WiFi.h>
#include "esp_camera.h"
#include "esp_system.h"
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

hw_timer_t *timer = NULL;
void IRAM_ATTR resetModule() {
  ets_printf("reboot\n");
  esp_restart();
}
#include <TridentTD_LineNotify.h>
#define SSID        "Hakao"   // WiFi name
#define PASSWORD    "KaoEud9962"   // PASSWORD
#define LINE_TOKEN  "nlSrjY8jpvhYBuYSbh0Pdb2PkTb3azmOYYrF1nhC3yj" // TOKEN
//notify-bot.line.me/th/
//nlSrjY8jpvhYBuYSbh0Pdb2PkTb3azmOYYrF1nhC3yj

// Pin definition for CAMERA_MODEL_AI_THINKER
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

int inPin = 14;
const int Led_Flash = 4;

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  Serial.begin(115200);
  while (!Serial) {
    ;
  }
  pinMode(inPin, INPUT);
  pinMode(Led_Flash, OUTPUT);
  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n",  SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(400);
  }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());
  LINE.setToken(LINE_TOKEN);

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  if (psramFound()) {
    // FRAMESIZE_ +
    //QQVGA/160x120//QQVGA2/128x160//QCIF/176x144//HQVGA/240x176
    //QVGA/320x240//CIF/400x296//VGA/640x480//SVGA/800x600//XGA/1024x768
    //SXGA/1280x1024//UXGA/1600x1200//QXGA/2048*1536
    config.frame_size = FRAMESIZE_VGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  }     else {
    config.frame_size = FRAMESIZE_QQVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

  // Init Camera
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }
}

int start = 0;
void loop() {
  int state = digitalRead(inPin);
  if (state == 1 && start == 0){
    Serial.println("input 1 recieved");
    Camera_capture();
    start = 1;
  }
  if (state == 0){
    start = 0;
  }
  delay(500);
}

void Camera_capture() {
  camera_fb_t * fb = NULL;
  delay(200);
  // Take Picture with Camera
  fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("Camera capture failed");
    return;
  }
  Send_line(fb->buf, fb->len);
  esp_camera_fb_return(fb);

}

void Send_line(uint8_t *image_data, size_t   image_size) {
  LINE.notifyPicture("Your ATK result from CO-DEK Machine", image_data, image_size);
}
