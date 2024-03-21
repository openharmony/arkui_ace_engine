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

#include "gtest/gtest.h"
#include "test/unittest/core/pattern/test_ng.h"

#define protected public
#define private public
#include "test/unittest/core/pattern/scrollable/mock_scrollable.h"

#include "frameworks/core/components_ng/base/frame_node.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class ScrollableEventTest : public TestNG {
public:
    void SetUp() override;
    void TearDown() override;

private:
    RefPtr<FrameNode> node_;
    RefPtr<FullyMockedScrollable> pattern_;
};

void ScrollableEventTest::SetUp()
{
    pattern_ = AceType::MakeRefPtr<FullyMockedScrollable>();
    node_ = FrameNode::CreateFrameNode("scroll", -1, pattern_);
    pattern_->SetEdgeEffect();
    pattern_->AddScrollEvent();
}

void ScrollableEventTest::TearDown()
{
    node_.Reset();
    pattern_.Reset();
}

/**
 * @tc.name: OnScrollEnd001
 * @tc.desc: Test HandleOverScroll -> ProcessSpringEffect -> OnScrollEnd
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableEventTest, OnScrollEnd001, TestSize.Level1)
{
    EXPECT_CALL(*pattern_, OnScrollEndCallback).Times(1);
    EXPECT_CALL(*pattern_, OutBoundaryCallback).Times(1).WillOnce(Return(false));

    pattern_->edgeEffect_ = EdgeEffect::SPRING;
    pattern_->SetEdgeEffect(EdgeEffect::SPRING);
    pattern_->SetCanOverScroll(false);

    EXPECT_TRUE(pattern_->HandleOverScroll(5.0f));
}
} // namespace OHOS::Ace::NG
