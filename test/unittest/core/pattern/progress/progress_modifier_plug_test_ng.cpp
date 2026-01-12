/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "progress_test_ng.h"

namespace OHOS::Ace::NG {
namespace {} // namespace

class ProgressModifierPlugTestNg : public ProgressTestNg {
public:
};

/**
 * @tc.name: CapsuleProgressModifier001
 * @tc.desc: Test the gradient color of the capsule progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierPlugTestNg, CapsuleProgressModifier001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ProgressModifier and set ProgressModifier property.
     * @tc.expected: step1. Check the ProgressModifier property value.
     */
    Gradient gradient;
    GradientColor gradientColorEnd;
    GradientColor gradientColorStart;
    gradientColorEnd.SetLinearColor(LinearColor(Color::WHITE));
    gradientColorStart.SetLinearColor(LinearColor(Color::BLACK));
    gradientColorEnd.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColorEnd);
    gradientColorStart.SetDimension(Dimension(1.0));
    gradient.AddColor(gradientColorStart);

    auto pipeline = PipelineBase::GetCurrentContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto progressModifier = AceType::MakeRefPtr<ProgressModifier>(frameNode_);
    progressModifier->SetVisible(true);
    progressModifier->SetProgressType(PROGRESS_TYPE_CAPSULE);
    progressModifier->SetStrokeWidth(PROGRESS_STROKE_WIDTH);
    EXPECT_EQ(progressModifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_CAPSULE));
    EXPECT_EQ(progressModifier->strokeWidth_->Get(), PROGRESS_STROKE_WIDTH);
    LinearColor linearColor;
    progressModifier->SetColor(linearColor);
    EXPECT_EQ(progressModifier->color_->Get(), linearColor);
    progressModifier->SetBackgroundColor(linearColor);
    EXPECT_EQ(progressModifier->bgColor_->Get(), linearColor);
    progressModifier->SetRingProgressColor(gradient);
    progressModifier->SetMaxValue(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier->maxValue_->Get(), PROGRESS_MODIFIER_VALUE);
    float value = 50.0f;
    progressModifier->SetValue(value);
    EXPECT_EQ(progressModifier->value_->Get(), value);
    OffsetF offset(0, 0);
    progressModifier->SetContentOffset(offset);
    EXPECT_EQ(progressModifier->offset_->Get(), offset);

    Testing::MockCanvas canvas;
    DrawingContext context { canvas, CONTEXT_WIDTH, CONTEXT_HEIGHT };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, Restore()).Times(AtLeast(1));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(canvas, ClipPath(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawRect(_)).Times(AtLeast(1));

    /**
     * @tc.steps: step2. Set different properties, call function onDraw.
     * @tc.expected: step2. Set the properties success.
     */
    value = 60.0f;
    progressModifier->SetSweepEffect(true);
    SizeF progressContentSize(200.0, 100.0);
    progressModifier->SetContentSize(progressContentSize);
    progressModifier->SetBorderWidth(2.0);
    progressModifier->isSweeping_ = true;
    progressModifier->sweepingDateBackup_ = 1000.0f;
    progressModifier->SetValue(20.0);
    progressModifier->onDraw(context);
    EXPECT_NE(progressModifier->sweepingDate_, 0.0f);
    auto gradientColors = progressModifier->ringProgressColors_->Get().GetGradient().GetColors();
    EXPECT_EQ(gradientColors.size(), 2);
    EXPECT_EQ(gradientColors[0].GetLinearColor(), LinearColor(Color::WHITE));
    EXPECT_EQ(gradientColors[1].GetLinearColor(), LinearColor(Color::BLACK));
}

/**
 * @tc.name: CapsuleProgressModifier002
 * @tc.desc: Test the gradient color of the capsule progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierPlugTestNg, CapsuleProgressModifier002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ProgressModifier and set ProgressModifier property.
     * @tc.expected: step1. Check the ProgressModifier property value.
     */
    Gradient gradient;
    GradientColor gradientColorEnd;
    GradientColor gradientColorStart;
    gradientColorEnd.SetLinearColor(LinearColor(Color::WHITE));
    gradientColorStart.SetLinearColor(LinearColor(Color::BLACK));
    gradientColorEnd.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColorEnd);
    gradientColorStart.SetDimension(Dimension(1.0));
    gradient.AddColor(gradientColorStart);

    auto pipeline = PipelineBase::GetCurrentContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto progressModifier = AceType::MakeRefPtr<ProgressModifier>(frameNode_);
    progressModifier->SetVisible(true);
    progressModifier->SetProgressType(PROGRESS_TYPE_CAPSULE);
    LinearColor linearColor;
    progressModifier->SetColor(linearColor);
    progressModifier->SetBackgroundColor(linearColor);
    progressModifier->SetRingProgressColor(gradient);
    OffsetF offset(0, 0);
    progressModifier->SetContentOffset(offset);

    Testing::MockCanvas canvas;
    DrawingContext context { canvas, CONTEXT_WIDTH, CONTEXT_HEIGHT };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, Restore()).Times(AtLeast(1));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(canvas, ClipPath(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawRect(_)).Times(AtLeast(1));

    /**
     * @tc.steps: step2. Set different properties, call function onDraw.
     * @tc.expected: step2. Set the properties success.
     */
    SizeF progressContentSize(200.0, 100.0);
    progressModifier->SetContentSize(progressContentSize);
    progressModifier->SetValue(20.0);
    progressModifier->PaintCapsuleWithGradient(context.canvas, progressModifier->offset_->Get(),
        progressModifier->contentSize_->Get(), progressModifier->capsuleBorderRadius_->Get());
    SizeF progressContentSize1(100.0, 200.0);
    progressModifier->SetContentSize(progressContentSize1);
    progressModifier->PaintVerticalCapsuleWithGradient(context.canvas, progressModifier->offset_->Get(),
        progressModifier->contentSize_->Get(), progressModifier->capsuleBorderRadius_->Get());
    auto gradientColors = progressModifier->ringProgressColors_->Get().GetGradient().GetColors();
    EXPECT_EQ(gradientColors.size(), 2);
    EXPECT_EQ(gradientColors[0].GetLinearColor(), LinearColor(Color::WHITE));
    EXPECT_EQ(gradientColors[1].GetLinearColor(), LinearColor(Color::BLACK));
}

/**
 * @tc.name: LinearProgressModifier001
 * @tc.desc: Test the gradient color of the linear progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierPlugTestNg, LinearProgressModifier001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ProgressModifier and set ProgressModifier property.
     * @tc.expected: step1. Check the ProgressModifier property value.
     */
    Gradient gradient;
    GradientColor gradientColorEnd;
    GradientColor gradientColorStart;
    gradientColorEnd.SetLinearColor(LinearColor(Color::WHITE));
    gradientColorStart.SetLinearColor(LinearColor(Color::BLACK));
    gradientColorEnd.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColorEnd);
    gradientColorStart.SetDimension(Dimension(1.0));
    gradient.AddColor(gradientColorStart);

    auto pipeline = PipelineBase::GetCurrentContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto progressModifier = AceType::MakeRefPtr<ProgressModifier>(frameNode_);
    progressModifier->SetVisible(true);
    progressModifier->SetProgressType(PROGRESS_TYPE_LINEAR);
    progressModifier->SetStrokeWidth(PROGRESS_STROKE_WIDTH);
    EXPECT_EQ(progressModifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_LINEAR));
    EXPECT_EQ(progressModifier->strokeWidth_->Get(), PROGRESS_STROKE_WIDTH);
    LinearColor linearColor;
    progressModifier->SetColor(linearColor);
    EXPECT_EQ(progressModifier->color_->Get(), linearColor);
    progressModifier->SetBackgroundColor(linearColor);
    EXPECT_EQ(progressModifier->bgColor_->Get(), linearColor);
    progressModifier->SetRingProgressColor(gradient);
    progressModifier->SetMaxValue(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier->maxValue_->Get(), PROGRESS_MODIFIER_VALUE);
    float value = 50.0f;
    progressModifier->SetValue(value);
    EXPECT_EQ(progressModifier->value_->Get(), value);
    OffsetF offset(0, 0);
    progressModifier->SetContentOffset(offset);
    EXPECT_EQ(progressModifier->offset_->Get(), offset);

    Testing::MockCanvas canvas;
    DrawingContext context { canvas, CONTEXT_WIDTH, CONTEXT_HEIGHT };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, Restore()).Times(AtLeast(1));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(canvas, ClipPath(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawRect(_)).Times(AtLeast(1));

    /**
     * @tc.steps: step2. Set different properties, call function onDraw.
     * @tc.expected: step2. Set the properties success.
     */
    value = 60.0f;
    progressModifier->SetSweepEffect(true);
    SizeF progressContentSize(200.0, 100.0);
    progressModifier->SetContentSize(progressContentSize);
    progressModifier->SetBorderWidth(2.0);
    progressModifier->isSweeping_ = true;
    progressModifier->sweepingDateBackup_ = 1000.0f;
    progressModifier->SetValue(20.0);
    progressModifier->onDraw(context);
    EXPECT_NE(progressModifier->sweepingDate_, 0.0f);
    auto gradientColors = progressModifier->ringProgressColors_->Get().GetGradient().GetColors();
    EXPECT_EQ(gradientColors.size(), 2);
    EXPECT_EQ(gradientColors[0].GetLinearColor(), LinearColor(Color::WHITE));
    EXPECT_EQ(gradientColors[1].GetLinearColor(), LinearColor(Color::BLACK));
}

/**
 * @tc.name: LinearProgressModifier002
 * @tc.desc: Test the gradient color of the linear progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierPlugTestNg, LinearProgressModifier002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ProgressModifier and set ProgressModifier property.
     * @tc.expected: step1. Check the ProgressModifier property value.
     */
    Gradient gradient;
    GradientColor gradientColorEnd;
    GradientColor gradientColorStart;
    gradientColorEnd.SetLinearColor(LinearColor(Color::WHITE));
    gradientColorStart.SetLinearColor(LinearColor(Color::BLACK));
    gradientColorEnd.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColorEnd);
    gradientColorStart.SetDimension(Dimension(1.0));
    gradient.AddColor(gradientColorStart);

    auto pipeline = PipelineBase::GetCurrentContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto progressModifier = AceType::MakeRefPtr<ProgressModifier>(frameNode_);
    progressModifier->SetVisible(true);
    progressModifier->SetProgressType(PROGRESS_TYPE_LINEAR);
    LinearColor linearColor;
    progressModifier->SetColor(linearColor);
    progressModifier->SetBackgroundColor(linearColor);
    progressModifier->SetRingProgressColor(gradient);
    OffsetF offset(0, 0);
    progressModifier->SetContentOffset(offset);

    Testing::MockCanvas canvas;
    DrawingContext context { canvas, CONTEXT_WIDTH, CONTEXT_HEIGHT };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, Restore()).Times(AtLeast(1));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(canvas, ClipPath(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawRect(_)).Times(AtLeast(1));

    /**
     * @tc.steps: step2. Set different properties, call function onDraw.
     * @tc.expected: step2. Set the properties success.
     */
    SizeF progressContentSize(200.0, 100.0);
    progressModifier->SetContentSize(progressContentSize);
    progressModifier->SetValue(20.0);
    progressModifier->PaintLinearWithGradient(
        context.canvas, progressModifier->offset_->Get(), progressModifier->contentSize_->Get());
    auto gradientColors = progressModifier->ringProgressColors_->Get().GetGradient().GetColors();
    EXPECT_EQ(gradientColors.size(), 2);
    EXPECT_EQ(gradientColors[0].GetLinearColor(), LinearColor(Color::WHITE));
    EXPECT_EQ(gradientColors[1].GetLinearColor(), LinearColor(Color::BLACK));
}

/**
 * @tc.name: StopAllLoopAnimation
 * @tc.desc: Test StopAllLoopAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierPlugTestNg, StopAllLoopAnimation, TestSize.Level1)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto progressModifier = AceType::MakeRefPtr<ProgressModifier>(frameNode_);
    progressModifier->StopAllLoopAnimation();
    EXPECT_FALSE(progressModifier->isLoading_);
    EXPECT_FALSE(progressModifier->isSweeping_);
    progressModifier->isLoading_ = true;
    progressModifier->isSweeping_ = true;
    progressModifier->StopAllLoopAnimation();
    EXPECT_FALSE(progressModifier->isLoading_);
    EXPECT_FALSE(progressModifier->isSweeping_);
}
} // namespace OHOS::Ace::NG
