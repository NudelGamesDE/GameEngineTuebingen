#include <iostream>
#include <thread>
#include <chrono>
#include "Engine.h"
#include "TechDemo.h"
using namespace std;

int main(int argc, char** argv)
{
	Engine().Start(Game_ptr(new TechDemo()));

	cout << "end";
	this_thread::sleep_for(chrono::seconds(1));
	return 1;
}