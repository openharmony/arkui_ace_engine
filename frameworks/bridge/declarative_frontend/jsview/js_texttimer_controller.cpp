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

#include "frameworks/bridge/declarative_frontend/jsview/js_texttimer_controller.h"

#include <regex>

#include "base/log/ace_scoring_log.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/text_timer_model_impl.h"
#include "core/components/common/layout/constants.h"
#include "core/components/declaration/texttimer/texttimer_declaration.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/texttimer/text_timer_model.h"
#include "core/components_ng/pattern/texttimer/text_timer_model_ng.h"

namespace OHOS::Ace::Framework {

void JSTextTimerController::JSBind(panda::Local<panda::ObjectRef> globalObj)
{
    JSClass<JSTextTimerController>::Declare("TextTimerController");
    JSClass<JSTextTimerController>::CustomMethod("start", &JSTextTimerController::Start);
    JSClass<JSTextTimerController>::CustomMethod("pause", &JSTextTimerController::Pause);
    JSClass<JSTextTimerController>::CustomMethod("reset", &JSTextTimerController::Reset);
    JSClass<JSTextTimerController>::Bind(
        globalObj, JSTextTimerController::Constructor, JSTextTimerController::Destructor);
}

void JSTextTimerController::Constructor(const JSCallbackInfo& info)
{
    auto timerController = Referenced::MakeRefPtr<JSTextTimerController>();
    timerController->IncRefCount();
    info.SetReturnValue(Referenced::RawPtr(timerController));
}

void JSTextTimerController::Destructor(JSTextTimerController* timerController)
{
    if (timerController != nullptr) {
        timerController->DecRefCount();
    }
}

void JSTextTimerController::Start(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (controller_) {
        controller_->Start();
    }
}

void JSTextTimerController::Pause(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (controller_) {
        controller_->Pause();
    }
}

void JSTextTimerController::Reset(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (controller_) {
        controller_->Reset();
    }
}
} // namespace OHOS::Ace::Framework
