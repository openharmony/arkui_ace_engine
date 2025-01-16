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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_SWIPER_CONTENT_TRANSITION_PROXY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_SWIPER_CONTENT_TRANSITION_PROXY_H

#include <cstdint>
#include <functional>
#include <memory>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/memory/type_info_base.h"

namespace OHOS::Ace {

class SwiperContentTransitionProxy : public AceType {
    DECLARE_ACE_TYPE(SwiperContentTransitionProxy, AceType);

public:
    int32_t GetSelectedIndex() const
    {
        return selectedIndex_;
    }

    void SetSelectedIndex(int32_t selectedIndex)
    {
        selectedIndex_ = selectedIndex;
    }

    int32_t GetIndex() const
    {
        return index_;
    }

    void SetIndex(int32_t index)
    {
        index_ = index;
    }

    float GetPosition() const
    {
        return position_;
    }

    void SetPosition(float position)
    {
        position_ = position;
    }

    float GetMainAxisLength() const
    {
        return mainAxisLength_;
    }

    void SetMainAxisLength(float mainAxisLength)
    {
        mainAxisLength_ = mainAxisLength;
    }

    void FinishTransition()
    {
        if (finishTransitionEvent_) {
            auto event = *finishTransitionEvent_;
            event();
        }
    }

    void SetFinishTransitionEvent(std::function<void()>&& event)
    {
        if (!finishTransitionEvent_) {
            finishTransitionEvent_ = std::make_shared<std::function<void()>>(event);
        } else {
            (*finishTransitionEvent_).swap(event);
        }
    }

private:
    int32_t selectedIndex_ = 0;
    int32_t index_ = 0;
    float position_ = 0.0f;
    float mainAxisLength_ = 0.0f;
    std::shared_ptr<std::function<void()>> finishTransitionEvent_;
};

struct SwiperContentAnimatedTransition {
    int32_t timeout = 0;
    std::function<void(const RefPtr<SwiperContentTransitionProxy>&)> transition;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_SWIPER_CONTENT_TRANSITION_PROXY_H