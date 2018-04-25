#pragma once
#include "NonMoveable.h"
#include "NonCopyable.h"
#include "Logger\Log.h"
#include <map>

namespace SpEx{
	/**
	* \brief Klasa przechowuj�ca ustawienia
	*
	* Klasa s�u�aca do wczytywania, przechowywyania, zarz�dzania i zapisywania ustawie� aplikacji.
	* \author Daniel Wojdak
	* \version 3
	* \date 20-10-2014
	*/
	class NARZEDZIA_API UstawieniaAplikacji :
		virtual public SLog::LoggerInterface,
		public se::NonCopyable,
		public se::NonMoveable
	{
	public:
		/**
		* \brief Konstruktor.
		*
		* Domy�lny konstruktor obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		UstawieniaAplikacji() = default;

		/**
		* \brief Destruktor.
		*
		* Domy�lny destruktor obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		virtual ~UstawieniaAplikacji() = default;

		/**
		* \brief Metoda wczytuj�ca dane z pliku.
		*
		* Metoda wczytuj�ca ustawienia w pliku, kt�rego adres jest podany w parametrze.
		* \param[in] plik - Adres pliku.
		* \return Zwracana jest warto�� true, je�eli wszystko si� powiedzie. Zwracana jest warto�c false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		bool zaladuj(const std::string& plik);

		const std::string& operator[](const std::string& nazwa) const;

		std::string& operator[](const std::string& nazwa);

		/**
		* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
		* \return Napis zwieraj�cy opis klasy.
		* \author Daniel Wojdak
		* \version 1
		* \date 20-10-2014
		*/
		std::string napis() const override;
		
	private:
		mutable std::map<std::string, std::string> opcje_;

	};
};
