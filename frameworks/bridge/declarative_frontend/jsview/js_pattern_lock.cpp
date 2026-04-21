/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_pattern_lock.h"

#include "bridge/declarative_frontend/jsview/js_pattern_lock_controller_binding.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/patternlock/patternlock_model_ng.h"
#include "core/components_v2/pattern_lock/pattern_lock_component.h"

namespace OHOS::Ace {

const std::vector<V2::PatternLockChallengeResult> CHALLENGE_RESULT = { V2::PatternLockChallengeResult::CORRECT,
    V2::PatternLockChallengeResult::WRONG };
}

namespace OHOS::Ace::Framework {

void JSPatternLockControllerBinding::Reset(const JSCallbackInfo& args)
{
    if (controller_) {
        controller_->Reset();
    }
}

void JSPatternLockControllerBinding::SetChallengeResult(const JSCallbackInfo& args)
{
    if (controller_) {
        if (!args[0]->IsNumber()) {
            return;
        }
        int32_t value = args[0]->ToNumber<int32_t>();
        if (value >= 1 && value <= static_cast<int32_t>(CHALLENGE_RESULT.size())) {
            controller_->SetChallengeResult(CHALLENGE_RESULT[value - 1]);
        }
    }
}

void JSPatternLockControllerBinding::JSBind(BindingTarget globalObj)
{
    JSClass<JSPatternLockController>::Declare("PatternLockController");
    JSClass<JSPatternLockController>::CustomMethod("reset", &JSPatternLockControllerBinding::Reset);
    JSClass<JSPatternLockController>::CustomMethod(
        "setChallengeResult", &JSPatternLockControllerBinding::SetChallengeResult);
    JSClass<JSPatternLockController>::Bind(
        globalObj, JSPatternLockControllerBinding::Constructor, JSPatternLockControllerBinding::Destructor);
}

void JSPatternLockControllerBinding::Constructor(const JSCallbackInfo& args)
{
    auto controller = Referenced::MakeRefPtr<JSPatternLockController>();
    controller->IncRefCount();
    args.SetReturnValue(Referenced::RawPtr(controller));
}
void JSPatternLockControllerBinding::Destructor(JSPatternLockController* controller)
{
    if (controller != nullptr) {
        controller->DecRefCount();
    }
}
} // namespace OHOS::Ace::Framework
