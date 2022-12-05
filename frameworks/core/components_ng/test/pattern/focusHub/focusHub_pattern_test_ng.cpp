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
#define private public
#define protected public

#include <optional>

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_view.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string BUTTON_CREATE_VALUE = "Hello Button";
} // namespace

class FocusHubPatternTestNg : public testing::Test {
public:
};

/**
 * @tc.name: FocusHubTest001
 * @tc.desc: Test FocusHub function: GetFrameNode GetGeometryNode GetInspectorKey
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubPatternTestNg, FocusHubTest001, TestSize.Level1)
{
    ButtonView::CreateWithLabel(BUTTON_CREATE_VALUE);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_NE(element, nullptr);
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(frameNode, nullptr);

    RefPtr<FocusHub> focusHub = frameNode->GetOrCreateFocusHub();
    EXPECT_NE(focusHub, nullptr);
    EXPECT_EQ(focusHub->GetFrameNode(), frameNode);
    EXPECT_EQ(focusHub->GetGeometryNode(), frameNode->GetGeometryNode());
    EXPECT_EQ(focusHub->GetInspectorKey(), frameNode->GetInspectorId());
}
} // namespace OHOS::Ace::NG

