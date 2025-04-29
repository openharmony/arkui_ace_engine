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

#include "core/interfaces/native/implementation/draw_modifier_peer_impl.h"

#include "accessor_test_base.h"
#include "core/components_ng/base/frame_node.h"

#include "gmock/gmock.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
class MockFrameNode : public FrameNode {
public:
    MockFrameNode() : FrameNode("TEST", 0, AceType::MakeRefPtr<Pattern>()) {}

    MOCK_METHOD(void, MarkDirtyNode, (PropertyChangeFlag));
};
} // namespace

class DrawModifierTest : public AccessorTestBase<GENERATED_ArkUIDrawModifierAccessor,
    &GENERATED_ArkUIAccessors::getDrawModifierAccessor, DrawModifierPeer> {
};

/**
 * @tc.name: invalidateTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DrawModifierTest, invalidateTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->invalidate, nullptr);
    const auto mockNode = AceType::MakeRefPtr<MockFrameNode>();
    ASSERT_NE(mockNode, nullptr);
    peer_->frameNode = mockNode;

    EXPECT_CALL(*mockNode, MarkDirtyNode(PROPERTY_UPDATE_RENDER)).Times(1);
    accessor_->invalidate(peer_);

    const auto extension = AceType::MakeRefPtr<ExtensionHandler>();
    auto wasInvalidate = false;
    extension->SetInvalidateRenderImpl([&wasInvalidate]() {
        wasInvalidate = true;
    });
    mockNode->SetExtensionHandler(extension);
    EXPECT_CALL(*mockNode, MarkDirtyNode(_)).Times(0);
    accessor_->invalidate(peer_);
    EXPECT_TRUE(wasInvalidate);
}
} // namespace OHOS::Ace::NG
