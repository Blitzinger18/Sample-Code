#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>

using namespace std;

class rectangle{
	private:
		int width;
		int height;
	public:
		rectangle(){}
		
		rectangle(int w, int h){
			width = w;
			height = h;
		}
		
		rectangle add(rectangle r){
			rectangle out;
			out.width = width + r.width;
			out.height = height + r.height;
			
			return out;
		}
		
		rectangle operator+(rectangle r){
			rectangle out;
			out.width = width + r.width;
			out.height = height + r.height;
			
			return out;
		}
		
		bool operator==(rectangle r){
			if((width == r.width) && (height == r.height))
				return true;
			else
				return false;
		}
		
		void print(){
			cout << width << " " << height << endl;
		}
};



int main(){

	rectangle r1(3,4);
	rectangle r2(5,7);
	
	rectangle r3 = r1.add(r2);
	
	rectangle r4 = r1 + r2;
	
	r3.print();
	r4.print();
	
	if(r3 == r4)
		cout << "r3 equals to r4" << endl;
	else
		cout << "re does not equal r4" << endl;



	return 0;
}
