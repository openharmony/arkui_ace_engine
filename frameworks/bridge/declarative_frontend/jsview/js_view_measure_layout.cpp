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

#include "bridge/declarative_frontend/jsview/js_view_measure_layout.h"

namespace OHOS::Ace::Framework {

#ifdef USE_ARK_ENGINE

thread_local std::list<RefPtr<NG::LayoutWrapper>> ViewMeasureLayout::measureChildren_;
thread_local std::list<RefPtr<NG::LayoutWrapper>>::iterator ViewMeasureLayout::iterMeasureChildren_;
thread_local std::list<RefPtr<NG::LayoutWrapper>> ViewMeasureLayout::layoutChildren_;
thread_local std::list<RefPtr<NG::LayoutWrapper>>::iterator ViewMeasureLayout::iterLayoutChildren_;
thread_local NG::LayoutConstraintF ViewMeasureLayout::measureDefaultConstraint_;

namespace {

std::unordered_map<std::string, Local<JSValueRef>> ParseJsObject(
    Local<ObjectRef> obj, Local<ArrayRef> names, EcmaVM* vm)
{
    std::unordered_map<std::string, Local<JSValueRef>> jsValue;
    auto length = names->Length(vm);

    for (int i = 0; i < length; i++) {
        auto value = ArrayRef::GetValueAt(vm, names, i);
        if (value->IsString()) {
            auto key = value->ToString(vm)->ToString();
            auto val = obj->Get(vm, value->ToString(vm));
            jsValue.insert({ key, val });
        }
    }

    return jsValue;
}

} // namespace

Local<JSValueRef> ViewMeasureLayout::JSMeasure(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    ACE_SCOPED_TRACE("ViewMeasureLayout::JSMeasure");
    EcmaVM* vm = runtimeCallInfo->GetVM();
    int32_t argc = runtimeCallInfo->GetArgsNumber();
    if (argc != 1) {
        LOGE("The arg is wrong, must have one argument");
        (*iterMeasureChildren_)->Measure(measureDefaultConstraint_);
        iterMeasureChildren_++;
        return panda::JSValueRef::Undefined(vm);
    }

    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    NG::SizeF minSize;
    NG::SizeF maxSize;
    NG::LayoutConstraintF jsConstraint_;
    auto value_ = firstArg->ToObject(vm);
    auto jsValue_ = ParseJsObject(value_, value_->GetOwnPropertyNames(vm), vm);

    minSize.SetWidth(jsValue_.at("minWidth")->ToNumber(vm)->Value());
    minSize.SetHeight(jsValue_.at("minHeight")->ToNumber(vm)->Value());
    maxSize.SetWidth(jsValue_.at("maxWidth")->ToNumber(vm)->Value());
    maxSize.SetHeight(jsValue_.at("maxHeight")->ToNumber(vm)->Value());
    jsConstraint_.minSize = minSize;
    jsConstraint_.maxSize = maxSize;
    (*iterMeasureChildren_)->Measure(jsConstraint_);
    iterMeasureChildren_++;
    return panda::JSValueRef::Undefined(vm);
}

panda::Local<panda::JSValueRef> ViewMeasureLayout::JSLayout(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    ACE_SCOPED_TRACE("ViewMeasureLayout::JSLayout");
    EcmaVM* vm = runtimeCallInfo->GetVM();
    auto jsParams = runtimeCallInfo->GetCallArgRef(0)->ToObject(vm);
    auto names = jsParams->GetOwnPropertyNames(vm);
    if (names->Length(vm) != 2) {
        LOGE("invalid param number for layout");
        (*iterLayoutChildren_)->Layout();
        iterLayoutChildren_++;
        return panda::JSValueRef::Undefined(vm);
    }

    auto first = ParseJsObject(jsParams, names, vm);
    auto posInfo = first.at("position");
    auto second = ParseJsObject(posInfo, posInfo->ToObject(vm)->GetOwnPropertyNames(vm), vm);
    auto xVal = second.at("x")->ToNumber(vm)->Value();
    auto yVal = second.at("y")->ToNumber(vm)->Value();
    (*iterLayoutChildren_)->GetGeometryNode()->SetMarginFrameOffset(NG::OffsetF(xVal, yVal));
    iterLayoutChildren_++;
    return panda::JSValueRef::Undefined(vm);
}

#endif

} // namespace OHOS::Ace::Framework