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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_INDICATOR_SWIPER_ARROW_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_INDICATOR_SWIPER_ARROW_PATTERN_H

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_arrow_layout_algorithm.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_arrow_layout_property.h"

namespace OHOS::Ace::NG {
class SwiperArrowPattern : public Pattern {
    DECLARE_ACE_TYPE(SwiperArrowPattern, Pattern);

public:
    SwiperArrowPattern() = default;
    ~SwiperArrowPattern() override = default;
    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<SwiperArrowLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<SwiperArrowLayoutAlgorithm>();
    }

    RefPtr<FrameNode> GetSwiperNode() const
    {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, nullptr);
        auto swiperNode = host->GetParent();
        CHECK_NULL_RETURN(swiperNode, nullptr);
        return DynamicCast<FrameNode>(swiperNode);
    }

    FocusPattern GetFocusPattern() const override
    {
        auto pipelineContext = PipelineBase::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, FocusPattern());
        auto swiperTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
        CHECK_NULL_RETURN(swiperTheme, FocusPattern());
        FocusPaintParam paintParam;
        paintParam.SetPaintColor(swiperTheme->GetFocusedColor());
        paintParam.SetPaintWidth(swiperTheme->GetFocusedBorderWidth());
        return { FocusType::NODE, true, FocusStyleType::INNER_BORDER, paintParam };
    }

    RefPtr<SwiperArrowLayoutProperty> GetSwiperArrowLayoutProperty() const
    {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, nullptr);
        auto swiperArrowLayoutProperty = host->GetLayoutProperty<SwiperArrowLayoutProperty>();
        CHECK_NULL_RETURN(swiperArrowLayoutProperty, nullptr);
        return swiperArrowLayoutProperty;
    }

    void ButtonOnHover(RefPtr<FrameNode> buttonNode, bool isHovered);
    void SetButtonVisible(bool visible);
    void DumpAdvanceInfo() override;
    void DumpAdvanceInfo(std::unique_ptr<JsonValue>& json) override;

private:
    std::tuple<bool, bool, bool> CheckHoverStatus();
    void OnModifyDone() override;
    void InitNavigationArrow();
    void InitSwiperChangeEvent(const RefPtr<SwiperEventHub>& swiperEventHub);
    void InitEvent();
    void UpdateButtonNode(int32_t index);
    void ButtonTouchEvent(RefPtr<FrameNode> buttonNode, TouchType touchType);
    void ButtonClickEvent();
    void UpdateArrowContent();
    void InitOnKeyEvent();
    bool OnKeyEvent(const KeyEvent& event);
    void OnClick() const;
    void InitAccessibilityText();
    int32_t TotalCount() const;
    RefPtr<SwiperPattern> GetSwiperPattern() const;

    RefPtr<ClickEvent> buttonClickListener_;
    RefPtr<TouchEventImpl> buttonTouchListener_;
    RefPtr<InputEvent> buttonOnHoverListener_;
    std::shared_ptr<ChangeEvent> swiperChangeEvent_;

    int32_t index_ = 0;
    bool isFirstCreate_ = true;
    Color hoverBeginColor_ = Color::TRANSPARENT;
    Color backgroundColor_ = Color::TRANSPARENT;
    bool isTouch_ = false;
    bool isHover_ = false;
    bool isVisible_ = false;
    bool hoverOnClickFlag_ = false;
    ACE_DISALLOW_COPY_AND_MOVE(SwiperArrowPattern);
    void UpdateArrowContentByImage(RefPtr<FrameNode>& buttonNode,
        RefPtr<SwiperArrowLayoutProperty>& swiperArrowLayoutProperty);
    void UpdateArrowContentBySymbol(RefPtr<FrameNode>& buttonNode,
        RefPtr<SwiperArrowLayoutProperty>& swiperArrowLayoutProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_INDICATOR_SWIPER_ARROW_PATTERN_H
