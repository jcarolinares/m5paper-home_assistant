// config.h
#ifndef CONFIG_H
#define CONFIG_H

const int button_width = 180;
const int button_heigh = 95;

void define_buttons_matrix();

const int buttons_matrix_coordinates[][4] = { // Pos X, Final X,  Pos Y,  Final Y, Button 1,2,3 (first row) and so on
  {0, 0+button_width, 60+0*button_heigh, 60+1*button_heigh}, {0+button_width, 0+2*button_width, 60+0*button_heigh, 60+1*button_heigh}, {0+2*button_width, 0+3*button_width, 60+0*button_heigh, 60+1*button_heigh}, // 0,N
  {0, 0+button_width, 60+1*button_heigh, 60+2*button_heigh}, {0+button_width, 0+2*button_width, 60+1*button_heigh, 60+2*button_heigh}, {0+2*button_width, 0+3*button_width, 60+1*button_heigh, 60+2*button_heigh}, // 1,N
  {0, 0+button_width, 60+2*button_heigh, 60+3*button_heigh}, {0+button_width, 0+2*button_width, 60+2*button_heigh, 60+3*button_heigh}, {0+2*button_width, 0+3*button_width, 60+2*button_heigh, 60+3*button_heigh}, // 2,N 
  {0, 0+button_width, 60+3*button_heigh, 60+4*button_heigh}, {0+button_width, 0+2*button_width, 60+3*button_heigh, 60+4*button_heigh}, {0+2*button_width, 0+3*button_width, 60+3*button_heigh, 60+4*button_heigh}, // 2,N 
  {0, 0+button_width, 60+4*button_heigh, 60+5*button_heigh}, {0+button_width, 0+2*button_width, 60+4*button_heigh, 60+5*button_heigh}, {0+2*button_width, 0+3*button_width, 60+4*button_heigh, 60+5*button_heigh}, // 3,N 
  {0, 0+button_width, 60+5*button_heigh, 60+6*button_heigh}, {0+button_width, 0+2*button_width, 60+5*button_heigh, 60+6*button_heigh}, {0+2*button_width, 0+3*button_width, 60+5*button_heigh, 60+6*button_heigh}, // 4,N 
  {0, 0+button_width, 60+6*button_heigh, 60+7*button_heigh}, {0+button_width, 0+2*button_width, 60+6*button_heigh, 60+7*button_heigh}, {0+2*button_width, 0+3*button_width, 60+6*button_heigh, 60+7*button_heigh}, // 5,N 
  {0, 0+button_width, 60+7*button_heigh, 60+8*button_heigh}, {0+button_width, 0+2*button_width, 60+7*button_heigh, 60+8*button_heigh}, {0+2*button_width, 0+3*button_width, 60+7*button_heigh, 60+8*button_heigh}, // 6,N 
  {0, 0+button_width, 60+8*button_heigh, 60+9*button_heigh}, {0+button_width, 0+2*button_width, 60+8*button_heigh, 60+9*button_heigh}, {0+2*button_width, 0+3*button_width, 60+8*button_heigh, 60+9*button_heigh}, // 7,N 
};




const String buttons_names[9][3] = { // Max 6 CAP letters with a font size of 4
  {"LIGHTS", "CAMERA", "TELE"},
  {"AMBI", "MOV", "PLAY"},
  {"ENTER", "   ", "PAUSE"},
  {"SALON", "CAMERA", "TELE"},
  {"AMBI", "   ", "PLAY"},
  {"   ", "   ", "PAUSE"},
  {"LIGHTS", "CAMERA", "TELE"},
  {"AMBI", "   ", "PLAY"},
  {"KITCHEN", "   ", "PAUSE"}
};

// int buttons_matrix_coordinates[3][4] = {};
// void define_buttons_matrix(){
//   for (int row = 0; row < 3; row++) {
//       buttons_matrix_coordinates[row][0] = 0;
//       buttons_matrix_coordinates[row][1] = 0+button_width;
//       buttons_matrix_coordinates[row][2] = 60+row*button_heigh;
//       buttons_matrix_coordinates[row][3] = 60+(row+1)*button_heigh;
//   }
// }

#endif