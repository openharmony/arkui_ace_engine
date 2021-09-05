/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include <functional>
#include <optional>

#include "base/json/json_util.h"
#include "base/log/ace_trace.h"
#include "base/log/log.h"
#include "base/memory/ace_type.h"
#include "bridge/declarative_frontend/engine/bindings.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "core/common/container.h"
#include "core/components/box/box_component.h"
#include "core/components/navigation_bar/navigation_container_component.h"
#include "core/components/theme/theme_manager.h"
#include "core/components/transform/transform_component.h"
#include "core/pipeline/base/component.h"

#include "resource_manager.h"

namespace OHOS::Ace::Framework {

enum class ResourceType : uint32_t {
    COLOR = 10001,
    FLOAT,
    STRING,
    PLURAL,
    MEDIA = 20000,
};

class JSViewAbstract {
public:
    static void SetPadding(const Dimension& value);
    static void SetPaddings(
        const Dimension& top, const Dimension& bottom, const Dimension& left, const Dimension& right);
    static void SetMargin(const Dimension& value);
    static void SetMargins(
        const Dimension& top, const Dimension& bottom, const Dimension& left, const Dimension& right);
    static void GetAngle(
        const std::string& key, const std::unique_ptr<JsonValue>& jsonValue, std::optional<float>& angle);
    static void GetGradientColorStops(Gradient& gradient, const std::unique_ptr<JsonValue>& jsonValue);

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
    static void ParseAndSetTransitionOption(std::unique_ptr<JsonValue>& transitionArgs);
    static void JsWidth(const JSCallbackInfo& info);
    static void JsHeight(const JSCallbackInfo& info);
    static void JsBackgroundColor(const JSCallbackInfo& info);
    static void JsBackgroundImage(const JSCallbackInfo& info);
    static void JsBackgroundImageSize(const JSCallbackInfo& info);
    static void JsBackgroundImagePosition(const JSCallbackInfo& info);
    static void JsBorderColor(const JSCallbackInfo& info);
    static void JsPadding(const JSCallbackInfo& info);
    static void JsMargin(const JSCallbackInfo& info);
    static void ParseMarginOrPadding(const JSCallbackInfo& info, bool isMargin);
    static void JsBorder(const JSCallbackInfo& info);
    static void JsBorderWidth(const JSCallbackInfo& info);
    static void JsBorderRadius(const JSCallbackInfo& info);
    static void JsBlur(const JSCallbackInfo& info);
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

    // for number and string with no unit, use default dimension unit.
    static bool ParseJsDimension(const JSRef<JSVal>& jsValue, Dimension& result, DimensionUnit defaultUnit);
    static bool ParseJsDimensionVp(const JSRef<JSVal>& jsValue, Dimension& result);
    static bool ParseJsAnimatableDimensionVp(const JSRef<JSVal>& jsValue, AnimatableDimension& result);
    static bool ParseJsDimensionFp(const JSRef<JSVal>& jsValue, Dimension& result);
    static bool ParseJsDimensionPx(const JSRef<JSVal>& jsValue, Dimension& result);
    static bool ParseJsDouble(const JSRef<JSVal>& jsValue, double& result);
    static bool ParseJsColor(const JSRef<JSVal>& jsValue, Color& result);
    static bool ParseJsFontFamilies(const JSRef<JSVal>& jsValue, std::vector<std::string>& result);

    static bool ParseJsonDimension(const std::unique_ptr<JsonValue>& jsonValue, Dimension& result,
        DimensionUnit defaultUnit);
    static bool ParseJsonDimensionVp(const std::unique_ptr<JsonValue>& jsonValue, Dimension& result);
    static bool ParseJsonDouble(const std::unique_ptr<JsonValue>& jsonValue, double& result);
    static bool ParseJsonColor(const std::unique_ptr<JsonValue>& jsonValue, Color& result);
    static bool ParseJsString(const JSRef<JSVal>& jsValue, std::string& result);
    static bool ParseJsMedia(const JSRef<JSVal>& jsValue, std::string& result);

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

    static void SetVisibility(int value);
    static void Pop();

    static void JsOnDrag(const JSCallbackInfo& info);
    static void JsOnDragEnter(const JSCallbackInfo& info);
    static void JsOnDragMove(const JSCallbackInfo& info);
    static void JsOnDragLeave(const JSCallbackInfo& info);
    static void JsOnDrop(const JSCallbackInfo& info);

    static void JsLinearGradient(const JSCallbackInfo& info);
    static void JsRadialGradient(const JSCallbackInfo& info);
    static void JsSweepGradient(const JSCallbackInfo& info);
    static void JsMotionPath(const JSCallbackInfo& info);
    static void JsShadow(const JSCallbackInfo& info);
    static void JsGrayScale(const JSCallbackInfo& info);
    static void JsBrightness(const JSCallbackInfo& info);
    static void JsContrast(const JSCallbackInfo& info);
    static void JsSaturate(const JSCallbackInfo& info);

    static void JsClip(const JSCallbackInfo& info);
    static void JsMask(const JSCallbackInfo& info);
#if defined(WINDOWS_PLATFORM) || defined(MAC_PLATFORM)
    static void JsDebugLine(const JSCallbackInfo& info);
#endif
    static void JsOpacityPassThrough(const JSCallbackInfo& info);
    static void JsTransitionPassThrough(const JSCallbackInfo& info);

    static void JsAccessibilityGroup(bool accessible);
    static void JsAccessibilityText(const std::string& text);
    static void JsAccessibilityDescription(const std::string& description);
    static void JsAccessibilityImportance(const std::string& importance);
    static RefPtr<AccessibilityNode> GetAccessibilityNodeById(int32_t nodeId);

#ifndef WEARABLE_PRODUCT
    static void JsBindPopup(const JSCallbackInfo& info);
#endif

    /**
     * Binds the native methods to the the js object
     */
    static void JSBind();

#ifdef USE_QUICKJS_ENGINE
    static JSValue JsToolBar(JSContext* ctx, JSValueConst this_value, int32_t argc, JSValueConst* argv);
#elif USE_V8_ENGINE
    static void JsToolBar(const v8::FunctionCallbackInfo<v8::Value>& info);
#elif USE_ARK_ENGINE
    static panda::Local<panda::JSValueRef> JsToolBar(panda::EcmaVM* vm,
        panda::Local<panda::JSValueRef> thisObj, const panda::Local<panda::JSValueRef> argv[], int32_t argc,
        void* data);
#endif // USE_ARK_ENGINE

protected:
    /**
     * box properties setter
     */
    static RefPtr<Decoration> GetFrontDecoration();
    static RefPtr<Decoration> GetBackDecoration();
    static const Border& GetBorder();
    static RefPtr<NavigationDeclaration> GetNavigationDeclaration();
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
    static void SetBorderRadius(const Dimension& value, const AnimationOption& option);
    static void SetBorderColor(const Color& color, const AnimationOption& option);
    static void SetBorderWidth(const Dimension& value, const AnimationOption& option);
    static void SetBlur(float radius);
    static void SetBackdropBlur(float radius);
    static void SetBlurRadius(const RefPtr<Decoration>& decoration, float radius);
    static void SetWindowBlur(float progress, WindowBlurStyle blurStyle);
    static void SetNavigationTitle(const std::string& title);
    static void SetNavigationSubTitle(const std::string& subTitle);
    static void SetHideNavigationBar(bool hide);
    static void SetHideNavigationBackButton(bool hide);
    static void SetHideToolBar(bool hide);
    static RefPtr<ThemeConstants> GetThemeConstants();
    static std::shared_ptr<Global::Resource::ResourceManager> GetResourceManager();
    static bool JsWidth(const JSRef<JSVal>& jsValue);
    static bool JsHeight(const JSRef<JSVal>& jsValue);
    template<typename T>
    static RefPtr<T> GetTheme()
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
        auto themeManager = pipelineContext->GetThemeManager();
        if (!themeManager) {
            LOGE("themeManager is null!");
            return nullptr;
        }
        return themeManager->GetTheme<T>();
    }
};
} // namespace OHOS::Ace::Framework
#endif // JS_VIEW_ABSTRACT_H
