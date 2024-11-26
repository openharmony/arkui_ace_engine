/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef POINTER_EVENT_H
#define POINTER_EVENT_H

#include <array>
#include <list>
#include <memory>
#include <set>
#include <unordered_map>
#include <vector>

namespace OHOS {
namespace MMI {
class PointerEvent {
public:
    static constexpr int32_t POINTER_ACTION_UNKNOWN = 0;
    static constexpr int32_t POINTER_ACTION_CANCEL = 1;
    static constexpr int32_t POINTER_ACTION_DOWN = 2;
    static constexpr int32_t POINTER_ACTION_MOVE = 3;
    static constexpr int32_t POINTER_ACTION_UP = 4;
    static constexpr int32_t POINTER_ACTION_PULL_DOWN = 12;
    static constexpr int32_t POINTER_ACTION_PULL_MOVE = 13;
    static constexpr int32_t POINTER_ACTION_PULL_UP = 14;
    static constexpr int32_t POINTER_ACTION_PULL_IN_WINDOW = 15;
    static constexpr int32_t POINTER_ACTION_PULL_OUT_WINDOW = 16;
    static constexpr int32_t SOURCE_TYPE_UNKNOWN = 0;
    static constexpr int32_t SOURCE_TYPE_TOUCHSCREEN = 2;
    static constexpr int32_t SOURCE_TYPE_TOUCHPAD = 3;
public:
    class PointerItem {
    public:
        PointerItem();
        ~PointerItem();
    public:
        void SetPointerId(int32_t pointerId);
        void SetDisplayX(int32_t displayX);
        int32_t GetDisplayY() const;
        void SetDisplayY(int32_t displayY);
        void SetWindowX(int32_t x);
        void SetWindowXPos(double x);
        void SetWindowY(int32_t y);
        void SetWindowYPos(double y);
    };
public:
    PointerEvent(const PointerEvent& other);
    virtual ~PointerEvent();
    static std::shared_ptr<PointerEvent> Create();
    void SetPointerAction(int32_t pointerAction);
    void SetPointerId(int32_t pointerId);
    void AddPointerItem(PointerItem &pointerItem);
    void SetSourceType(int32_t sourceType);
};
} // namespace MMI
} // namespace OHOS
#endif // POINTER_EVENT_H
