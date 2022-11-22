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

#include "frameworks/core/accessibility/js_inspector/inspect_image.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectImageTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectImageTest001
 * @tc.desc: InspectImage::InspectImage
 * @tc.type: FUNC
 */
HWTEST_F(InspectImageTest, InspectImageTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectImage inspectImage(nodeId, tag);
    EXPECT_EQ(inspectImage.nodeId_, nodeId);
    EXPECT_EQ(inspectImage.tag_, tag);
}

/**
 * @tc.name: InspectImageTest002
 * @tc.desc: InspectImage::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectImageTest, InspectImageTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectImage inspectImage(nodeId, tag);
    auto attrsSize = inspectImage.attrs_.size();
    auto stylesSize = inspectImage.styles_.size();
    uint16_t attrsSizeInsert = 2;
    uint16_t stylesSizeInsert = 3;

    inspectImage.PackAttrAndStyle();
    EXPECT_EQ(inspectImage.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectImage.attrs_["disabled"], "false");
    EXPECT_EQ(inspectImage.attrs_["focusable"], "false");
    EXPECT_EQ(inspectImage.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectImage.styles_["object-fit"], "cover");
    EXPECT_EQ(inspectImage.styles_["match-text-direction"], "false");
    EXPECT_EQ(inspectImage.styles_["fit-original-size"], "false");
}
} // namespace OHOS::Ace::Framework
