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

#include "core/components_ng/pattern/text_picker/textpicker_overscroll.h"

#include "core/components_ng/pattern/text_picker/textpicker_column_pattern.h"

namespace OHOS::Ace::NG {
namespace {
const int32_t HALF_NUMBER = 2;
constexpr float MIN_SCROLL = 0.1f;
constexpr float MIN_VELOCITY = 200.f;
constexpr float REBOUND_SCROLL_DAMPING = -1.848f;
constexpr float REBOUND_SPRING_VELOCITY = 1.f;
constexpr float REBOUND_SPRING_MASS = 1.f;
constexpr float REBOUND_SPRING_STIFFNESS = 228.f;
constexpr float REBOUND_SPRING_DAMPING = 30.f;
constexpr float LOOP_TOSS_DAMPING = 100.f;
} //namespace
bool TextPickerOverscroller::ApplyCurrentOffset(float yLast, float offsetY, float scrollDelta)
{
    auto column = AceType::DynamicCast<TextPickerColumnPattern>(column_.Upgrade());
    CHECK_NULL_RETURN(column, false);
    auto hostNode = column->GetHost();
    CHECK_NULL_RETURN(hostNode, false);
    auto geometryNode = hostNode->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, false);
    height_ = geometryNode->GetFrameSize().Height();

    if (!CanOverScroll(scrollDelta)) {
        overScroll_ = 0.0;
        backScrollOffset_ = 0.0;
        return false;
    }

    // start overScroll
    isFirstStart_ = false;
    if (NearZero(overScroll_)) {
        overScrollStartOffsetY_ = yLast;
        isFirstStart_ = true;
    }

    deltaScrollOffset_ = GetOverScrollOffset(yLast, offsetY);

    auto isSignDiff = LessNotEqual(deltaScrollOffset_ * overScroll_, 0.0);
    auto isBackZero = isSignDiff && GreatOrEqual(std::fabs(deltaScrollOffset_), std::fabs(overScroll_));
    if (!NearZero(overScroll_) && isBackZero) { // overScroll come back zero
        overScroll_ = 0.0;
        backScrollOffset_ = overScroll_ + deltaScrollOffset_;
    } else {
        overScroll_ += deltaScrollOffset_;
        overScroll_ = (overScroll_ > 0.0 ? 1 : -1) * std::min(std::fabs(overScroll_), height_ / HALF_NUMBER);
        backScrollOffset_ = 0.0;
    }

    return true;
}

bool TextPickerOverscroller::CanOverScroll(float scrollDelta) const
{
    if (NearZero(scrollDelta)) {
        return false;
    }

    auto column = AceType::DynamicCast<TextPickerColumnPattern>(column_.Upgrade());
    CHECK_NULL_RETURN(column, false);
    auto currentIdx = column->GetCurrentIndex();
    auto optionCount = column->GetOptionCount();
    if (optionCount == 0) {
        return false;
    }
    auto isDown = GreatNotEqual(overScroll_, 0.0) || (GreatNotEqual(scrollDelta, 0.0) && NearZero(overScroll_));
    auto isUp = LessNotEqual(overScroll_, 0.0) || (LessNotEqual(scrollDelta, 0.0) && NearZero(overScroll_));
    return (currentIdx == 0 && isDown) || (currentIdx == optionCount - 1 && isUp);
}

float TextPickerOverscroller::GetOverScrollOffset(float yLast, float offsetY) const
{
    auto dx = offsetY - yLast;
    auto input = NearZero(height_) ? 0.0 : std::fabs(offsetY - overScrollStartOffsetY_) / height_;
    return dx * std::exp(REBOUND_SCROLL_DAMPING * input);
}

RefPtr<Curve> TextPickerOverscroller::GetReboundCurve() const
{
    return AceType::MakeRefPtr<InterpolatingSpring>(
        REBOUND_SPRING_VELOCITY, REBOUND_SPRING_MASS, REBOUND_SPRING_STIFFNESS, REBOUND_SPRING_DAMPING);
}

void TextPickerOverscroller::UpdateTossSpring(float offsetY)
{
    velocityTracker_.UpdateTrackerPoint(0.0, offsetY, std::chrono::high_resolution_clock::now());
}

bool TextPickerOverscroller::ShouldStartRebound()
{
    auto damping = NearZero(loopTossOffset_) ? 1.0 : LOOP_TOSS_DAMPING / std::abs(loopTossOffset_);
    auto velocity = std::abs(velocityTracker_.GetVelocity().GetVelocityY()) * damping;
    auto canRebound = !isFirstStart_ && velocity < MIN_VELOCITY;
    return canRebound || InMaxOverScroll() || NearZero(deltaScrollOffset_, MIN_SCROLL);
}

void TextPickerOverscroller::Reset()
{
    overScroll_ = 0.0;
    backScrollOffset_ = 0.0;
    deltaScrollOffset_ = 0.0;
    overScrollStartOffsetY_ = 0.0;
    isFirstStart_ = false;
    loopTossOffset_ = 0.0;
    velocityTracker_.Reset();
}

bool TextPickerOverscroller::InMaxOverScroll() const
{
    return GreatOrEqual(std::fabs(overScroll_), height_ / HALF_NUMBER);
}

bool TextPickerOverscroller::IsOverScroll() const
{
    return !NearZero(overScroll_);
}

bool TextPickerOverscroller::IsBackOverScroll() const
{
    return !NearZero(backScrollOffset_);
}
} // namespace OHOS::Ace::NG