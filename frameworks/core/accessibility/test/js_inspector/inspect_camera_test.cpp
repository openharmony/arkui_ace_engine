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

#include "frameworks/core/accessibility/js_inspector/inspect_camera.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectCameraTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectCameraTest001
 * @tc.desc: InspectCamera::InspectCamera
 * @tc.type: FUNC
 */
HWTEST_F(InspectCameraTest, InspectCameraTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectCamera inspectCamera(nodeId, tag);
    EXPECT_EQ(inspectCamera.nodeId_, nodeId);
    EXPECT_EQ(inspectCamera.tag_, tag);
}

/**
 * @tc.name: InspectCameraTest002
 * @tc.desc: InspectCamera::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectCameraTest, InspectCameraTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectCamera inspectCamera(nodeId, tag);
    auto size = inspectCamera.attrs_.size();
    uint16_t sizeInsert = 2;
    inspectCamera.PackAttrAndStyle();
    EXPECT_EQ(inspectCamera.attrs_.size(), size + sizeInsert);
    EXPECT_EQ(inspectCamera.attrs_["flash"], "off");
    EXPECT_EQ(inspectCamera.attrs_["deviceposition"], "back");
}
} // namespace OHOS::Ace::Framework
