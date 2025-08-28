#pragma once

class FilePathSearchUtilty
{
public:

	//Searching all Files and Folders names with a specific prefix 
	static std::vector<wxString> SearchDirPath(const wxString& directoryPath, const wxString& searchPrefix, bool IgnoreUpperLower = true);


private:
	FilePathSearchUtilty();
};