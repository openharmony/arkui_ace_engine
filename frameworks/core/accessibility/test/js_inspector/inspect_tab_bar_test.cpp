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
#include "base/utils/device_type.h"

// Add the following two macro definitions to test the private and protected method.
#define private public
#define protected public

#include "frameworks/core/accessibility/js_inspector/inspect_tab_bar.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectTabBarTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};

    void CheckTabBarAttrAndStyle(InspectTabBar& inspectTabBar, uint16_t attrsSize, uint16_t stylesSize)
    {
        uint16_t attrsSizeInsert = 3;
        uint16_t stylesSizeInsert = 0;
        DeviceType deviceType = SystemProperties::GetDeviceType();
        EXPECT_EQ(inspectTabBar.attrs_["mode"], "scrollable");
        EXPECT_EQ(inspectTabBar.attrs_["disabled"], "false");
        EXPECT_EQ(inspectTabBar.attrs_["focusable"], "true");
        if (deviceType == DeviceType::PHONE) {
            EXPECT_EQ(inspectTabBar.styles_["height"], "100px");
            stylesSizeInsert++;
        } else if (deviceType == DeviceType::TV) {
            EXPECT_EQ(inspectTabBar.styles_["height"], "60px");
            stylesSizeInsert++;
        }
        EXPECT_EQ(inspectTabBar.attrs_.size(), attrsSize + attrsSizeInsert);
        EXPECT_EQ(inspectTabBar.styles_.size(), stylesSize + stylesSizeInsert);
    }
};

/**
 * @tc.name: InspectTabBarTest001
 * @tc.desc: InspectTabBar::InspectTabBar
 * @tc.type: FUNC
 */
HWTEST_F(InspectTabBarTest, InspectTabBarTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectTabBar inspectTabBar(nodeId, tag);
    EXPECT_EQ(inspectTabBar.nodeId_, nodeId);
    EXPECT_EQ(inspectTabBar.tag_, tag);
}

/**
 * @tc.name: InspectTabBarTest002
 * @tc.desc: InspectTabBar::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectTabBarTest, InspectTabBarTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    uint16_t typeNum = 6;
    DeviceType deviceType = SystemProperties::GetDeviceType();
    for (uint16_t i = 0; i < typeNum; i++) {
        InspectTabBar inspectTabBar(nodeId, tag);
        auto attrsSize = inspectTabBar.attrs_.size();
        auto stylesSize = inspectTabBar.styles_.size();
        SystemProperties::SetDeviceType(static_cast<DeviceType>(i));
        inspectTabBar.PackAttrAndStyle();
        CheckTabBarAttrAndStyle(inspectTabBar, attrsSize, stylesSize);
    }
    SystemProperties::SetDeviceType(deviceType);
}
} // namespace OHOS::Ace::Framework
