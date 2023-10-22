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

#include "core/components_ng/pattern/patternlock/patternlock_pattern.h"

#include "core/components/test/unittest/image/image_test_utils.h"
#include "core/components_ng/pattern/patternlock/patternlock_paint_property.h"
#include "core/components_ng/pattern/stage/page_event_hub.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_v2/pattern_lock/pattern_lock_component.h"
#include "core/event/touch_event.h"
#include "core/pipeline/base/constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t PATTERN_LOCK_COL_COUNT = 3;
constexpr int32_t RADIUS_TO_DIAMETER = 2;
constexpr int32_t RADIUS_COUNT = 6;
} // namespace

void PatternLockPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetLayoutProperty()->UpdateAlignment(Alignment::CENTER);
}

void PatternLockPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto gestureHub = host->GetOrCreateGestureEventHub();
    InitTouchEvent(gestureHub, touchDownListener_);
    InitPanEvent(gestureHub);
    InitPatternLockController();
    InitFocusEvent();
    InitMouseEvent();
}

void PatternLockPattern::InitTouchEvent(RefPtr<GestureEventHub>& gestureHub, RefPtr<TouchEventImpl>& touchDownListener)
{
    if (touchDownListener) {
        return;
    }
    auto touchDownTask = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleTouchEvent(info);
    };
    touchDownListener = MakeRefPtr<TouchEventImpl>(std::move(touchDownTask));
    gestureHub->AddTouchEvent(touchDownListener);
}

void PatternLockPattern::SetChallengeResult(V2::PatternLockChallengeResult challengeResult)
{
    if (!isMoveEventValid_) {
        CHECK_NULL_VOID(patternLockModifier_);
        std::optional<NG::PatternLockChallengeResult> ngChallengeResult;
        if (challengeResult == V2::PatternLockChallengeResult::CORRECT) {
            ngChallengeResult = NG::PatternLockChallengeResult::CORRECT;
        } else if (challengeResult == V2::PatternLockChallengeResult::WRONG) {
            ngChallengeResult = NG::PatternLockChallengeResult::WRONG;
        }
        patternLockModifier_->SetChallengeResult(ngChallengeResult);
    }
}

void PatternLockPattern::InitPatternLockController()
{
    patternLockController_->SetResetImpl([weak = WeakClaim(this)]() {
        auto patternLock = weak.Upgrade();
        CHECK_NULL_VOID(patternLock);
        patternLock->HandleReset();
    });
    patternLockController_->SetChallengeResultImpl(
        [weak = WeakClaim(this)](V2::PatternLockChallengeResult challengeResult) {
            auto patternLock = weak.Upgrade();
            CHECK_NULL_VOID(patternLock);
            patternLock->SetChallengeResult(challengeResult);
        });
}

void PatternLockPattern::HandleTouchEvent(const TouchEventInfo& info)
{
    auto touchType = info.GetTouches().front().GetTouchType();
    if (touchType == TouchType::DOWN) {
        OnTouchDown(info);
    } else if (touchType == TouchType::UP) {
        OnTouchUp();
    }
}

bool PatternLockPattern::CheckInHotSpot(const OffsetF& offset, int32_t x, int32_t y)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto patternLockPaintProperty = host->GetPaintProperty<PatternLockPaintProperty>();
    float sideLength = host->GetGeometryNode()->GetContentSize().Width();
    OffsetF contentOffset = host->GetGeometryNode()->GetContentOffset();
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    auto patternLockTheme = pipelineContext->GetTheme<V2::PatternLockTheme>();
    CHECK_NULL_RETURN(patternLockTheme, false);
    circleRadius_ = patternLockTheme->GetCircleRadius();
    if (patternLockPaintProperty->HasCircleRadius()) {
        circleRadius_ = patternLockPaintProperty->GetCircleRadiusValue();
    }
    auto backgroundRadiusScale = patternLockTheme->GetBackgroundRadiusScale();
    if (NearZero(backgroundRadiusScale)) {
        return false;
    }
    auto activeCircleRadiusScale = patternLockTheme->GetActiveCircleRadiusScale();
    auto handleCircleRadius = std::min(static_cast<float>(circleRadius_.ConvertToPxWithSize(sideLength)),
        sideLength / backgroundRadiusScale / RADIUS_COUNT);
    auto hotSpotCircleRadius = patternLockTheme->GetHotSpotCircleRadius();
    handleCircleRadius = std::max(handleCircleRadius * activeCircleRadiusScale,
        std::min(
            static_cast<float>(hotSpotCircleRadius.ConvertToPx()) / RADIUS_TO_DIAMETER, sideLength / RADIUS_COUNT));
    const int32_t scale = RADIUS_TO_DIAMETER;
    float offsetX = sideLength / PATTERN_LOCK_COL_COUNT / scale * (scale * x - 1);
    float offsetY = sideLength / PATTERN_LOCK_COL_COUNT / scale * (scale * y - 1);
    offsetX += contentOffset.GetX();
    offsetY += contentOffset.GetY();
    OffsetF centerOffset;
    centerOffset.SetX(offsetX);
    centerOffset.SetY(offsetY);
    auto X = (offset - centerOffset).GetX();
    auto Y = (offset - centerOffset).GetY();
    float distance = std::sqrt((X * X) + (Y * Y));
    return LessOrEqual(distance, handleCircleRadius);
}

bool PatternLockPattern::AddChoosePoint(const OffsetF& offset, int32_t x, int32_t y)
{
    if (CheckInHotSpot(offset, x, y)) {
        if (!CheckChoosePoint(x, y)) {
            AddPassPoint(x, y);
            choosePoint_.emplace_back(x, y);
            StartModifierConnectedAnimate(x, y);
            UpdateDotConnectEvent();
        }
        return true;
    }
    return false;
}

bool PatternLockPattern::CheckChoosePoint(int32_t x, int32_t y) const
{
    for (auto it : choosePoint_) {
        if (it.GetColumn() == x && it.GetRow() == y) {
            return true;
        }
    }
    return false;
}

void PatternLockPattern::UpdateDotConnectEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<PatternLockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->UpdateDotConnectEvent(choosePoint_.back().GetCode());
}

void PatternLockPattern::AddPassPointToChoosePoint(
    int32_t lastCode, int32_t nowCode, std::vector<PatternLockCell> passPointVec)
{
    passPointCount_ = static_cast<int32_t>(passPointVec.size());
    if (nowCode > lastCode) {
        choosePoint_.emplace_back(passPointVec.front());
        UpdateDotConnectEvent();
        StartModifierAddPassPointAnimate(passPointVec.front().GetColumn(), passPointVec.front().GetRow());
        if (passPointCount_ > 1) {
            choosePoint_.emplace_back(passPointVec.back());
            UpdateDotConnectEvent();
            StartModifierAddPassPointAnimate(passPointVec.back().GetColumn(), passPointVec.back().GetRow());
        }
    } else {
        choosePoint_.emplace_back(passPointVec.back());
        UpdateDotConnectEvent();
        StartModifierAddPassPointAnimate(passPointVec.back().GetColumn(), passPointVec.back().GetRow());
        if (passPointCount_ > 1) {
            choosePoint_.emplace_back(passPointVec.front());
            UpdateDotConnectEvent();
            StartModifierAddPassPointAnimate(passPointVec.front().GetColumn(), passPointVec.front().GetRow());
        }
    }
}

void PatternLockPattern::AddPassPoint(int32_t x, int32_t y)
{
    if (choosePoint_.empty()) {
        return;
    }
    passPointCount_ = 0;
    PatternLockCell lastCell = choosePoint_.back();
    int32_t lastX = lastCell.GetColumn();
    int32_t lastY = lastCell.GetRow();
    int32_t lastCode = lastCell.GetCode();
    int32_t nowCode = PATTERN_LOCK_COL_COUNT * (y - 1) + (x - 1);
    std::vector<PatternLockCell> passPointVec;
    for (int32_t i = 1; i <= PATTERN_LOCK_COL_COUNT; i++) {
        for (int32_t j = 1; j <= PATTERN_LOCK_COL_COUNT; j++) {
            PatternLockCell passPoint = PatternLockCell(i, j);
            if ((passPoint.GetCode() >= nowCode && passPoint.GetCode() >= lastCode) ||
                (passPoint.GetCode() <= nowCode && passPoint.GetCode() <= lastCode)) {
                continue;
            }
            if ((j != y) && (j != lastY) &&
                (NearEqual(static_cast<float>(lastX - i) / (lastY - j), static_cast<float>(i - x) / (j - y)) &&
                    !CheckChoosePoint(i, j))) {
                passPointVec.emplace_back(passPoint);
            }
            if ((j == lastY) && (j == y) && !CheckChoosePoint(i, j)) {
                passPointVec.emplace_back(passPoint);
            }
        }
    }
    size_t passPointLength = passPointVec.size();
    if (passPointLength == 0) {
        return;
    }
    AddPassPointToChoosePoint(lastCode, nowCode, passPointVec);
}

void PatternLockPattern::HandleReset()
{
    isMoveEventValid_ = false;
    choosePoint_.clear();
    cellCenter_.Reset();
    if (patternLockModifier_) {
        patternLockModifier_->Reset();
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

bool PatternLockPattern::CheckAutoReset() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto patternLockPaintProperty = host->GetPaintProperty<PatternLockPaintProperty>();
    if (patternLockPaintProperty->HasAutoReset()) {
        autoReset_ = patternLockPaintProperty->GetAutoResetValue();
    }
    return !(!autoReset_ && !choosePoint_.empty() && !isMoveEventValid_);
}

void PatternLockPattern::OnTouchDown(const TouchEventInfo& info)
{
    const auto& locationInfo = info.GetTouches().front();
    float moveDeltaX = locationInfo.GetLocalLocation().GetX();
    float moveDeltaY = locationInfo.GetLocalLocation().GetY();
    OffsetF touchPoint;
    touchPoint.SetX(moveDeltaX);
    touchPoint.SetY(moveDeltaY);

    if (!CheckAutoReset()) {
        return;
    }
    HandleReset();
    cellCenter_ = touchPoint;
    bool isAdd = false;
    for (int32_t i = 0; i < PATTERN_LOCK_COL_COUNT && !isAdd; i++) {
        for (int32_t j = 0; j < PATTERN_LOCK_COL_COUNT && !isAdd; j++) {
            isAdd = AddChoosePoint(touchPoint, i + 1, j + 1);
        }
    }

    if (patternLockModifier_) {
        patternLockModifier_->SetIsTouchDown(true);
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    isMoveEventValid_ = true;
}

void PatternLockPattern::HandleGestureUpdate(const GestureEvent& info)
{
    if (info.GetInputEventType() == InputEventType::AXIS) {
        return;
    }
    auto moveDeltaX = static_cast<float>(info.GetLocalLocation().GetX());
    auto moveDeltaY = static_cast<float>(info.GetLocalLocation().GetY());
    OffsetF touchPoint;
    touchPoint.SetX(moveDeltaX);
    touchPoint.SetY(moveDeltaY);

    if (!isMoveEventValid_) {
        return;
    }
    cellCenter_ = touchPoint;
    bool isAdd = false;
    for (int32_t i = 0; i < PATTERN_LOCK_COL_COUNT && !isAdd; i++) {
        for (int32_t j = 0; j < PATTERN_LOCK_COL_COUNT && !isAdd; j++) {
            isAdd = AddChoosePoint(touchPoint, i + 1, j + 1);
        }
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void PatternLockPattern::InitPanEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& /* info */) {};

    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleGestureUpdate(info);
    };

    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& /* info */) {};

    auto actionCancelTask = [weak = WeakClaim(this)]() {};
    if (panEvent_) {
        gestureHub->RemovePanEvent(panEvent_);
    }

    PanDirection panDirection;
    panDirection.type = PanDirection::ALL;
    panEvent_ = MakeRefPtr<PanEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
    gestureHub->AddPanEvent(panEvent_, panDirection, 1, DEFAULT_PAN_DISTANCE);
}

void PatternLockPattern::AddPointEnd()
{
    if (!CheckAutoReset()) {
        return;
    }
    isMoveEventValid_ = false;
    std::vector<int> chooseCellVec;
    for (auto& it : choosePoint_) {
        chooseCellVec.emplace_back(it.GetCode());
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<PatternLockEventHub>();
    CHECK_NULL_VOID(eventHub);

    auto patternCompleteEvent = V2::PatternCompleteEvent(chooseCellVec);
    eventHub->UpdateCompleteEvent(&patternCompleteEvent);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void PatternLockPattern::OnTouchUp()
{
    CHECK_NULL_VOID(patternLockModifier_);
    patternLockModifier_->SetIsTouchDown(false);
    StartModifierCanceledAnimate();
    AddPointEnd();
}

void PatternLockPattern::InitFocusEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);

    auto focusTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleFocusEvent();
    };
    focusHub->SetOnFocusInternal(focusTask);
    auto blurTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleBlurEvent();
    };
    focusHub->SetOnBlurInternal(blurTask);
    auto keyTask = [weak = WeakClaim(this)](const KeyEvent& keyEvent) -> bool {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        return pattern->OnKeyEvent(keyEvent);
    };
    focusHub->SetOnKeyEventInternal(keyTask);
    auto getInnerPaintRectCallback = [wp = WeakClaim(this)](RoundRect& paintRect) {
        auto pattern = wp.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->GetInnerFocusPaintRect(paintRect);
    };
    focusHub->SetInnerFocusPaintRectCallback(getInnerPaintRectCallback);
}

void PatternLockPattern::HandleFocusEvent()
{
    HandleReset();
    currentPoint_ = { 1, 1 };
    isMoveEventValid_ = true;
}

void PatternLockPattern::HandleBlurEvent()
{
    isMoveEventValid_ = false;
}

void PatternLockPattern::GetInnerFocusPaintRect(RoundRect& paintRect)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto patternLockTheme = pipelineContext->GetTheme<V2::PatternLockTheme>();
    CHECK_NULL_VOID(patternLockTheme);
    auto patternLockPaintProperty = host->GetPaintProperty<PatternLockPaintProperty>();
    CHECK_NULL_VOID(patternLockPaintProperty);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    OffsetF contentOffset = geometryNode->GetContentOffset();
    float sideLength = geometryNode->GetContentSize().Width();
    float offset = sideLength / PATTERN_LOCK_COL_COUNT;
    float circleRadius = patternLockPaintProperty->GetCircleRadius()
                             .value_or(patternLockTheme->GetCircleRadius())
                             .ConvertToPxWithSize(sideLength);
    auto backgroundRadiusScale = patternLockTheme->GetBackgroundRadiusScale();
    auto focusPaddingRadius = patternLockTheme->GetFocusPaddingRadius();
    auto focusPaintWidth = patternLockTheme->GetFocusPaintWidth();
    float foucusCircleRadius = std::min(circleRadius * backgroundRadiusScale, offset / RADIUS_TO_DIAMETER) +
                               (focusPaddingRadius).ConvertToPx() + focusPaintWidth.ConvertToPx() / RADIUS_TO_DIAMETER;
    float outRadius = offset / RADIUS_TO_DIAMETER - foucusCircleRadius;
    float offsetX = contentOffset.GetX() + (currentPoint_.first - 1) * offset + outRadius;
    float offsetY = contentOffset.GetY() + (currentPoint_.second - 1) * offset + outRadius;

    paintRect.SetRect(
        { offsetX, offsetY, foucusCircleRadius * RADIUS_TO_DIAMETER, foucusCircleRadius * RADIUS_TO_DIAMETER });
    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS, foucusCircleRadius, foucusCircleRadius);
    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS, foucusCircleRadius, foucusCircleRadius);
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS, foucusCircleRadius, foucusCircleRadius);
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS, foucusCircleRadius, foucusCircleRadius);
}

void PatternLockPattern::OnFocusClick()
{
    if (!CheckAutoReset()) {
        return;
    }
    if (!isMoveEventValid_) {
        HandleReset();
    }
    if (CheckChoosePoint(currentPoint_.first, currentPoint_.second)) {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    OffsetF touchPoint;
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    OffsetF contentOffset = geometryNode->GetContentOffset();
    float sideLength = geometryNode->GetContentSize().Width();
    float offset = sideLength / PATTERN_LOCK_COL_COUNT / RADIUS_TO_DIAMETER;
    float offsetX = contentOffset.GetX() + offset * (currentPoint_.first * 2 - 1);
    float offsetY = contentOffset.GetY() + offset * (currentPoint_.second * 2 - 1);
    touchPoint.SetX(offsetX);
    touchPoint.SetY(offsetY);
    cellCenter_ = touchPoint;

    AddPassPoint(currentPoint_.first, currentPoint_.second);
    choosePoint_.emplace_back(currentPoint_.first, currentPoint_.second);
    StartModifierConnectedAnimate(currentPoint_.first, currentPoint_.second);
    UpdateDotConnectEvent();

    isMoveEventValid_ = true;
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void PatternLockPattern::PaintFocusState()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->PaintFocusState(true);

    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void PatternLockPattern::OnKeyDrapUp()
{
    if (currentPoint_.second != 1) {
        currentPoint_ = { currentPoint_.first, currentPoint_.second - 1 };
        PaintFocusState();
    }
}

void PatternLockPattern::OnKeyDrapDown()
{
    if (currentPoint_.second != PATTERN_LOCK_COL_COUNT) {
        currentPoint_ = { currentPoint_.first, currentPoint_.second + 1 };
        PaintFocusState();
    }
}

void PatternLockPattern::OnKeyDrapLeft()
{
    if (currentPoint_.first != 1) {
        currentPoint_ = { currentPoint_.first - 1, currentPoint_.second };
        PaintFocusState();
    }
}

void PatternLockPattern::OnKeyDrapRight()
{
    if (currentPoint_.first != PATTERN_LOCK_COL_COUNT) {
        currentPoint_ = { currentPoint_.first + 1, currentPoint_.second };
        PaintFocusState();
    }
}

bool PatternLockPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.action != KeyAction::DOWN) {
        return false;
    }
    switch (event.code) {
        case KeyCode::KEY_SPACE:
            OnFocusClick();
            return true;
        case KeyCode::KEY_ENTER:
            if (isMoveEventValid_) {
                AddPointEnd();
            }
            return true;
        case KeyCode::KEY_DPAD_UP:
            OnKeyDrapUp();
            return true;
        case KeyCode::KEY_DPAD_DOWN:
            OnKeyDrapDown();
            return true;
        case KeyCode::KEY_DPAD_LEFT:
            OnKeyDrapLeft();
            return true;
        case KeyCode::KEY_DPAD_RIGHT:
            OnKeyDrapRight();
            return true;
        case KeyCode::KEY_MOVE_HOME:
            currentPoint_ = { 1, 1 };
            PaintFocusState();
            return true;
        case KeyCode::KEY_MOVE_END:
            currentPoint_ = { PATTERN_LOCK_COL_COUNT, PATTERN_LOCK_COL_COUNT };
            PaintFocusState();
            return true;
        case KeyCode::KEY_ESCAPE:
            HandleReset();
            return true;
        default:
            break;
    }
    return false;
}

void PatternLockPattern::InitMouseEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto inputEventHub = eventHub->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputEventHub);
    auto hoverTask = [weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleHoverEvent(isHover);
    };
    auto hoverEvent = MakeRefPtr<InputEvent>(std::move(hoverTask));
    CHECK_NULL_VOID(hoverEvent);
    inputEventHub->AddOnHoverEvent(hoverEvent);

    auto mouseTask = [weak = WeakClaim(this)](MouseInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleMouseEvent(info);
    };
    auto mouseEvent_ = MakeRefPtr<InputEvent>(std::move(mouseTask));
    inputEventHub->AddOnMouseEvent(mouseEvent_);
}

void PatternLockPattern::HandleHoverEvent(bool isHover)
{
    CHECK_NULL_VOID(patternLockModifier_);
    patternLockModifier_->SetIsHover(isHover);
}

void PatternLockPattern::HandleMouseEvent(const MouseInfo& info)
{
    OffsetF hoverPoint;
    hoverPoint.SetX(info.GetLocalLocation().GetX());
    hoverPoint.SetY(info.GetLocalLocation().GetY());
    cellCenter_ = hoverPoint;
    bool isPointHover = false;
    for (int32_t i = 0; i < PATTERN_LOCK_COL_COUNT; i++) {
        for (int32_t j = 0; j < PATTERN_LOCK_COL_COUNT; j++) {
            if (CheckInHotSpot(hoverPoint, i + 1, j + 1)) {
                CHECK_NULL_VOID(patternLockModifier_);
                patternLockModifier_->SetHoverIndex(i * PATTERN_LOCK_COL_COUNT + j);
                isPointHover = true;
                break;
            }
        }
    }
    if (!isPointHover) {
        patternLockModifier_->SetHoverIndex(-1);
    }
}

void PatternLockPattern::StartModifierConnectedAnimate(int32_t x, int32_t y)
{
    CHECK_NULL_VOID(patternLockModifier_);
    patternLockModifier_->StartConnectedCircleAnimate(x, y);
    patternLockModifier_->StartConnectedLineAnimate(x, y);
}

void PatternLockPattern::StartModifierAddPassPointAnimate(int32_t x, int32_t y)
{
    CHECK_NULL_VOID(patternLockModifier_);
    patternLockModifier_->StartConnectedCircleAnimate(x, y);
}

void PatternLockPattern::StartModifierCanceledAnimate()
{
    CHECK_NULL_VOID(patternLockModifier_);
    if (isMoveEventValid_) {
        patternLockModifier_->StartCanceledAnimate();
    }
}
} // namespace OHOS::Ace::NG
