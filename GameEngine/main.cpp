#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void main(int argc, char** argv)
{

	cout << "end";
	this_thread::sleep_for(chrono::seconds(1));
}