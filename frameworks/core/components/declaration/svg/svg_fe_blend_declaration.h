/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DECLARATION_SVG_SVG_FE_BLEND_DECLARATION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DECLARATION_SVG_SVG_FE_BLEND_DECLARATION_H

#include "core/components/declaration/svg/svg_fe_declaration.h"

namespace OHOS::Ace {

enum class FeBlendMode {
    NORMAL,
    MULTIPLY,
    SCREEN,
    DARKEN,
    LIGHTEN
};

struct SvgFeBlendAttribute : SvgFeAttribute {
    FeIn in2;
    FeBlendMode blendMode = FeBlendMode::NORMAL;
};

class SvgFeBlendDeclaration : public SvgFeDeclaration {
    DECLARE_ACE_TYPE(SvgFeBlendDeclaration, SvgFeDeclaration);

public:
    SvgFeBlendDeclaration() = default;
    ~SvgFeBlendDeclaration() override = default;
    void InitializeStyle() override;

    void SetIn2(const std::string& In2)
    {
        static const LinearMapNode<FeInType> IN_TABLE[] = {
            { "BackgroundAlpha", FeInType::BACKGROUND_ALPHA },
            { "BackgroundImage", FeInType::BACKGROUND_IMAGE },
            { "FillPaint", FeInType::FILL_PAINT },
            { "SourceAlpha", FeInType::SOURCE_ALPHA },
            { "SourceGraphic", FeInType::SOURCE_GRAPHIC },
            { "StrokePaint", FeInType::STROKE_PAINT },
        };
        int64_t inIndex = BinarySearchFindIndex(IN_TABLE, ArraySize(IN_TABLE), In2.c_str());
        auto& attribute = MaybeResetAttribute<SvgFeBlendAttribute>(AttributeTag::SPECIALIZED_ATTR);
        if (inIndex != -1) {
            attribute.in2.in = IN_TABLE[inIndex].value;
        } else {
            attribute.in2.id = In2;
        }
    }

    void SetBlendMode(const std::string& blendMode)
    {
        static const LinearMapNode<FeBlendMode> EDGE_MODE_TABLE[] = {
            { "darken", FeBlendMode::DARKEN },
            { "lighten", FeBlendMode::LIGHTEN },
            { "multiply", FeBlendMode::MULTIPLY },
            { "normal", FeBlendMode::NORMAL },
            { "screen", FeBlendMode::SCREEN }
        };
        int64_t inIndex = BinarySearchFindIndex(EDGE_MODE_TABLE, ArraySize(EDGE_MODE_TABLE), blendMode.c_str());
        if (inIndex != -1) {
            auto& attribute = MaybeResetAttribute<SvgFeBlendAttribute>(AttributeTag::SPECIALIZED_ATTR);
            attribute.blendMode = EDGE_MODE_TABLE[inIndex].value;
        }
    }

    const FeBlendMode& GetBlendMode() const
    {
        auto& attribute = static_cast<SvgFeBlendAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
        return attribute.blendMode;
    }

    const FeIn& GetIn2() const
    {
        auto& attribute = static_cast<SvgFeBlendAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
        return attribute.in2;
    }

protected:
    void InitSpecialized() override;
    bool SetSpecializedValue(const std::pair<std::string, std::string>& attr) override;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DECLARATION_SVG_SVG_FE_BLEND_DECLARATION_H
