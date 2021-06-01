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

#include "core/components/box/render_box_base.h"

#include <algorithm>

#include "base/geometry/offset.h"
#include "base/log/dump_log.h"
#include "core/components/box/box_base_component.h"
#include "core/components/text_field/render_text_field.h"

namespace OHOS::Ace {
namespace {

const double CIRCLE_LAYOUT_IN_BOX_SCALE = sin(M_PI_4);
constexpr double BOX_DIAMETER_TO_RADIUS = 2.0;

class DimensionHelper {
public:
    using Getter = const Dimension& (Edge::*)() const;
    using Setter = void (Edge::*)(const Dimension&);

    DimensionHelper(Setter setter, Getter getter) : setter_(setter), getter_(getter) {}
    ~DimensionHelper() = default;

    const Dimension& Get(const Edge& edge) const
    {
        return std::bind(getter_, &edge)();
    }

    bool Set(double value, Edge* edge) const
    {
        if (LessNotEqual(value, 0.0)) {
            return false;
        }
        Dimension dimension = Get(*edge);
        if (NearEqual(dimension.Value(), value)) {
            return false;
        }
        dimension.SetValue(value);
        std::bind(setter_, edge, dimension)();
        return true;
    }

private:
    Setter setter_ = nullptr;
    Getter getter_ = nullptr;
};

}

Size RenderBoxBase::GetBorderSize() const
{
    return Size(0.0, 0.0);
}

Offset RenderBoxBase::GetBorderOffset() const
{
    return Offset(0.0, 0.0);
}

bool RenderBoxBase::IsSizeValid(const Dimension& value, double maxLimit)
{
    if (NearZero(value.Value())) {
        return false;
    }
    if ((value.Unit() == DimensionUnit::PERCENT) && (NearEqual(maxLimit, Size::INFINITE_SIZE))) {
        // When maxLimit is INFINITE, percent value is invalid, except PERCENT_FLAG_USE_VIEW_PORT is set.
        return percentFlag_ == PERCENT_FLAG_USE_VIEW_PORT;
    }
    return true;
}

double RenderBoxBase::CalculateHeightPercent(double percent) const
{
    return ConvertVerticalDimensionToPx(Dimension(percent, DimensionUnit::PERCENT));
}

double RenderBoxBase::ConvertMarginToPx(Dimension dimension, bool vertical, bool additional) const
{
    if (dimension.Unit() == DimensionUnit::PERCENT) {
        double parentLimit = 0.0;
        if (vertical) {
            parentLimit = GetLayoutParam().GetMaxSize().Height();
            if (NearEqual(parentLimit, Size::INFINITE_SIZE) && !NearEqual(selfMaxHeight_, Size::INFINITE_SIZE)) {
                parentLimit = selfMaxHeight_;
            }
        } else {
            parentLimit = GetLayoutParam().GetMaxSize().Width();
            if (NearEqual(parentLimit, Size::INFINITE_SIZE) && !NearEqual(selfMaxWidth_, Size::INFINITE_SIZE)) {
                parentLimit = selfMaxWidth_;
            }
        }
        if (NearEqual(parentLimit, Size::INFINITE_SIZE)) {
            if (additional || percentFlag_ != PERCENT_FLAG_USE_VIEW_PORT) {
                return 0.0; // Additional(from theme) set to 0.0 when INFINITE_SIZE.
            }
            parentLimit = vertical ? viewPort_.Height() : viewPort_.Width();
        }
        return parentLimit * dimension.Value();
    } else if (dimension.Unit() == DimensionUnit::PX) {
        return dimension.Value();
    } else {
        auto context = context_.Upgrade();
        if (!context) {
            return dimension.Value();
        }
        return context->NormalizeToPx(dimension);
    }
}

double RenderBoxBase::ConvertDimensionToPx(Dimension dimension, bool vertical, bool defaultZero) const
{
    if (dimension.Unit() == DimensionUnit::PERCENT) {
        double parentLimit = GetLayoutParam().GetMaxSize().Width();
        if (vertical) {
            parentLimit = GetLayoutParam().GetMaxSize().Height();
        }
        if (NearEqual(parentLimit, Size::INFINITE_SIZE)) {
            if (percentFlag_ != PERCENT_FLAG_USE_VIEW_PORT) {
                return defaultZero ? 0.0 : Size::INFINITE_SIZE;
            } else {
                parentLimit = vertical ? viewPort_.Height() : viewPort_.Width();
            }
        }
        return parentLimit * dimension.Value();
    } else if (dimension.Unit() == DimensionUnit::PX) {
        return dimension.Value();
    } else {
        auto context = context_.Upgrade();
        if (!context) {
            return dimension.Value();
        }
        return context->NormalizeToPx(dimension);
    }
}

double RenderBoxBase::ConvertHorizontalDimensionToPx(Dimension dimension, bool defaultZero) const
{
    return ConvertDimensionToPx(dimension, false, defaultZero);
}

double RenderBoxBase::ConvertVerticalDimensionToPx(Dimension dimension, bool defaultZero) const
{
    return ConvertDimensionToPx(dimension, true, defaultZero);
}

void RenderBoxBase::CalculateWidth()
{
    useFlexWidth_ = true;
    selfDefineWidth_ = false;
    selfMaxWidth_ = ConvertHorizontalDimensionToPx(width_, false);
    selfMinWidth_ = 0.0;
    if (GreatOrEqual(selfMaxWidth_, 0.0) && !NearEqual(selfMaxWidth_, Size::INFINITE_SIZE)) {
        selfMinWidth_ = 0.0;
        selfDefineWidth_ = true;
        useFlexWidth_ = false;
    } else if (constraints_.IsWidthValid()) {
        selfMaxWidth_ = constraints_.GetMaxSize().Width();
        selfMinWidth_ = constraints_.GetMinSize().Width();
        useFlexWidth_ = false;
    } else if (flex_ != BoxFlex::FLEX_X && flex_ != BoxFlex::FLEX_XY) {
        selfMaxWidth_ = Size::INFINITE_SIZE;
        useFlexWidth_ = false;
    } else {
        // No width, no constrain, no flex, use default min and max, reset selfMaxWidth_ here.
        selfMaxWidth_ = Size::INFINITE_SIZE;
    }
    if (!GetLayoutParam().HasUsedConstraints() && constraints_.IsWidthValid()) {
        selfMaxWidth_ = std::clamp(selfMaxWidth_, constraints_.GetMinSize().Width(), constraints_.GetMaxSize().Width());
        selfMinWidth_ = std::clamp(selfMinWidth_, constraints_.GetMinSize().Width(), constraints_.GetMaxSize().Width());
    }
}

void RenderBoxBase::CalculateHeight()
{
    useFlexHeight_ = true;
    selfDefineHeight_ = false;
    selfMaxHeight_ = ConvertVerticalDimensionToPx(height_, false);
    selfMinHeight_ = 0.0;
    if (GreatOrEqual(selfMaxHeight_, 0.0) && !NearEqual(selfMaxHeight_, Size::INFINITE_SIZE)) {
        selfMinHeight_ = 0.0;
        selfDefineHeight_ = true;
        useFlexHeight_ = false;
    } else if (constraints_.IsHeightValid()) {
        selfMaxHeight_ = constraints_.GetMaxSize().Height();
        selfMinHeight_ = constraints_.GetMinSize().Height();
        useFlexHeight_ = false;
    } else if (flex_ != BoxFlex::FLEX_Y && flex_ != BoxFlex::FLEX_XY) {
        selfMaxHeight_ = Size::INFINITE_SIZE;
        useFlexHeight_ = false;
    } else {
        // No height, no constrain, no flex, use default min and max, reset selfMaxHeight_ here.
        selfMaxHeight_ = Size::INFINITE_SIZE;
    }
    if (!GetLayoutParam().HasUsedConstraints() && constraints_.IsHeightValid()) {
        selfMaxHeight_ =
            std::clamp(selfMaxHeight_, constraints_.GetMinSize().Height(), constraints_.GetMaxSize().Height());
        selfMinHeight_ =
            std::clamp(selfMinHeight_, constraints_.GetMinSize().Height(), constraints_.GetMaxSize().Height());
    }
}

EdgePx RenderBoxBase::ConvertEdgeToPx(const Edge& edge, bool additional)
{
    EdgePx edgePx;
    edgePx.SetLeft(Dimension(ConvertMarginToPx(edge.Left(), false, additional)));
    edgePx.SetRight(Dimension(ConvertMarginToPx(edge.Right(), false, additional)));
    edgePx.SetTop(Dimension(ConvertMarginToPx(edge.Top(), true, additional)));
    edgePx.SetBottom(Dimension(ConvertMarginToPx(edge.Bottom(), true, additional)));
    return edgePx;
}

void RenderBoxBase::ConvertMarginPaddingToPx()
{
    padding_ = ConvertEdgeToPx(paddingOrigin_, false);
    margin_ = ConvertEdgeToPx(marginOrigin_, false) + ConvertEdgeToPx(additionalMargin_, true);
}

void RenderBoxBase::ConvertConstraintsToPx()
{
    // constraints is set from two ways, one is from BoxComponent::SetConstraints, the other is from DomNode.
    // BoxComponent::SetConstraints is higher priority than DOMNode.
    if (GetLayoutParam().HasUsedConstraints() || constraints_.IsWidthValid() || constraints_.IsHeightValid()) {
        return;
    }
    double minWidth = ConvertHorizontalDimensionToPx(minWidth_, true);
    double minHeight = ConvertVerticalDimensionToPx(minHeight_, true);
    double maxWidth = ConvertHorizontalDimensionToPx(maxWidth_, true);
    double maxHeight = ConvertVerticalDimensionToPx(maxHeight_, true);
    if (LessOrEqual(minWidth, 0.0) && LessOrEqual(minHeight, 0.0) && LessOrEqual(maxWidth, 0.0) &&
        LessOrEqual(maxHeight, 0.0)) {
        return;
    }
    if (GreatNotEqual(minWidth, 0.0) && NearZero(maxWidth)) {
        maxWidth = Size::INFINITE_SIZE;
    }
    if (GreatNotEqual(minHeight, 0.0) && NearZero(maxHeight)) {
        maxHeight = Size::INFINITE_SIZE;
    }
    if (LessNotEqual(maxWidth, minWidth)) {
        maxWidth = minWidth;
    }
    if (LessNotEqual(maxHeight, minHeight)) {
        maxHeight = minHeight;
    }
    if (GreatNotEqual(minWidth, 0.0) || GreatNotEqual(minHeight, 0.0)) {
        deliverMinToChild_ = true;
    }
    Size minSize = Size(minWidth, minHeight);
    Size maxSize = Size(maxWidth, maxHeight);
    constraints_ = LayoutParam(maxSize, minSize);
}

void RenderBoxBase::CalculateGridLayoutSize()
{
    if (gridColumnInfo_) {
        auto gridParent = gridColumnInfo_->GetParent();
        if (gridParent && gridParent->GetColumnType() != GridColumnType::NONE) {
            gridParent->BuildColumnWidth(GetLayoutParam().GetMaxSize().Width());
        }

        double defaultWidth = gridColumnInfo_->GetWidth();
        double maxWidth = gridColumnInfo_->GetMaxWidth();
        if (!NearEqual(defaultWidth, maxWidth)) {
            constraints_.SetMinWidth(defaultWidth);
            constraints_.SetMaxWidth(maxWidth);
        } else {
            width_ = Dimension(gridColumnInfo_->GetWidth(), DimensionUnit::PX);
            LayoutParam gridLayoutParam = GetLayoutParam();
            gridLayoutParam.SetMaxSize(Size(width_.Value(), gridLayoutParam.GetMaxSize().Height()));
            gridLayoutParam.SetMinSize(Size(width_.Value(), gridLayoutParam.GetMinSize().Height()));
            SetLayoutParam(gridLayoutParam);
        }

        const auto& offset = gridColumnInfo_->GetOffset();
        if (offset != UNDEFINED_DIMENSION) {
            positionParam_.type = PositionType::ABSOLUTE;
            positionParam_.left.first = offset;
            positionParam_.left.second = true;
        }
    }
}

void RenderBoxBase::CalculateSelfLayoutParam()
{
    // first. Calculate width and height with the parameter that user set in box component
    ConvertConstraintsToPx();
    CalculateWidth();
    CalculateHeight();

    if (gridContainerInfo_) {
        marginOrigin_ = Edge(gridContainerInfo_->GetMarginLeft(), marginOrigin_.Top(),
            gridContainerInfo_->GetMarginRight(), marginOrigin_.Bottom());
    }
    ConvertMarginPaddingToPx();

    if (GreatNotEqual(aspectRatio_, 0.0)) {
        AdjustSizeByAspectRatio();
    }

    Size selfMax = Size(selfMaxWidth_, selfMaxHeight_);
    Size selfMin = Size(selfMinWidth_, selfMinHeight_);

    // second. constrain parameter with LayoutParam
    const LayoutParam& layoutSetByParent = GetLayoutParam();
    Size constrainMax = selfMax;
    Size constrainMin = selfMin;
    if (width_.Unit() != DimensionUnit::PERCENT) {
        // Margin layout width effect to the child when width unit is PERCENT.
        constrainMax.SetWidth(constrainMax.Width() + margin_.GetLayoutSize().Width());
        constrainMin.SetWidth(constrainMin.Width() + margin_.GetLayoutSize().Width());
    }
    if (height_.Unit() != DimensionUnit::PERCENT) {
        // Margin layout height effect to the child when height unit is PERCENT.
        constrainMax.SetHeight(constrainMax.Height() + margin_.GetLayoutSize().Height());
        constrainMin.SetHeight(constrainMin.Height() + margin_.GetLayoutSize().Height());
    }
    selfMax = layoutSetByParent.Constrain(constrainMax);
    selfMin = layoutSetByParent.Constrain(constrainMin);
    selfLayoutParam_.SetMaxSize(selfMax);
    selfLayoutParam_.SetMinSize(selfMin);

    if (gridContainerInfo_) {
        double width = selfMax.Width();
        gridContainerInfo_->BuildColumnWidth(width);
    }

    ConvertPaddingForLayoutInBox();
}

void RenderBoxBase::AdjustSizeByAspectRatio()
{
    const LayoutParam& layoutSetByParent = GetLayoutParam();
    LayoutParam selfLayout = layoutSetByParent;
    if (!layoutSetByParent.HasUsedConstraints() && constraints_.IsWidthValid() && constraints_.IsHeightValid()) {
        selfLayout = layoutSetByParent.Enforce(constraints_);
    }
    auto maxWidth = selfLayout.GetMaxSize().Width();
    auto minWidth = selfLayout.GetMinSize().Width();
    auto maxHeight = selfLayout.GetMaxSize().Height();
    auto minHeight = selfLayout.GetMinSize().Height();
    // Adjust by aspect ratio, firstly pick height based on width. It means that when width, height and aspectRatio are
    // all set, the height is not used.
    if (selfDefineWidth_) {
        selfMaxHeight_ = selfMaxWidth_ / aspectRatio_;
    } else if (selfDefineHeight_) {
        selfMaxWidth_ = selfMaxHeight_ * aspectRatio_;
    } else if (NearEqual(selfMaxWidth_, Size::INFINITE_SIZE)) {
        selfMaxWidth_ = selfMaxHeight_ * aspectRatio_;
    } else {
        selfMaxHeight_ = selfMaxWidth_ / aspectRatio_;
    }
    if (selfMaxWidth_ > maxWidth) {
        selfMaxWidth_ = maxWidth;
        selfMaxHeight_ = selfMaxWidth_ / aspectRatio_;
    }
    if (selfMaxHeight_ > maxHeight) {
        selfMaxHeight_ = maxHeight;
        selfMaxWidth_ = selfMaxHeight_ * aspectRatio_;
    }
    if (selfMaxWidth_ < minWidth) {
        selfMaxWidth_ = minWidth;
        selfMaxHeight_ = selfMaxWidth_ / aspectRatio_;
    }
    if (selfMaxHeight_ < minHeight) {
        selfMaxHeight_ = minHeight;
        selfMaxWidth_ = selfMaxHeight_ * aspectRatio_;
    }
    if (!NearEqual(selfMaxWidth_, Size::INFINITE_SIZE) && !NearEqual(selfMaxHeight_, Size::INFINITE_SIZE)) {
        selfDefineWidth_ = true;
        selfDefineHeight_ = true;
    }
}

void RenderBoxBase::SetChildLayoutParam()
{
    Size deflate = padding_.GetLayoutSize();
    deflate += margin_.GetLayoutSize();
    deflate += GetBorderSize();

    if (deliverMinToChild_) {
        double minWidth = std::max(selfLayoutParam_.GetMinSize().Width() - deflate.Width(), 0.0);
        double minHeight = std::max(selfLayoutParam_.GetMinSize().Height() - deflate.Height(), 0.0);
        childLayoutParam_.SetMinSize(Size(minWidth, minHeight));
    } else {
        childLayoutParam_.SetMinSize(Size(0.0, 0.0));
    }

    double maxWidth = std::max(selfLayoutParam_.GetMaxSize().Width() - deflate.Width(), 0.0);
    double maxHeight = std::max(selfLayoutParam_.GetMaxSize().Height() - deflate.Height(), 0.0);
    childLayoutParam_.SetMaxSize(Size(maxWidth, maxHeight));

    // First time layout all children
    for (const auto& item : GetChildren()) {
        item->Layout(childLayoutParam_);
    }
}

void RenderBoxBase::ConvertPaddingForLayoutInBox()
{
    if (!layoutInBox_) {
        return;
    }

    Size layoutParmMax = selfLayoutParam_.GetMaxSize();
    Size borderSize = GetBorderSize();
    double diameter = std::min(layoutParmMax.Width() - margin_.GetLayoutSize().Width() - borderSize.Width(),
        layoutParmMax.Height() - margin_.GetLayoutSize().Height() - borderSize.Height());

    double circlePadding = diameter * (1.0 - CIRCLE_LAYOUT_IN_BOX_SCALE) / BOX_DIAMETER_TO_RADIUS;

    padding_.SetLeft(Dimension(std::max(padding_.LeftPx(), circlePadding)));
    padding_.SetTop(Dimension(std::max(padding_.TopPx(), circlePadding)));
    padding_.SetRight(Dimension(std::max(padding_.RightPx(), circlePadding)));
    padding_.SetBottom(Dimension(std::max(padding_.BottomPx(), circlePadding)));
}

void RenderBoxBase::CalculateSelfLayoutSize()
{
    Size borderSize = GetBorderSize();

    const LayoutParam& layoutSetByParent = GetLayoutParam();
    Size selfMax = selfLayoutParam_.GetMaxSize() - margin_.GetLayoutSize();
    if (!GetChildren().empty()) {
        childSize_ = GetChildren().front()->GetLayoutSize();
    }
    // calculate width
    double width = 0.0;
    double childWidth = childSize_.Width() + padding_.GetLayoutSize().Width() + borderSize.Width();
    if (selfDefineWidth_) {
        width = selfMax.Width();
    } else if (useFlexWidth_) {
        if (layoutSetByParent.GetMaxSize().IsWidthInfinite() && viewPort_.Width() < childWidth) {
            width = childWidth;
        } else {
            double flexWidth = layoutSetByParent.GetMaxSize().IsWidthInfinite() && !viewPort_.IsWidthInfinite()
                                   ? viewPort_.Width()
                                   : layoutSetByParent.GetMaxSize().Width();
            width = flexWidth - margin_.GetLayoutSize().Width();
        }
    } else {
        if (gridColumnInfo_ && NearEqual(gridColumnInfo_->GetWidth(), gridColumnInfo_->GetMaxWidth())) {
            width = gridColumnInfo_->GetWidth();
        } else {
            width = childWidth;
        }
    }
    // calculate height
    double height = 0.0;
    double childHeight = childSize_.Height() + padding_.GetLayoutSize().Height() + borderSize.Height();
    if (selfDefineHeight_) {
        height = selfMax.Height();
    } else if (useFlexHeight_) {
        if (layoutSetByParent.GetMaxSize().IsHeightInfinite() && viewPort_.Height() < childHeight) {
            height = childHeight;
        } else {
            double flexHeight = layoutSetByParent.GetMaxSize().IsHeightInfinite() && !viewPort_.IsHeightInfinite()
                                    ? viewPort_.Height()
                                    : layoutSetByParent.GetMaxSize().Height();
            height = flexHeight - margin_.GetLayoutSize().Height();
        }
    } else {
        height = childSize_.Height() + padding_.GetLayoutSize().Height() + borderSize.Height();
    }
    paintSize_ = Size(width, height);
    // box layout size = paint size + margin size
    selfLayoutSize_ = GetLayoutParam().Constrain(paintSize_ + margin_.GetLayoutSize());
    paintSize_ = selfLayoutSize_ - margin_.GetLayoutSize();
    touchArea_.SetOffset(margin_.GetOffset());
    touchArea_.SetSize(paintSize_);
    SetLayoutSize(selfLayoutSize_);
}

void RenderBoxBase::CalculateChildPosition()
{
    Offset borderOffset = GetBorderOffset();
    Size parentSize = selfLayoutSize_ - margin_.GetLayoutSize() - padding_.GetLayoutSize();
    parentSize -= GetBorderSize();

    if (!GetChildren().empty()) {
        const auto& child = GetChildren().front();
        childPosition_ = margin_.GetOffset() + borderOffset + padding_.GetOffset() +
                         Alignment::GetAlignPosition(parentSize, child->GetLayoutSize(), align_);
        child->SetPosition(childPosition_);
    }
}

void RenderBoxBase::PerformLayout()
{
    // update scale for margin, padding
    auto context = context_.Upgrade();
    if (!context) {
        LOGE("[BOX][Dep:%{public}d][LAYOUT]Call Context Upgrade failed. PerformLayout failed.", this->GetDepth());
        return;
    }
    if (useLiteStyle_) {
        PerformLayoutInLiteMode();
        if (layoutCallback_) {
            layoutCallback_();
        }
        return;
    }
    CalculateGridLayoutSize();
    // first. calculate self layout param
    CalculateSelfLayoutParam();
    // second. set layout param of child to calculate layout size
    SetChildLayoutParam();
    // third. using layout size of child, calculate layout size of box
    CalculateSelfLayoutSize();
    // forth. calculate position of child
    CalculateChildPosition();
    if (layoutCallback_) {
        layoutCallback_();
    }
}

void RenderBoxBase::PerformLayoutInLiteMode()
{
    // Lite must has width and height
    CalculateWidth();
    CalculateHeight();
    ConvertMarginPaddingToPx();
    if (NearEqual(selfMaxWidth_, Size::INFINITE_SIZE) && !selfDefineWidth_) {
        selfMaxWidth_ = GetLayoutParam().GetMaxSize().Width();
    }
    if (NearEqual(selfMaxHeight_, Size::INFINITE_SIZE) && !selfDefineHeight_) {
        selfMaxHeight_ = GetLayoutParam().GetMaxSize().Height();
    }
    Size selfMax = Size(selfMaxWidth_, selfMaxHeight_) + margin_.GetLayoutSize();
    Size selfMin = Size(selfMinWidth_, selfMinHeight_) + margin_.GetLayoutSize();
    // Do not constrain param in lite mode
    selfLayoutParam_.SetMaxSize(selfMax);
    selfLayoutParam_.SetMinSize(selfMin);
    SetChildLayoutParam();
    double width = 0.0;
    double height = 0.0;
    Size borderSize = GetBorderSize();
    childSize_ = GetChildren().front()->GetLayoutSize();
    if (selfDefineWidth_) {
        width = selfMax.Width() - margin_.GetLayoutSize().Width();
    } else {
        width = childSize_.Width() + padding_.GetLayoutSize().Width() + borderSize.Width();
    }
    if (selfDefineHeight_) {
        height = selfMax.Height() - margin_.GetLayoutSize().Height();
    } else {
        height = childSize_.Height() + padding_.GetLayoutSize().Height() + borderSize.Height();
    }
    // Determine self size, not use constrain.
    paintSize_ = Size(width, height);
    selfLayoutSize_ = paintSize_ + margin_.GetLayoutSize();
    touchArea_.SetOffset(margin_.GetOffset());
    touchArea_.SetSize(paintSize_);
    SetLayoutSize(selfLayoutSize_);
    CalculateChildPosition();
}

void RenderBoxBase::Update(const RefPtr<Component>& component)
{
    const RefPtr<BoxBaseComponent> box = AceType::DynamicCast<BoxBaseComponent>(component);
    if (box) {
        scrollPage_ = box->GetScrollPage();

        paddingOrigin_ = box->GetPadding();
        marginOrigin_ = box->GetMargin();
        additionalMargin_ = box->GetAdditionalMargin();
        flex_ = box->GetFlex();
        constraints_ = box->GetConstraints();
        align_ = box->GetAlignment();
        deliverMinToChild_ = box->GetDeliverMinToChild();
        // When declarative animation is active for this renderbox,
        // the animatable properties are set by PropertyAnimatable::SetProperty.
        // And currently declarative api allow only animating
        // PROPERTY_WIDTH,  PROPERTY_HEIGHT
        if (!IsDeclarativeAnimationActive()) {
            width_ = box->GetWidthDimension();
            height_ = box->GetHeightDimension();
        }
        auto context = context_.Upgrade();
        if (context && scrollPage_) {
            height_ = Dimension(context->GetStageRect().Height(), DimensionUnit::PX);
        }
        percentFlag_ = box->GetPercentFlag();
        layoutInBox_ = box->GetLayoutInBoxFlag();
        aspectRatio_ = box->GetAspectRatio();
        minWidth_ = box->GetMinWidth();
        minHeight_ = box->GetMinHeight();
        maxWidth_ = box->GetMaxWidth();
        maxHeight_ = box->GetMaxHeight();
        useLiteStyle_ = box->UseLiteStyle();
        auto gridLayoutInfo = box->GetGridLayoutInfo();
        auto gridColumnInfo = AceType::DynamicCast<GridColumnInfo>(gridLayoutInfo);
        if (gridColumnInfo) {
            gridColumnInfo_ = gridColumnInfo;
        } else {
            auto gridContainerInfo = AceType::DynamicCast<GridContainerInfo>(gridLayoutInfo);
            if (gridContainerInfo) {
                gridContainerInfo_ = gridContainerInfo;
            }
        }

        MarkNeedLayout();
    }
}

Offset RenderBoxBase::GetPaintPosition() const
{
    return margin_.GetOffset();
}

const Size& RenderBoxBase::GetPaintSize() const
{
    return paintSize_;
}

void RenderBoxBase::SetPaintSize(const Size& paintSize)
{
    paintSize_ = paintSize;
}

void RenderBoxBase::Dump()
{
    double dipScale = 1.0;
    auto context = context_.Upgrade();
    if (context) {
        dipScale = context->GetDipScale();
    }
    Size borderSize = GetBorderSize();
    DumpLog::GetInstance().AddDesc(std::string("WH: ").append(Size(width_.Value(), height_.Value()).ToString()));
    DumpLog::GetInstance().AddDesc("Flex: " + std::to_string(static_cast<int32_t>(flex_)) + ", LayoutInBox: " +
        std::to_string(static_cast<int32_t>(layoutInBox_)) + ", BGcolor: " + std::to_string(GetColor().GetValue()));
    DumpLog::GetInstance().AddDesc(std::string("Align: ").append(align_.ToString()));
    DumpLog::GetInstance().AddDesc(std::string("Margin: ").append(margin_.GetLayoutSizeInPx(dipScale).ToString()));
    DumpLog::GetInstance().AddDesc(std::string("Padding: ").append(padding_.GetLayoutSizeInPx(dipScale).ToString()));
    DumpLog::GetInstance().AddDesc(std::string("Border: ").append(borderSize.ToString()));
    DumpLog::GetInstance().AddDesc(std::string("Constraints: ").append(constraints_.ToString()));
    LayoutParam layoutParam = GetLayoutParam();
    DumpLog::GetInstance().AddDesc(std::string("LayoutParam: ").append(layoutParam.ToString()));
    DumpLog::GetInstance().AddDesc(std::string("SelfLayout: ").append(selfLayoutParam_.ToString()));
    DumpLog::GetInstance().AddDesc(std::string("ChildLayout: ").append(childLayoutParam_.ToString()));
    DumpLog::GetInstance().AddDesc(std::string("PaintSize: ").append(paintSize_.ToString()));
    DumpLog::GetInstance().AddDesc(std::string("TouchArea: ").append(touchArea_.ToString()));
    DumpLog::GetInstance().AddDesc(std::string("SelfSize: ").append(selfLayoutSize_.ToString()));
    DumpLog::GetInstance().AddDesc(std::string("ChildSize: ").append(childSize_.ToString()));
    DumpLog::GetInstance().AddDesc(std::string("ChildPos: ").append(childPosition_.ToString()));
    if (gridColumnInfo_) {
        DumpLog::GetInstance().AddDesc(std::string("GridColumnInfo"));
    }
    if (gridContainerInfo_) {
        DumpLog::GetInstance().AddDesc(std::string("GridContainerInfo"));
    }
}

void RenderBoxBase::ClearRenderObject()
{
    RenderNode::ClearRenderObject();
    width_ = Dimension(-1.0, DimensionUnit::PX);
    height_ = Dimension(-1.0, DimensionUnit::PX);
    flex_ = BoxFlex::FLEX_NO;

    constraints_ = LayoutParam(Size(), Size());
    padding_ = EdgePx();
    margin_ = EdgePx();
    align_ = Alignment();
    paintSize_ = Size();
    touchArea_ = Rect();

    deliverMinToChild_ = true;
    scrollPage_ = false;
    percentFlag_ = 0;
    layoutInBox_ = false;

    paddingOrigin_ = Edge();
    marginOrigin_ = Edge();
    additionalMargin_ = Edge();

    useFlexWidth_ = false;
    useFlexHeight_ = false;
    selfDefineWidth_ = false;
    selfDefineHeight_ = false;
    selfMaxWidth_ = Size::INFINITE_SIZE;
    selfMinWidth_ = 0.0;
    selfMaxHeight_ = Size::INFINITE_SIZE;
    selfMinHeight_ = 0.0;

    aspectRatio_ = 0.0;
    minWidth_ = Dimension();
    minHeight_ = Dimension();
    maxWidth_ = Dimension();
    maxHeight_ = Dimension();

    selfLayoutParam_ = LayoutParam();
    selfLayoutSize_ = Size();
    childLayoutParam_ = LayoutParam();
    childSize_ = Size();
    childPosition_ = Offset();

    layoutCallback_ = nullptr;
    gridColumnInfo_ = nullptr;
    gridContainerInfo_ = nullptr;
}

FloatPropertyAnimatable::SetterMap RenderBoxBase::GetFloatPropertySetterMap()
{
    FloatPropertyAnimatable::SetterMap map;
    auto weak = AceType::WeakClaim(this);
    map[PropertyAnimatableType::PROPERTY_WIDTH] = [weak](float value) {
        auto box = weak.Upgrade();
        if (!box) {
            LOGE("Set width failed. box is null.");
            return;
        }
        box->SetWidth(value);
    };
    const RefPtr<RenderTextField> renderTextField = AceType::DynamicCast<RenderTextField>(GetFirstChild());
    if (renderTextField) {
        WeakPtr<RenderTextField> textWeak = renderTextField;
        map[PropertyAnimatableType::PROPERTY_HEIGHT] = [textWeak](float value) {
            auto renderTextField = textWeak.Upgrade();
            if (!renderTextField) {
                LOGE("Set height failed. text is null.");
                return;
            }
            return renderTextField->SetHeight(value);
        };
    } else {
        map[PropertyAnimatableType::PROPERTY_HEIGHT] = [weak](float value) {
            auto box = weak.Upgrade();
            if (!box) {
                LOGE("Set height failed. box is null.");
                return;
            }
            box->SetHeight(value);
        };
    }

    auto paddingSetFunc = [weak](float value, const DimensionHelper& helper) {
        auto box = weak.Upgrade();
        if (!box) {
            LOGE("Set Padding value failed. box is null");
            return;
        }
        if (helper.Set(value, &box->paddingOrigin_)) {
            box->MarkNeedLayout();
        }
    };
    map[PropertyAnimatableType::PROPERTY_PADDING_LEFT] =
        std::bind(paddingSetFunc, std::placeholders::_1, DimensionHelper(&Edge::SetLeft, &Edge::Left));
    map[PropertyAnimatableType::PROPERTY_PADDING_TOP] =
        std::bind(paddingSetFunc, std::placeholders::_1, DimensionHelper(&Edge::SetTop, &Edge::Top));
    map[PropertyAnimatableType::PROPERTY_PADDING_RIGHT] =
        std::bind(paddingSetFunc, std::placeholders::_1, DimensionHelper(&Edge::SetRight, &Edge::Right));
    map[PropertyAnimatableType::PROPERTY_PADDING_BOTTOM] =
        std::bind(paddingSetFunc, std::placeholders::_1, DimensionHelper(&Edge::SetBottom, &Edge::Bottom));

    auto marginSetFunc = [weak](float value, const DimensionHelper& helper) {
        auto box = weak.Upgrade();
        if (!box) {
            LOGE("Set Margin value failed. box is null.");
            return;
        }
        if (helper.Set(value, &box->marginOrigin_)) {
            box->MarkNeedLayout();
        }
    };

    map[PropertyAnimatableType::PROPERTY_MARGIN_LEFT] =
        std::bind(marginSetFunc, std::placeholders::_1, DimensionHelper(&Edge::SetLeft, &Edge::Left));
    map[PropertyAnimatableType::PROPERTY_MARGIN_TOP] =
        std::bind(marginSetFunc, std::placeholders::_1, DimensionHelper(&Edge::SetTop, &Edge::Top));
    map[PropertyAnimatableType::PROPERTY_MARGIN_RIGHT] =
        std::bind(marginSetFunc, std::placeholders::_1, DimensionHelper(&Edge::SetRight, &Edge::Right));
    map[PropertyAnimatableType::PROPERTY_MARGIN_BOTTOM] =
        std::bind(marginSetFunc, std::placeholders::_1, DimensionHelper(&Edge::SetBottom, &Edge::Bottom));

    return map;
};

FloatPropertyAnimatable::GetterMap RenderBoxBase::GetFloatPropertyGetterMap()
{
    FloatPropertyAnimatable::GetterMap map;
    auto weak = AceType::WeakClaim(this);
    map[PropertyAnimatableType::PROPERTY_WIDTH] = [weak]() -> float {
        auto box = weak.Upgrade();
        if (!box) {
            LOGE("Get width failed. box is null.");
            return 0.0;
        }
        return box->GetWidth();
    };
    const RefPtr<RenderTextField> renderTextField = AceType::DynamicCast<RenderTextField>(GetFirstChild());
    if (renderTextField) {
        WeakPtr<RenderTextField> textWeak = renderTextField;
        map[PropertyAnimatableType::PROPERTY_HEIGHT] = [textWeak]() -> float {
            auto renderTextField = textWeak.Upgrade();
            if (!renderTextField) {
                LOGE("Get height failed. text is null.");
                return 0.0;
            }
            return renderTextField->GetHeight();
        };
    } else {
        map[PropertyAnimatableType::PROPERTY_HEIGHT] = [weak]() -> float {
            auto box = weak.Upgrade();
            if (!box) {
                LOGE("Get height failed. box is null.");
                return 0.0;
            }
            return box->GetHeight();
        };
    }

    auto paddingGetFunc = [weak](const DimensionHelper& helper) -> float {
        auto box = weak.Upgrade();
        if (!box) {
            LOGE("Get Padding failed, box is null.");
            return 0.0f;
        }
        return helper.Get(box->paddingOrigin_).Value();
    };
    map[PropertyAnimatableType::PROPERTY_PADDING_LEFT] =
        std::bind(paddingGetFunc, DimensionHelper(&Edge::SetLeft, &Edge::Left));
    map[PropertyAnimatableType::PROPERTY_PADDING_TOP] =
        std::bind(paddingGetFunc, DimensionHelper(&Edge::SetTop, &Edge::Top));
    map[PropertyAnimatableType::PROPERTY_PADDING_RIGHT] =
        std::bind(paddingGetFunc, DimensionHelper(&Edge::SetRight, &Edge::Right));
    map[PropertyAnimatableType::PROPERTY_PADDING_BOTTOM] =
        std::bind(paddingGetFunc, DimensionHelper(&Edge::SetBottom, &Edge::Bottom));

    auto marginGetFunc = [weak](const DimensionHelper& helper) -> float {
        auto box = weak.Upgrade();
        if (!box) {
            LOGE("Get margin failed. box is null.");
            return 0.0f;
        }
        return helper.Get(box->marginOrigin_).Value();
    };
    map[PropertyAnimatableType::PROPERTY_MARGIN_LEFT] =
        std::bind(marginGetFunc, DimensionHelper(&Edge::SetLeft, &Edge::Left));
    map[PropertyAnimatableType::PROPERTY_MARGIN_TOP] =
        std::bind(marginGetFunc, DimensionHelper(&Edge::SetTop, &Edge::Top));
    map[PropertyAnimatableType::PROPERTY_MARGIN_RIGHT] =
        std::bind(marginGetFunc, DimensionHelper(&Edge::SetRight, &Edge::Right));
    map[PropertyAnimatableType::PROPERTY_MARGIN_BOTTOM] =
        std::bind(marginGetFunc, DimensionHelper(&Edge::SetBottom, &Edge::Bottom));
    return map;
}

} // namespace OHOS::Ace
