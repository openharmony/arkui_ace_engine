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

#include "bridge/declarative_frontend/jsview/js_scrollable.h"

#include "bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::Framework {
namespace {
const int32_t EDGE_EFFECT_PARAM_COUNT = 2;
}

EdgeEffect JSScrollable::ParseEdgeEffect(const JSCallbackInfo& info, EdgeEffect defaultValue)
{
    if (info.Length() < 1) {
        return defaultValue;
    }
    auto edgeEffect = static_cast<int32_t>(defaultValue);
    if (info[0]->IsNull() || info[0]->IsUndefined() || !JSViewAbstract::ParseJsInt32(info[0], edgeEffect) ||
        edgeEffect < static_cast<int32_t>(EdgeEffect::SPRING) || edgeEffect > static_cast<int32_t>(EdgeEffect::NONE)) {
        edgeEffect = static_cast<int32_t>(defaultValue);
    }
    return static_cast<EdgeEffect>(edgeEffect);
}

bool JSScrollable::ParseAlwaysEnable(const JSCallbackInfo& info, bool defaultValue)
{
    auto alwaysEnabled = defaultValue;
    if (info.Length() == EDGE_EFFECT_PARAM_COUNT) {
        auto paramObject = JSRef<JSObject>::Cast(info[1]);
        if (!(info[1]->IsNull() || info[1]->IsUndefined())) {
            JSRef<JSVal> alwaysEnabledParam = paramObject->GetProperty("alwaysEnabled");
            alwaysEnabled = alwaysEnabledParam->IsBoolean() ? alwaysEnabledParam->ToBoolean() : false;
        }
    }
    return alwaysEnabled;
}
} // namespace OHOS::Ace::Framework
