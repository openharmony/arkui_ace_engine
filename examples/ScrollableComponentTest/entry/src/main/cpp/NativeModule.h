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

// 提供获取ArkUI在Native侧模块的封装接口

#ifndef SCROLLABLE_COMPONENT_NATIVEMODULE_H
#define SCROLLABLE_COMPONENT_NATIVEMODULE_H

#include "napi/native_api.h"
#include <arkui/native_interface.h>
#include <arkui/native_node.h>
#include <cassert>

namespace NativeModule {

class NativeModuleInstance {
public:
    static NativeModuleInstance *GetInstance()
    {
        static NativeModuleInstance instance;
        return &instance;
    }

    NativeModuleInstance()
    {
        // 获取C API接口的函数指针结构体对象，用于后续操作。
        OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, arkUINativeNodeApi_);
    }
    // 暴露给其他模块使用。
    ArkUI_NativeNodeAPI_1 *GetNativeNodeAPI() { return arkUINativeNodeApi_; }

private:
    ArkUI_NativeNodeAPI_1 *arkUINativeNodeApi_ = nullptr;
};

} // namespace NativeModule

#endif // SCROLLABLE_COMPONENT_NATIVEMODULE_H