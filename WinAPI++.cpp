//////////////////////////////////////////////////////////////////////
// Copyright 2010 Putta Khunchalee
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WinAPI++.h"

namespace WinApiPP
{
	//////////////////////////////////////////////////////////////////////
	// KERNEL32.DLL C++ Extension
	//////////////////////////////////////////////////////////////////////
	namespace KERNEL32
	{
		ERRORCODE WINAPI GetLastError(std::string& strError, DWORD dwError) throw()
		{
			char *pszError;

			if (!&strError)
				return ERRORCODE_INVALID_PARAMETER;

			if (::FormatMessageA(FORMAT_MESSAGE_MAX_WIDTH_MASK | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwError, 0, reinterpret_cast<char *>(&pszError), 256, NULL))
			{
				strError = pszError;
				::LocalFree(pszError);

				return ERRORCODE_SUCCESS;
			}
			else
			{
				DWORD dwSaved = ::GetLastError();
				char szError[64];

				sprintf(szError, "Unknown Error (%u)", dwError);
				strError = szError;

				::SetLastError(dwSaved);

				return ERRORCODE_WINDOWS_ERROR;
			}
		}

		ERRORCODE WINAPI GetLastError(std::wstring& strError, DWORD dwError) throw()
		{
			wchar_t *pszError;

			if (!&strError)
				return ERRORCODE_INVALID_PARAMETER;

			if (::FormatMessageW(FORMAT_MESSAGE_MAX_WIDTH_MASK | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwError, 0, reinterpret_cast<wchar_t *>(&pszError), 256, NULL))
			{
				strError = pszError;
				::LocalFree(pszError);

				return ERRORCODE_SUCCESS;
			}
			else
			{
				DWORD dwSaved = ::GetLastError();
				wchar_t szError[64];

				swprintf(szError, sizeof(szError) - 1, L"Unknown Error (%u)", dwError);
				strError = szError;

				::SetLastError(dwSaved);

				return ERRORCODE_WINDOWS_ERROR;
			}
		}
	}
}
