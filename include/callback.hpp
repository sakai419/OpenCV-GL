#pragma once

// callback functions of home state
void display_home();
void keyboard_home(unsigned char key, int x, int y);
void mouse_home(int button, int state, int x, int y);
void motion_home(int x, int y);
void idle_home();
void special_home(int key, int x, int y);

// callback functions of stage state
void display_stage();
void keyboard_stage(unsigned char key, int x, int y);
void mouse_stage(int button, int state, int x, int y);
void motion_stage(int x, int y);
void idle_stage();

// callback functions of answer state
void display_answer();
void keyboard_answer(unsigned char key, int x, int y);
void mouse_answer(int button, int state, int x, int y);
void motion_answer(int x, int y);
void idle_answer();

// callback functions of result state
void display_result();
void keyboard_result(unsigned char key, int x, int y);
void mouse_result(int button, int state, int x, int y);
void motion_result(int x, int y);
void idle_result();