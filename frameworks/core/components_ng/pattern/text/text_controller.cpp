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

#include "core/components_ng/pattern/text/text_controller.h"

#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {
void TextController::SetPattern(const WeakPtr<TextPattern>& pattern)
{
    pattern_ = pattern;
}

void TextController::CloseSelectionMenu()
{
    auto textPattern = pattern_.Upgrade();
    if (textPattern) {
        textPattern->CloseSelectionMenu();
    }
}

void TextController::SetStyledString(const RefPtr<SpanStringBase>& value)
{
    auto textPattern = pattern_.Upgrade();
    if (textPattern) {
        auto spanString = AceType::DynamicCast<SpanString>(value);
        if (spanString) {
            textPattern->SetStyledString(spanString);
        }
    }
}

WeakPtr<LayoutInfoInterface> TextController::GetLayoutInfoInterface()
{
    auto textPattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(textPattern, nullptr);
    return textPattern->GetLayoutInfoInterface();
}
} // namespace OHOS::Ace::NG