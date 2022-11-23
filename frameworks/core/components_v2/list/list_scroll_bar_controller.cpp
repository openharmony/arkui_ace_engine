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

#include "core/components_v2/list/list_scroll_bar_controller.h"

#include "core/components_v2/list/render_list.h"

namespace OHOS::Ace::V2 {
void ListScrollBarController::MarkScrollRender()
{
    auto list = AceType::DynamicCast<RenderList>(scroll_.Upgrade());
    if (list) {
        list->MarkNeedLayout();
    }
}

bool ListScrollBarController::CheckScroll()
{
    auto list = AceType::DynamicCast<RenderList>(scroll_.Upgrade());
    return list != nullptr;
}

bool ListScrollBarController::UpdateScrollPosition(const double offset, int32_t source)
{
    bool ret = true;
    if (!callback_) {
        return true;
    }
    auto list = AceType::DynamicCast<RenderList>(scroll_.Upgrade());
    if (!list) {
        return true;
    }
    double height = list->GetLayoutSize().Height();
    double estimateHeight = list->GetEstimatedHeight();
    if (NearZero(estimateHeight) || NearZero(height)) {
        return true;
    }
    double activeHeight = height * height / estimateHeight;
    if (!NearEqual(height, activeHeight)) {
        double value = offset * estimateHeight / height;
        ret = source == SCROLL_FROM_AXIS ? callback_(offset, source) : callback_(value, source);
    }
    return ret;
}

void ListScrollBarController::ProcessScrollMotion(double position)
{
    if (!NearEqual(currentPos_, position)) {
        UpdateScrollPosition(0.0, SCROLL_FROM_ANIMATION);
    } else {
        if (!UpdateScrollPosition(currentPos_ - position, SCROLL_FROM_BAR)) {
            dragEndAnimator_->Stop();
        }
    }
    currentPos_ = position;
}
} // namespace OHOS::Ace::V2