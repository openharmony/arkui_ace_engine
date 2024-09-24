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

#include "frameworks/bridge/declarative_frontend/engine/functions/js_should_built_in_recognizer_parallel_with_function.h"

#include "core/components_ng/gestures/recognizers/pan_recognizer.h"

namespace OHOS::Ace::Framework {

RefPtr<NG::NGGestureRecognizer> JsShouldBuiltInRecognizerParallelWithFunction::Execute(
    const RefPtr<NG::NGGestureRecognizer>& current, const std::vector<RefPtr<NG::NGGestureRecognizer>>& others)
{
    CHECK_NULL_RETURN(current, nullptr);
    auto currentObj = CreateRecognizerObject(current);
    JSRef<JSArray> othersArr = JSRef<JSArray>::New();
    uint32_t idx = 0;
    for (const auto& item : others) {
        auto othersObj = CreateRecognizerObject(item);
        othersArr->SetValueAt(idx++, othersObj);
    }
    int32_t paramCount = 2;
    JSRef<JSVal> params[paramCount];
    params[0] = currentObj;
    params[1] = othersArr;
    auto jsValue = JsFunction::ExecuteJS(paramCount, params);
    if (!jsValue->IsObject()) {
        return nullptr;
    }
    RefPtr<NG::NGGestureRecognizer> returnValue = nullptr;
    auto jsObj = JSRef<JSObject>::Cast(jsValue);
    returnValue = Referenced::Claim(jsObj->Unwrap<JSGestureRecognizer>())->GetRecognizer().Upgrade();
    return returnValue;
}

JSRef<JSObject> JsShouldBuiltInRecognizerParallelWithFunction::CreateRecognizerObject(
    const RefPtr<NG::NGGestureRecognizer>& target)
{
    auto panRecognizer = AceType::DynamicCast<NG::PanRecognizer>(target);
    if (panRecognizer) {
        JSRef<JSObject> recognizerObj = JSClass<JSPanRecognizer>::NewInstance();
        auto currentRecognizer = Referenced::Claim(recognizerObj->Unwrap<JSPanRecognizer>());
        currentRecognizer->SetRecognizer(panRecognizer);
        currentRecognizer->SetPanGestureOptions(
            panRecognizer->GetFingers(), panRecognizer->GetDistance(), panRecognizer->GetDirection());
        return recognizerObj;
    }
    JSRef<JSObject> recognizerObj = JSClass<JSGestureRecognizer>::NewInstance();
    auto currentRecognizer = Referenced::Claim(recognizerObj->Unwrap<JSGestureRecognizer>());
    currentRecognizer->SetRecognizer(target);
    return recognizerObj;
}

void JSEventTargetInfo::JSBind(BindingTarget globalObj)
{
    JSClass<JSEventTargetInfo>::Declare("EventTargetInfo");
    JSClass<JSEventTargetInfo>::CustomMethod("getId", &JSEventTargetInfo::GetInspectorId);
    JSClass<JSEventTargetInfo>::Bind(globalObj, &JSEventTargetInfo::Constructor, &JSEventTargetInfo::Destructor);
}

void JSScrollableTargetInfo::JSBind(BindingTarget globalObj)
{
    JSClass<JSScrollableTargetInfo>::Declare("ScrollableTargetInfo");
    JSClass<JSScrollableTargetInfo>::CustomMethod("isBegin", &JSScrollableTargetInfo::IsBegin);
    JSClass<JSScrollableTargetInfo>::CustomMethod("isEnd", &JSScrollableTargetInfo::IsEnd);
    JSClass<JSScrollableTargetInfo>::CustomMethod("getId", &JSEventTargetInfo::GetInspectorId);
    JSClass<JSScrollableTargetInfo>::Inherit<JSEventTargetInfo>();
    JSClass<JSScrollableTargetInfo>::Bind(
        globalObj, &JSScrollableTargetInfo::Constructor, &JSScrollableTargetInfo::Destructor);
}

void JSGestureRecognizer::JSBind(BindingTarget globalObj)
{
    JSClass<JSGestureRecognizer>::Declare("GestureRecognizer");
    JSClass<JSGestureRecognizer>::CustomMethod("getTag", &JSGestureRecognizer::GetTag);
    JSClass<JSGestureRecognizer>::CustomMethod("getType", &JSGestureRecognizer::GetType);
    JSClass<JSGestureRecognizer>::CustomMethod("isBuiltIn", &JSGestureRecognizer::IsBuiltInRecognizer);
    JSClass<JSGestureRecognizer>::CustomMethod("setEnabled", &JSGestureRecognizer::SetEnabled);
    JSClass<JSGestureRecognizer>::CustomMethod("isEnabled", &JSGestureRecognizer::IsEnabled);
    JSClass<JSGestureRecognizer>::CustomMethod("getEventTargetInfo", &JSGestureRecognizer::GetEventTargetInfo);
    JSClass<JSGestureRecognizer>::CustomMethod("getState", &JSGestureRecognizer::GetRefereeState);
    JSClass<JSGestureRecognizer>::CustomMethod("isValid", &JSGestureRecognizer::IsValid);
    JSClass<JSGestureRecognizer>::Bind(
        globalObj, &JSGestureRecognizer::Constructor, &JSGestureRecognizer::Destructor);
}

void JSPanRecognizer::JSBind(BindingTarget globalObj)
{
    JSClass<JSPanRecognizer>::Declare("PanRecognizer");
    JSClass<JSPanRecognizer>::CustomMethod("getTag", &JSGestureRecognizer::GetTag);
    JSClass<JSPanRecognizer>::CustomMethod("getType", &JSGestureRecognizer::GetType);
    JSClass<JSPanRecognizer>::CustomMethod("isBuiltIn", &JSGestureRecognizer::IsBuiltInRecognizer);
    JSClass<JSPanRecognizer>::CustomMethod("setEnabled", &JSGestureRecognizer::SetEnabled);
    JSClass<JSPanRecognizer>::CustomMethod("isEnabled", &JSGestureRecognizer::IsEnabled);
    JSClass<JSPanRecognizer>::CustomMethod("getEventTargetInfo", &JSGestureRecognizer::GetEventTargetInfo);
    JSClass<JSPanRecognizer>::CustomMethod("getState", &JSGestureRecognizer::GetRefereeState);
    JSClass<JSPanRecognizer>::CustomMethod("getPanGestureOptions", &JSPanRecognizer::GetPanGestureOptions);
    JSClass<JSPanRecognizer>::CustomMethod("isValid", &JSGestureRecognizer::IsValid);
    JSClass<JSPanRecognizer>::Inherit<JSGestureRecognizer>();
    JSClass<JSPanRecognizer>::Bind(globalObj, &JSPanRecognizer::Constructor, &JSPanRecognizer::Destructor);
}

} // namespace OHOS::Ace::Framework
