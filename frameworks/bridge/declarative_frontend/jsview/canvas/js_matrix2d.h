/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_MATRIX2D_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_MATRIX2D_H

#include "base/memory/referenced.h"
#include "bridge/declarative_frontend/engine/bindings_defines.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "frameworks/core/components/common/properties/paint_state.h"

namespace OHOS::Ace::Framework {

class JSMatrix2d final : public Referenced {
public:
    JSMatrix2d() = default;
    ~JSMatrix2d() override = default;

    static void JSBind(BindingTarget globalObj);
    static void Constructor(const JSCallbackInfo& info);
    static void Destructor(JSMatrix2d* matrix2d);
    static TransformParam GetTransformInfo(const JSRef<JSObject>& obj);
    void JsSetScaleX(const JSCallbackInfo& info);
    void JsSetRotateY(const JSCallbackInfo& info);
    void JsSetRotateX(const JSCallbackInfo& info);
    void JsSetScaleY(const JSCallbackInfo& info);
    void JsSetTranslateX(const JSCallbackInfo& info);
    void JsSetTranslateY(const JSCallbackInfo& info);

    void JsGetScaleX(const JSCallbackInfo& info);
    void JsGetRotateY(const JSCallbackInfo& info);
    void JsGetRotateX(const JSCallbackInfo& info);
    void JsGetScaleY(const JSCallbackInfo& info);
    void JsGetTranslateX(const JSCallbackInfo& info);
    void JsGetTranslateY(const JSCallbackInfo& info);

    void JsIdentity(const JSCallbackInfo& info);
    void JsInvert(const JSCallbackInfo& info);
    void JsRotate(const JSCallbackInfo& info);
    void JsTranslate(const JSCallbackInfo& info);
    void JsScale(const JSCallbackInfo& info);
    void JSMultiply(const JSCallbackInfo& info) {}

    double JsGetScaleX() const
    {
        return transform_.scaleX;
    }

    double JsGetRotateY() const
    {
        return transform_.skewY;
    }

    double JsGetRotateX() const
    {
        return transform_.skewX;
    }

    double JsGetScaleY() const
    {
        return transform_.scaleY;
    }

    double JsGetTranslateX() const
    {
        return transform_.translateX;
    }

    double JsGetTranslateY() const
    {
        return transform_.translateY;
    }

    TransformParam GetTransform() const
    {
        return transform_;
    }

    void SetTransform(const TransformParam& param)
    {
        transform_ = param;
    }

    void SetUnit(CanvasUnit unit)
    {
        unit_ = unit;
    }

    CanvasUnit GetUnit()
    {
        return unit_;
    }

    double GetDensity()
    {
        double density = PipelineBase::GetCurrentDensity();
        return ((GetUnit() == CanvasUnit::DEFAULT) && !NearZero(density)) ? density : 1.0;
    }

    std::string ToString() const;
    ACE_DISALLOW_COPY_AND_MOVE(JSMatrix2d);

private:
    TransformParam transform_;
    CanvasUnit unit_ = CanvasUnit::DEFAULT;
};

} // OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_MATRIX2D_H

