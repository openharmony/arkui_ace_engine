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

#include "frameworks/core/accessibility/js_inspector/inspect_video.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectVideoTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectVideoTest001
 * @tc.desc: InspectVideo::InspectVideo
 * @tc.type: FUNC
 */
HWTEST_F(InspectVideoTest, InspectVideoTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectVideo inspectVideo(nodeId, tag);
    EXPECT_EQ(inspectVideo.nodeId_, nodeId);
    EXPECT_EQ(inspectVideo.tag_, tag);
}

/**
 * @tc.name: InspectVideoTest002
 * @tc.desc: InspectVideo::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectVideoTest, InspectVideoTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectVideo inspectVideo(nodeId, tag);
    auto attrsSize = inspectVideo.attrs_.size();
    auto stylesSize = inspectVideo.styles_.size();
    uint16_t attrsSizeInsert = 5;
    uint16_t stylesSizeInsert = 1;

    inspectVideo.PackAttrAndStyle();
    EXPECT_EQ(inspectVideo.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectVideo.attrs_["muted"], "false");
    EXPECT_EQ(inspectVideo.attrs_["autoplay"], "false");
    EXPECT_EQ(inspectVideo.attrs_["controls"], "true");
    EXPECT_EQ(inspectVideo.attrs_["disabled"], "false");
    EXPECT_EQ(inspectVideo.attrs_["focusable"], "true");
    EXPECT_EQ(inspectVideo.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectVideo.styles_["object-fit"], "contain");
}
} // namespace OHOS::Ace::Framework
