#include "STDInclude.hpp"

namespace Utils
{
	namespace String
	{
		std::string ToLower(std::string input)
		{
			std::transform(input.begin(), input.end(), input.begin(), ::tolower);
			return input;
		}

		std::string ToUpper(std::string input)
		{
			std::transform(input.begin(), input.end(), input.begin(), ::toupper);
			return input;
		}

		bool EndsWith(std::string haystack, std::string needle)
		{
			return (strstr(haystack.data(), needle.data()) == (haystack.data() + haystack.size() - needle.size()));
		}

		std::string DumpHex(std::string data, std::string separator)
		{
			std::string result;

			for (unsigned int i = 0; i < data.size(); ++i)
			{
				if (i > 0)
				{
					result.append(separator);
				}

				result.append(fmt::sprintf("%02X", data[i] & 0xFF));
			}

			return result;
		}

		std::string XOR(std::string str, char value)
		{
			for (unsigned int i = 0; i < str.size(); ++i)
			{
				str[i] ^= value;
			}

			return str;
		}

		std::vector<std::string> Explode(const std::string& str, char delim)
		{
			std::vector<std::string> result;
			std::istringstream iss(str);

			for (std::string token; std::getline(iss, token, delim);)
			{
				std::string _entry = std::move(token);

				// Remove trailing 0x0 bytes
				while (_entry.size() && !_entry.back())
				{
					_entry = _entry.substr(0, _entry.size() - 1);
				}

				result.push_back(_entry);
			}

			return result;
		}

		void Replace(std::string &string, std::string find, std::string replace)
		{
			size_t nPos = 0;

			while ((nPos = string.find(find, nPos)) != std::string::npos)
			{
				string = string.replace(nPos, find.length(), replace);
				nPos += replace.length();
			}
		}

		bool StartsWith(std::string haystack, std::string needle)
		{
			return (haystack.size() >= needle.size() && !strncmp(needle.data(), haystack.data(), needle.size()));
		}

		// trim from start
		std::string &LTrim(std::string &s)
		{
			s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
			return s;
		}

		// trim from end
		std::string &RTrim(std::string &s)
		{
			s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
			return s;
		}

		// trim from both ends
		std::string &Trim(std::string &s)
		{
			return LTrim(RTrim(s));
		}

		std::string FormatTimeSpan(int milliseconds)
		{
			int secondsTotal = milliseconds / 1000;
			int seconds = secondsTotal % 60;
			int minutesTotal = secondsTotal / 60;
			int minutes = minutesTotal % 60;
			int hoursTotal = minutesTotal / 60;

			return fmt::sprintf("%02d:%02d:%02d", hoursTotal, minutes, seconds);
		}

		// Encodes a given string in Base64
		std::string EncodeBase64(const char* input, const unsigned long inputSize) {
			unsigned long outlen = long(inputSize + (inputSize / 3.0) + 16);
			unsigned char* outbuf = new unsigned char[outlen]; //Reserve output memory
			base64_encode((unsigned char*)input, inputSize, outbuf, &outlen);
			std::string ret((char*)outbuf, outlen);
			delete[] outbuf;
			return ret;
		}

		// Encodes a given string in Base64
		std::string EncodeBase64(const std::string& input) {
			return EncodeBase64(input.c_str(), input.size());
		}

		// Decodes a given string from Base64
		std::string DecodeBase64(const std::string& input) {
			unsigned char* out = new unsigned char[input.size()];
			unsigned long outlen = input.size();
			base64_decode((unsigned char*)input.c_str(), input.size(), out, &outlen);
			std::string ret((char*)out, outlen);
			delete[] out;
			return ret;
		}
	}
}
