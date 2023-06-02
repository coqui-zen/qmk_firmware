// Copyright 2023 murasaki (@murasaki)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define MATRIX_ROW_PINS { D3, D5, F5, F1 }
#define MATRIX_COL_PINS { F0, F4, F6, F7, C7, C6, B6, B5, B4, D7, D6, D4 }
#define DIODE_DIRECTION COL2ROW
#define ENCODERS_PAD_A { D1 }
#define ENCODERS_PAD_B { D2 }

/* VIA Configuration */
#define DYNAMIC_KEYMAP_LAYER_COUNT 8