<<<<<<<< HEAD:keyboards/mechlovin/zed65/rev1/mcuconf.h
/* Copyright 2022 QMK
========
/* Copyright 2022 by rustedaperture
>>>>>>>> master:keyboards/gmmk/numpad/post_config.h
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

<<<<<<<< HEAD:keyboards/mechlovin/zed65/rev1/mcuconf.h
#include_next <mcuconf.h>


#undef STM32_SPI_USE_SPI1
#define STM32_SPI_USE_SPI1 TRUE
========
#ifndef TAP_CODE_DELAY
#    define TAP_CODE_DELAY 10
#endif
>>>>>>>> master:keyboards/gmmk/numpad/post_config.h
