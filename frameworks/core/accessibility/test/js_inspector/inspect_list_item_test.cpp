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

#include "frameworks/core/accessibility/js_inspector/inspect_list_item.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectListItemTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectListItemTest001
 * @tc.desc: InspectListItem::InspectListItem
 * @tc.type: FUNC
 */
HWTEST_F(InspectListItemTest, InspectListItemTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectListItem inspectListItem(nodeId, tag);
    EXPECT_EQ(inspectListItem.nodeId_, nodeId);
    EXPECT_EQ(inspectListItem.tag_, tag);
}

/**
 * @tc.name: InspectListItemTest002
 * @tc.desc: InspectListItem::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectListItemTest, InspectListItemTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectListItem inspectListItem(nodeId, tag);
    auto attrsSize = inspectListItem.attrs_.size();
    auto stylesSize = inspectListItem.styles_.size();
    uint16_t attrsSizeInsert = 7;
    uint16_t stylesSizeInsert = 1;

    inspectListItem.PackAttrAndStyle();
    EXPECT_EQ(inspectListItem.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectListItem.attrs_["type"], "default");
    EXPECT_EQ(inspectListItem.attrs_["primary"], "false");
    EXPECT_EQ(inspectListItem.attrs_["sticky"], "none");
    EXPECT_EQ(inspectListItem.attrs_["stickyradius"], "1000px");
    EXPECT_EQ(inspectListItem.attrs_["clickeffect"], "true");
    EXPECT_EQ(inspectListItem.attrs_["disabled"], "false");
    EXPECT_EQ(inspectListItem.attrs_["focusable"], "true");
    EXPECT_EQ(inspectListItem.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectListItem.styles_["column-span"], "1");
}
} // namespace OHOS::Ace::Framework
