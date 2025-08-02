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

#include "core/components_ng/pattern/linear_indicator/linear_indicator_layout_property.h"

#include "core/components_ng/pattern/linear_indicator/linear_indicator_theme.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {

LinearIndicatorLayoutProperty::LinearIndicatorLayoutProperty() : LinearLayoutProperty(false) {}

void LinearIndicatorLayoutProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    LayoutProperty::ToJsonValue(json, filter);
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetThemeManager()->GetTheme<NG::LinearIndicatorTheme>();
    CHECK_NULL_VOID(theme);

    auto jsonValue = JsonUtil::Create(true);

    jsonValue->Put("space", GetSpaceValue(theme->GetDefaultSpace()).ToString().c_str());
    jsonValue->Put("strokeWidth", GetStrokeWidthValue(theme->GetDefaultStrokeWidth()).ToString().c_str());
    jsonValue->Put("strokeRadius", GetStrokeRadiusValue(theme->GetDefaultStrokeRadius()).ToString().c_str());
    jsonValue->Put(
        "trackBackgroundColor", GetTrackBackgroundColorValue(theme->GetTrackBackgroundColor()).ColorToString().c_str());
    jsonValue->Put("trackColor", GetTrackColorValue(theme->GetTrackColor()).ColorToString().c_str());
    json->PutExtAttr("indicatorStyle", jsonValue->ToString().c_str(), filter);
    json->PutExtAttr("indicatorLoop", GetLoopValue(theme->GetDefaultLoop()) ? "True" : "False", filter);
    json->PutExtAttr("count", GetProgressCountValue(theme->GetDefaultProgressCount()), filter);
}

} // namespace OHOS::Ace::NG
