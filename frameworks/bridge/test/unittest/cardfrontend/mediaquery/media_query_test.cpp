/*
 * Copyright (c) 20212022 Huawei Device Co., Ltd.
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

#define private public
#include "frameworks/bridge/common/media_query/media_queryer.h"
#include "frameworks/bridge/common/media_query/media_query_info.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::Framework {
namespace {
constexpr int32_t ORIENTATION_LANDSCAPE = 1;
const std::string MEDIA_FEATURE_INFORMATION = "{\"width\":0,"
                                              "\"height\":0,"
                                              "\"aspect-ratio\":1,"
                                              "\"round-screen\":true,"
                                              "\"device-width\":100,"
                                              "\"device-height\":100,"
                                              "\"resolution\":1,"
                                              "\"orientation\":\"portrait\","
                                              "\"device-type\":\"phone\","
                                              "\"dark-mode\":false,"
                                              "\"api-version\":10,"
                                              "\"device-brand\":\"test_brand\"}";

const std::string PHONE_MEDIA_INFO = "{\"width\":0,"
                                     "\"height\":0,"
                                     "\"aspect-ratio\":1,"
                                     "\"round-screen\":true,"
                                     "\"device-width\":100,"
                                     "\"device-height\":100,"
                                     "\"resolution\":1,"
                                     "\"orientation\":\"portrait\","
                                     "\"device-type\":\"phone\","
                                     "\"dark-mode\":false,"
                                     "\"api-version\":9,"
                                     "\"isInit\":false}";

const std::string TV_MEDIA_INFO = "{\"width\":0,"
                                  "\"height\":0,"
                                  "\"aspect-ratio\":1,"
                                  "\"round-screen\":true,"
                                  "\"device-width\":100,"
                                  "\"device-height\":100,"
                                  "\"resolution\":1,"
                                  "\"orientation\":\"landscape\","
                                  "\"device-type\":\"tv\","
                                  "\"dark-mode\":false,"
                                  "\"api-version\":9,"
                                  "\"isInit\":false}";

const std::string CAR_MEDIA_INFO = "{\"width\":0,"
                                   "\"height\":0,"
                                   "\"aspect-ratio\":1,"
                                   "\"round-screen\":true,"
                                   "\"device-width\":100,"
                                   "\"device-height\":100,"
                                   "\"resolution\":1,"
                                   "\"orientation\":\"landscape\","
                                   "\"device-type\":\"car\","
                                   "\"dark-mode\":false,"
                                   "\"api-version\":9,"
                                   "\"isInit\":false}";

const std::string WATCH_MEDIA_INFO = "{\"width\":0,"
                                     "\"height\":0,"
                                     "\"aspect-ratio\":1,"
                                     "\"round-screen\":true,"
                                     "\"device-width\":100,"
                                     "\"device-height\":100,"
                                     "\"resolution\":1,"
                                     "\"orientation\":\"landscape\","
                                     "\"device-type\":\"wearable\","
                                     "\"dark-mode\":false,"
                                     "\"api-version\":9,"
                                     "\"isInit\":false}";

const std::string TABLET_MEDIA_INFO = "{\"width\":0,"
                                      "\"height\":0,"
                                      "\"aspect-ratio\":1,"
                                      "\"round-screen\":true,"
                                      "\"device-width\":100,"
                                      "\"device-height\":100,"
                                      "\"resolution\":1,"
                                      "\"orientation\":\"landscape\","
                                      "\"device-type\":\"tablet\","
                                      "\"dark-mode\":false,"
                                      "\"api-version\":9,"
                                      "\"isInit\":false}";
} // namespace

class MediaQueryTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
};

void MediaQueryTest::SetUpTestCase() {}
void MediaQueryTest::TearDownTestCase() {}
void MediaQueryTest::SetUp() {}
void MediaQueryTest::TearDown() {}

/**
 * @tc.name: MediaQueryTest001
 * @tc.desc: Verify that media query condition can match right result.
 * @tc.type: FUNC
 * @tc.require: issueI5MWTB
 */
HWTEST_F(MediaQueryTest, MediaQueryTest001, TestSize.Level1)
{
    OHOS::Ace::Framework::MediaFeature mediaFeature = JsonUtil::Create(true);
    mediaFeature->Put("width", 1500);
    mediaFeature->Put("device-type", "tv");
    mediaFeature->Put("round-screen", true);

    struct ConditionTestCase {
        std::string condition;
        bool result;
    };
    std::vector<ConditionTestCase> conditions = {
        { "(max-width: )", false },
        { "(min-width: 1000)", true },
        { "(width < 2000)", true },
        { "(width < 2000vp)", true },
        { "(width << 2000)", false },
        { "(1000 < width)", true },
        { "(1000 < width < 2000)", true },
        { "(round-screen: true) (device-type:tv)", false },
        { "screen and (round-screen: true) and (device-type:tv)", true },
        { "not screen and (round-screen: true) and (device-type:tv)", false },
        { "not screen and (round-screen: false) and (device-type:tv)", true },
        { "not screen and (round-screen: true) and (device-type:phone)", true },
        { "screen and (round-screen: false), (device-type:tv)", true },
        { "only screen and (1000 < width < 2000), (device-type:phone)", true },
        { "(device-height < 2000) and (device-width < 2000) and (round-screen: true) and (device-type:phone)", false },
        { "(device-height > 2000) or (device-width > 2000) or (round-screen: false) or (device-type:tv)", true },
        { "(round-screen: true) or (device-type:phone)", true },
        { "(round-screen: true), screen and (1000 < width < 2000), (device-type:phone)", false },
    };

    MediaQueryer mediaQueryer;
    for (const auto& item : conditions) {
        bool result = mediaQueryer.MatchCondition(item.condition, mediaFeature);
        ASSERT_EQ(result, item.result) << "condition = " << item.condition;
    }
}

/**
 * @tc.name: MediaQueryTest002
 * @tc.desc: Verify that media query condition can match right result.
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryTest, MediaQueryTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Input condition is empty.
     * @tc.expected: step1. Media query condition can not match right result.
     */
    OHOS::Ace::Framework::MediaFeature mediaFeature = JsonUtil::Create(true);
    mediaFeature->Put("device-type:phone", true);

    SystemProperties systemProperties;
    systemProperties.InitDeviceInfo(100, 100, 0, 1.0, true);
    systemProperties.paramDeviceType_ = "phone";
    systemProperties.apiVersion_ = "10";
    systemProperties.brand_ = "test_brand";
    systemProperties.SetDeviceType(DeviceType::PHONE);

    const std::string nullCondition = "";
    const std::string conditions = "{\"device-type:phone\":true}";
    MediaQueryer mediaQueryer;
    MediaQueryer::QueryHistory query = { conditions, true };
    mediaQueryer.queryHistories.insert({ conditions, query });
    bool result = mediaQueryer.MatchCondition(nullCondition, mediaFeature);
    ASSERT_EQ(result, false);
    auto mediaFeatureStr = mediaQueryer.GetMediaFeature()->ToString();
    ASSERT_EQ(mediaFeatureStr, MEDIA_FEATURE_INFORMATION);

    /**
     * @tc.steps: step2. Input the matching condition.
     * @tc.expected: step2. Media query condition can match right result.
     */
    result = mediaQueryer.MatchCondition(conditions, mediaFeature);
    ASSERT_EQ(result, true);

    /**
     * @tc.steps: step3. Width and height are not initialized.
     * And the query condition includes "width" or "height"
     * @tc.expected: step3. Media query condition can not match right result.
     */
    mediaFeature->Put("(min-width: 1000", true);
    result = mediaQueryer.MatchCondition(conditions, mediaFeature);
    ASSERT_EQ(result, false);
}

/**
 * @tc.name: MediaQueryTest003
 * @tc.desc: Get media query information as expect.
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryTest, MediaQueryTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize device information.
     * @tc.expected: step1. Get media query information as expect.
     */
    SystemProperties systemProperties;
    systemProperties.InitDeviceInfo(100, 100, 0, 1.0, true);
    MediaQueryInfo mediaQueryInfo;
    systemProperties.paramDeviceType_ = "phone";
    systemProperties.apiVersion_ = "9";
    systemProperties.SetDeviceType(DeviceType::PHONE);
    auto mediaQueryString = mediaQueryInfo.GetMediaQueryInfo();
    ASSERT_EQ(mediaQueryString, PHONE_MEDIA_INFO);

    /**
     * @tc.steps: step2. Device-type is "tv" and device-orientation is "landscape".
     * @tc.expected: step2. Get media query information as expect.
     */
    systemProperties.SetDeviceOrientation(ORIENTATION_LANDSCAPE);
    systemProperties.SetDeviceType(DeviceType::TV);
    mediaQueryString = mediaQueryInfo.GetMediaQueryInfo();
    ASSERT_EQ(mediaQueryString, TV_MEDIA_INFO);

    /**
     * @tc.steps: step3. Device-type is "car".
     * @tc.expected: step3. Get media query information as expect.
     */
    systemProperties.SetDeviceType(DeviceType::CAR);
    mediaQueryString = mediaQueryInfo.GetMediaQueryInfo();
    ASSERT_EQ(mediaQueryString, CAR_MEDIA_INFO);

    /**
     * @tc.steps: step4. Device-type is "wearable".
     * @tc.expected: step4. Get media query information as expect.
     */
    systemProperties.SetDeviceType(DeviceType::WATCH);
    mediaQueryString = mediaQueryInfo.GetMediaQueryInfo();
    ASSERT_EQ(mediaQueryString, WATCH_MEDIA_INFO);

    /**
     * @tc.steps: step5. Device-type is "tablet".
     * @tc.expected: step5. Get media query information as expect.
     */
    systemProperties.SetDeviceType(DeviceType::TABLET);
    mediaQueryString = mediaQueryInfo.GetMediaQueryInfo();
    ASSERT_EQ(mediaQueryString, TABLET_MEDIA_INFO);

    /**
     * @tc.steps: step6. Device-type param is "tablet".
     * @tc.expected: step6. Get media query information as expect.
     */
    systemProperties.paramDeviceType_ = "tablet";
    mediaQueryString = mediaQueryInfo.GetMediaQueryInfo();
    ASSERT_EQ(mediaQueryString, TABLET_MEDIA_INFO);
}
} // namespace OHOS::Ace::Framework
