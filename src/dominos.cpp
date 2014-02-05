/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
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


#include "cs296_base.hpp"
#include "render.hpp"

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include "GL/freeglut.h"
#endif

#include <cstring>
using namespace std;

#include "dominos.hpp"

namespace cs296
{
  /**  This is the constructor \n 
   * This is the documentation block for the constructor. \n
   * For the rest of the documentation we follow this convention \n
   * b2EdgeShape = \a variable_used_for_b2EdgeShape which itself is a \b shape datatype \n
   * fixture = \a variable_used_for_ b2FixtureDef_in_that_instance which itself is a \b fixture datatype \n
   */ 
  
  dominos_t::dominos_t()
  {
    b2Body* b1;  
    {
		/*! \b GROUND
		 * 
		 * Even ground body
		 * Static body
		 * b2EdgeShape = shape
         * fixture = none
         */ 
		     
      b2EdgeShape shape; 
      shape.Set(b2Vec2(-90.0f, 0.0f), b2Vec2(90.0f, 0.0f));
      b2BodyDef bd; 
      b1 = m_world->CreateBody(&bd); 
      b1->CreateFixture(&shape, 0.0f);
    }
             
    //horizontal shelf 1
    {
		/*! \b HORIZONTAL \b SHELF \b 1
		 * 
		 * Rectangular flat static body 
		 * position=(-31.0f,30.0f)
		 * b2EdgeShape = shape
         * fixture = none*/
      b2PolygonShape shape;
      shape.SetAsBox(6.0f, 0.25f);
	
      b2BodyDef bd;
      bd.position.Set(-31.0f, 30.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }

    //Dominos set 1
    {
		/*! \b DOMINOS \b SET \b 1
		 * 
		 * Series (10 in this case) of small rectangular dynamic bodies(0.1f x 1.0f) seperated by small distance (< 1.0f)
		 * Dynamic  objects 
		 * b2EdgeShape = shape
         * fixture = fd*/
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 1.0f);
	
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 20.0f;
      fd.friction = 0.1f;
      fd.restitution = 0.0f;
		
      for (int i = 0; i < 10; ++i)
	{
	  b2BodyDef bd;
	  bd.type = b2_dynamicBody;
	  bd.position.Set(-35.5f + 1.0f * i, 31.25f);
	  b2Body* body = m_world->CreateBody(&bd);
	  body->CreateFixture(&fd);
	}
    }
      
    //horizontal shelf 2
    {
		/*! \b HORIZONTAL \b SHELF \b 2
		 * 
		 * position : (1.0f , 6.0 f)
		 * Static body 
		 * b2EdgeShape = shape
         * fixture = bd*/
      b2PolygonShape shape;
      shape.SetAsBox(7.0f, 0.25f, b2Vec2(-20.f,20.f), 0.0f);
	
      b2BodyDef bd;
      bd.position.Set(1.0f, 6.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }


    //The pendulum that knocks the dominos off
    {
		//!\b PENDULUM \b SETUP
		  
		/*! b2:
		 * 
		 * Rectangular vertical box under the 'horizontal shelf 1'
		 * Static body
		 * b2EdgeShape = shape
         * fixture = bd
		 */ 
		/*! b4:
		 * 
		 * The bob(moving mass of the pendulum)
		 * shape:square(0.25f x 0.25f)
		 * b2EdgeShape = shape
         * b2BodyDef = bd
         * fixture = none
		 */ 
		/*! anchor :
		 * 
		 * the rigid point where the thread of the bob is connected to the pole from b2
		 */  
		/*! jd:
		 * 
		 * the revolute joint between b2,b4,anchor
		 */
      b2Body* b2;
      {
	b2PolygonShape shape;
	shape.SetAsBox(0.25f, 1.5f);
	  
	b2BodyDef bd;
	bd.position.Set(-36.5f, 28.0f);
	b2 = m_world->CreateBody(&bd);
	b2->CreateFixture(&shape, 10.0f);
      }
	
      b2Body* b4;
      {
	b2PolygonShape shape;
	shape.SetAsBox(0.25f, 0.25f);
	  
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(-40.0f, 33.0f);
	b4 = m_world->CreateBody(&bd);
	b4->CreateFixture(&shape, 2.0f);
      }
	
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(-37.0f, 40.0f);
      jd.Initialize(b2, b4, anchor);
      m_world->CreateJoint(&jd);
    }
      
    //The train of small spheres
    {
		/*! \b THE \b TRAIN \b OF \b SMALL \b SPHERES 
		 * 
		 * A series of dynamic circles(with radius=0.5f) which are in contact with one another on the surface of horizontal shelf 2
		 * Circles are inelastic and frictionless
		 * b2CircleShape = circle
         * fixture = ballfd*/
      b2Body* spherebody;
	
      b2CircleShape circle;
      circle.m_radius = 0.5;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 1.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
	
      for (int i = 0; i < 10; ++i)
	{
	  b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(-22.2f + i*1.0, 26.6f);
	  spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);
	}
    }

    //The pulley system
    {
		//! \b PULLEY \b SYSTEM:
		  
		/*! OPEN BOX:
		 *
		 * Dynamic 2d box anolgy
		 * FD1, FD2, FD3: combination of vertical, horizontal rectangles put together to form the 'openbox'
		 * density =  10.0 
		 * b2BodyDef* = bd
         * b2FixtureDef* = fd1,fd2,fd3
         * b2Body* = box1 
		 * restitution :inelastic (for the balls not to bounce back once they hit the base of the openbox)
		 */ 
      b2BodyDef *bd = new b2BodyDef;
      bd->type = b2_dynamicBody;
      bd->position.Set(-10,15);
      bd->fixedRotation = true;
      
      //The open box
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 10.0;
      fd1->friction = 0.5;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(2,0.2, b2Vec2(0.f,-1.9f), 0);
      fd1->shape = &bs1;
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 10.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(0.2,2, b2Vec2(2.0f,0.f), 0);
      fd2->shape = &bs2;
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 10.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(0.2,2, b2Vec2(-2.0f,0.f), 0);
      fd3->shape = &bs3;
       
      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);

      //The bar
        /*! BAR:
         * 
         * pulley-counterweight for the openbox
         * Simple horizontal rectangular dynamic block 
         * density : 34.0 (to exactly balance the 'openblock + train of spheres' system
         */
      bd->position.Set(10,15);	
      fd1->density = 34.0;	  
      b2Body* box2 = m_world->CreateBody(bd);
      box2->CreateFixture(fd1);

      // The pulley joint
        /*! PULLEY JOINT:
         * 
         * an instance of 'b2PulleyJoint'
         */
        /*! \a variables used: 
         */
      b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      b2Vec2 worldAnchorOnBody1(-10, 15); //!     \li \a worldAnchorOnBody1 : Anchor point on body 1 in world axis
      b2Vec2 worldAnchorOnBody2(10, 15); //!     \li \a worldAnchorOnBody2 : Anchor point on body 2 in world axis
      b2Vec2 worldAnchorGround1(-10, 20); //!      \li \a worldAnchorGround1 : Anchor point for ground 1 in world axis
      b2Vec2 worldAnchorGround2(10, 20); //!     \li \a worldAnchorGround2 : Anchor point for ground 2 in world axis
      float32 ratio = 1.0f; 
      /*!     \a ratio : 
       * 
       * ratio determines the relation between the rates at which the objects on both sides move vertically 
       *
       */
      
      myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);
      m_world->CreateJoint(myjoint);
    }

     //! \b THE \b REVOLVING \b HORIZONTAL \b PLATFORM \b 1
      
        /*! body:
         *
         * Dynamic rectangular block(2.2f x 0.2f)
         * fixture* = fd
         * position : (14.0f,14.0f)
         */
        /*! body2:
         *
         * static object
         * used for 'body' remain in its place
         */
        /*! jointDef:
         *
         * revolutejoint joining body,body2
         */
    {
      b2PolygonShape shape;
      shape.SetAsBox(2.2f, 0.2f);
	
      b2BodyDef bd;
      bd.position.Set(14.0f, 14.0f);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);

 //     b2PolygonShape shape2;
 //    shape2.SetAsBox(0.2f, 2.0f);
      b2BodyDef bd2;
      bd2.position.Set(14.0f, 16.0f);
      b2Body* body2 = m_world->CreateBody(&bd2);

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
    }

        /*! \b THE \b HEAVY \b SPHERE \b ON \b THE \b PLATFORM
         * 
         * Dynamic circle 
         * radius = 1.0
         * density=50.0f
         * b2CircleShape = circle
         * fixture = ballfd
         * inelastic,frictionless
         */
    {
      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 1.0;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 50.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(14.0f, 18.0f);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
    }


    //! \b SEE-SAW \b SYSTEM
    {
       /*! TRIANGLE WEDGE
        * 
        * Static triangular body 
        * vertices: vertices of the triangle[(-1f,0f),(1f,0f),(0f,1.5f)]
        * b2PolygonShape = poly
        * fixture = wedgefd*/

      b2Body* sbody;
      b2PolygonShape poly;
      b2Vec2 vertices[3];
      vertices[0].Set(-1,0);
      vertices[1].Set(1,0);
      vertices[2].Set(0,1.5);
      poly.Set(vertices, 3);
      b2FixtureDef wedgefd;
      wedgefd.shape = &poly;
      wedgefd.density = 10.0f;
      wedgefd.friction = 0.0f;
      wedgefd.restitution = 0.0f;
      b2BodyDef wedgebd;
      wedgebd.position.Set(30.0f, 0.0f);
      sbody = m_world->CreateBody(&wedgebd);
      sbody->CreateFixture(&wedgefd);

      /*!PLANK ON THE WEDGE
       * 
       * Long rectangular plank(30.0f x 0.2f) with centre of mass just above the tip of the triangular wedge
       * Dynamic body
       * b2PolygonShape = shape
       * fixture* = fd2
       */
      b2PolygonShape shape;
      shape.SetAsBox(15.0f, 0.2f);
      b2BodyDef bd2;
      bd2.position.Set(30.0f, 1.5f);
      bd2.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd2);
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 1.f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape;
      body->CreateFixture(fd2);
      /*! jd:
       * 
       * revolutejoint joining triangle wedge and the plank
       */
      b2RevoluteJointDef jd; 
      b2Vec2 anchor;
      anchor.Set(30.0f, 1.5f);
      jd.Initialize(sbody, body, anchor);
      m_world->CreateJoint(&jd);

      /*! \b THE \b LIGHT \b BOX \b ON \b THE \b RIGHT \b SIDE \b OF \b THE \b SEE-SAW
       * 
       * SQUARE BOX(4f x 4f)
       * density:0.01f
       * position(40.0f,2.0f)[ie., to the right of the triangle wedge]
       * b2PolygonShape = shape2
       * fixture* = fd3*/
      b2PolygonShape shape2;
      shape2.SetAsBox(2.0f, 2.0f);
      b2BodyDef bd3;
      bd3.position.Set(40.0f, 2.0f);
      bd3.type = b2_dynamicBody;
      b2Body* body3 = m_world->CreateBody(&bd3);
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 0.01f;
      fd3->shape = new b2PolygonShape;
      fd3->shape = &shape2;
      body3->CreateFixture(fd3);
    }
      /*! \b HORIZONTAL \b SHELF \b 3
       * 
	   * Rectangular flat static body(20.0f x 0.5f) 
	   * position=(-10.0f,7.0f)
	   * b2PolygonShape = shape
       * fixture = none*/
    {
      b2PolygonShape shape;
      shape.SetAsBox(10.0f, 0.25f);
	
      b2BodyDef bd;
      bd.position.Set(-10.0f, 7.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    //! \b THE \b REVOLVING \b HORIZONTAL \b PLATFORM \b 2
      /*! body:
       * 
       * Dynamic rectangular block(3.0f x 0.4f)
       * position : (-13.2f,10.3f)
       * b2PolygonShape = shape
       * fixture = bd
       */
      /*! body2:
       * 
       * static object
       * used for 'body' remain in its place
       * position : (-13.2f,10.3f)
       */
      /*! jointDef:
       *
       * revolutejoint joining body,body2
       */ 
     {
       b2PolygonShape shape;
      shape.SetAsBox(1.5f, 0.2f);
	
      b2BodyDef bd;
      bd.position.Set(-13.2f, 10.3f);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      fd->restitution=1.0f;
      body->CreateFixture(fd);

      b2BodyDef bd2;
      bd2.position.Set(-13.2f, 10.3f);
      b2Body* body2 = m_world->CreateBody(&bd2);

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
    }
    //! \b THE \b REVOLVING \b HORIZONTAL \b PLATFORM \b 3
     
      /*! body:
       *
       * Dynamic rectangular block(4.4f x 0.4f)
       * position : (-6.0f,10.0f)
       */
      /*! body2:
       * 
       * Static object
       * used for 'body' remain in its place
       * position : (-6.0f,10.0f)
       */
      /*! jointDef:
       *
       * revolutejoint joining body,body2
       */
    {
      b2PolygonShape shape;
      shape.SetAsBox(2.2f, 0.2f);
	
      b2BodyDef bd;
      bd.position.Set(-6.0f, 10.3f);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.f;
      fd->restitution=1.0f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);

      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 2.0f);
      b2BodyDef bd2;
      bd2.position.Set(-5.7f, 10.3f);
      b2Body* body2 = m_world->CreateBody(&bd2);

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
  }
      /*! \b LIGHT \b BALL
       * 
       * Circle shaped dynamic object
       * frictionless,elastic
       * position:(-6.0f,8.0f)[just above the horizontal platform 3]
       * b2CircleShape = circle
       * fixture = ballfd*/
     {
      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 0.8;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 0.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(-6.0f, 8.0f);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
    }
      /*! \b DOMINOS \b SET \b 2
	   * 
	   * Series (5 in this case) of small rectangular dynamic bodies(0.1f x 1.0f) separated by small distance (0.7f < 1.0f)
	   * dynamic  objects
	   * b2PolygonShape = shape
       * fixture = fd */   {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 1.0f);
	
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 5.0f;
      fd.friction = 0.1f;
      fd.restitution = 0.0f;
		
      for (int i = 0; i < 5; ++i)
	{
	  b2BodyDef bd;
	  bd.type = b2_dynamicBody;
	  bd.position.Set(-15.5f + 0.7f * i, 8.25f);
	  b2Body* body = m_world->CreateBody(&bd);
	  body->CreateFixture(&fd);
	}
    }
  }

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
