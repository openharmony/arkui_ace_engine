/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/swiper/swiper_group_node.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

RefPtr<SwiperGroupNode> SwiperGroupNode::GetOrCreateGroupNode(
    const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    auto frameNode = GetFrameNode(tag, nodeId);
    if (frameNode) {
        return AceType::DynamicCast<SwiperGroupNode>(frameNode);
    }
    auto pattern = patternCreator ? patternCreator() : MakeRefPtr<Pattern>();
    auto swiperGroupNode = AceType::MakeRefPtr<SwiperGroupNode>(tag, nodeId, pattern);
    swiperGroupNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(swiperGroupNode);
    return swiperGroupNode;
}

void SwiperGroupNode::AddChildToGroup(const RefPtr<UINode>& child)
{
    auto swiperNode = GetChildAtIndex(0);
    if (!swiperNode) {
        auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
        swiperNode = FrameNode::GetOrCreateFrameNode(
            V2::SWIPER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
        AddChild(swiperNode);
    }
    swiperNode->AddChild(child);
}

} // namespace OHOS::Ace::NG