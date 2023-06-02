// Copyright 2023 murasaki (@murasaki)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define MATRIX_ROW_PINS { F6, B0, B6, C6 }
#define MATRIX_COL_PINS { C7, F7, B5, B4, D7, D6, D4,  D5, D3, D2, D1, D0 }
#define DIODE_DIRECTION COL2ROW
#define ENCODERS_PAD_A { E6 }
#define ENCODERS_PAD_B { B7 }

/* VIA Configuration */
#define DYNAMIC_KEYMAP_LAYER_COUNT 8