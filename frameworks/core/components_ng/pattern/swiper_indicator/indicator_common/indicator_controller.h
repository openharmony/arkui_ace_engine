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

namespace OHOS::Ace::Framework {
class JSIndicatorController;
}
namespace OHOS::Ace::NG {
class IndicatorPattern;
class IndicatorController : public virtual AceType {
    DECLARE_ACE_TYPE(IndicatorController, AceType);

public:
    void ShowPrevious() const;

    void ShowNext() const;

    void ChangeIndex(int32_t index, bool useAnimation) const;

    void ResetJSIndicatorController();

    void SetJSIndicatorController(std::function<void()> resetFunc);

    void SetIndicatorPattern(const RefPtr<IndicatorPattern>& indicatorPattern);

    void SetSwiperNode(const RefPtr<FrameNode>& swiperNode);

    void SetSwiperNode(const RefPtr<FrameNode>& swiperNode, const RefPtr<FrameNode>& indicatorNode)
    {
        SetSwiperNode(swiperNode);
    }

    const WeakPtr<FrameNode>& GetSwiperNode() const;

    void ResetSwiperNode()
    {
        swiperNode_ = nullptr;
    }

    void ResetIndicatorControllor(
        const RefPtr<IndicatorController>& controller, const RefPtr<FrameNode>& indicatorNode);

    void UpdateIndicatorNode();

    RefPtr<FrameNode> GetIndicatorNode();

private:
    std::function<void()> resetFunc_;
    WeakPtr<IndicatorPattern> indicatorPattern_;
    WeakPtr<FrameNode> swiperNode_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SWIPER_SWIPER_CONTROLLER_H
