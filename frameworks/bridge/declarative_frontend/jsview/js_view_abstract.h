/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_VIEW_ABSTRACT_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_VIEW_ABSTRACT_H

#include <cstdint>
#include <functional>
#include <optional>

#include "base/geometry/dimension.h"
#include "base/geometry/dimension_rect.h"
#include "base/json/json_util.h"
#include "base/log/ace_scoring_log.h"
#include "base/log/ace_trace.h"
#include "base/log/log.h"
#include "base/memory/ace_type.h"
#include "bridge/declarative_frontend/engine/bindings.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "core/common/container.h"
#include "core/components/box/box_component.h"
#include "core/components/common/properties/border_image.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/popup_param.h"
#include "core/components/menu/menu_component.h"
#include "core/components/theme/theme_manager.h"
#include "core/components/transform/transform_component.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/property/gradient_property.h"
#include "core/components_ng/property/transition_property.h"
#include "core/pipeline/base/component.h"
#include "frameworks/core/gestures/tap_gesture.h"

namespace OHOS::Ace::Framework {

constexpr int32_t DEFAULT_TAP_FINGERS = 1;
constexpr int32_t DEFAULT_TAP_COUNTS = 1;

enum class ResourceType : uint32_t {
    COLOR = 10001,
    FLOAT,
    STRING,
    PLURAL,
    BOOLEAN,
    INTARRAY,
    INTEGER,
    PATTERN,
    STRARRAY,
    MEDIA = 20000,
    RAWFILE = 30000
};

enum class ResponseType : int32_t {
    RIGHT_CLICK = 0,
    LONGPRESS,
};

enum class JSCallbackInfoType { STRING, NUMBER, OBJECT, BOOLEAN, FUNCTION };

class JSViewAbstract {
public:
    static void GetAngle(
        const std::string& key, const std::unique_ptr<JsonValue>& jsonValue, std::optional<float>& angle);
    static void GetGradientColorStops(Gradient& gradient, const std::unique_ptr<JsonValue>& jsonValue);
    static void NewGetGradientColorStops(NG::Gradient& gradient, const std::unique_ptr<JsonValue>& jsonValue);
    static void ExecMenuBuilder(RefPtr<JsFunction> builderFunc, RefPtr<MenuComponent> menuComponent);

    static void JsScale(const JSCallbackInfo& info);
    static void JsScaleX(const JSCallbackInfo& info);
    static void JsScaleY(const JSCallbackInfo& info);
    static void JsOpacity(const JSCallbackInfo& info);
    static void JsTranslate(const JSCallbackInfo& info);
    static void JsTranslateX(const JSCallbackInfo& info);
    static void JsTranslateY(const JSCallbackInfo& info);
    static void JsRotate(const JSCallbackInfo& info);
    static void JsRotateX(const JSCallbackInfo& info);
    static void JsRotateY(const JSCallbackInfo& info);
    static void JsTransform(const JSCallbackInfo& info);
    static void JsTransition(const JSCallbackInfo& info);
    static NG::TransitionOptions ParseTransition(std::unique_ptr<JsonValue>& transitionArgs);
    static void JsWidth(const JSCallbackInfo& info);
    static void JsHeight(const JSCallbackInfo& info);
    static void JsBackgroundColor(const JSCallbackInfo& info);
    static void JsBackgroundImage(const JSCallbackInfo& info);
    static void JsBackgroundImageSize(const JSCallbackInfo& info);
    static void JsBackgroundImagePosition(const JSCallbackInfo& info);
    static void JsBackgroundBlurStyle(const JSCallbackInfo& info);
    static void JsBindMenu(const JSCallbackInfo& info);
    static void JsBindContextMenu(const JSCallbackInfo& info);
    static void JsBorderColor(const JSCallbackInfo& info);
    static void ParseBorderColor(const JSRef<JSVal>& args);
    static void JsPadding(const JSCallbackInfo& info);
    static void JsMargin(const JSCallbackInfo& info);
    static void ParseMarginOrPadding(const JSCallbackInfo& info, bool isMargin);
    static void JsBorder(const JSCallbackInfo& info);
    static void JsBorderWidth(const JSCallbackInfo& info);
    static void ParseBorderWidth(const JSRef<JSVal>& args);
    static void JsBorderRadius(const JSCallbackInfo& info);
    static void ParseBorderRadius(const JSRef<JSVal>& args);
    static void JsBorderStyle(const JSCallbackInfo& info);
    static void ParseBorderStyle(const JSRef<JSVal>& args);
    static void JsBorderImage(const JSCallbackInfo& info);
    static void ParseBorderImageRepeat(const JSRef<JSVal>& args, RefPtr<BorderImage>& borderImage);
    static void ParseBorderImageOutset(const JSRef<JSVal>& args, RefPtr<BorderImage>& borderImage);
    static void ParseBorderImageSlice(const JSRef<JSVal>& args, RefPtr<BorderImage>& borderImage);
    static void ParseBorderImageWidth(const JSRef<JSVal>& args, RefPtr<BorderImage>& borderImage);
    static void ParseBorderImageDimension(
        const JSRef<JSVal>& args, BorderImage::BorderImageOption& borderImageDimension);
    static void ParseBorderImageLinearGradient(const JSRef<JSVal>& args, uint8_t& bitset);
    static void JsBlur(const JSCallbackInfo& info);
    static void JsColorBlend(const JSCallbackInfo& info);
    static void JsBackdropBlur(const JSCallbackInfo& info);
    static void JsWindowBlur(const JSCallbackInfo& info);
    static void JsFlexBasis(const JSCallbackInfo& info);
    static void JsFlexGrow(const JSCallbackInfo& info);
    static void JsFlexShrink(const JSCallbackInfo& info);
    static void JsAlignSelf(const JSCallbackInfo& info);
    static void JsDisplayPriority(const JSCallbackInfo& info);
    static void JsSharedTransition(const JSCallbackInfo& info);
    static void JsGeometryTransition(const JSCallbackInfo& info);
    static void JsGridSpan(const JSCallbackInfo& Info);
    static void JsGridOffset(const JSCallbackInfo& info);
    static void JsUseSizeType(const JSCallbackInfo& Info);
    static void JsHoverEffect(const JSCallbackInfo& info);
    static void JsOnMouse(const JSCallbackInfo& info);
    static void JsOnHover(const JSCallbackInfo& info);
    static void JsOnClick(const JSCallbackInfo& info);
    static EventMarker GetClickEventMarker(const JSCallbackInfo& info);
    static void JsRestoreId(int32_t restoreId);
    static void JsOnVisibleAreaChange(const JSCallbackInfo& info);
    static void JsHitTestBehavior(const JSCallbackInfo& info);

    // response region
    static void JsResponseRegion(const JSCallbackInfo& info);
    static bool ParseJsResponseRegionArray(const JSRef<JSVal>& jsValue, std::vector<DimensionRect>& result);
    static bool ParseJsDimensionRect(const JSRef<JSVal>& jsValue, DimensionRect& result);

    // for number and string with no unit, use default dimension unit.
    static bool ParseJsDimension(const JSRef<JSVal>& jsValue, Dimension& result, DimensionUnit defaultUnit);
    static bool ParseJsDimensionVp(const JSRef<JSVal>& jsValue, Dimension& result);
    static bool ParseJsDimensionFp(const JSRef<JSVal>& jsValue, Dimension& result);
    static bool ParseJsDimensionPx(const JSRef<JSVal>& jsValue, Dimension& result);
    static bool ParseJsDouble(const JSRef<JSVal>& jsValue, double& result);
    static bool ParseJsInt32(const JSRef<JSVal>& jsValue, int32_t& result);
    static bool ParseJsColor(const JSRef<JSVal>& jsValue, Color& result);
    static bool ParseJsFontFamilies(const JSRef<JSVal>& jsValue, std::vector<std::string>& result);

    static bool ParseJsonDimension(
        const std::unique_ptr<JsonValue>& jsonValue, Dimension& result, DimensionUnit defaultUnit);
    static bool ParseJsonDimensionVp(const std::unique_ptr<JsonValue>& jsonValue, Dimension& result);
    static bool ParseJsonDouble(const std::unique_ptr<JsonValue>& jsonValue, double& result);
    static bool ParseJsonColor(const std::unique_ptr<JsonValue>& jsonValue, Color& result);
    static bool ParseJsString(const JSRef<JSVal>& jsValue, std::string& result);
    static bool ParseJsMedia(const JSRef<JSVal>& jsValue, std::string& result);

    static bool ParseJsBool(const JSRef<JSVal>& jsValue, bool& result);
    static bool ParseJsInteger(const JSRef<JSVal>& jsValue, uint32_t& result);
    static bool ParseJsInteger(const JSRef<JSVal>& jsValue, int32_t& result);
    static bool ParseJsIntegerArray(const JSRef<JSVal>& jsValue, std::vector<uint32_t>& result);
    static bool ParseJsStrArray(const JSRef<JSVal>& jsValue, std::vector<std::string>& result);

    static std::pair<Dimension, Dimension> ParseSize(const JSCallbackInfo& info);
    static void JsUseAlign(const JSCallbackInfo& info);
    static void JsZIndex(const JSCallbackInfo& info);
    static void SetDirection(const std::string& dir);
    static void JsSize(const JSCallbackInfo& info);
    static void JsConstraintSize(const JSCallbackInfo& info);
    static void JsLayoutPriority(const JSCallbackInfo& info);
    static void JsLayoutWeight(const JSCallbackInfo& info);

    static void JsAlign(const JSCallbackInfo& info);
    static void JsPosition(const JSCallbackInfo& info);
    static void JsMarkAnchor(const JSCallbackInfo& info);
    static void JsOffset(const JSCallbackInfo& info);
    static void JsEnabled(const JSCallbackInfo& info);
    static void JsAspectRatio(const JSCallbackInfo& info);
    static void JsOverlay(const JSCallbackInfo& info);
    static Alignment ParseAlignment(int32_t align);
    static void JsAlignRules(const JSCallbackInfo& info);

    static void SetVisibility(const JSCallbackInfo& info);
    static void Pop();

    static void JsOnDragStart(const JSCallbackInfo& info);
    static bool ParseAndUpdateDragItemInfo(const JSRef<JSVal>& info, NG::DragDropBaseInfo& dragInfo);
    static RefPtr<AceType> ParseDragNode(const JSRef<JSVal>& info);
    static void JsOnDragEnter(const JSCallbackInfo& info);
    static void JsOnDragMove(const JSCallbackInfo& info);
    static void JsOnDragLeave(const JSCallbackInfo& info);
    static void JsOnDrop(const JSCallbackInfo& info);
    static void JsOnAreaChange(const JSCallbackInfo& info);

    static void JsLinearGradient(const JSCallbackInfo& info);
    static void JsRadialGradient(const JSCallbackInfo& info);
    static void JsSweepGradient(const JSCallbackInfo& info);
    static void NewJsLinearGradient(const JSCallbackInfo& info, NG::Gradient& gradient);
    static void NewJsRadialGradient(const JSCallbackInfo& info, NG::Gradient& gradient);
    static void NewJsSweepGradient(const JSCallbackInfo& info, NG::Gradient& gradient);
    static void JsMotionPath(const JSCallbackInfo& info);
    static void JsShadow(const JSCallbackInfo& info);
    static void JsGrayScale(const JSCallbackInfo& info);
    static void JsBrightness(const JSCallbackInfo& info);
    static void JsContrast(const JSCallbackInfo& info);
    static void JsSaturate(const JSCallbackInfo& info);
    static void JsSepia(const JSCallbackInfo& info);
    static void JsInvert(const JSCallbackInfo& info);
    static void JsHueRotate(const JSCallbackInfo& info);

    static void JsClip(const JSCallbackInfo& info);
    static void JsMask(const JSCallbackInfo& info);

    static void JsKey(const std::string& key);
    static void JsId(const std::string& id);

    static void JsFocusable(const JSCallbackInfo& info);
    static void JsOnFocusMove(const JSCallbackInfo& args);
    static void JsOnKeyEvent(const JSCallbackInfo& args);
    static void JsOnFocus(const JSCallbackInfo& args);
    static void JsOnBlur(const JSCallbackInfo& args);
    static void JsTabIndex(const JSCallbackInfo& info);
    static void JsFocusOnTouch(const JSCallbackInfo& info);
    static void JsDefaultFocus(const JSCallbackInfo& info);
    static void JsGroupDefaultFocus(const JSCallbackInfo& info);
#if defined(PREVIEW)
    static void JsDebugLine(const JSCallbackInfo& info);
#endif
    static void JsOpacityPassThrough(const JSCallbackInfo& info);
    static void JsTransitionPassThrough(const JSCallbackInfo& info);

    static void JsAccessibilityGroup(bool accessible);
    static void JsAccessibilityText(const std::string& text);
    static void JsAccessibilityDescription(const std::string& description);
    static void JsAccessibilityImportance(const std::string& importance);

#ifndef WEARABLE_PRODUCT
    static void JsBindPopup(const JSCallbackInfo& info);
    static void JsBindPopupNG(const JSCallbackInfo& info);
    static void CreateCustomPopup(
        RefPtr<JsFunction>& builder, const RefPtr<NG::FrameNode>& targetNode, const RefPtr<PopupParam>& popupParam);
#endif

    /**
     * Binds the native methods to the the js object
     */
    static void JSBind();

    static const RefPtr<PipelineBase> GetPipelineContext()
    {
        auto container = Container::Current();
        if (!container) {
            LOGW("container is null");
            return nullptr;
        }
        auto pipelineContext = container->GetPipelineContext();
        if (!pipelineContext) {
            LOGE("pipelineContext is null!");
            return nullptr;
        }
        return pipelineContext;
    }

    template<typename T>
    static RefPtr<T> GetTheme()
    {
        auto pipelineContext = GetPipelineContext();
        if (!pipelineContext) {
            LOGE("pipelineContext is null!");
            return nullptr;
        }
        auto themeManager = pipelineContext->GetThemeManager();
        if (!themeManager) {
            LOGE("themeManager is null!");
            return nullptr;
        }
        return themeManager->GetTheme<T>();
    }

    /**
     * box properties setter
     */
    static RefPtr<Gesture> GetTapGesture(
        const JSCallbackInfo& info, int32_t countNum = DEFAULT_TAP_COUNTS, int32_t fingerNum = DEFAULT_TAP_FINGERS);
    static const Border& GetBorder();
    static void SetMarginTop(const JSCallbackInfo& info);
    static void SetMarginBottom(const JSCallbackInfo& info);
    static void SetMarginLeft(const JSCallbackInfo& info);
    static void SetMarginRight(const JSCallbackInfo& info);
    static void SetPaddingTop(const JSCallbackInfo& info);
    static void SetPaddingBottom(const JSCallbackInfo& info);
    static void SetPaddingLeft(const JSCallbackInfo& info);
    static void SetPaddingRight(const JSCallbackInfo& info);
    static void SetBorder(const Border& border);
    static void SetBorderStyle(int32_t style);
    static void SetBorderColor(const Color& color, const AnimationOption& option);
    static void SetBorderWidth(const Dimension& value, const AnimationOption& option);
    static void SetBlur(float radius);
    static void SetColorBlend(Color color);
    static void SetBackdropBlur(float radius);
    static void SetWindowBlur(float progress, WindowBlurStyle blurStyle);
    static RefPtr<ThemeConstants> GetThemeConstants(const JSRef<JSObject>& jsObj = JSRef<JSObject>());
    static bool JsWidth(const JSRef<JSVal>& jsValue);
    static bool JsHeight(const JSRef<JSVal>& jsValue);

    template<typename T>
    static bool ParseJsInteger(const JSRef<JSVal>& jsValue, T& result)
    {
        if (!jsValue->IsNumber() && !jsValue->IsObject()) {
            LOGE("arg is not number or Object.");
            return false;
        }

        if (jsValue->IsNumber()) {
            LOGD("jsValue->IsNumber()");
            result = jsValue->ToNumber<T>();
            return true;
        }

        JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
        JSRef<JSVal> type = jsObj->GetProperty("type");
        if (!type->IsNumber()) {
            LOGW("type is not number");
            return false;
        }

        JSRef<JSVal> resId = jsObj->GetProperty("id");
        if (!resId->IsNumber()) {
            LOGW("resId is not number");
            return false;
        }

        auto themeConstants = GetThemeConstants();
        if (!themeConstants) {
            LOGW("themeConstants is nullptr");
            return false;
        }

        if (type->ToNumber<uint32_t>() == static_cast<uint32_t>(ResourceType::INTEGER)) {
            result = static_cast<T>(themeConstants->GetInt(resId->ToNumber<uint32_t>()));
            return true;
        } else {
            return false;
        }
    }
};
} // namespace OHOS::Ace::Framework
#endif // JS_VIEW_ABSTRACT_H
