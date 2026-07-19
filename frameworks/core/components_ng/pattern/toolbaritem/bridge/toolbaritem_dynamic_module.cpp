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

#include "core/components_ng/pattern/toolbaritem/bridge/toolbaritem_dynamic_module.h"

#include "arkoala_api_generated.h"
#include "core/components_ng/pattern/toolbaritem/bridge/arkts_native_toolbaritem_bridge.h"
#include "core/components_ng/pattern/toolbaritem/toolbaritem_model_ng.h"

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_ToolBarItem()
{
    return new OHOS::Ace::ToolBarItemDynamicModule();
}

namespace OHOS::Ace {
namespace NG {

namespace NodeModifier {
const ArkUIToolBarItemModifier* GetToolbaritemDynamicModifier();
} // namespace NodeModifier
namespace GeneratedModifier {
const GENERATED_ArkUIToolBarItemModifier* GetToolBarItemStaticModifier();
}

ToolBarItemModelNG* GetToolBarItemModel()
{
    static ToolBarItemModelNG model;
    return &model;
}
} // namespace NG

void ToolBarItemDynamicModule::RegisterAttributes(
    panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::ToolBarItemBridge::RegisterToolBarItemAttributes(object, vm);
}

const void* ToolBarItemDynamicModule::GetDynamicModifier()
{
    return NG::NodeModifier::GetToolbaritemDynamicModifier();
}

const void* ToolBarItemDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetToolBarItemStaticModifier();
#else
    return nullptr;
#endif
}

const void* ToolBarItemDynamicModule::GetCjModifier()
{
    return nullptr;
}

const void* ToolBarItemDynamicModule::GetCustomModifier(const std::string& name)
{
    return nullptr;
}

void* ToolBarItemDynamicModule::GetModel()
{
    return NG::GetToolBarItemModel();
}
} // namespace OHOS::Ace
