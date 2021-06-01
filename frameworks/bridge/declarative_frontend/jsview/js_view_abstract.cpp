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

#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"

#include "base/json/json_util.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_animation.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_register.h"
#include "frameworks/core/animation/keyframe.h"
#include "frameworks/core/animation/keyframe_animation.h"

namespace OHOS::Ace::Framework {

namespace {
constexpr uint32_t COLOR_ALPHA_OFFSET = 24;
constexpr uint32_t COLOR_ALPHA_VALUE = 0xFF000000;
} // namespace

static std::atomic<uint32_t> g_nextUnusedViewId = { 0 };

uint32_t ColorAlphaAdapt(uint32_t origin)
{
    uint32_t result = origin;
    if (origin >> COLOR_ALPHA_OFFSET == 0) {
        result = origin | COLOR_ALPHA_VALUE;
    }
    return result;
}

JSViewAbstract ::JSViewAbstract() : viewId_(++g_nextUnusedViewId), uniqueKey_()
{
    tweenOption_ = TweenOption();
}

void JSViewAbstract::Destroy(JSViewAbstract* parentCustomView)
{
    LOGD("JSViewAbstract::Destroy start");
    RemoveViewById(viewId_);
    LOGD("JSViewAbstract::Destroy end");
}

void JSViewAbstract::CleanPendingAnimation()
{
    if (tweenOption_.IsValid()) {
        auto& colorAnimation = tweenOption_.GetColorAnimation();
        if (colorAnimation) {
            if (!boxComponent_) {
                boxComponent_ = AceType::MakeRefPtr<BoxComponent>();
            }
            boxComponent_->SetColor(colorAnimation->GetEndValue());
        }

        auto& propertyFloatMap = tweenOption_.GetFloatPropertyAnimation();
        if (!propertyFloatMap.empty()) {
            if (!boxComponent_) {
                boxComponent_ = AceType::MakeRefPtr<BoxComponent>();
            }
            for (auto&& [property, animation] : propertyFloatMap) {
                if (property == PropertyAnimatableType::PROPERTY_WIDTH) {
                    boxComponent_->SetWidth(animation->GetEndValue());
                } else if (property == PropertyAnimatableType::PROPERTY_HEIGHT) {
                    boxComponent_->SetHeight(animation->GetEndValue());
                }
            }
        }

        if (tweenOption_.HasTransformFloatChanged()) {
            if (!transformComponent_) {
                transformComponent_ = AceType::MakeRefPtr<TransformComponent>();
            }

            for (auto& [type, animation] : tweenOption_.GetTransformFloatAnimation()) {
                if (type == AnimationType::SCALE) {
                    transformComponent_->Scale(animation->GetEndValue());
                } else if (type == AnimationType::ROTATE_Z) {
                    transformComponent_->RotateZ(animation->GetEndValue());
                }
            }
        }

        if (tweenOption_.HasTransformOffsetChanged()) {
            if (!transformComponent_) {
                transformComponent_ = AceType::MakeRefPtr<TransformComponent>();
            }
            for (auto& [type, animation] : tweenOption_.GetTranslateAnimations()) {
                if (type == AnimationType::TRANSLATE) {
                    auto endValue = animation->GetEndValue();
                    transformComponent_->Translate(endValue.GetX(), endValue.GetY());
                }
            }
        }

        auto& opacityAnimation = tweenOption_.GetOpacityAnimation();
        if (opacityAnimation) {
            displayComponent_ = AceType::MakeRefPtr<DisplayComponent>();
            displayComponent_->SetOpacity(opacityAnimation->GetEndValue());
        }
    }
}

void JSViewAbstract::ProcessAnimation()
{
    if (animationInitialized_ && tweenOption_.IsValid()) {
        transformComponent_ = AceType::MakeRefPtr<TransformComponent>();
        displayComponent_ = AceType::MakeRefPtr<DisplayComponent>();
        tweenComponent_ = AceType::MakeRefPtr<TweenComponent>(HasUniqueKey() ? GetUniqueKey() : "Wrapped", "Tween");
        tweenComponent_->SetTweenOption(tweenOption_);
        tweenComponent_->MarkDeclarativeAniamtion();
        tweenComponent_->SetTweenOperation(TweenOperation::PLAY);
        tweenComponent_->SetIsFirstFrameShow(false);
        return;
    }
    CleanPendingAnimation();
}

RefPtr<Component> JSViewAbstract::CreateComponent()
{
    auto specializedComponent = CreateSpecializedComponent();

    if (IsCustomView() || IsForEachView()) {
        if (IsStatic()) {
            specializedComponent->SetStatic();
        }
        return specializedComponent;
    }

    ProcessAnimation();

    std::vector<RefPtr<SingleChild>> components;
    if (tweenComponent_) {
        components.emplace_back(std::move(tweenComponent_));
    } else if (HasUniqueKey()) {
        components.emplace_back(AceType::MakeRefPtr<OHOS::Ace::ComposedComponent>(GetUniqueKey(), "Wrapped"));
    }

    if (displayComponent_) {
        components.emplace_back(std::move(displayComponent_));
    }

    if (transformComponent_) {
        components.emplace_back(std::move(transformComponent_));
    }

    for (auto&& component : CreateInteractableComponents()) {
        components.emplace_back(std::move(component));
    }

    if (boxComponent_) {
        components.emplace_back(std::move(boxComponent_));
    }

    // First, composite all components.
    for (int32_t idx = static_cast<int32_t>(components.size()) - 1; idx - 1 >= 0; --idx) {
        components[idx - 1]->SetChild(DynamicCast<Component>(components[idx]));
    }

    if (components.empty()) {
        if (IsStatic()) {
            specializedComponent->SetStatic();
        }
        return specializedComponent;
    }

    const auto& parent = components.back();
    if (parent) {
        parent->SetChild(specializedComponent);
    }

    auto component = AceType::DynamicCast<Component>(components.front());
    if (IsStatic()) {
        component->SetStatic();
    }
    return component;
}

void JSViewAbstract::CreateAnimation(JSAnimation* animation)
{
    if (animation) {
        tweenOption_.SetDuration(animation->GetDuration());
        tweenOption_.SetDelay(animation->GetDelay());
        tweenOption_.SetCurve(CreateCurve(animation->GetAnimationCurve()));
        LOGD("CreateAnimation: duration: %{public}d", animation->GetDuration());
    } else {
        // Use default options.
        LOGW("CreateAnimation: animation object is not provided. Using default options.");
        tweenOption_.SetDuration(500);
        tweenOption_.SetDelay(0);
        tweenOption_.SetCurve(CreateCurve("linear"));
    }
    tweenOption_.SetIteration(1);
    tweenOption_.SetFillMode(FillMode::FORWARDS);

    if (animation && animation->GetNone()) {
        LOGD("CreateAnimation: animation.none()");
        animationInitialized_ = false;
        tweenOption_.SkipAllPendingAnimation();
    } else {
        animationInitialized_ = true;
    }
}

void JSViewAbstract::SetScale(double endScale)
{
    LOGD("CreateScaleAnimation()");
    auto scaleAnimation = AceType::MakeRefPtr<KeyframeAnimation<float>>();
    auto keyframe = AceType::MakeRefPtr<Keyframe<float>>(1.0f, endScale);
    scaleAnimation->AddKeyframe(keyframe);
    scaleAnimation->SetDeclarativeAnimation(true);
    tweenOption_.SetTransformFloatAnimation(AnimationType::SCALE, scaleAnimation);
}

void JSViewAbstract::SetOpacity(double endOpacity)
{
    LOGD("CreateOpacityAnimation()");
    auto opacityAnimation = AceType::MakeRefPtr<KeyframeAnimation<float>>();
    auto keyframe1 = AceType::MakeRefPtr<Keyframe<float>>(1.0f, endOpacity);
    opacityAnimation->AddKeyframe(keyframe1);
    opacityAnimation->SetDeclarativeAnimation(true);
    tweenOption_.SetOpacityAnimation(opacityAnimation);
}

void JSViewAbstract::SetTranslate(double deltaX, double deltaY)
{
    // 'VP' (Density independent pixels) is the default.
    auto translate = AceType::MakeRefPtr<CurveAnimation<DimensionOffset>>(DimensionOffset(Dimension(), Dimension()),
        DimensionOffset(Dimension(deltaX, DimensionUnit::VP), Dimension(deltaY, DimensionUnit::VP)), Curves::LINEAR);

    translate->SetDeclarativeAnimation(true);
    tweenOption_.SetTranslateAnimations(AnimationType::TRANSLATE, translate);
}

void JSViewAbstract::SetRotate(double angle)
{
    auto rotate = AceType::MakeRefPtr<CurveAnimation<float>>(0.0f, angle, Curves::LINEAR);
    rotate->SetDeclarativeAnimation(true);
    tweenOption_.SetTransformFloatAnimation(AnimationType::ROTATE_Z, rotate);
}

#ifdef USE_QUICKJS_ENGINE
JSValue JSViewAbstract::JsSetUniqueKey(JSContext* ctx, JSValueConst thisValue, int argc, JSValueConst* argv)
{
    return JsSetSingleString<JSViewAbstract>(
        ctx, thisValue, argc, argv, [](JSViewAbstract* view, std::string value) { view->setUniqueKey(value); },
        "setUniqueKey");
}

JSValue JSViewAbstract::JsMarkStaticView(JSContext* ctx, JSValueConst thisValue, int argc, JSValueConst* argv)
{
    if (JS_IsNull(thisValue)) {
        LOGD("thisValue is null, exisitng");
        return thisValue;
    }

    if (!JS_IsObject(thisValue)) {
        LOGD("thisValue is NOT an object, exisitng");
        return thisValue;
    }

    JSViewAbstract* view = static_cast<JSViewAbstract*>(UnwrapAny(thisValue));
    if (!view) {
        LOGE("view is null!");
        return thisValue;
    }
    view->MarkStatic();
    return JS_DupValue(ctx, thisValue); // for call chaining?
}

JSValue JSViewAbstract::JsAnimate(JSContext* ctx, JSValueConst thisValue, int32_t argc, JSValueConst* argv)
{
    LOGD("--> JsAnimate");
    JSViewAbstract* view = static_cast<JSViewAbstract*>(UnwrapAny(thisValue));
    if (!view) {
        LOGE("JsAnimate: view is null!");
        return thisValue;
    }

    if (argv == nullptr) {
        LOGE("JsAnimate: argv error.");
        return thisValue;
    }

    if (argc == 0) {
        LOGW("JsAnimate: No Animation object is provided. Using default animation options.");
        view->CreateAnimation(nullptr);
        return JS_DupValue(ctx, thisValue);
    }
    if (argc != 1) {
        LOGE("JsAnimate: The arg is wrong, it is supposed to have 1 or 0 arguments.");
        return thisValue;
    }
    if (!JS_IsObject(argv[0])) {
        LOGE("JsAnimate: argv[] is not object.");
        return thisValue;
    }

    QJSContext::Scope scope(ctx);
    JSAnimation* animationObj = Unwrap<JSAnimation>(argv[0]);
    if (!animationObj) {
        LOGE("JsAnimate: Animation object is null!");
        return thisValue;
    }

    view->CreateAnimation(animationObj);
    LOGD("<-- JsAnimate");
    return JS_DupValue(ctx, thisValue);
}

JSValue JSViewAbstract::JsScale(JSContext* ctx, JSValueConst thisValue, int32_t argc, JSValueConst* argv)
{
    LOGD("js_scale_effect");
    if ((argv == nullptr) || (argc < 1)) {
        LOGE("argv or argc error, argc = %{private}d", argc);
        return thisValue;
    }
    if (!JS_IsNumber(argv[0])) {
        LOGE("argv[] is not object.");
        return thisValue;
    }

    if (argc == 2 && JS_IsObject(argv[1])) {
        JsAnimate(ctx, thisValue, 1, &argv[1]);
        JS_FreeValue(ctx, thisValue);
    }

    JSViewAbstract* view = static_cast<JSViewAbstract*>(UnwrapAny(thisValue));
    if (!view) {
        LOGE("view is null!");
        return thisValue;
    }

    QJSContext::Scope scope(ctx);
    double value = 0.0;
    JS_ToFloat64(ctx, &value, argv[0]);
    view->SetScale(value);
    return JS_DupValue(ctx, thisValue);
}

JSValue JSViewAbstract::JsOpacity(JSContext* ctx, JSValueConst thisValue, int32_t argc, JSValueConst* argv)
{
    LOGD("js_opacity");
    if ((argv == nullptr) || (argc < 1)) {
        LOGE("argv or argc error, argc = %{private}d", argc);
        return thisValue;
    }
    if (!JS_IsNumber(argv[0])) {
        LOGE("argv[] is not a number.");
        return thisValue;
    }

    if (argc == 2 && JS_IsObject(argv[1])) {
        JsAnimate(ctx, thisValue, 1, &argv[1]);
        JS_FreeValue(ctx, thisValue);
    }

    JSViewAbstract* view = static_cast<JSViewAbstract*>(UnwrapAny(thisValue));
    if (!view) {
        LOGE("view is null!");
        return thisValue;
    }

    QJSContext::Scope scope(ctx);
    double value = 0.0;
    JS_ToFloat64(ctx, &value, argv[0]);

    view->SetOpacity(value);
    return JS_DupValue(ctx, thisValue);
}

JSValue JSViewAbstract::JsTranslate(JSContext* ctx, JSValueConst thisValue, int32_t argc, JSValueConst* argv)
{
    LOGD("js_translate");
    if ((argv == nullptr) || (argc < 1)) {
        LOGE("argv or argc error, argc = %{private}d", argc);
        return thisValue;
    }
    if (!JS_IsNumber(argv[0])) {
        LOGE("argv[] is not a number.");
        return thisValue;
    }

    if (argc == 2 && JS_IsObject(argv[1])) {
        JsAnimate(ctx, thisValue, 1, &argv[1]);
        JS_FreeValue(ctx, thisValue);
    }

    JSViewAbstract* view = static_cast<JSViewAbstract*>(UnwrapAny(thisValue));
    if (!view) {
        LOGE("view is null!");
        return thisValue;
    }

    QJSContext::Scope scope(ctx);
    double value = 0.0;
    JS_ToFloat64(ctx, &value, argv[0]);

    view->SetTranslate(value, value);
    return JS_DupValue(ctx, thisValue);
}

JSValue JSViewAbstract::JsTranslateX(JSContext* ctx, JSValueConst thisValue, int32_t argc, JSValueConst* argv)
{
    LOGD("js_translate");
    if ((argv == nullptr) || (argc < 1)) {
        LOGE("argv or argc error, argc = %{private}d", argc);
        return thisValue;
    }
    if (!JS_IsNumber(argv[0])) {
        LOGE("argv[] is not a number.");
        return thisValue;
    }

    if (argc == 2 && JS_IsObject(argv[1])) {
        JsAnimate(ctx, thisValue, 1, &argv[1]);
        JS_FreeValue(ctx, thisValue);
    }

    JSViewAbstract* view = static_cast<JSViewAbstract*>(UnwrapAny(thisValue));
    if (!view) {
        LOGE("view is null!");
        return thisValue;
    }

    QJSContext::Scope scope(ctx);
    double value = 0.0;
    JS_ToFloat64(ctx, &value, argv[0]);

    view->SetTranslate(value, 0.0f);
    return JS_DupValue(ctx, thisValue);
}

JSValue JSViewAbstract::JsTranslateY(JSContext* ctx, JSValueConst thisValue, int32_t argc, JSValueConst* argv)
{
    LOGD("js_translate");
    if ((argv == nullptr) || (argc < 1)) {
        LOGE("argv or argc error, argc = %{private}d", argc);
        return thisValue;
    }
    if (!JS_IsNumber(argv[0])) {
        LOGE("argv[] is not a number.");
        return thisValue;
    }

    if (argc == 2 && JS_IsObject(argv[1])) {
        JsAnimate(ctx, thisValue, 1, &argv[1]);
        JS_FreeValue(ctx, thisValue);
    }

    JSViewAbstract* view = static_cast<JSViewAbstract*>(UnwrapAny(thisValue));
    if (!view) {
        LOGE("view is null!");
        return thisValue;
    }

    QJSContext::Scope scope(ctx);
    double value = 0.0;
    JS_ToFloat64(ctx, &value, argv[0]);

    view->SetTranslate(0.0f, value);
    return JS_DupValue(ctx, thisValue);
}

JSValue JSViewAbstract::JsRotate(JSContext* ctx, JSValueConst thisValue, int32_t argc, JSValueConst* argv)
{
    LOGD("js_translate");
    if ((argv == nullptr) || (argc < 1)) {
        LOGE("argv or argc error, argc = %{private}d", argc);
        return thisValue;
    }
    if (!JS_IsNumber(argv[0])) {
        LOGE("argv[] is not a number.");
        return thisValue;
    }

    if (argc == 2 && JS_IsObject(argv[1])) {
        JsAnimate(ctx, thisValue, 1, &argv[1]);
        JS_FreeValue(ctx, thisValue);
    }

    JSViewAbstract* view = static_cast<JSViewAbstract*>(UnwrapAny(thisValue));
    if (!view) {
        LOGE("view is null!");
        return thisValue;
    }

    QJSContext::Scope scope(ctx);
    double value = 0.0;
    JS_ToFloat64(ctx, &value, argv[0]);

    view->SetRotate(value);
    return JS_DupValue(ctx, thisValue);
}

JSValue JSViewAbstract::JsWidth(JSContext* ctx, JSValueConst thisValue, int32_t argc, JSValueConst* argv)
{
    if ((argv == nullptr) || (argc < 1)) {
        return JS_ThrowSyntaxError(ctx, "js_width: one parameter of type number expected");
    }
    if (!JS_IsNumber(argv[0]) && !JS_IsString(argv[0])) {
        return JS_ThrowSyntaxError(ctx, "js_width: parameter of type number or string expected");
    }

    if (!JS_IsObject(thisValue)) {
        return JS_ThrowInternalError(ctx, "js_width: Failed to unwrap JS object to C++ JSView! this is not an object!");
    }

    if (argc == 2 && JS_IsObject(argv[1])) {
        JsAnimate(ctx, thisValue, 1, &argv[1]);
        JS_FreeValue(ctx, thisValue);
    }

    QJSContext::Scope scope(ctx);
    JSViewAbstract* view = static_cast<JSViewAbstract*>(UnwrapAny(thisValue));
    if (!view) {
        return JS_ThrowInternalError(ctx, "js_width: Failed to unwrap JS object to C++ JSView!");
    }

    Dimension value;
    if (JS_IsNumber(argv[0])) {
        double length = 0.0;
        JS_ToFloat64(ctx, &length, argv[0]);
        value = Dimension(length, DimensionUnit::VP);
    } else {
        value = StringUtils::StringToDimension(ScopedString(argv[0]).str(), true);
    }
    view->SetWidth(value);
    return JS_DupValue(ctx, thisValue);
}

JSValue JSViewAbstract::JsHeight(JSContext* ctx, JSValueConst thisValue, int32_t argc, JSValueConst* argv)
{
    if ((argv == nullptr) || (argc < 1)) {
        return JS_ThrowSyntaxError(ctx, "js_height: one parameter of type number expected");
    }
    if (!JS_IsNumber(argv[0]) && !JS_IsString(argv[0])) {
        return JS_ThrowSyntaxError(ctx, "js_height: parameter of type number expected");
    }

    if (!JS_IsObject(thisValue)) {
        return JS_ThrowInternalError(
            ctx, "js_height: Failed to unwrap JS object to C++ JSView! this is not an object!");
    }

    if (argc == 2 && JS_IsObject(argv[1])) {
        JsAnimate(ctx, thisValue, 1, &argv[1]);
        JS_FreeValue(ctx, thisValue);
    }

    QJSContext::Scope scope(ctx);
    JSViewAbstract* view = static_cast<JSViewAbstract*>(UnwrapAny(thisValue));
    if (!view) {
        return JS_ThrowInternalError(ctx, "js_height: Failed to unwrap JS object to C++ JSView!");
    }

    Dimension value;
    if (JS_IsNumber(argv[0])) {
        double length = 0.0;
        JS_ToFloat64(ctx, &length, argv[0]);
        value = Dimension(length, DimensionUnit::VP);
    } else {
        value = StringUtils::StringToDimension(ScopedString(argv[0]).str(), true);
    }
    view->SetHeight(value);
    return JS_DupValue(ctx, thisValue);
}

JSValue JSViewAbstract::JsBackgroundColor(JSContext* ctx, JSValueConst thisValue, int32_t argc, JSValueConst* argv)
{
    if ((argv == nullptr) || (argc < 1)) {
        return JS_ThrowSyntaxError(ctx, "js_background_color: one parameter of type string expected");
    }
    if (!JS_IsString(argv[0]) && !JS_IsNumber(argv[0])) {
        return JS_ThrowSyntaxError(ctx, "js_background_color: parameter of type string or number expected");
    }

    if (argc == 2 && JS_IsObject(argv[1])) {
        JsAnimate(ctx, thisValue, 1, &argv[1]);
        JS_FreeValue(ctx, thisValue);
    }

    QJSContext::Scope scope(ctx);
    JSViewAbstract* view = static_cast<JSViewAbstract*>(UnwrapAny(thisValue));
    if (!view) {
        return JS_ThrowInternalError(ctx, "js_background_color: Failed to unwrap JS object to C++ JSView!");
    }

    Color color;
    if (JS_IsString(argv[0])) {
        color = Color::FromString(ScopedString(argv[0]).str());
    } else if (JS_IsNumber(argv[0])) {
        uint32_t colorValue;
        JS_ToUint32(ctx, &colorValue, argv[0]);
        color = Color(ColorAlphaAdapt(colorValue));
    }
    view->SetBackgroundColor(color);
    return JS_DupValue(ctx, thisValue);
}

JSValue JSViewAbstract::JsBorderColor(JSContext* ctx, JSValueConst thisValue, int32_t argc, JSValueConst* argv)
{
    if ((argv == nullptr) || (argc < 1)) {
        return JS_ThrowSyntaxError(ctx, "JsBorderColor: one parameter of type string expected");
    }
    if (!JS_IsString(argv[0]) && !JS_IsNumber(argv[0])) {
        return JS_ThrowSyntaxError(ctx, "JsBorderColor: parameter of type string or number expected");
    }

    if (argc == 2 && JS_IsObject(argv[1])) {
        JsAnimate(ctx, thisValue, 1, &argv[1]);
        JS_FreeValue(ctx, thisValue);
    }

    QJSContext::Scope scope(ctx);
    JSViewAbstract* view = static_cast<JSViewAbstract*>(UnwrapAny(thisValue));
    if (!view) {
        return JS_ThrowInternalError(ctx, "JsBorderColor: Failed to unwrap JS object to C++ JSView!");
    }

    Color color;
    if (JS_IsString(argv[0])) {
        color = Color::FromString(ScopedString(argv[0]).str());
    } else if (JS_IsNumber(argv[0])) {
        uint32_t colorValue;
        JS_ToUint32(ctx, &colorValue, argv[0]);
        color = Color(ColorAlphaAdapt(colorValue));
    }
    view->SetBorderColor(color);
    return JS_DupValue(ctx, thisValue);
}

JSValue JSViewAbstract::JsPadding(JSContext* ctx, JSValueConst thisValue, int32_t argc, JSValueConst* argv)
{
    return ParseMarginOrPadding(ctx, thisValue, argc, argv, false);
}

JSValue JSViewAbstract::JsMargin(JSContext* ctx, JSValueConst thisValue, int32_t argc, JSValueConst* argv)
{
    return ParseMarginOrPadding(ctx, thisValue, argc, argv, true);
}

JSValue JSViewAbstract::ParseMarginOrPadding(
    JSContext* ctx, JSValueConst thisValue, int32_t argc, JSValueConst* argv, bool isMargin)
{
    if ((argv == nullptr) || (argc < 1)) {
        return JS_ThrowSyntaxError(ctx, "Less than one parameter");
    }
    if (!JS_IsString(argv[0]) && !JS_IsNumber(argv[0]) && !JS_IsObject(argv[0])) {
        return JS_ThrowSyntaxError(ctx, "Parameter of type string or number or object expected");
    }
    QJSContext::Scope scope(ctx);
    JSViewAbstract* view = static_cast<JSViewAbstract*>(UnwrapAny(thisValue));
    if (!view) {
        return JS_ThrowInternalError(ctx, "Failed to unwrap JS object to C++ JSView!");
    }

    if (JS_IsObject(argv[0])) {
        auto argsPtrItem = JsonUtil::ParseJsonString(ScopedString::Stringify(argv[0]));
        if (!argsPtrItem) {
            LOGE("Js Parse object failed. argsPtr is null. %s", ScopedString::Stringify(argv[0]).c_str());
            return thisValue;
        }
        if (argsPtrItem->IsNull()) {
            LOGE("Js Parse failed. argsPtr is null. %s", ScopedString::Stringify(argv[0]).c_str());
            return thisValue;
        }
        Dimension topDimen = view->GetDimension("top", argsPtrItem);
        Dimension bottomDimen = view->GetDimension("bottom", argsPtrItem);
        Dimension leftDimen = view->GetDimension("left", argsPtrItem);
        Dimension rightDimen = view->GetDimension("right", argsPtrItem);
        if (isMargin) {
            view->SetMargins(topDimen, bottomDimen, leftDimen, rightDimen);
        } else {
            view->SetPaddings(topDimen, bottomDimen, leftDimen, rightDimen);
        }
    } else if (JS_IsString(argv[0])) {
        if (isMargin) {
            view->SetMargin(StringUtils::StringToDimension(ScopedString(argv[0]).str(), true));
        } else {
            view->SetPadding(StringUtils::StringToDimension(ScopedString(argv[0]).str(), true));
        }
    } else if (JS_IsNumber(argv[0])) {
        double length = 0.0;
        JS_ToFloat64(ctx, &length, argv[0]);
        if (isMargin) {
            view->SetMargin(Dimension(length, DimensionUnit::VP));
        } else {
            view->SetPadding(Dimension(length, DimensionUnit::VP));
        }
    }
    return JS_DupValue(ctx, thisValue);
}

JSValue JSViewAbstract::JsBorder(JSContext* ctx, JSValueConst thisValue, int32_t argc, JSValueConst* argv)
{
    if ((argv == nullptr) || (argc < 1)) {
        return JS_ThrowSyntaxError(ctx, "JsBorder: less than one parameter");
    }
    if (!JS_IsObject(argv[0])) {
        return JS_ThrowSyntaxError(ctx, "JsBorder: parameter of type object expected");
    }
    QJSContext::Scope scope(ctx);
    JSViewAbstract* view = static_cast<JSViewAbstract*>(UnwrapAny(thisValue));
    if (!view) {
        return JS_ThrowInternalError(ctx, "JsBorder: Failed to unwrap JS object to C++ JSView!");
    }
    auto argsPtrItem = JsonUtil::ParseJsonString(ScopedString::Stringify(argv[0]));
    if (!argsPtrItem) {
        LOGE("Js Parse Border failed. argsPtr is null. %s", ScopedString::Stringify(argv[0]).c_str());
        return thisValue;
    }
    if (argsPtrItem->IsNull()) {
        LOGE("Js Parse Border failed. argsPtr is null. %s", ScopedString::Stringify(argv[0]).c_str());
        return thisValue;
    }

    Dimension width = view->GetDimension("width", argsPtrItem);
    Dimension radius = view->GetDimension("radius", argsPtrItem);
    auto borderStyle = argsPtrItem->GetInt("style", static_cast<int32_t>(BorderStyle::SOLID));
    std::unique_ptr<JsonValue> colorValue = argsPtrItem->GetValue("color");
    Color color;
    if (colorValue->IsString()) {
        color = Color::FromString(colorValue->GetString());
    } else if (colorValue->IsNumber()) {
        color = Color(ColorAlphaAdapt(colorValue->GetUInt()));
    }
    LOGD("JsBorder width = %lf unit = %d, radius = %lf unit = %d, borderStyle = %d, color = %x", width.Value(),
        width.Unit(), radius.Value(), radius.Unit(), borderStyle, color.GetValue());
    view->SetBorderStyle(borderStyle);
    view->SetBorderColor(color);
    view->SetBorderWidth(width);
    view->SetBorderRadius(radius);
    return JS_DupValue(ctx, thisValue);
}

JSValue JSViewAbstract::JsBorderWidth(JSContext* ctx, JSValueConst thisValue, int32_t argc, JSValueConst* argv)
{
    JSViewAbstract* view = static_cast<JSViewAbstract*>(UnwrapAny(thisValue));
    if (!view) {
        return JS_ThrowInternalError(ctx, "JsBorder: Failed to unwrap JS object to C++ JSView!");
    }
    Dimension borderWidth;
    JSValue result = ParseDimension(ctx, thisValue, argc, argv, borderWidth);
    LOGD("borderWidth = %lf unit = %d", borderWidth.Value(), borderWidth.Unit());
    view->SetBorderWidth(borderWidth);
    return result;
}

JSValue JSViewAbstract::JsBorderRadius(JSContext* ctx, JSValueConst thisValue, int32_t argc, JSValueConst* argv)
{
    JSViewAbstract* view = static_cast<JSViewAbstract*>(UnwrapAny(thisValue));
    if (!view) {
        return JS_ThrowInternalError(ctx, "JsBorder: Failed to unwrap JS object to C++ JSView!");
    }
    Dimension borderRadius;
    JSValue result = ParseDimension(ctx, thisValue, argc, argv, borderRadius);
    view->SetBorderRadius(borderRadius);
    LOGD("borderRadius = %lf unit = %d", borderRadius.Value(), borderRadius.Unit());
    return result;
}

JSValue JSViewAbstract::ParseDimension(
    JSContext* ctx, JSValueConst thisValue, int32_t argc, JSValueConst* argv, Dimension& result)
{
    if ((argv == nullptr) || (argc < 1)) {
        LOGE("At least one parameter expected");
        return JS_ThrowSyntaxError(ctx, "At least one parameter expected");
    }
    if (!JS_IsNumber(argv[0]) && !JS_IsString(argv[0])) {
        return JS_ThrowSyntaxError(ctx, "Parameter of type number or string expected");
    }
    if (!JS_IsObject(thisValue)) {
        return JS_ThrowInternalError(ctx, "Failed to unwrap JS object to C++ JSView! this is not an object!");
    }
    QJSContext::Scope scope(ctx);
    JSViewAbstract* view = static_cast<JSViewAbstract*>(UnwrapAny(thisValue));
    if (!view) {
        return JS_ThrowInternalError(ctx, "Failed to unwrap JS object to C++ JSView!");
    }

    if (JS_IsNumber(argv[0])) {
        double length = 0.0;
        JS_ToFloat64(ctx, &length, argv[0]);
        result = Dimension(length, DimensionUnit::VP);
    } else {
        result = StringUtils::StringToDimension(ScopedString(argv[0]).str(), true);
    }
    return JS_DupValue(ctx, thisValue);
}
#endif // USE_QUICKJS_ENGINE

#ifdef USE_V8_ENGINE
void JSViewAbstract::JsAnimate(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    LOGD("--> JsAnimate");
    auto isolate = info.GetIsolate();
    v8::HandleScope scp(isolate);
    auto context = isolate->GetCurrentContext();

    JSViewAbstract* view = static_cast<JSViewAbstract*>(info.This()->GetAlignedPointerFromInternalField(0));
    if (!view) {
        LOGE("view is null!");
        return;
    }

    if (info.Length() == 0) {
        LOGW("JsAnimate: No Animation object is provided. Using default animation options.");
        view->CreateAnimation(nullptr);
        info.GetReturnValue().Set(info.This());
        return;
    }

    if (info.Length() != 1) {
        LOGE("JsAnimate: The arg is wrong, it is supposed to have 1 or 0 arguments.");
        return;
    }
    if (!info[0]->IsObject()) {
        LOGE("JsAnimate: arg is not object.");
        return;
    }

    v8::Local<v8::Object> obj = info[0]->ToObject(context).ToLocalChecked();
    JSAnimation* animationObj = static_cast<JSAnimation*>(obj->GetAlignedPointerFromInternalField(0));
    if (!animationObj) {
        LOGE("JsAnimate: Animation object is null!");
        info.GetReturnValue().Set(info.This());
        return;
    }

    view->CreateAnimation(animationObj);
    info.GetReturnValue().Set(info.This());
    LOGD("<-- JsAnimate");
}

void JSViewAbstract::JsScale(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    LOGD("js_scale");
    auto isolate = info.GetIsolate();
    v8::HandleScope scp(isolate);
    auto context = isolate->GetCurrentContext();

    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    if (!info[0]->IsNumber()) {
        LOGE("arg is not Number.");
        return;
    }

    if (info.Length() == 2 && info[1]->IsObject()) {
        JsAnimate(info);
    }

    JSViewAbstract* view = static_cast<JSViewAbstract*>(info.This()->GetAlignedPointerFromInternalField(0));
    if (!view) {
        LOGE("view is null!");
        return;
    }

    view->SetScale(info[0]->NumberValue(context).ToChecked());
    info.GetReturnValue().Set(info.This());
}

void JSViewAbstract::JsOpacity(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    LOGD("js_opacity");
    auto isolate = info.GetIsolate();
    v8::HandleScope scp(isolate);
    auto context = isolate->GetCurrentContext();

    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    if (!info[0]->IsNumber()) {
        LOGE("arg is not Number.");
        return;
    }

    if (info.Length() == 2 && info[1]->IsObject()) {
        JsAnimate(info);
    }

    JSViewAbstract* view = static_cast<JSViewAbstract*>(info.This()->GetAlignedPointerFromInternalField(0));
    if (!view) {
        LOGE("view is null!");
        return;
    }

    view->SetOpacity(info[0]->NumberValue(context).ToChecked());
    info.GetReturnValue().Set(info.This());
}

void JSViewAbstract::JsTranslate(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    LOGD("js_translate");
    auto isolate = info.GetIsolate();
    v8::HandleScope scp(isolate);
    auto context = isolate->GetCurrentContext();

    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    if (!info[0]->IsNumber()) {
        LOGE("arg is not Number.");
        return;
    }

    if (info.Length() == 2 && info[1]->IsObject()) {
        JsAnimate(info);
    }

    JSViewAbstract* view = static_cast<JSViewAbstract*>(info.This()->GetAlignedPointerFromInternalField(0));
    if (!view) {
        LOGE("view is null!");
        return;
    }

    view->SetTranslate(info[0]->NumberValue(context).ToChecked(), info[0]->NumberValue(context).ToChecked());
    info.GetReturnValue().Set(info.This());
}

void JSViewAbstract::JsTranslateX(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    LOGD("JsTranslateX");
    auto isolate = info.GetIsolate();
    v8::HandleScope scp(isolate);
    auto context = isolate->GetCurrentContext();

    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    if (!info[0]->IsNumber()) {
        LOGE("arg is not Number.");
        return;
    }

    if (info.Length() == 2 && info[1]->IsObject()) {
        JsAnimate(info);
    }

    JSViewAbstract* view = static_cast<JSViewAbstract*>(info.This()->GetAlignedPointerFromInternalField(0));
    if (!view) {
        LOGE("view is null!");
        return;
    }

    view->SetTranslate(info[0]->NumberValue(context).ToChecked(), 0.0);
    info.GetReturnValue().Set(info.This());
}

void JSViewAbstract::JsTranslateY(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    LOGD("JsTranslateY");
    auto isolate = info.GetIsolate();
    v8::HandleScope scp(isolate);
    auto context = isolate->GetCurrentContext();

    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    if (!info[0]->IsNumber()) {
        LOGE("arg is not Number.");
        return;
    }

    if (info.Length() == 2 && info[1]->IsObject()) {
        JsAnimate(info);
    }

    JSViewAbstract* view = static_cast<JSViewAbstract*>(info.This()->GetAlignedPointerFromInternalField(0));
    if (!view) {
        LOGE("view is null!");
        return;
    }

    view->SetTranslate(0.0, info[0]->NumberValue(context).ToChecked());
    info.GetReturnValue().Set(info.This());
}

void JSViewAbstract::JsRotate(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    LOGD("js_translate");
    auto isolate = info.GetIsolate();
    v8::HandleScope scp(isolate);
    auto context = isolate->GetCurrentContext();

    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    if (!info[0]->IsNumber()) {
        LOGE("arg is not Number.");
        return;
    }

    if (info.Length() == 2 && info[1]->IsObject()) {
        JsAnimate(info);
    }

    JSViewAbstract* view = static_cast<JSViewAbstract*>(info.This()->GetAlignedPointerFromInternalField(0));
    if (!view) {
        LOGE("view is null!");
        return;
    }

    view->SetRotate(info[0]->NumberValue(context).ToChecked());
    info.GetReturnValue().Set(info.This());
}

void JSViewAbstract::JsWidth(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    auto isolate = info.GetIsolate();
    v8::HandleScope scp(isolate);
    auto context = isolate->GetCurrentContext();

    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    if (!info[0]->IsNumber() && !info[0]->IsString()) {
        LOGE("arg is not Number or String.");
        return;
    }

    if (info.Length() == 2 && info[1]->IsObject()) {
        JsAnimate(info);
    }

    JSViewAbstract* view = static_cast<JSViewAbstract*>(info.This()->GetAlignedPointerFromInternalField(0));
    if (!view) {
        LOGE("view is null!");
        return;
    }
    Dimension value;
    if (info[0]->IsNumber()) {
        value = Dimension(info[0]->NumberValue(context).ToChecked(), DimensionUnit::VP);
    } else {
        value = StringUtils::StringToDimension(V8Utils::ScopedString(info[0]).get(), true);
    }
    view->SetWidth(value);
    info.GetReturnValue().Set(info.This());
}

void JSViewAbstract::JsHeight(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    auto isolate = info.GetIsolate();
    v8::HandleScope scp(isolate);
    auto context = isolate->GetCurrentContext();

    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    if (!info[0]->IsNumber() && !info[0]->IsString()) {
        LOGE("arg is not Number or String.");
        return;
    }

    if (info.Length() == 2 && info[1]->IsObject()) {
        JsAnimate(info);
    }

    JSViewAbstract* view = static_cast<JSViewAbstract*>(info.This()->GetAlignedPointerFromInternalField(0));
    if (!view) {
        LOGE("view is null!");
        return;
    }

    Dimension value;
    if (info[0]->IsNumber()) {
        value = Dimension(info[0]->NumberValue(context).ToChecked(), DimensionUnit::VP);
    } else {
        value = StringUtils::StringToDimension(V8Utils::ScopedString(info[0]).get(), true);
    }
    view->SetHeight(value);
    info.GetReturnValue().Set(info.This());
}

void JSViewAbstract::JsBorderColor(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    auto isolate = info.GetIsolate();
    v8::HandleScope scp(isolate);
    auto context = isolate->GetCurrentContext();

    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    if (!info[0]->IsString() && !info[0]->IsNumber()) {
        LOGE("arg is not a string or number.");
        return;
    }
    JSViewAbstract* view = static_cast<JSViewAbstract*>(info.This()->GetAlignedPointerFromInternalField(0));
    if (!view) {
        LOGE("view is null!");
        return;
    }
    Color color;
    if (info[0]->IsString()) {
        color = Color::FromString(V8Utils::ScopedString(info[0]).get());
    } else if (info[0]->IsNumber()) {
        color = Color(ColorAlphaAdapt((uint32_t)info[0]->NumberValue(context).ToChecked()));
    }
    view->SetBorderColor(color);
    info.GetReturnValue().Set(info.This());
}

void JSViewAbstract::JsBackgroundColor(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    auto isolate = info.GetIsolate();
    v8::HandleScope scp(isolate);
    auto context = isolate->GetCurrentContext();

    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    if (!info[0]->IsString() && !info[0]->IsNumber()) {
        LOGE("arg is not a string or number.");
        return;
    }

    if (info.Length() == 2 && info[1]->IsObject()) {
        JsAnimate(info);
    }

    JSViewAbstract* view = static_cast<JSViewAbstract*>(info.This()->GetAlignedPointerFromInternalField(0));
    if (!view) {
        LOGE("view is null!");
        return;
    }

    Color color;
    if (info[0]->IsString()) {
        color = Color::FromString(V8Utils::ScopedString(info[0]).get());
    } else if (info[0]->IsNumber()) {
        color = Color(ColorAlphaAdapt((uint32_t)info[0]->NumberValue(context).ToChecked()));
    }
    view->SetBackgroundColor(color);
    info.GetReturnValue().Set(info.This());
}

void JSViewAbstract::JsPadding(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ParseMarginOrPadding(info, false);
}

void JSViewAbstract::JsMargin(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ParseMarginOrPadding(info, true);
}
void JSViewAbstract::ParseMarginOrPadding(const v8::FunctionCallbackInfo<v8::Value>& info, bool isMargin)
{
    auto isolate = info.GetIsolate();
    v8::HandleScope scp(isolate);
    auto context = isolate->GetCurrentContext();
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }
    if (!info[0]->IsString() && !info[0]->IsNumber() && !info[0]->IsObject()) {
        LOGE("arg is not a string, number or object.");
        return;
    }
    JSViewAbstract* view = static_cast<JSViewAbstract*>(info.This()->GetAlignedPointerFromInternalField(0));
    if (!view) {
        LOGE("view is null!");
        return;
    }
    if (info[0]->IsObject()) {
        auto argsPtrItem = JsonUtil::ParseJsonString(
            V8Utils::ScopedString(v8::JSON::Stringify(context, info[0]).ToLocalChecked()).get());
        if (!argsPtrItem) {
            LOGE("Js Parse object failed. argsPtr is null. %s", V8Utils::ScopedString(info[0]).get());
            info.GetReturnValue().Set(info.This());
            return;
        }
        if (argsPtrItem->IsNull()) {
            info.GetReturnValue().Set(info.This());
            return;
        }
        Dimension topDimen = view->GetDimension("top", argsPtrItem);
        Dimension bottomDimen = view->GetDimension("bottom", argsPtrItem);
        Dimension leftDimen = view->GetDimension("left", argsPtrItem);
        Dimension rightDimen = view->GetDimension("right", argsPtrItem);
        if (isMargin) {
            view->SetMargins(topDimen, bottomDimen, leftDimen, rightDimen);
        } else {
            view->SetPaddings(topDimen, bottomDimen, leftDimen, rightDimen);
        }
    } else if (info[0]->IsString()) {
        Dimension length = StringUtils::StringToDimension(V8Utils::ScopedString(info[0]).get(), true);
        if (isMargin) {
            view->SetMargin(length);
        } else {
            view->SetPadding(length);
        }
    } else if (info[0]->IsNumber()) {
        Dimension length = Dimension(info[0]->NumberValue(context).ToChecked(), DimensionUnit::VP);
        if (isMargin) {
            view->SetMargin(length);
        } else {
            view->SetPadding(length);
        }
    }
    info.GetReturnValue().Set(info.This());
}
void JSViewAbstract::JsBorder(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    auto isolate = info.GetIsolate();
    v8::HandleScope scp(isolate);
    auto context = isolate->GetCurrentContext();
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }
    if (!info[0]->IsObject()) {
        LOGE("arg is not a object.");
        return;
    }
    JSViewAbstract* view = static_cast<JSViewAbstract*>(info.This()->GetAlignedPointerFromInternalField(0));
    if (!view) {
        LOGE("view is null!");
        return;
    }
    auto argsPtrItem =
        JsonUtil::ParseJsonString(V8Utils::ScopedString(v8::JSON::Stringify(context, info[0]).ToLocalChecked()).get());
    if (!argsPtrItem || argsPtrItem->IsNull()) {
        LOGE("Js Parse object failed. argsPtr is null. %s", V8Utils::ScopedString(info[0]).get());
        info.GetReturnValue().Set(info.This());
        return;
    }
    Dimension width = view->GetDimension("width", argsPtrItem);
    Dimension radius = view->GetDimension("radius", argsPtrItem);
    auto borderStyle = argsPtrItem->GetInt("style", static_cast<int32_t>(BorderStyle::SOLID));
    std::unique_ptr<JsonValue> colorValue = argsPtrItem->GetValue("color");
    Color color;
    if (colorValue->IsString()) {
        color = Color::FromString(colorValue->GetString());
    } else if (colorValue->IsNumber()) {
        color = Color(ColorAlphaAdapt(colorValue->GetUInt()));
    }
    LOGD("JsBorder width = %lf unit = %d, radius = %lf unit = %d, borderStyle = %d, color = %x", width.Value(),
        width.Unit(), radius.Value(), radius.Unit(), borderStyle, color.GetValue());
    view->SetBorderColor(color);
    view->SetBorderStyle(borderStyle);
    view->SetBorderWidth(width);
    view->SetBorderRadius(radius);
    info.GetReturnValue().Set(info.This());
}

void JSViewAbstract::JsBorderWidth(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    JSViewAbstract* view = static_cast<JSViewAbstract*>(info.This()->GetAlignedPointerFromInternalField(0));
    if (!view) {
        LOGE("view is null!");
        return;
    }
    view->SetBorderWidth(ParseDimension(info));
    info.GetReturnValue().Set(info.This());
}

void JSViewAbstract::JsBorderRadius(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    JSViewAbstract* view = static_cast<JSViewAbstract*>(info.This()->GetAlignedPointerFromInternalField(0));
    if (!view) {
        LOGE("view is null!");
        return;
    }
    view->SetBorderRadius(ParseDimension(info));
    info.GetReturnValue().Set(info.This());
}

Dimension JSViewAbstract::ParseDimension(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    auto isolate = info.GetIsolate();
    v8::HandleScope scp(isolate);
    auto context = isolate->GetCurrentContext();
    Dimension DEFAULT_DIMENSION = Dimension(0.0, DimensionUnit::VP);
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return DEFAULT_DIMENSION;
    }
    if (!info[0]->IsNumber() && !info[0]->IsString()) {
        LOGE("arg is not Number or String.");
        return DEFAULT_DIMENSION;
    }
    JSViewAbstract* view = static_cast<JSViewAbstract*>(info.This()->GetAlignedPointerFromInternalField(0));
    if (!view) {
        LOGE("view is null!");
        return DEFAULT_DIMENSION;
    }
    Dimension value;
    if (info[0]->IsNumber()) {
        value = Dimension(info[0]->NumberValue(context).ToChecked(), DimensionUnit::VP);
    } else {
        value = StringUtils::StringToDimension(V8Utils::ScopedString(info[0]).get(), true);
    }
    return value;
}
#endif

void JSViewAbstract::JSBind()
{
    MethodOptions opt = MethodOptions::RETURN_SELF;
    JSClass<JSViewAbstract>::Declare("JSViewAbstract");
    JSClass<JSViewAbstract>::Method("borderStyle", &JSViewAbstract::SetBorderStyle, opt);
    JSClass<JSViewAbstract>::Method("marginTop", &JSViewAbstract::SetMarginTop, opt);
    JSClass<JSViewAbstract>::Method("marginBottom", &JSViewAbstract::SetMarginBottom, opt);
    JSClass<JSViewAbstract>::Method("marginLeft", &JSViewAbstract::SetMarginLeft, opt);
    JSClass<JSViewAbstract>::Method("marginRight", &JSViewAbstract::SetMarginRight, opt);
    JSClass<JSViewAbstract>::Method("markNeedUpdate", &JSViewAbstract::MarkNeedUpdate);
    JSClass<JSViewAbstract>::Method("setUniqueKey", &JSViewAbstract::setUniqueKey, opt);
    JSClass<JSViewAbstract>::Method("markStatic", &JSViewAbstract::MarkStatic, opt);
    JSClass<JSViewAbstract>::Method("getViewId", &JSViewAbstract::getViewId, opt);
    JSClass<JSViewAbstract>::Method("paddingTop", &JSViewAbstract::SetPaddingTop, opt);
    JSClass<JSViewAbstract>::Method("paddingBottom", &JSViewAbstract::SetPaddingBottom, opt);
    JSClass<JSViewAbstract>::Method("paddingLeft", &JSViewAbstract::SetPaddingLeft, opt);
    JSClass<JSViewAbstract>::Method("paddingRight", &JSViewAbstract::SetPaddingRight, opt);

    JSClass<JSViewAbstract>::CustomMethod("width", JsWidth);
    JSClass<JSViewAbstract>::CustomMethod("height", JsHeight);
    JSClass<JSViewAbstract>::CustomMethod("backgroundColor", JsBackgroundColor);
    JSClass<JSViewAbstract>::CustomMethod("borderColor", JsBorderColor);
    JSClass<JSViewAbstract>::CustomMethod("animate", JsAnimate);
    JSClass<JSViewAbstract>::CustomMethod("scale", JsScale);
    JSClass<JSViewAbstract>::CustomMethod("opacity", JsOpacity);
    JSClass<JSViewAbstract>::CustomMethod("rotate", JsRotate);
    JSClass<JSViewAbstract>::CustomMethod("translate", JsTranslate);
    JSClass<JSViewAbstract>::CustomMethod("translateX", JsTranslateX);
    JSClass<JSViewAbstract>::CustomMethod("translateY", JsTranslateY);
    JSClass<JSViewAbstract>::CustomMethod("padding", &JSViewAbstract::JsPadding);
    JSClass<JSViewAbstract>::CustomMethod("margin", &JSViewAbstract::JsMargin);
    JSClass<JSViewAbstract>::CustomMethod("border", JsBorder);
    JSClass<JSViewAbstract>::CustomMethod("borderWidth", JsBorderWidth);
    JSClass<JSViewAbstract>::CustomMethod("borderRadius", JsBorderRadius);
}

Dimension JSViewAbstract::ViewWidth() const
{
    if (!tweenOption_.IsValid()) {
        return Dimension();
    }

    auto& propertyFloatMap = const_cast<TweenOption&>(tweenOption_).GetFloatPropertyAnimation();
    auto i = propertyFloatMap.find(PropertyAnimatableType::PROPERTY_WIDTH);
    if (i != propertyFloatMap.end()) {
        return Dimension(i->second->GetEndValue(), DimensionUnit::PX);
    }

    return Dimension();
}

Dimension JSViewAbstract::ViewHeight() const
{
    if (!tweenOption_.IsValid()) {
        return Dimension();
    }

    auto& propertyFloatMap = const_cast<TweenOption&>(tweenOption_).GetFloatPropertyAnimation();
    auto i = propertyFloatMap.find(PropertyAnimatableType::PROPERTY_HEIGHT);
    if (i != propertyFloatMap.end()) {
        return Dimension(i->second->GetEndValue(), DimensionUnit::PX);
    }

    return Dimension();
}

const Dimension& JSViewAbstract::ViewRadius() const
{
    // TODO: radii specified per corner and x/y bases, thus we assume they are all the same.
    return GetBorder().TopLeftRadius().GetX();
}

RefPtr<BoxComponent> JSViewAbstract::GetOrMakeBoxComponent() const
{
    if (!boxComponent_) {
        boxComponent_ = AceType::MakeRefPtr<BoxComponent>();
    }

    return boxComponent_;
}

RefPtr<Decoration> JSViewAbstract::GetBackDecoration() const
{
    auto box = GetOrMakeBoxComponent();

    auto decoration = box->GetBackDecoration();
    if (!decoration) {
        decoration = MakeRefPtr<Decoration>();
        box->SetBackDecoration(decoration);
    }

    return decoration;
}

const Border& JSViewAbstract::GetBorder() const
{
    return GetBackDecoration()->GetBorder();
}

BorderEdge JSViewAbstract::GetLeftBorderEdge()
{
    return GetBorder().Left();
}

BorderEdge JSViewAbstract::GetTopBorderEdge()
{
    return GetBorder().Top();
}

BorderEdge JSViewAbstract::GetRightBorderEdge()
{
    return GetBorder().Right();
}

BorderEdge JSViewAbstract::GetBottomBorderEdge()
{
    return GetBorder().Bottom();
}

void JSViewAbstract::SetBorderEdge(const BorderEdge& edge)
{
    Border border = GetBorder();
    border.SetBorderEdge(edge);
    SetBorder(border);
}

void JSViewAbstract::SetLeftBorderEdge(const BorderEdge& edge)
{
    Border border = GetBorder();
    border.SetLeftEdge(edge);
    SetBorder(border);
}

void JSViewAbstract::SetTopBorderEdge(const BorderEdge& edge)
{
    Border border = GetBorder();
    border.SetTopEdge(edge);
    SetBorder(border);
}

void JSViewAbstract::SetRightBorderEdge(const BorderEdge& edge)
{
    Border border = GetBorder();
    border.SetRightEdge(edge);
    SetBorder(border);
}

void JSViewAbstract::SetBottomBorderEdge(const BorderEdge& edge)
{
    Border border = GetBorder();
    border.SetBottomEdge(edge);
    SetBorder(border);
}

void JSViewAbstract::SetBorder(const Border& border)
{
    GetBackDecoration()->SetBorder(border);
}

void JSViewAbstract::SetBorderRadius(const Dimension& value)
{
    Border border = GetBorder();
    border.SetBorderRadius(Radius(value));
    SetBorder(border);
}

void JSViewAbstract::SetBorderStyle(int32_t style)
{
    BorderStyle borderStyle = BorderStyle::SOLID;

    if (static_cast<int32_t>(BorderStyle::SOLID) == style) {
        borderStyle = BorderStyle::SOLID;
    } else if (static_cast<int32_t>(BorderStyle::DASHED) == style) {
        borderStyle = BorderStyle::DASHED;
    } else if (static_cast<int32_t>(BorderStyle::DOTTED) == style) {
        borderStyle = BorderStyle::DOTTED;
    } else {
        borderStyle = BorderStyle::NONE;
    }

    BorderEdge edge = GetLeftBorderEdge();
    edge.SetStyle(borderStyle);
    SetBorderEdge(edge);
}

void JSViewAbstract::SetBorderColor(const Color& color)
{
    SetLeftBorderColor(color);
    SetTopBorderColor(color);
    SetRightBorderColor(color);
    SetBottomBorderColor(color);
}

void JSViewAbstract::SetLeftBorderColor(const Color& color)
{
    BorderEdge edge = GetLeftBorderEdge();
    edge.SetColor(color);
    SetLeftBorderEdge(edge);
}

void JSViewAbstract::SetTopBorderColor(const Color& color)
{
    BorderEdge edge = GetTopBorderEdge();
    edge.SetColor(color);
    SetTopBorderEdge(edge);
}

void JSViewAbstract::SetRightBorderColor(const Color& color)
{
    BorderEdge edge = GetRightBorderEdge();
    edge.SetColor(color);
    SetRightBorderEdge(edge);
}

void JSViewAbstract::SetBottomBorderColor(const Color& color)
{
    BorderEdge edge = GetBottomBorderEdge();
    edge.SetColor(color);
    SetBottomBorderEdge(edge);
}

void JSViewAbstract::SetBorderWidth(const Dimension& value)
{
    SetLeftBorderWidth(value);
    SetTopBorderWidth(value);
    SetRightBorderWidth(value);
    SetBottomBorderWidth(value);
}

void JSViewAbstract::SetLeftBorderWidth(const Dimension& value)
{
    BorderEdge edge = GetLeftBorderEdge();
    edge.SetWidth(Dimension(value));
    SetLeftBorderEdge(edge);
}

void JSViewAbstract::SetTopBorderWidth(const Dimension& value)
{
    BorderEdge edge = GetTopBorderEdge();
    edge.SetWidth(Dimension(value));
    SetTopBorderEdge(edge);
}

void JSViewAbstract::SetRightBorderWidth(const Dimension& value)
{
    BorderEdge edge = GetRightBorderEdge();
    edge.SetWidth(Dimension(value));
    SetRightBorderEdge(edge);
}

void JSViewAbstract::SetBottomBorderWidth(const Dimension& value)
{
    BorderEdge edge = GetBottomBorderEdge();
    edge.SetWidth(Dimension(value));
    SetBottomBorderEdge(edge);
}

void JSViewAbstract::SetMarginTop(const std::string& value)
{
    auto box = GetOrMakeBoxComponent();
    Edge margin = box->GetMargin();
    margin.SetTop(StringUtils::StringToDimension(value, true));
    box->SetMargin(margin);
}

void JSViewAbstract::SetMarginBottom(const std::string& value)
{
    auto box = GetOrMakeBoxComponent();
    Edge margin = box->GetMargin();
    margin.SetBottom(StringUtils::StringToDimension(value, true));
    box->SetMargin(margin);
}

void JSViewAbstract::SetMarginLeft(const std::string& value)
{
    auto box = GetOrMakeBoxComponent();
    Edge margin = box->GetMargin();
    margin.SetLeft(StringUtils::StringToDimension(value, true));
    box->SetMargin(margin);
}

void JSViewAbstract::SetMarginRight(const std::string& value)
{
    auto box = GetOrMakeBoxComponent();
    Edge margin = box->GetMargin();
    margin.SetRight(StringUtils::StringToDimension(value, true));
    box->SetMargin(margin);
}

void JSViewAbstract::SetMargin(const std::string& value)
{
    Dimension dimen = StringUtils::StringToDimension(value, true);
    SetMargins(dimen, dimen, dimen, dimen);
}

void JSViewAbstract::SetMargins(
    const Dimension& top, const Dimension& bottom, const Dimension& left, const Dimension& right)
{
    auto box = GetOrMakeBoxComponent();
    Edge margin(left, top, right, bottom);
    box->SetMargin(margin);
}

void JSViewAbstract::SetBackgroundColor(const Color& color)
{
    userDefColor_ = true;
    backGroundColor_ = color;
    ProcessBackgroundColor();
}

void JSViewAbstract::ProcessBackgroundColor()
{
    if (!boxComponent_) {
        boxComponent_ = AceType::MakeRefPtr<BoxComponent>();
    }
    auto colorAnimation = AceType::MakeRefPtr<KeyframeAnimation<Color>>();
    auto keyframe1 = AceType::MakeRefPtr<Keyframe<Color>>(1.0f, backGroundColor_);
    colorAnimation->AddKeyframe(keyframe1);
    colorAnimation->SetEvaluator(AceType::MakeRefPtr<ColorEvaluator>());
    colorAnimation->SetDeclarativeAnimation(true);
    tweenOption_.SetColorAnimation(colorAnimation);
}

void JSViewAbstract::SetWidth(const Dimension& width)
{
    isDefWidth_ = true;
    if (!boxComponent_) {
        boxComponent_ = AceType::MakeRefPtr<BoxComponent>();
    }
    auto wCurve = AceType::MakeRefPtr<CurveAnimation<float>>(
        -1.0, width.ConvertToPx(SystemProperties::GetResolution()), Curves::LINEAR);
    wCurve->SetDeclarativeAnimation(true);
    tweenOption_.SetPropertyAnimationFloat(PropertyAnimatableType::PROPERTY_WIDTH, wCurve);
}

void JSViewAbstract::SetHeight(const Dimension& height)
{
    isDefHeight_ = true;
    if (!boxComponent_) {
        boxComponent_ = AceType::MakeRefPtr<BoxComponent>();
    }
    auto hCurve = AceType::MakeRefPtr<CurveAnimation<float>>(
        -1.0, height.ConvertToPx(SystemProperties::GetResolution()), Curves::LINEAR);
    hCurve->SetDeclarativeAnimation(true);
    tweenOption_.SetPropertyAnimationFloat(PropertyAnimatableType::PROPERTY_HEIGHT, hCurve);
}

void JSViewAbstract::SetPaddingTop(const std::string& value)
{
    auto box = GetOrMakeBoxComponent();
    Edge padding = box->GetPadding();
    padding.SetTop(StringUtils::StringToDimension(value, true));
    box->SetPadding(padding);
}

void JSViewAbstract::SetPaddingBottom(const std::string& value)
{
    auto box = GetOrMakeBoxComponent();
    Edge padding = box->GetPadding();
    padding.SetBottom(StringUtils::StringToDimension(value, true));
    box->SetPadding(padding);
}

void JSViewAbstract::SetPaddingLeft(const std::string& value)
{
    auto box = GetOrMakeBoxComponent();
    Edge padding = box->GetPadding();
    padding.SetLeft(StringUtils::StringToDimension(value, true));
    box->SetPadding(padding);
}

void JSViewAbstract::SetPaddingRight(const std::string& value)
{
    auto box = GetOrMakeBoxComponent();
    Edge padding = box->GetPadding();
    padding.SetRight(StringUtils::StringToDimension(value, true));
    box->SetPadding(padding);
}

void JSViewAbstract::SetPadding(const Dimension& value)
{
    SetPaddings(value, value, value, value);
}

void JSViewAbstract::SetPaddings(
    const Dimension& top, const Dimension& bottom, const Dimension& left, const Dimension& right)
{
    auto box = GetOrMakeBoxComponent();
    Edge padding(left, top, right, bottom);
    box->SetPadding(padding);
}

void JSViewAbstract::SetMargin(const Dimension& value)
{
    SetMargins(value, value, value, value);
}

Dimension JSViewAbstract::GetDimension(const std::string& key, const std::unique_ptr<JsonValue>& jsonValue)
{
    Dimension dimen;
    auto value = jsonValue->GetValue(key);
    if (value && value->IsString()) {
        dimen = StringUtils::StringToDimension(value->GetString(), true);
    } else if (value && value->IsNumber()) {
        dimen = Dimension(value->GetDouble(), DimensionUnit::VP);
    } else {
        LOGE("Invalid value type");
        dimen = Dimension(0.0, DimensionUnit::VP);
    }
    return dimen;
}

} // namespace OHOS::Ace::Framework
