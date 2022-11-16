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

#include "frameworks/core/accessibility/js_inspector/inspect_refresh.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectRefreshTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectRefreshTest001
 * @tc.desc: InspectRefresh::InspectRefresh
 * @tc.type: FUNC
 */
HWTEST_F(InspectRefreshTest, InspectRefreshTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectRefresh inspectRefresh(nodeId, tag);
    EXPECT_EQ(inspectRefresh.nodeId_, nodeId);
    EXPECT_EQ(inspectRefresh.tag_, tag);
}

/**
 * @tc.name: InspectRefreshTest002
 * @tc.desc: InspectRefresh::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectRefreshTest, InspectRefreshTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectRefresh inspectRefresh(nodeId, tag);
    auto attrsSize = inspectRefresh.attrs_.size();
    auto stylesSize = inspectRefresh.styles_.size();
    uint16_t attrsSizeInsert = 6;
    uint16_t stylesSizeInsert = 5;

    inspectRefresh.PackAttrAndStyle();
    EXPECT_EQ(inspectRefresh.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectRefresh.attrs_["refreshing"], "false");
    EXPECT_EQ(inspectRefresh.attrs_["type"], "auto");
    EXPECT_EQ(inspectRefresh.attrs_["lasttime"], "false");
    EXPECT_EQ(inspectRefresh.attrs_["friction"], "42");
    EXPECT_EQ(inspectRefresh.attrs_["disabled"], "false");
    EXPECT_EQ(inspectRefresh.attrs_["focusable"], "true");
    EXPECT_EQ(inspectRefresh.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectRefresh.styles_["background-color"], "white");
    EXPECT_EQ(inspectRefresh.styles_["progress-color"], "black");
    EXPECT_EQ(inspectRefresh.styles_["min-width"], "0");
    EXPECT_EQ(inspectRefresh.styles_["min-height"], "0");
    EXPECT_EQ(inspectRefresh.styles_["box-shadow"], "0");
}
} // namespace OHOS::Ace::Framework