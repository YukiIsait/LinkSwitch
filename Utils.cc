#include <string>
#include <vector>
#include <fstream>
#include "PathUtil.h"

class Utils
{
public:
	static void GeneratePwshModule(const std::vector<std::wstring> list)
	{
		if(list.size() == 0) return;

		auto procName = PathUtil::GetProgramFileName();
		auto psm = PathUtil::ReplaceExtension(procName, L".psm1");
		std::wofstream file(psm, std::ios::out);
		auto fname = PathUtil::GetFileNameWithoutExtension(procName);
		
		file << L"function " << fname << L" {" << std::endl
			<< L"    param(" << std::endl
			<< L"        [Parameter(Mandatory=$true)]" << std::endl
			<< L"        [ValidateSet(";
		for(size_t i = 0; i < list.size(); i++)
		{
			file << L"\"" << list[i] << L"\"";
			if(i < list.size() - 1)
				file << L", ";
		}
		file << L")]" << std::endl
			<< L"        [string]$Name" << std::endl
			<< L"    )" << std::endl
			<< L"    & \"$PSScriptRoot\\";
		file << PathUtil::GetFileName(procName) << L"\" $Name" << std::endl;
		file << L"}";

		file.close();
	}
};