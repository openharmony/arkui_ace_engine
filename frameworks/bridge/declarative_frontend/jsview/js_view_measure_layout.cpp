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

#include "jsnapi.h"

#include "base/geometry/dimension.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "frameworks/core/components_ng/base/frame_node.h"

namespace OHOS::Ace::Framework {

#ifdef USE_ARK_ENGINE

thread_local std::list<RefPtr<NG::LayoutWrapper>> ViewMeasureLayout::measureChildren_;
thread_local std::list<RefPtr<NG::LayoutWrapper>>::iterator ViewMeasureLayout::iterMeasureChildren_;
thread_local std::list<RefPtr<NG::LayoutWrapper>> ViewMeasureLayout::layoutChildren_;
thread_local std::list<RefPtr<NG::LayoutWrapper>>::iterator ViewMeasureLayout::iterLayoutChildren_;
thread_local NG::LayoutConstraintF ViewMeasureLayout::measureDefaultConstraint_;

panda::Local<panda::JSValueRef> ViewMeasureLayout::JSMeasure(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    ACE_SCOPED_TRACE("ViewMeasureLayout::JSMeasure");
    EcmaVM* vm = runtimeCallInfo->GetVM();

    if (iterMeasureChildren_ == measureChildren_.end()) {
        LOGE("Call measure exceed limit");
        return panda::JSValueRef::Undefined(vm);
    }

    auto info = runtimeCallInfo;
    if (info->GetArgsNumber() != 1 || !info->GetCallArgRef(0)->IsObject()) {
        LOGE("JSMeasure arg is wrong");
        (*iterMeasureChildren_)->Measure(measureDefaultConstraint_);
        iterMeasureChildren_++;
        return panda::JSValueRef::Undefined(vm);
    }

    auto jsObject = JsiObject(info->GetCallArgRef(0)->ToObject(vm));
    JSRef<JSObject> sizeObj = JSRef<JSObject>::Make(jsObject);
    JSRef<JSVal> minWidthValue = sizeObj->GetProperty("minWidth");
    CalcDimension minWidth;
    JSRef<JSVal> maxWidthValue = sizeObj->GetProperty("maxWidth");
    CalcDimension maxWidth;
    JSRef<JSVal> minHeightValue = sizeObj->GetProperty("minHeight");
    CalcDimension minHeight;
    JSRef<JSVal> maxHeightValue = sizeObj->GetProperty("maxHeight");
    CalcDimension maxHeight;

    if (JSViewAbstract::ParseJsDimensionVp(minWidthValue, minWidth)) {
        (*iterMeasureChildren_)
            ->GetLayoutProperty()
            ->UpdateCalcMinSize(NG::CalcSize(NG::CalcLength(minWidth), std::nullopt));
    }
    if (JSViewAbstract::ParseJsDimensionVp(maxWidthValue, maxWidth)) {
        (*iterMeasureChildren_)
            ->GetLayoutProperty()
            ->UpdateCalcMaxSize(NG::CalcSize(NG::CalcLength(maxWidth), std::nullopt));
    }
    if (JSViewAbstract::ParseJsDimensionVp(minHeightValue, minHeight)) {
        (*iterMeasureChildren_)
            ->GetLayoutProperty()
            ->UpdateCalcMinSize(NG::CalcSize(std::nullopt, NG::CalcLength(minHeight)));
    }
    if (JSViewAbstract::ParseJsDimensionVp(maxHeightValue, maxHeight)) {
        (*iterMeasureChildren_)
            ->GetLayoutProperty()
            ->UpdateCalcMaxSize(NG::CalcSize(std::nullopt, NG::CalcLength(maxHeight)));
    }
    (*iterMeasureChildren_)->Measure(measureDefaultConstraint_);

    Dimension measureWidth((*iterMeasureChildren_)->GetGeometryNode()->GetFrameRect().Width(), DimensionUnit::PX);
    Dimension measureHeight((*iterMeasureChildren_)->GetGeometryNode()->GetFrameRect().Height(), DimensionUnit::PX);
    Local<ObjectRef> measureResultObject = ObjectRef::New(vm);
    measureResultObject->Set(vm, ToJSValue("width"), ToJSValue(measureWidth.ConvertToVp()));
    measureResultObject->Set(vm, ToJSValue("height"), ToJSValue(measureHeight.ConvertToVp()));

    iterMeasureChildren_++;
    return measureResultObject;
}

panda::Local<panda::JSValueRef> ViewMeasureLayout::JSLayout(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    ACE_SCOPED_TRACE("ViewMeasureLayout::JSLayout");
    EcmaVM* vm = runtimeCallInfo->GetVM();

    if (iterLayoutChildren_ == layoutChildren_.end()) {
        LOGE("Call layout exceed limit");
        return panda::JSValueRef::Undefined(vm);
    }

    auto info = runtimeCallInfo;
    if (info->GetArgsNumber() != 1 || !info->GetCallArgRef(0)->IsObject()) {
        LOGE("JSLayout arg is wrong");
        (*iterLayoutChildren_)->Layout();
        iterLayoutChildren_++;
        return panda::JSValueRef::Undefined(vm);
    }

    auto jsObject = JsiObject(info->GetCallArgRef(0)->ToObject(vm));
    JSRef<JSObject> layoutInfo = JSRef<JSObject>::Make(jsObject);
    JSRef<JSObject> sizeObj = layoutInfo->GetProperty("position");
    JSRef<JSVal> xVal = sizeObj->GetProperty("x");
    JSRef<JSVal> yVal = sizeObj->GetProperty("y");
    CalcDimension dimenX;
    CalcDimension dimenY;
    auto xResult = JSViewAbstract::ParseJsDimensionVp(xVal, dimenX);
    auto yResult = JSViewAbstract::ParseJsDimensionVp(yVal, dimenY);
    if (!(xResult || yResult)) {
        LOGE("the position prop is illegal");
    } else {
        (*iterLayoutChildren_)->GetGeometryNode()->SetFrameOffset({ dimenX.ConvertToPx(), dimenY.ConvertToPx() });
    }
    (*iterLayoutChildren_)->Layout();
    iterLayoutChildren_++;

    return panda::JSValueRef::Undefined(vm);
}

panda::Local<panda::JSValueRef> ViewMeasureLayout::JSPlaceChildren(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    ACE_SCOPED_TRACE("ViewMeasureLayout::JSPlaceChildren");
    EcmaVM* vm = runtimeCallInfo->GetVM();

    if (iterLayoutChildren_ == layoutChildren_.end()) {
        LOGE("Call layout exceed limit");
        return panda::JSValueRef::Undefined(vm);
    }

    auto info = runtimeCallInfo;
    if (info->GetArgsNumber() != 1 || !info->GetCallArgRef(0)->IsObject()) {
        LOGE("JSPlaceChildren arg is wrong");
        (*iterLayoutChildren_)->Layout();
        iterLayoutChildren_++;
        return panda::JSValueRef::Undefined(vm);
    }

    auto jsObject = JsiObject(info->GetCallArgRef(0)->ToObject(vm));
    JSRef<JSObject> layoutInfo = JSRef<JSObject>::Make(jsObject);
    JSRef<JSVal> xVal = layoutInfo->GetProperty("x");
    JSRef<JSVal> yVal = layoutInfo->GetProperty("y");
    CalcDimension dimenX;
    CalcDimension dimenY;
    auto xResult = JSViewAbstract::ParseJsDimensionVp(xVal, dimenX);
    auto yResult = JSViewAbstract::ParseJsDimensionVp(yVal, dimenY);
    if (!(xResult || yResult)) {
        LOGE("the position prop is illegal");
    } else {
        (*iterLayoutChildren_)->GetGeometryNode()->SetFrameOffset({ dimenX.ConvertToPx(), dimenY.ConvertToPx() });
    }
    (*iterLayoutChildren_)->Layout();
    iterLayoutChildren_++;
    return panda::JSValueRef::Undefined(vm);
}

#endif

} // namespace OHOS::Ace::Framework
