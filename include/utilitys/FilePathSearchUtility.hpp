#pragma once

class FilePathSearchUtilty
{
public:

	//Searching all Files and Folders names with a specific prefix 
	static std::vector<wxString> SearchDirPath(const std::vector<wxString>& elements, const wxString& searchPrefix, bool IgnoreUpperLower = true);


private:
	FilePathSearchUtilty();
};