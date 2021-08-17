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
#include "core/components/box/box_component.h"
#include "core/components/navigation_bar/navigation_container_component.h"
#include "core/components/theme/theme_manager.h"
#include "core/components/transform/transform_component.h"
#include "core/pipeline/base/component.h"

namespace OHOS::Ace::Framework {

class JSViewAbstract {
public:
    static void SetPadding(const Dimension& value);
    static void SetPaddings(
        const Dimension& top, const Dimension& bottom, const Dimension& left, const Dimension& right);
    static void SetMargin(const Dimension& value);
    static void SetMargins(
        const Dimension& top, const Dimension& bottom, const Dimension& left, const Dimension& right);
    static Dimension GetDimension(const std::string& key, const std::unique_ptr<JsonValue>& jsonValue);
    static void GetDimension(
        const std::string& key, const std::unique_ptr<JsonValue>& jsonValue, std::optional<Dimension>& out);
    static void GetDimension(const std::unique_ptr<JsonValue>& jsonValue, std::optional<Dimension>& out);
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
    static void JsGridSpan(const JSCallbackInfo& Info);
    static void JsGridOffset(const JSCallbackInfo& info);
    static void JsUseSizeType(const JSCallbackInfo& Info);
    static Dimension ParseDimension(const JSCallbackInfo& info);
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
    static void JsOffset(const JSCallbackInfo& info);
    static void JsEnabled(const JSCallbackInfo& info);
    static void JsAspectRatio(const JSCallbackInfo& info);
    static void JsOverlay(const JSCallbackInfo& info);
    static Alignment ParseAlignment(int32_t align);

    static void SetVisibility(int value);
    static uint32_t ColorAlphaAdapt(uint32_t origin);
    static void Pop();

    static void JsOnDrag(const JSCallbackInfo& info);
    static void JsOnDragEnter(const JSCallbackInfo& info);
    static void JsOnDragLeave(const JSCallbackInfo& info);
    static void JsOnDrop(const JSCallbackInfo& info);

    static void JsLinearGradient(const JSCallbackInfo& info);
    static void JsRadialGradient(const JSCallbackInfo& info);
    static void JsSweepGradient(const JSCallbackInfo& info);
    static void JsMotionPath(const JSCallbackInfo& info);
    static void JsShadow(const JSCallbackInfo& info);

    static void JsClip(const JSCallbackInfo& info);
    static void JsMask(const JSCallbackInfo& info);

    /**
     * Binds the native methods to the the js object
     */
    static void JSBind();

    static JSValue JsToolBar(JSContext* ctx, JSValueConst this_value, int32_t argc, JSValueConst* argv);

protected:
    /**
     * box properties setter
     */
    static RefPtr<Decoration> GetFrontDecoration();
    static RefPtr<Decoration> GetBackDecoration();
    static const Border& GetBorder();
    static RefPtr<NavigationDeclaration> GetNavigationDeclaration();
    static void SetMarginTop(const std::string& value);
    static void SetMarginBottom(const std::string& value);
    static void SetMarginLeft(const std::string& value);
    static void SetMarginRight(const std::string& value);
    static void SetMargin(const std::string& value);
    static void SetPaddingTop(const std::string& value);
    static void SetPaddingBottom(const std::string& value);
    static void SetPaddingLeft(const std::string& value);
    static void SetPaddingRight(const std::string& value);
    static void SetBorder(const Border& border);
    static void SetBorderStyle(int32_t style);
    static void SetBorderRadius(const Dimension& value, const AnimationOption& option);
    static void SetBorderColor(const Color& color, const AnimationOption& option);
    static void SetBorderWidth(const Dimension& value, const AnimationOption& option);
    static void SetBlur(float radius);
    static void SetBackdropBlur(float radius);
    static void SetWindowBlur(float progress, WindowBlurStyle blurStyle);
    static void SetNavigationTitle(const std::string& title);
    static void SetNavigationSubTitle(const std::string& subTitle);
    static void SetHideNavigationBar(bool hide);
    static void SetHideNavigationBackButton(bool hide);
    static void SetHideToolBar(bool hide);
    static Dimension ToDimension(const JSRef<JSVal>& jsVal);
    static bool ToDimension(const JSRef<JSVal>& jsVal, Dimension& dim);
    static RefPtr<ThemeConstants> GetThemeConstants();
    template<typename T>
    static RefPtr<T> GetTheme()
    {
        RefPtr<ThemeManager> themeManager = AceType::MakeRefPtr<ThemeManager>();
        return themeManager->GetTheme<T>();
    }
};
} // namespace OHOS::Ace::Framework
#endif // JS_VIEW_ABSTRACT_H
