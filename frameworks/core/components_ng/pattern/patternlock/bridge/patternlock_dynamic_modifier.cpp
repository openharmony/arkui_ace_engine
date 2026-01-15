/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/interfaces/native/node/pattern_lock_modifier.h"
#include "core/components_v2/pattern_lock/pattern_lock_theme.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/patternlock/bridge/patternlock_model_impl.h"
#include "core/components_ng/pattern/patternlock/patternlock_model_ng.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_pattern_lock.h"

namespace OHOS::Ace {
#ifndef CROSS_PLATFORM
Framework::PatternLockModelImpl* GetPatternLockModelImpl()
{
    static Framework::PatternLockModelImpl instance;
    return &instance;
}
#endif
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
FrameNode* GetFrameNode(ArkUINodeHandle node)
{
    return node ? reinterpret_cast<FrameNode*>(node) : ViewStackProcessor::GetInstance()->GetMainFrameNode();
}

ArkUINodeHandle CreateFrameNode(int32_t nodeId)
{
    return nullptr;
}

void CreateModel(ArkUI_Bool isObject, void* controller)
{
    static PatternLockModelNG model;
    auto controllers = model.Create();
    auto* jsController = static_cast<Framework::JSPatternLockController*>(controller);
    if (isObject) {
        jsController->SetController(controllers);
    }
}

void SetPatternLockActiveColor(ArkUINodeHandle node, uint32_t value)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetActiveColor(frameNode, Color(value));
}

void SetPatternLockActiveColorByUser(ArkUINodeHandle node, uint32_t value, bool isByuserSet)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetActiveColorByUser(frameNode, isByuserSet);
}

void SetPatternLockActiveColorRes(ArkUINodeHandle node, uint32_t value, void* activeColorRawPtr)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetActiveColor(frameNode, Color(value));
    if (SystemProperties::ConfigChangePerform()) {
        auto* activeColor = reinterpret_cast<ResourceObject*>(activeColorRawPtr);
        auto activeColorResObj = AceType::Claim(activeColor);
        PatternLockModelNG::CreateWithResourceObj(frameNode, PatternLockResourceType::ACTIVECOLOR, activeColorResObj);
    }
}

void ResetPatternLockActiveColor(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto patternLockTheme = GetTheme<V2::PatternLockTheme>();
    CHECK_NULL_VOID(patternLockTheme);
    Color activeColor = patternLockTheme->GetActiveColor();
    PatternLockModelNG::SetActiveColor(frameNode, activeColor);
    if (SystemProperties::ConfigChangePerform()) {
        PatternLockModelNG::SetActiveColorByUser(frameNode, false);
        PatternLockModelNG::CreateWithResourceObj(frameNode, PatternLockResourceType::ACTIVECOLOR, nullptr);
    }
}

void ResetPatternLockCircleRadius(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto patternLockTheme = GetTheme<V2::PatternLockTheme>();
    CHECK_NULL_VOID(patternLockTheme);
    CalcDimension radius = patternLockTheme->GetCircleRadius();
    PatternLockModelNG::SetCircleRadius(frameNode, Dimension(radius.Value(), radius.Unit()));
    if (SystemProperties::ConfigChangePerform()) {
        PatternLockModelNG::CreateWithResourceObj(frameNode, PatternLockResourceType::CIRCLERADIUS, nullptr);
    }
}

void SetPatternLockCircleRadius(ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetCircleRadius(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
}

void SetPatternLockCircleRadiusRes(
    ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit, void* circleRadiusRawPtr)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetCircleRadius(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
    if (SystemProperties::ConfigChangePerform()) {
        auto* circleRadius = reinterpret_cast<ResourceObject*>(circleRadiusRawPtr);
        auto circleRadiusResObj = AceType::Claim(circleRadius);
        PatternLockModelNG::CreateWithResourceObj(frameNode, PatternLockResourceType::CIRCLERADIUS, circleRadiusResObj);
    }
}

void SetPatternLockSelectedColor(ArkUINodeHandle node, uint32_t value)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetSelectedColor(frameNode, Color(value));
}

void SetPatternLockSelectedColorRes(ArkUINodeHandle node, uint32_t value, void* selectedColorRawPtr)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetSelectedColor(frameNode, Color(value));
    if (SystemProperties::ConfigChangePerform()) {
        auto* selectedColor = reinterpret_cast<ResourceObject*>(selectedColorRawPtr);
        auto selectedColorResObj = AceType::Claim(selectedColor);
        PatternLockModelNG::CreateWithResourceObj(
            frameNode, PatternLockResourceType::SELECTEDCOLOR, selectedColorResObj);
    }
}

void ResetPatternLockSelectedColor(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto patternLockTheme = GetTheme<V2::PatternLockTheme>();
    CHECK_NULL_VOID(patternLockTheme);
    Color selectedColor = patternLockTheme->GetSelectedColor();
    PatternLockModelNG::SetSelectedColor(frameNode, selectedColor);
    if (SystemProperties::ConfigChangePerform()) {
        PatternLockModelNG::SetSelectedColorByUser(frameNode, false);
        PatternLockModelNG::CreateWithResourceObj(frameNode, PatternLockResourceType::SELECTEDCOLOR, nullptr);
    }
}

void SetPatternLockSideLength(ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetSideLength(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
}

void SetPatternLockSideLengthRes(ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit, void* sideLengthRawPtr)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetSideLength(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
    if (SystemProperties::ConfigChangePerform()) {
        auto* sideLength = reinterpret_cast<ResourceObject*>(sideLengthRawPtr);
        auto sideLengthResObj = AceType::Claim(sideLength);
        PatternLockModelNG::CreateWithResourceObj(frameNode, PatternLockResourceType::SIDELENGTH, sideLengthResObj);
    }
}

void ResetPatternLockSideLength(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto patternLockTheme = GetTheme<V2::PatternLockTheme>();
    CHECK_NULL_VOID(patternLockTheme);
    CalcDimension sideLength = patternLockTheme->GetSideLength();
    PatternLockModelNG::SetSideLength(frameNode, Dimension(sideLength.Value(), sideLength.Unit()));
    if (SystemProperties::ConfigChangePerform()) {
        PatternLockModelNG::CreateWithResourceObj(frameNode, PatternLockResourceType::SIDELENGTH, nullptr);
    }
}

void SetPatternLockAutoReset(ArkUINodeHandle node, uint32_t value)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetAutoReset(frameNode, static_cast<bool>(value));
}

void ResetPatternLockAutoReset(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetAutoReset(frameNode, true);
}

void SetPatternLockPathStrokeWidth(ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetStrokeWidth(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
}

void ResetPatternLockPathStrokeWidth(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto patternLockTheme = GetTheme<V2::PatternLockTheme>();
    CHECK_NULL_VOID(patternLockTheme);
    CalcDimension lineWidth = patternLockTheme->GetPathStrokeWidth();
    PatternLockModelNG::SetStrokeWidth(frameNode, lineWidth);
}

void SetPatternLockRegularColor(ArkUINodeHandle node, uint32_t color)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetRegularColor(frameNode, Color(color));
}

void SetPatternLockRegularColorRes(ArkUINodeHandle node, uint32_t color, void* regularColorRawPtr)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetRegularColor(frameNode, Color(color));
    if (SystemProperties::ConfigChangePerform()) {
        auto* regularColor = reinterpret_cast<ResourceObject*>(regularColorRawPtr);
        auto regularColorResObj = AceType::Claim(regularColor);
        PatternLockModelNG::CreateWithResourceObj(frameNode, PatternLockResourceType::REGULARCOLOR, regularColorResObj);
    }
}

void ResetPatternLockRegularColor(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto patternLockTheme = GetTheme<V2::PatternLockTheme>();
    CHECK_NULL_VOID(patternLockTheme);
    Color regularColor = patternLockTheme->GetRegularColor();
    PatternLockModelNG::SetRegularColor(frameNode, regularColor);
    if (SystemProperties::ConfigChangePerform()) {
        PatternLockModelNG::SetRegularColorByUser(frameNode, false);
        PatternLockModelNG::CreateWithResourceObj(frameNode, PatternLockResourceType::REGULARCOLOR, nullptr);
    }
}

void SetPatternLockPathColor(ArkUINodeHandle node, uint32_t color)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetPathColor(frameNode, Color(color));
}

void SetPatternLockPathColorRes(ArkUINodeHandle node, uint32_t color, void* pathColorRawPtr)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetPathColor(frameNode, Color(color));
    if (SystemProperties::ConfigChangePerform()) {
        auto* pathColor = reinterpret_cast<ResourceObject*>(pathColorRawPtr);
        auto pathColorResObj = AceType::Claim(pathColor);
        PatternLockModelNG::CreateWithResourceObj(frameNode, PatternLockResourceType::PATHCOLOR, pathColorResObj);
    }
}

void ResetPatternLockPathColor(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto patternLockTheme = GetTheme<V2::PatternLockTheme>();
    CHECK_NULL_VOID(patternLockTheme);
    Color pathColor = patternLockTheme->GetPathColor();
    PatternLockModelNG::SetPathColor(frameNode, pathColor);
    if (SystemProperties::ConfigChangePerform()) {
        PatternLockModelNG::SetPathColorByUser(frameNode, false);
        PatternLockModelNG::CreateWithResourceObj(frameNode, PatternLockResourceType::PATHCOLOR, nullptr);
    }
}

void SetPatternLockActiveCircleColor(ArkUINodeHandle node, uint32_t value)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetActiveCircleColor(frameNode, Color(value));
}

void SetPatternLockActiveCircleColorRes(ArkUINodeHandle node, uint32_t value, void* activeCircleColorRawPtr)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetActiveCircleColor(frameNode, Color(value));
    if (SystemProperties::ConfigChangePerform()) {
        auto* activeCircleColor = reinterpret_cast<ResourceObject*>(activeCircleColorRawPtr);
        auto activeCircleColorResObj = AceType::Claim(activeCircleColor);
        PatternLockModelNG::CreateWithResourceObj(
            frameNode, PatternLockResourceType::ACTIVECIRCLECOLOR, activeCircleColorResObj);
    }
}

void ResetPatternLockActiveCircleColor(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetActiveCircleColor(frameNode, Color::TRANSPARENT);
    if (SystemProperties::ConfigChangePerform()) {
        PatternLockModelNG::SetActiveCircleColorByUser(frameNode, false);
        PatternLockModelNG::CreateWithResourceObj(frameNode, PatternLockResourceType::ACTIVECIRCLECOLOR, nullptr);
    }
}

void SetPatternLockActiveCircleRadius(ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetActiveCircleRadius(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
}

void ResetPatternLockActiveCircleRadius(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto patternLockTheme = GetTheme<V2::PatternLockTheme>();
    CHECK_NULL_VOID(patternLockTheme);
    CalcDimension radius = patternLockTheme->GetCircleRadius();
    PatternLockModelNG::SetActiveCircleRadius(frameNode, Dimension(0.0f, DimensionUnit::VP));
}

void SetPatternLockEnableWaveEffect(ArkUINodeHandle node, uint32_t value)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetEnableWaveEffect(frameNode, static_cast<bool>(value));
}

void ResetPatternLockEnableWaveEffect(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetEnableWaveEffect(frameNode, true);
}

void SetPatternLockEnableForeground(ArkUINodeHandle node, uint32_t value)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetEnableForeground(frameNode, static_cast<bool>(value));
}

void ResetPatternLockEnableForeground(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetEnableForeground(frameNode, false);
}

void SetPatternLockSkipUnselectedPoint(ArkUINodeHandle node, uint32_t value)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetSkipUnselectedPoint(frameNode, static_cast<bool>(value));
}

void ResetPatternLockSkipUnselectedPoint(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetSkipUnselectedPoint(frameNode, false);
}

void SetPatternLockOnPatternComplete(ArkUINodeHandle node, void* callback)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onPatternComplete = reinterpret_cast<NG::PatternLockCompleteEvent*>(callback);
        PatternLockModelNG::SetPatternComplete(frameNode, std::move(*onPatternComplete));
    } else {
        PatternLockModelNG::SetPatternComplete(frameNode, nullptr);
    }
}

void ResetPatternLockOnPatternComplete(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetPatternComplete(frameNode, nullptr);
}

void SetPatternLockOnDotConnect(ArkUINodeHandle node, void* callback)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onDotConnect = reinterpret_cast<std::function<void(int32_t)>*>(callback);
        PatternLockModelNG::SetDotConnect(frameNode, std::move(*onDotConnect));
    } else {
        PatternLockModelNG::SetDotConnect(frameNode, nullptr);
    }
}

void ResetPatternLockOnDotConnect(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetDotConnect(frameNode, nullptr);
}

#ifndef CROSS_PLATFORM
void CreateModelImpl(ArkUI_Bool isObject, void* controller)
{
    auto controllers = GetPatternLockModelImpl()->Create();
    auto* jsController = static_cast<Framework::JSPatternLockController*>(controller);
    if (isObject) {
        jsController->SetController(controllers);
    }
}
void SetPatternLockActiveColorImpl(ArkUINodeHandle node, uint32_t value)
{
    auto activeColor = Color(value);
    GetPatternLockModelImpl()->SetActiveColor(activeColor);
}

void SetPatternLockActiveColorByUserImpl(ArkUINodeHandle node, uint32_t value, bool isByuserSet)
{
    GetPatternLockModelImpl()->SetActiveColorByUser(isByuserSet);
}

void SetPatternLockActiveColorResImpl(ArkUINodeHandle node, uint32_t value, void* activeColorRawPtr)
{
    auto activeColor = Color(value);
    GetPatternLockModelImpl()->SetActiveColor(activeColor);
}

void SetPatternLockCircleRadiusImpl(ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit)
{
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    GetPatternLockModelImpl()->SetCircleRadius(Dimension(number, unitEnum));
}

void SetPatternLockCircleRadiusResImpl(
    ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit, void* circleRadiusRawPtr)
{
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    GetPatternLockModelImpl()->SetCircleRadius(Dimension(number, unitEnum));
}

void SetPatternLockSelectedColorImpl(ArkUINodeHandle node, uint32_t value)
{
    auto activeColor = Color(value);
    GetPatternLockModelImpl()->SetSelectedColor(activeColor);
}

void SetPatternLockSelectedColorResImpl(ArkUINodeHandle node, uint32_t value, void* selectedColorRawPtr)
{
    auto activeColor = Color(value);
    GetPatternLockModelImpl()->SetSelectedColor(activeColor);
}

void SetPatternLockSideLengthImpl(ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit)
{
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    GetPatternLockModelImpl()->SetSideLength(Dimension(number, unitEnum));
}

void SetPatternLockSideLengthResImpl(
    ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit, void* sideLengthRawPtr)
{
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    GetPatternLockModelImpl()->SetSideLength(Dimension(number, unitEnum));
}

void SetPatternLockAutoResetImpl(ArkUINodeHandle node, uint32_t value)
{
    GetPatternLockModelImpl()->SetAutoReset(value);
}

void SetPatternLockPathStrokeWidthImpl(ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit)
{
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    GetPatternLockModelImpl()->SetStrokeWidth(Dimension(number, unitEnum));
}

void SetPatternLockRegularColorImpl(ArkUINodeHandle node, uint32_t color)
{
    GetPatternLockModelImpl()->SetRegularColor(Color(color));
}

void SetPatternLockRegularColorResImpl(ArkUINodeHandle node, uint32_t color, void* regularColorRawPtr)
{
    GetPatternLockModelImpl()->SetRegularColor(Color(color));
}

void SetPatternLockPathColorImpl(ArkUINodeHandle node, uint32_t color)
{
    GetPatternLockModelImpl()->SetPathColor(Color(color));
}

void SetPatternLockPathColorResImpl(ArkUINodeHandle node, uint32_t color, void* pathColorRawPtr)
{
    GetPatternLockModelImpl()->SetPathColor(Color(color));
}

void SetPatternLockActiveCircleColorImpl(ArkUINodeHandle node, uint32_t value)
{
    GetPatternLockModelImpl()->SetActiveCircleColor(Color(value));
}

void SetPatternLockActiveCircleColorResImpl(ArkUINodeHandle node, uint32_t value, void* activeCircleColorRawPtr)
{
    GetPatternLockModelImpl()->SetActiveCircleColor(Color(value));
}

void SetPatternLockActiveCircleRadiusImpl(ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit)
{
    GetPatternLockModelImpl()->SetActiveCircleRadius(Dimension(number, static_cast<DimensionUnit>(unit)));
}

void SetPatternLockEnableWaveEffectImpl(ArkUINodeHandle node, uint32_t value)
{
    GetPatternLockModelImpl()->SetEnableWaveEffect(value);
}

void SetPatternLockEnableForegroundImpl(ArkUINodeHandle node, uint32_t value)
{
    GetPatternLockModelImpl()->SetEnableForeground(value);
}

void SetPatternLockSkipUnselectedPointImpl(ArkUINodeHandle node, uint32_t value)
{
    GetPatternLockModelImpl()->SetSkipUnselectedPoint(value);
}

void SetPatternLockOnPatternCompleteImpl(ArkUINodeHandle node, void* callback)
{
    auto onPatternComplete = reinterpret_cast<NG::PatternLockCompleteEvent*>(callback);
    GetPatternLockModelImpl()->SetPatternComplete(std::move(*onPatternComplete));
}

void SetPatternLockOnDotConnectImpl(ArkUINodeHandle node, void* callback)
{
    auto onDotConnect = reinterpret_cast<std::function<void(int32_t)>*>(callback);
    GetPatternLockModelImpl()->SetDotConnect(std::move(*onDotConnect));
}
#endif

const ArkUIPatternLockModifier* GetPatternLockDynamicModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (!isCurrentUseNewPipeline) {
#ifndef CROSS_PLATFORM
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUIPatternLockModifier modifier = {
            .createModel = CreateModelImpl,
            .setPatternLockActiveColor = SetPatternLockActiveColorImpl,
            .setPatternLockActiveColorRes = SetPatternLockActiveColorResImpl,
            .resetPatternLockActiveColor = nullptr,
            .setPatternLockCircleRadius = SetPatternLockCircleRadiusImpl,
            .setPatternLockCircleRadiusRes = SetPatternLockCircleRadiusResImpl,
            .resetPatternLockCircleRadius = nullptr,
            .setPatternLockSelectedColor = SetPatternLockSelectedColorImpl,
            .setPatternLockSelectedColorRes = SetPatternLockSelectedColorResImpl,
            .resetPatternLockSelectedColor = nullptr,
            .setPatternLockSideLength = SetPatternLockSideLengthImpl,
            .setPatternLockSideLengthRes = SetPatternLockSideLengthResImpl,
            .resetPatternLockSideLength = nullptr,
            .setPatternLockAutoReset = SetPatternLockAutoResetImpl,
            .resetPatternLockAutoReset = nullptr,
            .setPatternLockPathStrokeWidth = SetPatternLockPathStrokeWidthImpl,
            .resetPatternLockPathStrokeWidth = nullptr,
            .setPatternLockRegularColor = SetPatternLockRegularColorImpl,
            .setPatternLockRegularColorRes = SetPatternLockRegularColorResImpl,
            .resetPatternLockRegularColor = nullptr,
            .setPatternLockPathColor = SetPatternLockPathColorImpl,
            .setPatternLockPathColorRes = SetPatternLockPathColorResImpl,
            .resetPatternLockPathColor = nullptr,
            .setPatternLockActiveCircleColor = SetPatternLockActiveCircleColorImpl,
            .setPatternLockActiveCircleColorRes = SetPatternLockActiveCircleColorResImpl,
            .resetPatternLockActiveCircleColor = nullptr,
            .setPatternLockActiveCircleRadius = SetPatternLockActiveCircleRadiusImpl,
            .resetPatternLockActiveCircleRadius = nullptr,
            .setPatternLockEnableWaveEffect = SetPatternLockEnableWaveEffectImpl,
            .resetPatternLockEnableWaveEffect = nullptr,
            .setPatternLockEnableForeground = SetPatternLockEnableForegroundImpl,
            .resetPatternLockEnableForeground = nullptr,
            .setPatternLockSkipUnselectedPoint = SetPatternLockSkipUnselectedPointImpl,
            .resetPatternLockSkipUnselectedPoint = nullptr,
            .setPatternLockOnPatternComplete = SetPatternLockOnPatternCompleteImpl,
            .resetPatternLockOnPatternComplete = nullptr,
            .setPatternLockOnDotConnect = SetPatternLockOnDotConnectImpl,
            .resetPatternLockOnDotConnect = nullptr,
            .createFrameNode = CreateFrameNode,
        };
        CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
        return &modifier;
#endif
    }
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIPatternLockModifier modifier = {
        .createModel = CreateModel,
        .setPatternLockActiveColor = SetPatternLockActiveColor,
        .setPatternLockActiveColorRes = SetPatternLockActiveColorRes,
        .resetPatternLockActiveColor = ResetPatternLockActiveColor,
        .setPatternLockCircleRadius = SetPatternLockCircleRadius,
        .setPatternLockCircleRadiusRes = SetPatternLockCircleRadiusRes,
        .resetPatternLockCircleRadius = ResetPatternLockCircleRadius,
        .setPatternLockSelectedColor = SetPatternLockSelectedColor,
        .setPatternLockSelectedColorRes = SetPatternLockSelectedColorRes,
        .resetPatternLockSelectedColor = ResetPatternLockSelectedColor,
        .setPatternLockSideLength = SetPatternLockSideLength,
        .setPatternLockSideLengthRes = SetPatternLockSideLengthRes,
        .resetPatternLockSideLength = ResetPatternLockSideLength,
        .setPatternLockAutoReset = SetPatternLockAutoReset,
        .resetPatternLockAutoReset = ResetPatternLockAutoReset,
        .setPatternLockPathStrokeWidth = SetPatternLockPathStrokeWidth,
        .resetPatternLockPathStrokeWidth = ResetPatternLockPathStrokeWidth,
        .setPatternLockRegularColor = SetPatternLockRegularColor,
        .setPatternLockRegularColorRes = SetPatternLockRegularColorRes,
        .resetPatternLockRegularColor = ResetPatternLockRegularColor,
        .setPatternLockPathColor = SetPatternLockPathColor,
        .setPatternLockPathColorRes = SetPatternLockPathColorRes,
        .resetPatternLockPathColor = ResetPatternLockPathColor,
        .setPatternLockActiveCircleColor = SetPatternLockActiveCircleColor,
        .setPatternLockActiveCircleColorRes = SetPatternLockActiveCircleColorRes,
        .resetPatternLockActiveCircleColor = ResetPatternLockActiveCircleColor,
        .setPatternLockActiveCircleRadius = SetPatternLockActiveCircleRadius,
        .resetPatternLockActiveCircleRadius = ResetPatternLockActiveCircleRadius,
        .setPatternLockEnableWaveEffect = SetPatternLockEnableWaveEffect,
        .resetPatternLockEnableWaveEffect = ResetPatternLockEnableWaveEffect,
        .setPatternLockEnableForeground = SetPatternLockEnableForeground,
        .resetPatternLockEnableForeground = ResetPatternLockEnableForeground,
        .setPatternLockSkipUnselectedPoint = SetPatternLockSkipUnselectedPoint,
        .resetPatternLockSkipUnselectedPoint = ResetPatternLockSkipUnselectedPoint,
        .setPatternLockOnPatternComplete = SetPatternLockOnPatternComplete,
        .resetPatternLockOnPatternComplete = ResetPatternLockOnPatternComplete,
        .setPatternLockOnDotConnect = SetPatternLockOnDotConnect,
        .resetPatternLockOnDotConnect = ResetPatternLockOnDotConnect,
        .createFrameNode = CreateFrameNode,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUIPatternLockModifier* GetCJUIPatternLockModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIPatternLockModifier modifier = {
        .setPatternLockActiveColor = SetPatternLockActiveColor,
        .setPatternLockActiveColorRes = SetPatternLockActiveColorRes,
        .resetPatternLockActiveColor = ResetPatternLockActiveColor,
        .setPatternLockCircleRadius = SetPatternLockCircleRadius,
        .setPatternLockCircleRadiusRes = SetPatternLockCircleRadiusRes,
        .resetPatternLockCircleRadius = ResetPatternLockCircleRadius,
        .setPatternLockSelectedColor = SetPatternLockSelectedColor,
        .setPatternLockSelectedColorRes = SetPatternLockSelectedColorRes,
        .resetPatternLockSelectedColor = ResetPatternLockSelectedColor,
        .setPatternLockSideLength = SetPatternLockSideLength,
        .setPatternLockSideLengthRes = SetPatternLockSideLengthRes,
        .resetPatternLockSideLength = ResetPatternLockSideLength,
        .setPatternLockAutoReset = SetPatternLockAutoReset,
        .resetPatternLockAutoReset = ResetPatternLockAutoReset,
        .setPatternLockPathStrokeWidth = SetPatternLockPathStrokeWidth,
        .resetPatternLockPathStrokeWidth = ResetPatternLockPathStrokeWidth,
        .setPatternLockRegularColor = SetPatternLockRegularColor,
        .setPatternLockRegularColorRes = SetPatternLockRegularColorRes,
        .resetPatternLockRegularColor = ResetPatternLockRegularColor,
        .setPatternLockPathColor = SetPatternLockPathColor,
        .setPatternLockPathColorRes = SetPatternLockPathColorRes,
        .resetPatternLockPathColor = ResetPatternLockPathColor,
        .setPatternLockActiveCircleColor = SetPatternLockActiveCircleColor,
        .setPatternLockActiveCircleColorRes = SetPatternLockActiveCircleColorRes,
        .resetPatternLockActiveCircleColor = ResetPatternLockActiveCircleColor,
        .setPatternLockActiveCircleRadius = SetPatternLockActiveCircleRadius,
        .resetPatternLockActiveCircleRadius = ResetPatternLockActiveCircleRadius,
        .setPatternLockEnableWaveEffect = SetPatternLockEnableWaveEffect,
        .resetPatternLockEnableWaveEffect = ResetPatternLockEnableWaveEffect,
        .setPatternLockEnableForeground = SetPatternLockEnableForeground,
        .resetPatternLockEnableForeground = ResetPatternLockEnableForeground,
        .setPatternLockSkipUnselectedPoint = SetPatternLockSkipUnselectedPoint,
        .resetPatternLockSkipUnselectedPoint = ResetPatternLockSkipUnselectedPoint,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

} // namespace OHOS::Ace::NG
