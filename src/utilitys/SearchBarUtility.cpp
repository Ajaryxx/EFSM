#include "PCH.hpp"
#include "utilitys/SearchBarUtility.hpp"


std::vector<wxString> SearchBarUtility::SearchPathVector(const std::vector<wxString>& vector, const wxString& searchPrefix, bool ignoreUpperChars)
{
	std::vector<wxString> FoundPathVec;

	if(ignoreUpperChars)
	{
		for (const auto& item : vector)
		{
			std::string fileName = item.Lower();
			if (fileName.find(searchPrefix.Lower()) != wxString::npos)
			{
				FoundPathVec.push_back(item);
			}
		}
	}
	else
	{
		/*for (const auto& item : vector)
		{
			if (item.find(searchPrefix.))
		}*/
	}


	return FoundPathVec;
}
