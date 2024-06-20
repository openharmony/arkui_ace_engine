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
    const RefPtr<TouchEventTarget>& current, const std::vector<RefPtr<TouchEventTarget>>& others)
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
    const RefPtr<TouchEventTarget>& target)
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
    currentRecognizer->SetRecognizer(AceType::DynamicCast<NG::NGGestureRecognizer>(target));
    return recognizerObj;
}

} // namespace OHOS::Ace::Framework
