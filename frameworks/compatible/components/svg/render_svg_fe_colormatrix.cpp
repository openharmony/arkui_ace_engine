/*
 * Copyright (c) 2021-2025 Huawei Device Co., Ltd.
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

#include "frameworks/compatible/components/svg/render_svg_fe_colormatrix.h"

#include <algorithm>

#include "frameworks/compatible/components/svg/svg_fe_colormatrix_component.h"

namespace OHOS::Ace {

void RenderSvgFeColorMatrix::Update(const RefPtr<Component>& component)
{
    const RefPtr<SvgFeColorMatrixComponent> feComponent = AceType::DynamicCast<SvgFeColorMatrixComponent>(component);
    if (!feComponent) {
        LOGW("line component is null");
        return;
    }

    auto& declaration = feComponent->GetDeclaration();
    if (declaration) {
        values_ = declaration->GetValues();
        std::fill(std::begin(matrix_), std::end(matrix_), 0.0f);
        std::vector<float> matrix;
        StringUtils::StringSplitter(values_, ' ', matrix);
        if (matrix.empty()) {
            StringUtils::StringSplitter(values_, ',', matrix);
        }
        for (int i = 0; i < int(sizeof(matrix_) / sizeof(float)) && i < (int)matrix.size(); i++) {
            // tv skia is range 0.0 and 1.0
            matrix_[i] = matrix[i];
        }
        SetFeCommonAttrs(declaration);
    }
}

} // namespace OHOS::Ace
