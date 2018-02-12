#pragma once
#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <basics/Scene>
#include <vector>
#include <basics/internal/Timer.hpp>
#include "Player.hpp"
#include "Arena.hpp"
#include "Dpad.hpp"


namespace example
{
    using namespace basics;
    using namespace std;

	class GameController
    {
        typedef std::shared_ptr< basics::Texture_2D > Texture_Handle;

	private:
        enum State
        {
            LOADING,///<Carga de juego
            RUNNING,///<Juego actuivo
			PAUSED,///<Pausado
			HELP///<Ayuda
        };
        //Estado en el cuals e encuentra el juego
        State          state;
        bool           suspended;

		//Player
        Player player = Player();
		float player_Speed=25;

		//UI
		//DPAD
		Size2f dpad_size{300,300};
		Point2f dpad_position{1100,200};
        Dpad dpadUI;	///<Dpad para controlar el movimeinto del jugador a su vez esta compueso por Buttons
		Point2f pauseButton_position{1100,620};
		Point2f helpButton_position{900,620};
		Button pauseButton;	///<Boton de pause
        Button helpButton;  ///<Boton de Ayuda

		float          x, y;

        //Player
		float playerSpeedX=40;
        float playerSpeedY=40;
        float playerSizeX=0.5;
        float playerSizeY=0.5;
        /*
         * SharedPtr de texturas del juego
         */
        Texture_Handle texture_loading;
		Texture_Handle texture_pause;
        Texture_Handle texture_help;
		Texture_Handle texture_pauseButton;
        Texture_Handle texture_helpButton;
		Texture_Handle texture_cesped;
		Texture_Handle texture_pared;
		Texture_Handle texture_pared_destruible;
        Texture_Handle texture_dpad;
        Texture_Handle texture_player;
		Texture_Handle textures_up[3];
		Texture_Handle textures_down[3];
		Texture_Handle textures_left[3];
		Texture_Handle textures_right[3];
		Arena arena{};
        Timer          timer;
	public:
        //Contructor
        GameController();
        //Posiciones X e y de click de usuario
        float touch_X;
        float touch_Y;
        bool touching;

        //Variables para controlar el juego
        bool GameFinished=false;
		bool GamePaused=false;




        //Control de juego
		void start();
		void restart();




        /**
         * Chequea clicks en el HUD
         */
        void checkUIClicks();

        /**
         * Se llama automaticamente cuando de minimiza
         */
        void suspend    () ;
        /**
         * Se llama auto cuando se vuelve a la app
         */
        void resume     () ;

        /**
             * Aquí se inicializan los atributos que deben restablecerse cada vez que se inicia la escena.
             * @return
             */
        bool initialize ();
        /**
          * Este método se invoca automáticamente una vez por fotograma cuando se acumulan
          * eventos dirigidos a la escena.
          */
        void handle     (basics::Event & event);
        /**
             * Este método se invoca automáticamente una vez por fotograma para que la escena
             * actualize su estado.
             */
        void update     (float time) ;
            /**
             * Este método se invoca automáticamente una vez por fotograma para que la escena
             * dibuje su contenido.
             */
        void render (Canvas * canvas, unsigned canvas_width,unsigned canvas_height);

        /**
         * Dibuja el HUD
         * @param canvas
         */
        void drawUi (Canvas & canvas);

        /**
         * Posiciona y carga las texturas necesaria del HUD
         */
		void loadUi ();
        /**
         * Se llama al estar en estado RUNNING y contra la actuazliaciones del juego
         * @param time
         */
        void run(float time);
        /**
         * Se llama cuando el juego esta pausado
         * @param time
         */
        void pause(float time);
        /**
         * Carga los sprites y cosas necesarias para el juego
         */
        void load ();
        /**
         * Muestra pantalla de carga
         * @param canvas
         */
        void render_loading (Canvas & canvas);
/**
 * Muestra la la escena del juego
 * @param canvas
 */
		void render_arena (Canvas & canvas);
        /**
         * Muestra la escena de pause
         * @param canvas
         */
		void render_paused (Canvas & canvas);
        /**
         * Muestra la escena de pause
         * @param canvas
         */
        void render_help (Canvas & canvas);



	};

}
#endif