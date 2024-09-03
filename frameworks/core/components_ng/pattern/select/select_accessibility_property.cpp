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

#include "core/components_ng/pattern/select/select_accessibility_property.h"

#include "core/components_ng/pattern/select/select_pattern.h"

namespace OHOS::Ace::NG {
int32_t SelectAccessibilityProperty::GetCurrentIndex() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, -1);
    auto selectPattern = frameNode->GetPattern<SelectPattern>();
    CHECK_NULL_RETURN(selectPattern, -1);
    return selectPattern->GetSelected();
}

int32_t SelectAccessibilityProperty::GetBeginIndex() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, -1);
    auto selectPattern = frameNode->GetPattern<SelectPattern>();
    CHECK_NULL_RETURN(selectPattern, -1);
    auto options = selectPattern->GetOptions();
    if (options.empty()) {
        return -1;
    }
    return 0;
}

int32_t SelectAccessibilityProperty::GetEndIndex() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, -1);
    auto selectPattern = frameNode->GetPattern<SelectPattern>();
    CHECK_NULL_RETURN(selectPattern, -1);
    auto options = selectPattern->GetOptions();
    if (options.empty()) {
        return -1;
    }
    return static_cast<int32_t>(options.size()) - 1;
}

std::string SelectAccessibilityProperty::GetText() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, "");
    auto selectPattern = frameNode->GetPattern<SelectPattern>();
    CHECK_NULL_RETURN(selectPattern, "");
    return selectPattern->GetValue();
}

int32_t SelectAccessibilityProperty::GetCollectionItemCounts() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, -1);
    auto selectPattern = frameNode->GetPattern<SelectPattern>();
    CHECK_NULL_RETURN(selectPattern, -1);
    auto options = selectPattern->GetOptions();
    if (options.empty()) {
        return -1;
    }
    return options.size();
}
} // namespace OHOS::Ace::NG
