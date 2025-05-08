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

#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"

#include <algorithm>

#include "base/geometry/dimension.h"
#include "base/geometry/dimension_rect.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/point_t.h"
#include "base/geometry/offset.h"
#include "base/subwindow/subwindow_manager.h"
#include "base/utils/utils.h"
#include "core/components/menu/menu_component.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_node.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/property/safe_area_insets.h"
#include "core/pipeline/base/constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr uint32_t HIDDEN_HANDLE_TIMER_MS = 4000; // 4000ms
constexpr float EXPAND_HANDLE_PAINT_RECT = 3.0f;
constexpr float EXPAND_HANDLE_PAINT_RECT_HALF = 1.5f;
} // namespace

void SelectOverlayPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    layoutProperty->UpdateAlignment(Alignment::TOP_LEFT);

    UpdateHandleHotZone();
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    if (overlayMode_ == SelectOverlayMode::MENU_ONLY) {
        gesture->SetHitTestMode(HitTestMode::HTMTRANSPARENT_SELF);
        return;
    }
    gesture->SetHitTestMode(info_->hitTestMode);
    SetGestureEvent();
    if (info_->isSingleHandle) {
        StartHiddenHandleTask();
    }
}

void SelectOverlayPattern::SetGestureEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    clickEvent_ = MakeRefPtr<ClickEvent>([weak = WeakClaim(this)](GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleOnClick(info);
    });
    gesture->AddClickEvent(clickEvent_);
    auto panStart = [weak = WeakClaim(this)](GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandlePanStart(info);
    };
    auto panUpdate = [weak = WeakClaim(this)](GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandlePanMove(info);
    };
    auto panEnd = [weak = WeakClaim(this)](GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandlePanEnd(info);
    };
    auto panCancel = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandlePanCancel();
    };
    panEvent_ =
        MakeRefPtr<PanEvent>(std::move(panStart), std::move(panUpdate), std::move(panEnd), std::move(panCancel));
    PanDistanceMap distanceMap = { { SourceTool::UNKNOWN, DEFAULT_PAN_DISTANCE.ConvertToPx() },
        { SourceTool::PEN, DEFAULT_PEN_PAN_DISTANCE.ConvertToPx() } };
    gesture->AddPanEvent(panEvent_, { PanDirection::ALL }, 1, distanceMap);

    auto touchTask = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleTouchEvent(info);
        }
    };
    touchEvent_ = MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    gesture->AddTouchEvent(touchEvent_);
    InitMouseEvent();
}

void SelectOverlayPattern::InitMouseEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetOrCreateEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto inputHub = eventHub->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);
    auto mouseTask = [weak = WeakClaim(this)](MouseInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleMouseEvent(info);
    };
    auto mouseEvent = MakeRefPtr<InputEvent>(std::move(mouseTask));
    inputHub->AddOnMouseEvent(mouseEvent);
}

void SelectOverlayPattern::OnDetachFromFrameNode(FrameNode* /*frameNode*/)
{
    CHECK_NULL_VOID(info_);
    if (info_->onClose) {
        info_->onClose(closedByGlobalTouchEvent_);
        closedByGlobalTouchEvent_ = false;
    }
}

void SelectOverlayPattern::AddMenuResponseRegion(std::vector<DimensionRect>& responseRegion)
{
    auto layoutProps = GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(layoutProps);
    float safeAreaInsetsLeft = 0.0f;
    float safeAreaInsetsTop = 0.0f;
    auto&& safeAreaInsets = layoutProps->GetSafeAreaInsets();
    if (safeAreaInsets) {
        safeAreaInsetsLeft = static_cast<float>(safeAreaInsets->left_.end);
        safeAreaInsetsTop = static_cast<float>(safeAreaInsets->top_.end);
    }
    const auto& children = GetHost()->GetChildren();
    for (const auto& it : children) {
        auto child = DynamicCast<FrameNode>(it);
        if (child == nullptr) {
            continue;
        }
        auto frameRect = child->GetGeometryNode()->GetFrameRect();
        // rect is relative to window
        auto rect = Rect(frameRect.GetX() + safeAreaInsetsLeft, frameRect.GetY() + safeAreaInsetsTop, frameRect.Width(),
            frameRect.Height());

        DimensionRect region;
        region.SetSize({ Dimension(rect.GetSize().Width()), Dimension(rect.GetSize().Height()) });
        region.SetOffset(DimensionOffset(Offset(rect.GetOffset().GetX(), rect.GetOffset().GetY())));

        responseRegion.emplace_back(region);
    }
}

void SelectOverlayPattern::UpdateHandleHotZone()
{
    if (!CheckIfNeedHandle()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto firstHandle = info_->GetFirstHandlePaintRect();
    auto secondHandle = info_->GetSecondHandlePaintRect();

    auto theme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_VOID(theme);
    auto hotZone = theme->GetHandleHotZoneRadius().ConvertToPx();
    info_->firstHandle.isTouchable ? firstHandleRegion_.SetSize({ hotZone * 2, hotZone * 2 + firstHandle.Height() })
        : firstHandleRegion_.Reset();
    auto firstHandleOffsetX = (firstHandle.Left() + firstHandle.Right()) / 2;
    info_->secondHandle.isTouchable ? secondHandleRegion_.SetSize({ hotZone * 2, hotZone * 2 + secondHandle.Height() })
        : secondHandleRegion_.Reset();
    auto secondHandleOffsetX = (secondHandle.Left() + secondHandle.Right()) / 2;
    std::vector<DimensionRect> responseRegion;
    auto gestureEventHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureEventHub);
    if (info_->isSingleHandle) {
        if (info_->firstHandle.isShow && !info_->secondHandle.isShow) {
            // Use the first handle to make a single handle.
            auto firstHandleOffsetY = firstHandle.Top();
            firstHandleRegion_.SetOffset({ firstHandleOffsetX - hotZone, firstHandleOffsetY });
            DimensionRect firstHandleRegion;
            firstHandleRegion.SetSize(
                { Dimension(firstHandleRegion_.GetSize().Width()), Dimension(firstHandleRegion_.GetSize().Height()) });
            firstHandleRegion.SetOffset(
                DimensionOffset(Offset(firstHandleRegion_.GetOffset().GetX(), firstHandleRegion_.GetOffset().GetY())));
            responseRegion.emplace_back(firstHandleRegion);
            gestureEventHub->SetResponseRegion(responseRegion);
            secondHandleRegion_.Reset();
        } else {
            // Use the second handle to make a single handle.
            auto secondHandleOffsetY = secondHandle.Top();
            secondHandleRegion_.SetOffset({ secondHandleOffsetX - hotZone, secondHandleOffsetY });
            DimensionRect secondHandleRegion;
            secondHandleRegion.SetSize({ Dimension(secondHandleRegion_.GetSize().Width()),
                Dimension(secondHandleRegion_.GetSize().Height()) });
            secondHandleRegion.SetOffset(DimensionOffset(
                Offset(secondHandleRegion_.GetOffset().GetX(), secondHandleRegion_.GetOffset().GetY())));
            responseRegion.emplace_back(secondHandleRegion);
            gestureEventHub->SetResponseRegion(responseRegion);
            firstHandleRegion_.Reset();
        }
        return;
    }
    if (info_->handleReverse) {
        auto firstHandleOffsetY = firstHandle.Top();
        firstHandleRegion_.SetOffset({ firstHandleOffsetX - hotZone, firstHandleOffsetY });
        auto secondHandleOffsetY = secondHandle.Top();
        secondHandleRegion_.SetOffset({ secondHandleOffsetX - hotZone, secondHandleOffsetY - hotZone * 2 });
    } else {
        auto firstHandleOffsetY = firstHandle.Top();
        firstHandleRegion_.SetOffset({ firstHandleOffsetX - hotZone, firstHandleOffsetY - hotZone * 2 });
        auto secondHandleOffsetY = secondHandle.Top();
        secondHandleRegion_.SetOffset({ secondHandleOffsetX - hotZone, secondHandleOffsetY });
    }
    DimensionRect firstHandleRegion;
    firstHandleRegion.SetSize(
        { Dimension(firstHandleRegion_.GetSize().Width()), Dimension(firstHandleRegion_.GetSize().Height()) });
    firstHandleRegion.SetOffset(
        DimensionOffset(Offset(firstHandleRegion_.GetOffset().GetX(), firstHandleRegion_.GetOffset().GetY())));
    responseRegion.emplace_back(firstHandleRegion);
    DimensionRect secondHandleRegion;
    secondHandleRegion.SetSize(
        { Dimension(secondHandleRegion_.GetSize().Width()), Dimension(secondHandleRegion_.GetSize().Height()) });
    secondHandleRegion.SetOffset(
        DimensionOffset(Offset(secondHandleRegion_.GetOffset().GetX(), secondHandleRegion_.GetOffset().GetY())));
    responseRegion.emplace_back(secondHandleRegion);
    if (IsCustomMenu()) {
        AddMenuResponseRegion(responseRegion);
    }
    host->GetOrCreateGestureEventHub()->SetResponseRegion(responseRegion);
}

void SelectOverlayPattern::HandleOnClick(GestureEvent& info)
{
    if (info_->onClick) {
        info_->onClick(info, isFirstHandleTouchDown_);
    }
    if (!info_->isSingleHandle) {
        return;
    }
    auto host = DynamicCast<SelectOverlayNode>(GetHost());
    CHECK_NULL_VOID(host);
    if (!info_->menuInfo.menuDisable) {
        info_->menuInfo.menuIsShow = !info_->menuInfo.menuIsShow;
        host->UpdateToolBar(false);

        StopHiddenHandleTask();
        StartHiddenHandleTask();
        info_->menuInfo.singleHandleMenuIsShow = info_->menuInfo.menuIsShow;
    }
    if (info_->afterOnClick) {
        info_->afterOnClick(info, isFirstHandleTouchDown_);
    }
}

void SelectOverlayPattern::HandleTouchEvent(const TouchEventInfo& info)
{
    const auto& changedPoint = info.GetChangedTouches().front();
    if (changedPoint.GetTouchType() == TouchType::DOWN) {
        HandleTouchDownEvent(info);
    } else if (info_->onTouchDown && changedPoint.GetTouchType() == TouchType::UP) {
        info_->onTouchUp(info);
    } else if (info_->onTouchMove && changedPoint.GetTouchType() == TouchType::MOVE) {
        info_->onTouchMove(info);
    }
    if (IsCustomMenu()) {
        MenuWrapperPattern::OnTouchEvent(info);
    }
    if (changedPoint.GetTouchType() == TouchType::UP) {
        SwitchHandleToOverlayMode(false);
    }
}

void SelectOverlayPattern::HandleTouchDownEvent(const TouchEventInfo& info)
{
    if (info_->onTouchDown) {
        info_->onTouchDown(info);
    }
    auto touchOffset = info.GetChangedTouches().front().GetLocalLocation();
    PointF point = { touchOffset.GetX(), touchOffset.GetY() };
    if (firstHandleRegion_.IsInRegion(point)) {
        isFirstHandleTouchDown_ = true;
    } else if (secondHandleRegion_.IsInRegion(point)) {
        isSecondHandleTouchDown_ = true;
    }
}

void SelectOverlayPattern::HandlePanStart(GestureEvent& info)
{
    if (info.GetSourceDevice() == SourceType::MOUSE) {
        return;
    }
    if (!isFirstHandleTouchDown_ && !isSecondHandleTouchDown_) {
        LOGW("no handle is pressed");
        return;
    }
    if (IsFirstHandleMoveStart(info.GetLocalLocation())) {
        firstHandleDrag_ = true;
        secondHandleDrag_ = false;
        if (info_->onHandleMoveStart) {
            info_->onHandleMoveStart(info, firstHandleDrag_);
        }
    } else {
        firstHandleDrag_ = false;
        secondHandleDrag_ = true;
        if (info_->onHandleMoveStart) {
            info_->onHandleMoveStart(info, firstHandleDrag_);
        }
    }

    auto host = DynamicCast<SelectOverlayNode>(GetHost());
    CHECK_NULL_VOID(host);
    orignMenuIsShow_ = info_->menuInfo.menuIsShow;
    if (info_->menuInfo.menuIsShow) {
        info_->menuInfo.menuIsShow = false;
        host->UpdateToolBar(false, true);
    }
    if (info_->isSingleHandle) {
        StopHiddenHandleTask();
    }
    isFirstHandleTouchDown_ = false;
    isSecondHandleTouchDown_ = false;
    SwitchHandleToOverlayMode(true);
}

void SelectOverlayPattern::HandlePanMove(GestureEvent& info)
{
    auto host = DynamicCast<SelectOverlayNode>(GetHost());
    CHECK_NULL_VOID(host);
    const auto& offset = OffsetF(info.GetDelta().GetX(), info.GetDelta().GetY());
    if (firstHandleDrag_) {
        if (info_->onHandlePanMove) {
            info_->onHandlePanMove(info, true);
        }
        UpdateOffsetOnMove(firstHandleRegion_, info_->firstHandle, offset, true);
    } else if (secondHandleDrag_) {
        if (info_->onHandlePanMove) {
            info_->onHandlePanMove(info, false);
        }
        UpdateOffsetOnMove(secondHandleRegion_, info_->secondHandle, offset, false);
    } else {
        LOGW("the move point is not in drag area");
    }
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    if (host->IsLayoutDirtyMarked()) {
        context->AddDirtyLayoutNode(host);
    }
}

void SelectOverlayPattern::UpdateOffsetOnMove(
    RectF& region, SelectHandleInfo& handleInfo, const OffsetF& offset, bool isFirst)
{
    auto host = DynamicCast<SelectOverlayNode>(GetHost());
    CHECK_NULL_VOID(host);
    region += offset;
    handleInfo.paintRect += offset;
    handleInfo.localPaintRect += offset;
    auto isOverlayMode = info_->handleLevelMode == HandleLevelMode::OVERLAY;
    if (!isOverlayMode && info_->getDeltaHandleOffset) {
        handleInfo.localPaintRect += info_->getDeltaHandleOffset();
    }
    auto paintRect = isOverlayMode ? handleInfo.paintRect : handleInfo.localPaintRect;
    handleInfo.paintInfo = handleInfo.paintInfo + offset;
    if (isOverlayMode && handleInfo.isPaintHandleWithPoints && handleInfo.paintInfoConverter) {
        paintRect = handleInfo.paintInfoConverter(handleInfo.paintInfo);
    }
    CheckHandleReverse();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    if (info_->onHandleMove) {
        info_->onHandleMove(paintRect, isFirst);
    }
}

void SelectOverlayPattern::HandlePanEnd(GestureEvent& info)
{
    auto host = DynamicCast<SelectOverlayNode>(GetHost());
    CHECK_NULL_VOID(host);
    if (!info_->menuInfo.menuIsShow &&
        (!info_->menuCallback.showMenuOnMoveDone || info_->menuCallback.showMenuOnMoveDone())) {
        info_->menuInfo.menuIsShow = orignMenuIsShow_;
        host->UpdateToolBar(false);
    }
    if (firstHandleDrag_) {
        firstHandleDrag_ = false;
        if (info_->onHandlePanEnd) {
            info_->onHandlePanEnd(info, true);
        }
        if (info_->onHandleMoveDone) {
            auto paintRect = GetHandlePaintRect(info_->firstHandle);
            info_->onHandleMoveDone(paintRect, true);
        }
    } else if (secondHandleDrag_) {
        secondHandleDrag_ = false;
        if (info_->onHandlePanEnd) {
            info_->onHandlePanEnd(info, false);
        }
        if (info_->onHandleMoveDone) {
            auto paintRect = GetHandlePaintRect(info_->secondHandle);
            info_->onHandleMoveDone(paintRect, false);
        }
    }
    if (info_->isSingleHandle) {
        StartHiddenHandleTask();
    }
}

RectF SelectOverlayPattern::GetHandlePaintRect(const SelectHandleInfo& handleInfo)
{
    auto paintRect = handleInfo.paintRect;
    if (info_->handleLevelMode == HandleLevelMode::OVERLAY && handleInfo.isPaintHandleWithPoints &&
        handleInfo.paintInfoConverter) {
        paintRect = handleInfo.paintInfoConverter(handleInfo.paintInfo);
    }
    return paintRect;
}

void SelectOverlayPattern::HandlePanCancel()
{
    GestureEvent info;
    HandlePanEnd(info);
}

void SelectOverlayPattern::HandleMouseEvent(const MouseInfo& info)
{
    if (info_->onMouseEvent) {
        info_->onMouseEvent(info);
    }
}

void SelectOverlayPattern::CheckHandleReverse()
{
    bool handleReverseChanged = false;
    if (IsHandlesInSameLine()) {
        if (GreatNotEqual(info_->firstHandle.paintRect.Left(), info_->secondHandle.paintRect.Left())) {
            if (!info_->handleReverse) {
                info_->handleReverse = true;
                handleReverseChanged = true;
            }
        } else {
            if (info_->handleReverse) {
                info_->handleReverse = false;
                handleReverseChanged = true;
            }
        }
    } else if (GreatNotEqual(info_->firstHandle.paintRect.Top(), info_->secondHandle.paintRect.Top())) {
        if (!info_->handleReverse) {
            info_->handleReverse = true;
            handleReverseChanged = true;
        }
    } else {
        if (info_->handleReverse) {
            info_->handleReverse = false;
            handleReverseChanged = true;
        }
    }
    if (handleReverseChanged && info_->onHandleReverse) {
        info_->onHandleReverse(info_->handleReverse);
    }
}

bool SelectOverlayPattern::IsHandlesInSameLine()
{
    float lowerHandleTop = 0.0f;
    RectF heigherHandleRect;
    if (GreatNotEqual(info_->firstHandle.paintRect.Top(), info_->secondHandle.paintRect.Top())) {
        lowerHandleTop = info_->firstHandle.paintRect.Top() + 0.5f;
        heigherHandleRect = info_->secondHandle.paintRect;
    } else {
        lowerHandleTop = info_->secondHandle.paintRect.Top() + 0.5f;
        heigherHandleRect = info_->firstHandle.paintRect;
    }
    return GreatNotEqual(lowerHandleTop, heigherHandleRect.Top())
        && LessNotEqual(lowerHandleTop, heigherHandleRect.Bottom());
}

bool SelectOverlayPattern::IsFirstHandleMoveStart(const Offset& touchOffset)
{
    if (isFirstHandleTouchDown_ && isSecondHandleTouchDown_) {
        auto firstHandleCenter = Offset{ firstHandleRegion_.Center().GetX(), firstHandleRegion_.Center().GetY() };
        auto secondHandleCenter = Offset{ secondHandleRegion_.Center().GetX(), secondHandleRegion_.Center().GetY() };
        auto distanceToFirstHandle = (firstHandleCenter - touchOffset).GetDistance();
        auto distanceToSecondHandle = (secondHandleCenter - touchOffset).GetDistance();
        return GreatNotEqual(distanceToSecondHandle, distanceToFirstHandle);
    }
    return isFirstHandleTouchDown_;
}

void SelectOverlayPattern::SetHandleReverse(bool reverse)
{
    info_->handleReverse = reverse;
    UpdateHandleHotZone();
    auto host = DynamicCast<SelectOverlayNode>(GetHost());
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SelectOverlayPattern::SetSelectRegionVisible(bool isSelectRegionVisible)
{
    if (info_->isSelectRegionVisible != isSelectRegionVisible) {
        info_->isSelectRegionVisible = isSelectRegionVisible;
        auto host = DynamicCast<SelectOverlayNode>(GetHost());
        CHECK_NULL_VOID(host);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
}

void SelectOverlayPattern::UpdateFirstSelectHandleInfo(const SelectHandleInfo& info)
{
    if (info_->firstHandle == info) {
        return;
    }
    info_->firstHandle = info;
    CheckHandleReverse();
    UpdateHandleHotZone();
    auto host = DynamicCast<SelectOverlayNode>(GetHost());
    CHECK_NULL_VOID(host);
    if (info.needLayout) {
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    } else {
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void SelectOverlayPattern::UpdateSecondSelectHandleInfo(const SelectHandleInfo& info)
{
    if (info_->secondHandle == info) {
        return;
    }
    info_->secondHandle = info;
    CheckHandleReverse();
    UpdateHandleHotZone();
    auto host = DynamicCast<SelectOverlayNode>(GetHost());
    CHECK_NULL_VOID(host);
    if (info.needLayout) {
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    } else {
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void SelectOverlayPattern::UpdateFirstAndSecondHandleInfo(
    const SelectHandleInfo& firstInfo, const SelectHandleInfo& secondInfo)
{
    if (info_->firstHandle == firstInfo && info_->secondHandle == secondInfo) {
        return;
    }
    if (info_->firstHandle != firstInfo && !firstHandleDrag_) {
        info_->firstHandle = firstInfo;
    }
    if (info_->secondHandle != secondInfo && !secondHandleDrag_) {
        info_->secondHandle = secondInfo;
    }
    CheckHandleReverse();
    UpdateHandleHotZone();
    auto host = DynamicCast<SelectOverlayNode>(GetHost());
    CHECK_NULL_VOID(host);
    host->UpdateToolBar(false);
}

void SelectOverlayPattern::UpdateSelectMenuInfo(const SelectMenuInfo& info)
{
    auto host = DynamicCast<SelectOverlayNode>(GetHost());
    CHECK_NULL_VOID(host);
    auto itemChanged = info_->menuInfo.IsIconChanged(info);
    info_->menuInfo = info;
    host->UpdateToolBar(itemChanged);
}

void SelectOverlayPattern::UpdateShowArea(const RectF& area)
{
    if (info_->showArea != area) {
        info_->showArea = area;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
}

void SelectOverlayPattern::UpdateSelectMenuInfo(std::function<void(SelectMenuInfo& menuInfo)> updateAction)
{
    if (updateAction) {
        SelectMenuInfo shadowMenuInfo = info_->menuInfo;
        updateAction(shadowMenuInfo);
        UpdateSelectMenuInfo(shadowMenuInfo);
    }
}

void SelectOverlayPattern::UpdateAncestorViewPort(const std::optional<RectF>& ancestorViewPort) const
{
    if (info_->ancestorViewPort != ancestorViewPort) {
        info_->ancestorViewPort = ancestorViewPort;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
}

void SelectOverlayPattern::ShowOrHiddenMenu(bool isHidden, bool noAnimation)
{
    auto host = DynamicCast<SelectOverlayNode>(GetHost());
    CHECK_NULL_VOID(host);
    if (info_->menuInfo.menuIsShow && isHidden) {
        info_->menuInfo.menuIsShow = false;
        host->UpdateToolBar(false, noAnimation);
    } else if (!info_->menuInfo.menuIsShow && !isHidden &&
               (info_->firstHandle.isShow || info_->secondHandle.isShow || info_->isSelectRegionVisible ||
               (info_->isNewAvoid && !info_->isSingleHandle))) {
        info_->menuInfo.menuIsShow = true;
        host->UpdateToolBar(false, noAnimation);
    }
}

void SelectOverlayPattern::DisableMenu(bool isDisabled)
{
    info_->menuInfo.menuDisable = isDisabled;
    auto host = DynamicCast<SelectOverlayNode>(GetHost());
    CHECK_NULL_VOID(host);
    host->UpdateToolBar(false);
}

bool SelectOverlayPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    UpdateHandleHotZone();
    if (config.skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto selectOverlayLayoutAlgorithm =
        DynamicCast<SelectOverlayLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(selectOverlayLayoutAlgorithm, false);
    defaultMenuStartOffset_ = selectOverlayLayoutAlgorithm->GetDefaultMenuStartOffset();
    defaultMenuEndOffset_ = selectOverlayLayoutAlgorithm->GetDefaultMenuEndOffset();
    menuWidth_ = selectOverlayLayoutAlgorithm->GetMenuWidth();
    menuHeight_ = selectOverlayLayoutAlgorithm->GetMenuHeight();
    hasExtensionMenu_ =
        selectOverlayLayoutAlgorithm->GetHasExtensionMenu() && !selectOverlayLayoutAlgorithm->GetHideMoreOrBack();
    if (IsCustomMenu()) {
        MenuWrapperPattern::CheckAndShowAnimation();
    }
    SetHotAreas(dirty);
    return true;
}

void SelectOverlayPattern::SetHotAreas(const RefPtr<LayoutWrapper>& layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    CHECK_NULL_VOID(GetIsMenuShowInSubWindow());
    auto host = DynamicCast<SelectOverlayNode>(GetHost());
    CHECK_NULL_VOID(host);
    if (!IsMenuShow()) {
        SubwindowManager::GetInstance()->DeleteSelectOverlayHotAreas(GetContainerId(), host->GetId());
        return;
    }

    auto layoutProps = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProps);
    float safeAreaInsetsLeft = 0.0f;
    float safeAreaInsetsTop = 0.0f;
    auto&& safeAreaInsets = layoutProps->GetSafeAreaInsets();
    if (safeAreaInsets) {
        safeAreaInsetsLeft = static_cast<float>(safeAreaInsets->left_.end);
        safeAreaInsetsTop = static_cast<float>(safeAreaInsets->top_.end);
    }

    std::vector<Rect> rects;
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        CHECK_NULL_VOID(child);
        auto childGeometryNode = child->GetGeometryNode();
        CHECK_NULL_VOID(childGeometryNode);
        auto frameRect = childGeometryNode->GetFrameRect();
        auto rect = Rect(frameRect.GetX() + safeAreaInsetsLeft, frameRect.GetY() + safeAreaInsetsTop, frameRect.Width(),
            frameRect.Height());

        auto node = layoutWrapper->GetHostNode();
        rects.emplace_back(rect);
    }
    SubwindowManager::GetInstance()->SetSelectOverlayHotAreas(rects, host->GetId(), GetContainerId());
}

void SelectOverlayPattern::DeleteHotAreas()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    SubwindowManager::GetInstance()->DeleteSelectOverlayHotAreas(GetContainerId(), host->GetId());
}

bool SelectOverlayPattern::IsMenuShow()
{
    CHECK_NULL_RETURN(info_, false);
    return info_->menuInfo.menuIsShow;
}

bool SelectOverlayPattern::IsSingleHandleMenuShow()
{
    CHECK_NULL_RETURN(info_, false);
    return info_->menuInfo.singleHandleMenuIsShow;
}

bool SelectOverlayPattern::IsHandleShow()
{
    CHECK_NULL_RETURN(info_, false);
    return info_->firstHandle.isShow || info_->secondHandle.isShow;
}

bool SelectOverlayPattern::IsSingleHandle()
{
    CHECK_NULL_RETURN(info_, false);
    return info_->isSingleHandle;
}

void SelectOverlayPattern::StartHiddenHandleTask(bool isDelay)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto weak = WeakClaim(this);
    hiddenHandleTask_.Reset([weak] {
        auto client = weak.Upgrade();
        CHECK_NULL_VOID(client);
        client->HiddenHandle();
    });
    if (isDelay) {
        taskExecutor->PostDelayedTask(hiddenHandleTask_, TaskExecutor::TaskType::UI, HIDDEN_HANDLE_TIMER_MS,
            "ArkUISelectOverlayHiddenHandle");
    } else {
        taskExecutor->PostTask(hiddenHandleTask_, TaskExecutor::TaskType::UI, "ArkUISelectOverlayHiddenHandle",
                               PriorityType::VIP);
    }
}

void SelectOverlayPattern::HiddenHandle()
{
    hiddenHandleTask_.Cancel();
    isHiddenHandle_ = true;
    if (info_->onHandleIsHidden) {
        info_->onHandleIsHidden();
    }
    auto host = DynamicCast<SelectOverlayNode>(GetHost());
    CHECK_NULL_VOID(host);
    if (overlayMode_ == SelectOverlayMode::HANDLE_ONLY) {
        firstHandleRegion_.Reset();
        secondHandleRegion_.Reset();
        std::vector<DimensionRect> responseRegion;
        host->GetOrCreateGestureEventHub()->SetResponseRegion(responseRegion);
        host->GetOrCreateGestureEventHub()->SetHitTestMode(HitTestMode::HTMNONE);
    }
    host->GetOrCreateGestureEventHub()->RemoveClickEvent(clickEvent_);
    host->GetOrCreateGestureEventHub()->RemovePanEvent(panEvent_);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SelectOverlayPattern::StopHiddenHandleTask()
{
    hiddenHandleTask_.Cancel();
}

void SelectOverlayPattern::UpdateSelectArea(const RectF& selectArea)
{
    info_->selectArea = selectArea;
}

void SelectOverlayPattern::SetIsNewAvoid(bool isNewAvoid)
{
    info_->isNewAvoid = isNewAvoid;
}

void SelectOverlayPattern::SetSelectMenuHeight()
{
    auto host = DynamicCast<SelectOverlayNode>(GetHost());
    CHECK_NULL_VOID(host);
    auto selectMenu = AceType::DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_VOID(selectMenu);
    auto geometryNode = selectMenu->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    selectMenuHeight_ = geometryNode->GetFrameSize().Height();
}

bool SelectOverlayPattern::CheckIfNeedMenu()
{
    return (overlayMode_ == SelectOverlayMode::ALL || overlayMode_ == SelectOverlayMode::MENU_ONLY);
}

bool SelectOverlayPattern::CheckIfNeedHandle()
{
    return (overlayMode_ == SelectOverlayMode::ALL || overlayMode_ == SelectOverlayMode::HANDLE_ONLY);
}

float SelectOverlayPattern::GetHandleDiameter()
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, 0.0f);
    auto textOverlayTheme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_RETURN(textOverlayTheme, 0.0f);
    return textOverlayTheme->GetHandleDiameter().ConvertToPx();
}

void SelectOverlayPattern::SetContentModifierBounds(const RefPtr<SelectOverlayContentModifier>& modifier)
{
    CHECK_NULL_VOID(modifier);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameRect = geometryNode->GetFrameRect();
    auto handleDiameter = GetHandleDiameter();
    RectF boundsRect;
    boundsRect.SetLeft(frameRect.Left() - handleDiameter * EXPAND_HANDLE_PAINT_RECT_HALF);
    boundsRect.SetTop(frameRect.Top() - handleDiameter * EXPAND_HANDLE_PAINT_RECT_HALF);
    boundsRect.SetWidth(frameRect.Width() + handleDiameter * EXPAND_HANDLE_PAINT_RECT);
    boundsRect.SetHeight(frameRect.Height() + handleDiameter * EXPAND_HANDLE_PAINT_RECT);
    modifier->SetBoundsRect(boundsRect);
}

void SelectOverlayPattern::OnDpiConfigurationUpdate()
{
    auto host = DynamicCast<SelectOverlayNode>(GetHost());
    CHECK_NULL_VOID(host);
    host->UpdateToolBarFromMainWindow(true, true);
}

void SelectOverlayPattern::SwitchHandleToOverlayMode(bool afterRender)
{
    if (!info_->enableHandleLevel || info_->handleLevelMode != HandleLevelMode::EMBED) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto overlayNode = DynamicCast<SelectOverlayNode>(host);
    CHECK_NULL_VOID(overlayNode);
    auto switchTask = [weak = WeakClaim(AceType::RawPtr(overlayNode))]() {
        auto overlayNode = weak.Upgrade();
        CHECK_NULL_VOID(overlayNode);
        if (overlayNode) {
            overlayNode->SwitchToOverlayMode();
        }
    };
    if (afterRender) {
        auto pipeline = host->GetContext();
        CHECK_NULL_VOID(pipeline);
        pipeline->AddAfterRenderTask(switchTask);
    } else {
        switchTask();
    }
}

void SelectOverlayPattern::OnColorConfigurationUpdate()
{
    auto host = DynamicCast<SelectOverlayNode>(GetHost());
    CHECK_NULL_VOID(host);
    host->UpdateSelectMenuBg();
    host->UpdateToolBarFromMainWindow(true, true);
}

void SelectOverlayPattern::OnLanguageConfigurationUpdate()
{
    auto host = DynamicCast<SelectOverlayNode>(GetHost());
    CHECK_NULL_VOID(host);
    host->UpdateToolBarFromMainWindow(true, true);
}
} // namespace OHOS::Ace::NG
