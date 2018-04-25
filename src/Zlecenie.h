#pragma once
#include "Logger\LoggerInterface.h"
#include "Logger\Logger.h"
#include "Operacja.h"
#include <functional>
namespace SpEx{
	/**
	* \brief Szablon klasy reprezentuj�cej pojedy�cz� operacje tranzakcyjn�.
	*
	* Klasa zawiera Argumenty operacji, funkcj� tranzakcyjn� oraz funkcj� odwrotn� anuluj�c� wprowadzone zmiany przez funkcj� tranzakcyjn�.
	*/
	template< typename ARG1, typename ARG2 >
	class Zlecenie :
		public Operacja,
		virtual public SLog::LoggerInterface
	{
	public:
		typedef std::function<bool(ARG1&, ARG2&)> Funkcja; /// Typ przechowywanych funkcji.

		/**
		* \brief Konstruktor zlecenia.
		*
		* \param[in] arg1 - pierwszy argument funkcji.
		* \param[in] arg2 - drugi argument funkcji.
		* \param[in] zlecenie - funkcja tranzakcyjna.
		* \param[in] odwrotna - funkcja odwrotna.
		*/
		Zlecenie(ARG1& arg1, ARG2& arg2, Funkcja zlecenie, Funkcja odwrotna)
			: argument1_(arg1), argument2_(arg2), funkcjaZlecenia_(zlecenie), funkcjaOdwrotna_(odwrotna)
		{
		}

		/**
		* \brief Destruktor.
		*/
		virtual ~Zlecenie() = default;

		/**
		* \brief Metoda zlecenia.
		*
		* Metoda wywo�uje funkcj� tranzakcyjn� i przekazuje do niej przechowywane argumenty.
		* \return Metoda zwraca true, je�eli wykona si� poprawnie lub false w przeciwnym wpadku.
		*/
		bool wykonaj() override{
			return funkcjaZlecenia_(argument1_, argument2_);
		}

		/**
		* \brief Metoda cofni�cia zmian.
		*
		* Metoda wywo�uje funkcj� odwrotn� i przekazuje do niej przechowywane argumenty.
		* \return Metoda zwraca true, je�eli wykona si� poprawnie lub false w przeciwnym wpadku.
		*/
		bool cofnij() override{
			return funkcjaOdwrotna_(argument1_, argument2_);
		}

		/**
		* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
		* \return Napis zwieraj�cy opis klasy.
		*/
		std::string napis() const override{
			SLog::Logger str(NAZWAKLASY(Zlecenie));
			str.dodajKlase(Operacja::napis());
			str.dodajPole(NAZWAPOLA(argument1_), argument1_);
			str.dodajPole(NAZWAPOLA(argument2_), argument2_);
			return str.napis();
		}

	protected:
		ARG1& argument1_; /// Pierwszy argument.
		ARG2& argument2_; /// Drugi argument.
		Funkcja funkcjaZlecenia_; /// Funkcja tranzakcyjna.
		Funkcja funkcjaOdwrotna_; /// Funkcja odwrotna.
	};
};
