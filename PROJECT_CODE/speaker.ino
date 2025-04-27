void playTone(){
  for (int thisNote = 0; melody[thisNote] != -1; thisNote++) {
    int noteDuration = speed * noteDurations[thisNote];
    tone(speakerPin, melody[thisNote], noteDuration * 0.95);
    Serial.println(melody[thisNote]);

    delay(noteDuration);

    noTone(speakerPin);
  }
}