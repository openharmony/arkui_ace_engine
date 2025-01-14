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
#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension MORE_MENU_INTERVAL = 8.0_vp;
constexpr float ROUND_EPSILON = 0.5f;
constexpr float CUSTOM_MENU_HEIGHT_CONSTRAINT_FACTOR = 0.8;
}

void SelectOverlayLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pattern = host->GetPattern<SelectOverlayPattern>();
    CHECK_NULL_VOID(pattern);
    if (pattern->GetMode() != SelectOverlayMode::HANDLE_ONLY) {
        MeasureChild(layoutWrapper);
    }
    PerformMeasureSelf(layoutWrapper);
    // match parent.
    if (pattern->GetMode() == SelectOverlayMode::HANDLE_ONLY) {
        auto geometryNode = layoutWrapper->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        auto parentNode = host->GetAncestorNodeOfFrame(false);
        CHECK_NULL_VOID(parentNode);
        auto parentGeo = parentNode->GetGeometryNode();
        CHECK_NULL_VOID(parentGeo);
        geometryNode->SetFrameSize(parentGeo->GetFrameSize());
    }
}

void SelectOverlayLayoutAlgorithm::MeasureChild(LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto layoutConstraint = layoutProperty->CreateChildConstraint();
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto safeAreaManager = pipeline->GetSafeAreaManager();
    CHECK_NULL_VOID(safeAreaManager);
    auto keyboardHeight = safeAreaManager->GetKeyboardInset().Length();
    auto safeAreaInsets = safeAreaManager->GetSafeAreaWithoutProcess();
    auto top = safeAreaInsets.top_.Length();
    auto bottom = GreatNotEqual(keyboardHeight, 0.0) ? 0.0 : safeAreaInsets.bottom_.Length();
    auto maxSize =
        SizeF(layoutConstraint.maxSize.Width(), layoutConstraint.maxSize.Height() - keyboardHeight - top - bottom);
    layoutConstraint.maxSize = maxSize;
    bool isMouseCustomMenu = false;
    if (info_->menuInfo.menuBuilder) {
        auto customMenuLayoutWrapper = layoutWrapper->GetChildByIndex(0);
        CHECK_NULL_VOID(customMenuLayoutWrapper);
        auto customNode = customMenuLayoutWrapper->GetHostNode();
        if (customNode && customNode->GetTag() != "SelectMenu") {
            auto customMenuLayoutConstraint = layoutConstraint;
            auto customMenuMaxHeight = GetCustomMenuMaxHeight(top, safeAreaInsets.bottom_.Length());
            if (GreatNotEqual(customMenuMaxHeight, 0.0)) {
                auto maxHeight = std::min(maxSize.Height(), customMenuMaxHeight);
                customMenuLayoutConstraint.maxSize.SetHeight(maxHeight);
            }
            customMenuLayoutConstraint.selfIdealSize =
                OptionalSizeF(std::nullopt, customMenuLayoutConstraint.maxSize.Height());
            customMenuLayoutWrapper->Measure(customMenuLayoutConstraint);
            isMouseCustomMenu = true;
        }
    }
    auto childIndex = -1;
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        childIndex++;
        if (childIndex == 0 && isMouseCustomMenu) {
            continue;
        }
        child->Measure(layoutConstraint);
    }
}

float SelectOverlayLayoutAlgorithm::GetCustomMenuMaxHeight(float topSafeArea, float bottomSafeArea)
{
    float defaultHeight = 0.0;
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipelineContext, defaultHeight);
    auto rect = pipelineContext->GetDisplayWindowRectInfo();
    return std::max(defaultHeight, static_cast<float>(rect.Height() - topSafeArea - bottomSafeArea)) *
           CUSTOM_MENU_HEIGHT_CONSTRAINT_FACTOR;
}

void SelectOverlayLayoutAlgorithm::CalculateCustomMenuLayoutConstraint(
    LayoutWrapper* layoutWrapper, LayoutConstraintF& layoutConstraint)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_VOID(theme);
    // Calculate the spacing with text and handle, menu is fixed up the handle and text.
    double menuSpacingBetweenText = theme->GetMenuSpacingWithText().ConvertToPx();
    double menuSpacingBetweenHandle = theme->GetHandleDiameter().ConvertToPx();

    // paint rect is in global position, need to convert to local position
    auto offset = layoutWrapper->GetGeometryNode()->GetFrameOffset();
    const auto firstHandleRect = info_->firstHandle.GetPaintRect() - offset;
    const auto secondHandleRect = info_->secondHandle.GetPaintRect() - offset;

    auto top = info_->isNewAvoid ? info_->selectArea.Top() : firstHandleRect.Top();
    auto bottom = info_->isNewAvoid ? info_->selectArea.Bottom() : secondHandleRect.Bottom();
    auto topSpace = top - menuSpacingBetweenText - menuSpacingBetweenHandle;
    auto bottomSpace = layoutConstraint.maxSize.Height() -
                       (bottom + menuSpacingBetweenText + menuSpacingBetweenHandle);
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
    if (GreatNotEqual(menuOffset.GetX() + menuSize.Width(), maxWidth)) {
        if (GreatOrEqual(menuOffset.GetX(), menuSize.Width())) {
            menuOffset.SetX(menuOffset.GetX() - menuSize.Width());
        } else if (LessOrEqual(menuSize.Width(), maxWidth)) {
            menuOffset.SetX(maxWidth - menuSize.Width());
        } else if (GreatNotEqual(menuSize.Width(), maxWidth)) {
            menuOffset.SetX(menuOffset.GetX() - menuSize.Width() / 2.0f);
        }
    }
    auto maxHeight = layoutConstraint->selfIdealSize.Height().value_or(0.0f);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, menuOffset);
    auto safeAreaManager = pipeline->GetSafeAreaManager();
    CHECK_NULL_RETURN(safeAreaManager, menuOffset);
    auto keyboardInsert = safeAreaManager->GetKeyboardInset();
    auto keyboardY = maxHeight - keyboardInsert.Length();
    uint32_t top = safeAreaManager->GetSystemSafeArea().top_.Length();
    if (GreatNotEqual(menuOffset.GetY() + menuSize.Height(), keyboardY)) {
        auto currentY = menuOffset.GetY();
        if (GreatOrEqual(currentY, menuSize.Height())) {
            currentY = menuOffset.GetY() - menuSize.Height();
        } else if (LessOrEqual(menuSize.Height(), keyboardY)) {
            currentY = keyboardY - menuSize.Height();
        } else if (GreatNotEqual(menuSize.Height(), keyboardY)) {
            currentY = menuOffset.GetY() - menuSize.Height() / 2.0f;
        }
        if (GreatNotEqual(top, currentY)) {
            currentY = top;
        }
        menuOffset.SetY(currentY);
    }
    return menuOffset;
}

void SelectOverlayLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pattern = host->GetPattern<SelectOverlayPattern>();
    CHECK_NULL_VOID(pattern);
    if (pattern->GetMode() != SelectOverlayMode::HANDLE_ONLY) {
        CheckHandleIsInClipViewPort();
        LayoutChild(layoutWrapper, pattern->GetMode());
    }
}

void SelectOverlayLayoutAlgorithm::LayoutChild(LayoutWrapper* layoutWrapper, SelectOverlayMode mode)
{
    auto menu = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_VOID(menu);
    auto shouldInActiveByHandle =
        !info_->firstHandle.isShow && !info_->secondHandle.isShow && !info_->isSelectRegionVisible;
    if ((!CheckInShowArea(*info_) || (!info_->isNewAvoid && shouldInActiveByHandle)) && !info_->isUsingMouse) {
        menu->SetActive(false);
        return;
    }
    menu->SetActive(true);
    OffsetF menuOffset = info_->isUsingMouse ? CalculateCustomMenuByMouseOffset(layoutWrapper)
                                             : ComputeSelectMenuPosition(layoutWrapper);
    auto menuGetGeometryNode = menu->GetGeometryNode();
    CHECK_NULL_VOID(menuGetGeometryNode);
    menuGetGeometryNode->SetMarginFrameOffset(menuOffset);
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
    if ((!info_->menuInfo.menuIsShow || info_->menuInfo.menuDisable) && mode != SelectOverlayMode::MENU_ONLY) {
        hasExtensionMenu_ = false;
        return;
    }
    hasExtensionMenu_ = true;
    auto buttonSize = button->GetGeometryNode()->GetMarginFrameSize();
    auto menuSize = menu->GetGeometryNode()->GetMarginFrameSize();
    bool isReverse = IsReverseLayout(layoutWrapper);
    OffsetF buttonOffset;
    if (GreatNotEqual(menuSize.Width(), menuSize.Height())) {
        auto diffY = std::max((menuSize.Height() - buttonSize.Height()) / 2.0f, 0.0f);
        buttonOffset = isReverse ? OffsetF(menuOffset.GetX(), menuOffset.GetY() + diffY) :
            OffsetF(menuOffset.GetX() + menuSize.Width() - buttonSize.Width(), menuOffset.GetY() + diffY);
    } else {
        buttonOffset = menuOffset;
    }
    button->GetGeometryNode()->SetMarginFrameOffset(buttonOffset);
    button->Layout();

    LayoutExtensionMenu(layoutWrapper, button);
}

void SelectOverlayLayoutAlgorithm::LayoutExtensionMenu(
    LayoutWrapper* layoutWrapper, const RefPtr<LayoutWrapper>& button)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto selectOverlayNode = DynamicCast<SelectOverlayNode>(host);
    CHECK_NULL_VOID(selectOverlayNode);
    // Avoid menu layout while the back animation is playing.
    if (!selectOverlayNode->GetIsExtensionMenu() && selectOverlayNode->GetAnimationStatus()) {
        return;
    }
    auto extensionMenu = layoutWrapper->GetOrCreateChildByIndex(2);
    CHECK_NULL_VOID(extensionMenu);
    extensionMenu->Layout();
    CheckHideBackOrMoreButton(extensionMenu, button);
}

void SelectOverlayLayoutAlgorithm::CheckHideBackOrMoreButton(
    const RefPtr<LayoutWrapper>& extensionMenu, const RefPtr<LayoutWrapper>& button)
{
    auto extensionMenuRect = extensionMenu->GetGeometryNode()->GetFrameRect();
    auto buttonRect = button->GetGeometryNode()->GetFrameRect();
    auto constraintRect = extensionMenuRect.Constrain(buttonRect);
    if (GreatNotEqual(constraintRect.Width(), 0.0f) && GreatNotEqual(constraintRect.Height(), 0.0f)) {
        hideMoreOrBack_ = true;
    }
}

bool SelectOverlayLayoutAlgorithm::CheckInShowArea(const SelectOverlayInfo& info)
{
    if (info.useFullScreen) {
        return true;
    }
    if (info.isSingleHandle) {
        return info.firstHandle.GetPaintRect().IsWrappedBy(info.showArea);
    }
    return info.firstHandle.GetPaintRect().IsWrappedBy(info.showArea) &&
           info.secondHandle.GetPaintRect().IsWrappedBy(info.showArea);
}

OffsetF SelectOverlayLayoutAlgorithm::ComputeSelectMenuPosition(LayoutWrapper* layoutWrapper)
{
    auto menuItem = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_RETURN(menuItem, OffsetF());
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, OffsetF());
    auto theme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_RETURN(theme, OffsetF());
    OffsetF menuPosition;
    bool isExtension = false;
    bool isReverse = IsReverseLayout(layoutWrapper);

    // Calculate the spacing with text and handle, menu is fixed up the handle and text.
    double menuSpacingBetweenText = theme->GetMenuSpacingWithText().ConvertToPx();
    double menuSpacingBetweenHandle = theme->GetHandleDiameter().ConvertToPx();

    // When the extended menu is displayed, the default menu becomes circular, but the position of the circle is aligned
    // with the end of the original menu.
    auto width = menuItem->GetGeometryNode()->GetMarginFrameSize().Width();
    auto height = menuItem->GetGeometryNode()->GetMarginFrameSize().Height();

    auto backButton = layoutWrapper->GetOrCreateChildByIndex(1);
    bool isBackButtonVisible = false;
    if (backButton) {
        isBackButtonVisible =
            backButton->GetLayoutProperty()->GetVisibilityValue(VisibleType::INVISIBLE) == VisibleType::VISIBLE;
    }
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, OffsetF());
    auto selectOverlayNode = DynamicCast<SelectOverlayNode>(host);
    CHECK_NULL_RETURN(selectOverlayNode, OffsetF());
    auto isExtensionMEnu = selectOverlayNode->GetIsExtensionMenu();
    if (!isBackButtonVisible && !isExtensionMEnu) {
        menuWidth_ = width;
        menuHeight_ = height;
    } else {
        isExtension = true;
    }
    auto menuWidth = menuWidth_.value_or(width);
    auto menuHeight = menuHeight_.value_or(height);

    // paint rect is in global position, need to convert to local position
    auto offset = layoutWrapper->GetGeometryNode()->GetFrameOffset();
    const auto firstHandleRect = info_->firstHandle.GetPaintRect() - offset;
    const auto secondHandleRect = info_->secondHandle.GetPaintRect() - offset;

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
    auto overlayVP = viewPort;
    info_->GetCallerNodeAncestorViewPort(viewPort);
    // Adjust position of overlay.
    auto adjustPositionXWithViewPort = [&](OffsetF& menuPosition) {
        auto defaultMenuPositionX = theme->GetDefaultMenuPositionX();
        if (LessOrEqual(menuPosition.GetX(), defaultMenuPositionX)) {
            menuPosition.SetX(defaultMenuPositionX);
        } else if (GreatOrEqual(
            menuPosition.GetX() + menuWidth, overlayVP.GetX() + overlayVP.Width() - defaultMenuPositionX)) {
            menuPosition.SetX(overlayWidth - menuWidth - defaultMenuPositionX);
        }
    };
    adjustPositionXWithViewPort(menuPosition);
    auto safeAreaManager = pipeline->GetSafeAreaManager();
    if (LessNotEqual(menuPosition.GetY(), menuHeight)) {
        if (IsTextAreaSelectAll()) {
            menuPosition.SetY(singleHandle.Top());
        } else if (info_->isSingleHandle &&
            IsMenuAreaSmallerHandleArea(singleHandle, menuHeight, menuSpacingBetweenText)) {
            if (safeAreaManager && safeAreaManager->GetSystemSafeArea().top_.Length() > singleHandle.Top()) {
                menuPosition.SetY(
                    static_cast<float>(singleHandle.Bottom() + menuSpacingBetweenText + menuSpacingBetweenHandle));
            }
        } else {
            menuPosition.SetY(
                static_cast<float>(singleHandle.Bottom() + menuSpacingBetweenText + menuSpacingBetweenHandle));
        }
    }
    auto spaceBetweenViewPort = menuSpacingBetweenText + menuSpacingBetweenHandle;
    if (LessNotEqual(menuPosition.GetY(), viewPort.GetY() - spaceBetweenViewPort - menuHeight) ||
        LessNotEqual(menuPosition.GetY(), menuSpacingBetweenText)) {
        auto menuOffsetY = viewPort.GetY() - spaceBetweenViewPort - menuHeight;
        if (GreatNotEqual(menuOffsetY, menuSpacingBetweenText)) {
            menuPosition.SetY(menuOffsetY);
        } else {
            menuPosition.SetY(menuSpacingBetweenText);
        }
    } else if (GreatOrEqual(menuPosition.GetY(), viewPort.GetY() + viewPort.Height() + spaceBetweenViewPort)) {
        menuPosition.SetY(viewPort.GetY() + viewPort.Height() + spaceBetweenViewPort);
    }

    if (safeAreaManager && !(info_->isSingleHandle &&
        IsMenuAreaSmallerHandleArea(singleHandle, menuHeight, menuSpacingBetweenText))) {
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
    menuPosition =
        info_->isNewAvoid && !info_->isSingleHandle
            ? NewMenuAvoidStrategy(layoutWrapper, menuWidth, menuHeight)
            : AdjustSelectMenuOffset(layoutWrapper, menuRect, menuSpacingBetweenText, menuSpacingBetweenHandle);
    AdjustMenuInRootRect(menuPosition, menuRect.GetSize(), layoutWrapper->GetGeometryNode()->GetFrameSize());

    defaultMenuStartOffset_ = menuPosition;
    defaultMenuEndOffset_ = menuPosition + OffsetF(menuWidth, 0.0f);
    // back and more button layout is on the left side of the selectmenu when reverse layout.
    if (isExtension && !isReverse) {
        return defaultMenuEndOffset_ - OffsetF(width, 0);
    }
    return menuPosition;
}

void SelectOverlayLayoutAlgorithm::AdjustMenuInRootRect(
    OffsetF& menuOffset, const SizeF& menuSize, const SizeF& rootSize)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_VOID(theme);
    // adjust x
    auto defaultPositionX = theme->GetDefaultMenuPositionX();
    auto menuX = LessOrEqual(menuOffset.GetX(), defaultPositionX) ? defaultPositionX : menuOffset.GetX();
    menuX = GreatOrEqual(menuX + menuSize.Width(), rootSize.Width() - defaultPositionX)
                ? rootSize.Width() - defaultPositionX - menuSize.Width()
                : menuX;
    menuOffset.SetX(menuX);
    // adjust y
    auto menuY = LessNotEqual(menuOffset.GetY(), 0.0f) ? 0.0f : menuOffset.GetY();
    menuY = GreatNotEqual(menuY + menuSize.Height(), rootSize.Height()) ? rootSize.Height() - menuSize.Height() : menuY;
    menuOffset.SetY(menuY);
}

OffsetF SelectOverlayLayoutAlgorithm::AdjustSelectMenuOffset(
    LayoutWrapper* layoutWrapper, const RectF& menuRect, double spaceBetweenText, double spaceBetweenHandle)
{
    auto menuOffset = menuRect.GetOffset();
    CHECK_NULL_RETURN((info_->firstHandle.isShow || info_->secondHandle.isShow),
        AdjustSelectMenuOffsetWhenHandlesUnshown(menuRect, spaceBetweenText));
    auto offset = layoutWrapper->GetGeometryNode()->GetFrameOffset();
    auto upHandle = info_->handleReverse ? info_->secondHandle : info_->firstHandle;
    auto downHandle = info_->handleReverse ? info_->firstHandle : info_->secondHandle;
    AdjustMenuTooFarAway(menuOffset, menuRect);
    // menu cover up handle
    auto upPaint = upHandle.GetPaintRect() - offset;
    auto downPaint = downHandle.GetPaintRect() - offset;
    if (!info_->isSingleHandle && upHandle.isShow && !downHandle.isShow) {
        auto circleOffset = OffsetF(
            upPaint.GetX() - (spaceBetweenHandle - upPaint.Width()) / 2.0f, upPaint.GetY() - spaceBetweenHandle);
        auto upCircleRect = RectF(circleOffset, SizeF(spaceBetweenHandle, spaceBetweenHandle));
        if (menuRect.IsIntersectWith(upPaint) || menuRect.IsIntersectWith(upCircleRect)) {
            menuOffset.SetY(upPaint.Bottom() + spaceBetweenText + spaceBetweenHandle);
        }
        return menuOffset;
    }
    // avoid soft keyboard and root bottom
    if ((!upHandle.isShow && downHandle.isShow) || info_->menuInfo.menuBuilder) {
        auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
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
        auto topArea = safeAreaManager->GetSystemSafeArea().top_.Length();
        if ((shouldAvoidKeyboard || shouldAvoidBottom) && GreatNotEqual(offsetY, 0)) {
            if (GreatNotEqual(topArea, offsetY)) {
                offsetY = downPaint.Bottom() - spaceBetweenText - menuRect.Height();
            }
            menuOffset.SetY(offsetY);
        } else {
            if (GreatNotEqual(topArea, menuOffset.GetY()) && info_->isSingleHandle) {
                menuOffset.SetY(downPaint.Bottom() + spaceBetweenText + spaceBetweenHandle);
            }
            AdjustMenuOffsetAtSingleHandleBottom(downPaint, menuRect, menuOffset, spaceBetweenText);
        }
    }
    return menuOffset;
}

void SelectOverlayLayoutAlgorithm::AdjustMenuOffsetAtSingleHandleBottom(const RectF handleRect, const RectF& menuRect,
    OffsetF& menuOffset, double spaceBetweenText)
{
    CHECK_NULL_VOID(info_->isSingleHandle);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto safeAreaManager = pipeline->GetSafeAreaManager();
    CHECK_NULL_VOID(safeAreaManager);
    auto keyboardInsert = safeAreaManager->GetKeyboardInset();
    auto shouldAvoidKeyboard = GreatNotEqual(keyboardInsert.Length(), 0.0f) &&
                               GreatNotEqual(menuOffset.GetY() + menuRect.Height(), keyboardInsert.start);
    if (shouldAvoidKeyboard) {
        menuOffset.SetY(handleRect.Bottom() - spaceBetweenText - menuRect.Height());
    }
}

OffsetF SelectOverlayLayoutAlgorithm::AdjustSelectMenuOffsetWhenHandlesUnshown(const RectF& menuRect,
    double spaceBetweenText)
{
    auto menuOffset = menuRect.GetOffset();
    CHECK_NULL_RETURN(info_->isSingleHandle, menuOffset);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, menuOffset);
    auto safeAreaManager = pipeline->GetSafeAreaManager();
    CHECK_NULL_RETURN(safeAreaManager, menuOffset);
    auto topArea = safeAreaManager->GetSystemSafeArea().top_.Length();
    auto selectArea = info_->selectArea;
    if (topArea > menuOffset.GetY()) {
        menuOffset.SetY((selectArea.Top() + selectArea.Bottom() - menuRect.Height()) / 2.0f);
        return menuOffset;
    }
    auto keyboardInsert = safeAreaManager->GetKeyboardInset();
    auto shouldAvoidKeyboard = GreatNotEqual(keyboardInsert.Length(), 0.0f) &&
        GreatNotEqual(menuRect.Bottom(), keyboardInsert.start);
    auto isBottomTouchKeyboard = GreatNotEqual(keyboardInsert.Length(), 0.0f) &&
        GreatNotEqual(selectArea.Bottom(), keyboardInsert.start);
    if (!isBottomTouchKeyboard && shouldAvoidKeyboard) {
        menuOffset.SetY(selectArea.Bottom() - spaceBetweenText - menuRect.Height());
        return menuOffset;
    }
    if (shouldAvoidKeyboard) {
        menuOffset.SetY((selectArea.Top() + selectArea.Bottom() - menuRect.Height()) / 2.0f);
    }
    return menuOffset;
}

bool SelectOverlayLayoutAlgorithm::IsMenuAreaSmallerHandleArea(RectF handleRect, float menuHeight, float menuDistance)
{
    return handleRect.Height() > menuHeight + menuDistance;
}

void SelectOverlayLayoutAlgorithm::AdjustMenuTooFarAway(OffsetF& menuOffset, const RectF& menuRect)
{
    // the menu is too far away.
    auto hostFrameNode = info_->callerFrameNode.Upgrade();
    CHECK_NULL_VOID(hostFrameNode);
    auto pipeline = hostFrameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto hostFrameRect = hostFrameNode->GetGeometryNode()->GetFrameRect();
    auto hostGlobalOffset = hostFrameNode->GetPaintRectOffset() - pipeline->GetRootRect().GetOffset();
    auto centerX = menuRect.Width() / 2.0f;
    if (info_->callerNodeInfo) {
        hostFrameRect = info_->callerNodeInfo->paintFrameRect;
        hostGlobalOffset = info_->callerNodeInfo->paintOffset;
    }
    if (GreatNotEqual(menuRect.GetX() + centerX, hostGlobalOffset.GetX() + hostFrameRect.Width())) {
        menuOffset.SetX(hostGlobalOffset.GetX() + hostFrameRect.Width() - centerX);
        return;
    }
    if (LessNotEqual(menuRect.GetX() + centerX, hostGlobalOffset.GetX())) {
        menuOffset.SetX(hostGlobalOffset.GetX() - centerX);
    }
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
        auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
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

OffsetF SelectOverlayLayoutAlgorithm::NewMenuAvoidStrategy(
    LayoutWrapper* layoutWrapper, float menuWidth, float menuHeight)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, OffsetF());
    auto theme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_RETURN(theme, OffsetF());
    double menuSpacingBetweenText = theme->GetMenuSpacingWithText().ConvertToPx();
    double menuSpacingBetweenHandle = theme->GetHandleDiameter().ConvertToPx() +
                                      theme->GetHandleDiameterStrokeWidth().ConvertToPx();
    double safeSpacing = theme->GetMenuSafeSpacing().ConvertToPx();
    auto selectArea = info_->selectArea;
    // 安全区域
    auto safeAreaManager = pipeline->GetSafeAreaManager();
    CHECK_NULL_RETURN(safeAreaManager, OffsetF());
    auto topArea = safeAreaManager->GetSystemSafeArea().top_.Length();
    auto keyboardInsert = safeAreaManager->GetKeyboardInset();
    float positionX = (selectArea.Left() + selectArea.Right() - menuWidth) / 2.0f;
    auto hasKeyboard = GreatNotEqual(keyboardInsert.Length(), 0.0f);
    auto downHandle = info_->handleReverse ? info_->firstHandle : info_->secondHandle;
    auto downHandleIsReallyShow = hasKeyboard ? ((LessOrEqual((double)downHandle.paintRect.Bottom(),
        (double)keyboardInsert.start)) ? true : false) : downHandle.isShow;
    auto upHandle = info_->handleReverse ? info_->secondHandle : info_->firstHandle;
    auto offset = layoutWrapper->GetGeometryNode()->GetFrameOffset();
    auto upPaint = upHandle.GetPaintRect() - offset;
    auto downPaint = downHandle.GetPaintRect() - offset;
    auto viewPort = pipeline->GetRootRect();
    auto selectAndRootRectArea = selectArea.IntersectRectT(viewPort);
    auto safeAreaBottom = safeAreaManager->GetSafeAreaWithoutProcess().bottom_.start;
    auto menuAvoidBottomY = GreatNotEqual(safeAreaBottom, 0.0f) ? (safeAreaBottom - menuHeight)
        : (viewPort.Bottom() - menuHeight);
    auto bottomLimitOffsetY = hasKeyboard ? std::max(keyboardInsert.start - safeSpacing - menuHeight, (double)topArea)
        : menuAvoidBottomY;

    AvoidStrategyMember avoidStrategyMember;
    avoidStrategyMember.menuHeight = menuHeight;
    avoidStrategyMember.menuSpacingBetweenText = menuSpacingBetweenText;
    avoidStrategyMember.bottomLimitOffsetY = bottomLimitOffsetY;
    avoidStrategyMember.menuSpacing = static_cast<float>(menuSpacingBetweenText + menuSpacingBetweenHandle);
    avoidStrategyMember.hasKeyboard = GreatNotEqual(keyboardInsert.Length(), 0.0f);
    avoidStrategyMember.keyboardInsertStart = keyboardInsert.start;
    avoidStrategyMember.downHandleIsReallyShow = downHandle.isShow && downHandleIsReallyShow;
    avoidStrategyMember.selectAreaTop = selectArea.Top();
    avoidStrategyMember.selectAndRootRectAreaTop = upHandle.isShow ? upPaint.Top() : selectAndRootRectArea.Top();
    avoidStrategyMember.selectAndRootRectAreaBottom =
        avoidStrategyMember.downHandleIsReallyShow ? downPaint.Bottom() : selectAndRootRectArea.Bottom();
    float offsetY = 0.0f;
    NewMenuAvoidStrategyGetY(avoidStrategyMember, offsetY);
    return OffsetF(positionX, offsetY);
}

void SelectOverlayLayoutAlgorithm::NewMenuAvoidStrategyGetY(const AvoidStrategyMember& avoidStrategyMember,
                                                            float& offsetY)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto safeAreaManager = pipeline->GetSafeAreaManager();
    CHECK_NULL_VOID(safeAreaManager);
    auto topArea = safeAreaManager->GetSystemSafeArea().top_.Length();
    auto upHandle = info_->handleReverse ? info_->secondHandle : info_->firstHandle;
    // 顶部避让
    offsetY = upHandle.isShow ? (avoidStrategyMember.selectAreaTop - avoidStrategyMember.menuSpacing -
                  avoidStrategyMember.menuHeight) : (avoidStrategyMember.selectAreaTop -
                  avoidStrategyMember.menuSpacingBetweenText - avoidStrategyMember.menuHeight);
    if (!upHandle.isShow || LessOrEqual(offsetY, topArea)) {
        auto selectBottom = avoidStrategyMember.hasKeyboard ? std::min(avoidStrategyMember.selectAndRootRectAreaBottom,
            (double)avoidStrategyMember.keyboardInsertStart) : avoidStrategyMember.selectAndRootRectAreaBottom;
        auto offsetBetweenSelectArea =
            std::clamp((double)(avoidStrategyMember.selectAndRootRectAreaTop + selectBottom -
                avoidStrategyMember.menuHeight) / 2.0f, (double)topArea, avoidStrategyMember.bottomLimitOffsetY);
        auto offsetYTmp = avoidStrategyMember.downHandleIsReallyShow ?
                                  (avoidStrategyMember.selectAndRootRectAreaBottom + avoidStrategyMember.menuSpacing) :
                                  (avoidStrategyMember.selectAndRootRectAreaBottom +
                                  avoidStrategyMember.menuSpacingBetweenText);
        if (avoidStrategyMember.downHandleIsReallyShow) {
            bool isOffsetYInBottom = false;
            // The upper handle is not visible and not in a single row, or offsetY <= topArea
            if ((!upHandle.isShow && !info_->isSingleLine) || (LessOrEqual(offsetY, topArea))) {
                offsetY = offsetYTmp;
                isOffsetYInBottom = true;
            }
            if (isOffsetYInBottom && GreatNotEqual(offsetY, avoidStrategyMember.bottomLimitOffsetY)) {
                offsetY = offsetBetweenSelectArea;
            }
        } else {
            if (info_->isSingleLine) {
                offsetY = LessOrEqual(offsetY, topArea) ?
                    ((GreatNotEqual(offsetYTmp, avoidStrategyMember.bottomLimitOffsetY)) ?
                        offsetBetweenSelectArea : offsetYTmp) : offsetY;
            } else {
                offsetY = offsetBetweenSelectArea;
            }
        }
    }
    if (avoidStrategyMember.hasKeyboard && GreatNotEqual(offsetY, avoidStrategyMember.bottomLimitOffsetY)) {
        offsetY = avoidStrategyMember.bottomLimitOffsetY;
    }
}

bool SelectOverlayLayoutAlgorithm::IsReverseLayout(LayoutWrapper* layoutWrapper) const
{
    CHECK_NULL_RETURN(layoutWrapper, false);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, false);
    return layoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;
}

void SelectOverlayLayoutAlgorithm::CheckHandleIsInClipViewPort()
{
    if (!info_->clipHandleDrawRect || info_->secondHandle.isPaintHandleWithPoints ||
        info_->handleLevelMode == HandleLevelMode::EMBED) {
        return;
    }
    if (!info_->isSingleHandle) {
        RectF viewPort;
        info_->GetCallerNodeAncestorViewPort(viewPort);
        auto isInRegion = [](const RectF& viewPort, float left, float right, float verticalY) {
            return LessOrEqual(left, viewPort.Right()) &&
                   GreatOrEqual(right, viewPort.Left()) &&
                   GreatOrEqual(verticalY, viewPort.Top() - ROUND_EPSILON) &&
                   LessOrEqual(verticalY, viewPort.Bottom() + ROUND_EPSILON);
        };
        auto& handleOnTop = !info_->handleReverse ? info_->firstHandle : info_->secondHandle;
        handleOnTop.isShow = isInRegion(
            viewPort, handleOnTop.paintRect.Left(), handleOnTop.paintRect.Right(), handleOnTop.paintRect.Top());
        auto& handleOnBottom = !info_->handleReverse ? info_->secondHandle : info_->firstHandle;
        handleOnBottom.isShow = isInRegion(viewPort, handleOnBottom.paintRect.Left(), handleOnBottom.paintRect.Right(),
            handleOnBottom.paintRect.Bottom());
    }
}
} // namespace OHOS::Ace::NG
