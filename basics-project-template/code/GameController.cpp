/*
 *
 * +-f5crrrrr
* SAMPLE SCENE
* Copyright � 2018+ �ngel Rodr�guez Ballesteros
*
* Distributed under the Boost Software License, version  1.0
* See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt
*52
* angel.rodriguez@esne.edu
*/


#include "GameController.hpp"
#include <algorithm>

//#include <basics/Log>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <basics/Director>
#include <basics/Canvas>
#include <basics/Director>
#include <basics/Log>
#include <basics/Scaling>
#include <basics/Rotation>
#include <basics/Translation>
using namespace basics;
using namespace example;
using namespace std;

namespace example {

    GameController::GameController() {
        /*item=GameObject{};
        item.set_size({100,100});
        player = Player{};
        player.setGameController(this);
        start();*/


    }

    void GameController::start() {
        GameFinished = false;
    }

    void GameController::restart() {
        GameFinished = false;

        //start();
        //player.setPositionX(0);
        //player.setPositionY(0);
    }


    void GameController::checkUIClicks() {

        //Se chekea si el usuario a clickeado en el Dpad y se clasifica dependiendo de la accion
        if(true){
            int dpadMove=dpadUI.checkDpadContains({touch_X,touch_Y});
            switch (dpadMove){
                case 1:{//Up
                    player.setDirection(player.Up);
                    break;
                }
                case 2:{//Down
                    player.setDirection(player.Down);
                    break;
                }
                case 3:{//Left
                    player.setDirection(player.Left);
                    break;
                }
                case 4:{//Right
                    player.setDirection(player.Right);
                    break;
                }
                case 0:{//Stop
                    player.setDirection(player.Stop);
                    break;
                }
            }
        }
        //Cheuqa si se ha clikeado el boton de pause
        if(pauseButton.contains({touch_X,touch_Y})&&touching){
            if(state==RUNNING) {
                GamePaused=true;
                state = PAUSED;
            }
        }
        //Chequea si ha clikeado el boton de ayuda
        if(helpButton.contains({touch_X,touch_Y})){
            if(state==RUNNING) {
                GamePaused=true;
                state = HELP;
            }
        }





    }

    bool GameController::initialize ()
    {
        //Se inicializan los estado del juego
        state     = LOADING;
        suspended = false;

        //Botones
        Button pauseButton{};
        Button helpButton{};

        //Datos del jugador
        player.setSpeed(player_Speed);
        player.set_position({50,50});
        player.setFilas(arena.getFilas());
        player.setColumnas(arena.getColumnas());

        x         = 640;
        y         = 360;



        return true;
    }

    void GameController::loadUi() {
        //Se incializa las posiciones de los botones y su tamaño
        dpadUI.initialize(dpad_position,dpad_size);
        pauseButton.set_position(pauseButton_position);
        pauseButton.set_scale(0.2);
        helpButton.set_position(helpButton_position);
        helpButton.set_scale(0.2);
    }

    void GameController::load ()
    {
        if (!suspended)
        {
            Graphics_Context::Accessor context = director.lock_graphics_context ();

            if (context)
            {   //Carga de texturas jugador
                textures_up[0]= Texture_2D::create (ID(arriba1), context, "arriba1.png");
                textures_up[1]= Texture_2D::create (ID(arriba2), context, "arriba2.png");
                textures_up[2]= Texture_2D::create (ID(arriba3), context, "arriba3.png");

                textures_down[0]= Texture_2D::create (ID(abajo1), context, "abajo1.png");
                textures_down[1]= Texture_2D::create (ID(abajo2), context, "abajo2.png");
                textures_down[2]= Texture_2D::create (ID(abajo3), context, "abajo3.png");

                textures_left[0]= Texture_2D::create (ID(izquierda1), context, "izquierda1.png");
                textures_left[1]= Texture_2D::create (ID(izquierda2), context, "izquierda2.png");
                textures_left[2]= Texture_2D::create (ID(izquierda3), context, "izquierda3.png");

                textures_right[0]= Texture_2D::create (ID(derecha1), context, "derecha1.png");
                textures_right[1]= Texture_2D::create (ID(derecha2), context, "derecha2.png");
                textures_right[2]= Texture_2D::create (ID(derecha3), context, "derecha3.png");



                //Carga de texturas del HUD
                texture_dpad=Texture_2D::create (ID(dpadid), context, "dpad.png");
                texture_loading = Texture_2D::create (ID(loading), context, "loading.png");
                texture_pause = Texture_2D::create (ID(pause), context, "pause.png");
                texture_help = Texture_2D::create (ID(help), context, "help.png");
                texture_pauseButton = Texture_2D::create (ID(puaseB), context, "pauseButton.png");
                texture_helpButton = Texture_2D::create (ID(helpB), context, "helpButton.png");
                //Carga de Textura de objetos
                texture_cesped=Texture_2D::create (ID(cesped), context, "cesped.png");
                texture_pared=Texture_2D::create (ID(pared), context, "pared.png");
                texture_pared_destruible=Texture_2D::create (ID(pared_destruible), context, "pared_destruible.png");
                //Carga de texturas del Dpad
                texture_dpad=Texture_2D::create (ID(dpadid), context, "dpad.png");
                texture_player=Texture_2D::create (ID(jugador), context, "Jugador.png");


                //Se comprueban si se han cargado correctamente y se añade al contexto de la app
                if (texture_helpButton&&texture_pauseButton&&texture_pause&&texture_help&&texture_loading&&texture_cesped&&texture_pared&&texture_pared_destruible&&texture_player&&texture_dpad)
                {
                    for(int i=0;i<3;i++){
                        context->add(textures_up[i]);
                        context->add(textures_down[i]);
                        context->add(textures_left[i]);
                        context->add(textures_right[i]);
                    }
                    context->add (texture_loading);
                    context->add (texture_help);
                    context->add (texture_helpButton);
                    context->add (texture_pause);
                    context->add (texture_pauseButton);
                    context->add(texture_pared);
                    context->add(texture_pared_destruible);
                    context->add(texture_cesped);
                    context->add(texture_dpad);
                    context->add(texture_player);

                    //Setters para añadir la texturas a GameObjects
                    player.setTextures(textures_up,textures_down,textures_left,textures_right);
                    arena.setTextures(texture_pared,texture_pared_destruible,texture_cesped);
                    helpButton.setTexture(texture_helpButton);
                    pauseButton.setTexture(texture_pauseButton);



                    if (timer.get_elapsed_seconds () > 1.f)         // Si las texturas se han cargado muy rápido
                    {
                        state = RUNNING;}

                    }
            }
        }
    }


    void GameController::update (float time)
    {
        if(!suspended){
            switch (state)
            {
                case LOADING: load ();     break;
                case RUNNING: run  (time); break;
                    //case PAUSED:break;
                    //case HELP:break;
            }
        }



    }

    void GameController::run(float time){
        GamePaused=false;
        player.update(time);
        dpadUI.update();
        checkUIClicks();
    }






    void GameController::suspend ()
    {
        suspended = true;
    }

    void GameController::resume ()
    {
        suspended = false;
    }

    void GameController::render (Canvas * canvas, unsigned canvas_width,unsigned canvas_height)
    {
        if (!suspended ) {


            if (canvas) {


                canvas->clear();

                canvas->set_color(1, 1, 1);

                //Dependiendo del estado actual de la aplicacion se llama a diferentes renders
                switch (state) {
                    case LOADING:
                        render_loading(*canvas);
                        break;
                    case RUNNING:
                        render_arena(*canvas);
                        break;
                    case PAUSED:
                        render_paused(*canvas);
                        break;
                    case HELP:
                        render_help(*canvas);
                        break;


                }
                //Carga el HUD y lo muestra
                loadUi();
                drawUi(*canvas);


            }
        }
    }

    void GameController::render_loading (Canvas & canvas)
    {
        //Render de la pantalla de carga

        if (texture_loading)
        {
            canvas.fill_rectangle
                    (
                            { 1280 * .5f, 720 * .5f },
                            { texture_loading->get_width (), texture_loading->get_height () },
                            texture_loading.get()
                    );
        }
    }

    void GameController::render_paused (Canvas & canvas)
    {
        //Render de la pantalla de pausa

        if (texture_pause)
        {
            //render_arena(canvas);
            canvas.fill_rectangle
                    (
                            { 1280 * .5f, 720 * .5f },
                            { texture_pause->get_width (), texture_pause->get_height () },
                            texture_pause.get()
                    );

        }
    }

    void GameController::render_help (Canvas & canvas)
    {

        //Render de la pantalla de ayuda
        if (texture_help)
        {
            //render_arena(canvas);
            canvas.fill_rectangle
                    (
                            { 200, 720 * .5f },
                            { texture_help->get_width (), texture_help->get_height () },
                            texture_help.get()
                    );

        }
    }

    void GameController::render_arena (Canvas & canvas)
    {
        //Render de la pantalla de juego

        arena.render(canvas);
        player.movePlayer(canvas,arena.getArena());
        //item.render(canvas);



    }

    //Dibuja el HUD
    void GameController::drawUi(Canvas & canvas){
        pauseButton.render(canvas);
        helpButton.render(canvas);
        dpadUI.render(canvas);
        canvas.fill_rectangle(dpadUI.get_position(),dpadUI.get_size(),texture_dpad.get());

    }


    void GameController::handle (Event & event)
    {

            switch (event.id)
            {

                case ID(touch-started):{


                        touching=true;
                        touch_X = *event[ID(x)].as< var::Float > ();
                        touch_Y = *event[ID(y)].as< var::Float > ();


                    if(GamePaused){
                        state=RUNNING;

                        GamePaused=false;
                    }


                    break;
                }
                case ID(touch-moved):{

                    break;
                }
                case ID(touch-ended):
                {

                        touching=false;

                        touch_X= 0;
                        touch_Y= 0;



                    break;
                }
            }

    }
}




