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

#include <string>
#include <stdarg.h>

namespace WinApiPP
{
	namespace KERNEL32
	{
		WINAPIPP_API DWORD WINAPI GetLastError(std::string& strError, DWORD dwError = ::GetLastError()) throw();
		WINAPIPP_API DWORD WINAPI GetLastError(std::wstring& strError, DWORD dwError = ::GetLastError()) throw();
	}

	namespace USER32
	{
		WINAPIPP_API int __cdecl MessageBoxA(const char *pszText, const char *pszCaption, va_list args, UINT uType = MB_OK, HWND hWnd = ::GetActiveWindow()) throw();
		WINAPIPP_API int __cdecl MessageBoxW(const wchar_t *pszText, const wchar_t *pszCaption, va_list args, UINT uType = MB_OK, HWND hWnd = ::GetActiveWindow()) throw();
		WINAPIPP_API int __cdecl MessageBoxA(const char *pszText, const char *pszCaption, UINT uType = MB_OK, HWND hWnd = ::GetActiveWindow(), ...) throw();
		WINAPIPP_API int __cdecl MessageBoxW(const wchar_t *pszText, const wchar_t *pszCaption, UINT uType = MB_OK, HWND hWnd = ::GetActiveWindow(), ...) throw();
	}
}

#endif // WINAPIPP_H_
