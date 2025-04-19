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

#include "base/i18n/localization.h"
#include "core/components_ng/pattern/patternlock/patternlock_pattern.h"

#include "core/components_ng/pattern/stage/page_event_hub.h"
#include "core/components_ng/pattern/text/text_pattern.h"
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
    InitPatternLockController();
    InitFocusEvent();
    InitMouseEvent();
    InitAccessibilityHoverEvent();
    InitSkipUnselectedPoint();
    if (isInitVirtualNode_) {
        auto pipeline = host->GetContext();
        CHECK_NULL_VOID(pipeline);
        pipeline->AddAfterRenderTask([weak = WeakClaim(this)]() {
            auto patternLock = weak.Upgrade();
            CHECK_NULL_VOID(patternLock);
            patternLock->ModifyAccessibilityVirtualNode();
        });
    }
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
    gestureHub->SetHitTestMode(HitTestMode::HTMBLOCK);
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

void PatternLockPattern::InitAccessibilityHoverEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetOrCreateInputEventHub();
    eventHub->SetAccessibilityHoverEvent([weak = WeakClaim(this)](bool isHover, AccessibilityHoverInfo& info) {
        auto patternLock = weak.Upgrade();
        CHECK_NULL_VOID(patternLock);
        patternLock->HandleAccessibilityHoverEvent(isHover, info);
    });
}

void PatternLockPattern::HandleAccessibilityHoverEvent(bool isHover, AccessibilityHoverInfo& info)
{
    auto accessibilityHoverAction = info.GetActionType();
    if (isHover && (accessibilityHoverAction == AccessibilityHoverAction::HOVER_ENTER ||
                     accessibilityHoverAction == AccessibilityHoverAction::HOVER_MOVE)) {
        for (const auto& accessibilityProperty : accessibilityPropertyVec_) {
            accessibilityProperty->SetAccessibilityLevel(AccessibilityProperty::Level::YES_STR);
        }
        if (!CheckAutoReset()) {
            return;
        }
        HandleReset();
    } else if (!isHover) {
        for (const auto& accessibilityProperty : accessibilityPropertyVec_) {
            accessibilityProperty->SetAccessibilityLevel(AccessibilityProperty::Level::NO_STR);
        }
        AddPointEnd();
        auto host = GetHost();
        auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
        accessibilityProperty->SetAccessibilityLevel(AccessibilityProperty::Level::YES_STR);
    }
}

bool PatternLockPattern::InitVirtualNode()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    float handleCircleRadius = 0.0f;
    if (!GetHandleCircleRadius(handleCircleRadius)) {
        return false;
    }
    auto lineNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto renderContext = lineNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);
    renderContext->UpdatePosition(OffsetT(Dimension(0.0f), Dimension(0.0f)));
    for (int32_t y = 0; y < PATTERN_LOCK_COL_COUNT; y++) {
        for (int32_t x = 0; x < PATTERN_LOCK_COL_COUNT; x++) {
            auto textNode = AddTextNodeIntoVirtual(x + 1, y + 1, handleCircleRadius);
            lineNode->AddChild(textNode);
            textAccessibilityNodeVec_.emplace_back(textNode);
        }
    }
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    accessibilityProperty->SetAccessibilityText(" ");
    auto virtualFrameNode = AceType::DynamicCast<NG::FrameNode>(lineNode);
    CHECK_NULL_RETURN(virtualFrameNode, false);
    virtualFrameNode->SetAccessibilityNodeVirtual();
    virtualFrameNode->SetAccessibilityVirtualNodeParent(AceType::DynamicCast<NG::UINode>(host));
    virtualFrameNode->SetFirstAccessibilityVirtualNode();
    FrameNode::ProcessOffscreenNode(virtualFrameNode);
    accessibilityProperty->SaveAccessibilityVirtualNode(lineNode);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    ModifyAccessibilityVirtualNode();
    return true;
}

RefPtr<FrameNode> PatternLockPattern::AddTextNodeIntoVirtual(int32_t x, int32_t y, float handleCircleRadius)
{
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    UpdateAccessibilityTextNode(textNode, handleCircleRadius, x, y);
    auto textAccessibilityProperty = textNode->GetAccessibilityProperty<AccessibilityProperty>();
    accessibilityPropertyVec_.emplace_back(textAccessibilityProperty);
    textAccessibilityProperty->SetOnAccessibilityFocusCallback([weak = WeakClaim(this), x, y](bool focus) {
        if (focus) {
            auto patternLock = weak.Upgrade();
            CHECK_NULL_VOID(patternLock);
            patternLock->HandleTextOnAccessibilityFocusCallback(x, y);
        }
    });
    return textNode;
}


void PatternLockPattern::HandleTextOnAccessibilityFocusCallback(int32_t x, int32_t y)
{
    if (!CheckChoosePoint(x, y)) {
        AddPassPoint(x, y);
        choosePoint_.emplace_back(x, y);
        StartModifierConnectedAnimate(x, y);
        auto host = GetHost();
        auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
        accessibilityProperty->SetAccessibilityLevel(AccessibilityProperty::Level::NO_STR);
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}


void PatternLockPattern::ModifyAccessibilityVirtualNode()
{
    if (textAccessibilityNodeVec_.size() < 1) {
        return;
    }
    float handleCircleRadius = 0.0f;
    if (!GetHandleCircleRadius(handleCircleRadius)) {
        return;
    }
    for (int32_t y = 0; y < PATTERN_LOCK_COL_COUNT; y++) {
        for (int32_t x = 0; x < PATTERN_LOCK_COL_COUNT; x++) {
            auto textNode = textAccessibilityNodeVec_[y * PATTERN_LOCK_COL_COUNT + x];
            UpdateAccessibilityTextNode(textNode, handleCircleRadius, x, y);
        }
    }
    auto host = GetHost();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
}

std::string PatternLockPattern::ReplacePlaceHolder(const std::string& str, int32_t number)
{
    std::string result = str;
    std::string numberStr = std::to_string(number);

    size_t pos = result.find("%d");
    if (pos != std::string::npos) {
        result.replace(pos, 2, numberStr); // 2: "%d" length
    } else {
        result = str + numberStr;
    }

    return result;
}

void PatternLockPattern::UpdateAccessibilityTextNode(
    RefPtr<FrameNode> frameNode, float handleCircleRadius, int32_t x, int32_t y)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    OffsetF contentOffset = host->GetGeometryNode()->GetContentOffset();
    float sideLength = host->GetGeometryNode()->GetContentSize().Width();
    int32_t scale = RADIUS_TO_DIAMETER;
    float offsetX = sideLength / PATTERN_LOCK_COL_COUNT / scale * (scale * (x + 1) - 1);
    float offsetY = sideLength / PATTERN_LOCK_COL_COUNT / scale * (scale * (y + 1) - 1);
    int32_t index = y * PATTERN_LOCK_COL_COUNT + x + 1;
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto patternLockTheme = pipeline->GetTheme<V2::PatternLockTheme>();
    CHECK_NULL_VOID(patternLockTheme);
    auto message = patternLockTheme->GetPassPointTxt();
    std::string text = ReplacePlaceHolder(message, index);
    CHECK_NULL_VOID(frameNode);
    auto textLayoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateContent(text);
    Dimension focusPaddingRadius = Dimension(handleCircleRadius * RADIUS_TO_DIAMETER);
    CalcLength width = CalcLength(focusPaddingRadius);
    CalcLength height = CalcLength(focusPaddingRadius);
    textLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(width, height));
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    Dimension textOffsetX = Dimension(offsetX - handleCircleRadius + contentOffset.GetX());
    Dimension textOffsetY = Dimension(offsetY - handleCircleRadius + contentOffset.GetY());
    renderContext->UpdatePosition(OffsetT(textOffsetX, textOffsetY));
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void PatternLockPattern::HandleTouchEvent(const TouchEventInfo& info)
{
    auto touchList = info.GetChangedTouches();
    CHECK_NULL_VOID(!touchList.empty());
    if (fingerId_ == -1) {
        fingerId_ = touchList.front().GetFingerId();
    }
    for (const auto& touchInfo : touchList) {
        if (touchInfo.GetFingerId() == fingerId_) {
            auto touchType = touchInfo.GetTouchType();
            if (touchType == TouchType::DOWN) {
                OnTouchDown(touchInfo);
            } else if (touchType == TouchType::MOVE) {
                OnTouchMove(touchInfo);
            } else if (touchType == TouchType::UP) {
                OnTouchUp();
            } else if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_FOURTEEN) &&
                       touchType == TouchType::CANCEL) {
                OnTouchUp();
            }
            break;
        }
    }
}

bool PatternLockPattern::GetHandleCircleRadius(float& handleCircleRadius)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto patternLockPaintProperty = host->GetPaintProperty<PatternLockPaintProperty>();
    float sideLength = host->GetGeometryNode()->GetContentSize().Width();
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
    handleCircleRadius = std::min(static_cast<float>(circleRadius_.ConvertToPxWithSize(sideLength)),
        sideLength / backgroundRadiusScale / RADIUS_COUNT);
    auto hotSpotCircleRadius = patternLockTheme->GetHotSpotCircleRadius();
    handleCircleRadius = std::max(handleCircleRadius * activeCircleRadiusScale,
        std::min(
            static_cast<float>(hotSpotCircleRadius.ConvertToPx()) / RADIUS_TO_DIAMETER, sideLength / RADIUS_COUNT));
    return true;
}


bool PatternLockPattern::CheckInHotSpot(const OffsetF& offset, int32_t x, int32_t y)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    float sideLength = host->GetGeometryNode()->GetContentSize().Width();
    OffsetF contentOffset = host->GetGeometryNode()->GetContentOffset();
    auto handleCircleRadius = 0.0f;
    if (!GetHandleCircleRadius(handleCircleRadius)) {
        return false;
    }
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
    auto eventHub = host->GetOrCreateEventHub<PatternLockEventHub>();
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
    if (choosePoint_.empty() || skipUnselectedPoint_) {
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
    isOnKeyEventState_ = false;
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

void PatternLockPattern::OnTouchDown(const TouchLocationInfo& info)
{
    auto locationX = static_cast<float>(info.GetLocalLocation().GetX());
    auto locationY = static_cast<float>(info.GetLocalLocation().GetY());
    screenTouchPoint_.SetX(locationX);
    screenTouchPoint_.SetY(locationY);

    if (!CheckAutoReset()) {
        return;
    }
    HandleReset();
    CalculateCellCenter();
    bool isAdd = false;
    for (int32_t i = 0; i < PATTERN_LOCK_COL_COUNT && !isAdd; i++) {
        for (int32_t j = 0; j < PATTERN_LOCK_COL_COUNT && !isAdd; j++) {
            isAdd = AddChoosePoint(cellCenter_, i + 1, j + 1);
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

void PatternLockPattern::OnTouchMove(const TouchLocationInfo& info)
{
    auto locationX = static_cast<float>(info.GetLocalLocation().GetX());
    auto locationY = static_cast<float>(info.GetLocalLocation().GetY());
    screenTouchPoint_.SetX(locationX);
    screenTouchPoint_.SetY(locationY);
    if (!isMoveEventValid_) {
        return;
    }
    CalculateCellCenter();
    bool isAdd = false;
    for (int32_t i = 0; i < PATTERN_LOCK_COL_COUNT && !isAdd; i++) {
        for (int32_t j = 0; j < PATTERN_LOCK_COL_COUNT && !isAdd; j++) {
            isAdd = AddChoosePoint(cellCenter_, i + 1, j + 1);
        }
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
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
    auto eventHub = host->GetOrCreateEventHub<PatternLockEventHub>();
    CHECK_NULL_VOID(eventHub);

    auto patternCompleteEvent = V2::PatternCompleteEvent(chooseCellVec);
    eventHub->UpdateCompleteEvent(&patternCompleteEvent);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void PatternLockPattern::OnTouchUp()
{
    CHECK_NULL_VOID(patternLockModifier_);
    patternLockModifier_->SetIsTouchDown(false);
    size_t count = patternLockModifier_->GetChoosePointCount();
    if (count < 1) {
        return;
    }
    StartModifierCanceledAnimate();
    AddPointEnd();
    fingerId_ = -1;
}

void PatternLockPattern::InitFocusEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);

    auto focusTask = [weak = WeakClaim(this)](FocusReason reason) {
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
    isOnKeyEventState_ = true;

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
                isOnKeyEventState_ = false;
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
    auto eventHub = host->GetOrCreateEventHub<EventHub>();
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

OffsetF PatternLockPattern::GetLastChoosePointOffset()
{
    OffsetF cellCenter;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, cellCenter);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, cellCenter);
    float sideLength = geometryNode->GetContentSize().Width();
    auto offset = geometryNode->GetContentOffset();
    auto lastPoint = choosePoint_.back();
    cellCenter.SetX(offset.GetX() + sideLength / PATTERN_LOCK_COL_COUNT / RADIUS_TO_DIAMETER *
                                        (lastPoint.GetColumn() * RADIUS_TO_DIAMETER - 1));
    cellCenter.SetY(offset.GetY() + sideLength / PATTERN_LOCK_COL_COUNT / RADIUS_TO_DIAMETER *
                                        (lastPoint.GetRow() * RADIUS_TO_DIAMETER - 1));
    return cellCenter;
}

void PatternLockPattern::CalculateCellCenter()
{
    if (isOnKeyEventState_) {
        size_t count = choosePoint_.size();
        if (count < 1) {
            return;
        }
        cellCenter_ = GetLastChoosePointOffset();
    } else {
        cellCenter_ = screenTouchPoint_;
    }
}

OffsetF PatternLockPattern::GetTouchOffsetToNode()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, OffsetF());
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, OffsetF());
    auto windowOffset = pipelineContext->GetCurrentWindowRect().GetOffset();
    OffsetF nodeOffset = host->GetPositionToWindowWithTransform();
    auto container = Container::CurrentSafely();
    auto windowScale = container->GetWindowScale();
    nodeOffset = nodeOffset * windowScale;
    OffsetF offset(windowOffset.GetX() + nodeOffset.GetX(), windowOffset.GetY() + nodeOffset.GetY());
    offset = screenTouchPoint_ - offset;
    if (windowScale != 0) {
        offset = offset / windowScale;
    }
    return offset;
}

void PatternLockPattern::InitSkipUnselectedPoint()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto patternLockPaintProperty = host->GetPaintProperty<PatternLockPaintProperty>();
    CHECK_NULL_VOID(patternLockPaintProperty);
    if (patternLockPaintProperty->HasSkipUnselectedPoint()) {
        skipUnselectedPoint_ = patternLockPaintProperty->GetSkipUnselectedPointValue();
    }
}
} // namespace OHOS::Ace::NG
