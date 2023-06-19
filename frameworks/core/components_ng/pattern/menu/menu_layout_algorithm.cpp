/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include <optional>
#include <vector>

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/memory/referenced.h"
#include "base/subwindow/subwindow_manager.h"
#include "base/utils/utils.h"
#include "core/common/ace_engine.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components/common/properties/placement.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"
#include "core/pipeline/pipeline_base.h"
#include "core/pipeline_ng/pipeline_context.h"
namespace OHOS::Ace::NG {

namespace {
constexpr uint32_t MIN_GRID_COUNTS = 2;
constexpr uint32_t GRID_COUNTS_4 = 4;
constexpr uint32_t GRID_COUNTS_6 = 6;
constexpr uint32_t GRID_COUNTS_8 = 8;
constexpr uint32_t GRID_COUNTS_12 = 12;
constexpr int32_t PLATFORM_VERSION_TEN = 10;

uint32_t GetMaxGridCounts(const RefPtr<GridColumnInfo>& columnInfo)
{
    CHECK_NULL_RETURN(columnInfo, GRID_COUNTS_8);
    auto currentColumns = columnInfo->GetParent()->GetColumns();
    auto maxGridCounts = GRID_COUNTS_8;
    switch (currentColumns) {
        case GRID_COUNTS_4:
            maxGridCounts = GRID_COUNTS_4;
            break;
        case GRID_COUNTS_8:
            maxGridCounts = GRID_COUNTS_6;
            break;
        case GRID_COUNTS_12:
            maxGridCounts = GRID_COUNTS_8;
            break;
        default:
            break;
    }
    return maxGridCounts;
}
} // namespace

MenuLayoutAlgorithm::MenuLayoutAlgorithm(int32_t id, const std::string& tag) : targetNodeId_(id), targetTag_(tag)
{
    placementFuncMap_[Placement::TOP] = &MenuLayoutAlgorithm::GetPositionWithPlacementTop;
    placementFuncMap_[Placement::TOP_LEFT] = &MenuLayoutAlgorithm::GetPositionWithPlacementTopLeft;
    placementFuncMap_[Placement::TOP_RIGHT] = &MenuLayoutAlgorithm::GetPositionWithPlacementTopRight;
    placementFuncMap_[Placement::BOTTOM] = &MenuLayoutAlgorithm::GetPositionWithPlacementBottom;
    placementFuncMap_[Placement::BOTTOM_LEFT] = &MenuLayoutAlgorithm::GetPositionWithPlacementBottomLeft;
    placementFuncMap_[Placement::BOTTOM_RIGHT] = &MenuLayoutAlgorithm::GetPositionWithPlacementBottomRight;
    placementFuncMap_[Placement::LEFT] = &MenuLayoutAlgorithm::GetPositionWithPlacementLeft;
    placementFuncMap_[Placement::LEFT_TOP] = &MenuLayoutAlgorithm::GetPositionWithPlacementLeftTop;
    placementFuncMap_[Placement::LEFT_BOTTOM] = &MenuLayoutAlgorithm::GetPositionWithPlacementLeftBottom;
    placementFuncMap_[Placement::RIGHT] = &MenuLayoutAlgorithm::GetPositionWithPlacementRight;
    placementFuncMap_[Placement::RIGHT_TOP] = &MenuLayoutAlgorithm::GetPositionWithPlacementRightTop;
    placementFuncMap_[Placement::RIGHT_BOTTOM] = &MenuLayoutAlgorithm::GetPositionWithPlacementRightBottom;

    setHorizontal_ = { Placement::LEFT, Placement::LEFT_BOTTOM, Placement::LEFT_TOP,
        Placement::RIGHT, Placement::RIGHT_BOTTOM, Placement::RIGHT_TOP };
    setVertical_ = { Placement::TOP, Placement::TOP_LEFT, Placement::TOP_RIGHT,
        Placement::BOTTOM, Placement::BOTTOM_LEFT, Placement::BOTTOM_RIGHT };
}

MenuLayoutAlgorithm::~MenuLayoutAlgorithm()
{
    placementFuncMap_.clear();
    setHorizontal_.clear();
    setVertical_.clear();
}

void MenuLayoutAlgorithm::Initialize(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    // currently using click point as menu position
    auto props = AceType::DynamicCast<MenuLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(props);
    auto menuPattern = layoutWrapper->GetHostNode()->GetPattern<MenuPattern>();
    auto targetSize = props->GetTargetSizeValue(SizeF());
    position_ = props->GetMenuOffset().value_or(OffsetF());
    positionOffset_ = props->GetPositionOffset().value_or(OffsetF());
    LOGD("menu position_ = %{public}s, targetSize = %{public}s", position_.ToString().c_str(),
        targetSize.ToString().c_str());

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    if (!menuPattern->IsSelectOverlayExtensionMenu()) {
        margin_ = static_cast<float>(theme->GetOutPadding().ConvertToPx());
        optionPadding_ = margin_;
    } else {
        optionPadding_ = static_cast<float>(theme->GetOutPadding().ConvertToPx());
    }

    auto constraint = props->GetLayoutConstraint();
    auto wrapperIdealSize =
        CreateIdealSize(constraint.value(), Axis::FREE, props->GetMeasureType(MeasureType::MATCH_PARENT), true);
    wrapperSize_ = wrapperIdealSize;
    if (menuPattern->IsSelectOverlayExtensionMenu()) {
        topSpace_ = 0.0f;
        bottomSpace_ = constraint->maxSize.Height() - position_.GetY();
        leftSpace_ = Infinity<float>();
    } else {
        topSpace_ = position_.GetY() - targetSize.Height() - margin_ * 2.0f;
        bottomSpace_ = wrapperSize_.Height() - position_.GetY() - margin_ * 2.0f;
        leftSpace_ = position_.GetX();
        rightSpace_ = wrapperSize_.Width() - leftSpace_;
    }

    placement_ = props->GetMenuPlacement().value_or(Placement::BOTTOM);
    auto context = GetCurrentPipelineContext();
    CHECK_NULL_VOID(context);
    auto stageManager = context->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    auto page = stageManager->GetLastPage();
    CHECK_NULL_VOID(page);
    pageOffset_ = page->GetOffsetRelativeToWindow();
    topSpace_ -= pageOffset_.GetY();
    leftSpace_ -= pageOffset_.GetX();
}

// Called to perform layout render node and child.
void MenuLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    // initialize screen size and menu position
    CHECK_NULL_VOID(layoutWrapper);
    Initialize(layoutWrapper);

    auto menuLayoutProperty = AceType::DynamicCast<MenuLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(menuLayoutProperty);
    const auto& constraint = menuLayoutProperty->GetLayoutConstraint();
    if (!constraint) {
        LOGE("fail to measure menu due to layoutConstraint is nullptr");
        return;
    }
    auto idealSize = CreateIdealSize(
        constraint.value(), Axis::VERTICAL, menuLayoutProperty->GetMeasureType(MeasureType::MATCH_CONTENT), true);
    const auto& padding = menuLayoutProperty->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, idealSize);

    // calculate menu main size
    auto childConstraint = CreateChildConstraint(layoutWrapper);
    float idealHeight = 0.0f;
    float idealWidth = 0.0f;
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        child->Measure(childConstraint);
        auto childSize = child->GetGeometryNode()->GetMarginFrameSize();
        LOGD("child finish measure, child %{public}s size = %{public}s", child->GetHostTag().c_str(),
            child->GetGeometryNode()->GetMarginFrameSize().ToString().c_str());
        idealHeight += childSize.Height();
        idealWidth = std::max(idealWidth, childSize.Width());
    }
    idealSize.SetHeight(idealHeight);
    idealSize.SetWidth(idealWidth);
    AddPaddingToSize(padding, idealSize);

    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    LOGD("finish measure, menu size = %{public}f x %{public}f", idealSize.Width(), idealSize.Height());
    geometryNode->SetFrameSize(idealSize);
}

void MenuLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto menuProp = DynamicCast<MenuLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(menuProp);
    if (!targetTag_.empty()) {
        InitTargetSizeAndPosition(menuProp);
    }

    auto menuNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);

    if (!menuPattern->IsSelectOverlayExtensionMenu()) {
        auto geometryNode = layoutWrapper->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        auto size = geometryNode->GetMarginFrameSize();
        bool didNeedArrow = GetIfNeedArrow(layoutWrapper, size);
        if (menuPattern->IsSelectMenu()) {
            ComputeMenuPositionByAlignType(menuProp, size);
        }
        auto menuPosition = MenuLayoutAvoidAlgorithm(menuProp, menuPattern, size);
        arrowPosition_ = GetArrowPositionWithPlacement(size);
        if (didNeedArrow && arrowPlacement_ != Placement::NONE) {
            LayoutArrow(layoutWrapper);
        }
        if (menuPattern->IsSelectMenu()) {
            auto offset = ComputeMenuPositionByOffset(menuProp, geometryNode);
            menuPosition += offset;
            position_ = menuPosition;
            menuPosition = MenuLayoutAvoidAlgorithm(menuProp, menuPattern, size);
            auto pipeline = PipelineContext::GetCurrentContext();
            if (pipeline->GetMinPlatformVersion() >= PLATFORM_VERSION_TEN && pipeline->GetIsAppWindow() &&
                pipeline->GetIsLayoutFullScreen()) {
                menuPosition += pageOffset_ * 2;
            }
        }
        LOGD("Menu layout, offset = %{public}s", menuPosition.ToString().c_str());
        geometryNode->SetFrameOffset(menuPosition);
    }

    // translate each option by the height of previous options
    OffsetF translate;
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        child->GetGeometryNode()->SetMarginFrameOffset(translate);
        child->Layout();
        translate += OffsetF(0, child->GetGeometryNode()->GetFrameSize().Height());
    }

    if (menuPattern->IsContextMenu()) {
        std::vector<Rect> rects;
        auto frameRect = layoutWrapper->GetGeometryNode()->GetFrameRect();
        auto rect = Rect(frameRect.GetX(), frameRect.GetY(), frameRect.Width(), frameRect.Height());
        rects.emplace_back(rect);
        SubwindowManager::GetInstance()->SetHotAreas(rects);
    }
}

void MenuLayoutAlgorithm::LayoutArrow(const LayoutWrapper* layoutWrapper)
{
    auto paintProperty = GetPaintProperty(layoutWrapper);
    CHECK_NULL_VOID(paintProperty);
    paintProperty->UpdateArrowPosition(arrowPosition_);
    paintProperty->UpdateArrowPlacement(arrowPlacement_);
}

RefPtr<MenuPaintProperty> MenuLayoutAlgorithm::GetPaintProperty(const LayoutWrapper* layoutWrapper)
{
    auto menuNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(menuNode, nullptr);
    auto paintProperty = menuNode->GetPaintProperty<MenuPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, nullptr);
    return paintProperty;
}

bool MenuLayoutAlgorithm::GetIfNeedArrow(const LayoutWrapper* layoutWrapper, const SizeF& menuSize)
{
    CHECK_NULL_RETURN(layoutWrapper, false);
    auto menuNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(menuNode, false);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(menuPattern, false);
    auto menuProp = DynamicCast<MenuLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(menuProp, false);
    auto paintProperty = GetPaintProperty(layoutWrapper);
    CHECK_NULL_RETURN(paintProperty, false);
    propNeedArrow_ = paintProperty->GetEnableArrow().value_or(false);

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto selectThemePtr = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(selectThemePtr, false);

    if (!propNeedArrow_) {
        return false;
    }

    propArrowOffset_ = paintProperty->GetArrowOffset().value_or(Dimension(0));
    menuRadius_ = selectThemePtr->GetMenuBorderRadius().ConvertToPx();
    arrowMinLimit_ = menuRadius_ + ARROW_WIDTH.ConvertToPx() / 2.0;
    arrowWidth_ = ARROW_WIDTH.ConvertToPx();
    auto targetSpaceReal = TARGET_SPACE.ConvertToPx();

    if (setHorizontal_.find(placement_) != setHorizontal_.end()) {
        if (menuSize.Height() >= menuRadius_ * 2 + arrowWidth_) {
            arrowInMenu_ = true;
            targetSpace_ = targetSpaceReal;
        }
    }

    if (setVertical_.find(placement_) != setVertical_.end()) {
        if (menuSize.Width() >= menuRadius_ * 2 + arrowWidth_) {
            arrowInMenu_ = true;
            targetSpace_ = targetSpaceReal;
        }
    }

    bool needArrow = menuPattern->IsContextMenu() && !targetTag_.empty() && arrowInMenu_;
    if (needArrow) {
        if (!menuProp->GetMenuPlacement().has_value()) {
            menuProp->UpdateMenuPlacement(Placement::TOP);
        }
    }
    return needArrow;
}

void MenuLayoutAlgorithm::UpdatePropArrowOffset()
{
    if (propArrowOffset_.IsValid()) {
        if (propArrowOffset_.Unit() == DimensionUnit::PERCENT) {
            propArrowOffset_.SetValue(std::clamp(propArrowOffset_.Value(), 0.0, 1.0));
        }
        return;
    }
    switch (arrowPlacement_) {
        case Placement::LEFT:
        case Placement::RIGHT:
        case Placement::TOP:
        case Placement::BOTTOM:
            propArrowOffset_ = ARROW_HALF_PERCENT_VALUE;
            break;
        case Placement::TOP_LEFT:
        case Placement::BOTTOM_LEFT:
        case Placement::LEFT_TOP:
        case Placement::RIGHT_TOP:
            propArrowOffset_ = ARROW_ZERO_PERCENT_VALUE;
            break;
        case Placement::TOP_RIGHT:
        case Placement::BOTTOM_RIGHT:
        case Placement::LEFT_BOTTOM:
        case Placement::RIGHT_BOTTOM:
            propArrowOffset_ = ARROW_ONE_HUNDRED_PERCENT_VALUE;
            break;
        default:
            break;
    }
}

void MenuLayoutAlgorithm::UpdateArrowOffsetWithMenuLimit(const SizeF& menuSize)
{
    UpdatePropArrowOffset();

    if (setHorizontal_.find(arrowPlacement_) != setHorizontal_.end()) {
        if (menuSize.Height() >= menuRadius_ * 2 + arrowWidth_) {
            float range = menuSize.Height() - menuRadius_ * 2  - arrowWidth_;
            float tempOffset = propArrowOffset_.Unit() == DimensionUnit::PERCENT ? propArrowOffset_.Value() * range :
                propArrowOffset_.ConvertToPx();
            arrowOffset_ = std::clamp(tempOffset, 0.0f, range);
        }
    }

    if (setVertical_.find(arrowPlacement_) != setVertical_.end()) {
        if (menuSize.Width() >= menuRadius_ * 2 + arrowWidth_) {
            arrowInMenu_ = true;
            float range = menuSize.Width() - menuRadius_ * 2  - arrowWidth_;
            float tempOffset = propArrowOffset_.Unit() == DimensionUnit::PERCENT ? propArrowOffset_.Value() * range :
                propArrowOffset_.ConvertToPx();
            arrowOffset_ = std::clamp(tempOffset, 0.0f, range);
        }
    }
}

void MenuLayoutAlgorithm::ComputeMenuPositionByAlignType(
    const RefPtr<MenuLayoutProperty>& menuProp, const SizeF& menuSize)
{
    auto alignType = menuProp->GetAlignType().value_or(MenuAlignType::START);
    auto targetSize = menuProp->GetTargetSizeValue(SizeF());
    switch (alignType) {
        case MenuAlignType::CENTER: {
            position_.AddX(targetSize.Width() / 2.0f - menuSize.Width() / 2.0f);
            break;
        }
        case MenuAlignType::END: {
            position_.AddX(targetSize.Width() - menuSize.Width());
            break;
        }
        default:
            break;
    }
}

OffsetF MenuLayoutAlgorithm::ComputeMenuPositionByOffset(
    const RefPtr<MenuLayoutProperty>& menuProp, const RefPtr<GeometryNode>& geometryNode)
{
    CHECK_NULL_RETURN(menuProp, OffsetF(0, 0));
    CHECK_NULL_RETURN(geometryNode, OffsetF(0, 0));

    const auto& layoutConstraint = menuProp->GetLayoutConstraint();
    CHECK_NULL_RETURN(layoutConstraint, OffsetF(0, 0));
    auto menuAlignOffset = menuProp->GetOffset().value_or(
        DimensionOffset(Dimension(0, DimensionUnit::VP), Dimension(0, DimensionUnit::VP)));

    auto menuSize = geometryNode->GetFrameSize();
    auto menuTrimOffsetX =
        ConvertToPx(CalcLength(menuAlignOffset.GetX()), layoutConstraint->scaleProperty, menuSize.Width());
    auto menuTrimOffsetY =
        ConvertToPx(CalcLength(menuAlignOffset.GetY()), layoutConstraint->scaleProperty, menuSize.Height());
    OffsetF menuTrimOffset = OffsetF(menuTrimOffsetX.value_or(0.0), menuTrimOffsetY.value_or(0.0));
    return menuTrimOffset;
}

RefPtr<PipelineContext> MenuLayoutAlgorithm::GetCurrentPipelineContext()
{
    auto containerId = Container::CurrentId();
    RefPtr<PipelineContext> context;
    if (containerId >= MIN_SUBCONTAINER_ID) {
        auto parentContainerId = SubwindowManager::GetInstance()->GetParentContainerId(containerId);
        auto parentContainer = AceEngine::Get().GetContainer(parentContainerId);
        CHECK_NULL_RETURN(parentContainer, nullptr);
        context = DynamicCast<PipelineContext>(parentContainer->GetPipelineContext());
    } else {
        context = PipelineContext::GetCurrentContext();
    }
    return context;
}

OffsetF MenuLayoutAlgorithm::MenuLayoutAvoidAlgorithm(
    const RefPtr<MenuLayoutProperty>& menuProp, const RefPtr<MenuPattern>& menuPattern, const SizeF& size)
{
    CHECK_NULL_RETURN(menuProp, OffsetF(0, 0));
    CHECK_NULL_RETURN(menuPattern, OffsetF(0, 0));
    float x = 0.0f;
    float y = 0.0f;
    if (menuProp->GetMenuPlacement().has_value() && (targetSize_.Width() > 0.0 || targetSize_.Height() > 0.0)) {
        auto childOffset = GetChildPosition(size, menuProp, menuPattern->IsContextMenu());
        x = childOffset.GetX() + positionOffset_.GetX();
        y = childOffset.GetY() + positionOffset_.GetY();
        auto pipelineContext = GetCurrentPipelineContext();
        if (pipelineContext && menuPattern->IsContextMenu()) {
            auto windowGlobalRect = pipelineContext->GetDisplayWindowRectInfo();
            float windowsOffsetX = windowGlobalRect.GetOffset().GetX();
            float windowsOffsetY = windowGlobalRect.GetOffset().GetY();
            auto isContainerModal =
                pipelineContext->GetWindowModal() == WindowModal::CONTAINER_MODAL &&
                pipelineContext->GetWindowManager()->GetWindowMode() == WindowMode::WINDOW_MODE_FLOATING;
            OffsetF pageOffset;
            if (isContainerModal) {
                pageOffset = pageOffset_;
            }
            x += windowsOffsetX + pageOffset.GetX();
            y += windowsOffsetY + pageOffset.GetY();
            x = std::clamp(x, windowsOffsetX + pageOffset.GetX() + margin_,
                wrapperSize_.Width() - size.Width() - margin_ + windowsOffsetX + pageOffset.GetX());
            y = std::clamp(y, windowsOffsetY + pageOffset.GetY() + margin_,
                wrapperSize_.Height() - size.Height() - margin_ + windowsOffsetY + pageOffset.GetY());

            return OffsetF(x, y);
        }
    } else {
        x = HorizontalLayout(size, position_.GetX(), menuPattern->IsSelectMenu()) + positionOffset_.GetX();
        y = VerticalLayout(size, position_.GetY()) + positionOffset_.GetY();
        if (!menuPattern->IsContextMenu()) {
            x -= pageOffset_.GetX();
            y -= pageOffset_.GetY();
        }
    }
    x = std::clamp(x, margin_, wrapperSize_.Width() - size.Width() - margin_);
    y = std::clamp(y, margin_, wrapperSize_.Height() - size.Height() - margin_);

    return OffsetF(x, y);
}

void MenuLayoutAlgorithm::UpdateConstraintWidth(LayoutWrapper* layoutWrapper, LayoutConstraintF& constraint)
{
    RefPtr<GridColumnInfo> columnInfo;
    columnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::MENU);
    auto menuPattern = layoutWrapper->GetHostNode()->GetPattern<MenuPattern>();
    if (menuPattern && menuPattern->IsSelectOverlayExtensionMenu()) {
        columnInfo->GetParent()->BuildColumnWidth();
    } else {
        columnInfo->GetParent()->BuildColumnWidth(wrapperSize_.Width());
    }
    // set max width
    auto menuLayoutProperty = AceType::DynamicCast<MenuLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(menuLayoutProperty);
    const auto& padding = menuLayoutProperty->CreatePaddingAndBorder();
    auto maxHorizontalSpace = std::max(leftSpace_, rightSpace_) - 2.0f * padding.Width();
    auto maxGridWidth = static_cast<float>(columnInfo->GetWidth(GetMaxGridCounts(columnInfo)));
    auto maxWidth = std::min(maxHorizontalSpace, maxGridWidth);
    maxWidth = std::min(constraint.maxSize.Width(), maxWidth);
    constraint.maxSize.SetWidth(maxWidth);
    // set min width
    auto minWidth = static_cast<float>(columnInfo->GetWidth(MIN_GRID_COUNTS));
    if (minWidth > constraint.maxSize.Width()) {
        minWidth = constraint.maxSize.Width();
    }
    constraint.minSize.SetWidth(minWidth);
}

void MenuLayoutAlgorithm::UpdateConstraintHeight(LayoutWrapper* layoutWrapper, LayoutConstraintF& constraint)
{
    auto maxSpaceHeight = std::max(topSpace_, bottomSpace_);
    constraint.maxSize.SetHeight(maxSpaceHeight);
}

LayoutConstraintF MenuLayoutAlgorithm::CreateChildConstraint(LayoutWrapper* layoutWrapper)
{
    auto menuLayoutProperty = AceType::DynamicCast<MenuLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(menuLayoutProperty, LayoutConstraintF());

    auto childConstraint = menuLayoutProperty->CreateChildConstraint();
    UpdateConstraintWidth(layoutWrapper, childConstraint);
    UpdateConstraintHeight(layoutWrapper, childConstraint);
    UpdateConstraintBaseOnOptions(layoutWrapper, childConstraint);
    return childConstraint;
}

void MenuLayoutAlgorithm::UpdateConstraintBaseOnOptions(LayoutWrapper* layoutWrapper, LayoutConstraintF& constraint)
{
    auto menuPattern = layoutWrapper->GetHostNode()->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto options = menuPattern->GetOptions();
    if (options.empty()) {
        LOGD("options is empty, no need to update constraint.");
        return;
    }
    auto optionConstraint = constraint;
    optionConstraint.maxSize.MinusWidth(optionPadding_ * 2.0f);
    optionConstraint.minSize.MinusWidth(optionPadding_ * 2.0f);
    auto maxChildrenWidth = optionConstraint.minSize.Width();
    auto optionsLayoutWrapper = GetOptionsLayoutWrappper(layoutWrapper);
    for (const auto& optionWrapper : optionsLayoutWrapper) {
        optionWrapper->Measure(optionConstraint);
        auto childSize = optionWrapper->GetGeometryNode()->GetMarginFrameSize();
        maxChildrenWidth = std::max(maxChildrenWidth, childSize.Width());
    }
    if (menuPattern->IsSelectOverlayExtensionMenu()) {
        maxChildrenWidth = std::min(maxChildrenWidth, optionConstraint.maxSize.Width());
        UpdateOptionConstraint(optionsLayoutWrapper, maxChildrenWidth);
        constraint.minSize.SetWidth(maxChildrenWidth);
        return;
    }
    UpdateOptionConstraint(optionsLayoutWrapper, maxChildrenWidth);
    constraint.minSize.SetWidth(maxChildrenWidth + optionPadding_ * 2.0f);
}

std::list<RefPtr<LayoutWrapper>> MenuLayoutAlgorithm::GetOptionsLayoutWrappper(LayoutWrapper* layoutWrapper)
{
    std::list<RefPtr<LayoutWrapper>> optionsWrapper;
    auto scrollWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_RETURN(scrollWrapper, optionsWrapper);
    auto columnWrapper = scrollWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_RETURN(columnWrapper, optionsWrapper);
    optionsWrapper = columnWrapper->GetAllChildrenWithBuild();
    return optionsWrapper;
}

void MenuLayoutAlgorithm::UpdateOptionConstraint(std::list<RefPtr<LayoutWrapper>>& options, float width)
{
    for (const auto& option : options) {
        auto optionLayoutProps = option->GetLayoutProperty();
        CHECK_NULL_VOID(optionLayoutProps);
        optionLayoutProps->UpdateCalcMinSize(CalcSize(CalcLength(width), std::nullopt));
    }
}

// return vertical offset
float MenuLayoutAlgorithm::VerticalLayout(const SizeF& size, float position)
{
    float wrapperHeight = wrapperSize_.Height();
    // can put menu below click point
    if (bottomSpace_ >= size.Height()) {
        return position + margin_;
    }

    // put menu above click point
    if (topSpace_ >= size.Height()) {
        return topSpace_ - size.Height() + margin_ + pageOffset_.GetY();
    }

    // line up bottom of menu with bottom of the screen
    if (size.Height() < wrapperHeight) {
        return wrapperHeight - size.Height();
    }
    // can't fit in screen, line up with top of the screen
    return 0.0f;
}

// returns horizontal offset
float MenuLayoutAlgorithm::HorizontalLayout(const SizeF& size, float position, bool isSelectMenu)
{
    float wrapperWidth = wrapperSize_.Width();
    // can fit menu on the right side of position
    if (rightSpace_ >= size.Width()) {
        return position + margin_;
    }

    // fit menu on the left side
    if (!isSelectMenu && leftSpace_ >= size.Width()) {
        return position - size.Width();
    }

    // line up right side of menu with right boundary of the screen
    if (size.Width() < wrapperWidth) {
        return wrapperWidth - size.Width();
    }

    // can't fit in screen, line up with left side of the screen
    return 0.0f;
}

OffsetF MenuLayoutAlgorithm::GetPositionWithPlacement(
    const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition)
{
    OffsetF childPosition;

    auto func = placementFuncMap_.find(placement_);
    if (func != placementFuncMap_.end()) {
        auto placementFunc = func->second;
        if (placementFunc != nullptr) {
            childPosition = (this->*placementFunc)(childSize, topPosition, bottomPosition);
        } else {
            LOGE("Invalid Placement of menu layout.");
        }
    } else {
        LOGE("Invalid Placement of menu layout.");
    }

    return childPosition;
}

OffsetF MenuLayoutAlgorithm::GetArrowPositionWithPlacement(const SizeF& menuSize)
{
    UpdateArrowOffsetWithMenuLimit(menuSize);
    auto addArrowOffsetToArrowMin = arrowOffset_ + arrowMinLimit_;
    auto space_ = ARROW_HIGHT.ConvertToPx();
    OffsetF childPosition;
    switch (arrowPlacement_) {
        case Placement::TOP:
        case Placement::TOP_LEFT:
        case Placement::TOP_RIGHT:
            childPosition = OffsetF(addArrowOffsetToArrowMin, menuSize.Height() + space_);
            break;
        case Placement::BOTTOM:
        case Placement::BOTTOM_LEFT:
        case Placement::BOTTOM_RIGHT:
            childPosition = OffsetF(addArrowOffsetToArrowMin, -space_);
            break;
        case Placement::LEFT:
        case Placement::LEFT_TOP:
        case Placement::LEFT_BOTTOM:
            childPosition = OffsetF(menuSize.Width() + space_, addArrowOffsetToArrowMin);
            break;
        case Placement::RIGHT:
        case Placement::RIGHT_TOP:
        case Placement::RIGHT_BOTTOM:
            childPosition = OffsetF(-space_, addArrowOffsetToArrowMin);
            break;
        default:
            break;
    }
    return childPosition;
}

void MenuLayoutAlgorithm::InitTargetSizeAndPosition(const RefPtr<MenuLayoutProperty>& layoutProp)
{
    auto targetNode = FrameNode::GetFrameNode(targetTag_, targetNodeId_);
    CHECK_NULL_VOID(targetNode);
    auto geometryNode = targetNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    targetSize_ = geometryNode->GetFrameSize();
    auto pipelineContext = GetCurrentPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto isContainerModal = pipelineContext->GetWindowModal() == WindowModal::CONTAINER_MODAL &&
                            pipelineContext->GetWindowManager()->GetWindowMode() == WindowMode::WINDOW_MODE_FLOATING;
    targetOffset_ = targetNode->GetPaintRectOffset();
    if (isContainerModal) {
        auto newOffsetX = targetOffset_.GetX() - static_cast<float>(CONTAINER_BORDER_WIDTH.ConvertToPx()) -
                          static_cast<float>(CONTENT_PADDING.ConvertToPx());
        auto newOffsetY = targetOffset_.GetY() - static_cast<float>(CONTAINER_TITLE_HEIGHT.ConvertToPx());
        targetOffset_.SetX(newOffsetX);
        targetOffset_.SetY(newOffsetY);
    }
}

MenuLayoutAlgorithm::ErrorPositionType MenuLayoutAlgorithm::GetErrorPositionType(
    const OffsetF& childOffset, const SizeF& childSize)
{
    RectF validRegion = RectF(targetOffset_, targetSize_);
    RectF childRegion(childOffset, childSize);
    if (validRegion.IsInnerIntersectWith(childRegion)) {
        return ErrorPositionType::TOP_LEFT_ERROR;
    }
    return ErrorPositionType::NORMAL;
}

OffsetF MenuLayoutAlgorithm::FitToScreen(const OffsetF& fitPosition, const SizeF& childSize, bool isContextMenu)
{
    float x = fitPosition.GetX() + positionOffset_.GetX();
    float y = fitPosition.GetY() + positionOffset_.GetY();
    auto pipelineContext = GetCurrentPipelineContext();
    if (pipelineContext && isContextMenu) {
        auto windowGlobalRect = pipelineContext->GetDisplayWindowRectInfo();
        float windowsOffsetX = windowGlobalRect.GetOffset().GetX();
        float windowsOffsetY = windowGlobalRect.GetOffset().GetY();
        auto isContainerModal =
            pipelineContext->GetWindowModal() == WindowModal::CONTAINER_MODAL &&
            pipelineContext->GetWindowManager()->GetWindowMode() == WindowMode::WINDOW_MODE_FLOATING;
        OffsetF pageOffset;
        if (isContainerModal) {
            pageOffset = pageOffset_;
        }
        x += windowsOffsetX + pageOffset.GetX();
        y += windowsOffsetY + pageOffset.GetY();
        x = std::clamp(x, windowsOffsetX + pageOffset.GetX() + margin_,
            wrapperSize_.Width() - childSize.Width() - margin_ + windowsOffsetX + pageOffset.GetX());
        y = std::clamp(y, windowsOffsetY + pageOffset.GetY() + margin_,
            wrapperSize_.Height() - childSize.Height() - margin_ + windowsOffsetY + pageOffset.GetY());

        return OffsetF(x, y);
    }
    x = std::clamp(x, margin_, wrapperSize_.Width() - childSize.Width() - margin_);
    y = std::clamp(y, margin_, wrapperSize_.Height() - childSize.Height() - margin_);

    return OffsetF(x, y);
}

OffsetF MenuLayoutAlgorithm::GetChildPosition(
    const SizeF& childSize, const RefPtr<MenuLayoutProperty>& layoutProp, bool isContextMenu)
{
    OffsetF bottomPosition = OffsetF(targetOffset_.GetX() + (targetSize_.Width() - childSize.Width()) / 2.0,
        targetOffset_.GetY() + targetSize_.Height() + targetSpace_);
    OffsetF topPosition = OffsetF(targetOffset_.GetX() + (targetSize_.Width() - childSize.Width()) / 2.0,
        targetOffset_.GetY() - childSize.Height() - targetSpace_);

    OffsetF originOffset = GetPositionWithPlacement(childSize, topPosition, bottomPosition);
    OffsetF childPosition = originOffset;

    // Fit popup to screen range.
    auto fitOffset = FitToScreen(childPosition, childSize, isContextMenu);
    ErrorPositionType errorType = GetErrorPositionType(fitOffset, childSize);
    if (errorType == ErrorPositionType::NORMAL) {
        arrowPlacement_ = placement_;
        return childPosition;
    }
    auto placement = placement_;
    // If childPosition is error, adjust menu to bottom.
    if (placement_ != Placement::BOTTOM) {
        placement_ = Placement::BOTTOM;
        childPosition = GetPositionWithPlacement(childSize, topPosition, bottomPosition);
        fitOffset = FitToScreen(childPosition, childSize, isContextMenu);
        if (GetErrorPositionType(fitOffset, childSize) == ErrorPositionType::NORMAL) {
            placement_ = placement;
            arrowPlacement_ = Placement::BOTTOM;
            return childPosition;
        }
    }
    // If childPosition is error, adjust menu to top.
    if (placement_ != Placement::TOP) {
        placement_ = Placement::TOP;
        childPosition = GetPositionWithPlacement(childSize, topPosition, bottomPosition);
        fitOffset = FitToScreen(childPosition, childSize, isContextMenu);
        if (GetErrorPositionType(fitOffset, childSize) == ErrorPositionType::NORMAL) {
            placement_ = placement;
            arrowPlacement_ = Placement::TOP;
            return childPosition;
        }
    }
    placement_ = placement;
    arrowPlacement_ = Placement::NONE;
    return originOffset;
}

OffsetF MenuLayoutAlgorithm::GetPositionWithPlacementTop(
    const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition)
{
    return topPosition;
}

OffsetF MenuLayoutAlgorithm::GetPositionWithPlacementTopLeft(
    const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition)
{
    OffsetF childPosition;
    float marginRight = 0.0f;
    float marginBottom = 0.0f;
    childPosition = OffsetF(targetOffset_.GetX() - marginRight,
        targetOffset_.GetY() - childSize.Height() - marginBottom - targetSpace_);
    return childPosition;
}

OffsetF MenuLayoutAlgorithm::GetPositionWithPlacementTopRight(
    const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition)
{
    OffsetF childPosition;
    float marginBottom = 0.0f;
    float marginLeft = 0.0f;
    childPosition = OffsetF(targetOffset_.GetX() + targetSize_.Width() - childSize.Width() + marginLeft,
        targetOffset_.GetY() - childSize.Height() - targetSpace_ - marginBottom);
    return childPosition;
}

OffsetF MenuLayoutAlgorithm::GetPositionWithPlacementBottom(
    const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition)
{
    return bottomPosition;
}

OffsetF MenuLayoutAlgorithm::GetPositionWithPlacementBottomLeft(
    const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition)
{
    OffsetF childPosition;
    float marginRight = 0.0f;
    float marginTop = 0.0f;
    childPosition = OffsetF(targetOffset_.GetX() - marginRight,
        targetOffset_.GetY() + targetSize_.Height() + targetSpace_ + marginTop);
    return childPosition;
}

OffsetF MenuLayoutAlgorithm::GetPositionWithPlacementBottomRight(
    const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition)
{
    OffsetF childPosition;
    float marginTop = 0.0f;
    float marginLeft = 0.0f;
    childPosition = OffsetF(targetOffset_.GetX() + targetSize_.Width() - childSize.Width() + marginLeft,
        targetOffset_.GetY() + targetSize_.Height() + targetSpace_ + marginTop);
    return childPosition;
}

OffsetF MenuLayoutAlgorithm::GetPositionWithPlacementLeft(
    const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition)
{
    OffsetF childPosition;
    float marginRight = 0.0f;
    childPosition =
        OffsetF(targetOffset_.GetX() - targetSpace_ - childSize.Width() - marginRight,
            targetOffset_.GetY() + targetSize_.Height() / 2.0 - childSize.Height() / 2.0);
    return childPosition;
}

OffsetF MenuLayoutAlgorithm::GetPositionWithPlacementLeftTop(
    const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition)
{
    OffsetF childPosition;
    float marginRight = 0.0f;
    float marginBottom = 0.0f;
    childPosition =
        OffsetF(targetOffset_.GetX() - targetSpace_ - childSize.Width() - marginRight,
            targetOffset_.GetY() - marginBottom);
    return childPosition;
}

OffsetF MenuLayoutAlgorithm::GetPositionWithPlacementLeftBottom(
    const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition)
{
    OffsetF childPosition;
    float marginRight = 0.0f;
    float marginTop = 0.0f;
    childPosition =
        OffsetF(targetOffset_.GetX() - targetSpace_ - childSize.Width() - marginRight,
            targetOffset_.GetY() + targetSize_.Height() - childSize.Height() - marginTop);
    return childPosition;
}

OffsetF MenuLayoutAlgorithm::GetPositionWithPlacementRight(
    const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition)
{
    OffsetF childPosition;
    float marginLeft = 0.0f;
    childPosition =
        OffsetF(targetOffset_.GetX() + targetSize_.Width() + targetSpace_ + marginLeft,
            targetOffset_.GetY() + targetSize_.Height() / 2.0 - childSize.Height() / 2.0);
    return childPosition;
}

OffsetF MenuLayoutAlgorithm::GetPositionWithPlacementRightTop(
    const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition)
{
    OffsetF childPosition;
    float marginBottom = 0.0f;
    float marginLeft = 0.0f;
    childPosition =
        OffsetF(targetOffset_.GetX() + targetSize_.Width() + targetSpace_ + marginLeft,
            targetOffset_.GetY() - marginBottom);
    return childPosition;
}

OffsetF MenuLayoutAlgorithm::GetPositionWithPlacementRightBottom(
    const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition)
{
    OffsetF childPosition;
    float marginTop = 0.0f;
    float marginLeft = 0.0f;
    childPosition =
        OffsetF(targetOffset_.GetX() + targetSize_.Width() + targetSpace_ + marginLeft,
            targetOffset_.GetY() + targetSize_.Height() - childSize.Height() - marginTop);
    return childPosition;
}

} // namespace OHOS::Ace::NG
