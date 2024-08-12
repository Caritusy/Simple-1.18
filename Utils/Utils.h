#pragma once

#include <algorithm>
#include <ctime>
#include <fstream>
#include <random>
#include <sstream>
#include <vector>
//#include "xorstr.h"
static const char* const KeyNames[] = {
	"Unknown",          // 0x00
	"LBUTTON",       // 0x01
	"RBUTTON",       // 0x02
	"CANCEL",        // 0x03
	"MBUTTON",       // 0x04
	"XBUTTON1",      // 0x05
	"XBUTTON2",      // 0x06
	"Unknown",          // 0x07
	"BACK",          // 0x08
	"TAB",           // 0x09
	"Unknown",          // 0x0A
	"Unknown",          // 0x0B
	"CLEAR",         // 0x0C
	"RETURN",        // 0x0D
	"Unknown",          // 0x0E
	"Unknown",          // 0x0F
	"SHIFT",         // 0x10
	"CONTROL",       // 0x11
	"MENU",          // 0x12 (Alt key)
	"PAUSE",         // 0x13
	"CAPITAL",       // 0x14 (Caps Lock)
	"KANA",          // 0x15
	"Unknown",          // 0x16
	"JUNJA",         // 0x17
	"FINAL",         // 0x18
	"KANJI",         // 0x19
	"Unknown",          // 0x1A
	"ESCAPE",        // 0x1B
	"CONVERT",       // 0x1C
	"NONCONVERT",    // 0x1D
	"ACCEPT",        // 0x1E
	"MODECHANGE",    // 0x1F
	"SPACE",         // 0x20
	"PRIOR",         // 0x21 (Page Up)
	"NEXT",          // 0x22 (Page Down)
	"END",           // 0x23
	"HOME",          // 0x24
	"LEFT",          // 0x25
	"UP",            // 0x26
	"RIGHT",         // 0x27
	"DOWN",          // 0x28
	"SELECT",        // 0x29
	"PRINT",         // 0x2A
	"EXECUTE",       // 0x2B
	"SNAPSHOT",      // 0x2C (Print Screen)
	"INSERT",        // 0x2D
	"DELETE",        // 0x2E
	"HELP",          // 0x2F
	"0",                // 0x30
	"1",                // 0x31
	"2",                // 0x32
	"3",                // 0x33
	"4",                // 0x34
	"5",                // 0x35
	"6",                // 0x36
	"7",                // 0x37
	"8",                // 0x38
	"9",                // 0x39
	"Unknown",          // 0x3A
	"Unknown",          // 0x3B
	"Unknown",          // 0x3C
	"Unknown",          // 0x3D
	"Unknown",          // 0x3E
	"Unknown",          // 0x3F
	"Unknown",          // 0x40
	"A",                // 0x41
	"B",                // 0x42
	"C",                // 0x43
	"D",                // 0x44
	"E",                // 0x45
	"F",                // 0x46
	"G",                // 0x47
	"H",                // 0x48
	"I",                // 0x49
	"J",                // 0x4A
	"K",                // 0x4B
	"L",                // 0x4C
	"M",                // 0x4D
	"N",                // 0x4E
	"O",                // 0x4F
	"P",                // 0x50
	"Q",                // 0x51
	"R",                // 0x52
	"S",                // 0x53
	"T",                // 0x54
	"U",                // 0x55
	"V",                // 0x56
	"W",                // 0x57
	"X",                // 0x58
	"Y",                // 0x59
	"Z",                // 0x5A
	"LWIN",          // 0x5B
	"RWIN",          // 0x5C
	"APPS",          // 0x5D
	"Unknown",          // 0x5E
	"SLEEP",         // 0x5F
	"NUMPAD0",       // 0x60
	"NUMPAD1",       // 0x61
	"NUMPAD2",       // 0x62
	"NUMPAD3",       // 0x63
	"NUMPAD4",       // 0x64
	"NUMPAD5",       // 0x65
	"NUMPAD6",       // 0x66
	"NUMPAD7",       // 0x67
	"NUMPAD8",       // 0x68
	"NUMPAD9",       // 0x69
	"MULTIPLY",      // 0x6A
	"ADD",           // 0x6B
	"SEPARATOR",     // 0x6C
	"SUBTRACT",      // 0x6D
	"DECIMAL",       // 0x6E
	"DIVIDE",        // 0x6F
	"F1",            // 0x70
	"F2",            // 0x71
	"F3",            // 0x72
	"F4",            // 0x73
	"F5",            // 0x74
	"F6",            // 0x75
	"F7",            // 0x76
	"F8",            // 0x77
	"F9",            // 0x78
	"F10",           // 0x79
	"F11",           // 0x7A
	"F12",           // 0x7B
	"F13",           // 0x7C
	"F14",           // 0x7D
	"F15",           // 0x7E
	"F16",           // 0x7F
	"F17",           // 0x80
	"F18",           // 0x81
	"F19",           // 0x82
	"F20",           // 0x83
	"F22",           // 0x84
	"F23",           // 0x85
	"F24",           // 0x86
	"Unknown",          // 0x87
	"Unknown",          // 0x88
	"Unknown",          // 0x89
	"Unknown",          // 0x8A
	"Unknown",          // 0x8B
	"Unknown",          // 0x8C
	"Unknown",          // 0x8D
	"Unknown",          // 0x8E
	"Unknown",          // 0x8F
	"NUMLOCK",       // 0x90
	"SCROLL",        // 0x91
	"OEM_NEC_EQUAL", // 0x92
	"OEM_FJ_MASSHOU",// 0x93
	"OEM_FJ_TOUROKU",// 0x94
	"OEM_FJ_LOYA",   // 0x95
	"OEM_FJ_ROYA",   // 0x96
	"Unknown",          // 0x97
	"Unknown",          // 0x98
	"Unknown",          // 0x99
	"Unknown",          // 0x9A
	"Unknown",          // 0x9B
	"Unknown",          // 0x9C
	"Unknown",          // 0x9D
	"Unknown",          // 0x9E
	"Unknown",          // 0x9F
	"LSHIFT",        // 0xA0
	"RSHIFT",        // 0xA1
	"LCONTROL",      // 0xA2
	"RCONTROL",      // 0xA3
	"LMENU",         // 0xA4 (Left Alt)
	"RMENU",         // 0xA5 (Right Alt)
	"BROWSER_BACK",  // 0xA6
	"BROWSER_FORWARD",// 0xA7
	"BROWSER_REFRESH",// 0xA8
	"BROWSER_STOP",  // 0xA9
	"BROWSER_SEARCH",// 0xAA
	"BROWSER_FAVORITES",// 0xAB
	"BROWSER_HOME",  // 0xAC
	"VOLUME_MUTE",   // 0xAD
	"VOLUME_DOWN",   // 0xAE
	"VOLUME_UP",     // 0xAF
	"MEDIA_NEXT_TRACK",// 0xB0
	"MEDIA_PREV_TRACK",// 0xB1
	"MEDIA_STOP",    // 0xB2
	"MEDIA_PLAY_PAUSE",// 0xB3
	"LAUNCH_MAIL",   // 0xB4
	"LAUNCH_MEDIA_SELECT",// 0xB5
	"LAUNCH_APP1",   // 0xB6
	"LAUNCH_APP2",   // 0xB7
	"Unknown",          // 0xB8
	"Unknown",          // 0xB9
	"OEM_1",         // 0xBA
	"OEM_PLUS",      // 0xBB
	"OEM_COMMA",     // 0xBC
	"OEM_MINUS",     // 0xBD
	"OEM_PERIOD",    // 0xBE
	"OEM_2",         // 0xBF
	"OEM_3",         // 0xC0
	"Unknown",          // 0xC1
	"Unknown",          // 0xC2
	"Unknown",          // 0xC3
	"Unknown",          // 0xC4
	"Unknown",          // 0xC5
	"Unknown",          // 0xC6
	"Unknown",          // 0xC7
	"Unknown",          // 0xC8
	"Unknown",          // 0xC9
	"Unknown",          // 0xCA
	"Unknown",          // 0xCB
	"Unknown",          // 0xCC
	"Unknown",          // 0xCD
	"Unknown",          // 0xCE
	"Unknown",          // 0xCF
	"Unknown",          // 0xD0
	"Unknown",          // 0xD1
	"Unknown",          // 0xD2
	"Unknown",          // 0xD3
	"Unknown",          // 0xD4
	"Unknown",          // 0xD5
	"Unknown",          // 0xD6
	"Unknown",          // 0xD7
	"Unknown",          // 0xD8
	"Unknown",          // 0xD9
	"Unknown",          // 0xDA
	"OEM_4",         // 0xDB
	"OEM_5",         // 0xDC
	"OEM_6",         // 0xDD
	"OEM_7",         // 0xDE
	"OEM_8",         // 0xDF
	"Unknown",          // 0xE0
	"Unknown",          // 0xE1
	"OEM_AX",        // 0xE2
	"OEM_102",       // 0xE3
	"ICO_HELP",      // 0xE4
	"ICO_00",        // 0xE5
	"PROCESSKEY",    // 0xE6
	"ICO_CLEAR",     // 0xE7
	"PACKET",        // 0xE8
	"Unknown",          // 0xE9
	"Unknown",          // 0xEA
	"Unknown",          // 0xEB
	"Unknown",          // 0xEC
	"Unknown",          // 0xED
	"Unknown",          // 0xEE
	"Unknown",          // 0xEF
	"Unknown",          // 0xF0
	"Unknown",          // 0xF1
	"Unknown",          // 0xF2
	"Unknown",          // 0xF3
	"Unknown",          // 0xF4
	"Unknown",          // 0xF5
	"ATTN",          // 0xF6
	"CRSEL",         // 0xF7
	"EXSEL",         // 0xF8
	"EREOF",         // 0xF9
	"PLAY",          // 0xFA
	"ZOOM",          // 0xFB
	"NONAME",        // 0xFC
	"PA1",           // 0xFD
	"OEM_CLEAR"      // 0xFE
};

#define INRANGE(x, a, b) (x >= a && x <= b)
#define GET_BYTE(x) (GET_BITS(x[0]) << 4 | GET_BITS(x[1]))
#define GET_BITS(x) (INRANGE((x & (~0x20)), 'A', 'F') ? ((x & (~0x20)) - 'A' + 0xa) : (INRANGE(x, '0', '9') ? x - '0' : 0))

static inline float UImFmod(float x, float y) { return fmodf(x, y); }
static inline float UImFabs(float x) { return fabsf(x); }
template <typename T>
static inline void UImSwap(T& a, T& b) {
	T tmp = a;
	a = b;
	b = tmp;
}

#ifdef JM_XORSTR_HPP
#define FindSignature(szSignature) Utils::FindSignatureModule("Minecraft.Windows.exe", xorstr_(szSignature))
#define GetOffsetFromSig(szSignature, offset) Utils::getOffsetFromSignature(xorstr_(szSignature), offset)
#define GetVtableFromSig(szSignature, offset) Utils::getVtableFromSignature(xorstr_(szSignature), offset)
#define PatchBytes(src, newBytes, size) Utils::patchBytes(src, newBytes, size)
#define NopBytes(src, size) Utils::nopBytes(src, size)
#else
#define FindSignature(szSignature) Utils::FindSignatureModule("Minecraft.Windows.exe", szSignature)
#define GetOffsetFromSig(szSignature, offset) Utils::getOffsetFromSignature(szSignature, offset)
#define GetVtableFromSig(szSignature, offset) Utils::getVtableFromSignature(szSignature, offset)
#define PatchBytes(src, newBytes, size) Utils::patchBytes(src, newBytes, size)
#define NopBytes(src, size) Utils::nopBytes(src, size)
#endif

struct Vec3i;
class Utils{
public:
	static __forceinline unsigned __int32 rotBy(int in, unsigned int by) {
		auto mut = static_cast<unsigned __int64>(in);
		return ((mut & 0x7FFFFFui64) | ((static_cast<unsigned int>(in) >> 8u) & 0x800000u) /*copy sign bit*/) << by;
	}
	static bool isEventOccurring(double probability)/*¸ÅÂÊÊÂ¼þ*/{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dis(0.0, 1.0);
		double randomValue = dis(gen);
		if (randomValue <= probability) {
			return true;
		}
		else {
			return false;
		}
	}
	static size_t posToHash(const Vec3i& pos);

	template <typename type>

	static inline auto lerp(type a, type b, float t) -> type {
		return a + t * (b - a);
	};

	static inline unsigned int getCrcHash(const char* str, int seed = 0) {
		static unsigned int crc32_lut[256] = { 0 };
		if (!crc32_lut[1]) {
			const unsigned int polynomial = 0xEDB88320;
			for (unsigned int i = 0; i < 256; i++) {
				unsigned int crc = i;
				for (unsigned int j = 0; j < 8; j++)
					crc = (crc >> 1) ^ (((unsigned int)(-((int)(crc & 1)))) & polynomial);
				crc32_lut[i] = crc;
			}
		}

		seed = ~seed;
		unsigned int crc = seed;
		const unsigned char* current = (const unsigned char*)str;
		{
			// Zero-terminated string
			while (unsigned char c = *current++) {
				// We support a syntax of "label###id" where only "###id" is included in the hash, and only "label" gets displayed.
				// Because this syntax is rarely used we are optimizing for the common case.
				// - If we reach ### in the string we discard the hash so far and reset to the seed.
				// - We don't do 'current += 2; continue;' after handling ### to keep the code smaller.
				if (c == '#' && current[0] == '#' && current[1] == '#')
					crc = seed;
				crc = (crc >> 8) ^ crc32_lut[(crc & 0xFF) ^ c];
			}
		}
		return ~crc;
	}

	static inline const char* getKeybindName(int keybind) {
		return KeyNames[keybind];
	};

	static inline void ColorConvertRGBtoHSV(float r, float g, float b, float& out_h, float& out_s, float& out_v) {
		float K = 0.f;
		if (g < b) {
			UImSwap(g, b);
			K = -1.f;
		}
		if (r < g) {
			UImSwap(r, g);
			K = -2.f / 6.f - K;
		}

		const float chroma = r - (g < b ? g : b);
		out_h = UImFabs(K + (g - b) / (6.f * chroma + 1e-20f));
		out_s = chroma / (r + 1e-20f);
		out_v = r;
	};

	static inline void ColorConvertHSVtoRGB(float h, float s, float v, float& out_r, float& out_g, float& out_b) {
		if (s == 0.0f) {
			// gray
			out_r = out_g = out_b = v;
			return;
		}

		h = UImFmod(h, 1.0f) / (60.0f / 360.0f);
		int i = (int)h;
		float f = h - (float)i;
		float p = v * (1.0f - s);
		float q = v * (1.0f - s * f);
		float t = v * (1.0f - s * (1.0f - f));

		switch (i) {
		case 0:
			out_r = v;
			out_g = t;
			out_b = p;
			break;
		case 1:
			out_r = q;
			out_g = v;
			out_b = p;
			break;
		case 2:
			out_r = p;
			out_g = v;
			out_b = t;
			break;
		case 3:
			out_r = p;
			out_g = q;
			out_b = v;
			break;
		case 4:
			out_r = t;
			out_g = p;
			out_b = v;
			break;
		case 5:
		default:
			out_r = v;
			out_g = p;
			out_b = q;
			break;
		}
	};

	template <unsigned int IIdx, typename TRet, typename... TArgs>

	static inline auto CallVFunc(void* thisptr, TArgs... argList) -> TRet {
		//if (thisptr == nullptr)
		//return nullptr;
		using Fn = TRet(__thiscall*)(void*, decltype(argList)...);
		return (*static_cast<Fn**>(thisptr))[IIdx](thisptr, argList...);
	}
	template < typename ret>

	static inline auto FuncFromSigOffset(uintptr_t sig, int offset) -> ret {
		return reinterpret_cast<ret>(sig + offset + 4 + *reinterpret_cast<int*>(sig + offset));
	}

	static std::string base64_encode(const std::string& in) {
		std::string out;

		int val = 0, valb = -6;
		for (unsigned char c : in) {
			val = (val << 8) + c;
			valb += 8;
			while (valb >= 0) {
				out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[(val >> valb) & 0x3F]);
				valb -= 6;
			}
		}
		if (valb > -6) out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[((val << 8) >> (valb + 8)) & 0x3F]);
		while (out.size() % 4) out.push_back('=');
		return out;
	}

	static std::string base64_decode(const std::string& in) {
		std::string out;

		std::vector<int> T(256, -1);
		for (int i = 0; i < 64; i++) T["ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[i]] = i;

		int val = 0, valb = -8;
		for (unsigned char c : in) {
			if (T[c] == -1) break;
			val = (val << 6) + T[c];
			valb += 6;
			if (valb >= 0) {
				out.push_back(char((val >> valb) & 0xFF));
				valb -= 8;
			}
		}
		return out;
	}


	static inline std::string randomString(const int size) {
		std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
		std::random_device rd;
		std::mt19937 generator(rd());
		std::shuffle(str.begin(), str.end(), generator);
		return str.substr(0, size);
	}

	static std::string getClipboardText();

	static void setClipboardText(std::string& text);

	static std::string readFileContents(std::wstring filePath) {
		std::ifstream fileStr(filePath, std::ios::in | std::ios::binary);
		if (fileStr) {
			std::string contents;
			fileStr.seekg(0, std::ios::end);
			contents.resize(fileStr.tellg());
			fileStr.seekg(0, std::ios::beg);
			fileStr.read(&contents[0], contents.size());
			fileStr.close();
			return contents;
		}
		return "";
	}

	static std::wstring wreadFileContents(std::wstring filePath) {
		std::wifstream fileStr(filePath, std::ios::in | std::ios::binary);
		if (fileStr) {
			std::wstring contents;
			fileStr.seekg(0, std::ios::end);
			contents.resize(fileStr.tellg());
			fileStr.seekg(0, std::ios::beg);
			fileStr.read(&contents[0], contents.size());
			fileStr.close();
			return contents;
		}
		return L"";
	}

	static uintptr_t FindSignatureModule(const char* szModule, const char* szSignature);

	static uintptr_t getOffsetFromSignature(const char* szSignature, int offset);

	static uintptr_t** getVtableFromSignature(const char* szSignature, int offset);

	template <typename T>
	static T readPointer(std::uintptr_t ptrAddress, std::initializer_list<std::uintptr_t> Offsets) {
		return Game.getSlimMem()->ReadPtr<T>(ptrAddress, Offsets);
	};
	static void GetCurrentSystemTime(tm& timeInfo);

	static void ApplySystemTime(std::stringstream* ss);
		
	static uintptr_t getBase();

	static std::string sanitize(std::string text);
	static std::string onlyOneLine(std::string text);
	static std::wstring stringToWstring(std::string txt);
	static std::string StringToUTF8(const std::string& gbkData);

	static bool endsWith(std::wstring const& fullString, std::wstring const& ending) {
		if (fullString.length() >= ending.length()) {
			return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
		}
		else {
			return false;
		}
	}

	static void ApplyRainbow(float* rcolors, const float modifier = 0.003f) {
		if (rcolors[3] < 1) {
			rcolors[0] = 1;
			rcolors[1] = 0.6f;
			rcolors[2] = 0.6f;
			rcolors[3] = 1;
		}

		Utils::ColorConvertRGBtoHSV(rcolors[0], rcolors[1], rcolors[2], rcolors[0], rcolors[1], rcolors[2]);

		rcolors[0] += modifier;
		if (rcolors[0] >= 1)
			rcolors[0] = 0;

		Utils::ColorConvertHSVtoRGB(rcolors[0], rcolors[1], rcolors[2], rcolors[0], rcolors[1], rcolors[2]);
	}

	static std::string getRttiBaseClassName(void* ptr);

	static void nopBytes(void* dst, unsigned int size);

	static void copyBytes(void* src, void* dst, unsigned int size);

	static void patchBytes(void* dst, void* src, unsigned int size);
};

