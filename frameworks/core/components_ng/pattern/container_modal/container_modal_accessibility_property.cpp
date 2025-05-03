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

#include "core/components_ng/pattern/container_modal/container_modal_accessibility_property.h"

#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"

namespace OHOS::Ace::NG {
std::string ContainerModalAccessibilityProperty::GetText() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, "");
    auto containerModalPattern = frameNode->GetPattern<ContainerModalPattern>();
    CHECK_NULL_RETURN(containerModalPattern, "");
    auto textLabel = containerModalPattern->GetAppLabel();
    if (!textLabel.empty()) {
        return textLabel;
    }

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, "");
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, "");
    auto themeConstants = themeManager->GetThemeConstants();
    CHECK_NULL_RETURN(themeConstants, "");
    auto appLabelId = pipeline->GetWindowManager()->GetAppLabelId();
    return themeConstants->GetString(appLabelId);
}
} // namespace OHOS::Ace::NG
