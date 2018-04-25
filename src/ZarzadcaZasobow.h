#pragma once
#include "GeneratorIdentyfikatorow.h"
#include "Zasob.h"
#include "NonCopyable.h"
#include <functional>
#include "Parser\XmlBO.h"
#include "Logger\LoggerInterface.h"
#include "UstawieniaAplikacji.h"
#include "CallbackSystemInterfejs.h"
namespace SpEx {
	
	namespace StrukturyZarzadcyZasobow {
		enum WyzwalaczCallback{
			PoRejestracji,
			PoUtworzeniu,
			PobranoPrzechowywany
		};

		typedef CallbackSystemInterfejs < WyzwalaczCallback, const std::string&, Zasob::SharedPtr > CallbackSystem;
		typedef CallbackSystem::Callback CallbackSystemFunction;
	}

	/**
	* \brief Klasa zarz�dzaj�ca zasobami.
	*
	* Klasa zarz�dzaj�ca zasobami, przechowuje wska�niki na zasoby.
	* \author Daniel Wojdak
	* \version 3
	* \date 25-11-2014
	*/
	class NARZEDZIA_API ZarzadcaZasobow :
		public StrukturyZarzadcyZasobow::CallbackSystem,
		public virtual SLog::LoggerInterface,
		se::NonCopyable
	{
	public:
		typedef std::string Parametr; /// Typ parametru przekazywanego do zasobu.
		typedef std::pair < Parametr, std::string > WpisLokalizacjiZasobu; /// Typ wi���cy nazw� symboliczn� z lokalizacj� zasobu.
		typedef std::vector < WpisLokalizacjiZasobu > TablicaLokalizacjiZasobu; /// Tablica powi�za� nazw symbolicznych z lokalizacj� zasobu.
		typedef STyp::Identyfikator Identyfikator; /// Identyfikator zasobu.
		
		
		/**
		* \brief Klasa pomocnicza przechowywanego zasobu.
		*
		* Klasa pomocnicza, s�u��ca do zarz�dzania przechowywanymi zasobami.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-11-2014
		*/
		struct WpisZasobu{
			Zasob::WeakPtr weakptr_; /// S�aby wska�nik do zasobu.
			Zasob::SharedPtr sharedptr_; /// Silny wska�nik do zasobu.
			bool cached_; /// Informacja czy zas�b jest przechowywany.
			Parametr parametr_; /// Parametr inicjalizuj�cy zas�b.
		};
		
		typedef std::function< Zasob::SharedPtr(const Parametr&, bool) > Inicjalizator; /// Typ metody tworz�cej zas�b.
		typedef std::unordered_map < Identyfikator, WpisZasobu, STyp::IdTypeHash> MapaZasobow; /// Typ kontenera przechowuj�cego zasoby.
		typedef std::unordered_map < std::string, Inicjalizator> MapaInicjalizatorow; /// Typ kontenera przechowuj�cego inicjalizatory.
		

		/**
		* \brief Domy�lny konstruktor.
		*
		* Domy�lny konstruktor.
		*/
		ZarzadcaZasobow() = default;
		
		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		virtual ~ZarzadcaZasobow() = default;
		
		/**
		* \brief Metoda pobieraj�ca klucz zasobu.
		*
		* Metoda na podstawie klucza znakowego zwraca klucz liczbowy.
		* \param[in] identyfikator - Napis identyfikuj�cy zas�b.
		* \return Identyfikator liczbowy.
		* \author Daniel Wojdak
		* \version 1
		* \date 02-09-2014
		*/
		Identyfikator pobierzKlucz(const Parametr& identyfikator);

		/**
		* \brief Metoda pobierajaca zas�b.
		*
		* Metoda pobiera lub tworzy zas�b.
		* \param[in] parametr - Adres pliku na bazie kt�rgo ma zosta� zainicjalizowany zas�b.
		* \param[in] cache - Informacja czy zas�b ma by� lokalnie przechowywany.
		* \param[out] id - Identyfikator utworzonego zasobu.
		* \return Wska�nik na zas�b lub nullptr.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		template <class T_>
		inline std::shared_ptr<T_> pobierzZasob(const Parametr& parametr, bool cache = false, Identyfikator& id = Identyfikator()){
			return std::dynamic_pointer_cast<T_>(pobierzZasob(pobierzInicjalizator(typename T_::NazwaTypu_), parametr, parametr, cache, id));
		}

		/**
		* \brief Metoda pobierajaca zas�b.
		*
		* Metoda pobiera lub tworzy zas�b.
		* \param[in] nazwa - W�asna nazwa identyfikuj�ca zas�b generowana w trakcie dzia�ania programu.
		* \param[in] identyfikator - Identyfikator zasobu.
		* \param[in] parametr - Adres pliku na bazie kt�rgo ma zosta� zainicjalizowany zas�b.
		* \param[in] cache - Informacja czy zas�b ma by� lokalnie przechowywany.
		* \param[out] id - Identyfikator utworzonego zasobu.
		* \return Wska�nik na zas�b lub nullptr.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-11-2014
		*/
		template <class T_>
		inline std::shared_ptr<T_> pobierzZasob(const std::string& nazwa, const Parametr& parametr, bool cache = false, Identyfikator& id = Identyfikator()){
			return std::dynamic_pointer_cast<T_>(pobierzZasob(pobierzInicjalizator(typename T_::NazwaTypu_), nazwa, parametr, cache, id));
		}

		/**
		* \brief Metoda pobierajaca zas�b.
		*
		* Metoda pobiera lub tworzy zas�b.
		* \param[in] parametr - Adres pliku na bazie kt�rgo ma zosta� zainicjalizowany zas�b.
		* \return Wska�nik na zas�b lub nullptr.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		template <class T_>
		inline std::shared_ptr<T_> pobierzUnikalnyZasob(const Parametr& parametr){
			return std::dynamic_pointer_cast<T_>(pobierzUnikalnyZasob(pobierzInicjalizator(typename T_::NazwaTypu_), parametr));
		}

		/**
		* \brief Metoda pobiera informacje czy zas�b jest przechowywany przez zarz�dc�.
		*
		* Metoda pobiera informacje czy zas�b jest przechowywany lokalnie przez zarz�dc� zasob�w.
		* \param[in] identyfikator - Identyfikator zasobu.
		* \return Zwracana jest warto�c true, je�eli zas�b jest przechowywany. Zwracana jest warto�� false, w przeciwnym przypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		bool przechowywanyZasob(const Identyfikator& identyfikator) const;

		/**
		* \brief Metoda rejestruj�ca inicjalizator.
		*
		* Metoda rejestruje inicjalizator w zarz�dcy zasob�w.
		* \return Zwracana jest warto�c true, je�eli uda si� zarejestrowa�. Zwracana jest warto�� false, w przypadku b��du.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		template <class T_>
		bool rejestruj(){
			wywolaj(StrukturyZarzadcyZasobow::PoRejestracji, typename T_::NazwaTypu_, nullptr);
			return dodajInicjalizator(typename T_::NazwaTypu_, std::bind(&ZarzadcaZasobow::tworz<T_>,this,std::placeholders::_1,std::placeholders::_2));
		}

		template <class T_>
		Zasob::SharedPtr tworz(const ZarzadcaZasobow::Parametr& parametr, bool cache){
			Zasob::SharedPtr ptr = std::make_shared<T_>(parametr);
			wywolaj(StrukturyZarzadcyZasobow::PoUtworzeniu, typename T_::NazwaTypu_, ptr);
			return ptr;
		}

		/**
		* \brief Metoda zwalaniaj�ca przechowywany zas�b.
		*
		* Metoda zwalnia zas�b przechowywany lokalnie w zarz�dcy.
		* \param[in] identyfikator - Identyfikator zasobu.
		* \return Zwracana jest warto�c true, je�eli jest uda�o si� zwolni� zas�b. Zwracana jest warto�� false, w przeciwnym przypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		bool zwolnijZasobPrzechowywany(const Identyfikator& identyfikator);

		/**
		* \brief Metoda inicjuj�ca dane zarz�dcy.
		*
		* Metoda pobiera dane i inicjuje obiekt zarz�dcy na podstawie danych przekazanych przez parametry.
		* \param[in] ustawienia - Obiekt zawierajacy ustawienia apliakcji.
		* \param[in] stos - Funkcja tworz�ca �lad stosu.
		* \return Zwracana jest warto�� true je�eli uda si� poprawnie zainicjowa� obiekt.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-11-2014
		*/
		bool inicjalizuj(const UstawieniaAplikacji& ustawienia);

		void rejestrujTypyWbudowane();

		/**
		* \brief Metoda pobieraj�ca adres obrazka.
		*
		* Metoda pobiera adres obrazka o padanym identyfikatorze.
		* \param[in] identyfikator - Identyfikator obrazka.
		* \return Adres obrazka.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-11-2014
		*/
		const std::string& pobierzAdresObrazka( const STyp::Identyfikator& identyfikator) const;

		/**
		* \brief Metoda pobieraj�ca identyfikator obrazka.
		*
		* Metoda pobiera identyfikator obrazka na podstawie nazwy obrazka.
		* \param[in] nazwaObrazka - Nazwa obrazka.
		* \return Identyfikator obrazka.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-11-2014
		*/
		STyp::Identyfikator pobierzIdentyfikator(const Parametr& nazwaObrazka) const;

		/**
		* Funkcja s�u��ca jako podstawa do tworzenia napis�w z opisem klasy.
		* \return Napis zawieraj�cy opis klasy.
		* \author Daniel Wojdak
		* \version 1
		* \date 13-11-2014
		*/
		std::string napis() const override;

		/**
		* Funkcja resetuj�ca stan obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-11-2014
		*/
		void resetuj();

	private:
		GeneratorIdentyfikatorow generator_; /// Generator identyfikator�w.
		TablicaLokalizacjiZasobu lokalizacjeZasobow_; /// Tablica zawieraj�ca powi�zania nazw symbolicznych z lokalizacj� zasobu na dysku.
		
		/**
		* \brief Metoda mapuje parametr na identyfikator.
		*
		* Metoda mapuje parametr tekstowy na identyfikator liczbowy.
		* \param[in] parametr - Adres pliku na bazie kt�rgo ma zosta� zainicjalizowany zas�b.
		* \param[out] identyfikator - Identyfikator zasobu.
		* \return Zwracana jest warto�c true, je�eli pierwszy raz odwo�ano si� do tego identyfikatora. Zwracana jest warto�� false, w przeciwnym przypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		bool mapujIdentyfikator(const Parametr& parametr, Identyfikator& identyfikator);

		Inicjalizator pobierzInicjalizator(const std::string&);

		bool dodajInicjalizator(const std::string&, Inicjalizator);

		/**
		* \brief Metoda pobierajaca zas�b.
		*
		* Metoda pobiera lub tworzy zas�b.
		* \param[in] parametr - Adres pliku na bazie kt�rgo ma zosta� zainicjalizowany zas�b.
		* \return Wska�nik na zas�b lub nullptr.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		Zasob::SharedPtr pobierzUnikalnyZasob(Inicjalizator inicjalizator, const Parametr& parametr);

		/**
		* \brief Metoda pobierajaca zas�b.
		*
		* Metoda pobiera lub tworzy zas�b.
		* \param[in] nazwa - W�asna nazwa identyfikuj�ca zas�b generowana w trakcie dzia�ania programu.
		* \param[in] identyfikator - Identyfikator zasobu.
		* \param[in] parametr - Adres pliku na bazie kt�rgo ma zosta� zainicjalizowany zas�b.
		* \param[in] cache - Informacja czy zas�b ma by� lokalnie przechowywany.
		* \param[out] id - Identyfikator utworzonego zasobu.
		* \return Wska�nik na zas�b lub nullptr.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-11-2014
		*/
		Zasob::SharedPtr pobierzZasob(Inicjalizator inicjalizator, const std::string& nazwa, const Parametr& parametr, bool cache = false, Identyfikator& id = Identyfikator());

		/**
		* \brief Metoda pobierajaca zas�b.
		*
		* Metoda pobiera lub tworzy zas�b.
		* \param[in] identyfikator - Identyfikator zasobu.
		* \param[in] parametr - Adres pliku na bazie kt�rgo ma zosta� zainicjalizowany zas�b.
		* \param[in] cache - Informacja czy zas�b ma by� lokalnie przechowywany.
		* \param[out] id - Identyfikator utworzonego zasobu.
		* \return Wska�nik na zas�b lub nullptr.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		Zasob::SharedPtr pobierzZasob(Inicjalizator inicjalizator, const Identyfikator& identyfikator, const Parametr& parametr, bool cache = false, Identyfikator& id = Identyfikator());

		/**
		* \brief Metoda wczytuj�ca zas�b.
		*
		* Metoda wczytuje zas�b do pami�ci.
		* \param[in] identyfikator - Identyfikator zasobu.
		* \param[in] parametr - Adres pliku na bazie kt�rgo ma zosta� zainicjalizowany zas�b.
		* \param[in] cache - Informacja czy zas�b ma by� lokalnie przechowywany.
		* \param[out] id - Identyfikator utworzonego zasobu.
		* \return Wska�nik na zas�b lub nullptr.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		Zasob::SharedPtr wczytajZasob(Inicjalizator inicjalizator, const Identyfikator& identyfikator, const Parametr& parametr, bool cache = false, Identyfikator& id = Identyfikator());

		MapaZasobow zasobyPrzechowywane_; /// Obiekt przechowuj�cy zasoby.
		MapaInicjalizatorow inicjalizatory_; /// Obiekt przechowuj�cy inicjalizatory.
		const std::string pustyNapis_ = std::string(); /// Pusty napis. U�ywany przy nie znalezieniu adresu obrazka.
	};
};
