/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/window_scene/screen/screen_model.h"
#include "core/components_ng/pattern/window_scene/screen/screen_pattren.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class ScreenPatternTest : public testing::Test {
public:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
};

/**
 * @tc.name: ScreenPatternTest001
 * @tc.desc: Screen test
 * @tc.type: FUNC
 */
HWTEST_F(ScreenPatternTest, ScreenPatternTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ScreenModel.
     */
    auto model = ScreenModel();
    uint64_t screenId = 0;
    model.Create(screenId);

    auto screenNode =
        AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    EXPECT_EQ(screenNode, nullptr);
}
} // namespace OHOS::Ace::NG
