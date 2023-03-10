/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/swiper/swiper_pattern.h"

namespace OHOS::Ace::NG {
SwiperPattern::SwiperPattern()
{
    swiperController_ = MakeRefPtr<SwiperController>();
}

void SwiperPattern::OnAttachToFrameNode()
{
    (void)isLastIndicatorFocused_;
    (void)distance_;
    (void)moveDirection_;
    (void)elapsedTime_;
}

void SwiperPattern::OnIndexChange() const
{
}

void SwiperPattern::OnModifyDone()
{
}

void SwiperPattern::FlushFocus(const RefPtr<FrameNode>& curShowFrame)
{
}

WeakPtr<FocusHub> SwiperPattern::GetNextFocusNode(FocusStep step, const WeakPtr<FocusHub>& currentFocusNode)
{
    return nullptr;
}

bool SwiperPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    return false;
}

void SwiperPattern::CalculateCacheRange()
{
}

void SwiperPattern::FireChangeEvent() const
{
}

void SwiperPattern::FireAnimationStartEvent() const
{
}

void SwiperPattern::FireAnimationEndEvent() const
{
}

void SwiperPattern::SwipeToWithoutAnimation(int32_t index)
{
}

void SwiperPattern::SwipeTo(int32_t index)
{
}

void SwiperPattern::ShowNext()
{
}

void SwiperPattern::ShowPrevious()
{
}

void SwiperPattern::FinishAnimation()
{
}

void SwiperPattern::StopTranslateAnimation()
{
}

void SwiperPattern::StopSpringAnimation()
{
}

void SwiperPattern::InitSwiperController()
{
}

void SwiperPattern::InitIndicator()
{
}

void SwiperPattern::InitPanEvent(const RefPtr<GestureEventHub>& gestureHub)
{
}

void SwiperPattern::InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub)
{
}

void SwiperPattern::InitOnKeyEvent(const RefPtr<FocusHub>& focusHub)
{
}

bool SwiperPattern::OnKeyEvent(const KeyEvent& event)
{
    return false;
}

void SwiperPattern::InitAutoPlay()
{
}

void SwiperPattern::Tick(uint64_t duration)
{
}

void SwiperPattern::StopAutoPlay()
{
}

void SwiperPattern::StartAutoPlay()
{
}

void SwiperPattern::OnVisibleChange(bool isVisible)
{
}

void SwiperPattern::UpdateCurrentOffset(float offset)
{
}

void SwiperPattern::HandleTouchEvent(const TouchEventInfo& info)
{
}

void SwiperPattern::HandleTouchDown()
{
}

void SwiperPattern::HandleTouchUp()
{
}

void SwiperPattern::HandleDragStart()
{
}

void SwiperPattern::HandleDragUpdate(const GestureEvent& info)
{
}

void SwiperPattern::HandleDragEnd(double dragVelocity)
{
}

void SwiperPattern::PlayTranslateAnimation(float startPos, float endPos, int32_t nextIndex, bool restartAutoPlay)
{
}

void SwiperPattern::PlaySpringAnimation(double dragVelocity)
{
}

void SwiperPattern::PlayFadeAnimation()
{
}

bool SwiperPattern::IsOutOfBoundary(float mainOffset) const
{
    return true;
}

float SwiperPattern::MainSize() const
{
    return 0.0f;
}

float SwiperPattern::GetItemSpace() const
{
    return 0.0f;
}

Axis SwiperPattern::GetDirection() const
{
    return Axis::HORIZONTAL;
}

int32_t SwiperPattern::CurrentIndex() const
{
    return 0;
}

int32_t SwiperPattern::GetDisplayCount() const
{
    return 0;
}

bool SwiperPattern::IsAutoPlay() const
{
    return false;
}

int32_t SwiperPattern::GetDuration() const
{
    return 0;
}

int32_t SwiperPattern::GetInterval() const
{
    return 0;
}

RefPtr<Curve> SwiperPattern::GetCurve() const
{
    return nullptr;
}

bool SwiperPattern::IsLoop() const
{
    return true;
}

EdgeEffect SwiperPattern::GetEdgeEffect() const
{
    return EdgeEffect::SPRING;
}

bool SwiperPattern::IsDisableSwipe() const
{
    return false;
}

bool SwiperPattern::IsShowIndicator() const
{
    return true;
}

int32_t SwiperPattern::TotalCount() const
{
    return 1;
}

float SwiperPattern::GetTranslateLength() const
{
    return 0.0f;
}
} // namespace OHOS::Ace::NG
