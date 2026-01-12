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
#include "bridge/declarative_frontend/jsview/models/view_abstract_model_impl.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/pattern/checkbox/bridge/checkbox_custom_modifier.h"
#include "core/components_ng/pattern/checkbox/checkbox_model_ng.h"
#include "core/components_ng/pattern/checkbox/checkbox_model_impl.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/interfaces/cjui/cjui_api.h"
#include "core/interfaces/native/node/node_api.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components/checkable/checkable_theme.h"

#ifndef CROSS_PLATFORM
namespace OHOS::Ace {
Framework::CheckBoxModelImpl* GetCheckboxImpl()
{
    static Framework::CheckBoxModelImpl instance;
    return &instance;
}

namespace {
Framework::ViewAbstractModelImpl* GetViewAbstractModelImpl()
{
    static Framework::ViewAbstractModelImpl instance;
    return &instance;
}
} // namespace
} // namespace OHOS::Ace
#endif

namespace OHOS::Ace::NG {
namespace {
constexpr float CHECK_BOX_MARK_SIZE_INVALID_VALUE = -1.0f;
const uint32_t ERROR_UINT_CODE = -1;
const float ERROR_FLOAT_CODE = -1.0f;
const int32_t ERROR_INT_CODE = -1;
static std::string nameValue;
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;

FrameNode* GetFrameNode(ArkUINodeHandle node)
{
    return node ? reinterpret_cast<FrameNode*>(node) : ViewStackProcessor::GetInstance()->GetMainFrameNode();
}
} // namespace

void SetSelect(ArkUINodeHandle node, ArkUI_Bool isSelected)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::SetSelect(frameNode, static_cast<bool>(isSelected));
}

void SetSelectedColor(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::SetSelectedColor(frameNode, Color(color));
}

void SetSelectedColorPtr(ArkUINodeHandle node, ArkUI_Uint32 color, void* colorRawPtr)
{
    Color result = Color(color);
    SetSelectedColor(node, result.GetValue());
    if (SystemProperties::ConfigChangePerform()) {
        auto* frameNode = GetFrameNode(node);
        CHECK_NULL_VOID(frameNode);
        RefPtr<ResourceObject> resObj;
        if (!colorRawPtr) {
            ResourceParseUtils::CompleteResourceObjectFromColor(resObj, result, frameNode->GetTag());
        } else {
            resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(colorRawPtr));
        }
        CheckBoxModelNG::CreateWithResourceObj(frameNode, CheckBoxColorType::SELECTED_COLOR, resObj);
    }
}

void SetUnSelectedColor(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::SetUnSelectedColor(frameNode, Color(color));
}

void SetUnSelectedColorPtr(ArkUINodeHandle node, ArkUI_Uint32 color, void* colorRawPtr)
{
    Color result = Color(color);
    SetUnSelectedColor(node, result.GetValue());
    if (SystemProperties::ConfigChangePerform()) {
        auto* frameNode = GetFrameNode(node);
        CHECK_NULL_VOID(frameNode);
        RefPtr<ResourceObject> resObj;
        if (!colorRawPtr) {
            ResourceParseUtils::CompleteResourceObjectFromColor(resObj, result, frameNode->GetTag());
        } else {
            resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(colorRawPtr));
        }
        CheckBoxModelNG::CreateWithResourceObj(frameNode, CheckBoxColorType::UN_SELECTED_COLOR, resObj);
    }
}

void SetCheckboxWidth(ArkUINodeHandle node, float value, int unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension width = Dimension(static_cast<double>(value), static_cast<OHOS::Ace::DimensionUnit>(unit));
    CheckBoxModelNG::SetWidth(frameNode, width);
}

void SetCheckboxHeight(ArkUINodeHandle node, float value, int unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension height = Dimension(static_cast<double>(value), static_cast<OHOS::Ace::DimensionUnit>(unit));
    CheckBoxModelNG::SetHeight(frameNode, height);
}

void SetMark(ArkUINodeHandle node, uint32_t color, float sizeValue, int sizeUnit, float widthValue, int widthUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::SetCheckMarkColor(frameNode, Color(color));

    Dimension size = Dimension(static_cast<double>(sizeValue), static_cast<OHOS::Ace::DimensionUnit>(sizeUnit));
    CheckBoxModelNG::SetCheckMarkSize(frameNode, size);

    Dimension width = Dimension(static_cast<double>(widthValue), static_cast<OHOS::Ace::DimensionUnit>(widthUnit));
    CheckBoxModelNG::SetCheckMarkWidth(frameNode, width);
}

void SetCheckboxPadding(ArkUINodeHandle node, const float* values, const int* units, uint32_t length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (length != 4) { // 4 : data length
        return;
    }
    CalcLength topDimen;
    CalcLength rightDimen;
    CalcLength bottomDimen;
    CalcLength leftDimen;
    topDimen = CalcLength(values[0], static_cast<DimensionUnit>(units[0]));    // 0: top Dimension
    rightDimen = CalcLength(values[1], static_cast<DimensionUnit>(units[1]));  // 1: right Dimension
    bottomDimen = CalcLength(values[2], static_cast<DimensionUnit>(units[2])); // 2: bottom Dimension
    leftDimen = CalcLength(values[3], static_cast<DimensionUnit>(units[3]));   // 3: left Dimension
    NG::PaddingProperty padding;
    padding.top = std::optional<CalcLength>(topDimen);
    padding.bottom = std::optional<CalcLength>(bottomDimen);
    padding.left = std::optional<CalcLength>(leftDimen);
    padding.right = std::optional<CalcLength>(rightDimen);

    CheckBoxModelNG::SetPadding(frameNode, padding);
}

void SetCheckboxResponseRegion(ArkUINodeHandle node, const float* values, const int32_t* units, uint32_t length)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<DimensionRect> region;
    uint32_t ARRAY_LENGTH = 4; // 4: dimension length
    for (uint32_t i = 0; i < length / 4; i++) {
        CalcDimension xDimen =
            CalcDimension(values[i * ARRAY_LENGTH], static_cast<DimensionUnit>(units[i * ARRAY_LENGTH]));
        CalcDimension yDimen =
            CalcDimension(values[i * ARRAY_LENGTH + 1], static_cast<DimensionUnit>(units[i * ARRAY_LENGTH + 1]));
        CalcDimension widthDimen = CalcDimension(
            values[i * ARRAY_LENGTH + 2], static_cast<DimensionUnit>(units[i * ARRAY_LENGTH + 2])); // 2: width value
        CalcDimension heightDimen = CalcDimension(
            values[i * ARRAY_LENGTH + 3], static_cast<DimensionUnit>(units[i * ARRAY_LENGTH + 3])); // 3: height value
        DimensionOffset offsetDimen(xDimen, yDimen);
        DimensionRect dimenRect(widthDimen, heightDimen, offsetDimen);
        region.emplace_back(dimenRect);
    }
    CheckBoxModelNG::SetResponseRegion(frameNode, region);
}

void SetCheckboxOnChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onChange = reinterpret_cast<std::function<void(bool)>*>(callback);
        CheckBoxModelNG::SetOnChange(frameNode, std::move(*onChange));
    } else {
        CheckBoxModelNG::SetOnChange(frameNode, nullptr);
    }
}

void ResetCheckboxPadding(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::PaddingProperty padding;
    padding.top = std::optional<CalcLength>(CalcLength(0.0, DimensionUnit::VP));
    padding.bottom = std::optional<CalcLength>(CalcLength(0.0, DimensionUnit::VP));
    padding.left = std::optional<CalcLength>(CalcLength(0.0, DimensionUnit::VP));
    padding.right = std::optional<CalcLength>(CalcLength(0.0, DimensionUnit::VP));

    CheckBoxModelNG::SetPadding(frameNode, padding);
}

void ResetCheckboxResponseRegion(ArkUINodeHandle node) {}

void ResetCheckboxOnChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::SetOnChange(frameNode, nullptr);
}

void ResetSelect(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::SetSelect(frameNode, false);
}

void ResetSelectedColor(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::ResetSelectedColor(frameNode);
    if (SystemProperties::ConfigChangePerform()) {
        CheckBoxModelNG::CreateWithResourceObj(frameNode, CheckBoxColorType::SELECTED_COLOR, nullptr);
    }
}

void ResetUnSelectedColor(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::ResetUnSelectedColor(frameNode);
    if (SystemProperties::ConfigChangePerform()) {
        CheckBoxModelNG::CreateWithResourceObj(frameNode, CheckBoxColorType::UN_SELECTED_COLOR, nullptr);
    }
}

void ResetCheckboxWidth(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto checkBoxTheme = pipelineContext->GetTheme<CheckboxTheme>();
    CHECK_NULL_VOID(checkBoxTheme);
    auto defaultWidth = checkBoxTheme->GetDefaultWidth();
    auto horizontalPadding = checkBoxTheme->GetHotZoneHorizontalPadding();
    auto width = defaultWidth - horizontalPadding * 2;
    CheckBoxModelNG::SetWidth(frameNode, width);
}

void ResetCheckboxHeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto checkBoxTheme = pipelineContext->GetTheme<CheckboxTheme>();
    CHECK_NULL_VOID(checkBoxTheme);
    auto defaultHeight = checkBoxTheme->GetDefaultHeight();
    auto verticalPadding = checkBoxTheme->GetHotZoneVerticalPadding();
    auto height = defaultHeight - verticalPadding * 2;

    CheckBoxModelNG::SetHeight(frameNode, height);
}

void ResetMark(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto checkBoxTheme = pipelineContext->GetTheme<CheckboxTheme>();

    CheckBoxModelNG::ResetCheckMarkColor(frameNode);
    CheckBoxModelNG::SetCheckMarkSize(frameNode, Dimension(CHECK_BOX_MARK_SIZE_INVALID_VALUE));
    CheckBoxModelNG::SetCheckMarkWidth(frameNode, checkBoxTheme->GetCheckStroke());
}

void SetCheckboxShape(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::SetCheckboxStyle(frameNode, static_cast<CheckBoxStyle>(value));
}

void ResetCheckboxShape(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::SetCheckboxStyle(frameNode, CheckBoxStyle::CIRCULAR_STYLE);
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

ArkUI_Uint32 GetSelectedColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return CheckBoxModelNG::GetSelectedColor(frameNode).GetValue();
}

ArkUI_Uint32 GetUnSelectedColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return CheckBoxModelNG::GetUnSelectedColor(frameNode).GetValue();
}

ArkUI_Uint32 GetCheckMarkColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return CheckBoxModelNG::GetCheckMarkColor(frameNode).GetValue();
}

ArkUI_Float64 GetCheckMarkSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return CheckBoxModelNG::GetCheckMarkSize(frameNode).Value();
}

ArkUI_Float64 GetCheckMarkWidth(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return CheckBoxModelNG::GetCheckMarkWidth(frameNode).Value();
}

ArkUI_Int32 GetCheckboxShape(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(CheckBoxModelNG::GetCheckboxStyle(frameNode));
}

void SetCheckboxName(ArkUINodeHandle node, ArkUI_CharPtr name)
{
    CHECK_NULL_VOID(name);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::SetCheckboxName(frameNode, std::string(name));
}

void SetCheckboxGroup(ArkUINodeHandle node, ArkUI_CharPtr group)
{
    CHECK_NULL_VOID(group);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::SetCheckboxGroup(frameNode, std::string(group));
}

ArkUI_CharPtr GetCheckboxName(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, "");
    nameValue = CheckBoxModelNG::GetCheckboxName(frameNode);
    return nameValue.c_str();
}

ArkUI_CharPtr GetCheckboxGroup(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, "");
    nameValue = CheckBoxModelNG::GetCheckboxGroup(frameNode);
    return nameValue.c_str();
}

void CreateCheckbox(ArkUI_CharPtr namePtr, ArkUI_CharPtr groupPtr)
{
    auto checkboxName = std::optional<std::string>(std::string(namePtr));
    auto checkboxGroup = std::optional<std::string>(std::string(groupPtr));
    CheckBoxModelNG::CreateCheckbox(checkboxName, checkboxGroup, CHECK_BOX_ETS_TAG);
}

void SetCheckboxBuilder(ArkUINodeHandle node, void* builder)
{
    auto* frameNode = GetFrameNode(node);
    std::optional<std::function<void()>> customBuilderFunc;
    if (builder) {
        auto builderFunc = reinterpret_cast<std::function<void()>*>(builder);
        customBuilderFunc = std::move(*builderFunc);
    }
    CheckBoxModelNG::SetBuilder(frameNode, customBuilderFunc);
}

void ResetCheckboxMarkColor(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::ResetCheckMarkColor(frameNode);
}

void SetCheckboxMarkColor(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::SetCheckMarkColor(frameNode, Color(color));
}

void SetCheckboxCheckMarkSize(ArkUINodeHandle node, ArkUI_Float32 sizeValue, ArkUI_Int32 sizeUnit)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    Dimension size = Dimension(static_cast<double>(sizeValue), static_cast<OHOS::Ace::DimensionUnit>(sizeUnit));
    CheckBoxModelNG::SetCheckMarkSize(frameNode, size);
}

void SetCheckboxCheckMarkWidth(ArkUINodeHandle node, ArkUI_Float32 widthValue, ArkUI_Int32 widthUnit)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    Dimension width = Dimension(static_cast<double>(widthValue), static_cast<OHOS::Ace::DimensionUnit>(widthUnit));
    CheckBoxModelNG::SetCheckMarkWidth(frameNode, width);
}

void SetCheckboxChangeEvent(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(callback);
    auto changeEvent = reinterpret_cast<std::function<void(bool)>*>(callback);
    CheckBoxModelNG::SetChangeEvent(frameNode, std::move(*changeEvent));
}

void SetCheckboxJsPadding(
    const struct ArkUIPaddingType* oldValue, const struct ArkUIPaddingType* newValue, ArkUI_Bool flag)
{
    auto frameNode = GetFrameNode(nullptr);
    CHECK_NULL_VOID(frameNode);
    PaddingProperty padding({ CalcLength(0.0_vp), CalcLength(0.0_vp), CalcLength(0.0_vp), CalcLength(0.0_vp),
        std::nullopt, std::nullopt });
    if (newValue) {
        padding.top = newValue->top.string
                          ? CalcLength(newValue->top.string)
                          : CalcLength(newValue->top.value, static_cast<DimensionUnit>(newValue->top.unit));
        padding.bottom = newValue->bottom.string
                             ? CalcLength(newValue->bottom.string)
                             : CalcLength(newValue->bottom.value, static_cast<DimensionUnit>(newValue->bottom.unit));
        padding.left = newValue->start.string
                           ? CalcLength(newValue->start.string)
                           : CalcLength(newValue->start.value, static_cast<DimensionUnit>(newValue->start.unit));
        padding.right = newValue->end.string
                            ? CalcLength(newValue->end.string)
                            : CalcLength(newValue->end.value, static_cast<DimensionUnit>(newValue->end.unit));
    }
    CheckBoxModelNG::SetPadding(frameNode, padding);
}

void SetCheckboxJsMargin(
    const struct ArkUIPaddingType* values, ArkUI_Bool isLengthMetrics, void* rawPtr, ArkUI_Bool parse)
{
    auto frameNode = GetFrameNode(nullptr);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::SetIsUserSetMargin(frameNode, static_cast<bool>(true));
    ViewAbstract::ResetResObj(frameNode, "margin");
    if (!parse) {
        ViewAbstract::SetMargin(frameNode, NG::CalcLength(0.0));
        return;
    }
    CHECK_NULL_VOID(values);
    auto topDimen = values->top.string ? CalcLength(values->top.string)
                                       : CalcLength(values->top.value, static_cast<DimensionUnit>(values->top.unit));
    auto bottomDimen = values->bottom.string
                           ? CalcLength(values->bottom.string)
                           : CalcLength(values->bottom.value, static_cast<DimensionUnit>(values->bottom.unit));
    auto leftDimen = values->start.string
                         ? CalcLength(values->start.string)
                         : CalcLength(values->start.value, static_cast<DimensionUnit>(values->start.unit));
    auto rightDimen = values->end.string ? CalcLength(values->end.string)
                                         : CalcLength(values->end.value, static_cast<DimensionUnit>(values->end.unit));
    NG::PaddingProperty margins;
    if (values->top.isSet) {
        margins.top = std::optional<CalcLength>(topDimen);
    }
    if (values->bottom.isSet) {
        margins.bottom = std::optional<CalcLength>(bottomDimen);
    }
    if (values->start.isSet) {
        isLengthMetrics ? margins.start = std::optional<CalcLength>(leftDimen)
                        : margins.left = std::optional<CalcLength>(leftDimen);
    }
    if (values->end.isSet) {
        isLengthMetrics ? margins.end = std::optional<CalcLength>(rightDimen)
                        : margins.right = std::optional<CalcLength>(rightDimen);
    }
    if (SystemProperties::ConfigChangePerform() && rawPtr) {
        auto objs = *(reinterpret_cast<const std::vector<RefPtr<ResourceObject>>*>(rawPtr));
        ViewAbstractModelNG::RegisterEdgeMarginsResObj("margin.top", margins, objs[NUM_0]);
        ViewAbstractModelNG::RegisterEdgeMarginsResObj("margin.bottom", margins, objs[NUM_1]);
        ViewAbstractModelNG::RegisterEdgeMarginsResObj("margin.left", margins, objs[NUM_2]);
        ViewAbstractModelNG::RegisterEdgeMarginsResObj("margin.right", margins, objs[NUM_3]);
    }
    ViewAbstract::SetMargin(frameNode, margins);
}

// for inner
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

void SetCheckboxOnChangeExtraParam(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [node, extraParam](const bool value) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_CHECKBOX_CHANGE;
        event.componentAsyncEvent.data[0].i32 = static_cast<int>(value);
        SendArkUISyncEvent(&event);
    };
    CheckBoxModelNG::SetOnChange(frameNode, std::move(onEvent));
}

#ifndef CROSS_PLATFORM
void CreateCheckboxImpl(ArkUI_CharPtr namePtr, ArkUI_CharPtr groupPtr)
{
    auto checkboxName = std::optional<std::string>(std::string(namePtr));
    auto checkboxGroup = std::optional<std::string>(std::string(groupPtr));
    GetCheckboxImpl()->Create(checkboxName, checkboxGroup, CHECK_BOX_ETS_TAG);
}

void SetCheckboxBuilderImpl(ArkUINodeHandle node, void* builder) {}

void SetCheckboxSelectImpl(ArkUINodeHandle node, ArkUI_Bool isSelected)
{
    GetCheckboxImpl()->SetSelect(static_cast<bool>(isSelected));
}

void SetCheckboxSelectedColorImpl(ArkUINodeHandle node, ArkUI_Uint32 color, void* colorRawPtr)
{
    GetCheckboxImpl()->SetSelectedColor(Color(color));
}

void SetCheckboxUnSelectedColorImpl(ArkUINodeHandle node, ArkUI_Uint32 color, void* colorRawPtr) {}

void SetCheckboxOnChangeImpl(ArkUINodeHandle node, void* callback)
{
    if (callback) {
        auto onChange = reinterpret_cast<std::function<void(bool)>*>(callback);
        GetCheckboxImpl()->SetOnChange(std::move(*onChange));
    }
}

void SetCheckboxPaddingImpl(
    const struct ArkUIPaddingType* oldValue, const struct ArkUIPaddingType* newValue, ArkUI_Bool flag)
{
    PaddingPropertyF oldPadding({ 0.0f, 0.0f, 0.0f, 0.0f });
    if (oldValue) {
        oldPadding.left = oldValue->start.value;
        oldPadding.right = oldValue->end.value;
        oldPadding.top = oldValue->top.value;
        oldPadding.bottom = oldValue->bottom.value;
    }
    PaddingProperty padding;
    GetCheckboxImpl()->SetPadding(oldPadding, padding, flag);
}

void SetCheckboxChangeEventImpl(ArkUINodeHandle node, void* callback) {}

void SetCheckboxResponseRegionImpl(ArkUINodeHandle node, const float* values, const int32_t* units, uint32_t length)
{
    std::vector<DimensionRect> region;
    uint32_t ARRAY_LENGTH = 4; // 4: dimension length
    for (uint32_t i = 0; i < length / 4; i++) {
        CalcDimension xDimen =
            CalcDimension(values[i * ARRAY_LENGTH], static_cast<DimensionUnit>(units[i * ARRAY_LENGTH]));
        CalcDimension yDimen =
            CalcDimension(values[i * ARRAY_LENGTH + 1], static_cast<DimensionUnit>(units[i * ARRAY_LENGTH + 1]));
        CalcDimension widthDimen = CalcDimension(
            values[i * ARRAY_LENGTH + 2], static_cast<DimensionUnit>(units[i * ARRAY_LENGTH + 2])); // 2: width value
        CalcDimension heightDimen = CalcDimension(
            values[i * ARRAY_LENGTH + 3], static_cast<DimensionUnit>(units[i * ARRAY_LENGTH + 3])); // 3: height value
        DimensionOffset offsetDimen(xDimen, yDimen);
        DimensionRect dimenRect(widthDimen, heightDimen, offsetDimen);
        region.emplace_back(dimenRect);
    }
    GetViewAbstractModelImpl()->SetResponseRegion(region);
}

void ResetCheckboxResponseRegionImpl(ArkUINodeHandle node)
{
    GetViewAbstractModelImpl()->SetResponseRegion({});
}

void ResetCheckboxSelectedColorImpl(ArkUINodeHandle node) {}

void ResetCheckboxUnSelectedColorImpl(ArkUINodeHandle node) {}

void ResetCheckboxMarkColorImpl(ArkUINodeHandle node) {}

void SetCheckboxMarginImpl(
    const struct ArkUIPaddingType* values, ArkUI_Bool isLengthMetrics, void* rawPtr, ArkUI_Bool parse)
{
    if (!parse) {
        GetViewAbstractModelImpl()->SetMargin(CalcDimension(0.0));
        return;
    }
    CHECK_NULL_VOID(values);
    if (isLengthMetrics) {
        return;
    }
    std::optional<CalcDimension> topDimen;
    std::optional<CalcDimension> bottomDimen;
    std::optional<CalcDimension> leftDimen;
    std::optional<CalcDimension> rightDimen;
    if (values->top.isSet) {
        topDimen = values->top.string ? CalcDimension(values->top.string)
                                      : CalcDimension(values->top.value, static_cast<DimensionUnit>(values->top.unit));
    }
    if (values->bottom.isSet) {
        bottomDimen = values->bottom.string
                          ? CalcDimension(values->bottom.string)
                          : CalcDimension(values->bottom.value, static_cast<DimensionUnit>(values->bottom.unit));
    }
    if (values->start.isSet) {
        leftDimen = values->start.string
                        ? CalcDimension(values->start.string)
                        : CalcDimension(values->start.value, static_cast<DimensionUnit>(values->start.unit));
    }
    if (values->end.isSet) {
        rightDimen = values->end.string
                         ? CalcDimension(values->end.string)
                         : CalcDimension(values->end.value, static_cast<DimensionUnit>(values->end.unit));
    }
    GetViewAbstractModelImpl()->SetMargins(topDimen, bottomDimen, leftDimen, rightDimen);
}
#endif

const ArkUICheckboxModifier* GetCheckboxDynamicModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (!isCurrentUseNewPipeline) {
#ifndef CROSS_PLATFORM
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUICheckboxModifier modifier = {
            .setSelect = SetCheckboxSelectImpl,
            .setSelectedColor = nullptr,
            .setUnSelectedColor = nullptr,
            .setCheckboxWidth = nullptr,
            .setCheckboxHeight = nullptr,
            .setMark = nullptr,
            .setCheckboxPadding = nullptr,
            .setCheckboxResponseRegion = SetCheckboxResponseRegionImpl,
            .setCheckboxOnChange = SetCheckboxOnChangeImpl,
            .resetSelect = nullptr,
            .resetSelectedColor = ResetCheckboxSelectedColorImpl,
            .resetUnSelectedColor = ResetCheckboxUnSelectedColorImpl,
            .resetCheckboxWidth = nullptr,
            .resetCheckboxHeight = nullptr,
            .resetMark = nullptr,
            .setCheckboxShape = nullptr,
            .resetCheckboxShape = nullptr,
            .resetCheckboxPadding = nullptr,
            .resetCheckboxResponseRegion = ResetCheckboxResponseRegionImpl,
            .resetCheckboxOnChange = nullptr,
            .setIsUserSetMargin = nullptr,
            .getSelect = nullptr,
            .getSelectedColor = nullptr,
            .getUnSelectedColor = nullptr,
            .getCheckMarkColor = nullptr,
            .getCheckMarkSize = nullptr,
            .getCheckMarkWidth = nullptr,
            .getCheckboxShape = nullptr,
            .setCheckboxName = nullptr,
            .setCheckboxGroup = nullptr,
            .getCheckboxName = nullptr,
            .getCheckboxGroup = nullptr,
            .setSelectedColorPtr = SetCheckboxSelectedColorImpl,
            .setUnSelectedColorPtr = SetCheckboxUnSelectedColorImpl,
            .createCheckbox = CreateCheckboxImpl,
            .setCheckboxBuilder = SetCheckboxBuilderImpl,
            .resetCheckboxMarkColor = ResetCheckboxMarkColorImpl,
            .setCheckboxMarkColor = nullptr,
            .setCheckMarkSize = nullptr,
            .setCheckMarkWidth = nullptr,
            .setCheckboxChangeEvent = SetCheckboxChangeEventImpl,
            .setCheckboxJsPadding = SetCheckboxPaddingImpl,
            .setCheckboxJsMargin = SetCheckboxMarginImpl,
        };
        CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
        return &modifier;
#endif
    }
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUICheckboxModifier modifier = {
        .setSelect = SetSelect,
        .setSelectedColor = SetSelectedColor,
        .setUnSelectedColor = SetUnSelectedColor,
        .setCheckboxWidth = SetCheckboxWidth,
        .setCheckboxHeight = SetCheckboxHeight,
        .setMark = SetMark,
        .setCheckboxPadding = SetCheckboxPadding,
        .setCheckboxResponseRegion = SetCheckboxResponseRegion,
        .setCheckboxOnChange = SetCheckboxOnChange,
        .resetSelect = ResetSelect,
        .resetSelectedColor = ResetSelectedColor,
        .resetUnSelectedColor = ResetUnSelectedColor,
        .resetCheckboxWidth = ResetCheckboxWidth,
        .resetCheckboxHeight = ResetCheckboxHeight,
        .resetMark = ResetMark,
        .setCheckboxShape = SetCheckboxShape,
        .resetCheckboxShape = ResetCheckboxShape,
        .resetCheckboxPadding = ResetCheckboxPadding,
        .resetCheckboxResponseRegion = ResetCheckboxResponseRegion,
        .resetCheckboxOnChange = ResetCheckboxOnChange,
        .setIsUserSetMargin = SetIsUserSetMargin,
        .getSelect = GetSelect,
        .getSelectedColor = GetSelectedColor,
        .getUnSelectedColor = GetUnSelectedColor,
        .getCheckMarkColor = GetCheckMarkColor,
        .getCheckMarkSize = GetCheckMarkSize,
        .getCheckMarkWidth = GetCheckMarkWidth,
        .getCheckboxShape = GetCheckboxShape,
        .setCheckboxName = SetCheckboxName,
        .setCheckboxGroup = SetCheckboxGroup,
        .getCheckboxName = GetCheckboxName,
        .getCheckboxGroup = GetCheckboxGroup,
        .setSelectedColorPtr = SetSelectedColorPtr,
        .setUnSelectedColorPtr = SetUnSelectedColorPtr,
        .createCheckbox = CreateCheckbox,
        .setCheckboxBuilder = SetCheckboxBuilder,
        .resetCheckboxMarkColor = ResetCheckboxMarkColor,
        .setCheckboxMarkColor = SetCheckboxMarkColor,
        .setCheckMarkSize = SetCheckboxCheckMarkSize,
        .setCheckMarkWidth = SetCheckboxCheckMarkWidth,
        .setCheckboxChangeEvent = SetCheckboxChangeEvent,
        .setCheckboxJsPadding = SetCheckboxJsPadding,
        .setCheckboxJsMargin = SetCheckboxJsMargin,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUICheckboxModifier* GetCJUICheckboxModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUICheckboxModifier modifier = {
        .setSelect = SetSelect,
        .setSelectedColor = SetSelectedColor,
        .setUnSelectedColor = SetUnSelectedColor,
        .setCheckboxWidth = SetCheckboxWidth,
        .setCheckboxHeight = SetCheckboxHeight,
        .setMark = SetMark,
        .setCheckboxPadding = SetCheckboxPadding,
        .setCheckboxResponseRegion = SetCheckboxResponseRegion,
        .resetSelect = ResetSelect,
        .resetSelectedColor = ResetSelectedColor,
        .resetUnSelectedColor = ResetUnSelectedColor,
        .resetCheckboxWidth = ResetCheckboxWidth,
        .resetCheckboxHeight = ResetCheckboxHeight,
        .resetMark = ResetMark,
        .setCheckboxShape = SetCheckboxShape,
        .resetCheckboxShape = ResetCheckboxShape,
        .resetCheckboxPadding = ResetCheckboxPadding,
        .resetCheckboxResponseRegion = ResetCheckboxResponseRegion,
        .getSelect = GetSelect,
        .getSelectedColor = GetSelectedColor,
        .getUnSelectedColor = GetUnSelectedColor,
        .getCheckMarkColor = GetCheckMarkColor,
        .getCheckMarkSize = GetCheckMarkSize,
        .getCheckMarkWidth = GetCheckMarkWidth,
        .getCheckboxShape = GetCheckboxShape,
        .setCheckboxName = SetCheckboxName,
        .setCheckboxGroup = SetCheckboxGroup,
        .getCheckboxName = GetCheckboxName,
        .getCheckboxGroup = GetCheckboxGroup,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const ArkUICheckboxCustomModifier* GetCheckboxCustomModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
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
        .setCheckboxOnChangeExtraParam = SetCheckboxOnChangeExtraParam,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
} // namespace OHOS::Ace::NG
