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
 
#include <cstddef>
#include <cstdint>
#include <map>
#include <sstream>
#include <unistd.h>
#include <vector>
 
#include "gtest/gtest.h"
 
#define private public
#define protected public
 
#include "frameworks/core/event/axis_event.h"
 
using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
static std::map<AxisAction, std::string> AxisAction2String = {
    { AxisAction::NONE, "AxisAction::NONE" },
    { AxisAction::BEGIN, "AxisAction::BEGIN" },
    { AxisAction::UPDATE, "AxisAction::UPDATE" },
    { AxisAction::END, "AxisAction::END" },
    { AxisAction::CANCEL, "AxisAction::CANCEL" },
};
 
struct AxisEventCheckerTestCase {
    AxisAction currentAction { AxisAction::NONE };
    AxisAction inputAction { AxisAction::NONE };
    bool expectedResult { false };
    AxisAction expectedPreActionOld { AxisAction::NONE };
    AxisAction expectedPreActionNew { AxisAction::NONE };

    std::string ToString() const
    {
        std::stringstream out;
        out << "{ " << AxisAction2String[currentAction] << ", " << AxisAction2String[inputAction] << ", "
            << expectedResult << ", " << AxisAction2String[expectedPreActionOld] << ", "
            << AxisAction2String[expectedPreActionNew] << " }";
        return out.str();
    }
};
} // namespace
 
class AxisEventTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};
 
void AxisEventTestNg::SetUpTestSuite()
{
    // do nothing
    GTEST_LOG_(INFO) << "AxisEventTestNg SetUpTestSuite";
}
 
void AxisEventTestNg::TearDownTestSuite()
{
    // do nothing
    GTEST_LOG_(INFO) << "AxisEventTestNg TearDownTestSuite";
}
 
const static std::vector<AxisEventCheckerTestCase> axisEventCheckerTestCases = {
    { AxisAction::NONE, AxisAction::NONE, false, AxisAction::NONE, AxisAction::NONE },
    { AxisAction::NONE, AxisAction::BEGIN, true, AxisAction::NONE, AxisAction::BEGIN, },
    { AxisAction::NONE, AxisAction::UPDATE, false, AxisAction::NONE, AxisAction::UPDATE },
    { AxisAction::NONE, AxisAction::END, false, AxisAction::NONE, AxisAction::NONE },
    { AxisAction::NONE, AxisAction::CANCEL, false, AxisAction::NONE, AxisAction::NONE },
 
    { AxisAction::BEGIN, AxisAction::NONE, false, AxisAction::BEGIN, AxisAction::NONE },
    { AxisAction::BEGIN, AxisAction::BEGIN, false, AxisAction::BEGIN, AxisAction::BEGIN },
    { AxisAction::BEGIN, AxisAction::UPDATE, true, AxisAction::BEGIN, AxisAction::UPDATE },
    { AxisAction::BEGIN, AxisAction::END, true, AxisAction::BEGIN, AxisAction::NONE },
    { AxisAction::BEGIN, AxisAction::CANCEL, true, AxisAction::BEGIN, AxisAction::NONE },
 
    { AxisAction::UPDATE, AxisAction::NONE, false, AxisAction::UPDATE, AxisAction::NONE },
    { AxisAction::UPDATE, AxisAction::BEGIN, false, AxisAction::UPDATE, AxisAction::BEGIN },
    { AxisAction::UPDATE, AxisAction::UPDATE, true, AxisAction::UPDATE, AxisAction::UPDATE },
    { AxisAction::UPDATE, AxisAction::END, true, AxisAction::UPDATE, AxisAction::NONE },
    { AxisAction::UPDATE, AxisAction::CANCEL, true, AxisAction::UPDATE, AxisAction::NONE },
};
 
/**
 * @tc.name: AxisEventChecker001
 * @tc.desc: Create AxisEventChecker and execute its functions.
 * @tc.type: FUNC
 */
HWTEST_F(AxisEventTestNg, AxisEventChecker001, TestSize.Level1)
{
    const static SourceType sourceTypes[] = { SourceType::MOUSE };
    for (auto& sourceType : sourceTypes) {
        for (auto& testCase : axisEventCheckerTestCases) {
 
            /**
             * @tc.steps: step1. Create AxisEventChecker and set preActionNew_
             */
            AxisEventChecker checker;
            checker.preActionNew_ = testCase.currentAction;
 
            /**
             * @tc.steps: step2. Create AxisEvent and set action and sourceType
             */
            AxisEvent axisEvent;
            axisEvent.action = testCase.inputAction;
            axisEvent.sourceType = sourceType;

            /**
             * @tc.steps: step3. Execute IsAxisEventSequenceCorrect
             * @tc.expected: IsAxisEventSequenceCorrect is equal to expectedResult
             * @tc.expected: GetPreAction is equal to expectedPreActionOld
             * @tc.expected: preActionNew_ is equal to expectedPreActionNew
             */
            GTEST_LOG_(INFO) << testCase.ToString().c_str() << std::endl;
            EXPECT_EQ(checker.IsAxisEventSequenceCorrect(axisEvent), testCase.expectedResult);
            EXPECT_EQ(checker.GetPreAction(), testCase.expectedPreActionOld);
            EXPECT_EQ(checker.preActionNew_, testCase.expectedPreActionNew);
        }
    }
}
 
/**
 * @tc.name: AxisEventChecker001
 * @tc.desc: Create AxisEventChecker and execute its functions not work for other sourceType
 * @tc.type: FUNC
 */
HWTEST_F(AxisEventTestNg, AxisEventChecker002, TestSize.Level1)
{
    const static SourceType sourceTypes[] = { SourceType::NONE, SourceType::TOUCH, SourceType::KEYBOARD,
        SourceType::TOUCH_PAD };
 
    for (auto& sourceType : sourceTypes) {
        for (auto& testCase : axisEventCheckerTestCases) {
            /**
             * @tc.steps: step1. Create AxisEventChecker and set preActionNew_
             */
            AxisEventChecker checker;
            checker.preActionNew_ = testCase.inputAction;
            checker.preActionOld_ = AxisAction::NONE;
 
            /**
             * @tc.steps: step2. Create AxisEvent and set action and sourceType
             */
            AxisEvent axisEvent;
            axisEvent.action = testCase.currentAction;
            axisEvent.sourceType = sourceType;
 
            /**
             * @tc.steps: step3. Execute IsAxisEventSequenceCorrect
             * @tc.expected: IsAxisEventSequenceCorrect is equal to true
             * @tc.expected: GetPreAction is equal to AxisAction::NONE
             */
            GTEST_LOG_(INFO) << testCase.ToString().c_str() << std::endl;
            EXPECT_EQ(checker.IsAxisEventSequenceCorrect(axisEvent), true);
            EXPECT_EQ(checker.GetPreAction(), AxisAction::NONE);
        }
    }
}
 
} // namespace OHOS::Ace::NG