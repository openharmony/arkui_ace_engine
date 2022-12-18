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

#include "frameworks/core/accessibility/js_inspector/inspect_grid_row.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectGridRowTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectGridRowTest001
 * @tc.desc: InspectGridRow::InspectGridRow
 * @tc.type: FUNC
 */
HWTEST_F(InspectGridRowTest, InspectGridRowTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectGridRow inspectGridRow(nodeId, tag);
    EXPECT_EQ(inspectGridRow.nodeId_, nodeId);
    EXPECT_EQ(inspectGridRow.tag_, tag);
}

/**
 * @tc.name: InspectGridRowTest002
 * @tc.desc: InspectGridRow::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectGridRowTest, InspectGridRowTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectGridRow inspectGridRow(nodeId, tag);
    auto attrsSize = inspectGridRow.attrs_.size();
    auto stylesSize = inspectGridRow.styles_.size();
    uint16_t attrsSizeInsert = 2;
    uint16_t stylesSizeInsert = 4;

    inspectGridRow.PackAttrAndStyle();
    EXPECT_EQ(inspectGridRow.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectGridRow.attrs_["disabled"], "false");
    EXPECT_EQ(inspectGridRow.attrs_["focusable"], "false");
    EXPECT_EQ(inspectGridRow.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectGridRow.styles_["flex-wrap"], "nowrap");
    EXPECT_EQ(inspectGridRow.styles_["justify-content"], "flex-start");
    EXPECT_EQ(inspectGridRow.styles_["align-items"], "flex-start");
    EXPECT_EQ(inspectGridRow.styles_["align-content"], "flex-start");
    EXPECT_EQ(inspectGridRow.styles_.find("padding-left"), inspectGridRow.styles_.end());
    EXPECT_EQ(inspectGridRow.styles_.find("padding-top"), inspectGridRow.styles_.end());
    EXPECT_EQ(inspectGridRow.styles_.find("padding-right"), inspectGridRow.styles_.end());
    EXPECT_EQ(inspectGridRow.styles_.find("padding-bottom"), inspectGridRow.styles_.end());
    EXPECT_EQ(inspectGridRow.styles_.find("padding-start"), inspectGridRow.styles_.end());
    EXPECT_EQ(inspectGridRow.styles_.find("padding-end"), inspectGridRow.styles_.end());
    EXPECT_EQ(inspectGridRow.styles_.find("margin-left"), inspectGridRow.styles_.end());
    EXPECT_EQ(inspectGridRow.styles_.find("margin-top"), inspectGridRow.styles_.end());
    EXPECT_EQ(inspectGridRow.styles_.find("margin-right"), inspectGridRow.styles_.end());
    EXPECT_EQ(inspectGridRow.styles_.find("margin-bottom"), inspectGridRow.styles_.end());
    EXPECT_EQ(inspectGridRow.styles_.find("margin-start"), inspectGridRow.styles_.end());
    EXPECT_EQ(inspectGridRow.styles_.find("margin-end"), inspectGridRow.styles_.end());
    EXPECT_EQ(inspectGridRow.styles_.find("flex-grow"), inspectGridRow.styles_.end());
    EXPECT_EQ(inspectGridRow.styles_.find("flex-shrink"), inspectGridRow.styles_.end());
    EXPECT_EQ(inspectGridRow.styles_.find("position"), inspectGridRow.styles_.end());
}
} // namespace OHOS::Ace::Framework
