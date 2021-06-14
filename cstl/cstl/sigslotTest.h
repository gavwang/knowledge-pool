#include "sigslot.h"
using namespace sigslot;  

class Switch
{
public:
	signal0<> Clicked;
	//这里的信号是不带参数的，signaln表示带几个参数
};

class Light : public has_slots<>
{
public:
	Light(bool state){b_state = state;Displaystate();}
	void ToggleState(){b_state = !b_state;Displaystate();} //作为消息的响应
	void TurnOn(){b_state = true;Displaystate();}
	void TurnOff(){b_state = false;Displaystate();}
	void Displaystate(){cout<<"The state is "<<b_state<<endl;}
private:
	bool b_state;
};

void sigslotTest()
{
	Switch sw1, sw2,all_on,all_off;
	Light lp1(TRUE), lp2(FALSE);
	sw1.Clicked.connect(&lp1,&Light::ToggleState); //绑定
	sw2.Clicked.connect(&lp2,&Light::ToggleState);
	all_on.Clicked.connect(&lp1,&Light::TurnOn);
	all_on.Clicked.connect(&lp2,&Light::TurnOn);
	all_off.Clicked.connect(&lp1,&Light::TurnOff);
	all_off.Clicked.connect(&lp2,&Light::TurnOff);

	sw1.Clicked();
	sw2.Clicked();
	all_on.Clicked();
	all_off.Clicked();

	sw1.Clicked.disconnect(&lp1);
	sw2.Clicked.disconnect(&lp2);
	all_on.Clicked.disconnect(&lp1);
	all_on.Clicked.disconnect(&lp2);
	all_off.Clicked.disconnect(&lp1);
	all_off.Clicked.disconnect(&lp2);
}