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

#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"

#include "core/common/dynamic_module_helper.h"
#include "ui/base/utils/utils.h"


namespace OHOS::Ace::NG::GeneratedModifier {
#ifdef ARKUI_CAPI_UNITTEST
const GENERATED_ArkUITextTimerModifier* GetTextTimerStaticModifier();
#endif
const GENERATED_ArkUITextTimerModifier* GetTextTimerModifier()
{
    static const GENERATED_ArkUITextTimerModifier* cachedModifier = nullptr;

    if (cachedModifier == nullptr) {
#ifdef ARKUI_CAPI_UNITTEST
        cachedModifier = GetTextTimerStaticModifier();
#else
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("TextTimer");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const GENERATED_ArkUITextTimerModifier*>(module->GetStaticModifier());
#endif
    }

    return cachedModifier;
}
}