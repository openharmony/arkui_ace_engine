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

#include "frameworks/core/accessibility/js_inspector/inspect_grid_column.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectGridColumnTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectGridColumnTest001
 * @tc.desc: InspectGridColumn::InspectGridColumn
 * @tc.type: FUNC
 */
HWTEST_F(InspectGridColumnTest, InspectGridColumnTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectGridColumn inspectGridColumn(nodeId, tag);
    EXPECT_EQ(inspectGridColumn.nodeId_, nodeId);
    EXPECT_EQ(inspectGridColumn.tag_, tag);
}

/**
 * @tc.name: InspectGridColumnTest002
 * @tc.desc: InspectGridColumn::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectGridColumnTest, InspectGridColumnTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectGridColumn inspectGridColumn(nodeId, tag);
    auto attrsSize = inspectGridColumn.attrs_.size();
    auto stylesSize = inspectGridColumn.styles_.size();
    uint16_t attrsSizeInsert = 4;
    uint16_t stylesSizeInsert = 9;

    inspectGridColumn.PackAttrAndStyle();
    EXPECT_EQ(inspectGridColumn.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectGridColumn.attrs_["span"], "1");
    EXPECT_EQ(inspectGridColumn.attrs_["offset"], "0");
    EXPECT_EQ(inspectGridColumn.attrs_["disabled"], "false");
    EXPECT_EQ(inspectGridColumn.attrs_["focusable"], "false");
    EXPECT_EQ(inspectGridColumn.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectGridColumn.styles_["flex-direction"], "row");
    EXPECT_EQ(inspectGridColumn.styles_["flex-wrap"], "nowrap");
    EXPECT_EQ(inspectGridColumn.styles_["justify-content"], "flex-start");
    EXPECT_EQ(inspectGridColumn.styles_["align-items"], "stretch");
    EXPECT_EQ(inspectGridColumn.styles_["align-content"], "flex-start");
    EXPECT_EQ(inspectGridColumn.styles_["grid-template-columns"], "1");
    EXPECT_EQ(inspectGridColumn.styles_["grid-template-rows"], "1");
    EXPECT_EQ(inspectGridColumn.styles_["grid-columns-gap"], "0");
    EXPECT_EQ(inspectGridColumn.styles_["grid-rows-gap"], "0");
    EXPECT_EQ(inspectGridColumn.styles_.find("margin-left"), inspectGridColumn.styles_.end());
    EXPECT_EQ(inspectGridColumn.styles_.find("margin-top"), inspectGridColumn.styles_.end());
    EXPECT_EQ(inspectGridColumn.styles_.find("margin-right"), inspectGridColumn.styles_.end());
    EXPECT_EQ(inspectGridColumn.styles_.find("margin-bottom"), inspectGridColumn.styles_.end());
    EXPECT_EQ(inspectGridColumn.styles_.find("margin-start"), inspectGridColumn.styles_.end());
    EXPECT_EQ(inspectGridColumn.styles_.find("margin-end"), inspectGridColumn.styles_.end());
    EXPECT_EQ(inspectGridColumn.styles_.find("flex-grow"), inspectGridColumn.styles_.end());
    EXPECT_EQ(inspectGridColumn.styles_.find("flex-shrink"), inspectGridColumn.styles_.end());
    EXPECT_EQ(inspectGridColumn.styles_.find("position"), inspectGridColumn.styles_.end());
}
} // namespace OHOS::Ace::Framework
