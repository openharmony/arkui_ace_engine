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

#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/pattern/linear_layout/column_model_ng.h"
#include "frameworks/core/components_ng/syntax/arkoala_lazy_node.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class TestUINode : public UINode {
    DECLARE_ACE_TYPE(TestUINode, UINode);

    static RefPtr<TestUINode> CreateTestUINode(int32_t nodeId)
    {
        return MakeRefPtr<TestUINode>(nodeId);
    }

    bool IsAtomicNode() const override
    {
        return true;
    }

    explicit TestUINode(int32_t nodeId) : UINode("TestUINode", nodeId) {}

    ~TestUINode() override = default;
};

class ArkoalaLazyNodeTest : public TestNG {
public:
    std::string DumpUINode(const RefPtr<UINode>& node) const
    {
        return (node == nullptr) ? "null" : node->GetTag() + "(" + std::to_string(node->GetId()) + ")";
    }

    int32_t GetNextId()
    {
        return ++nodeId_;
    }

    int32_t nodeId_ = 0;
};

const int32_t INDEX_1 = 1;
const int32_t INDEX_2 = 2;
const int32_t INDEX_8 = 8;
const int32_t INDEX_9 = 9;
const int32_t TOTAL_COUNT = 10;
const int32_t SCROLLER_CACHED_COUNT = 2;

TEST_F(ArkoalaLazyNodeTest, ArkoalaLazyNodeTest001)
{
    auto lazyNode = AceType::MakeRefPtr<ArkoalaLazyNode>(GetNextId());
    EXPECT_EQ(lazyNode->GetTag(), V2::JS_LAZY_FOR_EACH_ETS_TAG);
    lazyNode->SetCallbacks([](int32_t idx) { return ColumnModelNG::CreateFrameNode(-1); },
        [](int32_t start, int32_t end) {
            EXPECT_EQ(start, INDEX_8);
            EXPECT_EQ(end, INDEX_8);
        });
    lazyNode->SetTotalCount(TOTAL_COUNT);
    EXPECT_EQ(lazyNode->FrameCount(), TOTAL_COUNT);

    EXPECT_FALSE(lazyNode->GetChildByIndex(INDEX_9));
    EXPECT_FALSE(lazyNode->GetFrameChildByIndex(INDEX_9, false, false, false));
    RefPtr<UINode> childNode = lazyNode->GetFrameChildByIndex(INDEX_9, true, false, true);
    EXPECT_TRUE(childNode);
    EXPECT_TRUE(lazyNode->GetChildByIndex(INDEX_9));
    EXPECT_TRUE(AceType::DynamicCast<FrameNode>(childNode)->IsActive());

    childNode = lazyNode->GetFrameChildByIndex(INDEX_8, true, false, true);
    EXPECT_TRUE(childNode);
    lazyNode->DoSetActiveChildRange(INDEX_8, INDEX_8, 0, 0, false);
    EXPECT_FALSE(lazyNode->GetChildByIndex(INDEX_9));
    EXPECT_TRUE(AceType::DynamicCast<FrameNode>(childNode)->IsActive());
}

TEST_F(ArkoalaLazyNodeTest, ArkoalaLazyNodeTest002)
{
    auto lazyNode = AceType::MakeRefPtr<ArkoalaLazyNode>(GetNextId());
    ArkoalaLazyNode::CreateItemCb createItemCb = [this](int32_t idx) {
        RefPtr<TestUINode> uiNode = TestUINode::CreateTestUINode(GetNextId());
        auto columnNode = ColumnModelNG::CreateFrameNode(GetNextId());
        uiNode->AddChild(columnNode);
        EXPECT_EQ(uiNode->GetChildren().size(), 1);
        return uiNode;
    };
    ArkoalaLazyNode::UpdateRangeCb updateRangeCb = [](int32_t start, int32_t end) {};
    lazyNode->SetCallbacks(createItemCb, updateRangeCb);

    lazyNode->SetTotalCount(TOTAL_COUNT);
    RefPtr<UINode> childNode = lazyNode->GetFrameChildByIndex(INDEX_1, true, false, true);
    EXPECT_TRUE(childNode);
    EXPECT_TRUE(AceType::DynamicCast<FrameNode>(childNode)->IsActive());
    EXPECT_FALSE(lazyNode->GetChildByIndex(INDEX_2));
    childNode = lazyNode->GetFrameChildByIndex(INDEX_2, true, true, false);
    EXPECT_TRUE(childNode);
    lazyNode->DoSetActiveChildRange(INDEX_1, INDEX_1, SCROLLER_CACHED_COUNT, SCROLLER_CACHED_COUNT, false);
    EXPECT_FALSE(AceType::DynamicCast<FrameNode>(childNode)->IsActive());
}

TEST_F(ArkoalaLazyNodeTest, ArkoalaLazyNodeTest003)
{
    auto lazyNode = AceType::MakeRefPtr<ArkoalaLazyNode>(GetNextId());
    ArkoalaLazyNode::CreateItemCb createItemCb = [this](int32_t idx) {
        return ColumnModelNG::CreateFrameNode(GetNextId());
    };
    ArkoalaLazyNode::UpdateRangeCb updateRangeCb = [](int32_t start, int32_t end) {};
    lazyNode->SetCallbacks(createItemCb, updateRangeCb);
    lazyNode->SetTotalCount(TOTAL_COUNT);

    EXPECT_TRUE(lazyNode->GetFrameChildByIndex(INDEX_1, true, false, true));
    EXPECT_TRUE(lazyNode->GetFrameNode(INDEX_1));
}
} // namespace OHOS::Ace::NG