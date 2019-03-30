#include <stdio.h>
#include <stdlib.h>

struct stack {
  int size;
};

int left_startpoint(struct stack* stacks, int tgt_stack, int tgt_level);
int right_startpoint(struct stack* stacks, int tgt_stack, int tgt_level, int num_stacks);
int start_left(struct stack* stacks, int tgt_stack, int tgt_level);
int start_right(struct stack* stacks, int tgt_stack, int tgt_level, int num_stacks);
int remove_from_tgt_stack(struct stack* stacks, int tgt_stack, int tgt_level);

int main() {
  int num_boxes = 1;
  int num_stacks = 1;
  int tgt_stack, tgt_level;
  while (1) {
    scanf("%d %d",&num_boxes,&num_stacks);
    if (num_boxes == 0 && num_stacks == 0) {
      break;
    }
    struct stack stacks[num_stacks];
    struct stack* current_stack = (struct stack*)malloc(sizeof(struct stack));
    for (int stack_n=0; stack_n < num_stacks; stack_n++) {
      int num_boxes_stack;
      scanf("%d",&num_boxes_stack);
      current_stack = &stacks[stack_n];
      current_stack->size = num_boxes_stack;
      for (int i=0; i<num_boxes_stack; i++) {
        int box_id;
        scanf("%d",&box_id);
        if (box_id == 1) {
          tgt_stack = stack_n;
          tgt_level = i;
        }
      }
    }
    int from_same_stack = remove_from_tgt_stack(stacks, tgt_stack, tgt_level);
    if (tgt_stack == 0 || tgt_stack == num_stacks - 1) {
      printf("%d\n",from_same_stack);
    }
    else {
      int start_l = start_left(stacks,tgt_stack,tgt_level);
      int start_r = start_right(stacks,tgt_stack,tgt_level,num_stacks);
      printf("%d\n",start_l < start_r ? start_l + from_same_stack : start_r + from_same_stack);
    }
  }
  return 0;
}

int left_startpoint(struct stack* stacks, int tgt_stack, int tgt_level) {
  struct stack* stack = (stacks + --tgt_stack);
  while (tgt_stack >=0 && stack->size > tgt_level) {
    stack--;
    tgt_stack--;
  }
  if (tgt_stack < 0) {
    tgt_stack = 0;
  }
  return tgt_stack;
}

int right_startpoint(struct stack* stacks, int tgt_stack, int tgt_level, int num_stacks) {
  struct stack* stack = (stacks + ++tgt_stack);
  while (tgt_stack <= num_stacks && stack->size > tgt_level) {
    stack++;
    tgt_stack++;
  }
  if (tgt_stack > num_stacks - 1) {
    tgt_stack = num_stacks - 1;
  }
  return tgt_stack;
}

int start_left(struct stack* stacks ,int tgt_stack, int tgt_level) {
  int start_point = left_startpoint(stacks, tgt_stack, tgt_level);
  int n = 0;
  int num_boxes;
  while (start_point < tgt_stack) {
    num_boxes = (stacks+start_point++)->size - tgt_level;
    n += num_boxes > 0 ? num_boxes : 0;
  }
  return n;
}

int start_right(struct stack* stacks ,int tgt_stack, int tgt_level, int num_stacks) {
  int start_point = right_startpoint(stacks, tgt_stack, tgt_level, num_stacks);
  int n = 0;
  int num_boxes;
  while (start_point > tgt_stack) {
    num_boxes = (stacks+start_point--)->size - tgt_level;
    n += num_boxes > 0 ? num_boxes : 0;
  }
  return n;
}

int remove_from_tgt_stack(struct stack* stacks, int tgt_stack, int tgt_level) {
  return (stacks+tgt_stack)->size - tgt_level - 1;
}