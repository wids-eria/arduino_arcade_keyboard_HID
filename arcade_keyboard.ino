char  keymap[10] = {0};
int key[10] = {HIGH};
uint8_t buf[8] = {0}; /* Keyboard report buffer for keyboard HID firmware */
int buffer_map[10] = {0};

void setup()
{
  // Map physical inputs to keyboard simulation buffer
  keymap[2] = 34; // '5'
  keymap[3] = 34; // '5'
  keymap[4] = 30; // '1'
  keymap[5] = 31; // '2'
  keymap[6] = 26; // 'w'
  keymap[7] = 22; // 's'
  keymap[8] =  4; // 'a'
  keymap[9] =  7; // 'd'

  // Which of the 6 'held down' buffers to write the button to.
  // coins share 2, and W/A, then S/D share.
  buffer_map[2] = 2;
  buffer_map[3] = 2;
  buffer_map[4] = 3;
  buffer_map[5] = 4;
  buffer_map[6] = 5;
  buffer_map[7] = 5;
  buffer_map[8] = 6;
  buffer_map[9] = 6;

  for(int i = 2; i < 10; i++) {
         pinMode(i,INPUT);
    digitalWrite(i,HIGH );
  }

  pinMode(13, OUTPUT);
  digitalWrite(13,LOW );

  Serial.begin(9600);
  delay(1000);
}

void loop()
{
  digitalWrite(13, LOW);
  bool changes = false;

  // gather inputs
  for(int i = 2; i < 10; i++) {
    int key_state = digitalRead(i);

    if(key_state == LOW) {
      digitalWrite(13, HIGH); // visual indication that input is happening
    }

    if(key_state != key[i]) {
      changes = true;
      key[i] = key_state;
    }

  }
  delay(10); // debounce input


  // prepare keyboard buffer

  if(changes) {
    // coin 1 and 2
    if(key[2] == LOW || key[3] == LOW) {
      buf[buffer_map[2]] = keymap[2];
    }
    else {
      buf[buffer_map[2]] = 0;
    }

    // write start
    if(key[4] == LOW) {
      buf[buffer_map[4]] = keymap[4];
    }
    else {
      buf[buffer_map[4]] = 0;
    }

    // write exit
    if(key[5] == LOW) {
      buf[buffer_map[5]] = keymap[5];
    }
    else {
      buf[buffer_map[5]] = 0;
    }

    // if w or s write
    if(key[6] == LOW) {
      buf[buffer_map[6]] = keymap[6];
    }
    else if(key[7] == LOW) {
      buf[buffer_map[7]] = keymap[7];
    }
    else {
      buf[buffer_map[6]] = 0;
    }

    // if a or d write
    if(key[8] == LOW) {
      buf[buffer_map[8]] = keymap[8];
    }
    else if(key[9] == LOW) {
      buf[buffer_map[9]] = keymap[9];
    }
    else {
      buf[buffer_map[8]] = 0;
    }

    Serial.write(buf, 8); // send HID packet to keyboard HID firmware.
  }

}
