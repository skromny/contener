	UWAGA!
	Za³ozenie jest takie ¿e biblioteka otwiera domyœlny kontekst z folderu C:\\Menerva

	wszystkie eksportowane funkcje wg zaleceñ Mi³osza
	__declspec(dllexport) int __cdecl vtab_CountProc(char *_NAME);
	__declspec(dllexport) char* __cdecl vtab_GetColValue(char *_NAME, int ColNr, int RowKey);
	__declspec(dllexport) void __cdecl vtab_WriteColValue(char *_NAME, char *value, int ColNr, int RowKey);

	w opracowaniu:
	__declspec(dllexport) char* __cdecl vtab_GetSortedValue(char *_NAME, int ColNr, int Pos, int &Key);

	pracuja na tym jednym kontekœcie


	Oczywiœcie mo¿na siê zastanowiæ nad eksportem dodatkowych funkcji - inicjujacych/konfiguruj¹cych


	rac.h - g³ówny nag³ówek i jesli nie pracujemy bezpoœrednio na Context/Set wystarczaj¹cy by dzia³a³y wspomniane funkcje

	StdRowDefs.h - zdefiniowane struktury na które mapowana jest pamiêæ
		Obecnie, domyœlnie ka¿dy wiersz mapowany jest na struktórê z tego nag³ówka (TinyRow15Cols) - ma 15 kolumn po 256 bajtów ka¿da


	UWAGA!!!
	W wersji 32bity mo¿liwa jest praca z jednym kontekstem i jednym zbiorem


