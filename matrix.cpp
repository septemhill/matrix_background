#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <time.h>
#include <unistd.h>

using namespace std;

#define ARY_SIZE (64)

typedef struct _STR_FLOW{
  char str[ARY_SIZE];
  char output[ARY_SIZE];
  char color[ARY_SIZE];
} STR_FLOW;

/* Screen width */
#define STR_FLOW_COUNT  (160)

#define msleep(time) (usleep(time * 1000))

#define FONT_NONE         "\e[m"
#define FONT_DEEP_GREEN   "\e[0;32m"
#define FONT_LIGHT_GREEN  "\e[1;32m"
#define FONT_DEEP_GRAY    "\e[0;37m"
#define FONT_LIGHT_GRAY   "\e[1;37m"

//vector<char *> rand_str_cont;
vector<string> rand_str_cont;
STR_FLOW flows[STR_FLOW_COUNT];
string str_tbl = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

unsigned int gen_rand_num(unsigned int div)
{
  return (rand() % div);
}

void rand_init(void)
{
  srand(time(NULL));
}

void push_rand_str(void)
{
  int idx = 0, jdx = 0;
  int rand_str_len = 0;
  int rand_offset = 0;

  for (idx = 0; idx < STR_FLOW_COUNT; idx++) {
    string str = "";
    rand_str_len = gen_rand_num(35) + 6;
    
    for (jdx = 0; jdx < rand_str_len; jdx++) {
      rand_offset = gen_rand_num(str_tbl.length() - 1);
      str += str_tbl[rand_offset];
    }

    rand_str_cont.push_back(str);
  }
}

void flows_init(void)
{
  int i = 0;

  for (i = 0; i < STR_FLOW_COUNT; i++) {
    memset(flows[i].str, 0, ARY_SIZE);
    memcpy(flows[i].output, FONT_NONE"%c", sizeof(FONT_NONE"%c"));
    memcpy(flows[i].color, FONT_NONE, sizeof(FONT_NONE));
  }
}

string get_rand_str(void)
{
  return rand_str_cont[gen_rand_num(rand_str_cont.size() - 1)];
}

int main(int argc, char **argv)
{
  int idx = 0, jdx = 0;
  int rand_offset = 0;
  int rand_str_num = 0;

  rand_init();
  flows_init();

  push_rand_str();

  while (true) {
    /* Generate new offset for rand string in specified array */
    for (idx = 0; idx < STR_FLOW_COUNT; idx++) {
      rand_str_num = gen_rand_num(rand_str_cont.size() - 1);
      rand_offset = gen_rand_num(ARY_SIZE - 1 - rand_str_cont[rand_str_num].length());

      memset(flows[idx].str, 0x20, ARY_SIZE);
      memcpy(flows[idx].str + rand_offset, rand_str_cont[rand_str_num].c_str(), rand_str_cont[rand_str_num].length());
    }
 
    for (idx = 0; idx < ARY_SIZE; idx++) {
      for (jdx = 0; jdx < STR_FLOW_COUNT; jdx++) {
        switch (jdx % 4) {
          case 0:
            printf(FONT_DEEP_GREEN"%c", *(flows[jdx].str + idx));
            break;
          case 1:
            printf(FONT_LIGHT_GREEN"%c", *(flows[jdx].str + idx));
            break;
          case 2:
            printf(FONT_LIGHT_GRAY"%c", *(flows[jdx].str + idx));
            break;
          case 3:
            printf(FONT_DEEP_GRAY"%c", *(flows[jdx].str + idx));
            break;
        }
      }
      printf("\n");
      msleep(20);
    }

  }
}

