#pragma once
#include "NarzedziaSymbol.h"
#include "Logger\LoggerInterface.h"
#include "Logger\Log.h"
#include "Operacja.h"
#include <vector>
#include <memory>
namespace SpEx{
	/**
	* \brief Klasa reprezentuj�ca tranzakcje.
	*
	* Klasa zawiera zbi�r operacji i odpowiadaj�cych im operacji odwrotnych, sk�adaj�cych si� na jedn� tranzakcj�.
	* Klasa gwarantuje wykonanie si� wszystkiego albo niczego, je�eli si� to nie uda zostanie wyrzucony wyj�tek.
	* W takim wypadku nie wiadomo co zosta�o cofni�te, a co nie zosta�o cofni�te. W celu zabezbieczenia si� przed
	* dalszymi b�ednymi zmianami danych zaleca si� przerwanie dzia�ania programu.
	*/
	class NARZEDZIA_API MenedzerTranzakcji :
		virtual public SLog::LoggerInterface
	{
	private:
		typedef std::shared_ptr< Operacja > Element; /// Type element�w przechowywanych w kontenerze.
		typedef std::vector< Element > Kontener; /// Typ kontenera przechowuj�cego elementy.
		Kontener listaOperacji_; /// Lista przechowywanych operacji.
		SLog::Log& log_;

	public:

		/**
		* \brief Konstruktor.
		*/
		MenedzerTranzakcji(SLog::Log& log);

		/**
		* \brief Destruktor.
		*/
		virtual ~MenedzerTranzakcji() = default;

		/**
		* \brief Metoda dodaje operacje do listy oczekuj�cych na wykonanie.
		*
		* \param[in] operacja - Operacja dodawana do listy.
		*/
		void dodaj(Element operacja);

		/**
		* \brief Metoda wykonuj�ca wszystkie operacje tranzakcyjne jakie przechowuje.
		*
		* Metoda wykonuje wszystkie operacje w takiej kolejno�ci jakiej zosta�y dodane.
		* W przypadku niepowodzenia jednej operacji wszytskie wykonane sa cofane kolejno pocz�wszy od ostatnio udanej.
		* \return Metoda zwraca true, je�eli si� powiedzie lub false w przeciwnym wypadku.
		*/
		bool wykonaj();

		/**
		* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
		* \return Napis zwieraj�cy opis klasy.
		*/
		std::string napis() const override;
	};
};
