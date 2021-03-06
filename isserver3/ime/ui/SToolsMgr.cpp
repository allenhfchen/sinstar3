#include "stdafx.h"
#include "SToolsMgr.h"
#include "../../../helper/helper.h"
#include <shellapi.h>

SToolsMgr::SToolsMgr()
{
}


SToolsMgr::~SToolsMgr()
{
}


int SToolsMgr::InitToolMenu(HMENU hMenu, const SStringT &strToolPath, int nStartId)
{
	WIN32_FIND_DATA findData;
	HANDLE hFind = FindFirstFile(strToolPath + _T("\\*.exe"), &findData);
	SMenu smenu(hMenu);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do {
			if (!(findData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY))
			{
				if (nStartId == R.id.menu_tool_base)
				{
					smenu.DeleteMenu(nStartId, MF_BYCOMMAND);
				}
				nStartId++;
				SStringT strFullPath = strToolPath + _T("\\") + findData.cFileName;
				m_mapTool[nStartId] = strFullPath;
				SStringT strDesc = ExtractToolInfo(strFullPath);
				HICON hIcon =::ExtractIcon(NULL,strFullPath,0);
				smenu.AppendMenu(MF_STRING, nStartId, strDesc,-1,hIcon);
			}
		} while (FindNextFile(hFind, &findData));
		FindClose(hFind);
	}
	return nStartId;
}

SStringT SToolsMgr::ExtractToolInfo(SStringT strToolPath)
{
	TCHAR szDesc[200];
	DWORD dwVer;
	Helper_PEVersion(strToolPath, &dwVer, NULL, szDesc);
	BYTE *pbyVer = (BYTE*)&dwVer;
	return SStringT().Format(_T("%s[%u.%u.%u.%u]"), szDesc, pbyVer[3], pbyVer[2], pbyVer[1], pbyVer[0]);
}

SStringT SToolsMgr::ToolPathFromID(int nToolID) const
{
	SStringT strToolPath;
	if (const SMap<int, SStringT>::CPair * p = m_mapTool.Lookup(nToolID))
	{
		strToolPath = p->m_value;
	}
	return strToolPath;
}
