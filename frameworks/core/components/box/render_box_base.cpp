/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "base/log/dump_log.h"
#include "base/utils/string_expression.h"
#include "core/components/text_field/render_text_field.h"
#include "core/pipeline/base/constants.h"

namespace OHOS::Ace {
namespace {

const double CIRCLE_LAYOUT_IN_BOX_SCALE = sin(ACE_PI / 4);
constexpr double BOX_DIAMETER_TO_RADIUS = 2.0;
constexpr int32_t COMPATIBLE_VERSION = 5;
constexpr double TWO_SIDES = 2.0;

} // namespace

Size RenderBoxBase::GetBorderSize() const
{
    return Size(0.0, 0.0);
}

Offset RenderBoxBase::GetBorderOffset() const
{
    return Offset(0.0, 0.0);
}

Radius RenderBoxBase::GetBorderRadius() const
{
    return Radius();
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

void RenderBoxBase::OnAnimationCallback()
{
    MarkNeedLayout();
}

double RenderBoxBase::CalculateHeightPercent(double percent) const
{
    return ConvertVerticalDimensionToPx(Dimension(percent, DimensionUnit::PERCENT));
}

double RenderBoxBase::ConvertMarginToPx(CalcDimension dimension, bool vertical, bool additional) const
{
    if (dimension.Unit() == DimensionUnit::CALC) {
        std::string value = dimension.CalcValue();
        auto node = AceType::Claim(const_cast<RenderBoxBase*>(this));
        return StringExpression::CalculateExp(value, [vertical, node](const Dimension& dim) -> double {
            return node->NormalizePercentToPx(dim, vertical, false);
        });
    } else if (dimension.Unit() == DimensionUnit::PERCENT) {
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

double RenderBoxBase::ConvertDimensionToPx(CalcDimension dimension, bool vertical, bool defaultZero) const
{
    if (dimension.Unit() == DimensionUnit::CALC) {
        std::string value = dimension.CalcValue();
        auto node = AceType::Claim(const_cast<RenderBoxBase*>(this));
        return StringExpression::CalculateExp(value, [vertical, node](const Dimension& dim) -> double {
            return node->NormalizePercentToPx(dim, vertical, false);
        });
    } else if (dimension.Unit() == DimensionUnit::PERCENT) {
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

double RenderBoxBase::ConvertHorizontalDimensionToPx(CalcDimension dimension, bool defaultZero) const
{
    return ConvertDimensionToPx(dimension, false, defaultZero);
}

double RenderBoxBase::ConvertVerticalDimensionToPx(CalcDimension dimension, bool defaultZero) const
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

Edge RenderBoxBase::SetAutoMargin(FlexDirection flexDir, double freeSpace, bool isFirst)
{
    Edge margin;
    if (isFirst) {
        margin = marginOrigin_;
    } else {
        margin = marginBackup_;
    }

    if (flexDir == FlexDirection::COLUMN) {
        if (margin.Left().Unit() == DimensionUnit::AUTO && margin.Right().Unit() == DimensionUnit::AUTO) {
            marginOrigin_.SetLeft(Dimension(freeSpace / TWO_SIDES, DimensionUnit::PX));
            marginOrigin_.SetRight(Dimension(freeSpace / TWO_SIDES, DimensionUnit::PX));
        } else if (margin.Left().Unit() == DimensionUnit::AUTO) {
            marginOrigin_.SetRight(Dimension(ConvertMarginToPx(margin.Right(), false, false)));
            marginOrigin_.SetLeft(Dimension((freeSpace - marginOrigin_.Right().Value()), DimensionUnit::PX));
        } else if (margin.Right().Unit() == DimensionUnit::AUTO) {
            marginOrigin_.SetLeft(Dimension(ConvertMarginToPx(margin.Left(), false, false)));
            marginOrigin_.SetRight(Dimension((freeSpace - marginOrigin_.Left().Value()), DimensionUnit::PX));
        }
    } else {
        if (margin.Top().Unit() == DimensionUnit::AUTO && margin.Bottom().Unit() == DimensionUnit::AUTO) {
            marginOrigin_.SetTop(Dimension(freeSpace / TWO_SIDES, DimensionUnit::PX));
            marginOrigin_.SetBottom(Dimension(freeSpace / TWO_SIDES, DimensionUnit::PX));
        } else if (margin.Top().Unit() == DimensionUnit::AUTO) {
            marginOrigin_.SetBottom(Dimension(ConvertMarginToPx(margin.Bottom(), true, false)));
            marginOrigin_.SetTop(Dimension((freeSpace - marginOrigin_.Bottom().Value()), DimensionUnit::PX));
        } else if (margin.Bottom().Unit() == DimensionUnit::AUTO) {
            marginOrigin_.SetTop(Dimension(ConvertMarginToPx(margin.Top(), true, false)));
            marginOrigin_.SetBottom(Dimension((freeSpace - marginOrigin_.Top().Value()), DimensionUnit::PX));
        }
    }
    return marginOrigin_;
}

void RenderBoxBase::CalculateAutoMargin()
{
    double freeSpace = 0.0, width = 0.0, height = 0.0;
    FlexDirection flexDir = FlexDirection::ROW;
    if (marginOrigin_.Left().Unit() == DimensionUnit::AUTO || marginOrigin_.Right().Unit() == DimensionUnit::AUTO ||
        marginOrigin_.Top().Unit() == DimensionUnit::AUTO || marginOrigin_.Bottom().Unit() == DimensionUnit::AUTO ||
        marginBackup_.Left().Unit() == DimensionUnit::AUTO || marginBackup_.Right().Unit() == DimensionUnit::AUTO ||
        marginBackup_.Top().Unit() == DimensionUnit::AUTO || marginBackup_.Bottom().Unit() == DimensionUnit::AUTO) {
        auto parent = GetParent().Upgrade();
        while (parent) {
            RefPtr<RenderFlex> flexFather = AceType::DynamicCast<RenderFlex>(parent);
            if (flexFather) {
                flexDir = flexFather->GetDirection();
                break;
            }
            parent = parent->GetParent().Upgrade();
        }
        LayoutParam param = GetLayoutParam();
        if ((flexDir == FlexDirection::COLUMN ||
                (flexDir == FlexDirection::ROW && displayType_ == DisplayType::BLOCK)) &&
            width_.Value() == -1.0) {
            if (childWidth_ != 0.0) {
                width = childWidth_;
                freeSpace = param.GetMaxSize().Width() - width;
                SetAutoMargin(FlexDirection::COLUMN, freeSpace, false);
            } else {
                marginBackup_ = marginOrigin_;
                marginOrigin_.SetLeft(Dimension(0.0, DimensionUnit::PX));
                marginOrigin_.SetRight(Dimension(0.0, DimensionUnit::PX));
                needReCalc_ = true;
            }
        } else if ((flexDir == FlexDirection::COLUMN ||
                       (flexDir == FlexDirection::ROW && displayType_ == DisplayType::BLOCK)) &&
                   width_.Value() != -1.0) {
            width = width_.Value();
            freeSpace = param.GetMaxSize().Width() - width;
            SetAutoMargin(FlexDirection::COLUMN, freeSpace, true);
        } else if (flexDir == FlexDirection::ROW && height_.Value() == -1.0) {
            if (childHeight_ != 0.0) {
                height = childHeight_;
                freeSpace = param.GetMaxSize().Height() - height;
                SetAutoMargin(flexDir, freeSpace, false);
            } else {
                marginBackup_ = marginOrigin_;
                marginOrigin_.SetTop(Dimension(0.0, DimensionUnit::PX));
                marginOrigin_.SetBottom(Dimension(0.0, DimensionUnit::PX));
                needReCalc_ = true;
            }
        } else if (flexDir == FlexDirection::ROW && height_.Value() != -1.0) {
            height = height_.Value();
            freeSpace = param.GetMaxSize().Height() - height;
            SetAutoMargin(flexDir, freeSpace, true);
        }
    }
}

void RenderBoxBase::ConvertMarginPaddingToPx()
{
    padding_ = ConvertEdgeToPx(paddingOrigin_, false) + ConvertEdgeToPx(additionalPadding_, true);
    CalculateAutoMargin();
    margin_ = ConvertEdgeToPx(marginOrigin_, false);
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
    if (!gridColumnInfo_) {
        return;
    }

    auto offset = gridColumnInfo_->GetOffset();
    if (offset != UNDEFINED_DIMENSION) {
        if (IsHeadRenderNode()) {
            auto context = context_.Upgrade();
            positionParam_.type =
                (context && context->GetIsDeclarative()) ? PositionType::PTSEMI_RELATIVE : PositionType::PTABSOLUTE;
            std::pair<AnimatableDimension, bool>& edge =
                (GetTextDirection() == TextDirection::RTL) ? positionParam_.right : positionParam_.left;
            edge.first = offset;
            edge.second = true;
        } else {
            auto headRenderNode = GetHeadRenderNode();
            if (headRenderNode) {
                auto context = headRenderNode->GetContext().Upgrade();
                headRenderNode->SetPositionType(
                    (context && context->GetIsDeclarative()) ? PositionType::PTSEMI_RELATIVE :
                        PositionType::PTABSOLUTE);
                headRenderNode->GetTextDirection() == TextDirection::RTL ? headRenderNode->SetRight(offset)
                                                                         : headRenderNode->SetLeft(offset);
            }
        }
        // the above two cases will only work on rosen, so using below to support on preview.
#ifndef ENABLE_ROSEN_BACKEND
        auto context = context_.Upgrade();
        positionParam_.type =
            (context && context->GetIsDeclarative()) ? PositionType::PTSEMI_RELATIVE : PositionType::PTABSOLUTE;
        std::pair<AnimatableDimension, bool>& edge =
            (GetTextDirection() == TextDirection::RTL) ? positionParam_.right : positionParam_.left;
        edge.first = offset;
        edge.second = true;
#endif
    }

    double defaultWidth = gridColumnInfo_->GetWidth();
    if (NearEqual(defaultWidth, 0.0)) {
        return;
    }
    double maxWidth = gridColumnInfo_->GetMaxWidth();
    if (!NearEqual(defaultWidth, maxWidth)) {
        constraints_.SetMinWidth(defaultWidth);
        constraints_.SetMaxWidth(maxWidth);
    } else {
        width_ = AnimatableDimension(gridColumnInfo_->GetWidth(), DimensionUnit::PX);
        LayoutParam gridLayoutParam = GetLayoutParam();
        gridLayoutParam.SetMaxSize(Size(width_.Value(), gridLayoutParam.GetMaxSize().Height()));
        gridLayoutParam.SetMinSize(Size(width_.Value(), gridLayoutParam.GetMinSize().Height()));
        SetLayoutParam(gridLayoutParam);
    }
}

void RenderBoxBase::CalculateSelfLayoutParam()
{
    // first. Calculate width and height with the parameter that user set in box component
    ConvertConstraintsToPx();
    CalculateWidth();
    CalculateHeight();

    if (gridContainerInfo_ && gridContainerInfo_->GetColumnType() == GridColumnType::NONE) {
        marginOrigin_ = Edge(gridContainerInfo_->GetMarginLeft(), marginOrigin_.Top(),
            gridContainerInfo_->GetMarginRight(), marginOrigin_.Bottom());
    }
    ConvertMarginPaddingToPx();
    if (GreatNotEqual(aspectRatio_.Value(), 0.0)) {
        AdjustSizeByAspectRatio();
    }

    Size selfMax = Size(selfMaxWidth_, selfMaxHeight_);
    Size selfMin = Size(selfMinWidth_, selfMinHeight_);

    // second. constrain parameter with LayoutParam
    const LayoutParam& layoutSetByParent = GetLayoutParam();
    Size constrainMax = selfMax;
    Size constrainMin = selfMin;

    if (minPlatformVersion_ != COMPATIBLE_VERSION || width_.Unit() != DimensionUnit::PERCENT) {
        constrainMax.SetWidth(constrainMax.Width() + margin_.GetLayoutSize().Width());
        constrainMin.SetWidth(constrainMin.Width() + margin_.GetLayoutSize().Width());
    }
    if (minPlatformVersion_ != COMPATIBLE_VERSION || height_.Unit() != DimensionUnit::PERCENT) {
        constrainMax.SetHeight(constrainMax.Height() + margin_.GetLayoutSize().Height());
        constrainMin.SetHeight(constrainMin.Height() + margin_.GetLayoutSize().Height());
    }

    selfMax = layoutSetByParent.Constrain(constrainMax);
    selfMin = layoutSetByParent.Constrain(constrainMin);
    auto context = context_.Upgrade();
    // allow overflow parent when set height or width, except when set flexgrow or flexshrink
    if (context->GetIsDeclarative()) {
        if (selfDefineWidth_ && layoutSetByParent.GetMinSize().Width() != layoutSetByParent.GetMaxSize().Width()) {
            selfMax.SetWidth(constrainMax.Width());
        }
        if (selfDefineHeight_ && layoutSetByParent.GetMinSize().Height() != layoutSetByParent.GetMaxSize().Height()) {
            selfMax.SetHeight(constrainMax.Height());
        }
    }

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
        selfMaxHeight_ = selfMaxWidth_ / aspectRatio_.Value();
    } else if (selfDefineHeight_) {
        selfMaxWidth_ = selfMaxHeight_ * aspectRatio_.Value();
    } else if (NearEqual(selfMaxWidth_, Size::INFINITE_SIZE)) {
        selfMaxWidth_ = selfMaxHeight_ * aspectRatio_.Value();
    } else {
        selfMaxHeight_ = selfMaxWidth_ / aspectRatio_.Value();
    }
    if (selfMaxWidth_ > maxWidth) {
        selfMaxWidth_ = maxWidth;
        selfMaxHeight_ = selfMaxWidth_ / aspectRatio_.Value();
    }
    if (selfMaxHeight_ > maxHeight) {
        selfMaxHeight_ = maxHeight;
        selfMaxWidth_ = selfMaxHeight_ * aspectRatio_.Value();
    }
    if (selfMaxWidth_ < minWidth) {
        selfMaxWidth_ = minWidth;
        selfMaxHeight_ = selfMaxWidth_ / aspectRatio_.Value();
    }
    if (selfMaxHeight_ < minHeight) {
        selfMaxHeight_ = minHeight;
        selfMaxWidth_ = selfMaxHeight_ * aspectRatio_.Value();
    }
    if (!NearEqual(selfMaxWidth_, Size::INFINITE_SIZE) && !NearEqual(selfMaxHeight_, Size::INFINITE_SIZE)) {
        selfDefineWidth_ = true;
        selfDefineHeight_ = true;
    }
}

void RenderBoxBase::SetChildLayoutParam()
{
    Size deflate;
    if (boxSizing_ == BoxSizing::BORDER_BOX) {
        deflate += padding_.GetLayoutSize();
        deflate += GetBorderSize();
    }
    deflate += margin_.GetLayoutSize();

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

bool RenderBoxBase::IsDeclarativePara()
{
    auto context = context_.Upgrade();
    if (!context) {
        return false;
    }

    return context->GetIsDeclarative();
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
        childWidth_ = childSize_.Width();
        childHeight_ = childSize_.Height();
    }
    // calculate width
    double width = 0.0;
    double childWidth = childSize_.Width() + padding_.GetLayoutSize().Width() + borderSize.Width();
    if (selfDefineWidth_) {
        if (boxSizing_ == BoxSizing::BORDER_BOX) {
            width = selfMax.Width();
        } else {
            width = selfMax.Width() + padding_.GetLayoutSize().Width() + borderSize.Width();
        }
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
        width = childWidth;
        if (gridColumnInfo_) {
            auto columnWidth = gridColumnInfo_->GetWidth();
            if (NearEqual(columnWidth, gridColumnInfo_->GetMaxWidth()) && !NearEqual(columnWidth, 0.0)) {
                width = columnWidth;
            }
        }
    }
    // calculate height
    double height = 0.0;
    double childHeight = childSize_.Height() + padding_.GetLayoutSize().Height() + borderSize.Height();
    if (selfDefineHeight_) {
        if (boxSizing_ == BoxSizing::BORDER_BOX) {
            height = selfMax.Height();
        } else {
            height = selfMax.Height() + padding_.GetLayoutSize().Height() + borderSize.Height();
        }
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
        if (IsDeclarativePara()) {
            if (height < selfMinHeight_) {
                height = selfMinHeight_;
            }
        }
    }

    const static int32_t PLATFORM_VERSION_SIX = 6;
    auto context = GetContext().Upgrade();
    if (context && context->GetMinPlatformVersion() >= PLATFORM_VERSION_SIX) {
        double minWidth = padding_.GetLayoutSize().Width() + borderSize.Width();
        double minHeight = padding_.GetLayoutSize().Height() + borderSize.Height();
        width = width > minWidth ? width : minWidth;
        height = height > minHeight ? height : minHeight;
    }
    // allow force layoutsize for parent

    if (layoutSetByParent.GetMaxSize().Width() == layoutSetByParent.GetMinSize().Width()) {
        width = layoutSetByParent.GetMinSize().Width() - margin_.GetLayoutSize().Width();
    }
    if (layoutSetByParent.GetMaxSize().Height() == layoutSetByParent.GetMinSize().Height()) {
        height = layoutSetByParent.GetMinSize().Height() - margin_.GetLayoutSize().Height();
    }
    paintSize_ = Size(width, height);
    if (context && context->GetIsDeclarative()) {
        // box layout size = paint size + margin size
        if (LessNotEqual(margin_.LeftPx(), 0.0)) {
            positionParam_.left = std::make_pair(margin_.Left(), true);
            margin_.SetLeft(Dimension(0.0, margin_.Left().Unit()));
        }
        if (LessNotEqual(margin_.TopPx(), 0.0)) {
            positionParam_.top = std::make_pair(margin_.Top(), true);
            margin_.SetTop(Dimension(0.0, margin_.Top().Unit()));
        }
        selfLayoutSize_ = paintSize_ + margin_.GetLayoutSize();
    } else {
        selfLayoutSize_ = GetLayoutParam().Constrain(paintSize_ + margin_.GetLayoutSize());
    }

    paintSize_ = selfLayoutSize_ - margin_.GetLayoutSize();
    touchArea_.SetOffset(margin_.GetOffset());
    touchArea_.SetSize(paintSize_);
    SetLayoutSize(selfLayoutSize_);
    isChildOverflow_ = childSize_.Width() > GetLayoutSize().Width() || childSize_.Height() > GetLayoutSize().Height();
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
    if (isUseAlign_) {
        context->AddAlignDeclarationNode(AceType::Claim(this));
    }

    CalculateGridLayoutSize();
    // first. calculate self layout param
    CalculateSelfLayoutParam();
    // second. set layout param of child to calculate layout size
    SetChildLayoutParam();
    // third. using layout size of child, calculate layout size of box
    CalculateSelfLayoutSize();

    if (needReCalc_) {
        needReCalc_ = false;
        CalculateSelfLayoutParam();
        SetChildLayoutParam();
        CalculateSelfLayoutSize();
    }
    // forth. calculate position of child
    CalculateChildPosition();

    if (isUseAlign_) {
        CalculateAlignDeclaration();
    }

    if (layoutCallback_) {
        layoutCallback_();
    }
}

void RenderBoxBase::Update(const RefPtr<Component>& component)
{
    const RefPtr<BoxBaseComponent> box = AceType::DynamicCast<BoxBaseComponent>(component);
    if (box) {
        scrollPage_ = box->GetScrollPage();

        displayType_ = box->GetDisplayType();
        paddingOrigin_ = box->GetPadding();
        marginOrigin_ = box->GetMargin();
        additionalPadding_ = box->GetAdditionalPadding();
        flex_ = box->GetFlex();
        boxSizing_ = box->GetBoxSizing();
        constraints_ = box->GetConstraints();
        align_ = box->GetAlignment();
        overflow_ = box->GetOverflow();
        clipPath_ = box->GetClipPath();
        deliverMinToChild_ = box->GetDeliverMinToChild();
        width_ = box->GetWidthDimension();
        height_ = box->GetHeightDimension();
        auto context = context_.Upgrade();
        if (context && scrollPage_) {
            height_ = AnimatableDimension(context->GetStageRect().Height(), DimensionUnit::PX);
        }
        percentFlag_ = box->GetPercentFlag();
        layoutInBox_ = box->GetLayoutInBoxFlag();
        aspectRatio_ = box->GetAspectRatio();
        minWidth_ = box->GetMinWidth();
        minHeight_ = box->GetMinHeight();
        maxWidth_ = box->GetMaxWidth();
        maxHeight_ = box->GetMaxHeight();
        if (aspectRatio_.IsValid()) {
            if (GreatNotEqual(minWidth_.Value(), 0.0) && NearZero(minHeight_.Value())) {
                minHeight_ = minWidth_ / aspectRatio_.Value();
            }
            if (GreatNotEqual(minHeight_.Value(), 0.0) && NearZero(minWidth_.Value())) {
                minWidth_ = minHeight_ * aspectRatio_.Value();
            }
        }
        useLiteStyle_ = box->UseLiteStyle();
        mask_ = box->GetMask();
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
        isUseAlign_ = box->IsUseAlign();
        if (isUseAlign_) {
            alignPtr_ = box->GetAlignDeclarationPtr();
            alignSide_ = box->GetUseAlignSide();
            alignItemOffset_ = box->GetUseAlignOffset();
        }
        boxClipFlag_ = box->GetBoxClipFlag();
        pixelMap_ = box->GetPixelMap();

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
    Radius radius = GetBorderRadius();
    DumpLog::GetInstance().AddDesc(std::string("WH: ")
                                       .append(Size(width_.Value(), height_.Value()).ToString())
                                       .append(", Margin: ")
                                       .append(margin_.GetLayoutSizeInPx(dipScale).ToString())
                                       .append(", Padding: ")
                                       .append(padding_.GetLayoutSizeInPx(dipScale).ToString())
                                       .append(", Border: ")
                                       .append(borderSize.ToString())
                                       .append(", Radius: ")
                                       .append(radius.GetX().ToString())
                                       .append(", Constraints: ")
                                       .append(constraints_.ToString())
                                       .append(", BGcolor: ")
                                       .append(std::to_string(GetColor().GetValue())));
    DumpLog::GetInstance().AddDesc(std::string("SelfSize: ")
                                       .append(selfLayoutSize_.ToString())
                                       .append(", ChildSize: ")
                                       .append(childSize_.ToString())
                                       .append(", ChildPos: ")
                                       .append(childPosition_.ToString()));
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
    width_ = Dimension(-1.0);
    height_ = Dimension(-1.0);
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

    displayType_ = DisplayType::NO_SETTING;
    paddingOrigin_ = Edge();
    marginOrigin_ = Edge();
    additionalPadding_ = Edge();

    useFlexWidth_ = false;
    useFlexHeight_ = false;
    selfDefineWidth_ = false;
    selfDefineHeight_ = false;
    selfMaxWidth_ = Size::INFINITE_SIZE;
    selfMinWidth_ = 0.0;
    selfMaxHeight_ = Size::INFINITE_SIZE;
    selfMinHeight_ = 0.0;

    aspectRatio_ = AnimatableDimension();
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

    isUseAlign_ = false;
    alignPtr_ = nullptr;
    alignSide_ = AlignDeclaration::Edge::AUTO;
    alignItemOffset_ = Dimension();
    alignOffset_.Reset();
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
    return map;
}

void RenderBoxBase::CalculateAlignDeclaration()
{
    alignOffset_.Reset();
    if (!GetAlignDeclarationOffset(alignPtr_, alignOffset_)) {
        alignOffset_.Reset();
        return;
    }

    double itemAlignOffset = 0.0;
    auto context = GetContext().Upgrade();
    if (context) {
        itemAlignOffset = context->NormalizeToPx(alignItemOffset_);
    }

    switch (alignSide_) {
        case AlignDeclaration::Edge::TOP:
            alignOffset_ = alignOffset_ + Offset(0, itemAlignOffset);
            break;
        case AlignDeclaration::Edge::CENTER:
            alignOffset_ = alignOffset_ - Offset(0, GetLayoutSize().Height() / 2 - itemAlignOffset);
            break;
        case AlignDeclaration::Edge::BOTTOM:
            alignOffset_ = alignOffset_ - Offset(0, GetLayoutSize().Height() - itemAlignOffset);
            break;
        case AlignDeclaration::Edge::BASELINE:
            alignOffset_ = alignOffset_ - Offset(0, GetBaselineDistance(TextBaseline::ALPHABETIC) - itemAlignOffset);
            break;
        case AlignDeclaration::Edge::START:
            alignOffset_ = alignOffset_ + Offset(itemAlignOffset, 0);
            break;
        case AlignDeclaration::Edge::MIDDLE:
            alignOffset_ = alignOffset_ - Offset(GetLayoutSize().Width() / 2 - itemAlignOffset, 0);
            break;
        case AlignDeclaration::Edge::END:
            alignOffset_ = alignOffset_ - Offset(GetLayoutSize().Width() - itemAlignOffset, 0);
            break;
        default:
            alignOffset_.Reset();
            break;
    }
}

} // namespace OHOS::Ace
