#pragma once

namespace DyEngine
{
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

// From glfw3.h
#define DY_KEY_SPACE           ::DyEngine::Key::Space
#define DY_KEY_APOSTROPHE      ::DyEngine::Key::Apostrophe    /* ' */
#define DY_KEY_COMMA           ::DyEngine::Key::Comma         /* , */
#define DY_KEY_MINUS           ::DyEngine::Key::Minus         /* - */
#define DY_KEY_PERIOD          ::DyEngine::Key::Period        /* . */
#define DY_KEY_SLASH           ::DyEngine::Key::Slash         /* / */
#define DY_KEY_0               ::DyEngine::Key::D0
#define DY_KEY_1               ::DyEngine::Key::D1
#define DY_KEY_2               ::DyEngine::Key::D2
#define DY_KEY_3               ::DyEngine::Key::D3
#define DY_KEY_4               ::DyEngine::Key::D4
#define DY_KEY_5               ::DyEngine::Key::D5
#define DY_KEY_6               ::DyEngine::Key::D6
#define DY_KEY_7               ::DyEngine::Key::D7
#define DY_KEY_8               ::DyEngine::Key::D8
#define DY_KEY_9               ::DyEngine::Key::D9
#define DY_KEY_SEMICOLON       ::DyEngine::Key::Semicolon     /* ; */
#define DY_KEY_EQUAL           ::DyEngine::Key::Equal         /* = */
#define DY_KEY_A               ::DyEngine::Key::A
#define DY_KEY_B               ::DyEngine::Key::B
#define DY_KEY_C               ::DyEngine::Key::C
#define DY_KEY_D               ::DyEngine::Key::D
#define DY_KEY_E               ::DyEngine::Key::E
#define DY_KEY_F               ::DyEngine::Key::F
#define DY_KEY_G               ::DyEngine::Key::G
#define DY_KEY_H               ::DyEngine::Key::H
#define DY_KEY_I               ::DyEngine::Key::I
#define DY_KEY_J               ::DyEngine::Key::J
#define DY_KEY_K               ::DyEngine::Key::K
#define DY_KEY_L               ::DyEngine::Key::L
#define DY_KEY_M               ::DyEngine::Key::M
#define DY_KEY_N               ::DyEngine::Key::N
#define DY_KEY_O               ::DyEngine::Key::O
#define DY_KEY_P               ::DyEngine::Key::P
#define DY_KEY_Q               ::DyEngine::Key::Q
#define DY_KEY_R               ::DyEngine::Key::R
#define DY_KEY_S               ::DyEngine::Key::S
#define DY_KEY_T               ::DyEngine::Key::T
#define DY_KEY_U               ::DyEngine::Key::U
#define DY_KEY_V               ::DyEngine::Key::V
#define DY_KEY_W               ::DyEngine::Key::W
#define DY_KEY_X               ::DyEngine::Key::X
#define DY_KEY_Y               ::DyEngine::Key::Y
#define DY_KEY_Z               ::DyEngine::Key::Z
#define DY_KEY_LEFT_BRACKET    ::DyEngine::Key::LeftBracket   /* [ */
#define DY_KEY_BACKSLASH       ::DyEngine::Key::Backslash     /* \ */
#define DY_KEY_RIGHT_BRACKET   ::DyEngine::Key::RightBracket  /* ] */
#define DY_KEY_GRAVE_ACCENT    ::DyEngine::Key::GraveAccent   /* ` */
#define DY_KEY_WORLD_1         ::DyEngine::Key::World1        /* non-US #1 */
#define DY_KEY_WORLD_2         ::DyEngine::Key::World2        /* non-US #2 */

/* Function keys */
#define DY_KEY_ESCAPE          ::DyEngine::Key::Escape
#define DY_KEY_ENTER           ::DyEngine::Key::Enter
#define DY_KEY_TAB             ::DyEngine::Key::Tab
#define DY_KEY_BACKSPACE       ::DyEngine::Key::Backspace
#define DY_KEY_INSERT          ::DyEngine::Key::Insert
#define DY_KEY_DELETE          ::DyEngine::Key::Delete
#define DY_KEY_RIGHT           ::DyEngine::Key::Right
#define DY_KEY_LEFT            ::DyEngine::Key::Left
#define DY_KEY_DOWN            ::DyEngine::Key::Down
#define DY_KEY_UP              ::DyEngine::Key::Up
#define DY_KEY_PAGE_UP         ::DyEngine::Key::PageUp
#define DY_KEY_PAGE_DOWN       ::DyEngine::Key::PageDown
#define DY_KEY_HOME            ::DyEngine::Key::Home
#define DY_KEY_END             ::DyEngine::Key::End
#define DY_KEY_CAPS_LOCK       ::DyEngine::Key::CapsLock
#define DY_KEY_SCROLL_LOCK     ::DyEngine::Key::ScrollLock
#define DY_KEY_NUM_LOCK        ::DyEngine::Key::NumLock
#define DY_KEY_PRINT_SCREEN    ::DyEngine::Key::PrintScreen
#define DY_KEY_PAUSE           ::DyEngine::Key::Pause
#define DY_KEY_F1              ::DyEngine::Key::F1
#define DY_KEY_F2              ::DyEngine::Key::F2
#define DY_KEY_F3              ::DyEngine::Key::F3
#define DY_KEY_F4              ::DyEngine::Key::F4
#define DY_KEY_F5              ::DyEngine::Key::F5
#define DY_KEY_F6              ::DyEngine::Key::F6
#define DY_KEY_F7              ::DyEngine::Key::F7
#define DY_KEY_F8              ::DyEngine::Key::F8
#define DY_KEY_F9              ::DyEngine::Key::F9
#define DY_KEY_F10             ::DyEngine::Key::F10
#define DY_KEY_F11             ::DyEngine::Key::F11
#define DY_KEY_F12             ::DyEngine::Key::F12
#define DY_KEY_F13             ::DyEngine::Key::F13
#define DY_KEY_F14             ::DyEngine::Key::F14
#define DY_KEY_F15             ::DyEngine::Key::F15
#define DY_KEY_F16             ::DyEngine::Key::F16
#define DY_KEY_F17             ::DyEngine::Key::F17
#define DY_KEY_F18             ::DyEngine::Key::F18
#define DY_KEY_F19             ::DyEngine::Key::F19
#define DY_KEY_F20             ::DyEngine::Key::F20
#define DY_KEY_F21             ::DyEngine::Key::F21
#define DY_KEY_F22             ::DyEngine::Key::F22
#define DY_KEY_F23             ::DyEngine::Key::F23
#define DY_KEY_F24             ::DyEngine::Key::F24
#define DY_KEY_F25             ::DyEngine::Key::F25

/* Keypad */
#define DY_KEY_KP_0            ::DyEngine::Key::KP0
#define DY_KEY_KP_1            ::DyEngine::Key::KP1
#define DY_KEY_KP_2            ::DyEngine::Key::KP2
#define DY_KEY_KP_3            ::DyEngine::Key::KP3
#define DY_KEY_KP_4            ::DyEngine::Key::KP4
#define DY_KEY_KP_5            ::DyEngine::Key::KP5
#define DY_KEY_KP_6            ::DyEngine::Key::KP6
#define DY_KEY_KP_7            ::DyEngine::Key::KP7
#define DY_KEY_KP_8            ::DyEngine::Key::KP8
#define DY_KEY_KP_9            ::DyEngine::Key::KP9
#define DY_KEY_KP_DECIMAL      ::DyEngine::Key::KPDecimal
#define DY_KEY_KP_DIVIDE       ::DyEngine::Key::KPDivide
#define DY_KEY_KP_MULTIPLY     ::DyEngine::Key::KPMultiply
#define DY_KEY_KP_SUBTRACT     ::DyEngine::Key::KPSubtract
#define DY_KEY_KP_ADD          ::DyEngine::Key::KPAdd
#define DY_KEY_KP_ENTER        ::DyEngine::Key::KPEnter
#define DY_KEY_KP_EQUAL        ::DyEngine::Key::KPEqual

#define DY_KEY_LEFT_SHIFT      ::DyEngine::Key::LeftShift
#define DY_KEY_LEFT_CONTROL    ::DyEngine::Key::LeftControl
#define DY_KEY_LEFT_ALT        ::DyEngine::Key::LeftAlt
#define DY_KEY_LEFT_SUPER      ::DyEngine::Key::LeftSuper
#define DY_KEY_RIGHT_SHIFT     ::DyEngine::Key::RightShift
#define DY_KEY_RIGHT_CONTROL   ::DyEngine::Key::RightControl
#define DY_KEY_RIGHT_ALT       ::DyEngine::Key::RightAlt
#define DY_KEY_RIGHT_SUPER     ::DyEngine::Key::RightSuper
#define DY_KEY_MENU            ::DyEngine::Key::Menu