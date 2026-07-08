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

#include "core/components_ng/pattern/grid_container/bridge/grid_container_dynamic_module.h"

#include "core/components_ng/pattern/grid_container/bridge/arkts_native_grid_container_bridge.h"
#include "core/components_ng/pattern/grid_container/grid_container_model_ng.h"

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_GridContainer()
{
    return new OHOS::Ace::GridContainerDynamicModule();
}

namespace OHOS::Ace {
namespace NG {
const ArkUIGridContainerModifier* GetGridContainerDynamicModifier();
}

void GridContainerDynamicModule::RegisterAttributes(
    panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::GridContainerBridge::RegisterGridContainerAttributes(object, vm);
}

const void* GridContainerDynamicModule::GetDynamicModifier()
{
    return NG::GetGridContainerDynamicModifier();
}

const void* GridContainerDynamicModule::GetStaticModifier()
{
    return nullptr;
}

const void* GridContainerDynamicModule::GetCjModifier()
{
    return nullptr;
}

void* GridContainerDynamicModule::GetModel()
{
    static NG::GridContainerModelNG model;
    return &model;
}
} // namespace OHOS::Ace
