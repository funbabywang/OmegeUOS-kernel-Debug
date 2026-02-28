#ifndef INPUT_H
#define INPUT_H

#include <types.h>

/* 输入事件类型 */
enum input_event_type
{
    EV_KEY_DOWN,
    EV_KEY_UP,
};

/* 输入事件结构 */
struct input_event
{
    enum input_event_type type;
    uint32_t code; // 按键码或其它
};

/* 输入设备注册 */
int input_register_device(void (*event_callback)(struct input_event*));

/* 输入事件上报 */
void input_report_event(struct input_event* ev);

#endif