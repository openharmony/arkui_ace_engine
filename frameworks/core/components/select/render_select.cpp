/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "core/components/select/render_select.h"

namespace OHOS::Ace {

void RenderSelect::OnTouchTestHit(
    const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result)
{
    if (clickRecognizer_) {
        clickRecognizer_->SetCoordinateOffset(coordinateOffset);
        result.emplace_back(clickRecognizer_);
        clickRecognizer_->SetIsExternalGesture(true);
    }

    if (rawRecognizer_) {
        rawRecognizer_->SetCoordinateOffset(coordinateOffset);
        result.emplace_back(rawRecognizer_);
    }
}

void RenderSelect::Update(const RefPtr<Component>& component)
{
    data_ = AceType::DynamicCast<SelectComponent>(component);

    ApplyRestoreInfo();

    MarkNeedLayout();
}

void RenderSelect::PerformLayout()
{
    auto children = GetChildren();
    if (children.empty()) {
        LOGE("select: there has no child.");
        return;
    }

    auto child = children.front();
    if (!child) {
        LOGE("select: there has no child now in render select.");
        return;
    }

    child->Layout(GetLayoutParam());
    selectSize_ = child->GetLayoutSize();
    selectSize_ = GetLayoutParam().Constrain(selectSize_);
    SetLayoutSize(selectSize_);
}

std::string RenderSelect::ProvideRestoreInfo()
{
    std::size_t optionCount = data_->GetSelectOptionCount();
    index_ = 0;
    for (std::size_t index = 0; index < optionCount; index++) {
        auto optionComponent = data_->GetSelectOption(index);
        if (optionComponent->GetSelected()) {
            index_ = index;
            break;
        }
    }
    return std::to_string(index_);
}

void RenderSelect::ApplyRestoreInfo()
{
    if (GetRestoreInfo().empty()) {
        return;
    }
    index_ = static_cast<size_t>(StringUtils::StringToInt(GetRestoreInfo()));
    SetRestoreInfo("");

    auto tipText = data_->GetTipText();
    auto optionComponent = data_->GetSelectOption(index_);
    optionComponent->SetSelected(true);

    auto optionText = optionComponent->GetText();
    if (!optionText) {
        return;
    }
    tipText->SetData(optionText->GetData());
}

} // namespace OHOS::Ace
