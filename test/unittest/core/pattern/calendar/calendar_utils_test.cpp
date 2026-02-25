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

#define private public
#define protected public
#include "core/components_ng/pattern/calendar_picker/calendar_dialog_view.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "core/components_ng/pattern/calendar/calendar_utils.h"
#include "test/mock/core/modifier/mock_calendar_picker_dialog_modifier.h"
using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
static constexpr double SMALL_SIZE = 100.0;
class CalendarUtilsTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() {};
    void TearDown() {};
private:
    static double rootWidth_;
    static double rootHeight_;
    static DeviceOrientation previousOrientation_;
};

double CalendarUtilsTest::rootWidth_ = 0.0;
double CalendarUtilsTest::rootHeight_ = 0.0;
DeviceOrientation CalendarUtilsTest::previousOrientation_ = DeviceOrientation::PORTRAIT;
void CalendarUtilsTest::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    rootHeight_ = MockPipelineContext::GetCurrent()->rootHeight_;
    rootWidth_ = MockPipelineContext::GetCurrent()->rootWidth_;
    previousOrientation_ = CalendarDialogView::previousOrientation_;
}

void CalendarUtilsTest::TearDownTestSuite()
{
    MockPipelineContext::GetCurrent()->rootHeight_ = rootHeight_;
    MockPipelineContext::GetCurrent()->rootWidth_ = rootWidth_;
    CalendarDialogView::previousOrientation_ = previousOrientation_;
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: CheckOrientationChange
 * @tc.desc: CheckOrientationChange Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarUtilsTest, CheckOrientationChange, TestSize.Level1)
{
    /**
     * @tc.step: step1. GetCalendarPickerDialogModifier is null, always true
     */
    NodeModifier::MockCalendarPickerDialogModifier::SetModifierNull(true);
    auto result = CalendarUtils::CheckOrientationChange();
    EXPECT_TRUE(result);
    
    /**
     * @tc.step: step2. default rootWith is 720, default rootHeight is 1280, and deviceHeightLimit is 640,
            always rootWith or rootHeight more than deviceHeightLimit
     */
    NodeModifier::MockCalendarPickerDialogModifier::SetModifierNull(false);
    if (SystemProperties::GetDeviceOrientation() != DeviceOrientation::PORTRAIT) {
        CalendarDialogView::previousOrientation_ = DeviceOrientation::PORTRAIT;
    }

    result = CalendarUtils::CheckOrientationChange();
    EXPECT_FALSE(result);

    CalendarDialogView::previousOrientation_ = DeviceOrientation::LANDSCAPE;
    result = CalendarUtils::CheckOrientationChange();
    EXPECT_FALSE(result);

    /**
     * @tc.step: step3 set rootWith or rootHeight less than deviceHeightLimit
     */
    MockPipelineContext::GetCurrent()->SetRootSize(SMALL_SIZE, SMALL_SIZE);
    result = CalendarUtils::CheckOrientationChange();
    EXPECT_TRUE(result);

    CalendarDialogView::previousOrientation_ = DeviceOrientation::PORTRAIT;
    result = CalendarUtils::CheckOrientationChange();
    EXPECT_TRUE(result);
}
} // namespace OHOS::Ace::NG