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

#include "core/components/declaration/svg/svg_rect_declaration.h"

#include "core/components/declaration/common/declaration_constants.h"

namespace OHOS::Ace {

using namespace Framework;

void SvgRectDeclaration::InitSpecialized()
{
    AddSpecializedAttribute(DeclarationConstants::DEFAULT_SVG_RECT_ATTR);
}

void SvgRectDeclaration::InitializeStyle()
{
    // self attribute must be initialized first. Otherwise, may be initialized as a base attribute.
    MaybeResetAttribute<SvgRectAttribute>(AttributeTag::SPECIALIZED_ATTR);
}

bool SvgRectDeclaration::SetSpecializedAttr(const std::pair<std::string, std::string>& attr)
{
    return SetSpecializedValue(attr);
}

bool SvgRectDeclaration::SetSpecializedStyle(const std::pair<std::string, std::string>& style)
{
    return SetSpecializedValue(style);
}

bool SvgRectDeclaration::SetSpecializedValue(const std::pair<std::string, std::string>& attr)
{
    static const LinearMapNode<void (*)(const std::string&, SvgRectDeclaration&)> attrs[] = {
        { DOM_SVG_HEIGHT,
            [](const std::string& val, SvgRectDeclaration& declaration) {
                declaration.SetHeight(declaration.ParseDimension(val));
            } },
        { DOM_SVG_RX,
            [](const std::string& val, SvgRectDeclaration& declaration) {
                declaration.SetRx(declaration.ParseDimension(val));
            } },
        { DOM_SVG_RY,
            [](const std::string& val, SvgRectDeclaration& declaration) {
                declaration.SetRy(declaration.ParseDimension(val));
            } },
        { DOM_SVG_WIDTH,
            [](const std::string& val, SvgRectDeclaration& declaration) {
                declaration.SetWidth(declaration.ParseDimension(val));
            } },
        { DOM_SVG_X,
            [](const std::string& val, SvgRectDeclaration& declaration) {
                declaration.SetX(declaration.ParseDimension(val));
            } },
        { DOM_SVG_Y,
            [](const std::string& val, SvgRectDeclaration& declaration) {
                declaration.SetY(declaration.ParseDimension(val));
            } },
    };
    auto attrIter = BinarySearchFindIndex(attrs, ArraySize(attrs), attr.first.c_str());
    if (attrIter != -1) {
        attrs[attrIter].value(attr.second, *this);
        return true;
    }
    return SetPresentationAttr(attr);
}

} // namespace OHOS::Ace