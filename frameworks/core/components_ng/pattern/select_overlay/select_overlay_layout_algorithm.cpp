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

#include <optional>

#include "base/geometry/ng/offset_t.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void SelectOverlayLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto menu = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_VOID(menu);
    if (!CheckInShowArea(info_)) {
        LayoutWrapper::RemoveChildInRenderTree(menu);
        return;
    }
    auto menuOffset = ComputeSelectMenuPosition(layoutWrapper);
    menu->GetGeometryNode()->SetMarginFrameOffset(menuOffset);
    menu->Layout();

    auto exetensionMenu = layoutWrapper->GetOrCreateChildByIndex(1);
    CHECK_NULL_VOID(exetensionMenu);
    auto menuNode = menu->GetHostNode();
    CHECK_NULL_VOID(menuNode);
    auto menuContext = menuNode->GetRenderContext();
    CHECK_NULL_VOID(menuContext);
    auto offset = OffsetF();
    if (menuContext->GetOffset()) {
        offset =
            OffsetF(menuContext->GetOffset()->GetX().ConvertToPx(), menuContext->GetOffset()->GetY().ConvertToPx());
    }
    if (!info_->menuInfo.menuIsShow) {
        hasExtensitonMenu_ = false;
        return;
    }
    hasExtensitonMenu_ = true;
    // Adjust the constraint of extensionMenu
    RemeasureExtensionMenu(layoutWrapper, offset);
    auto extensionMenuOffset = ComputeExtensionMenuPosition(layoutWrapper, offset);
    exetensionMenu->GetGeometryNode()->SetMarginFrameOffset(extensionMenuOffset);
    exetensionMenu->Layout();
}

void SelectOverlayLayoutAlgorithm::RemeasureExtensionMenu(LayoutWrapper* layoutWrapper, const OffsetF& offset)
{
    auto extensionItem = layoutWrapper->GetOrCreateChildByIndex(1);
    CHECK_NULL_VOID(extensionItem);

    auto layoutConstraint = extensionItem->GetLayoutProperty()->GetLayoutConstraint();
    auto layoutConstraintMaxSize = layoutConstraint->maxSize;

    layoutConstraint->maxSize =
        SizeF(defaultMenuEndOffset_.GetX(), layoutConstraintMaxSize.Height() - defaultMenuEndOffset_.GetY());
    extensionItem->Measure(layoutConstraint);
}

bool SelectOverlayLayoutAlgorithm::CheckInShowArea(const std::shared_ptr<SelectOverlayInfo>& info)
{
    if (info->useFullScreen) {
        return true;
    }
    if (info->isSingleHandle) {
        return info->firstHandle.paintRect.IsWrappedBy(info->showArea);
    }
    return info->firstHandle.paintRect.IsWrappedBy(info->showArea) &&
           info->secondHandle.paintRect.IsWrappedBy(info->showArea);
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

    // Calculate the spacing with text and handle, menu is fixed up the handle and text.
    double menuSpacingBetweenText = theme->GetMenuSpacingWithText().ConvertToPx();
    double menuSpacingBetweenHandle = theme->GetHandleDiameter().ConvertToPx();

    auto menuWidth = menuItem->GetGeometryNode()->GetMarginFrameSize().Width();
    auto menuHeight = menuItem->GetGeometryNode()->GetMarginFrameSize().Height();

    // When the extended menu is displayed, the default menu becomes circular, but the position of the circle is aligned
    // with the end of the original menu.
    if (GreatNotEqual(menuWidth, menuHeight)) {
        menuWidth_ = menuWidth;
    } else {
        return defaultMenuEndOffset_ - OffsetF(menuWidth, 0.0f);
    }

    const auto& secondHandleRect = info_->secondHandle.paintRect;
    if (info_->isSingleHandle) {
        auto menuSpacing = static_cast<float>(menuSpacingBetweenText);
        menuPosition = OffsetF((secondHandleRect.Left() + secondHandleRect.Right() - menuWidth) / 2.0f,
            static_cast<float>(secondHandleRect.Top() - menuSpacing - menuHeight));
    } else {
        auto menuSpacing = static_cast<float>(menuSpacingBetweenText + menuSpacingBetweenHandle);
        const auto& firstHandleRect = info_->firstHandle.paintRect;
        menuPosition = OffsetF((firstHandleRect.Left() + secondHandleRect.Left() - menuWidth) / 2.0f,
            static_cast<float>(firstHandleRect.Top() - menuSpacing - menuHeight));
    }

    auto overlayWidth = layoutWrapper->GetGeometryNode()->GetFrameSize().Width();

    // Adjust position of overlay.
    if (LessOrEqual(menuPosition.GetX(), 0.0)) {
        menuPosition.SetX(theme->GetDefaultMenuPositionX());
    } else if (GreatOrEqual(menuPosition.GetX() + menuWidth, overlayWidth)) {
        menuPosition.SetX(overlayWidth - menuWidth - theme->GetDefaultMenuPositionX());
    }
    if (LessNotEqual(menuPosition.GetY(), menuHeight)) {
        menuPosition.SetY(
            static_cast<float>(secondHandleRect.Bottom() + menuSpacingBetweenText + menuSpacingBetweenHandle));
    }
    defaultMenuEndOffset_ = menuPosition + OffsetF(menuWidth, 0.0f);
    return menuPosition;
}

OffsetF SelectOverlayLayoutAlgorithm::ComputeExtensionMenuPosition(LayoutWrapper* layoutWrapper, const OffsetF& offset)
{
    auto extensionItem = layoutWrapper->GetOrCreateChildByIndex(1);
    CHECK_NULL_RETURN(extensionItem, OffsetF());
    auto menu = extensionItem->GetHostNode();
    CHECK_NULL_RETURN(menu, OffsetF());
    auto menuPattern = menu->GetPattern<LinearLayoutPattern>();
    CHECK_NULL_RETURN(menuPattern, OffsetF());
    auto property = menuPattern->GetLayoutProperty<LinearLayoutProperty>();
    auto visibility = property->GetVisibilityValue();
    if (visibility != VisibleType::VISIBLE) {
        return OffsetF();
    }
    auto extensionWidth = extensionItem->GetGeometryNode()->GetMarginFrameSize().Width();
    return (defaultMenuEndOffset_ - OffsetF(extensionWidth, 0.0f));
}

} // namespace OHOS::Ace::NG