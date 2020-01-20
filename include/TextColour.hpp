/**
 * @file TextColour.hpp
 * @author Simon Cahill (simon@h3lix.de)
 * @brief Contains an enumeration with different text colours which may be used by supported terminals.
 * @version 0.1
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020 Simon Cahill & Contributors.
 */

#ifndef LIBLOGPP_TEXTCOLOUR_HPP
#define LIBLOGPP_TEXTCOLOUR_HPP

namespace logpp {

    /**
     * @brief Enumeration containing different possible colours applicable to text.
     */
    enum class TextColour {
        None = 0,

        BlackBackground = 40,
        BlackForeground = 30,

        RedBackground = 41,
        RedForeground = 31,

        GreenBackground = 42,
        GreenForeground = 32,

        YellowBackground = 43,
        YellowForeground = 33,

        BlueBackground = 44,
        BlueForeground = 34,

        MagentaBackground = 45,
        MagentaForeground = 35,

        CyanBackground = 46,
        CyanForeground = 36,

        WhiteBackground = 47,
        WhiteForeground = 37
    };

}

#endif // LIBLOGPP_TEXTCOLOUR_HPP