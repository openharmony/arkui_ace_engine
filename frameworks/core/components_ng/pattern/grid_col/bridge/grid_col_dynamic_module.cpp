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

#include "core/components_ng/pattern/grid_col/bridge/grid_col_dynamic_module.h"

#include "arkoala_api_generated.h"

#include "core/components_ng/pattern/grid_col/bridge/arkts_native_grid_col_bridge.h"
#include "core/components_ng/pattern/grid_col/grid_col_model_ng.h"

#ifdef INCLUDE_GENERATED_SOURCES
#include "core/components_ng/pattern/grid_col/grid_col_model_ng_static.h"
#endif

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_GridCol()
{
    return new OHOS::Ace::GridColDynamicModule();
}

namespace OHOS::Ace {

namespace V2 {
const char GRID_COL_ETS_TAG[] = "GridCol";
} // namespace V2

namespace NG {
const ArkUIGridColModifier* GetGridColDynamicModifier();
const CJUIGridColModifier* GetCJUIGridColModifier();
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
const GENERATED_ArkUIGridColModifier* GetGridColStaticModifier();
}
#endif
} // namespace NG

void GridColDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::GridColBridge::RegisterGridColAttributes(object, vm);
}

const void* GridColDynamicModule::GetDynamicModifier()
{
    return NG::GetGridColDynamicModifier();
}

const void* GridColDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetGridColStaticModifier();
#else
    return nullptr;
#endif
}

const void* GridColDynamicModule::GetCjModifier()
{
    return NG::GetCJUIGridColModifier();
}

void* GridColDynamicModule::GetModel()
{
    static NG::GridColModelNG model;
    return &model;
}

} // namespace OHOS::Ace