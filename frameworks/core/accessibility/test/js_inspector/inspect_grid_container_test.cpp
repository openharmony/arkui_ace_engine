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

#include "frameworks/core/accessibility/js_inspector/inspect_grid_container.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectGridContainerTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectGridContainerTest001
 * @tc.desc: InspectGridContainer::InspectGridContainer
 * @tc.type: FUNC
 */
HWTEST_F(InspectGridContainerTest, InspectGridContainerTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectGridContainer inspectGridContainer(nodeId, tag);
    EXPECT_EQ(inspectGridContainer.nodeId_, nodeId);
    EXPECT_EQ(inspectGridContainer.tag_, tag);
}

/**
 * @tc.name: InspectGridContainerTest002
 * @tc.desc: InspectGridContainer::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectGridContainerTest, InspectGridContainerTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectGridContainer inspectGridContainer(nodeId, tag);
    auto attrsSize = inspectGridContainer.attrs_.size();
    auto stylesSize = inspectGridContainer.styles_.size();
    uint16_t attrsSizeInsert = 5;
    uint16_t stylesSizeInsert = 3;

    inspectGridContainer.PackAttrAndStyle();
    EXPECT_EQ(inspectGridContainer.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectGridContainer.attrs_["columns"], "auto");
    EXPECT_EQ(inspectGridContainer.attrs_["sizetype"], "auto");
    EXPECT_EQ(inspectGridContainer.attrs_["gutter"], "24px");
    EXPECT_EQ(inspectGridContainer.attrs_["disabled"], "false");
    EXPECT_EQ(inspectGridContainer.attrs_["focusable"], "true");
    EXPECT_EQ(inspectGridContainer.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectGridContainer.styles_["justify-content"], "flex-start");
    EXPECT_EQ(inspectGridContainer.styles_["align-items"], "stretch");
    EXPECT_EQ(inspectGridContainer.styles_["align-content"], "flex-start");
}
} // namespace OHOS::Ace::Framework
