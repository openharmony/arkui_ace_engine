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

#include "frameworks/core/accessibility/js_inspector/inspect_tab_content.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectTabContentTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectTabContentTest001
 * @tc.desc: InspectTabContent::InspectTabContent
 * @tc.type: FUNC
 */
HWTEST_F(InspectTabContentTest, InspectTabContentTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectTabContent inspectTabContent(nodeId, tag);
    EXPECT_EQ(inspectTabContent.nodeId_, nodeId);
    EXPECT_EQ(inspectTabContent.tag_, tag);
}

/**
 * @tc.name: InspectTabContentTest002
 * @tc.desc: InspectTabContent::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectTabContentTest, InspectTabContentTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectTabContent inspectTabContent(nodeId, tag);
    auto attrsSize = inspectTabContent.attrs_.size();
    auto stylesSize = inspectTabContent.styles_.size();
    uint16_t attrsSizeInsert = 3;

    inspectTabContent.PackAttrAndStyle();
    EXPECT_EQ(inspectTabContent.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectTabContent.attrs_["scrollable"], "true");
    EXPECT_EQ(inspectTabContent.attrs_["disabled"], "false");
    EXPECT_EQ(inspectTabContent.attrs_["focusable"], "true");
    EXPECT_EQ(inspectTabContent.styles_.size(), stylesSize);
}
} // namespace OHOS::Ace::Framework
