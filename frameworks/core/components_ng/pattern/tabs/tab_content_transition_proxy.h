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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TAB_CONTENT_TRANSITION_PROXY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TAB_CONTENT_TRANSITION_PROXY_H

#include <functional>
#include <memory>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/memory/type_info_base.h"

namespace OHOS::Ace {

class TabContentTransitionProxy : public AceType {
    DECLARE_ACE_TYPE(TabContentTransitionProxy, AceType);

public:
    int32_t GetFromIndex() const
    {
        return fromIndex_;
    }
    void SetFromIndex(int32_t fromIndex)
    {
        fromIndex_ = fromIndex;
    }

    int32_t GetToIndex() const
    {
        return toIndex_;
    }

    void SetToIndex(int32_t toIndex)
    {
        toIndex_ = toIndex;
    }

    bool GetHasFinished() const
    {
        return hasFinished_;
    }

    void SetHasFinished(bool hasFinished)
    {
        hasFinished_ = hasFinished;
    }

    bool GetHasOnChanged() const
    {
        return hasOnChanged_;
    }

    void SetHasOnChanged(bool hasOnChanged)
    {
        hasOnChanged_ = hasOnChanged;
    }

    void FinishTransition()
    {
        if (finishTransitionEvent_ && !hasFinished_) {
            hasFinished_ = true;
            auto event = *finishTransitionEvent_;
            event(hasOnChanged_);
        }
    }

    void SetFinishTransitionEvent(std::function<void(bool)>&& event)
    {
        if (!finishTransitionEvent_) {
            finishTransitionEvent_ = std::make_shared<std::function<void(bool)>>(event);
        } else {
            (*finishTransitionEvent_).swap(event);
        }
    }

private:
    int32_t fromIndex_;
    int32_t toIndex_;
    bool hasFinished_ = false;
    bool hasOnChanged_ = false;
    std::shared_ptr<std::function<void(bool)>> finishTransitionEvent_;
};

using TransitionFunc = std::function<void(const RefPtr<TabContentTransitionProxy>&)>;
struct TabContentAnimatedTransition {
    int32_t timeout = 0;
    TransitionFunc transition;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TAB_CONTENT_TRANSITION_PROXY_H