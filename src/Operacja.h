#pragma once
#include "NarzedziaSymbol.h"
#include "Logger\LoggerInterface.h"
namespace SpEx{
	/**
	* \brief Klasa bazowa zawieraj�ca interfejs dla wykonywanych operacji.
	*/
	class NARZEDZIA_API Operacja :
		virtual public SLog::LoggerInterface
	{
	public:
		/**
		* \brief Konstruktor domy�lny.
		*/
		Operacja(void) = default;

		/**
		* \brief Destruktor.
		*/
		virtual ~Operacja(void) = default;

		/**
		* \brief Metoda wykonuj�ca operacje tranzakcyjn�.
		*
		* \return Metoda klasy bazowej zawsze zwraca false.
		*/
		virtual bool wykonaj();

		/**
		* \brief Metoda wykonuj�ca operacje odwrotn� do tranzakcyjnej.
		*
		* \return Metoda klasy bazowej zawsze zwraca false.
		*/
		virtual bool cofnij();

		/**
		* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
		* \return Napis zwieraj�cy opis klasy.
		*/
		std::string napis() const override;
	};
};
