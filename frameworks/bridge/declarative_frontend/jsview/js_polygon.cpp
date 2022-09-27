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

#include "frameworks/bridge/declarative_frontend/jsview/js_polygon.h"

#include "core/common/container.h"
#include "core/components/box/box_component.h"
#include "core/components/shape/shape_component.h"
#include "core/components_ng/pattern/shape/polygon_view.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {

void JSPolygon::Create(const JSCallbackInfo& info)
{
    if (Container::IsCurrentUseNewPipeline()) {
        NG::PolygonView::Create(true);
        JSShapeAbstract::SetNgSize(info);
        return;
    }
    RefPtr<Component> polygonComponent = AceType::MakeRefPtr<OHOS::Ace::ShapeComponent>(ShapeType::POLYGON);
    ViewStackProcessor::GetInstance()->ClaimElementId(polygonComponent);
    ViewStackProcessor::GetInstance()->Push(polygonComponent);
    JSShapeAbstract::SetSize(info);
}

void JSPolygon::JSBind(BindingTarget globalObj)
{
    JSClass<JSPolygon>::Declare("Polygon");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSPolygon>::StaticMethod("create", &JSPolygon::Create, opt);

    JSClass<JSPolygon>::StaticMethod("width", &JSShapeAbstract::JsWidth);
    JSClass<JSPolygon>::StaticMethod("height", &JSShapeAbstract::JsHeight);
    JSClass<JSPolygon>::StaticMethod("points", &JSPolygon::JsPoints);

    JSClass<JSPolygon>::Inherit<JSShapeAbstract>();
    JSClass<JSPolygon>::Bind(globalObj);
}

void JSPolygon::JsPoints(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 argument.");
        return;
    }
    ShapePoint shapePoint;
    ShapePoints shapePoints;
    JSRef<JSArray> pointsArray = JSRef<JSArray>::Cast(info[0]);
    if (pointsArray->Length() < 3) {
        LOGE("Less than three parameters");
        return;
    } else {
        for (size_t i = 0; i < pointsArray->Length(); i++) {
            JSRef<JSArray> pointArray = pointsArray->GetValueAt(i);
            if (pointArray->GetValueAt(0)->IsNumber()) {
                shapePoint.first = Dimension(pointArray->GetValueAt(0)->ToNumber<double>(), DimensionUnit::VP);
            } else if (pointArray->GetValueAt(0)->IsString()) {
                shapePoint.first = StringUtils::StringToDimension(pointArray->GetValueAt(0)->ToString(), true);
            } else {
                LOGE("Polygon point should be Number or String");
                return;
            }
            if (pointArray->GetValueAt(1)->IsNumber()) {
                shapePoint.second = Dimension(pointArray->GetValueAt(1)->ToNumber<double>(), DimensionUnit::VP);
            } else if (pointArray->GetValueAt(1)->IsString()) {
                shapePoint.second = StringUtils::StringToDimension(pointArray->GetValueAt(1)->ToString(), true);
            } else {
                LOGE("Polygon point should be Number or String");
                return;
            }
            shapePoints.push_back(shapePoint);
        }
        if(Container::IsCurrentUseNewPipeline()){
            NG::PolygonView::SetPoints(shapePoints);
            return;
        }
        auto polygon = AceType::DynamicCast<ShapeComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
        if (!polygon) {
            LOGE("ShapeComponent is null.");
            return;
        }
        polygon->SetPoints(shapePoints);
    }
}

} // namespace OHOS::Ace::Framework
