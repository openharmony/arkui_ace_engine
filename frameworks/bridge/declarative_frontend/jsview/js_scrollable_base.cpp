/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_scrollable_base.h"

#include "bridge/declarative_frontend/jsview/js_shape_abstract.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"

namespace OHOS::Ace::Framework {
void JSScrollableBase::JSFlingSpeedLimit(const JSCallbackInfo& info)
{
    double max = -1.0;
    if (!JSViewAbstract::ParseJsDouble(info[0], max)) {
        return;
    }
    NG::ScrollableModelNG::SetMaxFlingSpeed(max);
}

void JSScrollableBase::JsOnWillScroll(const JSCallbackInfo& args)
{
    if (args.Length() <= 0) {
        return;
    }
    if (args[0]->IsFunction()) {
        auto onScroll = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])](
                            const CalcDimension& scrollOffset, const ScrollState& scrollState,
                            ScrollSource scrollSource) {
            auto params = ConvertToJSValues(scrollOffset, scrollState, scrollSource);
            ScrollFrameResult scrollRes { .offset = scrollOffset };
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, scrollRes);
            auto result = func->Call(JSRef<JSObject>(), params.size(), params.data());
            if (result.IsEmpty()) {
                return scrollRes;
            }

            if (!result->IsObject()) {
                return scrollRes;
            }

            auto resObj = JSRef<JSObject>::Cast(result);
            auto dxRemainValue = resObj->GetProperty("offsetRemain");
            if (dxRemainValue->IsNumber()) {
                scrollRes.offset = Dimension(dxRemainValue->ToNumber<float>(), DimensionUnit::VP);
            }
            return scrollRes;
        };
        NG::ScrollableModelNG::SetOnWillScroll(std::move(onScroll));
    } else {
        NG::ScrollableModelNG::SetOnWillScroll(nullptr);
    }
}

void JSScrollableBase::JsOnDidScroll(const JSCallbackInfo& args)
{
    if (args.Length() > 0 && args[0]->IsFunction()) {
        auto onScroll = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])](
                            const CalcDimension& scrollOffset, const ScrollState& scrollState) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto params = ConvertToJSValues(scrollOffset, scrollState);
            func->Call(JSRef<JSObject>(), params.size(), params.data());
        };
        NG::ScrollableModelNG::SetOnDidScroll(std::move(onScroll));
    }
}

void JSScrollableBase::SetFadingEdge(const JSCallbackInfo& info)
{
    bool fadingEdge = false;
    CalcDimension fadingEdgeLength = Dimension(32.0, DimensionUnit::VP); // 32.0: default fading edge length
    if (info.Length() >= 1) {
        ParseJsBool(info[0], fadingEdge);
    }
    if (info.Length() == 2 && info[1]->IsObject()) { /* 2: parameter count */
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[1]);
        JSViewAbstract::ParseLengthMetricsToDimension(obj->GetProperty("fadingEdgeLength"), fadingEdgeLength);
        if (fadingEdgeLength.Value() < 0) {
            fadingEdgeLength = Dimension(32.0, DimensionUnit::VP); // 32.0: default fading edge length
        }
    }
    NG::ScrollableModelNG::SetFadingEdge(fadingEdge, fadingEdgeLength);
}

void JSScrollableBase::SetDigitalCrownSensitivity(const JSCallbackInfo& info)
{
#ifdef SUPPORT_DIGITAL_CROWN
    if (info.Length() < 1 || info[0]->IsNull() || !info[0]->IsNumber()) {
        NG::ScrollableModelNG::SetDigitalCrownSensitivity(
            static_cast<CrownSensitivity>(static_cast<int32_t>(CrownSensitivity::MEDIUM)));
        return;
    }
    auto sensitivity = info[0]->ToNumber<int32_t>();
    if (sensitivity < 0 || sensitivity > static_cast<int32_t>(CrownSensitivity::HIGH)) {
        NG::ScrollableModelNG::SetDigitalCrownSensitivity(
            static_cast<CrownSensitivity>(static_cast<int32_t>(CrownSensitivity::MEDIUM)));
        return;
    } else {
        NG::ScrollableModelNG::SetDigitalCrownSensitivity(static_cast<CrownSensitivity>(sensitivity));
    }
#endif
}

void JSScrollableBase::JSBind(BindingTarget globalObj)
{
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSScrollableBase>::Declare("JSContainerBase");
    JSClass<JSScrollableBase>::StaticMethod("flingSpeedLimit", &JSScrollableBase::JSFlingSpeedLimit, opt);
    JSClass<JSScrollableBase>::StaticMethod("onWillScroll", &JSScrollableBase::JsOnWillScroll);
    JSClass<JSScrollableBase>::StaticMethod("onDidScroll", &JSScrollableBase::JsOnDidScroll);
    JSClass<JSScrollableBase>::StaticMethod("fadingEdge", &JSScrollableBase::SetFadingEdge);
    JSClass<JSScrollableBase>::StaticMethod("clipContent", &JSScrollableBase::JSClipContent);
    JSClass<JSScrollableBase>::StaticMethod("digitalCrownSensitivity", &JSScrollableBase::SetDigitalCrownSensitivity);
    JSClass<JSScrollableBase>::InheritAndBind<JSContainerBase>(globalObj);
}

void JSScrollableBase::JSClipContent(const JSCallbackInfo& info)
{
    if (info.Length() != 1) {
        return;
    }
    if (info[0]->IsNumber()) {
        auto mode = static_cast<NG::ContentClipMode>(info[0]->ToNumber<int32_t>());
        if (mode >= NG::ContentClipMode::CONTENT_ONLY && mode <= NG::ContentClipMode::SAFE_AREA) {
            NG::ScrollableModelNG::SetContentClip(mode, nullptr);
            return;
        }
    } else if (info[0]->IsObject()) {
        auto* clipShape = JSRef<JSObject>::Cast(info[0])->Unwrap<JSShapeAbstract>();
        if (clipShape) {
            NG::ScrollableModelNG::SetContentClip(
                NG::ContentClipMode::CUSTOM, AceType::DynamicCast<ShapeRect>(clipShape->GetBasicShape()));
            return;
        }
    }
    // default
    NG::ScrollableModelNG::SetContentClip(NG::ContentClipMode::DEFAULT, nullptr);
}
} // namespace OHOS::Ace::Framework
