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
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/security_component/save_button/save_button_common.h"
#include "core/components_ng/pattern/security_component/save_button/save_button_model_ng.h"
#include "core/components/common/layout/constants.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/interfaces/native/generated/interface/ui_node_api.h"
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
        case ARK_SAVE_DESCRIPTION_SAVE_ALL: dst = SaveButtonSaveDescription::SAVE_ALL; break;
        default: LOGE("Unexpected enum value in Ark_SaveDescription: %{public}d", src);
    }
}
template<>
SaveButtonStyle Convert(const Opt_SaveButtonOptions& src)
{
    SaveButtonStyle style;
    style.text = OptConvert<SaveButtonSaveDescription>(src.value.text);
    style.icon = OptConvert<SaveButtonIconStyle>(src.value.icon);
    style.backgroundType = OptConvert<ButtonType>(src.value.buttonType);
    return style;
}
} // namespace OHOS::Ace::NG::Converter
namespace OHOS::Ace::NG::GeneratedModifier {
namespace SaveButtonModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    if (MultiThreadBuildManager::IsParallelScope()) {
        LOGF_ABORT("Unsupported UI components SaveButton used in ParallelizeUI");
    }
    auto frameNode = SaveButtonModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // SaveButtonModifier
namespace SaveButtonInterfaceModifier {
void SetSaveButtonOptionsImpl(Ark_NativePointer node,
                              const Opt_SaveButtonOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    auto style = Converter::Convert<SaveButtonStyle>(*options);
    SaveButtonModelNG::InitSaveButton(frameNode, style, false);
}
} // SaveButtonInterfaceModifier
namespace SaveButtonAttributeModifier {
void SetOnClickImpl(Ark_NativePointer node,
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
        auto error = Converter::ArkValue<Opt_BusinessErrorInterface_Void>();
        arkCallback.InvokeSync(event.ArkValue(), arkResult, error);
    };

    ViewAbstract::SetOnClick(frameNode, std::move(onEvent));
}
void SetSetIconImpl(Ark_NativePointer node,
                    const Opt_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    LOGI("ARKOALA SaveButtonAttributeModifier::SetSetIconImpl: is not implemented yet");
}
void SetSetTextImpl(Ark_NativePointer node,
                    const Opt_Union_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    LOGI("ARKOALA SaveButtonAttributeModifier::SetSetTextImpl: is not implemented yet");
}
void SetIconSizeImpl(Ark_NativePointer node,
                     const Opt_Union_Dimension_SizeOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == INTEROP_TAG_UNDEFINED) {
        return;
    }
    auto valueSelector = value->value.selector;
    if (valueSelector == 0) {
        Opt_Dimension dimensionTmp = {};
        dimensionTmp.tag = INTEROP_TAG_OBJECT;
        dimensionTmp.value = value->value.value0;
        auto valueOpt = Converter::OptConvert<Dimension>(dimensionTmp);
        Validator::ValidateNonNegative(valueOpt);
        Validator::ValidateNonPercent(valueOpt);
        SecurityComponentModelNG::SetIconSize(frameNode, valueOpt);
    } else if (valueSelector == 1) {
        auto sizeOptionsTmp = value->value.value1;
        auto widthDimension = Converter::OptConvert<Dimension>(sizeOptionsTmp.width);
        auto heightDimension = Converter::OptConvert<Dimension>(sizeOptionsTmp.height);
        std::optional<CalcLength> width;
        std::optional<CalcLength> height;
        if (widthDimension.has_value()) {
            width.emplace(CalcLength(widthDimension.value()));
        }
        if (heightDimension.has_value()) {
            height.emplace(CalcLength(heightDimension.value()));
        }
        SecurityComponentModelNG::SetIconSize(frameNode, CalcSize(width, height));
    } else {
        return;
    }
}
void SetIconBorderRadiusImpl(Ark_NativePointer node,
                             const Opt_Union_Dimension_BorderRadiuses* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    LOGI("ARKOALA SaveButtonAttributeModifier::SetIconBorderRadiusImpl: is not implemented yet");
}
void SetStateEffectImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    LOGI("ARKOALA SaveButtonAttributeModifier::SetStateEffectImpl: is not implemented yet");
}
} // SaveButtonAttributeModifier
const GENERATED_ArkUISaveButtonModifier* GetSaveButtonModifier()
{
    static const GENERATED_ArkUISaveButtonModifier ArkUISaveButtonModifierImpl {
        SaveButtonModifier::ConstructImpl,
        SaveButtonInterfaceModifier::SetSaveButtonOptionsImpl,
        SaveButtonAttributeModifier::SetOnClickImpl,
        SaveButtonAttributeModifier::SetSetIconImpl,
        SaveButtonAttributeModifier::SetSetTextImpl,
        SaveButtonAttributeModifier::SetIconSizeImpl,
        SaveButtonAttributeModifier::SetIconBorderRadiusImpl,
        SaveButtonAttributeModifier::SetStateEffectImpl,
    };
    return &ArkUISaveButtonModifierImpl;
}

}
