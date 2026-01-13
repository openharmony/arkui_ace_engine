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
#include "core/components_ng/pattern/checkboxgroup/bridge/checkboxgroup_custom_modifier.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_model_impl.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_model_ng.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/interfaces/cjui/cjui_api.h"
#include "core/interfaces/native/node/node_api.h"

#ifndef CROSS_PLATFORM
namespace OHOS::Ace {
Framework::CheckBoxGroupModelImpl* GetCheckboxGroupImpl()
{
    static Framework::CheckBoxGroupModelImpl instance;
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
static const uint32_t ERROR_UINT_CODE = -1;
static const float ERROR_FLOAT_CODE = -1.0f;
static const int32_t ERROR_INT_CODE = -1;
static std::string groupNameValue;
const DimensionUnit DEFAULT_UNIT = DimensionUnit::VP;
FrameNode* GetFrameNode(ArkUINodeHandle node)
{
    return node ? reinterpret_cast<FrameNode*>(node) : ViewStackProcessor::GetInstance()->GetMainFrameNode();
}

} // namespace

void SetCheckboxGroupSelectedColor(ArkUINodeHandle node, uint32_t color)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxGroupModelNG::SetSelectedColor(frameNode, Color(color));
}

void SetCheckboxGroupSelectedColorPtr(ArkUINodeHandle node, uint32_t color, void* colorRawPtr)
{
    SetCheckboxGroupSelectedColor(node, color);
    Color result = Color(color);
    if (SystemProperties::ConfigChangePerform()) {
        auto* frameNode = GetFrameNode(node);
        CHECK_NULL_VOID(frameNode);
        RefPtr<ResourceObject> resObj;
        if (!colorRawPtr) {
            ResourceParseUtils::CompleteResourceObjectFromColor(resObj, result, frameNode->GetTag());
        } else {
            resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(colorRawPtr));
        }
        CheckBoxGroupModelNG::CreateWithResourceObj(frameNode, CheckBoxGroupColorType::SELECTED_COLOR, resObj);
    }
}

void ResetCheckboxGroupSelectedColor(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto checkBoxTheme = themeManager->GetTheme<CheckboxTheme>();
    if (node) {
        CheckBoxGroupModelNG::SetSelectedColor(frameNode, checkBoxTheme->GetActiveColor());
    } else {
        CheckBoxGroupModelNG::ResetSelectedColor(frameNode);
    }
    if (SystemProperties::ConfigChangePerform()) {
        if (node) {
            CheckBoxGroupModelNG::SetSelectedColorByUser(frameNode, false);
        }
        CheckBoxGroupModelNG::CreateWithResourceObj(frameNode, CheckBoxGroupColorType::SELECTED_COLOR, nullptr);
    }
}

void SetCheckboxGroupUnSelectedColor(ArkUINodeHandle node, uint32_t color)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxGroupModelNG::SetUnSelectedColor(frameNode, Color(color));
}

void SetCheckboxGroupUnSelectedColorPtr(ArkUINodeHandle node, uint32_t color, void* colorRawPtr)
{
    SetCheckboxGroupUnSelectedColor(node, color);
    Color result = Color(color);
    if (SystemProperties::ConfigChangePerform()) {
        auto* frameNode = GetFrameNode(node);
        CHECK_NULL_VOID(frameNode);
        RefPtr<ResourceObject> resObj;
        if (!colorRawPtr) {
            ResourceParseUtils::CompleteResourceObjectFromColor(resObj, result, frameNode->GetTag());
        } else {
            resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(colorRawPtr));
        }
        CheckBoxGroupModelNG::CreateWithResourceObj(frameNode, CheckBoxGroupColorType::UN_SELECTED_COLOR, resObj);
    }
}

void ResetCheckboxGroupUnSelectedColor(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto checkBoxTheme = themeManager->GetTheme<CheckboxTheme>();
    if (node) {
        CheckBoxGroupModelNG::SetUnSelectedColor(frameNode, checkBoxTheme->GetInactiveColor());
    } else {
        CheckBoxGroupModelNG::ResetUnSelectedColor(frameNode);
    }
    if (SystemProperties::ConfigChangePerform()) {
        if (node) {
            CheckBoxGroupModelNG::SetUnSelectedColorByUser(frameNode, false);
        }
        CheckBoxGroupModelNG::CreateWithResourceObj(frameNode, CheckBoxGroupColorType::UN_SELECTED_COLOR, nullptr);
    }
}

void SetCheckboxGroupSelectAll(ArkUINodeHandle node, ArkUI_Bool isSelected)
{
    auto* frameNode =  GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxGroupModelNG::SetSelectAll(frameNode, isSelected);
}

void ResetCheckboxGroupSelectAll(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxGroupModelNG::SetSelectAll(frameNode, false);
}

void SetCheckboxGroupWidth(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_CharPtr calcValue)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    if (unitEnum == DimensionUnit::CALC) {
        ViewAbstract::SetWidth(
            frameNode, CalcLength(CalcLength(std::string(calcValue))));
    } else {
        ViewAbstract::SetWidth(frameNode, CalcLength(value, unitEnum));
    }
}

void ResetCheckboxGroupWidth(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ClearWidthOrHeight(frameNode, true);
    if (!node) {
        ViewAbstract::ResetResObj(frameNode, "width");
        ViewAbstract::ResetLayoutPolicyProperty(frameNode, true);
    }
}

void SetCheckboxGroupHeight(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_CharPtr calcValue)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    if (unitEnum == DimensionUnit::CALC) {
        ViewAbstract::SetHeight(
            frameNode, CalcLength(CalcLength(std::string(calcValue))));
    } else {
        ViewAbstract::SetHeight(frameNode, CalcLength(value, unitEnum));
    }
}

void ResetCheckboxGroupHeight(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ClearWidthOrHeight(frameNode, false);
    if (!node) {
        ViewAbstract::ResetResObj(frameNode, "height");
        ViewAbstract::ResetLayoutPolicyProperty(frameNode, false);
    }
}

void SetCheckboxGroupMark(ArkUINodeHandle node, uint32_t color, ArkUI_Float32 sizeValue, ArkUI_Float32 widthValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxGroupModelNG::SetCheckMarkColor(frameNode, Color(color));

    Dimension size = Dimension(sizeValue, DEFAULT_UNIT);
    CheckBoxGroupModelNG::SetCheckMarkSize(frameNode, size);

    Dimension width = Dimension(widthValue, DEFAULT_UNIT);
    CheckBoxGroupModelNG::SetCheckMarkWidth(frameNode, width);
}

void ResetCheckboxGroupMark(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto checkBoxTheme = themeManager->GetTheme<CheckboxTheme>();

    CheckBoxGroupModelNG::SetCheckMarkColor(frameNode, checkBoxTheme->GetPointColor());

    Dimension size = Dimension(-1.0f);
    CheckBoxGroupModelNG::SetCheckMarkSize(frameNode, size);

    CheckBoxGroupModelNG::SetCheckMarkWidth(frameNode, checkBoxTheme->GetCheckStroke());
}

void SetCheckboxGroupStyle(ArkUINodeHandle node, ArkUI_Int32 style)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxGroupModelNG::SetCheckboxGroupStyle(frameNode, static_cast<CheckBoxStyle>(style));
}

void ResetCheckboxGroupStyle(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxGroupModelNG::SetCheckboxGroupStyle(frameNode, CheckBoxStyle::CIRCULAR_STYLE);
}

void SetCheckboxGroupName(ArkUINodeHandle node, ArkUI_CharPtr group)
{
    CHECK_NULL_VOID(group);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxGroupModelNG::SetCheckboxGroupName(frameNode, std::string(group));
}

void SetCheckboxGroupOnChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onChange = reinterpret_cast<std::function<void (const BaseEventInfo*)>*>(callback);
        CheckBoxGroupModelNG::SetOnChange(frameNode, std::move(*onChange));
    } else {
        CheckBoxGroupModelNG::SetOnChange(frameNode, nullptr);
    }
}

void ResetCheckboxGroupOnChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxGroupModelNG::SetOnChange(frameNode, nullptr);
}

ArkUI_CharPtr GetCheckboxGroupName(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, "");
    groupNameValue = CheckBoxGroupModelNG::GetCheckboxGroupName(frameNode);
    return groupNameValue.c_str();
}

ArkUI_Bool GetCheckboxGroupSelectAll(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Bool>(CheckBoxGroupModelNG::GetSelect(frameNode));
}

ArkUI_Uint32 GetCheckboxGroupSelectedColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return CheckBoxGroupModelNG::GetSelectedColor(frameNode).GetValue();
}

ArkUI_Uint32 GetCheckboxGroupUnSelectedColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return CheckBoxGroupModelNG::GetUnSelectedColor(frameNode).GetValue();
}

ArkUI_Uint32 GetCheckboxGroupMarkColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return CheckBoxGroupModelNG::GetCheckMarkColor(frameNode).GetValue();
}

ArkUI_Float64 GetCheckboxGroupMarkSize(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return CheckBoxGroupModelNG::GetCheckMarkSize(frameNode).Value();
}

ArkUI_Float64 GetCheckboxGroupMarkWidth(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return CheckBoxGroupModelNG::GetCheckMarkWidth(frameNode).Value();
}

ArkUI_Int32 GetCheckboxGroupStyle(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(CheckBoxGroupModelNG::GetCheckboxGroupStyle(frameNode));
}

void CreateCheckboxGroup(ArkUI_CharPtr groupNamePtr)
{
    std::optional<std::string> checkboxGroupName = std::make_optional(groupNamePtr ? groupNamePtr : "");
    CheckBoxGroupModelNG::CreateCheckboxGroup(checkboxGroupName);
}

ArkUINodeHandle CreateCheckboxGroupFrameNode(ArkUI_Uint32 nodeId)
{
    auto frameNode = CheckBoxGroupModelNG::CreateFrameNode(nodeId);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
}

void SetCheckMarkColor(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxGroupModelNG::SetCheckMarkColor(frameNode, Color(color));
}

void ResetCheckMarkColor(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxGroupModelNG::ResetCheckMarkColor(frameNode);
}

void SetCheckboxGroupCheckMarkSize(ArkUINodeHandle node, ArkUI_Float32 sizeValue, ArkUI_Int32 unit)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    Dimension size = Dimension(sizeValue, static_cast<OHOS::Ace::DimensionUnit>(unit));
    CheckBoxGroupModelNG::SetCheckMarkSize(frameNode, size);
}

void SetCheckboxGroupCheckMarkWidth(ArkUINodeHandle node, ArkUI_Float32 widthValue, ArkUI_Int32 unit)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    Dimension width = Dimension(widthValue, static_cast<OHOS::Ace::DimensionUnit>(unit));
    CheckBoxGroupModelNG::SetCheckMarkWidth(frameNode, width);
}

void SetCheckboxGroupResponseRegion(ArkUINodeHandle node, const float* values, const int32_t* units, uint32_t length)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<DimensionRect> region;
    uint32_t ARRAY_LENGTH = 4; // 4: dimension length
    for (uint32_t i = 0; i < length / ARRAY_LENGTH; i++) {
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
    CheckBoxGroupModelNG::SetResponseRegion(frameNode, region);
}

void ResetCheckboxGroupResponseRegion(ArkUINodeHandle node) {}

void SetCheckboxGroupPadding(
    const struct ArkUIPaddingType* oldValue, const struct ArkUIPaddingType* newValue, ArkUI_Bool flag)
{
    auto frameNode = GetFrameNode(nullptr);
    CHECK_NULL_VOID(frameNode);
    PaddingProperty padding(
        { CalcLength(0.0_vp), CalcLength(0.0_vp), CalcLength(0.0_vp), CalcLength(0.0_vp), std::nullopt, std::nullopt });
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
    CheckBoxGroupModelNG::SetPadding(frameNode, padding);
}

void SetCheckboxGroupChangeEvent(void* callback)
{
    CHECK_NULL_VOID(callback);
    auto frameNode = GetFrameNode(nullptr);
    CHECK_NULL_VOID(frameNode);
    auto changeEvent = reinterpret_cast<std::function<void(const BaseEventInfo*)>*>(callback);
    CheckBoxGroupModelNG::SetChangeEvent(frameNode, std::move(*changeEvent));
}

void SetCheckboxGroupSize(
    ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_CharPtr calcValue, void* resPtr, ArkUI_Bool isWidth)
{
    auto* frameNode = GetFrameNode(nullptr);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ResetResObj(frameNode, isWidth ? "width" : "height");
    ViewAbstract::ResetLayoutPolicyProperty(frameNode, isWidth);
    if (!SystemProperties::ConfigChangePerform() ? LessNotEqual(value, 0.0) : (LessNotEqual(value, 0.0) && !resPtr)) {
        if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            ViewAbstract::ClearWidthOrHeight(frameNode, isWidth);
            return;
        }
        value = 0.0f;
    }
    if (SystemProperties::ConfigChangePerform() && resPtr) {
        auto* res = reinterpret_cast<ResourceObject*>(resPtr);
        auto resObj = AceType::Claim(res);
        if (isWidth) {
            ViewAbstract::SetWidth(frameNode, resObj);
        } else {
            ViewAbstract::SetHeight(frameNode, resObj);
        }
        return;
    }
    CalcLength length;
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    if (unitEnum == DimensionUnit::CALC) {
        length = CalcLength(std::string(calcValue));
    } else {
        length = CalcLength(value, unitEnum);
    }
    if (isWidth) {
        ViewAbstract::SetWidth(frameNode, length);
    } else {
        ViewAbstract::SetHeight(frameNode, length);
    }
}

void SetCheckboxGroupOnChangeExtraParam(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [node, extraParam](const BaseEventInfo* info) {
        const auto* groupInfo = TypeInfoHelper::DynamicCast<CheckboxGroupResult>(info);
        if (!groupInfo) {
            return;
        }
        ArkUINodeEvent event;
        event.kind = TEXT_INPUT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.textInputEvent.subKind = ON_CHECKBOX_GROUP_CHANGE;
        std::vector<std::string> nameList = groupInfo->GetNameList();
        std::string status = std::to_string(groupInfo->GetStatus());

        std::string nodeEventStr;
        if (!nameList.empty()) {
            nodeEventStr.append("Name:");
            for (auto nameStr : nameList) {
                nodeEventStr.append(nameStr);
                nodeEventStr.append(",");
            }
            nodeEventStr.pop_back();
            nodeEventStr.append(";");
        }

        nodeEventStr.append("Status:" + status);
        event.textInputEvent.nativeStringPtr = reinterpret_cast<intptr_t>(nodeEventStr.c_str());
        SendArkUISyncEvent(&event);
    };
    CheckBoxGroupModelNG::SetOnChange(frameNode, std::move(onEvent));
}

#ifndef CROSS_PLATFORM
void CreateCheckboxGroupImpl(ArkUI_CharPtr groupNamePtr)
{
    std::optional<std::string> checkboxGroupName = std::make_optional(groupNamePtr ? groupNamePtr : "");
    GetCheckboxGroupImpl()->Create(checkboxGroupName);
}

void SetCheckboxGroupSelectAllImpl(ArkUINodeHandle node, ArkUI_Bool isSelected)
{
    GetCheckboxGroupImpl()->SetSelectAll(isSelected);
}

void SetCheckboxGroupSelectedColorImpl(ArkUINodeHandle node, uint32_t color, void* colorRawPtr)
{
    GetCheckboxGroupImpl()->SetSelectedColor(Color(color));
}

void SetCheckboxGroupOnChangeImpl(ArkUINodeHandle node, void* callback)
{
    CHECK_NULL_VOID(callback);
    auto onChange = reinterpret_cast<std::function<void (const BaseEventInfo*)>*>(callback);
    GetCheckboxGroupImpl()->SetOnChange(std::move(*onChange));
}

void SetCheckboxGroupPaddingImpl(
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
    GetCheckboxGroupImpl()->SetPadding(oldPadding, padding, flag);
}

void SetCheckboxGroupResponseRegionImpl(
    ArkUINodeHandle node, const float* values, const int32_t* units, uint32_t length)
{
    std::vector<DimensionRect> region;
    uint32_t ARRAY_LENGTH = 4; // 4: dimension length
    for (uint32_t i = 0; i < length / ARRAY_LENGTH; i++) {
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

void ResetCheckboxGroupResponseRegionImpl(ArkUINodeHandle node)
{
    GetViewAbstractModelImpl()->SetResponseRegion({});
}

void ResetCheckboxGroupSelectedColorImpl(ArkUINodeHandle node) {}

void ResetCheckboxGroupUnSelectedColorImpl(ArkUINodeHandle node) {}

void ResetCheckboxGroupCheckMarkColorImpl(ArkUINodeHandle node) {}

void SetCheckboxGroupChangeEventImpl(void* callback) {}

void ResetCheckboxGroupWidthImpl(ArkUINodeHandle node) {}

void ResetCheckboxGroupHeightImpl(ArkUINodeHandle node) {}

void SetCheckboxGroupSizeImpl(
    ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_CharPtr calcValue, void* resPtr, ArkUI_Bool isWidth)
{
    if (LessNotEqual(value, 0.0)) {
        if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            return;
        }
        value = 0.0f;
    }
    CalcDimension dimension;
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    if (unitEnum == DimensionUnit::CALC) {
        dimension = CalcDimension(std::string(calcValue));
    } else {
        dimension = CalcDimension(value, unitEnum);
    }
    if (isWidth) {
        GetViewAbstractModelImpl()->SetWidth(dimension);
    } else {
        GetViewAbstractModelImpl()->SetHeight(dimension);
    }
}
#endif

const ArkUICheckboxGroupModifier* GetCheckboxGroupDynamicModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (!isCurrentUseNewPipeline) {
#ifndef CROSS_PLATFORM
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUICheckboxGroupModifier modifier = {
            .setCheckboxGroupSelectedColor = nullptr,
            .resetCheckboxGroupSelectedColor = ResetCheckboxGroupSelectedColorImpl,
            .setCheckboxGroupUnSelectedColor = nullptr,
            .resetCheckboxGroupUnSelectedColor = ResetCheckboxGroupUnSelectedColorImpl,
            .setCheckboxGroupSelectAll = SetCheckboxGroupSelectAllImpl,
            .resetCheckboxGroupSelectAll = nullptr,
            .setCheckboxGroupWidth = nullptr,
            .resetCheckboxGroupWidth = ResetCheckboxGroupWidthImpl,
            .setCheckboxGroupHeight = nullptr,
            .resetCheckboxGroupHeight = ResetCheckboxGroupHeightImpl,
            .setCheckboxGroupMark = nullptr,
            .resetCheckboxGroupMark = nullptr,
            .setCheckboxGroupStyle = nullptr,
            .resetCheckboxGroupStyle = nullptr,
            .setCheckboxGroupName = nullptr,
            .setCheckboxGroupOnChange = SetCheckboxGroupOnChangeImpl,
            .resetCheckboxGroupOnChange = nullptr,
            .getCheckboxGroupName = nullptr,
            .getCheckboxGroupSelectAll = nullptr,
            .getCheckboxGroupSelectedColor = nullptr,
            .getCheckboxGroupUnSelectedColor = nullptr,
            .getCheckboxGroupMarkColor = nullptr,
            .getCheckboxGroupMarkSize = nullptr,
            .getCheckboxGroupMarkWidth = nullptr,
            .getCheckboxGroupStyle = nullptr,
            .setCheckboxGroupSelectedColorPtr = SetCheckboxGroupSelectedColorImpl,
            .setCheckboxGroupUnSelectedColorPtr = nullptr,
            .createCheckboxGroup = CreateCheckboxGroupImpl,
            .setCheckMarkColor = nullptr,
            .resetCheckMarkColor = ResetCheckboxGroupCheckMarkColorImpl,
            .setCheckMarkSize = nullptr,
            .setCheckMarkWidth = nullptr,
            .setCheckboxGroupResponseRegion = SetCheckboxGroupResponseRegionImpl,
            .resetCheckboxGroupResponseRegion = ResetCheckboxGroupResponseRegionImpl,
            .setCheckboxGroupPadding = SetCheckboxGroupPaddingImpl,
            .setCheckboxGroupChangeEvent = SetCheckboxGroupChangeEventImpl,
            .setCheckboxGroupSize = SetCheckboxGroupSizeImpl,
        };
        CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
        return &modifier;
#endif
    }
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUICheckboxGroupModifier modifier = {
        .setCheckboxGroupSelectedColor = SetCheckboxGroupSelectedColor,
        .resetCheckboxGroupSelectedColor = ResetCheckboxGroupSelectedColor,
        .setCheckboxGroupUnSelectedColor = SetCheckboxGroupUnSelectedColor,
        .resetCheckboxGroupUnSelectedColor = ResetCheckboxGroupUnSelectedColor,
        .setCheckboxGroupSelectAll = SetCheckboxGroupSelectAll,
        .resetCheckboxGroupSelectAll = ResetCheckboxGroupSelectAll,
        .setCheckboxGroupWidth = SetCheckboxGroupWidth,
        .resetCheckboxGroupWidth = ResetCheckboxGroupWidth,
        .setCheckboxGroupHeight = SetCheckboxGroupHeight,
        .resetCheckboxGroupHeight = ResetCheckboxGroupHeight,
        .setCheckboxGroupMark = SetCheckboxGroupMark,
        .resetCheckboxGroupMark = ResetCheckboxGroupMark,
        .setCheckboxGroupStyle = SetCheckboxGroupStyle,
        .resetCheckboxGroupStyle = ResetCheckboxGroupStyle,
        .setCheckboxGroupName = SetCheckboxGroupName,
        .setCheckboxGroupOnChange = SetCheckboxGroupOnChange,
        .resetCheckboxGroupOnChange = ResetCheckboxGroupOnChange,
        .getCheckboxGroupName = GetCheckboxGroupName,
        .getCheckboxGroupSelectAll = GetCheckboxGroupSelectAll,
        .getCheckboxGroupSelectedColor = GetCheckboxGroupSelectedColor,
        .getCheckboxGroupUnSelectedColor = GetCheckboxGroupUnSelectedColor,
        .getCheckboxGroupMarkColor = GetCheckboxGroupMarkColor,
        .getCheckboxGroupMarkSize = GetCheckboxGroupMarkSize,
        .getCheckboxGroupMarkWidth = GetCheckboxGroupMarkWidth,
        .getCheckboxGroupStyle = GetCheckboxGroupStyle,
        .setCheckboxGroupSelectedColorPtr = SetCheckboxGroupSelectedColorPtr,
        .setCheckboxGroupUnSelectedColorPtr = SetCheckboxGroupUnSelectedColorPtr,
        .createCheckboxGroup = CreateCheckboxGroup,
        .setCheckMarkColor = SetCheckMarkColor,
        .resetCheckMarkColor = ResetCheckMarkColor,
        .setCheckMarkSize = SetCheckboxGroupCheckMarkSize,
        .setCheckMarkWidth = SetCheckboxGroupCheckMarkWidth,
        .setCheckboxGroupResponseRegion = SetCheckboxGroupResponseRegion,
        .resetCheckboxGroupResponseRegion = ResetCheckboxGroupResponseRegion,
        .setCheckboxGroupPadding = SetCheckboxGroupPadding,
        .setCheckboxGroupChangeEvent = SetCheckboxGroupChangeEvent,
        .setCheckboxGroupSize = SetCheckboxGroupSize,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUICheckboxGroupModifier* GetCJUICheckboxGroupModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUICheckboxGroupModifier modifier = {
        .setCheckboxGroupSelectedColor = SetCheckboxGroupSelectedColor,
        .resetCheckboxGroupSelectedColor = ResetCheckboxGroupSelectedColor,
        .setCheckboxGroupUnSelectedColor = SetCheckboxGroupUnSelectedColor,
        .resetCheckboxGroupUnSelectedColor = ResetCheckboxGroupUnSelectedColor,
        .setCheckboxGroupSelectAll = SetCheckboxGroupSelectAll,
        .resetCheckboxGroupSelectAll = ResetCheckboxGroupSelectAll,
        .setCheckboxGroupWidth = SetCheckboxGroupWidth,
        .resetCheckboxGroupWidth = ResetCheckboxGroupWidth,
        .setCheckboxGroupHeight = SetCheckboxGroupHeight,
        .resetCheckboxGroupHeight = ResetCheckboxGroupHeight,
        .setCheckboxGroupMark = SetCheckboxGroupMark,
        .resetCheckboxGroupMark = ResetCheckboxGroupMark,
        .setCheckboxGroupStyle = SetCheckboxGroupStyle,
        .resetCheckboxGroupStyle = ResetCheckboxGroupStyle,
        .setCheckboxGroupName = SetCheckboxGroupName,
        .getCheckboxGroupName = GetCheckboxGroupName,
        .getCheckboxGroupSelectAll = GetCheckboxGroupSelectAll,
        .getCheckboxGroupSelectedColor = GetCheckboxGroupSelectedColor,
        .getCheckboxGroupUnSelectedColor = GetCheckboxGroupUnSelectedColor,
        .getCheckboxGroupMarkColor = GetCheckboxGroupMarkColor,
        .getCheckboxGroupMarkSize = GetCheckboxGroupMarkSize,
        .getCheckboxGroupMarkWidth = GetCheckboxGroupMarkWidth,
        .getCheckboxGroupStyle = GetCheckboxGroupStyle,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const ArkUICheckboxGroupCustomModifier* GetCheckboxGroupDynamicCustomModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUICheckboxGroupCustomModifier modifier = {
        .resetCheckboxGroupOnChange = ResetCheckboxGroupOnChange,
        .createCheckboxGroupFrameNode = CreateCheckboxGroupFrameNode,
        .setCheckboxGroupOnChangeExtraParam = SetCheckboxGroupOnChangeExtraParam,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
}