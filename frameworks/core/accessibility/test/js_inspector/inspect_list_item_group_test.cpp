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

#include "frameworks/core/accessibility/js_inspector/inspect_list_item_group.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectListItemGroupTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectListItemGroupTest001
 * @tc.desc: InspectListItemGroup::InspectListItemGroup
 * @tc.type: FUNC
 */
HWTEST_F(InspectListItemGroupTest, InspectListItemGroupTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectListItemGroup inspectListItemGroup(nodeId, tag);
    EXPECT_EQ(inspectListItemGroup.nodeId_, nodeId);
    EXPECT_EQ(inspectListItemGroup.tag_, tag);
}

/**
 * @tc.name: InspectListItemGroupTest002
 * @tc.desc: InspectListItemGroup::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectListItemGroupTest, InspectListItemGroupTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectListItemGroup inspectListItemGroup(nodeId, tag);
    auto attrsSize = inspectListItemGroup.attrs_.size();
    auto stylesSize = inspectListItemGroup.styles_.size();
    uint16_t attrsSizeInsert = 3;
    uint16_t stylesSizeInsert = 2;

    inspectListItemGroup.PackAttrAndStyle();
    EXPECT_EQ(inspectListItemGroup.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectListItemGroup.attrs_["type"], "default");
    EXPECT_EQ(inspectListItemGroup.attrs_["disabled"], "false");
    EXPECT_EQ(inspectListItemGroup.attrs_["focusable"], "true");
    EXPECT_EQ(inspectListItemGroup.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectListItemGroup.styles_["flex-direction"], "row");
    EXPECT_EQ(inspectListItemGroup.styles_["justify-content"], "flex-start");
    EXPECT_EQ(inspectListItemGroup.styles_.find("position"), inspectListItemGroup.styles_.end());
}
} // namespace OHOS::Ace::Framework
