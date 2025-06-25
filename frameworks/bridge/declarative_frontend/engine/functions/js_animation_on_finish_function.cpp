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

#include "frameworks/bridge/declarative_frontend/engine/functions/js_animation_on_finish_function.h"

namespace OHOS::Ace::Framework {

void JsAnimationOnFinishFunction::Execute(bool isDebugAnim)
{
    auto vm = jsFunction_->GetEcmaVM();
    panda::TryCatch trycatch(vm);
    if (isDebugAnim) {
        if (jsFunction_->GetHandle().IsEmpty() || !jsFunction_->GetHandle()->IsFunction(vm) || trycatch.HasCaught()) {
            TAG_LOGW(AceLogTag::ACE_ANIMATION,
                "call function handle is empty or not function, empty: %{public}d, hasError: %{public}d",
                jsFunction_->GetHandle().IsEmpty(), trycatch.HasCaught());
        } else {
            TAG_LOGI(AceLogTag::ACE_ANIMATION,
                "call function: %{public}s", jsFunction_->GetHandle()->GetName(vm)->ToString(vm).c_str());
        }
    }
    auto result = ExecuteJS();
    if (isDebugAnim && !result.IsEmpty()) {
        TAG_LOGI(
            AceLogTag::ACE_ANIMATION, "call function result: %{public}s", result->ToString().c_str());
    }
}

} // namespace OHOS::Ace::Framework
