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

#include "frameworks/core/accessibility/js_inspector/inspect_menu.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectMenuTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectMenuTest001
 * @tc.desc: InspectMenu::InspectMenu
 * @tc.type: FUNC
 */
HWTEST_F(InspectMenuTest, InspectMenuTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectMenu inspectMenu(nodeId, tag);
    EXPECT_EQ(inspectMenu.nodeId_, nodeId);
    EXPECT_EQ(inspectMenu.tag_, tag);
}

/**
 * @tc.name: InspectMenuTest002
 * @tc.desc: InspectMenu::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectMenuTest, InspectMenuTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectMenu inspectMenu(nodeId, tag);
    auto attrsSize = inspectMenu.attrs_.size();
    auto stylesSize = inspectMenu.styles_.size();
    uint16_t attrsSizeInsert = 1;
    uint16_t stylesSizeInsert = 6;

    inspectMenu.PackAttrAndStyle();
    EXPECT_EQ(inspectMenu.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectMenu.attrs_["type"], "click");
    EXPECT_EQ(inspectMenu.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectMenu.styles_["font-size"], "30px");
    EXPECT_EQ(inspectMenu.styles_["allow-scale"], "true");
    EXPECT_EQ(inspectMenu.styles_["letter-spacing"], "0");
    EXPECT_EQ(inspectMenu.styles_["font-style"], "normal");
    EXPECT_EQ(inspectMenu.styles_["font-weight"], "normal");
    EXPECT_EQ(inspectMenu.styles_["font-family"], "sans-serif");
}
} // namespace OHOS::Ace::Framework
