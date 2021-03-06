#pragma once

#include <exception>
#include "CHSLTypedef.h"

#ifdef CHSL_DX
#include "DXGIInfo.h"
#endif

namespace cs
{

	class Exception : public std::exception
	{
	protected:
		// Mutable so that it can be written to from what()
		mutable std::string whatBuffer;

	private:
		std::string file, func;
		int line;

	public:
		Exception() = delete;
		Exception(cstr file, cstr func, int line);

		cstr what() const override;

		virtual cstr GetType() const;
		const std::string& GetFile() const;
		const std::string& GetFunc() const;
		int GetLine() const;
		std::string GetOriginString() const;
	};

	class ExceptionGeneral : public Exception
	{
	private:
		std::string str;

	public:
		ExceptionGeneral() = delete;
		ExceptionGeneral(cstr file, cstr func, int line, std::string string);

		cstr what() const override;

		virtual cstr GetType() const override;
		std::string GetString() const;
	};

#ifdef _WINDOWS_

	class ExceptionWindows : public Exception
	{
	private:
		HRESULT hr;
		std::vector<std::string> info;

	public:
		ExceptionWindows() = delete;
		ExceptionWindows(cstr file, cstr func, int line, HRESULT hResult);
		ExceptionWindows(cstr file, cstr func, int line, HRESULT hResult, std::vector<std::string> info);

		cstr what() const override;

		virtual cstr GetType() const override;
		HRESULT GetErrorCode() const;
		std::string GetErrorString() const;

		// Publicly avaliable helper functions
		static std::string TranslateHRESULT(HRESULT hResult);
		static std::string TranslateMessageArray(std::vector<std::string> messages);
	};

#endif

}

#ifdef CHSL_EXCEPT

#define EXC_TEMP() throw cs::Exception(__FILE__, __FUNCTION__, __LINE__)
#define EXC(str) throw cs::ExceptionGeneral(__FILE__, __FUNCTION__, __LINE__, str)

#ifdef _WINDOWS_
#define EXC_WINDOWSCHECK(hrcall) { HRESULT _hres = (hrcall); if (_hres != 0) { throw cs::ExceptionWindows(__FILE__, __FUNCTION__, __LINE__, _hres); } }
#define EXC_HRLAST() { HRESULT hres = GetLastError(); if (hres != 0) { throw cs::ExceptionWindows(__FILE__, __FUNCTION__, __LINE__, hres); } }

#include <sstream>

// Requires std::wostringstream. Outputs to vs debug console
#define DBOUT(s)																	\
{																					\
   std::wostringstream oStream;														\
   oStream << "L: " << __LINE__ << "  F: " << __FILE__ << "  STR: " << s << '\n';	\
   OutputDebugStringW( oStream.str().c_str() );										\
}
#endif

#ifdef CHSL_DX
#define EXC_COMCHECK(hrcall) { HRESULT _hres = (hrcall); if (FAILED(_hres)) { throw cs::ExceptionWindows(__FILE__, __FUNCTION__, __LINE__, _hres); } }
#ifdef inSAFE
#define EXC_COMCHECKINFO(hrcall) { dxgiInfo::set(); HRESULT _hres = (hrcall); if (FAILED(_hres)) { throw cs::ExceptionWindows(__FILE__, __FUNCTION__, __LINE__, _hres, dxgiInfo::getMessages()); } }
#define EXC_COMINFO(call) { dxgiInfo::set(); (call); std::vector<std::string> v = dxgiInfo::getMessages(); if (v.size() > 0) { throw cs::ExceptionGeneral(__FILE__, __FUNCTION__, __LINE__, cs::ExceptionWindows::TranslateMessageArray(dxgiInfo::getMessages())); } }
#else
#define EXC_COMCHECKINFO(hrcall) { HRESULT _hres = (hrcall); if (FAILED(_hres)) { throw cs::ExceptionWindows(__FILE__, __FUNCTION__, __LINE__, _hres); } }
#define EXC_COMINFO(call) { (call); }
#endif
#endif

#endif
	
