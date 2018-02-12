#pragma once
#ifndef PLAYER_H
#define PLAYER_H





#include <list>
#include "GameObject.hpp"
//#include "GameController.hpp"


namespace example
{using namespace std;
	class GameController;

	class Player:public GameObject
	{

    public:

        enum Directions {Up,Down,Left,Right,Stop};///<Direcciones del jugador
	private:
        int filas; ///<Filas de la matriz de arena
        int columnas;   ///<Columnas de la matriz de arena


        int fpslimit=0;///<Contador de fps para limitar la velocidad de cambio de sprite

        float player_Speed;///<Velocidad de jugador
		Directions  direction;  ///<Direccion actual de jugador
		Directions lastDiretion;    ///<Ultima direccion del jugador

        float width_sprite; ///<Tamaño del sprite
        float height_sprite;    ///<Tamaño del sprite

        int indiceX;///<Indice de sprites X
        int indiceY;    ///<Indice de sprites Y
		Point2f spritePosition;
		Size2f spriteSize;

		shared_ptr<Texture_2D> textures[4][3]; ///<Array bidimensional que adjunta todas las animaciones

		shared_ptr<Texture_2D> textures_up[3];  ///<Texturas de movimiento arriba
		shared_ptr<Texture_2D> textures_down[3]; ///<Texturas de movimiento abajo
		shared_ptr<Texture_2D> textures_left[3];///<Texturas de movimiento izquierda
		shared_ptr<Texture_2D> textures_right[3];///<Texturas de movimiento derecha

		GameObject CheckLR{};   ///<GameObject usado como collider para validar movimiento en drcha e izq
		GameObject CheckUD{};    ///<GameObject usado como collider para validar movimiento en arriba y abajo

		GameObject triggerMove{};   //Trigger que se situa en la posicion donde se desplaza el jugador por la arena

    public:
        Player();
		//Setters
        void setDirection(Directions temp);
        void setFilas(int temp){
            filas=temp;
        }
        void setColumnas(int temp){
            columnas=temp;
        }
        void setSpeed(float temp)
        {
            player_Speed=temp;
        }
		void setTextures( shared_ptr<basics::Texture_2D>  temp[],shared_ptr<basics::Texture_2D>  temp1[],shared_ptr<basics::Texture_2D>  temp2[],shared_ptr<basics::Texture_2D>  temp3[]);

        /*
         * Render del jugador que conecta con el movimiento
         */
		void renderPlayer(Canvas & canvas,int **tempArena);
        /*
         * Movimiento del jugador
         */
		void movePlayer(Canvas & canvas,int **tempArena);


		/*
		 * Valida el movimiento del personaje
		 * tomando de referencia la posicion del
		 * jugador en la matriz Arena
		 */
        void validateMove(int **temp);




    };




}
#endif