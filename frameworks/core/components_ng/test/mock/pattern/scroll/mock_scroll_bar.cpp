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

#include "core/components_ng/pattern/scroll/inner/scroll_bar.h"

namespace OHOS::Ace::NG {
ScrollBar::ScrollBar() {}

bool ScrollBar::NeedPaint() const
{
    return isScrollable_;
}

void ScrollBar::OnCollectTouchTarget(
    const OffsetF& coordinateOffset, const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result)
{}

bool ScrollBar::InBarTouchRegion(const Point& point) const
{
    return false;
}
} // namespace OHOS::Ace::NG
