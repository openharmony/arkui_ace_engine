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

#include "core/components_ng/pattern/menu/sub_menu_layout_algorithm.h"

#include "core/components/container_modal/container_modal_constants.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"
namespace OHOS::Ace::NG {

void SubMenuLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto menuNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto props = AceType::DynamicCast<MenuLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(props);
    auto parentMenuItem = menuPattern->GetParentMenuItem();
    CHECK_NULL_VOID(parentMenuItem);
    InitCanExpandCurrentWindow(props->GetShowInSubWindowValue(false));
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        ModifySubMenuWrapper(layoutWrapper);
    }
    CheckMenuPadding(layoutWrapper);
    const auto& geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto parentItemPattern = parentMenuItem->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(parentItemPattern);
    auto expandingMode = parentItemPattern->GetExpandingMode();
    OffsetF position = GetSubMenuLayoutOffset(layoutWrapper, parentMenuItem, size,
        expandingMode == SubMenuExpandingMode::STACK);
    geometryNode->SetMarginFrameOffset(position);
    if (parentMenuItem) {
        UpdateHoverRegion(parentMenuItem, position, size);
    }
    auto child = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_VOID(child);
    child->Layout();
    ClipMenuPath(layoutWrapper);
}

void SubMenuLayoutAlgorithm::UpdateHoverRegion(
    RefPtr<FrameNode>& parentMenuItem, const OffsetF& position, const SizeF& size)
{
    auto parentPattern = parentMenuItem->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(parentPattern);
    auto bottomRightPoint = position + OffsetF(size.Width(), size.Height());
    auto pipelineContext = parentMenuItem->GetContextWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    auto windowManager = pipelineContext->GetWindowManager();
    auto isContainerModal = pipelineContext->GetWindowModal() == WindowModal::CONTAINER_MODAL && windowManager &&
                            windowManager->GetWindowMode() == WindowMode::WINDOW_MODE_FLOATING;
    OffsetF wrapperOffset;
    if ((!canExpandCurrentWindow_) && isContainerModal) {
        auto newOffsetX = static_cast<float>(CONTAINER_BORDER_WIDTH.ConvertToPx());
        if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_SIXTEEN)) {
            newOffsetX += static_cast<float>(CONTENT_PADDING.ConvertToPx());
        }
        auto newOffsetY = static_cast<float>(pipelineContext->GetCustomTitleHeight().ConvertToPx()) +
                          static_cast<float>(CONTAINER_BORDER_WIDTH.ConvertToPx());
        wrapperOffset = OffsetF(newOffsetX, newOffsetY);
    }
    parentPattern->AddHoverRegions(position + wrapperOffset, bottomRightPoint + wrapperOffset);
}

OffsetF SubMenuLayoutAlgorithm::GetSubMenuLayoutOffset(LayoutWrapper* layoutWrapper,
    const RefPtr<FrameNode>& parentMenuItem, const SizeF& size, bool stacked)
{
    OffsetF position;
    auto layoutDirection = layoutWrapper->GetLayoutProperty()->GetNonAutoLayoutDirection();
    position = MenuLayoutAvoidAlgorithm(parentMenuItem, size, stacked, layoutWrapper);
    if (layoutDirection == TextDirection::RTL) {
        position.SetX(wrapperSize_.Width() - position.GetX() - size.Width());
    }
    return position;
}

OffsetF SubMenuLayoutAlgorithm::MenuLayoutAvoidAlgorithm(const RefPtr<FrameNode>& parentMenuItem,
    const SizeF& size, bool stacked, LayoutWrapper* layoutWrapper)
{
    auto pipelineContext = PipelineContext::GetMainPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, NG::OffsetF(0.0f, 0.0f));
    auto menuItemSize = parentMenuItem->GetGeometryNode()->GetFrameSize();
    position_ = GetSubMenuPosition(parentMenuItem, stacked);
    if (layoutWrapper != nullptr) {
        auto menuLayoutProperty = layoutWrapper->GetLayoutProperty();
        CHECK_NULL_RETURN(menuLayoutProperty, NG::OffsetF(0.0f, 0.0f));
        auto layoutDirection = menuLayoutProperty->GetNonAutoLayoutDirection();
        if (layoutDirection == TextDirection::RTL) {
            float leftSpace = position_.GetX() - menuItemSize.Width();
            position_ = OffsetF(wrapperSize_.Width() - leftSpace, position_.GetY());
        }
    }
    float x = HorizontalLayoutSubMenu(size, position_.GetX(), menuItemSize);
    x = std::clamp(x, paddingStart_, wrapperSize_.Width() - size.Width() - paddingEnd_);
    float y = 0.0f;
    if (canExpandCurrentWindow_ || !Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        y = VerticalLayoutSubMenu(size, position_.GetY(), menuItemSize);
    } else {
        y = VerticalLayoutSubMenuHalfScreen(size, position_.GetY(), menuItemSize);
    }
    float yMinAvoid = wrapperRect_.Top() + paddingTop_;
    float yMaxAvoid = wrapperRect_.Bottom() - paddingBottom_ - size.Height();
    y = std::clamp(y, yMinAvoid, yMaxAvoid);
    return NG::OffsetF(x, y);
}

OffsetF SubMenuLayoutAlgorithm::GetSubMenuPosition(const RefPtr<FrameNode>& parentMenuItem, bool stacked)
{
    auto parentItemFrameSize = parentMenuItem->GetGeometryNode()->GetMarginFrameSize();
    OffsetF position;
    if (stacked) {
        auto parentItemPattern = parentMenuItem->GetPattern<MenuItemPattern>();
        if (parentItemPattern != nullptr) {
            auto parentMenu = parentItemPattern->GetMenu();
            position = parentMenu == nullptr
                ? parentMenuItem->GetPaintRectOffset(false, true) + OffsetF(parentItemFrameSize.Width(), 0.0)
                : OffsetF(parentMenu->GetPaintRectOffset(false, true).GetX(),
                    parentMenuItem->GetPaintRectOffset(false, true).GetY() +
                    parentItemFrameSize.Height()); // * 0.95
        }
    } else {
        position = parentMenuItem->GetPaintRectOffset(false, true) + OffsetF(parentItemFrameSize.Width(), 0.0);
    }

    auto pipelineContext = parentMenuItem->GetContextWithCheck();
    CHECK_NULL_RETURN(pipelineContext, OffsetF());
    auto windowManager = pipelineContext->GetWindowManager();
    CHECK_NULL_RETURN(windowManager, OffsetF());
    auto isContainerModal = pipelineContext->GetWindowModal() == WindowModal::CONTAINER_MODAL && windowManager &&
                            windowManager->GetWindowMode() == WindowMode::WINDOW_MODE_FLOATING;
    if ((!canExpandCurrentWindow_) && isContainerModal) {
        auto newOffsetX = static_cast<float>(CONTAINER_BORDER_WIDTH.ConvertToPx());
        if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
            newOffsetX += static_cast<float>(CONTENT_PADDING.ConvertToPx());
        }
        auto newOffsetY = static_cast<float>(pipelineContext->GetCustomTitleHeight().ConvertToPx()) +
                            static_cast<float>(CONTAINER_BORDER_WIDTH.ConvertToPx());
        position -= OffsetF(newOffsetX, newOffsetY);
    }
    auto parentMenu = AceType::DynamicCast<FrameNode>(parentMenuItem->GetParent());
    CHECK_NULL_RETURN(parentMenu, position);
    auto scroll = AceType::DynamicCast<FrameNode>(parentMenu->GetParent());
    CHECK_NULL_RETURN(scroll, position);
    while (scroll && (scroll->GetTag() != V2::SCROLL_ETS_TAG)) {
        scroll = AceType::DynamicCast<FrameNode>(scroll->GetParent());
    }
    CHECK_NULL_RETURN(scroll, position);
    auto scrollGeometryNode = scroll->GetGeometryNode();
    CHECK_NULL_RETURN(scrollGeometryNode, position);
    auto scrollTop = scroll->GetPaintRectOffset(false, true).GetY();
    auto scrollHeight = scrollGeometryNode->GetFrameSize().Height();
    auto bottomOffset = scrollTop + scrollHeight;
    if (parentMenuItem->GetPaintRectOffset(false, true).GetY() > bottomOffset) {
        return scroll->GetPaintRectOffset(false, true) + OffsetF(parentItemFrameSize.Width(), 0.0);
    }
    return position;
}

float SubMenuLayoutAlgorithm::VerticalLayoutSubMenuHalfScreen(
    const SizeF& size, float position, const SizeF& menuItemSize)
{
    auto pipelineContext = PipelineContext::GetMainPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, 0.0f);
    auto safeAreaManager = pipelineContext->GetSafeAreaManager();
    CHECK_NULL_RETURN(safeAreaManager, 0.0f);
    float wrapperHeight = wrapperSize_.Height();

    float bottomSpace = wrapperSize_.Height() - (position_.GetY() - param_.windowsOffsetY) - margin_ * 2.0f;
    // line up top of subMenu with top of the menuItem
    if (bottomSpace >= size.Height()) {
        return position;
    }
    // line up bottom of menu with bottom of the screen
    if (size.Height() < wrapperHeight) {
        return wrapperHeight - size.Height();
    }
    // can't fit in screen, line up with top of the screen
    return 0.0f;
}

// return submenu vertical offset
float SubMenuLayoutAlgorithm::VerticalLayoutSubMenu(const SizeF& size, float position, const SizeF& menuItemSize)
{
    float bottomSpace = wrapperRect_.Bottom() - position - paddingBottom_;
    // line up top of subMenu with top of the menuItem
    if (bottomSpace >= size.Height()) {
        return position;
    }
    // line up bottom of menu with bottom of the screen
    if (size.Height() < wrapperRect_.Height()) {
        return wrapperRect_.Bottom() - size.Height() - paddingBottom_;
    }
    // can't fit in screen, line up with top of the screen
    return wrapperRect_.Top() + paddingTop_;
}

// returns submenu horizontal offset
float SubMenuLayoutAlgorithm::HorizontalLayoutSubMenu(
    const SizeF& size, float position, const SizeF& menuItemSize, LayoutWrapper* layoutWrapper)
{
    float wrapperWidth = wrapperSize_.Width();
    float rightSpace = wrapperWidth - position - paddingEnd_;
    float leftSpace = position - menuItemSize.Width();
    if (layoutWrapper != nullptr) {
        auto menuLayoutProperty = layoutWrapper->GetLayoutProperty();
        CHECK_NULL_RETURN(menuLayoutProperty, 0.0f);
        auto layoutDirection = menuLayoutProperty->GetNonAutoLayoutDirection();
        if (layoutDirection == TextDirection::RTL) {
            rightSpace = position - menuItemSize.Width();
            leftSpace = wrapperWidth - position;
        }
    }
    // can fit subMenu on the right side of menuItem
    if (rightSpace >= size.Width()) {
        return position;
    }
    // fit subMenu on the left side of menuItem
    if (leftSpace >= size.Width()) {
        return position - size.Width() - menuItemSize.Width();
    }
    // line up right side of menu with right boundary of the screen
    if (size.Width() < wrapperWidth) {
        return wrapperWidth - size.Width() - paddingEnd_;
    }
    // can't fit in screen, line up with left side of the screen
    return 0.0f;
}

void SubMenuLayoutAlgorithm::ModifySubMenuWrapper(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto pipelineContext = PipelineContext::GetMainPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto safeAreaManager = pipelineContext->GetSafeAreaManager();
    CHECK_NULL_VOID(safeAreaManager);
    auto bottom = safeAreaManager->GetSystemSafeArea().bottom_.Length();
    if (!canExpandCurrentWindow_) {
        wrapperSize_ = SizeF(param_.menuWindowRect.Width(), param_.menuWindowRect.Height() - bottom);
    } else {
        wrapperSize_ = SizeF(wrapperSize_.Width(), wrapperSize_.Height());
    }
}

void SubMenuLayoutAlgorithm::InitializePadding(LayoutWrapper* layoutWrapper)
{
    auto menuPattern = layoutWrapper->GetHostNode()->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto host = menuPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    if (!menuPattern->IsSelectOverlayExtensionMenu()) {
        margin_ = static_cast<float>(theme->GetMenuPadding().ConvertToPx());
        paddingStart_ = static_cast<float>(theme->GetDefaultPaddingStart().ConvertToPx());
        paddingEnd_ = static_cast<float>(theme->GetDefaultPaddingEnd().ConvertToPx());
        if (!AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            paddingTop_ = static_cast<float>(theme->GetDefaultPaddingTop().ConvertToPx());
            paddingBottom_ = static_cast<float>(theme->GetDefaultPaddingBottomFixed().ConvertToPx());
        }
    }
}

void SubMenuLayoutAlgorithm::InitializePaddingAPI12(LayoutWrapper* layoutWrapper)
{
    auto menuNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto pipeline = PipelineContext::GetMainPipelineContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    if (!menuPattern->IsSelectOverlayExtensionMenu()) {
        margin_ = static_cast<float>(theme->GetMenuPadding().ConvertToPx());
        if (!canExpandCurrentWindow_) {
            paddingStart_ = static_cast<float>(theme->GetMenuLargeMargin().ConvertToPx());
            paddingEnd_ = static_cast<float>(theme->GetMenuLargeMargin().ConvertToPx());
        } else {
            paddingStart_ = static_cast<float>(theme->GetMenuMediumMargin().ConvertToPx());
            paddingEnd_ = static_cast<float>(theme->GetMenuMediumMargin().ConvertToPx());
        }
    }
}

void SubMenuLayoutAlgorithm::CheckMenuPadding(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        InitializePaddingAPI12(layoutWrapper);
    } else {
        InitializePadding(layoutWrapper);
    }
}

} // namespace OHOS::Ace::NG
