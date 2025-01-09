/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_linear_indicator_controller.h"

#include "base/utils/utils.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "core/components_ng/pattern/linear_indicator/linear_indicator_theme.h"

namespace OHOS::Ace::Framework {

void JSLinearIndicatorController::JSBind(BindingTarget globalObj)
{
    JSClass<JSLinearIndicatorController>::Declare("LinearIndicatorController");
    JSClass<JSLinearIndicatorController>::CustomMethod("setProgress", &JSLinearIndicatorController::SetProgress);
    JSClass<JSLinearIndicatorController>::CustomMethod("start", &JSLinearIndicatorController::Start);
    JSClass<JSLinearIndicatorController>::CustomMethod("pause", &JSLinearIndicatorController::Pause);
    JSClass<JSLinearIndicatorController>::CustomMethod("stop", &JSLinearIndicatorController::Stop);
    JSClass<JSLinearIndicatorController>::Bind(
        globalObj, JSLinearIndicatorController::Constructor, JSLinearIndicatorController::Destructor);
}

void JSLinearIndicatorController::Constructor(const JSCallbackInfo& args)
{
    auto linearIndicatorController = Referenced::MakeRefPtr<JSLinearIndicatorController>();
    linearIndicatorController->IncRefCount();
    args.SetReturnValue(Referenced::RawPtr(linearIndicatorController));
}

void JSLinearIndicatorController::Destructor(JSLinearIndicatorController* linearIndicatorController)
{
    if (linearIndicatorController) {
        linearIndicatorController->DecRefCount();
    }
}

void JSLinearIndicatorController::SetProgress(const JSCallbackInfo& args)
{
    if (args.Length() < 2) {
        return;
    }
    auto arg0 = args[0];
    auto arg1 = args[1];
    int32_t index = 0;
    float value = .0f;
    if (arg0->IsUndefined() || arg0->IsNull() || (!ConvertFromJSValue(arg0, index))) {
        index = 0;
    }
    if (arg1->IsUndefined() || arg1->IsNull() ||(!ConvertFromJSValue(arg1, value))) {
        value = .0f;
    }
    if (linearIndicatorController_) {
        linearIndicatorController_->SetProgress(index, value);
    }
}

void JSLinearIndicatorController::Start(const JSCallbackInfo& args)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetThemeManager()->GetTheme<NG::LinearIndicatorTheme>();
    CHECK_NULL_VOID(theme);
    int32_t defaultDuration = theme->GetDefaultDurationTime();
    int32_t defaultInterval = theme->GetDefaultIntervalTime();
    int32_t duration = defaultDuration;
    int32_t interval = defaultInterval;
    if (args.Length() > 0) {
        auto arg0 = args[0];
        if (arg0->IsObject()) {
            JSRef<JSObject> obj = JSRef<JSObject>::Cast(arg0);
            if (!ConvertFromJSValue(obj->GetProperty("duration"), duration)) {
                duration = defaultDuration;
            }
            if (!ConvertFromJSValue(obj->GetProperty("interval"), interval)) {
                interval = defaultInterval;
            }
        }
    }
    if (linearIndicatorController_) {
        linearIndicatorController_->Start(duration, interval);
    }
}

void JSLinearIndicatorController::Pause(const JSCallbackInfo& args)
{
    if (linearIndicatorController_) {
        linearIndicatorController_->Pause();
    }
}

void JSLinearIndicatorController::Stop(const JSCallbackInfo& args)
{
    if (linearIndicatorController_) {
        linearIndicatorController_->Stop();
    }
}

} // namespace OHOS::Ace::Framework
