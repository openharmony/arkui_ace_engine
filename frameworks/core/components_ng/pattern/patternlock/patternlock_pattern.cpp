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

void PatternLockPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetLayoutProperty()->UpdateAlignment(Alignment::CENTER);
}

void PatternLockPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto gestureHub = host->GetOrCreateGestureEventHub();
    InitTouchEvent(gestureHub, touchDownListener_);
    InitPatternLockController();
}

void PatternLockPattern::InitTouchEvent(RefPtr<GestureEventHub>& gestureHub, RefPtr<TouchEventImpl>& touchDownListener)
{
    if (touchDownListener) {
        return;
    }
    auto touchDownTask = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleTouchEvent(info);
        }
    };
    if (touchDownListener) {
        gestureHub->RemoveTouchEvent(touchDownListener);
    }
    touchDownListener = MakeRefPtr<TouchEventImpl>(std::move(touchDownTask));
    gestureHub->AddTouchEvent(touchDownListener);
}

void PatternLockPattern::InitPatternLockController()
{
    patternLockController_->SetResetImpl([weak = WeakClaim(this)]() {
        auto patternLock = weak.Upgrade();
        if (patternLock) {
            patternLock->HandleReset();
        }
    });
}

void PatternLockPattern::HandleTouchEvent(const TouchEventInfo& info)
{
    auto touchType = info.GetTouches().front().GetTouchType();
    if (touchType == TouchType::DOWN) {
        OnTouchDown(info);
    } else if (touchType == TouchType::UP) {
        OnTouchUp(info);
    } else if (touchType == TouchType::MOVE) {
        OnTouchMove(info);
    }
}

bool PatternLockPattern::AddChoosePoint(const OffsetF& offset, int16_t x, int16_t y)
{
    constexpr int32_t RADIUS_TO_DIAMETER = 2;
    constexpr float SCALE_SELECTED_CIRCLE_RADIUS = 26.00 / 14.00;

    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto patternLockPaintProperty = host->GetPaintProperty<PatternLockPaintProperty>();
    if (patternLockPaintProperty->HasSideLength()) {
        sideLength_ = patternLockPaintProperty->GetSideLengthValue();
    }
    if (patternLockPaintProperty->HasCircleRadius()) {
        circleRadius_ = patternLockPaintProperty->GetCircleRadiusValue();
    }

    const int16_t scale = RADIUS_TO_DIAMETER;
    float offsetX = sideLength_.ConvertToPx() / PATTERN_LOCK_COL_COUNT / scale * (scale * x - 1);
    float offsetY = sideLength_.ConvertToPx() / PATTERN_LOCK_COL_COUNT / scale * (scale * y - 1);
    OffsetF centerOffset;
    centerOffset.SetX(offsetX);
    centerOffset.SetY(offsetY);
    auto X = (offset - centerOffset).GetX();
    auto Y = (offset - centerOffset).GetY();
    float distance = std::sqrt((X * X) + (Y * Y));
    if (distance <= (circleRadius_.ConvertToPx() * SCALE_SELECTED_CIRCLE_RADIUS)) {
        if (!CheckChoosePoint(x, y)) {
            AddPassPoint(x, y);
            choosePoint_.emplace_back(x, y);
        }
        return true;
    }
    return false;
}

bool PatternLockPattern::CheckChoosePoint(int16_t x, int16_t y) const
{
    for (auto it : choosePoint_) {
        if (it.GetColumn() == x && it.GetRow() == y) {
            return true;
        }
    }
    return false;
}

void PatternLockPattern::AddPassPoint(int16_t x, int16_t y)
{
    if (choosePoint_.empty()) {
        return;
    }
    passPointCount_ = 0;
    PatternLockCell lastCell = choosePoint_.back();
    int16_t lastX = lastCell.GetColumn();
    int16_t lastY = lastCell.GetRow();
    int16_t lastCode = lastCell.GetCode();
    int16_t nowCode = PATTERN_LOCK_COL_COUNT * (y - 1) + (x - 1);
    std::vector<PatternLockCell> passPointVec;
    for (int16_t i = 1; i <= PATTERN_LOCK_COL_COUNT; i++) {
        for (int16_t j = 1; j <= PATTERN_LOCK_COL_COUNT; j++) {
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
    passPointCount_ = static_cast<int16_t>(passPointLength);
    if (nowCode > lastCode) {
        choosePoint_.emplace_back(passPointVec.front());
        if (passPointLength > 1) {
            choosePoint_.emplace_back(passPointVec.back());
        }
    } else {
        choosePoint_.emplace_back(passPointVec.back());
        if (passPointLength > 1) {
            choosePoint_.emplace_back(passPointVec.front());
        }
    }
}

void PatternLockPattern::HandleReset()
{
    isMoveEventValid_ = false;
    choosePoint_.clear();
    cellCenter_.Reset();
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
    for (int16_t i = 0; i < PATTERN_LOCK_COL_COUNT && !isAdd; i++) {
        for (int16_t j = 0; j < PATTERN_LOCK_COL_COUNT && !isAdd; j++) {
            isAdd = AddChoosePoint(touchPoint, i + 1, j + 1);
        }
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    isMoveEventValid_ = true;
}

void PatternLockPattern::OnTouchMove(const TouchEventInfo& info)
{
    const auto& locationInfo = info.GetTouches().front();
    float moveDeltaX = locationInfo.GetLocalLocation().GetX();
    float moveDeltaY = locationInfo.GetLocalLocation().GetY();
    OffsetF touchPoint;
    touchPoint.SetX(moveDeltaX);
    touchPoint.SetY(moveDeltaY);

    if (!isMoveEventValid_) {
        return;
    }
    cellCenter_ = touchPoint;
    bool isAdd = false;
    for (int16_t i = 0; i < PATTERN_LOCK_COL_COUNT && !isAdd; i++) {
        for (int16_t j = 0; j < PATTERN_LOCK_COL_COUNT && !isAdd; j++) {
            isAdd = AddChoosePoint(touchPoint, i + 1, j + 1);
        }
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void PatternLockPattern::OnTouchUp(const TouchEventInfo& info)
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

} // namespace OHOS::Ace::NG
