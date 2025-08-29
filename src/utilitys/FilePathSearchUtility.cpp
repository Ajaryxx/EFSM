#include "PCH.hpp"
#include "utilitys/FilePathSearchUtility.hpp"

namespace fs = std::filesystem;

std::vector<wxString> FilePathSearchUtilty::SearchDirPath(const std::vector<wxString>& elements, const wxString& searchPrefix, bool IgnoreUpperLower)
{
	std::vector<wxString> searchPathsVec;

	
	if (IgnoreUpperLower)
	{
		for (const auto& item : elements)
		{
			wxString fileName = fs::path(item.ToStdWstring()).filename().wstring();

			if (fileName.Lower().find(searchPrefix.Lower()) != wxString::npos)
			{
				searchPathsVec.push_back(item);
			}
		}
	}
	else
	{

	}



	return searchPathsVec;
}
