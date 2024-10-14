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

#include "core/animation/animation_util.h"

#include "bridge/common/utils/utils.h"

namespace OHOS::Ace {
namespace {
constexpr int PARAMS_NUM = 4;
constexpr int INITIAL_VELOCITY = 0;
constexpr int DAMPING = 1;
constexpr int STIFFNESS = 2;
constexpr int MASS = 3;
template<class T>
T ParseFunctionValue(const std::string& line, const std::string& key, std::function<T(const std::string&)> parser)
{
    std::vector<std::string> strs;
    StringUtils::SplitStr(line, " ", strs, true);
    for (const auto& str : strs) {
        if (str.empty()) {
            continue;
        }
        auto leftIndex = str.find('(');
        auto rightIndex = str.find(')');
        if (leftIndex == std::string::npos || rightIndex == std::string::npos) {
            continue;
        }
        if (leftIndex + 1 >= rightIndex) {
            continue;
        }
        if (str.substr(0, leftIndex) != key) {
            continue;
        }

        auto valueStr = str.substr(leftIndex + 1, rightIndex - leftIndex - 1);
        return parser(valueStr);
    }
    return T {};
}

std::string GetTransformTypeValue(const std::unique_ptr<JsonValue>& transformJson)
{
    if (transformJson->IsNull()) {
        LOGE("transformJson is null");
        return "";
    }
    std::string jsonValue = transformJson->GetString();
    if (jsonValue.empty()) {
        double jsonDouble = transformJson->GetDouble();
        return std::to_string(jsonDouble);
    }
    return jsonValue;
}

std::string GetTransformType(const std::unique_ptr<JsonValue>& transformJson)
{
    if (transformJson->IsNull()) {
        LOGE("transformJson is null");
        return "";
    }
    return transformJson->GetKey();
}

} // namespace

void AnimationUtil::ParseAnimationStyle(
    const std::vector<std::unordered_map<std::string, std::string>>& animationKeyframes,
    const RefPtr<Declaration>& declaration, const RefPtr<ThemeConstants> themeConstants)
{
    if (declaration) {
        isRightToLeft = declaration->IsRightToLeft();
    }
    themeConstants_ = themeConstants;

    Clear();

    for (const auto& animationNameKeyframe : animationKeyframes) {
        auto animationName = animationNameKeyframe.find(DOM_ANIMATION_NAME);
        if (animationName != animationNameKeyframe.end()) {
            animationName_ = animationName->second;
            if (declaration) {
                auto& animationStyle =
                    declaration->MaybeResetStyle<CommonAnimationStyle>(StyleTag::COMMON_ANIMATION_STYLE);
                if (animationStyle.IsValid()) {
                    animationStyle.animationOperation = AnimationOperation::PLAY;
                }
            }
            continue;
        }

        // time from keyframe; offset from js api
        auto pos = animationNameKeyframe.find(DOM_ANIMATION_NAME_TIME);
        if (pos == animationNameKeyframe.end()) {
            pos = animationNameKeyframe.find(DOM_ANIMATION_OFFSET);
        }
        if (pos == animationNameKeyframe.end()) {
            continue;
        }
        auto timeStr = pos->second;
        if (timeStr.empty()) {
            continue;
        }

        for (const auto& [keyStyle, value] : animationNameKeyframe) {
            if (keyStyle == DOM_ANIMATION_NAME_TIME || keyStyle == DOM_ANIMATION_OFFSET) {
                continue;
            }
            KeyframesAddKeyFrame(keyStyle, value, timeStr);
        }
    }
    if (!shadowKeyframes_.empty()) {
        for (auto&& [key, shadow] : shadowKeyframes_) {
            double time = StringUtils::StringToDouble(key) / 100.0;
            AddAnimatable(shadow, time, AnimatableType::PROPERTY_BOX_SHADOW);
        }
    }
}

void AnimationUtil::KeyframesAddKeyFrame(
    const std::string& keyStyle, const std::string& value, const std::string& timeStr)
{
    static const std::unordered_map<std::string,
        void (*)(const std::string&, const double&, const std::string&, AnimationUtil&)>
        keyFrameAddMap = {
            { DOM_BACKGROUND_COLOR,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    util.AddAnimatable(util.ParseColor(value), time, AnimatableType::PROPERTY_BG_COLOR);
                } },
            { DOM_BACKGROUND_IMAGE_SIZE,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    BackgroundImageSize backgroundImageSize;
                    if (!Framework::ParseBackgroundImageSize(value, backgroundImageSize)) {
                        LOGW("ParseBackgroundImageSize failed.");
                        return;
                    }
                    util.AddAnimatable(backgroundImageSize, time, AnimatableType::PROPERTY_BACKGROUND_SIZE);
                } },
            { DOM_BACKGROUND_IMAGE_POSITION,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    BackgroundImagePosition backgroundImagePosition;
                    if (!Framework::ParseBackgroundImagePosition(value, backgroundImagePosition)) {
                        LOGW("ParseBackgroundImagePosition failed.");
                        return;
                    }
                    util.AddAnimatable(backgroundImagePosition, time, AnimatableType::PROPERTY_BACKGROUND_POSITION);
                } },
            { DOM_WIDTH,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    LOGE("DOM_WIDTH:%{public}s time:%{public}lf", value.c_str(), time);
                    util.AddAnimatable(util.ParseDimension(value), time, AnimatableType::PROPERTY_WIDTH);
                } },
            { DOM_HEIGHT,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    util.AddAnimatable(util.ParseDimension(value), time, AnimatableType::PROPERTY_HEIGHT);
                } },
            { DOM_OPACITY,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    util.AddAnimatable<float>(util.ParseDouble(value), time, AnimatableType::PROPERTY_OPACITY);
                } },
            // margin
            { DOM_MARGIN_LEFT,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    util.AddAnimatable(
                        util.ParseDimension(value), time, AnimatableType::PROPERTY_MARGIN_LEFT);
                } },
            { DOM_MARGIN_RIGHT,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    util.AddAnimatable(
                        util.ParseDimension(value), time, AnimatableType::PROPERTY_MARGIN_RIGHT);
                } },
            { DOM_MARGIN_TOP,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    util.AddAnimatable(
                        util.ParseDimension(value), time, AnimatableType::PROPERTY_MARGIN_TOP);
                } },
            { DOM_MARGIN_BOTTOM,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    util.AddAnimatable(
                        util.ParseDimension(value), time, AnimatableType::PROPERTY_MARGIN_BOTTOM);
                } },
            { DOM_MARGIN_START,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    if (util.isRightToLeft) {
                        util.AddAnimatable(
                            util.ParseDimension(value), time, AnimatableType::PROPERTY_MARGIN_RIGHT);
                    } else {
                        util.AddAnimatable(
                            util.ParseDimension(value), time, AnimatableType::PROPERTY_MARGIN_LEFT);
                    }
                } },
            { DOM_MARGIN_END,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    if (util.isRightToLeft) {
                        util.AddAnimatable(
                            util.ParseDimension(value), time, AnimatableType::PROPERTY_MARGIN_LEFT);
                    } else {
                        util.AddAnimatable(
                            util.ParseDimension(value), time, AnimatableType::PROPERTY_MARGIN_RIGHT);
                    }
                } },
            { DOM_MARGIN,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    auto margin = util.ParseDimension(value);
                    util.AddAnimatable(margin, time, AnimatableType::PROPERTY_MARGIN_LEFT);
                    util.AddAnimatable(margin, time, AnimatableType::PROPERTY_MARGIN_TOP);
                    util.AddAnimatable(margin, time, AnimatableType::PROPERTY_MARGIN_RIGHT);
                    util.AddAnimatable(margin, time, AnimatableType::PROPERTY_MARGIN_BOTTOM);
                } },
            // padding
            { DOM_PADDING_LEFT,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    util.AddAnimatable(
                        util.ParseDimension(value), time, AnimatableType::PROPERTY_PADDING_LEFT);
                } },
            { DOM_PADDING_RIGHT,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    util.AddAnimatable(
                        util.ParseDimension(value), time, AnimatableType::PROPERTY_PADDING_RIGHT);
                } },
            { DOM_PADDING_TOP,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    util.AddAnimatable(
                        util.ParseDimension(value), time, AnimatableType::PROPERTY_PADDING_TOP);
                } },
            { DOM_PADDING_BOTTOM,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    util.AddAnimatable(
                        util.ParseDimension(value), time, AnimatableType::PROPERTY_PADDING_BOTTOM);
                } },
            { DOM_PADDING_START,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    auto padding = util.ParseDimension(value);
                    if (util.isRightToLeft) {
                        util.AddAnimatable(padding, time, AnimatableType::PROPERTY_PADDING_RIGHT);
                    } else {
                        util.AddAnimatable(padding, time, AnimatableType::PROPERTY_PADDING_LEFT);
                    }
                } },
            { DOM_PADDING_END,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    auto padding = util.ParseDimension(value);
                    if (util.isRightToLeft) {
                        util.AddAnimatable(padding, time, AnimatableType::PROPERTY_PADDING_LEFT);
                    } else {
                        util.AddAnimatable(padding, time, AnimatableType::PROPERTY_PADDING_RIGHT);
                    }
                } },
            { DOM_PADDING,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    auto padding = util.ParseDimension(value);
                    util.AddAnimatable(padding, time, AnimatableType::PROPERTY_PADDING_LEFT);
                    util.AddAnimatable(padding, time, AnimatableType::PROPERTY_PADDING_TOP);
                    util.AddAnimatable(padding, time, AnimatableType::PROPERTY_PADDING_RIGHT);
                    util.AddAnimatable(padding, time, AnimatableType::PROPERTY_PADDING_BOTTOM);
                } },
            // border
            { DOM_BORDER_LEFT_WIDTH,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    util.AddAnimatable<float>(
                        util.ParseDouble(value), time, AnimatableType::PROPERTY_BORDER_LEFT_WIDTH);
                } },
            { DOM_BORDER_RIGHT_WIDTH,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    util.AddAnimatable<float>(
                        util.ParseDouble(value), time, AnimatableType::PROPERTY_BORDER_RIGHT_WIDTH);
                } },
            { DOM_BORDER_TOP_WIDTH,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    util.AddAnimatable<float>(
                        util.ParseDouble(value), time, AnimatableType::PROPERTY_BORDER_TOP_WIDTH);
                } },
            { DOM_BORDER_BOTTOM_WIDTH,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    util.AddAnimatable<float>(
                        util.ParseDouble(value), time, AnimatableType::PROPERTY_BORDER_BOTTOM_WIDTH);
                } },
            { DOM_BORDER_WIDTH,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    auto borderWidth = util.ParseDouble(value);
                    util.AddAnimatable<float>(borderWidth, time, AnimatableType::PROPERTY_BORDER_LEFT_WIDTH);
                    util.AddAnimatable<float>(borderWidth, time, AnimatableType::PROPERTY_BORDER_RIGHT_WIDTH);
                    util.AddAnimatable<float>(borderWidth, time, AnimatableType::PROPERTY_BORDER_TOP_WIDTH);
                    util.AddAnimatable<float>(borderWidth, time, AnimatableType::PROPERTY_BORDER_BOTTOM_WIDTH);
                } },
            { DOM_BORDER_RADIUS,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    auto radius = util.ParseDouble(value);
                    util.AddAnimatable<float>(radius, time, AnimatableType::PROPERTY_BORDER_TOP_LEFT_RADIUS);
                    util.AddAnimatable<float>(radius, time, AnimatableType::PROPERTY_BORDER_TOP_RIGHT_RADIUS);
                    util.AddAnimatable<float>(radius, time, AnimatableType::PROPERTY_BORDER_BOTTOM_LEFT_RADIUS);
                    util.AddAnimatable<float>(radius, time, AnimatableType::PROPERTY_BORDER_BOTTOM_RIGHT_RADIUS);
                } },
            { DOM_BORDER_TOP_LEFT_RADIUS,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    auto radius = util.ParseDouble(value);
                    util.AddAnimatable<float>(radius, time, AnimatableType::PROPERTY_BORDER_TOP_LEFT_RADIUS);
                } },
            { DOM_BORDER_TOP_RIGHT_RADIUS,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    auto radius = util.ParseDouble(value);
                    util.AddAnimatable<float>(radius, time, AnimatableType::PROPERTY_BORDER_TOP_RIGHT_RADIUS);
                } },
            { DOM_BORDER_BOTTOM_LEFT_RADIUS,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    auto radius = util.ParseDouble(value);
                    util.AddAnimatable<float>(radius, time, AnimatableType::PROPERTY_BORDER_BOTTOM_LEFT_RADIUS);
                } },
            { DOM_BORDER_BOTTOM_RIGHT_RADIUS,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    auto radius = util.ParseDouble(value);
                    util.AddAnimatable<float>(radius, time, AnimatableType::PROPERTY_BORDER_BOTTOM_RIGHT_RADIUS);
                } },
            { DOM_BORDER_LEFT_COLOR,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    auto color = util.ParseColor(value);
                    util.AddAnimatable<Color>(color, time, AnimatableType::PROPERTY_BORDER_LEFT_COLOR);
                } },
            { DOM_BORDER_RIGHT_COLOR,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    auto color = util.ParseColor(value);
                    util.AddAnimatable<Color>(color, time, AnimatableType::PROPERTY_BORDER_RIGHT_COLOR);
                } },
            { DOM_BORDER_TOP_COLOR,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    auto color = util.ParseColor(value);
                    util.AddAnimatable<Color>(color, time, AnimatableType::PROPERTY_BORDER_TOP_COLOR);
                } },
            { DOM_BORDER_BOTTOM_COLOR,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    auto color = util.ParseColor(value);
                    util.AddAnimatable<Color>(color, time, AnimatableType::PROPERTY_BORDER_BOTTOM_COLOR);
                } },
            { DOM_BORDER_COLOR,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    auto color = util.ParseColor(value);
                    util.AddAnimatable<Color>(color, time, AnimatableType::PROPERTY_BORDER_LEFT_COLOR);
                    util.AddAnimatable<Color>(color, time, AnimatableType::PROPERTY_BORDER_TOP_COLOR);
                    util.AddAnimatable<Color>(color, time, AnimatableType::PROPERTY_BORDER_RIGHT_COLOR);
                    util.AddAnimatable<Color>(color, time, AnimatableType::PROPERTY_BORDER_BOTTOM_COLOR);
                } },
            { DOM_BORDER_LEFT_STYLE,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    auto borderStyle = Framework::ConvertStrToBorderStyle(value);
                    util.AddAnimatable<BorderStyle>(borderStyle, time, AnimatableType::PROPERTY_BORDER_LEFT_STYLE);
                } },
            { DOM_BORDER_RIGHT_STYLE,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    auto borderStyle = Framework::ConvertStrToBorderStyle(value);
                    util.AddAnimatable<BorderStyle>(borderStyle, time, AnimatableType::PROPERTY_BORDER_RIGHT_STYLE);
                } },
            { DOM_BORDER_TOP_STYLE,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    auto borderStyle = Framework::ConvertStrToBorderStyle(value);
                    util.AddAnimatable<BorderStyle>(borderStyle, time, AnimatableType::PROPERTY_BORDER_TOP_STYLE);
                } },
            { DOM_BORDER_BOTTOM_STYLE,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    auto borderStyle = Framework::ConvertStrToBorderStyle(value);
                    util.AddAnimatable<BorderStyle>(borderStyle, time, AnimatableType::PROPERTY_BORDER_BOTTOM_STYLE);
                } },
            { DOM_BORDER_STYLE,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    auto borderStyle = Framework::ConvertStrToBorderStyle(value);
                    util.AddAnimatable<BorderStyle>(borderStyle, time, AnimatableType::PROPERTY_BORDER_LEFT_STYLE);
                    util.AddAnimatable<BorderStyle>(borderStyle, time, AnimatableType::PROPERTY_BORDER_TOP_STYLE);
                    util.AddAnimatable<BorderStyle>(borderStyle, time, AnimatableType::PROPERTY_BORDER_RIGHT_STYLE);
                    util.AddAnimatable<BorderStyle>(borderStyle, time, AnimatableType::PROPERTY_BORDER_BOTTOM_STYLE);
                } },
            { DOM_FILTER,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    auto radius = ParseFunctionValue<Dimension>(value, DOM_BLUR, Framework::StringToDimension);
                    if (GreatOrEqual(radius.Value(), 0.0)) {
                        util.AddAnimatable<float>(
                            static_cast<float>(radius.Value()), time, AnimatableType::PROPERTY_FILTER_BLUR);
                    }
                } },
            { DOM_BACKDROP_FILTER,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    auto radius = ParseFunctionValue<Dimension>(value, DOM_BLUR, Framework::StringToDimension);
                    if (GreatOrEqual(radius.Value(), 0.0)) {
                        util.AddAnimatable<float>(
                            static_cast<float>(radius.Value()), time, AnimatableType::PROPERTY_BACKDROP_FILTER_BLUR);
                    }
                } },
            { DOM_WINDOW_FILTER,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    std::vector<std::string> offsets;
                    StringUtils::StringSplitter(value, ' ', offsets);
                    // property animation only support progress
                    if (!offsets.empty()) {
                        auto progress =
                            ParseFunctionValue<Dimension>(offsets[0], DOM_BLUR, Framework::StringToDimension);
                        if (progress.Unit() == DimensionUnit::PERCENT) {
                            if (GreatOrEqual(progress.Value(), 0.0) && LessOrEqual(progress.Value(), 1.0)) {
                                util.AddAnimatable<float>(static_cast<float>(progress.Value()), time,
                                    AnimatableType::PROPERTY_WINDOW_FILTER_BLUR);
                            }
                        }
                    }
                } },
            // BoxShadow
            { DOM_BOX_SHADOW_H,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    auto& shadow = util.shadowKeyframes_[timeStr];
                    shadow.SetOffsetX(util.ParseDouble(value));
                } },
            { DOM_BOX_SHADOW_V,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    auto& shadow = util.shadowKeyframes_[timeStr];
                    shadow.SetOffsetY(util.ParseDouble(value));
                } },
            { DOM_BOX_SHADOW_BLUR,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    auto& shadow = util.shadowKeyframes_[timeStr];
                    shadow.SetBlurRadius(util.ParseDouble(value));
                } },
            { DOM_BOX_SHADOW_SPREAD,
                [](const std::string& value, const double& time,  const std::string& timeStr, AnimationUtil& util) {
                    auto& shadow = util.shadowKeyframes_[timeStr];
                    shadow.SetSpreadRadius(util.ParseDouble(value));
                } },
            { DOM_BOX_SHADOW_COLOR,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    auto& shadow = util.shadowKeyframes_[timeStr];
                    shadow.SetColor(util.ParseColor(value));
                } },
            // position
            { DOM_POSITION_LEFT,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    util.AddAnimatable(
                        util.ParseDimension(value), time, AnimatableType::PROPERTY_POSITION_LEFT);
                } },
            { DOM_POSITION_TOP,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    util.AddAnimatable(
                        util.ParseDimension(value), time, AnimatableType::PROPERTY_POSITION_TOP);
                } },
            { DOM_POSITION_RIGHT,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    util.AddAnimatable(
                        util.ParseDimension(value), time, AnimatableType::PROPERTY_POSITION_RIGHT);
                } },
            { DOM_POSITION_BOTTOM,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    util.AddAnimatable(
                        util.ParseDimension(value), time, AnimatableType::PROPERTY_POSITION_BOTTOM);
                } },
            { DOM_TRANSFORM,
                [](const std::string& value, const double& time, const std::string& timeStr, AnimationUtil& util) {
                    std::unique_ptr<JsonValue> transformJson = JsonUtil::ParseJsonString(value);
                    if (transformJson->GetArraySize() == 0) {
                        // when empty should insert an identity matrix.
                        util.transformConvertor_.InsertIdentityKeyframe(time);
                    }
                    for (int32_t index = 0; index < transformJson->GetArraySize(); ++index) {
                        std::string typeKey = GetTransformType(transformJson->GetArrayItem(index));
                        std::string typeValue = GetTransformTypeValue(transformJson->GetArrayItem(index));
                        if ((!typeKey.empty()) && (!typeValue.empty())) {
                            util.transformConvertor_.Convert(typeKey, typeValue, time);
                        }
                    }
                } },
        };
    auto pos = keyFrameAddMap.find(keyStyle);
    if (pos != keyFrameAddMap.end()) {
        double time = StringUtils::StringToDouble(timeStr) / 100.0;
        pos->second(value, time, timeStr, *this);
    }
}

AnimationOption AnimationUtil::CreateKeyboardAnimationOption(
    const KeyboardAnimationConfig& config, float keyboardHeight)
{
    static const LinearMapNode<RefPtr<Curve>> curveMap[] = {
        { "ease", Curves::EASE },
        { "easeIn", Curves::EASE_IN },
        { "easeInOut", Curves::EASE_IN_OUT },
        { "easeOut", Curves::EASE_OUT },
        { "default", Curves::EASE_IN_OUT },
        { "linear", Curves::LINEAR },
        { "spring", AceType::MakeRefPtr<ResponsiveSpringMotion>(ResponsiveSpringMotion::DEFAULT_SPRING_MOTION_RESPONSE,
                        ResponsiveSpringMotion::DEFAULT_SPRING_MOTION_DAMPING_RATIO,
                        ResponsiveSpringMotion::DEFAULT_SPRING_MOTION_BLEND_DURATION) },
        { "interactiveSpring", AceType::MakeRefPtr<ResponsiveSpringMotion>(
                                   ResponsiveSpringMotion::DEFAULT_RESPONSIVE_SPRING_MOTION_RESPONSE,
                                   ResponsiveSpringMotion::DEFAULT_RESPONSIVE_SPRING_MOTION_DAMPING_RATIO,
                                   ResponsiveSpringMotion::DEFAULT_RESPONSIVE_SPRING_MOTION_BLEND_DURATION) },
    };

    AnimationOption option;
    auto curveConfig = NearZero(keyboardHeight) ? config.curveOut_ : config.curveIn_;
    option.SetDuration(curveConfig.duration_);
    RefPtr<Curve> curve;
    if (curveConfig.curveType_ == "cubic" && curveConfig.curveParams_.size() == PARAMS_NUM) {
        // cubic curve needs 4 params
        curve = AceType::MakeRefPtr<CubicCurve>(
            curveConfig.curveParams_[INITIAL_VELOCITY], curveConfig.curveParams_[DAMPING],
            curveConfig.curveParams_[STIFFNESS], curveConfig.curveParams_[MASS]);
    } else if (curveConfig.curveType_ == "interpolatingSpring" && curveConfig.curveParams_.size() == PARAMS_NUM) {
        // interpolatingSpring needs 4 params
        curve = AceType::MakeRefPtr<InterpolatingSpring>(
            curveConfig.curveParams_[INITIAL_VELOCITY], curveConfig.curveParams_[DAMPING],
            curveConfig.curveParams_[STIFFNESS], curveConfig.curveParams_[MASS]);
    } else {
        auto index = BinarySearchFindIndex(curveMap, ArraySize(curveMap), curveConfig.curveType_.c_str());
        curve = index < 0 ? nullptr : curveMap[index].value;
    }
    option.SetCurve(curve);
    return option;
}

template<class T>
void AnimationUtil::AddAnimatable(const T& value, double time, AnimatableType type)
{
    auto animatable = AceType::MakeRefPtr<AnimatableData<T>>(value);
    animatable->SetTimePoint(time);
    auto it = propAnimationMap_.find(type);
    if (it == propAnimationMap_.end()) {
        auto animation = AceType::MakeRefPtr<PropertyAnimation>(type);
        animation->AddAnimatable(animatable);
        propAnimationMap_.emplace(type, animation);
        return;
    }
    it->second->AddAnimatable(animatable);
}

RefPtr<ThemeConstants> AnimationUtil::GetThemeConstants() const
{
    return themeConstants_;
}

Color AnimationUtil::ParseColor(const std::string& value, uint32_t maskAlpha) const
{
    auto&& noRefFunc = [&value, maskAlpha = maskAlpha]() { return Color::FromString(value, maskAlpha); };
    auto&& idRefFunc = [constants = themeConstants_](uint32_t refId) { return constants->GetColor(refId); };
    if (!themeConstants_) {
        noRefFunc();
    }
    return ParseThemeReference<Color>(value, noRefFunc, idRefFunc, Color::TRANSPARENT);
}

double AnimationUtil::ParseDouble(const std::string& value) const
{
    auto&& noRefFunc = [&value]() { return StringUtils::StringToDouble(value); };
    auto&& idRefFunc = [constants = themeConstants_](uint32_t refId) { return constants->GetDouble(refId); };
    if (!themeConstants_) {
        noRefFunc();
    }
    return ParseThemeReference<double>(value, noRefFunc, idRefFunc, 0.0);
}

Dimension AnimationUtil::ParseDimension(const std::string& value) const
{
    auto&& noRefFunc = [&value]() { return StringUtils::StringToDimension(value); };
    auto&& idRefFunc = [constants = themeConstants_](uint32_t refId) { return constants->GetDimension(refId); };
    if (!themeConstants_) {
        noRefFunc();
    }
    return ParseThemeReference<Dimension>(value, noRefFunc, idRefFunc, Dimension());
}

} // namespace OHOS::Ace
