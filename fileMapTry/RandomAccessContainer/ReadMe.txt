	UWAGA!
	Za�ozenie jest takie �e biblioteka otwiera domy�lny kontekst z folderu C:\\Menerva

	wszystkie eksportowane funkcje wg zalece� Mi�osza
	__declspec(dllexport) int __cdecl vtab_CountProc(char *_NAME);
	__declspec(dllexport) char* __cdecl vtab_GetColValue(char *_NAME, int ColNr, int RowKey);
	__declspec(dllexport) void __cdecl vtab_WriteColValue(char *_NAME, char *value, int ColNr, int RowKey);

	w opracowaniu:
	__declspec(dllexport) char* __cdecl vtab_GetSortedValue(char *_NAME, int ColNr, int Pos, int &Key);

	pracuja na tym jednym kontek�cie


	Oczywi�cie mo�na si� zastanowi� nad eksportem dodatkowych funkcji - inicjujacych/konfiguruj�cych


	rac.h - g��wny nag��wek i jesli nie pracujemy bezpo�rednio na Context/Set wystarczaj�cy by dzia�a�y wspomniane funkcje

	StdRowDefs.h - zdefiniowane struktury na kt�re mapowana jest pami��
		Obecnie, domy�lnie ka�dy wiersz mapowany jest na strukt�r� z tego nag��wka (TinyRow15Cols) - ma 15 kolumn po 256 bajt�w ka�da


	UWAGA!!!
	W wersji 32bity mo�liwa jest praca z jednym kontekstem i jednym zbiorem


