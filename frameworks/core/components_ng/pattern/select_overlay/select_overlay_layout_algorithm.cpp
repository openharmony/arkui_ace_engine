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

#include "core/components_ng/pattern/select_overlay/select_overlay_layout_algorithm.h"

#include <cmath>
#include <optional>

#include "base/geometry/ng/offset_t.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension MORE_MENU_INTERVAL = 8.0_vp;
}

void SelectOverlayLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto layoutConstraint = layoutProperty->CreateChildConstraint();
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto safeAreaManager = pipeline->GetSafeAreaManager();
    CHECK_NULL_VOID(safeAreaManager);
    auto keyboardHeight = safeAreaManager->GetKeyboardInset().Length();
    auto maxSize =
        SizeF(layoutConstraint.maxSize.Width(), layoutConstraint.maxSize.Height() - keyboardHeight -
                                                    (info_->isUsingMouse ? info_->rightClickOffset.GetY() : 0.0f));
    layoutConstraint.maxSize = maxSize;
    bool isMouseCustomMenu = false;
    if (info_->menuInfo.menuBuilder) {
        auto customMenuLayoutWrapper = layoutWrapper->GetChildByIndex(0);
        CHECK_NULL_VOID(customMenuLayoutWrapper);
        auto customMenuLayoutConstraint = layoutConstraint;
        CalculateCustomMenuLayoutConstraint(layoutWrapper, customMenuLayoutConstraint);
        customMenuLayoutWrapper->Measure(customMenuLayoutConstraint);
        isMouseCustomMenu = true;
    }
    auto childIndex = -1;
    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        childIndex++;
        if (childIndex == 0 && isMouseCustomMenu) {
            continue;
        }
        child->Measure(layoutConstraint);
    }
    PerformMeasureSelf(layoutWrapper);
}

void SelectOverlayLayoutAlgorithm::CalculateCustomMenuLayoutConstraint(
    LayoutWrapper* layoutWrapper, LayoutConstraintF& layoutConstraint)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_VOID(theme);
    // Calculate the spacing with text and handle, menu is fixed up the handle and text.
    double menuSpacingBetweenText = theme->GetMenuSpacingWithText().ConvertToPx();
    double menuSpacingBetweenHandle = theme->GetHandleDiameter().ConvertToPx();

    // paint rect is in global position, need to convert to local position
    auto offset = layoutWrapper->GetGeometryNode()->GetFrameOffset();
    const auto firstHandleRect = info_->firstHandle.paintRect - offset;
    const auto secondHandleRect = info_->secondHandle.paintRect - offset;

    auto topSpace = firstHandleRect.Top() - menuSpacingBetweenText - menuSpacingBetweenHandle;
    auto bottomSpace = layoutConstraint.maxSize.Height() -
                       (secondHandleRect.Bottom() + menuSpacingBetweenText + menuSpacingBetweenHandle);
    if (info_->isUsingMouse) {
        layoutConstraint.selfIdealSize = OptionalSizeF(std::nullopt, layoutConstraint.maxSize.Height());
    } else {
        layoutConstraint.selfIdealSize = OptionalSizeF(std::nullopt, std::max(topSpace, bottomSpace));
    }
}

OffsetF SelectOverlayLayoutAlgorithm::CalculateCustomMenuByMouseOffset(LayoutWrapper* layoutWrapper)
{
    auto menuOffset = info_->rightClickOffset;
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, menuOffset);
    auto layoutConstraint = layoutProperty->GetLayoutConstraint();
    CHECK_NULL_RETURN(layoutConstraint, menuOffset);
    auto menu = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_RETURN(menu, menuOffset);
    auto maxWidth = layoutConstraint->selfIdealSize.Width().value_or(0.0f);
    auto menuSize = menu->GetGeometryNode()->GetFrameSize();
    if (menuOffset.GetX() + menuSize.Width() > maxWidth && menuOffset.GetX() >= menuSize.Width()) {
        menuOffset.SetX(menuOffset.GetX() - menuSize.Width());
    }
    return menuOffset;
}

void SelectOverlayLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto menu = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_VOID(menu);
    if ((!CheckInShowArea(*info_) ||
            (!info_->firstHandle.isShow && !info_->secondHandle.isShow && !info_->isSelectRegionVisible)) &&
        !info_->isUsingMouse) {
        menu->SetActive(false);
        return;
    } else {
        menu->SetActive(true);
    }
    OffsetF menuOffset;
    if (info_->isUsingMouse) {
        menuOffset = CalculateCustomMenuByMouseOffset(layoutWrapper);
    } else {
        menuOffset = ComputeSelectMenuPosition(layoutWrapper);
    }
    menu->GetGeometryNode()->SetMarginFrameOffset(menuOffset);

    // custom menu need to layout all menu and submenu
    if (info_->menuInfo.menuBuilder) {
        for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
            child->Layout();
        }
        return;
    }
    menu->Layout();
    auto button = layoutWrapper->GetOrCreateChildByIndex(1);
    CHECK_NULL_VOID(button);
    auto menuNode = menu->GetHostNode();
    CHECK_NULL_VOID(menuNode);
    auto menuContext = menuNode->GetRenderContext();
    CHECK_NULL_VOID(menuContext);
    auto offset = OffsetF();
    if (menuContext->GetOffset()) {
        offset =
            OffsetF(menuContext->GetOffset()->GetX().ConvertToPx(), menuContext->GetOffset()->GetY().ConvertToPx());
    }
    if (!info_->menuInfo.menuIsShow || info_->menuInfo.menuDisable) {
        hasExtensionMenu_ = false;
        return;
    }
    hasExtensionMenu_ = true;
    button->GetGeometryNode()->SetMarginFrameOffset(menuOffset);
    button->Layout();
    auto extensionMenuOffset = ComputeExtensionMenuPosition(layoutWrapper, offset);

    auto extensionMenu = layoutWrapper->GetOrCreateChildByIndex(2);
    CHECK_NULL_VOID(extensionMenu);
    extensionMenu->GetGeometryNode()->SetMarginFrameOffset(extensionMenuOffset);
    extensionMenu->Layout();
}

bool SelectOverlayLayoutAlgorithm::CheckInShowArea(const SelectOverlayInfo& info)
{
    if (info.useFullScreen) {
        return true;
    }
    if (info.isSingleHandle) {
        return info.firstHandle.paintRect.IsWrappedBy(info.showArea);
    }
    return info.firstHandle.paintRect.IsWrappedBy(info.showArea) &&
           info.secondHandle.paintRect.IsWrappedBy(info.showArea);
}

OffsetF SelectOverlayLayoutAlgorithm::ComputeSelectMenuPosition(LayoutWrapper* layoutWrapper)
{
    auto menuItem = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_RETURN(menuItem, OffsetF());
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, OffsetF());
    auto theme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_RETURN(theme, OffsetF());
    OffsetF menuPosition;
    bool isExtension = false;

    // Calculate the spacing with text and handle, menu is fixed up the handle and text.
    double menuSpacingBetweenText = theme->GetMenuSpacingWithText().ConvertToPx();
    double menuSpacingBetweenHandle = theme->GetHandleDiameter().ConvertToPx();

    auto width = menuItem->GetGeometryNode()->GetMarginFrameSize().Width();
    auto height = menuItem->GetGeometryNode()->GetMarginFrameSize().Height();

    // When the extended menu is displayed, the default menu becomes circular, but the position of the circle is aligned
    // with the end of the original menu.
    if (GreatNotEqual(width, height)) {
        menuWidth_ = width;
        menuHeight_ = height;
    } else {
        isExtension = true;
    }
    auto menuWidth = menuWidth_.value_or(width);
    auto menuHeight = menuHeight_.value_or(height);

    // paint rect is in global position, need to convert to local position
    auto offset = layoutWrapper->GetGeometryNode()->GetFrameOffset();
    const auto firstHandleRect = info_->firstHandle.paintRect - offset;
    const auto secondHandleRect = info_->secondHandle.paintRect - offset;

    auto singleHandle = firstHandleRect;
    if (!info_->firstHandle.isShow) {
        singleHandle = secondHandleRect;
    }
    if (IsTextAreaSelectAll()) {
        singleHandle = RectF(info_->menuInfo.menuOffset.value().GetX(), info_->menuInfo.menuOffset.value().GetY(),
            singleHandle.Width(), singleHandle.Height());
    }

    if (info_->isSingleHandle) {
        auto menuSpacing = static_cast<float>(menuSpacingBetweenText);
        menuPosition = OffsetF((singleHandle.Left() + singleHandle.Right() - menuWidth) / 2.0f,
            static_cast<float>(singleHandle.Top() - menuSpacing - menuHeight));
    } else {
        auto menuSpacing = static_cast<float>(menuSpacingBetweenText + menuSpacingBetweenHandle);
        menuPosition = OffsetF((firstHandleRect.Left() + secondHandleRect.Left() - menuWidth) / 2.0f,
            static_cast<float>(firstHandleRect.Top() - menuSpacing - menuHeight));

        if (!info_->firstHandle.isShow && info_->secondHandle.isShow && !info_->handleReverse) {
            menuPosition.SetY(secondHandleRect.Bottom() + menuSpacing);
        }
        if (info_->firstHandle.isShow && !info_->secondHandle.isShow && info_->handleReverse) {
            menuPosition.SetY(firstHandleRect.Bottom() + menuSpacing);
        }
        if (info_->firstHandle.isShow && info_->secondHandle.isShow &&
            !NearEqual(firstHandleRect.Top(), secondHandleRect.Top())) {
            auto top = std::min(firstHandleRect.Top(), secondHandleRect.Top());
            menuPosition.SetY(static_cast<float>(top - menuSpacing - menuHeight));
        }
        if (!info_->firstHandle.isShow && info_->secondHandle.isShow) {
            menuPosition.SetX(secondHandleRect.Left() - menuWidth / 2.0f);
        }
        if (info_->firstHandle.isShow && !info_->secondHandle.isShow) {
            menuPosition.SetX(firstHandleRect.Left() - menuWidth / 2.0f);
        }
    }

    auto overlayWidth = layoutWrapper->GetGeometryNode()->GetFrameSize().Width();
    RectF viewPort = layoutWrapper->GetGeometryNode()->GetFrameRect() - offset;
    auto frameNode = info_->callerFrameNode.Upgrade();
    if (frameNode) {
        auto viewPortOption = frameNode->GetViewPort();
        if (viewPortOption.has_value()) {
            viewPort = viewPortOption.value();
        }
    }
    // Adjust position of overlay.
    auto adjustPositionXWithViewPort = [&](OffsetF& menuPosition) {
        if (LessOrEqual(menuPosition.GetX(), viewPort.GetX())) {
            menuPosition.SetX(theme->GetDefaultMenuPositionX());
        } else if (GreatOrEqual(menuPosition.GetX() + menuWidth, viewPort.GetX() + viewPort.Width())) {
            menuPosition.SetX(overlayWidth - menuWidth - theme->GetDefaultMenuPositionX());
        }
    };
    adjustPositionXWithViewPort(menuPosition);
    if (LessNotEqual(menuPosition.GetY(), menuHeight)) {
        if (IsTextAreaSelectAll()) {
            menuPosition.SetY(singleHandle.Top());
        } else {
            menuPosition.SetY(
                static_cast<float>(singleHandle.Bottom() + menuSpacingBetweenText + menuSpacingBetweenHandle));
        }
    }
    if (LessNotEqual(menuPosition.GetY(), viewPort.GetY() - menuSpacingBetweenText - menuHeight) ||
        LessNotEqual(menuPosition.GetY(), menuSpacingBetweenText)) {
        auto menuOffsetY = viewPort.GetY() - menuSpacingBetweenText - menuHeight;
        if (menuOffsetY > menuSpacingBetweenText) {
            menuPosition.SetY(menuOffsetY);
        } else {
            menuPosition.SetY(menuSpacingBetweenText);
        }
    } else if (GreatOrEqual(menuPosition.GetY(), viewPort.GetY() + viewPort.Height() + menuSpacingBetweenText)) {
        menuPosition.SetY(viewPort.GetY() + viewPort.Height() + menuSpacingBetweenText);
    }

    auto safeAreaManager = pipeline->GetSafeAreaManager();
    if (safeAreaManager) {
        // ignore status bar
        auto top = safeAreaManager->GetSystemSafeArea().top_.Length();
        if (menuPosition.GetY() < top) {
            menuPosition.SetY(top);
        }
    }
    if (info_->firstHandle.isShow && info_->secondHandle.isShow &&
        !NearEqual(firstHandleRect.Top(), secondHandleRect.Top())) {
        auto menuRect = RectF(menuPosition, SizeF(menuWidth, menuHeight));
        auto downHandleRect =
            LessNotEqual(firstHandleRect.Top(), secondHandleRect.Top()) ? secondHandleRect : firstHandleRect;
        auto circleDiameter = menuSpacingBetweenHandle;
        auto circleOffset =
            OffsetF(downHandleRect.GetX() - (circleDiameter - downHandleRect.Width()) / 2.0f, downHandleRect.Bottom());
        auto downHandleCircleRect = RectF(circleOffset, SizeF(circleDiameter, circleDiameter));
        if (menuRect.IsIntersectWith(downHandleRect) || menuRect.IsInnerIntersectWith(downHandleCircleRect)) {
            auto menuSpacing = static_cast<float>(menuSpacingBetweenText + circleDiameter);
            menuPosition.SetY(downHandleRect.Bottom() + menuSpacing);
        }
    }
    auto menuRect = RectF(menuPosition, SizeF(menuWidth, menuHeight));
    menuPosition = AdjustSelectMenuOffset(layoutWrapper, menuRect, menuSpacingBetweenText, menuSpacingBetweenHandle);
    adjustPositionXWithViewPort(menuPosition);
    defaultMenuEndOffset_ = menuPosition + OffsetF(menuWidth, 0.0f);
    if (isExtension) {
        return defaultMenuEndOffset_ - OffsetF(width, 0);
    }
    return menuPosition;
}

OffsetF SelectOverlayLayoutAlgorithm::AdjustSelectMenuOffset(
    LayoutWrapper* layoutWrapper, const RectF& menuRect, double spaceBetweenText, double spaceBetweenHandle)
{
    auto menuOffset = menuRect.GetOffset();
    if (!info_->firstHandle.isShow && !info_->secondHandle.isShow) {
        return menuOffset;
    }
    auto offset = layoutWrapper->GetGeometryNode()->GetFrameOffset();
    auto upHandle = info_->handleReverse ? info_->secondHandle : info_->firstHandle;
    auto downHandle = info_->handleReverse ? info_->firstHandle : info_->secondHandle;
    // the menu is too far away.
    auto pipeline = PipelineContext::GetCurrentContext();
    auto hostFrameNode = info_->callerFrameNode.Upgrade();
    if (pipeline && hostFrameNode) {
        auto hostFrameRect = hostFrameNode->GetGeometryNode()->GetFrameRect();
        auto hostGlobalOffset = hostFrameNode->GetPaintRectOffset() - pipeline->GetRootRect().GetOffset();
        auto centerX = menuRect.Width() / 2.0f;
        if (GreatNotEqual(menuRect.GetX() + centerX, hostGlobalOffset.GetX() + hostFrameRect.Width())) {
            menuOffset.SetX(hostGlobalOffset.GetX() + hostFrameRect.Width() - centerX);
        } else if (LessNotEqual(menuRect.GetX() + centerX, hostGlobalOffset.GetX())) {
            menuOffset.SetX(hostGlobalOffset.GetX() - centerX);
        }
    }
    // menu cover up handle
    auto upPaint = upHandle.paintRect - offset;
    auto downPaint = downHandle.paintRect - offset;
    if (upHandle.isShow && !downHandle.isShow) {
        auto circleOffset = OffsetF(
            upPaint.GetX() - (spaceBetweenHandle - upPaint.Width()) / 2.0f, upPaint.GetY() - spaceBetweenHandle);
        auto upCircleRect = RectF(circleOffset, SizeF(spaceBetweenHandle, spaceBetweenHandle));
        if (menuRect.IsIntersectWith(upPaint) || menuRect.IsIntersectWith(upCircleRect)) {
            menuOffset.SetY(upPaint.Bottom() + spaceBetweenText + spaceBetweenHandle);
        }
        return menuOffset;
    }
    // avoid soft keyboard and root bottom
    if (!upHandle.isShow && downHandle.isShow) {
        CHECK_NULL_RETURN(pipeline, menuOffset);
        auto safeAreaManager = pipeline->GetSafeAreaManager();
        CHECK_NULL_RETURN(safeAreaManager, menuOffset);
        auto keyboardInsert = safeAreaManager->GetKeyboardInset();
        auto shouldAvoidKeyboard =
            GreatNotEqual(keyboardInsert.Length(), 0.0f) && GreatNotEqual(menuRect.Bottom(), keyboardInsert.start);
        auto rootRect = layoutWrapper->GetGeometryNode()->GetFrameRect();
        auto shouldAvoidBottom = GreatNotEqual(menuRect.Bottom(), rootRect.Height());
        auto menuSpace = NearEqual(upPaint.Top(), downPaint.Top()) ? spaceBetweenHandle : spaceBetweenText;
        auto offsetY = downPaint.GetY() - menuSpace - menuRect.Height();
        if ((shouldAvoidKeyboard || shouldAvoidBottom) && offsetY > 0) {
            menuOffset.SetY(offsetY);
        }
    }
    return menuOffset;
}

OffsetF SelectOverlayLayoutAlgorithm::ComputeExtensionMenuPosition(LayoutWrapper* layoutWrapper, const OffsetF& offset)
{
    auto extensionItem = layoutWrapper->GetOrCreateChildByIndex(2);
    CHECK_NULL_RETURN(extensionItem, OffsetF());
    auto extensionLayoutConstraint = extensionItem->GetLayoutProperty()->GetLayoutConstraint();
    auto extensionLayoutConstraintMaxSize = extensionLayoutConstraint->maxSize;
    auto extensionWidth = extensionItem->GetGeometryNode()->GetMarginFrameSize().Width();
    auto extensionHeight = extensionItem->GetGeometryNode()->GetMarginFrameSize().Height();
    auto menuItem = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_RETURN(menuItem, OffsetF());
    auto menuHeight = menuItem->GetGeometryNode()->GetMarginFrameSize().Height();
    auto extensionOffset =
        defaultMenuEndOffset_ - OffsetF(extensionWidth, -menuHeight - MORE_MENU_INTERVAL.ConvertToPx());
    auto extensionBottom = extensionOffset.GetY() + extensionHeight;
    auto isCoveredBySoftKeyBoard = [extensionBottom]() -> bool {
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(pipeline, false);
        auto safeAreaManager = pipeline->GetSafeAreaManager();
        CHECK_NULL_RETURN(safeAreaManager, false);
        auto keyboardInsert = safeAreaManager->GetKeyboardInset();
        return GreatNotEqual(keyboardInsert.Length(), 0.0f) && GreatNotEqual(extensionBottom, keyboardInsert.start);
    };
    if (GreatNotEqual(extensionBottom, extensionLayoutConstraintMaxSize.Height()) || isCoveredBySoftKeyBoard()) {
        extensionOffset =
            defaultMenuEndOffset_ - OffsetF(extensionWidth, extensionHeight + MORE_MENU_INTERVAL.ConvertToPx());
    }
    return extensionOffset;
}

bool SelectOverlayLayoutAlgorithm::IsTextAreaSelectAll()
{
    return info_->menuInfo.menuOffset.has_value() && (!info_->firstHandle.isShow || !info_->secondHandle.isShow);
}

} // namespace OHOS::Ace::NG