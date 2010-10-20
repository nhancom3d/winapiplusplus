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

#ifndef _WINAPIPP_H_
#define _WINAPIPP_H_

#ifndef __cplusplus
#error WinAPI++ Must be using in C++ Project
#endif

#if defined(WINAPIPP_EXPORT)
#define WINAPIPP_API __declspec(dllexport)
#elif defined(WINAPIPP_STATICLIB)
#define WINAPIPP_API
#else
#define WINAPIPP_API __declspec(dllimport)
#endif

namespace WinApiPP
{
	// WinAPI++ Error Code
	enum ERRORCODE
	{
		ERRORCODE_SUCCESS,
		ERRORCODE_INVALID_PARAMETER,
		ERRORCODE_WINDOWS_ERROR
	};

	// WinAPI++ Return struct. Must 64 bits structure.
	struct BASERET
	{
		ERRORCODE LibError;
	};

	struct RETINT : BASERET
	{
		int nRetVal;
	};

	namespace KERNEL32
	{
		// Save Windows SDK Macro
#pragma push_macro("GetLastError")

		// Destroy Windows SDK Macro
#undef GetLastError

		// Declaration Function
		WINAPIPP_API ERRORCODE WINAPI GetLastError(std::string& strError, DWORD dwError = ::GetLastError()) throw();
		WINAPIPP_API ERRORCODE WINAPI GetLastError(std::wstring& strError, DWORD dwError = ::GetLastError()) throw();

		// Restore Windows SDK Macro
#pragma pop_macro("GetLastError")
	}

	namespace USER32
	{
		enum MESSAGEBOXFORMAT
		{
			MESSAGEBOXFORMAT_TEXT,
			MESSAGEBOXFORMAT_CAPTION
		};

		WINAPIPP_API RETINT __cdecl MessageBox(HWND hWnd, const char *pszText, const char *pszCaption, UINT uType, MESSAGEBOXFORMAT Format, ...) throw();
		WINAPIPP_API RETINT __cdecl MessageBox(HWND hWnd, const wchar_t *pszText, const wchar_t *pszCaption, UINT uType, MESSAGEBOXFORMAT Format, ...) throw();
	}
}

#endif /* WINAPIPP_H_ */
