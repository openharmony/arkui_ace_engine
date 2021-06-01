/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BOX_RENDER_BOX_BASE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BOX_RENDER_BOX_BASE_H

#include "base/geometry/size.h"
#include "core/animation/property_animatable.h"
#include "core/components/box/box_base_component.h"
#include "core/components/common/layout/grid_column_info.h"
#include "core/components/common/properties/edge.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace {

class RenderBoxBase : public RenderNode, public PropertyAnimatable {
    DECLARE_ACE_TYPE(RenderBoxBase, RenderNode, PropertyAnimatable);

public:
    using LayoutCallback = std::function<void()>;

    void Update(const RefPtr<Component>& component) override;
    void PerformLayout() override;
    void Dump() override;

    Offset GetPaintPosition() const;
    const Size& GetPaintSize() const;
    void SetPaintSize(const Size& paintSize);
    virtual Size GetBorderSize() const;
    double CalculateHeightPercent(double percent) const; // add for text filed

    FloatPropertyAnimatable::SetterMap GetFloatPropertySetterMap() override;
    FloatPropertyAnimatable::GetterMap GetFloatPropertyGetterMap() override;

    virtual const Color& GetColor() const
    {
        return Color::TRANSPARENT;
    }

    double GetWidth() const // add for animation
    {
        return width_.Value();
    }

    double GetHeight() const // add for animation
    {
        return height_.Value();
    }

    void SetWidth(double width) // add for animation
    {
        if (GreatOrEqual(width, 0.0) && !NearEqual(width_.Value(), width)) {
            width_.SetValue(width);
            MarkNeedLayout();
        }
    }

    void SetHeight(double height) // add for animation
    {
        if (GreatOrEqual(height, 0.0) && !NearEqual(height_.Value(), height)) {
            height_.SetValue(height);
            MarkNeedLayout();
        }
    }

    EdgePx GetMargin() const
    {
        return margin_;
    }

    Size GetMarginSize() const
    {
        return margin_.GetLayoutSize();
    }

    Size GetPaddingSize() const
    {
        return padding_.GetLayoutSize();
    }

    void SetLayoutCallback(LayoutCallback&& layoutCallback)
    {
        layoutCallback_ = layoutCallback;
    }

    const Rect& GetTouchArea() const
    {
        return touchArea_;
    }

    void SetConstraints(const LayoutParam& constraints)
    {
        constraints_ = constraints;
        MarkNeedLayout();
    }

    void SetBoxFlex(BoxFlex flex)
    {
        flex_ = flex;
    }

protected:
    virtual void ClearRenderObject() override;
    virtual Offset GetBorderOffset() const;

    EdgePx ConvertEdgeToPx(const Edge& edge, bool additional);
    double ConvertMarginToPx(Dimension dimension, bool vertical, bool additional) const;
    double ConvertDimensionToPx(Dimension dimension, bool vertical, bool defaultZero = false) const;
    double ConvertHorizontalDimensionToPx(Dimension dimension, bool defaultZero = false) const;
    double ConvertVerticalDimensionToPx(Dimension dimension, bool defaultZero = false) const;
    void CalculateWidth();
    void CalculateHeight();
    void ConvertMarginPaddingToPx();
    void ConvertConstraintsToPx();
    void CalculateGridLayoutSize();
    void CalculateSelfLayoutParam();
    void SetChildLayoutParam();
    void ConvertPaddingForLayoutInBox();
    void CalculateSelfLayoutSize();
    void CalculateChildPosition();
    void AdjustSizeByAspectRatio();
    void PerformLayoutInLiteMode();

    Dimension width_ = Dimension(-1.0, DimensionUnit::PX);  // exclude margin
    Dimension height_ = Dimension(-1.0, DimensionUnit::PX); // exclude margin
    BoxFlex flex_ = BoxFlex::FLEX_NO;
    LayoutParam constraints_ = LayoutParam(Size(), Size()); // exclude margin
    EdgePx padding_;
    EdgePx margin_;
    Alignment align_;
    Size paintSize_; // exclude margin
    Rect touchArea_; // exclude margin
    bool deliverMinToChild_ = true;
    bool scrollPage_ = false;
    uint32_t percentFlag_ = 0;
    bool layoutInBox_ = false;
    Edge paddingOrigin_;
    LayoutCallback layoutCallback_;
    bool useLiteStyle_ = false;

private:
    bool IsSizeValid(const Dimension& value, double maxLimit);

    Edge marginOrigin_;
    Edge additionalMargin_;
    bool useFlexWidth_ = false;
    bool useFlexHeight_ = false;
    bool selfDefineWidth_ = false;
    bool selfDefineHeight_ = false;
    double selfMaxWidth_ = Size::INFINITE_SIZE;  // exclude margin
    double selfMinWidth_ = 0.0;                  // exclude margin
    double selfMaxHeight_ = Size::INFINITE_SIZE; // exclude margin
    double selfMinHeight_ = 0.0;                 // exclude margin
    double aspectRatio_ = 0.0;
    Dimension minWidth_ = Dimension();
    Dimension minHeight_ = Dimension();
    Dimension maxWidth_ = Dimension();
    Dimension maxHeight_ = Dimension();

    // result for layout
    LayoutParam selfLayoutParam_; // include margin
    Size selfLayoutSize_;         // include margin
    LayoutParam childLayoutParam_;
    Size childSize_;
    Offset childPosition_;

    // grid layout
    RefPtr<GridColumnInfo> gridColumnInfo_;
    RefPtr<GridContainerInfo> gridContainerInfo_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BOX_RENDER_BOX_BASE_H
