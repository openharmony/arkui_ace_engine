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

#include "frameworks/bridge/declarative_frontend/engine/functions/js_crown_function.h"

namespace OHOS::Ace::Framework {

JSRef<JSObject> JsCrownFunction::createCrownEvent(CrownEventInfo& event)
{
    JSRef<JSObjTemplate> objectTemplate = JSRef<JSObjTemplate>::New();
    objectTemplate->SetInternalFieldCount(1);
    JSRef<JSObject> crownEventObj = objectTemplate->NewInstance();
    crownEventObj->SetProperty<double>("timestamp", static_cast<double>
        (event.GetTimeStamp().time_since_epoch().count()));
    crownEventObj->SetProperty<double>("angularVelocity", static_cast<double>(event.GetAngularVelocity()));
    crownEventObj->SetProperty<double>("degree", static_cast<double>(event.GetDegree()));
    crownEventObj->SetProperty<int32_t>("action", static_cast<int32_t>(event.GetAction()));
    crownEventObj->SetPropertyObject("stopPropagation", JSRef<JSFunc>::New<FunctionCallback>(JsStopPropagation));
    crownEventObj->Wrap<CrownEventInfo>(&event);
    return crownEventObj;
}

void JsCrownFunction::Execute(OHOS::Ace::CrownEventInfo& event)
{
    JSRef<JSVal> param = JSRef<JSVal>::Cast(createCrownEvent(event));
    JsFunction::ExecuteJS(1, &param);
}

JSRef<JSVal> JsCrownFunction::ExecuteWithValue(OHOS::Ace::CrownEventInfo& event)
{
    JSRef<JSVal> param = JSRef<JSVal>::Cast(createCrownEvent(event));
    return JsFunction::ExecuteJS(1, &param);
}

} // namespace OHOS::Ace::Framework