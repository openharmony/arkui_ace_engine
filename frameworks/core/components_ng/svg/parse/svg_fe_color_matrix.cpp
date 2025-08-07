/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/svg/parse/svg_fe_color_matrix.h"

#include "core/components_ng/svg/parse/svg_constants.h"
#include "core/pipeline/base/constants.h"

namespace OHOS::Ace::NG {

static constexpr float HUE_R = 0.213f;
static constexpr float HUE_G = 0.715f;
static constexpr float HUE_B = 0.072f;

static constexpr float LUM_COEFF_R = 0.2126f;
static constexpr float LUM_COEFF_G = 0.7152f;
static constexpr float LUM_COEFF_B = 0.0722f;

bool ConvertStringToFloat(const std::string& str, float& result)
{
    char* endPtr = nullptr;
    errno = 0; // Reset errno before calling strtof

    // Check for overflow or underflow
    result = std::strtof(str.c_str(), &endPtr);
    if (errno == ERANGE || result == HUGE_VALF || result == -HUGE_VALF) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "Out of range: string value is too large or too small for float");
        return false;
    }

    // Check if no conversion was performed or if there are invalid characters
    if (endPtr == str.c_str() || *endPtr != '\0') {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "Invalid argument: unable to convert string to float");
        return false;
    }

    return true;
}

inline float DegreesToRadians(float degrees)
{
    return (degrees) * (ACE_PI / 180.0f);
}

const std::vector<float> luminanceMatrix_ = {
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    LUM_COEFF_R, LUM_COEFF_G, LUM_COEFF_B, 0, 0
};

static void SetRow(float* row, float r, float g, float b)
{
    row[0] = r;
    row[1] = g;
    row[2] = b;
}

RefPtr<SvgNode> SvgFeColorMatrix::Create()
{
    return AceType::MakeRefPtr<SvgFeColorMatrix>();
}

SvgFeColorMatrix::SvgFeColorMatrix() : SvgFe() {}

void SvgFeColorMatrix::MakeMatrix(const std::string& value)
{
    std::vector<float> matrix;
    if (!StringUtils::ParseStringToArray(value, matrix)) {
        return;
    }
    // when matrix length not equal 20, then return
    if (matrix.size() != matrix_.size()) {
        return;
    }
    matrix_ = matrix;
}

void SvgFeColorMatrix::MakeHueRotate(const std::string& value)
{
    float theta = 0.0;
    float result = 0.0;
    if (ConvertStringToFloat(value, result)) {
        theta = DegreesToRadians(result);
    }
    const float cosValue = cos(theta);
    const float sinValue = sin(theta);

    // The source of the formula is this website: https://www.w3.org/TR/SVG11/filters.html#FilterPrimitiveSubRegion
    matrix_ = {
        0.213f + cosValue*0.787f + sinValue*-0.213f,
        0.715f + cosValue*-0.715f + sinValue*-0.715f,
        0.072f + cosValue*-0.072f + sinValue* 0.928f,
        0,
        0,

        0.213f + cosValue*-0.213f + sinValue* 0.143f,
        0.715f + cosValue* 0.285f + sinValue* 0.140f,
        0.072f + cosValue*-0.072f + sinValue*-0.283f,
        0,
        0,

        0.213f + cosValue*-0.213f + sinValue*-0.787f,
        0.715f + cosValue*-0.715f + sinValue* 0.715f,
        0.072f + cosValue* 0.928f + sinValue* 0.072f,
        0,
        0,

        0, 0, 0, 1, 0
    };
}

void SvgFeColorMatrix::MakeSaturate(const std::string& value)
{
    float satValue = 1.0;
    float result = 0.0;
    if (ConvertStringToFloat(value, result)) {
        satValue = result;
    }

    const float RValue = HUE_R * (1 - satValue);
    const float GValue = HUE_G * (1 - satValue);
    const float BValue = HUE_B * (1 - satValue);

    SetRow(matrix_.data() +  0, RValue + satValue, GValue, BValue);
    SetRow(matrix_.data() +  5, RValue, GValue + satValue, BValue);
    SetRow(matrix_.data() + 10, RValue, GValue, BValue + satValue);
}

void SvgFeColorMatrix::MakeLuminanceToAlpha()
{
    matrix_ = luminanceMatrix_;
}

void SvgFeColorMatrix::OnInitStyle()
{
    auto type = matrixAttr_.type;
    switch (type) {
        case SvgFeColorMatrixType::SATURATE:
            MakeSaturate(matrixAttr_.values);
            break;
        case SvgFeColorMatrixType::HUE_ROTATE:
            MakeHueRotate(matrixAttr_.values);
            break;
        case SvgFeColorMatrixType::LUMINACE_TO_ALPHA:
            MakeLuminanceToAlpha();
            break;
        default:
            MakeMatrix(matrixAttr_.values);
            break;
    }
}

void SvgFeColorMatrix::OnAsImageFilter(std::shared_ptr<RSImageFilter>& imageFilter,
    const SvgColorInterpolationType& srcColor, SvgColorInterpolationType& currentColor,
    std::unordered_map<std::string, std::shared_ptr<RSImageFilter>>& resultHash, bool cropRect) const
{
    imageFilter = MakeImageFilter(feAttr_.in, imageFilter, resultHash);

    RSColorMatrix colorMatrix;
    colorMatrix.SetArray(matrix_.data());
    auto colorFilter = RSRecordingColorFilter::CreateMatrixColorFilter(colorMatrix);
    CHECK_NULL_VOID(colorFilter);
    RSRect filterRect(effectFilterArea_.Left(), effectFilterArea_.Top(),
        effectFilterArea_.Right(), effectFilterArea_.Bottom());
    if (cropRect) {
        imageFilter = RSRecordingImageFilter::CreateColorFilterImageFilter(*colorFilter,
            imageFilter, filterRect);
    } else {
        imageFilter = RSRecordingImageFilter::CreateColorFilterImageFilter(*colorFilter, imageFilter);
    }
    ConverImageFilterColor(imageFilter, srcColor, currentColor);
    RegisterResult(feAttr_.result, imageFilter, resultHash);
}

bool SvgFeColorMatrix::ParseAndSetSpecializedAttr(const std::string& name, const std::string& value)
{
    static const LinearMapNode<void (*)(const std::string&, SvgFeColorMatrixAttribute&)> attrs[] = {
        { SVG_FE_TYPE,
            [](const std::string& type, SvgFeColorMatrixAttribute& attr) {
                if (type == "saturate") {
                    attr.type = SvgFeColorMatrixType::SATURATE;
                } else if (type == "hueRotate") {
                    attr.type = SvgFeColorMatrixType::HUE_ROTATE;
                } else if (type == "luminanceToAlpha") {
                    attr.type = SvgFeColorMatrixType::LUMINACE_TO_ALPHA;
                }
            } },
        { SVG_FE_VALUES,
            [](const std::string& val, SvgFeColorMatrixAttribute& attr) {
                attr.values = val;
            } },
    };
    auto attrIter = BinarySearchFindIndex(attrs, ArraySize(attrs), name.c_str());
    if (attrIter != -1) {
        attrs[attrIter].value(value, matrixAttr_);
        return true;
    }
    return SvgFe::ParseAndSetSpecializedAttr(name, value);
}

} // namespace OHOS::Ace::NG
