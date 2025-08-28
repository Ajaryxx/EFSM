#pragma once


class SearchBarUtility
{
public:


	static std::vector<wxString> SearchPathVector(const std::vector<wxString>& vector, const wxString& searchPrefix, bool ignoreUpperChars = true);

};