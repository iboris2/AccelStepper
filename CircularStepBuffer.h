/*
 * CIrcularStepBuffer.h
 *
 *  Created on: 12 avr. 2016
 *      Author: iboris
 */

#ifndef CIRCULARSTEPBUFFER_H_
#define CIRCULARSTEPBUFFER_H_

struct Command {
	uint16_t step_buff;
	uint8_t dir_buff;
};

struct CBuffer {
	struct Command command[128];
	volatile uint8_t wp;
	volatile uint8_t rp;
	volatile uint8_t step_added;
	volatile uint8_t step_consumed;	
};

static inline void init_c_buffer(struct CBuffer * c_buffer){
  c_buffer->wp = 0;
  c_buffer->rp = 0;
  c_buffer->step_added = 0;
  c_buffer->step_consumed = 0;
}

static inline uint8_t is_full(struct CBuffer * c_buffer){
	return ((c_buffer->wp - c_buffer->rp) & 0x7F) == 0x7F;
}

static inline void push(struct CBuffer * c_buffer, uint16_t value, uint8_t dir){
  c_buffer->command[c_buffer->wp].step_buff = value;
  c_buffer->command[c_buffer->wp].dir_buff = dir;
  if (dir != 255 )
  	c_buffer->step_added++;
  c_buffer->wp = (c_buffer->wp + 1) & 0x7F;
}

static inline uint8_t pull(struct CBuffer * c_buffer, struct Command *cmd){
  if (c_buffer->wp == c_buffer->rp) return 0;
  *cmd = c_buffer->command[c_buffer->rp];
  if (cmd->dir_buff != 255 )
  	c_buffer->step_consumed++;
  c_buffer->rp = (c_buffer->rp + 1) & 0x7F;
  return 1;
}

static inline uint8_t step_remaining(struct CBuffer * c_buffer){
	return (c_buffer->step_added - c_buffer->step_consumed);
}

#endif /* CIRCULARSTEPBUFFER_H_ */
