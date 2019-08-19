#include<iostream>
#include<string>
using namespace std;
#pragma warning(disable: 4996) 

template<typename T>
T Add(T a, T b)
{
	return a + b;
}

template<>
const char * Add(const char * a, const char * b)
{
	char * temp = new char[strlen(a) + strlen(b) + 1];
	memset(temp, 0, sizeof(temp));

	strcpy(temp, a);

	strcat(temp, b);

	return temp;
}


int main()
{
	cout << Add<int>(2, 3) << endl;
	cout << Add<float>(2.5, 2.3) << endl;

	cout << Add<const char*>("addd","bcccc") << endl;

	return 0;
}