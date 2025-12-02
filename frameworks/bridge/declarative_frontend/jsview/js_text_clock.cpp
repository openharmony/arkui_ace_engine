/*
 * Copyright (c) 2021-2025 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_text_clock_controller_binding.h"

namespace OHOS::Ace::Framework {
void JSTextClockController::Start()
{
    ContainerScope scope(instanceId_);
    if (!controller_.empty()) {
        for (auto& i : controller_) {
            i->Start();
        }
    }
}

void JSTextClockController::Stop()
{
    ContainerScope scope(instanceId_);
    if (!controller_.empty()) {
        for (auto& i : controller_) {
            i->Stop();
        }
    }
}

void JSTextClockController::removeController(const RefPtr<TextClockController>& controller)
{
    for (auto it = controller_.begin(); it != controller_.end(); it++) {
        if (controller == *it) {
            controller_.erase(it);
            break;
        }
    }
}

void JSTextClockControllerBinding::JSBind(BindingTarget globalObj)
{
    JSClass<JSTextClockController>::Declare("TextClockController");
    JSClass<JSTextClockController>::Method("start", &JSTextClockController::Start);
    JSClass<JSTextClockController>::Method("stop", &JSTextClockController::Stop);
    JSClass<JSTextClockController>::Bind(
        globalObj, JSTextClockControllerBinding::Constructor, JSTextClockControllerBinding::Destructor);
}

void JSTextClockControllerBinding::Constructor(const JSCallbackInfo& args)
{
    auto scroller = Referenced::MakeRefPtr<JSTextClockController>();
    scroller->IncRefCount();
    args.SetReturnValue(Referenced::RawPtr(scroller));
}

void JSTextClockControllerBinding::Destructor(JSTextClockController* scroller)
{
    if (scroller != nullptr) {
        scroller->DecRefCount();
    }
}
} // namespace OHOS::Ace::Framework
