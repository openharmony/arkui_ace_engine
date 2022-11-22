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

#include "frameworks/core/accessibility/js_inspector/inspect_progress.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectProgressTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};

    void CheckProgressAttrAndStyle(InspectProgress& inspectProgress, uint16_t attrsSize, uint16_t stylesSize)
    {
        uint16_t attrsSizeInsert = 5;
        uint16_t stylesSizeInsert = 1;
        DeviceType deviceType = SystemProperties::GetDeviceType();
        EXPECT_EQ(inspectProgress.attrs_["type"], "horizontal");
        EXPECT_EQ(inspectProgress.attrs_["focusable"], "true");
        EXPECT_EQ(inspectProgress.attrs_["percent"], "0");
        EXPECT_EQ(inspectProgress.attrs_["secondarypercent"], "0");
        EXPECT_EQ(inspectProgress.attrs_["clockwise"], "true");
        if (deviceType == DeviceType::PHONE) {
            EXPECT_EQ(inspectProgress.styles_["color"], "#ff007dff");
            stylesSizeInsert++;
        } else if (deviceType == DeviceType::TV) {
            EXPECT_EQ(inspectProgress.styles_["color"], "#e5ffffff");
            stylesSizeInsert++;
        } else if (deviceType == DeviceType::WATCH) {
            EXPECT_EQ(inspectProgress.styles_["color"], "#ff45a5ff");
            stylesSizeInsert++;
        }
        EXPECT_EQ(inspectProgress.styles_["stroke-width"], "4px");
        EXPECT_EQ(inspectProgress.styles_.find("background-size"), inspectProgress.styles_.end());
        EXPECT_EQ(inspectProgress.styles_.find("background-repeat"), inspectProgress.styles_.end());
        EXPECT_EQ(inspectProgress.styles_.find("background-position"), inspectProgress.styles_.end());
        EXPECT_EQ(inspectProgress.attrs_.size(), attrsSize + attrsSizeInsert);
        EXPECT_EQ(inspectProgress.styles_.size(), stylesSize + stylesSizeInsert);
    }
};

/**
 * @tc.name: InspectProgressTest001
 * @tc.desc: InspectProgress::InspectProgress
 * @tc.type: FUNC
 */
HWTEST_F(InspectProgressTest, InspectProgressTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectProgress inspectProgress(nodeId, tag);
    EXPECT_EQ(inspectProgress.nodeId_, nodeId);
    EXPECT_EQ(inspectProgress.tag_, tag);
}

/**
 * @tc.name: InspectProgressTest002
 * @tc.desc: InspectProgress::PackAttrAndStyle-PHONE
 * @tc.type: FUNC
 */
HWTEST_F(InspectProgressTest, InspectProgressTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectProgress inspectProgress(nodeId, tag);
    auto attrsSize = inspectProgress.attrs_.size();
    auto stylesSize = inspectProgress.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    inspectProgress.PackAttrAndStyle();
    CheckProgressAttrAndStyle(inspectProgress, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectProgressTest003
 * @tc.desc: InspectProgress::PackAttrAndStyle-TV
 * @tc.type: FUNC
 */
HWTEST_F(InspectProgressTest, InspectProgressTest003, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectProgress inspectProgress(nodeId, tag);
    auto attrsSize = inspectProgress.attrs_.size();
    auto stylesSize = inspectProgress.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::TV);
    inspectProgress.PackAttrAndStyle();
    CheckProgressAttrAndStyle(inspectProgress, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectProgressTest004
 * @tc.desc: InspectProgress::PackAttrAndStyle-WATCH
 * @tc.type: FUNC
 */
HWTEST_F(InspectProgressTest, InspectProgressTest004, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectProgress inspectProgress(nodeId, tag);
    auto attrsSize = inspectProgress.attrs_.size();
    auto stylesSize = inspectProgress.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::WATCH);
    inspectProgress.PackAttrAndStyle();
    CheckProgressAttrAndStyle(inspectProgress, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectProgressTest005
 * @tc.desc: InspectProgress::PackAttrAndStyle-CAR
 * @tc.type: FUNC
 */
HWTEST_F(InspectProgressTest, InspectProgressTest005, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectProgress inspectProgress(nodeId, tag);
    auto attrsSize = inspectProgress.attrs_.size();
    auto stylesSize = inspectProgress.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::CAR);
    inspectProgress.PackAttrAndStyle();
    CheckProgressAttrAndStyle(inspectProgress, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectProgressTest006
 * @tc.desc: InspectProgress::PackAttrAndStyle-TABLET
 * @tc.type: FUNC
 */
HWTEST_F(InspectProgressTest, InspectProgressTest006, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectProgress inspectProgress(nodeId, tag);
    auto attrsSize = inspectProgress.attrs_.size();
    auto stylesSize = inspectProgress.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::TABLET);
    inspectProgress.PackAttrAndStyle();
    CheckProgressAttrAndStyle(inspectProgress, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectProgressTest007
 * @tc.desc: InspectProgress::PackAttrAndStyle-UNKNOWN
 * @tc.type: FUNC
 */
HWTEST_F(InspectProgressTest, InspectProgressTest007, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectProgress inspectProgress(nodeId, tag);
    auto attrsSize = inspectProgress.attrs_.size();
    auto stylesSize = inspectProgress.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::UNKNOWN);
    inspectProgress.PackAttrAndStyle();
    CheckProgressAttrAndStyle(inspectProgress, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}
} // namespace OHOS::Ace::Framework
