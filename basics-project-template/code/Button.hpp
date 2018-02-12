#ifndef BUTTON_H
#define BUTTON_H

#include <basics/Scene>
#include <basics/Size>
#include <basics/Point>
#include <basics/Vector>
#include <basics/Canvas>

//#include "GameController.hpp"

namespace example
{
	using basics::Canvas;
	using basics::Size2f;
	using basics::Point2f;
	using basics::Vector2f;
	using basics::Texture_2D;
	using namespace std;

	class Button
	{


	public:

        int          anchor;                    ///< Indica qué punto de la textura se colocará en 'position' (x,y).

        Size2f       size;
        Size2f       sizeNEW;                      ///< Tamaño del sprite (normalmente en coordenadas virtuales).
        Point2f      position;                  ///< Posición del sprite (normalmente en coordenadas virtuales).
        float        scale;                     ///< Escala el tamaño del sprite. Por defecto es 1.



		bool visible;
        bool haveSprite;
		shared_ptr<Texture_2D> sprite;



	public:

        Button(Texture_2D * texture);
		Button();
		//Getters

		const Size2f   & get_size       () const { return  size;        }
		const float    & get_width      () const { return  size.width;  }
		const float    & get_height     () const { return  size.height; }
		const Point2f  & get_position   () const { return  position;    }
		const float    & get_position_x () const { return  position[0]; }
		const float    & get_position_y () const { return  position[1]; }

        float get_left_x () const
        {
            return
                    (anchor & 0x3) == basics::LEFT  ? position[0] :
                    (anchor & 0x3) == basics::RIGHT ? position[0] - sizeNEW[0] :
                    position[0] - sizeNEW[0] * .5f;
        }

        float get_right_x () const
        {
            return get_left_x () + sizeNEW.width;
        }

        float get_bottom_y () const
        {
            return
                    (anchor & 0xC) == basics::BOTTOM ? position[1] :
                    (anchor & 0xC) == basics::TOP    ? position[1] - sizeNEW[1] :
                    position[1] - sizeNEW[1] * .5f;
        }

        float get_top_y () const
        {
            return get_bottom_y () + sizeNEW.height;
        }




        bool is_visible () const
		{
			return  visible;
		}

		bool is_not_visible () const
		{
			return !visible;
		}
		// Setters

        void set_size(Size2f new_size){
            size=new_size;
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

		void set_scale (float new_scale)
		{
			scale = new_scale;
		}


		void hide()
		{
			visible = false;
		}

		void show()
		{
			visible = true;
		}


		/**
		* Comprueba si el área envolvente rectangular de este sprite se solapa con la de otro.
		* @param other Referencia al otro sprite.
		* @return true si las áreas se solapan o false en caso contrario.
		*/
		bool intersects (const Button & other);

		/**
         * Comprueba si un punto está dentro del sprite.
         * Se puede usar para, por ejemplo, comprobar si el punto donde el usuario ha tocado la
         * pantalla está dentro del sprite.
         * @param point Referencia al punto que se comprobará.
         * @return true si el punto está dentro o false si está fuera.
         */
		bool contains (const Point2f & point);

		void setTexture( shared_ptr<basics::Texture_2D>  temp);
        void update();




		void render(Canvas & canvas);






	};

}
#endif