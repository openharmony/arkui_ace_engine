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

#ifndef OHOS_ACE_FRAMEWORK_CJ_GESTURE_NATIVE_H
#define OHOS_ACE_FRAMEWORK_CJ_GESTURE_NATIVE_H

#include <cstdint>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"
#include "ffi_remote_data.h"
#include "cj_animate_param_ffi.h"
#include "core/interfaces/native/node/node_api.h"

class NativeGesture : public OHOS::FFI::FFIData {
public:
    NativeGesture() : FFIData() {}

    void setArkUIGesture(ArkUIGesture* gesture)
    {
        gesture_ = gesture;
    }

    ArkUIGesture* getArkUIGesture()
    {
        return gesture_;
    }

private:
    ArkUIGesture* gesture_;
};

class NativeGestureGroup : public OHOS::FFI::FFIData {
public:
    NativeGestureGroup() : FFIData() {}

    void setArkUIGesture(ArkUIGesture* gesture)
    {
        gesture_ = gesture;
    }

    ArkUIGesture* getArkUIGesture()
    {
        return gesture_;
    }

private:
    ArkUIGesture* gesture_;
};

#endif // OHOS_ACE_FRAMEWORK_CJ_GESTURE_NATIVE_H