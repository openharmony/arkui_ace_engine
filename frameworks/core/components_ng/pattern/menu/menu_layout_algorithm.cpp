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

#include "core/common/ace_engine.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
namespace OHOS::Ace::NG {

namespace {
constexpr uint32_t MIN_GRID_COUNTS = 2;
constexpr uint32_t GRID_COUNTS_4 = 4;
constexpr uint32_t GRID_COUNTS_6 = 6;
constexpr uint32_t GRID_COUNTS_8 = 8;
constexpr uint32_t GRID_COUNTS_12 = 12;
constexpr size_t ALIGNMENT_STEP_OFFSET = 2;
constexpr float HEIGHT_CONSTRAINT_FACTOR = 0.8;
constexpr float ARROW_WIDTH_FACTOR = 2.0;
constexpr double HALF = 2.0;

constexpr Dimension ARROW_RADIUS = 2.0_vp;
constexpr Dimension ARROW_P1_OFFSET_X = 8.0_vp;
constexpr Dimension ARROW_P2_OFFSET_X = 1.5_vp;
constexpr Dimension ARROW_P1_OFFSET_Y = 8.0_vp;
constexpr Dimension ARROW_P2_OFFSET_Y = 0.68_vp;

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

RefPtr<NG::MenuTheme> GetMenuTheme(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    return pipelineContext->GetTheme<NG::MenuTheme>();
}
} // namespace

MenuLayoutAlgorithm::MenuLayoutAlgorithm(int32_t id, const std::string& tag,
    const std::optional<OffsetF>& lastPosition) : targetNodeId_(id), targetTag_(tag)
{
    if (lastPosition.has_value()) {
        lastPosition_ = lastPosition;
    }
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

    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    targetSecurity_ = static_cast<float>(theme->GetMenuTargetSecuritySpace().ConvertToPx());
}

MenuLayoutAlgorithm::~MenuLayoutAlgorithm()
{
    placementFuncMap_.clear();
    setHorizontal_.clear();
    setVertical_.clear();
}

void MenuLayoutAlgorithm::ModifyPreviewMenuPlacement(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto props = AceType::DynamicCast<MenuLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(props);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto menuTheme = pipeline->GetTheme<NG::MenuTheme>();
    CHECK_NULL_VOID(menuTheme);
    auto hasPlacement = props->GetMenuPlacement().has_value();
    if (!hasPlacement) {
        if (menuTheme->GetNormalPlacement() &&
            SystemProperties::GetDeviceOrientation() == DeviceOrientation::PORTRAIT) {
            // for Phone with PORTRAIT orientation, default placement is BOTTOM_LEFT
            placement_ = Placement::BOTTOM_LEFT;
            props->UpdateMenuPlacement(placement_);
        } else {
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
    auto menuTheme = GetMenuTheme(menuNode);
    CHECK_NULL_VOID(menuTheme);
    auto beforeAnimationScale = menuPattern->GetPreviewBeforeAnimationScale();
    auto afterAnimationScale = menuPattern->GetPreviewAfterAnimationScale();
    dumpInfo_.previewBeginScale =
        LessOrEqual(beforeAnimationScale, 0.0f) ? menuTheme->GetPreviewBeforeAnimationScale() : beforeAnimationScale;
    dumpInfo_.previewEndScale =
        LessOrEqual(afterAnimationScale, 0.0f) ? menuTheme->GetPreviewAfterAnimationScale() : afterAnimationScale;
    previewScale_ = LessOrEqual(afterAnimationScale, 0.0f) ? previewScale_ : afterAnimationScale;
    position_ = props->GetMenuOffset().value_or(OffsetF());
    dumpInfo_.globalLocation = position_;
    // user-set offset
    positionOffset_ = props->GetPositionOffset().value_or(OffsetF());
    dumpInfo_.offset = positionOffset_;
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        InitializePaddingAPI12(layoutWrapper);
    } else {
        InitializePadding(layoutWrapper);
    }
    InitializeParam(menuPattern);
    if (canExpandCurrentWindow_ && isExpandDisplay_ && !menuPattern->IsSelectMenu()) {
        position_ += NG::OffsetF { displayWindowRect_.Left(), displayWindowRect_.Top() };
        TAG_LOGI(AceLogTag::ACE_MENU, "original postion after applying displayWindowRect : %{public}s",
            position_.ToString().c_str());
    }
    dumpInfo_.originPlacement =
        PlacementUtils::ConvertPlacementToString(props->GetMenuPlacement().value_or(Placement::NONE));
    placement_ = props->GetMenuPlacement().value_or(Placement::BOTTOM_LEFT);
    if (menuPattern->IsSubMenu() && Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        placement_ = props->GetMenuPlacement().value_or(Placement::BOTTOM_RIGHT);
    }
    ModifyPositionToWrapper(layoutWrapper, position_);
    if (menuPattern->GetPreviewMode() != MenuPreviewMode::NONE) {
        ModifyPreviewMenuPlacement(layoutWrapper);
    }
    dumpInfo_.defaultPlacement = PlacementUtils::ConvertPlacementToString(placement_);
    InitSpace(props, menuPattern);
    holdEmbeddedMenuPosition_ = HoldEmbeddedMenuPosition(layoutWrapper);
    auto previewRect = menuPattern->GetPreviewRect();
    previewOriginOffset_ = menuPattern->GetPreviewOriginOffset();
    previewOffset_ = previewRect.GetOffset();
    previewSize_ = previewRect.GetSize();
}

void MenuLayoutAlgorithm::InitializeParam(const RefPtr<MenuPattern>& menuPattern)
{
    auto pipelineContext = GetCurrentPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto safeAreaManager = pipelineContext->GetSafeAreaManager();
    CHECK_NULL_VOID(safeAreaManager);
    auto safeAreaInsets = safeAreaManager->GetSafeAreaWithoutProcess();
    auto top = safeAreaInsets.top_.Length();
    auto props = menuPattern->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(props);
    auto bottom = GetBottomBySafeAreaManager(safeAreaManager, props, menuPattern);
    auto menuWindowRect = GetMenuWindowRectInfo(menuPattern);
    float windowsOffsetX = static_cast<float>(menuWindowRect.GetOffset().GetX());
    float windowsOffsetY = static_cast<float>(menuWindowRect.GetOffset().GetY());
    SizeF windowGlobalSizeF(menuWindowRect.Width(), menuWindowRect.Height());
    float topSecurity = 0.0f;
    float bottomSecurity = 0.0f;
    if (SystemProperties::GetDeviceOrientation() == DeviceOrientation::PORTRAIT) {
        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            topSecurity = static_cast<float>(PORTRAIT_TOP_SECURITY_API12.ConvertToPx());
            bottomSecurity = static_cast<float>(PORTRAIT_BOTTOM_SECURITY_API12.ConvertToPx());
        } else {
            topSecurity = static_cast<float>(PORTRAIT_TOP_SECURITY.ConvertToPx());
            bottomSecurity = static_cast<float>(PORTRAIT_BOTTOM_SECURITY.ConvertToPx());
        }
    } else {
        topSecurity = static_cast<float>(LANDSCAPE_TOP_SECURITY.ConvertToPx());
        bottomSecurity = static_cast<float>(LANDSCAPE_BOTTOM_SECURITY.ConvertToPx());
    }
    if (canExpandCurrentWindow_) {
        param_.windowsOffsetX = windowsOffsetX;
        param_.windowsOffsetY = windowsOffsetY;
    } else {
        param_.windowsOffsetX = 0;
        param_.windowsOffsetY = 0;
    }
    param_.menuWindowRect = menuWindowRect;
    param_.windowGlobalSizeF = windowGlobalSizeF;
    param_.top = top;
    param_.bottom = bottom;
    param_.left = safeAreaInsets.left_.Length();
    param_.right = safeAreaInsets.right_.Length();
    param_.topSecurity = topSecurity;
    param_.bottomSecurity = bottomSecurity;
    param_.previewMenuGap = targetSecurity_;

    InitWrapperRect(props, menuPattern);
    InitializeLayoutRegionMargin(menuPattern);
}

void MenuLayoutAlgorithm::InitializeLayoutRegionMargin(const RefPtr<MenuPattern>& menuPattern)
{
    CHECK_NULL_VOID(menuPattern);
    auto menuWrapper = menuPattern->GetMenuWrapper();
    CHECK_NULL_VOID(menuWrapper);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);

    auto menuParam = menuWrapperPattern->GetMenuParam();
    isPreviewContainScale_ = menuParam.isPreviewContainScale;
    if (!menuParam.layoutRegionMargin.has_value()) {
        return;
    }

    auto marginProps = menuParam.layoutRegionMargin.value();
    float left = marginProps.start.has_value()
                     ? marginProps.start.value().GetDimension().ConvertToPxWithSize(wrapperSize_.Width())
                     : paddingStart_;
    float right = marginProps.end.has_value()
                      ? marginProps.end.value().GetDimension().ConvertToPxWithSize(wrapperSize_.Width())
                      : paddingEnd_;
    float top = marginProps.top.has_value()
                    ? marginProps.top.value().GetDimension().ConvertToPxWithSize(wrapperSize_.Height())
                    : param_.topSecurity;
    float bottom = marginProps.bottom.has_value()
                       ? marginProps.bottom.value().GetDimension().ConvertToPxWithSize(wrapperSize_.Height())
                       : param_.bottomSecurity;

    if (LessNotEqual(left + right, wrapperSize_.Width())) {
        paddingStart_ = left;
        paddingEnd_ = right;
        if (marginProps.start.has_value()) {
            layoutRegionMargin_.left = left;
        }
        if (marginProps.end.has_value()) {
            layoutRegionMargin_.right = right;
        }
    }

    if (LessNotEqual(top + bottom, wrapperSize_.Height())) {
        param_.topSecurity = top;
        param_.bottomSecurity = bottom;
        if (marginProps.top.has_value()) {
            layoutRegionMargin_.top = top;
        }
        if (marginProps.bottom.has_value()) {
            layoutRegionMargin_.bottom = bottom;
        }
    }
}

void MenuLayoutAlgorithm::InitWrapperRect(
    const RefPtr<MenuLayoutProperty>& props, const RefPtr<MenuPattern>& menuPattern)
{
    if (canExpandCurrentWindow_ && isExpandDisplay_ && !isTargetNodeInSubwindow_) {
        wrapperRect_ = param_.menuWindowRect;
        wrapperSize_ = SizeF(wrapperRect_.Width(), wrapperRect_.Height());
        dumpInfo_.wrapperRect = wrapperRect_;
        return;
    }
    wrapperRect_.SetRect(0, 0, param_.menuWindowRect.Width(), param_.menuWindowRect.Height());
    auto pipelineContext = GetCurrentPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto safeAreaManager = pipelineContext->GetSafeAreaManager();
    CHECK_NULL_VOID(safeAreaManager);
    // system safeArea(AvoidAreaType.TYPE_SYSTEM) only include status bar,now the bottom is 0
    auto safeAreaInsets = safeAreaManager->GetSafeAreaWithoutProcess();
    bottom_ = static_cast<double>(GetBottomBySafeAreaManager(safeAreaManager, props, menuPattern));
    top_ = static_cast<double>(safeAreaInsets.top_.Length());
    left_ = static_cast<double>(safeAreaInsets.left_.Length());
    right_ = static_cast<double>(safeAreaInsets.right_.Length());
    width_ = wrapperRect_.Width();
    height_ = wrapperRect_.Height();
    dumpInfo_.top = top_;
    dumpInfo_.bottom = bottom_;
    dumpInfo_.left = left_;
    dumpInfo_.right = right_;
    auto windowManager = pipelineContext->GetWindowManager();
    auto isContainerModal = pipelineContext->GetWindowModal() == WindowModal::CONTAINER_MODAL && windowManager &&
                            windowManager->GetWindowMode() == WindowMode::WINDOW_MODE_FLOATING;

    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        if (!canExpandCurrentWindow_ && isContainerModal) {
            LimitContainerModalMenuRect(width_, height_);
        }
        isHalfFoldHover_ = pipelineContext->IsHalfFoldHoverStatus();
        if (isHalfFoldHover_ && menuPattern->GetHoverMode()) {
            UpdateWrapperRectForHoverMode(props, menuPattern);
        } else {
            wrapperRect_.SetRect(left_, top_, width_ - left_ - right_, height_ - top_ - bottom_);
        }
    }
    wrapperSize_ = SizeF(wrapperRect_.Width(), wrapperRect_.Height());
    dumpInfo_.wrapperRect = wrapperRect_;
}

void MenuLayoutAlgorithm::UpdateWrapperRectForHoverMode(
    const RefPtr<MenuLayoutProperty>& props, const RefPtr<MenuPattern>& menuPattern)
{
    auto container = Container::CurrentSafelyWithCheck();
    CHECK_NULL_VOID(container);
    auto displayInfo = container->GetDisplayInfo();
    CHECK_NULL_VOID(displayInfo);
    auto foldCreaseRects = displayInfo->GetCurrentFoldCreaseRegion();
    int32_t creaseTop = 0;
    int32_t creaseBottom = 0;
    int32_t creaseHeight = 0;
    if (!foldCreaseRects.empty()) {
        auto foldCrease = foldCreaseRects.front();
        creaseTop = static_cast<int32_t>(foldCrease.Top());
        creaseBottom = static_cast<int32_t>(foldCrease.Bottom());
        creaseHeight = static_cast<int32_t>(foldCrease.Height());
    }
    float offsetY = 0;
    if (props->GetMenuPlacement().has_value()) {
        offsetY = targetOffset_.GetY();
    } else {
        offsetY = position_.GetY();
    }
    if (offsetY < creaseTop) {
        wrapperRect_.SetRect(left_, top_, width_ - left_ - right_, creaseTop - top_);
    } else if (offsetY > creaseBottom) {
        wrapperRect_.SetRect(left_, creaseBottom, width_ - left_ - right_, height_ - creaseBottom - bottom_);
    } else {
        wrapperRect_.SetRect(left_, top_, width_ - left_ - right_, height_ - top_ - bottom_);
    }
}

uint32_t MenuLayoutAlgorithm::GetBottomBySafeAreaManager(const RefPtr<SafeAreaManager>& safeAreaManager,
    const RefPtr<MenuLayoutProperty>& props, const RefPtr<MenuPattern>& menuPattern)
{
    auto safeAreaInsets = safeAreaManager->GetSafeAreaWithoutProcess();
    auto bottom = safeAreaInsets.bottom_.Length();
    auto keyboardHeight = safeAreaManager->GetKeyboardInset().Length();
    if ((menuPattern->IsSelectOverlayExtensionMenu() || menuPattern->IsSelectOverlayRightClickMenu()) &&
        GreatNotEqual(keyboardHeight, 0)) {
        bottom = keyboardHeight;
    }

    // Determine whether the menu is an AI menu
    if (props->GetIsRectInTargetValue(false)) {
        if (LessOrEqual(keyboardHeight, 0)) {
            keyboardHeight = safeAreaManager->GetkeyboardHeightConsideringUIExtension();
        }
        if (GreatNotEqual(keyboardHeight, 0)) {
            bottom = keyboardHeight;
        }
    }
    return bottom;
}

void MenuLayoutAlgorithm::InitSpace(const RefPtr<MenuLayoutProperty>& props, const RefPtr<MenuPattern>& menuPattern)
{
    auto targetSize = props->GetTargetSizeValue(SizeF());
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
        if (canExpandCurrentWindow_ || !Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
            topSpace_ = position_.GetY() - targetSize.Height() - paddingTop_ - wrapperRect_.Top();
            bottomSpace_ = wrapperRect_.Bottom() - position_.GetY() - paddingBottom_;
        } else {
            topSpace_ = position_.GetY() - wrapperRect_.Top() - paddingTop_;
            bottomSpace_ = wrapperRect_.Bottom() - position_.GetY() - paddingTop_;
        }
        leftSpace_ = position_.GetX() - paddingStart_;
        rightSpace_ = wrapperRect_.Right() - position_.GetX() - paddingEnd_;
    }
}

void MenuLayoutAlgorithm::InitializePadding(LayoutWrapper* layoutWrapper)
{
    auto menuNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    margin_ = static_cast<float>(theme->GetOutPadding().ConvertToPx());
    optionPadding_ = margin_;
    paddingStart_ = static_cast<float>(theme->GetDefaultPaddingStart().ConvertToPx());
    paddingEnd_ = static_cast<float>(theme->GetDefaultPaddingEnd().ConvertToPx());
    paddingTop_ = static_cast<float>(theme->GetDefaultPaddingTop().ConvertToPx());
    paddingBottom_ = static_cast<float>(theme->GetDefaultPaddingBottomFixed().ConvertToPx());
}

void MenuLayoutAlgorithm::InitializePaddingAPI12(LayoutWrapper* layoutWrapper)
{
    auto menuNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);

    margin_ = static_cast<float>(theme->GetOutPadding().ConvertToPx());
    optionPadding_ = margin_;
    if (!canExpandCurrentWindow_) {
        paddingStart_ = static_cast<float>(theme->GetMenuLargeMargin().ConvertToPx());
        paddingEnd_ = static_cast<float>(theme->GetMenuLargeMargin().ConvertToPx());
    } else {
        paddingStart_ = static_cast<float>(theme->GetMenuMediumMargin().ConvertToPx());
        paddingEnd_ = static_cast<float>(theme->GetMenuMediumMargin().ConvertToPx());
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
            canExpandCurrentWindow_) &&
        (targetTag_ != V2::SELECT_ETS_TAG)) {
        // no need to modify for context menu, because context menu wrapper is full screen.
        return;
    }
    // minus wrapper offset in floating window
    auto pipelineContext = GetCurrentPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto windowManager = pipelineContext->GetWindowManager();
    auto isContainerModal = pipelineContext->GetWindowModal() == WindowModal::CONTAINER_MODAL;
    if (isContainerModal) {
        wrapperOffset = OffsetF(0.0f, static_cast<float>(pipelineContext->GetCustomTitleHeight().ConvertToPx()));
        if (windowManager && windowManager->GetWindowMode() == WindowMode::WINDOW_MODE_FLOATING) {
            if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_SIXTEEN)) {
                wrapperOffset += OffsetF(static_cast<float>(CONTAINER_BORDER_WIDTH.ConvertToPx()),
                static_cast<float>(CONTAINER_BORDER_WIDTH.ConvertToPx()));
            } else {
                wrapperOffset += OffsetF(static_cast<float>((CONTAINER_BORDER_WIDTH + CONTENT_PADDING).ConvertToPx()),
                static_cast<float>(CONTAINER_BORDER_WIDTH.ConvertToPx()));
            }
        }
        position -= wrapperOffset;
    }
}

bool IsNodeOnRootTree(const RefPtr<FrameNode>& frameNode)
{
    auto parent = frameNode->GetParent();
    while (parent) {
        if (parent->GetTag() == V2::ROOT_ETS_TAG) {
            return true;
        }
        parent = parent->GetParent();
    }
    TAG_LOGW(AceLogTag::ACE_MENU, "node %{public}d not no root tree", frameNode->GetId());
    return false;
}

// Called to perform layout render node and child.
void MenuLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto targetNode = FrameNode::GetFrameNode(targetTag_, targetNodeId_);
    // if targetNode == nullptr, it means the menu is subMenu or multiMenu
    if (targetNode && !IsNodeOnRootTree(targetNode)) {
        TAG_LOGW(AceLogTag::ACE_MENU, "measure return because targetNode %{public}d not no root tree", targetNodeId_);
        return;
    }
    // initialize screen size and menu position
    CHECK_NULL_VOID(layoutWrapper);
    MenuDumpInfo dumpInfo;
    auto menuNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto menuLayoutProperty = AceType::DynamicCast<MenuLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(menuLayoutProperty);
    auto isContextMenu = menuPattern->IsContextMenu();
    auto isShowInSubWindow = menuLayoutProperty->GetShowInSubWindowValue(true) || isContextMenu;
    InitCanExpandCurrentWindow(isShowInSubWindow);
    Initialize(layoutWrapper);
    if (!targetTag_.empty()) {
        InitTargetSizeAndPosition(layoutWrapper, isContextMenu, menuPattern);
    }

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

    // The menu width child Constraint is added to the 2in1 device in API13
    UpdateChildConstraintByDevice(menuPattern, childConstraint, constraint.value());

    auto parentItem = menuPattern->GetParentMenuItem();
    CalculateIdealSize(layoutWrapper, childConstraint, padding, idealSize, parentItem);
}

bool MenuLayoutAlgorithm::CheckChildConstraintCondition(const RefPtr<MenuPattern>& menuPattern)
{
    CHECK_NULL_RETURN(menuPattern, false);
    CHECK_NULL_RETURN(Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_THIRTEEN), false);
    if (menuPattern->IsSubMenu()) {
        auto parentItem = menuPattern->GetParentMenuItem();
        CHECK_NULL_RETURN(parentItem, false);
        auto parentPattern = parentItem->GetPattern<MenuItemPattern>();
        CHECK_NULL_RETURN(parentPattern, false);
        auto expandingMode = parentPattern->GetExpandingMode();
        if (expandingMode == SubMenuExpandingMode::SIDE) {
            return true;
        }
        return false;
    }

    if (menuPattern->IsMenu() || menuPattern->IsContextMenu()) {
        return true;
    }
    return false;
}

void MenuLayoutAlgorithm::UpdateChildConstraintByDevice(const RefPtr<MenuPattern>& menuPattern,
    LayoutConstraintF& childConstraint, const LayoutConstraintF& layoutConstraint)
{
    CHECK_NULL_VOID(menuPattern);

    // only 2in1 device has restrictions on the menu width in API13
    if (!CheckChildConstraintCondition(menuPattern)) {
        return;
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);

    auto expandDisplay = theme->GetExpandDisplay();
    CHECK_NULL_VOID(expandDisplay);

    auto menuMinWidth = theme->GetMenuMinWidth().ConvertToPx();
    auto menuDefaultWidth = theme->GetMenuDefaultWidth().ConvertToPx();
    auto menuMaxWidth = theme->GetMenuMaxWidthRatio() * SystemProperties::GetDeviceWidth();
    double minWidth = 0.0f;
    double maxWidth = 0.0f;

    auto firstMenu = menuPattern->GetFirstInnerMenu();
    CHECK_NULL_VOID(firstMenu);
    auto layoutProperty = firstMenu->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->HasMenuWidth()) {
        auto menuWidth = layoutProperty->GetMenuWidthValue();
        auto menuWidthPX = (menuWidth.Unit() == DimensionUnit::PERCENT) ?
            menuWidth.Value() * layoutConstraint.percentReference.Width() : menuWidth.ConvertToPx();
        if (LessNotEqual(menuWidthPX, menuMinWidth) || GreatNotEqual(menuWidthPX, menuMaxWidth)) {
            minWidth = menuDefaultWidth;
            maxWidth = menuMaxWidth;
        } else {
            minWidth = menuWidthPX;
            maxWidth = menuWidthPX;
        }
    } else {
        minWidth = menuDefaultWidth;
        maxWidth = menuMaxWidth;
    }
    childConstraint.minSize.SetWidth(minWidth);
    childConstraint.maxSize.SetWidth(maxWidth);
}

void MenuLayoutAlgorithm::CalculateIdealSize(LayoutWrapper* layoutWrapper,
    LayoutConstraintF& childConstraint, PaddingPropertyF padding, SizeF& idealSize,
    RefPtr<FrameNode> parentItem)
{
    if (parentItem != nullptr) {
        auto parentPattern = parentItem->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(parentPattern);
        auto expandingMode = parentPattern->GetExpandingMode();
        if (expandingMode == SubMenuExpandingMode::STACK) {
            auto parentPattern = parentItem->GetPattern<MenuItemPattern>();
            CHECK_NULL_VOID(parentPattern);
            auto parentMenu = parentPattern->GetMenu();
            auto parentWidth = parentMenu->GetGeometryNode()->GetFrameSize().Width();
            childConstraint.minSize.SetWidth(parentWidth);
            childConstraint.maxSize.SetWidth(parentWidth);
            childConstraint.selfIdealSize.SetWidth(parentWidth);
        }
    }

    float idealHeight = 0.0f;
    float idealWidth = 0.0f;
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pattern = host->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(pattern);
    std::list<RefPtr<LayoutWrapper>> builderChildList;
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        if (pattern->UseContentModifier()) {
            if (child->GetHostNode()->GetId() != pattern->GetBuilderId()) {
                child->GetGeometryNode()->Reset();
                child->GetGeometryNode()->SetContentSize(SizeF());
            } else {
                child->Measure(childConstraint);
                builderChildList.push_back(child);
            }
            BoxLayoutAlgorithm::PerformMeasureSelfWithChildList(layoutWrapper, builderChildList);
        } else {
            child->Measure(childConstraint);
        }
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
    childMarginFrameSize_ = idealSize;
}

void MenuLayoutAlgorithm::CheckPreviewConstraint(const RefPtr<FrameNode>& frameNode, const Rect& menuWindowRect)
{
    CHECK_NULL_VOID(frameNode &&
        (frameNode->GetTag() == V2::MENU_PREVIEW_ETS_TAG || frameNode->GetTag() == V2::FLEX_ETS_TAG));
    auto geometryNode = frameNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);

    auto maxWidth = wrapperSize_.Width();
    if (layoutRegionMargin_.left.has_value() || layoutRegionMargin_.right.has_value()) {
        maxWidth = std::max(0.0f, wrapperSize_.Width() - paddingStart_ - paddingEnd_) / previewScale_;
    } else {
        RefPtr<GridColumnInfo> columnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::MENU);
        CHECK_NULL_VOID(columnInfo);
        auto parent = columnInfo->GetParent();
        CHECK_NULL_VOID(parent);
        parent->BuildColumnWidth(std::min(menuWindowRect.Width(), menuWindowRect.Height()));
        maxWidth = static_cast<float>(columnInfo->GetWidth(GRID_COUNTS_4)) / previewScale_;
    }

    auto frameSize = geometryNode->GetMarginFrameSize();
    if (!isPreviewContainScale_) {
        static SizeF previewSize;
        static int32_t hostId = -1;
        if (previewSize == SizeF(0.0f, 0.0f) || hostId != frameNode->GetId()) {
            previewSize = frameSize;
            hostId = frameNode->GetId();
        } else {
            frameSize = previewSize;
        }
    }

    if (LessOrEqual(frameSize.Width(), maxWidth)) {
        geometryNode->SetFrameSize(SizeF(frameSize.Width(), frameSize.Height()));
    } else if (isPreviewContainScale_) {
        geometryNode->SetFrameSize(SizeF(maxWidth, frameSize.Height() * (maxWidth / frameSize.Width())));
    } else {
        geometryNode->SetFrameSize(SizeF(maxWidth, frameSize.Height()));
    }
}

void MenuLayoutAlgorithm::CheckPreviewSize(
    const RefPtr<LayoutWrapper>& previewLayoutWrapper, const RefPtr<MenuPattern>& menuPattern)
{
    CHECK_NULL_VOID(previewLayoutWrapper && menuPattern);
    auto previewNode = previewLayoutWrapper->GetHostNode();
    CHECK_NULL_VOID(previewNode);
    auto tag = previewNode->GetTag();
    auto isPreview = tag == V2::IMAGE_ETS_TAG || tag == V2::MENU_PREVIEW_ETS_TAG || tag == V2::FLEX_ETS_TAG;
    CHECK_NULL_VOID(isPreview);

    auto previewGeometryNode = previewNode->GetGeometryNode();
    CHECK_NULL_VOID(previewGeometryNode);
    auto previewSize = previewGeometryNode->GetMarginFrameSize();

    if (menuPattern->GetIsFirstShow()) {
        menuPattern->SetPreviewIdealSize(previewSize);
        return;
    }

    if (previewSize != menuPattern->GetPreviewIdealSize()) {
        auto menuWrapper = menuPattern->GetMenuWrapper();
        CHECK_NULL_VOID(menuWrapper);
        auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
        CHECK_NULL_VOID(menuWrapperPattern);
        auto constraint = menuWrapperPattern->GetChildLayoutConstraint();
        CHECK_NULL_VOID(constraint.maxSize.IsPositive() && constraint.percentReference.IsPositive());
        auto layoutProperty = previewLayoutWrapper->GetLayoutProperty();
        CHECK_NULL_VOID(layoutProperty);
        layoutProperty->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
        previewLayoutWrapper->Measure(constraint);
        menuPattern->SetPreviewIdealSize(previewGeometryNode->GetMarginFrameSize());
    }
}

void MenuLayoutAlgorithm::GetPreviewNodeTotalSize(const RefPtr<LayoutWrapper>& child, const Rect& menuWindowRect,
    RefPtr<LayoutWrapper>& previewLayoutWrapper, SizeF& size, const RefPtr<LayoutWrapper>& menuLayoutWrapper)
{
    CHECK_NULL_VOID(child);
    auto hostNode = child->GetHostNode();
    auto geometryNode = child->GetGeometryNode();
    if (!hostNode || !geometryNode) {
        return;
    }

    bool isImageNode = hostNode->GetTag() == V2::IMAGE_ETS_TAG;
    bool isPreviewNode = hostNode->GetTag() == V2::MENU_PREVIEW_ETS_TAG;
    bool isFlexNode = hostNode->GetTag() == V2::FLEX_ETS_TAG;
    if (!isPreviewNode && !isImageNode && !isFlexNode) {
        return;
    }

    CHECK_NULL_VOID(menuLayoutWrapper);
    auto menuNode = menuLayoutWrapper->GetHostNode();
    CHECK_NULL_VOID(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    CheckPreviewSize(child, menuPattern);

    if (isImageNode && menuPattern->GetIsShowHoverImage()) {
        return;
    }

    auto frameSize = geometryNode->GetMarginFrameSize();
    if (isPreviewNode || isFlexNode) {
        CheckPreviewConstraint(hostNode, menuWindowRect);
    } else {
        geometryNode->SetFrameSize(frameSize);
    }
    frameSize = geometryNode->GetMarginFrameSize() * previewScale_;
    auto widthLeftSpace = menuWindowRect.Width() - paddingStart_ - paddingEnd_;
    if (GreatNotEqual(frameSize.Width(), widthLeftSpace)) {
        auto unitSpace = widthLeftSpace / frameSize.Width() / previewScale_;
        geometryNode->SetFrameSize(SizeF(widthLeftSpace / previewScale_, unitSpace * frameSize.Height()));
        frameSize = geometryNode->GetMarginFrameSize() * previewScale_;
    }
    previewLayoutWrapper = child;
    size += frameSize;
}

SizeF MenuLayoutAlgorithm::GetPreviewNodeAndMenuNodeTotalSize(const RefPtr<FrameNode>& frameNode,
    RefPtr<LayoutWrapper>& previewLayoutWrapper, RefPtr<LayoutWrapper>& menuLayoutWrapper)
{
    SizeF size;
    CHECK_NULL_RETURN(frameNode, size);
    auto pipelineContext = GetCurrentPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, size);
    for (auto& child : frameNode->GetAllChildrenWithBuild()) {
        auto hostNode = child->GetHostNode();
        auto geometryNode = child->GetGeometryNode();
        if (!hostNode || !geometryNode) {
            continue;
        }
        GetPreviewNodeTotalSize(child, param_.menuWindowRect, previewLayoutWrapper, size, menuLayoutWrapper);
        auto menuPattern = hostNode->GetPattern<MenuPattern>();
        if (hostNode->GetTag() == V2::MENU_ETS_TAG && menuPattern && !menuPattern->IsSubMenu()) {
            menuLayoutWrapper = child;
            size += geometryNode->GetMarginFrameSize();
        }
    }
    return size;
}

void MenuLayoutAlgorithm::LayoutNormalTopPreviewBottomMenuLessThan(
    const RefPtr<GeometryNode>& previewGeometryNode, const RefPtr<GeometryNode>& menuGeometryNode, SizeF& totalSize)
{
    CHECK_NULL_VOID(previewGeometryNode);
    CHECK_NULL_VOID(menuGeometryNode);

    OffsetF center(
        targetOffset_.GetX() + targetSize_.Width() / HALF, targetOffset_.GetY() + targetSize_.Height() / HALF);
    targetCenterOffset_ = center;
    auto previewSize = previewGeometryNode->GetMarginFrameSize() * previewScale_;
    OffsetF offset(center.GetX() - previewSize.Width() / HALF,
        std::min<float>(center.GetY() - previewSize.Height() / HALF, param_.windowGlobalSizeF.Height() -
                                                                         param_.bottomSecurity - param_.bottom -
                                                                         totalSize.Height() - param_.previewMenuGap));
    auto x = std::clamp(offset.GetX(), static_cast<float>(wrapperRect_.Left()) + paddingStart_,
        static_cast<float>(wrapperRect_.Right()) - paddingEnd_ - previewSize.Width());
    auto y = std::clamp(offset.GetY(), static_cast<float>(wrapperRect_.Top()) + param_.topSecurity,
        static_cast<float>(wrapperRect_.Bottom()) - param_.bottomSecurity - previewSize.Height());
    x = x + (previewSize.Width() - previewSize.Width() / previewScale_) / HALF;
    y = y + (previewSize.Height() - previewSize.Height() / previewScale_) / HALF;
    previewGeometryNode->SetMarginFrameOffset(OffsetF(x, y));
}

void MenuLayoutAlgorithm::LayoutNormalTopPreviewBottomMenuGreateThan(
    const RefPtr<GeometryNode>& previewGeometryNode, const RefPtr<GeometryNode>& menuGeometryNode, SizeF& totalSize)
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
        if (GreatNotEqual(param_.menuItemTotalHeight, previewHalfHeight)) {
            menuGeometryNode->SetFrameSize(SizeF(menuSize.Width(), previewHalfHeight));
            totalSize = SizeF(totalSize.Width(), previewHalfHeight + previewSize.Height());
        } else {
            menuGeometryNode->SetFrameSize(SizeF(menuSize.Width(), param_.menuItemTotalHeight));
            totalSize = SizeF(totalSize.Width(), param_.menuItemTotalHeight + previewSize.Height());
        }
    }

    auto heightLeftSpace = wrapperRect_.Height() - param_.topSecurity - param_.bottomSecurity - param_.previewMenuGap;
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
    auto x = std::clamp(offset.GetX(), static_cast<float>(wrapperRect_.Left()) + paddingStart_,
        static_cast<float>(wrapperRect_.Right()) - paddingEnd_ - previewSize.Width());
    auto y = std::clamp(offset.GetY(), static_cast<float>(wrapperRect_.Top()) + param_.topSecurity,
        static_cast<float>(wrapperRect_.Bottom()) - param_.bottomSecurity - previewSize.Height());
    x = x + (previewSize.Width() - previewSize.Width() / previewScale_) / 2;
    y = y + (previewSize.Height() - previewSize.Height() / previewScale_) / 2;
    previewGeometryNode->SetMarginFrameOffset(OffsetF(x, y));
}

void MenuLayoutAlgorithm::LayoutNormalTopPreviewBottomMenu(const RefPtr<GeometryNode>& previewGeometryNode,
    const RefPtr<GeometryNode>& menuGeometryNode, SizeF& totalSize, float menuItemTotalHeight)
{
    CHECK_NULL_VOID(previewGeometryNode);
    CHECK_NULL_VOID(menuGeometryNode);
    param_.menuItemTotalHeight = menuItemTotalHeight;
    auto pipelineContext = GetCurrentPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    if (LessNotEqual(totalSize.Height() + targetSecurity_,
        wrapperRect_.Height() - paddingTop_ - paddingBottom_ - param_.topSecurity - param_.bottomSecurity)) {
        LayoutNormalTopPreviewBottomMenuLessThan(previewGeometryNode, menuGeometryNode, totalSize);
    } else {
        LayoutNormalTopPreviewBottomMenuGreateThan(previewGeometryNode, menuGeometryNode, totalSize);
    }
    auto previewSize = previewGeometryNode->GetMarginFrameSize();
    auto securityHeight = wrapperRect_.Height() - param_.topSecurity - param_.bottomSecurity;
    if (GreatNotEqual(param_.windowGlobalSizeF.Height(), param_.menuWindowRect.Height()) &&
        GreatNotEqual(previewSize.Height(), securityHeight)) {
        previewGeometryNode->SetFrameSize(SizeF(previewSize.Width(), securityHeight));
    }
}

void MenuLayoutAlgorithm::LayoutNormalBottomPreviewTopMenuLessThan(
    const RefPtr<GeometryNode>& previewGeometryNode, const RefPtr<GeometryNode>& menuGeometryNode, SizeF& totalSize)
{
    CHECK_NULL_VOID(previewGeometryNode);
    CHECK_NULL_VOID(menuGeometryNode);

    OffsetF center(targetOffset_.GetX() + targetSize_.Width() / 2, targetOffset_.GetY() + targetSize_.Height() / 2);
    targetCenterOffset_ = center;
    auto previewSize = previewGeometryNode->GetMarginFrameSize() * previewScale_;
    OffsetF offset(center.GetX() - previewSize.Width() / 2,
        std::max<float>(center.GetY() - previewSize.Height() / 2,
            param_.top + param_.topSecurity + totalSize.Height() - previewSize.Height() + param_.previewMenuGap));
    auto x = std::clamp(offset.GetX(), static_cast<float>(wrapperRect_.Left()) + paddingStart_,
        static_cast<float>(wrapperRect_.Right()) - previewSize.Width() - paddingEnd_);
    auto y = std::clamp(offset.GetY(), static_cast<float>(wrapperRect_.Top()) + param_.topSecurity,
        static_cast<float>(wrapperRect_.Bottom()) - param_.bottomSecurity - previewSize.Height());
    x = x + (previewSize.Width() - previewSize.Width() / previewScale_) / 2;
    y = y + (previewSize.Height() - previewSize.Height() / previewScale_) / 2;
    previewGeometryNode->SetMarginFrameOffset(OffsetF(x, y));
}

void MenuLayoutAlgorithm::LayoutNormalBottomPreviewTopMenuGreateThan(
    const RefPtr<GeometryNode>& previewGeometryNode, const RefPtr<GeometryNode>& menuGeometryNode, SizeF& totalSize)
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
        if (GreatNotEqual(param_.menuItemTotalHeight, previewHalfHeight)) {
            menuGeometryNode->SetFrameSize(SizeF(menuSize.Width(), previewHalfHeight));
            totalSize = SizeF(totalSize.Width(), previewHalfHeight + previewSize.Height());
        } else {
            menuGeometryNode->SetFrameSize(SizeF(menuSize.Width(), param_.menuItemTotalHeight));
            totalSize = SizeF(totalSize.Width(), param_.menuItemTotalHeight + previewSize.Height());
        }
    }

    auto heightLeftSpace = param_.windowGlobalSizeF.Height() - param_.top - param_.topSecurity - param_.bottom -
                           param_.bottomSecurity - param_.previewMenuGap;
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
        param_.windowGlobalSizeF.Height() - param_.bottomSecurity - param_.bottom - previewSize.Height());

    auto x = std::clamp(offset.GetX(), static_cast<float>(wrapperRect_.Left()) + paddingStart_,
        static_cast<float>(wrapperRect_.Right()) - previewSize.Width() - paddingEnd_);
    auto y = std::clamp(offset.GetY(), static_cast<float>(wrapperRect_.Top()) + param_.topSecurity,
        static_cast<float>(wrapperRect_.Bottom()) - param_.bottomSecurity - previewSize.Height());
    x = x + (previewSize.Width() - previewSize.Width() / previewScale_) / 2;
    y = y + (previewSize.Height() - previewSize.Height() / previewScale_) / 2;
    previewGeometryNode->SetMarginFrameOffset(OffsetF(x, y));
}

void MenuLayoutAlgorithm::LayoutNormalBottomPreviewTopMenu(const RefPtr<GeometryNode>& previewGeometryNode,
    const RefPtr<GeometryNode>& menuGeometryNode, SizeF& totalSize, float menuItemTotalHeight)
{
    CHECK_NULL_VOID(previewGeometryNode);
    CHECK_NULL_VOID(menuGeometryNode);
    param_.menuItemTotalHeight = menuItemTotalHeight;
    auto pipelineContext = GetCurrentPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    if (LessNotEqual(totalSize.Height() + targetSecurity_, param_.windowGlobalSizeF.Height() - param_.topSecurity -
                                                               param_.bottomSecurity - param_.top - param_.bottom)) {
        LayoutNormalBottomPreviewTopMenuLessThan(previewGeometryNode, menuGeometryNode, totalSize);
    } else {
        LayoutNormalBottomPreviewTopMenuGreateThan(previewGeometryNode, menuGeometryNode, totalSize);
    }
    auto previewSize = previewGeometryNode->GetMarginFrameSize();
    auto securityHeight =
        param_.menuWindowRect.Height() - param_.topSecurity - param_.top - param_.bottomSecurity - param_.bottom;
    if (GreatNotEqual(param_.windowGlobalSizeF.Height(), param_.menuWindowRect.Height()) &&
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
        geometryNode->SetFrameSize(SizeF(frameSize.Width(), frameSize.Height()));
        auto layoutProperty = child->GetLayoutProperty();
        CHECK_NULL_VOID(layoutProperty);
        auto constraint = layoutProperty->GetLayoutConstraint();
        if (constraint.has_value()) {
            constraint.value().maxSize.SetWidth(frameSize.Width());
            constraint.value().maxSize.SetHeight(frameSize.Height());
            constraint.value().selfIdealSize.UpdateSizeWithCheck(SizeF(frameSize.Width(), frameSize.Height()));
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

float MenuLayoutAlgorithm::CheckHorizontalLayoutPreviewOffsetX(
    const RefPtr<GeometryNode>& previewGeometryNode, const RefPtr<GeometryNode>& menuGeometryNode, float offsetX)
{
    if (SystemProperties::GetDeviceOrientation() != DeviceOrientation::LANDSCAPE) {
        return offsetX;
    }
    CHECK_NULL_RETURN(previewGeometryNode, offsetX);
    auto previewSize = previewGeometryNode->GetMarginFrameSize() * previewScale_;
    CHECK_NULL_RETURN(menuGeometryNode, offsetX);
    auto menuSize = menuGeometryNode->GetMarginFrameSize();
    // left menu right preview
    auto x_min = wrapperRect_.Left() + paddingStart_ + menuSize.Width() + targetSecurity_;
    // left preview right menu
    auto x_max = wrapperRect_.Right() - paddingEnd_ - menuSize.Width() - previewSize.Width() - targetSecurity_;
    auto needAvoid = GreatNotEqual(offsetX, x_max) && LessNotEqual(offsetX, x_min);
    return needAvoid ? x_max : offsetX;
}

void MenuLayoutAlgorithm::LayoutOtherDeviceLeftPreviewRightMenuLessThan(
    const RefPtr<GeometryNode>& previewGeometryNode, const RefPtr<GeometryNode>& menuGeometryNode, SizeF& totalSize)
{
    CHECK_NULL_VOID(previewGeometryNode);
    CHECK_NULL_VOID(menuGeometryNode);

    OffsetF targetCenterOffset(
        targetOffset_.GetX() + targetSize_.Width() / 2, targetOffset_.GetY() + targetSize_.Height() / 2);
    targetCenterOffset_ = targetCenterOffset;
    auto previewSize = previewGeometryNode->GetMarginFrameSize() * previewScale_;
    auto heightLeftSpace =
        param_.windowGlobalSizeF.Height() - param_.top - param_.topSecurity - param_.bottomSecurity - param_.bottom;
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
        SizeF(menuSize.Width(), std::min<float>(param_.menuItemTotalHeight, heightLeftSpace)));
    menuSize = menuGeometryNode->GetMarginFrameSize();
    auto offsetX = targetCenterOffset.GetX() - previewSize.Width() / 2;
    auto offsetY = std::min<float>(targetCenterOffset.GetY() - previewSize.Height() / 2,
        param_.windowGlobalSizeF.Height() - param_.bottomSecurity - param_.bottom - menuSize.Height());
    offsetX = CheckHorizontalLayoutPreviewOffsetX(previewGeometryNode, menuGeometryNode, offsetX);
    auto x = std::clamp(offsetX, static_cast<float>(wrapperRect_.Left()) + paddingStart_,
        static_cast<float>(wrapperRect_.Right()) - previewSize.Width() - paddingEnd_);
    auto y = std::clamp(offsetY, static_cast<float>(wrapperRect_.Top()) + param_.topSecurity,
        static_cast<float>(wrapperRect_.Bottom()) - param_.bottomSecurity - previewSize.Height());
    x = x + (previewSize.Width() - previewSize.Width() / previewScale_) / 2;
    y = y + (previewSize.Height() - previewSize.Height() / previewScale_) / 2;
    previewGeometryNode->SetMarginFrameOffset(OffsetF(x, y));
}

void MenuLayoutAlgorithm::LayoutOtherDeviceLeftPreviewRightMenuGreateThan(
    const RefPtr<GeometryNode>& previewGeometryNode, const RefPtr<GeometryNode>& menuGeometryNode, SizeF& totalSize)
{
    CHECK_NULL_VOID(previewGeometryNode);
    CHECK_NULL_VOID(menuGeometryNode);

    OffsetF targetCenterOffset(
        targetOffset_.GetX() + targetSize_.Width() / 2, targetOffset_.GetY() + targetSize_.Height() / 2);
    targetCenterOffset_ = targetCenterOffset;
    auto previewSize = previewGeometryNode->GetMarginFrameSize() * previewScale_;
    auto widthLeftSpace = param_.windowGlobalSizeF.Width() - paddingStart_ - paddingEnd_ - param_.previewMenuGap -
                          param_.left - param_.right;
    auto delta = totalSize.Width() - widthLeftSpace;
    if (GreatNotEqual(delta, 0.0f)) {
        auto unitSpace = delta / previewSize.Width();
        previewGeometryNode->SetFrameSize(SizeF((1 - unitSpace) * previewSize.Width() / previewScale_,
            (1 - unitSpace) * previewSize.Height() / previewScale_));
        totalSize = totalSize - SizeF(unitSpace * previewSize.Width(), unitSpace * previewSize.Height());
    }
    previewSize = previewGeometryNode->GetMarginFrameSize() * previewScale_;
    auto heightLeftSpace =
        param_.windowGlobalSizeF.Height() - param_.topSecurity - param_.top - param_.bottomSecurity - param_.bottom;
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
        SizeF(menuSize.Width(), std::min<float>(param_.menuItemTotalHeight, heightLeftSpace)));
    menuSize = menuGeometryNode->GetMarginFrameSize();
    auto offsetX = 0.0f;
    auto offsetY = std::min<float>(targetCenterOffset.GetY() - previewSize.Height() / 2,
        param_.windowGlobalSizeF.Height() - param_.bottomSecurity - param_.bottom - menuSize.Height());
    auto x = std::clamp(offsetX, static_cast<float>(wrapperRect_.Left()) + paddingStart_,
        static_cast<float>(wrapperRect_.Right()) - previewSize.Width() - paddingEnd_);
    auto y = std::clamp(offsetY, static_cast<float>(wrapperRect_.Top()) + param_.topSecurity,
        static_cast<float>(wrapperRect_.Bottom()) - param_.bottomSecurity - previewSize.Height());
    x = x + (previewSize.Width() - previewSize.Width() / previewScale_) / 2;
    y = y + (previewSize.Height() - previewSize.Height() / previewScale_) / 2;
    previewGeometryNode->SetMarginFrameOffset(OffsetF(x, y));
}

void MenuLayoutAlgorithm::LayoutOtherDeviceLeftPreviewRightMenu(const RefPtr<GeometryNode>& previewGeometryNode,
    const RefPtr<GeometryNode>& menuGeometryNode, SizeF& totalSize, float menuItemTotalHeight)
{
    CHECK_NULL_VOID(previewGeometryNode);
    CHECK_NULL_VOID(menuGeometryNode);
    param_.menuItemTotalHeight = menuItemTotalHeight;
    auto safeAreaWidth = param_.left + param_.right;
    auto maxRectRight = param_.windowGlobalSizeF.Width() - paddingStart_ - paddingEnd_ - safeAreaWidth;
    if (LessNotEqual(totalSize.Width() + targetSecurity_, maxRectRight)) {
        LayoutOtherDeviceLeftPreviewRightMenuLessThan(previewGeometryNode, menuGeometryNode, totalSize);
    } else {
        LayoutOtherDeviceLeftPreviewRightMenuGreateThan(previewGeometryNode, menuGeometryNode, totalSize);
    }
    auto previewSize = previewGeometryNode->GetMarginFrameSize();
    auto securityHeight =
        param_.menuWindowRect.Height() - param_.topSecurity - param_.top - param_.bottomSecurity - param_.bottom;
    if (GreatNotEqual(param_.windowGlobalSizeF.Height(), param_.menuWindowRect.Height()) &&
        GreatNotEqual(previewSize.Height(), securityHeight)) {
        previewGeometryNode->SetFrameSize(SizeF(previewSize.Width(), securityHeight));
    }
}

void MenuLayoutAlgorithm::LayoutPreviewMenu(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto paintProperty = GetPaintProperty(layoutWrapper);
    CHECK_NULL_VOID(paintProperty);
    paintProperty->UpdateEnableArrow(false);
    auto menuNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(menuNode);
    auto parentNode = AceType::DynamicCast<FrameNode>(menuNode->GetParent());
    CHECK_NULL_VOID(parentNode);
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
    if (placement_ == Placement::BOTTOM_LEFT || placement_ == Placement::BOTTOM ||
        placement_ == Placement::BOTTOM_RIGHT) {
        LayoutNormalTopPreviewBottomMenu(previewGeometryNode, menuGeometryNode, totalSize, menuItemTotalHeight);
    } else if (placement_ == Placement::TOP_LEFT || placement_ == Placement::TOP ||
               placement_ == Placement::TOP_RIGHT) {
        LayoutNormalBottomPreviewTopMenu(previewGeometryNode, menuGeometryNode, totalSize, menuItemTotalHeight);
    } else {
        LayoutOtherDeviceLeftPreviewRightMenu(previewGeometryNode, menuGeometryNode, totalSize, menuItemTotalHeight);
    }
    UpdateScrollAndColumnLayoutConstraint(previewLayoutWrapper, menuLayoutWrapper);
    UpdatePreviewPositionAndOffset(previewLayoutWrapper, menuLayoutWrapper);
}

void MenuLayoutAlgorithm::UpdatePreviewPositionAndOffset(
    RefPtr<LayoutWrapper>& previewLayoutWrapper, RefPtr<LayoutWrapper>& menuLayoutWrapper)
{
    CHECK_NULL_VOID(previewLayoutWrapper);
    CHECK_NULL_VOID(menuLayoutWrapper);
    RefPtr<GeometryNode> previewGeometryNode = previewLayoutWrapper->GetGeometryNode();
    RefPtr<GeometryNode> menuGeometryNode = menuLayoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(previewGeometryNode);
    CHECK_NULL_VOID(menuGeometryNode);

    auto previewSize = previewGeometryNode->GetMarginFrameSize();
    previewOffset_ = previewGeometryNode->GetFrameOffset();
    auto previewOffsetX = previewOffset_.GetX();
    auto previewOffsetY = previewOffset_.GetY();
    if (previewSize.IsPositive()) {
        targetSize_ = previewSize * previewScale_;
        targetOffset_ = OffsetF(previewOffsetX + (previewSize.Width() - targetSize_.Width()) / HALF,
            previewOffsetY + (previewSize.Height() - targetSize_.Height()) / HALF);
    }
    auto previewHostNode = previewLayoutWrapper->GetHostNode();
    CHECK_NULL_VOID(previewHostNode);
    auto renderContext = previewHostNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    auto menuHostNode = menuLayoutWrapper->GetHostNode();
    CHECK_NULL_VOID(menuHostNode);
    auto menuPattern = menuHostNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);

    // only update when current position is not equal to last position, otherwise animation will be interrupted
    if (previewOffset_ != menuPattern->GetPreviewRect().GetOffset()) {
        renderContext->UpdatePosition(OffsetT<Dimension>(Dimension(previewOffsetX), Dimension(previewOffsetY)));
    }

    previewOriginOffset_ = targetCenterOffset_ - OffsetF(previewSize.Width() / HALF, previewSize.Height() / HALF);
    previewSize_ = previewSize;
    menuPattern->SetPreviewOriginOffset(previewOriginOffset_);
    menuPattern->SetPreviewRect(RectF(previewOffset_, previewSize_));
}

OffsetF MenuLayoutAlgorithm::FixMenuOriginOffset(float beforeAnimationScale, float afterAnimationScale)
{
    auto beforeRate = (1.0f - beforeAnimationScale) / 2;
    auto beforeScalePreviewOffset = OffsetF((previewSize_ * beforeRate).Width(),
        (previewSize_ * beforeRate).Height());
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

void MenuLayoutAlgorithm::CalculateChildOffset(bool didNeedArrow)
{
    childOffset_.Reset();
    if (didNeedArrow) {
        switch (arrowPlacement_) {
            case Placement::RIGHT:
            case Placement::RIGHT_TOP:
            case Placement::RIGHT_BOTTOM:
                childOffset_.SetX(ARROW_HIGHT.ConvertToPx());
                break;
            case Placement::BOTTOM:
            case Placement::BOTTOM_LEFT:
            case Placement::BOTTOM_RIGHT:
                childOffset_.SetY(ARROW_HIGHT.ConvertToPx());
                break;
            default:
                break;
        }
    }
}

OffsetF MenuLayoutAlgorithm::CalculateMenuPositionWithArrow(const OffsetF& menuPosition, bool didNeedArrow)
{
    OffsetF menuPositionWithArrow = menuPosition;
    if (didNeedArrow) {
        switch (arrowPlacement_) {
            case Placement::RIGHT:
            case Placement::RIGHT_TOP:
            case Placement::RIGHT_BOTTOM:
                menuPositionWithArrow -= OffsetF(ARROW_HIGHT.ConvertToPx(), 0);
                break;
            case Placement::BOTTOM:
            case Placement::BOTTOM_LEFT:
            case Placement::BOTTOM_RIGHT:
                menuPositionWithArrow -= OffsetF(0, ARROW_HIGHT.ConvertToPx());
                break;
            default:
                break;
        }
    }
    return menuPositionWithArrow;
}

void MenuLayoutAlgorithm::UpdateMenuFrameSizeWithArrow(const RefPtr<GeometryNode>& geometryNode,
    bool didNeedArrow)
{
    if (didNeedArrow && arrowPlacement_ != Placement::NONE) {
        switch (arrowPlacement_) {
            case Placement::LEFT:
            case Placement::LEFT_TOP:
            case Placement::LEFT_BOTTOM:
            case Placement::RIGHT:
            case Placement::RIGHT_TOP:
            case Placement::RIGHT_BOTTOM:
                geometryNode->SetFrameSize(geometryNode->GetFrameSize() + SizeF(ARROW_HIGHT.ConvertToPx(), 0));
                break;
            case Placement::TOP:
            case Placement::TOP_LEFT:
            case Placement::TOP_RIGHT:
            case Placement::BOTTOM:
            case Placement::BOTTOM_LEFT:
            case Placement::BOTTOM_RIGHT:
                geometryNode->SetFrameSize(geometryNode->GetFrameSize() + SizeF(0, ARROW_HIGHT.ConvertToPx()));
                break;
            default:
                break;
        }
    }
}

void MenuLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto targetNode = FrameNode::GetFrameNode(targetTag_, targetNodeId_);
    // if targetNode == nullptr, it means the menu is subMenu or multiMenu
    if (targetNode && !IsNodeOnRootTree(targetNode)) {
        TAG_LOGW(AceLogTag::ACE_MENU, "layout return because targetNode %{public}d not no root tree", targetNodeId_);
        return;
    }
    CHECK_NULL_VOID(layoutWrapper);
    auto menuProp = DynamicCast<MenuLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(menuProp);
    auto menuNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);

    if (menuPattern->GetPreviewMode() != MenuPreviewMode::NONE && !holdEmbeddedMenuPosition_) {
        LayoutPreviewMenu(layoutWrapper);
    }
    if (!menuPattern->IsSelectOverlayCustomMenu()) {
        auto geometryNode = layoutWrapper->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        auto size = geometryNode->GetMarginFrameSize();
        bool didNeedArrow = GetIfNeedArrow(layoutWrapper, size);
        if (menuPattern->IsSelectMenu()) {
            ComputeMenuPositionByAlignType(menuProp, size);
            auto offset = ComputeMenuPositionByOffset(menuProp, geometryNode);
            position_ += offset;
        }
        OffsetF menuPosition;
        auto useLastPosition = lastPosition_.has_value() && holdEmbeddedMenuPosition_;
        if (useLastPosition) {
            menuPosition = lastPosition_.value();
            auto lastPlacement = menuPattern->GetLastPlacement();
            if (lastPlacement.has_value()) {
                placement_ = lastPlacement.value();
                arrowPlacement_ = lastPlacement.value();
            }
        } else {
            menuPosition = MenuLayoutAvoidAlgorithm(menuProp, menuPattern, size, didNeedArrow, layoutWrapper);
        }
        menuPattern->UpdateLastPosition(menuPosition);
        menuPattern->UpdateLastPlacement(placement_);
        CalculateChildOffset(didNeedArrow);
        OffsetF menuPositionWithArrow = CalculateMenuPositionWithArrow(menuPosition, didNeedArrow);
        TAG_LOGD(AceLogTag::ACE_MENU, "update menu postion: %{public}s", menuPositionWithArrow.ToString().c_str());
        auto renderContext = menuNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        // show animation will be interrupted by repeated update
        if (lastPosition_.value_or(OffsetF()) != menuPositionWithArrow) {
            renderContext->UpdatePosition(
                OffsetT<Dimension>(Dimension(menuPositionWithArrow.GetX()), Dimension(menuPositionWithArrow.GetY())));
        }
        dumpInfo_.finalPlacement = PlacementUtils::ConvertPlacementToString(placement_);
        dumpInfo_.finalPosition = menuPosition;
        SetMenuPlacementForAnimation(layoutWrapper);
        if (didNeedArrow && arrowPlacement_ != Placement::NONE) {
            arrowPosition_ = GetArrowPositionWithPlacement(size, layoutWrapper);
            LayoutArrow(layoutWrapper);
        }
        geometryNode->SetFrameOffset(menuPositionWithArrow);
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
        auto menuEndOffset = menuPosition - (previewOffset_ - previewOriginOffset_) +
                             FixMenuOriginOffset(previewScale, afterAnimationScale);
        menuPattern->SetEndOffset(menuEndOffset);
        menuPattern->SetHasLaid(true);
        dumpInfo_.menuPreviewMode = static_cast<uint32_t>(menuPattern->GetPreviewMode());
        dumpInfo_.menuType = static_cast<uint32_t>(menuPattern->GetMenuType());
        auto menuWrapper = menuPattern->GetMenuWrapper();
        CHECK_NULL_VOID(menuWrapper);
        auto wrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
        CHECK_NULL_VOID(wrapperPattern);
        wrapperPattern->SetDumpInfo(dumpInfo_);
        UpdateMenuFrameSizeWithArrow(geometryNode, didNeedArrow);
    }

    TranslateOptions(layoutWrapper);
    ClipMenuPath(layoutWrapper);
}

void MenuLayoutAlgorithm::TranslateOptions(LayoutWrapper* layoutWrapper)
{
    // translate each option by the height of previous options
    OffsetF translate = childOffset_;
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
    dumpInfo_.enableArrow = true;
}

RefPtr<MenuPaintProperty> MenuLayoutAlgorithm::GetPaintProperty(const LayoutWrapper* layoutWrapper)
{
    auto menuNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(menuNode, nullptr);
    auto paintProperty = menuNode->GetPaintProperty<MenuPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, nullptr);
    return paintProperty;
}

BorderRadiusProperty MenuLayoutAlgorithm::GetMenuRadius(const LayoutWrapper* layoutWrapper, const SizeF& menuSize)
{
    Dimension defaultDimension(0);
    BorderRadiusProperty radius = { defaultDimension, defaultDimension, defaultDimension, defaultDimension };
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, radius);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(theme, radius);
    auto defaultRadius = Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)
                             ? theme->GetMenuDefaultRadius()
                             : theme->GetMenuBorderRadius();
    radius.SetRadius(defaultRadius);
    auto menuLayoutProp = DynamicCast<MenuLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(menuLayoutProp, radius);
    if (menuLayoutProp->GetBorderRadius().has_value()) {
        auto menuNode = layoutWrapper->GetHostNode();
        CHECK_NULL_RETURN(menuNode, radius);
        auto menuPattern = menuNode->GetPattern<MenuPattern>();
        CHECK_NULL_RETURN(menuPattern, radius);
        radius = menuPattern->CalcIdealBorderRadius(menuLayoutProp->GetBorderRadiusValue(), menuSize);
    }

    return radius;
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
    ProcessArrowParams(layoutWrapper, menuSize);

    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        return (menuPattern->IsContextMenu() || menuPattern->IsMenu()) && !targetTag_.empty() && arrowInMenu_;
    }

    return menuPattern->IsContextMenu() && !targetTag_.empty() && arrowInMenu_;
}

void MenuLayoutAlgorithm::ProcessArrowParams(const LayoutWrapper* layoutWrapper, const SizeF& menuSize)
{
    BorderRadiusProperty menuBorderRadius = GetMenuRadius(layoutWrapper, menuSize);
    auto radiusTopLeft = menuBorderRadius.radiusTopLeft.value_or(Dimension()).ConvertToPx();
    auto radiusTopRight = menuBorderRadius.radiusTopRight.value_or(Dimension()).ConvertToPx();
    auto radiusBottomLeft = menuBorderRadius.radiusBottomLeft.value_or(Dimension()).ConvertToPx();
    auto radiusBottomRight = menuBorderRadius.radiusBottomRight.value_or(Dimension()).ConvertToPx();
    arrowWidth_ = ARROW_WIDTH.ConvertToPx();

    switch (placement_) {
        case Placement::LEFT:
        case Placement::LEFT_TOP:
        case Placement::LEFT_BOTTOM:
            if (menuSize.Height() >= radiusTopRight + radiusBottomRight + arrowWidth_) {
                arrowInMenu_ = true;
            }
            break;
        case Placement::RIGHT:
        case Placement::RIGHT_TOP:
        case Placement::RIGHT_BOTTOM:
            if (menuSize.Height() >= radiusTopLeft + radiusBottomLeft + arrowWidth_) {
                arrowInMenu_ = true;
            }
            break;
        case Placement::TOP:
        case Placement::TOP_LEFT:
        case Placement::TOP_RIGHT:
            if (menuSize.Width() >= radiusBottomLeft + radiusBottomRight + arrowWidth_) {
                arrowInMenu_ = true;
            }
            break;
        case Placement::BOTTOM:
        case Placement::BOTTOM_LEFT:
        case Placement::BOTTOM_RIGHT:
            if (menuSize.Width() >= radiusTopLeft + radiusTopRight + arrowWidth_) {
                arrowInMenu_ = true;
            }
            break;
        default:
            break;
    }

    if (arrowInMenu_) {
        targetSpace_ = TARGET_SPACE.ConvertToPx();
    }
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

void MenuLayoutAlgorithm::UpdateArrowOffsetWithMenuLimit(const SizeF& menuSize, const LayoutWrapper* layoutWrapper)
{
    UpdatePropArrowOffset();
    BorderRadiusProperty menuBorderRadius = GetMenuRadius(layoutWrapper, menuSize);
    auto radiusTopLeft = menuBorderRadius.radiusTopLeft.value_or(Dimension()).ConvertToPx();
    auto radiusTopRight = menuBorderRadius.radiusTopRight.value_or(Dimension()).ConvertToPx();
    auto radiusBottomLeft = menuBorderRadius.radiusBottomLeft.value_or(Dimension()).ConvertToPx();
    auto radiusBottomRight = menuBorderRadius.radiusBottomRight.value_or(Dimension()).ConvertToPx();
    float range = -1.0f;

    switch (arrowPlacement_) {
        case Placement::LEFT:
        case Placement::LEFT_TOP:
        case Placement::LEFT_BOTTOM:
            range = menuSize.Height() - radiusTopRight - radiusBottomRight - arrowWidth_;
            arrowMinLimit_ = radiusTopRight + ARROW_WIDTH.ConvertToPx() / ARROW_WIDTH_FACTOR;
            break;
        case Placement::RIGHT:
        case Placement::RIGHT_TOP:
        case Placement::RIGHT_BOTTOM:
            range = menuSize.Height() - radiusTopLeft - radiusBottomLeft - arrowWidth_;
            arrowMinLimit_ = radiusTopLeft + ARROW_WIDTH.ConvertToPx() / ARROW_WIDTH_FACTOR;
            break;
        case Placement::TOP:
        case Placement::TOP_LEFT:
        case Placement::TOP_RIGHT:
            range = menuSize.Width() - radiusBottomLeft - radiusBottomRight - arrowWidth_;
            arrowMinLimit_ = radiusBottomLeft + ARROW_WIDTH.ConvertToPx() / ARROW_WIDTH_FACTOR;
            break;
        case Placement::BOTTOM:
        case Placement::BOTTOM_LEFT:
        case Placement::BOTTOM_RIGHT:
            range = menuSize.Width() - radiusTopLeft - radiusTopRight - arrowWidth_;
            arrowMinLimit_ = radiusTopLeft + ARROW_WIDTH.ConvertToPx() / ARROW_WIDTH_FACTOR;
            break;
        default:
            break;
    }
    if (range >= 0) {
        float tempOffset = propArrowOffset_.Unit() == DimensionUnit::PERCENT ? propArrowOffset_.Value() * range
                                                                             : propArrowOffset_.ConvertToPx();
        arrowOffset_ = std::clamp(tempOffset, 0.0f, range);
    }
}

void MenuLayoutAlgorithm::ComputeMenuPositionByAlignType(
    const RefPtr<MenuLayoutProperty>& menuProp, const SizeF& menuSize)
{
    auto alignType = menuProp->GetAlignType().value_or(MenuAlignType::START);
    auto direction = menuProp->GetNonAutoLayoutDirection();
    auto targetSize = menuProp->GetTargetSizeValue(SizeF());
    switch (alignType) {
        case MenuAlignType::CENTER: {
            position_.AddX(targetSize.Width() / 2.0f - menuSize.Width() / 2.0f);
            break;
        }
        case MenuAlignType::END: {
            if (direction == TextDirection::RTL) {
                return;
            }
            position_.AddX(targetSize.Width() - menuSize.Width());
            break;
        }
        case MenuAlignType::START: {
            if (direction != TextDirection::RTL) {
                return;
            }
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
    // Get pipelineContext of main window or host window for UIExtension
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
    const RefPtr<MenuPattern>& menuPattern, const SizeF& size, bool didNeedArrow, LayoutWrapper* layoutWrapper)
{
    auto pipelineContext = GetCurrentPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, OffsetF(0, 0));
    CHECK_NULL_RETURN(menuProp, OffsetF(0, 0));
    CHECK_NULL_RETURN(menuPattern, OffsetF(0, 0));
    float x = 0.0f;
    float y = 0.0f;
    if (menuProp->GetMenuPlacement().has_value() && (targetSize_.Width() > 0.0 || targetSize_.Height() > 0.0)) {
        placement_ = menuProp->GetMenuPlacement().value();
        if (layoutWrapper != nullptr) {
            PlacementRTL(layoutWrapper, placement_);
        }
        auto childOffset = GetChildPosition(size, didNeedArrow);
        x = childOffset.GetX();
        y = childOffset.GetY();
    } else {
        x = HorizontalLayout(size, position_.GetX(), menuPattern->IsSelectMenu()) + positionOffset_.GetX();
        y = VerticalLayout(size, position_.GetY(), menuPattern->IsContextMenu()) + positionOffset_.GetY();
    }
    x = std::clamp(static_cast<double>(x), static_cast<double>(paddingStart_),
        static_cast<double>(wrapperRect_.Right() - size.Width() - paddingEnd_));
    float yMinAvoid = wrapperRect_.Top() + paddingTop_;
    float yMaxAvoid = wrapperRect_.Bottom() - paddingBottom_ - size.Height();
    y = std::clamp(y, yMinAvoid, yMaxAvoid);
    return { x, y };
}

void MenuLayoutAlgorithm::PlacementRTL(LayoutWrapper* layoutWrapper, Placement& placement_)
{
    auto menuLayoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(menuLayoutProperty);
    auto layoutDirection = menuLayoutProperty->GetNonAutoLayoutDirection();
    if (layoutDirection == TextDirection::RTL) {
        switch (placement_) {
            case Placement::LEFT:
                placement_ = Placement::RIGHT;
                break;
            case Placement::RIGHT:
                placement_ = Placement::LEFT;
                break;
            case Placement::TOP_LEFT:
                placement_ = Placement::TOP_RIGHT;
                break;
            case Placement::TOP_RIGHT:
                placement_ = Placement::TOP_LEFT;
                break;
            case Placement::BOTTOM_LEFT:
                placement_ = Placement::BOTTOM_RIGHT;
                break;
            case Placement::BOTTOM_RIGHT:
                placement_ = Placement::BOTTOM_LEFT;
                break;
            case Placement::LEFT_TOP:
                placement_ = Placement::RIGHT_TOP;
                break;
            case Placement::RIGHT_TOP:
                placement_ = Placement::LEFT_TOP;
                break;
            case Placement::LEFT_BOTTOM:
                placement_ = Placement::RIGHT_BOTTOM;
                break;
            case Placement::RIGHT_BOTTOM:
                placement_ = Placement::LEFT_BOTTOM;
                break;
            default:
                break;
        }
    }
}

void MenuLayoutAlgorithm::LimitContainerModalMenuRect(double& rectWidth, double& rectHeight)
{
    auto containerOffsetX = static_cast<float>(CONTAINER_BORDER_WIDTH.ConvertToPx()) +
                            static_cast<float>(CONTAINER_BORDER_WIDTH.ConvertToPx());
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_SIXTEEN)) {
        containerOffsetX += static_cast<float>(CONTENT_PADDING.ConvertToPx());
    }
    auto pipeline = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto containerOffsetY = static_cast<float>(pipeline->GetCustomTitleHeight().ConvertToPx()) +
                            static_cast<float>(CONTAINER_BORDER_WIDTH.ConvertToPx()) +
                            static_cast<float>(CONTAINER_BORDER_WIDTH.ConvertToPx());
    rectWidth -= containerOffsetX;
    rectHeight -= containerOffsetY;
}

void MenuLayoutAlgorithm::UpdateConstraintWidth(LayoutWrapper* layoutWrapper, LayoutConstraintF& constraint)
{
    RefPtr<GridColumnInfo> columnInfo;
    columnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::MENU);
    auto menuNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    columnInfo->GetParent()->BuildColumnWidth(wrapperSize_.Width());
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

    float maxAvailableHeight = wrapperRect_.Height();
    float maxSpaceHeight = maxAvailableHeight * HEIGHT_CONSTRAINT_FACTOR;
    if (lastPosition_.has_value() && holdEmbeddedMenuPosition_) {
        auto spaceToBottom = GetMenuMaxBottom(menuPattern) - lastPosition_.value().GetY();
        maxSpaceHeight = std::min(maxSpaceHeight, spaceToBottom);
    }
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
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

float MenuLayoutAlgorithm::GetMenuMaxBottom(const RefPtr<MenuPattern>& menuPattern)
{
    auto bottom = wrapperRect_.Bottom();
    CHECK_NULL_RETURN(menuPattern, bottom);
    if (menuPattern->GetPreviewMode() != MenuPreviewMode::NONE) {
        auto placement = menuPattern->GetLastPlacement().value_or(Placement::NONE);
        auto isTopMenuBottomPreview =
            placement == Placement::TOP || placement == Placement::TOP_LEFT || placement == Placement::TOP_RIGHT;
        auto previewTopSpace = bottom - previewSize_.Height() * previewScale_ - targetSecurity_;
        return std::max<float>(0.0f, (isTopMenuBottomPreview ? previewTopSpace : bottom) - param_.bottomSecurity);
    }

    return bottom;
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
float MenuLayoutAlgorithm::VerticalLayout(const SizeF& size, float position, bool isContextMenu)
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
            return position + margin_;
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

OffsetF MenuLayoutAlgorithm::GetArrowPositionWithPlacement(const SizeF& menuSize, const LayoutWrapper* layoutWrapper)
{
    UpdateArrowOffsetWithMenuLimit(menuSize, layoutWrapper);
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
            childPosition = OffsetF(addArrowOffsetToArrowMin, 0);
            break;
        case Placement::LEFT:
        case Placement::LEFT_TOP:
        case Placement::LEFT_BOTTOM:
            childPosition = OffsetF(menuSize.Width() + space_, addArrowOffsetToArrowMin);
            break;
        case Placement::RIGHT:
        case Placement::RIGHT_TOP:
        case Placement::RIGHT_BOTTOM:
            childPosition = OffsetF(0, addArrowOffsetToArrowMin);
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
    auto menuLayoutProperty = layoutWrapper->GetLayoutProperty();
    if (menuLayoutProperty && menuLayoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL) {
        return menuNode->GetPaintRectOffset(true);
    }
    return menuNode->GetParentGlobalOffsetDuringLayout();
}

bool MenuLayoutAlgorithm::SkipUpdateTargetNodeSize(
    const RefPtr<FrameNode>& targetNode, const RefPtr<MenuPattern>& menuPattern)
{
    CHECK_NULL_RETURN(menuPattern, false);
    auto menuWrapper = menuPattern->GetMenuWrapper();
    CHECK_NULL_RETURN(menuWrapper, false);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_RETURN(menuWrapperPattern, false);

    auto isMenuHide = menuWrapperPattern->IsHide();
    auto isTargetEmpty = !targetNode && menuPattern->GetTargetSize().IsPositive();
    if (isMenuHide || isTargetEmpty) {
        TAG_LOGI(AceLogTag::ACE_MENU,
            "targetNode empty: %{public}d, menu hidden: %{public}d, update targetNode to last size and position",
            isTargetEmpty, isMenuHide);
        targetSize_ = menuPattern->GetTargetSize();
        targetOffset_ = menuPattern->GetTargetOffset();
        return true;
    }
    return false;
}

void MenuLayoutAlgorithm::InitTargetSizeAndPosition(
    const LayoutWrapper* layoutWrapper, bool isContextMenu, const RefPtr<MenuPattern>& menuPattern)
{
    CHECK_NULL_VOID(layoutWrapper && menuPattern);
    auto targetNode = FrameNode::GetFrameNode(targetTag_, targetNodeId_);
    if (!SkipUpdateTargetNodeSize(targetNode, menuPattern)) {
        CHECK_NULL_VOID(targetNode);
        dumpInfo_.targetNode = targetNode->GetTag();
        auto props = AceType::DynamicCast<MenuLayoutProperty>(layoutWrapper->GetLayoutProperty());
        CHECK_NULL_VOID(props);
        if (props->GetIsRectInTargetValue(false)) {
            targetSize_ = props->GetTargetSizeValue(SizeF());
            targetOffset_ = props->GetMenuOffsetValue(OffsetF());
        } else {
            targetSize_ = targetNode->GetPaintRectWithTransform().GetSize();
            targetOffset_ = targetNode->GetPaintRectOffset();
        }
    }
    dumpInfo_.targetSize = targetSize_;
    dumpInfo_.targetOffset = targetOffset_;
    menuPattern->SetTargetSize(targetSize_);
    menuPattern->SetTargetOffset(targetOffset_);
    TAG_LOGI(AceLogTag::ACE_MENU, "targetNode: %{public}s, targetSize: %{public}s, targetOffset: %{public}s",
        targetTag_.c_str(), targetSize_.ToString().c_str(), targetOffset_.ToString().c_str());
    auto pipelineContext = GetCurrentPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    if (canExpandCurrentWindow_ && targetTag_ != V2::SELECT_ETS_TAG) {
        ModifyTargetOffset();
        OffsetF offset = GetMenuWrapperOffset(layoutWrapper);
        targetOffset_ -= offset;
        return;
    }

    auto windowManager = pipelineContext->GetWindowManager();
    auto isContainerModal = pipelineContext->GetWindowModal() == WindowModal::CONTAINER_MODAL && windowManager &&
                            windowManager->GetWindowMode() == WindowMode::WINDOW_MODE_FLOATING;
    if (isContainerModal) {
        auto newOffsetX = static_cast<float>(CONTAINER_BORDER_WIDTH.ConvertToPx());
        if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_SIXTEEN)) {
            newOffsetX += static_cast<float>(CONTENT_PADDING.ConvertToPx());
        }
        auto newOffsetY = static_cast<float>(pipelineContext->GetCustomTitleHeight().ConvertToPx()) +
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

    // add space between targetNode and menu using default value or user-set offset
    if (NearEqual(positionOffset_, OffsetF(0.0f, 0.0f))) {
        afterOffsetPosition = AddTargetSpace(originPosition);
    } else {
        afterOffsetPosition = AddOffset(originPosition);
    }

    if (!CheckPosition(afterOffsetPosition, childSize) || flag_) {
        flag_ = false;
        return OffsetF(0.0f, 0.0f);
    }

    return afterOffsetPosition;
}

OffsetF MenuLayoutAlgorithm::GetChildPosition(const SizeF& childSize, bool didNeedArrow)
{
    // add space between arrow and targetNode
    OffsetF bottomPosition = OffsetF(targetOffset_.GetX() + (targetSize_.Width() - childSize.Width()) / 2.0,
        targetOffset_.GetY() + targetSize_.Height() + targetSpace_);
    OffsetF topPosition = OffsetF(targetOffset_.GetX() + (targetSize_.Width() - childSize.Width()) / 2.0,
        targetOffset_.GetY() - childSize.Height() - targetSpace_);
    // when failed to find place for menu, put menu above targetNode with center-aligned
    OffsetF defaultPosition = OffsetF(targetOffset_.GetX() + (targetSize_.Width() - childSize.Width()) / 2.0,
        targetOffset_.GetY() + (targetSize_.Height() - childSize.Height()) / 2.0);

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
            xMax = wrapperRect_.Right() - width - paddingEnd_;
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
    auto leftOutside = LessNotEqual(x, rect.Left());
    auto rightOutside = GreatNotEqual(x + childSize.Width(), rect.Right());
    auto topOutside = LessNotEqual(y, rect.Top());
    auto bottomOutside = GreatNotEqual(y + childSize.Height(), rect.Bottom());
    TAG_LOGI(AceLogTag::ACE_MENU,
        "CheckPositionInPlacementRect, leftOutside : %{public}d, rightOutside : %{public}d, topOutside : %{public}d, "
        "bottomOutside : %{public}d",
        leftOutside, rightOutside, topOutside, bottomOutside);
    auto outside = leftOutside || rightOutside || topOutside || bottomOutside;
    if (state_ != prevState_) {
        if (prevState_ == -1) {
            prevState_ = state_;
            preOffset_ = position;
            preRect_ = rect;
            if (!outside) {
                return true;
            }
            flag_ = true;
            positionOffset_ = { 0.0f, 0.0f };
            return false;
        }
        return CheckPlacement(childSize);
    }
    if (outside) {
        preOffset_ = position;
        preRect_ = rect;
        return false;
    }
    return true;
}

bool MenuLayoutAlgorithm::CheckPlacement(const SizeF& childSize)
{
    auto x = preOffset_.GetX();
    auto y = preOffset_.GetY();
    auto leftOutside = LessNotEqual(x, preRect_.Left());
    auto rightOutside = GreatNotEqual(x + childSize.Width(), preRect_.Right());
    auto topOutside = LessNotEqual(y, preRect_.Top());
    auto bottomOutside = GreatNotEqual(y + childSize.Height(), preRect_.Bottom());
    TAG_LOGI(AceLogTag::ACE_MENU,
        "CheckPlacement, leftOutside : %{public}d, rightOutside : %{public}d, topOutside : %{public}d, "
        "bottomOutside : %{public}d",
        leftOutside, rightOutside, topOutside, bottomOutside);

    switch (prevState_) {
        case static_cast<int>(DirectionState::Bottom_Direction):
        case static_cast<int>(DirectionState::Top_Direction): {
            if ((leftOutside || rightOutside) && !(topOutside || bottomOutside)) {
                placement_ = Placement::NONE;
                return true;
            }
            break;
        }
        case static_cast<int>(DirectionState::Right_Direction):
        case static_cast<int>(DirectionState::Left_Direction): {
            if ((topOutside || bottomOutside) && !(leftOutside || rightOutside)) {
                placement_ = Placement::NONE;
                return true;
            }
            break;
        }
        default:
            return false;
    }

    return false;
}

bool MenuLayoutAlgorithm::CheckPosition(const OffsetF& position, const SizeF& childSize)
{
    float xAvoid = wrapperRect_.Left() + paddingStart_;
    float yAvoid = wrapperRect_.Top() + paddingTop_ + param_.topSecurity;
    float maxWidth = wrapperSize_.Width() - paddingEnd_ - paddingStart_;
    float maxHeight = wrapperSize_.Height() - paddingTop_ - param_.topSecurity - paddingBottom_ - param_.bottomSecurity;
    Rect rect;
    Rect targetRect = Rect(targetOffset_.GetX(), targetOffset_.GetY(), targetSize_.Width(), targetSize_.Height());
    switch (placement_) {
        case Placement::BOTTOM_LEFT:
        case Placement::BOTTOM_RIGHT:
        case Placement::BOTTOM: {
            state_ = static_cast<int>(DirectionState::Bottom_Direction);
            auto y = std::max<float>(targetRect.Bottom(), yAvoid);
            auto height = std::min<float>(
                wrapperRect_.Bottom() - targetRect.Bottom() - paddingBottom_ - param_.bottomSecurity, maxHeight);
            rect.SetRect(xAvoid, y, maxWidth, height);
            break;
        }
        case Placement::TOP_LEFT:
        case Placement::TOP_RIGHT:
        case Placement::TOP: {
            state_ = static_cast<int>(DirectionState::Top_Direction);
            auto height = std::min<float>(targetRect.Top() - yAvoid, maxHeight);
            rect.SetRect(xAvoid, yAvoid, maxWidth, height);
            break;
        }
        case Placement::RIGHT_TOP:
        case Placement::RIGHT_BOTTOM:
        case Placement::RIGHT: {
            state_ = static_cast<int>(DirectionState::Right_Direction);
            auto x = std::max<float>(targetRect.Right(), xAvoid);
            auto width = std::min<float>(wrapperRect_.Right() - targetRect.Right() - paddingEnd_, maxWidth);
            rect.SetRect(x, yAvoid, width, maxHeight);
            break;
        }
        case Placement::LEFT_TOP:
        case Placement::LEFT_BOTTOM:
        case Placement::LEFT: {
            state_ = static_cast<int>(DirectionState::Left_Direction);
            auto width = std::min<float>(targetRect.Left() - xAvoid, maxWidth);
            rect.SetRect(xAvoid, yAvoid, width, maxHeight);
            break;
        }
        default:
            state_ = static_cast<int>(DirectionState::None_Direction);
            return false;
    }
    return CheckPositionInPlacementRect(rect, position, childSize);
}

OffsetF MenuLayoutAlgorithm::GetPositionWithPlacementTop(
    const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition)
{
    TAG_LOGI(AceLogTag::ACE_MENU, "GetPositionWithPlacementTop : %{public}s", topPosition.ToString().c_str());
    return topPosition;
}

OffsetF MenuLayoutAlgorithm::GetPositionWithPlacementTopLeft(
    const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition)
{
    OffsetF childPosition;
    float marginRight = 0.0f;
    float marginBottom = 0.0f;
    childPosition = OffsetF(
        targetOffset_.GetX() - marginRight, targetOffset_.GetY() - childSize.Height() - marginBottom - targetSpace_);
    TAG_LOGI(AceLogTag::ACE_MENU, "GetPositionWithPlacementTopLeft : %{public}s", childPosition.ToString().c_str());
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
    TAG_LOGI(AceLogTag::ACE_MENU, "GetPositionWithPlacementTopRight : %{public}s", childPosition.ToString().c_str());
    return childPosition;
}

OffsetF MenuLayoutAlgorithm::GetPositionWithPlacementBottom(
    const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition)
{
    TAG_LOGI(AceLogTag::ACE_MENU, "GetPositionWithPlacementBottom : %{public}s", bottomPosition.ToString().c_str());
    return bottomPosition;
}

OffsetF MenuLayoutAlgorithm::GetPositionWithPlacementBottomLeft(
    const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition)
{
    OffsetF childPosition;
    float marginRight = 0.0f;
    float marginTop = 0.0f;
    childPosition = OffsetF(
        targetOffset_.GetX() - marginRight, targetOffset_.GetY() + targetSize_.Height() + targetSpace_ + marginTop);
    TAG_LOGI(AceLogTag::ACE_MENU, "GetPositionWithPlacementBottomLeft : %{public}s", childPosition.ToString().c_str());
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
    TAG_LOGI(AceLogTag::ACE_MENU, "GetPositionWithPlacementBottomRight : %{public}s", childPosition.ToString().c_str());
    return childPosition;
}

OffsetF MenuLayoutAlgorithm::GetPositionWithPlacementLeft(
    const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition)
{
    OffsetF childPosition;
    float marginRight = 0.0f;
    childPosition = OffsetF(targetOffset_.GetX() - targetSpace_ - childSize.Width() - marginRight,
        targetOffset_.GetY() + targetSize_.Height() / 2.0 - childSize.Height() / 2.0);
    TAG_LOGI(AceLogTag::ACE_MENU, "GetPositionWithPlacementLeft : %{public}s", childPosition.ToString().c_str());
    return childPosition;
}

OffsetF MenuLayoutAlgorithm::GetPositionWithPlacementLeftTop(
    const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition)
{
    OffsetF childPosition;
    float marginRight = 0.0f;
    float marginBottom = 0.0f;
    childPosition = OffsetF(
        targetOffset_.GetX() - targetSpace_ - childSize.Width() - marginRight, targetOffset_.GetY() - marginBottom);
    TAG_LOGI(AceLogTag::ACE_MENU, "GetPositionWithPlacementLeftTop : %{public}s", childPosition.ToString().c_str());
    return childPosition;
}

OffsetF MenuLayoutAlgorithm::GetPositionWithPlacementLeftBottom(
    const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition)
{
    OffsetF childPosition;
    float marginRight = 0.0f;
    float marginTop = 0.0f;
    childPosition = OffsetF(targetOffset_.GetX() - targetSpace_ - childSize.Width() - marginRight,
        targetOffset_.GetY() + targetSize_.Height() - childSize.Height() - marginTop);
    TAG_LOGI(AceLogTag::ACE_MENU, "GetPositionWithPlacementLeftBottom : %{public}s", childPosition.ToString().c_str());
    return childPosition;
}

OffsetF MenuLayoutAlgorithm::GetPositionWithPlacementRight(
    const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition)
{
    OffsetF childPosition;
    float marginLeft = 0.0f;
    childPosition = OffsetF(targetOffset_.GetX() + targetSize_.Width() + targetSpace_ + marginLeft,
        targetOffset_.GetY() + targetSize_.Height() / 2.0 - childSize.Height() / 2.0);
    TAG_LOGI(AceLogTag::ACE_MENU, "GetPositionWithPlacementRight : %{public}s", childPosition.ToString().c_str());
    return childPosition;
}

OffsetF MenuLayoutAlgorithm::GetPositionWithPlacementRightTop(
    const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition)
{
    OffsetF childPosition;
    float marginBottom = 0.0f;
    float marginLeft = 0.0f;
    childPosition = OffsetF(
        targetOffset_.GetX() + targetSize_.Width() + targetSpace_ + marginLeft, targetOffset_.GetY() - marginBottom);
    TAG_LOGI(AceLogTag::ACE_MENU, "GetPositionWithPlacementRightTop : %{public}s", childPosition.ToString().c_str());
    return childPosition;
}

OffsetF MenuLayoutAlgorithm::GetPositionWithPlacementRightBottom(
    const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition)
{
    OffsetF childPosition;
    float marginTop = 0.0f;
    float marginLeft = 0.0f;
    childPosition = OffsetF(targetOffset_.GetX() + targetSize_.Width() + targetSpace_ + marginLeft,
        targetOffset_.GetY() + targetSize_.Height() - childSize.Height() - marginTop);
    TAG_LOGI(AceLogTag::ACE_MENU, "GetPositionWithPlacementRightBottom : %{public}s", childPosition.ToString().c_str());
    return childPosition;
}

void MenuLayoutAlgorithm::InitCanExpandCurrentWindow(bool isShowInSubWindow)
{
    auto pipelineContext = GetCurrentPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto containerId = Container::CurrentId();
    auto container = AceEngine::Get().GetContainer(containerId);
    if (containerId >= MIN_SUBCONTAINER_ID) {
        auto parentContainerId = SubwindowManager::GetInstance()->GetParentContainerId(containerId);
        container = AceEngine::Get().GetContainer(parentContainerId);
    }
    CHECK_NULL_VOID(container);
    // Get FreeMultiWindow status of main window or host window
    isFreeMultiWindow_ = container->IsFreeMultiWindow();
    auto theme = pipelineContext->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    // false for phone devices
    isExpandDisplay_ = theme->GetExpandDisplay() || isFreeMultiWindow_;
    if (isExpandDisplay_ && !isShowInSubWindow && containerId >= MIN_SUBCONTAINER_ID) {
        canExpandCurrentWindow_ = true;
        isTargetNodeInSubwindow_ = true;
        return;
    }
    canExpandCurrentWindow_ = isExpandDisplay_ && isShowInSubWindow;
    if (containerId >= MIN_SUBCONTAINER_ID) {
        auto parentContainerId = SubwindowManager::GetInstance()->GetParentContainerId(containerId);
        container = AceEngine::Get().GetContainer(parentContainerId);
        CHECK_NULL_VOID(container);
        isUIExtensionSubWindow_ = container->IsUIExtensionWindow();
        if (isUIExtensionSubWindow_) {
            canExpandCurrentWindow_ = true;
            auto subwindow = SubwindowManager::GetInstance()->GetSubwindow(parentContainerId);
            CHECK_NULL_VOID(subwindow);
            auto rect = subwindow->GetUIExtensionHostWindowRect();
            UIExtensionHostWindowRect_ = RectF(rect.Left(), rect.Top(), rect.Width(), rect.Height());
            TAG_LOGI(AceLogTag::ACE_MENU, "GetUIExtensionHostWindowRect : %{public}s",
                UIExtensionHostWindowRect_.ToString().c_str());
        }
    }
}

Rect MenuLayoutAlgorithm::GetMenuWindowRectInfo(const RefPtr<MenuPattern>& menuPattern)
{
    auto menuWindowRect = Rect();
    CHECK_NULL_RETURN(menuPattern, menuWindowRect);
    auto pipelineContext = GetCurrentPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, menuWindowRect);
    auto rect = pipelineContext->GetDisplayWindowRectInfo();
    displayWindowRect_ = RectF(rect.Left(), rect.Top(), rect.Width(), rect.Height());
    TAG_LOGI(AceLogTag::ACE_MENU, "GetDisplayWindowRectInfo : %{public}s", displayWindowRect_.ToString().c_str());
    menuWindowRect = Rect(rect.Left(), rect.Top(), rect.Width(), rect.Height());
    auto availableRect = pipelineContext->GetDisplayAvailableRect();
    TAG_LOGI(AceLogTag::ACE_MENU, "GetDisplayAvailableRect : %{public}s", availableRect.ToString().c_str());
    if (canExpandCurrentWindow_ && isExpandDisplay_) {
        menuWindowRect = Rect(availableRect.Left(), availableRect.Top(), availableRect.Width(), availableRect.Height());
    } else if (isUIExtensionSubWindow_ && !isExpandDisplay_) {
        rect = Rect(UIExtensionHostWindowRect_.Left(), UIExtensionHostWindowRect_.Top(),
            UIExtensionHostWindowRect_.Width(), UIExtensionHostWindowRect_.Height());
        menuWindowRect = rect;
    }
    TAG_LOGI(AceLogTag::ACE_MENU, "GetMenuWindowRectInfo : %{public}s", menuWindowRect.ToString().c_str());
    dumpInfo_.menuWindowRect = menuWindowRect;
    menuPattern->SetMenuWindowRect(menuWindowRect);
    return menuWindowRect;
}

void MenuLayoutAlgorithm::ModifyTargetOffset()
{
    TAG_LOGI(AceLogTag::ACE_MENU, "original targetOffset is : %{public}s", targetOffset_.ToString().c_str());
    if (canExpandCurrentWindow_ && isExpandDisplay_ && !isTargetNodeInSubwindow_) {
        targetOffset_ += displayWindowRect_.GetOffset();
        TAG_LOGI(AceLogTag::ACE_MENU, "ModifyTargetOffset for displayAvailableRect : %{public}s",
            targetOffset_.ToString().c_str());
    } else if (isUIExtensionSubWindow_ && !isExpandDisplay_) {
        targetOffset_ += displayWindowRect_.GetOffset() - UIExtensionHostWindowRect_.GetOffset();
        TAG_LOGI(AceLogTag::ACE_MENU, "ModifyTargetOffset for UIExtensionHostWindowRect : %{public}s",
            targetOffset_.ToString().c_str());
    }
}

bool MenuLayoutAlgorithm::HoldEmbeddedMenuPosition(LayoutWrapper* layoutWrapper)
{
    auto menuNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(menuNode, false);
    auto menuNodePattern = AceType::DynamicCast<MenuPattern>(menuNode->GetPattern());
    CHECK_NULL_RETURN(menuNodePattern, false);
    auto menuWrapper = menuNodePattern->GetMenuWrapper();
    CHECK_NULL_RETURN(menuWrapper, false);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_RETURN(menuWrapperPattern, false);
    auto innerMenu = menuWrapperPattern->GetMenuChild(menuNode);
    CHECK_NULL_RETURN(innerMenu, false);
    auto innerMenuPattern = AceType::DynamicCast<MenuPattern>(innerMenu->GetPattern());
    CHECK_NULL_RETURN(innerMenuPattern, false);
    auto layoutProps = innerMenuPattern->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_RETURN(layoutProps, false);
    return layoutProps->GetExpandingMode().value_or(SubMenuExpandingMode::SIDE) == SubMenuExpandingMode::EMBEDDED &&
           menuWrapperPattern->GetEmbeddedSubMenuExpandTotalCount() > 0;
}

std::string MenuLayoutAlgorithm::MoveTo(double x, double y)
{
    return "M" + std::to_string(x) + " " + std::to_string(y) + " ";
}

std::string MenuLayoutAlgorithm::LineTo(double x, double y)
{
    return "L" + std::to_string(x) + " " + std::to_string(y) + " ";
}

std::string MenuLayoutAlgorithm::ArcTo(double rx, double ry, double rotation, int32_t arc_flag, double x, double y)
{
    int32_t sweep_flag = 1;
    return "A" + std::to_string(rx) + " " + std::to_string(ry) + " " + std::to_string(rotation) + " " +
           std::to_string(arc_flag) + " " + std::to_string(sweep_flag) + " " + std::to_string(x) + " " +
           std::to_string(y) + " ";
}

void MenuLayoutAlgorithm::BuildBottomArrowPath(float arrowX, float arrowY, std::string& path)
{
    path += LineTo(arrowX - ARROW_P1_OFFSET_X.ConvertToPx(), arrowY + ARROW_P1_OFFSET_Y.ConvertToPx()); //P1
    path += LineTo(arrowX - ARROW_P2_OFFSET_X.ConvertToPx(), arrowY + ARROW_P2_OFFSET_Y.ConvertToPx()); //P2
    path += ArcTo(ARROW_RADIUS.ConvertToPx(), ARROW_RADIUS.ConvertToPx(), 0.0f, 0,
        arrowX + ARROW_P2_OFFSET_X.ConvertToPx(), arrowY + ARROW_P2_OFFSET_Y.ConvertToPx()); //P4
    path += LineTo(arrowX + ARROW_P1_OFFSET_X.ConvertToPx(), arrowY + ARROW_P1_OFFSET_Y.ConvertToPx()); //P5
}

void MenuLayoutAlgorithm::BuildTopArrowPath(float arrowX, float arrowY, std::string& path)
{
    path += LineTo(arrowX + ARROW_P1_OFFSET_X.ConvertToPx(), arrowY - ARROW_P1_OFFSET_Y.ConvertToPx()); //P1
    path += LineTo(arrowX + ARROW_P2_OFFSET_X.ConvertToPx(), arrowY - ARROW_P2_OFFSET_Y.ConvertToPx()); //P2
    path += ArcTo(ARROW_RADIUS.ConvertToPx(), ARROW_RADIUS.ConvertToPx(), 0.0f, 0,
        arrowX - ARROW_P2_OFFSET_X.ConvertToPx(), arrowY - ARROW_P2_OFFSET_Y.ConvertToPx()); //P4
    path += LineTo(arrowX - ARROW_P1_OFFSET_X.ConvertToPx(), arrowY - ARROW_P1_OFFSET_Y.ConvertToPx()); //P5
}

void MenuLayoutAlgorithm::BuildRightArrowPath(float arrowX, float arrowY, std::string& path)
{
    path += LineTo(arrowX + ARROW_P1_OFFSET_Y.ConvertToPx(), arrowY + ARROW_P1_OFFSET_X.ConvertToPx()); //P1
    path += LineTo(arrowX + ARROW_P2_OFFSET_Y.ConvertToPx(), arrowY + ARROW_P2_OFFSET_X.ConvertToPx()); //P2
    path += ArcTo(ARROW_RADIUS.ConvertToPx(), ARROW_RADIUS.ConvertToPx(), 0.0f, 0,
        arrowX + ARROW_P2_OFFSET_Y.ConvertToPx(), arrowY - ARROW_P2_OFFSET_X.ConvertToPx()); //P4
    path += LineTo(arrowX + ARROW_P1_OFFSET_Y.ConvertToPx(), arrowY - ARROW_P1_OFFSET_X.ConvertToPx()); //P5
}

void MenuLayoutAlgorithm::BuildLeftArrowPath(float arrowX, float arrowY, std::string& path)
{
    path += LineTo(arrowX - ARROW_P1_OFFSET_Y.ConvertToPx(), arrowY - ARROW_P1_OFFSET_X.ConvertToPx()); //P1
    path += LineTo(arrowX - ARROW_P2_OFFSET_Y.ConvertToPx(), arrowY - ARROW_P2_OFFSET_X.ConvertToPx()); //P2
    path += ArcTo(ARROW_RADIUS.ConvertToPx(), ARROW_RADIUS.ConvertToPx(), 0.0f, 0,
        arrowX - ARROW_P2_OFFSET_Y.ConvertToPx(), arrowY + ARROW_P2_OFFSET_X.ConvertToPx()); //P4
    path += LineTo(arrowX - ARROW_P1_OFFSET_Y.ConvertToPx(), arrowY + ARROW_P1_OFFSET_X.ConvertToPx()); //P5
}

std::string MenuLayoutAlgorithm::BuildTopLinePath(const OffsetF& arrowPosition, float radiusPx,
    Placement arrowBuildPlacement, bool didNeedArrow)
{
    std::string path;
    if (didNeedArrow) {
        switch (arrowBuildPlacement) {
            case Placement::BOTTOM:
            case Placement::BOTTOM_LEFT:
            case Placement::BOTTOM_RIGHT:
                BuildBottomArrowPath(arrowPosition.GetX(), arrowPosition.GetY(), path);
                break;
            default:
                break;
        }
    }
    path += LineTo(childOffset_.GetX() + childMarginFrameSize_.Width() - radiusPx, childOffset_.GetY());
    path += ArcTo(radiusPx, radiusPx, 0.0f, 0, childOffset_.GetX() + childMarginFrameSize_.Width(),
        childOffset_.GetY() + radiusPx);
    return path;
}

std::string MenuLayoutAlgorithm::BuildRightLinePath(const OffsetF& arrowPosition, float radiusPx,
    Placement arrowBuildPlacement, bool didNeedArrow)
{
    std::string path;
    if (didNeedArrow) {
        switch (arrowBuildPlacement) {
            case Placement::LEFT:
            case Placement::LEFT_TOP:
            case Placement::LEFT_BOTTOM:
                BuildLeftArrowPath(arrowPosition.GetX(), arrowPosition.GetY(), path);
                break;
            default:
                break;
        }
    }
    path += LineTo(childOffset_.GetX() + childMarginFrameSize_.Width(),
        childOffset_.GetY() + childMarginFrameSize_.Height() - radiusPx);
    path += ArcTo(radiusPx, radiusPx, 0.0f, 0, childOffset_.GetX() + childMarginFrameSize_.Width() - radiusPx,
        childOffset_.GetY() + childMarginFrameSize_.Height());
    return path;
}

std::string MenuLayoutAlgorithm::BuildBottomLinePath(const OffsetF& arrowPosition, float radiusPx,
    Placement arrowBuildPlacement, bool didNeedArrow)
{
    std::string path;
    if (didNeedArrow) {
        switch (arrowBuildPlacement) {
            case Placement::TOP:
            case Placement::TOP_LEFT:
            case Placement::TOP_RIGHT:
                BuildTopArrowPath(arrowPosition.GetX(), arrowPosition.GetY(), path);
                break;
            default:
                break;
        }
    }
    path += LineTo(childOffset_.GetX() + radiusPx, childOffset_.GetY() + childMarginFrameSize_.Height());
    path += ArcTo(radiusPx, radiusPx, 0.0f, 0, childOffset_.GetX(),
        childOffset_.GetY() + childMarginFrameSize_.Height() - radiusPx);
    return path;
}

std::string MenuLayoutAlgorithm::BuildLeftLinePath(const OffsetF& arrowPosition, float radiusPx,
    Placement arrowBuildPlacement, bool didNeedArrow)
{
    std::string path;
    if (didNeedArrow) {
        switch (arrowBuildPlacement) {
            case Placement::RIGHT:
            case Placement::RIGHT_TOP:
            case Placement::RIGHT_BOTTOM:
                BuildRightArrowPath(arrowPosition.GetX(), arrowPosition.GetY(), path);
                break;
            default:
                break;
        }
    }
    path += LineTo(childOffset_.GetX(), childOffset_.GetY() + radiusPx);
    path += ArcTo(radiusPx, radiusPx, 0.0f, 0, childOffset_.GetX() + radiusPx, childOffset_.GetY());
    return path;
}

void MenuLayoutAlgorithm::NormalizeBorderRadius(float& radiusTopLeftPx, float& radiusTopRightPx,
    float& radiusBottomLeftPx, float& radiusBottomRightPx)
{
    float childMarginFrameWidth = childMarginFrameSize_.Width();
    float childMarginFrameHeight = childMarginFrameSize_.Height();
    if (NearZero(childMarginFrameWidth) || NearZero(childMarginFrameHeight)) {
        radiusTopLeftPx = 0.0f;
        radiusTopRightPx = 0.0f;
        radiusBottomLeftPx = 0.0f;
        radiusBottomRightPx = 0.0f;
        return;
    }
    float topRatio = (radiusTopLeftPx + radiusTopRightPx) / childMarginFrameWidth;
    float bottomRatio = (radiusBottomLeftPx + radiusBottomRightPx) / childMarginFrameWidth;
    float leftRatio = (radiusTopLeftPx + radiusBottomLeftPx) / childMarginFrameHeight;
    float rightRatio = (radiusTopRightPx + radiusBottomRightPx) / childMarginFrameHeight;
    float maxRatio = std::max(std::max(topRatio, bottomRatio), std::max(leftRatio, rightRatio));
    if (GreatNotEqual(maxRatio, 1.0f)) {
        radiusTopLeftPx = radiusTopLeftPx / maxRatio;
        radiusTopRightPx = radiusTopRightPx / maxRatio;
        radiusBottomLeftPx = radiusBottomLeftPx / maxRatio;
        radiusBottomRightPx = radiusBottomRightPx / maxRatio;
    }
}

std::string MenuLayoutAlgorithm::CalculateMenuPath(LayoutWrapper* layoutWrapper, bool didNeedArrow)
{
    CHECK_NULL_RETURN(layoutWrapper, "");
    auto menuNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(menuNode, "");
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(menuPattern, "");
    auto renderContext = menuNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, "");
    auto menuPosition = renderContext->GetPositionValue(OffsetT<Dimension>());
    BorderRadiusProperty menuBorderRadius = GetMenuRadius(layoutWrapper, childMarginFrameSize_);
    float radiusTopLeftPx = menuBorderRadius.radiusTopLeft.value_or(Dimension())
        .ConvertToPxWithSize(childMarginFrameSize_.Width());
    float radiusTopRightPx = menuBorderRadius.radiusTopRight.value_or(Dimension())
        .ConvertToPxWithSize(childMarginFrameSize_.Width());
    float radiusBottomLeftPx = menuBorderRadius.radiusBottomLeft.value_or(Dimension())
        .ConvertToPxWithSize(childMarginFrameSize_.Width());
    float radiusBottomRightPx = menuBorderRadius.radiusBottomRight.value_or(Dimension())
        .ConvertToPxWithSize(childMarginFrameSize_.Width());
    NormalizeBorderRadius(radiusTopLeftPx, radiusTopRightPx, radiusBottomLeftPx, radiusBottomRightPx);
    auto targetOffset = OffsetF(menuPosition.GetX().ConvertToPx(), menuPosition.GetY().ConvertToPx());
    if (menuPattern->GetMenuType() == MenuType::SUB_MENU) {
        const auto& geometryNode = layoutWrapper->GetGeometryNode();
        CHECK_NULL_RETURN(geometryNode, "");
        targetOffset = geometryNode->GetMarginFrameOffset();
    }
    auto childOffset = targetOffset + childOffset_;
    auto arrowPosition = targetOffset + arrowPosition_;
    MenuPathParams params = {
        radiusTopLeftPx,
        radiusTopRightPx,
        radiusBottomLeftPx,
        radiusBottomRightPx,
        childOffset,
        childMarginFrameSize_,
        arrowPosition,
        arrowPlacement_,
        didNeedArrow,
    };
    menuPattern->UpdateMenuPathParams(params);
    if (!didNeedArrow) {
        return "";
    }
    std::string path;
    path += MoveTo(childOffset_.GetX() + radiusTopLeftPx, childOffset_.GetY());
    path += BuildTopLinePath(arrowPosition_, radiusTopRightPx, arrowPlacement_, didNeedArrow);
    path += BuildRightLinePath(arrowPosition_, radiusBottomRightPx, arrowPlacement_, didNeedArrow);
    path += BuildBottomLinePath(arrowPosition_, radiusBottomLeftPx, arrowPlacement_, didNeedArrow);
    path += BuildLeftLinePath(arrowPosition_, radiusTopLeftPx, arrowPlacement_, didNeedArrow);
    return path + "Z";
}

void MenuLayoutAlgorithm::ClipMenuPath(LayoutWrapper* layoutWrapper)
{
    bool didNeedArrow = GetIfNeedArrow(layoutWrapper, childMarginFrameSize_);
    clipPath_ = CalculateMenuPath(layoutWrapper, didNeedArrow);
}
} // namespace OHOS::Ace::NG
