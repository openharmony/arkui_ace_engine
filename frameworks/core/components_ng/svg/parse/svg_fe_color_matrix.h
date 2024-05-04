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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_FE_COLOR_MATRIX_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_FE_COLOR_MATRIX_H

#include "frameworks/core/components_ng/svg/parse/svg_fe.h"

namespace OHOS::Ace::NG {

class SvgFeColorMatrix : public SvgFe {
    DECLARE_ACE_TYPE(SvgFeColorMatrix, SvgFe);

public:
    SvgFeColorMatrix();
    ~SvgFeColorMatrix() override = default;
    static RefPtr<SvgNode> Create();

    void MakeMatrix(const std::string& values);
    void MakeSaturate(const std::string& values);
    void MakeHueRotate(const std::string& values);
    void MakeLuminanceToAlpha();

    void OnInitStyle() override;

#ifndef USE_ROSEN_DRAWING
    void OnAsImageFilter(sk_sp<SkImageFilter>& imageFilter,
        const ColorInterpolationType& srcColor, ColorInterpolationType& currentColor) const override;
#else
    void OnAsImageFilter(std::shared_ptr<RSImageFilter>& imageFilter,
        const SvgColorInterpolationType& srcColor, SvgColorInterpolationType& currentColor,
        std::unordered_map<std::string, std::shared_ptr<RSImageFilter>>& resultHash) const override;
#endif

    bool ParseAndSetSpecializedAttr(const std::string& name, const std::string& value) override;

private:
    // default matrix, don't change the RGBA in origin image
    std::vector<float> matrix_ = {
        1, 0, 0, 0, 0,
        0, 1, 0, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 0, 1, 0
    }; // 5 * 4 matrix
    SvgFeColorMatrixAttribute matrixAttr_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_FE_COLOR_MATRIX_H
