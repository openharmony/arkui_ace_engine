/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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
#include "base/utils/utf_helper.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/functions/js_click_function.h"
#include "bridge/declarative_frontend/engine/functions/js_clipboard_function.h"
#include "bridge/declarative_frontend/engine/functions/js_event_function.h"
#include "bridge/declarative_frontend/engine/functions/js_on_child_touch_test_function.h"
#include "bridge/declarative_frontend/engine/functions/js_focus_function.h"
#include "bridge/declarative_frontend/engine/functions/js_gesture_judge_function.h"
#include "bridge/declarative_frontend/engine/functions/js_hover_function.h"
#include "bridge/declarative_frontend/engine/functions/js_key_function.h"
#include "bridge/declarative_frontend/engine/functions/js_on_area_change_function.h"
#include "bridge/declarative_frontend/engine/functions/js_on_size_change_function.h"
#include "bridge/declarative_frontend/engine/functions/js_should_built_in_recognizer_parallel_with_function.h"
#include "bridge/declarative_frontend/engine/functions/js_touch_intercept_function.h"
#include "bridge/declarative_frontend/engine/functions/js_touch_test_done_function.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_utils_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/js_ui_index.h"
#include "bridge/declarative_frontend/engine/js_converter.h"
#include "bridge/declarative_frontend/jsview/js_animatable_arithmetic.h"
#include "bridge/declarative_frontend/jsview/js_shape_abstract.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/jsview/js_view_context.h"
#include "bridge/declarative_frontend/jsview/models/view_abstract_model_impl.h"
#include "bridge/declarative_frontend/jsview/js_layoutable_view.h"
#include "core/event/focus_axis_event.h"
#include "canvas_napi/js_canvas.h"
#ifdef SUPPORT_DIGITAL_CROWN
#include "bridge/declarative_frontend/engine/functions/js_crown_function.h"
#endif
#include "interfaces/inner_api/ui_session/ui_session_manager.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components/theme/shadow_theme.h"
#ifdef PLUGIN_COMPONENT_SUPPORTED
#include "core/common/plugin_manager.h"
#endif
#include "interfaces/native/node/resource.h"

#include "core/common/card_scope.h"
#include "core/common/resource/resource_manager.h"
#include "core/common/resource/resource_wrapper.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/common/resource/resource_configuration.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/base/inspector.h"
#include "core/components_ng/pattern/toolbaritem/toolbaritem_model.h"
#include "core/event/key_event.h"

#include "interfaces/inner_api/ace_kit/include/ui/properties/safe_area_insets.h"

namespace OHOS::Ace::NG {
constexpr uint32_t DEFAULT_GRID_SPAN = 1;
constexpr int32_t DEFAULT_GRID_OFFSET = 0;
}

namespace OHOS::Ace {
namespace {
const std::string RESOURCE_TOKEN_PATTERN = "(app|sys|\\[.+?\\])\\.(\\S+?)\\.(\\S+)";
const std::string RESOURCE_NAME_PATTERN = "\\[(.+?)\\]";
constexpr int32_t DIRECTION_COUNT = 4;
constexpr char JS_TEXT_MENU_ID_CLASS_NAME[] = "TextMenuItemId";
constexpr int NUM1 = 1;
constexpr int NUM2 = 2;
const std::vector<HoverModeAreaType> HOVER_MODE_AREA_TYPE = { HoverModeAreaType::TOP_SCREEN,
    HoverModeAreaType::BOTTOM_SCREEN };
const std::string CUSTOM_SYMBOL_SUFFIX = "_CustomSymbol";
} // namespace

ViewAbstractModel* ViewAbstractModel::GetInstance()
{
#ifdef NG_BUILD
    static NG::ViewAbstractModelNG instance;
    return &instance;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        static NG::ViewAbstractModelNG instance;
        return &instance;
    } else {
        static Framework::ViewAbstractModelImpl instance;
        return &instance;
    }
#endif
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
constexpr uint32_t LAYOUT_SAFE_AREA_TYPE_LIMIT = 2;
constexpr uint32_t LAYOUT_SAFE_AREA_EDGE_LIMIT = 6;
constexpr int32_t MAX_ALIGN_VALUE = 8;
constexpr int32_t UNKNOWN_RESOURCE_ID = -1;
constexpr int32_t UNKNOWN_RESOURCE_TYPE = -1;
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
constexpr int32_t SECOND_INDEX = 2;
constexpr float DEFAULT_SCALE_LIGHT = 0.9f;
constexpr float DEFAULT_SCALE_MIDDLE_OR_HEAVY = 0.95f;
constexpr float MAX_ANGLE = 360.0f;
constexpr float DEFAULT_BIAS = 0.5f;
const std::vector<std::string> TEXT_DETECT_TYPES = { "phoneNum", "url", "email", "location", "datetime" };
const std::vector<std::string> RESOURCE_HEADS = { "app", "sys" };
const std::string BLOOM_RADIUS_SYS_RES_NAME = "sys.float.ohos_id_point_light_bloom_radius";
const std::string BLOOM_COLOR_SYS_RES_NAME = "sys.color.ohos_id_point_light_bloom_color";
const std::string ILLUMINATED_BORDER_WIDTH_SYS_RES_NAME = "sys.float.ohos_id_point_light_illuminated_border_width";
const std::vector<std::string> SLICE_KEYS = { "left", "right", "top", "bottom" };
const std::vector<int32_t> LENGTH_METRICS_KEYS {
    static_cast<int32_t>(ArkUIIndex::START), static_cast<int32_t>(ArkUIIndex::END),
    static_cast<int32_t>(ArkUIIndex::TOP), static_cast<int32_t>(ArkUIIndex::BOTTOM) };
const char* START_PROPERTY = "start";
const char* END_PROPERTY = "end";
const char* TOP_PROPERTY = "top";
const char* BOTTOM_PROPERTY = "bottom";
const char* LEFT_PROPERTY = "left";
const char* RIGHT_PROPERTY = "right";
const char* TOP_START_PROPERTY = "topStart";
const char* TOP_END_PROPERTY = "topEnd";
const char* TOP_LEFT_PROPERTY = "topLeft";
const char* TOP_RIGHT_PROPERTY = "topRight";
const char* BOTTOM_START_PROPERTY = "bottomStart";
const char* BOTTOM_END_PROPERTY = "bottomEnd";
const char* BOTTOM_LEFT_PROPERTY = "bottomLeft";
const char* BOTTOM_RIGHT_PROPERTY = "bottomRight";
const char* DEBUG_LINE_INFO_LINE = "$line";
const char* DEBUG_LINE_INFO_PACKAGE_NAME = "$packageName";

enum class MenuItemType { COPY, PASTE, CUT, SELECT_ALL, UNKNOWN, CAMERA_INPUT, AI_WRITER, TRANSLATE, SHARE, SEARCH };
enum class BackgroundType { CUSTOM_BUILDER, COLOR };

const int32_t NUM_0 = 0;
const int32_t NUM_1 = 1;
const int32_t NUM_2 = 2;

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
    JSViewAbstract::ParseJsDouble(jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::X)), xVal);
    JSViewAbstract::ParseJsDouble(jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::Y)), yVal);
    JSViewAbstract::ParseJsDouble(jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::Z)), zVal);
    scaleX = static_cast<float>(xVal);
    scaleY = static_cast<float>(yVal);
    scaleZ = static_cast<float>(zVal);
    // if specify centerX
    JSViewAbstract::ParseJsDimensionVp(jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::CENTER_X)), centerX);
    // if specify centerY
    JSViewAbstract::ParseJsDimensionVp(jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::CENTER_Y)), centerY);
}

void ParseJsTranslate(const JSRef<JSVal>& jsValue, CalcDimension& translateX, CalcDimension& translateY,
    CalcDimension& translateZ)
{
    if (!jsValue->IsObject()) {
        return;
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    JSViewAbstract::ParseJsDimensionVp(jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::X)), translateX);
    JSViewAbstract::ParseJsDimensionVp(jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::Y)), translateY);
    JSViewAbstract::ParseJsDimensionVp(jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::Z)), translateZ);
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
    auto jsRotateX = jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::X));
    auto jsRotateY = jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::Y));
    auto jsRotateZ = jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::Z));
    if (jsRotateX->IsUndefined()
        && jsRotateY->IsUndefined()
        && jsRotateZ->IsUndefined()) {
        GetDefaultRotateVector(dxVal, dyVal, dzVal);
    } else {
        JSViewAbstract::ParseJsDouble(jsRotateX, dxVal);
        JSViewAbstract::ParseJsDouble(jsRotateY, dyVal);
        JSViewAbstract::ParseJsDouble(jsRotateZ, dzVal);
    }
    rotate.xDirection = static_cast<float>(dxVal);
    rotate.yDirection = static_cast<float>(dyVal);
    rotate.zDirection = static_cast<float>(dzVal);
    // if specify centerX
    if (!JSViewAbstract::ParseJsDimensionVp(jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::CENTER_X)),
        rotate.centerX)) {
        rotate.centerX = Dimension(0.5f, DimensionUnit::PERCENT);
    }
    // if specify centerY
    if (!JSViewAbstract::ParseJsDimensionVp(jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::CENTER_Y)),
        rotate.centerY)) {
        rotate.centerY = Dimension(0.5f, DimensionUnit::PERCENT);
    }
    // if specify centerZ
    if (!JSViewAbstract::ParseJsDimensionVp(jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::CENTER_Z)),
        rotate.centerZ)) {
        rotate.centerZ = Dimension(0.5f, DimensionUnit::PERCENT);
    }
    // if specify angle
    JSViewAbstract::GetJsAngle(static_cast<int32_t>(ArkUIIndex::ANGLE), jsObj, angle);
    rotate.perspective = 0.0f;
    JSViewAbstract::GetJsPerspective(static_cast<int32_t>(ArkUIIndex::PERSPECTIVE), jsObj, rotate.perspective);
}

void ParseJsRotateAngle(const JSRef<JSVal>& jsValue, NG::RotateAngleOptions& rotateAngle)
{
    if (!jsValue->IsObject()) {
        return;
    }

    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);

    std::optional<float> angleX = 0.0;
    std::optional<float> angleY = 0.0;
    std::optional<float> angleZ = 0.0;

    JSViewAbstract::GetJsAngleWithDefault(static_cast<int32_t>(ArkUIIndex::ANGLE_X), jsObj, angleX, 0.0f);
    JSViewAbstract::GetJsAngleWithDefault(static_cast<int32_t>(ArkUIIndex::ANGLE_Y), jsObj, angleY, 0.0f);
    JSViewAbstract::GetJsAngleWithDefault(static_cast<int32_t>(ArkUIIndex::ANGLE_Z), jsObj, angleZ, 0.0f);

    rotateAngle.angleX = angleX.value_or(0.0f);
    rotateAngle.angleY = angleY.value_or(0.0f);
    rotateAngle.angleZ = angleZ.value_or(0.0f);

    // if specify centerX
    if (!JSViewAbstract::ParseJsDimensionVp(jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::CENTER_X)),
    rotateAngle.centerX)) {
        rotateAngle.centerX = Dimension(0.5f, DimensionUnit::PERCENT);
    }
    // if specify centerY
    if (!JSViewAbstract::ParseJsDimensionVp(jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::CENTER_Y)), 
    rotateAngle.centerY)) {
        rotateAngle.centerY = Dimension(0.5f, DimensionUnit::PERCENT);
    }
    // if specify centerZ
    if (!JSViewAbstract::ParseJsDimensionVp(jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::CENTER_Z)),
    rotateAngle.centerZ)) {
        rotateAngle.centerZ = Dimension(0.0f, DimensionUnit::VP);
    }
    rotateAngle.perspective = 0.0f;
    JSViewAbstract::GetJsPerspective(static_cast<int32_t>(ArkUIIndex::PERSPECTIVE), jsObj, rotateAngle.perspective);
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

void ParseDragPreviewMode(NG::DragPreviewOption& previewOption, int32_t modeValue, bool& isAuto)
{
    isAuto = false;
    switch (modeValue) {
        case static_cast<int32_t>(NG::DragPreviewMode::AUTO):
            previewOption.ResetDragPreviewMode();
            isAuto = true;
            break;
        case static_cast<int32_t>(NG::DragPreviewMode::DISABLE_SCALE):
            previewOption.isScaleEnabled = false;
            break;
        case static_cast<int32_t>(NG::DragPreviewMode::ENABLE_DEFAULT_SHADOW):
            previewOption.isDefaultShadowEnabled = true;
            break;
        case static_cast<int32_t>(NG::DragPreviewMode::ENABLE_DEFAULT_RADIUS):
            previewOption.isDefaultRadiusEnabled = true;
            break;
        case static_cast<int32_t>(NG::DragPreviewMode::ENABLE_DRAG_ITEM_GRAY_EFFECT):
            previewOption.isDefaultDragItemGrayEffectEnabled = true;
            break;
        case static_cast<int32_t>(NG::DragPreviewMode::ENABLE_MULTI_TILE_EFFECT):
            previewOption.isMultiTiled = true;
            break;
        case static_cast<int32_t>(NG::DragPreviewMode::ENABLE_TOUCH_POINT_CALCULATION_BASED_ON_FINAL_PREVIEW):
            previewOption.isTouchPointCalculationBasedOnFinalPreviewEnable = true;
            break;
        default:
            break;
    }
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
    auto index = pos + containCount;
    if (index < 0) {
        return std::string();
    }

    JSRef<JSVal> item = params->GetValueAt(static_cast<size_t>(index));
    if (type == "d") {
        if (item->IsNumber()) {
            return std::to_string(item->ToNumber<int32_t>());
        } else if (item->IsObject()) {
            int32_t result = 0;
            JSViewAbstract::ParseJsInteger(item, result);
            return std::to_string(result);
        }
    } else if (type == "s") {
        if (item->IsString()) {
            return item->ToString();
        } else if (item->IsObject()) {
            std::string result;
            JSViewAbstract::ParseJsString(item, result);
            return result;
        }
    } else if (type == "f") {
        if (item->IsNumber()) {
            return std::to_string(item->ToNumber<float>());
        } else if (item->IsObject()) {
            double result = 0.0;
            JSViewAbstract::ParseJsDouble(item, result);
            return std::to_string(result);
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

bool ParseLocationProps(const JSRef<JSObject>& sizeObj, CalcDimension& x, CalcDimension& y,
    RefPtr<ResourceObject>& xresObj, RefPtr<ResourceObject>& yresObj)
{
    JSRef<JSVal> xVal = sizeObj->GetProperty(static_cast<int32_t>(ArkUIIndex::X));
    JSRef<JSVal> yVal = sizeObj->GetProperty(static_cast<int32_t>(ArkUIIndex::Y));
    bool hasX = false;
    bool hasY = false;
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        hasX = JSViewAbstract::ParseJsDimensionNG(xVal, x, DimensionUnit::VP, xresObj);
        hasY = JSViewAbstract::ParseJsDimensionNG(yVal, y, DimensionUnit::VP, yresObj);
    } else {
        hasX = JSViewAbstract::ParseJsDimension(xVal, x, DimensionUnit::VP, xresObj);
        hasY = JSViewAbstract::ParseJsDimension(yVal, y, DimensionUnit::VP, yresObj);
    }
    return hasX || hasY;
}

void ParseLocationPropsEdgesResObj(EdgesParam& edges, const RefPtr<ResourceObject>& topResObj,
    const RefPtr<ResourceObject>& leftResObj, const RefPtr<ResourceObject>& bottomResObj,
    const RefPtr<ResourceObject>& rightResObj)
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    edges.resMap_.clear();
    if (topResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, EdgesParam& edges) {
            CalcDimension result;
            ResourceParseUtils::ParseResDimensionVpNG(resObj, result);
            edges.SetTop(result);
        };
        edges.AddResource("edges.top", topResObj, std::move(updateFunc));
    }
    if (leftResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, EdgesParam& edges) {
            CalcDimension result;
            ResourceParseUtils::ParseResDimensionVpNG(resObj, result);
            edges.SetLeft(result);
        };
        edges.AddResource("edges.left", leftResObj, std::move(updateFunc));
    }
    if (bottomResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, EdgesParam& edges) {
            CalcDimension result;
            ResourceParseUtils::ParseResDimensionVpNG(resObj, result);
            edges.SetBottom(result);
        };
        edges.AddResource("edges.bottom", bottomResObj, std::move(updateFunc));
    }
    if (rightResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, EdgesParam& edges) {
            CalcDimension result;
            ResourceParseUtils::ParseResDimensionVpNG(resObj, result);
            edges.SetRight(result);
        };
        edges.AddResource("edges.right", rightResObj, std::move(updateFunc));
    }
}

void ParseAllBorderRadiusesResObj(NG::BorderRadiusProperty& borderRadius, const RefPtr<ResourceObject>& topLeftResObj,
    const RefPtr<ResourceObject>& topRightResObj, const RefPtr<ResourceObject>& bottomLeftResObj,
    const RefPtr<ResourceObject>& bottomRightResObj)
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    borderRadius.resMap_.clear();
    if (topLeftResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderRadiusProperty& borderRadius) {
            CalcDimension result;
            ResourceParseUtils::ParseResDimensionVp(resObj, result);
            borderRadius.radiusTopLeft = result;
        };
        borderRadius.AddResource("borderRadius.topLeft", topLeftResObj, std::move(updateFunc));
    }
    if (topRightResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderRadiusProperty& borderRadius) {
            CalcDimension result;
            ResourceParseUtils::ParseResDimensionVp(resObj, result);
            borderRadius.radiusTopRight = result;
        };
        borderRadius.AddResource("borderRadius.topRight", topRightResObj, std::move(updateFunc));
    }
    if (bottomLeftResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderRadiusProperty& borderRadius) {
            CalcDimension result;
            ResourceParseUtils::ParseResDimensionVp(resObj, result);
            borderRadius.radiusBottomLeft = result;
        };
        borderRadius.AddResource("borderRadius.bottomLeft", bottomLeftResObj, std::move(updateFunc));
    }
    if (bottomRightResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderRadiusProperty& borderRadius) {
            CalcDimension result;
            ResourceParseUtils::ParseResDimensionVp(resObj, result);
            borderRadius.radiusBottomRight = result;
        };
        borderRadius.AddResource("borderRadius.bottomRight", bottomRightResObj, std::move(updateFunc));
    }
}

bool ParseLocationPropsEdges(const JSRef<JSObject>& edgesObj, EdgesParam& edges)
{
    bool useEdges = false;
    CalcDimension top;
    CalcDimension left;
    CalcDimension bottom;
    CalcDimension right;
    RefPtr<ResourceObject> topResObj;
    RefPtr<ResourceObject> leftResObj;
    RefPtr<ResourceObject> bottomResObj;
    RefPtr<ResourceObject> rightResObj;
    JSRef<JSVal> topVal = edgesObj->GetProperty(static_cast<int32_t>(ArkUIIndex::TOP));
    JSRef<JSVal> leftVal = edgesObj->GetProperty(static_cast<int32_t>(ArkUIIndex::LEFT));
    JSRef<JSVal> bottomVal = edgesObj->GetProperty(static_cast<int32_t>(ArkUIIndex::BOTTOM));
    JSRef<JSVal> rightVal = edgesObj->GetProperty(static_cast<int32_t>(ArkUIIndex::RIGHT));
    if (JSViewAbstract::ParseJsDimensionNG(topVal, top, DimensionUnit::VP, topResObj)) {
        edges.SetTop(top);
        useEdges = true;
    }
    if (JSViewAbstract::ParseJsDimensionNG(leftVal, left, DimensionUnit::VP, leftResObj)) {
        edges.SetLeft(left);
        useEdges = true;
    }
    if (JSViewAbstract::ParseJsDimensionNG(bottomVal, bottom, DimensionUnit::VP, bottomResObj)) {
        edges.SetBottom(bottom);
        useEdges = true;
    }
    if (JSViewAbstract::ParseJsDimensionNG(rightVal, right, DimensionUnit::VP, rightResObj)) {
        edges.SetRight(right);
        useEdges = true;
    }
    ParseLocationPropsEdgesResObj(edges, topResObj, leftResObj, bottomResObj, rightResObj);
    return useEdges;
}

decltype(JSViewAbstract::ParseJsLengthMetricsVp)* ParseJsLengthMetrics = JSViewAbstract::ParseJsLengthMetricsVp;

void ParseJsLengthMetricsToDimension(const JSRef<JSObject>& obj, Dimension& result, RefPtr<ResourceObject>& resourceObj)
{
    auto value = obj->GetProperty(static_cast<int32_t>(ArkUIIndex::VALUE));
    if (!value->IsNumber()) {
        return;
    }
    auto unit = DimensionUnit::VP;
    auto jsUnit = obj->GetProperty(static_cast<int32_t>(ArkUIIndex::UNIT));
    if (jsUnit->IsNumber()) {
        unit = static_cast<DimensionUnit>(jsUnit->ToNumber<int32_t>());
    }
    CalcDimension dimension(value->ToNumber<double>(), unit);
    result = dimension;
    auto jsRes = obj->GetProperty("res");
    if (SystemProperties::ConfigChangePerform() && !jsRes->IsUndefined() &&
        !jsRes->IsNull() && jsRes->IsObject()) {
        JSRef<JSObject> resObj = JSRef<JSObject>::Cast(jsRes);
        JSViewAbstract::CompleteResourceObject(resObj);
        resourceObj = JSViewAbstract::GetResourceObject(resObj);
    }
    return;
}

bool CheckLengthMetrics(const JSRef<JSObject>& object)
{
    if (object->HasProperty(static_cast<int32_t>(ArkUIIndex::START)) ||
        object->HasProperty(static_cast<int32_t>(ArkUIIndex::END)) ||
        object->HasProperty(static_cast<int32_t>(ArkUIIndex::TOP_START)) ||
        object->HasProperty(static_cast<int32_t>(ArkUIIndex::TOP_END)) ||
        object->HasProperty(static_cast<int32_t>(ArkUIIndex::BOTTOM_START)) ||
        object->HasProperty(static_cast<int32_t>(ArkUIIndex::BOTTOM_END))) {
        return true;
    }
    auto jsTop = object->GetProperty(static_cast<int32_t>(ArkUIIndex::TOP));
    if (jsTop->IsObject()) {
        JSRef<JSObject> topObj = JSRef<JSObject>::Cast(jsTop);
        if (topObj->HasProperty(static_cast<int32_t>(ArkUIIndex::VALUE))) {
            return true;
        }
    }
    auto jsBottom = object->GetProperty(static_cast<int32_t>(ArkUIIndex::BOTTOM));
    if (jsBottom->IsObject()) {
        JSRef<JSObject> bottomObj = JSRef<JSObject>::Cast(jsBottom);
        if (bottomObj->HasProperty(static_cast<int32_t>(ArkUIIndex::VALUE))) {
            return true;
        }
    }
    return false;
}

bool ParseLocalizedEdges(const JSRef<JSObject>& LocalizeEdgesObj, EdgesParam& edges)
{
    bool useLocalizedEdges = false;
    CalcDimension start;
    CalcDimension end;
    CalcDimension top;
    CalcDimension bottom;

    JSRef<JSVal> startVal = LocalizeEdgesObj->GetProperty(static_cast<int32_t>(ArkUIIndex::START));
    if (startVal->IsObject()) {
        JSRef<JSObject> startObj = JSRef<JSObject>::Cast(startVal);
        ParseJsLengthMetrics(startObj, start);
        edges.start = start;
        useLocalizedEdges = true;
    }
    JSRef<JSVal> endVal = LocalizeEdgesObj->GetProperty(static_cast<int32_t>(ArkUIIndex::END));
    if (endVal->IsObject()) {
        JSRef<JSObject> endObj = JSRef<JSObject>::Cast(endVal);
        ParseJsLengthMetrics(endObj, end);
        edges.end = end;
        useLocalizedEdges = true;
    }
    JSRef<JSVal> topVal = LocalizeEdgesObj->GetProperty(static_cast<int32_t>(ArkUIIndex::TOP));
    if (topVal->IsObject() && ParseJsLengthMetrics(JSRef<JSObject>::Cast(topVal), top)) {
        edges.SetTop(top);
        useLocalizedEdges = true;
    }
    JSRef<JSVal> bottomVal = LocalizeEdgesObj->GetProperty(static_cast<int32_t>(ArkUIIndex::BOTTOM));
    if (bottomVal->IsObject() && ParseJsLengthMetrics(JSRef<JSObject>::Cast(bottomVal), bottom)) {
        edges.SetBottom(bottom);
        useLocalizedEdges = true;
    }
    return useLocalizedEdges;
}

bool ParseMarkAnchorPosition(const JSRef<JSObject>& LocalizeEdgesObj, CalcDimension& x, CalcDimension& y)
{
    bool useMarkAnchorPosition = false;
    CalcDimension start;
    CalcDimension top;

    JSRef<JSVal> startVal = LocalizeEdgesObj->GetProperty(static_cast<int32_t>(ArkUIIndex::START));
    if (startVal->IsObject()) {
        JSRef<JSObject> startObj = JSRef<JSObject>::Cast(startVal);
        ParseJsLengthMetrics(startObj, start);
        x = start;
        useMarkAnchorPosition = true;
    }
    JSRef<JSVal> topVal = LocalizeEdgesObj->GetProperty(static_cast<int32_t>(ArkUIIndex::TOP));
    if (topVal->IsObject()) {
        JSRef<JSObject> topObj = JSRef<JSObject>::Cast(topVal);
        ParseJsLengthMetrics(topObj, top);
        y = top;
        useMarkAnchorPosition = true;
    }
    return useMarkAnchorPosition;
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
        if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            if (LessNotEqual(opacity, 0.0) || opacity > 1.0) {
                opacity = 1.0;
            }
        } else {
            opacity = std::clamp(opacity, 0.0, 1.0);
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
            appearEffect = JSViewAbstract::ParseChainedTransition(appearObj, context);
        }
        if (disappearJsVal->IsObject()) {
            auto disappearObj = JSRef<JSObject>::Cast(disappearJsVal);
            disappearEffect = JSViewAbstract::ParseChainedTransition(disappearObj, context);
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

std::string GetBundleNameFromContainer()
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, "");
    return container->GetBundleName();
}

std::string GetModuleNameFromContainer()
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, "");
    return container->GetModuleName();
}

void CompleteResourceObjectFromParams(
    int32_t resId, JSRef<JSObject>& jsObj, std::string& targetModule, ResourceType& resType, std::string& resName)
{
    JSRef<JSVal> type = jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::TYPE));
    int32_t typeNum = -1;
    if (type->IsNumber()) {
        typeNum = type->ToNumber<int32_t>();
    }

    JSRef<JSVal> args = jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::PARAMS));
    if (!args->IsArray()) {
        return;
    }
    JSRef<JSArray> params = JSRef<JSArray>::Cast(args);
    if (resId != UNKNOWN_RESOURCE_ID) {
        return;
    }
    JSRef<JSVal> identity = params->GetValueAt(0);

    bool isParseDollarResourceSuccess =
        JSViewAbstract::ParseDollarResource(identity, targetModule, resType, resName, typeNum == UNKNOWN_RESOURCE_TYPE);
    if (!isParseDollarResourceSuccess) {
        return;
    }

    std::regex resNameRegex(RESOURCE_NAME_PATTERN);
    std::smatch resNameResults;
    if (std::regex_match(targetModule, resNameResults, resNameRegex)) {
        jsObj->SetProperty<std::string>(static_cast<int32_t>(ArkUIIndex::MODULE_NAME), resNameResults[1]);
    }

    if (typeNum == UNKNOWN_RESOURCE_TYPE) {
        jsObj->SetProperty<int32_t>(static_cast<int32_t>(ArkUIIndex::TYPE), static_cast<int32_t>(resType));
    }
}

void CompleteResourceObjectFromId(
    JSRef<JSVal>& type, JSRef<JSObject>& jsObj, ResourceType& resType, const std::string& resName)
{
    JSRef<JSVal> args = jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::PARAMS));
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
        if (!type->IsEmpty()) {
            params->SetValueAt(paramIndex, type);
            paramIndex++;
        }
        for (auto tmpParam : tmpParams) {
            params->SetValueAt(paramIndex, tmpParam);
            paramIndex++;
        }
    } else {
        params->SetValueAt(0, name);
    }
    jsObj->SetProperty<int32_t>(static_cast<int32_t>(ArkUIIndex::ID), UNKNOWN_RESOURCE_ID);
    jsObj->SetProperty<int32_t>(static_cast<int32_t>(ArkUIIndex::TYPE), static_cast<int32_t>(resType));
    if (!jsObj->HasProperty(static_cast<int32_t>(ArkUIIndex::BUNDLE_NAME))) {
        jsObj->SetProperty<std::string>(static_cast<int32_t>(ArkUIIndex::BUNDLE_NAME), "");
    }
    if (!jsObj->HasProperty(static_cast<int32_t>(ArkUIIndex::MODULE_NAME))) {
        jsObj->SetProperty<std::string>(static_cast<int32_t>(ArkUIIndex::MODULE_NAME), "");
    }
}

void CheckDimensionUnit(CalcDimension& checkDimension, bool notPercent, bool notNegative)
{
    if (notPercent && checkDimension.Unit() == DimensionUnit::PERCENT) {
        checkDimension.Reset();
        return;
    }
    if (notNegative && checkDimension.IsNegative()) {
        checkDimension.Reset();
        return;
    }
}

void ParseEdgeColors(const JSRef<JSObject>& object, CommonColor& commonColor)
{
    Color left;
    RefPtr<ResourceObject> leftResObj;
    if (JSViewAbstract::ParseJsColor(
        object->GetProperty(static_cast<int32_t>(ArkUIIndex::LEFT)), left, leftResObj)) {
        commonColor.left = left;
    }
    Color right;
    RefPtr<ResourceObject> rightResObj;
    if (JSViewAbstract::ParseJsColor(
        object->GetProperty(static_cast<int32_t>(ArkUIIndex::RIGHT)), right, rightResObj)) {
        commonColor.right = right;
    }
    Color top;
    RefPtr<ResourceObject> topResObj;
    if (JSViewAbstract::ParseJsColor(
        object->GetProperty(static_cast<int32_t>(ArkUIIndex::TOP)), top, topResObj)) {
        commonColor.top = top;
    }
    Color bottom;
    RefPtr<ResourceObject> bottomResObj;
    if (JSViewAbstract::ParseJsColor(
        object->GetProperty(static_cast<int32_t>(ArkUIIndex::BOTTOM)), bottom, bottomResObj)) {
        commonColor.bottom = bottom;
    }
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    if (leftResObj) {
        commonColor.leftResObj = leftResObj;
    }
    if (rightResObj) {
        commonColor.rightResObj = rightResObj;
    }
    if (topResObj) {
        commonColor.topResObj = topResObj;
    }
    if (bottomResObj) {
        commonColor.bottomResObj = bottomResObj;
    }
}

void ParseLocalizedEdgeStartColorsForOutLineColor(const JSRef<JSObject>& object, NG::BorderColorProperty& borderColors)
{
    if (object->IsUndefined()) {
        return;
    }
    RefPtr<ResourceObject> startResObj;
    Color start;
    if (JSViewAbstract::ParseJsColor(object->GetProperty(static_cast<int32_t>(ArkUIIndex::START)), start, startResObj)) {
        borderColors.leftColor = start;
    }
    if (startResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& startResObj, NG::BorderColorProperty& borderColors) {
            Color color;
            ResourceParseUtils::ParseResColor(startResObj, color);
            borderColors.leftColor = color;
        };
        borderColors.AddResource("localizedEdgeColor.start", startResObj, std::move(updateFunc));
    }
}

void ParseLocalizedEdgeEndColorsForOutLineColor(const JSRef<JSObject>& object, NG::BorderColorProperty& borderColors)
{
    if (object->IsUndefined()) {
        return;
    }
    RefPtr<ResourceObject> endResObj;
    Color end;
    if (JSViewAbstract::ParseJsColor(object->GetProperty(static_cast<int32_t>(ArkUIIndex::END)), end, endResObj)) {
        borderColors.rightColor = end;
    }
    if (endResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& endResObj, NG::BorderColorProperty& borderColors) {
            Color color;
            ResourceParseUtils::ParseResColor(endResObj, color);
            borderColors.rightColor = color;
        };
        borderColors.AddResource("localizedEdgeColor.end", endResObj, std::move(updateFunc));
    }
}

void ParseLocalizedEdgeTopColorsForOutLineColor(const JSRef<JSObject>& object, NG::BorderColorProperty& borderColors)
{
    if (object->IsUndefined()) {
        return;
    }
    RefPtr<ResourceObject> topResObj;
    Color top;
    if (JSViewAbstract::ParseJsColor(object->GetProperty(static_cast<int32_t>(ArkUIIndex::TOP)), top, topResObj)) {
        borderColors.topColor = top;
    }
    if (topResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& topResObj, NG::BorderColorProperty& borderColors) {
            Color color;
            ResourceParseUtils::ParseResColor(topResObj, color);
            borderColors.topColor = color;
        };
        borderColors.AddResource("localizedEdgeColor.top", topResObj, std::move(updateFunc));
    }
}

void ParseLocalizedEdgeBottomColorsForOutLineColor(const JSRef<JSObject>& object, NG::BorderColorProperty& borderColors)
{
    if (object->IsUndefined()) {
        return;
    }
    RefPtr<ResourceObject> bottomResObj;
    Color bottom;
    if (JSViewAbstract::ParseJsColor(object->GetProperty(static_cast<int32_t>(ArkUIIndex::BOTTOM)), bottom, bottomResObj)) {
        borderColors.bottomColor = bottom;
    }
    if (bottomResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& bottomResObj, NG::BorderColorProperty& borderColors) {
            Color color;
            ResourceParseUtils::ParseResColor(bottomResObj, color);
            borderColors.bottomColor = color;
        };
        borderColors.AddResource("localizedEdgeColor.bottom", bottomResObj, std::move(updateFunc));
    }
}

void ParseLocalizedEdgeColorsForOutLineColor(const JSRef<JSObject>& object, NG::BorderColorProperty& borderColors)
{
    ParseLocalizedEdgeStartColorsForOutLineColor(object, borderColors);
    ParseLocalizedEdgeEndColorsForOutLineColor(object, borderColors);
    ParseLocalizedEdgeTopColorsForOutLineColor(object, borderColors);
    ParseLocalizedEdgeBottomColorsForOutLineColor(object, borderColors);
}

void ParseEdgeLeftColorsForOutLineColor(const JSRef<JSObject>& object, NG::BorderColorProperty& borderColors)
{
    if (object->IsUndefined()) {
        return;
    }
    RefPtr<ResourceObject> leftResObj;
    Color left;
    if (JSViewAbstract::ParseJsColor(object->GetProperty(static_cast<int32_t>(ArkUIIndex::LEFT)), left, leftResObj)) {
        borderColors.leftColor = left;
    }
    if (leftResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& leftResObj, NG::BorderColorProperty& borderColors) {
            Color color;
            ResourceParseUtils::ParseResColor(leftResObj, color);
            borderColors.leftColor = color;
        };
        borderColors.AddResource("outLineColor.edgeColor.left", leftResObj, std::move(updateFunc));
    }
}

void ParseEdgeRightColorsForOutLineColor(const JSRef<JSObject>& object, NG::BorderColorProperty& borderColors)
{
    if (object->IsUndefined()) {
        return;
    }
    RefPtr<ResourceObject> rightResObj;
    Color right;
    if (JSViewAbstract::ParseJsColor(object->GetProperty(static_cast<int32_t>(ArkUIIndex::RIGHT)), right, rightResObj)) {
        borderColors.rightColor = right;
    }
    if (rightResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderColorProperty& borderColors) {
            Color color;
            ResourceParseUtils::ParseResColor(resObj, color);
            borderColors.rightColor = color;
        };
        borderColors.AddResource("outLineColor.edgeColor.right", rightResObj, std::move(updateFunc));
    }
}

void ParseEdgeTopColorsForOutLineColor(const JSRef<JSObject>& object, NG::BorderColorProperty& borderColors)
{
    if (object->IsUndefined()) {
        return;
    }
    RefPtr<ResourceObject> topResObj;
    Color top;
    if (JSViewAbstract::ParseJsColor(object->GetProperty(static_cast<int32_t>(ArkUIIndex::TOP)), top, topResObj)) {
        borderColors.topColor = top;
    }
    if (topResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& topResObj, NG::BorderColorProperty& borderColors) {
            Color color;
            ResourceParseUtils::ParseResColor(topResObj, color);
            borderColors.topColor = color;
        };
        borderColors.AddResource("outLineColor.edgeColor.top", topResObj, std::move(updateFunc));
    }
}

void ParseEdgeBottomColorsForOutLineColor(const JSRef<JSObject>& object, NG::BorderColorProperty& borderColors)
{
    if (object->IsUndefined()) {
        return;
    }
    RefPtr<ResourceObject> bottomResObj;
    Color bottom;
    if (JSViewAbstract::ParseJsColor(object->GetProperty(static_cast<int32_t>(ArkUIIndex::BOTTOM)), bottom, bottomResObj)) {
        borderColors.bottomColor = bottom;
    }
    if (bottomResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderColorProperty& borderColors) {
            Color color;
            ResourceParseUtils::ParseResColor(resObj, color);
            borderColors.bottomColor = color;
        };
        borderColors.AddResource("outLineColor.edgeColor.bottom", bottomResObj, std::move(updateFunc));
    }
}

void ParseEdgeColorsForOutLineColor(const JSRef<JSObject>& object, NG::BorderColorProperty& borderColors)
{
    ParseEdgeLeftColorsForOutLineColor(object, borderColors);
    ParseEdgeRightColorsForOutLineColor(object, borderColors);
    ParseEdgeTopColorsForOutLineColor(object, borderColors);
    ParseEdgeBottomColorsForOutLineColor(object, borderColors);
}

void ParseLocalizedEdgeColors(const JSRef<JSObject>& object, LocalizedColor& localizedColor)
{
    Color start;
    RefPtr<ResourceObject> startResObj;
    if (JSViewAbstract::ParseJsColor(
        object->GetProperty(static_cast<int32_t>(ArkUIIndex::START)), start, startResObj)) {
        localizedColor.start = start;
    }
    Color end;
    RefPtr<ResourceObject> endResObj;
    if (JSViewAbstract::ParseJsColor(
        object->GetProperty(static_cast<int32_t>(ArkUIIndex::END)), end, endResObj)) {
        localizedColor.end = end;
    }
    Color top;
    RefPtr<ResourceObject> topResObj;
    if (JSViewAbstract::ParseJsColor(
        object->GetProperty(static_cast<int32_t>(ArkUIIndex::TOP)), top, topResObj)) {
        localizedColor.top = top;
    }
    Color bottom;
    RefPtr<ResourceObject> bottomResObj;
    if (JSViewAbstract::ParseJsColor(
        object->GetProperty(static_cast<int32_t>(ArkUIIndex::BOTTOM)), bottom, bottomResObj)) {
        localizedColor.bottom = bottom;
    }
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    if (startResObj) {
        localizedColor.startResObj = startResObj;
    }
    if (endResObj) {
        localizedColor.endResObj = endResObj;
    }
    if (topResObj) {
        localizedColor.topResObj = topResObj;
    }
    if (bottomResObj) {
        localizedColor.bottomResObj = bottomResObj;
    }
}

bool ParseCommonEdgeColors(const JSRef<JSObject>& object, CommonColor& commonColor)
{
    if (object->HasProperty(static_cast<int32_t>(ArkUIIndex::START)) ||
        object->HasProperty(static_cast<int32_t>(ArkUIIndex::END))) {
        LocalizedColor localizedColor;
        ParseLocalizedEdgeColors(object, localizedColor);
        commonColor.top = localizedColor.top;
        commonColor.bottom = localizedColor.bottom;
        commonColor.left = localizedColor.start;
        commonColor.right = localizedColor.end;
        commonColor.topResObj = localizedColor.topResObj;
        commonColor.bottomResObj = localizedColor.bottomResObj;
        commonColor.leftResObj = localizedColor.startResObj;
        commonColor.rightResObj = localizedColor.endResObj;
        return true;
    }
    ParseEdgeColors(object, commonColor);
    return false;
}

void ParseEdgeWidths(const JSRef<JSObject>& object, CommonCalcDimension& commonCalcDimension, bool notNegative)
{
    CalcDimension left;
    if (JSViewAbstract::ParseJsDimensionVp(object->GetProperty(static_cast<int32_t>(ArkUIIndex::LEFT)), left)) {
        CheckDimensionUnit(left, true, notNegative);
        commonCalcDimension.left = left;
    }
    CalcDimension right;
    if (JSViewAbstract::ParseJsDimensionVp(object->GetProperty(static_cast<int32_t>(ArkUIIndex::RIGHT)), right)) {
        CheckDimensionUnit(right, true, notNegative);
        commonCalcDimension.right = right;
    }
    CalcDimension top;
    if (JSViewAbstract::ParseJsDimensionVp(object->GetProperty(static_cast<int32_t>(ArkUIIndex::TOP)), top)) {
        CheckDimensionUnit(top, true, notNegative);
        commonCalcDimension.top = top;
    }
    CalcDimension bottom;
    if (JSViewAbstract::ParseJsDimensionVp(object->GetProperty(static_cast<int32_t>(ArkUIIndex::BOTTOM)), bottom)) {
        CheckDimensionUnit(bottom, true, notNegative);
        commonCalcDimension.bottom = bottom;
    }
}

void ParseEdgeWidthsResObjFunc(NG::BorderWidthProperty& borderWidth, RefPtr<ResourceObject> leftResObj,
    RefPtr<ResourceObject> rightResObj, RefPtr<ResourceObject> topResObj, RefPtr<ResourceObject> bottomResObj)
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    borderWidth.resMap_.clear();
    if (leftResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderWidthProperty& borderWidth) {
            CalcDimension result;
            ResourceParseUtils::ParseResDimensionVp(resObj, result);
            borderWidth.leftDimen = result;
            borderWidth.multiValued = true;
        };
        borderWidth.AddResource("borderWidth.left", leftResObj, std::move(updateFunc));
    }
    if (rightResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderWidthProperty& borderWidth) {
            CalcDimension result;
            ResourceParseUtils::ParseResDimensionVp(resObj, result);
            borderWidth.rightDimen = result;
            borderWidth.multiValued = true;
        };
        borderWidth.AddResource("borderWidth.right", rightResObj, std::move(updateFunc));
    }
    if (topResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderWidthProperty& borderWidth) {
            CalcDimension result;
            ResourceParseUtils::ParseResDimensionVp(resObj, result);
            borderWidth.topDimen = result;
            borderWidth.multiValued = true;
        };
        borderWidth.AddResource("borderWidth.top", topResObj, std::move(updateFunc));
    }
    if (bottomResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderWidthProperty& borderWidth) {
            CalcDimension result;
            ResourceParseUtils::ParseResDimensionVp(resObj, result);
            borderWidth.bottomDimen = result;
            borderWidth.multiValued = true;
        };
        borderWidth.AddResource("borderWidth.bottom", bottomResObj, std::move(updateFunc));
    }
}

void ParseEdgeWidthsForDashParamsResObj(NG::BorderWidthProperty& borderWidth, RefPtr<ResourceObject> topResObj,
    RefPtr<ResourceObject> rightResObj, RefPtr<ResourceObject> bottomResObj, RefPtr<ResourceObject> leftResObj)
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    borderWidth.resMap_.clear();
    if (leftResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderWidthProperty& borderWidth) {
            CalcDimension result;
            if (ResourceParseUtils::ParseResDimensionVp(resObj, result)) {
                CheckDimensionUnit(result, true, false);
                borderWidth.leftDimen = result;
            } else {
                borderWidth.leftDimen = static_cast<CalcDimension>(-1);
            }
        };
        borderWidth.AddResource("borderWidth.left", leftResObj, std::move(updateFunc));
    }
    if (rightResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderWidthProperty& borderWidth) {
            CalcDimension result;
            if (ResourceParseUtils::ParseResDimensionVp(resObj, result)) {
                CheckDimensionUnit(result, true, false);
                borderWidth.rightDimen = result;
            } else {
                borderWidth.rightDimen = static_cast<CalcDimension>(-1);
            }
        };
        borderWidth.AddResource("borderWidth.right", rightResObj, std::move(updateFunc));
    }
    if (topResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderWidthProperty& borderWidth) {
            CalcDimension result;
            if (ResourceParseUtils::ParseResDimensionVp(resObj, result)) {
                CheckDimensionUnit(result, true, false);
                borderWidth.topDimen = result;
            } else {
                borderWidth.topDimen = static_cast<CalcDimension>(-1);
            }
        };
        borderWidth.AddResource("borderWidth.top", topResObj, std::move(updateFunc));
    }
    if (bottomResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderWidthProperty& borderWidth) {
            CalcDimension result;
            if (ResourceParseUtils::ParseResDimensionVp(resObj, result)) {
                CheckDimensionUnit(result, true, false);
                borderWidth.bottomDimen = result;
            } else {
                borderWidth.bottomDimen = static_cast<CalcDimension>(-1);
            }
        };
        borderWidth.AddResource("borderWidth.bottom", bottomResObj, std::move(updateFunc));
    }
}

void ParseEdgeWidthsResObj(const JSRef<JSObject>& object, NG::BorderWidthProperty& borderWidth, bool notNegative)
{
    CalcDimension left;
    RefPtr<ResourceObject> leftResObj;
    if (JSViewAbstract::ParseJsDimensionVp(
            object->GetProperty(static_cast<int32_t>(ArkUIIndex::LEFT)), left, leftResObj)) {
        CheckDimensionUnit(left, true, notNegative);
        borderWidth.leftDimen = left;
        borderWidth.multiValued = true;
    }
    CalcDimension right;
    RefPtr<ResourceObject> rightResObj;
    if (JSViewAbstract::ParseJsDimensionVp(
            object->GetProperty(static_cast<int32_t>(ArkUIIndex::RIGHT)), right, rightResObj)) {
        CheckDimensionUnit(right, true, notNegative);
        borderWidth.rightDimen = right;
        borderWidth.multiValued = true;
    }
    CalcDimension top;
    RefPtr<ResourceObject> topResObj;
    if (JSViewAbstract::ParseJsDimensionVp(
            object->GetProperty(static_cast<int32_t>(ArkUIIndex::TOP)), top, topResObj)) {
        CheckDimensionUnit(top, true, notNegative);
        borderWidth.topDimen = top;
        borderWidth.multiValued = true;
    }
    CalcDimension bottom;
    RefPtr<ResourceObject> bottomResObj;
    if (JSViewAbstract::ParseJsDimensionVp(
            object->GetProperty(static_cast<int32_t>(ArkUIIndex::BOTTOM)), bottom, bottomResObj)) {
        CheckDimensionUnit(bottom, true, notNegative);
        borderWidth.bottomDimen = bottom;
        borderWidth.multiValued = true;
    }
    ParseEdgeWidthsResObjFunc(borderWidth, leftResObj, rightResObj, topResObj, bottomResObj);
}

void ParseEdgeWidthsForDashParamsResObj(
    const JSRef<JSObject>& object, NG::BorderWidthProperty& borderWidth, CalcDimension defaultValue)
{
    CalcDimension left;
    RefPtr<ResourceObject> leftResObj;
    if (JSViewAbstract::ParseJsDimensionVpNG(object->GetProperty(LEFT_PROPERTY), left, leftResObj, true)) {
        CheckDimensionUnit(left, true, false);
        borderWidth.leftDimen = left;
    } else {
        borderWidth.leftDimen = defaultValue;
    }
    CalcDimension right;
    RefPtr<ResourceObject> rightResObj;
    if (JSViewAbstract::ParseJsDimensionVpNG(object->GetProperty(RIGHT_PROPERTY), right, rightResObj, true)) {
        CheckDimensionUnit(right, true, false);
        borderWidth.rightDimen = right;
    } else {
        borderWidth.rightDimen = defaultValue;
    }
    CalcDimension top;
    RefPtr<ResourceObject> topResObj;
    if (JSViewAbstract::ParseJsDimensionVpNG(object->GetProperty(TOP_PROPERTY), top, topResObj, true)) {
        CheckDimensionUnit(top, true, false);
        borderWidth.topDimen = top;
    } else {
        borderWidth.topDimen = defaultValue;
    }
    CalcDimension bottom;
    RefPtr<ResourceObject> bottomResObj;
    if (JSViewAbstract::ParseJsDimensionVpNG(object->GetProperty(BOTTOM_PROPERTY), bottom, bottomResObj, true)) {
        CheckDimensionUnit(bottom, false, true);
        borderWidth.bottomDimen = bottom;
    } else {
        borderWidth.bottomDimen = defaultValue;
    }
    ParseEdgeWidthsForDashParamsResObj(borderWidth, leftResObj, rightResObj, topResObj, bottomResObj);
}

void ParseEdgeWidthsProps(const JSRef<JSObject>& object, CommonCalcDimension& commonCalcDimension, bool notPercent,
    bool notNegative, CalcDimension defaultValue)
{
    CalcDimension left;
    if (JSViewAbstract::ParseJsDimensionVpNG(object->GetProperty(LEFT_PROPERTY), left, true)) {
        CheckDimensionUnit(left, notPercent, notNegative);
        commonCalcDimension.left = left;
    } else {
        commonCalcDimension.left = defaultValue;
    }
    CalcDimension right;
    if (JSViewAbstract::ParseJsDimensionVpNG(object->GetProperty(RIGHT_PROPERTY), right, true)) {
        CheckDimensionUnit(right, notPercent, notNegative);
        commonCalcDimension.right = right;
    } else {
        commonCalcDimension.right = defaultValue;
    }
    CalcDimension top;
    if (JSViewAbstract::ParseJsDimensionVpNG(object->GetProperty(TOP_PROPERTY), top, true)) {
        CheckDimensionUnit(top, notPercent, notNegative);
        commonCalcDimension.top = top;
    } else {
        commonCalcDimension.top = defaultValue;
    }
    CalcDimension bottom;
    if (JSViewAbstract::ParseJsDimensionVpNG(object->GetProperty(BOTTOM_PROPERTY), bottom, true)) {
        CheckDimensionUnit(bottom, false, true);
        commonCalcDimension.bottom = bottom;
    } else {
        commonCalcDimension.bottom = defaultValue;
    }
}

void ParseLocalizedEdgeWidths(const JSRef<JSObject>& object, LocalizedCalcDimension& localizedCalcDimension,
                              bool notNegative)
{
    auto jsStart = object->GetProperty(static_cast<int32_t>(ArkUIIndex::START));
    if (jsStart->IsObject()) {
        JSRef<JSObject> startObj = JSRef<JSObject>::Cast(jsStart);
        CalcDimension calcDimension;
        if (ParseJsLengthMetrics(startObj, calcDimension)) {
            CheckDimensionUnit(calcDimension, true, notNegative);
            localizedCalcDimension.start = calcDimension;
        }
    }
    auto jsEnd = object->GetProperty(static_cast<int32_t>(ArkUIIndex::END));
    if (jsEnd->IsObject()) {
        JSRef<JSObject> endObj = JSRef<JSObject>::Cast(jsEnd);
        CalcDimension calcDimension;
        if (ParseJsLengthMetrics(endObj, calcDimension)) {
            CheckDimensionUnit(calcDimension, true, notNegative);
            localizedCalcDimension.end = calcDimension;
        }
    }
    auto jsTop = object->GetProperty(static_cast<int32_t>(ArkUIIndex::TOP));
    if (jsTop->IsObject()) {
        JSRef<JSObject> topObj = JSRef<JSObject>::Cast(jsTop);
        CalcDimension calcDimension;
        if (ParseJsLengthMetrics(topObj, calcDimension)) {
            CheckDimensionUnit(calcDimension, true, notNegative);
            localizedCalcDimension.top = calcDimension;
        }
    }
    auto jsBottom = object->GetProperty(static_cast<int32_t>(ArkUIIndex::BOTTOM));
    if (jsBottom->IsObject()) {
        JSRef<JSObject> bottomObj = JSRef<JSObject>::Cast(jsBottom);
        CalcDimension calcDimension;
        if (ParseJsLengthMetrics(bottomObj, calcDimension)) {
            CheckDimensionUnit(calcDimension, true, notNegative);
            localizedCalcDimension.bottom = calcDimension;
        }
    }
}

void ParseLocalizedEdgeWidthsProps(const JSRef<JSObject>& object, LocalizedCalcDimension& localizedCalcDimension)
{
    if (object->HasProperty(START_PROPERTY) && object->GetProperty(START_PROPERTY)->IsObject()) {
        JSRef<JSObject> startObj = JSRef<JSObject>::Cast(object->GetProperty(START_PROPERTY));
        CalcDimension calcDimension;
        if (ParseJsLengthMetrics(startObj, calcDimension)) {
            CheckDimensionUnit(calcDimension, false, true);
            localizedCalcDimension.start = calcDimension;
        }
    }
    if (object->HasProperty(END_PROPERTY) && object->GetProperty(END_PROPERTY)->IsObject()) {
        JSRef<JSObject> endObj = JSRef<JSObject>::Cast(object->GetProperty(END_PROPERTY));
        CalcDimension calcDimension;
        if (ParseJsLengthMetrics(endObj, calcDimension)) {
            CheckDimensionUnit(calcDimension, false, true);
            localizedCalcDimension.end = calcDimension;
        }
    }
    if (object->HasProperty(TOP_PROPERTY) && object->GetProperty(TOP_PROPERTY)->IsObject()) {
        JSRef<JSObject> topObj = JSRef<JSObject>::Cast(object->GetProperty(TOP_PROPERTY));
        CalcDimension calcDimension;
        if (ParseJsLengthMetrics(topObj, calcDimension)) {
            CheckDimensionUnit(calcDimension, false, true);
            localizedCalcDimension.top = calcDimension;
        }
    }
    if (object->HasProperty(BOTTOM_PROPERTY) && object->GetProperty(BOTTOM_PROPERTY)->IsObject()) {
        JSRef<JSObject> bottomObj = JSRef<JSObject>::Cast(object->GetProperty(BOTTOM_PROPERTY));
        CalcDimension calcDimension;
        if (ParseJsLengthMetrics(bottomObj, calcDimension)) {
            CheckDimensionUnit(calcDimension, false, true);
            localizedCalcDimension.bottom = calcDimension;
        }
    }
}

bool ParseCommonEdgeWidths(const JSRef<JSObject>& object, CommonCalcDimension& commonCalcDimension, bool notNegative)
{
    if (CheckLengthMetrics(object)) {
        LocalizedCalcDimension localizedCalcDimension;
        ParseLocalizedEdgeWidths(object, localizedCalcDimension, notNegative);
        commonCalcDimension.top = localizedCalcDimension.top;
        commonCalcDimension.bottom = localizedCalcDimension.bottom;
        commonCalcDimension.left = localizedCalcDimension.start;
        commonCalcDimension.right = localizedCalcDimension.end;
        return true;
    }
    if (!SystemProperties::ConfigChangePerform()) {
        ParseEdgeWidths(object, commonCalcDimension, notNegative);
    }
    return false;
}

bool ParseCommonEdgeWidthsForDashParams(const JSRef<JSObject>& object, CommonCalcDimension& commonCalcDimension)
{
    if (CheckLengthMetrics(object)) {
        LocalizedCalcDimension localizedCalcDimension;
        ParseLocalizedEdgeWidths(object, localizedCalcDimension, false);
        auto isRightToLeft = AceApplicationInfo::GetInstance().IsRightToLeft();
        commonCalcDimension.top = localizedCalcDimension.top;
        commonCalcDimension.bottom = localizedCalcDimension.bottom;
        commonCalcDimension.left = isRightToLeft ? localizedCalcDimension.end : localizedCalcDimension.start;
        commonCalcDimension.right = isRightToLeft ? localizedCalcDimension.start : localizedCalcDimension.end;
        return true;
    }
    ParseEdgeWidthsProps(object, commonCalcDimension, true, false, static_cast<CalcDimension>(-1));
    return false;
}

void ParseCommonEdgeWidthsProps(const JSRef<JSObject>& object, CommonCalcDimension& commonCalcDimension)
{
    if (CheckLengthMetrics(object)) {
        LocalizedCalcDimension localizedCalcDimension;
        ParseLocalizedEdgeWidthsProps(object, localizedCalcDimension);
        auto isRightToLeft = AceApplicationInfo::GetInstance().IsRightToLeft();
        commonCalcDimension.top = localizedCalcDimension.top;
        commonCalcDimension.bottom = localizedCalcDimension.bottom;
        commonCalcDimension.left = isRightToLeft ? localizedCalcDimension.end : localizedCalcDimension.start;
        commonCalcDimension.right = isRightToLeft ? localizedCalcDimension.start : localizedCalcDimension.end;
        return;
    }
    ParseEdgeWidthsProps(object, commonCalcDimension, false, true, 0.0_vp);
}

std::function<void(bool)> ParseTransitionCallback(const JSRef<JSFunc>& jsFunc, const JSExecutionContext& context)
{
    auto jsFuncFinish = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(jsFunc));
    auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto finishCallback = [execCtx = context, jsFuncFinish, targetNode](bool isTransitionIn) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        NG::PipelineContext::SetCallBackNode(targetNode);
        JSRef<JSVal> newJSVal = JSRef<JSVal>::Make(ToJSValue(isTransitionIn));
        jsFuncFinish->ExecuteJS(1, &newJSVal);
    };
    return finishCallback;
}

NG::CalcLength ConvertCalcLength(CalcDimension& target)
{
    NG::CalcLength targetLength = (target.Unit() == DimensionUnit::CALC) ?
        NG::CalcLength(target.IsNonNegative() ? target.CalcValue() : CalcDimension().CalcValue()) :
        NG::CalcLength(target.IsNonNegative() ? target : CalcDimension());
    return targetLength;
}

void SetConstraintSize(const RefPtr<ResourceObject>& minWidthResObj, const RefPtr<ResourceObject>& maxWidthResObj,
    const RefPtr<ResourceObject>& minHeightResObj, const RefPtr<ResourceObject>& maxHeightResObj)
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    if (minWidthResObj) {
        ViewAbstractModel::GetInstance()->SetMinWidth(minWidthResObj);
    }
    if (maxWidthResObj) {
        ViewAbstractModel::GetInstance()->SetMaxWidth(maxWidthResObj);
    }
    if (minHeightResObj) {
        ViewAbstractModel::GetInstance()->SetMinHeight(minHeightResObj);
    }
    if (maxHeightResObj) {
        ViewAbstractModel::GetInstance()->SetMaxHeight(maxHeightResObj);
    }
}
} // namespace

RefPtr<ResourceObject> JSViewAbstract::GetResourceObject(const JSRef<JSObject>& jsObj)
{
    auto id = jsObj->GetProperty("id")->ToNumber<int32_t>();
    auto type = jsObj->GetProperty("type")->ToNumber<int32_t>();
    auto args = jsObj->GetProperty("params");

    std::string bundleName;
    std::string moduleName;
    auto bundle = jsObj->GetProperty("bundleName");
    auto module = jsObj->GetProperty("moduleName");
    if (bundle->IsString() && module->IsString()) {
        bundleName = bundle->ToString();
        moduleName = module->ToString();
    }
    if (!args->IsArray()) {
        return nullptr;
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
    auto resourceObject = AceType::MakeRefPtr<ResourceObject>(
        id, type, resObjParamsList, bundleName, moduleName, Container::CurrentIdSafely());
    return resourceObject;
}

RefPtr<ResourceObject> GetResourceObjectByBundleAndModule(const JSRef<JSObject>& jsObj)
{
    auto bundleName = jsObj->GetPropertyValue<std::string>(static_cast<int32_t>(ArkUIIndex::BUNDLE_NAME), "");
    auto moduleName = jsObj->GetPropertyValue<std::string>(static_cast<int32_t>(ArkUIIndex::MODULE_NAME), "");
    auto resourceObject = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, Container::CurrentIdSafely());
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

uint32_t ColorAlphaAdapt(uint32_t origin)
{
    uint32_t result = origin;
    if (origin >> COLOR_ALPHA_OFFSET == 0) {
        result = origin | COLOR_ALPHA_VALUE;
    }
    return result;
}

MenuItemType StringToMenuItemType(std::string_view id)
{
    static const std::unordered_map<std::string_view, MenuItemType> keyMenuItemMap = {
        { "OH_DEFAULT_COPY", MenuItemType::COPY },
        { "OH_DEFAULT_PASTE", MenuItemType::PASTE },
        { "OH_DEFAULT_CUT", MenuItemType::CUT },
        { "OH_DEFAULT_SELECT_ALL", MenuItemType::SELECT_ALL },
        { "OH_DEFAULT_CAMERA_INPUT", MenuItemType::CAMERA_INPUT },
        { "OH_DEFAULT_AI_WRITE", MenuItemType::AI_WRITER },
        { "OH_DEFAULT_TRANSLATE", MenuItemType::TRANSLATE },
        { "OH_DEFAULT_SHARE", MenuItemType::SHARE },
        { "OH_DEFAULT_SEARCH", MenuItemType::SEARCH },
    };

    auto item = keyMenuItemMap.find(id);
    return item != keyMenuItemMap.end() ? item->second : MenuItemType::UNKNOWN;
}

void UpdateInfoById(NG::MenuOptionsParam& menuOptionsParam, std::string_view id)
{
    auto opType = StringToMenuItemType(id);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_VOID(theme);
    switch (opType) {
        case MenuItemType::COPY:
            menuOptionsParam.labelInfo = theme->GetCopyLabelInfo();
            menuOptionsParam.symbolId = theme->GetCopySymbolId();
            break;
        case MenuItemType::PASTE:
            menuOptionsParam.labelInfo = theme->GetPasteLabelInfo();
            menuOptionsParam.symbolId = theme->GetPasteSymbolId();
            break;
        case MenuItemType::CUT:
            menuOptionsParam.labelInfo = theme->GetCutLabelInfo();
            menuOptionsParam.symbolId = theme->GetCutSymbolId();
            break;
        case MenuItemType::SELECT_ALL:
            menuOptionsParam.labelInfo = theme->GetSelectAllLabelInfo();
            menuOptionsParam.symbolId = theme->GetCopyAllSymbolId();
            break;
        case MenuItemType::CAMERA_INPUT:
            menuOptionsParam.symbolId = theme->GetCameraInputSymbolId();
            break;
        case MenuItemType::AI_WRITER:
            menuOptionsParam.symbolId = theme->GetAIWriteSymbolId();
            break;
        case MenuItemType::TRANSLATE:
            menuOptionsParam.symbolId = theme->GetTranslateSymbolId();
            break;
        case MenuItemType::SHARE:
            menuOptionsParam.symbolId = theme->GetShareSymbolId();
            break;
        case MenuItemType::SEARCH:
            menuOptionsParam.symbolId = theme->GetSearchSymbolId();
            break;
        default:
            menuOptionsParam.labelInfo = menuOptionsParam.labelInfo.value_or("");
            menuOptionsParam.symbolId = 0;
            break;
    }
}

void UpdateOptionsInfo(std::vector<NG::MenuItemParam>& params)
{
    for (auto& param : params) {
        UpdateInfoById(param.menuOptionsParam, param.menuOptionsParam.id);
    }
}

RefPtr<NG::ChainedTransitionEffect> JSViewAbstract::ParseChainedTransition(
    const JSRef<JSObject>& object, const JSExecutionContext& context, const RefPtr<NG::FrameNode> node)
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
            JSViewContext::CreateAnimation(propAnimationOption, pipelineContext->IsFormRenderExceptDynamicComponent()));
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
        auto animationOptionObj = JSRef<JSObject>::Cast(propAnimationOption);
        JSRef<JSVal> onFinish = animationOptionObj->GetProperty("onFinish");
        WeakPtr<NG::FrameNode> targetNode = nullptr;
        if (node) {
            targetNode = AceType::WeakClaim(AceType::RawPtr(node));
        } else {
            targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        }
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

void JSViewAbstract::JsScale(const JSCallbackInfo& info)
{
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::NUMBER, JSCallbackInfoType::OBJECT };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("JsScale", jsVal, checkList)) {
        SetDefaultScale();
        return;
    }

    if (jsVal->IsObject()) {
        JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsVal);
        if (jsObj->HasProperty(static_cast<int32_t>(ArkUIIndex::X)) ||
            jsObj->HasProperty(static_cast<int32_t>(ArkUIIndex::Y)) ||
            jsObj->HasProperty(static_cast<int32_t>(ArkUIIndex::Z))) {
            // default: x, y, z (1.0, 1.0, 1.0)
            auto scaleX = 1.0f;
            auto scaleY = 1.0f;
            auto scaleZ = 1.0f;
            // default centerX, centerY 50% 50%;
            CalcDimension centerX = 0.5_pct;
            CalcDimension centerY = 0.5_pct;
            ParseJsScale(jsVal, scaleX, scaleY, scaleZ, centerX, centerY);
            ViewAbstractModel::GetInstance()->SetScale(scaleX, scaleY, scaleZ);
            ViewAbstractModel::GetInstance()->SetPivot(centerX, centerY, 0.0_vp);
            return;
        } else {
            SetDefaultScale();
        }
    }
    double scale = 0.0;
    if (ParseJsDouble(jsVal, scale)) {
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
    ViewAbstractModel::GetInstance()->RemoveResObj("viewAbstract.opacity");
    double opacity = 0.0;
    RefPtr<ResourceObject> opacityResObj;
    if (!ParseJsDouble(info[0], opacity, opacityResObj)) {
        ViewAbstractModel::GetInstance()->SetOpacity(1.0f);
        return;
    }
    if (SystemProperties::ConfigChangePerform() && opacityResObj) {
        ViewAbstractModel::GetInstance()->CreateWithOpacityResourceObj(opacityResObj);
        return;
    }
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        opacity = std::clamp(opacity, 0.0, 1.0);
    } else {
        if (opacity > 1.0 || LessNotEqual(opacity, 0.0)) {
            opacity = 1.0;
        }
    }
    ViewAbstractModel::GetInstance()->SetOpacity(opacity);
}

void JSViewAbstract::JsTranslate(const JSCallbackInfo& info)
{
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::STRING, JSCallbackInfoType::NUMBER,
        JSCallbackInfoType::OBJECT };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("JsTranslate", jsVal, checkList)) {
        SetDefaultTranslate();
        return;
    }

    if (jsVal->IsObject()) {
        JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsVal);
        if (jsObj->HasProperty(static_cast<int32_t>(ArkUIIndex::X)) ||
            jsObj->HasProperty(static_cast<int32_t>(ArkUIIndex::Y)) ||
            jsObj->HasProperty(static_cast<int32_t>(ArkUIIndex::Z))) {
            // default: x, y, z (0.0, 0.0, 0.0)
            auto translateX = CalcDimension(0.0);
            auto translateY = CalcDimension(0.0);
            auto translateZ = CalcDimension(0.0);
            ParseJsTranslate(jsVal, translateX, translateY, translateZ);
            ViewAbstractModel::GetInstance()->SetTranslate(translateX, translateY, translateZ);
            return;
        } else {
            SetDefaultTranslate();
        }
    }
    CalcDimension value;
    if (ParseJsDimensionVp(jsVal, value)) {
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
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::NUMBER, JSCallbackInfoType::OBJECT };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("JsRotate", jsVal, checkList)) {
        SetDefaultRotate();
        return;
    }

    if (jsVal->IsObject()) {
        NG::RotateOptions rotate(0.0f, 0.0f, 0.0f, 0.0f, 0.5_pct, 0.5_pct);
        NG::RotateAngleOptions rotateAngle(0.0f, 0.0f, 0.0f, 0.5_pct, 0.5_pct);
        std::optional<float> angle;
        JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsVal);
        bool hasAngleProp = jsObj->HasProperty(static_cast<int32_t>(ArkUIIndex::ANGLE));
        if (hasAngleProp) {
            ParseJsRotate(jsVal, rotate, angle);
            if (angle) {
                ViewAbstractModel::GetInstance()->SetRotate(
                    rotate.xDirection, rotate.yDirection, rotate.zDirection, angle.value(), rotate.perspective);
                ViewAbstractModel::GetInstance()->SetPivot(rotate.centerX, rotate.centerY, rotate.centerZ);
            } else {
                SetDefaultRotate();
            }
        } else {
            ParseJsRotateAngle(jsVal, rotateAngle);
            ViewAbstractModel::GetInstance()->SetRotateAngle(
                rotateAngle.angleX, rotateAngle.angleY, rotateAngle.angleZ, rotateAngle.perspective);
            ViewAbstractModel::GetInstance()->SetPivot(rotateAngle.centerX, rotateAngle.centerY, rotateAngle.centerZ);
        }
        return;
    }
    double rotateZ;
    if (ParseJsDouble(jsVal, rotateZ)) {
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
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::OBJECT };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("JsTransform", jsVal, checkList)) {
        SetDefaultTransform();
        return;
    }
    JSRef<JSVal> array = JSRef<JSObject>::Cast(jsVal)->GetProperty(static_cast<int32_t>(ArkUIIndex::MATRIX4X4));
    const auto matrix4Len = Matrix4::DIMENSION * Matrix4::DIMENSION;
    if (!array->IsArray()) {
        return;
    }
    JSRef<JSArray> jsArray = JSRef<JSArray>::Cast(array);
    if (jsArray->Length() != matrix4Len) {
        return;
    }
    std::vector<float> matrix(matrix4Len);
    for (int32_t i = 0; i < matrix4Len; i++) {
        double value = 0.0;
        ParseJsDouble(jsArray->GetValueAt(i), value);
        matrix[i] = static_cast<float>(value);
    }
    ViewAbstractModel::GetInstance()->SetTransformMatrix(matrix);
}

void JSViewAbstract::JsTransform3D(const JSCallbackInfo& info)
{
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::OBJECT };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("JsTransform3D", jsVal, checkList)) {
        SetDefaultTransform3D();
        return;
    }
    JSRef<JSVal> array = JSRef<JSObject>::Cast(jsVal)->GetProperty(static_cast<int32_t>(ArkUIIndex::MATRIX4X4));
    const auto matrix4Len = Matrix4::DIMENSION * Matrix4::DIMENSION;
    if (!array->IsArray()) {
        TAG_LOGW(AceLogTag::ACE_VISUAL_EFFECT, "[JSI] Type check failed in %{public}s: expected array", __FUNCTION__);
        SetDefaultTransform3D();
        return;
    }
    JSRef<JSArray> jsArray = JSRef<JSArray>::Cast(array);
    if (jsArray->Length() != matrix4Len) {
        TAG_LOGW(AceLogTag::ACE_VISUAL_EFFECT,
            "Invalid matrix parameter: Expected %{public}d elements, but JS array has %{public}zu elements", matrix4Len,
            jsArray->Length());
        SetDefaultTransform3D();
        return;
    }
    std::vector<float> matrix(matrix4Len);
    for (int32_t i = 0; i < matrix4Len; i++) {
        double value = 0.0;
        if (!ParseJsDouble(jsArray->GetValueAt(i), value)) {
            TAG_LOGW(AceLogTag::ACE_VISUAL_EFFECT,"[JSView] Failed to parse double");
            value = 0.0;
        }
        matrix[i] = static_cast<float>(value);
    }
    ViewAbstractModel::GetInstance()->SetTransform3DMatrix(matrix);
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

void JSViewAbstract::SetDefaultTransform3D()
{
    const auto matrix4Len = Matrix4::DIMENSION * Matrix4::DIMENSION;
    std::vector<float> matrix(matrix4Len);
    const int32_t initPosition = 5;
    for (int32_t i = 0; i < matrix4Len; i = i + initPosition) {
        double value = 1.0;
        matrix[i] = static_cast<float>(value);
    }
    ViewAbstractModel::GetInstance()->SetTransform3DMatrix(matrix);
}

NG::TransitionOptions JSViewAbstract::ParseJsTransition(const JSRef<JSObject>& jsObj)
{
    NG::TransitionOptions transitionOption;
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

RefPtr<NG::ChainedTransitionEffect> JSViewAbstract::ParseJsTransitionEffect(const JSCallbackInfo& info)
{
    JSRef<JSVal> arg = info[0];
    if (!arg->IsObject()) {
        return nullptr;
    }
    auto obj = JSRef<JSObject>::Cast(arg);
    auto transitionVal = obj->GetProperty("transition");
    if (!transitionVal->IsObject()) {
        return nullptr;
    }
    auto transitionObj = JSRef<JSObject>::Cast(transitionVal);
    auto chainedEffect = ParseChainedTransition(transitionObj, info.GetExecutionContext());
    return chainedEffect;
}

RefPtr<NG::ChainedTransitionEffect> JSViewAbstract::ParseNapiChainedTransition(const JSRef<JSObject>& object,
    const JSExecutionContext& context)
{
    auto chainedEffect = ParseChainedTransition(object, context);
    return chainedEffect;
}

void JSViewAbstract::JsTransition(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            ViewAbstractModel::GetInstance()->CleanTransition();
            ViewAbstractModel::GetInstance()->SetChainedTransition(nullptr, nullptr);
        }
        return;
    }
    auto obj = JSRef<JSObject>::Cast(info[0]);
    if (!obj->GetProperty("successor_")->IsUndefined()) {
        auto chainedEffect = ParseChainedTransition(obj, info.GetExecutionContext());
        std::function<void(bool)> finishCallback;
        if (info.Length() > 1 && info[1]->IsFunction()) {
            finishCallback = ParseTransitionCallback(JSRef<JSFunc>::Cast(info[1]), info.GetExecutionContext());
        }
        ViewAbstractModel::GetInstance()->SetChainedTransition(chainedEffect, std::move(finishCallback));
        return;
    }
    auto options = ParseJsTransition(obj);
    ViewAbstractModel::GetInstance()->SetTransition(options);
}

void JSViewAbstract::JsWidth(const JSCallbackInfo& info)
{
    JsWidth(info[0]);
}

bool JSViewAbstract::JsWidth(const JSRef<JSVal>& jsValue)
{
    ViewAbstractModel::GetInstance()->ResetResObj("width");
    CalcDimension value;
    RefPtr<ResourceObject> valueResObj;
    if (jsValue->IsUndefined()) {
        ViewAbstractModel::GetInstance()->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, true);
        ViewAbstractModel::GetInstance()->ClearWidthOrHeight(true);
        return true;
    }
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        if (!ParseJsDimensionVpNG(jsValue, value, valueResObj)) {
            // JsWidth return false, check if set LayoutPolicy before return.
            ViewAbstractModel::GetInstance()->ClearWidthOrHeight(true);
            if (jsValue->IsObject()) {
                JSRef<JSObject> object = JSRef<JSObject>::Cast(jsValue);
                JSRef<JSVal> layoutPolicy = object->GetProperty("id_");
                if (layoutPolicy->IsString()) {
                    auto policy = ParseLayoutPolicy(layoutPolicy->ToString());
                    ViewAbstractModel::GetInstance()->UpdateLayoutPolicyProperty(policy, true);
                    return true;
                }
            }
            ViewAbstractModel::GetInstance()->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, true);
            return false;
        }
    } else if (!ParseJsDimensionVp(jsValue, value, valueResObj)) {
        return false;
    }

    ViewAbstractModel::GetInstance()->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, true);
    if (!SystemProperties::ConfigChangePerform() ? LessNotEqual(value.Value(), 0.0) :
        (LessNotEqual(value.Value(), 0.0) && !valueResObj)) {
        if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            ViewAbstractModel::GetInstance()->ClearWidthOrHeight(true);
            return true;
        } else {
            value.SetValue(0.0);
        }
    }

    if (SystemProperties::ConfigChangePerform() && valueResObj) {
        ViewAbstractModel::GetInstance()->SetWidth(valueResObj);
    } else {
        ViewAbstractModel::GetInstance()->SetWidth(value);
    }
    return true;
}

void JSViewAbstract::JsHeight(const JSCallbackInfo& info)
{
    JsHeight(info[0]);
}

void JSViewAbstract::JsToolbar(const JSCallbackInfo& info)
{
    // Check the parameters
    if (info.Length() <= 0) {
        return;
    }
    if (info[0]->IsNull() || info[0]->IsUndefined()) {
        ViewAbstractModel::GetInstance()->SetToolbarBuilder(nullptr);
    } else if (info[0]->IsObject()) {
        JSRef<JSObject> toolbarObj = JSRef<JSObject>::Cast(info[0]);
        auto builder = toolbarObj->GetProperty("builder");
        if (!builder->IsFunction()) {
            return;
        }
        auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(builder));
        CHECK_NULL_VOID(builderFunc);
        auto buildFunc = [execCtx = info.GetExecutionContext(), func = std::move(builderFunc)]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("CrateToolbarItems");
            ToolBarItemModel::GetInstance()->SetIsFirstCreate(true);
            func->Execute();
        };
        ViewAbstractModel::GetInstance()->SetToolbarBuilder(std::move(buildFunc));
    }
}

bool JSViewAbstract::JsHeight(const JSRef<JSVal>& jsValue)
{
    ViewAbstractModel::GetInstance()->ResetResObj("height");
    CalcDimension value;
    RefPtr<ResourceObject> valueResObj;
    if (jsValue->IsUndefined()) {
        ViewAbstractModel::GetInstance()->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, false);
        ViewAbstractModel::GetInstance()->ClearWidthOrHeight(false);
        return true;
    }
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        if (!ParseJsDimensionVpNG(jsValue, value, valueResObj)) {
            // JsHeight return false, check if set LayoutPolicy before return.
            ViewAbstractModel::GetInstance()->ClearWidthOrHeight(false);
            if (jsValue->IsObject()) {
                JSRef<JSObject> object = JSRef<JSObject>::Cast(jsValue);
                JSRef<JSVal> layoutPolicy = object->GetProperty("id_");
                if (layoutPolicy->IsString()) {
                    auto policy = ParseLayoutPolicy(layoutPolicy->ToString());
                    ViewAbstractModel::GetInstance()->UpdateLayoutPolicyProperty(policy, false);
                    return true;
                }
            }
            ViewAbstractModel::GetInstance()->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, false);
            return false;
        }
    } else if (!ParseJsDimensionVp(jsValue, value, valueResObj)) {
        return false;
    }

    ViewAbstractModel::GetInstance()->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, false);
    if (!SystemProperties::ConfigChangePerform() ? LessNotEqual(value.Value(), 0.0) :
        (LessNotEqual(value.Value(), 0.0) && !valueResObj)) {
        if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            ViewAbstractModel::GetInstance()->ClearWidthOrHeight(false);
            return true;
        } else {
            value.SetValue(0.0);
        }
    }

    if (SystemProperties::ConfigChangePerform() && valueResObj) {
        ViewAbstractModel::GetInstance()->SetHeight(valueResObj);
    } else {
        ViewAbstractModel::GetInstance()->SetHeight(value);
    }
    return true;
}

void JSViewAbstract::JsResponseRegion(const JSCallbackInfo& info)
{
    std::vector<DimensionRect> result;
    if (!JSViewAbstract::ParseJsResponseRegionArray(info[0], result)) {
        ViewAbstractModel::GetInstance()->SetResponseRegion({});
        return;
    }

    ViewAbstractModel::GetInstance()->SetResponseRegion(result);
}

void JSViewAbstract::JsMouseResponseRegion(const JSCallbackInfo& info)
{
    std::vector<DimensionRect> result;
    if (!JSViewAbstract::ParseJsResponseRegionArray(info[0], result)) {
        ViewAbstractModel::GetInstance()->SetMouseResponseRegion({});
        return;
    }
    ViewAbstractModel::GetInstance()->SetMouseResponseRegion(result);
}

void JSViewAbstract::ParseMaskRectOffset(
    const JSRef<JSVal>& offsetX, const JSRef<JSVal>& offsetY, DimensionOffset& options)
{
    CalcDimension xDimen;
    CalcDimension yDimen;
    if (!SystemProperties::ConfigChangePerform()) {
        if (ParseJsDimensionNG(offsetX, xDimen, DimensionUnit::VP)) {
            options.SetX(xDimen);
        }
        if (ParseJsDimensionNG(offsetY, yDimen, DimensionUnit::VP)) {
            options.SetY(yDimen);
        }
        return;
    }
    RefPtr<ResourceObject> xResObj = nullptr;
    RefPtr<ResourceObject> yResObj = nullptr;
    if (ParseJsDimensionVp(offsetX, xDimen, xResObj)) {
        options.SetX(xDimen);
    }
    if (xResObj) {
        auto&& xUpdateFunc = [](const RefPtr<ResourceObject>& xResObj, DimensionOffset& options) {
            CalcDimension x;
            if (ResourceParseUtils::ParseResDimensionVp(xResObj, x)) {
                options.SetX(x);
            }
        };
        options.AddResource("dialog.dimensionOffset.x", xResObj, std::move(xUpdateFunc));
    }
    if (ParseJsDimensionVp(offsetY, yDimen, yResObj)) {
        options.SetY(yDimen);
    }
    if (yResObj) {
        auto&& yUpdateFunc = [](const RefPtr<ResourceObject>& yResObj, DimensionOffset& options) {
            CalcDimension y;
            if (ResourceParseUtils::ParseResDimensionVp(yResObj, y)) {
                options.SetY(y);
            }
        };
        options.AddResource("dialog.dimensionOffset.y", yResObj, std::move(yUpdateFunc));
    }
}

void JSViewAbstract::ParseMarkRectWidthWithResourceObj(const JSRef<JSVal>& width, DimensionRect& options)
{
    CalcDimension rectDimen;
    RefPtr<ResourceObject> resObj = nullptr;
    if (ParseJsDimensionNG(width, rectDimen, DimensionUnit::VP, resObj)) {
        if (rectDimen.Unit() == DimensionUnit::PERCENT && rectDimen.Value() < 0) {
            return;
        }
        options.SetWidth(rectDimen);
    }
    if (resObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, DimensionRect& options) {
            CalcDimension rectDimenVal;
            if (ResourceParseUtils::ParseResDimensionVpNG(resObj, rectDimenVal)) {
                if (rectDimenVal.Unit() == DimensionUnit::PERCENT && rectDimenVal.Value() < 0) {
                    return;
                }
                options.SetWidth(rectDimenVal);
            }
        };
        options.AddResource("dialog.maskRect.width", resObj, std::move(updateFunc));
    }
}

void JSViewAbstract::ParseMarkRectWidth(const JSRef<JSVal>& width, DimensionRect& options)
{
    CalcDimension rectDimen;
    if (!SystemProperties::ConfigChangePerform()) {
        if (ParseJsDimensionNG(width, rectDimen, DimensionUnit::VP)) {
            if (rectDimen.Unit() == DimensionUnit::PERCENT && rectDimen.Value() < 0) {
                return;
            }
            options.SetWidth(rectDimen);
        }
        return;
    }
    ParseMarkRectWidthWithResourceObj(width, options);
}

void JSViewAbstract::ParseMaskRectHeightWithResourceObj(const JSRef<JSVal>& height, DimensionRect& options)
{
    RefPtr<ResourceObject> resObj = nullptr;
    CalcDimension rectDimen;
    if (ParseJsDimensionNG(height, rectDimen, DimensionUnit::VP, resObj)) {
        if (rectDimen.Unit() == DimensionUnit::PERCENT && rectDimen.Value() < 0) {
            return;
        }
        options.SetHeight(rectDimen);
    }
    if (resObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, DimensionRect& options) {
            CalcDimension rectDimenVal;
            if (ResourceParseUtils::ParseResDimensionVpNG(resObj, rectDimenVal)) {
                if (rectDimenVal.Unit() == DimensionUnit::PERCENT && rectDimenVal.Value() < 0) {
                    return;
                }
                options.SetHeight(rectDimenVal);
            }
        };
        options.AddResource("dialog.maskRect.height", resObj, std::move(updateFunc));
    }
}

void JSViewAbstract::ParseMarkRectHeight(const JSRef<JSVal>& height, DimensionRect& options)
{
    CalcDimension rectDimen;
    if (!SystemProperties::ConfigChangePerform()) {
        if (ParseJsDimensionNG(height, rectDimen, DimensionUnit::VP)) {
            if (rectDimen.Unit() == DimensionUnit::PERCENT && rectDimen.Value() < 0) {
                return;
            }
            options.SetHeight(rectDimen);
        }
        return;
    }
    ParseMaskRectHeightWithResourceObj(height, options);
}

bool JSViewAbstract::ParseJsDimensionRect(const JSRef<JSVal>& jsValue, DimensionRect& result)
{
    result.SetOffset(DimensionOffset(CalcDimension(0, DimensionUnit::VP), CalcDimension(0, DimensionUnit::VP)));
    result.SetSize(DimensionSize(CalcDimension(1, DimensionUnit::PERCENT), CalcDimension(1, DimensionUnit::PERCENT)));
    if (!jsValue->IsObject()) {
        return true;
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
    DimensionOffset offset;
    ParseMaskRectOffset(x, y, offset);
    result.SetOffset(offset);
    ParseMarkRectWidth(width, result);
    ParseMarkRectHeight(height, result);
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
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::OBJECT };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("JsSize", jsVal, checkList)) {
        return;
    }

    JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(jsVal);
    JsWidth(sizeObj->GetProperty(static_cast<int32_t>(ArkUIIndex::WIDTH)));
    JsHeight(sizeObj->GetProperty(static_cast<int32_t>(ArkUIIndex::HEIGHT)));
}

void JSViewAbstract::JsConstraintSize(const JSCallbackInfo& info)
{
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::OBJECT };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("JsConstraintSize", jsVal, checkList)) {
        ViewAbstractModel::GetInstance()->ResetMaxSize(true);
        ViewAbstractModel::GetInstance()->ResetMinSize(true);
        ViewAbstractModel::GetInstance()->ResetMaxSize(false);
        ViewAbstractModel::GetInstance()->ResetMinSize(false);
        return;
    }

    JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(jsVal);

    JSRef<JSVal> minWidthValue = sizeObj->GetProperty("minWidth");
    CalcDimension minWidth;
    RefPtr<ResourceObject> minWidthResObj;
    JSRef<JSVal> maxWidthValue = sizeObj->GetProperty("maxWidth");
    CalcDimension maxWidth;
    RefPtr<ResourceObject> maxWidthResObj;
    JSRef<JSVal> minHeightValue = sizeObj->GetProperty("minHeight");
    CalcDimension minHeight;
    RefPtr<ResourceObject> minHeightResObj;
    JSRef<JSVal> maxHeightValue = sizeObj->GetProperty("maxHeight");
    CalcDimension maxHeight;
    RefPtr<ResourceObject> maxHeightResObj;
    bool version10OrLarger = Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN);
    if (ParseJsDimensionVp(minWidthValue, minWidth, minWidthResObj)) {
        ViewAbstractModel::GetInstance()->SetMinWidth(minWidth);
    } else if (version10OrLarger) {
        ViewAbstractModel::GetInstance()->ResetMinSize(true);
    }

    if (ParseJsDimensionVp(maxWidthValue, maxWidth, maxWidthResObj)) {
        ViewAbstractModel::GetInstance()->SetMaxWidth(maxWidth);
    } else if (version10OrLarger) {
        ViewAbstractModel::GetInstance()->ResetMaxSize(true);
    }

    if (ParseJsDimensionVp(minHeightValue, minHeight, minHeightResObj)) {
        ViewAbstractModel::GetInstance()->SetMinHeight(minHeight);
    } else if (version10OrLarger) {
        ViewAbstractModel::GetInstance()->ResetMinSize(false);
    }

    if (ParseJsDimensionVp(maxHeightValue, maxHeight, maxHeightResObj)) {
        ViewAbstractModel::GetInstance()->SetMaxHeight(maxHeight);
    } else if (version10OrLarger) {
        ViewAbstractModel::GetInstance()->ResetMaxSize(false);
    }
    SetConstraintSize(minWidthResObj, maxWidthResObj, minHeightResObj, maxHeightResObj);
}

void JSViewAbstract::JsLayoutPriority(const JSCallbackInfo& info)
{
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::STRING, JSCallbackInfoType::NUMBER };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("JsLayoutPriority", jsVal, checkList)) {
        return;
    }

    int32_t priority;
    if (jsVal->IsNumber()) {
        priority = jsVal->ToNumber<int32_t>();
    } else {
        priority = static_cast<int32_t>(StringUtils::StringToUint(jsVal->ToString()));
    }
    ViewAbstractModel::GetInstance()->SetLayoutPriority(priority);
}

void JSViewAbstract::JsLayoutWeight(const JSCallbackInfo& info)
{
    float value = 0.0f;
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::STRING, JSCallbackInfoType::NUMBER };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("JsLayoutWeight", jsVal, checkList)) {
        if (!jsVal->IsUndefined()) {
            return;
        }
    }

    if (jsVal->IsNumber()) {
        if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            value = jsVal->ToNumber<float>();
        } else {
            value = jsVal->ToNumber<int32_t>();
        }
    } else {
        if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            value = static_cast<float>(StringUtils::StringToUintCheck(jsVal->ToString()));
        } else {
            value = static_cast<int32_t>(StringUtils::StringToUintCheck(jsVal->ToString()));
        }
    }

    ViewAbstractModel::GetInstance()->SetLayoutWeight(value);
}

void JSViewAbstract::JsAlign(const JSCallbackInfo& info)
{
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::NUMBER, JSCallbackInfoType::STRING };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("JsAlign", jsVal, checkList) &&
        Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        ViewAbstractModel::GetInstance()->SetAlign(Alignment::CENTER);
        return;
    }
    if (jsVal->IsNumber()) {
        auto value = jsVal->ToNumber<int32_t>();
        Alignment alignment = ParseAlignment(value);
        ViewAbstractModel::GetInstance()->SetAlign(alignment);
        ViewAbstractModel::GetInstance()->SetIsMirrorable(false);
    } else {
        std::string localizedAlignment = jsVal->ToString();
        ViewAbstractModel::GetInstance()->SetAlign(localizedAlignment);
        ViewAbstractModel::GetInstance()->SetIsMirrorable(true);
    }
}

void JSViewAbstract::JsLayoutGravity(const JSCallbackInfo& info)
{
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::STRING };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("JsLayoutGravity", jsVal, checkList)) {
        ViewAbstractModel::GetInstance()->SetLayoutGravity(Alignment::CENTER);
        return;
    }

    if (jsVal->IsString()) {
        std::string value = jsVal->ToString();
        Alignment layoutGravityAlignment = NG::BoxLayoutAlgorithm::MapLocalizedToAlignment(value);
        ViewAbstractModel::GetInstance()->SetLayoutGravity(layoutGravityAlignment);
    }
}

void JSViewAbstract::JsPosition(const JSCallbackInfo& info)
{
    ViewAbstractModel::GetInstance()->ResetResObj("position.x");
    ViewAbstractModel::GetInstance()->ResetResObj("position.y");
    ViewAbstractModel::GetInstance()->ResetResObj("position.edges");
    CalcDimension x;
    CalcDimension y;
    RefPtr<ResourceObject> xResObj;
    RefPtr<ResourceObject> yResObj;
    OHOS::Ace::EdgesParam edges;

    auto jsArg = info[0];
    if (jsArg->IsObject()) {
        JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsArg);
        if (ParseLocationProps(jsObj, x, y, xResObj, yResObj)) {
            if (SystemProperties::ConfigChangePerform()) {
                return ViewAbstractModel::GetInstance()->SetPosition(x, y, xResObj, yResObj);
            } else {
                return ViewAbstractModel::GetInstance()->SetPosition(x, y);
            }
        } else if (ParseLocalizedEdges(jsObj, edges)) {
            ViewAbstractModel::GetInstance()->SetPositionLocalizedEdges(true);
            return ViewAbstractModel::GetInstance()->SetPositionEdges(edges);
        } else if (ParseLocationPropsEdges(jsObj, edges)) {
            return ViewAbstractModel::GetInstance()->SetPositionEdges(edges);
        }
    }
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        ViewAbstractModel::GetInstance()->ResetPosition();
    } else {
        ViewAbstractModel::GetInstance()->SetPosition(0.0_vp, 0.0_vp);
    }
}

void JSViewAbstract::JsMarkAnchor(const JSCallbackInfo& info)
{
    ViewAbstractModel::GetInstance()->ResetResObj("markAnchor.x");
    ViewAbstractModel::GetInstance()->ResetResObj("markAnchor.y");
    CalcDimension x;
    CalcDimension y;
    RefPtr<ResourceObject> xResObj;
    RefPtr<ResourceObject> yResObj;

    auto jsArg = info[0];
    if (jsArg->IsObject()) {
        JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsArg);
        if (ParseMarkAnchorPosition(jsObj, x, y)) {
            ViewAbstractModel::GetInstance()->SetMarkAnchorStart(x);
            return ViewAbstractModel::GetInstance()->MarkAnchor(x, y);
        }
        if (ParseLocationProps(jsObj, x, y, xResObj, yResObj)) {
            ViewAbstractModel::GetInstance()->ResetMarkAnchorStart();
            if (SystemProperties::ConfigChangePerform()) {
                return ViewAbstractModel::GetInstance()->MarkAnchor(x, y, xResObj, yResObj);
            } else {
                return ViewAbstractModel::GetInstance()->MarkAnchor(x, y);
            }
        }
    }
    ViewAbstractModel::GetInstance()->ResetMarkAnchorStart();
    ViewAbstractModel::GetInstance()->MarkAnchor(0.0_vp, 0.0_vp);
}

void JSViewAbstract::JsOffset(const JSCallbackInfo& info)
{
    ViewAbstractModel::GetInstance()->ResetResObj("offset.x");
    ViewAbstractModel::GetInstance()->ResetResObj("offset.y");
    ViewAbstractModel::GetInstance()->ResetResObj("offset.edges");
    CalcDimension x;
    CalcDimension y;
    RefPtr<ResourceObject> xResObj;
    RefPtr<ResourceObject> yResObj;
    OHOS::Ace::EdgesParam edges;
    auto jsArg = info[0];
    if (jsArg->IsObject()) {
        JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsArg);
        if (ParseLocalizedEdges(jsObj, edges)) {
            ViewAbstractModel::GetInstance()->SetOffsetLocalizedEdges(true);
            return ViewAbstractModel::GetInstance()->SetOffsetEdges(edges);
        } else if (ParseLocationProps(jsObj, x, y, xResObj, yResObj)) {
            if (SystemProperties::ConfigChangePerform()) {
                return ViewAbstractModel::GetInstance()->SetOffset(x, y, xResObj, yResObj);
            } else {
                return ViewAbstractModel::GetInstance()->SetOffset(x, y);
            }
        } else if (ParseLocationPropsEdges(jsObj, edges)) {
            return ViewAbstractModel::GetInstance()->SetOffsetEdges(edges);
        }
    }

    ViewAbstractModel::GetInstance()->SetOffset(0.0_vp, 0.0_vp);
}

void JSViewAbstract::JsEnabled(const JSCallbackInfo& info)
{
    auto arg = info[0];
    if (!arg->IsBoolean()) {
        ViewAbstractModel::GetInstance()->SetEnabled(true);
    } else {
        ViewAbstractModel::GetInstance()->SetEnabled(arg->ToBoolean());
    }
}

void JSViewAbstract::JsAspectRatio(const JSCallbackInfo& info)
{
    double value = 0.0;
    auto jsAspectRatio = info[0];
    if (!ParseJsDouble(jsAspectRatio, value)) {
        // add version protection, undefined use default value
        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN) &&
            (jsAspectRatio->IsNull() || jsAspectRatio->IsUndefined())) {
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

void ParseOverlayFirstParam(const JSCallbackInfo& info, std::optional<Alignment>& align,
    std::optional<CalcDimension>& offsetX, std::optional<CalcDimension>& offsetY)
{
    if (info[0]->IsString()) {
        std::string text = info[0]->ToString();
        ViewAbstractModel::GetInstance()->SetOverlay(
            text, nullptr, nullptr, align, offsetX, offsetY, NG::OverlayType::TEXT);
    } else if (info[0]->IsObject()) {
        JSRef<JSObject> overlayObject = JSRef<JSObject>::Cast(info[0]);
        auto builder = overlayObject->GetProperty("builder");
        if (builder->IsFunction()) {
            auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(builder));
            CHECK_NULL_VOID(builderFunc);
            auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
            auto buildFunc = [execCtx = info.GetExecutionContext(), func = std::move(builderFunc),
                                 node = targetNode]() {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                ACE_SCORING_EVENT("Overlay");
                PipelineContext::SetCallBackNode(node);
                func->Execute();
            };
            ViewAbstractModel::GetInstance()->SetOverlay(
                "", std::move(buildFunc), nullptr, align, offsetX, offsetY, NG::OverlayType::BUILDER);
            return;
        }

        JSRef<JSVal> builderNode = overlayObject->GetProperty("builderNode_");
        if (!builderNode->IsObject()) {
            return;
        }
        auto builderNodeObj = JSRef<JSObject>::Cast(builderNode);
        JSRef<JSVal> nodePtr = builderNodeObj->GetProperty("nodePtr_");
        if (nodePtr.IsEmpty()) {
            return;
        }
        const auto* vm = nodePtr->GetEcmaVM();
        auto localHandle = nodePtr->GetLocalHandle();
        if (!localHandle->IsNativePointer(vm)) {
            return;
        }
        auto* node = localHandle->ToNativePointer(vm)->Value();
        auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
        CHECK_NULL_VOID(frameNode);
        RefPtr<NG::FrameNode> contentNode = AceType::Claim(frameNode);
        ViewAbstractModel::GetInstance()->SetOverlay(
            "", nullptr, contentNode, align, offsetX, offsetY, NG::OverlayType::COMPONENT_CONTENT);
    }
}

void JSViewAbstract::JsOverlay(const JSCallbackInfo& info)
{
    if (info.Length() > 0 && (info[0]->IsUndefined())) {
        ViewAbstractModel::GetInstance()->SetOverlay(
            "", nullptr, nullptr, Alignment::TOP_LEFT, CalcDimension(0), CalcDimension(0), NG::OverlayType::RESET);
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

    ParseOverlayFirstParam(info, align, offsetX, offsetY);
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

LayoutCalPolicy JSViewAbstract::ParseLayoutPolicy(const std::string& layoutPolicy)
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

void JSViewAbstract::SetVisibility(const JSCallbackInfo& info)
{
    int32_t visible = 0;
    JSRef<JSVal> arg = info[0];
    if (arg->IsNull() || arg->IsUndefined()) {
        // undefined value use default value.
        visible = 0;
    } else if (!arg->IsNumber()) {
        return;
    } else {
        visible = arg->ToNumber<int32_t>();
    }

    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE) &&
        (visible < static_cast<int32_t>(VisibleType::VISIBLE) || visible > static_cast<int32_t>(VisibleType::GONE))) {
        visible = 0;
    }

    if (info.Length() > 1 && info[1]->IsFunction()) {
        RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[1]));
        auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
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

void JSViewAbstract::JsSetFreeze(const JSCallbackInfo& info)
{
    if (info[0]->IsBoolean()) {
        ViewAbstractModel::GetInstance()->SetFreeze(info[0]->ToBoolean());
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
            return;
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
        if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            ViewAbstractModel::GetInstance()->SetDisplayIndex(0);
        }
        return;
    }
    ViewAbstractModel::GetInstance()->SetDisplayIndex(static_cast<int32_t>(value));
}

void JSViewAbstract::JsSharedTransition(const JSCallbackInfo& info)
{
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::STRING };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("JsSharedTransition", jsVal, checkList)) {
        return;
    }
    // id
    auto id = jsVal->ToString();
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
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::STRING };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("JsGeometryTransition", jsVal, checkList)) {
        return;
    }
    // id
    auto id = jsVal->ToString();
    // follow flag
    bool followWithOutTransition = false;
    // hierarchy flag
    bool doRegisterSharedTransition = true;
    if (info.Length() >= PARAMETER_LENGTH_SECOND && info[1]->IsObject()) {
        JSRef<JSObject> jsOption = JSRef<JSObject>::Cast(info[1]);
        ParseJsBool(jsOption->GetProperty("follow"), followWithOutTransition);

        auto transitionHierarchyStrategy = static_cast<int32_t>(TransitionHierarchyStrategy::ADAPTIVE);
        ParseJsInt32(jsOption->GetProperty("hierarchyStrategy"), transitionHierarchyStrategy);
        switch (transitionHierarchyStrategy) {
            case static_cast<int32_t>(TransitionHierarchyStrategy::NONE):
                doRegisterSharedTransition = false;
                break;
            case static_cast<int32_t>(TransitionHierarchyStrategy::ADAPTIVE):
                doRegisterSharedTransition = true;
                break;
            default:
                break;
        }
    }
    ViewAbstractModel::GetInstance()->SetGeometryTransition(id, followWithOutTransition, doRegisterSharedTransition);
}

void JSViewAbstract::JsAlignSelf(const JSCallbackInfo& info)
{
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::NUMBER };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("JsAlignSelf", jsVal, checkList)) {
        ViewAbstractModel::GetInstance()->SetAlignSelf(FlexAlign::AUTO);
        return;
    }
    auto alignVal = jsVal->ToNumber<int32_t>();

    if (alignVal >= 0 && alignVal <= MAX_ALIGN_VALUE) {
        ViewAbstractModel::GetInstance()->SetAlignSelf(static_cast<FlexAlign>(alignVal));
    }
}

void JSViewAbstract::JsBackgroundColor(const JSCallbackInfo& info)
{
    Color backgroundColor;
    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> backgroundColorResObj;
        if (!ParseJsColor(info[0], backgroundColor, backgroundColorResObj)) {
            backgroundColor = Color::TRANSPARENT;
        }
        ViewAbstractModel::GetInstance()->SetBackgroundColorWithResourceObj(backgroundColor, backgroundColorResObj);
        return;
    } else {
        if (!ParseJsColor(info[0], backgroundColor)) {
            backgroundColor = Color::TRANSPARENT;
        }
    }

    ViewAbstractModel::GetInstance()->SetBackgroundColor(backgroundColor);
}

void JSViewAbstract::JsBackgroundImage(const JSCallbackInfo& info)
{
    int32_t resId = 0;
    std::string src;
    std::string bundle;
    std::string module;
    RefPtr<PixelMap> pixmap = nullptr;
    auto jsBackgroundImage = info[0];
    GetJsMediaBundleInfo(jsBackgroundImage, bundle, module);
    int32_t repeatIndex = 0;
    bool syncMode = false;
    ParseBackgroundImageOption(info, repeatIndex, syncMode);
    ViewAbstractModel::GetInstance()->SetBackgroundImageSyncMode(syncMode);
    RefPtr<ResourceObject> backgroundImageResObj;
    if (jsBackgroundImage->IsString()) {
        src = jsBackgroundImage->ToString();
        ViewAbstractModel::GetInstance()->SetBackgroundImage(
            ImageSourceInfo { src, bundle, module }, GetThemeConstants());
        ViewAbstractModel::GetInstance()->ClearResObj("backgroundImageSrc");
    } else if (ParseJsMediaWithBundleName(jsBackgroundImage, src, bundle, module, resId, backgroundImageResObj)) {
        if (!SystemProperties::ConfigChangePerform()) {
            ViewAbstractModel::GetInstance()->SetBackgroundImage(ImageSourceInfo{src, bundle, module}, nullptr);
        } else {
            ViewAbstractModel::GetInstance()->SetBackgroundImageWithResourceObj(
                backgroundImageResObj, ImageSourceInfo { src, bundle, module }, nullptr);
        }
    } else {
#if defined(PIXEL_MAP_SUPPORTED)
        if (IsDrawable(jsBackgroundImage)) {
            pixmap = GetDrawablePixmap(jsBackgroundImage);
        } else {
            pixmap = CreatePixelMapFromNapiValue(jsBackgroundImage);
        }
#endif
        ViewAbstractModel::GetInstance()->SetBackgroundImage(ImageSourceInfo { pixmap }, nullptr);
        ViewAbstractModel::GetInstance()->ClearResObj("backgroundImageSrc");
    }
    if (info.Length() == 2) { // 2 is background image info length
        auto jsImageRepeat = info[1];
        if (jsImageRepeat->IsNumber()) {
            repeatIndex = jsImageRepeat->ToNumber<int32_t>();
        }
    }
    auto repeat = static_cast<ImageRepeat>(repeatIndex);
    ViewAbstractModel::GetInstance()->SetBackgroundImageRepeat(repeat);
}

void JSViewAbstract::ParseBackgroundImageOption(const JSCallbackInfo& info, int32_t& repeatIndex, bool& syncMode)
{
    if (info.Length() < 2) { // 2 represents the least para num;
        return;
    }
    if (!info[1]->IsObject()) {
        return;
    }
    JSRef<JSObject> jsOption  = JSRef<JSObject>::Cast(info[1]);
    if (jsOption->GetProperty("syncLoad")->IsBoolean()) {
        syncMode = jsOption->GetProperty("syncLoad")->ToBoolean();
    }
    if (jsOption->GetProperty("repeat")->IsNumber()) {
        repeatIndex = jsOption->GetProperty("repeat")->ToNumber<int32_t>();
    }
}

void JSViewAbstract::ParseBlurOption(const JSRef<JSObject>& jsBlurOption, BlurOption& blurOption)
{
    auto blurOptionProperty = jsBlurOption->GetProperty("grayscale");
    if (blurOptionProperty->IsArray()) {
        JSRef<JSArray> params = JSRef<JSArray>::Cast(blurOptionProperty);
        auto grey1 = params->GetValueAt(0)->ToNumber<uint32_t>();
        auto grey2 = params->GetValueAt(1)->ToNumber<uint32_t>();
        std::vector<float> greyVec(2); // 2 number
        greyVec[0] = grey1;
        greyVec[1] = grey2;
        blurOption.grayscale = greyVec;
    }
}

void JSViewAbstract::ParseSysOptions(const JSRef<JSObject>& jsSysOptions, SysOptions& sysOptions)
{
    auto disableAdaptation = jsSysOptions->GetProperty("disableSystemAdaptation");
    if (disableAdaptation->IsBoolean()) {
        sysOptions.disableSystemAdaptation = disableAdaptation->ToBoolean();
    }
}

void JSViewAbstract::ParseInactiveColor(const JSRef<JSObject>& jsOption, BlurStyleOption& styleOption)
{
    RefPtr<ResourceObject> inactiveColorResObj;
    if (ParseJsColor(jsOption->GetProperty("inactiveColor"), styleOption.inactiveColor, inactiveColorResObj)) {
        styleOption.isValidColor = true;
    }
    if (SystemProperties::ConfigChangePerform() && inactiveColorResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, BlurStyleOption& styleOption) {
            Color inactiveColorValue;
            ResourceParseUtils::ParseResColor(resObj, inactiveColorValue);
            styleOption.inactiveColor = inactiveColorValue;
            styleOption.isValidColor = true;
        };
        styleOption.AddResource("backgroundBlurStyle.backgroundBlurStyleOptions.inactiveColor",
            inactiveColorResObj, std::move(updateFunc));
    }
}

void JSViewAbstract::ParseBlurStyleOption(const JSRef<JSObject>& jsOption, BlurStyleOption& styleOption)
{
    if (jsOption->IsUndefined()) {
        return;
    }
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

    // policy
    auto policy = static_cast<int32_t>(BlurStyleActivePolicy::ALWAYS_ACTIVE);
    ParseJsInt32(jsOption->GetProperty("policy"), policy);
    if (policy >= static_cast<int32_t>(BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE) &&
        policy <= static_cast<int32_t>(BlurStyleActivePolicy::ALWAYS_INACTIVE)) {
        styleOption.policy = static_cast<BlurStyleActivePolicy>(policy);
    }

    // blurType
    auto blurType = static_cast<int32_t>(BlurType::WITHIN_WINDOW);
    ParseJsInt32(jsOption->GetProperty("type"), blurType);
    if (blurType >= static_cast<int32_t>(BlurType::WITHIN_WINDOW) &&
        blurType <= static_cast<int32_t>(BlurType::BEHIND_WINDOW)) {
        styleOption.blurType = static_cast<BlurType>(blurType);
    }

    // inactiveColor
    ParseInactiveColor(jsOption, styleOption);

    // scale
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

void JSViewAbstract::JsBackgroundBlurStyle(const JSCallbackInfo& info)
{
    if (info.Length() == 0) {
        return;
    }
    ViewAbstractModel::GetInstance()->RemoveResObj("backgroundBlurStyle.backgroundBlurStyleOptions");
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
        ParseBlurStyleOption(jsOption, styleOption);
    }
    SysOptions sysOptions;
    sysOptions.disableSystemAdaptation = false;
    if (info.Length() > NUM2 && info[NUM2]->IsObject()) {
        JSRef<JSObject> jsSysOptions = JSRef<JSObject>::Cast(info[NUM2]);
        ParseSysOptions(jsSysOptions, sysOptions);
    }
    ViewAbstractModel::GetInstance()->SetBackgroundBlurStyle(styleOption, sysOptions);
}

void JSViewAbstract::ParseBrightnessOption(const JSRef<JSObject>& jsOption, BrightnessOption& brightnessOption)
{
    double rate = 1.0f;
    auto jsRate = jsOption->GetProperty("rate");
    if (jsRate->IsNumber()) {
        rate = jsRate->ToNumber<double>();
    }
    double lightUpDegree = 0.0f;
    auto jslightUpDegree = jsOption->GetProperty("lightUpDegree");
    if (jslightUpDegree->IsNumber()) {
        lightUpDegree = jslightUpDegree->ToNumber<double>();
    }
    double cubicCoeff = 0.0f;
    auto jsCubicCoeff = jsOption->GetProperty("cubicCoeff");
    if (jsCubicCoeff->IsNumber()) {
        cubicCoeff = jsCubicCoeff->ToNumber<double>();
    }
    double quadCoeff = 0.0f;
    auto jsQuadCoeff = jsOption->GetProperty("quadCoeff");
    if (jsQuadCoeff->IsNumber()) {
        quadCoeff = jsQuadCoeff->ToNumber<double>();
    }
    double saturation = 1.0f;
    auto jsSaturation = jsOption->GetProperty("saturation");
    if (jsSaturation->IsNumber()) {
        saturation = jsSaturation->ToNumber<double>();
    }
    std::vector<float> posRGB(3, 0.0);
    auto jsPosRGB = jsOption->GetProperty("posRGB");
    if (jsPosRGB->IsArray()) {
        JSRef<JSArray> params = JSRef<JSArray>::Cast(jsPosRGB);
        auto r = params->GetValueAt(0)->ToNumber<double>();
        auto g = params->GetValueAt(1)->ToNumber<double>();
        auto b = params->GetValueAt(2)->ToNumber<double>();
        posRGB[0] = r;
        posRGB[1] = g;
        posRGB[2] = b;
    }
    std::vector<float> negRGB(3, 0.0);
    auto jsNegRGB = jsOption->GetProperty("negRGB");
    if (jsNegRGB->IsArray()) {
        JSRef<JSArray> params = JSRef<JSArray>::Cast(jsNegRGB);
        auto r = params->GetValueAt(0)->ToNumber<double>();
        auto g = params->GetValueAt(1)->ToNumber<double>();
        auto b = params->GetValueAt(2)->ToNumber<double>();
        negRGB[0] = r;
        negRGB[1] = g;
        negRGB[2] = b;
    }
    double fraction = 1.0f;
    auto jsFraction = jsOption->GetProperty("fraction");
    if (jsFraction->IsNumber()) {
        fraction = jsFraction->ToNumber<double>();
        fraction = std::clamp(fraction, 0.0, 1.0);
    }
    brightnessOption = { rate, lightUpDegree, cubicCoeff, quadCoeff, saturation, posRGB, negRGB, fraction };
}

void JSViewAbstract::GetEffectOptionColor(const JSRef<JSObject>& jsOption, EffectOption& effectOption)
{
    if (!SystemProperties::ConfigChangePerform()) {
        ParseJsColor(jsOption->GetProperty("color"), effectOption.color);
    } else {
        RefPtr<ResourceObject> colorResObj;
        ParseJsColor(jsOption->GetProperty("color"), effectOption.color, colorResObj);
        if (colorResObj) {
            auto&& updateFunc = [](const RefPtr<ResourceObject>& colorResObj, EffectOption& effectOption) {
                Color effectOptionColor;
                ResourceParseUtils::ParseResColor(colorResObj, effectOptionColor);
                effectOption.color = effectOptionColor;
            };
            effectOption.AddResource("backgroundEffect.color", colorResObj, std::move(updateFunc));
        }
    }
}

void JSViewAbstract::GetEffectOptionInactiveColorUpdate(const RefPtr<ResourceObject>& inactiveColorObj,
    EffectOption& effectOption)
{
    if (inactiveColorObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& inactiveColorObj, EffectOption& effectOption) {
            Color effectOptionInactiveColor;
            ResourceParseUtils::ParseResColor(inactiveColorObj, effectOptionInactiveColor);
            effectOption.inactiveColor = effectOptionInactiveColor;
        };
        effectOption.AddResource("backgroundEffect.inactiveColor", inactiveColorObj, std::move(updateFunc));
    }
}

void JSViewAbstract::GetEffectOptionInactiveColor(const JSRef<JSObject>& jsOption, EffectOption& effectOption)
{
    if (!SystemProperties::ConfigChangePerform()) {
        if (ParseJsColor(jsOption->GetProperty("inactiveColor"), effectOption.inactiveColor)) {
            effectOption.isValidColor = true;
        }
    } else {
        RefPtr<ResourceObject> inactiveColorObj;
        if (ParseJsColor(jsOption->GetProperty("inactiveColor"), effectOption.inactiveColor, inactiveColorObj)) {
            GetEffectOptionInactiveColorUpdate(inactiveColorObj, effectOption);
            effectOption.isValidColor = true;
        }
    }
}

void JSViewAbstract::ParseEffectOption(const JSRef<JSObject>& jsOption, EffectOption& effectOption)
{
    CalcDimension radius;
    if (!ParseJsDimensionVp(jsOption->GetProperty("radius"), radius) || LessNotEqual(radius.Value(), 0.0f)) {
        radius.SetValue(0.0f);
    }
    effectOption.radius = radius;

    double saturation = 1.0f;
    if (jsOption->GetProperty("saturation")->IsNumber()) {
        saturation = jsOption->GetProperty("saturation")->ToNumber<double>();
        saturation = (saturation > 0.0f || NearZero(saturation)) ? saturation : 1.0f;
    }
    effectOption.saturation = saturation;

    double brightness = 1.0f;
    if (jsOption->GetProperty("brightness")->IsNumber()) {
        brightness = jsOption->GetProperty("brightness")->ToNumber<double>();
        brightness = (brightness > 0.0f || NearZero(brightness)) ? brightness : 1.0f;
    }
    effectOption.brightness = brightness;

    GetEffectOptionColor(jsOption, effectOption);

    auto adaptiveColorValue = static_cast<int32_t>(AdaptiveColor::DEFAULT);
    auto adaptiveColor = AdaptiveColor::DEFAULT;
    ParseJsInt32(jsOption->GetProperty("adaptiveColor"), adaptiveColorValue);
    if (adaptiveColorValue >= static_cast<int32_t>(AdaptiveColor::DEFAULT) &&
        adaptiveColorValue <= static_cast<int32_t>(AdaptiveColor::AVERAGE)) {
        adaptiveColor = static_cast<AdaptiveColor>(adaptiveColorValue);
    }
    effectOption.adaptiveColor = adaptiveColor;

    // policy
    auto policy = static_cast<int32_t>(BlurStyleActivePolicy::ALWAYS_ACTIVE);
    ParseJsInt32(jsOption->GetProperty("policy"), policy);
    if (policy >= static_cast<int32_t>(BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE) &&
        policy <= static_cast<int32_t>(BlurStyleActivePolicy::ALWAYS_INACTIVE)) {
        effectOption.policy = static_cast<BlurStyleActivePolicy>(policy);
    }

    // blurType
    auto blurType = static_cast<int32_t>(BlurType::WITHIN_WINDOW);
    ParseJsInt32(jsOption->GetProperty("type"), blurType);
    if (blurType >= static_cast<int32_t>(BlurType::WITHIN_WINDOW) &&
        blurType <= static_cast<int32_t>(BlurType::BEHIND_WINDOW)) {
        effectOption.blurType = static_cast<BlurType>(blurType);
    }

    // inactiveColor
    GetEffectOptionInactiveColor(jsOption, effectOption);

    BlurOption blurOption;
    if (jsOption->GetProperty("blurOptions")->IsObject()) {
        JSRef<JSObject> jsBlurOption = JSRef<JSObject>::Cast(jsOption->GetProperty("blurOptions"));
        ParseBlurOption(jsBlurOption, blurOption);
        effectOption.blurOption = blurOption;
    }
}

void JSViewAbstract::JsForegroundEffect(const JSCallbackInfo& info)
{
    if (info.Length() == 0) {
        return;
    }
    float radius = 0.0;
    if (info[0]->IsObject()) {
        JSRef<JSObject> jsOption = JSRef<JSObject>::Cast(info[0]);
        if (jsOption->GetProperty("radius")->IsNumber()) {
            radius = jsOption->GetProperty("radius")->ToNumber<float>();
        }
    }
    radius = std::max(radius, 0.0f);
    ViewAbstractModel::GetInstance()->SetForegroundEffect(radius);
}

void JSViewAbstract::JsBackgroundEffect(const JSCallbackInfo& info)
{
    if (info.Length() == 0) {
        return;
    }
    ViewAbstractModel::GetInstance()->RemoveResObj("backgroundEffect");
    EffectOption option;
    if (info[0]->IsObject()) {
        JSRef<JSObject> jsOption = JSRef<JSObject>::Cast(info[0]);
        ParseEffectOption(jsOption, option);
    }
    SysOptions sysOptions;
    sysOptions.disableSystemAdaptation = false;
    if (info.Length() > NUM1 && info[NUM1]->IsObject()) {
        JSRef<JSObject> jsSysOptions = JSRef<JSObject>::Cast(info[NUM1]);
        ParseSysOptions(jsSysOptions, sysOptions);
    }
    ViewAbstractModel::GetInstance()->SetBackgroundEffect(option, sysOptions);
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
    SysOptions sysOptions;
    sysOptions.disableSystemAdaptation = false;
    if (info.Length() > NUM2 && info[NUM2]->IsObject()) {
        JSRef<JSObject> jsSysOptions = JSRef<JSObject>::Cast(info[NUM2]);
        ParseSysOptions(jsSysOptions, sysOptions);
    }
    ViewAbstractModel::GetInstance()->SetForegroundBlurStyle(styleOption, sysOptions);
}

void JSViewAbstract::JsSphericalEffect(const JSCallbackInfo& info)
{
    auto radio = 0.0;
    if (info[0]->IsNumber()) {
        radio = info[0]->ToNumber<double>();
    }
    ViewAbstractModel::GetInstance()->SetSphericalEffect(std::clamp(radio, 0.0, 1.0));
}

void JSViewAbstract::GetPixelStretchEffectLeftObj(const JSRef<JSObject>& jsObject, CalcDimension& left, PixStretchEffectOption& option)
{
    RefPtr<ResourceObject> leftObj;
    ParseJsDimensionVp(jsObject->GetProperty("left"), left, leftObj);
    if (leftObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& leftObj, PixStretchEffectOption& effectOption) {
            CalcDimension left;
            ResourceParseUtils::ParseResDimensionVp(leftObj, left);
            effectOption.left = left;
        };
        option.AddResource("pixelStretchEffect.left", leftObj, std::move(updateFunc));
    }
}

void JSViewAbstract::GetPixelStretchEffectRightObj(const JSRef<JSObject>& jsObject, CalcDimension& right, PixStretchEffectOption& option)
{
    RefPtr<ResourceObject> rightObj;
    ParseJsDimensionVp(jsObject->GetProperty("right"), right, rightObj);
    if (rightObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& rightObj, PixStretchEffectOption& effectOption) {
            CalcDimension right;
            ResourceParseUtils::ParseResDimensionVp(rightObj, right);
            effectOption.right = right;
        };
        option.AddResource("pixelStretchEffect.right", rightObj, std::move(updateFunc));
    }
}

void JSViewAbstract::GetPixelStretchEffectTopObj(const JSRef<JSObject>& jsObject, CalcDimension& top, PixStretchEffectOption& option)
{
    RefPtr<ResourceObject> topObj;
    ParseJsDimensionVp(jsObject->GetProperty("top"), top, topObj);
    if (topObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& topObj, PixStretchEffectOption& effectOption) {
            CalcDimension top;
            ResourceParseUtils::ParseResDimensionVp(topObj, top);
            effectOption.top = top;
        };
        option.AddResource("pixelStretchEffect.top", topObj, std::move(updateFunc));
    }
}

void JSViewAbstract::GetPixelStretchEffectBottomObj(const JSRef<JSObject>& jsObject, CalcDimension& bottom, PixStretchEffectOption& option)
{
    RefPtr<ResourceObject> bottomObj;
    ParseJsDimensionVp(jsObject->GetProperty("bottom"), bottom, bottomObj);
    if (bottomObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& bottomObj, PixStretchEffectOption& effectOption) {
            CalcDimension bottom;
            ResourceParseUtils::ParseResDimensionVp(bottomObj, bottom);
            effectOption.bottom = bottom;
        };
        option.AddResource("pixelStretchEffect.bottom", bottomObj, std::move(updateFunc));
    }
}

void JSViewAbstract::JsPixelStretchEffect(const JSCallbackInfo& info)
{
    ViewAbstractModel::GetInstance()->RemoveResObj("pixelStretchEffect");
    if (!info[0]->IsObject()) {
        PixStretchEffectOption option;
        option.ResetValue();
        ViewAbstractModel::GetInstance()->SetPixelStretchEffect(option);
        return;
    }
    auto jsObject = JSRef<JSObject>::Cast(info[0]);
    CalcDimension left;
    CalcDimension right;
    CalcDimension top;
    CalcDimension bottom;
    PixStretchEffectOption option;
    if (!SystemProperties::ConfigChangePerform()) {
        ParseJsDimensionVp(jsObject->GetProperty("left"), left);
        ParseJsDimensionVp(jsObject->GetProperty("right"), right);
        ParseJsDimensionVp(jsObject->GetProperty("top"), top);
        ParseJsDimensionVp(jsObject->GetProperty("bottom"), bottom);
    } else {
        GetPixelStretchEffectLeftObj(jsObject, left, option);
        GetPixelStretchEffectRightObj(jsObject, right, option);
        GetPixelStretchEffectTopObj(jsObject, top, option);
        GetPixelStretchEffectBottomObj(jsObject, bottom, option);
    }

    bool illegalInput = InitPixStretchEffect(left, right, top, bottom);
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

bool JSViewAbstract::InitPixStretchEffect(
    CalcDimension& left, CalcDimension& right, CalcDimension& top, CalcDimension bottom)
{
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
    return illegalInput;
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
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::NUMBER, JSCallbackInfoType::OBJECT };
    BackgroundImageSize bgImgSize;
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("JsBackgroundImageSize", jsVal, checkList)) {
        bgImgSize.SetSizeTypeX(BackgroundImageSizeType::AUTO);
        bgImgSize.SetSizeTypeY(BackgroundImageSizeType::AUTO);
        ViewAbstractModel::GetInstance()->SetBackgroundImageSize(bgImgSize);
        ViewAbstractModel::GetInstance()->ClearResObj("backgroundImageSize");
        return;
    }
    if (jsVal->IsNumber()) {
        auto sizeType = static_cast<BackgroundImageSizeType>(jsVal->ToNumber<int32_t>());
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE) &&
            (sizeType < BackgroundImageSizeType::CONTAIN || sizeType > BackgroundImageSizeType::FILL)) {
            sizeType = BackgroundImageSizeType::AUTO;
        }
        bgImgSize.SetSizeTypeX(sizeType);
        bgImgSize.SetSizeTypeY(sizeType);
        ViewAbstractModel::GetInstance()->ClearResObj("backgroundImageSize");
    } else {
        CalcDimension width;
        CalcDimension height;
        JSRef<JSObject> object = JSRef<JSObject>::Cast(jsVal);
        RefPtr<ResourceObject> resObjWidth;
        RefPtr<ResourceObject> resObjHeight;
        ParseJsDimensionVp(object->GetProperty("width"), width, resObjWidth);
        ParseJsDimensionVp(object->GetProperty("height"), height, resObjHeight);
        ViewAbstractModel::GetInstance()->SetBackgroundImageSizeUpdateFunc(bgImgSize, resObjWidth, "width");
        ViewAbstractModel::GetInstance()->SetBackgroundImageSizeUpdateFunc(bgImgSize, resObjHeight, "height");
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

void SetBgImgPositionWithAlign(BackgroundImagePosition& bgImgPosition, int32_t align)
{
    if (align > 8 || align < 0) { // align ranges from [0, 8].
        return;
    }
    std::vector<std::pair<double, double>> vec = { { 0.0, 0.0 }, { HALF_DIMENSION, 0.0 }, { FULL_DIMENSION, 0.0 },
        { 0.0, HALF_DIMENSION }, { HALF_DIMENSION, HALF_DIMENSION }, { FULL_DIMENSION, HALF_DIMENSION },
        { 0.0, FULL_DIMENSION }, { HALF_DIMENSION, FULL_DIMENSION }, { FULL_DIMENSION, FULL_DIMENSION } };
    SetBgImgPosition(
        DimensionUnit::PERCENT, DimensionUnit::PERCENT, vec[align].first, vec[align].second, bgImgPosition);
}

void SetBackgroundImagePositionUpdateFunc(
    BackgroundImagePosition& bgImgPosition, const RefPtr<ResourceObject>& resObj, const std::string direction)
{
    if (direction.empty()) {
        return;
    }
    if (!resObj) {
        (direction == "x") ? bgImgPosition.RemoveResource("backgroundImagePositionX")
                        : bgImgPosition.RemoveResource("backgroundImagePositionY");
        return;
    }
    auto&& updateFunc = [direction](const RefPtr<ResourceObject>& resObj, BackgroundImagePosition& position) {
        CalcDimension dimension;
        ResourceParseUtils::ParseResDimensionVp(resObj, dimension);
        double value = dimension.Value();
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            value = dimension.ConvertToPx();
        }
        DimensionUnit type = DimensionUnit::PX;
        if (dimension.Unit() == DimensionUnit::PERCENT) {
            value = dimension.Value();
            type = DimensionUnit::PERCENT;
        }
        AnimationOption option = ViewStackModel::GetInstance()->GetImplicitAnimationOption();
        (direction == "x") ? position.SetSizeX(AnimatableDimension(value, type, option))
                        : position.SetSizeY(AnimatableDimension(value, type, option));
    };
    (direction == "x") ? bgImgPosition.AddResource("backgroundImagePositionX", resObj, std::move(updateFunc))
                    : bgImgPosition.AddResource("backgroundImagePositionY", resObj, std::move(updateFunc));
}

void JSViewAbstract::JsBackgroundImagePosition(const JSCallbackInfo& info)
{
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::NUMBER, JSCallbackInfoType::OBJECT };
    BackgroundImagePosition bgImgPosition;
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("JsBackgroundImagePosition", jsVal, checkList)) {
        SetBgImgPosition(DimensionUnit::PX, DimensionUnit::PX, 0.0, 0.0, bgImgPosition);
        ViewAbstractModel::GetInstance()->SetBackgroundImagePosition(bgImgPosition);
        ViewAbstractModel::GetInstance()->ClearResObj("backgroundImagePosition");
        return;
    }
    if (jsVal->IsNumber()) {
        int32_t align = jsVal->ToNumber<int32_t>();
        bgImgPosition.SetIsAlign(true);
        SetBgImgPositionWithAlign(bgImgPosition, align);
        ViewAbstractModel::GetInstance()->ClearResObj("backgroundImagePosition");
    } else {
        CalcDimension x;
        CalcDimension y;
        JSRef<JSObject> object = JSRef<JSObject>::Cast(jsVal);
        RefPtr<ResourceObject> resObjX;
        RefPtr<ResourceObject> resObjY;
        ParseJsDimensionVp(object->GetProperty("x"), x, resObjX);
        ParseJsDimensionVp(object->GetProperty("y"), y, resObjY);
        SetBackgroundImagePositionUpdateFunc(bgImgPosition, resObjX, "x");
        SetBackgroundImagePositionUpdateFunc(bgImgPosition, resObjY, "y");
        double valueX = x.Value();
        double valueY = y.Value();
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            valueX = x.ConvertToPx();
            valueY = y.ConvertToPx();
        }
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

void JSViewAbstract::JsPadding(const JSCallbackInfo& info)
{
    ParseMarginOrPadding(info, EdgeType::PADDING);
}

void JSViewAbstract::JsMargin(const JSCallbackInfo& info)
{
    ParseMarginOrPadding(info, EdgeType::MARGIN);
}

void JSViewAbstract::ParseMarginOrPadding(const JSCallbackInfo& info, EdgeType type)
{
    ViewAbstractModel::GetInstance()->ResetResObj("margin");
    ViewAbstractModel::GetInstance()->ResetResObj("padding");
    ViewAbstractModel::GetInstance()->ResetResObj("safeAreaPadding");
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::OBJECT, JSCallbackInfoType::STRING,
        JSCallbackInfoType::NUMBER };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("MarginOrPadding", jsVal, checkList)) {
        auto resetDimension = CalcDimension(0.0);
        if (type == EdgeType::MARGIN) {
            ViewAbstractModel::GetInstance()->SetMargin(resetDimension);
        } else if (type == EdgeType::PADDING) {
            ViewAbstractModel::GetInstance()->SetPadding(resetDimension);
        } else if (type == EdgeType::SAFE_AREA_PADDING) {
            ViewAbstractModel::GetInstance()->ResetSafeAreaPadding();
        }
        return;
    }

    if (jsVal->IsObject()) {
        JSRef<JSObject> paddingObj = JSRef<JSObject>::Cast(jsVal);

        CalcDimension length;
        if (type == EdgeType::SAFE_AREA_PADDING && ParseJsLengthMetrics(paddingObj, length)) {
            ViewAbstractModel::GetInstance()->SetSafeAreaPadding(length);
            return;
        }

        CommonCalcDimension commonCalcDimension;
        auto useLengthMetrics = ParseCommonMarginOrPaddingCorner(paddingObj, commonCalcDimension);
        if (commonCalcDimension.left.has_value() || commonCalcDimension.right.has_value() ||
            commonCalcDimension.top.has_value() || commonCalcDimension.bottom.has_value()) {
            if (type == EdgeType::MARGIN) {
                if (useLengthMetrics) {
                    ViewAbstractModel::GetInstance()->SetMargins(GetLocalizedPadding(commonCalcDimension.top,
                        commonCalcDimension.bottom, commonCalcDimension.left, commonCalcDimension.right));
                } else {
                    if (SystemProperties::ConfigChangePerform()) {
                        ViewAbstractModel::GetInstance()->SetMargins(GetEdgeMargins(commonCalcDimension));
                    } else {
                        ViewAbstractModel::GetInstance()->SetMargins(commonCalcDimension.top, commonCalcDimension.bottom,
                            commonCalcDimension.left, commonCalcDimension.right);
                    }
                }
            } else if (type == EdgeType::PADDING) {
                if (useLengthMetrics) {
                    ViewAbstractModel::GetInstance()->SetPaddings(GetLocalizedPadding(commonCalcDimension.top,
                        commonCalcDimension.bottom, commonCalcDimension.left, commonCalcDimension.right));
                } else {
                    if (SystemProperties::ConfigChangePerform()) {
                        ViewAbstractModel::GetInstance()->SetPaddings(
                            GetEdgePaddingsOrSafeAreaPaddings(commonCalcDimension));
                    } else {
                        ViewAbstractModel::GetInstance()->SetPaddings(commonCalcDimension.top,
                            commonCalcDimension.bottom, commonCalcDimension.left, commonCalcDimension.right);
                    }
                }
            } else if (type == EdgeType::SAFE_AREA_PADDING) {
                if (useLengthMetrics) {
                    ViewAbstractModel::GetInstance()->SetSafeAreaPaddings(GetLocalizedPadding(commonCalcDimension.top,
                        commonCalcDimension.bottom, commonCalcDimension.left, commonCalcDimension.right));
                } else {
                    if (SystemProperties::ConfigChangePerform()) {
                        ViewAbstractModel::GetInstance()->SetSafeAreaPaddings(
                            GetEdgePaddingsOrSafeAreaPaddings(commonCalcDimension));
                    } else {
                        ViewAbstractModel::GetInstance()->SetSafeAreaPaddings(commonCalcDimension.top,
                            commonCalcDimension.bottom, commonCalcDimension.left, commonCalcDimension.right);
                    }
                }
            }
            return;
        }
    }

    CalcDimension length;
    RefPtr<ResourceObject> lengthResObj;
    if (!ParseJsDimensionVp(jsVal, length, lengthResObj)) {
        // use default value.
        length.Reset();
    }
    if (type == EdgeType::MARGIN) {
        if (SystemProperties::ConfigChangePerform() && lengthResObj) {
            ViewAbstractModel::GetInstance()->SetMargin(lengthResObj);
        } else {
            ViewAbstractModel::GetInstance()->SetMargin(length);
        }
    } else if (type == EdgeType::PADDING) {
        if (SystemProperties::ConfigChangePerform() && lengthResObj) {
            ViewAbstractModel::GetInstance()->SetPadding(lengthResObj);
        } else {
            ViewAbstractModel::GetInstance()->SetPadding(length);
        }
    }
}

NG::PaddingProperty JSViewAbstract::GetLocalizedPadding(const std::optional<CalcDimension>& top,
    const std::optional<CalcDimension>& bottom, const std::optional<CalcDimension>& start,
    const std::optional<CalcDimension>& end)
{
    NG::PaddingProperty paddings;
    if (start.has_value()) {
        if (start.value().Unit() == DimensionUnit::CALC) {
            paddings.start = NG::CalcLength(start.value().CalcValue());
        } else {
            paddings.start = NG::CalcLength(start.value());
        }
    }
    if (bottom.has_value()) {
        if (bottom.value().Unit() == DimensionUnit::CALC) {
            paddings.bottom = NG::CalcLength(bottom.value().CalcValue());
        } else {
            paddings.bottom = NG::CalcLength(bottom.value());
        }
    }
    if (end.has_value()) {
        if (end.value().Unit() == DimensionUnit::CALC) {
            paddings.end = NG::CalcLength(end.value().CalcValue());
        } else {
            paddings.end = NG::CalcLength(end.value());
        }
    }
    if (top.has_value()) {
        if (top.value().Unit() == DimensionUnit::CALC) {
            paddings.top = NG::CalcLength(top.value().CalcValue());
        } else {
            paddings.top = NG::CalcLength(top.value());
        }
    }
    return paddings;
}

NG::MarginProperty JSViewAbstract::GetEdgeMargins(const CommonCalcDimension& commonCalcDimension)
{
    NG::MarginProperty margins;
    if (commonCalcDimension.top.has_value()) {
        if (commonCalcDimension.top.value().Unit() == DimensionUnit::CALC) {
            margins.top = NG::CalcLength(commonCalcDimension.top.value().CalcValue());
        } else {
            margins.top = NG::CalcLength(commonCalcDimension.top.value());
        }
    }
    if (commonCalcDimension.bottom.has_value()) {
        if (commonCalcDimension.bottom.value().Unit() == DimensionUnit::CALC) {
            margins.bottom = NG::CalcLength(commonCalcDimension.bottom.value().CalcValue());
        } else {
            margins.bottom = NG::CalcLength(commonCalcDimension.bottom.value());
        }
    }
    if (commonCalcDimension.left.has_value()) {
        if (commonCalcDimension.left.value().Unit() == DimensionUnit::CALC) {
            margins.left = NG::CalcLength(commonCalcDimension.left.value().CalcValue());
        } else {
            margins.left = NG::CalcLength(commonCalcDimension.left.value());
        }
    }
    if (commonCalcDimension.right.has_value()) {
        if (commonCalcDimension.right.value().Unit() == DimensionUnit::CALC) {
            margins.right = NG::CalcLength(commonCalcDimension.right.value().CalcValue());
        } else {
            margins.right = NG::CalcLength(commonCalcDimension.right.value());
        }
    }
    GetEdgeMarginsResObj(margins, commonCalcDimension);
    return margins;
}

void JSViewAbstract::GetEdgeMarginsResObj(NG::MarginProperty& margins, const CommonCalcDimension& commonCalcDimension)
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    margins.resMap_.clear();
    if (commonCalcDimension.topResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::MarginProperty& margins) {
            CalcDimension result;
            ResourceParseUtils::ParseResDimensionVpNG(resObj, result);
            NG::CalcLength resultLength;
            resultLength = (result.Unit() == DimensionUnit::CALC) ? NG::CalcLength(result.CalcValue()) :
                NG::CalcLength(result);
            margins.top = resultLength;
        };
        margins.AddResource("margin.top", commonCalcDimension.topResObj, std::move(updateFunc));
    }
    if (commonCalcDimension.bottomResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::MarginProperty& margins) {
            CalcDimension result;
            ResourceParseUtils::ParseResDimensionVpNG(resObj, result);
            NG::CalcLength resultLength;
            resultLength = (result.Unit() == DimensionUnit::CALC) ? NG::CalcLength(result.CalcValue()) :
                NG::CalcLength(result);
            margins.bottom = resultLength;
        };
        margins.AddResource("margin.bottom", commonCalcDimension.bottomResObj, std::move(updateFunc));
    }
    if (commonCalcDimension.leftResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::MarginProperty& margins) {
            CalcDimension result;
            ResourceParseUtils::ParseResDimensionVpNG(resObj, result);
            NG::CalcLength resultLength;
            resultLength = (result.Unit() == DimensionUnit::CALC) ? NG::CalcLength(result.CalcValue()) :
                NG::CalcLength(result);
            margins.left = resultLength;
        };
        margins.AddResource("margin.left", commonCalcDimension.leftResObj, std::move(updateFunc));
    }
    if (commonCalcDimension.rightResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::MarginProperty& margins) {
            CalcDimension result;
            ResourceParseUtils::ParseResDimensionVpNG(resObj, result);
            NG::CalcLength resultLength;
            resultLength = (result.Unit() == DimensionUnit::CALC) ? NG::CalcLength(result.CalcValue()) :
                NG::CalcLength(result);
            margins.right = resultLength;
        };
        margins.AddResource("margin.right", commonCalcDimension.rightResObj, std::move(updateFunc));
    }
}

NG::PaddingProperty JSViewAbstract::GetEdgePaddingsOrSafeAreaPaddings(const CommonCalcDimension& commonCalcDimension)
{
    NG::PaddingProperty paddings = NG::ConvertToCalcPaddingProperty(
        commonCalcDimension.top, commonCalcDimension.bottom, commonCalcDimension.left, commonCalcDimension.right);
    if (!SystemProperties::ConfigChangePerform()) {
        return paddings;
    }
    if (commonCalcDimension.topResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::PaddingProperty& paddings) {
            CalcDimension result;
            ResourceParseUtils::ParseResDimensionVpNG(resObj, result);
            NG::CalcLength resultLength = ConvertCalcLength(result);
            paddings.top = resultLength;
        };
        paddings.AddResource("top", commonCalcDimension.topResObj, std::move(updateFunc));
    }
    if (commonCalcDimension.bottomResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::PaddingProperty& paddings) {
            CalcDimension result;
            ResourceParseUtils::ParseResDimensionVpNG(resObj, result);
            NG::CalcLength resultLength = ConvertCalcLength(result);
            paddings.bottom = resultLength;
        };
        paddings.AddResource("bottom", commonCalcDimension.bottomResObj, std::move(updateFunc));
    }
    if (commonCalcDimension.leftResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::PaddingProperty& paddings) {
            CalcDimension result;
            ResourceParseUtils::ParseResDimensionVpNG(resObj, result);
            NG::CalcLength resultLength = ConvertCalcLength(result);
            paddings.left = resultLength;
        };
        paddings.AddResource("left", commonCalcDimension.leftResObj, std::move(updateFunc));
    }
    if (commonCalcDimension.rightResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::PaddingProperty& paddings) {
            CalcDimension result;
            ResourceParseUtils::ParseResDimensionVpNG(resObj, result);
            NG::CalcLength resultLength = ConvertCalcLength(result);
            paddings.right = resultLength;
        };
        paddings.AddResource("right", commonCalcDimension.rightResObj, std::move(updateFunc));
    }
    return paddings;
}

void JSViewAbstract::ParseMarginOrPaddingCorner(JSRef<JSObject> obj, std::optional<CalcDimension>& top,
    std::optional<CalcDimension>& bottom, std::optional<CalcDimension>& left, std::optional<CalcDimension>& right)
{
    CalcDimension leftDimen;
    if (ParseJsDimensionVp(obj->GetProperty(static_cast<int32_t>(ArkUIIndex::LEFT)), leftDimen)) {
        left = leftDimen;
    }
    CalcDimension rightDimen;
    if (ParseJsDimensionVp(obj->GetProperty(static_cast<int32_t>(ArkUIIndex::RIGHT)), rightDimen)) {
        right = rightDimen;
    }
    CalcDimension topDimen;
    if (ParseJsDimensionVp(obj->GetProperty(static_cast<int32_t>(ArkUIIndex::TOP)), topDimen)) {
        top = topDimen;
    }
    CalcDimension bottomDimen;
    if (ParseJsDimensionVp(obj->GetProperty(static_cast<int32_t>(ArkUIIndex::BOTTOM)), bottomDimen)) {
        bottom = bottomDimen;
    }
}

void JSViewAbstract::ParseMarginOrPaddingCorner(JSRef<JSObject> obj, CommonCalcDimension& commonCalcDimension)
{
    CalcDimension leftDimen;
    RefPtr<ResourceObject> leftResObj;
    if (ParseJsDimensionVp(obj->GetProperty(static_cast<int32_t>(ArkUIIndex::LEFT)), leftDimen, leftResObj)) {
        commonCalcDimension.left = leftDimen;
    }
    CalcDimension rightDimen;
    RefPtr<ResourceObject> rightResObj;
    if (ParseJsDimensionVp(obj->GetProperty(static_cast<int32_t>(ArkUIIndex::RIGHT)), rightDimen, rightResObj)) {
        commonCalcDimension.right = rightDimen;
    }
    CalcDimension topDimen;
    RefPtr<ResourceObject> topResObj;
    if (ParseJsDimensionVp(obj->GetProperty(static_cast<int32_t>(ArkUIIndex::TOP)), topDimen, topResObj)) {
        commonCalcDimension.top = topDimen;
    }
    CalcDimension bottomDimen;
    RefPtr<ResourceObject> bottomResObj;
    if (ParseJsDimensionVp(obj->GetProperty(static_cast<int32_t>(ArkUIIndex::BOTTOM)), bottomDimen, bottomResObj)) {
        commonCalcDimension.bottom = bottomDimen;
    }
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    if (leftResObj) {
        commonCalcDimension.leftResObj = leftResObj;
    }
    if (rightResObj) {
        commonCalcDimension.rightResObj = rightResObj;
    }
    if (topResObj) {
        commonCalcDimension.topResObj = topResObj;
    }
    if (bottomResObj) {
        commonCalcDimension.bottomResObj = bottomResObj;
    }
}

void JSViewAbstract::ParseLocalizedMarginOrLocalizedPaddingCorner(
    const JSRef<JSObject>& object, LocalizedCalcDimension& localizedCalcDimension)
{
    auto jsStart = object->GetProperty(static_cast<int32_t>(ArkUIIndex::START));
    if (jsStart->IsObject()) {
        JSRef<JSObject> startObj = JSRef<JSObject>::Cast(jsStart);
        CalcDimension calcDimension;
        if (ParseJsLengthMetrics(startObj, calcDimension)) {
            localizedCalcDimension.start = calcDimension;
        }
    }
    auto jsEnd = object->GetProperty(static_cast<int32_t>(ArkUIIndex::END));
    if (jsEnd->IsObject()) {
        JSRef<JSObject> endObj = JSRef<JSObject>::Cast(jsEnd);
        CalcDimension calcDimension;
        if (ParseJsLengthMetrics(endObj, calcDimension)) {
            localizedCalcDimension.end = calcDimension;
        }
    }
    auto jsTop = object->GetProperty(static_cast<int32_t>(ArkUIIndex::TOP));
    if (jsTop->IsObject()) {
        JSRef<JSObject> topObj = JSRef<JSObject>::Cast(jsTop);
        CalcDimension calcDimension;
        if (ParseJsLengthMetrics(topObj, calcDimension)) {
            localizedCalcDimension.top = calcDimension;
        }
    }
    auto jsBottom = object->GetProperty(static_cast<int32_t>(ArkUIIndex::BOTTOM));
    if (jsBottom->IsObject()) {
        JSRef<JSObject> bottomObj = JSRef<JSObject>::Cast(jsBottom);
        CalcDimension calcDimension;
        if (ParseJsLengthMetrics(bottomObj, calcDimension)) {
            localizedCalcDimension.bottom = calcDimension;
        }
    }
}

bool JSViewAbstract::ParseCommonMarginOrPaddingCorner(
    const JSRef<JSObject>& object, CommonCalcDimension& commonCalcDimension)
{
    if (CheckLengthMetrics(object)) {
        LocalizedCalcDimension localizedCalcDimension;
        ParseLocalizedMarginOrLocalizedPaddingCorner(object, localizedCalcDimension);
        commonCalcDimension.top = localizedCalcDimension.top;
        commonCalcDimension.bottom = localizedCalcDimension.bottom;
        commonCalcDimension.left = localizedCalcDimension.start;
        commonCalcDimension.right = localizedCalcDimension.end;
        return true;
    }
    if (SystemProperties::ConfigChangePerform()) {
        ParseMarginOrPaddingCorner(object, commonCalcDimension);
    } else {
        ParseMarginOrPaddingCorner(object, commonCalcDimension.top, commonCalcDimension.bottom, commonCalcDimension.left,
            commonCalcDimension.right);
    }
        return false;
}

void JSViewAbstract::JsOutline(const JSCallbackInfo& info)
{
    ViewAbstractModel::GetInstance()->RemoveResObj("outerBorderWidth");
    ViewAbstractModel::GetInstance()->RemoveResObj("outerBorderColorRes");
    ViewAbstractModel::GetInstance()->RemoveResObj("outerBorderRadiusRes");
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::OBJECT };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("JsOutline", jsVal, checkList)) {
        CalcDimension borderWidth;
        ViewAbstractModel::GetInstance()->SetOuterBorderWidth(borderWidth);
        ViewAbstractModel::GetInstance()->SetOuterBorderColor(Color::BLACK);
        ViewAbstractModel::GetInstance()->SetOuterBorderRadius(borderWidth);
        ViewAbstractModel::GetInstance()->SetOuterBorderStyle(BorderStyle::SOLID);
        return;
    }
    JSRef<JSObject> object = JSRef<JSObject>::Cast(jsVal);
    auto valueOuterWidth = object->GetProperty("width");
    if (!valueOuterWidth->IsUndefined()) {
        ParseOuterBorderWidth(valueOuterWidth);
    } else if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        ViewAbstractModel::GetInstance()->SetOuterBorderWidth({});
    }

    // use default value when undefined.
    ParseOuterBorderColor(object->GetProperty("color"));

    auto valueOuterRadius = object->GetProperty("radius");
    if (!valueOuterRadius->IsUndefined()) {
        ParseOuterBorderRadius(valueOuterRadius);
    } else if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        ViewAbstractModel::GetInstance()->SetOuterBorderRadius(Dimension {});
    }
    // use default value when undefined.
    ParseOuterBorderStyle(object->GetProperty("style"));
    info.ReturnSelf();
}

void JSViewAbstract::JsOutlineWidth(const JSCallbackInfo& info)
{
    ViewAbstractModel::GetInstance()->RemoveResObj("outerBorderWidth");
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::STRING, JSCallbackInfoType::NUMBER,
        JSCallbackInfoType::OBJECT };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("JsOutlineWidth", jsVal, checkList)) {
        ViewAbstractModel::GetInstance()->SetOuterBorderWidth({});
        return;
    }
    ParseOuterBorderWidth(jsVal);
}

void JSViewAbstract::JsOutlineColor(const JSCallbackInfo& info)
{
    ViewAbstractModel::GetInstance()->RemoveResObj("outerBorderColorRes");
    ParseOuterBorderColor(info[0]);
}

void JSViewAbstract::JsOutlineRadius(const JSCallbackInfo& info)
{
    ViewAbstractModel::GetInstance()->RemoveResObj("outerBorderRadius");
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::STRING, JSCallbackInfoType::NUMBER,
        JSCallbackInfoType::OBJECT };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("JsOutlineRadius", jsVal, checkList)) {
        ViewAbstractModel::GetInstance()->SetOuterBorderRadius(Dimension {});
        return;
    }
    ParseOuterBorderRadius(jsVal);
}

void JSViewAbstract::JsOutlineStyle(const JSCallbackInfo& info)
{
    ParseOuterBorderStyle(info[0]);
}

void JSViewAbstract::JsBorder(const JSCallbackInfo& info)
{
    ViewAbstractModel::GetInstance()->ResetResObj("borderWidth");
    ViewAbstractModel::GetInstance()->ResetResObj("borderColor");
    ViewAbstractModel::GetInstance()->ResetResObj("borderRadius");
    ViewAbstractModel::GetInstance()->ResetResObj("border.dashGap");
    ViewAbstractModel::GetInstance()->ResetResObj("border.dashWidth");
    if (!info[0]->IsObject()) {
        CalcDimension borderWidth;
        ViewAbstractModel::GetInstance()->SetBorderWidth(borderWidth);
        ViewAbstractModel::GetInstance()->SetBorderColor(Color::BLACK);
        ViewAbstractModel::GetInstance()->SetBorderRadius(borderWidth);
        ViewAbstractModel::GetInstance()->SetBorderStyle(BorderStyle::SOLID);
        ViewAbstractModel::GetInstance()->SetDashGap(Dimension(-1));
        ViewAbstractModel::GetInstance()->SetDashWidth(Dimension(-1));
        return;
    }
    JSRef<JSObject> object = JSRef<JSObject>::Cast(info[0]);

    auto valueWidth = object->GetProperty(static_cast<int32_t>(ArkUIIndex::WIDTH));
    if (!valueWidth->IsUndefined()) {
        ParseBorderWidth(valueWidth);
    }

    // use default value when undefined.
    ParseBorderColor(object->GetProperty(static_cast<int32_t>(ArkUIIndex::COLOR)));

    auto valueRadius = object->GetProperty(static_cast<int32_t>(ArkUIIndex::RADIUS));
    if (!valueRadius->IsUndefined()) {
        ParseBorderRadius(valueRadius);
    }
    // use default value when undefined.
    ParseBorderStyle(object->GetProperty(static_cast<int32_t>(ArkUIIndex::STYLE)));

    auto dashGap = object->GetProperty("dashGap");
    if (!dashGap->IsUndefined()) {
        ParseDashGap(dashGap);
    }
    auto dashWidth = object->GetProperty("dashWidth");
    if (!dashWidth->IsUndefined()) {
        ParseDashWidth(dashWidth);
    }

    info.ReturnSelf();
}

bool IsBorderWidthObjUndefined(const JSRef<JSVal>& args)
{
    if (!args->IsObject()) {
        return false;
    }
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(args);
    if (obj->IsUndefined()) {
        return true;
    }
    // filter dynamic $r raw input
    if (obj->HasProperty("id")) {
        return false;
    }
    if ((!obj->HasProperty(TOP_PROPERTY) || obj->GetProperty(TOP_PROPERTY)->IsUndefined()) &&
        (!obj->HasProperty(RIGHT_PROPERTY) || obj->GetProperty(RIGHT_PROPERTY)->IsUndefined()) &&
        (!obj->HasProperty(BOTTOM_PROPERTY) || obj->GetProperty(BOTTOM_PROPERTY)->IsUndefined()) &&
        (!obj->HasProperty(LEFT_PROPERTY) || obj->GetProperty(LEFT_PROPERTY)->IsUndefined()) &&
        (!obj->HasProperty(START_PROPERTY) || obj->GetProperty(START_PROPERTY)->IsUndefined()) &&
        (!obj->HasProperty(END_PROPERTY) || obj->GetProperty(END_PROPERTY)->IsUndefined())) {
        return true;
    }

    return false;
}

void JSViewAbstract::JsBorderWidth(const JSCallbackInfo& info)
{
    ViewAbstractModel::GetInstance()->ResetResObj("borderWidth");
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::STRING, JSCallbackInfoType::NUMBER,
        JSCallbackInfoType::OBJECT };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("JsBorderWidth", jsVal, checkList)) {
        CalcDimension value = {};
        ViewAbstractModel::GetInstance()->SetBorderWidth(value);
        return;
    }

    ParseBorderWidth(jsVal);
}

void JSViewAbstract::ParseBorderWidth(const JSRef<JSVal>& args)
{
    CalcDimension borderWidth;
    RefPtr<ResourceObject> borderWidthResObj;
    if (ParseJsDimensionVp(args, borderWidth, borderWidthResObj)) {
        if (borderWidth.IsNegative()) {
            borderWidth.Reset();
        }
        if (borderWidth.Unit() == DimensionUnit::PERCENT) {
            borderWidth.Reset();
        }
        if (SystemProperties::ConfigChangePerform() && borderWidthResObj) {
            ViewAbstractModel::GetInstance()->SetBorderWidth(borderWidthResObj);
        } else {
            ViewAbstractModel::GetInstance()->SetBorderWidth(borderWidth);
        }
    } else if (args->IsObject()) {
        if (IsBorderWidthObjUndefined(args)) {
            CalcDimension value = {};
            ViewAbstractModel::GetInstance()->SetBorderWidth(value);
            return;
        }
        CommonCalcDimension commonCalcDimension;
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(args);
        if (ParseCommonEdgeWidths(obj, commonCalcDimension, true)) {
            ViewAbstractModel::GetInstance()->SetBorderWidth(commonCalcDimension.left, commonCalcDimension.right,
                commonCalcDimension.top, commonCalcDimension.bottom, true);
            return;
        }
        if (SystemProperties::ConfigChangePerform()) {
            NG::BorderWidthProperty borderWidth;
            ParseEdgeWidthsResObj(obj, borderWidth, true);
            ViewAbstractModel::GetInstance()->SetBorderWidth(borderWidth);
        } else {
            ViewAbstractModel::GetInstance()->SetBorderWidth(commonCalcDimension.left,
                commonCalcDimension.right, commonCalcDimension.top, commonCalcDimension.bottom);
        }
    } else {
        return;
    }
}

void JSViewAbstract::ParseDashGap(const JSRef<JSVal>& args)
{
    CalcDimension dashGap;
    if (ParseLengthMetricsToDimension(args, dashGap)) {
        if (dashGap.Unit() == DimensionUnit::PERCENT) {
            dashGap.Reset();
        }
        ViewAbstractModel::GetInstance()->SetDashGap(dashGap);
    } else if (args->IsObject()) {
        CommonCalcDimension commonCalcDimension;
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(args);
        if (ParseCommonEdgeWidthsForDashParams(obj, commonCalcDimension)) {
            ViewAbstractModel::GetInstance()->SetDashGap(commonCalcDimension.left,
                commonCalcDimension.right, commonCalcDimension.top, commonCalcDimension.bottom);
            return;
        }
        if (SystemProperties::ConfigChangePerform()) {
            NG::BorderWidthProperty dashGap;
            ParseEdgeWidthsForDashParamsResObj(obj, dashGap, static_cast<CalcDimension>(-1));
            ViewAbstractModel::GetInstance()->SetDashGap(dashGap);
        } else {
            ViewAbstractModel::GetInstance()->SetDashGap(commonCalcDimension.left,
                commonCalcDimension.right, commonCalcDimension.top, commonCalcDimension.bottom);
        }
    } else {
        dashGap.Reset();
        ViewAbstractModel::GetInstance()->SetDashGap(dashGap);
    }
}

void JSViewAbstract::ParseDashWidth(const JSRef<JSVal>& args)
{
    CalcDimension dashWidth;
    if (ParseLengthMetricsToDimension(args, dashWidth)) {
        if (dashWidth.Unit() == DimensionUnit::PERCENT) {
            dashWidth.Reset();
        }
        ViewAbstractModel::GetInstance()->SetDashWidth(dashWidth);
    } else if (args->IsObject()) {
        CommonCalcDimension commonCalcDimension;
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(args);
        if (ParseCommonEdgeWidthsForDashParams(obj, commonCalcDimension)) {
            ViewAbstractModel::GetInstance()->SetDashWidth(commonCalcDimension.left,
                commonCalcDimension.right, commonCalcDimension.top, commonCalcDimension.bottom);
            return;
        }
        if (SystemProperties::ConfigChangePerform()) {
            NG::BorderWidthProperty dashWidth;
            ParseEdgeWidthsForDashParamsResObj(obj, dashWidth, static_cast<CalcDimension>(-1));
            ViewAbstractModel::GetInstance()->SetDashWidth(dashWidth);
        } else {
            ViewAbstractModel::GetInstance()->SetDashWidth(commonCalcDimension.left,
                commonCalcDimension.right, commonCalcDimension.top, commonCalcDimension.bottom);
        }
    } else {
        dashWidth.Reset();
        ViewAbstractModel::GetInstance()->SetDashWidth(dashWidth);
    }
}

void JSViewAbstract::ParseEdgeOutlineWidthLeft(const JSRef<JSObject>& object, NG::BorderWidthProperty& borderWidth)
{
    if (object->IsUndefined()) {
        return;
    }
    RefPtr<ResourceObject> resObj;
    CalcDimension calcDim;
    bool ret = ParseJsDimensionVp(object->GetProperty("left"), calcDim, resObj);
    if (ret && calcDim.IsNonNegative()) {
        if (calcDim.Unit() == DimensionUnit::PERCENT) {
            calcDim.Reset();
        }
        borderWidth.leftDimen = calcDim;
    }
    if (resObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderWidthProperty& borderWidth) {
            CalcDimension dimension;
            ResourceParseUtils::ParseResDimensionVp(resObj, dimension);
            borderWidth.leftDimen = dimension;
        };
        borderWidth.AddResource("outLineWidth.EdgeOutlineWidths.left", resObj, std::move(updateFunc));
    }
}

void JSViewAbstract::ParseEdgeOutlineWidthRight(const JSRef<JSObject>& object, NG::BorderWidthProperty& borderWidth)
{
    if (object->IsUndefined()) {
        return;
    }
    RefPtr<ResourceObject> resObj;
    CalcDimension calcDim;
    bool ret = ParseJsDimensionVp(object->GetProperty("right"), calcDim, resObj);
    if (ret && calcDim.IsNonNegative()) {
        if (calcDim.Unit() == DimensionUnit::PERCENT) {
            calcDim.Reset();
        }
        borderWidth.rightDimen = calcDim;
    }
    if (resObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderWidthProperty& borderWidth) {
            CalcDimension dimension;
            ResourceParseUtils::ParseResDimensionVp(resObj, dimension);
            borderWidth.rightDimen = dimension;
        };
        borderWidth.AddResource("outLineWidth.EdgeOutlineWidths.right", resObj, std::move(updateFunc));
    }
}

void JSViewAbstract::ParseEdgeOutlineWidthTop(const JSRef<JSObject>& object, NG::BorderWidthProperty& borderWidth)
{
    if (object->IsUndefined()) {
        return;
    }
    RefPtr<ResourceObject> resObj;
    CalcDimension calcDim;
    bool ret = ParseJsDimensionVp(object->GetProperty("top"), calcDim, resObj);
    if (ret && calcDim.IsNonNegative()) {
        if (calcDim.Unit() == DimensionUnit::PERCENT) {
            calcDim.Reset();
        }
        borderWidth.topDimen = calcDim;
    }
    if (resObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderWidthProperty& borderWidth) {
            CalcDimension dimension;
            ResourceParseUtils::ParseResDimensionVp(resObj, dimension);
            borderWidth.topDimen = dimension;
        };
        borderWidth.AddResource("outLineWidth.EdgeOutlineWidths.top", resObj, std::move(updateFunc));
    }
}

void JSViewAbstract::ParseEdgeOutlineWidthBottom(const JSRef<JSObject>& object, NG::BorderWidthProperty& borderWidth)
{
    if (object->IsUndefined()) {
        return;
    }
    RefPtr<ResourceObject> resObj;
    CalcDimension calcDim;
    bool ret = ParseJsDimensionVp(object->GetProperty("bottom"), calcDim, resObj);
    if (ret && calcDim.IsNonNegative()) {
        if (calcDim.Unit() == DimensionUnit::PERCENT) {
            calcDim.Reset();
        }
        borderWidth.bottomDimen = calcDim;
    }
    if (resObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderWidthProperty& borderWidth) {
            CalcDimension dimension;
            ResourceParseUtils::ParseResDimensionVp(resObj, dimension);
            borderWidth.bottomDimen = dimension;
        };
        borderWidth.AddResource("outLineWidth.EdgeOutlineWidths.bottom", resObj, std::move(updateFunc));
    }
}

void JSViewAbstract::ParseOuterBorderWidthNew(const JSRef<JSVal>& args)
{
    CalcDimension borderWidth;
    RefPtr<ResourceObject> borderResObj;
    bool ret = ParseJsDimensionVp(args, borderWidth, borderResObj);
    if (borderResObj) {
        // Dimension
        ViewAbstractModel::GetInstance()->CreateWithOuterBorderWidthResourceObj(borderResObj);
    } else if (ret) {
        if (borderWidth.IsNegative() || borderWidth.Unit() == DimensionUnit::PERCENT) {
            borderWidth.Reset();
        }
        ViewAbstractModel::GetInstance()->SetOuterBorderWidth(borderWidth);
    } else if (args->IsObject()) {
        // obj
        JSRef<JSObject> object = JSRef<JSObject>::Cast(args);
        NG::BorderWidthProperty borderWidthProperty;
        borderWidthProperty.multiValued = true;
        borderWidthProperty.resMap_.clear();
        ParseEdgeOutlineWidthLeft(object, borderWidthProperty);
        ParseEdgeOutlineWidthRight(object, borderWidthProperty);
        ParseEdgeOutlineWidthTop(object, borderWidthProperty);
        ParseEdgeOutlineWidthBottom(object, borderWidthProperty);
        ViewAbstractModel::GetInstance()->SetOuterBorderWidthNew(borderWidthProperty);
    } else {
        return;
    }
}

void JSViewAbstract::ParseOuterBorderWidth(const JSRef<JSVal>& args)
{
    if (SystemProperties::ConfigChangePerform()) {
        ParseOuterBorderWidthNew(args);
        return;
    }
    CalcDimension borderWidth;
    if (ParseJsDimensionVp(args, borderWidth)) {
        if (borderWidth.IsNegative() || borderWidth.Unit() == DimensionUnit::PERCENT) {
            borderWidth.Reset();
        }
        ViewAbstractModel::GetInstance()->SetOuterBorderWidth(borderWidth);
    } else if (args->IsObject()) {
        std::optional<CalcDimension> leftDimen;
        std::optional<CalcDimension> rightDimen;
        std::optional<CalcDimension> topDimen;
        std::optional<CalcDimension> bottomDimen;
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

void JSViewAbstract::JsBorderImage(const JSCallbackInfo& info)
{
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::OBJECT };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("JsBorderImage", jsVal, checkList)) {
        RefPtr<BorderImage> borderImage = AceType::MakeRefPtr<BorderImage>();
        uint8_t imageBorderBitsets = 0;
        ViewAbstractModel::GetInstance()->SetBorderImage(borderImage, imageBorderBitsets);
        return;
    }
    JSRef<JSObject> object = JSRef<JSObject>::Cast(jsVal);
    CHECK_NULL_VOID(!object->IsEmpty());

    RefPtr<BorderImage> borderImage = AceType::MakeRefPtr<BorderImage>();
    uint8_t imageBorderBitsets = 0;

    auto valueSource = object->GetProperty(static_cast<int32_t>(ArkUIIndex::SOURCE));
    CHECK_NULL_VOID((valueSource->IsString() || valueSource->IsObject()));
    std::string srcResult;
    std::string bundleName;
    std::string moduleName;
    GetJsMediaBundleInfo(valueSource, bundleName, moduleName);
    borderImage->SetBundleName(bundleName);
    borderImage->SetModuleName(moduleName);
    if (valueSource->IsString() && !valueSource->ToString().empty()) {
        borderImage->SetSrc(valueSource->ToString());
        imageBorderBitsets |= BorderImage::SOURCE_BIT;
    } else if (valueSource->IsObject() && ParseJsMedia(valueSource, srcResult)) {
        borderImage->SetSrc(srcResult);
        imageBorderBitsets |= BorderImage::SOURCE_BIT;
    } else if (valueSource->IsObject()) {
        ParseBorderImageLinearGradient(valueSource, imageBorderBitsets);
    }
    auto valueOutset = object->GetProperty("outset");
    if (valueOutset->IsNumber() || valueOutset->IsString() || valueOutset->IsObject()) {
        imageBorderBitsets |= BorderImage::OUTSET_BIT;
        ParseBorderImageOutset(valueOutset, borderImage);
    }
    auto valueRepeat = object->GetProperty(static_cast<int32_t>(ArkUIIndex::REPEAT));
    if (!valueRepeat->IsNull()) {
        imageBorderBitsets |= BorderImage::REPEAT_BIT;
        ParseBorderImageRepeat(valueRepeat, borderImage);
    }
    auto valueSlice = object->GetProperty(static_cast<int32_t>(ArkUIIndex::SLICE));
    if (valueSlice->IsNumber() || valueSlice->IsString() || valueSlice->IsObject()) {
        imageBorderBitsets |= BorderImage::SLICE_BIT;
        ParseBorderImageSlice(valueSlice, borderImage);
    }
    auto valueWidth = object->GetProperty(static_cast<int32_t>(ArkUIIndex::WIDTH));
    if (valueWidth->IsNumber() || valueWidth->IsString() || valueWidth->IsObject()) {
        imageBorderBitsets |= BorderImage::WIDTH_BIT;
        ParseBorderImageWidth(valueWidth, borderImage);
    }
    auto needFill = object->GetProperty(static_cast<int32_t>(ArkUIIndex::FILL));
    if (needFill->IsBoolean()) {
        borderImage->SetNeedFillCenter(needFill->ToBoolean());
    }
    ViewAbstractModel::GetInstance()->SetBorderImage(borderImage, imageBorderBitsets);
    info.ReturnSelf();
}

bool JSViewAbstract::ParseBorderImageDimension(
    const JSRef<JSVal>& args, BorderImage::BorderImageOption& borderImageDimension)
{
    if (!args->IsObject()) {
        return false;
    }
    JSRef<JSObject> object = JSRef<JSObject>::Cast(args);
    if (CheckLengthMetrics(object)) {
        LocalizedCalcDimension localizedCalcDimension;
        ParseBorderImageLengthMetrics(object, localizedCalcDimension);
        borderImageDimension.topDimension = localizedCalcDimension.top;
        borderImageDimension.bottomDimension = localizedCalcDimension.bottom;
        borderImageDimension.startDimension = localizedCalcDimension.start;
        borderImageDimension.endDimension = localizedCalcDimension.end;
        return true;
    }
    static std::array<int32_t, DIRECTION_COUNT> keys = { static_cast<int32_t>(ArkUIIndex::LEFT),
        static_cast<int32_t>(ArkUIIndex::RIGHT), static_cast<int32_t>(ArkUIIndex::TOP),
        static_cast<int32_t>(ArkUIIndex::BOTTOM) };
    for (uint32_t i = 0; i < keys.size(); i++) {
        CalcDimension currentDimension;
        auto dimensionValue = object->GetProperty(keys.at(i));
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
    return false;
}

void JSViewAbstract::ParseBorderImageLengthMetrics(
    const JSRef<JSObject>& object, LocalizedCalcDimension& localizedCalcDimension)
{
    for (uint32_t i = 0; i < LENGTH_METRICS_KEYS.size(); i++) {
        auto jsVal = object->GetProperty(LENGTH_METRICS_KEYS.at(i));
        if (!jsVal->IsObject()) {
            continue;
        }
        JSRef<JSObject> lengthMetricsObj = JSRef<JSObject>::Cast(jsVal);
        CalcDimension calcDimension;
        if (ParseJsLengthMetrics(lengthMetricsObj, calcDimension)) {
            auto direction = static_cast<BorderImageDirection>(i);
            switch (direction) {
                case BorderImageDirection::LEFT:
                    localizedCalcDimension.start = calcDimension;
                    break;
                case BorderImageDirection::RIGHT:
                    localizedCalcDimension.end = calcDimension;
                    break;
                case BorderImageDirection::TOP:
                    localizedCalcDimension.top = calcDimension;
                    break;
                case BorderImageDirection::BOTTOM:
                    localizedCalcDimension.bottom = calcDimension;
                    break;
                default:
                    break;
            }
        }
    }
}

bool JSViewAbstract::CheckJSCallbackInfo(
    const std::string& callerName, const JSRef<JSVal>& tmpInfo, std::vector<JSCallbackInfoType>& infoTypes)
{
    bool typeVerified = false;
    std::string unrecognizedType;
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

void JSViewAbstract::UpdateGradientWithDirection(NG::Gradient& lineGradient, NG::GradientDirection direction)
{
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
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        GetJsAngle(static_cast<int32_t>(ArkUIIndex::ANGLE), jsObj, degree);
    } else {
        GetJsAngleWithDefault(static_cast<int32_t>(ArkUIIndex::ANGLE), jsObj, degree, 180.0f);
    }
    if (degree) {
        lineGradient.GetLinearGradient()->angle = CalcDimension(degree.value(), DimensionUnit::PX);
        degree.reset();
    }
    // direction
    auto direction = static_cast<NG::GradientDirection>(
        jsObj->GetPropertyValue<int32_t>(static_cast<int32_t>(ArkUIIndex::DIRECTION),
        static_cast<int32_t>(NG::GradientDirection::NONE)));
    UpdateGradientWithDirection(lineGradient, direction);
    auto repeating = jsObj->GetPropertyValue<bool>(static_cast<int32_t>(ArkUIIndex::REPEATING), false);
    lineGradient.SetRepeat(repeating);
    NewGetJsGradientColorStops(lineGradient, jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::COLORS)));
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
    if (option.startDimension.has_value()) {
        borderImage->SetEdgeOutset(BorderImageDirection::START, option.startDimension.value());
    }
    if (option.endDimension.has_value()) {
        borderImage->SetEdgeOutset(BorderImageDirection::END, option.endDimension.value());
    }
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
    if (!args->IsObject()) {
        return;
    }
    JSRef<JSObject> object = JSRef<JSObject>::Cast(args);
    if (CheckLengthMetrics(object)) {
        LocalizedCalcDimension localizedCalcDimension;
        ParseBorderImageLengthMetrics(object, localizedCalcDimension);
        if (localizedCalcDimension.top.has_value()) {
            borderImage->SetEdgeSlice(BorderImageDirection::TOP, localizedCalcDimension.top.value());
        }
        if (localizedCalcDimension.bottom.has_value()) {
            borderImage->SetEdgeSlice(BorderImageDirection::BOTTOM, localizedCalcDimension.bottom.value());
        }
        if (localizedCalcDimension.start.has_value()) {
            borderImage->SetEdgeSlice(BorderImageDirection::START, localizedCalcDimension.start.value());
        }
        if (localizedCalcDimension.end.has_value()) {
            borderImage->SetEdgeSlice(BorderImageDirection::END, localizedCalcDimension.end.value());
        }
        return;
    }
    static std::array<int32_t, DIRECTION_COUNT> keys = { static_cast<int32_t>(ArkUIIndex::LEFT),
        static_cast<int32_t>(ArkUIIndex::RIGHT), static_cast<int32_t>(ArkUIIndex::TOP),
        static_cast<int32_t>(ArkUIIndex::BOTTOM) };
    for (uint32_t i = 0; i < keys.size(); i++) {
        auto dimensionValue = object->GetProperty(keys.at(i));
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
    if (option.startDimension.has_value()) {
        borderImage->SetEdgeWidth(BorderImageDirection::START, option.startDimension.value());
    }
    if (option.endDimension.has_value()) {
        borderImage->SetEdgeWidth(BorderImageDirection::END, option.endDimension.value());
    }
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
    ViewAbstractModel::GetInstance()->ResetResObj("borderColor");
    ParseBorderColor(info[0]);
}

NG::BorderColorProperty JSViewAbstract::GetLocalizedBorderColor(const std::optional<Color>& colorStart,
    const std::optional<Color>& colorEnd, const std::optional<Color>& colorTop,
    const std::optional<Color>& colorBottom)
{
    NG::BorderColorProperty borderColors;
    borderColors.startColor = colorStart;
    borderColors.endColor = colorEnd;
    borderColors.topColor = colorTop;
    borderColors.bottomColor = colorBottom;
    borderColors.multiValued = true;
    return borderColors;
}

NG::BorderColorProperty JSViewAbstract::GetLocalizedBorderColor(const CommonColor& commonColor)
{
    NG::BorderColorProperty borderColors;
    borderColors.startColor = commonColor.left;
    borderColors.endColor = commonColor.right;
    borderColors.topColor = commonColor.top;
    borderColors.bottomColor = commonColor.bottom;
    if (!SystemProperties::ConfigChangePerform()) {
        return borderColors;
    }
    if (commonColor.leftResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderColorProperty& borderColors) {
            Color result;
            ResourceParseUtils::ParseResColor(resObj, result);
            borderColors.startColor = result;
        };
        borderColors.AddResource("borderColor.start", commonColor.leftResObj, std::move(updateFunc));
    }
    if (commonColor.rightResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderColorProperty& borderColors) {
            Color result;
            ResourceParseUtils::ParseResColor(resObj, result);
            borderColors.endColor = result;
        };
        borderColors.AddResource("borderColor.end", commonColor.rightResObj, std::move(updateFunc));
    }
    if (commonColor.topResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderColorProperty& borderColors) {
            Color result;
            ResourceParseUtils::ParseResColor(resObj, result);
            borderColors.topColor = result;
        };
        borderColors.AddResource("borderColor.top", commonColor.topResObj, std::move(updateFunc));
    }
    if (commonColor.bottomResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderColorProperty& borderColors) {
            Color result;
            ResourceParseUtils::ParseResColor(resObj, result);
            borderColors.bottomColor = result;
        };
        borderColors.AddResource("borderColor.bottom", commonColor.bottomResObj, std::move(updateFunc));
    }
    borderColors.multiValued = true;
    return borderColors;
}

NG::BorderColorProperty JSViewAbstract::GetBorderColor(const CommonColor& commonColor)
{
    NG::BorderColorProperty borderColors;
    borderColors.leftColor = commonColor.left;
    borderColors.rightColor = commonColor.right;
    borderColors.topColor = commonColor.top;
    borderColors.bottomColor = commonColor.bottom;
    if (!SystemProperties::ConfigChangePerform()) {
        return borderColors;
    }
    if (commonColor.leftResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderColorProperty& borderColors) {
            Color result;
            ResourceParseUtils::ParseResColor(resObj, result);
            borderColors.leftColor = result;
        };
        borderColors.AddResource("borderColor.left", commonColor.leftResObj, std::move(updateFunc));
    }
    if (commonColor.rightResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderColorProperty& borderColors) {
            Color result;
            ResourceParseUtils::ParseResColor(resObj, result);
            borderColors.rightColor = result;
        };
        borderColors.AddResource("borderColor.right", commonColor.rightResObj, std::move(updateFunc));
    }
    if (commonColor.topResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderColorProperty& borderColors) {
            Color result;
            ResourceParseUtils::ParseResColor(resObj, result);
            borderColors.topColor = result;
        };
        borderColors.AddResource("borderColor.top", commonColor.topResObj, std::move(updateFunc));
    }
    if (commonColor.bottomResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderColorProperty& borderColors) {
            Color result;
            ResourceParseUtils::ParseResColor(resObj, result);
            borderColors.bottomColor = result;
        };
        borderColors.AddResource("borderColor.bottom", commonColor.bottomResObj, std::move(updateFunc));
    }
    borderColors.multiValued = true;
    return borderColors;
}

void JSViewAbstract::ParseBorderColor(const JSRef<JSVal>& args)
{
    Color borderColor;
    RefPtr<ResourceObject> borderColorResObj;
    if (ParseJsColor(args, borderColor, borderColorResObj)) {
        if (SystemProperties::ConfigChangePerform() && borderColorResObj) {
            ViewAbstractModel::GetInstance()->SetBorderColor(borderColorResObj);
        } else {
            ViewAbstractModel::GetInstance()->SetBorderColor(borderColor);
        }
    } else if (args->IsObject()) {
        CommonColor commonColor;
        JSRef<JSObject> object = JSRef<JSObject>::Cast(args);
        if (ParseCommonEdgeColors(object, commonColor)) {
            ViewAbstractModel::GetInstance()->SetBorderColor(GetLocalizedBorderColor(commonColor));
            return;
        }
        ViewAbstractModel::GetInstance()->SetBorderColor(GetBorderColor(commonColor));
    } else {
        ViewAbstractModel::GetInstance()->SetBorderColor(Color::BLACK);
    }
}

void JSViewAbstract::ParseOuterBorderColor(const JSRef<JSVal>& args)
{
    Color borderColor;
    if (!SystemProperties::ConfigChangePerform()) {
        if (ParseJsColor(args, borderColor)) {
            ViewAbstractModel::GetInstance()->SetOuterBorderColor(borderColor);
        } else if (args->IsObject()) {
            CommonColor commonColor;
            JSRef<JSObject> object = JSRef<JSObject>::Cast(args);
            if (ParseCommonEdgeColors(object, commonColor)) {
                ViewAbstractModel::GetInstance()->SetOuterBorderColor(
                    GetLocalizedBorderColor(commonColor.left, commonColor.right, commonColor.top, commonColor.bottom));
                return;
            }
            ViewAbstractModel::GetInstance()->SetOuterBorderColor(
                commonColor.left, commonColor.right, commonColor.top, commonColor.bottom);
        } else {
            ViewAbstractModel::GetInstance()->SetOuterBorderColor(Color::BLACK);
        }
    } else {
        RefPtr<ResourceObject> borderResObj;
        bool ret = ParseJsColor(args, borderColor, borderResObj);
        if (borderResObj) {
            ViewAbstractModel::GetInstance()->CreateWithOuterBorderColorResourceObj(borderResObj);
        } else if (ret) {
            ViewAbstractModel::GetInstance()->SetOuterBorderColor(borderColor);
        } else if (args->IsObject()) {
            JSRef<JSObject> object = JSRef<JSObject>::Cast(args);
            NG::BorderColorProperty borderColors;
            borderColors.resMap_.clear();
            if (object->HasProperty(static_cast<int32_t>(ArkUIIndex::START)) ||
                object->HasProperty(static_cast<int32_t>(ArkUIIndex::END))) {
                ParseLocalizedEdgeColorsForOutLineColor(object, borderColors);
                ViewAbstractModel::GetInstance()->SetOuterBorderColor(borderColors);
            } else {
                ParseEdgeColorsForOutLineColor(object, borderColors);
                borderColors.multiValued = true;
                ViewAbstractModel::GetInstance()->SetOuterBorderColor(borderColors);
            }
        } else {
            ViewAbstractModel::GetInstance()->SetOuterBorderColor(Color::BLACK);
        }
    }
}

void JSViewAbstract::JsBorderRadius(const JSCallbackInfo& info)
{
    ViewAbstractModel::GetInstance()->ResetResObj("borderRadius");
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::STRING, JSCallbackInfoType::NUMBER,
        JSCallbackInfoType::OBJECT };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("JsBorderRadius", jsVal, checkList)) {
        ViewAbstractModel::GetInstance()->SetBorderRadius(Dimension {});
        return;
    }
    ParseBorderRadius(jsVal);
}

NG::BorderRadiusProperty JSViewAbstract::GetLocalizedBorderRadius(const std::optional<Dimension>& radiusTopStart,
    const std::optional<Dimension>& radiusTopEnd, const std::optional<Dimension>& radiusBottomStart,
    const std::optional<Dimension>& radiusBottomEnd)
{
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopStart = radiusTopStart;
    borderRadius.radiusTopEnd = radiusTopEnd;
    borderRadius.radiusBottomStart = radiusBottomStart;
    borderRadius.radiusBottomEnd = radiusBottomEnd;
    borderRadius.multiValued = true;
    return borderRadius;
}

void JSViewAbstract::ParseBorderRadius(const JSRef<JSVal>& args)
{
    CalcDimension borderRadius;
    RefPtr<ResourceObject> borderRadiusResObj;
    if (ParseJsDimensionVp(args, borderRadius, borderRadiusResObj)) {
        if (SystemProperties::ConfigChangePerform() && borderRadiusResObj) {
            ViewAbstractModel::GetInstance()->SetBorderRadius(borderRadiusResObj);
        } else {
            ViewAbstractModel::GetInstance()->SetBorderRadius(borderRadius);
        }
    } else if (args->IsObject()) {
        JSRef<JSObject> object = JSRef<JSObject>::Cast(args);
        CalcDimension topLeft;
        CalcDimension topRight;
        CalcDimension bottomLeft;
        CalcDimension bottomRight;
        if (ParseAllBorderRadiuses(object, topLeft, topRight, bottomLeft, bottomRight)) {
            ViewAbstractModel::GetInstance()->SetBorderRadius(
                GetLocalizedBorderRadius(topLeft, topRight, bottomLeft, bottomRight));
                return;
        }
        if (SystemProperties::ConfigChangePerform()) {
            NG::BorderRadiusProperty borderRadius;
            RefPtr<ResourceObject> topLeftResObj;
            RefPtr<ResourceObject> topRightResObj;
            RefPtr<ResourceObject> bottomLeftResObj;
            RefPtr<ResourceObject> bottomRightResObj;
            GetBorderRadiusResObj("topLeft", object, topLeft, topLeftResObj);
            GetBorderRadiusResObj("topRight", object, topRight, topRightResObj);
            GetBorderRadiusResObj("bottomLeft", object, bottomLeft, bottomLeftResObj);
            GetBorderRadiusResObj("bottomRight", object, bottomRight, bottomRightResObj);
            borderRadius.radiusTopLeft = topLeft;
            borderRadius.radiusTopRight = topRight;
            borderRadius.radiusBottomLeft = bottomLeft;
            borderRadius.radiusBottomRight = bottomRight;
            borderRadius.multiValued = true;
            ParseAllBorderRadiusesResObj(
                borderRadius, topLeftResObj, topRightResObj, bottomLeftResObj, bottomRightResObj);
            ViewAbstractModel::GetInstance()->SetBorderRadius(borderRadius);
        } else {
            ViewAbstractModel::GetInstance()->SetBorderRadius(topLeft, topRight, bottomLeft, bottomRight);
        }
    }
}

void JSViewAbstract::ParseOuterBorderRadius(const JSRef<JSVal>& args)
{
    if (!args->IsObject() && !args->IsNumber() && !args->IsString()) {
        return;
    }
    CalcDimension borderRadius;
    if (!SystemProperties::ConfigChangePerform()) {
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
            if (ParseAllBorderRadiuses(object, topLeft, topRight, bottomLeft, bottomRight)) {
                ViewAbstractModel::GetInstance()->SetOuterBorderRadius(
                    GetLocalizedBorderRadius(topLeft, topRight, bottomLeft, bottomRight));
            }
            ViewAbstractModel::GetInstance()->SetOuterBorderRadius(topLeft, topRight, bottomLeft, bottomRight);
        }
    } else {
        RefPtr<ResourceObject> resObj;
        bool ret = ParseJsDimensionVp(args, borderRadius, resObj);
        if (resObj) {
            ViewAbstractModel::GetInstance()->CreateWithOuterBorderRadiusResourceObj(resObj);
        } else if (ret) {
            if (borderRadius.Unit() == DimensionUnit::PERCENT) {
                borderRadius.Reset();
            }
            ViewAbstractModel::GetInstance()->SetOuterBorderRadius(borderRadius);
        } else if (args->IsObject()) {
            JSRef<JSObject> object = JSRef<JSObject>::Cast(args);
            NG::BorderRadiusProperty borderRadius;
            if (!ParseAllBorderRadiusesForOutLine(object, borderRadius)) {
                borderRadius.multiValued = true;
            }
            ViewAbstractModel::GetInstance()->SetOuterBorderRadius(borderRadius);
        }
    }
}

void JSViewAbstract::GetBorderRadiusTopLeft(const JSRef<JSVal>& jsValue, NG::BorderRadiusProperty& borderRadius)
{
    RefPtr<ResourceObject> topLeftResObj;
    CalcDimension dim;
    if (ParseJsDimensionVp(jsValue, dim, topLeftResObj)) {
        borderRadius.radiusTopLeft = dim;
    }
    if (topLeftResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderRadiusProperty& borderRadius) {
            CalcDimension dimension;
            ResourceParseUtils::ParseResDimensionVp(resObj, dimension);
            borderRadius.radiusTopLeft = dimension;
        };
        borderRadius.AddResource("outLineRadius.radius.radiusTopLft", topLeftResObj, std::move(updateFunc));
    }
}

void JSViewAbstract::GetBorderRadiusTopRight(const JSRef<JSVal>& jsValue, NG::BorderRadiusProperty& borderRadius)
{
    RefPtr<ResourceObject> topRightResObj;
    CalcDimension dim;
    if (ParseJsDimensionVp(jsValue, dim, topRightResObj)) {
        borderRadius.radiusTopRight = dim;
    }
    if (topRightResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderRadiusProperty& borderRadius) {
            CalcDimension dimension;
            ResourceParseUtils::ParseResDimensionVp(resObj, dimension);
            borderRadius.radiusTopRight = dimension;
        };
        borderRadius.AddResource("outLineRadius.radius.radiusTopRight", topRightResObj, std::move(updateFunc));
    }
}

void JSViewAbstract::GetBorderRadiusBottomLeft(const JSRef<JSVal>& jsValue, NG::BorderRadiusProperty& borderRadius)
{
    RefPtr<ResourceObject> bottomLeftResObj;
    CalcDimension dim;
    if (ParseJsDimensionVp(jsValue, dim, bottomLeftResObj)) {
        borderRadius.radiusBottomLeft = dim;
    }
    if (bottomLeftResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderRadiusProperty& borderRadius) {
            CalcDimension dimension;
            ResourceParseUtils::ParseResDimensionVp(resObj, dimension);
            borderRadius.radiusBottomLeft = dimension;
        };
        borderRadius.AddResource("outLineRadius.radius.radiusBottomLeft", bottomLeftResObj, std::move(updateFunc));
    }
}

void JSViewAbstract::GetBorderRadiusBottomRight(const JSRef<JSVal>& jsValue, NG::BorderRadiusProperty& borderRadius)
{
    RefPtr<ResourceObject> bottomRightResObj;
    CalcDimension dim;
    if (ParseJsDimensionVp(jsValue, dim, bottomRightResObj)) {
        borderRadius.radiusBottomRight = dim;
    }
    if (bottomRightResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderRadiusProperty& borderRadius) {
            CalcDimension dimension;
            ResourceParseUtils::ParseResDimensionVp(resObj, dimension);
            borderRadius.radiusBottomRight = dimension;
        };
        borderRadius.AddResource("outLineRadius.radius.radiusBottomRight", bottomRightResObj, std::move(updateFunc));
    }
}

bool JSViewAbstract::ParseAllBorderRadiusesForOutLine(JSRef<JSObject>& object, NG::BorderRadiusProperty& borderRadius)
{
    if (object->IsUndefined()) {
        return false;
    }
    borderRadius.resMap_.clear();
    if (object->HasProperty(TOP_START_PROPERTY) || object->HasProperty(TOP_END_PROPERTY) ||
        object->HasProperty(BOTTOM_START_PROPERTY) || object->HasProperty(BOTTOM_END_PROPERTY)) {
        CalcDimension topStart;
        CalcDimension topEnd;
        CalcDimension bottomStart;
        CalcDimension bottomEnd;
        GetBorderRadiusByLengthMetrics(TOP_START_PROPERTY, object, topStart);
        GetBorderRadiusByLengthMetrics(TOP_END_PROPERTY, object, topEnd);
        GetBorderRadiusByLengthMetrics(BOTTOM_START_PROPERTY, object, bottomStart);
        GetBorderRadiusByLengthMetrics(BOTTOM_END_PROPERTY, object, bottomEnd);
        borderRadius.radiusTopStart = topStart;
        borderRadius.radiusTopEnd = topEnd;
        borderRadius.radiusBottomEnd = bottomStart;
        borderRadius.radiusBottomStart = bottomEnd;
        return true;
    }
    GetBorderRadiusTopLeft(object->GetProperty("topLeft"), borderRadius);
    GetBorderRadiusTopRight(object->GetProperty("topRight"), borderRadius);
    GetBorderRadiusBottomLeft(object->GetProperty("bottomLeft"), borderRadius);
    GetBorderRadiusBottomRight(object->GetProperty("bottomRight"), borderRadius);
    return false;
}

void JSViewAbstract::GetBorderRadius(const char* key, JSRef<JSObject>& object, CalcDimension& radius)
{
    ParseJsDimensionVp(object->GetProperty(key), radius);
}

void JSViewAbstract::GetBorderRadiusResObj(
    const char* key, JSRef<JSObject>& object, CalcDimension& radius, RefPtr<ResourceObject>& resObj)
{
    ParseJsDimensionVp(object->GetProperty(key), radius, resObj);
}

void JSViewAbstract::GetBorderRadiusByLengthMetrics(const char* key, JSRef<JSObject>& object, CalcDimension& radius)
{
    if (object->HasProperty(key) && object->GetProperty(key)->IsObject()) {
        JSRef<JSObject> startObj = JSRef<JSObject>::Cast(object->GetProperty(key));
        ParseJsLengthMetrics(startObj, radius);
    }
}

bool JSViewAbstract::ParseAllBorderRadiuses(JSRef<JSObject>& object, CalcDimension& topLeft, CalcDimension& topRight,
    CalcDimension& bottomLeft, CalcDimension& bottomRight)
{
    TextBackgroundStyle textBackgroundStyle;
    return ParseAllBorderRadiuses(object, topLeft, topRight, bottomLeft, bottomRight, textBackgroundStyle);
}

void JSViewAbstract::RegisterTextBackgroundStyleResource(TextBackgroundStyle& textBackgroundStyle,
    RefPtr<ResourceObject>& resObjTopLeft, RefPtr<ResourceObject>& resObjTopRight,
    RefPtr<ResourceObject>& resObjBottomLeft, RefPtr<ResourceObject>& resObjBottomRight)
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    if (resObjTopLeft) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObjTopLeft,
            TextBackgroundStyle& textBackgroundStyle) {
            CalcDimension radius;
            ResourceParseUtils::ParseResDimensionVp(resObjTopLeft, radius);
            textBackgroundStyle.backgroundRadius->radiusTopLeft = radius;
            textBackgroundStyle.backgroundRadius->multiValued = true;
        };
        textBackgroundStyle.AddResource("textBackgroundStyle.radiusTopLeft", resObjTopLeft,
            std::move(updateFunc));
    }
    if (resObjTopRight) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObjTopRight,
            TextBackgroundStyle& textBackgroundStyle) {
            CalcDimension radius;
            ResourceParseUtils::ParseResDimensionVp(resObjTopRight, radius);
            textBackgroundStyle.backgroundRadius->radiusTopRight = radius;
            textBackgroundStyle.backgroundRadius->multiValued = true;
        };
        textBackgroundStyle.AddResource("textBackgroundStyle.radiusTopRight", resObjTopRight,
            std::move(updateFunc));
    }
    if (resObjBottomLeft) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObjBottomLeft,
            TextBackgroundStyle& textBackgroundStyle) {
            CalcDimension radius;
            ResourceParseUtils::ParseResDimensionVp(resObjBottomLeft, radius);
            textBackgroundStyle.backgroundRadius->radiusBottomLeft = radius;
            textBackgroundStyle.backgroundRadius->multiValued = true;
        };
        textBackgroundStyle.AddResource("textBackgroundStyle.radiusBottomLeft", resObjBottomLeft,
            std::move(updateFunc));
    }
    if (resObjBottomRight) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObjBottomRight,
            TextBackgroundStyle& textBackgroundStyle) {
            CalcDimension radius;
            ResourceParseUtils::ParseResDimensionVp(resObjBottomRight, radius);
            textBackgroundStyle.backgroundRadius->radiusBottomRight = radius;
            textBackgroundStyle.backgroundRadius->multiValued = true;
        };
        textBackgroundStyle.AddResource("textBackgroundStyle.radiusBottomRight", resObjBottomRight,
            std::move(updateFunc));
    }
}

bool JSViewAbstract::ParseAllBorderRadiuses(JSRef<JSObject>& object, CalcDimension& topLeft, CalcDimension& topRight,
    CalcDimension& bottomLeft, CalcDimension& bottomRight, TextBackgroundStyle& textBackgroundStyle)
{
    if (object->HasProperty(TOP_START_PROPERTY) || object->HasProperty(TOP_END_PROPERTY) ||
        object->HasProperty(BOTTOM_START_PROPERTY) || object->HasProperty(BOTTOM_END_PROPERTY)) {
        CalcDimension topStart;
        CalcDimension topEnd;
        CalcDimension bottomStart;
        CalcDimension bottomEnd;
        GetBorderRadiusByLengthMetrics(TOP_START_PROPERTY, object, topStart);
        GetBorderRadiusByLengthMetrics(TOP_END_PROPERTY, object, topEnd);
        GetBorderRadiusByLengthMetrics(BOTTOM_START_PROPERTY, object, bottomStart);
        GetBorderRadiusByLengthMetrics(BOTTOM_END_PROPERTY, object, bottomEnd);
        topLeft = topStart;
        topRight = topEnd;
        bottomLeft = bottomStart;
        bottomRight = bottomEnd;
        return true;
    }
    RefPtr<ResourceObject> resObjTopLeft;
    RefPtr<ResourceObject> resObjTopRight;
    RefPtr<ResourceObject> resObjBottomLeft;
    RefPtr<ResourceObject> resObjBottomRight;
    GetBorderRadiusResObj("topLeft", object, topLeft, resObjTopLeft);
    GetBorderRadiusResObj("topRight", object, topRight, resObjTopRight);
    GetBorderRadiusResObj("bottomLeft", object, bottomLeft, resObjBottomLeft);
    GetBorderRadiusResObj("bottomRight", object, bottomRight, resObjBottomRight);
    
    RegisterTextBackgroundStyleResource(textBackgroundStyle, resObjTopLeft, resObjTopRight, resObjBottomLeft,
        resObjBottomRight);
    return false;
}

#define ADDRESOURCE_UPDATE_FUNC(property, resObj, radiusMember, resourceName) \
    RefPtr<ResourceObject> resObj; \
    ParseJsDimensionVp(object->GetProperty(#property), property, resObj); \
    if (resObj) { \
        auto&& updateFunc = [](const RefPtr<ResourceObject>& (resObj), NG::BorderRadiusProperty& borderRadiusProperty) { \
            CalcDimension property; \
            ResourceParseUtils::ParseResDimensionVp(resObj, property); \
            if (LessNotEqual((property).Value(), 0.0f)) { \
                (property).Reset(); \
            } \
            borderRadiusProperty.radiusMember = property; \
        }; \
        borderRadius.AddResource(resourceName, resObj, std::move(updateFunc)); \
    }

void JSViewAbstract::ParseAllBorderRadiuses(JSRef<JSObject>& object, NG::BorderRadiusProperty& borderRadius)
{
    CalcDimension topLeft;
    CalcDimension topRight;
    CalcDimension bottomLeft;
    CalcDimension bottomRight;
    bool hasSetBorderRadius = false;
    if (object->HasProperty(TOP_START_PROPERTY) || object->HasProperty(TOP_END_PROPERTY) ||
        object->HasProperty(BOTTOM_START_PROPERTY) || object->HasProperty(BOTTOM_END_PROPERTY)) {
        CalcDimension topStart;
        CalcDimension topEnd;
        CalcDimension bottomStart;
        CalcDimension bottomEnd;
        GetBorderRadiusByLengthMetrics(TOP_START_PROPERTY, object, topStart);
        GetBorderRadiusByLengthMetrics(TOP_END_PROPERTY, object, topEnd);
        GetBorderRadiusByLengthMetrics(BOTTOM_START_PROPERTY, object, bottomStart);
        GetBorderRadiusByLengthMetrics(BOTTOM_END_PROPERTY, object, bottomEnd);
        topLeft = topStart;
        topRight = topEnd;
        bottomLeft = bottomStart;
        bottomRight = bottomEnd;
        hasSetBorderRadius = true;
    }
    else {
        ADDRESOURCE_UPDATE_FUNC(topLeft, topLeftResObj, radiusTopLeft, "borderRadius.topLeft")
        ADDRESOURCE_UPDATE_FUNC(topRight, topRightResObj, radiusTopRight, "borderRadius.topRight")
        ADDRESOURCE_UPDATE_FUNC(bottomLeft, bottomLeftResObj, radiusBottomLeft, "borderRadius.bottomLeft")
        ADDRESOURCE_UPDATE_FUNC(bottomRight, bottomRightResObj, radiusBottomRight, "borderRadius.bottomRight")
    }
    if (LessNotEqual(topLeft.Value(), 0.0f)) {
        topLeft.Reset();
    }
    if (LessNotEqual(topRight.Value(), 0.0f)) {
        topRight.Reset();
    }
    if (LessNotEqual(bottomLeft.Value(), 0.0f)) {
        bottomLeft.Reset();
    }
    if (LessNotEqual(bottomRight.Value(), 0.0f)) {
        bottomRight.Reset();
    }
    auto isRtl = hasSetBorderRadius && AceApplicationInfo::GetInstance().IsRightToLeft();
    borderRadius.radiusTopLeft = isRtl ? topRight : topLeft;
    borderRadius.radiusTopRight = isRtl ? topLeft : topRight;
    borderRadius.radiusBottomLeft = isRtl ? bottomRight : bottomLeft;
    borderRadius.radiusBottomRight = isRtl ? bottomLeft : bottomRight;
    borderRadius.multiValued = true;
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

bool ConvertOptionBorderStyle(int32_t value, std::optional<BorderStyle>& style)
{
    style = static_cast<BorderStyle>(value);
    if (style < BorderStyle::SOLID || style > BorderStyle::NONE) {
        return false;
    }
    return true;
}
} // namespace

void JSViewAbstract::ParseBorderStyle(const JSRef<JSVal>& args)
{
    if (args->IsObject()) {
        std::optional<BorderStyle> styleLeft;
        std::optional<BorderStyle> styleRight;
        std::optional<BorderStyle> styleTop;
        std::optional<BorderStyle> styleBottom;
        JSRef<JSObject> object = JSRef<JSObject>::Cast(args);
        auto leftValue = object->GetProperty(static_cast<int32_t>(ArkUIIndex::LEFT));
        if (leftValue->IsNumber()) {
            styleLeft = ConvertBorderStyle(leftValue->ToNumber<int32_t>());
        }
        auto rightValue = object->GetProperty(static_cast<int32_t>(ArkUIIndex::RIGHT));
        if (rightValue->IsNumber()) {
            styleRight = ConvertBorderStyle(rightValue->ToNumber<int32_t>());
        }
        auto topValue = object->GetProperty(static_cast<int32_t>(ArkUIIndex::TOP));
        if (topValue->IsNumber()) {
            styleTop = ConvertBorderStyle(topValue->ToNumber<int32_t>());
        }
        auto bottomValue = object->GetProperty(static_cast<int32_t>(ArkUIIndex::BOTTOM));
        if (bottomValue->IsNumber()) {
            styleBottom = ConvertBorderStyle(bottomValue->ToNumber<int32_t>());
        }
        ViewAbstractModel::GetInstance()->SetBorderStyle(styleLeft, styleRight, styleTop, styleBottom);
        return;
    }
    if (args->IsNumber()) {
        auto borderStyle = ConvertBorderStyle(args->ToNumber<int32_t>());
        ViewAbstractModel::GetInstance()->SetBorderStyle(borderStyle);
        return;
    }
    ViewAbstractModel::GetInstance()->SetBorderStyle(BorderStyle::SOLID);
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
    SysOptions sysOptions;
    sysOptions.disableSystemAdaptation = false;
    if (info.Length() > NUM2 && info[NUM2]->IsObject()) {
        JSRef<JSObject> jsSysOptions = JSRef<JSObject>::Cast(info[NUM2]);
        ParseSysOptions(jsSysOptions, sysOptions);
    }
    CalcDimension dimensionRadius(blur, DimensionUnit::PX);
    ViewAbstractModel::GetInstance()->SetFrontBlur(dimensionRadius, blurOption, sysOptions);
    info.SetReturnValue(info.This());
}

void JSViewAbstract::JsMotionBlur(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }
    MotionBlurOption option;
    double x = 0.0;
    double y = 0.0;
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSVal> jsAnchor = jsObj->GetProperty("anchor");
    if (!jsAnchor->IsNull() && !jsAnchor->IsUndefined() && jsAnchor->IsObject()) {
        JSRef<JSObject> jsAnchorObj = JSRef<JSObject>::Cast(jsAnchor);
        ParseJsDouble(jsAnchorObj->GetProperty("x"), x);
        ParseJsDouble(jsAnchorObj->GetProperty("y"), y);
    }
    double radius = 0.0;
    if (!ParseJsDouble(jsObj->GetProperty("radius"), radius) || LessNotEqual(radius, 0.0)) {
        radius = 0.0;
    }
    if (LessNotEqual(x, 0.0)) {
        x = 0.0;
    }
    if (LessNotEqual(y, 0.0)) {
        y = 0.0;
    }
    option.radius = radius;
    option.anchor.x = std::clamp(x, 0.0, 1.0);
    option.anchor.y = std::clamp(y, 0.0, 1.0);
    ViewAbstractModel::GetInstance()->SetMotionBlur(option);
}

void JSViewAbstract::JsColorBlend(const JSCallbackInfo& info)
{
    ViewAbstractModel::GetInstance()->RemoveResObj("viewAbstract.colorBlend");
    Color colorBlend;
    if (info[0]->IsUndefined()) {
        colorBlend = Color::TRANSPARENT;
        SetColorBlend(colorBlend);
        return;
    }
    if (!SystemProperties::ConfigChangePerform()) {
        if (!ParseJsColor(info[0], colorBlend)) {
            if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
                colorBlend = Color::TRANSPARENT;
                SetColorBlend(colorBlend);
            }
            return;
        }
        SetColorBlend(colorBlend);
        info.SetReturnValue(info.This());
    } else {
        RefPtr<ResourceObject> colorBlendResObj;
        if (ParseJsColor(info[0], colorBlend, colorBlendResObj) && !colorBlendResObj) {
            SetColorBlend(colorBlend);
            info.SetReturnValue(info.This());
            return;
        }
        if (colorBlendResObj) {
            ViewAbstractModel::GetInstance()->CreateWithColorBlendResourceObj(colorBlendResObj);
            info.SetReturnValue(info.This());
        } else {
            if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
                colorBlend = Color::TRANSPARENT;
                SetColorBlend(colorBlend);
            }
        }
    }
}

void JSViewAbstract::JsUseEffect(const JSCallbackInfo& info)
{
    if (info[0]->IsBoolean()) {
        auto effectType = EffectType::DEFAULT;
        if (info.Length() == 2 && info[1]->IsNumber()) {
            effectType = static_cast<EffectType>(info[1]->ToNumber<int32_t>());
            if (effectType < EffectType::DEFAULT || effectType > EffectType::WINDOW_EFFECT) {
                effectType = EffectType::DEFAULT;
            }
        }
        ViewAbstractModel::GetInstance()->SetUseEffect(info[0]->ToBoolean(), effectType);
    }
}

void JSViewAbstract::JsUseShadowBatching(const JSCallbackInfo& info)
{
    if (info[0]->IsBoolean()) {
        ViewAbstractModel::GetInstance()->SetUseShadowBatching(info[0]->ToBoolean());
    } else if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        ViewAbstractModel::GetInstance()->SetUseShadowBatching(false);
    }
}

void JSViewAbstract::JsBackdropBlur(const JSCallbackInfo& info)
{
    if (info.Length() == 0) {
        return;
    }
    double blur = 0.0;
    BlurOption blurOption;
    if (!ParseJsDouble(info[0], blur)) {
        if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            return;
        }
    }
    CalcDimension dimensionRadius(blur, DimensionUnit::PX);
    if (info.Length() > 1 && info[1]->IsObject()) {
        JSRef<JSObject> jsBlurOption = JSRef<JSObject>::Cast(info[1]);
        ParseBlurOption(jsBlurOption, blurOption);
    }
    SysOptions sysOptions;
    sysOptions.disableSystemAdaptation = false;
    if (info.Length() > NUM2 && info[NUM2]->IsObject()) {
        JSRef<JSObject> jsSysOptions = JSRef<JSObject>::Cast(info[NUM2]);
        ParseSysOptions(jsSysOptions, sysOptions);
    }
    ViewAbstractModel::GetInstance()->SetBackdropBlur(dimensionRadius, blurOption, sysOptions);
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
    double rate = 0.0;
    double lightUpDegree = 0.0;
    if (info[0]->IsObject()) {
        JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);
        ParseJsDouble(jsObj->GetProperty("rate"), rate);
        ParseJsDouble(jsObj->GetProperty("lightUpDegree"), lightUpDegree);
    }
    SetDynamicLightUp(rate, lightUpDegree);
}

void JSViewAbstract::JsBackgroundBrightnessInternal(const JSCallbackInfo& info)
{
    if (info.Length() == 0) {
        return;
    }
    BrightnessOption option;
    if (info[0]->IsObject()) {
        JSRef<JSObject> jsOption = JSRef<JSObject>::Cast(info[0]);
        ParseBrightnessOption(jsOption, option);
    }
    SetBgDynamicBrightness(option);
}

void JSViewAbstract::JsForegroundBrightness(const JSCallbackInfo& info)
{
    if (info.Length() == 0) {
        return;
    }
    BrightnessOption option;
    if (info[0]->IsObject()) {
        JSRef<JSObject> jsOption = JSRef<JSObject>::Cast(info[0]);
        ParseBrightnessOption(jsOption, option);
    }
    SetFgDynamicBrightness(option);
}

void JSViewAbstract::JsWindowBlur(const JSCallbackInfo& info)
{
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::OBJECT };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("JsWindowBlur", jsVal, checkList)) {
        return;
    }

    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsVal);
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

bool JSViewAbstract::ParseDollarResource(const JSRef<JSVal>& jsValue, std::string& targetModule, ResourceType& resType,
    std::string& resName, bool isParseType)
{
    if (!jsValue->IsString()) {
        return false;
    }
    std::string resPath = jsValue->ToString();
    std::smatch results;
    std::regex tokenRegex(RESOURCE_TOKEN_PATTERN);
    if (!std::regex_match(resPath, results, tokenRegex)) {
        return false;
    }
    targetModule = results[1];
    if (isParseType && !ConvertResourceType(results[2], resType)) {
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
    std::string bundleName;
    std::string moduleName;
    int32_t resId = -1;
    CompleteResourceObjectInner(jsObj, bundleName, moduleName, resId);
}

void JSViewAbstract::CompleteResourceObjectWithBundleName(
    JSRef<JSObject>& jsObj, std::string& bundleName, std::string& moduleName, int32_t& resId)
{
    CompleteResourceObjectInner(jsObj, bundleName, moduleName, resId);
}

void JSViewAbstract::CompleteResourceObjectInner(
    JSRef<JSObject>& jsObj, std::string& bundleName, std::string& moduleName, int32_t& resIdValue)
{
    // dynamic $r raw input format is
    // {"id":"app.xxx.xxx", "params":[], "bundleName":"xxx", "moduleName":"xxx"}
    JSRef<JSVal> resId = jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::ID));
    ResourceType resType;

    std::string targetModule;
    std::string resName;
    if (resId->IsString()) {
        JSRef<JSVal> type = jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::TYPE));
        int32_t typeNum = -1;
        if (type->IsNumber()) {
            typeNum = type->ToNumber<int32_t>();
        }
        if (!ParseDollarResource(resId, targetModule, resType, resName, typeNum == UNKNOWN_RESOURCE_TYPE)) {
            return;
        }
        CompleteResourceObjectFromId(type, jsObj, resType, resName);
    } else if (resId->IsNumber()) {
        resIdValue = resId->ToNumber<int32_t>();
        if (resIdValue == -1) {
            CompleteResourceObjectFromParams(resIdValue, jsObj, targetModule, resType, resName);
        }
    }

    JSViewAbstract::GetJsMediaBundleInfo(jsObj, bundleName, moduleName);
    if ((bundleName.empty() && !moduleName.empty()) || bundleName == DEFAULT_HAR_BUNDLE_NAME) {
        bundleName = GetBundleNameFromContainer();
        jsObj->SetProperty<std::string>(static_cast<int32_t>(ArkUIIndex::BUNDLE_NAME), bundleName);
    }
    if (moduleName == DEFAULT_HAR_MODULE_NAME) {
        moduleName = GetModuleNameFromContainer();
        jsObj->SetProperty<std::string>(static_cast<int32_t>(ArkUIIndex::MODULE_NAME), moduleName);
    }
}

bool JSViewAbstract::ParseJsDimensionNG(const JSRef<JSVal>& jsValue, CalcDimension& result,
    DimensionUnit defaultUnit, bool isSupportPercent)
{
    RefPtr<ResourceObject> resObj;
    return ParseJsDimensionNG(jsValue, result, defaultUnit, resObj, isSupportPercent);
}

bool JSViewAbstract::ParseJsDimensionNG(const JSRef<JSVal>& jsValue, CalcDimension& result,
    DimensionUnit defaultUnit, RefPtr<ResourceObject>& resObj, bool isSupportPercent)
{
    if (jsValue->IsNumber()) {
        result = CalcDimension(jsValue->ToNumber<double>(), defaultUnit);
        return true;
    }
    if (jsValue->IsString()) {
        auto value = jsValue->ToString();
        if (!isSupportPercent && value.back() == '%') {
            return false;
        }
        return StringUtils::StringToCalcDimensionNG(value, result, false, defaultUnit);
    }
    if (jsValue->IsObject()) {
        JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
        CompleteResourceObject(jsObj);
        JSRef<JSVal> resId = jsObj->GetProperty("id");
        if (!resId->IsNumber()) {
            return false;
        }
        auto resType = jsObj->GetPropertyValue<int32_t>("type", UNKNOWN_RESOURCE_TYPE);
        if (resType == UNKNOWN_RESOURCE_TYPE) {
            return false;
        }
        resObj = SystemProperties::ConfigChangePerform() ? GetResourceObject(jsObj) :
            GetResourceObjectByBundleAndModule(jsObj);
        auto resourceWrapper = CreateResourceWrapper(jsObj, resObj);
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
            if (resType == static_cast<int32_t>(ResourceType::STRING)) {
                auto value = resourceWrapper->GetStringByName(param->ToString());
                return StringUtils::StringToCalcDimensionNG(value, result, false, defaultUnit);
            }
            if (resType == static_cast<int32_t>(ResourceType::INTEGER)) {
                auto value = std::to_string(resourceWrapper->GetIntByName(param->ToString()));
                StringUtils::StringToDimensionWithUnitNG(value, result, defaultUnit);
                return true;
            }
            result = resourceWrapper->GetDimensionByName(param->ToString());
            return true;
        }
        if (resType == static_cast<int32_t>(ResourceType::STRING)) {
            auto value = resourceWrapper->GetString(resId->ToNumber<uint32_t>());
            return StringUtils::StringToCalcDimensionNG(value, result, false, defaultUnit);
        }
        if (resType == static_cast<int32_t>(ResourceType::INTEGER)) {
            auto value = std::to_string(resourceWrapper->GetInt(resId->ToNumber<uint32_t>()));
            StringUtils::StringToDimensionWithUnitNG(value, result, defaultUnit);
            return true;
        }
        if (resType == static_cast<int32_t>(ResourceType::FLOAT)) {
            result = resourceWrapper->GetDimension(resId->ToNumber<uint32_t>()); // float return true pixel value
            return true;
        }
    }
    return false;
}

bool JSViewAbstract::ParseJsLengthNG(
    const JSRef<JSVal>& jsValue, NG::CalcLength& result, DimensionUnit defaultUnit, bool isSupportPercent)
{
    RefPtr<ResourceObject> resourceObj;
    return ParseJsLengthNG(jsValue, result, defaultUnit, resourceObj, isSupportPercent);
}

bool JSViewAbstract::ParseJsLengthNG(const JSRef<JSVal>& jsValue, NG::CalcLength& result, DimensionUnit defaultUnit,
    RefPtr<ResourceObject>& resourceObj, bool isSupportPercent)
{
    if (jsValue->IsNumber()) {
        if (std::isnan(jsValue->ToNumber<double>())) {
            return false;
        }
        result = NG::CalcLength(jsValue->ToNumber<double>(), defaultUnit);
        return true;
    } else if (jsValue->IsObject()) {
        JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
        JSRef<JSVal> value = jsObj->GetProperty("value");
        if (value->IsNull() || (value->IsNumber() && std::isnan(value->ToNumber<double>())) || value->IsUndefined()) {
            return false;
        }
        DimensionUnit unit = defaultUnit;
        JSRef<JSVal> jsUnit = jsObj->GetProperty("unit");
        if (jsUnit->IsNumber()) {
            if (!isSupportPercent && jsUnit->ToNumber<int32_t>() == static_cast<int32_t>(DimensionUnit::PERCENT)) {
                return false;
            }
            unit = static_cast<DimensionUnit>(jsUnit->ToNumber<int32_t>());
        }
        result = NG::CalcLength(value->ToNumber<double>(), unit);
        auto jsRes = jsObj->GetProperty("res");
        if (SystemProperties::ConfigChangePerform() && !jsRes->IsUndefined() &&
            !jsRes->IsNull() && jsRes->IsObject()) {
            JSRef<JSObject> resObj = JSRef<JSObject>::Cast(jsRes);
            JSViewAbstract::CompleteResourceObject(resObj);
            resourceObj = JSViewAbstract::GetResourceObject(resObj);
        }
        return true;
    }

    return false;
}

bool JSViewAbstract::ParseJsLengthVpNG(const JSRef<JSVal>& jsValue, NG::CalcLength& result, bool isSupportPercent)
{
    RefPtr<ResourceObject> resObj;
    return ParseJsLengthNG(jsValue, result, DimensionUnit::VP, resObj, isSupportPercent);
}

bool JSViewAbstract::ParseJsLengthVpNG(const JSRef<JSVal>& jsValue, NG::CalcLength& result,
    RefPtr<ResourceObject>& resObj, bool isSupportPercent)
{
    // 'vp' -> the value varies with pixel density of device.
    return ParseJsLengthNG(jsValue, result, DimensionUnit::VP, resObj, isSupportPercent);
}

bool JSViewAbstract::ParseJsDimension(const JSRef<JSVal>& jsValue, CalcDimension& result, DimensionUnit defaultUnit)
{
    RefPtr<ResourceObject> resObj;
    return ParseJsDimension(jsValue, result, defaultUnit, resObj);
}

bool JSViewAbstract::ParseJsDimensionByNameInternal(const JSRef<JSObject>& jsObj, CalcDimension& result,
    DimensionUnit defaultUnit, RefPtr<ResourceWrapper>& resourceWrapper, int32_t resType)
{
    if (!IsGetResourceByName(jsObj)) {
        return false;
    }
    JSRef<JSVal> args = jsObj->GetProperty("params");
    if (!args->IsArray()) {
        return false;
    }
    JSRef<JSArray> params = JSRef<JSArray>::Cast(args);
    auto param = params->GetValueAt(0);
    if (resType == static_cast<int32_t>(ResourceType::STRING)) {
        auto value = resourceWrapper->GetStringByName(param->ToString());
        result = StringUtils::StringToCalcDimension(value, false, defaultUnit);
        return true;
    }
    if (resType == static_cast<int32_t>(ResourceType::INTEGER)) {
        auto value = std::to_string(resourceWrapper->GetIntByName(param->ToString()));
        result = StringUtils::StringToDimensionWithUnit(value, defaultUnit);
        return true;
    }
    result = resourceWrapper->GetDimensionByName(param->ToString());
    return true;
}

bool JSViewAbstract::ParseJsDimension(const JSRef<JSVal>& jsValue, CalcDimension& result, DimensionUnit defaultUnit,
    RefPtr<ResourceObject>& resObj)
{
    if (jsValue->IsNumber()) {
        result = CalcDimension(jsValue->ToNumber<double>(), defaultUnit);
        return true;
    }
    if (jsValue->IsString()) {
        result = StringUtils::StringToCalcDimension(jsValue->ToString(), false, defaultUnit);
        return true;
    }
    if (!jsValue->IsObject()) {
        return false;
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    CompleteResourceObject(jsObj);
    JSRef<JSVal> resId = jsObj->GetProperty("id");
    if (!resId->IsNumber()) {
        return false;
    }
    resObj = SystemProperties::ConfigChangePerform() ? GetResourceObject(jsObj) :
        GetResourceObjectByBundleAndModule(jsObj);
    auto resourceWrapper = CreateResourceWrapper(jsObj, resObj);
    if (!resourceWrapper) {
        return false;
    }
    auto resIdNum = resId->ToNumber<int32_t>();
    int32_t resType = jsObj->GetPropertyValue<int32_t>("type", UNKNOWN_RESOURCE_TYPE);
    if (resType == UNKNOWN_RESOURCE_TYPE) {
        return false;
    }
    if (resIdNum == -1) {
        return ParseJsDimensionByNameInternal(jsObj, result, defaultUnit, resourceWrapper, resType);
    }
    if (resType == static_cast<int32_t>(ResourceType::STRING)) {
        auto value = resourceWrapper->GetString(resId->ToNumber<uint32_t>());
        result = StringUtils::StringToCalcDimension(value, false, defaultUnit);
        return true;
    }
    if (resType == static_cast<int32_t>(ResourceType::INTEGER)) {
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

bool JSViewAbstract::ParseJsDimensionVpNG(const JSRef<JSVal>& jsValue, CalcDimension& result,
    RefPtr<ResourceObject>& resObj, bool isSupportPercent)
{
    // 'vp' -> the value varies with pixel density of device.
    return ParseJsDimensionNG(jsValue, result, DimensionUnit::VP, resObj, isSupportPercent);
}

bool JSViewAbstract::ParseJsLengthMetricsVp(const JSRef<JSObject>& jsObj, CalcDimension& result)
{
    RefPtr<ResourceObject> resourceObj;
    return ParseJsLengthMetricsVpWithResObj(jsObj, result, resourceObj);
}

bool JSViewAbstract::ParseJsLengthMetricsVpWithResObj(const JSRef<JSObject>& jsObj, CalcDimension& result,
    RefPtr<ResourceObject>& resourceObj)
{
    auto value = jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::VALUE));
    if (!value->IsNumber()) {
        return false;
    }
    auto unit = DimensionUnit::VP;
    auto jsUnit = jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::UNIT));
    if (jsUnit->IsNumber()) {
        unit = static_cast<DimensionUnit>(jsUnit->ToNumber<int32_t>());
    }
    CalcDimension dimension(value->ToNumber<double>(), unit);
    result = dimension;
    auto jsRes = jsObj->GetProperty("res");
    if (SystemProperties::ConfigChangePerform() && !jsRes->IsUndefined() &&
        !jsRes->IsNull() && jsRes->IsObject()) {
        JSRef<JSObject> resObj = JSRef<JSObject>::Cast(jsRes);
        JSViewAbstract::CompleteResourceObject(resObj);
        resourceObj = JSViewAbstract::GetResourceObject(resObj);
    }
    return true;
}

bool JSViewAbstract::ParseJsDimensionVp(const JSRef<JSVal>& jsValue, CalcDimension& result)
{
    RefPtr<ResourceObject> resObj;
    // 'vp' -> the value varies with pixel density of device.
    return ParseJsDimension(jsValue, result, DimensionUnit::VP, resObj);
}

bool JSViewAbstract::ParseJsDimensionVp(const JSRef<JSVal>& jsValue, CalcDimension& result,
    RefPtr<ResourceObject>& resObj)
{
    // 'vp' -> the value varies with pixel density of device.
    return ParseJsDimension(jsValue, result, DimensionUnit::VP, resObj);
}

bool JSViewAbstract::ParseJsDimensionFp(const JSRef<JSVal>& jsValue, CalcDimension& result)
{
    RefPtr<ResourceObject> resObj;
    // the 'fp' unit is used for text scenes.
    return ParseJsDimension(jsValue, result, DimensionUnit::FP, resObj);
}

bool JSViewAbstract::ParseJsDimensionFp(const JSRef<JSVal>& jsValue, CalcDimension& result,
    RefPtr<ResourceObject>& resObj)
{
    // the 'fp' unit is used for text scenes.
    return ParseJsDimension(jsValue, result, DimensionUnit::FP, resObj);
}

bool JSViewAbstract::ParseJsDimensionFpNG(const JSRef<JSVal>& jsValue, CalcDimension& result, bool isSupportPercent)
{
    // the 'fp' unit is used for text scenes.
    return ParseJsDimensionNG(jsValue, result, DimensionUnit::FP, isSupportPercent);
}

bool JSViewAbstract::ParseJsDimensionFpNG(const JSRef<JSVal>& jsValue, CalcDimension& result,
    RefPtr<ResourceObject>& resObj, bool isSupportPercent)
{
    // the 'fp' unit is used for text scenes.
    return ParseJsDimensionNG(jsValue, result, DimensionUnit::FP, resObj, isSupportPercent);
}

bool JSViewAbstract::ParseJsDimensionPx(const JSRef<JSVal>& jsValue, CalcDimension& result)
{
    RefPtr<ResourceObject> resObj;
    return ParseJsDimension(jsValue, result, DimensionUnit::PX, resObj);
}

bool JSViewAbstract::ParseJsDimensionPx(const JSRef<JSVal>& jsValue, CalcDimension& result,
    RefPtr<ResourceObject>& resObj)
{
    return ParseJsDimension(jsValue, result, DimensionUnit::PX, resObj);
}

bool JSViewAbstract::ParseColorMetricsToColor(const JSRef<JSVal>& jsValue, Color& result)
{
    RefPtr<ResourceObject> resObj;
    return ParseColorMetricsToColor(jsValue, result, resObj);
}

bool JSViewAbstract::ParseColorMetricsToColor(
    const JSRef<JSVal>& jsValue, Color& result, RefPtr<ResourceObject>& resObj)
{
    if (!jsValue->IsObject()) {
        return false;
    }
    auto colorObj = JSRef<JSObject>::Cast(jsValue);
    auto toNumericProp = colorObj->GetProperty("toNumeric");
    auto colorSpaceProp = colorObj->GetProperty("getColorSpace");
    auto jsRes = colorObj->GetProperty("res_");
    if (SystemProperties::ConfigChangePerform() && !jsRes->IsUndefined() && !jsRes->IsNull() && jsRes->IsObject()) {
        JSRef<JSObject> jsResObj = JSRef<JSObject>::Cast(jsRes);
        JSViewAbstract::CompleteResourceObject(jsResObj);
        resObj = JSViewAbstract::GetResourceObject(jsResObj);
    }
    if (toNumericProp->IsFunction() && colorSpaceProp->IsFunction()) {
        auto colorVal = JSRef<JSFunc>::Cast(toNumericProp)->Call(colorObj, 0, nullptr);
        result.SetValue(colorVal->ToNumber<uint32_t>());

        auto resourceIdProp = colorObj->GetProperty("getResourceId");
        if (resourceIdProp->IsFunction()) {
            auto resourceIdVal = JSRef<JSFunc>::Cast(resourceIdProp)->Call(colorObj, 0, nullptr);
            result.SetResourceId(resourceIdVal->ToNumber<uint32_t>());
        }

        auto colorSpaceVal = JSRef<JSFunc>::Cast(colorSpaceProp)->Call(colorObj, 0, nullptr);
        if (colorSpaceVal->IsNumber() &&
            colorSpaceVal->ToNumber<uint32_t>() == static_cast<uint32_t>(ColorSpace::DISPLAY_P3)) {
            result.SetColorSpace(ColorSpace::DISPLAY_P3);
        } else {
            result.SetColorSpace(ColorSpace::SRGB);
        }

        return true;
    }
    return false;
}

bool JSViewAbstract::ParseLengthMetricsToDimension(const JSRef<JSVal>& jsValue, CalcDimension& result)
{
    RefPtr<ResourceObject> resObj;
    return ParseLengthMetricsToDimension(jsValue, result, resObj);
}

bool JSViewAbstract::ParseLengthMetricsToDimension(
    const JSRef<JSVal>& jsValue, CalcDimension& result, RefPtr<ResourceObject>& resourceObj)
{
    if (jsValue->IsNumber()) {
        result = CalcDimension(jsValue->ToNumber<double>(), DimensionUnit::FP);
        return true;
    }
    if (jsValue->IsString()) {
        auto value = jsValue->ToString();
        return StringUtils::StringToCalcDimensionNG(value, result, false, DimensionUnit::FP);
    }
    if (jsValue->IsObject()) {
        auto jsObj = JSRef<JSObject>::Cast(jsValue);
        auto valObj = jsObj->GetProperty("value");
        if (valObj->IsUndefined() || valObj->IsNull()) {
            return false;
        }
        double value = valObj->ToNumber<double>();
        auto unit = static_cast<DimensionUnit>(jsObj->GetProperty("unit")->ToNumber<int32_t>());
        result = CalcDimension(value, unit);
        auto jsRes = jsObj->GetProperty("res");
        if (SystemProperties::ConfigChangePerform() && !jsRes->IsUndefined() &&
            !jsRes->IsNull() && jsRes->IsObject()) {
            JSRef<JSObject> resObj = JSRef<JSObject>::Cast(jsRes);
            JSViewAbstract::CompleteResourceObject(resObj);
            resourceObj = JSViewAbstract::GetResourceObject(resObj);
        }
        return true;
    }
    return false;
}

bool JSViewAbstract::ParseLengthMetricsToPositiveDimension(const JSRef<JSVal>& jsValue, CalcDimension& result)
{
    return ParseLengthMetricsToDimension(jsValue, result) ? GreatOrEqual(result.Value(), 0.0f) : false;
}

bool JSViewAbstract::ParseLengthMetricsToPositiveDimension(
    const JSRef<JSVal>& jsValue, CalcDimension& result, RefPtr<ResourceObject>& resObj)
{
    return ParseLengthMetricsToDimension(jsValue, result, resObj) ? GreatOrEqual(result.Value(), 0.0f) : false;
}

bool JSViewAbstract::ParseResourceToDouble(const JSRef<JSVal>& jsValue, double& result,
    RefPtr<ResourceObject>& resObj)
{
    if (!jsValue->IsObject()) {
        return false;
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    CompleteResourceObject(jsObj);
    if (jsObj->IsEmpty()) {
        return false;
    }
    JSRef<JSVal> id = jsObj->GetProperty("id");
    if (!id->IsNumber()) {
        return false;
    }

    auto resId = id->ToNumber<int32_t>();
    int32_t resType = jsObj->GetPropertyValue<int32_t>("type", UNKNOWN_RESOURCE_TYPE);
    if (resType == UNKNOWN_RESOURCE_TYPE) {
        return false;
    }

    resObj = SystemProperties::ConfigChangePerform() ? GetResourceObject(jsObj) :
        GetResourceObjectByBundleAndModule(jsObj);
    auto resourceWrapper = CreateResourceWrapper(jsObj, resObj);
    if (!resourceWrapper) {
        return false;
    }

    if (resId == -1) {
        return ParseResourceToDoubleByName(jsObj, resType, resourceWrapper, result);
    }
    return ParseResourceToDoubleById(resId, resType, resourceWrapper, result);
}

bool JSViewAbstract::ParseResourceToDoubleByName(
    const JSRef<JSObject>& jsObj, int32_t resType, const RefPtr<ResourceWrapper>& resourceWrapper, double& result)
{
    if (!IsGetResourceByName(jsObj)) {
        return false;
    }
    JSRef<JSVal> args = jsObj->GetProperty("params");
    if (!args->IsArray()) {
        return false;
    }
    JSRef<JSArray> params = JSRef<JSArray>::Cast(args);
    auto param = params->GetValueAt(0);
    if (resType == static_cast<int32_t>(ResourceType::STRING)) {
        auto numberString = resourceWrapper->GetStringByName(param->ToString());
        return StringUtils::StringToDouble(numberString, result);
    }
    if (resType == static_cast<int32_t>(ResourceType::INTEGER)) {
        result = resourceWrapper->GetIntByName(param->ToString());
        return true;
    }
    if (resType == static_cast<int32_t>(ResourceType::FLOAT)) {
        result = resourceWrapper->GetDoubleByName(param->ToString());
        return true;
    }
    return false;
}

bool JSViewAbstract::ParseResourceToDoubleById(
    int32_t resId, int32_t resType, const RefPtr<ResourceWrapper>& resourceWrapper, double& result)
{
    if (resType == static_cast<int32_t>(ResourceType::STRING)) {
        auto numberString = resourceWrapper->GetString(resId);
        return StringUtils::StringToDouble(numberString, result);
    }
    if (resType == static_cast<int32_t>(ResourceType::INTEGER)) {
        result = resourceWrapper->GetInt(resId);
        return true;
    }
    if (resType == static_cast<int32_t>(ResourceType::FLOAT)) {
        result = resourceWrapper->GetDouble(resId);
        return true;
    }
    return false;
}

bool JSViewAbstract::ParseJsDouble(const JSRef<JSVal>& jsValue, double& result)
{
    RefPtr<ResourceObject> resObj;
    return ParseJsDouble(jsValue, result, resObj);
}

bool JSViewAbstract::ParseJsDouble(const JSRef<JSVal>& jsValue, double& result,
    RefPtr<ResourceObject>& resObj)
{
    if (jsValue->IsNumber()) {
        result = jsValue->ToNumber<double>();
        return true;
    }
    if (jsValue->IsString()) {
        return StringUtils::StringToDouble(jsValue->ToString(), result);
    }
    if (jsValue->IsObject()) {
        return ParseResourceToDouble(jsValue, result, resObj);
    }
    return false;
}

bool JSViewAbstract::ParseJsInt32(const JSRef<JSVal>& jsValue, int32_t& result)
{
    if (jsValue->IsNumber()) {
        result = jsValue->ToNumber<int32_t>();
        return true;
    }
    if (jsValue->IsString()) {
        result = StringUtils::StringToInt(jsValue->ToString());
        return true;
    }
    if (!jsValue->IsObject()) {
        return false;
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    CompleteResourceObject(jsObj);
    JSRef<JSVal> resId = jsObj->GetProperty("id");
    if (!resId->IsNumber()) {
        return false;
    }

    auto resourceObject = GetResourceObjectByBundleAndModule(jsObj);
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

bool JSViewAbstract::ParseJsColorFromResource(const JSRef<JSVal>& jsValue, Color& result,
    RefPtr<ResourceObject>& resObj)
{
    if (!jsValue->IsObject()) {
        return false;
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    CompleteResourceObject(jsObj);

    auto ok = JSViewAbstract::ParseJsObjColorFromResource(jsObj, result, resObj);
    if (ok) {
        JSRef<JSVal> jsOpacityRatio = jsObj->GetProperty("opacityRatio");
        if (jsOpacityRatio->IsNumber()) {
            double opacityRatio = jsOpacityRatio->ToNumber<double>();
            result = result.BlendOpacity(opacityRatio);
        }
    }
    return ok;
}

bool JSViewAbstract::ParseJsObjColorFromResource(const JSRef<JSObject> &jsObj, Color& result,
    RefPtr<ResourceObject>& resObj)
{
    JSRef<JSVal> resId = jsObj->GetProperty("id");
    if (!resId->IsNumber()) {
        return false;
    }

    resObj = SystemProperties::ConfigChangePerform() ? GetResourceObject(jsObj) :
        GetResourceObjectByBundleAndModule(jsObj);
    auto resourceWrapper = CreateResourceWrapper(jsObj, resObj);
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

    auto type = jsObj->GetPropertyValue<int32_t>("type", UNKNOWN_RESOURCE_TYPE);
    if (type == static_cast<int32_t>(ResourceType::STRING)) {
        auto value = resourceWrapper->GetString(resId->ToNumber<uint32_t>());
        return Color::ParseColorString(value, result);
    }
    if (type == static_cast<int32_t>(ResourceType::INTEGER)) {
        auto value = resourceWrapper->GetInt(resId->ToNumber<uint32_t>());
        result = Color(ColorAlphaAdapt(value));
        return true;
    }
    if (type == static_cast<int32_t>(ResourceType::COLOR)) {
        result = resourceWrapper->GetColor(resId->ToNumber<uint32_t>());
        result.SetResourceId(resId->ToNumber<uint32_t>());
        return true;
    }
    return false;
}

bool JSViewAbstract::CheckDarkResource(const RefPtr<ResourceObject>& resObj)
{
    if (!SystemProperties::GetResourceDecoupling() || !resObj) {
        return false;
    }
    auto resourceAdapter = ResourceManager::GetInstance().GetOrCreateResourceAdapter(resObj);
    CHECK_NULL_RETURN(resourceAdapter, false);

    int32_t resId = resObj->GetId();
    bool hasDarkRes = false;
    auto params = resObj->GetParams();
    if (resId == -1 && (params.size() > 0)) {
        hasDarkRes = resourceAdapter->ExistDarkResByName(params[params.size() - 1].value.value(),
            std::to_string(resObj->GetType()));
    } else {
        hasDarkRes = resourceAdapter->ExistDarkResById(std::to_string(resId));
    }
    return hasDarkRes;
}

void JSViewAbstract::CompleteResourceObjectFromColor(RefPtr<ResourceObject>& resObj,
    Color& color, bool state)
{
    if (!state || !SystemProperties::ConfigChangePerform()) {
        return;
    }

    auto node = NG::ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(node);

    auto instanceId = Container::CurrentIdSafely();
    auto nodeTag = node->GetTag();
    auto invertFunc = ColorInverter::GetInstance().GetInvertFunc(instanceId, nodeTag);
    CHECK_NULL_VOID(invertFunc);

    auto localColorMode = node->GetLocalColorMode();
    if (localColorMode == ColorMode::LIGHT) {
        resObj = nullptr;
        return;
    }

    auto colorMode = Container::CurrentColorMode();
    bool hasDarkRes = CheckDarkResource(resObj);
    if ((colorMode == ColorMode::DARK || localColorMode == ColorMode::DARK) && (!resObj || !hasDarkRes)) {
        color = Color(invertFunc(color.GetValue()));
    }
    if (!resObj) {
        resObj = AceType::MakeRefPtr<ResourceObject>();
        resObj->SetIsResource(false);
        resObj->SetInstanceId(instanceId);
    }
    resObj->SetNodeTag(nodeTag);
    resObj->SetColorMode(colorMode);
    resObj->SetHasDarkRes(hasDarkRes);
    resObj->SetColor(color);
}

bool JSViewAbstract::ParseJsColor(const JSRef<JSVal>& jsValue, Color& result)
{
    RefPtr<ResourceObject> resObj;
    return ParseJsColor(jsValue, result, resObj);
}

bool JSViewAbstract::ParseJsColor(const JSRef<JSVal>& jsValue, Color& result,
    RefPtr<ResourceObject>& resObj)
{
    bool state = false;
    if (jsValue->IsNumber()) {
        result = Color(ColorAlphaAdapt(jsValue->ToNumber<uint32_t>()));
        CompleteResourceObjectFromColor(resObj, result, true);
        return true;
    }
    if (jsValue->IsString()) {
        state = Color::ParseColorString(jsValue->ToString(), result);
        CompleteResourceObjectFromColor(resObj, result, state);
        return state;
    }
    if (jsValue->IsObject()) {
        if (ParseColorMetricsToColor(jsValue, result, resObj)) {
            CompleteResourceObjectFromColor(resObj, result, true);
            return true;
        }
        state = ParseJsColorFromResource(jsValue, result, resObj);
        CompleteResourceObjectFromColor(resObj, result, state);
        return state;
    }
    return state;
}

bool JSViewAbstract::ParseJsColor(const JSRef<JSVal>& jsValue, Color& result, const Color& defaultColor)
{
    RefPtr<ResourceObject> resObj;
    return ParseJsColor(jsValue, result, defaultColor, resObj);
}

bool JSViewAbstract::ParseJsColor(const JSRef<JSVal>& jsValue, Color& result,
    const Color& defaultColor, RefPtr<ResourceObject>& resObj)
{
    bool state = false;
    if (jsValue->IsNumber()) {
        result = Color(ColorAlphaAdapt(jsValue->ToNumber<uint32_t>()));
        CompleteResourceObjectFromColor(resObj, result, true);
        return true;
    }
    if (jsValue->IsString()) {
        state = Color::ParseColorString(jsValue->ToString(), result, defaultColor);
        CompleteResourceObjectFromColor(resObj, result, state);
        return state;
    }
    if (!jsValue->IsObject()) {
        return state;
    }
    state = ParseJsColorFromResource(jsValue, result, resObj);
    CompleteResourceObjectFromColor(resObj, result, state);
    return state;
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

void JSViewAbstract::ParseJsSymbolCustomFamilyNames(std::vector<std::string>& customFamilyNames,
    const JSRef<JSVal>& jsValue)
{
    if (jsValue->IsNull() || jsValue->IsUndefined()) {
        return;
    }
    if (!jsValue->IsObject()) {
        return;
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    CompleteResourceObject(jsObj);
    JSRef<JSVal> resId = jsObj->GetProperty("id");
    if (resId->IsNull() || !resId->IsNumber()) {
        return;
    }
    auto resourceObject = GetResourceObject(jsObj);
    std::string bundleName = resourceObject->GetBundleName();
    std::string moduleName = resourceObject->GetModuleName();
    auto customSymbolFamilyName = bundleName + "_" + moduleName + CUSTOM_SYMBOL_SUFFIX;
    std::replace(customSymbolFamilyName.begin(), customSymbolFamilyName.end(), '.', '_');
    customFamilyNames.push_back(customSymbolFamilyName);
}

bool JSViewAbstract::CheckResource(RefPtr<ResourceObject> resourceObject, RefPtr<ResourceWrapper> resourceWrapper)
{
    if (!resourceWrapper) {
        return false;
    }
    if (!resourceObject) {
        return false;
    }
    return true;
}

bool JSViewAbstract::CheckCustomSymbolId(RefPtr<ResourceWrapper> resourceWrapper, JSRef<JSVal>& resId,
    std::uint32_t& symbolId)
{
    auto strValue = resourceWrapper->GetString(resId->ToNumber<uint32_t>());
    if (!strValue.empty()) {
        auto customSymbolId = static_cast<uint32_t>(strtol(strValue.c_str(), nullptr, 16));
        symbolId = customSymbolId;
        return true;
    }
    return false;
}

bool JSViewAbstract::ParseJsSymbolId(
    const JSRef<JSVal>& jsValue, std::uint32_t& symbolId, RefPtr<ResourceObject>& symbolResourceObject)
{
    if (jsValue->IsNull() || jsValue->IsUndefined()) {
        symbolId = 0;
        return false;
    }
    if (jsValue->IsNumber()) {
        symbolId = jsValue->ToNumber<uint32_t>();
        return true;
    }
    if (!jsValue->IsObject()) {
        return false;
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    CompleteResourceObject(jsObj);
    JSRef<JSVal> resId = jsObj->GetProperty("id");
    if (resId->IsNull() || !resId->IsNumber()) {
        return false;
    }
    auto resourceObject = GetResourceObject(jsObj);
    auto resourceWrapper = CreateResourceWrapper(jsObj, resourceObject);
    symbolResourceObject = resourceObject;
    if (CheckCustomSymbolId(resourceWrapper, resId, symbolId)) {
        return true;
    }
    if (!CheckResource(resourceObject, resourceWrapper)) {
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
        auto symbol = resourceWrapper->GetSymbolByName(param->ToString().c_str());
        if (!symbol) {
            return false;
        }
        symbolId = symbol;
        return true;
    }

    auto symbol = resourceWrapper->GetSymbolById(resIdNum);
    if (!symbol) {
        return false;
    }
    symbolId = symbol;
    return true;
}

bool JSViewAbstract::ParseJsSymbolColor(const JSRef<JSVal>& jsValue, std::vector<Color>& result,
    bool enableResourceUpdate, std::vector<std::pair<int32_t, RefPtr<ResourceObject>>>& resObjArr)
{
    if (!jsValue->IsArray()) {
        return false;
    }
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
            RefPtr<ResourceObject> resObj;
            ParseJsColorFromResource(value, color, resObj);
            result.emplace_back(color);
            if (enableResourceUpdate && resObj) {
                std::pair<int32_t, RefPtr<ResourceObject>> pair(i, resObj);
                resObjArr.push_back(pair);
            }
        }
    }
    return true;
}

bool JSViewAbstract::ParseJsFontFamilies(const JSRef<JSVal>& jsValue, std::vector<std::string>& result)
{
    RefPtr<ResourceObject> resObj;
    return ParseJsFontFamilies(jsValue, result, resObj);
}

bool JSViewAbstract::ParseJsFontFamilies(const JSRef<JSVal>& jsValue, std::vector<std::string>& result,
    RefPtr<ResourceObject>& resObj)
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

    resObj = SystemProperties::ConfigChangePerform() ? GetResourceObject(jsObj) :
        GetResourceObjectByBundleAndModule(jsObj);
    auto resourceWrapper = CreateResourceWrapper(jsObj, resObj);
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

bool JSViewAbstract::ParseJsStringObj(const JSRef<JSVal>& jsValue, std::string& result,
    RefPtr<ResourceObject>& resObj)
{
    if (!jsValue->IsObject()) {
        return false;
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    CompleteResourceObject(jsObj);
    JSRef<JSVal> resId = jsObj->GetProperty("id");
    if (!resId->IsNumber()) {
        return false;
    }
    auto type = jsObj->GetPropertyValue<int32_t>("type", UNKNOWN_RESOURCE_TYPE);
    if (type == UNKNOWN_RESOURCE_TYPE) {
        return false;
    }
    JSRef<JSVal> args = jsObj->GetProperty("params");
    if (!args->IsArray()) {
        return false;
    }
    resObj = SystemProperties::ConfigChangePerform() ? GetResourceObject(jsObj) :
        GetResourceObjectByBundleAndModule(jsObj);
    auto resourceWrapper = CreateResourceWrapper(jsObj, resObj);
    if (!resourceWrapper) {
        return false;
    }
    JSRef<JSArray> params = JSRef<JSArray>::Cast(args);
    auto resIdNum = resId->ToNumber<int32_t>();
    if (resIdNum == -1) {
        if (!IsGetResourceByName(jsObj)) {
            return false;
        }
        auto param = params->GetValueAt(0);
        if (type == static_cast<int32_t>(ResourceType::STRING)) {
            auto originStr = resourceWrapper->GetStringByName(param->ToString());
            ReplaceHolder(originStr, params, 1);
            result = originStr;
        } else if (type == static_cast<int32_t>(ResourceType::PLURAL)) {
            auto countJsVal = params->GetValueAt(1);
            int count = 0;
            if (!countJsVal->IsNumber()) {
                return false;
            }
            count = countJsVal->ToNumber<int>();
            auto pluralStr = resourceWrapper->GetPluralStringByName(param->ToString(), count);
            ReplaceHolder(pluralStr, params, 2); // params[2] applys pluralStr.
            result = pluralStr;
        } else {
            return false;
        }
        return true;
    }
    if (type == static_cast<int32_t>(ResourceType::STRING)) {
        auto originStr = resourceWrapper->GetString(resId->ToNumber<uint32_t>());
        ReplaceHolder(originStr, params, 0);
        result = originStr;
    } else if (type == static_cast<int32_t>(ResourceType::PLURAL)) {
        auto countJsVal = params->GetValueAt(0);
        int count = 0;
        if (!countJsVal->IsNumber()) {
            return false;
        }
        count = countJsVal->ToNumber<int>();
        auto pluralStr = resourceWrapper->GetPluralString(resId->ToNumber<uint32_t>(), count);
        ReplaceHolder(pluralStr, params, 1);
        result = pluralStr;
    } else if (type == static_cast<int32_t>(ResourceType::FLOAT)) {
        result = std::to_string(resourceWrapper->GetDouble(resId->ToNumber<uint32_t>()));
    } else if (type == static_cast<int32_t>(ResourceType::INTEGER)) {
        result = std::to_string(resourceWrapper->GetInt(resId->ToNumber<uint32_t>()));
    } else {
        return false;
    }
    return true;
}

bool JSViewAbstract::ParseJsString(const JSRef<JSVal>& jsValue, std::string& result)
{
    RefPtr<ResourceObject> resObj;
    return ParseJsString(jsValue, result, resObj);
}

bool JSViewAbstract::ParseJsString(const JSRef<JSVal>& jsValue, std::string& result,
    RefPtr<ResourceObject>& resObj)
{
    if (jsValue->IsString()) {
        result = jsValue->ToString();
        return true;
    }
    return ParseJsStringObj(jsValue, result, resObj);
}

bool JSViewAbstract::ParseJsString(const JSRef<JSVal>& jsValue, std::u16string& result)
{
    RefPtr<ResourceObject> resObj;
    return ParseJsString(jsValue, result, resObj);
}

bool JSViewAbstract::ParseJsString(const JSRef<JSVal>& jsValue, std::u16string& result,
    RefPtr<ResourceObject>& resObj)
{
    std::string u8Result;
    if (jsValue->IsString()) {
        result = jsValue->ToU16String();
        return true;
    }
    bool ret = ParseJsStringObj(jsValue, u8Result, resObj);
    if (ret) {
        result = UtfUtils::Str8DebugToStr16(u8Result);
        return true;
    }
    return false;
}

bool JSViewAbstract::ParseJsMedia(const JSRef<JSVal>& jsValue, std::string& result,
    RefPtr<ResourceObject>& resObj)
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
    return ParseJSMediaInternal(jsObj, result, resObj);
}

bool JSViewAbstract::ParseJsMedia(const JSRef<JSVal>& jsValue, std::string& result)
{
    RefPtr<ResourceObject> resObj;
    return ParseJsMedia(jsValue, result, resObj);
}

bool JSViewAbstract::ParseJsMediaWithBundleName(
    const JSRef<JSVal>& jsValue, std::string& result, std::string& bundleName, std::string& moduleName, int32_t& resId)
{
    RefPtr<ResourceObject> resObj;
    return ParseJsMediaWithBundleName(jsValue, result, bundleName, moduleName, resId, resObj);
}

bool JSViewAbstract::ParseJsMediaWithBundleName(
    const JSRef<JSVal>& jsValue, std::string& result, std::string& bundleName, std::string& moduleName,
    int32_t& resId, RefPtr<ResourceObject>& resObj)
{
    if (!jsValue->IsObject() && !jsValue->IsString()) {
        return JSViewAbstract::GetJsMediaBundleInfo(jsValue, bundleName, moduleName);
    }
    if (jsValue->IsString()) {
        result = jsValue->ToString();
        return JSViewAbstract::GetJsMediaBundleInfo(jsValue, bundleName, moduleName);
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    CompleteResourceObjectWithBundleName(jsObj, bundleName, moduleName, resId);
    return ParseJSMediaInternal(jsObj, result, resObj);
}

bool JSViewAbstract::ParseJSMediaWithRawFile(const JSRef<JSObject>& jsObj, std::string& result,
    RefPtr<ResourceWrapper>& resourceWrapper)
{
    JSRef<JSVal> args = jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::PARAMS));
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

bool JSViewAbstract::ParseJSMediaInternal(const JSRef<JSObject>& jsObj, std::string& result,
    RefPtr<ResourceObject>& resObj)
{
    int32_t type = jsObj->GetPropertyValue<int32_t>(static_cast<int32_t>(ArkUIIndex::TYPE), UNKNOWN_RESOURCE_TYPE);
    JSRef<JSVal> resId = jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::ID));
    if (!resId->IsNull() && type != UNKNOWN_RESOURCE_TYPE && resId->IsNumber()) {
        resObj = SystemProperties::ConfigChangePerform() ? GetResourceObject(jsObj) :
            GetResourceObjectByBundleAndModule(jsObj);
        auto resourceWrapper = CreateResourceWrapper(jsObj, resObj);
        CHECK_NULL_RETURN(resourceWrapper, false);
        if (type == static_cast<int32_t>(ResourceType::RAWFILE)) {
            return JSViewAbstract::ParseJSMediaWithRawFile(jsObj, result, resourceWrapper);
        }
        auto resIdNum = resId->ToNumber<int32_t>();
        if (resIdNum == -1) {
            if (!IsGetResourceByName(jsObj)) {
                return false;
            }
            JSRef<JSVal> args = jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::PARAMS));
            if (!args->IsArray()) {
                return false;
            }
            JSRef<JSArray> params = JSRef<JSArray>::Cast(args);
            auto param = params->GetValueAt(0);
            if (type == static_cast<int32_t>(ResourceType::MEDIA)) {
                result = resourceWrapper->GetMediaPathByName(param->ToString());
                return true;
            }
            if (type == static_cast<int32_t>(ResourceType::STRING)) {
                result = resourceWrapper->GetStringByName(param->ToString());
                return true;
            }
            return false;
        } else if (type == static_cast<int32_t>(ResourceType::MEDIA)) {
            result = resourceWrapper->GetMediaPath(resId->ToNumber<uint32_t>());
            return true;
        } else if (type == static_cast<int32_t>(ResourceType::STRING)) {
            result = resourceWrapper->GetString(resId->ToNumber<uint32_t>());
            return true;
        }
    }
    return false;
}

void JSViewAbstract::SetTabBarSymbolOptionApply(const JSCallbackInfo& info, TabBarSymbol& symbolApply,
    const JSRef<JSVal>& modifierNormalObj, const JSRef<JSVal>& modifierSelectedObj)
{
    auto vm = info.GetVm();
    auto globalObj = JSNApi::GetGlobalObject(vm);
    auto globalFunc = globalObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "applySymbolGlyphModifierToNode"));
    JsiValue jsiValue(globalFunc);
    JsiRef<JsiValue> globalFuncRef = JsiRef<JsiValue>::Make(jsiValue);
    if (!globalFuncRef->IsFunction()) {
        return;
    }
    if (modifierNormalObj->IsUndefined()) {
        symbolApply.onApply = nullptr;
    } else {
        RefPtr<JsFunction> jsFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(globalFuncRef));
        auto onApply = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc),
                           modifierNormal = std::move(modifierNormalObj),
                           modifierSelected = std::move(modifierSelectedObj)](
                           WeakPtr<NG::FrameNode> frameNode, std::string type) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto node = frameNode.Upgrade();
            CHECK_NULL_VOID(node);
            JSRef<JSVal> params[SECOND_INDEX];
            if (type == "normal") {
                params[0] = modifierNormal;
            } else if (!modifierSelected->IsUndefined()) {
                params[0] = modifierSelected;
            }
            params[1] = JSRef<JSVal>::Make(panda::NativePointerRef::New(execCtx.vm_, AceType::RawPtr(node)));
            PipelineContext::SetCallBackNode(node);
            func->ExecuteJS(SECOND_INDEX, params);
        };
        symbolApply.onApply = onApply;
    }
}

bool JSViewAbstract::ParseJsBool(const JSRef<JSVal>& jsValue, bool& result)
{
    RefPtr<ResourceObject> resObj;
    return ParseJsBool(jsValue, result, resObj);
}

bool JSViewAbstract::ParseJsBool(const JSRef<JSVal>& jsValue, bool& result,
    RefPtr<ResourceObject>& resObj)
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
    int32_t resType = jsObj->GetPropertyValue<int32_t>(static_cast<int32_t>(ArkUIIndex::TYPE), UNKNOWN_RESOURCE_TYPE);
    if (resType == UNKNOWN_RESOURCE_TYPE) {
        return false;
    }

    JSRef<JSVal> resId = jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::ID));
    if (!resId->IsNumber()) {
        return false;
    }

    resObj = SystemProperties::ConfigChangePerform() ? GetResourceObject(jsObj) :
        GetResourceObjectByBundleAndModule(jsObj);
    auto resourceWrapper = CreateResourceWrapper(jsObj, resObj);
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
        if (resType == static_cast<int32_t>(ResourceType::BOOLEAN)) {
            result = resourceWrapper->GetBooleanByName(param->ToString());
            return true;
        }
        return false;
    }

    if (resType == static_cast<int32_t>(ResourceType::BOOLEAN)) {
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
    RefPtr<ResourceObject> resObj;
    std::vector<RefPtr<ResourceObject>> resObjArray;
    return ParseJsIntegerArray(jsValue, result, resObj, resObjArray);
}

bool JSViewAbstract::ParseJsIntegerArrayInternal(const JSRef<JSArray>& jsArray, std::vector<uint32_t>& result,
    std::vector<RefPtr<ResourceObject>>& resObjArray)
{
    for (size_t i = 0; i < jsArray->Length(); i++) {
        RefPtr<ResourceObject> resObj;
        JSRef<JSVal> value = jsArray->GetValueAt(i);
        if (value->IsNumber()) {
            result.emplace_back(value->ToNumber<uint32_t>());
        } else if (value->IsObject()) {
            uint32_t singleResInt;
            if (ParseJsInteger(value, singleResInt, resObj)) {
                result.emplace_back(singleResInt);
            } else {
                resObjArray.clear();
                return false;
            }
        } else {
            resObjArray.clear();
            return false;
        }
        resObjArray.emplace_back(resObj);
    }
    return true;
}

bool JSViewAbstract::ParseJsIntegerArray(const JSRef<JSVal>& jsValue, std::vector<uint32_t>& result,
    RefPtr<ResourceObject>& resObj, std::vector<RefPtr<ResourceObject>>& resObjArray)
{
    if (!jsValue->IsArray() && !jsValue->IsObject()) {
        return false;
    }
    if (jsValue->IsArray()) {
        JSRef<JSArray> jsArray = JSRef<JSArray>::Cast(jsValue);
        return ParseJsIntegerArrayInternal(jsArray, result, resObjArray);
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    CompleteResourceObject(jsObj);
    int32_t resType = jsObj->GetPropertyValue<int32_t>("type", UNKNOWN_RESOURCE_TYPE);
    if (resType == UNKNOWN_RESOURCE_TYPE) {
        return false;
    }
    JSRef<JSVal> resId = jsObj->GetProperty("id");
    if (!resId->IsNumber()) {
        return false;
    }
    resObj = SystemProperties::ConfigChangePerform() ? GetResourceObject(jsObj) :
        GetResourceObjectByBundleAndModule(jsObj);
    auto resourceWrapper = CreateResourceWrapper(jsObj, resObj);
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
        if (resType == static_cast<int32_t>(ResourceType::INTARRAY)) {
            result = resourceWrapper->GetIntArrayByName(param->ToString());
            return true;
        }
        return false;
    }
    if (resType == static_cast<int32_t>(ResourceType::INTARRAY)) {
        result = resourceWrapper->GetIntArray(resId->ToNumber<uint32_t>());
        return true;
    }
    return false;
}

bool JSViewAbstract::ParseJsStrArray(const JSRef<JSVal>& jsValue, std::vector<std::string>& result)
{
    RefPtr<ResourceObject> resObj;
    std::vector<RefPtr<ResourceObject>> resObjArray;
    return ParseJsStrArray(jsValue, result, resObj, resObjArray);
}

bool JSViewAbstract::ParseJsStrArrayInternal(const JSRef<JSArray>& jsArray, std::vector<std::string>& result,
    std::vector<RefPtr<ResourceObject>>& resObjArray)
{
    for (size_t i = 0; i < jsArray->Length(); i++) {
        RefPtr<ResourceObject> resObj;
        JSRef<JSVal> value = jsArray->GetValueAt(i);
        if (value->IsString()) {
            result.emplace_back(value->ToString());
        } else if (value->IsObject()) {
            std::string singleResStr;
            if (ParseJsString(value, singleResStr, resObj)) {
                result.emplace_back(singleResStr);
            } else {
                resObjArray.clear();
                return false;
            }
        } else {
            resObjArray.clear();
            return false;
        }
        resObjArray.emplace_back(resObj);
    }
    return true;
}

bool JSViewAbstract::ParseJsStrArray(const JSRef<JSVal>& jsValue, std::vector<std::string>& result,
    RefPtr<ResourceObject>& resObj, std::vector<RefPtr<ResourceObject>>& resObjArray)
{
    if (!jsValue->IsArray() && !jsValue->IsObject()) {
        return false;
    }
    if (jsValue->IsArray()) {
        JSRef<JSArray> jsArray = JSRef<JSArray>::Cast(jsValue);
        return ParseJsStrArrayInternal(jsArray, result, resObjArray);
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    CompleteResourceObject(jsObj);
    int32_t resType = jsObj->GetPropertyValue<int32_t>("type", UNKNOWN_RESOURCE_TYPE);
    if (resType == UNKNOWN_RESOURCE_TYPE) {
        return false;
    }
    JSRef<JSVal> resId = jsObj->GetProperty("id");
    if (!resId->IsNumber()) {
        return false;
    }
    resObj = SystemProperties::ConfigChangePerform() ? GetResourceObject(jsObj) :
        GetResourceObjectByBundleAndModule(jsObj);
    auto resourceWrapper = CreateResourceWrapper(jsObj, resObj);
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
        if (resType == static_cast<int32_t>(ResourceType::STRARRAY)) {
            result = resourceWrapper->GetStringArrayByName(param->ToString());
            return true;
        }
        return false;
    }
    if (resType == static_cast<int32_t>(ResourceType::STRARRAY)) {
        result = resourceWrapper->GetStringArray(resId->ToNumber<uint32_t>());
        return true;
    }
    return false;
}

bool JSViewAbstract::ParseJsLengthMetricsArray(const JSRef<JSVal>& jsValue, std::vector<Dimension>& result)
{
    std::vector<RefPtr<ResourceObject>> resObjArray;
    return ParseJsLengthMetricsArray(jsValue, result, resObjArray);
}

bool JSViewAbstract::ParseJsLengthMetricsArray(const JSRef<JSVal>& jsValue, std::vector<Dimension>& result,
    std::vector<RefPtr<ResourceObject>>& resObjArray)
{
    if (jsValue->IsArray()) {
        JSRef<JSArray> array = JSRef<JSArray>::Cast(jsValue);
        for (size_t i = 0; i < array->Length(); i++) {
            RefPtr<ResourceObject> resObj;
            JSRef<JSVal> value = array->GetValueAt(i);
            Dimension calc;
            ParseJsLengthMetricsToDimension(value, calc, resObj);
            result.emplace_back(calc);
            resObjArray.emplace_back(resObj);
        }
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
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::OBJECT };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("ParseSize", jsVal, checkList)) {
        return std::pair<CalcDimension, CalcDimension>();
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsVal);
    CalcDimension width;
    CalcDimension height;
    if (!ParseJsDimensionVp(jsObj->GetProperty("width"), width) ||
        !ParseJsDimensionVp(jsObj->GetProperty("height"), height)) {
        return std::pair<CalcDimension, CalcDimension>();
    }
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
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::NUMBER };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("JsGridSpan", jsVal, checkList)) {
        if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            ViewAbstractModel::GetInstance()->SetGrid(NG::DEFAULT_GRID_SPAN, std::nullopt);
        }
        return;
    }
    auto span = jsVal->ToNumber<int32_t>();
    ViewAbstractModel::GetInstance()->SetGrid(span, std::nullopt);
}

void JSViewAbstract::JsGridOffset(const JSCallbackInfo& info)
{
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::NUMBER };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("JsGridOffset", jsVal, checkList)) {
        if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            ViewAbstractModel::GetInstance()->SetGrid(std::nullopt, NG::DEFAULT_GRID_OFFSET);
        }
        return;
    }
    auto offset = jsVal->ToNumber<int32_t>();
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
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::OBJECT };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("JsUseSizeType", jsVal, checkList)) {
        return;
    }
    JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(jsVal);
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
    if (ViewStackModel::GetInstance()->IsPrebuilding()) {
        return ViewStackModel::GetInstance()->PushPrebuildCompCmd("[JSViewAbstract][pop]", &JSViewAbstract::Pop);
    }
    ViewStackModel::GetInstance()->Pop();
}

void JSViewAbstract::JsSetDraggable(bool draggable)
{
    ViewAbstractModel::GetInstance()->SetDraggable(draggable);
}

void JSViewAbstract::ParseDragInteractionOptions(const JSCallbackInfo& info,
    NG::DragPreviewOption& previewOption)
{
    if (info.Length() > 1 && info[1]->IsObject()) {
        JSRef<JSObject> interObj = JSRef<JSObject>::Cast(info[1]);
        auto multiSelection = interObj->GetProperty("isMultiSelectionEnabled");
        if (multiSelection->IsBoolean()) {
            previewOption.isMultiSelectionEnabled = multiSelection->ToBoolean();
        }
        auto defaultAnimation = interObj->GetProperty("defaultAnimationBeforeLifting");
        if (defaultAnimation->IsBoolean()) {
            previewOption.defaultAnimationBeforeLifting = defaultAnimation->ToBoolean();
        }
        auto hapicFeedback = interObj->GetProperty("enableHapticFeedback");
        if (hapicFeedback->IsBoolean()) {
            previewOption.enableHapticFeedback = hapicFeedback->ToBoolean();
        }
        auto dragPreview = interObj->GetProperty("isDragPreviewEnabled");
        if (dragPreview->IsBoolean()) {
            previewOption.isDragPreviewEnabled = dragPreview->ToBoolean();
        }
        auto enableEdgeAutoScroll = interObj->GetProperty("enableEdgeAutoScroll");
        if (enableEdgeAutoScroll->IsBoolean()) {
            previewOption.enableEdgeAutoScroll = enableEdgeAutoScroll->ToBoolean();
        }
        auto isLiftingDisabled = interObj->GetProperty("isLiftingDisabled");
        if (isLiftingDisabled->IsBoolean()) {
            previewOption.isLiftingDisabled = isLiftingDisabled->ToBoolean();
        }
    }
}

NG::DragPreviewOption JSViewAbstract::ParseDragPreviewOptions (const JSCallbackInfo& info)
{
    NG::DragPreviewOption previewOption;
    if (!info[0]->IsObject()) {
        return previewOption;
    }
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
    auto mode = obj->GetProperty("mode");
    bool isAuto = true;
    if (mode->IsNumber()) {
        ParseDragPreviewMode(previewOption, mode->ToNumber<int>(), isAuto);
    } else if (mode->IsArray()) {
        JSRef<JSArray> array = JSRef<JSArray>::Cast(mode);
        for (size_t i = 0; i < array->Length(); i++) {
            JSRef<JSVal> value = array->GetValueAt(i);
            if (value->IsNumber()) {
                ParseDragPreviewMode(previewOption, value->ToNumber<int>(), isAuto);
            }
            if (isAuto) {
                break;
            }
        }
    }

    auto sizeChangeEffect = obj->GetProperty("sizeChangeEffect");
    if (sizeChangeEffect->IsNumber()) {
        previewOption.sizeChangeEffect = static_cast<NG::DraggingSizeChangeEffect>(sizeChangeEffect->ToNumber<int>());
    }

    JSViewAbstract::SetDragNumberBadge(info, previewOption);

    ParseDragInteractionOptions(info, previewOption);

    JSViewAbstract::SetDragPreviewOptionApply(info, previewOption);

    return previewOption;
}

void JSViewAbstract::JsSetDragPreviewOptions(const JSCallbackInfo& info)
{
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::OBJECT };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("JsSetDragPreviewOptions", jsVal, checkList)) {
        return;
    }
    NG::DragPreviewOption previewOption = ParseDragPreviewOptions(info);
    ViewAbstractModel::GetInstance()->SetDragPreviewOptions(previewOption);
}

void JSViewAbstract::JsOnDragStart(const JSCallbackInfo& info)
{
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::FUNCTION };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("JsOnDragStart", jsVal, checkList)) {
        return;
    }

    RefPtr<JsDragFunction> jsOnDragStartFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(jsVal));

    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
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
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::FUNCTION };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("JsOnDragEnter", jsVal, checkList)) {
        return;
    }
    RefPtr<JsDragFunction> jsOnDragEnterFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(jsVal));
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onDragEnter = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragEnterFunc), node = frameNode](
                           const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onDragEnter");
        PipelineContext::SetCallBackNode(node);
        func->Execute(info, extraParams);
    };

    ViewAbstractModel::GetInstance()->SetOnDragEnter(std::move(onDragEnter));
}

void JSViewAbstract::JsOnDragSpringLoading(const JSCallbackInfo& info)
{
    if (info.Length() > 0) {
        static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::FUNCTION, JSCallbackInfoType::OBJECT };
        auto jsVal = info[0];
        if (!CheckJSCallbackInfo("JsOnDragSpringLoading", jsVal, checkList)) {
            return;
        }
        NG::OnDrapDropSpringLoadingFunc onDragSpringLoading = nullptr;
        WeakPtr<NG::FrameNode> frameNode =
            AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        if (jsVal->IsFunction()) {
            RefPtr<JsDragFunction> jsOnDragSpringLoadingFunc =
                AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(jsVal));
            onDragSpringLoading = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragSpringLoadingFunc),
                                      node = frameNode](const RefPtr<DragSpringLoadingContext>& info) {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                ACE_SCORING_EVENT("JsOnDragSpringLoading");
                PipelineContext::SetCallBackNode(node);
                func->DragSpringLoadingExecute(info);
            };
        }
        ViewAbstractModel::GetInstance()->SetOnDragSpringLoading(std::move(onDragSpringLoading));
    }
    if (info.Length() == NUM2 && info[NUM1]->IsObject()) {
        auto dragSpringLoadingConfiguration = AceType::MakeRefPtr<NG::DragSpringLoadingConfiguration>();
        ParseDragSpringLoadingConfiguration(info[NUM1], dragSpringLoadingConfiguration);
        ViewAbstractModel::GetInstance()->SetOnDragSpringLoadingConfiguration(
            std::move(dragSpringLoadingConfiguration));
    }
}

void JSViewAbstract::JsOnDragEnd(const JSCallbackInfo& info)
{
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::FUNCTION };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("JsOnDragEnd", jsVal, checkList)) {
        return;
    }
    RefPtr<JsDragFunction> jsOnDragEndFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(jsVal));
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
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
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::FUNCTION };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("JsOnDragMove", jsVal, checkList)) {
        return;
    }
    RefPtr<JsDragFunction> jsOnDragMoveFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(jsVal));
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
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
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::FUNCTION };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("JsOnDragLeave", jsVal, checkList)) {
        return;
    }
    RefPtr<JsDragFunction> jsOnDragLeaveFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(jsVal));
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
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
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::FUNCTION };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("JsOnDrop", jsVal, checkList)) {
        return;
    }
    RefPtr<JsDragFunction> jsOnDropFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(jsVal));
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onDrop = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDropFunc), node = frameNode](
                      const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onDrop");
        PipelineContext::SetCallBackNode(node);
        func->Execute(info, extraParams);
    };

    ViewAbstractModel::GetInstance()->SetOnDrop(std::move(onDrop));

    bool disableDataPrefetch = false;
    if (info.Length() > 1 && info[1]->IsObject()) {
        JSRef<JSObject> interObj = JSRef<JSObject>::Cast(info[1]);
        auto jsDisableDataPrefetch = interObj->GetProperty("disableDataPrefetch");
        if (jsDisableDataPrefetch->IsBoolean()) {
            disableDataPrefetch = jsDisableDataPrefetch->ToBoolean();
        }
    }
    ViewAbstractModel::GetInstance()->SetDisableDataPrefetch(disableDataPrefetch);
}

void JSViewAbstract::JsOnAreaChange(const JSCallbackInfo& info)
{
    auto jsVal = info[0];
    if (jsVal->IsUndefined() && IsDisableEventVersion()) {
        ViewAbstractModel::GetInstance()->DisableOnAreaChange();
        return;
    }
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::FUNCTION };
    if (!CheckJSCallbackInfo("JsOnAreaChange", jsVal, checkList)) {
        return;
    }
    auto jsOnAreaChangeFunction = AceType::MakeRefPtr<JsOnAreaChangeFunction>(JSRef<JSFunc>::Cast(jsVal));

    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
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

void JSViewAbstract::JsOnSizeChange(const JSCallbackInfo& info)
{
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::FUNCTION };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("JsOnSizeChange", jsVal, checkList)) {
        return;
    }
    auto jsOnSizeChangeFunction = AceType::MakeRefPtr<JsOnSizeChangeFunction>(JSRef<JSFunc>::Cast(jsVal));

    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onSizeChanged = [execCtx = info.GetExecutionContext(), func = std::move(jsOnSizeChangeFunction),
                             node = frameNode](const NG::RectF& oldRect, const NG::RectF& rect) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onSizeChange");
        PipelineContext::SetCallBackNode(node);
        func->Execute(oldRect, rect);
    };
    ViewAbstractModel::GetInstance()->SetOnSizeChanged(std::move(onSizeChanged));
}

void JSViewAbstract::NewJsLinearGradient(const JSCallbackInfo& info, NG::Gradient& newGradient)
{
    if (!info[0]->IsObject()) {
        return;
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);
    newGradient.CreateGradientWithType(NG::GradientType::LINEAR);
    // angle
    std::optional<float> degree;
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        GetJsAngle(static_cast<int32_t>(ArkUIIndex::ANGLE), jsObj, degree);
    } else {
        GetJsAngleWithDefault(static_cast<int32_t>(ArkUIIndex::ANGLE), jsObj, degree, 180.0f);
    }
    if (degree) {
        newGradient.GetLinearGradient()->angle = CalcDimension(degree.value(), DimensionUnit::PX);
        degree.reset();
    }
    // direction
    auto direction = static_cast<GradientDirection>(
        jsObj->GetPropertyValue<int32_t>("direction", static_cast<int32_t>(GradientDirection::NONE)));
    SetGradientDirection(newGradient, direction);
    auto repeating = jsObj->GetPropertyValue<bool>("repeating", false);
    newGradient.SetRepeat(repeating);
    NewGetJsGradientColorStops(newGradient, jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::COLORS)), NUM_0);
}

void JSViewAbstract::SetGradientDirection(NG::Gradient& newGradient, const GradientDirection& direction)
{
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
        default:
            break;
    }
}

void JSViewAbstract::JsRadialGradient(const JSCallbackInfo& info)
{
    ViewAbstractModel::GetInstance()->RemoveResObj("RadialGradient.gradient");
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::OBJECT };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("JsRadialGradient", jsVal, checkList)) {
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
    JSRef<JSVal> arg = info[0];
    if (!arg->IsObject()) {
        return;
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(arg);
    newGradient.CreateGradientWithType(NG::GradientType::RADIAL);
    // center
    JSRef<JSVal> center = jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::CENTER));
    if (center->IsArray() && JSRef<JSArray>::Cast(center)->Length() == 2) {
        CalcDimension value;
        JSRef<JSArray> centerArray = JSRef<JSArray>::Cast(center);
        ParseRadialGradientCenter(newGradient, center);
    }
    // radius
    CalcDimension radius;
    RefPtr<ResourceObject> resObj;
    if (ParseJsDimensionVp(jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::RADIUS)), radius, resObj)) {
        newGradient.GetRadialGradient()->radialVerticalSize = CalcDimension(radius);
        newGradient.GetRadialGradient()->radialHorizontalSize = CalcDimension(radius);
    }
    if (SystemProperties::ConfigChangePerform() && resObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::Gradient& gradient) {
            CalcDimension dimension;
            ResourceParseUtils::ParseResDimensionVp(resObj, dimension);
            gradient.GetRadialGradient()->radialVerticalSize = CalcDimension(dimension);
            gradient.GetRadialGradient()->radialHorizontalSize = CalcDimension(dimension);
        };
        newGradient.AddResource("RadialGradient.radius", resObj, std::move(updateFunc));
    }

    // repeating
    auto repeating = jsObj->GetPropertyValue<bool>("repeating", false);
    newGradient.SetRepeat(repeating);
    // color stops
    NewGetJsGradientColorStops(newGradient, jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::COLORS)), NUM_2);
}

void JSViewAbstract::ParseRadialGradientCenter(NG::Gradient& newGradient, JSRef<JSArray> centerArray)
{
    RefPtr<ResourceObject> resObjX;
    RefPtr<ResourceObject> resObjY;
    CalcDimension value;

    if (ParseJsDimensionVp(centerArray->GetValueAt(0), value, resObjX)) {
        newGradient.GetRadialGradient()->radialCenterX = CalcDimension(value);
        if (value.Unit() == DimensionUnit::PERCENT) {
            // [0,1] -> [0, 100]
            newGradient.GetRadialGradient()->radialCenterX =
                CalcDimension(value.Value() * 100.0, DimensionUnit::PERCENT);
        }
    }
    if (SystemProperties::ConfigChangePerform() && resObjX) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::Gradient& gradient) {
            CalcDimension dimension;
            ResourceParseUtils::ParseResDimensionVp(resObj, dimension);
            gradient.GetRadialGradient()->radialCenterX = CalcDimension(dimension);
            if (dimension.Unit() == DimensionUnit::PERCENT) {
                // [0,1] -> [0, 100]
                gradient.GetRadialGradient()->radialCenterX =
                    CalcDimension(dimension.Value() * 100.0, DimensionUnit::PERCENT);
            }
        };
        newGradient.AddResource("RadialGradient.center.centerX", resObjX, std::move(updateFunc));
    }
    if (ParseJsDimensionVp(centerArray->GetValueAt(1), value, resObjY)) {
        newGradient.GetRadialGradient()->radialCenterY = CalcDimension(value);
        if (value.Unit() == DimensionUnit::PERCENT) {
            // [0,1] -> [0, 100]
            newGradient.GetRadialGradient()->radialCenterY =
                CalcDimension(value.Value() * 100.0, DimensionUnit::PERCENT);
        }
    }
    if (SystemProperties::ConfigChangePerform() && resObjY) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::Gradient& gradient) {
            CalcDimension dimension;
            ResourceParseUtils::ParseResDimensionVp(resObj, dimension);
            gradient.GetRadialGradient()->radialCenterY = CalcDimension(dimension);
            if (dimension.Unit() == DimensionUnit::PERCENT) {
                // [0,1] -> [0, 100]
                gradient.GetRadialGradient()->radialCenterY =
                    CalcDimension(dimension.Value() * 100.0, DimensionUnit::PERCENT);
            }
        };
        newGradient.AddResource("RadialGradient.center.centerY", resObjY, std::move(updateFunc));
    }
}

void JSViewAbstract::JsSweepGradient(const JSCallbackInfo& info)
{
    ViewAbstractModel::GetInstance()->RemoveResObj("SweepGradient.gradient");
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::OBJECT };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("JsSweepGradient", jsVal, checkList)) {
        NG::Gradient newGradient;
        newGradient.CreateGradientWithType(NG::GradientType::SWEEP);
        ViewAbstractModel::GetInstance()->SetSweepGradient(newGradient);
        return;
    }

    NG::Gradient newGradient;
    NewJsSweepGradient(info, newGradient);
    ViewAbstractModel::GetInstance()->SetSweepGradient(newGradient);
}

void JSViewAbstract::ParseSweepGradientCenter(NG::Gradient& newGradient, JSRef<JSArray> centerArray)
{
    RefPtr<ResourceObject> resObjX;
    RefPtr<ResourceObject> resObjY;
    CalcDimension value;
    if (ParseJsDimensionVp(centerArray->GetValueAt(0), value, resObjX)) {
        newGradient.GetSweepGradient()->centerX = CalcDimension(value);
        if (value.Unit() == DimensionUnit::PERCENT) {
            // [0,1] -> [0, 100]
            newGradient.GetSweepGradient()->centerX = CalcDimension(value.Value() * 100.0, DimensionUnit::PERCENT);
        }
    }
    if (SystemProperties::ConfigChangePerform() && resObjX) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::Gradient& gradient) {
            CalcDimension dimension;
            ResourceParseUtils::ParseResDimensionVp(resObj, dimension);
            gradient.GetSweepGradient()->centerX = CalcDimension(dimension);
            if (dimension.Unit() == DimensionUnit::PERCENT) {
                // [0,1] -> [0, 100]
                gradient.GetSweepGradient()->centerX = CalcDimension(dimension.Value() * 100.0, DimensionUnit::PERCENT);
            }
        };
        newGradient.AddResource("SweepGradient.center.centerX", resObjX, std::move(updateFunc));
    }
    if (ParseJsDimensionVp(centerArray->GetValueAt(1), value, resObjY)) {
        newGradient.GetSweepGradient()->centerY = CalcDimension(value);
        if (value.Unit() == DimensionUnit::PERCENT) {
            // [0,1] -> [0, 100]
            newGradient.GetSweepGradient()->centerY = CalcDimension(value.Value() * 100.0, DimensionUnit::PERCENT);
        }
    }
    if (SystemProperties::ConfigChangePerform() && resObjY) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::Gradient& gradient) {
            CalcDimension dimension;
            ResourceParseUtils::ParseResDimensionVp(resObj, dimension);
            gradient.GetSweepGradient()->centerY = CalcDimension(dimension);
            if (dimension.Unit() == DimensionUnit::PERCENT) {
                // [0,1] -> [0, 100]
                gradient.GetSweepGradient()->centerY = CalcDimension(dimension.Value() * 100.0, DimensionUnit::PERCENT);
            }
        };
        newGradient.AddResource("SweepGradient.center.centerY", resObjY, std::move(updateFunc));
    }
}

void JSViewAbstract::NewJsSweepGradient(const JSCallbackInfo& info, NG::Gradient& newGradient)
{
    JSRef<JSVal> arg = info[0];
    if (!arg->IsObject()) {
        return;
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(arg);
    newGradient.CreateGradientWithType(NG::GradientType::SWEEP);
    // center
    JSRef<JSVal> center = jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::CENTER));
    if (center->IsArray() && JSRef<JSArray>::Cast(center)->Length() == 2) {
        CalcDimension value;
        JSRef<JSArray> centerArray = JSRef<JSArray>::Cast(center);
        ParseSweepGradientCenter(newGradient, centerArray);
    }
    // start, end and rotation
    ParseSweepGradientPartly(jsObj, newGradient);
    // repeating
    auto repeating = jsObj->GetPropertyValue<bool>("repeating", false);
    newGradient.SetRepeat(repeating);
    // color stops
    JSRef<JSVal> metricColors = jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::METRICS_COLORS));
    if (metricColors->IsArray()) {
        NewGetJsGradientColorStopsCheck(newGradient, metricColors);
    } else {
        NewGetJsGradientColorStops(newGradient, jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::COLORS)), NUM_1);
    }
}

void JSViewAbstract::ParseSweepGradientPartly(const JSRef<JSObject>& obj, NG::Gradient& newGradient)
{
    std::optional<float> degreeStart;
    std::optional<float> degreeEnd;
    std::optional<float> degreeRotation;
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        GetJsAngle(static_cast<int32_t>(ArkUIIndex::START), obj, degreeStart);
        GetJsAngle(static_cast<int32_t>(ArkUIIndex::END), obj, degreeEnd);
        GetJsAngle(static_cast<int32_t>(ArkUIIndex::ROTATION), obj, degreeRotation);
    } else {
        GetJsAngleWithDefault(static_cast<int32_t>(ArkUIIndex::START), obj, degreeStart, 0.0f);
        GetJsAngleWithDefault(static_cast<int32_t>(ArkUIIndex::END), obj, degreeEnd, 0.0f);
        GetJsAngleWithDefault(static_cast<int32_t>(ArkUIIndex::ROTATION), obj, degreeRotation, 0.0f);
    }
    if (degreeStart) {
        CheckAngle(degreeStart);
        newGradient.GetSweepGradient()->startAngle = CalcDimension(degreeStart.value(), DimensionUnit::PX);
    }
    if (degreeEnd) {
        CheckAngle(degreeEnd);
        newGradient.GetSweepGradient()->endAngle = CalcDimension(degreeEnd.value(), DimensionUnit::PX);
    }
    if (degreeRotation) {
        CheckAngle(degreeRotation);
        newGradient.GetSweepGradient()->rotation = CalcDimension(degreeRotation.value(), DimensionUnit::PX);
    }
}

void JSViewAbstract::JsMotionPath(const JSCallbackInfo& info)
{
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::OBJECT };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("JsMotionPath", jsVal, checkList)) {
        ViewAbstractModel::GetInstance()->SetMotionPath(MotionPathOption());
        return;
    }
    MotionPathOption motionPathOption;
    if (ParseMotionPath(jsVal, motionPathOption)) {
        ViewAbstractModel::GetInstance()->SetMotionPath(motionPathOption);
    } else {
        TAG_LOGI(AceLogTag::ACE_ANIMATION, "Parse animation motionPath failed. %{public}s", jsVal->ToString().c_str());
        ViewAbstractModel::GetInstance()->SetMotionPath(MotionPathOption());
    }
}

void JSViewAbstract::JsShadow(const JSCallbackInfo& info)
{
    ViewAbstractModel::GetInstance()->RemoveResObj("shadow");
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::OBJECT, JSCallbackInfoType::NUMBER };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("JsShadow", jsVal, checkList)) {
        Shadow shadow;
        std::vector<Shadow> shadows { shadow };
        ViewAbstractModel::GetInstance()->SetBackShadow(shadows);
        return;
    }
    Shadow shadow;
    if (!ParseShadowProps(jsVal, shadow, SystemProperties::ConfigChangePerform())) {
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
    constexpr int BACKWARD_COMPAT_SOURCE_IN_NUMBER_OFFSCREEN = 2000;
    constexpr int BACKWARD_COMPAT_DESTINATION_IN_NUMBER_OFFSCREEN = 3000;
    constexpr int BACKWARD_COMPAT_MAGIC_NUMBER_SRC_IN = 5000;
    if (info[0]->IsNumber()) {
        auto blendModeNum = info[0]->ToNumber<int32_t>();
        if (blendModeNum >= 0 && blendModeNum < static_cast<int>(BlendMode::MAX)) {
            blendMode = static_cast<BlendMode>(blendModeNum);
        } else if (blendModeNum == BACKWARD_COMPAT_MAGIC_NUMBER_OFFSCREEN) {
            // backward compatibility code, will remove soon
            blendMode = BlendMode::SRC_OVER;
            blendApplyType = BlendApplyType::OFFSCREEN;
        } else if (blendModeNum == BACKWARD_COMPAT_SOURCE_IN_NUMBER_OFFSCREEN) {
            // backward compatibility code, will remove soon
            blendMode = BlendMode::SRC_IN;
            blendApplyType = BlendApplyType::OFFSCREEN;
        } else if (blendModeNum == BACKWARD_COMPAT_DESTINATION_IN_NUMBER_OFFSCREEN) {
            // backward compatibility code, will remove soon
            blendMode = BlendMode::DST_IN;
            blendApplyType = BlendApplyType::OFFSCREEN;
        } else if (blendModeNum == BACKWARD_COMPAT_MAGIC_NUMBER_SRC_IN) {
            blendMode = BlendMode::BACK_COMPAT_SOURCE_IN;
        }
    }
    if (info.Length() >= PARAMETER_LENGTH_SECOND && info[1]->IsNumber()) {
        auto blendApplyTypeNum = info[1]->ToNumber<int32_t>();
        if (blendApplyTypeNum >= 0 && blendApplyTypeNum < static_cast<int>(BlendApplyType::MAX)) {
            blendApplyType = static_cast<BlendApplyType>(blendApplyTypeNum);
        }
    }
    ViewAbstractModel::GetInstance()->SetBlendMode(blendMode);
    ViewAbstractModel::GetInstance()->SetBlendApplyType(blendApplyType);
}

void JSViewAbstract::JsAdvancedBlendMode(const JSCallbackInfo& info)
{
    if (info.Length() == 0) {
        return;
    }
    BlendMode blendMode = BlendMode::NONE;
    BlendApplyType blendApplyType = BlendApplyType::FAST;
    // for backward compatible, we temporary add a magic number to trigger offscreen, will remove soon
    constexpr int BACKWARD_COMPAT_MAGIC_NUMBER_OFFSCREEN = 1000;
    constexpr int BACKWARD_COMPAT_SOURCE_IN_NUMBER_OFFSCREEN = 2000;
    constexpr int BACKWARD_COMPAT_DESTINATION_IN_NUMBER_OFFSCREEN = 3000;
    constexpr int BACKWARD_COMPAT_MAGIC_NUMBER_SRC_IN = 5000;
    if (info[0]->IsNumber()) {
        auto blendModeNum = info[0]->ToNumber<int32_t>();
        if (blendModeNum >= 0 && blendModeNum < static_cast<int>(BlendMode::MAX)) {
            blendMode = static_cast<BlendMode>(blendModeNum);
        } else if (blendModeNum == BACKWARD_COMPAT_MAGIC_NUMBER_OFFSCREEN) {
            // backward compatibility code, will remove soon
            blendMode = BlendMode::SRC_OVER;
            blendApplyType = BlendApplyType::OFFSCREEN;
        } else if (blendModeNum == BACKWARD_COMPAT_SOURCE_IN_NUMBER_OFFSCREEN) {
            // backward compatibility code, will remove soon
            blendMode = BlendMode::SRC_IN;
            blendApplyType = BlendApplyType::OFFSCREEN;
        } else if (blendModeNum == BACKWARD_COMPAT_DESTINATION_IN_NUMBER_OFFSCREEN) {
            // backward compatibility code, will remove soon
            blendMode = BlendMode::DST_IN;
            blendApplyType = BlendApplyType::OFFSCREEN;
        } else if (blendModeNum == BACKWARD_COMPAT_MAGIC_NUMBER_SRC_IN) {
            blendMode = BlendMode::BACK_COMPAT_SOURCE_IN;
        }
    } else if (info[0]->IsObject()) {
        auto blender = CreateRSBrightnessBlenderFromNapiValue(info[0]);
        ViewAbstractModel::GetInstance()->SetBrightnessBlender(blender);
    }
    if (info.Length() >= PARAMETER_LENGTH_SECOND && info[1]->IsNumber()) {
        auto blendApplyTypeNum = info[1]->ToNumber<int32_t>();
        if (blendApplyTypeNum >= 0 && blendApplyTypeNum < static_cast<int>(BlendApplyType::MAX)) {
            blendApplyType = static_cast<BlendApplyType>(blendApplyTypeNum);
        }
    }
    if (!info[0]->IsObject()) {
        ViewAbstractModel::GetInstance()->SetBlendMode(blendMode);
    }
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
        invert = static_cast<float>(std::clamp(invertValue, 0.0, 1.0));
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
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::OBJECT, JSCallbackInfoType::NUMBER };
    InvertVariant invert = 0.0f;
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("JsInvert", jsVal, checkList)) {
        ViewAbstractModel::GetInstance()->SetInvert(invert);
        return;
    }
    if (ParseInvertProps(jsVal, invert)) {
        ViewAbstractModel::GetInstance()->SetInvert(invert);
    }
    ViewAbstractModel::GetInstance()->SetInvert(invert);
}

void JSViewAbstract::JsSystemBarEffect(const JSCallbackInfo& info)
{
    ViewAbstractModel::GetInstance()->SetSystemBarEffect(true);
}

void JSViewAbstract::JsHueRotate(const JSCallbackInfo& info)
{
    std::optional<float> degree;
    JSRef<JSVal> arg = info[0];
    if (arg->IsString()) {
        degree = static_cast<float>(StringUtils::StringToDegree(arg->ToString()));
    } else if (arg->IsNumber()) {
        degree = static_cast<float>(arg->ToNumber<int32_t>());
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
    JSRef<JSVal> arg = info[0];
    if (arg->IsUndefined()) {
        ViewAbstractModel::GetInstance()->SetClipEdge(false);
        return;
    }
    if (arg->IsObject()) {
        JSShapeAbstract* clipShape = JSRef<JSObject>::Cast(arg)->Unwrap<JSShapeAbstract>();
        if (clipShape == nullptr) {
            return;
        }
        ViewAbstractModel::GetInstance()->SetClipShape(clipShape->GetBasicShape());
    } else if (arg->IsBoolean()) {
        ViewAbstractModel::GetInstance()->SetClipEdge(arg->ToBoolean());
    }
}

void JSViewAbstract::JsClipShape(const JSCallbackInfo& info)
{
    ViewAbstractModel::GetInstance()->RemoveResObj("clipShape");
    if (info[0]->IsObject()) {
        JSShapeAbstract* clipShape = JSRef<JSObject>::Cast(info[0])->Unwrap<JSShapeAbstract>();
        if (clipShape == nullptr) {
            return;
        }
        ViewAbstractModel::GetInstance()->SetClipShape(clipShape->GetBasicShape());
    }
}

void JSViewAbstract::ParseProgressMaskResObj(const JSRef<JSVal>& jColor, Color& colorVal,
    RefPtr<NG::ProgressMaskProperty>& progressMask)
{
    RefPtr<ResourceObject> colorResObj;
    auto ret = ParseJsColor(jColor, colorVal, colorResObj);
    if (colorResObj) {
        progressMask->SetColor(colorVal);
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::ProgressMaskProperty& progressMask) {
            Color color;
            ResourceParseUtils::ParseResColor(resObj, color);
            progressMask.SetColor(color);
        };
        progressMask->AddResource("progressMask.color", colorResObj, std::move(updateFunc));
    } else if (ret) {
        progressMask->SetColor(colorVal);
    } else {
        RefPtr<ProgressTheme> theme = GetTheme<ProgressTheme>();
        progressMask->SetColor(theme->GetMaskColor());
        RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::ProgressMaskProperty& progressMask) {
            RefPtr<ProgressTheme> theme = GetTheme<ProgressTheme>();
            progressMask.SetColor(theme->GetMaskColor());
        };
        progressMask->AddResource("progressMask.color", resObj, std::move(updateFunc));
    }
}

void JSViewAbstract::ParseJsMaskProperty(const JSRef<JSObject>& paramObject)
{
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
    JSRef<JSVal> jEnableBreathe = paramObject->GetProperty("breathe");
    if (jEnableBreathe->IsBoolean()) {
        progressMask->SetEnableBreathe(jEnableBreathe->ToBoolean());
    }
    JSRef<JSVal> jColor = paramObject->GetProperty("color");
    Color colorVal;
    if (!SystemProperties::ConfigChangePerform()) {
        if (ParseJsColor(jColor, colorVal)) {
            progressMask->SetColor(colorVal);
        } else {
            RefPtr<ProgressTheme> theme = GetTheme<ProgressTheme>();
            progressMask->SetColor(theme->GetMaskColor());
        }
        ViewAbstractModel::GetInstance()->SetProgressMask(progressMask);
    } else {
        ParseProgressMaskResObj(jColor, colorVal, progressMask);
        ViewAbstractModel::GetInstance()->SetProgressMask(progressMask);
    }
}

void JSViewAbstract::JsMask(const JSCallbackInfo& info)
{
    JSRef<JSVal> arg = info[0];
    if (!arg->IsObject()) {
        ViewAbstractModel::GetInstance()->SetProgressMask(nullptr);
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(arg);
    JSRef<JSVal> typeParam = paramObject->GetProperty("type");
    if (!typeParam->IsNull() && !typeParam->IsUndefined() && typeParam->IsString() &&
        typeParam->ToString() == "ProgressMask") {
            ViewAbstractModel::GetInstance()->RemoveResObj("ProgressMask");
            ParseJsMaskProperty(paramObject);
    } else {
        ViewAbstractModel::GetInstance()->RemoveResObj("maskShape");
        JSShapeAbstract* maskShape = JSRef<JSObject>::Cast(arg)->Unwrap<JSShapeAbstract>();
        if (maskShape == nullptr) {
            return;
        };
        ViewAbstractModel::GetInstance()->SetMask(maskShape->GetBasicShape());
    }
}

void JSViewAbstract::JsMaskShape(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }

    JSShapeAbstract* maskShape = JSRef<JSObject>::Cast(info[0])->Unwrap<JSShapeAbstract>();
    if (maskShape == nullptr) {
        return;
    };
    ViewAbstractModel::GetInstance()->SetMask(maskShape->GetBasicShape());
}

void JSViewAbstract::JsFocusable(const JSCallbackInfo& info)
{
    if (!info[0]->IsBoolean()) {
        return;
    }
    ViewAbstractModel::GetInstance()->SetFocusable(info[0]->ToBoolean());
}

void JSViewAbstract::JsTabStop(const JSCallbackInfo& info)
{
    if (!info[0]->IsBoolean()) {
        ViewAbstractModel::GetInstance()->SetTabStop(false);
        return;
    }
    ViewAbstractModel::GetInstance()->SetTabStop(info[0]->ToBoolean());
}

void JSViewAbstract::JsNextFocus(const JSCallbackInfo& info)
{
    ViewAbstractModel::GetInstance()->ResetNextFocus();
    if (info.Length() == 1 && info[0]->IsObject()) {
        auto obj = JSRef<JSObject>::Cast(info[0]);
        auto forward = obj->GetPropertyValue<std::string>("forward", "");
        if (!forward.empty()) {
            ViewAbstractModel::GetInstance()->SetNextFocus(NG::FocusIntension::TAB, forward);
        }
        auto backward = obj->GetPropertyValue<std::string>("backward", "");
        if (!backward.empty()) {
            ViewAbstractModel::GetInstance()->SetNextFocus(NG::FocusIntension::SHIFT_TAB, backward);
        }
        auto up = obj->GetPropertyValue<std::string>("up", "");
        if (!up.empty()) {
            ViewAbstractModel::GetInstance()->SetNextFocus(NG::FocusIntension::UP, up);
        }
        auto down = obj->GetPropertyValue<std::string>("down", "");
        if (!down.empty()) {
            ViewAbstractModel::GetInstance()->SetNextFocus(NG::FocusIntension::DOWN, down);
        }
        auto left = obj->GetPropertyValue<std::string>("left", "");
        if (!left.empty()) {
            ViewAbstractModel::GetInstance()->SetNextFocus(NG::FocusIntension::LEFT, left);
        }
        auto right = obj->GetPropertyValue<std::string>("right", "");
        if (!right.empty()) {
            ViewAbstractModel::GetInstance()->SetNextFocus(NG::FocusIntension::RIGHT, right);
        }
    }
}

void JSViewAbstract::JsFocusBox(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject() || info.Length() != 1) {
        return;
    }
    auto obj = JSRef<JSObject>::Cast(info[0]);
    NG::FocusBoxStyle style;

    CalcDimension margin;
    RefPtr<ResourceObject> resObjMargin;
    if (ParseLengthMetricsToDimension(obj->GetProperty("margin"), margin, resObjMargin)) {
        ViewAbstractModel::GetInstance()->SetFocusBoxStyleUpdateFunc(style, resObjMargin, "focusBoxStyleMargin");
        style.margin = margin;
    }
    CalcDimension strokeWidth;
    RefPtr<ResourceObject> resObjWidth;
    if (ParseLengthMetricsToPositiveDimension(obj->GetProperty("strokeWidth"), strokeWidth, resObjWidth)) {
        ViewAbstractModel::GetInstance()->SetFocusBoxStyleUpdateFunc(style, resObjWidth, "focusBoxStyleWidth");
        style.strokeWidth = strokeWidth;
    }
    Color strokeColor;
    if (ParseColorMetricsToColor(obj->GetProperty("strokeColor"), strokeColor)) {
        style.strokeColor = strokeColor;
    }

    ViewAbstractModel::GetInstance()->SetFocusBoxStyle(style);
}

void JSViewAbstract::JsOnFocusMove(const JSCallbackInfo& args)
{
    JSRef<JSVal> arg = args[0];
    if (arg->IsFunction()) {
        RefPtr<JsFocusFunction> jsOnFocusMove = AceType::MakeRefPtr<JsFocusFunction>(JSRef<JSFunc>::Cast(arg));
        auto frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
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
    JSRef<JSVal> arg = args[0];
    if (arg->IsUndefined() && IsDisableEventVersion()) {
        ViewAbstractModel::GetInstance()->DisableOnKeyEvent();
        return;
    }
    if (!arg->IsFunction()) {
        return;
    }
    RefPtr<JsKeyFunction> JsOnKeyEvent = AceType::MakeRefPtr<JsKeyFunction>(JSRef<JSFunc>::Cast(arg));
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onKeyEvent = [execCtx = args.GetExecutionContext(), func = std::move(JsOnKeyEvent), node = frameNode](
                          KeyEventInfo& info) -> bool {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, false);
        ACE_SCORING_EVENT("onKey");
        PipelineContext::SetCallBackNode(node);
        auto ret = func->ExecuteWithValue(info);
        return ret->IsBoolean() ? ret->ToBoolean() : false;
    };
    ViewAbstractModel::GetInstance()->SetOnKeyEvent(std::move(onKeyEvent));
}

void JSViewAbstract::JsDispatchKeyEvent(const JSCallbackInfo& args)
{
    JSRef<JSVal> arg = args[0];
    if (!(arg->IsNumber() || arg->IsString())) {
        return;
    }
    RefPtr<NG::FrameNode> frameNode = nullptr;
    if (arg->IsString()) {
        std::string id = arg->ToString();
        frameNode = NG::Inspector::GetFrameNodeByKey(id);
    }

    if (arg->IsNumber()) {
        auto id = arg->ToNumber<int32_t>();
        auto node = ElementRegister::GetInstance()->GetNodeById(id);
        frameNode = AceType::DynamicCast<NG::FrameNode>(node);
    }
    CHECK_NULL_VOID(frameNode);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);

    if (!(args[1]->IsObject())) {
        return;
    }
    JSRef<JSObject> jsObject = JSRef<JSObject>::Cast(args[1]);
    auto eventInfoPtr = jsObject->Unwrap<KeyEventInfo>();
    CHECK_NULL_VOID(eventInfoPtr);
    KeyEvent keyEvent;
    eventInfoPtr->ParseKeyEvent(keyEvent);
    auto result = focusHub->HandleEvent(keyEvent);
    args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(result)));
}

void JSViewAbstract::JsOnCrownEvent(const JSCallbackInfo& args)
{
#ifdef SUPPORT_DIGITAL_CROWN
    if (args.Length() <= 0) {
        return;
    }
    if (args[0]->IsFunction()) {
        RefPtr<JsCrownFunction> JsOnCrownEventfunc = AceType::MakeRefPtr<JsCrownFunction>(JSRef<JSFunc>::Cast(args[0]));
        WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->
            GetMainFrameNode());
        auto onCrownEvent = [execCtx = args.GetExecutionContext(), func = std::move(JsOnCrownEventfunc),
            node = frameNode](CrownEventInfo& info) {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                ACE_SCORING_EVENT("onCrown");
                PipelineContext::SetCallBackNode(node);
                func->Execute(info);
            };
        ViewAbstractModel::GetInstance()->SetOnCrownEvent(std::move(onCrownEvent));
    } else {
        ViewAbstractModel::GetInstance()->DisableOnCrownEvent();
    }
#endif
}

void JSViewAbstract::ParseBindSheetBorderRadius(const JSRef<JSVal>& args, NG::SheetStyle& sheetStyle)
{
    if (!args->IsObject() && !args->IsNumber() && !args->IsString()) {
        TAG_LOGE(AceLogTag::ACE_SHEET, "radius is not correct type");
        return;
    }
    CalcDimension radius;
    NG::BorderRadiusProperty borderRadius;
    if (ParseJsLengthMetrics(args, radius)) {
        borderRadius.SetRadius(radius);
        sheetStyle.radius = borderRadius;
    } else if (ParseBindSheetBorderRadiusProps(args, borderRadius)) {
        sheetStyle.radius = borderRadius;
    } else {
        TAG_LOGW(AceLogTag::ACE_SHEET, "radius is not correct.");
        return;
    }
}

bool JSViewAbstract::ParseBindSheetBorderRadiusProps(const JSRef<JSVal>& args, NG::BorderRadiusProperty& radius)
{
    if (args->IsObject()) {
        JSRef<JSObject> object = JSRef<JSObject>::Cast(args);
        if (CheckLengthMetrics(object)) {
            std::optional<CalcDimension> radiusTopStart = ParseBindSheetBorderRadiusProp(object, TOP_START_PROPERTY);
            std::optional<CalcDimension> radiusTopEnd = ParseBindSheetBorderRadiusProp(object, TOP_END_PROPERTY);
            std::optional<CalcDimension> radiusBottomStart =
                ParseBindSheetBorderRadiusProp(object, BOTTOM_START_PROPERTY);
            std::optional<CalcDimension> radiusBottomEnd = ParseBindSheetBorderRadiusProp(object, BOTTOM_END_PROPERTY);
            auto isRightToLeft = AceApplicationInfo::GetInstance().IsRightToLeft();
            radius.radiusTopLeft = isRightToLeft ? radiusTopEnd : radiusTopStart;
            radius.radiusTopRight = isRightToLeft ? radiusTopStart : radiusTopEnd;
            radius.radiusBottomLeft = isRightToLeft ? radiusBottomEnd : radiusBottomStart;
            radius.radiusBottomRight = isRightToLeft ? radiusBottomStart : radiusBottomEnd;
            radius.multiValued = true;
        } else {
            ParseBorderRadiusProps(object, radius);
        }
        return true;
    }
    return false;
}

std::optional<CalcDimension> JSViewAbstract::ParseBindSheetBorderRadiusProp(
    const JSRef<JSObject>& object, const char* prop)
{
    if (object->IsEmpty()) {
        return std::nullopt;
    }
    if (object->HasProperty(prop) && object->GetProperty(prop)->IsObject()) {
        JSRef<JSObject> propObj = JSRef<JSObject>::Cast(object->GetProperty(prop));
        CalcDimension calcDimension;
        if (ParseJsLengthMetrics(propObj, calcDimension)) {
            return calcDimension;
        }
    }
    return std::nullopt;
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
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
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
    if (info.Length() >= PARAMETER_LENGTH_FIRST && info[0]->IsArray()) {
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

void JSViewAbstract::JsIgnoreLayoutSafeArea(const JSCallbackInfo& info)
{
    NG::IgnoreLayoutSafeAreaOpts opts { .type = NG::LAYOUT_SAFE_AREA_TYPE_SYSTEM, .rawEdges = NG::LAYOUT_SAFE_AREA_EDGE_ALL };
    if (info.Length() >= PARAMETER_LENGTH_FIRST && info[0]->IsArray()) {
        auto paramArray = JSRef<JSArray>::Cast(info[0]);
        uint32_t layoutSafeAreaType = NG::LAYOUT_SAFE_AREA_TYPE_NONE;
        for (size_t i = 0; i < paramArray->Length(); ++i) {
            if (!paramArray->GetValueAt(i)->IsNumber() ||
                paramArray->GetValueAt(i)->ToNumber<uint32_t>() > LAYOUT_SAFE_AREA_TYPE_LIMIT) {
                layoutSafeAreaType = NG::SAFE_AREA_TYPE_SYSTEM;
                break;
            }
            layoutSafeAreaType |= NG::IgnoreLayoutSafeAreaOpts::TypeToMask(paramArray->GetValueAt(i)->ToNumber<uint32_t>());
        }
        opts.type = layoutSafeAreaType;
    }
    if (info.Length() >= PARAMETER_LENGTH_SECOND && info[1]->IsArray()) {
        auto paramArray = JSRef<JSArray>::Cast(info[1]);
        uint32_t layoutSafeAreaEdge = NG::LAYOUT_SAFE_AREA_EDGE_NONE;
        for (size_t i = 0; i < paramArray->Length(); ++i) {
            if (!paramArray->GetValueAt(i)->IsNumber() ||
                paramArray->GetValueAt(i)->ToNumber<uint32_t>() > LAYOUT_SAFE_AREA_EDGE_LIMIT) {
                layoutSafeAreaEdge = NG::LAYOUT_SAFE_AREA_EDGE_ALL;
                break;
            }
            layoutSafeAreaEdge |=
                NG::IgnoreLayoutSafeAreaOpts::EdgeToMask(paramArray->GetValueAt(i)->ToNumber<uint32_t>());
        }
        opts.rawEdges = layoutSafeAreaEdge;
    }

    ViewAbstractModel::GetInstance()->UpdateIgnoreLayoutSafeAreaOpts(opts);
}

void ParseJSLightSource(JSRef<JSObject>& lightSource)
{
    if (lightSource->IsUndefined()) {
        return;
    }
    JSRef<JSVal> positionX = lightSource->GetProperty("positionX");
    JSRef<JSVal> positionY = lightSource->GetProperty("positionY");
    JSRef<JSVal> positionZ = lightSource->GetProperty("positionZ");
    JSRef<JSVal> intensity = lightSource->GetProperty("intensity");
    JSRef<JSVal> color = lightSource->GetProperty("color");

    CalcDimension dimPositionX;
    CalcDimension dimPositionY;
    CalcDimension dimPositionZ;
    if (JSViewAbstract::ParseJsDimensionVp(positionX, dimPositionX) &&
        JSViewAbstract::ParseJsDimensionVp(positionY, dimPositionY) &&
        JSViewAbstract::ParseJsDimensionVp(positionZ, dimPositionZ)) {
        ViewAbstractModel::GetInstance()->SetLightPosition(dimPositionX, dimPositionY, dimPositionZ);
    }

    if (intensity->IsNumber()) {
        float intensityValue = intensity->ToNumber<float>();
        ViewAbstractModel::GetInstance()->SetLightIntensity(intensityValue);
    }

    Color lightColor;
    if (JSViewAbstract::ParseJsColor(color, lightColor)) {
        ViewAbstractModel::GetInstance()->SetLightColor(lightColor);
    }
}

void ParseJSLightSourcePositionX(const JSRef<JSObject>& lightSource, NG::TranslateOptions& option)
{
    JSRef<JSVal> positionX = lightSource->GetProperty("positionX");
    CalcDimension dimPositionX;
    RefPtr<ResourceObject> dimPositionXResObj;
    if (JSViewAbstract::ParseJsDimensionVp(positionX, dimPositionX, dimPositionXResObj)) {
        option.x = dimPositionX;
    }
    if (dimPositionXResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::TranslateOptions& option) {
            CalcDimension dimension;
            ResourceParseUtils::ParseResDimensionVp(resObj, dimension);
            option.x = dimension;
        };
        option.AddResource("pointLight.LightSource.PositionX", dimPositionXResObj, std::move(updateFunc));
    }
}

void ParseJSLightSourcePositionY(const JSRef<JSObject>& lightSource, NG::TranslateOptions& option)
{
    JSRef<JSVal> positionY = lightSource->GetProperty("positionY");
    CalcDimension dimPositionY;
    RefPtr<ResourceObject> dimPositionYResObj;
    if (JSViewAbstract::ParseJsDimensionVp(positionY, dimPositionY, dimPositionYResObj)) {
        option.y = dimPositionY;
    }
    if (dimPositionYResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::TranslateOptions& option) {
            CalcDimension dimension;
            ResourceParseUtils::ParseResDimensionVp(resObj, dimension);
            option.y = dimension;
        };
        option.AddResource("pointLight.LightSource.PositionY", dimPositionYResObj, std::move(updateFunc));
    }
}

void ParseJSLightSourcePositionZ(const JSRef<JSObject>& lightSource, NG::TranslateOptions& option)
{
    JSRef<JSVal> positionZ = lightSource->GetProperty("positionZ");
    CalcDimension dimPositionZ;
    RefPtr<ResourceObject> dimPositionZResObj;
    if (JSViewAbstract::ParseJsDimensionVp(positionZ, dimPositionZ, dimPositionZResObj)) {
        option.z = dimPositionZ;
    }
    if (dimPositionZResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::TranslateOptions& option) {
            CalcDimension dimension;
            ResourceParseUtils::ParseResDimensionVp(resObj, dimension);
            option.z = dimension;
        };
        option.AddResource("pointLight.LightSource.PositionZ", dimPositionZResObj, std::move(updateFunc));
    }

}

void ParseJSLightSourceNew(JSRef<JSObject>& lightSource)
{
    if (lightSource->IsUndefined()) {
        return;
    }
    JSRef<JSVal> intensity = lightSource->GetProperty("intensity");
    JSRef<JSVal> color = lightSource->GetProperty("color");

    NG::TranslateOptions option;
    ParseJSLightSourcePositionX(lightSource, option);
    ParseJSLightSourcePositionY(lightSource, option);
    ParseJSLightSourcePositionZ(lightSource, option);
    ViewAbstractModel::GetInstance()->SetLightPosition(option);

    if (intensity->IsNumber()) {
        float intensityValue = intensity->ToNumber<float>();
        ViewAbstractModel::GetInstance()->SetLightIntensity(intensityValue);
    }

    Color lightColor;
    RefPtr<ResourceObject> lightColorResObj;
    bool ret = JSViewAbstract::ParseJsColor(color, lightColor, lightColorResObj);
    if (lightColorResObj) {
        ViewAbstractModel::GetInstance()->CreateWithLightColorResourceObj(lightColorResObj);
    } else if (ret) {
        ViewAbstractModel::GetInstance()->SetLightColor(lightColor);
    }
}

void JSViewAbstract::JsPointLight(const JSCallbackInfo& info)
{
#ifdef POINT_LIGHT_ENABLE
    if (!info[0]->IsObject()) {
        return;
    }

    ViewAbstractModel::GetInstance()->RemoveResObj("LightColorRes");
    JSRef<JSObject> object = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSObject> lightSource = object->GetProperty("lightSource");
    if (!SystemProperties::ConfigChangePerform()) {
        ParseJSLightSource(lightSource);
    } else {
        ParseJSLightSourceNew(lightSource);
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
#endif
}

void JSViewAbstract::JsSetDragEventStrictReportingEnabled(const JSCallbackInfo& info)
{
    if (info[0]->IsBoolean()) {
        ViewAbstractModel::GetInstance()->SetDragEventStrictReportingEnabled(info[0]->ToBoolean());
    }
}

void JSViewAbstract::JsEnableDropDisallowedBadge(const JSCallbackInfo& info)
{
    if (info[0]->IsBoolean()) {
        ViewAbstractModel::GetInstance()->EnableDropDisallowedBadge(info[0]->ToBoolean());
    }
}

void JSViewAbstract::JsNotifyDragStartRequest(const JSCallbackInfo& info)
{
    if (info[0]->IsNumber()) {
        int32_t dragStatus = info[0]->ToNumber<int32_t>();
        ViewAbstractModel::GetInstance()->NotifyDragStartRequest(
            static_cast<DragStartRequestStatus>(dragStatus));
    }
}

void JSViewAbstract::JsCancelDataLoading(const std::string& key)
{
    if (key.empty()) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Invalid input parameter.");
        return;
    }
    auto ret = ViewAbstractModel::GetInstance()->CancelDataLoading(key);
    if (ret != 0) {
        JSException::Throw(ERROR_CODE_DRAG_OPERATION_FAILED, "%s", "Operation failed.");
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
    JSClass<JSViewAbstract>::StaticMethod("toolbar", &JSViewAbstract::JsToolbar);
    JSClass<JSViewAbstract>::StaticMethod("responseRegion", &JSViewAbstract::JsResponseRegion);
    JSClass<JSViewAbstract>::StaticMethod("mouseResponseRegion", &JSViewAbstract::JsMouseResponseRegion);
    JSClass<JSViewAbstract>::StaticMethod("size", &JSViewAbstract::JsSize);
    JSClass<JSViewAbstract>::StaticMethod("constraintSize", &JSViewAbstract::JsConstraintSize);
    JSClass<JSViewAbstract>::StaticMethod("layoutPriority", &JSViewAbstract::JsLayoutPriority);
    JSClass<JSViewAbstract>::StaticMethod("pixelRound", &JSLayoutableView::JsPixelRound);
    JSClass<JSViewAbstract>::StaticMethod("layoutWeight", &JSViewAbstract::JsLayoutWeight);
    JSClass<JSViewAbstract>::StaticMethod("chainWeight", &JSLayoutableView::JsChainWeight);

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
    JSClass<JSViewAbstract>::StaticMethod("safeAreaPadding", &JSViewAbstract::SetSafeAreaPadding, opt);

    JSClass<JSViewAbstract>::StaticMethod("foregroundColor", &JSViewAbstract::JsForegroundColor);
    JSClass<JSViewAbstract>::StaticMethod("foregroundEffect", &JSViewAbstract::JsForegroundEffect);
    JSClass<JSViewAbstract>::StaticMethod("backgroundColor", &JSViewAbstract::JsBackgroundColor);
    JSClass<JSViewAbstract>::StaticMethod("backgroundImage", &JSViewAbstract::JsBackgroundImage);
    JSClass<JSViewAbstract>::StaticMethod("backgroundImageSize", &JSViewAbstract::JsBackgroundImageSize);
    JSClass<JSViewAbstract>::StaticMethod("backgroundImagePosition", &JSViewAbstract::JsBackgroundImagePosition);
    JSClass<JSViewAbstract>::StaticMethod("backgroundBlurStyle", &JSViewAbstract::JsBackgroundBlurStyle);
    JSClass<JSViewAbstract>::StaticMethod("backgroundEffect", &JSViewAbstract::JsBackgroundEffect);
    JSClass<JSViewAbstract>::StaticMethod("backgroundImageResizable", &JSViewAbstract::JsBackgroundImageResizable);
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
    JSClass<JSViewAbstract>::StaticMethod("transform3D", &JSViewAbstract::JsTransform3D);
    JSClass<JSViewAbstract>::StaticMethod("transition", &JSViewAbstract::JsTransition);

    JSClass<JSViewAbstract>::StaticMethod("align", &JSViewAbstract::JsAlign);
    JSClass<JSViewAbstract>::StaticMethod("layoutGravity", &JSViewAbstract::JsLayoutGravity);
    JSClass<JSViewAbstract>::StaticMethod("position", &JSViewAbstract::JsPosition);
    JSClass<JSViewAbstract>::StaticMethod("markAnchor", &JSViewAbstract::JsMarkAnchor);
    JSClass<JSViewAbstract>::StaticMethod("offset", &JSViewAbstract::JsOffset);
    JSClass<JSViewAbstract>::StaticMethod("enabled", &JSViewAbstract::JsEnabled);
    JSClass<JSViewAbstract>::StaticMethod("aspectRatio", &JSViewAbstract::JsAspectRatio);
    JSClass<JSViewAbstract>::StaticMethod("overlay", &JSViewAbstract::JsOverlay);

    JSClass<JSViewAbstract>::StaticMethod("blur", &JSViewAbstract::JsBlur);
    JSClass<JSViewAbstract>::StaticMethod("motionBlur", &JSViewAbstract::JsMotionBlur);
    JSClass<JSViewAbstract>::StaticMethod("useEffect", &JSViewAbstract::JsUseEffect);
    JSClass<JSViewAbstract>::StaticMethod("useShadowBatching", &JSViewAbstract::JsUseShadowBatching);
    JSClass<JSViewAbstract>::StaticMethod("colorBlend", &JSViewAbstract::JsColorBlend);
    JSClass<JSViewAbstract>::StaticMethod("backdropBlur", &JSViewAbstract::JsBackdropBlur);
    JSClass<JSViewAbstract>::StaticMethod("linearGradientBlur", &JSViewAbstract::JsLinearGradientBlur);
    JSClass<JSViewAbstract>::StaticMethod("backgroundBrightness", &JSViewAbstract::JsBackgroundBrightness);
    JSClass<JSViewAbstract>::StaticMethod("backgroundBrightnessInternal", &JSViewAbstract::JsBackgroundBrightnessInternal);
    JSClass<JSViewAbstract>::StaticMethod("foregroundBrightness", &JSViewAbstract::JsForegroundBrightness);
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
    JSClass<JSViewAbstract>::StaticMethod("bindTips", &JSViewAbstract::JsBindTips);
#endif

    JSClass<JSViewAbstract>::StaticMethod("background", &JSViewAbstract::JsBackground);
    JSClass<JSViewAbstract>::StaticMethod("bindMenu", &JSViewAbstract::JsBindMenu);
    JSClass<JSViewAbstract>::StaticMethod("bindContextMenu", &JSViewAbstract::JsBindContextMenu);
    JSClass<JSViewAbstract>::StaticMethod("bindContentCover", &JSViewAbstract::JsBindContentCover);
    JSClass<JSViewAbstract>::StaticMethod("bindSheet", &JSViewAbstract::JsBindSheet);
    JSClass<JSViewAbstract>::StaticMethod("draggable", &JSViewAbstract::JsSetDraggable);
    JSClass<JSViewAbstract>::StaticMethod("dragPreviewOptions", &JSViewAbstract::JsSetDragPreviewOptions);
    JSClass<JSViewAbstract>::StaticMethod("onPreDrag", &JSViewAbstract::JsOnPreDrag);
    JSClass<JSViewAbstract>::StaticMethod("onDragStart", &JSViewAbstract::JsOnDragStart);
    JSClass<JSViewAbstract>::StaticMethod("onDragEnter", &JSViewAbstract::JsOnDragEnter);
    JSClass<JSViewAbstract>::StaticMethod("onDragSpringLoading", &JSViewAbstract::JsOnDragSpringLoading);
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
    JSClass<JSViewAbstract>::StaticMethod("advancedBlendMode", &JSViewAbstract::JsAdvancedBlendMode);
    JSClass<JSViewAbstract>::StaticMethod("grayscale", &JSViewAbstract::JsGrayScale);
    JSClass<JSViewAbstract>::StaticMethod("focusable", &JSViewAbstract::JsFocusable);
    JSClass<JSViewAbstract>::StaticMethod("tabStop", &JSViewAbstract::JsTabStop);
    JSClass<JSViewAbstract>::StaticMethod("nextFocus", &JSViewAbstract::JsNextFocus);
    JSClass<JSViewAbstract>::StaticMethod("focusBox", &JSViewAbstract::JsFocusBox);
    JSClass<JSViewAbstract>::StaticMethod("onKeyEvent", &JSViewAbstract::JsOnKeyEvent);
    JSClass<JSViewAbstract>::StaticMethod("onKeyPreIme", &JSInteractableView::JsOnKeyPreIme);
    JSClass<JSViewAbstract>::StaticMethod("onKeyEventDispatch", &JSInteractableView::JsOnKeyEventDispatch);
    JSClass<JSViewAbstract>::StaticMethod("dispatchKeyEvent", &JSViewAbstract::JsDispatchKeyEvent);
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
    JSClass<JSViewAbstract>::StaticMethod("systemBarEffect", &JSViewAbstract::JsSystemBarEffect);
    JSClass<JSViewAbstract>::StaticMethod("hueRotate", &JSViewAbstract::JsHueRotate);
    JSClass<JSViewAbstract>::StaticMethod("clip", &JSViewAbstract::JsClip);
    JSClass<JSViewAbstract>::StaticMethod("clipShape", &JSViewAbstract::JsClip);
    JSClass<JSViewAbstract>::StaticMethod("mask", &JSViewAbstract::JsMask);
    JSClass<JSViewAbstract>::StaticMethod("maskShape", &JSViewAbstract::JsMask);
    JSClass<JSViewAbstract>::StaticMethod("key", &JSViewAbstract::JsKey);
    JSClass<JSViewAbstract>::StaticMethod("id", &JSViewAbstract::JsId);
    JSClass<JSViewAbstract>::StaticMethod("restoreId", &JSViewAbstract::JsRestoreId);
    JSClass<JSViewAbstract>::StaticMethod("hoverEffect", &JSViewAbstract::JsHoverEffect);
    JSClass<JSViewAbstract>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSViewAbstract>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSViewAbstract>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSViewAbstract>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSViewAbstract>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSViewAbstract>::StaticMethod("onMouse", &JSViewAbstract::JsOnMouse);
    JSClass<JSViewAbstract>::StaticMethod("onAxisEvent", &JSViewAbstract::JsOnAxisEvent);
    JSClass<JSViewAbstract>::StaticMethod("onHover", &JSViewAbstract::JsOnHover);
    JSClass<JSViewAbstract>::StaticMethod("onHoverMove", &JSViewAbstract::JsOnHoverMove);
    JSClass<JSViewAbstract>::StaticMethod("onAccessibilityHover", &JSViewAbstract::JsOnAccessibilityHover);
    JSClass<JSViewAbstract>::StaticMethod("onDigitalCrown", &JSViewAbstract::JsOnCrownEvent);
    JSClass<JSViewAbstract>::StaticMethod("onClick", &JSViewAbstract::JsOnClick);
    JSClass<JSViewAbstract>::StaticMethod("onGestureJudgeBegin", &JSViewAbstract::JsOnGestureJudgeBegin);
    JSClass<JSViewAbstract>::StaticMethod("onTouchIntercept", &JSViewAbstract::JsOnTouchIntercept);
    JSClass<JSViewAbstract>::StaticMethod(
        "shouldBuiltInRecognizerParallelWith", &JSViewAbstract::JsShouldBuiltInRecognizerParallelWith);
    JSClass<JSViewAbstract>::StaticMethod(
        "onGestureRecognizerJudgeBegin", &JSViewAbstract::JsOnGestureRecognizerJudgeBegin);
    JSClass<JSViewAbstract>::StaticMethod("onTouchTestDone", &JSViewAbstract::JsOnTouchTestDone);
    JSClass<JSViewAbstract>::StaticMethod("clickEffect", &JSViewAbstract::JsClickEffect);
    JSClass<JSViewAbstract>::StaticMethod("debugLine", &JSViewAbstract::JsDebugLine);
    JSClass<JSViewAbstract>::StaticMethod("geometryTransition", &JSViewAbstract::JsGeometryTransition);
    JSClass<JSViewAbstract>::StaticMethod("onAreaChange", &JSViewAbstract::JsOnAreaChange);
    JSClass<JSViewAbstract>::StaticMethod("onSizeChange", &JSViewAbstract::JsOnSizeChange);
    JSClass<JSViewAbstract>::StaticMethod("touchable", &JSInteractableView::JsTouchable);
    JSClass<JSViewAbstract>::StaticMethod("monopolizeEvents", &JSInteractableView::JsMonopolizeEvents);
    JSClass<JSViewAbstract>::StaticMethod("onFocusAxisEvent", &JSViewAbstract::JsOnFocusAxisEvent);

    JSClass<JSViewAbstract>::StaticMethod("accessibilityGroup", &JSViewAbstract::JsAccessibilityGroup);
    JSClass<JSViewAbstract>::StaticMethod("accessibilityText", &JSViewAbstract::JsAccessibilityText);
    JSClass<JSViewAbstract>::StaticMethod("accessibilityNextFocusId", &JSViewAbstract::JsAccessibilityNextFocusId);
    JSClass<JSViewAbstract>::StaticMethod("accessibilityDescription", &JSViewAbstract::JsAccessibilityDescription);
    JSClass<JSViewAbstract>::StaticMethod("accessibilityImportance", &JSViewAbstract::JsAccessibilityImportance);
    JSClass<JSViewAbstract>::StaticMethod("accessibilityLevel", &JSViewAbstract::JsAccessibilityLevel);
    JSClass<JSViewAbstract>::StaticMethod("accessibilityVirtualNode", &JSViewAbstract::JsAccessibilityVirtualNode);
    JSClass<JSViewAbstract>::StaticMethod("onAccessibility", &JSInteractableView::JsOnAccessibility);
    JSClass<JSViewAbstract>::StaticMethod("accessibilitySelected", &JSViewAbstract::JsAccessibilitySelected);
    JSClass<JSViewAbstract>::StaticMethod("accessibilityChecked", &JSViewAbstract::JsAccessibilityChecked);
    JSClass<JSViewAbstract>::StaticMethod("accessibilityRole", &JSViewAbstract::JsAccessibilityRole);
    JSClass<JSViewAbstract>::StaticMethod("onAccessibilityFocus", &JSViewAbstract::JsOnAccessibilityFocus);
    JSClass<JSViewAbstract>::StaticMethod("accessibilityDefaultFocus", &JSViewAbstract::JsAccessibilityDefaultFocus);
    JSClass<JSViewAbstract>::StaticMethod("accessibilityUseSamePage", &JSViewAbstract::JsAccessibilityUseSamePage);
    JSClass<JSViewAbstract>::StaticMethod("accessibilityScrollTriggerable",
                                          &JSViewAbstract::JsAccessibilityScrollTriggerable);
    JSClass<JSViewAbstract>::StaticMethod("accessibilityFocusDrawLevel",
                                          &JSViewAbstract::JsAccessibilityFocusDrawLevel);
    JSClass<JSViewAbstract>::StaticMethod("onAccessibilityActionIntercept",
                                          &JSViewAbstract::JsOnAccessibilityActionIntercept);
    JSClass<JSViewAbstract>::StaticMethod("onAccessibilityHoverTransparent",
                                          &JSViewAbstract::JsOnAccessibilityHoverTransparent);

    JSClass<JSViewAbstract>::StaticMethod("alignRules", &JSViewAbstract::JsAlignRules);
    JSClass<JSViewAbstract>::StaticMethod("chainMode", &JSViewAbstract::JsChainMode);
    JSClass<JSViewAbstract>::StaticMethod("onVisibleAreaChange", &JSViewAbstract::JsOnVisibleAreaChange);
    JSClass<JSViewAbstract>::StaticMethod(
        "onVisibleAreaApproximateChange", &JSViewAbstract::JsOnVisibleAreaApproximateChange);
    JSClass<JSViewAbstract>::StaticMethod("hitTestBehavior", &JSViewAbstract::JsHitTestBehavior);
    JSClass<JSViewAbstract>::StaticMethod("onChildTouchTest", &JSViewAbstract::JsOnChildTouchTest);
    JSClass<JSViewAbstract>::StaticMethod("keyboardShortcut", &JSViewAbstract::JsKeyboardShortcut);
    JSClass<JSViewAbstract>::StaticMethod("obscured", &JSViewAbstract::JsObscured);
    JSClass<JSViewAbstract>::StaticMethod("privacySensitive", &JSViewAbstract::JsPrivacySensitive);
    JSClass<JSViewAbstract>::StaticMethod("allowDrop", &JSViewAbstract::JsAllowDrop);
    JSClass<JSViewAbstract>::StaticMethod("dragPreview", &JSViewAbstract::JsDragPreview);
    JSClass<JSViewAbstract>::StaticMethod("accessibilityTextHint", &JSViewAbstract::JsAccessibilityTextHint);

    JSClass<JSViewAbstract>::StaticMethod("createAnimatableProperty", &JSViewAbstract::JSCreateAnimatableProperty);
    JSClass<JSViewAbstract>::StaticMethod("updateAnimatableProperty", &JSViewAbstract::JSUpdateAnimatableProperty);
    JSClass<JSViewAbstract>::StaticMethod("renderGroup", &JSViewAbstract::JSRenderGroup);
    JSClass<JSViewAbstract>::StaticMethod("renderFit", &JSViewAbstract::JSRenderFit);

    JSClass<JSViewAbstract>::StaticMethod("freeze", &JSViewAbstract::JsSetFreeze);

    JSClass<JSViewAbstract>::StaticMethod("expandSafeArea", &JSViewAbstract::JsExpandSafeArea);
    JSClass<JSViewAbstract>::StaticMethod("ignoreLayoutSafeArea", &JSViewAbstract::JsIgnoreLayoutSafeArea);

    JSClass<JSViewAbstract>::StaticMethod("drawModifier", &JSViewAbstract::JsDrawModifier);
    JSClass<JSViewAbstract>::StaticMethod("customProperty", &JSViewAbstract::JsCustomProperty);
    JSClass<JSViewAbstract>::StaticMethod("gestureModifier", &JSViewAbstract::JsGestureModifier);
    JSClass<JSViewAbstract>::StaticMethod("notifyDragStartRequest", &JSViewAbstract::JsNotifyDragStartRequest);
    JSClass<JSViewAbstract>::StaticMethod(
        "setDragEventStrictReportingEnabled", &JSViewAbstract::JsSetDragEventStrictReportingEnabled);
    JSClass<JSViewAbstract>::StaticMethod(
        "enableDropDisallowedBadge", &JSViewAbstract::JsEnableDropDisallowedBadge);
    JSClass<JSViewAbstract>::StaticMethod("cancelDataLoading", &JSViewAbstract::JsCancelDataLoading);

    JSClass<JSViewAbstract>::StaticMethod("focusScopeId", &JSViewAbstract::JsFocusScopeId);
    JSClass<JSViewAbstract>::StaticMethod("focusScopePriority", &JSViewAbstract::JsFocusScopePriority);

    JSClass<JSViewAbstract>::StaticMethod("visualEffect", &JSViewAbstract::JsVisualEffect);
    JSClass<JSViewAbstract>::StaticMethod("backgroundFilter", &JSViewAbstract::JsBackgroundFilter);
    JSClass<JSViewAbstract>::StaticMethod("foregroundFilter", &JSViewAbstract::JsForegroundFilter);
    JSClass<JSViewAbstract>::StaticMethod("compositingFilter", &JSViewAbstract::JsCompositingFilter);

    JSClass<JSViewAbstract>::StaticMethod("setPixelRoundMode", &JSViewAbstract::SetPixelRoundMode);
    JSClass<JSViewAbstract>::StaticMethod("getPixelRoundMode", &JSViewAbstract::GetPixelRoundMode);

    JSClass<JSViewAbstract>::Bind(globalObj);
}

void AddInvalidateFunc(JSRef<JSObject> jsDrawModifier, NG::FrameNode* frameNode)
{
    auto invalidate = [](panda::JsiRuntimeCallInfo* info) -> panda::Local<panda::JSValueRef> {
        auto vm = info->GetVM();
        CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
        Local<JSValueRef> thisObj = info->GetFunctionRef();
        auto thisObjRef = panda::Local<panda::ObjectRef>(thisObj);
        if (thisObjRef->GetNativePointerFieldCount(vm) < 1) {
            return panda::JSValueRef::Undefined(vm);
        }

        auto* weak = reinterpret_cast<NG::NativeWeakRef*>(thisObjRef->GetNativePointerField(vm, 0));
        if (weak->Invalid()) {
            return panda::JSValueRef::Undefined(vm);
        }

        auto frameNode = AceType::DynamicCast<NG::FrameNode>(weak->weakRef.Upgrade());
        if (frameNode) {
            const auto& extensionHandler = frameNode->GetExtensionHandler();
            if (extensionHandler) {
                extensionHandler->InvalidateRender();
                extensionHandler->ForegroundRender();
            } else {
                frameNode->MarkDirtyNode(NG::PROPERTY_UPDATE_RENDER);
            }
        }

        return panda::JSValueRef::Undefined(vm);
    };
    auto jsInvalidate = JSRef<JSFunc>::New<FunctionCallback>(invalidate);
    if (frameNode) {
        const auto& extensionHandler = frameNode->GetExtensionHandler();
        if (extensionHandler) {
            extensionHandler->InvalidateRender();
            extensionHandler->ForegroundRender();
        } else {
            frameNode->MarkDirtyNode(NG::PROPERTY_UPDATE_RENDER);
        }
    }
    auto vm = jsInvalidate->GetEcmaVM();
    auto* weak = new NG::NativeWeakRef(static_cast<AceType*>(frameNode));
    jsInvalidate->GetHandle()->SetNativePointerFieldCount(vm, 1);
    jsInvalidate->GetHandle()->SetNativePointerField(vm, 0, weak, &NG::DestructorInterceptor<NG::NativeWeakRef>);
    jsDrawModifier->SetPropertyObject("invalidate", jsInvalidate);
}

void JSViewAbstract::JsDrawModifier(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }

    auto frameNode = static_cast<NG::FrameNode*>(ViewAbstractModel::GetInstance()->GetFrameNode());
    bool IsSupportDrawModifier = frameNode && frameNode->IsSupportDrawModifier();
    if (!IsSupportDrawModifier) {
        return;
    }
    auto jsDrawModifier = JSRef<JSObject>::Cast(info[0]);
    RefPtr<NG::DrawModifier> drawModifier = AceType::MakeRefPtr<NG::DrawModifier>();
    auto execCtx = info.GetExecutionContext();
    auto getDrawModifierFunc = [execCtx, jsDrawModifier](const char* key) -> NG::DrawModifierFunc {
        JSRef<JSVal> drawMethod = jsDrawModifier->GetProperty(key);
        if (!drawMethod->IsFunction()) {
            return nullptr;
        }

        auto jsDrawFunc = AceType::MakeRefPtr<JsFunction>(
            JSRef<JSObject>(jsDrawModifier), JSRef<JSFunc>::Cast(drawMethod));

        return GetDrawCallback(jsDrawFunc, execCtx, jsDrawModifier);
    };

    drawModifier->drawBehindFunc = getDrawModifierFunc("drawBehind");
    drawModifier->drawContentFunc = getDrawModifierFunc("drawContent");
    drawModifier->drawFrontFunc = getDrawModifierFunc("drawFront");
    drawModifier->drawForegroundFunc = getDrawModifierFunc("drawForeground");

    ViewAbstractModel::GetInstance()->SetDrawModifier(drawModifier);
    AddInvalidateFunc(jsDrawModifier, frameNode);
}

void JSViewAbstract::JsAllowDrop(const JSCallbackInfo& info)
{
    std::set<std::string> allowDropSet;
    allowDropSet.clear();
    if (!info[0]->IsUndefined() && info[0]->IsArray()) {
        auto allowDropArray = JSRef<JSArray>::Cast(info[0]);
        std::string allowDrop;
        for (size_t i = 0; i < allowDropArray->Length(); i++) {
            allowDrop = allowDropArray->GetValueAt(i)->ToString();
            allowDropSet.insert(allowDrop);
        }
        ViewAbstractModel::GetInstance()->SetDisallowDropForcedly(false);
    } else if (info[0]->IsNull()) {
        ViewAbstractModel::GetInstance()->SetDisallowDropForcedly(true);
    } else {
        ViewAbstractModel::GetInstance()->SetDisallowDropForcedly(false);
    }
    ViewAbstractModel::GetInstance()->SetAllowDrop(allowDropSet);
}

void JSViewAbstract::JsOnPreDrag(const JSCallbackInfo& info)
{
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::FUNCTION };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("JsOnPreDrag", jsVal, checkList)) {
        return;
    }

    RefPtr<JsDragFunction> jsDragFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(jsVal));
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onPreDrag = [execCtx = info.GetExecutionContext(), func = std::move(jsDragFunc), node = frameNode](
                         const PreDragStatus preDragStatus) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onPreDrag");
        PipelineContext::SetCallBackNode(node);
        func->PreDragExecute(preDragStatus);
    };
    ViewAbstractModel::GetInstance()->SetOnPreDrag(onPreDrag);
}

void JSViewAbstract::ParseDragPreviewConfig(const JSCallbackInfo& info, NG::DragDropInfo& dragPreviewInfo)
{
    if (info.Length() <= 1) {
        return;
    }
    auto jsVal = info[1];
    if (!jsVal->IsObject()) {
        return;
    }
    auto config = JSRef<JSObject>::Cast(jsVal);
    ParseJsBool(config->GetProperty("onlyForLifting"), dragPreviewInfo.onlyForLifting);
    ParseJsBool(config->GetProperty("delayCreating"), dragPreviewInfo.delayCreating);
}

void JSViewAbstract::ParseDragPreviewValue(const JSCallbackInfo& info, NG::DragDropInfo& dragPreviewInfo)
{
    auto jsVal = info[0];
    JSRef<JSVal> builder;
    JSRef<JSVal> pixelMap;
    JSRef<JSVal> extraInfo;
    if (jsVal->IsFunction()) {
        builder = jsVal;
    } else if (jsVal->IsObject()) {
        auto dragItemInfo = JSRef<JSObject>::Cast(jsVal);
        builder = dragItemInfo->GetProperty("builder");
#if defined(PIXEL_MAP_SUPPORTED)
        pixelMap = dragItemInfo->GetProperty("pixelMap");
        dragPreviewInfo.pixelMap = CreatePixelMapFromNapiValue(pixelMap);
#endif
        extraInfo = dragItemInfo->GetProperty("extraInfo");
        ParseJsString(extraInfo, dragPreviewInfo.extraInfo);
    } else if (jsVal->IsString()) {
        auto inspectorId = jsVal;
        ParseJsString(inspectorId, dragPreviewInfo.inspectorId);
    } else {
        return;
    }
    ParseDragPreviewBuilderNode(info, dragPreviewInfo, builder);
}

void JSViewAbstract::ParseDragPreviewBuilderNode(const JSCallbackInfo& info, NG::DragDropInfo& dragPreviewInfo,
    const JSRef<JSVal>& builder)
{
    if (!builder->IsFunction()) {
        return;
    }
    RefPtr<JsFunction> builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(builder));
    CHECK_NULL_VOID(builderFunc);
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto buildFunc = [execCtx = info.GetExecutionContext(), func = std::move(builderFunc),
                         node = frameNode]() -> RefPtr<NG::UINode> {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, nullptr);
        ACE_SCORING_EVENT("dragPreview.builder");
        PipelineContext::SetCallBackNode(node);
        func->Execute();
        auto customNode = ViewStackModel::GetInstance()->Finish();
        return AceType::DynamicCast<NG::UINode>(customNode);
    };
    if (!dragPreviewInfo.delayCreating) {
        ViewStackModel::GetInstance()->NewScope();
        {
            dragPreviewInfo.customNode = buildFunc();
        }
    } else {
        dragPreviewInfo.buildFunc = buildFunc;
    }
}

void JSViewAbstract::JsDragPreview(const JSCallbackInfo& info)
{
    auto jsVal = info[0];
    if ((!jsVal->IsObject()) && (!jsVal->IsString())) {
        return;
    }
    NG::DragDropInfo dragPreviewInfo;
    ParseDragPreviewConfig(info, dragPreviewInfo);
    ParseDragPreviewValue(info, dragPreviewInfo);
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
    const char* keys[] = { "left", "middle", "right", "top", "center", "bottom", "bias", "start", "end" };
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
            } else if (i == HORIZONTAL_DIRECTION_START_INDEX) {
                alignRules[AlignDirection::LEFT] = alignRule;
            } else if (i == HORIZONTAL_DIRECTION_END_INDEX) {
                alignRules[AlignDirection::RIGHT] = alignRule;
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

void JSViewAbstract::JsChainMode(const JSCallbackInfo& info)
{
    ChainInfo chainInfo;
    if (info.Length() >= 1) {
        auto tmpDirection = info[0];
        if (tmpDirection->IsUndefined()) {
            chainInfo.direction = std::nullopt;
        } else if (tmpDirection->IsNumber()) {
            auto direction = tmpDirection->ToNumber<int32_t>();
            chainInfo.direction = static_cast<LineDirection>(direction);
        }
    }

    if (info.Length() >= 2) { // 2 : two args
        auto tmpStyle = info[1];
        if (tmpStyle->IsUndefined()) {
            chainInfo.style = std::nullopt;
        } else if (tmpStyle->IsNumber()) {
            auto style = tmpStyle->ToNumber<int32_t>();
            chainInfo.style = static_cast<ChainStyle>(style);
        }
    }
    ViewAbstractModel::GetInstance()->SetChainStyle(chainInfo);
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

void JSViewAbstract::SetSafeAreaPadding(const JSCallbackInfo& info)
{
    ParseMarginOrPadding(info, EdgeType::SAFE_AREA_PADDING);
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

void JSViewAbstract::SetBgDynamicBrightness(BrightnessOption brightnessOption)
{
    ViewAbstractModel::GetInstance()->SetBgDynamicBrightness(brightnessOption);
}

void JSViewAbstract::SetFgDynamicBrightness(BrightnessOption brightnessOption)
{
    ViewAbstractModel::GetInstance()->SetFgDynamicBrightness(brightnessOption);
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

void JSViewAbstract::ParseShadowOffsetXY(const JSRef<JSObject>& jsObj, Shadow& shadow)
{
    CalcDimension offsetX;
    RefPtr<ResourceObject> xResObj;
    if (ParseJsResource(jsObj->GetProperty("offsetX"), offsetX, xResObj)) {
        if (SystemProperties::ConfigChangePerform() && xResObj) {
            auto&& updateFunc = [](const RefPtr<ResourceObject>& xResObj, Shadow& shadow) {
                CalcDimension xValue;
                ResourceParseUtils::ParseResResource(xResObj, xValue);
                shadow.SetOffsetX(xValue.Value());
            };
            shadow.AddResource("shadow.offsetX", xResObj, std::move(updateFunc));
        }
        shadow.SetOffsetX(offsetX.Value());
    } else {
        if (ParseJsDimensionVp(jsObj->GetProperty("offsetX"), offsetX)) {
            shadow.SetOffsetX(offsetX.Value());
        }
    }
    CalcDimension offsetY;
    RefPtr<ResourceObject> yResObj;
    auto jsOffsetY = jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::OFFSET_Y));
    if (ParseJsResource(jsOffsetY, offsetY, yResObj)) {
        if (yResObj) {
            auto&& updateFunc = [](const RefPtr<ResourceObject>& yResObj, Shadow& shadow) {
                CalcDimension yValue;
                ResourceParseUtils::ParseResResource(yResObj, yValue);
                shadow.SetOffsetY(yValue.Value());
            };
            shadow.AddResource("shadow.offsetY", yResObj, std::move(updateFunc));
        }
        shadow.SetOffsetY(offsetY.Value());
    } else {
        if (ParseJsDimensionVp(jsOffsetY, offsetY)) {
            shadow.SetOffsetY(offsetY.Value());
        }
    }
}

void JSViewAbstract::ParseShadowPropsUpdate(const JSRef<JSObject>& jsObj, double& radius, Shadow& shadow)
{
    if (jsObj->IsUndefined()) {
        return;
    }
    RefPtr<ResourceObject> radiusResObj;
    ParseJsDouble(jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::RADIUS)), radius, radiusResObj);
    if (SystemProperties::ConfigChangePerform() && radiusResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& radiusResObj, Shadow& shadow) {
            double radius = 0.0;
            ResourceParseUtils::ParseResDouble(radiusResObj, radius);
            if (LessNotEqual(radius, 0.0)) {
                radius = 0.0;
            }
            shadow.SetBlurRadius(radius);
        };
        shadow.AddResource("shadow.radius", radiusResObj, std::move(updateFunc));
    }
}

bool JSViewAbstract::ParseShadowProps(const JSRef<JSVal>& jsValue, Shadow& shadow, const bool configChangePerform)
{
    int32_t shadowStyle = 0;
    if (ParseJsInteger<int32_t>(jsValue, shadowStyle)) {
        auto style = static_cast<ShadowStyle>(shadowStyle);
        return GetShadowFromTheme(style, shadow, configChangePerform);
    }
    if (!jsValue->IsObject()) {
        return false;
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    double radius = 0.0;
    ParseShadowPropsUpdate(jsObj, radius, shadow);
    if (LessNotEqual(radius, 0.0)) {
        radius = 0.0;
    }
    shadow.SetBlurRadius(radius);
    ParseShadowOffsetXY(jsObj, shadow);

    Color color;
    ShadowColorStrategy shadowColorStrategy;
    auto jsColor = jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::COLOR));
    RefPtr<ResourceObject> colorResObj;
    if (ParseJsShadowColorStrategy(jsColor, shadowColorStrategy)) {
        shadow.SetShadowColorStrategy(shadowColorStrategy);
    } else if (ParseJsColor(jsColor, color, colorResObj)) {
        if (SystemProperties::ConfigChangePerform() && colorResObj) {
            auto&& updateFunc = [](const RefPtr<ResourceObject>& colorResObj, Shadow& shadow) {
                Color colorValue;
                ResourceParseUtils::ParseResColor(colorResObj, colorValue);
                shadow.SetColor(colorValue);
            };
            shadow.AddResource("shadow.colorValue", colorResObj, std::move(updateFunc));
        }
        shadow.SetColor(color);
    }

    int32_t type = static_cast<int32_t>(ShadowType::COLOR);
    JSViewAbstract::ParseJsInt32(jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::TYPE)), type);
    if (type != static_cast<int32_t>(ShadowType::BLUR)) {
        type = static_cast<int32_t>(ShadowType::COLOR);
    }
    shadow.SetShadowType(static_cast<ShadowType>(type));
    bool isFilled = jsObj->GetPropertyValue<bool>(static_cast<int32_t>(ArkUIIndex::FILL), false);
    shadow.SetIsFilled(isFilled);
    return true;
}

bool JSViewAbstract::GetShadowFromTheme(ShadowStyle shadowStyle, Shadow& shadow, const bool configChangePerform)
{
    ViewAbstractModel::GetInstance()->RemoveResObj("shadowStyle");
    auto colorMode = Container::CurrentColorMode();
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
    if (configChangePerform) {
        auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
        CHECK_NULL_RETURN(frameNode, false);
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_RETURN(pattern, false);
        RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
        auto&& updateFunc = [shadowStyle, weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
            auto frameNode = weak.Upgrade();
            CHECK_NULL_VOID(frameNode);
            auto colorMode = Container::CurrentColorMode();
            auto container = Container::Current();
            CHECK_NULL_VOID(container);
            auto pipelineContext = container->GetPipelineContext();
            CHECK_NULL_VOID(pipelineContext);
            auto shadowTheme = pipelineContext->GetTheme<ShadowTheme>();
            if (!shadowTheme) {
                return;
            }
            Shadow shadow = shadowTheme->GetShadow(shadowStyle, colorMode);
            ACE_UPDATE_NODE_RENDER_CONTEXT(BackShadow, shadow, frameNode);
        };
        updateFunc(resObj);
        pattern->AddResObj("shadowStyle", resObj, std::move(updateFunc));
        return false;
    }
    return true;
}

bool JSViewAbstract::ParseJsResource(const JSRef<JSVal>& jsValue, CalcDimension& result)
{
    RefPtr<ResourceObject> resObj;
    return ParseJsResource(jsValue, result, resObj);
}

bool JSViewAbstract::ParseJsResource(const JSRef<JSVal>& jsValue, CalcDimension& result,
    RefPtr<ResourceObject>& resObj)
{
    if (!jsValue->IsObject()) {
        return false;
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    uint32_t type = jsObj->GetPropertyValue<uint32_t>(static_cast<int32_t>(ArkUIIndex::TYPE), 0);
    if (type == 0) {
        return false;
    }
    if (SystemProperties::ConfigChangePerform()) {
        resObj = GetResourceObject(jsObj);
    }
    auto resourceWrapper = CreateResourceWrapper();
    CHECK_NULL_RETURN(resourceWrapper, false);
    if (type == static_cast<uint32_t>(ResourceType::STRING)) {
        auto value = resourceWrapper->GetString(
            jsObj->GetPropertyValue<uint32_t>(static_cast<int32_t>(ArkUIIndex::ID), 0));
        return StringUtils::StringToCalcDimensionNG(value, result, false);
    }
    if (type == static_cast<uint32_t>(ResourceType::INTEGER)) {
        auto value = std::to_string(
            resourceWrapper->GetInt(jsObj->GetPropertyValue<uint32_t>(static_cast<int32_t>(ArkUIIndex::ID), 0)));
        StringUtils::StringToDimensionWithUnitNG(value, result);
        return true;
    }

    if (type == static_cast<uint32_t>(ResourceType::FLOAT)) {
        result = resourceWrapper->GetDimension(
            jsObj->GetPropertyValue<uint32_t>(static_cast<int32_t>(ArkUIIndex::ID), 0));
        return true;
    }
    return false;
}

bool JSViewAbstract::ParseDataDetectorConfig(const JSCallbackInfo& info, TextDetectConfig& textDetectConfig)
{
    JSRef<JSVal> arg = info[0];
    if (!arg->IsObject()) {
        return false;
    }
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(arg);
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
            textDetectConfig.types.append(",");
        }
        textDetectConfig.types.append(TEXT_DETECT_TYPES[index]);
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    JSRef<JSVal> resultCallback = obj->GetProperty("onDetectResultUpdate");
    if (resultCallback->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsClipboardFunction>(JSRef<JSFunc>::Cast(resultCallback));
        textDetectConfig.onResult = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                       const std::string& result) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            PipelineContext::SetCallBackNode(node);
            func->Execute(result);
        };
    }
    auto enablePreviewMenuValue = obj->GetProperty("enablePreviewMenu");
    if (enablePreviewMenuValue->IsBoolean()) {
        textDetectConfig.enablePreviewMenu = enablePreviewMenuValue->ToBoolean();
    }
    return ParseAIEntityColor(obj, textDetectConfig);
}

bool JSViewAbstract::ParseAIEntityColor(const JSRef<JSObject>& obj, TextDetectConfig& textDetectConfig)
{
    RefPtr<ResourceObject> resObj;
    JSRef<JSVal> entityColorValue = obj->GetProperty("color");
    ParseJsColor(entityColorValue, textDetectConfig.entityColor, resObj);
    TextDetectConfig::RegisterColorResource(textDetectConfig, resObj);

    JSRef<JSVal> decorationValue = obj->GetProperty("decoration");
    if (decorationValue->IsUndefined() || !decorationValue->IsObject()) {
        textDetectConfig.entityDecorationColor = textDetectConfig.entityColor;
        return true;
    }
    JSRef<JSObject> decorationObj = JSRef<JSObject>::Cast(decorationValue);
    JSRef<JSVal> typeValue = decorationObj->GetProperty("type");
    JSRef<JSVal> colorValue = decorationObj->GetProperty("color");
    JSRef<JSVal> styleValue = decorationObj->GetProperty("style");

    if (typeValue->IsNumber()) {
        textDetectConfig.entityDecorationType = static_cast<TextDecoration>(typeValue->ToNumber<int32_t>());
    } else {
        textDetectConfig.entityDecorationType = TextDecoration::UNDERLINE;
    }
    RefPtr<ResourceObject> decoColorResObj;
    if (!ParseJsColor(colorValue, textDetectConfig.entityDecorationColor, decoColorResObj)) {
        textDetectConfig.entityDecorationColor = textDetectConfig.entityColor;
    }
    TextDetectConfig::RegisterDecoColorResource(textDetectConfig, decoColorResObj);
    if (styleValue->IsNumber()) {
        textDetectConfig.entityDecorationStyle = static_cast<TextDecorationStyle>(styleValue->ToNumber<int32_t>());
    } else {
        textDetectConfig.entityDecorationStyle = TextDecorationStyle::SOLID;
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
    int32_t key, const JSRef<JSVal>& jsValue, std::optional<float>& angle)
{
    if (!jsValue->IsObject()) {
        return;
    }
    JSRef<JSVal> value = JSRef<JSObject>::Cast(jsValue)->GetProperty(key);
    if (value->IsString()) {
        angle = static_cast<float>(StringUtils::StringToDegree(value->ToString()));
    } else if (value->IsNumber()) {
        angle = value->ToNumber<float>();
    }
}

// if angle is not string or number, return directly. If angle is invalid string, use defaultValue.
void JSViewAbstract::GetJsAngleWithDefault(
    int32_t key, const JSRef<JSObject>& jsObj, std::optional<float>& angle, float defaultValue)
{
    JSRef<JSVal> value = jsObj->GetProperty(key);
    if (value->IsString()) {
        double temp = 0.0;
        if (StringUtils::StringToDegree(value->ToString(), temp)) {
            angle = static_cast<float>(temp);
        } else {
            angle = defaultValue;
        }
    } else if (value->IsNumber()) {
        angle = value->ToNumber<float>();
    }
}

inline void JSViewAbstract::CheckAngle(std::optional<float>& angle)
{
    angle = std::clamp(angle.value(), 0.0f, MAX_ANGLE);
}

void JSViewAbstract::GetPerspective(
    const std::string& key, const std::unique_ptr<JsonValue>& jsonValue, float& perspective)
{
    auto value = jsonValue->GetValue(key);
    if (value && value->IsNumber()) {
        perspective = static_cast<float>(value->GetDouble());
    }
}

void JSViewAbstract::GetJsPerspective(int32_t key, const JSRef<JSObject>& jsValue, float& perspective)
{
    auto value = jsValue->GetProperty(key);
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

void JSViewAbstract::NewParseSweepGradientColor(NG::Gradient& gradient, RefPtr<ResourceObject>& resObj,
    NG::GradientColor& gradientColor, int32_t& indx)
{
    auto&& updateFunc = [gradientColor, indx](const RefPtr<ResourceObject>& resObj,
        NG::Gradient& gradient) {
        std::vector<NG::GradientColor> colorVector = gradient.GetColors();
        int32_t colorLength = colorVector.size();
        gradient.ClearColors();
        for (int32_t index = 0; index < colorLength; index++) {
            NG::GradientColor gradColor = colorVector[index];
            if (index == indx) {
                Color color;
                ResourceParseUtils::ParseResColor(resObj, color);
                gradColor.SetColor(color);
            }
            gradient.AddColor(gradColor);
        }
    };
    std::string key = "SweepGradient.gradient.color" + std::to_string(indx);
    gradient.AddResource(key, resObj, std::move(updateFunc));
}

void JSViewAbstract::NewParseRadialGradientColor(NG::Gradient& gradient, RefPtr<ResourceObject>& resObj,
    NG::GradientColor& gradientColor, int32_t& indx)
{
    auto&& updateFunc = [gradientColor, indx](const RefPtr<ResourceObject>& resObj,
        NG::Gradient& gradient) {
        std::vector<NG::GradientColor> colorVector = gradient.GetColors();
        int32_t colorLength = colorVector.size();
        gradient.ClearColors();
        for (int32_t index = 0; index < colorLength; index++) {
            NG::GradientColor gradColor = colorVector[index];
            if (index == indx) {
                Color color;
                ResourceParseUtils::ParseResColor(resObj, color);
                gradColor.SetColor(color);
            }
            gradient.AddColor(gradColor);
        }
    };
    std::string key = "RadialGradient.gradient.color" + std::to_string(indx);
    gradient.AddResource(key, resObj, std::move(updateFunc));
}

void JSViewAbstract::NewParseGradientColor(NG::Gradient& gradient, RefPtr<ResourceObject>& resObj,
    NG::GradientColor& gradientColor, int32_t& indx)
{
    auto&& updateFunc = [gradientColor, indx](const RefPtr<ResourceObject>& resObj,
        NG::Gradient& gradient) {
        std::vector<NG::GradientColor> colorVector = gradient.GetColors();
        int32_t colorLength = colorVector.size();
        gradient.ClearColors();
        for (int32_t index = 0; index < colorLength; index++) {
            NG::GradientColor gradColor = colorVector[index];
            if (index == indx) {
                Color color;
                ResourceParseUtils::ParseResColor(resObj, color);
                gradColor.SetColor(color);
            }
            gradient.AddColor(gradColor);
        }
    };
    std::string key = "LinearGradient.gradient.color" + std::to_string(indx);
    gradient.AddResource(key, resObj, std::move(updateFunc));
}

void JSViewAbstract::NewGetJsGradientColorStops(NG::Gradient& gradient, const JSRef<JSVal>& colorStops,
    const int32_t mapIdx)
{
    if (!colorStops->IsArray()) {
        return;
    }
    JSRef<JSArray> jsArray = JSRef<JSArray>::Cast(colorStops);
    size_t length = jsArray->Length();
    int32_t nullNum = 0;
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
        RefPtr<ResourceObject> resObj;
        if (!ParseJsColor(subArray->GetValueAt(0), color, resObj)) {
            nullNum++;
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
        if (SystemProperties::ConfigChangePerform() && resObj) {
            int32_t indx = i - nullNum;
            if (mapIdx == NUM_1) {
                NewParseSweepGradientColor(gradient, resObj, gradientColor, indx);
            } else if (mapIdx == NUM_2) {
                NewParseRadialGradientColor(gradient, resObj, gradientColor, indx);
            } else {
                NewParseGradientColor(gradient, resObj, gradientColor, indx);
            }
        }
    }
}

void JSViewAbstract::NewGetJsGradientColorStopsCheck(NG::Gradient& gradient, const JSRef<JSVal>& colorStops)
{
    if (!colorStops->IsArray()) {
        return;
    }

    JSRef<JSArray> jsArray = JSRef<JSArray>::Cast(colorStops);
    size_t length = jsArray->Length();
    bool isValid = true;
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
        // is valid
        if (gradient.GetColors().size()) {
            if (color.GetColorSpace() != gradient.GetColors().back().GetColor().GetColorSpace()) {
                isValid = false;
                gradient.ClearColors();
                break;
            }
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
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::NUMBER };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("HoverEffect", jsVal, checkList)) {
        ViewAbstractModel::GetInstance()->SetHoverEffect(HoverEffectType::AUTO);
        return;
    }
    if (!jsVal->IsNumber()) {
        return;
    }
    ViewAbstractModel::GetInstance()->SetHoverEffect(static_cast<HoverEffectType>(jsVal->ToNumber<int32_t>()));
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
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onMouse = [execCtx = info.GetExecutionContext(), func = std::move(jsOnMouseFunc), node = targetNode](
                       MouseInfo& mouseInfo) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onMouse");
        PipelineContext::SetCallBackNode(node);
        func->Execute(mouseInfo);
    };
    ViewAbstractModel::GetInstance()->SetOnMouse(std::move(onMouse));
}

void JSViewAbstract::JsOnAxisEvent(const JSCallbackInfo& args)
{
    JSRef<JSVal> arg = args[0];
    if (arg->IsUndefined() && IsDisableEventVersion()) {
        ViewAbstractModel::GetInstance()->DisableOnAxisEvent();
        return;
    }
    if (!arg->IsFunction()) {
        return;
    }
    EcmaVM* vm = args.GetVm();
    CHECK_NULL_VOID(vm);
    auto jsOnAxisEventFunc = JSRef<JSFunc>::Cast(args[0]);
    if (jsOnAxisEventFunc->IsEmpty()) {
        return;
    }
    auto jsOnAxisFuncLocalHandle = jsOnAxisEventFunc->GetLocalHandle();
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onAxisEvent = [vm, execCtx = args.GetExecutionContext(),
                       func = panda::CopyableGlobal(vm, jsOnAxisFuncLocalHandle),
                       node = frameNode](Ace::AxisInfo& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onAxis");
        PipelineContext::SetCallBackNode(node);
        auto eventObj = NG::CommonBridge::CreateAxisEventInfo(vm, info);
        panda::Local<panda::JSValueRef> params[1] = { eventObj };
        func->Call(vm, func.ToLocal(), params, 1);
    };
    ViewAbstractModel::GetInstance()->SetOnAxisEvent(std::move(onAxisEvent));
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
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onHover = [execCtx = info.GetExecutionContext(), func = std::move(jsOnHoverFunc), node = frameNode](
                       bool isHover, HoverInfo& hoverInfo) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onHover");
        PipelineContext::SetCallBackNode(node);
        func->HoverExecute(isHover, hoverInfo);
    };
    ViewAbstractModel::GetInstance()->SetOnHover(std::move(onHover));
}

void JSViewAbstract::JsOnHoverMove(const JSCallbackInfo& info)
{
    if (info[0]->IsUndefined() && IsDisableEventVersion()) {
        ViewAbstractModel::GetInstance()->DisableOnHoverMove();
        return;
    }
    if (!info[0]->IsFunction()) {
        return;
    }

    RefPtr<JsHoverFunction> jsOnHoverMoveFunc = AceType::MakeRefPtr<JsHoverFunction>(JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onHoverMove = [execCtx = info.GetExecutionContext(), func = std::move(jsOnHoverMoveFunc), node = frameNode](
                       HoverInfo& hoverInfo) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onHoverMove");
        PipelineContext::SetCallBackNode(node);
        func->HoverMoveExecute(hoverInfo);
    };
    ViewAbstractModel::GetInstance()->SetOnHoverMove(std::move(onHoverMove));
}

void JSViewAbstract::JsOnAccessibilityHover(const JSCallbackInfo& info)
{
    if (info[0]->IsUndefined()) {
        ViewAbstractModel::GetInstance()->DisableOnAccessibilityHover();
        return;
    }
    if (!info[0]->IsFunction()) {
        return;
    }

    RefPtr<JsHoverFunction> jsOnHoverFunc = AceType::MakeRefPtr<JsHoverFunction>(JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onAccessibilityHover = [execCtx = info.GetExecutionContext(), func = std::move(jsOnHoverFunc),
                                    node = frameNode](bool isHover, AccessibilityHoverInfo& hoverInfo) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onAccessibilityHover");
        PipelineContext::SetCallBackNode(node);
        func->AccessibilityHoverExecute(isHover, hoverInfo);
    };
    ViewAbstractModel::GetInstance()->SetOnAccessibilityHover(std::move(onAccessibilityHover));
}

void JSViewAbstract::JsOnClick(const JSCallbackInfo& info)
{
    auto arg = info[0];
    if (arg->IsUndefined() && IsDisableEventVersion()) {
        ViewAbstractModel::GetInstance()->DisableOnClick();
        return;
    }
    if (!arg->IsFunction()) {
        return;
    }

    auto jsOnClickFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(arg));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onTap = [execCtx = info.GetExecutionContext(), func = std::move(jsOnClickFunc), node = targetNode](
                     BaseEventInfo* info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto* tapInfo = TypeInfoHelper::DynamicCast<GestureEvent>(info);
        ACE_SCORING_EVENT("onClick");
        PipelineContext::SetCallBackNode(node);
        func->Execute(*tapInfo);
#if !defined(PREVIEW) && defined(OHOS_PLATFORM)
        JSInteractableView::ReportClickEvent(node);
#endif
    };
    auto tmpOnTap = [func = std::move(onTap)](GestureEvent& info) { func(&info); };
    auto onClick = [execCtx = info.GetExecutionContext(), func = jsOnClickFunc, node = targetNode](
                       const ClickInfo* info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onClick");
        PipelineContext::SetCallBackNode(node);
        func->Execute(*info);
#if !defined(PREVIEW) && defined(OHOS_PLATFORM)
        JSInteractableView::ReportClickEvent(node);
#endif
    };

    Dimension distanceThreshold = Dimension(std::numeric_limits<double>::infinity(), DimensionUnit::PX);
    if (info.Length() > 1 && info[1]->IsNumber()) {
        double jsDistanceThreshold = info[1]->ToNumber<double>();
        if (jsDistanceThreshold < 0) {
            distanceThreshold = Dimension(std::numeric_limits<double>::infinity(), DimensionUnit::PX);
        }
        distanceThreshold = Dimension(jsDistanceThreshold, DimensionUnit::VP);
    }
    ViewAbstractModel::GetInstance()->SetOnClick(std::move(tmpOnTap), std::move(onClick), distanceThreshold);
}

void JSViewAbstract::JsOnGestureJudgeBegin(const JSCallbackInfo& info)
{
    if (info[0]->IsUndefined() || !info[0]->IsFunction()) {
        ViewAbstractModel::GetInstance()->SetOnGestureJudgeBegin(nullptr);
        return;
    }

    auto jsOnGestureJudgeFunc = AceType::MakeRefPtr<JsGestureJudgeFunction>(JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
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

void JSViewAbstract::JsOnTouchIntercept(const JSCallbackInfo& info)
{
    if (info[0]->IsUndefined() || !info[0]->IsFunction()) {
        ViewAbstractModel::GetInstance()->SetOnTouchIntercept(nullptr);
        return;
    }

    auto jsOnTouchInterceptFunc = AceType::MakeRefPtr<JsTouchInterceptFunction>(JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onTouchInterceptfunc = [execCtx = info.GetExecutionContext(), func = jsOnTouchInterceptFunc, node = frameNode](
                                    TouchEventInfo& info) -> NG::HitTestMode {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, NG::HitTestMode::HTMDEFAULT);
        ACE_SCORING_EVENT("onTouchIntercept");
        PipelineContext::SetCallBackNode(node);
        return func->Execute(info);
    };
    ViewAbstractModel::GetInstance()->SetOnTouchIntercept(std::move(onTouchInterceptfunc));
}

void JSViewAbstract::JsShouldBuiltInRecognizerParallelWith(const JSCallbackInfo& info)
{
    if (info[0]->IsUndefined() || !info[0]->IsFunction()) {
        ViewAbstractModel::GetInstance()->SetShouldBuiltInRecognizerParallelWith(nullptr);
        return;
    }

    auto jsParallelInnerGestureToFunc =
        AceType::MakeRefPtr<JsShouldBuiltInRecognizerParallelWithFunction>(JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto shouldBuiltInRecognizerParallelWithFunc =
        [execCtx = info.GetExecutionContext(), func = jsParallelInnerGestureToFunc, node = frameNode](
            const RefPtr<NG::NGGestureRecognizer>& current,
            const std::vector<RefPtr<NG::NGGestureRecognizer>>& others) -> RefPtr<NG::NGGestureRecognizer> {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, nullptr);
        ACE_SCORING_EVENT("shouldBuiltInRecognizerParallelWith");
        PipelineContext::SetCallBackNode(node);
        return func->Execute(current, others);
    };
    ViewAbstractModel::GetInstance()->SetShouldBuiltInRecognizerParallelWith(
        std::move(shouldBuiltInRecognizerParallelWithFunc));
}

void JSViewAbstract::JsOnGestureRecognizerJudgeBegin(const JSCallbackInfo& info)
{
    if (info[0]->IsUndefined() || !info[0]->IsFunction()) {
        ViewAbstractModel::GetInstance()->SetOnGestureRecognizerJudgeBegin(nullptr, false);
        return;
    }

    auto jsOnGestureRecognizerJudgeFunc = AceType::MakeRefPtr<JsGestureJudgeFunction>(JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onGestureRecognizerJudgefunc =
        [execCtx = info.GetExecutionContext(), func = jsOnGestureRecognizerJudgeFunc, node = frameNode](
            const std::shared_ptr<BaseGestureEvent>& info, const RefPtr<NG::NGGestureRecognizer>& current,
            const std::list<RefPtr<NG::NGGestureRecognizer>>& others) -> GestureJudgeResult {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, GestureJudgeResult::CONTINUE);
        ACE_SCORING_EVENT("onGestureRecognizerJudgeBegin");
        PipelineContext::SetCallBackNode(node);
        return func->Execute(info, current, others);
    };

    bool exposeInnerGestureFlag = false;
    if (info.Length() > 1 && info[1]->IsBoolean()) {
        exposeInnerGestureFlag = info[1]->ToBoolean();
    }
    ViewAbstractModel::GetInstance()->SetOnGestureRecognizerJudgeBegin(
        std::move(onGestureRecognizerJudgefunc), exposeInnerGestureFlag);
}

void JSViewAbstract::JsOnTouchTestDone(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || info[0]->IsUndefined() || !info[0]->IsFunction()) {
        ViewAbstractModel::GetInstance()->SetOnTouchTestDone(nullptr);
        return;
    }
    auto JsOnTouchTestDoneFunc = AceType::MakeRefPtr<JsTouchTestDoneFunction>(JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onTouchTestDoneFunc = [execCtx = info.GetExecutionContext(), func = JsOnTouchTestDoneFunc, node = frameNode](
                                   const std::shared_ptr<BaseGestureEvent>& info,
                                   const std::list<RefPtr<NG::NGGestureRecognizer>>& others) -> bool {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, false);
        ACE_SCORING_EVENT("onTouchTestDone");
        PipelineContext::SetCallBackNode(node);
        return func->Execute(info, others);
    };
    ViewAbstractModel::GetInstance()->SetOnTouchTestDone(std::move(onTouchTestDoneFunc));
}

void JSViewAbstract::JsClickEffect(const JSCallbackInfo& info)
{
    JSRef<JSVal> arg = info[0];
    if (arg->IsUndefined() || arg->IsNull()) {
        ViewAbstractModel::GetInstance()->SetClickEffectLevel(ClickEffectLevel::UNDEFINED, DEFAULT_SCALE_LIGHT);
        return;
    }
    if (!arg->IsObject()) {
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
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
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

void JSViewAbstract::JsOnVisibleAreaApproximateChange(const JSCallbackInfo& info)
{
    if (info.Length() != PARAMETER_LENGTH_SECOND) {
        return;
    }

    if (!info[0]->IsObject() || !info[1]->IsFunction()) {
        return;
    }

    const auto& options = info[0];
    JSRef<JSObject> optionObj = JSRef<JSObject>::Cast(options);
    JSRef<JSVal> ratios = optionObj->GetProperty("ratios");
    if (!ratios->IsArray()) {
        return;
    }
    auto ratioArray = JSRef<JSArray>::Cast(ratios);
    size_t size = ratioArray->Length();
    std::vector<double> ratioVec(size);
    for (size_t i = 0; i < size; i++) {
        double ratio = 0.0;
        ParseJsDouble(ratioArray->GetValueAt(i), ratio);
        ratio = std::clamp(ratio, VISIBLE_RATIO_MIN, VISIBLE_RATIO_MAX);
        ratioVec.push_back(ratio);
    }
    int32_t expectedUpdateInterval = DEFAULT_DURATION;
    JSRef<JSVal> expectedUpdateIntervalVal = optionObj->GetProperty("expectedUpdateInterval");
    if (expectedUpdateIntervalVal->IsNumber()) {
        JSViewAbstract::ParseJsInteger(expectedUpdateIntervalVal, expectedUpdateInterval);
    }
    if (expectedUpdateInterval < 0) {
        expectedUpdateInterval = DEFAULT_DURATION;
    }

    RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[1]));
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onVisibleChange = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                               bool visible, double ratio) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onVisibleAreaApproximateChange");

        JSRef<JSVal> params[2];
        params[0] = JSRef<JSVal>::Make(ToJSValue(visible));
        params[1] = JSRef<JSVal>::Make(ToJSValue(ratio));
        PipelineContext::SetCallBackNode(node);
        func->ExecuteJS(2, params);
    };
    ViewAbstractModel::GetInstance()->SetOnVisibleAreaApproximateChange(
        std::move(onVisibleChange), ratioVec, expectedUpdateInterval);
}

void JSViewAbstract::JsHitTestBehavior(const JSCallbackInfo& info)
{
    if (info.Length() != 1 || !info[0]->IsNumber()) {
        return;
    }

    NG::HitTestMode hitTestModeNG = NG::HitTestMode::HTMDEFAULT;
    hitTestModeNG = static_cast<NG::HitTestMode>(info[0]->ToNumber<int32_t>());
    ViewAbstractModel::GetInstance()->SetHitTestMode(hitTestModeNG);
}

void JSViewAbstract::JsOnChildTouchTest(const JSCallbackInfo& info)
{
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::FUNCTION };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("onChildTouchTest", jsVal, checkList)) {
        return;
    }

    RefPtr<JsOnChildTouchTestFunction> jsOnChildTouchTestFunc =
        AceType::MakeRefPtr<JsOnChildTouchTestFunction>(JSRef<JSFunc>::Cast(jsVal));

    auto onTouchTestFunc = [execCtx = info.GetExecutionContext(), func = std::move(jsOnChildTouchTestFunc)](
                               const std::vector<NG::TouchTestInfo>& touchInfo) -> NG::TouchResult {
        NG::TouchResult touchRes;
        NG::TouchResult defaultRes;
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, defaultRes);
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
    ViewAbstractModel::GetInstance()->RemoveResObj("foregroundColor");
    Color foregroundColor = Color::TRANSPARENT;
    ForegroundColorStrategy strategy;
    if (ParseJsColorStrategy(info[0], strategy)) {
        ViewAbstractModel::GetInstance()->SetForegroundColorStrategy(strategy);
        return;
    }
    if (!SystemProperties::ConfigChangePerform()) {
        ParseJsColor(info[0], foregroundColor);
        ViewAbstractModel::GetInstance()->SetForegroundColor(foregroundColor);
    } else {
        RefPtr<ResourceObject> foregroundResObj;
        ParseJsColor(info[0], foregroundColor, foregroundResObj);
        if (foregroundResObj) {
            ViewAbstractModel::GetInstance()->CreateWithForegroundColorResourceObj(foregroundResObj);
        } else {
            ViewAbstractModel::GetInstance()->SetForegroundColor(foregroundColor);
        }
    }
}

void JSViewAbstract::JsKeyboardShortcut(const JSCallbackInfo& info)
{
    // KeyboardShortcut only allows 2 or 3 params.
    if (info.Length() < 2 || info.Length() > 3) {
        return;
    }
    if ((!info[0]->IsString() && !info[0]->IsNumber()) || !info[1]->IsArray()) {
        // clear shortcut key
        ViewAbstractModel::GetInstance()->SetKeyboardShortcut({}, {}, nullptr);
        return;
    }

    std::string value;
    if (info[0]->IsString()) {
        // common letter/number/symbol
        value = info[0]->ToString();
        if (value.size() != 1) {
            // clear shortcut key
            ViewAbstractModel::GetInstance()->SetKeyboardShortcut({}, {}, nullptr);
            return;
        }
    } else {
        // function keys such as F1-F10/ESC
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
        auto frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
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

void JSViewAbstract::JsOnFocusAxisEvent(const JSCallbackInfo& args)
{
    JSRef<JSVal> arg = args[0];
    if (arg->IsUndefined() && IsDisableEventVersion()) {
        ViewAbstractModel::GetInstance()->DisableOnFocusAxisEvent();
        return;
    }
    if (!arg->IsFunction()) {
        return;
    }
    EcmaVM* vm = args.GetVm();
    CHECK_NULL_VOID(vm);
    auto jsOnFocusAxisEventFunc = JSRef<JSFunc>::Cast(arg);
    if (jsOnFocusAxisEventFunc->IsEmpty()) {
        return;
    }
    auto jsOnFocusAxisFuncLocalHandle = jsOnFocusAxisEventFunc->GetLocalHandle();
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onFocusAxisEvent = [vm, execCtx = args.GetExecutionContext(),
                       func = panda::CopyableGlobal(vm, jsOnFocusAxisFuncLocalHandle),
                       node = frameNode](NG::FocusAxisEventInfo& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onFocusAxis");
        PipelineContext::SetCallBackNode(node);
        auto eventObj = NG::CommonBridge::CreateFocusAxisEventInfo(vm, info);
        panda::Local<panda::JSValueRef> params[1] = { eventObj };
        func->Call(vm, func.ToLocal(), params, 1);
    };
    ViewAbstractModel::GetInstance()->SetOnFocusAxisEvent(std::move(onFocusAxisEvent));
}

bool JSViewAbstract::CheckColor(
    const JSRef<JSVal>& jsValue, Color& result, const char* componentName, const char* propName)
{
    RefPtr<ResourceObject> resourceObject;
    return CheckColor(jsValue, result, componentName, propName, resourceObject);
}

bool JSViewAbstract::CheckColor(
    const JSRef<JSVal>& jsValue, Color& result, const char* componentName, const char* propName,
    RefPtr<ResourceObject>& resourceObject)
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
    if (!ParseJsColor(jsValue, result, resourceObject)) {
        return false;
    }
    return true;
}

bool JSViewAbstract::CheckLength(
    const JSRef<JSVal>& jsValue, CalcDimension& result, const char* componentName, const char* propName)
{
    RefPtr<ResourceObject> resourceObject;
    return CheckLength(jsValue, result, componentName, propName, resourceObject);
}

bool JSViewAbstract::CheckLength(
    const JSRef<JSVal>& jsValue, CalcDimension& result, const char* componentName, const char* propName,
    RefPtr<ResourceObject>& resourceObject)
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
        return ParseJsDimensionVpNG(jsValue, result, resourceObject);
    }
    // Correct type, incorrect value parsing
    if (!ParseJsDimensionVp(jsValue, result, resourceObject)) {
        return false;
    }
    return true;
}

// obscured means that the developer calls the component to be private style.
void JSViewAbstract::JsObscured(const JSCallbackInfo& info)
{
    JSRef<JSVal> arg = info[0];
    if (arg->IsUndefined() || arg->IsNull()) {
        std::vector<ObscuredReasons> reasons(0);
        ViewAbstractModel::GetInstance()->SetObscured(reasons);
        return;
    }
    if (!arg->IsArray()) {
        return;
    }

    auto obscuredArray = JSRef<JSArray>::Cast(arg);
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

// PrivacySensitive means that the component will change style when system calls the app to be privated.
void JSViewAbstract::JsPrivacySensitive(const JSCallbackInfo& info)
{
    auto sensitiveInfo = info[0];
    if (sensitiveInfo->IsUndefined()) {
        ViewAbstractModel::GetInstance()->SetPrivacySensitive(false);
        return;
    }
    bool sensitive = false;
    if (sensitiveInfo->IsBoolean()) {
        sensitive = sensitiveInfo->ToBoolean();
    }
    ViewAbstractModel::GetInstance()->SetPrivacySensitive(sensitive);
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

bool JSViewAbstract::GetJsMediaBundleInfo(const JSRef<JSVal>& jsValue, std::string& bundleName, std::string& moduleName)
{
    if (!jsValue->IsObject() || jsValue->IsString()) {
        return false;
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    if (!jsObj->IsUndefined()) {
        JSRef<JSVal> bundle = jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::BUNDLE_NAME));
        JSRef<JSVal> module = jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::MODULE_NAME));
        if (bundle->IsString() && module->IsString()) {
            bundleName = bundle->ToString();
            moduleName = module->ToString();
            return true;
        }
    }
    return false;
}

void JSViewAbstract::SetBorderColorProps(const Color& color, NG::BorderColorProperty& props, const char* propName)
{
    if (propName == nullptr) {
        return;
    }
    if (propName == BOTTOM_PROPERTY) {
        props.bottomColor = color;
    } else if (propName == TOP_PROPERTY) {
        props.topColor = color;
    } else if (propName == LEFT_PROPERTY || propName == START_PROPERTY) {
        props.leftColor = color;
    } else if (propName == RIGHT_PROPERTY || propName == END_PROPERTY) {
        props.rightColor = color;
    }
}

void JSViewAbstract::ParseBorderColorProps(
    const JSRef<JSObject>& object, NG::BorderColorProperty& props, const char* propName)
{
    if (!object->HasProperty(propName) || propName == nullptr) {
        return;
    }
    RefPtr<ResourceObject> resObj = nullptr;
    Color color;
    if (JSViewAbstract::ParseJsColor(object->GetProperty(propName), color, resObj)) {
        SetBorderColorProps(color, props, propName);
    }
    if (!resObj) {
        return;
    }
    auto&& updateFunc = [propName](const RefPtr<ResourceObject>& resObj, NG::BorderColorProperty& props) {
        Color color;
        ResourceParseUtils::ParseResColor(resObj, color);
        SetBorderColorProps(color, props, propName);
    };
    props.AddResource("dialog.borderColor." + std::string(propName), resObj, std::move(updateFunc));
}

void JSViewAbstract::GetBorderColors(const JSRef<JSObject>& object, NG::BorderColorProperty& borderColors)
{
    ParseBorderColorProps(object, borderColors, BOTTOM_PROPERTY);
    ParseBorderColorProps(object, borderColors, TOP_PROPERTY);
    ParseBorderColorProps(object, borderColors, LEFT_PROPERTY);
    ParseBorderColorProps(object, borderColors, RIGHT_PROPERTY);
    ParseBorderColorProps(object, borderColors, START_PROPERTY);
    ParseBorderColorProps(object, borderColors, END_PROPERTY);
    borderColors.multiValued = true;
}

void JSViewAbstract::GetBorderColorsFromResource(const JSRef<JSVal>& args, NG::BorderColorProperty& colorProps)
{
    Color borderColor;
    RefPtr<ResourceObject> resObj = nullptr;
    if (ParseJsColor(args, borderColor, resObj)) {
        colorProps.SetColor(borderColor);
    }
    if (resObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderColorProperty& colorProps) {
            Color color;
            bool ret = ResourceParseUtils::ParseResColor(resObj, color);
            Color target = ret ? color : Color::BLACK;
            colorProps.SetColor(target);
        };
        colorProps.AddResource("dialog.borderColor", resObj, std::move(updateFunc));
    }
    if (args->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(args);
        GetBorderColors(obj, colorProps);
    }
}

bool JSViewAbstract::ParseBorderColorProps(const JSRef<JSVal>& args, NG::BorderColorProperty& colorProperty)
{
    if (!args->IsObject() && !args->IsNumber() && !args->IsString()) {
        return false;
    }
    if (SystemProperties::ConfigChangePerform()) {
        GetBorderColorsFromResource(args, colorProperty);
        return true;
    }
    Color borderColor;
    if (ParseJsColor(args, borderColor)) {
        colorProperty.SetColor(borderColor);
        return true;
    } else if (args->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(args);
        CommonColor commonColor;
        auto isLocalizedEdgeColor = ParseCommonEdgeColors(obj, commonColor);
        colorProperty.topColor = commonColor.top;
        colorProperty.bottomColor = commonColor.bottom;
        if (isLocalizedEdgeColor) {
            colorProperty.startColor = commonColor.left;
            colorProperty.endColor = commonColor.right;
        } else {
            colorProperty.leftColor = commonColor.left;
            colorProperty.rightColor = commonColor.right;
        }
        colorProperty.multiValued = true;
        return true;
    }
    return false;
}

bool JSViewAbstract::ParseBorderWidthProps(const JSRef<JSVal>& args, NG::BorderWidthProperty& borderWidthProperty)
{
    if (!args->IsObject() && !args->IsNumber() && !args->IsString()) {
        return false;
    }
    if (SystemProperties::ConfigChangePerform()) {
        GetBorderWidthFromResource(args, borderWidthProperty);
        return true;
    }
    CalcDimension borderWidth;
    if (ParseJsDimensionVpNG(args, borderWidth, true)) {
        if (borderWidth.IsNegative()) {
            borderWidth.Reset();
        }
        borderWidthProperty = NG::BorderWidthProperty({ borderWidth, borderWidth, borderWidth, borderWidth,
            std::nullopt, std::nullopt});
        return true;
    } else if (args->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(args);
        CommonCalcDimension commonCalcDimension;
        ParseCommonEdgeWidthsProps(obj, commonCalcDimension);
        borderWidthProperty.topDimen = commonCalcDimension.top;
        borderWidthProperty.bottomDimen = commonCalcDimension.bottom;
        borderWidthProperty.leftDimen = commonCalcDimension.left;
        borderWidthProperty.rightDimen = commonCalcDimension.right;
        borderWidthProperty.multiValued = true;
        return true;
    }
    return false;
}

bool JSViewAbstract::ParseBorderStyleProps(const JSRef<JSVal>& args, NG::BorderStyleProperty& borderStyleProperty)
{
    if (!args->IsObject() && !args->IsNumber()) {
        return false;
    }
    if (args->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(args);
        auto leftValue = obj->GetProperty("left");
        if (!leftValue->IsUndefined() && leftValue->IsNumber()) {
            ConvertOptionBorderStyle(leftValue->ToNumber<int32_t>(), borderStyleProperty.styleLeft);
        }
        auto rightValue = obj->GetProperty("right");
        if (!rightValue->IsUndefined() && rightValue->IsNumber()) {
            ConvertOptionBorderStyle(rightValue->ToNumber<int32_t>(), borderStyleProperty.styleRight);
        }
        auto topValue = obj->GetProperty("top");
        if (!topValue->IsUndefined() && topValue->IsNumber()) {
            ConvertOptionBorderStyle(topValue->ToNumber<int32_t>(), borderStyleProperty.styleTop);
        }
        auto bottomValue = obj->GetProperty("bottom");
        if (!bottomValue->IsUndefined() && bottomValue->IsNumber()) {
            ConvertOptionBorderStyle(bottomValue->ToNumber<int32_t>(), borderStyleProperty.styleBottom);
        }
        borderStyleProperty.multiValued = true;
        return true;
    }
    std::optional<BorderStyle> borderStyle;
    if (ConvertOptionBorderStyle(args->ToNumber<int32_t>(), borderStyle)) {
        borderStyleProperty = NG::BorderStyleProperty({ borderStyle, borderStyle, borderStyle, borderStyle });
        return true;
    }
    return false;
}

void JSViewAbstract::ParseBorderRadiusProps(const JSRef<JSObject>& object, NG::BorderRadiusProperty& radius)
{
    std::optional<CalcDimension> radiusTopLeft;
    std::optional<CalcDimension> radiusTopRight;
    std::optional<CalcDimension> radiusBottomLeft;
    std::optional<CalcDimension> radiusBottomRight;
    CalcDimension topLeft;
    if (ParseJsDimensionVpNG(object->GetProperty("topLeft"), topLeft, true)) {
        radiusTopLeft = topLeft;
    }
    CalcDimension topRight;
    if (ParseJsDimensionVpNG(object->GetProperty("topRight"), topRight, true)) {
        radiusTopRight = topRight;
    }
    CalcDimension bottomLeft;
    if (ParseJsDimensionVpNG(object->GetProperty("bottomLeft"), bottomLeft, true)) {
        radiusBottomLeft = bottomLeft;
    }
    CalcDimension bottomRight;
    if (ParseJsDimensionVpNG(object->GetProperty("bottomRight"), bottomRight, true)) {
        radiusBottomRight = bottomRight;
    }
    CheckLengthMetrics(object);
    radius.radiusTopLeft = radiusTopLeft;
    radius.radiusTopRight = radiusTopRight;
    radius.radiusBottomLeft = radiusBottomLeft;
    radius.radiusBottomRight = radiusBottomRight;
    radius.multiValued = true;
    return;
}

void JSViewAbstract::ParseCommonBorderRadiusProps(
    const JSRef<JSObject>& object, NG::BorderRadiusProperty& radius, bool notNegative)
{
    if (CheckLengthMetrics(object)) {
        std::optional<CalcDimension> radiusTopStart;
        std::optional<CalcDimension> radiusTopEnd;
        std::optional<CalcDimension> radiusBottomStart;
        std::optional<CalcDimension> radiusBottomEnd;
        if (object->HasProperty(TOP_START_PROPERTY) && object->GetProperty(TOP_START_PROPERTY)->IsObject()) {
            JSRef<JSObject> topStartObj = JSRef<JSObject>::Cast(object->GetProperty(TOP_START_PROPERTY));
            CalcDimension calcDimension;
            if (ParseJsLengthMetrics(topStartObj, calcDimension)) {
                CheckDimensionUnit(calcDimension, false, notNegative);
                radiusTopStart = calcDimension;
            }
        }
        if (object->HasProperty(TOP_END_PROPERTY) && object->GetProperty(TOP_END_PROPERTY)->IsObject()) {
            JSRef<JSObject> topEndObj = JSRef<JSObject>::Cast(object->GetProperty(TOP_END_PROPERTY));
            CalcDimension calcDimension;
            if (ParseJsLengthMetrics(topEndObj, calcDimension)) {
                CheckDimensionUnit(calcDimension, false, notNegative);
                radiusTopEnd = calcDimension;
            }
        }
        if (object->HasProperty(BOTTOM_START_PROPERTY) && object->GetProperty(BOTTOM_START_PROPERTY)->IsObject()) {
            JSRef<JSObject> bottomStartObj = JSRef<JSObject>::Cast(object->GetProperty(BOTTOM_START_PROPERTY));
            CalcDimension calcDimension;
            if (ParseJsLengthMetrics(bottomStartObj, calcDimension)) {
                CheckDimensionUnit(calcDimension, false, notNegative);
                radiusBottomStart = calcDimension;
            }
        }
        if (object->HasProperty(BOTTOM_END_PROPERTY) && object->GetProperty(BOTTOM_END_PROPERTY)->IsObject()) {
            JSRef<JSObject> bottomEndObj = JSRef<JSObject>::Cast(object->GetProperty(BOTTOM_END_PROPERTY));
            CalcDimension calcDimension;
            if (ParseJsLengthMetrics(bottomEndObj, calcDimension)) {
                CheckDimensionUnit(calcDimension, false, notNegative);
                radiusBottomEnd = calcDimension;
            }
        }
        auto isRightToLeft = AceApplicationInfo::GetInstance().IsRightToLeft();
        radius.radiusTopLeft = isRightToLeft ? radiusTopEnd : radiusTopStart;
        radius.radiusTopRight = isRightToLeft ? radiusTopStart : radiusTopEnd;
        radius.radiusBottomLeft = isRightToLeft ? radiusBottomEnd : radiusBottomStart;
        radius.radiusBottomRight = isRightToLeft ? radiusBottomStart : radiusBottomEnd;
        radius.multiValued = true;
        return;
    }
    ParseBorderRadiusProps(object, radius);
}

void JSViewAbstract::GetBorderRadiusUpdate(const JSRef<JSVal>& args, NG::BorderRadiusProperty& props)
{
    CalcDimension borderRadius;
    RefPtr<ResourceObject> resObj;
    if (ParseJsDimensionVpNG(args, borderRadius, resObj)) {
        props = NG::BorderRadiusProperty(borderRadius);
        props.multiValued = false;
    }
    auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderRadiusProperty& props) {
        CalcDimension radiusValue;
        ResourceParseUtils::ParseResDimensionVpNG(resObj, radiusValue);
        props = NG::BorderRadiusProperty(radiusValue);
        props.multiValued = false;
    };
    props.AddResource("dialog.borderRadius", resObj, std::move(updateFunc));
}

void JSViewAbstract::SetBorderRadiusProps(
    const CalcDimension& dim, NG::BorderRadiusProperty& props, const char* propName)
{
    if (dim.IsNegative() || propName == nullptr) {
        return;
    }

    auto isRightToLeft = AceApplicationInfo::GetInstance().IsRightToLeft();
    if (propName == BOTTOM_LEFT_PROPERTY) {
        props.radiusBottomLeft = dim;
    } else if (propName == BOTTOM_RIGHT_PROPERTY) {
        props.radiusBottomRight = dim;
    } else if (propName == TOP_LEFT_PROPERTY) {
        props.radiusTopLeft = dim;
    } else if (propName == TOP_RIGHT_PROPERTY) {
        props.radiusTopRight = dim;
    } else if (propName == TOP_START_PROPERTY || propName == TOP_END_PROPERTY) {
        if (isRightToLeft) {
            props.radiusTopRight = dim;
            return;
        }
        props.radiusTopLeft = dim;

    } else if (propName == BOTTOM_START_PROPERTY || propName == BOTTOM_END_PROPERTY) {
        if (isRightToLeft) {
            props.radiusTopRight = dim;
            return;
        }
        props.radiusTopLeft = dim;
    }
}

void JSViewAbstract::ParseBorderRadiusPropsUpdate(
    const char* key, const JSRef<JSObject>& object, NG::BorderRadiusProperty& props)
{
    CHECK_NULL_VOID(key);
    if (!object->HasProperty(key)) {
        return;
    }
    CalcDimension radius;
    RefPtr<ResourceObject> resObj;
    if (ParseJsDimensionVpNG(object->GetProperty(key), radius, resObj)) {
        SetBorderRadiusProps(radius, props, key);
    }
    auto&& updateFunc = [key](const RefPtr<ResourceObject>& resObj, NG::BorderRadiusProperty& props) {
        CalcDimension value;
        if (ResourceParseUtils::ParseResDimensionVpNG(resObj, value)) {
            SetBorderRadiusProps(value, props, key);
        }
    };
    props.AddResource("dialog.borderRadius." + std::string(key), resObj, std::move(updateFunc));
}

void JSViewAbstract::GetBorderRadiusByLengthMetricsUpdate(
    const char* key, const JSRef<JSObject>& object, NG::BorderRadiusProperty& props, bool notNegative)
{
    CHECK_NULL_VOID(key);
    if (!object->HasProperty(key) && !object->GetProperty(key)->IsObject()) {
        return;
    }
    JSRef<JSObject> radiusObj = JSRef<JSObject>::Cast(object->GetProperty(key));
    CalcDimension radius;
    RefPtr<ResourceObject> resObj = nullptr;
    if (ParseJsLengthMetricsVpWithResObj(radiusObj, radius, resObj)) {
        CheckDimensionUnit(radius, false, notNegative);
        SetBorderRadiusProps(radius, props, key);
    }
    if (!resObj) {
        return;
    }
    auto unit = radius.Unit();
    auto&& updateFunc = [unit, key, notNegative](
                            const RefPtr<ResourceObject>& resObj, NG::BorderRadiusProperty& props) {
        CalcDimension value;
        if (ResourceParseUtils::ParseResDimension(resObj, value, unit)) {
            CheckDimensionUnit(value, false, notNegative);
            SetBorderRadiusProps(value, props, key);
        }
    };
    props.AddResource("dialog.borderRadius." + std::string(key), resObj, std::move(updateFunc));
}

void JSViewAbstract::GetBorderRadiusObject(
    const JSRef<JSObject>& object, NG::BorderRadiusProperty& props, bool notNegative)
{
    if (CheckLengthMetrics(object)) {
        GetBorderRadiusByLengthMetricsUpdate(BOTTOM_START_PROPERTY, object, props, notNegative);
        GetBorderRadiusByLengthMetricsUpdate(BOTTOM_END_PROPERTY, object, props, notNegative);
        GetBorderRadiusByLengthMetricsUpdate(TOP_START_PROPERTY, object, props, notNegative);
        GetBorderRadiusByLengthMetricsUpdate(TOP_END_PROPERTY, object, props, notNegative);
        return;
    }
    ParseBorderRadiusPropsUpdate(TOP_LEFT_PROPERTY, object, props);
    ParseBorderRadiusPropsUpdate(TOP_RIGHT_PROPERTY, object, props);
    ParseBorderRadiusPropsUpdate(BOTTOM_LEFT_PROPERTY, object, props);
    ParseBorderRadiusPropsUpdate(BOTTOM_RIGHT_PROPERTY, object, props);
}

bool JSViewAbstract::ParseBorderRadius(const JSRef<JSVal>& args, NG::BorderRadiusProperty& radius, bool notNegative)
{
    if (!args->IsObject() && !args->IsNumber() && !args->IsString()) {
        return false;
    }
    if (SystemProperties::ConfigChangePerform()) {
        if (args->IsObject()) {
            JSRef<JSObject> object = JSRef<JSObject>::Cast(args);
            GetBorderRadiusObject(object, radius, notNegative);
            radius.multiValued = true;
            return true;
        }
        GetBorderRadiusUpdate(args, radius);
        return true;
    }
    CalcDimension borderRadius;
    if (ParseJsDimensionVpNG(args, borderRadius, true)) {
        radius = NG::BorderRadiusProperty(borderRadius);
        radius.multiValued = false;
    } else if (args->IsObject()) {
        JSRef<JSObject> object = JSRef<JSObject>::Cast(args);
        ParseCommonBorderRadiusProps(object, radius, notNegative);
    } else {
        return false;
    }
    return true;
}

void JSViewAbstract::SetDragPreviewOptionApply(const JSCallbackInfo& info, NG::DragPreviewOption& option)
{
    JSRef<JSVal> arg = info[0];
    if (!arg->IsObject()) {
        return;
    }
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(arg);
    auto vm = info.GetVm();
    auto globalObj = JSNApi::GetGlobalObject(vm);
    auto globalFunc = globalObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "applyImageModifierToNode"));
    JsiValue jsiValue(globalFunc);
    JsiRef<JsiValue> globalFuncRef = JsiRef<JsiValue>::Make(jsiValue);
    if (globalFuncRef->IsFunction()) {
        auto modifierObj = obj->GetProperty("modifier");
        if (modifierObj->IsUndefined()) {
            option.onApply = nullptr;
        } else {
            RefPtr<JsFunction> jsFunc =
                AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(globalFuncRef));
            auto onApply = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc),
                               modifier = std::move(modifierObj)](WeakPtr<NG::FrameNode> frameNode) {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                auto node = frameNode.Upgrade();
                JSRef<JSVal> params[SECOND_INDEX];
                params[0] = modifier;
                params[1] = JSRef<JSVal>::Make(panda::NativePointerRef::New(execCtx.vm_, AceType::RawPtr(node)));
                PipelineContext::SetCallBackNode(node);
                func->ExecuteJS(SECOND_INDEX, params);
            };
            option.onApply = onApply;
        }
    }
}

void JSViewAbstract::SetDragNumberBadge(const JSCallbackInfo& info, NG::DragPreviewOption& option)
{
    if (!info[0]->IsObject()) {
        return;
    }
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
    auto numberBadge = obj->GetProperty("numberBadge");
    if (!numberBadge->IsEmpty()) {
        if (numberBadge->IsNumber()) {
            int64_t number = numberBadge->ToNumber<int64_t>();
            if (number < 0 || number > INT_MAX) {
                option.isNumber = false;
                option.isShowBadge = true;
            } else {
                option.isNumber = true;
                option.badgeNumber = numberBadge->ToNumber<int>();
            }
        } else if (numberBadge->IsBoolean()) {
            option.isNumber = false;
            option.isShowBadge = numberBadge->ToBoolean();
        }
    } else {
        option.isNumber = false;
        option.isShowBadge = true;
    }
}

void JSViewAbstract::ParseDialogWidthAndHeight(DialogProperties& properties, const JSRef<JSObject>& obj)
{
    CalcDimension width;
    CalcDimension height;
    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> resWidthObj;
        RefPtr<ResourceObject> resHeightObj;
        if (ParseJsDimensionVpNG(obj->GetProperty("width"), width, resWidthObj)) {
            properties.width = width;
        }
        properties.resourceWidthObj = resWidthObj;
        if (ParseJsDimensionVpNG(obj->GetProperty("height"), height, resHeightObj)) {
            properties.height = height;
        }
        properties.resourceHeightObj = resHeightObj;
        return;
    }
    if (ParseJsDimensionVpNG(obj->GetProperty("width"), width, true)) {
        properties.width = width;
    }
    if (ParseJsDimensionVpNG(obj->GetProperty("height"), height, true)) {
        properties.height = height;
    }
}

void JSViewAbstract::SetDialogProperties(const JSRef<JSObject>& obj, DialogProperties& properties)
{
    // Parse cornerRadius.
    auto cornerRadiusValue = obj->GetProperty("cornerRadius");
    NG::BorderRadiusProperty radius;
    if (ParseBorderRadius(cornerRadiusValue, radius)) {
        properties.borderRadius = radius;
    }
    // Parse border width
    auto borderWidthValue = obj->GetProperty("borderWidth");
    NG::BorderWidthProperty borderWidth;
    if (ParseBorderWidthProps(borderWidthValue, borderWidth)) {
        properties.borderWidth = borderWidth;
        auto colorValue = obj->GetProperty("borderColor");
        NG::BorderColorProperty borderColor;
        if (ParseBorderColorProps(colorValue, borderColor)) {
            properties.borderColor = borderColor;
        } else {
            borderColor.SetColor(Color::BLACK);
            properties.borderColor = borderColor;
        }
        // Parse border style
        auto styleValue = obj->GetProperty("borderStyle");
        NG::BorderStyleProperty borderStyle;
        if (ParseBorderStyleProps(styleValue, borderStyle)) {
            properties.borderStyle = borderStyle;
        } else {
            properties.borderStyle = NG::BorderStyleProperty(
                { BorderStyle::SOLID, BorderStyle::SOLID, BorderStyle::SOLID, BorderStyle::SOLID });
        }
    }
    auto shadowValue = obj->GetProperty("shadow");
    Shadow shadow;
    if ((shadowValue->IsObject() || shadowValue->IsNumber()) && ParseShadowProps(shadowValue, shadow)) {
        properties.shadow = shadow;
    }
    ParseDialogWidthAndHeight(properties, obj);
}

std::function<void(NG::DrawingContext& context)> JSViewAbstract::GetDrawCallback(
    const RefPtr<JsFunction>& jsDraw, const JSExecutionContext& execCtx, JSRef<JSObject> modifier)
{
    std::function<void(NG::DrawingContext & context)> drawCallback = [func = std::move(jsDraw), execCtx, modifier](
                                                                         NG::DrawingContext& context) -> void {
        JAVASCRIPT_EXECUTION_SCOPE(execCtx);
        if (modifier->IsEmpty()) {
            return;
        }
        JSRef<JSObjTemplate> objectTemplate = JSRef<JSObjTemplate>::New();
        objectTemplate->SetInternalFieldCount(1);
        JSRef<JSObject> contextObj = objectTemplate->NewInstance();
        JSRef<JSObject> sizeObj = objectTemplate->NewInstance();
        sizeObj->SetProperty<float>("height", PipelineBase::Px2VpWithCurrentDensity(context.height));
        sizeObj->SetProperty<float>("width", PipelineBase::Px2VpWithCurrentDensity(context.width));
        contextObj->SetPropertyObject("size", sizeObj);

        JSRef<JSObject> sizeInPxObj = objectTemplate->NewInstance();
        sizeInPxObj->SetProperty<float>("height", context.height);
        sizeInPxObj->SetProperty<float>("width", context.width);
        contextObj->SetPropertyObject("sizeInPixel", sizeInPxObj);

        auto engine = EngineHelper::GetCurrentEngine();
        CHECK_NULL_VOID(engine);
        NativeEngine* nativeEngine = engine->GetNativeEngine();
        napi_env env = reinterpret_cast<napi_env>(nativeEngine);
        ScopeRAII scope(env);

        auto jsCanvas = OHOS::Rosen::Drawing::JsCanvas::CreateJsCanvas(env, &context.canvas);
        OHOS::Rosen::Drawing::JsCanvas* unwrapCanvas = nullptr;
        napi_unwrap(env, jsCanvas, reinterpret_cast<void**>(&unwrapCanvas));
        if (unwrapCanvas) {
            unwrapCanvas->SaveCanvas();
            unwrapCanvas->ClipCanvas(context.width, context.height);
        }
        JsiRef<JsiValue> jsCanvasVal = JsConverter::ConvertNapiValueToJsVal(jsCanvas);
        contextObj->SetPropertyObject("canvas", jsCanvasVal);

        auto jsVal = JSRef<JSVal>::Cast(contextObj);
        panda::Local<JsiValue> value = jsVal.Get().GetLocalHandle();
        JSValueWrapper valueWrapper = value;
        napi_value nativeValue = nativeEngine->ValueToNapiValue(valueWrapper);

        napi_wrap(
            env, nativeValue, &context.canvas, [](napi_env, void*, void*) {}, nullptr, nullptr);

        JSRef<JSVal> result = func->ExecuteJS(1, &jsVal);
        if (unwrapCanvas) {
            unwrapCanvas->RestoreCanvas();
            unwrapCanvas->ResetCanvas();
        }
    };
    return drawCallback;
}

std::function<std::string(const std::string&)> ParseJsGetFunc(const JSCallbackInfo& info, int32_t nodeId)
{
    auto* vm = info.GetVm();
    return [vm, nodeId](const std::string& key) -> std::string {
        std::string resultString = std::string();
        CHECK_NULL_RETURN(vm, resultString);
        panda::LocalScope scope(vm);
        auto global = JSNApi::GetGlobalObject(vm);
        auto getCustomProperty = global->Get(vm, panda::StringRef::NewFromUtf8(vm, "__getCustomPropertyString__"));
        if (getCustomProperty->IsUndefined() || !getCustomProperty->IsFunction(vm)) {
            return resultString;
        }
        auto obj = getCustomProperty->ToObject(vm);
        panda::Local<panda::FunctionRef> func = obj;
        panda::Local<panda::JSValueRef> params2[2] = { panda::NumberRef::New(vm, nodeId),
            panda::StringRef::NewFromUtf8(vm, key.c_str()) };
        auto function = panda::CopyableGlobal(vm, func);
        auto callValue = function->Call(vm, function.ToLocal(), params2, 2);
        if (callValue.IsNull() || callValue->IsUndefined() || !callValue->IsString(vm)) {
            return resultString;
        }
        auto value = callValue->ToString(vm)->ToString(vm);
        return value;
    };
}

std::function<std::string()> JsGetCustomMapFunc(const JSCallbackInfo& info, int32_t nodeId)
{
    auto* vm = info.GetVm();
    return [vm, nodeId]() -> std::string {
        std::string resultString = std::string();
        CHECK_NULL_RETURN(vm, resultString);
        panda::LocalScope scope(vm);
        auto global = JSNApi::GetGlobalObject(vm);
        auto getCustomProperty = global->Get(vm, panda::StringRef::NewFromUtf8(vm, "__getCustomPropertyMapString__"));
        if (getCustomProperty->IsUndefined() || !getCustomProperty->IsFunction(vm)) {
            return resultString;
        }
        auto obj = getCustomProperty->ToObject(vm);
        panda::Local<panda::FunctionRef> func = obj;
        panda::Local<panda::JSValueRef> params[1] = { panda::NumberRef::New(vm, nodeId) };
        auto function = panda::CopyableGlobal(vm, func);
        auto callValue = function->Call(vm, function.ToLocal(), params, 1);
        if (callValue.IsNull() || callValue->IsUndefined() || !callValue->IsString(vm)) {
            return resultString;
        }
        auto value = callValue->ToString(vm)->ToString(vm);
        return value;
    };
}

std::function<bool()> ParseJsFunc(const JSCallbackInfo& info, int32_t nodeId)
{
    auto* vm = info.GetVm();
    panda::Local<panda::JSValueRef> params3[3] = { panda::NumberRef::New(vm, nodeId), info[0]->GetLocalHandle(),
        info[1]->GetLocalHandle() };
    return [vm, params3]() -> bool {
        CHECK_NULL_RETURN(vm, false);
        panda::LocalScope scope(vm);
        auto global = JSNApi::GetGlobalObject(vm);
        auto setCustomProperty = global->Get(vm, panda::StringRef::NewFromUtf8(vm, "__setCustomProperty__"));
        if (setCustomProperty->IsUndefined() || !setCustomProperty->IsFunction(vm)) {
            return false;
        }
        auto obj = setCustomProperty->ToObject(vm);
        panda::Local<panda::FunctionRef> func = obj;
        auto frameNode = static_cast<NG::FrameNode*>(ViewAbstractModel::GetInstance()->GetFrameNode());
        auto nodeId = frameNode->GetId();
        auto function = panda::CopyableGlobal(vm, func);
        auto customPropertyExisted = function->Call(vm, function.ToLocal(), params3, 3)->ToBoolean(vm)->Value();
        if (customPropertyExisted) {
            frameNode->SetCustomPropertyMapFlagByKey(params3[1]->ToString(vm)->ToString(vm));
            frameNode->SetRemoveCustomProperties([vm, nodeId]() -> void {
                CHECK_NULL_VOID(vm);
                panda::LocalScope scope(vm);
                auto global = JSNApi::GetGlobalObject(vm);
                auto removeCustomProperty =
                    global->Get(vm, panda::StringRef::NewFromUtf8(vm, "__removeCustomProperties__"));
                if (removeCustomProperty->IsUndefined() || !removeCustomProperty->IsFunction(vm)) {
                    return;
                }
                auto obj = removeCustomProperty->ToObject(vm);
                panda::Local<panda::FunctionRef> func = obj;
                panda::Local<panda::JSValueRef> params[1] = { panda::NumberRef::New(vm, nodeId) };
                auto function = panda::CopyableGlobal(vm, func);
                function->Call(vm, function.ToLocal(), params, 1);
            });
        }
        return true;
    };
}

void JSViewAbstract::JsCustomProperty(const JSCallbackInfo& info)
{
    if (info[0]->GetLocalHandle()->IsUndefined()) {
        return;
    }
    auto* vm = info.GetVm();
    CHECK_NULL_VOID(vm);
    auto frameNode = static_cast<NG::FrameNode*>(ViewAbstractModel::GetInstance()->GetFrameNode());
    auto nodeId = frameNode->GetId();
    auto getFunc = ParseJsGetFunc(info, nodeId);
    auto func = ParseJsFunc(info, nodeId);
    auto getMapFunc = JsGetCustomMapFunc(info, nodeId);
    frameNode->SetJSCustomProperty(func, getFunc, std::move(getMapFunc));
}

void JSViewAbstract::JsLinearGradient(const JSCallbackInfo& info)
{
    ViewAbstractModel::GetInstance()->RemoveResObj("LinearGradient.gradient");
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::OBJECT };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("LinearGradient", jsVal, checkList)) {
        NG::Gradient newGradient;
        newGradient.CreateGradientWithType(NG::GradientType::LINEAR);
        ViewAbstractModel::GetInstance()->SetLinearGradient(newGradient);
        return;
    }
    NG::Gradient newGradient;
    NewJsLinearGradient(info, newGradient);
    ViewAbstractModel::GetInstance()->SetLinearGradient(newGradient);
}

void JSViewAbstract::JsGestureModifier(const JSCallbackInfo& info)
{
    auto* vm = info.GetExecutionContext().vm_;
    CHECK_NULL_VOID(vm);
    auto global = JSNApi::GetGlobalObject(vm);
    auto gestureModifier = global->Get(vm, panda::StringRef::NewFromUtf8(vm, "__gestureModifier__"));
    if (gestureModifier->IsUndefined() || !gestureModifier->IsFunction(vm)) {
        return;
    }
    auto obj = gestureModifier->ToObject(vm);
    panda::Local<panda::FunctionRef> func = obj;
    auto thisObj = info.This()->GetLocalHandle();
    panda::Local<panda::JSValueRef> params[1] = { info[0]->GetLocalHandle() };
    func->Call(vm, thisObj, params, 1);
}

void SetBackgroundImageResizableUpdateFunc(
    ImageResizableSlice& sliceResult, const RefPtr<ResourceObject>& resObj, std::string direction)
{
    if (direction.empty()) {
        return;
    }
    if (!resObj) {
        sliceResult.RemoveResource("backgroundImageResizable");
        return;
    }
    auto&& updateFunc = [direction](const RefPtr<ResourceObject>& resObj, ImageResizableSlice& sliceResult) {
        CHECK_NULL_VOID(resObj);
        CalcDimension sliceDimension;
        ResourceParseUtils::ParseResDimensionVp(resObj, sliceDimension);
        if (direction == "Left") {
            sliceResult.left = sliceDimension;
        } else if (direction == "Right") {
            sliceResult.right = sliceDimension;
        } else if (direction == "Top") {
            sliceResult.top = sliceDimension;
        } else if (direction == "Bottom") {
            sliceResult.bottom = sliceDimension;
        }
    };
    sliceResult.AddResource("backgroundImageResizable" + direction, resObj, std::move(updateFunc));
}

void JSViewAbstract::JsBackgroundImageResizable(const JSCallbackInfo& info)
{
    auto infoObj = info[0];
    ImageResizableSlice sliceResult;
    if (!infoObj->IsObject()) {
        ViewAbstractModel::GetInstance()->SetBackgroundImageResizableSlice(sliceResult);
        ViewAbstractModel::GetInstance()->ClearResObj("backgroundImageResizableSlice");
        return;
    }
    JSRef<JSObject> resizableObject = JSRef<JSObject>::Cast(infoObj);
    if (resizableObject->IsEmpty()) {
        ViewAbstractModel::GetInstance()->SetBackgroundImageResizableSlice(sliceResult);
        ViewAbstractModel::GetInstance()->ClearResObj("backgroundImageResizableSlice");
        return;
    }
    auto sliceValue = resizableObject->GetProperty("slice");
    if (!sliceValue->IsObject()) {
        return;
    }
    JSRef<JSObject> sliceObj = JSRef<JSObject>::Cast(sliceValue);
    if (sliceObj->IsEmpty()) {
        ViewAbstractModel::GetInstance()->SetBackgroundImageResizableSlice(sliceResult);
        ViewAbstractModel::GetInstance()->ClearResObj("backgroundImageResizableSlice");
        return;
    }
    for (uint32_t i = 0; i < SLICE_KEYS.size(); i++) {
        auto sliceSize = sliceObj->GetProperty(SLICE_KEYS.at(i).c_str());
        CalcDimension sliceDimension;
        RefPtr<ResourceObject> resObj;
        if (!ParseJsDimensionVp(sliceSize, sliceDimension, resObj)) {
            continue;
        }
        if (!sliceDimension.IsValid()) {
            continue;
        }
        switch (static_cast<BorderImageDirection>(i)) {
            case BorderImageDirection::LEFT:
                sliceResult.left = sliceDimension;
                SetBackgroundImageResizableUpdateFunc(sliceResult, resObj, "Left");
                break;
            case BorderImageDirection::RIGHT:
                sliceResult.right = sliceDimension;
                SetBackgroundImageResizableUpdateFunc(sliceResult, resObj, "Right");
                break;
            case BorderImageDirection::TOP:
                sliceResult.top = sliceDimension;
                SetBackgroundImageResizableUpdateFunc(sliceResult, resObj, "Top");
                break;
            case BorderImageDirection::BOTTOM:
                sliceResult.bottom = sliceDimension;
                SetBackgroundImageResizableUpdateFunc(sliceResult, resObj, "Bottom");
                break;
            default:
                break;
        }
    }
    ViewAbstractModel::GetInstance()->SetBackgroundImageResizableSlice(sliceResult);
}

void JSViewAbstract::JsOnFocus(const JSCallbackInfo& args)
{
    JSRef<JSVal> arg = args[0];
    if (arg->IsUndefined() && IsDisableEventVersion()) {
        ViewAbstractModel::GetInstance()->DisableOnFocus();
        return;
    }
    if (!arg->IsFunction()) {
        return;
    }
    RefPtr<JsFocusFunction> jsOnFocus = AceType::MakeRefPtr<JsFocusFunction>(JSRef<JSFunc>::Cast(arg));
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
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
    JSRef<JSVal> arg = args[0];
    if (arg->IsUndefined() && IsDisableEventVersion()) {
        ViewAbstractModel::GetInstance()->DisableOnBlur();
        return;
    }
    if (!arg->IsFunction()) {
        return;
    }
    RefPtr<JsFocusFunction> jsOnBlur = AceType::MakeRefPtr<JsFocusFunction>(JSRef<JSFunc>::Cast(arg));
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
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
    JSRef<JSVal> arg = info[0];
    if (!arg->IsNumber()) {
        return;
    }
    ViewAbstractModel::GetInstance()->SetTabIndex(arg->ToNumber<int32_t>());
}

void JSViewAbstract::JsFocusOnTouch(const JSCallbackInfo& info)
{
    JSRef<JSVal> arg = info[0];
    if (!arg->IsBoolean()) {
        return;
    }
    auto isFocusOnTouch = arg->ToBoolean();
    ViewAbstractModel::GetInstance()->SetFocusOnTouch(isFocusOnTouch);
}

void JSViewAbstract::JsDefaultFocus(const JSCallbackInfo& info)
{
    JSRef<JSVal> arg = info[0];
    if (!arg->IsBoolean()) {
        return;
    }
    auto isDefaultFocus = arg->ToBoolean();
    ViewAbstractModel::GetInstance()->SetDefaultFocus(isDefaultFocus);
}

void JSViewAbstract::JsGroupDefaultFocus(const JSCallbackInfo& info)
{
    JSRef<JSVal> arg = info[0];
    if (!arg->IsBoolean()) {
        return;
    }
    auto isGroupDefaultFocus = arg->ToBoolean();
    ViewAbstractModel::GetInstance()->SetGroupDefaultFocus(isGroupDefaultFocus);
}

void JSViewAbstract::JsKey(const std::string& key)
{
    ViewAbstractModel::GetInstance()->SetInspectorId(key);
}

void JSViewAbstract::JsId(const JSCallbackInfo& info)
{
    JSRef<JSVal> arg = info[0];
    if (!arg->IsString() || arg->IsNull() || arg->IsUndefined()) {
        return;
    }
    std::string id = arg->ToString();
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
    std::string debugLine;
    auto length = info.Length();
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::STRING };

    if (length == 1) { // deprecated version of debug line
        auto jsVal = info[0];
        if (!CheckJSCallbackInfo("JsDebugLine", jsVal, checkList)) {
            return;
        }
        debugLine = jsVal->ToString();
    } else if (length == 2) { // debug line with extra package name
        auto line = info[0];
        auto packageName = info[1];
        if (!CheckJSCallbackInfo("JsDebugLine", line, checkList) ||
            !CheckJSCallbackInfo("JsDebugLine", packageName, checkList)) {
            return;
        }
        auto json = JsonUtil::Create(true);
        json->Put(DEBUG_LINE_INFO_LINE, line->ToString().c_str());
        json->Put(DEBUG_LINE_INFO_PACKAGE_NAME, packageName->ToString().c_str());
        debugLine = json->ToString();
    }

    ViewAbstractModel::GetInstance()->SetDebugLine(debugLine);
}

void JSViewAbstract::JsOpacityPassThrough(const JSCallbackInfo& info)
{
    double opacity = 1.0;
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        if (ParseJsDouble(info[0], opacity)) {
            opacity = std::clamp(opacity, 0.0, 1.0);
        }
    } else {
        if (!ParseJsDouble(info[0], opacity)) {
            return;
        }
        if ((LessNotEqual(opacity, 0.0)) || opacity > 1) {
            opacity = 1.0;
        }
    }

    ViewAbstractModel::GetInstance()->SetOpacity(opacity, true);
}

void JSViewAbstract::JsTransitionPassThrough(const JSCallbackInfo& info)
{
    if (info.Length() == 0) {
        ViewAbstractModel::GetInstance()->SetTransition(
            NG::TransitionOptions::GetDefaultTransition(TransitionType::ALL));
        return;
    }
    if (!info[0]->IsObject()) {
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            ViewAbstractModel::GetInstance()->CleanTransition();
            ViewAbstractModel::GetInstance()->SetChainedTransition(nullptr, nullptr);
        }
        return;
    }
    auto obj = JSRef<JSObject>::Cast(info[0]);
    if (!obj->GetProperty("successor_")->IsUndefined()) {
        auto chainedEffect = ParseChainedTransition(obj, info.GetExecutionContext());
        std::function<void(bool)> finishCallback;
        if (info.Length() > 1 && info[1]->IsFunction()) {
            finishCallback = ParseTransitionCallback(JSRef<JSFunc>::Cast(info[1]), info.GetExecutionContext());
        }
        ViewAbstractModel::GetInstance()->SetChainedTransition(chainedEffect, std::move(finishCallback));
        return;
    }
    auto options = ParseJsTransition(obj);
    ViewAbstractModel::GetInstance()->SetTransition(options, true);
}

void JSViewAbstract::JsFocusScopeId(const JSCallbackInfo& info)
{
    if (info.Length() == 0) {
        return;
    }

    std::string focusScopeId;
    if (info[0]->IsString()) {
        focusScopeId = info[0]->ToString();
    }

    bool isGroup = false;
    if (info.Length() >= PARAMETER_LENGTH_SECOND && !info[1]->IsNull() && !info[1]->IsUndefined() &&
        info[1]->IsBoolean()) {
        isGroup = info[1]->ToBoolean();
    }
    bool arrowKeyStepOut = true;
    if (info.Length() >= PARAMETER_LENGTH_THIRD && !info[2]->IsNull() && !info[2]->IsUndefined() && // 2:args index.
        info[2]->IsBoolean()) { // 2:args index.
        arrowKeyStepOut = info[2]->ToBoolean(); // 2:args index.
    }
    ViewAbstractModel::GetInstance()->SetFocusScopeId(focusScopeId, isGroup, arrowKeyStepOut);
}

void JSViewAbstract::JsFocusScopePriority(const JSCallbackInfo& info)
{
    if (info.Length() == 0) {
        return;
    }

    if (!info[0]->IsString() || info[0]->IsNull() || info[0]->IsUndefined()) {
        return;
    }
    std::string focusScopeId = info[0]->ToString();

    int32_t focusPriority = 0;
    if (info.Length() == PARAMETER_LENGTH_SECOND && !info[0]->IsNull() && !info[0]->IsUndefined() &&
        info[1]->IsNumber()) {
        focusPriority = info[1]->ToNumber<int32_t>();
    }
    ViewAbstractModel::GetInstance()->SetFocusScopePriority(focusScopeId, focusPriority);
}

void JSViewAbstract::JsBackground(const JSCallbackInfo& info)
{
    if (info.Length() <= 0) {
        return;
    }

    // parse custom background
    Color color = Color::TRANSPARENT;
    RefPtr<ResourceObject> backgroundColorResObj;
    std::function<void()> builderFunc;
    BackgroundType backgroundType = BackgroundType::COLOR;
    if (!ParseJsColor(info[0], color, backgroundColorResObj)) {
        if (ParseBackgroundBuilder(info, info[0], builderFunc)) {
            backgroundType = BackgroundType::CUSTOM_BUILDER;
        } else {
            return;
        }
    }

    // parse background options
    Alignment alignment = Alignment::CENTER;
    NG::LayoutSafeAreaEdge ignoreLayoutSafeAreaEdges =
        (BackgroundType::COLOR == backgroundType) ? NG::LAYOUT_SAFE_AREA_EDGE_ALL : NG::LAYOUT_SAFE_AREA_EDGE_NONE;
    if (info.Length() >= PARAMETER_LENGTH_SECOND && info[1]->IsObject()) {
        JSRef<JSObject> object = JSRef<JSObject>::Cast(info[1]);
        if (object->HasProperty(static_cast<int32_t>(ArkUIIndex::ALIGN))) {
            auto align = object->GetProperty(static_cast<int32_t>(ArkUIIndex::ALIGN));
            auto value = align->ToNumber<int32_t>();
            alignment = ParseAlignment(value);
        }
        if (object->HasProperty(static_cast<int32_t>(ArkUIIndex::IGNORES_LAYOUT_SAFE_AREA_EDGES))) {
            auto safeAreaEdgesArray =
                object->GetProperty(static_cast<int32_t>(ArkUIIndex::IGNORES_LAYOUT_SAFE_AREA_EDGES));
            ignoreLayoutSafeAreaEdges = ParseJsLayoutSafeAreaEdgeArray(safeAreaEdgesArray, ignoreLayoutSafeAreaEdges);
        }
    }

    // parameters parsed, set the properties parsed above
    if (BackgroundType::CUSTOM_BUILDER == backgroundType &&
        NG::LAYOUT_SAFE_AREA_EDGE_NONE == ignoreLayoutSafeAreaEdges) {
        ViewAbstractModel::GetInstance()->SetIsTransitionBackground(false);
    } else {
        ViewAbstractModel::GetInstance()->SetIsTransitionBackground(true);
    }

    ViewAbstractModel::GetInstance()->SetIsBuilderBackground(BackgroundType::CUSTOM_BUILDER == backgroundType);
    ViewAbstractModel::GetInstance()->SetBackground(std::move(builderFunc));
    ViewAbstractModel::GetInstance()->SetBackgroundIgnoresLayoutSafeAreaEdges(ignoreLayoutSafeAreaEdges);
    ViewAbstractModel::GetInstance()->SetBackgroundAlign(alignment);
    if (SystemProperties::ConfigChangePerform() && backgroundColorResObj) {
        ViewAbstractModel::GetInstance()->SetCustomBackgroundColorWithResourceObj(backgroundColorResObj);
    } else {
        ViewAbstractModel::GetInstance()->SetCustomBackgroundColor(color);
    }
}

bool JSViewAbstract::ParseBackgroundBuilder(
    const JSCallbackInfo& info, const JSRef<JSVal>& jsFunc, std::function<void()>& builderFunc)
{
    if (!jsFunc->IsObject()) {
        return false;
    }

    JSRef<JSObject> backgroundObj = JSRef<JSObject>::Cast(jsFunc);
    auto contentObj = backgroundObj->GetProperty(static_cast<int32_t>(ArkUIIndex::BUILDER));
    if (!contentObj->IsFunction()) {
        return false;
    }
    auto jsBuilderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(contentObj));
    CHECK_NULL_RETURN(jsBuilderFunc, false);
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    builderFunc = [execCtx = info.GetExecutionContext(), func = std::move(jsBuilderFunc), node = frameNode]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("BindBackground");
        PipelineContext::SetCallBackNode(node);
        func->Execute();
    };

    return true;
}

NG::LayoutSafeAreaEdge JSViewAbstract::ParseJsLayoutSafeAreaEdgeArray(
    const JSRef<JSArray>& jsSafeAreaEdges, NG::LayoutSafeAreaEdge defaultVal)
{
    if (!jsSafeAreaEdges->IsArray()) {
        return defaultVal;
    }

    static std::vector<uint32_t> layoutEdgeEnum {
        NG::LAYOUT_SAFE_AREA_EDGE_TOP,
        NG::LAYOUT_SAFE_AREA_EDGE_BOTTOM,
        NG::LAYOUT_SAFE_AREA_EDGE_START,
        NG::LAYOUT_SAFE_AREA_EDGE_END,
        NG::LAYOUT_SAFE_AREA_EDGE_VERTICAL,
        NG::LAYOUT_SAFE_AREA_EDGE_HORIZONTAL,
        NG::LAYOUT_SAFE_AREA_EDGE_ALL
    };

    NG::LayoutSafeAreaEdge edges = NG::LAYOUT_SAFE_AREA_EDGE_NONE;
    for (size_t i = 0; i < jsSafeAreaEdges->Length(); ++i) {
        if (!jsSafeAreaEdges->GetValueAt(i)->IsNumber() ||
            jsSafeAreaEdges->GetValueAt(i)->ToNumber<uint32_t>() > LAYOUT_SAFE_AREA_EDGE_LIMIT) {
            return defaultVal;
        }
        edges |= layoutEdgeEnum[jsSafeAreaEdges->GetValueAt(i)->ToNumber<uint32_t>()];
    }

    return edges;
}

void JSViewAbstract::SetSymbolOptionApply(const JSCallbackInfo& info,
    std::function<void(WeakPtr<NG::FrameNode>)>& symbolApply, const JSRef<JSVal> modifierObj)
{
    auto vm = info.GetVm();
    auto globalObj = JSNApi::GetGlobalObject(vm);
    auto globalFunc = globalObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "applySymbolGlyphModifierToNode"));
    JsiValue jsiValue(globalFunc);
    JsiRef<JsiValue> globalFuncRef = JsiRef<JsiValue>::Make(jsiValue);
    if (globalFuncRef->IsFunction()) {
        RefPtr<JsFunction> jsFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(globalFuncRef));
        if (!modifierObj->IsObject()) {
            symbolApply = nullptr;
        } else {
            auto onApply = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc),
                               modifierParam = std::move(modifierObj)](WeakPtr<NG::FrameNode> frameNode) {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                auto node = frameNode.Upgrade();
                CHECK_NULL_VOID(node);
                JSRef<JSVal> params[2];
                params[0] = modifierParam;
                params[1] = JSRef<JSVal>::Make(panda::NativePointerRef::New(execCtx.vm_, AceType::RawPtr(node)));
                PipelineContext::SetCallBackNode(node);
                func->ExecuteJS(2, params);
            };
            symbolApply = onApply;
        }
    }
}

int32_t JSViewAbstract::ParseJsPropertyId(const JSRef<JSVal>& jsValue)
{
    int32_t resId = 0;
    if (jsValue->IsObject()) {
        JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
        JSRef<JSVal> tmp = jsObj->GetProperty("id");
        if (!tmp->IsNull() && tmp->IsNumber()) {
            resId = tmp->ToNumber<int32_t>();
        }
    }
    return resId;
}

void JSViewAbstract::JsVisualEffect(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }
    auto visualEffect = CreateRSEffectFromNapiValue(info[0]);
    ViewAbstractModel::GetInstance()->SetVisualEffect(visualEffect);
}

void JSViewAbstract::JsBackgroundFilter(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }
    auto backgroundFilter = CreateRSFilterFromNapiValue(info[0]);
    ViewAbstractModel::GetInstance()->SetBackgroundFilter(backgroundFilter);
}

void JSViewAbstract::JsForegroundFilter(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }
    auto foregroundFilter = CreateRSFilterFromNapiValue(info[0]);
    ViewAbstractModel::GetInstance()->SetForegroundFilter(foregroundFilter);
}

void JSViewAbstract::JsCompositingFilter(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }
    auto compositingFilter = CreateRSFilterFromNapiValue(info[0]);
    ViewAbstractModel::GetInstance()->SetCompositingFilter(compositingFilter);
}

void JSViewAbstract::ParseMenuItemsSymbolId(const JSRef<JSVal>& jsStartIcon, NG::MenuOptionsParam menuOptionsParam)
{
     if (StringToMenuItemType(menuOptionsParam.id) == MenuItemType::UNKNOWN) {
        uint32_t symbolId = 0;
        RefPtr<ResourceObject> resourceObject;
        if (ParseJsSymbolId(jsStartIcon, symbolId, resourceObject)) {
            menuOptionsParam.symbolId = symbolId;
        }
    } else {
        UpdateInfoById(menuOptionsParam, menuOptionsParam.id);
    }
}

std::vector<NG::MenuOptionsParam> JSViewAbstract::ParseMenuItems(const JSRef<JSArray>& menuItemsArray, bool showShortcut)
{
    std::vector<NG::MenuOptionsParam> menuParams;
    for (size_t i = 0; i <= menuItemsArray->Length(); i++) {
        auto menuItem = menuItemsArray->GetValueAt(i);
        if (!menuItem->IsObject()) {
            continue;
        }
        auto menuItemObject = JSRef<JSObject>::Cast(menuItem);
        NG::MenuOptionsParam menuOptionsParam;
        auto jsContent = menuItemObject->GetProperty("content");
        std::string content;
        ParseJsString(jsContent, content);
        menuOptionsParam.content = content;
        auto jsTextMenuId = menuItemObject->GetProperty("id");
        std::string id;
        if (jsTextMenuId->IsObject()) {
            auto textMenuIdObject = JSRef<JSObject>::Cast(jsTextMenuId);
            auto jsId = textMenuIdObject->GetProperty("id_");
            ParseJsString(jsId, id);
        }
        menuOptionsParam.id = id;
        auto jsLabelInfo = menuItemObject->GetProperty("labelInfo");
        std::string labelInfo;
        ParseJsString(jsLabelInfo, labelInfo);
        if (jsLabelInfo->IsString() || jsLabelInfo->IsObject()) {
            menuOptionsParam.labelInfo = labelInfo;
        }
        auto jsStartIcon = menuItemObject->GetProperty("icon");
        std::string icon;
        ParseJsMedia(jsStartIcon, icon);
        menuOptionsParam.icon = icon;
        if (!showShortcut) {
           ParseMenuItemsSymbolId(jsStartIcon, menuOptionsParam);
        }
        menuParams.emplace_back(menuOptionsParam);
    }
    return menuParams;
}

void JSViewAbstract::ParseOnCreateMenu(
    const JSCallbackInfo& info, const JSRef<JSVal>& jsFunc, NG::OnCreateMenuCallback& onCreateMenuCallback)
{
    if (jsFunc.IsEmpty() || !jsFunc->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsOnCreateMenu = AceType::MakeRefPtr<JsEventFunction<std::vector<NG::MenuItemParam>, 1>>(
        JSRef<JSFunc>::Cast(jsFunc), CreateJsSystemMenuItems);
    auto jsCallback = [execCtx = info.GetExecutionContext(), func = std::move(jsOnCreateMenu),
                          instanceId = Container::CurrentId(), node = frameNode](
                          const std::vector<NG::MenuItemParam>& systemMenuItems) -> std::vector<NG::MenuOptionsParam> {
        ContainerScope scope(instanceId);
        std::vector<NG::MenuOptionsParam> menuParams;
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, menuParams);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, menuParams);
        pipelineContext->UpdateCurrentActiveNode(node);
        auto textOverlayTheme = pipelineContext->GetTheme<TextOverlayTheme>();
        CHECK_NULL_RETURN(textOverlayTheme, menuParams);
        bool showShortcut = textOverlayTheme->GetShowShortcut();
        auto modifiedSystemMenuItems = systemMenuItems;
        UpdateOptionsInfo(modifiedSystemMenuItems);
        auto menuItem = func->ExecuteWithValue(modifiedSystemMenuItems);
        if (!menuItem->IsArray()) {
            return menuParams;
        }
        auto menuItemsArray = JSRef<JSArray>::Cast(menuItem);
        menuParams = ParseMenuItems(menuItemsArray, showShortcut);
        return menuParams;
    };
    onCreateMenuCallback = jsCallback;
}

void JSViewAbstract::ParseOnPrepareMenu(
    const JSCallbackInfo& info, const JSRef<JSVal>& jsFunc, NG::OnPrepareMenuCallback& onPrepareMenuCallback)
{
    if (jsFunc.IsEmpty() || !jsFunc->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsOnPrepareMenu = AceType::MakeRefPtr<JsEventFunction<std::vector<NG::MenuItemParam>, 1>>(
        JSRef<JSFunc>::Cast(jsFunc), CreateJsSystemMenuItems);
    auto jsCallback = [execCtx = info.GetExecutionContext(), func = std::move(jsOnPrepareMenu),
                          instanceId = Container::CurrentId(), node = frameNode](
                          const std::vector<NG::MenuItemParam>& systemMenuItems) -> std::vector<NG::MenuOptionsParam> {
        ContainerScope scope(instanceId);
        std::vector<NG::MenuOptionsParam> menuParams;
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, menuParams);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, menuParams);
        auto textOverlayTheme = pipelineContext->GetTheme<TextOverlayTheme>();
        CHECK_NULL_RETURN(textOverlayTheme, menuParams);
        bool showShortcut = textOverlayTheme->GetShowShortcut();

        pipelineContext->UpdateCurrentActiveNode(node);
        auto modifiedSystemMenuItems = systemMenuItems;
        UpdateOptionsInfo(modifiedSystemMenuItems);
        auto menuItem = func->ExecuteWithValue(modifiedSystemMenuItems);
        if (!menuItem->IsArray()) {
            return menuParams;
        }
        auto menuItemsArray = JSRef<JSArray>::Cast(menuItem);
        menuParams = ParseMenuItems(menuItemsArray, showShortcut);
        return menuParams;
    };
    onPrepareMenuCallback = jsCallback;
}

JSRef<JSVal> JSViewAbstract::CreateJsSystemMenuItems(const std::vector<NG::MenuItemParam>& systemMenuItems)
{
    JSRef<JSArray> systemMenuItemsArray = JSRef<JSArray>::New();
    uint32_t idx = 0;
    for (const auto& item : systemMenuItems) {
        systemMenuItemsArray->SetValueAt(idx++, CreateJsTextMenuItem(item));
    }
    return systemMenuItemsArray;
}

bool JSViewAbstract::ParseEditMenuOptions(const JSCallbackInfo& info, NG::OnCreateMenuCallback& onCreateMenuCallback,
    NG::OnMenuItemClickCallback& onMenuItemClick, NG::OnPrepareMenuCallback& onPrepareMenuCallback)
{
    auto tmpInfo = info[0];
    if (info.Length() != 1 || !tmpInfo->IsObject()) {
        return false;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto menuOptionsObject = JSRef<JSObject>::Cast(tmpInfo);
    auto jsValueOnCreateMenu = menuOptionsObject->GetProperty("onCreateMenu");
    ParseOnCreateMenu(info, jsValueOnCreateMenu, onCreateMenuCallback);
    auto jsValueOnPrepareMenu = menuOptionsObject->GetProperty("onPrepareMenu");
    ParseOnPrepareMenu(info, jsValueOnPrepareMenu, onPrepareMenuCallback);

    auto jsValue = menuOptionsObject->GetProperty("onMenuItemClick");
    if (jsValue.IsEmpty() || !jsValue->IsFunction()) {
        return false;
    }
    RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(jsValue));
    auto jsCallback = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc),
                          onMenuItemCallback = std::move(CreateJsOnMenuItemClick), instanceId = Container::CurrentId(),
                          node = frameNode](NG::MenuItemParam menuOptionsParam) -> bool {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, false);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, false);
        pipelineContext->UpdateCurrentActiveNode(node);
        auto paramArray = onMenuItemCallback(menuOptionsParam);
        if (paramArray->Length() != 2) {
            return false;
        }
        JSRef<JSVal> params[2];
        params[0] = JSRef<JSVal>::Cast(paramArray->GetValueAt(0));
        params[1] = JSRef<JSVal>::Cast(paramArray->GetValueAt(1));
        auto ret = func->ExecuteJS(2, params);
        if (ret->IsBoolean()) {
            return ret->ToBoolean();
        }
        return false;
    };
    onMenuItemClick = jsCallback;
    return true;
}

JSRef<JSObject> JSViewAbstract::CreateJsTextMenuId(const std::string& id)
{
    JSRef<JSObject> empty;
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_RETURN(engine, empty);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    CHECK_NULL_RETURN(nativeEngine, empty);
    auto env = reinterpret_cast<napi_env>(nativeEngine);

    napi_value global;
    napi_status ret = napi_get_global(env, &global);
    if (ret != napi_ok) {
        return empty;
    }
    napi_value constructor;
    ret = napi_get_named_property(env, global, JS_TEXT_MENU_ID_CLASS_NAME, &constructor);
    if (ret != napi_ok) {
        return empty;
    }

    napi_value obj;
    napi_value menuId = nullptr;

    ret = napi_create_string_utf8(env, id.c_str(), id.length(), &menuId);
    if (ret != napi_ok) {
        return empty;
    }
    ret = napi_new_instance(env, constructor, NUM1, &menuId, &obj);
    if (ret != napi_ok) {
        return empty;
    }

    JSRef<JSVal> value = JsConverter::ConvertNapiValueToJsVal(obj);
    if (!value->IsObject()) {
        return empty;
    }

    return JSRef<JSObject>::Cast(value);
}

JSRef<JSArray> JSViewAbstract::CreateJsOnMenuItemClick(const NG::MenuItemParam& menuItemParam)
{
    JSRef<JSArray> params = JSRef<JSArray>::New();
    params->SetValueAt(0, CreateJsTextMenuItem(menuItemParam));
    params->SetValueAt(1, CreateJsTextRange(menuItemParam));
    return params;
}

JSRef<JSVal> JSViewAbstract::CreateJsTextMenuItem(const NG::MenuItemParam& menuItemParam)
{
    JSRef<JSObject> TextMenuItem = JSRef<JSObject>::New();
    TextMenuItem->SetProperty<std::string>("content", menuItemParam.menuOptionsParam.content.value_or(""));
    JSRef<JSObject> obj = CreateJsTextMenuId(menuItemParam.menuOptionsParam.id);
    TextMenuItem->SetPropertyObject("id", obj);
    TextMenuItem->SetProperty<std::string>("labelInfo", menuItemParam.menuOptionsParam.labelInfo.value_or(""));
    if (menuItemParam.menuOptionsParam.symbolId.has_value() && menuItemParam.menuOptionsParam.symbolId.value() != 0) {
        TextMenuItem->SetProperty<uint32_t>("icon", menuItemParam.menuOptionsParam.symbolId.value());
    } else {
        TextMenuItem->SetProperty<std::string>("icon", menuItemParam.menuOptionsParam.icon.value_or(""));
    }
    return JSRef<JSVal>::Cast(TextMenuItem);
}

JSRef<JSVal> JSViewAbstract::CreateJsTextRange(const NG::MenuItemParam& menuItemParam)
{
    JSRef<JSObject> textRange = JSRef<JSObject>::New();
    textRange->SetProperty<int32_t>("start", menuItemParam.start);
    textRange->SetProperty<int32_t>("end", menuItemParam.end);
    return JSRef<JSVal>::Cast(textRange);
}

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_ParseJsMedia(void* value, void* resource)
{
    napi_value napiValue = reinterpret_cast<napi_value>(value);
    ArkUI_Resource* res = reinterpret_cast<ArkUI_Resource*>(resource);
    if (!napiValue || !res) {
        return;
    }
    JSRef<JSVal> jsVal = JsConverter::ConvertNapiValueToJsVal(napiValue);
    std::string src;
    std::string bundleName;
    std::string moduleName;
    JSViewAbstract::ParseJsMedia(jsVal, src);
    JSViewAbstract::GetJsMediaBundleInfo(jsVal, bundleName, moduleName);
    res->resId = JSViewAbstract::ParseJsPropertyId(jsVal);
    res->src = src;
    res->bundleName = bundleName;
    res->moduleName = moduleName;
}

void JSViewAbstract::SetTextStyleApply(const JSCallbackInfo& info,
    std::function<void(WeakPtr<NG::FrameNode>)>& textStyleApply, const JSRef<JSVal>& modifierObj)
{
    if (!modifierObj->IsObject()) {
        textStyleApply = nullptr;
        return;
    }
    auto vm = info.GetVm();
    auto globalObj = JSNApi::GetGlobalObject(vm);
    auto globalFunc = globalObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "applyTextModifierToNode"));
    JsiValue jsiValue(globalFunc);
    JsiRef<JsiValue> globalFuncRef = JsiRef<JsiValue>::Make(jsiValue);
    if (!globalFuncRef->IsFunction()) {
        textStyleApply = nullptr;
        return;
    }
    RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(globalFuncRef));
    auto onApply = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc),
                    modifierParam = std::move(modifierObj)](WeakPtr<NG::FrameNode> frameNode) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto node = frameNode.Upgrade();
        CHECK_NULL_VOID(node);
        JSRef<JSVal> params[2];
        params[0] = modifierParam;
        params[1] = JSRef<JSVal>::Make(panda::NativePointerRef::New(execCtx.vm_, AceType::RawPtr(node)));
        PipelineContext::SetCallBackNode(node);
        func->ExecuteJS(2, params);
    };
    textStyleApply = onApply;
}

void JSViewAbstract::SetPixelRoundMode(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    if (!info[0]->IsNumber()) {
        return;
    }
    auto index = info[0]->ToNumber<uint8_t>();
    auto size = sizeof(PixelRoundMode) / sizeof(PixelRoundMode::PIXEL_ROUND_ON_LAYOUT_FINISH);
    if (index < 0 || index > size) {
        return;
    }
    PixelRoundMode pixelRoundMode = static_cast<PixelRoundMode>(index);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetPixelRoundMode(pixelRoundMode);
}

uint8_t JSViewAbstract::GetPixelRoundMode()
{
    auto pipeline = PipelineBase::GetCurrentContext();
    return pipeline ? static_cast<uint8_t>(pipeline->GetPixelRoundMode())
                    : static_cast<uint8_t>(PixelRoundMode::PIXEL_ROUND_ON_LAYOUT_FINISH);
}

void JSViewAbstract::UnRegisterResource(const std::string& key)
{
    auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern(); 
    CHECK_NULL_VOID(pattern);
    pattern->UnRegisterResource(key);
}

void JSViewAbstract::ParseDragSpringLoadingConfiguration(
    const JSRef<JSObject>& paramObj, const RefPtr<NG::DragSpringLoadingConfiguration>& config)
{
    JSRef<JSObject> configuration = JSRef<JSObject>::Cast(paramObj);
    auto setConfigurationPropertyIfValid =
        [&configuration, &config](const char* propName,
            std::function<void(const RefPtr<NG::DragSpringLoadingConfiguration>&, int32_t)> setter) {
            auto propObj = configuration->GetProperty(propName);
            if (propObj->IsNumber()) {
                auto value = propObj->ToNumber<int32_t>();
                if (value >= 0) {
                    setter(config, value);
                }
            }
        };
    setConfigurationPropertyIfValid("stillTimeLimit", [](const RefPtr<NG::DragSpringLoadingConfiguration>& config,
                                                          int32_t value) { config->stillTimeLimit = value; });
    setConfigurationPropertyIfValid("updateInterval", [](const RefPtr<NG::DragSpringLoadingConfiguration>& config,
                                                          int32_t value) { config->updateInterval = value; });
    setConfigurationPropertyIfValid("updateNotifyCount", [](const RefPtr<NG::DragSpringLoadingConfiguration>& config,
                                                             int32_t value) { config->updateNotifyCount = value; });
    setConfigurationPropertyIfValid(
        "updateToFinishInterval", [](const RefPtr<NG::DragSpringLoadingConfiguration>& config, int32_t value) {
            config->updateToFinishInterval = value;
        });
}

void JSViewAbstract::GetBorderTopWidth(const JSRef<JSObject>& object, NG::BorderWidthProperty& borderWidthProperty)
{
    if (!object->HasProperty(TOP_PROPERTY)) {
        return;
    }
    RefPtr<ResourceObject> resObj = nullptr;
    CalcDimension widthValue;
    if (JSViewAbstract::ParseJsDimensionVpNG(object->GetProperty(TOP_PROPERTY), widthValue, resObj)) {
        if (widthValue.IsNegative()) {
            widthValue.Reset();
        }
    }
    CommonCalcDimension commonCalcDimension;
    ParseCommonEdgeWidthsProps(object, commonCalcDimension);
    borderWidthProperty.topDimen = commonCalcDimension.top;
    if (!resObj) {
        return;
    }

    auto&& updateFunc = [object](const RefPtr<ResourceObject>& resObj,
                            NG::BorderWidthProperty& borderWidthProperty) {
        CalcDimension widthValue;
        ResourceParseUtils::ParseResDimensionVpNG(resObj, widthValue);
        if (widthValue.IsNegative()) {
            widthValue.Reset();
        }
        CommonCalcDimension commonCalcDimension;
        ParseCommonEdgeWidthsProps(object, commonCalcDimension);
        borderWidthProperty.topDimen = widthValue;
    };
    borderWidthProperty.AddResource("dialog.borderWidth.topDimen", resObj, std::move(updateFunc));
}

void JSViewAbstract::GetBorderBottomWidth(const JSRef<JSObject>& object, NG::BorderWidthProperty& borderWidthProperty)
{
    if (!object->HasProperty(BOTTOM_PROPERTY)) {
        return;
    }
    RefPtr<ResourceObject> resObj = nullptr;
    CalcDimension widthValue;
    if (JSViewAbstract::ParseJsDimensionVpNG(object->GetProperty(BOTTOM_PROPERTY), widthValue, resObj)) {
        if (widthValue.IsNegative()) {
            widthValue.Reset();
        }
    }
    CommonCalcDimension commonCalcDimension;
    ParseCommonEdgeWidthsProps(object, commonCalcDimension);
    borderWidthProperty.bottomDimen = commonCalcDimension.bottom;
    if (!resObj) {
        return;
    }

    auto&& updateFunc = [object](const RefPtr<ResourceObject>& resObj,
                            NG::BorderWidthProperty& borderWidthProperty) {
        CalcDimension widthValue;
        ResourceParseUtils::ParseResDimensionVpNG(resObj, widthValue);
        if (widthValue.IsNegative()) {
            widthValue.Reset();
        }
        CommonCalcDimension commonCalcDimension;
        ParseCommonEdgeWidthsProps(object, commonCalcDimension);
        borderWidthProperty.bottomDimen = commonCalcDimension.bottom;
    };
    borderWidthProperty.AddResource("dialog.borderWidth.bottomDimen", resObj, std::move(updateFunc));
}

void JSViewAbstract::GetBorderLeftWidth(const JSRef<JSObject>& object, NG::BorderWidthProperty& borderWidthProperty)
{
    if (!object->HasProperty(LEFT_PROPERTY)) {
        return;
    }
    RefPtr<ResourceObject> resObj = nullptr;
    CalcDimension widthValue;
    if (JSViewAbstract::ParseJsDimensionVpNG(object->GetProperty(LEFT_PROPERTY), widthValue, resObj)) {
        if (widthValue.IsNegative()) {
            widthValue.Reset();
        }
    }
    CommonCalcDimension commonCalcDimension;
    ParseCommonEdgeWidthsProps(object, commonCalcDimension);
    borderWidthProperty.leftDimen = commonCalcDimension.left;
    if (!resObj) {
        return;
    }

    auto&& updateFunc = [object](const RefPtr<ResourceObject>& resObj,
                            NG::BorderWidthProperty& borderWidthProperty) {
        CalcDimension widthValue;
        ResourceParseUtils::ParseResDimensionVpNG(resObj, widthValue);
        if (widthValue.IsNegative()) {
            widthValue.Reset();
        }
        CommonCalcDimension commonCalcDimension;
        ParseCommonEdgeWidthsProps(object, commonCalcDimension);
        borderWidthProperty.leftDimen = commonCalcDimension.left;
    };
    borderWidthProperty.AddResource("dialog.borderWidth.leftDimen", resObj, std::move(updateFunc));
}

void JSViewAbstract::GetBorderRightWidth(const JSRef<JSObject>& object, NG::BorderWidthProperty& borderWidthProperty)
{
    if (!object->HasProperty(RIGHT_PROPERTY)) {
        return;
    }
    RefPtr<ResourceObject> resObj = nullptr;
    CalcDimension widthValue;
    if (JSViewAbstract::ParseJsDimensionVpNG(object->GetProperty(RIGHT_PROPERTY), widthValue, resObj)) {
        if (widthValue.IsNegative()) {
            widthValue.Reset();
        }
    }
    CommonCalcDimension commonCalcDimension;
    ParseCommonEdgeWidthsProps(object, commonCalcDimension);
    borderWidthProperty.rightDimen = widthValue;
    if (!resObj) {
        return;
    }
    auto&& updateFunc = [object](const RefPtr<ResourceObject>& resObj,
                            NG::BorderWidthProperty& borderWidthProperty) {
        CalcDimension widthValue;
        ResourceParseUtils::ParseResDimensionVpNG(resObj, widthValue);
        if (widthValue.IsNegative()) {
            widthValue.Reset();
        }
        CommonCalcDimension commonCalcDimension;
        ParseCommonEdgeWidthsProps(object, commonCalcDimension);
        borderWidthProperty.rightDimen = commonCalcDimension.right;
    };
    borderWidthProperty.AddResource("dialog.borderWidth.rightDimen", resObj, std::move(updateFunc));
}

void JSViewAbstract::GetBorderStartWidth(const JSRef<JSObject>& object, NG::BorderWidthProperty& borderWidthProperty)
{
    if (!object->HasProperty(START_PROPERTY)) {
        return;
    }
    RefPtr<ResourceObject> resObj = nullptr;
    CalcDimension widthValue;
    if (JSViewAbstract::ParseJsDimensionVpNG(object->GetProperty(START_PROPERTY), widthValue, resObj)) {
        if (widthValue.IsNegative()) {
            widthValue.Reset();
        }
    }
    CommonCalcDimension commonCalcDimension;
    ParseCommonEdgeWidthsProps(object, commonCalcDimension);
    borderWidthProperty.leftDimen = commonCalcDimension.left;
    borderWidthProperty.rightDimen = commonCalcDimension.right;

    if (!resObj) {
        return;
    }

    auto&& updateFunc = [object](const RefPtr<ResourceObject>& resObj,
                            NG::BorderWidthProperty& borderWidthProperty) {
        CalcDimension widthValue;
        ResourceParseUtils::ParseResDimensionVpNG(resObj, widthValue);
        if (widthValue.IsNegative()) {
            widthValue.Reset();
        }
        CommonCalcDimension commonCalcDimension;
        ParseCommonEdgeWidthsProps(object, commonCalcDimension);
        borderWidthProperty.leftDimen = commonCalcDimension.left;
        borderWidthProperty.rightDimen = commonCalcDimension.right;
    };
    borderWidthProperty.AddResource("dialog.borderWidth.startDimen", resObj, std::move(updateFunc));
}

void JSViewAbstract::GetBorderEndWidth(const JSRef<JSObject>& object, NG::BorderWidthProperty& borderWidthProperty)
{
    if (!object->HasProperty(END_PROPERTY)) {
        return;
    }
    RefPtr<ResourceObject> resObj = nullptr;
    CalcDimension widthValue;
    if (JSViewAbstract::ParseJsDimensionVpNG(object->GetProperty(END_PROPERTY), widthValue, resObj)) {
        if (widthValue.IsNegative()) {
            widthValue.Reset();
        }
    }
    CommonCalcDimension commonCalcDimension;
    ParseCommonEdgeWidthsProps(object, commonCalcDimension);
    borderWidthProperty.leftDimen = commonCalcDimension.left;
    borderWidthProperty.rightDimen = commonCalcDimension.right;

    if (!resObj) {
        return;
    }

    auto&& updateFunc = [object](const RefPtr<ResourceObject>& resObj,
                            NG::BorderWidthProperty& borderWidthProperty) {
        CalcDimension widthValue;
        ResourceParseUtils::ParseResDimensionVpNG(resObj, widthValue);
        if (widthValue.IsNegative()) {
            widthValue.Reset();
        }
        CommonCalcDimension commonCalcDimension;
        ParseCommonEdgeWidthsProps(object, commonCalcDimension);
        borderWidthProperty.leftDimen = commonCalcDimension.left;
        borderWidthProperty.rightDimen = commonCalcDimension.right;
    };
    borderWidthProperty.AddResource("dialog.borderWidth.endDimen", resObj, std::move(updateFunc));
}

void JSViewAbstract::GetBorderWidth(const JSRef<JSObject>& object, NG::BorderWidthProperty& borderWidthProperty)
{
    GetBorderStartWidth(object, borderWidthProperty);
    GetBorderEndWidth(object, borderWidthProperty);
    GetBorderTopWidth(object, borderWidthProperty);
    GetBorderBottomWidth(object, borderWidthProperty);
    GetBorderLeftWidth(object, borderWidthProperty);
    GetBorderRightWidth(object, borderWidthProperty);
    borderWidthProperty.multiValued = true;
}

void JSViewAbstract::GetBorderWidthFromResource(const JSRef<JSVal>& args, NG::BorderWidthProperty& borderWidthProperty)
{
    CalcDimension borderWidth;
    RefPtr<ResourceObject> resObj = nullptr;
    if (ParseJsDimensionVpNG(args, borderWidth, resObj)) {
        if (borderWidth.IsNegative()) {
            borderWidth.Reset();
        }
        borderWidthProperty =
            NG::BorderWidthProperty({ borderWidth, borderWidth, borderWidth, borderWidth, std::nullopt, std::nullopt });
    }
    if (resObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderWidthProperty& borderWidthProperty) {
            CalcDimension widthValue;
            ResourceParseUtils::ParseResDimensionVpNG(resObj, widthValue);
            if (widthValue.IsNegative()) {
                widthValue.Reset();
            }
            borderWidthProperty =
                NG::BorderWidthProperty({ widthValue, widthValue, widthValue, widthValue, std::nullopt, std::nullopt });
        };
        borderWidthProperty.AddResource("dialog.borderWidth", resObj, std::move(updateFunc));
    }
    if (args->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(args);
        GetBorderWidth(obj, borderWidthProperty);
    }
}

void JSViewAbstract::SetBorderRadiusWithCheck(std::optional<NG::BorderRadiusProperty>& result,
    NG::BorderRadiusProperty& borderRadius)
{
    if (borderRadius.radiusTopLeft.has_value() && !borderRadius.radiusTopLeft->IsNegative() &&
        borderRadius.radiusTopRight.has_value() && !borderRadius.radiusTopRight->IsNegative() &&
        borderRadius.radiusBottomLeft.has_value() && !borderRadius.radiusBottomLeft->IsNegative() &&
        borderRadius.radiusBottomRight.has_value() && !borderRadius.radiusBottomRight->IsNegative()) {
        result = borderRadius;
    }
}
} // namespace OHOS::Ace::Framework
