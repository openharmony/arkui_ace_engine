/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_calendar_controller_ng.h"

#include "bridge/declarative_frontend/jsview/js_view_common_def.h"

namespace OHOS::Ace::Framework {

void JSCalendarControllerNg::JSBind(BindingTarget globalObj)
{
    JSClass<JSCalendarControllerNg>::Declare("CalendarController");
    JSClass<JSCalendarControllerNg>::CustomMethod("backToToday", &JSCalendarControllerNg::BackToToday);
    JSClass<JSCalendarControllerNg>::CustomMethod("goTo", &JSCalendarControllerNg::GoTo);
    JSClass<JSCalendarControllerNg>::Bind(globalObj, JSCalendarControllerNg::Constructor, JSCalendarControllerNg::Destructor);
}

void JSCalendarControllerNg::Constructor(const JSCallbackInfo& args)
{
    auto jsCalendarController = Referenced::MakeRefPtr<JSCalendarControllerNg>();
    jsCalendarController->IncRefCount();
    args.SetReturnValue(Referenced::RawPtr(jsCalendarController));
}

void JSCalendarControllerNg::Destructor(JSCalendarControllerNg* controller)
{
    if (controller != nullptr) {
        controller->DecRefCount();
    }
}

void JSCalendarControllerNg::BackToToday(const JSCallbackInfo& args)
{
    if (controller_ != nullptr) {
    }
}

void JSCalendarControllerNg::GoTo(const JSCallbackInfo& info)
{
    if (info.Length() != 1 || !info[0]->IsObject() || !controller_) {
        return;
    }

    auto obj = JSRef<JSObject>::Cast(info[0]);
    int32_t year = 0;
    int32_t month = 0;
    int32_t day = 0;
    ConvertFromJSValue(obj->GetProperty("year"), year);
    ConvertFromJSValue(obj->GetProperty("month"), month);
    ConvertFromJSValue(obj->GetProperty("day"), day);
}

} // namespace OHOS::Ace::Framework