/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "ui/view/components/text.h"

#include "interfaces/inner_api/ace_kit/src/view/frame_node_impl.h"
#include "ui/base/referenced.h"
#include "ui/view_stack/view_stack_processor.h"

#include "core/components_ng/pattern/text/text_model_ng.h"

namespace OHOS::Ace::Kit {

Text::Text(const std::u16string& content)
{
    int32_t nodeId = Ace::Kit::ViewStackProcessor::ClaimNodeId();
    auto aceNode = NG::TextModelNG::CreateFrameNode(nodeId, content);
    node_ = AceType::MakeRefPtr<FrameNodeImpl>(aceNode);
}

Text::~Text() = default;

RefPtr<Text> Text::Create(const std::u16string& content)
{
    return Referenced::MakeRefPtr<Text>(content);
}

void Text::SetTextColor(const Color& value)
{
    NG::TextModelNG::SetTextColor(reinterpret_cast<AceNode*>(node_->GetHandle()), value);
}

void Text::SetFontSize(const Dimension& value)
{
    NG::TextModelNG::SetFontSize(reinterpret_cast<AceNode*>(node_->GetHandle()), value);
}

} // namespace OHOS::Ace::Kit
