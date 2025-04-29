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

#include "frameworks/bridge/declarative_frontend/jsview/js_line.h"

#include "bridge/declarative_frontend/jsview/models/line_model_impl.h"
#include "core/components/shape/shape_component.h"
#include "core/components_ng/pattern/shape/line_model.h"
#include "core/components_ng/pattern/shape/line_model_ng.h"

namespace OHOS::Ace {
LineModel* LineModel::GetInstance()
{
#ifdef NG_BUILD
    static NG::LineModelNG instance;
    return &instance;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        static NG::LineModelNG instance;
        return &instance;
    } else {
        static Framework::LineModelImpl instance;
        return &instance;
    }
#endif
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

void JSLine::JSBind(BindingTarget globalObj)
{
    JSClass<JSLine>::Declare("Line");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSLine>::StaticMethod("create", &JSLine::Create, opt);

    JSClass<JSLine>::StaticMethod("width", &JSShapeAbstract::JsWidth);
    JSClass<JSLine>::StaticMethod("height", &JSShapeAbstract::JsHeight);
    JSClass<JSLine>::StaticMethod("startPoint", &JSLine::SetStart);
    JSClass<JSLine>::StaticMethod("endPoint", &JSLine::SetEnd);

    JSClass<JSLine>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSLine>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSLine>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSLine>::StaticMethod("onClick", &JSInteractableView::JsOnClick);

    JSClass<JSLine>::InheritAndBind<JSShapeAbstract>(globalObj);
}

void JSLine::Create(const JSCallbackInfo& info)
{
    LineModel::GetInstance()->Create();
    JSShapeAbstract::SetSize(info);
}

void JSLine::SetStart(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsArray()) {
        return;
    }
    JSRef<JSArray> pointArray = JSRef<JSArray>::Cast(info[0]);
    ShapePoint startPoint;
    SetPoint(pointArray, startPoint);
    LineModel::GetInstance()->StartPoint(startPoint);
}

void JSLine::SetEnd(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsArray()) {
        return;
    }
    JSRef<JSArray> pointArray = JSRef<JSArray>::Cast(info[0]);
    ShapePoint endPoint;
    SetPoint(pointArray, endPoint);
    LineModel::GetInstance()->EndPoint(endPoint);
}

void JSLine::SetPoint(const JSRef<JSArray>& array, ShapePoint& point)
{
    if (array->Length() < 1) {
        return;
    }

    auto parseJsDimension = [](const JSRef<JSVal>& jsValue, Dimension &val) {
        if (jsValue->IsNumber()) {
            val = Dimension(jsValue->ToNumber<double>(), DimensionUnit::VP);
        } else if (jsValue->IsString()) {
            if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
                val = StringUtils::StringToDimension(jsValue->ToString(), true);
            } else if (!StringUtils::StringToDimensionWithUnitNG(jsValue->ToString(), val, DimensionUnit::VP, 0.0)) {
                // unit is invalid, use default value(0.0vp) instead.
                val = 0.0_vp;
            }
        } else if (jsValue->IsObject()) {
            CalcDimension value;
            ParseJsDimensionVpNG(jsValue, value);
            if (!StringUtils::StringToDimensionWithUnitNG(value.ToString(), val, DimensionUnit::VP, 0.0)) {
                // unit is invalid, use default value(0.0vp) instead.
                val = 0.0_vp;
            }
        }
    };

    parseJsDimension(array->GetValueAt(0), point.first);
    parseJsDimension(array->GetValueAt(1), point.second);
}

} // namespace OHOS::Ace::Framework
