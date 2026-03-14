/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ARKUI_CAPI_XTS_COMMON_TEST_H
#define ARKUI_CAPI_XTS_COMMON_TEST_H

#include <napi/native_api.h>
#include <hilog/log.h>

namespace ArkUICapiTest {
#define PARAM_0 0
#define PARAM_1 1
#define PARAM_2 2
#define PARAM_4 4
#define PARAM_10 10
#define PARAM_15 15
#define PARAM_20 20
#define PARAM_32 32
#define PARAM_40 40
#define PARAM_100 100
#define PARAM_150 150
#define PARAM_200 200
#define PARAM_300 300
#define PARAM_350 350
#define PARAM_400 400
#define PARAM_500 500
#define PARAM_600 600
#define PARAM_800 800

#define PARAM_NEGATIVE_10 (-10)
#define PARAM_NEGATIVE_20 (-20)
#define PARAM_NEGATIVE_99 (-99)
#define DEFAULT_MARGIN 10

#define SUCCESS 0
#define INVALID_PARAM 401
#define NULL_PARAM 404

#define COLOR_RED 0xFFFF0000
#define COLOR_GREEN 0xFF00FF00
#define COLOR_BLUE 0xFF0000FF
#define COLOR_YELLOW 0xFFFFFF00
#define COLOR_GRAY 0xFFDDDDDD
#define COLOR_WHITE 0xFFFFFFFF
#define COLOR_PINK 0xFFFFC0CB
#define ON_CLICK_EVENT_ID 6001
#define ON_CLICK_EVENT_ID2 6015
#define ON_CLICK_EVENT_ID3 6016
#define ON_CLICK_EVENT_ID4 6017
#define ON_CLICK_EVENT_ID5 6018

#define ON_CLICK_EVENT_ID_2 1002

/**
 * Log print domain.
 */
const unsigned int LOG_PRINT_DOMAIN = 0xFF00;
} // namespace ArkUICapiTest
#endif // ARKUI_CAPI_XTS_COMMON_TEST_H
