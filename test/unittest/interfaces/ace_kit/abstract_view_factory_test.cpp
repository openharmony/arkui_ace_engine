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

#include "ui/view_factory/abstract_view_factory.h"
#include "test/unittest/interfaces/ace_kit/mock/mock_ace_kit_pattern.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Kit;
namespace OHOS::Ace {
class AbstractViewFactoryTest : public testing::Test {};

/**
 * @tc.name: AbstractViewFactoryTest001
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AbstractViewFactoryTest, AbstractViewFactoryTest001, TestSize.Level1)
{
    std::string tag = "ExtendNode";
    auto framenode = AbstractViewFactory::CreateFrameNode(tag, 0, AceType::MakeRefPtr<MockAceKitPattern>());
    EXPECT_NE(framenode, nullptr);
}
} // namespace OHOS::Ace
