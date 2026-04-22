/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/menu/menu_layout_algorithm.h"

#include "core/common/ace_engine.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/overlay/dialog_manager.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/pattern/menu/menu_tag_constants.h"

namespace OHOS::Ace::NG {

namespace {
constexpr size_t ALIGNMENT_STEP_OFFSET = 2;
constexpr Dimension MIN_MENU_HEIGHT = 48.0_vp;
constexpr Dimension MIN_MENU_HEIGHT_HAD = 40.0_vp;

const std::map<Placement, std::vector<Placement>> PLACEMENT_STATES = {
    { Placement::BOTTOM_LEFT,
        {
            Placement::BOTTOM_LEFT,
            Placement::BOTTOM_RIGHT,
            Placement::TOP_LEFT,
            Placement::TOP_RIGHT,
            Placement::RIGHT_TOP,
            Placement::RIGHT_BOTTOM,
            Placement::LEFT_TOP,
            Placement::LEFT_BOTTOM,
            Placement::NONE,
        } },
    { Placement::BOTTOM,
        {
            Placement::BOTTOM,
            Placement::BOTTOM_LEFT,
            Placement::BOTTOM_RIGHT,
            Placement::TOP,
            Placement::TOP_LEFT,
            Placement::TOP_RIGHT,
            Placement::RIGHT,
            Placement::RIGHT_TOP,
            Placement::RIGHT_BOTTOM,
            Placement::LEFT,
            Placement::LEFT_TOP,
            Placement::LEFT_BOTTOM,
            Placement::NONE,
        } },
    { Placement::BOTTOM_RIGHT,
        {
            Placement::BOTTOM_RIGHT,
            Placement::BOTTOM_LEFT,
            Placement::TOP_RIGHT,
            Placement::TOP_LEFT,
            Placement::RIGHT_BOTTOM,
            Placement::RIGHT_TOP,
            Placement::LEFT_BOTTOM,
            Placement::LEFT_TOP,
            Placement::NONE,
        } },
    { Placement::TOP_LEFT,
        {
            Placement::TOP_LEFT,
            Placement::TOP_RIGHT,
            Placement::BOTTOM_LEFT,
            Placement::BOTTOM_RIGHT,
            Placement::RIGHT_TOP,
            Placement::RIGHT_BOTTOM,
            Placement::LEFT_TOP,
            Placement::LEFT_BOTTOM,
            Placement::NONE,
        } },
    { Placement::TOP,
        {
            Placement::TOP,
            Placement::TOP_LEFT,
            Placement::TOP_RIGHT,
            Placement::BOTTOM,
            Placement::BOTTOM_LEFT,
            Placement::BOTTOM_RIGHT,
            Placement::RIGHT,
            Placement::RIGHT_TOP,
            Placement::RIGHT_BOTTOM,
            Placement::LEFT,
            Placement::LEFT_TOP,
            Placement::LEFT_BOTTOM,
            Placement::NONE,
        } },
    { Placement::TOP_RIGHT,
        {
            Placement::TOP_RIGHT,
            Placement::TOP_LEFT,
            Placement::BOTTOM_RIGHT,
            Placement::BOTTOM_LEFT,
            Placement::RIGHT_BOTTOM,
            Placement::RIGHT_TOP,
            Placement::LEFT_BOTTOM,
            Placement::LEFT_TOP,
            Placement::NONE,
        } },
    { Placement::LEFT_TOP,
        {
            Placement::LEFT_TOP,
            Placement::LEFT_BOTTOM,
            Placement::RIGHT_TOP,
            Placement::RIGHT_BOTTOM,
            Placement::BOTTOM_LEFT,
            Placement::BOTTOM_RIGHT,
            Placement::TOP_LEFT,
            Placement::TOP_RIGHT,
            Placement::NONE,
        } },
    { Placement::LEFT,
        {
            Placement::LEFT,
            Placement::LEFT_TOP,
            Placement::LEFT_BOTTOM,
            Placement::RIGHT,
            Placement::RIGHT_TOP,
            Placement::RIGHT_BOTTOM,
            Placement::BOTTOM,
            Placement::BOTTOM_LEFT,
            Placement::BOTTOM_RIGHT,
            Placement::TOP,
            Placement::TOP_LEFT,
            Placement::TOP_RIGHT,
            Placement::NONE,
        } },
    { Placement::LEFT_BOTTOM,
        {
            Placement::LEFT_BOTTOM,
            Placement::LEFT_TOP,
            Placement::RIGHT_BOTTOM,
            Placement::RIGHT_TOP,
            Placement::BOTTOM_RIGHT,
            Placement::BOTTOM_LEFT,
            Placement::TOP_RIGHT,
            Placement::TOP_LEFT,
            Placement::NONE,
        } },
    { Placement::RIGHT_TOP,
        {
            Placement::RIGHT_TOP,
            Placement::RIGHT_BOTTOM,
            Placement::LEFT_TOP,
            Placement::LEFT_BOTTOM,
            Placement::BOTTOM_LEFT,
            Placement::BOTTOM_RIGHT,
            Placement::TOP_LEFT,
            Placement::TOP_RIGHT,
            Placement::NONE,
        } },
    { Placement::RIGHT,
        {
            Placement::RIGHT,
            Placement::RIGHT_TOP,
            Placement::RIGHT_BOTTOM,
            Placement::LEFT,
            Placement::LEFT_TOP,
            Placement::LEFT_BOTTOM,
            Placement::BOTTOM,
            Placement::BOTTOM_LEFT,
            Placement::BOTTOM_RIGHT,
            Placement::TOP,
            Placement::TOP_LEFT,
            Placement::TOP_RIGHT,
            Placement::NONE,
        } },
    { Placement::RIGHT_BOTTOM,
        {
            Placement::RIGHT_BOTTOM,
            Placement::RIGHT_TOP,
            Placement::LEFT_BOTTOM,
            Placement::LEFT_TOP,
            Placement::BOTTOM_RIGHT,
            Placement::BOTTOM_LEFT,
            Placement::TOP_RIGHT,
            Placement::TOP_LEFT,
            Placement::NONE,
        } },
};
} // namespace

void MenuLayoutAlgorithm::UpdatePropTargetSpace(
    const RefPtr<MenuLayoutProperty>& props, const RefPtr<MenuPattern>& menuPattern)
{
    CHECK_NULL_VOID(menuPattern);
    CHECK_NULL_VOID(props);
    if (menuPattern->GetPreviewMode() == MenuPreviewMode::NONE || props->GetMenuTargetSpace().has_value()) {
        propTargetSpace_ = props->GetMenuTargetSpace();
        propTargetOffset_ = props->GetTargetOffset();
        proptargetSize_ = props->GetTargetMenuSize();
    } else {
        propTargetSpace_.reset();
        propTargetOffset_.reset();
        proptargetSize_.reset();
    }
}

void MenuLayoutAlgorithm::UpdateTargetValue(const LayoutWrapper* layoutWrapper)
{
    auto props = AceType::DynamicCast<MenuLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(props);
    props->UpdateTargetOffset(targetOffset_);
    props->UpdateTargetMenuSize(targetSize_);
}

void MenuLayoutAlgorithm::UpdateTargetSpaceScroll(LayoutWrapper* layoutWrapper, LayoutConstraintF& constraint)
{
    if (!propTargetSpace_.has_value()) {
        return;
    }
    float maxSpaceHeight = constraint.maxSize.Height();
    float targetSpace = propTargetSpace_.value().ConvertToPx();
    CHECK_NULL_VOID(layoutWrapper);
    auto menuNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(menuNode);
    auto menuNodePattern = AceType::DynamicCast<MenuPattern>(menuNode->GetPattern());
    CHECK_NULL_VOID(menuNodePattern);
    auto geometryNode = menuNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto menuWidth = geometryNode->GetFrameSize().Height();
    if (menuNodePattern->IsSubMenu() || menuWidth <= 0) {
        return;
    }
    auto parentPlacement = menuNodePattern->GetLastPlacement().value_or(Placement::NONE);
    float yMin = std::max(1.0f, static_cast<float>(wrapperRect_.Top()) + paddingTop_);
    float yMax = static_cast<float>(wrapperRect_.Bottom()) - paddingBottom_;
    float targetOffset = propTargetOffset_.has_value() ? propTargetOffset_.value().GetY() : targetOffset_.GetY();
    float targetSize = proptargetSize_.has_value() ? proptargetSize_.value().Height() : targetSize_.Height();
    float topSpace = targetOffset - targetSpace - yMin;
    float bottomSpace = yMax - targetOffset - targetSpace - targetSize;
    if (parentPlacement == Placement::NONE) {
        auto idealHeight = std::max({ topSpace, bottomSpace });
        constraint.maxSize.SetHeight(std::min({ idealHeight, maxSpaceHeight }));
        positionOffset_ = OffsetF(0.0f, 0.0f);
        return;
    }
    UpdateTargetSpaceMaxHeight(layoutWrapper, constraint, topSpace, bottomSpace);
}

void MenuLayoutAlgorithm::UpdateTargetSpaceMaxHeight(
    LayoutWrapper* layoutWrapper, LayoutConstraintF& constraint, float topSpace, float bottomSpace)
{
    CHECK_NULL_VOID(layoutWrapper);
    float maxSpaceHeight = constraint.maxSize.Height();
    auto menuNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(menuNode);
    auto geometryNode = menuNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto menuNodePattern = AceType::DynamicCast<MenuPattern>(menuNode->GetPattern());
    CHECK_NULL_VOID(menuNodePattern);
    auto parentPlacement = menuNodePattern->GetLastPlacement().value_or(Placement::NONE);
    bool isTop = parentPlacement == Placement::TOP_LEFT || parentPlacement == Placement::TOP ||
                 parentPlacement == Placement::TOP_RIGHT;
    bool isBottom = parentPlacement == Placement::BOTTOM_LEFT || parentPlacement == Placement::BOTTOM ||
                    parentPlacement == Placement::BOTTOM_RIGHT;
    if (!isTop && !isBottom) {
        return;
    }
    auto useLastPosition = lastPosition_.has_value() && holdEmbeddedMenuPosition_;
    auto menuBottom = menuNode->GetPaintRectOffset(false, true).GetY() + geometryNode->GetFrameSize().Height();
    float topOffset = GreatOrEqual(positionOffset_.GetY(), 0.0f) ? topSpace : topSpace - positionOffset_.GetY();
    float bottomOffset =
        GreatOrEqual(positionOffset_.GetY(), 0.0f) ? bottomSpace : bottomSpace - positionOffset_.GetY();
    if (isTop && useLastPosition) {
        float yMin = std::max(1.0f, static_cast<float>(wrapperRect_.Top()) + paddingTop_);
        float topPosition = menuBottom >= topSpace + yMin ? topSpace : topOffset;
        const auto menuSize = GetMeasureSize(layoutWrapper, constraint);
        if (menuSize.Height() > topPosition) {
            constraint.maxSize.SetHeight(std::min(topPosition, maxSpaceHeight));
        }
        return;
    }
    if (!useLastPosition) {
        return;
    }
    auto idealHeight = std::max({ topOffset, bottomOffset });
    if (isTop) {
        if (idealHeight == bottomOffset) {
            idealHeight = bottomSpace;
        }
    }
    if (isBottom) {
        if (idealHeight == topOffset) {
            idealHeight = topSpace;
        }
    }
    constraint.maxSize.SetHeight(std::min(idealHeight, maxSpaceHeight));
}

void MenuLayoutAlgorithm::UpdateExpandSize(
    LayoutWrapper* layoutWrapper, LayoutConstraintF& childConstraint, RefPtr<FrameNode> parentItem)
{
    auto parentPattern = parentItem->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(parentPattern);
    auto expandingMode = parentPattern->GetExpandingMode();
    if (expandingMode == SubMenuExpandingMode::STACK) {
        UpdateStackHeight(layoutWrapper, childConstraint, parentItem);
    } else if (propTargetSpace_.has_value() && expandingMode == SubMenuExpandingMode::SIDE) {
        UpdateSideHeight(layoutWrapper, childConstraint, parentItem);
    }
}

void MenuLayoutAlgorithm::UpdateEmbeddedPosition(
    OffsetF& menuPosition, const RefPtr<MenuPattern>& menuPattern, const SizeF& size, const RefPtr<FrameNode>& menuNode)
{
    if (!propTargetSpace_.has_value()) {
        return;
    }
    CHECK_NULL_VOID(menuPattern);
    auto menuWrapper = menuPattern->GetMenuWrapper();
    CHECK_NULL_VOID(menuWrapper);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    auto innerMenu = menuWrapperPattern->GetMenuChild(menuNode);
    CHECK_NULL_VOID(innerMenu);
    auto innerMenuPattern = AceType::DynamicCast<MenuPattern>(innerMenu->GetPattern());
    CHECK_NULL_VOID(innerMenuPattern);
    auto layoutProps = innerMenuPattern->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(layoutProps);
    auto expandingMode = layoutProps->GetExpandingMode().value_or(SubMenuExpandingMode::SIDE);
    if (expandingMode != SubMenuExpandingMode::EMBEDDED) {
        return;
    }
    auto parentPlacement = menuPattern->GetLastPlacement().value_or(Placement::NONE);
    bool isUpdatePosition = parentPlacement == Placement::TOP || parentPlacement == Placement::TOP_LEFT ||
                            parentPlacement == Placement::TOP_RIGHT;
    if (!isUpdatePosition) {
        return;
    }
    float targetSpace = propTargetSpace_.value().ConvertToPx();
    float yMin = std::max(1.0f, static_cast<float>(wrapperRect_.Top()) + paddingTop_);
    float y = targetOffset_.GetY() - size.Height() - targetSpace_ - targetSpace;
    float idealY = std::max({ yMin, y });
    menuPosition = { menuPosition.GetX(), idealY };
}

void MenuLayoutAlgorithm::UpdateStackHeight(
    LayoutWrapper* layoutWrapper, LayoutConstraintF& childConstraint, RefPtr<FrameNode> parentItem)
{
    auto parentPattern = parentItem->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(parentPattern);
    auto parentMenu = parentPattern->GetMenu();
    CHECK_NULL_VOID(parentMenu);
    auto geometryNode = parentMenu->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto parentWidth = geometryNode->GetFrameSize().Width();
    childConstraint.minSize.SetWidth(parentWidth);
    childConstraint.maxSize.SetWidth(parentWidth);
    childConstraint.selfIdealSize.SetWidth(parentWidth);
    Placement parentPlacement = GetPlacementWithItem(parentItem);
    bool isTop = parentPlacement == Placement::TOP || parentPlacement == Placement::TOP_LEFT ||
                 parentPlacement == Placement::TOP_RIGHT;
    float subMenuMaxHeight;
    if (propTargetSpace_.has_value() && isTop) {
        subMenuMaxHeight = CalcSubMenuMaxHeightTargetSpace(childConstraint, parentItem);
    } else {
        subMenuMaxHeight = CalcSubMenuMaxHeightConstraint(childConstraint, parentItem);
    }
    childConstraint.maxSize.SetHeight(std::min(subMenuMaxHeight, childConstraint.maxSize.Height()));
}

void MenuLayoutAlgorithm::UpdateSideHeight(
    LayoutWrapper* layoutWrapper, LayoutConstraintF& childConstraint, RefPtr<FrameNode> parentItem)
{
    if (!propTargetOffset_.has_value() || !proptargetSize_.has_value()) {
        return;
    }
    CHECK_NULL_VOID(parentItem);
    auto parentItemGeometryNode = parentItem->GetGeometryNode();
    CHECK_NULL_VOID(parentItemGeometryNode);
    auto menuItemSize = parentItemGeometryNode->GetFrameSize();
    auto pipeline = parentItem->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto selectTheme = pipeline ? pipeline->GetTheme<SelectTheme>() : nullptr;
    float contentPadding = selectTheme ? -static_cast<float>(selectTheme->GetMenuPadding().ConvertToPx()) : 0.0f;
    auto position = parentItem->GetPaintRectOffset(false, true) + OffsetF(menuItemSize.Width(), contentPadding);
    auto pipelineContext = parentItem->GetContextWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    auto isContainerModal = pipelineContext->GetWindowModal() == WindowModal::CONTAINER_MODAL;
    if ((!canExpandCurrentWindow_) && isContainerModal) {
        auto newOffsetX = static_cast<float>(CONTAINER_BORDER_WIDTH.ConvertToPx());
        auto newOffsetY = static_cast<float>(pipelineContext->GetCustomTitleHeight().ConvertToPx()) +
                          static_cast<float>(CONTAINER_BORDER_WIDTH.ConvertToPx());
        position -= OffsetF(newOffsetX, newOffsetY);
    }
    if (layoutWrapper != nullptr) {
        auto menuLayoutProperty = layoutWrapper->GetLayoutProperty();
        CHECK_NULL_VOID(menuLayoutProperty);
        auto layoutDirection = menuLayoutProperty->GetNonAutoLayoutDirection();
        if (layoutDirection == TextDirection::RTL) {
            float leftSpace = position.GetX() - menuItemSize.Width();
            position = OffsetF(wrapperSize_.Width() - leftSpace, position.GetY());
        }
    }
    auto childMenuSize = GetMeasureSize(layoutWrapper, childConstraint);
    float maxSizeHeight = NeedUpdateMaxHeight(childMenuSize, position, menuItemSize, layoutWrapper);
    childConstraint.maxSize.SetHeight(maxSizeHeight);
}

float MenuLayoutAlgorithm::NeedUpdateMaxHeight(
    const SizeF& size, OffsetF position, const SizeF& menuItemSize, LayoutWrapper* layoutWrapper)
{
    float yMin = std::max(1.0f, static_cast<float>(wrapperRect_.Top()) + paddingTop_);
    float yMax = static_cast<float>(wrapperRect_.Bottom()) - paddingBottom_;
    float maxSizeHeight = yMax - yMin;
    float wrapperWidth = wrapperSize_.Width();
    float rightSpace = wrapperWidth - position.GetX() - paddingEnd_;
    float leftSpace = position.GetX() - menuItemSize.Width() - paddingStart_;
    if (layoutWrapper != nullptr) {
        auto menuLayoutProperty = layoutWrapper->GetLayoutProperty();
        CHECK_NULL_RETURN(menuLayoutProperty, maxSizeHeight);
        auto layoutDirection = menuLayoutProperty->GetNonAutoLayoutDirection();
        if (layoutDirection == TextDirection::RTL) {
            rightSpace = position.GetX() - menuItemSize.Width();
            leftSpace = wrapperWidth - position.GetX();
        }
    }
    if (rightSpace >= size.Width()) {
        position.SetX(std::clamp(position.GetX(), paddingStart_, wrapperSize_.Width() - size.Width() - paddingEnd_));
        maxSizeHeight = GetCurrentPosition(
            position, size, position.GetX() - size.Width() - menuItemSize.Width(), leftSpace >= size.Width());
        return maxSizeHeight;
    }
    if (leftSpace >= size.Width()) {
        position.SetX(std::clamp(position.GetX() - size.Width() - menuItemSize.Width(), paddingStart_,
            wrapperSize_.Width() - size.Width() - paddingEnd_));
        maxSizeHeight = GetOthersPosition(position, size);
        return maxSizeHeight;
    }
    if (size.Width() < wrapperWidth) {
        position.SetX(std::clamp(wrapperWidth - size.Width() - paddingEnd_, paddingStart_,
            wrapperSize_.Width() - size.Width() - paddingEnd_));
        maxSizeHeight = GetOthersPosition(position, size);
        return maxSizeHeight;
    }
    return maxSizeHeight;
}

float MenuLayoutAlgorithm::GetCurrentPosition(OffsetF& position, const SizeF& size, float flip, bool widthEnough)
{
    float yMin = std::max(1.0f, static_cast<float>(wrapperRect_.Top()) + paddingTop_);
    float yMax = static_cast<float>(wrapperRect_.Bottom()) - paddingBottom_;
    float maxSizeHeight = yMax - yMin;
    position.SetX(std::clamp(position.GetX(), paddingStart_, wrapperSize_.Width() - size.Width() - paddingEnd_));
    flip = std::clamp(flip, paddingStart_, wrapperSize_.Width() - size.Width() - paddingEnd_);
    NG::OffsetF currentPosition = { position.GetX(), position.GetY() };
    NG::OffsetF flipPosition = { flip, position.GetY() };
    if (CheckFitScreen(currentPosition, size)) {
        return maxSizeHeight;
    }
    if (!widthEnough) {
        maxSizeHeight = MenuVerticalPanHeight(currentPosition, size);
        return maxSizeHeight;
    }
    if (CheckFitScreen(flipPosition, size)) {
        return maxSizeHeight;
    }
    if (!CheckHorizontalRange(currentPosition, size)) {
        maxSizeHeight = MenuVerticalPanHeight(currentPosition, size);
        return maxSizeHeight;
    }
    if (!CheckHorizontalRange(flipPosition, size)) {
        maxSizeHeight = MenuVerticalPanHeight(flipPosition, size);
        return maxSizeHeight;
    }
    maxSizeHeight = MenuVerticalPanHeight(currentPosition, size);
    return maxSizeHeight;
}

float MenuLayoutAlgorithm::GetOthersPosition(OffsetF& position, const SizeF& size)
{
    float yMin = std::max(1.0f, static_cast<float>(wrapperRect_.Top()) + paddingTop_);
    float yMax = static_cast<float>(wrapperRect_.Bottom()) - paddingBottom_;
    float maxSizeHeight = yMax - yMin;
    if (CheckFitScreen(position, size)) {
        return maxSizeHeight;
    }
    maxSizeHeight = MenuVerticalPanHeight(position, size);
    return maxSizeHeight;
}

bool MenuLayoutAlgorithm::CheckFitScreen(const OffsetF& position, const SizeF& size)
{
    float yMax = static_cast<float>(wrapperRect_.Bottom()) - paddingBottom_;
    if (position.GetY() + size.Height() > yMax) {
        return false;
    }
    if (!CheckHorizontalRange(position, size)) {
        return true;
    } else {
        return !CheckVerticalRange(position, size);
    }
}

float MenuLayoutAlgorithm::MenuVerticalPanHeight(const OffsetF& position, const SizeF& size)
{
    float yMin = std::max(1.0f, static_cast<float>(wrapperRect_.Top()) + paddingTop_);
    float yMax = static_cast<float>(wrapperRect_.Bottom()) - paddingBottom_;
    float maxSizeHeight = yMax - yMin;
    if (!CheckHorizontalRange(position, size)) {
        return maxSizeHeight;
    }
    float targetSpace = propTargetSpace_.value().ConvertToPx();
    float topSpace = propTargetOffset_.value().GetY() - targetSpace - yMin;
    float bottomSpace = yMax - propTargetOffset_.value().GetY() - targetSpace - proptargetSize_.value().Height();
    TargetSpaceReason reason = CheckHeightReason(position, size);
    switch (reason) {
        case TargetSpaceReason::TOP:
            maxSizeHeight = topSpace;
            break;
        case TargetSpaceReason::MIDDLE:
            maxSizeHeight = bottomSpace;
            break;
        case TargetSpaceReason::BOTTOM:
            maxSizeHeight = bottomSpace;
            break;
        default:
            break;
    }
    return maxSizeHeight;
}

TargetSpaceReason MenuLayoutAlgorithm::CheckHeightReason(const OffsetF& position, const SizeF& size)
{
    float targetSpace = propTargetSpace_.value().ConvertToPx();
    float targetTop = propTargetOffset_.value().GetY() - targetSpace;
    float targetBottom = propTargetOffset_.value().GetY() + proptargetSize_.value().Height() + targetSpace;
    if (position.GetY() < targetTop - targetSpace) {
        return TargetSpaceReason::TOP;
    }
    if (position.GetY() >= targetBottom + targetSpace) {
        return TargetSpaceReason::BOTTOM;
    }
    if (position.GetY() >= targetTop - targetSpace && position.GetY() < targetBottom + targetSpace) {
        return TargetSpaceReason::MIDDLE;
    }
    return TargetSpaceReason::TOP;
}

bool MenuLayoutAlgorithm::CheckHorizontalRange(const OffsetF& position, const SizeF& size)
{
    float targetSpace = propTargetSpace_.value().ConvertToPx();
    float targetLeft = propTargetOffset_.value().GetX() - targetSpace;
    float targetRight = propTargetOffset_.value().GetX() + proptargetSize_.value().Width() + targetSpace;
    float itemLeft = position.GetX();
    float itemRight = position.GetX() + size.Width();
    if (itemLeft > targetRight || itemRight < targetLeft) {
        return false;
    }
    return true;
}

bool MenuLayoutAlgorithm::CheckVerticalRange(const OffsetF& position, const SizeF& size)
{
    float targetSpace = propTargetSpace_.value().ConvertToPx();
    float targetTop = propTargetOffset_.value().GetY() - targetSpace;
    float targetBottom = propTargetOffset_.value().GetY() + proptargetSize_.value().Height() + targetSpace;
    float itemTop = position.GetY();
    float itemBottom = position.GetY() + size.Height();
    if (itemTop > targetBottom || itemBottom < targetTop) {
        return false;
    }
    return true;
}

float MenuLayoutAlgorithm::CalcSubMenuMaxHeightTargetSpace(
    LayoutConstraintF& childConstraint, RefPtr<FrameNode> parentItem)
{
    if (!propTargetOffset_.has_value()) {
        return 0.0f;
    }
    auto space = canExpandCurrentWindow_ ? MIN_MENU_HEIGHT_HAD : MIN_MENU_HEIGHT;
    float targetSpace = propTargetSpace_.value().ConvertToPx();
    float yMin = std::max(1.0f, static_cast<float>(wrapperRect_.Top()) + paddingTop_);
    float topY = propTargetOffset_.value().GetY() - targetSpace - space.ConvertToPx();
    float subMenuMaxHeight = childConstraint.maxSize.Height();
    return std::min(topY - yMin, subMenuMaxHeight);
}

OffsetF MenuLayoutAlgorithm::GetTargetSpacePosition(const SizeF& childSize, bool didNeedArrow)
{
    // add space between arrow and targetNode
    OffsetF bottomPosition = OffsetF(targetOffset_.GetX() + (targetSize_.Width() - childSize.Width()) / 2.0,
        targetOffset_.GetY() + targetSize_.Height() + targetSpace_);
    OffsetF topPosition = OffsetF(targetOffset_.GetX() + (targetSize_.Width() - childSize.Width()) / 2.0,
        targetOffset_.GetY() - childSize.Height() - targetSpace_);
    OffsetF defaultPosition = GetTargetSpaceDefaultPosition(topPosition, bottomPosition);

    OffsetF childPosition;
    OffsetF position = defaultPosition;
    auto positionOffset = positionOffset_;
    std::vector<Placement> currentPlacementStates = PLACEMENT_STATES.find(Placement::BOTTOM_LEFT)->second;
    auto it = PLACEMENT_STATES.find(placement_);
    if (it != PLACEMENT_STATES.end()) {
        currentPlacementStates = it->second;
    }
    size_t step = ALIGNMENT_STEP_OFFSET;
    if (placement_ <= Placement::BOTTOM) {
        step += 1;
    }
    for (size_t i = 0, len = currentPlacementStates.size(); i < len; i++) {
        placement_ = currentPlacementStates[i];
        if (placement_ == Placement::NONE) {
            break;
        }
        if (i >= step) {
            positionOffset_ = OffsetF(0.0f, 0.0f);
        }
        childPosition = GetPositionWithPlacement(childSize, topPosition, bottomPosition);
        position = FitToTargetSpaceScreen(childPosition, childSize, didNeedArrow);
        if (NearEqual(position, OffsetF(0.0f, 0.0f))) {
            continue;
        }
        break;
    }
    if (placement_ == Placement::NONE) {
        position = GetAdjustTargetSpacePosition(currentPlacementStates, step, childSize, topPosition, bottomPosition);
        if (NearEqual(position, OffsetF(0.0f, 0.0f))) {
            position = GetTargetSpaceDefaultPosition(topPosition, bottomPosition);
        }
    }
    positionOffset_ = positionOffset;
    arrowPlacement_ = placement_;
    return position;
}

OffsetF MenuLayoutAlgorithm::GetTargetSpaceDefaultPosition(const OffsetF& topPosition, const OffsetF& bottomPosition)
{
    float targetSpace = propTargetSpace_.value().ConvertToPx();
    float yMin = std::max(1.0f, static_cast<float>(wrapperRect_.Top()) + paddingTop_);
    float yMax = static_cast<float>(wrapperRect_.Bottom()) - paddingBottom_;
    float topSpace = targetOffset_.GetY() - targetSpace - yMin;
    float bottomSpace = yMax - targetOffset_.GetY() - targetSpace - targetSize_.Height();
    auto position = topSpace > bottomSpace
                        ? OffsetF(topPosition.GetX(), yMin)
                        : OffsetF(bottomPosition.GetX(), targetOffset_.GetY() + targetSpace + targetSize_.Height());
    return position;
}

OffsetF MenuLayoutAlgorithm::FitToTargetSpaceScreen(const OffsetF& position, const SizeF& childSize, bool didNeedArrow)
{
    OffsetF afterPosition;
    OffsetF afterOffsetPosition;
    auto originPosition = position;

    // add space between targetNode and menu using default value or user-set offset
    if (NearEqual(positionOffset_, OffsetF(0.0f, 0.0f))) {
        afterOffsetPosition = AddCustomTargetSpace(originPosition);
    } else {
        afterPosition = AddCustomTargetSpace(originPosition);
        afterOffsetPosition = AddAdjustOffset(afterPosition);
    }

    if (!CheckPosition(afterOffsetPosition, childSize) || flag_) {
        if (!CheckPosition(afterPosition, childSize) || flag_) {
            flag_ = false;
            return OffsetF(0.0f, 0.0f);
        } else {
            return afterPosition;
        }
        flag_ = false;
        return OffsetF(0.0f, 0.0f);
    }

    return afterOffsetPosition;
}

OffsetF MenuLayoutAlgorithm::GetAdjustTargetSpacePosition(std::vector<Placement>& currentPlacementStates, size_t step,
    const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition)
{
    float targetSpace = propTargetSpace_.value().ConvertToPx();
    OffsetF childPosition;
    OffsetF position;
    size_t len = currentPlacementStates.size();
    for (size_t i = 0; i < len;) {
        placement_ = currentPlacementStates[i];
        if (placement_ == Placement::NONE) {
            break;
        }
        childPosition = GetPositionWithPlacement(childSize, topPosition, bottomPosition);
        position = AdjustPosition(childPosition, childSize.Width(), childSize.Height(), targetSpace);
        if (!NearEqual(position, OffsetF(0.0f, 0.0f))) {
            break;
        }
        if (len - i <= step) {
            break;
        }
        i += step;
    }
    return position;
}

OffsetF MenuLayoutAlgorithm::AddCustomTargetSpace(const OffsetF& position)
{
    auto x = position.GetX();
    auto y = position.GetY();
    float targetSpace = propTargetSpace_.value().ConvertToPx();
    switch (placement_) {
        case Placement::BOTTOM_LEFT:
        case Placement::BOTTOM_RIGHT:
        case Placement::BOTTOM: {
            y += targetSpace;
            break;
        }
        case Placement::TOP_LEFT:
        case Placement::TOP_RIGHT:
        case Placement::TOP: {
            y -= targetSpace;
            break;
        }
        case Placement::RIGHT_TOP:
        case Placement::RIGHT_BOTTOM:
        case Placement::RIGHT: {
            x += targetSpace;
            break;
        }
        case Placement::LEFT_TOP:
        case Placement::LEFT_BOTTOM:
        case Placement::LEFT: {
            x -= targetSpace;
            break;
        }
        default: {
            y += targetSpace;
            break;
        }
    }
    return OffsetF(x, y);
}

OffsetF MenuLayoutAlgorithm::AddAdjustOffset(const OffsetF& position)
{
    auto x = position.GetX();
    auto y = position.GetY();
    switch (placement_) {
        case Placement::BOTTOM_LEFT:
        case Placement::BOTTOM_RIGHT:
        case Placement::BOTTOM: {
            x += positionOffset_.GetX();
            y += positionOffset_.GetY();
            y = std::max(targetOffset_.GetY() + targetSize_.Height(), y);
            break;
        }
        case Placement::TOP_LEFT:
        case Placement::TOP_RIGHT:
        case Placement::TOP: {
            x += positionOffset_.GetX();
            y -= positionOffset_.GetY();
            y = std::min(targetOffset_.GetY(), y);
            break;
        }
        case Placement::RIGHT_TOP:
        case Placement::RIGHT_BOTTOM:
        case Placement::RIGHT: {
            x += positionOffset_.GetX();
            x = std::max(targetOffset_.GetX() + targetSize_.Width(), x);
            y += positionOffset_.GetY();
            break;
        }
        case Placement::LEFT_TOP:
        case Placement::LEFT_BOTTOM:
        case Placement::LEFT: {
            x -= positionOffset_.GetX();
            x = std::min(targetOffset_.GetX(), x);
            y += positionOffset_.GetY();
            break;
        }
        default: {
            x += positionOffset_.GetX();
            y += positionOffset_.GetY();
            break;
        }
    }
    return OffsetF(x, y);
}

Placement MenuLayoutAlgorithm::GetPlacementWithItem(RefPtr<FrameNode> parentItem)
{
    CHECK_NULL_RETURN(parentItem, Placement::NONE);
    auto parentPattern = parentItem->GetPattern<MenuItemPattern>();
    CHECK_NULL_RETURN(parentPattern, Placement::NONE);
    auto parentMenu = parentPattern->GetMenu(true);
    CHECK_NULL_RETURN(parentMenu, Placement::NONE);
    auto parentMenuPattern = parentMenu->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(parentMenuPattern, Placement::NONE);
    auto parentPlacement = parentMenuPattern->GetLastPlacement().value_or(Placement::NONE);
    return parentPlacement;
}

SizeF MenuLayoutAlgorithm::GetMeasureSize(LayoutWrapper* layoutWrapper, LayoutConstraintF& constraint)
{
    SizeF childMenuSize;
    float idealHeight = 0.0f;
    float idealWidth = 0.0f;
    std::list<RefPtr<LayoutWrapper>> builderChildList;
    CHECK_NULL_RETURN(layoutWrapper, childMenuSize);
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        child->Measure(constraint);
        auto childSize = child->GetGeometryNode()->GetMarginFrameSize();
        idealHeight += childSize.Height();
        idealWidth = std::max(idealWidth, childSize.Width());
    }
    childMenuSize.SetHeight(idealHeight);
    childMenuSize.SetWidth(idealWidth);
    return childMenuSize;
}
}