//////////////////////////////////////////////////////////////////////
// Copyright 2010 - 2011 Putta Khunchalee
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

	//////////////////////////////////////////////////////////////////////
	// USER32.DLL C++ Extension
	//////////////////////////////////////////////////////////////////////

	namespace USER32
	{
#undef MessageBox

		RETINT __cdecl MessageBox(HWND hWnd, const char *pszText, const char *pszCaption, UINT uType, MESSAGEBOXFORMAT Format, ...) throw()
		{
			RETINT Ret;
			va_list args;
			char *pszFormatted = NULL;
			size_t uBufSize;
			
			::memset(&Ret, 0, sizeof(Ret));
			
			switch (Format)
			{
			case MESSAGEBOXFORMAT_TEXT:
				if (!pszText)
				{
					Ret.LibError = ERRORCODE_INVALID_PARAMETER;
					return Ret;
				}
				
				uBufSize = strlen(pszText) << 1;
				pszFormatted = new char [uBufSize];
				
				va_start(args, Format);
				while (StringCchVPrintfA(pszFormatted, uBufSize, pszText, args) != S_OK)
				{
					// Assume the error is STRSAFE_E_INSUFFICIENT_BUFFER
					uBufSize <<= 1;
					
					delete[] pszFormatted;
					
					pszFormatted = new char [uBufSize];
				}
				va_end(args);
				break;
			case MESSAGEBOXFORMAT_CAPTION:
				if (!pszCaption)
				{
					Ret.LibError = ERRORCODE_INVALID_PARAMETER;
					return Ret;
				}
				
				uBufSize = strlen(pszCaption) << 1;
				pszFormatted = new char [uBufSize];
				
				va_start(args, Format);
				while (StringCchVPrintfA(pszFormatted, uBufSize, pszCaption, args) != S_OK)
				{
					// Assume the error is STRSAFE_E_INSUFFICIENT_BUFFER
					uBufSize <<= 1;
					
					delete[] pszFormatted;
					
					pszFormatted = new char [uBufSize];
				}
				va_end(args);
				break;
			default:
				Ret.LibError = ERRORCODE_INVALID_PARAMETER;
				return Ret;
			}
			
			// Show message box
			if (MESSAGEBOXFORMAT_TEXT == Format)
				Ret.nRetVal = MessageBoxA(hWnd, pszFormatted, pszCaption, uType);
			else
				Ret.nRetVal = MessageBoxA(hWnd, pszText, pszFormatted, uType);
			
			// Clean up
			delete[] pszFormatted;
			
			return Ret;
		}
		
		RETINT __cdecl MessageBox(HWND hWnd, const wchar_t *pszText, const wchar_t *pszCaption, UINT uType, MESSAGEBOXFORMAT Format, ...) throw()
		{
			RETINT Ret;
			va_list args;
			wchar_t *pszFormatted = NULL;
			size_t uBufSize;
			
			::memset(&Ret, 0, sizeof(Ret));
			
			switch (Format)
			{
			case MESSAGEBOXFORMAT_TEXT:
				if (!pszText)
				{
					Ret.LibError = ERRORCODE_INVALID_PARAMETER;
					return Ret;
				}
				
				uBufSize = wcslen(pszText) << 1;
				pszFormatted = new wchar_t [uBufSize];
				
				va_start(args, Format);
				while (StringCchVPrintfW(pszFormatted, uBufSize, pszText, args) != S_OK)
				{
					// Assume the error is STRSAFE_E_INSUFFICIENT_BUFFER
					uBufSize <<= 1;
					
					delete[] pszFormatted;
					
					pszFormatted = new wchar_t [uBufSize];
				}
				va_end(args);
				break;
			case MESSAGEBOXFORMAT_CAPTION:
				if (!pszCaption)
				{
					Ret.LibError = ERRORCODE_INVALID_PARAMETER;
					return Ret;
				}
				
				uBufSize = wcslen(pszCaption) << 1;
				pszFormatted = new wchar_t [uBufSize];
				
				va_start(args, Format);
				while (StringCchVPrintfW(pszFormatted, uBufSize, pszCaption, args) != S_OK)
				{
					// Assume the error is STRSAFE_E_INSUFFICIENT_BUFFER
					uBufSize <<= 1;
					
					delete[] pszFormatted;
					
					pszFormatted = new wchar_t [uBufSize];
				}
				va_end(args);
				break;
			default:
				Ret.LibError = ERRORCODE_INVALID_PARAMETER;
				return Ret;
			}
			
			// Show message box
			if (MESSAGEBOXFORMAT_TEXT == Format)
				Ret.nRetVal = MessageBoxW(hWnd, pszFormatted, pszCaption, uType);
			else
				Ret.nRetVal = MessageBoxW(hWnd, pszText, pszFormatted, uType);
			
			// Clean up
			delete[] pszFormatted;
			
			return Ret;
		}
	}
}
