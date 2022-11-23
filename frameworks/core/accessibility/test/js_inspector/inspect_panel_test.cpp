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

#include "frameworks/core/accessibility/js_inspector/inspect_panel.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectPanelTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectPanelTest001
 * @tc.desc: InspectPanel::InspectPanel
 * @tc.type: FUNC
 */
HWTEST_F(InspectPanelTest, InspectPanelTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectPanel inspectPanel(nodeId, tag);
    EXPECT_EQ(inspectPanel.nodeId_, nodeId);
    EXPECT_EQ(inspectPanel.tag_, tag);
}

/**
 * @tc.name: InspectPanelTest002
 * @tc.desc: InspectPanel::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectPanelTest, InspectPanelTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectPanel inspectPanel(nodeId, tag);
    auto attrsSize = inspectPanel.attrs_.size();
    uint16_t attrsSizeInsert = 2;

    inspectPanel.PackAttrAndStyle();
    EXPECT_EQ(inspectPanel.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectPanel.attrs_["mode"], "full");
    EXPECT_EQ(inspectPanel.attrs_["dragbar"], "true");
    EXPECT_EQ(inspectPanel.styles_.find("display"), inspectPanel.styles_.end());
    EXPECT_EQ(inspectPanel.styles_.find("visibility"), inspectPanel.styles_.end());
    EXPECT_EQ(inspectPanel.styles_.find("flex-grow"), inspectPanel.styles_.end());
    EXPECT_EQ(inspectPanel.styles_.find("flex-shrink"), inspectPanel.styles_.end());
    EXPECT_EQ(inspectPanel.styles_.find("position"), inspectPanel.styles_.end());
}
} // namespace OHOS::Ace::Framework
