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

#include "core/components_ng/pattern/grid/bridge/grid/grid_dynamic_module.h"

#include "arkoala_api_generated.h"

#include "core/components_ng/pattern/grid/bridge/grid/arkts_native_grid_bridge.h"
#include "core/components_ng/pattern/grid/bridge/grid/grid_utils_modifier.h"
#include "core/components_ng/pattern/grid/grid_model_ng.h"

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_Grid()
{
    return new OHOS::Ace::GridDynamicModule();
}

namespace OHOS::Ace {
namespace NG {
namespace NodeModifier {
const ArkUIGridModifier* GetGridDynamicModifier();
const CJUIGridModifier* GetCJUIGridDynamicModifier();
const GridCustomModifier* GetGridCustomDynamicModifier();
} // namespace NodeModifier

#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
const GENERATED_ArkUIGridModifier* GetGridStaticModifier();
const GENERATED_ArkUIUIGridEventAccessor* GetUIGridEventStaticAccessor();
} // namespace GeneratedModifier
#endif
} // namespace NG

void GridDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::GridBridge::RegisterGridAttributes(object, vm);
}

const void* GridDynamicModule::GetDynamicModifier()
{
    return NG::NodeModifier::GetGridDynamicModifier();
}

const void* GridDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetGridStaticModifier();
#else
    return nullptr;
#endif
}

const void* GridDynamicModule::GetCjModifier()
{
    return NG::NodeModifier::GetCJUIGridDynamicModifier();
}

void* GridDynamicModule::GetModel()
{
    static NG::GridModelNG gridModel;
    return &gridModel;
}

const void* GridDynamicModule::GetCustomModifier(const std::string& name)
{
    if (name == "GridCustom") {
        return NG::NodeModifier::GetGridCustomDynamicModifier();
    }
#ifdef INCLUDE_GENERATED_SOURCES
    if (name == "UIGridEventAccessor") {
        return NG::GeneratedModifier::GetUIGridEventStaticAccessor();
    }
#endif
    return nullptr;
}
} // namespace OHOS::Ace
