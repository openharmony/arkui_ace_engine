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
#ifndef TEST_UNITTEST_CORE_MANAGER_SAFE_AREA_MANAGER_TEST_NG_H
#define TEST_UNITTEST_CORE_MANAGER_SAFE_AREA_MANAGER_TEST_NG_H

#include "gtest/gtest.h"
#define protected public
#define private public
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/checkbox/checkbox_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "frameworks/core/components_ng/manager/safe_area/safe_area_manager.h"
#include "frameworks/core/components_ng/pattern/navigation/navigation_pattern.h"
#include "frameworks/core/components_ng/pattern/navrouter/navdestination_pattern.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
namespace {
constexpr double DISPLAY_WIDTH = 720;
constexpr double DISPLAY_HEIGHT = 1280;
constexpr double SYSTEM_LEFT_START = 0.0f;
constexpr double SYSTEM_LEFT_END = 30.0f;
constexpr double SYSTEM_RIGHT_START = DISPLAY_WIDTH - 30.0f;
constexpr double SYSTEM_RIGHT_END = DISPLAY_WIDTH - 0.0f;
constexpr double SYSTEM_TOP_START = 0.0f;
constexpr double SYSTEM_TOP_END = 30.0f;
constexpr double SYSTEM_BOTTOM_START = DISPLAY_HEIGHT - 30.0f;
constexpr double SYSTEM_BOTTOM_END = DISPLAY_HEIGHT - 0.0f;
constexpr double CUTOUT_LEFT_START = 10.0f;
constexpr double CUTOUT_LEFT_END = 40.0f;
constexpr double CUTOUT_RIGHT_START = DISPLAY_WIDTH - 40.0f;
constexpr double CUTOUT_RIGHT_END = DISPLAY_WIDTH - 10.0f;
constexpr double CUTOUT_TOP_START = 20.0f;
constexpr double CUTOUT_TOP_END = 50.0f;
constexpr double CUTOUT_BOTTOM_START = DISPLAY_HEIGHT - 50.0f;
constexpr double CUTOUT_BOTTOM_END = DISPLAY_HEIGHT - 20.0f;
constexpr double CUTOUT_WITH_ROOT_LEFT_START = 0.0f;
constexpr double CUTOUT_WITH_ROOT_LEFT_END = CUTOUT_LEFT_END;
constexpr double CUTOUT_WITH_ROOT_RIGHT_START = CUTOUT_RIGHT_START;
constexpr double CUTOUT_WITH_ROOT_RIGHT_END = DISPLAY_WIDTH;
constexpr double CUTOUT_WITH_ROOT_TOP_START = 0.0f;
constexpr double CUTOUT_WITH_ROOT_TOP_END = CUTOUT_TOP_END;
constexpr double CUTOUT_WITH_ROOT_BOTTOM_START = CUTOUT_BOTTOM_START;
constexpr double CUTOUT_WITH_ROOT_BOTTOM_END = DISPLAY_HEIGHT;
constexpr double NAV_LEFT_START = 20.0f;
constexpr double NAV_LEFT_END = 50.0f;
constexpr double NAV_RIGHT_START = DISPLAY_WIDTH - 50.0f;
constexpr double NAV_RIGHT_END = DISPLAY_WIDTH - 20.0f;
constexpr double NAV_TOP_START = 40.0f;
constexpr double NAV_TOP_END = 70.0f;
constexpr double NAV_BOTTOM_START = DISPLAY_HEIGHT - 70.0f;
constexpr double NAV_BOTTOM_END = DISPLAY_HEIGHT - 40.0f;
constexpr double KEYBOARD_HEIGHT = 420.0f;
} // namespace

class SafeAreaManagerTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

    void SetUp() override;
    void TearDown() override;
    struct Rect {
        float left;
        float right;
        float top;
        float bottom;
    };

    void CommonExpectEQ(const Rect& s1, const Rect& s2);
    RefPtr<SafeAreaManager> safeAreaManager_;
    NG::SafeAreaInsets cutoutArea =
        NG::SafeAreaInsets({ CUTOUT_LEFT_START, CUTOUT_LEFT_END }, { CUTOUT_TOP_START, CUTOUT_TOP_END },
            { CUTOUT_RIGHT_START, CUTOUT_RIGHT_END }, { CUTOUT_BOTTOM_START, CUTOUT_BOTTOM_END });

    NG::SafeAreaInsets systemArea =
        NG::SafeAreaInsets({ SYSTEM_LEFT_START, SYSTEM_LEFT_END }, { SYSTEM_TOP_START, SYSTEM_TOP_END },
            { SYSTEM_RIGHT_START, SYSTEM_RIGHT_END }, { SYSTEM_BOTTOM_START, SYSTEM_BOTTOM_END });

    NG::SafeAreaInsets navArea = NG::SafeAreaInsets({ NAV_LEFT_START, NAV_LEFT_END }, { NAV_TOP_START, NAV_TOP_END },
        { NAV_RIGHT_START, NAV_RIGHT_END }, { NAV_BOTTOM_START, NAV_BOTTOM_END });
    NG::SafeAreaInsets cutoutAreaNotValid =
        NG::SafeAreaInsets({ CUTOUT_LEFT_END, CUTOUT_LEFT_START }, { CUTOUT_TOP_END, CUTOUT_TOP_START },
            { CUTOUT_RIGHT_END, CUTOUT_RIGHT_START }, { CUTOUT_BOTTOM_END, CUTOUT_BOTTOM_START });

    NG::SafeAreaInsets systemAreaNotValid =
        NG::SafeAreaInsets({ SYSTEM_LEFT_END, SYSTEM_LEFT_START }, { SYSTEM_TOP_END, SYSTEM_TOP_START },
            { SYSTEM_RIGHT_END, SYSTEM_RIGHT_START }, { SYSTEM_BOTTOM_END, SYSTEM_BOTTOM_START });

    NG::SafeAreaInsets navAreaNotValid = NG::SafeAreaInsets({ NAV_LEFT_END, NAV_LEFT_START },
        { NAV_TOP_END, NAV_TOP_START }, { NAV_RIGHT_END, NAV_RIGHT_START }, { NAV_BOTTOM_END, NAV_BOTTOM_START });

    NG::SafeAreaInsets cutoutAreaWithRoot =
        NG::SafeAreaInsets({ CUTOUT_WITH_ROOT_LEFT_START, CUTOUT_WITH_ROOT_LEFT_END },
            { CUTOUT_WITH_ROOT_TOP_START, CUTOUT_WITH_ROOT_TOP_END },
            { CUTOUT_WITH_ROOT_RIGHT_START, CUTOUT_WITH_ROOT_RIGHT_END },
            { CUTOUT_WITH_ROOT_BOTTOM_START, CUTOUT_WITH_ROOT_BOTTOM_END });
};

inline void SafeAreaManagerTest::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}

inline void SafeAreaManagerTest::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

inline void SafeAreaManagerTest::SetUp()
{
    safeAreaManager_ = Referenced::MakeRefPtr<SafeAreaManager>();
    safeAreaManager_->SetUseCutout(true);
}

inline void SafeAreaManagerTest::TearDown()
{
    safeAreaManager_ = nullptr;
}

inline void SafeAreaManagerTest::CommonExpectEQ(const Rect& s1, const Rect& s2)
{
    EXPECT_EQ(s1.left, s2.left);
    EXPECT_EQ(s1.right, s2.right);
    EXPECT_EQ(s1.top, s2.top);
    EXPECT_EQ(s1.bottom, s2.bottom);
}
} // namespace OHOS::Ace::NG

#endif // TEST_UNITTEST_CORE_MANAGER_SAFE_AREA_MANAGER_TEST_NG_H