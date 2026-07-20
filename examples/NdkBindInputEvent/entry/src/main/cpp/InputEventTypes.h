/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
// [Start Cpp_InputEventTypes]
// InputEventTypes.h
// 输入事件相关的类型定义和辅助函数

#ifndef MYAPPLICATION_INPUTEVENTTYPES_H
#define MYAPPLICATION_INPUTEVENTTYPES_H

#include <cstdint>

namespace NativeModule {

// 基础事件信息结构体
struct BaseEventInfo {
    int32_t action;
    int64_t eventTime;
    int32_t sourceType;
    int32_t type;
};

// 指针坐标信息结构体
struct PointerPosition {
    float x;
    float y;
    float displayX;
    float displayY;
    float windowX;
    float windowY;
};

// 按键信息结构体
struct KeyInfo {
    int32_t pressedKey;
    uint64_t modifierKeys;
};

} // namespace NativeModule

#endif // MYAPPLICATION_INPUTEVENTTYPES_H
// [End Cpp_InputEventTypes]
