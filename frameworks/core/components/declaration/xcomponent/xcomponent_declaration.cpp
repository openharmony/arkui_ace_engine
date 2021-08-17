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

#include "core/components/declaration/xcomponent/xcomponent_declaration.h"

#include "base/utils/string_utils.h"
#include "core/components/declaration/common/declaration_constants.h"
#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace {
using namespace Framework;

void XComponentDeclaration::InitSpecialized()
{
    AddSpecializedAttribute(DeclarationConstants::DEFAULT_XCOMPONENT_ATTR);
}

bool XComponentDeclaration::SetSpecializedAttr(const std::pair<std::string, std::string>& attr)
{
    static const LinearMapNode<void (*)(XComponentDeclaration&, const std::string&)> xComponentAttrOperators[] = {
        { DOM_XCOMPONENT_NAME,
          [](XComponentDeclaration& declaration, const std::string& name) {
            declaration.SetXComponentName(name);
          }
        },
    };
    auto operatorIter = BinarySearchFindIndex(xComponentAttrOperators,
                                              ArraySize(xComponentAttrOperators),
                                              attr.first.c_str());
    if (operatorIter != -1) {
        xComponentAttrOperators[operatorIter].value(*this, attr.second);
        return true;
    }
    return false;
}
} // namespace OHOS::Ace
