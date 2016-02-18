// Возвращает в указателе tempFileName путь к временному файлу 
// память выделяется внутри процедуры
//
int GetTempFileName(char** tempFileName){

	unsigned int uRetVal = 0;

// для Linux подойдет стандартная функция tmpnam (для Windows она возвращает путь в корень диска C)
#ifdef __linux__
	(*tempFileName) = new char[ L_tmpnam];
	tmpnam (*tempFileName);
	uRetVal = strlen(*tempFileName);
#else
	char lpTempPathBuffer[MAX_PATH];
	(*tempFileName) = new char[MAX_PATH];
	//  Gets the temp path env string (no guarantee it's a valid path).
	DWORD dwRetVal = GetTempPathA(MAX_PATH,          // length of the buffer
		lpTempPathBuffer); // buffer for path 
	if (dwRetVal > MAX_PATH || (dwRetVal == 0))
	{
		SetLastError("Не удалось получить путь к каталогу временных файлов.");
		delete[] (*tempFileName);
		return -1;
	}

	//  Generates a temporary file name. 
	uRetVal = GetTempFileNameA(lpTempPathBuffer, // directory for tmp files
		NULL,     // temp file name prefix 
		0,                // create unique name 
		(*tempFileName));  // buffer for name 
	if (uRetVal == 0)
	{
		SetLastError("Не удалось получить путь к временному файлу.");
		delete[] (*tempFileName);
		return -1;
	}
#endif
	return uRetVal; 
}