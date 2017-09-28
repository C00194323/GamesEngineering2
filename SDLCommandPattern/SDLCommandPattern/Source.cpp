// SDLTemplate.cpp : Defines the entry point for the console application.
//

#include <SDL.h>
#include <iostream>
#include <list>
using namespace std;

class Command {
public:
	virtual ~Command() {}
	virtual void execute() = 0;
	/*virtual void undo() = 0;
	virtual void redo()= 0;*/
protected:
	Command() {}
};
class JumpCommand : public Command
{
public:
	virtual void execute() { cout << "Jump Pressed" << endl; }
};

class FireCommand : public Command
{
	virtual void execute() { cout << "Fire Pressed" << endl; }
};

class InputHandler {
public:
	void handleInput(SDL_Event &event);
private:
	Command* buttonX_ = new FireCommand;
	Command* buttonY_ = new FireCommand;
	Command* buttonA_ = new JumpCommand;
	Command* buttonB_ = new JumpCommand;

};

void InputHandler::handleInput(SDL_Event &event)
{
	if (event.key.keysym.sym == SDLK_x) {
		buttonX_->execute();
	}
	else if (event.key.keysym.sym == SDLK_y) {
		buttonY_->execute();
	}
	else if (event.key.keysym.sym == SDLK_a) {
		buttonA_->execute();
	}
	else if (event.key.keysym.sym == SDLK_b) {
		buttonB_->execute();
	}
}

class MacroCommand : public Command {
public:
	MacroCommand() {}
	virtual ~MacroCommand() {}
	virtual void add(Command*);
	virtual void remove(Command*);
	virtual void execute();
	/*virtual void undo();
	virtual void redo();*/
private:
	list<Command*>* commands;
	list<Command*>*PrevCommand;
};

 
void MacroCommand::add(Command *c) {
	commands->push_back(c);
}
void MacroCommand::remove(Command *c)
{
	commands->remove(c);
}
void MacroCommand::execute() {
	list<Command*>::iterator i;
	for (i = commands->begin(); i != commands->end(); i++)
	{
		Command *c = *i;
		c->execute();
	}
}

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Hello Sean", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 800, SDL_WINDOW_SHOWN);
	InputHandler* input = new InputHandler;
	MacroCommand* macCommand = new MacroCommand;
	bool isRunning = true;

	SDL_Event event;
	while (isRunning)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				isRunning = false;
			}

			switch (event.type)
			{
			case SDL_KEYDOWN:
				input->handleInput(event);
			}
		}
	}
	SDL_Quit();
	return 0;
} 