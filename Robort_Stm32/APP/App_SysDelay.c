#include "App_SysDelay.h"

void SysDelay_Init()
{
	delay_init();
}

void SysDelay_us(uint32 nus)
{
	delay_us(nus);
}
void SysDelay_ms(uint16 nms)
{
	delay_ms(nms);
}