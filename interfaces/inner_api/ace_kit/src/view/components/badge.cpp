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

#include "interfaces/inner_api/ace_kit/include/ui/view/components/badge.h"

#include "interfaces/inner_api/ace_kit/src/view/frame_node_impl.h"
#include "interfaces/inner_api/ace_kit/src/view/extend/badge/badge_extend_pattern.h"
#include "ui/base/referenced.h"
#include "ui/view/extend/badge/badge_pattern.h"
#include "ui/view_stack/view_stack_processor.h"

#include "core/components_ng/pattern/badge/badge_model_ng.h"

namespace OHOS::Ace::Kit {

Badge::Badge()
{
    int32_t nodeId = Ace::Kit::ViewStackProcessor::ClaimNodeId();
    auto aceNode = NG::BadgeModelNG::CreateFrameNode(nodeId);
    node_ = AceType::MakeRefPtr<FrameNodeImpl>(aceNode);
}

Badge::Badge(const std::string& tag, const RefPtr<BadgePattern>& pattern)
{
    int32_t nodeId = Ace::Kit::ViewStackProcessor::ClaimNodeId();
    auto aceFrameNode = NG::FrameNode::GetOrCreateFrameNode(
        tag, nodeId, [pattern]() { return AceType::MakeRefPtr<BadgeExtendPattern>(pattern); });
    auto frameNode = AceType::MakeRefPtr<FrameNodeImpl>(aceFrameNode, pattern);
    aceFrameNode->SetKitNode(frameNode);
    frameNode->InitializePatternAndContext();
    pattern->SetHost(frameNode);
    node_ = frameNode;
}

Badge::~Badge() = default;

RefPtr<Badge> Badge::Create()
{
    return Referenced::MakeRefPtr<Badge>();
}

RefPtr<Badge> Badge::CreateCustom(const std::string& tag, const RefPtr<BadgePattern>& pattern)
{
    return Referenced::MakeRefPtr<Badge>(tag, pattern);
}


void Badge::SetBadgeParam(BadgeParameters& params, bool isDefaultFontSize, bool isDefaultBadgeSize)
{
    NG::BadgeModelNG::SetBadgeParam(
        reinterpret_cast<AceNode*>(node_->GetHandle()), params, isDefaultFontSize, isDefaultBadgeSize);
}

} // namespace OHOS::Ace::Kit
