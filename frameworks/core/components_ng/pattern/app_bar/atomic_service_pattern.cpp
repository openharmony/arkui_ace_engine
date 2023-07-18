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
#include "core/components_ng/pattern/app_bar/atomic_service_pattern.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/measure_property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void AtomicServicePattern::BeforeCreateLayoutWrapper()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto safeArea = pipeline->GetSafeArea();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    PaddingProperty padding {
        .left = CalcLength(safeArea.left_.Length()),
        .right = CalcLength(safeArea.right_.Length()),
        .top = CalcLength(safeArea.top_.Length()),
        .bottom = CalcLength(safeArea.bottom_.Length()),
    };
    host->GetLayoutProperty()->UpdatePadding(padding);
}

void AtomicServicePattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    host->GetRenderContext()->UpdateBackgroundColor(pipeline->GetAppBgColor());
}
} // namespace OHOS::Ace::NG