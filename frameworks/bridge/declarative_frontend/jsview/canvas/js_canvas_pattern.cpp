/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/canvas/js_canvas_pattern.h"

#include "bridge/declarative_frontend/jsview/canvas/js_matrix2d.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "core/components_ng/render/adapter/matrix2d.h"

namespace OHOS::Ace::Framework {
constexpr int SET_TRANSFORM_PARAMETER_SIZE = 1;
void JSCanvasPattern::Constructor(const JSCallbackInfo& info)
{
    auto canvasPattern = Referenced::MakeRefPtr<JSCanvasPattern>();
    canvasPattern->IncRefCount();
    info.SetReturnValue(Referenced::RawPtr(canvasPattern));
}

void JSCanvasPattern::Destructor(JSCanvasPattern* canvasPattern)
{
    if (canvasPattern != nullptr) {
        canvasPattern->DecRefCount();
    }
}

void JSCanvasPattern::JSBind(BindingTarget globalObj)
{
    JSClass<JSCanvasPattern>::Declare("CanvasPattern");
    JSClass<JSCanvasPattern>::CustomMethod("setTransform", &JSCanvasPattern::JSSetTransform);
    JSClass<JSCanvasPattern>::Bind(globalObj, JSCanvasPattern::Constructor, JSCanvasPattern::Destructor);
}

void JSCanvasPattern::JSSetTransform(const JSCallbackInfo& info)
{
    if (info.Length() != SET_TRANSFORM_PARAMETER_SIZE || !info[0]->IsObject()) {
        return;
    }
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TEN)) {
        auto* matrix = JSRef<JSObject>::Cast(info[0])->Unwrap<JSMatrix2d>();
        if (matrix) {
            auto canvasRenderer = canvasRenderWeak_.Upgrade();
            if (canvasRenderer) {
                canvasRenderer->SetTransform(GetId(), matrix->GetTransform());
            }
        }
        return;
    }

    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);
    TransformParam param = JSMatrix2d::GetTransformInfo(jsObj);
    double density = GetDensity();
    param.translateX *= density;
    param.translateY *= density;
    auto canvasRenderer = canvasRenderWeak_.Upgrade();
    if (canvasRenderer) {
        canvasRenderer->SetTransform(GetId(), param);
    }
}
} // namespace OHOS::Ace::Framework

