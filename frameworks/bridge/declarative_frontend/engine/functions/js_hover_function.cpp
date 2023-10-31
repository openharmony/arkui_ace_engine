/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/engine/functions/js_hover_function.h"

namespace OHOS::Ace::Framework {
void JsHoverFunction::HoverExecute(bool isHover, HoverInfo& hoverInfo)
{
    JSRef<JSVal> isHoverParam = JSRef<JSVal>::Make(ToJSValue(isHover));

    JSRef<JSObjTemplate> objectTemplate = JSRef<JSObjTemplate>::New();
    objectTemplate->SetInternalFieldCount(1);
    JSRef<JSObject> hoverObj = objectTemplate->NewInstance();
    hoverObj->SetPropertyObject("stopPropagation", JSRef<JSFunc>::New<FunctionCallback>(JsStopPropagation));
    hoverObj->SetProperty<double>(
        "timestamp", static_cast<double>(hoverInfo.GetTimeStamp().time_since_epoch().count()));
    hoverObj->SetProperty<double>("source", static_cast<int32_t>(hoverInfo.GetSourceDevice()));
    auto target = CreateEventTargetObject(hoverInfo);
    hoverObj->SetPropertyObject("target", target);
    hoverObj->Wrap<HoverInfo>(&hoverInfo);
    JSRef<JSVal> hoverVal = JSRef<JSObject>::Cast(hoverObj);
    JSRef<JSVal> params[] = { isHoverParam, hoverVal };
    JsFunction::ExecuteJS((sizeof(params) / sizeof(params[0])), params);
}

} // namespace OHOS::Ace::Framework
