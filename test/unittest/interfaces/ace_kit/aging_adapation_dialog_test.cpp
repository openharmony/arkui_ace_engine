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
#include "ui/base/agingadapation/aging_adapation_dialog_util.h"
#include "ui/view_factory/abstract_view_factory.h"
#include "test/unittest/interfaces/ace_kit/mock/mock_ace_kit_pattern.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Kit;
namespace OHOS::Ace {
class AgingAdapationDialogTest : public testing::Test {};
/**
 * @tc.name: AgingAdapationDialogTest001
 * @tc.desc:
 * @tc.type: Func
 */
HWTEST_F(AgingAdapationDialogTest, AgingAdapationDialogTest001, TestSize.Level1)
{
    const std::string tag = "TEST1";
    const int32_t id = 1;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, id, mockPattern);
    EXPECT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetId(), id);
    auto nodeTag = frameNode->GetTag();
    EXPECT_EQ(tag, nodeTag);
    auto agingNode = AgingAdapationDialogUtil::ShowLongPressDialog(tag, id, IconNodeType::TEXT);
    EXPECT_EQ(agingNode, nullptr);
}
}
