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
#include "swiper_test_ng.h"
namespace OHOS::Ace::NG {
namespace {
constexpr float EXIT_SCALE_VALUE = 0.6f;
constexpr int32_t EXIT_SCALE_DURATION = 750;
constexpr int32_t EXIT_OFFSET_DURATION = 750;
constexpr int32_t EXIT_BLUR_VALUE = 30;
constexpr int32_t EXIT_BLUR_DELAY = 150;
constexpr int32_t EXIT_BLUR_DURATION = 250;
constexpr int32_t EXIT_ALPHA_DURATION = 750;
constexpr int32_t ENTRY_COLOR_DURATION = 40;
constexpr int32_t NO_ANIMAION_DEFAULT_DURATION = 400;
constexpr int32_t VERTICAL_ANIMAION_DEFAULT_DURATION = 330;
constexpr int32_t HORIZONTAL_ANIMAION_DEFAULT_DURATION = 750;

constexpr float HORIZONTAL_SCALE_REDUCTION_FACTOR = 0.4f;
constexpr float HORIZONTAL_BLUR_MIN_RATIO = 0.2f;
constexpr float HORIZONTAL_BLUR_REDUCTION_FACTOR = 750.0f / 250.0f * 30.0f;
constexpr float HORIZONTAL_BLUR_MAX_VALUE = 30.0f;
constexpr float HORIZONTAL_ALPHA_REDUCTION_FACTOR = 750.0f / 500.0f;
constexpr float HORIZONTAL_ENTRY_SCALE_INITIAL_VALUE = 0.6f;
constexpr float HORIZONTAL_EXIT_SCALE_FINAL_VALUE = 0.6f;

constexpr float VERTICAL_EXIT_SCALE_MIN_VALUE = 0.95f;
constexpr float VERTICAL_EXIT_BLUR_REDUCTION_FACTOR = 3728.0f / 23.0f;
constexpr float VERTICAL_EXIT_BLUR_MAX_VALUE = 40.0f;
constexpr float VERTICAL_EXIT_SCALE_REDUCTION_FACTOR = 466.0f / 2300.0f;
constexpr float VERTICAL_EXIT_ALPHA_REDUCTION_FACTOR = 466.0f / 115.0f;
constexpr float VERTICAL_ENTRY_BLUR_ALPHA_FACTOR = 2.5f;

constexpr float VERTICAL_ENTRY_SCALE_REDUCTION_FACTOR = 0.125f;
constexpr float VERTICAL_ENTRY_OFFSET_PART = 0.6f;
constexpr float VERTICAL_ENTRY_SCALE_INITIAL_VALUE = 1.05f;
constexpr float VERTICAL_ENTRY_BLUR_REDUCTION_FACTOR = 100.0f;
constexpr float VERTICAL_ENTRY_BLUR_INITIAL_VALUE = 40.0f;
} // namespace

class ArcSwiperPatternTestNg : public SwiperTestNg {
public:
private:
    RefPtr<FrameNode> CreateFrameNode();
    SwiperItemInfo CreateSwiperItemInfo(float startPos, float endPos, const RefPtr<FrameNode>& node);
    SwiperLayoutAlgorithm::PositionMap CreateSwiperItemPostion();
    ArcSwiperPattern::AnimationParam CreateScaleParam(float value, int32_t duration, RefPtr<FrameNode>& frameNode);
    ArcSwiperPattern::AnimationParam
        CreateBlurParam(float value, int32_t delay, int32_t duration, RefPtr<FrameNode>& frameNode);
    ArcSwiperPattern::AnimationParam
        CreateAlphaParam(float value, int32_t delay, int32_t duration, RefPtr<FrameNode>& frameNode);

    float CalcPercent(float swiperWidth, float startPos, bool exit);
    float CalcStartByPercent(float value, float swiperWidth, bool exit);
    float CalcHorizontalScrollScale(float swiperWidth, float startPos, bool exit);
    float CalcHorizontalScrollExitScale(float percent);
    float CalcHorizontalScrollEntryScale(float percent);

    float CalcHorizontalScrollBlur(float swiperWidth, float startPos, bool exit);
    float CalcHorizontalScrollExitBlur(float percent);
    float CalcHorizontalScrollEntryBlur(float percent);

    float CalcHorizontalScrollAlpha(float swiperWidth, float startPos, bool exit);
    float CalcHorizontalScrollExitAlpha(float percent);
    float CalcHorizontalScrollEntryAlpha(float percent);

    float CalcHorizontalScrollStartPosByAlpha(float alpha, float swiperWidth, bool exit);
    float CalcHorizontalScrollStartPosByExitAlpha(float alpha, float swiperWidth);
    float CalcHorizontalScrollStartPosByEntryAlpha(float alpha, float swiperWidth);

    float CalcHorizontalScrollStartPosByScale(float scale, float swiperWidth, bool exit);
    float CalcHorizontalScrollStartPosByExitScale(float scale, float swiperWidth);
    float CalcHorizontalScrollStartPosByEntryScale(float scale, float swiperWidth);

    float CalcHorizontalScrollStartPosByBlur(float blur, float swiperWidth, bool exit);
    float CalcHorizontalScrollStartPosByExitBlur(float blur, float swiperWidth);
    float CalcHorizontalScrollStartPosByEntryBlur(float blur, float swiperWidth);

    float CalcVerticalScrollScale(float swiperWidth, float startPos, bool exit);
    float CalcVerticalScrollExitScale(float percent);
    float CalcVerticalScrollEntryScale(float percent);

    float CalcVerticalScrollAlpha(float swiperWidth, float startPos, bool exit);
    float CalcVerticalScrollExitAlpha(float percent);
    float CalcVerticalScrollEntryAlpha(float percent);

    float CalcVerticalScrollBlur(float swiperWidth, float startPos, bool exit);
    float CalcVerticalScrollExitBlur(float percent);
    float CalcVerticalScrollEntryBlur(float percent);

    float CalcVerticalScrollStartPosByAlpha(float alpha, float swiperWidth, bool exit);
    float CalcVerticalScrollStartPosByExitAlpha(float alpha, float swiperWidth);
    float CalcVerticalScrollStartPosByEntryAlpha(float alpha, float swiperWidth);

    float CalcVerticalScrollStartPosByScale(float scale, float swiperWidth, bool exit);
    float CalcVerticalScrollStartPosByExitScale(float scale, float swiperWidth);
    float CalcVerticalScrollStartPosByEntryScale(float scale, float swiperWidth);

    float CalcVerticalScrollStartPosByBlur(float blur, float swiperWidth, bool exit);
    float CalcVerticalScrollStartPosByExitBlur(float blur, float swiperWidth);
    float CalcVerticalScrollStartPosByEntryBlur(float blur, float swiperWidth);

    bool FindItemByIndex(const RefPtr<ArcSwiperPattern>& pattern, int32_t index, SwiperItemInfo& item);
};

RefPtr<FrameNode> ArcSwiperPatternTestNg::CreateFrameNode()
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    return FrameNode::CreateFrameNode("node", nodeId, AceType::MakeRefPtr<ArcSwiperPattern>());
}

SwiperItemInfo ArcSwiperPatternTestNg::CreateSwiperItemInfo(float startPos, float endPos, const RefPtr<FrameNode>& node)
{
    SwiperItemInfo item;
    item.startPos = startPos;
    item.endPos = endPos;
    item.node = node;
    return item;
}

SwiperLayoutAlgorithm::PositionMap ArcSwiperPatternTestNg::CreateSwiperItemPostion()
{
    SwiperLayoutAlgorithm::PositionMap itemPosition;
    auto node1 = CreateFrameNode();
    auto item1 = CreateSwiperItemInfo(0, 20, node1);

    auto node2 = CreateFrameNode();
    auto item2 = CreateSwiperItemInfo(21, 40, node2);

    itemPosition.insert(std::make_pair(0, item1));
    itemPosition.insert(std::make_pair(1, item2));
    return itemPosition;
}

ArcSwiperPattern::AnimationParam ArcSwiperPatternTestNg::CreateScaleParam(float value, int32_t duration,
    RefPtr<FrameNode>& frameNode)
{
    ArcSwiperPattern::AnimationParam param;
    param.type = ArcSwiperPattern::AnimationType::TYPE_SCALE;
    param.frameNode = frameNode;
    param.scaleValue = value;

    AnimationOption option;
    option.SetDuration(duration);
    option.SetCurve(Curves::FRICTION);
    param.option = option;
    return param;
}

ArcSwiperPattern::AnimationParam ArcSwiperPatternTestNg::CreateBlurParam(float value, int32_t delay, int32_t duration,
    RefPtr<FrameNode>& frameNode)
{
    ArcSwiperPattern::AnimationParam param;
    param.type = ArcSwiperPattern::AnimationType::TYPE_BLUR;
    param.frameNode = frameNode;
    param.blurValue = value;

    AnimationOption option;
    option.SetDelay(delay);
    option.SetDuration(duration);
    option.SetCurve(Curves::LINEAR);
    param.option = option;
    return param;
}

ArcSwiperPattern::AnimationParam ArcSwiperPatternTestNg::CreateAlphaParam(float value, int32_t delay, int32_t duration,
    RefPtr<FrameNode>& frameNode)
{
    ArcSwiperPattern::AnimationParam param;
    param.type = ArcSwiperPattern::AnimationType::TYPE_ALPHA;
    param.frameNode = frameNode;
    param.opacityValue = value;

    AnimationOption option;
    option.SetDelay(delay);
    option.SetDuration(duration);
    option.SetCurve(Curves::LINEAR);
    param.option = option;
    return param;
}

float ArcSwiperPatternTestNg::CalcPercent(float swiperWidth, float startPos, bool exit)
{
    auto percent = 0.0f;
    if (swiperWidth != 0) {
        if (exit) {
            percent = std::abs(startPos) / swiperWidth;
        } else {
            percent = (swiperWidth - std::abs(startPos)) / swiperWidth;
        }
    }
    return percent;
}

float ArcSwiperPatternTestNg::CalcStartByPercent(float percent, float swiperWidth, bool exit)
{
    if (exit) {
        return percent * swiperWidth;
    } else {
        return swiperWidth - percent * swiperWidth;
    }
}

float ArcSwiperPatternTestNg::CalcHorizontalScrollStartPosByScale(float scale, float swiperWidth, bool exit)
{
    if (exit) {
        return CalcHorizontalScrollStartPosByExitScale(scale, swiperWidth);
    } else {
        return CalcHorizontalScrollStartPosByEntryScale(scale, swiperWidth);
    }
}

float ArcSwiperPatternTestNg::CalcHorizontalScrollStartPosByExitScale(float scale, float swiperWidth)
{
    auto percent = (1.0f - scale) / HORIZONTAL_SCALE_REDUCTION_FACTOR;
    return percent * swiperWidth;
}

float ArcSwiperPatternTestNg::CalcHorizontalScrollStartPosByEntryScale(float scale, float swiperWidth)
{
    float percent = (scale - HORIZONTAL_ENTRY_SCALE_INITIAL_VALUE) / HORIZONTAL_SCALE_REDUCTION_FACTOR;
    return swiperWidth - percent * swiperWidth;
}

float ArcSwiperPatternTestNg::CalcHorizontalScrollScale(float swiperWidth, float startPos, bool exit)
{
    float value = 0.0f;
    float percent = CalcPercent(swiperWidth, startPos, exit);
    if (exit) {
        value = CalcHorizontalScrollExitScale(percent);
    } else {
        value = CalcHorizontalScrollEntryScale(percent);
    }
    return value;
}

float ArcSwiperPatternTestNg::CalcHorizontalScrollExitScale(float percent)
{
    auto value = 1.0f - percent * HORIZONTAL_SCALE_REDUCTION_FACTOR;
    if (value < HORIZONTAL_EXIT_SCALE_FINAL_VALUE) {
        value = HORIZONTAL_EXIT_SCALE_FINAL_VALUE;
    }
    return value;
}

float ArcSwiperPatternTestNg::CalcHorizontalScrollEntryScale(float percent)
{
    auto value = HORIZONTAL_ENTRY_SCALE_INITIAL_VALUE + HORIZONTAL_SCALE_REDUCTION_FACTOR * percent;
    if (value >= 1.0f) {
        value = 1.0f;
    }
    return value;
}

float ArcSwiperPatternTestNg::CalcHorizontalScrollStartPosByBlur(float blur, float swiperWidth, bool exit)
{
    if (exit) {
        return CalcHorizontalScrollStartPosByExitBlur(blur, swiperWidth);
    } else {
        return CalcHorizontalScrollStartPosByEntryBlur(blur, swiperWidth);
    }
}

float ArcSwiperPatternTestNg::CalcHorizontalScrollStartPosByExitBlur(float blur, float swiperWidth)
{
    float percent = blur / HORIZONTAL_BLUR_REDUCTION_FACTOR;
    return percent * swiperWidth;
}

float ArcSwiperPatternTestNg::CalcHorizontalScrollStartPosByEntryBlur(float blur, float swiperWidth)
{
    float percent = (HORIZONTAL_BLUR_MAX_VALUE - blur) / HORIZONTAL_BLUR_REDUCTION_FACTOR;
    return swiperWidth - percent * swiperWidth;
}

float ArcSwiperPatternTestNg::CalcHorizontalScrollBlur(float swiperWidth, float startPos, bool exit)
{
    float value = 0.0f;
    float percent = CalcPercent(swiperWidth, startPos, exit);
    if (exit) {
        value = CalcHorizontalScrollExitBlur(percent);
    } else {
        value = CalcHorizontalScrollEntryBlur(percent);
    }
    return value;
}

float ArcSwiperPatternTestNg::CalcHorizontalScrollExitBlur(float percent)
{
    float value = 0.0f;
    if (percent > HORIZONTAL_BLUR_MIN_RATIO) {
        value = HORIZONTAL_BLUR_REDUCTION_FACTOR * percent;
        if (value > HORIZONTAL_BLUR_MAX_VALUE) {
            value = HORIZONTAL_BLUR_MAX_VALUE;
        }
    }
    return value;
}

float ArcSwiperPatternTestNg::CalcHorizontalScrollEntryBlur(float percent)
{
    float value = 0.0f;
    value = HORIZONTAL_BLUR_MAX_VALUE - HORIZONTAL_BLUR_REDUCTION_FACTOR * percent;
    if (value < 0.0f) {
        value = 0.0f;
    }
    return value;
}

float ArcSwiperPatternTestNg::CalcHorizontalScrollStartPosByAlpha(float alpha, float swiperWidth, bool exit)
{
    if (swiperWidth == 0.0f) {
        return 0.0f;
    }
    if (exit) {
        return CalcHorizontalScrollStartPosByExitAlpha(alpha, swiperWidth);
    } else {
        return CalcHorizontalScrollStartPosByEntryAlpha(alpha, swiperWidth);
    }
}

float ArcSwiperPatternTestNg::CalcHorizontalScrollStartPosByExitAlpha(float alpha, float swiperWidth)
{
    if (swiperWidth == 0.0f) {
        return 0.0f;
    }
    float percent = 1.0f - alpha;
    return percent * swiperWidth;
}

float ArcSwiperPatternTestNg::CalcHorizontalScrollStartPosByEntryAlpha(float alpha, float swiperWidth)
{
    if (swiperWidth == 0.0f) {
        return 0.0f;
    }
    float percent = alpha / HORIZONTAL_ALPHA_REDUCTION_FACTOR;
    return swiperWidth - percent * swiperWidth;
}

float ArcSwiperPatternTestNg::CalcHorizontalScrollAlpha(float swiperWidth, float startPos, bool exit)
{
    float value = 0.0f;
    float percent = CalcPercent(swiperWidth, startPos, exit);
    if (exit) {
        value = CalcHorizontalScrollExitAlpha(percent);
    } else {
        value = CalcHorizontalScrollEntryAlpha(percent);
    }
    return value;
}

float ArcSwiperPatternTestNg::CalcHorizontalScrollExitAlpha(float percent)
{
    float value = 0.0f;
    value = 1.0f - percent;
    if (value < 0.0f) {
        value = 0.0f;
    }
    return value;
}

float ArcSwiperPatternTestNg::CalcHorizontalScrollEntryAlpha(float percent)
{
    float value = 0.0f;
    value = HORIZONTAL_ALPHA_REDUCTION_FACTOR * percent;
    if (value > 1.0f) {
        value = 1.0f;
    }
    return value;
}

float ArcSwiperPatternTestNg::CalcVerticalScrollStartPosByScale(float scale, float swiperWidth, bool exit)
{
    if (exit) {
        return CalcVerticalScrollStartPosByExitScale(scale, swiperWidth);
    } else {
        return CalcVerticalScrollStartPosByEntryScale(scale, swiperWidth);
    }
}

float ArcSwiperPatternTestNg::CalcVerticalScrollStartPosByExitScale(float scale, float swiperWidth)
{
    auto percent = (1.0f - scale * VERTICAL_EXIT_SCALE_REDUCTION_FACTOR) / VERTICAL_EXIT_SCALE_REDUCTION_FACTOR;
    return percent * swiperWidth;
}

float ArcSwiperPatternTestNg::CalcVerticalScrollStartPosByEntryScale(float scale, float swiperWidth)
{
    float percent = (scale + VERTICAL_ENTRY_SCALE_REDUCTION_FACTOR * VERTICAL_ENTRY_OFFSET_PART) /
                        VERTICAL_ENTRY_SCALE_REDUCTION_FACTOR -
                    VERTICAL_ENTRY_SCALE_INITIAL_VALUE / VERTICAL_ENTRY_SCALE_REDUCTION_FACTOR;
    return swiperWidth - percent * swiperWidth;
}

float ArcSwiperPatternTestNg::CalcVerticalScrollScale(float swiperWidth, float startPos, bool exit)
{
    float value = 0.0f;
    float percent = CalcPercent(swiperWidth, startPos, exit);
    if (exit) {
        value = CalcVerticalScrollExitScale(percent);
    } else {
        value = CalcVerticalScrollEntryScale(percent);
    }
    return value;
}

float ArcSwiperPatternTestNg::CalcVerticalScrollExitScale(float percent)
{
    float value = 1.0f - percent * VERTICAL_EXIT_SCALE_REDUCTION_FACTOR;
    if (value < VERTICAL_EXIT_SCALE_MIN_VALUE) {
        value = VERTICAL_EXIT_SCALE_MIN_VALUE;
    }
    return value;
}

float ArcSwiperPatternTestNg::CalcVerticalScrollEntryScale(float percent)
{
    float value = 0.0f;
    if (percent >= VERTICAL_ENTRY_OFFSET_PART) {
        value = VERTICAL_ENTRY_SCALE_INITIAL_VALUE -
                VERTICAL_ENTRY_SCALE_REDUCTION_FACTOR * (percent - VERTICAL_ENTRY_OFFSET_PART);
        if (value < 1.0f) {
            value = 1.0f;
        }
    }
    return value;
}

float ArcSwiperPatternTestNg::CalcVerticalScrollStartPosByBlur(float blur, float swiperWidth, bool exit)
{
    if (exit) {
        return CalcVerticalScrollStartPosByExitBlur(blur, swiperWidth);
    } else {
        return CalcVerticalScrollStartPosByEntryBlur(blur, swiperWidth);
    }
}

float ArcSwiperPatternTestNg::CalcVerticalScrollStartPosByExitBlur(float blur, float swiperWidth)
{
    float percent = blur / VERTICAL_EXIT_BLUR_REDUCTION_FACTOR;
    return percent * swiperWidth;
}

float ArcSwiperPatternTestNg::CalcVerticalScrollStartPosByEntryBlur(float blur, float swiperWidth)
{
    float percent = (blur + VERTICAL_ENTRY_BLUR_REDUCTION_FACTOR * VERTICAL_ENTRY_OFFSET_PART) /
                        VERTICAL_ENTRY_BLUR_REDUCTION_FACTOR -
                    VERTICAL_ENTRY_BLUR_INITIAL_VALUE / VERTICAL_ENTRY_BLUR_REDUCTION_FACTOR;
    return swiperWidth - percent * swiperWidth;
}

float ArcSwiperPatternTestNg::CalcVerticalScrollBlur(float swiperWidth, float startPos, bool exit)
{
    float value = 0.0f;
    float percent = CalcPercent(swiperWidth, startPos, exit);
    if (exit) {
        value = CalcVerticalScrollExitBlur(percent);
    } else {
        value = CalcVerticalScrollEntryBlur(percent);
    }
    return value;
}

float ArcSwiperPatternTestNg::CalcVerticalScrollExitBlur(float percent)
{
    float value = percent * VERTICAL_EXIT_BLUR_REDUCTION_FACTOR;
    if (value > VERTICAL_EXIT_BLUR_MAX_VALUE) {
        value = VERTICAL_EXIT_BLUR_MAX_VALUE;
    }
    return value;
}

float ArcSwiperPatternTestNg::CalcVerticalScrollEntryBlur(float percent)
{
    float value = 0.0f;
    if (percent >= VERTICAL_ENTRY_OFFSET_PART) {
        value = VERTICAL_ENTRY_BLUR_INITIAL_VALUE -
                VERTICAL_ENTRY_BLUR_REDUCTION_FACTOR * (percent - VERTICAL_ENTRY_OFFSET_PART);
        if (value < 0.0f) {
            value = 0.0f;
        }
    }
    return value;
}

float ArcSwiperPatternTestNg::CalcVerticalScrollStartPosByAlpha(float alpha, float swiperWidth, bool exit)
{
    if (swiperWidth == 0.0f) {
        return 0.0f;
    }
    if (exit) {
        return CalcVerticalScrollStartPosByExitAlpha(alpha, swiperWidth);
    } else {
        return CalcVerticalScrollStartPosByEntryAlpha(alpha, swiperWidth);
    }
}

float ArcSwiperPatternTestNg::CalcVerticalScrollStartPosByExitAlpha(float alpha, float swiperWidth)
{
    if (swiperWidth == 0.0f) {
        return 0.0f;
    }
    float percent = (1.0f - alpha * VERTICAL_EXIT_ALPHA_REDUCTION_FACTOR) / VERTICAL_EXIT_ALPHA_REDUCTION_FACTOR;
    return percent * swiperWidth;
}

float ArcSwiperPatternTestNg::CalcVerticalScrollStartPosByEntryAlpha(float alpha, float swiperWidth)
{
    if (swiperWidth == 0.0f) {
        return 0.0f;
    }
    float percent = alpha / VERTICAL_ENTRY_BLUR_ALPHA_FACTOR + VERTICAL_ENTRY_OFFSET_PART;
    return swiperWidth - percent * swiperWidth;
}

float ArcSwiperPatternTestNg::CalcVerticalScrollAlpha(float swiperWidth, float startPos, bool exit)
{
    float value = 0.0f;
    float percent = CalcPercent(swiperWidth, startPos, exit);
    if (exit) {
        value = CalcVerticalScrollExitAlpha(percent);
    } else {
        value = CalcVerticalScrollEntryAlpha(percent);
    }
    return value;
}

float ArcSwiperPatternTestNg::CalcVerticalScrollExitAlpha(float percent)
{
    float value = 1.0f - percent * VERTICAL_EXIT_ALPHA_REDUCTION_FACTOR;
    if (value < 0.0f) {
        value = 0.0f;
    }
    return value;
}

float ArcSwiperPatternTestNg::CalcVerticalScrollEntryAlpha(float percent)
{
    float value = 0.0f;
    if (percent >= VERTICAL_ENTRY_OFFSET_PART) {
        value = (percent - VERTICAL_ENTRY_OFFSET_PART) * VERTICAL_ENTRY_BLUR_ALPHA_FACTOR;
        if (value > 1.0f) {
            value = 1.0f;
        }
    }
    return value;
}

bool ArcSwiperPatternTestNg::FindItemByIndex(const RefPtr<ArcSwiperPattern>& pattern,
                                             int32_t index,
                                             SwiperItemInfo& item)
{
    auto iter = pattern->itemPosition_.find(index);
    if (iter == pattern->itemPosition_.end()) {
        return false;
    }
    item = iter->second;
    return true;
}

/**
 * @tc.name: IsPreItem001
 * @tc.desc: Test for method of IsPreItem.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, IsPreItem001, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    model.SetPreviousMargin(Dimension(20), false);
    model.SetNextMargin(Dimension(20), false);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->itemPosition_.size(), 2);
    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->itemPosition_.size(), 2);
    int32_t index = 0;
    float translate = -1.0f;
    EXPECT_TRUE(pattern->IsPreItem(index, translate, false));
    EXPECT_FALSE(pattern->IsPreItem(index, translate, true));
}

/**
 * @tc.name: IsPreItem002
 * @tc.desc: Test for method of IsPreItem.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, IsPreItem002, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    model.SetPreviousMargin(Dimension(20), false);
    model.SetNextMargin(Dimension(20), false);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->itemPosition_.size(), 2);
    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->itemPosition_.size(), 2);
    int32_t index = 0;
    float translate = 1.0f;
    EXPECT_FALSE(pattern->IsPreItem(index, translate, false));
    EXPECT_TRUE(pattern->IsPreItem(index, translate, true));
}

/**
 * @tc.name: IsPreItem003
 * @tc.desc: Test for method of IsPreItem.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, IsPreItem003, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    model.SetPreviousMargin(Dimension(20), false);
    model.SetNextMargin(Dimension(20), false);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->itemPosition_.size(), 2);
    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->itemPosition_.size(), 2);
    int32_t index = 1;
    float translate = -1.0f;
    EXPECT_FALSE(pattern->IsPreItem(index, translate, false));
    EXPECT_TRUE(pattern->IsPreItem(index, translate, true));
}

/**
 * @tc.name: IsPreItem004
 * @tc.desc: Test for method of IsPreItem.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, IsPreItem004, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    model.SetPreviousMargin(Dimension(20), false);
    model.SetNextMargin(Dimension(20), false);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->itemPosition_.size(), 2);
    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->itemPosition_.size(), 2);
    int32_t index = 1;
    float translate = 1.0f;
    EXPECT_TRUE(pattern->IsPreItem(index, translate, false));
    EXPECT_FALSE(pattern->IsPreItem(index, translate, true));
}

/**
 * @tc.name: Animation001
 * @tc.desc: Test for animation of scale.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, Animation001, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    model.SetPreviousMargin(Dimension(20), false);
    model.SetNextMargin(Dimension(20), false);
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_NE(frameNode_, nullptr);
    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);

    // scale
    renderContext->UpdateTransformScale({1.0f, 1.0f});
    ArcSwiperPattern::AnimationParam scaleParam;
    scaleParam.type = ArcSwiperPattern::AnimationType::TYPE_SCALE;
    scaleParam.frameNode = frameNode_;
    scaleParam.scaleValue = EXIT_SCALE_VALUE;

    AnimationOption scaleOption;
    scaleOption.SetDuration(EXIT_SCALE_DURATION);
    scaleOption.SetCurve(Curves::FRICTION);
    scaleParam.option = scaleOption;

    pattern->animationFinishList_.clear();
    auto animation = pattern->Animation(true, scaleParam);
    ASSERT_NE(animation, nullptr);

    auto list = pattern->animationFinishList_;
    EXPECT_EQ(list.size(), 1);

    auto animationType = list.at(0);
    EXPECT_EQ(animationType, ArcSwiperPattern::AnimationFinishType::EXIT_SCALE);

    animation = pattern->Animation(false, scaleParam);
    ASSERT_NE(animation, nullptr);

    list = pattern->animationFinishList_;
    EXPECT_EQ(list.size(), 2);

    animationType = list.at(1);
    EXPECT_EQ(animationType, ArcSwiperPattern::AnimationFinishType::ENTRY_SCALE);
}

/**
 * @tc.name: Animation002
 * @tc.desc: Test for animation of offset.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, Animation002, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    model.SetPreviousMargin(Dimension(20), false);
    model.SetNextMargin(Dimension(20), false);
    CreateSwiperItems();
    CreateSwiperDone();

    ASSERT_NE(frameNode_, nullptr);
    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);

    // Offset
    ArcSwiperPattern::AnimationParam offsetParam;
    offsetParam.type = ArcSwiperPattern::AnimationType::TYPE_OFFSET;
    offsetParam.frameNode = frameNode_;

    AnimationOption offsetOption;
    offsetOption.SetDuration(EXIT_OFFSET_DURATION);
    offsetOption.SetCurve(Curves::FRICTION);
    offsetParam.option = offsetOption;

    pattern->animationFinishList_.clear();
    auto animation = pattern->Animation(true, offsetParam);
    ASSERT_NE(animation, nullptr);

    auto list = pattern->animationFinishList_;
    EXPECT_EQ(list.size(), 1);

    auto animationType = list.at(0);
    EXPECT_EQ(animationType, ArcSwiperPattern::AnimationFinishType::EXIT_OFFSET);

    animation = pattern->Animation(false, offsetParam);
    ASSERT_NE(animation, nullptr);

    list = pattern->animationFinishList_;
    EXPECT_EQ(list.size(), 2);

    animationType = list.at(1);
    EXPECT_EQ(animationType, ArcSwiperPattern::AnimationFinishType::ENTRY_OFFSET);
}

/**
 * @tc.name: Animation003
 * @tc.desc: Test for animation of blur.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, Animation003, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    model.SetPreviousMargin(Dimension(20), false);
    model.SetNextMargin(Dimension(20), false);
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_NE(frameNode_, nullptr);
    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);

    // blur
    BlurOption blurOption;
    renderContext->UpdateBackBlur(Dimension(0, DimensionUnit::PERCENT), blurOption);
    ArcSwiperPattern::AnimationParam blurParam;
    blurParam.type = ArcSwiperPattern::AnimationType::TYPE_BLUR;
    blurParam.frameNode = frameNode_;
    blurParam.blurValue = EXIT_BLUR_VALUE;

    AnimationOption blurAnimationOption;
    blurAnimationOption.SetDelay(EXIT_BLUR_DELAY);
    blurAnimationOption.SetDuration(EXIT_BLUR_DURATION);
    blurAnimationOption.SetCurve(Curves::LINEAR);
    blurParam.option = blurAnimationOption;

    pattern->animationFinishList_.clear();
    auto animation = pattern->Animation(true, blurParam);
    ASSERT_NE(animation, nullptr);

    auto list = pattern->animationFinishList_;
    EXPECT_EQ(list.size(), 1);

    auto animationType = list.at(0);
    EXPECT_EQ(animationType, ArcSwiperPattern::AnimationFinishType::EXIT_BLUR);

    animation = pattern->Animation(false, blurParam);
    ASSERT_NE(animation, nullptr);

    list = pattern->animationFinishList_;
    EXPECT_EQ(list.size(), 2);

    animationType = list.at(1);
    EXPECT_EQ(animationType, ArcSwiperPattern::AnimationFinishType::ENTRY_BLUR);
}

/**
 * @tc.name: Animation004
 * @tc.desc: Test for animation of alpha.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, Animation004, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    model.SetPreviousMargin(Dimension(20), false);
    model.SetNextMargin(Dimension(20), false);
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_NE(frameNode_, nullptr);
    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);

    // alpha
    renderContext->UpdateOpacity(1);
    ArcSwiperPattern::AnimationParam alphaParam;
    alphaParam.type = ArcSwiperPattern::AnimationType::TYPE_ALPHA;
    alphaParam.frameNode = frameNode_;
    alphaParam.opacityValue = 0;

    AnimationOption alphaOption;
    alphaOption.SetDuration(EXIT_ALPHA_DURATION);
    alphaOption.SetCurve(Curves::LINEAR);
    alphaParam.option = alphaOption;

    pattern->animationFinishList_.clear();
    auto animation = pattern->Animation(true, alphaParam);
    ASSERT_NE(animation, nullptr);

    auto list = pattern->animationFinishList_;
    EXPECT_EQ(list.size(), 1);

    auto animationType = list.at(0);
    EXPECT_EQ(animationType, ArcSwiperPattern::AnimationFinishType::EXIT_ALPHA);

    animation = pattern->Animation(false, alphaParam);
    ASSERT_NE(animation, nullptr);

    list = pattern->animationFinishList_;
    EXPECT_EQ(list.size(), 2);

    animationType = list.at(1);
    EXPECT_EQ(animationType, ArcSwiperPattern::AnimationFinishType::ENTRY_ALPHA);
}

/**
 * @tc.name: Animation005
 * @tc.desc: Test for animation of color.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, Animation005, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    model.SetPreviousMargin(Dimension(20), false);
    model.SetNextMargin(Dimension(20), false);
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_NE(frameNode_, nullptr);
    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = CreateFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->GetRenderContext()->UpdateBackgroundColor(Color::BLUE);
    EXPECT_EQ(frameNode->GetRenderContext()->GetBackgroundColorValue(), Color::BLUE);

    //background
    renderContext->OnBackgroundColorUpdate(Color::RED);
    ArcSwiperPattern::AnimationParam colorParam;
    colorParam.type = ArcSwiperPattern::AnimationType::TYPE_COLOR;
    colorParam.frameNode = frameNode;
    colorParam.backColor = Color::BLUE;

    AnimationOption colorOption;
    colorOption.SetDuration(ENTRY_COLOR_DURATION);
    colorOption.SetCurve(Curves::LINEAR);
    colorParam.option = colorOption;

    pattern->animationFinishList_.clear();
    auto animation = pattern->Animation(true, colorParam);
    ASSERT_NE(animation, nullptr);

    auto list = pattern->animationFinishList_;
    EXPECT_EQ(list.size(), 1);

    auto animationType = list.at(0);
    EXPECT_EQ(animationType, ArcSwiperPattern::AnimationFinishType::EXIT_BACKGROUND);

    animation = pattern->Animation(false, colorParam);
    ASSERT_NE(animation, nullptr);

    list = pattern->animationFinishList_;
    EXPECT_EQ(list.size(), 2);

    animationType = list.at(1);
    EXPECT_EQ(animationType, ArcSwiperPattern::AnimationFinishType::ENTRY_BACKGROUND);
}

/**
 * @tc.name: Animation006
 * @tc.desc: Test for animation of error value.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, Animation006, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    model.SetPreviousMargin(Dimension(20), false);
    model.SetNextMargin(Dimension(20), false);
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_NE(frameNode_, nullptr);
    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);

    auto targetIndex = std::make_optional<int>(2);
    pattern->targetIndex_ = targetIndex;
    pattern->currentIndex_ = 2;
    auto iScrollOverCritical = pattern->IsScrollOverCritical();
    EXPECT_FALSE(iScrollOverCritical);
}

/**
 * @tc.name: Animation007
 * @tc.desc: Test for animation of error value.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, Animation007, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    model.SetPreviousMargin(Dimension(20), false);
    model.SetNextMargin(Dimension(20), false);
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_NE(frameNode_, nullptr);
    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);

    // background
    renderContext->OnBackgroundColorUpdate(Color::RED);
    ArcSwiperPattern::AnimationParam colorParam;
    colorParam.type = ArcSwiperPattern::AnimationType::TYPE_COLOR;
    colorParam.frameNode = nullptr;
    colorParam.backColor = Color::BLUE;

    AnimationOption colorOption;
    colorOption.SetDuration(ENTRY_COLOR_DURATION);
    colorOption.SetCurve(Curves::LINEAR);
    colorParam.option = colorOption;

    auto childNode = CreateFrameNode();
    auto parentNode = CreateFrameNode();
    parentNode->renderContext_ = nullptr;
    childNode->MountToParent(parentNode);
    colorParam.frameNode = childNode;
    pattern->animationFinishList_.clear();
    auto animation = pattern->Animation(true, colorParam);
    ASSERT_NE(animation, nullptr);
    auto list = pattern->animationFinishList_;
    EXPECT_EQ(list.size(), 1);

    parentNode = CreateFrameNode();
    childNode->MountToParent(parentNode);
    colorParam.frameNode = childNode;
    pattern->animationFinishList_.clear();
    animation = pattern->Animation(true, colorParam);
    ASSERT_NE(animation, nullptr);
    list = pattern->animationFinishList_;
    EXPECT_EQ(list.size(), 1);
}

/**
 * @tc.name: IsDisableTransitionAnimation
 * @tc.desc: Test for IsDisableTransitionAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, IsDisableTransitionAnimation, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    model.SetPreviousMargin(Dimension(20), false);
    model.SetNextMargin(Dimension(20), false);
    CreateSwiperItems();
    CreateSwiperDone();

    ASSERT_NE(frameNode_, nullptr);
    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->SetDisableTransitionAnimation(true);
    EXPECT_TRUE(pattern->IsDisableTransitionAnimation());

    pattern->SetDisableTransitionAnimation(false);
    EXPECT_FALSE(pattern->IsDisableTransitionAnimation());
}

/**
 * @tc.name: EnableTransitionAnimation
 * @tc.desc: Test for EnableTransitionAnimation when IsDisableTransitionAnimation is true
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, EnableTransitionAnimation001, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    model.SetPreviousMargin(Dimension(20), false);
    model.SetNextMargin(Dimension(20), false);
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_NE(frameNode_, nullptr);
    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_TRUE(pattern->EnableTransitionAnimation());

    pattern->SetDisableTransitionAnimation(true);
    EXPECT_TRUE(pattern->IsDisableTransitionAnimation());
    EXPECT_FALSE(pattern->EnableTransitionAnimation());
}

/**
 * @tc.name: GetCurve001
 * @tc.desc: Test for GetCurve when disableTransitionAnimation is false
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, GetCurve001, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetCurve(Curves::SMOOTH);
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetDisableTransitionAnimation(false);
    EXPECT_EQ(pattern->GetCurve(), Curves::FRICTION);
}

/**
 * @tc.name: GetCurve002
 * @tc.desc: Test for GetCurve when disableTransitionAnimation is false
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, GetCurve002, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetDisableTransitionAnimation(false);
    EXPECT_EQ(pattern->GetCurve(), Curves::FRICTION);
}

/**
 * @tc.name: GetCurve003
 * @tc.desc: Test for GetCurve when disableTransitionAnimation is true
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, GetCurve003, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetDisableTransitionAnimation(true);
    EXPECT_EQ(pattern->GetCurve(), nullptr);
}

/**
 * @tc.name: GetCurve004
 * @tc.desc: Test for GetCurve when disableTransitionAnimation is true
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, GetCurve004, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetCurve(Curves::SMOOTH);
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetDisableTransitionAnimation(true);
    EXPECT_EQ(pattern->GetCurve(), Curves::SMOOTH);
}

/**
 * @tc.name: GetDuraion001
 * @tc.desc: Test for GetDuraion when disableTransitionAnimation is false and axis is horizontal
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, GetDuraion001, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetDisableTransitionAnimation(false);
    EXPECT_EQ(pattern->GetDuration(), HORIZONTAL_ANIMAION_DEFAULT_DURATION);
}

/**
 * @tc.name: GetDuraion002
 * @tc.desc: Test for GetDuraion when disableTransitionAnimation is false and axis is vertical
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, GetDuraion002, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetDisableTransitionAnimation(false);
    EXPECT_EQ(pattern->GetDuration(), VERTICAL_ANIMAION_DEFAULT_DURATION);
}

/**
 * @tc.name: GetDuraion003
 * @tc.desc: Test for GetDuraion when disableTransitionAnimation is false and set duration
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, GetDuraion003, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDuration(1000);
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetDisableTransitionAnimation(false);
    EXPECT_EQ(pattern->GetDuration(), 1000);
}

/**
 * @tc.name: GetDuraion004
 * @tc.desc: Test for GetDuraion when disableTransitionAnimation is true and axis is horizontal
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, GetDuraion004, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetDisableTransitionAnimation(true);
    EXPECT_EQ(pattern->GetDuration(), NO_ANIMAION_DEFAULT_DURATION);
}

/**
 * @tc.name: GetDuraion005
 * @tc.desc: Test for GetDuraion when disableTransitionAnimation is true and axis is vertical
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, GetDuraion005, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetDisableTransitionAnimation(true);
    EXPECT_EQ(pattern->GetDuration(), NO_ANIMAION_DEFAULT_DURATION);
}

/**
 * @tc.name: ClacTime001
 * @tc.desc: Test for ClacTime when disableTransitionAnimation is false and axis is vertical
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, ClacTime001, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    model.SetDuration(300);
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetDisableTransitionAnimation(false);
    auto time = pattern->CalcTime(660);
    EXPECT_EQ(time, 600);
}

/**
 * @tc.name: ClacTime002
 * @tc.desc: Test for ClacTime when disableTransitionAnimation is false and axis is horizontal
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, ClacTime002, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetDisableTransitionAnimation(false);
    auto time = pattern->CalcTime(800);
    EXPECT_EQ(time, 800);
}

/**
 * @tc.name: PlayScrollAnimation
 * @tc.desc: Test for PlayScrollAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, PlayScrollAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node
     */
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    CreateSwiperItems();
    CreateSwiperDone();

    ASSERT_NE(frameNode_, nullptr);

    /**
     * @tc.steps: step2. get pattern
     */
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->contentMainSize_ = SWIPER_WIDTH;
    /**
     * @tc.steps: step3. SetDisableTransitionAnimation
     */
    pattern->SetDisableTransitionAnimation(true);
    EXPECT_TRUE(pattern->IsDisableTransitionAnimation());

    pattern->itemPosition_ = CreateSwiperItemPostion();
    EXPECT_EQ(pattern->itemPosition_.size(), 2);

    pattern->SetDisableTransitionAnimation(false);
    EXPECT_FALSE(pattern->IsDisableTransitionAnimation());
    /**
     * @tc.steps: step4. test PlayScrollAnimation when currentDelta is 0.0f
     */
    float currentDelta = 0.0f;
    float currentIndexOffset = 50.0f;
    pattern->PlayScrollAnimation(currentDelta, currentIndexOffset);
    EXPECT_EQ(pattern->canChangeDirectionFlag_, 0);
    /**
     * @tc.steps: step5. test PlayScrollAnimation when currentDelta is 0.0f
     */
    pattern->isDragging_ = true;
    currentDelta = 0.0f;
    pattern->PlayScrollAnimation(currentDelta, currentIndexOffset);
    EXPECT_EQ(pattern->canChangeDirectionFlag_, 0);
    /**
     * @tc.steps: step6. test PlayScrollAnimation when currentIndexOffset is 0.0f
     */
    currentDelta = 50.0f;
    currentIndexOffset = 0.0f;
    pattern->PlayScrollAnimation(currentDelta, currentIndexOffset);
    EXPECT_EQ(pattern->canChangeDirectionFlag_, 1);
    /**
     * @tc.steps: step7. test PlayScrollAnimation when currentIndexOffset is 0.0f
     */
    pattern->isDragging_ = true;
    currentIndexOffset = 0.0f;
    pattern->PlayScrollAnimation(currentDelta, currentIndexOffset);
    EXPECT_EQ(pattern->canChangeDirectionFlag_, 1);
    /**
     * @tc.steps: step8. test PlayScrollAnimation when currentDelta and currentIndexOffset is more than 0 but can't find
     * next item
     */
    pattern->currentIndex_ = 3;
    pattern->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_RIGHT;
    currentDelta = 50.0f;
    currentIndexOffset = 50.0f;
    pattern->PlayScrollAnimation(currentDelta, currentIndexOffset);
    EXPECT_EQ(pattern->horizontalExitNodeBlur_, 0);
    /**
     * @tc.steps: step7. change currentIndex_ to find next item
     */
    pattern->currentIndex_ = 0;
    pattern->PlayScrollAnimation(currentDelta, currentIndexOffset);
    EXPECT_EQ(pattern->horizontalExitNodeBlur_, 0);

    pattern->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    pattern->currentIndex_ = 1;
    pattern->PlayScrollAnimation(currentDelta, currentIndexOffset);
    EXPECT_EQ(pattern->horizontalExitNodeBlur_, 0);
}

/**
 * @tc.name: PlayScrollAnimation002
 * @tc.desc: Test for PlayScrollAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, PlayScrollAnimation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node
     */
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();

    ASSERT_NE(frameNode_, nullptr);

    /**
     * @tc.steps: step2. get pattern
     */
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->contentMainSize_ = 80;

    /**
     * @tc.steps: step3. test for isDragging_ is false
     */
    float currentDelta = 0.0f;
    float currentIndexOffset = 0.0f;
    pattern->canChangeDirectionFlag_ = true;
    pattern->PlayScrollAnimation(currentDelta, currentIndexOffset);
    EXPECT_FALSE(pattern->canChangeDirectionFlag_);
    
    /**
     * @tc.steps: step4. test for isDragging_ is true but itemPositon size is 1
     */
    pattern->isDragging_ = true;
    SwiperLayoutAlgorithm::PositionMap itemPosition;
    auto node1 = CreateFrameNode();
    auto item1 = CreateSwiperItemInfo(0, 20, node1);
    pattern->itemPosition_.clear();
    pattern->itemPosition_.insert(std::make_pair(0, item1));
    EXPECT_EQ(pattern->itemPosition_.size(), 1);
    pattern->PlayScrollAnimation(-10.0f, -10.0f);
    EXPECT_FALSE(pattern->canChangeDirectionFlag_);
}

/**
 * @tc.name: InitialFrameNodePropertyAnimation001
 * @tc.desc: Test for InitialFrameNodePropertyAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, InitialFrameNodePropertyAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node
     */
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();

    /**
     * @tc.steps: step2. get pattern
     */
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. test for InitialFrameNodePropertyAnimation when frameNode is nullptr
     */
    OffsetF offset(40.0f, 50.0f);
    RefPtr<FrameNode> frameNode = nullptr;
    pattern->InitialFrameNodePropertyAnimation(offset, frameNode);

    /**
     * @tc.steps: step3. test for InitialFrameNodePropertyAnimation when frameNode is not nullptr
     */
    frameNode = CreateFrameNode();
    pattern->InitialFrameNodePropertyAnimation(offset, frameNode);
    EXPECT_EQ(frameNode->isTransformNotChanged_, false);
}

/**
 * @tc.name: InitialFrameNodePropertyAnimation002
 * @tc.desc: Test for InitialFrameNodePropertyAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, InitialFrameNodePropertyAnimation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node
     */
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();

    /**
     * @tc.steps: step2. get pattern
     */
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. test for InitialFrameNodePropertyAnimation when frameNode is nullptr
     */
    OffsetF offset;
    RefPtr<FrameNode> frameNode = nullptr;
    pattern->InitialFrameNodePropertyAnimation(offset, frameNode);

    /**
     * @tc.steps: step3. test for InitialFrameNodePropertyAnimation when frameNode is not nullptr
     */
    frameNode = CreateFrameNode();

    pattern->InitialFrameNodePropertyAnimation(offset, frameNode);
    EXPECT_EQ(frameNode->isTransformNotChanged_, false);
    ArcSwiperPattern::AnimationParam scaleParam = CreateScaleParam(1.0, 40, frameNode);

    auto animation = pattern->Animation(true, scaleParam);
    pattern->animationVector_.push_back(animation);
    pattern->InitialFrameNodePropertyAnimation(offset, frameNode);
    EXPECT_EQ(frameNode->isTransformNotChanged_, false);
}

/**
 * @tc.name: ResetAnimationParam001
 * @tc.desc: Test for ResetAnimationParam
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, ResetAnimationParam001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node
     */
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    CreateSwiperItems();
    CreateSwiperDone();

    /**
     * @tc.steps: step2. get pattern
     */
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. axis_ is HORIZONTAL
     */
    pattern->horizontalExitNodeScale_ = 0.5f;
    pattern->axis_ = Axis::HORIZONTAL;
    pattern->ResetAnimationParam();
    EXPECT_EQ(pattern->horizontalExitNodeScale_, 1.0f);

    /**
     * @tc.steps: step4. axis_ is VERTICAL but can't find currentIndex_
     */
    pattern->currentIndex_ = 3;
    pattern->horizontalExitNodeScale_ = 0.5f;
    pattern->axis_ = Axis::VERTICAL;
    pattern->ResetAnimationParam();
    EXPECT_EQ(pattern->horizontalExitNodeScale_, 1.0f);

    /**
     * @tc.steps: step5. axis_ is VERTICAL, find currentIndex_ but no frameNode
     */
    pattern->axis_ = Axis::VERTICAL;
    pattern->horizontalExitNodeScale_ = 0.5f;
    RefPtr<FrameNode> frameNode = nullptr;
    SwiperItemInfo item = CreateSwiperItemInfo(0, 20, frameNode);
    pattern->itemPosition_.clear();
    pattern->itemPosition_.insert(std::make_pair(0, item));
    pattern->currentIndex_ = 0;
    pattern->ResetAnimationParam();
    EXPECT_EQ(pattern->horizontalExitNodeScale_, 1.0f);

    /**
     * @tc.steps: step6. axis_ is VERTICAL, find currentIndex_ and frameNode
     */
    pattern->axis_ = Axis::VERTICAL;
    pattern->horizontalExitNodeScale_ = 0.5f;
    auto item1 = CreateSwiperItemInfo(0, 20, CreateFrameNode());
    pattern->itemPosition_.insert(std::make_pair(1, item1));
    EXPECT_EQ(pattern->itemPosition_.size(), 2);
    pattern->currentIndex_ = 0;
    pattern->ResetAnimationParam();
    EXPECT_EQ(pattern->horizontalExitNodeScale_, 1.0f);

    pattern->axis_ = Axis::VERTICAL;
    pattern->horizontalExitNodeScale_ = 0.5f;
    auto parentNode = CreateFrameNode();
    parentNode->GetRenderContext()->UpdateBackgroundColor(Color::BLUE);
    EXPECT_EQ(parentNode->GetRenderContext()->GetBackgroundColorValue(), Color::BLUE);
    auto childNode = CreateFrameNode();
    childNode->MountToParent(parentNode);
    auto item2 = CreateSwiperItemInfo(21, 40, childNode);

    pattern->itemPosition_.insert(std::make_pair(2, item2));
    EXPECT_EQ(pattern->itemPosition_.size(), 3);
    pattern->currentIndex_ = 2;
    pattern->ResetAnimationParam();
    EXPECT_EQ(pattern->horizontalExitNodeScale_, 1.0f);
    EXPECT_EQ(parentNode->GetRenderContext()->GetBackgroundColorValue(), Color::BLUE);
}

/**
 * @tc.name: ResetAnimationParam002
 * @tc.desc: Test for ResetAnimationParam
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, ResetAnimationParam002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node
     */
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();

    /**
     * @tc.steps: step2. get pattern
     */
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. axis_ is VERTICAL, find currentIndex_ and frameNode but parentNode has no background
     */
    pattern->horizontalExitNodeScale_ = 0.5f;
    auto parentNode = CreateFrameNode();
    auto childNode = CreateFrameNode();
    childNode->MountToParent(parentNode);
    auto item2 = CreateSwiperItemInfo(21, 40, childNode);
    pattern->itemPosition_.clear();
    pattern->itemPosition_.insert(std::make_pair(0, item2));
    EXPECT_EQ(pattern->itemPosition_.size(), 1);
    pattern->currentIndex_ = 0;
    pattern->ResetAnimationParam();

    /**
     * @tc.steps: step3. axis_ is VERTICAL, find currentIndex_ and frameNode and parentNode has background
     */
    parentNode->GetRenderContext()->UpdateBackgroundColor(Color::BLUE);
    EXPECT_EQ(parentNode->GetRenderContext()->GetBackgroundColorValue(), Color::BLUE);
    pattern->ResetAnimationParam();
    EXPECT_EQ(pattern->horizontalExitNodeScale_, 1.0f);
    auto backPtr = pattern->preNodeBackgroundColor_;
    ASSERT_NE(backPtr, nullptr);
    EXPECT_EQ(*backPtr, Color::BLUE);

    childNode->GetRenderContext()->UpdateBackgroundColor(Color::RED);
    pattern->ResetAnimationParam();
    backPtr = pattern->preNodeBackgroundColor_;
    ASSERT_NE(backPtr, nullptr);
    EXPECT_EQ(*backPtr, Color::RED);

    parentNode->renderContext_ = nullptr;
    pattern->ResetAnimationParam();
    backPtr = pattern->preNodeBackgroundColor_;
    ASSERT_NE(backPtr, nullptr);
}

/**
 * @tc.name: PlayHorizontalScrollAnimation001
 * @tc.desc: Test for PlayHorizontalScrollAnimation001
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, PlayHorizontalScrollAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node
     */
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    CreateSwiperItems();
    CreateSwiperDone();

    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->contentMainSize_ = SWIPER_WIDTH;
    /**
     * @tc.steps: step2. frameNode is nullptr
     */
    pattern->PlayHorizontalScrollExitAnimation(0, 0, nullptr);
    EXPECT_EQ(pattern->horizontalExitNodeScale_, 0);

    pattern->PlayHorizontalScrollEntryAnimation(0, 0, nullptr);
    EXPECT_EQ(pattern->horizontalEntryNodeScale_, 0);
    /**
     * @tc.steps: step3. context is 0
     */
    auto frameNode = CreateFrameNode();
    frameNode->renderContext_ = nullptr;
    pattern->PlayHorizontalScrollExitAnimation(0, 0, frameNode);
    EXPECT_EQ(pattern->horizontalExitNodeScale_, 0);

    pattern->PlayHorizontalScrollEntryAnimation(0, 0, frameNode);
    EXPECT_EQ(pattern->horizontalEntryNodeScale_, 0);

    /**
     * @tc.steps: step4. swiperWidth is 0
     */
    frameNode = CreateFrameNode();
    pattern->PlayHorizontalScrollExitAnimation(0, 0, frameNode);
    EXPECT_EQ(pattern->horizontalExitNodeScale_, 0);

    pattern->PlayHorizontalScrollEntryAnimation(0, 0, frameNode);
    EXPECT_EQ(pattern->horizontalEntryNodeScale_, 0);

    /**
     * @tc.steps: step5. swiperWidth is not 0, but exitNodePercent is 0
     */
    frameNode = CreateFrameNode();
    pattern->PlayHorizontalScrollExitAnimation(100, 0, frameNode);
    EXPECT_EQ(pattern->horizontalExitNodeScale_, 1);

    pattern->PlayHorizontalScrollEntryAnimation(100, 100, frameNode);
    EXPECT_EQ(pattern->horizontalEntryNodeScale_, HORIZONTAL_ENTRY_SCALE_INITIAL_VALUE);
}

/**
 * @tc.name: PlayHorizontalScrollAnimation002
 * @tc.desc: Test for PlayHorizontalScrollAnimation002
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, PlayHorizontalScrollAnimation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node
     */
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    CreateSwiperItems();
    CreateSwiperDone();

    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->contentMainSize_ = SWIPER_WIDTH;

    /**
     * @tc.steps: step1. swiperWidth is not 0, and exitNodePercent is more than 0 for PlayHorizontalScrollExitAnimation
     */
    float swiperWidth = 100.0f;
    float startPos = 50.0f;
    float exit = true;
    auto frameNode = CreateFrameNode();
    pattern->PlayHorizontalScrollExitAnimation(swiperWidth, startPos, frameNode);
    EXPECT_EQ(pattern->horizontalExitNodeScale_, CalcHorizontalScrollScale(swiperWidth, startPos, exit));
    EXPECT_EQ(pattern->horizontalExitNodeOpacity_, CalcHorizontalScrollAlpha(swiperWidth, startPos, exit));
    EXPECT_EQ(pattern->horizontalExitNodeBlur_, CalcHorizontalScrollBlur(swiperWidth, startPos, exit));

    /**
     * @tc.steps: step2. swiperWidth is not 0, and test critical value for PlayHorizontalScrollExitAnimation
     */
    startPos = CalcHorizontalScrollStartPosByScale(HORIZONTAL_EXIT_SCALE_FINAL_VALUE - 0.1f, swiperWidth, exit);
    pattern->PlayHorizontalScrollExitAnimation(swiperWidth, startPos, frameNode);
    EXPECT_EQ(pattern->horizontalExitNodeScale_, HORIZONTAL_EXIT_SCALE_FINAL_VALUE);

    startPos = CalcHorizontalScrollStartPosByBlur(HORIZONTAL_BLUR_MAX_VALUE + 0.1f, swiperWidth, exit);
    pattern->PlayHorizontalScrollExitAnimation(swiperWidth, startPos, frameNode);
    EXPECT_EQ(pattern->horizontalExitNodeBlur_, HORIZONTAL_BLUR_MAX_VALUE);

    startPos = CalcHorizontalScrollStartPosByAlpha(-0.1f, swiperWidth, exit);
    pattern->PlayHorizontalScrollExitAnimation(swiperWidth, startPos, frameNode);
    EXPECT_EQ(pattern->horizontalExitNodeOpacity_, 0.0f);

    /**
     * @tc.steps: step3. swiperWidth is not 0, and exitNodePercent is more than 0 for PlayHorizontalScrollEntryAnimation
     */
    startPos = 50.0f;
    exit = false;
    pattern->PlayHorizontalScrollEntryAnimation(swiperWidth, startPos, frameNode);
    EXPECT_EQ(pattern->horizontalEntryNodeScale_, CalcHorizontalScrollScale(swiperWidth, startPos, exit));
    EXPECT_EQ(pattern->horizontalEntryNodeOpacity_, CalcHorizontalScrollAlpha(swiperWidth, startPos, exit));
    EXPECT_EQ(pattern->horizontalEntryNodeBlur_, CalcHorizontalScrollBlur(swiperWidth, startPos, exit));

    startPos = CalcHorizontalScrollStartPosByScale(1.0f, swiperWidth, exit);
    pattern->PlayHorizontalScrollEntryAnimation(swiperWidth, startPos, frameNode);
    EXPECT_EQ(pattern->horizontalEntryNodeScale_, 1.0f);

    startPos = CalcHorizontalScrollStartPosByBlur(-0.1f, swiperWidth, exit);
    pattern->PlayHorizontalScrollEntryAnimation(swiperWidth, startPos, frameNode);
    EXPECT_EQ(pattern->horizontalEntryNodeBlur_, 0.0f);

    startPos = CalcHorizontalScrollStartPosByAlpha(1.0f + 0.1f, swiperWidth, exit);
    pattern->PlayHorizontalScrollEntryAnimation(swiperWidth, startPos, frameNode);
    EXPECT_EQ(pattern->horizontalEntryNodeOpacity_, 1.0f);
}

/**
 * @tc.name: PlayVerticalScrollAnimation001
 * @tc.desc: Test for PlayVerticalScrollAnimation error value
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, PlayVerticalScrollAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node
     */
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();

    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->contentMainSize_ = SWIPER_WIDTH;
    /**
     * @tc.steps: step2. frameNode is nullptr
     */
    pattern->PlayVerticalScrollExitAnimation(0, 0, nullptr);
    EXPECT_EQ(pattern->verticalExitNodeScale_, 0);

    pattern->PlayVerticalScrollEntryAnimation(0, 0, nullptr);
    EXPECT_EQ(pattern->verticalEntryNodeScale_, 0);
    /**
     * @tc.steps: step3. context is 0
     */
    auto frameNode = CreateFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->renderContext_ = nullptr;
    pattern->PlayVerticalScrollExitAnimation(0, 0, frameNode);
    EXPECT_EQ(pattern->verticalExitNodeScale_, 0);

    pattern->PlayVerticalScrollEntryAnimation(0, 0, frameNode);
    EXPECT_EQ(pattern->verticalEntryNodeScale_, 0);

    /**
     * @tc.steps: step4. swiperWidth is 0
     */
    frameNode = CreateFrameNode();
    pattern->PlayVerticalScrollExitAnimation(0, 0, frameNode);
    EXPECT_EQ(pattern->verticalExitNodeScale_, 0);

    pattern->PlayVerticalScrollEntryAnimation(0, 0, frameNode);
    EXPECT_EQ(pattern->verticalEntryNodeScale_, 0);

    /**
     * @tc.steps: step5. swiperWidth is not 0, but exitNodePercent is 0
     */
    pattern->PlayVerticalScrollExitAnimation(100, 0, frameNode);
    EXPECT_EQ(pattern->verticalExitNodeScale_, 1.0f);
    pattern->PlayVerticalScrollEntryAnimation(100, 100, frameNode);
    EXPECT_EQ(pattern->verticalEntryNodeScale_, 0.0f);
}

/**
 * @tc.name: PlayVerticalScrollAnimation002
 * @tc.desc: Test for PlayVerticalScrollExitAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, PlayVerticalScrollAnimation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node
     */
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();

    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->contentMainSize_ = SWIPER_WIDTH;
    auto frameNode = CreateFrameNode();
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. swiperWidth is not 0, and exitNodePercent is more than 0
     */
    float swiperWidth = 100.0f;
    float startPos = 50.0f;
    float exit = true;
    pattern->PlayVerticalScrollExitAnimation(swiperWidth, startPos, frameNode);
    EXPECT_EQ(pattern->verticalExitNodeScale_, CalcVerticalScrollScale(swiperWidth, startPos, exit));
    EXPECT_EQ(pattern->verticalExitNodeOpacity_, CalcVerticalScrollAlpha(swiperWidth, startPos, exit));
    EXPECT_EQ(pattern->verticalExitNodeBlur_, CalcVerticalScrollBlur(swiperWidth, startPos, exit));

    /**
     * @tc.steps: step3. swiperWidth is not 0, and test critical value
     */
    startPos = CalcVerticalScrollStartPosByScale(VERTICAL_EXIT_SCALE_MIN_VALUE - 0.1f, swiperWidth, exit);
    pattern->PlayHorizontalScrollExitAnimation(swiperWidth, startPos, frameNode);
    EXPECT_EQ(pattern->verticalExitNodeScale_, VERTICAL_EXIT_SCALE_MIN_VALUE);

    startPos = CalcVerticalScrollStartPosByBlur(VERTICAL_EXIT_BLUR_MAX_VALUE + 0.1f, swiperWidth, exit);
    pattern->PlayVerticalScrollExitAnimation(swiperWidth, startPos, frameNode);
    EXPECT_EQ(pattern->verticalExitNodeBlur_, VERTICAL_EXIT_BLUR_MAX_VALUE);

    startPos = CalcVerticalScrollStartPosByAlpha(-0.1f, swiperWidth, exit);
    pattern->PlayVerticalScrollExitAnimation(swiperWidth, startPos, frameNode);
    EXPECT_EQ(pattern->verticalExitNodeOpacity_, 0.0f);
}

/**
 * @tc.name: PlayVerticalScrollAnimation003
 * @tc.desc: Test for PlayVerticalScrollEntryAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, PlayVerticalScrollAnimation003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node
     */
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();

    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->contentMainSize_ = SWIPER_WIDTH;
    auto frameNode = CreateFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. swiperWidth is not 0, and exitNodePercent is more than 0
     */
    float swiperWidth = 100.0f;
    float startPos = 50.0f;
    bool exit = false;
    auto childNode = CreateFrameNode();
    auto parentNode = CreateFrameNode();
    childNode->MountToParent(parentNode);
    pattern->PlayVerticalScrollEntryAnimation(swiperWidth, startPos, childNode);
    EXPECT_EQ(pattern->verticalEntryNodeScale_, CalcVerticalScrollScale(swiperWidth, startPos, exit));
    EXPECT_EQ(pattern->verticalEntryNodeOpacity_, CalcVerticalScrollAlpha(swiperWidth, startPos, exit));
    EXPECT_EQ(pattern->verticalEntryNodeBlur_, CalcVerticalScrollBlur(swiperWidth, startPos, exit));

    startPos = CalcStartByPercent(VERTICAL_ENTRY_OFFSET_PART - 0.1f, swiperWidth, exit);
    pattern->PlayVerticalScrollEntryAnimation(swiperWidth, startPos, frameNode);
    EXPECT_EQ(pattern->verticalEntryNodeScale_, 0.0f);
    EXPECT_EQ(pattern->verticalEntryNodeBlur_, 0.0f);
    EXPECT_EQ(pattern->verticalEntryNodeOpacity_, 0.0f);

    startPos = CalcStartByPercent(0.6f, swiperWidth, exit);
    pattern->PlayVerticalScrollEntryAnimation(swiperWidth, startPos, frameNode);
    auto scale1 = pattern->verticalEntryNodeScale_;
    auto scale2 = CalcVerticalScrollScale(swiperWidth, startPos, exit);
    EXPECT_EQ(scale1, scale2);

    auto blur1 = pattern->verticalEntryNodeBlur_;
    auto blur2 = CalcVerticalScrollBlur(swiperWidth, startPos, exit);
    EXPECT_EQ(blur1, blur2);

    auto alpha1 = pattern->verticalEntryNodeOpacity_;
    auto alpha2 = CalcVerticalScrollAlpha(swiperWidth, startPos, exit);
    EXPECT_EQ(alpha1, alpha2);
}

/**
 * @tc.name: PlayVerticalScrollEntryBackgroundAnimation
 * @tc.desc: Test for PlayVerticalScrollEntryBackgroundAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, PlayVerticalScrollEntryBackgroundAnimation, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();

    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->contentMainSize_ = 60;
    std::shared_ptr<Color> beginColor = std::make_shared<Color>(Color::RED);
    std::shared_ptr<Color> endColor = std::make_shared<Color>(Color::BLUE);
    pattern->preNodeBackgroundColor_ = nullptr;
    pattern->entryNodeBackgroundColor_ = nullptr;
    pattern->parentNodeBackgroundColor_ = beginColor;

    auto childNode = CreateFrameNode();
    pattern->PlayVerticalScrollEntryBackgroundAnimation(0.6f, childNode);

    auto parentNode = CreateFrameNode();
    childNode->MountToParent(parentNode);
    pattern->PlayVerticalScrollEntryBackgroundAnimation(0.6f, childNode);

    pattern->preNodeBackgroundColor_ = beginColor;
    childNode->GetRenderContext()->UpdateBackgroundColor(Color::BLUE);
    EXPECT_EQ(childNode->GetRenderContext()->GetBackgroundColorValue(), Color::BLUE);
    pattern->PlayVerticalScrollEntryBackgroundAnimation(0.6f, childNode);
}

/**
 * @tc.name: PlayScrollBackgroundAnimation001
 * @tc.desc: Test for PlayScrollBackgroundAnimation001
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, PlayScrollBackgroundAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and get pattern
     */
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();

    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->contentMainSize_ = 60;

    /**
     * @tc.steps: step2. test for params are nullptr
     */
    std::shared_ptr<Color> color = nullptr;
    std::shared_ptr<Color> parentColor = nullptr;
    RefPtr<RenderContext> parentRenderContext;
    bool exitNodeNeedTransparent = true;
    pattern->PlayScrollBackgroundAnimation(color, parentColor, parentRenderContext, exitNodeNeedTransparent);
    exitNodeNeedTransparent = false;
    pattern->PlayScrollBackgroundAnimation(color, parentColor, parentRenderContext, exitNodeNeedTransparent);

    /**
     * @tc.steps: step3. test for has parentRenderContext
     */
    exitNodeNeedTransparent = true;
    auto childNode = CreateFrameNode();
    auto parentNode = CreateFrameNode();
    childNode->MountToParent(parentNode);
    auto parentFrameNode = childNode->GetParentFrameNode();
    ASSERT_NE(parentFrameNode, nullptr);
    EXPECT_EQ(parentNode, parentFrameNode);
    parentRenderContext = parentFrameNode->GetRenderContext();
    ASSERT_NE(parentRenderContext, nullptr);
    pattern->PlayScrollBackgroundAnimation(color, parentColor, parentRenderContext, exitNodeNeedTransparent);
    exitNodeNeedTransparent = false;
    pattern->PlayScrollBackgroundAnimation(color, parentColor, parentRenderContext, exitNodeNeedTransparent);

    /**
     * @tc.steps: step4. test for has exitFrameNode_ but its renderContext_ is nullptr
     */
    exitNodeNeedTransparent = true;
    auto exitNode = CreateFrameNode();
    exitNode->renderContext_ = nullptr;
    pattern->exitFrameNode_ = WeakPtr<FrameNode>(exitNode);
    ASSERT_EQ(exitNode->GetRenderContext(), nullptr);
    pattern->PlayScrollBackgroundAnimation(color, parentColor, parentRenderContext, exitNodeNeedTransparent);
    exitNodeNeedTransparent = false;
    pattern->PlayScrollBackgroundAnimation(color, parentColor, parentRenderContext, exitNodeNeedTransparent);
}

/**
 * @tc.name: PlayScrollBackgroundAnimation002
 * @tc.desc: Test for PlayScrollBackgroundAnimation002
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, PlayScrollBackgroundAnimation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and get pattern
     */
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();

    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->contentMainSize_ = 60;

    auto childNode = CreateFrameNode();
    auto parentNode = CreateFrameNode();
    childNode->MountToParent(parentNode);
    auto parentFrameNode = childNode->GetParentFrameNode();
    ASSERT_NE(parentFrameNode, nullptr);
    EXPECT_EQ(parentNode, parentFrameNode);
    auto parentRenderContext = parentFrameNode->GetRenderContext();
    ASSERT_NE(parentRenderContext, nullptr);

    /**
     * @tc.steps: step2. test for has exitFrameNode_ but its renderContext_ is not nullptr
     */
    bool exitNodeNeedTransparent = true;
    auto exitNode = CreateFrameNode();
    std::shared_ptr<Color> color = nullptr;
    std::shared_ptr<Color> parentColor = nullptr;
    pattern->exitFrameNode_ = WeakPtr<FrameNode>(exitNode);
    ASSERT_NE(exitNode->GetRenderContext(), nullptr);
    pattern->PlayScrollBackgroundAnimation(color, parentColor, parentRenderContext, exitNodeNeedTransparent);
    exitNodeNeedTransparent = false;
    pattern->PlayScrollBackgroundAnimation(color, parentColor, parentRenderContext, exitNodeNeedTransparent);

    /**
     * @tc.steps: step3. test for all params is not nullptr
     */
    exitNodeNeedTransparent = true;
    color = std::make_shared<Color>(Color::RED);
    pattern->PlayScrollBackgroundAnimation(color, parentColor, parentRenderContext, exitNodeNeedTransparent);
    exitNodeNeedTransparent = false;
    pattern->PlayScrollBackgroundAnimation(color, parentColor, parentRenderContext, exitNodeNeedTransparent);

    /**
     * @tc.steps: step4. test for color is TRANSPARENT
     */
    exitNodeNeedTransparent = true;
    color = std::make_shared<Color>(Color::TRANSPARENT);
    parentColor = std::make_shared<Color>(Color::BLUE);
    pattern->PlayScrollBackgroundAnimation(color, parentColor, parentRenderContext, exitNodeNeedTransparent);
    exitNodeNeedTransparent = false;
    pattern->PlayScrollBackgroundAnimation(color, parentColor, parentRenderContext, exitNodeNeedTransparent);
}

/**
 * @tc.name: GetVerticalEntryBackgroundValue
 * @tc.desc: Test for GetVerticalEntryBackgroundValue
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, GetVerticalEntryBackgroundValue, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();

    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->contentMainSize_ = 60;

    bool rollBack = true;
    pattern->preNodeBackgroundColor_ = nullptr;
    pattern->parentNodeBackgroundColor_ = nullptr;
    auto color = pattern->GetVerticalEntryBackgroundValue(rollBack);
    ASSERT_EQ(color, Color::TRANSPARENT);

    auto redColorPtr = std::make_shared<Color>(Color::RED);
    auto blueColorPtr = std::make_shared<Color>(Color::BLUE);
    pattern->preNodeBackgroundColor_ = nullptr;
    pattern->parentNodeBackgroundColor_ = redColorPtr;
    color = pattern->GetVerticalEntryBackgroundValue(rollBack);
    ASSERT_EQ(color, Color::RED);

    pattern->preNodeBackgroundColor_ = blueColorPtr;
    color = pattern->GetVerticalEntryBackgroundValue(rollBack);
    ASSERT_EQ(color, Color::BLUE);

    rollBack = false;
    pattern->parentNodeBackgroundColor_ = redColorPtr;
    pattern->entryNodeBackgroundColor_ = nullptr;
    color = pattern->GetVerticalEntryBackgroundValue(rollBack);
    ASSERT_EQ(color, Color::RED);

    pattern->parentNodeBackgroundColor_ = redColorPtr;
    pattern->entryNodeBackgroundColor_ = blueColorPtr;
    color = pattern->GetVerticalEntryBackgroundValue(rollBack);
    ASSERT_EQ(color, Color::BLUE);
}

/**
 * @tc.name: PlayAnimation001
 * @tc.desc: Test for PlayAnimation of VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, PlayAnimation001, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    model.SetLoop(true);
    CreateSwiperItems();
    CreateSwiperDone();

    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_FALSE(pattern->IsLoop());
    pattern->contentMainSize_ = 60;
    pattern->currentIndex_ = 0;
    OffsetF offset;
    offset.SetY(50);
    auto frameNode = CreateFrameNode();
    pattern->animationVector_.clear();
    pattern->PlayAnimation(offset, 0, frameNode);
    EXPECT_EQ(pattern->animationVector_.size(), 4);
}

/**
 * @tc.name: PlayAnimation002
 * @tc.desc: Test for PlayAnimation of HORIZONTAL
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, PlayAnimation002, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    model.SetLoop(true);
    CreateSwiperItems();
    CreateSwiperDone();

    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_FALSE(pattern->IsLoop());
    pattern->contentMainSize_ = 60;
    pattern->currentIndex_ = 0;
    OffsetF offset;
    offset.SetY(50);
    auto frameNode = CreateFrameNode();
    pattern->animationVector_.clear();
    pattern->PlayAnimation(offset, 0, frameNode);
    EXPECT_EQ(pattern->animationVector_.size(), 4);
}

/**
 * @tc.name: PlayVerticalExitAnimation001
 * @tc.desc: Test for method of PlayVerticalExitAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, PlayVerticalExitAnimation001, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    model.SetPreviousMargin(Dimension(20), false);
    model.SetNextMargin(Dimension(20), false);
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->itemPosition_.size(), 2);
    OffsetF offset(0.0f, 0.0f);
    auto frameNode = CreateFrameNode();
    bool rollBack = true;
    pattern->PlayVerticalExitAnimation(offset, frameNode, rollBack);
    EXPECT_EQ(pattern->animationVector_.size(), 4);
    pattern->animationVector_.clear();
    EXPECT_EQ(pattern->animationVector_.size(), 0);
    pattern->PlayVerticalExitAnimation(offset, nullptr, rollBack);
    EXPECT_EQ(pattern->animationVector_.size(), 0);
}

/**
 * @tc.name: PlayVerticalEntryAnimation
 * @tc.desc: Test for method of PlayVerticalEntryAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, PlayVerticalEntryAnimation, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    model.SetPreviousMargin(Dimension(20), false);
    model.SetNextMargin(Dimension(20), false);
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->itemPosition_.size(), 2);
    OffsetF offset(0.0f, 0.0f);
    auto frameNode = CreateFrameNode();
    bool rollBack = true;
    pattern->PlayVerticalEntryAnimation(offset, frameNode, rollBack);
    EXPECT_EQ(pattern->animationVector_.size(), 5);
    pattern->animationVector_.clear();
    EXPECT_EQ(pattern->animationVector_.size(), 0);
    pattern->PlayVerticalEntryAnimation(offset, nullptr, rollBack);
    EXPECT_EQ(pattern->animationVector_.size(), 0);
}
} // namespace OHOS::Ace::NG
