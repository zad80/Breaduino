#ifndef __MODULE_H__
#define __MODULE_H__

#include "Arduino.h"
#include "Breaduino.h"
#include "utility.h"
typedef enum _result_t
{
	r_ok = 0x00,
	r_running = 0x01,
	r_warning = 0x02,
	r_error = 0x04,
	r_exitMainLoop = 0xFE,
	r_aborted = 0xFF
}result_type;


class Module
{
public:
	Module()
	{
		_wake_up_time = 0;
	}
	virtual ~Module(){
	}
/* 
virtual senza corpo, pure virtual il figlio deve per forza implementarla
virtual definita puo' essere ridefinita , in questo modo il metodo specializzato della classe figlio puo' essere richiamato
anche se si ha un puntatore generico di tipo padre che punta alla classe specializzata
*/
	virtual void init()
	{
		_result = r_ok;

	}
	virtual int getStatus()
	{
		return _result;

	}
	virtual void begin()
	{
		_wake_up_time = millis();
		active=true;
	}

	virtual void update()
	{
		if (ready() && active)
		{
			_result |= r_running;
			run();
		}
		else
		{
			_result &= ~r_running;
		}

	}

	virtual void end()
	{
		_result &= ~r_running;
	}


	static void init(Module** modules)
	{
		while((*modules) != 0)
		{
			(*modules)->init();
			modules++;
		}
	};

	static void begin(Module** modules)
	{
		while((*modules) != 0)
		{
			(*modules)->begin();
			modules++;
		}
	};
	static void update(Module** modules)
	{
		while((*modules) != 0)
		{
			(*modules)->update();
			modules++;
		}
	};
	static void end(Module** modules)
	{
		while((*modules) != 0)
		{
			(*modules)->end();
			modules++;
		}
	};

        void runCb(){
          run();
        }
          int isExitMain()
        {
        	if(_result & r_exitMainLoop)
        		return 1;
        	return 0;
        }
protected:
	virtual bool ready()
	{
        /* return true if the module can run */
		return _wake_up_time <= millis();
	}
        /* in caso di pure virtual :
        virtual void run()=0;
        */
	virtual void run(){};
	void delay(unsigned long delay)
	{
		_wake_up_time = millis() + delay;
	}
	unsigned long _wake_up_time;
	byte _result;
	bool active;
};

#endif //__MODULE_H__
