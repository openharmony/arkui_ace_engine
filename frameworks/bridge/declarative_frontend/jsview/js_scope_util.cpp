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

#include "frameworks/bridge/declarative_frontend/jsview/js_scope_util.h"

#include "base/memory/referenced.h"
#include "frameworks/core/common/container.h"

namespace OHOS::Ace::Framework {
static thread_local std::vector<int32_t> restoreInstanceIds_;

JSScopeUtil::JSScopeUtil() {}

void JSScopeUtil::JSBind(BindingTarget globalObj)
{
    JSClass<JSScopeUtil>::Declare("__JSScopeUtil__");
    JSClass<JSScopeUtil>::StaticMethod("syncInstanceId", &JSScopeUtil::SyncInstanceId);
    JSClass<JSScopeUtil>::StaticMethod("restoreInstanceId", &JSScopeUtil::RestoreInstanceId);
    JSClass<JSScopeUtil>::Bind(globalObj);
}

void JSScopeUtil::SyncInstanceId(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    if (!info[0]->IsNumber()) {
        return;
    }

    restoreInstanceIds_.emplace_back(Container::CurrentId());
    int32_t instanceId = info[0]->ToNumber<int32_t>();
    ContainerScope::UpdateCurrent(instanceId);
}

void JSScopeUtil::RestoreInstanceId(const JSCallbackInfo& info)
{
    if (restoreInstanceIds_.empty()) {
        ContainerScope::UpdateCurrent(INSTANCE_ID_UNDEFINED);
        return;
    }
    ContainerScope::UpdateCurrent(restoreInstanceIds_.back());
    restoreInstanceIds_.pop_back();
}
} // namespace OHOS::Ace::Framework