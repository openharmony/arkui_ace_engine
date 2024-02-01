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

#include "bridge/declarative_frontend/jsview/js_calendar_controller.h"

#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/calendar_controller_model_impl.h"
#include "core/components_ng/pattern/calendar/calendar_controller_model_ng.h"

namespace OHOS::Ace {
std::unique_ptr<CalendarControllerModel> CalendarControllerModel::instance_ = nullptr;
std::mutex CalendarControllerModel::mutex_;

CalendarControllerModel* CalendarControllerModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::CalendarControllerModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::CalendarControllerModelNG());
            } else {
                instance_.reset(new Framework::CalendarControllerModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
void JSCalendarController::JSBind(BindingTarget globalObj)
{
    JSClass<JSCalendarController>::Declare("CalendarController");
    JSClass<JSCalendarController>::CustomMethod("backToToday", &JSCalendarController::BackToToday);
    JSClass<JSCalendarController>::CustomMethod("goTo", &JSCalendarController::GoTo);
    JSClass<JSCalendarController>::Bind(globalObj,
        JSCalendarController::Constructor, JSCalendarController::Destructor);
}

void JSCalendarController::Constructor(const JSCallbackInfo& args)
{
    auto jsCalendarController = Referenced::MakeRefPtr<JSCalendarController>();
    auto controller = CalendarControllerModel::GetInstance()->GetController();
    jsCalendarController->SetController(controller);
    jsCalendarController->IncRefCount();
    args.SetReturnValue(Referenced::RawPtr(jsCalendarController));
}

void JSCalendarController::Destructor(JSCalendarController* controller)
{
    if (controller != nullptr) {
        controller->DecRefCount();
    }
}

void JSCalendarController::BackToToday(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    CalendarControllerModel::GetInstance()->BackToToday(controller_);
}

void JSCalendarController::GoTo(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info.Length() != 1 || !info[0]->IsObject()) {
        return;
    }
    auto obj = JSRef<JSObject>::Cast(info[0]);
    int32_t year = 0;
    int32_t month = 0;
    int32_t day = 0;
    ConvertFromJSValue(obj->GetProperty("year"), year);
    ConvertFromJSValue(obj->GetProperty("month"), month);
    ConvertFromJSValue(obj->GetProperty("day"), day);
    CalendarControllerModel::GetInstance()->GoTo(year, month, day, controller_);
}
} // namespace OHOS::Ace::Framework