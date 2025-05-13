/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/tabs/tab_content_model_static.h"

#include "core/components_ng/pattern/tabs/tab_content_pattern.h"

namespace OHOS::Ace::NG {
void TabContentModelStatic::SetIndicator(FrameNode* frameNode, const std::optional<IndicatorStyle>& indicatorOpt)
{
    CHECK_NULL_VOID(frameNode);
    auto frameNodePattern = frameNode->GetPattern<TabContentPattern>();
    CHECK_NULL_VOID(frameNodePattern);
    if (indicatorOpt) {
        frameNodePattern->SetIndicatorStyle(indicatorOpt.value());
    } else {
        IndicatorStyle indicator;
        auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_VOID(pipeline);
        RefPtr<TabTheme> tabTheme = pipeline->GetTheme<TabTheme>();
        if (tabTheme) {
            indicator.color = tabTheme->GetActiveIndicatorColor();
            indicator.height = tabTheme->GetActiveIndicatorWidth();
            indicator.marginTop = tabTheme->GetSubTabIndicatorGap();
        }
        frameNodePattern->SetIndicatorStyle(indicator);
    }
}

void TabContentModelStatic::SetLabelStyle(FrameNode* frameNode, const std::optional<LabelStyle>& labelStyleOpt)
{
    CHECK_NULL_VOID(frameNode);
    auto frameNodePattern = frameNode->GetPattern<TabContentPattern>();
    CHECK_NULL_VOID(frameNodePattern);
    frameNodePattern->SetLabelStyle(labelStyleOpt.value_or(LabelStyle()));
}
} // namespace OHOS::Ace::NG
