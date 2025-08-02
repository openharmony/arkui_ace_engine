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

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#define private public
#define protected public


#include "base/log/dump_log.h"

#include "base/log/dump_log.h"
#include "core/accessibility/hidumper/accessibility_hidumper.h"

#include "core/components_ng/base/frame_node.h"


using namespace OHOS::Accessibility;
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
namespace {
} // namespace

class AccessibilityHidumperTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void AccessibilityHidumperTest::SetUpTestCase()
{
    std::unique_ptr<std::ostream> ostream = std::make_unique<std::ostringstream>();
    ASSERT_NE(ostream, nullptr);
    DumpLog::GetInstance().SetDumpFile(std::move(ostream));
}

void AccessibilityHidumperTest::TearDownTestCase()
{
}

/**
 * @tc.name: AccessibilityDfxTest003
 * @tc.desc: DumpProcessInjectActionParameters
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHidumperTest, AccessibilityDfxTest003, TestSize.Level1)
{
    std::vector<std::string> params = {"-inspector", "--inject-action", "999", "--NotifyChildAction", "5"};
    int64_t nodeId = 0;
    int32_t resultVal = 0;
    InjectActionType actionType{};

    bool ret = AccessibilityHidumper::DumpProcessInjectActionParameters(
        params, nodeId, resultVal, actionType);

    // suppose to parse inject-action normal
    EXPECT_TRUE(ret);
    EXPECT_EQ(nodeId, 999);
    EXPECT_EQ(resultVal, 5);
    EXPECT_EQ(actionType, InjectActionType::NOTIFY_CHILD_ACTION);
}

/**
 * @tc.name: AccessibilityDfxTest004
 * @tc.desc: DumpProcessInjectActionParameters
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHidumperTest, AccessibilityDfxTest004, TestSize.Level1)
{
    std::vector<std::string> params = {"-inspector", "--NotifyChildAction"};
    int64_t nodeId = 0;
    int32_t resultVal = 0;
    InjectActionType actionType{};

    // suppose to parse inject-action fail
    bool ret = AccessibilityHidumper::DumpProcessInjectActionParameters(
        params, nodeId, resultVal, actionType);

    EXPECT_FALSE(ret);
}

/**
 * @tc.name: AccessibilityDfxTest005
 * @tc.desc: DumpProcessInjectActionParameters
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHidumperTest, AccessibilityDfxTest005, TestSize.Level1)
{
    std::vector<std::string> params = {};
    int64_t nodeId = 0;
    int32_t resultVal = 0;
    InjectActionType actionType{};

    // suppose to parse inject-action fail
    bool ret = AccessibilityHidumper::DumpProcessInjectActionParameters(
        params, nodeId, resultVal, actionType);

    EXPECT_FALSE(ret);
}


/**
 * @tc.name: AccessibilityDfxTest006
 * @tc.desc: DumpProcessInjectActionParameters
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHidumperTest, AccessibilityDfxTest006, TestSize.Level1)
{
    std::vector<std::string> params = {"-inspector", "--inject-action"};
    int64_t nodeId = 0;
    int32_t resultVal = 0;
    InjectActionType actionType{};

    // suppose to parse inject-action fail
    bool ret = AccessibilityHidumper::DumpProcessInjectActionParameters(
        params, nodeId, resultVal, actionType);

    EXPECT_FALSE(ret);
}
} // namespace OHOS::Ace::NG