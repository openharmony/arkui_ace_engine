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

#include "arkoala_api_generated.h"
#include "core/components_ng/pattern/radio/radio_model_ng.h"
#include "core/interfaces/arkoala/generated/interface/node_api.h"
#include "core/interfaces/arkoala/utility/converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
    namespace RadioInterfaceModifier {
        void _setRadioOptionsImpl(Ark_NativePointer node, const Ark_RadioOptions* options) {
        }
    } // RadioInterfaceModifier
    namespace RadioAttributeModifier {
        void CheckedImpl(Ark_NativePointer node, Ark_Boolean value) {
            auto frameNode = reinterpret_cast<FrameNode*>(node);
            CHECK_NULL_VOID(frameNode);
            RadioModelNG::SetChecked(frameNode, value);
        }
        void OnChangeImpl(Ark_NativePointer node, Ark_Function callback) {
            auto frameNode = reinterpret_cast<FrameNode*>(node);
            CHECK_NULL_VOID(frameNode);
            auto onEvent = [frameNode](const bool value) {
                GetFullAPI()->getEventsAPI()->getRadioEventsReceiver()->onChange(frameNode->GetId(), value);
            };
            RadioModelNG::SetOnChange(frameNode, onEvent);
        }
        void RadioStyleImpl(Ark_NativePointer node, const Opt_RadioStyle* value) {
            auto frameNode = reinterpret_cast<FrameNode*>(node);
            CHECK_NULL_VOID(frameNode);
            CHECK_NULL_VOID(value);
            if (auto checkedBackgroundColor = Converter::OptConvert<Color>(value->value.checkedBackgroundColor); 
                checkedBackgroundColor) {
                RadioModelNG::SetCheckedBackgroundColor(frameNode, checkedBackgroundColor.value());
            }
            if (auto uncheckedBorderColor = Converter::OptConvert<Color>(value->value.uncheckedBorderColor); 
                uncheckedBorderColor) {
                RadioModelNG::SetUncheckedBorderColor(frameNode, uncheckedBorderColor.value());
            }
            if (auto indicatorColor = Converter::OptConvert<Color>(value->value.indicatorColor); 
                indicatorColor) {
                RadioModelNG::SetIndicatorColor(frameNode, indicatorColor.value());
            }
        }
        void ContentModifierImpl(Ark_NativePointer node, const Ark_CustomObject* modifier) {
            LOGE("ARKOALA RadioAttributeModifier::ContentModifierImpl -> Method is not "
                "implemented.");
        }
    } // RadioAttributeModifier
    const GENERATED_ArkUIRadioModifier* GetRadioModifier() {
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
