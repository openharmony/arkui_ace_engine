/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLL_SCROLL_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLL_SCROLL_PAINT_PROPERTY_H

#include <algorithm>
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/scroll/scroll_bar_theme.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/paint_property.h"
#include "core/components_ng/pattern/scroll/inner/scroll_bar.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

class ScrollPaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(ScrollPaintProperty, PaintProperty)

public:
    ScrollPaintProperty()
    {
        InitScrollBar();
    }
    ~ScrollPaintProperty() override = default;

    RefPtr<PaintProperty> Clone() const override
    {
        auto paintProperty = MakeRefPtr<ScrollPaintProperty>();
        paintProperty->UpdatePaintProperty(this);
        paintProperty->currentOffset_ = currentOffset_;
        paintProperty->scrollBar_ = scrollBar_;
        paintProperty->viewPortExtent_ = viewPortExtent_;
        paintProperty->propAxis_ = CloneAxis();
        return paintProperty;
    }

    void InitScrollBar()
    {
        if (scrollBar_ == nullptr) {
            auto pipelineContext = PipelineContext::GetCurrentContext();
            auto theme = pipelineContext->GetTheme<ScrollBarTheme>();
            scrollBar_ = AceType::MakeRefPtr<ScrollBar>(DisplayMode::AUTO);
            scrollBar_->SetInactiveWidth(theme->GetNormalWidth());
            scrollBar_->SetNormalWidth(theme->GetNormalWidth());
            scrollBar_->SetActiveWidth(theme->GetActiveWidth());
            scrollBar_->SetTouchWidth(theme->GetTouchWidth());
            scrollBar_->SetReservedHeight(theme->GetReservedHeight());
            scrollBar_->SetMinHeight(theme->GetMinHeight());
            scrollBar_->SetMinDynamicHeight(theme->GetMinDynamicHeight());
            scrollBar_->SetBackgroundColor(theme->GetBackgroundColor());
            scrollBar_->SetForegroundColor(theme->GetForegroundColor());
            scrollBar_->SetPadding(theme->GetPadding());
            scrollBar_->SetScrollable(true);
        }
    }

    RefPtr<ScrollBar> GetScrollBar()
    {
        if (scrollBar_ == nullptr) {
            InitScrollBar();
        }
        return scrollBar_;
    }

    void Reset() override
    {
        PaintProperty::Reset();
        if (scrollBar_) {
            scrollBar_.Reset();
        }
        ResetAxis();
    }

    void SetScrollBarWidth(const Dimension& width)
    {
        if (!scrollBar_) {
            return;
        }
        scrollBar_->SetInactiveWidth(width);
        scrollBar_->SetNormalWidth(width);
        scrollBar_->SetActiveWidth(width);
        scrollBar_->SetTouchWidth(width);
    }

    void SetScrollBarColor(const Color& color)
    {
        if (!scrollBar_) {
            return;
        }
        scrollBar_->SetForegroundColor(color);
    }

    void SetDisplayMode(DisplayMode displayMode)
    {
        if (!scrollBar_) {
            return;
        }
        scrollBar_->SetDisplayMode(displayMode);
    }

    void UpdateScrollBarOffset(float currentOffset, const SizeF& viewPortExtent)
    {
        currentOffset_ = currentOffset;
        viewPortExtent_ = viewPortExtent;
    }

    void UpdateScrollBarRegion(const SizeF& frameSize)
    {
        if (scrollBar_ == nullptr) {
            return;
        }

        Size size(frameSize.Width(), frameSize.Height());
        Offset scrollOffset =
            (propAxis_ == Axis::HORIZONTAL) ? Offset(0.0 - currentOffset_, 0.0) : Offset(0.0, 0.0 - currentOffset_);
        double estimatedHeight = (propAxis_ == Axis::HORIZONTAL) ? viewPortExtent_.Width() : viewPortExtent_.Height();
        scrollBar_->UpdateScrollBarRegion(Offset(), size, scrollOffset, estimatedHeight);
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Axis, Axis, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ScrollOffset, float, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ScrollViewPortExtent, SizeF, PROPERTY_UPDATE_RENDER);

private:
    float currentOffset_ = 0.0f;
    SizeF viewPortExtent_;
    RefPtr<ScrollBar> scrollBar_;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLL_SCROLL_PAINT_PROPERTY_H
