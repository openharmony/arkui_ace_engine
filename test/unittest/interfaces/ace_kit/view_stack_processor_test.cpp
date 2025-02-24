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

#include "ui/view_stack/view_stack_processor.h"

#include "gtest/gtest.h"
#include "test/unittest/interfaces/ace_kit/mock/mock_ace_kit_pattern.h"
#include "ui/view_factory/abstract_view_factory.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Kit;
namespace OHOS::Ace::Kit {
class ViewStackProcessorTest : public testing::Test {};

/**
 * @tc.name: ViewStackProcessorTest001
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ViewStackProcessorTest, ViewStackProcessorTest001, TestSize.Level1)
{
    const std::string tag = "TEST";
    auto framenode = AbstractViewFactory::CreateFrameNode(tag, 0, AceType::MakeRefPtr<MockAceKitPattern>());
    EXPECT_NE(framenode, nullptr);
    ViewStackProcessor::Push(framenode);
    auto topNode = ViewStackProcessor::GetTopNode();
    EXPECT_EQ(topNode, framenode);
}
} // namespace OHOS::Ace::Kit
