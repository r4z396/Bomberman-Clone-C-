#pragma once
#ifndef MENU_H
#define MENU_H

#include <basics/Scene>
#include <vector>
#include <basics/internal/Timer.hpp>
#include "Player.hpp"
#include "Arena.hpp"
#include "Menu.hpp"
#include "Button.hpp"


namespace example
{
    using namespace basics;
    using namespace std;

	class Menu: public basics::Scene
    {
        typedef std::shared_ptr< basics::Texture_2D > Texture_Handle;

	private:
        enum State
        {
            LOADING,
            RUNNING
        };

        State          state;
        bool           suspended;


		unsigned       canvas_width;
		unsigned       canvas_height;

		//UI


		Point2f playButton_position{640,200};




		Button playButton;




        Texture_Handle texture_logo;

        Texture_Handle texture_loading;

		Texture_Handle texture_playButton;


        Timer          timer;
	public:
        Menu();
        float touch_X;
        float touch_Y;
        bool touching;





        /**
         * Chequea colisiones del jugador con el HUD
         */
        void checkUIClicks();



        /**
         * Dibuja el HUD
         */
        void drawUi (Canvas & canvas);

        /**
         * Carga la interfaz de usuario
         */
		void loadUi ();

        /**
         * Controla que funciones se llaman cuando esta RUNNING
         */
        void run(float time);

        /**
         * Carga de sprites y de canvas
         */
        void load ();

        /**
         * Muestra el mensaje de  carga
         */
        void render_loading (Canvas & canvas);

        /**
         *Muestra el Menu de juego
         */
		void render_Menu (Canvas & canvas);

        /**
         * Este método lo llama Director para conocer la resolución virtual con la que está
         * trabajando la escena.
         * @return Tamaño en coordenadas virtuales que está usando la escena.
         */
		basics::Size2u get_view_size () override
		{
			return { canvas_width, canvas_height };
		}


        /**
         * Aquí se inicializan los atributos que deben restablecerse cada vez que se inicia la escena.
         * @return
         */
        bool initialize () override;

        /**
         * Este método lo invoca Director automáticamente cuando el juego pasa a segundo plano.
         */
        void suspend () override;

        /**
         * Este método lo invoca Director automáticamente cuando el juego pasa a primer plano.
         */
        void resume () override;

        /**
         * Este método se invoca automáticamente una vez por fotograma cuando se acumulan
         * eventos dirigidos a la escena.
         */
        void handle (basics::Event & event) override;

        /**
         * Este método se invoca automáticamente una vez por fotograma para que la escena
         * actualize su estado.
         */
        void update (float time) override;

        /**
         * Este método se invoca automáticamente una vez por fotograma para que la escena
         * dibuje su contenido.
         */
		void render     (basics::Graphics_Context::Accessor & context) override;


	};

}
#endif