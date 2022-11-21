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

#include "frameworks/core/accessibility/js_inspector/inspect_canvas.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectCanvasTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectCanvasTest001
 * @tc.desc: InspectCanvas::InspectCanvas
 * @tc.type: FUNC
 */
HWTEST_F(InspectCanvasTest, InspectCanvasTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectCanvas inspectCanvas(nodeId, tag);
    EXPECT_EQ(inspectCanvas.nodeId_, nodeId);
    EXPECT_EQ(inspectCanvas.tag_, tag);
}

/**
 * @tc.name: InspectCanvasTest002
 * @tc.desc: InspectCanvas::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectCanvasTest, InspectCanvasTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectCanvas inspectCanvas(nodeId, tag);
    auto size = inspectCanvas.attrs_.size();
    uint16_t sizeInsert = 2;
    inspectCanvas.PackAttrAndStyle();
    EXPECT_EQ(inspectCanvas.attrs_.size(), size + sizeInsert);
    EXPECT_EQ(inspectCanvas.attrs_["disabled"], "false");
    EXPECT_EQ(inspectCanvas.attrs_["focusable"], "false");
}
} // namespace OHOS::Ace::Framework
