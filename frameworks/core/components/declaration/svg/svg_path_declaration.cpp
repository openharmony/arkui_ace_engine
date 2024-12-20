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

#include "core/components/declaration/svg/svg_path_declaration.h"

#include "core/components/declaration/common/declaration_constants.h"

namespace OHOS::Ace {

using namespace Framework;

void SvgPathDeclaration::InitSpecialized()
{
    AddSpecializedAttribute(DeclarationConstants::DEFAULT_SVG_PATH_ATTR);
}

void SvgPathDeclaration::InitializeStyle()
{
    // self attribute must be initialized first. Otherwise, may be initialized as a base attribute.
    MaybeResetAttribute<SvgPathAttribute>(AttributeTag::SPECIALIZED_ATTR);
}

bool SvgPathDeclaration::SetSpecializedAttr(const std::pair<std::string, std::string>& attr)
{
    return SetSpecializedValue(attr);
}

bool SvgPathDeclaration::SetSpecializedStyle(const std::pair<std::string, std::string>& style)
{
    return SetSpecializedValue(style);
}

bool SvgPathDeclaration::SetSpecializedValue(const std::pair<std::string, std::string>& attr)
{
    if (attr.first == DOM_SVG_D) {
        SetD(attr.second);
        return true;
    }
    return SetPresentationAttr(attr);
}

} // namespace OHOS::Ace