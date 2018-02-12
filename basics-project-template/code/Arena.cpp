/*
* SAMPLE SCENE
* Copyright � 2018+ �ngel Rodr�guez Ballesteros
*
* Distributed under the Boost Software License, version  1.0
* See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt
*52
* angel.rodriguez@esne.edu
*/


#include "Arena.hpp"


//#include <basics/Log>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


using namespace basics;
using namespace example;
using namespace std;


namespace example
{



    Arena::Arena()
    {
        //Pared
        pared.sizeY=40;
        pared.sizeX=pared.sizeY;
        //Pared Destruible
        pared_destruible.sizeY=40;
        pared_destruible.sizeX=pared_destruible.sizeY;
        srand (time(NULL));

        generateMap();




    }
    void Arena::generateMap(){

        matriz= new int*[filas];
        for(int i=0;i<filas;i++){
            matriz[i]= new int[columnas];

        }
        for (int i = 0; i <filas ; ++i) {
            for (int j = 0; j < columnas; ++j) {
                //1==Wall
                //2==
                //0==
                //Bordes de mapa
                if(i==0||j==0||i==filas-1||j==columnas-1){
                    matriz[i][j]=1;

                }
                else{
                    //Bloques fijos
                    if((i%2==0)&&(j%2==0)){
                        matriz[i][j]=1;
                    }else{
                        //Cesped
                        if((i==1&&(j==1||j==2))||(j==1&&i==2)||(i==filas-2&&(j==columnas-3||j==columnas-2))||(i==filas-3&&j==columnas-2)){
                            matriz[i][j]=0;
                        }else
                        {
                            //Aleatorio
                            matriz[i][j]=rand()%2+2 ;

                        }

                    }

                }
            }
        }
        matriz[1][1]=0;
    }
    void Arena::setTextures( shared_ptr<basics::Texture_2D>  paredtemp,shared_ptr< basics::Texture_2D > pared_desttuible,shared_ptr< basics::Texture_2D > cesped){
        texture_pared=paredtemp;
        texture_pared_destruible=pared_desttuible;
        texture_cesped=cesped;

    }
    void Arena::render(Canvas &canvas) {
        //Cesped
        float X=0,Y=0;
        for (int i = 0; i <filas ; ++i) {
            for (int j = 0; j < columnas; ++j) {

                   if(matriz[i][j]==0||matriz[i][j]==2){
                        canvas.fill_rectangle({X,Y},{pared_destruible.sizeX,pared_destruible.sizeY},texture_cesped.get());

                    }

                X=X+pared.sizeX;
            }
            X=0;
            Y=Y+pared.sizeY;
        }
        X=0,Y=0;
        for (int i = 0; i <filas ; ++i) {
            for (int j = 0; j < columnas; ++j) {
                if(matriz[i][j]==1){

                    //canvas.draw_rectangle(X,Y,pared.sizeX,pared.sizeY);
                    //canvas.draw_rectangle({X,Y},{pared.sizeX,pared.sizeY});
                    canvas.fill_rectangle({X,Y},{pared.sizeX,pared.sizeY},texture_pared.get());

                }
                else {
                    if(matriz[i][j]==3){
                        //renderer.draw_rectangle(X+pared_destruible.sizeX/2,Y+pared_destruible.sizeY/2,pared_destruible.sizeX,pared_destruible.sizeY);
                        //canvas.draw_rectangle({X+pared_destruible.sizeX/2,Y+pared_destruible.sizeY/2},{pared_destruible.sizeX,pared_destruible.sizeY});
                        canvas.fill_rectangle({X,Y},{pared_destruible.sizeX,pared_destruible.sizeY},texture_pared_destruible.get());
                    }

                }
                X=X+pared.sizeX;
            }
            X=0;
            Y=Y+pared.sizeY;
        }
    }

}


