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

#include "frameworks/bridge/js_frontend/engine/common/base_animation_bridge.h"

#include "base/json/json_util.h"
#include "base/utils/linear_map.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "core/animation/keyframe_animation.h"
#include "frameworks/bridge/common/dom/dom_type.h"
#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::Framework {
namespace {

constexpr double PI = 3.14;
constexpr double RAD_CONVERT = 180.0;
constexpr int32_t MIN_SIZE = 2;
constexpr Dimension HALF = 0.5_pct;
constexpr Dimension FULL = 1.0_pct;
constexpr Dimension ZERO = 0.0_pct;
const char ROTATE_RAD[] = "rad";

RefPtr<KeyframeAnimation<float>> CreateFloatAnimation(const std::string& type, const RefPtr<Curve>& curve,
    const std::vector<std::unordered_map<std::string, std::string>>& animationFrames)
{
    RefPtr<KeyframeAnimation<float>> floatAnimation;
    for (const auto& frame : animationFrames) {
        std::string floatString;
        std::string offsetString;
        auto floatValue = frame.find(type);
        auto offset = frame.find(DOM_ANIMATION_OFFSET);
        if (floatValue != frame.end()) {
            floatString = floatValue->second;
        }
        if (offset != frame.end()) {
            offsetString = offset->second;
        }
        if (!floatString.empty() && !offsetString.empty()) {
            if (!floatAnimation) {
                floatAnimation = AceType::MakeRefPtr<KeyframeAnimation<float>>();
            }
            double keyValue = 0.0;
            if (floatString.find(ROTATE_RAD) != std::string::npos) {
                keyValue = RAD_CONVERT * StringToDouble(floatString) / PI;
            } else {
                keyValue = StringToDouble(floatString);
            }

            auto keyframe = AceType::MakeRefPtr<Keyframe<float>>(StringToDouble(offsetString), keyValue);
            keyframe->SetCurve(curve);
            floatAnimation->AddKeyframe(keyframe);
        }
    }
    return floatAnimation;
}

RefPtr<KeyframeAnimation<BackgroundImagePosition>> CreateBackgroundPositionAnimation(
    const RefPtr<Curve>& curve, const std::vector<std::unordered_map<std::string, std::string>>& animationFrames)
{
    RefPtr<KeyframeAnimation<BackgroundImagePosition>> animation;
    for (const auto& frame : animationFrames) {
        std::string backgroundImageString;
        std::string offsetString;
        auto backgroundImage = frame.find(DOM_BACKGROUND_IMAGE_POSITION);
        auto offset = frame.find(DOM_ANIMATION_OFFSET);
        if (backgroundImage != frame.end()) {
            backgroundImageString = backgroundImage->second;
        }
        if (offset != frame.end()) {
            offsetString = offset->second;
        }
        if (!backgroundImageString.empty() && !offsetString.empty()) {
            BackgroundImagePosition backgroundImagePosition;
            if (!ParseBackgroundImagePosition(backgroundImageString, backgroundImagePosition)) {
                LOGW("parse frame failed.");
                continue;
            }
            if (!animation) {
                animation = AceType::MakeRefPtr<KeyframeAnimation<BackgroundImagePosition>>();
            }
            auto keyframe = AceType::MakeRefPtr<Keyframe<BackgroundImagePosition>>(
                StringToDouble(offsetString), backgroundImagePosition);
            keyframe->SetCurve(curve);
            animation->AddKeyframe(keyframe);
        }
    }
    return animation;
}

DimensionOffset ParseTranslateProperties(const std::string& type, const std::string& translateString)
{
    if (type == TRANSLATE) {
        std::vector<std::string> values;
        StringUtils::StringSpliter(translateString, ' ', values);
        if (values.empty() || values.size() > OFFSET_VALUE_NUMBER) {
            return DimensionOffset();
        } else if (values.size() == OFFSET_VALUE_NUMBER) {
            return DimensionOffset(StringToDimension(values.front()), StringToDimension(values.back()));
        } else {
            return DimensionOffset(StringToDimension(translateString), ZERO);
        }
    } else if (type == DOM_TRANSLATE_X) {
        return DimensionOffset(StringToDimension(translateString), ZERO);
    } else if (type == DOM_TRANSLATE_Y) {
        return DimensionOffset(ZERO, StringToDimension(translateString));
    }
    return DimensionOffset();
}

RefPtr<KeyframeAnimation<DimensionOffset>> CreateTranslateAnimation(const std::string& type, const RefPtr<Curve>& curve,
    const std::vector<std::unordered_map<std::string, std::string>>& animationFrames)
{
    RefPtr<KeyframeAnimation<DimensionOffset>> translateAnimation;
    for (const auto& frame : animationFrames) {
        std::string translateString;
        std::string offsetString;
        auto translate = frame.find(type);
        auto offset = frame.find(DOM_ANIMATION_OFFSET);
        if (translate != frame.end()) {
            translateString = translate->second;
        }
        if (offset != frame.end()) {
            offsetString = offset->second;
        }
        if (!translateString.empty() && !offsetString.empty()) {
            if (!translateAnimation) {
                translateAnimation = AceType::MakeRefPtr<KeyframeAnimation<DimensionOffset>>();
            }
            DimensionOffset keyValue = ParseTranslateProperties(type, translateString);
            auto keyframe = AceType::MakeRefPtr<Keyframe<DimensionOffset>>(StringToDouble(offsetString), keyValue);
            keyframe->SetCurve(curve);
            translateAnimation->AddKeyframe(keyframe);
        }
    }
    return translateAnimation;
}

RefPtr<KeyframeAnimation<Color>> CreateColorAnimation(
    const RefPtr<Curve>& curve, const std::vector<std::unordered_map<std::string, std::string>>& animationFrames)
{
    RefPtr<KeyframeAnimation<Color>> colorAnimation;
    for (const auto& frame : animationFrames) {
        std::string colorString;
        std::string offsetString;
        auto color = frame.find(DOM_ANIMATION_COLOR);
        auto offset = frame.find(DOM_ANIMATION_OFFSET);
        if (color != frame.end()) {
            colorString = color->second;
        }
        if (offset != frame.end()) {
            offsetString = offset->second;
        }
        if (!colorString.empty() && !offsetString.empty()) {
            if (!colorAnimation) {
                colorAnimation = AceType::MakeRefPtr<KeyframeAnimation<Color>>();
                colorAnimation->SetEvaluator(AceType::MakeRefPtr<ColorEvaluator>());
            }
            auto keyframe =
                AceType::MakeRefPtr<Keyframe<Color>>(StringToDouble(offsetString), Color::FromString(colorString));
            keyframe->SetCurve(curve);
            colorAnimation->AddKeyframe(keyframe);
        }
    }
    return colorAnimation;
}

void SetScaleAnimation(TweenOption& tweenOption, const RefPtr<Curve>& curve,
    const std::vector<std::unordered_map<std::string, std::string>>& animationFrames)
{
    RefPtr<KeyframeAnimation<float>> scaleXAnimation;
    RefPtr<KeyframeAnimation<float>> scaleYAnimation;
    bool sameScale = true;
    for (const auto& frame : animationFrames) {
        std::string scaleValue;
        std::string offsetString;
        auto floatValue = frame.find(SCALE);
        auto offset = frame.find(DOM_ANIMATION_OFFSET);
        if (floatValue != frame.end()) {
            scaleValue = floatValue->second;
        }
        if (offset != frame.end()) {
            offsetString = offset->second;
        }
        if (scaleValue.empty() || offsetString.empty()) {
            continue;
        }
        std::vector<std::string> values;
        StringUtils::StringSpliter(scaleValue, ' ', values);
        if (values.empty() || values.size() > OFFSET_VALUE_NUMBER) {
            continue;
        }

        if (!scaleXAnimation) {
            scaleXAnimation = AceType::MakeRefPtr<KeyframeAnimation<float>>();
            scaleYAnimation = AceType::MakeRefPtr<KeyframeAnimation<float>>();
        }

        double keyValueX = StringToDouble(values.front());
        double keyValueY = StringToDouble(values.back());
        if (!NearEqual(keyValueX, keyValueY)) {
            sameScale = false;
        }
        auto scaleXKeyframe = AceType::MakeRefPtr<Keyframe<float>>(StringToDouble(offsetString), keyValueX);
        scaleXKeyframe->SetCurve(curve);
        auto scaleYKeyframe = AceType::MakeRefPtr<Keyframe<float>>(StringToDouble(offsetString), keyValueY);
        scaleYKeyframe->SetCurve(curve);
        scaleXAnimation->AddKeyframe(scaleXKeyframe);
        scaleYAnimation->AddKeyframe(scaleYKeyframe);
    }
    if (scaleXAnimation) {
        if (sameScale) {
            tweenOption.SetTransformFloatAnimation(AnimationType::SCALE, scaleXAnimation);
        } else {
            tweenOption.SetTransformFloatAnimation(AnimationType::SCALE_X, scaleXAnimation);
            tweenOption.SetTransformFloatAnimation(AnimationType::SCALE_Y, scaleYAnimation);
        }
    }
}

void SetFramesFloatAnimation(TweenOption& tweenOption, const RefPtr<Curve>& curve,
    const std::vector<std::unordered_map<std::string, std::string>>& animationFrames)
{
    static const LinearMapNode<AnimationType> floatTransformAnimations[] = {
        { DOM_ROTATE, AnimationType::ROTATE_Z },
        { DOM_ROTATE_X, AnimationType::ROTATE_X },
        { DOM_ROTATE_Y, AnimationType::ROTATE_Y },
        { DOM_SCALE, AnimationType::SCALE },
        { DOM_SCALE_X, AnimationType::SCALE_X },
        { DOM_SCALE_Y, AnimationType::SCALE_Y },
    };
    for (size_t idx = 0; idx < ArraySize(floatTransformAnimations); ++idx) {
        if (strcmp(floatTransformAnimations[idx].key, SCALE) == 0) {
            SetScaleAnimation(tweenOption, curve, animationFrames);
        } else {
            auto transformAnimation = CreateFloatAnimation(floatTransformAnimations[idx].key, curve, animationFrames);
            if (transformAnimation) {
                tweenOption.SetTransformFloatAnimation(floatTransformAnimations[idx].value, transformAnimation);
            }
        }
    }
    static const char* floatAnimations[] = { DOM_ANIMATION_WIDTH, DOM_ANIMATION_HEIGHT, DOM_ANIMATION_OPACITY };
    for (size_t idx = 0; idx < ArraySize(floatAnimations); ++idx) {
        auto floatAnimation = CreateFloatAnimation(floatAnimations[idx], curve, animationFrames);
        if (!floatAnimation) {
            continue;
        }
        if (strcmp(floatAnimations[idx], DOM_ANIMATION_WIDTH) == 0) {
            tweenOption.SetPropertyAnimationFloat(PropertyAnimatableType::PROPERTY_WIDTH, floatAnimation);
        } else if (strcmp(floatAnimations[idx], DOM_ANIMATION_HEIGHT) == 0) {
            tweenOption.SetPropertyAnimationFloat(PropertyAnimatableType::PROPERTY_HEIGHT, floatAnimation);
        } else if (strcmp(floatAnimations[idx], DOM_ANIMATION_OPACITY) == 0) {
            tweenOption.SetOpacityAnimation(floatAnimation);
        }
    }
}

void SetFramesTranslateAnimation(TweenOption& tweenOption, const RefPtr<Curve>& curve,
    const std::vector<std::unordered_map<std::string, std::string>>& animationFrames)
{
    static const LinearMapNode<AnimationType> translateAnimations[] = {
        { DOM_TRANSLATE, AnimationType::TRANSLATE },
        { DOM_TRANSLATE_X, AnimationType::TRANSLATE_X },
        { DOM_TRANSLATE_Y, AnimationType::TRANSLATE_Y },
    };
    for (size_t idx = 0; idx < ArraySize(translateAnimations); ++idx) {
        auto translateAnimation = CreateTranslateAnimation(translateAnimations[idx].key, curve, animationFrames);
        if (translateAnimation) {
            tweenOption.SetTranslateAnimations(translateAnimations[idx].value, translateAnimation);
        }
    }
}

void JsParseAnimationTransformInternal(
    const std::unique_ptr<JsonValue>& argsPtrTransform, std::unordered_map<std::string, std::string>& animationFrames)
{
    static const char* transformValue[] = {
        DOM_SCALE,
        DOM_SCALE_X,
        DOM_SCALE_Y,
        DOM_TRANSLATE,
        DOM_TRANSLATE_X,
        DOM_TRANSLATE_Y,
        DOM_ROTATE,
        DOM_ROTATE_X,
        DOM_ROTATE_Y,
    };

    for (size_t idx = 0; idx < ArraySize(transformValue); ++idx) {
        auto argsPtrTransformValue = argsPtrTransform->GetValue(transformValue[idx]);
        if (argsPtrTransformValue) {
            animationFrames[transformValue[idx]] = argsPtrTransformValue->GetString();
        }
    }
}

void JsParseAnimationFramesInternal(
    const std::unique_ptr<JsonValue>& argsPtrAnimation, std::unordered_map<std::string, std::string>& animationFrames)
{
    static const char* framesValue[] = {
        DOM_TRANSFORM,
        DOM_ANIMATION_WIDTH,
        DOM_ANIMATION_HEIGHT,
        DOM_ANIMATION_COLOR,
        DOM_ANIMATION_OPACITY,
        DOM_TRANSFORM_ORIGIN,
        DOM_BACKGROUND_IMAGE_POSITION,
        DOM_ANIMATION_OFFSET,
    };

    for (size_t idx = 0; idx < ArraySize(framesValue); ++idx) {
        if (strcmp(framesValue[idx], TRANSFORM) == 0) {
            auto argsPtrTransform = argsPtrAnimation->GetValue(framesValue[idx]);
            if (argsPtrTransform) {
                JsParseAnimationTransformInternal(argsPtrTransform, animationFrames);
            }
        } else {
            auto value = argsPtrAnimation->GetValue(framesValue[idx]);
            if (value) {
                animationFrames[framesValue[idx]] = value->IsString() ? value->GetString() : value->ToString();
            }
        }
    }
}

} // namespace

std::vector<Dimension> BaseAnimationBridgeUtils::HandleTransformOrigin(
    const std::vector<std::unordered_map<std::string, std::string>>& animationFrames)
{
    std::string transformOrigin;
    if (animationFrames.size() >= MIN_SIZE) {
        auto iterFrom = animationFrames.front().find(DOM_TRANSFORM_ORIGIN);
        if (iterFrom != animationFrames.front().end()) {
            transformOrigin = iterFrom->second;
        }
        if (transformOrigin.empty()) {
            auto iterTo = animationFrames.back().find(DOM_TRANSFORM_ORIGIN);
            if (iterTo != animationFrames.back().end()) {
                transformOrigin = iterTo->second;
            }
        }
    }

    std::vector<Dimension> transformOriginValue;
    if (transformOrigin.empty()) {
        return transformOriginValue;
    }

    static const LinearMapNode<std::vector<Dimension>> transformOriginMap[] = {
        { DOM_TRANSFORM_ORIGIN_CENTER_BOTTOM, { HALF, FULL } },
        { DOM_TRANSFORM_ORIGIN_CENTER_CENTER, { HALF, HALF } },
        { DOM_TRANSFORM_ORIGIN_CENTER_TOP, { HALF, ZERO } },
        { DOM_TRANSFORM_ORIGIN_LEFT_BOTTOM, { ZERO, FULL } },
        { DOM_TRANSFORM_ORIGIN_LEFT_CENTER, { ZERO, HALF } },
        { DOM_TRANSFORM_ORIGIN_LEFT_TOP, { ZERO, ZERO } },
        { DOM_TRANSFORM_ORIGIN_RIGHT_BOTTOM, { FULL, FULL } },
        { DOM_TRANSFORM_ORIGIN_RIGHT_CENTER, { FULL, HALF } },
        { DOM_TRANSFORM_ORIGIN_RIGHT_TOP, { FULL, ZERO } },
    };

    int64_t idx = BinarySearchFindIndex(transformOriginMap, ArraySize(transformOriginMap), transformOrigin.c_str());
    if (idx < 0) {
        auto pos = transformOrigin.find(' ', 0);
        if (pos != std::string::npos) {
            transformOriginValue.emplace_back(StringToDimension(transformOrigin.substr(0, pos)));
            transformOriginValue.emplace_back(StringToDimension(transformOrigin.substr(pos + 1)));
        }
    } else {
        transformOriginValue = transformOriginMap[idx].value;
    }
    return transformOriginValue;
}

void BaseAnimationBridgeUtils::SetTweenComponentParams(const RefPtr<Curve>& curve,
    const std::vector<std::unordered_map<std::string, std::string>>& animationFrames,
    RefPtr<TweenComponent>& tweenComponent, TweenOption& tweenOption)
{
    SetFramesFloatAnimation(tweenOption, curve, animationFrames);
    SetFramesTranslateAnimation(tweenOption, curve, animationFrames);

    auto colorAnimation = CreateColorAnimation(curve, animationFrames);
    if (colorAnimation) {
        tweenOption.SetColorAnimation(colorAnimation);
    }

    auto backgroundPositionAnimation = CreateBackgroundPositionAnimation(curve, animationFrames);
    if (backgroundPositionAnimation) {
        tweenOption.SetBackgroundPositionAnimation(backgroundPositionAnimation);
    }
    tweenComponent->SetCustomTweenOption(tweenOption);
    tweenComponent->SetCustomTweenOperation(TweenOperation::NONE);
}

void BaseAnimationBridgeUtils::JsParseAnimationFrames(
    const std::string& content, std::vector<std::unordered_map<std::string, std::string>>& animationFrames)
{
    auto argsPtr = JsonUtil::ParseJsonString(content);
    if (!argsPtr) {
        return;
    }
    auto argsPtrItem = argsPtr->GetArrayItem(0);
    if (!argsPtrItem) {
        LOGE("Animation frames are null.");
        return;
    }

    // Parse the arguments to each item in the frame
    for (int32_t idx = 0; idx < argsPtrItem->GetArraySize(); ++idx) {
        auto argsPtrAnimation = argsPtrItem->GetArrayItem(idx);
        if (!argsPtrAnimation) {
            continue;
        }
        std::unordered_map<std::string, std::string> animationFrame;
        JsParseAnimationFramesInternal(argsPtrAnimation, animationFrame);
        if (idx == 0) {
            animationFrame[DOM_ANIMATION_OFFSET] = BaseAnimationBridgeUtils::ANIMATION_FROM;
        }
        if (idx == (argsPtrItem->GetArraySize() - 1)) {
            animationFrame[DOM_ANIMATION_OFFSET] = BaseAnimationBridgeUtils::ANIMATION_TO;
        }
        animationFrames.emplace_back(animationFrame);
    }
}

void BaseAnimationBridgeUtils::JsParseAnimationOptions(const std::string& content, int32_t& iterations,
    std::unordered_map<std::string, double>& animationDoubleOptions,
    std::unordered_map<std::string, std::string>& animationStringOptions)
{
    auto argsPtr = JsonUtil::ParseJsonString(content);
    if (!argsPtr) {
        LOGE("Js Parse AnimationOption failed. argsPtr is null.");
        return;
    }

    auto argsPtrItem = argsPtr->GetArrayItem(1);
    if (!argsPtrItem) {
        LOGE("Js Parse AnimationOption failed. argsPtrItem is null.");
        return;
    }

    auto argsPtrItemIterations = argsPtrItem->GetValue(DOM_ANIMATION_ITERATIONS);
    auto argsPtrItemDelay = argsPtrItem->GetValue(DOM_ANIMATION_DELAY_API);
    auto argsPtrItemDuration = argsPtrItem->GetValue(DOM_ANIMATION_DURATION_API);
    auto argsPtrItemEasing = argsPtrItem->GetValue(DOM_ANIMATION_EASING);
    auto argsPtrItemFill = argsPtrItem->GetValue(DOM_ANIMATION_FILL);

    if (argsPtrItemIterations) {
        if (argsPtrItemIterations->IsString()) {
            std::string iterationsString = argsPtrItemIterations->GetString();
            if (iterationsString == BaseAnimationBridgeUtils::ITERATIONS_INFINITY) {
                iterations = ANIMATION_REPEAT_INFINITE;
            } else {
                iterations = StringToInt(iterationsString);
            }
        } else if (argsPtrItemIterations->IsNumber()) {
            iterations = argsPtrItemIterations->GetInt();
        } else {
            iterations = 1;
        }
    }
    if (argsPtrItemDelay) {
        double delay = 0.0;
        if (argsPtrItemDelay->IsString()) {
            delay = StringToDouble(argsPtrItemDelay->GetString());
        } else {
            delay = argsPtrItemDelay->GetDouble();
        }
        animationDoubleOptions[DOM_ANIMATION_DELAY_API] = delay;
    }
    if (argsPtrItemDuration) {
        double duration = 0.0;
        if (argsPtrItemDuration->IsString()) {
            duration = StringToDouble(argsPtrItemDuration->GetString());
        } else {
            duration = argsPtrItemDuration->GetDouble();
        }
        animationDoubleOptions[DOM_ANIMATION_DURATION_API] = duration;
    }
    if (argsPtrItemEasing) {
        animationStringOptions[DOM_ANIMATION_EASING] = argsPtrItemEasing->GetString();
    }
    if (argsPtrItemFill) {
        animationStringOptions[DOM_ANIMATION_FILL] = argsPtrItemFill->GetString();
    }
}
} // namespace OHOS::Ace::Framework
