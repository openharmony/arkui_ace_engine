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

#include "frameworks/bridge/common/utils/utils.h"

#include "frameworks/bridge/js_frontend/engine/common/js_constants.h"
#include "interfaces/native/native_type.h"

namespace OHOS::Ace::Framework {

namespace {

using CustomCurveCreator = RefPtr<Curve> (*)(const std::vector<std::string>&);

const size_t STEPS_PARAMS_SIZE = 2;
const size_t CUBIC_PARAMS_SIZE = 4;
const size_t SPRING_PARAMS_SIZE = 4;
constexpr size_t RESPONSIVE_SPRING_MOTION_PARAMS_SIZE = 3;
constexpr size_t INTERPOLATING_SPRING_PARAMS_SIZE = 4;

static const std::unordered_set<std::string> HORIZON_SET = {
    DOM_BACKGROUND_IMAGE_POSITION_LEFT,
    DOM_BACKGROUND_IMAGE_POSITION_RIGHT,
};
static const std::unordered_set<std::string> VERTICAL_SET = {
    DOM_BACKGROUND_IMAGE_POSITION_TOP,
    DOM_BACKGROUND_IMAGE_POSITION_BOTTOM,
};
static const std::unordered_set<std::string> OBJECT_HORIZON_SET = {
    DOM_IMAGE_POSITION_LEFT,
    DOM_IMAGE_POSITION_RIGHT,
};
static const std::unordered_set<std::string> OBJECT_VERTICAL_SET = {
    DOM_IMAGE_POSITION_TOP,
    DOM_IMAGE_POSITION_BOTTOM,
};

RefPtr<Curve> StepsCurveCreator(const std::vector<std::string>& params)
{
    if (params.empty() || params.size() > STEPS_PARAMS_SIZE) {
        return nullptr;
    }
    auto step = StringUtils::StringToInt(params.front());
    if (step <= 0) {
        return nullptr;
    }
    StepsCurvePosition position = StepsCurvePosition::END;
    if (params.size() > 1) {
        if (params.back() == "start") {
            position = StepsCurvePosition::START;
        } else if (params.back() == "end") {
            position = StepsCurvePosition::END;
        } else {
            return nullptr;
        }
    }
    return AceType::MakeRefPtr<StepsCurve>(step, position);
}

RefPtr<Curve> CubicCurveCreator(const std::vector<std::string>& params)
{
    if (params.size() != CUBIC_PARAMS_SIZE) {
        return nullptr;
    }
    double x1 = StringToDouble(params.at(0));
    double y1 = StringToDouble(params.at(1));
    double x2 = StringToDouble(params.at(2));
    double y2 = StringToDouble(params.at(3));
    return AceType::MakeRefPtr<CubicCurve>(x1, y1, x2, y2);
}

RefPtr<Curve> SpringCurveCreator(const std::vector<std::string>& params)
{
    if (params.size() != SPRING_PARAMS_SIZE) {
        return nullptr;
    }
    double velocity = StringToDouble(params.at(0));
    double mass = StringToDouble(params.at(1));
    double stiffness = StringToDouble(params.at(2));
    double damping = StringToDouble(params.at(3));
    return AceType::MakeRefPtr<SpringCurve>(velocity, mass, stiffness, damping);
}

RefPtr<Curve> InterpolatingSpringCreator(const std::vector<std::string>& params)
{
    if (params.size() != INTERPOLATING_SPRING_PARAMS_SIZE) {
        return nullptr;
    }
    double velocity = StringToDouble(params.at(0));
    double mass = StringToDouble(params.at(1));
    double stiffness = StringToDouble(params.at(2));
    double damping = StringToDouble(params.at(3));
    return AceType::MakeRefPtr<InterpolatingSpring>(velocity, mass, stiffness, damping);
}

RefPtr<Curve> SpringMotionCreator(const std::vector<std::string>& params)
{
    if (params.size() > RESPONSIVE_SPRING_MOTION_PARAMS_SIZE) {
        return nullptr;
    }
    size_t paramSize = params.size();
    float response = paramSize > 0 ? StringUtils::StringToFloat(params[0])
                        : ResponsiveSpringMotion::DEFAULT_SPRING_MOTION_RESPONSE;
    float dampingRatio = paramSize > 1 ? StringUtils::StringToFloat(params[1])
                            : ResponsiveSpringMotion::DEFAULT_SPRING_MOTION_DAMPING_RATIO;
    float blendDuration = paramSize > 2 ? StringUtils::StringToFloat(params[2])
                            : ResponsiveSpringMotion::DEFAULT_SPRING_MOTION_BLEND_DURATION;
    return AceType::MakeRefPtr<ResponsiveSpringMotion>(response, dampingRatio, blendDuration);
}

RefPtr<Curve> ResponsiveSpringMotionCreator(const std::vector<std::string>& params)
{
    if (params.size() > RESPONSIVE_SPRING_MOTION_PARAMS_SIZE) {
        return nullptr;
    }
    size_t paramSize = params.size();
    float response = paramSize > 0 ? StringUtils::StringToFloat(params[0])
                        : ResponsiveSpringMotion::DEFAULT_RESPONSIVE_SPRING_MOTION_RESPONSE;
    float dampingRatio = paramSize > 1 ? StringUtils::StringToFloat(params[1])
                            : ResponsiveSpringMotion::DEFAULT_RESPONSIVE_SPRING_MOTION_DAMPING_RATIO;
    float blendDuration = paramSize > 2 ? StringUtils::StringToFloat(params[2])
                            : ResponsiveSpringMotion::DEFAULT_RESPONSIVE_SPRING_MOTION_BLEND_DURATION;
    return AceType::MakeRefPtr<ResponsiveSpringMotion>(response, dampingRatio, blendDuration);
}
#ifndef FUZZTEST
void SetBgImgPositionX(
    const BackgroundImagePositionType type, const double value, BackgroundImagePosition& bgImgPosition)
{
    bgImgPosition.SetSizeTypeX(type);
    bgImgPosition.SetSizeValueX(value);
}

void SetBgImgPositionY(
    const BackgroundImagePositionType type, const double value, BackgroundImagePosition& bgImgPosition)
{
    bgImgPosition.SetSizeTypeY(type);
    bgImgPosition.SetSizeValueY(value);
}

void SetBgImgPosition(
    const BackgroundImagePositionType type, const double value, BackgroundImagePosition& bgImgPosition)
{
    SetBgImgPositionX(type, value, bgImgPosition);
    SetBgImgPositionY(type, value, bgImgPosition);
}

void GetOffsetValue(std::vector<std::string> offsets, std::string& posX, std::string& posY)
{
    if (offsets.size() == 1) {
        posX = offsets.front();
        if (VERTICAL_SET.find(posX) != VERTICAL_SET.end()) {
            posY = offsets.front();
            posX = DOM_BACKGROUND_IMAGE_POSITION_CENTER;
        } else {
            posY = DOM_BACKGROUND_IMAGE_POSITION_CENTER;
        }
    } else {
        posX = offsets.front();
        posY = offsets.back();
        if (VERTICAL_SET.find(posX) != VERTICAL_SET.end() && HORIZON_SET.find(posY) != HORIZON_SET.end()) {
            posY = offsets.front();
            posX = offsets.back();
        }
    }
}

// object-position check msg number
void GetOffsetValueObjectPosition(std::vector<std::string> offsets, std::string& posX, std::string& posY)
{
    if (offsets.size() == 1) {
        posX = offsets.front();
        if (OBJECT_VERTICAL_SET.find(posX) != OBJECT_VERTICAL_SET.end()) {
            posY = offsets.front();
            posX = DOM_IMAGE_POSITION_CENTER;
        } else {
            posY = DOM_IMAGE_POSITION_CENTER;
        }
    } else {
        posX = offsets.front();
        posY = offsets.back();
        if (OBJECT_VERTICAL_SET.find(posX) != OBJECT_VERTICAL_SET.end()
            && OBJECT_HORIZON_SET.find(posY) != OBJECT_HORIZON_SET.end()) {
            posY = offsets.front();
            posX = offsets.back();
        }
    }
}

bool BgImgPositionIsValid(const std::string& posX, const std::string& posY)
{
    if ((posX == DOM_BACKGROUND_IMAGE_POSITION_CENTER) || (posY == DOM_BACKGROUND_IMAGE_POSITION_CENTER)) {
        return true;
    }
    // posX and posY are not strictly corresponding to horizontal or vertical, but they must not conflict,
    // for example both of them are "top" is invalid.
    if (posX.find("px") != std::string::npos || posX.find('%') != std::string::npos ||
        HORIZON_SET.find(posX) != HORIZON_SET.end()) {
        if (posY.find("px") != std::string::npos || posY.find('%') != std::string::npos ||
            VERTICAL_SET.find(posY) != VERTICAL_SET.end()) {
            return true;
        }
    }
    return VERTICAL_SET.find(posX) != VERTICAL_SET.end() && HORIZON_SET.find(posY) != HORIZON_SET.end();
}

// objectPosition
bool ObjectImgPositionIsValid(const std::string& posX, const std::string& posY)
{
    if (posX.find("px") != std::string::npos || posX.find('%') != std::string::npos ||
        OBJECT_HORIZON_SET.find(posX) != OBJECT_HORIZON_SET.end() || posX != DOM_IMAGE_POSITION_CENTER) {
        if (posY.find("px") != std::string::npos || posY.find('%') != std::string::npos ||
            OBJECT_VERTICAL_SET.find(posY) != OBJECT_VERTICAL_SET.end() || posY != DOM_IMAGE_POSITION_CENTER) {
            return true;
        }
    }
    return false;
}

void SetBgImgSizeX(BackgroundImageSizeType type, double value, BackgroundImageSize& bgImgSize)
{
    bgImgSize.SetSizeTypeX(type);
    bgImgSize.SetSizeValueX(value);
}

void SetBgImgSizeY(BackgroundImageSizeType type, double value, BackgroundImageSize& bgImgSize)
{
    bgImgSize.SetSizeTypeY(type);
    bgImgSize.SetSizeValueY(value);
}
#endif
} // namespace

RefPtr<Curve> CreateBuiltinCurve(const std::string& aniTimFunc)
{
    // this map should be sorted by key
    static const LinearMapNode<RefPtr<Curve>> aniTimFuncMap[] = {
        { DOM_ANIMATION_TIMING_FUNCTION_EASE, Curves::EASE },
        { DOM_ANIMATION_TIMING_FUNCTION_EASE_IN, Curves::EASE_IN },
        { DOM_ANIMATION_TIMING_FUNCTION_EASE_IN_OUT, Curves::EASE_IN_OUT },
        { DOM_ANIMATION_TIMING_FUNCTION_EASE_OUT, Curves::EASE_OUT },
        { DOM_ANIMATION_TIMING_FUNCTION_EXTREME_DECELERATION, Curves::EXTREME_DECELERATION },
        { DOM_ANIMATION_TIMING_FUNCTION_FAST_OUT_LINEAR_IN, Curves::FAST_OUT_LINEAR_IN },
        { DOM_ANIMATION_TIMING_FUNCTION_FAST_OUT_SLOW_IN, Curves::FAST_OUT_SLOW_IN },
        { DOM_ANIMATION_TIMING_FUNCTION_FRICTION, Curves::FRICTION },
        { DOM_ANIMATION_TIMING_FUNCTION_LINEAR, Curves::LINEAR },
        { DOM_ANIMATION_TIMING_FUNCTION_LINEAR_OUT_SLOW_IN, Curves::LINEAR_OUT_SLOW_IN },
        { DOM_ANIMATION_TIMING_FUNCTION_RHYTHM, Curves::RHYTHM },
        { DOM_ANIMATION_TIMING_FUNCTION_SHARP, Curves::SHARP },
        { DOM_ANIMATION_TIMING_FUNCTION_SMOOTH, Curves::SMOOTH },
    };
    auto index = BinarySearchFindIndex(aniTimFuncMap, ArraySize(aniTimFuncMap), aniTimFunc.c_str());
    return index < 0 ? nullptr : aniTimFuncMap[index].value;
}

std::string CurveIntToString(int curve)
{
    static const LinearEnumMapNode<ArkUI_AnimationCurve, std::string> curveMap[] = {
        { ArkUI_AnimationCurve::ARKUI_CURVE_EASE, DOM_ANIMATION_TIMING_FUNCTION_EASE },
        { ArkUI_AnimationCurve::ARKUI_CURVE_EASE_IN, DOM_ANIMATION_TIMING_FUNCTION_EASE_IN },
        { ArkUI_AnimationCurve::ARKUI_CURVE_EASE_IN_OUT, DOM_ANIMATION_TIMING_FUNCTION_EASE_IN_OUT },
        { ArkUI_AnimationCurve::ARKUI_CURVE_EASE_OUT, DOM_ANIMATION_TIMING_FUNCTION_EASE_OUT},
        { ArkUI_AnimationCurve::ARKUI_CURVE_EXTREME_DECELERATION, DOM_ANIMATION_TIMING_FUNCTION_EXTREME_DECELERATION },
        { ArkUI_AnimationCurve::ARKUI_CURVE_FAST_OUT_LINEAR_IN, DOM_ANIMATION_TIMING_FUNCTION_FAST_OUT_LINEAR_IN },
        { ArkUI_AnimationCurve::ARKUI_CURVE_FAST_OUT_SLOW_IN, DOM_ANIMATION_TIMING_FUNCTION_FAST_OUT_SLOW_IN},
        { ArkUI_AnimationCurve::ARKUI_CURVE_FRICTION, DOM_ANIMATION_TIMING_FUNCTION_FRICTION },
        { ArkUI_AnimationCurve::ARKUI_CURVE_LINEAR, DOM_ANIMATION_TIMING_FUNCTION_LINEAR},
        { ArkUI_AnimationCurve::ARKUI_CURVE_LINEAR_OUT_SLOW_IN, DOM_ANIMATION_TIMING_FUNCTION_LINEAR_OUT_SLOW_IN},
        { ArkUI_AnimationCurve::ARKUI_CURVE_RHYTHM, DOM_ANIMATION_TIMING_FUNCTION_RHYTHM},
        { ArkUI_AnimationCurve::ARKUI_CURVE_SHARP, DOM_ANIMATION_TIMING_FUNCTION_SHARP},
        { ArkUI_AnimationCurve::ARKUI_CURVE_SMOOTH, DOM_ANIMATION_TIMING_FUNCTION_SMOOTH},
    };
    auto index = BinarySearchFindIndex(curveMap, ArraySize(curveMap), static_cast<ArkUI_AnimationCurve>(curve));
    return index < 0 ? DOM_ANIMATION_TIMING_FUNCTION_LINEAR : curveMap[index].value;
}

bool ParseCurveParam(
    const std::string& aniTimFunc, std::string& curveName, std::vector<std::string>& paramsVector)
{
    if (aniTimFunc.back() != ')') {
        return false;
    }
    std::string::size_type leftEmbracePosition = aniTimFunc.find_last_of('(');
    if (leftEmbracePosition == std::string::npos) {
        return false;
    }
    auto aniTimFuncName = aniTimFunc.substr(0, leftEmbracePosition);
    auto params = aniTimFunc.substr(leftEmbracePosition + 1, aniTimFunc.length() - leftEmbracePosition - 2);
    if (aniTimFuncName.empty() || params.empty()) {
        return false;
    }
    StringUtils::StringSplitter(params, ',', paramsVector);
    for (auto& param : paramsVector) {
        RemoveHeadTailSpace(param);
    }
    curveName = std::move(aniTimFuncName);
    return true;
}

RefPtr<Curve> CreateCustomCurve(const std::string& aniTimFunc)
{
    std::string aniTimFuncName;
    std::vector<std::string> paramsVector;
    bool result = ParseCurveParam(aniTimFunc, aniTimFuncName, paramsVector);
    if (!result) {
        return nullptr;
    }
    static const LinearMapNode<CustomCurveCreator> customCurveMap[] = {
        { DOM_ANIMATION_TIMING_FUNCTION_CUBIC_BEZIER, CubicCurveCreator },
        { DOM_ANIMATION_TIMING_FUNCTION_INTERPOLATING_SPRING, InterpolatingSpringCreator },
        { DOM_ANIMATION_TIMING_FUNCTION_RESPONSIVE_SPRING_MOTION, ResponsiveSpringMotionCreator },
        { DOM_ANIMATION_TIMING_FUNCTION_SPRING, SpringCurveCreator },
        { DOM_ANIMATION_TIMING_FUNCTION_SPRING_MOTION, SpringMotionCreator },
        { DOM_ANIMATION_TIMING_FUNCTION_STEPS, StepsCurveCreator },
    };
    int64_t index = BinarySearchFindIndex(customCurveMap, ArraySize(customCurveMap), aniTimFuncName.c_str());
    if (index < 0) {
        return nullptr;
    }
    return customCurveMap[index].value(paramsVector);
}

RefPtr<Curve> CreateCustomCurveExceptSpring(const std::string& aniTimFunc)
{
    std::string aniTimFuncName;
    std::vector<std::string> paramsVector;
    bool result = ParseCurveParam(aniTimFunc, aniTimFuncName, paramsVector);
    if (!result) {
        return nullptr;
    }
    static const LinearMapNode<CustomCurveCreator> customCurveExceptSpringMap[] = {
        { DOM_ANIMATION_TIMING_FUNCTION_CUBIC_BEZIER, CubicCurveCreator },
        { DOM_ANIMATION_TIMING_FUNCTION_SPRING, SpringCurveCreator },
        { DOM_ANIMATION_TIMING_FUNCTION_STEPS, StepsCurveCreator },
    };
    int64_t index = BinarySearchFindIndex(
        customCurveExceptSpringMap, ArraySize(customCurveExceptSpringMap), aniTimFuncName.c_str());
    if (index < 0) {
        return nullptr;
    }
    return customCurveExceptSpringMap[index].value(paramsVector);
}

RefPtr<Curve> CreateCurve(const std::function<float(float)>& jsFunc)
{
    if (jsFunc) {
        return AceType::MakeRefPtr<CustomCurve>(jsFunc);
    }
    return Curves::EASE_IN_OUT;
}

RefPtr<Curve> CreateCurve(const std::string& aniTimFunc, bool useDefault)
{
    auto curve = CreateBuiltinCurve(aniTimFunc);
    if (curve) {
        return curve;
    }
    curve = CreateCustomCurve(aniTimFunc);
    if (curve) {
        return curve;
    }
    return useDefault? Curves::EASE_IN_OUT : nullptr;
}

// create curve whose duration works. i.e not support spring
RefPtr<Curve> CreateCurveExceptSpring(
    const std::string& aniTimFunc, const std::function<float(float)>& jsFunc)
{
    if (jsFunc) {
        return AceType::MakeRefPtr<CustomCurve>(jsFunc);
    }
    auto curve = CreateBuiltinCurve(aniTimFunc);
    if (curve) {
        return curve;
    }
    curve = CreateCustomCurveExceptSpring(aniTimFunc);
    if (curve) {
        return curve;
    }
    return Curves::EASE_IN_OUT;
}

// used for declarative only
TransitionType ParseTransitionType(const std::string& transitionType)
{
    if (transitionType == "All") {
        return TransitionType::ALL;
    } else if (transitionType == "Insert") {
        return TransitionType::APPEARING;
    } else if (transitionType == "Delete") {
        return TransitionType::DISAPPEARING;
    } else {
        return TransitionType::ALL;
    }
}
#ifndef FUZZTEST
// Support keyword values / percentage/px values. Do not support multiple images and edge offsets values.
bool ParseBackgroundImagePosition(const std::string& value, BackgroundImagePosition& backgroundImagePosition)
{
    static const LinearMapNode<void (*)(BackgroundImagePosition&)> backGroundPositionOperators[] = {
        { DOM_BACKGROUND_IMAGE_POSITION_BOTTOM,
            [](BackgroundImagePosition& backgroundImagePosition) {
                SetBgImgPositionY(BackgroundImagePositionType::PERCENT, 100.0, backgroundImagePosition);
            } },
        { DOM_BACKGROUND_IMAGE_POSITION_LEFT,
            [](BackgroundImagePosition& backgroundImagePosition) {
                SetBgImgPositionX(BackgroundImagePositionType::PERCENT, 0.0, backgroundImagePosition);
            } },
        { DOM_BACKGROUND_IMAGE_POSITION_RIGHT,
            [](BackgroundImagePosition& backgroundImagePosition) {
                SetBgImgPositionX(BackgroundImagePositionType::PERCENT, 100.0, backgroundImagePosition);
            } },
        { DOM_BACKGROUND_IMAGE_POSITION_TOP,
            [](BackgroundImagePosition& backgroundImagePosition) {
                SetBgImgPositionY(BackgroundImagePositionType::PERCENT, 0.0, backgroundImagePosition);
            } },
    };

    std::vector<std::string> offsets;
    StringUtils::StringSplitter(value, ' ', offsets);
    if (!offsets.empty()) {
        std::string valueX = "";
        std::string valueY = "";
        GetOffsetValue(offsets, valueX, valueY);
        if (!BgImgPositionIsValid(valueX, valueY)) {
            return false;
        }
        // The input is valid,so set the default is (center,center),
        // if the value is different, the default value is overwritten.
        // the center value is 50%.
        SetBgImgPosition(BackgroundImagePositionType::PERCENT, 50.0, backgroundImagePosition);
        if (valueX.find("px") != std::string::npos) {
            SetBgImgPositionX(BackgroundImagePositionType::PX, StringToDouble(valueX), backgroundImagePosition);
        } else if (valueX.find('%') != std::string::npos) {
            SetBgImgPositionX(BackgroundImagePositionType::PERCENT, StringToDouble(valueX), backgroundImagePosition);
        } else {
            auto operatorIterX = BinarySearchFindIndex(
                backGroundPositionOperators, ArraySize(backGroundPositionOperators), valueX.c_str());
            if (operatorIterX != -1) {
                backGroundPositionOperators[operatorIterX].value(backgroundImagePosition);
            }
        }
        if (valueY.find("px") != std::string::npos) {
            SetBgImgPositionY(BackgroundImagePositionType::PX, StringToDouble(valueY), backgroundImagePosition);
        } else if (valueY.find('%') != std::string::npos) {
            SetBgImgPositionY(BackgroundImagePositionType::PERCENT, StringToDouble(valueY), backgroundImagePosition);
        } else {
            auto operatorIterY = BinarySearchFindIndex(
                backGroundPositionOperators, ArraySize(backGroundPositionOperators), valueY.c_str());
            if (operatorIterY != -1) {
                backGroundPositionOperators[operatorIterY].value(backgroundImagePosition);
            }
        }
    } else {
        SetBgImgPosition(BackgroundImagePositionType::PERCENT, 50.0, backgroundImagePosition);
        if (value.find("px") != std::string::npos) {
            SetBgImgPositionX(BackgroundImagePositionType::PX, StringToDouble(value), backgroundImagePosition);
        } else if (value.find('%') != std::string::npos) {
            SetBgImgPositionX(BackgroundImagePositionType::PERCENT, StringToDouble(value), backgroundImagePosition);
        } else {
            auto operatorIter = BinarySearchFindIndex(
                backGroundPositionOperators, ArraySize(backGroundPositionOperators), value.c_str());
            if (operatorIter != -1) {
                backGroundPositionOperators[operatorIter].value(backgroundImagePosition);
            }
        }
    }
    return true;
}

bool ParseBackgroundImageSize(const std::string& value, BackgroundImageSize& bgImgSize)
{
    static const LinearMapNode<BackgroundImageSizeType> bgImageSizeType[] = {
        { DOM_BACKGROUND_IMAGE_SIZE_AUTO, BackgroundImageSizeType::AUTO },
        { DOM_BACKGROUND_IMAGE_SIZE_CONTAIN, BackgroundImageSizeType::CONTAIN },
        { DOM_BACKGROUND_IMAGE_SIZE_COVER, BackgroundImageSizeType::COVER },
        { DOM_BACKGROUND_IMAGE_SIZE_FILL, BackgroundImageSizeType::FILL },
    };
    auto spaceIndex = value.find(' ', 0);
    if (spaceIndex != std::string::npos) {
        std::string valueX = value.substr(0, spaceIndex);
        std::string valueY = value.substr(spaceIndex + 1, value.size() - spaceIndex - 1);
        if (valueX.find("px") != std::string::npos) {
            SetBgImgSizeX(BackgroundImageSizeType::LENGTH, StringToDouble(valueX), bgImgSize);
        } else if (valueX.find('%') != std::string::npos) {
            SetBgImgSizeX(BackgroundImageSizeType::PERCENT, StringToDouble(valueX), bgImgSize);
        } else {
            bgImgSize.SetSizeTypeX(BackgroundImageSizeType::AUTO);
        }
        if (valueY.find("px") != std::string::npos) {
            SetBgImgSizeY(BackgroundImageSizeType::LENGTH, StringToDouble(valueY), bgImgSize);
        } else if (valueY.find('%') != std::string::npos) {
            SetBgImgSizeY(BackgroundImageSizeType::PERCENT, StringToDouble(valueY), bgImgSize);
        } else {
            bgImgSize.SetSizeTypeY(BackgroundImageSizeType::AUTO);
        }
    } else {
        auto sizeTypeIter = BinarySearchFindIndex(bgImageSizeType, ArraySize(bgImageSizeType), value.c_str());
        if (sizeTypeIter != -1) {
            bgImgSize.SetSizeTypeX(bgImageSizeType[sizeTypeIter].value);
            bgImgSize.SetSizeTypeY(bgImageSizeType[sizeTypeIter].value);
        } else if (value.find("px") != std::string::npos) {
            SetBgImgSizeX(BackgroundImageSizeType::LENGTH, StringToDouble(value), bgImgSize);
            bgImgSize.SetSizeTypeY(BackgroundImageSizeType::AUTO);
        } else if (value.find('%') != std::string::npos) {
            SetBgImgSizeX(BackgroundImageSizeType::PERCENT, StringToDouble(value), bgImgSize);
            bgImgSize.SetSizeTypeY(BackgroundImageSizeType::AUTO);
        } else {
            bgImgSize.SetSizeTypeX(BackgroundImageSizeType::AUTO);
            bgImgSize.SetSizeTypeY(BackgroundImageSizeType::AUTO);
        }
    }
    return true;
}
#endif
RefPtr<ClipPath> CreateClipPath(const std::string& value)
{
    if (value.empty()) {
        return nullptr;
    }
    auto clipPath = ClipPath::CreateShape(value);
    GeometryBoxType geometryBoxType = ClipPath::GetGeometryBoxType(value);
    if (geometryBoxType != GeometryBoxType::NONE) {
        if (!clipPath) {
            clipPath = AceType::MakeRefPtr<ClipPath>();
        }
    }
    if (clipPath) {
        clipPath->SetGeometryBoxType(geometryBoxType);
    }
    return clipPath;
}

std::optional<RadialSizeType> ParseRadialGradientSize(const std::string& value)
{
    const static std::unordered_map<std::string, RadialSizeType> sizeTypes = {
        { DOM_GRADIENT_SIZE_CLOSEST_CORNER, RadialSizeType::CLOSEST_CORNER },
        { DOM_GRADIENT_SIZE_CLOSEST_SIDE, RadialSizeType::CLOSEST_SIDE },
        { DOM_GRADIENT_SIZE_FARTHEST_CORNER, RadialSizeType::FARTHEST_CORNER },
        { DOM_GRADIENT_SIZE_FARTHEST_SIDE, RadialSizeType::FARTHEST_SIDE },
    };
    if (!value.empty()) {
        auto pos = sizeTypes.find(value);
        if (pos != sizeTypes.end()) {
            return std::make_optional(pos->second);
        }
    }
    return std::nullopt;
}
#ifndef FUZZTEST
// ObjectPosition
ImageObjectPosition ParseImageObjectPosition(const std::string& value)
{
    ImageObjectPosition imageObjectPosition;
    static const LinearMapNode<void (*)(ImageObjectPosition&)> backGroundPositionOperators[] = {
        { DOM_IMAGE_POSITION_BOTTOM,
            [](ImageObjectPosition& imageObjectPosition) {
                SetBgImgPositionY(BackgroundImagePositionType::PERCENT, 100.0, imageObjectPosition);
            } },
        { DOM_IMAGE_POSITION_LEFT,
            [](ImageObjectPosition& imageObjectPosition) {
                SetBgImgPositionX(BackgroundImagePositionType::PERCENT, 0.0, imageObjectPosition);
            } },
        { DOM_IMAGE_POSITION_RIGHT,
            [](ImageObjectPosition& imageObjectPosition) {
                SetBgImgPositionX(BackgroundImagePositionType::PERCENT, 100.0, imageObjectPosition);
            } },
        { DOM_IMAGE_POSITION_TOP,
            [](ImageObjectPosition& imageObjectPosition) {
                SetBgImgPositionY(BackgroundImagePositionType::PERCENT, 0.0, imageObjectPosition);
            } },
    };

    std::vector<std::string> offsets;
    StringUtils::StringSplitter(value, ' ', offsets);
    if (!offsets.empty()) {
        std::string valueX = "";
        std::string valueY = "";
        GetOffsetValueObjectPosition(offsets, valueX, valueY);
        SetBgImgPosition(BackgroundImagePositionType::PERCENT, 50.0, imageObjectPosition);
        if (ObjectImgPositionIsValid(valueX, valueY)) {
            if (valueX.find("px") != std::string::npos) {
                SetBgImgPositionX(BackgroundImagePositionType::PX, StringToDouble(valueX), imageObjectPosition);
            } else if (valueX.find('%') != std::string::npos) {
                SetBgImgPositionX(BackgroundImagePositionType::PERCENT, StringToDouble(valueX), imageObjectPosition);
            } else {
                auto operatorIterX = BinarySearchFindIndex(
                    backGroundPositionOperators, ArraySize(backGroundPositionOperators), valueX.c_str());
                if (operatorIterX != -1) {
                    backGroundPositionOperators[operatorIterX].value(imageObjectPosition);
                }
            }
            if (valueY.find("px") != std::string::npos) {
                SetBgImgPositionY(BackgroundImagePositionType::PX, StringToDouble(valueY), imageObjectPosition);
            } else if (valueY.find('%') != std::string::npos) {
                SetBgImgPositionY(BackgroundImagePositionType::PERCENT, StringToDouble(valueY), imageObjectPosition);
            } else {
                auto operatorIterY = BinarySearchFindIndex(
                    backGroundPositionOperators, ArraySize(backGroundPositionOperators), valueY.c_str());
                if (operatorIterY != -1) {
                    backGroundPositionOperators[operatorIterY].value(imageObjectPosition);
                }
            }
        }
    }

    return imageObjectPosition;
}
#endif

} // namespace OHOS::Ace::Framework