/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_view_abstract.h"

#include <algorithm>
#include <cstdint>
#include <functional>
#include <memory>
#include <optional>
#include <regex>
#include <string>
#include <utility>
#include <vector>
#include <unordered_map>

#include "base/geometry/calc_dimension.h"
#include "base/geometry/dimension.h"
#include "base/geometry/matrix4.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/vector.h"
#include "base/geometry/shape.h"
#include "base/json/json_util.h"
#include "base/log/ace_scoring_log.h"
#include "base/log/log.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/utils.h"
#include "bridge/declarative_frontend/engine/functions/js_click_function.h"
#include "bridge/declarative_frontend/engine/functions/js_clipboard_function.h"
#include "bridge/declarative_frontend/engine/functions/js_drag_function.h"
#include "bridge/declarative_frontend/engine/functions/js_on_child_touch_test_function.h"
#include "bridge/declarative_frontend/engine/functions/js_focus_function.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/engine/functions/js_gesture_judge_function.h"
#include "bridge/declarative_frontend/engine/functions/js_hover_function.h"
#include "bridge/declarative_frontend/engine/functions/js_key_function.h"
#include "bridge/declarative_frontend/engine/functions/js_on_area_change_function.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "bridge/declarative_frontend/jsview/js_animatable_arithmetic.h"
#include "bridge/declarative_frontend/jsview/js_grid_container.h"
#include "bridge/declarative_frontend/jsview/js_shape_abstract.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/js_view_context.h"
#include "bridge/declarative_frontend/jsview/models/view_abstract_model_impl.h"
#include "core/common/resource/resource_manager.h"
#include "core/common/resource/resource_object.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/layout/screen_system_manager.h"
#include "core/components/common/properties/animation_option.h"
#include "core/components/common/properties/border_image.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/decoration.h"
#include "core/components/common/properties/invert.h"
#include "core/components/common/properties/shadow.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/components/theme/resource_adapter.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/gestures/base_gesture_event.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/overlay/modal_style.h"
#include "core/components_ng/property/safe_area_insets.h"
#include "core/gestures/gesture_info.h"
#include "core/image/image_source_info.h"
#ifdef PLUGIN_COMPONENT_SUPPORTED
#include "core/common/plugin_manager.h"
#endif
#include "core/common/card_scope.h"
#include "core/common/container.h"
#include "core/components/progress/progress_theme.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/property/progress_mask_property.h"

namespace OHOS::Ace {

std::unique_ptr<ViewAbstractModel> ViewAbstractModel::instance_ = nullptr;
std::mutex ViewAbstractModel::mutex_;
using DoubleBindCallback = std::function<void(const std::string&)>;

ViewAbstractModel* ViewAbstractModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::ViewAbstractModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::ViewAbstractModelNG());
            } else {
                instance_.reset(new Framework::ViewAbstractModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
namespace {

constexpr uint32_t DEFAULT_DURATION = 1000; // ms
constexpr int64_t MICROSEC_TO_MILLISEC = 1000;
constexpr uint32_t COLOR_ALPHA_OFFSET = 24;
constexpr uint32_t COLOR_ALPHA_VALUE = 0xFF000000;
constexpr uint32_t SAFE_AREA_TYPE_LIMIT = 3;
constexpr uint32_t SAFE_AREA_EDGE_LIMIT = 4;
constexpr int32_t MAX_ALIGN_VALUE = 8;
constexpr int32_t UNKNOWN_RESOURCE_ID = -1;
const std::regex RESOURCE_APP_STRING_PLACEHOLDER(R"(\%((\d+)(\$)){0,1}([dsf]))", std::regex::icase);
const std::regex FLOAT_PATTERN(R"(-?(0|[1-9]\d*)(\.\d+))", std::regex::icase);
constexpr double FULL_DIMENSION = 100.0;
constexpr double HALF_DIMENSION = 50.0;
constexpr double ROUND_UNIT = 360.0;
constexpr double VISIBLE_RATIO_MIN = 0.0;
constexpr double VISIBLE_RATIO_MAX = 1.0;
constexpr int32_t PARAMETER_LENGTH_FIRST = 1;
constexpr int32_t PARAMETER_LENGTH_SECOND = 2;
constexpr int32_t PARAMETER_LENGTH_THIRD = 3;
constexpr float DEFAULT_SCALE_LIGHT = 0.9f;
constexpr float DEFAULT_SCALE_MIDDLE_OR_HEAVY = 0.95f;
constexpr float MAX_ANGLE = 360.0f;
constexpr float DEFAULT_BIAS = 0.5f;
const std::vector<FontStyle> FONT_STYLES = { FontStyle::NORMAL, FontStyle::ITALIC };
const std::vector<std::string> TEXT_DETECT_TYPES = { "phoneNum", "url", "email", "location" };
const std::vector<std::string> RESOURCE_HEADS = { "app", "sys" };
const std::string SHEET_HEIGHT_MEDIUM = "medium";
const std::string SHEET_HEIGHT_LARGE = "large";
const std::string SHEET_HEIGHT_AUTO = "auto";
const std::string SHEET_HEIGHT_FITCONTENT = "fit_content";
const std::string BLOOM_RADIUS_SYS_RES_NAME = "sys.float.ohos_id_point_light_bloom_radius";
const std::string BLOOM_COLOR_SYS_RES_NAME = "sys.color.ohos_id_point_light_bloom_color";
const std::string ILLUMINATED_BORDER_WIDTH_SYS_RES_NAME = "sys.float.ohos_id_point_light_illuminated_border_width";

constexpr Dimension ARROW_ZERO_PERCENT_VALUE = 0.0_pct;
constexpr Dimension ARROW_HALF_PERCENT_VALUE = 0.5_pct;
constexpr Dimension ARROW_ONE_HUNDRED_PERCENT_VALUE = 1.0_pct;

bool CheckJSCallbackInfo(
    const std::string& callerName, const JSCallbackInfo& info, std::vector<JSCallbackInfoType>& infoTypes)
{
    bool typeVerified = false;
    std::string unrecognizedType;
    auto tmpInfo = info[0];
    for (const auto& infoType : infoTypes) {
        switch (infoType) {
            case JSCallbackInfoType::STRING:
                if (tmpInfo->IsString()) {
                    typeVerified = true;
                } else {
                    unrecognizedType += "string|";
                }
                break;
            case JSCallbackInfoType::NUMBER:
                if (tmpInfo->IsNumber()) {
                    typeVerified = true;
                } else {
                    unrecognizedType += "number|";
                }
                break;
            case JSCallbackInfoType::OBJECT:
                if (tmpInfo->IsObject()) {
                    typeVerified = true;
                } else {
                    unrecognizedType += "object|";
                }
                break;
            case JSCallbackInfoType::FUNCTION:
                if (tmpInfo->IsFunction()) {
                    typeVerified = true;
                } else {
                    unrecognizedType += "Function|";
                }
                break;
            default:
                break;
        }
    }
    if (!typeVerified) {
        LOGD("%{public}s: info[0] is not a [%{public}s]", callerName.c_str(),
            unrecognizedType.substr(0, unrecognizedType.size() - 1).c_str());
    }
    return typeVerified || infoTypes.size() == 0;
}

void ParseJsonScale(std::unique_ptr<JsonValue>& argsPtrItem, float& scaleX, float& scaleY, float& scaleZ,
    CalcDimension& centerX, CalcDimension& centerY)
{
    double xVal = 1.0;
    double yVal = 1.0;
    double zVal = 1.0;
    if (!argsPtrItem->IsObject() && !argsPtrItem->IsNumber() && !argsPtrItem->IsString()) {
        scaleX = static_cast<float>(xVal);
        scaleY = static_cast<float>(yVal);
        scaleZ = static_cast<float>(zVal);
        CalcDimension length;
        centerX = length;
        centerY = length;
        return;
    }
    JSViewAbstract::ParseJsonDouble(argsPtrItem->GetValue("x"), xVal);
    JSViewAbstract::ParseJsonDouble(argsPtrItem->GetValue("y"), yVal);
    JSViewAbstract::ParseJsonDouble(argsPtrItem->GetValue("z"), zVal);
    scaleX = static_cast<float>(xVal);
    scaleY = static_cast<float>(yVal);
    scaleZ = static_cast<float>(zVal);
    // if specify centerX
    CalcDimension length;
    if (JSViewAbstract::ParseJsonDimensionVp(argsPtrItem->GetValue("centerX"), length)) {
        centerX = length;
    }
    // if specify centerY
    if (JSViewAbstract::ParseJsonDimensionVp(argsPtrItem->GetValue("centerY"), length)) {
        centerY = length;
    }
}

void ParseJsScale(const JSRef<JSVal>& jsValue, float& scaleX, float& scaleY, float& scaleZ,
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
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    JSViewAbstract::ParseJsDouble(jsObj->GetProperty("x"), xVal);
    JSViewAbstract::ParseJsDouble(jsObj->GetProperty("y"), yVal);
    JSViewAbstract::ParseJsDouble(jsObj->GetProperty("z"), zVal);
    scaleX = static_cast<float>(xVal);
    scaleY = static_cast<float>(yVal);
    scaleZ = static_cast<float>(zVal);
    // if specify centerX
    JSViewAbstract::ParseJsDimensionVp(jsObj->GetProperty("centerX"), centerX);
    // if specify centerY
    JSViewAbstract::ParseJsDimensionVp(jsObj->GetProperty("centerY"), centerY);
}

void ParseJsonTranslate(std::unique_ptr<JsonValue>& argsPtrItem, CalcDimension& translateX, CalcDimension& translateY,
    CalcDimension& translateZ)
{
    CalcDimension length;
    if (JSViewAbstract::ParseJsonDimensionVp(argsPtrItem->GetValue("x"), length)) {
        translateX = length;
    }
    if (JSViewAbstract::ParseJsonDimensionVp(argsPtrItem->GetValue("y"), length)) {
        translateY = length;
    }
    if (JSViewAbstract::ParseJsonDimensionVp(argsPtrItem->GetValue("z"), length)) {
        translateZ = length;
    }
}

void ParseJsTranslate(const JSRef<JSVal>& jsValue, CalcDimension& translateX, CalcDimension& translateY,
    CalcDimension& translateZ)
{
    if (!jsValue->IsObject()) {
        return;
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    JSViewAbstract::ParseJsDimensionVp(jsObj->GetProperty("x"), translateX);
    JSViewAbstract::ParseJsDimensionVp(jsObj->GetProperty("y"), translateY);
    JSViewAbstract::ParseJsDimensionVp(jsObj->GetProperty("z"), translateZ);
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

void ParseJsonRotate(std::unique_ptr<JsonValue>& argsPtrItem, NG::RotateOptions& rotate, std::optional<float>& angle)
{
    // default: dx, dy, dz (0.0, 0.0, 0.0)
    double dxVal = 0.0;
    double dyVal = 0.0;
    double dzVal = 0.0;
    if (!argsPtrItem->Contains("x") && !argsPtrItem->Contains("y") && !argsPtrItem->Contains("z")) {
        GetDefaultRotateVector(dxVal, dyVal, dzVal);
    }
    JSViewAbstract::ParseJsonDouble(argsPtrItem->GetValue("x"), dxVal);
    JSViewAbstract::ParseJsonDouble(argsPtrItem->GetValue("y"), dyVal);
    JSViewAbstract::ParseJsonDouble(argsPtrItem->GetValue("z"), dzVal);
    rotate.xDirection = static_cast<float>(dxVal);
    rotate.yDirection = static_cast<float>(dyVal);
    rotate.zDirection = static_cast<float>(dzVal);
    // if specify centerX
    CalcDimension length;
    if (!JSViewAbstract::ParseJsonDimensionVp(argsPtrItem->GetValue("centerX"), length, true)) {
        length = Dimension(0.5f, DimensionUnit::PERCENT);
    }
    rotate.centerX = length;
    // if specify centerY

    if (!JSViewAbstract::ParseJsonDimensionVp(argsPtrItem->GetValue("centerY"), length, true)) {
        length = Dimension(0.5f, DimensionUnit::PERCENT);
    }
    rotate.centerY = length;

    // if specify centerZ
    if (!JSViewAbstract::ParseJsonDimensionVp(argsPtrItem->GetValue("centerZ"), length, true)) {
        length = Dimension(0.5f, DimensionUnit::PERCENT);
    }
    rotate.centerZ = length;
    // if specify angle
    JSViewAbstract::GetAngle("angle", argsPtrItem, angle);
    float perspective = 0.0f;
    JSViewAbstract::GetPerspective("perspective", argsPtrItem, perspective);
    rotate.perspective = perspective;
}

void ParseJsRotate(const JSRef<JSVal>& jsValue, NG::RotateOptions& rotate, std::optional<float>& angle)
{
    if (!jsValue->IsObject()) {
        return;
    }
    // default: dx, dy, dz (0.0, 0.0, 0.0)
    double dxVal = 0.0;
    double dyVal = 0.0;
    double dzVal = 0.0;
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    if (!jsObj->HasProperty("x") && !jsObj->HasProperty("y") && !jsObj->HasProperty("z")) {
        GetDefaultRotateVector(dxVal, dyVal, dzVal);
    } else {
        JSViewAbstract::ParseJsDouble(jsObj->GetProperty("x"), dxVal);
        JSViewAbstract::ParseJsDouble(jsObj->GetProperty("y"), dyVal);
        JSViewAbstract::ParseJsDouble(jsObj->GetProperty("z"), dzVal);
    }
    rotate.xDirection = static_cast<float>(dxVal);
    rotate.yDirection = static_cast<float>(dyVal);
    rotate.zDirection = static_cast<float>(dzVal);
    // if specify centerX
    if (!JSViewAbstract::ParseJsDimensionVp(jsObj->GetProperty("centerX"), rotate.centerX)) {
        rotate.centerX = Dimension(0.5f, DimensionUnit::PERCENT);
    }
    // if specify centerY
    if (!JSViewAbstract::ParseJsDimensionVp(jsObj->GetProperty("centerY"), rotate.centerY)) {
        rotate.centerY = Dimension(0.5f, DimensionUnit::PERCENT);
    }
    // if specify centerZ
    if (!JSViewAbstract::ParseJsDimensionVp(jsObj->GetProperty("centerZ"), rotate.centerZ)) {
        rotate.centerZ = Dimension(0.5f, DimensionUnit::PERCENT);
    }
    // if specify angle
    JSViewAbstract::GetJsAngle("angle", jsObj, angle);
    rotate.perspective = 0.0f;
    JSViewAbstract::GetJsPerspective("perspective", jsObj, rotate.perspective);
}

bool ParseMotionPath(const JSRef<JSVal>& jsValue, MotionPathOption& option)
{
    if (!jsValue->IsObject()) {
        return false;
    }

    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    auto path = jsObj->GetPropertyValue<std::string>("path", "");
    if (path.empty()) {
        return false;
    }
    option.SetPath(path);
    double from = 0.0;
    double to = 1.0;
    JSViewAbstract::ParseJsDouble(jsObj->GetProperty("from"), from);
    JSViewAbstract::ParseJsDouble(jsObj->GetProperty("to"), to);
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

void SetBgImgPosition(const DimensionUnit& typeX, const DimensionUnit& typeY, const double valueX, const double valueY,
    BackgroundImagePosition& bgImgPosition)
{
    AnimationOption option = ViewStackModel::GetInstance()->GetImplicitAnimationOption();
    bgImgPosition.SetSizeX(AnimatableDimension(valueX, typeX, option));
    bgImgPosition.SetSizeY(AnimatableDimension(valueY, typeY, option));
}

std::string GetReplaceContentStr(int pos, const std::string& type, JSRef<JSArray> params, int32_t containCount)
{
    JSRef<JSVal> item = params->GetValueAt(pos + containCount);
    if (type == "d") {
        if (item->IsNumber()) {
            return std::to_string(item->ToNumber<uint32_t>());
        }
    } else if (type == "s") {
        if (item->IsString()) {
            return item->ToString();
        }
    } else if (type == "f") {
        if (item->IsNumber()) {
            return std::to_string(item->ToNumber<float>());
        }
    }
    return std::string();
}

void ReplaceHolder(std::string& originStr, JSRef<JSArray> params, int32_t containCount)
{
    auto size = static_cast<int32_t>(params->Length());
    if (containCount == size) {
        return;
    }
    std::string::const_iterator start = originStr.begin();
    std::string::const_iterator end = originStr.end();
    std::smatch matches;
    bool shortHolderType = false;
    bool firstMatch = true;
    int searchTime = 0;
    while (std::regex_search(start, end, matches, RESOURCE_APP_STRING_PLACEHOLDER)) {
        std::string pos = matches[2];
        std::string type = matches[4];
        if (firstMatch) {
            firstMatch = false;
            shortHolderType = pos.length() == 0;
        } else {
            if (shortHolderType ^ (pos.length() == 0)) {
                return;
            }
        }

        std::string replaceContentStr;
        if (shortHolderType) {
            replaceContentStr = GetReplaceContentStr(searchTime, type, params, containCount);
        } else {
            replaceContentStr = GetReplaceContentStr(StringToInt(pos) - 1, type, params, containCount);
        }

        originStr.replace(matches[0].first - originStr.begin(), matches[0].length(), replaceContentStr);
        start = originStr.begin() + matches.prefix().length() + replaceContentStr.length();
        end = originStr.end();
        searchTime++;
    }
}

bool ParseLocationProps(const JSCallbackInfo& info, CalcDimension& x, CalcDimension& y)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::OBJECT };
    if (!CheckJSCallbackInfo("ParseLocationProps", info, checkList)) {
        return false;
    }
    JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSVal> xVal = sizeObj->GetProperty("x");
    JSRef<JSVal> yVal = sizeObj->GetProperty("y");
    bool hasX = JSViewAbstract::ParseJsDimensionVp(xVal, x);
    bool hasY = JSViewAbstract::ParseJsDimensionVp(yVal, y);
    return hasX || hasY;
}

RefPtr<JsFunction> ParseDragStartBuilderFunc(const JSRef<JSVal>& info)
{
    JSRef<JSVal> builder;
    if (info->IsObject()) {
        auto builderObj = JSRef<JSObject>::Cast(info);
        builder = builderObj->GetProperty("builder");
    } else if (info->IsFunction()) {
        builder = info;
    } else {
        return nullptr;
    }

    if (!builder->IsFunction()) {
        return nullptr;
    }

    return AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(builder));
}

RefPtr<NG::ChainedTransitionEffect> ParseChainedTransition(
    const JSRef<JSObject>& object, const JSExecutionContext& context);

RefPtr<NG::ChainedTransitionEffect> ParseChainedRotateTransition(
    const JSRef<JSVal>& effectOption, const JSExecutionContext& context)
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

RefPtr<NG::ChainedTransitionEffect> ParseChainedOpacityTransition(
    const JSRef<JSVal>& effectOption, const JSExecutionContext& context)
{
    double opacity = 1.0;
    if (JSViewAbstract::ParseJsDouble(effectOption, opacity)) {
        if ((LessNotEqual(opacity, 0.0)) || opacity > 1.0) {
            opacity = 1.0;
        }
        return AceType::MakeRefPtr<NG::ChainedOpacityEffect>(opacity);
    }
    return nullptr;
}

RefPtr<NG::ChainedTransitionEffect> ParseChainedTranslateTransition(
    const JSRef<JSVal>& effectOption, const JSExecutionContext& context)
{
    if (effectOption->IsObject()) {
        // default: x, y, z (0.0, 0.0, 0.0)
        NG::TranslateOptions translate;
        ParseJsTranslate(effectOption, translate.x, translate.y, translate.z);
        return AceType::MakeRefPtr<NG::ChainedTranslateEffect>(translate);
    }
    return nullptr;
}

RefPtr<NG::ChainedTransitionEffect> ParseChainedScaleTransition(
    const JSRef<JSVal>& effectOption, const JSExecutionContext& context)
{
    if (effectOption->IsObject()) {
        // default: x, y, z (1.0, 1.0, 1.0), centerX, centerY 50% 50%;
        NG::ScaleOptions scale(1.0f, 1.0f, 1.0f, 0.5_pct, 0.5_pct);
        ParseJsScale(effectOption, scale.xScale, scale.yScale, scale.zScale, scale.centerX, scale.centerY);
        return AceType::MakeRefPtr<NG::ChainedScaleEffect>(scale);
    }
    return nullptr;
}

RefPtr<NG::ChainedTransitionEffect> ParseChainedMoveTransition(
    const JSRef<JSVal>& effectOption, const JSExecutionContext& context)
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

RefPtr<NG::ChainedTransitionEffect> ParseChainedAsymmetricTransition(
    const JSRef<JSVal>& effectOption, const JSExecutionContext& context)
{
    if (effectOption->IsObject()) {
        auto effectObj = JSRef<JSObject>::Cast(effectOption);
        auto appearJsVal = effectObj->GetProperty("appear");
        auto disappearJsVal = effectObj->GetProperty("disappear");
        RefPtr<NG::ChainedTransitionEffect> appearEffect;
        RefPtr<NG::ChainedTransitionEffect> disappearEffect;
        if (appearJsVal->IsObject()) {
            auto appearObj = JSRef<JSObject>::Cast(appearJsVal);
            appearEffect = ParseChainedTransition(appearObj, context);
        }
        if (disappearJsVal->IsObject()) {
            auto disappearObj = JSRef<JSObject>::Cast(disappearJsVal);
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
    const JSRef<JSVal>&, const JSExecutionContext&);

RefPtr<NG::ChainedTransitionEffect> ParseChainedTransition(
    const JSRef<JSObject>& object, const JSExecutionContext& context)
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
            [](const JSRef<JSVal>& effectOption, const JSExecutionContext& context)
                -> RefPtr<NG::ChainedTransitionEffect> { return AceType::MakeRefPtr<NG::ChainedIdentityEffect>(); } },
        { "move", ParseChainedMoveTransition },
        { "opacity", ParseChainedOpacityTransition },
        { "rotate", ParseChainedRotateTransition },
        { "scale", ParseChainedScaleTransition },
        { "slideSwitch",
            [](const JSRef<JSVal>& effectOption,
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
            JSViewContext::CreateAnimation(propAnimationOption, pipelineContext->IsFormRender()));
        // The maximum of the form-animation-playback duration value is 1000 ms.
        if (pipelineContext->IsFormRender() && pipelineContext->IsFormAnimation()) {
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
        auto animationOptionObj = JSRef<JSObject>::Cast(propAnimationOption);
        JSRef<JSVal> onFinish = animationOptionObj->GetProperty("onFinish");
        WeakPtr<NG::FrameNode> targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
        if (onFinish->IsFunction()) {
            RefPtr<JsFunction> jsFunc =
                AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onFinish));
            std::function<void()> onFinishEvent = [execCtx = context, func = std::move(jsFunc),
                                                      id = Container::CurrentId(), node = targetNode]() {
                ContainerScope scope(id);
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                PipelineContext::SetCallBackNode(node);
                func->Execute();
            };
            animationOptionResult->SetOnFinishEvent(onFinishEvent);
        }
        result->SetAnimationOption(animationOptionResult);
    }
    if (propSuccessor->IsObject()) {
        result->SetNext(ParseChainedTransition(JSRef<JSObject>::Cast(propSuccessor), context));
    }
    return result;
}

#ifndef WEARABLE_PRODUCT
const std::vector<Placement> PLACEMENT = { Placement::LEFT, Placement::RIGHT, Placement::TOP, Placement::BOTTOM,
    Placement::TOP_LEFT, Placement::TOP_RIGHT, Placement::BOTTOM_LEFT, Placement::BOTTOM_RIGHT, Placement::LEFT_TOP,
    Placement::LEFT_BOTTOM, Placement::RIGHT_TOP, Placement::RIGHT_BOTTOM };

DoubleBindCallback ParseDoubleBindCallback(const JSCallbackInfo& info, const JSRef<JSObject>& callbackObj)
{
    JSRef<JSVal> changeEvent = callbackObj->GetProperty("changeEvent");
    if (!changeEvent->IsFunction()) {
        return {};
    }
    RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(changeEvent));
    WeakPtr<NG::FrameNode> targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto callback = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                        const std::string& param) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        if (param != "true" && param != "false") {
            return;
        }
        PipelineContext::SetCallBackNode(node);
        bool newValue = StringToBool(param);
        JSRef<JSVal> newJSVal = JSRef<JSVal>::Make(ToJSValue(newValue));
        func->ExecuteJS(1, &newJSVal);
    };
    return callback;
}

void SetPopupMessageOptions(const JSRef<JSObject> messageOptionsObj, const RefPtr<PopupParam>& popupParam)
{
    auto colorValue = messageOptionsObj->GetProperty("textColor");
    Color textColor;
    if (JSViewAbstract::ParseJsColor(colorValue, textColor)) {
        if (popupParam) {
            popupParam->SetTextColor(textColor);
        }
    }

    auto font = messageOptionsObj->GetProperty("font");
    if (!font->IsNull() && font->IsObject()) {
        JSRef<JSObject> fontObj = JSRef<JSObject>::Cast(font);
        auto fontSizeValue = fontObj->GetProperty("size");
        CalcDimension fontSize;
        if (JSViewAbstract::ParseJsDimensionFp(fontSizeValue, fontSize)) {
            if (popupParam) {
                popupParam->SetFontSize(fontSize);
            }
        }
        auto fontWeightValue = fontObj->GetProperty("weight");
        if (fontWeightValue->IsString()) {
            if (popupParam) {
                popupParam->SetFontWeight(ConvertStrToFontWeight(fontWeightValue->ToString()));
            }
        }
        auto fontStyleValue = fontObj->GetProperty("style");
        if (fontStyleValue->IsNumber()) {
            int32_t value = fontStyleValue->ToNumber<int32_t>();
            if (value < 0 || value >= static_cast<int32_t>(FONT_STYLES.size())) {
                return;
            }
            if (popupParam) {
                popupParam->SetFontStyle(FONT_STYLES[value]);
            }
        }
    }
}

void SetPlacementOnTopVal(const JSRef<JSObject>& popupObj, const RefPtr<PopupParam>& popupParam)
{
    JSRef<JSVal> placementOnTopVal = popupObj->GetProperty("placementOnTop");
    if (placementOnTopVal->IsBoolean() && popupParam) {
        popupParam->SetPlacement(placementOnTopVal->ToBoolean() ? Placement::TOP : Placement::BOTTOM);
    }
}

void ParsePopupCommonParam(
    const JSCallbackInfo& info, const JSRef<JSObject>& popupObj, const RefPtr<PopupParam>& popupParam)
{
    auto arrowOffset = popupObj->GetProperty("arrowOffset");
    CalcDimension offset;
    if (JSViewAbstract::ParseJsDimensionVp(arrowOffset, offset)) {
        if (popupParam) {
            popupParam->SetArrowOffset(offset);
        }
    }

    auto arrowPointPosition = popupObj->GetProperty("arrowPointPosition");
    if (arrowPointPosition->IsString()) {
        char* pEnd = nullptr;
        std::strtod(arrowPointPosition->ToString().c_str(), &pEnd);
        if (pEnd != nullptr) {
            if (std::strcmp(pEnd, "Start") == 0) {
                offset = ARROW_ZERO_PERCENT_VALUE;
            }
            if (std::strcmp(pEnd, "Center") == 0) {
                offset = ARROW_HALF_PERCENT_VALUE;
            }
            if (std::strcmp(pEnd, "End") == 0) {
                offset = ARROW_ONE_HUNDRED_PERCENT_VALUE;
            }
            if (popupParam) {
                popupParam->SetArrowOffset(offset);
            }
        }
    }

    auto targetSpace = popupObj->GetProperty("targetSpace");
    if (!targetSpace->IsNull()) {
        CalcDimension space;
        if (JSViewAbstract::ParseJsDimensionVp(targetSpace, space)) {
            if (popupParam) {
                popupParam->SetTargetSpace(space);
            }
        }
    }

    JSRef<JSVal> showInSubWindowValue = popupObj->GetProperty("showInSubWindow");
    if (showInSubWindowValue->IsBoolean()) {
        bool showInSubBoolean = showInSubWindowValue->ToBoolean();
#if defined(PREVIEW)
        if (showInSubBoolean) {
            LOGI("[Engine Log] Unable to use the SubWindow in the Previewer. Use normal type instead.");
            showInSubBoolean = false;
        }
#endif
        if (popupParam) {
            popupParam->SetShowInSubWindow(showInSubBoolean);
        }
    }

    auto placementValue = popupObj->GetProperty("placement");
    if (placementValue->IsNumber()) {
        auto placement = placementValue->ToNumber<int32_t>();
        if (placement >= 0 && placement <= static_cast<int32_t>(PLACEMENT.size())) {
            popupParam->SetPlacement(PLACEMENT[placement]);
        }
    } else {
        SetPlacementOnTopVal(popupObj, popupParam);
    }

    auto enableArrowValue = popupObj->GetProperty("enableArrow");
    if (enableArrowValue->IsBoolean()) {
        popupParam->SetEnableArrow(enableArrowValue->ToBoolean());
    }

    JSRef<JSVal> maskValue = popupObj->GetProperty("mask");
    if (maskValue->IsBoolean()) {
        if (popupParam) {
            popupParam->SetBlockEvent(maskValue->ToBoolean());
        }
    }
    if (maskValue->IsObject()) {
        auto maskObj = JSRef<JSObject>::Cast(maskValue);
        auto colorValue = maskObj->GetProperty("color");
        Color maskColor;
        if (JSViewAbstract::ParseJsColor(colorValue, maskColor)) {
            popupParam->SetMaskColor(maskColor);
        }
    }

    JSRef<JSVal> onStateChangeVal = popupObj->GetProperty("onStateChange");
    if (onStateChangeVal->IsFunction()) {
        std::vector<std::string> keys = { "isVisible" };
        RefPtr<JsFunction> jsFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onStateChangeVal));
        WeakPtr<NG::FrameNode> targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
        if (popupParam) {
            auto onStateChangeCallback = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), keys,
                                             node = targetNode](const std::string& param) {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                ACE_SCORING_EVENT("Popup.onStateChange");
                PipelineContext::SetCallBackNode(node);
                func->Execute(keys, param);
            };
            popupParam->SetOnStateChange(onStateChangeCallback);
        }
    }

    auto offsetVal = popupObj->GetProperty("offset");
    if (offsetVal->IsObject()) {
        auto offsetObj = JSRef<JSObject>::Cast(offsetVal);
        auto xVal = offsetObj->GetProperty("x");
        auto yVal = offsetObj->GetProperty("y");
        Offset popupOffset;
        CalcDimension dx;
        CalcDimension dy;
        if (JSViewAbstract::ParseJsDimensionVp(xVal, dx)) {
            popupOffset.SetX(dx.ConvertToPx());
        }
        if (JSViewAbstract::ParseJsDimensionVp(yVal, dy)) {
            popupOffset.SetY(dy.ConvertToPx());
        }
        if (popupParam) {
            popupParam->SetTargetOffset(popupOffset);
        }
    }

    Color backgroundColor;
    auto popupColorVal = popupObj->GetProperty("popupColor");
    if (JSViewAbstract::ParseJsColor(popupColorVal, backgroundColor)) {
        popupParam->SetBackgroundColor(backgroundColor);
    }

    auto autoCancelVal = popupObj->GetProperty("autoCancel");
    if (autoCancelVal->IsBoolean()) {
        popupParam->SetHasAction(!autoCancelVal->ToBoolean());
    }

    auto childWidthVal = popupObj->GetProperty("width");
    if (!childWidthVal->IsNull()) {
        CalcDimension width;
        if (JSViewAbstract::ParseJsDimensionVp(childWidthVal, width)) {
            if (width.Value() > 0) {
                popupParam->SetChildWidth(width);
            }
        }
    }

    auto arrowWidthVal = popupObj->GetProperty("arrowWidth");
    if (!arrowWidthVal->IsNull()) {
        bool setError = true;
        CalcDimension arrowWidth;
        if (JSViewAbstract::ParseJsDimensionVp(arrowWidthVal, arrowWidth)) {
            if (arrowWidth.Value() > 0 && arrowWidth.Unit() != DimensionUnit::PERCENT) {
                popupParam->SetArrowWidth(arrowWidth);
                setError = false;
            }
        }
        popupParam->SetErrorArrowWidth(setError);
    }

    auto arrowHeightVal = popupObj->GetProperty("arrowHeight");
    if (!arrowHeightVal->IsNull()) {
        bool setError = true;
        CalcDimension arrowHeight;
        if (JSViewAbstract::ParseJsDimensionVp(arrowHeightVal, arrowHeight)) {
            if (arrowHeight.Value() > 0 && arrowHeight.Unit() != DimensionUnit::PERCENT) {
                popupParam->SetArrowHeight(arrowHeight);
                setError = false;
            }
        }
        popupParam->SetErrorArrowHeight(setError);
    }

    auto radiusVal = popupObj->GetProperty("radius");
    if (!radiusVal->IsNull()) {
        bool setError = true;
        CalcDimension radius;
        if (JSViewAbstract::ParseJsDimensionVp(radiusVal, radius)) {
            if (radius.Value() >= 0) {
                popupParam->SetRadius(radius);
                setError = false;
            }
        }
        popupParam->SetErrorRadius(setError);
    }

    Shadow shadow;
    auto shadowVal = popupObj->GetProperty("shadow");
    if (shadowVal->IsObject() || shadowVal->IsNumber()) {
        auto ret = JSViewAbstract::ParseShadowProps(shadowVal, shadow);
        if (!ret) {
            JSViewAbstract::GetShadowFromTheme(ShadowStyle::OuterDefaultMD, shadow);
        }
    } else {
        JSViewAbstract::GetShadowFromTheme(ShadowStyle::OuterDefaultMD, shadow);
    }
    popupParam->SetShadow(shadow);

    auto blurStyleValue = popupObj->GetProperty("backgroundBlurStyle");
    if (blurStyleValue->IsNumber()) {
        auto blurStyle = blurStyleValue->ToNumber<int32_t>();
        if (blurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
            blurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
            popupParam->SetBlurStyle(static_cast<BlurStyle>(blurStyle));
        }
    }
}

void ParsePopupParam(const JSCallbackInfo& info, const JSRef<JSObject>& popupObj, const RefPtr<PopupParam>& popupParam)
{
    ParsePopupCommonParam(info, popupObj, popupParam);
    JSRef<JSVal> messageVal = popupObj->GetProperty("message");
    if (popupParam) {
        popupParam->SetMessage(messageVal->ToString());
    }

    auto messageOptions = popupObj->GetProperty("messageOptions");
    JSRef<JSObject> messageOptionsObj;
    if (!messageOptions->IsNull() && messageOptions->IsObject()) {
        messageOptionsObj = JSRef<JSObject>::Cast(messageOptions);
        SetPopupMessageOptions(messageOptionsObj, popupParam);
    }

    JSRef<JSVal> primaryButtonVal = popupObj->GetProperty("primaryButton");
    if (primaryButtonVal->IsObject()) {
        ButtonProperties properties;
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(primaryButtonVal);
        JSRef<JSVal> value = obj->GetProperty("value");
        if (value->IsString()) {
            properties.value = value->ToString();
        }

        JSRef<JSVal> actionValue = obj->GetProperty("action");
        if (actionValue->IsFunction()) {
            auto jsOnClickFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(actionValue));
            WeakPtr<NG::FrameNode> targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
            if (popupParam) {
                auto clickCallback = [execCtx = info.GetExecutionContext(), func = std::move(jsOnClickFunc),
                                         node = targetNode](GestureEvent& info) {
                    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                    ACE_SCORING_EVENT("primaryButton.action");
                    PipelineContext::SetCallBackNode(node);
                    func->Execute(info);
                };
                properties.action = AceType::MakeRefPtr<NG::ClickEvent>(clickCallback);
            }
        }
        properties.showButton = true;
        if (popupParam) {
            popupParam->SetPrimaryButtonProperties(properties);
        }
    }

    JSRef<JSVal> secondaryButtonVal = popupObj->GetProperty("secondaryButton");
    if (secondaryButtonVal->IsObject()) {
        ButtonProperties properties;
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(secondaryButtonVal);
        JSRef<JSVal> value = obj->GetProperty("value");
        if (value->IsString()) {
            properties.value = value->ToString();
        }

        JSRef<JSVal> actionValue = obj->GetProperty("action");
        if (actionValue->IsFunction()) {
            auto jsOnClickFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(actionValue));
            WeakPtr<NG::FrameNode> targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
            if (popupParam) {
                auto clickCallback = [execCtx = info.GetExecutionContext(), func = std::move(jsOnClickFunc),
                                         node = targetNode](GestureEvent& info) {
                    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                    ACE_SCORING_EVENT("secondaryButton.action");
                    PipelineContext::SetCallBackNode(node);
                    func->Execute(info);
                };
                properties.action = AceType::MakeRefPtr<NG::ClickEvent>(clickCallback);
            }
        }
        properties.showButton = true;
        if (popupParam) {
            popupParam->SetSecondaryButtonProperties(properties);
        }
    }
}

void ParseCustomPopupParam(
    const JSCallbackInfo& info, const JSRef<JSObject>& popupObj, const RefPtr<PopupParam>& popupParam)
{
    auto builderValue = popupObj->GetProperty("builder");
    if (!builderValue->IsObject()) {
        return;
    }

    JSRef<JSObject> builderObj;
    builderObj = JSRef<JSObject>::Cast(builderValue);
    auto builder = builderObj->GetProperty("builder");
    if (!builder->IsFunction()) {
        return;
    }
    auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(builder));
    if (!builderFunc) {
        return;
    }

    if (popupParam) {
        popupParam->SetUseCustomComponent(true);
    }

    auto focusableValue = popupObj->GetProperty("focusable");
    if (focusableValue->IsBoolean()) {
        popupParam->SetFocusable(focusableValue->ToBoolean());
    }

    ParsePopupCommonParam(info, popupObj, popupParam);
}
#endif

} // namespace

RefPtr<ResourceObject> GetResourceObject(const JSRef<JSObject>& jsObj)
{
    auto id = jsObj->GetProperty("id")->ToNumber<uint32_t>();
    auto type = jsObj->GetProperty("type")->ToNumber<uint32_t>();
    auto args = jsObj->GetProperty("params");

    std::string bundleName;
    std::string moduleName;
    auto bundle = jsObj->GetProperty("bundleName");
    auto module = jsObj->GetProperty("moduleName");
    if (bundle->IsString() && module->IsString()) {
        bundleName = bundle->ToString();
        moduleName = module->ToString();
    }

    JSRef<JSArray> params = JSRef<JSArray>::Cast(args);
    std::vector<ResourceObjectParams> resObjParamsList;
    auto size = static_cast<int32_t>(params->Length());
    for (int32_t i = 0; i < size; i++) {
        auto item = params->GetValueAt(i);
        ResourceObjectParams resObjParams { .value = item->ToString().c_str() };
        if (item->IsString()) {
            resObjParams.type = ResourceObjectParamType::STRING;
        } else if (item->IsNumber()) {
            if (std::regex_match(item->ToString(), FLOAT_PATTERN)) {
                resObjParams.type = ResourceObjectParamType::FLOAT;
            } else {
                resObjParams.type = ResourceObjectParamType::INT;
            }
        }
        resObjParamsList.push_back(resObjParams);
    }
    auto resourceObject = AceType::MakeRefPtr<ResourceObject>(id, type, resObjParamsList, bundleName, moduleName);
    return resourceObject;
}

RefPtr<ResourceWrapper> CreateResourceWrapper(const JSRef<JSObject>& jsObj, RefPtr<ResourceObject>& resourceObject)
{
    RefPtr<ResourceAdapter> resourceAdapter = nullptr;
    RefPtr<ThemeConstants> themeConstants = nullptr;
    if (SystemProperties::GetResourceDecoupling()) {
        resourceAdapter = ResourceManager::GetInstance().GetOrCreateResourceAdapter(resourceObject);
        if (!resourceAdapter) {
            return nullptr;
        }
    } else {
        themeConstants = JSViewAbstract::GetThemeConstants(jsObj);
        if (!themeConstants) {
            return nullptr;
        }
    }
    auto resourceWrapper = AceType::MakeRefPtr<ResourceWrapper>(themeConstants, resourceAdapter);
    return resourceWrapper;
}

RefPtr<ResourceWrapper> CreateResourceWrapper()
{
    RefPtr<ResourceAdapter> resourceAdapter = nullptr;
    RefPtr<ThemeConstants> themeConstants = nullptr;
    if (SystemProperties::GetResourceDecoupling()) {
        resourceAdapter = ResourceManager::GetInstance().GetResourceAdapter();
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

uint32_t ColorAlphaAdapt(uint32_t origin)
{
    uint32_t result = origin;
    if (origin >> COLOR_ALPHA_OFFSET == 0) {
        result = origin | COLOR_ALPHA_VALUE;
    }
    return result;
}

void JSViewAbstract::JsScale(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::NUMBER, JSCallbackInfoType::OBJECT };
    if (!CheckJSCallbackInfo("JsScale", info, checkList)) {
        SetDefaultScale();
        return;
    }

    if (info[0]->IsObject()) {
        JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);
        if (jsObj->HasProperty("x") || jsObj->HasProperty("y") || jsObj->HasProperty("z")) {
            // default: x, y, z (1.0, 1.0, 1.0)
            auto scaleX = 1.0f;
            auto scaleY = 1.0f;
            auto scaleZ = 1.0f;
            // default centerX, centerY 50% 50%;
            CalcDimension centerX = 0.5_pct;
            CalcDimension centerY = 0.5_pct;
            ParseJsScale(info[0], scaleX, scaleY, scaleZ, centerX, centerY);
            ViewAbstractModel::GetInstance()->SetScale(scaleX, scaleY, scaleZ);
            ViewAbstractModel::GetInstance()->SetPivot(centerX, centerY, 0.0_vp);
            return;
        } else {
            SetDefaultScale();
        }
    }
    double scale = 0.0;
    if (ParseJsDouble(info[0], scale)) {
        ViewAbstractModel::GetInstance()->SetScale(scale, scale, 1.0f);
    }
}

void JSViewAbstract::SetDefaultScale()
{
    ViewAbstractModel::GetInstance()->SetScale(1.0f, 1.0f, 1.0f);
    ViewAbstractModel::GetInstance()->SetPivot(0.5_pct, 0.5_pct, 0.0_vp);
}

void JSViewAbstract::JsScaleX(const JSCallbackInfo& info)
{
    double scaleVal = 0.0;
    if (!ParseJsDouble(info[0], scaleVal)) {
        return;
    }
    ViewAbstractModel::GetInstance()->SetScale(scaleVal, 1.0f, 1.0f);
}

void JSViewAbstract::JsScaleY(const JSCallbackInfo& info)
{
    double scaleVal = 0.0;
    if (!ParseJsDouble(info[0], scaleVal)) {
        return;
    }
    ViewAbstractModel::GetInstance()->SetScale(1.0f, scaleVal, 1.0f);
}

void JSViewAbstract::JsOpacity(const JSCallbackInfo& info)
{
    double opacity = 0.0;
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::OBJECT, JSCallbackInfoType::NUMBER,
        JSCallbackInfoType::STRING };
    if (!CheckJSCallbackInfo("Opacity", info, checkList)) {
        ViewAbstractModel::GetInstance()->SetOpacity(1.0f);
        return;
    }
    if (!ParseJsDouble(info[0], opacity)) {
        return;
    }
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        if (opacity > 1.0 || LessNotEqual(opacity, 0.0)) {
            opacity = 1.0;
        }
    } else {
        opacity = std::clamp(opacity, 0.0, 1.0);
    }
    ViewAbstractModel::GetInstance()->SetOpacity(opacity);
}

void JSViewAbstract::JsTranslate(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::STRING, JSCallbackInfoType::NUMBER,
        JSCallbackInfoType::OBJECT };
    if (!CheckJSCallbackInfo("JsTranslate", info, checkList)) {
        SetDefaultTranslate();
        return;
    }

    if (info[0]->IsObject()) {
        JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);
        if (jsObj->HasProperty("x") || jsObj->HasProperty("y") || jsObj->HasProperty("z")) {
            // default: x, y, z (0.0, 0.0, 0.0)
            auto translateX = CalcDimension(0.0);
            auto translateY = CalcDimension(0.0);
            auto translateZ = CalcDimension(0.0);
            ParseJsTranslate(info[0], translateX, translateY, translateZ);
            ViewAbstractModel::GetInstance()->SetTranslate(translateX, translateY, translateZ);
            return;
        } else {
            SetDefaultTranslate();
        }
    }
    CalcDimension value;
    if (ParseJsDimensionVp(info[0], value)) {
        ViewAbstractModel::GetInstance()->SetTranslate(value, value, value);
    }
}

void JSViewAbstract::SetDefaultTranslate()
{
    ViewAbstractModel::GetInstance()->SetTranslate(CalcDimension(0.0), CalcDimension(0.0), CalcDimension(0.0));
}

void JSViewAbstract::JsTranslateX(const JSCallbackInfo& info)
{
    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return;
    }
    ViewAbstractModel::GetInstance()->SetTranslate(value, 0.0_px, 0.0_px);
}

void JSViewAbstract::JsTranslateY(const JSCallbackInfo& info)
{
    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return;
    }
    ViewAbstractModel::GetInstance()->SetTranslate(0.0_px, value, 0.0_px);
}

void JSViewAbstract::JsRotate(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::NUMBER, JSCallbackInfoType::OBJECT };
    if (!CheckJSCallbackInfo("JsRotate", info, checkList)) {
        SetDefaultRotate();
        return;
    }

    if (info[0]->IsObject()) {
        NG::RotateOptions rotate(0.0f, 0.0f, 0.0f, 0.0f, 0.5_pct, 0.5_pct);
        std::optional<float> angle;
        ParseJsRotate(info[0], rotate, angle);
        if (angle) {
            ViewAbstractModel::GetInstance()->SetRotate(
                rotate.xDirection, rotate.yDirection, rotate.zDirection, angle.value(), rotate.perspective);
            ViewAbstractModel::GetInstance()->SetPivot(rotate.centerX, rotate.centerY, rotate.centerZ);
        } else {
            SetDefaultRotate();
        }
        return;
    }
    double rotateZ;
    if (ParseJsDouble(info[0], rotateZ)) {
        ViewAbstractModel::GetInstance()->SetRotate(0.0f, 0.0f, 1.0f, rotateZ);
    }
}

void JSViewAbstract::SetDefaultRotate()
{
    NG::RotateOptions rotate(0.0f, 0.0f, 0.0f, 0.0f, 0.5_pct, 0.5_pct, 0.0f, 0.0f);
    ViewAbstractModel::GetInstance()->SetRotate(
        rotate.xDirection, rotate.yDirection, rotate.zDirection, 0.0f, rotate.perspective);
    ViewAbstractModel::GetInstance()->SetPivot(rotate.centerX, rotate.centerY, rotate.centerZ);
}

void JSViewAbstract::JsRotateX(const JSCallbackInfo& info)
{
    double rotateVal = 0.0;
    if (!ParseJsDouble(info[0], rotateVal)) {
        return;
    }
    ViewAbstractModel::GetInstance()->SetRotate(1.0f, 0.0f, 0.0f, rotateVal);
}

void JSViewAbstract::JsRotateY(const JSCallbackInfo& info)
{
    double rotateVal = 0.0;
    if (!ParseJsDouble(info[0], rotateVal)) {
        return;
    }
    ViewAbstractModel::GetInstance()->SetRotate(0.0f, 1.0f, 0.0f, rotateVal);
}

void JSViewAbstract::JsTransform(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::OBJECT };
    if (!CheckJSCallbackInfo("JsTransform", info, checkList)) {
        SetDefaultTransform();
        return;
    }
    JSRef<JSVal> array = JSRef<JSObject>::Cast(info[0])->GetProperty("matrix4x4");
    const auto matrix4Len = Matrix4::DIMENSION * Matrix4::DIMENSION;
    if (!array->IsArray() || JSRef<JSArray>::Cast(array)->Length() != matrix4Len) {
        return;
    }
    JSRef<JSArray> jsArray = JSRef<JSArray>::Cast(array);
    std::vector<float> matrix(matrix4Len);
    for (int32_t i = 0; i < matrix4Len; i++) {
        double value = 0.0;
        ParseJsDouble(jsArray->GetValueAt(i), value);
        matrix[i] = static_cast<float>(value);
    }
    ViewAbstractModel::GetInstance()->SetTransformMatrix(matrix);
}

void JSViewAbstract::SetDefaultTransform()
{
    const auto matrix4Len = Matrix4::DIMENSION * Matrix4::DIMENSION;
    std::vector<float> matrix(matrix4Len);
    const int32_t initPosition = 5;
    for (int32_t i = 0; i < matrix4Len; i = i + initPosition) {
        double value = 1.0;
        matrix[i] = static_cast<float>(value);
    }
    ViewAbstractModel::GetInstance()->SetTransformMatrix(matrix);
}

NG::TransitionOptions JSViewAbstract::ParseTransition(std::unique_ptr<JsonValue>& transitionArgs)
{
    bool hasEffect = false;
    NG::TransitionOptions transitionOption;
    transitionOption.Type = ParseTransitionType(transitionArgs->GetString("type", "All"));
    if (transitionArgs->Contains("opacity")) {
        double opacity = 1.0;
        ParseJsonDouble(transitionArgs->GetValue("opacity"), opacity);
        if (opacity > 1.0 || LessNotEqual(opacity, 0.0)) {
            opacity = 1.0;
        }
        transitionOption.UpdateOpacity(static_cast<float>(opacity));
        hasEffect = true;
    }
    if (transitionArgs->Contains("translate")) {
        auto translateArgs = transitionArgs->GetObject("translate");
        // default: x, y, z (0.0, 0.0, 0.0)
        NG::TranslateOptions translate;
        ParseJsonTranslate(translateArgs, translate.x, translate.y, translate.z);
        transitionOption.UpdateTranslate(translate);
        hasEffect = true;
    }
    if (transitionArgs->Contains("scale")) {
        auto scaleArgs = transitionArgs->GetObject("scale");
        // default: x, y, z (1.0, 1.0, 1.0), centerX, centerY 50% 50%;
        NG::ScaleOptions scale(1.0f, 1.0f, 1.0f, 0.5_pct, 0.5_pct);
        ParseJsonScale(scaleArgs, scale.xScale, scale.yScale, scale.zScale, scale.centerX, scale.centerY);
        transitionOption.UpdateScale(scale);
        hasEffect = true;
    }
    if (transitionArgs->Contains("rotate")) {
        auto rotateArgs = transitionArgs->GetObject("rotate");
        // default: dx, dy, dz (0.0, 0.0, 0.0), angle 0, centerX, centerY 50% 50%;
        NG::RotateOptions rotate(0.0f, 0.0f, 0.0f, 0.0f, 0.5_pct, 0.5_pct);
        std::optional<float> angle;
        ParseJsonRotate(rotateArgs, rotate, angle);
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

NG::TransitionOptions JSViewAbstract::ParseJsTransition(const JSRef<JSVal>& transitionArgs)
{
    NG::TransitionOptions transitionOption;
    if (!transitionArgs->IsObject()) {
        return transitionOption;
    }

    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(transitionArgs);
    bool hasEffect = false;
    transitionOption.Type = ParseTransitionType(jsObj->GetPropertyValue<std::string>("type", "All"));
    if (jsObj->HasProperty("opacity")) {
        double opacity = 1.0;
        ParseJsDouble(jsObj->GetProperty("opacity"), opacity);
        if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
            if (opacity > 1.0 || LessNotEqual(opacity, 0.0)) {
                opacity = 1.0;
            }
        } else {
            opacity = std::clamp(opacity, 0.0, 1.0);
        }
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
        ParseJsScale(jsObj->GetProperty("scale"), scale.xScale, scale.yScale, scale.zScale,
            scale.centerX, scale.centerY);
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

void JSViewAbstract::JsTransition(const JSCallbackInfo& info)
{
    if (info.Length() > 1) {
        return;
    }
    if (info.Length() == 0) {
        ViewAbstractModel::GetInstance()->SetTransition(
            NG::TransitionOptions::GetDefaultTransition(TransitionType::ALL));
        return;
    }
    if (!info[0]->IsObject()) {
        return;
    }
    auto obj = JSRef<JSObject>::Cast(info[0]);
    if (!obj->GetProperty("successor_")->IsUndefined()) {
        auto chainedEffect = ParseChainedTransition(obj, info.GetExecutionContext());
        ViewAbstractModel::GetInstance()->SetChainedTransition(chainedEffect);
        return;
    }
    auto options = ParseJsTransition(info[0]);
    ViewAbstractModel::GetInstance()->SetTransition(options);
}

void JSViewAbstract::JsWidth(const JSCallbackInfo& info)
{
    JsWidth(info[0]);
}

bool JSViewAbstract::JsWidth(const JSRef<JSVal>& jsValue)
{
    CalcDimension value;
    if (jsValue->IsUndefined()) {
        ViewAbstractModel::GetInstance()->ClearWidthOrHeight(true);
        return true;
    }
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        if (!ParseJsDimensionVpNG(jsValue, value)) {
            ViewAbstractModel::GetInstance()->ClearWidthOrHeight(true);
            return false;
        }
    } else if (!ParseJsDimensionVp(jsValue, value)) {
        return false;
    }

    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }

    ViewAbstractModel::GetInstance()->SetWidth(value);
    return true;
}

void JSViewAbstract::JsHeight(const JSCallbackInfo& info)
{
    JsHeight(info[0]);
}

bool JSViewAbstract::JsHeight(const JSRef<JSVal>& jsValue)
{
    CalcDimension value;
    if (jsValue->IsUndefined()) {
        ViewAbstractModel::GetInstance()->ClearWidthOrHeight(false);
        return true;
    }
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        if (!ParseJsDimensionVpNG(jsValue, value)) {
            ViewAbstractModel::GetInstance()->ClearWidthOrHeight(false);
            return false;
        }
    } else if (!ParseJsDimensionVp(jsValue, value)) {
        return false;
    }

    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }

    ViewAbstractModel::GetInstance()->SetHeight(value);
    return true;
}

void JSViewAbstract::JsResponseRegion(const JSCallbackInfo& info)
{
    std::vector<DimensionRect> result;
    if (!JSViewAbstract::ParseJsResponseRegionArray(info[0], result)) {
        return;
    }

    ViewAbstractModel::GetInstance()->SetResponseRegion(result);
}

void JSViewAbstract::JsMouseResponseRegion(const JSCallbackInfo& info)
{
    std::vector<DimensionRect> result;
    if (!JSViewAbstract::ParseJsResponseRegionArray(info[0], result)) {
        return;
    }
    ViewAbstractModel::GetInstance()->SetMouseResponseRegion(result);
}

bool JSViewAbstract::ParseJsDimensionRect(const JSRef<JSVal>& jsValue, DimensionRect& result)
{
    if (!jsValue->IsObject()) {
        return false;
    }

    JSRef<JSObject> obj = JSRef<JSObject>::Cast(jsValue);
    JSRef<JSVal> x = obj->GetProperty("x");
    JSRef<JSVal> y = obj->GetProperty("y");
    JSRef<JSVal> width = obj->GetProperty("width");
    JSRef<JSVal> height = obj->GetProperty("height");
    CalcDimension xDimen = result.GetOffset().GetX();
    CalcDimension yDimen = result.GetOffset().GetY();
    CalcDimension widthDimen = result.GetWidth();
    CalcDimension heightDimen = result.GetHeight();
    auto s1 = width->ToString();
    auto s2 = height->ToString();
    if (s1.find('-') != std::string::npos) {
        width = JSRef<JSVal>::Make(ToJSValue("100%"));
    }
    if (s2.find('-') != std::string::npos) {
        height = JSRef<JSVal>::Make(ToJSValue("100%"));
    }
    if (ParseJsDimensionNG(x, xDimen, DimensionUnit::VP)) {
        auto offset = result.GetOffset();
        offset.SetX(xDimen);
        result.SetOffset(offset);
    }
    if (ParseJsDimensionNG(y, yDimen, DimensionUnit::VP)) {
        auto offset = result.GetOffset();
        offset.SetY(yDimen);
        result.SetOffset(offset);
    }
    if (ParseJsDimensionNG(width, widthDimen, DimensionUnit::VP)) {
        if (widthDimen.Unit() == DimensionUnit::PERCENT && widthDimen.Value() < 0) {
            return true;
        }
        result.SetWidth(widthDimen);
    }
    if (ParseJsDimensionNG(height, heightDimen, DimensionUnit::VP)) {
        if (heightDimen.Unit() == DimensionUnit::PERCENT && heightDimen.Value() < 0) {
            return true;
        }
        result.SetHeight(heightDimen);
    }
    return true;
}

bool JSViewAbstract::ParseJsResponseRegionArray(const JSRef<JSVal>& jsValue, std::vector<DimensionRect>& result)
{
    if (!jsValue->IsArray() && !jsValue->IsObject()) {
        return false;
    }

    if (jsValue->IsArray()) {
        JSRef<JSArray> array = JSRef<JSArray>::Cast(jsValue);
        for (size_t i = 0; i < array->Length(); i++) {
            CalcDimension xDimen = CalcDimension(0.0, DimensionUnit::VP);
            CalcDimension yDimen = CalcDimension(0.0, DimensionUnit::VP);
            CalcDimension widthDimen = CalcDimension(1, DimensionUnit::PERCENT);
            CalcDimension heightDimen = CalcDimension(1, DimensionUnit::PERCENT);
            DimensionOffset offsetDimen(xDimen, yDimen);
            DimensionRect dimenRect(widthDimen, heightDimen, offsetDimen);
            if (ParseJsDimensionRect(array->GetValueAt(i), dimenRect)) {
                result.emplace_back(dimenRect);
            } else {
                return false;
            }
        }
        return true;
    }

    CalcDimension xDimen = CalcDimension(0.0, DimensionUnit::VP);
    CalcDimension yDimen = CalcDimension(0.0, DimensionUnit::VP);
    CalcDimension widthDimen = CalcDimension(1, DimensionUnit::PERCENT);
    CalcDimension heightDimen = CalcDimension(1, DimensionUnit::PERCENT);
    DimensionOffset offsetDimen(xDimen, yDimen);
    DimensionRect dimenRect(widthDimen, heightDimen, offsetDimen);
    if (ParseJsDimensionRect(jsValue, dimenRect)) {
        result.emplace_back(dimenRect);
        return true;
    } else {
        return false;
    }
}

void JSViewAbstract::JsSize(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::OBJECT };
    if (!CheckJSCallbackInfo("JsSize", info, checkList)) {
        return;
    }

    JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(info[0]);
    JsWidth(sizeObj->GetProperty("width"));
    JsHeight(sizeObj->GetProperty("height"));
}

void JSViewAbstract::JsConstraintSize(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::OBJECT };
    if (!CheckJSCallbackInfo("JsConstraintSize", info, checkList)) {
        ViewAbstractModel::GetInstance()->ResetMaxSize(true);
        ViewAbstractModel::GetInstance()->ResetMinSize(true);
        ViewAbstractModel::GetInstance()->ResetMaxSize(false);
        ViewAbstractModel::GetInstance()->ResetMinSize(false);
        return;
    }

    JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(info[0]);

    JSRef<JSVal> minWidthValue = sizeObj->GetProperty("minWidth");
    CalcDimension minWidth;
    JSRef<JSVal> maxWidthValue = sizeObj->GetProperty("maxWidth");
    CalcDimension maxWidth;
    JSRef<JSVal> minHeightValue = sizeObj->GetProperty("minHeight");
    CalcDimension minHeight;
    JSRef<JSVal> maxHeightValue = sizeObj->GetProperty("maxHeight");
    CalcDimension maxHeight;
    bool version10OrLarger = Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN);
    if (ParseJsDimensionVp(minWidthValue, minWidth)) {
        ViewAbstractModel::GetInstance()->SetMinWidth(minWidth);
    } else if (version10OrLarger) {
        ViewAbstractModel::GetInstance()->ResetMinSize(true);
    }

    if (ParseJsDimensionVp(maxWidthValue, maxWidth)) {
        ViewAbstractModel::GetInstance()->SetMaxWidth(maxWidth);
    } else if (version10OrLarger) {
        ViewAbstractModel::GetInstance()->ResetMaxSize(true);
    }

    if (ParseJsDimensionVp(minHeightValue, minHeight)) {
        ViewAbstractModel::GetInstance()->SetMinHeight(minHeight);
    } else if (version10OrLarger) {
        ViewAbstractModel::GetInstance()->ResetMinSize(false);
    }

    if (ParseJsDimensionVp(maxHeightValue, maxHeight)) {
        ViewAbstractModel::GetInstance()->SetMaxHeight(maxHeight);
    } else if (version10OrLarger) {
        ViewAbstractModel::GetInstance()->ResetMaxSize(false);
    }
}

void JSViewAbstract::JsLayoutPriority(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::STRING, JSCallbackInfoType::NUMBER };
    if (!CheckJSCallbackInfo("JsLayoutPriority", info, checkList)) {
        return;
    }

    int32_t priority;
    if (info[0]->IsNumber()) {
        priority = info[0]->ToNumber<int32_t>();
    } else {
        priority = static_cast<int32_t>(StringUtils::StringToUint(info[0]->ToString()));
    }
    ViewAbstractModel::GetInstance()->SetLayoutPriority(priority);
}

void JSViewAbstract::JsLayoutWeight(const JSCallbackInfo& info)
{
    int32_t value = 0.0;
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::STRING, JSCallbackInfoType::NUMBER };
    if (!CheckJSCallbackInfo("JsLayoutWeight", info, checkList)) {
        if (!info[0]->IsUndefined()) {
            return;
        }
    }

    if (info[0]->IsNumber()) {
        value = info[0]->ToNumber<int32_t>();
    } else {
        value = static_cast<int32_t>(StringUtils::StringToUint(info[0]->ToString()));
    }

    ViewAbstractModel::GetInstance()->SetLayoutWeight(value);
}

void JSViewAbstract::JsAlign(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::NUMBER };
    if (!CheckJSCallbackInfo("JsAlign", info, checkList) &&
        Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        ViewAbstractModel::GetInstance()->SetAlign(Alignment::CENTER);
        return;
    }
    auto value = info[0]->ToNumber<int32_t>();
    Alignment alignment = ParseAlignment(value);
    ViewAbstractModel::GetInstance()->SetAlign(alignment);
}

void JSViewAbstract::JsPosition(const JSCallbackInfo& info)
{
    CalcDimension x;
    CalcDimension y;
    if (ParseLocationProps(info, x, y)) {
        ViewAbstractModel::GetInstance()->SetPosition(x, y);
    } else {
        ViewAbstractModel::GetInstance()->SetPosition(0.0_vp, 0.0_vp);
    }
}

void JSViewAbstract::JsMarkAnchor(const JSCallbackInfo& info)
{
    CalcDimension x;
    CalcDimension y;
    if (ParseLocationProps(info, x, y)) {
        ViewAbstractModel::GetInstance()->MarkAnchor(x, y);
    } else {
        ViewAbstractModel::GetInstance()->MarkAnchor(0.0_vp, 0.0_vp);
    }
}

void JSViewAbstract::JsOffset(const JSCallbackInfo& info)
{
    CalcDimension x;
    CalcDimension y;
    if (ParseLocationProps(info, x, y)) {
        ViewAbstractModel::GetInstance()->SetOffset(x, y);
    } else {
        ViewAbstractModel::GetInstance()->SetOffset(0.0_vp, 0.0_vp);
    }
}

void JSViewAbstract::JsEnabled(const JSCallbackInfo& info)
{
    bool enabled;
    if (!info[0]->IsBoolean()) {
        enabled = true;
    } else {
        enabled = info[0]->ToBoolean();
    }

    ViewAbstractModel::GetInstance()->SetEnabled(enabled);
}

void JSViewAbstract::JsAspectRatio(const JSCallbackInfo& info)
{
    double value = 0.0;
    if (!ParseJsDouble(info[0], value)) {
        // add version protection, undefined use default value
        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN) &&
            (info[0]->IsNull() || info[0]->IsUndefined())) {
            ViewAbstractModel::GetInstance()->ResetAspectRatio();
            return;
        } else {
            return;
        }
    }

    // negative use default value.
    if (LessOrEqual(value, 0.0)) {
        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
            ViewAbstractModel::GetInstance()->ResetAspectRatio();
            return;
        } else {
            value = 1.0;
        }
    }

    ViewAbstractModel::GetInstance()->SetAspectRatio(static_cast<float>(value));
}

void JSViewAbstract::JsOverlay(const JSCallbackInfo& info)
{
    if (info.Length() > 0 && (info[0]->IsUndefined())) {
        ViewAbstractModel::GetInstance()->SetOverlay(
            "", nullptr, Alignment::TOP_LEFT, CalcDimension(0), CalcDimension(0));
        return;
    }

    if (info.Length() <= 0 || (!info[0]->IsString() && !info[0]->IsObject())) {
        return;
    }
    std::optional<Alignment> align;
    std::optional<CalcDimension> offsetX;
    std::optional<CalcDimension> offsetY;

    if (info[1]->IsObject()) {
        JSRef<JSObject> optionObj = JSRef<JSObject>::Cast(info[1]);
        JSRef<JSVal> alignVal = optionObj->GetProperty("align");
        auto value = alignVal->ToNumber<int32_t>();
        Alignment alignment = ParseAlignment(value);
        align = alignment;

        JSRef<JSVal> val = optionObj->GetProperty("offset");
        if (val->IsObject()) {
            JSRef<JSObject> offsetObj = JSRef<JSObject>::Cast(val);
            JSRef<JSVal> xVal = offsetObj->GetProperty("x");
            CalcDimension x;
            if (ParseJsDimensionVp(xVal, x)) {
                offsetX = x;
            }
            JSRef<JSVal> yVal = offsetObj->GetProperty("y");
            CalcDimension y;
            if (ParseJsDimensionVp(yVal, y)) {
                offsetY = y;
            }
        }
    }

    if (info[0]->IsString()) {
        std::string text = info[0]->ToString();
        ViewAbstractModel::GetInstance()->SetOverlay(text, nullptr, align, offsetX, offsetY);
    } else if (info[0]->IsObject()) {
        JSRef<JSObject> menuObj = JSRef<JSObject>::Cast(info[0]);
        auto builder = menuObj->GetProperty("builder");
        if (!builder->IsFunction()) {
            return;
        }
        auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(builder));
        CHECK_NULL_VOID(builderFunc);
        WeakPtr<NG::FrameNode> targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
        auto buildFunc = [execCtx = info.GetExecutionContext(), func = std::move(builderFunc), node = targetNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Overlay");
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
        ViewAbstractModel::GetInstance()->SetOverlay("", std::move(buildFunc), align, offsetX, offsetY);
    }
}

Alignment JSViewAbstract::ParseAlignment(int32_t align)
{
    Alignment alignment = Alignment::CENTER;
    switch (align) {
        case 0:
            alignment = Alignment::TOP_LEFT;
            break;
        case 1:
            alignment = Alignment::TOP_CENTER;
            break;
        case 2:
            alignment = Alignment::TOP_RIGHT;
            break;
        case 3:
            alignment = Alignment::CENTER_LEFT;
            break;
        case 4:
            alignment = Alignment::CENTER;
            break;
        case 5:
            alignment = Alignment::CENTER_RIGHT;
            break;
        case 6:
            alignment = Alignment::BOTTOM_LEFT;
            break;
        case 7:
            alignment = Alignment::BOTTOM_CENTER;
            break;
        case 8:
            alignment = Alignment::BOTTOM_RIGHT;
            break;
        default:
            break;
    }
    return alignment;
}

void JSViewAbstract::SetVisibility(const JSCallbackInfo& info)
{
    int32_t visible = 0;
    if (info[0]->IsNull() || info[0]->IsUndefined()) {
        // undefined value use default value.
        visible = 0;
    } else if (!info[0]->IsNumber()) {
        return;
    } else {
        visible = info[0]->ToNumber<int32_t>();
    }

    if (info.Length() > 1 && info[1]->IsFunction()) {
        RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[1]));
        WeakPtr<NG::FrameNode> targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
        auto onVisibilityChange = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                                      int32_t visible) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("onVisibilityChange");
            PipelineContext::SetCallBackNode(node);
            JSRef<JSVal> newJSVal = JSRef<JSVal>::Make(ToJSValue(visible));
            func->ExecuteJS(1, &newJSVal);
        };
        ViewAbstractModel::GetInstance()->SetVisibility(
            static_cast<VisibleType>(visible), std::move(onVisibilityChange));
    } else {
        ViewAbstractModel::GetInstance()->SetVisibility(static_cast<VisibleType>(visible), [](int32_t visible) {});
    }
}

void JSViewAbstract::JsFlexBasis(const JSCallbackInfo& info)
{
    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        value.SetUnit(DimensionUnit::AUTO);
    }
    // flexbasis don't support percent case.
    if (value.Unit() == DimensionUnit::PERCENT) {
        value.SetUnit(DimensionUnit::AUTO);
    }
    ViewAbstractModel::GetInstance()->SetFlexBasis(value);
}

void JSViewAbstract::JsFlexGrow(const JSCallbackInfo& info)
{
    double value = 0.0;
    if (!ParseJsDouble(info[0], value)) {
        if (info[0]->IsNull() || info[0]->IsUndefined()) {
            // undefined use default value.
            value = 0.0;
        } else {
            return;
        }
    }
    // negative use default value.
    if (value < 0.0) {
        value = 0.0;
    }
    ViewAbstractModel::GetInstance()->SetFlexGrow(static_cast<float>(value));
}

void JSViewAbstract::JsFlexShrink(const JSCallbackInfo& info)
{
    double value = 0.0;
    if (!ParseJsDouble(info[0], value)) {
        if (info[0]->IsNull() || info[0]->IsUndefined()) {
            // undefined use default value.
            ViewAbstractModel::GetInstance()->ResetFlexShrink();
        } else {
            return;
        }
    }
    // negative use default value.
    if (value < 0.0) {
        ViewAbstractModel::GetInstance()->ResetFlexShrink();
        return;
    }
    ViewAbstractModel::GetInstance()->SetFlexShrink(static_cast<float>(value));
}

void JSViewAbstract::JsDisplayPriority(const JSCallbackInfo& info)
{
    double value = 0.0;
    if (!ParseJsDouble(info[0], value)) {
        return;
    }
    ViewAbstractModel::GetInstance()->SetDisplayIndex(static_cast<int32_t>(value));
}

void JSViewAbstract::JsSharedTransition(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::STRING };
    if (!CheckJSCallbackInfo("JsSharedTransition", info, checkList)) {
        return;
    }
    // id
    auto id = info[0]->ToString();
    if (id.empty()) {
        return;
    }
    std::shared_ptr<SharedTransitionOption> sharedOption;

    // options
    if (info.Length() > 1 && info[1]->IsObject()) {
        JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[1]);
        sharedOption = std::make_shared<SharedTransitionOption>();
        // default: duration: 1000
        sharedOption->duration = jsObj->GetPropertyValue<int32_t>("duration", DEFAULT_DURATION);
        if (sharedOption->duration < 0) {
            sharedOption->duration = DEFAULT_DURATION;
        }
        // default: delay: 0
        sharedOption->delay = jsObj->GetPropertyValue<int32_t>("delay", 0);
        if (sharedOption->delay < 0) {
            sharedOption->delay = 0;
        }
        // default: LinearCurve
        RefPtr<Curve> curve;
        JSRef<JSVal> curveArgs = jsObj->GetProperty("curve");
        if (curveArgs->IsString()) {
            curve = CreateCurve(jsObj->GetPropertyValue<std::string>("curve", "linear"), false);
        } else if (curveArgs->IsObject()) {
            JSRef<JSVal> curveString = JSRef<JSObject>::Cast(curveArgs)->GetProperty("__curveString");
            if (!curveString->IsString()) {
                return;
            }
            curve = CreateCurve(curveString->ToString(), false);
        }
        if (!curve) {
            curve = Curves::LINEAR;
        }
        sharedOption->curve = curve;
        // motionPath
        if (jsObj->HasProperty("motionPath")) {
            MotionPathOption motionPathOption;
            if (ParseMotionPath(jsObj->GetProperty("motionPath"), motionPathOption)) {
                sharedOption->motionPathOption = motionPathOption;
            }
        }
        // zIndex
        sharedOption->zIndex = jsObj->GetPropertyValue<int32_t>("zIndex", 0);
        // type
        int32_t type = jsObj->GetPropertyValue<int32_t>("type",
            static_cast<int32_t>(SharedTransitionEffectType::SHARED_EFFECT_EXCHANGE));
        sharedOption->type = static_cast<SharedTransitionEffectType>(type);
    }
    ViewAbstractModel::GetInstance()->SetSharedTransition(id, sharedOption);
}

void JSViewAbstract::JsGeometryTransition(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::STRING };
    if (!CheckJSCallbackInfo("JsGeometryTransition", info, checkList)) {
        return;
    }
    // id
    auto id = info[0]->ToString();
    // follow flag
    bool followWithOutTransition = false;
    if (info.Length() >= PARAMETER_LENGTH_SECOND) {
        if (info[1]->IsBoolean()) {
            followWithOutTransition = info[1]->ToBoolean();
        } else if (info[1]->IsObject()) {
            JSRef<JSObject> jsOption = JSRef<JSObject>::Cast(info[1]);
            ParseJsBool(jsOption->GetProperty("follow"), followWithOutTransition);
        }
    }
    ViewAbstractModel::GetInstance()->SetGeometryTransition(id, followWithOutTransition);
}

void JSViewAbstract::JsAlignSelf(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::NUMBER };
    if (!CheckJSCallbackInfo("JsAlignSelf", info, checkList)) {
        ViewAbstractModel::GetInstance()->SetAlignSelf(FlexAlign::AUTO);
        return;
    }
    auto alignVal = info[0]->ToNumber<int32_t>();

    if (alignVal >= 0 && alignVal <= MAX_ALIGN_VALUE) {
        ViewAbstractModel::GetInstance()->SetAlignSelf(static_cast<FlexAlign>(alignVal));
    }
}

void JSViewAbstract::JsBackgroundColor(const JSCallbackInfo& info)
{
    Color backgroundColor;
    if (!ParseJsColor(info[0], backgroundColor)) {
        backgroundColor = Color::TRANSPARENT;
    }

    ViewAbstractModel::GetInstance()->SetBackgroundColor(backgroundColor);
}

void JSViewAbstract::JsBackgroundImage(const JSCallbackInfo& info)
{
    std::string src;
    std::string bundle;
    std::string module;
    RefPtr<PixelMap> pixmap = nullptr;
    GetJsMediaBundleInfo(info[0], bundle, module);
    if (info[0]->IsString()) {
        src = info[0]->ToString();
        ViewAbstractModel::GetInstance()->SetBackgroundImage(
            ImageSourceInfo { src, bundle, module }, GetThemeConstants());
    } else if (ParseJsMedia(info[0], src)) {
        ViewAbstractModel::GetInstance()->SetBackgroundImage(ImageSourceInfo { src, bundle, module }, nullptr);
    } else {
#if defined(PIXEL_MAP_SUPPORTED)
        if (IsDrawable(info[0])) {
            pixmap = GetDrawablePixmap(info[0]);
        } else {
            pixmap = CreatePixelMapFromNapiValue(info[0]);
        }
#endif
        CHECK_NULL_VOID(pixmap);
        ViewAbstractModel::GetInstance()->SetBackgroundImage(ImageSourceInfo { pixmap }, nullptr);
    }

    int32_t repeatIndex = 0;
    if (info.Length() == 2 && info[1]->IsNumber()) {
        repeatIndex = info[1]->ToNumber<int32_t>();
    }
    auto repeat = static_cast<ImageRepeat>(repeatIndex);
    ViewAbstractModel::GetInstance()->SetBackgroundImageRepeat(repeat);
}

void JSViewAbstract::ParseBlurOption(const JSRef<JSObject>& jsBlurOption, BlurOption& blurOption)
{
    if (jsBlurOption->GetProperty("grayscale")->IsArray()) {
        JSRef<JSArray> params = JSRef<JSArray>::Cast(jsBlurOption->GetProperty("grayscale"));
        auto grey1 = params->GetValueAt(0)->ToNumber<uint32_t>();
        auto grey2 = params->GetValueAt(1)->ToNumber<uint32_t>();
        std::vector<float> greyVec(2); // 2 number
        greyVec[0] = grey1;
        greyVec[1] = grey2;
        blurOption.grayscale = greyVec;
    }
}

void JSViewAbstract::JsBackgroundBlurStyle(const JSCallbackInfo& info)
{
    if (info.Length() == 0) {
        return;
    }
    BlurStyleOption styleOption;
    if (info[0]->IsNumber()) {
        auto blurStyle = info[0]->ToNumber<int32_t>();
        if (blurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
            blurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
            styleOption.blurStyle = static_cast<BlurStyle>(blurStyle);
        }
    }
    if (info.Length() > 1 && info[1]->IsObject()) {
        JSRef<JSObject> jsOption = JSRef<JSObject>::Cast(info[1]);
        auto colorMode = static_cast<int32_t>(ThemeColorMode::SYSTEM);
        ParseJsInt32(jsOption->GetProperty("colorMode"), colorMode);
        if (colorMode >= static_cast<int32_t>(ThemeColorMode::SYSTEM) &&
            colorMode <= static_cast<int32_t>(ThemeColorMode::DARK)) {
            styleOption.colorMode = static_cast<ThemeColorMode>(colorMode);
        }
        auto adaptiveColor = static_cast<int32_t>(AdaptiveColor::DEFAULT);
        ParseJsInt32(jsOption->GetProperty("adaptiveColor"), adaptiveColor);
        if (adaptiveColor >= static_cast<int32_t>(AdaptiveColor::DEFAULT) &&
            adaptiveColor <= static_cast<int32_t>(AdaptiveColor::AVERAGE)) {
            styleOption.adaptiveColor = static_cast<AdaptiveColor>(adaptiveColor);
        }
        if (jsOption->GetProperty("scale")->IsNumber()) {
            double scale = jsOption->GetProperty("scale")->ToNumber<double>();
            styleOption.scale = std::clamp(scale, 0.0, 1.0);
        }

        if (jsOption->GetProperty("blurOptions")->IsObject()) {
            JSRef<JSObject> jsBlurOption = JSRef<JSObject>::Cast(jsOption->GetProperty("blurOptions"));
            BlurOption blurOption;
            ParseBlurOption(jsBlurOption, blurOption);
            styleOption.blurOption = blurOption;
        }
    }
    ViewAbstractModel::GetInstance()->SetBackgroundBlurStyle(styleOption);
}

void JSViewAbstract::ParseEffectOption(const JSRef<JSObject>& jsOption, EffectOption& effectOption)
{
    CalcDimension radius;
    if (!ParseJsDimensionVp(jsOption->GetProperty("radius"), radius) || LessNotEqual(radius.Value(), 0.0f)) {
        radius.SetValue(0.0f);
    }
    double saturation = 1.0f;
    if (jsOption->GetProperty("saturation")->IsNumber()) {
        saturation = jsOption->GetProperty("saturation")->ToNumber<double>();
        saturation = (saturation > 0.0f || NearZero(saturation)) ? saturation : 1.0f;
    }
    double brightness = 1.0f;
    if (jsOption->GetProperty("brightness")->IsNumber()) {
        brightness = jsOption->GetProperty("brightness")->ToNumber<double>();
        brightness = (brightness > 0.0f || NearZero(brightness)) ? brightness : 1.0f;
    }
    Color color = Color::TRANSPARENT;
    if (!ParseJsColor(jsOption->GetProperty("color"), color)) {
        color.SetValue(Color::TRANSPARENT.GetValue());
    }
    auto adaptiveColorValue = static_cast<int32_t>(AdaptiveColor::DEFAULT);
    auto adaptiveColor = AdaptiveColor::DEFAULT;
    ParseJsInt32(jsOption->GetProperty("adaptiveColor"), adaptiveColorValue);
    if (adaptiveColorValue >= static_cast<int32_t>(AdaptiveColor::DEFAULT) &&
        adaptiveColorValue <= static_cast<int32_t>(AdaptiveColor::AVERAGE)) {
        adaptiveColor = static_cast<AdaptiveColor>(adaptiveColorValue);
    }

    BlurOption blurOption;
    if (jsOption->GetProperty("blurOptions")->IsObject()) {
        JSRef<JSObject> jsBlurOption = JSRef<JSObject>::Cast(jsOption->GetProperty("blurOptions"));
        ParseBlurOption(jsBlurOption, blurOption);
    }
    effectOption = { radius, saturation, brightness, color, adaptiveColor, blurOption };
}

void JSViewAbstract::JsBackgroundEffect(const JSCallbackInfo& info)
{
    if (info.Length() == 0) {
        return;
    }
    if (!info[0]->IsObject()) {
        return;
    }
    JSRef<JSObject> jsOption = JSRef<JSObject>::Cast(info[0]);
    EffectOption option;
    ParseEffectOption(jsOption, option);
    ViewAbstractModel::GetInstance()->SetBackgroundEffect(option);
}

void JSViewAbstract::JsForegroundBlurStyle(const JSCallbackInfo& info)
{
    if (info.Length() == 0) {
        return;
    }
    BlurStyleOption styleOption;
    if (info[0]->IsNumber()) {
        auto blurStyle = info[0]->ToNumber<int32_t>();
        if (blurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
            blurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
            styleOption.blurStyle = static_cast<BlurStyle>(blurStyle);
        }
    }
    if (info.Length() > 1 && info[1]->IsObject()) {
        JSRef<JSObject> jsOption = JSRef<JSObject>::Cast(info[1]);
        auto colorMode = static_cast<int32_t>(ThemeColorMode::SYSTEM);
        ParseJsInt32(jsOption->GetProperty("colorMode"), colorMode);
        if (colorMode >= static_cast<int32_t>(ThemeColorMode::SYSTEM) &&
            colorMode <= static_cast<int32_t>(ThemeColorMode::DARK)) {
            styleOption.colorMode = static_cast<ThemeColorMode>(colorMode);
        }
        auto adaptiveColor = static_cast<int32_t>(AdaptiveColor::DEFAULT);
        ParseJsInt32(jsOption->GetProperty("adaptiveColor"), adaptiveColor);
        if (adaptiveColor >= static_cast<int32_t>(AdaptiveColor::DEFAULT) &&
            adaptiveColor <= static_cast<int32_t>(AdaptiveColor::AVERAGE)) {
            styleOption.adaptiveColor = static_cast<AdaptiveColor>(adaptiveColor);
        }
        if (jsOption->GetProperty("scale")->IsNumber()) {
            double scale = jsOption->GetProperty("scale")->ToNumber<double>();
            styleOption.scale = std::clamp(scale, 0.0, 1.0);
        }

        if (jsOption->GetProperty("blurOptions")->IsObject()) {
            JSRef<JSObject> jsBlurOption = JSRef<JSObject>::Cast(jsOption->GetProperty("blurOptions"));
            BlurOption blurOption;
            ParseBlurOption(jsBlurOption, blurOption);
            styleOption.blurOption = blurOption;
        }
    }
    ViewAbstractModel::GetInstance()->SetForegroundBlurStyle(styleOption);
}

void JSViewAbstract::JsSphericalEffect(const JSCallbackInfo& info)
{
    auto radio = 0.0;
    if (info[0]->IsNumber()) {
        radio = info[0]->ToNumber<double>();
    }
    ViewAbstractModel::GetInstance()->SetSphericalEffect(std::clamp(radio, 0.0, 1.0));
}

void JSViewAbstract::JsPixelStretchEffect(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        PixStretchEffectOption option;
        option.ResetValue();
        ViewAbstractModel::GetInstance()->SetPixelStretchEffect(option);
        return;
    }
    auto jsObject = JSRef<JSObject>::Cast(info[0]);
    CalcDimension left;
    ParseJsDimensionVp(jsObject->GetProperty("left"), left);
    CalcDimension right;
    ParseJsDimensionVp(jsObject->GetProperty("right"), right);
    CalcDimension top;
    ParseJsDimensionVp(jsObject->GetProperty("top"), top);
    CalcDimension bottom;
    ParseJsDimensionVp(jsObject->GetProperty("bottom"), bottom);

    PixStretchEffectOption option;
    bool illegalInput = false;
    if (left.Unit() == DimensionUnit::PERCENT || right.Unit() == DimensionUnit::PERCENT ||
        top.Unit() == DimensionUnit::PERCENT || bottom.Unit() == DimensionUnit::PERCENT) {
        if ((NearEqual(left.Value(), 0.0) || left.Unit() == DimensionUnit::PERCENT) &&
            (NearEqual(top.Value(), 0.0) || top.Unit() == DimensionUnit::PERCENT) &&
            (NearEqual(right.Value(), 0.0) || right.Unit() == DimensionUnit::PERCENT) &&
            (NearEqual(bottom.Value(), 0.0) || bottom.Unit() == DimensionUnit::PERCENT)) {
            left.SetUnit(DimensionUnit::PERCENT);
            top.SetUnit(DimensionUnit::PERCENT);
            right.SetUnit(DimensionUnit::PERCENT);
            bottom.SetUnit(DimensionUnit::PERCENT);
        } else {
            illegalInput = true;
        }
    }
    if ((left.IsNonNegative() && top.IsNonNegative() && right.IsNonNegative() && bottom.IsNonNegative()) ||
        (left.IsNonPositive() && top.IsNonPositive() && right.IsNonPositive() && bottom.IsNonPositive())) {
        option.left = left;
        option.top = top;
        option.right = right;
        option.bottom = bottom;
    } else {
        illegalInput = true;
    }
    if (illegalInput) {
        option.ResetValue();
    }
    ViewAbstractModel::GetInstance()->SetPixelStretchEffect(option);
}

void JSViewAbstract::JsLightUpEffect(const JSCallbackInfo& info)
{
    auto radio = 1.0;
    if (info[0]->IsNumber()) {
        radio = info[0]->ToNumber<double>();
    }
    ViewAbstractModel::GetInstance()->SetLightUpEffect(std::clamp(radio, 0.0, 1.0));
}

void JSViewAbstract::JsBackgroundImageSize(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::NUMBER, JSCallbackInfoType::OBJECT };
    BackgroundImageSize bgImgSize;
    if (!CheckJSCallbackInfo("JsBackgroundImageSize", info, checkList)) {
        bgImgSize.SetSizeTypeX(BackgroundImageSizeType::AUTO);
        bgImgSize.SetSizeTypeY(BackgroundImageSizeType::AUTO);
        ViewAbstractModel::GetInstance()->SetBackgroundImageSize(bgImgSize);
        return;
    }
    if (info[0]->IsNumber()) {
        auto sizeType = static_cast<BackgroundImageSizeType>(info[0]->ToNumber<int32_t>());
        bgImgSize.SetSizeTypeX(sizeType);
        bgImgSize.SetSizeTypeY(sizeType);
    } else {
        CalcDimension width;
        CalcDimension height;
        JSRef<JSObject> object = JSRef<JSObject>::Cast(info[0]);
        ParseJsDimensionVp(object->GetProperty("width"), width);
        ParseJsDimensionVp(object->GetProperty("height"), height);
        double valueWidth = width.ConvertToPx();
        double valueHeight = height.ConvertToPx();
        BackgroundImageSizeType typeWidth = BackgroundImageSizeType::LENGTH;
        BackgroundImageSizeType typeHeight = BackgroundImageSizeType::LENGTH;
        if (width.Unit() == DimensionUnit::PERCENT) {
            typeWidth = BackgroundImageSizeType::PERCENT;
            valueWidth = width.Value() * FULL_DIMENSION;
        }
        if (height.Unit() == DimensionUnit::PERCENT) {
            typeHeight = BackgroundImageSizeType::PERCENT;
            valueHeight = height.Value() * FULL_DIMENSION;
        }
        bgImgSize.SetSizeTypeX(typeWidth);
        bgImgSize.SetSizeValueX(valueWidth);
        bgImgSize.SetSizeTypeY(typeHeight);
        bgImgSize.SetSizeValueY(valueHeight);
    }

    ViewAbstractModel::GetInstance()->SetBackgroundImageSize(bgImgSize);
}

void JSViewAbstract::JsBackgroundImagePosition(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::NUMBER, JSCallbackInfoType::OBJECT };
    BackgroundImagePosition bgImgPosition;
    if (!CheckJSCallbackInfo("JsBackgroundImagePosition", info, checkList)) {
        SetBgImgPosition(DimensionUnit::PX, DimensionUnit::PX, 0.0, 0.0, bgImgPosition);
        ViewAbstractModel::GetInstance()->SetBackgroundImagePosition(bgImgPosition);
        return;
    }
    if (info[0]->IsNumber()) {
        int32_t align = info[0]->ToNumber<int32_t>();
        bgImgPosition.SetIsAlign(true);
        switch (align) {
            case 0:
                SetBgImgPosition(DimensionUnit::PERCENT, DimensionUnit::PERCENT, 0.0, 0.0, bgImgPosition);
                break;
            case 1:
                SetBgImgPosition(DimensionUnit::PERCENT, DimensionUnit::PERCENT, HALF_DIMENSION, 0.0, bgImgPosition);
                break;
            case 2:
                SetBgImgPosition(DimensionUnit::PERCENT, DimensionUnit::PERCENT, FULL_DIMENSION, 0.0, bgImgPosition);
                break;
            case 3:
                SetBgImgPosition(DimensionUnit::PERCENT, DimensionUnit::PERCENT, 0.0, HALF_DIMENSION, bgImgPosition);
                break;
            case 4:
                SetBgImgPosition(
                    DimensionUnit::PERCENT, DimensionUnit::PERCENT, HALF_DIMENSION, HALF_DIMENSION, bgImgPosition);
                break;
            case 5:
                SetBgImgPosition(
                    DimensionUnit::PERCENT, DimensionUnit::PERCENT, FULL_DIMENSION, HALF_DIMENSION, bgImgPosition);
                break;
            case 6:
                SetBgImgPosition(DimensionUnit::PERCENT, DimensionUnit::PERCENT, 0.0, FULL_DIMENSION, bgImgPosition);
                break;
            case 7:
                SetBgImgPosition(
                    DimensionUnit::PERCENT, DimensionUnit::PERCENT, HALF_DIMENSION, FULL_DIMENSION, bgImgPosition);
                break;
            case 8:
                SetBgImgPosition(
                    DimensionUnit::PERCENT, DimensionUnit::PERCENT, FULL_DIMENSION, FULL_DIMENSION, bgImgPosition);
                break;
            default:
                break;
        }
    } else {
        CalcDimension x;
        CalcDimension y;
        JSRef<JSObject> object = JSRef<JSObject>::Cast(info[0]);
        ParseJsDimensionVp(object->GetProperty("x"), x);
        ParseJsDimensionVp(object->GetProperty("y"), y);
        double valueX = x.Value();
        double valueY = y.Value();
        DimensionUnit typeX = DimensionUnit::PX;
        DimensionUnit typeY = DimensionUnit::PX;
        if (x.Unit() == DimensionUnit::PERCENT) {
            valueX = x.Value();
            typeX = DimensionUnit::PERCENT;
        }
        if (y.Unit() == DimensionUnit::PERCENT) {
            valueY = y.Value();
            typeY = DimensionUnit::PERCENT;
        }
        SetBgImgPosition(typeX, typeY, valueX, valueY, bgImgPosition);
    }

    ViewAbstractModel::GetInstance()->SetBackgroundImagePosition(bgImgPosition);
}

std::vector<NG::OptionParam> ParseBindOptionParam(const JSCallbackInfo& info, size_t optionIndex)
{
    auto paramArray = JSRef<JSArray>::Cast(info[optionIndex]);
    std::vector<NG::OptionParam> params(paramArray->Length());
    // parse paramArray
    for (size_t i = 0; i < paramArray->Length(); ++i) {
        auto indexObject = JSRef<JSObject>::Cast(paramArray->GetValueAt(i));
        JSViewAbstract::ParseJsString(indexObject->GetProperty("value"), params[i].value);
        auto actionFunc = indexObject->GetProperty("action");
        if (!actionFunc->IsFunction()) {
            return params;
        }
        auto action = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(actionFunc));
        WeakPtr<NG::FrameNode> targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
        // set onClick function
        params[i].action = [func = std::move(action), context = info.GetExecutionContext(), node = targetNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(context);
            ACE_SCORING_EVENT("menu.action");
            PipelineContext::SetCallBackNode(node);
            if (func) {
                func->Execute();
            }
        };
        std::string iconPath;
        if (JSViewAbstract::ParseJsMedia(indexObject->GetProperty("icon"), iconPath)) {
            params[i].icon = iconPath;
        }
        auto enabled = indexObject->GetProperty("enabled");
        if (enabled->IsBoolean()) {
            params[i].enabled = enabled->ToBoolean();
        }
    }
    return params;
}

void ParseMenuArrowParam(const JSRef<JSObject>& menuOptions, NG::MenuParam& menuParam)
{
    auto enableArrowValue = menuOptions->GetProperty("enableArrow");
    if (enableArrowValue->IsBoolean()) {
        menuParam.enableArrow = enableArrowValue->ToBoolean();
    }

    auto arrowOffset = menuOptions->GetProperty("arrowOffset");
    CalcDimension offset;
    if (JSViewAbstract::ParseJsDimensionVp(arrowOffset, offset)) {
        menuParam.arrowOffset = offset;
    }

    // if enableArrow is true and placement not set, set placement default value to top.
    if (menuParam.enableArrow.has_value() && !menuParam.placement.has_value() && menuParam.enableArrow.value()) {
        menuParam.placement = Placement::TOP;
    }
}

void ParseMenuParam(const JSCallbackInfo& info, const JSRef<JSObject>& menuOptions, NG::MenuParam& menuParam)
{
    auto offsetVal = menuOptions->GetProperty("offset");
    if (offsetVal->IsObject()) {
        auto offsetObj = JSRef<JSObject>::Cast(offsetVal);
        JSRef<JSVal> xVal = offsetObj->GetProperty("x");
        JSRef<JSVal> yVal = offsetObj->GetProperty("y");
        CalcDimension dx;
        CalcDimension dy;
        if (JSViewAbstract::ParseJsDimensionVp(xVal, dx)) {
            menuParam.positionOffset.SetX(dx.ConvertToPx());
        }
        if (JSViewAbstract::ParseJsDimensionVp(yVal, dy)) {
            menuParam.positionOffset.SetY(dy.ConvertToPx());
        }
    }

    auto placementValue = menuOptions->GetProperty("placement");
    if (placementValue->IsNumber()) {
        auto placement = placementValue->ToNumber<int32_t>();
        if (placement >= 0 && placement < static_cast<int32_t>(PLACEMENT.size())) {
            menuParam.placement = PLACEMENT[placement];
        }
    }
    
    auto backgroundColorValue = menuOptions->GetProperty("backgroundColor");
    Color backgroundColor;
    if (JSViewAbstract::ParseJsColor(backgroundColorValue, backgroundColor)) {
        menuParam.backgroundColor = backgroundColor;
    }

    auto backgroundBlurStyle = menuOptions->GetProperty("backgroundBlurStyle");
    BlurStyleOption styleOption;
    if (backgroundBlurStyle->IsNumber()) {
        auto blurStyle = backgroundBlurStyle->ToNumber<int32_t>();
        if (blurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
            blurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
            menuParam.backgroundBlurStyle = blurStyle;
        }
    }
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto onAppearValue = menuOptions->GetProperty("onAppear");
    if (onAppearValue->IsFunction()) {
        RefPtr<JsFunction> jsOnAppearFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onAppearValue));
        auto onAppear = [execCtx = info.GetExecutionContext(), func = std::move(jsOnAppearFunc), node = frameNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("onAppear");
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
        menuParam.onAppear = std::move(onAppear);
    }

    auto onDisappearValue = menuOptions->GetProperty("onDisappear");
    if (onDisappearValue->IsFunction()) {
        RefPtr<JsFunction> jsOnDisAppearFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onDisappearValue));
        auto onDisappear = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDisAppearFunc),
                               node = frameNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("onDisappear");
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
        menuParam.onDisappear = std::move(onDisappear);
    }
    auto aboutToAppearValue = menuOptions->GetProperty("aboutToAppear");
    if (aboutToAppearValue->IsFunction()) {
        RefPtr<JsFunction> jsAboutToAppearFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(aboutToAppearValue));
        auto aboutToAppear = [execCtx = info.GetExecutionContext(), func = std::move(jsAboutToAppearFunc),
                            node = frameNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("aboutToAppear");
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
        menuParam.aboutToAppear = std::move(aboutToAppear);
    }

    auto aboutToDisAppearValue = menuOptions->GetProperty("aboutToDisappear");
    if (aboutToDisAppearValue->IsFunction()) {
        RefPtr<JsFunction> jsAboutToDisAppearFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(aboutToDisAppearValue));
        auto aboutToDisappear = [execCtx = info.GetExecutionContext(), func = std::move(jsAboutToDisAppearFunc),
                               node = frameNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("aboutToDisappear");
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
        menuParam.aboutToDisappear = std::move(aboutToDisappear);
    }
    ParseMenuArrowParam(menuOptions, menuParam);
}

void ParseBindOptionParam(const JSCallbackInfo& info, NG::MenuParam& menuParam, size_t optionIndex)
{
    auto menuOptions = JSRef<JSObject>::Cast(info[optionIndex]);
    JSViewAbstract::ParseJsString(menuOptions->GetProperty("title"), menuParam.title);
    ParseMenuParam(info, menuOptions, menuParam);
}

void ParseAnimationScaleArray(const JSRef<JSArray>& scaleArray, NG::MenuParam& menuParam)
{
    constexpr int scaleArraySize = 2;
    if (scaleArray->Length() == scaleArraySize) {
        auto scalePropertyFrom = scaleArray->GetValueAt(0);
        if (scalePropertyFrom->IsNumber()) {
            auto scaleFrom = scalePropertyFrom->ToNumber<float>();
            menuParam.previewAnimationOptions.scaleFrom = LessOrEqual(scaleFrom, 0.0) ? -1.0f : scaleFrom;
        }
        auto scalePropertyTo = scaleArray->GetValueAt(1);
        if (scalePropertyTo->IsNumber()) {
            auto scaleTo = scalePropertyTo->ToNumber<float>();
            menuParam.previewAnimationOptions.scaleTo = LessOrEqual(scaleTo, 0.0) ? -1.0f : scaleTo;
        }
    }
}

void ParseContentPreviewAnimationOptionsParam(const JSRef<JSObject>& menuContentOptions, NG::MenuParam& menuParam)
{
    menuParam.previewAnimationOptions.scaleFrom = -1.0f;
    menuParam.previewAnimationOptions.scaleTo = -1.0f;

    auto animationOptions = menuContentOptions->GetProperty("previewAnimationOptions");
    if (!animationOptions->IsEmpty() && animationOptions->IsObject()) {
        auto animationOptionsObj = JSRef<JSObject>::Cast(animationOptions);
        auto scaleProperty = animationOptionsObj->GetProperty("scale");
        if (!scaleProperty->IsEmpty() && scaleProperty->IsArray()) {
            JSRef<JSArray> scaleArray = JSRef<JSArray>::Cast(scaleProperty);
            ParseAnimationScaleArray(scaleArray, menuParam);
        }
    }
}

void ParseBindContentOptionParam(const JSCallbackInfo& info, const JSRef<JSVal>& args, NG::MenuParam& menuParam,
    std::function<void()>& previewBuildFunc)
{
    auto menuContentOptions = JSRef<JSObject>::Cast(args);
    ParseMenuParam(info, menuContentOptions, menuParam);
    RefPtr<JsFunction> previewBuilderFunc;
    auto preview = menuContentOptions->GetProperty("preview");
    if (!preview->IsFunction() && !preview->IsNumber()) {
        return;
    }

    if (preview->IsNumber()) {
        if (preview->ToNumber<int32_t>() == 1) {
            menuParam.previewMode = MenuPreviewMode::IMAGE;
            ParseContentPreviewAnimationOptionsParam(menuContentOptions, menuParam);
        }
    } else {
        previewBuilderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(preview));
        CHECK_NULL_VOID(previewBuilderFunc);
        WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
        previewBuildFunc = [execCtx = info.GetExecutionContext(), func = std::move(previewBuilderFunc),
                               node = frameNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("BuildContextMenuPreviwer");
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
        menuParam.previewMode = MenuPreviewMode::CUSTOM;
    }
}

void JSViewAbstract::JsBindMenu(const JSCallbackInfo& info)
{
    NG::MenuParam menuParam;
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        menuParam.placement = Placement::BOTTOM_LEFT;
    }
    size_t builderIndex = 0;
    if (info.Length() > PARAMETER_LENGTH_FIRST) {
        if (info[0]->IsBoolean()) {
            menuParam.isShow = info[0]->ToBoolean();
            menuParam.setShow = true;
            builderIndex = 1;
            if (info.Length() > PARAMETER_LENGTH_SECOND) {
                ParseBindOptionParam(info, menuParam, builderIndex + 1);
            }
        } else if (info[0]->IsUndefined()) {
            menuParam.setShow = true;
            menuParam.isShow = false;
            builderIndex = 1;
            if (info.Length() > PARAMETER_LENGTH_SECOND) {
                ParseBindOptionParam(info, menuParam, builderIndex + 1);
            }
        } else {
            JSRef<JSObject> callbackObj = JSRef<JSObject>::Cast(info[0]);
            menuParam.onStateChange = ParseDoubleBindCallback(info, callbackObj);
            auto isShowObj = callbackObj->GetProperty("value");
            if (isShowObj->IsBoolean()) {
                menuParam.isShow = isShowObj->ToBoolean();
                menuParam.setShow = true;
                builderIndex = 1;
                if (info.Length() > PARAMETER_LENGTH_SECOND) {
                    ParseBindOptionParam(info, menuParam, builderIndex + 1);
                }
            } else {
                builderIndex = 0;
                ParseBindOptionParam(info, menuParam, builderIndex + 1);
            }
        }
    }

    if (info[builderIndex]->IsArray()) {
        std::vector<NG::OptionParam> optionsParam = ParseBindOptionParam(info, builderIndex);
        ViewAbstractModel::GetInstance()->BindMenu(std::move(optionsParam), nullptr, menuParam);
    } else if (info[builderIndex]->IsObject()) {
        // CustomBuilder
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[builderIndex]);
        auto builder = obj->GetProperty("builder");
        if (!builder->IsFunction()) {
            return;
        }
        auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(builder));

        WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
        CHECK_NULL_VOID(builderFunc);
        auto buildFunc = [execCtx = info.GetExecutionContext(), func = std::move(builderFunc), node = frameNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("BuildMenu");
            WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
            func->Execute();
        };
        ViewAbstractModel::GetInstance()->BindMenu({}, std::move(buildFunc), menuParam);
    }
}

void JSViewAbstract::JsPadding(const JSCallbackInfo& info)
{
    ParseMarginOrPadding(info, false);
}

void JSViewAbstract::JsMargin(const JSCallbackInfo& info)
{
    ParseMarginOrPadding(info, true);
}

void JSViewAbstract::ParseMarginOrPadding(const JSCallbackInfo& info, bool isMargin)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::OBJECT, JSCallbackInfoType::STRING,
        JSCallbackInfoType::NUMBER };
    if (!CheckJSCallbackInfo("MarginOrPadding", info, checkList)) {
        auto resetDimension = CalcDimension(0.0);
        if (isMargin) {
            ViewAbstractModel::GetInstance()->SetMargin(resetDimension);
        } else {
            ViewAbstractModel::GetInstance()->SetPadding(resetDimension);
        }
        return;
    }
    auto tmpInfo = info[0];
    if (tmpInfo->IsObject()) {
        std::optional<CalcDimension> left;
        std::optional<CalcDimension> right;
        std::optional<CalcDimension> top;
        std::optional<CalcDimension> bottom;
        JSRef<JSObject> paddingObj = JSRef<JSObject>::Cast(tmpInfo);
        ParseMarginOrPaddingCorner(paddingObj, top, bottom, left, right);
        if (left.has_value() || right.has_value() || top.has_value() || bottom.has_value()) {
            if (isMargin) {
                ViewAbstractModel::GetInstance()->SetMargins(top, bottom, left, right);
            } else {
                ViewAbstractModel::GetInstance()->SetPaddings(top, bottom, left, right);
            }
            return;
        }
    }

    CalcDimension length;
    if (!ParseJsDimensionVp(tmpInfo, length)) {
        // use default value.
        length.Reset();
    }
    if (isMargin) {
        ViewAbstractModel::GetInstance()->SetMargin(length);
    } else {
        ViewAbstractModel::GetInstance()->SetPadding(length);
    }
}

void JSViewAbstract::ParseMarginOrPaddingCorner(JSRef<JSObject> obj, std::optional<CalcDimension>& top,
    std::optional<CalcDimension>& bottom, std::optional<CalcDimension>& left, std::optional<CalcDimension>& right)
{
    CalcDimension leftDimen;
    if (ParseJsDimensionVp(obj->GetProperty("left"), leftDimen)) {
        left = leftDimen;
    }
    CalcDimension rightDimen;
    if (ParseJsDimensionVp(obj->GetProperty("right"), rightDimen)) {
        right = rightDimen;
    }
    CalcDimension topDimen;
    if (ParseJsDimensionVp(obj->GetProperty("top"), topDimen)) {
        top = topDimen;
    }
    CalcDimension bottomDimen;
    if (ParseJsDimensionVp(obj->GetProperty("bottom"), bottomDimen)) {
        bottom = bottomDimen;
    }
}

void JSViewAbstract::JsOutline(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::OBJECT };
    if (!CheckJSCallbackInfo("JsOutline", info, checkList)) {
        CalcDimension borderWidth;
        ViewAbstractModel::GetInstance()->SetOuterBorderWidth(borderWidth);
        ViewAbstractModel::GetInstance()->SetOuterBorderColor(Color::BLACK);
        ViewAbstractModel::GetInstance()->SetOuterBorderRadius(borderWidth);
        ViewAbstractModel::GetInstance()->SetOuterBorderStyle(BorderStyle::SOLID);
        return;
    }
    JSRef<JSObject> object = JSRef<JSObject>::Cast(info[0]);
    auto valueOuterWidth = object->GetProperty("width");
    if (!valueOuterWidth->IsUndefined()) {
        ParseOuterBorderWidth(valueOuterWidth);
    }

    // use default value when undefined.
    ParseOuterBorderColor(object->GetProperty("color"));

    auto valueOuterRadius = object->GetProperty("radius");
    if (!valueOuterRadius->IsUndefined()) {
        ParseOuterBorderRadius(valueOuterRadius);
    }
    // use default value when undefined.
    ParseOuterBorderStyle(object->GetProperty("style"));
    info.ReturnSelf();
}

void JSViewAbstract::JsOutlineWidth(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::STRING, JSCallbackInfoType::NUMBER,
        JSCallbackInfoType::OBJECT };
    if (!CheckJSCallbackInfo("JsOutlineWidth", info, checkList)) {
        ViewAbstractModel::GetInstance()->SetOuterBorderWidth({});
        return;
    }
    ParseOuterBorderWidth(info[0]);
}

void JSViewAbstract::JsOutlineColor(const JSCallbackInfo& info)
{
    ParseOuterBorderColor(info[0]);
}

void JSViewAbstract::JsOutlineRadius(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::STRING, JSCallbackInfoType::NUMBER,
        JSCallbackInfoType::OBJECT };
    if (!CheckJSCallbackInfo("JsOutlineRadius", info, checkList)) {
        ViewAbstractModel::GetInstance()->SetOuterBorderRadius({});
        return;
    }
    ParseOuterBorderRadius(info[0]);
}

void JSViewAbstract::JsOutlineStyle(const JSCallbackInfo& info)
{
    ParseOuterBorderStyle(info[0]);
}

void JSViewAbstract::JsBorder(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::OBJECT };
    if (!CheckJSCallbackInfo("JsBorder", info, checkList)) {
        CalcDimension borderWidth;
        ViewAbstractModel::GetInstance()->SetBorderWidth(borderWidth);
        ViewAbstractModel::GetInstance()->SetBorderColor(Color::BLACK);
        ViewAbstractModel::GetInstance()->SetBorderRadius(borderWidth);
        ViewAbstractModel::GetInstance()->SetBorderStyle(BorderStyle::SOLID);
        return;
    }
    JSRef<JSObject> object = JSRef<JSObject>::Cast(info[0]);

    auto valueWidth = object->GetProperty("width");
    if (!valueWidth->IsUndefined()) {
        ParseBorderWidth(valueWidth);
    }

    // use default value when undefined.
    ParseBorderColor(object->GetProperty("color"));

    auto valueRadius = object->GetProperty("radius");
    if (!valueRadius->IsUndefined()) {
        ParseBorderRadius(valueRadius);
    }
    // use default value when undefined.
    ParseBorderStyle(object->GetProperty("style"));

    info.ReturnSelf();
}

void JSViewAbstract::JsBorderWidth(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::STRING, JSCallbackInfoType::NUMBER,
        JSCallbackInfoType::OBJECT };
    if (!CheckJSCallbackInfo("JsBorderWidth", info, checkList)) {
        ViewAbstractModel::GetInstance()->SetBorderWidth({});
        return;
    }
    ParseBorderWidth(info[0]);
}

void JSViewAbstract::ParseBorderWidth(const JSRef<JSVal>& args)
{
    if (!args->IsObject() && !args->IsNumber() && !args->IsString()) {
        return;
    }
    std::optional<CalcDimension> leftDimen;
    std::optional<CalcDimension> rightDimen;
    std::optional<CalcDimension> topDimen;
    std::optional<CalcDimension> bottomDimen;
    CalcDimension borderWidth;
    if (ParseJsDimensionVp(args, borderWidth)) {
        if (borderWidth.IsNegative()) {
            borderWidth.Reset();
        }
        if (borderWidth.Unit() == DimensionUnit::PERCENT) {
            borderWidth.Reset();
        }
        ViewAbstractModel::GetInstance()->SetBorderWidth(borderWidth);
    } else if (args->IsObject()) {
        JSRef<JSObject> object = JSRef<JSObject>::Cast(args);
        CalcDimension left;
        if (ParseJsDimensionVp(object->GetProperty("left"), left) && left.IsNonNegative()) {
            if (left.Unit() == DimensionUnit::PERCENT) {
                left.Reset();
            }
            leftDimen = left;
        }
        CalcDimension right;
        if (ParseJsDimensionVp(object->GetProperty("right"), right) && right.IsNonNegative()) {
            if (right.Unit() == DimensionUnit::PERCENT) {
                right.Reset();
            }
            rightDimen = right;
        }
        CalcDimension top;
        if (ParseJsDimensionVp(object->GetProperty("top"), top) && top.IsNonNegative()) {
            if (top.Unit() == DimensionUnit::PERCENT) {
                top.Reset();
            }
            topDimen = top;
        }
        CalcDimension bottom;
        if (ParseJsDimensionVp(object->GetProperty("bottom"), bottom) && bottom.IsNonNegative()) {
            if (bottom.Unit() == DimensionUnit::PERCENT) {
                bottom.Reset();
            }
            bottomDimen = bottom;
        }
        ViewAbstractModel::GetInstance()->SetBorderWidth(leftDimen, rightDimen, topDimen, bottomDimen);
    } else {
        return;
    }
}

void JSViewAbstract::ParseOuterBorderWidth(const JSRef<JSVal>& args)
{
    if (!args->IsObject() && !args->IsNumber() && !args->IsString()) {
        return;
    }
    std::optional<CalcDimension> leftDimen;
    std::optional<CalcDimension> rightDimen;
    std::optional<CalcDimension> topDimen;
    std::optional<CalcDimension> bottomDimen;
    CalcDimension borderWidth;
    if (ParseJsDimensionVp(args, borderWidth)) {
        if (borderWidth.IsNegative() || borderWidth.Unit() == DimensionUnit::PERCENT) {
            borderWidth.Reset();
        }
        ViewAbstractModel::GetInstance()->SetOuterBorderWidth(borderWidth);
    } else if (args->IsObject()) {
        JSRef<JSObject> object = JSRef<JSObject>::Cast(args);
        CalcDimension left;
        if (ParseJsDimensionVp(object->GetProperty("left"), left) && left.IsNonNegative()) {
            if (left.Unit() == DimensionUnit::PERCENT) {
                left.Reset();
            }
            leftDimen = left;
        }
        CalcDimension right;
        if (ParseJsDimensionVp(object->GetProperty("right"), right) && right.IsNonNegative()) {
            if (right.Unit() == DimensionUnit::PERCENT) {
                right.Reset();
            }
            rightDimen = right;
        }
        CalcDimension top;
        if (ParseJsDimensionVp(object->GetProperty("top"), top) && top.IsNonNegative()) {
            if (top.Unit() == DimensionUnit::PERCENT) {
                top.Reset();
            }
            topDimen = top;
        }
        CalcDimension bottom;
        if (ParseJsDimensionVp(object->GetProperty("bottom"), bottom) && bottom.IsNonNegative()) {
            if (bottom.Unit() == DimensionUnit::PERCENT) {
                bottom.Reset();
            }
            bottomDimen = bottom;
        }
        ViewAbstractModel::GetInstance()->SetOuterBorderWidth(leftDimen, rightDimen, topDimen, bottomDimen);
    } else {
        return;
    }
}

void JSViewAbstract::ParseMenuOptions(
    const JSCallbackInfo& info, const JSRef<JSArray>& jsArray, std::vector<NG::MenuOptionsParam>& items)
{
    auto length = jsArray->Length();
    for (size_t i = 0; i < length; i++) {
        auto item = jsArray->GetValueAt(i);
        if (!item->IsObject()) {
            continue;
        }
        auto itemObject = JSRef<JSObject>::Cast(item);
        NG::MenuOptionsParam menuOptionItem;
        std::string value;
        std::string icon;
        auto menuOptionsValue = itemObject->GetProperty("content");
        auto menuOptionsIcon = itemObject->GetProperty("icon");

        if (!ParseJsString(menuOptionsValue, value)) {
            return;
        }
        ParseJsMedia(menuOptionsIcon, icon);
        menuOptionItem.content = value;
        menuOptionItem.icon = icon;

        auto itemActionValue = itemObject->GetProperty("action");
        if (itemActionValue->IsFunction()) {
            JsEventCallback<void(const std::string&)> callback(
                info.GetExecutionContext(), JSRef<JSFunc>::Cast(itemActionValue));
            menuOptionItem.action = callback;
        }
        items.emplace_back(menuOptionItem);
    }
}

void JSViewAbstract::JsBorderImage(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::OBJECT };
    if (!CheckJSCallbackInfo("JsBorderImage", info, checkList)) {
        RefPtr<BorderImage> borderImage = AceType::MakeRefPtr<BorderImage>();
        uint8_t imageBorderBitsets = 0;
        ViewAbstractModel::GetInstance()->SetBorderImage(borderImage, imageBorderBitsets);
        return;
    }
    JSRef<JSObject> object = JSRef<JSObject>::Cast(info[0]);
    if (object->IsEmpty()) {
        return;
    }

    RefPtr<BorderImage> borderImage = AceType::MakeRefPtr<BorderImage>();
    uint8_t imageBorderBitsets = 0;

    auto valueSource = object->GetProperty("source");
    if (!valueSource->IsString() && !valueSource->IsObject()) {
        return;
    }
    std::string srcResult;
    if (valueSource->IsString()) {
        srcResult = valueSource->ToString();
        if (!srcResult.empty()) {
            borderImage->SetSrc(srcResult);
            imageBorderBitsets |= BorderImage::SOURCE_BIT;
        }
    } else if (valueSource->IsObject()) {
        if (ParseJsMedia(valueSource, srcResult)) {
            borderImage->SetSrc(srcResult);
            imageBorderBitsets |= BorderImage::SOURCE_BIT;
        } else {
            ParseBorderImageLinearGradient(valueSource, imageBorderBitsets);
        }
    }
    auto valueOutset = object->GetProperty("outset");
    if (valueOutset->IsNumber() || valueOutset->IsString() || valueOutset->IsObject()) {
        imageBorderBitsets |= BorderImage::OUTSET_BIT;
        ParseBorderImageOutset(valueOutset, borderImage);
    }
    auto valueRepeat = object->GetProperty("repeat");
    if (!valueRepeat->IsNull()) {
        imageBorderBitsets |= BorderImage::REPEAT_BIT;
        ParseBorderImageRepeat(valueRepeat, borderImage);
    }
    auto valueSlice = object->GetProperty("slice");
    if (valueSlice->IsNumber() || valueSlice->IsString() || valueSlice->IsObject()) {
        imageBorderBitsets |= BorderImage::SLICE_BIT;
        ParseBorderImageSlice(valueSlice, borderImage);
    }
    auto valueWidth = object->GetProperty("width");
    if (valueWidth->IsNumber() || valueWidth->IsString() || valueWidth->IsObject()) {
        imageBorderBitsets |= BorderImage::WIDTH_BIT;
        ParseBorderImageWidth(valueWidth, borderImage);
    }
    auto needFill = object->GetProperty("fill");
    if (needFill->IsBoolean()) {
        borderImage->SetNeedFillCenter(needFill->ToBoolean());
    }
    ViewAbstractModel::GetInstance()->SetBorderImage(borderImage, imageBorderBitsets);
    info.ReturnSelf();
}

void JSViewAbstract::ParseBorderImageDimension(
    const JSRef<JSVal>& args, BorderImage::BorderImageOption& borderImageDimension)
{
    JSRef<JSObject> object = JSRef<JSObject>::Cast(args);
    static std::array<std::string, 4> keys = { "left", "right", "top", "bottom" };
    for (uint32_t i = 0; i < keys.size(); i++) {
        CalcDimension currentDimension;
        auto dimensionValue = object->GetProperty(keys.at(i).c_str());
        if (ParseJsDimensionVp(dimensionValue, currentDimension)) {
            auto direction = static_cast<BorderImageDirection>(i);
            switch (direction) {
                case BorderImageDirection::LEFT:
                    borderImageDimension.leftDimension = currentDimension;
                    break;
                case BorderImageDirection::RIGHT:
                    borderImageDimension.rightDimension = currentDimension;
                    break;
                case BorderImageDirection::TOP:
                    borderImageDimension.topDimension = currentDimension;
                    break;
                case BorderImageDirection::BOTTOM:
                    borderImageDimension.bottomDimension = currentDimension;
                    break;
                default:
                    break;
            }
        }
    }
}

void JSViewAbstract::ParseBorderImageLinearGradient(const JSRef<JSVal>& args, uint8_t& bitset)
{
    if (!args->IsObject()) {
        return;
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(args);
    NG::Gradient lineGradient;
    lineGradient.CreateGradientWithType(NG::GradientType::LINEAR);
    // angle
    std::optional<float> degree;
    GetJsAngle("angle", jsObj, degree);
    if (degree) {
        lineGradient.GetLinearGradient()->angle = CalcDimension(degree.value(), DimensionUnit::PX);
        degree.reset();
    }
    // direction
    auto direction = static_cast<NG::GradientDirection>(
        jsObj->GetPropertyValue<int32_t>("direction", static_cast<int32_t>(NG::GradientDirection::NONE)));
    switch (direction) {
        case NG::GradientDirection::LEFT:
            lineGradient.GetLinearGradient()->linearX = NG::GradientDirection::LEFT;
            break;
        case NG::GradientDirection::RIGHT:
            lineGradient.GetLinearGradient()->linearX = NG::GradientDirection::RIGHT;
            break;
        case NG::GradientDirection::TOP:
            lineGradient.GetLinearGradient()->linearY = NG::GradientDirection::TOP;
            break;
        case NG::GradientDirection::BOTTOM:
            lineGradient.GetLinearGradient()->linearY = NG::GradientDirection::BOTTOM;
            break;
        case NG::GradientDirection::LEFT_TOP:
            lineGradient.GetLinearGradient()->linearX = NG::GradientDirection::LEFT;
            lineGradient.GetLinearGradient()->linearY = NG::GradientDirection::TOP;
            break;
        case NG::GradientDirection::LEFT_BOTTOM:
            lineGradient.GetLinearGradient()->linearX = NG::GradientDirection::LEFT;
            lineGradient.GetLinearGradient()->linearY = NG::GradientDirection::BOTTOM;
            break;
        case NG::GradientDirection::RIGHT_TOP:
            lineGradient.GetLinearGradient()->linearX = NG::GradientDirection::RIGHT;
            lineGradient.GetLinearGradient()->linearY = NG::GradientDirection::TOP;
            break;
        case NG::GradientDirection::RIGHT_BOTTOM:
            lineGradient.GetLinearGradient()->linearX = NG::GradientDirection::RIGHT;
            lineGradient.GetLinearGradient()->linearY = NG::GradientDirection::BOTTOM;
            break;
        case NG::GradientDirection::NONE:
        case NG::GradientDirection::START_TO_END:
        case NG::GradientDirection::END_TO_START:
        default:
            break;
    }
    auto repeating = jsObj->GetPropertyValue<bool>("repeating", false);
    lineGradient.SetRepeat(repeating);
    NewGetJsGradientColorStops(lineGradient, jsObj->GetProperty("colors"));
    ViewAbstractModel::GetInstance()->SetBorderImageGradient(lineGradient);
    bitset |= BorderImage::GRADIENT_BIT;
}

void JSViewAbstract::ParseBorderImageRepeat(const JSRef<JSVal>& args, RefPtr<BorderImage>& borderImage)
{
    auto repeatString = args->ToString();
    if (repeatString == "Repeat") {
        borderImage->SetRepeatMode(BorderImageRepeat::REPEAT);
    } else if (repeatString == "Round") {
        borderImage->SetRepeatMode(BorderImageRepeat::ROUND);
    } else if (repeatString == "Space") {
        borderImage->SetRepeatMode(BorderImageRepeat::SPACE);
    } else {
        borderImage->SetRepeatMode(BorderImageRepeat::STRETCH);
    }
}

void JSViewAbstract::ParseBorderImageOutset(const JSRef<JSVal>& args, RefPtr<BorderImage>& borderImage)
{
    CalcDimension outsetDimension;
    if (ParseJsDimensionVp(args, outsetDimension)) {
        borderImage->SetEdgeOutset(BorderImageDirection::LEFT, outsetDimension);
        borderImage->SetEdgeOutset(BorderImageDirection::RIGHT, outsetDimension);
        borderImage->SetEdgeOutset(BorderImageDirection::TOP, outsetDimension);
        borderImage->SetEdgeOutset(BorderImageDirection::BOTTOM, outsetDimension);
        return;
    }
    BorderImage::BorderImageOption option;
    ParseBorderImageDimension(args, option);
    if (option.leftDimension.has_value()) {
        borderImage->SetEdgeOutset(BorderImageDirection::LEFT, option.leftDimension.value());
    }
    if (option.rightDimension.has_value()) {
        borderImage->SetEdgeOutset(BorderImageDirection::RIGHT, option.rightDimension.value());
    }
    if (option.topDimension.has_value()) {
        borderImage->SetEdgeOutset(BorderImageDirection::TOP, option.topDimension.value());
    }
    if (option.bottomDimension.has_value()) {
        borderImage->SetEdgeOutset(BorderImageDirection::BOTTOM, option.bottomDimension.value());
    }
}

void JSViewAbstract::ParseBorderImageSlice(const JSRef<JSVal>& args, RefPtr<BorderImage>& borderImage)
{
    CalcDimension sliceDimension;
    if (ParseJsDimensionVp(args, sliceDimension)) {
        borderImage->SetEdgeSlice(BorderImageDirection::LEFT, sliceDimension);
        borderImage->SetEdgeSlice(BorderImageDirection::RIGHT, sliceDimension);
        borderImage->SetEdgeSlice(BorderImageDirection::TOP, sliceDimension);
        borderImage->SetEdgeSlice(BorderImageDirection::BOTTOM, sliceDimension);
        return;
    }

    JSRef<JSObject> object = JSRef<JSObject>::Cast(args);
    static std::array<std::string, 4> keys = { "left", "right", "top", "bottom" };
    for (uint32_t i = 0; i < keys.size(); i++) {
        auto dimensionValue = object->GetProperty(keys.at(i).c_str());
        if (ParseJsDimensionVp(dimensionValue, sliceDimension)) {
            borderImage->SetEdgeSlice(static_cast<BorderImageDirection>(i), sliceDimension);
        }
    }
}

void JSViewAbstract::ParseBorderImageWidth(const JSRef<JSVal>& args, RefPtr<BorderImage>& borderImage)
{
    CalcDimension widthDimension;
    if (ParseJsDimensionVp(args, widthDimension)) {
        borderImage->SetEdgeWidth(BorderImageDirection::LEFT, widthDimension);
        borderImage->SetEdgeWidth(BorderImageDirection::RIGHT, widthDimension);
        borderImage->SetEdgeWidth(BorderImageDirection::TOP, widthDimension);
        borderImage->SetEdgeWidth(BorderImageDirection::BOTTOM, widthDimension);
        return;
    }

    BorderImage::BorderImageOption option;
    ParseBorderImageDimension(args, option);
    if (option.leftDimension.has_value()) {
        borderImage->SetEdgeWidth(BorderImageDirection::LEFT, option.leftDimension.value());
    }
    if (option.rightDimension.has_value()) {
        borderImage->SetEdgeWidth(BorderImageDirection::RIGHT, option.rightDimension.value());
    }
    if (option.topDimension.has_value()) {
        borderImage->SetEdgeWidth(BorderImageDirection::TOP, option.topDimension.value());
    }
    if (option.bottomDimension.has_value()) {
        borderImage->SetEdgeWidth(BorderImageDirection::BOTTOM, option.bottomDimension.value());
    }
}

void JSViewAbstract::JsBorderColor(const JSCallbackInfo& info)
{
    ParseBorderColor(info[0]);
}

void JSViewAbstract::ParseBorderColor(const JSRef<JSVal>& args)
{
    if (!args->IsObject() && !args->IsNumber() && !args->IsString()) {
        ViewAbstractModel::GetInstance()->SetBorderColor(Color::BLACK);
        return;
    }
    std::optional<Color> leftColor;
    std::optional<Color> rightColor;
    std::optional<Color> topColor;
    std::optional<Color> bottomColor;
    Color borderColor;
    if (ParseJsColor(args, borderColor)) {
        ViewAbstractModel::GetInstance()->SetBorderColor(borderColor);
    } else if (args->IsObject()) {
        JSRef<JSObject> object = JSRef<JSObject>::Cast(args);
        Color left;
        if (ParseJsColor(object->GetProperty("left"), left)) {
            leftColor = left;
        }
        Color right;
        if (ParseJsColor(object->GetProperty("right"), right)) {
            rightColor = right;
        }
        Color top;
        if (ParseJsColor(object->GetProperty("top"), top)) {
            topColor = top;
        }
        Color bottom;
        if (ParseJsColor(object->GetProperty("bottom"), bottom)) {
            bottomColor = bottom;
        }

        ViewAbstractModel::GetInstance()->SetBorderColor(leftColor, rightColor, topColor, bottomColor);
    } else {
        return;
    }
}

void JSViewAbstract::ParseOuterBorderColor(const JSRef<JSVal>& args)
{
    if (!args->IsObject() && !args->IsNumber() && !args->IsString()) {
        ViewAbstractModel::GetInstance()->SetOuterBorderColor(Color::BLACK);
        return;
    }
    std::optional<Color> leftColor;
    std::optional<Color> rightColor;
    std::optional<Color> topColor;
    std::optional<Color> bottomColor;
    Color borderColor;
    if (ParseJsColor(args, borderColor)) {
        ViewAbstractModel::GetInstance()->SetOuterBorderColor(borderColor);
    } else if (args->IsObject()) {
        JSRef<JSObject> object = JSRef<JSObject>::Cast(args);
        Color left;
        if (ParseJsColor(object->GetProperty("left"), left)) {
            leftColor = left;
        }
        Color right;
        if (ParseJsColor(object->GetProperty("right"), right)) {
            rightColor = right;
        }
        Color top;
        if (ParseJsColor(object->GetProperty("top"), top)) {
            topColor = top;
        }
        Color bottom;
        if (ParseJsColor(object->GetProperty("bottom"), bottom)) {
            bottomColor = bottom;
        }

        ViewAbstractModel::GetInstance()->SetOuterBorderColor(leftColor, rightColor, topColor, bottomColor);
    } else {
        return;
    }
}

void JSViewAbstract::JsBorderRadius(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::STRING, JSCallbackInfoType::NUMBER,
        JSCallbackInfoType::OBJECT };
    if (!CheckJSCallbackInfo("JsBorderRadius", info, checkList)) {
        ViewAbstractModel::GetInstance()->SetBorderRadius({});
        return;
    }
    ParseBorderRadius(info[0]);
}

void JSViewAbstract::ParseBorderRadius(const JSRef<JSVal>& args)
{
    if (!args->IsObject() && !args->IsNumber() && !args->IsString()) {
        return;
    }
    CalcDimension borderRadius;
    if (ParseJsDimensionVp(args, borderRadius)) {
        if (borderRadius.Unit() == DimensionUnit::PERCENT) {
            borderRadius.Reset();
        }
        ViewAbstractModel::GetInstance()->SetBorderRadius(borderRadius);
    } else if (args->IsObject()) {
        JSRef<JSObject> object = JSRef<JSObject>::Cast(args);
        CalcDimension topLeft;
        CalcDimension topRight;
        CalcDimension bottomLeft;
        CalcDimension bottomRight;
        ParseAllBorderRadiuses(object, topLeft, topRight, bottomLeft, bottomRight);
        ViewAbstractModel::GetInstance()->SetBorderRadius(topLeft, topRight, bottomLeft, bottomRight);
    }
}

void JSViewAbstract::ParseOuterBorderRadius(const JSRef<JSVal>& args)
{
    if (!args->IsObject() && !args->IsNumber() && !args->IsString()) {
        return;
    }
    CalcDimension borderRadius;
    if (ParseJsDimensionVp(args, borderRadius)) {
        if (borderRadius.Unit() == DimensionUnit::PERCENT) {
            borderRadius.Reset();
        }
        ViewAbstractModel::GetInstance()->SetOuterBorderRadius(borderRadius);
    } else if (args->IsObject()) {
        JSRef<JSObject> object = JSRef<JSObject>::Cast(args);
        CalcDimension topLeft;
        CalcDimension topRight;
        CalcDimension bottomLeft;
        CalcDimension bottomRight;
        ParseAllBorderRadiuses(object, topLeft, topRight, bottomLeft, bottomRight);
        ViewAbstractModel::GetInstance()->SetOuterBorderRadius(topLeft, topRight, bottomLeft, bottomRight);
    }
}

void JSViewAbstract::GetBorderRadius(const char* key, JSRef<JSObject>& object, CalcDimension& radius)
{
    if (ParseJsDimensionVp(object->GetProperty(key), radius)) {
        if ((radius.Unit() == DimensionUnit::PERCENT)) {
            radius.Reset();
        }
    }
}

void JSViewAbstract::ParseAllBorderRadiuses(JSRef<JSObject>& object, CalcDimension& topLeft, CalcDimension& topRight,
    CalcDimension& bottomLeft, CalcDimension& bottomRight)
{
    GetBorderRadius("topLeft", object, topLeft);
    GetBorderRadius("topRight", object, topRight);
    GetBorderRadius("bottomLeft", object, bottomLeft);
    GetBorderRadius("bottomRight", object, bottomRight);
}

void JSViewAbstract::JsBorderStyle(const JSCallbackInfo& info)
{
    ParseBorderStyle(info[0]);
}
namespace {
BorderStyle ConvertBorderStyle(int32_t value)
{
    auto style = static_cast<BorderStyle>(value);
    if (style < BorderStyle::SOLID || style > BorderStyle::NONE) {
        style = BorderStyle::SOLID;
    }
    return style;
}
} // namespace

void JSViewAbstract::ParseBorderStyle(const JSRef<JSVal>& args)
{
    if (!args->IsObject() && !args->IsNumber()) {
        ViewAbstractModel::GetInstance()->SetBorderStyle(BorderStyle::SOLID);
        return;
    }
    if (args->IsObject()) {
        std::optional<BorderStyle> styleLeft;
        std::optional<BorderStyle> styleRight;
        std::optional<BorderStyle> styleTop;
        std::optional<BorderStyle> styleBottom;
        JSRef<JSObject> object = JSRef<JSObject>::Cast(args);
        auto leftValue = object->GetProperty("left");
        if (!leftValue->IsUndefined() && leftValue->IsNumber()) {
            styleLeft = ConvertBorderStyle(leftValue->ToNumber<int32_t>());
        }
        auto rightValue = object->GetProperty("right");
        if (!rightValue->IsUndefined() && rightValue->IsNumber()) {
            styleRight = ConvertBorderStyle(rightValue->ToNumber<int32_t>());
        }
        auto topValue = object->GetProperty("top");
        if (!topValue->IsUndefined() && topValue->IsNumber()) {
            styleTop = ConvertBorderStyle(topValue->ToNumber<int32_t>());
        }
        auto bottomValue = object->GetProperty("bottom");
        if (!bottomValue->IsUndefined() && bottomValue->IsNumber()) {
            styleBottom = ConvertBorderStyle(bottomValue->ToNumber<int32_t>());
        }
        ViewAbstractModel::GetInstance()->SetBorderStyle(styleLeft, styleRight, styleTop, styleBottom);
        return;
    }
    auto borderStyle = ConvertBorderStyle(args->ToNumber<int32_t>());
    ViewAbstractModel::GetInstance()->SetBorderStyle(borderStyle);
}

void JSViewAbstract::ParseOuterBorderStyle(const JSRef<JSVal>& args)
{
    if (!args->IsObject() && !args->IsNumber()) {
        ViewAbstractModel::GetInstance()->SetOuterBorderStyle(BorderStyle::SOLID);
        return;
    }
    if (args->IsObject()) {
        std::optional<BorderStyle> styleLeft;
        std::optional<BorderStyle> styleRight;
        std::optional<BorderStyle> styleTop;
        std::optional<BorderStyle> styleBottom;
        JSRef<JSObject> object = JSRef<JSObject>::Cast(args);
        auto leftValue = object->GetProperty("left");
        if (!leftValue->IsUndefined() && leftValue->IsNumber()) {
            styleLeft = ConvertBorderStyle(leftValue->ToNumber<int32_t>());
        }
        auto rightValue = object->GetProperty("right");
        if (!rightValue->IsUndefined() && rightValue->IsNumber()) {
            styleRight = ConvertBorderStyle(rightValue->ToNumber<int32_t>());
        }
        auto topValue = object->GetProperty("top");
        if (!topValue->IsUndefined() && topValue->IsNumber()) {
            styleTop = ConvertBorderStyle(topValue->ToNumber<int32_t>());
        }
        auto bottomValue = object->GetProperty("bottom");
        if (!bottomValue->IsUndefined() && bottomValue->IsNumber()) {
            styleBottom = ConvertBorderStyle(bottomValue->ToNumber<int32_t>());
        }
        ViewAbstractModel::GetInstance()->SetOuterBorderStyle(styleLeft, styleRight, styleTop, styleBottom);
        return;
    }
    auto borderStyle = ConvertBorderStyle(args->ToNumber<int32_t>());
    ViewAbstractModel::GetInstance()->SetOuterBorderStyle(borderStyle);
}

void JSViewAbstract::JsBlur(const JSCallbackInfo& info)
{
    if (info.Length() == 0) {
        return;
    }
    double blur = 0.0;
    if (!ParseJsDouble(info[0], blur)) {
        return;
    }

    BlurOption blurOption;
    if (info.Length() > 1 && info[1]->IsObject()) {
        JSRef<JSObject> jsBlurOption = JSRef<JSObject>::Cast(info[1]);
        ParseBlurOption(jsBlurOption, blurOption);
    }
    CalcDimension dimensionRadius(blur, DimensionUnit::PX);
    ViewAbstractModel::GetInstance()->SetFrontBlur(dimensionRadius, blurOption);
    info.SetReturnValue(info.This());
}

void JSViewAbstract::JsColorBlend(const JSCallbackInfo& info)
{
    Color colorBlend;
    if (info[0]->IsUndefined()) {
        colorBlend = Color::TRANSPARENT;
        SetColorBlend(colorBlend);
        return;
    }
    if (!ParseJsColor(info[0], colorBlend)) {
        return;
    }
    SetColorBlend(colorBlend);
    info.SetReturnValue(info.This());
}

void JSViewAbstract::JsUseEffect(const JSCallbackInfo& info)
{
    if (info[0]->IsBoolean()) {
        ViewAbstractModel::GetInstance()->SetUseEffect(info[0]->ToBoolean());
    }
}

void JSViewAbstract::JsUseShadowBatching(const JSCallbackInfo& info)
{
    if (info[0]->IsBoolean()) {
        ViewAbstractModel::GetInstance()->SetUseShadowBatching(info[0]->ToBoolean());
    }
}

void JSViewAbstract::JsBackdropBlur(const JSCallbackInfo& info)
{
    if (info.Length() == 0) {
        return;
    }
    double blur = 0.0;
    if (!ParseJsDouble(info[0], blur)) {
        return;
    }
    BlurOption blurOption;
    if (info.Length() > 1 && info[1]->IsObject()) {
        JSRef<JSObject> jsBlurOption = JSRef<JSObject>::Cast(info[1]);
        ParseBlurOption(jsBlurOption, blurOption);
    }
    CalcDimension dimensionRadius(blur, DimensionUnit::PX);
    ViewAbstractModel::GetInstance()->SetBackdropBlur(dimensionRadius, blurOption);

    info.SetReturnValue(info.This());
}

void JSViewAbstract::GetFractionStops(
    std::vector<std::pair<float, float>>& fractionStops, const JSRef<JSVal>& array)
{
    if (!array->IsArray() || JSRef<JSArray>::Cast(array)->Length() <= 1) {
        return;
    }
    JSRef<JSArray> jsArray = JSRef<JSArray>::Cast(array);
    float tmpPos = -1.0f;
    size_t length = jsArray->Length();
    for (size_t i = 0; i < length; i++) {
        std::pair<float, float> fractionStop;
        JSRef<JSVal> item = jsArray->GetValueAt(i);
        if (!item->IsArray()) {
            continue;
        }
        JSRef<JSArray> subArray = JSRef<JSArray>::Cast(item);
        if (subArray->Length() < 2) {
            continue;
        }

        double value = 0.0;
        if (ParseJsDouble(subArray->GetValueAt(0), value)) {
            value = std::clamp(value, 0.0, 1.0);
            fractionStop.first = static_cast<float>(value);
        }
        value = 0.0;
        if (ParseJsDouble(subArray->GetValueAt(1), value)) {
            value = std::clamp(value, 0.0, 1.0);
            fractionStop.second = static_cast<float>(value);
        }

        if (fractionStop.second <= tmpPos) {
            fractionStops.clear();
            return;
        }
        tmpPos = fractionStop.second;
        fractionStops.push_back(fractionStop);
    }
}
void JSViewAbstract::JsLinearGradientBlur(const JSCallbackInfo& info)
{
    if (info.Length() < 2) { // 2 represents the least para num;
        return;
    }
    double blurRadius = 0.0;
    ParseJsDouble(info[0], blurRadius);

    std::vector<std::pair<float, float>> fractionStops;
    auto direction = GradientDirection::BOTTOM;
    if (info[1]->IsObject()) {
        JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[1]);
        GetFractionStops(fractionStops, jsObj->GetProperty("fractionStops"));
        auto directionValue =
            jsObj->GetPropertyValue<int8_t>("direction", static_cast<int8_t>(GradientDirection::BOTTOM));
        if (directionValue < static_cast<int8_t>(GradientDirection::LEFT) ||
            directionValue >= static_cast<int8_t>(GradientDirection::NONE)) {
            directionValue = static_cast<int8_t>(GradientDirection::BOTTOM);
        }
        direction = static_cast<GradientDirection>(directionValue);
    }
    if (static_cast<int32_t>(fractionStops.size()) <= 1) {
        fractionStops.clear();
        fractionStops.push_back(std::pair<float, float>(0.0f, 0.0f));
        fractionStops.push_back(std::pair<float, float>(0.0f, 1.0f));
    }
    // Parse direction
    CalcDimension dimensionRadius(static_cast<float>(blurRadius), DimensionUnit::PX);
    NG::LinearGradientBlurPara blurPara(dimensionRadius, fractionStops, static_cast<NG::GradientDirection>(direction));
    SetLinearGradientBlur(blurPara);
}

void JSViewAbstract::JsBackgroundBrightness(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);
    double rate = 0.0;
    double lightUpDegree = 0.0;
    if (!ParseJsDouble(jsObj->GetProperty("rate"), rate)) {
        return;
    }
    if (!ParseJsDouble(jsObj->GetProperty("lightUpDegree"), lightUpDegree)) {
        return;
    }
    SetDynamicLightUp(rate, lightUpDegree);
}

void JSViewAbstract::JsWindowBlur(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::OBJECT };
    if (!CheckJSCallbackInfo("JsWindowBlur", info, checkList)) {
        return;
    }

    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);
    double progress = 0.0;
    ParseJsDouble(jsObj->GetProperty("percent"), progress);
    auto style = jsObj->GetPropertyValue<int32_t>("style",
        static_cast<int32_t>(WindowBlurStyle::STYLE_BACKGROUND_SMALL_LIGHT));

    progress = std::clamp(progress, 0.0, 1.0);
    style = std::clamp(style, static_cast<int32_t>(WindowBlurStyle::STYLE_BACKGROUND_SMALL_LIGHT),
        static_cast<int32_t>(WindowBlurStyle::STYLE_BACKGROUND_XLARGE_DARK));

    SetWindowBlur(static_cast<float>(progress), static_cast<WindowBlurStyle>(style));
    info.SetReturnValue(info.This());
}

bool JSViewAbstract::ParseDollarResource(const JSRef<JSVal>& jsValue, ResourceType& resType, std::string& resName)
{
    if (!jsValue->IsString()) {
        return false;
    }
    std::string resPath = jsValue->ToString();
    std::vector<std::string> tokens;
    StringUtils::StringSplitter(resPath, '.', tokens);
    if (static_cast<int32_t>(tokens.size()) != 3) { // $r format like app.xxx.xxx, has 3 paragraph
        return false;
    }
    if (std::find(RESOURCE_HEADS.begin(), RESOURCE_HEADS.end(), tokens[0]) == RESOURCE_HEADS.end()) {
        return false;
    }
    if (!ConvertResourceType(tokens[1], resType)) {
        return false;
    }
    resName = resPath;
    return true;
}

bool JSViewAbstract::ConvertResourceType(const std::string& typeName, ResourceType& resType)
{
    static const std::unordered_map<std::string, ResourceType> resTypeMap {
        { "color", ResourceType::COLOR },
        { "media", ResourceType::MEDIA },
        { "float", ResourceType::FLOAT },
        { "string", ResourceType::STRING },
        { "plural", ResourceType::PLURAL },
        { "pattern", ResourceType::PATTERN },
        { "boolean", ResourceType::BOOLEAN },
        { "integer", ResourceType::INTEGER },
        { "strarray", ResourceType::STRARRAY },
        { "intarray", ResourceType::INTARRAY },
    };
    auto it = resTypeMap.find(typeName);
    if (it == resTypeMap.end()) {
        return false;
    }
    resType = it->second;
    return true;
}

void JSViewAbstract::CompleteResourceObject(JSRef<JSObject>& jsObj)
{
    // dynamic $r raw input format is
    // {"id":"app.xxx.xxx", "params":[], "bundleName":"xxx", "moduleName":"xxx"}
    JSRef<JSVal> resId = jsObj->GetProperty("id");
    ResourceType resType;
    std::string resName;
    if (!ParseDollarResource(resId, resType, resName)) {
        return;
    }
    JSRef<JSVal> args = jsObj->GetProperty("params");
    if (!args->IsArray()) {
        return;
    }
    JSRef<JSArray> params = JSRef<JSArray>::Cast(args);
    auto paramCount = params->Length();
    JSRef<JSVal> name = JSRef<JSVal>::Make(ToJSValue(resName));
    if (resType == ResourceType::PLURAL || resType == ResourceType::STRING) {
        std::vector<JSRef<JSVal>> tmpParams;
        for (uint32_t i = 0; i < paramCount; i++) {
            auto param = params->GetValueAt(i);
            tmpParams.insert(tmpParams.end(), param);
        }
        params->SetValueAt(0, name);
        uint32_t paramIndex = 1;
        auto firstParam = jsObj->GetProperty("type");
        if (!firstParam->IsEmpty()) {
            params->SetValueAt(paramIndex, firstParam);
            paramIndex++;
        }
        for (auto tmpParam : tmpParams) {
            params->SetValueAt(paramIndex, tmpParam);
            paramIndex++;
        }
    } else {
        params->SetValueAt(0, name);
    }
    jsObj->SetProperty<int32_t>("id", UNKNOWN_RESOURCE_ID);
    jsObj->SetProperty<int32_t>("type", static_cast<int32_t>(resType));
    if (!jsObj->HasProperty("bundleName")) {
        jsObj->SetProperty<std::string>("bundleName", "");
    }
    if (!jsObj->HasProperty("moduleName")) {
        jsObj->SetProperty<std::string>("moduleName", "");
    }
}

bool JSViewAbstract::ParseJsDimensionNG(
    const JSRef<JSVal>& jsValue, CalcDimension& result, DimensionUnit defaultUnit, bool isSupportPercent)
{
    if (!jsValue->IsNumber() && !jsValue->IsString() && !jsValue->IsObject()) {
        return false;
    }

    if (jsValue->IsNumber()) {
        result = CalcDimension(jsValue->ToNumber<double>(), defaultUnit);
        return true;
    }
    if (jsValue->IsString()) {
        auto value = jsValue->ToString();
        if (value.back() == '%' && !isSupportPercent) {
            return false;
        }
        return StringUtils::StringToCalcDimensionNG(jsValue->ToString(), result, false, defaultUnit);
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    CompleteResourceObject(jsObj);
    JSRef<JSVal> resId = jsObj->GetProperty("id");
    if (!resId->IsNumber()) {
        return false;
    }

    auto resourceObject = GetResourceObject(jsObj);
    auto resourceWrapper = CreateResourceWrapper(jsObj, resourceObject);
    if (!resourceWrapper) {
        return false;
    }

    auto resIdNum = resId->ToNumber<int32_t>();
    uint32_t resType = resourceObject->GetType();
    if (resIdNum == -1) {
        if (!IsGetResourceByName(jsObj)) {
            return false;
        }
        JSRef<JSVal> args = jsObj->GetProperty("params");
        if (!args->IsArray()) {
            return false;
        }
        JSRef<JSArray> params = JSRef<JSArray>::Cast(args);
        auto param = params->GetValueAt(0);
        if (resType == static_cast<uint32_t>(ResourceType::STRING)) {
            auto value = resourceWrapper->GetStringByName(param->ToString());
            return StringUtils::StringToCalcDimensionNG(value, result, false, defaultUnit);
        }
        if (resType == static_cast<uint32_t>(ResourceType::INTEGER)) {
            auto value = std::to_string(resourceWrapper->GetIntByName(param->ToString()));
            StringUtils::StringToDimensionWithUnitNG(value, result, defaultUnit);
            return true;
        }
        result = resourceWrapper->GetDimensionByName(param->ToString());
        return true;
    }

    JSRef<JSVal> type = jsObj->GetProperty("type");
    if (type->IsNull() || !type->IsNumber()) {
        return false;
    }
    if (resType == static_cast<uint32_t>(ResourceType::STRING)) {
        auto value = resourceWrapper->GetString(resId->ToNumber<uint32_t>());
        return StringUtils::StringToCalcDimensionNG(value, result, false, defaultUnit);
    }
    if (resType == static_cast<uint32_t>(ResourceType::INTEGER)) {
        auto value = std::to_string(resourceWrapper->GetInt(resId->ToNumber<uint32_t>()));
        StringUtils::StringToDimensionWithUnitNG(value, result, defaultUnit);
        return true;
    }

    if (resType == static_cast<uint32_t>(ResourceType::FLOAT)) {
        result = resourceWrapper->GetDimension(resId->ToNumber<uint32_t>()); // float return true pixel value
        return true;
    }

    return false;
}

bool JSViewAbstract::ParseJsDimension(const JSRef<JSVal>& jsValue, CalcDimension& result, DimensionUnit defaultUnit)
{
    if (!jsValue->IsNumber() && !jsValue->IsString() && !jsValue->IsObject()) {
        return false;
    }

    if (jsValue->IsNumber()) {
        result = CalcDimension(jsValue->ToNumber<double>(), defaultUnit);
        return true;
    }
    if (jsValue->IsString()) {
        return StringUtils::StringToCalcDimensionNG(jsValue->ToString(), result, false, defaultUnit);
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    CompleteResourceObject(jsObj);
    JSRef<JSVal> resId = jsObj->GetProperty("id");
    if (!resId->IsNumber()) {
        return false;
    }

    auto resourceObject = GetResourceObject(jsObj);
    auto resourceWrapper = CreateResourceWrapper(jsObj, resourceObject);
    if (!resourceWrapper) {
        return false;
    }

    auto resIdNum = resId->ToNumber<int32_t>();
    uint32_t resType = resourceObject->GetType();
    if (resIdNum == -1) {
        if (!IsGetResourceByName(jsObj)) {
            return false;
        }
        JSRef<JSVal> args = jsObj->GetProperty("params");
        if (!args->IsArray()) {
            return false;
        }
        JSRef<JSArray> params = JSRef<JSArray>::Cast(args);
        auto param = params->GetValueAt(0);
        if (resType == static_cast<uint32_t>(ResourceType::STRING)) {
            auto value = resourceWrapper->GetStringByName(param->ToString());
            result = StringUtils::StringToCalcDimension(value, false, defaultUnit);
            return true;
        }
        if (resType == static_cast<uint32_t>(ResourceType::INTEGER)) {
            auto value = std::to_string(resourceWrapper->GetIntByName(param->ToString()));
            result = StringUtils::StringToDimensionWithUnit(value, defaultUnit);
            return true;
        }
        result = resourceWrapper->GetDimensionByName(param->ToString());
        return true;
    }

    JSRef<JSVal> type = jsObj->GetProperty("type");
    if (type->IsNull() || !type->IsNumber()) {
        return false;
    }
    if (resType == static_cast<uint32_t>(ResourceType::STRING)) {
        auto value = resourceWrapper->GetString(resId->ToNumber<uint32_t>());
        result = StringUtils::StringToCalcDimension(value, false, defaultUnit);
        return true;
    }
    if (resType == static_cast<uint32_t>(ResourceType::INTEGER)) {
        auto value = std::to_string(resourceWrapper->GetInt(resId->ToNumber<uint32_t>()));
        result = StringUtils::StringToDimensionWithUnit(value, defaultUnit);
        return true;
    }
    result = resourceWrapper->GetDimension(resId->ToNumber<uint32_t>());
    return true;
}

bool JSViewAbstract::ParseJsDimensionVpNG(const JSRef<JSVal>& jsValue, CalcDimension& result, bool isSupportPercent)
{
    // 'vp' -> the value varies with pixel density of device.
    return ParseJsDimensionNG(jsValue, result, DimensionUnit::VP, isSupportPercent);
}

bool JSViewAbstract::ParseJsDimensionVp(const JSRef<JSVal>& jsValue, CalcDimension& result)
{
    // 'vp' -> the value varies with pixel density of device.
    return ParseJsDimension(jsValue, result, DimensionUnit::VP);
}

bool JSViewAbstract::ParseJsDimensionFp(const JSRef<JSVal>& jsValue, CalcDimension& result)
{
    // the 'fp' unit is used for text scenes.
    return ParseJsDimension(jsValue, result, DimensionUnit::FP);
}

bool JSViewAbstract::ParseJsDimensionFpNG(const JSRef<JSVal>& jsValue, CalcDimension& result, bool isSupportPercent)
{
    // the 'fp' unit is used for text scenes.
    return ParseJsDimensionNG(jsValue, result, DimensionUnit::FP, isSupportPercent);
}

bool JSViewAbstract::ParseJsDimensionPx(const JSRef<JSVal>& jsValue, CalcDimension& result)
{
    return ParseJsDimension(jsValue, result, DimensionUnit::PX);
}

bool JSViewAbstract::ParseResourceToDouble(const JSRef<JSVal>& jsValue, double& result)
{
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    CompleteResourceObject(jsObj);
    if (jsObj->IsEmpty()) {
        return false;
    }
    JSRef<JSVal> id = jsObj->GetProperty("id");
    JSRef<JSVal> type = jsObj->GetProperty("type");
    if (!id->IsNumber() || !type->IsNumber()) {
        return false;
    }

    auto resId = id->ToNumber<int32_t>();
    auto resType = type->ToNumber<uint32_t>();

    auto resourceObject = GetResourceObject(jsObj);
    auto resourceWrapper = CreateResourceWrapper(jsObj, resourceObject);
    if (!resourceWrapper) {
        return false;
    }

    if (resId == -1) {
        if (!IsGetResourceByName(jsObj)) {
            return false;
        }
        JSRef<JSVal> args = jsObj->GetProperty("params");
        if (!args->IsArray()) {
            return false;
        }
        JSRef<JSArray> params = JSRef<JSArray>::Cast(args);
        auto param = params->GetValueAt(0);
        if (resType == static_cast<uint32_t>(ResourceType::STRING)) {
            auto numberString = resourceWrapper->GetStringByName(param->ToString());
            return StringUtils::StringToDouble(numberString, result);
        }
        if (resType == static_cast<uint32_t>(ResourceType::INTEGER)) {
            result = resourceWrapper->GetIntByName(param->ToString());
            return true;
        }
        if (resType == static_cast<uint32_t>(ResourceType::FLOAT)) {
            result = resourceWrapper->GetDoubleByName(param->ToString());
            return true;
        }
        return false;
    }
    if (resourceObject->GetType() == static_cast<uint32_t>(ResourceType::STRING)) {
        auto numberString = resourceWrapper->GetString(resId);
        return StringUtils::StringToDouble(numberString, result);
    }
    if (resourceObject->GetType() == static_cast<uint32_t>(ResourceType::INTEGER)) {
        result = resourceWrapper->GetInt(resId);
        return true;
    }
    if (resourceObject->GetType() == static_cast<uint32_t>(ResourceType::FLOAT)) {
        result = resourceWrapper->GetDouble(resId);
        return true;
    }
    return false;
}

bool JSViewAbstract::ParseJsDouble(const JSRef<JSVal>& jsValue, double& result)
{
    if (jsValue->IsNumber()) {
        result = jsValue->ToNumber<double>();
        return true;
    }
    if (jsValue->IsString()) {
        return StringUtils::StringToDouble(jsValue->ToString(), result);
    }
    if (jsValue->IsObject()) {
        return ParseResourceToDouble(jsValue, result);
    }
    return false;
}

bool JSViewAbstract::ParseJsInt32(const JSRef<JSVal>& jsValue, int32_t& result)
{
    if (!jsValue->IsNumber() && !jsValue->IsString() && !jsValue->IsObject()) {
        return false;
    }
    if (jsValue->IsNumber()) {
        result = jsValue->ToNumber<int32_t>();
        return true;
    }
    if (jsValue->IsString()) {
        result = StringUtils::StringToInt(jsValue->ToString());
        return true;
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    CompleteResourceObject(jsObj);
    JSRef<JSVal> resId = jsObj->GetProperty("id");
    if (!resId->IsNumber()) {
        return false;
    }

    auto resourceObject = GetResourceObject(jsObj);
    auto resourceWrapper = CreateResourceWrapper(jsObj, resourceObject);
    if (!resourceWrapper) {
        return false;
    }

    auto resIdNum = resId->ToNumber<int32_t>();
    if (resIdNum == -1) {
        if (!IsGetResourceByName(jsObj)) {
            return false;
        }
        JSRef<JSVal> args = jsObj->GetProperty("params");
        if (!args->IsArray()) {
            return false;
        }
        JSRef<JSArray> params = JSRef<JSArray>::Cast(args);
        auto param = params->GetValueAt(0);
        result = resourceWrapper->GetIntByName(param->ToString());
        return true;
    }
    result = resourceWrapper->GetInt(resId->ToNumber<uint32_t>());
    return true;
}

bool JSViewAbstract::ParseJsColorFromResource(const JSRef<JSVal>& jsValue, Color& result)
{
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    CompleteResourceObject(jsObj);
    JSRef<JSVal> resId = jsObj->GetProperty("id");
    if (!resId->IsNumber()) {
        return false;
    }

    auto resourceObject = GetResourceObject(jsObj);
    auto resourceWrapper = CreateResourceWrapper(jsObj, resourceObject);
    if (!resourceWrapper) {
        return false;
    }

    auto resIdNum = resId->ToNumber<int32_t>();
    if (resIdNum == -1) {
        if (!IsGetResourceByName(jsObj)) {
            return false;
        }
        JSRef<JSVal> args = jsObj->GetProperty("params");
        if (!args->IsArray()) {
            return false;
        }
        JSRef<JSArray> params = JSRef<JSArray>::Cast(args);
        auto param = params->GetValueAt(0);
        result = resourceWrapper->GetColorByName(param->ToString());
        return true;
    }
    JSRef<JSVal> type = jsObj->GetProperty("type");
    if (type->IsNull() || !type->IsNumber()) {
        return false;
    }
    if (resourceObject->GetType() == static_cast<uint32_t>(ResourceType::STRING)) {
        auto value = resourceWrapper->GetString(resId->ToNumber<uint32_t>());
        return Color::ParseColorString(value, result);
    }
    if (resourceObject->GetType() == static_cast<uint32_t>(ResourceType::INTEGER)) {
        auto value = resourceWrapper->GetInt(resId->ToNumber<uint32_t>());
        result = Color(ColorAlphaAdapt(value));
        return true;
    }
    if (resourceObject->GetType() == static_cast<uint32_t>(ResourceType::COLOR)) {
        result = resourceWrapper->GetColor(resId->ToNumber<uint32_t>());
        return true;
    }
    return false;
}

bool JSViewAbstract::ParseJsColor(const JSRef<JSVal>& jsValue, Color& result)
{
    if (!jsValue->IsNumber() && !jsValue->IsString() && !jsValue->IsObject()) {
        return false;
    }
    if (jsValue->IsNumber()) {
        result = Color(ColorAlphaAdapt(jsValue->ToNumber<uint32_t>()));
        return true;
    }
    if (jsValue->IsString()) {
        return Color::ParseColorString(jsValue->ToString(), result);
    }
    return ParseJsColorFromResource(jsValue, result);
}

bool JSViewAbstract::ParseJsColorStrategy(const JSRef<JSVal>& jsValue, ForegroundColorStrategy& strategy)
{
    if (jsValue->IsString()) {
        std::string colorStr = jsValue->ToString();
        if (colorStr.compare("invert") == 0) {
            strategy = ForegroundColorStrategy::INVERT;
            return true;
        }
    }
    return false;
}

bool JSViewAbstract::ParseJsShadowColorStrategy(const JSRef<JSVal>& jsValue, ShadowColorStrategy& strategy)
{
    if (jsValue->IsString()) {
        std::string colorStr = jsValue->ToString();
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

bool JSViewAbstract::ParseJsSymbolId(const JSRef<JSVal>& jsValue, std::uint32_t& symbolId)
{
    if (jsValue->IsNull() || jsValue->IsUndefined()) {
        symbolId = 0;
        return false;
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    JSRef<JSVal> resId = jsObj->GetProperty("id");
    if (resId->IsNull() || !resId->IsNumber()) {
        return false;
    }
    auto resourceObject = GetResourceObject(jsObj);
    if (!resourceObject) {
        return false;
    }
    auto resourceWrapper = CreateResourceWrapper(jsObj, resourceObject);
    if (!resourceWrapper) {
        return false;
    }
    auto symbol = resourceWrapper->GetSymbolById(resId->ToNumber<uint32_t>());
    if (!symbol) {
        return false;
    }
    symbolId = symbol;
    return true;
}

bool JSViewAbstract::ParseJsSymbolColor(const JSRef<JSVal>& jsValue, std::vector<Color>& result)
{
    if (!jsValue->IsArray()) {
        return false;
    }
    if (jsValue->IsArray()) {
        JSRef<JSArray> array = JSRef<JSArray>::Cast(jsValue);
        for (size_t i = 0; i < array->Length(); i++) {
            JSRef<JSVal> value = array->GetValueAt(i);
            if (!value->IsNumber() && !value->IsString() && !value->IsObject()) {
                return false;
            }
            if (value->IsNumber()) {
                result.emplace_back(Color(ColorAlphaAdapt(value->ToNumber<uint32_t>())));
                continue;
            } else if (value->IsString()) {
                Color color;
                Color::ParseColorString(value->ToString(), color);
                result.emplace_back(color);
                continue;
            } else {
                Color color;
                ParseJsColorFromResource(value, color);
                result.emplace_back(color);
            }
        }
        return true;
    }
    return false;
}

bool JSViewAbstract::ParseJsFontFamilies(const JSRef<JSVal>& jsValue, std::vector<std::string>& result)
{
    result.clear();
    if (!jsValue->IsString() && !jsValue->IsObject()) {
        return false;
    }
    if (jsValue->IsString()) {
        result = ConvertStrToFontFamilies(jsValue->ToString());
        return true;
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    CompleteResourceObject(jsObj);
    JSRef<JSVal> resId = jsObj->GetProperty("id");
    if (!resId->IsNumber()) {
        return false;
    }

    auto resourceObject = GetResourceObject(jsObj);
    auto resourceWrapper = CreateResourceWrapper(jsObj, resourceObject);
    if (!resourceWrapper) {
        return false;
    }

    auto resIdNum = resId->ToNumber<int32_t>();
    if (resIdNum == -1) {
        if (!IsGetResourceByName(jsObj)) {
            return false;
        }
        JSRef<JSVal> args = jsObj->GetProperty("params");
        if (!args->IsArray()) {
            return false;
        }
        JSRef<JSArray> params = JSRef<JSArray>::Cast(args);
        auto param = params->GetValueAt(0);
        result.emplace_back(resourceWrapper->GetStringByName(param->ToString()));
        return true;
    }
    result.emplace_back(resourceWrapper->GetString(resId->ToNumber<uint32_t>()));
    return true;
}

bool JSViewAbstract::ParseJsString(const JSRef<JSVal>& jsValue, std::string& result)
{
    if (!jsValue->IsString() && !jsValue->IsObject()) {
        return false;
    }

    if (jsValue->IsString()) {
        result = jsValue->ToString();
        return true;
    }

    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    CompleteResourceObject(jsObj);
    JSRef<JSVal> type = jsObj->GetProperty("type");
    if (!type->IsNumber()) {
        return false;
    }

    JSRef<JSVal> resId = jsObj->GetProperty("id");
    if (!resId->IsNumber()) {
        return false;
    }

    JSRef<JSVal> args = jsObj->GetProperty("params");
    if (!args->IsArray()) {
        return false;
    }

    auto resourceObject = GetResourceObject(jsObj);
    auto resourceWrapper = CreateResourceWrapper(jsObj, resourceObject);
    if (!resourceWrapper) {
        return false;
    }

    JSRef<JSArray> params = JSRef<JSArray>::Cast(args);
    auto resIdNum = resourceObject->GetId();
    if (resIdNum == -1) {
        if (!IsGetResourceByName(jsObj)) {
            return false;
        }
        auto param = params->GetValueAt(0);
        if (type->ToNumber<uint32_t>() == static_cast<uint32_t>(ResourceType::STRING)) {
            auto originStr = resourceWrapper->GetStringByName(param->ToString());
            ReplaceHolder(originStr, params, 1);
            result = originStr;
        } else if (type->ToNumber<uint32_t>() == static_cast<uint32_t>(ResourceType::PLURAL)) {
            auto countJsVal = params->GetValueAt(1);
            int count = 0;
            if (!countJsVal->IsNumber()) {
                return false;
            }
            count = countJsVal->ToNumber<int>();
            auto pluralStr = resourceWrapper->GetPluralStringByName(param->ToString(), count);
            ReplaceHolder(pluralStr, params, 2);
            result = pluralStr;
        } else {
            return false;
        }
        return true;
    }
    if (resourceObject->GetType() == static_cast<uint32_t>(ResourceType::STRING)) {
        auto originStr = resourceWrapper->GetString(resId->ToNumber<uint32_t>());
        ReplaceHolder(originStr, params, 0);
        result = originStr;
    } else if (resourceObject->GetType() == static_cast<uint32_t>(ResourceType::PLURAL)) {
        auto countJsVal = params->GetValueAt(0);
        int count = 0;
        if (!countJsVal->IsNumber()) {
            return false;
        }
        count = countJsVal->ToNumber<int>();
        auto pluralStr = resourceWrapper->GetPluralString(resId->ToNumber<uint32_t>(), count);
        ReplaceHolder(pluralStr, params, 1);
        result = pluralStr;
    } else if (resourceObject->GetType() == static_cast<uint32_t>(ResourceType::FLOAT)) {
        result = std::to_string(resourceWrapper->GetDouble(resId->ToNumber<uint32_t>()));
    } else if (resourceObject->GetType() == static_cast<uint32_t>(ResourceType::INTEGER)) {
        result = std::to_string(resourceWrapper->GetInt(resId->ToNumber<uint32_t>()));
    } else {
        return false;
    }
    return true;
}

bool JSViewAbstract::ParseJsMedia(const JSRef<JSVal>& jsValue, std::string& result)
{
    if (!jsValue->IsObject() && !jsValue->IsString()) {
        return false;
    }
    if (jsValue->IsString()) {
        result = jsValue->ToString();
        return true;
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    CompleteResourceObject(jsObj);
    JSRef<JSVal> type = jsObj->GetProperty("type");
    JSRef<JSVal> resId = jsObj->GetProperty("id");
    if (!resId->IsNull() && !type->IsNull() && type->IsNumber() && resId->IsNumber()) {
        auto resourceObject = GetResourceObject(jsObj);
        auto resourceWrapper = CreateResourceWrapper(jsObj, resourceObject);
        if (!resourceWrapper) {
            return false;
        }

        if (resourceObject->GetType() == static_cast<int32_t>(ResourceType::RAWFILE)) {
            JSRef<JSVal> args = jsObj->GetProperty("params");
            if (!args->IsArray()) {
                return false;
            }
            JSRef<JSArray> params = JSRef<JSArray>::Cast(args);
            auto fileName = params->GetValueAt(0);
            if (!fileName->IsString()) {
                return false;
            }
            result = resourceWrapper->GetRawfile(fileName->ToString());
            return true;
        }
        auto resIdNum = resId->ToNumber<int32_t>();
        if (resIdNum == -1) {
            if (!IsGetResourceByName(jsObj)) {
                return false;
            }
            JSRef<JSVal> args = jsObj->GetProperty("params");
            if (!args->IsArray()) {
                return false;
            }
            JSRef<JSArray> params = JSRef<JSArray>::Cast(args);
            auto param = params->GetValueAt(0);
            if (resourceObject->GetType() == static_cast<int32_t>(ResourceType::MEDIA)) {
                result = resourceWrapper->GetMediaPathByName(param->ToString());
                return true;
            }
            return false;
        }
        if (resourceObject->GetType() == static_cast<int32_t>(ResourceType::MEDIA)) {
            result = resourceWrapper->GetMediaPath(resId->ToNumber<uint32_t>());
            return true;
        }
        return false;
    }
    return false;
}

bool JSViewAbstract::ParseJsBool(const JSRef<JSVal>& jsValue, bool& result)
{
    if (!jsValue->IsBoolean() && !jsValue->IsObject()) {
        return false;
    }

    if (jsValue->IsBoolean()) {
        result = jsValue->ToBoolean();
        return true;
    }

    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    CompleteResourceObject(jsObj);
    JSRef<JSVal> type = jsObj->GetProperty("type");
    if (!type->IsNumber()) {
        return false;
    }

    JSRef<JSVal> resId = jsObj->GetProperty("id");
    if (!resId->IsNumber()) {
        return false;
    }

    auto resourceObject = GetResourceObject(jsObj);
    auto resourceWrapper = CreateResourceWrapper(jsObj, resourceObject);
    if (!resourceWrapper) {
        return false;
    }

    auto resIdNum = resId->ToNumber<int32_t>();
    if (resIdNum == -1) {
        if (!IsGetResourceByName(jsObj)) {
            return false;
        }
        JSRef<JSVal> args = jsObj->GetProperty("params");
        if (!args->IsArray()) {
            return false;
        }
        JSRef<JSArray> params = JSRef<JSArray>::Cast(args);
        auto param = params->GetValueAt(0);
        if (resourceObject->GetType() == static_cast<uint32_t>(ResourceType::BOOLEAN)) {
            result = resourceWrapper->GetBooleanByName(param->ToString());
            return true;
        }
        return false;
    }

    if (resourceObject->GetType() == static_cast<uint32_t>(ResourceType::BOOLEAN)) {
        result = resourceWrapper->GetBoolean(resId->ToNumber<uint32_t>());
        return true;
    }
    return false;
}

bool JSViewAbstract::ParseJsInteger(const JSRef<JSVal>& jsValue, uint32_t& result)
{
    return ParseJsInteger<uint32_t>(jsValue, result);
}

bool JSViewAbstract::ParseJsInteger(const JSRef<JSVal>& jsValue, int32_t& result)
{
    return ParseJsInteger<int32_t>(jsValue, result);
}

bool JSViewAbstract::ParseJsIntegerArray(const JSRef<JSVal>& jsValue, std::vector<uint32_t>& result)
{
    if (!jsValue->IsArray() && !jsValue->IsObject()) {
        return false;
    }

    if (jsValue->IsArray()) {
        JSRef<JSArray> array = JSRef<JSArray>::Cast(jsValue);
        for (size_t i = 0; i < array->Length(); i++) {
            JSRef<JSVal> value = array->GetValueAt(i);
            if (value->IsNumber()) {
                result.emplace_back(value->ToNumber<uint32_t>());
            } else if (value->IsObject()) {
                uint32_t singleResInt;
                if (ParseJsInteger(value, singleResInt)) {
                    result.emplace_back(singleResInt);
                } else {
                    return false;
                }
            } else {
                return false;
            }
        }
        return true;
    }

    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    CompleteResourceObject(jsObj);
    JSRef<JSVal> type = jsObj->GetProperty("type");
    if (!type->IsNumber()) {
        return false;
    }

    JSRef<JSVal> resId = jsObj->GetProperty("id");
    if (!resId->IsNumber()) {
        return false;
    }

    auto resourceObject = GetResourceObject(jsObj);
    auto resourceWrapper = CreateResourceWrapper(jsObj, resourceObject);
    if (!resourceWrapper) {
        return false;
    }

    auto resIdNum = resId->ToNumber<int32_t>();
    if (resIdNum == -1) {
        if (!IsGetResourceByName(jsObj)) {
            return false;
        }
        JSRef<JSVal> args = jsObj->GetProperty("params");
        if (!args->IsArray()) {
            return false;
        }
        JSRef<JSArray> params = JSRef<JSArray>::Cast(args);
        auto param = params->GetValueAt(0);
        if (resourceObject->GetType() == static_cast<uint32_t>(ResourceType::INTARRAY)) {
            result = resourceWrapper->GetIntArrayByName(param->ToString());
            return true;
        }
        return false;
    }

    if (resourceObject->GetType() == static_cast<uint32_t>(ResourceType::INTARRAY)) {
        result = resourceWrapper->GetIntArray(resId->ToNumber<uint32_t>());
        return true;
    }
    return false;
}

bool JSViewAbstract::ParseJsStrArray(const JSRef<JSVal>& jsValue, std::vector<std::string>& result)
{
    if (!jsValue->IsArray() && !jsValue->IsObject()) {
        return false;
    }

    if (jsValue->IsArray()) {
        JSRef<JSArray> array = JSRef<JSArray>::Cast(jsValue);
        for (size_t i = 0; i < array->Length(); i++) {
            JSRef<JSVal> value = array->GetValueAt(i);
            if (value->IsString()) {
                result.emplace_back(value->ToString());
            } else if (value->IsObject()) {
                std::string singleResStr;
                if (ParseJsString(value, singleResStr)) {
                    result.emplace_back(singleResStr);
                } else {
                    return false;
                }
            } else {
                return false;
            }
        }
        return true;
    }

    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    CompleteResourceObject(jsObj);
    JSRef<JSVal> type = jsObj->GetProperty("type");
    if (!type->IsNumber()) {
        return false;
    }

    JSRef<JSVal> resId = jsObj->GetProperty("id");
    if (!resId->IsNumber()) {
        return false;
    }

    auto resourceObject = GetResourceObject(jsObj);
    auto resourceWrapper = CreateResourceWrapper(jsObj, resourceObject);
    if (!resourceWrapper) {
        return false;
    }

    auto resIdNum = resId->ToNumber<int32_t>();
    if (resIdNum == -1) {
        if (!IsGetResourceByName(jsObj)) {
            return false;
        }
        JSRef<JSVal> args = jsObj->GetProperty("params");
        if (!args->IsArray()) {
            return false;
        }
        JSRef<JSArray> params = JSRef<JSArray>::Cast(args);
        auto param = params->GetValueAt(0);
        if (resourceObject->GetType() == static_cast<uint32_t>(ResourceType::STRARRAY)) {
            result = resourceWrapper->GetStringArrayByName(param->ToString());
            return true;
        }
        return false;
    }

    if (resourceObject->GetType() == static_cast<uint32_t>(ResourceType::STRARRAY)) {
        result = resourceWrapper->GetStringArray(resId->ToNumber<uint32_t>());
        return true;
    }
    return false;
}

bool JSViewAbstract::IsGetResourceByName(const JSRef<JSObject>& jsObj)
{
    JSRef<JSVal> resId = jsObj->GetProperty("id");
    if (!resId->IsNumber() || resId->ToNumber<int32_t>() != -1) {
        return false;
    }
    JSRef<JSVal> args = jsObj->GetProperty("params");
    if (!args->IsArray()) {
        return false;
    }
    JSRef<JSVal> bundleName = jsObj->GetProperty("bundleName");
    JSRef<JSVal> moduleName = jsObj->GetProperty("moduleName");
    if (!bundleName->IsString() || !moduleName->IsString()) {
        return false;
    }
    JSRef<JSArray> params = JSRef<JSArray>::Cast(args);
    if (params->IsEmpty()) {
        return false;
    }
    return true;
}

std::pair<CalcDimension, CalcDimension> JSViewAbstract::ParseSize(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::OBJECT };
    if (!CheckJSCallbackInfo("ParseSize", info, checkList)) {
        return std::pair<CalcDimension, CalcDimension>();
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);
    CalcDimension width;
    CalcDimension height;
    if (!ParseJsDimensionVp(jsObj->GetProperty("width"), width) ||
        !ParseJsDimensionVp(jsObj->GetProperty("height"), height)) {
        return std::pair<CalcDimension, CalcDimension>();
    }
    info.SetReturnValue(info.This());
    return std::pair<CalcDimension, CalcDimension>(width, height);
}

void JSViewAbstract::JsUseAlign(const JSCallbackInfo& info)
{
    if (info.Length() < 2) {
        return;
    }

    if (!info[0]->IsObject() && !info[1]->IsObject()) {
        return;
    }

    AlignDeclaration* declaration = JSRef<JSObject>::Cast(info[0])->Unwrap<AlignDeclaration>();
    if (declaration == nullptr) {
        return;
    }

    JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[1]);
    JSRef<JSVal> side = obj->GetProperty("side");
    JSRef<JSVal> offset = obj->GetProperty("offset");

    if (!side->IsNumber()) {
        return;
    }

    auto sideValue = side->ToNumber<int32_t>();

    if (declaration->GetDeclarationType() == AlignDeclaration::DeclarationType::HORIZONTAL) {
        if (sideValue < static_cast<int32_t>(AlignDeclaration::Edge::START) ||
            sideValue > static_cast<int32_t>(AlignDeclaration::Edge::END)) {
            return;
        }
    } else if (declaration->GetDeclarationType() == AlignDeclaration::DeclarationType::VERTICAL) {
        if (sideValue < static_cast<int32_t>(AlignDeclaration::Edge::TOP) ||
            sideValue > static_cast<int32_t>(AlignDeclaration::Edge::BASELINE)) {
            return;
        }
    }

    std::optional<CalcDimension> optOffset;
    CalcDimension offsetDimension;
    if (ParseJsDimensionVp(offset, offsetDimension)) {
        optOffset = offsetDimension;
    }
    ViewAbstractModel::GetInstance()->SetUseAlign(
        declaration, static_cast<AlignDeclaration::Edge>(sideValue), optOffset);
}

void JSViewAbstract::JsGridSpan(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::NUMBER };
    if (!CheckJSCallbackInfo("JsGridSpan", info, checkList)) {
        return;
    }
    auto span = info[0]->ToNumber<int32_t>();
    ViewAbstractModel::GetInstance()->SetGrid(span, std::nullopt);
}

void JSViewAbstract::JsGridOffset(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::NUMBER };
    if (!CheckJSCallbackInfo("JsGridOffset", info, checkList)) {
        return;
    }
    auto offset = info[0]->ToNumber<int32_t>();
    ViewAbstractModel::GetInstance()->SetGrid(std::nullopt, offset);
}

static bool ParseSpanAndOffset(const JSRef<JSVal>& val, uint32_t& span, int32_t& offset)
{
    // {lg: 4}
    if (val->IsNumber()) {
        span = val->ToNumber<uint32_t>();
        return true;
    }

    if (!val->IsObject()) {
        return false;
    }

    // {lg: {span: 1, offset: 2}}
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(val);
    span = obj->GetProperty("span")->ToNumber<uint32_t>();
    offset = obj->GetProperty("offset")->ToNumber<int32_t>();
    return true;
}

void JSViewAbstract::JsUseSizeType(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::OBJECT };
    if (!CheckJSCallbackInfo("JsUseSizeType", info, checkList)) {
        return;
    }
    JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(info[0]);
    for (auto values : SCREEN_SIZE_VALUES) {
        JSRef<JSVal> val = sizeObj->GetProperty(values.second.c_str());
        if (val->IsNull() || val->IsEmpty()) {
            continue;
        }
        uint32_t span = 0;
        int32_t offset = 0;
        if (ParseSpanAndOffset(val, span, offset)) {
            ViewAbstractModel::GetInstance()->SetGrid(span, offset, values.first);
        }
    }
}

void JSViewAbstract::JsZIndex(const JSCallbackInfo& info)
{
    int zIndex = 0;
    if (info[0]->IsNumber()) {
        zIndex = info[0]->ToNumber<int>();
    }

    ViewAbstractModel::GetInstance()->SetZIndex(zIndex);
}

void JSViewAbstract::Pop()
{
    ViewStackModel::GetInstance()->Pop();
}

void JSViewAbstract::JsSetDraggable(bool draggable)
{
    ViewAbstractModel::GetInstance()->SetDraggable(draggable);
}

void JSViewAbstract::JsSetDragPreviewOptions(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::OBJECT };
    if (!CheckJSCallbackInfo("JsSetDragPreviewOptions", info, checkList)) {
        return;
    }
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
    auto mode = obj->GetProperty("mode");
    if (!mode->IsNumber()) {
        ViewAbstractModel::GetInstance()->SetDragPreviewOptions({NG::DragPreviewMode::AUTO});
        return;
    }
    int32_t dragPreviewMode = mode->ToNumber<int>();
    if (!(dragPreviewMode >= static_cast<int32_t>(NG::DragPreviewMode::AUTO) &&
            dragPreviewMode <= static_cast<int32_t>(NG::DragPreviewMode::DISABLE_SCALE))) {
        dragPreviewMode = static_cast<int32_t>(NG::DragPreviewMode::AUTO);
    }
    NG::DragPreviewOption option {static_cast<NG::DragPreviewMode>(dragPreviewMode)};
    ViewAbstractModel::GetInstance()->SetDragPreviewOptions(option);
}

void JSViewAbstract::JsOnDragStart(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::FUNCTION };
    if (!CheckJSCallbackInfo("JsOnDragStart", info, checkList)) {
        return;
    }

    RefPtr<JsDragFunction> jsOnDragStartFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));

    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto onDragStart = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragStartFunc), node = frameNode](
                           const RefPtr<DragEvent>& info, const std::string& extraParams) -> NG::DragDropBaseInfo {
        NG::DragDropBaseInfo dragDropInfo;
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, dragDropInfo);
        PipelineContext::SetCallBackNode(node);
        auto ret = func->Execute(info, extraParams);
        if (!ret->IsObject()) {
            return dragDropInfo;
        }

        dragDropInfo.node = ParseDragNode(ret);
        auto builderObj = JSRef<JSObject>::Cast(ret);
#if defined(PIXEL_MAP_SUPPORTED)
        auto pixmap = builderObj->GetProperty("pixelMap");
        dragDropInfo.pixelMap = CreatePixelMapFromNapiValue(pixmap);
#endif
        auto extraInfo = builderObj->GetProperty("extraInfo");
        ParseJsString(extraInfo, dragDropInfo.extraInfo);
        return dragDropInfo;
    };
    ViewAbstractModel::GetInstance()->SetOnDragStart(std::move(onDragStart));
}

bool JSViewAbstract::ParseAndUpdateDragItemInfo(const JSRef<JSVal>& info, NG::DragDropBaseInfo& dragInfo)
{
    auto node = ParseDragNode(info);
    if (!node) {
        return false;
    }
    dragInfo.node = node;
    return true;
}

RefPtr<AceType> JSViewAbstract::ParseDragNode(const JSRef<JSVal>& info)
{
    auto builderFunc = ParseDragStartBuilderFunc(info);
    if (!builderFunc) {
        return nullptr;
    }
    // use another VSP instance while executing the builder function
    ViewStackModel::GetInstance()->NewScope();
    {
        ACE_SCORING_EVENT("onDragStart.builder");
        builderFunc->Execute();
    }

    return ViewStackModel::GetInstance()->Finish();
}

void JSViewAbstract::JsOnDragEnter(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::FUNCTION };
    if (!CheckJSCallbackInfo("JsOnDragEnter", info, checkList)) {
        return;
    }
    RefPtr<JsDragFunction> jsOnDragEnterFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto onDragEnter = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragEnterFunc), node = frameNode](
                           const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onDragEnter");
        PipelineContext::SetCallBackNode(node);
        func->Execute(info, extraParams);
    };

    ViewAbstractModel::GetInstance()->SetOnDragEnter(std::move(onDragEnter));
}

void JSViewAbstract::JsOnDragEnd(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::FUNCTION };
    if (!CheckJSCallbackInfo("JsOnDragEnd", info, checkList)) {
        return;
    }
    RefPtr<JsDragFunction> jsOnDragEndFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto onDragEnd = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragEndFunc), node = frameNode](
                         const RefPtr<OHOS::Ace::DragEvent>& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onDragEnd");
        auto extraParams = JsonUtil::Create(true);
        PipelineContext::SetCallBackNode(node);
        func->Execute(info, extraParams->ToString());
    };

    ViewAbstractModel::GetInstance()->SetOnDragEnd(std::move(onDragEnd));
}

void JSViewAbstract::JsOnDragMove(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::FUNCTION };
    if (!CheckJSCallbackInfo("JsOnDragMove", info, checkList)) {
        return;
    }
    RefPtr<JsDragFunction> jsOnDragMoveFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto onDragMove = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragMoveFunc), node = frameNode](
                          const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onDragMove");
        PipelineContext::SetCallBackNode(node);
        func->Execute(info, extraParams);
    };

    ViewAbstractModel::GetInstance()->SetOnDragMove(std::move(onDragMove));
}

void JSViewAbstract::JsOnDragLeave(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::FUNCTION };
    if (!CheckJSCallbackInfo("JsOnDragLeave", info, checkList)) {
        return;
    }
    RefPtr<JsDragFunction> jsOnDragLeaveFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto onDragLeave = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragLeaveFunc), node = frameNode](
                           const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onDragLeave");
        PipelineContext::SetCallBackNode(node);
        func->Execute(info, extraParams);
    };

    ViewAbstractModel::GetInstance()->SetOnDragLeave(std::move(onDragLeave));
}

void JSViewAbstract::JsOnDrop(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::FUNCTION };
    if (!CheckJSCallbackInfo("JsOnDrop", info, checkList)) {
        return;
    }
    RefPtr<JsDragFunction> jsOnDropFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto onDrop = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDropFunc), node = frameNode](
                      const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onDrop");
        PipelineContext::SetCallBackNode(node);
        func->Execute(info, extraParams);
    };

    ViewAbstractModel::GetInstance()->SetOnDrop(std::move(onDrop));
}

void JSViewAbstract::JsOnAreaChange(const JSCallbackInfo& info)
{
    if (info[0]->IsUndefined() && IsDisableEventVersion()) {
        ViewAbstractModel::GetInstance()->DisableOnAreaChange();
        return;
    }
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::FUNCTION };
    if (!CheckJSCallbackInfo("JsOnAreaChange", info, checkList)) {
        return;
    }
    auto jsOnAreaChangeFunction = AceType::MakeRefPtr<JsOnAreaChangeFunction>(JSRef<JSFunc>::Cast(info[0]));

    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto onAreaChanged = [execCtx = info.GetExecutionContext(), func = std::move(jsOnAreaChangeFunction),
                             node = frameNode](
                             const Rect& oldRect, const Offset& oldOrigin, const Rect& rect, const Offset& origin) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onAreaChange");
        PipelineContext::SetCallBackNode(node);
        func->Execute(oldRect, oldOrigin, rect, origin);
    };
    ViewAbstractModel::GetInstance()->SetOnAreaChanged(std::move(onAreaChanged));
}

#ifndef WEARABLE_PRODUCT
void JSViewAbstract::JsBindPopup(const JSCallbackInfo& info)
{
    if (info.Length() < 2) {
        return;
    }

    if (!info[0]->IsBoolean() && !info[0]->IsObject()) {
        return;
    }

    if (!info[1]->IsObject()) {
        return;
    }

    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    // Set IsShow to popupParam
    if (info[0]->IsBoolean()) {
        popupParam->SetIsShow(info[0]->ToBoolean());
    } else {
        JSRef<JSObject> showObj = JSRef<JSObject>::Cast(info[0]);
        auto callback = ParseDoubleBindCallback(info, showObj);
        popupParam->SetOnStateChange(std::move(callback));
        popupParam->SetIsShow(showObj->GetProperty("value")->ToBoolean());
    }

    // Set popup to popupParam
    auto popupObj = JSRef<JSObject>::Cast(info[1]);

    if (popupObj->GetProperty("message")->IsString()) {
        ParsePopupParam(info, popupObj, popupParam); // Parse PopupOptions param
        ViewAbstractModel::GetInstance()->BindPopup(popupParam, nullptr);
    } else if (!popupObj->GetProperty("builder").IsEmpty()) {
        ParseCustomPopupParam(info, popupObj, popupParam); // Parse CustomPopupOptions param
        auto builderValue = popupObj->GetProperty("builder");
        if (!builderValue->IsObject()) {
            return;
        }

        JSRef<JSObject> builderObj;
        builderObj = JSRef<JSObject>::Cast(builderValue);
        auto builder = builderObj->GetProperty("builder");
        if (!builder->IsFunction()) {
            return;
        }
        auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(builder));
        CHECK_NULL_VOID(builderFunc);
        ViewStackModel::GetInstance()->NewScope();
        builderFunc->Execute();
        auto customNode = ViewStackModel::GetInstance()->Finish();
        ViewAbstractModel::GetInstance()->BindPopup(popupParam, customNode);
    } else {
        return;
    }
}
#endif

void JSViewAbstract::JsLinearGradient(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::OBJECT };
    if (!CheckJSCallbackInfo("LinearGradient", info, checkList)) {
        NG::Gradient newGradient;
        newGradient.CreateGradientWithType(NG::GradientType::LINEAR);
        ViewAbstractModel::GetInstance()->SetLinearGradient(newGradient);
        return;
    }
    NG::Gradient newGradient;
    NewJsLinearGradient(info, newGradient);
    ViewAbstractModel::GetInstance()->SetLinearGradient(newGradient);
}

void JSViewAbstract::NewJsLinearGradient(const JSCallbackInfo& info, NG::Gradient& newGradient)
{
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);
    newGradient.CreateGradientWithType(NG::GradientType::LINEAR);
    // angle
    std::optional<float> degree;
    GetJsAngle("angle", jsObj, degree);
    if (degree) {
        newGradient.GetLinearGradient()->angle = CalcDimension(degree.value(), DimensionUnit::PX);
        degree.reset();
    }
    // direction
    auto direction = static_cast<GradientDirection>(
        jsObj->GetPropertyValue<int32_t>("direction", static_cast<int32_t>(GradientDirection::NONE)));
    switch (direction) {
        case GradientDirection::LEFT:
            newGradient.GetLinearGradient()->linearX = NG::GradientDirection::LEFT;
            break;
        case GradientDirection::RIGHT:
            newGradient.GetLinearGradient()->linearX = NG::GradientDirection::RIGHT;
            break;
        case GradientDirection::TOP:
            newGradient.GetLinearGradient()->linearY = NG::GradientDirection::TOP;
            break;
        case GradientDirection::BOTTOM:
            newGradient.GetLinearGradient()->linearY = NG::GradientDirection::BOTTOM;
            break;
        case GradientDirection::LEFT_TOP:
            newGradient.GetLinearGradient()->linearX = NG::GradientDirection::LEFT;
            newGradient.GetLinearGradient()->linearY = NG::GradientDirection::TOP;
            break;
        case GradientDirection::LEFT_BOTTOM:
            newGradient.GetLinearGradient()->linearX = NG::GradientDirection::LEFT;
            newGradient.GetLinearGradient()->linearY = NG::GradientDirection::BOTTOM;
            break;
        case GradientDirection::RIGHT_TOP:
            newGradient.GetLinearGradient()->linearX = NG::GradientDirection::RIGHT;
            newGradient.GetLinearGradient()->linearY = NG::GradientDirection::TOP;
            break;
        case GradientDirection::RIGHT_BOTTOM:
            newGradient.GetLinearGradient()->linearX = NG::GradientDirection::RIGHT;
            newGradient.GetLinearGradient()->linearY = NG::GradientDirection::BOTTOM;
            break;
        case GradientDirection::NONE:
        case GradientDirection::START_TO_END:
        case GradientDirection::END_TO_START:
        default:
            break;
    }
    auto repeating = jsObj->GetPropertyValue<bool>("repeating", false);
    newGradient.SetRepeat(repeating);
    NewGetJsGradientColorStops(newGradient, jsObj->GetProperty("colors"));
}

void JSViewAbstract::JsRadialGradient(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::OBJECT };
    if (!CheckJSCallbackInfo("JsRadialGradient", info, checkList)) {
        NG::Gradient newGradient;
        newGradient.CreateGradientWithType(NG::GradientType::RADIAL);
        ViewAbstractModel::GetInstance()->SetRadialGradient(newGradient);
        return;
    }
    NG::Gradient newGradient;
    NewJsRadialGradient(info, newGradient);
    ViewAbstractModel::GetInstance()->SetRadialGradient(newGradient);
}

void JSViewAbstract::NewJsRadialGradient(const JSCallbackInfo& info, NG::Gradient& newGradient)
{
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);
    newGradient.CreateGradientWithType(NG::GradientType::RADIAL);
    // center
    JSRef<JSVal> center = jsObj->GetProperty("center");
    if (center->IsArray() && JSRef<JSArray>::Cast(center)->Length() == 2) {
        CalcDimension value;
        JSRef<JSArray> centerArray = JSRef<JSArray>::Cast(center);
        if (ParseJsDimensionVp(centerArray->GetValueAt(0), value)) {
            newGradient.GetRadialGradient()->radialCenterX = CalcDimension(value);
            if (value.Unit() == DimensionUnit::PERCENT) {
                // [0,1] -> [0, 100]
                newGradient.GetRadialGradient()->radialCenterX =
                    CalcDimension(value.Value() * 100.0, DimensionUnit::PERCENT);
            }
        }
        if (ParseJsDimensionVp(centerArray->GetValueAt(1), value)) {
            newGradient.GetRadialGradient()->radialCenterY = CalcDimension(value);
            if (value.Unit() == DimensionUnit::PERCENT) {
                // [0,1] -> [0, 100]
                newGradient.GetRadialGradient()->radialCenterY =
                    CalcDimension(value.Value() * 100.0, DimensionUnit::PERCENT);
            }
        }
    }
    // radius
    CalcDimension radius;
    if (ParseJsDimensionVp(jsObj->GetProperty("radius"), radius)) {
        newGradient.GetRadialGradient()->radialVerticalSize = CalcDimension(radius);
        newGradient.GetRadialGradient()->radialHorizontalSize = CalcDimension(radius);
    }
    // repeating
    auto repeating = jsObj->GetPropertyValue<bool>("repeating", false);
    newGradient.SetRepeat(repeating);
    // color stops
    NewGetJsGradientColorStops(newGradient, jsObj->GetProperty("colors"));
}

void JSViewAbstract::JsSweepGradient(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::OBJECT };
    if (!CheckJSCallbackInfo("JsSweepGradient", info, checkList)) {
        NG::Gradient newGradient;
        newGradient.CreateGradientWithType(NG::GradientType::SWEEP);
        ViewAbstractModel::GetInstance()->SetSweepGradient(newGradient);
        return;
    }

    NG::Gradient newGradient;
    NewJsSweepGradient(info, newGradient);
    ViewAbstractModel::GetInstance()->SetSweepGradient(newGradient);
}

void JSViewAbstract::NewJsSweepGradient(const JSCallbackInfo& info, NG::Gradient& newGradient)
{
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);
    newGradient.CreateGradientWithType(NG::GradientType::SWEEP);
    // center
    JSRef<JSVal> center = jsObj->GetProperty("center");
    if (center->IsArray() && JSRef<JSArray>::Cast(center)->Length() == 2) {
        CalcDimension value;
        JSRef<JSArray> centerArray = JSRef<JSArray>::Cast(center);
        if (ParseJsDimensionVp(centerArray->GetValueAt(0), value)) {
            newGradient.GetSweepGradient()->centerX = CalcDimension(value);
            if (value.Unit() == DimensionUnit::PERCENT) {
                // [0,1] -> [0, 100]
                newGradient.GetSweepGradient()->centerX = CalcDimension(value.Value() * 100.0, DimensionUnit::PERCENT);
            }
        }
        if (ParseJsDimensionVp(centerArray->GetValueAt(1), value)) {
            newGradient.GetSweepGradient()->centerY = CalcDimension(value);
            if (value.Unit() == DimensionUnit::PERCENT) {
                // [0,1] -> [0, 100]
                newGradient.GetSweepGradient()->centerY = CalcDimension(value.Value() * 100.0, DimensionUnit::PERCENT);
            }
        }
    }
    std::optional<float> degree;
    // start
    GetJsAngle("start", jsObj, degree);
    if (degree) {
        CheckAngle(degree);
        newGradient.GetSweepGradient()->startAngle = CalcDimension(degree.value(), DimensionUnit::PX);
        degree.reset();
    }
    // end
    GetJsAngle("end", jsObj, degree);
    if (degree) {
        CheckAngle(degree);
        newGradient.GetSweepGradient()->endAngle = CalcDimension(degree.value(), DimensionUnit::PX);
        degree.reset();
    }
    // rotation
    GetJsAngle("rotation", jsObj, degree);
    if (degree) {
        CheckAngle(degree);
        newGradient.GetSweepGradient()->rotation = CalcDimension(degree.value(), DimensionUnit::PX);
        degree.reset();
    }
    // repeating
    auto repeating = jsObj->GetPropertyValue<bool>("repeating", false);
    newGradient.SetRepeat(repeating);
    // color stops
    NewGetJsGradientColorStops(newGradient, jsObj->GetProperty("colors"));
}

void JSViewAbstract::JsMotionPath(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::OBJECT };
    if (!CheckJSCallbackInfo("JsMotionPath", info, checkList)) {
        ViewAbstractModel::GetInstance()->SetMotionPath(MotionPathOption());
        return;
    }
    MotionPathOption motionPathOption;
    if (ParseMotionPath(info[0], motionPathOption)) {
        ViewAbstractModel::GetInstance()->SetMotionPath(motionPathOption);
    } else {
        LOGI("Parse animation motionPath failed. %{public}s", info[0]->ToString().c_str());
        ViewAbstractModel::GetInstance()->SetMotionPath(MotionPathOption());
    }
}

void JSViewAbstract::JsShadow(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::OBJECT, JSCallbackInfoType::NUMBER };
    if (!CheckJSCallbackInfo("JsShadow", info, checkList)) {
        Shadow shadow;
        std::vector<Shadow> shadows { shadow };
        ViewAbstractModel::GetInstance()->SetBackShadow(shadows);
        return;
    }
    Shadow shadow;
    if (!ParseShadowProps(info[0], shadow)) {
        info.ReturnSelf();
        return;
    }
    std::vector<Shadow> shadows { shadow };
    ViewAbstractModel::GetInstance()->SetBackShadow(shadows);
}

void JSViewAbstract::JsBlendMode(const JSCallbackInfo& info)
{
    if (info.Length() == 0) {
        return;
    }
    BlendMode blendMode = BlendMode::NONE;
    BlendApplyType blendApplyType = BlendApplyType::FAST;
    // for backward compatible, we temporary add a magic number to trigger offscreen, will remove soon
    constexpr int BACKWARD_COMPAT_MAGIC_NUMBER_OFFSCREEN = 1000;
    if (info[0]->IsNumber()) {
        auto blendModeNum = info[0]->ToNumber<int32_t>();
        if (blendModeNum >= static_cast<int>(BlendMode::NONE) &&
            blendModeNum <= static_cast<int>(BlendMode::LUMINOSITY)) {
            blendMode = static_cast<BlendMode>(blendModeNum);
        } else if (blendModeNum == BACKWARD_COMPAT_MAGIC_NUMBER_OFFSCREEN) {
            // backward compatibility code, will remove soon
            blendMode = BlendMode::SRC_OVER;
            blendApplyType = BlendApplyType::OFFSCREEN;
        }
    }
    if (info.Length() >= PARAMETER_LENGTH_SECOND && info[1]->IsNumber()) {
        auto blendApplyTypeNum = info[1]->ToNumber<int32_t>();
        if (blendApplyTypeNum >= static_cast<int>(BlendApplyType::FAST) &&
            blendApplyTypeNum <= static_cast<int>(BlendApplyType::OFFSCREEN)) {
            blendApplyType = static_cast<BlendApplyType>(blendApplyTypeNum);
        }
    }
    ViewAbstractModel::GetInstance()->SetBlendMode(blendMode);
    ViewAbstractModel::GetInstance()->SetBlendApplyType(blendApplyType);
}

void JSViewAbstract::JsGrayScale(const JSCallbackInfo& info)
{
    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        value.SetValue(0.0);
        ViewAbstractModel::GetInstance()->SetGrayScale(value);
        return;
    }

    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }

    if (GreatNotEqual(value.Value(), 1.0)) {
        value.SetValue(1.0);
    }

    ViewAbstractModel::GetInstance()->SetGrayScale(value);
}

void JSViewAbstract::JsBrightness(const JSCallbackInfo& info)
{
    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        value.SetValue(1.0);
        ViewAbstractModel::GetInstance()->SetBrightness(value);
        return;
    }

    ViewAbstractModel::GetInstance()->SetBrightness(value);
}

void JSViewAbstract::JsContrast(const JSCallbackInfo& info)
{
    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        value.SetValue(1.0);
        ViewAbstractModel::GetInstance()->SetContrast(value);
        return;
    }

    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }

    ViewAbstractModel::GetInstance()->SetContrast(value);
}

void JSViewAbstract::JsSaturate(const JSCallbackInfo& info)
{
    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        value.SetValue(1.0);
        ViewAbstractModel::GetInstance()->SetSaturate(value);
        return;
    }

    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }

    ViewAbstractModel::GetInstance()->SetSaturate(value);
}

void JSViewAbstract::JsSepia(const JSCallbackInfo& info)
{
    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        value.SetValue(0.0);
        ViewAbstractModel::GetInstance()->SetSepia(value);
        return;
    }

    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }

    ViewAbstractModel::GetInstance()->SetSepia(value);
}

bool JSViewAbstract::ParseInvertProps(const JSRef<JSVal>& jsValue, InvertVariant& invert)
{
    double invertValue = 0.0;
    if (ParseJsDouble(jsValue, invertValue)) {
        invert = static_cast<float>(invertValue);
        return true;
    }
    auto argsPtrItem = JsonUtil::ParseJsonString(jsValue->ToString());
    if (!argsPtrItem || argsPtrItem->IsNull()) {
        return false;
    }
    InvertOption option;
    double low = 0.0;
    if (ParseJsonDouble(argsPtrItem->GetValue("low"), low)) {
        option.low_ = std::clamp(low, 0.0, 1.0);
    }
    double high = 0.0;
    if (ParseJsonDouble(argsPtrItem->GetValue("high"), high)) {
        option.high_ = std::clamp(high, 0.0, 1.0);
    }
    double threshold = 0.0;
    if (ParseJsonDouble(argsPtrItem->GetValue("threshold"), threshold)) {
        option.threshold_ = std::clamp(threshold, 0.0, 1.0);
    }
    double thresholdRange = 0.0;
    if (ParseJsonDouble(argsPtrItem->GetValue("thresholdRange"), thresholdRange)) {
        option.thresholdRange_ = std::clamp(thresholdRange, 0.0, 1.0);
    }
    invert = option;
    return true;
}

void JSViewAbstract::JsInvert(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::OBJECT, JSCallbackInfoType::NUMBER };
    InvertVariant invert = 0.0f;
    if (!CheckJSCallbackInfo("JsInvert", info, checkList)) {
        ViewAbstractModel::GetInstance()->SetInvert(invert);
        return;
    }
    if (ParseInvertProps(info[0], invert)) {
        ViewAbstractModel::GetInstance()->SetInvert(invert);
    }
    ViewAbstractModel::GetInstance()->SetInvert(invert);
}

void JSViewAbstract::JsHueRotate(const JSCallbackInfo& info)
{
    std::optional<float> degree;
    if (info[0]->IsString()) {
        degree = static_cast<float>(StringUtils::StringToDegree(info[0]->ToString()));
    } else if (info[0]->IsNumber()) {
        degree = static_cast<float>(info[0]->ToNumber<int32_t>());
    } else {
        ViewAbstractModel::GetInstance()->SetHueRotate(0.0);
        return;
    }
    float deg = 0.0f;
    if (degree) {
        deg = degree.value();
        degree.reset();
    }
    deg = std::fmod(deg, ROUND_UNIT);
    if (deg < 0.0f) {
        deg += ROUND_UNIT;
    }
    ViewAbstractModel::GetInstance()->SetHueRotate(deg);
}

void JSViewAbstract::JsClip(const JSCallbackInfo& info)
{
    if (info[0]->IsUndefined()) {
        ViewAbstractModel::GetInstance()->SetClipEdge(false);
        return;
    }
    if (info[0]->IsObject()) {
        JSShapeAbstract* clipShape = JSRef<JSObject>::Cast(info[0])->Unwrap<JSShapeAbstract>();
        if (clipShape == nullptr) {
            return;
        }
        ViewAbstractModel::GetInstance()->SetClipShape(clipShape->GetBasicShape());
    } else if (info[0]->IsBoolean()) {
        ViewAbstractModel::GetInstance()->SetClipEdge(info[0]->ToBoolean());
    }
}

void JSViewAbstract::JsMask(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        ViewAbstractModel::GetInstance()->SetProgressMask(nullptr);
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSVal> typeParam = paramObject->GetProperty("type");
    if (!typeParam->IsNull() && !typeParam->IsUndefined() && typeParam->IsString() &&
        typeParam->ToString() == "ProgressMask") {
        auto progressMask = AceType::MakeRefPtr<NG::ProgressMaskProperty>();
        JSRef<JSVal> jValue = paramObject->GetProperty("value");
        auto value = jValue->IsNumber() ? jValue->ToNumber<float>() : 0.0f;
        if (value < 0.0f) {
            value = 0.0f;
        }
        progressMask->SetValue(value);
        JSRef<JSVal> jTotal = paramObject->GetProperty("total");
        auto total = jTotal->IsNumber() ? jTotal->ToNumber<float>() : DEFAULT_PROGRESS_TOTAL;
        if (total < 0.0f) {
            total = DEFAULT_PROGRESS_TOTAL;
        }
        progressMask->SetMaxValue(total);
        JSRef<JSVal> jColor = paramObject->GetProperty("color");
        Color colorVal;
        if (ParseJsColor(jColor, colorVal)) {
            progressMask->SetColor(colorVal);
        } else {
            RefPtr<ProgressTheme> theme = GetTheme<ProgressTheme>();
            progressMask->SetColor(theme->GetMaskColor());
        }
        ViewAbstractModel::GetInstance()->SetProgressMask(progressMask);
    } else {
        JSShapeAbstract* maskShape = JSRef<JSObject>::Cast(info[0])->Unwrap<JSShapeAbstract>();
        if (maskShape == nullptr) {
            return;
        };
        ViewAbstractModel::GetInstance()->SetMask(maskShape->GetBasicShape());
    }
}

void JSViewAbstract::JsFocusable(const JSCallbackInfo& info)
{
    if (!info[0]->IsBoolean()) {
        return;
    }
    ViewAbstractModel::GetInstance()->SetFocusable(info[0]->ToBoolean());
}

void JSViewAbstract::JsOnFocusMove(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        RefPtr<JsFocusFunction> jsOnFocusMove = AceType::MakeRefPtr<JsFocusFunction>(JSRef<JSFunc>::Cast(args[0]));
        WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
        auto onFocusMove = [execCtx = args.GetExecutionContext(), func = std::move(jsOnFocusMove), node = frameNode](
                               int info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("onFocusMove");
            PipelineContext::SetCallBackNode(node);
            func->Execute(info);
        };
        ViewAbstractModel::GetInstance()->SetOnFocusMove(std::move(onFocusMove));
    }
}

void JSViewAbstract::JsOnKeyEvent(const JSCallbackInfo& args)
{
    if (args[0]->IsUndefined() && IsDisableEventVersion()) {
        ViewAbstractModel::GetInstance()->DisableOnKeyEvent();
        return;
    }
    if (!args[0]->IsFunction()) {
        return;
    }
    RefPtr<JsKeyFunction> JsOnKeyEvent = AceType::MakeRefPtr<JsKeyFunction>(JSRef<JSFunc>::Cast(args[0]));
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto onKeyEvent = [execCtx = args.GetExecutionContext(), func = std::move(JsOnKeyEvent), node = frameNode](
                          KeyEventInfo& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onKey");
        PipelineContext::SetCallBackNode(node);
        func->Execute(info);
    };
    ViewAbstractModel::GetInstance()->SetOnKeyEvent(std::move(onKeyEvent));
}

void JSViewAbstract::JsOnFocus(const JSCallbackInfo& args)
{
    if (args[0]->IsUndefined() && IsDisableEventVersion()) {
        ViewAbstractModel::GetInstance()->DisableOnFocus();
        return;
    }
    if (!args[0]->IsFunction()) {
        return;
    }
    RefPtr<JsFocusFunction> jsOnFocus = AceType::MakeRefPtr<JsFocusFunction>(JSRef<JSFunc>::Cast(args[0]));
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto onFocus = [execCtx = args.GetExecutionContext(), func = std::move(jsOnFocus), node = frameNode]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onFocus");
        PipelineContext::SetCallBackNode(node);
        func->Execute();
    };

    ViewAbstractModel::GetInstance()->SetOnFocus(std::move(onFocus));
}

void JSViewAbstract::JsOnBlur(const JSCallbackInfo& args)
{
    if (args[0]->IsUndefined() && IsDisableEventVersion()) {
        ViewAbstractModel::GetInstance()->DisableOnBlur();
        return;
    }
    if (!args[0]->IsFunction()) {
        return;
    }
    RefPtr<JsFocusFunction> jsOnBlur = AceType::MakeRefPtr<JsFocusFunction>(JSRef<JSFunc>::Cast(args[0]));
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto onBlur = [execCtx = args.GetExecutionContext(), func = std::move(jsOnBlur), node = frameNode]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onBlur");
        PipelineContext::SetCallBackNode(node);
        func->Execute();
    };

    ViewAbstractModel::GetInstance()->SetOnBlur(std::move(onBlur));
}

void JSViewAbstract::JsTabIndex(const JSCallbackInfo& info)
{
    if (!info[0]->IsNumber()) {
        return;
    }
    ViewAbstractModel::GetInstance()->SetTabIndex(info[0]->ToNumber<int32_t>());
}

void JSViewAbstract::JsFocusOnTouch(const JSCallbackInfo& info)
{
    if (!info[0]->IsBoolean()) {
        return;
    }
    auto isFocusOnTouch = info[0]->ToBoolean();
    ViewAbstractModel::GetInstance()->SetFocusOnTouch(isFocusOnTouch);
}

void JSViewAbstract::JsDefaultFocus(const JSCallbackInfo& info)
{
    if (!info[0]->IsBoolean()) {
        return;
    }
    auto isDefaultFocus = info[0]->ToBoolean();
    ViewAbstractModel::GetInstance()->SetDefaultFocus(isDefaultFocus);
}

void JSViewAbstract::JsGroupDefaultFocus(const JSCallbackInfo& info)
{
    if (!info[0]->IsBoolean()) {
        return;
    }
    auto isGroupDefaultFocus = info[0]->ToBoolean();
    ViewAbstractModel::GetInstance()->SetGroupDefaultFocus(isGroupDefaultFocus);
}

void JSViewAbstract::JsKey(const std::string& key)
{
    ViewAbstractModel::GetInstance()->SetInspectorId(key);
}

void JSViewAbstract::JsId(const JSCallbackInfo& info)
{
    if (!info[0]->IsString() || info[0]->IsNull() || info[0]->IsUndefined()) {
        return;
    }
    std::string id = info[0]->ToString();
    if (id.empty()) {
        return;
    }
    JsKey(id);
}

void JSViewAbstract::JsRestoreId(int32_t restoreId)
{
    ViewAbstractModel::GetInstance()->SetRestoreId(restoreId);
}

void JSViewAbstract::JsDebugLine(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::STRING };
    if (!CheckJSCallbackInfo("JsDebugLine", info, checkList)) {
        return;
    }

    ViewAbstractModel::GetInstance()->SetDebugLine(info[0]->ToString());
}

void JSViewAbstract::JsOpacityPassThrough(const JSCallbackInfo& info)
{
    double opacity = 0.0;
    if (!ParseJsDouble(info[0], opacity)) {
        return;
    }

    if ((LessNotEqual(opacity, 0.0)) || opacity > 1) {
        opacity = 1.0;
    }

    ViewAbstractModel::GetInstance()->SetOpacity(opacity, true);
}

void JSViewAbstract::JsTransitionPassThrough(const JSCallbackInfo& info)
{
    if (info.Length() > 1) {
        return;
    }
    if (info.Length() == 0) {
        ViewAbstractModel::GetInstance()->SetTransition(
            NG::TransitionOptions::GetDefaultTransition(TransitionType::ALL));
        return;
    }
    if (!info[0]->IsObject()) {
        return;
    }
    auto obj = JSRef<JSObject>::Cast(info[0]);
    if (!obj->GetProperty("successor_")->IsUndefined()) {
        auto chainedEffect = ParseChainedTransition(obj, info.GetExecutionContext());
        ViewAbstractModel::GetInstance()->SetChainedTransition(chainedEffect);
        return;
    }
    auto options = ParseJsTransition(obj);
    ViewAbstractModel::GetInstance()->SetTransition(options, true);
}

void JSViewAbstract::JsAccessibilityGroup(bool accessible)
{
    ViewAbstractModel::GetInstance()->SetAccessibilityGroup(accessible);
}

void JSViewAbstract::JsAccessibilityText(const std::string& text)
{
    ViewAbstractModel::GetInstance()->SetAccessibilityText(text);
}

void JSViewAbstract::JsAccessibilityDescription(const std::string& description)
{
    std::pair<bool, std::string> autoEventPair(false, "");
    std::pair<bool, std::string> descriptionPair(false, "");
    ParseAccessibilityDescriptionJson(description, autoEventPair, descriptionPair);
    if (descriptionPair.first) {
        ViewAbstractModel::GetInstance()->SetAccessibilityDescription(descriptionPair.second);
    } else {
        ViewAbstractModel::GetInstance()->SetAccessibilityDescription(description);
    }
    if (autoEventPair.first) {
        ViewAbstractModel::GetInstance()->SetAutoEventParam(autoEventPair.second);
    }
}

void JSViewAbstract::ParseAccessibilityDescriptionJson(const std::string& description,
    std::pair<bool, std::string>& autoEventPair, std::pair<bool, std::string>& descriptionPair)
{
    if (description.empty()) {
        return;
    }
    if (!StartWith(description, "{") || !EndWith(description, "}")) {
        return;
    }
    auto jsonObj = JsonUtil::ParseJsonString(description);
    if (!jsonObj || !jsonObj->IsValid() || !jsonObj->IsObject()) {
        return;
    }
    if (jsonObj->Contains("$autoEventParam")) {
        auto param = jsonObj->GetValue("$autoEventParam");
        if (param) {
            autoEventPair = std::make_pair(true, param->ToString());
        }
    }
    if (jsonObj->Contains("$accessibilityDescription")) {
        descriptionPair = std::make_pair(true, jsonObj->GetString("$accessibilityDescription"));
    } else if (jsonObj->Contains("$autoEventParam")) {
        descriptionPair = std::make_pair(true, "");
    }
}

void JSViewAbstract::JsAccessibilityImportance(const std::string& importance)
{
    ViewAbstractModel::GetInstance()->SetAccessibilityImportance(importance);
}

void JSViewAbstract::JsAccessibilityLevel(const std::string& level)
{
    ViewAbstractModel::GetInstance()->SetAccessibilityImportance(level);
}

void JSViewAbstract::JsAccessibilityVirtualNode(const JSCallbackInfo& info)
{
    // parse builder
    if (!info[0]->IsObject()) {
        return;
    }
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
    auto builder = obj->GetProperty("builder");

    auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(builder));
    CHECK_NULL_VOID(builderFunc);
    auto buildFunc = [execCtx = info.GetExecutionContext(), func = std::move(builderFunc)]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("AccessibilityVirtualNode");
        func->Execute();
    };
    NG::ViewAbstractModelNG::GetInstance()->SetAccessibilityVirtualNode(std::move(buildFunc));
}

void JSViewAbstract::JsBackground(const JSCallbackInfo& info)
{
    // Check the parameters
    if (info.Length() <= 0 || !info[0]->IsObject()) {
        return;
    }
    JSRef<JSObject> backgroundObj = JSRef<JSObject>::Cast(info[0]);
    auto builder = backgroundObj->GetProperty("builder");
    if (!builder->IsFunction()) {
        return;
    }
    auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(builder));
    CHECK_NULL_VOID(builderFunc);
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto buildFunc = [execCtx = info.GetExecutionContext(), func = std::move(builderFunc), node = frameNode]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("BindBackground");
        PipelineContext::SetCallBackNode(node);
        func->Execute();
    };
    Alignment alignment = Alignment::CENTER;
    if (info.Length() >= PARAMETER_LENGTH_SECOND && info[1]->IsObject()) {
        JSRef<JSObject> object = JSRef<JSObject>::Cast(info[1]);
        auto align = object->GetProperty("align");
        auto value = align->ToNumber<int32_t>();
        alignment = ParseAlignment(value);
    }
    ViewAbstractModel::GetInstance()->BindBackground(std::move(buildFunc), alignment);
}

void JSViewAbstract::JsBindContextMenu(const JSCallbackInfo& info)
{
    // Check the parameters
    if (info.Length() <= 0 || !info[0]->IsObject()) {
        return;
    }
    JSRef<JSObject> menuObj = JSRef<JSObject>::Cast(info[0]);
    auto builder = menuObj->GetProperty("builder");
    if (!builder->IsFunction()) {
        return;
    }
    auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(builder));
    CHECK_NULL_VOID(builderFunc);

    ResponseType responseType = ResponseType::LONG_PRESS;
    if (info.Length() >= PARAMETER_LENGTH_SECOND && info[1]->IsNumber()) {
        auto response = info[1]->ToNumber<int32_t>();
        responseType = static_cast<ResponseType>(response);
    }
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    std::function<void()> buildFunc = [execCtx = info.GetExecutionContext(), func = std::move(builderFunc),
                                          node = frameNode]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("BuildContextMenu");
        PipelineContext::SetCallBackNode(node);
        func->Execute();
    };

    NG::MenuParam menuParam;
    menuParam.previewMode = MenuPreviewMode::NONE;
    std::function<void()> previewBuildFunc = nullptr;
    if (info.Length() >= PARAMETER_LENGTH_THIRD && info[2]->IsObject()) {
        ParseBindContentOptionParam(info, info[2], menuParam, previewBuildFunc);
    }
    if (responseType != ResponseType::LONG_PRESS) {
        menuParam.previewMode = MenuPreviewMode::NONE;
    }
    menuParam.type = NG::MenuType::CONTEXT_MENU;
    ViewAbstractModel::GetInstance()->BindContextMenu(responseType, buildFunc, menuParam, previewBuildFunc);
}

void JSViewAbstract::JsBindContentCover(const JSCallbackInfo& info)
{
    // parse isShow
    bool isShow = false;
    DoubleBindCallback callback = nullptr;
    if (info[0]->IsBoolean()) {
        isShow = info[0]->ToBoolean();
    } else if (info[0]->IsObject()) {
        JSRef<JSObject> callbackObj = JSRef<JSObject>::Cast(info[0]);
        callback = ParseDoubleBindCallback(info, callbackObj);
        auto isShowObj = callbackObj->GetProperty("value");
        isShow = isShowObj->IsBoolean() ? isShowObj->ToBoolean() : false;
    }

    // parse builder
    if (!info[1]->IsObject()) {
        return;
    }
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[1]);
    auto builder = obj->GetProperty("builder");
    if (!builder->IsFunction()) {
        return;
    }
    auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(builder));
    CHECK_NULL_VOID(builderFunc);
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto buildFunc = [execCtx = info.GetExecutionContext(), func = std::move(builderFunc), node = frameNode]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("BindContentCover");
        PipelineContext::SetCallBackNode(node);
        func->Execute();
    };

    // parse ModalTransition
    NG::ModalStyle modalStyle;
    modalStyle.modalTransition = NG::ModalTransition::DEFAULT;
    std::function<void()> onShowCallback;
    std::function<void()> onDismissCallback;
    if (info.Length() == 3) {
        if (info[2]->IsObject()) {
            ParseOverlayCallback(info[2], onShowCallback, onDismissCallback);
            ParseModalStyle(info[2], modalStyle);
        } else if (info[2]->IsNumber()) {
            auto transitionNumber = info[2]->ToNumber<int32_t>();
            if (transitionNumber >= 0 && transitionNumber <= 2) {
                modalStyle.modalTransition = static_cast<NG::ModalTransition>(transitionNumber);
            }
        }
    }
    ViewAbstractModel::GetInstance()->BindContentCover(isShow, std::move(callback), std::move(buildFunc), modalStyle,
        std::move(onShowCallback), std::move(onDismissCallback));
}

void JSViewAbstract::ParseModalStyle(const JSRef<JSObject>& paramObj, NG::ModalStyle& modalStyle)
{
    auto modalTransition = paramObj->GetProperty("modalTransition");
    auto backgroundColor = paramObj->GetProperty("backgroundColor");
    if (modalTransition->IsNumber()) {
        auto transitionNumber = modalTransition->ToNumber<int32_t>();
        if (transitionNumber >= 0 && transitionNumber <= 2) {
            modalStyle.modalTransition = static_cast<NG::ModalTransition>(transitionNumber);
        }
    }
    Color color;
    if (ParseJsColor(backgroundColor, color)) {
        modalStyle.backgroundColor = color;
    }
}

void JSViewAbstract::JsBindSheet(const JSCallbackInfo& info)
{
    // parse isShow
    bool isShow = false;
    DoubleBindCallback callback = nullptr;
    if (info[0]->IsBoolean()) {
        isShow = info[0]->ToBoolean();
    } else if (info[0]->IsObject()) {
        JSRef<JSObject> callbackObj = JSRef<JSObject>::Cast(info[0]);
        callback = ParseDoubleBindCallback(info, callbackObj);
        auto isShowObj = callbackObj->GetProperty("value");
        isShow = isShowObj->IsBoolean() ? isShowObj->ToBoolean() : false;
    }

    // parse builder
    if (!info[1]->IsObject()) {
        return;
    }
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[1]);
    auto builder = obj->GetProperty("builder");
    if (!builder->IsFunction()) {
        return;
    }
    auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(builder));
    CHECK_NULL_VOID(builderFunc);
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto buildFunc = [execCtx = info.GetExecutionContext(), func = std::move(builderFunc), node = frameNode]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("BindSheet");
        PipelineContext::SetCallBackNode(node);
        func->Execute();
    };

    // parse SheetStyle and callbacks
    NG::SheetStyle sheetStyle;
    sheetStyle.sheetMode = NG::SheetMode::LARGE;
    sheetStyle.showDragBar = true;
    sheetStyle.showCloseIcon = true;
    std::function<void()> onShowCallback;
    std::function<void()> onDismissCallback;
    std::function<void()> shouldDismissFunc;
    std::function<void()> titleBuilderFunction;
    if (info.Length() == 3) {
        if (info[2]->IsObject()) {
            ParseSheetCallback(info[2], onShowCallback, onDismissCallback, shouldDismissFunc);
            ParseSheetStyle(info[2], sheetStyle);
            ParseSheetTitle(info[2], sheetStyle, titleBuilderFunction);
        }
    }
    ViewAbstractModel::GetInstance()->BindSheet(isShow, std::move(callback), std::move(buildFunc),
        std::move(titleBuilderFunction), sheetStyle, std::move(onShowCallback), std::move(onDismissCallback),
        std::move(shouldDismissFunc));
}

void JSViewAbstract::ParseSheetStyle(const JSRef<JSObject>& paramObj, NG::SheetStyle& sheetStyle)
{
    auto height = paramObj->GetProperty("height");
    auto showDragBar = paramObj->GetProperty("dragBar");
    auto backgroundColor = paramObj->GetProperty("backgroundColor");
    auto maskColor = paramObj->GetProperty("maskColor");
    auto sheetDetents = paramObj->GetProperty("detents");
    auto backgroundBlurStyle = paramObj->GetProperty("blurStyle");
    auto showCloseIcon = paramObj->GetProperty("showClose");
    auto type = paramObj->GetProperty("preferType");
    auto interactive = paramObj->GetProperty("enableOutsideInteractive");

    std::vector<NG::SheetHeight> detents;
    if (ParseSheetDetents(sheetDetents, detents)) {
        sheetStyle.detents = detents;
    }
    BlurStyleOption styleOption;
    if (ParseSheetBackgroundBlurStyle(backgroundBlurStyle, styleOption)) {
        sheetStyle.backgroundBlurStyle = styleOption;
    }
    bool showClose = true;
    if (showCloseIcon->IsNull() || showCloseIcon->IsUndefined()) {
        sheetStyle.showCloseIcon = showClose;
    } else {
        if (ParseJsBool(showCloseIcon, showClose)) {
            sheetStyle.showCloseIcon = showClose;
        }
    }
    bool isInteractive = false;
    if (ParseJsBool(interactive, isInteractive)) {
        sheetStyle.interactive = isInteractive;
    }
    if (showDragBar->IsNull() || showDragBar->IsUndefined()) {
        sheetStyle.showDragBar = true;
    } else {
        if (showDragBar->IsBoolean()) {
            sheetStyle.showDragBar = showDragBar->ToBoolean();
        }
    }
    if (type->IsNull() || type->IsUndefined()) {
        sheetStyle.sheetType.reset();
    } else {
        if (type->IsNumber()) {
            auto sheetType = type->ToNumber<int32_t>();
            if (sheetType >= static_cast<int>(NG::SheetType::SHEET_BOTTOM) &&
                sheetType <= static_cast<int>(NG::SheetType::SHEET_POPUP)) {
                sheetStyle.sheetType = static_cast<NG::SheetType>(sheetType);
            }
        }
    }
    Color color;
    if (ParseJsColor(backgroundColor, color)) {
        sheetStyle.backgroundColor = color;
    }
    // parse maskColor
    Color parseMaskColor;
    if (!maskColor->IsNull() && !maskColor->IsUndefined() && JSViewAbstract::ParseJsColor(maskColor, parseMaskColor)) {
        sheetStyle.maskColor = std::move(parseMaskColor);
    }
    CalcDimension sheetHeight;
    if (height->IsString()) {
        std::string heightStr = height->ToString();
        // Remove all " ".
        heightStr.erase(std::remove(heightStr.begin(), heightStr.end(), ' '), heightStr.end());
        std::transform(heightStr.begin(), heightStr.end(), heightStr.begin(), ::tolower);
        if (heightStr == SHEET_HEIGHT_MEDIUM) {
            sheetStyle.sheetMode = NG::SheetMode::MEDIUM;
            sheetStyle.height.reset();
            return;
        }
        if (heightStr == SHEET_HEIGHT_LARGE) {
            sheetStyle.sheetMode = NG::SheetMode::LARGE;
            sheetStyle.height.reset();
            return;
        }
        if (heightStr == SHEET_HEIGHT_FITCONTENT) {
            sheetStyle.sheetMode = NG::SheetMode::AUTO;
            sheetStyle.height.reset();
            return;
        }
        if (heightStr.find("calc") != std::string::npos) {
            sheetHeight = CalcDimension(heightStr, DimensionUnit::CALC);
        } else {
            sheetHeight = StringUtils::StringToDimensionWithUnit(heightStr, DimensionUnit::VP, -1.0);
        }
        if (sheetHeight.Value() < 0) {
            sheetStyle.sheetMode = NG::SheetMode::LARGE;
            sheetStyle.height.reset();
            return;
        }
    }
    if (!ParseJsDimensionVpNG(height, sheetHeight)) {
        sheetStyle.sheetMode = NG::SheetMode::LARGE;
        sheetStyle.height.reset();
    } else {
        sheetStyle.height = sheetHeight;
        sheetStyle.sheetMode.reset();
    }
}

bool JSViewAbstract::ParseSheetDetents(const JSRef<JSVal>& args, std::vector<NG::SheetHeight>& sheetDetents)
{
    if (!args->IsArray()) {
        return false;
    }
    JSRef<JSArray> array = JSRef<JSArray>::Cast(args);
    NG::SheetHeight sheetDetent;
    for (size_t i = 0; i < array->Length(); i++) {
        ParseSheetDetentHeight(array->GetValueAt(i), sheetDetent);
        if ((!sheetDetent.height.has_value()) && (!sheetDetent.sheetMode.has_value())) {
            continue;
        }
        sheetDetents.emplace_back(sheetDetent);
        sheetDetent.height.reset();
        sheetDetent.sheetMode.reset();
    }
    return true;
}

void JSViewAbstract::ParseSheetDetentHeight(const JSRef<JSVal>& args, NG::SheetHeight& detent)
{
    CalcDimension sheetHeight;
    if (args->IsString()) {
        std::string heightStr = args->ToString();
        // Remove all " ".
        heightStr.erase(std::remove(heightStr.begin(), heightStr.end(), ' '), heightStr.end());
        std::transform(heightStr.begin(), heightStr.end(), heightStr.begin(), ::tolower);
        if (heightStr == SHEET_HEIGHT_MEDIUM) {
            detent.sheetMode = NG::SheetMode::MEDIUM;
            detent.height.reset();
            return;
        }
        if (heightStr == SHEET_HEIGHT_LARGE) {
            detent.sheetMode = NG::SheetMode::LARGE;
            detent.height.reset();
            return;
        }
        if (heightStr == SHEET_HEIGHT_FITCONTENT) {
            detent.sheetMode = NG::SheetMode::AUTO;
            detent.height.reset();
            return;
        }
        if (heightStr.find("calc") != std::string::npos) {
            sheetHeight = CalcDimension(heightStr, DimensionUnit::CALC);
        } else {
            sheetHeight = StringUtils::StringToDimensionWithUnit(heightStr, DimensionUnit::VP, -1.0);
        }
        if (sheetHeight.Value() < 0) {
            detent.sheetMode = NG::SheetMode::LARGE;
            detent.height.reset();
            return;
        }
    }
    if (!ParseJsDimensionVpNG(args, sheetHeight)) {
        detent.sheetMode = NG::SheetMode::LARGE;
        detent.height.reset();
    } else {
        detent.height = sheetHeight;
        detent.sheetMode.reset();
    }
}

bool JSViewAbstract::ParseSheetBackgroundBlurStyle(const JSRef<JSVal>& args, BlurStyleOption& blurStyleOptions)
{
    if (args->IsNumber()) {
        auto sheetBlurStyle = args->ToNumber<int32_t>();
        if (sheetBlurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
            sheetBlurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
            blurStyleOptions.blurStyle = static_cast<BlurStyle>(sheetBlurStyle);
        } else {
            return false;
        }
    } else {
        return false;
    }
    return true;
}

void JSViewAbstract::ParseSheetCallback(const JSRef<JSObject>& paramObj, std::function<void()>& onAppear,
    std::function<void()>& onDisappear, std::function<void()>& shouldDismiss)
{
    auto showCallback = paramObj->GetProperty("onAppear");
    auto dismissCallback = paramObj->GetProperty("onDisappear");
    auto shouldDismissFunc = paramObj->GetProperty("shouldDismiss");
    if (showCallback->IsFunction()) {
        RefPtr<JsFunction> jsFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(showCallback));
        onAppear = [func = std::move(jsFunc)]() { func->Execute(); };
    }
    if (dismissCallback->IsFunction()) {
        RefPtr<JsFunction> jsFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(dismissCallback));
        onDisappear = [func = std::move(jsFunc)]() { func->Execute(); };
    }
    if (shouldDismissFunc->IsFunction()) {
        RefPtr<JsFunction> jsFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(shouldDismissFunc));
        shouldDismiss = [func = std::move(jsFunc)]() {
            JSRef<JSObjTemplate> objectTemplate = JSRef<JSObjTemplate>::New();
            objectTemplate->SetInternalFieldCount(1);
            JSRef<JSObject> dismissObj = objectTemplate->NewInstance();
            dismissObj->SetPropertyObject(
                "dismiss", JSRef<JSFunc>::New<FunctionCallback>(JSViewAbstract::JsDismissSheet));
            JSRef<JSVal> newJSVal = JSRef<JSObject>::Cast(dismissObj);
            func->ExecuteJS(1, &newJSVal);
        };
    }
}

void JSViewAbstract::ParseSheetTitle(
    const JSRef<JSObject>& paramObj, NG::SheetStyle& sheetStyle, std::function<void()>& titleBuilderFunction)
{
    auto title = paramObj->GetProperty("title");
    std::string mainTitle;
    std::string subtitle;
    if (title->IsFunction()) {
        sheetStyle.isTitleBuilder = true;
        auto titleBuilderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(title));
        CHECK_NULL_VOID(titleBuilderFunc);
        titleBuilderFunction = [func = std::move(titleBuilderFunc)]() {
            ACE_SCORING_EVENT("BindSheet");
            func->Execute();
        };
    } else if (title->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(title);
        sheetStyle.isTitleBuilder = false;
        auto sheetTitle = obj->GetProperty("title");
        auto sheetSubtitle = obj->GetProperty("subtitle");
        if (ParseJsString(sheetTitle, mainTitle)) {
            sheetStyle.sheetTitle = mainTitle;
        }
        if (ParseJsString(sheetSubtitle, subtitle)) {
            sheetStyle.sheetSubtitle = subtitle;
        }
    }
}

panda::Local<panda::JSValueRef> JSViewAbstract::JsDismissSheet(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    ViewAbstractModel::GetInstance()->DismissSheet();
    return JSValueRef::Undefined(runtimeCallInfo->GetVM());
}

void JSViewAbstract::ParseOverlayCallback(
    const JSRef<JSObject>& paramObj, std::function<void()>& onAppear, std::function<void()>& onDisappear)
{
    auto showCallback = paramObj->GetProperty("onAppear");
    auto dismissCallback = paramObj->GetProperty("onDisappear");
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    if (showCallback->IsFunction()) {
        RefPtr<JsFunction> jsFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(showCallback));
        onAppear = [func = std::move(jsFunc), node = frameNode]() {
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
    }
    if (dismissCallback->IsFunction()) {
        RefPtr<JsFunction> jsFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(dismissCallback));
        onDisappear = [func = std::move(jsFunc), node = frameNode]() {
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
    }
}

void JSViewAbstract::JSCreateAnimatableProperty(const JSCallbackInfo& info)
{
    if (info.Length() < 3 || !info[0]->IsString()) { /* 3:args number */
        return;
    }

    JSRef<JSVal> callback = info[2]; /* 2:args index */
    if (!callback->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    std::string propertyName = info[0]->ToString();
    if (info[1]->IsNumber()) {
        float numValue = info[1]->ToNumber<float>();
        std::function<void(float)> onCallbackEvent;
        RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(callback));
        onCallbackEvent = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), id = Container::CurrentId(),
                              node = frameNode](const float val) {
            ContainerScope scope(id);
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto newJSVal = JSRef<JSVal>::Make(ToJSValue(val));
            PipelineContext::SetCallBackNode(node);
            func->ExecuteJS(1, &newJSVal);
        };
        ViewAbstractModel::GetInstance()->CreateAnimatablePropertyFloat(propertyName, numValue, onCallbackEvent);
    } else if (info[1]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[1]);
        RefPtr<JSAnimatableArithmetic> animatableArithmeticImpl =
            AceType::MakeRefPtr<JSAnimatableArithmetic>(obj, info.GetExecutionContext());
        RefPtr<CustomAnimatableArithmetic> animatableArithmetic =
            AceType::DynamicCast<CustomAnimatableArithmetic>(animatableArithmeticImpl);
        std::function<void(const RefPtr<NG::CustomAnimatableArithmetic>&)> onCallbackEvent;
        RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(callback));
        onCallbackEvent = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), id = Container::CurrentId(),
                              node = frameNode](const RefPtr<NG::CustomAnimatableArithmetic>& value) {
            ContainerScope scope(id);
            RefPtr<JSAnimatableArithmetic> impl = AceType::DynamicCast<JSAnimatableArithmetic>(value);
            if (!impl) {
                return;
            }
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto newJSVal = JSRef<JSVal>(impl->GetObject());
            PipelineContext::SetCallBackNode(node);
            func->ExecuteJS(1, &newJSVal);
        };
        ViewAbstractModel::GetInstance()->CreateAnimatableArithmeticProperty(
            propertyName, animatableArithmetic, onCallbackEvent);
    }
}

void JSViewAbstract::JSUpdateAnimatableProperty(const JSCallbackInfo& info)
{
    if (info.Length() < 2 || !info[0]->IsString()) { /* 2:args number */
        return;
    }

    std::string propertyName = info[0]->ToString();
    float numValue = 0.0;
    if (info[1]->IsNumber()) {
        numValue = info[1]->ToNumber<float>();
        ViewAbstractModel::GetInstance()->UpdateAnimatablePropertyFloat(propertyName, numValue);
    } else if (info[1]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[1]);
        RefPtr<JSAnimatableArithmetic> animatableArithmeticImpl =
            AceType::MakeRefPtr<JSAnimatableArithmetic>(obj, info.GetExecutionContext());
        RefPtr<CustomAnimatableArithmetic> animatableArithmetic =
            AceType::DynamicCast<CustomAnimatableArithmetic>(animatableArithmeticImpl);
        ViewAbstractModel::GetInstance()->UpdateAnimatableArithmeticProperty(propertyName, animatableArithmetic);
    }
}

void JSViewAbstract::JsExpandSafeArea(const JSCallbackInfo& info)
{
    NG::SafeAreaExpandOpts opts { .type = NG::SAFE_AREA_TYPE_ALL, .edges = NG::SAFE_AREA_EDGE_ALL };
    if (info.Length() >= 1 && info[0]->IsArray()) {
        auto paramArray = JSRef<JSArray>::Cast(info[0]);
        uint32_t safeAreaType = NG::SAFE_AREA_TYPE_NONE;
        for (size_t i = 0; i < paramArray->Length(); ++i) {
            if (!paramArray->GetValueAt(i)->IsNumber() ||
                paramArray->GetValueAt(i)->ToNumber<uint32_t>() >= SAFE_AREA_TYPE_LIMIT) {
                safeAreaType = NG::SAFE_AREA_TYPE_ALL;
                break;
            }
            safeAreaType |= (1 << paramArray->GetValueAt(i)->ToNumber<uint32_t>());
        }
        opts.type = safeAreaType;
    }
    if (info.Length() >= 2 && info[1]->IsArray()) {
        auto paramArray = JSRef<JSArray>::Cast(info[1]);
        uint32_t safeAreaEdge = NG::SAFE_AREA_EDGE_NONE;
        for (size_t i = 0; i < paramArray->Length(); ++i) {
            if (!paramArray->GetValueAt(i)->IsNumber() ||
                paramArray->GetValueAt(i)->ToNumber<uint32_t>() >= SAFE_AREA_EDGE_LIMIT) {
                safeAreaEdge = NG::SAFE_AREA_EDGE_ALL;
                break;
            }
            safeAreaEdge |= (1 << paramArray->GetValueAt(i)->ToNumber<uint32_t>());
        }
        opts.edges = safeAreaEdge;
    }

    ViewAbstractModel::GetInstance()->UpdateSafeAreaExpandOpts(opts);
}

void JSViewAbstract::JsPointLight(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }

    JSRef<JSObject> object = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSObject> lightSource = object->GetProperty("lightSource");
    if (!lightSource->IsUndefined()) {
        JSRef<JSVal> positionX = lightSource->GetProperty("positionX");
        JSRef<JSVal> positionY = lightSource->GetProperty("positionY");
        JSRef<JSVal> positionZ = lightSource->GetProperty("positionZ");
        JSRef<JSVal> intensity = lightSource->GetProperty("intensity");

        CalcDimension dimPositionX, dimPositionY, dimPositionZ;
        if (ParseJsDimensionVp(positionX, dimPositionX) && ParseJsDimensionVp(positionY, dimPositionY) &&
            ParseJsDimensionVp(positionZ, dimPositionZ)) {
            ViewAbstractModel::GetInstance()->SetLightPosition(dimPositionX, dimPositionY, dimPositionZ);
        }

        if (intensity->IsNumber()) {
            float intensityValue = intensity->ToNumber<float>();
            ViewAbstractModel::GetInstance()->SetLightIntensity(intensityValue);
        }
    }

    auto resourceWrapper = CreateResourceWrapper();
    if (!resourceWrapper) {
        return;
    }
    double bloomRadius = resourceWrapper->GetDoubleByName(BLOOM_RADIUS_SYS_RES_NAME);
    Color bloomColor = resourceWrapper->GetColorByName(BLOOM_COLOR_SYS_RES_NAME);
    Dimension illuminatedBorderWidth = resourceWrapper->GetDimensionByName(ILLUMINATED_BORDER_WIDTH_SYS_RES_NAME);

    JSRef<JSVal> illuminated = object->GetProperty("illuminated");
    if (illuminated->IsNumber()) {
        uint32_t illuminatedValue = illuminated->ToNumber<uint32_t>();
        ViewAbstractModel::GetInstance()->SetLightIlluminated(illuminatedValue);
        ViewAbstractModel::GetInstance()->SetIlluminatedBorderWidth(illuminatedBorderWidth);
    }

    JSRef<JSVal> bloom = object->GetProperty("bloom");
    if (bloom->IsNumber()) {
        float bloomValue = bloom->ToNumber<float>();
        ViewAbstractModel::GetInstance()->SetBloom(bloomValue);

        Shadow shadow;
        shadow.SetBlurRadius(bloomValue * bloomRadius);
        shadow.SetColor(bloomColor);
        std::vector<Shadow> shadows { shadow };
        ViewAbstractModel::GetInstance()->SetBackShadow(shadows);
    }
}

void JSViewAbstract::JSBind(BindingTarget globalObj)
{
    JSClass<JSViewAbstract>::Declare("JSViewAbstract");

    // static methods
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSViewAbstract>::StaticMethod("pop", &JSViewAbstract::Pop, opt);

    JSClass<JSViewAbstract>::StaticMethod("width", &JSViewAbstract::JsWidth);
    JSClass<JSViewAbstract>::StaticMethod("height", &JSViewAbstract::JsHeight);
    JSClass<JSViewAbstract>::StaticMethod("responseRegion", &JSViewAbstract::JsResponseRegion);
    JSClass<JSViewAbstract>::StaticMethod("mouseResponseRegion", &JSViewAbstract::JsMouseResponseRegion);
    JSClass<JSViewAbstract>::StaticMethod("size", &JSViewAbstract::JsSize);
    JSClass<JSViewAbstract>::StaticMethod("constraintSize", &JSViewAbstract::JsConstraintSize);
    JSClass<JSViewAbstract>::StaticMethod("layoutPriority", &JSViewAbstract::JsLayoutPriority);
    JSClass<JSViewAbstract>::StaticMethod("layoutWeight", &JSViewAbstract::JsLayoutWeight);

    JSClass<JSViewAbstract>::StaticMethod("margin", &JSViewAbstract::JsMargin);
    JSClass<JSViewAbstract>::StaticMethod("marginTop", &JSViewAbstract::SetMarginTop, opt);
    JSClass<JSViewAbstract>::StaticMethod("marginBottom", &JSViewAbstract::SetMarginBottom, opt);
    JSClass<JSViewAbstract>::StaticMethod("marginLeft", &JSViewAbstract::SetMarginLeft, opt);
    JSClass<JSViewAbstract>::StaticMethod("marginRight", &JSViewAbstract::SetMarginRight, opt);

    JSClass<JSViewAbstract>::StaticMethod("padding", &JSViewAbstract::JsPadding);
    JSClass<JSViewAbstract>::StaticMethod("paddingTop", &JSViewAbstract::SetPaddingTop, opt);
    JSClass<JSViewAbstract>::StaticMethod("paddingBottom", &JSViewAbstract::SetPaddingBottom, opt);
    JSClass<JSViewAbstract>::StaticMethod("paddingLeft", &JSViewAbstract::SetPaddingLeft, opt);
    JSClass<JSViewAbstract>::StaticMethod("paddingRight", &JSViewAbstract::SetPaddingRight, opt);

    JSClass<JSViewAbstract>::StaticMethod("foregroundColor", &JSViewAbstract::JsForegroundColor);
    JSClass<JSViewAbstract>::StaticMethod("backgroundColor", &JSViewAbstract::JsBackgroundColor);
    JSClass<JSViewAbstract>::StaticMethod("backgroundImage", &JSViewAbstract::JsBackgroundImage);
    JSClass<JSViewAbstract>::StaticMethod("backgroundImageSize", &JSViewAbstract::JsBackgroundImageSize);
    JSClass<JSViewAbstract>::StaticMethod("backgroundImagePosition", &JSViewAbstract::JsBackgroundImagePosition);
    JSClass<JSViewAbstract>::StaticMethod("backgroundBlurStyle", &JSViewAbstract::JsBackgroundBlurStyle);
    JSClass<JSViewAbstract>::StaticMethod("backgroundEffect", &JSViewAbstract::JsBackgroundEffect);
    JSClass<JSViewAbstract>::StaticMethod("foregroundBlurStyle", &JSViewAbstract::JsForegroundBlurStyle);
    JSClass<JSViewAbstract>::StaticMethod("lightUpEffect", &JSViewAbstract::JsLightUpEffect);
    JSClass<JSViewAbstract>::StaticMethod("sphericalEffect", &JSViewAbstract::JsSphericalEffect);
    JSClass<JSViewAbstract>::StaticMethod("pixelStretchEffect", &JSViewAbstract::JsPixelStretchEffect);
    JSClass<JSViewAbstract>::StaticMethod("outline", &JSViewAbstract::JsOutline);
    JSClass<JSViewAbstract>::StaticMethod("outlineWidth", &JSViewAbstract::JsOutlineWidth);
    JSClass<JSViewAbstract>::StaticMethod("outlineStyle", &JSViewAbstract::JsOutlineStyle);
    JSClass<JSViewAbstract>::StaticMethod("outlineColor", &JSViewAbstract::JsOutlineColor);
    JSClass<JSViewAbstract>::StaticMethod("outlineRadius", &JSViewAbstract::JsOutlineRadius);
    JSClass<JSViewAbstract>::StaticMethod("border", &JSViewAbstract::JsBorder);
    JSClass<JSViewAbstract>::StaticMethod("borderWidth", &JSViewAbstract::JsBorderWidth);
    JSClass<JSViewAbstract>::StaticMethod("borderColor", &JSViewAbstract::JsBorderColor);
    JSClass<JSViewAbstract>::StaticMethod("borderRadius", &JSViewAbstract::JsBorderRadius);
    JSClass<JSViewAbstract>::StaticMethod("borderStyle", &JSViewAbstract::JsBorderStyle);
    JSClass<JSViewAbstract>::StaticMethod("borderImage", &JSViewAbstract::JsBorderImage);

    JSClass<JSViewAbstract>::StaticMethod("scale", &JSViewAbstract::JsScale);
    JSClass<JSViewAbstract>::StaticMethod("scaleX", &JSViewAbstract::JsScaleX);
    JSClass<JSViewAbstract>::StaticMethod("scaleY", &JSViewAbstract::JsScaleY);
    JSClass<JSViewAbstract>::StaticMethod("opacity", &JSViewAbstract::JsOpacity);
    JSClass<JSViewAbstract>::StaticMethod("rotate", &JSViewAbstract::JsRotate);
    JSClass<JSViewAbstract>::StaticMethod("rotateX", &JSViewAbstract::JsRotateX);
    JSClass<JSViewAbstract>::StaticMethod("rotateY", &JSViewAbstract::JsRotateY);
    JSClass<JSViewAbstract>::StaticMethod("translate", &JSViewAbstract::JsTranslate);
    JSClass<JSViewAbstract>::StaticMethod("translateX", &JSViewAbstract::JsTranslateX);
    JSClass<JSViewAbstract>::StaticMethod("translateY", &JSViewAbstract::JsTranslateY);
    JSClass<JSViewAbstract>::StaticMethod("transform", &JSViewAbstract::JsTransform);
    JSClass<JSViewAbstract>::StaticMethod("transition", &JSViewAbstract::JsTransition);

    JSClass<JSViewAbstract>::StaticMethod("align", &JSViewAbstract::JsAlign);
    JSClass<JSViewAbstract>::StaticMethod("position", &JSViewAbstract::JsPosition);
    JSClass<JSViewAbstract>::StaticMethod("markAnchor", &JSViewAbstract::JsMarkAnchor);
    JSClass<JSViewAbstract>::StaticMethod("offset", &JSViewAbstract::JsOffset);
    JSClass<JSViewAbstract>::StaticMethod("enabled", &JSViewAbstract::JsEnabled);
    JSClass<JSViewAbstract>::StaticMethod("aspectRatio", &JSViewAbstract::JsAspectRatio);
    JSClass<JSViewAbstract>::StaticMethod("overlay", &JSViewAbstract::JsOverlay);

    JSClass<JSViewAbstract>::StaticMethod("blur", &JSViewAbstract::JsBlur);
    JSClass<JSViewAbstract>::StaticMethod("useEffect", &JSViewAbstract::JsUseEffect);
    JSClass<JSViewAbstract>::StaticMethod("useShadowBatching", &JSViewAbstract::JsUseShadowBatching);
    JSClass<JSViewAbstract>::StaticMethod("colorBlend", &JSViewAbstract::JsColorBlend);
    JSClass<JSViewAbstract>::StaticMethod("backdropBlur", &JSViewAbstract::JsBackdropBlur);
    JSClass<JSViewAbstract>::StaticMethod("linearGradientBlur", &JSViewAbstract::JsLinearGradientBlur);
    JSClass<JSViewAbstract>::StaticMethod("backgroundBrightness", &JSViewAbstract::JsBackgroundBrightness);
    JSClass<JSViewAbstract>::StaticMethod("windowBlur", &JSViewAbstract::JsWindowBlur);
    JSClass<JSViewAbstract>::StaticMethod("visibility", &JSViewAbstract::SetVisibility);
    JSClass<JSViewAbstract>::StaticMethod("flexBasis", &JSViewAbstract::JsFlexBasis);
    JSClass<JSViewAbstract>::StaticMethod("flexGrow", &JSViewAbstract::JsFlexGrow);
    JSClass<JSViewAbstract>::StaticMethod("flexShrink", &JSViewAbstract::JsFlexShrink);
    JSClass<JSViewAbstract>::StaticMethod("alignSelf", &JSViewAbstract::JsAlignSelf);
    JSClass<JSViewAbstract>::StaticMethod("displayPriority", &JSViewAbstract::JsDisplayPriority);
    JSClass<JSViewAbstract>::StaticMethod("useAlign", &JSViewAbstract::JsUseAlign);
    JSClass<JSViewAbstract>::StaticMethod("zIndex", &JSViewAbstract::JsZIndex);
    JSClass<JSViewAbstract>::StaticMethod("sharedTransition", &JSViewAbstract::JsSharedTransition);
    JSClass<JSViewAbstract>::StaticMethod("direction", &JSViewAbstract::SetDirection, opt);
#ifndef WEARABLE_PRODUCT
    JSClass<JSViewAbstract>::StaticMethod("bindPopup", &JSViewAbstract::JsBindPopup);
#endif

    JSClass<JSViewAbstract>::StaticMethod("background", &JSViewAbstract::JsBackground);
    JSClass<JSViewAbstract>::StaticMethod("bindMenu", &JSViewAbstract::JsBindMenu);
    JSClass<JSViewAbstract>::StaticMethod("bindContextMenu", &JSViewAbstract::JsBindContextMenu);
    JSClass<JSViewAbstract>::StaticMethod("bindContentCover", &JSViewAbstract::JsBindContentCover);
    JSClass<JSViewAbstract>::StaticMethod("bindSheet", &JSViewAbstract::JsBindSheet);
    JSClass<JSViewAbstract>::StaticMethod("draggable", &JSViewAbstract::JsSetDraggable);
    JSClass<JSViewAbstract>::StaticMethod("dragPreviewOptions", &JSViewAbstract::JsSetDragPreviewOptions);
    JSClass<JSViewAbstract>::StaticMethod("onDragStart", &JSViewAbstract::JsOnDragStart);
    JSClass<JSViewAbstract>::StaticMethod("onDragEnter", &JSViewAbstract::JsOnDragEnter);
    JSClass<JSViewAbstract>::StaticMethod("onDragMove", &JSViewAbstract::JsOnDragMove);
    JSClass<JSViewAbstract>::StaticMethod("onDragLeave", &JSViewAbstract::JsOnDragLeave);
    JSClass<JSViewAbstract>::StaticMethod("onDrop", &JSViewAbstract::JsOnDrop);
    JSClass<JSViewAbstract>::StaticMethod("onDragEnd", &JSViewAbstract::JsOnDragEnd);

    JSClass<JSViewAbstract>::StaticMethod("linearGradient", &JSViewAbstract::JsLinearGradient);
    JSClass<JSViewAbstract>::StaticMethod("sweepGradient", &JSViewAbstract::JsSweepGradient);
    JSClass<JSViewAbstract>::StaticMethod("radialGradient", &JSViewAbstract::JsRadialGradient);
    JSClass<JSViewAbstract>::StaticMethod("motionPath", &JSViewAbstract::JsMotionPath);
    JSClass<JSViewAbstract>::StaticMethod("gridSpan", &JSViewAbstract::JsGridSpan);
    JSClass<JSViewAbstract>::StaticMethod("gridOffset", &JSViewAbstract::JsGridOffset);
    JSClass<JSViewAbstract>::StaticMethod("useSizeType", &JSViewAbstract::JsUseSizeType);
    JSClass<JSViewAbstract>::StaticMethod("shadow", &JSViewAbstract::JsShadow);
    JSClass<JSViewAbstract>::StaticMethod("blendMode", &JSViewAbstract::JsBlendMode);
    JSClass<JSViewAbstract>::StaticMethod("grayscale", &JSViewAbstract::JsGrayScale);
    JSClass<JSViewAbstract>::StaticMethod("focusable", &JSViewAbstract::JsFocusable);
    JSClass<JSViewAbstract>::StaticMethod("onKeyEvent", &JSViewAbstract::JsOnKeyEvent);
    JSClass<JSViewAbstract>::StaticMethod("onFocusMove", &JSViewAbstract::JsOnFocusMove);
    JSClass<JSViewAbstract>::StaticMethod("onFocus", &JSViewAbstract::JsOnFocus);
    JSClass<JSViewAbstract>::StaticMethod("onBlur", &JSViewAbstract::JsOnBlur);
    JSClass<JSViewAbstract>::StaticMethod("tabIndex", &JSViewAbstract::JsTabIndex);
    JSClass<JSViewAbstract>::StaticMethod("focusOnTouch", &JSViewAbstract::JsFocusOnTouch);
    JSClass<JSViewAbstract>::StaticMethod("defaultFocus", &JSViewAbstract::JsDefaultFocus);
    JSClass<JSViewAbstract>::StaticMethod("groupDefaultFocus", &JSViewAbstract::JsGroupDefaultFocus);
    JSClass<JSViewAbstract>::StaticMethod("brightness", &JSViewAbstract::JsBrightness);
    JSClass<JSViewAbstract>::StaticMethod("contrast", &JSViewAbstract::JsContrast);
    JSClass<JSViewAbstract>::StaticMethod("saturate", &JSViewAbstract::JsSaturate);
    JSClass<JSViewAbstract>::StaticMethod("sepia", &JSViewAbstract::JsSepia);
    JSClass<JSViewAbstract>::StaticMethod("invert", &JSViewAbstract::JsInvert);
    JSClass<JSViewAbstract>::StaticMethod("hueRotate", &JSViewAbstract::JsHueRotate);
    JSClass<JSViewAbstract>::StaticMethod("clip", &JSViewAbstract::JsClip);
    JSClass<JSViewAbstract>::StaticMethod("mask", &JSViewAbstract::JsMask);
    JSClass<JSViewAbstract>::StaticMethod("key", &JSViewAbstract::JsKey);
    JSClass<JSViewAbstract>::StaticMethod("id", &JSViewAbstract::JsId);
    JSClass<JSViewAbstract>::StaticMethod("restoreId", &JSViewAbstract::JsRestoreId);
    JSClass<JSViewAbstract>::StaticMethod("hoverEffect", &JSViewAbstract::JsHoverEffect);
    JSClass<JSViewAbstract>::StaticMethod("onMouse", &JSViewAbstract::JsOnMouse);
    JSClass<JSViewAbstract>::StaticMethod("onHover", &JSViewAbstract::JsOnHover);
    JSClass<JSViewAbstract>::StaticMethod("onClick", &JSViewAbstract::JsOnClick);
    JSClass<JSViewAbstract>::StaticMethod("onGestureJudgeBegin", &JSViewAbstract::JsOnGestureJudgeBegin);
    JSClass<JSViewAbstract>::StaticMethod("clickEffect", &JSViewAbstract::JsClickEffect);
    JSClass<JSViewAbstract>::StaticMethod("debugLine", &JSViewAbstract::JsDebugLine);
    JSClass<JSViewAbstract>::StaticMethod("geometryTransition", &JSViewAbstract::JsGeometryTransition);
    JSClass<JSViewAbstract>::StaticMethod("onAreaChange", &JSViewAbstract::JsOnAreaChange);
    JSClass<JSViewAbstract>::StaticMethod("touchable", &JSInteractableView::JsTouchable);
    JSClass<JSViewAbstract>::StaticMethod("monopolizeEvents", &JSInteractableView::JsMonopolizeEvents);

    JSClass<JSViewAbstract>::StaticMethod("accessibilityGroup", &JSViewAbstract::JsAccessibilityGroup);
    JSClass<JSViewAbstract>::StaticMethod("accessibilityText", &JSViewAbstract::JsAccessibilityText);
    JSClass<JSViewAbstract>::StaticMethod("accessibilityDescription", &JSViewAbstract::JsAccessibilityDescription);
    JSClass<JSViewAbstract>::StaticMethod("accessibilityImportance", &JSViewAbstract::JsAccessibilityImportance);
    JSClass<JSViewAbstract>::StaticMethod("accessibilityLevel", &JSViewAbstract::JsAccessibilityLevel);
    JSClass<JSViewAbstract>::StaticMethod("accessibilityVirtualNode", &JSViewAbstract::JsAccessibilityVirtualNode);
    JSClass<JSViewAbstract>::StaticMethod("onAccessibility", &JSInteractableView::JsOnAccessibility);
    JSClass<JSViewAbstract>::StaticMethod("alignRules", &JSViewAbstract::JsAlignRules);
    JSClass<JSViewAbstract>::StaticMethod("onVisibleAreaChange", &JSViewAbstract::JsOnVisibleAreaChange);
    JSClass<JSViewAbstract>::StaticMethod("hitTestBehavior", &JSViewAbstract::JsHitTestBehavior);
    JSClass<JSViewAbstract>::StaticMethod("onChildTouchTest", &JSViewAbstract::JsOnChildTouchTest);
    JSClass<JSViewAbstract>::StaticMethod("keyboardShortcut", &JSViewAbstract::JsKeyboardShortcut);
    JSClass<JSViewAbstract>::StaticMethod("obscured", &JSViewAbstract::JsObscured);
    JSClass<JSViewAbstract>::StaticMethod("allowDrop", &JSViewAbstract::JsAllowDrop);
    JSClass<JSViewAbstract>::StaticMethod("dragPreview", &JSViewAbstract::JsDragPreview);

    JSClass<JSViewAbstract>::StaticMethod("createAnimatableProperty", &JSViewAbstract::JSCreateAnimatableProperty);
    JSClass<JSViewAbstract>::StaticMethod("updateAnimatableProperty", &JSViewAbstract::JSUpdateAnimatableProperty);
    JSClass<JSViewAbstract>::StaticMethod("renderGroup", &JSViewAbstract::JSRenderGroup);
    JSClass<JSViewAbstract>::StaticMethod("renderFit", &JSViewAbstract::JSRenderFit);

    JSClass<JSViewAbstract>::StaticMethod("expandSafeArea", &JSViewAbstract::JsExpandSafeArea);

    JSClass<JSViewAbstract>::Bind(globalObj);
}
void JSViewAbstract::JsAllowDrop(const JSCallbackInfo& info)
{
    if (!info[0]->IsArray()) {
        return;
    }

    auto allowDropArray = JSRef<JSArray>::Cast(info[0]);
    std::set<std::string> allowDropSet;
    allowDropSet.clear();
    std::string allowDrop;
    for (size_t i = 0; i < allowDropArray->Length(); i++) {
        allowDrop = allowDropArray->GetValueAt(i)->ToString();
        allowDropSet.insert(allowDrop);
    }
    ViewAbstractModel::GetInstance()->SetAllowDrop(allowDropSet);
}

void JSViewAbstract::JsDragPreview(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }
    NG::DragDropInfo dragPreviewInfo;
    JSRef<JSVal> builder;
    JSRef<JSVal> pixelMap;
    JSRef<JSVal> extraInfo;
    if (info[0]->IsFunction()) {
        builder = info[0];
    } else if (info[0]->IsObject()) {
        auto dragItemInfo = JSRef<JSObject>::Cast(info[0]);
        builder = dragItemInfo->GetProperty("builder");
#if defined(PIXEL_MAP_SUPPORTED)
        pixelMap = dragItemInfo->GetProperty("pixelMap");
        dragPreviewInfo.pixelMap = CreatePixelMapFromNapiValue(pixelMap);
#endif
        extraInfo = dragItemInfo->GetProperty("extraInfo");
        ParseJsString(extraInfo, dragPreviewInfo.extraInfo);
    } else {
        return;
    }

    if (builder->IsFunction()) {
        RefPtr<JsFunction> builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(builder));
        if (builderFunc != nullptr) {
            ViewStackModel::GetInstance()->NewScope();
            {
                ACE_SCORING_EVENT("dragPreview.builder");
                builderFunc->Execute();
            }
            RefPtr<AceType> node = ViewStackModel::GetInstance()->Finish();
            dragPreviewInfo.customNode = AceType::DynamicCast<NG::UINode>(node);
        }
    }
    ViewAbstractModel::GetInstance()->SetDragPreview(dragPreviewInfo);
}

void JSViewAbstract::JsAlignRules(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }

    JSRef<JSObject> valueObj = JSRef<JSObject>::Cast(info[0]);
    if (valueObj->IsEmpty()) {
        return;
    }
    const char* keys[] = { "left", "middle", "right", "top", "center", "bottom", "bias" };
    std::map<AlignDirection, AlignRule> alignRules;
    BiasPair biasPair(DEFAULT_BIAS, DEFAULT_BIAS);
    for (uint32_t i = 0; i < sizeof(keys) / sizeof(const char*); i++) {
        auto rule = valueObj->GetProperty(keys[i]);
        if (rule->IsObject()) {
            JSRef<JSObject> val = JSRef<JSObject>::Cast(rule);
            JSRef<JSVal> align = val->GetProperty("align");
            AlignRule alignRule;
            alignRule.anchor = val->GetProperty("anchor")->ToString();
            if (i < HORIZONTAL_DIRECTION_RANGE) {
                alignRule.horizontal = static_cast<HorizontalAlign>(val->GetProperty("align")->ToNumber<int32_t>());
            } else {
                alignRule.vertical = static_cast<VerticalAlign>(val->GetProperty("align")->ToNumber<int32_t>());
            }
            if (i < VERTICAL_DIRECTION_RANGE) {
                alignRules[static_cast<AlignDirection>(i)] = alignRule;
            }
            auto biasX = val->GetProperty("horizontal");
            if (biasX->IsNumber()) {
                biasPair.first = biasX->ToNumber<float>();
            }
            auto biasY = val->GetProperty("vertical");
            if (biasY->IsNumber()) {
                biasPair.second = biasY->ToNumber<float>();
            }
        }
    }

    ViewAbstractModel::GetInstance()->SetAlignRules(alignRules);
    ViewAbstractModel::GetInstance()->SetBias(biasPair);
}

void JSViewAbstract::SetMarginTop(const JSCallbackInfo& info)
{
    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return;
    }
    ViewAbstractModel::GetInstance()->SetMargins(value, std::nullopt, std::nullopt, std::nullopt);
}

void JSViewAbstract::SetMarginBottom(const JSCallbackInfo& info)
{
    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return;
    }
    ViewAbstractModel::GetInstance()->SetMargins(std::nullopt, value, std::nullopt, std::nullopt);
}

void JSViewAbstract::SetMarginLeft(const JSCallbackInfo& info)
{
    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return;
    }
    ViewAbstractModel::GetInstance()->SetMargins(std::nullopt, std::nullopt, value, std::nullopt);
}

void JSViewAbstract::SetMarginRight(const JSCallbackInfo& info)
{
    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return;
    }
    ViewAbstractModel::GetInstance()->SetMargins(std::nullopt, std::nullopt, std::nullopt, value);
}

void JSViewAbstract::SetPaddingTop(const JSCallbackInfo& info)
{
    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return;
    }
    ViewAbstractModel::GetInstance()->SetPaddings(value, std::nullopt, std::nullopt, std::nullopt);
}

void JSViewAbstract::SetPaddingBottom(const JSCallbackInfo& info)
{
    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return;
    }
    ViewAbstractModel::GetInstance()->SetPaddings(std::nullopt, value, std::nullopt, std::nullopt);
}

void JSViewAbstract::SetPaddingLeft(const JSCallbackInfo& info)
{
    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return;
    }
    ViewAbstractModel::GetInstance()->SetPaddings(std::nullopt, std::nullopt, value, std::nullopt);
}

void JSViewAbstract::SetPaddingRight(const JSCallbackInfo& info)
{
    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return;
    }
    ViewAbstractModel::GetInstance()->SetPaddings(std::nullopt, std::nullopt, std::nullopt, value);
}

void JSViewAbstract::SetColorBlend(Color color)
{
    ViewAbstractModel::GetInstance()->SetColorBlend(color);
}

void JSViewAbstract::SetLinearGradientBlur(NG::LinearGradientBlurPara blurPara)
{
    ViewAbstractModel::GetInstance()->SetLinearGradientBlur(blurPara);
}

void JSViewAbstract::SetDynamicLightUp(float rate, float lightUpDegree)
{
    ViewAbstractModel::GetInstance()->SetDynamicLightUp(rate, lightUpDegree);
}

void JSViewAbstract::SetWindowBlur(float progress, WindowBlurStyle blurStyle)
{
    ViewAbstractModel::GetInstance()->SetWindowBlur(progress, blurStyle);
}

bool JSViewAbstract::ParseJsonDimension(
    const std::unique_ptr<JsonValue>& jsonValue, CalcDimension& result, DimensionUnit defaultUnit, bool checkIllegal)
{
    if (!jsonValue || jsonValue->IsNull()) {
        return false;
    }
    if (!jsonValue->IsNumber() && !jsonValue->IsString() && !jsonValue->IsObject()) {
        return false;
    }
    if (jsonValue->IsNumber()) {
        result = Dimension(jsonValue->GetDouble(), defaultUnit);
        return true;
    }
    if (jsonValue->IsString()) {
        if (checkIllegal) {
            return StringUtils::StringToDimensionWithUnitNG(jsonValue->GetString(), result, defaultUnit);
        }
        result = StringUtils::StringToCalcDimension(jsonValue->GetString(), false, defaultUnit);
        return true;
    }
    auto resVal = JsonUtil::ParseJsonString(jsonValue->ToString());
    auto resId = resVal->GetValue("id");
    if (!resId || !resId->IsNumber()) {
        return false;
    }

    auto resourceWrapper = CreateResourceWrapper();
    if (!resourceWrapper) {
        return false;
    }
    result = resourceWrapper->GetDimension(resId->GetUInt());
    return true;
}

bool JSViewAbstract::ParseJsonDimensionVp(
    const std::unique_ptr<JsonValue>& jsonValue, CalcDimension& result, bool checkIllegal)
{
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        return ParseJsonDimension(jsonValue, result, DimensionUnit::VP, true);
    }
    return ParseJsonDimension(jsonValue, result, DimensionUnit::VP, checkIllegal);
}

bool JSViewAbstract::ParseJsonDouble(const std::unique_ptr<JsonValue>& jsonValue, double& result)
{
    if (!jsonValue || jsonValue->IsNull()) {
        return false;
    }
    if (!jsonValue->IsNumber() && !jsonValue->IsString() && !jsonValue->IsObject()) {
        return false;
    }
    if (jsonValue->IsNumber()) {
        result = jsonValue->GetDouble();
        return true;
    }
    if (jsonValue->IsString()) {
        result = StringUtils::StringToDouble(jsonValue->GetString());
        return true;
    }
    // parse json Resource
    auto resVal = JsonUtil::ParseJsonString(jsonValue->ToString());
    auto resId = resVal->GetValue("id");
    CHECK_NULL_RETURN(resId && resId->IsNumber(), false);
    auto id = resId->GetUInt();
    auto resType = resVal->GetValue("type");
    CHECK_NULL_RETURN(resType && resType->IsNumber(), false);
    auto type = resType->GetUInt();

    auto resourceWrapper = CreateResourceWrapper();
    if (!resourceWrapper) {
        return false;
    }
    if (type == static_cast<uint32_t>(ResourceType::STRING)) {
        auto numberString = resourceWrapper->GetString(id);
        return StringUtils::StringToDouble(numberString, result);
    }
    if (type == static_cast<uint32_t>(ResourceType::INTEGER)) {
        result = resourceWrapper->GetInt(id);
        return true;
    }
    if (type == static_cast<uint32_t>(ResourceType::FLOAT)) {
        result = resourceWrapper->GetDouble(id);
        return true;
    }
    return false;
}

bool JSViewAbstract::ParseJsonColor(const std::unique_ptr<JsonValue>& jsonValue, Color& result)
{
    if (!jsonValue || jsonValue->IsNull()) {
        return false;
    }
    if (!jsonValue->IsNumber() && !jsonValue->IsString() && !jsonValue->IsObject()) {
        return false;
    }
    if (jsonValue->IsNumber()) {
        result = Color(ColorAlphaAdapt(jsonValue->GetUInt()));
        return true;
    }

    bool isSetColor = false;
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        isSetColor = jsonValue->IsString();
    } else {
        isSetColor = jsonValue->IsString() && jsonValue->GetString() != "";
    }
    if (isSetColor) {
        result = Color::FromString(jsonValue->GetString());
        return true;
    }
    auto resVal = JsonUtil::ParseJsonString(jsonValue->ToString());
    auto resId = resVal->GetValue("id");
    if (!resId || !resId->IsNumber()) {
        return false;
    }
    auto resourceWrapper = CreateResourceWrapper();
    if (!resourceWrapper) {
        return false;
    }
    result = resourceWrapper->GetColor(resId->GetUInt());
    return true;
}

bool JSViewAbstract::ParseShadowProps(const JSRef<JSVal>& jsValue, Shadow& shadow)
{
    int32_t shadowStyle = 0;
    if (ParseJsInteger<int32_t>(jsValue, shadowStyle)) {
        auto style = static_cast<ShadowStyle>(shadowStyle);
        return GetShadowFromTheme(style, shadow);
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    double radius = 0.0;
    ParseJsDouble(jsObj->GetProperty("radius"), radius);
    if (LessNotEqual(radius, 0.0)) {
        radius = 0.0;
    }
    shadow.SetBlurRadius(radius);
    CalcDimension offsetX;
    if (ParseJsResource(jsObj->GetProperty("offsetX"), offsetX)) {
        shadow.SetOffsetX(offsetX.Value());
    } else {
        if (ParseJsDimensionVp(jsObj->GetProperty("offsetX"), offsetX)) {
            shadow.SetOffsetX(offsetX.Value());
        }
    }

    CalcDimension offsetY;
    if (ParseJsResource(jsObj->GetProperty("offsetY"), offsetY)) {
        shadow.SetOffsetY(offsetY.Value());
    } else {
        if (ParseJsDimensionVp(jsObj->GetProperty("offsetY"), offsetY)) {
            shadow.SetOffsetY(offsetY.Value());
        }
    }
    Color color;
    ShadowColorStrategy shadowColorStrategy;
    if (ParseJsShadowColorStrategy(jsObj->GetProperty("color"), shadowColorStrategy)) {
        shadow.SetShadowColorStrategy(shadowColorStrategy);
    } else if (ParseJsColor(jsObj->GetProperty("color"), color)) {
        shadow.SetColor(color);
    }
    auto type = jsObj->GetPropertyValue<int32_t>("type", static_cast<int32_t>(ShadowType::COLOR));
    type = std::clamp(type, static_cast<int32_t>(ShadowType::COLOR), static_cast<int32_t>(ShadowType::BLUR));
    shadow.SetShadowType(static_cast<ShadowType>(type));
    bool isFilled = jsObj->GetPropertyValue<bool>("fill", false);
    shadow.SetIsFilled(isFilled);
    return true;
}

bool JSViewAbstract::GetShadowFromTheme(ShadowStyle shadowStyle, Shadow& shadow)
{
    auto colorMode = SystemProperties::GetColorMode();
    if (shadowStyle == ShadowStyle::None) {
        return true;
    }

    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, false);

    auto shadowTheme = pipelineContext->GetTheme<ShadowTheme>();
    if (!shadowTheme) {
        return false;
    }

    shadow = shadowTheme->GetShadow(shadowStyle, colorMode);
    return true;
}

bool JSViewAbstract::ParseJsResource(const JSRef<JSVal>& jsValue, CalcDimension& result)
{
    if (!jsValue->IsObject()) {
        return false;
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    auto resourceWrapper = CreateResourceWrapper();
    CHECK_NULL_RETURN(resourceWrapper, false);
    uint32_t type = jsObj->GetPropertyValue<uint32_t>("type", 0);
    if (type == static_cast<uint32_t>(ResourceType::STRING)) {
        auto value = resourceWrapper->GetString(jsObj->GetPropertyValue<uint32_t>("id", 0));
        return StringUtils::StringToCalcDimensionNG(value, result, false);
    }
    if (type == static_cast<uint32_t>(ResourceType::INTEGER)) {
        auto value = std::to_string(resourceWrapper->GetInt(jsObj->GetPropertyValue<uint32_t>("id", 0)));
        StringUtils::StringToDimensionWithUnitNG(value, result);
        return true;
    }

    if (type == static_cast<uint32_t>(ResourceType::FLOAT)) {
        result = resourceWrapper->GetDimension(jsObj->GetPropertyValue<uint32_t>("id", 0));
        return true;
    }
    return false;
}

bool JSViewAbstract::ParseDataDetectorConfig(
    const JSCallbackInfo& info, std::string& types, std::function<void(const std::string&)>& onResult)
{
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSVal> typeValue = obj->GetProperty("types");
    if (!typeValue->IsArray()) {
        return false;
    }
    JSRef<JSArray> array = JSRef<JSArray>::Cast(typeValue);
    for (size_t i = 0; i < array->Length(); i++) {
        JSRef<JSVal> value = array->GetValueAt(i);
        auto index = value->ToNumber<int32_t>();
        if (index < 0 || index >= static_cast<int32_t>(TEXT_DETECT_TYPES.size())) {
            return false;
        }
        if (i != 0) {
            types.append(",");
        }
        types.append(TEXT_DETECT_TYPES[index]);
    }
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    JSRef<JSVal> resultCallback = obj->GetProperty("onDetectResultUpdate");
    if (resultCallback->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsClipboardFunction>(JSRef<JSFunc>::Cast(resultCallback));
        onResult = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                       const std::string& result) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            PipelineContext::SetCallBackNode(node);
            func->Execute(result);
        };
    }
    return true;
}

void JSViewAbstract::GetAngle(
    const std::string& key, const std::unique_ptr<JsonValue>& jsonValue, std::optional<float>& angle)
{
    auto value = jsonValue->GetValue(key);
    if (value && value->IsString()) {
        angle = static_cast<float>(StringUtils::StringToDegree(value->GetString()));
    } else if (value && value->IsNumber()) {
        angle = static_cast<float>(value->GetDouble());
    }
}

void JSViewAbstract::GetJsAngle(
    const std::string& key, const JSRef<JSVal>& jsValue, std::optional<float>& angle)
{
    if (!jsValue->IsObject()) {
        return;
    }
    JSRef<JSVal> value = JSRef<JSObject>::Cast(jsValue)->GetProperty(key.c_str());
    if (value->IsString()) {
        angle = static_cast<float>(StringUtils::StringToDegree(value->ToString()));
    } else if (value->IsNumber()) {
        angle = value->ToNumber<float>();
    }
}

void JSViewAbstract::CheckAngle(std::optional<float>& angle)
{
    if (LessNotEqual(angle.value(), 0.0f)) {
        angle = 0.0f;
    } else if (GreatNotEqual(angle.value(), MAX_ANGLE)) {
        angle = MAX_ANGLE;
    }
}

void JSViewAbstract::GetPerspective(
    const std::string& key, const std::unique_ptr<JsonValue>& jsonValue, float& perspective)
{
    auto value = jsonValue->GetValue(key);
    if (value && value->IsNumber()) {
        perspective = static_cast<float>(value->GetDouble());
    }
}

void JSViewAbstract::GetJsPerspective(const std::string& key, const JSRef<JSVal>& jsValue, float& perspective)
{
    if (!jsValue->IsObject()) {
        return;
    }
    auto value = JSRef<JSObject>::Cast(jsValue)->GetProperty(key.c_str());
    if (value->IsNumber()) {
        perspective = value->ToNumber<float>();
    }
}

void JSViewAbstract::GetGradientColorStops(Gradient& gradient, const std::unique_ptr<JsonValue>& colorStops)
{
    if (!colorStops || colorStops->IsNull() || !colorStops->IsArray()) {
        return;
    }

    for (int32_t i = 0; i < colorStops->GetArraySize(); i++) {
        GradientColor gradientColor;
        auto item = colorStops->GetArrayItem(i);
        if (item && !item->IsNull() && item->IsArray() && item->GetArraySize() >= 1) {
            auto colorParams = item->GetArrayItem(0);
            // color
            Color color;
            if (!ParseJsonColor(colorParams, color)) {
                continue;
            }
            gradientColor.SetColor(color);
            gradientColor.SetHasValue(false);
            // stop value
            if (item->GetArraySize() <= 1) {
                continue;
            }
            auto stopValue = item->GetArrayItem(1);
            double value = 0.0;
            if (ParseJsonDouble(stopValue, value)) {
                value = std::clamp(value, 0.0, 1.0);
                gradientColor.SetHasValue(true);
                gradientColor.SetDimension(CalcDimension(value * 100.0, DimensionUnit::PERCENT));
            }
            gradient.AddColor(gradientColor);
        }
    }
}

void JSViewAbstract::NewGetGradientColorStops(NG::Gradient& gradient, const std::unique_ptr<JsonValue>& colorStops)
{
    if (!colorStops || colorStops->IsNull() || !colorStops->IsArray()) {
        return;
    }

    for (int32_t i = 0; i < colorStops->GetArraySize(); i++) {
        NG::GradientColor gradientColor;
        auto item = colorStops->GetArrayItem(i);
        if (item && !item->IsNull() && item->IsArray() && item->GetArraySize() >= 1) {
            auto colorParams = item->GetArrayItem(0);
            // color
            Color color;
            if (!ParseJsonColor(colorParams, color)) {
                continue;
            }
            gradientColor.SetColor(color);
            gradientColor.SetHasValue(false);
            // stop value
            if (item->GetArraySize() <= 1) {
                continue;
            }
            auto stopValue = item->GetArrayItem(1);
            double value = 0.0;
            if (ParseJsonDouble(stopValue, value)) {
                value = std::clamp(value, 0.0, 1.0);
                gradientColor.SetHasValue(true);
                //  [0, 1] -> [0, 100.0];
                gradientColor.SetDimension(CalcDimension(value * 100.0, DimensionUnit::PERCENT));
            }
            gradient.AddColor(gradientColor);
        }
    }
}

void JSViewAbstract::NewGetJsGradientColorStops(NG::Gradient& gradient, const JSRef<JSVal>& colorStops)
{
    if (!colorStops->IsArray()) {
        return;
    }

    JSRef<JSArray> jsArray = JSRef<JSArray>::Cast(colorStops);
    size_t length = jsArray->Length();
    for (size_t i = 0; i < length; i++) {
        NG::GradientColor gradientColor;
        JSRef<JSVal> item = jsArray->GetValueAt(i);
        if (!item->IsArray()) {
            continue;
        }
        JSRef<JSArray> subArray = JSRef<JSArray>::Cast(item);
        if (subArray->Length() < 2) {
            continue;
        }
        // color
        Color color;
        if (!ParseJsColor(subArray->GetValueAt(0), color)) {
            continue;
        }
        gradientColor.SetColor(color);
        gradientColor.SetHasValue(false);
        // stop value
        double value = 0.0;
        if (ParseJsDouble(subArray->GetValueAt(1), value)) {
            value = std::clamp(value, 0.0, 1.0);
            gradientColor.SetHasValue(true);
        }
        //  [0, 1] -> [0, 100.0];
        gradientColor.SetDimension(CalcDimension(value * 100.0, DimensionUnit::PERCENT));
        gradient.AddColor(gradientColor);
    }
}

void JSViewAbstract::SetDirection(const std::string& dir)
{
    TextDirection direction = TextDirection::AUTO;
    if (dir == "Ltr") {
        direction = TextDirection::LTR;
    } else if (dir == "Rtl") {
        direction = TextDirection::RTL;
    } else if (dir == "Auto") {
        direction = TextDirection::AUTO;
    } else if (dir == "undefined" && Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        direction = TextDirection::AUTO;
    }
    ViewAbstractModel::GetInstance()->SetLayoutDirection(direction);
}

RefPtr<ThemeConstants> JSViewAbstract::GetThemeConstants(const JSRef<JSObject>& jsObj)
{
    std::string bundleName;
    std::string moduleName;
    if (!jsObj->IsUndefined()) {
        JSRef<JSVal> bundle = jsObj->GetProperty("bundleName");
        JSRef<JSVal> module = jsObj->GetProperty("moduleName");
        if (bundle->IsString() && module->IsString()) {
            bundleName = bundle->ToString();
            moduleName = module->ToString();
        }
    }

    auto cardId = CardScope::CurrentId();
    if (cardId != INVALID_CARD_ID) {
        auto container = Container::Current();
        auto weak = container->GetCardPipeline(cardId);
        auto cardPipelineContext = weak.Upgrade();
        CHECK_NULL_RETURN(cardPipelineContext, nullptr);
        auto cardThemeManager = cardPipelineContext->GetThemeManager();
        CHECK_NULL_RETURN(cardThemeManager, nullptr);
        return cardThemeManager->GetThemeConstants(bundleName, moduleName);
    }

#ifdef PLUGIN_COMPONENT_SUPPORTED
    if (Container::CurrentId() >= MIN_PLUGIN_SUBCONTAINER_ID) {
        auto pluginContainer = PluginManager::GetInstance().GetPluginSubContainer(Container::CurrentId());
        if (!pluginContainer) {
            return nullptr;
        }
        auto pluginPipelineContext = pluginContainer->GetPipelineContext();
        if (!pluginPipelineContext) {
            return nullptr;
        }
        auto pluginThemeManager = pluginPipelineContext->GetThemeManager();
        if (!pluginThemeManager) {
            return nullptr;
        }
        return pluginThemeManager->GetThemeConstants(bundleName, moduleName);
    }
#endif
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, nullptr);
    return themeManager->GetThemeConstants(bundleName, moduleName);
}

void JSViewAbstract::JsHoverEffect(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::NUMBER };
    if (!CheckJSCallbackInfo("HoverEffect", info, checkList)) {
        ViewAbstractModel::GetInstance()->SetHoverEffect(HoverEffectType::AUTO);
        return;
    }
    if (!info[0]->IsNumber()) {
        return;
    }
    ViewAbstractModel::GetInstance()->SetHoverEffect(static_cast<HoverEffectType>(info[0]->ToNumber<int32_t>()));
}

void JSViewAbstract::JsOnMouse(const JSCallbackInfo& info)
{
    if (info[0]->IsUndefined() && IsDisableEventVersion()) {
        ViewAbstractModel::GetInstance()->DisableOnMouse();
        return;
    }
    if (!info[0]->IsFunction()) {
        return;
    }

    RefPtr<JsClickFunction> jsOnMouseFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto onMouse = [execCtx = info.GetExecutionContext(), func = std::move(jsOnMouseFunc), node = targetNode](
                       MouseInfo& mouseInfo) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onMouse");
        PipelineContext::SetCallBackNode(node);
        func->Execute(mouseInfo);
    };
    ViewAbstractModel::GetInstance()->SetOnMouse(std::move(onMouse));
}

void JSViewAbstract::JsOnHover(const JSCallbackInfo& info)
{
    if (info[0]->IsUndefined() && IsDisableEventVersion()) {
        ViewAbstractModel::GetInstance()->DisableOnHover();
        return;
    }
    if (!info[0]->IsFunction()) {
        return;
    }

    RefPtr<JsHoverFunction> jsOnHoverFunc = AceType::MakeRefPtr<JsHoverFunction>(JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto onHover = [execCtx = info.GetExecutionContext(), func = std::move(jsOnHoverFunc), node = frameNode](
                       bool isHover, HoverInfo& hoverInfo) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onHover");
        PipelineContext::SetCallBackNode(node);
        func->HoverExecute(isHover, hoverInfo);
    };
    ViewAbstractModel::GetInstance()->SetOnHover(std::move(onHover));
}

void JSViewAbstract::JsOnClick(const JSCallbackInfo& info)
{
    if (info[0]->IsUndefined() && IsDisableEventVersion()) {
        ViewAbstractModel::GetInstance()->DisableOnClick();
        return;
    }
    if (!info[0]->IsFunction()) {
        return;
    }

    auto jsOnClickFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto onTap = [execCtx = info.GetExecutionContext(), func = std::move(jsOnClickFunc), node = targetNode](
                     GestureEvent& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onClick");
        PipelineContext::SetCallBackNode(node);
        func->Execute(info);
    };
    auto onClick = [execCtx = info.GetExecutionContext(), func = jsOnClickFunc, node = targetNode](
                       const ClickInfo* info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onClick");
        PipelineContext::SetCallBackNode(node);
        func->Execute(*info);
    };
    ViewAbstractModel::GetInstance()->SetOnClick(std::move(onTap), std::move(onClick));
}

void JSViewAbstract::JsOnGestureJudgeBegin(const JSCallbackInfo& info)
{
    if (info[0]->IsUndefined() || !info[0]->IsFunction()) {
        ViewAbstractModel::GetInstance()->SetOnGestureJudgeBegin(nullptr);
        return;
    }

    auto jsOnGestureJudgeFunc = AceType::MakeRefPtr<JsGestureJudgeFunction>(JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto onGestureJudgefunc = [execCtx = info.GetExecutionContext(), func = jsOnGestureJudgeFunc, node = frameNode](
                                  const RefPtr<NG::GestureInfo>& gestureInfo,
                                  const std::shared_ptr<BaseGestureEvent>& info) -> GestureJudgeResult {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, GestureJudgeResult::CONTINUE);
        ACE_SCORING_EVENT("onGestureJudgeBegin");
        PipelineContext::SetCallBackNode(node);
        return func->Execute(gestureInfo, info);
    };
    ViewAbstractModel::GetInstance()->SetOnGestureJudgeBegin(std::move(onGestureJudgefunc));
}

void JSViewAbstract::JsClickEffect(const JSCallbackInfo& info)
{
    if (info[0]->IsUndefined() || info[0]->IsNull()) {
        ViewAbstractModel::GetInstance()->SetClickEffectLevel(ClickEffectLevel::UNDEFINED, DEFAULT_SCALE_LIGHT);
        return;
    }
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSVal> clickEffectLevel = obj->GetProperty("level");
    int32_t clickEffectLevelValue = 0;
    if (clickEffectLevel->IsNumber()) {
        clickEffectLevelValue = clickEffectLevel->ToNumber<int32_t>();
        if (clickEffectLevelValue < static_cast<int32_t>(ClickEffectLevel::LIGHT) ||
            clickEffectLevelValue > static_cast<int32_t>(ClickEffectLevel::HEAVY)) {
            clickEffectLevelValue = 0;
        }
    }

    JSRef<JSVal> scaleNumber = obj->GetProperty("scale");
    float scaleNumberValue = DEFAULT_SCALE_LIGHT;
    if (!scaleNumber->IsNumber()) {
        if ((ClickEffectLevel)clickEffectLevelValue == ClickEffectLevel::MIDDLE ||
            (ClickEffectLevel)clickEffectLevelValue == ClickEffectLevel::HEAVY) {
            scaleNumberValue = DEFAULT_SCALE_MIDDLE_OR_HEAVY;
        }
        ViewAbstractModel::GetInstance()->SetClickEffectLevel(
            (ClickEffectLevel)clickEffectLevelValue, scaleNumberValue);
        return;
    }

    scaleNumberValue = scaleNumber->ToNumber<float>();
    if (LessNotEqual(scaleNumberValue, 0.0) || GreatNotEqual(scaleNumberValue, 1.0)) {
        if ((ClickEffectLevel)clickEffectLevelValue == ClickEffectLevel::MIDDLE ||
            (ClickEffectLevel)clickEffectLevelValue == ClickEffectLevel::HEAVY) {
            scaleNumberValue = DEFAULT_SCALE_MIDDLE_OR_HEAVY;
        } else {
            scaleNumberValue = DEFAULT_SCALE_LIGHT;
        }
    }

    ViewAbstractModel::GetInstance()->SetClickEffectLevel((ClickEffectLevel)clickEffectLevelValue, scaleNumberValue);
}

void JSViewAbstract::JsOnVisibleAreaChange(const JSCallbackInfo& info)
{
    if (info.Length() != 2) {
        return;
    }

    if (!info[0]->IsArray() || !info[1]->IsFunction()) {
        return;
    }

    auto ratioArray = JSRef<JSArray>::Cast(info[0]);
    size_t size = ratioArray->Length();
    std::vector<double> ratioVec(size);
    ratioVec.clear();
    for (size_t i = 0; i < size; i++) {
        double ratio = 0.0;
        ParseJsDouble(ratioArray->GetValueAt(i), ratio);
        if (LessOrEqual(ratio, VISIBLE_RATIO_MIN)) {
            ratio = VISIBLE_RATIO_MIN;
        }

        if (GreatOrEqual(ratio, VISIBLE_RATIO_MAX)) {
            ratio = VISIBLE_RATIO_MAX;
        }
        ratioVec.push_back(ratio);
    }

    RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[1]));
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto onVisibleChange = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                               bool visible, double ratio) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onVisibleAreaChange");

        JSRef<JSVal> params[2];
        params[0] = JSRef<JSVal>::Make(ToJSValue(visible));
        params[1] = JSRef<JSVal>::Make(ToJSValue(ratio));
        PipelineContext::SetCallBackNode(node);
        func->ExecuteJS(2, params);
    };
    ViewAbstractModel::GetInstance()->SetOnVisibleChange(std::move(onVisibleChange), ratioVec);
}

void JSViewAbstract::JsHitTestBehavior(const JSCallbackInfo& info)
{
    if (info.Length() != 1) {
        return;
    }

    NG::HitTestMode hitTestModeNG = NG::HitTestMode::HTMDEFAULT;
    hitTestModeNG = static_cast<NG::HitTestMode>(info[0]->ToNumber<int32_t>());
    ViewAbstractModel::GetInstance()->SetHitTestMode(hitTestModeNG);
}

void JSViewAbstract::JsOnChildTouchTest(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::FUNCTION };
    if (!CheckJSCallbackInfo("onChildTouchTest", info, checkList)) {
        return;
    }

    RefPtr<JsOnChildTouchTestFunction> jsOnChildTouchTestFunc =
        AceType::MakeRefPtr<JsOnChildTouchTestFunction>(JSRef<JSFunc>::Cast(info[0]));

    auto onTouchTestFunc = [execCtx = info.GetExecutionContext(), func = std::move(jsOnChildTouchTestFunc)](
                               const std::vector<NG::TouchTestInfo>& touchInfo) -> NG::TouchResult {
        NG::TouchResult touchRes;
        NG::TouchResult defaultRes;
        defaultRes.strategy = NG::TouchTestStrategy::DEFAULT;
        defaultRes.id = "";
        auto ret = func->Execute(touchInfo);
        if (!ret->IsObject()) {
            TAG_LOGW(AceLogTag::ACE_UIEVENT, "onChildTouchTest return value is not object, parse failed.");
            return defaultRes;
        }

        auto retObj = JSRef<JSObject>::Cast(ret);
        auto strategy = retObj->GetProperty("strategy");
        if (!strategy->IsNumber()) {
            TAG_LOGW(AceLogTag::ACE_UIEVENT, "onChildTouchTest return value strategy is not number, parse failed.");
            return defaultRes;
        }
        touchRes.strategy = static_cast<NG::TouchTestStrategy>(strategy->ToNumber<int32_t>());
        auto id = retObj->GetProperty("id");
        if (!id->IsString()) {
            TAG_LOGW(AceLogTag::ACE_UIEVENT, "onChildTouchTest return value id is not string, parse failed.");
            return defaultRes;
        }
        touchRes.id = id->ToString();
        return touchRes;
    };
    ViewAbstractModel::GetInstance()->SetOnTouchTestFunc(std::move(onTouchTestFunc));
}

void JSViewAbstract::JsForegroundColor(const JSCallbackInfo& info)
{
    Color foregroundColor;
    ForegroundColorStrategy strategy;
    if (ParseJsColorStrategy(info[0], strategy)) {
        ViewAbstractModel::GetInstance()->SetForegroundColorStrategy(strategy);
        return;
    }
    if (!ParseJsColor(info[0], foregroundColor)) {
        return;
    }
    ViewAbstractModel::GetInstance()->SetForegroundColor(foregroundColor);
}

void JSViewAbstract::JsKeyboardShortcut(const JSCallbackInfo& info)
{
    // KeyboardShortcut only allows 2 or 3 params.
    if (info.Length() < 2 || info.Length() > 3) {
        return;
    }
    if ((!info[0]->IsString() && !info[0]->IsNumber()) || !info[1]->IsArray()) {
        ViewAbstractModel::GetInstance()->SetKeyboardShortcut("", std::vector<ModifierKey>(), nullptr);
        return;
    }

    std::string value;
    if (info[0]->IsString()) {
        value = info[0]->ToString();
        if (value.empty() || value.size() > 1) {
            ViewAbstractModel::GetInstance()->SetKeyboardShortcut("", std::vector<ModifierKey>(), nullptr);
            return;
        }
    } else {
        FunctionKey functionkey = static_cast<FunctionKey>(info[0]->ToNumber<int32_t>());
        value = GetFunctionKeyName(functionkey);
    }

    auto keysArray = JSRef<JSArray>::Cast(info[1]);
    size_t size = keysArray->Length();
    std::vector<ModifierKey> keys(size);
    keys.clear();
    for (size_t i = 0; i < size; i++) {
        JSRef<JSVal> key = keysArray->GetValueAt(i);
        if (key->IsNumber()) {
            keys.emplace_back(static_cast<ModifierKey>(key->ToNumber<int32_t>()));
        }
    }

    // KeyboardShortcut allows 3 params, the third param is function callback.
    if (info.Length() == 3 && info[2]->IsFunction()) {
        RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[2]));
        WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
        auto onKeyboardShortcutAction = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc),
                                            node = frameNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("onKeyboardShortcutAction");
            PipelineContext::SetCallBackNode(node);
            func->ExecuteJS();
        };
        ViewAbstractModel::GetInstance()->SetKeyboardShortcut(value, keys, std::move(onKeyboardShortcutAction));
        return;
    }
    ViewAbstractModel::GetInstance()->SetKeyboardShortcut(value, keys, nullptr);
}

bool JSViewAbstract::CheckColor(
    const JSRef<JSVal>& jsValue, Color& result, const char* componentName, const char* propName)
{
    // Color is undefined or null
    if (jsValue->IsUndefined() || jsValue->IsNull()) {
        return false;
    }
    // input type is not in [number, string, Resource]
    if (!jsValue->IsNumber() && !jsValue->IsString() && !jsValue->IsObject()) {
        return false;
    }
    // Correct type, incorrect value parsing
    if (!ParseJsColor(jsValue, result)) {
        return false;
    }
    return true;
}

bool JSViewAbstract::CheckLength(
    const JSRef<JSVal>& jsValue, CalcDimension& result, const char* componentName, const char* propName)
{
    // Length is undefined or null
    if (jsValue->IsUndefined() || jsValue->IsNull()) {
        return false;
    }
    // input type is not in [number, string, Resource]
    if (!jsValue->IsNumber() && !jsValue->IsString() && !jsValue->IsObject()) {
        return false;
    }
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        return ParseJsDimensionVpNG(jsValue, result);
    }
    // Correct type, incorrect value parsing
    if (!ParseJsDimensionVp(jsValue, result)) {
        return false;
    }
    return true;
}

void JSViewAbstract::JsObscured(const JSCallbackInfo& info)
{
    if (info[0]->IsUndefined()) {
        std::vector<ObscuredReasons> reasons(0);
        ViewAbstractModel::GetInstance()->SetObscured(reasons);
        return;
    }
    if (!info[0]->IsArray()) {
        return;
    }

    auto obscuredArray = JSRef<JSArray>::Cast(info[0]);
    size_t size = obscuredArray->Length();
    std::vector<ObscuredReasons> reasons(size);
    reasons.clear();
    for (size_t i = 0; i < size; i++) {
        JSRef<JSVal> reason = obscuredArray->GetValueAt(i);
        if (reason->IsNumber()) {
            reasons.emplace_back(static_cast<ObscuredReasons>(reason->ToNumber<int32_t>()));
        }
    }

    ViewAbstractModel::GetInstance()->SetObscured(reasons);
}

void JSViewAbstract::JSRenderGroup(const JSCallbackInfo& info)
{
    if (info.Length() != 1) {
        return;
    }
    bool isRenderGroup = false;
    if (info[0]->IsBoolean()) {
        isRenderGroup = info[0]->ToBoolean();
    }
    ViewAbstractModel::GetInstance()->SetRenderGroup(isRenderGroup);
}

void JSViewAbstract::JSRenderFit(const JSCallbackInfo& info)
{
    if (info.Length() != 1) {
        return;
    }
    RenderFit renderFit = RenderFit::TOP_LEFT;
    if (info[0]->IsNumber()) {
        int32_t fitNumber = info[0]->ToNumber<int32_t>();
        if (fitNumber >= static_cast<int32_t>(RenderFit::CENTER) &&
            fitNumber <= static_cast<int32_t>(RenderFit::RESIZE_COVER_BOTTOM_RIGHT)) {
            renderFit = static_cast<RenderFit>(fitNumber);
        }
    }
    // how content fills the node duration implicit animation
    ViewAbstractModel::GetInstance()->SetRenderFit(renderFit);
}

void JSViewAbstract::GetJsMediaBundleInfo(const JSRef<JSVal>& jsValue, std::string& bundleName, std::string& moduleName)
{
    if (!jsValue->IsObject() || jsValue->IsString()) {
        return;
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    if (!jsObj->IsUndefined()) {
        JSRef<JSVal> bundle = jsObj->GetProperty("bundleName");
        JSRef<JSVal> module = jsObj->GetProperty("moduleName");
        if (bundle->IsString() && module->IsString()) {
            bundleName = bundle->ToString();
            moduleName = module->ToString();
        }
    }
}

void JSViewAbstract::ParseImageAnalyzerSubjectOptions(const JSRef<JSVal>& optionVal,
    ImageAnalyzerConfig& analyzerConfig)
{
    ImageAnalyzerSubjectOptions subjectOptions;
    auto obj = JSRef<JSObject>::Cast(optionVal);
    JSRef<JSVal> onAnalyzedVal = obj->GetProperty("onAnalyzed");
    if (onAnalyzedVal->IsFunction()) {
        RefPtr<JsFunction> jsOnAnalyzedFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(),
            JSRef<JSFunc>::Cast(onAnalyzedVal));
        onSubcjectAnalyzedFunc onAnalyzedCallback =
            [func = std::move(jsOnAnalyzedFunc)](std::string tag, std::vector<uint8_t> data) {
            JSRef<JSVal> params[2];
            params[0] = JSRef<JSVal>::Make(ToJSValue(tag));
            JSRef<JSArray> indexArray = JSRef<JSArray>::New();
            for (uint32_t i = 0; i < data.size(); i++) {
                indexArray->SetValueAt(i, JSRef<JSVal>::Make(ToJSValue(data[i])));
            }
            params[1] = JSRef<JSVal>::Cast(indexArray);
            func->ExecuteJS(2, params);
        };
        subjectOptions.onAnalyzedCallback = std::move(onAnalyzedCallback);
    }

    JSRef<JSVal> dataVal = obj->GetProperty("analyzedData");
    if (dataVal->IsArray()) {
        JSRef<JSArray> dataArray  = JSRef<JSArray>::Cast(dataVal);
        std::vector<uint8_t> analyzedData;
        for (size_t i = 0; i < dataArray->Length(); ++i) {
            JSRef<JSVal> value = dataArray->GetValueAt(i);
            if (value->IsNumber()) {
                analyzedData.emplace_back(value->ToNumber<uint8_t>());
            }
        }
        subjectOptions.analyzedData = std::move(analyzedData);
    }

#if defined(PIXEL_MAP_SUPPORTED)
    auto pixmapVal = obj->GetProperty("sourcePixelmap");
    RefPtr<PixelMap> pixmap = CreatePixelMapFromNapiValue(pixmapVal);
    if (pixmap != nullptr) {
        subjectOptions.sourcePixelmap = ConvertPixmapNapi(pixmap);
    }
#endif
    analyzerConfig.subjectOptions_ = std::move(subjectOptions);
}

void JSViewAbstract::ParseImageAnalyzerTextOptions(const JSRef<JSVal>& optionVal, ImageAnalyzerConfig& analyzerConfig)
{
    ImageAnalyzerTextOptions textOptions;
    auto obj = JSRef<JSObject>::Cast(optionVal);
    JSRef<JSVal> onAnalyzedVal = obj->GetProperty("onAnalyzed");
    if (onAnalyzedVal->IsFunction()) {
        RefPtr<JsFunction> jsFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onAnalyzedVal));
        onTextAnalyzedFunc onAnalyzedCallback = [func = std::move(jsFunc)] (
            std::string tag, std::string data) {
            JSRef<JSVal> params[2];
            params[0] = JSRef<JSVal>::Make(ToJSValue(tag));
            params[1] = JSRef<JSVal>::Make(ToJSValue(data));
            func->ExecuteJS(2, params);
        };
        textOptions.onAnalyzedCallback = std::move(onAnalyzedCallback);
    }

    JSRef<JSVal> onTextSelected = obj->GetProperty("onTextSelected");
    if (onTextSelected->IsFunction()) {
        RefPtr<JsFunction> jsOnTextSelectedFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(),
        JSRef<JSFunc>::Cast(onTextSelected));
        onTextSelectedFunc onTextSelectedCallback =
            [func = std::move(jsOnTextSelectedFunc)] (std::string tag, std::string data) {
            JSRef<JSVal> params[2];
            params[0] = JSRef<JSVal>::Make(ToJSValue(tag));
            params[1] = JSRef<JSVal>::Make(ToJSValue(data));
            func->ExecuteJS(2, params);
        };
        textOptions.onTextSelected = std::move(onTextSelectedCallback);
    }

    JSRef<JSVal> dataVal = obj->GetProperty("analyzedData");
    if (dataVal->IsArray()) {
        std::string analyzedData = dataVal->ToString();
        textOptions.analyzedData = std::move(analyzedData);
    }
    analyzerConfig.textOptions = std::move(textOptions);
}
} // namespace OHOS::Ace::Framework
