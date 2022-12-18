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

#include "frameworks/core/accessibility/js_inspector/inspect_list.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectListTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectListTest001
 * @tc.desc: InspectList::InspectList
 * @tc.type: FUNC
 */
HWTEST_F(InspectListTest, InspectListTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectList inspectList(nodeId, tag);
    EXPECT_EQ(inspectList.nodeId_, nodeId);
    EXPECT_EQ(inspectList.tag_, tag);
}

/**
 * @tc.name: InspectListTest002
 * @tc.desc: InspectList::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectListTest, InspectListTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectList inspectList(nodeId, tag);
    auto attrsSize = inspectList.attrs_.size();
    auto stylesSize = inspectList.styles_.size();
    uint16_t attrsSizeInsert = 18;
    uint16_t stylesSizeInsert = 7;

    inspectList.PackAttrAndStyle();
    EXPECT_EQ(inspectList.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectList.attrs_["scrollpage"], "true");
    EXPECT_EQ(inspectList.attrs_["cachedcount"], "0");
    EXPECT_EQ(inspectList.attrs_["scrollbar"], "off");
    EXPECT_EQ(inspectList.attrs_["scrolleffect"], "spring");
    EXPECT_EQ(inspectList.attrs_["indexer"], "false");
    EXPECT_EQ(inspectList.attrs_["indexermulti"], "false");
    EXPECT_EQ(inspectList.attrs_["indexerbubble"], "true");
    EXPECT_EQ(inspectList.attrs_["divider"], "false");
    EXPECT_EQ(inspectList.attrs_["shapemode"], "default");
    EXPECT_EQ(inspectList.attrs_["itemscale"], "true");
    EXPECT_EQ(inspectList.attrs_["itemcenter"], "false");
    EXPECT_EQ(inspectList.attrs_["updateeffect"], "false");
    EXPECT_EQ(inspectList.attrs_["chainanimation"], "false");
    EXPECT_EQ(inspectList.attrs_["scrollvibrate"], "true");
    EXPECT_EQ(inspectList.attrs_["initialindex"], "0");
    EXPECT_EQ(inspectList.attrs_["initialoffset"], "0");
    EXPECT_EQ(inspectList.attrs_["disabled"], "false");
    EXPECT_EQ(inspectList.attrs_["focusable"], "true");
    EXPECT_EQ(inspectList.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectList.styles_["divider-color"], "transparent");
    EXPECT_EQ(inspectList.styles_["divider-height"], "1");
    EXPECT_EQ(inspectList.styles_["divider-origin"], "0");
    EXPECT_EQ(inspectList.styles_["flex-direction"], "column");
    EXPECT_EQ(inspectList.styles_["columns"], "1");
    EXPECT_EQ(inspectList.styles_["align-items"], "stretch");
    EXPECT_EQ(inspectList.styles_["fade-color"], "grey");
}
} // namespace OHOS::Ace::Framework
