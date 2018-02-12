/*
* SAMPLE SCENE
* Copyright � 2018+ �ngel Rodr�guez Ballesteros
*
* Distributed under the Boost Software License, version  1.0
* See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt
*52
* angel.rodriguez@esne.edu
*/


#include "Dpad.hpp"


//#include <basics/Log>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


using namespace basics;
using namespace example;
using namespace std;


namespace example
{



    Dpad::Dpad() {


    }
    void Dpad::initialize(Point2f pos, Size2f siz) {
        position=pos;
        size=siz;
        iniPads();
    }


    void Dpad::iniPads(){
        //Inicializa botones
        Button up{};
        Button down{};
        Button left{};
        Button right{};
        position_left={get_position_x()-100,get_position_y()};
        position_right={get_position_x()+100,get_position_y()};
        position_down={get_position_x(),get_position_y()-100};
        position_up={get_position_x(),get_position_y()+100};

    }
    void Dpad::update(){
        //Asigna posiciones
        up.set_position(position_up);
        left.set_position(position_left);
        down.set_position(position_down
        );
        right.set_position(position_right);
    }
    void Dpad::render(Canvas & canvas) {
        //Renderiza los botones
        up.render(canvas);
        down.render(canvas);
        left.render(canvas);
        right.render(canvas);
    }

    int Dpad::checkDpadContains(Point2f temp) {
        //Chequea si alguno de los botnes contiene esa posiciones y la devulve
        if(up.contains(temp)){
            return 1;
        }
        else if(down.contains(temp)){
            return 2;

        } else if(right.contains(temp)){
            return 3;

        }else if(left.contains(temp)){
            return 4;

        }
        return 0;
    }
}


