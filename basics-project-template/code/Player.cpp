/*
* SAMPLE SCENE
* Copyright � 2018+ �ngel Rodr�guez Ballesteros
*
* Distributed under the Boost Software License, version  1.0
* See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt
*52
* angel.rodriguez@esne.edu
*/


#include "Player.hpp"

#include <list>

//#include <basics/Log>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace basics;
using namespace example;
using namespace std;

namespace example
{


    Player::Player()

    {
        anchor   = basics::CENTER;

        position = { 500.f, 500.f };
        scale    = 2.f;
        speed    = { 0.f, 0.f };

        width_sprite=16;
        height_sprite=24;
        indiceX=0;
        indiceY=0;
        direction=Directions::Stop;
        lastDiretion=Directions::Down;
        haveSprite=true;
        visible=true;

    }







    void Player::setTextures( shared_ptr<basics::Texture_2D>  temp[],shared_ptr<basics::Texture_2D>  temp1[],shared_ptr<basics::Texture_2D>  temp2[],shared_ptr<basics::Texture_2D>  temp3[]){
        for (int i = 0; i <4 ; ++i) {
            //Añade texturas al array bidimensional
            for (int j = 0; j <3 ; ++j) {
                if(i==0){
                    textures[0][j]=temp[j];
                }
                if(i==1){
                    textures[1][j]=temp1[j];
                }
                if(i==2){
                    textures[2][j]=temp2[j];
                }
                if(i==3){
                    textures[3][j]=temp3[j];
                }

            }
        }
        size     = {width_sprite, height_sprite};
    }
    //Valida el movimiento anticipando el movimiento del jugador con los dos colliders en la posicion actual del jugador
    void Player::validateMove(int **temp) {
        int X,Y=0;
        for (int i = 0; i < filas; ++i) {
            X=0;
            for (int j = 0; j < columnas; ++j) {
                triggerMove.set_position({X,Y});
                triggerMove.set_size({40,40});
                if(temp[i][j]==1||temp[i][j]==3)
                {
                    if(CheckLR.intersects(triggerMove))
                        set_speed({0,0});
                    if(CheckUD.intersects(triggerMove))
                        set_speed({0,0});
                }
            X+=40;
            }
            Y+=40;
        }
    }
    //Renderiza el jugador
    void Player::renderPlayer(Canvas & canvas, int ** temp)
    {

        if (visible) {


            //Se posicionan los triggers de movimiento anticipando el movimiento
            CheckLR.set_position({get_position_x()-get_width()/2+get_speed_x()/2,get_position_y()-get_height()/2});
            CheckLR.set_size({(get_width()-4),(get_height()-15)});
            CheckUD.set_position({get_position_x()-get_width()/2,get_position_y()-get_height()/2+get_speed_y()/2});
            CheckUD.set_size({(get_width()-4),(get_height()-15)});
            CheckLR.render(canvas);
            CheckUD.render(canvas);
            //Validamos el movimiento
            validateMove(temp);
            canvas.fill_rectangle(position, size*scale,textures[indiceY][indiceX].get());
            //triggerMove.render(canvas);
        }



    }

    void Player::setDirection(Directions temp) {
        direction=temp;
    }
    /*
     * Metodo que recorre el spritesheet guardado en el array bidimensional
     * y añade velociad al jugador dependiendo de su direccion
     */
    void Player::movePlayer(Canvas & temp, int **tempArena) {

        switch (direction){

            case Directions::Up:{
                if(fpslimit>50){
                    indiceY=0;
                    if(indiceX>=0&&indiceX<2)
                        indiceX++;
                    else
                        indiceX=0;
                    fpslimit=0;
                } else
                    fpslimit++;
                set_speed_x(0);
                set_speed_y(player_Speed);
                lastDiretion=Up;
                break;
            }
            case Directions::Down:{
                if(fpslimit>50){

                indiceY=1;
                if(indiceX>=0&&indiceX<2)
                    indiceX++;
                else
                    indiceX=0;
                    fpslimit=0;
                } else
                    fpslimit++;
                set_speed_x(0);
                set_speed_y(-player_Speed);
                lastDiretion=Down;

                break;
            }
            case Directions::Right:{
                if(fpslimit>50){
                indiceY=2;
                if(indiceX>=0&&indiceX<2)
                    indiceX++;
                else
                    indiceX=0;
                    fpslimit=0;
                } else
                    fpslimit++;
                set_speed_x(-player_Speed);
                set_speed_y(0);
                lastDiretion=Right;
                break;
            }
            case Directions::Left:{
                if(fpslimit>50){
                indiceY=3;
                if(indiceX>=0&&indiceX<2)
                    indiceX++;
                else
                    indiceX=0;
                    fpslimit=0;
                } else
                    fpslimit++;
                set_speed_x(player_Speed);
                set_speed_y(0);
                lastDiretion=Left;


                break;
            }
            //Cambia el sprite dependineod de la ultima tecla pulsada
            case Directions ::Stop:{
                set_speed_x(0);
                set_speed_y(0);
                if(lastDiretion==Directions::Down){
                    indiceX=0;
                    indiceY=1;
                }
                if(lastDiretion==Directions::Up){
                    indiceX=0;
                    indiceY=0;
                }
                if(lastDiretion==Directions::Right){
                    indiceX=0;
                    indiceY=2;
                }
                if(lastDiretion==Directions::Left){
                    indiceX=0;
                    indiceY=3;
                }
                break;

            }


        }
        renderPlayer(temp,tempArena);
    }

}


