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

#include "core/common/multi_thread_build_manager.h"
#include "core/components_ng/pattern/security_component/paste_button/paste_button_common.h"
#include "core/components_ng/pattern/security_component/paste_button/paste_button_model_ng.h"
#include "core/components/common/layout/constants.h"
#include "core/interfaces/native/implementation/click_event_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::Converter {
template<>
void AssignCast(std::optional<PasteButtonIconStyle>& dst, const Ark_PasteIconStyle& src)
{
    switch (src) {
        case ARK_PASTE_ICON_STYLE_LINES: dst = PasteButtonIconStyle::ICON_LINE; break;
        default: LOGE("Unexpected enum value in Ark_PasteIconStyle: %{public}d", src);
    }
}
template<>
void AssignCast(std::optional<PasteButtonPasteDescription>& dst, const Ark_PasteDescription& src)
{
    switch (src) {
        case ARK_PASTE_DESCRIPTION_PASTE: dst = PasteButtonPasteDescription::PASTE; break;
        default: LOGE("Unexpected enum value in Ark_PasteDescription: %{public}d", src);
    }
}
template<>
PasteButtonStyle Convert(const Opt_PasteButtonOptions& src)
{
    PasteButtonStyle style;
    style.text = OptConvert<PasteButtonPasteDescription>(src.value.text);
    style.icon = OptConvert<PasteButtonIconStyle>(src.value.icon);
    style.backgroundType = OptConvert<ButtonType>(src.value.buttonType);
    return style;
}
} // namespace OHOS::Ace::NG::Converter
namespace OHOS::Ace::NG::GeneratedModifier {
namespace PasteButtonModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = PasteButtonModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // PasteButtonModifier
namespace PasteButtonInterfaceModifier {
void SetPasteButtonOptionsImpl(Ark_NativePointer node,
                               const Opt_PasteButtonOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    auto style = Converter::Convert<PasteButtonStyle>(*options);
    PasteButtonModelNG::InitPasteButton(frameNode, style, false);
}
} // PasteButtonInterfaceModifier
namespace PasteButtonAttributeModifier {
void SetOnClickImpl(Ark_NativePointer node,
                    const Opt_PasteButtonCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onEvent = [arkCallback = CallbackHelper(value->value), frameNode](GestureEvent& info) {
        auto res = SecurityComponentHandleResult::CLICK_GRANT_FAILED;
        std::string message;
        int32_t code = 0;
#ifdef SECURITY_COMPONENT_ENABLE
        auto secEventValue = info.GetSecCompHandleEvent();
        if (secEventValue != nullptr) {
            int32_t intRes = secEventValue->GetInt("handleRes", static_cast<int32_t>(res));
            res = static_cast<SecurityComponentHandleResult>(intRes);
            if (res == SecurityComponentHandleResult::DROP_CLICK) {
                return;
            }
            code = secEventValue->GetInt("code", code);
            message = secEventValue->GetString("message", message);
        }
#endif
        const auto event = Converter::SyncEvent<Ark_ClickEvent>(info);
        auto arkResult = Converter::ArkValue<Ark_PasteButtonOnClickResult>(res);
        auto error = Converter::ArkValue<Opt_BusinessError>();
        arkCallback.InvokeSync(event.ArkValue(), arkResult, error);
    };
    ViewAbstract::SetOnClick(frameNode, std::move(onEvent));
}
} // PasteButtonAttributeModifier
const GENERATED_ArkUIPasteButtonModifier* GetPasteButtonModifier()
{
    static const GENERATED_ArkUIPasteButtonModifier ArkUIPasteButtonModifierImpl {
        PasteButtonModifier::ConstructImpl,
        PasteButtonInterfaceModifier::SetPasteButtonOptionsImpl,
        PasteButtonAttributeModifier::SetOnClickImpl,
    };
    return &ArkUIPasteButtonModifierImpl;
}

}
