/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/test/unittest/image/image_test_utils.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

class RenderImageTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void RenderImageTest::SetUpTestCase() {}
void RenderImageTest::TearDownTestCase() {}
void RenderImageTest::SetUp() {}
void RenderImageTest::TearDown() {}

/**
 * @tc.name: GenerateRepeatRects001
 * @tc.desc: Verify that GenerateRepeatRects can generate all rects in all direction.
 * @tc.type: FUNC
 * @tc.require: AR000DAQUP
 * @tc.author: chenxuankai
 */
HWTEST_F(RenderImageTest, GenerateRepeatRects001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a fundamentalRect, set parentSize and imageRepeat and then call GenerateRepeatRects.
     */
    auto rectList = GetRectList(ImageRepeat::REPEAT, PARENT_SIZE);

    /**
     * @tc.steps: step2. Verify whether the receList has 4 expected rects.
     * @tc.expected: step2. The rectList has 4 expected rects.
     */
    ASSERT_TRUE(rectList.size() == REPEAT_LIST_LENGTH);
    VerifyRectSize(rectList, Size(SMALL_LENGTH, SMALL_LENGTH));
    auto iter = rectList.begin();
    ASSERT_TRUE(iter->GetOffset() == Offset(MINUS_EXTRA_SMALL_LENGTH, MINUS_EXTRA_SMALL_LENGTH));
    ASSERT_TRUE((++iter)->GetOffset() == Offset(EXTRA_SMALL_LENGTH, MINUS_EXTRA_SMALL_LENGTH));
    ASSERT_TRUE((++iter)->GetOffset() == Offset(MINUS_EXTRA_SMALL_LENGTH, EXTRA_SMALL_LENGTH));
    ASSERT_TRUE((++iter)->GetOffset() == Offset(EXTRA_SMALL_LENGTH, EXTRA_SMALL_LENGTH));
}

/**
 * @tc.name: GenerateRepeatRects002
 * @tc.desc: Verify that GenerateRepeatRects can generate all rects horizontally.
 * @tc.type: FUNC
 * @tc.require: AR000DAQUP
 * @tc.author: chenxuankai
 */
HWTEST_F(RenderImageTest, GenerateRepeatRects002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a fundamentalRect, set parentSize and imageRepeat and then call GenerateRepeatRects.
     */
    auto rectList = GetRectList(ImageRepeat::REPEATX, PARENT_SIZE);

    /**
     * @tc.steps: step2. Verify whether the receList has 2 expected rects.
     * @tc.expected: step2. The rectList has 2 expected rects.
     */
    ASSERT_TRUE(rectList.size() == REPEATX_LIST_LENGTH);
    VerifyRectSize(rectList, Size(SMALL_LENGTH, SMALL_LENGTH));
    auto iter = rectList.begin();
    ASSERT_TRUE(iter->GetOffset() == Offset(MINUS_EXTRA_SMALL_LENGTH, EXTRA_SMALL_LENGTH));
    ASSERT_TRUE((++iter)->GetOffset() == Offset(EXTRA_SMALL_LENGTH, EXTRA_SMALL_LENGTH));
}

/**
 * @tc.name: GenerateRepeatRects003
 * @tc.desc: Verify that GenerateRepeatRects can generate all rects vertically.
 * @tc.type: FUNC
 * @tc.require: AR000DAQUP
 * @tc.author: chenxuankai
 */
HWTEST_F(RenderImageTest, GenerateRepeatRects003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a fundamentalRect, set parentSize and imageRepeat and then call GenerateRepeatRects.
     */
    auto rectList = GetRectList(ImageRepeat::REPEATY, PARENT_SIZE);

    /**
     * @tc.steps: step2. Verify whether the receList has 2 expected rects.
     * @tc.expected: step2. The rectList has 2 expected rects.
     */
    ASSERT_TRUE(rectList.size() == REPEATY_LIST_LENGTH);
    VerifyRectSize(rectList, Size(SMALL_LENGTH, SMALL_LENGTH));
    auto iter = rectList.begin();
    ASSERT_TRUE(iter->GetOffset() == Offset(EXTRA_SMALL_LENGTH, MINUS_EXTRA_SMALL_LENGTH));
    ASSERT_TRUE((++iter)->GetOffset() == Offset(EXTRA_SMALL_LENGTH, EXTRA_SMALL_LENGTH));
}

/**
 * @tc.name: GenerateRepeatRects004
 * @tc.desc: Verify that GenerateRepeatRects can generate a single rect.
 * @tc.type: FUNC
 * @tc.require: AR000DAQUP
 * @tc.author: chenxuankai
 */
HWTEST_F(RenderImageTest, GenerateRepeatRects004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a fundamentalRect, set parentSize and imageRepeat and then call GenerateRepeatRects.
     */
    auto rectList = GetRectList(ImageRepeat::NOREPEAT, PARENT_SIZE);

    /**
     * @tc.steps: step2. Verify whether the receList has 1 expected rects.
     * @tc.expected: step2. The rectList has 1 expected rects.
     */
    ASSERT_TRUE(rectList.size() == NOREPEAT_LIST_LENGTH);
    VerifyRectSize(rectList, Size(SMALL_LENGTH, SMALL_LENGTH));
    auto iter = rectList.begin();
    ASSERT_TRUE(iter->GetOffset() == Offset(EXTRA_SMALL_LENGTH, EXTRA_SMALL_LENGTH));
}

/**
 * @tc.name: GenerateRepeatRects005
 * @tc.desc: Verify that GenerateRepeatRects can work correctly when parentSize .
 * @tc.type: FUNC
 * @tc.require: AR000DAQUP
 * @tc.author: chenxuankai
 */
HWTEST_F(RenderImageTest, GenerateRepeatRects005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a fundamentalRect, set parentSize and imageRepeat and then call GenerateRepeatRects.
     */
    auto rectList = GetRectList(ImageRepeat::NOREPEAT, Size(EXTRA_SMALL_LENGTH, EXTRA_SMALL_LENGTH));

    /**
     * @tc.steps: step2. Verify whether the receList has 1 expected rects.
     * @tc.expected: step2. The rectList has 1 expected rects.
     */
    ASSERT_TRUE(rectList.size() == NOREPEAT_LIST_LENGTH);
    VerifyRectSize(rectList, Size(SMALL_LENGTH, SMALL_LENGTH));
    auto iter = rectList.begin();
    ASSERT_TRUE(iter->GetOffset() == Offset(EXTRA_SMALL_LENGTH, EXTRA_SMALL_LENGTH));
}

/**
 * @tc.name: DecideLayoutSize001
 * @tc.desc: Verify that RenderImage can decide a right layout size when width and height are set and maxSize > piSize.
 * @tc.type: FUNC
 * @tc.require: AR000DAQUM
 * @tc.author: chenxuankai
 */
HWTEST_F(RenderImageTest, DecideLayoutSize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create renderImage with expected maxSize, width and height and then call PerformLayout()
     */
    RefPtr<RenderRoot> root = CreateRenderRoot(Size(LARGE_LENGTH, SMALL_LENGTH));
    RefPtr<RenderImage> renderImage = CreateRenderImage(LARGE_LENGTH, SMALL_LENGTH);
    auto mockContext = GetMockContext();
    renderImage->Attach(mockContext);
    root->AddChild(renderImage);
    root->PerformLayout();

    /**
     * @tc.steps: step2. Verify that layout size is Size(LARGE_LENGTH, SMALL_LENGTH).
     * @tc.expected: step2. layout size is Size(LARGE_LENGTH, SMALL_LENGTH).
     */
    ASSERT_TRUE(renderImage->GetLayoutSize() == Size(LARGE_LENGTH, SMALL_LENGTH));
}

/**
 * @tc.name: DecideLayoutSize002
 * @tc.desc: Verify that RenderImage can decide a right layout size when width and height are set and maxSize < picSize.
 * @tc.type: FUNC
 * @tc.require: AR000DAQUM
 * @tc.author: chenxuankai
 */
HWTEST_F(RenderImageTest, DecideLayoutSize002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create renderImage with expected maxSize, width and height and then call PerformLayout()
     */
    RefPtr<RenderRoot> root = CreateRenderRoot(Size(SMALL_LENGTH, EXTRA_SMALL_LENGTH));
    RefPtr<RenderImage> renderImage = CreateRenderImage(LARGE_LENGTH, SMALL_LENGTH);
    auto mockContext = GetMockContext();
    renderImage->Attach(mockContext);
    root->AddChild(renderImage);
    root->PerformLayout();

    /**
     * @tc.steps: step2. Verify that layout size is Size(SMALL_LENGTH, EXTRA_SMALL_LENGTH).
     * @tc.expected: step2. layout size is Size(SMALL_LENGTH, EXTRA_SMALL_LENGTH).
     */
    ASSERT_TRUE(renderImage->GetLayoutSize() == Size(SMALL_LENGTH, EXTRA_SMALL_LENGTH));
}

/**
 * @tc.name: DecideLayoutSize003
 * @tc.desc: Verify that RenderImage can decide a right layout size when maxSize > picSize with no width and height.
 * @tc.type: FUNC
 * @tc.require: AR000DAQUM
 * @tc.author: chenxuankai
 */
HWTEST_F(RenderImageTest, DecideLayoutSize003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create renderImage with expected maxSize, width and height and then call PerformLayout()
     */
    RefPtr<RenderRoot> root = CreateRenderRoot(Size(EXTRA_LARGE_LENGTH, LARGE_LENGTH));
    RefPtr<RenderImage> renderImage = CreateRenderImage(DEFAULT_LENGTH, DEFAULT_LENGTH);
    auto mockContext = GetMockContext();
    renderImage->Attach(mockContext);
    root->AddChild(renderImage);
    root->PerformLayout();

    /**
     * @tc.steps: step2. Verify that layout size is Size(LARGE_LENGTH, LARGE_LENGTH).
     * @tc.expected: step2. layout size is Size(LARGE_LENGTH, LARGE_LENGTH).
     */
    ASSERT_TRUE(renderImage->GetLayoutSize() == Size(LARGE_LENGTH, LARGE_LENGTH));
}

/**
 * @tc.name: DecideLayoutSize004
 * @tc.desc: Verify that RenderImage can decide a right layout size when maxSize < picSize with no width and height.
 * @tc.type: FUNC
 * @tc.require: AR000DAQUM
 * @tc.author: chenxuankai
 */
HWTEST_F(RenderImageTest, DecideLayoutSize004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create renderImage with expected maxSize, width and height and then call PerformLayout()
     */
    RefPtr<RenderRoot> root = CreateRenderRoot(Size(SMALL_LENGTH, EXTRA_SMALL_LENGTH));
    RefPtr<RenderImage> renderImage = CreateRenderImage(DEFAULT_LENGTH, DEFAULT_LENGTH);
    auto mockContext = GetMockContext();
    renderImage->Attach(mockContext);
    root->AddChild(renderImage);
    root->PerformLayout();

    /**
     * @tc.steps: step2. Verify that layout size is Size(EXTRA_SMALL_LENGTH, EXTRA_SMALL_LENGTH).
     * @tc.expected: step2. layout size is Size(EXTRA_SMALL_LENGTH, EXTRA_SMALL_LENGTH).
     */
    ASSERT_TRUE(renderImage->GetLayoutSize() == Size(SMALL_LENGTH, EXTRA_SMALL_LENGTH));
}

} // namespace OHOS::Ace
