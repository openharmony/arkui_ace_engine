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

#include "core/components_ng/pattern/panel/bridge/panel_dynamic_module.h"

#include "core/components_ng/pattern/panel/bridge/arkts_native_panel_bridge.h"
#include "core/components_ng/pattern/panel/sliding_panel_model_ng.h"

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_Panel()
{
    return new OHOS::Ace::PanelDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
namespace NodeModifier {
const ArkUIPanelModifier* GetPanelDynamicModifier();
const CJUIPanelModifier* GetCJUIPanelModifier();
} // namespace NodeModifier
} // namespace NG

void PanelDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::PanelBridge::RegisterPanelAttributes(object, vm);
}

const void* PanelDynamicModule::GetDynamicModifier()
{
    return NG::NodeModifier::GetPanelDynamicModifier();
}

const void* PanelDynamicModule::GetStaticModifier()
{
    return nullptr;
}

const void* PanelDynamicModule::GetCjModifier()
{
    return NG::NodeModifier::GetCJUIPanelModifier();
}

void* PanelDynamicModule::GetModel()
{
    static NG::SlidingPanelModelNG model;
    return &model;
}

const void* PanelDynamicModule::GetCustomModifier(const std::string& name)
{
    return nullptr;
}

} // namespace OHOS::Ace
