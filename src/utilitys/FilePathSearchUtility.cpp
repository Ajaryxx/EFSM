#include "PCH.hpp"
#include "utilitys/FilePathSearchUtility.hpp"

namespace fs = std::filesystem;

std::vector<wxString> FilePathSearchUtilty::SearchDirPath(const wxString& directoryPath, const wxString& searchPrefix, bool IgnoreUpperLower)
{
	std::vector<wxString> searchPathsVec;

	if (!fs::exists(directoryPath.ToStdWstring()))
	{
		wxMessageBox("Path doesnt exist!", "WARNING");
		return std::vector<wxString>();
	}
		
	if (IgnoreUpperLower)
	{
		for (const auto& item : fs::directory_iterator(directoryPath.ToStdWstring()))
		{
			wxString fileName = fs::path(item).filename().wstring();

			if (fileName.Lower().find(searchPrefix.Lower()) != wxString::npos)
			{
				searchPathsVec.push_back(item.path().wstring());
			}
		}
	}
	else
	{

	}



	return searchPathsVec;
}
