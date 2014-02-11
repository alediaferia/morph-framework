#include "mstring.h"
#include "mnumber.h"
#include "mfile.h"

class Button : public MObject
{
    M_OBJECT(Button)
public:
    Button() : MObject(),
    M_SYNTHESIZE_PROPERTY(toggled)
    {
        registerInvokable(M_INVOKABLE0(Button, click));
    }

    ~Button()
    {
        std::cout << "Button dying" << std::endl;
    }

    M_INVOKABLE void click()
    {
        std::cout << "Clicked" << std::endl;

		_self->toggled = MNumber::alloc()->init((int)1);
    }

private:
    M_PROPERTY(mref, toggled)
};

class PrettierButton : public Button
{
	M_OBJECT(PrettierButton)
public:
	PrettierButton() : Button()
	{
		
	} 
};

int main(int argc, char **argv)
{
    mref button = Button::alloc();
    button->invokableByName("click")->invoke();
}
