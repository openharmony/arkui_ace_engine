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

#include <chrono>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#define private public
#define protected public
#include "base/memory/ace_type.h"
#include "core/components_ng/pattern/select_overlay/magnifier_controller.h"
#undef private
#undef protected

#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class MagnifierVelocityTddTest : public testing::Test {
public:
    static inline int32_t backupContainerApiVersion_ = 0;
    static inline int32_t backupMinPlatformVersion_ = 0;
    static inline int32_t backupApplicationApiVersion_ = 0;

    static void SetUpTestCase()
    {
        MockPipelineContext::SetUp();
        MockContainer::SetUp();
        MockContainer::Current()->SetTaskExecutor(AceType::MakeRefPtr<MockTaskExecutor>());
        backupContainerApiVersion_ = MockContainer::Current()->GetApiTargetVersion();
        backupMinPlatformVersion_ = MockPipelineContext::GetCurrent()->GetMinPlatformVersion();
        backupApplicationApiVersion_ = AceApplicationInfo::GetInstance().GetApiTargetVersion();
        MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
        MockPipelineContext::GetCurrent()->SetMinPlatformVersion(
            static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
        AceApplicationInfo::GetInstance().SetApiTargetVersion(
            static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    }

    static void TearDownTestCase()
    {
        MockContainer::Current()->SetApiTargetVersion(backupContainerApiVersion_);
        MockPipelineContext::GetCurrent()->SetMinPlatformVersion(backupMinPlatformVersion_);
        AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApplicationApiVersion_);
        MockPipelineContext::TearDown();
        MockContainer::TearDown();
    }

    RefPtr<MagnifierController> CreateController()
    {
        auto pattern = AceType::MakeRefPtr<Pattern>();
        return AceType::MakeRefPtr<MagnifierController>(WeakPtr<Pattern>(pattern));
    }

    void VerifyMoveOnlyBuildVelocityCases()
    {
        {
            auto controller = CreateController();
            controller->ResetTouchInfo();
            auto time1 = TimeStamp(std::chrono::milliseconds(10));
            auto time2 = TimeStamp(std::chrono::milliseconds(20));
            controller->UpdateTouchVelocity(OffsetF(10.0f, 10.0f), time1, TouchType::MOVE);
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            controller->UpdateTouchVelocity(OffsetF(50.0f, 10.0f), time2, TouchType::MOVE);
            EXPECT_GT(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->ResetTouchInfo();
            auto time1 = TimeStamp(std::chrono::milliseconds(11));
            auto time2 = TimeStamp(std::chrono::milliseconds(23));
            controller->UpdateTouchVelocity(OffsetF(20.0f, 8.0f), time1, TouchType::MOVE);
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            controller->UpdateTouchVelocity(OffsetF(60.0f, 8.0f), time2, TouchType::MOVE);
            EXPECT_GT(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->ResetTouchInfo();
            auto time1 = TimeStamp(std::chrono::milliseconds(13));
            auto time2 = TimeStamp(std::chrono::milliseconds(28));
            controller->UpdateTouchVelocity(OffsetF(30.0f, 12.0f), time1, TouchType::MOVE);
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            controller->UpdateTouchVelocity(OffsetF(90.0f, 12.0f), time2, TouchType::MOVE);
            EXPECT_GT(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->ResetTouchInfo();
            auto time1 = TimeStamp(std::chrono::milliseconds(14));
            auto time2 = TimeStamp(std::chrono::milliseconds(30));
            controller->UpdateTouchVelocity(OffsetF(15.0f, 15.0f), time1, TouchType::MOVE);
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            controller->UpdateTouchVelocity(OffsetF(75.0f, 15.0f), time2, TouchType::MOVE);
            EXPECT_GT(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->ResetTouchInfo();
            auto time1 = TimeStamp(std::chrono::milliseconds(15));
            auto time2 = TimeStamp(std::chrono::milliseconds(35));
            controller->UpdateTouchVelocity(OffsetF(18.0f, 6.0f), time1, TouchType::MOVE);
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            controller->UpdateTouchVelocity(OffsetF(70.0f, 6.0f), time2, TouchType::MOVE);
            EXPECT_GT(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->ResetTouchInfo();
            auto time1 = TimeStamp(std::chrono::milliseconds(16));
            auto time2 = TimeStamp(std::chrono::milliseconds(40));
            controller->UpdateTouchVelocity(OffsetF(12.0f, 3.0f), time1, TouchType::MOVE);
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            controller->UpdateTouchVelocity(OffsetF(62.0f, 3.0f), time2, TouchType::MOVE);
            EXPECT_GT(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->ResetTouchInfo();
            auto time1 = TimeStamp(std::chrono::milliseconds(17));
            auto time2 = TimeStamp(std::chrono::milliseconds(41));
            controller->UpdateTouchVelocity(OffsetF(6.0f, 1.0f), time1, TouchType::MOVE);
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            controller->UpdateTouchVelocity(OffsetF(36.0f, 1.0f), time2, TouchType::MOVE);
            EXPECT_GT(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->ResetTouchInfo();
            auto time1 = TimeStamp(std::chrono::milliseconds(21));
            auto time2 = TimeStamp(std::chrono::milliseconds(44));
            controller->UpdateTouchVelocity(OffsetF(22.0f, 11.0f), time1, TouchType::MOVE);
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            controller->UpdateTouchVelocity(OffsetF(82.0f, 11.0f), time2, TouchType::MOVE);
            EXPECT_GT(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->ResetTouchInfo();
            auto time1 = TimeStamp(std::chrono::milliseconds(25));
            auto time2 = TimeStamp(std::chrono::milliseconds(55));
            controller->UpdateTouchVelocity(OffsetF(8.0f, 4.0f), time1, TouchType::MOVE);
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            controller->UpdateTouchVelocity(OffsetF(68.0f, 4.0f), time2, TouchType::MOVE);
            EXPECT_GT(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->ResetTouchInfo();
            auto time1 = TimeStamp(std::chrono::milliseconds(31));
            auto time2 = TimeStamp(std::chrono::milliseconds(61));
            controller->UpdateTouchVelocity(OffsetF(13.0f, 5.0f), time1, TouchType::MOVE);
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            controller->UpdateTouchVelocity(OffsetF(53.0f, 5.0f), time2, TouchType::MOVE);
            EXPECT_GT(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->ResetTouchInfo();
            auto time1 = TimeStamp(std::chrono::milliseconds(35));
            auto time2 = TimeStamp(std::chrono::milliseconds(70));
            controller->UpdateTouchVelocity(OffsetF(28.0f, 9.0f), time1, TouchType::MOVE);
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            controller->UpdateTouchVelocity(OffsetF(98.0f, 9.0f), time2, TouchType::MOVE);
            EXPECT_GT(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->ResetTouchInfo();
            auto time1 = TimeStamp(std::chrono::milliseconds(40));
            auto time2 = TimeStamp(std::chrono::milliseconds(80));
            controller->UpdateTouchVelocity(OffsetF(45.0f, 18.0f), time1, TouchType::MOVE);
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            controller->UpdateTouchVelocity(OffsetF(105.0f, 18.0f), time2, TouchType::MOVE);
            EXPECT_GT(controller->touchVelocityX_, 0.0f);
        }
    }

    void VerifyMoveOnlyNegativeVelocityCases()
    {
        {
            auto controller = CreateController();
            controller->ResetTouchInfo();
            auto time1 = TimeStamp(std::chrono::milliseconds(10));
            auto time2 = TimeStamp(std::chrono::milliseconds(20));
            controller->UpdateTouchVelocity(OffsetF(70.0f, 10.0f), time1, TouchType::MOVE);
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            controller->UpdateTouchVelocity(OffsetF(10.0f, 10.0f), time2, TouchType::MOVE);
            EXPECT_LT(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->ResetTouchInfo();
            auto time1 = TimeStamp(std::chrono::milliseconds(12));
            auto time2 = TimeStamp(std::chrono::milliseconds(24));
            controller->UpdateTouchVelocity(OffsetF(66.0f, 8.0f), time1, TouchType::MOVE);
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            controller->UpdateTouchVelocity(OffsetF(16.0f, 8.0f), time2, TouchType::MOVE);
            EXPECT_LT(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->ResetTouchInfo();
            auto time1 = TimeStamp(std::chrono::milliseconds(14));
            auto time2 = TimeStamp(std::chrono::milliseconds(28));
            controller->UpdateTouchVelocity(OffsetF(88.0f, 12.0f), time1, TouchType::MOVE);
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            controller->UpdateTouchVelocity(OffsetF(28.0f, 12.0f), time2, TouchType::MOVE);
            EXPECT_LT(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->ResetTouchInfo();
            auto time1 = TimeStamp(std::chrono::milliseconds(16));
            auto time2 = TimeStamp(std::chrono::milliseconds(32));
            controller->UpdateTouchVelocity(OffsetF(54.0f, 15.0f), time1, TouchType::MOVE);
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            controller->UpdateTouchVelocity(OffsetF(14.0f, 15.0f), time2, TouchType::MOVE);
            EXPECT_LT(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->ResetTouchInfo();
            auto time1 = TimeStamp(std::chrono::milliseconds(18));
            auto time2 = TimeStamp(std::chrono::milliseconds(38));
            controller->UpdateTouchVelocity(OffsetF(80.0f, 6.0f), time1, TouchType::MOVE);
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            controller->UpdateTouchVelocity(OffsetF(20.0f, 6.0f), time2, TouchType::MOVE);
            EXPECT_LT(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->ResetTouchInfo();
            auto time1 = TimeStamp(std::chrono::milliseconds(20));
            auto time2 = TimeStamp(std::chrono::milliseconds(45));
            controller->UpdateTouchVelocity(OffsetF(72.0f, 3.0f), time1, TouchType::MOVE);
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            controller->UpdateTouchVelocity(OffsetF(32.0f, 3.0f), time2, TouchType::MOVE);
            EXPECT_LT(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->ResetTouchInfo();
            auto time1 = TimeStamp(std::chrono::milliseconds(24));
            auto time2 = TimeStamp(std::chrono::milliseconds(54));
            controller->UpdateTouchVelocity(OffsetF(50.0f, 1.0f), time1, TouchType::MOVE);
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            controller->UpdateTouchVelocity(OffsetF(0.0f, 1.0f), time2, TouchType::MOVE);
            EXPECT_LT(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->ResetTouchInfo();
            auto time1 = TimeStamp(std::chrono::milliseconds(26));
            auto time2 = TimeStamp(std::chrono::milliseconds(60));
            controller->UpdateTouchVelocity(OffsetF(95.0f, 11.0f), time1, TouchType::MOVE);
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            controller->UpdateTouchVelocity(OffsetF(35.0f, 11.0f), time2, TouchType::MOVE);
            EXPECT_LT(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->ResetTouchInfo();
            auto time1 = TimeStamp(std::chrono::milliseconds(30));
            auto time2 = TimeStamp(std::chrono::milliseconds(63));
            controller->UpdateTouchVelocity(OffsetF(58.0f, 4.0f), time1, TouchType::MOVE);
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            controller->UpdateTouchVelocity(OffsetF(18.0f, 4.0f), time2, TouchType::MOVE);
            EXPECT_LT(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->ResetTouchInfo();
            auto time1 = TimeStamp(std::chrono::milliseconds(32));
            auto time2 = TimeStamp(std::chrono::milliseconds(68));
            controller->UpdateTouchVelocity(OffsetF(78.0f, 5.0f), time1, TouchType::MOVE);
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            controller->UpdateTouchVelocity(OffsetF(8.0f, 5.0f), time2, TouchType::MOVE);
            EXPECT_LT(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->ResetTouchInfo();
            auto time1 = TimeStamp(std::chrono::milliseconds(36));
            auto time2 = TimeStamp(std::chrono::milliseconds(72));
            controller->UpdateTouchVelocity(OffsetF(91.0f, 9.0f), time1, TouchType::MOVE);
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            controller->UpdateTouchVelocity(OffsetF(41.0f, 9.0f), time2, TouchType::MOVE);
            EXPECT_LT(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->ResetTouchInfo();
            auto time1 = TimeStamp(std::chrono::milliseconds(40));
            auto time2 = TimeStamp(std::chrono::milliseconds(78));
            controller->UpdateTouchVelocity(OffsetF(110.0f, 18.0f), time1, TouchType::MOVE);
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            controller->UpdateTouchVelocity(OffsetF(50.0f, 18.0f), time2, TouchType::MOVE);
            EXPECT_LT(controller->touchVelocityX_, 0.0f);
        }
    }

    void VerifyDownResetAndUnknownCases()
    {
        {
            auto controller = CreateController();
            auto time0 = TimeStamp(std::chrono::milliseconds(0));
            auto time1 = TimeStamp(std::chrono::milliseconds(10));
            auto time2 = TimeStamp(std::chrono::milliseconds(20));
            controller->UpdateTouchVelocity(OffsetF(0.0f, 0.0f), time0, TouchType::DOWN);
            controller->UpdateTouchVelocity(OffsetF(40.0f, 0.0f), time1, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(80.0f, 0.0f), time2, TouchType::MOVE);
            EXPECT_GT(controller->touchVelocityX_, 0.0f);
            controller->UpdateTouchVelocity(OffsetF(100.0f, 0.0f), time2, TouchType::DOWN);
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            auto time0 = TimeStamp(std::chrono::milliseconds(1));
            auto time1 = TimeStamp(std::chrono::milliseconds(11));
            auto time2 = TimeStamp(std::chrono::milliseconds(21));
            controller->UpdateTouchVelocity(OffsetF(4.0f, 1.0f), time0, TouchType::DOWN);
            controller->UpdateTouchVelocity(OffsetF(44.0f, 1.0f), time1, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(84.0f, 1.0f), time2, TouchType::MOVE);
            EXPECT_GT(controller->touchVelocityX_, 0.0f);
            controller->UpdateTouchVelocity(OffsetF(104.0f, 1.0f), time2, TouchType::DOWN);
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            auto time0 = TimeStamp(std::chrono::milliseconds(2));
            auto time1 = TimeStamp(std::chrono::milliseconds(12));
            auto time2 = TimeStamp(std::chrono::milliseconds(22));
            controller->UpdateTouchVelocity(OffsetF(8.0f, 2.0f), time0, TouchType::DOWN);
            controller->UpdateTouchVelocity(OffsetF(48.0f, 2.0f), time1, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(88.0f, 2.0f), time2, TouchType::MOVE);
            EXPECT_GT(controller->touchVelocityX_, 0.0f);
            controller->UpdateTouchVelocity(OffsetF(108.0f, 2.0f), time2, TouchType::DOWN);
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->touchVelocityX_ = 123.0f;
            auto time = TimeStamp(std::chrono::milliseconds(10));
            controller->UpdateTouchVelocity(OffsetF(20.0f, 2.0f), time, TouchType::UNKNOWN);
            EXPECT_EQ(controller->touchVelocityX_, 123.0f);
        }
        {
            auto controller = CreateController();
            controller->shapeProgress_ = 0.6f;
            auto time = TimeStamp(std::chrono::milliseconds(12));
            controller->UpdateTouchVelocity(OffsetF(22.0f, 2.0f), time, TouchType::UNKNOWN);
            EXPECT_EQ(controller->shapeProgress_, 0.6f);
        }
        {
            auto controller = CreateController();
            controller->touchVelocityX_ = -50.0f;
            auto time = TimeStamp(std::chrono::milliseconds(14));
            controller->UpdateTouchVelocity(OffsetF(24.0f, 2.0f), time, TouchType::UNKNOWN);
            EXPECT_EQ(controller->touchVelocityX_, -50.0f);
        }
        {
            auto controller = CreateController();
            controller->shapeProgress_ = 0.4f;
            auto time = TimeStamp(std::chrono::milliseconds(16));
            controller->UpdateTouchVelocity(OffsetF(26.0f, 2.0f), time, TouchType::UNKNOWN);
            EXPECT_EQ(controller->shapeProgress_, 0.4f);
        }
        {
            auto controller = CreateController();
            controller->touchVelocityX_ = 0.0f;
            auto time = TimeStamp(std::chrono::milliseconds(18));
            controller->UpdateTouchVelocity(OffsetF(28.0f, 2.0f), time, TouchType::UNKNOWN);
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->shapeProgress_ = 0.0f;
            auto time = TimeStamp(std::chrono::milliseconds(20));
            controller->UpdateTouchVelocity(OffsetF(30.0f, 2.0f), time, TouchType::UNKNOWN);
            EXPECT_EQ(controller->shapeProgress_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->touchVelocityX_ = 88.0f;
            auto time = TimeStamp(std::chrono::milliseconds(22));
            controller->UpdateTouchVelocity(OffsetF(32.0f, 2.0f), time, TouchType::UNKNOWN);
            EXPECT_EQ(controller->touchVelocityX_, 88.0f);
        }
        {
            auto controller = CreateController();
            controller->shapeProgress_ = 0.2f;
            auto time = TimeStamp(std::chrono::milliseconds(24));
            controller->UpdateTouchVelocity(OffsetF(34.0f, 2.0f), time, TouchType::UNKNOWN);
            EXPECT_EQ(controller->shapeProgress_, 0.2f);
        }
        {
            auto controller = CreateController();
            controller->touchVelocityX_ = -88.0f;
            auto time = TimeStamp(std::chrono::milliseconds(26));
            controller->UpdateTouchVelocity(OffsetF(36.0f, 2.0f), time, TouchType::UNKNOWN);
            EXPECT_EQ(controller->touchVelocityX_, -88.0f);
        }
    }

    void VerifyResetTouchInfoCases()
    {
        {
            auto controller = CreateController();
            auto time1 = TimeStamp(std::chrono::milliseconds(10));
            auto time2 = TimeStamp(std::chrono::milliseconds(20));
            controller->UpdateTouchVelocity(OffsetF(10.0f, 0.0f), time1, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(60.0f, 0.0f), time2, TouchType::MOVE);
            controller->shapeProgress_ = 0.5f;
            EXPECT_GT(controller->touchVelocityX_, 0.0f);
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            EXPECT_EQ(controller->shapeProgress_, 0.0f);
            EXPECT_TRUE(controller->velocityTracker_.GetDelta().IsZero());
        }
        {
            auto controller = CreateController();
            auto time1 = TimeStamp(std::chrono::milliseconds(15));
            auto time2 = TimeStamp(std::chrono::milliseconds(30));
            controller->UpdateTouchVelocity(OffsetF(20.0f, 1.0f), time1, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(80.0f, 1.0f), time2, TouchType::MOVE);
            controller->shapeProgress_ = 0.3f;
            EXPECT_GT(controller->touchVelocityX_, 0.0f);
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            EXPECT_EQ(controller->shapeProgress_, 0.0f);
            EXPECT_TRUE(controller->velocityTracker_.GetDelta().IsZero());
        }
        {
            auto controller = CreateController();
            auto time1 = TimeStamp(std::chrono::milliseconds(18));
            auto time2 = TimeStamp(std::chrono::milliseconds(36));
            controller->UpdateTouchVelocity(OffsetF(90.0f, 4.0f), time1, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(10.0f, 4.0f), time2, TouchType::MOVE);
            controller->shapeProgress_ = 0.7f;
            EXPECT_LT(controller->touchVelocityX_, 0.0f);
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            EXPECT_EQ(controller->shapeProgress_, 0.0f);
            EXPECT_TRUE(controller->velocityTracker_.GetDelta().IsZero());
        }
        {
            auto controller = CreateController();
            controller->shapeProgress_ = 1.0f;
            controller->touchVelocityX_ = 20.0f;
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            EXPECT_EQ(controller->shapeProgress_, 0.0f);
            EXPECT_TRUE(controller->velocityTracker_.GetDelta().IsZero());
        }
        {
            auto controller = CreateController();
            controller->shapeProgress_ = 0.9f;
            controller->touchVelocityX_ = -20.0f;
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            EXPECT_EQ(controller->shapeProgress_, 0.0f);
            EXPECT_TRUE(controller->velocityTracker_.GetDelta().IsZero());
        }
        {
            auto controller = CreateController();
            controller->shapeProgress_ = 0.1f;
            controller->touchVelocityX_ = 120.0f;
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            EXPECT_EQ(controller->shapeProgress_, 0.0f);
            EXPECT_TRUE(controller->velocityTracker_.GetDelta().IsZero());
        }
        {
            auto controller = CreateController();
            controller->shapeProgress_ = 0.8f;
            controller->touchVelocityX_ = -120.0f;
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            EXPECT_EQ(controller->shapeProgress_, 0.0f);
            EXPECT_TRUE(controller->velocityTracker_.GetDelta().IsZero());
        }
        {
            auto controller = CreateController();
            controller->shapeProgress_ = 0.25f;
            controller->touchVelocityX_ = 66.0f;
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            EXPECT_EQ(controller->shapeProgress_, 0.0f);
            EXPECT_TRUE(controller->velocityTracker_.GetDelta().IsZero());
        }
        {
            auto controller = CreateController();
            controller->shapeProgress_ = 0.35f;
            controller->touchVelocityX_ = -66.0f;
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            EXPECT_EQ(controller->shapeProgress_, 0.0f);
            EXPECT_TRUE(controller->velocityTracker_.GetDelta().IsZero());
        }
        {
            auto controller = CreateController();
            controller->shapeProgress_ = 0.45f;
            controller->touchVelocityX_ = 5.0f;
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            EXPECT_EQ(controller->shapeProgress_, 0.0f);
            EXPECT_TRUE(controller->velocityTracker_.GetDelta().IsZero());
        }
        {
            auto controller = CreateController();
            controller->shapeProgress_ = 0.55f;
            controller->touchVelocityX_ = -5.0f;
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            EXPECT_EQ(controller->shapeProgress_, 0.0f);
            EXPECT_TRUE(controller->velocityTracker_.GetDelta().IsZero());
        }
        {
            auto controller = CreateController();
            controller->shapeProgress_ = 0.65f;
            controller->touchVelocityX_ = 0.0f;
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            EXPECT_EQ(controller->shapeProgress_, 0.0f);
            EXPECT_TRUE(controller->velocityTracker_.GetDelta().IsZero());
        }
    }

    void VerifyUpAndCancelCases()
    {
        {
            auto controller = CreateController();
            auto time1 = TimeStamp(std::chrono::milliseconds(10));
            auto time2 = TimeStamp(std::chrono::milliseconds(20));
            auto time3 = TimeStamp(std::chrono::milliseconds(35));
            controller->UpdateTouchVelocity(OffsetF(10.0f, 0.0f), time1, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(50.0f, 0.0f), time2, TouchType::MOVE);
            EXPECT_GT(controller->touchVelocityX_, 0.0f);
            controller->UpdateTouchVelocity(OffsetF(90.0f, 0.0f), time3, TouchType::UP);
            EXPECT_GT(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            auto time1 = TimeStamp(std::chrono::milliseconds(11));
            auto time2 = TimeStamp(std::chrono::milliseconds(22));
            auto time3 = TimeStamp(std::chrono::milliseconds(33));
            controller->UpdateTouchVelocity(OffsetF(12.0f, 1.0f), time1, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(52.0f, 1.0f), time2, TouchType::MOVE);
            EXPECT_GT(controller->touchVelocityX_, 0.0f);
            controller->UpdateTouchVelocity(OffsetF(92.0f, 1.0f), time3, TouchType::CANCEL);
            EXPECT_GT(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            auto time1 = TimeStamp(std::chrono::milliseconds(12));
            auto time2 = TimeStamp(std::chrono::milliseconds(24));
            auto time3 = TimeStamp(std::chrono::milliseconds(36));
            controller->UpdateTouchVelocity(OffsetF(90.0f, 2.0f), time1, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(30.0f, 2.0f), time2, TouchType::MOVE);
            EXPECT_LT(controller->touchVelocityX_, 0.0f);
            controller->UpdateTouchVelocity(OffsetF(10.0f, 2.0f), time3, TouchType::UP);
            EXPECT_LT(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            auto time1 = TimeStamp(std::chrono::milliseconds(13));
            auto time2 = TimeStamp(std::chrono::milliseconds(26));
            auto time3 = TimeStamp(std::chrono::milliseconds(39));
            controller->UpdateTouchVelocity(OffsetF(88.0f, 3.0f), time1, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(28.0f, 3.0f), time2, TouchType::MOVE);
            EXPECT_LT(controller->touchVelocityX_, 0.0f);
            controller->UpdateTouchVelocity(OffsetF(8.0f, 3.0f), time3, TouchType::CANCEL);
            EXPECT_LT(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            auto time1 = TimeStamp(std::chrono::milliseconds(14));
            auto time2 = TimeStamp(std::chrono::milliseconds(28));
            auto time3 = TimeStamp(std::chrono::milliseconds(42));
            controller->UpdateTouchVelocity(OffsetF(18.0f, 4.0f), time1, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(78.0f, 4.0f), time2, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(88.0f, 4.0f), time3, TouchType::UP);
            EXPECT_GT(controller->touchVelocityX_, 0.0f);
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            auto time1 = TimeStamp(std::chrono::milliseconds(15));
            auto time2 = TimeStamp(std::chrono::milliseconds(30));
            auto time3 = TimeStamp(std::chrono::milliseconds(45));
            controller->UpdateTouchVelocity(OffsetF(24.0f, 5.0f), time1, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(84.0f, 5.0f), time2, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(94.0f, 5.0f), time3, TouchType::CANCEL);
            EXPECT_GT(controller->touchVelocityX_, 0.0f);
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            auto time1 = TimeStamp(std::chrono::milliseconds(16));
            auto time2 = TimeStamp(std::chrono::milliseconds(32));
            auto time3 = TimeStamp(std::chrono::milliseconds(48));
            controller->UpdateTouchVelocity(OffsetF(76.0f, 6.0f), time1, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(26.0f, 6.0f), time2, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(16.0f, 6.0f), time3, TouchType::UP);
            EXPECT_LT(controller->touchVelocityX_, 0.0f);
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            auto time1 = TimeStamp(std::chrono::milliseconds(17));
            auto time2 = TimeStamp(std::chrono::milliseconds(34));
            auto time3 = TimeStamp(std::chrono::milliseconds(51));
            controller->UpdateTouchVelocity(OffsetF(74.0f, 7.0f), time1, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(24.0f, 7.0f), time2, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(14.0f, 7.0f), time3, TouchType::CANCEL);
            EXPECT_LT(controller->touchVelocityX_, 0.0f);
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            auto time1 = TimeStamp(std::chrono::milliseconds(18));
            auto time2 = TimeStamp(std::chrono::milliseconds(36));
            auto time3 = TimeStamp(std::chrono::milliseconds(54));
            controller->UpdateTouchVelocity(OffsetF(8.0f, 8.0f), time1, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(18.0f, 8.0f), time2, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(28.0f, 8.0f), time3, TouchType::UP);
            EXPECT_GT(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            auto time1 = TimeStamp(std::chrono::milliseconds(19));
            auto time2 = TimeStamp(std::chrono::milliseconds(38));
            auto time3 = TimeStamp(std::chrono::milliseconds(57));
            controller->UpdateTouchVelocity(OffsetF(28.0f, 9.0f), time1, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(18.0f, 9.0f), time2, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(8.0f, 9.0f), time3, TouchType::CANCEL);
            EXPECT_LT(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            auto time1 = TimeStamp(std::chrono::milliseconds(20));
            auto time2 = TimeStamp(std::chrono::milliseconds(40));
            auto time3 = TimeStamp(std::chrono::milliseconds(60));
            controller->UpdateTouchVelocity(OffsetF(30.0f, 10.0f), time1, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(90.0f, 10.0f), time2, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(120.0f, 10.0f), time3, TouchType::UP);
            EXPECT_GT(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            auto time1 = TimeStamp(std::chrono::milliseconds(21));
            auto time2 = TimeStamp(std::chrono::milliseconds(42));
            auto time3 = TimeStamp(std::chrono::milliseconds(63));
            controller->UpdateTouchVelocity(OffsetF(100.0f, 11.0f), time1, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(40.0f, 11.0f), time2, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(20.0f, 11.0f), time3, TouchType::CANCEL);
            EXPECT_LT(controller->touchVelocityX_, 0.0f);
        }
    }

    void VerifyMixedSequenceCases()
    {
        {
            auto controller = CreateController();
            auto time0 = TimeStamp(std::chrono::milliseconds(0));
            auto time1 = TimeStamp(std::chrono::milliseconds(10));
            auto time2 = TimeStamp(std::chrono::milliseconds(20));
            auto time3 = TimeStamp(std::chrono::milliseconds(30));
            controller->UpdateTouchVelocity(OffsetF(0.0f, 0.0f), time0, TouchType::DOWN);
            controller->UpdateTouchVelocity(OffsetF(20.0f, 0.0f), time1, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(60.0f, 0.0f), time2, TouchType::MOVE);
            EXPECT_GT(controller->touchVelocityX_, 0.0f);
            controller->UpdateTouchVelocity(OffsetF(30.0f, 0.0f), time3, TouchType::MOVE);
            EXPECT_LT(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            auto time0 = TimeStamp(std::chrono::milliseconds(1));
            auto time1 = TimeStamp(std::chrono::milliseconds(11));
            auto time2 = TimeStamp(std::chrono::milliseconds(21));
            auto time3 = TimeStamp(std::chrono::milliseconds(31));
            controller->UpdateTouchVelocity(OffsetF(5.0f, 1.0f), time0, TouchType::DOWN);
            controller->UpdateTouchVelocity(OffsetF(25.0f, 1.0f), time1, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(65.0f, 1.0f), time2, TouchType::MOVE);
            EXPECT_GT(controller->touchVelocityX_, 0.0f);
            controller->UpdateTouchVelocity(OffsetF(35.0f, 1.0f), time3, TouchType::MOVE);
            EXPECT_LT(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            auto time0 = TimeStamp(std::chrono::milliseconds(2));
            auto time1 = TimeStamp(std::chrono::milliseconds(12));
            auto time2 = TimeStamp(std::chrono::milliseconds(22));
            auto time3 = TimeStamp(std::chrono::milliseconds(32));
            controller->UpdateTouchVelocity(OffsetF(10.0f, 2.0f), time0, TouchType::DOWN);
            controller->UpdateTouchVelocity(OffsetF(30.0f, 2.0f), time1, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(70.0f, 2.0f), time2, TouchType::MOVE);
            EXPECT_GT(controller->touchVelocityX_, 0.0f);
            controller->UpdateTouchVelocity(OffsetF(40.0f, 2.0f), time3, TouchType::MOVE);
            EXPECT_LT(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            auto time0 = TimeStamp(std::chrono::milliseconds(3));
            auto time1 = TimeStamp(std::chrono::milliseconds(13));
            auto time2 = TimeStamp(std::chrono::milliseconds(23));
            auto time3 = TimeStamp(std::chrono::milliseconds(33));
            controller->UpdateTouchVelocity(OffsetF(15.0f, 3.0f), time0, TouchType::DOWN);
            controller->UpdateTouchVelocity(OffsetF(35.0f, 3.0f), time1, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(75.0f, 3.0f), time2, TouchType::MOVE);
            EXPECT_GT(controller->touchVelocityX_, 0.0f);
            controller->UpdateTouchVelocity(OffsetF(45.0f, 3.0f), time3, TouchType::MOVE);
            EXPECT_LT(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            auto time0 = TimeStamp(std::chrono::milliseconds(4));
            auto time1 = TimeStamp(std::chrono::milliseconds(14));
            auto time2 = TimeStamp(std::chrono::milliseconds(24));
            auto time3 = TimeStamp(std::chrono::milliseconds(34));
            controller->UpdateTouchVelocity(OffsetF(20.0f, 4.0f), time0, TouchType::DOWN);
            controller->UpdateTouchVelocity(OffsetF(40.0f, 4.0f), time1, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(80.0f, 4.0f), time2, TouchType::MOVE);
            EXPECT_GT(controller->touchVelocityX_, 0.0f);
            controller->UpdateTouchVelocity(OffsetF(50.0f, 4.0f), time3, TouchType::MOVE);
            EXPECT_LT(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            auto time0 = TimeStamp(std::chrono::milliseconds(5));
            auto time1 = TimeStamp(std::chrono::milliseconds(15));
            auto time2 = TimeStamp(std::chrono::milliseconds(25));
            auto time3 = TimeStamp(std::chrono::milliseconds(35));
            controller->UpdateTouchVelocity(OffsetF(25.0f, 5.0f), time0, TouchType::DOWN);
            controller->UpdateTouchVelocity(OffsetF(45.0f, 5.0f), time1, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(85.0f, 5.0f), time2, TouchType::MOVE);
            EXPECT_GT(controller->touchVelocityX_, 0.0f);
            controller->UpdateTouchVelocity(OffsetF(55.0f, 5.0f), time3, TouchType::MOVE);
            EXPECT_LT(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            auto time0 = TimeStamp(std::chrono::milliseconds(6));
            auto time1 = TimeStamp(std::chrono::milliseconds(16));
            auto time2 = TimeStamp(std::chrono::milliseconds(26));
            auto time3 = TimeStamp(std::chrono::milliseconds(36));
            controller->UpdateTouchVelocity(OffsetF(30.0f, 6.0f), time0, TouchType::DOWN);
            controller->UpdateTouchVelocity(OffsetF(50.0f, 6.0f), time1, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(90.0f, 6.0f), time2, TouchType::MOVE);
            EXPECT_GT(controller->touchVelocityX_, 0.0f);
            controller->UpdateTouchVelocity(OffsetF(60.0f, 6.0f), time3, TouchType::MOVE);
            EXPECT_LT(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            auto time0 = TimeStamp(std::chrono::milliseconds(7));
            auto time1 = TimeStamp(std::chrono::milliseconds(17));
            auto time2 = TimeStamp(std::chrono::milliseconds(27));
            auto time3 = TimeStamp(std::chrono::milliseconds(37));
            controller->UpdateTouchVelocity(OffsetF(35.0f, 7.0f), time0, TouchType::DOWN);
            controller->UpdateTouchVelocity(OffsetF(55.0f, 7.0f), time1, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(95.0f, 7.0f), time2, TouchType::MOVE);
            EXPECT_GT(controller->touchVelocityX_, 0.0f);
            controller->UpdateTouchVelocity(OffsetF(65.0f, 7.0f), time3, TouchType::MOVE);
            EXPECT_LT(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            auto time0 = TimeStamp(std::chrono::milliseconds(8));
            auto time1 = TimeStamp(std::chrono::milliseconds(18));
            auto time2 = TimeStamp(std::chrono::milliseconds(28));
            auto time3 = TimeStamp(std::chrono::milliseconds(38));
            controller->UpdateTouchVelocity(OffsetF(40.0f, 8.0f), time0, TouchType::DOWN);
            controller->UpdateTouchVelocity(OffsetF(60.0f, 8.0f), time1, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(100.0f, 8.0f), time2, TouchType::MOVE);
            EXPECT_GT(controller->touchVelocityX_, 0.0f);
            controller->UpdateTouchVelocity(OffsetF(70.0f, 8.0f), time3, TouchType::MOVE);
            EXPECT_LT(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            auto time0 = TimeStamp(std::chrono::milliseconds(9));
            auto time1 = TimeStamp(std::chrono::milliseconds(19));
            auto time2 = TimeStamp(std::chrono::milliseconds(29));
            auto time3 = TimeStamp(std::chrono::milliseconds(39));
            controller->UpdateTouchVelocity(OffsetF(45.0f, 9.0f), time0, TouchType::DOWN);
            controller->UpdateTouchVelocity(OffsetF(65.0f, 9.0f), time1, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(105.0f, 9.0f), time2, TouchType::MOVE);
            EXPECT_GT(controller->touchVelocityX_, 0.0f);
            controller->UpdateTouchVelocity(OffsetF(75.0f, 9.0f), time3, TouchType::MOVE);
            EXPECT_LT(controller->touchVelocityX_, 0.0f);
        }
    }

    void VerifyRepeatedResetAfterEndCases()
    {
        {
            auto controller = CreateController();
            auto time1 = TimeStamp(std::chrono::milliseconds(10));
            auto time2 = TimeStamp(std::chrono::milliseconds(20));
            auto time3 = TimeStamp(std::chrono::milliseconds(30));
            controller->UpdateTouchVelocity(OffsetF(10.0f, 0.0f), time1, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(70.0f, 0.0f), time2, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(90.0f, 0.0f), time3, TouchType::UP);
            EXPECT_GT(controller->touchVelocityX_, 0.0f);
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            auto time1 = TimeStamp(std::chrono::milliseconds(11));
            auto time2 = TimeStamp(std::chrono::milliseconds(22));
            auto time3 = TimeStamp(std::chrono::milliseconds(33));
            controller->UpdateTouchVelocity(OffsetF(90.0f, 1.0f), time1, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(30.0f, 1.0f), time2, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(10.0f, 1.0f), time3, TouchType::CANCEL);
            EXPECT_LT(controller->touchVelocityX_, 0.0f);
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            auto time1 = TimeStamp(std::chrono::milliseconds(12));
            auto time2 = TimeStamp(std::chrono::milliseconds(24));
            auto time3 = TimeStamp(std::chrono::milliseconds(36));
            controller->UpdateTouchVelocity(OffsetF(20.0f, 2.0f), time1, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(80.0f, 2.0f), time2, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(120.0f, 2.0f), time3, TouchType::UP);
            EXPECT_GT(controller->touchVelocityX_, 0.0f);
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            auto time1 = TimeStamp(std::chrono::milliseconds(13));
            auto time2 = TimeStamp(std::chrono::milliseconds(26));
            auto time3 = TimeStamp(std::chrono::milliseconds(39));
            controller->UpdateTouchVelocity(OffsetF(100.0f, 3.0f), time1, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(40.0f, 3.0f), time2, TouchType::MOVE);
            controller->UpdateTouchVelocity(OffsetF(20.0f, 3.0f), time3, TouchType::CANCEL);
            EXPECT_LT(controller->touchVelocityX_, 0.0f);
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->shapeProgress_ = 0.1f;
            controller->touchVelocityX_ = 1.0f;
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->shapeProgress_, 0.0f);
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            controller->shapeProgress_ = 0.2f;
            controller->touchVelocityX_ = 2.0f;
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->shapeProgress_, 0.0f);
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->shapeProgress_ = 0.3f;
            controller->touchVelocityX_ = 3.0f;
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->shapeProgress_, 0.0f);
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            controller->shapeProgress_ = 0.4f;
            controller->touchVelocityX_ = 4.0f;
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->shapeProgress_, 0.0f);
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->shapeProgress_ = 0.5f;
            controller->touchVelocityX_ = 5.0f;
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->shapeProgress_, 0.0f);
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            controller->shapeProgress_ = 0.6f;
            controller->touchVelocityX_ = 6.0f;
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->shapeProgress_, 0.0f);
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->shapeProgress_ = 0.7f;
            controller->touchVelocityX_ = 7.0f;
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->shapeProgress_, 0.0f);
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            controller->shapeProgress_ = 0.8f;
            controller->touchVelocityX_ = 8.0f;
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->shapeProgress_, 0.0f);
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->shapeProgress_ = 0.9f;
            controller->touchVelocityX_ = 9.0f;
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->shapeProgress_, 0.0f);
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            controller->shapeProgress_ = 1.0f;
            controller->touchVelocityX_ = 10.0f;
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->shapeProgress_, 0.0f);
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->shapeProgress_ = 0.33f;
            controller->touchVelocityX_ = -10.0f;
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->shapeProgress_, 0.0f);
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            controller->shapeProgress_ = 0.66f;
            controller->touchVelocityX_ = -20.0f;
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->shapeProgress_, 0.0f);
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
        }
    }

    void VerifyAdditionalIgnoreAndResetCases()
    {
        {
            auto controller = CreateController();
            controller->touchVelocityX_ = 11.0f;
            controller->shapeProgress_ = 0.11f;
            controller->UpdateTouchVelocity(OffsetF(1.0f, 1.0f), TimeStamp(std::chrono::milliseconds(1)),
                TouchType::UNKNOWN);
            EXPECT_EQ(controller->touchVelocityX_, 11.0f);
            EXPECT_EQ(controller->shapeProgress_, 0.11f);
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            EXPECT_EQ(controller->shapeProgress_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->touchVelocityX_ = 22.0f;
            controller->shapeProgress_ = 0.22f;
            controller->UpdateTouchVelocity(OffsetF(2.0f, 2.0f), TimeStamp(std::chrono::milliseconds(2)),
                TouchType::UNKNOWN);
            EXPECT_EQ(controller->touchVelocityX_, 22.0f);
            EXPECT_EQ(controller->shapeProgress_, 0.22f);
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            EXPECT_EQ(controller->shapeProgress_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->touchVelocityX_ = 33.0f;
            controller->shapeProgress_ = 0.33f;
            controller->UpdateTouchVelocity(OffsetF(3.0f, 3.0f), TimeStamp(std::chrono::milliseconds(3)),
                TouchType::UNKNOWN);
            EXPECT_EQ(controller->touchVelocityX_, 33.0f);
            EXPECT_EQ(controller->shapeProgress_, 0.33f);
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            EXPECT_EQ(controller->shapeProgress_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->touchVelocityX_ = 44.0f;
            controller->shapeProgress_ = 0.44f;
            controller->UpdateTouchVelocity(OffsetF(4.0f, 4.0f), TimeStamp(std::chrono::milliseconds(4)),
                TouchType::UNKNOWN);
            EXPECT_EQ(controller->touchVelocityX_, 44.0f);
            EXPECT_EQ(controller->shapeProgress_, 0.44f);
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            EXPECT_EQ(controller->shapeProgress_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->touchVelocityX_ = 55.0f;
            controller->shapeProgress_ = 0.55f;
            controller->UpdateTouchVelocity(OffsetF(5.0f, 5.0f), TimeStamp(std::chrono::milliseconds(5)),
                TouchType::UNKNOWN);
            EXPECT_EQ(controller->touchVelocityX_, 55.0f);
            EXPECT_EQ(controller->shapeProgress_, 0.55f);
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            EXPECT_EQ(controller->shapeProgress_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->touchVelocityX_ = 66.0f;
            controller->shapeProgress_ = 0.66f;
            controller->UpdateTouchVelocity(OffsetF(6.0f, 6.0f), TimeStamp(std::chrono::milliseconds(6)),
                TouchType::UNKNOWN);
            EXPECT_EQ(controller->touchVelocityX_, 66.0f);
            EXPECT_EQ(controller->shapeProgress_, 0.66f);
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            EXPECT_EQ(controller->shapeProgress_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->touchVelocityX_ = 77.0f;
            controller->shapeProgress_ = 0.77f;
            controller->UpdateTouchVelocity(OffsetF(7.0f, 7.0f), TimeStamp(std::chrono::milliseconds(7)),
                TouchType::UNKNOWN);
            EXPECT_EQ(controller->touchVelocityX_, 77.0f);
            EXPECT_EQ(controller->shapeProgress_, 0.77f);
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            EXPECT_EQ(controller->shapeProgress_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->touchVelocityX_ = 88.0f;
            controller->shapeProgress_ = 0.88f;
            controller->UpdateTouchVelocity(OffsetF(8.0f, 8.0f), TimeStamp(std::chrono::milliseconds(8)),
                TouchType::UNKNOWN);
            EXPECT_EQ(controller->touchVelocityX_, 88.0f);
            EXPECT_EQ(controller->shapeProgress_, 0.88f);
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            EXPECT_EQ(controller->shapeProgress_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->touchVelocityX_ = 99.0f;
            controller->shapeProgress_ = 0.99f;
            controller->UpdateTouchVelocity(OffsetF(9.0f, 9.0f), TimeStamp(std::chrono::milliseconds(9)),
                TouchType::UNKNOWN);
            EXPECT_EQ(controller->touchVelocityX_, 99.0f);
            EXPECT_EQ(controller->shapeProgress_, 0.99f);
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            EXPECT_EQ(controller->shapeProgress_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->touchVelocityX_ = 111.0f;
            controller->shapeProgress_ = 0.15f;
            controller->UpdateTouchVelocity(OffsetF(11.0f, 11.0f), TimeStamp(std::chrono::milliseconds(11)),
                TouchType::UNKNOWN);
            EXPECT_EQ(controller->touchVelocityX_, 111.0f);
            EXPECT_EQ(controller->shapeProgress_, 0.15f);
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            EXPECT_EQ(controller->shapeProgress_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->touchVelocityX_ = -11.0f;
            controller->shapeProgress_ = 0.21f;
            controller->UpdateTouchVelocity(OffsetF(12.0f, 12.0f), TimeStamp(std::chrono::milliseconds(12)),
                TouchType::UNKNOWN);
            EXPECT_EQ(controller->touchVelocityX_, -11.0f);
            EXPECT_EQ(controller->shapeProgress_, 0.21f);
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            EXPECT_EQ(controller->shapeProgress_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->touchVelocityX_ = -22.0f;
            controller->shapeProgress_ = 0.31f;
            controller->UpdateTouchVelocity(OffsetF(13.0f, 13.0f), TimeStamp(std::chrono::milliseconds(13)),
                TouchType::UNKNOWN);
            EXPECT_EQ(controller->touchVelocityX_, -22.0f);
            EXPECT_EQ(controller->shapeProgress_, 0.31f);
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            EXPECT_EQ(controller->shapeProgress_, 0.0f);
        }
    }

    void VerifyResetIdempotentCases()
    {
        {
            auto controller = CreateController();
            controller->touchVelocityX_ = 1.0f;
            controller->shapeProgress_ = 0.1f;
            controller->ResetTouchInfo();
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            EXPECT_EQ(controller->shapeProgress_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->touchVelocityX_ = -1.0f;
            controller->shapeProgress_ = 0.2f;
            controller->ResetTouchInfo();
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            EXPECT_EQ(controller->shapeProgress_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->touchVelocityX_ = 50.0f;
            controller->shapeProgress_ = 0.3f;
            controller->ResetTouchInfo();
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            EXPECT_EQ(controller->shapeProgress_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->touchVelocityX_ = -50.0f;
            controller->shapeProgress_ = 0.4f;
            controller->ResetTouchInfo();
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            EXPECT_EQ(controller->shapeProgress_, 0.0f);
        }
        {
            auto controller = CreateController();
            controller->ResetTouchInfo();
            EXPECT_EQ(controller->touchVelocityX_, 0.0f);
            EXPECT_EQ(controller->shapeProgress_, 0.0f);
        }
    }
};

/**
 * @tc.name: MagnifierVelocityTdd_MoveOnlyPositive001
 * @tc.desc: test move-only positive velocity sequences
 * @tc.type: FUNC
 */
HWTEST_F(MagnifierVelocityTddTest, MagnifierVelocityTdd_MoveOnlyPositive001, TestSize.Level1)
{
    VerifyMoveOnlyBuildVelocityCases();
}

/**
 * @tc.name: MagnifierVelocityTdd_MoveOnlyNegative001
 * @tc.desc: test move-only negative velocity sequences
 * @tc.type: FUNC
 */
HWTEST_F(MagnifierVelocityTddTest, MagnifierVelocityTdd_MoveOnlyNegative001, TestSize.Level1)
{
    VerifyMoveOnlyNegativeVelocityCases();
}

/**
 * @tc.name: MagnifierVelocityTdd_DownResetAndUnknown001
 * @tc.desc: test down reset and unknown ignore sequences
 * @tc.type: FUNC
 */
HWTEST_F(MagnifierVelocityTddTest, MagnifierVelocityTdd_DownResetAndUnknown001, TestSize.Level1)
{
    VerifyDownResetAndUnknownCases();
}

/**
 * @tc.name: MagnifierVelocityTdd_ResetTouchInfo001
 * @tc.desc: test reset touch info clears velocity state sequences
 * @tc.type: FUNC
 */
HWTEST_F(MagnifierVelocityTddTest, MagnifierVelocityTdd_ResetTouchInfo001, TestSize.Level1)
{
    VerifyResetTouchInfoCases();
}

/**
 * @tc.name: MagnifierVelocityTdd_UpAndCancel001
 * @tc.desc: test up and cancel sequences for magnifier velocity tracking
 * @tc.type: FUNC
 */
HWTEST_F(MagnifierVelocityTddTest, MagnifierVelocityTdd_UpAndCancel001, TestSize.Level1)
{
    VerifyUpAndCancelCases();
}

/**
 * @tc.name: MagnifierVelocityTdd_MixedSequence001
 * @tc.desc: test mixed move direction sequences
 * @tc.type: FUNC
 */
HWTEST_F(MagnifierVelocityTddTest, MagnifierVelocityTdd_MixedSequence001, TestSize.Level1)
{
    VerifyMixedSequenceCases();
}

/**
 * @tc.name: MagnifierVelocityTdd_RepeatedResetAfterEnd001
 * @tc.desc: test repeated reset behavior after end sequences
 * @tc.type: FUNC
 */
HWTEST_F(MagnifierVelocityTddTest, MagnifierVelocityTdd_RepeatedResetAfterEnd001, TestSize.Level1)
{
    VerifyRepeatedResetAfterEndCases();
}

/**
 * @tc.name: MagnifierVelocityTdd_AdditionalIgnoreAndReset001
 * @tc.desc: test additional ignore and reset sequences
 * @tc.type: FUNC
 */
HWTEST_F(MagnifierVelocityTddTest, MagnifierVelocityTdd_AdditionalIgnoreAndReset001, TestSize.Level1)
{
    VerifyAdditionalIgnoreAndResetCases();
}

/**
 * @tc.name: MagnifierVelocityTdd_ResetIdempotent001
 * @tc.desc: test reset touch info idempotent sequences
 * @tc.type: FUNC
 */
HWTEST_F(MagnifierVelocityTddTest, MagnifierVelocityTdd_ResetIdempotent001, TestSize.Level1)
{
    VerifyResetIdempotentCases();
}
} // namespace OHOS::Ace::NG
