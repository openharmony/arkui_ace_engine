/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "arkoala_api_generated.h"

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace {
std::optional<std::string> ConvertString(const Ark_Union_Number_String& src)
{
    std::optional<std::string> value;
    auto selector = src.selector;
    if (selector == 1) {
        value = Converter::OptConvert<std::string>(src.value1);
    }
    return value;
}
std::optional<int32_t> ConvertInt(const Ark_Union_Number_String& src)
{
    std::optional<int32_t> value;
    auto selector = src.selector;
    if (selector == 0) {
        value = Converter::OptConvert<int32_t>(src.value0);
    }
    return value;
}
} // namespace
namespace IUIContextAccessor {
void FreezeUINode0Impl(const Ark_String* id,
                       Ark_Boolean isFrozen)
{
    CHECK_NULL_VOID(id);
    ViewAbstract::FreezeUINodeById(Converter::Convert<std::string>(*id), Converter::Convert<bool>(isFrozen));
}
void FreezeUINode1Impl(Ark_Int64 id,
                       Ark_Boolean isFrozen)
{
    ViewAbstract::FreezeUINodeByUniqueId(Converter::Convert<int64_t>(id), Converter::Convert<bool>(isFrozen));
}
Ark_Boolean DispatchKeyEventImpl(const Ark_Union_Number_String* node,
                                 Ark_KeyEvent event)
{
    auto result = false;
    RefPtr<NG::FrameNode> frameNode = nullptr;
    auto convId = ConvertString(*node);
    if (convId) {
        frameNode = NG::Inspector::GetFrameNodeByKey(*convId);
    } else {
        auto numberId = ConvertInt(*node);
        if (numberId) {
            auto node = ElementRegister::GetInstance()->GetNodeById(*numberId);
            frameNode = AceType::DynamicCast<NG::FrameNode>(node);
        }
    }
    CHECK_NULL_RETURN(frameNode, Converter::ArkValue<Ark_Boolean>(result));
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_RETURN(focusHub, Converter::ArkValue<Ark_Boolean>(result));

    CHECK_NULL_RETURN(event, Converter::ArkValue<Ark_Boolean>(result));
    const auto info = event->GetEventInfo();
    CHECK_NULL_RETURN(info, Converter::ArkValue<Ark_Boolean>(result));
    KeyEvent keyEvent;
    info->ParseKeyEvent(keyEvent);
    result = focusHub->HandleEvent(keyEvent);
    return Converter::ArkValue<Ark_Boolean>(result);
}
} // IUIContextAccessor
const GENERATED_ArkUIIUIContextAccessor* GetIUIContextAccessor()
{
    static const GENERATED_ArkUIIUIContextAccessor IUIContextAccessorImpl {
        IUIContextAccessor::FreezeUINode0Impl,
        IUIContextAccessor::FreezeUINode1Impl,
        IUIContextAccessor::DispatchKeyEventImpl,
    };
    return &IUIContextAccessorImpl;
}

}
