/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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
// #include "core/components_v2/swiper/swiper_element.h"
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
 * @tc.name: continuation001
 * @tc.desc: Test state transfer of the swiper component
 * @tc.type: FUNC
 * @tc.require:I5NC9F
 */
HWTEST_F(RenderSwiperTest, continuation001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderSwiperTest continuation001 start";

    /**
     * @tc.steps: step1. Construct a SwiperComponent, set current index.
     */
    std::list<RefPtr<Component>> componentChildren;
    for (uint32_t i = 0; i < 10; i++) {
        componentChildren.emplace_back(AceType::MakeRefPtr<BoxComponent>());
    }
    RefPtr<SwiperComponent> swiperComponent = AceType::MakeRefPtr<SwiperComponent>(componentChildren);
    RefPtr<SwiperIndicatorTest> swiperIndicator = AceType::MakeRefPtr<SwiperIndicatorTest>();
    swiperIndicator->SetCurrentIndex(3);
    
    /**
     * @tc.steps: step2. Store index state of swiper component.
     * @tc.expected: step2. The return string is correct.
     */
    std::string info = swiperIndicator->ProvideRestoreInfo();
    std::string expectStateResult = "{\"index\":0,\"currentIndex\":3,\"swipeToIndex\":-1}";
    EXPECT_EQ(info, expectStateResult);

    /**
     * @tc.steps: step3. Restore index state of swiper component.
     * @tc.expected: step3. The index state is correct.
     */  
    swiperIndicator->SetRestoreInfo(expectStateResult);
    auto mockContext = MockRenderCommon::GetMockContext();
    swiperIndicator->Attach(mockContext);
    swiperIndicator->Update(swiperComponent);
    EXPECT_EQ(swiperIndicator->GetCurrentIndex(), 3);

    /**
     * @tc.steps: step4. Second Update doesn't restore the state.
     * @tc.expected: step4. The stored string is empty.
     */ 
    swiperIndicator->Update(swiperComponent);
    EXPECT_TRUE(swiperIndicator->GetRestoreInfo().empty());

    /**
     * @tc.steps: step5. Restore index state from invalid json string.
     * @tc.expected: step5. The index state is unchanged.
     */  
    std::string invalidInfo = "index\":0,\"currentIndex\":2,\"swipeToIndex\":-1";
    swiperIndicator->SetRestoreInfo(invalidInfo);
    swiperIndicator->Update(swiperComponent);
    EXPECT_EQ(swiperIndicator->GetCurrentIndex(), 3);

    GTEST_LOG_(INFO) << "RenderSwiperTest continuation001 stop";
}

} // namespace OHOS::Ace
