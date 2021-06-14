#ifndef _QueryFileCounts_H_
#define _QueryFileCounts_H_

int QueryFileCounts( LPCTSTR Path )
{
	queue<std::wstring> qFolders; 
	qFolders.push(Path);

	int fileCounts = 0;   
	WIN32_FIND_DATA findResult;
	HANDLE handle=NULL;

	while(qFolders.size()>0)
	{ 
		std::wstring tempFolder = qFolders.front();
		tempFolder.append(L"\\*.*");
		handle = FindFirstFile(tempFolder.c_str(), &findResult);
		do
		{   
			if (findResult.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if (lstrcmp(L".",findResult.cFileName)==0 || lstrcmp(L"..",findResult.cFileName)==0)
				{
					continue;
				} 
				tempFolder=qFolders.front();
				tempFolder.append(L"\\").append(findResult.cFileName);
				qFolders.push(tempFolder); 
			}else{
				fileCounts++;
			} 
		}
		while (FindNextFile(handle, &findResult));
		qFolders.pop();
	} 
	if (handle)
	{
		FindClose(handle);
		handle = NULL;
	} 
	return fileCounts;
}

#endif

