/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/select_content_overlay/select_content_overlay_pattern.h"

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
void SelectContentOverlayPattern::UpdateMenuIsShow(bool menuIsShow, bool noAnimation)
{
    if (info_->menuInfo.menuIsShow == menuIsShow) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(host);
    CHECK_NULL_VOID(selectOverlayNode);
    info_->menuInfo.menuIsShow = menuIsShow;
    selectOverlayNode->UpdateToolBar(false, noAnimation);
}

void SelectContentOverlayPattern::UpdateMenuInfo(const SelectMenuInfo& info)
{
    auto host = DynamicCast<SelectOverlayNode>(GetHost());
    CHECK_NULL_VOID(host);
    auto itemChanged = info_->menuInfo.IsIconChanged(info);
    info_->menuInfo = info;
    host->UpdateToolBar(itemChanged, true);
}

void SelectContentOverlayPattern::UpdateIsShowHandleLine(bool isHandleLineShow)
{
    if (info_->isHandleLineShow == isHandleLineShow) {
        return;
    }
    auto host = DynamicCast<SelectOverlayNode>(GetHost());
    CHECK_NULL_VOID(host);
    info_->isHandleLineShow = isHandleLineShow;
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SelectContentOverlayPattern::UpdateIsSingleHandle(bool isSingleHandle)
{
    if (info_->isSingleHandle == isSingleHandle) {
        return;
    }
    auto host = DynamicCast<SelectOverlayNode>(GetHost());
    CHECK_NULL_VOID(host);
    info_->isSingleHandle = isSingleHandle;
    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
}

void SelectContentOverlayPattern::RestartHiddenHandleTask(bool isDelay)
{
    CancelHiddenHandleTask();
    StartHiddenHandleTask(isDelay);
}

void SelectContentOverlayPattern::CancelHiddenHandleTask()
{
    hiddenHandleTask_.Cancel();
    isHiddenHandle_ = false;
    auto host = DynamicCast<SelectOverlayNode>(GetHost());
    CHECK_NULL_VOID(host);
    UpdateHandleHotZone();
    auto gestureEventHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureEventHub);
    gestureEventHub->SetHitTestMode(info_->hitTestMode);
    gestureEventHub->AddClickEvent(clickEvent_);
    gestureEventHub->AddPanEvent(panEvent_, { PanDirection::ALL }, 1, DEFAULT_PAN_DISTANCE);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

SelectMenuInfo SelectContentOverlayPattern::GetSelectMenuInfo()
{
    return info_->menuInfo;
}

void SelectContentOverlayPattern::CheckHandleReverse()
{
    CHECK_NULL_VOID(!info_->isSingleHandle);
    auto firstRect = GetHandlePaintRect(info_->firstHandle);
    auto secondRect = GetHandlePaintRect(info_->secondHandle);
    auto isReversed = info_->handleReverse;
    if (info_->checkHandleReverse) {
        isReversed = info_->checkHandleReverse(firstRect, secondRect);
    } else if (IsHandleInSameLine(firstRect, secondRect)) {
        isReversed = GreatNotEqual(firstRect.Left(), secondRect.Left());
    } else {
        isReversed = GreatNotEqual(firstRect.Top(), secondRect.Top());
    }
    if (isReversed != info_->handleReverse) {
        info_->handleReverse = isReversed;
        if (info_->onHandleReverse) {
            info_->onHandleReverse(info_->handleReverse);
        }
    }
}

bool SelectContentOverlayPattern::IsHandleInSameLine(const RectF& first, const RectF& second)
{
    float lowerHandleTop = 0.0f;
    RectF heigherHandleRect;
    if (GreatNotEqual(first.Top(), second.Top())) {
        lowerHandleTop = first.Top() + 0.5f; // 0.5f : for round
        heigherHandleRect = second;
    } else {
        lowerHandleTop = second.Top() + 0.5f; // 0.5f : for round
        heigherHandleRect = first;
    }
    return GreatNotEqual(lowerHandleTop, heigherHandleRect.Top()) &&
           LessNotEqual(lowerHandleTop, heigherHandleRect.Bottom());
}

void SelectContentOverlayPattern::UpdateHandleHotZone()
{
    if (!CheckIfNeedHandle()) {
        return;
    }
    if (info_->handleLevelMode == HandleLevelMode::OVERLAY &&
        (info_->firstHandle.isPaintHandleWithPoints || info_->secondHandle.isPaintHandleWithPoints)) {
        UpdateHandleHotZoneWithPoint();
    } else {
        SelectOverlayPattern::UpdateHandleHotZone();
    }
}

bool SelectContentOverlayPattern::UpdateHandleHotZoneWithPoint()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto theme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_RETURN(theme, false);
    auto hotZone = theme->GetHandleHotZoneRadius().ConvertToPx();
    auto radius =
        (theme->GetHandleDiameter().ConvertToPx() + theme->GetHandleDiameterStrokeWidth().ConvertToPx()) / 2.0f;
    firstHandleRegion_.SetSize({ hotZone * 2, hotZone * 2 });
    secondHandleRegion_.SetSize({ hotZone * 2, hotZone * 2 });
    if (info_->isSingleHandle) {
        if (!info_->firstHandle.isShow && info_->secondHandle.isShow) {
            // Use the second handle to make a single handle.
            auto centerOffset = GetHandleHotZoneOffset(false, radius, false);
            auto offsetX = centerOffset.GetX() - hotZone;
            auto offsetY = centerOffset.GetY() - hotZone;
            UpdateHandleHotRegion(secondHandleRegion_, { offsetX, offsetY });
            firstHandleRegion_.Reset();
        } else {
            // Use the first handle to make a single handle.
            auto centerOffset = GetHandleHotZoneOffset(true, radius, false);
            auto offsetX = centerOffset.GetX() - hotZone;
            auto offsetY = centerOffset.GetY() - hotZone;
            UpdateHandleHotRegion(firstHandleRegion_, { offsetX, offsetY });
            secondHandleRegion_.Reset();
        }
        return true;
    }
    auto firstCenter = GetHandleHotZoneOffset(true, radius, !info_->handleReverse);
    auto secondCenter = GetHandleHotZoneOffset(false, radius, info_->handleReverse);
    firstHandleRegion_.SetOffset({ firstCenter.GetX() - hotZone, firstCenter.GetY() - hotZone });
    secondHandleRegion_.SetOffset({ secondCenter.GetX() - hotZone, secondCenter.GetY() - hotZone });

    std::vector<DimensionRect> responseRegion;
    DimensionRect firstRegion = ConvertToHotRect(firstHandleRegion_);
    responseRegion.emplace_back(firstRegion);
    DimensionRect secondRegion = ConvertToHotRect(secondHandleRegion_);
    responseRegion.emplace_back(secondRegion);
    if (IsCustomMenu()) {
        AddMenuResponseRegion(responseRegion);
    }
    auto gestureEventHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(gestureEventHub, false);
    gestureEventHub->SetResponseRegion(responseRegion);
    return true;
}

void SelectContentOverlayPattern::UpdateHandleHotRegion(RectF& hotRegion, const OffsetF& offset)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    hotRegion.SetOffset(offset);
    DimensionRect newRegion = ConvertToHotRect(hotRegion);
    std::vector<DimensionRect> responseRegion;
    responseRegion.emplace_back(newRegion);
    auto gestureEventHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureEventHub);
    gestureEventHub->SetResponseRegion(responseRegion);
}

DimensionRect SelectContentOverlayPattern::ConvertToHotRect(const RectF& rect)
{
    DimensionRect newRegion;
    newRegion.SetSize({ Dimension(rect.GetSize().Width()), Dimension(rect.GetSize().Height()) });
    newRegion.SetOffset(DimensionOffset(Offset(rect.GetOffset().GetX(), rect.GetOffset().GetY())));
    return newRegion;
}

OffsetF SelectContentOverlayPattern::GetHandleHotZoneOffset(bool isFirst, float raidus, bool handleOnTop)
{
    auto startPoint = isFirst ? info_->firstHandle.paintInfo.startPoint : info_->secondHandle.paintInfo.startPoint;
    auto endPoint = isFirst ? info_->firstHandle.paintInfo.endPoint : info_->secondHandle.paintInfo.endPoint;
    return SelectOverlayContentModifier::CalculateCenterPoint(startPoint, endPoint, raidus, handleOnTop);
}

void SelectContentOverlayPattern::UpdateViewPort(const std::optional<RectF>& viewPort)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    info_->ancestorViewPort = viewPort;
    auto extraFlag = PROPERTY_UPDATE_LAYOUT;
    if (GetMode() == SelectOverlayMode::HANDLE_ONLY) {
        extraFlag |= PROPERTY_UPDATE_RENDER;
    }
    host->MarkDirtyNode(extraFlag);
}

void SelectContentOverlayPattern::UpdateSelectArea(const RectF& selectArea)
{
    SelectOverlayPattern::UpdateSelectArea(selectArea);
    if (info_->menuInfo.menuIsShow && selectArea.IsEmpty()) {
        UpdateMenuIsShow(false);
    }
}

void SelectContentOverlayPattern::SetHandleCircleIsShow(bool isFirst, bool isShow)
{
    auto& handleInfo = isFirst ? info_->firstHandle : info_->secondHandle;
    if (handleInfo.isCircleShow != isShow) {
        handleInfo.isCircleShow = isShow;
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void SelectContentOverlayPattern::SetIsHandleLineShow(bool isShow)
{
    if (info_->isHandleLineShow != isShow) {
        info_->isHandleLineShow = isShow;
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}
} // namespace OHOS::Ace::NG
