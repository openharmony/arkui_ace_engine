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

#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/pattern/button/button_model_ng.h"
#include "core/components_ng/pattern/checkbox/checkbox_model_ng.h"
#include "core/components_ng/pattern/checkbox/checkbox_model_static.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_model_ng.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_model_static.h"
#include "core/components_ng/pattern/common_view/common_view_model_ng.h"
#include "core/components_ng/pattern/data_panel/data_panel_model_ng.h"
#include "core/components_ng/pattern/gauge/bridge/content_modifier_helper.h"
#include "core/components_ng/pattern/gauge/bridge/gauge_dynamic_module.h"
#include "core/components_ng/pattern/gauge/gauge_model_ng.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_model_ng.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/progress/progress_model_ng.h"
#include "core/components_ng/pattern/radio/radio_model_ng.h"
#include "core/components_ng/pattern/rating/rating_model_ng.h"
#include "core/components_ng/pattern/rating/rating_model_static.h"
#include "core/components_ng/pattern/slider/slider_model_ng.h"
#include "core/components_ng/pattern/text_clock/text_clock_model_ng.h"
#include "core/components_ng/pattern/texttimer/text_timer_model_ng.h"
#include "core/components_ng/pattern/toggle/toggle_model_ng.h"
#include "core/components_ng/pattern/toggle/toggle_model_static.h"
#include "core/interfaces/native/implementation/checkbox_group_configuration_peer.h"
#include "core/interfaces/native/implementation/frame_node_peer_impl.h"
#include "core/interfaces/native/implementation/menu_item_configuration_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/object_keeper.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ContentModifierHelperAccessor {
void ContentModifierButtonImpl(Ark_NativePointer node,
                               const Ark_Object* contentModifier,
                               const ButtonModifierBuilder* builder)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto objectKeeper = std::make_shared<ObjectKeeper>(*contentModifier);
    auto builderFunc = [arkBuilder = CallbackHelper(*builder), node, frameNode, objectKeeper](
        ButtonConfiguration config) -> RefPtr<FrameNode> {
        Ark_ContentModifier contentModifier = (*objectKeeper).get();
        Ark_ButtonConfiguration arkConfig;
        arkConfig.contentModifier = contentModifier;
        arkConfig.enabled = Converter::ArkValue<Ark_Boolean>(config.enabled_);
        arkConfig.label = Converter::ArkValue<Ark_String>(config.label_, Converter::FC);
        arkConfig.pressed = Converter::ArkValue<Ark_Boolean>(config.pressed_);
        std::function<void(Ark_Float64, Ark_Float64)> handler = [frameNode](Ark_Float64 arkX, Ark_Float64 arkY) {
            auto x = Converter::Convert<int32_t>(arkX);
            auto y = Converter::Convert<int32_t>(arkY);
            ButtonModelNG::TriggerClick(frameNode, x, y);
        };
        auto triggerCallback = CallbackKeeper::Claim<ButtonTriggerClickCallback>(handler);
        arkConfig.triggerClick = triggerCallback.ArkValue();
        auto btnNode = CommonViewModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
        arkBuilder.BuildAsync([btnNode](const RefPtr<UINode>& uiNode) mutable {
            btnNode->AddChild(uiNode);
            btnNode->MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE);
            }, node, arkConfig);
        return btnNode;
    };
    ButtonModelNG::SetBuilderFunc(frameNode, std::move(builderFunc));
}
void ResetContentModifierButtonImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetBuilderFunc(frameNode, nullptr);
}
void ContentModifierCheckBoxImpl(Ark_NativePointer node,
                                 const Ark_Object* contentModifier,
                                 const CheckBoxModifierBuilder* builder)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto objectKeeper = std::make_shared<ObjectKeeper>(*contentModifier);
    auto builderFunc = [arkBuilder = CallbackHelper(*builder), node, frameNode, objectKeeper](
        CheckBoxConfiguration config) -> RefPtr<FrameNode> {
        Ark_ContentModifier contentModifier = (*objectKeeper).get();
        Ark_CheckBoxConfiguration arkConfig;
        arkConfig.contentModifier = contentModifier;
        arkConfig.enabled = Converter::ArkValue<Ark_Boolean>(config.enabled_);
        arkConfig.name = Converter::ArkValue<Ark_String>(config.name_, Converter::FC);
        arkConfig.selected = Converter::ArkValue<Ark_Boolean>(config.selected_);
        auto handler = [frameNode](Ark_Boolean retValue) {
            CheckBoxModelStatic::TriggerChange(frameNode, Converter::Convert<bool>(retValue));
        };
        auto triggerCallback = CallbackKeeper::Claim<Callback_Boolean_Void>(handler);
        arkConfig.triggerChange = triggerCallback.ArkValue();
        auto boxNode = CommonViewModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
        arkBuilder.BuildAsync([boxNode](const RefPtr<UINode>& uiNode) mutable {
            boxNode->AddChild(uiNode);
            boxNode->MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE);
            }, node, arkConfig);
        return boxNode;
    };
    CheckBoxModelNG::SetBuilderFunc(frameNode, std::move(builderFunc));
}
void ResetContentModifierCheckBoxImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::SetBuilderFunc(frameNode, nullptr);
}
void ContentModifierDataPanelImpl(Ark_NativePointer node,
                                  const Ark_Object* contentModifier,
                                  const DataPanelModifierBuilder* builder)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto objectKeeper = std::make_shared<ObjectKeeper>(*contentModifier);
    auto builderFunc = [arkBuilder = CallbackHelper(*builder), node, frameNode, objectKeeper](
        DataPanelConfiguration config) -> RefPtr<FrameNode> {
        Ark_ContentModifier contentModifier = (*objectKeeper).get();
        Ark_DataPanelConfiguration arkConfig;
        arkConfig.contentModifier = contentModifier;
        arkConfig.enabled = Converter::ArkValue<Ark_Boolean>(config.enabled_);
        arkConfig.values = Converter::ArkValue<Array_Float64>(config.values_, Converter::FC);
        arkConfig.maxValue = Converter::ArkValue<Ark_Float64>(config.maxValue_);
        auto panelNode = CommonViewModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
        arkBuilder.BuildAsync([panelNode](const RefPtr<UINode>& uiNode) mutable {
            panelNode->AddChild(uiNode);
            panelNode->MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE);
            }, node, arkConfig);
        return panelNode;
    };
    DataPanelModelNG::SetBuilderFunc(frameNode, std::move(builderFunc));
}
void ResetContentModifierDataPanelImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    DataPanelModelNG::SetBuilderFunc(frameNode, nullptr);
}
void ContentModifierGaugeImpl(
    Ark_NativePointer node, const Ark_Object* contentModifier, const GaugeModifierBuilder* builder)
{
    auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("gauge");
    CHECK_NULL_VOID(module);
    auto* modifier =
        reinterpret_cast<const GENERATED_ArkUIGaugeContentModifier*>(module->GetCustomModifier("contentModifier"));
    CHECK_NULL_VOID(modifier);
    modifier->contentModifierGaugeImpl(node, contentModifier, builder);
}
void ResetContentModifierGaugeImpl(Ark_NativePointer node)
{
    auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("gauge");
    CHECK_NULL_VOID(module);
    auto* modifier =
        reinterpret_cast<const GENERATED_ArkUIGaugeContentModifier*>(module->GetCustomModifier("contentModifier"));
    CHECK_NULL_VOID(modifier);
    modifier->resetContentModifierGaugeImpl(node);
}
void ContentModifierLoadingProgressImpl(Ark_NativePointer node,
                                        const Ark_Object* contentModifier,
                                        const LoadingProgressModifierBuilder* builder)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(contentModifier);
    CHECK_NULL_VOID(builder);
    auto objectKeeper = std::make_shared<ObjectKeeper>(*contentModifier);
    auto builderFunc = [arkBuilder = CallbackHelper(*builder), node, frameNode, objectKeeper](
        LoadingProgressConfiguration config) -> RefPtr<FrameNode> {
        Ark_ContentModifier contentModifier = (*objectKeeper).get();
        Ark_LoadingProgressConfiguration arkConfig;
        arkConfig.contentModifier = contentModifier;
        arkConfig.enabled = Converter::ArkValue<Ark_Boolean>(config.enabled_);
        arkConfig.enableLoading = Converter::ArkValue<Ark_Boolean>(config.enableloading_);
        auto boxNode = CommonViewModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
        arkBuilder.BuildAsync([boxNode](const RefPtr<UINode>& uiNode) mutable {
            boxNode->AddChild(uiNode);
            boxNode->MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE);
            }, node, arkConfig);
        return boxNode;
    };
    LoadingProgressModelNG::SetBuilderFunc(frameNode, std::move(builderFunc));
}
void ResetContentModifierLoadingProgressImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    LoadingProgressModelNG::SetBuilderFunc(frameNode, nullptr);
}
void ContentModifierProgressImpl(Ark_NativePointer node,
                                 const Ark_Object* contentModifier,
                                 const ProgressModifierBuilder* builder)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto objectKeeper = std::make_shared<ObjectKeeper>(*contentModifier);
    auto builderFunc = [arkBuilder = CallbackHelper(*builder), node, frameNode, objectKeeper](
        ProgressConfiguration config) -> RefPtr<FrameNode> {
        Ark_ContentModifier contentModifier = (*objectKeeper).get();
        Ark_ProgressConfiguration arkConfig;
        arkConfig.contentModifier = contentModifier;
        arkConfig.enabled = Converter::ArkValue<Ark_Boolean>(config.enabled_);
        arkConfig.value = Converter::ArkValue<Ark_Float64>(config.value_);
        arkConfig.total = Converter::ArkValue<Ark_Float64>(config.total_);
        auto boxNode = CommonViewModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
        arkBuilder.BuildAsync([boxNode](const RefPtr<UINode>& uiNode) mutable {
            boxNode->AddChild(uiNode);
            boxNode->MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE);
            }, node, arkConfig);
        return boxNode;
    };
    ProgressModelNG::SetBuilderFunc(frameNode, std::move(builderFunc));
}
void ResetContentModifierProgressImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ProgressModelNG::SetBuilderFunc(frameNode, nullptr);
}
void ContentModifierRadioImpl(Ark_NativePointer node,
                              const Ark_Object* contentModifier,
                              const RadioModifierBuilder* builder)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
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
        auto radioNode = CommonViewModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
        arkBuilder.BuildAsync([radioNode](const RefPtr<UINode>& uiNode) mutable {
            radioNode->AddChild(uiNode);
            radioNode->MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE);
            }, node, arkConfig);
        return radioNode;
    };
    RadioModelNG::SetBuilderFunc(frameNode, std::move(builderFunc));
}
void ResetContentModifierRadioImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    RadioModelNG::SetBuilderFunc(frameNode, nullptr);
}
void ContentModifierRatingImpl(Ark_NativePointer node,
                               const Ark_Object* contentModifier,
                               const RatingModifierBuilder* builder)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto objectKeeper = std::make_shared<ObjectKeeper>(*contentModifier);
    auto builderFunc = [arkBuilder = CallbackHelper(*builder), node, frameNode, objectKeeper](
    RatingConfiguration config) -> RefPtr<FrameNode> {
        Ark_ContentModifier contentModifier = (*objectKeeper).get();
        Ark_RatingConfiguration arkConfig;
        arkConfig.enabled = Converter::ArkValue<Ark_Boolean>(config.enabled_);
        arkConfig.contentModifier = contentModifier;
        arkConfig.rating = Converter::ArkValue<Ark_Float64>(config.rating_);
        arkConfig.indicator = Converter::ArkValue<Ark_Boolean>(config.isIndicator_);
        arkConfig.stars = Converter::ArkValue<Ark_Int32>(config.starNum_);
        arkConfig.stepSize = Converter::ArkValue<Ark_Float64>(config.stepSize_);
        auto handler = [frameNode](Ark_Float64 retValue) {
            RatingModelStatic::TriggerChange(frameNode, Converter::Convert<double>(retValue));
        };
        auto triggerCallback = CallbackKeeper::Claim<Callback_F64_Void>(handler);
        arkConfig.triggerChange = triggerCallback.ArkValue();
        auto boxNode = CommonViewModelNG::CreateFrameNode(ViewStackProcessor::GetInstance()->ClaimNodeId());
        arkBuilder.BuildAsync([boxNode](const RefPtr<UINode>& uiNode) mutable {
            boxNode->AddChild(uiNode);
            boxNode->MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE);
            }, node, arkConfig);
        return boxNode;
    };
    RatingModelNG::SetBuilderFunc(frameNode, std::move(builderFunc));
}
void ResetContentModifierRatingImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    RatingModelNG::SetBuilderFunc(frameNode, nullptr);
}
void ContentModifierMenuItemImpl(Ark_NativePointer node,
                                 const Ark_Object* contentModifier,
                                 const MenuItemModifierBuilder* builder)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto objectKeeper = std::make_shared<ObjectKeeper>(*contentModifier);
    auto builderFunc = [arkBuilder = CallbackHelper(*builder), node, frameNode, objectKeeper](
        MenuItemConfiguration config) -> RefPtr<FrameNode> {
        Ark_ContentModifier contentModifier = (*objectKeeper).get();
        Ark_MenuItemConfiguration arkConfig = PeerUtils::CreatePeer<MenuItemConfigurationPeer>();
        arkConfig->contentModifier_ = contentModifier;
        arkConfig->enabled_ = config.enabled_;
        arkConfig->value_ = config.value_;
        arkConfig->icon_ = config.icon_;
        arkConfig->symbolModifier_ = config.symbolModifier_;
        arkConfig->selected_ = config.selected_;
        arkConfig->index_ = config.index_;
        arkConfig->node_ = node;
        auto boxNode = CommonViewModelNG::CreateFrameNode(ViewStackProcessor::GetInstance()->ClaimNodeId());
        arkBuilder.BuildAsync([boxNode](const RefPtr<UINode>& uiNode) mutable {
            boxNode->AddChild(uiNode);
            boxNode->MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE);
            }, node, arkConfig);
        return boxNode;
    };
    SelectModelNG::SetBuilderFunc(frameNode, std::move(builderFunc));
}
void ResetContentModifierMenuItemImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SelectModelNG::ResetBuilderFunc(frameNode);
}
void ContentModifierSliderImpl(Ark_NativePointer node,
                               const Ark_Object* contentModifier,
                               const SliderModifierBuilder* builder)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto objectKeeper = std::make_shared<ObjectKeeper>(*contentModifier);
    auto builderFunc = [arkBuilder = CallbackHelper(*builder), node, frameNode, objectKeeper](
        const SliderConfiguration& config) -> RefPtr<FrameNode> {
        Ark_ContentModifier contentModifier = (*objectKeeper).get();
        Ark_SliderConfiguration arkConfig;
        arkConfig.contentModifier = contentModifier;
        arkConfig.value = Converter::ArkValue<Ark_Float64>(config.value_);
        arkConfig.min = Converter::ArkValue<Ark_Float64>(config.min_);
        arkConfig.max = Converter::ArkValue<Ark_Float64>(config.max_);
        arkConfig.enabled = Converter::ArkValue<Ark_Boolean>(config.enabled_);
        arkConfig.step = Converter::ArkValue<Ark_Float64>(config.step_);
        auto triggerCallback = CallbackKeeper::Claim<SliderTriggerChangeCallback>(
            [frameNode](Ark_Float64 value, Ark_SliderChangeMode mode) {
                SliderModelNG::SetChangeValue(frameNode, Converter::Convert<double>(value), mode);
        });
        arkConfig.triggerChange = triggerCallback.ArkValue();

        auto sliderNode = CommonViewModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
        arkBuilder.BuildAsync([sliderNode](const RefPtr<UINode>& uiNode) mutable {
            sliderNode->AddChild(uiNode);
            sliderNode->MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE);
            }, node, arkConfig);
        return sliderNode;
    };
    SliderModelNG::SetBuilderFunc(frameNode, std::move(builderFunc));
}
void ResetContentModifierSliderImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetBuilderFunc(frameNode, nullptr);
}
void ContentModifierTextClockImpl(Ark_NativePointer node,
                                  const Ark_Object* contentModifier,
                                  const TextClockModifierBuilder* builder)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto objectKeeper = std::make_shared<ObjectKeeper>(*contentModifier);
    auto builderFunc = [arkBuilder = CallbackHelper(*builder), node, frameNode, objectKeeper](
        TextClockConfiguration config) -> RefPtr<FrameNode> {
        Ark_ContentModifier contentModifier = (*objectKeeper).get();
        Ark_TextClockConfiguration arkConfig;
        arkConfig.contentModifier = contentModifier;
        arkConfig.enabled = Converter::ArkValue<Ark_Boolean>(config.enabled_);
        arkConfig.timeZoneOffset = Converter::ArkValue<Ark_Float64>(config.timeZoneOffset_);
        arkConfig.started = Converter::ArkValue<Ark_Boolean>(config.started_);
        arkConfig.timeValue = Converter::ArkValue<Ark_Int64>(config.timeValue_);
        auto boxNode = CommonViewModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
        arkBuilder.BuildAsync([boxNode](const RefPtr<UINode>& uiNode) mutable {
            boxNode->AddChild(uiNode);
            boxNode->MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE);
            }, node, arkConfig);
        return boxNode;
    };
    TextClockModelNG::SetBuilderFunc(frameNode, std::move(builderFunc));
}
void ResetContentModifierTextClockImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextClockModelNG::SetBuilderFunc(frameNode, nullptr);
}
void ContentModifierTextTimerImpl(Ark_NativePointer node,
                                  const Ark_Object* contentModifier,
                                  const TextTimerModifierBuilder* builder)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto objectKeeper = std::make_shared<ObjectKeeper>(*contentModifier);
    auto builderFunc = [arkBuilder = CallbackHelper(*builder), node, frameNode, objectKeeper](
        TextTimerConfiguration config) -> RefPtr<FrameNode> {
        Ark_ContentModifier contentModifier = (*objectKeeper).get();
        Ark_TextTimerConfiguration arkConfig;
        arkConfig.contentModifier = contentModifier;
        arkConfig.enabled = Converter::ArkValue<Ark_Boolean>(config.enabled_);
        arkConfig.count = Converter::ArkValue<Ark_Int64>(config.count_);
        arkConfig.isCountDown = Converter::ArkValue<Ark_Boolean>(config.isCountDown_);
        arkConfig.started = Converter::ArkValue<Ark_Boolean>(config.started_);
        arkConfig.elapsedTime = Converter::ArkValue<Ark_Int64>(static_cast<int32_t>(config.elapsedTime_));
        auto boxNode = CommonViewModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
        arkBuilder.BuildAsync([boxNode](const RefPtr<UINode>& uiNode) mutable {
            boxNode->AddChild(uiNode);
            boxNode->MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE);
            }, node, arkConfig);
        return boxNode;
    };
    TextTimerModelNG::SetBuilderFunc(frameNode, std::move(builderFunc));
}
void ResetContentModifierTextTimerImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextTimerModelNG::SetBuilderFunc(frameNode, nullptr);
}
void ContentModifierToggleImpl(Ark_NativePointer node,
                               const Ark_Object* contentModifier,
                               const ToggleModifierBuilder* builder)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(contentModifier);
    CHECK_NULL_VOID(builder);
    auto objectKeeper = std::make_shared<ObjectKeeper>(*contentModifier);
    auto builderFunc = [arkBuilder = CallbackHelper(*builder), node, frameNode, objectKeeper](
        ToggleConfiguration config) -> RefPtr<FrameNode> {
        Ark_ContentModifier contentModifier = (*objectKeeper).get();
        Ark_ToggleConfiguration arkConfig;
        arkConfig.contentModifier = contentModifier;
        arkConfig.enabled = Converter::ArkValue<Ark_Boolean>(config.enabled_);
        arkConfig.isOn = Converter::ArkValue<Ark_Boolean>(config.isOn_);
        arkConfig.toggleEnabled = Converter::ArkValue<Ark_Boolean>(config.enabled_);
        auto handler = [frameNode](Ark_Boolean retValue) {
            ToggleModelStatic::TriggerChange(frameNode, Converter::Convert<bool>(retValue));
        };
        auto triggerCallback = CallbackKeeper::Claim<Callback_Boolean_Void>(handler);
        arkConfig.triggerChange = triggerCallback.ArkValue();
        auto boxNode = CommonViewModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
        arkBuilder.BuildAsync([boxNode](const RefPtr<UINode>& uiNode) mutable {
            boxNode->AddChild(uiNode);
            boxNode->MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE);
            }, node, arkConfig);
        return boxNode;
    };
    ToggleModelNG::SetBuilderFunc(frameNode, std::move(builderFunc));
}
void ResetContentModifierToggleImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ToggleModelNG::SetBuilderFunc(frameNode, nullptr);
}
void ContentModifierCheckBoxGroupImpl(Ark_NativePointer node,
                                    const Ark_Object* contentModifier,
                                    const CheckBoxGroupModifierBuilder* builder)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(contentModifier);
    CHECK_NULL_VOID(builder);
    auto objectKeeper = std::make_shared<ObjectKeeper>(*contentModifier);
    auto builderFunc = [arkBuilder = CallbackHelper(*builder), node, frameNode, objectKeeper](
        CheckBoxGroupConfiguration config) -> RefPtr<FrameNode> {
        Ark_ContentModifier contentModifier = (*objectKeeper).get();
        Ark_CheckBoxGroupConfiguration arkConfig = PeerUtils::CreatePeer<CheckBoxGroupConfigurationPeer>();
        arkConfig->contentModifier_ = contentModifier;
        arkConfig->enabled_ = config.enabled_;
        arkConfig->name_ = config.name_;
        arkConfig->status_ = Converter::ArkValue<Ark_SelectStatus>(static_cast<int>(config.status_));
        arkConfig->node_ = node;
        auto handler = [frameNode](Ark_Boolean retValue) {
            CheckBoxGroupModelStatic::TriggerChange(frameNode, Converter::Convert<bool>(retValue));
        };
        auto triggerCallback = CallbackKeeper::Claim<Callback_Boolean_Void>(handler);
        arkConfig->triggerChange_ = triggerCallback.ArkValue();
        auto boxNode = CommonViewModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
        arkBuilder.BuildAsync([boxNode](const RefPtr<UINode>& uiNode) mutable {
            boxNode->AddChild(uiNode);
            boxNode->MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE);
            }, node, arkConfig);
        return boxNode;
    };
    CheckBoxGroupModelNG::SetBuilderFunc(frameNode, std::move(builderFunc));
}
void ResetContentModifierCheckBoxGroupImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxGroupModelNG::SetBuilderFunc(frameNode, nullptr);
}
} // ContentModifierHelperAccessor
const GENERATED_ArkUIContentModifierHelperAccessor* GetContentModifierHelperAccessor()
{
    static const GENERATED_ArkUIContentModifierHelperAccessor ContentModifierHelperAccessorImpl {
        ContentModifierHelperAccessor::ContentModifierButtonImpl,
        ContentModifierHelperAccessor::ResetContentModifierButtonImpl,
        ContentModifierHelperAccessor::ContentModifierCheckBoxImpl,
        ContentModifierHelperAccessor::ResetContentModifierCheckBoxImpl,
        ContentModifierHelperAccessor::ContentModifierDataPanelImpl,
        ContentModifierHelperAccessor::ResetContentModifierDataPanelImpl,
        ContentModifierHelperAccessor::ContentModifierGaugeImpl,
        ContentModifierHelperAccessor::ResetContentModifierGaugeImpl,
        ContentModifierHelperAccessor::ContentModifierLoadingProgressImpl,
        ContentModifierHelperAccessor::ResetContentModifierLoadingProgressImpl,
        ContentModifierHelperAccessor::ContentModifierProgressImpl,
        ContentModifierHelperAccessor::ResetContentModifierProgressImpl,
        ContentModifierHelperAccessor::ContentModifierRadioImpl,
        ContentModifierHelperAccessor::ResetContentModifierRadioImpl,
        ContentModifierHelperAccessor::ContentModifierRatingImpl,
        ContentModifierHelperAccessor::ResetContentModifierRatingImpl,
        ContentModifierHelperAccessor::ContentModifierMenuItemImpl,
        ContentModifierHelperAccessor::ResetContentModifierMenuItemImpl,
        ContentModifierHelperAccessor::ContentModifierSliderImpl,
        ContentModifierHelperAccessor::ResetContentModifierSliderImpl,
        ContentModifierHelperAccessor::ContentModifierTextClockImpl,
        ContentModifierHelperAccessor::ResetContentModifierTextClockImpl,
        ContentModifierHelperAccessor::ContentModifierTextTimerImpl,
        ContentModifierHelperAccessor::ResetContentModifierTextTimerImpl,
        ContentModifierHelperAccessor::ContentModifierToggleImpl,
        ContentModifierHelperAccessor::ResetContentModifierToggleImpl,
        ContentModifierHelperAccessor::ContentModifierCheckBoxGroupImpl,
        ContentModifierHelperAccessor::ResetContentModifierCheckBoxGroupImpl,
    };
    return &ContentModifierHelperAccessorImpl;
}

}
