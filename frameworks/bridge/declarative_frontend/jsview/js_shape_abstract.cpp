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

#include "frameworks/bridge/declarative_frontend/jsview/js_shape_abstract.h"

#include "base/geometry/shape.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/common/resource/resource_parse_utils.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {

void JSShapeAbstract::ObjectWidth(const JSCallbackInfo& info)
{
    info.ReturnSelf();
    if (info.Length() < 1) {
        return;
    }

    ObjectWidth(info[0]);
}

void JSShapeAbstract::ObjectWidth(const JSRef<JSVal>& jsValue)
{
    CalcDimension value;
    RefPtr<ResourceObject> widthResObj;
    if (!ParseJsDimensionVp(jsValue, value, widthResObj) || !basicShape_) {
        return;
    }
    if (SystemProperties::ConfigChangePerform() && widthResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, BasicShape& basicShape) {
            CalcDimension shapeValue;
            ResourceParseUtils::ParseResDimensionVp(resObj, shapeValue);
            if (LessNotEqual(shapeValue.Value(), 0.0)) {
                return;
            }
            basicShape.SetWidth(shapeValue);
        };
        basicShape_->AddResource("shapeAbstract.width", widthResObj, std::move(updateFunc));
    }
    if (LessNotEqual(value.Value(), 0.0)) {
        return;
    }
    basicShape_->SetWidth(value);
}

void JSShapeAbstract::ObjectHeight(const JSCallbackInfo& info)
{
    info.ReturnSelf();
    if (info.Length() < 1) {
        return;
    }

    ObjectHeight(info[0]);
}

void JSShapeAbstract::ObjectHeightUpdate(const RefPtr<ResourceObject>& heightResObj)
{
    if (heightResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, BasicShape& basicShape) {
            CalcDimension shapeValue;
            ResourceParseUtils::ParseResDimensionVp(resObj, shapeValue);
            if (LessNotEqual(shapeValue.Value(), 0.0)) {
                return;
            }
            basicShape.SetHeight(shapeValue);
        };
        basicShape_->AddResource("shapeAbstract.height", heightResObj, std::move(updateFunc));
    }
}

void JSShapeAbstract::ObjectHeight(const JSRef<JSVal>& jsValue)
{
    CalcDimension value;
    if (!SystemProperties::ConfigChangePerform()) {
        if (!ParseJsDimensionVp(jsValue, value)) {
            return;
        }
    } else {
        RefPtr<ResourceObject> heightResObj;
        if (!ParseJsDimensionVp(jsValue, value, heightResObj)) {
            LOGE("fail to parse the Dimension!");
            return;
        }
        ObjectHeightUpdate(heightResObj);
    }
    if (LessNotEqual(value.Value(), 0.0)) {
        return;
    }
    if (basicShape_) {
        basicShape_->SetHeight(value);
    }
}

void JSShapeAbstract::ObjectSize(const JSCallbackInfo& info)
{
    info.ReturnSelf();
    if (info.Length() < 1) {
        return;
    }

    if (!info[0]->IsObject()) {
        return;
    }

    JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(info[0]);
    ObjectWidth(sizeObj->GetProperty("width"));
    ObjectHeight(sizeObj->GetProperty("height"));
}

void JSShapeAbstract::ObjectOffsetUpdate(const RefPtr<ResourceObject>& xResObj, RefPtr<ResourceObject> yResObj)
{
    if (xResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, BasicShape& basicShape) {
            CalcDimension shapeValueX;
            ResourceParseUtils::ParseResDimensionVp(resObj, shapeValueX);
            CalcDimension shapeValueY = basicShape.GetOffset().GetY();
            basicShape.SetOffset(DimensionOffset(shapeValueX, shapeValueY));
        };
        basicShape_->AddResource("shapeAbstract.ObjectOffset.X", xResObj, std::move(updateFunc));
    }
    if (yResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, BasicShape& basicShape) {
            CalcDimension shapeValueY;
            ResourceParseUtils::ParseResDimensionVp(resObj, shapeValueY);
            CalcDimension shapeValueX = basicShape.GetOffset().GetX();
            basicShape.SetOffset(DimensionOffset(shapeValueX, shapeValueY));
        };
        basicShape_->AddResource("shapeAbstract.ObjectOffset.Y", yResObj, std::move(updateFunc));
    }
}

void JSShapeAbstract::ObjectOffset(const JSCallbackInfo& info)
{
    info.ReturnSelf();
    if (info.Length() > 0 && info[0]->IsObject()) {
        JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> xVal = sizeObj->GetProperty("x");
        JSRef<JSVal> yVal = sizeObj->GetProperty("y");
        CalcDimension x;
        CalcDimension y;
        if (!SystemProperties::ConfigChangePerform()) {
            if (basicShape_ && ParseJsDimensionVp(xVal, x) && ParseJsDimensionVp(yVal, y)) {
                basicShape_->SetOffset(DimensionOffset(x, y));
            }
        } else {
            RefPtr<ResourceObject> xResObj;
            RefPtr<ResourceObject> yResObj;
            if (basicShape_ && ParseJsDimensionVp(xVal, x, xResObj) && ParseJsDimensionVp(yVal, y, yResObj)) {
                ObjectOffsetUpdate(xResObj, yResObj);
                basicShape_->SetOffset(DimensionOffset(x, y));
            }
        }
    }
}

void JSShapeAbstract::ObjectFillUpdate(const RefPtr<ResourceObject>& fillResObj)
{
    if (fillResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, BasicShape& basicShape) {
            Color shapeValue;
            ResourceParseUtils::ParseResColor(resObj, shapeValue);
            basicShape.SetColor(shapeValue);
        };
        basicShape_->AddResource("shapeAbstract.fill", fillResObj, std::move(updateFunc));
    }
}

void JSShapeAbstract::ObjectFill(const JSCallbackInfo& info)
{
    info.ReturnSelf();
    if (info.Length() < 1) {
        return;
    }

    Color color;
    if (!SystemProperties::ConfigChangePerform()) {
        if (ParseJsColor(info[0], color) && basicShape_) {
            basicShape_->SetColor(color);
        }
    } else {
        RefPtr<ResourceObject> fillResObj;
        if (ParseJsColor(info[0], color, fillResObj) && basicShape_) {
            ObjectFillUpdate(fillResObj);
            basicShape_->SetColor(color);
        }
    }
}

void JSShapeAbstract::JSBind(BindingTarget globalObj)
{
    JSClass<JSShapeAbstract>::Declare("__JSShapeAbstract__");
    JSClass<JSShapeAbstract>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSShapeAbstract::ObjectPositionUpdate(DimensionOffset& position, RefPtr<ResourceObject>& xResObj,
    RefPtr<ResourceObject>& yResObj)
{
    if (SystemProperties::ConfigChangePerform() && xResObj) {
        auto&& updateFunc = [position](const RefPtr<ResourceObject>& resObj, BasicShape& basicShape) {
            DimensionOffset& value = const_cast<DimensionOffset&>(position);
            CalcDimension x;
            CalcDimension y;
            if (!ResourceParseUtils::ParseResDimensionVp(resObj, x)) {
                x = basicShape.GetPosition().GetX();
            }
            y = basicShape.GetPosition().GetY();
            value.SetX(x);
            value.SetY(y);
            basicShape.SetPosition(value);
        };
        basicShape_->AddResource("shapeAbstract.position.xResObj", xResObj, std::move(updateFunc));
    }
    if (SystemProperties::ConfigChangePerform() && yResObj) {
        auto&& updateFunc = [position](const RefPtr<ResourceObject>& resObj, BasicShape& basicShape) {
            DimensionOffset& value = const_cast<DimensionOffset&>(position);
            CalcDimension x;
            CalcDimension y;
            x = basicShape.GetPosition().GetX();
            if (!ResourceParseUtils::ParseResDimensionVp(resObj, y)) {
                y = basicShape.GetPosition().GetY();
            }
            value.SetX(x);
            value.SetY(y);
            basicShape.SetPosition(value);
        };
        basicShape_->AddResource("shapeAbstract.position.yResObj", yResObj, std::move(updateFunc));
    }
}

void JSShapeAbstract::ObjectPosition(const JSCallbackInfo& info)
{
    info.ReturnSelf();
    if (!(info.Length() > 0 && info[0]->IsObject())) {
        LOGE("Info is invalid!");
        return;
    }
    JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSVal> xVal = sizeObj->GetProperty("x");
    JSRef<JSVal> yVal = sizeObj->GetProperty("y");
    CalcDimension x;
    CalcDimension y;
    DimensionOffset position(x, y);
    CHECK_NULL_VOID(basicShape_);
    RefPtr<ResourceObject> xResObj;
    RefPtr<ResourceObject> yResObj;
    if (ParseJsDimensionVp(xVal, x, xResObj)) {
        position.SetX(x);
    }
    if (ParseJsDimensionVp(yVal, y, yResObj)) {
        position.SetY(y);
    }
    ObjectPositionUpdate(position, xResObj, yResObj);
    basicShape_->SetPosition(position);
}

void JSShapeAbstract::SetBasicShape(const RefPtr<BasicShape>& basicShape)
{
    basicShape_ = basicShape;
}
} // namespace OHOS::Ace::Framework
