/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ui/base/utils/utils.h"

#include "core/common/dynamic_module_helper.h"
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"
#include "frameworks/base/log/log_wrapper.h"

namespace OHOS::Ace::NG::GeneratedModifier {
const GENERATED_ArkUIDataPanelModifier* GetDataPanelModifier()
{
    static const GENERATED_ArkUIDataPanelModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("DataPanel");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const GENERATED_ArkUIDataPanelModifier*>(module->GetStaticModifier());
    }
    return cachedModifier;
}

const GENERATED_ArkUIDataPanelExtenderAccessor* GetDataPanelExtenderAccessor()
{
    static const GENERATED_ArkUIDataPanelExtenderAccessor* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("DataPanel");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const GENERATED_ArkUIDataPanelExtenderAccessor*>(module->GetStaticModifier());
    }
    return cachedModifier;
}
}
