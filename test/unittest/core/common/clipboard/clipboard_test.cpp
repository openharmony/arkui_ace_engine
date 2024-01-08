/*
 * Copyright (c) 2023 iSoftStone Information Technology (Group) Co.,Ltd.
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
#include "mock_clip_board.h"

#include "base/utils/utils.h"
#include "core/common/clipboard/clipboard.h"
#include "core/common/clipboard/clipboard_interface.h"
#include "core/common/clipboard/clipboard_proxy.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
class ClipboardTest : public testing::Test {};

/**
 * @tc.name: CastToClipboardTestTest001
 * @tc.desc: Test cast to clipboard
 * @tc.type: FUNC
 */
HWTEST_F(ClipboardTest, CastToClipboardTestTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call GetInstance first.
     * @tc.expected: step1. The return value is not null.
     */
    ClipboardProxy* firstTestGetInstance = ClipboardProxy::GetInstance();
    ASSERT_NE(firstTestGetInstance, nullptr);

    /**
     * @tc.steps: step2. call GetInstance second.
     * @tc.expected: step2. The return value is same with firstTestGetInstance.
     */
    ClipboardProxy* secondTestGetInstance = ClipboardProxy::GetInstance();
    EXPECT_EQ(firstTestGetInstance, secondTestGetInstance);
}

/**
 * @tc.name: CastToClipboardTestTest001
 * @tc.desc: Test cast to clipboard
 * @tc.type: FUNC
 */
HWTEST_F(ClipboardTest, CastToClipboardTestTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set delegate to nullptr.
     * @tc.expected: step1. The return clipboard is null.
     */
    ClipboardProxy::GetInstance()->SetDelegate(nullptr);

    RefPtr<TaskExecutor> taskExecutor;
    RefPtr<Clipboard> clipboard = ClipboardProxy::GetInstance()->GetClipboard(taskExecutor);
    EXPECT_NE(clipboard, nullptr);
}

std::string g_data;
void ClipboardcallBack(const std::string& data)
{
    g_data = data;
}

/**
 * @tc.name: CastToClipboardTestTest001
 * @tc.desc: Test cast to clipboard
 * @tc.type: FUNC
 */
HWTEST_F(ClipboardTest, CastToClipboardTestTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set delegate to mock object.
     * @tc.expected: step1. The return clipboard is ok and the GetData fuction is ok.
     */
    ClipboardProxy::GetInstance()->SetDelegate(std::make_unique<MockClipboardProxyImpl>());
    RefPtr<TaskExecutor> taskExecutor;
    RefPtr<Clipboard> clipboard = ClipboardProxy::GetInstance()->GetClipboard(taskExecutor);
    ASSERT_NE(clipboard, nullptr);

    clipboard->GetData(ClipboardcallBack);
    EXPECT_EQ(g_data, "");
}
} // namespace OHOS::Ace
