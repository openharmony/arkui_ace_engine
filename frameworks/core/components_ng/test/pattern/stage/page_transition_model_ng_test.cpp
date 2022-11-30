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
#define private public
#define protect public
#include "core/components_ng/pattern/stage/page_transition_model_ng.h"
#undef protect
#undef private

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
class PageTransitionModelNGTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    PageTransitionModelNG manager_;
};

void PageTransitionModelNGTest::SetUpTestCase() {}
void PageTransitionModelNGTest::TearDownTestCase() {}
void PageTransitionModelNGTest::SetUp() {}
void PageTransitionModelNGTest::TearDown() {}

void TmpVoid(RouteType, const float&)
{
    return;
}

/**
 * @tc.name: PageTransitionModelNGTestt001
 * @tc.desc: Test all the properties of PageTransitionModelNGTest
 * @tc.type: FUNC
 */
HWTEST_F(PageTransitionModelNGTest, PageTransitionModelNGTest001, TestSize.Level1)
{
    manager_.SetSlideEffect(SlideEffect::NONE);

    const NG::TranslateOptions option;
    manager_.SetTranslateEffect(option);

    const NG::ScaleOptions option1;
    manager_.SetScaleEffect(option1);

    float opacity = 1.0f;
    manager_.SetOpacityEffect(opacity);

    PageTransitionEventFunc handler = TmpVoid;
    manager_.SetOnEnter(std::move(handler));
    manager_.SetOnExit(std::move(handler));

    manager_.Create();
    manager_.Pop();
}
} // namespace OHOS::Ace::NG
