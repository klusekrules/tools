#pragma once
#include "NarzedziaSymbol.h"
#include "Types\Wyjatek.h"

namespace SpEx{
	/**
	* \brief Wyj�tek b��du krytycznego wykonywanej tranzakcji.
	*
	* Wyj�tek zostaje wyrzucony kiedy w trakcie cofania tranzakcji wyst�pi� wyj�tek, b�d� funkcja si� nie powiod�a.
	*/
	class NARZEDZIA_API NiepowodzenieTranzakcji :
		public STyp::Wyjatek,
		virtual public SLog::LoggerInterface
	{
	public:
		static const STyp::Identyfikator domyslnyNiepowodzenieTranzakcjiID; /// Domy�lna warto�� id klasy.

		/**
		* \brief Konstruktor.
		*
		* \param[in] tPlik - Plik wyst�pienia wyj�tku.
		* \param[in] funkcja - Nazwa funkcji w kt�rej zosta� wygenerowany wyj�tek.
		* \param[in] iLinia - Linia wytapienia wyj�tku.
		* \param[in] tranzakcja - Opis tranzakcji dla ktorej wyst�pi� wyj�tek.
		*/
		NiepowodzenieTranzakcji(const STyp::Tekst& tPlik, const STyp::Tekst& funkcja, const STyp::Ilosc& iLinia, const STyp::Tekst& tranzakcja);

		/**
		* \brief Destruktor.
		*/
		virtual ~NiepowodzenieTranzakcji(void) = default;

		/**
		* \brief Metoda tworz�ca komunikat opisuj�cyh wyj�tek.
		* \return Tekst opisuj�cy wyj�tek.
		*/
		STyp::Tekst generujKomunikat() const override;

		/**
		* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
		* \return Napis zwieraj�cy opis klasy.
		*/
		std::string napis() const override;

	protected:
		STyp::Tekst tranzakcja_; /// Opis tranzakcji

	private:
		static const STyp::Tekst domyslnyNiepowodzenieTranzakcjiTytul; /// Domy�lny tytu� wyjatku
		static const STyp::Tekst domyslnyNiepowodzenieTranzakcjiTresc; /// Domy�lna tre�� wyj�tku
	};
}
