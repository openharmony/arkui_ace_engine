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

#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_arrow_pattern.h"
namespace OHOS::Ace::NG {
void SwiperArrowPattern::OnModifyDone()
{
    isFirstCreate_ = false;
}
void SwiperArrowPattern::InitSwiperChangeEvent(const RefPtr<SwiperEventHub>& swiperEventHub) {}
void SwiperArrowPattern::UpdateButtonNode(int32_t index)
{
    index_ = index;
}
void SwiperArrowPattern::InitButtonEvent()
{
    isTouch_ = true;
}
void SwiperArrowPattern::InitNavigationArrow() {}
int32_t SwiperArrowPattern::TotalCount() const
{
    return 0;
}
void SwiperArrowPattern::ButtonTouchEvent(RefPtr<FrameNode> buttonNode, TouchType touchType) {}
void SwiperArrowPattern::ButtonOnHover(RefPtr<FrameNode> buttonNode, bool isHovered)
{
    isHover_ = isHovered;
}
void SwiperArrowPattern::SetButtonVisible(bool visible) {}
void SwiperArrowPattern::UpdateArrowContent() {}
} // namespace OHOS::Ace::NG
