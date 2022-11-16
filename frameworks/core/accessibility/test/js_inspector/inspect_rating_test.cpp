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

#include "frameworks/core/accessibility/js_inspector/inspect_rating.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectRatingTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectRatingTest001
 * @tc.desc: InspectRating::InspectRating
 * @tc.type: FUNC
 */
HWTEST_F(InspectRatingTest, InspectRatingTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectRating inspectRating(nodeId, tag);
    EXPECT_EQ(inspectRating.nodeId_, nodeId);
    EXPECT_EQ(inspectRating.tag_, tag);
}

/**
 * @tc.name: InspectRatingTest002
 * @tc.desc: InspectRating::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectRatingTest, InspectRatingTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectRating inspectRating(nodeId, tag);
    auto attrsSize = inspectRating.attrs_.size();
    auto stylesSize = inspectRating.styles_.size();
    uint16_t attrsSizeInsert = 6;
    uint16_t stylesSizeInsert = 3;

    inspectRating.PackAttrAndStyle();
    EXPECT_EQ(inspectRating.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectRating.attrs_["numstars"], "5");
    EXPECT_EQ(inspectRating.attrs_["rating"], "0");
    EXPECT_EQ(inspectRating.attrs_["stepsize"], "0.5");
    EXPECT_EQ(inspectRating.attrs_["indicator"], "false");
    EXPECT_EQ(inspectRating.attrs_["disabled"], "false");
    EXPECT_EQ(inspectRating.attrs_["focusable"], "true");
    EXPECT_EQ(inspectRating.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectRating.styles_["width"], "120px");
    EXPECT_EQ(inspectRating.styles_["height"], "24px");
    EXPECT_EQ(inspectRating.styles_["rtl-flip"], "true");
}
} // namespace OHOS::Ace::Framework
