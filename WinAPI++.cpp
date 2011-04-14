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
		DWORD WINAPI GetLastError(std::string& strError, DWORD dwError) throw()
		{
			char *pszError;

			// Parameter Check
			if (!&strError)
				return ERROR_INVALID_PARAMETER;

			// Load Error Message
			if (::FormatMessageA(FORMAT_MESSAGE_MAX_WIDTH_MASK | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwError, 0, reinterpret_cast<char *>(&pszError), 256, NULL))
			{
				try
				{
					strError = pszError;
					dwError = ERROR_SUCCESS;
				}
				catch (std::bad_alloc)
				{
					dwError = ERROR_NOT_ENOUGH_MEMORY;
				}
				catch (...)
				{
					// Assume it is access violation.
					dwError = ERROR_INVALID_PARAMETER;
				}

				// Free resource
				::LocalFree(pszError);

				return dwError;
			}
			else
				return ::GetLastError();
		}

		DWORD WINAPI GetLastError(std::wstring& strError, DWORD dwError) throw()
		{
			wchar_t *pszError;

			// Parameter Check
			if (!&strError)
				return ERROR_INVALID_PARAMETER;

			if (::FormatMessageW(FORMAT_MESSAGE_MAX_WIDTH_MASK | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwError, 0, reinterpret_cast<wchar_t *>(&pszError), 256, NULL))
			{
				try
				{
					strError = pszError;
					dwError = ERROR_SUCCESS;
				}
				catch (std::bad_alloc)
				{
					dwError = ERROR_NOT_ENOUGH_MEMORY;
				}
				catch (...)
				{
					// Assume it is access violation.
					dwError = ERROR_INVALID_PARAMETER;
				}

				// Free resource
				::LocalFree(pszError);

				return dwError;
			}
			else
				return ::GetLastError();
		}
	}

	//////////////////////////////////////////////////////////////////////
	// USER32.DLL C++ Extension
	//////////////////////////////////////////////////////////////////////

	namespace USER32
	{
		int __cdecl MessageBoxA(const char *pszText, const char *pszCaption, va_list args, UINT uType, HWND hWnd) throw()
		{
			char *pszFormatted;
			size_t uBufSize;
			int nRet;

			// Calculate buffer size
			__try
			{
				uBufSize = ::strlen(pszText) * 2;
			}
			__except(EXCEPTION_EXECUTE_HANDLER)
			{
				// pszText is not valid pointer.
				::SetLastError(ERROR_INVALID_PARAMETER);
				return 0;
			}

			// Alloc buffer
			pszFormatted = reinterpret_cast<char *>(calloc(uBufSize, sizeof(char)));

			if (!pszFormatted)
			{
				::SetLastError(ERROR_NOT_ENOUGH_MEMORY);
				return 0;
			}

			// Format message
			__try
			{
				while (FAILED(StringCchVPrintfA(pszFormatted, uBufSize, pszText, args)))
				{
					// Assume the error is STRSAFE_E_INSUFFICIENT_BUFFER
					uBufSize *= 2;

					::free(pszFormatted);

					pszFormatted = reinterpret_cast<char *>(calloc(uBufSize, sizeof(char)));

					if (!pszFormatted)
					{
						::SetLastError(ERROR_NOT_ENOUGH_MEMORY);
						return 0;
					}
				}
			}
			__except(EXCEPTION_EXECUTE_HANDLER)
			{
				::free(pszFormatted);
				::SetLastError(ERROR_INVALID_PARAMETER);
				return 0;
			}

			// Show Message Box
			nRet = ::MessageBoxA(hWnd, pszFormatted, pszCaption, uType);

			// Clean up
			::free(pszFormatted);

			return nRet;
		}

		int __cdecl MessageBoxW(const wchar_t *pszText, const wchar_t *pszCaption, va_list args, UINT uType, HWND hWnd) throw()
		{
			wchar_t *pszFormatted;
			size_t uBufSize;
			int nRet;

			// Calculate buffer size
			__try
			{
				uBufSize = ::wcslen(pszText) * 2;
			}
			__except(EXCEPTION_EXECUTE_HANDLER)
			{
				// pszText is not valid pointer.
				::SetLastError(ERROR_INVALID_PARAMETER);
				return 0;
			}

			// Alloc buffer
			pszFormatted = reinterpret_cast<wchar_t *>(calloc(uBufSize, sizeof(wchar_t)));

			if (!pszFormatted)
			{
				::SetLastError(ERROR_NOT_ENOUGH_MEMORY);
				return 0;
			}

			// Format message
			__try
			{
				while (FAILED(StringCchVPrintfW(pszFormatted, uBufSize, pszText, args)))
				{
					// Assume the error is STRSAFE_E_INSUFFICIENT_BUFFER
					uBufSize *= 2;

					::free(pszFormatted);

					pszFormatted = reinterpret_cast<wchar_t *>(calloc(uBufSize, sizeof(wchar_t)));

					if (!pszFormatted)
					{
						::SetLastError(ERROR_NOT_ENOUGH_MEMORY);
						return 0;
					}
				}
			}
			__except(EXCEPTION_EXECUTE_HANDLER)
			{
				::free(pszFormatted);
				::SetLastError(ERROR_INVALID_PARAMETER);
				return 0;
			}

			// Show Message Box
			nRet = ::MessageBoxW(hWnd, pszFormatted, pszCaption, uType);

			// Clean up
			::free(pszFormatted);

			return nRet;
		}

		int __cdecl MessageBoxA(const char *pszText, const char *pszCaption, UINT uType, HWND hWnd, ...) throw()
		{
			va_list args;
			int nRet;

			va_start(args, hWnd);
			nRet = MessageBoxA(pszText, pszCaption, args, uType, hWnd);
			va_end(args);

			return nRet;
		}
		
		int __cdecl MessageBoxW(const wchar_t *pszText, const wchar_t *pszCaption, UINT uType, HWND hWnd, ...) throw()
		{
			va_list args;
			int nRet;

			va_start(args, hWnd);
			nRet = MessageBoxW(pszText, pszCaption, args, uType, hWnd);
			va_end(args);

			return nRet;
		}
	}
}
