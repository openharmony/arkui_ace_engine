/*
 * Copyright (c) 2025 iSoftStone Information Technology (Group) Co.,Ltd.
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

#include "core/common/multi_thread_build_manager.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
class MultiThreadBuildManagerTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void MultiThreadBuildManagerTest::SetUpTestSuite()
{
}

void MultiThreadBuildManagerTest::TearDownTestSuite()
{
}

/**
 * @tc.name: MultiThreadBuildManagerTest
 * @tc.desc: Test cast to CheckNodeOnValidThread
 * @tc.type: FUNC
 */
HWTEST_F(MultiThreadBuildManagerTest, CheckNodeOnValidThread001, TestSize.Level1)
{
    bool result = MultiThreadBuildManager::CheckNodeOnValidThread(nullptr);
    EXPECT_FALSE(result);
    bool isUIThread = MultiThreadBuildManager::isUIThread_;
    auto frameNode =
        NG::FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<NG::Pattern>(), true);
    MultiThreadBuildManager::isUIThread_ = true;
    result = MultiThreadBuildManager::CheckNodeOnValidThread(AceType::RawPtr(frameNode));
    EXPECT_TRUE(result);
    MultiThreadBuildManager::isUIThread_ = isUIThread;
}
} // namespace OHOS::Ace
