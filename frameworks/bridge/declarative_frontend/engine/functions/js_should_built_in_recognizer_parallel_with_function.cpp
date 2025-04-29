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
        currentRecognizer->Update(panRecognizer);
        return recognizerObj;
    }
    auto pinchRecognizer = AceType::DynamicCast<NG::PinchRecognizer>(target);
    if (pinchRecognizer) {
        JSRef<JSObject> recognizerObj = JSClass<JSPinchRecognizer>::NewInstance();
        auto currentRecognizer = Referenced::Claim(recognizerObj->Unwrap<JSPinchRecognizer>());
        currentRecognizer->Update(pinchRecognizer);
        return recognizerObj;
    }
    auto tapRecognizer = AceType::DynamicCast<NG::ClickRecognizer>(target);
    if (tapRecognizer) {
        JSRef<JSObject> recognizerObj = JSClass<JSTapRecognizer>::NewInstance();
        auto currentRecognizer = Referenced::Claim(recognizerObj->Unwrap<JSTapRecognizer>());
        currentRecognizer->Update(tapRecognizer);
        return recognizerObj;
    }
    auto longPressRecognizer = AceType::DynamicCast<NG::LongPressRecognizer>(target);
    if (longPressRecognizer) {
        JSRef<JSObject> recognizerObj = JSClass<JSLongPressRecognizer>::NewInstance();
        auto currentRecognizer = Referenced::Claim(recognizerObj->Unwrap<JSLongPressRecognizer>());
        currentRecognizer->Update(longPressRecognizer);
        return recognizerObj;
    }
    auto rotationRecognizer = AceType::DynamicCast<NG::RotationRecognizer>(target);
    if (rotationRecognizer) {
        JSRef<JSObject> recognizerObj = JSClass<JSRotationRecognizer>::NewInstance();
        auto currentRecognizer = Referenced::Claim(recognizerObj->Unwrap<JSRotationRecognizer>());
        currentRecognizer->Update(rotationRecognizer);
        return recognizerObj;
    }
    auto swipeRecognizer = AceType::DynamicCast<NG::SwipeRecognizer>(target);
    if (swipeRecognizer) {
        JSRef<JSObject> recognizerObj = JSClass<JSSwipeRecognizer>::NewInstance();
        auto currentRecognizer = Referenced::Claim(recognizerObj->Unwrap<JSSwipeRecognizer>());
        currentRecognizer->Update(swipeRecognizer);
        return recognizerObj;
    }
    JSRef<JSObject> recognizerObj = JSClass<JSGestureRecognizer>::NewInstance();
    auto currentRecognizer = Referenced::Claim(recognizerObj->Unwrap<JSGestureRecognizer>());
    currentRecognizer->Update(target);
    return recognizerObj;
}

} // namespace OHOS::Ace::Framework
