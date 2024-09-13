/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/radio/radio_model_ng.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/ace_engine_types.h"
#include "core/interfaces/arkoala/generated/interface/node_api.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/radio/radio_pattern.h"

namespace OHOS::Ace::NG::Converter {
template<>
void AssignCast(std::optional<RadioIndicatorType>& dst, const Ark_RadioIndicatorType& src)
{
    switch (src) {
        case ARK_RADIO_INDICATOR_TYPE_TICK: dst = RadioIndicatorType::TICK; break;
        case ARK_RADIO_INDICATOR_TYPE_DOT: dst = RadioIndicatorType::DOT; break;
        case ARK_RADIO_INDICATOR_TYPE_CUSTOM: dst = RadioIndicatorType::CUSTOM; break;
        default: LOGE("Unexpected enum value in Ark_RadioIndicatorType: %{public}d", src);
    }
}
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
    namespace RadioInterfaceModifier {
        void _setRadioOptionsImpl(Ark_NativePointer node, const Ark_RadioOptions* options)
        {
            CHECK_NULL_VOID(options);
            auto frameNode = reinterpret_cast<FrameNode*>(node);
            CHECK_NULL_VOID(frameNode);
            auto group = Converter::Convert<std::string>(options->group);
            RadioModelNG::SetRadioGroup(frameNode, group);
            auto radioValue = Converter::Convert<std::string>(options->value);
            RadioModelNG::SetRadioValue(frameNode, radioValue);
            if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
                auto indicatorType = Converter::OptConvert<RadioIndicatorType>(options->indicatorType);
                RadioModelNG::SetRadioIndicatorType(frameNode, EnumToInt(indicatorType));
            }
            LOGE("ARKOALA Opt_CustomBuilder -> Method is not implemented.");
        }
    } // RadioInterfaceModifier
    namespace RadioAttributeModifier {
        void CheckedImpl(Ark_NativePointer node, Ark_Boolean value)
        {
            auto frameNode = reinterpret_cast<FrameNode*>(node);
            CHECK_NULL_VOID(frameNode);
            auto isChecked = Converter::Convert<bool>(value);
            RadioModelNG::SetChecked(frameNode, isChecked);
        }
        void OnChangeImpl(Ark_NativePointer node, Ark_Function callback)
        {
            auto frameNode = reinterpret_cast<FrameNode*>(node);
            CHECK_NULL_VOID(frameNode);
            auto onEvent = [frameNode](const bool value) {
                GetFullAPI()->getEventsAPI()->getRadioEventsReceiver()->onChange(frameNode->GetId(), value);
            };
            RadioModelNG::SetOnChange(frameNode, onEvent);
        }
        void RadioStyleImpl(Ark_NativePointer node, const Opt_RadioStyle* value)
        {
            auto frameNode = reinterpret_cast<FrameNode*>(node);
            CHECK_NULL_VOID(frameNode);
            CHECK_NULL_VOID(value);
            auto style = Converter::OptConvert<Converter::RadioStyle>(*value);
            if (style) {
                if (style->checkedBackgroundColor) {
                    RadioModelNG::SetCheckedBackgroundColor(frameNode, style->checkedBackgroundColor.value());
                }
                if (style->uncheckedBorderColor) {
                    RadioModelNG::SetUncheckedBorderColor(frameNode, style->uncheckedBorderColor.value());
                }
                if (style->indicatorColor) {
                    RadioModelNG::SetIndicatorColor(frameNode, style->indicatorColor.value());
                }
            }
        }
        void ContentModifierImpl(Ark_NativePointer node, const Ark_CustomObject* modifier)
        {
            LOGE("ARKOALA RadioAttributeModifier::ContentModifierImpl -> Method is not "
                "implemented.");
        }
    } // RadioAttributeModifier
    const GENERATED_ArkUIRadioModifier* GetRadioModifier()
    {
        static const GENERATED_ArkUIRadioModifier ArkUIRadioModifierImpl {
            RadioInterfaceModifier::_setRadioOptionsImpl,
            RadioAttributeModifier::CheckedImpl,
            RadioAttributeModifier::OnChangeImpl,
            RadioAttributeModifier::RadioStyleImpl,
            RadioAttributeModifier::ContentModifierImpl,
        };
        return &ArkUIRadioModifierImpl;
    }
}
