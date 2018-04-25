#pragma once
#include "NarzedziaSymbol.h"
namespace SpEx{
	/**
	* \brief Klasa zliczaj�ca ilo�� fps.
	*
	* Klasa s�u��ca do zliczania ilo��i fps.
	* \author Daniel Wojdak
	* \version 1
	* \date 03-07-2014
	*/
	class NARZEDZIA_API FPSCounter
	{
	private:
		unsigned long long Frames = 0; /// Ilo�� zmierzonych ramek, od ostatniego pobrania wyniku
		double time; /// Chwilowy punkt czasu.
		double fpsTime = 0; /// Czas pomiaru, kt�ry min�� od ostatniego pobrania wyniku
		long double fps_ = 0; /// Ilo�� fps.
	public:
		/**
		* \brief Konstruktor.
		*
		* Bezparametrowy konstruktor obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 03-07-2014
		*/
		FPSCounter();

		/**
		* \brief Metoda zlicza nast�pn� ramk�.
		*
		* Metoda oblicza czas pomi�dzy ramkami oraz zwi�ksza licznik ramek.
		* \author Daniel Wojdak
		* \version 1
		* \date 03-07-2014
		*/
		void nextFrame();

		/**
		* \brief Metoda zwraca ilo�� fps.
		*
		* Metoda zwraca aktualn� �redni� ilo�� fps.
		* \return Ilo�� fps.
		* \author Daniel Wojdak
		* \version 1
		* \date 03-07-2014
		*/
		long double FPS();
		
		/**
		* \brief Metoda informuje o poprawno�ci wyniku metody FPS.
		*
		* Metoda informuje czy wynik metody FPS b�dzie wzgl�dnie poprawny, tzn. czy okres w kt�rym zosta�y zbierane pr�bki jest wystarczaj�co d�ugi.
		* \return Zwraca warto�� true, je�eli wynik b�dzie poprawny. Warto�� false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 03-07-2014
		*/
		bool ready() const;

		/**
		* \brief Destruktor.
		*
		* Domy�lny destruktor obiektu.
		*/
		~FPSCounter() = default;
	};
};
