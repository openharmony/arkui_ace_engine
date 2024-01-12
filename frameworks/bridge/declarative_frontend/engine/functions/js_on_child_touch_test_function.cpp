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

#include "frameworks/bridge/declarative_frontend/engine/functions/js_on_child_touch_test_function.h"

namespace OHOS::Ace::Framework {
void JsOnChildTouchTestFunction::Execute()
{
    JsFunction::Execute();
}

JSRef<JSVal> JsOnChildTouchTestFunction::Execute(const std::vector<NG::TouchTestInfo>& touchInfo)
{
    JSRef<JSArray> infoArray = JSRef<JSArray>::New();
    for (size_t i = 0; i < touchInfo.size(); i++) {
        JSRef<JSVal> info = JSRef<JSObject>::Cast(CreateTouchTestInfo(touchInfo[i]));
        infoArray->SetValueAt(i, info);
    }
    JSRef<JSVal> param = infoArray;
    return JsFunction::ExecuteJS(1, &param);
}

JSRef<JSObject> JsOnChildTouchTestFunction::CreateTouchTestInfo(const NG::TouchTestInfo& info)
{
    JSRef<JSObject> infoObj = JSRef<JSObject>::New();
    infoObj->SetProperty<double>("windowX", PipelineBase::Px2VpWithCurrentDensity(info.windowPoint.GetX()));
    infoObj->SetProperty<double>("windowY", PipelineBase::Px2VpWithCurrentDensity(info.windowPoint.GetY()));
    infoObj->SetProperty<double>("parentX", PipelineBase::Px2VpWithCurrentDensity(info.currentCmpPoint.GetX()));
    infoObj->SetProperty<double>("parentY", PipelineBase::Px2VpWithCurrentDensity(info.currentCmpPoint.GetY()));
    infoObj->SetProperty<double>("x", PipelineBase::Px2VpWithCurrentDensity(info.subCmpPoint.GetX()));
    infoObj->SetProperty<double>("y", PipelineBase::Px2VpWithCurrentDensity(info.subCmpPoint.GetY()));
    infoObj->SetPropertyObject("rect", CreateRectangle(info.subRect));
    infoObj->SetProperty<std::string>("id", info.id);
    return infoObj;
}

JSRef<JSObject> JsOnChildTouchTestFunction::CreateRectangle(const NG::RectF& info)
{
    JSRef<JSObject> rectangleObj = JSRef<JSObject>::New();
    rectangleObj->SetProperty<double>("x", PipelineBase::Px2VpWithCurrentDensity(info.GetX()));
    rectangleObj->SetProperty<double>("y", PipelineBase::Px2VpWithCurrentDensity(info.GetY()));
    rectangleObj->SetProperty<double>("width", PipelineBase::Px2VpWithCurrentDensity(info.Width()));
    rectangleObj->SetProperty<double>("height", PipelineBase::Px2VpWithCurrentDensity(info.Height()));
    return rectangleObj;
}
} // namespace OHOS::Ace::Framework
