#include <stdint.h>
#include "../../headers/io/screen.h"


void textGraphickInit(){
  vidptr = (char*)VIDEO_MEM;
  i = 0;
  cursorPos = START_VIDEO_BUFFER;

  setScreenTextColor(LIGHT_GREY);
  clearTextGraphickScreen();
}

void setScreenTextColor(uint8_t color){
  screenTextColor = color;
}

void scrollUp(){
  unsigned int buffer = cursorPos;
  cursorPos = 0;

  while(cursorPos < TEXT_LINE_NUMBERS * TEXT_COLLUM_NUMBERS){
    screenTextBuffer[cursorPos] = screenTextBuffer[cursorPos + TEXT_COLLUM_NUMBERS];
    ++cursorPos;
  }

  cursorPos = buffer - TEXT_COLLUM_NUMBERS;
}

void clearTextGraphickScreen(){
  cursorPos = 0;
  while(cursorPos < TEXT_LINE_NUMBERS * TEXT_COLLUM_NUMBERS + 160){
    screenTextBuffer[cursorPos] = ' ';
    screenTextBuffer[cursorPos+1] = screenTextColor;
    cursorPos += 2;
  }

  cursorPos = START_VIDEO_BUFFER;
}

void textGraphickPutChar(char c){
  switch(c){
    case '\n':
      textGraphickNewLine();
      break;
    default:
      screenTextBuffer[cursorPos] = c;
      screenTextBuffer[cursorPos+1] = screenTextColor;
      cursorPos += 2;
  }

  if(cursorPos > TEXT_COLLUM_NUMBERS * TEXT_LINE_NUMBERS) scrollUp();
}

void textGraphickDeleteChar(){
  if(cursorPos > 1){
    screenTextBuffer[cursorPos - 2] = ' ';
    cursorPos -= 2;
  }
}

void textGraphickNewLine(){
  int buffer = 0;
  buffer = cursorPos / TEXT_COLLUM_NUMBERS;

  if(buffer == 0)
    buffer = TEXT_COLLUM_NUMBERS - cursorPos;
  else{
    buffer = TEXT_COLLUM_NUMBERS * (buffer + 1);
    buffer = buffer - cursorPos;
  }

  cursorPos += buffer;
}

void updateScreen(){
  i = 0;

  while(i < TEXT_LINE_NUMBERS * TEXT_COLLUM_NUMBERS){
    vidptr[i] = screenTextBuffer[i];
    ++i;
  }

  i = 0;
}
