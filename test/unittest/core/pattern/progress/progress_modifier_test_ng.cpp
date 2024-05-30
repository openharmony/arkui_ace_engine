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

#include "progress_test_ng.h"

namespace OHOS::Ace::NG {
namespace {} // namespace

class ProgressModifierTestNg : public ProgressTestNg {
public:
};

/**
 * @tc.name: ProgressModifier001
 * @tc.desc: Test ProgressModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTestNg, ProgressModifier001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ProgressModifier and set ProgressModifier property.
     * @tc.expected: step1. Check the ProgressModifier property value.
     */
    Gradient gradient;
    GradientColor gradientColorEnd;
    GradientColor gradientColorStart;
    gradientColorEnd.SetLinearColor(LinearColor(Color::WHITE));
    gradientColorStart.SetLinearColor(LinearColor(Color::WHITE));
    gradientColorEnd.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColorEnd);
    gradientColorStart.SetDimension(Dimension(1.0));
    gradient.AddColor(gradientColorStart);

    ProgressModifier progressModifier;
    progressModifier.SetStrokeWidth(PROGRESS_STROKE_WIDTH);
    LinearColor linearColor;
    progressModifier.SetColor(linearColor);
    EXPECT_EQ(progressModifier.color_->Get(), linearColor);
    progressModifier.SetBackgroundColor(linearColor);
    EXPECT_EQ(progressModifier.bgColor_->Get(), linearColor);
    progressModifier.SetBorderColor(linearColor);
    EXPECT_EQ(progressModifier.borderColor_->Get(), linearColor);
    progressModifier.SetRingProgressColor(gradient);
    progressModifier.SetPaintShadow(true);
    progressModifier.SetMaxValue(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier.maxValue_->Get(), PROGRESS_MODIFIER_VALUE);
    progressModifier.SetValue(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier.value_->Get(), PROGRESS_MODIFIER_VALUE);
    progressModifier.SetScaleWidth(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier.scaleWidth_->Get(), PROGRESS_MODIFIER_VALUE);
    progressModifier.SetScaleCount(SCALE_COUNT);
    EXPECT_EQ(progressModifier.scaleCount_->Get(), SCALE_COUNT);
    OffsetF offset(0, 0);
    progressModifier.SetContentOffset(offset);
    EXPECT_EQ(progressModifier.offset_->Get(), offset);

    /**
     * @tc.steps: step2. Set different properties, call function onDraw.
     * @tc.expected: step2. Set the properties success.
     */
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, CONTEXT_WIDTH, CONTEXT_HEIGHT };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(canvas, Rotate(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Restore()).Times(AtLeast(1));

    progressModifier.SetProgressType(PROGRESS_TYPE_LINEAR);
    SizeF ContentSize(CONTEXT_WIDTH, CONTEXT_HEIGHT);

    // set ProgressType LINEAR(Width >= Height)
    progressModifier.SetContentSize(ContentSize);
    progressModifier.onDraw(context);
    EXPECT_EQ(progressModifier.progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_LINEAR));
    EXPECT_EQ(progressModifier.contentSize_->Get(), ContentSize);

    // set ProgressType LINEAR(Width < Height)
    SizeF secondContentSize(CONTEXT_WIDTH, CONTEXT_LARGE_HEIGHT);
    progressModifier.SetContentSize(secondContentSize);
    progressModifier.onDraw(context);
    EXPECT_EQ(progressModifier.progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_LINEAR));
    EXPECT_EQ(progressModifier.contentSize_->Get(), secondContentSize);

    // set ProgressType RING
    progressModifier.SetStrokeWidth(PROGRESS_LARGE_STROKE_WIDTH);
    progressModifier.SetProgressType(PROGRESS_TYPE_RING);
    progressModifier.onDraw(context);
    EXPECT_EQ(progressModifier.progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_RING));
    EXPECT_EQ(progressModifier.strokeWidth_->Get(), PROGRESS_LARGE_STROKE_WIDTH);
}

/**
 * @tc.name: ProgressModifier002
 * @tc.desc: Test ProgressModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTestNg, ProgressModifier002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ProgressModifier and set ProgressModifier property.
     * @tc.expected: step1. Check the ProgressModifier property value.
     */
    Gradient gradient;
    GradientColor gradientColorEnd;
    GradientColor gradientColorStart;
    gradientColorEnd.SetLinearColor(LinearColor(Color::WHITE));
    gradientColorStart.SetLinearColor(LinearColor(Color::WHITE));
    gradientColorEnd.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColorEnd);
    gradientColorStart.SetDimension(Dimension(1.0));
    gradient.AddColor(gradientColorStart);

    ProgressModifier progressModifier;
    progressModifier.SetStrokeWidth(PROGRESS_STROKE_WIDTH);
    LinearColor linearColor;
    progressModifier.SetColor(linearColor);
    EXPECT_EQ(progressModifier.color_->Get(), linearColor);
    progressModifier.SetBackgroundColor(linearColor);
    EXPECT_EQ(progressModifier.bgColor_->Get(), linearColor);
    progressModifier.SetBorderColor(linearColor);
    EXPECT_EQ(progressModifier.borderColor_->Get(), linearColor);
    progressModifier.SetRingProgressColor(gradient);
    progressModifier.SetMaxValue(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier.maxValue_->Get(), PROGRESS_MODIFIER_VALUE);
    progressModifier.SetValue(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier.value_->Get(), PROGRESS_MODIFIER_VALUE);
    progressModifier.SetScaleWidth(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier.scaleWidth_->Get(), PROGRESS_MODIFIER_VALUE);
    progressModifier.SetScaleCount(SCALE_COUNT);
    EXPECT_EQ(progressModifier.scaleCount_->Get(), SCALE_COUNT);
    OffsetF offset(0, 0);
    progressModifier.SetContentOffset(offset);
    EXPECT_EQ(progressModifier.offset_->Get(), offset);

    /**
     * @tc.steps: step2. Set different properties, call function onDraw.
     * @tc.expected: step2. Set the properties success.
     */
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, CONTEXT_WIDTH, CONTEXT_HEIGHT };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawArc(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(canvas, Rotate(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Restore()).Times(AtLeast(1));
    // set ProgressType SCALE
    progressModifier.SetProgressType(PROGRESS_TYPE_SCALE);
    progressModifier.onDraw(context);
    EXPECT_EQ(progressModifier.progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_SCALE));

    // set ProgressType SCALE SetScaleWidth 0
    progressModifier.SetScaleWidth(0);
    progressModifier.onDraw(context);
    EXPECT_EQ(progressModifier.scaleWidth_->Get(), 0);

    // set ProgressType MOON
    progressModifier.SetStrokeWidth(PROGRESS_STROKE_WIDTH);
    progressModifier.SetProgressType(PROGRESS_TYPE_MOON);
    progressModifier.onDraw(context);
    EXPECT_EQ(progressModifier.progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_MOON));
    EXPECT_EQ(progressModifier.strokeWidth_->Get(), PROGRESS_STROKE_WIDTH);

    // set ProgressType MOON(angle <=FLOAT_ZERO_FIVE)
    progressModifier.SetMaxValue(PROGRESS_MODIFIER_MAX_VALUE);
    progressModifier.onDraw(context);
    EXPECT_EQ(progressModifier.maxValue_->Get(), PROGRESS_MODIFIER_MAX_VALUE);
}

/**
 * @tc.name: ProgressModifier003
 * @tc.desc: Test ProgressModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTestNg, ProgressModifier003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ProgressModifier and set ProgressModifier property.
     * @tc.expected: step1. Check the ProgressModifier property value.
     */
    ProgressModifier progressModifier;
    progressModifier.SetStrokeWidth(PROGRESS_STROKE_WIDTH);
    LinearColor linearColor;
    progressModifier.SetColor(linearColor);
    EXPECT_EQ(progressModifier.color_->Get(), linearColor);
    progressModifier.SetBackgroundColor(linearColor);
    EXPECT_EQ(progressModifier.bgColor_->Get(), linearColor);
    progressModifier.SetBorderColor(linearColor);
    EXPECT_EQ(progressModifier.borderColor_->Get(), linearColor);
    progressModifier.SetMaxValue(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier.maxValue_->Get(), PROGRESS_MODIFIER_VALUE);
    progressModifier.SetValue(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier.value_->Get(), PROGRESS_MODIFIER_VALUE);
    progressModifier.SetScaleWidth(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier.scaleWidth_->Get(), PROGRESS_MODIFIER_VALUE);
    progressModifier.SetScaleCount(SCALE_COUNT);
    EXPECT_EQ(progressModifier.scaleCount_->Get(), SCALE_COUNT);
    OffsetF offset(0, 0);
    progressModifier.SetContentOffset(offset);
    EXPECT_EQ(progressModifier.offset_->Get(), offset);

    /**
     * @tc.steps: step2. Set different properties, call function onDraw.
     * @tc.expected: step2. Set the properties success.
     */
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, CONTEXT_WIDTH, CONTEXT_HEIGHT };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, Restore()).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(canvas, ClipPath(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawRect(_)).Times(AtLeast(1));

    // set ProgressType CAPSULE(Width >= Height)
    progressModifier.SetProgressType(PROGRESS_TYPE_CAPSULE);
    progressModifier.onDraw(context);
    EXPECT_EQ(progressModifier.progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_CAPSULE));

    // set ProgressType CAPSULE(Width >= Height, progressWidth < radius)
    progressModifier.SetMaxValue(PROGRESS_MODIFIER_MAX_VALUE);
    progressModifier.onDraw(context);
    EXPECT_EQ(progressModifier.maxValue_->Get(), PROGRESS_MODIFIER_MAX_VALUE);

    // set ProgressType CAPSULE(Width >= Height, else)
    progressModifier.SetMaxValue(PROGRESS_MODIFIER_LARGE_VALUE);
    SizeF thirdContentSize(CONTEXT_HUGE_WIDTH, CONTEXT_HEIGHT);
    progressModifier.SetContentSize(thirdContentSize);
    progressModifier.onDraw(context);
    EXPECT_EQ(progressModifier.maxValue_->Get(), PROGRESS_MODIFIER_LARGE_VALUE);
    EXPECT_EQ(progressModifier.contentSize_->Get(), thirdContentSize);

    // set ProgressType CAPSULE(Width < Height)
    progressModifier.SetMaxValue(PROGRESS_MODIFIER_VALUE);
    SizeF secondContentSize(CONTEXT_WIDTH, CONTEXT_LARGE_HEIGHT);
    progressModifier.SetContentSize(secondContentSize);
    progressModifier.onDraw(context);
    EXPECT_EQ(progressModifier.maxValue_->Get(), PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier.contentSize_->Get(), secondContentSize);
}

/**
 * @tc.name: ProgressModifier004
 * @tc.desc: Test ProgressModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTestNg, ProgressModifier004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ProgressModifier and set ProgressModifier property.
     * @tc.expected: step1. Check the ProgressModifier property value.
     */
    ProgressModifier progressModifier;
    progressModifier.SetStrokeWidth(PROGRESS_STROKE_WIDTH);
    LinearColor linearColor;
    progressModifier.SetColor(linearColor);
    EXPECT_EQ(progressModifier.color_->Get(), linearColor);
    progressModifier.SetBackgroundColor(linearColor);
    EXPECT_EQ(progressModifier.bgColor_->Get(), linearColor);
    progressModifier.SetBorderColor(linearColor);
    EXPECT_EQ(progressModifier.borderColor_->Get(), linearColor);
    progressModifier.SetMaxValue(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier.maxValue_->Get(), PROGRESS_MODIFIER_VALUE);
    progressModifier.SetValue(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier.value_->Get(), PROGRESS_MODIFIER_VALUE);
    progressModifier.SetScaleWidth(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier.scaleWidth_->Get(), PROGRESS_MODIFIER_VALUE);
    progressModifier.SetScaleCount(SCALE_COUNT);
    EXPECT_EQ(progressModifier.scaleCount_->Get(), SCALE_COUNT);
    OffsetF offset(0, 0);
    progressModifier.SetContentOffset(offset);
    EXPECT_EQ(progressModifier.offset_->Get(), offset);

    /**
     * @tc.steps: step2. Set different properties, call function onDraw.
     * @tc.expected: step2. Set the properties success.
     */
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, CONTEXT_WIDTH, CONTEXT_HEIGHT };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, Restore()).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(canvas, ClipPath(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawRect(_)).Times(AtLeast(1));

    // set ProgressType CAPSULE(Width < Height,progressWidth < radius)
    progressModifier.SetProgressType(PROGRESS_TYPE_CAPSULE);
    progressModifier.SetMaxValue(PROGRESS_MODIFIER_MAX_VALUE);
    SizeF secondContentSize(CONTEXT_WIDTH, CONTEXT_LARGE_HEIGHT);
    progressModifier.SetContentSize(secondContentSize);
    progressModifier.onDraw(context);
    EXPECT_EQ(progressModifier.maxValue_->Get(), PROGRESS_MODIFIER_MAX_VALUE);
    EXPECT_EQ(progressModifier.contentSize_->Get(), secondContentSize);

    // set ProgressType CAPSULE(Width < Height,progressWidth > radius)
    progressModifier.SetProgressType(PROGRESS_TYPE_CAPSULE);
    progressModifier.SetMaxValue(PROGRESS_MODIFIER_MAX_VALUE);
    progressModifier.SetBorderWidth(CONTEXT_WIDTH);
    progressModifier.SetContentSize(secondContentSize);
    progressModifier.onDraw(context);
    EXPECT_EQ(progressModifier.maxValue_->Get(), PROGRESS_MODIFIER_MAX_VALUE);
    EXPECT_EQ(progressModifier.contentSize_->Get(), secondContentSize);

    // set ProgressType CAPSULE(Width < Height,else)
    progressModifier.SetMaxValue(PROGRESS_MODIFIER_LARGE_VALUE);
    SizeF fourthContentSize(CONTEXT_WIDTH, CONTEXT_HUGE_HEIGHT);
    progressModifier.SetContentSize(fourthContentSize);
    progressModifier.onDraw(context);
    EXPECT_EQ(progressModifier.maxValue_->Get(), PROGRESS_MODIFIER_LARGE_VALUE);
    EXPECT_EQ(progressModifier.contentSize_->Get(), fourthContentSize);

    // set ProgressType CIRCLE
    progressModifier.SetProgressType(PROGRESS_TYPE_CIRCLE);
    progressModifier.onDraw(context);
    EXPECT_EQ(progressModifier.progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_CIRCLE));
}

/**
 * @tc.name: ProgressPaintMethod002
 * @tc.desc: Test ProgressPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTestNg, ProgressPaintMethod002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the frameNode_.
     * @tc.expected: step1. Check the frameNode_ was created successfully.
     */
    ProgressModelNG progressModelNG;
    progressModelNG.Create(5.0, 0.0, 10.0, 20.0, PROGRESS_TYPE_CAPSULE);
    auto frameNode_ = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());

    /**
     * @tc.steps: step2. Create the GeometryNode and PaintWrapper.Set the paintProperty_.
     * @tc.expected: step2. Check the GeometryNode and PaintWrapper were created successfully.
     */
    auto pipeline = PipelineBase::GetCurrentContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty_ = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    paintProperty_->UpdateMaxValue(100.0);
    paintProperty_->UpdateValue(0.0);
    paintProperty_->UpdateBorderWidth(0.0_vp);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty_);

    /**
     * @tc.steps: step3. Create ProgressPaintMethod. Call the function UpdateContentModifier and GetContentModifier.
     * @tc.expected: step3. Check the properties update before.
     */
    auto progressModifier = AceType::MakeRefPtr<ProgressModifier>();
    ProgressPaintMethod progressPaintMethod(PROGRESS_TYPE_CAPSULE, PROGRESS_STROKE_WIDTH, progressModifier);
    progressPaintMethod.progressType_ = PROGRESS_TYPE_CAPSULE;
    progressPaintMethod.UpdateContentModifier(paintWrapper);

    paintProperty_->UpdateValue(10.0);
    paintProperty_->UpdateBorderWidth(300.0_vp);
    paintProperty_->UpdateEnableScanEffect(true);
    paintProperty_->UpdateBorderWidth(2.0_vp);
    SizeF progressContentSize(300.0f, 50.0f);
    progressModifier->SetContentSize(progressContentSize);
    progressPaintMethod.UpdateContentModifier(paintWrapper);

    SizeF progressContentSize1(50.0f, 300.0f);
    progressModifier->SetContentSize(progressContentSize1);
    progressPaintMethod.UpdateContentModifier(paintWrapper);

    auto getModifier = progressPaintMethod.GetContentModifier(paintWrapper);
    auto getProgressModifier = AceType::DynamicCast<ProgressModifier>(getModifier);
}

/**
 * @tc.name: ProgressPaintMethod003
 * @tc.desc: Test ProgressPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTestNg, ProgressPaintMethod003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the frameNode_.
     * @tc.expected: step1. Check the frameNode_ was created successfully.
     */
    ProgressModelNG progressModelNG;
    progressModelNG.Create(5.0, 10.0, 10.0, 20.0, PROGRESS_TYPE_RING);
    auto frameNode_ = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());

    /**
     * @tc.steps: step2. Create the GeometryNode and PaintWrapper.Set the paintProperty_.
     * @tc.expected: step2. Check the GeometryNode and PaintWrapper were created successfully.
     */
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty_ = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    paintProperty_->UpdateItalicFontStyle(Ace::FontStyle::ITALIC);
    paintProperty_->UpdateMaxValue(PROGRESS_MODIFIER_MAX_VALUE);
    paintProperty_->UpdateValue(PROGRESS_MODIFIER_VALUE);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty_);

    /**
     * @tc.steps: step3. Create ProgressPaintMethod. Call the function UpdateContentModifier and GetContentModifier.
     * @tc.expected: step3. Check the properties update before.
     */
    auto pipeline = PipelineBase::GetCurrentContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto progressModifier = AceType::MakeRefPtr<ProgressModifier>();
    ProgressPaintMethod progressPaintMethod(PROGRESS_TYPE_LINEAR, PROGRESS_STROKE_WIDTH, progressModifier);
    progressPaintMethod.progressType_ = PROGRESS_TYPE_RING;
    progressPaintMethod.UpdateContentModifier(paintWrapper);
    auto getModifier = progressPaintMethod.GetContentModifier(paintWrapper);
    auto getProgressModifier = AceType::DynamicCast<ProgressModifier>(getModifier);
    EXPECT_TRUE(getProgressModifier->isItalic_->Get());
    EXPECT_EQ(getProgressModifier->maxValue_->Get(), PROGRESS_MODIFIER_MAX_VALUE);
    EXPECT_EQ(getProgressModifier->value_->Get(), PROGRESS_MODIFIER_VALUE);

    Gradient gradient;
    GradientColor gradientColorEnd;
    GradientColor gradientColorStart;
    gradientColorEnd.SetLinearColor(LinearColor(Color::WHITE));
    gradientColorStart.SetLinearColor(LinearColor(Color::WHITE));
    gradientColorEnd.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColorEnd);
    gradientColorStart.SetDimension(Dimension(1.0));
    gradient.AddColor(gradientColorStart);

    paintProperty_->UpdateGradientColor(gradient);
    paintProperty_->UpdateItalicFontStyle(Ace::FontStyle::NORMAL);
    paintProperty_->UpdateMaxValue(PROGRESS_MODIFIER_MAX_VALUE);
    paintProperty_->UpdateValue(PROGRESS_MODIFIER_VALUE);
    progressPaintMethod.progressType_ = PROGRESS_TYPE_RING;
    progressPaintMethod.UpdateContentModifier(paintWrapper);
    getModifier = progressPaintMethod.GetContentModifier(paintWrapper);
    getProgressModifier = AceType::DynamicCast<ProgressModifier>(getModifier);
    EXPECT_FALSE(getProgressModifier->isItalic_->Get());
    EXPECT_EQ(getProgressModifier->maxValue_->Get(), PROGRESS_MODIFIER_MAX_VALUE);
    EXPECT_EQ(getProgressModifier->value_->Get(), PROGRESS_MODIFIER_VALUE);
    delete paintWrapper;
}

/**
 * @tc.name: CapsuleProgressModifier001
 * @tc.desc: Test ProgressModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTestNg, CapsuleProgressModifier001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ProgressModifier and set ProgressModifier property.
     * @tc.expected: step1. Check the ProgressModifier property value.
     */
    ProgressModifier progressModifier;
    LinearColor linearColor;
    progressModifier.SetColor(linearColor);
    EXPECT_EQ(progressModifier.color_->Get(), linearColor);
    progressModifier.SetBackgroundColor(linearColor);
    EXPECT_EQ(progressModifier.bgColor_->Get(), linearColor);
    progressModifier.SetBorderColor(linearColor);
    EXPECT_EQ(progressModifier.borderColor_->Get(), linearColor);

    Testing::MockCanvas canvas;
    DrawingContext context { canvas, 100, 100 };
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
    progressModifier.SetProgressType(PROGRESS_TYPE_CAPSULE);
    progressModifier.SetMaxValue(100.0);
    progressModifier.SetValue(20.0);
    SizeF progressContentSize(200.0, 100.0);
    progressModifier.SetContentSize(progressContentSize);
    progressModifier.SetBorderWidth(2.0);
    progressModifier.onDraw(context);
    EXPECT_EQ(progressModifier.progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_CAPSULE));
    EXPECT_EQ(progressModifier.capsuleBorderWidth_->Get(), 2.0);

    progressModifier.SetProgressType(PROGRESS_TYPE_CAPSULE);
    progressModifier.SetContentSize(progressContentSize);
    progressModifier.SetBorderWidth(100.0);
    progressModifier.onDraw(context);
    EXPECT_EQ(progressModifier.progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_CAPSULE));
    EXPECT_EQ(progressModifier.capsuleBorderWidth_->Get(), 100.0);

    SizeF progressContentSize2(100.0, 200.0);
    progressModifier.SetMaxValue(100.0);
    progressModifier.SetValue(20.0);
    progressModifier.SetBorderWidth(2.0);
    progressModifier.SetContentSize(progressContentSize2);
    progressModifier.onDraw(context);
    EXPECT_EQ(progressModifier.contentSize_->Get(), progressContentSize2);

    progressModifier.SetContentSize(progressContentSize2);
    progressModifier.SetMaxValue(100.0);
    progressModifier.SetValue(20.0);
    progressModifier.SetBorderWidth(2.0);
    progressModifier.onDraw(context);
    EXPECT_EQ(progressModifier.contentSize_->Get(), progressContentSize2);
}

/**
 * @tc.name: CapsuleProgressModifier002
 * @tc.desc: Test the sweep animation of the capsule progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTestNg, CapsuleProgressModifier002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ProgressModifier and set ProgressModifier property.
     * @tc.expected: step1. Check the ProgressModifier property value.
     */
    auto pipeline = PipelineBase::GetCurrentContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto progressModifier = AceType::MakeRefPtr<ProgressModifier>();
    LinearColor linearColor;
    progressModifier->SetColor(linearColor);
    EXPECT_EQ(progressModifier->color_->Get(), linearColor);
    progressModifier->SetBackgroundColor(linearColor);
    EXPECT_EQ(progressModifier->bgColor_->Get(), linearColor);
    progressModifier->SetBorderColor(linearColor);
    EXPECT_EQ(progressModifier->borderColor_->Get(), linearColor);

    Testing::MockCanvas canvas;
    DrawingContext context { canvas, 100, 100 };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, Restore()).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(canvas, ClipPath(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawRect(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));

    /**
     * @tc.steps: step2. Set value while sweeping.
     * @tc.expected: step2. The sweeping date updated successfully.
     */
    progressModifier->SetProgressType(PROGRESS_TYPE_CAPSULE);
    progressModifier->SetMaxValue(100.0);
    progressModifier->SetSweepEffect(true);
    SizeF progressContentSize(200.0, 100.0);
    progressModifier->SetContentSize(progressContentSize);
    progressModifier->SetBorderWidth(2.0);
    progressModifier->isSweeping_ = true;
    progressModifier->sweepingDateBackup_ = 1000.0f;
    progressModifier->SetValue(20.0);
    progressModifier->onDraw(context);
    EXPECT_NE(progressModifier->sweepingDate_, 0.0f);
}

/**
 * @tc.name: RingProgressModifier001
 * @tc.desc: Test the loading and sweeping animation of the ring progress can be started and stoped.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTestNg, RingProgressModifier001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ProgressModifier and set ProgressModifier property.
     * @tc.expected: step1. Check the ProgressModifier property value.
     */
    Gradient gradient;
    GradientColor gradientColorEnd;
    GradientColor gradientColorStart;
    gradientColorEnd.SetLinearColor(LinearColor(Color::WHITE));
    gradientColorStart.SetLinearColor(LinearColor(Color::WHITE));
    gradientColorEnd.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColorEnd);
    gradientColorStart.SetDimension(Dimension(1.0));
    gradient.AddColor(gradientColorStart);

    auto pipeline = PipelineBase::GetCurrentContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto progressModifier = AceType::MakeRefPtr<ProgressModifier>();
    progressModifier->SetVisible(true);
    progressModifier->SetProgressType(PROGRESS_TYPE_RING);
    progressModifier->SetProgressStatus(ProgressStatus::PROGRESSING);
    progressModifier->SetStrokeWidth(PROGRESS_STROKE_WIDTH);
    progressModifier->SetRingSweepEffect(true);
    EXPECT_EQ(progressModifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_RING));
    EXPECT_EQ(progressModifier->strokeWidth_->Get(), PROGRESS_STROKE_WIDTH);
    LinearColor linearColor;
    progressModifier->SetColor(linearColor);
    EXPECT_EQ(progressModifier->color_->Get(), linearColor);
    progressModifier->SetBackgroundColor(linearColor);
    EXPECT_EQ(progressModifier->bgColor_->Get(), linearColor);
    progressModifier->SetRingProgressColor(gradient);
    progressModifier->SetPaintShadow(true);
    progressModifier->SetMaxValue(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier->maxValue_->Get(), PROGRESS_MODIFIER_VALUE);
    progressModifier->SetSmoothEffect(false);
    EXPECT_EQ(progressModifier->smoothEffect_->Get(), false);
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
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(canvas, Restore()).Times(AtLeast(1));
    EXPECT_CALL(canvas, Rotate(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawArc(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, ClipPath(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));

    /**
     * @tc.steps: step2. Set different properties, call function onDraw.
     * @tc.expected: step2. Set the properties success.
     */
    value = 60.0f;
    SizeF ContentSize(CONTEXT_WIDTH, CONTEXT_HEIGHT);
    progressModifier->SetContentSize(ContentSize);
    progressModifier->isSweeping_ = false;
    progressModifier->SetValue(value);
    progressModifier->onDraw(context);
    EXPECT_EQ(progressModifier->isSweeping_, true);

    /**
     * @tc.steps: step3. In sweeping, set value.
     * @tc.expected: step3. The dateUpdated_ is true.
     */
    value = 70.0f;
    progressModifier->sweepingDate_->Set(0.0f);
    progressModifier->isSweeping_ = true;
    progressModifier->sweepingDateBackup_ = 10000.0f;
    progressModifier->SetValue(value);
    progressModifier->onDraw(context);
    EXPECT_EQ(progressModifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_RING));
    EXPECT_TRUE(progressModifier->dateUpdated_);

    /**
     * @tc.steps: step4. In sweeping, set value to 0.
     * @tc.expected: step4. The sweeping animation is stopped.
     */
    value = 0.0f;
    progressModifier->SetValue(value);
    progressModifier->onDraw(context);
    EXPECT_EQ(progressModifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_RING));
    EXPECT_EQ(progressModifier->isSweeping_, false);

    /**
     * @tc.steps: step5. Set progress status to LOADING.
     * @tc.expected: step5. The loading animation is started.
     */
    progressModifier->SetProgressStatus(ProgressStatus::LOADING);
    EXPECT_EQ(progressModifier->isLoading_, true);

    /**
     * @tc.steps: step6. Set the progress invisible.
     * @tc.expected: step6. The loading animation is stopped.
     */
    progressModifier->SetVisible(false);
    EXPECT_EQ(progressModifier->isLoading_, false);
}

/**
 * @tc.name: RingProgressModifier003
 * @tc.desc: Test sets the value in the LOADING state.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTestNg, RingProgressModifier003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ProgressModifier and set ProgressModifier property.
     * @tc.expected: step1. Check the ProgressModifier property value.
     */
    Gradient gradient;
    GradientColor gradientColorEnd;
    GradientColor gradientColorStart;
    gradientColorEnd.SetLinearColor(LinearColor(Color::WHITE));
    gradientColorStart.SetLinearColor(LinearColor(Color::WHITE));
    gradientColorEnd.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColorEnd);
    gradientColorStart.SetDimension(Dimension(1.0));
    gradient.AddColor(gradientColorStart);

    auto pipeline = PipelineBase::GetCurrentContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto progressModifier = AceType::MakeRefPtr<ProgressModifier>();
    progressModifier->SetStrokeWidth(PROGRESS_STROKE_WIDTH);
    LinearColor linearColor;
    progressModifier->SetBackgroundColor(linearColor);
    EXPECT_EQ(progressModifier->bgColor_->Get(), linearColor);
    progressModifier->SetBorderColor(linearColor);
    EXPECT_EQ(progressModifier->borderColor_->Get(), linearColor);
    progressModifier->SetRingProgressColor(gradient);
    progressModifier->SetPaintShadow(true);
    progressModifier->SetMaxValue(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier->maxValue_->Get(), PROGRESS_MODIFIER_VALUE);
    progressModifier->SetValue(50.0f);
    EXPECT_EQ(progressModifier->value_->Get(), 50.0f);
    progressModifier->SetScaleWidth(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier->scaleWidth_->Get(), PROGRESS_MODIFIER_VALUE);

    /**
     * @tc.steps: step2. Sets value in the LOADING state.
     * @tc.expected: step2. Value is not changed.
     */
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, CONTEXT_WIDTH, CONTEXT_HEIGHT };
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, Rotate(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(canvas, Restore()).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(AtLeast(1));

    SizeF ContentSize(CONTEXT_WIDTH, CONTEXT_HEIGHT);
    progressModifier->isLoading_ = true;
    progressModifier->SetContentSize(ContentSize);
    progressModifier->SetProgressType(PROGRESS_TYPE_RING);
    progressModifier->onDraw(context);
    EXPECT_EQ(progressModifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_RING));

    progressModifier->SetValue(20.0f);
    EXPECT_EQ(progressModifier->value_->Get(), 50.0f);
}

/**
 * @tc.name: RingProgressModifier004
 * @tc.desc: Test clip path during sweeping.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTestNg, RingProgressModifier004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ProgressModifier and set ProgressModifier property.
     * @tc.expected: step1. Check the ProgressModifier property value.
     */
    Gradient gradient;
    GradientColor gradientColorEnd;
    GradientColor gradientColorStart;
    gradientColorEnd.SetLinearColor(LinearColor(Color::WHITE));
    gradientColorStart.SetLinearColor(LinearColor(Color::WHITE));
    gradientColorEnd.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColorEnd);
    gradientColorStart.SetDimension(Dimension(1.0));
    gradient.AddColor(gradientColorStart);

    auto pipeline = PipelineBase::GetCurrentContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto progressModifier = AceType::MakeRefPtr<ProgressModifier>();
    progressModifier->SetStrokeWidth(PROGRESS_STROKE_WIDTH);
    LinearColor linearColor;
    progressModifier->SetBackgroundColor(linearColor);
    EXPECT_EQ(progressModifier->bgColor_->Get(), linearColor);
    progressModifier->SetBorderColor(linearColor);
    EXPECT_EQ(progressModifier->borderColor_->Get(), linearColor);
    progressModifier->SetRingProgressColor(gradient);
    progressModifier->SetPaintShadow(true);
    progressModifier->SetMaxValue(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier->maxValue_->Get(), PROGRESS_MODIFIER_VALUE);
    progressModifier->SetValue(50.0f);
    EXPECT_EQ(progressModifier->value_->Get(), 50.0f);
    progressModifier->SetScaleWidth(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier->scaleWidth_->Get(), PROGRESS_MODIFIER_VALUE);

    /**
     * @tc.steps: step2. Set different properties, call function onDraw.
     * @tc.expected: step2. Set the properties success.
     */
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, CONTEXT_WIDTH, CONTEXT_HEIGHT };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, ClipPath(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawArc(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Rotate(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(canvas, Restore()).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));

    // Set sweepingDate_ = 0.
    SizeF ContentSize(CONTEXT_WIDTH, CONTEXT_HEIGHT);
    progressModifier->SetContentSize(ContentSize);
    progressModifier->SetProgressType(PROGRESS_TYPE_RING);
    progressModifier->isLoading_ = false;
    progressModifier->sweepingDate_->Set(0.0f);
    progressModifier->onDraw(context);
    EXPECT_EQ(progressModifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_RING));
    progressModifier->SetValue(80.0f);
    progressModifier->isLoading_ = false;
    progressModifier->sweepingDate_->Set(0.0f);
    progressModifier->onDraw(context);
    EXPECT_EQ(progressModifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_RING));

    // Set sweepingDate_ = 200.
    progressModifier->isLoading_ = false;
    progressModifier->sweepingDate_->Set(200.0f);
    progressModifier->SetContentSize(ContentSize);
    progressModifier->SetProgressType(PROGRESS_TYPE_RING);
    progressModifier->onDraw(context);
    EXPECT_EQ(progressModifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_RING));

    // Set sweepingDate_ = 405.
    progressModifier->SetContentSize(ContentSize);
    progressModifier->SetProgressType(PROGRESS_TYPE_RING);
    progressModifier->isLoading_ = false;
    progressModifier->sweepingDate_->Set(405.0f);
    progressModifier->onDraw(context);
    EXPECT_EQ(progressModifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_RING));
}

/**
 * @tc.name: RingProgressModifier005
 * @tc.desc: Test the modifier while drawing ring progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTestNg, RingProgressModifier005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ProgressModifier and set ProgressModifier property.
     * @tc.expected: step1. Check the ProgressModifier property value.
     */
    Gradient gradient;
    auto pipeline = PipelineBase::GetCurrentContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto progressModifier = AceType::MakeRefPtr<ProgressModifier>();
    SizeF contentSize(CONTEXT_WIDTH, CONTEXT_HEIGHT);
    progressModifier->SetContentSize(contentSize);
    progressModifier->SetVisible(true);
    progressModifier->SetProgressType(PROGRESS_TYPE_RING);
    progressModifier->SetProgressStatus(ProgressStatus::PROGRESSING);
    EXPECT_EQ(progressModifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_RING));
    LinearColor linearColor;
    progressModifier->SetColor(linearColor);
    EXPECT_EQ(progressModifier->color_->Get(), linearColor);
    progressModifier->SetBackgroundColor(linearColor);
    EXPECT_EQ(progressModifier->bgColor_->Get(), linearColor);
    progressModifier->SetRingProgressColor(gradient);
    progressModifier->SetMaxValue(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier->maxValue_->Get(), PROGRESS_MODIFIER_VALUE);
    progressModifier->SetValue(50.0f);
    EXPECT_EQ(progressModifier->value_->Get(), 50.0f);
    OffsetF offset(0, 0);
    progressModifier->SetContentOffset(offset);
    EXPECT_EQ(progressModifier->offset_->Get(), offset);

    Testing::MockCanvas canvas;
    DrawingContext context { canvas, CONTEXT_WIDTH, CONTEXT_HEIGHT };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, ClipPath(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawArc(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Rotate(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(canvas, Restore()).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));

    /**
     * @tc.steps: step2. Disable shadow and make stroke width smaller than the radius, then call function onDraw.
     * @tc.expected: step2. Draw ring progress without shadow.
     */
    progressModifier->SetPaintShadow(false);
    contentSize.SetWidth(CONTEXT_WIDTH);
    contentSize.SetHeight(CONTEXT_WIDTH);
    progressModifier->SetContentSize(contentSize);
    progressModifier->SetStrokeWidth(50.0f);
    progressModifier->onDraw(context);
    EXPECT_EQ(progressModifier->contentSize_->Get(), contentSize);

    /**
     * @tc.steps: step3. Disable shadow and make stroke width equal to the radius, then call function onDraw.
     * @tc.expected: step3. Draw ring progress without shadow.
     */
    progressModifier->SetPaintShadow(false);
    contentSize.SetWidth(CONTEXT_WIDTH);
    contentSize.SetHeight(CONTEXT_WIDTH);
    progressModifier->SetContentSize(contentSize);
    progressModifier->SetStrokeWidth(CONTEXT_WIDTH);
    progressModifier->onDraw(context);
    EXPECT_EQ(progressModifier->contentSize_->Get(), contentSize);

    /**
     * @tc.steps: step4. Enable shadow and make stroke width smaller than the radius, then call function onDraw.
     * @tc.expected: step4. Draw ring progress with shadow.
     */
    progressModifier->SetPaintShadow(true);
    contentSize.SetWidth(CONTEXT_WIDTH);
    contentSize.SetHeight(CONTEXT_WIDTH);
    progressModifier->SetContentSize(contentSize);
    progressModifier->SetStrokeWidth(50.0f);
    progressModifier->onDraw(context);
    EXPECT_EQ(progressModifier->contentSize_->Get(), contentSize);

    /**
     * @tc.steps: step5. Enable shadow and make stroke width close to the radius, then call function onDraw.
     * @tc.expected: step5. Draw ring progress with shadow.
     */
    progressModifier->SetPaintShadow(true);
    contentSize.SetWidth(CONTEXT_WIDTH);
    contentSize.SetHeight(CONTEXT_WIDTH);
    progressModifier->SetContentSize(contentSize);
    progressModifier->SetStrokeWidth(CONTEXT_WIDTH - 5.0f);
    progressModifier->onDraw(context);
    EXPECT_EQ(progressModifier->contentSize_->Get(), contentSize);

    /**
     * @tc.steps: step6. Enable shadow and make radius equal to 10.0, then call function onDraw.
     * @tc.expected: step6. Draw ring progress without shadow.
     */
    progressModifier->SetPaintShadow(true);
    contentSize.SetWidth(20.0f);
    contentSize.SetHeight(20.0f);
    progressModifier->SetContentSize(contentSize);
    progressModifier->SetStrokeWidth(1.0f);
    progressModifier->onDraw(context);
    EXPECT_EQ(progressModifier->contentSize_->Get(), contentSize);
}

/**
 * @tc.name: LinearProgressModifier001
 * @tc.desc: Test ProgressModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTestNg, LinearProgressModifier001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ProgressModifier and set ProgressModifier property.
     * @tc.expected: step1. Check the ProgressModifier property value.
     */
    float value = 50.0f;
    auto pipeline = PipelineBase::GetCurrentContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto progressModifier = AceType::MakeRefPtr<ProgressModifier>();
    progressModifier->SetStrokeWidth(PROGRESS_STROKE_WIDTH);
    LinearColor linearColor;
    progressModifier->SetLinearSweepEffect(true);
    progressModifier->SetBackgroundColor(linearColor);
    EXPECT_EQ(progressModifier->bgColor_->Get(), linearColor);
    progressModifier->SetBorderColor(linearColor);
    EXPECT_EQ(progressModifier->borderColor_->Get(), linearColor);
    progressModifier->SetMaxValue(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier->maxValue_->Get(), PROGRESS_MODIFIER_VALUE);
    progressModifier->SetValue(value);
    EXPECT_EQ(progressModifier->value_->Get(), value);
    progressModifier->SetScaleWidth(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier->scaleWidth_->Get(), PROGRESS_MODIFIER_VALUE);

    /**
     * @tc.steps: step2. Set different properties, call function onDraw.
     * @tc.expected: step2. Set the properties success.
     */
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, CONTEXT_WIDTH, CONTEXT_HEIGHT };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, ClipPath(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawRect(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(canvas, Restore()).Times(AtLeast(1));

    /**
     * @tc.steps: step3. Set value for the horizontal linear progress.
     * @tc.expected: step3. The sweeping animation is started.
     */
    SizeF ContentSize2(200.0f, 100.0f);
    progressModifier->SetContentSize(ContentSize2);
    progressModifier->SetVisible(true);
    progressModifier->isSweeping_ = false;
    progressModifier->SetProgressType(PROGRESS_TYPE_LINEAR);
    progressModifier->SetValue(value);
    progressModifier->onDraw(context);
    EXPECT_EQ(progressModifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_LINEAR));
    EXPECT_EQ(progressModifier->isSweeping_, true);

    /**
     * @tc.steps: step4. Set value for the vertical linear progress.
     * @tc.expected: step4. The dateUpdated_ is true.
     */
    SizeF ContentSize3(50.0f, 100.0f);
    progressModifier->SetContentSize(ContentSize3);
    progressModifier->sweepingDate_->Set(0.0f);
    progressModifier->isSweeping_ = true;
    progressModifier->sweepingDateBackup_ = 10000.0f;
    progressModifier->SetProgressType(PROGRESS_TYPE_LINEAR);
    progressModifier->SetValue(value);
    progressModifier->onDraw(context);
    EXPECT_EQ(progressModifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_LINEAR));
    EXPECT_TRUE(progressModifier->dateUpdated_);

    /**
     * @tc.steps: step5. Set invisible.
     * @tc.expected: step5. The sweeping animation is stopped.
     */
    value = 0.0f;
    progressModifier->SetContentSize(ContentSize3);
    progressModifier->SetProgressType(PROGRESS_TYPE_LINEAR);
    progressModifier->SetValue(value);
    progressModifier->onDraw(context);
    progressModifier->isSweeping_ = true;
    progressModifier->SetVisible(false);
    EXPECT_EQ(progressModifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_LINEAR));
    EXPECT_EQ(progressModifier->isSweeping_, false);
    EXPECT_EQ(progressModifier->isVisible_, false);

    /**
     * @tc.steps: step6. Set value while invisible.
     * @tc.expected: step6. The value is set but the sweepingDate is not set.
     */
    value = 10.0f;
    progressModifier->SetValue(value);
    EXPECT_EQ(progressModifier->value_->Get(), 10.0f);
    EXPECT_EQ(progressModifier->sweepingDate_->Get(), 0.0f);
}

/**
 * @tc.name: ProgressModifier005
 * @tc.desc: Test ProgressModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTestNg, ProgressModifier005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ProgressModifier and set ProgressModifier property.
     * @tc.expected: step1. Check the ProgressModifier property value.
     */
    int32_t minPlatformVersion = PipelineBase::GetCurrentContext()->GetMinPlatformVersion();
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_NINE));
    auto modifier = AceType::MakeRefPtr<ProgressModifier>();

    /**
     * @tc.steps: step2. Set different properties, call function onDraw.
     * @tc.expected: step2. Set the properties success.
     */
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, CONTEXT_WIDTH, CONTEXT_HEIGHT };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawArc(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(canvas, Restore()).Times(AtLeast(1));

    modifier->SetProgressType(PROGRESS_TYPE_SCALE);
    auto contentSize = SizeF(100.0f, 100.0f);
    modifier->SetContentSize(contentSize);
    modifier->onDraw(context);
    EXPECT_EQ(modifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_SCALE));

    modifier->SetStrokeWidth(CONTEXT_WIDTH);
    modifier->SetScaleWidth(3.f);
    modifier->onDraw(context);
    EXPECT_EQ(modifier->scaleWidth_->Get(), 3.f);
    EXPECT_EQ(modifier->strokeWidth_->Get(), CONTEXT_WIDTH);

    modifier->SetProgressType(PROGRESS_TYPE_CAPSULE);
    std::vector<float> valueVector = { 0.f, 50.f, 100.f };
    std::vector<SizeF> contentSizeVector = { SizeF(100.0f, 100.0f), SizeF(50.0f, 100.0f) };
    for (auto i : contentSizeVector) {
        modifier->SetContentSize(i);
        for (auto it : valueVector) {
            modifier->SetValue(it);
            modifier->onDraw(context);
            EXPECT_EQ(modifier->value_->Get(), it);
            EXPECT_EQ(modifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_CAPSULE));
        }
        EXPECT_EQ(modifier->contentSize_->Get(), i);
    }
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(minPlatformVersion);
}

/**
 * @tc.name: ProgressModifier006
 * @tc.desc: Test ProgressModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTestNg, ProgressModifier006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ProgressModifier and set ProgressModifier property.
     * @tc.expected: step1. Check the ProgressModifier property value.
     */
    auto modifier = AceType::MakeRefPtr<ProgressModifier>();

    /**
     * @tc.steps: step2. Set different properties, call function onDraw.
     * @tc.expected: step2. Set the properties success.
     */
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, CONTEXT_WIDTH, CONTEXT_HEIGHT };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawRect(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, ClipPath(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Rotate(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(canvas, Restore()).Times(AtLeast(1));

    modifier->SetProgressType(PROGRESS_TYPE_CAPSULE);
    std::vector<float> valueVector = { 0.f, 50.f, 100.f };
    std::vector<SizeF> contentSizeVector = { SizeF(100.0f, 100.0f), SizeF(50.0f, 100.0f) };
    for (auto i : contentSizeVector) {
        modifier->SetContentSize(i);
        for (auto it : valueVector) {
            modifier->SetValue(it);
            modifier->onDraw(context);
            EXPECT_EQ(modifier->value_->Get(), it);
            EXPECT_EQ(modifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_CAPSULE));
        }
        EXPECT_EQ(modifier->contentSize_->Get(), i);
    }

    std::vector<ProgressType> typeVector = { PROGRESS_TYPE_LINEAR, PROGRESS_TYPE_RING };
    for (auto it : typeVector) {
        modifier->SetProgressType(it);
        modifier->SetMaxValue(0.f);
        modifier->onDraw(context);
        EXPECT_FLOAT_EQ(modifier->maxValue_->Get(), 0.f);
        modifier->SetValue(0.f);
        modifier->onDraw(context);
        EXPECT_FLOAT_EQ(modifier->value_->Get(), 0.f);
        EXPECT_EQ(modifier->progressType_->Get(), static_cast<int32_t>(it));
    }
}

/**
 * @tc.name: ProgressModifier007
 * @tc.desc: Test PROGRESS_TYPE_CAPSULE ProgressModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTestNg, ProgressModifier007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ProgressModifier and set ProgressModifier property.
     * @tc.expected: step1. Check the ProgressModifier property value.
     */
    auto modifier = AceType::MakeRefPtr<ProgressModifier>();
    modifier->SetProgressType(PROGRESS_TYPE_CAPSULE);
    auto contentSize = SizeF(100.0f, 100.0f);
    modifier->SetContentSize(contentSize);
    EXPECT_EQ(modifier->contentSize_->Get(), contentSize);
    EXPECT_EQ(modifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_CAPSULE));

    /**
     * @tc.steps: step2. Set different properties, call function onDraw.
     * @tc.expected: step2. Set the properties success.
     */
    modifier->SetSweepEffect(true);
    modifier->dateUpdated_ = true;
    modifier->SetValue(10.f);
    EXPECT_FLOAT_EQ(modifier->value_->Get(), 10.f);
    EXPECT_EQ(modifier->sweepEffect_->Get(), true);
    EXPECT_EQ(modifier->isSweeping_, true);
    EXPECT_EQ(modifier->dateUpdated_, false);

    modifier->SetVisible(false);
    modifier->SetSweepEffect(true);
    modifier->SetProgressStatus(ProgressStatus::LOADING);
    modifier->StartCapsuleSweepingAnimationImpl(1.f, 1.f);
    modifier->StartContinuousSweepingAnimation(0.f, 1.f, 1.f);
    EXPECT_EQ(modifier->isVisible_, false);
    EXPECT_EQ(modifier->isSweeping_, false);
    EXPECT_FLOAT_EQ(modifier->sweepingDate_->Get(), 0.f);
    EXPECT_EQ(modifier->sweepEffect_->Get(), true);
    EXPECT_EQ(modifier->progressStatus_->Get(), static_cast<int32_t>(ProgressStatus::LOADING));

    modifier->SetVisible(true);
    modifier->SetProgressType(PROGRESS_TYPE_SCALE);
    modifier->StartContinuousSweepingAnimation(0.f, 1.f, 1.f);
    EXPECT_EQ(modifier->isVisible_, true);
    EXPECT_EQ(modifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_SCALE));
}

/**
 * @tc.name: ProgressModifier008
 * @tc.desc: Test PROGRESS_TYPE_RING ProgressModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTestNg, ProgressModifier008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ProgressModifier and set ProgressModifier property.
     * @tc.expected: step1. Check the ProgressModifier property value.
     */
    auto modifier = AceType::MakeRefPtr<ProgressModifier>();
    modifier->SetProgressType(PROGRESS_TYPE_RING);
    auto contentSize = SizeF(100.0f, 100.0f);
    modifier->SetContentSize(contentSize);
    EXPECT_EQ(modifier->contentSize_->Get(), contentSize);
    EXPECT_EQ(modifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_RING));

    /**
     * @tc.steps: step2. Set different properties, call function onDraw.
     * @tc.expected: step2. Set the properties success.
     */
    modifier->SetRingSweepEffect(true);
    modifier->dateUpdated_ = true;
    modifier->SetValue(10.f);
    EXPECT_FLOAT_EQ(modifier->value_->Get(), 10.f);
    EXPECT_EQ(modifier->ringSweepEffect_->Get(), true);
    EXPECT_EQ(modifier->isSweeping_, true);
    EXPECT_EQ(modifier->dateUpdated_, false);

    modifier->StartRingLoadingAnimation();
    EXPECT_EQ(modifier->isLoading_, false);
    EXPECT_FLOAT_EQ(modifier->trailingHeadDate_->Get(), 0.f);
    EXPECT_FLOAT_EQ(modifier->trailingTailDate_->Get(), 0.f);

    modifier->SetValue(-10.f);
    modifier->StartRingLoadingAnimation();
    EXPECT_EQ(modifier->isLoading_, false);
    EXPECT_FLOAT_EQ(modifier->trailingHeadDate_->Get(), 0.f);
    EXPECT_FLOAT_EQ(modifier->trailingTailDate_->Get(), 0.f);

    modifier->SetValue(100.f);
    modifier->StartRingSweepingAnimation(100.f);
    modifier->StartContinuousSweepingAnimation(0.f, 1.f, 1.f);
    EXPECT_FLOAT_EQ(modifier->value_->Get(), 100.f);

    modifier->SetVisible(false);
    modifier->StartRingLoadingAnimation();
    modifier->StartRingSweepingAnimation(100.f);
    EXPECT_EQ(modifier->isVisible_, false);

    modifier->isLoading_ = true;
    modifier->StartRingLoadingAnimation();
    EXPECT_EQ(modifier->isLoading_, true);
}

/**
 * @tc.name: ProgressModifier009
 * @tc.desc: Test PROGRESS_TYPE_LINEAR ProgressModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTestNg, ProgressModifier009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ProgressModifier and set ProgressModifier property.
     * @tc.expected: step1. Check the ProgressModifier property value.
     */
    auto modifier = AceType::MakeRefPtr<ProgressModifier>();
    modifier->SetProgressType(PROGRESS_TYPE_LINEAR);
    auto contentSize = SizeF(100.0f, 100.0f);
    modifier->SetContentSize(contentSize);
    EXPECT_EQ(modifier->contentSize_->Get(), contentSize);
    EXPECT_EQ(modifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_LINEAR));

    /**
     * @tc.steps: step2. Set different properties, call function onDraw.
     * @tc.expected: step2. Set the properties success.
     */
    modifier->SetLinearSweepEffect(true);
    modifier->dateUpdated_ = true;
    modifier->SetValue(10.f);
    EXPECT_FLOAT_EQ(modifier->value_->Get(), 10.f);
    EXPECT_EQ(modifier->linearSweepEffect_->Get(), true);
    EXPECT_EQ(modifier->isSweeping_, true);
    EXPECT_EQ(modifier->dateUpdated_, false);

    modifier->SetValue(0.f);
    modifier->StartLinearSweepingAnimation(0.f);
    modifier->dateUpdated_ = true;
    modifier->StartContinuousSweepingAnimation(0.f, 1.f, 1.f);
    EXPECT_FLOAT_EQ(modifier->value_->Get(), 0.f);
    EXPECT_EQ(modifier->isSweeping_, true);
    EXPECT_EQ(modifier->dateUpdated_, false);

    modifier->SetValue(100.f);
    modifier->StartLinearSweepingAnimation(100.f);
    modifier->StartContinuousSweepingAnimation(0.f, 1.f, 1.f);
    EXPECT_FLOAT_EQ(modifier->value_->Get(), 100.f);

    modifier->SetVisible(false);
    modifier->StartLinearSweepingAnimation(100.f);
    EXPECT_EQ(modifier->isVisible_, false);
}

/**
 * @tc.name: GetContentDrawFunction
 * @tc.desc: Test the function GetContentDrawFunction in ProgressPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTestNg, GetContentDrawFunction, TestSize.Level1)
{
    ProgressType progressType[TYPE_OF_PROGRESS] = { PROGRESS_TYPE_LINEAR, PROGRESS_TYPE_RING, PROGRESS_TYPE_SCALE,
        PROGRESS_TYPE_MOON, PROGRESS_TYPE_CAPSULE };
    for (int32_t i = 0; i < TYPE_OF_PROGRESS; i++) {
        /**
         * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
         * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
         */
        ClearOldNodes();
        ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, progressType[i]);
        model.SetStrokeWidth(LARG_STROKE_WIDTH);
        model.SetScaleWidth(SCALE_WIDTH);
        model.SetScaleCount(SCALE_COUNT);
        CreateDone(frameNode_);

        /**
         * @tc.steps: step3. create GeometryNode and PaintWrapper, ProgressPaintMethod.
         */
        RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
        geometryNode->SetContentSize(SizeF(PROGRESS_COMPONENT_MAXSIZE_WIDTH, PROGRESS_COMPONENT_MAXSIZE_HEIGHT));
        geometryNode->SetContentOffset(OffsetF(0, 0));
        RefPtr<PaintWrapper> paintWrapper =
            AceType::MakeRefPtr<PaintWrapper>(RenderContext::Create(), geometryNode, paintProperty_);
        auto progressModifier = AceType::MakeRefPtr<ProgressModifier>();
        auto progressPaintMethod = AceType::MakeRefPtr<ProgressPaintMethod>(
            progressType[i], LARG_STROKE_WIDTH.ConvertToPx(), progressModifier);
        EXPECT_NE(progressPaintMethod, nullptr);
        EXPECT_NE(progressPaintMethod->progressModifier_, nullptr);
    }
}

/**
 * @tc.name: ProgressPaintMethod001
 * @tc.desc: Test ProgressPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTestNg, ProgressPaintMethod001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the frameNode_.
     * @tc.expected: step1. Check the frameNode_ was created successfully.
     */
    ProgressModelNG progressModelNG;
    progressModelNG.Create(5.0, 10.0, 10.0, 20.0, PROGRESS_TYPE_LINEAR);
    auto frameNode_ = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());

    /**
     * @tc.steps: step2. Create the GeometryNode and PaintWrapper.Set the paintProperty_.
     * @tc.expected: step2. Check the GeometryNode and PaintWrapper were created successfully.
     */
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty_ = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    paintProperty_->UpdateColor(TEST_COLOR);
    paintProperty_->UpdateBackgroundColor(TEST_COLOR);
    paintProperty_->UpdateBorderColor(TEST_COLOR);
    paintProperty_->UpdateMaxValue(PROGRESS_MODIFIER_MAX_VALUE);
    paintProperty_->UpdateValue(PROGRESS_MODIFIER_VALUE);
    paintProperty_->UpdateScaleCount(SCALE_COUNT);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty_);

    /**
     * @tc.steps: step3. Create ProgressPaintMethod. Call the function UpdateContentModifier and GetContentModifier.
     * @tc.expected: step3. Check the properties update before.
     */
    auto pipeline = PipelineBase::GetCurrentContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto progressModifier = AceType::MakeRefPtr<ProgressModifier>();
    ProgressPaintMethod progressPaintMethod(PROGRESS_TYPE_LINEAR, PROGRESS_STROKE_WIDTH, progressModifier);
    // progressType_ = PROGRESS_TYPE_LINEAR
    progressPaintMethod.progressType_ = PROGRESS_TYPE_LINEAR;
    progressPaintMethod.UpdateContentModifier(paintWrapper);
    // progressType_ = PROGRESS_TYPE_MOON
    progressPaintMethod.progressType_ = PROGRESS_TYPE_MOON;
    progressPaintMethod.UpdateContentModifier(paintWrapper);
    // progressType_ = PROGRESS_TYPE_RING
    progressPaintMethod.progressType_ = PROGRESS_TYPE_RING;
    progressPaintMethod.UpdateContentModifier(paintWrapper);
    auto getModifier = progressPaintMethod.GetContentModifier(paintWrapper);
    auto getProgressModifier = AceType::DynamicCast<ProgressModifier>(getModifier);
    EXPECT_EQ(getProgressModifier->color_->Get(), TEST_LINEARCOLOR);
    EXPECT_EQ(getProgressModifier->bgColor_->Get(), TEST_LINEARCOLOR);
    EXPECT_EQ(getProgressModifier->borderColor_->Get(), TEST_LINEARCOLOR);
    EXPECT_EQ(getProgressModifier->scaleCount_->Get(), SCALE_COUNT);
    EXPECT_EQ(getProgressModifier->maxValue_->Get(), PROGRESS_MODIFIER_MAX_VALUE);
    EXPECT_EQ(getProgressModifier->value_->Get(), PROGRESS_MODIFIER_VALUE);
    delete paintWrapper;
}

/**
 * @tc.name: ProgressPaintMethod004
 * @tc.desc: Test ProgressPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTestNg, ProgressPaintMethod004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the frameNode_.
     * @tc.expected: step1. Check the frameNode_ was created successfully.
     */
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_MOON);
    model.SetStrokeWidth(LARG_STROKE_WIDTH);
    model.SetShowText(true);
    CreateDone(frameNode_);

    /**
     * @tc.steps: step2. Create the GeometryNode and PaintWrapper.Set the paintProperty_.
     * @tc.expected: step2. Check the GeometryNode and PaintWrapper were created successfully.
     */
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty_ = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    paintProperty_->UpdateColor(TEST_COLOR);
    paintProperty_->UpdateBackgroundColor(TEST_COLOR);
    paintProperty_->UpdateBorderColor(TEST_COLOR);
    paintProperty_->UpdateMaxValue(PROGRESS_MODIFIER_MAX_VALUE);
    paintProperty_->UpdateValue(PROGRESS_MODIFIER_VALUE);
    paintProperty_->UpdateScaleCount(SCALE_COUNT);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty_);
    paintWrapper->geometryNode_->SetContentSize(SizeF(16.f, 16.f));

    /**
     * @tc.steps: step3. Create ProgressPaintMethod. Call the function UpdateContentModifier and GetContentModifier.
     * @tc.expected: step3. Check the properties update before.
     */
    auto progressModifier = AceType::MakeRefPtr<ProgressModifier>();
    ProgressPaintMethod progressPaintMethod(PROGRESS_TYPE_LINEAR, PROGRESS_STROKE_WIDTH, progressModifier);
    progressPaintMethod.UpdateContentModifier(paintWrapper);
    EXPECT_FLOAT_EQ(progressPaintMethod.strokeWidth_, PROGRESS_STROKE_WIDTH);

    progressPaintMethod.progressType_ = PROGRESS_TYPE_SCALE;
    progressPaintMethod.UpdateContentModifier(paintWrapper);
    EXPECT_FLOAT_EQ(progressPaintMethod.strokeWidth_, 4.f);

    paintWrapper->geometryNode_->SetContentSize(SizeF(30.f, 30.f));
    progressPaintMethod.UpdateContentModifier(paintWrapper);
    EXPECT_FLOAT_EQ(progressPaintMethod.strokeWidth_, 4.f);

    progressPaintMethod.progressType_ = PROGRESS_TYPE_CIRCLE;
    progressPaintMethod.UpdateContentModifier(paintWrapper);
    EXPECT_FLOAT_EQ(progressPaintMethod.strokeWidth_, 4.f);
    delete paintWrapper;
}

/**
 * @tc.name: ProgressModifierRTL001
 * @tc.desc: Test RightToLeft PROGRESS_TYPE_LINEAR ProgressModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTestNg, ProgressModifierRTL001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ProgressModifier and set ProgressModifier property.
     * @tc.expected: step1. Check the ProgressModifier property value.
     */
    auto progressModifier = AceType::MakeRefPtr<ProgressModifier>();

    /**
     * @tc.steps: step2. Set different properties, call function onDraw.
     * @tc.expected: step2. Set the properties success.
     */
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, CONTEXT_WIDTH, CONTEXT_HEIGHT };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, ClipPath(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawRect(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(canvas, Restore()).Times(AtLeast(1));

    /**
     * @tc.steps: step3. Set RightToLeft value for the horizontal linear progress.
     * @tc.expected: step3. The sweeping animation is started.
     */
    float value = 50.0f;
    SizeF ContentSize2(200.0f, 100.0f);
    progressModifier->SetIsRightToLeft(true);
    EXPECT_EQ(progressModifier->isRightToLeft_->Get(), true);
    progressModifier->SetContentSize(ContentSize2);
    progressModifier->SetVisible(true);
    progressModifier->isSweeping_ = false;
    progressModifier->SetProgressType(PROGRESS_TYPE_LINEAR);
    progressModifier->SetValue(value);
    progressModifier->onDraw(context);
    EXPECT_EQ(progressModifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_LINEAR));
}

/**
 * @tc.name: ProgressModifierRTL002
 * @tc.desc: Test RightToLeft PROGRESS_TYPE_RING ProgressModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTestNg, ProgressModifierRTL002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ProgressModifier and set ProgressModifier property.
     * @tc.expected: step1. Check the ProgressModifier property value.
     */
    auto progressModifier = AceType::MakeRefPtr<ProgressModifier>();

    /**
     * @tc.steps: step2. Set different properties, call function onDraw.
     * @tc.expected: step2. Set the properties success.
     */
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, CONTEXT_WIDTH, CONTEXT_HEIGHT };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, ClipPath(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawArc(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Rotate(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(canvas, Restore()).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Scale(_, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Translate(_, _)).Times(AtLeast(1));

    // Set RightToLeft SweepingDate_ = 200.
    SizeF ContentSize(CONTEXT_WIDTH, CONTEXT_HEIGHT);
    progressModifier->SetIsRightToLeft(true);
    EXPECT_EQ(progressModifier->isRightToLeft_->Get(), true);
    progressModifier->SetStrokeWidth(PROGRESS_STROKE_WIDTH);
    progressModifier->SetPaintShadow(true);
    progressModifier->SetMaxValue(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier->maxValue_->Get(), PROGRESS_MODIFIER_VALUE);
    progressModifier->SetValue(50.0f);
    EXPECT_EQ(progressModifier->value_->Get(), 50.0f);
    progressModifier->SetScaleWidth(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier->scaleWidth_->Get(), PROGRESS_MODIFIER_VALUE);
    progressModifier->isLoading_ = false;
    progressModifier->sweepingDate_->Set(200.0f);
    progressModifier->SetContentSize(ContentSize);
    progressModifier->SetProgressType(PROGRESS_TYPE_RING);
    progressModifier->onDraw(context);
    EXPECT_EQ(progressModifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_RING));
}

/**
 * @tc.name: ProgressModifierRTL003
 * @tc.desc: Test RightToLeft PROGRESS_TYPE_SCALE AND MOON ProgressModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTestNg, ProgressModifierRTL003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ProgressModifier and set ProgressModifier property.
     * @tc.expected: step1. Check the ProgressModifier property value.
     */
    auto progressModifier = AceType::MakeRefPtr<ProgressModifier>();

    /**
     * @tc.steps: step2. Set different properties, call function onDraw.
     * @tc.expected: step2. Set the properties success.
     */
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, CONTEXT_WIDTH, CONTEXT_HEIGHT };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawArc(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(canvas, Restore()).Times(AtLeast(1));
    EXPECT_CALL(canvas, Scale(_, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Translate(_, _)).Times(AtLeast(1));

    // set RightToLeft ProgressType SCALE
    progressModifier->SetIsRightToLeft(true);
    EXPECT_EQ(progressModifier->isRightToLeft_->Get(), true);
    progressModifier->SetProgressType(PROGRESS_TYPE_SCALE);
    progressModifier->onDraw(context);
    EXPECT_EQ(progressModifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_SCALE));

    // set RightToLeft ProgressType SCALE SetScaleWidth 0
    progressModifier->SetIsRightToLeft(true);
    EXPECT_EQ(progressModifier->isRightToLeft_->Get(), true);
    progressModifier->SetScaleWidth(0);
    progressModifier->onDraw(context);
    EXPECT_EQ(progressModifier->scaleWidth_->Get(), 0);

    // set RightToLeft ProgressType MOON
    progressModifier->SetIsRightToLeft(true);
    EXPECT_EQ(progressModifier->isRightToLeft_->Get(), true);
    progressModifier->SetStrokeWidth(PROGRESS_STROKE_WIDTH);
    progressModifier->SetProgressType(PROGRESS_TYPE_MOON);
    progressModifier->onDraw(context);
    EXPECT_EQ(progressModifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_MOON));
    EXPECT_EQ(progressModifier->strokeWidth_->Get(), PROGRESS_STROKE_WIDTH);

    // set RightToLeft ProgressType MOON(angle <=FLOAT_ZERO_FIVE)
    progressModifier->SetIsRightToLeft(true);
    EXPECT_EQ(progressModifier->isRightToLeft_->Get(), true);
    progressModifier->SetMaxValue(PROGRESS_MODIFIER_MAX_VALUE);
    progressModifier->onDraw(context);
    EXPECT_EQ(progressModifier->maxValue_->Get(), PROGRESS_MODIFIER_MAX_VALUE);
}

/**
 * @tc.name: ProgressModifierRTL004
 * @tc.desc: Test RightToLeft PROGRESS_TYPE_CAPSULE ProgressModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTestNg, ProgressModifierRTL004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ProgressModifier and set ProgressModifier property.
     * @tc.expected: step1. Check the ProgressModifier property value.
     */
    auto modifier = AceType::MakeRefPtr<ProgressModifier>();

    /**
     * @tc.steps: step2. Set different properties, call function onDraw.
     * @tc.expected: step2. Set the properties success.
     */
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, CONTEXT_WIDTH, CONTEXT_HEIGHT };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawRect(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, ClipPath(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(canvas, Restore()).Times(AtLeast(1));

    modifier->SetProgressType(PROGRESS_TYPE_CAPSULE);
    modifier->SetIsRightToLeft(true);
    EXPECT_EQ(modifier->isRightToLeft_->Get(), true);
    std::vector<float> valueVector = { 0.f, 50.f, 100.f };
    std::vector<SizeF> contentSizeVector = { SizeF(100.0f, 100.0f), SizeF(50.0f, 100.0f) };
    for (auto i : contentSizeVector) {
        modifier->SetContentSize(i);
        for (auto it : valueVector) {
            modifier->SetValue(it);
            modifier->onDraw(context);
            EXPECT_EQ(modifier->value_->Get(), it);
            EXPECT_EQ(modifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_CAPSULE));
        }
        EXPECT_EQ(modifier->contentSize_->Get(), i);
    }
}
} // namespace OHOS::Ace::NG
