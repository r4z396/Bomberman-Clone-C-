/*
* SAMPLE SCENE
* Copyright © 2018+ Ángel Rodríguez Ballesteros
*
* Distributed under the Boost Software License, version  1.0
* See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt
*52
* angel.rodriguez@esne.edu
*/


#include "GameObject.hpp"


//#include <basics/Log>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


using namespace basics;
using namespace example;
using namespace std;


namespace example
{


    GameObject::GameObject(Texture_2D * texture)
            :
            sprite (texture)

	{

        anchor   = basics::CENTER;
        size     = { texture->get_width (), texture->get_height () };
        position = { 0.f, 0.f };
        scale    = 1.f;
        speed    = { 0.f, 0.f };
        visible  = true;
        haveSprite=true;


	}
    GameObject::GameObject()
    {

        anchor   = basics::CENTER;
        size     = { 10,10};
        position = { 0.f, 0.f };
        scale    = 1.f;
        speed    = { 0.f, 0.f };
        visible  = true;
        haveSprite=false;


    }

    bool GameObject::intersects (const GameObject & other)
    {
        // Se determinan las coordenadas de la esquina inferior izquierda y de la superior derecha
        // de este sprite:

        float this_left    = this->get_left_x   ();
        float this_bottom  = this->get_bottom_y ();
        float this_right   = this_left   + this->size.width;
        float this_top     = this_bottom + this->size.height;

        // Se determinan las coordenadas de la esquina inferior izquierda y de la superior derecha
        // del otro sprite:

        float other_left   = other.get_left_x   ();
        float other_bottom = other.get_bottom_y ();
        float other_right  = other_left   + other.size.width;
        float other_top    = other_bottom + other.size.height;

        // Se determina si los rectángulos envolventes de ambos sprites se solapan:

        return !(other_left >= this_right || other_right <= this_left || other_bottom >= this_top || other_top <= this_bottom);
    }

    bool GameObject::contains (const Point2f & point)
    {
        float this_left = this->get_left_x ();

        if (point.coordinates.x () > this_left)
        {
            float this_bottom = this->get_bottom_y ();

            if (point.coordinates.y () > this_bottom)
            {
                float this_right = this_left + this->size.width;

                if (point.coordinates.x () < this_right)
                {
                    float this_top = this_bottom + this->size.height;

                    if (point.coordinates.y () < this_top)
                    {
                        return true;
                    }
                }
            }
        }

        return false;
    }


}


