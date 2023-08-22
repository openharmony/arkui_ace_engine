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

#include "core/components/text_field/text_field_scroll_bar_controller.h"
#include "core/components/text_field/render_text_field.h"

namespace OHOS::Ace {
void TextFieldScrollBarController::MarkScrollRender()
{
    auto list = AceType::DynamicCast<RenderTextField>(scroll_.Upgrade());
    if (list) {
        list->MarkNeedLayout();
    }
}

bool TextFieldScrollBarController::CheckScroll()
{
    auto textFiled = AceType::DynamicCast<RenderTextField>(scroll_.Upgrade());
    return textFiled != nullptr;
}

bool TextFieldScrollBarController::UpdateScrollPosition(const double offset, int32_t source)
{
    bool ret = true;
    if (!callback_) {
        return true;
    }
    auto textField = AceType::DynamicCast<RenderTextField>(scroll_.Upgrade());
    if (!textField) {
        return true;
    }
    double height = textField->GetLayoutSize().Width();
    double estimateHeight = textField->GetEstimatedHeight();
    if (NearZero(estimateHeight) || NearZero(height)) {
        return true;
    }
    double activeHeight = height * height / estimateHeight;
    if (!NearEqual(height, activeHeight)) {
        double value = offset * estimateHeight / height;
        ret = callback_(value, source);
    }
    return ret;
}

void TextFieldScrollBarController::ProcessScrollMotion(double position)
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
} // namespace OHOS::Ace