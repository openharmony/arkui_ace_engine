/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_indicator_controller_binding.h"

#include "core/common/container.h"
#include "core/common/dynamic_module_helper.h"

namespace OHOS::Ace::Framework {
namespace {
const NG::ArkUIIndicatorControllerModifier* GetIndicatorControllerModifier()
{
    static const NG::ArkUIIndicatorControllerModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("IndicatorComponent");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const NG::ArkUIIndicatorControllerModifier*>(
            module->GetCustomModifier("indicator_controller"));
    }
    return cachedModifier;
}
} // namespace

void JSIndicatorControllerBinding::JSBind(BindingTarget globalObj)
{
    JSClass<JSIndicatorController>::Declare("IndicatorComponentController");
    JSClass<JSIndicatorController>::CustomMethod("showNext", &JSIndicatorControllerBinding::ShowNext);
    JSClass<JSIndicatorController>::CustomMethod("showPrevious", &JSIndicatorControllerBinding::ShowPrevious);
    JSClass<JSIndicatorController>::CustomMethod("changeIndex", &JSIndicatorControllerBinding::ChangeIndex);

    JSClass<JSIndicatorController>::Bind(
        globalObj, JSIndicatorControllerBinding::Constructor, JSIndicatorControllerBinding::Destructor);
}

void JSIndicatorControllerBinding::Constructor(const JSCallbackInfo& args)
{
    auto scroller = Referenced::MakeRefPtr<JSIndicatorController>();
    scroller->IncRefCount();
    args.SetReturnValue(Referenced::RawPtr(scroller));
}

void JSIndicatorControllerBinding::Destructor(JSIndicatorController* scroller)
{
    if (scroller != nullptr) {
        scroller->DecRefCount();
    }
}

void JSIndicatorControllerBinding::ShowNext(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    if (auto* modifier = GetIndicatorControllerModifier()) {
        modifier->showNext(controllerHandle_);
    }
}

void JSIndicatorControllerBinding::ShowPrevious(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    if (auto* modifier = GetIndicatorControllerModifier()) {
        modifier->showPrevious(controllerHandle_);
    }
}

void JSIndicatorControllerBinding::ChangeIndex(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    if (!args[0]->IsNumber()) {
        return;
    }
    bool useAnimation = false;
    if (args.Length() > 1 && args[1]->IsBoolean()) {
        useAnimation = args[1]->ToBoolean();
    }
    if (auto* modifier = GetIndicatorControllerModifier()) {
        modifier->changeIndex(controllerHandle_, args[0]->ToNumber<int32_t>(), useAnimation);
    }
}
} // namespace OHOS::Ace::Framework
