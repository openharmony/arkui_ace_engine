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

#include "frameworks/core/accessibility/js_inspector/inspect_chart.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectChartTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectChartTest001
 * @tc.desc: InspectChart::InspectChart
 * @tc.type: FUNC
 */
HWTEST_F(InspectChartTest, InspectChartTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectChart inspectChart(nodeId, tag);
    EXPECT_EQ(inspectChart.nodeId_, nodeId);
    EXPECT_EQ(inspectChart.tag_, tag);
}

/**
 * @tc.name: InspectChartTest002
 * @tc.desc: InspectChart::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectChartTest, InspectChartTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectChart inspectChart(nodeId, tag);
    auto attrsSize = inspectChart.attrs_.size();
    auto stylesSize = inspectChart.styles_.size();
    uint16_t attrsSizeInsert = 19;
    uint16_t stylesSizeInsert = 3;
    inspectChart.PackAttrAndStyle();
    EXPECT_EQ(inspectChart.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectChart.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectChart.attrs_["type"], "line");
    EXPECT_EQ(inspectChart.attrs_["effects"], "true");
    EXPECT_EQ(inspectChart.attrs_["disabled"], "false");
    EXPECT_EQ(inspectChart.attrs_["focusable"], "false");
    // insert makes sure that the second insert is invalid
    EXPECT_EQ(inspectChart.attrs_["strokeColor"], "#ff6384");
    EXPECT_EQ(inspectChart.attrs_["fillColor"], "#ff6384");
    EXPECT_EQ(inspectChart.attrs_["gradient"], "false");
    EXPECT_EQ(inspectChart.attrs_["min"], "0");
    EXPECT_EQ(inspectChart.attrs_["max"], "100");
    EXPECT_EQ(inspectChart.attrs_["axisTick"], "10");
    EXPECT_EQ(inspectChart.attrs_["display"], "false");
    EXPECT_EQ(inspectChart.attrs_["color"], "#c0c0c0");
    EXPECT_EQ(inspectChart.attrs_["width"], "1px");
    EXPECT_EQ(inspectChart.attrs_["smooth"], "false");
    EXPECT_EQ(inspectChart.attrs_["shape"], "circle");
    EXPECT_EQ(inspectChart.attrs_["size"], "5px");
    EXPECT_EQ(inspectChart.attrs_["strokeWidth"], "1px");
    EXPECT_EQ(inspectChart.attrs_["margin"], "1");
    EXPECT_EQ(inspectChart.attrs_["percent"], "0");
    EXPECT_EQ(inspectChart.styles_["stroke-width"], "32px");
    EXPECT_EQ(inspectChart.styles_["start-angle"], "240");
    EXPECT_EQ(inspectChart.styles_["total-angle"], "240");
}
} // namespace OHOS::Ace::Framework
