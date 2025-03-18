/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_FOCUS_STATE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_FOCUS_STATE_H

#include <string>
#include <map>
#include <variant>
#include "base/memory/ace_type.h"

namespace OHOS::Ace::NG {
class FocusHub;
class FrameNode;
class EventHub;
class GeometryNode;

enum class FocusType : int32_t {
    DISABLE = 0,
    NODE = 1,
    SCOPE = 2,
};

class FocusState : public virtual AceType {
    DECLARE_ACE_TYPE(FocusState, AceType)

public:
    FocusState() = default;
    explicit FocusState(const WeakPtr<EventHub>& eventHub, FocusType type = FocusType::DISABLE)
        : eventHub_(eventHub), focusType_(type)
    {}
    explicit FocusState(const WeakPtr<FrameNode>& frameNode, FocusType type = FocusType::DISABLE)
        : frameNode_(frameNode), focusType_(type)
    {}
    virtual ~FocusState() = default;

    void SetLastWeakFocusNode(const WeakPtr<FocusHub>& focusHub)
    {
        lastWeakFocusNode_ = focusHub;
    }
    WeakPtr<FocusHub> GetLastWeakFocusNode() const
    {
        return lastWeakFocusNode_;
    }
    bool IsCurrentFocus() const
    {
        return currentFocus_;
    }
    void SetCurrentFocus(bool currentFocus)
    {
        currentFocus_ = currentFocus;
    }
    void SetTabStop(bool tabStop)
    {
        tabStop_ = tabStop;
    }
    bool IsTabStop() const
    {
        return tabStop_;
    }
    void ResetNextFocus()
    {
        nextStep_.clear();
    }
    std::variant<WeakPtr<AceType>, std::string> GetNextFocus(int32_t key) const
    {
        auto it = nextStep_.find(key);
        if (it != nextStep_.end()) {
            return it->second;
        } else {
            return std::string("");
        }
    }
    void SetNextFocus(int32_t key, const std::variant<WeakPtr<AceType>, std::string>& nextFocus)
    {
        nextStep_[key] = nextFocus;
    }
    RefPtr<FrameNode> GetFrameNode() const;
    std::string GetFrameName() const;
    int32_t GetFrameId() const;
    RefPtr<GeometryNode> GetGeometryNode() const;

    bool currentFocus_ { false };
    WeakPtr<EventHub> eventHub_;
    WeakPtr<FrameNode> frameNode_;
    FocusType focusType_ = FocusType::DISABLE;
    WeakPtr<FocusHub> lastWeakFocusNode_ { nullptr };
    bool tabStop_ { false };
    std::map<int32_t, std::variant<WeakPtr<AceType>, std::string>> nextStep_;
};
} // namespace OHOS::Ace::NG

#endif