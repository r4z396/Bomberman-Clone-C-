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


#include "Menu.hpp"
#include "Sample_Scene.hpp"
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

    Menu::Menu() {


    }




    void Menu::checkUIClicks() {


        //Si se pulsa el boton de Play se cambia de escena
        if(playButton.contains({touch_X,touch_Y})&&touching){
            director.run_scene (shared_ptr< Scene >(new Sample_Scene));
        }







    }

    bool Menu::initialize ()
    {
        state     = LOADING;
        suspended = false;

        Button playButton{};
        return true;
    }

    void Menu::loadUi() {




        //Damos posiciones y pasamos la textura del boton
        playButton.set_position(playButton_position);
        playButton.setTexture(texture_playButton);
        playButton.set_scale(1);


    }

    void Menu::load ()
    {
        if (!suspended)
        {
            Graphics_Context::Accessor context = director.lock_graphics_context ();

            if (context)
            {   //Carga de texturas del HUD
                texture_logo=Texture_2D::create (ID(logomain), context, "logo_main1.png");
                texture_loading = Texture_2D::create (ID(loading), context, "loading.png");
                texture_playButton = Texture_2D::create (ID(playbutton), context, "playButton.png");




                if (true)
                {

                    context->add (texture_loading);
                    context->add (texture_playButton);
                    context->add (texture_logo);

                    if (timer.get_elapsed_seconds () > 1.f)         // Si las texturas se han cargado muy rápido
                    {
                        state = RUNNING;}

                    }
            }
        }
    }

    void Menu::update (float time)
    {
        if(!suspended){
            switch (state)
            {
                case LOADING: load ();     break;
                case RUNNING: run  (time); break;

            }
        }



    }

    void Menu::run(float time){


        checkUIClicks();



    }

    void Menu::suspend ()
    {
        suspended = true;
    }

    void Menu::resume ()
    {
        suspended = false;
    }

    void Menu::render(basics::Graphics_Context::Accessor &context)
    {
        if (!suspended ) {

            Canvas * canvas = context->get_renderer< Canvas > (ID(canvas));

            if (!canvas)
            {
                canvas = Canvas::create (ID(canvas), context, {{ 1280, 720 }});
            }


            if (canvas) {


                canvas->clear();

                canvas->set_color(1, 1, 1);


                switch (state) {
                    case LOADING:
                        render_loading(*canvas);
                        break;
                    case RUNNING:
                        render_Menu(*canvas);
                        break;



                }



            }


        }
    }

    void Menu::render_loading (Canvas & canvas)
    {


        if (texture_loading)
        {
            canvas.fill_rectangle
                    (
                            { 1280 * .5f, 720 * .5f },
                            { texture_loading->get_width ()*2, texture_loading->get_height ()*2 },
                            texture_loading.get()
                    );


        }
    }



    void Menu::render_Menu(Canvas &canvas)
    {


        if (texture_logo&&texture_playButton)
        {
            canvas.fill_rectangle
                    (
                            { 1280*.5f, 500},
                            { texture_logo->get_width ()*2, texture_logo->get_height ()*2 },
                            texture_logo.get()
                    );
            loadUi();
            drawUi(canvas);
        }


    }

    void Menu::drawUi(Canvas & canvas){
        playButton.render(canvas);
    }

    void Menu::handle (Event & event)
    {

            switch (event.id)
            {

                case ID(touch-started):{


                        touching=true;
                        touch_X = *event[ID(x)].as< var::Float > ();
                        touch_Y = *event[ID(y)].as< var::Float > ();

                        playButton.set_position({touch_X,touch_Y});



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




