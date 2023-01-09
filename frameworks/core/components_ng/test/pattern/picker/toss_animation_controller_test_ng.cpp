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

#include <functional>
#include <optional>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/picker/datepicker_pattern.h"
#include "core/components_ng/pattern/picker/toss_animation_controller.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const double YOFFSET_START1 = 0.0;
const double YOFFSET_END1 = 1000.0;
const double YOFFSET_START2 = 2000.0;
const double YOFFSET_END2 = 3000.0;
const double TIME_PLUS = 1 * 100.0;
const double TIME_PLUS_LARGE = 10 * 1000.0;
} // namespace

class TossAnimationControllerTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
};

void TossAnimationControllerTestNg::SetUp()
{
    MockPipelineBase::SetUp();
}

void TossAnimationControllerTestNg::TearDown()
{
    MockPipelineBase::TearDown();
}

/**
 * @tc.name: TossAnimationControllerTest001
 * @tc.desc: Test TossAnimationController.
 * @tc.type: FUNC
 */
HWTEST_F(TossAnimationControllerTestNg, TossAnimationControllerTest001, TestSize.Level1)
{
    RefPtr<TossAnimationController> toss = AceType::MakeRefPtr<TossAnimationController>();
    toss->SetStart(YOFFSET_START1);
    toss->SetEnd(YOFFSET_END1);
    toss->timeEnd_ = toss->GetCurrentTime() + TIME_PLUS;
    auto ret = toss->Play();
    EXPECT_EQ(toss->yStart_, YOFFSET_START1);
    EXPECT_EQ(toss->yEnd_, YOFFSET_END1);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: TossAnimationControllerTest002
 * @tc.desc: Test TossAnimationController.
 * @tc.type: FUNC
 */
HWTEST_F(TossAnimationControllerTestNg, TossAnimationControllerTest002, TestSize.Level1)
{
    RefPtr<TossAnimationController> toss = AceType::MakeRefPtr<TossAnimationController>();
    toss->SetStart(YOFFSET_START1);
    toss->SetEnd(YOFFSET_END1);
    toss->timeEnd_ = toss->GetCurrentTime() + TIME_PLUS;
    auto ret = toss->Play();
    EXPECT_EQ(toss->yStart_, YOFFSET_START1);
    EXPECT_EQ(toss->yEnd_, YOFFSET_END1);
    EXPECT_TRUE(ret);
    toss->SetStart(YOFFSET_START2);
    toss->SetEnd(YOFFSET_END2);
    toss->timeEnd_ = toss->GetCurrentTime() + TIME_PLUS;
    ret = toss->Play();
    EXPECT_EQ(toss->yStart_, YOFFSET_START2);
    EXPECT_EQ(toss->yEnd_, YOFFSET_END2);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: TossAnimationControllerTest003
 * @tc.desc: Test TossAnimationController.
 * @tc.type: FUNC
 */
HWTEST_F(TossAnimationControllerTestNg, TossAnimationControllerTest003, TestSize.Level1)
{
    RefPtr<TossAnimationController> toss = AceType::MakeRefPtr<TossAnimationController>();
    toss->SetStart(YOFFSET_START1);
    toss->SetEnd(YOFFSET_END1);
    toss->timeEnd_ = toss->GetCurrentTime() - TIME_PLUS;
    auto ret = toss->Play();
    EXPECT_EQ(toss->yStart_, YOFFSET_START1);
    EXPECT_EQ(toss->yEnd_, YOFFSET_END1);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: TossAnimationControllerTest004
 * @tc.desc: Test TossAnimationController.
 * @tc.type: FUNC
 */
HWTEST_F(TossAnimationControllerTestNg, TossAnimationControllerTest004, TestSize.Level1)
{
    RefPtr<TossAnimationController> toss = AceType::MakeRefPtr<TossAnimationController>();
    toss->SetStart(YOFFSET_START1);
    toss->SetEnd(YOFFSET_START1);
    toss->timeEnd_ = toss->GetCurrentTime() + TIME_PLUS;
    auto ret = toss->Play();
    EXPECT_EQ(toss->yStart_, YOFFSET_START1);
    EXPECT_EQ(toss->yEnd_, YOFFSET_START1);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: TossAnimationControllerTest005
 * @tc.desc: Test TossAnimationController.
 * @tc.type: FUNC
 */
HWTEST_F(TossAnimationControllerTestNg, TossAnimationControllerTest005, TestSize.Level1)
{
    RefPtr<TossAnimationController> toss = AceType::MakeRefPtr<TossAnimationController>();
    toss->SetStart(YOFFSET_START1);
    toss->SetEnd(YOFFSET_END1);
    toss->timeEnd_ = toss->GetCurrentTime() + TIME_PLUS_LARGE;
    auto ret = toss->Play();
    EXPECT_EQ(toss->yStart_, YOFFSET_START1);
    EXPECT_EQ(toss->yEnd_, YOFFSET_END1);
    EXPECT_FALSE(ret);
}
} // namespace OHOS::Ace::NG