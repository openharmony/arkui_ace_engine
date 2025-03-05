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

#include "gtest/gtest.h"

#include "interfaces/inner_api/ace_kit/src/view/frame_node_impl.h"
#include "test/unittest/interfaces/ace_kit/mock/mock_ace_kit_pattern.h"
#include "ui/view_factory/abstract_view_factory.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::Kit {
class ContentModifierTest : public testing::Test {};

/**
 * @tc.name: ContentModifierTest001
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ContentModifierTest, ContentModifierTest001, TestSize.Level1)
{
    const std::string tag = "TEST1";
    const int32_t id = 1;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, id, mockPattern);
    EXPECT_NE(frameNode, nullptr);
    auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(frameNode);
    ASSERT_TRUE(frameNodeImpl);

    auto paintMethod = mockPattern->CreateNodePaintMethod();
    ASSERT_TRUE(paintMethod);
    auto contentModifier = paintMethod->GetContentModifier();
    ASSERT_TRUE(contentModifier);
    auto rsModifier = contentModifier->GetRSModifier();
    EXPECT_FALSE(rsModifier);
    contentModifier->InitAdapter();
    EXPECT_TRUE(contentModifier->GetRSModifier());
}
} // namespace OHOS::Ace::Kit
