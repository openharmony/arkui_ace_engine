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

#include "frameworks/bridge/declarative_frontend/jsview/js_polyline.h"

#include "core/common/container.h"
#include "core/components_ng/pattern/shape/polygon_model.h"
#include "frameworks/base/memory/referenced.h"

namespace OHOS::Ace::Framework {

void JSPolyline::Create(const JSCallbackInfo& info)
{
    PolygonModel::GetInstance()->Create(false);
    JSShapeAbstract::SetSize(info);
}

void JSPolyline::JSBind(BindingTarget globalObj)
{
    JSClass<JSPolyline>::Declare("Polyline");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSPolyline>::StaticMethod("create", &JSPolyline::Create, opt);

    JSClass<JSPolyline>::StaticMethod("width", &JSShapeAbstract::JsWidth);
    JSClass<JSPolyline>::StaticMethod("height", &JSShapeAbstract::JsHeight);
    JSClass<JSPolyline>::StaticMethod("points", &JSPolyline::JSPoints);

    JSClass<JSPolyline>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSPolyline>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSPolyline>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSPolyline>::StaticMethod("onClick", &JSInteractableView::JsOnClick);

    JSClass<JSPolyline>::InheritAndBind<JSShapeAbstract>(globalObj);
}

void JSPolyline::JSPoints(const JSCallbackInfo& info)
{
    ShapePoints points;
    PolygonModel::GetInstance()->SetPoints(points);
    if (info.Length() < 1 || !info[0]->IsArray()) {
        return;
    }
    ShapePoint point;

    JSRef<JSArray> pointsArray = JSRef<JSArray>::Cast(info[0]);
    if (pointsArray->Length() < 2) {
        return;
    }
    for (size_t i = 0; i < pointsArray->Length(); i++) {
        JSRef<JSVal> val = pointsArray->GetValueAt(i);
        if (!val->IsArray()) {
            continue;
        }
        JSRef<JSArray> pointArray = JSRef<JSArray>::Cast(val);
        if (pointArray->GetValueAt(0)->IsNumber()) {
            point.first = Dimension(pointArray->GetValueAt(0)->ToNumber<double>(), DimensionUnit::VP);
        } else if (pointArray->GetValueAt(0)->IsString()) {
            point.first = StringUtils::StringToDimension(pointArray->GetValueAt(0)->ToString(), true);
        } else {
            return;
        }
        if (pointArray->GetValueAt(1)->IsNumber()) {
            point.second = Dimension(pointArray->GetValueAt(1)->ToNumber<double>(), DimensionUnit::VP);
        } else if (pointArray->GetValueAt(1)->IsString()) {
            point.second = StringUtils::StringToDimension(pointArray->GetValueAt(1)->ToString(), true);
        } else {
            return;
        }
        points.push_back(point);
    }
    PolygonModel::GetInstance()->SetPoints(points);
}

} // namespace OHOS::Ace::Framework
