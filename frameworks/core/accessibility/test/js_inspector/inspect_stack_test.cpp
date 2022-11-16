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

#include "frameworks/core/accessibility/js_inspector/inspect_stack.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectStackTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectStackTest001
 * @tc.desc: InspectStack::InspectStack
 * @tc.type: FUNC
 */
HWTEST_F(InspectStackTest, InspectStackTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectStack inspectStack(nodeId, tag);
    EXPECT_EQ(inspectStack.nodeId_, nodeId);
    EXPECT_EQ(inspectStack.tag_, tag);
}

/**
 * @tc.name: InspectStackTest002
 * @tc.desc: InspectStack::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectStackTest, InspectStackTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectStack inspectStack(nodeId, tag);
    auto attrsSize = inspectStack.attrs_.size();
    auto stylesSize = inspectStack.styles_.size();
    uint16_t attrsSizeInsert = 2;

    inspectStack.PackAttrAndStyle();
    EXPECT_EQ(inspectStack.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectStack.attrs_["disabled"], "false");
    EXPECT_EQ(inspectStack.attrs_["focusable"], "true");
    EXPECT_EQ(inspectStack.styles_.size(), stylesSize);
}
} // namespace OHOS::Ace::Framework
