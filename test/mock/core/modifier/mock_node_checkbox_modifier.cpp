/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/checkbox/checkbox_model_ng.h"
#include "core/components_ng/pattern/checkbox/bridge/checkbox_custom_modifier.h"

namespace OHOS::Ace::NG {
const int32_t ERROR_INT_CODE = -1;

void SetSelect(ArkUINodeHandle node, ArkUI_Bool isSelected)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::SetSelect(frameNode, static_cast<bool>(isSelected));
}

void SetSelectedColor(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::SetSelectedColor(frameNode, Color(color));
}

void SetCheckboxOnChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onChange = reinterpret_cast<std::function<void(bool)>*>(callback);
        CheckBoxModelNG::SetOnChange(frameNode, std::move(*onChange));
    } else {
        CheckBoxModelNG::SetOnChange(frameNode, nullptr);
    }
}

void ResetSelectedColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::ResetSelectedColor(frameNode);
    if (SystemProperties::ConfigChangePerform()) {
        CheckBoxModelNG::CreateWithResourceObj(frameNode, CheckBoxColorType::SELECTED_COLOR, nullptr);
    }
}

void SetIsUserSetMargin(ArkUINodeHandle node, ArkUI_Bool isUserSet)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::SetIsUserSetMargin(frameNode, static_cast<bool>(isUserSet));
}

ArkUI_Bool GetSelect(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Bool>(CheckBoxModelNG::GetSelect(frameNode));
}

ArkUINodeHandle CreateCheckboxFrameNode(ArkUI_Uint32 nodeId)
{
    auto frameNode = CheckBoxModelNG::CreateFrameNode(nodeId);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
}

ArkUINodeHandle CreateToggleCheckboxFrameNode(ArkUI_Uint32 nodeId)
{
    auto frameNode = CheckBoxModelNG::CreateToggleCheckboxFrameNode(nodeId);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
}

void setToggleBuilderFunc(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto makeFunc = reinterpret_cast<SwitchMakeCallback*>(callback);
        CheckBoxModelNG::SetToggleBuilderFunc(frameNode, std::move(*makeFunc));
    } else {
        CheckBoxModelNG::SetToggleBuilderFunc(frameNode, nullptr);
    }
}

void SetChangeValue(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::SetChangeValue(frameNode, static_cast<bool>(value));
}

void SetSelectedColorFlagByUser(ArkUINodeHandle node, ArkUI_Bool isByUser)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::SetSelectedColorFlagByUser(frameNode, static_cast<bool>(isByUser));
}

void SetCheckboxChangeEvent(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto changeEvent = reinterpret_cast<std::function<void(bool)>*>(callback);
    CheckBoxModelNG::SetChangeEvent(frameNode, std::move(*changeEvent));
}

ArkUI_Bool IsToggleCheckboxPattern(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    return CheckBoxModelNG::IsToggleCheckboxPattern(frameNode);
}

ArkUI_Bool IsCheckboxContentModifierNodeId(ArkUINodeHandle node, ArkUI_Int32 nodeId)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    return CheckBoxModelNG::IsCheckboxContentModifierNodeId(frameNode, nodeId);
}

void UpdatePaintPropertyBySettingData(ArkUINodeHandle node, ArkUICheckboxSettingData* data, ArkUI_Bool isLunar)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(data);
    CheckboxSettingData settingData;
    if (data->selectColor.isSet) {
        settingData.selectedColor = Color(data->selectColor.value);
    }
    if (data->unselectedColor.isSet) {
        settingData.unselectedColor = Color(data->unselectedColor.value);
    }
    if (data->strokeColor.isSet) {
        settingData.strokeColor = Color(data->strokeColor.value);
    }
    CheckBoxModelNG::UpdatePaintPropertyBySettingData(frameNode, settingData, isLunar);
}

namespace NodeModifier {
const ArkUICheckboxCustomModifier* GetCheckboxCustomModifier()
{
    static const ArkUICheckboxCustomModifier modifier = {
        .setSelect = SetSelect,
        .setSelectedColor = SetSelectedColor,
        .resetSelectedColor = ResetSelectedColor,
        .setCheckboxOnChange = SetCheckboxOnChange,
        .setIsUserSetMargin = SetIsUserSetMargin,
        .getSelect = GetSelect,
        .createCheckboxFrameNode = CreateCheckboxFrameNode,
        .createToggleCheckboxFrameNode = CreateToggleCheckboxFrameNode,
        .setToggleBuilderFunc = setToggleBuilderFunc,
        .setChangeValue = SetChangeValue,
        .setSelectedColorFlagByUser = SetSelectedColorFlagByUser,
        .setCheckboxChangeEvent = SetCheckboxChangeEvent,
        .isToggleCheckboxPattern = IsToggleCheckboxPattern,
        .isCheckboxContentModifierNodeId = IsCheckboxContentModifierNodeId,
        .updatePaintPropertyBySettingData = UpdatePaintPropertyBySettingData,
    };
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
