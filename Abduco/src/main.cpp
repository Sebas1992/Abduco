/* 
 * File:   main.cpp
 * Author: sebas
 *
 * Created on 13 novembre 2017, 17:06
 */

#include<Application.h>


int main() {
    Application* app = new Application();
    app->run();
    delete app;
	return 0;
}

