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
#include "core/components_ng/pattern/linear_split/bridge/row_split_dynamic_module.h"

#include "arkoala_api_generated.h"

#include "core/components_ng/pattern/linear_split/bridge/arkts_native_row_split_bridge.h"
#include "core/components_ng/pattern/linear_split/linear_split_model_ng.h"
#ifdef INCLUDE_GENERATED_SOURCES
#include "core/components_ng/pattern/linear_split/linear_split_model_ng_static.h"
#endif

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_RowSplit()
{
    return new OHOS::Ace::RowSplitDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
namespace NodeModifier {
const ArkUIRowSplitModifier* GetRowSplitDynamicModifier();
const CJUIRowSplitModifier* GetCJUIRowSplitModifier();
} // namespace NodeModifier
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
const GENERATED_ArkUIRowSplitModifier* GetRowSplitStaticModifier();
}
#endif
} // namespace NG

void RowSplitDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::RowSplitBridge::RegisterRowSplitAttributes(object, vm);
}

const void* RowSplitDynamicModule::GetDynamicModifier()
{
    return NG::NodeModifier::GetRowSplitDynamicModifier();
}

const void* RowSplitDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetRowSplitStaticModifier();
#else
    return nullptr;
#endif
}

const void* RowSplitDynamicModule::GetCjModifier()
{
    return NG::NodeModifier::GetCJUIRowSplitModifier();
}

void* RowSplitDynamicModule::GetModel()
{
    static NG::LinearSplitModelNG model;
    return &model;
}

} // namespace OHOS::Ace