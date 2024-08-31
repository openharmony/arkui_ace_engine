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

#include "core/components_ng/pattern/indexer/indexer_accessibility_property.h"

#include "core/components_ng/pattern/indexer/indexer_pattern.h"

namespace OHOS::Ace::NG {
int32_t IndexerAccessibilityProperty::GetCollectionItemCounts() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, 0);
    auto layoutProperty = frameNode->GetLayoutProperty<IndexerLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, 0);
    if (layoutProperty->GetActualArrayValue().has_value()) {
        auto arrayValue = layoutProperty->GetActualArrayValue().value();
        return static_cast<int32_t>(arrayValue.size());
    } else {
        return 0;
    }
}

int32_t IndexerAccessibilityProperty::GetCurrentIndex() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, -1);
    auto pattern = frameNode->GetPattern<IndexerPattern>();
    CHECK_NULL_RETURN(pattern, -1);
    return pattern->GetSelected();
}

int32_t IndexerAccessibilityProperty::GetEndIndex() const
{
    return GetCollectionItemCounts() - 1;
}

std::string IndexerAccessibilityProperty::GetText() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, "");
    auto layoutProperty = frameNode->GetLayoutProperty<IndexerLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, "");
    if (layoutProperty->GetActualArrayValue().has_value()) {
        auto arrayValue = layoutProperty->GetActualArrayValue().value();
        auto selectIndex = GetCurrentIndex();
        if (selectIndex < static_cast<int32_t>(arrayValue.size())) {
            return arrayValue.at(selectIndex);
        }
    }
    return "";
}
} // namespace OHOS::Ace::NG
