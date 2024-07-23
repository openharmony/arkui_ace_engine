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

#include "swiper_helper.h"

#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_pattern.h"

namespace OHOS::Ace::NG {
void SwiperHelper::InitSwiperController(const RefPtr<SwiperController>& controller, const WeakPtr<SwiperPattern>& weak)
{
    controller->SetSwipeToImpl([weak](int32_t index, bool reverse) {
        auto swiper = weak.Upgrade();
        CHECK_NULL_VOID(swiper);
        swiper->SwipeTo(index);
    });

    controller->SetSwipeToWithoutAnimationImpl([weak](int32_t index) {
        auto swiper = weak.Upgrade();
        CHECK_NULL_VOID(swiper);
        swiper->SwipeToWithoutAnimation(index);
    });

    controller->SetShowNextImpl([weak]() {
        auto swiper = weak.Upgrade();
        CHECK_NULL_VOID(swiper);
        auto swiperNode = swiper->GetHost();
        CHECK_NULL_VOID(swiperNode);
        TAG_LOGI(AceLogTag::ACE_SWIPER, "Swiper ShowNext, id:%{public}d", swiperNode->GetId());
        swiper->ShowNext();
    });

    controller->SetShowPrevImpl([weak]() {
        auto swiper = weak.Upgrade();
        CHECK_NULL_VOID(swiper);
        auto swiperNode = swiper->GetHost();
        CHECK_NULL_VOID(swiperNode);
        TAG_LOGI(AceLogTag::ACE_SWIPER, "Swiper ShowPrevious, id:%{public}d", swiperNode->GetId());
        swiper->ShowPrevious();
    });

    controller->SetChangeIndexImpl([weak](int32_t index, bool useAnimation) {
        auto swiper = weak.Upgrade();
        CHECK_NULL_VOID(swiper);
        TAG_LOGI(AceLogTag::ACE_SWIPER, "Swiper ChangeIndex %{public}d, useAnimation:%{public}d", index, useAnimation);
        swiper->ChangeIndex(index, useAnimation);
    });

    controller->SetFinishImpl([weak]() {
        auto swiper = weak.Upgrade();
        CHECK_NULL_VOID(swiper);
        swiper->FinishAnimation();
    });

    controller->SetPreloadItemsImpl([weak](const std::set<int32_t>& indexSet) {
        auto swiper = weak.Upgrade();
        CHECK_NULL_VOID(swiper);
        swiper->PreloadItems(indexSet);
    });
}

void SwiperHelper::SaveDigitIndicatorProperty(const RefPtr<FrameNode>& indicatorNode, SwiperPattern& swiper)
{
    CHECK_NULL_VOID(indicatorNode);
    auto indicatorProps = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    CHECK_NULL_VOID(indicatorProps);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    const auto theme = pipeline->GetTheme<SwiperIndicatorTheme>();
    const auto digitalParams = swiper.GetSwiperDigitalParameters();
    CHECK_NULL_VOID(digitalParams);
    indicatorProps->ResetIndicatorLayoutStyle();
    if (digitalParams->dimLeft.has_value()) {
        indicatorProps->UpdateLeft(digitalParams->dimLeft.value());
    }
    if (digitalParams->dimTop.has_value()) {
        indicatorProps->UpdateTop(digitalParams->dimTop.value());
    }
    if (digitalParams->dimRight.has_value()) {
        indicatorProps->UpdateRight(digitalParams->dimRight.value());
    }
    if (digitalParams->dimBottom.has_value()) {
        indicatorProps->UpdateBottom(digitalParams->dimBottom.value());
    }
    indicatorProps->UpdateFontColor(digitalParams->fontColor.value_or(
        theme->GetDigitalIndicatorTextStyle().GetTextColor()));
    indicatorProps->UpdateSelectedFontColor(digitalParams->selectedFontColor.value_or(
        theme->GetDigitalIndicatorTextStyle().GetTextColor()));
    indicatorProps->UpdateFontSize(
        digitalParams->fontSize.value_or(theme->GetDigitalIndicatorTextStyle().GetFontSize()));
    indicatorProps->UpdateSelectedFontSize(digitalParams->selectedFontSize.value_or(
        theme->GetDigitalIndicatorTextStyle().GetFontSize()));
    indicatorProps->UpdateFontWeight(digitalParams->fontWeight.value_or(
        theme->GetDigitalIndicatorTextStyle().GetFontWeight()));
    indicatorProps->UpdateSelectedFontWeight(digitalParams->selectedFontWeight.value_or(
        theme->GetDigitalIndicatorTextStyle().GetFontWeight()));
    auto props = swiper.GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(props);
    props->UpdateLeft(digitalParams->dimLeft.value_or(0.0_vp));
    props->UpdateTop(digitalParams->dimTop.value_or(0.0_vp));
    props->UpdateRight(digitalParams->dimRight.value_or(0.0_vp));
    props->UpdateBottom(digitalParams->dimBottom.value_or(0.0_vp));
    swiper.SetDigitStartAndEndProperty(indicatorNode);
}

void SwiperHelper::SaveDotIndicatorProperty(const RefPtr<FrameNode>& indicatorNode, SwiperPattern& swiper)
{
    CHECK_NULL_VOID(indicatorNode);
    auto indicatorProps = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    CHECK_NULL_VOID(indicatorProps);
    const auto params = swiper.GetSwiperParameters();
    CHECK_NULL_VOID(params);
    indicatorProps->ResetIndicatorLayoutStyle();
    if (params->dimLeft.has_value()) {
        indicatorProps->UpdateLeft(params->dimLeft.value());
    }
    if (params->dimTop.has_value()) {
        indicatorProps->UpdateTop(params->dimTop.value());
    }
    if (params->dimRight.has_value()) {
        indicatorProps->UpdateRight(params->dimRight.value());
    }
    if (params->dimBottom.has_value()) {
        indicatorProps->UpdateBottom(params->dimBottom.value());
    }
    const bool isRtl = swiper.GetNonAutoLayoutDirection() == TextDirection::RTL;
    if (params->dimStart.has_value()) {
        auto dimValue = params->dimStart.value();
        isRtl ? indicatorProps->UpdateRight(dimValue) : indicatorProps->UpdateLeft(dimValue);
    } else if (params->dimEnd.has_value()) {
        auto dimValue = params->dimEnd.value();
        isRtl ? indicatorProps->UpdateLeft(dimValue) : indicatorProps->UpdateRight(dimValue);
    }

    swiper.UpdatePaintProperty(indicatorNode);
}
} // namespace OHOS::Ace::NG
