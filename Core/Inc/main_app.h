#ifndef INC_MAIN_APP_H_
#define INC_MAIN_APP_H_

#include <stdint.h>

#define LED_BLINK_ON_DELAY		50U
#define LED_BLINK_OFF_DELAY		1000U - LED_BLINK_ON_DELAY

typedef struct {
	void * port;
	uint16_t pin;
}GPIO_Properties_t;

typedef struct {
	enum {
		BUTTON_OFF	= 0,
		BUTTON_PUSHED,
		BUTTON_LOCK
	}status;
	GPIO_Properties_t * line;
	uint32_t delay;
	void (*callback)(void * arg);
}PushButton_Properties_t;

typedef struct {
	enum {
		LED_OFF		= 0,
		LED_ON,
		LED_BLINK
	}state;
	enum {
		ACTIVE_LOW	= 0,
		ACTIVE_HIGH
	}orientation;
	GPIO_Properties_t * line;
	uint32_t delay;
}LEDIndicator_Properties_t;
#endif /* INC_MAIN_APP_H_ */
