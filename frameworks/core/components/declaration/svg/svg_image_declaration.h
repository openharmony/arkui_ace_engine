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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DECLARATION_SVG_SVG_IMAGE_DECLARATION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DECLARATION_SVG_SVG_IMAGE_DECLARATION_H

#include "core/components/declaration/svg/svg_base_declaration.h"

namespace OHOS::Ace {

struct SvgImageAttribute : SvgBaseAttribute {
    Dimension x = Dimension(0, DimensionUnit::PX); // x-axis default value
    Dimension y = Dimension(0, DimensionUnit::PX); // y-axis default value
    Dimension width = Dimension(0.0, DimensionUnit::PX); // image width default value
    Dimension height = Dimension(0.0, DimensionUnit::PX); // image height default value
    std::string href = "";
};

class SvgImageDeclaration : public SvgBaseDeclaration {
    DECLARE_ACE_TYPE(SvgImageDeclaration, SvgBaseDeclaration);

public:
    SvgImageDeclaration() = default;
    ~SvgImageDeclaration() override = default;
    void InitializeStyle() override;
    bool SetSpecializedAttr(const std::pair<std::string, std::string>& attr) override;

    void SetX(const Dimension& x)
    {
        auto& attribute = MaybeResetAttribute<SvgImageAttribute>(AttributeTag::SPECIALIZED_ATTR);
        attribute.x = x;
    }

    const Dimension& GetX() const
    {
        auto& attribute = static_cast<SvgImageAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
        return attribute.x;
    }

    void SetY(const Dimension& y)
    {
        auto& attribute = MaybeResetAttribute<SvgImageAttribute>(AttributeTag::SPECIALIZED_ATTR);
        attribute.y = y;
    }

    const Dimension& GetY() const
    {
        auto& attribute = static_cast<SvgImageAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
        return attribute.y;
    }

    void SetHeight(const Dimension& height)
    {
        auto& attribute = MaybeResetAttribute<SvgImageAttribute>(AttributeTag::SPECIALIZED_ATTR);
        attribute.height = height;
    }

    const Dimension& GetHeight() const
    {
        auto& attribute = static_cast<SvgImageAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
        return attribute.height;
    }

    void SetWidth(const Dimension& width)
    {
        auto& attribute = MaybeResetAttribute<SvgImageAttribute>(AttributeTag::SPECIALIZED_ATTR);
        attribute.width = width;
    }

    const Dimension& GetWidth() const
    {
        auto& attribute = static_cast<SvgImageAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
        return attribute.width;
    }

    void SetHref(const std::string& href)
    {
        auto& attrs = MaybeResetAttribute<SvgImageAttribute>(AttributeTag::SPECIALIZED_ATTR);
        attrs.href = href;
    }

    const std::string& GetHref() const
    {
        auto& attribute = static_cast<SvgImageAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
        return attribute.href;
    }

protected:
    void InitSpecialized() override;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DECLARATION_SVG_SVG_IMAGE_DECLARATION_H
