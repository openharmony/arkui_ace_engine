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

#include "frameworks/core/accessibility/js_inspector/inspect_toolbar_item.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectToolbarItemTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectToolbarItemTest001
 * @tc.desc: InspectToolbarItem::InspectToolbarItem
 * @tc.type: FUNC
 */
HWTEST_F(InspectToolbarItemTest, InspectToolbarItemTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectToolbarItem inspectToolbarItem(nodeId, tag);
    EXPECT_EQ(inspectToolbarItem.nodeId_, nodeId);
    EXPECT_EQ(inspectToolbarItem.tag_, tag);
}

/**
 * @tc.name: InspectToolbarItemTest002
 * @tc.desc: InspectToolbarItem::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectToolbarItemTest, InspectToolbarItemTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectToolbarItem inspectToolbarItem(nodeId, tag);
    auto attrsSize = inspectToolbarItem.attrs_.size();
    auto stylesSize = inspectToolbarItem.styles_.size();
    uint16_t attrsSizeInsert = 2;
    uint16_t stylesSizeInsert = 13;

    inspectToolbarItem.PackAttrAndStyle();
    EXPECT_EQ(inspectToolbarItem.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectToolbarItem.attrs_["disabled"], "false");
    EXPECT_EQ(inspectToolbarItem.attrs_["focusable"], "false");
    EXPECT_EQ(inspectToolbarItem.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectToolbarItem.styles_["color"], "#e6000000");
    EXPECT_EQ(inspectToolbarItem.styles_["font-size"], "16px");
    EXPECT_EQ(inspectToolbarItem.styles_["allow-scale"], "true");
    EXPECT_EQ(inspectToolbarItem.styles_["font-style"], "normal");
    EXPECT_EQ(inspectToolbarItem.styles_["font-weight"], "normal");
    EXPECT_EQ(inspectToolbarItem.styles_["text-decoration"], "none");
    EXPECT_EQ(inspectToolbarItem.styles_["font-family"], "sans-serif");
    EXPECT_EQ(inspectToolbarItem.styles_["background-size"], "auto");
    EXPECT_EQ(inspectToolbarItem.styles_["background-repeat"], "repeat");
    EXPECT_EQ(inspectToolbarItem.styles_["background-position"], "0px 0px");
    EXPECT_EQ(inspectToolbarItem.styles_["opacity"], "1");
    EXPECT_EQ(inspectToolbarItem.styles_["display"], "flex");
    EXPECT_EQ(inspectToolbarItem.styles_["visibility"], "visible");
}
} // namespace OHOS::Ace::Framework
