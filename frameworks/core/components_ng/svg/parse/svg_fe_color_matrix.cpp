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

#include "frameworks/core/components_ng/svg/parse/svg_fe_color_matrix.h"

#include "securec.h"
#ifndef NEW_SKIA
#include "include/effects/SkColorFilterImageFilter.h"
#else
#include "include/core/SkColorFilter.h"
#include "third_party/skia/include/effects/SkImageFilters.h"
#endif
#include "base/utils/utils.h"
#include "frameworks/core/components/declaration/svg/svg_fe_colormatrix_declaration.h"

namespace OHOS::Ace::NG {

RefPtr<SvgNode> SvgFeColorMatrix::Create()
{
    return AceType::MakeRefPtr<SvgFeColorMatrix>();
}

SvgFeColorMatrix::SvgFeColorMatrix() : SvgFe()
{
    declaration_ = AceType::MakeRefPtr<SvgFeColorMatrixDeclaration>();
    declaration_->Init();
    declaration_->InitializeStyle();
}

void SvgFeColorMatrix::OnInitStyle()
{
    auto declaration = AceType::DynamicCast<SvgFeColorMatrixDeclaration>(declaration_);
    CHECK_NULL_VOID_NOLOG(declaration);
    auto value = declaration->GetValues();
    if (memset_s(matrix_, sizeof(matrix_), 0, sizeof(matrix_)) != EOK) {
        return;
    }
    std::vector<float> matrix;
    StringUtils::StringSplitter(value, ' ', matrix);
    if (matrix.empty()) {
        StringUtils::StringSplitter(value, ',', matrix);
    }
    for (int i = 0; i < int(sizeof(matrix_) / sizeof(float)) && i < (int)matrix.size(); i++) {
#ifdef USE_SYSTEM_SKIA
        // phone skia is range 0.0 and 255.0
        matrix_[i] = matrix[i] * 255;
#else
        // tv skia is range 0.0 and 1.0
        matrix_[i] = matrix[i];
#endif
    }
}

#ifndef USE_ROSEN_DRAWING
void SvgFeColorMatrix::OnAsImageFilter(sk_sp<SkImageFilter>& imageFilter, const ColorInterpolationType& srcColor,
    ColorInterpolationType& currentColor) const
#else
void SvgFeColorMatrix::OnAsImageFilter(std::shared_ptr<RSImageFilter>& imageFilter,
    const ColorInterpolationType& srcColor, ColorInterpolationType& currentColor) const
#endif
{
    auto declaration = AceType::DynamicCast<SvgFeColorMatrixDeclaration>(declaration_);
    CHECK_NULL_VOID_NOLOG(declaration);
    imageFilter = MakeImageFilter(declaration->GetIn(), imageFilter);

#ifndef USE_ROSEN_DRAWING
#ifdef USE_SYSTEM_SKIA
    auto colorFilter = SkColorFilter::MakeMatrixFilterRowMajor255(matrix_);
#else
    auto colorFilter = SkColorFilters::Matrix(matrix_);
#endif

#ifndef NEW_SKIA
    imageFilter = SkColorFilterImageFilter::Make(colorFilter, imageFilter);
#else
    imageFilter = SkImageFilters::ColorFilter(colorFilter, imageFilter);
#endif
#else
    RSColorMatrix colorMatrix;
    colorMatrix.SetArray(matrix_);
    auto colorFilter = RSRecordingColorFilter::CreateMatrixColorFilter(colorMatrix);
    CHECK_NULL_VOID_NOLOG(colorFilter);

    imageFilter = RSRecordingImageFilter::CreateColorFilterImageFilter(*colorFilter, imageFilter);
#endif
    ConverImageFilterColor(imageFilter, srcColor, currentColor);
}

} // namespace OHOS::Ace::NG
