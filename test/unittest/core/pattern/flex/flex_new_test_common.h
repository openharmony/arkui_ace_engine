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

#ifndef BASE_TEST_FLEX_NEW_TEST_COMMON_H
#define BASE_TEST_FLEX_NEW_TEST_COMMON_H

#include "flex_base_test_ng.h"

#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/blank/blank_pattern.h"
#include "core/components_ng/pattern/text/text_controller.h"
#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

namespace {
const int32_t FIRST_CHILD = 0;
const int32_t SECOND_CHILD = 1;
const float RK356_WIDTH = 720.0f;
const float RK356_HEIGHT = 1136.0f;
const SizeF CONTAINER_SIZE(RK356_WIDTH, RK356_HEIGHT);
const float ZERO = 0.0f;
const OffsetF OFFSET_TOP_LEFT = OffsetF(ZERO, ZERO);
} // namespace

class FlexNewTestNG : public FlexBaseTestNG {
public:
    RefPtr<FrameNode> CreateNormalFrameNode(const std::u16string& content, const std::string& tag)
    {
        auto* stack = ViewStackProcessor::GetInstance();
        auto nodeId = stack->ClaimNodeId();
        ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", tag.c_str(), nodeId);
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(tag, nodeId, []() { return AceType::MakeRefPtr<TextPattern>(); });
        stack->Push(frameNode);

        auto castTextLayoutProperty = frameNode->GetLayoutPropertyPtr<TextLayoutProperty>();
        castTextLayoutProperty->UpdateContent(content);

        auto textPattern = frameNode->GetPattern<TextPattern>();
        textPattern->SetTextController(AceType::MakeRefPtr<TextController>());
        textPattern->GetTextController()->SetPattern(WeakPtr(textPattern));
        textPattern->ClearSelectionMenu();

        RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
        ViewStackProcessor::GetInstance()->PopContainer();
        return AceType::DynamicCast<FrameNode>(element);
    }
};
}
#endif // BASE_TEST_FLEX_NEW_TEST_COMMON_H