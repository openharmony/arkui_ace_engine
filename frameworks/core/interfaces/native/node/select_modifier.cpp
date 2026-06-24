/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/select_modifier.h"

#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/pattern/select/bridge/select_custom_modifier.h"
#include "core/interfaces/native/node/select_modifier.h"
#include "core/interfaces/native/utility/converter.h"

namespace OHOS::Ace::NG::Converter {
template<>
ACE_FORCE_EXPORT void AssignCast(std::optional<AvoidanceMode>& dst, const Ark_AvoidanceMode& src)
{
    auto customModifier = NG::NodeModifier::GetSelectCustomModifier();
    if (customModifier) {
        customModifier->castAvoidTarget(dst, src);
    }
}
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG {
namespace NodeModifier {
const ArkUISelectModifier* GetSelectModifier()
{
    static const ArkUISelectModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Select");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const ArkUISelectModifier*>(module->GetDynamicModifier());
    }
    return cachedModifier;
}

const CJUISelectModifier* GetCJUISelectModifier()
{
    static const CJUISelectModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Select");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const CJUISelectModifier*>(module->GetCjModifier());
    }
    return cachedModifier;
}

const ArkUISelectCustomModifier* GetSelectCustomModifier()
{
    static const ArkUISelectCustomModifier* cachedCustomModifier = nullptr;
    if (cachedCustomModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Select");
        CHECK_NULL_RETURN(module, nullptr);
        cachedCustomModifier = reinterpret_cast<const ArkUISelectCustomModifier*>(module->GetCustomModifier());
    }
    return cachedCustomModifier;
}

void SetOnSelectSelect(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [node, extraParam](int32_t index, const std::string& value) {
        ArkUINodeEvent event;
        event.kind = TEXT_ARRAY;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        auto indexStr = std::to_string(index);
        const char* arrayValue[] = {value.c_str(), indexStr.c_str()};
        event.textArrayEvent.subKind = ON_SELECT_SELECT;
        event.textArrayEvent.nativeStringArrayPtr = reinterpret_cast<intptr_t>(arrayValue);
        SendArkUISyncEvent(&event);
    };
    auto customModifier = NG::NodeModifier::GetSelectCustomModifier();
    CHECK_NULL_VOID(customModifier);
    customModifier->setOnSelect(frameNode, std::move(onEvent));
}
}
} // namespace OHOS::Ace::NG
