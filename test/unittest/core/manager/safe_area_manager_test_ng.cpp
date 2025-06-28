/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#define protected public
#define private public

#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/checkbox/checkbox_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "frameworks/core/components_ng/manager/safe_area/safe_area_manager.h"
#include "frameworks/core/components_ng/pattern/navigation/navigation_pattern.h"
#include "frameworks/core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "test/mock/core/common/mock_container.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {

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
        NG::SafeAreaInsets({ CUTOUT_WITH_ROOT_LEFT_START, CUTOUT_WITH_ROOT_LEFT_END }, { CUTOUT_WITH_ROOT_TOP_START,
            CUTOUT_WITH_ROOT_TOP_END }, { CUTOUT_WITH_ROOT_RIGHT_START, CUTOUT_WITH_ROOT_RIGHT_END },
            { CUTOUT_WITH_ROOT_BOTTOM_START, CUTOUT_WITH_ROOT_BOTTOM_END });
};

void SafeAreaManagerTest::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}

void SafeAreaManagerTest::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

void SafeAreaManagerTest::SetUp()
{
    safeAreaManager_ = Referenced::MakeRefPtr<SafeAreaManager>();
    safeAreaManager_->SetUseCutout(true);
}

void SafeAreaManagerTest::TearDown()
{
    safeAreaManager_ = nullptr;
}

void SafeAreaManagerTest::CommonExpectEQ(const Rect& s1, const Rect& s2)
{
    EXPECT_EQ(s1.left, s2.left);
    EXPECT_EQ(s1.right, s2.right);
    EXPECT_EQ(s1.top, s2.top);
    EXPECT_EQ(s1.bottom, s2.bottom);
}

/**
 * @tc.name: IsSafeAreaValidTest
 * @tc.desc: Use IsSafeAreaValid and test.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, IsSafeAreaValidTest, TestSize.Level1)
{
    EXPECT_EQ(safeAreaManager_->IsIgnoreSafeArea(), false);
    EXPECT_EQ(safeAreaManager_->IsFullScreen(), false);
    EXPECT_EQ(safeAreaManager_->IsNeedAvoidWindow(), false);
    EXPECT_EQ(safeAreaManager_->IsSafeAreaValid(), false);

    auto res = safeAreaManager_->GetCutoutSafeArea();
    CommonExpectEQ(
        Rect { res.left_.start, res.right_.end, res.top_.start, res.bottom_.end }, Rect { 0.0f, 0.0f, 0.0f, 0.0f });
    res = safeAreaManager_->GetSafeArea();
    CommonExpectEQ(
        Rect { res.left_.start, res.right_.end, res.top_.start, res.bottom_.end }, Rect { 0.0f, 0.0f, 0.0f, 0.0f });
    res = safeAreaManager_->GetSafeAreaWithoutCutout();
    CommonExpectEQ(
        Rect { res.left_.start, res.right_.end, res.top_.start, res.bottom_.end }, Rect { 0.0f, 0.0f, 0.0f, 0.0f });
    res = safeAreaManager_->GetCombinedSafeArea(SafeAreaExpandOpts());
    CommonExpectEQ(
        Rect { res.left_.start, res.right_.end, res.top_.start, res.bottom_.end }, Rect { 0.0f, 0.0f, 0.0f, 0.0f });

    EXPECT_EQ(safeAreaManager_->SetIgnoreSafeArea(true), true);
    EXPECT_EQ(safeAreaManager_->SetIgnoreSafeArea(true), false);
    EXPECT_EQ(safeAreaManager_->IsSafeAreaValid(), false);
    EXPECT_EQ(safeAreaManager_->SetIgnoreSafeArea(false), true);

    EXPECT_EQ(safeAreaManager_->SetIsFullScreen(true), true);
    EXPECT_EQ(safeAreaManager_->SetIsFullScreen(true), false);
    EXPECT_EQ(safeAreaManager_->IsSafeAreaValid(), true);
    EXPECT_EQ(safeAreaManager_->SetIsFullScreen(false), true);

    EXPECT_EQ(safeAreaManager_->SetIsNeedAvoidWindow(true), true);
    EXPECT_EQ(safeAreaManager_->SetIsNeedAvoidWindow(true), false);
    EXPECT_EQ(safeAreaManager_->IsSafeAreaValid(), true);
    EXPECT_EQ(safeAreaManager_->SetIsNeedAvoidWindow(false), true);

    EXPECT_EQ(safeAreaManager_->SetIsFullScreen(true), true);
    EXPECT_EQ(safeAreaManager_->SetIsNeedAvoidWindow(true), true);
    EXPECT_EQ(safeAreaManager_->IsSafeAreaValid(), true);

    EXPECT_EQ(safeAreaManager_->IsAtomicService(), false);
    EXPECT_EQ(safeAreaManager_->SetIsAtomicService(true), true);
    EXPECT_EQ(safeAreaManager_->SetIsAtomicService(true), false);
    EXPECT_EQ(safeAreaManager_->IsAtomicService(), true);
}

/**
 * @tc.name: CutoutSafeAreaTest
 * @tc.desc: Use CutoutSafeArea and test.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, CutoutSafeAreaTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1 call UpdateCutoutSafeArea without rootSize params.
     * @tc.expected: cutout regions need to adjacent to edges.
     */
    safeAreaManager_->SetIsFullScreen(true);
    auto ret = safeAreaManager_->UpdateCutoutSafeArea(cutoutArea);
    EXPECT_EQ(ret, true);
    ret = safeAreaManager_->UpdateCutoutSafeArea(cutoutArea);
    EXPECT_EQ(ret, false);

    auto cutoutSafeArea = safeAreaManager_->GetCutoutSafeArea();
    EXPECT_EQ(cutoutSafeArea, cutoutAreaWithRoot);
    auto safeArea = safeAreaManager_->GetSafeArea();
    auto safeAreaWithoutProcess = safeAreaManager_->GetSafeAreaWithoutProcess();
    EXPECT_EQ(safeArea, safeAreaWithoutProcess);
    EXPECT_EQ(cutoutSafeArea, safeArea);

    CommonExpectEQ(Rect { safeArea.left_.start, safeArea.right_.end, safeArea.top_.start, safeArea.bottom_.end },
        Rect { 0.0f, DISPLAY_WIDTH, 0.0f, DISPLAY_HEIGHT });
    /**
     * @tc.steps: step2 call UpdateCutoutSafeArea with rootSize params.
     * @tc.expected: cutout regions need to adjacent to edges.
     */
    NG::OptionalSize<uint32_t> rootSize;
    rootSize.SetWidth(DISPLAY_WIDTH - 20);
    rootSize.SetHeight(DISPLAY_HEIGHT - 25);
    ret = safeAreaManager_->UpdateCutoutSafeArea(cutoutArea, rootSize);
    EXPECT_EQ(ret, true);
    safeArea = safeAreaManager_->GetSafeArea();
    CommonExpectEQ(Rect { safeArea.left_.start, safeArea.right_.end, safeArea.top_.start, safeArea.bottom_.end },
        Rect { 0.0f, DISPLAY_WIDTH - 20, 0.0f, DISPLAY_HEIGHT - 25 });
    /**
     * @tc.steps: step3 call UpdateCutoutSafeArea SafeAreaInsets with invalid params.
     * @tc.expected: cutout regions need to adjacent to edges.
     */
    ret = safeAreaManager_->UpdateCutoutSafeArea(cutoutAreaNotValid);
    EXPECT_EQ(ret, true);
    ret = safeAreaManager_->UpdateCutoutSafeArea(cutoutAreaNotValid);
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: SystemSafeAreaTest
 * @tc.desc: Use SystemSafeArea and test.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, SystemSafeAreaTest, TestSize.Level1)
{
    /**
     * @tc.steps: call UpdateSystemSafeAreaTest
     */
    safeAreaManager_->SetIsFullScreen(true);
    auto ret = safeAreaManager_->UpdateSystemSafeArea(systemArea);
    EXPECT_EQ(ret, true);
    ret = safeAreaManager_->UpdateSystemSafeArea(systemArea);
    EXPECT_EQ(ret, false);

    auto systemSafeArea = safeAreaManager_->GetSystemSafeArea();
    EXPECT_EQ(systemSafeArea, systemArea);

    auto safeArea = safeAreaManager_->GetSafeArea();
    auto safeAreaWithoutProcess = safeAreaManager_->GetSafeAreaWithoutProcess();
    EXPECT_EQ(safeArea, safeAreaWithoutProcess);
    EXPECT_EQ(systemSafeArea, safeArea);

    CommonExpectEQ(Rect { safeArea.left_.start, safeArea.right_.end, safeArea.top_.start, safeArea.bottom_.end },
        Rect { SYSTEM_LEFT_START, SYSTEM_RIGHT_END, SYSTEM_TOP_START, SYSTEM_BOTTOM_END });
}

/**
 * @tc.name: NavSafeAreaTest
 * @tc.desc: Use UpdateNavSafeArea and test.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, NavSafeAreaTest, TestSize.Level1)
{
    /**
     * @tc.steps: call UpdateNavSafeAreaTest
     */
    safeAreaManager_->SetIsFullScreen(true);
    auto ret = safeAreaManager_->UpdateNavSafeArea(navArea);
    EXPECT_EQ(ret, true);
    ret = safeAreaManager_->UpdateNavSafeArea(navArea);
    EXPECT_EQ(ret, false);

    auto safeArea = safeAreaManager_->GetSafeArea();
    auto safeAreaWithoutProcess = safeAreaManager_->GetSafeAreaWithoutProcess();
    EXPECT_EQ(safeArea, safeAreaWithoutProcess);

    CommonExpectEQ(Rect { safeArea.left_.start, safeArea.right_.end, safeArea.top_.start, safeArea.bottom_.end },
        Rect { NAV_LEFT_START, NAV_RIGHT_END, NAV_TOP_START, NAV_BOTTOM_END });
}

/**
 * @tc.name: UpdateKeyboardSafeAreaTest
 * @tc.desc: Use UpdateKeyboardSafeArea and test.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, UpdateKeyboardSafeAreaTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1 call UpdateKeyboardSafeAreaTest with valid systemArea
     */
    safeAreaManager_->SetIsFullScreen(true);
    safeAreaManager_->UpdateSystemSafeArea(systemArea);
    auto ret = safeAreaManager_->UpdateKeyboardSafeArea(KEYBOARD_HEIGHT);
    EXPECT_EQ(ret, true);
    ret = safeAreaManager_->UpdateKeyboardSafeArea(KEYBOARD_HEIGHT);
    EXPECT_EQ(ret, false);
    auto keyboardInset = safeAreaManager_->GetKeyboardInset();
    EXPECT_EQ(keyboardInset.start, DISPLAY_HEIGHT - KEYBOARD_HEIGHT);
    EXPECT_EQ(keyboardInset.end, DISPLAY_HEIGHT);
    /**
     * @tc.steps: step2 call UpdateKeyboardSafeAreaTest with invalid systemArea
     */
    safeAreaManager_->UpdateSystemSafeArea(systemAreaNotValid);
    safeAreaManager_->UpdateKeyboardSafeArea(KEYBOARD_HEIGHT);
    keyboardInset = safeAreaManager_->GetKeyboardInset();
    auto rootHeight = PipelineContext::GetCurrentRootHeight();
    EXPECT_EQ(keyboardInset.start, rootHeight - KEYBOARD_HEIGHT);
    EXPECT_EQ(keyboardInset.end, rootHeight);
    /**
     * @tc.steps: step3 call UpdateKeyboardSafeAreaTest with rootHeight and invalid systemArea
     */
    rootHeight = SYSTEM_BOTTOM_START;
    safeAreaManager_->UpdateSystemSafeArea(systemAreaNotValid);
    safeAreaManager_->UpdateKeyboardSafeArea(KEYBOARD_HEIGHT, rootHeight);
    keyboardInset = safeAreaManager_->GetKeyboardInset();
    EXPECT_EQ(keyboardInset.start, rootHeight - KEYBOARD_HEIGHT);
    EXPECT_EQ(keyboardInset.end, rootHeight);
}

HWTEST_F(SafeAreaManagerTest, UpdateKeyboardSafeAreaWebTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1 call UpdateKeyboardWebSafeAreaTest with valid systemArea
     */
    MockContainer container(nullptr);
    safeAreaManager_->SetIsFullScreen(true);
    safeAreaManager_->UpdateSystemSafeArea(systemArea);
    auto ret = safeAreaManager_->UpdateKeyboardWebSafeArea(KEYBOARD_HEIGHT);
    EXPECT_EQ(ret, true);
    ret = safeAreaManager_->UpdateKeyboardWebSafeArea(KEYBOARD_HEIGHT);
    EXPECT_EQ(ret, false);
    auto keyboardInset = safeAreaManager_->GetKeyboardWebInset();
    EXPECT_EQ(keyboardInset.start, DISPLAY_HEIGHT - KEYBOARD_HEIGHT);
    EXPECT_EQ(keyboardInset.end, DISPLAY_HEIGHT);
    MockContainer::SetUp();
    safeAreaManager_->SetIsFullScreen(false);
    safeAreaManager_->UpdateSystemSafeArea(systemArea);
    ret = safeAreaManager_->UpdateKeyboardWebSafeArea(KEYBOARD_HEIGHT);
    EXPECT_EQ(ret, true);
    ret = safeAreaManager_->UpdateKeyboardWebSafeArea(KEYBOARD_HEIGHT);
    EXPECT_EQ(ret, false);
    keyboardInset = safeAreaManager_->GetKeyboardWebInset();
    EXPECT_EQ(keyboardInset.start, SYSTEM_BOTTOM_START - KEYBOARD_HEIGHT);
    EXPECT_EQ(keyboardInset.end, SYSTEM_BOTTOM_START);
    /**
     * @tc.steps: step2 call UpdateKeyboardSafeAreaTest with invalid systemArea
     */
    safeAreaManager_->UpdateSystemSafeArea(systemAreaNotValid);
    safeAreaManager_->UpdateKeyboardWebSafeArea(KEYBOARD_HEIGHT);
    keyboardInset = safeAreaManager_->GetKeyboardWebInset();
    auto rootHeight = PipelineContext::GetCurrentRootHeight();
    EXPECT_EQ(keyboardInset.start, rootHeight - KEYBOARD_HEIGHT);
    EXPECT_EQ(keyboardInset.end, rootHeight);
    /**
     * @tc.steps: step3 call UpdateKeyboardSafeAreaTest with rootHeight and invalid systemArea
     */
    rootHeight = SYSTEM_BOTTOM_START;
    safeAreaManager_->UpdateSystemSafeArea(systemAreaNotValid);
    safeAreaManager_->UpdateKeyboardWebSafeArea(KEYBOARD_HEIGHT, rootHeight);
    keyboardInset = safeAreaManager_->GetKeyboardWebInset();
    EXPECT_EQ(keyboardInset.start, rootHeight - KEYBOARD_HEIGHT);
    EXPECT_EQ(keyboardInset.end, rootHeight);
    MockContainer::TearDown();
}

/**
 * @tc.name: CheckCutoutSafeAreaTest
 * @tc.desc: Use CheckCutoutSafeArea and test.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, CheckCutoutSafeAreaTest, TestSize.Level1)
{
    /* 
     * @tc.steps: step1 call CheckCutoutSafeArea with null rootSize params.
     * @tc.expected: CheckCutoutSafeArea returns false.
     */
    safeAreaManager_->UpdateCutoutSafeArea(cutoutArea);
    NG::OptionalSize<uint32_t> rootSize;
    auto ret = safeAreaManager_->CheckCutoutSafeArea(cutoutArea, rootSize);
    EXPECT_EQ(ret, false);

    /*
     * @tc.steps: step2 call CheckCutoutSafeArea with wrong rootSize params.
     * @tc.expected: CheckCutoutSafeArea returns true.
     */
    rootSize.SetWidth(1.0f);
    rootSize.SetHeight(1.0f);
    ret = safeAreaManager_->CheckCutoutSafeArea(cutoutArea, rootSize);
    EXPECT_EQ(ret, true);

    /*
     * @tc.steps: step3 call CheckCutoutSafeArea SafeAreaInsets is not valid params.
     * @tc.expected: CheckCutoutSafeArea returns false.
     */
    safeAreaManager_->UpdateCutoutSafeArea(cutoutAreaNotValid);
    rootSize.SetWidth(0.0f);
    rootSize.SetHeight(0.0f);
    ret = safeAreaManager_->CheckCutoutSafeArea(cutoutAreaNotValid, rootSize);
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: CheckSystemSafeAreaTest
 * @tc.desc: Use CheckSystemSafeArea and test.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, CheckSystemSafeAreaTest, TestSize.Level1)
{
    safeAreaManager_->UpdateSystemSafeArea(systemArea);
    auto ret = safeAreaManager_->CheckSystemSafeArea(systemArea);
    EXPECT_EQ(ret, false);

    ret = safeAreaManager_->UpdateSystemSafeArea(systemAreaNotValid);
    EXPECT_EQ(ret, true);
    ret = safeAreaManager_->CheckSystemSafeArea(systemArea);
    EXPECT_EQ(ret, true);
}

/**
 * @tc.name: CheckNavSafeAreaTest
 * @tc.desc: Use CheckNavSafeArea and test.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, CheckNavSafeAreaTest, TestSize.Level1)
{
    safeAreaManager_->UpdateNavSafeArea(navArea);
    auto ret = safeAreaManager_->CheckNavSafeArea(navArea);
    EXPECT_EQ(ret, false);

    ret = safeAreaManager_->UpdateNavSafeArea(navAreaNotValid);
    EXPECT_EQ(ret, true);
    ret = safeAreaManager_->CheckNavSafeArea(cutoutArea);
    EXPECT_EQ(ret, true);
}

/**
 * @tc.name: GetCombinedSafeAreaTest
 * @tc.desc: Use GetCombinedSafeArea GetSafeAreaWithoutCutout GetSafeAreaWithoutProcess and test.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, GetCombinedSafeAreaTest, TestSize.Level1)
{
    auto funExPect = [this](SafeAreaExpandOpts options, float left, float right, float top, float bottom) {
        auto res = safeAreaManager_->GetCombinedSafeArea(options);
        CommonExpectEQ(Rect { res.left_.start, res.right_.end, res.top_.start, res.bottom_.end },
            Rect { left, right, top, bottom });
    };

    safeAreaManager_->SetIsFullScreen(true);
    safeAreaManager_->UpdateCutoutSafeArea(cutoutArea);
    safeAreaManager_->UpdateSystemSafeArea(systemArea);
    safeAreaManager_->UpdateNavSafeArea(navArea);
    safeAreaManager_->UpdateKeyboardSafeArea(KEYBOARD_HEIGHT);
    safeAreaManager_->SetKeyBoardAvoidMode(KeyBoardAvoidMode::OFFSET);
    SafeAreaExpandOpts opt;

    /*@tc.steps: step1 Ignore SafeArea and call GetCombinedSafeArea*/
    safeAreaManager_->SetIgnoreSafeArea(true);
    funExPect(opt, 0.0f, 0.0f, 0.0f, 0.0f);

    /*@tc.steps: step2 Set option is null and call GetCombinedSafeArea*/
    safeAreaManager_->SetIgnoreSafeArea(false);
    funExPect(opt, 0.0f, 0.0f, 0.0f, 0.0f);

    /*@tc.steps: step3 Call GetCombinedSafeArea with invalid SafeArea*/
    safeAreaManager_->SetIsNeedAvoidWindow(false);
    safeAreaManager_->SetIsFullScreen(false);
    funExPect(opt, 0.0f, 0.0f, 0.0f, 0.0f);
    safeAreaManager_->SetIsFullScreen(true);

    /*@tc.steps: step4 SafeArea expand type includes SAFE_AREA_TYPE_CUTOUT*/
    opt.type |= SAFE_AREA_TYPE_CUTOUT;
    funExPect(opt, 0.0f, DISPLAY_WIDTH, 0.0f, DISPLAY_HEIGHT);

    /*@tc.steps: step5 SafeArea expand type includes SAFE_AREA_TYPE_SYSTEM*/
    opt.type |= SAFE_AREA_TYPE_SYSTEM;
    funExPect(opt, SYSTEM_LEFT_START, SYSTEM_RIGHT_END, SYSTEM_TOP_START, SYSTEM_BOTTOM_END);

    /**@tc.steps: step6 SafeArea expand type includes SAFE_AREA_TYPE_KEYBOARD and Set KeyBoardAvoidMode
        to RESIZE and NONE*/
    safeAreaManager_->SetKeyBoardAvoidMode(KeyBoardAvoidMode::RESIZE);
    funExPect(opt, SYSTEM_LEFT_START, SYSTEM_RIGHT_END, SYSTEM_TOP_START, SYSTEM_BOTTOM_END);

    safeAreaManager_->SetKeyBoardAvoidMode(KeyBoardAvoidMode::NONE);
    funExPect(opt, SYSTEM_LEFT_START, SYSTEM_RIGHT_END, SYSTEM_TOP_START, SYSTEM_BOTTOM_END);

    safeAreaManager_->SetKeyBoardAvoidMode(KeyBoardAvoidMode::OFFSET);
    opt.type |= SAFE_AREA_TYPE_KEYBOARD;
    funExPect(opt, SYSTEM_LEFT_START, SYSTEM_RIGHT_END, SYSTEM_TOP_START, SYSTEM_BOTTOM_END);

    safeAreaManager_->SetKeyBoardAvoidMode(KeyBoardAvoidMode::NONE);
    funExPect(opt, SYSTEM_LEFT_START, SYSTEM_RIGHT_END, SYSTEM_TOP_START, SYSTEM_BOTTOM_END);

    safeAreaManager_->SetKeyBoardAvoidMode(KeyBoardAvoidMode::RESIZE);
    funExPect(opt, SYSTEM_LEFT_START, SYSTEM_RIGHT_END, SYSTEM_TOP_START, SYSTEM_BOTTOM_END);

    /*@tc.steps: step7 call GetSafeAreaWithoutCutout*/
    auto res = safeAreaManager_->GetSafeAreaWithoutCutout();
    CommonExpectEQ(Rect { res.left_.start, res.right_.end, res.top_.start, res.bottom_.end },
        Rect { 0.0f, DISPLAY_WIDTH, 0.0f, DISPLAY_HEIGHT });

    /*@tc.steps: step7 call GetSafeAreaWithoutProcess*/
    res = safeAreaManager_->GetSafeAreaWithoutProcess();
    CommonExpectEQ(Rect { res.left_.start, res.right_.end, res.top_.start, res.bottom_.end },
        Rect { 0.0f, DISPLAY_WIDTH, 0.0f, DISPLAY_HEIGHT });
}

/**
 * @tc.name: ScbSystemSafeAreaTest
 * @tc.desc: Use UpdateScbSystemSafeArea and test.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, ScbSystemSafeAreaTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Call UpdateSystemSafeArea.
     */
    auto ret = safeAreaManager_->UpdateSystemSafeArea(systemAreaNotValid);
    EXPECT_EQ(ret, true);
    ret = safeAreaManager_->UpdateSystemSafeArea(systemAreaNotValid);
    EXPECT_EQ(ret, false);

    /**
     * @tc.steps: step2 Set the window type to SCB window and call GetSystemSafeArea.
     * @tc.expected: scbSystemSafeArea is null, GetSystemSafeArea returns systemSafeArea instead of scbSystemSafeArea.
     */
    safeAreaManager_->SetWindowTypeConfig(false, false, true);
    auto scbSystemSafeArea = safeAreaManager_->GetSystemSafeArea();
    EXPECT_EQ(scbSystemSafeArea, systemAreaNotValid);

    /**
     * @tc.steps: step3 Set the window type to app window and call UpdateScbSystemSafeArea.
     * @tc.expected: scbSystemSafeArea has value, but GetSystemSafeArea returns systemSafeArea because of appWindow.
     */
    safeAreaManager_->SetWindowTypeConfig(true, false, false);
    ret = safeAreaManager_->UpdateScbSystemSafeArea(systemArea);
    EXPECT_EQ(ret, true);
    ret = safeAreaManager_->UpdateScbSystemSafeArea(systemArea);
    EXPECT_EQ(ret, false);
    auto systemSafeArea = safeAreaManager_->GetSystemSafeArea();
    EXPECT_EQ(systemSafeArea, systemAreaNotValid);

    /**
     * @tc.steps: step2 Set the window type to SCB window and call GetSystemSafeArea.
     * @tc.expected: scbSystemSafeArea has value and window type is SCB, GetSystemSafeArea returns scbSystemSafeArea.
     */
    safeAreaManager_->SetWindowTypeConfig(false, false, true);
    scbSystemSafeArea = safeAreaManager_->GetSystemSafeArea();
    EXPECT_EQ(scbSystemSafeArea, systemArea);

    auto safeArea = safeAreaManager_->GetSafeAreaWithoutProcess();
    EXPECT_EQ(scbSystemSafeArea, safeArea);

    CommonExpectEQ(Rect { safeArea.left_.start, safeArea.right_.end, safeArea.top_.start, safeArea.bottom_.end },
        Rect { SYSTEM_LEFT_START, SYSTEM_RIGHT_END, SYSTEM_TOP_START, SYSTEM_BOTTOM_END });
}

/**
 * @tc.name: ScbCutoutSafeAreaTest
 * @tc.desc: Use ScbCutoutSafeArea and test.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, ScbCutoutSafeAreaTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1 call UpdateScbCutoutSafeArea without rootSize params.
     * @tc.expected: cutout regions need to adjacent to edges.
     */
    safeAreaManager_->SetIsFullScreen(true);
    auto ret = safeAreaManager_->UpdateCutoutSafeArea(cutoutAreaNotValid);
    EXPECT_EQ(ret, true);
    ret = safeAreaManager_->UpdateCutoutSafeArea(cutoutAreaNotValid);
    EXPECT_EQ(ret, false);

    /*@tc.steps: Set the window type to SCB window and call GetCutoutSafeArea.*/
    safeAreaManager_->SetWindowTypeConfig(false, false, true);
    auto scbCutoutSafeArea = safeAreaManager_->GetCutoutSafeArea();
    EXPECT_EQ(scbCutoutSafeArea, cutoutAreaNotValid);

    /*@tc.steps: Set the window type to app window and call UpdateScbCutoutSafeArea.*/
    safeAreaManager_->SetWindowTypeConfig(true, false, false);
    ret = safeAreaManager_->UpdateScbCutoutSafeArea(cutoutArea);
    EXPECT_EQ(ret, true);
    ret = safeAreaManager_->UpdateScbCutoutSafeArea(cutoutArea);
    EXPECT_EQ(ret, false);
    auto cutoutSafeArea = safeAreaManager_->GetCutoutSafeArea();
    EXPECT_EQ(cutoutSafeArea, cutoutAreaNotValid);

    /*@tc.steps: Set the window type to SCB window and call UpdateScbCutoutSafeArea.*/
    safeAreaManager_->SetWindowTypeConfig(false, false, true);
    scbCutoutSafeArea = safeAreaManager_->GetCutoutSafeArea();
    EXPECT_EQ(scbCutoutSafeArea, cutoutAreaWithRoot);

    auto safeArea = safeAreaManager_->GetSafeAreaWithoutProcess();
    EXPECT_EQ(scbCutoutSafeArea, safeArea);

    CommonExpectEQ(Rect { safeArea.left_.start, safeArea.right_.end, safeArea.top_.start, safeArea.bottom_.end },
        Rect { 0.0f, DISPLAY_WIDTH, 0.0f, DISPLAY_HEIGHT });

    /**
     * @tc.steps: step2 call UpdateScbCutoutSafeArea with rootSize params.
     * @tc.expected: cutout regions need to adjacent to edges.
     */
    NG::OptionalSize<uint32_t> rootSize;
    rootSize.SetWidth(DISPLAY_WIDTH - 20);
    rootSize.SetHeight(DISPLAY_HEIGHT - 25);
    ret = safeAreaManager_->UpdateScbCutoutSafeArea(cutoutArea, rootSize);
    EXPECT_EQ(ret, true);
    safeArea = safeAreaManager_->GetSafeAreaWithoutProcess();
    CommonExpectEQ(Rect { safeArea.left_.start, safeArea.right_.end, safeArea.top_.start, safeArea.bottom_.end },
        Rect { 0.0f, DISPLAY_WIDTH - 20, 0.0f, DISPLAY_HEIGHT - 25 });

    /**
     * @tc.steps: step3 call UpdateScbCutoutSafeArea SafeAreaInsets with invalid params.
     * @tc.expected: cutout regions need to adjacent to edges.
     */
    ret = safeAreaManager_->UpdateScbCutoutSafeArea(cutoutAreaNotValid);
    EXPECT_EQ(ret, true);
    ret = safeAreaManager_->UpdateScbCutoutSafeArea(cutoutAreaNotValid);
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: ScbNavSafeAreaTest
 * @tc.desc: Use UpdateScbNavSafeArea and test.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, ScbNavSafeAreaTest, TestSize.Level1)
{
    /**
     * @tc.steps: call UpdateScbNavSafeAreaTest
     */
    safeAreaManager_->SetIsFullScreen(true);
    auto ret = safeAreaManager_->UpdateScbNavSafeArea(navArea);
    EXPECT_EQ(ret, true);
    ret = safeAreaManager_->UpdateScbNavSafeArea(navArea);
    EXPECT_EQ(ret, false);

    safeAreaManager_->SetWindowTypeConfig(false, false, true);
    auto safeArea = safeAreaManager_->GetSafeAreaWithoutProcess();
    CommonExpectEQ(Rect { safeArea.left_.start, safeArea.right_.end, safeArea.top_.start, safeArea.bottom_.end },
        Rect { NAV_LEFT_START, NAV_RIGHT_END, NAV_TOP_START, NAV_BOTTOM_END });
}

/**
 * @tc.name: KeyboardOffsetTest1
 * @tc.desc: Set KeyBoardAvoidMode to KeyBoardAvoidMode::OFFSET And see if GetKeyboardOffset get right result
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, KeyboardOffsetTest1, TestSize.Level1)
{
    float offset = 100.0f;
    safeAreaManager_->UpdateKeyboardOffset(offset);
    /**
     * @tc.steps: SetKeyBoardAvoidMode OFFSET
     */
    auto ret = safeAreaManager_->SetKeyBoardAvoidMode(KeyBoardAvoidMode::OFFSET);
    EXPECT_EQ(ret, false);
    auto keyboardAvoidMode = safeAreaManager_->GetKeyBoardAvoidMode();
    ret = keyboardAvoidMode == KeyBoardAvoidMode::OFFSET;
    EXPECT_EQ(ret, true);

    auto keyboardOffset = safeAreaManager_->GetKeyboardOffset();
    EXPECT_EQ(keyboardOffset, offset);
    keyboardOffset = safeAreaManager_->GetKeyboardOffset(true);
    EXPECT_EQ(keyboardOffset, offset);
}

/**
 * @tc.name: KeyboardOffsetTest2
 * @tc.desc: Set KeyBoardAvoidMode to KeyBoardAvoidMode::RESIZE And see if GetKeyboardOffset get right result
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, KeyboardOffsetTest2, TestSize.Level1)
{
    float offset = 100.0f;
    safeAreaManager_->UpdateKeyboardOffset(offset);
    /**
     * @tc.steps: SetKeyBoardAvoidMode OFFSET
     */
    auto ret = safeAreaManager_->SetKeyBoardAvoidMode(KeyBoardAvoidMode::RESIZE);
    EXPECT_EQ(ret, true);
    auto keyboardAvoidMode = safeAreaManager_->GetKeyBoardAvoidMode();
    ret = keyboardAvoidMode == KeyBoardAvoidMode::RESIZE;
    EXPECT_EQ(ret, true);

    auto keyboardOffset = safeAreaManager_->GetKeyboardOffset();
    EXPECT_EQ(keyboardOffset, 0.0f);
    keyboardOffset = safeAreaManager_->GetKeyboardOffset(true);
    EXPECT_EQ(keyboardOffset, offset);
}

/**
 * @tc.name: KeyboardOffsetTest3
 * @tc.desc: Set KeyBoardAvoidMode to KeyBoardAvoidMode::NONE And see if GetKeyboardOffset get right result
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, KeyboardOffsetTest3, TestSize.Level1)
{
    float offset = 100.0f;
    safeAreaManager_->UpdateKeyboardOffset(offset);
    /**
     * @tc.steps: SetKeyBoardAvoidMode OFFSET
     */
    auto ret = safeAreaManager_->SetKeyBoardAvoidMode(KeyBoardAvoidMode::NONE);
    EXPECT_EQ(ret, true);
    auto keyboardAvoidMode = safeAreaManager_->GetKeyBoardAvoidMode();
    ret = keyboardAvoidMode == KeyBoardAvoidMode::NONE;
    EXPECT_EQ(ret, true);

    auto keyboardOffset = safeAreaManager_->GetKeyboardOffset();
    EXPECT_EQ(keyboardOffset, 0.0f);
    keyboardOffset = safeAreaManager_->GetKeyboardOffset(true);
    EXPECT_EQ(keyboardOffset, 0.0f);
}

/**
 * @tc.name: CaretAvoidModeTest001
 * @tc.desc: Set KeyBoardAvoidMode to KeyBoardAvoidMode::RESIZE_WITH_CARET
             And see if GetKeyboardOffset get right result
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, CaretAvoidModeTest001, TestSize.Level1)
{
    float offset = 100.0f;
    safeAreaManager_->UpdateKeyboardOffset(offset);
    /**
    * @tc.steps: step1 SetKeyBoardAvoidMode RESIZE_WITH_CARET
    */
    auto ret = safeAreaManager_->SetKeyBoardAvoidMode(KeyBoardAvoidMode::OFFSET_WITH_CARET);
    EXPECT_EQ(ret, true);
    auto keyboardAvoidMode = safeAreaManager_->GetKeyBoardAvoidMode();
    ret = keyboardAvoidMode == KeyBoardAvoidMode::OFFSET_WITH_CARET;
    EXPECT_EQ(ret, true);

    auto keyboardOffset = safeAreaManager_->GetKeyboardOffset();
    EXPECT_EQ(keyboardOffset, offset);
    keyboardOffset = safeAreaManager_->GetKeyboardOffset(true);
    EXPECT_EQ(keyboardOffset, offset);
}

/**
 * @tc.name: CaretAvoidModeTest002
 * @tc.desc: Set KeyBoardAvoidMode to KeyBoardAvoidMode::RESIZE_WITH_CARET
             And see if GetKeyboardOffset get right result
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, CaretAvoidModeTest002, TestSize.Level1)
{
    float offset = 100.0f;
    safeAreaManager_->UpdateKeyboardOffset(offset);
    /**
    * @tc.steps: step1 SetKeyBoardAvoidMode RESIZE_WITH_CARET
    */
    auto ret = safeAreaManager_->SetKeyBoardAvoidMode(KeyBoardAvoidMode::RESIZE_WITH_CARET);
    EXPECT_EQ(ret, true);
    auto keyboardAvoidMode = safeAreaManager_->GetKeyBoardAvoidMode();
    ret = keyboardAvoidMode == KeyBoardAvoidMode::RESIZE_WITH_CARET;
    EXPECT_EQ(ret, true);

    auto keyboardOffset = safeAreaManager_->GetKeyboardOffset();
    EXPECT_EQ(keyboardOffset, 0.0f);
    keyboardOffset = safeAreaManager_->GetKeyboardOffset(true);
    EXPECT_EQ(keyboardOffset, offset);
}

/**
 * @tc.name: LastKeyboardPoistionTest
 * @tc.desc: Use SetLastKeyboardPoistion GetLastKeyboardPoistion and test.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, LastKeyboardPoistionTest, TestSize.Level1)
{
    float lastKeyPos = 10.0f;
    EXPECT_EQ(safeAreaManager_->GetLastKeyboardPoistion(), 0.0f);
    safeAreaManager_->SetLastKeyboardPoistion(lastKeyPos);
    EXPECT_EQ(safeAreaManager_->GetLastKeyboardPoistion(), lastKeyPos);
    safeAreaManager_->SetLastKeyboardPoistion(0.0f);
    EXPECT_EQ(safeAreaManager_->GetLastKeyboardPoistion(), 0.0f);
}

/**
 * @tc.name: WindowWrapperOffsetTest
 * @tc.desc: Use GetWindowWrapperOffset and test.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, WindowWrapperOffsetTest, TestSize.Level1)
{
    auto windowModeCallback1 = []() { return WindowMode::WINDOW_MODE_FLOATING; };
    auto windowModeCallback2 = []() { return WindowMode::WINDOW_MODE_FULLSCREEN; };
    auto pipeline = PipelineContext::GetCurrentContext();
    auto manager = pipeline->GetSafeAreaManager();
    auto windowManager = pipeline->GetWindowManager();

    pipeline->SetWindowModal(WindowModal::NORMAL);
    windowManager->SetWindowGetModeCallBack(std::move(windowModeCallback1));
    auto ret = manager->GetWindowWrapperOffset();
    EXPECT_EQ(ret, OffsetF());

    pipeline->SetWindowModal(WindowModal::CONTAINER_MODAL);
    windowManager->SetWindowGetModeCallBack(std::move(windowModeCallback1));
    ret = manager->GetWindowWrapperOffset();
    EXPECT_EQ(ret, OffsetF(4.0f, 0.0f));

    pipeline->SetWindowModal(WindowModal::NORMAL);
    windowManager->SetWindowGetModeCallBack(std::move(windowModeCallback2));
    ret = manager->GetWindowWrapperOffset();
    EXPECT_EQ(ret, OffsetF());

    pipeline->SetWindowModal(WindowModal::CONTAINER_MODAL);
    windowManager->SetWindowGetModeCallBack(std::move(windowModeCallback2));
    ret = manager->GetWindowWrapperOffset();
    EXPECT_EQ(ret, OffsetF());
}

/**
 * @tc.name: NodesTest
 * @tc.desc: Use GetGeoRestoreNodes AddGeoRestoreNode RemoveRestoreNode
 *           AddNeedExpandNode ClearNeedExpandNode ExpandSafeArea AddNodeToExpandListIfNeeded and test.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, NodesTest, TestSize.Level1)
{
    safeAreaManager_->ExpandSafeArea();
    auto frameNode0 = FrameNode::CreateFrameNode(
        V2::PAGE_ETS_TAG, 0, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()), true);
    frameNode0->SetRootNodeId(0);
    auto pattern0 = frameNode0->GetPattern<PagePattern>();
    pattern0->CreateOverlayManager(true);
    auto frameNode1 = FrameNode::CreateFrameNode(
        V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()), true);
    frameNode1->SetRootNodeType(RootNodeType::PAGE_ETS_TAG);
    frameNode1->SetRootNodeId(0);
    auto frameNode2 = FrameNode::CreateFrameNode(
        V2::PAGE_ETS_TAG, 2, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()), false);
    frameNode2->SetRootNodeType(RootNodeType::NAVDESTINATION_VIEW_ETS_TAG);
    frameNode2->SetRootNodeId(0);
    auto frameNode3 = FrameNode::CreateFrameNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 3, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()), false);
    frameNode3->SetRootNodeType(RootNodeType::NAVDESTINATION_VIEW_ETS_TAG);
    frameNode3->SetRootNodeId(0);
    auto frameNode4 = FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, 4, AceType::MakeRefPtr<CheckBoxPattern>());
    EXPECT_EQ(safeAreaManager_->CheckPageNeedAvoidKeyboard(frameNode0), true);
    EXPECT_EQ(safeAreaManager_->CheckPageNeedAvoidKeyboard(frameNode1), true);
    EXPECT_EQ(safeAreaManager_->CheckPageNeedAvoidKeyboard(frameNode2), true);
    EXPECT_EQ(safeAreaManager_->CheckPageNeedAvoidKeyboard(frameNode3), false);
    EXPECT_EQ(safeAreaManager_->CheckPageNeedAvoidKeyboard(frameNode4), false);

    EXPECT_EQ(safeAreaManager_->AddNodeToExpandListIfNeeded(frameNode0), true);
    EXPECT_EQ(safeAreaManager_->AddNodeToExpandListIfNeeded(frameNode1), true);
    EXPECT_EQ(safeAreaManager_->AddNodeToExpandListIfNeeded(frameNode2), true);
    EXPECT_EQ(safeAreaManager_->AddNodeToExpandListIfNeeded(frameNode3), true);
    EXPECT_EQ(safeAreaManager_->AddNodeToExpandListIfNeeded(frameNode4), true);

    EXPECT_EQ(safeAreaManager_->AddNodeToExpandListIfNeeded(frameNode0), false);
    EXPECT_EQ(safeAreaManager_->AddNodeToExpandListIfNeeded(frameNode1), false);
    EXPECT_EQ(safeAreaManager_->AddNodeToExpandListIfNeeded(frameNode2), false);
    EXPECT_EQ(safeAreaManager_->AddNodeToExpandListIfNeeded(frameNode3), false);
    EXPECT_EQ(safeAreaManager_->AddNodeToExpandListIfNeeded(frameNode4), false);

    safeAreaManager_->ExpandSafeArea();
    EXPECT_EQ(safeAreaManager_->AddNodeToExpandListIfNeeded(frameNode0), true);
    EXPECT_EQ(safeAreaManager_->AddNodeToExpandListIfNeeded(frameNode1), true);
    EXPECT_EQ(safeAreaManager_->AddNodeToExpandListIfNeeded(frameNode2), true);
    EXPECT_EQ(safeAreaManager_->AddNodeToExpandListIfNeeded(frameNode3), true);
    EXPECT_EQ(safeAreaManager_->AddNodeToExpandListIfNeeded(frameNode4), true);
    auto pipeline = PipelineContext::GetCurrentContext();
    auto manager = pipeline->GetSafeAreaManager();
    EXPECT_EQ(manager->GetGeoRestoreNodes().size(), 5);
}

/**
 * @tc.name: SafeAreaToPaddingTest1
 * @tc.desc: Test SafeAreaToPadding with default parameter false.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, SafeAreaToPaddingTest1, TestSize.Level1)
{
    /**
     * @tc.steps: Call SafeAreaToPadding with different ignoreSafeArea_, isFullScreen_, isNeedAvoidWindow_.
     * @tc.expected: SafeAreaToPadding returns empty.
     */
    safeAreaManager_->SetIgnoreSafeArea(true);
    safeAreaManager_->SetIsFullScreen(true);
    safeAreaManager_->SetIsNeedAvoidWindow(true);
    PaddingPropertyF paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);

    safeAreaManager_->SetIgnoreSafeArea(true);
    safeAreaManager_->SetIsFullScreen(false);
    safeAreaManager_->SetIsNeedAvoidWindow(true);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);

    safeAreaManager_->SetIgnoreSafeArea(true);
    safeAreaManager_->SetIsFullScreen(true);
    safeAreaManager_->SetIsNeedAvoidWindow(false);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);

    safeAreaManager_->SetIgnoreSafeArea(true);
    safeAreaManager_->SetIsFullScreen(false);
    safeAreaManager_->SetIsNeedAvoidWindow(false);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);

    safeAreaManager_->SetIgnoreSafeArea(false);
    safeAreaManager_->SetIsFullScreen(false);
    safeAreaManager_->SetIsNeedAvoidWindow(false);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);
}

/**
 * @tc.name: SafeAreaToPaddingTest2
 * @tc.desc: Test SafeAreaToPadding with default parameter false.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, SafeAreaToPaddingTest2, TestSize.Level1)
{
    /**
     * @tc.steps: Call UpdateSystemSafeArea, UpdateNavSafeArea, UpdateCutoutSafeArea with
     * valid safeAreaInsets before calling SafeAreaToPadding.
     * @tc.expected: SafeAreaToPadding returns empty or non-empty.
     */
    safeAreaManager_->UpdateSystemSafeArea(systemArea);
    safeAreaManager_->UpdateNavSafeArea(navArea);
    safeAreaManager_->UpdateCutoutSafeArea(cutoutArea);

    safeAreaManager_->SetIgnoreSafeArea(false);
    safeAreaManager_->SetIsFullScreen(true);
    safeAreaManager_->SetIsNeedAvoidWindow(false);
    PaddingPropertyF paddingProperty = safeAreaManager_->SafeAreaToPadding();

    EXPECT_EQ(paddingProperty.left, NAV_LEFT_END - SYSTEM_LEFT_START);
    EXPECT_EQ(paddingProperty.right, SYSTEM_RIGHT_END - NAV_RIGHT_START);
    EXPECT_EQ(paddingProperty.top, NAV_TOP_END - SYSTEM_TOP_START);
    EXPECT_EQ(paddingProperty.bottom, SYSTEM_BOTTOM_END - NAV_BOTTOM_START);

    safeAreaManager_->SetIgnoreSafeArea(false);
    safeAreaManager_->SetIsFullScreen(false);
    safeAreaManager_->SetIsNeedAvoidWindow(true);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();

    EXPECT_EQ(paddingProperty.left, NAV_LEFT_END - SYSTEM_LEFT_START);
    EXPECT_EQ(paddingProperty.right, SYSTEM_RIGHT_END - NAV_RIGHT_START);
    EXPECT_EQ(paddingProperty.top, NAV_TOP_END - SYSTEM_TOP_START);
    EXPECT_EQ(paddingProperty.bottom, SYSTEM_BOTTOM_END - NAV_BOTTOM_START);

    safeAreaManager_->SetIgnoreSafeArea(false);
    safeAreaManager_->SetIsFullScreen(false);
    safeAreaManager_->SetIsNeedAvoidWindow(false);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);

    safeAreaManager_->SetIgnoreSafeArea(true);
    safeAreaManager_->SetIsFullScreen(false);
    safeAreaManager_->SetIsNeedAvoidWindow(false);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);

    safeAreaManager_->SetIgnoreSafeArea(true);
    safeAreaManager_->SetIsFullScreen(true);
    safeAreaManager_->SetIsNeedAvoidWindow(false);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);

    safeAreaManager_->SetIgnoreSafeArea(true);
    safeAreaManager_->SetIsFullScreen(false);
    safeAreaManager_->SetIsNeedAvoidWindow(true);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);
}

/**
 * @tc.name: SafeAreaToPaddingTest3
 * @tc.desc: Test SafeAreaToPadding with default parameter false.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, SafeAreaToPaddingTest3, TestSize.Level1)
{
    /**
     * @tc.steps: Call UpdateSystemSafeArea, UpdateNavSafeArea, UpdateCutoutSafeArea with
     * not valid safeAreaInsets before calling SafeAreaToPadding.
     * @tc.expected: SafeAreaToPadding returns empty or non-empty.
     */
    safeAreaManager_->UpdateSystemSafeArea(systemAreaNotValid);
    safeAreaManager_->UpdateNavSafeArea(navAreaNotValid);
    safeAreaManager_->UpdateCutoutSafeArea(cutoutAreaNotValid);
    PaddingPropertyF paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);

    safeAreaManager_->SetIgnoreSafeArea(false);
    safeAreaManager_->SetIsFullScreen(true);
    safeAreaManager_->SetIsNeedAvoidWindow(true);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);

    safeAreaManager_->SetIgnoreSafeArea(false);
    safeAreaManager_->SetIsFullScreen(true);
    safeAreaManager_->SetIsNeedAvoidWindow(false);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);

    safeAreaManager_->SetIgnoreSafeArea(false);
    safeAreaManager_->SetIsFullScreen(false);
    safeAreaManager_->SetIsNeedAvoidWindow(true);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);

    safeAreaManager_->SetIgnoreSafeArea(false);
    safeAreaManager_->SetIsFullScreen(false);
    safeAreaManager_->SetIsNeedAvoidWindow(false);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);

    safeAreaManager_->SetIgnoreSafeArea(true);
    safeAreaManager_->SetIsFullScreen(false);
    safeAreaManager_->SetIsNeedAvoidWindow(false);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);

    safeAreaManager_->SetIgnoreSafeArea(true);
    safeAreaManager_->SetIsFullScreen(true);
    safeAreaManager_->SetIsNeedAvoidWindow(false);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);

    safeAreaManager_->SetIgnoreSafeArea(true);
    safeAreaManager_->SetIsFullScreen(false);
    safeAreaManager_->SetIsNeedAvoidWindow(true);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);
}

/**
 * @tc.name: SafeAreaToPaddingTest4
 * @tc.desc: Test SafeAreaToPadding with default parameter false.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, SafeAreaToPaddingTest4, TestSize.Level1)
{
    /**
     * @tc.steps: Call UpdateSystemSafeArea, UpdateNavSafeArea, UpdateCutoutSafeArea with
     * valid systemArea and not valid navArea cutoutArea before calling SafeAreaToPadding.
     * @tc.expected: SafeAreaToPadding returns empty or non-empty.
     */
    safeAreaManager_->UpdateSystemSafeArea(systemArea);
    safeAreaManager_->UpdateNavSafeArea(navAreaNotValid);
    safeAreaManager_->UpdateCutoutSafeArea(cutoutAreaNotValid);

    safeAreaManager_->SetIgnoreSafeArea(false);
    safeAreaManager_->SetIsFullScreen(true);
    safeAreaManager_->SetIsNeedAvoidWindow(false);
    PaddingPropertyF paddingProperty = safeAreaManager_->SafeAreaToPadding();

    EXPECT_EQ(paddingProperty.left, SYSTEM_LEFT_END - SYSTEM_LEFT_START);
    EXPECT_EQ(paddingProperty.right, SYSTEM_TOP_END - SYSTEM_TOP_START);
    EXPECT_EQ(paddingProperty.top, SYSTEM_RIGHT_END - SYSTEM_RIGHT_START);
    EXPECT_EQ(paddingProperty.bottom, SYSTEM_BOTTOM_END - SYSTEM_BOTTOM_START);

    safeAreaManager_->SetIgnoreSafeArea(false);
    safeAreaManager_->SetIsFullScreen(false);
    safeAreaManager_->SetIsNeedAvoidWindow(true);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();

    EXPECT_EQ(paddingProperty.left, SYSTEM_LEFT_END - SYSTEM_LEFT_START);
    EXPECT_EQ(paddingProperty.right, SYSTEM_RIGHT_END - SYSTEM_RIGHT_START);
    EXPECT_EQ(paddingProperty.top, SYSTEM_TOP_END - SYSTEM_TOP_START);
    EXPECT_EQ(paddingProperty.bottom, SYSTEM_BOTTOM_END - SYSTEM_BOTTOM_START);

    safeAreaManager_->SetIgnoreSafeArea(false);
    safeAreaManager_->SetIsFullScreen(false);
    safeAreaManager_->SetIsNeedAvoidWindow(false);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);

    safeAreaManager_->SetIgnoreSafeArea(true);
    safeAreaManager_->SetIsFullScreen(false);
    safeAreaManager_->SetIsNeedAvoidWindow(false);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);

    safeAreaManager_->SetIgnoreSafeArea(true);
    safeAreaManager_->SetIsFullScreen(true);
    safeAreaManager_->SetIsNeedAvoidWindow(false);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);

    safeAreaManager_->SetIgnoreSafeArea(true);
    safeAreaManager_->SetIsFullScreen(false);
    safeAreaManager_->SetIsNeedAvoidWindow(true);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);
}

/**
 * @tc.name: SafeAreaToPaddingTest5
 * @tc.desc: Test SafeAreaToPadding with default parameter false.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, SafeAreaToPaddingTest5, TestSize.Level1)
{
    /**
     * @tc.steps: Call UpdateSystemSafeArea, UpdateNavSafeArea, UpdateCutoutSafeArea with
     * valid systemArea and cutoutArea and not valid navArea before calling SafeAreaToPadding.
     * @tc.expected: SafeAreaToPadding returns empty or non-empty.
     */
    safeAreaManager_->UpdateSystemSafeArea(systemArea);
    safeAreaManager_->UpdateNavSafeArea(navAreaNotValid);
    safeAreaManager_->UpdateCutoutSafeArea(cutoutArea);

    safeAreaManager_->SetIgnoreSafeArea(false);
    safeAreaManager_->SetIsFullScreen(true);
    safeAreaManager_->SetIsNeedAvoidWindow(false);
    PaddingPropertyF paddingProperty = safeAreaManager_->SafeAreaToPadding();

    EXPECT_EQ(paddingProperty.left, CUTOUT_LEFT_END - SYSTEM_LEFT_START);
    EXPECT_EQ(paddingProperty.right, SYSTEM_RIGHT_END - CUTOUT_RIGHT_START);
    EXPECT_EQ(paddingProperty.top, CUTOUT_TOP_END - SYSTEM_TOP_START);
    EXPECT_EQ(paddingProperty.bottom, SYSTEM_BOTTOM_END - CUTOUT_BOTTOM_START);

    safeAreaManager_->SetIgnoreSafeArea(false);
    safeAreaManager_->SetIsFullScreen(false);
    safeAreaManager_->SetIsNeedAvoidWindow(true);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();

    EXPECT_EQ(paddingProperty.left, CUTOUT_LEFT_END - SYSTEM_LEFT_START);
    EXPECT_EQ(paddingProperty.right, SYSTEM_RIGHT_END - CUTOUT_RIGHT_START);
    EXPECT_EQ(paddingProperty.top, CUTOUT_TOP_END - SYSTEM_TOP_START);
    EXPECT_EQ(paddingProperty.bottom, SYSTEM_BOTTOM_END - CUTOUT_BOTTOM_START);

    safeAreaManager_->SetIgnoreSafeArea(false);
    safeAreaManager_->SetIsFullScreen(false);
    safeAreaManager_->SetIsNeedAvoidWindow(false);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);

    safeAreaManager_->SetIgnoreSafeArea(true);
    safeAreaManager_->SetIsFullScreen(false);
    safeAreaManager_->SetIsNeedAvoidWindow(false);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);

    safeAreaManager_->SetIgnoreSafeArea(true);
    safeAreaManager_->SetIsFullScreen(true);
    safeAreaManager_->SetIsNeedAvoidWindow(false);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);

    safeAreaManager_->SetIgnoreSafeArea(true);
    safeAreaManager_->SetIsFullScreen(false);
    safeAreaManager_->SetIsNeedAvoidWindow(true);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);
}

/**
 * @tc.name: SafeAreaToPaddingTest6
 * @tc.desc: Test SafeAreaToPadding with parameter true.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, SafeAreaToPaddingTest6, TestSize.Level1)
{
    /**
     * @tc.steps: Call UpdateSystemSafeArea, UpdateNavSafeArea, UpdateCutoutSafeArea with
     *  valid safeAreaInsets before calling SafeAreaToPadding.
     * @tc.expected: SafeAreaToPadding returns non-empty.
     */
    safeAreaManager_->UpdateSystemSafeArea(systemArea);
    safeAreaManager_->UpdateNavSafeArea(navArea);
    safeAreaManager_->UpdateCutoutSafeArea(cutoutArea);
    PaddingPropertyF paddingProperty = safeAreaManager_->SafeAreaToPadding(true);

    EXPECT_EQ(paddingProperty.left, NAV_LEFT_END - SYSTEM_LEFT_START);
    EXPECT_EQ(paddingProperty.right, SYSTEM_RIGHT_END - NAV_RIGHT_START);
    EXPECT_EQ(paddingProperty.top, NAV_TOP_END - SYSTEM_TOP_START);
    EXPECT_EQ(paddingProperty.bottom, SYSTEM_BOTTOM_END - NAV_BOTTOM_START);

    /**
     * @tc.steps: Call UpdateSystemSafeArea, UpdateNavSafeArea, UpdateCutoutSafeArea with
     * not valid safeAreaInsets before calling SafeAreaToPadding.
     * @tc.expected: SafeAreaToPadding returns empty.
     */
    safeAreaManager_->UpdateSystemSafeArea(systemAreaNotValid);
    safeAreaManager_->UpdateNavSafeArea(navAreaNotValid);
    safeAreaManager_->UpdateCutoutSafeArea(cutoutAreaNotValid);
    paddingProperty = safeAreaManager_->SafeAreaToPadding(true);
    EXPECT_EQ(paddingProperty.Empty(), true);

    /**
     * @tc.steps: Call UpdateSystemSafeArea, UpdateNavSafeArea, UpdateCutoutSafeArea with
     * valid systemArea and not valid navArea cutoutArea before calling SafeAreaToPadding.
     * @tc.expected: SafeAreaToPadding returns non-empty.
     */
    safeAreaManager_->UpdateSystemSafeArea(systemArea);
    safeAreaManager_->UpdateNavSafeArea(navAreaNotValid);
    safeAreaManager_->UpdateCutoutSafeArea(cutoutAreaNotValid);
    paddingProperty = safeAreaManager_->SafeAreaToPadding(true);

    EXPECT_EQ(paddingProperty.left, SYSTEM_LEFT_END - SYSTEM_LEFT_START);
    EXPECT_EQ(paddingProperty.right, SYSTEM_TOP_END - SYSTEM_TOP_START);
    EXPECT_EQ(paddingProperty.top, SYSTEM_RIGHT_END - SYSTEM_RIGHT_START);
    EXPECT_EQ(paddingProperty.bottom, SYSTEM_BOTTOM_END - SYSTEM_BOTTOM_START);

    /**
     * @tc.steps: step4 call UpdateSystemSafeArea, UpdateNavSafeArea, UpdateCutoutSafeArea with
     * valid systemArea and cutoutArea and not valid navArea before calling SafeAreaToPadding.
     * @tc.expected: SafeAreaToPadding returns non-empty.
     */
    safeAreaManager_->UpdateSystemSafeArea(systemArea);
    safeAreaManager_->UpdateNavSafeArea(navAreaNotValid);
    safeAreaManager_->UpdateCutoutSafeArea(cutoutArea);
    paddingProperty = safeAreaManager_->SafeAreaToPadding(true);

    EXPECT_EQ(paddingProperty.left, CUTOUT_LEFT_END - SYSTEM_LEFT_START);
    EXPECT_EQ(paddingProperty.right, SYSTEM_RIGHT_END - CUTOUT_RIGHT_START);
    EXPECT_EQ(paddingProperty.top, CUTOUT_TOP_END - SYSTEM_TOP_START);
    EXPECT_EQ(paddingProperty.bottom, SYSTEM_BOTTOM_END - CUTOUT_BOTTOM_START);
}

/**
 * @tc.name: SafeAreaToPaddingTest7
 * @tc.desc: Test SafeAreaToPadding with LayoutSafeAreaType.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, SafeAreaToPaddingTest7, TestSize.Level1)
{
    safeAreaManager_->SetIgnoreSafeArea(false);
    safeAreaManager_->SetIsFullScreen(false);
    safeAreaManager_->SetIsNeedAvoidWindow(true);

    safeAreaManager_->UpdateSystemSafeArea(systemArea);
    safeAreaManager_->UpdateNavSafeArea(navArea);
    safeAreaManager_->UpdateCutoutSafeArea(cutoutArea);

    safeAreaManager_->SetKeyBoardAvoidMode(KeyBoardAvoidMode::RESIZE);
    safeAreaManager_->UpdateKeyboardSafeArea(KEYBOARD_HEIGHT);
    PaddingPropertyF paddingProperty = safeAreaManager_->SafeAreaToPadding(true, LAYOUT_SAFE_AREA_TYPE_KEYBOARD);
    EXPECT_EQ(paddingProperty.left, std::nullopt);
    EXPECT_EQ(paddingProperty.right, std::nullopt);
    EXPECT_EQ(paddingProperty.top, std::nullopt);
    EXPECT_EQ(paddingProperty.bottom, KEYBOARD_HEIGHT);

    paddingProperty = safeAreaManager_->SafeAreaToPadding(true, LAYOUT_SAFE_AREA_TYPE_ALL);
    EXPECT_EQ(paddingProperty.left, NAV_LEFT_END - SYSTEM_LEFT_START);
    EXPECT_EQ(paddingProperty.right, SYSTEM_RIGHT_END - NAV_RIGHT_START);
    EXPECT_EQ(paddingProperty.top, NAV_TOP_END - SYSTEM_TOP_START);
    EXPECT_EQ(paddingProperty.bottom, KEYBOARD_HEIGHT);

    safeAreaManager_->SetKeyBoardAvoidMode(KeyBoardAvoidMode::OFFSET);
    float offset = -KEYBOARD_HEIGHT;
    safeAreaManager_->UpdateKeyboardOffset(offset);
    paddingProperty = safeAreaManager_->SafeAreaToPadding(true, LAYOUT_SAFE_AREA_TYPE_KEYBOARD);
    EXPECT_EQ(paddingProperty.left, std::nullopt);
    EXPECT_EQ(paddingProperty.right, std::nullopt);
    EXPECT_EQ(paddingProperty.top, std::nullopt);
    EXPECT_EQ(paddingProperty.bottom, std::nullopt);

    offset = -KEYBOARD_HEIGHT / 2.0f;
    safeAreaManager_->UpdateKeyboardOffset(offset);
    paddingProperty = safeAreaManager_->SafeAreaToPadding(true, LAYOUT_SAFE_AREA_TYPE_KEYBOARD);
    EXPECT_EQ(paddingProperty.left, std::nullopt);
    EXPECT_EQ(paddingProperty.right, std::nullopt);
    EXPECT_EQ(paddingProperty.top, std::nullopt);
    EXPECT_EQ(paddingProperty.bottom, SYSTEM_BOTTOM_END - NAV_BOTTOM_START);

    paddingProperty = safeAreaManager_->SafeAreaToPadding(true, LAYOUT_SAFE_AREA_TYPE_ALL);
    EXPECT_EQ(paddingProperty.left, NAV_LEFT_END - SYSTEM_LEFT_START);
    EXPECT_EQ(paddingProperty.right, SYSTEM_RIGHT_END - NAV_RIGHT_START);
    EXPECT_EQ(paddingProperty.top, NAV_TOP_END - SYSTEM_TOP_START);
    EXPECT_EQ(paddingProperty.bottom, SYSTEM_BOTTOM_END - NAV_BOTTOM_START);
}

/**
 * @tc.name: NeedExpandNodeListTest
 * @tc.desc: Build an UI tree and start layouting from the root
 * and test if set of nodes are added in the list correctly.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, NeedExpandNodeListTest, TestSize.Level1)
{
    // create nodes
    auto frameNode0 = FrameNode::CreateFrameNode(
        V2::PAGE_ETS_TAG, 0, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()), true);

    auto frameNode1 = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<LinearLayoutPattern>(true));

    auto frameNode2 = FrameNode::CreateFrameNode(V2::FLEX_ETS_TAG, 2, AceType::MakeRefPtr<LinearLayoutPattern>(true));

    auto frameNode3 = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 3, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    frameNode1->MountToParent(frameNode0);
    frameNode2->MountToParent(frameNode1);
    frameNode3->MountToParent(frameNode2);
    // make sure nodes mount correctly
    EXPECT_EQ(frameNode1->GetParent()->GetTag(), V2::PAGE_ETS_TAG);
    EXPECT_EQ(frameNode2->GetParent()->GetTag(), V2::COLUMN_ETS_TAG);
    EXPECT_EQ(frameNode3->GetParent()->GetTag(), V2::FLEX_ETS_TAG);
    SafeAreaExpandOpts opts = { .type = SAFE_AREA_TYPE_SYSTEM, .edges = SAFE_AREA_EDGE_TOP };
    auto columnLayoutProperty = frameNode1->GetLayoutProperty();
    EXPECT_NE(columnLayoutProperty, nullptr);
    columnLayoutProperty->UpdateSafeAreaExpandOpts(opts);
    auto flexLayoutProperty = frameNode2->GetLayoutProperty();
    EXPECT_NE(flexLayoutProperty, nullptr);
    flexLayoutProperty->UpdateSafeAreaExpandOpts(opts);
    auto rowLayoutProperty = frameNode3->GetLayoutProperty();
    EXPECT_NE(rowLayoutProperty, nullptr);
    rowLayoutProperty->UpdateSafeAreaExpandOpts(opts);
    // page start to measure
    frameNode0->SetLayoutDirtyMarked(true);
    frameNode0->CreateLayoutTask();
    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);
    auto manager = pipeline->GetSafeAreaManager();
    EXPECT_NE(manager, nullptr);
    auto nodeSet = manager->GetExpandNodeSet();
    // page should not be added
    EXPECT_EQ(nodeSet.size(), 3);
    auto iter = nodeSet.begin();
    EXPECT_NE(iter, nodeSet.end());
    auto nodeIter = (*iter).Upgrade();
    EXPECT_NE(nodeIter, nullptr);
    EXPECT_EQ(nodeIter->GetTag(), V2::COLUMN_ETS_TAG);
    EXPECT_EQ(nodeIter->GetId(), 1);
    iter++;
    EXPECT_NE(iter, nodeSet.end());
    nodeIter = (*iter).Upgrade();
    EXPECT_NE(nodeIter, nullptr);
    EXPECT_EQ(nodeIter->GetTag(), V2::FLEX_ETS_TAG);
    EXPECT_EQ(nodeIter->GetId(), 2);
    iter++;
    EXPECT_NE(iter, nodeSet.end());
    nodeIter = (*iter).Upgrade();
    EXPECT_NE(nodeIter, nullptr);
    EXPECT_EQ(nodeIter->GetTag(), V2::ROW_ETS_TAG);
    EXPECT_EQ(nodeIter->GetId(), 3);
}

/**
 * @tc.name: AddNodeToExpandListIfNeededTest
 * @tc.desc: test functionality of AddNodeToExpandListIfNeededTest interface
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, AddNodeToExpandListIfNeededTest, TestSize.Level1)
{
    auto frameNode0 = FrameNode::CreateFrameNode(
        V2::PAGE_ETS_TAG, 0, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()), true);

    auto frameNode1 =
        FrameNode::CreateFrameNode(V2::NAVIGATION_VIEW_ETS_TAG, 1, AceType::MakeRefPtr<NavigationPattern>(), false);

    auto frameNode2 = FrameNode::CreateFrameNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 2, AceType::MakeRefPtr<NavDestinationPattern>(), true);

    auto frameNode3 = FrameNode::CreateFrameNode(
        V2::NAVDESTINATION_CONTENT_ETS_TAG, 3, AceType::MakeRefPtr<LinearLayoutPattern>(true), false);

    auto frameNode4 = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 4, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    EXPECT_EQ(safeAreaManager_->AddNodeToExpandListIfNeeded(frameNode0), true);
    EXPECT_EQ(safeAreaManager_->AddNodeToExpandListIfNeeded(frameNode1), true);
    EXPECT_EQ(safeAreaManager_->AddNodeToExpandListIfNeeded(frameNode2), true);
    EXPECT_EQ(safeAreaManager_->AddNodeToExpandListIfNeeded(frameNode3), true);
    EXPECT_EQ(safeAreaManager_->AddNodeToExpandListIfNeeded(frameNode4), true);
    EXPECT_EQ(safeAreaManager_->GetExpandNodeSet().size(), 4);

    // repeat add should not work
    EXPECT_EQ(safeAreaManager_->AddNodeToExpandListIfNeeded(frameNode0), false);
    EXPECT_EQ(safeAreaManager_->AddNodeToExpandListIfNeeded(frameNode1), false);
    EXPECT_EQ(safeAreaManager_->AddNodeToExpandListIfNeeded(frameNode2), false);
    EXPECT_EQ(safeAreaManager_->AddNodeToExpandListIfNeeded(frameNode3), false);
    EXPECT_EQ(safeAreaManager_->AddNodeToExpandListIfNeeded(frameNode4), false);

    safeAreaManager_->ClearNeedExpandNode();
    EXPECT_EQ(safeAreaManager_->GetExpandNodeSet().size(), 0);
}

/**
 * @tc.name: GetKeyboardWebInset
 * @tc.desc: Use GetKeyboardWebInset and test.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, GetKeyboardWebInsetTest, TestSize.Level1)
{
    SafeAreaInsets::Inset inset;
    safeAreaManager_->keyboardAvoidMode_ = KeyBoardAvoidMode::NONE;
    auto keyboardInset = safeAreaManager_->GetKeyboardWebInset();
    EXPECT_EQ(keyboardInset.start, inset.start);
    EXPECT_EQ(keyboardInset.end, inset.end);
    safeAreaManager_->keyboardAvoidMode_ = KeyBoardAvoidMode::OFFSET;
    keyboardInset = safeAreaManager_ ->GetKeyboardWebInset();
    EXPECT_EQ(keyboardInset.start, safeAreaManager_->keyboardWebInset_.start);
    EXPECT_EQ(keyboardInset.end, safeAreaManager_->keyboardWebInset_.end);
}

/**
 * @tc.name: IsModeResizeOrIsModeOffset
 * @tc.desc: Test IsModeResize and IsModeOffset
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, IsModeResizeOrIsModeOffset, TestSize.Level1)
{
    std::vector<KeyBoardAvoidMode> modeArr = {
        KeyBoardAvoidMode::OFFSET,
        KeyBoardAvoidMode::RESIZE,
        KeyBoardAvoidMode::OFFSET_WITH_CARET,
        KeyBoardAvoidMode::RESIZE_WITH_CARET,
        KeyBoardAvoidMode::NONE
    };
    std::vector<std::pair<bool, bool>> expectedRes = {
        { true, false },
        { false, true },
        { true, false },
        { false, true },
        { false, false }
    };
    for (int i= 0; i < modeArr.size(); ++i) {
        safeAreaManager_->SetKeyBoardAvoidMode(modeArr[i]);
        EXPECT_EQ(safeAreaManager_->IsModeOffset(), expectedRes[i].first);
        EXPECT_EQ(safeAreaManager_->IsModeResize(), expectedRes[i].second);
    }
}
} // namespace OHOS::Ace::NG