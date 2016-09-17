bool ExecuteProcess(std::string process)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	std::wstring _process(process.begin(), process.end());
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	if (!CreateProcess(_process.c_str(), NULL, NULL, NULL, false, 0, NULL, NULL, &si, &pi))
	{
		return false;
	}
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	return true;
}