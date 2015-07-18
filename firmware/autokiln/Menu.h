#ifndef __MENU_H__
#define __MENU_H__

#include"Input.h"
#include"Os.h"

void Menu_Init();

class MenuBase {
public:
  MenuBase();
  virtual void Input(input_type_t type, int32_t arg) = 0;
  virtual void Redraw() = 0;
  void Schedule_Redraw() { need_redraw = true; };
  bool Need_Redraw() { return need_redraw; };
protected:
  bool need_redraw = false;
};

extern MenuBase * g_pCurrentMenu;

class MenuMain : public MenuBase {
public:
  MenuMain();
  void Input(input_type_t type, int32_t arg);
  void Redraw();
};


class MenuHist : public MenuBase {
public:
  MenuHist();
  void Input(input_type_t type, int32_t arg);
  void Redraw();
};


class MenuConfig : public MenuBase {
public:
  MenuConfig();
  void Input(input_type_t type, int32_t arg);
  void Redraw();
private:
  int32_t item = 0;
  int32_t pos = 0;
};

#endif // __MENU_H__
