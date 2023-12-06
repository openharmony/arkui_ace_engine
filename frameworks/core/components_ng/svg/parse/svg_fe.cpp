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

    if (fe->GetIn() == FeInType::SOURCE_GRAPHIC) {
        currentColor = ColorInterpolationType::SRGB;
    } else {
        currentColor = fe->GetColorInterpolationType();
    }
}

SvgFe::SvgFe() : SvgNode()
{
    InitNoneFlag();
}

#ifndef USE_ROSEN_DRAWING
void SvgFe::GetImageFilter(sk_sp<SkImageFilter>& imageFilter, ColorInterpolationType& currentColor)
#else
void SvgFe::GetImageFilter(std::shared_ptr<RSImageFilter>& imageFilter, ColorInterpolationType& currentColor)
#endif
{
    ColorInterpolationType srcColor = currentColor;
    InitFilterColor(AceType::DynamicCast<SvgFeDeclaration>(declaration_), currentColor);
    OnAsImageFilter(imageFilter, srcColor, currentColor);
    currentColor = srcColor;
}

#ifndef USE_ROSEN_DRAWING
void SvgFe::ConverImageFilterColor(
    sk_sp<SkImageFilter>& imageFilter, const ColorInterpolationType& srcColor, const ColorInterpolationType& dst)
{
    if (dst == ColorInterpolationType::LINEAR_RGB && srcColor == ColorInterpolationType::SRGB) {
        imageFilter = SkImageFilters::ColorFilter(SkColorFilters::SRGBToLinearGamma(), imageFilter);

    } else if (dst == ColorInterpolationType::SRGB && srcColor == ColorInterpolationType::LINEAR_RGB) {
        imageFilter = SkImageFilters::ColorFilter(SkColorFilters::LinearToSRGBGamma(), imageFilter);
    }
}
#else
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
#endif

#ifndef USE_ROSEN_DRAWING
sk_sp<SkImageFilter> SvgFe::MakeImageFilter(const FeInType& in, sk_sp<SkImageFilter>& imageFilter)
#else
std::shared_ptr<RSImageFilter> SvgFe::MakeImageFilter(const FeInType& in, std::shared_ptr<RSImageFilter>& imageFilter)
#endif
{
    switch (in) {
        case FeInType::SOURCE_GRAPHIC:
            return nullptr;
        case FeInType::SOURCE_ALPHA: {
#ifndef USE_ROSEN_DRAWING
            SkColorMatrix m;
            m.setScale(0, 0, 0, 1.0f);

            return SkImageFilters::ColorFilter(SkColorFilters::Matrix(m), nullptr);

#else
            RSColorMatrix m;
            m.SetScale(0, 0, 0, 1.0f);
            auto colorFilter = RSRecordingColorFilter::CreateMatrixColorFilter(m);
            CHECK_NULL_RETURN(colorFilter, nullptr);
            return RSRecordingImageFilter::CreateColorFilterImageFilter(*colorFilter, nullptr);
#endif
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
            break;
        default:
            break;
    }
    return imageFilter;
}

} // namespace OHOS::Ace::NG
