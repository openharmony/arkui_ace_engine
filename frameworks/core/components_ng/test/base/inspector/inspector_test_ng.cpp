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

#include "gtest/gtest.h"

#define protected public
#define private public

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/inspector.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const RefPtr<FrameNode> ONE = FrameNode::CreateFrameNode("one", 1, AceType::MakeRefPtr<Pattern>(), true);
const RefPtr<FrameNode> TWO = FrameNode::CreateFrameNode("two", 2, AceType::MakeRefPtr<Pattern>());
const RefPtr<FrameNode> THREE = FrameNode::CreateFrameNode("three", 3, AceType::MakeRefPtr<Pattern>());
} // namespace
class InspectorTestNg : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
};

/**
 * @tc.name: InspectorTestNg001
 * @tc.desc: Test geometry node method
 * @tc.type: FUNC
 */
HWTEST_F(InspectorTestNg, InspectorTestNg001, TestSize.Level1)
{
    PipelineContext::GetCurrentContext()->rootNode_ = ONE;
    /**
     * @tc.steps: step1. GetInspectorTree
     * @tc.expected: step1. return substr(10, 4)="root"
     */
    auto strResult1 = Inspector::GetInspectorTree(false);
    EXPECT_EQ(strResult1.substr(10, 4), "root");
    /**
     * @tc.steps: step2. GetInspectorNodeByKey by key "one"
     * @tc.expected: step2. return ""
     */
    ONE->AddChild(TWO, 1, false);
    auto strResult2 = Inspector::GetInspectorNodeByKey("one");
    EXPECT_EQ(strResult2, "");
    /**
     * @tc.steps: step3. GetInspectorNodeByKey by key ""
     * @tc.expected: step3. return "one"
     */
    auto strResult3 = Inspector::GetInspectorNodeByKey("");
    EXPECT_EQ(strResult3.substr(10, 3), "one");
    /**
     * @tc.steps: step4. GetInspectorTree
     * @tc.expected: step4. return substr(10, 4)="root"
     */
    auto strResult4 = Inspector::GetInspectorTree(false);
    EXPECT_EQ(strResult4.substr(10, 4), "root");
    auto strResult5 = Inspector::GetInspectorTree(true);
    EXPECT_EQ(strResult5.substr(9, 4), "root");
}
} // namespace OHOS::Ace::NG