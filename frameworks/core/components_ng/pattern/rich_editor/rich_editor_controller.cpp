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

#include "core/components_ng/pattern/rich_editor/rich_editor_controller.h"

#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"

namespace OHOS::Ace::NG {
void RichEditorController::SetPattern(const WeakPtr<Pattern>& pattern)
{
    pattern_ = pattern;
}

int32_t RichEditorController::AddImageSpan(const ImageSpanOptions& options)
{
    auto richEditorPattern = AceType::DynamicCast<RichEditorPattern>(pattern_.Upgrade());
    int32_t spanIndex = 0;
    if (richEditorPattern) {
        richEditorPattern->AddImageSpan(options);
        spanIndex = richEditorPattern->GetSpanIndex();
    }
    return spanIndex;
}

int32_t RichEditorController::AddTextSpan(const TextSpanOptions& options)
{
    auto richEditorPattern = AceType::DynamicCast<RichEditorPattern>(pattern_.Upgrade());
    int32_t spanIndex = 0;
    if (richEditorPattern) {
        richEditorPattern->AddTextSpan(options);
        spanIndex = richEditorPattern->GetSpanIndex();
    }
    return spanIndex;
}
} // namespace OHOS::Ace::NG
