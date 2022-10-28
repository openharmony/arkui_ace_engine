/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/progress/progress_paint_property.h"

#include "base/geometry/dimension.h"
#include "core/common/container.h"
#include "core/components/progress/progress_theme.h"
#include "core/components_ng/pattern/progress/progress_date.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

const double PROGRSS_MAX_VALUE = 100.f;

void ProgressPaintProperty::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    PaintProperty::ToJsonValue(json);

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto progressTheme = pipeline->GetTheme<ProgressTheme>();
    CHECK_NULL_VOID(progressTheme);

    json->Put("maxVlaue", std::to_string(GetMaxValue().value_or(PROGRSS_MAX_VALUE)).c_str());
    json->Put("vlaue", std::to_string(GetValue().value_or(0.f)).c_str());
    json->Put("scaleCount", std::to_string(GetScaleCount().value_or(progressTheme->GetScaleNumber())).c_str());
    json->Put("scaleWidth", (GetScaleWidth().value_or(progressTheme->GetScaleWidth()).ToString()).c_str());
    json->Put("color", (GetColor().value_or(progressTheme->GetTrackSelectedColor())).ColorToString().c_str());
    json->Put(
        "backgroundColor", (GetBackgroundColor().value_or(progressTheme->GetTrackBgColor())).ColorToString().c_str());
}

} // namespace OHOS::Ace::NG
