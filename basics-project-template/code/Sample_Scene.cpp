/*
 * SAMPLE SCENE
 * Copyright © 2018+ Ángel Rodríguez Ballesteros
 *
 * Distributed under the Boost Software License, version  1.0
 * See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt
 *
 * angel.rodriguez@esne.edu
 */

#include "Sample_Scene.hpp"
#include <basics/Canvas>
#include <basics/Director>
#include <basics/Log>
#include <basics/Scaling>
#include <basics/Rotation>
#include <basics/Translation>

using namespace basics;
using namespace std;

namespace example
{

    Sample_Scene::Sample_Scene()
    {
        canvas_width  = 1280;
        canvas_height =  720;
    }

    bool Sample_Scene::initialize ()
    {
        gameController.initialize();


        return true;
    }
    void Sample_Scene::suspend ()
    {
        gameController.suspend();

    }

    void Sample_Scene::resume ()
    {
        gameController.resume();
    }

    void Sample_Scene::handle (Event & event)
    {
        gameController.handle(event);
    }

    void Sample_Scene::update (float time)
    {
        gameController.update(time);
    }

    void Sample_Scene::render (basics::Graphics_Context::Accessor & context)
    {
        Canvas * canvas = context->get_renderer< Canvas > (ID(canvas));

        if (!canvas)
        {
            canvas = Canvas::create (ID(canvas), context, {{ canvas_width, canvas_height }});
        }

        if (canvas)
        {

            canvas->clear        ();

            canvas->set_color    (1, 1, 1);

           /* canvas->draw_point   ({ 360, 360 });
            canvas->draw_segment ({   0,   0 }, { 1280, 720 });
            canvas->draw_segment ({   0, 720 }, { 1280,   0 });*/

            //arena.render(*canvas);
            gameController.render( canvas,canvas_width,canvas_height);

        }


    }


}
