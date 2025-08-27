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

#include "core/components_ng/pattern/scrollable/scrollable_layout_property.h"

namespace OHOS::Ace::NG {

void ScrollableLayoutProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    LayoutProperty::ToJsonValue(json, filter);
    if (filter.IsFastFilter()) {
        return;
    }
    json->PutExtAttr("contentStartOffset", std::to_string(propContentStartOffset_.value_or(0)).c_str(), filter);
    json->PutExtAttr("contentEndOffset", std::to_string(propContentEndOffset_.value_or(0)).c_str(), filter);
}

} // namespace OHOS::Ace::NG
