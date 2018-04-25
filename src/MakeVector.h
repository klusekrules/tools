#pragma once
#include "NarzedziaSymbol.h"
#include <vector>
#include <string>
namespace SpEx{

	/**
	* \brief Klasa tworz�ca wektor z listy argument�w.
	*
	* Klasa s�u��ca do tworzenia wektora z listy argument�w przekazanych w konstruktorze.
	* \author Daniel Wojdak
	* \version 1
	* \date 08-07-2014
	*/
	class NARZEDZIA_API MakeVector
	{
	public:
		/**
		* \brief Konstruktor obiektu.
		*
		* Metoda konstruuj�ca obiekt.
		* \param[in] tail - Lista obiekt�w.
		* \tparam V - Typ obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		*/
		template< class... V >
		MakeVector(V&... tail){
			step(a, tail...);
		}

		/**
		* \brief Konstruktor przenosz�cy.
		*
		* Konstruktor przenosz�cy.
		* \param[inout] d - Obiekt �r�d�owy.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		*/
		MakeVector(MakeVector&& d)
			: a(d.a)
		{
		}

		/**
		* \brief Metoda zwracaj�ca stworzon� tablice.
		*
		* Metoda zwracaj�ca stworzon� w konstruktorze tablice opis�w obiekt�w.
		* \return Wektor obiekt�w.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		*/
		const std::vector< std::string >& get() {
			return a;
		}

	private:
		std::vector< std::string > a; /// Wektor z opisem obiekt�w przekazanych w konstruktorze.

		/**
		* \brief Metoda pojedy�czego kroku dodaj�ca obiekt do wektora.
		*
		* Metoda dodaje opis obiektu do wektora. Wywo�uje koleny krok tworzenia opisu listy obiekt�w.
		* \param[inout] v - Wektor z opisem obiekt�w.
		* \param[in] c - Obiekt.
		* \param[in] tail - lista obiekt�w.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		*/
		template< class T, class... V >
		void step(std::vector< std::string >& v, T &c, V&... tail){
			v.push_back(c);
			step(v, tail...);
		}

		/**
		* \brief Metoda pojedy�czego kroku dodaj�ca obiekt do wektora.
		*
		* Metoda dodaje opis obiektu do wektora. Metoda ko�czy tworzenie wektora z opisami obiekt�w.
		* \param[inout] v - Wektor z opisem obiekt�w.
		* \param[in] c - Obiekt.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		*/
		template< class T >
		void step(std::vector< std::string >& v, T &c){
			v.push_back(c);
		}

	};
};
