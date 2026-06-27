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

#include "core/components_ng/pattern/arc_list/bridge/arc_list_dynamic_module.h"
#include "core/components_ng/pattern/arc_list/bridge/arc_list_custom_modifier.h"

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_bridge.h"

namespace OHOS::Ace {

namespace NG::NodeModifier {
const ArkUIArcListModifier* GetArcListDynamicModifier();
const ArkUIArcListItemModifier* GetArcListItemDynamicModifier();
const ArkUIArcListCustomModifier* GetArcListCustomModifier();
const ArkUIArcListItemCustomModifier* GetArcListItemCustomModifier();
} // namespace NG::NodeModifier

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_ArcList()
{
    return new ArcListDynamicModule();
}

void ArcListDynamicModule::RegisterAttributes(
    panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
}

const void* ArcListDynamicModule::GetDynamicModifier()
{
    return NG::NodeModifier::GetArcListDynamicModifier();
}

const void* ArcListDynamicModule::GetStaticModifier()
{
    return nullptr;
}

const void* ArcListDynamicModule::GetCjModifier()
{
    return nullptr;
}

void* ArcListDynamicModule::GetModel()
{
    return nullptr;
}

const void* ArcListDynamicModule::GetCustomModifier(const std::string& name)
{
    if (name == "item") {
        return NG::NodeModifier::GetArcListItemCustomModifier();
    } else if (name == "item_dynamic") {
        return NG::NodeModifier::GetArcListItemDynamicModifier();
    }
    return NG::NodeModifier::GetArcListCustomModifier();
}
} // namespace OHOS::Ace
