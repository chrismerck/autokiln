#ifndef __INPUT_H__
#define __INPUT_H__

#define INPUT_EVENT_DOWN   1
#define INPUT_EVENT_UP    -1
#define INPUT_EVENT_NONE   0

enum input_type_t {
  INPUT_TYPE_CLICK,
  INPUT_TYPE_MANUAL,
  INPUT_TYPE_MENU,
  INPUT_TYPE_RESET,
  INPUT_TYPE_ENCODER,
};

void Input_Init();

#endif
