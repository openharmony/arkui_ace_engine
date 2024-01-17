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
#include "base/geometry/ng/size_t.h"
#include "base/geometry/size.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/subwindow/subwindow_manager.h"
#include "base/utils/utils.h"
#include "core/common/ace_engine.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components/common/properties/placement.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/menu/preview/menu_preview_pattern.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_layout_property.h"
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
constexpr size_t ALIGNMENT_STEP_OFFSET = 2;
constexpr float HEIGHT_CONSTRAINT_FACTOR = 0.8;

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
        case MIN_GRID_COUNTS:
            maxGridCounts = MIN_GRID_COUNTS;
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

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto menuTheme = pipeline->GetTheme<NG::MenuTheme>();
    CHECK_NULL_VOID(menuTheme);
    previewScale_ = menuTheme->GetPreviewAfterAnimationScale();
    if (LessOrEqual(previewScale_, 0.0f)) {
        previewScale_ = 1.0f;
    }
}

MenuLayoutAlgorithm::~MenuLayoutAlgorithm()
{
    placementFuncMap_.clear();
    setHorizontal_.clear();
    setVertical_.clear();
}

void MenuLayoutAlgorithm::ModifyNormalPreviewMenuPortraitPlacement(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto props = AceType::DynamicCast<MenuLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(props);

    auto hasPlacement = props->GetMenuPlacement().has_value();
    if (placement_ == Placement::TOP_LEFT || placement_ == Placement::TOP || placement_ == Placement::TOP_RIGHT) {
        if (!hasPlacement) {
            placement_ = Placement::TOP_LEFT;
            props->UpdateMenuPlacement(placement_);
        }
    } else if (!hasPlacement) {
        placement_ = Placement::BOTTOM_LEFT;
        props->UpdateMenuPlacement(placement_);
    }
}

void MenuLayoutAlgorithm::ModifyNormalPreviewMenuPlacement(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto props = AceType::DynamicCast<MenuLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(props);

    auto hasPlacement = props->GetMenuPlacement().has_value();
    if (SystemProperties::GetDeviceOrientation() == DeviceOrientation::PORTRAIT) {
        ModifyNormalPreviewMenuPortraitPlacement(layoutWrapper);
    } else if (!hasPlacement) {
        placement_ = Placement::RIGHT_TOP;
        props->UpdateMenuPlacement(placement_);
    }
}

void MenuLayoutAlgorithm::ModifyPreviewMenuPlacement(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto props = AceType::DynamicCast<MenuLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(props);

    auto hasPlacement = props->GetMenuPlacement().has_value();
    if (SystemProperties::GetDeviceType() == DeviceType::PHONE) {
        ModifyNormalPreviewMenuPlacement(layoutWrapper);
    } else {
        if (!hasPlacement) {
            placement_ = Placement::RIGHT_TOP;
            props->UpdateMenuPlacement(placement_);
        }
    }
}

void MenuLayoutAlgorithm::Initialize(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    // currently using click point as menu position
    auto props = AceType::DynamicCast<MenuLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(props);
    auto menuNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    float scale = menuPattern->GetPreviewAfterAnimationScale();
    previewScale_ = LessOrEqual(scale, 0.0f) ? previewScale_ : scale;
    position_ = props->GetMenuOffset().value_or(OffsetF());
    positionOffset_ = props->GetPositionOffset().value_or(OffsetF());
    InitializePadding(layoutWrapper);
    InitWrapperRect(props, menuPattern);
    placement_ = props->GetMenuPlacement().value_or(Placement::BOTTOM_LEFT);
    ModifyPositionToWrapper(layoutWrapper, position_);
    if (!menuPattern->IsSelectOverlayExtensionMenu() && menuPattern->GetPreviewMode() != MenuPreviewMode::NONE) {
        ModifyPreviewMenuPlacement(layoutWrapper);
    }
    InitSpace(props, menuPattern);
}

void MenuLayoutAlgorithm::InitWrapperRect(
    const RefPtr<MenuLayoutProperty>& props, const RefPtr<MenuPattern>& menuPattern)
{
    auto constraint = props->GetLayoutConstraint();
    // has minus navgation bar height(AvoidAreaType.TYPE_NAVIGATION_INDICATOR)
    auto wrapperIdealSize =
        CreateIdealSize(constraint.value(), Axis::FREE, props->GetMeasureType(MeasureType::MATCH_PARENT), true);
    auto pipelineContext = GetCurrentPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto windowGlobalRect = pipelineContext->GetDisplayWindowRectInfo();
    wrapperRect_.SetRect(0, 0, wrapperIdealSize.Width(), wrapperIdealSize.Height());
    auto safeAreaManager = pipelineContext->GetSafeAreaManager();
    // system safeArea(AvoidAreaType.TYPE_SYSTEM) only include status bar,now the bottom is 0
    auto bottom = safeAreaManager->GetSystemSafeArea().bottom_.Length();
    auto top = safeAreaManager->GetSystemSafeArea().top_.Length();
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        if (hierarchicalParameters_) {
            // wrapperRect_= windowGlobalRect- dock -statusbar
            wrapperRect_ = pipelineContext->GetDisplayAvailableRect();
        } else {
            // wrapperIdealSize.Height = windowGlobalRect.Height()-navigation_indicator.height,no AR to avoid navigation
            wrapperRect_.SetRect(0, top, windowGlobalRect.Width(), windowGlobalRect.Height() - top - bottom);
        }
    }

    if (!menuPattern->IsSelectOverlayExtensionMenu() && menuPattern->GetPreviewMode() != MenuPreviewMode::NONE) {
        //  come from ModifyPreviewMenuPlacement
        if (NearEqual(wrapperIdealSize.Height(), windowGlobalRect.Height())) {
            wrapperRect_.SetRect(0, top, windowGlobalRect.Width(), windowGlobalRect.Height() - bottom);
        }
    }
    wrapperSize_ = SizeF(wrapperRect_.Width(), wrapperRect_.Height());
}

void MenuLayoutAlgorithm::InitSpace(const RefPtr<MenuLayoutProperty>& props, const RefPtr<MenuPattern>& menuPattern)
{
    auto constraint = props->GetLayoutConstraint();
    auto targetSize = props->GetTargetSizeValue(SizeF());
    if (menuPattern->IsSelectOverlayExtensionMenu()) {
        topSpace_ = 0.0f;
        bottomSpace_ = constraint->maxSize.Height() - position_.GetY();
        leftSpace_ = Infinity<float>();
    } else {
        if (props->GetMenuPlacement().has_value()) {
            auto targetSecurity = targetSecurity_;
            topSpace_ = std::max(0.0, targetOffset_.GetY() - targetSecurity - paddingTop_ - wrapperRect_.Top());
            bottomSpace_ = std::max(0.0,
                wrapperRect_.Bottom() - targetOffset_.GetY() - targetSize_.Height() - targetSecurity - paddingBottom_);
            if (NearZero(topSpace_) && NearZero(bottomSpace_)) {
                bottomSpace_ = wrapperRect_.Bottom() - position_.GetY() - paddingTop_;
            }
            leftSpace_ = std::max(0.0, wrapperRect_.Left() + targetOffset_.GetX() - paddingStart_ - targetSecurity);
            rightSpace_ = std::max(
                0.0, wrapperRect_.Right() - targetSize_.Width() - targetSecurity - paddingStart_ - paddingEnd_);
            if (NearZero(leftSpace_) && NearZero(rightSpace_)) {
                leftSpace_ = position_.GetX();
                rightSpace_ = wrapperRect_.Right() - leftSpace_;
            }
        } else {
            if (hierarchicalParameters_ || !Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
                topSpace_ = position_.GetY() - targetSize.Height() - paddingTop_ - wrapperRect_.Top();
                bottomSpace_ = wrapperRect_.Bottom() - position_.GetY() - paddingBottom_;
            } else {
                topSpace_ = position_.GetY() - wrapperRect_.Top() - paddingTop_;
                bottomSpace_ = wrapperRect_.Bottom() - position_.GetY() - paddingTop_;
            }
            leftSpace_ = position_.GetX() - paddingStart_;
            rightSpace_ = wrapperRect_.Right() - leftSpace_ - paddingEnd_;
        }
    }
}

void MenuLayoutAlgorithm::InitializePadding(LayoutWrapper* layoutWrapper)
{
    auto menuPattern = layoutWrapper->GetHostNode()->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    if (!menuPattern->IsSelectOverlayExtensionMenu()) {
        margin_ = static_cast<float>(theme->GetOutPadding().ConvertToPx());
        optionPadding_ = margin_;
        paddingStart_ = static_cast<float>(theme->GetDefaultPaddingStart().ConvertToPx());
        paddingEnd_ = static_cast<float>(theme->GetDefaultPaddingEnd().ConvertToPx());
        paddingTop_ = static_cast<float>(theme->GetDefaultPaddingTop().ConvertToPx());
        paddingBottom_ = static_cast<float>(theme->GetDefaultPaddingBottomFixed().ConvertToPx());
    } else {
        optionPadding_ = static_cast<float>(theme->GetOutPadding().ConvertToPx());
    }
}

void MenuLayoutAlgorithm::InitializePaddingAPI11(LayoutWrapper* layoutWrapper)
{
    auto menuNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);

    if (!menuPattern->IsSelectOverlayExtensionMenu() && !hierarchicalParameters_) {
        margin_ = static_cast<float>(theme->GetOutPadding().ConvertToPx());
        optionPadding_ = margin_;
        paddingStart_ = static_cast<float>(theme->GetMaxPaddingStart().ConvertToPx());
        paddingEnd_ = static_cast<float>(theme->GetMaxPaddingEnd().ConvertToPx());
        paddingTop_ = static_cast<float>(theme->GetDefaultPaddingTop().ConvertToPx());
        paddingBottom_ = static_cast<float>(theme->GetDefaultPaddingBottomFixed().ConvertToPx());
    } else {
        margin_ = static_cast<float>(theme->GetOutPadding().ConvertToPx());
        paddingStart_ = margin_;
        paddingEnd_ = margin_;
        paddingTop_ = margin_;
        paddingBottom_ = margin_;
        optionPadding_ = static_cast<float>(theme->GetOutPadding().ConvertToPx());
    }
}

void MenuLayoutAlgorithm::ModifyPositionToWrapper(LayoutWrapper* layoutWrapper, OffsetF& position)
{
    auto menu = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(menu);
    auto wrapper = AceType::DynamicCast<FrameNode>(menu->GetParent());
    CHECK_NULL_VOID(wrapper);

    OffsetF wrapperOffset;
    // minus wrapper offset in LayoutFullScreen
    auto wrapperLayoutProps = wrapper->GetLayoutProperty();
    CHECK_NULL_VOID(wrapperLayoutProps);
    auto&& safeAreaInsets = wrapperLayoutProps->GetSafeAreaInsets();
    if (safeAreaInsets) {
        wrapperOffset +=
            OffsetF(static_cast<float>(safeAreaInsets->left_.end), static_cast<float>(safeAreaInsets->top_.end));
        position -= wrapperOffset;
    }

    auto menuPattern = menu->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    bool isSubMenu = menuPattern->IsSubMenu() || menuPattern->IsSelectOverlaySubMenu();
    if ((menuPattern->IsContextMenu() || (isSubMenu && Container::CurrentId() >= MIN_SUBCONTAINER_ID) ||
            hierarchicalParameters_) &&
        (targetTag_ != V2::SELECT_ETS_TAG)) {
        // no need to modify for context menu, because context menu wrapper is full screen.
        return;
    }
    // minus wrapper offset in floating window
    auto pipelineContext = GetCurrentPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto windowManager = pipelineContext->GetWindowManager();
    auto isContainerModal = pipelineContext->GetWindowModal() == WindowModal::CONTAINER_MODAL && windowManager &&
                            windowManager->GetWindowMode() == WindowMode::WINDOW_MODE_FLOATING;
    if (isContainerModal) {
        wrapperOffset = OffsetF(static_cast<float>((CONTAINER_BORDER_WIDTH + CONTENT_PADDING).ConvertToPx()),
            static_cast<float>((CONTAINER_TITLE_HEIGHT + CONTAINER_BORDER_WIDTH).ConvertToPx()));
        position -= wrapperOffset;
    }
}

// Called to perform layout render node and child.
void MenuLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    // initialize screen size and menu position
    CHECK_NULL_VOID(layoutWrapper);
    auto menuNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto menuLayoutProperty = AceType::DynamicCast<MenuLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(menuLayoutProperty);
    auto isShowInSubWindow = menuLayoutProperty->GetShowInSubWindowValue(true);
    InitHierarchicalParameters(isShowInSubWindow);
    if (!targetTag_.empty()) {
        InitTargetSizeAndPosition(layoutWrapper, menuPattern->IsContextMenu(), menuPattern);
    }
    Initialize(layoutWrapper);

    const auto& constraint = menuLayoutProperty->GetLayoutConstraint();
    if (!constraint) {
        return;
    }
    auto idealSize = CreateIdealSize(
        constraint.value(), Axis::VERTICAL, menuLayoutProperty->GetMeasureType(MeasureType::MATCH_CONTENT), true);
    const auto& padding = menuLayoutProperty->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, idealSize);

    // calculate menu main size
    auto childConstraint = CreateChildConstraint(layoutWrapper);
    if (menuPattern->IsSelectMenu() && menuPattern->GetHasOptionWidth()) {
        auto selectMenuWidth = menuPattern->GetSelectMenuWidth();
        childConstraint.maxSize.SetWidth(selectMenuWidth);
        childConstraint.parentIdealSize.SetWidth(selectMenuWidth);
        childConstraint.selfIdealSize.SetWidth(selectMenuWidth);
    }
    float idealHeight = 0.0f;
    float idealWidth = 0.0f;
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        child->Measure(childConstraint);
        auto childSize = child->GetGeometryNode()->GetMarginFrameSize();
        idealHeight += childSize.Height();
        idealWidth = std::max(idealWidth, childSize.Width());
    }
    idealSize.SetHeight(idealHeight);
    idealSize.SetWidth(idealWidth);
    AddPaddingToSize(padding, idealSize);

    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    geometryNode->SetFrameSize(idealSize);
}

SizeF MenuLayoutAlgorithm::GetPreviewNodeAndMenuNodeTotalSize(const RefPtr<FrameNode>& frameNode,
    RefPtr<LayoutWrapper>& previewLayoutWrapper, RefPtr<LayoutWrapper>& menuLayoutWrapper)
{
    SizeF size;
    CHECK_NULL_RETURN(frameNode, size);
    auto pipelineContext = GetCurrentPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, size);
    auto windowGlobalRect = pipelineContext->GetDisplayWindowRectInfo();
    for (auto& child : frameNode->GetAllChildrenWithBuild()) {
        auto hostNode = child->GetHostNode();
        auto geometryNode = child->GetGeometryNode();
        if (!hostNode || !geometryNode) {
            continue;
        }
        if (hostNode->GetTag() == V2::MENU_PREVIEW_ETS_TAG || hostNode->GetTag() == V2::IMAGE_ETS_TAG) {
            RefPtr<GridColumnInfo> columnInfo =
                GridSystemManager::GetInstance().GetInfoByType(GridColumnType::CARD_TYPE);
            CHECK_NULL_RETURN(columnInfo, size);
            auto parent = columnInfo->GetParent();
            CHECK_NULL_RETURN(parent, size);
            parent->BuildColumnWidth(std::min(windowGlobalRect.Width(), windowGlobalRect.Height()));
            auto maxWidth = static_cast<float>(columnInfo->GetWidth(GRID_COUNTS_4)) / previewScale_;
            auto frameSize = geometryNode->GetMarginFrameSize();
            static SizeF previewSize;
            static int32_t hostId = -1;
            if (hostNode->GetTag() == V2::MENU_PREVIEW_ETS_TAG) {
                if (previewSize == SizeF(0.0f, 0.0f) || hostId != hostNode->GetId()) {
                    previewSize = frameSize;
                    hostId = hostNode->GetId();
                } else {
                    frameSize = previewSize;
                }
                geometryNode->SetFrameSize(SizeF(maxWidth, frameSize.Height()));
            } else {
                geometryNode->SetFrameSize(frameSize);
            }
            frameSize = geometryNode->GetMarginFrameSize() * previewScale_;
            auto widthLeftSpace = windowGlobalRect.Width() - paddingStart_ - paddingEnd_;
            if (GreatNotEqual(frameSize.Width(), widthLeftSpace)) {
                auto unitSpace = widthLeftSpace / frameSize.Width() / previewScale_;
                geometryNode->SetFrameSize(SizeF(widthLeftSpace / previewScale_, unitSpace * frameSize.Height()));
            }
            previewLayoutWrapper = child;
            size += geometryNode->GetMarginFrameSize() * previewScale_;
        }
        auto menuPattern = hostNode->GetPattern<MenuPattern>();
        if (hostNode->GetTag() == V2::MENU_ETS_TAG && menuPattern && !menuPattern->IsSubMenu()) {
            menuLayoutWrapper = child;
            size += geometryNode->GetMarginFrameSize();
        }
    }
    return size;
}

void MenuLayoutAlgorithm::LayoutNormalTopPreviewBottomMenuLessThan(const RefPtr<GeometryNode>& previewGeometryNode,
    const RefPtr<GeometryNode>& menuGeometryNode, const PreviewMenuParam& param, SizeF& totalSize)
{
    CHECK_NULL_VOID(previewGeometryNode);
    CHECK_NULL_VOID(menuGeometryNode);

    OffsetF center(targetOffset_.GetX() + targetSize_.Width() / 2, targetOffset_.GetY() + targetSize_.Height() / 2);
    targetCenterOffset_ = center;
    auto previewSize = previewGeometryNode->GetMarginFrameSize() * previewScale_;
    OffsetF offset(center.GetX() - previewSize.Width() / 2,
        std::min<float>(center.GetY() - previewSize.Height() / 2, param.windowGlobalSizeF.Height() -
            param.bottomSecurity - param.bottom - totalSize.Height() - param.previewMenuGap));
    auto x = std::clamp(offset.GetX(), param.windowsOffsetX + paddingStart_,
        param.windowsOffsetX + param.windowGlobalSizeF.Width() - previewSize.Width() - paddingEnd_);
    auto y = std::clamp(offset.GetY(), param.windowsOffsetY + param.top + param.topSecurity,
        param.windowsOffsetY + param.windowGlobalSizeF.Height() - param.bottomSecurity - param.bottom -
            previewSize.Height());
    x = x + (previewSize.Width() - previewSize.Width() / previewScale_) / 2;
    y = y + (previewSize.Height() - previewSize.Height() / previewScale_) / 2;
    previewGeometryNode->SetMarginFrameOffset(OffsetF(x, y));
}

void MenuLayoutAlgorithm::LayoutNormalTopPreviewBottomMenuGreateThan(const RefPtr<GeometryNode>& previewGeometryNode,
    const RefPtr<GeometryNode>& menuGeometryNode, const PreviewMenuParam& param, SizeF& totalSize)
{
    CHECK_NULL_VOID(previewGeometryNode);
    CHECK_NULL_VOID(menuGeometryNode);

    OffsetF center(targetOffset_.GetX() + targetSize_.Width() / 2, targetOffset_.GetY() + targetSize_.Height() / 2);
    targetCenterOffset_ = center;
    auto previewSize = previewGeometryNode->GetMarginFrameSize() * previewScale_;
    auto menuHeight = totalSize.Height() - previewSize.Height();
    auto previewHalfHeight = previewSize.Height() / 2;
    if (LessNotEqual(menuHeight, previewHalfHeight)) {
        auto menuSize = menuGeometryNode->GetMarginFrameSize();
        if (GreatNotEqual(param.menuItemTotalHeight, previewHalfHeight)) {
            menuGeometryNode->SetFrameSize(SizeF(menuSize.Width(), previewHalfHeight));
            totalSize = SizeF(totalSize.Width(), previewHalfHeight + previewSize.Height());
        } else {
            menuGeometryNode->SetFrameSize(SizeF(menuSize.Width(), param.menuItemTotalHeight));
            totalSize = SizeF(totalSize.Width(), param.menuItemTotalHeight + previewSize.Height());
        }
    }

    auto heightLeftSpace = param.windowGlobalSizeF.Height() - param.top - param.bottom - param.topSecurity -
                           param.bottomSecurity - param.previewMenuGap;
    auto delta = totalSize.Height() - heightLeftSpace;
    if (GreatNotEqual(delta, 0.0f)) {
        menuHeight = totalSize.Height() - previewSize.Height();
        float unitSpace = 0.0f;
        if (LessNotEqual(menuHeight, previewHalfHeight)) {
            unitSpace = delta / previewSize.Height();
        } else {
            unitSpace = delta / totalSize.Height();
            auto menuSize = menuGeometryNode->GetMarginFrameSize();
            menuGeometryNode->SetFrameSize(SizeF(menuSize.Width(), (1 - unitSpace) * menuSize.Height()));
        }
        previewGeometryNode->SetFrameSize(SizeF((1 - unitSpace) * previewSize.Width() / previewScale_,
            (1 - unitSpace) * previewSize.Height() / previewScale_));
        totalSize = totalSize - SizeF(0.0f, delta);
    }
    previewSize = previewGeometryNode->GetMarginFrameSize() * previewScale_;
    OffsetF offset(center.GetX() - previewSize.Width() / 2, 0.0f);
    auto x = std::clamp(offset.GetX(), param.windowsOffsetX + paddingStart_,
        param.windowsOffsetX + param.windowGlobalSizeF.Width() - previewSize.Width() - paddingEnd_);
    auto y = std::clamp(offset.GetY(), param.windowsOffsetY + param.top + param.topSecurity, param.windowsOffsetY +
        param.windowGlobalSizeF.Height() - param.bottomSecurity - param.bottom - previewSize.Height());
    x = x + (previewSize.Width() - previewSize.Width() / previewScale_) / 2;
    y = y + (previewSize.Height() - previewSize.Height() / previewScale_) / 2;
    previewGeometryNode->SetMarginFrameOffset(OffsetF(x, y));
}

void MenuLayoutAlgorithm::LayoutNormalTopPreviewBottomMenu(const RefPtr<GeometryNode>& previewGeometryNode,
    const RefPtr<GeometryNode>& menuGeometryNode, SizeF& totalSize, float menuItemTotalHeight)
{
    CHECK_NULL_VOID(previewGeometryNode);
    CHECK_NULL_VOID(menuGeometryNode);

    auto pipelineContext = GetCurrentPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto safeAreaManager = pipelineContext->GetSafeAreaManager();
    CHECK_NULL_VOID(safeAreaManager);
    auto top = safeAreaManager->GetSystemSafeArea().top_.Length();
    auto bottom = safeAreaManager->GetSystemSafeArea().bottom_.Length();
    auto windowGlobalRect = pipelineContext->GetDisplayWindowRectInfo();
    float windowsOffsetX = static_cast<float>(windowGlobalRect.GetOffset().GetX());
    float windowsOffsetY = static_cast<float>(windowGlobalRect.GetOffset().GetY());
    float screenHeight = wrapperSize_.Height();
    if (!NearEqual(wrapperSize_.Height(), windowGlobalRect.Height())) {
        screenHeight += bottom;
    }
    SizeF windowGlobalSizeF(windowGlobalRect.Width(), screenHeight - windowsOffsetY);

    float topSecurity = static_cast<float>(PORTRAIT_TOP_SECURITY.ConvertToPx());
    float bottomSecurity = static_cast<float>(PORTRAIT_BOTTOM_SECURITY.ConvertToPx());

    PreviewMenuParam param;
    param.windowGlobalSizeF = windowGlobalSizeF;
    param.windowsOffsetX = windowsOffsetX;
    param.windowsOffsetY = windowsOffsetY;
    param.top = top;
    param.bottom = bottom;
    param.topSecurity = topSecurity;
    param.bottomSecurity = bottomSecurity;
    param.previewMenuGap = targetSecurity_;
    param.menuItemTotalHeight = menuItemTotalHeight;
    if (LessNotEqual(totalSize.Height() + targetSecurity_,
        windowGlobalSizeF.Height() - topSecurity - bottomSecurity - top - bottom)) {
        LayoutNormalTopPreviewBottomMenuLessThan(previewGeometryNode, menuGeometryNode, param, totalSize);
    } else {
        LayoutNormalTopPreviewBottomMenuGreateThan(previewGeometryNode, menuGeometryNode, param, totalSize);
    }
    auto previewSize = previewGeometryNode->GetMarginFrameSize();
    auto securityHeight = windowGlobalRect.Height() - topSecurity - top - bottomSecurity - bottom;
    if (GreatNotEqual(windowGlobalSizeF.Height(), windowGlobalRect.Height()) &&
        GreatNotEqual(previewSize.Height(), securityHeight)) {
        previewGeometryNode->SetFrameSize(SizeF(previewSize.Width(), securityHeight));
    }
}

void MenuLayoutAlgorithm::LayoutNormalBottomPreviewTopMenuLessThan(const RefPtr<GeometryNode>& previewGeometryNode,
    const RefPtr<GeometryNode>& menuGeometryNode, const PreviewMenuParam& param, SizeF& totalSize)
{
    CHECK_NULL_VOID(previewGeometryNode);
    CHECK_NULL_VOID(menuGeometryNode);

    OffsetF center(targetOffset_.GetX() + targetSize_.Width() / 2, targetOffset_.GetY() + targetSize_.Height() / 2);
    targetCenterOffset_ = center;
    auto previewSize = previewGeometryNode->GetMarginFrameSize() * previewScale_;
    OffsetF offset(center.GetX() - previewSize.Width() / 2,
        std::max<float>(center.GetY() - previewSize.Height() / 2,
            param.top + param.topSecurity + totalSize.Height() - previewSize.Height() + param.previewMenuGap));
    auto x = std::clamp(offset.GetX(), param.windowsOffsetX + paddingStart_,
        param.windowsOffsetX + param.windowGlobalSizeF.Width() - previewSize.Width() - paddingEnd_);
    auto y = std::clamp(offset.GetY(), param.windowsOffsetY + param.top + param.topSecurity,
        param.windowsOffsetY + param.windowGlobalSizeF.Height() - param.bottomSecurity - param.bottom -
            previewSize.Height());
    x = x + (previewSize.Width() - previewSize.Width() / previewScale_) / 2;
    y = y + (previewSize.Height() - previewSize.Height() / previewScale_) / 2;
    previewGeometryNode->SetMarginFrameOffset(OffsetF(x, y));
}

void MenuLayoutAlgorithm::LayoutNormalBottomPreviewTopMenuGreateThan(const RefPtr<GeometryNode>& previewGeometryNode,
    const RefPtr<GeometryNode>& menuGeometryNode, const PreviewMenuParam& param, SizeF& totalSize)
{
    CHECK_NULL_VOID(previewGeometryNode);
    CHECK_NULL_VOID(menuGeometryNode);

    OffsetF center(targetOffset_.GetX() + targetSize_.Width() / 2, targetOffset_.GetY() + targetSize_.Height() / 2);
    targetCenterOffset_ = center;
    auto previewSize = previewGeometryNode->GetMarginFrameSize() * previewScale_;
    auto menuHeight = totalSize.Height() - previewSize.Height();
    auto previewHalfHeight = previewSize.Height() / 2;
    if (LessNotEqual(menuHeight, previewHalfHeight)) {
        auto menuSize = menuGeometryNode->GetMarginFrameSize();
        if (GreatNotEqual(param.menuItemTotalHeight, previewHalfHeight)) {
            menuGeometryNode->SetFrameSize(SizeF(menuSize.Width(), previewHalfHeight));
            totalSize = SizeF(totalSize.Width(), previewHalfHeight + previewSize.Height());
        } else {
            menuGeometryNode->SetFrameSize(SizeF(menuSize.Width(), param.menuItemTotalHeight));
            totalSize = SizeF(totalSize.Width(), param.menuItemTotalHeight + previewSize.Height());
        }
    }

    auto heightLeftSpace = param.windowGlobalSizeF.Height() - param.top - param.topSecurity - param.bottom -
                           param.bottomSecurity - param.previewMenuGap;
    auto delta = totalSize.Height() - heightLeftSpace;
    if (GreatNotEqual(delta, 0.0f)) {
        menuHeight = totalSize.Height() - previewSize.Height();
        float unitSpace = 0.0f;
        if (LessNotEqual(menuHeight, previewHalfHeight)) {
            unitSpace = delta / previewSize.Height();
        } else {
            unitSpace = delta / totalSize.Height();
            auto menuSize = menuGeometryNode->GetMarginFrameSize();
            menuGeometryNode->SetFrameSize(SizeF(menuSize.Width(), (1 - unitSpace) * menuSize.Height()));
        }
        previewGeometryNode->SetFrameSize(SizeF((1 - unitSpace) * previewSize.Width() / previewScale_,
            (1 - unitSpace) * previewSize.Height() / previewScale_));
        totalSize = totalSize - SizeF(0.0f, delta);
    }
    previewSize = previewGeometryNode->GetMarginFrameSize() * previewScale_;
    OffsetF offset(center.GetX() - previewSize.Width() / 2,
        param.windowGlobalSizeF.Height() - param.bottomSecurity - param.bottom - previewSize.Height());

    auto x = std::clamp(offset.GetX(), param.windowsOffsetX + paddingStart_,
        param.windowsOffsetX + param.windowGlobalSizeF.Width() - previewSize.Width() - paddingEnd_);
    auto y = std::clamp(offset.GetY(), param.windowsOffsetY + param.top + param.topSecurity, param.windowsOffsetY +
        param.windowGlobalSizeF.Height() - param.bottomSecurity - param.bottom - previewSize.Height());
    x = x + (previewSize.Width() - previewSize.Width() / previewScale_) / 2;
    y = y + (previewSize.Height() - previewSize.Height() / previewScale_) / 2;
    previewGeometryNode->SetMarginFrameOffset(OffsetF(x, y));
}

void MenuLayoutAlgorithm::LayoutNormalBottomPreviewTopMenu(const RefPtr<GeometryNode>& previewGeometryNode,
    const RefPtr<GeometryNode>& menuGeometryNode, SizeF& totalSize, float menuItemTotalHeight)
{
    CHECK_NULL_VOID(previewGeometryNode);
    CHECK_NULL_VOID(menuGeometryNode);

    auto pipelineContext = GetCurrentPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto safeAreaManager = pipelineContext->GetSafeAreaManager();
    CHECK_NULL_VOID(safeAreaManager);
    auto top = safeAreaManager->GetSystemSafeArea().top_.Length();
    auto bottom = safeAreaManager->GetSystemSafeArea().bottom_.Length();
    auto windowGlobalRect = pipelineContext->GetDisplayWindowRectInfo();
    float windowsOffsetX = static_cast<float>(windowGlobalRect.GetOffset().GetX());
    float windowsOffsetY = static_cast<float>(windowGlobalRect.GetOffset().GetY());
    float screenHeight = wrapperSize_.Height();
    if (!NearEqual(wrapperSize_.Height(), windowGlobalRect.Height())) {
        screenHeight += bottom;
    }
    SizeF windowGlobalSizeF(windowGlobalRect.Width(), screenHeight - windowsOffsetY);

    float topSecurity = static_cast<float>(PORTRAIT_TOP_SECURITY.ConvertToPx());
    float bottomSecurity = static_cast<float>(PORTRAIT_BOTTOM_SECURITY.ConvertToPx());

    PreviewMenuParam param;
    param.windowGlobalSizeF = windowGlobalSizeF;
    param.windowsOffsetX = windowsOffsetX;
    param.windowsOffsetY = windowsOffsetY;
    param.top = top;
    param.bottom = bottom;
    param.topSecurity = topSecurity;
    param.bottomSecurity = bottomSecurity;
    param.previewMenuGap = targetSecurity_;
    param.menuItemTotalHeight = menuItemTotalHeight;
    if (LessNotEqual(totalSize.Height() + targetSecurity_,
        windowGlobalSizeF.Height() - topSecurity - bottomSecurity - top - bottom)) {
        LayoutNormalBottomPreviewTopMenuLessThan(previewGeometryNode, menuGeometryNode, param, totalSize);
    } else {
        LayoutNormalBottomPreviewTopMenuGreateThan(previewGeometryNode, menuGeometryNode, param, totalSize);
    }
    auto previewSize = previewGeometryNode->GetMarginFrameSize();
    auto securityHeight = windowGlobalRect.Height() - topSecurity - top - bottomSecurity - bottom;
    if (GreatNotEqual(windowGlobalSizeF.Height(), windowGlobalRect.Height()) &&
        GreatNotEqual(previewSize.Height(), securityHeight)) {
        previewGeometryNode->SetFrameSize(SizeF(previewSize.Width(), securityHeight));
    }
}

void MenuLayoutAlgorithm::UpdateScrollAndColumnLayoutConstraint(
    const RefPtr<LayoutWrapper>& previewLayoutWrapper, const RefPtr<LayoutWrapper>& menuLayoutWrapper)
{
    CHECK_NULL_VOID(menuLayoutWrapper);
    CHECK_NULL_VOID(previewLayoutWrapper);
    RefPtr<GeometryNode> menuGeometryNode = menuLayoutWrapper->GetGeometryNode();
    RefPtr<GeometryNode> previewGeometryNode = previewLayoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(menuGeometryNode);
    CHECK_NULL_VOID(previewGeometryNode);

    for (auto& child : menuLayoutWrapper->GetAllChildrenWithBuild()) {
        auto geometryNode = child->GetGeometryNode();
        if (!geometryNode) {
            continue;
        }
        auto frameSize = menuGeometryNode->GetMarginFrameSize();
        geometryNode->SetFrameSize(SizeF(frameSize.Width(), frameSize.Height()));
        auto layoutProperty = child->GetLayoutProperty();
        CHECK_NULL_VOID(layoutProperty);
        auto constraint = layoutProperty->GetLayoutConstraint();
        if (constraint.has_value()) {
            constraint.value().maxSize.SetWidth(frameSize.Width());
            constraint.value().maxSize.SetHeight(frameSize.Height());
            constraint.value().selfIdealSize.UpdateSizeWithCheck(SizeF(frameSize.Width(), frameSize.Height()));
            layoutProperty->UpdateLayoutConstraint(constraint.value());
            child->Measure(constraint);
        }
    }
    for (auto& child : previewLayoutWrapper->GetAllChildrenWithBuild()) {
        auto hostNode = child->GetHostNode();
        auto geometryNode = child->GetGeometryNode();
        if (!hostNode || !geometryNode) {
            continue;
        }
        auto frameSize = previewGeometryNode->GetMarginFrameSize();
        auto previewSecurity = static_cast<float>(PREVIEW_INNER_SECURITY.ConvertToPx() / previewScale_) * 2;
        geometryNode->SetFrameSize(SizeF(frameSize.Width() - previewSecurity, frameSize.Height() - previewSecurity));
        auto layoutProperty = child->GetLayoutProperty();
        CHECK_NULL_VOID(layoutProperty);
        auto constraint = layoutProperty->GetLayoutConstraint();
        if (constraint.has_value()) {
            constraint.value().maxSize.SetWidth(frameSize.Width() - previewSecurity);
            constraint.value().maxSize.SetHeight(frameSize.Height() - previewSecurity);
            constraint.value().selfIdealSize.UpdateSizeWithCheck(
                SizeF(frameSize.Width() - previewSecurity, frameSize.Height() - previewSecurity));
            layoutProperty->UpdateLayoutConstraint(constraint.value());
            hostNode->GetRenderContext()->SetClipToBounds(true);
            child->Measure(constraint);
        }
    }
}

float MenuLayoutAlgorithm::GetMenuItemTotalHeight(const RefPtr<LayoutWrapper>& menuLayoutWrapper)
{
    CHECK_NULL_RETURN(menuLayoutWrapper, 0.0f);
    RefPtr<GeometryNode> menuGeometryNode = menuLayoutWrapper->GetGeometryNode();
    CHECK_NULL_RETURN(menuGeometryNode, 0.0f);
    float height = 0.0f;

    for (auto& child : menuLayoutWrapper->GetAllChildrenWithBuild()) {
        auto geometryNode = child->GetGeometryNode();
        if (!geometryNode) {
            continue;
        }
        for (auto& menuItem : child->GetAllChildrenWithBuild()) {
            auto itemHostnode = menuItem->GetHostNode();
            auto itemGeometryNode = menuItem->GetGeometryNode();
            if (!itemHostnode || !itemGeometryNode) {
                continue;
            }
            height += itemGeometryNode->GetMarginFrameSize().Height();
        }
    }
    auto menuHeight = menuGeometryNode->GetMarginFrameSize().Height();
    if (LessNotEqual(height, menuHeight)) {
        height = menuHeight;
    }
    return height;
}

void MenuLayoutAlgorithm::LayoutNormalPreviewMenu(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto menuNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(menuNode);
    auto parentNode = AceType::DynamicCast<FrameNode>(menuNode->GetParent());
    CHECK_NULL_VOID(parentNode);
    auto menuProp = DynamicCast<MenuLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(menuProp);

    RefPtr<LayoutWrapper> menuLayoutWrapper;
    RefPtr<LayoutWrapper> previewLayoutWrapper;
    SizeF totalSize = GetPreviewNodeAndMenuNodeTotalSize(parentNode, previewLayoutWrapper, menuLayoutWrapper);
    CHECK_NULL_VOID(menuLayoutWrapper);
    CHECK_NULL_VOID(previewLayoutWrapper);
    RefPtr<GeometryNode> menuGeometryNode = menuLayoutWrapper->GetGeometryNode();
    RefPtr<GeometryNode> previewGeometryNode = previewLayoutWrapper->GetGeometryNode();
    auto menuItemTotalHeight = GetMenuItemTotalHeight(menuLayoutWrapper);

    if (SystemProperties::GetDeviceOrientation() == DeviceOrientation::PORTRAIT) {
        if (placement_ == Placement::TOP_LEFT || placement_ == Placement::TOP || placement_ == Placement::TOP_RIGHT) {
            LayoutNormalBottomPreviewTopMenu(previewGeometryNode, menuGeometryNode, totalSize, menuItemTotalHeight);
        } else {
            LayoutNormalTopPreviewBottomMenu(previewGeometryNode, menuGeometryNode, totalSize, menuItemTotalHeight);
        }
    } else {
        LayoutOtherDeviceLeftPreviewRightMenu(previewGeometryNode, menuGeometryNode, totalSize, menuItemTotalHeight);
    }
    UpdateScrollAndColumnLayoutConstraint(previewLayoutWrapper, menuLayoutWrapper);
    auto previewSize = previewGeometryNode->GetMarginFrameSize();
    previewOffset_ = previewGeometryNode->GetFrameOffset();
    auto previewOffsetX = previewOffset_.GetX();
    auto previewOffsetY = previewOffset_.GetY();
    targetSize_ = previewSize * previewScale_;
    targetOffset_ = OffsetF(previewOffsetX + (previewSize.Width() - targetSize_.Width()) / 2,
        previewOffsetY + (previewSize.Height() - targetSize_.Height()) / 2);
    auto previewHostNode = previewLayoutWrapper->GetHostNode();
    CHECK_NULL_VOID(previewHostNode);
    auto renderContext = previewHostNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdatePosition(OffsetT<Dimension>(Dimension(previewOffsetX), Dimension(previewOffsetY)));

    auto menuHostNode = menuLayoutWrapper->GetHostNode();
    CHECK_NULL_VOID(menuHostNode);
    previewOriginOffset_ = targetCenterOffset_ - OffsetF(previewSize.Width() / 2, previewSize.Height() / 2);
    previewSize_ = previewSize;
    auto menuPattern = menuHostNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->SetPreviewOriginOffset(previewOriginOffset_);
}

void MenuLayoutAlgorithm::LayoutOtherDeviceLeftPreviewRightMenuLessThan(const RefPtr<GeometryNode>& previewGeometryNode,
    const RefPtr<GeometryNode>& menuGeometryNode, const PreviewMenuParam& param, SizeF& totalSize)
{
    CHECK_NULL_VOID(previewGeometryNode);
    CHECK_NULL_VOID(menuGeometryNode);

    OffsetF targetCenterOffset(
        targetOffset_.GetX() + targetSize_.Width() / 2, targetOffset_.GetY() + targetSize_.Height() / 2);
    targetCenterOffset_ = targetCenterOffset;
    auto previewSize = previewGeometryNode->GetMarginFrameSize() * previewScale_;
    auto heightLeftSpace =
        param.windowGlobalSizeF.Height() - param.top - param.topSecurity - param.bottomSecurity - param.bottom;
    auto delta = previewSize.Height() - heightLeftSpace;
    if (GreatNotEqual(delta, 0.0f)) {
        auto unitSpace = delta / previewSize.Height();
        previewGeometryNode->SetFrameSize(SizeF((1 - unitSpace) * previewSize.Width() / previewScale_,
            (1 - unitSpace) * previewSize.Height() / previewScale_));
        totalSize = totalSize - SizeF(unitSpace * previewSize.Width(), unitSpace * previewSize.Height());
    }
    previewSize = previewGeometryNode->GetMarginFrameSize() * previewScale_;
    auto menuSize = menuGeometryNode->GetMarginFrameSize();
    menuGeometryNode->SetFrameSize(
        SizeF(menuSize.Width(), std::min<float>(param.menuItemTotalHeight, heightLeftSpace)));
    menuSize = menuGeometryNode->GetMarginFrameSize();
    auto offsetX = targetCenterOffset.GetX() - previewSize.Width() / 2;
    auto offsetY = std::min<float>(targetCenterOffset.GetY() - previewSize.Height() / 2,
        param.windowGlobalSizeF.Height() - param.bottomSecurity - param.bottom - menuSize.Height());
    auto x = std::clamp(offsetX, param.windowsOffsetX + paddingStart_,
        param.windowsOffsetX + param.windowGlobalSizeF.Width() - previewSize.Width() - paddingEnd_);
    auto y = std::clamp(offsetY, param.windowsOffsetY + param.top + param.topSecurity,
        param.windowsOffsetY + param.windowGlobalSizeF.Height() - param.bottomSecurity - param.bottom -
            previewSize.Height());
    x = x + (previewSize.Width() - previewSize.Width() / previewScale_) / 2;
    y = y + (previewSize.Height() - previewSize.Height() / previewScale_) / 2;
    previewGeometryNode->SetMarginFrameOffset(OffsetF(x, y));
}

void MenuLayoutAlgorithm::LayoutOtherDeviceLeftPreviewRightMenuGreateThan(
    const RefPtr<GeometryNode>& previewGeometryNode, const RefPtr<GeometryNode>& menuGeometryNode,
    const PreviewMenuParam& param, SizeF& totalSize)
{
    CHECK_NULL_VOID(previewGeometryNode);
    CHECK_NULL_VOID(menuGeometryNode);

    OffsetF targetCenterOffset(
        targetOffset_.GetX() + targetSize_.Width() / 2, targetOffset_.GetY() + targetSize_.Height() / 2);
    targetCenterOffset_ = targetCenterOffset;
    auto previewSize = previewGeometryNode->GetMarginFrameSize() * previewScale_;
    auto widthLeftSpace = param.windowGlobalSizeF.Width() - paddingStart_ - paddingEnd_ - param.previewMenuGap;
    auto delta = totalSize.Width() - widthLeftSpace;
    if (GreatNotEqual(delta, 0.0f)) {
        auto unitSpace = delta / previewSize.Width();
        previewGeometryNode->SetFrameSize(SizeF((1 - unitSpace) * previewSize.Width() / previewScale_,
            (1 - unitSpace) * previewSize.Height() / previewScale_));
        totalSize = totalSize - SizeF(unitSpace * previewSize.Width(), unitSpace * previewSize.Height());
    }
    previewSize = previewGeometryNode->GetMarginFrameSize() * previewScale_;
    auto heightLeftSpace =
        param.windowGlobalSizeF.Height() - param.topSecurity - param.top - param.bottomSecurity - param.bottom;
    delta = previewSize.Height() - heightLeftSpace;
    if (GreatNotEqual(delta, 0.0f)) {
        auto unitSpace = delta / previewSize.Height();
        previewGeometryNode->SetFrameSize(SizeF((1 - unitSpace) * previewSize.Width() / previewScale_,
            (1 - unitSpace) * previewSize.Height() / previewScale_));
        totalSize = totalSize - SizeF(unitSpace * previewSize.Width(), unitSpace * previewSize.Height());
    }
    previewSize = previewGeometryNode->GetMarginFrameSize() * previewScale_;
    auto menuSize = menuGeometryNode->GetMarginFrameSize();
    menuGeometryNode->SetFrameSize(
        SizeF(menuSize.Width(), std::min<float>(param.menuItemTotalHeight, heightLeftSpace)));
    menuSize = menuGeometryNode->GetMarginFrameSize();
    auto offsetX = 0.0f;
    auto offsetY = std::min<float>(targetCenterOffset.GetY() - previewSize.Height() / 2,
        param.windowGlobalSizeF.Height() - param.bottomSecurity - param.bottom - menuSize.Height());
    auto x = std::clamp(offsetX, param.windowsOffsetX + paddingStart_,
        param.windowsOffsetX + param.windowGlobalSizeF.Width() - previewSize.Width() - paddingEnd_);
    auto y = std::clamp(offsetY, param.windowsOffsetY + param.top + param.topSecurity,
        param.windowsOffsetY + param.windowGlobalSizeF.Height() - param.bottomSecurity - param.bottom -
            previewSize.Height());
    x = x + (previewSize.Width() - previewSize.Width() / previewScale_) / 2;
    y = y + (previewSize.Height() - previewSize.Height() / previewScale_) / 2;
    previewGeometryNode->SetMarginFrameOffset(OffsetF(x, y));
}

void MenuLayoutAlgorithm::LayoutOtherDeviceLeftPreviewRightMenu(const RefPtr<GeometryNode>& previewGeometryNode,
    const RefPtr<GeometryNode>& menuGeometryNode, SizeF& totalSize, float menuItemTotalHeight)
{
    CHECK_NULL_VOID(previewGeometryNode);
    CHECK_NULL_VOID(menuGeometryNode);

    auto pipelineContext = GetCurrentPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto safeAreaManager = pipelineContext->GetSafeAreaManager();
    CHECK_NULL_VOID(safeAreaManager);
    auto top = safeAreaManager->GetSystemSafeArea().top_.Length();
    auto bottom = safeAreaManager->GetSystemSafeArea().bottom_.Length();
    auto windowGlobalRect = pipelineContext->GetDisplayWindowRectInfo();
    float windowsOffsetX = static_cast<float>(windowGlobalRect.GetOffset().GetX());
    float windowsOffsetY = static_cast<float>(windowGlobalRect.GetOffset().GetY());
    float screenHeight = wrapperSize_.Height();
    if (!NearEqual(wrapperSize_.Height(), windowGlobalRect.Height())) {
        screenHeight += bottom;
    }
    SizeF windowGlobalSizeF(windowGlobalRect.Width(), screenHeight - windowsOffsetY);
    float topSecurity = 0.0f;
    float bottomSecurity = 0.0f;
    if (SystemProperties::GetDeviceOrientation() == DeviceOrientation::PORTRAIT) {
        topSecurity = static_cast<float>(PORTRAIT_TOP_SECURITY.ConvertToPx());
        bottomSecurity = static_cast<float>(PORTRAIT_BOTTOM_SECURITY.ConvertToPx());
    } else {
        topSecurity = static_cast<float>(LANDSCAPE_TOP_SECURITY.ConvertToPx());
        bottomSecurity = static_cast<float>(LANDSCAPE_BOTTOM_SECURITY.ConvertToPx());
    }
    PreviewMenuParam param;
    param.windowGlobalSizeF = windowGlobalSizeF;
    param.windowsOffsetX = windowsOffsetX;
    param.windowsOffsetY = windowsOffsetY;
    param.top = top;
    param.bottom = bottom;
    param.topSecurity = topSecurity;
    param.bottomSecurity = bottomSecurity;
    param.previewMenuGap = targetSecurity_;
    param.menuItemTotalHeight = menuItemTotalHeight;
    if (LessNotEqual(totalSize.Width() + targetSecurity_, windowGlobalSizeF.Width() - paddingStart_ - paddingEnd_)) {
        LayoutOtherDeviceLeftPreviewRightMenuLessThan(previewGeometryNode, menuGeometryNode, param, totalSize);
    } else {
        LayoutOtherDeviceLeftPreviewRightMenuGreateThan(previewGeometryNode, menuGeometryNode, param, totalSize);
    }
    auto previewSize = previewGeometryNode->GetMarginFrameSize();
    auto securityHeight = windowGlobalRect.Height() - topSecurity - top - bottomSecurity - bottom;
    if (GreatNotEqual(windowGlobalSizeF.Height(), windowGlobalRect.Height()) &&
        GreatNotEqual(previewSize.Height(), securityHeight)) {
        previewGeometryNode->SetFrameSize(SizeF(previewSize.Width(), securityHeight));
    }
}

void MenuLayoutAlgorithm::LayoutOtherDevicePreviewMenu(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto menuNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(menuNode);
    auto parentNode = AceType::DynamicCast<FrameNode>(menuNode->GetParent());
    CHECK_NULL_VOID(parentNode);
    auto menuProp = DynamicCast<MenuLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(menuProp);

    RefPtr<LayoutWrapper> menuLayoutWrapper;
    RefPtr<LayoutWrapper> previewLayoutWrapper;
    SizeF totalSize = GetPreviewNodeAndMenuNodeTotalSize(parentNode, previewLayoutWrapper, menuLayoutWrapper);
    CHECK_NULL_VOID(menuLayoutWrapper);
    CHECK_NULL_VOID(previewLayoutWrapper);
    RefPtr<GeometryNode> menuGeometryNode = menuLayoutWrapper->GetGeometryNode();
    RefPtr<GeometryNode> previewGeometryNode = previewLayoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(menuGeometryNode);
    CHECK_NULL_VOID(previewGeometryNode);
    auto menuItemTotalHeight = GetMenuItemTotalHeight(menuLayoutWrapper);
    LayoutOtherDeviceLeftPreviewRightMenu(previewGeometryNode, menuGeometryNode, totalSize, menuItemTotalHeight);
    UpdateScrollAndColumnLayoutConstraint(previewLayoutWrapper, menuLayoutWrapper);
    auto previewSize = previewGeometryNode->GetMarginFrameSize();
    previewOffset_ = previewGeometryNode->GetFrameOffset();
    auto previewOffsetX = previewGeometryNode->GetFrameOffset().GetX();
    auto previewOffsetY = previewGeometryNode->GetFrameOffset().GetY();
    targetSize_ = previewSize * previewScale_;
    targetOffset_ = OffsetF(previewOffsetX + (previewSize.Width() - targetSize_.Width()) / 2,
        previewOffsetY + (previewSize.Height() - targetSize_.Height()) / 2);
    auto previewHostNode = previewLayoutWrapper->GetHostNode();
    CHECK_NULL_VOID(previewHostNode);
    auto renderContext = previewHostNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdatePosition(OffsetT<Dimension>(Dimension(previewOffsetX), Dimension(previewOffsetY)));

    auto menuHostNode = menuLayoutWrapper->GetHostNode();
    CHECK_NULL_VOID(menuHostNode);
    previewOriginOffset_ = targetCenterOffset_ - OffsetF(previewSize.Width() / 2, previewSize.Height() / 2);
    previewSize_ = previewSize;
    auto menuPattern = menuHostNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->SetPreviewOriginOffset(previewOriginOffset_);
}

void MenuLayoutAlgorithm::LayoutPreviewMenu(LayoutWrapper* layoutWrapper)
{
    auto paintProperty = GetPaintProperty(layoutWrapper);
    CHECK_NULL_VOID(paintProperty);
    paintProperty->UpdateEnableArrow(false);
    if (SystemProperties::GetDeviceType() == DeviceType::PHONE) {
        LayoutNormalPreviewMenu(layoutWrapper);
    } else {
        LayoutOtherDevicePreviewMenu(layoutWrapper);
    }
}

OffsetF MenuLayoutAlgorithm::FixMenuOriginOffset(float beforeAnimationScale, float afterAnimationScale)
{
    auto beforeScalePreviewOffset = OffsetF((previewSize_ * ((1.0f - beforeAnimationScale) / 2)).Width(),
        (previewSize_ * ((1.0f - beforeAnimationScale) / 2)).Height());
    auto afterScalePreviewOffset = OffsetF((previewSize_ * ((afterAnimationScale - 1.0f) / 2)).Width(),
        (previewSize_ * ((afterAnimationScale - 1.0f) / 2)).Height());
    auto scaleOffset = afterScalePreviewOffset + beforeScalePreviewOffset;
    float x = 0.0f;
    float y = 0.0f;
    switch (placement_) {
        case Placement::BOTTOM_LEFT:
        case Placement::LEFT_BOTTOM:
            x += scaleOffset.GetX();
            y -= scaleOffset.GetY();
            break;
        case Placement::TOP_RIGHT:
        case Placement::RIGHT_TOP:
            x -= scaleOffset.GetX();
            y += scaleOffset.GetY();
            break;
        case Placement::TOP_LEFT:
        case Placement::LEFT_TOP:
            x += scaleOffset.GetX();
            y += scaleOffset.GetY();
            break;
        case Placement::BOTTOM_RIGHT:
        case Placement::RIGHT_BOTTOM:
            x -= scaleOffset.GetX();
            y -= scaleOffset.GetY();
            break;
        case Placement::BOTTOM:
            y -= scaleOffset.GetY();
            break;
        case Placement::TOP:
            y += scaleOffset.GetY();
            break;
        case Placement::LEFT:
            x += scaleOffset.GetX();
            break;
        case Placement::RIGHT:
            x -= scaleOffset.GetX();
            break;
        default:
            x += scaleOffset.GetX();
            y -= scaleOffset.GetY();
            break;
    }
    return OffsetF(x, y);
}

void MenuLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto menuProp = DynamicCast<MenuLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(menuProp);
    auto menuNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);

    if (menuPattern->GetPreviewMode() != MenuPreviewMode::NONE) {
        LayoutPreviewMenu(layoutWrapper);
    }
    if (!menuPattern->IsSelectOverlayExtensionMenu() && !menuPattern->IsSelectOverlayCustomMenu()) {
        auto geometryNode = layoutWrapper->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        auto size = geometryNode->GetMarginFrameSize();
        bool didNeedArrow = GetIfNeedArrow(layoutWrapper, size);
        if (menuPattern->IsSelectMenu()) {
            ComputeMenuPositionByAlignType(menuProp, size);
            auto offset = ComputeMenuPositionByOffset(menuProp, geometryNode);
            position_ += offset;
        }
        auto menuPosition = MenuLayoutAvoidAlgorithm(menuProp, menuPattern, size, didNeedArrow);
        SetMenuPlacementForAnimation(layoutWrapper);
        arrowPosition_ = GetArrowPositionWithPlacement(size);
        if (didNeedArrow && arrowPlacement_ != Placement::NONE) {
            LayoutArrow(layoutWrapper);
        }
        geometryNode->SetFrameOffset(menuPosition);
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto menuTheme = pipeline->GetTheme<NG::MenuTheme>();
        CHECK_NULL_VOID(menuTheme);
        auto beforeAnimationScale = menuTheme->GetPreviewBeforeAnimationScale();
        auto afterAnimationScale = menuTheme->GetPreviewAfterAnimationScale();
        auto menuOriginOffset = menuPosition - (previewOffset_ - previewOriginOffset_) +
                                FixMenuOriginOffset(beforeAnimationScale, afterAnimationScale);
        menuPattern->SetOriginOffset(menuOriginOffset);
        auto previewScale = 1.0f;
        if (menuPattern->GetPreviewMode() == MenuPreviewMode::IMAGE &&
            !NearEqual(menuPattern->GetTargetSize().Width(), previewSize_.Width())) {
            previewScale = menuPattern->GetTargetSize().Width() / previewSize_.Width();
        }
        auto menuEndOffset = menuPosition -
            (previewOffset_ - previewOriginOffset_) + FixMenuOriginOffset(previewScale, afterAnimationScale);
        menuPattern->SetEndOffset(menuEndOffset);
        menuPattern->SetHasLaid(true);
    }

    // translate each option by the height of previous options
    OffsetF translate;
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        child->GetGeometryNode()->SetMarginFrameOffset(translate);
        child->Layout();
        translate += OffsetF(0, child->GetGeometryNode()->GetFrameSize().Height());
    }
}

void MenuLayoutAlgorithm::SetMenuPlacementForAnimation(LayoutWrapper* layoutWrapper)
{
    auto menu = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(menu);
    auto menuPattern = menu->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto menuWrapper = menuPattern->GetMenuWrapper();
    CHECK_NULL_VOID(menuWrapper);
    auto wrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(wrapperPattern);
    wrapperPattern->SetMenuPlacementAfterLayout(placement_);
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
    if (!propNeedArrow_ || !menuProp->GetMenuPlacement().has_value()) {
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

    return menuPattern->IsContextMenu() && !targetTag_.empty() && arrowInMenu_;
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

OffsetF MenuLayoutAlgorithm::MenuLayoutAvoidAlgorithm(const RefPtr<MenuLayoutProperty>& menuProp,
    const RefPtr<MenuPattern>& menuPattern, const SizeF& size, bool didNeedArrow)
{
    auto pipelineContext = GetCurrentPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, OffsetF(0, 0));
    CHECK_NULL_RETURN(menuProp, OffsetF(0, 0));
    CHECK_NULL_RETURN(menuPattern, OffsetF(0, 0));
    float x = 0.0f;
    float y = 0.0f;
    if (menuProp->GetMenuPlacement().has_value() && (targetSize_.Width() > 0.0 || targetSize_.Height() > 0.0)) {
        placement_ = menuProp->GetMenuPlacement().value();
        auto childOffset = GetChildPosition(size, didNeedArrow);
        x = childOffset.GetX();
        y = childOffset.GetY();
    } else {
        x = HorizontalLayout(size, position_.GetX(), menuPattern->IsSelectMenu()) + positionOffset_.GetX();
        y = VerticalLayout(size, position_.GetY(), menuPattern->IsContextMenu()) + positionOffset_.GetY();
        x = std::clamp(x, paddingStart_, wrapperSize_.Width() - size.Width() - paddingEnd_);
        float yMinAvoid = wrapperRect_.Top() + paddingTop_;
        float yMaxAvoid = wrapperRect_.Bottom() - paddingBottom_ - size.Height();
        y = std::clamp(y, yMinAvoid, yMaxAvoid);
    }
    return { x, y };
}

void MenuLayoutAlgorithm::UpdateConstraintWidth(LayoutWrapper* layoutWrapper, LayoutConstraintF& constraint)
{
    RefPtr<GridColumnInfo> columnInfo;
    columnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::MENU);
    auto menuNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    if (menuPattern && menuPattern->IsSelectOverlayExtensionMenu()) {
        columnInfo->GetParent()->BuildColumnWidth();
    } else {
        columnInfo->GetParent()->BuildColumnWidth(wrapperSize_.Width());
    }
    auto menuLayoutProperty = AceType::DynamicCast<MenuLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(menuLayoutProperty);
    // set max width
    const auto& padding = menuLayoutProperty->CreatePaddingAndBorder();
    auto maxHorizontalSpace = std::max(leftSpace_, rightSpace_) - 2.0f * padding.Width();
    auto maxWidth = static_cast<float>(columnInfo->GetWidth(GetMaxGridCounts(columnInfo)));
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        maxWidth = std::min(maxHorizontalSpace, maxWidth);
    }
    maxWidth = std::min(constraint.maxSize.Width(), maxWidth);
    constraint.maxSize.SetWidth(maxWidth);
}

void MenuLayoutAlgorithm::UpdateConstraintHeight(LayoutWrapper* layoutWrapper, LayoutConstraintF& constraint)
{
    auto pipelineContext = GetCurrentPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto menuPattern = layoutWrapper->GetHostNode()->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);

    float maxAvailableHeight = 0;
    if (hierarchicalParameters_) {
        auto displayAvailableRect = pipelineContext->GetDisplayAvailableRect();
        maxAvailableHeight = displayAvailableRect.Height();
    } else {
        auto safeAreaManager = pipelineContext->GetSafeAreaManager();
        CHECK_NULL_VOID(safeAreaManager);
        auto top = safeAreaManager->GetSystemSafeArea().top_.Length();
        auto bottom = safeAreaManager->GetSystemSafeArea().bottom_.Length();
        auto windowGlobalRect = pipelineContext->GetDisplayWindowRectInfo();
#if defined(PREVIEW)
        if (menuPattern->IsSelectOverlayCustomMenu()) {
            windowGlobalRect.SetHeight(constraint.maxSize.Height());
        }
#endif
        maxAvailableHeight = windowGlobalRect.Height() - top - bottom;
    }
    float maxSpaceHeight = maxAvailableHeight;
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        maxSpaceHeight = maxAvailableHeight * HEIGHT_CONSTRAINT_FACTOR;
    
        if (menuPattern->IsHeightModifiedBySelect()) {
            auto menuLayoutProps = AceType::DynamicCast<MenuLayoutProperty>(layoutWrapper->GetLayoutProperty());
            auto selectModifiedHeight = menuLayoutProps->GetSelectModifiedHeight().value();
            if (selectModifiedHeight < maxSpaceHeight) {
                maxSpaceHeight = selectModifiedHeight;
            }
        }
    }
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
    auto menuNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto options = menuPattern->GetOptions();
    if (options.empty()) {
        return;
    }
    auto optionConstraint = constraint;
    RefPtr<GridColumnInfo> columnInfo;
    columnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::MENU);
    columnInfo->GetParent()->BuildColumnWidth(wrapperSize_.Width());
    auto minWidth = static_cast<float>(columnInfo->GetWidth(MIN_GRID_COUNTS));
    optionConstraint.maxSize.MinusWidth(optionPadding_ * 2.0f);
    optionConstraint.minSize.SetWidth(minWidth - optionPadding_ * 2.0f);
    auto maxChildrenWidth = optionConstraint.minSize.Width();
    auto optionsLayoutWrapper = GetOptionsLayoutWrappper(layoutWrapper);
    for (const auto& optionWrapper : optionsLayoutWrapper) {
        optionWrapper->GetLayoutProperty()->ResetCalcMinSize();
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
float MenuLayoutAlgorithm::VerticalLayout(const SizeF &size, float position, bool isContextMenu)
{
    placement_ = Placement::BOTTOM;
    // can put menu below click point
    if (GreatOrEqual(bottomSpace_, size.Height())) {
        return position + margin_;
    }
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN) && isContextMenu) {
        if (LessNotEqual(bottomSpace_, size.Height()) && LessNotEqual(size.Height(), wrapperRect_.Height())) {
            return wrapperRect_.Bottom() - size.Height() - paddingBottom_;
        }
        // can't fit in screen, line up with top of the screen
        return wrapperRect_.Top() + paddingTop_;
    } else {
        float wrapperHeight = wrapperSize_.Height();
        // put menu above click point
        if (GreatOrEqual(topSpace_, size.Height())) {
            // menu show on top
            placement_ = Placement::TOP;
            return topSpace_ - size.Height() + margin_;
        }
        // line up bottom of menu with bottom of the screen
        if (LessNotEqual(size.Height(), wrapperHeight)) {
            return wrapperHeight - size.Height();
        }
        // can't fit in screen, line up with top of the screen
        return 0.0f;
    }
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
        if (isSelectMenu) {
            return position;
        }
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
        }
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

OffsetF MenuLayoutAlgorithm::GetMenuWrapperOffset(const LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_RETURN(layoutWrapper, OffsetF());
    auto menuNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(menuNode, OffsetF());
    return menuNode->GetParentGlobalOffsetDuringLayout();
}

void MenuLayoutAlgorithm::InitTargetSizeAndPosition(const LayoutWrapper* layoutWrapper, bool isContextMenu,
    const RefPtr<MenuPattern>& menuPattern)
{
    CHECK_NULL_VOID(layoutWrapper);
    CHECK_NULL_VOID(menuPattern);
    auto targetNode = FrameNode::GetFrameNode(targetTag_, targetNodeId_);
    CHECK_NULL_VOID(targetNode);
    auto geometryNode = targetNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto props = AceType::DynamicCast<MenuLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(props);
    if (props->GetIsRectInTargetValue(false)) {
        targetSize_ = props->GetTargetSizeValue(SizeF());
        targetOffset_ = props->GetMenuOffsetValue(OffsetF());
    } else {
        targetSize_ = geometryNode->GetFrameSize();
        targetOffset_ = targetNode->GetPaintRectOffset();
    }
    menuPattern->SetTargetSize(targetSize_);
    auto pipelineContext = GetCurrentPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    if ((isContextMenu || hierarchicalParameters_) && (targetTag_ != V2::SELECT_ETS_TAG)) {
        auto windowGlobalRect = pipelineContext->GetDisplayWindowRectInfo();
        float windowsOffsetX = static_cast<float>(windowGlobalRect.GetOffset().GetX());
        float windowsOffsetY = static_cast<float>(windowGlobalRect.GetOffset().GetY());
        targetOffset_ += OffsetF(windowsOffsetX, windowsOffsetY);

        OffsetF offset = GetMenuWrapperOffset(layoutWrapper);
        targetOffset_ -= offset;
        return;
    }

    auto windowManager = pipelineContext->GetWindowManager();
    auto isContainerModal = pipelineContext->GetWindowModal() == WindowModal::CONTAINER_MODAL && windowManager &&
                            windowManager->GetWindowMode() == WindowMode::WINDOW_MODE_FLOATING;
    if (isContainerModal) {
        auto newOffsetX = static_cast<float>(CONTAINER_BORDER_WIDTH.ConvertToPx()) +
                          static_cast<float>(CONTENT_PADDING.ConvertToPx());
        auto newOffsetY = static_cast<float>(CONTAINER_TITLE_HEIGHT.ConvertToPx()) +
                          static_cast<float>(CONTAINER_BORDER_WIDTH.ConvertToPx());
        targetOffset_ -= OffsetF(newOffsetX, newOffsetY);
    } else {
        OffsetF offset = GetMenuWrapperOffset(layoutWrapper);
        targetOffset_ -= offset;
    }
}

OffsetF MenuLayoutAlgorithm::FitToScreen(const OffsetF& position, const SizeF& childSize, bool didNeedArrow)
{
    OffsetF afterOffsetPosition;
    auto originPosition = position;

    if (NearEqual(positionOffset_, OffsetF(0.0f, 0.0f)) && (!didNeedArrow || arrowPlacement_ == Placement::NONE)) {
        afterOffsetPosition = AddTargetSpace(originPosition);
    } else {
        afterOffsetPosition = AddOffset(originPosition);
    }

    if (!CheckPosition(afterOffsetPosition, childSize)) {
        return OffsetF(0.0f, 0.0f);
    }

    return afterOffsetPosition;
}

OffsetF MenuLayoutAlgorithm::GetChildPosition(const SizeF& childSize, bool didNeedArrow)
{
    OffsetF bottomPosition = OffsetF(targetOffset_.GetX() + (targetSize_.Width() - childSize.Width()) / 2.0,
        targetOffset_.GetY() + targetSize_.Height() + targetSpace_);
    OffsetF topPosition = OffsetF(targetOffset_.GetX() + (targetSize_.Width() - childSize.Width()) / 2.0,
        targetOffset_.GetY() - childSize.Height() - targetSpace_);
    OffsetF defaultPosition = OffsetF(targetOffset_.GetX() + (targetSize_.Width() - childSize.Width()) / 2.0,
        targetOffset_.GetY() + (targetSize_.Height() - childSize.Height()) / 2.0);

    OffsetF childPosition;
    OffsetF position = defaultPosition;
    auto positionOffset = positionOffset_;
    std::vector<Placement> currentPlacementStates = PLACEMENT_STATES.find(Placement::BOTTOM_LEFT)->second;
    if (PLACEMENT_STATES.find(placement_) != PLACEMENT_STATES.end()) {
        currentPlacementStates = PLACEMENT_STATES.find(placement_)->second;
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
        position = FitToScreen(childPosition, childSize, didNeedArrow);
        if (NearEqual(position, OffsetF(0.0f, 0.0f))) {
            continue;
        }
        break;
    }
    if (placement_ == Placement::NONE) {
        position = GetAdjustPosition(currentPlacementStates, step, childSize, topPosition, bottomPosition);
        if (NearEqual(position, OffsetF(0.0f, 0.0f))) {
            position = defaultPosition;
        }
    }
    positionOffset_ = positionOffset;
    arrowPlacement_ = placement_;

    return position;
}

OffsetF MenuLayoutAlgorithm::GetAdjustPosition(std::vector<Placement>& currentPlacementStates, size_t step,
    const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition)
{
    OffsetF childPosition;
    OffsetF position;
    for (size_t i = 0, len = currentPlacementStates.size(); i < len;) {
        placement_ = currentPlacementStates[i];
        if (placement_ == Placement::NONE) {
            break;
        }
        childPosition = GetPositionWithPlacement(childSize, topPosition, bottomPosition);
        position = AdjustPosition(childPosition, childSize.Width(), childSize.Height(), targetSecurity_);
        if (NearEqual(position, OffsetF(0.0f, 0.0f))) {
            i += step;
            continue;
        }
        break;
    }
    return position;
}

OffsetF MenuLayoutAlgorithm::AdjustPosition(const OffsetF& position, float width, float height, float space)
{
    float xMax = 0.0f;
    float yMax = 0.0f;
    float xMin = paddingStart_;
    float yMin = std::max(1.0f, static_cast<float>(wrapperRect_.Top()) + paddingTop_);
    float wrapperBottom = wrapperRect_.Bottom();
    switch (placement_) {
        case Placement::LEFT_TOP:
        case Placement::LEFT_BOTTOM:
        case Placement::LEFT: {
            xMax = std::min(targetOffset_.GetX() - width - space, wrapperSize_.Width() - paddingEnd_ - width);
            yMax = wrapperBottom - height - paddingBottom_;
            break;
        }
        case Placement::RIGHT_TOP:
        case Placement::RIGHT_BOTTOM:
        case Placement::RIGHT: {
            xMin = std::max(targetOffset_.GetX() + targetSize_.Width() + space, paddingStart_);
            xMax = wrapperSize_.Width() - width - paddingEnd_;
            yMax = wrapperBottom - height - paddingBottom_;
            break;
        }
        case Placement::TOP_LEFT:
        case Placement::TOP_RIGHT:
        case Placement::TOP: {
            xMax = wrapperSize_.Width() - width - paddingEnd_;
            yMax = std::min(targetOffset_.GetY() - height - space, wrapperBottom - paddingBottom_ - height);
            break;
        }
        case Placement::BOTTOM_LEFT:
        case Placement::BOTTOM_RIGHT:
        case Placement::BOTTOM: {
            xMax = wrapperSize_.Width() - width - paddingEnd_;
            yMin = std::max(targetOffset_.GetY() + targetSize_.Height() + space, yMin);
            yMax = wrapperBottom - height - paddingBottom_;
            break;
        }
        default:
            break;
    }
    if (xMax < xMin || yMax < yMin) {
        return OffsetF(0.0f, 0.0f);
    }
    auto x = std::clamp(position.GetX(), xMin, xMax);
    auto y = std::clamp(position.GetY(), yMin, yMax);
    return OffsetF(x, y);
}

OffsetF MenuLayoutAlgorithm::AddTargetSpace(const OffsetF& position)
{
    auto x = position.GetX();
    auto y = position.GetY();
    switch (placement_) {
        case Placement::BOTTOM_LEFT:
        case Placement::BOTTOM_RIGHT:
        case Placement::BOTTOM: {
            y += targetSecurity_;
            break;
        }
        case Placement::TOP_LEFT:
        case Placement::TOP_RIGHT:
        case Placement::TOP: {
            y -= targetSecurity_;
            break;
        }
        case Placement::RIGHT_TOP:
        case Placement::RIGHT_BOTTOM:
        case Placement::RIGHT: {
            x += targetSecurity_;
            break;
        }
        case Placement::LEFT_TOP:
        case Placement::LEFT_BOTTOM:
        case Placement::LEFT: {
            x -= targetSecurity_;
            break;
        }
        default: {
            y += targetSecurity_;
            break;
        }
    }
    return OffsetF(x, y);
}

OffsetF MenuLayoutAlgorithm::AddOffset(const OffsetF& position)
{
    auto x = position.GetX();
    auto y = position.GetY();
    switch (placement_) {
        case Placement::BOTTOM_LEFT:
        case Placement::BOTTOM_RIGHT:
        case Placement::BOTTOM: {
            x += positionOffset_.GetX();
            y += positionOffset_.GetY();
            break;
        }
        case Placement::TOP_LEFT:
        case Placement::TOP_RIGHT:
        case Placement::TOP: {
            x += positionOffset_.GetX();
            y -= positionOffset_.GetY();
            break;
        }
        case Placement::RIGHT_TOP:
        case Placement::RIGHT_BOTTOM:
        case Placement::RIGHT: {
            x += positionOffset_.GetX();
            y += positionOffset_.GetY();
            break;
        }
        case Placement::LEFT_TOP:
        case Placement::LEFT_BOTTOM:
        case Placement::LEFT: {
            x -= positionOffset_.GetX();
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

bool MenuLayoutAlgorithm::CheckPositionInPlacementRect(
    const Rect& rect, const OffsetF& position, const SizeF& childSize)
{
    auto x = position.GetX();
    auto y = position.GetY();
    if (x < rect.Left() || (x + childSize.Width()) > rect.Right() || y < rect.Top() ||
        (y + childSize.Height()) > rect.Bottom()) {
        return false;
    }
    return true;
}

bool MenuLayoutAlgorithm::CheckPosition(const OffsetF& position, const SizeF& childSize)
{
    float targetOffsetX = targetOffset_.GetX();
    float targetOffsetY = targetOffset_.GetY();
    float yAvoid = wrapperRect_.Top() + paddingTop_;
    Rect rect;
    switch (placement_) {
        case Placement::BOTTOM_LEFT:
        case Placement::BOTTOM_RIGHT:
        case Placement::BOTTOM: {
            auto y = std::max(targetOffsetY + targetSize_.Height(), yAvoid);
            auto height = std::min(
                static_cast<float>(wrapperRect_.Bottom()) - paddingBottom_ - targetOffsetY - targetSize_.Height(),
                wrapperSize_.Height() - paddingBottom_ - paddingTop_);
            rect.SetRect(
                paddingStart_, y, wrapperSize_.Width() - paddingEnd_ - paddingStart_, height);
            break;
        }
        case Placement::TOP_LEFT:
        case Placement::TOP_RIGHT:
        case Placement::TOP: {
            auto height = std::min(targetOffsetY - yAvoid, wrapperSize_.Height() - paddingTop_ - paddingBottom_);
            rect.SetRect(paddingStart_, yAvoid, wrapperSize_.Width() - paddingEnd_ - paddingStart_, height);
            break;
        }
        case Placement::RIGHT_TOP:
        case Placement::RIGHT_BOTTOM:
        case Placement::RIGHT: {
            auto x = std::max(targetOffsetX + targetSize_.Width(), paddingStart_);
            auto width = std::min(wrapperSize_.Width() - targetOffsetX - targetSize_.Width() - paddingEnd_,
                wrapperSize_.Width() - paddingStart_ - paddingEnd_);
            rect.SetRect(x, yAvoid, width, wrapperSize_.Height() - paddingBottom_ - paddingTop_);
            break;
        }
        case Placement::LEFT_TOP:
        case Placement::LEFT_BOTTOM:
        case Placement::LEFT: {
            auto width = std::min(
                targetOffsetX - paddingStart_, wrapperSize_.Width() - paddingEnd_ - paddingStart_);
            rect.SetRect(paddingStart_, yAvoid, width, wrapperSize_.Height() - paddingBottom_ - paddingTop_);
            break;
        }
        default:
            return false;
    }
    return CheckPositionInPlacementRect(rect, position, childSize);
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

void MenuLayoutAlgorithm::InitHierarchicalParameters(bool isShowInSubWindow)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    auto expandDisplay = theme->GetExpandDisplay();
    if (expandDisplay && !isShowInSubWindow) {
        hierarchicalParameters_ = false;
        return;
    }
    hierarchicalParameters_ = expandDisplay;
}

} // namespace OHOS::Ace::NG
