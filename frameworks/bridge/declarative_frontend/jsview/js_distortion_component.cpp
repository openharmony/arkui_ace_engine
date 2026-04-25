/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_distortion_component.h"

#include "frameworks/core/components_ng/pattern/distortion_component/distortion_component_model_ng.h"
#include "frameworks/core/components_ng/pattern/distortion_component/distortion_component_model.h"
#include "frameworks/core/components_ng/pattern/distortion_component/distortion_component_options.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"

namespace OHOS::Ace {
std::unique_ptr<DistortionComponentModel> DistortionComponentModel::instance_ = nullptr;
std::mutex DistortionComponentModel::mutex_;

DistortionComponentModel* DistortionComponentModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
            instance_.reset(new NG::DistortionComponentModelNG());
        }
    }
    return instance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
namespace {
/**
 * Parses Vector2 from JS object property.
 * Vector2 is an array [number, number] representing [x, y].
 */
NG::VectorF ParseVector2Option(const JSRef<JSObject>& obj, const char* propertyName)
{
    auto val = obj->GetProperty(propertyName);
    if (!val->IsObject()) {
        return NG::VectorF(0.0f, 0.0f);
    }
    auto vector2Obj = JSRef<JSObject>::Cast(val);
    auto xVal = vector2Obj->GetProperty("x");
    auto yVal = vector2Obj->GetProperty("y");
    if (!xVal->IsNumber() || !yVal->IsNumber()) {
        return NG::VectorF(0.0f, 0.0f);
    }
    return NG::VectorF(xVal->ToNumber<float>(), yVal->ToNumber<float>());
}

/**
 * Parses Vector4 from JS object property.
 * Vector4 is an array [number, number, number, number] representing [x, y, z, w].
 */
NG::Vector4F ParseVector4Option(const JSRef<JSObject>& obj, const char* propertyName)
{
    auto val = obj->GetProperty(propertyName);
    if (!val->IsObject()) {
        return NG::Vector4F(0.0f, 0.0f, 0.0f, 0.0f);
    }
    auto vector4Obj = JSRef<JSObject>::Cast(val);
    auto xVal = vector4Obj->GetProperty("x");
    auto yVal = vector4Obj->GetProperty("y");
    auto zVal = vector4Obj->GetProperty("z");
    auto wVal = vector4Obj->GetProperty("w");
    if (!xVal->IsNumber() || !yVal->IsNumber() || !zVal->IsNumber() || !wVal->IsNumber()) {
        return NG::Vector4F(0.0f, 0.0f, 0.0f, 0.0f);
    }
    
    return NG::Vector4F(
        xVal->ToNumber<float>(),
        yVal->ToNumber<float>(),
        zVal->ToNumber<float>(),
        wVal->ToNumber<float>()
    );
}

} // namespace

void JSDistortionComponent::Create(const JSCallbackInfo& info)
{
    DistortionComponentModel::GetInstance()->Create();
    if (info.Length() > 0 && info[0]->IsObject()) {
        auto obj = JSRef<JSObject>::Cast(info[0]);
        auto distortion = obj->GetProperty("distortion");
        Distortion(distortion);
    }
}

void JSDistortionComponent::Distortion(const JSRef<JSVal>& distortion)
{
    if (!distortion->IsObject()) {
        return;
    }
    // Parse distortion options from JS object
    auto obj = JSRef<JSObject>::Cast(distortion);
    NG::DistortionParam distortionParam;
    distortionParam.luCorner = ParseVector2Option(distortion, "topLeft");
    distortionParam.ruCorner = ParseVector2Option(distortion, "topRight");
    distortionParam.lbCorner = ParseVector2Option(distortion, "bottomLeft");
    distortionParam.rbCorner = ParseVector2Option(distortion, "bottomRight");
    distortionParam.barrelDistortion = ParseVector4Option(distortion, "barrelDistortion");
    DistortionComponentModel::GetInstance()->SetDistortion(distortionParam);
}

void JSDistortionComponent::JSBind(BindingTarget globalObj)
{
    JSClass<JSDistortionComponent>::Declare("DistortionComponent");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSDistortionComponent>::StaticMethod("create", &JSDistortionComponent::Create, opt);

    JSClass<JSDistortionComponent>::InheritAndBind<JSContainerBase>(globalObj);
}

} // namespace OHOS::Ace::Framework