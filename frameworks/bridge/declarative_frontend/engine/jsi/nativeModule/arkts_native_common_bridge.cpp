/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.h"
#include <utility>

#include "ark_native_engine.h"
#include "jsnapi_expo.h"

#include "base/memory/ace_type.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/functions/js_should_built_in_recognizer_parallel_with_function.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "bridge/declarative_frontend/engine/jsi/js_ui_index.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_types.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_frame_node_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_utils_bridge.h"
#include "bridge/declarative_frontend/jsview/js_gesture.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/jsview/js_view_context.h"
#include "bridge/js_frontend/engine/jsi/ark_js_runtime.h"
#include "core/common/resource/resource_parse_utils.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_accessibility_function.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_shape_abstract.h"
#include "frameworks/core/components_ng/pattern/text/span_model_ng.h"

#include "base/log/ace_scoring_log.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/jsview/js_accessibility.h"
#include "bridge/declarative_frontend/jsview/js_popups.h"
#include "bridge/declarative_frontend/style_string/js_span_string.h"
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
namespace {
constexpr uint32_t COLOR_ALPHA_VALUE = 0xFF000000;
constexpr uint32_t ALIGNMENT_TOP_LEFT = 0;
constexpr uint32_t ALIGNMENT_CENTER = 4;
constexpr int32_t DEFAULT_LAYOUT_SAFE_AREA_EDGE_FOR_COLOR_BACKGROUND = 6;
constexpr float DEFAULT_PROGRESS_TOTAL = 100.0f;
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int NUM_5 = 5;
constexpr int NUM_6 = 6;
constexpr int NUM_7 = 7;
constexpr int NUM_8 = 8;
constexpr int NUM_9 = 9;
constexpr int NUM_10 = 10;
constexpr int NUM_11 = 11;
constexpr int NUM_12 = 12;
constexpr int NUM_13 = 13;
constexpr int SIZE_OF_ONE = 1;
constexpr int SIZE_OF_TWO = 2;
constexpr int SIZE_OF_THREE = 3;
constexpr int SIZE_OF_FOUR = 4;
constexpr int SIZE_OF_FIVE = 5;
constexpr int SIZE_OF_SEVEN = 7;
constexpr int SIZE_OF_EIGHT = 8;
constexpr int32_t ALIGN_RULES_NUM = 6;
constexpr int32_t ALIGN_DIRECTION_DEFAULT = 2;
constexpr double FULL_DIMENSION = 100.0;
constexpr double HALF_DIMENSION = 50.0;
constexpr uint32_t DEFAULT_DURATION = 1000;
constexpr int64_t MICROSEC_TO_MILLISEC = 1000;
constexpr int32_t MAX_ALIGN_VALUE = 8;
constexpr int32_t BACKWARD_COMPAT_MAGIC_NUMBER_OFFSCREEN = 1000;
constexpr SharedTransitionEffectType DEFAULT_SHARED_EFFECT = SharedTransitionEffectType::SHARED_EFFECT_EXCHANGE;
constexpr int32_t DEFAULT_TAP_FINGER = 1;
constexpr int32_t DEFAULT_TAP_COUNT = 1;
constexpr double DEFAULT_TAP_DISTANCE = std::numeric_limits<double>::infinity();
constexpr int32_t DEFAULT_LONG_PRESS_FINGER = 1;
constexpr int32_t DEFAULT_LONG_PRESS_DURATION = 500;
constexpr int32_t DEFAULT_PINCH_FINGER = 2;
constexpr int32_t DEFAULT_MAX_PINCH_FINGER = 5;
constexpr double DEFAULT_PINCH_DISTANCE = 5.0;
constexpr int32_t DEFAULT_PAN_FINGER = 1;
constexpr int32_t DEFAULT_MAX_FINGERS = 10;
constexpr OHOS::Ace::Dimension DEFAULT_PAN_DISTANCE = 5.0_vp;
constexpr OHOS::Ace::Dimension DEFAULT_PEN_PAN_DISTANCE = 8.0_vp;
constexpr int32_t DEFAULT_SLIDE_FINGER = DEFAULT_PAN_FINGER;
constexpr double DEFAULT_SLIDE_SPEED = 100.0;
constexpr int32_t DEFAULT_ROTATION_FINGER = 2;
constexpr int32_t DEFAULT_MAX_ROTATION_FINGER = 5;
constexpr double DEFAULT_ROTATION_ANGLE = 1.0;
constexpr double DEFAULT_MAX_ROTATION_ANGLE = 360.0;
const std::string BLOOM_RADIUS_SYS_RES_NAME = "sys.float.ohos_id_point_light_bloom_radius";
const std::string BLOOM_COLOR_SYS_RES_NAME = "sys.color.ohos_id_point_light_bloom_color";
const std::string ILLUMINATED_BORDER_WIDTH_SYS_RES_NAME = "sys.float.ohos_id_point_light_illuminated_border_width";
constexpr double VISIBLE_RATIO_MIN = 0.0;
constexpr double VISIBLE_RATIO_MAX = 1.0;
enum ParseResult { LENGTHMETRICS_SUCCESS, DIMENSION_SUCCESS, FAIL };
constexpr int32_t PARAMETER_LENGTH_SECOND = 2;
constexpr int32_t PARAMETER_LENGTH_THIRD = 3;

BorderStyle ConvertBorderStyle(int32_t value)
{
    auto style = static_cast<BorderStyle>(value);
    if (style < BorderStyle::SOLID || style > BorderStyle::NONE) {
        style = BorderStyle::SOLID;
    }
    return style;
}

bool ParseJsDouble(const EcmaVM *vm, const Local<JSValueRef> &value, double &result)
{
    if (value->IsNumber()) {
        result = value->ToNumber(vm)->Value();
        return true;
    }
    if (value->IsString(vm)) {
        return StringUtils::StringToDouble(value->ToString(vm)->ToString(vm), result);
    }

    return false;
}

void ParseGradientColorStopsWithColorSpace(const EcmaVM *vm, const Local<JSValueRef> &value,
    std::vector<ArkUIInt32orFloat32> &colors, std::optional<ColorSpace> &colorSpace)
{
    if (!value->IsArray(vm)) {
        return;
    }
    auto array = panda::Local<panda::ArrayRef>(value);
    auto length = array->Length(vm);
    bool isValid = true;
    for (uint32_t index = 0; index < length; index++) {
        auto item = panda::ArrayRef::GetValueAt(vm, array, index);
        if (!item->IsArray(vm)) {
            continue;
        }
        auto itemArray = panda::Local<panda::ArrayRef>(item);
        auto itemLength = itemArray->Length(vm);
        if (itemLength < NUM_1) {
            continue;
        }
        Color color;
        auto colorParams = panda::ArrayRef::GetValueAt(vm, itemArray, NUM_0);
        if (!ArkTSUtils::ParseJsColorAlpha(vm, colorParams, color)) {
            continue;
        }
        // is valid
        if (!colorSpace.has_value()) {
            colorSpace = color.GetColorSpace();
        } else if (color.GetColorSpace() != colorSpace.value()) {
            isValid = false;
            colors.clear();
            colorSpace = ColorSpace::SRGB;
            break;
        }
        bool hasDimension = false;
        double dimension = 0.0;
        if (itemLength > NUM_1) {
            auto stopDimension = panda::ArrayRef::GetValueAt(vm, itemArray, NUM_1);
            if (ArkTSUtils::ParseJsDouble(vm, stopDimension, dimension)) {
                hasDimension = true;
            }
        }
        colors.push_back({.u32 = static_cast<ArkUI_Uint32>(color.GetValue())});
        colors.push_back({.i32 = static_cast<ArkUI_Int32>(hasDimension)});
        colors.push_back({.f32 = static_cast<ArkUI_Float32>(dimension)});
    }
}

bool ParseJsShadowColorStrategy(const EcmaVM *vm, const Local<JSValueRef> &value, ShadowColorStrategy& strategy)
{
    if (value->IsString(vm)) {
        std::string colorStr = value->ToString(vm)->ToString(vm);
        if (colorStr.compare("average") == 0) {
            strategy = ShadowColorStrategy::AVERAGE;
            return true;
        } else if (colorStr.compare("primary") == 0) {
            strategy = ShadowColorStrategy::PRIMARY;
            return true;
        }
    }
    return false;
}

bool ParseJsShadowDimension(const EcmaVM *vm, const Local<JSValueRef> &value, CalcDimension& dimension,
    std::vector<RefPtr<ResourceObject>>& vectorResObj)
{
    RefPtr<ResourceObject> shadowResObj;
    bool ret = ArkTSUtils::ParseJsResource(vm, value, dimension, shadowResObj);
    if (!ret) {
        ret = ArkTSUtils::ParseJsDimensionVp(vm, value, dimension);
    }
    if (shadowResObj) {
        vectorResObj.push_back(shadowResObj);
    } else {
        vectorResObj.push_back(nullptr);
    }
    return ret;
}

bool ParseJsShadowColor(const EcmaVM *vm, const Local<JSValueRef> &colorArg,
    int32_t& type, uint32_t& colorValue, RefPtr<ResourceObject>& colorResObj,
    ArkUINodeHandle nativeNode)
{
    Color color;
    ShadowColorStrategy shadowColorStrategy;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (ParseJsShadowColorStrategy(vm, colorArg, shadowColorStrategy)) {
        type = 1; // 1: has shadowColorStrategy
        colorValue = static_cast<uint32_t>(shadowColorStrategy);
        return true;
    } else if (ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color, colorResObj, nodeInfo)) {
        type = 2; // 2: has shadowColor
        colorValue = color.GetValue();
        return true;
    }
    return false;
}

bool ParseCalcDimensions(ArkUIRuntimeCallInfo* runtimeCallInfo, uint32_t offset, uint32_t count,
    std::vector<std::optional<CalcDimension>>& results, const CalcDimension& defValue)
{
    auto end = offset + count;
    auto argsNumber = runtimeCallInfo->GetArgsNumber();
    if (end > argsNumber) {
        return false;
    }
    bool hasValue = false;
    EcmaVM* vm = runtimeCallInfo->GetVM();
    for (uint32_t index = offset; index < end; index++) {
        auto arg = runtimeCallInfo->GetCallArgRef(index);
        std::optional<CalcDimension> optCalcDimension;
        CalcDimension dimension(defValue);
        if (ArkTSUtils::ParseJsDimensionVp(vm, arg, dimension, false)) {
            optCalcDimension = dimension;
            hasValue = true;
        }
        results.push_back(optCalcDimension);
    }
    return hasValue;
}

ParseResult ParseCalcDimensionsNG(ArkUIRuntimeCallInfo* runtimeCallInfo, uint32_t offset, uint32_t count,
    std::vector<std::optional<CalcDimension>>& results, std::vector<RefPtr<ResourceObject>>& edgesResObj,
    const CalcDimension& defValue)
{
    auto end = offset + count;
    auto argsNumber = runtimeCallInfo->GetArgsNumber();
    if (end > argsNumber) {
        return ParseResult::FAIL;
    }
    ParseResult res = ParseResult::FAIL;
    EcmaVM* vm = runtimeCallInfo->GetVM();
    for (uint32_t index = offset; index < end; index++) {
        auto arg = runtimeCallInfo->GetCallArgRef(index);
        std::optional<CalcDimension> optCalcDimension;
        RefPtr<ResourceObject> resObj;
        CalcDimension dimension(defValue);
        // Parse string, '10abc' return false
        if (ArkTSUtils::ParseJsDimensionVpNG(vm, arg, dimension, resObj, true)) {
            optCalcDimension = dimension;
            res = ParseResult::DIMENSION_SUCCESS;
        } else if (ArkTSUtils::ParseJsLengthMetrics(vm, arg, dimension)) {
            optCalcDimension = dimension;
            res = ParseResult::LENGTHMETRICS_SUCCESS;
        }
        results.push_back(optCalcDimension);
        if (SystemProperties::ConfigChangePerform()) {
            edgesResObj.push_back(resObj);
        }
    }
    return res;
}

void ParseTipsOptionsTime(
    EcmaVM* vm, ArkUIBindTipsOptionsTime& options, Local<JSValueRef> arg, ArkUI_Float32& targetField)
{
    if (!arg->IsUndefined() && !arg->IsNull() && arg->IsNumber()) {
        ArkUI_Float32 value = arg->ToNumber(vm)->Value();
        if (value >= 0) {
            targetField = value;
        }
    }
}

void ParseTipsOptionsArrowSize(EcmaVM* vm, Local<JSValueRef> arg, ArkUI_Float64& targetValue, ArkUI_Int32& targetUnit)
{
    CalcDimension dimension;
    if (!arg->IsUndefined() && !arg->IsNull() && ArkTSUtils::ParseJsDimensionVp(vm, arg, dimension, true)) {
        if (dimension.Value() > 0 && dimension.Unit() != DimensionUnit::PERCENT) {
            targetValue = dimension.Value();
            targetUnit = static_cast<ArkUI_Int32>(dimension.Unit());
        }
    }
}

void ParseTipsOptionsShowAtAnchor(EcmaVM* vm, Local<JSValueRef> showAtAnchorArg, ArkUIBindTipsOptionsArrow& options)
{
    options.showAtAnchor = static_cast<int32_t>(TipsAnchorType::TARGET);
    if (showAtAnchorArg->IsNumber()) {
        int32_t temp = static_cast<int32_t>(showAtAnchorArg->ToNumber(vm)->Value());
        if (temp <= static_cast<int32_t>(TipsAnchorType::CURSOR) &&
            temp >= static_cast<int32_t>(TipsAnchorType::TARGET)) {
            options.showAtAnchor = temp;
            options.enableArrow = temp == static_cast<int32_t>(TipsAnchorType::CURSOR) ? false : options.enableArrow;
        }
    }
}

void ResetCalcDimensions(std::vector<std::optional<CalcDimension>>& optDimensions)
{
    for (uint32_t index = 0; index < optDimensions.size(); index++) {
        auto optDimension = optDimensions[index];
        optDimension.reset();
    }
}

void PushDimensionsToVector(std::vector<ArkUIStringAndFloat>& results,
    const std::vector<std::optional<CalcDimension>>& optDimensions)
{
    for (uint32_t index = 0; index < optDimensions.size(); index++) {
        auto optDimension = optDimensions[index];
        auto hasValue = optDimension.has_value();
        DimensionUnit unit = DimensionUnit::PX;
        ArkUIStringAndFloat value = { 0.0, nullptr };
        if (hasValue) {
            unit = optDimension.value().Unit();
            if (unit == DimensionUnit::CALC) {
                value.valueStr = optDimension.value().CalcValue().c_str();
            } else {
                value.value = optDimension.value().Value();
            }
        }
        results.push_back(ArkUIStringAndFloat { static_cast<ArkUI_Float32>(hasValue), nullptr });
        results.push_back(value);
        results.push_back(ArkUIStringAndFloat { static_cast<ArkUI_Float32>(unit), nullptr });
    }
}

void ParseBorderImageSlice(ArkUIRuntimeCallInfo* runtimeCallInfo, uint32_t& offset,
    std::vector<std::optional<CalcDimension>>& optDimensions, uint8_t& bitsets)
{
    if (ParseCalcDimensions(runtimeCallInfo, offset, NUM_4, optDimensions, CalcDimension(0.0))) {
        bitsets |= BorderImage::SLICE_BIT;
    }
    offset += NUM_4;
}

void ParseBorderImageWidth(ArkUIRuntimeCallInfo* runtimeCallInfo, uint32_t& offset,
    std::vector<std::optional<CalcDimension>>& optDimensions, uint8_t& bitsets)
{
    if (ParseCalcDimensions(runtimeCallInfo, offset, NUM_4, optDimensions, CalcDimension(0.0))) {
        bitsets |= BorderImage::WIDTH_BIT;
    }
    offset += NUM_4;
}

void ParseBorderImageOutset(ArkUIRuntimeCallInfo* runtimeCallInfo, uint32_t& offset,
    std::vector<std::optional<CalcDimension>>& optDimensions, uint8_t& bitsets)
{
    if (ParseCalcDimensions(runtimeCallInfo, offset, NUM_4, optDimensions, CalcDimension(0.0))) {
        bitsets |= BorderImage::OUTSET_BIT;
    }
    offset += NUM_4;
}

bool ParseBorderImageRepeat(ArkUIRuntimeCallInfo* runtimeCallInfo, uint32_t& offset,
    std::vector<ArkUIStringAndFloat>& options, uint8_t& bitsets)
{
    auto argsNumber = runtimeCallInfo->GetArgsNumber();
    if ((offset + NUM_1) > argsNumber) {
        return false;
    }
    auto vm = runtimeCallInfo->GetVM();
    auto repeatArg = runtimeCallInfo->GetCallArgRef(offset);
    auto repeatHasValue = repeatArg->IsString(vm);
    auto repeatValue = BorderImageRepeat::STRETCH;
    if (repeatHasValue) {
        auto repeatStr = repeatArg->ToString(vm)->ToString(vm);
        if (repeatStr == "Repeat") {
            repeatValue = BorderImageRepeat::REPEAT;
        } else if (repeatStr == "Round") {
            repeatValue = BorderImageRepeat::ROUND;
        } else if (repeatStr == "Space") {
            repeatValue = BorderImageRepeat::SPACE;
        } else {
            repeatValue = BorderImageRepeat::STRETCH;
        }
    }
    options.push_back(ArkUIStringAndFloat { static_cast<ArkUI_Float32>(repeatHasValue), nullptr });
    options.push_back(ArkUIStringAndFloat { static_cast<ArkUI_Float32>(repeatValue), nullptr });
    if (repeatHasValue) {
        bitsets |= BorderImage::REPEAT_BIT;
    }
    offset += NUM_1;
    return true;
}

bool ParseBorderImageFill(ArkUIRuntimeCallInfo* runtimeCallInfo, uint32_t& offset,
    std::vector<ArkUIStringAndFloat>& options)
{
    auto argsNumber = runtimeCallInfo->GetArgsNumber();
    if ((offset + NUM_1) > argsNumber) {
        return false;
    }
    auto fillArg = runtimeCallInfo->GetCallArgRef(offset);
    auto hasValue = fillArg->IsBoolean();
    auto fill = (hasValue) ? fillArg->BooleaValue(runtimeCallInfo->GetVM()) : false;
    options.push_back(ArkUIStringAndFloat {static_cast<ArkUI_Float32>(hasValue), nullptr });
    options.push_back(ArkUIStringAndFloat {static_cast<ArkUI_Float32>(fill), nullptr });
    offset += NUM_1;
    return true;
}

bool IsArgsUndefined(ArkUIRuntimeCallInfo* runtimeCallInfo, uint32_t offset, uint32_t count)
{
    auto argsNumber = runtimeCallInfo->GetArgsNumber();
    auto end = offset + count;
    end = (end > argsNumber) ? argsNumber : end;
    for (uint32_t index = offset; index < end; index++) {
        auto jsArg = runtimeCallInfo->GetCallArgRef(index);
        if (jsArg->IsUndefined()) {
            continue;
        }
        return false;
    }
    return true;
}

void ParseBorderImageLinearGradient(ArkUINodeHandle node,
    ArkUIRuntimeCallInfo* runtimeCallInfo, uint32_t offset,
    uint8_t& bitsets)
{
    auto argsNumber = runtimeCallInfo->GetArgsNumber();
    if ((offset + NUM_4) > argsNumber) {
        return;
    }
    auto angleArg = runtimeCallInfo->GetCallArgRef(offset);
    auto directionArg = runtimeCallInfo->GetCallArgRef(offset + NUM_1);
    auto colorsArg = runtimeCallInfo->GetCallArgRef(offset + NUM_2);
    auto repeatingArg = runtimeCallInfo->GetCallArgRef(offset + NUM_3);
    if (angleArg->IsUndefined() && directionArg->IsUndefined() &&
        colorsArg->IsUndefined() && repeatingArg->IsUndefined()) {
        return;
    }
    auto vm = runtimeCallInfo->GetVM();
    std::vector<ArkUIInt32orFloat32> options;
    ArkTSUtils::ParseGradientAngle(vm, angleArg, options);
    int32_t direction = static_cast<int32_t>(GradientDirection::NONE);
    ArkTSUtils::ParseJsInt32(vm, directionArg, direction);
    options.push_back({.i32 = static_cast<ArkUI_Int32>(direction)});

    std::vector<ArkUIInt32orFloat32> colors;
    ArkTSUtils::ParseGradientColorStops(vm, colorsArg, colors);
    auto repeating = repeatingArg->IsBoolean() ? repeatingArg->BooleaValue(runtimeCallInfo->GetVM()) : false;
    options.push_back({.i32 = static_cast<ArkUI_Int32>(repeating)});
    GetArkUINodeModifiers()->getCommonModifier()->setBorderImageGradient(node,
        options.data(), options.size(), colors.data(), colors.size());
}

bool ParseBorderImageSource(ArkUIRuntimeCallInfo* runtimeCallInfo, uint32_t& offset,
    ArkUINodeHandle node, std::string& src, uint8_t& bitsets)
{
    auto argsNumber = runtimeCallInfo->GetArgsNumber();
    if ((offset + NUM_5) > argsNumber) {
        return false;
    }
    if (IsArgsUndefined(runtimeCallInfo, offset, NUM_5)) {
        return false;
    }
    auto sourceArg = runtimeCallInfo->GetCallArgRef(offset); // use 1 args
    offset += NUM_1;
    auto vm = runtimeCallInfo->GetVM();
    if (sourceArg->IsString(vm)) {
        src = sourceArg->ToString(vm)->ToString(vm);
        bitsets |= BorderImage::SOURCE_BIT;
    } else {
        if (ArkTSUtils::ParseJsMedia(vm, sourceArg, src)) {
            bitsets |= BorderImage::SOURCE_BIT;
        } else {
            ParseBorderImageLinearGradient(node, runtimeCallInfo, offset, bitsets);
        }
    }
    offset += NUM_4; // skip 4 args
    return true;
}

RefPtr<NG::ChainedTransitionEffect> ParseChainedMoveTransition(
    const Framework::JSRef<Framework::JSVal>& effectOption, const JSExecutionContext& context)
{
    int32_t edge = 0;
    if (JSViewAbstract::ParseJsInt32(effectOption, edge)) {
        if (edge < static_cast<int32_t>(NG::TransitionEdge::TOP) ||
            edge > static_cast<int32_t>(NG::TransitionEdge::END)) {
            edge = static_cast<int32_t>(NG::TransitionEdge::START);
        }
        return AceType::MakeRefPtr<NG::ChainedMoveEffect>(static_cast<NG::TransitionEdge>(edge));
    }
    return nullptr;
}

RefPtr<NG::ChainedTransitionEffect> ParseChainedOpacityTransition(
    const Framework::JSRef<Framework::JSVal>& effectOption, const JSExecutionContext& context)
{
    double opacity = 1.0;
    if (Framework::JSViewAbstract::ParseJsDouble(effectOption, opacity)) {
        if ((LessNotEqual(opacity, 0.0)) || opacity > 1.0) {
            opacity = 1.0;
        }
        return AceType::MakeRefPtr<NG::ChainedOpacityEffect>(opacity);
    }
    return nullptr;
}

void ParseJsTranslate(const Framework::JSRef<Framework::JSVal>& jsValue, CalcDimension& translateX,
    CalcDimension& translateY, CalcDimension& translateZ)
{
    if (!jsValue->IsObject()) {
        return;
    }
    Framework::JSRef<Framework::JSObject> jsObj = Framework::JSRef<Framework::JSObject>::Cast(jsValue);
    Framework::JSViewAbstract::ParseJsDimensionVp(jsObj->GetProperty("x"), translateX);
    Framework::JSViewAbstract::ParseJsDimensionVp(jsObj->GetProperty("y"), translateY);
    Framework::JSViewAbstract::ParseJsDimensionVp(jsObj->GetProperty("z"), translateZ);
}

uint32_t ParseStrToUint(std::string safeAreaTypeStr)
{
    uint32_t uintType = NG::SAFE_AREA_TYPE_NONE;
    std::string delimiter = "|";
    std::string type;
    size_t pos = 0;
    while ((pos = safeAreaTypeStr.find(delimiter)) != std::string::npos) {
        type = safeAreaTypeStr.substr(0, pos);
        uintType |= (1 << StringUtils::StringToUint(type));
        safeAreaTypeStr.erase(0, pos + delimiter.length());
    }
    uintType |= (1 << StringUtils::StringToUint(safeAreaTypeStr));
    return uintType;
}

uint32_t ParseLayoutSafeAreaTypeStr(std::string safeAreaTypeStr)
{
    uint32_t uintType = NG::LAYOUT_SAFE_AREA_TYPE_NONE;
    std::string delimiter = "|";
    std::string type;
    size_t pos = 0;
    while ((pos = safeAreaTypeStr.find(delimiter)) != std::string::npos) {
        type = safeAreaTypeStr.substr(0, pos);
        uintType |= IgnoreLayoutSafeAreaOpts::TypeToMask(StringUtils::StringToUint(type));
        safeAreaTypeStr.erase(0, pos + delimiter.length());
    }
    if (safeAreaTypeStr != "") {
        uintType |= IgnoreLayoutSafeAreaOpts::TypeToMask(StringUtils::StringToUint(safeAreaTypeStr));
    }
    return uintType;
}

uint32_t ParseLayoutSafeAreaEdgesStr(std::string safeAreaEdgeStr)
{
    uint32_t uintType = NG::LAYOUT_SAFE_AREA_EDGE_NONE;
    std::string delimiter = "|";
    std::string type;
    size_t pos = 0;
    while ((pos = safeAreaEdgeStr.find(delimiter)) != std::string::npos) {
        type = safeAreaEdgeStr.substr(0, pos);
        uintType |= IgnoreLayoutSafeAreaOpts::EdgeToMask(StringUtils::StringToUint(type));
        safeAreaEdgeStr.erase(0, pos + delimiter.length());
    }
    if (safeAreaEdgeStr != "") {
        uintType |= IgnoreLayoutSafeAreaOpts::EdgeToMask(StringUtils::StringToUint(safeAreaEdgeStr));
    }
    return uintType;
}

RefPtr<NG::ChainedTransitionEffect> ParseChainedTranslateTransition(
    const Framework::JSRef<Framework::JSVal>& effectOption, const JSExecutionContext& context)
{
    if (effectOption->IsObject()) {
        // default: x, y, z (0.0, 0.0, 0.0)
        NG::TranslateOptions translate;
        ParseJsTranslate(effectOption, translate.x, translate.y, translate.z);
        return AceType::MakeRefPtr<NG::ChainedTranslateEffect>(translate);
    }
    return nullptr;
}

void GetDefaultRotateVector(double& dx, double& dy, double& dz)
{
    dx = 0.0;
    dy = 0.0;
    dz = 0.0;
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_NINE)) {
        dz = 1.0;
    }
}

void ParseJsRotate(
    const Framework::JSRef<Framework::JSVal>& jsValue, NG::RotateOptions& rotate, std::optional<float>& angle)
{
    if (!jsValue->IsObject()) {
        return;
    }
    // default: dx, dy, dz (0.0, 0.0, 0.0)
    double dxVal = 0.0;
    double dyVal = 0.0;
    double dzVal = 0.0;
    Framework::JSRef<Framework::JSObject> jsObj = Framework::JSRef<Framework::JSObject>::Cast(jsValue);
    if (!jsObj->HasProperty("x") && !jsObj->HasProperty("y") && !jsObj->HasProperty("z")) {
        GetDefaultRotateVector(dxVal, dyVal, dzVal);
    } else {
        Framework::JSViewAbstract::ParseJsDouble(jsObj->GetProperty("x"), dxVal);
        Framework::JSViewAbstract::ParseJsDouble(jsObj->GetProperty("y"), dyVal);
        Framework::JSViewAbstract::ParseJsDouble(jsObj->GetProperty("z"), dzVal);
    }
    rotate.xDirection = static_cast<float>(dxVal);
    rotate.yDirection = static_cast<float>(dyVal);
    rotate.zDirection = static_cast<float>(dzVal);
    // if specify centerX
    if (!Framework::JSViewAbstract::ParseJsDimensionVp(jsObj->GetProperty("centerX"), rotate.centerX)) {
        rotate.centerX = Dimension(0.5f, DimensionUnit::PERCENT);
    }
    // if specify centerY
    if (!Framework::JSViewAbstract::ParseJsDimensionVp(jsObj->GetProperty("centerY"), rotate.centerY)) {
        rotate.centerY = Dimension(0.5f, DimensionUnit::PERCENT);
    }
    // if specify centerZ
    if (!Framework::JSViewAbstract::ParseJsDimensionVp(jsObj->GetProperty("centerZ"), rotate.centerZ)) {
        rotate.centerZ = Dimension(0.5f, DimensionUnit::PERCENT);
    }
    // if specify angle
    Framework::JSViewAbstract::GetJsAngle(static_cast<int32_t>(ArkUIIndex::ANGLE), jsObj, angle);
    rotate.perspective = 0.0f;
    Framework::JSViewAbstract::GetJsPerspective(static_cast<int32_t>(ArkUIIndex::PERSPECTIVE), jsObj,
        rotate.perspective);
}

RefPtr<NG::ChainedTransitionEffect> ParseChainedRotateTransition(
    const Framework::JSRef<Framework::JSVal>& effectOption, const JSExecutionContext& context)
{
    RefPtr<NG::ChainedTransitionEffect> effect;
    if (effectOption->IsObject()) {
        NG::RotateOptions rotate(0.0f, 0.0f, 0.0f, 0.0f, 0.5_pct, 0.5_pct);
        std::optional<float> angle;
        ParseJsRotate(effectOption, rotate, angle);
        if (angle.has_value()) {
            rotate.angle = angle.value();
            return AceType::MakeRefPtr<NG::ChainedRotateEffect>(rotate);
        }
    }
    return nullptr;
}

void ParseJsScale(const Framework::JSRef<Framework::JSVal>& jsValue, float& scaleX, float& scaleY, float& scaleZ,
    CalcDimension& centerX, CalcDimension& centerY)
{
    double xVal = 1.0;
    double yVal = 1.0;
    double zVal = 1.0;
    if (!jsValue->IsObject()) {
        scaleX = static_cast<float>(xVal);
        scaleY = static_cast<float>(yVal);
        scaleZ = static_cast<float>(zVal);
        CalcDimension length;
        centerX = length;
        centerY = length;
        return;
    }
    Framework::JSRef<Framework::JSObject> jsObj = Framework::JSRef<Framework::JSObject>::Cast(jsValue);
    Framework::JSViewAbstract::ParseJsDouble(jsObj->GetProperty("x"), xVal);
    Framework::JSViewAbstract::ParseJsDouble(jsObj->GetProperty("y"), yVal);
    Framework::JSViewAbstract::ParseJsDouble(jsObj->GetProperty("z"), zVal);
    scaleX = static_cast<float>(xVal);
    scaleY = static_cast<float>(yVal);
    scaleZ = static_cast<float>(zVal);
    // if specify centerX
    Framework::JSViewAbstract::ParseJsDimensionVp(jsObj->GetProperty("centerX"), centerX);
    // if specify centerY
    Framework::JSViewAbstract::ParseJsDimensionVp(jsObj->GetProperty("centerY"), centerY);
}

RefPtr<NG::ChainedTransitionEffect> ParseChainedScaleTransition(
    const Framework::JSRef<Framework::JSVal>& effectOption, const JSExecutionContext& context)
{
    if (effectOption->IsObject()) {
        // default: x, y, z (1.0, 1.0, 1.0), centerX, centerY 50% 50%;
        NG::ScaleOptions scale(1.0f, 1.0f, 1.0f, 0.5_pct, 0.5_pct);
        ParseJsScale(effectOption, scale.xScale, scale.yScale, scale.zScale, scale.centerX, scale.centerY);
        return AceType::MakeRefPtr<NG::ChainedScaleEffect>(scale);
    }
    return nullptr;
}

RefPtr<NG::ChainedTransitionEffect> ParseChainedTransition(
    const JSRef<JSObject>& object, const JSExecutionContext& context);

RefPtr<NG::ChainedTransitionEffect> ParseChainedAsymmetricTransition(
    const Framework::JSRef<Framework::JSVal>& effectOption, const JSExecutionContext& context)
{
    if (effectOption->IsObject()) {
        auto effectObj = Framework::JSRef<Framework::JSObject>::Cast(effectOption);
        auto appearJsVal = effectObj->GetProperty("appear");
        auto disappearJsVal = effectObj->GetProperty("disappear");
        RefPtr<NG::ChainedTransitionEffect> appearEffect;
        RefPtr<NG::ChainedTransitionEffect> disappearEffect;
        if (appearJsVal->IsObject()) {
            auto appearObj = Framework::JSRef<Framework::JSObject>::Cast(appearJsVal);
            appearEffect = ParseChainedTransition(appearObj, context);
        }
        if (disappearJsVal->IsObject()) {
            auto disappearObj = Framework::JSRef<Framework::JSObject>::Cast(disappearJsVal);
            disappearEffect = ParseChainedTransition(disappearObj, context);
        }
        return AceType::MakeRefPtr<NG::ChainedAsymmetricEffect>(appearEffect, disappearEffect);
    }
    return nullptr;
}

int64_t GetFormAnimationTimeInterval(const RefPtr<PipelineBase>& pipelineContext)
{
    CHECK_NULL_RETURN(pipelineContext, 0);
    return (GetMicroTickCount() - pipelineContext->GetFormAnimationStartTime()) / MICROSEC_TO_MILLISEC;
}

using ChainedTransitionEffectCreator = RefPtr<NG::ChainedTransitionEffect> (*)(
    const Framework::JSRef<Framework::JSVal>&, const JSExecutionContext&);

void GetAnimationOptionResult(shared_ptr<AnimationOption>& animationOptionResult,
    const JSRef<JSObject>& propAnimationOption, const RefPtr<PipelineBase>& pipelineContext,
    const JSExecutionContext& context)
{
    // The maximum of the form-animation-playback duration value is 1000 ms.
    if (pipelineContext->IsFormRenderExceptDynamicComponent() && pipelineContext->IsFormAnimation()) {
        auto formAnimationTimeInterval = GetFormAnimationTimeInterval(pipelineContext);
        // If the duration exceeds 1000ms, init it to 0 ms.
        if (formAnimationTimeInterval > DEFAULT_DURATION) {
            animationOptionResult->SetDuration(0);
        } else if (animationOptionResult->GetDuration() > (DEFAULT_DURATION - formAnimationTimeInterval)) {
            // If remaining time is less than 1000ms, check for update duration.
            animationOptionResult->SetDuration(DEFAULT_DURATION - formAnimationTimeInterval);
            TAG_LOGI(AceLogTag::ACE_FORM, "[Form animation]  Form Transition SetDuration: %{public}lld ms",
                static_cast<long long>(DEFAULT_DURATION - formAnimationTimeInterval));
        }
    }
    auto animationOptionObj = Framework::JSRef<Framework::JSObject>::Cast(propAnimationOption);
    Framework::JSRef<Framework::JSVal> onFinish = animationOptionObj->GetProperty("onFinish");
    if (onFinish->IsFunction()) {
        RefPtr<JsFunction> jsFunc =
            AceType::MakeRefPtr<JsFunction>(Framework::JSRef<Framework::JSObject>(), JSRef<JSFunc>::Cast(onFinish));
        std::function<void()> onFinishEvent = [execCtx = context, func = std::move(jsFunc),
                                                  id = Container::CurrentId()]() {
            ContainerScope scope(id);
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            func->Execute();
        };
        animationOptionResult->SetOnFinishEvent(onFinishEvent);
    }
}

RefPtr<NG::ChainedTransitionEffect> ParseChainedTransition(
    const Framework::JSRef<Framework::JSObject>& object, const JSExecutionContext& context)
{
    auto propType = object->GetProperty("type_");
    if (!propType->IsString()) {
        return nullptr;
    }
    std::string type = propType->ToString();
    auto propEffectOption = object->GetProperty("effect_");
    auto propAnimationOption = object->GetProperty("animation_");
    auto propSuccessor = object->GetProperty("successor_");
    static const LinearMapNode<ChainedTransitionEffectCreator> creatorMap[] = {
        { "asymmetric", ParseChainedAsymmetricTransition },
        { "identity",
            [](const Framework::JSRef<Framework::JSVal>& effectOption, const JSExecutionContext& context)
                -> RefPtr<NG::ChainedTransitionEffect> { return AceType::MakeRefPtr<NG::ChainedIdentityEffect>(); } },
        { "move", ParseChainedMoveTransition },
        { "opacity", ParseChainedOpacityTransition },
        { "rotate", ParseChainedRotateTransition },
        { "scale", ParseChainedScaleTransition },
        { "slideSwitch",
            [](const Framework::JSRef<Framework::JSVal>& effectOption,
                const JSExecutionContext& context) -> RefPtr<NG::ChainedTransitionEffect> {
                return AceType::MakeRefPtr<NG::ChainedSlideSwitchEffect>();
            } },
        { "translate", ParseChainedTranslateTransition },
    };
    int64_t index = BinarySearchFindIndex(creatorMap, ArraySize(creatorMap), type.c_str());
    if (index < 0) {
        return nullptr;
    }
    RefPtr<NG::ChainedTransitionEffect> result = creatorMap[index].value(propEffectOption, context);
    if (!result) {
        return nullptr;
    }
    if (propAnimationOption->IsObject()) {
        auto container = Container::Current();
        CHECK_NULL_RETURN(container, nullptr);
        auto pipelineContext = container->GetPipelineContext();
        CHECK_NULL_RETURN(pipelineContext, nullptr);
        auto animationOptionResult = std::make_shared<AnimationOption>(
            JSViewContext::CreateAnimation(propAnimationOption, pipelineContext->IsFormRenderExceptDynamicComponent()));
        GetAnimationOptionResult(animationOptionResult, propAnimationOption, pipelineContext, context);
        result->SetAnimationOption(animationOptionResult);
    }
    if (propSuccessor->IsObject()) {
        result->SetNext(ParseChainedTransition(Framework::JSRef<Framework::JSObject>::Cast(propSuccessor), context));
    }
    return result;
}

NG::TransitionOptions ParseJsTransition(const Framework::JSRef<Framework::JSVal>& transitionArgs)
{
    NG::TransitionOptions transitionOption;
    if (!transitionArgs->IsObject()) {
        return transitionOption;
    }
    Framework::JSRef<Framework::JSObject> jsObj = Framework::JSRef<Framework::JSObject>::Cast(transitionArgs);
    bool hasEffect = false;
    transitionOption.Type = ParseTransitionType(jsObj->GetPropertyValue<std::string>("type", "All"));
    if (jsObj->HasProperty("opacity")) {
        double opacity = 1.0;
        Framework::JSViewAbstract::ParseJsDouble(jsObj->GetProperty("opacity"), opacity);
        opacity = std::clamp(opacity, 0.0, 1.0);
        transitionOption.UpdateOpacity(static_cast<float>(opacity));
        hasEffect = true;
    }
    if (jsObj->HasProperty("translate")) {
        // default: x, y, z (0.0, 0.0, 0.0)
        NG::TranslateOptions translate;
        ParseJsTranslate(jsObj->GetProperty("translate"), translate.x, translate.y, translate.z);
        transitionOption.UpdateTranslate(translate);
        hasEffect = true;
    }
    if (jsObj->HasProperty("scale")) {
        // default: x, y, z (1.0, 1.0, 1.0), centerX, centerY 50% 50%;
        NG::ScaleOptions scale(1.0f, 1.0f, 1.0f, 0.5_pct, 0.5_pct);
        ParseJsScale(
            jsObj->GetProperty("scale"), scale.xScale, scale.yScale, scale.zScale, scale.centerX, scale.centerY);
        transitionOption.UpdateScale(scale);
        hasEffect = true;
    }
    if (jsObj->HasProperty("rotate")) {
        // default: dx, dy, dz (0.0, 0.0, 0.0), angle 0, centerX, centerY 50% 50%;
        NG::RotateOptions rotate(0.0f, 0.0f, 0.0f, 0.0f, 0.5_pct, 0.5_pct);
        std::optional<float> angle;
        ParseJsRotate(jsObj->GetProperty("rotate"), rotate, angle);
        if (angle.has_value()) {
            rotate.angle = angle.value();
            transitionOption.UpdateRotate(rotate);
            hasEffect = true;
        }
    }
    if (!hasEffect) {
        // default transition
        transitionOption = NG::TransitionOptions::GetDefaultTransition(transitionOption.Type);
    }
    return transitionOption;
}

bool ParseMotionPath(const Framework::JSRef<Framework::JSVal>& jsValue, MotionPathOption& option)
{
    if (!jsValue->IsObject()) {
        return false;
    }

    Framework::JSRef<Framework::JSObject> jsObj = Framework::JSRef<Framework::JSObject>::Cast(jsValue);
    auto path = jsObj->GetPropertyValue<std::string>("path", "");
    if (path.empty()) {
        return false;
    }
    option.SetPath(path);
    double from = 0.0;
    double to = 1.0;
    Framework::JSViewAbstract::ParseJsDouble(jsObj->GetProperty("from"), from);
    Framework::JSViewAbstract::ParseJsDouble(jsObj->GetProperty("to"), to);
    if (GreatNotEqual(from, 1.0) || LessNotEqual(from, 0.0)) {
        from = 0.0;
    }
    if (GreatNotEqual(to, 1.0) || LessNotEqual(to, 0.0)) {
        to = 1.0;
    } else if (to < from) {
        to = from;
    }
    option.SetBegin(static_cast<float>(from));
    option.SetEnd(static_cast<float>(to));
    option.SetRotate(jsObj->GetPropertyValue<bool>("rotatable", false));
    return true;
}

bool ParseJsDoublePair(const EcmaVM *vm, const Local<JSValueRef> &value, ArkUI_Float32 &first, ArkUI_Float32 &second)
{
    if (!value->IsArray(vm)) {
        return false;
    }
    auto array = panda::Local<panda::ArrayRef>(value);
    if (array->Length(vm) != NUM_2) {
        return false;
    }
    auto firstArg = panda::ArrayRef::GetValueAt(vm, array, NUM_0);
    if (!firstArg->IsNumber()) {
        return false;
    }
    auto secondArg = panda::ArrayRef::GetValueAt(vm, array, NUM_1);
    if (!secondArg->IsNumber()) {
        return false;
    }
    first = static_cast<ArkUI_Float32>(firstArg->ToNumber(vm)->Value());
    second = static_cast<ArkUI_Float32>(secondArg->ToNumber(vm)->Value());
    return true;
}

void PushOuterBorderDimensionVector(const std::optional<CalcDimension>& valueDim, std::vector<ArkUI_Float32> &options)
{
    options.push_back(static_cast<ArkUI_Float32>(valueDim.has_value()));
    if (valueDim.has_value()) {
        options.push_back(static_cast<ArkUI_Float32>(valueDim.value().Value()));
        options.push_back(static_cast<ArkUI_Float32>(valueDim.value().Unit()));
    } else {
        options.push_back(0);
        options.push_back(0);
    }
}

void PushOuterBorderColorVector(const std::optional<Color>& valueColor, std::vector<uint32_t> &options)
{
    options.push_back(static_cast<uint32_t>(valueColor.has_value()));
    if (valueColor.has_value()) {
        options.push_back(static_cast<uint32_t>(valueColor.value().GetValue()));
    } else {
        options.push_back(0);
    }
}

void ParseOuterBorderEdgeColor(EcmaVM* vm, Local<JSValueRef>& arg, std::optional<Color>& optColor,
    std::vector<RefPtr<ResourceObject>>& resObjs, const NodeInfo& nodeInfo)
{
    Color color;
    auto result = ArkTSUtils::ParseJsColorAlpha(vm, arg, color, resObjs, nodeInfo);
    if (!arg->IsUndefined() && result) {
        optColor = color;
    }
}

void ParseOuterBorderColor(ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm, std::vector<uint32_t>& values,
    int32_t argsIndex, std::vector<RefPtr<ResourceObject>>& resObjs, const NodeInfo& nodeInfo,
    bool needLocalized = false)
{
    Local<JSValueRef> leftArg = runtimeCallInfo->GetCallArgRef(argsIndex);
    Local<JSValueRef> rightArg = runtimeCallInfo->GetCallArgRef(argsIndex + NUM_1);
    Local<JSValueRef> topArg = runtimeCallInfo->GetCallArgRef(argsIndex + NUM_2);
    Local<JSValueRef> bottomArg = runtimeCallInfo->GetCallArgRef(argsIndex + NUM_3);

    std::optional<Color> leftColor;
    std::optional<Color> rightColor;
    std::optional<Color> topColor;
    std::optional<Color> bottomColor;
    std::optional<Color> startColor;
    std::optional<Color> endColor;

    ParseOuterBorderEdgeColor(vm, leftArg, leftColor, resObjs, nodeInfo);
    ParseOuterBorderEdgeColor(vm, rightArg, rightColor, resObjs, nodeInfo);
    ParseOuterBorderEdgeColor(vm, topArg, topColor, resObjs, nodeInfo);
    ParseOuterBorderEdgeColor(vm, bottomArg, bottomColor, resObjs, nodeInfo);
    if (needLocalized) {
        Local<JSValueRef> startArgs = runtimeCallInfo->GetCallArgRef(27); // 27: index of BorderColor.startColor
        Local<JSValueRef> endArgs = runtimeCallInfo->GetCallArgRef(28);   // 28: index of BorderColor.endColor
        ParseOuterBorderEdgeColor(vm, startArgs, startColor, resObjs, nodeInfo);
        ParseOuterBorderEdgeColor(vm, endArgs, endColor, resObjs, nodeInfo);
    }
    if (startColor.has_value() || endColor.has_value()) {
        PushOuterBorderColorVector(startColor, values);
        PushOuterBorderColorVector(endColor, values);
        if (SystemProperties::ConfigChangePerform()) {
            if (resObjs[NUM_12]) {
                std::swap(resObjs[NUM_8], resObjs[NUM_12]);
            }
            if (resObjs[NUM_13]) {
                std::swap(resObjs[NUM_9], resObjs[NUM_13]);
            }
        }
    } else {
        PushOuterBorderColorVector(leftColor, values);
        PushOuterBorderColorVector(rightColor, values);
    }
    PushOuterBorderColorVector(topColor, values);
    PushOuterBorderColorVector(bottomColor, values);
}

void ParseOutLineColor(ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm, std::vector<uint32_t>& values,
    int32_t argsIndex, std::vector<RefPtr<ResourceObject>>& resObjs, const NodeInfo& nodeInfo)
{
    Local<JSValueRef> leftArg = runtimeCallInfo->GetCallArgRef(argsIndex);
    Local<JSValueRef> rightArg = runtimeCallInfo->GetCallArgRef(argsIndex + NUM_1);
    Local<JSValueRef> topArg = runtimeCallInfo->GetCallArgRef(argsIndex + NUM_2);
    Local<JSValueRef> bottomArg = runtimeCallInfo->GetCallArgRef(argsIndex + NUM_3);

    std::optional<Color> leftColor;
    std::optional<Color> rightColor;
    std::optional<Color> topColor;
    std::optional<Color> bottomColor;

    ParseOuterBorderEdgeColor(vm, leftArg, leftColor, resObjs, nodeInfo);
    ParseOuterBorderEdgeColor(vm, rightArg, rightColor, resObjs, nodeInfo);
    ParseOuterBorderEdgeColor(vm, topArg, topColor, resObjs, nodeInfo);
    ParseOuterBorderEdgeColor(vm, bottomArg, bottomColor, resObjs, nodeInfo);
    
    PushOuterBorderColorVector(topColor, values);
    PushOuterBorderColorVector(rightColor, values);
    PushOuterBorderColorVector(bottomColor, values);
    PushOuterBorderColorVector(leftColor, values);
}

bool ParseLocalizedBorderRadius(const EcmaVM* vm, const Local<JSValueRef>& value, CalcDimension& result)
{
    if (ArkTSUtils::ParseJsLengthMetrics(vm, value, result)) {
        if (result.IsNegative()) {
            result.Reset();
        }
        return true;
    }
    return false;
}

void ParseOuterBorder(EcmaVM* vm, const Local<JSValueRef>& args, std::optional<CalcDimension>& optionalDimension,
    std::vector<RefPtr<ResourceObject>>& resObjs)
{
    RefPtr<ResourceObject> resObj;
    ArkTSUtils::ParseOuterBorder(vm, args, optionalDimension, resObj);
    if (SystemProperties::ConfigChangePerform()) {
        resObjs.push_back(resObj);
    }
}

void ParseNullptrResObj(std::vector<RefPtr<ResourceObject>>& resObjs, int32_t index)
{
    if (SystemProperties::ConfigChangePerform()) {
        for (int32_t i = 0; i < index; i++) {
            resObjs.push_back(nullptr);
        }
    }
}

void ParseOuterBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm, std::vector<ArkUI_Float32>& values,
    int32_t argsIndex, std::vector<RefPtr<ResourceObject>>& resObjs, bool needLocalized = false)
{
    Local<JSValueRef> topLeftArgs = runtimeCallInfo->GetCallArgRef(argsIndex);
    Local<JSValueRef> topRightArgs = runtimeCallInfo->GetCallArgRef(argsIndex + NUM_1);
    Local<JSValueRef> bottomLeftArgs = runtimeCallInfo->GetCallArgRef(argsIndex + NUM_2);
    Local<JSValueRef> bottomRightArgs = runtimeCallInfo->GetCallArgRef(argsIndex + NUM_3);
    if (needLocalized) {
        Local<JSValueRef> topStartArgs = runtimeCallInfo->GetCallArgRef(29);    // 29: index of BorderRadius.topStart
        Local<JSValueRef> topEndArgs = runtimeCallInfo->GetCallArgRef(30);      // 30: index of BorderRadius.topEnd
        Local<JSValueRef> bottomStartArgs = runtimeCallInfo->GetCallArgRef(31); // 31: index of BorderRadius.bottomStart
        Local<JSValueRef> bottomEndArgs = runtimeCallInfo->GetCallArgRef(32);   // 32: index of BorderRadius.bottomEnd
        // 35: index of is LocalizedBorderRadius or not
        Local<JSValueRef> isLocalizedBorderRadiusArg = runtimeCallInfo->GetCallArgRef(35);
        bool isLocalizedBorderRadius =
            (isLocalizedBorderRadiusArg->IsBoolean()) ? isLocalizedBorderRadiusArg->ToBoolean(vm)->Value() : false;
        if (isLocalizedBorderRadius) {
            CalcDimension topStartOptional;
            CalcDimension topEndOptional;
            CalcDimension bottomStartOptional;
            CalcDimension bottomEndOptional;
            ParseLocalizedBorderRadius(vm, topStartArgs, topStartOptional);
            ParseLocalizedBorderRadius(vm, topEndArgs, topEndOptional);
            ParseLocalizedBorderRadius(vm, bottomStartArgs, bottomStartOptional);
            ParseLocalizedBorderRadius(vm, bottomEndArgs, bottomEndOptional);
            PushOuterBorderDimensionVector(topStartOptional, values);
            PushOuterBorderDimensionVector(topEndOptional, values);
            PushOuterBorderDimensionVector(bottomStartOptional, values);
            PushOuterBorderDimensionVector(bottomEndOptional, values);
            ParseNullptrResObj(resObjs, NUM_4);
            return;
        }
    }

    std::optional<CalcDimension> topLeftOptional;
    std::optional<CalcDimension> topRightOptional;
    std::optional<CalcDimension> bottomLeftOptional;
    std::optional<CalcDimension> bottomRightOptional;

    ParseOuterBorder(vm, topLeftArgs, topLeftOptional, resObjs);
    ParseOuterBorder(vm, topRightArgs, topRightOptional, resObjs);
    ParseOuterBorder(vm, bottomLeftArgs, bottomLeftOptional, resObjs);
    ParseOuterBorder(vm, bottomRightArgs, bottomRightOptional, resObjs);

    PushOuterBorderDimensionVector(topLeftOptional, values);
    PushOuterBorderDimensionVector(topRightOptional, values);
    PushOuterBorderDimensionVector(bottomLeftOptional, values);
    PushOuterBorderDimensionVector(bottomRightOptional, values);
}

void PushOuterBorderStyleVector(const std::optional<BorderStyle>& value, std::vector<uint32_t> &options)
{
    options.push_back(static_cast<uint32_t>(value.has_value()));
    if (value.has_value()) {
        options.push_back(static_cast<uint32_t>(value.value()));
    } else {
        options.push_back(0);
    }
}

void ParseOuterBorderStyle(
    ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm, std::vector<uint32_t>& values, int32_t argsIndex)
{
    std::optional<BorderStyle> styleLeft;
    std::optional<BorderStyle> styleRight;
    std::optional<BorderStyle> styleTop;
    std::optional<BorderStyle> styleBottom;

    auto topArg = runtimeCallInfo->GetCallArgRef(argsIndex);
    auto rightArg = runtimeCallInfo->GetCallArgRef(argsIndex + NUM_1);
    auto bottomArg = runtimeCallInfo->GetCallArgRef(argsIndex + NUM_2);
    auto leftArg = runtimeCallInfo->GetCallArgRef(argsIndex + NUM_3);

    if (!topArg->IsUndefined() && topArg->IsNumber()) {
        styleTop = ConvertBorderStyle(topArg->Int32Value(vm));
    }
    if (!rightArg->IsUndefined() && rightArg->IsNumber()) {
        styleRight = ConvertBorderStyle(rightArg->Int32Value(vm));
    }
    if (!bottomArg->IsUndefined() && bottomArg->IsNumber()) {
        styleBottom = ConvertBorderStyle(bottomArg->Int32Value(vm));
    }
    if (!leftArg->IsUndefined() && leftArg->IsNumber()) {
        styleLeft = ConvertBorderStyle(leftArg->Int32Value(vm));
    }

    PushOuterBorderStyleVector(styleLeft, values);
    PushOuterBorderStyleVector(styleRight, values);
    PushOuterBorderStyleVector(styleTop, values);
    PushOuterBorderStyleVector(styleBottom, values);
}

void ParseOuterBorderForDashParams(EcmaVM* vm, const Local<JSValueRef>& args,
    std::optional<CalcDimension>& optionalDimension, std::vector<RefPtr<ResourceObject>>& resObjs)
{
    RefPtr<ResourceObject> resObj;
    ArkTSUtils::ParseOuterBorderForDashParams(vm, args, optionalDimension, resObj);
    if (SystemProperties::ConfigChangePerform()) {
        resObjs.push_back(resObj);
    }
}

void ParseOuterBorderDashParam(ArkUIRuntimeCallInfo *runtimeCallInfo, EcmaVM *vm, std::vector<ArkUI_Float32> &values,
    int32_t argsIndex, std::vector<RefPtr<ResourceObject>>& resObjs)
{
    Local<JSValueRef> leftArgs = runtimeCallInfo->GetCallArgRef(argsIndex);
    Local<JSValueRef> rightArgs = runtimeCallInfo->GetCallArgRef(argsIndex + NUM_1);
    Local<JSValueRef> topArgs = runtimeCallInfo->GetCallArgRef(argsIndex + NUM_2);
    Local<JSValueRef> bottomArgs = runtimeCallInfo->GetCallArgRef(argsIndex + NUM_3);
    std::optional<CalcDimension> leftDim;
    std::optional<CalcDimension> rightDim;
    std::optional<CalcDimension> topDim;
    std::optional<CalcDimension> bottomDim;

    ParseOuterBorderForDashParams(vm, leftArgs, leftDim, resObjs);
    ParseOuterBorderForDashParams(vm, rightArgs, rightDim, resObjs);
    ParseOuterBorderForDashParams(vm, topArgs, topDim, resObjs);
    ParseOuterBorderForDashParams(vm, bottomArgs, bottomDim, resObjs);

    PushOuterBorderDimensionVector(leftDim, values);
    PushOuterBorderDimensionVector(rightDim, values);
    PushOuterBorderDimensionVector(topDim, values);
    PushOuterBorderDimensionVector(bottomDim, values);
}

void SetBackgroundImagePositionAlign(double &value, DimensionUnit &type, double valueContent,
    const DimensionUnit &typeContent)
{
    value = valueContent;
    type = typeContent;
}

void ParseBackgroundImagePositionAlign(const int32_t align, double &valueX, double &valueY, DimensionUnit &typeX,
    DimensionUnit &typeY)
{
    switch (align) {
        case NUM_0:
            SetBackgroundImagePositionAlign(valueX, typeX, 0.0, DimensionUnit::PERCENT);
            SetBackgroundImagePositionAlign(valueY, typeY, 0.0, DimensionUnit::PERCENT);
            break;
        case NUM_1:
            SetBackgroundImagePositionAlign(valueX, typeX, HALF_DIMENSION, DimensionUnit::PERCENT);
            SetBackgroundImagePositionAlign(valueY, typeY, 0.0, DimensionUnit::PERCENT);
            break;
        case NUM_2:
            SetBackgroundImagePositionAlign(valueX, typeX, FULL_DIMENSION, DimensionUnit::PERCENT);
            SetBackgroundImagePositionAlign(valueY, typeY, 0.0, DimensionUnit::PERCENT);
            break;
        case NUM_3:
            SetBackgroundImagePositionAlign(valueX, typeX, 0.0, DimensionUnit::PERCENT);
            SetBackgroundImagePositionAlign(valueY, typeY, HALF_DIMENSION, DimensionUnit::PERCENT);
            break;
        case NUM_4:
            SetBackgroundImagePositionAlign(valueX, typeX, HALF_DIMENSION, DimensionUnit::PERCENT);
            SetBackgroundImagePositionAlign(valueY, typeY, HALF_DIMENSION, DimensionUnit::PERCENT);
            break;
        case NUM_5:
            SetBackgroundImagePositionAlign(valueX, typeX, FULL_DIMENSION, DimensionUnit::PERCENT);
            SetBackgroundImagePositionAlign(valueY, typeY, HALF_DIMENSION, DimensionUnit::PERCENT);
            break;
        case NUM_6:
            SetBackgroundImagePositionAlign(valueX, typeX, 0.0, DimensionUnit::PERCENT);
            SetBackgroundImagePositionAlign(valueY, typeY, FULL_DIMENSION, DimensionUnit::PERCENT);
            break;
        case NUM_7:
            SetBackgroundImagePositionAlign(valueX, typeX, HALF_DIMENSION, DimensionUnit::PERCENT);
            SetBackgroundImagePositionAlign(valueY, typeY, FULL_DIMENSION, DimensionUnit::PERCENT);
            break;
        case NUM_8:
            SetBackgroundImagePositionAlign(valueX, typeX, FULL_DIMENSION, DimensionUnit::PERCENT);
            SetBackgroundImagePositionAlign(valueY, typeY, FULL_DIMENSION, DimensionUnit::PERCENT);
            break;
        default:
            break;
    }
}

bool ParseAxisDimensionVp(const EcmaVM *vm, const Local<JSValueRef> &jsValue, CalcDimension &result,
    bool checkIllegal = false)
{
    if (jsValue->IsNumber()) {
        result = Dimension(jsValue->ToNumber(vm)->Value(), DimensionUnit::VP);
        return true;
    }
    if (jsValue->IsString(vm)) {
        if (checkIllegal) {
            return StringUtils::StringToDimensionWithUnitNG(jsValue->ToString(vm)->ToString(vm), result,
                DimensionUnit::VP);
        }
        result = StringUtils::StringToCalcDimension(jsValue->ToString(vm)->ToString(vm), false, DimensionUnit::VP);
        return true;
    }
    return false;
}

void ParseDirection(EcmaVM *vm, const Local<JSValueRef> &directionArg, float &value)
{
    if (directionArg->IsNumber()) {
        value = directionArg->ToNumber(vm)->Value();
    }
}

void GetJsAngle(const EcmaVM* vm, const Local<JSValueRef>& angleArg, std::optional<float>& angle)
{
    if (angleArg->IsString(vm)) {
        angle = static_cast<float>(StringUtils::StringToDegree(angleArg->ToString(vm)->ToString(vm)));
    } else if (angleArg->IsNumber()) {
        angle = static_cast<float>(angleArg->ToNumber(vm)->Value());
    } else {
        LOGE("Invalid value type");
    }
}

void GetJsAngleWithDefault(
    const EcmaVM* vm, const Local<JSValueRef>& angleArg, std::optional<float>& angle, float defaultValue)
{
    if (angleArg->IsString(vm)) {
        double temp = 0.0;
        if (StringUtils::StringToDegree(angleArg->ToString(vm)->ToString(vm), temp)) {
            angle = static_cast<float>(temp);
        } else {
            angle = defaultValue;
        }
    } else if (angleArg->IsNumber()) {
        angle = static_cast<float>(angleArg->ToNumber(vm)->Value());
    }
}

void ParseCenterDimension(const EcmaVM* vm, const Local<JSValueRef>& centerArg, CalcDimension& centerDimension)
{
    if (!ArkTSUtils::ParseJsDimensionVp(vm, centerArg, centerDimension, false)) {
        centerDimension = Dimension(0.5f, DimensionUnit::PERCENT);
    }
}

void ParseCenterZDimension(const EcmaVM* vm, const Local<JSValueRef>& centerArg, CalcDimension& centerDimension)
{
    if (!ArkTSUtils::ParseJsDimensionVp(vm, centerArg, centerDimension, false)) {
        centerDimension = Dimension(0.0f, DimensionUnit::VP);
    }
}

bool ParseRotateAngle(ArkUIRuntimeCallInfo *runtimeCallInfo, ArkUI_Float32 values[], int units[],
    int valuesLength, int unitsLength)
{
    if (valuesLength != SIZE_OF_SEVEN || unitsLength != SIZE_OF_THREE) {
        return false;
    }
    EcmaVM *vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> angleXArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> angleYArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> angleZArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> centerXArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> centerYArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    Local<JSValueRef> centerZArg = runtimeCallInfo->GetCallArgRef(NUM_6);
    Local<JSValueRef> perspectiveArg = runtimeCallInfo->GetCallArgRef(NUM_7);
    float angleX = 0.0f;
    float angleY = 0.0f;
    float angleZ = 0.0f;
    std::optional<float> angleXOptional;
    std::optional<float> angleYOptional;
    std::optional<float> angleZOptional;
    CalcDimension centerX = 0.5_pct;
    CalcDimension centerY = 0.5_pct;
    CalcDimension centerZ = CalcDimension(0.0f, DimensionUnit::VP);
    GetJsAngleWithDefault(vm, angleXArg, angleXOptional, 0.0f);
    GetJsAngleWithDefault(vm, angleYArg, angleYOptional, 0.0f);
    GetJsAngleWithDefault(vm, angleZArg, angleZOptional, 0.0f);

    double perspective = 0.0;

    angleX = angleXOptional.value_or(0.0f);
    angleY = angleYOptional.value_or(0.0f);
    angleZ = angleZOptional.value_or(0.0f);
    ParseCenterDimension(vm, centerXArg, centerX);
    ParseCenterDimension(vm, centerYArg, centerY);
    ParseCenterZDimension(vm, centerZArg, centerZ);
    ArkTSUtils::ParseJsDouble(vm, perspectiveArg, perspective);
    values[NUM_0] = static_cast<ArkUI_Float32>(centerX.Value());
    units[NUM_0] = static_cast<int>(centerX.Unit());
    values[NUM_1] = static_cast<ArkUI_Float32>(centerY.Value());
    units[NUM_1] = static_cast<int>(centerY.Unit());
    values[NUM_2] = static_cast<ArkUI_Float32>(centerZ.Value());
    units[NUM_2] = static_cast<int>(centerZ.Unit());
    values[NUM_3] = static_cast<ArkUI_Float32>(angleX);
    values[NUM_4] = static_cast<ArkUI_Float32>(angleY);
    values[NUM_5] = static_cast<ArkUI_Float32>(angleZ);
    values[NUM_6] = static_cast<ArkUI_Float32>(perspective);
    return true;
}

bool ParseRotate(ArkUIRuntimeCallInfo *runtimeCallInfo, ArkUI_Float32 values[], int units[],
    int valuesLength, int unitsLength)
{
    if (valuesLength != SIZE_OF_EIGHT || unitsLength != SIZE_OF_THREE) {
        return false;
    }
    EcmaVM *vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> xDirectionArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> yDirectionArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> zDirectionArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> angleArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> centerXArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    Local<JSValueRef> centerYArg = runtimeCallInfo->GetCallArgRef(NUM_6);
    Local<JSValueRef> centerZArg = runtimeCallInfo->GetCallArgRef(NUM_7);
    Local<JSValueRef> perspectiveArg = runtimeCallInfo->GetCallArgRef(NUM_8);
    float xDirection = 0.0f;
    float yDirection = 0.0f;
    float zDirection = 0.0f;
    float angle = 0.0f;
    std::optional<float> angleOptional;
    CalcDimension centerX = 0.5_pct;
    CalcDimension centerY = 0.5_pct;
    CalcDimension centerZ = CalcDimension(0.0f, DimensionUnit::VP);
    GetJsAngle(vm, angleArg, angleOptional);
    if (!angleOptional) {
        return false;
    }
    angle = angleOptional.value();
    double perspective = 0.0;
    if (!xDirectionArg->IsNumber() && !yDirectionArg->IsNumber() && !zDirectionArg->IsNumber()) {
        zDirection = 1.0f;
    }
    ParseDirection(vm, xDirectionArg, xDirection);
    ParseDirection(vm, yDirectionArg, yDirection);
    ParseDirection(vm, zDirectionArg, zDirection);
    ParseCenterDimension(vm, centerXArg, centerX);
    ParseCenterDimension(vm, centerYArg, centerY);
    ParseCenterDimension(vm, centerZArg, centerZ);
    ArkTSUtils::ParseJsDouble(vm, perspectiveArg, perspective);
    values[NUM_0] = static_cast<ArkUI_Float32>(centerX.Value());
    units[NUM_0] = static_cast<int>(centerX.Unit());
    values[NUM_1] = static_cast<ArkUI_Float32>(centerY.Value());
    units[NUM_1] = static_cast<int>(centerY.Unit());
    values[NUM_2] = static_cast<ArkUI_Float32>(centerZ.Value());
    units[NUM_2] = static_cast<int>(centerZ.Unit());
    values[NUM_3] = static_cast<ArkUI_Float32>(xDirection);
    values[NUM_4] = static_cast<ArkUI_Float32>(yDirection);
    values[NUM_5] = static_cast<ArkUI_Float32>(zDirection);
    values[NUM_6] = static_cast<ArkUI_Float32>(angle);
    values[NUM_7] = static_cast<ArkUI_Float32>(perspective);
    return true;
}

void ParseBlurOption(const EcmaVM* vm, const Local<JSValueRef> blurOptionsArg, BlurOption& blurOption)
{
    if (blurOptionsArg->IsArray(vm)) {
        Local<panda::ArrayRef> params = static_cast<Local<panda::ArrayRef>>(blurOptionsArg);
        auto grey1 = params->GetValueAt(vm, blurOptionsArg, 0)->Uint32Value(vm);
        auto grey2 = params->GetValueAt(vm, blurOptionsArg, 1)->Uint32Value(vm);
        std::vector<float> greyVec(2);
        greyVec[0] = grey1;
        greyVec[1] = grey2;
        blurOption.grayscale = greyVec;
    }
}

void ParseDynamicBrightnessOption(ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm,
    ArkUI_Float32& rate, ArkUI_Float32& lightUpDegree, ArkUI_Float32& cubicCoeff, ArkUI_Float32& quadCoeff,
    ArkUI_Float32& saturation, std::vector<float>& posRGB, std::vector<float>& negRGB, ArkUI_Float32& fraction)
{
    Local<JSValueRef> rateArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> lightUpDegreeArg = runtimeCallInfo->GetCallArgRef(2);
    Local<JSValueRef> cubicCoeffArg = runtimeCallInfo->GetCallArgRef(3);
    Local<JSValueRef> quadCoeffArg = runtimeCallInfo->GetCallArgRef(4);
    Local<JSValueRef> saturationArg = runtimeCallInfo->GetCallArgRef(5);
    Local<JSValueRef> posRGBArg = runtimeCallInfo->GetCallArgRef(6);
    Local<JSValueRef> negRGBArg = runtimeCallInfo->GetCallArgRef(7);
    Local<JSValueRef> fractionArg = runtimeCallInfo->GetCallArgRef(8);
    if (rateArg->IsNumber()) {
        rate = rateArg->ToNumber(vm)->Value();
    }
    if (lightUpDegreeArg->IsNumber()) {
        lightUpDegree = lightUpDegreeArg->ToNumber(vm)->Value();
    }
    if (cubicCoeffArg->IsNumber()) {
        cubicCoeff = cubicCoeffArg->ToNumber(vm)->Value();
    }
    if (quadCoeffArg->IsNumber()) {
        quadCoeff = quadCoeffArg->ToNumber(vm)->Value();
    }
    if (saturationArg->IsNumber()) {
        saturation = saturationArg->ToNumber(vm)->Value();
    }
    if (posRGBArg->IsArray(vm)) {
        Local<panda::ArrayRef> params = static_cast<Local<panda::ArrayRef>>(posRGBArg);
        auto r = params->GetValueAt(vm, posRGBArg, 0)->Uint32Value(vm);
        auto g = params->GetValueAt(vm, posRGBArg, 1)->Uint32Value(vm);
        auto b = params->GetValueAt(vm, posRGBArg, 2)->Uint32Value(vm);
        posRGB[0] = r;
        posRGB[1] = g;
        posRGB[2] = b;
    }
    if (negRGBArg->IsArray(vm)) {
        Local<panda::ArrayRef> params = static_cast<Local<panda::ArrayRef>>(negRGBArg);
        auto r = params->GetValueAt(vm, negRGBArg, 0)->Uint32Value(vm);
        auto g = params->GetValueAt(vm, negRGBArg, 1)->Uint32Value(vm);
        auto b = params->GetValueAt(vm, negRGBArg, 2)->Uint32Value(vm);
        negRGB[0] = r;
        negRGB[1] = g;
        negRGB[2] = b;
    }
    if (fractionArg->IsNumber()) {
        fraction = fractionArg->ToNumber(vm)->Value();
    }
}

bool ParseCalcDimension(const EcmaVM* vm,
    ArkUINodeHandle node, const Local<JSValueRef>& value, CalcDimension& result, bool isWidth,
    RefPtr<ResourceObject>& resourceObject)
{
    CHECK_NULL_RETURN(vm, false);
    bool undefined = value->IsUndefined();
    if (undefined) {
        GetArkUINodeModifiers()->getCommonModifier()->clearWidthOrHeight(node, isWidth);
        return true;
    }
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        if (!ArkTSUtils::ParseJsDimensionVpNG(vm, value, result, resourceObject)) {
            GetArkUINodeModifiers()->getCommonModifier()->clearWidthOrHeight(node, isWidth);
            return false;
        }
    } else if (!ArkTSUtils::ParseJsDimensionVp(vm, value, result, resourceObject)) {
        return false;
    }

    if (LessNotEqual(result.Value(), 0.0)) {
        result.SetValue(0.0);
    }
    std::string calc = result.CalcValue();
    auto RawResObj = AceType::RawPtr(resourceObject);
    if (isWidth) {
        GetArkUINodeModifiers()->getCommonModifier()->setWidth(
            node, result.Value(), static_cast<int32_t>(result.Unit()), calc.c_str(), RawResObj);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->setHeight(
            node, result.Value(), static_cast<int32_t>(result.Unit()), calc.c_str(), RawResObj);
    }
    return true;
}

void ParseResizableCalcDimensions(ArkUIRuntimeCallInfo* runtimeCallInfo, uint32_t offset, uint32_t count,
    std::vector<std::optional<CalcDimension>>& results, const CalcDimension& defValue,
    std::vector<RefPtr<ResourceObject>>& bgImageResizableResObjs)
{
    auto end = offset + count;
    auto argsNumber = runtimeCallInfo->GetArgsNumber();
    if (end > argsNumber) {
        return;
    }
    CalcDimension defaultDimension(defValue);
    EcmaVM* vm = runtimeCallInfo->GetVM();
    for (uint32_t index = offset; index < end; index++) {
        auto arg = runtimeCallInfo->GetCallArgRef(index);
        std::optional<CalcDimension> optCalcDimension;
        CalcDimension dimension(defValue);
        RefPtr<ResourceObject> resObj;
        if (ArkTSUtils::ParseJsDimensionVp(vm, arg, dimension, resObj, false)) {
            optCalcDimension = dimension;
        } else {
            optCalcDimension = defaultDimension;
        }
        bgImageResizableResObjs.push_back(resObj);
        results.push_back(optCalcDimension);
    }
}

bool ParseJsAlignRule(const EcmaVM* vm, const Local<JSValueRef> &arg, std::string& anchor, ArkUI_Int32 &direction)
{
    if (arg->IsString(vm)) {
        std::string directionString = arg->ToString(vm)->ToString(vm);
        if (directionString.empty()) {
            return false;
        }
        size_t pos = directionString.find('|');
        if (pos == std::string::npos) {
            return false;
        }
        char* endPtr = nullptr;
        long alignValue = std::strtol(directionString.substr(0, pos).c_str(), &endPtr, 10);
        direction = static_cast<int8_t>(alignValue);
        anchor = directionString.substr(pos + 1);
        return true;
    }
    return false;
}

bool ParseResponseRegion(const EcmaVM* vm, const Local<JSValueRef>& jsValue, ArkUI_Float32 regionValues[],
    int32_t regionUnits[], int32_t length)
{
    if (jsValue->IsUndefined() || !jsValue->IsArray(vm)) {
        return false;
    }

    Local<panda::ArrayRef> transArray = static_cast<Local<panda::ArrayRef>>(jsValue);
    for (int32_t i = 0; i < length; i = i + NUM_4) {
        Local<JSValueRef> x = transArray->GetValueAt(vm, jsValue, i + NUM_0);
        Local<JSValueRef> y = transArray->GetValueAt(vm, jsValue, i + NUM_1);
        Local<JSValueRef> width = transArray->GetValueAt(vm, jsValue, i + NUM_2);
        Local<JSValueRef> height = transArray->GetValueAt(vm, jsValue, i + NUM_3);
        CalcDimension xDimen = CalcDimension(0.0, DimensionUnit::VP);
        CalcDimension yDimen = CalcDimension(0.0, DimensionUnit::VP);
        CalcDimension widthDimen = CalcDimension(1, DimensionUnit::PERCENT);
        CalcDimension heightDimen = CalcDimension(1, DimensionUnit::PERCENT);
        auto s1 = width->ToString(vm)->ToString(vm);
        auto s2 = height->ToString(vm)->ToString(vm);
        if (s1.find('-') != std::string::npos) {
            width = ToJSValue("100%");
        }
        if (s2.find('-') != std::string::npos) {
            height = ToJSValue("100%");
        }
        if (!ArkTSUtils::ParseJsDimensionNG(vm, x, xDimen, DimensionUnit::VP)) {
            xDimen = CalcDimension(0.0, DimensionUnit::VP);
        }
        if (!ArkTSUtils::ParseJsDimensionNG(vm, y, yDimen, DimensionUnit::VP)) {
            yDimen = CalcDimension(0.0, DimensionUnit::VP);
        }
        if (!ArkTSUtils::ParseJsDimensionNG(vm, width, widthDimen, DimensionUnit::VP)) {
            widthDimen = CalcDimension(1, DimensionUnit::PERCENT);
        }
        if (!ArkTSUtils::ParseJsDimensionNG(vm, height, heightDimen, DimensionUnit::VP)) {
            heightDimen = CalcDimension(1, DimensionUnit::PERCENT);
        }
        regionValues[i + NUM_0] = static_cast<ArkUI_Float32>(xDimen.Value());
        regionUnits[i + NUM_0] = static_cast<int32_t>(xDimen.Unit());
        regionValues[i + NUM_1] = static_cast<ArkUI_Float32>(yDimen.Value());
        regionUnits[i + NUM_1] = static_cast<int32_t>(yDimen.Unit());
        regionValues[i + NUM_2] = static_cast<ArkUI_Float32>(widthDimen.Value());
        regionUnits[i + NUM_2] = static_cast<int32_t>(widthDimen.Unit());
        regionValues[i + NUM_3] = static_cast<ArkUI_Float32>(heightDimen.Value());
        regionUnits[i + NUM_3] = static_cast<int32_t>(heightDimen.Unit());
    }
    return true;
}

std::function<void(bool)> ParseTransitionCallback(
    const JSRef<JSFunc>& jsFunc, const JSExecutionContext& context, FrameNode* node)
{
    auto jsFuncFinish = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(jsFunc));
    auto targetNode = AceType::WeakClaim(node);
    auto finishCallback = [execCtx = context, jsFuncFinish, targetNode](bool isTransitionIn) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        NG::PipelineContext::SetCallBackNode(targetNode);
        JSRef<JSVal> newJSVal = JSRef<JSVal>::Make(ToJSValue(isTransitionIn));
        jsFuncFinish->ExecuteJS(1, &newJSVal);
    };
    return finishCallback;
}

const std::vector<AccessibilitySamePageMode> PAGE_MODE_TYPE = { AccessibilitySamePageMode::SEMI_SILENT,
    AccessibilitySamePageMode::FULL_SILENT };
const std::vector<FocusDrawLevel> FOCUS_DRAW_LEVEL = { FocusDrawLevel::SELF, FocusDrawLevel::TOP };
} // namespace

ArkUINativeModuleValue CommonBridge::SetBackground(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> fourthArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);

    // Parse color background
    Color color;
    RefPtr<ResourceObject> backgroundColorResObj;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, backgroundColorResObj, nodeInfo)) {
        return panda::JSValueRef::Undefined(vm);
    }
    ArkUIBackgroundContent content;
    content.color = color.GetValue();
    content.bgColorRawPtr = AceType::RawPtr(backgroundColorResObj);

    ArkUIBackgroundOptions options;
    options.align = ALIGNMENT_CENTER;
    // Parse ignoresLayoutSafeAreaEdges
    std::vector<ArkUI_Int32> edges;
    if (!ArkTSUtils::ParseJsIgnoresLayoutSafeAreaEdges(vm, fourthArg, edges)) {
        edges.emplace_back(DEFAULT_LAYOUT_SAFE_AREA_EDGE_FOR_COLOR_BACKGROUND);
    }
    options.ignoresLayoutSafeAreaEdges = edges.data();
    options.ignoresLayoutSafeAreaEdgesSize = edges.size();
    
    GetArkUINodeModifiers()->getCommonModifier()->setBackground(nativeNode, &content, &options);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetBackground(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetBackground(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetBackgroundColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Color color;
    RefPtr<ResourceObject> backgroundColorResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, backgroundColorResObj, nodeInfo)) {
        GetArkUINodeModifiers()->getCommonModifier()->resetBackgroundColor(nativeNode);
    } else {
        auto bgColorRawPtr = AceType::RawPtr(backgroundColorResObj);
        GetArkUINodeModifiers()->getCommonModifier()->setBackgroundColorWithColorSpace(
            nativeNode, color.GetValue(), color.GetColorSpace(), bgColorRawPtr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetBackgroundColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetBackgroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void SetBorderWidthArray(const EcmaVM* vm, const Local<JSValueRef>& args, ArkUI_Float32 values[],
    int units[], int index, std::vector<RefPtr<ResourceObject>>& resObj)
{
    CalcDimension borderDimension;
    RefPtr<ResourceObject> borderDimensionResObj;
    if (!args->IsUndefined()) {
        if (ArkTSUtils::ParseAllBorder(vm, args, borderDimension, borderDimensionResObj)) {
            values[index] = borderDimension.Value();
            units[index] = static_cast<int>(borderDimension.Unit());
        } else {
            values[index] = 0;
            units[index] = static_cast<int>(DimensionUnit::VP);
        }
        if (SystemProperties::ConfigChangePerform()) {
            resObj.push_back(borderDimensionResObj);
        }
    } else {
        values[index] = -1;
        units[index] = static_cast<int>(DimensionUnit::INVALID);
        ParseNullptrResObj(resObj, NUM_1);
    }
}

bool ParseLocalizedBorderWidth(const EcmaVM* vm, const Local<JSValueRef>& value, CalcDimension& dimen)
{
    if (ArkTSUtils::ParseJsLengthMetrics(vm, value, dimen)) {
        if (LessOrEqual(dimen.Value(), 0.0)) {
            dimen.SetValue(0.0);
            dimen.SetUnit(DimensionUnit::VP);
        }
        return true;
    }
    return false;
}

void SetBorderWidthArrayByDimen(CalcDimension& borderDimension, ArkUI_Float32 values[], int units[], int index)
{
    values[index] = borderDimension.Value();
    units[index] = static_cast<int>(borderDimension.Unit());
}

void ParseBorderWidthLengthMetrics(EcmaVM* vm, Local<JSValueRef> arg, CalcDimension& dimension, bool& isLengthMetrics)
{
    if (arg->IsObject(vm)) {
        isLengthMetrics |= ParseLocalizedBorderWidth(vm, arg, dimension);
    }
}

ArkUINativeModuleValue CommonBridge::SetBorderWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> topArgs = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> rightArgs = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> bottomArgs = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> leftArgs = runtimeCallInfo->GetCallArgRef(NUM_4);
    if (leftArgs->IsUndefined() && rightArgs->IsUndefined() && topArgs->IsUndefined() && bottomArgs->IsUndefined()) {
        GetArkUINodeModifiers()->getCommonModifier()->resetBorderWidth(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    CalcDimension top;
    CalcDimension right;
    CalcDimension bottom;
    CalcDimension left;
    bool isLengthMetrics = false;

    ParseBorderWidthLengthMetrics(vm, topArgs, top, isLengthMetrics);
    ParseBorderWidthLengthMetrics(vm, rightArgs, right, isLengthMetrics);
    ParseBorderWidthLengthMetrics(vm, bottomArgs, bottom, isLengthMetrics);
    ParseBorderWidthLengthMetrics(vm, leftArgs, left, isLengthMetrics);

    uint32_t size = SIZE_OF_FOUR;
    ArkUI_Float32 values[size];
    std::vector<RefPtr<ResourceObject>> resObj;
    int units[size];

    if (isLengthMetrics) {
        auto isRightToLeft = AceApplicationInfo::GetInstance().IsRightToLeft();
        SetBorderWidthArrayByDimen(top, values, units, NUM_0);
        SetBorderWidthArrayByDimen(isRightToLeft ? left : right, values, units, NUM_1);
        SetBorderWidthArrayByDimen(bottom, values, units, NUM_2);
        SetBorderWidthArrayByDimen(isRightToLeft ? right : left, values, units, NUM_3);
        ParseNullptrResObj(resObj, NUM_4);
    } else {
        SetBorderWidthArray(vm, topArgs, values, units, NUM_0, resObj);
        SetBorderWidthArray(vm, rightArgs, values, units, NUM_1, resObj);
        SetBorderWidthArray(vm, bottomArgs, values, units, NUM_2, resObj);
        SetBorderWidthArray(vm, leftArgs, values, units, NUM_3, resObj);
    }

    auto rawPtr = static_cast<void*>(&resObj);
    GetArkUINodeModifiers()->getCommonModifier()->setBorderWidth(nativeNode, values, units, size, rawPtr);
    return panda::JSValueRef::Undefined(vm);
}

void CommonBridge::ParseOuterBorderWidth( ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm,
    std::vector<ArkUI_Float32>& values, bool needLocalized)
{
    std::vector<RefPtr<ResourceObject>> resObj;
    ParseOuterBorderWidth(runtimeCallInfo, vm, values, resObj, needLocalized);
}

void CommonBridge::ParseOuterBorderWidth(ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm,
    std::vector<ArkUI_Float32>& values, std::vector<RefPtr<ResourceObject>>& resObjs, bool needLocalized)
{
    Local<JSValueRef> leftArgs = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> rightArgs = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> topArgs = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> bottomArgs = runtimeCallInfo->GetCallArgRef(NUM_4);

    std::optional<CalcDimension> leftDim;
    std::optional<CalcDimension> rightDim;
    std::optional<CalcDimension> topDim;
    std::optional<CalcDimension> bottomDim;
    std::optional<CalcDimension> startDim;
    std::optional<CalcDimension> endDim;

    ParseOuterBorder(vm, leftArgs, leftDim, resObjs);
    ParseOuterBorder(vm, rightArgs, rightDim, resObjs);
    if (needLocalized) {
        Local<JSValueRef> startArgs = runtimeCallInfo->GetCallArgRef(25); // 25: index of BorderWidth.start
        Local<JSValueRef> endArgs = runtimeCallInfo->GetCallArgRef(26);   // 26: index of BorderWidth.end
        ArkTSUtils::ParseOuterBorderForDashParams(vm, startArgs, startDim);
        ArkTSUtils::ParseOuterBorderForDashParams(vm, endArgs, endDim);
        ArkTSUtils::ParseOuterBorderForDashParams(vm, topArgs, topDim);
        ArkTSUtils::ParseOuterBorderForDashParams(vm, bottomArgs, bottomDim);
        ParseNullptrResObj(resObjs, NUM_2);
    } else {
        ParseOuterBorder(vm, topArgs, topDim, resObjs);
        ParseOuterBorder(vm, bottomArgs, bottomDim, resObjs);
    }

    if (startDim.has_value() || endDim.has_value()) {
        PushOuterBorderDimensionVector(startDim, values);
        PushOuterBorderDimensionVector(endDim, values);
    } else {
        PushOuterBorderDimensionVector(leftDim, values);
        PushOuterBorderDimensionVector(rightDim, values);
    }
    PushOuterBorderDimensionVector(topDim, values);
    PushOuterBorderDimensionVector(bottomDim, values);
}

ArkUINativeModuleValue CommonBridge::ResetBorderWidth(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetBorderWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void ParseMirrorDimen(ArkUI_Float32 values[], int units[], int idx, CalcDimension& calcDimen)
{
    values[idx] = calcDimen.Value();
    units[idx] = static_cast<int>(calcDimen.Unit());
}

void ParseJsDimensionVpResObj(EcmaVM* vm, const Local<JSValueRef>& refValue, CalcDimension& dimension,
    std::vector<RefPtr<ResourceObject>>& vectorResObj)
{
    RefPtr<ResourceObject> resObj;
    ArkTSUtils::ParseJsDimensionVp(vm, refValue, dimension, resObj);
    if (resObj) {
        vectorResObj.push_back(resObj);
    } else {
        vectorResObj.push_back(nullptr);
    }
}

void ParseJsShadowRadiusResObj(const EcmaVM *vm, const Local<JSValueRef>& radiusArg, double& radius,
    std::vector<RefPtr<ResourceObject>>& vectorResObj)
{
    RefPtr<ResourceObject> radiusResObj;
    ArkTSUtils::ParseJsDouble(vm, radiusArg, radius, radiusResObj);
    if (radiusResObj) {
        vectorResObj.push_back(radiusResObj);
    } else {
        vectorResObj.push_back(nullptr);
    }
}

bool ParseJsShadowColorResObj(const EcmaVM *vm, const Local<JSValueRef>& colorArg, int32_t& type, uint32_t& color,
    std::vector<RefPtr<ResourceObject>>& vectorResObj, ArkUINodeHandle nativeNode)
{
    RefPtr<ResourceObject> colorResObj;
    bool ret = ParseJsShadowColor(vm, colorArg, type, color, colorResObj, nativeNode);
    if (colorResObj) {
        vectorResObj.push_back(colorResObj);
    } else {
        vectorResObj.push_back(nullptr);
    }
    return ret;
}

bool SetBackShadowForShadowStyle(const ArkUINodeHandle nativeNode, const EcmaVM *vm,
    const Local<JSValueRef>& styleArg)
{
    int32_t shadowStyle = 0;
    if (ArkTSUtils::ParseJsInteger(vm, styleArg, shadowStyle)) {
        ArkUIInt32orFloat32 shadows[] = { {.i32 = shadowStyle} };
        GetArkUINodeModifiers()->getCommonModifier()->setBackShadow(nativeNode, shadows,
            (sizeof(shadows) / sizeof(shadows[NUM_0])), nullptr);
        return true;
    }
    return false;
}

void SetBorderRadiusArray(const EcmaVM* vm, const Local<JSValueRef>& args, CalcDimension& result,
    std::vector<RefPtr<ResourceObject>>& resObjs)
{
    RefPtr<ResourceObject> resObj;
    ArkTSUtils::ParseAllBorder(vm, args, result, resObj);
    if (SystemProperties::ConfigChangePerform()) {
        resObjs.push_back(resObj);
    }
}

void ParseBorderRadiusLengthMetrics(EcmaVM* vm, Local<JSValueRef> arg, CalcDimension& dimension, bool& isLengthMetrics)
{
    if (arg->IsObject(vm)) {
        isLengthMetrics |= ParseLocalizedBorderRadius(vm, arg, dimension);
    }
}

ArkUINativeModuleValue CommonBridge::SetBorderRadius(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> topLeftArgs = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> topRightArgs = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> bottomLeftArgs = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> bottomRightArgs = runtimeCallInfo->GetCallArgRef(NUM_4);
    if (topLeftArgs->IsUndefined() && topRightArgs->IsUndefined() && bottomLeftArgs->IsUndefined() &&
        bottomRightArgs->IsUndefined()) {
        GetArkUINodeModifiers()->getCommonModifier()->resetBorderRadius(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    CalcDimension topLeft;
    CalcDimension topRight;
    CalcDimension bottomLeft;
    CalcDimension bottomRight;
    std::vector<RefPtr<ResourceObject>> resObj;
    bool isLengthMetrics = false;
    ParseBorderRadiusLengthMetrics(vm, topLeftArgs, topLeft, isLengthMetrics);
    ParseBorderRadiusLengthMetrics(vm, topRightArgs, topRight, isLengthMetrics);
    ParseBorderRadiusLengthMetrics(vm, bottomLeftArgs, bottomLeft, isLengthMetrics);
    ParseBorderRadiusLengthMetrics(vm, bottomRightArgs, bottomRight, isLengthMetrics);
    if (!isLengthMetrics) {
        SetBorderRadiusArray(vm, topLeftArgs, topLeft, resObj);
        SetBorderRadiusArray(vm, topRightArgs, topRight, resObj);
        SetBorderRadiusArray(vm, bottomLeftArgs, bottomLeft, resObj);
        SetBorderRadiusArray(vm, bottomRightArgs, bottomRight, resObj);
    } else {
        ParseNullptrResObj(resObj, NUM_4);
    }
    ArkUI_Float32 values[SIZE_OF_FOUR];
    int units[SIZE_OF_FOUR];
    bool isMirror = isLengthMetrics && AceApplicationInfo::GetInstance().IsRightToLeft();
    ParseMirrorDimen(values, units, NUM_0, isMirror ? topRight : topLeft);
    ParseMirrorDimen(values, units, NUM_1, isMirror ? topLeft : topRight);
    ParseMirrorDimen(values, units, NUM_2, isMirror ? bottomRight : bottomLeft);
    ParseMirrorDimen(values, units, NUM_3, isMirror ? bottomLeft : bottomRight);
    auto rawPtr = static_cast<void*>(&resObj);
    GetArkUINodeModifiers()->getCommonModifier()->setBorderRadius(nativeNode, values, units, SIZE_OF_FOUR, rawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetBorderRadius(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetBorderRadius(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

LayoutCalPolicy CommonBridge::ParseLayoutPolicy(const std::string& layoutPolicy)
{
    if (layoutPolicy == "matchParent") {
        return LayoutCalPolicy::MATCH_PARENT;
    }
    if (layoutPolicy == "wrapContent") {
        return LayoutCalPolicy::WRAP_CONTENT;
    }
    if (layoutPolicy == "fixAtIdealSize") {
        return LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    }
    return LayoutCalPolicy::NO_MATCH;
}

ArkUINativeModuleValue CommonBridge::SetWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(NUM_1);
    CalcDimension width;
    RefPtr<ResourceObject> widthResObj;
    std::string calcStr;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, width, widthResObj)) {
        GetArkUINodeModifiers()->getCommonModifier()->resetWidth(nativeNode);
        if (jsValue->IsObject(vm)) {
            auto obj = jsValue->ToObject(vm);
            auto layoutPolicy = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id_"));
            if (layoutPolicy->IsString(vm)) {
                auto policy = ParseLayoutPolicy(layoutPolicy->ToString(vm)->ToString(vm));
                ViewAbstractModel::GetInstance()->UpdateLayoutPolicyProperty(policy, true);
                return panda::JSValueRef::Undefined(vm);
            }
        }
    } else {
        if (LessNotEqual(width.Value(), 0.0)) {
            if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
                GetArkUINodeModifiers()->getCommonModifier()->resetWidth(nativeNode);
                ViewAbstractModel::GetInstance()->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, true);
                return panda::JSValueRef::Undefined(vm);
            }
            width.SetValue(0.0);
        }

        auto widthRawResObj = AceType::RawPtr(widthResObj);
        if (width.Unit() == DimensionUnit::CALC) {
            GetArkUINodeModifiers()->getCommonModifier()->setWidth(
                nativeNode, 0, static_cast<int32_t>(width.Unit()), width.CalcValue().c_str(), widthRawResObj);
        } else {
            GetArkUINodeModifiers()->getCommonModifier()->setWidth(
                nativeNode, width.Value(), static_cast<int32_t>(width.Unit()), calcStr.c_str(), widthRawResObj);
        }
    }
    ViewAbstractModel::GetInstance()->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, true);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(NUM_1);
    CalcDimension height;
    RefPtr<ResourceObject> heightResObj;
    std::string calcStr;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, height, heightResObj)) {
        GetArkUINodeModifiers()->getCommonModifier()->resetHeight(nativeNode);
        if (jsValue->IsObject(vm)) {
            auto obj = jsValue->ToObject(vm);
            auto layoutPolicy = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id_"));
            if (layoutPolicy->IsString(vm)) {
                auto policy = ParseLayoutPolicy(layoutPolicy->ToString(vm)->ToString(vm));
                ViewAbstractModel::GetInstance()->UpdateLayoutPolicyProperty(policy, false);
                return panda::JSValueRef::Undefined(vm);
            }
        }
    } else {
        if (LessNotEqual(height.Value(), 0.0)) {
            if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
                GetArkUINodeModifiers()->getCommonModifier()->resetHeight(nativeNode);
                ViewAbstractModel::GetInstance()->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, false);
                return panda::JSValueRef::Undefined(vm);
            }
            height.SetValue(0.0);
        }
        auto heightRawResObj = AceType::RawPtr(heightResObj);
        if (height.Unit() == DimensionUnit::CALC) {
            GetArkUINodeModifiers()->getCommonModifier()->setHeight(nativeNode, height.Value(),
                static_cast<int32_t>(height.Unit()), height.CalcValue().c_str(), heightRawResObj);
        } else {
            GetArkUINodeModifiers()->getCommonModifier()->setHeight(
                nativeNode, height.Value(), static_cast<int32_t>(height.Unit()), calcStr.c_str(), heightRawResObj);
        }
    }
    ViewAbstractModel::GetInstance()->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, false);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetHeight(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    bool useEdges = runtimeCallInfo->GetCallArgRef(NUM_1)->ToBoolean(vm)->Value();
    std::vector<ArkUIStringAndFloat> options;
    std::vector<std::optional<CalcDimension>> edges;
    std::vector<RefPtr<ResourceObject>> edgesResObj;

    if (useEdges) {
        ParseResult res = ParseCalcDimensionsNG(runtimeCallInfo, NUM_2, NUM_4, edges, edgesResObj, CalcDimension(0.0));
        if (res == ParseResult::LENGTHMETRICS_SUCCESS && AceApplicationInfo::GetInstance().IsRightToLeft()) {
            // Swap left and right
            std::swap(edges[NUM_1], edges[NUM_3]);
        }
        PushDimensionsToVector(options, edges);
        auto edgesRawPtr = static_cast<void*>(&edgesResObj);
        GetArkUINodeModifiers()->getCommonModifier()->setPositionEdges(
            nativeNode, useEdges, options.data(), edgesRawPtr);
    } else {
        ParseCalcDimensionsNG(runtimeCallInfo, NUM_2, NUM_2, edges, edgesResObj, CalcDimension(0.0));
        PushDimensionsToVector(options, edges);
        auto edgesRawPtr = static_cast<void*>(&edgesResObj);
        GetArkUINodeModifiers()->getCommonModifier()->setPositionEdges(
            nativeNode, useEdges, options.data(), edgesRawPtr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetPosition(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetPositionEdges(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetTransform(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(NUM_1);

    if (!jsValue->IsArray(vm)) {
        GetArkUINodeModifiers()->getCommonModifier()->resetTransform(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    const auto matrix4Len = Matrix4::DIMENSION * Matrix4::DIMENSION;
    float matrix[matrix4Len];
    Local<panda::ArrayRef> transArray = static_cast<Local<panda::ArrayRef>>(jsValue);
    for (size_t i = 0; i < transArray->Length(vm); i++) {
        Local<JSValueRef> value = transArray->GetValueAt(vm, jsValue, i);
        matrix[i] = value->ToNumber(vm)->Value();
    }
    GetArkUINodeModifiers()->getCommonModifier()->setTransform(nativeNode, matrix, matrix4Len);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetTransform(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    GetArkUINodeModifiers()->getCommonModifier()->resetTransform(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetTransform3D(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    if (firstArg->IsNull()) {
        return panda::NativePointerRef::New(vm, nullptr);
    }
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(NUM_1);

    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::NativePointerRef::New(vm, nullptr));

    if (!jsValue->IsArray(vm)) {
        nodeModifiers->getCommonModifier()->resetTransform3D(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    const auto matrix4Len = Matrix4::DIMENSION * Matrix4::DIMENSION;
    float matrix[matrix4Len];
    Local<panda::ArrayRef> transArray = static_cast<Local<panda::ArrayRef>>(jsValue);
    if (transArray->Length(vm) != matrix4Len) {
        TAG_LOGW(AceLogTag::ACE_VISUAL_EFFECT,
            "Invalid matrix parameter: Expected %{public}d elements, but transArray has %{public}u elements",
            matrix4Len, transArray->Length(vm));
        nodeModifiers->getCommonModifier()->resetTransform3D(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    for (size_t i = 0; i < transArray->Length(vm); i++) {
        Local<JSValueRef> value = transArray->GetValueAt(vm, jsValue, i);
        matrix[i] = value->ToNumber(vm)->Value();
    }
    nodeModifiers->getCommonModifier()->setTransform3D(nativeNode, matrix, matrix4Len);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetTransform3D(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (firstArg->IsNull()) {
        return panda::NativePointerRef::New(vm, nullptr);
    }
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::NativePointerRef::New(vm, nullptr));
    nodeModifiers->getCommonModifier()->resetTransform3D(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetBorderColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> topArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> rightArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> bottomArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> leftArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> isLocalizedArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto isLocalized = (isLocalizedArg->IsBoolean()) ? isLocalizedArg->ToBoolean(vm)->Value() : false;
    std::vector<RefPtr<ResourceObject>> resObj;

    Color topColor;
    Color rightColor;
    Color bottomColor;
    Color leftColor;

    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, topArg, topColor, resObj, nodeInfo)) {
        topColor.SetValue(COLOR_ALPHA_VALUE);
    }
    if (!ArkTSUtils::ParseJsColorAlpha(vm, rightArg, rightColor, resObj, nodeInfo)) {
        rightColor.SetValue(COLOR_ALPHA_VALUE);
    }
    if (!ArkTSUtils::ParseJsColorAlpha(vm, bottomArg, bottomColor, resObj, nodeInfo)) {
        bottomColor.SetValue(COLOR_ALPHA_VALUE);
    }
    if (!ArkTSUtils::ParseJsColorAlpha(vm, leftArg, leftColor, resObj, nodeInfo)) {
        leftColor.SetValue(COLOR_ALPHA_VALUE);
    }
    auto isRightToLeft = AceApplicationInfo::GetInstance().IsRightToLeft();
    if (SystemProperties::ConfigChangePerform() && isRightToLeft && isLocalized) {
        std::swap(resObj[1], resObj[3]);
    }
    auto rawPtr = static_cast<void*>(&resObj);
    GetArkUINodeModifiers()->getCommonModifier()->setBorderColor(nativeNode,
        topColor.GetValue(),
        (isRightToLeft && isLocalized) ? leftColor.GetValue() : rightColor.GetValue(),
        bottomColor.GetValue(),
        (isRightToLeft && isLocalized) ? rightColor.GetValue() : leftColor.GetValue(), rawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetBorderColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetBorderColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetOutlineColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    std::vector<uint32_t> colorOptions;
    std::vector<RefPtr<ResourceObject>> vectorResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    ParseOutLineColor(runtimeCallInfo, vm, colorOptions, NUM_1, vectorResObj, nodeInfo);
    auto rawPtr = static_cast<void*>(&vectorResObj);
    GetArkUINodeModifiers()->getCommonModifier()->setOutlineColor(
        nativeNode, colorOptions.data(), colorOptions.size(), rawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetOutlineColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetOutlineColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetOutlineRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    std::vector<ArkUI_Float32> radiusOptions;
    std::vector<RefPtr<ResourceObject>> vectorResObj;
    ParseOuterBorderRadius(runtimeCallInfo, vm, radiusOptions, NUM_1, vectorResObj);
    auto rawPtr = static_cast<void*>(&vectorResObj);
    GetArkUINodeModifiers()->getCommonModifier()->setOutlineRadius(
        nativeNode, radiusOptions.data(), radiusOptions.size(), rawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetOutlineRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetOutlineRadius(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetOutlineWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    std::vector<ArkUI_Float32> widthOptions;
    std::vector<RefPtr<ResourceObject>> vectorResObj;
    ParseOuterBorderWidth(runtimeCallInfo, vm, widthOptions, vectorResObj);
    auto rawPtr = static_cast<void*>(&vectorResObj);
    GetArkUINodeModifiers()->getCommonModifier()->setOutlineWidth(
        nativeNode, widthOptions.data(), widthOptions.size(), rawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetOutlineWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetOutlineWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetOutlineStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    std::vector<uint32_t> styleOptions;
    ParseOuterBorderStyle(runtimeCallInfo, vm, styleOptions, NUM_1);
    GetArkUINodeModifiers()->getCommonModifier()->setOutlineStyle(
        nativeNode, styleOptions.data(), styleOptions.size());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetOutlineStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetOutlineStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetOutline(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    std::vector<ArkUI_Float32> options;
    std::vector<RefPtr<ResourceObject>> vectorResObj;
    ParseOuterBorderWidth(runtimeCallInfo, vm, options, vectorResObj);         // Outline Width args start index from 1
    ParseOuterBorderRadius(runtimeCallInfo, vm, options, NUM_9, vectorResObj); // Outline Radius args start index

    std::vector<uint32_t> colorAndStyleOptions;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    ParseOuterBorderColor(runtimeCallInfo, vm, colorAndStyleOptions, NUM_5, vectorResObj, nodeInfo);  // Outline Color args start index
    ParseOuterBorderStyle(runtimeCallInfo, vm, colorAndStyleOptions, NUM_13); // Outline Style args start index

    auto resRawPtr = static_cast<void*>(&vectorResObj);
    GetArkUINodeModifiers()->getCommonModifier()->setOutline(
        nativeNode, options.data(), options.size(), colorAndStyleOptions.data(), colorAndStyleOptions.size(), resRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetOutline(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetOutline(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetBorderStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto typeArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto styleArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    auto topArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    auto rightArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    auto bottomArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    auto leftArg = runtimeCallInfo->GetCallArgRef(NUM_6);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if ((!typeArg->IsBoolean()) || (!typeArg->BooleaValue(vm))) {
        int32_t styles[] = { static_cast<int32_t>(BorderStyle::SOLID) };
        GetArkUINodeModifiers()->getCommonModifier()->setBorderStyle(nativeNode, styles,
            (sizeof(styles) / sizeof(styles[NUM_0])));
        return panda::JSValueRef::Undefined(vm);
    }
    if (styleArg->IsInt()) {
        int32_t styles[] = { styleArg->Int32Value(vm) };
        GetArkUINodeModifiers()->getCommonModifier()->setBorderStyle(nativeNode, styles,
            (sizeof(styles) / sizeof(styles[NUM_0])));
        return panda::JSValueRef::Undefined(vm);
    }
    int32_t styles[] = { -1, -1, -1, -1 };
    if (topArg->IsInt()) {
        styles[NUM_0] = topArg->Int32Value(vm);
    }
    if (rightArg->IsInt()) {
        styles[NUM_1] = rightArg->Int32Value(vm);
    }
    if (bottomArg->IsInt()) {
        styles[NUM_2] = bottomArg->Int32Value(vm);
    }
    if (leftArg->IsInt()) {
        styles[NUM_3] = leftArg->Int32Value(vm);
    }
    GetArkUINodeModifiers()->getCommonModifier()->setBorderStyle(nativeNode, styles,
        (sizeof(styles) / sizeof(styles[NUM_0])));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetBorderStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetBorderStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetShadow(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto styleArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto radiusArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    auto typeArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    auto colorArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    auto offsetXArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    auto offsetYArg = runtimeCallInfo->GetCallArgRef(NUM_6);
    auto fillArg = runtimeCallInfo->GetCallArgRef(NUM_7);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (SetBackShadowForShadowStyle(nativeNode, vm, styleArg)) {
        return panda::JSValueRef::Undefined(vm);
    }
    ArkUIInt32orFloat32 shadows[] = { { 0.0 }, { .i32 = 0  }, { 0.0 }, { 0.0 },
        { .i32 = static_cast<ArkUI_Int32>(ShadowType::COLOR) }, { .u32 = 0 }, { .i32 = 0 } };
    std::vector<RefPtr<ResourceObject>> vectorResObj;
    double radius;
    ParseJsShadowRadiusResObj(vm, radiusArg, radius, vectorResObj);
    shadows[NUM_0].f32 = radius;

    shadows[NUM_0].f32 = (LessNotEqual(shadows[NUM_0].f32, 0.0)) ? 0.0 : shadows[NUM_0].f32;
    CalcDimension offsetX;
    if (ParseJsShadowDimension(vm, offsetXArg, offsetX, vectorResObj)) {
        shadows[NUM_2].f32 = offsetX.Value();
    }
    CalcDimension offsetY;
    if (ParseJsShadowDimension(vm, offsetYArg, offsetY, vectorResObj)) {
        shadows[NUM_3].f32 = offsetY.Value();
    }
    if (typeArg->IsInt()) {
        uint32_t shadowType = typeArg->Uint32Value(vm);
        shadows[NUM_4].i32 =
            std::clamp(shadowType, static_cast<uint32_t>(ShadowType::COLOR), static_cast<uint32_t>(ShadowType::BLUR));
    }
    int32_t type = 0;
    uint32_t color = 0;
    if (ParseJsShadowColorResObj(vm, colorArg, type, color, vectorResObj, nativeNode)) {
        shadows[NUM_1].i32 = type;
        shadows[NUM_5].u32 = color;
    }
    shadows[NUM_6].i32 = fillArg->IsBoolean() ? fillArg->BooleaValue(vm) : false;
    auto resRawPtr = static_cast<void*>(&vectorResObj);
    GetArkUINodeModifiers()->getCommonModifier()->setBackShadow(nativeNode, shadows,
        (sizeof(shadows) / sizeof(shadows[NUM_0])), resRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetShadow(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetBackShadow(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetHitTestBehavior(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsNumber()) {
        uint32_t hitTestModeNG = secondArg->Uint32Value(vm);
        GetArkUINodeModifiers()->getCommonModifier()->setHitTestBehavior(nativeNode, hitTestModeNG);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetHitTestBehavior(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetHitTestBehavior(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetHitTestBehavior(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetZIndex(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsNumber()) {
        int32_t value = secondArg->Int32Value(vm);
        GetArkUINodeModifiers()->getCommonModifier()->setZIndex(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetZIndex(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetZIndex(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetZIndex(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetOpacity(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    double opacity;
    RefPtr<ResourceObject> opacityResObj;
    if (!ArkTSUtils::ParseJsDouble(vm, secondArg, opacity, opacityResObj)) {
        GetArkUINodeModifiers()->getCommonModifier()->resetOpacity(nativeNode);
    } else {
        auto opacityRawPtr = AceType::RawPtr(opacityResObj);
        GetArkUINodeModifiers()->getCommonModifier()->setOpacity(nativeNode, opacity, opacityRawPtr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetOpacity(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetOpacity(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetAlign(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsNumber()) {
        GetArkUINodeModifiers()->getCommonModifier()->setAlign(nativeNode, secondArg->ToNumber(vm)->Value());
    } else if (secondArg->IsString(vm)) {
        GetArkUINodeModifiers()->getCommonModifier()->setLocalizedAlign(nativeNode, secondArg->ToString(vm)
            ->ToString(vm).c_str());
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetAlign(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetAlign(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetAlign(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetLayoutGravity(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsString(vm)) {
        GetArkUINodeModifiers()->getCommonModifier()->setLayoutGravity(
            nativeNode, secondArg->ToString(vm)->ToString(vm).c_str());
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetLayoutGravity(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetLayoutGravity(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetLayoutGravity(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetBackdropBlur(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> blurArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> blurOptionArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> disableSystemAdaptationArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    double blur = 0.0;
    if (!ArkTSUtils::ParseJsDouble(vm, blurArg, blur)) {
        GetArkUINodeModifiers()->getCommonModifier()->resetBackdropBlur(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    BlurOption blurOption;
    if (blurOptionArg->IsArray(vm)) {
        ParseBlurOption(vm, blurOptionArg, blurOption);
    }
    bool disableSystemAdaptation = false;
    if (disableSystemAdaptationArg->IsBoolean()) {
        disableSystemAdaptation = disableSystemAdaptationArg->ToBoolean(vm)->Value();
    }
    GetArkUINodeModifiers()->getCommonModifier()->setBackdropBlur(
        nativeNode, blur, blurOption.grayscale.data(), blurOption.grayscale.size(), disableSystemAdaptation);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetBackdropBlur(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetBackdropBlur(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetHueRotate(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    std::optional<float> degree;
    if (secondArg->IsString(vm)) {
        degree = static_cast<float>(StringUtils::StringToDegree(secondArg->ToString(vm)->ToString(vm)));
    } else if (secondArg->IsNumber()) {
        degree = static_cast<float>(secondArg->ToNumber(vm)->Value());
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetHueRotate(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    float deg = 0.0f;
    if (degree) {
        deg = degree.value();
        degree.reset();
    }
    GetArkUINodeModifiers()->getCommonModifier()->setHueRotate(nativeNode, deg);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetHueRotate(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetHueRotate(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetInvert(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> invertValueArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> optionLowArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> optionHighArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> optionThresholdArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> optionThresholdRangeArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    if (!invertValueArg->IsUndefined()) {
        double invertValue = 0.0;
        if (ArkTSUtils::ParseJsDouble(vm, invertValueArg, invertValue)) {
            ArkUI_Float32 invert[] = { static_cast<ArkUI_Float32>(invertValue) };
            GetArkUINodeModifiers()->getCommonModifier()->setInvert(nativeNode, invert, NUM_1);
        } else {
            GetArkUINodeModifiers()->getCommonModifier()->resetInvert(nativeNode);
        }
    } else {
        ArkUI_Float32 invert[] = { 0.0, 0.0, 0.0, 0.0 };
        double low = 0.0;
        double high = 0.0;
        double threshold = 0.0;
        double thresholdRange = 0.0;
        if (ArkTSUtils::ParseJsDouble(vm, optionLowArg, low)) {
            invert[NUM_0] = std::clamp(low, 0.0, 1.0);
        }
        if (ArkTSUtils::ParseJsDouble(vm, optionHighArg, high)) {
            invert[NUM_1] = std::clamp(high, 0.0, 1.0);
        }
        if (ArkTSUtils::ParseJsDouble(vm, optionThresholdArg, threshold)) {
            invert[NUM_2] = std::clamp(threshold, 0.0, 1.0);
        }
        if (ArkTSUtils::ParseJsDouble(vm, optionThresholdRangeArg, thresholdRange)) {
            invert[NUM_3] = std::clamp(thresholdRange, 0.0, 1.0);
        }
        GetArkUINodeModifiers()->getCommonModifier()->setInvert(nativeNode, invert, NUM_4);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetInvert(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetInvert(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetSepia(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsNumber()) {
        GetArkUINodeModifiers()->getCommonModifier()->setSepia(nativeNode, secondArg->ToNumber(vm)->Value());
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetSepia(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetSepia(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetSepia(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetSaturate(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsNumber()) {
        GetArkUINodeModifiers()->getCommonModifier()->setSaturate(nativeNode, secondArg->ToNumber(vm)->Value());
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetSaturate(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetSaturate(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetSaturate(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetColorBlend(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Color color;
    RefPtr<ResourceObject> colorBlendObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, colorBlendObj, nodeInfo)) {
        GetArkUINodeModifiers()->getCommonModifier()->resetColorBlend(nativeNode);
        } else {
            auto cbColorRawPtr = AceType::RawPtr(colorBlendObj);
            GetArkUINodeModifiers()->getCommonModifier()->setColorBlend(nativeNode, color.GetValue(), cbColorRawPtr);
        }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetColorBlend(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetColorBlend(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetGrayscale(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsNumber()) {
        GetArkUINodeModifiers()->getCommonModifier()->setGrayscale(nativeNode, secondArg->ToNumber(vm)->Value());
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetGrayscale(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetGrayscale(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetGrayscale(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetContrast(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsNumber()) {
        GetArkUINodeModifiers()->getCommonModifier()->setContrast(nativeNode, secondArg->ToNumber(vm)->Value());
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetContrast(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetContrast(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetContrast(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetBrightness(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsNumber()) {
        GetArkUINodeModifiers()->getCommonModifier()->setBrightness(nativeNode, secondArg->ToNumber(vm)->Value());
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetBrightness(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetBrightness(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetBrightness(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetBlur(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> blurArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> blurOptionArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> disableSystemAdaptationArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    double blur = 0.0;
    if (!ArkTSUtils::ParseJsDouble(vm, blurArg, blur)) {
        GetArkUINodeModifiers()->getCommonModifier()->resetBlur(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    BlurOption blurOption;
    if (blurOptionArg->IsArray(vm)) {
        ParseBlurOption(vm, blurOptionArg, blurOption);
    }
    bool disableSystemAdaptation = false;
    if (disableSystemAdaptationArg->IsBoolean()) {
        disableSystemAdaptation = disableSystemAdaptationArg->ToBoolean(vm)->Value();
    }
    GetArkUINodeModifiers()->getCommonModifier()->setBlur(
        nativeNode, blur, blurOption.grayscale.data(), blurOption.grayscale.size(), disableSystemAdaptation);

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetBlur(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetBlur(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetLinearGradient(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto angleArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto directionArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    auto colorsArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    auto repeatingArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    std::vector<ArkUIInt32orFloat32> values;
    ArkTSUtils::ParseGradientAngle(vm, angleArg, values);
    int32_t direction = static_cast<int32_t>(GradientDirection::NONE);
    ArkTSUtils::ParseJsInt32(vm, directionArg, direction);
    values.push_back({.i32 = static_cast<ArkUI_Int32>(direction)});

    std::vector<ArkUIInt32orFloat32> colors;
    std::vector<RefPtr<ResourceObject>> vectorResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    ArkTSUtils::ParseGradientColorStops(vm, colorsArg, colors, vectorResObj, nodeInfo);
    auto repeating = repeatingArg->IsBoolean() ? repeatingArg->BooleaValue(vm) : false;
    values.push_back({.i32 = static_cast<ArkUI_Int32>(repeating)});
    auto colorRawPtr = static_cast<void*>(&vectorResObj);
    GetArkUINodeModifiers()->getCommonModifier()->setLinearGradient(nativeNode, values.data(), values.size(),
        colors.data(), colors.size(), colorRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetLinearGradient(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetLinearGradient(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetSweepGradient(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto centerArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto startArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    auto endArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    auto rotationArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    auto colorsArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    auto metricsColorsArg = runtimeCallInfo->GetCallArgRef(NUM_6);
    auto repeatingArg = runtimeCallInfo->GetCallArgRef(NUM_7);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    std::vector<ArkUIInt32orFloat32> values;
    std::vector<RefPtr<ResourceObject>> vectorResObj;
    ArkTSUtils::ParseGradientCenter(vm, centerArg, values, vectorResObj);
    ArkTSUtils::ParseGradientAngle(vm, startArg, values);
    ArkTSUtils::ParseGradientAngle(vm, endArg, values);
    ArkTSUtils::ParseGradientAngle(vm, rotationArg, values);
    std::vector<ArkUIInt32orFloat32> colors;
    std::optional<ColorSpace> colorSpace;
    if (metricsColorsArg->IsArray(vm)) {
        ParseGradientColorStopsWithColorSpace(vm, metricsColorsArg, colors, colorSpace);
    } else {
        auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
        ArkTSUtils::ParseGradientColorStops(vm, colorsArg, colors, vectorResObj, nodeInfo);
    }
    if (!colorSpace.has_value()) {
        colorSpace = ColorSpace::SRGB;
    }
    auto repeating = repeatingArg->IsBoolean() ? repeatingArg->BooleaValue(vm) : false;
    values.push_back({.i32 = static_cast<ArkUI_Int32>(repeating)});
    auto resRawPtr = static_cast<void*>(&vectorResObj);
    GetArkUINodeModifiers()->getCommonModifier()->setSweepGradient(nativeNode, values.data(), values.size(),
        colors.data(), colors.size(), colorSpace.value(), resRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetSweepGradient(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetSweepGradient(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetRadialGradient(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto centerArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto radiusArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    auto colorsArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    auto repeatingArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    std::vector<ArkUIInt32orFloat32> values;
    std::vector<RefPtr<ResourceObject>> vectorResObj;
    ArkTSUtils::ParseGradientCenter(vm, centerArg, values, vectorResObj);
    CalcDimension radius;
    RefPtr<ResourceObject> radiusResObj;
    auto hasRadius = ArkTSUtils::ParseJsDimensionVp(vm, radiusArg, radius, radiusResObj, false);
    if (radiusResObj) {
        vectorResObj.push_back(radiusResObj);
    } else {
        vectorResObj.push_back(nullptr);
    }
    values.push_back({.i32 = static_cast<ArkUI_Int32>(hasRadius)});
    values.push_back({.f32 = static_cast<ArkUI_Float32>(radius.Value())});
    values.push_back({.i32 = static_cast<ArkUI_Int32>(radius.Unit())});
    std::vector<ArkUIInt32orFloat32> colors;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    ArkTSUtils::ParseGradientColorStops(vm, colorsArg, colors, vectorResObj, nodeInfo);
    auto repeating = repeatingArg->IsBoolean() ? repeatingArg->BooleaValue(vm) : false;
    values.push_back({.i32 = static_cast<ArkUI_Int32>(repeating)});
    auto resRawPtr = static_cast<void*>(&vectorResObj);
    GetArkUINodeModifiers()->getCommonModifier()->setRadialGradient(nativeNode, values.data(), values.size(),
        colors.data(), colors.size(), resRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetRadialGradient(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetRadialGradient(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetOverlay(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto valueArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto alignArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    auto offsetXArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    auto offsetYArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    auto hasOptionsArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    auto hasOffsetArg = runtimeCallInfo->GetCallArgRef(NUM_6);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    std::optional<std::string> text;
    if (valueArg->IsString(vm)) {
        text = valueArg->ToString(vm)->ToString(vm);
    }
    int32_t align = ALIGNMENT_TOP_LEFT;
    auto hasAlign = ArkTSUtils::ParseJsInteger(vm, alignArg, align);
    std::optional<CalcDimension> offsetX = CalcDimension(0);
    std::optional<CalcDimension> offsetY = CalcDimension(0);
    CalcDimension dimensionX;
    if (ArkTSUtils::ParseJsDimensionVp(vm, offsetXArg, dimensionX, false)) {
        offsetX = dimensionX;
    }
    CalcDimension dimensionY;
    if (ArkTSUtils::ParseJsDimensionVp(vm, offsetYArg, dimensionY, false)) {
        offsetY = dimensionY;
    }
    auto hasOptions = (hasOptionsArg->IsBoolean()) ? hasOptionsArg->ToBoolean(vm)->Value(): false;
    auto hasOffset = (hasOffsetArg->IsBoolean()) ? hasOffsetArg->ToBoolean(vm)->Value(): false;
    std::vector<ArkUI_Float32> options;
    options.push_back(static_cast<ArkUI_Float32>(hasAlign));
    options.push_back(static_cast<ArkUI_Float32>(align));
    options.push_back(static_cast<ArkUI_Float32>(offsetX.has_value()));
    options.push_back(static_cast<ArkUI_Float32>(offsetX.value().Value()));
    options.push_back(static_cast<ArkUI_Float32>(offsetX.value().Unit()));
    options.push_back(static_cast<ArkUI_Float32>(offsetY.has_value()));
    options.push_back(static_cast<ArkUI_Float32>(offsetY.value().Value()));
    options.push_back(static_cast<ArkUI_Float32>(offsetY.value().Unit()));
    options.push_back(static_cast<ArkUI_Float32>(hasOptions));
    options.push_back(static_cast<ArkUI_Float32>(hasOffset));
    auto textPtr = (text.has_value()) ? text.value().c_str() : nullptr;
    GetArkUINodeModifiers()->getCommonModifier()->setOverlay(nativeNode, textPtr, options.data(), options.size());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetOverlay(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetOverlay(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetBorderImage(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto argsNumber = runtimeCallInfo->GetArgsNumber();
    if (IsArgsUndefined(runtimeCallInfo, NUM_1, argsNumber - NUM_1)) {
        return panda::JSValueRef::Undefined(vm);
    }
    std::string src;
    std::vector<ArkUIStringAndFloat> options;
    uint8_t bitsets = 0;
    uint32_t offset = NUM_1;
    std::vector<std::optional<CalcDimension>> sliceDimensions;
    ParseBorderImageSlice(runtimeCallInfo, offset, sliceDimensions, bitsets); // use 4 args
    PushDimensionsToVector(options, sliceDimensions);
    ParseBorderImageRepeat(runtimeCallInfo, offset, options, bitsets); // use 1 args
    if (!ParseBorderImageSource(runtimeCallInfo, offset, nativeNode, src, bitsets)) { // use 5 args
        return panda::JSValueRef::Undefined(vm);
    }
    std::vector<std::optional<CalcDimension>> widthDimensions;
    ParseBorderImageWidth(runtimeCallInfo, offset, widthDimensions, bitsets); // use 4 args
    PushDimensionsToVector(options, widthDimensions);
    std::vector<std::optional<CalcDimension>> outsetDimensions;
    ParseBorderImageOutset(runtimeCallInfo, offset, outsetDimensions, bitsets); // use 4 args
    PushDimensionsToVector(options, outsetDimensions);
    ParseBorderImageFill(runtimeCallInfo, offset, options); // use 1 args
    options.push_back(ArkUIStringAndFloat { static_cast<ArkUI_Float32>(bitsets), nullptr });
    GetArkUINodeModifiers()->getCommonModifier()->setBorderImage(nativeNode,
        src.c_str(), options.data(), options.size());
    ResetCalcDimensions(sliceDimensions);
    ResetCalcDimensions(widthDimensions);
    ResetCalcDimensions(outsetDimensions);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetBorderImage(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetBorderImage(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetForegroundBlurStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto blurStyleArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto colorModeArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    auto adaptiveColorArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    auto scaleArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    auto blurOptionsArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    auto disableSystemAdaptationArg = runtimeCallInfo->GetCallArgRef(NUM_6);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    int32_t blurStyle = -1;
    if (blurStyleArg->IsNumber()) {
        blurStyle = blurStyleArg->Int32Value(vm);
    }
    bool isHasOptions = !(colorModeArg->IsUndefined() && adaptiveColorArg->IsUndefined() && scaleArg->IsUndefined() &&
                          blurOptionsArg->IsUndefined());
    int32_t colorMode = static_cast<int32_t>(ThemeColorMode::SYSTEM);
    int32_t adaptiveColor = static_cast<int32_t>(AdaptiveColor::DEFAULT);
    double scale = 1.0;
    BlurOption blurOption;
    if (isHasOptions) {
        ArkTSUtils::ParseJsInt32(vm, colorModeArg, colorMode);
        ArkTSUtils::ParseJsInt32(vm, adaptiveColorArg, adaptiveColor);
        if (scaleArg->IsNumber()) {
            scale = scaleArg->ToNumber(vm)->Value();
        }
        if (blurOptionsArg->IsArray(vm)) {
            ParseBlurOption(vm, blurOptionsArg, blurOption);
        }
    }
    int32_t intArray[NUM_3];
    intArray[NUM_0] = blurStyle;
    intArray[NUM_1] = colorMode;
    intArray[NUM_2] = adaptiveColor;
    bool disableSystemAdaptation = false;
    if (disableSystemAdaptationArg->IsBoolean()) {
        disableSystemAdaptation = disableSystemAdaptationArg->ToBoolean(vm)->Value();
    }
    GetArkUINodeModifiers()->getCommonModifier()->setForegroundBlurStyle(nativeNode, &intArray, scale,
        blurOption.grayscale.data(), blurOption.grayscale.size(), disableSystemAdaptation);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetForegroundBlurStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetForegroundBlurStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetLinearGradientBlur(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto blurRadiusArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto fractionStopsArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    auto directionArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    double blurRadius = 0.0;
    ParseJsDouble(vm, blurRadiusArg, blurRadius);
    auto direction = static_cast<int32_t>(GradientDirection::BOTTOM);
    if (directionArg->IsInt()) {
        direction = directionArg->Int32Value(vm);
    }
    std::vector<ArkUI_Float32> fractionStops;
    if (fractionStopsArg->IsArray(vm)) {
        auto array = panda::Local<panda::ArrayRef>(fractionStopsArg);
        auto length = array->Length(vm);
        for (uint32_t index = 0; index < length; index++) {
            auto fractionStop = panda::ArrayRef::GetValueAt(vm, array, index);
            ArkUI_Float32 first = 0.0;
            ArkUI_Float32 second = 0.0;
            if (!ParseJsDoublePair(vm, fractionStop, first, second)) {
                continue;
            }
            fractionStops.push_back(first);
            fractionStops.push_back(second);
        }
    }
    GetArkUINodeModifiers()->getCommonModifier()->setLinearGradientBlur(nativeNode, blurRadius, fractionStops.data(),
        fractionStops.size(), direction);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetLinearGradientBlur(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetLinearGradientBlur(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void SetBackgroundBlurStyleParam(ArkUIRuntimeCallInfo* runtimeCallInfo, bool& isValidColor, Color& inactiveColor,
    int32_t& policy, int32_t& blurType, ArkUINodeHandle nativeNode, RefPtr<ResourceObject>& resourceObject)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    auto policyArg = runtimeCallInfo->GetCallArgRef(NUM_6);
    auto inactiveColorArg = runtimeCallInfo->GetCallArgRef(NUM_7);
    auto typeArg = runtimeCallInfo->GetCallArgRef(NUM_8);

    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (ArkTSUtils::ParseJsColor(vm, inactiveColorArg, inactiveColor, resourceObject, nodeInfo)) {
        isValidColor = true;
    }
    ArkTSUtils::ParseJsInt32(vm, policyArg, policy);
    if (policy < static_cast<int32_t>(BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE) ||
        policy > static_cast<int32_t>(BlurStyleActivePolicy::ALWAYS_INACTIVE)) {
        policy = static_cast<int32_t>(BlurStyleActivePolicy::ALWAYS_ACTIVE);
    }
    ArkTSUtils::ParseJsInt32(vm, typeArg, blurType);
    if (blurType < static_cast<int32_t>(BlurType::WITHIN_WINDOW) ||
        blurType > static_cast<int32_t>(BlurType::BEHIND_WINDOW)) {
        blurType = static_cast<int32_t>(BlurType::WITHIN_WINDOW);
    }
}

void ParseBackgroundBlurStyleParams(ArkUIRuntimeCallInfo *runtimeCallInfo, int32_t& colorMode, int32_t& adaptiveColor,
    double& scale, BlurOption& blurOption)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    auto colorModeArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    auto adaptiveColorArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    auto scaleArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    auto blurOptionsArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    bool isHasOptions = !(colorModeArg->IsUndefined() && adaptiveColorArg->IsUndefined() && scaleArg->IsUndefined() &&
                          blurOptionsArg->IsUndefined());
    if (isHasOptions) {
        colorMode = static_cast<int32_t>(ThemeColorMode::SYSTEM);
        ArkTSUtils::ParseJsInt32(vm, colorModeArg, colorMode);
        adaptiveColor = static_cast<int32_t>(AdaptiveColor::DEFAULT);
        ArkTSUtils::ParseJsInt32(vm, adaptiveColorArg, adaptiveColor);
        scale = 1.0;
        if (scaleArg->IsNumber()) {
            scale = scaleArg->ToNumber(vm)->Value();
        }
        if (blurOptionsArg->IsArray(vm)) {
            ParseBlurOption(vm, blurOptionsArg, blurOption);
        }
    }
}

ArkUINativeModuleValue CommonBridge::SetBackgroundBlurStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto blurStyleArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto disableSystemAdaptationArg = runtimeCallInfo->GetCallArgRef(NUM_9);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    int32_t blurStyle = -1;
    if (blurStyleArg->IsNumber()) {
        blurStyle = blurStyleArg->Int32Value(vm);
    }
    int32_t colorMode = -1;
    int32_t adaptiveColor = -1;
    double scale = -1.0;
    BlurOption blurOption;
    ParseBackgroundBlurStyleParams(runtimeCallInfo, colorMode, adaptiveColor, scale, blurOption);
    bool isValidColor = false;
    Color inactiveColor = Color::TRANSPARENT;
    auto policy = static_cast<int32_t>(BlurStyleActivePolicy::ALWAYS_ACTIVE);
    auto blurType = static_cast<int32_t>(BlurType::WITHIN_WINDOW);
    RefPtr<ResourceObject> inactiveColorResObj;
    SetBackgroundBlurStyleParam(
        runtimeCallInfo, isValidColor, inactiveColor, policy, blurType, nativeNode, inactiveColorResObj);
    int32_t intArray[NUM_5];
    intArray[NUM_0] = blurStyle;
    intArray[NUM_1] = colorMode;
    intArray[NUM_2] = adaptiveColor;
    intArray[NUM_3] = policy;
    intArray[NUM_4] = blurType;
    bool disableSystemAdaptation = false;
    if (disableSystemAdaptationArg->IsBoolean()) {
        disableSystemAdaptation = disableSystemAdaptationArg->ToBoolean(vm)->Value();
    }
    auto inactiveColorRawPtr = AceType::RawPtr(inactiveColorResObj);
    GetArkUINodeModifiers()->getCommonModifier()->setBackgroundBlurStyle(
        nativeNode, &intArray, scale, blurOption.grayscale.data(), blurOption.grayscale.size(),
        isValidColor, inactiveColor.GetValue(), disableSystemAdaptation, inactiveColorRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetBackgroundBlurStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetBackgroundBlurStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetBorder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    std::vector<ArkUI_Float32> options;
    std::vector<RefPtr<ResourceObject>> resObj;
    ParseOuterBorderWidth(runtimeCallInfo, vm, options, resObj);         // Border Width args start index from 1
    ParseOuterBorderRadius(runtimeCallInfo, vm, options, NUM_9, resObj); // Border Radius args start index

    std::vector<uint32_t> colorAndStyleOptions;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    ParseOuterBorderColor(runtimeCallInfo, vm, colorAndStyleOptions, NUM_5, resObj, nodeInfo);  // Border Color args start index
    ParseOuterBorderStyle(runtimeCallInfo, vm, colorAndStyleOptions, NUM_13); // Border Style args start index

    auto rawPtr = static_cast<void*>(&resObj);
    GetArkUINodeModifiers()->getCommonModifier()->setBorder(nativeNode, options.data(), options.size(),
        colorAndStyleOptions.data(), colorAndStyleOptions.size(), false, false, false, rawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetLocalizedBorder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::NativePointerRef::New(vm, nullptr));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    std::vector<ArkUI_Float32> options;
    std::vector<RefPtr<ResourceObject>> resObj;
    ParseOuterBorderWidth(runtimeCallInfo, vm, options, resObj, true);         // Border Width args start index from 1
    ParseOuterBorderRadius(runtimeCallInfo, vm, options, NUM_9, resObj, true); // Border Radius args start index

    std::vector<uint32_t> colorAndStyleOptions;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    ParseOuterBorderColor(runtimeCallInfo, vm, colorAndStyleOptions, NUM_5, resObj, nodeInfo, true);  // Border Color args start index
    ParseOuterBorderStyle(runtimeCallInfo, vm, colorAndStyleOptions, NUM_13); // Border Style args start index

    int32_t isLocalizedBorderWidth = 0;
    int32_t isLocalizedBorderColor = 0;
    int32_t isLocalizedBorderRadius = 0;
    ParseLocalizedBorder(runtimeCallInfo, isLocalizedBorderWidth, isLocalizedBorderColor, isLocalizedBorderRadius);

    auto rawPtr = static_cast<void*>(&resObj);
    GetArkUINodeModifiers()->getCommonModifier()->setBorder(nativeNode, options.data(), options.size(),
        colorAndStyleOptions.data(), colorAndStyleOptions.size(), isLocalizedBorderWidth, isLocalizedBorderColor,
        isLocalizedBorderRadius, rawPtr);
    return panda::JSValueRef::Undefined(vm);
}

void CommonBridge::ParseLocalizedBorder(ArkUIRuntimeCallInfo* runtimeCallInfo, int& isLocalizedBorderWidth,
    int& isLocalizedBorderColor, int& isLocalizedBorderRadius)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    Local<JSValueRef> isLocalizedBorderWidthArg =
        runtimeCallInfo->GetCallArgRef(33); // 33: index of is LocalizedBorderWidth or not
    Local<JSValueRef> isLocalizedBorderColorArg =
        runtimeCallInfo->GetCallArgRef(34); // 34: index of is LocalizedBorderColor or not
    Local<JSValueRef> isLocalizedBorderRadiusArg =
        runtimeCallInfo->GetCallArgRef(35); // 35: index of is LocalizedBorderRadius or not
    isLocalizedBorderWidth =
        (isLocalizedBorderWidthArg->IsBoolean()) ? isLocalizedBorderWidthArg->ToBoolean(vm)->Value() : false;
    isLocalizedBorderColor =
        (isLocalizedBorderColorArg->IsBoolean()) ? isLocalizedBorderColorArg->ToBoolean(vm)->Value() : false;
    isLocalizedBorderRadius =
        (isLocalizedBorderRadiusArg->IsBoolean()) ? isLocalizedBorderRadiusArg->ToBoolean(vm)->Value() : false;
}

ArkUINativeModuleValue CommonBridge::SetBorderWithDashParams(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    int32_t isLocalizedBorderWidth = 0;
    int32_t isLocalizedBorderColor = 0;
    int32_t isLocalizedBorderRadius = 0;
    ParseLocalizedBorder(runtimeCallInfo, isLocalizedBorderWidth, isLocalizedBorderColor, isLocalizedBorderRadius);
    if (isLocalizedBorderWidth || isLocalizedBorderColor || isLocalizedBorderRadius) {
        CommonBridge::SetLocalizedBorder(runtimeCallInfo);
    } else {
        CommonBridge::SetBorder(runtimeCallInfo);
    }

    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    std::vector<ArkUI_Float32> dashOptions;
    std::vector<RefPtr<ResourceObject>> resObj;
    ParseOuterBorderDashParam(runtimeCallInfo, vm, dashOptions, 17, resObj); // Border DashGap args start index from 17
    Local<JSValueRef> startDashGap = runtimeCallInfo->GetCallArgRef(36); // Border DashGap args start index from 36
    Local<JSValueRef> endDashGap = runtimeCallInfo->GetCallArgRef(37); // Border DashGap args end index from 37
    std::optional<CalcDimension> startDashGapDim;
    std::optional<CalcDimension> endDashGapDim;
    ArkTSUtils::ParseOuterBorderForDashParams(vm, startDashGap, startDashGapDim);
    ArkTSUtils::ParseOuterBorderForDashParams(vm, endDashGap, endDashGapDim);
    ArkTSUtils::PushOuterBorderDimensionVector(startDashGapDim, dashOptions);
    ArkTSUtils::PushOuterBorderDimensionVector(endDashGapDim, dashOptions);

    ParseOuterBorderDashParam(runtimeCallInfo, vm, dashOptions, 21, resObj); // Border DashWidth args start index from 21
    Local<JSValueRef> startDashWidth = runtimeCallInfo->GetCallArgRef(38); // Border DashWidth args start index from 38
    Local<JSValueRef> endDashWidth = runtimeCallInfo->GetCallArgRef(39); // Border DashWidth args end index from 39
    std::optional<CalcDimension> startDashWidthDim;
    std::optional<CalcDimension> endDashWidthDim;
    ArkTSUtils::ParseOuterBorderForDashParams(vm, startDashWidth, startDashWidthDim);
    ArkTSUtils::ParseOuterBorderForDashParams(vm, endDashWidth, endDashWidthDim);
    ArkTSUtils::PushOuterBorderDimensionVector(startDashWidthDim, dashOptions);
    ArkTSUtils::PushOuterBorderDimensionVector(endDashWidthDim, dashOptions);

    auto rawPtr = static_cast<void*>(&resObj);
    GetArkUINodeModifiers()->getCommonModifier()->setBorderDashParams(nativeNode, dashOptions.data(),
        dashOptions.size(), rawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetBorder(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetBorder(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetBackgroundImagePosition(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> xArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> yArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    double valueX = 0.0;
    double valueY = 0.0;
    DimensionUnit typeX = DimensionUnit::PX;
    DimensionUnit typeY = DimensionUnit::PX;
    bool isAlign = false;
    RefPtr<ResourceObject> resObjX;
    RefPtr<ResourceObject> resObjY;

    if (secondArg->IsNumber()) {
        int32_t align = secondArg->ToNumber(vm)->Value();
        ParseBackgroundImagePositionAlign(align, valueX, valueY, typeX, typeY);
        isAlign = true;
    } else {
        CalcDimension x(0, DimensionUnit::VP);
        CalcDimension y(0, DimensionUnit::VP);
        ArkTSUtils::ParseJsDimensionVp(vm, xArg, x, resObjX);
        ArkTSUtils::ParseJsDimensionVp(vm, yArg, y, resObjY);
        valueX = x.ConvertToPx();
        valueY = y.ConvertToPx();
        if (x.Unit() == DimensionUnit::PERCENT) {
            valueX = x.Value();
            typeX = DimensionUnit::PERCENT;
        }
        if (y.Unit() == DimensionUnit::PERCENT) {
            valueY = y.Value();
            typeY = DimensionUnit::PERCENT;
        }
    }

    ArkUI_Float32 values[SIZE_OF_TWO];
    int32_t types[SIZE_OF_TWO];
    values[NUM_0] = static_cast<ArkUI_Float32>(valueX);
    types[NUM_0] = static_cast<int32_t>(typeX);
    values[NUM_1] = static_cast<ArkUI_Float32>(valueY);
    types[NUM_1] = static_cast<int32_t>(typeY);

    auto bgImageXRawPtr = AceType::RawPtr(resObjX);
    auto bgImageYRawPtr = AceType::RawPtr(resObjY);
    GetArkUINodeModifiers()->getCommonModifier()->setBackgroundImagePosition(nativeNode, values, types, isAlign,
        SIZE_OF_TWO, bgImageXRawPtr, bgImageYRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetBackgroundImagePosition(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetBackgroundImagePosition(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetBackgroundImageResizable(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    std::vector<ArkUIStringAndFloat> options;
    std::vector<std::optional<CalcDimension>> sliceDimensions;
    std::vector<RefPtr<ResourceObject>> bgImageResizableResObjs;
    ParseResizableCalcDimensions(
        runtimeCallInfo, NUM_1, NUM_4, sliceDimensions, CalcDimension(0.0), bgImageResizableResObjs);
    PushDimensionsToVector(options, sliceDimensions);
    GetArkUINodeModifiers()->getCommonModifier()->setBackgroundImageResizable(nativeNode, options.data(),
        static_cast<ArkUI_Int32>(options.size()), static_cast<void*>(&bgImageResizableResObjs));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetBackgroundImageResizable(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetBackgroundImageResizable(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetBackgroundImageSize(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> imageSizeArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> widthArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> heightArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    OHOS::Ace::BackgroundImageSizeType typeWidth = OHOS::Ace::BackgroundImageSizeType::AUTO;
    double valueWidth = 0.0;
    OHOS::Ace::BackgroundImageSizeType typeHeight = OHOS::Ace::BackgroundImageSizeType::AUTO;
    double valueHeight = 0.0;
    RefPtr<ResourceObject> resObjWidth;
    RefPtr<ResourceObject> resObjHeight;

    if (imageSizeArg->IsNumber()) {
        auto sizeType = imageSizeArg->ToNumber(vm)->Value();
        if (sizeType < static_cast<uint32_t>(BackgroundImageSizeType::CONTAIN) ||
            sizeType > static_cast<uint32_t>(BackgroundImageSizeType::FILL)) {
            sizeType = static_cast<uint32_t>(BackgroundImageSizeType::AUTO);
        }
        typeWidth = static_cast<OHOS::Ace::BackgroundImageSizeType>(sizeType);
        typeHeight = static_cast<OHOS::Ace::BackgroundImageSizeType>(sizeType);
    } else {
        CalcDimension width;
        CalcDimension height;
        ArkTSUtils::ParseJsDimensionVp(vm, widthArg, width, resObjWidth);
        ArkTSUtils::ParseJsDimensionVp(vm, heightArg, height, resObjHeight);

        valueWidth = width.ConvertToPx();
        valueHeight = height.ConvertToPx();
        typeWidth = BackgroundImageSizeType::LENGTH;
        typeHeight = BackgroundImageSizeType::LENGTH;
        if (width.Unit() == DimensionUnit::PERCENT) {
            typeWidth = BackgroundImageSizeType::PERCENT;
            valueWidth = width.Value() * FULL_DIMENSION;
        }
        if (height.Unit() == DimensionUnit::PERCENT) {
            typeHeight = BackgroundImageSizeType::PERCENT;
            valueHeight = height.Value() * FULL_DIMENSION;
        }
    }
    auto bgImageSizeWidthRawPtr = AceType::RawPtr(resObjWidth);
    auto bgImageSizeHeightRawPtr = AceType::RawPtr(resObjHeight);
    GetArkUINodeModifiers()->getCommonModifier()->setBackgroundImageSize(nativeNode, valueWidth, valueHeight,
        static_cast<int32_t>(typeWidth), static_cast<int32_t>(typeHeight), bgImageSizeWidthRawPtr,
        bgImageSizeHeightRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetBackgroundImageSize(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetBackgroundImageSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

bool ParseJsBackgroundImageOptions(
    const EcmaVM* vm, const Local<JSValueRef>& value, int32_t& repeatIndex, bool& syncMode)
{
    if (!value->IsObject(vm)) {
        return false;
    }
    auto jsObj = value->ToObject(vm);
    auto repeat = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "repeat"));
    if (repeat->IsNumber()) {
        repeatIndex = repeat->ToNumber(vm)->Value();
    }
    auto syncLoad = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "syncLoad"));
    if (syncLoad->IsBoolean()) {
        syncMode = syncLoad->ToBoolean(vm)->Value();
    }
    return true;
}

ArkUINativeModuleValue CommonBridge::SetBackgroundImage(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> srcArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> repeatArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    std::string src;
    std::string bundle;
    std::string module;
    int32_t repeatIndex = 0;
    bool syncMode = false;
    RefPtr<PixelMap> pixmap = nullptr;
    if (repeatArg->IsNumber()) {
        repeatIndex = repeatArg->ToNumber(vm)->Value();
    }
    if (ParseJsBackgroundImageOptions(vm, repeatArg, repeatIndex, syncMode)) {
        GetArkUINodeModifiers()->getCommonModifier()->setBackgroundImageSyncMode(nativeNode, syncMode);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetBackgroundImageSyncMode(nativeNode);
    }
    RefPtr<ResourceObject> backgroundImageResObj;
    auto bgImageRawPtr = AceType::RawPtr(backgroundImageResObj);
    if (srcArg->IsString(vm)) {
        src = srcArg->ToString(vm)->ToString(vm);
        GetArkUINodeModifiers()->getCommonModifier()->setBackgroundImage(
            nativeNode, src.c_str(), bundle.c_str(), module.c_str(), repeatIndex, bgImageRawPtr);
    } else if (ArkTSUtils::ParseJsMedia(vm, srcArg, src, backgroundImageResObj)) {
        ArkTSUtils::GetJsMediaBundleInfo(vm, srcArg, bundle, module);
        bgImageRawPtr = AceType::RawPtr(backgroundImageResObj);
        GetArkUINodeModifiers()->getCommonModifier()->setBackgroundImage(
            nativeNode, src.c_str(), bundle.c_str(), module.c_str(), repeatIndex, bgImageRawPtr);
    } else {
#if defined(PIXEL_MAP_SUPPORTED)
        if (ArkTSUtils::IsDrawable(vm, srcArg)) {
            pixmap = ArkTSUtils::GetDrawablePixmap(vm, srcArg);
        } else {
            pixmap = ArkTSUtils::CreatePixelMapFromNapiValue(vm, srcArg);
        }
#endif
        if (pixmap) {
            auto pixelMapSharedPtr = pixmap->GetPixelMapSharedPtr();
            GetArkUINodeModifiers()->getCommonModifier()->setBackgroundImagePixelMapByPixelMapPtr(
                nativeNode, &pixelMapSharedPtr, repeatIndex);
        } else {
            GetArkUINodeModifiers()->getCommonModifier()->resetBackgroundImage(nativeNode);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetBackgroundImage(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetBackgroundImageSyncMode(nativeNode);
    GetArkUINodeModifiers()->getCommonModifier()->resetBackgroundImage(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetTranslate(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> xArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> yArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> zArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (!xArg->IsNumber() && !xArg->IsString(vm) && !yArg->IsNumber() && !yArg->IsString(vm) && !zArg->IsNumber() &&
        !zArg->IsString(vm)) {
        GetArkUINodeModifiers()->getCommonModifier()->resetTranslate(nativeNode);
    } else {
        auto translateX = CalcDimension(0.0);
        auto translateY = CalcDimension(0.0);
        auto translateZ = CalcDimension(0.0);
        bool hasX = ParseAxisDimensionVp(vm, xArg, translateX, true);
        bool hasY = ParseAxisDimensionVp(vm, yArg, translateY, true);
        bool hasZ = ParseAxisDimensionVp(vm, zArg, translateZ, true);
        if (hasX || hasY || hasZ) {
            uint32_t size = SIZE_OF_THREE;
            ArkUI_Float32 values[size];
            int units[size];

            values[NUM_0] = static_cast<ArkUI_Float32>(translateX.Value());
            units[NUM_0] = static_cast<int>(translateX.Unit());
            values[NUM_1] = static_cast<ArkUI_Float32>(translateY.Value());
            units[NUM_1] = static_cast<int>(translateY.Unit());
            values[NUM_2] = static_cast<ArkUI_Float32>(translateZ.Value());
            units[NUM_2] = static_cast<int>(translateZ.Unit());
            GetArkUINodeModifiers()->getCommonModifier()->setTranslate(nativeNode, values, units, size);
        } else {
            GetArkUINodeModifiers()->getCommonModifier()->resetTranslate(nativeNode);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetTranslate(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetTranslate(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetScale(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> xArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> yArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> zArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> centerXArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> centerYArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (xArg->IsNumber() || yArg->IsNumber() || zArg->IsNumber()) {
        auto scaleX = 1.0f;
        auto scaleY = 1.0f;
        auto scaleZ = 1.0f;

        CalcDimension centerX = 0.5_pct;
        CalcDimension centerY = 0.5_pct;

        if (xArg->IsNumber()) {
            scaleX = xArg->ToNumber(vm)->Value();
        }
        if (yArg->IsNumber()) {
            scaleY = yArg->ToNumber(vm)->Value();
        }
        if (zArg->IsNumber()) {
            scaleZ = zArg->ToNumber(vm)->Value();
        }
        if (centerXArg->IsNumber() || centerXArg->IsString(vm)) {
            ParseAxisDimensionVp(vm, centerXArg, centerX, true);
        }
        if (centerYArg->IsNumber() || centerYArg->IsString(vm)) {
            ParseAxisDimensionVp(vm, centerYArg, centerY, true);
        }

        ArkUI_Float32 values[SIZE_OF_FIVE];
        int units[SIZE_OF_TWO];

        values[NUM_0] = static_cast<ArkUI_Float32>(scaleX);
        values[NUM_1] = static_cast<ArkUI_Float32>(scaleY);
        values[NUM_2] = static_cast<ArkUI_Float32>(scaleZ);
        values[NUM_3] = static_cast<ArkUI_Float32>(centerX.Value());
        values[NUM_4] = static_cast<ArkUI_Float32>(centerY.Value());
        units[NUM_0] = static_cast<int>(centerX.Unit());
        units[NUM_1] = static_cast<int>(centerY.Unit());
        GetArkUINodeModifiers()->getCommonModifier()->setScale(nativeNode, values, SIZE_OF_FIVE, units, SIZE_OF_TWO);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetScale(nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetScale(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetScale(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetRotateAngle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    ArkUI_Float32 values[SIZE_OF_SEVEN];
    int units[SIZE_OF_THREE];

    if (ParseRotateAngle(runtimeCallInfo, values, units, SIZE_OF_SEVEN, SIZE_OF_THREE)) {
        GetArkUINodeModifiers()->getCommonModifier()->setRotateAngle(
            nativeNode, values, SIZE_OF_SEVEN, units, SIZE_OF_THREE);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetRotateAngle(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetRotateAngle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetRotateAngle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetRotate(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    ArkUI_Float32 values[SIZE_OF_EIGHT];
    int units[SIZE_OF_THREE];

    if (ParseRotate(runtimeCallInfo, values, units, SIZE_OF_EIGHT, SIZE_OF_THREE)) {
        GetArkUINodeModifiers()->getCommonModifier()->setRotate(
            nativeNode, values, SIZE_OF_EIGHT, units, SIZE_OF_THREE);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetRotate(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetRotate(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetRotate(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetGeometryTransition(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> idArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> followArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> hierarchyStrategyArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (idArg->IsUndefined() || idArg->IsNull() || !idArg->IsString(vm)) {
        GetArkUINodeModifiers()->getCommonModifier()->resetGeometryTransition(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    std::string id = idArg->ToString(vm)->ToString(vm);
    ArkUIGeometryTransitionOptions options = {false, static_cast<int32_t>(TransitionHierarchyStrategy::ADAPTIVE)};
    if (followArg->IsBoolean()) {
        options.follow = followArg->ToBoolean(vm)->Value();
    }
    if (hierarchyStrategyArg->IsInt()) {
        options.hierarchyStrategy = hierarchyStrategyArg->Int32Value(vm);
        if (options.hierarchyStrategy < static_cast<int32_t>(TransitionHierarchyStrategy::NONE) ||
            options.hierarchyStrategy > static_cast<int32_t>(TransitionHierarchyStrategy::ADAPTIVE)) {
            options.hierarchyStrategy = static_cast<int32_t>(TransitionHierarchyStrategy::ADAPTIVE);
        }
    }
    GetArkUINodeModifiers()->getCommonModifier()->setGeometryTransition(nativeNode, id.c_str(), &options);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetGeometryTransition(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetGeometryTransition(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetBindMenu(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Framework::JSCallbackInfo info = Framework::JSCallbackInfo(runtimeCallInfo);
    NG::MenuParam menuParam;
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        menuParam.placement = Placement::BOTTOM_LEFT;
    }
    size_t builderIndex = NUM_1;
    JSViewPopups::GetMenuShowInSubwindow(menuParam);
    if (info.Length() > PARAMETER_LENGTH_SECOND) {
        auto jsVal = info[builderIndex];
        if (jsVal->IsBoolean()) {
            menuParam.isShow = jsVal->ToBoolean();
            menuParam.setShow = true;
            builderIndex = NUM_2;
            if (info.Length() > PARAMETER_LENGTH_THIRD) {
                JSViewPopups::ParseBindOptionParam(info, menuParam, builderIndex + 1);
            }
        } else if (jsVal->IsUndefined()) {
            menuParam.setShow = true;
            menuParam.isShow = false;
            builderIndex = NUM_2;
            if (info.Length() > PARAMETER_LENGTH_THIRD) {
                JSViewPopups::ParseBindOptionParam(info, menuParam, builderIndex + 1);
            }
        } else if (jsVal->IsObject()) {
            JSRef<JSObject> callbackObj = JSRef<JSObject>::Cast(jsVal);
            menuParam.onStateChange = JSViewPopups::ParseDoubleBindCallback(info, callbackObj, "$value");
            auto isShowObj = callbackObj->GetProperty(static_cast<int32_t>(ArkUIIndex::VALUE));
            if (isShowObj->IsBoolean()) {
                menuParam.isShow = isShowObj->ToBoolean();
                menuParam.setShow = true;
                builderIndex = NUM_2;
                if (info.Length() > PARAMETER_LENGTH_THIRD) {
                    JSViewPopups::ParseBindOptionParam(info, menuParam, builderIndex + 1);
                }
            } else {
                JSViewPopups::ParseBindOptionParam(info, menuParam, builderIndex + 1);
            }
        }
    }
    if (info[builderIndex]->IsArray()) {
        std::vector<NG::OptionParam> optionsParam = JSViewPopups::ParseBindOptionParam(info, builderIndex);
        ViewAbstractModel::GetInstance()->BindMenu(std::move(optionsParam), nullptr, menuParam);
    }
    return panda::JSValueRef::Undefined(vm);
}

bool ParseTipsMessage(
    ArkUIRuntimeCallInfo* runtimeCallInfo, const EcmaVM* vm, std::string& message, RefPtr<SpanString>& styledString)
{
    bool parseRuslut = false;
    Local<JSValueRef> messageArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (messageArg->IsString(vm)) {
        message = messageArg->ToString(vm)->ToString(vm);
        parseRuslut = true;
    } else if (messageArg->IsObject(vm)) {
        Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
        Framework::JSRef<Framework::JSVal> args = info[1];
        auto* spanString = Framework::JSRef<Framework::JSObject>::Cast(args)->Unwrap<Framework::JSSpanString>();
        if (!spanString) {
            ArkTSUtils::ParseJsString(vm, messageArg, message);
        } else {
            styledString = spanString->GetController();
        }
        parseRuslut = true;
    }
    return parseRuslut;
}

void ParseTipsParam(const RefPtr<PopupParam>& tipsParam, const ArkUIBindTipsOptionsTime& timeOptions,
    const ArkUIBindTipsOptionsArrow& arrowOptions)
{
    CHECK_NULL_VOID(tipsParam);
    tipsParam->SetShowInSubWindow(true);
    tipsParam->SetAppearingTime(timeOptions.appearingTime);
    tipsParam->SetDisappearingTime(timeOptions.disappearingTime);
    tipsParam->SetAppearingTimeWithContinuousOperation(timeOptions.appearingTimeWithContinuousOperation);
    tipsParam->SetDisappearingTimeWithContinuousOperation(timeOptions.disappearingTimeWithContinuousOperation);
    tipsParam->SetEnableArrow(arrowOptions.enableArrow);
    if (arrowOptions.arrowPointPosition && arrowOptions.enableArrow) {
        CalcDimension offset;
        char* pEnd = nullptr;
        std::strtod(arrowOptions.arrowPointPosition, &pEnd);
        if (pEnd != nullptr) {
            if (std::strcmp(pEnd, "Start") == 0) {
                offset = 0.0_pct; // 0.0_pct : The offset is 0%
            }
            if (std::strcmp(pEnd, "Center") == 0) {
                offset = 0.5_pct; // 0.5_pct : The offset is 50%
            }
            if (std::strcmp(pEnd, "End") == 0) {
                offset = 1.0_pct; // 1.0_pct : The offset is 100%
            }
            tipsParam->SetArrowOffset(offset);
        }
    }
    CalcDimension arrowWidth(arrowOptions.arrowWidthValue, static_cast<DimensionUnit>(arrowOptions.arrowWidthUnit));
    bool setArrowWidthError = true;
    if (arrowOptions.arrowWidthValue > 0 &&
        static_cast<DimensionUnit>(arrowOptions.arrowWidthUnit) != DimensionUnit::PERCENT) {
        tipsParam->SetArrowWidth(arrowWidth);
        setArrowWidthError = false;
    }
    tipsParam->SetErrorArrowWidth(setArrowWidthError);
    CalcDimension arrowHeight(arrowOptions.arrowHeightValue, static_cast<DimensionUnit>(arrowOptions.arrowHeightUnit));
    bool setArrowHeightError = true;
    if (arrowOptions.arrowHeightValue > 0 &&
        static_cast<DimensionUnit>(arrowOptions.arrowHeightUnit) != DimensionUnit::PERCENT) {
        tipsParam->SetArrowHeight(arrowHeight);
        setArrowHeightError = false;
    }
    tipsParam->SetErrorArrowHeight(setArrowHeightError);
    tipsParam->SetBlockEvent(false);
    tipsParam->SetTipsFlag(true);
    tipsParam->SetAnchorType(static_cast<TipsAnchorType>(arrowOptions.showAtAnchor));
}

ArkUINativeModuleValue CommonBridge::SetBindTips(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> appearingTimeArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> disappearingTimeArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> appearingTimeWithContinuousOperationArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> disappearingTimeWithContinuousOperationArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    Local<JSValueRef> enableArrowArg = runtimeCallInfo->GetCallArgRef(NUM_6);
    Local<JSValueRef> arrowPointPositionArg = runtimeCallInfo->GetCallArgRef(NUM_7);
    Local<JSValueRef> arrowWidthArg = runtimeCallInfo->GetCallArgRef(NUM_8);
    Local<JSValueRef> arrowHeightArg = runtimeCallInfo->GetCallArgRef(NUM_9);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    std::string message;
    RefPtr<SpanString> styledString;
    if (!ParseTipsMessage(runtimeCallInfo, vm, message, styledString)) {
        return panda::JSValueRef::Undefined(vm);
    }
    ArkUIBindTipsOptionsTime timeOptions {
        .appearingTime = 700.0f,                         // 700.0f : Default appearing time
        .disappearingTime = 300.0f,                      // 300.0f : Default disappearing time
        .appearingTimeWithContinuousOperation = 300.0f,  // 300.0f : Default continous appearing time
        .disappearingTimeWithContinuousOperation = 0.0f  // 0.0f : Default continous disappearing time
    };
    ParseTipsOptionsTime(vm, timeOptions, appearingTimeArg, timeOptions.appearingTime);
    ParseTipsOptionsTime(vm, timeOptions, disappearingTimeArg, timeOptions.disappearingTime);
    ParseTipsOptionsTime(
        vm, timeOptions, appearingTimeWithContinuousOperationArg, timeOptions.appearingTimeWithContinuousOperation);
    ParseTipsOptionsTime(vm, timeOptions, disappearingTimeWithContinuousOperationArg,
        timeOptions.disappearingTimeWithContinuousOperation);
    ArkUIBindTipsOptionsArrow arrowOptions;
    arrowOptions.enableArrow = (enableArrowArg->IsBoolean()) ? enableArrowArg->ToBoolean(vm)->Value() : true;
    std::string arrowPointPosition;
    if (arrowPointPositionArg->IsString(vm)) {
        arrowPointPosition = arrowPointPositionArg->ToString(vm)->ToString(vm);
        arrowOptions.arrowPointPosition = arrowPointPosition.c_str();
    }
    ParseTipsOptionsShowAtAnchor(vm, runtimeCallInfo->GetCallArgRef(NUM_10), arrowOptions);
    ParseTipsOptionsArrowSize(vm, arrowWidthArg, arrowOptions.arrowWidthValue, arrowOptions.arrowWidthUnit);
    ParseTipsOptionsArrowSize(vm, arrowHeightArg, arrowOptions.arrowHeightValue, arrowOptions.arrowHeightUnit);
    if (styledString) {
        auto tipsParam = AceType::MakeRefPtr<PopupParam>();
        ParseTipsParam(tipsParam, timeOptions, arrowOptions);
        ViewAbstract::BindTips(tipsParam, AceType::Claim(reinterpret_cast<FrameNode*>(nativeNode)), styledString);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->setBindTips(
            nativeNode, message.c_str(), timeOptions, arrowOptions);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetBindTips(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetBindTips(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetClip(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto *frameNode = reinterpret_cast<FrameNode *>(nativeNode);
    ViewAbstract::SetClipEdge(frameNode, false);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetClip(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto *frameNode = reinterpret_cast<FrameNode *>(nativeNode);

    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    if (info[NUM_1]->IsUndefined()) {
        ViewAbstract::SetClipEdge(frameNode, false);
        return panda::JSValueRef::Undefined(vm);
    }
    if (info[NUM_1]->IsObject()) {
        Framework::JSShapeAbstract *clipShape =
            Framework::JSRef<Framework::JSObject>::Cast(info[NUM_1])->Unwrap<Framework::JSShapeAbstract>();
        if (clipShape == nullptr) {
            return panda::JSValueRef::Undefined(vm);
        }
        ViewAbstractModelNG::RemoveResObj(frameNode, "clipShape");
        ViewAbstract::SetClipShape(frameNode, clipShape->GetBasicShape());
    } else if (info[NUM_1]->IsBoolean()) {
        ViewAbstract::SetClipEdge(frameNode, info[NUM_1]->ToBoolean());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetClipShape(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto *frameNode = reinterpret_cast<FrameNode *>(nativeNode);

    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    if (info[NUM_1]->IsObject()) {
        Framework::JSShapeAbstract *clipShape =
            Framework::JSRef<Framework::JSObject>::Cast(info[NUM_1])->Unwrap<Framework::JSShapeAbstract>();
        if (clipShape == nullptr) {
            return panda::JSValueRef::Undefined(vm);
        }
        ViewAbstractModelNG::RemoveResObj(frameNode, "clipShape");
        ViewAbstract::SetClipShape(frameNode, clipShape->GetBasicShape());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetClipShape(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto *frameNode = reinterpret_cast<FrameNode *>(nativeNode);
    ViewAbstract::SetClipEdge(frameNode, false);
    return panda::JSValueRef::Undefined(vm);
}

void SetMaskColorResObj(Framework::JSRef<Framework::JSVal>& jColor, Color& colorVal,
    RefPtr<ProgressMaskProperty>& progressMask)
{
    RefPtr<ResourceObject> colorResObj;
    auto parseJsColor = Framework::JSViewAbstract::ParseJsColor(jColor, colorVal, colorResObj);
    if (colorResObj) {
        progressMask->SetColor(colorVal);
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::ProgressMaskProperty& progressMask) {
            Color color;
            ResourceParseUtils::ParseResColor(resObj, color);
            progressMask.SetColor(color);
        };
        progressMask->AddResource("progressMask.color", colorResObj, std::move(updateFunc));
    } else if (parseJsColor) {
        progressMask->SetColor(colorVal);
    } else {
        auto theme = Framework::JSShapeAbstract::GetTheme<ProgressTheme>();
        progressMask->SetColor(theme->GetMaskColor());
        RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::ProgressMaskProperty& progressMask) {
            RefPtr<ProgressTheme> theme = GetTheme<ProgressTheme>();
            progressMask.SetColor(theme->GetMaskColor());
        };
        progressMask->AddResource("progressMask.color", resObj, std::move(updateFunc));
    }
}

void ParseJsMaskProperty(FrameNode* frameNode, const Framework::JSRef<Framework::JSObject>& paramObject)
{
    auto progressMask = AceType::MakeRefPtr<NG::ProgressMaskProperty>();
    Framework::JSRef<Framework::JSVal> jValue = paramObject->GetProperty("value");
    auto value = jValue->IsNumber() ? jValue->ToNumber<float>() : 0.0f;
    if (value < 0.0f) {
        value = 0.0f;
    }
    progressMask->SetValue(value);
    Framework::JSRef<Framework::JSVal> jTotal = paramObject->GetProperty("total");
    auto total = jTotal->IsNumber() ? jTotal->ToNumber<float>() : DEFAULT_PROGRESS_TOTAL;
    if (total < 0.0f) {
        total = DEFAULT_PROGRESS_TOTAL;
    }
    progressMask->SetMaxValue(total);
    Framework::JSRef<Framework::JSVal> jEnableBreathe = paramObject->GetProperty("breathe");
    if (jEnableBreathe->IsBoolean()) {
        progressMask->SetEnableBreathe(jEnableBreathe->ToBoolean());
    }
    Framework::JSRef<Framework::JSVal> jColor = paramObject->GetProperty("color");
    Color colorVal;
    if (!SystemProperties::ConfigChangePerform()) {
        if (Framework::JSViewAbstract::ParseJsColor(jColor, colorVal)) {
            progressMask->SetColor(colorVal);
        } else {
            auto theme = Framework::JSShapeAbstract::GetTheme<ProgressTheme>();
            progressMask->SetColor(theme->GetMaskColor());
        }
        ViewAbstract::SetProgressMask(frameNode, progressMask);
    } else {
        ViewAbstractModelNG::RemoveResObj(frameNode, "ProgressMask");
        SetMaskColorResObj(jColor, colorVal, progressMask);
        ViewAbstract::SetProgressMask(frameNode, progressMask);
    }
}

ArkUINativeModuleValue CommonBridge::SetPixelStretchEffect(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto topArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto rightArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    auto bottomArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    auto leftArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    std::vector<RefPtr<ResourceObject>> vectorResObj;
    CalcDimension left;
    ParseJsDimensionVpResObj(vm, leftArg, left, vectorResObj);
    CalcDimension right;
    ParseJsDimensionVpResObj(vm, rightArg, right, vectorResObj);
    CalcDimension top;
    ParseJsDimensionVpResObj(vm, topArg, top, vectorResObj);
    CalcDimension bottom;
    ParseJsDimensionVpResObj(vm, bottomArg, bottom, vectorResObj);
    auto rawPtr = static_cast<void*>(&vectorResObj);
    ArkUI_Float32 values[] = { static_cast<ArkUI_Float32>(left.Value()), static_cast<ArkUI_Float32>(top.Value()),
        static_cast<ArkUI_Float32>(right.Value()), static_cast<ArkUI_Float32>(bottom.Value()) };
    int units[] = { static_cast<int>(left.Unit()), static_cast<int>(top.Unit()), static_cast<int>(right.Unit()),
                    static_cast<int>(bottom.Unit()) };
    GetArkUINodeModifiers()->getCommonModifier()->setPixelStretchEffect(nativeNode, values, units,
        (sizeof(values) / sizeof(values[NUM_0])), rawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetPixelStretchEffect(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetPixelStretchEffect(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetLightUpEffect(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto radio = 1.0;
    if (secondArg->IsNumber()) {
        radio = secondArg->ToNumber(vm)->Value();
    }
    GetArkUINodeModifiers()->getCommonModifier()->setLightUpEffect(nativeNode, radio);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetLightUpEffect(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetLightUpEffect(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetSphericalEffect(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto radio = 0.0;
    if (secondArg->IsNumber()) {
        radio = secondArg->ToNumber(vm)->Value();
    }
    GetArkUINodeModifiers()->getCommonModifier()->setSphericalEffect(nativeNode, radio);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetSphericalEffect(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetSphericalEffect(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetRenderGroup(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto isRenderGroup = false;
    if (secondArg->IsBoolean()) {
        isRenderGroup = secondArg->ToBoolean(vm)->Value();
    }
    GetArkUINodeModifiers()->getCommonModifier()->setRenderGroup(nativeNode, isRenderGroup);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetRenderGroup(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetRenderGroup(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetRenderFit(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto fitModeArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto renderFit = static_cast<int32_t>(RenderFit::TOP_LEFT);
    if (fitModeArg->IsNumber()) {
        renderFit = fitModeArg->Int32Value(vm);
    }
    GetArkUINodeModifiers()->getCommonModifier()->setRenderFit(nativeNode, renderFit);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetRenderFit(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetRenderFit(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetUseEffect(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto useEffect = false;
    if (secondArg->IsBoolean()) {
        useEffect = secondArg->ToBoolean(vm)->Value();
    }
    auto effectTypeDefault = EffectType::DEFAULT;
    auto effectTypeParam = effectTypeDefault;
    auto effectTypeValue = static_cast<int32_t>(effectTypeDefault);

    if (thirdArg->IsNumber()) {
        effectTypeValue = thirdArg->Int32Value(vm);
        if (effectTypeValue >= static_cast<int32_t>(effectTypeDefault) &&
            effectTypeValue <= static_cast<int32_t>(EffectType::WINDOW_EFFECT)) {
            effectTypeParam = static_cast<EffectType>(effectTypeValue);
        }
    }
    auto effectType =  static_cast<ArkUI_Int32>(effectTypeParam);
    GetArkUINodeModifiers()->getCommonModifier()->setUseEffect(nativeNode, useEffect, effectType);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetUseEffect(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetUseEffect(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetForegroundColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto colorArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (colorArg->IsString(vm)) {
        std::string colorStr = colorArg->ToString(vm)->ToString(vm);
        colorStr.erase(std::remove(colorStr.begin(), colorStr.end(), ' '), colorStr.end());
        std::transform(colorStr.begin(), colorStr.end(), colorStr.begin(), ::tolower);
        if (colorStr.compare("invert") == 0) {
            auto strategy = static_cast<uint32_t>(ForegroundColorStrategy::INVERT);
            GetArkUINodeModifiers()->getCommonModifier()->setForegroundColor(nativeNode, false, strategy, nullptr);
            return panda::JSValueRef::Undefined(vm);
        }
    }
    Color foregroundColor = Color::TRANSPARENT;
    RefPtr<ResourceObject> colorResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    ArkTSUtils::ParseJsColorAlpha(vm, colorArg, foregroundColor, colorResObj, nodeInfo);
    auto fgColorRawPtr = AceType::RawPtr(colorResObj);
    GetArkUINodeModifiers()->getCommonModifier()->setForegroundColor(nativeNode, true, foregroundColor.GetValue(), fgColorRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetForegroundColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetForegroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetMotionPath(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto pathArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto fromArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    auto toArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    auto rotatableArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    std::string pathStringValue;
    if (pathArg->IsString(vm)) {
        pathStringValue = pathArg->ToString(vm)->ToString(vm);
    }
    float fromValue = (fromArg->IsNumber()) ? fromArg->ToNumber(vm)->Value() : 0.0f;
    float toValue = (toArg->IsNumber()) ? toArg->ToNumber(vm)->Value() : 1.0f;
    if (fromValue > 1.0f || fromValue < 0.0f) {
        fromValue = 0.0f;
    }
    if (toValue > 1.0f || toValue < 0.0f) {
        toValue = 1.0f;
    } else if (toValue < fromValue) {
        toValue = fromValue;
    }
    bool rotatableValue = (rotatableArg->IsBoolean()) ? rotatableArg->ToBoolean(vm)->Value() : false;
    GetArkUINodeModifiers()->getCommonModifier()->setMotionPath(nativeNode, pathStringValue.c_str(), fromValue,
        toValue, rotatableValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetMotionPath(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetMotionPath(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}


ArkUINativeModuleValue CommonBridge::SetMotionBlur(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> radiusArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> xArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> yArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    double radius = 0.0;
    if (!ArkTSUtils::ParseJsDouble(vm, radiusArg, radius) || LessNotEqual(radius, 0.0)) {
        radius = 0.0;
    }
    double x = 0.0;
    double y = 0.0;
    if (!ArkTSUtils::ParseJsDouble(vm, xArg, x) || LessNotEqual(x, 0.0)) {
        x = 0.0;
    }
    if (!ArkTSUtils::ParseJsDouble(vm, yArg, y) || LessNotEqual(y, 0.0)) {
        y = 0.0;
    }
    x = std::clamp(x, 0.0, 1.0);
    y = std::clamp(y, 0.0, 1.0);
    GetArkUINodeModifiers()->getCommonModifier()->setMotionBlur(nativeNode, radius, x, y);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetMotionBlur(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetMotionBlur(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetGroupDefaultFocus(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsBoolean()) {
        bool groupDefaultFocus = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getCommonModifier()->setGroupDefaultFocus(nativeNode, groupDefaultFocus);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetGroupDefaultFocus(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetGroupDefaultFocus(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetGroupDefaultFocus(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetFocusOnTouch(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsBoolean()) {
        bool focusOnTouch = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getCommonModifier()->setFocusOnTouch(nativeNode, focusOnTouch);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetFocusOnTouch(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetFocusOnTouch(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetFocusOnTouch(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetFocusable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsBoolean()) {
        bool focusable = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getCommonModifier()->setFocusable(nativeNode, focusable);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetFocusable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetFocusable(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetTabStop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsBoolean()) {
        bool tabStop = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getCommonModifier()->setTabStop(nativeNode, tabStop);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->setTabStop(nativeNode, false);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetTabStop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->setTabStop(nativeNode, false);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetTouchable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsBoolean()) {
        bool touchable = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getCommonModifier()->setTouchable(nativeNode, touchable);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetTouchable(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetTouchable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetTouchable(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetDefaultFocus(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsBoolean()) {
        bool defaultFocus = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getCommonModifier()->setDefaultFocus(nativeNode, defaultFocus);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetDefaultFocus(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetDefaultFocus(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetDefaultFocus(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetDisplayPriority(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsNumber()) {
        double value = secondArg->ToNumber(vm)->Value();
        GetArkUINodeModifiers()->getCommonModifier()->setDisplayPriority(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetDisplayPriority(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetDisplayPriority(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetDisplayPriority(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetAccessibilityLevel(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsString(vm)) {
        std::string stringValue = secondArg->ToString(vm)->ToString(vm);
        GetArkUINodeModifiers()->getCommonModifier()->setAccessibilityLevel(nativeNode, stringValue.c_str());
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetAccessibilityLevel(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetAccessibilityLevel(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetAccessibilityLevel(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetAccessibilityRoleType(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    if (runtimeCallInfo->GetArgsNumber() < NUM_2) {
        TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY, "set role params num is invalid");
        return panda::NativePointerRef::New(vm, nullptr);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    if (!firstArg->IsNativePointer(vm)) {
        TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY, "set role first param is invalid");
        return panda::NativePointerRef::New(vm, nullptr);
    }
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsInt()) {
        auto index = secondArg->Int32Value(vm);
        AccessibilityRoleType roleType = static_cast<AccessibilityRoleType>(index);
        std::string role = JSAccessibilityAbstract::GetRoleByType(roleType);
        if (!role.empty()) {
            GetArkUINodeModifiers()->getCommonModifier()->setAccessibilityCustomRole(nativeNode, role.c_str());
        } else {
            GetArkUINodeModifiers()->getCommonModifier()->resetAccessibilityCustomRole(nativeNode);
        }
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetAccessibilityCustomRole(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetAccessibilityRoleType(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    if (runtimeCallInfo->GetArgsNumber() < NUM_1) {
        TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY, "reset role params num is invalid");
        return panda::NativePointerRef::New(vm, nullptr);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsNativePointer(vm)) {
        TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY, "reset role first param is invalid");
        return panda::NativePointerRef::New(vm, nullptr);
    }
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetAccessibilityCustomRole(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetAccessibilityFocusCallback(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    if (runtimeCallInfo->GetArgsNumber() < NUM_2) {
        TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY, "set focus callback params num is invalid");
        return panda::NativePointerRef::New(vm, nullptr);
    }
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    if (!secondArg->IsFunction(vm)) {
        TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY, "set focus callback params is invalid, reset callback");
        ViewAbstractModelNG::ResetOnAccessibilityFocus(frameNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto obj = secondArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    panda::Local<panda::FunctionRef> func = obj;
    auto focusCallback = [vm, func = panda::CopyableGlobal(vm, func), node = AceType::WeakClaim(frameNode),
        containerId](bool isFocus) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        PipelineContext::SetCallBackNode(node);
        auto newJSVal = panda::BooleanRef::New(vm, isFocus);
        panda::Local<panda::JSValueRef> params[] = { newJSVal };
        func->Call(vm, func.ToLocal(), params, 1);
    };
    ViewAbstractModelNG::SetOnAccessibilityFocus(frameNode, std::move(focusCallback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetAccessibilityFocusCallback(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    if (runtimeCallInfo->GetArgsNumber() < NUM_1) {
        TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY, "reset focus callback params num is invalid");
        return panda::NativePointerRef::New(vm, nullptr);
    }
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ViewAbstractModelNG::ResetOnAccessibilityFocus(frameNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetOnAccessibilityActionIntercept(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::FUNCTION };
    auto jsVal = info[1];
    if (!JSViewAbstract::CheckJSCallbackInfo("onAccessibilityActionIntercept", jsVal, checkList)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto jsInterceptFunc = AceType::MakeRefPtr<JsAccessibilityActionInterceptFunction>(JSRef<JSFunc>::Cast(jsVal));
    auto onAccessibilityActionIntercept = [execCtx = info.GetExecutionContext(), func = std::move(jsInterceptFunc),
        node = AceType::WeakClaim<NG::FrameNode>(frameNode)](AccessibilityInterfaceAction action) ->
            AccessibilityActionInterceptResult {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, AccessibilityActionInterceptResult::ACTION_CONTINUE);
        PipelineContext::SetCallBackNode(node);
        return func->Execute(action);
    };
    ViewAbstractModelNG::SetOnAccessibilityActionIntercept(frameNode, std::move(onAccessibilityActionIntercept));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetOnAccessibilityActionIntercept(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    if (runtimeCallInfo->GetArgsNumber() < NUM_1) {
        return panda::NativePointerRef::New(vm, nullptr);
    }
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ViewAbstractModelNG::SetOnAccessibilityActionIntercept(frameNode, nullptr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetAccessibilityHoverTransparent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::FUNCTION };
    auto jsVal = info[1];
    if (!JSViewAbstract::CheckJSCallbackInfo("onAccessibilityHoverTransparent", jsVal, checkList)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto jsOnHoverTransparentFunc =
        AceType::MakeRefPtr<JsAccessibilityHoverTransparentFunction>(JSRef<JSFunc>::Cast(jsVal));
    auto onHoverTransparentFunc = [execCtx = info.GetExecutionContext(),
                                      func = std::move(jsOnHoverTransparentFunc),
                                      node = AceType::WeakClaim<NG::FrameNode>(frameNode)](TouchEventInfo& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        PipelineContext::SetCallBackNode(node);
        func->Execute(info);
    };
    ViewAbstractModelNG::SetOnAccessibilityHoverTransparent(frameNode, std::move(onHoverTransparentFunc));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetAccessibilityHoverTransparent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ViewAbstractModelNG::SetOnAccessibilityHoverTransparent(frameNode, nullptr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetAccessibilityDescription(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    std::string value;
    if (ArkTSUtils::ParseJsString(vm, secondArg, value)) {
        GetArkUINodeModifiers()->getCommonModifier()->setAccessibilityDescription(nativeNode, value.c_str());
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetAccessibilityDescription(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetAccessibilityDescription(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetAccessibilityDescription(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetOffset(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    bool useEdges = runtimeCallInfo->GetCallArgRef(NUM_1)->ToBoolean(vm)->Value();
    std::vector<ArkUIStringAndFloat> options;
    std::vector<std::optional<CalcDimension>> edges;
    std::vector<RefPtr<ResourceObject>> edgesResObj;

    if (useEdges) {
        ParseResult res = ParseCalcDimensionsNG(runtimeCallInfo, NUM_2, NUM_4, edges, edgesResObj, CalcDimension(0.0));
        if (res == ParseResult::LENGTHMETRICS_SUCCESS && AceApplicationInfo::GetInstance().IsRightToLeft()) {
            // Swap left and right
            std::swap(edges[NUM_1], edges[NUM_3]);
        }
        PushDimensionsToVector(options, edges);
        auto edgesRawPtr = static_cast<void*>(&edgesResObj);
        GetArkUINodeModifiers()->getCommonModifier()->setOffsetEdges(nativeNode, useEdges, options.data(), edgesRawPtr);
    } else {
        ParseCalcDimensionsNG(runtimeCallInfo, NUM_2, NUM_2, edges, edgesResObj, CalcDimension(0.0));
        PushDimensionsToVector(options, edges);
        auto edgesRawPtr = static_cast<void*>(&edgesResObj);
        GetArkUINodeModifiers()->getCommonModifier()->setOffsetEdges(nativeNode, useEdges, options.data(), edgesRawPtr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetOffset(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    GetArkUINodeModifiers()->getCommonModifier()->resetOffset(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void ParsePadding(const EcmaVM* vm, const Local<JSValueRef>& value, CalcDimension& dimen, ArkUISizeType& result,
    std::vector<RefPtr<ResourceObject>>& resObjs)
{
    RefPtr<ResourceObject> resObj;
    if (ArkTSUtils::ParseJsDimensionVp(vm, value, dimen, resObj)) {
        if (LessOrEqual(dimen.Value(), 0.0)) {
            dimen.SetValue(0.0);
            dimen.SetUnit(DimensionUnit::VP);
        }
        result.unit = static_cast<int8_t>(dimen.Unit());
        if (dimen.CalcValue() != "") {
            result.string = dimen.CalcValue().c_str();
        } else {
            result.value = dimen.Value();
        }
    }
    if (SystemProperties::ConfigChangePerform()) {
        resObjs.push_back(resObj);
    }
}

bool ParseLocalizedPadding(const EcmaVM* vm, const Local<JSValueRef>& value, CalcDimension& dimen,
    ArkUISizeType& result)
{
    if (ArkTSUtils::ParseJsLengthMetrics(vm, value, dimen)) {
        if (LessOrEqual(dimen.Value(), 0.0)) {
            dimen.SetValue(0.0);
            dimen.SetUnit(DimensionUnit::VP);
        }
        result.unit = static_cast<int8_t>(dimen.Unit());
        if (dimen.CalcValue() != "") {
            result.string = dimen.CalcValue().c_str();
        } else {
            result.value = dimen.Value();
        }
        return true;
    }
    return false;
}

ArkUINativeModuleValue CommonBridge::SetPadding(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> forthArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fifthArg = runtimeCallInfo->GetCallArgRef(NUM_4);

    struct ArkUISizeType top = { 0.0, static_cast<int8_t>(DimensionUnit::VP) };
    struct ArkUISizeType right = { 0.0, static_cast<int8_t>(DimensionUnit::VP) };
    struct ArkUISizeType bottom = { 0.0, static_cast<int8_t>(DimensionUnit::VP) };
    struct ArkUISizeType left = { 0.0, static_cast<int8_t>(DimensionUnit::VP) };

    CalcDimension topDimen(0, DimensionUnit::VP);
    CalcDimension rightDimen(0, DimensionUnit::VP);
    CalcDimension bottomDimen(0, DimensionUnit::VP);
    CalcDimension leftDimen(0, DimensionUnit::VP);
    std::vector<RefPtr<ResourceObject>> resObj;

    bool isLengthMetrics = false;
    if (secondArg->IsObject(vm)) {
        isLengthMetrics |= ParseLocalizedPadding(vm, secondArg, topDimen, top);
    }
    if (thirdArg->IsObject(vm)) {
        isLengthMetrics |= ParseLocalizedPadding(vm, thirdArg, rightDimen, right);
    }
    if (forthArg->IsObject(vm)) {
        isLengthMetrics |= ParseLocalizedPadding(vm, forthArg, bottomDimen, bottom);
    }
    if (fifthArg->IsObject(vm)) {
        isLengthMetrics |= ParseLocalizedPadding(vm, fifthArg, leftDimen, left);
    }

    if (isLengthMetrics) {
        auto isRightToLeft = AceApplicationInfo::GetInstance().IsRightToLeft();
        GetArkUINodeModifiers()->getCommonModifier()->setPadding(nativeNode,
            &top,
            isRightToLeft ? &left : &right,
            &bottom,
            isRightToLeft ? &right : &left,
            nullptr);
        return panda::JSValueRef::Undefined(vm);
    }

    ParsePadding(vm, secondArg, topDimen, top, resObj);
    ParsePadding(vm, thirdArg, rightDimen, right, resObj);
    ParsePadding(vm, forthArg, bottomDimen, bottom, resObj);
    ParsePadding(vm, fifthArg, leftDimen, left, resObj);
    auto rawPtr = static_cast<void*>(&resObj);
    GetArkUINodeModifiers()->getCommonModifier()->setPadding(nativeNode, &top, &right, &bottom, &left, rawPtr);

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetPadding(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetPadding(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

bool ParseLocalizedMargin(const EcmaVM* vm, const Local<JSValueRef>& value, CalcDimension& dimen, ArkUISizeType& result)
{
    if (ArkTSUtils::ParseJsLengthMetrics(vm, value, dimen)) {
        result.unit = static_cast<int8_t>(dimen.Unit());
        if (dimen.CalcValue() != "") {
            result.string = dimen.CalcValue().c_str();
        } else {
            result.value = dimen.Value();
        }
        return true;
    }
    return false;
}

void ParseMargin(const EcmaVM* vm, const Local<JSValueRef>& value, CalcDimension& dimen, ArkUISizeType& result,
    std::vector<RefPtr<ResourceObject>>& resObjs)
{
    RefPtr<ResourceObject> resObj;
    if (ArkTSUtils::ParseJsDimensionVp(vm, value, dimen, resObj)) {
        result.unit = static_cast<int8_t>(dimen.Unit());
        if (dimen.CalcValue() != "") {
            result.string = dimen.CalcValue().c_str();
        } else {
            result.value = dimen.Value();
        }
    }
    if (SystemProperties::ConfigChangePerform()) {
        resObjs.push_back(resObj);
    }
}

void ParseMarginLengthMetrics(EcmaVM* vm, Local<JSValueRef> arg, CalcDimension& dimension, ArkUISizeType& sizeType,
    bool& isLengthMetrics)
{
    if (arg->IsObject(vm)) {
        isLengthMetrics |= ParseLocalizedMargin(vm, arg, dimension, sizeType);
    }
}

ArkUINativeModuleValue CommonBridge::SetMargin(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> forthArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fifthArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    ArkUISizeType top = { 0.0, static_cast<int8_t>(DimensionUnit::VP), nullptr };
    ArkUISizeType right = { 0.0, static_cast<int8_t>(DimensionUnit::VP), nullptr };
    ArkUISizeType bottom = { 0.0, static_cast<int8_t>(DimensionUnit::VP), nullptr };
    ArkUISizeType left = { 0.0, static_cast<int8_t>(DimensionUnit::VP), nullptr };
    CalcDimension topDimen(0, DimensionUnit::VP);
    CalcDimension rightDimen(0, DimensionUnit::VP);
    CalcDimension bottomDimen(0, DimensionUnit::VP);
    CalcDimension leftDimen(0, DimensionUnit::VP);
    std::vector<RefPtr<ResourceObject>> resObj;

    bool isLengthMetrics = false;
    ParseMarginLengthMetrics(vm, secondArg, topDimen, top, isLengthMetrics);
    ParseMarginLengthMetrics(vm, thirdArg, rightDimen, right, isLengthMetrics);
    ParseMarginLengthMetrics(vm, forthArg, bottomDimen, bottom, isLengthMetrics);
    ParseMarginLengthMetrics(vm, fifthArg, leftDimen, left, isLengthMetrics);
    if (isLengthMetrics) {
        auto isRightToLeft = AceApplicationInfo::GetInstance().IsRightToLeft();
        GetArkUINodeModifiers()->getCommonModifier()->setMargin(nativeNode,
            &top,
            isRightToLeft ? &left : &right,
            &bottom,
            isRightToLeft ? &right : &left,
            nullptr);
        ParseNullptrResObj(resObj, NUM_4);
        return panda::JSValueRef::Undefined(vm);
    }
    ParseMargin(vm, secondArg, topDimen, top, resObj);
    ParseMargin(vm, thirdArg, rightDimen, right, resObj);
    ParseMargin(vm, forthArg, bottomDimen, bottom, resObj);
    ParseMargin(vm, fifthArg, leftDimen, left, resObj);
    auto rawPtr = static_cast<void*>(&resObj);
    GetArkUINodeModifiers()->getCommonModifier()->setMargin(nativeNode, &top, &right, &bottom, &left, rawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetMargin(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetMargin(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetSafeAreaPadding(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> forthArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fifthArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    struct ArkUISizeType top = { 0.0, static_cast<int8_t>(DimensionUnit::VP) };
    struct ArkUISizeType end = { 0.0, static_cast<int8_t>(DimensionUnit::VP) };
    struct ArkUISizeType bottom = { 0.0, static_cast<int8_t>(DimensionUnit::VP) };
    struct ArkUISizeType start = { 0.0, static_cast<int8_t>(DimensionUnit::VP) };
    CalcDimension topDimen(0, DimensionUnit::VP);
    CalcDimension endDimen(0, DimensionUnit::VP);
    CalcDimension bottomDimen(0, DimensionUnit::VP);
    CalcDimension startDimen(0, DimensionUnit::VP);
    bool isLengthMetrics = false;
    std::vector<RefPtr<ResourceObject>> resObj;
    if (secondArg->IsObject(vm)) {
        isLengthMetrics |= ParseLocalizedPadding(vm, secondArg, topDimen, top);
    }
    if (thirdArg->IsObject(vm)) {
        isLengthMetrics |= ParseLocalizedPadding(vm, thirdArg, endDimen, end);
    }
    if (forthArg->IsObject(vm)) {
        isLengthMetrics |= ParseLocalizedPadding(vm, forthArg, bottomDimen, bottom);
    }
    if (fifthArg->IsObject(vm)) {
        isLengthMetrics |= ParseLocalizedPadding(vm, fifthArg, startDimen, start);
    }
    if (!isLengthMetrics) {
        ParsePadding(vm, secondArg, topDimen, top, resObj);
        ParsePadding(vm, thirdArg, endDimen, end, resObj);
        ParsePadding(vm, forthArg, bottomDimen, bottom, resObj);
        ParsePadding(vm, fifthArg, startDimen, start, resObj);
    } else {
        ParseNullptrResObj(resObj, NUM_4);
    }
    struct ArkUIPaddingType localizedPadding;
    localizedPadding.top = top;
    localizedPadding.end = end;
    localizedPadding.bottom = bottom;
    localizedPadding.start = start;
    auto rawPtr = static_cast<void*>(&resObj);
    GetArkUINodeModifiers()->getCommonModifier()->setSafeAreaPadding(nativeNode, &localizedPadding, isLengthMetrics,
        rawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetSafeAreaPadding(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetSafeAreaPadding(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetMarkAnchor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> xArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> yArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    CalcDimension x(0.0, DimensionUnit::VP);
    CalcDimension y(0.0, DimensionUnit::VP);
    RefPtr<ResourceObject> xResObj;
    RefPtr<ResourceObject> yResObj;
    bool useLengthMetrics = ArkTSUtils::ParseJsLengthMetrics(vm, xArg, x);
    useLengthMetrics = ArkTSUtils::ParseJsLengthMetrics(vm, yArg, y) || useLengthMetrics;
    if (useLengthMetrics && AceApplicationInfo::GetInstance().IsRightToLeft()) {
        x.SetValue(-x.Value());
    }
    bool hasX = useLengthMetrics || ArkTSUtils::ParseJsDimensionNG(vm, xArg, x, DimensionUnit::VP, xResObj);
    bool hasY = useLengthMetrics || ArkTSUtils::ParseJsDimensionNG(vm, yArg, y, DimensionUnit::VP, yResObj);
    if (useLengthMetrics || hasX || hasY) {
        auto xRawPtr = AceType::RawPtr(xResObj);
        auto yRawPtr = AceType::RawPtr(yResObj);
        GetArkUINodeModifiers()->getCommonModifier()->setMarkAnchor(
            nativeNode, x.Value(), static_cast<int32_t>(x.Unit()), y.Value(), static_cast<int32_t>(y.Unit()),
            xRawPtr, yRawPtr);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetMarkAnchor(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetMarkAnchor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetMarkAnchor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetVisibility(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    int32_t value = 0;
    if (secondArg->IsNumber()) {
        value = secondArg->Int32Value(vm);
        if (value<NUM_0 || value>NUM_2) {
            value = 0;
        }
    }
    GetArkUINodeModifiers()->getCommonModifier()->setVisibility(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetVisibility(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetVisibility(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetAccessibilityText(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    std::string value;
    if (ArkTSUtils::ParseJsString(vm, secondArg, value)) {
        GetArkUINodeModifiers()->getCommonModifier()->setAccessibilityText(nativeNode, value.c_str());
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetAccessibilityText(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetAccessibilityText(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetAccessibilityText(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetAccessibilityTextHint(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    if (runtimeCallInfo->GetArgsNumber() < NUM_2) {
        TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY, "set text hint params num is invalid");
        return panda::NativePointerRef::New(vm, nullptr);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    if (!firstArg->IsNativePointer(vm)) {
        TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY, "set text hint first param is invalid");
        return panda::NativePointerRef::New(vm, nullptr);
    }
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    std::string value;
    if (ArkTSUtils::ParseJsString(vm, secondArg, value)) {
        GetArkUINodeModifiers()->getCommonModifier()->setAccessibilityTextHint(nativeNode, value.c_str());
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetAccessibilityTextHint(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetAccessibilityTextHint(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    if (runtimeCallInfo->GetArgsNumber() < NUM_1) {
        TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY, "reset text hint params num is invalid");
        return panda::NativePointerRef::New(vm, nullptr);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsNativePointer(vm)) {
        TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY, "reset text hint first param is invalid");
        return panda::NativePointerRef::New(vm, nullptr);
    }
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetAccessibilityTextHint(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetAccessibilityChecked(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    if (runtimeCallInfo->GetArgsNumber() < NUM_2) {
        TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY, "set checked params num is invalid");
        return panda::NativePointerRef::New(vm, nullptr);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (!firstArg->IsNativePointer(vm)) {
        TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY, "set checked first param is invalid");
        return panda::NativePointerRef::New(vm, nullptr);
    }
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsBoolean()) {
        bool boolValue = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getCommonModifier()->setAccessibilityChecked(nativeNode, boolValue);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetAccessibilityChecked(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetAccessibilityChecked(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    if (runtimeCallInfo->GetArgsNumber() < NUM_1) {
        TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY, "reset checked params num is invalid");
        return panda::NativePointerRef::New(vm, nullptr);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    if (!firstArg->IsNativePointer(vm)) {
        TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY, "reset checked first param is invalid");
        return panda::NativePointerRef::New(vm, nullptr);
    }
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetAccessibilityChecked(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetAccessibilitySelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    if (runtimeCallInfo->GetArgsNumber() < NUM_2) {
        TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY, "set selected params num is invalid");
        return panda::NativePointerRef::New(vm, nullptr);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (!firstArg->IsNativePointer(vm)) {
        TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY, "set selected first param is invalid");
        return panda::NativePointerRef::New(vm, nullptr);
    }
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsBoolean()) {
        bool boolValue = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getCommonModifier()->setAccessibilitySelected(nativeNode, boolValue);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetAccessibilitySelected(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetAccessibilitySelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    if (runtimeCallInfo->GetArgsNumber() < NUM_1) {
        TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY, "reset selected params num is invalid");
        return panda::NativePointerRef::New(vm, nullptr);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    if (!firstArg->IsNativePointer(vm)) {
        TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY, "reset selected first param is invalid");
        return panda::NativePointerRef::New(vm, nullptr);
    }
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetAccessibilitySelected(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetConstraintSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> forthArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fifthArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CalcDimension minWidth;
    CalcDimension maxWidth;
    CalcDimension minHeight;
    CalcDimension maxHeight;
    struct ArkUISizeType minWidthValue = {0.0, 0};
    struct ArkUISizeType maxWidthValue = {0.0, 0};
    struct ArkUISizeType minHeightValue = {0.0, 0};
    struct ArkUISizeType maxHeightValue = {0.0, 0};

    RefPtr<ResourceObject> minWidthResObj;
    RefPtr<ResourceObject> maxWidthResObj;
    RefPtr<ResourceObject> minHeightResObj;
    RefPtr<ResourceObject> maxHeightResObj;
    bool version10OrLarger = Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN);
    if (ArkTSUtils::ParseJsDimensionVp(vm, secondArg, minWidth, minWidthResObj, false)) {
        if (minWidth.CalcValue() != "") {
            minWidthValue.string = minWidth.CalcValue().c_str();
        } else {
            minWidthValue.value = minWidth.Value();
            minWidthValue.unit = static_cast<int8_t>(minWidth.Unit());
        }
        auto minWidthRawResPtr = AceType::RawPtr(minWidthResObj);
        GetArkUINodeModifiers()->getCommonModifier()->setMinWidth(nativeNode, &minWidthValue, minWidthRawResPtr);
    } else if (version10OrLarger) {
        GetArkUINodeModifiers()->getCommonModifier()->resetMinWidth(nativeNode);
    }

    if (ArkTSUtils::ParseJsDimensionVp(vm, thirdArg, maxWidth, maxWidthResObj, false)) {
        if (maxWidth.CalcValue() != "") {
            maxWidthValue.string = maxWidth.CalcValue().c_str();
        } else {
            maxWidthValue.value = maxWidth.Value();
            maxWidthValue.unit = static_cast<int8_t>(maxWidth.Unit());
        }
        auto maxWidthRawResPtr = AceType::RawPtr(maxWidthResObj);
        GetArkUINodeModifiers()->getCommonModifier()->setMaxWidth(nativeNode, &maxWidthValue, maxWidthRawResPtr);
    } else if (version10OrLarger) {
        GetArkUINodeModifiers()->getCommonModifier()->resetMaxWidth(nativeNode);
    }

    if (ArkTSUtils::ParseJsDimensionVp(vm, forthArg, minHeight, minHeightResObj, false)) {
        if (minHeight.CalcValue() != "") {
            minHeightValue.string = minHeight.CalcValue().c_str();
        } else {
            minHeightValue.value = minHeight.Value();
            minHeightValue.unit = static_cast<int8_t>(minHeight.Unit());
        }
        auto minHeightRawResPtr = AceType::RawPtr(minHeightResObj);
        GetArkUINodeModifiers()->getCommonModifier()->setMinHeight(nativeNode, &minHeightValue, minHeightRawResPtr);
    } else if (version10OrLarger) {
        GetArkUINodeModifiers()->getCommonModifier()->resetMinHeight(nativeNode);
    }

    if (ArkTSUtils::ParseJsDimensionVp(vm, fifthArg, maxHeight, maxHeightResObj, false)) {
        if (maxHeight.CalcValue() != "") {
            maxHeightValue.string = maxHeight.CalcValue().c_str();
        } else {
            maxHeightValue.value = maxHeight.Value();
            maxHeightValue.unit = static_cast<int8_t>(maxHeight.Unit());
        }
        auto maxHeightRawResPtr = AceType::RawPtr(maxHeightResObj);
        GetArkUINodeModifiers()->getCommonModifier()->setMaxHeight(nativeNode, &maxHeightValue, maxHeightRawResPtr);
    } else if (version10OrLarger) {
        GetArkUINodeModifiers()->getCommonModifier()->resetMaxHeight(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetConstraintSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetMaxHeight(nativeNode);
    GetArkUINodeModifiers()->getCommonModifier()->resetMaxWidth(nativeNode);
    GetArkUINodeModifiers()->getCommonModifier()->resetMinHeight(nativeNode);
    GetArkUINodeModifiers()->getCommonModifier()->resetMinWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetDirection(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    std::string dir;
    int32_t direction = NUM_3;
    if (secondArg->IsString(vm)) {
        dir = secondArg->ToString(vm)->ToString(vm);
        if (dir == "Ltr") {
            direction = NUM_0;
        } else if (dir == "Rtl") {
            direction = NUM_1;
        } else if (dir == "Auto") {
            direction = NUM_3;
        } else if (dir == "undefined" && Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
            direction = NUM_3;
        }
    }
    GetArkUINodeModifiers()->getCommonModifier()->setDirection(nativeNode, direction);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetDirection(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetDirection(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetLayoutWeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    float layoutWeight = 0.0f;
    if (secondArg->IsNumber()) {
        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            layoutWeight = secondArg->ToNumber(vm)->Value();
        } else {
            layoutWeight = secondArg->Int32Value(vm);
        }
    } else if (secondArg->IsString(vm)) {
        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            layoutWeight = StringUtils::StringToFloat(secondArg->ToString(vm)->ToString(vm));
        } else {
            layoutWeight = StringUtils::StringToInt(secondArg->ToString(vm)->ToString(vm));
        }
    }
    GetArkUINodeModifiers()->getCommonModifier()->setLayoutWeight(nativeNode, layoutWeight);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetLayoutWeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetLayoutWeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CalcDimension wVal(0.0, DimensionUnit::VP);
    CalcDimension hVal(0.0, DimensionUnit::VP);
    RefPtr<ResourceObject> widthResObj;
    RefPtr<ResourceObject> heightResObj;
    ParseCalcDimension(vm, nativeNode, secondArg, wVal, true, widthResObj);
    ParseCalcDimension(vm, nativeNode, thirdArg, hVal, false, heightResObj);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetWidth(nativeNode);
    GetArkUINodeModifiers()->getCommonModifier()->resetHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetAlignSelf(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    if (secondArg->IsNumber() && secondArg->ToNumber(vm)->Value() >= 0 &&
        secondArg->ToNumber(vm)->Value() <= MAX_ALIGN_VALUE) {
        GetArkUINodeModifiers()->getCommonModifier()->setAlignSelf(nativeNode, secondArg->Int32Value(vm));
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetAlignSelf(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetAlignSelf(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetAlignSelf(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetAspectRatio(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    if (secondArg->IsNumber()) {
        double value = secondArg->ToNumber(vm)->Value();
        GetArkUINodeModifiers()->getCommonModifier()->setAspectRatio(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetAspectRatio(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetAspectRatio(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetAspectRatio(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetFlexGrow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    if (secondArg->IsNumber()) {
        double value = secondArg->ToNumber(vm)->Value();
        GetArkUINodeModifiers()->getCommonModifier()->setFlexGrow(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetFlexGrow(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetFlexGrow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetFlexGrow(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetFlexShrink(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    if (secondArg->IsNumber()) {
        double value = secondArg->ToNumber(vm)->Value();
        GetArkUINodeModifiers()->getCommonModifier()->setFlexShrink(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetFlexShrink(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetFlexShrink(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetFlexShrink(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetGridOffset(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> offsetArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    int32_t offset = 0;
    if (offsetArg->IsNumber()) {
        offset = offsetArg->Int32Value(vm);
        GetArkUINodeModifiers()->getCommonModifier()->setGridOffset(nativeNode, offset);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetGridOffset(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetGridOffset(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetGridOffset(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetGridSpan(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    int32_t value = 0;
    if (secondArg->IsNumber()) {
        value = secondArg->Int32Value(vm);
        GetArkUINodeModifiers()->getCommonModifier()->setGridSpan(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetGridSpan(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetGridSpan(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetGridSpan(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetIgnoreLayoutSafeArea(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    std::string typeCppStr = "";
    std::string edgesCppStr = "";
    LayoutSafeAreaType layoutSafeAreaType = NG::LAYOUT_SAFE_AREA_TYPE_SYSTEM;
    LayoutSafeAreaEdge layoutSafeAreaEdges = NG::LAYOUT_SAFE_AREA_EDGE_ALL;
    if (secondArg->IsString(vm)) {
        typeCppStr = secondArg->ToString(vm)->ToString(vm);
        layoutSafeAreaType = ParseLayoutSafeAreaTypeStr(typeCppStr);
    }
    if (thirdArg->IsString(vm)) {
        edgesCppStr = thirdArg->ToString(vm)->ToString(vm);
        layoutSafeAreaEdges = ParseLayoutSafeAreaEdgesStr(edgesCppStr);
    }
    GetArkUINodeModifiers()->getCommonModifier()->setIgnoreLayoutSafeArea(
        nativeNode, layoutSafeAreaType, layoutSafeAreaEdges);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetIgnoreLayoutSafeArea(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetIgnoreLayoutSafeArea(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetExpandSafeArea(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    std::string typeCppStr = "";
    std::string edgesCppStr = "";
    uint32_t safeAreaType = NG::SAFE_AREA_TYPE_NONE;
    uint32_t safeAreaEdge = NG::SAFE_AREA_EDGE_NONE;
    if (secondArg->IsString(vm)) {
        typeCppStr = secondArg->ToString(vm)->ToString(vm);
        safeAreaType = ParseStrToUint(typeCppStr);
    } else {
        safeAreaType = NG::SAFE_AREA_TYPE_ALL;
    }

    if (thirdArg->IsString(vm)) {
        edgesCppStr = thirdArg->ToString(vm)->ToString(vm);
        safeAreaEdge = ParseStrToUint(edgesCppStr);
    } else {
        safeAreaEdge = NG::SAFE_AREA_EDGE_ALL;
    }
    GetArkUINodeModifiers()->getCommonModifier()->setExpandSafeArea(nativeNode, safeAreaType, safeAreaEdge);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetExpandSafeArea(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetExpandSafeArea(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetAlignRules(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> leftArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> middleArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> rightArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> topArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> centerArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    Local<JSValueRef> bottomArg = runtimeCallInfo->GetCallArgRef(NUM_6);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    auto anchors = std::make_unique<std::string []>(ALIGN_RULES_NUM);
    auto direction = std::make_unique<ArkUI_Int32 []>(ALIGN_RULES_NUM);
    for (int32_t i = 0; i < ALIGN_RULES_NUM; i++) {
        anchors[i] = "";
        direction[i] = ALIGN_DIRECTION_DEFAULT;
    }
    bool leftParseResult = ParseJsAlignRule(vm, leftArg, anchors[0], direction[0]);
    bool middleParseResult = ParseJsAlignRule(vm, middleArg, anchors[1], direction[1]);
    bool rightParseResult = ParseJsAlignRule(vm, rightArg, anchors[2], direction[2]);
    bool topParseResult = ParseJsAlignRule(vm, topArg, anchors[3], direction[3]);
    bool centerParseResult = ParseJsAlignRule(vm, centerArg, anchors[4], direction[4]);
    bool bottomParseResult = ParseJsAlignRule(vm, bottomArg, anchors[5], direction[5]);
    if (!leftParseResult && !middleParseResult && !rightParseResult && !topParseResult && !centerParseResult &&
        !bottomParseResult) {
        GetArkUINodeModifiers()->getCommonModifier()->resetAlignRules(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto realAnchors = std::make_unique<char* []>(ALIGN_RULES_NUM);
    for (int32_t i = 0; i < ALIGN_RULES_NUM; i++) {
        realAnchors[i] = const_cast<char*>(anchors[i].c_str());
    }
    GetArkUINodeModifiers()->getCommonModifier()->setAlignRules(nativeNode, realAnchors.get(), direction.get(),
        ALIGN_RULES_NUM);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetAlignRules(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetAlignRules(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetFlexBasis(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    struct ArkUIStringAndFloat flexBasis { 0.0, nullptr};
    std::string tempValueStr = "";
    if (secondArg->IsNumber()) {
        flexBasis.value = secondArg->ToNumber(vm)->Value();
        GetArkUINodeModifiers()->getCommonModifier()->setFlexBasis(nativeNode, &flexBasis);
    } else if (secondArg->IsString(vm)) {
        tempValueStr = secondArg->ToString(vm)->ToString(vm);
        flexBasis.valueStr = tempValueStr.c_str();
        GetArkUINodeModifiers()->getCommonModifier()->setFlexBasis(nativeNode, &flexBasis);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetFlexBasis(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetFlexBasis(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetFlexBasis(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetAllowDrop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsUndefined()) {
        GetArkUINodeModifiers()->getCommonModifier()->resetAllowDrop(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    Local<panda::ArrayRef> allowDropArray = static_cast<Local<panda::ArrayRef>>(secondArg);
    auto length = allowDropArray->Length(vm);
    if (length <= 0) {
        GetArkUINodeModifiers()->getCommonModifier()->resetAllowDrop(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    std::vector<std::string> keepStr(length);
    std::vector<const char*> strList;
    for (size_t i = 0; i < length; i++) {
        Local<JSValueRef> objValue = allowDropArray->GetValueAt(vm, secondArg, i);
        keepStr[i] = objValue->ToString(vm)->ToString(vm);
        strList.push_back(keepStr[i].c_str());
    }
    GetArkUINodeModifiers()->getCommonModifier()->setAllowDrop(nativeNode, strList.data(), strList.size());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetAllowDrop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetAllowDrop(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetId(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsString(vm)) {
        std::string stringValue = secondArg->ToString(vm)->ToString(vm);
        GetArkUINodeModifiers()->getCommonModifier()->setId(nativeNode, stringValue.c_str());
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetId(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetId(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetId(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetKey(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsString(vm)) {
        std::string stringValue = secondArg->ToString(vm)->ToString(vm);
        GetArkUINodeModifiers()->getCommonModifier()->setKey(nativeNode, stringValue.c_str());
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetKey(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetKey(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetKey(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetRestoreId(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsNumber()) {
        uint32_t value = secondArg->Uint32Value(vm);
        GetArkUINodeModifiers()->getCommonModifier()->setRestoreId(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetRestoreId(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetRestoreId(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetRestoreId(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetTabIndex(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsNumber()) {
        int32_t index = secondArg->Int32Value(vm);
        GetArkUINodeModifiers()->getCommonModifier()->setTabIndex(nativeNode, index);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetTabIndex(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetTabIndex(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetTabIndex(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetObscured(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    if (secondArg->IsUndefined() || !secondArg->IsArray(vm)) {
        GetArkUINodeModifiers()->getCommonModifier()->resetObscured(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    Local<panda::ArrayRef> transArray = static_cast<Local<panda::ArrayRef>>(secondArg);
    auto length = transArray->Length(vm);
    int32_t reasonArray[length];

    for (size_t i = 0; i < length; i++) {
        Local<JSValueRef> value = transArray->GetValueAt(vm, secondArg, i);
        reasonArray[i] = value->Int32Value(vm);
    }
    GetArkUINodeModifiers()->getCommonModifier()->setObscured(nativeNode, reasonArray, length);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetObscured(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetObscured(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetForegroundEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> frameNodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> radiusArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(frameNodeArg->ToNativePointer(vm)->Value());
    CalcDimension radius;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, radiusArg, radius) || LessNotEqual(radius.Value(), 0.0f)) {
        radius.SetValue(0.0f);
    }
    ArkUI_Float32 radiusArk = static_cast<ArkUI_Int32>(radius.Value());
    GetArkUINodeModifiers()->getCommonModifier()->setForegroundEffect(nativeNode, radiusArk);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetForegroundEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetForegroundEffect(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void SetBackgroundEffectParam(ArkUIRuntimeCallInfo* runtimeCallInfo, int32_t& policy, int32_t& blurType,
    Color& inactiveColor, bool& isValidColor, ArkUINodeHandle nativeNode, RefPtr<ResourceObject>& resourceObject)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> policyArg = runtimeCallInfo->GetCallArgRef(7);        // 7:index of parameter policy
    Local<JSValueRef> inactiveColorArg = runtimeCallInfo->GetCallArgRef(8); // 8:index of parameter inactiveColor
    Local<JSValueRef> typeArg = runtimeCallInfo->GetCallArgRef(9);          // 9:index of parameter type

    ArkTSUtils::ParseJsInt32(vm, policyArg, policy);
    if (policy < static_cast<int32_t>(BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE) ||
        policy > static_cast<int32_t>(BlurStyleActivePolicy::ALWAYS_INACTIVE)) {
        policy = static_cast<int32_t>(BlurStyleActivePolicy::ALWAYS_ACTIVE);
    }
    ArkTSUtils::ParseJsInt32(vm, typeArg, blurType);
    if (blurType < static_cast<int32_t>(BlurType::WITHIN_WINDOW) ||
        blurType > static_cast<int32_t>(BlurType::BEHIND_WINDOW)) {
        blurType = static_cast<int32_t>(BlurType::WITHIN_WINDOW);
    }

    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (ArkTSUtils::ParseJsColor(vm, inactiveColorArg, inactiveColor, resourceObject, nodeInfo)) {
        isValidColor = true;
    }
}

void SetAdaptiveColorParam(ArkUIRuntimeCallInfo* runtimeCallInfo, AdaptiveColor& adaptiveColor)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> adaptiveColorArg = runtimeCallInfo->GetCallArgRef(5); // 5:index of parameter adaptiveColor
    auto adaptiveColorValue = static_cast<int32_t>(AdaptiveColor::DEFAULT);
    if (adaptiveColorArg->IsNumber()) {
        adaptiveColorValue = adaptiveColorArg->Int32Value(vm);
        if (adaptiveColorValue >= static_cast<int32_t>(AdaptiveColor::DEFAULT) &&
            adaptiveColorValue <= static_cast<int32_t>(AdaptiveColor::AVERAGE)) {
            adaptiveColor = static_cast<AdaptiveColor>(adaptiveColorValue);
        }
    }
}

void ParseBackgroundEffectParams(const Local<JSValueRef>& saturationArg, const Local<JSValueRef>& brightnessArg,
    const EcmaVM* vm, ArkUI_Float32& saturationVal, ArkUI_Float32& brightnessVal)
{
    ArkUI_Float32 saturation = 1.0f;
    if (saturationArg->IsNumber()) {
        saturation = saturationArg->ToNumber(vm)->Value();
        saturation = (saturation > 0.0f || NearZero(saturation)) ? saturation : 1.0f;
    }
    saturationVal = saturation;
    ArkUI_Float32 brightness = 1.0f;
    if (brightnessArg->IsNumber()) {
        brightness = brightnessArg->ToNumber(vm)->Value();
        brightness = (brightness > 0.0f || NearZero(brightness)) ? brightness : 1.0f;
    }
    brightnessVal = brightness;
}

ArkUINativeModuleValue CommonBridge::SetBackgroundEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> frameNodeArg = runtimeCallInfo->GetCallArgRef(0);     // 0:index of parameter frameNode
    Local<JSValueRef> radiusArg = runtimeCallInfo->GetCallArgRef(1);        // 1:index of parameter radius
    Local<JSValueRef> saturationArg = runtimeCallInfo->GetCallArgRef(2);    // 2:index of parameter saturation
    Local<JSValueRef> brightnessArg = runtimeCallInfo->GetCallArgRef(3);    // 3:index of parameter brightness
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(4);         // 4:index of parameter color
    Local<JSValueRef> blurOptionsArg = runtimeCallInfo->GetCallArgRef(6);   // 6:index of parameter blurOptions
    Local<JSValueRef> disableSystemAdaptationArg = runtimeCallInfo->GetCallArgRef(NUM_10);
    auto nativeNode = nodePtr(frameNodeArg->ToNativePointer(vm)->Value());
    CalcDimension radius;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, radiusArg, radius) || LessNotEqual(radius.Value(), 0.0f)) {
        radius.SetValue(0.0f);
    }
    ArkUI_Float32 saturation = 1.0f;
    ArkUI_Float32 brightness = 1.0f;
    ParseBackgroundEffectParams(saturationArg, brightnessArg, vm, saturation, brightness);
    Color color = Color::TRANSPARENT;
    RefPtr<ResourceObject> colorResObj;

    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColor(vm, colorArg, color, colorResObj, nodeInfo)) {
        color.SetValue(Color::TRANSPARENT.GetValue());
    }
    auto adaptiveColor = AdaptiveColor::DEFAULT;
    SetAdaptiveColorParam(runtimeCallInfo, adaptiveColor);
    BlurOption blurOption;
    if (blurOptionsArg->IsArray(vm)) {
        ParseBlurOption(vm, blurOptionsArg, blurOption);
    }
    auto policy = static_cast<int32_t>(BlurStyleActivePolicy::ALWAYS_ACTIVE);
    auto blurType = static_cast<int32_t>(BlurType::WITHIN_WINDOW);
    Color inactiveColor = Color::TRANSPARENT;
    bool isValidColor = false;
    RefPtr<ResourceObject> inactiveColorResObj;
    SetBackgroundEffectParam(
        runtimeCallInfo, policy, blurType, inactiveColor, isValidColor, nativeNode, inactiveColorResObj);
    bool disableSystemAdaptation = false;
    if (disableSystemAdaptationArg->IsBoolean()) {
        disableSystemAdaptation = disableSystemAdaptationArg->ToBoolean(vm)->Value();
    }
    auto colorRawPtr = AceType::RawPtr(colorResObj);
    auto inactiveColorRawPtr = AceType::RawPtr(inactiveColorResObj);
    GetArkUINodeModifiers()->getCommonModifier()->setBackgroundEffect(nativeNode,
        static_cast<ArkUI_Float32>(radius.Value()), saturation, brightness, color.GetValue(),
        static_cast<ArkUI_Int32>(adaptiveColor), blurOption.grayscale.data(), blurOption.grayscale.size(), policy,
        blurType, isValidColor, inactiveColor.GetValue(), disableSystemAdaptation, colorRawPtr, inactiveColorRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetBackgroundEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetBackgroundEffect(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetBackgroundBrightness(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> frameNodeArg = runtimeCallInfo->GetCallArgRef(0);     // 0:index of parameter frameNode
    Local<JSValueRef> ratedArg = runtimeCallInfo->GetCallArgRef(1);         // 1:index of parameter ratedArg
    Local<JSValueRef> lightUpDegreeArg = runtimeCallInfo->GetCallArgRef(2); // 2:index of parameter lightUpDegreeArg
    auto nativeNode = nodePtr(frameNodeArg->ToNativePointer(vm)->Value());
    double rate = 0.0;
    double lightUpDegree = 0.0;
    if (!ArkTSUtils::ParseJsDouble(vm, ratedArg, rate)) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (!ArkTSUtils::ParseJsDouble(vm, lightUpDegreeArg, lightUpDegree)) {
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getCommonModifier()->setBackgroundBrightness(nativeNode, rate, lightUpDegree);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetBackgroundBrightness(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetBackgroundBrightness(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetBackgroundBrightnessInternal(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> frameNodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(frameNodeArg->ToNativePointer(vm)->Value());
    ArkUI_Float32 rate = 1.0f;
    ArkUI_Float32 lightUpDegree = 0.0f;
    ArkUI_Float32 cubicCoeff = 0.0f;
    ArkUI_Float32 quadCoeff = 0.0f;
    ArkUI_Float32 saturation = 1.0f;
    std::vector<float> posRGB(3, 0.0);
    std::vector<float> negRGB(3, 0.0);
    ArkUI_Float32 fraction = 1.0f;
    ParseDynamicBrightnessOption(runtimeCallInfo, vm, rate, lightUpDegree,
        cubicCoeff, quadCoeff, saturation, posRGB, negRGB, fraction);
    GetArkUINodeModifiers()->getCommonModifier()->setBackgroundBrightnessInternal(
        nativeNode, rate, lightUpDegree, cubicCoeff, quadCoeff, saturation,
        posRGB.data(), posRGB.size(), negRGB.data(), negRGB.size(), fraction);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetBackgroundBrightnessInternal(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetBackgroundBrightnessInternal(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetForegroundBrightness(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> frameNodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(frameNodeArg->ToNativePointer(vm)->Value());
    ArkUI_Float32 rate = 1.0f;
    ArkUI_Float32 lightUpDegree = 0.0f;
    ArkUI_Float32 cubicCoeff = 0.0f;
    ArkUI_Float32 quadCoeff = 0.0f;
    ArkUI_Float32 saturation = 1.0f;
    std::vector<float> posRGB(3, 0.0);
    std::vector<float> negRGB(3, 0.0);
    ArkUI_Float32 fraction = 1.0f;
    ParseDynamicBrightnessOption(runtimeCallInfo, vm, rate, lightUpDegree,
        cubicCoeff, quadCoeff, saturation, posRGB, negRGB, fraction);
    GetArkUINodeModifiers()->getCommonModifier()->setForegroundBrightness(
        nativeNode, rate, lightUpDegree, cubicCoeff, quadCoeff, saturation,
        posRGB.data(), posRGB.size(), negRGB.data(), negRGB.size(), fraction);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetForegroundBrightness(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetForegroundBrightness(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void ParseDragPreViewOptions(ArkUIRuntimeCallInfo* runtimeCallInfo, Local<JSValueRef>& valueObj,
    ArkUIDragPreViewOptions& preViewOptions)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    if (!valueObj->IsObject(vm)) {
        return;
    }
    auto obj = valueObj->ToObject(vm);
    auto mode = obj->Get(vm, "mode");
    if (mode->IsNumber()) {
        preViewOptions.isModeArray = false;
        preViewOptions.mode = mode->Int32Value(vm);
    } else if (mode->IsArray(vm)) {
        Local<panda::ArrayRef> modeArray = static_cast<Local<panda::ArrayRef>>(mode);
        int32_t arrLength = static_cast<int32_t>(modeArray->Length(vm));
        if (arrLength > NUM_4) {
            arrLength = NUM_4;
        }
        preViewOptions.modeArray = new int32_t[arrLength];
        for (int32_t i = 0; i < arrLength; i++) {
            Local<JSValueRef> objValue = modeArray->GetValueAt(vm, modeArray, i);
            preViewOptions.modeArray[i] = objValue->Int32Value(vm);
        }
        preViewOptions.isModeArray = true;
        preViewOptions.modeArrayLength = static_cast<ArkUI_Int32>(arrLength);
    }

    auto sizeChangeEffect = obj->Get(vm, "sizeChangeEffect");
    if (sizeChangeEffect->IsNumber()) {
        preViewOptions.sizeChangeEffect = sizeChangeEffect->Int32Value(vm);
    }

    auto numberBadge = obj->Get(vm, "numberBadge");
    if (numberBadge->IsBoolean()) {
        preViewOptions.isBadgeNumber = false;
        preViewOptions.isShowBadge = numberBadge->ToBoolean(vm)->Value();
    } else if (numberBadge->IsNumber()) {
        preViewOptions.isBadgeNumber = true;
        preViewOptions.badgeNumber = numberBadge->Int32Value(vm);
    }
}

void ParseDragInteractionOptions(ArkUIRuntimeCallInfo* runtimeCallInfo, Local<JSValueRef>& valueObj,
    ArkUIDragInteractionOptions& interactionOptions)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    if (!valueObj->IsObject(vm)) {
        return;
    }
    auto obj = valueObj->ToObject(vm);

    Local<JSValueRef> isMultiSelectionEnabled = obj->Get(vm, "isMultiSelectionEnabled");
    if (isMultiSelectionEnabled->IsBoolean()) {
        interactionOptions.isMultiSelectionEnabled = isMultiSelectionEnabled->ToBoolean(vm)->Value();
    }
    Local<JSValueRef> defaultAnimationBeforeLifting = obj->Get(vm, "defaultAnimationBeforeLifting");
    if (defaultAnimationBeforeLifting->IsBoolean()) {
        interactionOptions.defaultAnimationBeforeLifting = defaultAnimationBeforeLifting->ToBoolean(vm)->Value();
    }
    Local<JSValueRef> enableEdgeAutoScroll = obj->Get(vm, "enableEdgeAutoScroll");
    if (enableEdgeAutoScroll->IsBoolean()) {
        interactionOptions.enableEdgeAutoScroll = enableEdgeAutoScroll->ToBoolean(vm)->Value();
    }
    Local<JSValueRef> enableHapticFeedback = obj->Get(vm, "enableHapticFeedback");
    if (enableHapticFeedback->IsBoolean()) {
        interactionOptions.enableHapticFeedback = enableHapticFeedback->ToBoolean(vm)->Value();
    }
    Local<JSValueRef> isLiftingDisabled = obj->Get(vm, "isLiftingDisabled");
    if (isLiftingDisabled->IsBoolean()) {
        interactionOptions.isLiftingDisabled = isLiftingDisabled->ToBoolean(vm)->Value();
    }
}

ArkUINativeModuleValue CommonBridge::SetDragPreviewOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> frameNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(frameNodeArg->ToNativePointer(vm)->Value());

    Local<JSValueRef> valueObj = runtimeCallInfo->GetCallArgRef(NUM_1);
    struct ArkUIDragPreViewOptions preViewOptions = { 1, 0, 0, 0, nullptr, false, true, false };
    struct ArkUIDragInteractionOptions interactionOptions = { false, false, true, false, false };
    ParseDragPreViewOptions(runtimeCallInfo, valueObj, preViewOptions);
    ParseDragInteractionOptions(runtimeCallInfo, valueObj, interactionOptions);

    GetArkUINodeModifiers()->getCommonModifier()->setDragPreviewOptions(
        nativeNode, preViewOptions, interactionOptions);
    delete[] preViewOptions.modeArray;
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetDragPreviewOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetDragPreviewOptions(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetDragPreview(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> frameNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(frameNodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueObj = runtimeCallInfo->GetCallArgRef(NUM_1);
    struct ArkUIDragPreview dragPreview = { "" };
    std::string stringValue;
    std::string extraInfoValue;
    RefPtr<PixelMap> pixmap = nullptr;
    std::shared_ptr<Media::PixelMap> pixelMapSharedPtr = nullptr;
    if (valueObj->IsObject(vm)) {
        auto obj = valueObj->ToObject(vm);
        auto inspectorId = obj->Get(vm, "inspetorId");
        if (inspectorId->IsString(vm)) {
            stringValue = inspectorId->ToString(vm)->ToString(vm);
            dragPreview.inspectorId = stringValue.c_str();
        }
        auto onlyForLifting = obj->Get(vm, "onlyForLifting");
        if (onlyForLifting->IsBoolean()) {
            dragPreview.onlyForLifting = onlyForLifting->ToBoolean(vm)->Value();
        }
        auto extraInfo = obj->Get(vm, "extraInfo");
        if (extraInfo->IsString(vm)) {
            extraInfoValue = extraInfo->ToString(vm)->ToString(vm);
            dragPreview.extraInfo = extraInfoValue.c_str();
        }
        auto pixelMap = obj->Get(vm, "pixelMap");
        if (!pixelMap->IsUndefined()) {
#if defined(PIXEL_MAP_SUPPORTED)
            pixmap = ArkTSUtils::CreatePixelMapFromNapiValue(vm, pixelMap);
#endif
            if (pixmap) {
                pixelMapSharedPtr = pixmap->GetPixelMapSharedPtr();
                dragPreview.pixelMap = static_cast<void*>(&pixelMapSharedPtr);
            }
        }
    }
    GetArkUINodeModifiers()->getCommonModifier()->setDragPreview(nativeNode, dragPreview);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetDragPreview(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetDragPreview(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetResponseRegion(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    int32_t length = thirdArg->Int32Value(vm);
    ArkUI_Float32 regionArray[length];
    int32_t regionUnits[length];
    if (!ParseResponseRegion(vm, secondArg, regionArray, regionUnits, length)) {
        GetArkUINodeModifiers()->getCommonModifier()->resetResponseRegion(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getCommonModifier()->setResponseRegion(nativeNode, regionArray, regionUnits, length);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetResponseRegion(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetResponseRegion(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetTransition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    ViewAbstract::CleanTransition(frameNode);
    ViewAbstract::SetChainedTransition(frameNode, nullptr, nullptr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetTransition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    if (!info[1]->IsObject()) {
        ViewAbstract::CleanTransition(frameNode);
        ViewAbstract::SetChainedTransition(frameNode, nullptr, nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    auto obj = Framework::JSRef<Framework::JSObject>::Cast(info[1]);
    if (!obj->GetProperty("successor_")->IsUndefined()) {
        auto chainedEffect = ParseChainedTransition(obj, info.GetExecutionContext());
        std::function<void(bool)> finishCallback;
        if (info.Length() > 2 && info[2]->IsFunction()) {
            finishCallback =
                ParseTransitionCallback(JSRef<JSFunc>::Cast(info[2]), info.GetExecutionContext(), frameNode);
        }
        ViewAbstract::SetChainedTransition(frameNode, chainedEffect, std::move(finishCallback));
        return panda::JSValueRef::Undefined(vm);
    }
    auto options = ParseJsTransition(info[1]);
    ViewAbstract::SetTransition(frameNode, options);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetTransitionPassThrough(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    return CommonBridge::ResetTransition(runtimeCallInfo);
}

ArkUINativeModuleValue CommonBridge::SetTransitionPassThrough(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    return CommonBridge::SetTransition(runtimeCallInfo);
}

ArkUINativeModuleValue CommonBridge::ResetSharedTransition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    if (!info[1]->IsString() || info[1]->ToString().empty()) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto id = info[1]->ToString();
    std::shared_ptr<SharedTransitionOption> sharedOption;
    sharedOption = std::make_shared<SharedTransitionOption>();
    sharedOption->duration = DEFAULT_DURATION;
    sharedOption->delay = NUM_0;
    sharedOption->curve = Curves::LINEAR;
    sharedOption->zIndex = NUM_0;
    sharedOption->type = DEFAULT_SHARED_EFFECT;

    ViewAbstract::SetSharedTransition(frameNode, id, sharedOption);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetSharedTransition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    if (!info[NUM_1]->IsString() || info[NUM_1]->ToString().empty()) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto id = info[NUM_1]->ToString();
    std::shared_ptr<SharedTransitionOption> sharedOption;
    if (info[NUM_2]->IsObject()) {
        Framework::JSRef<Framework::JSObject> jsObj = Framework::JSRef<Framework::JSObject>::Cast(info[NUM_2]);
        sharedOption = std::make_shared<SharedTransitionOption>();
        sharedOption->duration = jsObj->GetPropertyValue<int32_t>("duration", DEFAULT_DURATION);
        if (sharedOption->duration < 0) {
            sharedOption->duration = DEFAULT_DURATION;
        }
        sharedOption->delay = jsObj->GetPropertyValue<int32_t>("delay", 0);
        if (sharedOption->delay < 0) {
            sharedOption->delay = 0;
        }
        RefPtr<Curve> curve;
        Framework::JSRef<Framework::JSVal> curveArgs = jsObj->GetProperty("curve");
        if (curveArgs->IsString()) {
            curve = Framework::CreateCurve(jsObj->GetPropertyValue<std::string>("curve", "linear"), false);
        } else if (curveArgs->IsObject()) {
            Framework::JSRef<Framework::JSVal> curveString =
                Framework::JSRef<Framework::JSObject>::Cast(curveArgs)->GetProperty("__curveString");
            if (!curveString->IsString()) {
                return panda::JSValueRef::Undefined(vm);
            }
            curve = Framework::CreateCurve(curveString->ToString(), false);
        }
        if (!curve) {
            curve = Curves::LINEAR;
        }
        sharedOption->curve = curve;
        if (jsObj->HasProperty("motionPath")) {
            MotionPathOption motionPathOption;
            if (ParseMotionPath(jsObj->GetProperty("motionPath"), motionPathOption)) {
                sharedOption->motionPathOption = motionPathOption;
            }
        }
        sharedOption->zIndex = jsObj->GetPropertyValue<int32_t>("zIndex", 0);
        int32_t type = jsObj->GetPropertyValue<int32_t>("type", static_cast<int32_t>(DEFAULT_SHARED_EFFECT));
        sharedOption->type = static_cast<SharedTransitionEffectType>(type);
    }
    ViewAbstract::SetSharedTransition(frameNode, id, sharedOption);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CommonBridge::SetMask(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);

    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    if (!info[NUM_1]->IsObject()) {
        ViewAbstract::SetProgressMask(frameNode, nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    auto paramObject = Framework::JSRef<Framework::JSObject>::Cast(info[NUM_1]);
    Framework::JSRef<Framework::JSVal> typeParam = paramObject->GetProperty("type");
    if (!typeParam->IsNull() && !typeParam->IsUndefined() && typeParam->IsString() &&
        typeParam->ToString() == "ProgressMask") {
        ParseJsMaskProperty(frameNode, paramObject);
    } else {
        Framework::JSShapeAbstract* maskShape =
            Framework::JSRef<Framework::JSObject>::Cast(info[NUM_1])->Unwrap<Framework::JSShapeAbstract>();
        if (maskShape == nullptr) {
            return panda::JSValueRef::Undefined(vm);
        };
        ViewAbstractModelNG::RemoveResObj(frameNode, "maskShape");
        ViewAbstract::SetMask(frameNode, maskShape->GetBasicShape());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetMask(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    ViewAbstractModelNG::RemoveResObj(frameNode, "ProgressMask");
    ViewAbstract::SetProgressMask(frameNode, nullptr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetMaskShape(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);

    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    if (!info[NUM_1]->IsObject()) {
        return panda::JSValueRef::Undefined(vm);
    }
    ViewAbstractModelNG::RemoveResObj(frameNode, "maskShape");

    Framework::JSShapeAbstract* maskShape =
        Framework::JSRef<Framework::JSObject>::Cast(info[NUM_1])->Unwrap<Framework::JSShapeAbstract>();
    if (maskShape == nullptr) {
        return panda::JSValueRef::Undefined(vm);
    };
    ViewAbstract::SetMask(frameNode, maskShape->GetBasicShape());

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetMaskShape(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    ViewAbstractModelNG::RemoveResObj(frameNode, "ProgressMask");
    ViewAbstract::SetProgressMask(frameNode, nullptr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetMouseResponseRegion(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    int32_t length = thirdArg->Int32Value(vm);
    ArkUI_Float32 regionArray[length];
    int32_t regionUnits[length];
    if (!ParseResponseRegion(vm, secondArg, regionArray, regionUnits, length)) {
        GetArkUINodeModifiers()->getCommonModifier()->resetMouseResponseRegion(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getCommonModifier()->setMouseResponseRegion(nativeNode, regionArray, regionUnits, length);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetMouseResponseRegion(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetMouseResponseRegion(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetEnabled(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsBoolean()) {
        bool boolValue = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getCommonModifier()->setEnabled(nativeNode, boolValue);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetEnabled(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetEnabled(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetEnabled(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetUseShadowBatching(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> frameNodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> booleanArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(frameNodeArg->ToNativePointer(vm)->Value());
    if (booleanArg->IsBoolean()) {
        bool boolValue = booleanArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getCommonModifier()->setUseShadowBatching(nativeNode, boolValue);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetUseShadowBatching(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetUseShadowBatching(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> frameNodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(frameNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetUseShadowBatching(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetBlendMode(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> frameNodeArg = runtimeCallInfo->GetCallArgRef(0);      // 0: index of parameter frameNode
    Local<JSValueRef> blendModeArg = runtimeCallInfo->GetCallArgRef(1);      // 1: index of parameter blendMode
    Local<JSValueRef> blendApplyTypeArg = runtimeCallInfo->GetCallArgRef(2); // 2: index of parameter blendApplyType
    auto nativeNode = nodePtr(frameNodeArg->ToNativePointer(vm)->Value());
    int32_t blendModeValue = static_cast<int32_t>(OHOS::Ace::BlendMode::NONE);
    int32_t blendApplyTypeValue = static_cast<int32_t>(OHOS::Ace::BlendApplyType::FAST);
    if (blendModeArg->IsNumber()) {
        int32_t blendModeNum = blendModeArg->Int32Value(vm);
        if (blendModeNum >= static_cast<int32_t>(OHOS::Ace::BlendMode::NONE) &&
            blendModeNum <= static_cast<int32_t>(OHOS::Ace::BlendMode::LUMINOSITY)) {
            blendModeValue = blendModeNum;
        } else if (blendModeNum == BACKWARD_COMPAT_MAGIC_NUMBER_OFFSCREEN) {
            blendModeValue = static_cast<int32_t>(OHOS::Ace::BlendMode::SRC_OVER);
            blendApplyTypeValue = static_cast<int32_t>(OHOS::Ace::BlendApplyType::OFFSCREEN);
        }
        if (blendApplyTypeArg->IsNumber()) {
            int32_t blendApplyTypeNum = blendApplyTypeArg->Int32Value(vm);
            if (blendApplyTypeNum >= static_cast<int>(OHOS::Ace::BlendApplyType::FAST) &&
                blendApplyTypeNum <= static_cast<int>(OHOS::Ace::BlendApplyType::OFFSCREEN)) {
                blendApplyTypeValue = blendApplyTypeNum;
            }
        }
        GetArkUINodeModifiers()->getCommonModifier()->setBlendMode(nativeNode, blendModeValue, blendApplyTypeValue);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetBlendMode(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetBlendMode(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> frameNodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(frameNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetBlendMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetAdvancedBlendMode(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> frameNodeArg = runtimeCallInfo->GetCallArgRef(0);      // 0: index of parameter frameNode
    Local<JSValueRef> blendModeArg = runtimeCallInfo->GetCallArgRef(1);      // 1: index of parameter blendMode
    Local<JSValueRef> blendApplyTypeArg = runtimeCallInfo->GetCallArgRef(2); // 2: index of parameter blendApplyType
    CHECK_NULL_RETURN(frameNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(frameNodeArg->ToNativePointer(vm)->Value());
    int32_t blendModeValue = static_cast<int32_t>(OHOS::Ace::BlendMode::NONE);
    int32_t blendApplyTypeValue = static_cast<int32_t>(OHOS::Ace::BlendApplyType::FAST);
    if (blendApplyTypeArg->IsNumber()) {
        int32_t blendApplyTypeNum = blendApplyTypeArg->Int32Value(vm);
        if (blendApplyTypeNum >= static_cast<int>(OHOS::Ace::BlendApplyType::FAST) &&
            blendApplyTypeNum <= static_cast<int>(OHOS::Ace::BlendApplyType::OFFSCREEN)) {
            blendApplyTypeValue = blendApplyTypeNum;
        }
    }
    if (blendModeArg->IsNumber()) {
        int32_t blendModeNum = blendModeArg->Int32Value(vm);
        if (blendModeNum >= static_cast<int32_t>(OHOS::Ace::BlendMode::NONE) &&
            blendModeNum <= static_cast<int32_t>(OHOS::Ace::BlendMode::LUMINOSITY)) {
            blendModeValue = blendModeNum;
        } else if (blendModeNum == BACKWARD_COMPAT_MAGIC_NUMBER_OFFSCREEN) {
            blendModeValue = static_cast<int32_t>(OHOS::Ace::BlendMode::SRC_OVER);
            blendApplyTypeValue = static_cast<int32_t>(OHOS::Ace::BlendApplyType::OFFSCREEN);
        }
        GetArkUINodeModifiers()->getCommonModifier()->setBlendMode(nativeNode, blendModeValue, blendApplyTypeValue);
    } else if (blendModeArg->IsObject(vm)) {
        auto arkBlender = ArkTSUtils::CreateRSBrightnessBlenderFromNapiValue(vm, blendModeArg);
        auto blender = reinterpret_cast<ArkUINodeHandle>(arkBlender);
        GetArkUINodeModifiers()->getCommonModifier()->setBlendModeByBlender(nativeNode, blender, blendApplyTypeValue);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetBlendMode(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetAdvancedBlendMode(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> frameNodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(frameNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(frameNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetBlendMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetMonopolizeEvents(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> frameNodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> booleanArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(frameNodeArg->ToNativePointer(vm)->Value());
    if (booleanArg->IsBoolean()) {
        bool boolValue = booleanArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getCommonModifier()->setMonopolizeEvents(nativeNode, boolValue);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetMonopolizeEvents(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetMonopolizeEvents(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> frameNodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(frameNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetMonopolizeEvents(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetDraggable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsBoolean()) {
        bool boolValue = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getCommonModifier()->setDraggable(nativeNode, boolValue);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetDraggable(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetDraggable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetDraggable(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetAccessibilityGroup(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsBoolean()) {
        bool boolValue = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getCommonModifier()->setAccessibilityGroup(nativeNode, boolValue);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetAccessibilityGroup(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetAccessibilityGroup(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetAccessibilityGroup(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetAccessibilityNextFocusId(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsString(vm)) {
        std::string stringValue = secondArg->ToString(vm)->ToString(vm);
        GetArkUINodeModifiers()->getCommonModifier()->setAccessibilityNextFocusId(nativeNode, stringValue.c_str());
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetAccessibilityNextFocusId(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetAccessibilityNextFocusId(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetAccessibilityNextFocusId(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetAccessibilityDefaultFocus(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsBoolean()) {
        bool boolValue = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getCommonModifier()->setAccessibilityDefaultFocus(nativeNode, boolValue);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetAccessibilityDefaultFocus(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetAccessibilityDefaultFocus(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetAccessibilityDefaultFocus(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetAccessibilityUseSamePage(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);

    if (secondArg->IsUndefined() || !secondArg->IsNumber()) {
        GetArkUINodeModifiers()->getCommonModifier()->resetAccessibilityUseSamePage(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    int32_t intValue = secondArg->Int32Value(vm);
    if (intValue >= 0 && intValue < static_cast<int32_t>(PAGE_MODE_TYPE.size())) {
        bool isFullSilent = static_cast<bool>(PAGE_MODE_TYPE[intValue]);
        GetArkUINodeModifiers()->getCommonModifier()->setAccessibilityUseSamePage(nativeNode, isFullSilent);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetAccessibilityUseSamePage(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetAccessibilityUseSamePage(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetAccessibilityUseSamePage(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetAccessibilityScrollTriggerable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsBoolean()) {
        bool boolValue = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getCommonModifier()->setAccessibilityScrollTriggerable(nativeNode, boolValue);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetAccessibilityScrollTriggerable(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetAccessibilityScrollTriggerable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetAccessibilityScrollTriggerable(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetAccessibilityFocusDrawLevel(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);

    if (secondArg->IsUndefined() || !secondArg->IsNumber()) {
        GetArkUINodeModifiers()->getCommonModifier()->resetAccessibilityFocusDrawLevel(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    int32_t intValue = secondArg->Int32Value(vm);
    if (intValue >= 0 && intValue < static_cast<int32_t>(FOCUS_DRAW_LEVEL.size())) {
        GetArkUINodeModifiers()->getCommonModifier()->setAccessibilityFocusDrawLevel(nativeNode, intValue);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetAccessibilityFocusDrawLevel(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetAccessibilityFocusDrawLevel(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetAccessibilityFocusDrawLevel(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetHoverEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);

    if (secondArg->IsUndefined() || !secondArg->IsNumber()) {
        GetArkUINodeModifiers()->getCommonModifier()->resetHoverEffect(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    int32_t intValue = secondArg->Int32Value(vm);
    GetArkUINodeModifiers()->getCommonModifier()->setHoverEffect(nativeNode, intValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetHoverEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetHoverEffect(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetClickEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> levelArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> scaleArg = runtimeCallInfo->GetCallArgRef(NUM_2);

    int32_t clickEffectLevelValue = 0;
    if (levelArg->IsNumber()) {
        clickEffectLevelValue = levelArg->Int32Value(vm);
        if (clickEffectLevelValue < static_cast<int32_t>(OHOS::Ace::ClickEffectLevel::LIGHT) ||
            clickEffectLevelValue > static_cast<int32_t>(OHOS::Ace::ClickEffectLevel::HEAVY)) {
            clickEffectLevelValue = 0;
        }
    }
    float scaleNumberValue = 0.9f;
    if (!scaleArg->IsNumber()) {
        if ((OHOS::Ace::ClickEffectLevel)clickEffectLevelValue == OHOS::Ace::ClickEffectLevel::MIDDLE ||
            (OHOS::Ace::ClickEffectLevel)clickEffectLevelValue == OHOS::Ace::ClickEffectLevel::HEAVY) {
            scaleNumberValue = 0.95f;
        }
    } else {
        scaleNumberValue = scaleArg->ToNumber(vm)->Value();
        if (LessNotEqual(scaleNumberValue, 0.0) || GreatNotEqual(scaleNumberValue, 1.0)) {
            if ((OHOS::Ace::ClickEffectLevel)clickEffectLevelValue == OHOS::Ace::ClickEffectLevel::MIDDLE ||
                (OHOS::Ace::ClickEffectLevel)clickEffectLevelValue == OHOS::Ace::ClickEffectLevel::HEAVY) {
                scaleNumberValue = 0.95f;
            } else {
                scaleNumberValue = 0.9f;
            }
        }
    }
    GetArkUINodeModifiers()->getCommonModifier()->setClickEffect(nativeNode, clickEffectLevelValue,
        scaleNumberValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetClickEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetClickEffect(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetKeyBoardShortCut(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> keysArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if ((!valueArg->IsString(vm) && !valueArg->IsNumber()) || !keysArg->IsArray(vm)) {
        GetArkUINodeModifiers()->getCommonModifier()->resetKeyBoardShortCut(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    std::string stringValue;
    if (valueArg->IsNumber()) {
        OHOS::Ace::FunctionKey functionkey = static_cast<OHOS::Ace::FunctionKey>(valueArg->Int32Value(vm));
        stringValue = JSViewAbstract::GetFunctionKeyName(functionkey);
    } else {
        stringValue = valueArg->ToString(vm)->ToString(vm);
    }
    Local<panda::ArrayRef> keysArray = static_cast<Local<panda::ArrayRef>>(keysArg);
    auto arrLength = keysArray->Length(vm);
    if (arrLength > NUM_10) {
        arrLength = NUM_10;
    }
    std::vector<OHOS::Ace::ModifierKey> keysVector(arrLength);
    for (uint32_t i = 0; i < arrLength; i++) {
        Local<JSValueRef> objValue = keysArray->GetValueAt(vm, keysArg, i);
        keysVector.emplace_back(static_cast<OHOS::Ace::ModifierKey>(objValue->Int32Value(vm)));
    }
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    if (runtimeCallInfo->GetArgsNumber() == NUM_4) {
        Local<JSValueRef> actionArg = runtimeCallInfo->GetCallArgRef(NUM_3);
        auto obj = actionArg->ToObject(vm);
        auto containerId = Container::CurrentId();
        panda::Local<panda::FunctionRef> func = obj;
        auto flag = FrameNodeBridge::IsCustomFrameNode(frameNode);
        auto onActionFunc = [vm, func = JSFuncObjRef(panda::CopyableGlobal(vm, func), flag),
                                node = AceType::WeakClaim(frameNode), containerId]() {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            ContainerScope scope(containerId);
            auto function = func.Lock();
            CHECK_NULL_VOID(!function.IsEmpty());
            CHECK_NULL_VOID(function->IsFunction(vm));
            PipelineContext::SetCallBackNode(node);
            function->Call(vm, function.ToLocal(), nullptr, 0);
        };
        ViewAbstractModelNG::SetKeyboardShortcut(frameNode, stringValue, keysVector, std::move(onActionFunc));
        return panda::JSValueRef::Undefined(vm);
    }
    ViewAbstractModelNG::SetKeyboardShortcut(frameNode, stringValue, keysVector, nullptr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetKeyBoardShortCut(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetKeyBoardShortCut(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

RefPtr<ResourceWrapper> CreateResourceWrapper()
{
    RefPtr<ResourceAdapter> resourceAdapter = nullptr;
    RefPtr<ThemeConstants> themeConstants = nullptr;
    if (SystemProperties::GetResourceDecoupling()) {
        resourceAdapter = ResourceManager::GetInstance().GetResourceAdapter(Container::CurrentIdSafely());
        if (!resourceAdapter) {
            return nullptr;
        }
    } else {
        themeConstants = JSViewAbstract::GetThemeConstants();
        if (!themeConstants) {
            return nullptr;
        }
    }
    auto resourceWrapper = AceType::MakeRefPtr<ResourceWrapper>(themeConstants, resourceAdapter);
    return resourceWrapper;
}

bool ParseLightPosition(ArkUIRuntimeCallInfo *runtimeCallInfo, EcmaVM* vm, ArkUISizeType& dimPosX,
    ArkUISizeType& dimPosY, ArkUISizeType& dimPosZ, std::vector<RefPtr<ResourceObject>>& vectorResObj)
{
    Local<JSValueRef> positionXArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> positionYArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> positionZArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    CalcDimension dimPositionX;
    CalcDimension dimPositionY;
    CalcDimension dimPositionZ;
    RefPtr<ResourceObject> xResObj;
    RefPtr<ResourceObject> yResObj;
    RefPtr<ResourceObject> zResObj;
    bool xSuccess = ArkTSUtils::ParseJsDimensionVp(vm, positionXArg, dimPositionX, xResObj, false);
    bool ySuccess = ArkTSUtils::ParseJsDimensionVp(vm, positionYArg, dimPositionY, yResObj, false);
    bool zSuccess = ArkTSUtils::ParseJsDimensionVp(vm, positionZArg, dimPositionZ, zResObj, false);
    if (!(xSuccess && ySuccess && zSuccess)) {
        return false;
    }
    if (xResObj) {
        vectorResObj.emplace_back(xResObj);
    } else {
        vectorResObj.emplace_back(nullptr);
    }
    if (yResObj) {
        vectorResObj.emplace_back(yResObj);
    } else {
        vectorResObj.emplace_back(nullptr);
    }
    if (zResObj) {
        vectorResObj.emplace_back(zResObj);
    } else {
        vectorResObj.emplace_back(nullptr);
    }
    dimPosX.value = dimPositionX.Value();
    dimPosX.unit = static_cast<int8_t>(dimPositionX.Unit());
    dimPosY.value = dimPositionY.Value();
    dimPosY.unit = static_cast<int8_t>(dimPositionY.Unit());
    dimPosZ.value = dimPositionZ.Value();
    dimPosZ.unit = static_cast<int8_t>(dimPositionZ.Unit());
    return true;
}

void ParseLightSource(ArkUIRuntimeCallInfo *runtimeCallInfo, EcmaVM* vm, ArkUINodeHandle nativeNode)
{
    struct ArkUISizeType dimPosX = { 0.0, 0 };
    struct ArkUISizeType dimPosY = { 0.0, 0 };
    struct ArkUISizeType dimPosZ = { 0.0, 0 };
    std::vector<RefPtr<ResourceObject>> vectorResObj;
    bool success  = ParseLightPosition(runtimeCallInfo, vm, dimPosX, dimPosY, dimPosZ, vectorResObj);
    if (success) {
        auto resRawPtr = static_cast<void*>(&vectorResObj);
        GetArkUINodeModifiers()->getCommonModifier()->setPointLightPosition(
            nativeNode, &dimPosX, &dimPosY, &dimPosZ, resRawPtr);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetPointLightPosition(nativeNode);
    }

    Local<JSValueRef> intensityArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    if (intensityArg->IsNumber()) {
        auto intensityValue = static_cast<ArkUI_Float32>((intensityArg->ToNumber(vm)->Value()));
        GetArkUINodeModifiers()->getCommonModifier()->setPointLightIntensity(nativeNode, intensityValue);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetPointLightIntensity(nativeNode);
    }

    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    Color colorValue;
    RefPtr<ResourceObject> colorResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (ArkTSUtils::ParseJsColorAlpha(vm, colorArg, colorValue, colorResObj, nodeInfo)) {
        auto colorRawPtr = AceType::RawPtr(colorResObj);
        GetArkUINodeModifiers()->getCommonModifier()->setPointLightColor(nativeNode, colorValue.GetValue(), colorRawPtr);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetPointLightColor(nativeNode);
    }
}

ArkUINativeModuleValue CommonBridge::SetPointLightStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
#ifdef POINT_LIGHT_ENABLE
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    ParseLightSource(runtimeCallInfo, vm, nativeNode);

    auto resourceWrapper = CreateResourceWrapper();
    Local<JSValueRef> illuminatedArg = runtimeCallInfo->GetCallArgRef(NUM_6);
    if (illuminatedArg->IsNumber() || !resourceWrapper) {
        auto illuminatedValue = static_cast<ArkUI_Uint32>(illuminatedArg->ToNumber(vm)->Value());
        Dimension illuminatedBorderWidth = resourceWrapper->GetDimensionByName(ILLUMINATED_BORDER_WIDTH_SYS_RES_NAME);
        struct ArkUISizeType illuminatedBorderWidthValue = { 0.0, 0 };
        illuminatedBorderWidthValue.value = illuminatedBorderWidth.Value();
        illuminatedBorderWidthValue.unit = static_cast<int8_t>(illuminatedBorderWidth.Unit());
        GetArkUINodeModifiers()->getCommonModifier()->setPointLightIlluminated(
            nativeNode, illuminatedValue, &illuminatedBorderWidthValue);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetPointLightIlluminated(nativeNode);
    }

    Local<JSValueRef> bloomArg = runtimeCallInfo->GetCallArgRef(NUM_7);
    if (bloomArg->IsNumber() || !resourceWrapper) {
        auto bloomValue = static_cast<ArkUI_Float32>(bloomArg->ToNumber(vm)->Value());
        double bloomRadius = resourceWrapper->GetDoubleByName(BLOOM_RADIUS_SYS_RES_NAME);
        Color bloomColor = resourceWrapper->GetColorByName(BLOOM_COLOR_SYS_RES_NAME);
        GetArkUINodeModifiers()->getCommonModifier()->setPointLightBloom(nativeNode, bloomValue,
            static_cast<ArkUI_Float32>(bloomRadius), static_cast<ArkUI_Uint32>(bloomColor.GetValue()));
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetPointLightBloom(nativeNode);
    }
#endif
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetPointLightStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
#ifdef POINT_LIGHT_ENABLE
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetPointLightPosition(nativeNode);
    GetArkUINodeModifiers()->getCommonModifier()->resetPointLightIntensity(nativeNode);
    GetArkUINodeModifiers()->getCommonModifier()->resetPointLightColor(nativeNode);
    GetArkUINodeModifiers()->getCommonModifier()->resetPointLightIlluminated(nativeNode);
    GetArkUINodeModifiers()->getCommonModifier()->resetPointLightBloom(nativeNode);
#endif
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetClipWithEdge(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto *frameNode = reinterpret_cast<FrameNode *>(nativeNode);

    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    if (info[NUM_1]->IsUndefined()) {
        ViewAbstract::SetClipEdge(frameNode, true);
        return panda::JSValueRef::Undefined(vm);
    }
    if (info[NUM_1]->IsObject()) {
        Framework::JSShapeAbstract *clipShape =
            Framework::JSRef<Framework::JSObject>::Cast(info[NUM_1])->Unwrap<Framework::JSShapeAbstract>();
        if (clipShape == nullptr) {
            return panda::JSValueRef::Undefined(vm);
        }
        ViewAbstract::SetClipShape(frameNode, clipShape->GetBasicShape());
    } else if (info[NUM_1]->IsBoolean()) {
        ViewAbstract::SetClipEdge(frameNode, info[NUM_1]->ToBoolean());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetClipWithEdge(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto *frameNode = reinterpret_cast<FrameNode *>(nativeNode);
    ViewAbstract::SetClipEdge(frameNode, true);
    return panda::JSValueRef::Undefined(vm);
}

FrameNode* CommonBridge::GetFrameNode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, nullptr);
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull() && firstArg->IsNativePointer(vm), nullptr);
    auto* nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, nullptr);
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    return frameNode;
}

Local<panda::ObjectRef> CommonBridge::CreateChangeValueInfoObj(EcmaVM* vm, const ChangeValueInfo& changeValueInfo)
{
    const char* previewTextKeys[] = { "value", "offset" };
    Local<JSValueRef> previewTextValues[] = {
        panda::StringRef::NewFromUtf16(vm, changeValueInfo.previewText.value.c_str()),
        panda::NumberRef::New(vm, changeValueInfo.previewText.offset) };
    auto previewTextObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(previewTextKeys),
        previewTextKeys, previewTextValues);

    const char* rangeKeys[] = { "start", "end" };
    Local<JSValueRef> rangeBeforeValues[] = {
        panda::NumberRef::New(vm, changeValueInfo.rangeBefore.start),
        panda::NumberRef::New(vm, changeValueInfo.rangeBefore.end) };
    auto rangeBeforeObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(rangeKeys),
        rangeKeys, rangeBeforeValues);
    Local<JSValueRef> rangeAfterValues[] = {
        panda::NumberRef::New(vm, changeValueInfo.rangeAfter.start),
        panda::NumberRef::New(vm, changeValueInfo.rangeAfter.end) };
    auto rangeAfterObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(rangeKeys),
        rangeKeys, rangeAfterValues);
    Local<JSValueRef> oldPreviewTextValues[] = {
        panda::StringRef::NewFromUtf16(vm, changeValueInfo.oldPreviewText.value.c_str()),
        panda::NumberRef::New(vm, changeValueInfo.oldPreviewText.offset) };
    auto oldPreviewTextObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(previewTextKeys),
        previewTextKeys, oldPreviewTextValues);

    const char* optionsKeys[] = { "rangeBefore", "rangeAfter", "oldContent", "oldPreviewText" };
    Local<JSValueRef> optionsValues[] = { rangeBeforeObj, rangeAfterObj,
        panda::StringRef::NewFromUtf16(vm, changeValueInfo.oldContent.c_str()), oldPreviewTextObj };
    auto optionsObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(optionsKeys),
        optionsKeys, optionsValues);

    const char* changeValueInfoKeys[] = { "content", "previewText", "options" };
    Local<JSValueRef> changeValueInfoValues[] = { panda::StringRef::NewFromUtf16(vm, changeValueInfo.value.c_str()),
        previewTextObj, optionsObj };
    auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(changeValueInfoKeys),
        changeValueInfoKeys, changeValueInfoValues);
    return eventObject;
}

Local<panda::ObjectRef> CommonBridge::CreateGestureInfo(EcmaVM* vm, const RefPtr<NG::GestureInfo>& gestureInfo)
{
    if (gestureInfo->GetTag().has_value()) {
        const char* keys[] = { "tag", "type", "isSystemGesture" };
        Local<JSValueRef> values[] = { panda::StringRef::NewFromUtf8(vm, gestureInfo->GetTag().value().c_str()),
            panda::NumberRef::New(vm, static_cast<int32_t>(gestureInfo->GetType())),
            panda::BooleanRef::New(vm, gestureInfo->IsSystemGesture()) };
        return panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
    }
    const char* keys[] = { "type", "isSystemGesture" };
    Local<JSValueRef> values[] = { panda::NumberRef::New(vm, static_cast<int32_t>(gestureInfo->GetType())),
        panda::BooleanRef::New(vm, gestureInfo->IsSystemGesture()) };
    return panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
}

Local<panda::ObjectRef> CommonBridge::CreateGestureEventInfo(
    EcmaVM* vm, GestureTypeName typeName, const std::shared_ptr<BaseGestureEvent>& info)
{
    auto obj = SetUniqueAttributes(vm, typeName, info);
    SetCommonAttributes(obj, vm, info);
    auto fingerArr = panda::ArrayRef::New(vm);
    const std::list<FingerInfo>& fingerList = info->GetFingerList();
    std::list<FingerInfo> notTouchFingerList;
    int32_t maxFingerId = -1;
    for (const FingerInfo& fingerInfo : fingerList) {
        auto element = CreateFingerInfo(vm, fingerInfo);
        if (fingerInfo.sourceType_ == SourceType::TOUCH && fingerInfo.sourceTool_ == SourceTool::FINGER) {
            fingerArr->SetValueAt(vm, fingerArr, fingerInfo.fingerId_, element);
            if (fingerInfo.fingerId_ > maxFingerId) {
                maxFingerId = fingerInfo.fingerId_;
            }
        } else {
            notTouchFingerList.emplace_back(fingerInfo);
        }
    }
    auto idx = maxFingerId + 1;
    for (const FingerInfo& fingerInfo : notTouchFingerList) {
        auto element = CreateFingerInfo(vm, fingerInfo);
        fingerArr->SetValueAt(vm, fingerArr, idx++, element);
    }
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "fingerList"), fingerArr);
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "target"), CreateEventTargetObject(vm, info));
    CreateFingerInfosInfo(vm, info, obj);
    obj->SetNativePointerFieldCount(vm, 1);
    obj->SetNativePointerField(vm, 0, static_cast<void*>(info.get()));
    return obj;
}

void CommonBridge::SetCommonAttributes(
    Local<panda::ObjectRef>& obj, EcmaVM* vm, const std::shared_ptr<BaseGestureEvent>& info)
{
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "timestamp"),
        panda::NumberRef::New(vm, static_cast<double>(info->GetTimeStamp().time_since_epoch().count())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "source"),
        panda::NumberRef::New(vm, static_cast<int32_t>(info->GetSourceDevice())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "pressure"), panda::NumberRef::New(vm, info->GetForce()));
    if (info->GetTiltX().has_value()) {
        obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "tiltX"), panda::NumberRef::New(vm, info->GetTiltX().value()));
    }
    if (info->GetTiltY().has_value()) {
        obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "tiltY"), panda::NumberRef::New(vm, info->GetTiltY().value()));
    }
    if (info->GetRollAngle().has_value()) {
        obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "rollAngle"),
            panda::NumberRef::New(vm, info->GetRollAngle().value()));
    }
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "sourceTool"),
        panda::NumberRef::New(vm, static_cast<int32_t>(info->GetSourceTool())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "deviceId"),
        panda::NumberRef::New(vm, static_cast<int32_t>(info->GetDeviceId())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "targetDisplayId"),
        panda::NumberRef::New(vm, static_cast<int32_t>(info->GetTargetDisplayId())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "axisVertical"), panda::NumberRef::New(vm, info->GetVerticalAxis()));
    obj->Set(
        vm, panda::StringRef::NewFromUtf8(vm, "axisHorizontal"), panda::NumberRef::New(vm, info->GetHorizontalAxis()));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "getModifierKeyState"),
        panda::FunctionRef::New(vm, ArkTSUtils::JsGetModifierKeyState));
}

Local<panda::ObjectRef> CommonBridge::CreateGestureEventInfo(EcmaVM* vm, const std::shared_ptr<BaseGestureEvent>& info)
{
    auto obj = panda::ObjectRef::New(vm);
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "timestamp"),
        panda::NumberRef::New(vm, static_cast<double>(info->GetTimeStamp().time_since_epoch().count())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "source"),
        panda::NumberRef::New(vm, static_cast<int32_t>(info->GetSourceDevice())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "pressure"), panda::NumberRef::New(vm, info->GetForce()));
    if (info->GetTiltX().has_value()) {
        obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "tiltX"), panda::NumberRef::New(vm, info->GetTiltX().value()));
    }
    if (info->GetTiltY().has_value()) {
        obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "tiltY"), panda::NumberRef::New(vm, info->GetTiltY().value()));
    }
    if (info->GetRollAngle().has_value()) {
        obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "rollAngle"),
            panda::NumberRef::New(vm, info->GetRollAngle().value()));
    }
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "sourceTool"),
        panda::NumberRef::New(vm, static_cast<int32_t>(info->GetSourceTool())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "deviceId"),
        panda::NumberRef::New(vm, static_cast<int32_t>(info->GetDeviceId())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "targetDisplayId"),
        panda::NumberRef::New(vm, static_cast<int32_t>(info->GetTargetDisplayId())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "axisVertical"), panda::NumberRef::New(vm, info->GetVerticalAxis()));
    obj->Set(
        vm, panda::StringRef::NewFromUtf8(vm, "axisHorizontal"), panda::NumberRef::New(vm, info->GetHorizontalAxis()));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "getModifierKeyState"),
        panda::FunctionRef::New(vm, ArkTSUtils::JsGetModifierKeyState));

    auto fingerArr = panda::ArrayRef::New(vm);
    const std::list<FingerInfo>& fingerList = info->GetFingerList();
    std::list<FingerInfo> notTouchFingerList;
    int32_t maxFingerId = -1;
    for (const FingerInfo& fingerInfo : fingerList) {
        auto element = CreateFingerInfo(vm, fingerInfo);
        if (fingerInfo.sourceType_ == SourceType::TOUCH && fingerInfo.sourceTool_ == SourceTool::FINGER) {
            fingerArr->SetValueAt(vm, fingerArr, fingerInfo.fingerId_, element);
            if (fingerInfo.fingerId_ > maxFingerId) {
                maxFingerId = fingerInfo.fingerId_;
            }
        } else {
            notTouchFingerList.emplace_back(fingerInfo);
        }
    }
    auto idx = maxFingerId + 1;
    for (const FingerInfo& fingerInfo : notTouchFingerList) {
        auto element = CreateFingerInfo(vm, fingerInfo);
        fingerArr->SetValueAt(vm, fingerArr, idx++, element);
    }
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "fingerList"), fingerArr);
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "target"), CreateEventTargetObject(vm, info));
    CreateFingerInfosInfo(vm, info, obj);
    obj->SetNativePointerFieldCount(vm, 1);
    obj->SetNativePointerField(vm, 0, static_cast<void*>(info.get()));
    return obj;
}

Local<panda::ObjectRef> CommonBridge::CreateFingerInfosInfo(
    EcmaVM* vm, const std::shared_ptr<BaseGestureEvent>& info, Local<panda::ObjectRef>& obj)
{
    auto fingerArr = panda::ArrayRef::New(vm);
    const std::list<FingerInfo>& fingerList = info->GetFingerList();
    std::list<FingerInfo> notTouchFingerList;
    std::vector<Local<panda::ObjectRef>> validFingers;
    for (const FingerInfo& fingerInfo : fingerList) {
        auto element = CreateFingerInfo(vm, fingerInfo);
        if (fingerInfo.sourceType_ == SourceType::TOUCH && fingerInfo.sourceTool_ == SourceTool::FINGER) {
            validFingers.emplace_back(element);
        } else {
            notTouchFingerList.emplace_back(fingerInfo);
        }
    }
    for (size_t i = 0; i < validFingers.size(); ++i) {
        fingerArr->SetValueAt(vm, fingerArr, i, validFingers[i]);
    }
    auto idx = validFingers.size();
    for (const FingerInfo& fingerInfo : notTouchFingerList) {
        auto element = CreateFingerInfo(vm, fingerInfo);
        fingerArr->SetValueAt(vm, fingerArr, idx++, element);
    }
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "fingerInfos"), fingerArr);
    return obj;
}

Local<panda::ObjectRef> CommonBridge::SetUniqueAttributes(
    EcmaVM* vm, GestureTypeName typeName, const std::shared_ptr<BaseGestureEvent>& info)
{
    double density = PipelineBase::GetCurrentDensity();
    switch (typeName) {
        case OHOS::Ace::GestureTypeName::TAP_GESTURE: {
            const char* keys[] = { "tapLocation" };
            Local<JSValueRef> values[] = { CreateTapGestureLocationInfo(vm,info) };
            return panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        }
        case OHOS::Ace::GestureTypeName::LONG_PRESS_GESTURE: {
            auto* longPressGestureEvent = TypeInfoHelper::DynamicCast<LongPressGestureEvent>(info.get());
            if (longPressGestureEvent) {
                const char* keys[] = { "repeat" };
                Local<JSValueRef> values[] = { panda::BooleanRef::New(vm, longPressGestureEvent->GetRepeat()) };
                return panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
            }
            return panda::ObjectRef::New(vm);
        }
        case OHOS::Ace::GestureTypeName::PAN_GESTURE: {
            auto* panGestureEvent = TypeInfoHelper::DynamicCast<PanGestureEvent>(info.get());
            if (panGestureEvent) {
                const char* keys[] = { "offsetX", "offsetY", "velocityX", "velocityY", "velocity" };
                Local<JSValueRef> values[] = { panda::NumberRef::New(vm, panGestureEvent->GetOffsetX() / density),
                    panda::NumberRef::New(vm, panGestureEvent->GetOffsetY() / density),
                    panda::NumberRef::New(vm, panGestureEvent->GetVelocity().GetVelocityX() / density),
                    panda::NumberRef::New(vm, panGestureEvent->GetVelocity().GetVelocityY() / density),
                    panda::NumberRef::New(vm, panGestureEvent->GetVelocity().GetVelocityValue() / density) };
                return panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
            }
            return panda::ObjectRef::New(vm);
        }
        case OHOS::Ace::GestureTypeName::PINCH_GESTURE: {
            auto* pinchGestureEvent = TypeInfoHelper::DynamicCast<PinchGestureEvent>(info.get());
            if (pinchGestureEvent) {
                const char* keys[] = { "scale", "pinchCenterX", "pinchCenterY" };
                Local<JSValueRef> values[] = { panda::NumberRef::New(vm, pinchGestureEvent->GetScale()),
                    panda::NumberRef::New(vm, pinchGestureEvent->GetPinchCenter().GetX() / density),
                    panda::NumberRef::New(vm, pinchGestureEvent->GetPinchCenter().GetY() / density) };
                return panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
            }
            return panda::ObjectRef::New(vm);
        }
        case OHOS::Ace::GestureTypeName::ROTATION_GESTURE: {
            auto* rotationGestureEvent = TypeInfoHelper::DynamicCast<RotationGestureEvent>(info.get());
            if (rotationGestureEvent) {
                const char* keys[] = { "angle" };
                Local<JSValueRef> values[] = { panda::NumberRef::New(vm, rotationGestureEvent->GetAngle()) };
                return panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
            }
            return panda::ObjectRef::New(vm);
        }
        case OHOS::Ace::GestureTypeName::SWIPE_GESTURE: {
            auto* swipeGestureEvent = TypeInfoHelper::DynamicCast<SwipeGestureEvent>(info.get());
            if (swipeGestureEvent) {
                const char* keys[] = { "angle", "speed" };
                Local<JSValueRef> values[] = { panda::NumberRef::New(vm, swipeGestureEvent->GetAngle()),
                    panda::NumberRef::New(vm, swipeGestureEvent->GetSpeed()) };
                return panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
            }
            return panda::ObjectRef::New(vm);
        }
        default:
            return panda::ObjectRef::New(vm);
    }
}

Local<panda::ObjectRef> CommonBridge::CreateRecognizerObject(EcmaVM* vm, const RefPtr<NG::NGGestureRecognizer>& target)
{
    auto panRecognizer = AceType::DynamicCast<NG::PanRecognizer>(target);
    if (panRecognizer) {
        JSRef<JSObject> recognizerObj = JSClass<JSPanRecognizer>::NewInstance();
        auto currentRecognizer = Referenced::Claim(recognizerObj->Unwrap<JSPanRecognizer>());
        currentRecognizer->Update(panRecognizer);
        return recognizerObj->GetLocalHandle();
    }
    auto pinchRecognizer = AceType::DynamicCast<NG::PinchRecognizer>(target);
    if (pinchRecognizer) {
        JSRef<JSObject> recognizerObj = JSClass<JSPinchRecognizer>::NewInstance();
        auto currentRecognizer = Referenced::Claim(recognizerObj->Unwrap<JSPinchRecognizer>());
        currentRecognizer->Update(pinchRecognizer);
        return recognizerObj->GetLocalHandle();
    }
    auto tapRecognizer = AceType::DynamicCast<NG::ClickRecognizer>(target);
    if (tapRecognizer) {
        JSRef<JSObject> recognizerObj = JSClass<JSTapRecognizer>::NewInstance();
        auto currentRecognizer = Referenced::Claim(recognizerObj->Unwrap<JSTapRecognizer>());
        currentRecognizer->Update(tapRecognizer);
        return recognizerObj->GetLocalHandle();
    }
    auto longPressRecognizer = AceType::DynamicCast<NG::LongPressRecognizer>(target);
    if (longPressRecognizer) {
        JSRef<JSObject> recognizerObj = JSClass<JSLongPressRecognizer>::NewInstance();
        auto currentRecognizer = Referenced::Claim(recognizerObj->Unwrap<JSLongPressRecognizer>());
        currentRecognizer->Update(longPressRecognizer);
        return recognizerObj->GetLocalHandle();
    }
    auto rotationRecognizer = AceType::DynamicCast<NG::RotationRecognizer>(target);
    if (rotationRecognizer) {
        JSRef<JSObject> recognizerObj = JSClass<JSRotationRecognizer>::NewInstance();
        auto currentRecognizer = Referenced::Claim(recognizerObj->Unwrap<JSRotationRecognizer>());
        currentRecognizer->Update(rotationRecognizer);
        return recognizerObj->GetLocalHandle();
    }
    auto swipeRecognizer = AceType::DynamicCast<NG::SwipeRecognizer>(target);
    if (swipeRecognizer) {
        JSRef<JSObject> recognizerObj = JSClass<JSSwipeRecognizer>::NewInstance();
        auto currentRecognizer = Referenced::Claim(recognizerObj->Unwrap<JSSwipeRecognizer>());
        currentRecognizer->Update(swipeRecognizer);
        return recognizerObj->GetLocalHandle();
    }
    JSRef<JSObject> recognizerObj = JSClass<JSGestureRecognizer>::NewInstance();
    auto currentRecognizer = Referenced::Claim(recognizerObj->Unwrap<JSGestureRecognizer>());
    currentRecognizer->Update(target);
    return recognizerObj->GetLocalHandle();
}

Local<panda::ObjectRef> CommonBridge::CreateTapGestureInfo(EcmaVM* vm, GestureEvent& info)
{
    if (info.GetFingerList().empty()) {
        return panda::ObjectRef::New(vm);
    }
    auto fingerInfo = info.GetFingerList().back();
    const OHOS::Ace::Offset& localLocation = fingerInfo.localLocation_;
    const OHOS::Ace::Offset& globalLocation = fingerInfo.globalLocation_;
    const OHOS::Ace::Offset& screenLocation = fingerInfo.screenLocation_;
    const OHOS::Ace::Offset& globalDisplayLocation = fingerInfo.globalDisplayLocation_;
    const char* keys[] = { "x", "y", "windowX", "windowY", "displayX", "displayY",
                           "globalDisplayX", "globalDisplayY"};
    Local<JSValueRef> values[] = {
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(localLocation.GetX())),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(localLocation.GetY())),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(globalLocation.GetX())),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(globalLocation.GetY())),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(screenLocation.GetX())),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(screenLocation.GetY())),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(globalDisplayLocation.GetX())),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(globalDisplayLocation.GetY())),
    };
    return panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
}

Local<panda::ArrayRef> CommonBridge::CreateTouchRecognizersObject(
    EcmaVM* vm, const std::shared_ptr<BaseGestureEvent>& info, const RefPtr<NG::NGGestureRecognizer>& target)
{
    auto touchRecognizers = panda::ArrayRef::New(vm);
    auto frameNode = target->GetAttachedNode().Upgrade();
    CHECK_NULL_RETURN(frameNode, touchRecognizers);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_RETURN(pipeline, touchRecognizers);
    auto eventManager = pipeline->GetEventManager();
    CHECK_NULL_RETURN(eventManager, touchRecognizers);
    auto& touchTestResult = eventManager->touchTestResults_;
    TouchRecognizerMap touchRecognizerMap;
    const auto& fingerList = info->GetFingerList();
    for (const auto& finger : fingerList) {
        auto& touchTargetList = touchTestResult[finger.fingerId_];
        CollectTouchEventTarget(touchRecognizerMap, touchTargetList, AceType::RawPtr(frameNode), finger.fingerId_);
    }
    uint32_t touchRecognizersIdx = 0;
    for (auto& [item, fingerIds] : touchRecognizerMap) {
        JSRef<JSObject> recognizerObj = JSClass<JSTouchRecognizer>::NewInstance();
        auto jsRecognizer = Referenced::Claim(recognizerObj->Unwrap<JSTouchRecognizer>());
        if (jsRecognizer) {
            jsRecognizer->SetTouchData(item, fingerIds);
        }
        touchRecognizers->SetValueAt(vm, touchRecognizers, touchRecognizersIdx++, recognizerObj->GetLocalHandle());
    }
    return touchRecognizers;
}

TouchRecognizerMap CommonBridge::CreateTouchRecognizerMap(
    const std::shared_ptr<BaseGestureEvent>& info, const RefPtr<NG::NGGestureRecognizer>& current)
{
    TouchRecognizerMap touchRecognizerMap;
    auto frameNode = current->GetAttachedNode().Upgrade();
    CHECK_NULL_RETURN(frameNode, touchRecognizerMap);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_RETURN(pipeline, touchRecognizerMap);
    auto eventManager = pipeline->GetEventManager();
    CHECK_NULL_RETURN(eventManager, touchRecognizerMap);
    auto& touchTestResult = eventManager->touchTestResults_;
    const auto& fingerList = info->GetFingerList();
    for (const auto& finger : fingerList) {
        auto& touchTargetList = touchTestResult[finger.fingerId_];
        CollectTouchEventTarget(touchRecognizerMap, touchTargetList, AceType::RawPtr(frameNode), finger.fingerId_);
    }
    return touchRecognizerMap;
}

void CommonBridge::CollectTouchEventTarget(
    TouchRecognizerMap& dict, std::list<RefPtr<TouchEventTarget>>& targets, NG::FrameNode* frameNode, int32_t fingerId)
{
    for (auto& target : targets) {
        if (AceType::DynamicCast<NG::NGGestureRecognizer>(target)) {
            continue;
        }
        auto weakTarget = WeakPtr<TouchEventTarget>(target);
        if (dict.find(weakTarget) != dict.end() && dict[weakTarget].count(fingerId) > 0) {
            continue;
        }
        auto targetNode = target->GetAttachedNode().Upgrade();
        if (targetNode && targetNode == frameNode) {
            dict[weakTarget].insert(fingerId);
            return;
        }
        while (targetNode) {
            if (targetNode == frameNode) {
                dict[weakTarget].insert(fingerId);
                break;
            }
            targetNode = targetNode->GetParentFrameNode();
        }
    }
}

Local<panda::ObjectRef> CommonBridge::CreateFingerInfo(EcmaVM* vm, const FingerInfo& fingerInfo)
{
    const OHOS::Ace::Offset& globalLocation = fingerInfo.globalLocation_;
    const OHOS::Ace::Offset& localLocation = fingerInfo.localLocation_;
    const OHOS::Ace::Offset& screenLocation = fingerInfo.screenLocation_;
    const OHOS::Ace::Offset& globalDisplayLocation  = fingerInfo.globalDisplayLocation_;
    double density = PipelineBase::GetCurrentDensity();
    const char* keys[] = { "id", "globalX", "globalY", "localX", "localY", "displayX", "displayY",
                           "globalDisplayX", "globalDisplayY", "hand" };
    Local<JSValueRef> values[] = { panda::NumberRef::New(vm, fingerInfo.fingerId_),
        panda::NumberRef::New(vm, globalLocation.GetX() / density),
        panda::NumberRef::New(vm, globalLocation.GetY() / density),
        panda::NumberRef::New(vm, localLocation.GetX() / density),
        panda::NumberRef::New(vm, localLocation.GetY() / density),
        panda::NumberRef::New(vm, screenLocation.GetX() / density),
        panda::NumberRef::New(vm, screenLocation.GetY() / density),
        panda::NumberRef::New(vm, globalDisplayLocation.GetX() / density),
        panda::NumberRef::New(vm, globalDisplayLocation.GetY() / density),
        panda::NumberRef::New(vm, fingerInfo.operatingHand_) };
        return panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
}

Local<panda::ObjectRef> CommonBridge::CreateEventTargetObject(EcmaVM* vm, const std::shared_ptr<BaseGestureEvent>& info)
{
    const auto& localOffset = info->GetTarget().area.GetOffset();
    const auto& origin = info->GetTarget().origin;
    const char* keysOfOffset[] = { "x", "y" };
    Local<JSValueRef> valuesOfOffset[] = { panda::NumberRef::New(vm, localOffset.GetX().ConvertToVp()),
        panda::NumberRef::New(vm, localOffset.GetY().ConvertToVp()) };
    auto offset = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keysOfOffset), keysOfOffset, valuesOfOffset);

    const char* keysOfGlobalOffset[] = { "x", "y" };
    Local<JSValueRef> valuesOfGlobalOffset[] = { panda::NumberRef::New(
        vm, (origin.GetX() + localOffset.GetX()).ConvertToVp()),
        panda::NumberRef::New(vm, (origin.GetY() + localOffset.GetY()).ConvertToVp()) };
    auto globalOffset = panda::ObjectRef::NewWithNamedProperties(
        vm, ArraySize(keysOfGlobalOffset), keysOfGlobalOffset, valuesOfGlobalOffset);
    const char* keysOfArea[] = { "position", "globalPosition", "width", "height" };
    Local<JSValueRef> valuesOfArea[] = { offset, globalOffset,
        panda::NumberRef::New(vm, info->GetTarget().area.GetWidth().ConvertToVp()),
        panda::NumberRef::New(vm, info->GetTarget().area.GetHeight().ConvertToVp()) };
    auto area = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keysOfArea), keysOfArea, valuesOfArea);
    auto target = panda::ObjectRef::New(vm);
    target->Set(vm, panda::StringRef::NewFromUtf8(vm, "area"), area);
    if (info->GetTarget().id.empty()) {
        target->Set(vm, panda::StringRef::NewFromUtf8(vm, "id"), panda::JSValueRef().Undefined(vm));
    } else {
        target->Set(vm, panda::StringRef::NewFromUtf8(vm, "id"),
            panda::StringRef::NewFromUtf8(vm, info->GetTarget().id.c_str()));
    }
    return target;
}

Local<panda::ObjectRef> CommonBridge::CreateAreaObject(EcmaVM* vm, const RectF& rect, const OffsetF& origin)
{
    double density = PipelineBase::GetCurrentDensity();
    auto localOffset = rect.GetOffset();
    const char* keysOfOffset[] = { "x", "y" };
    Local<JSValueRef> valuesOfOffset[] = { panda::NumberRef::New(vm, localOffset.GetX() / density),
        panda::NumberRef::New(vm, localOffset.GetY() / density) };
    auto offset = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keysOfOffset), keysOfOffset, valuesOfOffset);
    const char* keysOfGlobalOffset[] = { "x", "y" };
    Local<JSValueRef> valuesOfGlobalOffset[] = { panda::NumberRef::New(
        vm, (localOffset.GetX() + origin.GetX()) / density),
        panda::NumberRef::New(vm, (localOffset.GetY() + origin.GetY()) / density) };
    auto globalOffset = panda::ObjectRef::NewWithNamedProperties(
        vm, ArraySize(keysOfGlobalOffset), keysOfGlobalOffset, valuesOfGlobalOffset);

    const char* keysOfArea[] = { "pos", "position", "globalPos", "globalPosition", "width", "height" };
    Local<JSValueRef> valuesOfArea[] = { offset, offset, globalOffset, globalOffset,
        panda::NumberRef::New(vm, rect.Width() / density), panda::NumberRef::New(vm, rect.Height() / density) };
    return panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keysOfArea), keysOfArea, valuesOfArea);
}

void CommonBridge::GetGestureCommonValue(ArkUIRuntimeCallInfo* runtimeCallInfo, int32_t& priority, int32_t& mask)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    Local<JSValueRef> priorityArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (!priorityArg.IsNull() && !priorityArg->IsUndefined()) {
        priority = static_cast<int32_t>(priorityArg->ToNumber(vm)->Value());
    }
    Local<JSValueRef> maskArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    if (!maskArg.IsNull() && !maskArg->IsUndefined()) {
        mask = static_cast<int32_t>(maskArg->ToNumber(vm)->Value());
    }
}

void CommonBridge::SetGestureTag(ArkUIRuntimeCallInfo* runtimeCallInfo, uint32_t argNumber, ArkUIGesture* gesture)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    Local<JSValueRef> gestureTagArg = runtimeCallInfo->GetCallArgRef(argNumber);
    if (!gestureTagArg.IsNull() && !gestureTagArg->IsUndefined()) {
        auto gesturePtr = Referenced::Claim(reinterpret_cast<Gesture*>(gesture));
        gesturePtr->SetTag(gestureTagArg->ToString(vm)->ToString(vm));
    }
}

void CommonBridge::SetGestureDistanceMap(ArkUIRuntimeCallInfo* runtimeCallInfo, uint32_t argNumber,
    ArkUIGesture* gesture)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    Local<JSValueRef> gestureDistanceMap = runtimeCallInfo->GetCallArgRef(argNumber);
    if (!gestureDistanceMap.IsNull() && !gestureDistanceMap->IsUndefined() && gestureDistanceMap->IsMap(vm)) {
        Local<panda::MapRef> distanceMapRef(gestureDistanceMap);
        int32_t distanceMapSize = distanceMapRef->GetSize(vm);
        PanDistanceMapDimension distanceMap = { { SourceTool::UNKNOWN, DEFAULT_PAN_DISTANCE },
            { SourceTool::PEN, DEFAULT_PEN_PAN_DISTANCE } };
        for (int32_t i = 0; i < distanceMapSize; i++) {
            SourceTool sourceTool = static_cast<SourceTool>(distanceMapRef->GetKey(vm, i)->ToNumber(vm)->Value());
            double distance = static_cast<double>(distanceMapRef->GetValue(vm, i)->ToNumber(vm)->Value());
            if (sourceTool >= SourceTool::UNKNOWN &&
                sourceTool <= SourceTool::JOYSTICK && GreatOrEqual(distance, 0.0)) {
                distanceMap[sourceTool] = Dimension(distance, DimensionUnit::VP);
            }
        }
        auto gesturePtr = Referenced::Claim(reinterpret_cast<PanGesture*>(gesture));
        gesturePtr->SetDistanceMap(distanceMap);
    }
}

void CommonBridge::SetGestureAllowedTypes(ArkUIRuntimeCallInfo* runtimeCallInfo, uint32_t argNumber,
    ArkUIGesture* gesture)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    Local<JSValueRef> typesArg = runtimeCallInfo->GetCallArgRef(argNumber);
    if (typesArg.IsNull() || typesArg->IsUndefined() || !typesArg->IsArray(vm)) {
        return;
    }
    auto typesArr = panda::Local<panda::ArrayRef>(typesArg);
    auto typesLength = typesArr->Length(vm);
    std::set<SourceTool> allowedTypes{};
    for (size_t i = 0; i < typesLength; ++i) {
        auto type = panda::ArrayRef::GetValueAt(vm, typesArr, i);
        if (type->IsNumber()) {
            allowedTypes.insert(static_cast<SourceTool>(type->Int32Value(vm)));
        }
    }
    if (allowedTypes.empty()) {
        return;
    }
    auto gesturePtr = Referenced::Claim(reinterpret_cast<Gesture*>(gesture));
    gesturePtr->SetAllowedTypes(allowedTypes);
}

void CommonBridge::GetTapGestureValue(ArkUIRuntimeCallInfo* runtimeCallInfo, int32_t& fingers,
    int32_t& count, double& distanceThreshold, bool& limitFingerCount, uint32_t argNumber)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    Local<JSValueRef> fingersArg = runtimeCallInfo->GetCallArgRef(argNumber);
    if (!fingersArg.IsNull() && !fingersArg->IsUndefined()) {
        auto fingersValue = static_cast<int32_t>(fingersArg->ToNumber(vm)->Value());
        fingers = (fingersValue < DEFAULT_TAP_FINGER || fingersValue > DEFAULT_MAX_FINGERS) ? DEFAULT_TAP_FINGER
                                                                                            : fingersValue;
    }
    Local<JSValueRef> countArg = runtimeCallInfo->GetCallArgRef(argNumber + 1);
    if (!countArg.IsNull() && !countArg->IsUndefined()) {
        auto countValue = static_cast<int32_t>(countArg->ToNumber(vm)->Value());
        count = countValue < DEFAULT_TAP_COUNT ? DEFAULT_TAP_COUNT : countValue;
    }
    Local<JSValueRef> limitFingerCountArg = runtimeCallInfo->GetCallArgRef(argNumber + 2); // 2: get the third arg
    if (!limitFingerCountArg.IsNull() && !limitFingerCountArg->IsUndefined()) {
        limitFingerCount = limitFingerCountArg->ToBoolean(vm)->Value();
    }
}

void CommonBridge::GetLongPressGestureValue(
    ArkUIRuntimeCallInfo* runtimeCallInfo, int32_t& fingers, bool& repeat, int32_t& duration,
    bool& limitFingerCount, uint32_t argNumber)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    Local<JSValueRef> fingersArg = runtimeCallInfo->GetCallArgRef(argNumber);
    if (!fingersArg.IsNull() && !fingersArg->IsUndefined()) {
        auto fingersValue = static_cast<int32_t>(fingersArg->ToNumber(vm)->Value());
        fingers = (fingersValue < DEFAULT_LONG_PRESS_FINGER || fingersValue > DEFAULT_MAX_FINGERS)
                      ? DEFAULT_LONG_PRESS_FINGER
                      : fingersValue;
    }
    Local<JSValueRef> repeatArg = runtimeCallInfo->GetCallArgRef(argNumber + 1);
    if (!repeatArg.IsNull() && !repeatArg->IsUndefined()) {
        repeat = repeatArg->ToBoolean(vm)->Value();
    }
    Local<JSValueRef> durationArg = runtimeCallInfo->GetCallArgRef(argNumber + NUM_2);
    if (!durationArg.IsNull() && !durationArg->IsUndefined()) {
        auto durationValue = static_cast<int32_t>(durationArg->ToNumber(vm)->Value());
        duration = durationValue <= 0 ? DEFAULT_LONG_PRESS_DURATION : durationValue;
    }
    Local<JSValueRef> limitFingerCountArg = runtimeCallInfo->GetCallArgRef(argNumber + 3); // 3: get the fourth arg
    if (!limitFingerCountArg.IsNull() && !limitFingerCountArg->IsUndefined()) {
        limitFingerCount = limitFingerCountArg->ToBoolean(vm)->Value();
    }
}

void CommonBridge::GetPanGestureValue(
    ArkUIRuntimeCallInfo* runtimeCallInfo, int32_t& fingers, int32_t& direction, PanDistanceMapDimension& distanceMap,
    bool& limitFingerCount, uint32_t argNumber)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    Local<JSValueRef> fingersArg = runtimeCallInfo->GetCallArgRef(argNumber);
    if (!fingersArg.IsNull() && !fingersArg->IsUndefined()) {
        auto fingersValue = static_cast<int32_t>(fingersArg->ToNumber(vm)->Value());
        fingers = (fingersValue < DEFAULT_PAN_FINGER || fingersValue > DEFAULT_MAX_FINGERS) ? DEFAULT_PAN_FINGER
                                                                                            : fingersValue;
    }
    Local<JSValueRef> directionArg = runtimeCallInfo->GetCallArgRef(argNumber + 1);
    if (!directionArg.IsNull() && !directionArg->IsUndefined()) {
        direction = static_cast<int32_t>(directionArg->ToNumber(vm)->Value());
    }
    Local<JSValueRef> distanceArg = runtimeCallInfo->GetCallArgRef(argNumber + 2);
    if (!distanceArg.IsNull() && !distanceArg->IsUndefined()) {
        auto distanceValue = static_cast<double>(distanceArg->ToNumber(vm)->Value());
        if (distanceValue >= 0.0f) {
            distanceMap[SourceTool::UNKNOWN] = OHOS::Ace::Dimension(distanceValue, DimensionUnit::PX);
        } else {
            distanceMap[SourceTool::PEN] = DEFAULT_PEN_PAN_DISTANCE;
        }
    } else {
        distanceMap[SourceTool::PEN] = DEFAULT_PEN_PAN_DISTANCE;
    }
    Local<JSValueRef> limitFingerCountArg = runtimeCallInfo->GetCallArgRef(argNumber + 3); // 3: get the fourth arg
    if (!limitFingerCountArg.IsNull() && !limitFingerCountArg->IsUndefined()) {
        limitFingerCount = limitFingerCountArg->ToBoolean(vm)->Value();
    }
}

void CommonBridge::GetSwipeGestureValue(
    ArkUIRuntimeCallInfo* runtimeCallInfo, int32_t& fingers, int32_t& direction, double& speed,
    bool& limitFingerCount, uint32_t argNumber)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    Local<JSValueRef> fingersArg = runtimeCallInfo->GetCallArgRef(argNumber);
    if (!fingersArg.IsNull() && !fingersArg->IsUndefined()) {
        auto fingersValue = static_cast<int32_t>(fingersArg->ToNumber(vm)->Value());
        fingers = (fingersValue < DEFAULT_SLIDE_FINGER || fingersValue > DEFAULT_MAX_FINGERS) ? DEFAULT_SLIDE_FINGER
                                                                                              : fingersValue;
    }
    Local<JSValueRef> directionArg = runtimeCallInfo->GetCallArgRef(argNumber + 1);
    if (!directionArg.IsNull() && !directionArg->IsUndefined()) {
        direction = static_cast<int32_t>(directionArg->ToNumber(vm)->Value());
    }
    Local<JSValueRef> speedArg = runtimeCallInfo->GetCallArgRef(argNumber + 2);
    if (!speedArg.IsNull() && !speedArg->IsUndefined()) {
        auto speedValue = static_cast<double>(speedArg->ToNumber(vm)->Value());
        speed = LessOrEqual(speedValue, 0.0) ? DEFAULT_SLIDE_SPEED : speedValue;
    }
    Local<JSValueRef> limitFingerCountArg = runtimeCallInfo->GetCallArgRef(argNumber + 3); // 3: get the fourth arg
    if (!limitFingerCountArg.IsNull() && !limitFingerCountArg->IsUndefined()) {
        limitFingerCount = limitFingerCountArg->ToBoolean(vm)->Value();
    }
}

void CommonBridge::GetPinchGestureValue(
    ArkUIRuntimeCallInfo* runtimeCallInfo, int32_t& fingers, double& distance,
    bool& limitFingerCount, uint32_t argNumber)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    Local<JSValueRef> fingersArg = runtimeCallInfo->GetCallArgRef(argNumber);
    if (!fingersArg.IsNull() && !fingersArg->IsUndefined()) {
        auto fingersValue = static_cast<int32_t>(fingersArg->ToNumber(vm)->Value());
        fingers = (fingersValue < DEFAULT_PINCH_FINGER || fingersValue > DEFAULT_MAX_PINCH_FINGER)
                      ? DEFAULT_PINCH_FINGER
                      : fingersValue;
    }
    Local<JSValueRef> distanceArg = runtimeCallInfo->GetCallArgRef(argNumber + 1);
    if (!distanceArg.IsNull() && !distanceArg->IsUndefined()) {
        auto distanceValue = static_cast<double>(distanceArg->ToNumber(vm)->Value());
        distance = distanceValue <= 0.0 ? DEFAULT_PINCH_DISTANCE : distanceValue;
    }
    Local<JSValueRef> limitFingerCountArg = runtimeCallInfo->GetCallArgRef(argNumber + 2); // 2: get the third arg
    if (!limitFingerCountArg.IsNull() && !limitFingerCountArg->IsUndefined()) {
        limitFingerCount = limitFingerCountArg->ToBoolean(vm)->Value();
    }
}

void CommonBridge::GetRotationGestureValue(
    ArkUIRuntimeCallInfo* runtimeCallInfo, int32_t& fingers, double& angle,
    bool& limitFingerCount, uint32_t argNumber)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    Local<JSValueRef> fingersArg = runtimeCallInfo->GetCallArgRef(argNumber);
    if (!fingersArg.IsNull() && !fingersArg->IsUndefined()) {
        auto fingersValue = static_cast<int32_t>(fingersArg->ToNumber(vm)->Value());
        fingers = (fingersValue < DEFAULT_ROTATION_FINGER || fingersValue > DEFAULT_MAX_ROTATION_FINGER)
                      ? DEFAULT_ROTATION_FINGER
                      : fingersValue;
    }
    Local<JSValueRef> angleArg = runtimeCallInfo->GetCallArgRef(argNumber + 1);
    if (!angleArg.IsNull() && !angleArg->IsUndefined()) {
        auto angleValue = static_cast<double>(angleArg->ToNumber(vm)->Value());
        angle = (angleValue <= 0 || angleValue > DEFAULT_MAX_ROTATION_ANGLE) ? DEFAULT_ROTATION_ANGLE : angleValue;
    }
    Local<JSValueRef> limitFingerCountArg = runtimeCallInfo->GetCallArgRef(argNumber + 2); // 2: get the third arg
    if (!limitFingerCountArg.IsNull() && !limitFingerCountArg->IsUndefined()) {
        limitFingerCount = limitFingerCountArg->ToBoolean(vm)->Value();
    }
}

void CommonBridge::GetGestureModeValue(ArkUIRuntimeCallInfo* runtimeCallInfo, int32_t& mode, uint32_t argNumber)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    Local<JSValueRef> modeArg = runtimeCallInfo->GetCallArgRef(argNumber);
    if (!modeArg.IsNull() && !modeArg->IsUndefined()) {
        mode = static_cast<int32_t>(modeArg->ToNumber(vm)->Value());
    }
}

void CommonBridge::SetOnGestureEvent(
    ArkUIRuntimeCallInfo* runtimeCallInfo, const GestureEventAction& action, uint32_t argNumber, ArkUIGesture* gesture)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    Local<JSValueRef> eventArg = runtimeCallInfo->GetCallArgRef(argNumber);
    if (eventArg.IsNull() || eventArg->IsUndefined() || !eventArg->IsFunction(vm)) {
        return;
    }
    auto obj = eventArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    panda::Local<panda::FunctionRef> func = obj;
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    bool isWeak = frameNode == nullptr ? false : FrameNodeBridge::IsCustomFrameNode(frameNode);

    if (action == Ace::GestureEventAction::CANCEL) {
        auto onActionCancelFunc = [vm, func = JSFuncObjRef(panda::CopyableGlobal(vm, func), isWeak),
            containerId](GestureEvent& info) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            ContainerScope scope(containerId);
            auto function = func.Lock();
            if (!function.IsEmpty() && function->IsFunction(vm)) {
                auto obj = CreateCommonGestureEventInfo(vm, info);
                panda::Local<panda::JSValueRef> params[1] = { obj };
                function->Call(vm, function.ToLocal(), params, 1);
            }
        };
        auto gesturePtr = Referenced::Claim(reinterpret_cast<Gesture*>(gesture));
        gesturePtr->SetOnActionCancelId(onActionCancelFunc);
        return;
    }
    auto event = [vm, func = JSFuncObjRef(panda::CopyableGlobal(vm, func), isWeak), containerId](GestureEvent& info) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        auto function = func.Lock();
        if (!function.IsEmpty() && function->IsFunction(vm)) {
            auto obj = CreateCommonGestureEventInfo(vm, info);
            panda::Local<panda::JSValueRef> params[1] = { obj };
            function->Call(vm, function.ToLocal(), params, 1);
        }
    };
    auto gesturePtr = Referenced::Claim(reinterpret_cast<Gesture*>(gesture));
    switch (action) {
        case Ace::GestureEventAction::ACTION:
            gesturePtr->SetOnActionId(event);
            break;
        case Ace::GestureEventAction::START:
            gesturePtr->SetOnActionStartId(event);
            break;
        case Ace::GestureEventAction::UPDATE:
            gesturePtr->SetOnActionUpdateId(event);
            break;
        case Ace::GestureEventAction::END:
            gesturePtr->SetOnActionEndId(event);
            break;
        default:
            break;
    }
}

Local<panda::ObjectRef> CommonBridge::CreateCommonGestureEventInfo(EcmaVM* vm, GestureEvent& info)
{
    double density = PipelineBase::GetCurrentDensity();
    const char* keys[] = { "repeat", "offsetX", "offsetY", "scale", "angle", "speed", "timestamp", "pinchCenterX",
        "pinchCenterY", "source", "pressure", "sourceTool", "velocityX", "velocityY", "velocity",
        "deviceId", "getModifierKeyState" };
    Local<JSValueRef> values[] = { panda::BooleanRef::New(vm, info.GetRepeat()),
        panda::NumberRef::New(vm, info.GetOffsetX() / density), panda::NumberRef::New(vm, info.GetOffsetY() / density),
        panda::NumberRef::New(vm, info.GetScale()), panda::NumberRef::New(vm, info.GetAngle()),
        panda::NumberRef::New(vm, info.GetSpeed()),
        panda::NumberRef::New(vm, static_cast<double>(info.GetTimeStamp().time_since_epoch().count())),
        panda::NumberRef::New(vm, info.GetPinchCenter().GetX() / density),
        panda::NumberRef::New(vm, info.GetPinchCenter().GetY() / density),
        panda::NumberRef::New(vm, static_cast<int32_t>(info.GetSourceDevice())),
        panda::NumberRef::New(vm, info.GetForce()),
        panda::NumberRef::New(vm, static_cast<int32_t>(static_cast<int32_t>(info.GetSourceTool()))),
        panda::NumberRef::New(vm, info.GetVelocity().GetVelocityX() / density),
        panda::NumberRef::New(vm, info.GetVelocity().GetVelocityY() / density),
        panda::NumberRef::New(vm, info.GetVelocity().GetVelocityValue() / density),
        panda::NumberRef::New(vm, info.GetDeviceId()),
        panda::FunctionRef::New(vm, ArkTSUtils::JsGetModifierKeyState) };
    auto obj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "tiltX"),
        panda::NumberRef::New(vm, static_cast<int32_t>(info.GetTiltX().value_or(0.0f))));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "tiltY"),
        panda::NumberRef::New(vm, static_cast<int32_t>(info.GetTiltY().value_or(0.0f))));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "rollAngle"),
        panda::NumberRef::New(vm, static_cast<int32_t>(info.GetRollAngle().value_or(0.0f))));
    auto fingerArr = CreateFingerListArray(vm, info);
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "fingerList"), fingerArr);
    auto fingerInfoArr = CreateFingerInfosArray(vm, info);
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "fingerInfos"), fingerInfoArr);
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "target"), FrameNodeBridge::CreateEventTargetObject(vm, info));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "axisVertical"), panda::NumberRef::New(vm, info.GetVerticalAxis()));
    obj->Set(
        vm, panda::StringRef::NewFromUtf8(vm, "axisHorizontal"), panda::NumberRef::New(vm, info.GetHorizontalAxis()));
    obj->Set(
        vm, panda::StringRef::NewFromUtf8(vm, "targetDisplayId"), panda::NumberRef::New(vm, info.GetTargetDisplayId()));
    obj->SetNativePointerFieldCount(vm, 1);
    obj->SetNativePointerField(vm, 0, static_cast<void*>(&info));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "targetDisplayId"),
        panda::NumberRef::New(vm, static_cast<int32_t>(info.GetTargetDisplayId())));
    if (info.GetGestureTypeName() == GestureTypeName::TAP_GESTURE && !info.GetFingerList().empty()) {
        auto tapGuestureInfo = CreateTapGestureInfo(vm, info);
        obj->Set(
            vm, panda::StringRef::NewFromUtf8(vm, "tapLocation"), tapGuestureInfo);
    }
    return obj;
}

Local<panda::ArrayRef> CommonBridge::CreateFingerListArray(EcmaVM* vm, GestureEvent& info)
{
    auto fingerArr = panda::ArrayRef::New(vm);
    const std::list<FingerInfo>& fingerList = info.GetFingerList();
    std::list<FingerInfo> notTouchFingerList;
    int32_t maxFingerId = -1;
    for (const FingerInfo& fingerInfo : fingerList) {
        auto element = CreateFingerInfo(vm, fingerInfo);
        if (fingerInfo.sourceType_ == SourceType::TOUCH && fingerInfo.sourceTool_ == SourceTool::FINGER) {
            fingerArr->SetValueAt(vm, fingerArr, fingerInfo.fingerId_, element);
            if (fingerInfo.fingerId_ > maxFingerId) {
                maxFingerId = fingerInfo.fingerId_;
            }
        } else {
            notTouchFingerList.emplace_back(fingerInfo);
        }
    }
    auto idx = maxFingerId + 1;
    for (const FingerInfo& fingerInfo : notTouchFingerList) {
        auto element = CreateFingerInfo(vm, fingerInfo);
        fingerArr->SetValueAt(vm, fingerArr, idx++, element);
    }
    return fingerArr;
}

Local<panda::ArrayRef> CommonBridge::CreateFingerInfosArray(EcmaVM* vm, GestureEvent& info)
{
    auto fingerArr = panda::ArrayRef::New(vm);
    const std::list<FingerInfo>& fingerList = info.GetFingerList();
    std::list<FingerInfo> notTouchFingerList;
    std::vector<Local<panda::ObjectRef>> validFingers;
    for (const FingerInfo& fingerInfo : fingerList) {
        auto element = CreateFingerInfo(vm, fingerInfo);
        if (fingerInfo.sourceType_ == SourceType::TOUCH && fingerInfo.sourceTool_ == SourceTool::FINGER) {
            validFingers.emplace_back(element);
        } else {
            notTouchFingerList.emplace_back(fingerInfo);
        }
    }
    for (size_t i = 0; i < validFingers.size(); ++i) {
        fingerArr->SetValueAt(vm, fingerArr, i, validFingers[i]);
    }
    auto idx = validFingers.size();
    for (const FingerInfo& fingerInfo : notTouchFingerList) {
        auto element = CreateFingerInfo(vm, fingerInfo);
        fingerArr->SetValueAt(vm, fingerArr, idx++, element);
    }
    return fingerArr;
}

ArkUIGesture* CommonBridge::GetGestureGroup(ArkUIRuntimeCallInfo* runtimeCallInfo, uint32_t argNumber)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, nullptr);
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(argNumber);
    CHECK_NULL_RETURN(!firstArg.IsNull(), nullptr);
    auto* group = reinterpret_cast<ArkUIGesture*>(firstArg->ToNativePointer(vm)->Value());
    return group;
}

ArkUINativeModuleValue CommonBridge::SetOnClick(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(secondeArg->IsFunction(vm), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    panda::Local<panda::FunctionRef> func = obj;
    auto flag = FrameNodeBridge::IsCustomFrameNode(frameNode);
    auto onClick = [vm, func = JSFuncObjRef(panda::CopyableGlobal(vm, func), flag),
                       node = AceType::WeakClaim(frameNode), containerId](GestureEvent& info) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        auto function = func.Lock();
        CHECK_NULL_VOID(!function.IsEmpty());
        CHECK_NULL_VOID(function->IsFunction(vm));
        PipelineContext::SetCallBackNode(node);
        auto obj = FrameNodeBridge::CreateGestureEventInfo(vm, info);
        panda::Local<panda::JSValueRef> params[1] = { obj };
        function->Call(vm, function.ToLocal(), params, 1);
    };
    // The click event of the text component requires special integration.
    // If the onClick callback function is modified,
    // the SetOnClick function in the arkts_native_text_bridge.cpp file must also be updated accordingly.
    if (frameNode->GetTag() == V2::SPAN_ETS_TAG) {
        SpanModelNG::SetOnClick(frameNode, std::move(onClick));
    } else {
        NG::ViewAbstract::SetOnClick(frameNode, std::move(onClick));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetOnClick(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ViewAbstract::DisableOnClick(frameNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetOnDragStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::FUNCTION };
    auto jsVal = info[1];
    if (!JSViewAbstract::CheckJSCallbackInfo("OnDragStart", jsVal, checkList)) {
        return panda::JSValueRef::Undefined(vm);
    }
    RefPtr<JsDragFunction> jsOnDragStartFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(jsVal));
    auto onDragStart = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragStartFunc),
                           node = AceType::WeakClaim<NG::FrameNode>(frameNode)](
                           const RefPtr<OHOS::Ace::DragEvent>& info,
                           const std::string& extraParams) -> NG::DragDropBaseInfo {
        NG::DragDropBaseInfo dragDropInfo;
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, dragDropInfo);
        PipelineContext::SetCallBackNode(node);
        auto ret = func->Execute(info, extraParams);
        if (!ret->IsObject()) {
            return dragDropInfo;
        }
        auto builderObj = JSRef<JSObject>::Cast(ret);
#if defined(PIXEL_MAP_SUPPORTED)
        auto pixmap = builderObj->GetProperty("pixelMap");
        dragDropInfo.pixelMap = CreatePixelMapFromNapiValue(pixmap);
#endif
        auto extraInfo = builderObj->GetProperty("extraInfo");
        JSViewAbstract::ParseJsString(extraInfo, dragDropInfo.extraInfo);
        return dragDropInfo;
    };
    ViewAbstractModelNG::SetOnDragStart(frameNode, std::move(onDragStart));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetOnDragStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ViewAbstract::DisableOnDragStart(frameNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetOnDragEnter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::FUNCTION };
    auto jsVal = info[1];
    if (!JSViewAbstract::CheckJSCallbackInfo("OnDragEnter", jsVal, checkList)) {
        return panda::JSValueRef::Undefined(vm);
    }
    RefPtr<JsDragFunction> jsOnDragEnterFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(jsVal));
    auto onDragEnter = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragEnterFunc),
                           node = AceType::WeakClaim<NG::FrameNode>(frameNode)](
                           const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onDragEnter");
        PipelineContext::SetCallBackNode(node);
        func->Execute(info, extraParams);
    };
    NG::ViewAbstract::SetOnDragEnter(frameNode, std::move(onDragEnter));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetOnDragEnter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ViewAbstract::DisableOnDragEnter(frameNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetOnDragSpringLoading(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    if (info.Length() > SIZE_OF_ONE) {
        static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::FUNCTION };
        auto jsVal = info[NUM_1];
        if (!JSViewAbstract::CheckJSCallbackInfo("JsOnDragSpringLoading", jsVal, checkList)) {
            return panda::JSValueRef::Undefined(vm);
        }
        NG::OnDragDropSpringLoadingFunc onDragSpringLoading = nullptr;
        if (jsVal->IsFunction()) {
            RefPtr<JsDragFunction> jsOnDragSpringLoadingFunc =
                AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(jsVal));
            onDragSpringLoading = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragSpringLoadingFunc),
                                      node = AceType::WeakClaim<NG::FrameNode>(frameNode)](
                                      const RefPtr<DragSpringLoadingContext>& info) {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                ACE_SCORING_EVENT("JsOnDragSpringLoading");
                PipelineContext::SetCallBackNode(node);
                func->DragSpringLoadingExecute(info);
            };
        }
        NG::ViewAbstract::SetOnDragSpringLoading(frameNode, std::move(onDragSpringLoading));
    }
    if (info.Length() == SIZE_OF_THREE && info[NUM_2]->IsObject()) {
        auto dragSpringLoadingConfiguration = AceType::MakeRefPtr<NG::DragSpringLoadingConfiguration>();
        JSViewAbstract::ParseDragSpringLoadingConfiguration(info[NUM_2], dragSpringLoadingConfiguration);
        NG::ViewAbstract::SetOnDragSpringLoadingConfiguration(frameNode, std::move(dragSpringLoadingConfiguration));
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetOnDragSpringLoading(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ViewAbstract::DisableOnDragSpringLoading(frameNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetOnDragMove(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::FUNCTION };
    auto jsVal = info[1];
    if (!JSViewAbstract::CheckJSCallbackInfo("OnDragMove", jsVal, checkList)) {
        return panda::JSValueRef::Undefined(vm);
    }
    RefPtr<JsDragFunction> jsOnDragMoveFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(jsVal));
    auto onDragMove = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragMoveFunc),
                          node = AceType::WeakClaim<NG::FrameNode>(frameNode)](
                          const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onDragMove");
        PipelineContext::SetCallBackNode(node);
        func->Execute(info, extraParams);
    };
    NG::ViewAbstract::SetOnDragMove(frameNode, std::move(onDragMove));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetOnDragMove(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ViewAbstract::DisableOnDragMove(frameNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetOnDragLeave(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::FUNCTION };
    auto jsVal = info[1];
    if (!JSViewAbstract::CheckJSCallbackInfo("OnDragLeave", jsVal, checkList)) {
        return panda::JSValueRef::Undefined(vm);
    }
    RefPtr<JsDragFunction> jsOnDragLeaveFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(jsVal));
    auto onDragLeave = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragLeaveFunc),
                           node = AceType::WeakClaim<NG::FrameNode>(frameNode)](
                           const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onDragLeave");
        PipelineContext::SetCallBackNode(node);
        func->Execute(info, extraParams);
    };
    NG::ViewAbstract::SetOnDragLeave(frameNode, std::move(onDragLeave));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetOnDragLeave(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ViewAbstract::DisableOnDragLeave(frameNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetOnDrop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::FUNCTION };
    auto jsVal = info[1];
    if (!JSViewAbstract::CheckJSCallbackInfo("OnDrop", jsVal, checkList)) {
        return panda::JSValueRef::Undefined(vm);
    }
    RefPtr<JsDragFunction> jsOnDropFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(jsVal));
    auto onDrop = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDropFunc),
                      node = AceType::WeakClaim<NG::FrameNode>(frameNode)](
                      const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onDrop");
        PipelineContext::SetCallBackNode(node);
        func->Execute(info, extraParams);
    };
    NG::ViewAbstract::SetOnDrop(frameNode, std::move(onDrop));

    bool disableDataPrefetch = false;
    if (info[NUM_2]->IsBoolean()) {
        disableDataPrefetch = info[NUM_2]->ToBoolean();
    }
    NG::ViewAbstract::SetDisableDataPrefetch(frameNode, disableDataPrefetch);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetOnDrop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ViewAbstract::DisableOnDrop(frameNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetOnDragEnd(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::FUNCTION };
    auto jsVal = info[1];
    if (!JSViewAbstract::CheckJSCallbackInfo("OnDragEnd", jsVal, checkList)) {
        return panda::JSValueRef::Undefined(vm);
    }
    RefPtr<JsDragFunction> jsOnDragEndFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(jsVal));
    auto onDragEnd = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragEndFunc),
                         node = AceType::WeakClaim<NG::FrameNode>(frameNode)](
                         const RefPtr<OHOS::Ace::DragEvent>& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onDragEnd");
        auto extraParams = JsonUtil::Create(true);
        PipelineContext::SetCallBackNode(node);
        func->Execute(info, extraParams->ToString());
    };
    NG::ViewAbstract::SetOnDragEnd(frameNode, std::move(onDragEnd));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetOnDragEnd(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ViewAbstract::DisableOnDragEnd(frameNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetOnTouch(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(secondeArg->IsFunction(vm), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    panda::Local<panda::FunctionRef> func = obj;
    auto flag = FrameNodeBridge::IsCustomFrameNode(frameNode);
    auto onTouch = [vm, func = JSFuncObjRef(panda::CopyableGlobal(vm, func), flag),
                       node = AceType::WeakClaim(frameNode), containerId](TouchEventInfo& info) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        auto function = func.Lock();
        CHECK_NULL_VOID(!function.IsEmpty());
        CHECK_NULL_VOID(function->IsFunction(vm));
        PipelineContext::SetCallBackNode(node);
        auto eventObj = FrameNodeBridge::CreateTouchEventInfo(vm, info);
        panda::Local<panda::JSValueRef> params[1] = { eventObj };
        function->Call(vm, function.ToLocal(), params, 1);
    };
    NG::ViewAbstract::SetOnTouch(frameNode, std::move(onTouch));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetOnTouch(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ViewAbstract::DisableOnTouch(frameNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetChainMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    int32_t direction = 0;
    int32_t style = 0;
    if (!secondArg.IsNull() && !secondArg->IsUndefined()) {
        direction = static_cast<int32_t>(secondArg->ToNumber(vm)->Value());
    }
    if (!thirdArg.IsNull() && !thirdArg->IsUndefined()) {
        style = static_cast<int32_t>(thirdArg->ToNumber(vm)->Value());
    }
    GetArkUINodeModifiers()->getCommonModifier()->setChainStyle(nativeNode, direction, style);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetChainMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetChainStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CommonBridge::SetOnAppear(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(secondeArg->IsFunction(vm), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    panda::Local<panda::FunctionRef> func = obj;
    auto flag = FrameNodeBridge::IsCustomFrameNode(frameNode);
    auto onAppear = [vm, func = JSFuncObjRef(panda::CopyableGlobal(vm, func), flag),
                        node = AceType::WeakClaim(frameNode), containerId]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        auto function = func.Lock();
        CHECK_NULL_VOID(!function.IsEmpty());
        CHECK_NULL_VOID(function->IsFunction(vm));
        PipelineContext::SetCallBackNode(node);
        function->Call(vm, function.ToLocal(), nullptr, 0);
    };
    NG::ViewAbstract::SetOnAppear(frameNode, std::move(onAppear));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetOnAppear(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ViewAbstract::DisableOnAppear(frameNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetOnDisappear(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(secondeArg->IsFunction(vm), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    panda::Local<panda::FunctionRef> func = obj;
    auto flag = FrameNodeBridge::IsCustomFrameNode(frameNode);
    auto onDisappear = [vm, func = JSFuncObjRef(panda::CopyableGlobal(vm, func), flag),
                           node = AceType::WeakClaim(frameNode), containerId]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        auto function = func.Lock();
        CHECK_NULL_VOID(!function.IsEmpty());
        CHECK_NULL_VOID(function->IsFunction(vm));
        PipelineContext::SetCallBackNode(node);
        function->Call(vm, function.ToLocal(), nullptr, 0);
    };
    NG::ViewAbstract::SetOnDisappear(frameNode, std::move(onDisappear));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetOnDisappear(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ViewAbstract::DisableOnDisappear(frameNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetOnAttach(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(secondeArg->IsFunction(vm), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    panda::Local<panda::FunctionRef> func = obj;
    auto flag = FrameNodeBridge::IsCustomFrameNode(frameNode);
    auto onAttach = [vm, func = JSFuncObjRef(panda::CopyableGlobal(vm, func), flag),
                        node = AceType::WeakClaim(frameNode), containerId]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        auto function = func.Lock();
        CHECK_NULL_VOID(!function.IsEmpty());
        CHECK_NULL_VOID(function->IsFunction(vm));
        PipelineContext::SetCallBackNode(node);
        function->Call(vm, function.ToLocal(), nullptr, 0);
    };
    NG::ViewAbstract::SetOnAttach(frameNode, std::move(onAttach));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetOnAttach(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ViewAbstract::DisableOnAttach(frameNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetOnDetach(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(secondeArg->IsFunction(vm), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    panda::Local<panda::FunctionRef> func = obj;
    auto flag = FrameNodeBridge::IsCustomFrameNode(frameNode);
    auto onDetach = [vm, func = JSFuncObjRef(panda::CopyableGlobal(vm, func), flag),
                        node = AceType::WeakClaim(frameNode), containerId]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        auto function = func.Lock();
        CHECK_NULL_VOID(!function.IsEmpty());
        CHECK_NULL_VOID(function->IsFunction(vm));
        PipelineContext::SetCallBackNode(node);
        function->Call(vm, function.ToLocal(), nullptr, 0);
    };
    NG::ViewAbstract::SetOnDetach(frameNode, std::move(onDetach));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetOnDetach(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ViewAbstract::DisableOnDetach(frameNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetOnKeyEvent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(secondeArg->IsFunction(vm), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    panda::Local<panda::FunctionRef> func = obj;
    auto flag = FrameNodeBridge::IsCustomFrameNode(frameNode);
    auto onKeyEvent = [vm, func = JSFuncObjRef(panda::CopyableGlobal(vm, func), flag),
                          node = AceType::WeakClaim(frameNode), containerId](KeyEventInfo& info) -> bool {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        auto function = func.Lock();
        CHECK_NULL_RETURN(!function.IsEmpty(), false);
        CHECK_NULL_RETURN(function->IsFunction(vm), false);
        PipelineContext::SetCallBackNode(node);
        const char* keys[] = { "type", "keyCode", "keyText", "keySource", "deviceId", "metaKey", "unicode", "timestamp",
            "stopPropagation", "getModifierKeyState", "intentionCode", "isNumLockOn", "isCapsLockOn",
            "isScrollLockOn" };
        Local<JSValueRef> values[] = { panda::NumberRef::New(vm, static_cast<int32_t>(info.GetKeyType())),
            panda::NumberRef::New(vm, static_cast<int32_t>(info.GetKeyCode())),
            panda::StringRef::NewFromUtf8(vm, info.GetKeyText().c_str()),
            panda::NumberRef::New(vm, static_cast<int32_t>(info.GetKeySource())),
            panda::NumberRef::New(vm, info.GetDeviceId()), panda::NumberRef::New(vm, info.GetMetaKey()),
            panda::NumberRef::New(vm, info.GetUnicode()),
            panda::NumberRef::New(vm, static_cast<double>(info.GetTimeStamp().time_since_epoch().count())),
            panda::FunctionRef::New(vm, Framework::JsStopPropagation),
            panda::FunctionRef::New(vm, ArkTSUtils::JsGetModifierKeyState),
            panda::NumberRef::New(vm, static_cast<int32_t>(info.GetKeyIntention())),
            panda::BooleanRef::New(vm, info.GetNumLock()),
            panda::BooleanRef::New(vm, info.GetCapsLock()),
            panda::BooleanRef::New(vm, info.GetScrollLock()) };
        auto obj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        obj->SetNativePointerFieldCount(vm, 1);
        obj->SetNativePointerField(vm, 0, static_cast<void*>(&info));
        panda::Local<panda::JSValueRef> params[] = { obj };
        auto ret = function->Call(vm, function.ToLocal(), params, 1);
        if (ret->IsBoolean()) {
            return ret->ToBoolean(vm)->Value();
        }
        return false;
    };
    NG::ViewAbstract::SetOnKeyEvent(frameNode, std::move(onKeyEvent));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetOnKeyEvent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ViewAbstract::DisableOnKeyEvent(frameNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetOnKeyPreIme(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(secondeArg->IsFunction(vm), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    panda::Local<panda::FunctionRef> func = obj;
    auto flag = FrameNodeBridge::IsCustomFrameNode(frameNode);
    auto onPreImeEvent = [vm, func = JSFuncObjRef(panda::CopyableGlobal(vm, func), flag),
                             node = AceType::WeakClaim(frameNode), containerId](KeyEventInfo& info) -> bool {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        auto function = func.Lock();
        CHECK_NULL_RETURN(!function.IsEmpty(), false);
        CHECK_NULL_RETURN(function->IsFunction(vm), false);
        PipelineContext::SetCallBackNode(node);
        const char* keys[] = { "type", "keyCode", "keyText", "keySource", "deviceId", "metaKey", "unicode",
            "timestamp", "stopPropagation", "getModifierKeyState", "intentionCode", "isNumLockOn", "isCapsLockOn",
            "isScrollLockOn" };
        Local<JSValueRef> values[] = { panda::NumberRef::New(vm, static_cast<int32_t>(info.GetKeyType())),
            panda::NumberRef::New(vm, static_cast<int32_t>(info.GetKeyCode())),
            panda::StringRef::NewFromUtf8(vm, info.GetKeyText().c_str()),
            panda::NumberRef::New(vm, static_cast<int32_t>(info.GetKeySource())),
            panda::NumberRef::New(vm, info.GetDeviceId()), panda::NumberRef::New(vm, info.GetMetaKey()),
            panda::NumberRef::New(vm, info.GetUnicode()),
            panda::NumberRef::New(vm, static_cast<double>(info.GetTimeStamp().time_since_epoch().count())),
            panda::FunctionRef::New(vm, Framework::JsStopPropagation),
            panda::FunctionRef::New(vm, ArkTSUtils::JsGetModifierKeyState),
            panda::NumberRef::New(vm, static_cast<int32_t>(info.GetKeyIntention())),
            panda::BooleanRef::New(vm, info.GetNumLock()),
            panda::BooleanRef::New(vm, info.GetCapsLock()),
            panda::BooleanRef::New(vm, info.GetScrollLock()) };
        auto obj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        obj->SetNativePointerFieldCount(vm, 1);
        obj->SetNativePointerField(vm, 0, static_cast<void*>(&info));
        panda::Local<panda::JSValueRef> params[] = { obj };
        auto ret = function->Call(vm, function.ToLocal(), params, 1);
        if (ret->IsBoolean()) {
            return ret->ToBoolean(vm)->Value();
        }
        return false;
    };
    NG::ViewAbstractModelNG::SetOnKeyPreIme(frameNode, std::move(onPreImeEvent));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetOnKeyPreIme(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    NG::ViewAbstractModelNG::DisableOnKeyPreIme(frameNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetOnKeyEventDispatch(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(secondeArg->IsFunction(vm), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    panda::Local<panda::FunctionRef> func = obj;
    auto flag = FrameNodeBridge::IsCustomFrameNode(frameNode);
    auto onKeyEventDispatch = [vm, func = JSFuncObjRef(panda::CopyableGlobal(vm, func), flag),
                                  node = AceType::WeakClaim(frameNode), containerId](KeyEventInfo& info) -> bool {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        auto function = func.Lock();
        CHECK_NULL_RETURN(!function.IsEmpty(), false);
        CHECK_NULL_RETURN(function->IsFunction(vm), false);
        PipelineContext::SetCallBackNode(node);
        const char* keys[] = { "type", "keyCode", "keyText", "keySource", "deviceId", "metaKey", "unicode", "timestamp",
            "stopPropagation", "getModifierKeyState", "intentionCode", "isNumLockOn", "isCapsLockOn",
            "isScrollLockOn" };
        Local<JSValueRef> values[] = { panda::NumberRef::New(vm, static_cast<int32_t>(info.GetKeyType())),
            panda::NumberRef::New(vm, static_cast<int32_t>(info.GetKeyCode())),
            panda::StringRef::NewFromUtf8(vm, info.GetKeyText().c_str()),
            panda::NumberRef::New(vm, static_cast<int32_t>(info.GetKeySource())),
            panda::NumberRef::New(vm, info.GetDeviceId()), panda::NumberRef::New(vm, info.GetMetaKey()),
            panda::NumberRef::New(vm, info.GetUnicode()),
            panda::NumberRef::New(vm, static_cast<double>(info.GetTimeStamp().time_since_epoch().count())),
            panda::FunctionRef::New(vm, Framework::JsStopPropagation),
            panda::FunctionRef::New(vm, ArkTSUtils::JsGetModifierKeyState),
            panda::NumberRef::New(vm, static_cast<int32_t>(info.GetKeyIntention())),
            panda::BooleanRef::New(vm, info.GetNumLock()),
            panda::BooleanRef::New(vm, info.GetCapsLock()),
            panda::BooleanRef::New(vm, info.GetScrollLock()) };
        auto obj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        obj->SetNativePointerFieldCount(vm, 1);
        obj->SetNativePointerField(vm, 0, static_cast<void*>(&info));
        panda::Local<panda::JSValueRef> params[] = { obj };
        auto ret = function->Call(vm, function.ToLocal(), params, 1);
        if (ret->IsBoolean()) {
            return ret->ToBoolean(vm)->Value();
        }
        return false;
    };
    NG::ViewAbstract::SetOnKeyEventDispatch(frameNode, std::move(onKeyEventDispatch));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetOnKeyEventDispatch(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    NG::ViewAbstract::DisableOnKeyEventDispatch(frameNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetOnFocus(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(secondeArg->IsFunction(vm), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    panda::Local<panda::FunctionRef> func = obj;
    auto flag = FrameNodeBridge::IsCustomFrameNode(frameNode);
    auto onFocus = [vm, func = JSFuncObjRef(panda::CopyableGlobal(vm, func), flag),
                       node = AceType::WeakClaim(frameNode), containerId]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        auto function = func.Lock();
        CHECK_NULL_VOID(!function.IsEmpty());
        CHECK_NULL_VOID(function->IsFunction(vm));
        PipelineContext::SetCallBackNode(node);
        function->Call(vm, function.ToLocal(), nullptr, 0);
    };
    NG::ViewAbstract::SetOnFocus(frameNode, std::move(onFocus));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetOnFocus(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ViewAbstract::DisableOnFocus(frameNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetOnBlur(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(secondeArg->IsFunction(vm), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    panda::Local<panda::FunctionRef> func = obj;
    auto flag = FrameNodeBridge::IsCustomFrameNode(frameNode);
    auto onBlur = [vm, func = JSFuncObjRef(panda::CopyableGlobal(vm, func), flag), node = AceType::WeakClaim(frameNode),
                      containerId]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        auto function = func.Lock();
        CHECK_NULL_VOID(!function.IsEmpty());
        CHECK_NULL_VOID(function->IsFunction(vm));
        PipelineContext::SetCallBackNode(node);
        function->Call(vm, function.ToLocal(), nullptr, 0);
    };
    NG::ViewAbstract::SetOnBlur(frameNode, std::move(onBlur));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetOnBlur(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ViewAbstract::DisableOnBlur(frameNode);
    return panda::JSValueRef::Undefined(vm);
}

Local<panda::ObjectRef> CommonBridge::CreateHoverInfo(EcmaVM* vm, const HoverInfo& hoverInfo)
{
    const char* keys[] = { "stopPropagation", "getModifierKeyState", "timestamp", "source", "target", "deviceId",
        "targetDisplayId", "displayX", "displayY", "windowX", "windowY", "x", "y", "globalDisplayX", "globalDisplayY",
        "sourceTool" };
    double density = PipelineBase::GetCurrentDensity();
    const Offset& globalOffset = hoverInfo.GetGlobalLocation();
    const Offset& localOffset = hoverInfo.GetLocalLocation();
    const Offset& screenOffset = hoverInfo.GetScreenLocation();
    const Offset& globalDisplayOffset = hoverInfo.GetGlobalDisplayLocation();
    Local<JSValueRef> values[] = { panda::FunctionRef::New(vm, Framework::JsStopPropagation),
        panda::FunctionRef::New(vm, ArkTSUtils::JsGetModifierKeyState),
        panda::NumberRef::New(vm, static_cast<double>(hoverInfo.GetTimeStamp().time_since_epoch().count())),
        panda::NumberRef::New(vm, static_cast<int32_t>(hoverInfo.GetSourceDevice())),
        FrameNodeBridge::CreateEventTargetObject(vm, hoverInfo), panda::NumberRef::New(vm, hoverInfo.GetDeviceId()),
        panda::NumberRef::New(vm, hoverInfo.GetTargetDisplayId()),
        panda::NumberRef::New(vm, density != 0 ? screenOffset.GetX() / density : 0),
        panda::NumberRef::New(vm, density != 0 ? screenOffset.GetY() / density : 0),
        panda::NumberRef::New(vm, density != 0 ? globalOffset.GetX() / density : 0),
        panda::NumberRef::New(vm, density != 0 ? globalOffset.GetY() / density : 0),
        panda::NumberRef::New(vm, density != 0 ? localOffset.GetX() / density : 0),
        panda::NumberRef::New(vm, density != 0 ? localOffset.GetY() / density : 0),
        panda::NumberRef::New(vm, density != 0 ? globalDisplayOffset.GetX() / density : 0),
        panda::NumberRef::New(vm, density != 0 ? globalDisplayOffset.GetY() / density : 0),
        panda::NumberRef::New(vm, static_cast<int32_t>(hoverInfo.GetSourceTool())) };
    return panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
}

ArkUINativeModuleValue CommonBridge::SetOnHover(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(secondeArg->IsFunction(vm), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    panda::Local<panda::FunctionRef> func = obj;
    auto flag = FrameNodeBridge::IsCustomFrameNode(frameNode);
    auto onHover = [vm, func = JSFuncObjRef(panda::CopyableGlobal(vm, func), flag),
                       node = AceType::WeakClaim(frameNode), containerId](bool isHover, HoverInfo& hoverInfo) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        auto function = func.Lock();
        CHECK_NULL_VOID(!function.IsEmpty());
        CHECK_NULL_VOID(function->IsFunction(vm));
        PipelineContext::SetCallBackNode(node);
        auto isHoverParam = panda::BooleanRef::New(vm, isHover);
        auto obj = CreateHoverInfo(vm, hoverInfo);
        obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "tiltX"),
            panda::NumberRef::New(vm, static_cast<int32_t>(hoverInfo.GetTiltX().value_or(0.0f))));
        obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "tiltY"),
            panda::NumberRef::New(vm, static_cast<int32_t>(hoverInfo.GetTiltY().value_or(0.0f))));
        obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "rollAngle"),
            panda::NumberRef::New(vm, static_cast<int32_t>(hoverInfo.GetRollAngle().value_or(0.0f))));
        obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "axisVertical"), panda::NumberRef::New(vm, 0.0f));
        obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "axisHorizontal"), panda::NumberRef::New(vm, 0.0f));
        obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "pressure"), panda::NumberRef::New(vm, 0.0f));
        obj->SetNativePointerFieldCount(vm, 1);
        obj->SetNativePointerField(vm, 0, static_cast<void*>(&hoverInfo));
        panda::Local<panda::JSValueRef> params[] = { isHoverParam, obj };
        function->Call(vm, function.ToLocal(), params, ArraySize(params));
    };
    NG::ViewAbstract::SetOnHover(frameNode, std::move(onHover));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetOnHover(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ViewAbstract::DisableOnHover(frameNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetOnHoverMove(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(secondeArg->IsFunction(vm), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    panda::Local<panda::FunctionRef> func = obj;
    auto flag = FrameNodeBridge::IsCustomFrameNode(frameNode);
    auto onHoverMove = [vm, func = JSFuncObjRef(panda::CopyableGlobal(vm, func), flag),
                           node = AceType::WeakClaim(frameNode), containerId](HoverInfo& hoverInfo) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        auto function = func.Lock();
        CHECK_NULL_VOID(!function.IsEmpty());
        CHECK_NULL_VOID(function->IsFunction(vm));
        PipelineContext::SetCallBackNode(node);
        auto obj = CreateHoverInfo(vm, hoverInfo);
        obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "tiltX"),
            panda::NumberRef::New(vm, static_cast<int32_t>(hoverInfo.GetTiltX().value_or(0.0f))));
        obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "tiltY"),
            panda::NumberRef::New(vm, static_cast<int32_t>(hoverInfo.GetTiltY().value_or(0.0f))));
        obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "rollAngle"),
            panda::NumberRef::New(vm, static_cast<int32_t>(hoverInfo.GetRollAngle().value_or(0.0f))));
        obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "axisVertical"), panda::NumberRef::New(vm, 0.0f));
        obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "axisHorizontal"), panda::NumberRef::New(vm, 0.0f));
        obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "pressure"), panda::NumberRef::New(vm, 0.0f));
        obj->SetNativePointerFieldCount(vm, 1);
        obj->SetNativePointerField(vm, 0, static_cast<void*>(&hoverInfo));
        panda::Local<panda::JSValueRef> params[] = { obj };
        function->Call(vm, function.ToLocal(), params, ArraySize(params));
    };
    NG::ViewAbstract::SetOnHoverMove(frameNode, std::move(onHoverMove));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetOnHoverMove(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ViewAbstract::DisableOnHoverMove(frameNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetOnMouse(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(secondeArg->IsFunction(vm), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    panda::Local<panda::FunctionRef> func = obj;
    auto flag = FrameNodeBridge::IsCustomFrameNode(frameNode);
    auto onMouse = [vm, func = JSFuncObjRef(panda::CopyableGlobal(vm, func), flag),
                       node = AceType::WeakClaim(frameNode), containerId](MouseInfo& info) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        auto function = func.Lock();
        CHECK_NULL_VOID(!function.IsEmpty());
        CHECK_NULL_VOID(function->IsFunction(vm));
        PipelineContext::SetCallBackNode(node);
        auto obj = FrameNodeBridge::CreateMouseInfo(vm, info);
        panda::Local<panda::JSValueRef> params[1] = { obj };
        function->Call(vm, function.ToLocal(), params, 1);
    };
    NG::ViewAbstract::SetOnMouse(frameNode, std::move(onMouse));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetOnMouse(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ViewAbstract::DisableOnMouse(frameNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetOnSizeChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(secondeArg->IsFunction(vm), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    panda::Local<panda::FunctionRef> func = obj;
    auto flag = FrameNodeBridge::IsCustomFrameNode(frameNode);
    auto onSizeChange = [vm, func = JSFuncObjRef(panda::CopyableGlobal(vm, func), flag),
                            node = AceType::WeakClaim(frameNode),
                            containerId](const NG::RectF& oldRect, const NG::RectF& rect) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        auto function = func.Lock();
        CHECK_NULL_VOID(!function.IsEmpty());
        CHECK_NULL_VOID(function->IsFunction(vm));
        PipelineContext::SetCallBackNode(node);
        double density = PipelineBase::GetCurrentDensity();
        const char* keys[] = { "width", "height" };
        Local<JSValueRef> oldValues[] = { panda::NumberRef::New(vm, oldRect.Width() / density),
            panda::NumberRef::New(vm, oldRect.Height() / density) };
        auto oldSize = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, oldValues);
        Local<JSValueRef> newValues[] = { panda::NumberRef::New(vm, rect.Width() / density),
            panda::NumberRef::New(vm, rect.Height() / density) };
        auto newSize = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, newValues);
        panda::Local<panda::JSValueRef> params[2] = { oldSize, newSize };
        function->Call(vm, function.ToLocal(), params, 2);
    };
    NG::ViewAbstract::SetOnSizeChanged(frameNode, std::move(onSizeChange));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetOnSizeChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ViewAbstract::SetOnSizeChanged(frameNode, nullptr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetOnAreaChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(secondeArg->IsFunction(vm), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    panda::Local<panda::FunctionRef> func = obj;
    auto flag = FrameNodeBridge::IsCustomFrameNode(frameNode);
    auto onAreaChange = [vm, func = JSFuncObjRef(panda::CopyableGlobal(vm, func), flag),
                            node = AceType::WeakClaim(frameNode), containerId](
                            const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        auto function = func.Lock();
        CHECK_NULL_VOID(!function.IsEmpty());
        CHECK_NULL_VOID(function->IsFunction(vm));
        PipelineContext::SetCallBackNode(node);
        auto oldArea = CreateAreaObject(vm, oldRect, oldOrigin);
        auto area = CreateAreaObject(vm, rect, origin);
        panda::Local<panda::JSValueRef> params[2] = { oldArea, area };
        function->Call(vm, function.ToLocal(), params, 2);
    };
    NG::ViewAbstract::SetOnAreaChanged(frameNode, std::move(onAreaChange));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetOnAreaChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ViewAbstract::DisableOnAreaChange(frameNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetOnGestureJudgeBegin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(secondeArg->IsFunction(vm), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    panda::Local<panda::FunctionRef> func = obj;
    auto flag = FrameNodeBridge::IsCustomFrameNode(frameNode);
    auto onGestureJudgeBegin = [vm, func = JSFuncObjRef(panda::CopyableGlobal(vm, func), flag),
                                   node = AceType::WeakClaim(frameNode),
                                   containerId](const RefPtr<GestureInfo>& gestureInfo,
                                   const std::shared_ptr<BaseGestureEvent>& info) -> GestureJudgeResult {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        auto function = func.Lock();
        CHECK_NULL_RETURN(!function.IsEmpty(), GestureJudgeResult::CONTINUE);
        CHECK_NULL_RETURN(function->IsFunction(vm), GestureJudgeResult::CONTINUE);
        PipelineContext::SetCallBackNode(node);
        auto gestureInfoObj = CreateGestureInfo(vm, gestureInfo);
        auto gestureEventObj = CreateGestureEventInfo(vm, gestureInfo->GetType(), info);
        panda::Local<panda::JSValueRef> params[2] = { gestureInfoObj, gestureEventObj };
        auto returnValue = GestureJudgeResult::CONTINUE;
        auto value = function->Call(vm, function.ToLocal(), params, 2);
        if (value->IsNumber()) {
            returnValue = static_cast<GestureJudgeResult>(value->ToNumber(vm)->Value());
        }
        return returnValue;
    };
    NG::ViewAbstract::SetOnGestureJudgeBegin(frameNode, std::move(onGestureJudgeBegin));
    return panda::JSValueRef::Undefined(vm);
}

Local<panda::ObjectRef> CommonBridge::CreateTapGestureLocationInfo(
    EcmaVM* vm, const std::shared_ptr<BaseGestureEvent>& info)
{
    const std::list<FingerInfo>& fingerList = info->GetFingerList();
    if (fingerList.empty()) {
        return panda::ObjectRef::New(vm);
    }
    auto fingerInfo = info->GetFingerList().back();
    const OHOS::Ace::Offset& localLocation = fingerInfo.localLocation_;
    const OHOS::Ace::Offset& globalLocation = fingerInfo.globalLocation_;
    const OHOS::Ace::Offset& screenLocation = fingerInfo.screenLocation_;
    const OHOS::Ace::Offset& globalDisplayLocation = fingerInfo.globalDisplayLocation_;
    double density = PipelineBase::GetCurrentDensity();
    const char* keys[] = { "x", "y", "windowX", "windowY", "displayX", "displayY",
                           "globalDisplayX", "globalDisplayY"};
    density = density != 0 ? density : 1;
    Local<JSValueRef> values[] = {
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(localLocation.GetX())),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(localLocation.GetY())),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(globalLocation.GetX())),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(globalLocation.GetY())),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(screenLocation.GetX())),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(screenLocation.GetY())),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(globalDisplayLocation.GetX())),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(globalDisplayLocation.GetY())),
    };
    return panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
}

ArkUINativeModuleValue CommonBridge::ResetOnGestureJudgeBegin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ViewAbstract::SetOnGestureJudgeBegin(frameNode, nullptr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetOnGestureRecognizerJudgeBegin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(secondeArg->IsFunction(vm), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    panda::Local<panda::FunctionRef> func = obj;
    auto flag = FrameNodeBridge::IsCustomFrameNode(frameNode);
    auto onGestureRecognizerJudgeBegin =
        [vm, func = JSFuncObjRef(panda::CopyableGlobal(vm, func), flag), node = AceType::WeakClaim(frameNode),
            containerId](const std::shared_ptr<BaseGestureEvent>& info, const RefPtr<NGGestureRecognizer>& current,
            const std::list<RefPtr<NGGestureRecognizer>>& others) -> GestureJudgeResult {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        auto function = func.Lock();
        CHECK_NULL_RETURN(!function.IsEmpty(), GestureJudgeResult::CONTINUE);
        CHECK_NULL_RETURN(function->IsFunction(vm), GestureJudgeResult::CONTINUE);
        PipelineContext::SetCallBackNode(node);
        auto gestureInfo = current->GetGestureInfo();
        CHECK_NULL_RETURN(gestureInfo, GestureJudgeResult::CONTINUE);
        auto gestureEventObj = CreateGestureEventInfo(vm, gestureInfo->GetType(), info);
        auto currentObj = CreateRecognizerObject(vm, current);
        auto othersArr = panda::ArrayRef::New(vm);
        uint32_t othersIdx = 0;
        for (const auto& item : others) {
            auto othersObj = CreateRecognizerObject(vm, item);
            othersArr->SetValueAt(vm, othersArr, othersIdx++, othersObj);
        }
        auto touchRecognizers = CreateTouchRecognizersObject(vm, info, current);
        panda::Local<panda::JSValueRef> params[4] = { gestureEventObj, currentObj, othersArr, touchRecognizers };
        auto returnValue = GestureJudgeResult::CONTINUE;
        auto value = function->Call(vm, function.ToLocal(), params, 4);
        if (value->IsNumber()) {
            returnValue = static_cast<GestureJudgeResult>(value->ToNumber(vm)->Value());
        }
        return returnValue;
    };
    NG::ViewAbstract::SetOnGestureRecognizerJudgeBegin(frameNode, std::move(onGestureRecognizerJudgeBegin));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetOnGestureRecognizerJudgeBegin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ViewAbstract::SetOnGestureRecognizerJudgeBegin(frameNode, nullptr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetOnTouchTestDone(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(secondeArg->IsFunction(vm), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    panda::Local<panda::FunctionRef> func = obj;
    auto flag = FrameNodeBridge::IsCustomFrameNode(frameNode);
    auto onTouchTestDone = [vm, func = JSFuncObjRef(panda::CopyableGlobal(vm, func), flag),
                               node = AceType::WeakClaim(frameNode),
                               containerId](const std::shared_ptr<BaseGestureEvent>& info,
                               const std::list<RefPtr<NGGestureRecognizer>>& others) -> void {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        auto function = func.Lock();
        CHECK_NULL_VOID(!function.IsEmpty());
        CHECK_NULL_VOID(function->IsFunction(vm));
        PipelineContext::SetCallBackNode(node);
        auto gestureEventObj = CreateGestureEventInfo(vm, info);
        auto othersArr = panda::ArrayRef::New(vm);
        uint32_t othersIdx = 0;
        for (const auto& item : others) {
            auto othersObj = CreateRecognizerObject(vm, item);
            othersArr->SetValueAt(vm, othersArr, othersIdx++, othersObj);
        }
        panda::Local<panda::JSValueRef> params[2] = { gestureEventObj, othersArr };
        function->Call(vm, function.ToLocal(), params, 2);
    };
    NG::ViewAbstract::SetOnTouchTestDone(frameNode, std::move(onTouchTestDone));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetOnTouchTestDone(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ViewAbstract::SetOnTouchTestDone(frameNode, nullptr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetShouldBuiltInRecognizerParallelWith(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(secondeArg->IsFunction(vm), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    panda::Local<panda::FunctionRef> func = obj;
    auto flag = FrameNodeBridge::IsCustomFrameNode(frameNode);
    auto shouldBuiltInRecognizerParallelWithFunc =
        [vm, func = JSFuncObjRef(panda::CopyableGlobal(vm, func), flag), node = AceType::WeakClaim(frameNode),
            containerId](const RefPtr<NG::NGGestureRecognizer>& current,
            const std::vector<RefPtr<NG::NGGestureRecognizer>>& others) -> RefPtr<NG::NGGestureRecognizer> {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        auto function = func.Lock();
        CHECK_NULL_RETURN(!function.IsEmpty(), nullptr);
        CHECK_NULL_RETURN(function->IsFunction(vm), nullptr);
        PipelineContext::SetCallBackNode(node);
        auto currentObj = CreateRecognizerObject(vm, current);
        auto othersArr = panda::ArrayRef::New(vm);
        uint32_t othersIdx = 0;
        for (const auto& item : others) {
            auto othersObj = CreateRecognizerObject(vm, item);
            othersArr->SetValueAt(vm, othersArr, othersIdx++, othersObj);
        }
        panda::Local<panda::JSValueRef> params[2] = { currentObj, othersArr };
        auto value = function->Call(vm, function.ToLocal(), params, 2);
        if (!value->IsObject(vm)) {
            return nullptr;
        }
        RefPtr<NG::NGGestureRecognizer> returnValue = nullptr;
        auto valueObj = value->ToObject(vm);
        valueObj->Freeze(vm);
        auto jsObj = JSRef<JSObject>(JSObject(valueObj));
        returnValue = Referenced::Claim(jsObj->Unwrap<JSGestureRecognizer>())->GetRecognizer().Upgrade();
        return returnValue;
    };
    NG::ViewAbstract::SetShouldBuiltInRecognizerParallelWith(
        frameNode, std::move(shouldBuiltInRecognizerParallelWithFunc));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetShouldBuiltInRecognizerParallelWith(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ViewAbstract::SetShouldBuiltInRecognizerParallelWith(frameNode, nullptr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::AddTapGesture(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::JSValueRef::Undefined(vm));
    auto* nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    int32_t priority = 0;
    int32_t mask = 0;
    GetGestureCommonValue(runtimeCallInfo, priority, mask);
    int32_t fingers = DEFAULT_TAP_FINGER;
    int32_t count = DEFAULT_TAP_COUNT;
    double distanceThreshold = DEFAULT_TAP_DISTANCE;
    bool limitFingerCount = false;
    GetTapGestureValue(runtimeCallInfo, fingers, count, distanceThreshold, limitFingerCount, NUM_5);
    auto* gesture = GetArkUINodeModifiers()->getGestureModifier()->
        createTapGestureWithDistanceThreshold(count, fingers, distanceThreshold, limitFingerCount, nullptr);
    SetGestureTag(runtimeCallInfo, NUM_3, gesture);
    SetGestureAllowedTypes(runtimeCallInfo, NUM_4, gesture);
    SetOnGestureEvent(runtimeCallInfo, GestureEventAction::ACTION, NUM_8, gesture);
    GetArkUINodeModifiers()->getGestureModifier()->addGestureToNodeWithRefCountDecrease(
        nativeNode, gesture, priority, mask);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::AddLongPressGesture(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::JSValueRef::Undefined(vm));
    auto* nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    int32_t priority = 0;
    int32_t mask = 0;
    GetGestureCommonValue(runtimeCallInfo, priority, mask);
    int32_t fingers = DEFAULT_LONG_PRESS_FINGER;
    bool repeat = false;
    int32_t duration = DEFAULT_LONG_PRESS_DURATION;
    bool limitFingerCount = false;
    GetLongPressGestureValue(runtimeCallInfo, fingers, repeat, duration, limitFingerCount, NUM_5);
    auto* gesture = GetArkUINodeModifiers()->getGestureModifier()->createLongPressGesture(
        fingers, repeat, duration, limitFingerCount, nullptr);
    SetGestureTag(runtimeCallInfo, NUM_3, gesture);
    SetGestureAllowedTypes(runtimeCallInfo, NUM_4, gesture);
    SetOnGestureEvent(runtimeCallInfo, GestureEventAction::ACTION, NUM_9, gesture);
    SetOnGestureEvent(runtimeCallInfo, GestureEventAction::END, NUM_10, gesture);
    SetOnGestureEvent(runtimeCallInfo, GestureEventAction::CANCEL, NUM_11, gesture);
    GetArkUINodeModifiers()->getGestureModifier()->addGestureToNodeWithRefCountDecrease(
        nativeNode, gesture, priority, mask);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::AddPanGesture(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::JSValueRef::Undefined(vm));
    auto* nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    int32_t priority = 0;
    int32_t mask = 0;
    GetGestureCommonValue(runtimeCallInfo, priority, mask);
    int32_t fingers = DEFAULT_PAN_FINGER;
    int32_t direction = PanDirection::ALL;
    PanDistanceMapDimension distanceMap = { { SourceTool::UNKNOWN, DEFAULT_PAN_DISTANCE } };
    bool limitFingerCount = false;
    GetPanGestureValue(runtimeCallInfo, fingers, direction, distanceMap, limitFingerCount, NUM_5);
    auto* gesture = GetArkUINodeModifiers()->getGestureModifier()->createPanGesture(
        fingers, direction, distanceMap[SourceTool::UNKNOWN].ConvertToPx(), limitFingerCount, nullptr);
    SetGestureDistanceMap(runtimeCallInfo, NUM_9, gesture);
    SetGestureTag(runtimeCallInfo, NUM_3, gesture);
    SetGestureAllowedTypes(runtimeCallInfo, NUM_4, gesture);
    SetOnGestureEvent(runtimeCallInfo, GestureEventAction::START, NUM_10, gesture);
    SetOnGestureEvent(runtimeCallInfo, GestureEventAction::UPDATE, NUM_11, gesture);
    SetOnGestureEvent(runtimeCallInfo, GestureEventAction::END, NUM_12, gesture);
    SetOnGestureEvent(runtimeCallInfo, GestureEventAction::CANCEL, NUM_13, gesture);
    GetArkUINodeModifiers()->getGestureModifier()->addGestureToNodeWithRefCountDecrease(
        nativeNode, gesture, priority, mask);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::AddSwipeGesture(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::JSValueRef::Undefined(vm));
    auto* nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    int32_t priority = 0;
    int32_t mask = 0;
    GetGestureCommonValue(runtimeCallInfo, priority, mask);
    int32_t fingers = DEFAULT_SLIDE_FINGER;
    int32_t direction = SwipeDirection::ALL;
    double speed = DEFAULT_SLIDE_SPEED;
    bool limitFingerCount = false;
    GetSwipeGestureValue(runtimeCallInfo, fingers, direction, speed, limitFingerCount, NUM_5);
    auto* gesture =
        GetArkUINodeModifiers()->getGestureModifier()-> createSwipeGestureByModifier(
            fingers, direction, speed, limitFingerCount);
    SetGestureTag(runtimeCallInfo, NUM_3, gesture);
    SetGestureAllowedTypes(runtimeCallInfo, NUM_4, gesture);
    SetOnGestureEvent(runtimeCallInfo, GestureEventAction::ACTION, NUM_9, gesture);
    GetArkUINodeModifiers()->getGestureModifier()->addGestureToNodeWithRefCountDecrease(
        nativeNode, gesture, priority, mask);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::AddPinchGesture(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::JSValueRef::Undefined(vm));
    auto* nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    int32_t priority = 0;
    int32_t mask = 0;
    GetGestureCommonValue(runtimeCallInfo, priority, mask);
    int32_t fingers = DEFAULT_PINCH_FINGER;
    double distance = DEFAULT_PINCH_DISTANCE;
    bool limitFingerCount = false;
    GetPinchGestureValue(runtimeCallInfo, fingers, distance, limitFingerCount, NUM_5);
    auto* gesture = GetArkUINodeModifiers()->getGestureModifier()->createPinchGesture(
        fingers, distance, limitFingerCount, nullptr);
    SetGestureTag(runtimeCallInfo, NUM_3, gesture);
    SetGestureAllowedTypes(runtimeCallInfo, NUM_4, gesture);
    SetOnGestureEvent(runtimeCallInfo, GestureEventAction::START, NUM_8, gesture);
    SetOnGestureEvent(runtimeCallInfo, GestureEventAction::UPDATE, NUM_9, gesture);
    SetOnGestureEvent(runtimeCallInfo, GestureEventAction::END, NUM_10, gesture);
    SetOnGestureEvent(runtimeCallInfo, GestureEventAction::CANCEL, NUM_11, gesture);
    GetArkUINodeModifiers()->getGestureModifier()->addGestureToNodeWithRefCountDecrease(
        nativeNode, gesture, priority, mask);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::AddRotationGesture(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::JSValueRef::Undefined(vm));
    auto* nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    int32_t priority = 0;
    int32_t mask = 0;
    GetGestureCommonValue(runtimeCallInfo, priority, mask);
    int32_t fingers = DEFAULT_ROTATION_FINGER;
    double angle = DEFAULT_ROTATION_ANGLE;
    bool limitFingerCount = false;
    GetRotationGestureValue(runtimeCallInfo, fingers, angle, limitFingerCount, NUM_5);
    auto* gesture = GetArkUINodeModifiers()->getGestureModifier()->createRotationGesture(
        fingers, angle, limitFingerCount, nullptr);
    SetGestureTag(runtimeCallInfo, NUM_3, gesture);
    SetGestureAllowedTypes(runtimeCallInfo, NUM_4, gesture);
    SetOnGestureEvent(runtimeCallInfo, GestureEventAction::START, NUM_8, gesture);
    SetOnGestureEvent(runtimeCallInfo, GestureEventAction::UPDATE, NUM_9, gesture);
    SetOnGestureEvent(runtimeCallInfo, GestureEventAction::END, NUM_10, gesture);
    SetOnGestureEvent(runtimeCallInfo, GestureEventAction::CANCEL, NUM_11, gesture);
    GetArkUINodeModifiers()->getGestureModifier()->addGestureToNodeWithRefCountDecrease(
        nativeNode, gesture, priority, mask);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::AddGestureGroup(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    int32_t mode = 0;
    GetGestureModeValue(runtimeCallInfo, mode, NUM_3);
    auto* gesture = GetArkUINodeModifiers()->getGestureModifier()->createGestureGroup(mode);
    SetGestureTag(runtimeCallInfo, NUM_1, gesture);
    SetOnGestureEvent(runtimeCallInfo, GestureEventAction::CANCEL, NUM_2, gesture);
    return panda::NativePointerRef::New(vm, gesture);
}

ArkUINativeModuleValue CommonBridge::AddTapGestureToGroup(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    int32_t fingers = DEFAULT_TAP_FINGER;
    int32_t count = DEFAULT_TAP_COUNT;
    double distanceThreshold = DEFAULT_TAP_DISTANCE;
    bool limitFingerCount = false;
    GetTapGestureValue(runtimeCallInfo, fingers, count, distanceThreshold, limitFingerCount, NUM_3);
    auto* gesture = GetArkUINodeModifiers()->getGestureModifier()->
        createTapGestureWithDistanceThreshold(count, fingers, distanceThreshold, limitFingerCount, nullptr);
    SetGestureTag(runtimeCallInfo, NUM_1, gesture);
    SetGestureAllowedTypes(runtimeCallInfo, NUM_2, gesture);
    SetOnGestureEvent(runtimeCallInfo, GestureEventAction::ACTION, NUM_6, gesture);
    auto* group = GetGestureGroup(runtimeCallInfo, NUM_7);
    GetArkUINodeModifiers()->getGestureModifier()->addGestureToGestureGroupWithRefCountDecrease(group, gesture);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::AddLongPressGestureToGroup(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    int32_t fingers = DEFAULT_LONG_PRESS_FINGER;
    bool repeat = false;
    int32_t duration = DEFAULT_LONG_PRESS_DURATION;
    bool limitFingerCount = false;
    GetLongPressGestureValue(runtimeCallInfo, fingers, repeat, duration, limitFingerCount, NUM_3);
    auto* gesture = GetArkUINodeModifiers()->getGestureModifier()->createLongPressGesture(
        fingers, repeat, duration, limitFingerCount, nullptr);
    SetGestureTag(runtimeCallInfo, NUM_1, gesture);
    SetGestureAllowedTypes(runtimeCallInfo, NUM_2, gesture);
    SetOnGestureEvent(runtimeCallInfo, GestureEventAction::ACTION, NUM_7, gesture);
    SetOnGestureEvent(runtimeCallInfo, GestureEventAction::END, NUM_8, gesture);
    SetOnGestureEvent(runtimeCallInfo, GestureEventAction::CANCEL, NUM_9, gesture);
    auto* group = GetGestureGroup(runtimeCallInfo, NUM_10);
    GetArkUINodeModifiers()->getGestureModifier()->addGestureToGestureGroupWithRefCountDecrease(group, gesture);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::AddPanGestureToGroup(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    int32_t fingers = DEFAULT_PAN_FINGER;
    int32_t direction = PanDirection::ALL;
    PanDistanceMapDimension distanceMap = { { SourceTool::UNKNOWN, DEFAULT_PAN_DISTANCE } };
    bool limitFingerCount = false;
    GetPanGestureValue(runtimeCallInfo, fingers, direction, distanceMap, limitFingerCount, NUM_3);
    auto* gesture = GetArkUINodeModifiers()->getGestureModifier()->createPanGesture(
        fingers, direction, distanceMap[SourceTool::UNKNOWN].ConvertToPx(), limitFingerCount, nullptr);
    SetGestureDistanceMap(runtimeCallInfo, NUM_7, gesture);
    SetGestureTag(runtimeCallInfo, NUM_1, gesture);
    SetGestureAllowedTypes(runtimeCallInfo, NUM_2, gesture);
    SetOnGestureEvent(runtimeCallInfo, GestureEventAction::START, NUM_8, gesture);
    SetOnGestureEvent(runtimeCallInfo, GestureEventAction::UPDATE, NUM_9, gesture);
    SetOnGestureEvent(runtimeCallInfo, GestureEventAction::END, NUM_10, gesture);
    SetOnGestureEvent(runtimeCallInfo, GestureEventAction::CANCEL, NUM_11, gesture);
    auto* group = GetGestureGroup(runtimeCallInfo, NUM_12);
    GetArkUINodeModifiers()->getGestureModifier()->addGestureToGestureGroupWithRefCountDecrease(group, gesture);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::AddSwipeGestureToGroup(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    int32_t fingers = DEFAULT_SLIDE_FINGER;
    int32_t direction = SwipeDirection::ALL;
    double speed = DEFAULT_SLIDE_SPEED;
    bool limitFingerCount = false;
    GetSwipeGestureValue(runtimeCallInfo, fingers, direction, speed, limitFingerCount, NUM_3);
    auto* gesture =
        GetArkUINodeModifiers()->getGestureModifier()->createSwipeGestureByModifier(
            fingers, direction, speed, limitFingerCount);
    SetGestureTag(runtimeCallInfo, NUM_1, gesture);
    SetGestureAllowedTypes(runtimeCallInfo, NUM_2, gesture);
    SetOnGestureEvent(runtimeCallInfo, GestureEventAction::ACTION, NUM_7, gesture);
    auto* group = GetGestureGroup(runtimeCallInfo, NUM_8);
    GetArkUINodeModifiers()->getGestureModifier()->addGestureToGestureGroupWithRefCountDecrease(group, gesture);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::AddPinchGestureToGroup(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    int32_t fingers = DEFAULT_PINCH_FINGER;
    double distance = DEFAULT_PINCH_DISTANCE;
    bool limitFingerCount = false;
    GetPinchGestureValue(runtimeCallInfo, fingers, distance, limitFingerCount, NUM_3);
    auto* gesture = GetArkUINodeModifiers()->getGestureModifier()->createPinchGesture(
        fingers, distance, limitFingerCount, nullptr);
    SetGestureTag(runtimeCallInfo, NUM_1, gesture);
    SetGestureAllowedTypes(runtimeCallInfo, NUM_2, gesture);
    SetOnGestureEvent(runtimeCallInfo, GestureEventAction::START, NUM_6, gesture);
    SetOnGestureEvent(runtimeCallInfo, GestureEventAction::UPDATE, NUM_7, gesture);
    SetOnGestureEvent(runtimeCallInfo, GestureEventAction::END, NUM_8, gesture);
    SetOnGestureEvent(runtimeCallInfo, GestureEventAction::CANCEL, NUM_9, gesture);
    auto* group = GetGestureGroup(runtimeCallInfo, NUM_10);
    GetArkUINodeModifiers()->getGestureModifier()->addGestureToGestureGroupWithRefCountDecrease(group, gesture);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::AddRotationGestureToGroup(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    int32_t fingers = DEFAULT_ROTATION_FINGER;
    double angle = DEFAULT_ROTATION_ANGLE;
    bool limitFingerCount = false;
    GetRotationGestureValue(runtimeCallInfo, fingers, angle, limitFingerCount, NUM_3);
    auto* gesture = GetArkUINodeModifiers()->getGestureModifier()->createRotationGesture(
        fingers, angle, limitFingerCount, nullptr);
    SetGestureTag(runtimeCallInfo, NUM_1, gesture);
    SetGestureAllowedTypes(runtimeCallInfo, NUM_2, gesture);
    SetOnGestureEvent(runtimeCallInfo, GestureEventAction::START, NUM_6, gesture);
    SetOnGestureEvent(runtimeCallInfo, GestureEventAction::UPDATE, NUM_7, gesture);
    SetOnGestureEvent(runtimeCallInfo, GestureEventAction::END, NUM_8, gesture);
    SetOnGestureEvent(runtimeCallInfo, GestureEventAction::CANCEL, NUM_9, gesture);
    auto* group = GetGestureGroup(runtimeCallInfo, NUM_10);
    GetArkUINodeModifiers()->getGestureModifier()->addGestureToGestureGroupWithRefCountDecrease(group, gesture);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::AddGestureGroupToGroup(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    int32_t mode = 2;
    GetGestureModeValue(runtimeCallInfo, mode, NUM_3);
    auto* gesture = GetArkUINodeModifiers()->getGestureModifier()->createGestureGroup(mode);
    SetGestureTag(runtimeCallInfo, NUM_1, gesture);
    SetOnGestureEvent(runtimeCallInfo, GestureEventAction::CANCEL, NUM_2, gesture);
    auto* group = GetGestureGroup(runtimeCallInfo, NUM_4);
    GetArkUINodeModifiers()->getGestureModifier()->addGestureToGestureGroupWithRefCountDecrease(group, gesture);
    return panda::NativePointerRef::New(vm, gesture);
}

ArkUINativeModuleValue CommonBridge::AttachGestureGroup(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::JSValueRef::Undefined(vm));
    auto* nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    int32_t priority = 0;
    int32_t mask = 0;
    GetGestureCommonValue(runtimeCallInfo, priority, mask);
    auto* group = GetGestureGroup(runtimeCallInfo, NUM_3);
    GetArkUINodeModifiers()->getGestureModifier()->addGestureToNodeWithRefCountDecrease(
        nativeNode, group, priority, mask);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::RemoveGestureByTag(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::JSValueRef::Undefined(vm));
    auto* nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> gestureTagArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (!gestureTagArg.IsNull() && !gestureTagArg->IsUndefined()) {
        auto tag = gestureTagArg->ToString(vm)->ToString(vm);
        GetArkUINodeModifiers()->getGestureModifier()->removeGestureFromNodeByTag(nativeNode, tag.c_str());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ClearGestures(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::JSValueRef::Undefined(vm));
    auto* nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getGestureModifier()->clearGestures(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::GetWindowName(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(context, panda::JSValueRef::Undefined(vm));
    auto window = context->GetWindow();
    CHECK_NULL_RETURN(window, panda::JSValueRef::Undefined(vm));
    std::string windowName = window->GetWindowName();
    return panda::StringRef::NewFromUtf8(vm, windowName.c_str());
}

ArkUINativeModuleValue CommonBridge::GetWindowWidthBreakpoint(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, panda::JSValueRef::Undefined(vm));
    auto window = container->GetWindow();
    CHECK_NULL_RETURN(window, panda::JSValueRef::Undefined(vm));

    WidthLayoutBreakPoint layoutBreakpoints = SystemProperties::GetWidthLayoutBreakpoints();
    WidthBreakpoint breakpoint = window->GetWidthBreakpoint(layoutBreakpoints);

    return panda::IntegerRef::NewFromUnsigned(vm, static_cast<uint32_t>(breakpoint));
}

ArkUINativeModuleValue CommonBridge::GetWindowHeightBreakpoint(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, panda::JSValueRef::Undefined(vm));
    auto window = container->GetWindow();
    CHECK_NULL_RETURN(window, panda::JSValueRef::Undefined(vm));

    HeightLayoutBreakPoint layoutBreakpoints = SystemProperties::GetHeightLayoutBreakpoints();
    HeightBreakpoint breakpoint = window->GetHeightBreakpoint(layoutBreakpoints);

    return panda::IntegerRef::NewFromUnsigned(vm, static_cast<uint32_t>(breakpoint));
}

ArkUINativeModuleValue CommonBridge::FreezeUINodeById(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> idArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> isFreezeArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (!idArg->IsString(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    std::string id = idArg->ToString(vm)->ToString(vm);
    bool isFreeze = false;
    if (isFreezeArg->IsBoolean()) {
        isFreeze = isFreezeArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getCommonModifier()->freezeUINodeById(id.c_str(), isFreeze);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->freezeUINodeById(id.c_str(), false);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::FreezeUINodeByUniqueId(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> uniqueIdArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> isFreezeArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (!uniqueIdArg->IsNumber()) {
        return panda::JSValueRef::Undefined(vm);
    }
    int32_t uniqueId = uniqueIdArg->IntegerValue(vm);
    bool isFreeze = false;
    if (isFreezeArg->IsBoolean()) {
        isFreeze = isFreezeArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getCommonModifier()->freezeUINodeByUniqueId(uniqueId, isFreeze);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->freezeUINodeByUniqueId(uniqueId, false);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetSystemBarEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::JSValueRef::Undefined(vm));
    auto* nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> enableArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (enableArg->IsBoolean()) {
        auto enable = enableArg->ToBoolean(vm);
        GetArkUINodeModifiers()->getCommonModifier()->setSystemBarEffect(nativeNode, enable->Value());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::PostFrameCallback(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));

    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0); // frameCallback
    if (firstArg->IsNull() || firstArg->IsUndefined() || !firstArg->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameCallback = firstArg->ToObject(vm);

    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    int64_t delayMillis = 0;
    if (secondArg->IsNumber()) {
        delayMillis = secondArg->IntegerValue(vm);
    }

    if (frameCallback->IsNull() || frameCallback->IsUndefined() || !frameCallback->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }

    FrameCallbackFunc onFrameCallbackFunc = nullptr;
    FrameCallbackFuncFromCAPI onIdleCallbackFunc = nullptr;

    if (frameCallback->Get(vm, "onFrame")->IsFunction(vm)) {
        onFrameCallbackFunc = [vm, frameCallbackObj =
            panda::CopyableGlobal(vm, frameCallback)](int64_t nanoTimestamp) -> void {
            LocalScope scope(vm);
            Local<FunctionRef> onFrameFunc = frameCallbackObj->Get(vm, "onFrame");

            auto nanoTimestampRef = NumberRef::New(vm, nanoTimestamp);
            Local<JSValueRef> params[] = { nanoTimestampRef };
            onFrameFunc->Call(vm, frameCallbackObj.ToLocal(), params, 1);
        };
    }

    if (frameCallback->Get(vm, "onIdle")->IsFunction(vm)) {
        onIdleCallbackFunc = [vm, frameCallbackObj =
            panda::CopyableGlobal(vm, frameCallback)](int64_t nanoTimestamp, int32_t frameCount) -> void {
            LocalScope scope(vm);
            Local<FunctionRef> onIdleFunc = frameCallbackObj->Get(vm, "onIdle");

            auto nanoTimestampRef = NumberRef::New(vm, nanoTimestamp);
            Local<JSValueRef> params[] = { nanoTimestampRef };
            onIdleFunc->Call(vm, frameCallbackObj.ToLocal(), params, 1);
        };
    }

    if (onFrameCallbackFunc == nullptr && onIdleCallbackFunc == nullptr) {
        return panda::JSValueRef::Undefined(vm);
    }

    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(context, panda::JSValueRef::Undefined(vm));
    context->AddFrameCallback(std::move(onFrameCallbackFunc), std::move(onIdleCallbackFunc), delayMillis);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetFocusScopeId(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getCommonModifier()->resetFocusScopeId(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetFocusScopeId(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> idArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> isGroupArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> arrowKeyStepOutArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    if (!idArg->IsString(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto id = idArg->ToString(vm)->ToString(vm);
    bool isGroup = false;
    if (isGroupArg->IsBoolean()) {
        isGroup = isGroupArg->ToBoolean(vm)->Value();
    }
    bool arrowKeyStepOut = true;
    if (arrowKeyStepOutArg->IsBoolean()) {
        arrowKeyStepOut = arrowKeyStepOutArg->ToBoolean(vm)->Value();
    }
    GetArkUINodeModifiers()->getCommonModifier()->setFocusScopeId(nativeNode, id.c_str(), isGroup, arrowKeyStepOut);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetFocusScopePriority(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getCommonModifier()->resetFocusScopePriority(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetFocusScopePriority(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> scopeIdArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> priorityArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    if (!scopeIdArg->IsString(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto scopeId = scopeIdArg->ToString(vm)->ToString(vm);
    int32_t priority = 0;
    if (priorityArg->IsNumber()) {
        priority = priorityArg->Int32Value(vm);
    }
    GetArkUINodeModifiers()->getCommonModifier()->setFocusScopePriority(nativeNode, scopeId.c_str(), priority);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CommonBridge::SetPixelRound(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    auto startArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto topArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    auto endArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    auto bottomArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    if (startArg->IsUndefined() && topArg->IsUndefined() && endArg->IsUndefined() && bottomArg->IsUndefined()) {
        GetArkUINodeModifiers()->getCommonModifier()->resetPixelRound(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    int32_t values[] = { -1, -1, -1, -1 };
    if (startArg->IsInt()) {
        values[NUM_0] = startArg->Int32Value(vm);
    }
    if (topArg->IsInt()) {
        values[NUM_1] = topArg->Int32Value(vm);
    }
    if (endArg->IsInt()) {
        values[NUM_2] = endArg->Int32Value(vm);
    }
    if (bottomArg->IsInt()) {
        values[NUM_3] = bottomArg->Int32Value(vm);
    }
    GetArkUINodeModifiers()->getCommonModifier()->setPixelRound(
        nativeNode, values, (sizeof(values) / sizeof(values[NUM_0])));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetPixelRound(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetPixelRound(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::GreatOrEqualAPITargetVersion(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));

    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (firstArg->IsNull() || firstArg->IsUndefined() || !firstArg->IsNumber()) {
        return panda::BooleanRef::New(vm, false);
    }
    int32_t apiTargetVersion = firstArg->Int32Value(vm);
    auto platformVersion = static_cast<PlatformVersion>(apiTargetVersion);
    return panda::BooleanRef::New(vm, Container::GreatOrEqualAPITargetVersion(platformVersion));
}

ArkUINativeModuleValue CommonBridge::LessThanAPITargetVersion(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));

    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (firstArg->IsNull() || firstArg->IsUndefined() || !firstArg->IsNumber()) {
        return panda::BooleanRef::New(vm, false);
    }
    int32_t apiTargetVersion = firstArg->Int32Value(vm);
    auto platformVersion = static_cast<PlatformVersion>(apiTargetVersion);
    return panda::BooleanRef::New(vm, Container::LessThanAPITargetVersion(platformVersion));
}

ArkUINativeModuleValue CommonBridge::GetApiTargetVersion(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));

    auto container = Container::CurrentSafely();
    CHECK_NULL_RETURN(container, panda::JSValueRef::Undefined(vm));
    int32_t apiTargetVersion = container->GetApiTargetVersion();
    return panda::NumberRef::New(vm, apiTargetVersion);
}

ArkUINativeModuleValue CommonBridge::SetFocusBox(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    auto marginArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto widthArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    auto colorArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    ArkUI_Uint32 hasValue = 0;
    CalcDimension margin;
    std::vector<RefPtr<ResourceObject>> focusBoxResObjs;
    RefPtr<ResourceObject> resObjMargin;
    if (!marginArg->IsUndefined() && !marginArg->IsNull()) {
        if (ArkTSUtils::ParseJsDimensionFpNG(vm, marginArg, margin, resObjMargin, false)) {
            hasValue = 1;
        } else if (ArkTSUtils::ParseJsLengthMetrics(vm, marginArg, margin, resObjMargin)) {
            hasValue = 1;
        }
    }
    focusBoxResObjs.push_back(resObjMargin);
    hasValue = hasValue << 1;
    CalcDimension width;
    RefPtr<ResourceObject> resObjWidth;
    if (!widthArg->IsUndefined() && !widthArg->IsNull()) {
        if (ArkTSUtils::ParseJsDimensionFpNG(vm, widthArg, width, resObjWidth, false) && GreatOrEqual(width.Value(), 0.0f)) {
            hasValue += 1;
        } else if (ArkTSUtils::ParseJsLengthMetrics(vm, widthArg, width, resObjWidth) && GreatOrEqual(width.Value(), 0.0f)) {
            hasValue += 1;
        }
    }
    focusBoxResObjs.push_back(resObjWidth);
    hasValue = hasValue << 1;
    Color strokeColor;
    RefPtr<ResourceObject> resObjColor;
    if (!colorArg->IsUndefined() && !colorArg->IsNull() &&
        ArkTSUtils::ParseColorMetricsToColor(vm, colorArg, strokeColor, resObjColor)) {
        hasValue += 1;
        auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
        ArkTSUtils::CompleteResourceObjectFromColor(resObjColor, strokeColor, true, nodeInfo);
    }
    focusBoxResObjs.push_back(resObjColor);
    GetArkUINodeModifiers()->getCommonModifier()->setFocusBoxStyle(nativeNode, margin.Value(),
        static_cast<int>(margin.Unit()), width.Value(), static_cast<int>(width.Unit()), strokeColor.GetValue(),
        hasValue, static_cast<void*>(&focusBoxResObjs));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetFocusBox(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetFocusBoxStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetNextFocus(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    ArkUI_Uint32 hasValue = 0;
    std::string nextFocusArray[NUM_6];
    auto forward = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto backward = runtimeCallInfo->GetCallArgRef(NUM_2);
    auto up = runtimeCallInfo->GetCallArgRef(NUM_3);
    auto down = runtimeCallInfo->GetCallArgRef(NUM_4);
    auto left = runtimeCallInfo->GetCallArgRef(NUM_5);
    auto right = runtimeCallInfo->GetCallArgRef(NUM_6);
    if (forward->IsString(vm)) {
        nextFocusArray[NUM_0] = forward->ToString(vm)->ToString(vm);
        hasValue = 1;
    }
    hasValue = hasValue << 1;
    if (backward->IsString(vm)) {
        nextFocusArray[NUM_1] = backward->ToString(vm)->ToString(vm);
        hasValue += 1;
    }
    hasValue = hasValue << 1;
    if (up->IsString(vm)) {
        nextFocusArray[NUM_2] = up->ToString(vm)->ToString(vm);
        hasValue += 1;
    }
    hasValue = hasValue << 1;
    if (down->IsString(vm)) {
        nextFocusArray[NUM_3] = down->ToString(vm)->ToString(vm);
        hasValue += 1;
    }
    hasValue = hasValue << 1;
    if (left->IsString(vm)) {
        nextFocusArray[NUM_4] = left->ToString(vm)->ToString(vm);
        hasValue += 1;
    }
    hasValue = hasValue << 1;
    if (right->IsString(vm)) {
        nextFocusArray[NUM_5] = right->ToString(vm)->ToString(vm);
        hasValue += 1;
    }
    GetArkUINodeModifiers()->getCommonModifier()->setNextFocus(nativeNode,
        nextFocusArray[NUM_0].c_str(), nextFocusArray[NUM_1].c_str(),
        nextFocusArray[NUM_2].c_str(), nextFocusArray[NUM_3].c_str(),
        nextFocusArray[NUM_4].c_str(), nextFocusArray[NUM_5].c_str(), hasValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetNextFocus(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetNextFocus(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

Local<panda::ObjectRef> CommonBridge::CreateFocusAxisEventInfo(EcmaVM* vm, NG::FocusAxisEventInfo& info)
{
    auto axisMap = panda::MapRef::New(vm);
    axisMap->Set(vm, panda::NumberRef::New(vm, static_cast<int>(NG::AxisModel::ABS_X)),
        panda::NumberRef::New(vm, info.GetAbsXValue()));
    axisMap->Set(vm, panda::NumberRef::New(vm, static_cast<int>(NG::AxisModel::ABS_Y)),
        panda::NumberRef::New(vm, info.GetAbsYValue()));
    axisMap->Set(vm, panda::NumberRef::New(vm, static_cast<int>(NG::AxisModel::ABS_Z)),
        panda::NumberRef::New(vm, info.GetAbsZValue()));
    axisMap->Set(vm, panda::NumberRef::New(vm, static_cast<int>(NG::AxisModel::ABS_RZ)),
        panda::NumberRef::New(vm, info.GetAbsRzValue()));
    axisMap->Set(vm, panda::NumberRef::New(vm, static_cast<int>(NG::AxisModel::ABS_GAS)),
        panda::NumberRef::New(vm, info.GetAbsGasValue()));
    axisMap->Set(vm, panda::NumberRef::New(vm, static_cast<int>(NG::AxisModel::ABS_BRAKE)),
        panda::NumberRef::New(vm, info.GetAbsBrakeValue()));
    axisMap->Set(vm, panda::NumberRef::New(vm, static_cast<int>(NG::AxisModel::ABS_HAT0X)),
        panda::NumberRef::New(vm, info.GetAbsHat0XValue()));
    axisMap->Set(vm, panda::NumberRef::New(vm, static_cast<int>(NG::AxisModel::ABS_HAT0Y)),
        panda::NumberRef::New(vm, info.GetAbsHat0YValue()));
    const char* keys[] = { "axisMap", "target", "timestamp", "source", "pressure", "tiltX", "tiltY", "sourceTool",
        "deviceId", "getModifierKeyState", "stopPropagation", "targetDisplayId" };
    Local<JSValueRef> values[] = { axisMap, FrameNodeBridge::CreateEventTargetObject(vm, info),
        panda::NumberRef::New(vm, static_cast<double>(info.GetTimeStamp().time_since_epoch().count())),
        panda::NumberRef::New(vm, static_cast<int32_t>(info.GetSourceDevice())),
        panda::NumberRef::New(vm, info.GetForce()),
        panda::NumberRef::New(vm, static_cast<int32_t>(info.GetTiltX().value_or(0.0f))),
        panda::NumberRef::New(vm, static_cast<int32_t>(info.GetTiltY().value_or(0.0f))),
        panda::NumberRef::New(vm, static_cast<int32_t>(static_cast<int32_t>(info.GetSourceTool()))),
        panda::NumberRef::New(vm, info.GetDeviceId()), panda::FunctionRef::New(vm, ArkTSUtils::JsGetModifierKeyState),
        panda::FunctionRef::New(vm, Framework::JsStopPropagation),
        panda::NumberRef::New(vm, (info.GetTargetDisplayId()))};
    auto obj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
    obj->SetNativePointerFieldCount(vm, 1);
    obj->SetNativePointerField(vm, 0, static_cast<void*>(&info));
    return obj;
}

ArkUINativeModuleValue CommonBridge::SetOnFocusAxisEvent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(secondeArg->IsFunction(vm), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    panda::Local<panda::FunctionRef> func = obj;
    auto flag = FrameNodeBridge::IsCustomFrameNode(frameNode);
    auto onFocusAxisEvent = [vm, func = JSFuncObjRef(panda::CopyableGlobal(vm, func), flag),
                                node = AceType::WeakClaim(frameNode), containerId](FocusAxisEventInfo& info) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        auto function = func.Lock();
        CHECK_NULL_VOID(!function.IsEmpty());
        CHECK_NULL_VOID(function->IsFunction(vm));
        PipelineContext::SetCallBackNode(node);
        auto obj = CreateFocusAxisEventInfo(vm, info);
        panda::Local<panda::JSValueRef> params[] = { obj };
        function->Call(vm, function.ToLocal(), params, 1);
    };
    NG::ViewAbstract::SetOnFocusAxisEvent(frameNode, std::move(onFocusAxisEvent));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetOnFocusAxisEvent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ViewAbstract::DisableOnFocusAxisEvent(frameNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::RegisterFrameNodeDestructorCallback(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    if (secondeArg->IsNull() || secondeArg->IsUndefined()) {
        frameNode->SetFrameNodeDestructorCallback(nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    CHECK_NULL_RETURN(secondeArg->IsFunction(vm), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    CHECK_NULL_RETURN(containerId != -1, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = obj;
    auto frameNodeDestructorCallback = [vm, func = JsWeak(panda::CopyableGlobal(vm, func)),
                                           node = AceType::WeakClaim(frameNode), containerId](int32_t frameNodeId) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        auto function = func.Lock();
        CHECK_NULL_VOID(!function.IsEmpty());
        CHECK_NULL_VOID(function->IsFunction(vm));
        PipelineContext::SetCallBackNode(node);
        auto frameNodeIdParam = panda::NumberRef::New(vm, frameNodeId);
        panda::Local<panda::JSValueRef> params[] = { frameNodeIdParam };
        function->Call(vm, function.ToLocal(), params, 1);
    };
    frameNode->SetFrameNodeDestructorCallback(std::move(frameNodeDestructorCallback));
    return panda::JSValueRef::Undefined(vm);
}

Local<panda::ObjectRef> CommonBridge::CreateAxisEventInfo(EcmaVM* vm, AxisInfo& info)
{
    const Offset& globalOffset = info.GetGlobalLocation();
    const Offset& localOffset = info.GetLocalLocation();
    const Offset& screenOffset = info.GetScreenLocation();
    const Offset& globalDisplayOffset = info.GetGlobalDisplayLocation();
    double density = PipelineBase::GetCurrentDensity();
    const char* keys[] = { "action", "displayX", "displayY", "windowX", "windowY", "x", "y", "scrollStep",
        "propagation", "getHorizontalAxisValue", "getVerticalAxisValue", "getPinchAxisValue", "target",
        "timestamp", "source", "pressure", "tiltX", "tiltY", "sourceTool", "deviceId", "getModifierKeyState",
        "axisVertical", "axisHorizontal", "globalDisplayX", "globalDisplayY", "targetDisplayId" };
    Local<JSValueRef> values[] = { panda::NumberRef::New(vm, static_cast<int32_t>(info.GetAction())),
        panda::NumberRef::New(vm, screenOffset.GetX() / density),
        panda::NumberRef::New(vm, screenOffset.GetY() / density),
        panda::NumberRef::New(vm, globalOffset.GetX() / density),
        panda::NumberRef::New(vm, globalOffset.GetY() / density),
        panda::NumberRef::New(vm, localOffset.GetX() / density),
        panda::NumberRef::New(vm, localOffset.GetY() / density), panda::NumberRef::New(vm, info.GetScrollStep()),
        panda::FunctionRef::New(vm, Framework::JsPropagation),
        panda::FunctionRef::New(vm, ArkTSUtils::JsGetHorizontalAxisValue),
        panda::FunctionRef::New(vm, ArkTSUtils::JsGetVerticalAxisValue),
        panda::FunctionRef::New(vm, ArkTSUtils::JsGetPinchAxisValue),
        FrameNodeBridge::CreateEventTargetObject(vm, info),
        panda::NumberRef::New(vm, static_cast<double>(info.GetTimeStamp().time_since_epoch().count())),
        panda::NumberRef::New(vm, static_cast<int32_t>(info.GetSourceDevice())),
        panda::NumberRef::New(vm, info.GetForce()),
        panda::NumberRef::New(vm, static_cast<int32_t>(info.GetTiltX().value_or(0.0f))),
        panda::NumberRef::New(vm, static_cast<int32_t>(info.GetTiltY().value_or(0.0f))),
        panda::NumberRef::New(vm, static_cast<int32_t>(static_cast<int32_t>(info.GetSourceTool()))),
        panda::NumberRef::New(vm, info.GetDeviceId()),
        panda::FunctionRef::New(vm, ArkTSUtils::JsGetModifierKeyState),
        panda::NumberRef::New(vm, info.GetVerticalAxis()),
        panda::NumberRef::New(vm, info.GetHorizontalAxis()),
        panda::NumberRef::New(vm, globalDisplayOffset.GetX() / density),
        panda::NumberRef::New(vm, globalDisplayOffset.GetY() / density),
        panda::NumberRef::New(vm, info.GetTargetDisplayId()) };
    auto obj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
    obj->SetNativePointerFieldCount(vm, 1);
    obj->SetNativePointerField(vm, 0, static_cast<void*>(&info));
    return obj;
}

ArkUINativeModuleValue CommonBridge::SetOnAxisEvent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(secondeArg->IsFunction(vm), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    panda::Local<panda::FunctionRef> func = obj;
    auto flag = FrameNodeBridge::IsCustomFrameNode(frameNode);
    auto onAxisEvent = [vm, func = JSFuncObjRef(panda::CopyableGlobal(vm, func), flag),
                           node = AceType::WeakClaim(frameNode), containerId](AxisInfo& info) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        auto function = func.Lock();
        CHECK_NULL_VOID(!function.IsEmpty());
        CHECK_NULL_VOID(function->IsFunction(vm));
        PipelineContext::SetCallBackNode(node);
        auto obj = CreateAxisEventInfo(vm, info);
        panda::Local<panda::JSValueRef> params[] = { obj };
        function->Call(vm, function.ToLocal(), params, 1);
    };
    NG::ViewAbstract::SetOnAxisEvent(frameNode, std::move(onAxisEvent));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetOnAxisEvent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ViewAbstract::DisableOnAxisEvent(frameNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetVisualEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> visualEffectArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (visualEffectArg->IsNull() || visualEffectArg->IsUndefined()) {
        nodeModifiers->getCommonModifier()->resetVisualEffect(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    auto jsVal = info[NUM_1];
    auto visualEffect = Framework::UnwrapNapiValue(jsVal);
    nodeModifiers->getCommonModifier()->setVisualEffect(nativeNode, visualEffect);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetVisualEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getCommonModifier()->resetVisualEffect(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetBackgroundFilter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> backgroundFilterArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (backgroundFilterArg->IsNull() || backgroundFilterArg->IsUndefined()) {
        nodeModifiers->getCommonModifier()->resetBackgroundFilter(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    auto jsVal = info[NUM_1];
    auto backgroundFilter = Framework::UnwrapNapiValue(jsVal);
    nodeModifiers->getCommonModifier()->setBackgroundFilter(nativeNode, backgroundFilter);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetBackgroundFilter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getCommonModifier()->resetBackgroundFilter(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetForegroundFilter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> foregroundFilterArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (foregroundFilterArg->IsNull() || foregroundFilterArg->IsUndefined()) {
        nodeModifiers->getCommonModifier()->resetForegroundFilter(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    auto jsVal = info[NUM_1];
    auto foregroundFilter = Framework::UnwrapNapiValue(jsVal);
    nodeModifiers->getCommonModifier()->setForegroundFilter(nativeNode, foregroundFilter);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetForegroundFilter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getCommonModifier()->resetForegroundFilter(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetCompositingFilter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> compositingFilterArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (compositingFilterArg->IsNull() || compositingFilterArg->IsUndefined()) {
        nodeModifiers->getCommonModifier()->resetCompositingFilter(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    auto jsVal = info[NUM_1];
    auto compositingFilter = Framework::UnwrapNapiValue(jsVal);
    nodeModifiers->getCommonModifier()->setCompositingFilter(nativeNode, compositingFilter);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetCompositingFilter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getCommonModifier()->resetCompositingFilter(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetFreeze(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> freezeArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (freezeArg->IsBoolean()) {
        bool freeze = freezeArg->ToBoolean(vm)->Value();
        nodeModifiers->getCommonModifier()->setFreeze(nativeNode, freeze);
        return panda::JSValueRef::Undefined(vm);
    }
    nodeModifiers->getCommonModifier()->resetFreeze(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetFreeze(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getCommonModifier()->resetFreeze(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetOnPreDrag(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(secondeArg->IsFunction(vm), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    panda::Local<panda::FunctionRef> func = obj;
    auto flag = FrameNodeBridge::IsCustomFrameNode(frameNode);
    auto onPreDrag = [vm, func = JSFuncObjRef(panda::CopyableGlobal(vm, func), flag),
                         node = AceType::WeakClaim(frameNode), containerId](const PreDragStatus& preDragStatus) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        auto function = func.Lock();
        CHECK_EQUAL_VOID(function.IsEmpty(), true);
        CHECK_EQUAL_VOID(function->IsFunction(vm), false);
        PipelineContext::SetCallBackNode(node);
        auto preDragStatusParam = panda::NumberRef::New(vm, static_cast<int32_t>(preDragStatus));
        panda::Local<panda::JSValueRef> params[] = { preDragStatusParam };
        function->Call(vm, function.ToLocal(), params, NUM_1);
    };
    NG::ViewAbstract::SetOnPreDrag(frameNode, std::move(onPreDrag));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetOnPreDrag(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ViewAbstract::DisableOnPreDrag(frameNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetOnVisibleAreaChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    JsiRef<JsiValue> secondArg =
        JsiRef<JsiValue>::FastMake(runtimeCallInfo->GetVM(), runtimeCallInfo->GetCallArgRef(NUM_1));
    CHECK_NULL_RETURN(secondArg->IsArray(), panda::JSValueRef::Undefined(vm));
    auto ratioArray = JSRef<JSArray>::Cast(secondArg);
    size_t size = ratioArray->Length();
    std::vector<double> ratioList;
    for (size_t i = 0; i < size; i++) {
        double ratio = 0.0;
        JSViewAbstract::ParseJsDouble(ratioArray->GetValueAt(i), ratio);
        if (LessOrEqual(ratio, VISIBLE_RATIO_MIN)) {
            ratio = VISIBLE_RATIO_MIN;
        }

        if (GreatOrEqual(ratio, VISIBLE_RATIO_MAX)) {
            ratio = VISIBLE_RATIO_MAX;
        }
        ratioList.push_back(ratio);
    }
    CHECK_NULL_RETURN(thirdArg->IsFunction(vm), panda::JSValueRef::Undefined(vm));
    auto event = thirdArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    panda::Local<panda::FunctionRef> func = event;
    auto flag = FrameNodeBridge::IsCustomFrameNode(frameNode);
    auto onVisibleAreaChange = [vm, func = JSFuncObjRef(panda::CopyableGlobal(vm, func), flag),
                                   node = AceType::WeakClaim(frameNode),
                                   containerId](bool isVisible, double visibleRatio) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        auto function = func.Lock();
        CHECK_EQUAL_VOID(function.IsEmpty(), true);
        CHECK_EQUAL_VOID(function->IsFunction(vm), false);
        PipelineContext::SetCallBackNode(node);
        auto isVisibles = panda::BooleanRef::New(vm, isVisible);
        auto visibleRatios = panda::NumberRef::New(vm, visibleRatio);
        panda::Local<panda::JSValueRef> params[NUM_2] = { isVisibles, visibleRatios };
        function->Call(vm, function.ToLocal(), params, NUM_2);
    };
    NG::ViewAbstract::SetOnVisibleChange(frameNode, std::move(onVisibleAreaChange), ratioList);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetOnVisibleAreaChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ViewAbstract::ResetVisibleChange(frameNode);
    return panda::JSValueRef::Undefined(vm);
}

panda::Local<panda::JSValueRef> ConvertHitTestMode(EcmaVM* vm, HitTestMode mode)
{
    switch (mode) {
        case HitTestMode::HTMDEFAULT:
            return panda::StringRef::NewFromUtf8(vm, "default");
        case HitTestMode::HTMBLOCK:
            return panda::StringRef::NewFromUtf8(vm, "block");
        case HitTestMode::HTMTRANSPARENT:
            return panda::StringRef::NewFromUtf8(vm, "transparent");
        case HitTestMode::HTMNONE:
            return panda::StringRef::NewFromUtf8(vm, "none");
        case HitTestMode::HTMTRANSPARENT_SELF:
            return panda::StringRef::NewFromUtf8(vm, "transparent_self");
        default:
            return panda::StringRef::NewFromUtf8(vm, "unknown");
    }
}

ArkUINativeModuleValue CommonBridge::SetOnTouchIntercept(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(secondeArg->IsFunction(vm), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    panda::Local<panda::FunctionRef> func = obj;
    auto flag = FrameNodeBridge::IsCustomFrameNode(frameNode);
    auto onTouchIntercept = [vm, func = JSFuncObjRef(panda::CopyableGlobal(vm, func), flag),
                                node = AceType::WeakClaim(frameNode),
                                containerId](TouchEventInfo& info) -> NG::HitTestMode {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        auto function = func.Lock();
        CHECK_EQUAL_RETURN(function.IsEmpty(), true, HitTestMode::HTMDEFAULT);
        CHECK_EQUAL_RETURN(function->IsFunction(vm), false, HitTestMode::HTMDEFAULT);
        PipelineContext::SetCallBackNode(node);
        auto touchEventObj = FrameNodeBridge::CreateTouchEventInfo(vm, info);
        HitTestMode hitTestMode = NG::HitTestMode::HTMDEFAULT;
        auto hitTestModeValue = ConvertHitTestMode(vm, hitTestMode);
        panda::Local<panda::JSValueRef> params[NUM_2] = { touchEventObj, hitTestModeValue };
        auto value = function->Call(vm, function.ToLocal(), params, NUM_2);
        if (value->IsNumber()) {
            return static_cast<NG::HitTestMode>(value->ToNumber(vm)->Value());
        }
        return hitTestMode;
    };
    NG::ViewAbstract::SetOnTouchIntercept(frameNode, std::move(onTouchIntercept));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetOnTouchIntercept(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ViewAbstract::SetOnTouchIntercept(frameNode, nullptr);
    return panda::JSValueRef::Undefined(vm);
}

Local<panda::ObjectRef> CommonBridge::CreateTouchTestInfo(EcmaVM *vm, const NG::TouchTestInfo &info)
{
    const char *keys[] = {"windowX", "windowY", "parentX", "parentY", "x", "y", "rect", "id"};
    Local<JSValueRef> values[] = {
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(info.windowPoint.GetX())),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(info.windowPoint.GetY())),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(info.currentCmpPoint.GetX())),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(info.currentCmpPoint.GetY())),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(info.subCmpPoint.GetX())),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(info.subCmpPoint.GetY())),
        CreateRectangle(vm, info.subRect),
        panda::StringRef::NewFromUtf8(vm, info.id.c_str())};
    auto obj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
    return obj;
}

Local<panda::ObjectRef> CommonBridge::CreateRectangle(EcmaVM *vm, const NG::RectF &rect)
{
    const char *rectKeys[] = {"x", "y", "width", "height"};
    Local<JSValueRef> rectValues[] = {panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(rect.GetX())),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(rect.GetY())),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(rect.Width())),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(rect.Height()))};

    return panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(rectKeys), rectKeys, rectValues);
}

ArkUINativeModuleValue CommonBridge::SetOnChildTouchTest(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(secondeArg->IsFunction(vm), panda::JSValueRef::Undefined(vm));
    auto containerId = Container::CurrentId();
    panda::Local<panda::FunctionRef> func = secondeArg->ToObject(vm);
    auto flag = FrameNodeBridge::IsCustomFrameNode(frameNode);
    auto onChildTouchTest = [vm, func = JSFuncObjRef(panda::CopyableGlobal(vm, func), flag),
                                node = AceType::WeakClaim(frameNode),
                                containerId](const std::vector<TouchTestInfo>& touchTestInfo) -> TouchResult {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        PipelineContext::SetCallBackNode(node);
        auto touchEventArr = panda::ArrayRef::New(vm);
        for (size_t i = 0; i < touchTestInfo.size(); i++) {
            auto touchEventObj = CreateTouchTestInfo(vm, touchTestInfo[i]);
            touchEventArr->SetValueAt(vm, touchEventArr, i, touchEventObj);
        }
        NG::TouchResult returnValue;
        returnValue.strategy = TouchTestStrategy::DEFAULT;
        returnValue.id = "";
        auto function = func.Lock();
        CHECK_EQUAL_RETURN(function.IsEmpty(), true, returnValue);
        CHECK_EQUAL_RETURN(function->IsFunction(vm), false, returnValue);
        panda::Local<panda::JSValueRef> params[] = { touchEventArr };
        auto value = function->Call(vm, function.ToLocal(), params, NUM_1);
        if (!value->IsObject(vm)) {
            return returnValue;
        }
        auto retObj = value->ToObject(vm);
        auto strategy = retObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "strategy"));
        if (!strategy->IsNumber()) {
            return returnValue;
        }
        auto id = retObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id"));
        if (!id->IsString(vm)) {
            return returnValue;
        }
        returnValue.strategy = static_cast<NG::TouchTestStrategy>(strategy->ToNumber(vm)->Value());
        returnValue.id = id->ToString(vm)->ToString(vm);
        return returnValue;
    };
    ViewAbstract::SetOnTouchTestFunc(frameNode, std::move(onChildTouchTest));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetOnChildTouchTest(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* frameNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ViewAbstract::SetOnTouchTestFunc(frameNode, nullptr);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
