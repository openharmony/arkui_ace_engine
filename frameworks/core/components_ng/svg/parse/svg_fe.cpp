/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "frameworks/core/components_ng/svg/parse/svg_fe.h"

#include "include/core/SkColorFilter.h"
#include "include/effects/SkColorMatrix.h"
#include "include/effects/SkImageFilters.h"

#include "base/utils/utils.h"

namespace OHOS::Ace::NG {

void InitFilterColor(const RefPtr<SvgFeDeclaration>& fe, ColorInterpolationType& currentColor)
{
    CHECK_NULL_VOID(fe);

    if (fe->GetIn().in == FeInType::SOURCE_GRAPHIC) {
        currentColor = ColorInterpolationType::SRGB;
    } else {
        currentColor = fe->GetColorInterpolationType();
    }
}

void SvgFe::OnInitStyle()
{
    auto declaration = Ace::AceType::DynamicCast<SvgFeDeclaration>(declaration_);
    CHECK_NULL_VOID(declaration);
    x_ = declaration->GetX();
    y_ = declaration->GetY();
    height_ = declaration->GetHeight();
    width_ = declaration->GetWidth();
}

void SvgFe::RegisterResult(const std::string& id, std::shared_ptr<RSImageFilter>& imageFilter,
    std::unordered_map<std::string, std::shared_ptr<RSImageFilter>>& resultHash) const
{
    if (!id.empty()) {
        resultHash[id] = imageFilter;
    }
}

SvgFe::SvgFe() : SvgNode()
{
    InitNoneFlag();
}

void SvgFe::GetImageFilter(std::shared_ptr<RSImageFilter>& imageFilter, ColorInterpolationType& currentColor,
    std::unordered_map<std::string, std::shared_ptr<RSImageFilter>>& resultHash,
    const Rect& effectFilterArea)
{
    ColorInterpolationType srcColor = currentColor;
    OnInitStyle();
    InitFilterColor(AceType::DynamicCast<SvgFeDeclaration>(declaration_), currentColor);
    Rect effectFeArea = effectFilterArea;
    if (x_.Unit() != DimensionUnit::PERCENT) {
        effectFeArea.SetLeft(x_.Value());
    }
    if (y_.Unit() != DimensionUnit::PERCENT) {
        effectFeArea.SetTop(x_.Value());
    }
    effectFeArea.SetWidth(width_.ConvertToPxWithSize(effectFilterArea.Width()));
    effectFeArea.SetHeight(height_.ConvertToPxWithSize(effectFilterArea.Height()));
    effectFilterArea_ = effectFilterArea.IntersectRect(effectFeArea);
    OnAsImageFilter(imageFilter, srcColor, currentColor, resultHash);
    currentColor = srcColor;
}

void SvgFe::ConverImageFilterColor(std::shared_ptr<RSImageFilter>& imageFilter, const ColorInterpolationType& srcColor,
    const ColorInterpolationType& dst)
{
    if (dst == ColorInterpolationType::LINEAR_RGB && srcColor == ColorInterpolationType::SRGB) {
        auto colorFilter = RSRecordingColorFilter::CreateSrgbGammaToLinear();
        CHECK_NULL_VOID(colorFilter);
        imageFilter = RSRecordingImageFilter::CreateColorFilterImageFilter(*colorFilter, imageFilter);
    } else if (dst == ColorInterpolationType::SRGB && srcColor == ColorInterpolationType::LINEAR_RGB) {
        auto colorFilter = RSRecordingColorFilter::CreateLinearToSrgbGamma();
        CHECK_NULL_VOID(colorFilter);
        imageFilter = RSRecordingImageFilter::CreateColorFilterImageFilter(*colorFilter, imageFilter);
    }
}

std::shared_ptr<RSImageFilter> SvgFe::MakeImageFilter(const FeIn& in, std::shared_ptr<RSImageFilter>& imageFilter,
    std::unordered_map<std::string, std::shared_ptr<RSImageFilter>>& resultHash)
{
    switch (in.in) {
        case FeInType::SOURCE_GRAPHIC:
            return nullptr;
        case FeInType::SOURCE_ALPHA: {
            RSColorMatrix m;
            m.SetScale(0, 0, 0, 1.0f);
            auto colorFilter = RSRecordingColorFilter::CreateMatrixColorFilter(m);
            CHECK_NULL_RETURN(colorFilter, nullptr);
            return RSRecordingImageFilter::CreateColorFilterImageFilter(*colorFilter, nullptr);
        }
        case FeInType::BACKGROUND_IMAGE:
            break;
        case FeInType::BACKGROUND_ALPHA:
            break;
        case FeInType::FILL_PAINT:
            break;
        case FeInType::STROKE_PAINT:
            break;
        case FeInType::PRIMITIVE:
            if (!in.id.empty()) {
                auto it = resultHash.find(in.id);
                if (it != resultHash.end()) {
                    return it->second;
                }
            }
            break;
        default:
            break;
    }
    return imageFilter;
}

} // namespace OHOS::Ace::NG
