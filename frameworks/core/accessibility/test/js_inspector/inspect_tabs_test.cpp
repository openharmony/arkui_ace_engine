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

#include "frameworks/core/accessibility/js_inspector/inspect_tabs.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectTabsTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectTabsTest001
 * @tc.desc: InspectTabs::InspectTabs
 * @tc.type: FUNC
 */
HWTEST_F(InspectTabsTest, InspectTabsTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectTabs inspectTabs(nodeId, tag);
    EXPECT_EQ(inspectTabs.nodeId_, nodeId);
    EXPECT_EQ(inspectTabs.tag_, tag);
}

/**
 * @tc.name: InspectTabsTest002
 * @tc.desc: InspectTabs::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectTabsTest, InspectTabsTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectTabs inspectTabs(nodeId, tag);
    auto attrsSize = inspectTabs.attrs_.size();
    auto stylesSize = inspectTabs.styles_.size();
    uint16_t attrsSizeInsert = 4;

    inspectTabs.PackAttrAndStyle();
    EXPECT_EQ(inspectTabs.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectTabs.attrs_["index"], "0");
    EXPECT_EQ(inspectTabs.attrs_["vertical"], "false");
    EXPECT_EQ(inspectTabs.attrs_["disabled"], "false");
    EXPECT_EQ(inspectTabs.attrs_["focusable"], "true");
    EXPECT_EQ(inspectTabs.styles_.size(), stylesSize);
}
} // namespace OHOS::Ace::Framework
