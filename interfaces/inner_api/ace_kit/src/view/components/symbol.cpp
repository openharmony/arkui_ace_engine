/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "ui/view/components/symbol.h"

#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "ui/base/referenced.h"
#include "ui/view_stack/view_stack_processor.h"
#include "view/frame_node_impl.h"

namespace OHOS::Ace::Kit {

RefPtr<Symbol> Symbol::Create(RefPtr<FrameNode>& node)
{
    return Referenced::MakeRefPtr<Symbol>(node);
}

Symbol::Symbol(RefPtr<FrameNode>& node)
{
    node_ = node;
}

void Symbol::SetIsFontColorResource(bool flag)
{
    CHECK_NULL_VOID(node_);
    auto frameNode = reinterpret_cast<AceNode*>(node_->GetHandle());
    CHECK_NULL_VOID(frameNode);
    auto property = frameNode->GetLayoutProperty<NG::TextLayoutProperty>();
    CHECK_NULL_VOID(property);
    property->UpdateIsFontColorResource(flag);
}

std::vector<Color> Symbol::GetSymbolFontColor()
{
    CHECK_NULL_RETURN(node_, std::vector<Color>());
    auto frameNode = reinterpret_cast<AceNode*>(node_->GetHandle());
    CHECK_NULL_RETURN(frameNode, std::vector<Color>());
    auto property = frameNode->GetLayoutProperty<NG::TextLayoutProperty>();
    CHECK_NULL_RETURN(property, std::vector<Color>());
    return property->GetSymbolColorList().value_or(std::vector<Color>());
}

std::vector<RefPtr<ResourceObject>> Symbol::GetSymbolFontObjColor()
{
    CHECK_NULL_RETURN(node_, {});
    auto frameNode = reinterpret_cast<AceNode*>(node_->GetHandle());
    CHECK_NULL_RETURN(frameNode, {});
    auto property = frameNode->GetLayoutProperty<NG::TextLayoutProperty>();
    CHECK_NULL_RETURN(property, {});
    return property->GetFontColorResource().value_or(std::vector<RefPtr<ResourceObject>>());
}
} // namespace OHOS::Ace::Kit
