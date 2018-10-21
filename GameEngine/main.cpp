#include <iostream>
#include "Engine.h"
#include "TechDemo.h"
using namespace std;

int main(int argc, char** argv)
{
	Engine().Start(make_shared<TechDemo>());
	return 1;
}