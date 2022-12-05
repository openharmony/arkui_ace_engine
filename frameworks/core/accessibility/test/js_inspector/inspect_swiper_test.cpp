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

#include "frameworks/core/accessibility/js_inspector/inspect_swiper.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectSwiperTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};

    void CheckSwiperAttrAndStyle(InspectSwiper& inspectSwiper, uint16_t attrsSize, uint16_t stylesSize)
    {
        uint16_t attrsSizeInsert = 14;
        uint16_t stylesSizeInsert = 1;
        DeviceType deviceType = SystemProperties::GetDeviceType();
        EXPECT_EQ(inspectSwiper.attrs_["index"], "0");
        EXPECT_EQ(inspectSwiper.attrs_["autoplay"], "false");
        EXPECT_EQ(inspectSwiper.attrs_["interval"], "3000");
        EXPECT_EQ(inspectSwiper.attrs_["indicator"], "true");
        EXPECT_EQ(inspectSwiper.attrs_["digital"], "false");
        EXPECT_EQ(inspectSwiper.attrs_["indicatormask"], "false");
        EXPECT_EQ(inspectSwiper.attrs_["indicatordisabled"], "false");
        EXPECT_EQ(inspectSwiper.attrs_["loop"], "true");
        EXPECT_EQ(inspectSwiper.attrs_["vertical"], "false");
        EXPECT_EQ(inspectSwiper.attrs_["disabled"], "false");
        EXPECT_EQ(inspectSwiper.attrs_["focusable"], "true");
        EXPECT_EQ(inspectSwiper.attrs_["cachedsize"], "-1");
        EXPECT_EQ(inspectSwiper.attrs_["scrolleffect"], "spring");
        EXPECT_EQ(inspectSwiper.attrs_["displaymode"], "stretch");
        if (deviceType == DeviceType::PHONE) {
            EXPECT_EQ(inspectSwiper.styles_["indicator-selected-color"], "#ff007dff");
            stylesSizeInsert++;
        } else if (deviceType == DeviceType::TV || deviceType == DeviceType::WATCH) {
            EXPECT_EQ(inspectSwiper.styles_["indicator-selected-color"], "#ffffffff");
            stylesSizeInsert++;
        }
        EXPECT_EQ(inspectSwiper.styles_["indicator-size"], "4px");
        EXPECT_EQ(inspectSwiper.attrs_.size(), attrsSize + attrsSizeInsert);
        EXPECT_EQ(inspectSwiper.styles_.size(), stylesSize + stylesSizeInsert);
    }
};

/**
 * @tc.name: InspectSwiperTest001
 * @tc.desc: InspectSwiper::InspectSwiper
 * @tc.type: FUNC
 */
HWTEST_F(InspectSwiperTest, InspectSwiperTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSwiper inspectSwiper(nodeId, tag);
    EXPECT_EQ(inspectSwiper.nodeId_, nodeId);
    EXPECT_EQ(inspectSwiper.tag_, tag);
}

/**
 * @tc.name: InspectSwiperTest002
 * @tc.desc: InspectSwiper::PackAttrAndStyle-PHONE
 * @tc.type: FUNC
 */
HWTEST_F(InspectSwiperTest, InspectSwiperTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSwiper inspectSwiper(nodeId, tag);
    auto attrsSize = inspectSwiper.attrs_.size();
    auto stylesSize = inspectSwiper.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    inspectSwiper.PackAttrAndStyle();
    CheckSwiperAttrAndStyle(inspectSwiper, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectSwiperTest003
 * @tc.desc: InspectSwiper::PackAttrAndStyle-TV
 * @tc.type: FUNC
 */
HWTEST_F(InspectSwiperTest, InspectSwiperTest003, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSwiper inspectSwiper(nodeId, tag);
    auto attrsSize = inspectSwiper.attrs_.size();
    auto stylesSize = inspectSwiper.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::TV);
    inspectSwiper.PackAttrAndStyle();
    CheckSwiperAttrAndStyle(inspectSwiper, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectSwiperTest004
 * @tc.desc: InspectSwiper::PackAttrAndStyle-WATCH
 * @tc.type: FUNC
 */
HWTEST_F(InspectSwiperTest, InspectSwiperTest004, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSwiper inspectSwiper(nodeId, tag);
    auto attrsSize = inspectSwiper.attrs_.size();
    auto stylesSize = inspectSwiper.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::WATCH);
    inspectSwiper.PackAttrAndStyle();
    CheckSwiperAttrAndStyle(inspectSwiper, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectSwiperTest005
 * @tc.desc: InspectSwiper::PackAttrAndStyle-CAR
 * @tc.type: FUNC
 */
HWTEST_F(InspectSwiperTest, InspectSwiperTest005, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSwiper inspectSwiper(nodeId, tag);
    auto attrsSize = inspectSwiper.attrs_.size();
    auto stylesSize = inspectSwiper.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::CAR);
    inspectSwiper.PackAttrAndStyle();
    CheckSwiperAttrAndStyle(inspectSwiper, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectSwiperTest006
 * @tc.desc: InspectSwiper::PackAttrAndStyle-TABLET
 * @tc.type: FUNC
 */
HWTEST_F(InspectSwiperTest, InspectSwiperTest006, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSwiper inspectSwiper(nodeId, tag);
    auto attrsSize = inspectSwiper.attrs_.size();
    auto stylesSize = inspectSwiper.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::TABLET);
    inspectSwiper.PackAttrAndStyle();
    CheckSwiperAttrAndStyle(inspectSwiper, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectSwiperTest007
 * @tc.desc: InspectSwiper::PackAttrAndStyle-UNKNOWN
 * @tc.type: FUNC
 */
HWTEST_F(InspectSwiperTest, InspectSwiperTest007, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSwiper inspectSwiper(nodeId, tag);
    auto attrsSize = inspectSwiper.attrs_.size();
    auto stylesSize = inspectSwiper.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::UNKNOWN);
    inspectSwiper.PackAttrAndStyle();
    CheckSwiperAttrAndStyle(inspectSwiper, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}
} // namespace OHOS::Ace::Framework
