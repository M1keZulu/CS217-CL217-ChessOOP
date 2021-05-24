#include<iostream>

using namespace std;

class Test{
	string test;
	public:
		Test(string t){
			test=t;
		}
		virtual string getTest(){
			return test;
		}
};

class Demo:public Test{
		public:
			Demo(string x):Test(x){
			}
};

class Hello{
	private:
		Test *ptr;
	public:
		Hello(){
			Demo d("Zain");
			ptr = new Test("Zain");
		}
		Test* getPoint(){
			return ptr;
		}
};

class AnothaOne{
	private:
		Hello h;
	public:
		void show(){
			cout<<h.getPoint()->getTest();
		}
};

int main(){
	AnothaOne a;
	a.show();
}
