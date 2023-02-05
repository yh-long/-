#include <iostream>
using namespace std;
class hello
{
public:
	hello();
};

hello::hello()
{
	system("echo off");
	system("color f2");
	cout << "hello world" << endl;
}