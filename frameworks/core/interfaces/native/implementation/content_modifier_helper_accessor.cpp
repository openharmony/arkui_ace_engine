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
#include "core/components_ng/pattern/button/button_model_ng.h"
#include "core/components_ng/pattern/checkbox/checkbox_model_ng.h"
#include "core/components_ng/pattern/radio/radio_model_ng.h"
#include "core/components_ng/pattern/rating/rating_model_ng.h"
#include "core/components_ng/pattern/slider/slider_model_ng.h"
#include "core/components_ng/pattern/toggle/toggle_model_ng.h"
#include "core/interfaces/native/implementation/frame_node_peer_impl.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ContentModifierHelperAccessor {
void ContentModifierButtonImpl(
    Ark_NativePointer node, const Ark_Object* contentModifier, const ButtonModifierBuilder* builder)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto weakNode = AceType::WeakClaim(frameNode);
    ButtonModelNG::SetBuilderFunc(frameNode,
        [weakNode, node, contentModifier, arkCallback = CallbackHelper(*builder)](
            ButtonConfiguration config) -> RefPtr<FrameNode> {
            Ark_ButtonConfiguration buttonConfig;
            buttonConfig.label = Converter::ArkValue<Ark_String>(config.label_);
            buttonConfig.pressed = Converter::ArkValue<Ark_Boolean>(config.pressed_);
            buttonConfig.enabled = Converter::ArkValue<Ark_Boolean>(config.enabled_);
            buttonConfig.triggerClick = CallbackKeeper::DefineButtonTriggerClickCallback<ButtonTriggerClickCallback>(
                [weakNode](Ark_Number xPos, Ark_Number yPos) {
                    auto buttonNode = weakNode.Upgrade();
                    CHECK_NULL_VOID(buttonNode);
                    ButtonModelNG::TriggerClick(AceType::RawPtr(buttonNode), Converter::Convert<float>(xPos),
                        Converter::Convert<float>(yPos));
                });
            auto returnNode =
                arkCallback.InvokeWithObtainResult<Ark_NativePointer, Callback_Pointer_Void>(node, buttonConfig);
            if (returnNode) {
                auto contentNode = FrameNodePeer::GetFrameNodeByPeer(reinterpret_cast<Ark_FrameNode>(returnNode));
                return contentNode;
            }
            return nullptr;
        });
}

void ResetContentModifierButtonImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetBuilderFunc(frameNode, nullptr);
}

void ContentModifierCheckBoxImpl(
    Ark_NativePointer node, const Ark_Object* contentModifier, const CheckBoxModifierBuilder* builder)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto weakNode = AceType::WeakClaim(frameNode);
    CheckBoxModelNG::SetBuilderFunc(frameNode,
        [weakNode, node, contentModifier, arkCallback = CallbackHelper(*builder)](
            CheckBoxConfiguration config) -> RefPtr<FrameNode> {
            Ark_CheckBoxConfiguration checkboxConfig;
            checkboxConfig.name = Converter::ArkValue<Ark_String>(config.name_);
            checkboxConfig.selected = Converter::ArkValue<Ark_Boolean>(config.selected_);
            checkboxConfig.enabled = Converter::ArkValue<Ark_Boolean>(config.enabled_);
            checkboxConfig.triggerChange =
                CallbackKeeper::DefineBooleanCallback<Callback_Boolean_Void>([weakNode](bool change) {
                    auto checkboxNode = weakNode.Upgrade();
                    CHECK_NULL_VOID(checkboxNode);
                    CheckBoxModelNG::SetChangeValue(AceType::RawPtr(checkboxNode), change);
                });
            auto returnNode =
                arkCallback.InvokeWithObtainResult<Ark_NativePointer, Callback_Pointer_Void>(node, checkboxConfig);
            if (returnNode) {
                auto contentNode = FrameNodePeer::GetFrameNodeByPeer(reinterpret_cast<Ark_FrameNode>(returnNode));
                return contentNode;
            }
            return nullptr;
        });
}

void ResetContentModifierCheckBoxImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetBuilderFunc(frameNode, nullptr);
}

void ContentModifierRadioImpl(
    Ark_NativePointer node, const Ark_Object* contentModifier, const RadioModifierBuilder* builder)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto weakNode = AceType::WeakClaim(frameNode);
    RadioModelNG::SetBuilderFunc(frameNode,
        [weakNode, node, contentModifier, arkCallback = CallbackHelper(*builder)](
            RadioConfiguration config) -> RefPtr<FrameNode> {
            Ark_RadioConfiguration radioConfig;
            radioConfig.value = Converter::ArkValue<Ark_String>(config.value_);
            radioConfig.checked = Converter::ArkValue<Ark_Boolean>(config.checked_);
            radioConfig.enabled = Converter::ArkValue<Ark_Boolean>(config.enabled_);
            radioConfig.triggerChange =
                CallbackKeeper::DefineBooleanCallback<Callback_Boolean_Void>([weakNode](bool change) {
                    auto radioNode = weakNode.Upgrade();
                    CHECK_NULL_VOID(radioNode);
                    RadioModelNG::SetChangeValue(AceType::RawPtr(radioNode), change);
                });
            auto returnNode =
                arkCallback.InvokeWithObtainResult<Ark_NativePointer, Callback_Pointer_Void>(node, radioConfig);
            if (returnNode) {
                auto contentNode = FrameNodePeer::GetFrameNodeByPeer(reinterpret_cast<Ark_FrameNode>(returnNode));
                return contentNode;
            }
            return nullptr;
        });
}
void ResetContentModifierRadioImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RadioModelNG::SetBuilderFunc(frameNode, nullptr);
}

void ContentModifierRatingImpl(
    Ark_NativePointer node, const Ark_Object* contentModifier, const RatingModifierBuilder* builder)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto weakNode = AceType::WeakClaim(frameNode);
    RatingModelNG::SetBuilderFunc(frameNode,
        [weakNode, node, contentModifier, arkCallback = CallbackHelper(*builder)](
            RatingConfiguration config) -> RefPtr<FrameNode> {
            Ark_RatingConfiguration ratingConfig;
            ratingConfig.rating = Converter::ArkValue<Ark_Number>(config.rating_);
            ratingConfig.indicator = Converter::ArkValue<Ark_Boolean>(config.isIndicator_);
            ratingConfig.enabled = Converter::ArkValue<Ark_Boolean>(config.enabled_);
            ratingConfig.stars = Converter::ArkValue<Ark_Number>(config.starNum_);
            ratingConfig.stepSize = Converter::ArkValue<Ark_Number>(config.stepSize_);
            ratingConfig.triggerChange =
                CallbackKeeper::DefineNumberCallback<Callback_Number_Void>([weakNode](Ark_Number value) {
                    auto ratingNode = weakNode.Upgrade();
                    CHECK_NULL_VOID(ratingNode);
                    auto rating = Converter::Convert<double>(value);
                    RatingModelNG::SetChangeValue(AceType::RawPtr(ratingNode), rating);
                });
            auto returnNode =
                arkCallback.InvokeWithObtainResult<Ark_NativePointer, Callback_Pointer_Void>(node, ratingConfig);
            if (returnNode) {
                auto contentNode = FrameNodePeer::GetFrameNodeByPeer(reinterpret_cast<Ark_FrameNode>(returnNode));
                return contentNode;
            }
            return nullptr;
        });
}

void ResetContentModifierRatingImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RatingModelNG::SetBuilderFunc(frameNode, nullptr);
}

void ContentModifierSliderImpl(
    Ark_NativePointer node, const Ark_Object* contentModifier, const SliderModifierBuilder* builder)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto weakNode = AceType::WeakClaim(frameNode);
    SliderModelNG::SetBuilderFunc(frameNode,
        [weakNode, node, contentModifier, arkCallback = CallbackHelper(*builder)](
            SliderConfiguration config) -> RefPtr<FrameNode> {
            Ark_SliderConfiguration sliderConfig;
            sliderConfig.value = Converter::ArkValue<Ark_Number>(config.value_);
            sliderConfig.min = Converter::ArkValue<Ark_Number>(config.min_);
            sliderConfig.max = Converter::ArkValue<Ark_Number>(config.max_);
            sliderConfig.enabled = Converter::ArkValue<Ark_Boolean>(config.enabled_);
            sliderConfig.step = Converter::ArkValue<Ark_Number>(config.step_);
            sliderConfig.triggerChange = CallbackKeeper::DefineSliderTriggerChangeCallback<SliderTriggerChangeCallback>(
                [weakNode](Ark_Number value, Ark_SliderChangeMode mode) {
                    auto sliderNode = weakNode.Upgrade();
                    CHECK_NULL_VOID(sliderNode);

                    SliderModelNG::SetChangeValue(
                        AceType::RawPtr(sliderNode), Converter::Convert<double>(value), mode);
                });
            auto returnNode =
                arkCallback.InvokeWithObtainResult<Ark_NativePointer, Callback_Pointer_Void>(node, sliderConfig);
            if (returnNode) {
                auto contentNode = FrameNodePeer::GetFrameNodeByPeer(reinterpret_cast<Ark_FrameNode>(returnNode));
                return contentNode;
            }
            return nullptr;
        });
}

void ResetContentModifierSliderImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RatingModelNG::SetBuilderFunc(frameNode, nullptr);
}

void ContentModifierToggleImpl(
    Ark_NativePointer node, const Ark_Object* contentModifier, const ToggleModifierBuilder* builder)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto weakNode = AceType::WeakClaim(frameNode);
    ToggleModelNG::SetBuilderFunc(frameNode,
        [weakNode, node, contentModifier, arkCallback = CallbackHelper(*builder)](
            ToggleConfiguration config) -> RefPtr<FrameNode> {
            Ark_ToggleConfiguration toggleConfig;
            toggleConfig.isOn = Converter::ArkValue<Ark_Boolean>(config.isOn_);
            toggleConfig.enabled = Converter::ArkValue<Ark_Boolean>(config.enabled_);
            toggleConfig.triggerChange =
                CallbackKeeper::DefineBooleanCallback<Callback_Boolean_Void>([weakNode](bool change) {
                    auto togglNode = weakNode.Upgrade();
                    CHECK_NULL_VOID(togglNode);
                    ToggleModelNG::SetChangeValue(AceType::RawPtr(togglNode), change);
                });
            auto returnNode =
                arkCallback.InvokeWithObtainResult<Ark_NativePointer, Callback_Pointer_Void>(node, toggleConfig);
            if (returnNode) {
                auto contentNode = FrameNodePeer::GetFrameNodeByPeer(reinterpret_cast<Ark_FrameNode>(returnNode));
                return contentNode;
            }
            return nullptr;
        });
}
void ResetContentModifierToggleImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RadioModelNG::SetBuilderFunc(frameNode, nullptr);
}
} // namespace ContentModifierHelperAccessor
const GENERATED_ArkUIContentModifierHelperAccessor* GetContentModifierHelperAccessor()
{
    static const GENERATED_ArkUIContentModifierHelperAccessor ContentModifierHelperAccessorImpl {
        ContentModifierHelperAccessor::ContentModifierButtonImpl,
        ContentModifierHelperAccessor::ResetContentModifierButtonImpl,
        ContentModifierHelperAccessor::ContentModifierCheckBoxImpl,
        ContentModifierHelperAccessor::ResetContentModifierCheckBoxImpl,
        ContentModifierHelperAccessor::ContentModifierRadioImpl,
        ContentModifierHelperAccessor::ResetContentModifierRadioImpl,
        ContentModifierHelperAccessor::ContentModifierRatingImpl,
        ContentModifierHelperAccessor::ResetContentModifierRatingImpl,
        ContentModifierHelperAccessor::ContentModifierSliderImpl,
        ContentModifierHelperAccessor::ResetContentModifierSliderImpl,
        ContentModifierHelperAccessor::ContentModifierToggleImpl,
        ContentModifierHelperAccessor::ResetContentModifierToggleImpl,
    };
    return &ContentModifierHelperAccessorImpl;
}

} // namespace OHOS::Ace::NG::GeneratedModifier
