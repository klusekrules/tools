#pragma once
#include "NarzedziaSymbol.h"
namespace se{
	/**
	* \brief Klasa blokująca kopiowanie.
	*
	* Klasa blokuje użycie domyślnych konstruktorów kopiujących.
	* \author Daniel Wojdak
	* \version 1
	* \date 06-06-2014
	*/
	class NARZEDZIA_API NonCopyable
	{
	public:
		NonCopyable() = default;
		virtual ~NonCopyable() = default;
		NonCopyable& operator=(const NonCopyable&) = delete;
		NonCopyable(const NonCopyable&) = delete;
	};
}
