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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_INDICATOR_CONTROLLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_INDICATOR_CONTROLLER_H

#include "core/components_ng/pattern/swiper/swiper_pattern.h"

namespace OHOS::Ace::NG {
using CommonFunc = std::function<void()>;
using ChangeIndexImpl = std::function<void(const int32_t, bool)>;

class IndicatorController : public virtual AceType {
    DECLARE_ACE_TYPE(IndicatorController, AceType);

public:
    void ShowPrevious() const
    {
        if (showPrevImpl_) {
            showPrevImpl_();
        }
    }

    void SetShowPrevImpl(const CommonFunc& showPrevImpl)
    {
        showPrevImpl_ = showPrevImpl;
    }

    void ShowNext() const
    {
        if (showNextImpl_) {
            showNextImpl_();
        }
    }

    void SetShowNextImpl(const CommonFunc& showNextImpl)
    {
        showNextImpl_ = showNextImpl;
    }

    void ChangeIndex(int32_t index, bool useAnimation)
    {
        if (changeIndexImpl_) {
            changeIndexImpl_(index, useAnimation);
        }
    }

    void SetChangeIndexImpl(const ChangeIndexImpl& changeIndexImpl)
    {
        changeIndexImpl_ = changeIndexImpl;
    }

    void SetSwiperNode(const WeakPtr<NG::UINode>& swiperNode, const WeakPtr<NG::UINode>& indicatorNode)
    {
        swiperNode_ = swiperNode;
        auto refUINode = swiperNode_.Upgrade();
        CHECK_NULL_VOID(refUINode);
        auto frameNode = DynamicCast<NG::FrameNode>(refUINode);
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<NG::SwiperPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetIndicatorNode(indicatorNode);
    }

    const WeakPtr<NG::UINode>& GetSwiperNode() const
    {
        return swiperNode_;
    }

    void ResetSwiperNode()
    {
        swiperNode_ = nullptr;
    }
private:
    CommonFunc showPrevImpl_;
    CommonFunc showNextImpl_;
    ChangeIndexImpl changeIndexImpl_;
    WeakPtr<NG::UINode> swiperNode_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SWIPER_SWIPER_CONTROLLER_H
