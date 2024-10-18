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

#include "core/components_ng/pattern/rich_editor/rich_editor_accessibility_property.h"

#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"

namespace OHOS::Ace::NG {

bool RichEditorAccessibilityProperty::IsEditable() const
{
    return true;
}

std::string RichEditorAccessibilityProperty::GetHintText() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, "");
    auto richEditorPattern = frameNode->GetPattern<RichEditorPattern>();
    CHECK_NULL_RETURN(richEditorPattern, "");
    return richEditorPattern->GetPlaceHolder();
}
} // namespace OHOS::Ace::NG
