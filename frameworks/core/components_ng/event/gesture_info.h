/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_GESTURE_INFO_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_GESTURE_INFO_H

#include <set>
#include <optional>

#include "base/memory/ace_type.h"
#include "core/components/common/layout/constants.h"
#include "core/gestures/gesture_info.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT GestureInfo : public virtual AceType {
    DECLARE_ACE_TYPE(GestureInfo, AceType);

public:
    GestureInfo() = default;
    GestureInfo(std::string tag, GestureTypeName type, bool isSystemGesture)
        : tag_(std::move(tag)), type_(type), isSystemGesture_(isSystemGesture)
    {}
    GestureInfo(GestureTypeName type, bool isSystemGesture) : type_(type), isSystemGesture_(isSystemGesture) {}
    GestureInfo(GestureTypeName type, GestureTypeName trueType, bool isSystemGesture)
        : type_(type), recognizerType_(trueType), isSystemGesture_(isSystemGesture)
    {}
    explicit GestureInfo(std::string tag) : tag_(std::move(tag)) {}
    explicit GestureInfo(std::set<SourceTool> allowedTypes) : allowedTypes_(std::move(allowedTypes)) {}
    explicit GestureInfo(GestureTypeName type) : type_(type) {}
    explicit GestureInfo(bool isSystemGesture) : isSystemGesture_(isSystemGesture) {}
    ~GestureInfo() override
    {
        if (isCapi_) {
            return;
        }
        if (disposeNotifyFunc_) {
            disposeNotifyFunc_(userData_);
        }
        if (disposeJSRecognizerInfoFunc_) {
            disposeJSRecognizerInfoFunc_();
        }
    }

    std::optional<std::string> GetTag() const
    {
        return tag_;
    }

    const std::set<SourceTool>& GetAllowedTypes() const
    {
        return allowedTypes_;
    }

    GestureTypeName GetType() const
    {
        return type_;
    }

    InputEventType GetInputEventType() const
    {
        return inputEventType_;
    }

    bool IsSystemGesture() const
    {
        return isSystemGesture_;
    }

    void SetTag(std::string tag)
    {
        tag_ = std::move(tag);
    }

    void SetAllowedTypes(std::set<SourceTool> allowedTypes)
    {
        allowedTypes_ = std::move(allowedTypes);
    }

    void SetType(GestureTypeName type)
    {
        type_ = type;
    }

    void SetRecognizerType(GestureTypeName trueType)
    {
        recognizerType_ = trueType;
    }

    GestureTypeName GetRecognizerType() const
    {
        return recognizerType_;
    }

    void SetInputEventType(InputEventType type)
    {
        inputEventType_ = type;
    }

    void SetIsSystemGesture(bool isSystemGesture)
    {
        isSystemGesture_ = isSystemGesture;
    }

    void SetUserData(void* userData)
    {
        userData_ = userData;
    }

    void* GetUserData()
    {
        return userData_;
    }

    void SetDisposeTag(bool tag)
    {
        disposeTag_ = tag;
    }

    bool GetDisposeTag()
    {
        return disposeTag_;
    }

    void SetIsCapi(bool isCapi)
    {
        isCapi_ = isCapi;
    }

    bool IsCapi() const
    {
        return isCapi_;
    }

    void SetDisposeNotifyFunc(std::function<void(void*)>&& func)
    {
        disposeNotifyFunc_ = std::move(func);
    }

    void SetDisposeJSRecognizerInfoFunc(std::function<void()>&& func)
    {
        disposeJSRecognizerInfoFunc_ = std::move(func);
    }

private:
    std::optional<std::string> tag_;
    std::set<SourceTool> allowedTypes_{};
    GestureTypeName type_ = GestureTypeName::UNKNOWN;
    // used in onGestureRecognizerJudgeBegin
    GestureTypeName recognizerType_ = GestureTypeName::UNKNOWN;
    InputEventType inputEventType_ = InputEventType::TOUCH_SCREEN;
    bool isSystemGesture_ = false;
    void* userData_ = nullptr;
    bool disposeTag_ = false;
    bool isCapi_ = true;
    std::function<void(void*)> disposeNotifyFunc_;
    std::function<void()> disposeJSRecognizerInfoFunc_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_GESTURE_INFO_H
