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

#include "core/components_ng/pattern/data_panel/bridge/data_panel_dynamic_module.h"

#include "core/components_ng/pattern/data_panel/bridge/arkts_native_data_panel_bridge.h"
#include "core/components_ng/pattern/data_panel/bridge/data_panel_content_modifier_helper.h"
#include "core/components_ng/pattern/data_panel/data_panel_model_ng.h"
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"

#include "base/log/ace_scoring_log.h"

#ifndef ARKUI_WEARABLE
#include "core/components_ng/pattern/data_panel/data_panel_model_static.h"
#endif

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_DataPanel()
{
    return new OHOS::Ace::DataPanelDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
const ArkUIDataPanelModifier* GetDataPanelDynamicModifier();
const CJUIDataPanelModifier* GetCJUIDataPanelModifier();
#ifndef ARKUI_WEARABLE
namespace GeneratedModifier {
const GENERATED_ArkUIDataPanelModifier* GetDataPanelStaticModifier();
const GENERATED_ArkUIDataPanelContentModifier* GetDataPanelStaticContentModifier();
const GENERATED_ArkUIDataPanelExtenderAccessor* GetDataPanelExtenderAccessor();
}
#endif
} // namespace NG

void DataPanelDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::DataPanelBridge::RegisterDataPanelAttributes(object, vm);
}

const void* DataPanelDynamicModule::GetDynamicModifier()
{
    return NG::GetDataPanelDynamicModifier();
}

const void* DataPanelDynamicModule::GetStaticModifier()
{
#ifndef ARKUI_WEARABLE
    return NG::GeneratedModifier::GetDataPanelStaticModifier();
#else
    return nullptr;
#endif
}

const void* DataPanelDynamicModule::GetCjModifier()
{
    return NG::GetCJUIDataPanelModifier();
}

void* DataPanelDynamicModule::GetModel()
{
    static NG::DataPanelModelNG model;
    return &model;
}

} // namespace OHOS::Ace