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

#include "frameworks/bridge/declarative_frontend/jsview/js_indicator_controller.h"

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

JSIndicatorController::JSIndicatorController()
{
    if (auto* modifier = GetIndicatorControllerModifier()) {
        controllerHandle_ = modifier->createControllerHandle();
    }
}

void JSIndicatorController::SetControllerHandle(const RefPtr<AceType>& controller, const RefPtr<AceType>& indicatorNode)
{
    if (auto* modifier = GetIndicatorControllerModifier()) {
        modifier->setController(controllerHandle_, controller, indicatorNode);
    }
}

void JSIndicatorController::ResetSwiperNode()
{
    if (auto* modifier = GetIndicatorControllerModifier()) {
        modifier->resetSwiperNode(controllerHandle_);
    }
}

std::function<void()> JSIndicatorController::SetSwiperNodeBySwiper(const RefPtr<AceType>& node)
{
    if (auto* modifier = GetIndicatorControllerModifier()) {
        return modifier->setSwiperNodeBySwiper(controllerHandle_, node);
    }
    return nullptr;
}

RefPtr<AceType> JSIndicatorController::GetControllerBase() const
{
    if (auto* modifier = GetIndicatorControllerModifier()) {
        return modifier->getControllerBase(controllerHandle_);
    }
    return nullptr;
}
} // namespace OHOS::Ace::Framework
