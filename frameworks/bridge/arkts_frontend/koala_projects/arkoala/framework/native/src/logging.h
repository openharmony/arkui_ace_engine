/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#pragma once

#include <cassert>

#define ASSERT_VERBOSE

#ifdef ASSERT_VERBOSE
#define ASSERT0(expression, msg) (void)( \
            (!!(expression)) || \
            (ARKOALA_LOG0(msg), assert(expression), 0) \
        )
#define ASSERT(expression, msg, ...) (void)( \
            (!!(expression)) || \
            (ARKOALA_LOG(msg, __VA_ARGS__), assert(expression), 0) \
        )
#else
#define ASSERT0(expression, msg) assert(expression)
#define ASSERT(expression, msg, ...) assert(expression)
#endif

#ifdef KOALA_OHOS
#include <hilog/log.h>
#define ARKOALA_LOG0(msg) OH_LOG_Print(LOG_APP, LOG_INFO, 0xFF00, "Arkoala", msg)
#define ARKOALA_LOG(msg, ...) OH_LOG_Print(LOG_APP, LOG_INFO, 0xFF00, "Arkoala", msg, __VA_ARGS__)
// Also do
//  hdc shell hilog -p off
//  hdc shell hilog -Q pidoff
// to see the output.
#else
#include <stdio.h>
#define ARKOALA_LOG0(msg) fprintf(stderr, "Arkoala: %s", msg)
#define ARKOALA_LOG(msg, ...) fprintf(stderr, "Arkoala: " msg, __VA_ARGS__)
#endif