/*
* Copyright (c) 2006-2007 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

/* 
 * Base code for CS 296 Software Systems Lab 
 * Department of Computer Science and Engineering, IIT Bombay
 * Instructor: Parag Chaudhuri
 */

//! These are user defined include files
//! Included in double quotes - the path to find these has to be given at compile time
#include "render.hpp"
#include "cs296_base.hpp"
#include "callbacks.hpp"
#include "iostream"
//! GLUI is the library used for drawing the GUI
//! Learn more about GLUI by reading the GLUI documentation
//! Learn to use preprocessor diectives to make your code portable
#ifndef __APPLE__
#include "GL/glui.h"
#else
#include "GL/glui.h"
#endif

//! These are standard include files
//! These are usually available at standard system paths like /usr/include
//! Read about the use of include files in C++
#include <sys/time.h>



//! Notice the use of extern. Why is it used here?
namespace cs296
{
  extern int32 test_index;
  extern int32 test_selection;
  extern int32 test_count;
  extern cs296::sim_t* entry;
  extern cs296::base_sim_t* test;
  extern cs296::settings_t settings;
  extern const int32 frame_period;
  extern float settings_hz;
  extern int32 width;
  extern int32 height;
  extern int32 main_window;
};

//! This opens up the cs296 namespace
//! What is the consequence of opening up a namespace?
using namespace cs296;


//! This function creates all the GLUI gui elements
void create_glui_ui(void)
{}


//! This is the main function
int main(int argc, char** argv)
{
start :
  test_count = 1;
  test_index = 0;
  test_selection = test_index;
  
  entry = sim;
  test = entry->create_fcn();
  float32 t[4];
  for(int i=0;i<4;i++){
	  t[i]=0;
  }
  int iter=atoi(argv[1]);
  struct timeval tv;
  struct timezone tz;
  float32 strtsec,endsec,strtu,endu;
  
  gettimeofday(&tv,&tz);
  strtsec=(tv.tv_sec);
  strtu=(tv.tv_usec);
  
  for(int i=0;i<iter;i++){

	(*test).step(&settings);
	t[0]=t[0]+test->get_world()->GetProfile().step;
	t[1]=t[1]+test->get_world()->GetProfile().collide;
	t[2]=t[2]+test->get_world()->GetProfile().solveVelocity;
	t[3]=t[3]+test->get_world()->GetProfile().solvePosition;
  }
  gettimeofday(&tv,&tz);
  endsec=(tv.tv_sec);
  endu=(tv.tv_usec);
  float32 secdiff,udiff,diff;
  secdiff = (endsec-strtsec);
  udiff = (endu - strtu);
  diff = (secdiff * 1000.0) + (udiff / 1000.0);

  if(abs(t[0]/iter) > 5 || abs(t[1]/iter) > 5 || abs(t[2]/iter) > 5 || abs(t[0]/iter) > 5 || diff < 0 || diff > 20)
	goto start;
  
	std::cout.precision(5);
	std::cout << "Number of Iterations: " << iter << std::endl;
	std::cout << "Average time per step is " << std::fixed <<  t[0]/iter << " ms" << std::endl;
	std::cout << "Average time for collisions is " << std::fixed<<  t[1]/iter << " ms" << std::endl;
	std::cout << "Average time for velocity updates is " << std::fixed<<  t[2]/iter << " ms" << std::endl;
	std::cout << "Average time for position updates is " << std::fixed<<  t[3]/iter << " ms" << std::endl << std::endl;
	std::cout << "Total loop time is " << std::fixed<< diff << "ms" << std::endl;

 return 0;
}
