#ifndef GPIO__H__
#define GPIO__H__

#define  SET_OUTPUT_BIT(reg,bit)  ((reg)|=(1)<<(bit))
#define  RESET_INPUT_BIT(reg,bit)  ((reg)&=~((1)<<(bit)))
#define  TOGGLE_BIT(reg,bit)  ((reg)^=(1)<<(bit))


#endif