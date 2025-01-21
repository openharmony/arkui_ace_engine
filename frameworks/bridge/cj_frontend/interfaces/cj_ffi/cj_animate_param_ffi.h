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
#ifndef OHOS_ACE_FRAMEWORK_CJ_ANIMATE_PARAM_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_ANIMATE_PARAM_FFI_H

#include <cinttypes>
#include <optional>
#include <string>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "core/components/common/properties/animation_option.h"

extern "C" {
struct NativeAnimateParam {
    NativeOptionInt32 duration;
    NativeOptionFloat32 tempo;
    NativeOptionCString curve;
    NativeOptionInt32 delay;
    NativeOptionInt32 iterations;
    NativeOptionInt32 playMode;
    NativeOptionCallBack onFinish;
    NativeOptionInt32 finishCallbackType;
    NativeOptionInt32 min;
    NativeOptionInt32 max;
    NativeOptionInt32 expected;
};

struct NativeOptionAnimateParam {
    bool hasValue;
    NativeAnimateParam value;
};

namespace OHOS::Ace::Framework {
void ParseCjAnimation(NativeAnimateParam animationValue, AnimationOption& result);
}
}

#endif // OHOS_ACE_FRAMEWORK_CJ_ANIMATE_PARAM_H