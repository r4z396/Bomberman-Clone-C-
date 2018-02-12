#ifndef DPAD_H
#define DPAD_H

#include <basics/Scene>
#include <basics/Size>
#include <basics/Point>
#include <basics/Vector>
#include <basics/Canvas>
#include "Button.hpp"



//#include "GameController.hpp"

namespace example
{
	using basics::Canvas;
	using basics::Size2f;
	using basics::Point2f;
	using basics::Vector2f;
	using basics::Texture_2D;
    using namespace std;


	class Dpad
	{
	private:
		Size2f       size;                      ///< Tamaño del sprite (normalmente en coordenadas virtuales).
		Point2f      position;                  ///< Posición del sprite (normalmente en coordenadas virtuales).
		Button up;
        Button down;
        Button left;
        Button right;
		Point2f      position_up;
		Point2f      position_down;
		Point2f      position_left;
		Point2f      position_right;

	public:
		//Constructor del DPAD
		Dpad();
		/**
		 * Se incializa el DPad en posicion y tamaño pasados por param
		 * @param position
		 * @param size
		 */
		void initialize(Point2f position,Size2f size);
		/**
		 * Se incializan los botones en posicion y tamaños dados
		 */
        void iniPads();
		/**
		 * Update la posicio de los botones
		 */
        void update();

		const Size2f   & get_size       () const { return  size;        }
		const float    & get_width      () const { return  size.width;  }
		const float    & get_height     () const { return  size.height; }
		const Point2f  & get_position   () const { return  position;    }
		const float    & get_position_x () const { return  position[0]; }
		const float    & get_position_y () const { return  position[1]; }

		// Setters

		void set_size(Size2f new_size)
		{
			size = new_size;
		}

		void set_position (const Point2f & new_position)
		{
			position = new_position;
		}

		void set_position_x (const float & new_position_x)
		{
			position.coordinates.x () = new_position_x;
		}

		void set_position_y (const float & new_position_y)
		{
			position.coordinates.y () = new_position_y;
		}
         void render(Canvas & canvas);

        int checkDpadContains(Point2f temp);
	};

}
#endif