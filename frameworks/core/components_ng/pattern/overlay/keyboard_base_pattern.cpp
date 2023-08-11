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

#include "core/components_ng/pattern/overlay/keyboard_base_pattern.h"

#include "base/utils/utils.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {
void KeyboardPattern::BeforeCreateLayoutWrapper()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto child = host->GetChildAtIndex(0);
    while (child) {
        // find first framenode, filter SyntaxItem
        auto childFrameNode = AceType::DynamicCast<FrameNode>(child);
        if (childFrameNode) {
            auto layoutProperty = childFrameNode->GetLayoutProperty();
            if (!layoutProperty) {
                break;
            }
            // set custom keyboard view width match parent
            std::optional<CalcLength> height = std::nullopt;
            auto&& layoutConstraint = layoutProperty->GetCalcLayoutConstraint();
            if (layoutConstraint != nullptr && layoutConstraint->selfIdealSize) {
                height = layoutConstraint->selfIdealSize->Height();
            }
            auto dimension = Dimension(1.0f, DimensionUnit::PERCENT);
            layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(dimension), height));
            break;
        }
        child = child->GetChildAtIndex(0);
    }
}
} // namespace OHOS::Ace::NG