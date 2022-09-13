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

#include "base/log/log.h"
#include "core/components/swiper/render_swiper.h"
#include "core/components/test/unittest/mock/mock_render_common.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

class SwiperIndicatorTest : public RenderSwiper {
public:
    explicit SwiperIndicatorTest(const RefPtr<PipelineContext>& context)
    {
        std::list<RefPtr<Component>> componentChildren;
        for (uint32_t i = 0; i < 10; i++) {
            componentChildren.emplace_back(AceType::MakeRefPtr<BoxComponent>());
        }

        RefPtr<SwiperComponent> swiperComponent = AceType::MakeRefPtr<SwiperComponent>(componentChildren);
        Attach(context);
        Update(swiperComponent);
    }

    SwiperIndicatorTest() = default;

    static RefPtr<SwiperIndicatorTest> CreateIndicatorTest(const RefPtr<PipelineContext>& context)
    {
        return AceType::MakeRefPtr<SwiperIndicatorTest>(context);
    }

    virtual void UpdateIndicator()
    {
        return;
    }

    void SetCurrentIndex(int32_t index)
    {
        currentIndex_ = index;
    }

    void SetIndicatorAnimationFlag(bool isIndicatorAnimationStart)
    {
        isIndicatorAnimationStart_ = isIndicatorAnimationStart;
    }
};

class RenderSwiperTest : public testing::Test {
public:
    static void SetUpTestCase()
    {
        GTEST_LOG_(INFO) << "RenderSwiperTest SetUpTestCase";
    }

    static void TearDownTestCase()
    {
        GTEST_LOG_(INFO) << "RenderSwiperTest TearDownTestCase";
    }

    void SetUp() {}

    void TearDown() {}
};

/**
 * @tc.name: ShowPrevious001
 * @tc.desc: Test ShowPrevious interface of the swiper component for RTL
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderSwiperTest, ShowPrevious001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderSwiperTest ShowPrevious001 start";

    /**
     * @tc.steps: step1. Construct a SwiperComponent and RenderSwiper.
     */
    std::list<RefPtr<Component>> componentChildren;
    for (uint32_t i = 0; i < 10; i++) {
        componentChildren.emplace_back(AceType::MakeRefPtr<BoxComponent>());
    }
    RefPtr<SwiperComponent> swiperComponent = AceType::MakeRefPtr<SwiperComponent>(componentChildren);
    RefPtr<SwiperIndicatorTest> swiperIndicator = AceType::MakeRefPtr<SwiperIndicatorTest>();
    auto mockContext = MockRenderCommon::GetMockContext();
    swiperIndicator->Attach(mockContext);

    /**
     * @tc.steps: step2. Set text direction and component direction.
     */
    swiperComponent->SetTextDirection(TextDirection::RTL);
    swiperComponent->SetAxis(Axis::VERTICAL);
    swiperIndicator->Update(swiperComponent);
    swiperIndicator->SetCurrentIndex(3);

    /**
     * @tc.steps: step3. Run ShowPrevious interface.
     * @tc.expected: step3. The index state is correct.
     */
    swiperIndicator->ShowPrevious();
    EXPECT_EQ(swiperIndicator->GetCurrentIndex(), 3);

    /**
     * @tc.steps: step4. Set text direction and component direction.
     */
    swiperComponent->SetTextDirection(TextDirection::RTL);
    swiperComponent->SetAxis(Axis::HORIZONTAL);
    swiperIndicator->Update(swiperComponent);
    swiperIndicator->SetCurrentIndex(3);

    /**
     * @tc.steps: step5. Run ShowPrevious interface.
     * @tc.expected: step5. The index state is correct.
     */
    swiperIndicator->ShowPrevious();
    EXPECT_EQ(swiperIndicator->GetCurrentIndex(), 3);

    GTEST_LOG_(INFO) << "RenderSwiperTest ShowPrevious001 stop";
}

/**
 * @tc.name: ShowPrevious002
 * @tc.desc: Test ShowPrevious interface of the swiper component with animation on for RTL
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderSwiperTest, ShowPrevious002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderSwiperTest ShowPrevious002 start";

    /**
     * @tc.steps: step1. Construct a SwiperComponent and RenderSwiper.
     */
    std::list<RefPtr<Component>> componentChildren;
    for (uint32_t i = 0; i < 10; i++) {
        componentChildren.emplace_back(AceType::MakeRefPtr<BoxComponent>());
    }
    RefPtr<SwiperComponent> swiperComponent = AceType::MakeRefPtr<SwiperComponent>(componentChildren);
    RefPtr<SwiperIndicatorTest> swiperIndicator = AceType::MakeRefPtr<SwiperIndicatorTest>();
    auto mockContext = MockRenderCommon::GetMockContext();
    swiperIndicator->Attach(mockContext);

    /**
     * @tc.steps: step2. Set text direction and component direction.
     */
    swiperComponent->SetTextDirection(TextDirection::RTL);
    swiperComponent->SetAxis(Axis::VERTICAL);
    swiperIndicator->Update(swiperComponent);
    swiperIndicator->SetIndicatorAnimationFlag(true);

    /**
     * @tc.steps: step3. Run ShowPrevious interface.
     * @tc.expected: step3. The index state is correct.
     */
    swiperIndicator->ShowPrevious();
    EXPECT_EQ(swiperIndicator->GetCurrentIndex(), 0);

    /**
     * @tc.steps: step4. Set text direction and component direction.
     */
    swiperComponent->SetTextDirection(TextDirection::RTL);
    swiperComponent->SetAxis(Axis::HORIZONTAL);
    swiperIndicator->Update(swiperComponent);
    swiperIndicator->SetIndicatorAnimationFlag(true);

    /**
     * @tc.steps: step5. Run ShowPrevious interface.
     * @tc.expected: step5. The index state is correct.
     */
    swiperIndicator->ShowPrevious();
    EXPECT_EQ(swiperIndicator->GetCurrentIndex(), 9);

    GTEST_LOG_(INFO) << "RenderSwiperTest ShowPrevious002 stop";
}

/**
 * @tc.name: ShowNext001
 * @tc.desc: Test ShowNext interface of the swiper component for RTL
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderSwiperTest, ShowNext001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderSwiperTest ShowNext001 start";

    /**
     * @tc.steps: step1. Construct a SwiperComponent and RenderSwiper.
     */
    std::list<RefPtr<Component>> componentChildren;
    for (uint32_t i = 0; i < 10; i++) {
        componentChildren.emplace_back(AceType::MakeRefPtr<BoxComponent>());
    }
    RefPtr<SwiperComponent> swiperComponent = AceType::MakeRefPtr<SwiperComponent>(componentChildren);
    RefPtr<SwiperIndicatorTest> swiperIndicator = AceType::MakeRefPtr<SwiperIndicatorTest>();
    auto mockContext = MockRenderCommon::GetMockContext();
    swiperIndicator->Attach(mockContext);

    /**
     * @tc.steps: step2. Set text direction and component direction.
     */
    swiperComponent->SetTextDirection(TextDirection::RTL);
    swiperComponent->SetAxis(Axis::VERTICAL);
    swiperIndicator->Update(swiperComponent);
    swiperIndicator->SetCurrentIndex(3);

    /**
     * @tc.steps: step3. Run ShowNext interface.
     * @tc.expected: step3. The index state is correct.
     */
    swiperIndicator->ShowNext();
    EXPECT_EQ(swiperIndicator->GetCurrentIndex(), 3);

    /**
     * @tc.steps: step4. Set text direction and component direction.
     */
    swiperComponent->SetTextDirection(TextDirection::RTL);
    swiperComponent->SetAxis(Axis::HORIZONTAL);
    swiperIndicator->Update(swiperComponent);
    swiperIndicator->SetCurrentIndex(3);

    /**
     * @tc.steps: step5. Run ShowNext interface.
     * @tc.expected: step5. The index state is correct.
     */
    swiperIndicator->ShowNext();
    EXPECT_EQ(swiperIndicator->GetCurrentIndex(), 3);

    GTEST_LOG_(INFO) << "RenderSwiperTest ShowNext001 stop";
}

/**
 * @tc.name: ShowNext002
 * @tc.desc: Test ShowNext interface of the swiper component with animation on for RTL
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderSwiperTest, ShowNext002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderSwiperTest ShowNext002 start";

    /**
     * @tc.steps: step1. Construct a SwiperComponent and RenderSwiper.
     */
    std::list<RefPtr<Component>> componentChildren;
    for (uint32_t i = 0; i < 10; i++) {
        componentChildren.emplace_back(AceType::MakeRefPtr<BoxComponent>());
    }
    RefPtr<SwiperComponent> swiperComponent = AceType::MakeRefPtr<SwiperComponent>(componentChildren);
    RefPtr<SwiperIndicatorTest> swiperIndicator = AceType::MakeRefPtr<SwiperIndicatorTest>();
    auto mockContext = MockRenderCommon::GetMockContext();
    swiperIndicator->Attach(mockContext);

    /**
     * @tc.steps: step2. Set text direction and component direction.
     */
    swiperComponent->SetTextDirection(TextDirection::RTL);
    swiperComponent->SetAxis(Axis::VERTICAL);
    swiperIndicator->Update(swiperComponent);
    swiperIndicator->SetIndicatorAnimationFlag(true);

    /**
     * @tc.steps: step3. Run ShowNext interface.
     * @tc.expected: step3. The index state is correct.
     */
    swiperIndicator->ShowNext();
    EXPECT_EQ(swiperIndicator->GetCurrentIndex(), 0);

    /**
     * @tc.steps: step4. Set text direction and component direction.
     */
    swiperComponent->SetTextDirection(TextDirection::RTL);
    swiperComponent->SetAxis(Axis::HORIZONTAL);
    swiperIndicator->Update(swiperComponent);
    swiperIndicator->SetIndicatorAnimationFlag(true);

    /**
     * @tc.steps: step5. Run ShowNext interface.
     * @tc.expected: step5. The index state is correct.
     */
    swiperIndicator->ShowNext();
    EXPECT_EQ(swiperIndicator->GetCurrentIndex(), 1);

    GTEST_LOG_(INFO) << "RenderSwiperTest ShowNext002 stop";
}

/**
 * @tc.name: Tick001
 * @tc.desc: Test Tick of the swiper component for RTL
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderSwiperTest, Tick001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderSwiperTest Tick001 start";

    /**
     * @tc.steps: step1. Construct a SwiperComponent and RenderSwiper.
     */
    std::list<RefPtr<Component>> componentChildren;
    for (uint32_t i = 0; i < 10; i++) {
        componentChildren.emplace_back(AceType::MakeRefPtr<BoxComponent>());
    }
    RefPtr<SwiperComponent> swiperComponent = AceType::MakeRefPtr<SwiperComponent>(componentChildren);
    RefPtr<SwiperIndicatorTest> swiperIndicator = AceType::MakeRefPtr<SwiperIndicatorTest>();
    auto mockContext = MockRenderCommon::GetMockContext();
    swiperIndicator->Attach(mockContext);

    /**
     * @tc.steps: step2. Set text direction and component direction.
     */
    swiperComponent->SetTextDirection(TextDirection::RTL);
    swiperComponent->SetAxis(Axis::VERTICAL);

    /**
     * @tc.steps: step3. Run Update interface.
     * @tc.expected: step3. The index state is correct.
     */
    swiperComponent->SetAutoPlay(true);
    swiperComponent->SetShow(true);
    swiperIndicator->Update(swiperComponent);
    sleep(3);
    EXPECT_EQ(swiperIndicator->GetCurrentIndex(), 0);

    /**
     * @tc.steps: step4. Set text direction and component direction.
     */
    swiperComponent->SetTextDirection(TextDirection::RTL);
    swiperComponent->SetAxis(Axis::HORIZONTAL);

    /**
     * @tc.steps: step5. Run Update interface.
     * @tc.expected: step5. The index state is correct.
     */
    swiperComponent->SetAutoPlay(true);
    swiperComponent->SetShow(true);
    swiperIndicator->Update(swiperComponent);
    sleep(3);
    EXPECT_EQ(swiperIndicator->GetCurrentIndex(), 0);

    GTEST_LOG_(INFO) << "RenderSwiperTest Tick001 stop";
}

} // namespace OHOS::Ace
