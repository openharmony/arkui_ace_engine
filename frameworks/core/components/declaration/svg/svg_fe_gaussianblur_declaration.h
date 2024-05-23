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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DECLARATION_SVG_SVG_FE_GAUSSIANBLUR_DECLARATION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DECLARATION_SVG_SVG_FE_GAUSSIANBLUR_DECLARATION_H

#include <vector>

#include "base/utils/utils.h"
#include "core/components/declaration/svg/svg_fe_declaration.h"

namespace OHOS::Ace {
enum class FeEdgeMode {
    EDGE_DUPLICATE,
    EDGE_WRAP,
    EDGE_NONE
};

struct SvgFeGaussianBlurAttribute : SvgFeAttribute {
    double stdDeviationX = 0.0;
    double stdDeviationY = 0.0;
    FeEdgeMode edgeMode = FeEdgeMode::EDGE_DUPLICATE;
};

class SvgFeGaussianBlurDeclaration : public SvgFeDeclaration {
    DECLARE_ACE_TYPE(SvgFeGaussianBlurDeclaration, SvgFeDeclaration);

public:
    SvgFeGaussianBlurDeclaration() = default;
    ~SvgFeGaussianBlurDeclaration() override = default;
    void InitializeStyle() override;

    void SetStdDeviation(const std::vector<float>& stdDeviation)
    {
        if (stdDeviation.empty() || stdDeviation.size() > 2) {
            return;
        }
        auto& attribute = MaybeResetAttribute<SvgFeGaussianBlurAttribute>(AttributeTag::SPECIALIZED_ATTR);
        attribute.stdDeviationX = stdDeviation[0];
        attribute.stdDeviationY = stdDeviation.size() > 1 ? stdDeviation[1] : stdDeviation[0];
    }

    void SetEdgeMode(const std::string& edgeMode)
    {
        static const LinearMapNode<FeEdgeMode> EDGE_MODE_TABLE[] = {
            { "duplicate", FeEdgeMode::EDGE_DUPLICATE },
            { "none", FeEdgeMode::EDGE_NONE },
            { "wrap", FeEdgeMode::EDGE_WRAP },
        };
        int64_t inIndex = BinarySearchFindIndex(EDGE_MODE_TABLE, ArraySize(EDGE_MODE_TABLE), edgeMode.c_str());
        if (inIndex != -1) {
            auto& attribute = MaybeResetAttribute<SvgFeGaussianBlurAttribute>(AttributeTag::SPECIALIZED_ATTR);
            attribute.edgeMode = EDGE_MODE_TABLE[inIndex].value;
        }
    }

    double GetStdDeviationX() const
    {
        auto& attribute = static_cast<SvgFeGaussianBlurAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
        return attribute.stdDeviationX;
    }

    double GetStdDeviationY() const
    {
        auto& attribute = static_cast<SvgFeGaussianBlurAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
        return attribute.stdDeviationY;
    }

    const FeEdgeMode& GetEdgeMode() const
    {
        auto& attribute = static_cast<SvgFeGaussianBlurAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
        return attribute.edgeMode;
    }

protected:
    void InitSpecialized() override;
    bool SetSpecializedValue(const std::pair<std::string, std::string>& attr) override;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DECLARATION_SVG_SVG_FE_GAUSSIANBLUR_DECLARATION_H
