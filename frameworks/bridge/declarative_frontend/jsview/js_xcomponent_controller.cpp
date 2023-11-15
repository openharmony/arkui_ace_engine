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

#include "frameworks/bridge/declarative_frontend/jsview/js_xcomponent_controller.h"

#include "base/utils/linear_map.h"
#include "base/utils/utils.h"
#include "core/components/xcomponent/xcomponent_controller_impl.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_controller_ng.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_common_def.h"

namespace OHOS::Ace::Framework {
void JSXComponentController::JSBind(BindingTarget globalObj)
{
    JSClass<JSXComponentController>::Declare("XComponentController");
    JSClass<JSXComponentController>::CustomMethod("getXComponentSurfaceId", &JSXComponentController::GetSurfaceId);
    JSClass<JSXComponentController>::CustomMethod(
        "getXComponentContext", &JSXComponentController::GetXComponentContext);
    JSClass<JSXComponentController>::CustomMethod(
        "setXComponentSurfaceSize", &JSXComponentController::SetSurfaceConfig);
    JSClass<JSXComponentController>::Bind(
        globalObj, JSXComponentController::Constructor, JSXComponentController::Destructor);
}

void JSXComponentController::Constructor(const JSCallbackInfo& args)
{
    auto xcomponentController = Referenced::MakeRefPtr<JSXComponentController>();
    xcomponentController->IncRefCount();
    std::shared_ptr<InnerXComponentController> controller;
#ifdef NG_BUILD
    controller = std::make_shared<NG::XComponentControllerNG>();
#else
    if (Container::IsCurrentUseNewPipeline()) {
        controller = std::make_shared<NG::XComponentControllerNG>();
    } else {
        controller = std::make_shared<XComponentControllerImpl>();
    }
#endif
    xcomponentController->SetController(controller);
    args.SetReturnValue(Referenced::RawPtr(xcomponentController));
}

void JSXComponentController::Destructor(JSXComponentController* xcomponentController)
{
    if (xcomponentController) {
        xcomponentController->DecRefCount();
    }
}

void JSXComponentController::GetSurfaceId(const JSCallbackInfo& args)
{
    if (xcomponentController_) {
        auto surfaceId = xcomponentController_->GetSurfaceId();
        auto returnValue = JSVal(ToJSValue(surfaceId));
        auto returnPtr = JSRef<JSVal>::Make(returnValue);
        args.SetReturnValue(returnPtr);
    }
}

void JSXComponentController::SetSurfaceConfig(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsObject()) {
        LOGW("Invalid params");
        return;
    }

    JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
    uint32_t surfaceWidth;
    uint32_t surfaceHeight;
    if (!ConvertFromJSValue(obj->GetProperty("surfaceWidth"), surfaceWidth) ||
        !ConvertFromJSValue(obj->GetProperty("surfaceHeight"), surfaceHeight)) {
        LOGW("Failed to parse param 'surfaceWidth' or 'surfaceHeight'");
        return;
    }

    if (xcomponentController_) {
        xcomponentController_->ConfigSurface(surfaceWidth, surfaceHeight);
    }
}
} // namespace OHOS::Ace::Framework