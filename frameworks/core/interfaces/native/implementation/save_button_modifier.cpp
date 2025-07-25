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

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/security_component/save_button/save_button_common.h"
#include "core/components_ng/pattern/security_component/save_button/save_button_model_ng.h"
#include "core/components/common/layout/constants.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::Converter {
template<>
void AssignCast(std::optional<SaveButtonIconStyle>& dst, const Ark_SaveIconStyle& src)
{
    switch (src) {
        case ARK_SAVE_ICON_STYLE_FULL_FILLED: dst = SaveButtonIconStyle::ICON_FULL_FILLED; break;
        case ARK_SAVE_ICON_STYLE_LINES: dst = SaveButtonIconStyle::ICON_LINE; break;
        case ARK_SAVE_ICON_STYLE_PICTURE: dst = SaveButtonIconStyle::ICON_PICTURE; break;
        default: LOGE("Unexpected enum value in Ark_SaveIconStyle: %{public}d", src);
    }
}
template<>
void AssignCast(std::optional<SaveButtonSaveDescription>& dst, const Ark_SaveDescription& src)
{
    switch (src) {
        case ARK_SAVE_DESCRIPTION_DOWNLOAD: dst = SaveButtonSaveDescription::DOWNLOAD; break;
        case ARK_SAVE_DESCRIPTION_DOWNLOAD_FILE: dst = SaveButtonSaveDescription::DOWNLOAD_FILE; break;
        case ARK_SAVE_DESCRIPTION_SAVE: dst = SaveButtonSaveDescription::SAVE; break;
        case ARK_SAVE_DESCRIPTION_SAVE_IMAGE: dst = SaveButtonSaveDescription::SAVE_IMAGE; break;
        case ARK_SAVE_DESCRIPTION_SAVE_FILE: dst = SaveButtonSaveDescription::SAVE_FILE; break;
        case ARK_SAVE_DESCRIPTION_DOWNLOAD_AND_SHARE: dst = SaveButtonSaveDescription::DOWNLOAD_AND_SHARE; break;
        case ARK_SAVE_DESCRIPTION_RECEIVE: dst = SaveButtonSaveDescription::RECEIVE; break;
        case ARK_SAVE_DESCRIPTION_CONTINUE_TO_RECEIVE: dst = SaveButtonSaveDescription::CONTINUE_TO_RECEIVE; break;
        case ARK_SAVE_DESCRIPTION_SAVE_TO_GALLERY: dst = SaveButtonSaveDescription::SAVE_TO_GALLERY; break;
        case ARK_SAVE_DESCRIPTION_EXPORT_TO_GALLERY: dst = SaveButtonSaveDescription::EXPORT_TO_GALLERY; break;
        case ARK_SAVE_DESCRIPTION_QUICK_SAVE_TO_GALLERY: dst = SaveButtonSaveDescription::QUICK_SAVE_TO_GALLERY; break;
        case ARK_SAVE_DESCRIPTION_RESAVE_TO_GALLERY: dst = SaveButtonSaveDescription::RESAVE_TO_GALLERY; break;
        default: LOGE("Unexpected enum value in Ark_SaveDescription: %{public}d", src);
    }
}
template<>
SaveButtonStyle Convert(const Ark_SaveButtonOptions& src)
{
    SaveButtonStyle style;
    style.text = OptConvert<SaveButtonSaveDescription>(src.text);
    style.icon = OptConvert<SaveButtonIconStyle>(src.icon);
    style.backgroundType = OptConvert<ButtonType>(src.buttonType);
    return style;
}
} // namespace OHOS::Ace::NG::Converter
namespace OHOS::Ace::NG::GeneratedModifier {
namespace SaveButtonModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = SaveButtonModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // SaveButtonModifier
namespace SaveButtonInterfaceModifier {
void SetSaveButtonOptions0Impl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SaveButtonModelNG::InitSaveButton(frameNode, SaveButtonStyle(), false);
}
void SetSaveButtonOptions1Impl(Ark_NativePointer node,
                               const Ark_SaveButtonOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    auto style = Converter::Convert<SaveButtonStyle>(*options);
    SaveButtonModelNG::InitSaveButton(frameNode, style, false);
}
} // SaveButtonInterfaceModifier
namespace SaveButtonAttributeModifier {
void OnClickImpl(Ark_NativePointer node,
                 const Opt_SaveButtonCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onEvent = [arkCallback = CallbackHelper(value->value)](GestureEvent& info) {
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
        const auto event = Converter::ArkClickEventSync(info);
        Ark_SaveButtonOnClickResult arkResult = Converter::ArkValue<Ark_SaveButtonOnClickResult>(res);
        auto error = Opt_BusinessError{
            .value = Ark_BusinessError{
                .name = Converter::ArkValue<Ark_String>("", Converter::FC),
                .message = Converter::ArkValue<Ark_String>(message, Converter::FC),
                .stack = Converter::ArkValue<Opt_String>("", Converter::FC),
                .code = Converter::ArkValue<Ark_Number>(code)
            }
        };
        arkCallback.InvokeSync(event.ArkValue(), arkResult, error);
    };

    ViewAbstract::SetOnClick(frameNode, std::move(onEvent));
}
} // SaveButtonAttributeModifier
const GENERATED_ArkUISaveButtonModifier* GetSaveButtonModifier()
{
    static const GENERATED_ArkUISaveButtonModifier ArkUISaveButtonModifierImpl {
        SaveButtonModifier::ConstructImpl,
        SaveButtonInterfaceModifier::SetSaveButtonOptions0Impl,
        SaveButtonInterfaceModifier::SetSaveButtonOptions1Impl,
        SaveButtonAttributeModifier::OnClickImpl,
    };
    return &ArkUISaveButtonModifierImpl;
}

}
