/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "adapter/ohos/entrance/ui_session/content_change_config_impl.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
constexpr int32_t MIN_REPORT_TIME = 120;
constexpr float TEXT_CONTENT_RATIO = 0.25f;
constexpr char IGNORE_EVENT_TYPE[] = R"({"scrollTo":true})";
constexpr int32_t MIN_WIDTH = 80;
constexpr int32_t MIN_HEIGHT = 90;
constexpr int32_t REPORT_DELAY_TIME = 500;

void WriteLegacyConfig(Parcel& parcel)
{
    ASSERT_TRUE(parcel.WriteInt32(MIN_REPORT_TIME));
    ASSERT_TRUE(parcel.WriteFloat(TEXT_CONTENT_RATIO));
    ASSERT_TRUE(parcel.WriteString(IGNORE_EVENT_TYPE));
    ASSERT_TRUE(parcel.WriteInt32(MIN_WIDTH));
    ASSERT_TRUE(parcel.WriteInt32(MIN_HEIGHT));
    ASSERT_TRUE(parcel.WriteInt32(REPORT_DELAY_TIME));
}
} // namespace

class ContentChangeConfigImplTest : public testing::Test {};

/**
 * @tc.name: ContentChangeConfigImplRoundTrip001
 * @tc.desc: Verify reportStartEvent is preserved by parcel marshalling.
 * @tc.type: FUNC
 */
HWTEST_F(ContentChangeConfigImplTest, ContentChangeConfigImplRoundTrip001, TestSize.Level1)
{
    ContentChangeConfig config;
    config.minReportTime = MIN_REPORT_TIME;
    config.textContentRatio = TEXT_CONTENT_RATIO;
    config.ignoreEventType = IGNORE_EVENT_TYPE;
    config.minWidth = MIN_WIDTH;
    config.minHeight = MIN_HEIGHT;
    config.reportDelayTime = REPORT_DELAY_TIME;
    config.reportStartEvent = true;
    ContentChangeConfigImpl configImpl(config);
    Parcel parcel;

    ASSERT_TRUE(configImpl.Marshalling(parcel));
    std::unique_ptr<ContentChangeConfigImpl> result(ContentChangeConfigImpl::Unmarshalling(parcel));
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(result->GetConfig().reportStartEvent);
}

/**
 * @tc.name: ContentChangeConfigImplLegacy001
 * @tc.desc: Verify a legacy parcel without reportStartEvent defaults to false.
 * @tc.type: FUNC
 */
HWTEST_F(ContentChangeConfigImplTest, ContentChangeConfigImplLegacy001, TestSize.Level1)
{
    Parcel parcel;
    WriteLegacyConfig(parcel);

    std::unique_ptr<ContentChangeConfigImpl> result(ContentChangeConfigImpl::Unmarshalling(parcel));
    ASSERT_NE(result, nullptr);
    auto config = result->GetConfig();
    EXPECT_EQ(config.minReportTime, MIN_REPORT_TIME);
    EXPECT_FLOAT_EQ(config.textContentRatio, TEXT_CONTENT_RATIO);
    EXPECT_EQ(config.ignoreEventType, IGNORE_EVENT_TYPE);
    EXPECT_EQ(config.minWidth, MIN_WIDTH);
    EXPECT_EQ(config.minHeight, MIN_HEIGHT);
    EXPECT_EQ(config.reportDelayTime, REPORT_DELAY_TIME);
    EXPECT_FALSE(config.reportStartEvent);
}
} // namespace OHOS::Ace
