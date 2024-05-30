/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef OHOS_ACE_FRAMEWORK_CJ_PAGE_TRANSITION_H
#define OHOS_ACE_FRAMEWORK_CJ_PAGE_TRANSITION_H

#include <cstdint>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"

extern "C" {
CJ_EXPORT void FfiPageTransitionEnterCreate(int type, int duration, char *curve, int delay);
CJ_EXPORT void FfiPageTransitionExitCreate(int type, int duration, char *curve, int delay);
CJ_EXPORT void FfiPageTransitionSlideEffect(int slideEffect);
CJ_EXPORT void FfiPageTransitionTranslate(double x, double y, double z);
CJ_EXPORT void FfiPageTransitionScalePointer(double x, double y, double z, double centerX, double centerY);
CJ_EXPORT void FfiPageTransitionSetOpacity(double value);
CJ_EXPORT void FfiPageTransitionOnEnter(void (*callback)(int type, double progress));
CJ_EXPORT void FfiPageTransitionOnExit(void (*callback)(int type, double progress));
}

#endif