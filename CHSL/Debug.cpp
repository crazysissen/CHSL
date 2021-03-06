#include "core.h"

#include "Debug.h"
#include <sstream>


// Temporary exception (BASE) ---------------------------------------------------------------------------------------------------------

cs::Exception::Exception(cstr file, cstr func, int line)
	:
	line(line),
	func(func),
	file(file)
{
}

cstr cs::Exception::what() const
{
	std::ostringstream stream;

	stream
		<< "[Type]: " << GetType() << "\n\n"
		<< GetOriginString();

	whatBuffer = stream.str();
	return whatBuffer.c_str();
}

cstr cs::Exception::GetType() const
{
	return "Temporary Exception";
}

const std::string& cs::Exception::GetFile() const
{
	return file;
}

const std::string& cs::Exception::GetFunc() const
{
	return func;
}

int cs::Exception::GetLine() const
{
	return line;
}

std::string cs::Exception::GetOriginString() const
{
	std::ostringstream stream;

	stream
		<< "[File]: " << file
		<< "\n[Function]: " << func
		<< "\n[Line]: " << line;

	return stream.str();
}



// General exception ---------------------------------------------------------------------------------------------------------

cs::ExceptionGeneral::ExceptionGeneral(cstr file, cstr func, int line, std::string string)
	:
	Exception(file, func, line),
	str(string)
{
}

cstr cs::ExceptionGeneral::what() const
{
	std::ostringstream stream;

	stream
		<< "[Type]: " << GetType() << "\n\n"
		<< GetOriginString() << "\n\n"
		<< "[Info]: " << GetString();

	whatBuffer = stream.str();
	return whatBuffer.c_str();
}

cstr cs::ExceptionGeneral::GetType() const
{
	return "Info Exception";
}

std::string cs::ExceptionGeneral::GetString() const
{
	return str;
}



// Windows exception ---------------------------------------------------------------------------------------------------------

#ifdef _WINDOWS_

cs::ExceptionWindows::ExceptionWindows(cstr file, cstr func, int line, HRESULT hResult)
	:
	Exception(file, func, line),
	hr(hResult),
	info(std::vector<std::string>())
{
}

cs::ExceptionWindows::ExceptionWindows(cstr file, cstr func, int line, HRESULT hResult, std::vector<std::string> info)
	:
	Exception(file, func, line),
	hr(hResult),
	info(info)
{

}

cstr cs::ExceptionWindows::what() const
{
	std::ostringstream stream;

	stream
		<< "[Type]: " << GetType() << "\n\n"
		<< GetOriginString() << "\n\n"
		<< "[Error Code]: " << "0x" << std::hex << std::uppercase << GetErrorCode() << "\n\n"
		<< "[Description]:\n" << GetErrorString();


	if (info.size() > 0) 
	{
		stream << "\n[Info]:" << TranslateMessageArray(info);
	}

	whatBuffer = stream.str();
	return whatBuffer.c_str();
}

cstr cs::ExceptionWindows::GetType() const
{
	return hr > 0 ? "Windows Exception" : "DX11 Graphics Exception";
}

HRESULT cs::ExceptionWindows::GetErrorCode() const
{
	return hr;
}

std::string cs::ExceptionWindows::GetErrorString() const
{
	return TranslateHRESULT(hr);
}

std::string cs::ExceptionWindows::TranslateHRESULT(HRESULT hResult)
{
	char* stringBuffer = nullptr;

	DWORD length = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, hResult,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPSTR>(&stringBuffer), 0, nullptr
	);

	if (length == 0)
	{
		return "Unidentified error";
	}
	
	string errorString = stringBuffer;
	LocalFree(stringBuffer); // Free the buffer allocated by windows

	return errorString;
}

std::string cs::ExceptionWindows::TranslateMessageArray(std::vector<std::string> messages)
{
	std::ostringstream stream;

	for (std::string s : messages)
	{
		stream << '\n' << s;
	}

	return stream.str();
}

#endif
