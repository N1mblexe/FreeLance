#ifndef COLOR_H
#define COLOR_H

#include <iostream>

/**
 * Color namespace providing ANSI color codes for terminal output
 *
 * Usage in C++:
 *   std::cout << Color::GREEN << "Success!" << Color::RESET << std::endl;
 *
 * Usage in Makefile:
 *   $(info $(COLOR_GREEN)Building...$(COLOR_RESET))
 */

namespace Color {
// Text Colors (Bright Neon Variants)
const char *const RESET = "\033[0m";
const char *const BLACK = "\033[90m";
const char *const RED = "\033[91m";
const char *const GREEN = "\033[92m";
const char *const YELLOW = "\033[93m";
const char *const BLUE = "\033[94m";
const char *const MAGENTA = "\033[95m";
const char *const CYAN = "\033[96m";
const char *const WHITE = "\033[97m";

// Bright/Bold Colors
const char *const BRIGHT_BLACK = "\033[90m";
const char *const BRIGHT_RED = "\033[91m";
const char *const BRIGHT_GREEN = "\033[92m";
const char *const BRIGHT_YELLOW = "\033[93m";
const char *const BRIGHT_BLUE = "\033[94m";
const char *const BRIGHT_MAGENTA = "\033[95m";
const char *const BRIGHT_CYAN = "\033[96m";
const char *const BRIGHT_WHITE = "\033[97m";

// Background Colors
const char *const BG_BLACK = "\033[40m";
const char *const BG_RED = "\033[41m";
const char *const BG_GREEN = "\033[42m";
const char *const BG_YELLOW = "\033[43m";
const char *const BG_BLUE = "\033[44m";
const char *const BG_MAGENTA = "\033[45m";
const char *const BG_CYAN = "\033[46m";
const char *const BG_WHITE = "\033[47m";

// Text Styles
const char *const BOLD = "\033[1m";
const char *const DIM = "\033[2m";
const char *const ITALIC = "\033[3m";
const char *const UNDERLINE = "\033[4m";
const char *const BLINK = "\033[5m";
const char *const REVERSE = "\033[7m";
const char *const HIDDEN = "\033[8m";

// Semantic colors for common use cases (Bright Neon)
const char *const SUCCESS = "\033[92m";     // Bright Green
const char *const ERROR = "\033[91m";       // Bright Red
const char *const WARNING = "\033[93m";     // Bright Yellow
const char *const INFO = "\033[96m";        // Bright Cyan
const char *const DEBUG_COLOR = "\033[95m"; // Bright Magenta
const char *const HEADER = "\033[1;94m";    // Bold Bright Blue
} // namespace Color

// Makefile-compatible defines (for export to shell)
// These are duplicates for documentation purposes
// Actual Makefile colors are defined in the Makefile itself

#endif // COLOR_H
