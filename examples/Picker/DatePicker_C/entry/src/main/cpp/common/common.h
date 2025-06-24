/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ARKUI_CAPI_DEMO_COMMON_TEST_H
#define ARKUI_CAPI_DEMO_COMMON_TEST_H

#include <napi/native_api.h>
#include <hilog/log.h>

namespace ArkUIDatePickerCApiDemo {

#define PARAM_0 0
#define PARAM_1 1
#define PARAM_2 2
#define PARAM_3 3
#define PARAM_4 4
#define PARAM_5 5
#define PARAM_6 6
#define PARAM_7 7
#define PARAM_8 8
#define PARAM_9 9
#define PARAM_10 10
#define PARAM_11 11
#define PARAM_12 12
#define PARAM_64 64
#define DEFAULT_MARGIN 10
#define SIZE_10 10
#define SIZE_30 30
#define SIZE_50 50
#define SIZE_100 100
#define SIZE_150 150
#define SIZE_180 180
#define SIZE_200 200
#define SIZE_250 250
#define SIZE_300 300
#define SIZE_350 350
#define SIZE_400 400
#define SIZE_500 500
#define SIZE_600 600
#define DEFAULT_VALUE_TAG 7000
#define ENUM_ABNORMAL_VALUE 500
#define INVALID_PARAM 401
#define COLOR_RED 0xFFFF0000
#define COLOR_GREEN 0xFF00FF00
#define COLOR_BLUE 0xFF0000FF
#define COLOR_YELLOW 0xFFFFFF00
#define COLOR_PURPLE 0xFFFF11FF
#define COLOR_GRAY 0xFFDDDDDD
#define COLOR_TRANSPARENT 0x00000000
#define COLOR_BLACK 0xFF000000
#define COLOR_WHITE 0xFFFFFFFF
#define COLOR_LIGHT_BLUE 0xFF00FFFF
#define ON_CLICK_EVENT_ID 6001
#define ON_FOCUS_EVENT_ID 6002
#define ON_TOUCH_EVENT_ID 6003
#define ON_AREA_CHANGE_EVENT_ID 6004
#define ON_APPEAR_EVENT_ID 6005
#define ON_BLUR_EVENT_ID 6006
#define ON_CHANGE_EVENT_ID 6007
#define ON_SUBMIT_EVENT_ID 6008
#define ON_CUT_EVENT_ID 6009
#define ON_PASTE_EVENT_ID 6010
#define ON_MEASURE_EVENT_ID 6011
#define ON_LAYOUT_EVENT_ID 6012
#define ON_DRAW_EVENT_ID 6013
#define PARAM_NEGATIVE_1 (-1)
#define PARAM_NEGATIVE_100 (-100)

/**
 * Log print domain.
 */
const unsigned int LOG_PRINT_DOMAIN = 0xFF00;
} // namespace ArkUIDatePickerCApiDemo
#endif // ARKUI_CAPI_DEMO_COMMON_TEST_H