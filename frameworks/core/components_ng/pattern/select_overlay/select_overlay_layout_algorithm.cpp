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
#include "base/utils/utils.h"
#include "core/components/text_overlay/text_overlay_theme.h"
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

    // Calculate the spacing with text and handle, menu is fixed up the handle and text.
    double menuSpacingBetweenText = theme->GetMenuSpacingWithText().ConvertToPx();
    double menuSpacingBetweenHandle = theme->GetHandleDiameter().ConvertToPx();

    auto menuWidth = menuItem->GetGeometryNode()->GetMarginFrameSize().Width();
    auto menuHeight = menuItem->GetGeometryNode()->GetMarginFrameSize().Height();
    OffsetF menuPosition;
    const auto& firstHandleRect = info_->firstHandle.paintRect;
    if (info_->isSingleHandle) {
        double menuSpacing = menuSpacingBetweenText;
        menuPosition = OffsetF((firstHandleRect.Left() + firstHandleRect.Right() - menuWidth) / 2.0f,
            static_cast<float>(firstHandleRect.Top() - menuSpacing - menuHeight));
    } else {
        double menuSpacing = menuSpacingBetweenText + menuSpacingBetweenHandle;
        const auto& secondHandleRect = info_->secondHandle.paintRect;
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
    if (LessNotEqual(menuPosition.GetY(), 0.0)) {
        menuPosition.SetY(
            static_cast<float>(firstHandleRect.Bottom() + menuSpacingBetweenText + menuSpacingBetweenHandle));
    }
    return menuPosition;
}

} // namespace OHOS::Ace::NG