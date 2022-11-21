/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

// Add the following two macro definitions to test the private and protected method.
#define private public
#define protected public

#include "frameworks/core/accessibility/js_inspector/inspect_stepper.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectStepperTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectStepperTest001
 * @tc.desc: InspectStepper::InspectStepper
 * @tc.type: FUNC
 */
HWTEST_F(InspectStepperTest, InspectStepperTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectStepper inspectStepper(nodeId, tag);
    EXPECT_EQ(inspectStepper.nodeId_, nodeId);
    EXPECT_EQ(inspectStepper.tag_, tag);
}

/**
 * @tc.name: InspectStepperTest002
 * @tc.desc: InspectStepper::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectStepperTest, InspectStepperTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectStepper inspectStepper(nodeId, tag);
    auto attrsSize = inspectStepper.attrs_.size();
    auto stylesSize = inspectStepper.styles_.size();
    uint16_t attrsSizeInsert = 2;

    inspectStepper.PackAttrAndStyle();
    EXPECT_EQ(inspectStepper.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectStepper.attrs_["disabled"], "false");
    EXPECT_EQ(inspectStepper.attrs_["focusable"], "false");
    EXPECT_EQ(inspectStepper.styles_.size(), stylesSize);
}
} // namespace OHOS::Ace::Framework
