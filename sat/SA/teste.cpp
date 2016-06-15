#include <ctime>
#include <cstdlib>
#include <iostream>

int main() 
{
     // use current time as seed for random generator
   	    std::srand(std::time(NULL));
    for (int j = 0; j < 20; ++j)
   	{
   
   		for (int i = 0; i < 20; ++i)
   	{

		int random_variable = std::rand() % 2;
    	std::cout << random_variable << ' ';
   	}
   	std::cout << '\n';
   	}
   	
    
              return 0;
}