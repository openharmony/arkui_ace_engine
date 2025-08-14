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

#include "core/components_ng/pattern/swiper_indicator/indicator_common/indicator_controller.h"

#include "core/components_ng/pattern/swiper_indicator/indicator_common/indicator_pattern.h"

namespace OHOS::Ace::NG {
void IndicatorController::ShowPrevious() const
{
    if (indicatorPattern_.Upgrade()) {
        indicatorPattern_.Upgrade()->ShowPrevious();
    }
}

void IndicatorController::ShowNext() const
{
    if (indicatorPattern_.Upgrade()) {
        indicatorPattern_.Upgrade()->ShowNext();
    }
}

void IndicatorController::ChangeIndex(int32_t index, bool useAnimation) const
{
    if (indicatorPattern_.Upgrade()) {
        indicatorPattern_.Upgrade()->ChangeIndex(index, useAnimation);
    }
}

void IndicatorController::ResetJSIndicatorController()
{
    if (resetFunc_) {
        resetFunc_();
        resetFunc_ = nullptr;
    }
}

void IndicatorController::SetJSIndicatorController(std::function<void()> resetFunc)
{
    resetFunc_ = resetFunc;
}

void IndicatorController::SetIndicatorPattern(const RefPtr<IndicatorPattern>& indicatorPattern)
{
    indicatorPattern_ = indicatorPattern;
}

void IndicatorController::SetSwiperNode(const RefPtr<FrameNode>& swiperNode)
{
    swiperNode_ = swiperNode;
    if (indicatorPattern_.Upgrade() && swiperNode) {
        auto indicatorNode = indicatorPattern_.Upgrade()->GetHost();
        CHECK_NULL_VOID(indicatorNode);
        auto pattern = swiperNode->GetPattern<SwiperPattern>();
        CHECK_NULL_VOID(pattern);
        auto lastIndicatorNode = pattern->GetIndicatorNode();
        pattern->SetIndicatorNode(indicatorNode);
        if (lastIndicatorNode && lastIndicatorNode != indicatorNode) {
            auto lastIndicatorPattern = lastIndicatorNode->GetPattern<IndicatorPattern>();
            CHECK_NULL_VOID(lastIndicatorPattern);
            lastIndicatorPattern->ResetSwiperNode();
        }
    }
}

const WeakPtr<FrameNode>& IndicatorController::GetSwiperNode() const
{
    return swiperNode_;
}

void IndicatorController::ResetIndicatorControllor(
    const RefPtr<IndicatorController>& controller, const RefPtr<FrameNode>& indicatorNode)
{
    CHECK_NULL_VOID(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<IndicatorPattern>();
    CHECK_NULL_VOID(indicatorPattern);
    auto lastSwiperNode = indicatorPattern->GetBindSwiperNode();
    controller->SetSwiperNode(lastSwiperNode);
    indicatorPattern->ResetJSIndicatorController();
}

void IndicatorController::UpdateIndicatorNode()
{
    auto indicatorPattern = indicatorPattern_.Upgrade();
    CHECK_NULL_VOID(indicatorPattern);
    auto dotIndicatorModifier = indicatorPattern->GetDotIndicatorModifier();
    if (dotIndicatorModifier) {
        dotIndicatorModifier->StopAnimation();
    }
    auto indicatorNode = indicatorPattern->GetHost();
    CHECK_NULL_VOID(indicatorNode);
    indicatorNode->MarkDirtyNode(NG::PROPERTY_UPDATE_MEASURE);
}

RefPtr<FrameNode> IndicatorController::GetIndicatorNode()
{
    auto indicatorPattern = indicatorPattern_.Upgrade();
    CHECK_NULL_RETURN(indicatorPattern, nullptr);
    return indicatorPattern->GetHost();
}
} // namespace OHOS::Ace::NG
