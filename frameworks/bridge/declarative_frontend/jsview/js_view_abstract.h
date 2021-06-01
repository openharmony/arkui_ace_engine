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

#include "base/json/json_util.h"
#include "base/log/ace_trace.h"
#include "base/log/log.h"
#include "core/animation/curve_animation.h"
#include "core/animation/keyframe_animation.h"
#include "core/components/common/properties/tween_option.h"
#include "core/pipeline/base/component.h"
#include "frameworks/core/components/box/box_component.h"
#include "frameworks/core/components/theme/theme_manager.h"
#include "frameworks/core/components/transform/transform_component.h"
#include "frameworks/core/components/tween/tween_component.h"

#ifdef USE_QUICKJS_ENGINE
#ifdef __cplusplus
extern "C" {
#endif
#include "third_party/quickjs/quickjs.h"
#ifdef __cplusplus
}
#endif

#include "frameworks/bridge/declarative_frontend/engine/bindings.h"
#include "frameworks/bridge/js_frontend/engine/quickjs/qjs_utils.h"
#endif // USE_QUICKJS_ENGINE

#ifdef USE_V8_ENGINE
#include "third_party/v8/include/v8.h"

#include "frameworks/bridge/declarative_frontend/engine/bindings.h"
#include "frameworks/bridge/declarative_frontend/engine/v8/v8_bindings.h"
#include "frameworks/bridge/declarative_frontend/engine/v8/v8_utils.h"
#endif

namespace OHOS::Ace::Framework {
using ViewId = uint32_t;
class JSAnimation;

class JSViewAbstract : public virtual AceType {
    DECLARE_ACE_TYPE(JSViewAbstract, AceType);

public:
    JSViewAbstract();
    ~JSViewAbstract() = default;

    /**
     * This implements the composition of the specialized and generic components
     * such as box, tween, transform, display etc.
     */
    RefPtr<OHOS::Ace::Component> CreateComponent();

    /**
     * Subclasses which are custom view should implement this interface to mark
     * the view need update upon state changes.
     * For Example JSView and JSForEach are custom view and should implement.
     */
    virtual void MarkNeedUpdate() {}
    virtual bool NeedsUpdate()
    {
        return false;
    }

    /**
     * All Subclasses should implement this.
     * Should take care of releasing the handles of js objects
     */
    virtual void Destroy(JSViewAbstract* parentCustomView);

    /**
     * Subclasses which are custom view should implement this interface and return true.
     * For Example JSView and JSForEach are custom view and should return true.
     */
    virtual bool IsCustomView()
    {
        return false;
    }

    /**
     * Subclasses which are custom view should implement this interface and return true.
     * For Example JSView and JSForEach are custom view and should return true.
     */
    virtual bool IsForEachView()
    {
        return false;
    }

    /**
     * Views which do not have a state can mark static.
     * The element will be reused and re-render will be skipped.
     */
    void MarkStatic()
    {
        isStatic_ = true;
    }

    void SetPadding(const Dimension& value);
    void SetPaddings(const Dimension& top, const Dimension& bottom, const Dimension& left, const Dimension& right);
    void SetMargin(const Dimension& value);
    void SetMargins(const Dimension& top, const Dimension& bottom, const Dimension& left, const Dimension& right);
    void SetBorderWidth(const Dimension& value);
    void SetLeftBorderWidth(const Dimension& value);
    void SetTopBorderWidth(const Dimension& value);
    void SetRightBorderWidth(const Dimension& value);
    void SetBottomBorderWidth(const Dimension& value);
    void SetBorderRadius(const Dimension& value);
    Dimension GetDimension(const std::string& key, const std::unique_ptr<JsonValue>& jsonValue);

#ifdef USE_QUICKJS_ENGINE
    virtual void MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc) {}
    virtual void ReleaseRT(JSRuntime* rt) {}

    static JSValue JsSetUniqueKey(JSContext* ctx, JSValueConst this_value, int argc, JSValueConst* argv);
    static JSValue JsMarkStaticView(JSContext* ctx, JSValueConst this_value, int argc, JSValueConst* argv);

    static JSValue JsAnimate(JSContext* ctx, JSValueConst this_value, int32_t argc, JSValueConst* argv);
    static JSValue JsScale(JSContext* ctx, JSValueConst this_value, int32_t argc, JSValueConst* argv);
    static JSValue JsOpacity(JSContext* ctx, JSValueConst this_value, int32_t argc, JSValueConst* argv);
    static JSValue JsTranslate(JSContext* ctx, JSValueConst this_value, int32_t argc, JSValueConst* argv);
    static JSValue JsTranslateX(JSContext* ctx, JSValueConst this_value, int32_t argc, JSValueConst* argv);
    static JSValue JsTranslateY(JSContext* ctx, JSValueConst this_value, int32_t argc, JSValueConst* argv);
    static JSValue JsRotate(JSContext* ctx, JSValueConst this_value, int32_t argc, JSValueConst* argv);
    static JSValue JsWidth(JSContext* ctx, JSValueConst this_value, int32_t argc, JSValueConst* argv);
    static JSValue JsHeight(JSContext* ctx, JSValueConst this_value, int32_t argc, JSValueConst* argv);
    static JSValue JsBackgroundColor(JSContext* ctx, JSValueConst this_value, int32_t argc, JSValueConst* argv);
    static JSValue JsBorderColor(JSContext* ctx, JSValueConst this_value, int32_t argc, JSValueConst* argv);
    static JSValue JsPadding(JSContext* ctx, JSValueConst this_value, int32_t argc, JSValueConst* argv);
    static JSValue JsMargin(JSContext* ctx, JSValueConst this_value, int32_t argc, JSValueConst* argv);
    static JSValue ParseMarginOrPadding(
        JSContext* ctx, JSValueConst this_value, int32_t argc, JSValueConst* argv, bool isMargin);
    static JSValue JsBorder(JSContext* ctx, JSValueConst this_value, int32_t argc, JSValueConst* argv);
    static JSValue JsBorderWidth(JSContext* ctx, JSValueConst this_value, int32_t argc, JSValueConst* argv);
    static JSValue JsBorderRadius(JSContext* ctx, JSValueConst this_value, int32_t argc, JSValueConst* argv);
    static JSValue ParseDimension(
        JSContext* ctx, JSValueConst this_value, int32_t argc, JSValueConst* argv, Dimension& result);
#endif // USE_QUICKJS_ENGINE

#ifdef USE_V8_ENGINE
    static void JsAnimate(const v8::FunctionCallbackInfo<v8::Value>& info);
    static void JsScale(const v8::FunctionCallbackInfo<v8::Value>& info);
    static void JsOpacity(const v8::FunctionCallbackInfo<v8::Value>& info);
    static void JsTranslate(const v8::FunctionCallbackInfo<v8::Value>& info);
    static void JsTranslateX(const v8::FunctionCallbackInfo<v8::Value>& info);
    static void JsTranslateY(const v8::FunctionCallbackInfo<v8::Value>& info);
    static void JsRotate(const v8::FunctionCallbackInfo<v8::Value>& info);
    static void JsWidth(const v8::FunctionCallbackInfo<v8::Value>& info);
    static void JsHeight(const v8::FunctionCallbackInfo<v8::Value>& info);
    static void JsBackgroundColor(const v8::FunctionCallbackInfo<v8::Value>& info);
    static void JsBorderColor(const v8::FunctionCallbackInfo<v8::Value>& info);
    static void JsPadding(const v8::FunctionCallbackInfo<v8::Value>& info);
    static void JsMargin(const v8::FunctionCallbackInfo<v8::Value>& info);
    static void ParseMarginOrPadding(const v8::FunctionCallbackInfo<v8::Value>& info, bool isMargin);
    static void JsBorder(const v8::FunctionCallbackInfo<v8::Value>& info);
    static void JsBorderWidth(const v8::FunctionCallbackInfo<v8::Value>& info);
    static void JsBorderRadius(const v8::FunctionCallbackInfo<v8::Value>& info);
    static Dimension ParseDimension(const v8::FunctionCallbackInfo<v8::Value>& info);
#endif

    template<typename T>
    RefPtr<T> GetTheme() const
    {
        RefPtr<ThemeManager> themeManager = AceType::MakeRefPtr<ThemeManager>();
        return themeManager->GetTheme<T>();
    }

    /**
     * Binds the native methods to the the js object
     */
    static void JSBind();

protected:
    /**
     * Subclasses need to implement this interface to return their specialized components,
     * Which will be added to the last node of the component tree.
     * For Ex- JSText should return TextComponent
     */
    virtual RefPtr<OHOS::Ace::Component> CreateSpecializedComponent() = 0;

    /**
     * The results of this function will be combined with ther results of the
     * CreateSpecializedComponent in CreateComponent. The specialized
     * component will be put inside of the containers created by this method.
     * Components will be reparented so that front container will be the
     * outermost and last will be the innermost.
     */
    virtual std::vector<RefPtr<OHOS::Ace::SingleChild>> CreateInteractableComponents()
    {
        return {};
    }

    bool IsStatic()
    {
        return isStatic_;
    }

    bool HasUniqueKey()
    {
        return !uniqueKey_.empty();
    }

    std::string GetUniqueKey()
    {
        return uniqueKey_;
    }

    /**
     * The Below getters are used by JSButton
     */
    Dimension ViewWidth() const;
    Dimension ViewHeight() const;

    const Color& BackGroundColor() const
    {
        return backGroundColor_;
    }
    const Dimension& ViewRadius() const;

    bool GetUserDefColor() const
    {
        return userDefColor_;
    }

    bool GetIsDefHeight() const
    {
        return isDefHeight_;
    }

    bool GetIsDefWidth() const
    {
        return isDefWidth_;
    }

#ifdef USE_QUICKJS_ENGINE
    // STATIC QuickJS functions
    template<typename T>
    static JSValue JsSetSingleString(JSContext* ctx, JSValueConst this_value, int32_t argc, JSValueConst* argv,
        std::function<void(T* view, std::string)> setterFunc, const char* debugInfo);
#endif

    RefPtr<BoxComponent> GetOrMakeBoxComponent() const;
    RefPtr<Decoration> GetBackDecoration() const;
    const Border& GetBorder() const;
    BorderEdge GetLeftBorderEdge();
    BorderEdge GetTopBorderEdge();
    BorderEdge GetRightBorderEdge();
    BorderEdge GetBottomBorderEdge();

    void SetBorderEdge(const BorderEdge& edge);
    void SetLeftBorderEdge(const BorderEdge& edge);
    void SetTopBorderEdge(const BorderEdge& edge);
    void SetRightBorderEdge(const BorderEdge& edge);
    void SetBottomBorderEdge(const BorderEdge& edge);
    void SetBorder(const Border& border);

    mutable RefPtr<BoxComponent> boxComponent_;
    RefPtr<DisplayComponent> displayComponent_;

    ViewId getViewId()
    {
        return viewId_;
    }

private:

    void setUniqueKey(std::string key)
    {
        uniqueKey_ = std::string(key);
    }

    /**
     * box properties setter
     */
    void SetWidth(const Dimension& width);
    void SetHeight(const Dimension& height);
    void SetMarginTop(const std::string& value);
    void SetMarginBottom(const std::string& value);
    void SetMarginLeft(const std::string& value);
    void SetMarginRight(const std::string& value);
    void SetMargin(const std::string& value);
    void SetPaddingTop(const std::string& value);
    void SetPaddingBottom(const std::string& value);
    void SetPaddingLeft(const std::string& value);
    void SetPaddingRight(const std::string& value);
    void SetPadding(const std::string& value);
    void SetBackgroundColor(const Color& color);
    void ProcessBackgroundColor();
    void SetBorderStyle(int32_t style);
    void SetBorderColor(const Color& color);
    void SetLeftBorderColor(const Color& color);
    void SetTopBorderColor(const Color& color);
    void SetRightBorderColor(const Color& color);
    void SetBottomBorderColor(const Color& color);

    /**
     * Animation and transform
     */
    void ProcessAnimation();
    void CleanPendingAnimation();
    void CreateAnimation(JSAnimation* animation);
    void SetScale(double endScale);
    void SetOpacity(double endOpacity);
    void SetTranslate(double deltaX, double deltaY);
    void SetRotate(double degree);

    RefPtr<TweenComponent> tweenComponent_;
    RefPtr<TransformComponent> transformComponent_;

    ViewId viewId_;
    std::string uniqueKey_;
    Color backGroundColor_;
    bool userDefColor_ = false;
    bool isDefHeight_ = false;
    bool isDefWidth_ = false;
    TweenOption tweenOption_;

    bool isStatic_ = false;
    bool animationInitialized_ = false;
};

} // namespace OHOS::Ace::Framework

#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.inl"

#endif // JS_VIEW_ABSTRACT_H
