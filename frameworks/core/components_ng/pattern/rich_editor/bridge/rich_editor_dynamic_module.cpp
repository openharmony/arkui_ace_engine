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

#include "core/components_ng/pattern/rich_editor/bridge/rich_editor_dynamic_module.h"

#include "arkoala_api_generated.h"

#include "core/components_ng/pattern/rich_editor/bridge/arkts_native_rich_editor_bridge.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"

#ifdef INCLUDE_GENERATED_SOURCES
#include "core/components_ng/pattern/rich_editor/rich_editor_model_static.h"
#endif

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_Richeditor()
{
    return new OHOS::Ace::RichEditorDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
namespace NodeModifier {
const ArkUIRichEditorModifier* GetRichEditorDynamicModifier();
const CJUIRichEditorModifier* GetCJUIRichEditorDynamicModifier();
}

#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
const GENERATED_ArkUIRichEditorModifier* GetRichEditorStaticModifier();
} // namespace GeneratedModifier
#endif
} // namespace NG

void RichEditorDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::RichEditorBridge::RegisterRichEditorAttributes(object, vm);
}

const void* RichEditorDynamicModule::GetDynamicModifier()
{
    return NG::NodeModifier::GetRichEditorDynamicModifier();
}

const void* RichEditorDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetRichEditorStaticModifier();
#else
    return nullptr;
#endif
}

const void* RichEditorDynamicModule::GetCjModifier()
{
    return NG::NodeModifier::GetCJUIRichEditorDynamicModifier();
}

void* RichEditorDynamicModule::GetModel()
{
    static NG::RichEditorModelNG model;
    return &model;
}

const void* RichEditorDynamicModule::GetCustomModifier(const std::string& name)
{
    return nullptr;
}

} // namespace OHOS::Ace