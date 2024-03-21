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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_RECT_SHAPE_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_RECT_SHAPE_H

#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_shape_abstract.h"

namespace OHOS::Ace::Framework {

class JSRectShape : public JSShapeAbstract {
    DECLARE_ACE_TYPE(JSRectShape, JSShapeAbstract);

public:
    static void JSBind(BindingTarget globalObj);
    static void JsRadiusWidth(const JSCallbackInfo& info);
    static void JsRadiusHeight(const JSCallbackInfo& info);
    static void SetRadius(const JSCallbackInfo& info);

    static void ConstructorCallback(const JSCallbackInfo& info);
    static void DestructorCallback(JSRectShape* obj);

    void ObjectRadiusWidth(const JSCallbackInfo& info);
    void ObjectRadiusHeight(const JSCallbackInfo& info);
    void ObjectRadius(const JSCallbackInfo& info);

protected:
    enum RADIUS { TOP_LEFT_RADIUS = 0, TOP_RIGHT_RADIUS = 1, BOTTOM_RIGHT_RADIUS = 2, BOTTOM_LEFT_RADIUS = 3 };

private:
    static void SetRadiusValue(
        const RefPtr<ShapeRect>& shapeRect, const CalcDimension& radiusX, const CalcDimension& radiusY, int32_t index);
    static void SetRadiusWithArrayValue(const RefPtr<ShapeRect>& shapeRect, const JSRef<JSVal>& jsVal);
    static void SetRadiusWithJsVal(const RefPtr<ShapeRect>& shapeRect, const JSRef<JSVal>& jsVal);
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_RECT_SHAPE_H
