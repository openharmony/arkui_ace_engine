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
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/paint_property.h"
#include "core/components_ng/pattern/scroll/inner/scroll_bar.h"
#include "core/components_ng/pattern/scroll/scroll_edge_effect.h"

namespace OHOS::Ace::NG {

class ScrollPaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(ScrollPaintProperty, PaintProperty)

public:
    ScrollPaintProperty()
    {
        scrollBar_ = AceType::MakeRefPtr<ScrollBar>(DisplayMode::AUTO);
    }
    ~ScrollPaintProperty() override = default;

    RefPtr<PaintProperty> Clone() const override
    {
        auto paintProperty = MakeRefPtr<ScrollPaintProperty>();
        paintProperty->UpdatePaintProperty(this);
        paintProperty->currentOffset_ = currentOffset_;
        paintProperty->scrollBar_ = scrollBar_;
        paintProperty->scrollEdgeEffect_ = scrollEdgeEffect_;
        paintProperty->viewPortExtent_ = viewPortExtent_;
        paintProperty->propAxis_ = CloneAxis();
        return paintProperty;
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override
    {
        PaintProperty::ToJsonValue(json);
        std::unordered_map<DisplayMode, std::string> scrollBarMap = { { DisplayMode::OFF, "BarState.Off" },
            { DisplayMode::AUTO, "BarState.Auto" }, { DisplayMode::ON, "BarState.On" } };
        json->Put("scrollBar", scrollBar_ ? scrollBarMap[scrollBar_->GetDisplayMode()].c_str() : "");
        json->Put("scrollBarColor", scrollBar_ ? scrollBar_->GetForegroundColor().ColorToString().c_str() : "");
        json->Put("scrollBarWidth", scrollBar_ ? scrollBar_->GetActiveWidth().ToString().c_str() : "");
    }

    void SetScrollEdgeEffect(const RefPtr<ScrollEdgeEffect>& scrollEdgeEffect)
    {
        scrollEdgeEffect_ = scrollEdgeEffect;
    }

    RefPtr<ScrollEdgeEffect> GetScrollEdgeEffect() const
    {
        return scrollEdgeEffect_;
    }

    RefPtr<ScrollBar> GetScrollBar()
    {
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

    void SetScrollBarPositionMode(const Axis& axis)
    {
        if (!scrollBar_) {
            return;
        }
        scrollBar_->SetPositionMode(axis == Axis::HORIZONTAL ? PositionMode::BOTTOM : PositionMode::RIGHT);
    }

    bool NeedPaintScrollBar() const
    {
        return scrollBar_ && scrollBar_->NeedScrollBar();
    }

    void UpdateScrollBarOffset(float currentOffset, SizeF viewPort, SizeF viewPortExtent, bool isDriving)
    {
        if (scrollBar_ == nullptr) {
            return;
        }
        scrollBar_->SetDriving(isDriving);
        Size size(viewPort.Width(), viewPort.Height());
        Offset scrollOffset = { 0.0 - currentOffset, 0.0 - currentOffset }; // fit for w/h switched.
        auto estimatedHeight = (propAxis_ == Axis::HORIZONTAL) ? viewPortExtent.Width() : viewPortExtent.Height();
        scrollBar_->UpdateScrollBarRegion(Offset(), size, scrollOffset, estimatedHeight);
    }

    float CalculatePatternOffset(float currentOffset)
    {
        if (scrollBar_ == nullptr) {
            return currentOffset;
        }
        return scrollBar_->CalcPatternOffset(currentOffset);
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Axis, Axis, PROPERTY_UPDATE_MEASURE);

private:
    float currentOffset_ = 0.0f;
    SizeF viewPortExtent_;
    RefPtr<ScrollBar> scrollBar_;
    RefPtr<ScrollEdgeEffect> scrollEdgeEffect_;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLL_SCROLL_PAINT_PROPERTY_H
