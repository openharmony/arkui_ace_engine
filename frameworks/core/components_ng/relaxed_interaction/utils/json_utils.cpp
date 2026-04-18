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

#include "core/components_ng/relaxed_interaction/utils/json_utils.h"

#include <cmath>

#include "base/log/log_wrapper.h"

namespace OHOS::Ace::NG {

bool JsonUtils::IsUint(const std::unique_ptr<JsonValue>& json)
{
    return IsUint(json.get());
}

bool JsonUtils::IsUint(const JsonValue* json)
{
    if (!json || !json->IsNumber()) {
        return false;
    }

    double value = json->GetDouble();
    return value >= 0.0 && std::fabs(value - std::floor(value)) < 1e-10;
}

} // namespace OHOS::Ace::NG