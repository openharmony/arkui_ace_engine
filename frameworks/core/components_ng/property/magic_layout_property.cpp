/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/property/magic_layout_property.h"

#include "core/common/ace_application_info.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {

void MagicItemProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    json->PutExtAttr("layoutWeight", propLayoutWeight.value_or(0), filter);
    auto context = PipelineBase::GetCurrentContext();
    // add version protection, null as default start from API 10 or higher
    if (context && context->GetMinPlatformVersion() > static_cast<int32_t>(PlatformVersion::VERSION_NINE)) {
        if (propAspectRatio.has_value()) {
            json->PutExtAttr("aspectRatio",
                round(static_cast<double>(propAspectRatio.value()) * 100) / 100, filter);
        } else {
            json->PutExtAttr("aspectRatio", "", filter);
        }
    } else {
        json->PutExtAttr("aspectRatio",
            round(static_cast<double>(propAspectRatio.value_or(0.0)) * 100) / 100, filter);
    }
}

} // namespace OHOS::Ace::NG
