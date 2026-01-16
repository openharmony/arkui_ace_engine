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

#include "core/components_ng/pattern/common_view/common_view_model_ng.h"
#include "core/components_ng/pattern/radio/bridge/radio_content_modifier_helper.h"
#include "core/components_ng/pattern/radio/radio_model_ng.h"
#include "core/components_ng/pattern/radio/radio_model_static.h"
#include "core/interfaces/native/common/api_impl.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/ace_engine_types.h"
#include "core/interfaces/native/utility/object_keeper.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/radio/radio_pattern.h"

namespace OHOS::Ace::NG {
namespace {

std::optional<bool> ProcessBindableChecked(FrameNode* frameNode, const Opt_Union_Boolean_Bindable* value)
{
    std::optional<bool> result;
    Converter::VisitUnionPtr(
        value, [&result](const Ark_Boolean& src) { result = Converter::OptConvert<bool>(src); },
        [&result, frameNode](const Ark_Bindable_Boolean& src) {
            result = Converter::OptConvert<bool>(src.value);
            WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
            auto onEvent = [arkCallback = CallbackHelper(src.onChange), weakNode](bool check) {
                PipelineContext::SetCallBackNode(weakNode);
                arkCallback.Invoke(Converter::ArkValue<Ark_Boolean>(check));
            };
            RadioModelStatic::SetOnChangeEvent(frameNode, std::move(onEvent));
        },
        [] {});
    return result;
}
} // namespace
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::Converter {
template<>
void AssignCast(std::optional<RadioIndicatorType>& dst, const Ark_RadioIndicatorType& src)
{
    switch (src) {
        case ARK_RADIO_INDICATOR_TYPE_TICK:
            dst = RadioIndicatorType::TICK;
            break;
        case ARK_RADIO_INDICATOR_TYPE_DOT:
            dst = RadioIndicatorType::DOT;
            break;
        case ARK_RADIO_INDICATOR_TYPE_CUSTOM:
            dst = RadioIndicatorType::CUSTOM;
            break;
        default:
            LOGE("Unexpected enum value in Ark_RadioIndicatorType: %{public}d", src);
    }
}
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace RadioModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id, Ark_Int32 flags)
{
    auto frameNode = RadioModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // namespace RadioModifier
namespace RadioInterfaceModifier {
void SetRadioOptionsImpl(Ark_NativePointer node, const Ark_RadioOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    auto group = Converter::Convert<std::string>(options->group);
    RadioModelNG::SetRadioGroup(frameNode, group);
    auto radioValue = Converter::Convert<std::string>(options->value);
    RadioModelNG::SetRadioValue(frameNode, radioValue);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        auto indicatorType = Converter::OptConvert<RadioIndicatorType>(options->indicatorType);
        RadioModelStatic::SetRadioIndicatorType(frameNode, EnumToInt(indicatorType));
    }
    auto arkBuilder = Converter::OptConvert<CustomNodeBuilder>(options->indicatorBuilder);
    if (arkBuilder.has_value()) {
        CallbackHelper(arkBuilder.value()).BuildAsync([frameNode](const RefPtr<UINode>& uiNode) {
            auto builder = [uiNode]() {
                NG::ViewStackProcessor::GetInstance()->Push(uiNode);
            };
            RadioModelStatic::SetBuilder(frameNode, std::move(builder));
            }, node);
    }
}
} // namespace RadioInterfaceModifier
namespace RadioAttributeModifier {
void SetCheckedImpl(Ark_NativePointer node, const Opt_Union_Boolean_Bindable_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto isChecked = ProcessBindableChecked(frameNode, value);
    RadioModelStatic::SetChecked(frameNode, isChecked);
}
void SetOnChangeImpl(Ark_NativePointer node, const Opt_OnRadioChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto optCallback = Converter::GetOptPtr(value);
    ChangeEvent onEvent = {};
    if (optCallback.has_value()) {
        onEvent = [arkCallback = CallbackHelper(*optCallback)](const bool param) {
            auto arkValue = Converter::ArkValue<Ark_Boolean>(param);
            arkCallback.Invoke(arkValue);
        };
    }
    RadioModelNG::SetOnChange(frameNode, std::move(onEvent));
}
void SetRadioStyleImpl(Ark_NativePointer node, const Opt_RadioStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto style = Converter::OptConvertPtr<Converter::RadioStyle>(value);
    if (style) {
        RadioModelStatic::SetCheckedBackgroundColor(frameNode, style->checkedBackgroundColor);
        RadioModelStatic::SetUncheckedBorderColor(frameNode, style->uncheckedBorderColor);
        RadioModelStatic::SetIndicatorColor(frameNode, style->indicatorColor);
    } else {
        RadioModelStatic::SetCheckedBackgroundColor(frameNode, std::nullopt);
        RadioModelStatic::SetUncheckedBorderColor(frameNode, std::nullopt);
        RadioModelStatic::SetIndicatorColor(frameNode, std::nullopt);
    }
}
void ContentModifierRadioImpl(Ark_NativePointer node,
                              const Ark_Object* contentModifier,
                              const RadioModifierBuilder* builder)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(contentModifier);
    CHECK_NULL_VOID(builder);
    auto objectKeeper = std::make_shared<ObjectKeeper>(*contentModifier);
    auto builderFunc = [arkBuilder = CallbackHelper(*builder), node, frameNode, objectKeeper](
        RadioConfiguration config) -> RefPtr<FrameNode> {
        Ark_ContentModifier contentModifier = (*objectKeeper).get();
        Ark_RadioConfiguration arkConfig;
        arkConfig.contentModifier = contentModifier;
        arkConfig.enabled = Converter::ArkValue<Ark_Boolean>(config.enabled_);
        arkConfig.value = Converter::ArkValue<Ark_String>(config.value_, Converter::FC);
        arkConfig.checked = Converter::ArkValue<Ark_Boolean>(config.checked_);
        auto triggerCallback = CallbackKeeper::Claim<Callback_Boolean_Void>([frameNode](bool change) {
            RadioModelNG::SetChangeValue(frameNode, change);
        });
        arkConfig.triggerChange = triggerCallback.ArkValue();
        auto boxNode = GeneratedApiImpl::GetContentNode(node);
        if (boxNode == nullptr) {
            boxNode = CommonViewModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
            GeneratedApiImpl::SetContentNode(node, boxNode);
        }
        arkBuilder.BuildAsync([boxNode](const RefPtr<UINode>& uiNode) mutable {
            auto old = boxNode->GetChildAtIndex(0);
            if (old != nullptr) {
                boxNode->RemoveChildSilently(old);
            }
            boxNode->AddChild(uiNode);
            boxNode->MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE);
            }, node, arkConfig);
        return boxNode;
    };
    RadioModelNG::SetBuilderFunc(frameNode, std::move(builderFunc));
}
void ResetContentModifierRadioImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    RadioModelNG::SetBuilderFunc(frameNode, nullptr);
}
} // namespace RadioAttributeModifier
const GENERATED_ArkUIRadioModifier* GetRadioStaticModifier()
{
    static const GENERATED_ArkUIRadioModifier ArkUIRadioModifierImpl {
        RadioModifier::ConstructImpl,
        RadioInterfaceModifier::SetRadioOptionsImpl,
        RadioAttributeModifier::SetCheckedImpl,
        RadioAttributeModifier::SetOnChangeImpl,
        RadioAttributeModifier::SetRadioStyleImpl,
    };
    return &ArkUIRadioModifierImpl;
}

const GENERATED_ArkUIRadioContentModifier* GetRadioStaticContentModifier()
{
    static const GENERATED_ArkUIRadioContentModifier ArkUIRadioStaticContentModifierImpl {
        RadioAttributeModifier::ContentModifierRadioImpl,
        RadioAttributeModifier::ResetContentModifierRadioImpl,
    };
    return &ArkUIRadioStaticContentModifierImpl;
}
} // namespace OHOS::Ace::NG::GeneratedModifier