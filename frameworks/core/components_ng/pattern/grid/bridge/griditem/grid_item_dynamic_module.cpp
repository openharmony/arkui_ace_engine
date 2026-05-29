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

#include "core/components_ng/pattern/grid/bridge/griditem/grid_item_dynamic_module.h"

#include "arkoala_api_generated.h"

#include "core/components_ng/pattern/grid/bridge/griditem/arkts_native_grid_item_bridge.h"
#include "core/components_ng/pattern/grid/bridge/griditem/grid_item_utils_modifier.h"
#include "core/components_ng/pattern/grid/grid_item_model_ng.h"

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_GridItem()
{
    return new OHOS::Ace::GridItemDynamicModule();
}

namespace OHOS::Ace {
namespace NG {
namespace NodeModifier {
const ArkUIGridItemModifier* GetGridItemDynamicModifier();
const CJUIGridItemModifier* GetCJUIGridItemDynamicModifier();
const GridItemCustomModifier* GetGridItemCustomDynamicModifier();
} // namespace NodeModifier

#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
const GENERATED_ArkUIGridItemModifier* GetGridItemStaticModifier();
}
#endif
} // namespace NG

void GridItemDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::GridItemBridge::RegisterGridItemAttributes(object, vm);
}

const void* GridItemDynamicModule::GetDynamicModifier()
{
    return NG::NodeModifier::GetGridItemDynamicModifier();
}

const void* GridItemDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetGridItemStaticModifier();
#else
    return nullptr;
#endif
}

const void* GridItemDynamicModule::GetCjModifier()
{
    return NG::NodeModifier::GetCJUIGridItemDynamicModifier();
}

void* GridItemDynamicModule::GetModel()
{
    static NG::GridItemModelNG gridItemModel;
    return &gridItemModel;
}

const void* GridItemDynamicModule::GetCustomModifier(const std::string& name)
{
    if (name == "GridItemCustom") {
        return NG::NodeModifier::GetGridItemCustomDynamicModifier();
    }
    return nullptr;
}
} // namespace OHOS::Ace
