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

#include "frameworks/core/accessibility/js_inspector/inspect_popup.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectPopupTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectPopupTest001
 * @tc.desc: InspectPopup::InspectPopup
 * @tc.type: FUNC
 */
HWTEST_F(InspectPopupTest, InspectPopupTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectPopup inspectPopup(nodeId, tag);
    EXPECT_EQ(inspectPopup.nodeId_, nodeId);
    EXPECT_EQ(inspectPopup.tag_, tag);
}

/**
 * @tc.name: InspectPopupTest002
 * @tc.desc: InspectPopup::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectPopupTest, InspectPopupTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectPopup inspectPopup(nodeId, tag);
    auto attrsSize = inspectPopup.attrs_.size();
    auto stylesSize = inspectPopup.styles_.size();
    uint16_t attrsSizeInsert = 5;
    uint16_t stylesSizeInsert = 1;

    inspectPopup.PackAttrAndStyle();
    EXPECT_EQ(inspectPopup.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectPopup.attrs_["placement"], "bottom");
    EXPECT_EQ(inspectPopup.attrs_["keepalive"], "false");
    EXPECT_EQ(inspectPopup.attrs_["clickable"], "true");
    EXPECT_EQ(inspectPopup.attrs_["arrowoffset"], "0");
    EXPECT_EQ(inspectPopup.attrs_["disabled"], "false");
    EXPECT_EQ(inspectPopup.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectPopup.styles_["mask-color"], "#00000000");
    EXPECT_EQ(inspectPopup.styles_.find("flex-grow"), inspectPopup.styles_.end());
    EXPECT_EQ(inspectPopup.styles_.find("flex-shrink"), inspectPopup.styles_.end());
    EXPECT_EQ(inspectPopup.styles_.find("position"), inspectPopup.styles_.end());
}
} // namespace OHOS::Ace::Framework
