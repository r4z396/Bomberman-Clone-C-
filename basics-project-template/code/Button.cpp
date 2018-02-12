/*
* SAMPLE SCENE
* Copyright � 2018+ �ngel Rodr�guez Ballesteros
*
* Distributed under the Boost Software License, version  1.0
* See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt
*52
* angel.rodriguez@esne.edu
*/


#include "Button.hpp"


//#include <basics/Log>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


using namespace basics;
using namespace example;
using namespace std;


namespace example
{



    Button::Button() {
        anchor   = basics::CENTER;
        size     = { 100, 100 };
        position = { 100.f, 100.f };
        scale    = 1.f;
        haveSprite=false;
        sizeNEW=size*scale;
        visible  = true;
    }
    void Button::setTexture(shared_ptr<basics::Texture_2D> temp) {
        sprite=temp;
        haveSprite=true;
        size     = { temp.get()->get_width(), temp.get()->get_height() };
        sizeNEW=size*scale;
    }



    bool Button::contains (const Point2f & point) {

        float this_left = this->get_left_x ();

        if (point.coordinates.x () > this_left)
        {
            float this_bottom = this->get_bottom_y ();

            if (point.coordinates.y () > this_bottom)
            {
                float this_right = this_left + this->sizeNEW.width;

                if (point.coordinates.x () < this_right)
                {
                    float this_top = this_bottom + this->sizeNEW.height;

                    if (point.coordinates.y () < this_top)
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    void Button::render(Canvas & canvas)
    {



        //canvas.fill_rectangle({position.coordinates.x(),position.coordinates.y()},size);


        if (visible) {
            if(!haveSprite){
                canvas.draw_rectangle({position.coordinates.x()-size.width*scale/2,position.coordinates.y()-size.height*scale/2},size*scale);
            } else{
                canvas.fill_rectangle ({position.coordinates.x(),position.coordinates.y()}, size * scale, sprite.get(),anchor);
                //canvas.draw_rectangle(position,size*scale);
            }

        }

    }

}


