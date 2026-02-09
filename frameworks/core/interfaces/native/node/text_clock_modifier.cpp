/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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

#include "base/log/log_wrapper.h"
#include "core/common/dynamic_module_helper.h"
#include "core/interfaces/native/node/text_clock_modifier.h"
#include "core/components_ng/pattern/text_clock/text_clock_model_ng.h"
#include "ui/base/utils/utils.h"

namespace OHOS::Ace::NG {
namespace NodeModifier {
const ArkUITextClockModifier* GetTextClockModifier()
{
    static const ArkUITextClockModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("TextClock");
        if (module == nullptr) {
            LOGF("Can't find textclock dynamic module");
            abort();
        }
        cachedModifier = reinterpret_cast<const ArkUITextClockModifier*>(module->GetDynamicModifier());
    }
    return cachedModifier;
}

const CJUITextClockModifier* GetCJUITextClockModifier()
{
    static const CJUITextClockModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("TextClock");
        if (module == nullptr) {
            LOGF("Can't find textclock dynamic module");
            abort();
        }
        cachedModifier = reinterpret_cast<const CJUITextClockModifier*>(module->GetCjModifier());
    }
    return cachedModifier;
}

const ArkUITextClockCustomModifier* GetTextClockCustomModifier()
{
    static const ArkUITextClockCustomModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("TextClock");
        if (module == nullptr) {
            LOGF("Can't find textclock dynamic module");
            abort();
        }
        cachedModifier =
            reinterpret_cast<const ArkUITextClockCustomModifier*>(module->GetCustomModifier("customModifier"));
    }
    return cachedModifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
