#ifndef ARENA_H
#define ARENA_H

#include <basics/Scene>
#include <basics/Size>
#include <basics/Point>
#include <basics/Vector>
#include <basics/Canvas>
#include "GameObject.hpp"

//#include "GameController.hpp"

namespace example
{
	using basics::Canvas;
	using basics::Size2f;
	using basics::Point2f;
	using basics::Vector2f;
	using basics::Texture_2D;
    using namespace std;


	class Arena
	{

	private:
		int **matriz;

	public:
        int filas=18;
        int columnas =19;
		float x;
		float y;
		void generateMap();

		 shared_ptr<Texture_2D> texture_pared;
        shared_ptr<Texture_2D> texture_pared_destruible;
        shared_ptr<Texture_2D> texture_cesped;
		struct Pared
		{

			float sizeX,sizeY;

		};

		struct Pared_Destruible
		{

			float sizeX,sizeY;

		};
		Pared pared;
		Pared_Destruible pared_destruible;
	public:


        Arena();

		void setTextures(shared_ptr< basics::Texture_2D > pared,shared_ptr< basics::Texture_2D > pared_destruible,shared_ptr< basics::Texture_2D > cesped);
		int** getArena()
		{
			return matriz;
		}
		int getFilas()
		{
			return filas;
		}
		int getColumnas()
		{
			return columnas;
		}
		void render(Canvas & canvas);






	};

}
#endif