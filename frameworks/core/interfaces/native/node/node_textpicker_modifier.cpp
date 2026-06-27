/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/node_textpicker_modifier.h"

#include "ui/base/utils/utils.h"

#include "core/common/dynamic_module_helper.h"

namespace OHOS::Ace::NG {
#ifdef ACE_UNITTEST
namespace NodeModifier {
const ArkUITextPickerModifier* GetTextPickerDynamicModifier();
const CJUITextPickerModifier* GetCJUITextPickerModifier();
} // namespace NodeModifier
namespace TextPickerUtil {
const TextPickerCustomModifier* GetTextPickerCustomModifier();
} // namespace TextPickerUtil
#endif
namespace NodeModifier {
const ArkUITextPickerModifier* GetTextPickerModifier()
{
    static const ArkUITextPickerModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
#ifdef ACE_UNITTEST
        cachedModifier = NG::NodeModifier::GetTextPickerDynamicModifier();
#else
        // Dynamically load the independently compiled so library
        // from frameworks/core/components_ng/pattern/text_picker directory
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("TextPicker");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const ArkUITextPickerModifier*>(module->GetDynamicModifier());
#endif
    }
    return cachedModifier;
}

const CJUITextPickerModifier* GetCJUITextPickerModifier()
{
    static const CJUITextPickerModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
#ifdef ACE_UNITTEST
        cachedModifier = NG::NodeModifier::GetCJUITextPickerModifier();
#else
        // Dynamically load the independently compiled so library
        // from frameworks/core/components_ng/pattern/text_picker directory
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("TextPicker");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const CJUITextPickerModifier*>(module->GetCjModifier());
#endif
    }
    return cachedModifier;
}

void SetTextPickerOnChange(ArkUINodeHandle node, void* extraParam)
{
    static const ArkUITextPickerModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
#ifdef ACE_UNITTEST
        cachedModifier = NG::NodeModifier::GetTextPickerDynamicModifier();
#else
        // Dynamically load the independently compiled so library
        // from frameworks/core/components_ng/pattern/text_picker directory
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("TextPicker");
        CHECK_NULL_VOID(module);
        cachedModifier = reinterpret_cast<const ArkUITextPickerModifier*>(module->GetDynamicModifier());
#endif
    }
    cachedModifier->setTextPickerOnChangeHandler(node, extraParam);
}

void SetTextPickerOnScrollStop(ArkUINodeHandle node, void* extraParam)
{
    static const ArkUITextPickerModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
#ifdef ACE_UNITTEST
        cachedModifier = NG::NodeModifier::GetTextPickerDynamicModifier();
#else
        // Dynamically load the independently compiled so library
        // from frameworks/core/components_ng/pattern/text_picker directory
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("TextPicker");
        CHECK_NULL_VOID(module);
        cachedModifier = reinterpret_cast<const ArkUITextPickerModifier*>(module->GetDynamicModifier());
#endif
    }
    cachedModifier->setTextPickerOnScrollStopHandler(node, extraParam);
}

const NG::TextPickerUtil::TextPickerCustomModifier* GetTextPickerCustomModifier()
{
    static const NG::TextPickerUtil::TextPickerCustomModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
#ifdef ACE_UNITTEST
        cachedModifier = NG::TextPickerUtil::GetTextPickerCustomModifier();
#else
        // Dynamically load the independently compiled so library
        // from frameworks/core/components_ng/pattern/text_picker directory
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("TextPicker");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const NG::TextPickerUtil::TextPickerCustomModifier*>(
            module->GetCustomModifier("customModifier"));
#endif
    }
    return cachedModifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
