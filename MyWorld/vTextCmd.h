#pragma once

using namespace std;

struct TextCmdFunc
{
	BOOL (*m_pFunc)( vScanner* pScanner );
	char* m_pCommand;  
	char* m_pAbbreviation;  
	char* m_pKrCommand;  
	char* m_pKrAbbreviation;  
	DWORD m_nServer;
	DWORD m_dwAuthorization;
	char* m_pszDesc;
};


class vTextCmd
{
public:
	void Inject();

	TextCmdFunc*	FindTextCmd(char* szCommand);
	TextCmdFunc*	FindTextCmdFromTable(char* szName);


	void	UpdateCmdTable();
	void	EditCommands();



private:
	map<string, TextCmdFunc*>		m_mapCommand;
	map<string, TextCmdFunc*>		m_mapCommandAbbreviation;
};


void vParsingCommand();