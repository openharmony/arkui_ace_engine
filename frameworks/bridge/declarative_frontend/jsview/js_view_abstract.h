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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_VIEW_ABSTRACT_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_VIEW_ABSTRACT_H

#include <cstdint>
#include <optional>

#include "base/geometry/dimension.h"
#include "base/geometry/dimension_rect.h"
#include "base/json/json_util.h"
#include "base/log/log.h"
#include "base/memory/ace_type.h"
#include "base/utils/system_properties.h"
#include "bridge/declarative_frontend/engine/bindings.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "core/common/container.h"
#include "core/common/resource/resource_manager.h"
#include "core/common/resource/resource_object.h"
#include "core/common/resource/resource_wrapper.h"
#include "core/components/common/properties/popup_param.h"
#include "core/components/theme/theme_manager.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/tabs/tab_content_model.h"
#include "core/components_ng/pattern/text/text_model.h"
#include "core/components_ng/pattern/text/text_menu_extension.h"
#include "core/components_ng/property/gradient_property.h"
#include "core/components_ng/property/transition_property.h"
#include "interfaces/inner_api/ace/ai/image_analyzer.h"

namespace OHOS::Ace::Framework {

constexpr int32_t DEFAULT_TAP_FINGERS = 1;
constexpr int32_t DEFAULT_TAP_COUNTS = 1;
constexpr float DEFAULT_PROGRESS_TOTAL = 100.0f;

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

static std::vector<std::pair<int32_t, RefPtr<ResourceObject>>> DEFAULT_RESOURCE_PAIR_ARRAY;

enum class JSCallbackInfoType { STRING, NUMBER, OBJECT, BOOLEAN, FUNCTION };

struct LocalizedCalcDimension {
    std::optional<CalcDimension> start;
    std::optional<CalcDimension> end;
    std::optional<CalcDimension> top;
    std::optional<CalcDimension> bottom;
    RefPtr<ResourceObject> leftResObj;
    RefPtr<ResourceObject> rightResObj;
    RefPtr<ResourceObject> topResObj;
    RefPtr<ResourceObject> bottomResObj;
};

struct CommonCalcDimension {
    std::optional<CalcDimension> left;
    std::optional<CalcDimension> right;
    std::optional<CalcDimension> top;
    std::optional<CalcDimension> bottom;
    RefPtr<ResourceObject> leftResObj;
    RefPtr<ResourceObject> rightResObj;
    RefPtr<ResourceObject> topResObj;
    RefPtr<ResourceObject> bottomResObj;
};

struct LocalizedColor {
    std::optional<Color> start;
    std::optional<Color> end;
    std::optional<Color> top;
    std::optional<Color> bottom;
    RefPtr<ResourceObject> startResObj;
    RefPtr<ResourceObject> endResObj;
    RefPtr<ResourceObject> topResObj;
    RefPtr<ResourceObject> bottomResObj;
};

struct CommonColor {
    std::optional<Color> left;
    std::optional<Color> right;
    std::optional<Color> top;
    std::optional<Color> bottom;
    RefPtr<ResourceObject> leftResObj;
    RefPtr<ResourceObject> rightResObj;
    RefPtr<ResourceObject> topResObj;
    RefPtr<ResourceObject> bottomResObj;
};

RefPtr<ResourceObject> GetResourceObject(const JSRef<JSObject>& jsObj);
RefPtr<ResourceObject> GetResourceObjectByBundleAndModule(const JSRef<JSObject>& jsObj);
RefPtr<ResourceWrapper> CreateResourceWrapper(const JSRef<JSObject>& jsObj, RefPtr<ResourceObject>& resourceObject);
RefPtr<ResourceWrapper> CreateResourceWrapper();
using PopupOnWillDismiss = std::function<void(int32_t)>;
std::function<std::string()> JsGetCustomMapFunc(panda::ecmascript::EcmaVM* vm, int32_t nodeId);
class JSViewAbstract {
public:
    static RefPtr<ResourceObject> GetResourceObject(const JSRef<JSObject>& jsObj);
    static void SetPixelRoundMode(const JSCallbackInfo& info);
    static uint8_t GetPixelRoundMode();
    static void GetAngle(
        const std::string& key, const std::unique_ptr<JsonValue>& jsonValue, std::optional<float>& angle);
    static void GetJsAngle(
        int32_t key, const JSRef<JSVal>& jsValue, std::optional<float>& angle);
    static void GetJsAngleWithDefault(
        int32_t key, const JSRef<JSObject>& jsObj, std::optional<float>& angle, float defaultValue);
    static inline void CheckAngle(std::optional<float>& angle);
    static void GetPerspective(const std::string& key, const std::unique_ptr<JsonValue>& jsonValue, float& perspective);
    static void GetJsPerspective(int32_t key, const JSRef<JSObject>& jsValue, float& perspective);
    static void GetGradientColorStops(Gradient& gradient, const std::unique_ptr<JsonValue>& jsonValue);
    static void GetFractionStops(
        std::vector<std::pair<float, float>>& fractionStops, const JSRef<JSVal>& array);
    static void NewGetGradientColorStops(NG::Gradient& gradient, const std::unique_ptr<JsonValue>& jsonValue);
    static void NewGetJsGradientColorStops(NG::Gradient& gradient, const JSRef<JSVal>& colorStops,
        const int32_t mapIdx = 0);
    static void NewGetJsGradientColorStopsCheck(NG::Gradient& gradient, const JSRef<JSVal>& colorStops);

    static void JsScale(const JSCallbackInfo& info);
    static void SetTabBarSymbolOptionApply(const JSCallbackInfo& info, TabBarSymbol& symbolApply,
        const JSRef<JSVal>& modifierNormalObj, const JSRef<JSVal>& modifierSelectedObj);
    static void SetDragPreviewOptionApply(const JSCallbackInfo& info, NG::DragPreviewOption& previewOption);
    static void SetDragNumberBadge(const JSCallbackInfo& info, NG::DragPreviewOption& option);
    static void SetDefaultScale();
    static void JsScaleX(const JSCallbackInfo& info);
    static void JsScaleY(const JSCallbackInfo& info);
    static void JsOpacity(const JSCallbackInfo& info);
    static void JsTranslate(const JSCallbackInfo& info);
    static void SetDefaultTranslate();
    static void JsTranslateX(const JSCallbackInfo& info);
    static void JsTranslateY(const JSCallbackInfo& info);
    static void JsRotate(const JSCallbackInfo& info);
    static void SetDefaultRotate();
    static void JsRotateX(const JSCallbackInfo& info);
    static void JsRotateY(const JSCallbackInfo& info);
    static void JsTransform(const JSCallbackInfo& info);
    static void JsTransform3D(const JSCallbackInfo& info);
    static void SetDefaultTransform();
    static void SetDefaultTransform3D();
    static void JsTransition(const JSCallbackInfo& info);
    static void ParseDragPreviewConfig(const JSCallbackInfo& info, NG::DragDropInfo& dragPreviewInfo);
    static void ParseDragPreviewValue(const JSCallbackInfo& info, NG::DragDropInfo& dragPreviewInfo);
    static void ParseDragPreviewBuilderNode(const JSCallbackInfo& info, NG::DragDropInfo& dragPreviewInfo,
        const JSRef<JSVal>& builder);
    static void ParseDragInteractionOptions(const JSCallbackInfo& info, NG::DragPreviewOption& previewOption);
    static NG::DragPreviewOption ParseDragPreviewOptions(const JSCallbackInfo& info);
    static NG::TransitionOptions ParseJsTransition(const JSRef<JSObject>& jsObj);
    static RefPtr<NG::ChainedTransitionEffect> ParseJsTransitionEffect(const JSCallbackInfo& info);
    static void JsWidth(const JSCallbackInfo& info);
    static void JsHeight(const JSCallbackInfo& info);
    static void JsToolbar(const JSCallbackInfo& info);
    static void JsBackgroundColor(const JSCallbackInfo& info);
    static void JsBackgroundImage(const JSCallbackInfo& info);
    static void JsBackgroundImageSize(const JSCallbackInfo& info);
    static void JsBackgroundImagePosition(const JSCallbackInfo& info);
    static void ParseBlurOption(const JSRef<JSObject>& jsBlurOption, BlurOption& blurOption);
    static void ParseBackgroundImageOption(const JSCallbackInfo& jsOption, int32_t& repeatIndex, bool& syncMode);
    static void ParseInactiveColor(const JSRef<JSObject>& jsOption, BlurStyleOption& styleOption);
    static void ParseBlurStyleOption(const JSRef<JSObject>& jsOption, BlurStyleOption& styleOption);
    static void ParseSysOptions(const JSRef<JSObject>& jsSysOptions, SysOptions& sysOptions);
    static void JsBackgroundBlurStyle(const JSCallbackInfo& info);
    static void JsBackgroundEffect(const JSCallbackInfo& info);
    static void GetEffectOptionColor(const JSRef<JSObject>& jsOption, EffectOption& effectOption);
    static void GetEffectOptionInactiveColorUpdate(const RefPtr<ResourceObject>& inactiveColorObj,
        EffectOption& effectOption);
    static void GetEffectOptionInactiveColor(const JSRef<JSObject>& jsOption, EffectOption& effectOption);
    static void ParseEffectOption(const JSRef<JSObject>& jsObj, EffectOption& effectOption);
    static void ParseBrightnessOption(const JSRef<JSObject>& jsObj, BrightnessOption& brightnessOption);
    static void JsForegroundBlurStyle(const JSCallbackInfo& info);
    static void JsForegroundEffect(const JSCallbackInfo& info);
    static void JsSphericalEffect(const JSCallbackInfo& info);
    static void GetPixelStretchEffectLeftObj(
        const JSRef<JSObject>& jsObject, CalcDimension& left, PixStretchEffectOption& option);
    static void GetPixelStretchEffectRightObj(
        const JSRef<JSObject>& jsObject, CalcDimension& right, PixStretchEffectOption& option);
    static void GetPixelStretchEffectTopObj(
        const JSRef<JSObject>& jsObject, CalcDimension& top, PixStretchEffectOption& option);
    static void GetPixelStretchEffectBottomObj(
        const JSRef<JSObject>& jsObject, CalcDimension& bottom, PixStretchEffectOption& option);
    static void JsPixelStretchEffect(const JSCallbackInfo& info);
    static bool InitPixStretchEffect(
        CalcDimension& left, CalcDimension& right, CalcDimension& top, CalcDimension bottom);
    static void JsLightUpEffect(const JSCallbackInfo& info);
    static void JsBackground(const JSCallbackInfo& info);
    static void JsBindMenu(const JSCallbackInfo& info);
    static void JsBindContextMenu(const JSCallbackInfo& info);
    static void MenuDefaultParam(NG::MenuParam& menuParam);
    static void ParseContentMenuCommonParam(
        const JSCallbackInfo& info, const JSRef<JSObject>& menuObj, NG::MenuParam& menuParam);
    static int32_t OpenMenu(NG::MenuParam& menuParam, const RefPtr<NG::UINode>& customNode, const int32_t& targetId);
    static int32_t UpdateMenu(const NG::MenuParam& menuParam, const RefPtr<NG::UINode>& customNode);
    static int32_t CloseMenu(const RefPtr<NG::UINode>& customNode);
    static void JsBindContentCover(const JSCallbackInfo& info);
    static void ParseModalStyle(const JSRef<JSObject>& paramObj, NG::ModalStyle& modalStyle);
    static void ParseModalTransition(const JSRef<JSVal>& jsValue,
        std::optional<NG::ModalTransition>& modalTransition,
        NG::ModalTransition defaultTransition = NG::ModalTransition::DEFAULT);
    static void ParseEnableSafeArea(const JSRef<JSObject>& paramObj, NG::ContentCoverParam& contentCoverParam);
    static void JsBindSheet(const JSCallbackInfo& info);
    static bool CheckJSCallbackInfo(
        const std::string& callerName, const JSRef<JSVal>& tmpInfo, std::vector<JSCallbackInfoType>& infoTypes);
    static bool ParseSheetIsShow(
        const JSCallbackInfo& info, const std::string& name, std::function<void(const std::string&)>& callback);
    static RefPtr<NG::ChainedTransitionEffect> ParseChainedTransition(
        const JSRef<JSObject>& object, const JSExecutionContext& context, const RefPtr<NG::FrameNode> node = nullptr);
    static void ParseSheetStyle(
        const JSRef<JSObject>& paramObj, NG::SheetStyle& sheetStyle, bool isPartialUpdate = false);
    static NG::SheetEffectEdge ParseSheetEffectEdge(const JSRef<JSObject>& paramObj);
    static void ParseBindSheetBorderRadius(const JSRef<JSVal>& args, NG::SheetStyle& sheetStyle);
    static void ParseBindSheetBorderRadius(const JSRef<JSVal>& args,
        NG::SheetStyle& sheetStyle, RefPtr<ResourceObject>& resourceObj);
    static bool ParseBindSheetBorderRadiusProps(const JSRef<JSVal>& args, NG::BorderRadiusProperty& radius);
    static std::optional<CalcDimension> ParseBindSheetBorderRadiusProp(const JSRef<JSObject>& object,
        const char* prop, RefPtr<ResourceObject>& resourceObj);
    static bool ParseSheetMode(const std::string heightStr, NG::SheetHeight& detent);
    static bool ParseSheetDetents(const JSRef<JSVal>& args,
        std::vector<NG::SheetHeight>& sheetDetents, NG::SheetStyle& sheetStyle);
    static bool ParseSheetHeight(const JSRef<JSVal>& args, NG::SheetHeight& detent, bool isReset);
    static bool ParseSheetHeight(const JSRef<JSVal>& args,
        NG::SheetHeight& detent, bool isReset, RefPtr<ResourceObject>& resObj);
    static bool ParseSheetBackgroundBlurStyle(const JSRef<JSVal>& args, BlurStyleOption& blurStyleOptions);
    static bool ParseSheetLevel(const JSRef<JSVal>& args, NG::SheetLevel& sheetLevel);
    static void ParseCallback(const JSRef<JSObject>& paramObj,
        std::function<void(const float)>& callbackDidChange, const char* prop);
    static void ParseLifeCycleCallback(const JSRef<JSObject>& paramObj, std::function<void()>& lifeCycleCallBack,
        const char* prop);
    static void ParseSpringBackCallback(const JSRef<JSObject>& paramObj,
        std::function<void()>& sheetSpringBack, const char* prop);
    static void ParseSheetCallback(const JSRef<JSObject>& paramObj, std::function<void()>& onAppear,
        std::function<void()>& onDisappear, std::function<void()>& shouldDismiss,
        std::function<void(const int32_t info)>& onWillDismiss, std::function<void()>& onWillAppear,
        std::function<void()>& onWillDisappear, std::function<void(const float)>& onHeightDidChange,
        std::function<void(const float)>& onDetentsDidChange,
        std::function<void(const float)>& onWidthDidChange,
        std::function<void(const float)>& onTypeDidChange,
        std::function<void()>& sheetSpringBack);
    static void ParseSheetTitle(const JSRef<JSObject>& paramObj, NG::SheetStyle& sheetStyle,
        std::function<void()>& titleBuilderFunction);
    static panda::Local<panda::JSValueRef> JsDismissSheet(panda::JsiRuntimeCallInfo* runtimeCallInfo);
    static panda::Local<panda::JSValueRef> JsDismissContentCover(panda::JsiRuntimeCallInfo* runtimeCallInfo);
    static panda::Local<panda::JSValueRef> JsSheetSpringBack(panda::JsiRuntimeCallInfo* runtimeCallInfo);
    static void ParseModalTransitonEffect(
        const JSRef<JSObject>& paramObj, NG::ContentCoverParam& contentCoverParam, const JSExecutionContext& context);
    static void ParseOverlayCallback(const JSRef<JSObject>& paramObj, std::function<void()>& onAppear,
        std::function<void()>& onDisappear, std::function<void()>& onWillAppear, std::function<void()>& onWillDisappear,
        std::function<void(const int32_t& info)>& onWillDismiss);
    static void JsBorderColor(const JSCallbackInfo& info);
    static void ParseBorderColor(const JSRef<JSVal>& args);
    static void JsPadding(const JSCallbackInfo& info);
    static void JsMargin(const JSCallbackInfo& info);
    static void SetSafeAreaPadding(const JSCallbackInfo& info);
    static void ParseMarginOrPadding(const JSCallbackInfo& info, EdgeType type);
    static void ParseMarginOrPaddingCorner(JSRef<JSObject> obj, std::optional<CalcDimension>& top,
        std::optional<CalcDimension>& bottom, std::optional<CalcDimension>& left, std::optional<CalcDimension>& right);
    static void ParseMarginOrPaddingCorner(JSRef<JSObject> obj, CommonCalcDimension& commonCalcDimension);
    static void ParseLocalizedMarginOrLocalizedPaddingCorner(
        const JSRef<JSObject>& object, LocalizedCalcDimension& localizedCalcDimension);
    static bool ParseCommonMarginOrPaddingCorner(
        const JSRef<JSObject>& object, CommonCalcDimension& commonCalcDimension);
    static void GetBorderRadiusByLengthMetrics(const char* key, JSRef<JSObject>& object, CalcDimension& radius);
    static void JsOutline(const JSCallbackInfo& info);
    static void JsOutlineWidth(const JSCallbackInfo& info);
    static void JsOutlineColor(const JSCallbackInfo& info);
    static void JsOutlineStyle(const JSCallbackInfo& info);
    static void JsOutlineRadius(const JSCallbackInfo& info);
    static void JsBorder(const JSCallbackInfo& info);
    static void JsBorderWidth(const JSCallbackInfo& info);
    static void ParseBorderWidth(const JSRef<JSVal>& args);
    static void JsBorderRadius(const JSCallbackInfo& info);
    static void ParseBorderRadius(const JSRef<JSVal>& args);
    static void JsBorderStyle(const JSCallbackInfo& info);
    static void ParseBorderStyle(const JSRef<JSVal>& args);
    static void ParseDashGap(const JSRef<JSVal>& args);
    static void ParseDashWidth(const JSRef<JSVal>& args);
    static void JsBorderImage(const JSCallbackInfo& info);
    static void ParseBorderImageRepeat(const JSRef<JSVal>& args, RefPtr<BorderImage>& borderImage);
    static void ParseBorderImageOutset(const JSRef<JSVal>& args, RefPtr<BorderImage>& borderImage);
    static void ParseBorderImageSlice(const JSRef<JSVal>& args, RefPtr<BorderImage>& borderImage);
    static void ParseBorderImageWidth(const JSRef<JSVal>& args, RefPtr<BorderImage>& borderImage);
    static bool ParseBorderImageDimension(
        const JSRef<JSVal>& args, BorderImage::BorderImageOption& borderImageDimension);
    static void ParseBorderImageLengthMetrics(
        const JSRef<JSObject>& object, LocalizedCalcDimension& localizedCalcDimension);
    static void UpdateGradientWithDirection(NG::Gradient& lineGradient, NG::GradientDirection direction);
    static void ParseBorderImageLinearGradient(const JSRef<JSVal>& args, uint8_t& bitset);
    static void JsUseEffect(const JSCallbackInfo& info);
    static void JsUseShadowBatching(const JSCallbackInfo& info);
    static void JsBlur(const JSCallbackInfo& info);
    static void JsColorBlend(const JSCallbackInfo& info);
    static void JsBackdropBlur(const JSCallbackInfo& info);
    static void JsLinearGradientBlur(const JSCallbackInfo& info);
    static void JsBackgroundBrightness(const JSCallbackInfo& info);
    static void JsBackgroundBrightnessInternal(const JSCallbackInfo& info);
    static void JsForegroundBrightness(const JSCallbackInfo& info);
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
    static void JsOnAxisEvent(const JSCallbackInfo& info);
    static void JsOnHover(const JSCallbackInfo& info);
    static void JsOnHoverMove(const JSCallbackInfo& info);
    static void JsOnAccessibilityHover(const JSCallbackInfo& info);
    static void JsOnClick(const JSCallbackInfo& info);
    static void JsOnGestureJudgeBegin(const JSCallbackInfo& args);
    static void JsOnTouchIntercept(const JSCallbackInfo& info);
    static void JsShouldBuiltInRecognizerParallelWith(const JSCallbackInfo& info);
    static void JsOnGestureRecognizerJudgeBegin(const JSCallbackInfo& info);
    static void JsOnTouchTestDone(const JSCallbackInfo& info);
    static void JsClickEffect(const JSCallbackInfo& info);
    static void JsRestoreId(int32_t restoreId);
    static void JsOnVisibleAreaChange(const JSCallbackInfo& info);
    static void JsOnVisibleAreaApproximateChange(const JSCallbackInfo& info);
    static void JsHitTestBehavior(const JSCallbackInfo& info);
    static void JsOnChildTouchTest(const JSCallbackInfo& info);
    static void JsForegroundColor(const JSCallbackInfo& info);
    static void JsSetFreeze(const JSCallbackInfo& info);
    static void ParseSheetSubWindowValue(const JSRef<JSObject>& paramObj, NG::SheetStyle& sheetStyle);

    // outer border
    static void ParseOuterBorderColor(const JSRef<JSVal>& args);
    static void ParseOuterBorderWidth(const JSRef<JSVal>& args);
    static void ParseOuterBorderWidthNew(const JSRef<JSVal>& args);
    static void ParseOuterBorderRadius(const JSRef<JSVal>& args);
    static void ParseOuterBorderStyle(const JSRef<JSVal>& args);
    static void ParseEdgeOutlineWidthLeft(const JSRef<JSObject>& object, NG::BorderWidthProperty& borderWidth);
    static void ParseEdgeOutlineWidthRight(const JSRef<JSObject>& object, NG::BorderWidthProperty& borderWidth);
    static void ParseEdgeOutlineWidthTop(const JSRef<JSObject>& object, NG::BorderWidthProperty& borderWidth);
    static void ParseEdgeOutlineWidthBottom(const JSRef<JSObject>& object, NG::BorderWidthProperty& borderWidth);

    // response region
    static void JsResponseRegion(const JSCallbackInfo& info);
    static bool ParseJsResponseRegionArray(const JSRef<JSVal>& jsValue, std::vector<DimensionRect>& result);
    static bool ParseJsDimensionRect(const JSRef<JSVal>& jsValue, DimensionRect& result);

    // for dynamic $r
    static void CompleteResourceObject(JSRef<JSObject>& jsObj);
    static void CompleteResourceObjectWithBundleName(
        JSRef<JSObject>& jsObj, std::string& bundleName, std::string& moduleName, int32_t& resId);
    static bool ConvertResourceType(const std::string& typeName, ResourceType& resType);
    static bool ParseDollarResource(const JSRef<JSVal>& jsValue, std::string& targetModule, ResourceType& resType,
        std::string& resName, bool isParseType);

    // mouse response response region
    static void JsMouseResponseRegion(const JSCallbackInfo& info);

    static bool ParseJsLengthNG(
        const JSRef<JSVal>& jsValue, NG::CalcLength& result, DimensionUnit defaultUnit, bool isSupportPercent = true);
    static bool ParseJsLengthNG(const JSRef<JSVal>& jsValue, NG::CalcLength& result, DimensionUnit defaultUnit,
        RefPtr<ResourceObject>& rsourceObj, bool isSupportPercent = true);
    static bool ParseJsLengthVpNG(const JSRef<JSVal>& jsValue, NG::CalcLength& result, bool isSupportPercent = true);
    static bool ParseJsLengthVpNG(const JSRef<JSVal>& jsValue, NG::CalcLength& result,
        RefPtr<ResourceObject>& resObj, bool isSupportPercent = true);

    // for number and string with no unit, use default dimension unit.
    static bool ParseJsDimension(const JSRef<JSVal>& jsValue, CalcDimension& result, DimensionUnit defaultUnit);
    static bool ParseJsDimension(const JSRef<JSVal>& jsValue, CalcDimension& result, DimensionUnit defaultUnit,
        RefPtr<ResourceObject>& resObj);
    static bool ParseJsDimensionVp(const JSRef<JSVal>& jsValue, CalcDimension& result);
    static bool ParseJsDimensionVp(const JSRef<JSVal>& jsValue, CalcDimension& result,
        RefPtr<ResourceObject>& resObj);
    static bool ParseJsDimensionFp(const JSRef<JSVal>& jsValue, CalcDimension& result);
    static bool ParseJsDimensionFp(const JSRef<JSVal>& jsValue, CalcDimension& result,
        RefPtr<ResourceObject>& resObj);
    static bool ParseJsDimensionPx(const JSRef<JSVal>& jsValue, CalcDimension& result);
    static bool ParseJsDimensionPx(const JSRef<JSVal>& jsValue, CalcDimension& result,
        RefPtr<ResourceObject>& resObj);
    static bool ParseLengthMetricsToDimension(const JSRef<JSVal>& jsValue, CalcDimension& result);
    static bool ParseLengthMetricsToDimension(
        const JSRef<JSVal>& jsValue, CalcDimension& result, RefPtr<ResourceObject>& resObj);
    static bool ParseLengthMetricsToPositiveDimension(const JSRef<JSVal>& jsValue, CalcDimension& result);
    static bool ParseLengthMetricsToPositiveDimension(
        const JSRef<JSVal>& jsValue, CalcDimension& result, RefPtr<ResourceObject>& resObj);
    static bool ParseColorMetricsToColor(const JSRef<JSVal>& jsValue, Color& result);
    static bool ParseColorMetricsToColor(const JSRef<JSVal>& jsValue, Color& result, RefPtr<ResourceObject>& resObj);
    static bool ParseJsDouble(const JSRef<JSVal>& jsValue, double& result);
    static bool ParseJsDouble(const JSRef<JSVal>& jsValue, double& result, RefPtr<ResourceObject>& resObj);
    static bool ParseJsInt32(const JSRef<JSVal>& jsValue, int32_t& result);
    static bool ParseJsColorFromResource(const JSRef<JSVal>& jsValue, Color& result, RefPtr<ResourceObject>& resObj);
    static bool ParseJsObjColorFromResource(const JSRef<JSObject> &jsObj, Color& result,
        RefPtr<ResourceObject>& resObj);
    static bool ParseJsColor(const JSRef<JSVal>& jsValue, Color& result);
    static bool ParseJsColor(const JSRef<JSVal>& jsValue, Color& result,
        RefPtr<ResourceObject>& resObj);
    static bool ParseJsColor(const JSRef<JSVal>& jsValue, Color& result, const Color& defaultColor);
    static bool ParseJsColor(const JSRef<JSVal>& jsValue, Color& result,
        const Color& defaultColor, RefPtr<ResourceObject>& resObj);
    static bool ParseJsColorStrategy(const JSRef<JSVal>& jsValue, ForegroundColorStrategy& strategy);
    static bool ParseJsShadowColorStrategy(const JSRef<JSVal>& jsValue, ShadowColorStrategy& strategy);
    static bool ParseJsFontFamilies(const JSRef<JSVal>& jsValue, std::vector<std::string>& result);
    static bool ParseJsFontFamilies(const JSRef<JSVal>& jsValue, std::vector<std::string>& result,
        RefPtr<ResourceObject>& resObj);

    static bool ParseJsDimensionNG(
        const JSRef<JSVal>& jsValue, CalcDimension& result, DimensionUnit defaultUnit, bool isSupportPercent = true);
    static bool ParseJsDimensionNG(const JSRef<JSVal>& jsValue, CalcDimension& result,
        DimensionUnit defaultUnit, RefPtr<ResourceObject>& resObj, bool isSupportPercent = true);
    static bool ParseJsDimensionVpNG(const JSRef<JSVal>& jsValue, CalcDimension& result, bool isSupportPercent = true);
    static bool ParseJsDimensionVpNG(const JSRef<JSVal>& jsValue, CalcDimension& result,
        RefPtr<ResourceObject>& resObj, bool isSupportPercent = true);
    static bool ParseJsDimensionFpNG(const JSRef<JSVal>& jsValue, CalcDimension& result, bool isSupportPercent = true);
    static bool ParseJsDimensionFpNG(const JSRef<JSVal>& jsValue, CalcDimension& result,
        RefPtr<ResourceObject>& resObj, bool isSupportPercent = true);
    static bool ParseJsLengthMetricsVp(const JSRef<JSObject>& jsObj, CalcDimension& result);
    static bool ParseJsLengthMetricsVpWithResObj(const JSRef<JSObject>& jsObj, CalcDimension& result,
        RefPtr<ResourceObject>& rsourceObj);
    static bool ParseJsonDimension(const std::unique_ptr<JsonValue>& jsonValue, CalcDimension& result,
        DimensionUnit defaultUnit, bool checkIllegal = false);
    static bool ParseJsonDimensionVp(
        const std::unique_ptr<JsonValue>& jsonValue, CalcDimension& result, bool checkIllegal = false);
    static bool ParseJsonDouble(const std::unique_ptr<JsonValue>& jsonValue, double& result);
    static bool ParseJsonColor(const std::unique_ptr<JsonValue>& jsonValue, Color& result);
    static bool ParseJsString(const JSRef<JSVal>& jsValue, std::string& result);
    static bool ParseJsString(const JSRef<JSVal>& jsValue, std::string& result,
        RefPtr<ResourceObject>& resObj);
    static bool ParseJsString(const JSRef<JSVal>& jsValue, std::u16string& result);
    static bool ParseJsString(const JSRef<JSVal>& jsValue, std::u16string& result,
        RefPtr<ResourceObject>& resObj);
    static bool ParseJsMedia(const JSRef<JSVal>& jsValue, std::string& result);
    static bool ParseJsMedia(const JSRef<JSVal>& jsValue, std::string& result,
        RefPtr<ResourceObject>& resObj);
    static bool ParseJsMediaWithBundleName(const JSRef<JSVal>& jsValue, std::string& result, std::string& bundleName,
        std::string& moduleName, int32_t& resId);
    static bool ParseJsMediaWithBundleName(const JSRef<JSVal>& jsValue, std::string& result,
        std::string& bundleName, std::string& moduleName, int32_t& resId, RefPtr<ResourceObject>& resObj);
    static bool ParseResourceToDouble(const JSRef<JSVal>& jsValue, double& result,
        RefPtr<ResourceObject>& resObj);
    static bool ParseJsBool(const JSRef<JSVal>& jsValue, bool& result);
    static bool ParseJsBool(const JSRef<JSVal>& jsValue, bool& result,
        RefPtr<ResourceObject>& resObj);
    static bool ParseJsInteger(const JSRef<JSVal>& jsValue, uint32_t& result);
    static bool ParseJsInteger(const JSRef<JSVal>& jsValue, int32_t& result);
    static bool ParseJsIntegerArray(const JSRef<JSVal>& jsValue, std::vector<uint32_t>& result);
    static bool ParseJsIntegerArray(const JSRef<JSVal>& jsValue, std::vector<uint32_t>& result,
        RefPtr<ResourceObject>& resObj, std::vector<RefPtr<ResourceObject>>& resObjArray);
    static bool ParseJsStrArray(const JSRef<JSVal>& jsValue, std::vector<std::string>& result);
    static bool ParseJsStrArray(const JSRef<JSVal>& jsValue, std::vector<std::string>& result,
        RefPtr<ResourceObject>& resObj, std::vector<RefPtr<ResourceObject>>& resObjArray);
    static bool ParseJsLengthMetricsArray(const JSRef<JSVal>& jsValue, std::vector<Dimension>& result);
    static bool ParseJsLengthMetricsArray(const JSRef<JSVal>& jsValue, std::vector<Dimension>& result,
        std::vector<RefPtr<ResourceObject>>& resObjArray);
    static bool IsGetResourceByName(const JSRef<JSObject>& jsObj);
    static bool GetJsMediaBundleInfo(const JSRef<JSVal>& jsValue, std::string& bundleName, std::string& moduleName);
    static void ParseShadowPropsUpdate(const JSRef<JSObject>& jsObj, double& radius, Shadow& shadow);
    static bool ParseShadowProps(const JSRef<JSVal>& jsValue, Shadow& shadow, const bool configChangePerform = false);
    static void ParseShadowOffsetXY(const JSRef<JSObject>& jsObj, Shadow& shadow);
    static bool GetShadowFromTheme(ShadowStyle shadowStyle, Shadow& shadow, const bool configChangePerform = false);
    static bool ParseJsResource(const JSRef<JSVal>& jsValue, CalcDimension& result);
    static bool ParseJsResource(const JSRef<JSVal>& jsValue, CalcDimension& result,
        RefPtr<ResourceObject>& resObj);
    static bool ParseDataDetectorConfig(const JSCallbackInfo& info, TextDetectConfig& textDetectConfig);
    static bool ParseAIEntityColor(const JSRef<JSObject>& obj, TextDetectConfig& textDetectConfig);
    static bool ParseInvertProps(const JSRef<JSVal>& jsValue, InvertVariant& invert);
    static std::pair<CalcDimension, CalcDimension> ParseSize(const JSCallbackInfo& info);
    static void JsUseAlign(const JSCallbackInfo& info);
    static void JsZIndex(const JSCallbackInfo& info);
    static void SetDirection(const std::string& dir);
    static void JsSize(const JSCallbackInfo& info);
    static void JsConstraintSize(const JSCallbackInfo& info);
    static void JsLayoutPriority(const JSCallbackInfo& info);
    static void JsLayoutWeight(const JSCallbackInfo& info);

    static void JsAlign(const JSCallbackInfo& info);
    static void JsLayoutGravity(const JSCallbackInfo& info);
    static void JsPosition(const JSCallbackInfo& info);
    static void JsMarkAnchor(const JSCallbackInfo& info);
    static void JsOffset(const JSCallbackInfo& info);
    static void JsEnabled(const JSCallbackInfo& info);
    static void JsAspectRatio(const JSCallbackInfo& info);
    static void JsOverlay(const JSCallbackInfo& info);
    static Alignment ParseAlignment(int32_t align);
    static LayoutCalPolicy ParseLayoutPolicy(const std::string& layoutPolicy);
    static Alignment ParseLocalizedAlignment(std::string localizedAlignment);
    static void JsAlignRules(const JSCallbackInfo& info);
    static void JsChainMode(const JSCallbackInfo& info);

    static void SetVisibility(const JSCallbackInfo& info);
    static void Pop();

    static void JsSetDraggable(bool draggable);
    static void JsSetDragPreviewOptions(const JSCallbackInfo& info);
    static void JsOnDragStart(const JSCallbackInfo& info);
    static bool ParseAndUpdateDragItemInfo(const JSRef<JSVal>& info, NG::DragDropBaseInfo& dragInfo);
    static RefPtr<AceType> ParseDragNode(const JSRef<JSVal>& info);
    static void JsOnDragEnter(const JSCallbackInfo& info);
    static void JsOnDragSpringLoading(const JSCallbackInfo& info);
    static void JsOnDragEnd(const JSCallbackInfo& info);
    static void JsOnDragMove(const JSCallbackInfo& info);
    static void JsOnDragLeave(const JSCallbackInfo& info);
    static void JsOnPreDrag(const JSCallbackInfo& info);
    static void JsOnDrop(const JSCallbackInfo& info);
    static void JsOnAreaChange(const JSCallbackInfo& info);
    static void JsOnSizeChange(const JSCallbackInfo& info);

    static void JsLinearGradient(const JSCallbackInfo& info);
    static void JsRadialGradient(const JSCallbackInfo& info);
    static void JsSweepGradient(const JSCallbackInfo& info);
    static void NewJsLinearGradient(const JSCallbackInfo& info, NG::Gradient& gradient);
    static void NewLinearGradient(const JSRef<JSObject>& jsObj, NG::Gradient& gradient);
    static void SetGradientDirection(NG::Gradient& newGradient, const GradientDirection& direction);
    static void NewJsRadialGradient(const JSCallbackInfo& info, NG::Gradient& gradient);
    static void NewJsSweepGradient(const JSCallbackInfo& info, NG::Gradient& gradient);
    static void NewRadialGradient(const JSRef<JSObject>& jsObj, NG::Gradient& gradient);
    static void ParseSweepGradientPartly(const JSRef<JSObject>& obj, NG::Gradient& newGradient);
    static void JsMotionPath(const JSCallbackInfo& info);
    static void JsMotionBlur(const JSCallbackInfo& info);
    static void JsShadow(const JSCallbackInfo& info);
    static void JsBlendMode(const JSCallbackInfo& info);
    static void JsAdvancedBlendMode(const JSCallbackInfo& info);
    static void JsGrayScale(const JSCallbackInfo& info);
    static void JsBrightness(const JSCallbackInfo& info);
    static void JsContrast(const JSCallbackInfo& info);
    static void JsSaturate(const JSCallbackInfo& info);
    static void JsSepia(const JSCallbackInfo& info);
    static void JsInvert(const JSCallbackInfo& info);
    static void JsSystemBarEffect(const JSCallbackInfo& info);
    static void JsHueRotate(const JSCallbackInfo& info);

    static void JsClip(const JSCallbackInfo& info);
    static void JsClipShape(const JSCallbackInfo& info);

    static void ParseProgressMaskResObj(const JSRef<JSVal>& jColor, Color& colorVal,
        RefPtr<NG::ProgressMaskProperty>& progressMask);
    static void ParseJsMaskProperty(const JSRef<JSObject>& paramObject);
    static void JsMask(const JSCallbackInfo& info);
    static void JsMaskShape(const JSCallbackInfo& info);

    static void JsKey(const std::string& key);
    static void JsId(const JSCallbackInfo& info);

    static void JsFocusable(const JSCallbackInfo& info);
    static void JsTabStop(const JSCallbackInfo& info);
    static void JsNextFocus(const JSCallbackInfo& info);
    static void JsFocusBox(const JSCallbackInfo& info);
    static void JsOnFocusMove(const JSCallbackInfo& args);
    static void JsOnKeyEvent(const JSCallbackInfo& args);
    static void JsDispatchKeyEvent(const JSCallbackInfo& args);
    static void JsOnFocus(const JSCallbackInfo& args);
    static void JsOnBlur(const JSCallbackInfo& args);
    static void JsTabIndex(const JSCallbackInfo& info);
    static void JsFocusOnTouch(const JSCallbackInfo& info);
    static void JsDefaultFocus(const JSCallbackInfo& info);
    static void JsGroupDefaultFocus(const JSCallbackInfo& info);
    static void JsDebugLine(const JSCallbackInfo& info);
    static void JsOpacityPassThrough(const JSCallbackInfo& info);
    static void JsTransitionPassThrough(const JSCallbackInfo& info);
    static void JsKeyboardShortcut(const JSCallbackInfo& info);
    static void JsOnFocusAxisEvent(const JSCallbackInfo& args);
    static void JsOnCrownEvent(const JSCallbackInfo& args);

    static void JsObscured(const JSCallbackInfo& info);
    static void JsPrivacySensitive(const JSCallbackInfo& info);

    static void JsAccessibilityGroup(const JSCallbackInfo& info);
    static void JsAccessibilityText(const JSCallbackInfo& info);
    static void JsAccessibilityTextHint(const std::string& text);
    static void JsAccessibilityNextFocusId(const JSCallbackInfo& info);
    static void JsAccessibilityDescription(const JSCallbackInfo& info);
    static void JsAccessibilityImportance(const std::string& importance);
    static void JsAccessibilityLevel(const std::string& level);
    static void JsAccessibilitySelected(const JSCallbackInfo& info);
    static void JsAccessibilityChecked(const JSCallbackInfo& info);
    static void JsAccessibilityRole(const JSCallbackInfo& info);
    static std::string GetRoleByType(AccessibilityRoleType roleType);
    static void JsOnAccessibilityFocus(const JSCallbackInfo& info);
    static void JsOnAccessibilityActionIntercept(const JSCallbackInfo& info);
    static void JsOnAccessibilityHoverTransparent(const JSCallbackInfo& info);
    static void JsAccessibilityDefaultFocus(const JSCallbackInfo& info);
    static void JsAccessibilityUseSamePage(const JSCallbackInfo& info);
    static void JsAccessibilityScrollTriggerable(const JSCallbackInfo& info);
    static void JsAccessibilityFocusDrawLevel(const JSCallbackInfo& info);
    static void JsAllowDrop(const JSCallbackInfo& info);
    static void JsDrawModifier(const JSCallbackInfo& info);
    static void JsDragPreview(const JSCallbackInfo& info);
    static void JsAccessibilityVirtualNode(const JSCallbackInfo& info);

    static void ParseAccessibilityDescriptionJson(const std::string& description,
        std::pair<bool, std::string>& autoEventPair, std::pair<bool, std::string>& descriptionPair);

    static void JSCreateAnimatableProperty(const JSCallbackInfo& info);
    static void JSUpdateAnimatableProperty(const JSCallbackInfo& info);
    static void JSRenderGroup(const JSCallbackInfo& info);
    static void JSRenderFit(const JSCallbackInfo& info);
    static void JsExpandSafeArea(const JSCallbackInfo& info);
    static void JsIgnoreLayoutSafeArea(const JSCallbackInfo& info);
    static void JsGestureModifier(const JSCallbackInfo& info);
    static void JsCustomProperty(const JSCallbackInfo& info);

    static void JsBackgroundImageResizable(const JSCallbackInfo& info);
    static void JsSetDragEventStrictReportingEnabled(const JSCallbackInfo& info);
    static void JsEnableDropDisallowedBadge(const JSCallbackInfo& info);
    static void JsCancelDataLoading(const std::string& key);
    static void SetSymbolOptionApply(const JSCallbackInfo& info,
        std::function<void(WeakPtr<NG::FrameNode>)>& symbolApply, const JSRef<JSVal> modifierObj);
    static void SetTextStyleApply(const JSCallbackInfo& info,
        std::function<void(WeakPtr<NG::FrameNode>)>& textStyleApply, const JSRef<JSVal>& modifierObj);

#ifndef WEARABLE_PRODUCT
    static void JsBindPopup(const JSCallbackInfo& info);
    static void JsBindTips(const JSCallbackInfo& info);
    static void SetPopupDismiss(
        const JSCallbackInfo& info, const JSRef<JSObject>& popupObj, const RefPtr<PopupParam>& popupParam);
    static PopupOnWillDismiss ParsePopupCallback(const JSCallbackInfo& info, const JSRef<JSObject>& paramObj);
    static panda::Local<panda::JSValueRef> JsDismissPopup(panda::JsiRuntimeCallInfo* runtimeCallInfo);
    static void ParseContentPopupCommonParam(
        const JSCallbackInfo& info, const JSRef<JSObject>& popupObj, const RefPtr<PopupParam>& popupParam);
    static int32_t OpenPopup(const RefPtr<PopupParam>& param, const RefPtr<NG::UINode>& customNode);
    static int32_t UpdatePopup(const RefPtr<PopupParam>& param, const RefPtr<NG::UINode>& customNode);
    static int32_t ClosePopup(const RefPtr<NG::UINode>& customNode);
    static int32_t GetPopupParam(RefPtr<PopupParam>& param, const RefPtr<NG::UINode>& customNode);
#endif

    /**
     * Binds the native methods to the the js object
     */
    static void JSBind(BindingTarget globalObj);
    static void JsNotifyDragStartRequest(const JSCallbackInfo& info);
    static void ParseDialogCallback(const JSRef<JSObject>& paramObj,
        std::function<void(const int32_t& info, const int32_t& instanceId)>& onWillDismiss);
    static void ParseAppearDialogCallback(const JSCallbackInfo& info, DialogProperties& dialogProperties);
    static panda::Local<panda::JSValueRef> JsDismissDialog(panda::JsiRuntimeCallInfo* runtimeCallInfo);

    static RefPtr<PipelineBase> GetPipelineContext()
    {
        auto container = Container::Current();
        CHECK_NULL_RETURN(container, nullptr);
        return container->GetPipelineContext();
    }

    template<typename T>
    static RefPtr<T> GetTheme()
    {
        auto pipelineContext = GetPipelineContext();
        CHECK_NULL_RETURN(pipelineContext, nullptr);
        auto themeManager = pipelineContext->GetThemeManager();
        CHECK_NULL_RETURN(themeManager, nullptr);
        auto node = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
        return node ? themeManager->GetTheme<T>(node->GetThemeScopeId()) : themeManager->GetTheme<T>();
    }

    template<typename T>
    static RefPtr<T> GetTheme(int32_t themeScopeId)
    {
        auto pipelineContext = GetPipelineContext();
        CHECK_NULL_RETURN(pipelineContext, nullptr);
        auto themeManager = pipelineContext->GetThemeManager();
        CHECK_NULL_RETURN(themeManager, nullptr);
        return themeManager->GetTheme<T>(themeScopeId);
    }

    /**
     * box properties setter
     */
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
    static void SetBorderWidth(const CalcDimension& value, const AnimationOption& option);
    static void SetColorBlend(Color color);
    static void SetLinearGradientBlur(NG::LinearGradientBlurPara blurPara);
    static void SetDynamicLightUp(float rate, float lightUpDegree);
    static void SetBgDynamicBrightness(BrightnessOption brightnessOption);
    static void SetFgDynamicBrightness(BrightnessOption brightnessOption);
    static void SetWindowBlur(float progress, WindowBlurStyle blurStyle);
    static RefPtr<ThemeConstants> GetThemeConstants(const JSRef<JSObject>& jsObj = JSRef<JSObject>());
    static bool JsWidth(const JSRef<JSVal>& jsValue);
    static bool JsHeight(const JSRef<JSVal>& jsValue);
    static void GetBorderRadius(const char* key, JSRef<JSObject>& object, CalcDimension& radius);
    static void GetBorderRadiusResObj(const char* key, JSRef<JSObject>& object, CalcDimension& radius,
        RefPtr<ResourceObject>& resObj);
    static void RegisterTextBackgroundStyleResource(TextBackgroundStyle& textBackgroundStyle,
        RefPtr<ResourceObject>& resObjTopLeft, RefPtr<ResourceObject>& resObjTopRight,
        RefPtr<ResourceObject>& resObjBottomLeft, RefPtr<ResourceObject>& resObjBottomRight);
    static bool ParseAllBorderRadiuses(JSRef<JSObject>& object, CalcDimension& topLeft, CalcDimension& topRight,
        CalcDimension& bottomLeft, CalcDimension& bottomRight);
    static bool ParseAllBorderRadiuses(JSRef<JSObject>& object, CalcDimension& topLeft, CalcDimension& topRight,
        CalcDimension& bottomLeft, CalcDimension& bottomRight, TextBackgroundStyle& textBackgroundStyle);
    static void ParseAllBorderRadiuses(JSRef<JSObject>& object, NG::BorderRadiusProperty& borderRadius);
    static void JsPointLight(const JSCallbackInfo& info);

    template<typename T>
    static bool ParseJsInteger(const JSRef<JSVal>& jsValue, T& result)
    {
        RefPtr<ResourceObject> resObj;
        return ParseJsInteger(jsValue, result, resObj);
    }

    template<typename T>
    static bool ParseJsInteger(const JSRef<JSVal>& jsValue, T& result, RefPtr<ResourceObject>& resObj)
    {
        if (jsValue->IsNumber()) {
            result = jsValue->ToNumber<T>();
            return true;
        }

        if (!jsValue->IsObject()) {
            return false;
        }
        JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
        CompleteResourceObject(jsObj);
        int32_t resType = jsObj->GetPropertyValue<int32_t>("type", -1);
        if (resType == -1) {
            return false;
        }

        JSRef<JSVal> resId = jsObj->GetProperty("id");
        if (!resId->IsNumber()) {
            return false;
        }

        resObj = SystemProperties::ConfigChangePerform() ? GetResourceObject(jsObj) :
            GetResourceObjectByBundleAndModule(jsObj);
        auto resourceWrapper = CreateResourceWrapper(jsObj, resObj);
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
            if (resType == static_cast<int32_t>(ResourceType::INTEGER)) {
                result = static_cast<T>(resourceWrapper->GetIntByName(param->ToString()));
                return true;
            }
            return false;
        }
        if (resType == static_cast<int32_t>(ResourceType::INTEGER)) {
            result = static_cast<T>(resourceWrapper->GetInt(resId->ToNumber<uint32_t>()));
            return true;
        }
        return false;
    }

    static std::string GetFunctionKeyName(FunctionKey functionkey)
    {
        std::map<FunctionKey, std::string> keyNameMap {
            {FunctionKey::ESC, "ESC"},
            {FunctionKey::F1, "F1"},
            {FunctionKey::F2, "F2"},
            {FunctionKey::F3, "F3"},
            {FunctionKey::F4, "F4"},
            {FunctionKey::F5, "F5"},
            {FunctionKey::F6, "F6"},
            {FunctionKey::F7, "F7"},
            {FunctionKey::F8, "F8"},
            {FunctionKey::F9, "F9"},
            {FunctionKey::F10, "F10"},
            {FunctionKey::F11, "F11"},
            {FunctionKey::F12, "F12"},
            {FunctionKey::TAB, "TAB"},
            {FunctionKey::DPAD_UP, "DPAD_UP"},
            {FunctionKey::DPAD_DOWN, "DPAD_DOWN"},
            {FunctionKey::DPAD_LEFT, "DPAD_LEFT"},
            {FunctionKey::DPAD_RIGHT, "DPAD_RIGHT"}
        };
        auto result = keyNameMap.find(functionkey);
        return (result != keyNameMap.end()) ? result->second : std::string();
    }

    static bool CheckColor(const JSRef<JSVal>& jsValue, Color& result, const char* componentName, const char* propName);
    static bool CheckColor(
        const JSRef<JSVal>& jsValue, Color& result, const char* componentName, const char* propName,
        RefPtr<ResourceObject>& resourceObject);
    static bool CheckLength(
        const JSRef<JSVal>& jsValue, CalcDimension& result, const char* componentName, const char* propName);
    static bool CheckLength(
        const JSRef<JSVal>& jsValue, CalcDimension& result, const char* componentName, const char* propName,
        RefPtr<ResourceObject>& resourceObject);
    static bool CheckResource(RefPtr<ResourceObject> resourceObject,
        RefPtr<ResourceWrapper> resourceWrapper);
    static bool CheckCustomSymbolId(RefPtr<ResourceWrapper> resourceWrapper, JSRef<JSVal>& resId,
        std::uint32_t& symbolId);
    static bool ProcessSymbolObject(
        JSRef<JSObject>& jsObj, std::uint32_t& symbolId, RefPtr<ResourceObject>& symbolResourceObject);
    static bool ParseJsSymbolId(
        const JSRef<JSVal>& jsValue, uint32_t& symbolId, RefPtr<ResourceObject>& symbolResourceObject);
    static void ParseJsSymbolCustomFamilyNames(std::vector<std::string>& customFamilyNames,
        const JSRef<JSVal>& jsValue);
    static bool ParseJsSymbolColor(const JSRef<JSVal>& jsValue, std::vector<Color>& result,
        bool enableResourceUpdate = false,
        std::vector<std::pair<int32_t, RefPtr<ResourceObject>>>& resObjArr = DEFAULT_RESOURCE_PAIR_ARRAY);
    static bool ParseBorderWidthProps(const JSRef<JSVal>& args, NG::BorderWidthProperty& borderWidthProperty);
    static bool ParseBorderWidthProps(const JSRef<JSVal>& args,
        NG::BorderWidthProperty& borderWidthProperty, RefPtr<ResourceObject>& resourceObj);
    static bool ParseBorderColorProps(const JSRef<JSVal>& args, NG::BorderColorProperty& colorProperty);
    static bool ParseBorderColorProps(const JSRef<JSVal>& args,
        NG::BorderColorProperty& colorProperty, RefPtr<ResourceObject>& resourceObj);
    static bool ParseBorderStyleProps(const JSRef<JSVal>& args, NG::BorderStyleProperty& borderStyleProperty);
    static bool ParseBorderRadius(const JSRef<JSVal>& args, NG::BorderRadiusProperty& radius, bool notNegative = true);
    static void ParseCommonBorderRadiusProps(
        const JSRef<JSObject>& object, NG::BorderRadiusProperty& radius, bool notNegative = true);
    static void ParseBorderRadiusProps(const JSRef<JSObject>& object, NG::BorderRadiusProperty& radius);
    static bool ParseEditMenuOptions(const JSCallbackInfo& info, NG::OnCreateMenuCallback& onCreateMenuCallback,
        NG::OnMenuItemClickCallback& onMenuItemClick, NG::OnPrepareMenuCallback& onPrepareMenuCallback);
    static void SetDialogProperties(const JSRef<JSObject>& obj, DialogProperties& properties);
    static void SetDialogHoverModeProperties(const JSRef<JSObject>& obj, DialogProperties& properties);
    static void SetDialogBlurStyleOption(const JSRef<JSObject>& obj, DialogProperties& properties);
    static void SetDialogEffectOption(const JSRef<JSObject>& obj, DialogProperties& properties);
    static std::function<void(NG::DrawingContext& context)> GetDrawCallback(
        const RefPtr<JsFunction>& jsDraw, const JSExecutionContext& execCtx, JSRef<JSObject> modifier);

    static RefPtr<NG::ChainedTransitionEffect> ParseNapiChainedTransition(
        const JSRef<JSObject>& object, const JSExecutionContext& context);
    static void JsFocusScopeId(const JSCallbackInfo& info);
    static void JsFocusScopePriority(const JSCallbackInfo& info);
    static int32_t ParseJsPropertyId(const JSRef<JSVal>& jsValue);
    static void JsVisualEffect(const JSCallbackInfo& info);
    static void JsBackgroundFilter(const JSCallbackInfo& info);
    static void JsForegroundFilter(const JSCallbackInfo& info);
    static void JsCompositingFilter(const JSCallbackInfo& info);
    static NG::PaddingProperty GetLocalizedPadding(const std::optional<CalcDimension>& top,
        const std::optional<CalcDimension>& bottom, const std::optional<CalcDimension>& start,
        const std::optional<CalcDimension>& end);
    static NG::MarginProperty GetEdgeMargins(const CommonCalcDimension& commonCalcDimension);
    static void GetEdgeMarginsResObj(NG::MarginProperty& margins, const CommonCalcDimension& commonCalcDimension);
    static NG::PaddingProperty GetEdgePaddingsOrSafeAreaPaddings(const CommonCalcDimension& commonCalcDimension);
    static NG::BorderColorProperty GetLocalizedBorderColor(const std::optional<Color>& colorStart,
        const std::optional<Color>& colorEnd, const std::optional<Color>& colorTop,
        const std::optional<Color>& colorBottom);
    static NG::BorderColorProperty GetLocalizedBorderColor(const CommonColor& commonColor);
    static NG::BorderColorProperty GetBorderColor(const CommonColor& commonColor);
    static NG::BorderRadiusProperty GetLocalizedBorderRadius(const std::optional<Dimension>& radiusTopStart,
        const std::optional<Dimension>& radiusTopEnd, const std::optional<Dimension>& radiusBottomStart,
        const std::optional<Dimension>& radiusBottomEnd);
    static void ParseDetentSelection(const JSRef<JSObject>& paramObj, NG::SheetStyle& sheetStyle);
    template<typename T>
    static void RegisterResource(const std::string& key, const RefPtr<ResourceObject>& resObj, T value)
    {
        auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->RegisterResource<T>(key, resObj, value);
    }
    static void UnRegisterResource(const std::string& key);
    static void ParseDragSpringLoadingConfiguration(
        const JSRef<JSObject>& paramObj, const RefPtr<NG::DragSpringLoadingConfiguration>& config);
    static void SetBorderRadiusWithCheck(std::optional<NG::BorderRadiusProperty>& result,
        NG::BorderRadiusProperty& dimension);
    static bool CheckLengthMetrics(const JSRef<JSObject>& object);
    static void CompleteResourceObjectFromColor(RefPtr<ResourceObject>& resObj,
        Color& color, bool state);

private:
    static bool CheckDarkResource(const RefPtr<ResourceObject>& resObj);
    static bool ParseJsStrArrayInternal(const JSRef<JSArray>& jsArray, std::vector<std::string>& result,
        std::vector<RefPtr<ResourceObject>>& resObjArray);
    static bool ParseJsIntegerArrayInternal(const JSRef<JSArray>& jsArray, std::vector<uint32_t>& result,
        std::vector<RefPtr<ResourceObject>>& resObjArray);
    static bool ParseJsStringObj(const JSRef<JSVal>& jsValue, std::string& result, RefPtr<ResourceObject>& resObj);
    static bool ParseJSMediaWithRawFile(const JSRef<JSObject>& jsObj, std::string& result,
        RefPtr<ResourceWrapper>& resourceWrapper);
    static bool ParseJSMediaInternal(const JSRef<JSObject>& jsValue, std::string& result,
        RefPtr<ResourceObject>& resObj);
    static bool ParseResourceToDoubleByName(
        const JSRef<JSObject>& jsObj, int32_t resType, const RefPtr<ResourceWrapper>& resourceWrapper, double& result);
    static bool ParseResourceToDoubleById(
        int32_t resId, int32_t resType, const RefPtr<ResourceWrapper>& resourceWrapper, double& result);
    static bool ParseJsDimensionByNameInternal(const JSRef<JSObject>& jsObj, CalcDimension& result,
        DimensionUnit defaultUnit, RefPtr<ResourceWrapper>& resourceWrapper, int32_t resType);
    static void ParseMenuItemsSymbolId(const JSRef<JSVal>& jsStartIcon, NG::MenuOptionsParam& menuOptionsParam);
    static std::vector<NG::MenuOptionsParam> ParseMenuItems(const JSRef<JSArray>& menuItemsArray, bool showShortcut);
    static void ParseOnCreateMenu(
        const JSCallbackInfo& info, const JSRef<JSVal>& jsFunc, NG::OnCreateMenuCallback& onCreateMenuCallback);
    static void ParseOnPrepareMenu(
        const JSCallbackInfo& info, const JSRef<JSVal>& jsFunc, NG::OnPrepareMenuCallback& onPrepareMenuCallback);
    static JSRef<JSVal> CreateJsTextMenuItem(const NG::MenuItemParam& menuItemParam);
    static JSRef<JSVal> CreateJsTextRange(const NG::MenuItemParam& menuItemParam);
    static JSRef<JSObject> CreateJsTextMenuId(const std::string& id);
    static JSRef<JSArray> CreateJsOnMenuItemClick(const NG::MenuItemParam& menuItemParam);
    static JSRef<JSVal> CreateJsSystemMenuItems(const std::vector<NG::MenuItemParam>& systemMenuItems);
    static void CompleteResourceObjectInner(
        JSRef<JSObject>& jsObj, std::string& bundleName, std::string& moduleName, int32_t& resIdValue);
    static NG::LayoutSafeAreaEdge ParseJsLayoutSafeAreaEdgeArray(
        const JSRef<JSArray>& jsSafeAreaEdges, NG::LayoutSafeAreaEdge defaultVal);
    static bool ParseAllBorderRadiusesForOutLine(JSRef<JSObject>& object, NG::BorderRadiusProperty& borderRadius);
    static void GetBorderRadiusTopLeft(const JSRef<JSVal>& jsValue, NG::BorderRadiusProperty& borderRadius);
    static void GetBorderRadiusTopRight(const JSRef<JSVal>& jsValue, NG::BorderRadiusProperty& borderRadius);
    static void GetBorderRadiusBottomLeft(const JSRef<JSVal>& jsValue, NG::BorderRadiusProperty& borderRadius);
    static void GetBorderRadiusBottomRight(const JSRef<JSVal>& jsValue, NG::BorderRadiusProperty& borderRadius);
    static void ParseSweepGradientCenter(NG::Gradient& newGradient, const JSRef<JSArray> centerArray);
    static void ParseRadialGradientCenter(NG::Gradient& newGradient, const JSRef<JSArray> centerArray);
    static void NewParseGradientColor(NG::Gradient& gradient, RefPtr<ResourceObject>& resObj,
        NG::GradientColor& gradientColor, int32_t& indx);
    static void NewParseSweepGradientColor(NG::Gradient& gradient, RefPtr<ResourceObject>& resObj,
        NG::GradientColor& gradientColor, int32_t& indx);
    static void NewParseRadialGradientColor(NG::Gradient& gradient, RefPtr<ResourceObject>& resObj,
        NG::GradientColor& gradientColor, int32_t& indx);
    static bool ParseBackgroundBuilder(
        const JSCallbackInfo& info, const JSRef<JSVal>& jsFunc, std::function<void()>& builderFunc);
};
} // namespace OHOS::Ace::Framework
#endif // JS_VIEW_ABSTRACT_H
