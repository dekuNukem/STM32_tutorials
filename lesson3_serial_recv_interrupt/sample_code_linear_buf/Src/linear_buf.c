#include <string.h>
#include "linear_buf.h"

void linear_buf_reset(linear_buf *lb)
{
  lb->curr_index = 0;
  memset(lb->buf, 0, LB_SIZE);
}

void linear_buf_add(linear_buf *lb, char c)
{
  lb->buf[lb->curr_index] = c;
  if(lb->curr_index < LB_SIZE - 1)
    lb->curr_index++;
}

uint8_t linear_buf_ready(linear_buf *lb)
{
  if(lb->buf[lb->curr_index - 1] == '\n')
    return 1;
  return 0;
}



