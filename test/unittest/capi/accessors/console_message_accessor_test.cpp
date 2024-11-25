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

#include "gmock/gmock.h"

#include "accessor_test_base.h"
#include "node_api.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "core/interfaces/native/implementation/console_message_peer_impl.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
std::string g_message = "message";
std::string g_sourceId = "sourceId";
int g_lineNumber = 354;
} // namespace

class ConsoleMessageAccessorTest : public AccessorTestCtorBase<GENERATED_ArkUIConsoleMessageAccessor,
    &GENERATED_ArkUIAccessors::getConsoleMessageAccessor, ConsoleMessagePeer> {
public:
    ConsoleMessagePeer* CreatePeerInstance() override
    {
        Ark_String arkMessage = Converter::ArkValue<Ark_String>(g_message);
        Ark_String arkSourceId = Converter::ArkValue<Ark_String>(g_sourceId);
        Ark_Number arkLineNumber = Converter::ArkValue<Ark_Number>(g_lineNumber);
        return accessor_->ctor(&arkMessage, &arkSourceId, &arkLineNumber, ARK_MESSAGE_LEVEL_INFO);
    }
};

/**
 * @tc.name: DISABLED_getMessageTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ConsoleMessageAccessorTest, DISABLED_getMessageTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getMessage, nullptr);

    // should return value
    accessor_->getMessage(peer_);
}

/**
 * @tc.name: DISABLED_getSourceIdTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ConsoleMessageAccessorTest, DISABLED_getSourceIdTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getSourceId, nullptr);

    // should return value
    accessor_->getSourceId(peer_);
}

/**
 * @tc.name: DISABLED_getMessageLevelTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ConsoleMessageAccessorTest, DISABLED_getMessageLevelTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getMessageLevel, nullptr);

    // should return value
    accessor_->getMessageLevel(peer_);
}

/**
 * @tc.name: getLineNumberTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ConsoleMessageAccessorTest, getLineNumberTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getLineNumber, nullptr);
    EXPECT_EQ(g_lineNumber, accessor_->getLineNumber(peer_));
}

} // namespace OHOS::Ace::NG
