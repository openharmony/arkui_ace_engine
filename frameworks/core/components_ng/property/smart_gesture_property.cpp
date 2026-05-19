/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "frameworks/core/components_ng/property/smart_gesture_property.h"
#include "json/json_util.h"
#include "base/json/json_util.h"
#include "core/components_ng/base/inspector_filter.h"

namespace OHOS::Ace::NG {
void SmartGestureProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    if (smartGestureShortcutConfig_.has_value()) {
        auto value = JsonUtil::Create(false);
        value->PutExtAttr("action", static_cast<int32_t>(smartGestureShortcutConfig_->action), filter);
        value->PutExtAttr("enabled", smartGestureShortcutConfig_->enabled, filter);
        value->PutExtAttr("selectable", smartGestureShortcutConfig_->selectable, filter);
        json->Put("smartGestureShortcut", value);
    }
}
} // namespace OHOS::Ace::NG
