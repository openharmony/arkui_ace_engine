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

#include "frameworks/core/accessibility/js_inspector/inspect_refresh.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectRefreshTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};

    void CheckRefreshAttrAndStyle(InspectRefresh& inspectRefresh, uint16_t attrsSize, uint16_t stylesSize)
    {
        uint16_t attrsSizeInsert = 5;
        uint16_t stylesSizeInsert = 3;
        uint16_t insertTwo = 2;
        DeviceType deviceType = SystemProperties::GetDeviceType();
        EXPECT_EQ(inspectRefresh.attrs_["refreshing"], "false");
        EXPECT_EQ(inspectRefresh.attrs_["type"], "auto");
        EXPECT_EQ(inspectRefresh.attrs_["lasttime"], "false");
        if (deviceType == DeviceType::PHONE) {
            EXPECT_EQ(inspectRefresh.attrs_["friction"], "42");
            attrsSizeInsert++;
        } else if (deviceType == DeviceType::WATCH) {
            EXPECT_EQ(inspectRefresh.styles_["friction"], "62");
            stylesSizeInsert++;
        }
        EXPECT_EQ(inspectRefresh.attrs_["disabled"], "false");
        EXPECT_EQ(inspectRefresh.attrs_["focusable"], "true");
        if (deviceType == DeviceType::PHONE) {
            EXPECT_EQ(inspectRefresh.styles_["background-color"], "white");
            EXPECT_EQ(inspectRefresh.styles_["progress-color"], "black");
            stylesSizeInsert += insertTwo;
        } else {
            EXPECT_EQ(inspectRefresh.styles_["background-color"], "black");
            EXPECT_EQ(inspectRefresh.styles_["progress-color"], "white");
            stylesSizeInsert += insertTwo;
        }
        EXPECT_EQ(inspectRefresh.styles_["min-width"], "0");
        EXPECT_EQ(inspectRefresh.styles_["min-height"], "0");
        EXPECT_EQ(inspectRefresh.styles_["box-shadow"], "0");
        EXPECT_EQ(inspectRefresh.attrs_.size(), attrsSize + attrsSizeInsert);
        EXPECT_EQ(inspectRefresh.styles_.size(), stylesSize + stylesSizeInsert);
    }
};

/**
 * @tc.name: InspectRefreshTest001
 * @tc.desc: InspectRefresh::InspectRefresh
 * @tc.type: FUNC
 */
HWTEST_F(InspectRefreshTest, InspectRefreshTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectRefresh inspectRefresh(nodeId, tag);
    EXPECT_EQ(inspectRefresh.nodeId_, nodeId);
    EXPECT_EQ(inspectRefresh.tag_, tag);
}

/**
 * @tc.name: InspectRefreshTest002
 * @tc.desc: InspectRefresh::PackAttrAndStyle-PHONE
 * @tc.type: FUNC
 */
HWTEST_F(InspectRefreshTest, InspectRefreshTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectRefresh inspectRefresh(nodeId, tag);
    auto attrsSize = inspectRefresh.attrs_.size();
    auto stylesSize = inspectRefresh.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    inspectRefresh.PackAttrAndStyle();
    CheckRefreshAttrAndStyle(inspectRefresh, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectRefreshTest003
 * @tc.desc: InspectRefresh::PackAttrAndStyle-TV
 * @tc.type: FUNC
 */
HWTEST_F(InspectRefreshTest, InspectRefreshTest003, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectRefresh inspectRefresh(nodeId, tag);
    auto attrsSize = inspectRefresh.attrs_.size();
    auto stylesSize = inspectRefresh.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::TV);
    inspectRefresh.PackAttrAndStyle();
    CheckRefreshAttrAndStyle(inspectRefresh, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectRefreshTest004
 * @tc.desc: InspectRefresh::PackAttrAndStyle-WATCH
 * @tc.type: FUNC
 */
HWTEST_F(InspectRefreshTest, InspectRefreshTest004, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectRefresh inspectRefresh(nodeId, tag);
    auto attrsSize = inspectRefresh.attrs_.size();
    auto stylesSize = inspectRefresh.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::WATCH);
    inspectRefresh.PackAttrAndStyle();
    CheckRefreshAttrAndStyle(inspectRefresh, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectRefreshTest005
 * @tc.desc: InspectRefresh::PackAttrAndStyle-CAR
 * @tc.type: FUNC
 */
HWTEST_F(InspectRefreshTest, InspectRefreshTest005, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectRefresh inspectRefresh(nodeId, tag);
    auto attrsSize = inspectRefresh.attrs_.size();
    auto stylesSize = inspectRefresh.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::CAR);
    inspectRefresh.PackAttrAndStyle();
    CheckRefreshAttrAndStyle(inspectRefresh, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectRefreshTest006
 * @tc.desc: InspectRefresh::PackAttrAndStyle-TABLET
 * @tc.type: FUNC
 */
HWTEST_F(InspectRefreshTest, InspectRefreshTest006, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectRefresh inspectRefresh(nodeId, tag);
    auto attrsSize = inspectRefresh.attrs_.size();
    auto stylesSize = inspectRefresh.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::TABLET);
    inspectRefresh.PackAttrAndStyle();
    CheckRefreshAttrAndStyle(inspectRefresh, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectRefreshTest007
 * @tc.desc: InspectRefresh::PackAttrAndStyle-UNKNOWN
 * @tc.type: FUNC
 */
HWTEST_F(InspectRefreshTest, InspectRefreshTest007, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectRefresh inspectRefresh(nodeId, tag);
    auto attrsSize = inspectRefresh.attrs_.size();
    auto stylesSize = inspectRefresh.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::UNKNOWN);
    inspectRefresh.PackAttrAndStyle();
    CheckRefreshAttrAndStyle(inspectRefresh, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}
} // namespace OHOS::Ace::Framework
