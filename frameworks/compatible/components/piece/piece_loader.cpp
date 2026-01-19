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

#include "compatible/components/piece/piece_loader.h"

#include "compatible/components/piece/piece_declaration.h"
#include "compatible/components/piece/dom_piece.h"

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "bridge/common/dom/dom_configs.h"

#include "compatible/components/piece/piece_modifier_compatible.h"

namespace OHOS::Ace {

namespace PieceModifier {
const ArkUIPieceModifierCompatible* GetPieceModifier();
}

RefPtr<Framework::DOMNode> PieceLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMPiece>(nodeId, nodeName);
}

void* PieceLoader::CreateModel()
{
    return nullptr;
}

RefPtr<V2::InspectorComposedElement> PieceLoader::CreateInspectorElement(const std::string& id)
{
    return nullptr;
}

RefPtr<Declaration> PieceLoader::CreateDeclaration()
{
    return AceType::MakeRefPtr<PieceDeclaration>();
}

const void* PieceLoader::GetModifier()
{
    return PieceModifier::GetPieceModifier();
}

} // namespace OHOS::Ace