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

#include "refresh_test_ng.h"
#include "test/mock/core/animation/mock_animation_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/pattern/loading_progress/loading_progress_paint_property.h"

namespace OHOS::Ace::NG {
class RefreshLayoutTestNg : public RefreshTestNg {
public:
};

/**
 * @tc.name: AddCustomBuilderNode001
 * @tc.desc: Test AddCustomBuilderNode
 * @tc.type: FUNC
 */
HWTEST_F(RefreshLayoutTestNg, AddCustomBuilderNode001, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    RefreshModelNG model = CreateRefresh();
    CreateDone();
    EXPECT_NE(pattern_->progressChild_, nullptr);
    EXPECT_FALSE(pattern_->isHigherVersion_);

    /**
     * @tc.steps: step1. Add custom
     * @tc.expected: Custom replace progress
     */
    auto builder = CreateCustomNode();
    model.SetCustomBuilder(AceType::RawPtr(frameNode_), AceType::RawPtr(builder));
    frameNode_->MarkModifyDone();
    FlushUITasks();
    EXPECT_EQ(pattern_->customBuilder_, builder);
    EXPECT_EQ(pattern_->progressChild_, nullptr);

    /**
     * @tc.steps: step2. Add same custom
     * @tc.expected: Would not replace node
     */
    model.SetCustomBuilder(AceType::RawPtr(frameNode_), AceType::RawPtr(builder));
    frameNode_->MarkModifyDone();
    FlushUITasks();
    EXPECT_EQ(pattern_->customBuilder_, builder);

    /**
     * @tc.steps: step3. Add diff custom
     * @tc.expected: Replace old custom
     */
    auto newBuilder = CreateCustomNode();
    model.SetCustomBuilder(AceType::RawPtr(frameNode_), AceType::RawPtr(newBuilder));
    frameNode_->MarkModifyDone();
    FlushUITasks();
    EXPECT_EQ(pattern_->customBuilder_, newBuilder);

    /**
     * @tc.steps: step4. Remove custom
     * @tc.expected: Process replace custom
     */
    model.SetCustomBuilder(AceType::RawPtr(frameNode_), nullptr);
    frameNode_->MarkModifyDone();
    FlushUITasks();
    EXPECT_EQ(pattern_->customBuilder_, nullptr);
    EXPECT_NE(pattern_->progressChild_, nullptr);

    /**
     * @tc.steps: step5. Remove custom again
     * @tc.expected: Still progress
     */
    model.SetCustomBuilder(AceType::RawPtr(frameNode_), nullptr);
    frameNode_->MarkModifyDone();
    FlushUITasks();
    EXPECT_EQ(pattern_->customBuilder_, nullptr);
    EXPECT_NE(pattern_->progressChild_, nullptr);
}

/**
 * @tc.name: AddCustomBuilderNode002
 * @tc.desc: Test AddCustomBuilderNode, will replace progress and loadingText
 * @tc.type: FUNC
 */
HWTEST_F(RefreshLayoutTestNg, AddCustomBuilderNode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. SetLoadingText
     * @tc.expected: Has loadingText
     */
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    RefreshModelNG model = CreateRefresh();
    model.SetLoadingText("loadingText");
    CreateDone();
    EXPECT_EQ(pattern_->customBuilder_, nullptr);
    EXPECT_NE(pattern_->progressChild_, nullptr);
    EXPECT_NE(pattern_->loadingTextNode_, nullptr);
    EXPECT_FALSE(pattern_->isHigherVersion_);

    /**
     * @tc.steps: step2. Add custom
     * @tc.expected: Custom replace progress/loadingText
     */
    auto builder = CreateCustomNode();
    model.SetCustomBuilder(AceType::RawPtr(frameNode_), AceType::RawPtr(builder));
    frameNode_->MarkModifyDone();
    FlushUITasks();
    EXPECT_EQ(pattern_->customBuilder_, builder);
    EXPECT_EQ(pattern_->progressChild_, nullptr);
    EXPECT_EQ(pattern_->loadingTextNode_, nullptr);
}

/**
 * @tc.name: AddCustomBuilderNode003
 * @tc.desc: Test AddCustomBuilderNode, update default children's position when remove custom
 * @tc.type: FUNC
 */
HWTEST_F(RefreshLayoutTestNg, AddCustomBuilderNode003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. SetCustomBuilder
     * @tc.expected: Has custom
     */
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    auto builder = CreateCustomNode();
    RefreshModelNG model = CreateRefresh();
    model.SetCustomBuilder(builder);
    model.SetIsCustomBuilderExist(true);
    CreateDone();
    EXPECT_EQ(pattern_->progressChild_, nullptr);
    EXPECT_EQ(pattern_->customBuilder_, builder);
    EXPECT_FALSE(pattern_->isHigherVersion_);

    /**
     * @tc.steps: step2. Remove custom when isRefreshing
     * @tc.expected: Update default children's position
     */
    layoutProperty_->UpdateIsRefreshing(true);
    frameNode_->MarkModifyDone();
    FlushUITasks();

    model.SetCustomBuilder(AceType::RawPtr(frameNode_), nullptr);
    frameNode_->MarkModifyDone();
    FlushUITasks();
    EXPECT_EQ(pattern_->customBuilder_, nullptr);
    EXPECT_NE(pattern_->progressChild_, nullptr);
    auto progressPaintProperty = pattern_->progressChild_->GetPaintProperty<LoadingProgressPaintProperty>();
    EXPECT_EQ(progressPaintProperty->GetRefreshSizeScaleRatio().value(), 0);
}

/**
 * @tc.name: AttrRefreshing001
 * @tc.desc: Test attr refreshing in low version
 * @tc.type: FUNC
 */
HWTEST_F(RefreshLayoutTestNg, AttrRefreshing001, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    CreateRefresh();
    CreateDone();
    EXPECT_FALSE(pattern_->isHigherVersion_);

    /**
     * @tc.steps: step2. Set to refreshing
     * @tc.expected: Refreshing
     */
    layoutProperty_->UpdateIsRefreshing(true);
    frameNode_->MarkModifyDone();
    FlushUITasks();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);

    /**
     * @tc.steps: step2. Set to not refreshing
     * @tc.expected: Not refreshing
     */
    layoutProperty_->UpdateIsRefreshing(false);
    frameNode_->MarkModifyDone();
    FlushUITasks();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DONE);
}

/**
 * @tc.name: OnKeyEvent001
 * @tc.desc: OnKeyEvent return false
 * @tc.type: FUNC
 */
HWTEST_F(RefreshLayoutTestNg, OnKeyEvent001, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    CreateRefresh();
    CreateDone();
    EXPECT_FALSE(pattern_->isHigherVersion_);

    /**
     * @tc.steps: step1. KeyCode::KEY_UNKNOWN
     */
    EXPECT_FALSE(pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_UNKNOWN, KeyAction::UNKNOWN)));

    /**
     * @tc.steps: step2. IsCombinationKey and KeyCode::KEY_UNKNOWN
     */
    EXPECT_FALSE(pattern_->OnKeyEvent(
        KeyEvent(KeyCode::KEY_UNKNOWN, KeyAction::UNKNOWN, { KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_UNKNOWN }, 0,
            TimeStamp(std::chrono::milliseconds(0)), 0, 0, SourceType::KEYBOARD, {})));
}

/**
 * @tc.name: OnKeyEvent002
 * @tc.desc: OnKeyEvent return true
 * @tc.type: FUNC
 */
HWTEST_F(RefreshLayoutTestNg, OnKeyEvent002, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    bool isTrigger = false;
    auto onRefreshing = [&isTrigger]() { isTrigger = true; };
    RefreshModelNG model = CreateRefresh();
    model.SetOnRefreshing(std::move(onRefreshing));
    CreateDone();
    EXPECT_FALSE(pattern_->isHigherVersion_);

    /**
     * @tc.steps: step1. KeyCode::KEY_F5
     * @tc.expected: trigger onRefresh event
     */
    EXPECT_TRUE(pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_F5, KeyAction::UNKNOWN)));
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step2. IsCombinationKey and KeyCode::KEY_R
     * @tc.expected: no trigger onRefresh event
     */
    isTrigger = false;
    EXPECT_TRUE(pattern_->OnKeyEvent(
        KeyEvent(KeyCode::KEY_UNKNOWN, KeyAction::UNKNOWN, { KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_R }, 0,
            TimeStamp(std::chrono::milliseconds(0)), 0, 0, SourceType::KEYBOARD, {})));
    EXPECT_FALSE(isTrigger);
}

/**
 * @tc.name: GetTargetOffset001
 * @tc.desc: Test frame ratio
 * @tc.type: FUNC
 */
HWTEST_F(RefreshLayoutTestNg, GetTargetOffset001, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    CreateRefresh();
    CreateDone();
    pattern_->HandleDragStart();
    EXPECT_FLOAT_EQ(pattern_->GetTargetOffset(), 0.f);
    pattern_->HandleDragUpdate(TRIGGER_REFRESH_DISTANCE / RATIO);
    EXPECT_FLOAT_EQ(pattern_->GetTargetOffset(), TRIGGER_REFRESH_DISTANCE);
    pattern_->HandleDragEnd(0.f);
    EXPECT_FLOAT_EQ(pattern_->GetTargetOffset(), TRIGGER_REFRESH_DISTANCE);
    EXPECT_FALSE(pattern_->isHigherVersion_);
}

/**
 * @tc.name: VersionElevenAttrRefreshing001
 * @tc.desc: Test attr refreshing in VERSION_ELEVEN
 * @tc.type: FUNC
 */
HWTEST_F(RefreshLayoutTestNg, VersionElevenAttrRefreshing001, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    CreateRefresh();
    CreateDone();
    EXPECT_TRUE(pattern_->isHigherVersion_);

    /**
     * @tc.steps: step2. Set to refreshing
     * @tc.expected: Refreshing
     */
    layoutProperty_->UpdateIsRefreshing(true);
    frameNode_->MarkModifyDone();
    FlushUITasks();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);

    /**
     * @tc.steps: step2. Set to not refreshing
     * @tc.expected: Not refreshing
     */
    layoutProperty_->UpdateIsRefreshing(false);
    frameNode_->MarkModifyDone();
    FlushUITasks();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DONE);
}

/**
 * @tc.name: AttrRefreshOffset01
 * @tc.desc: Test attr RefreshOffset
 * @tc.type: FUNC
 */
HWTEST_F(RefreshLayoutTestNg, AttrRefreshOffset01, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    RefreshModelNG model = CreateRefresh();
    model.SetRefreshOffset(Dimension(10.f));
    CreateDone();
    EXPECT_EQ(pattern_->refreshOffset_, Dimension(10.f));
    EXPECT_TRUE(pattern_->isHigherVersion_);

    /**
     * @tc.steps: step1. Illegal arg
     * @tc.expected: refreshOffset_ will be default
     */
    model.SetRefreshOffset(AceType::RawPtr(frameNode_), Dimension(0));
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->refreshOffset_.ConvertToPx(), TRIGGER_REFRESH_DISTANCE);

    /**
     * @tc.steps: step2. Illegal arg and has LoadingText
     * @tc.expected: refreshOffset_ will be another default
     */
    model.SetRefreshOffset(AceType::RawPtr(frameNode_), Dimension(0));
    layoutProperty_->UpdateLoadingText("LoadingText");
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->refreshOffset_.ConvertToPx(), TRIGGER_REFRESH_WITH_TEXT_DISTANCE);
}

/**
 * @tc.name: SetPullDownRatio001
 * @tc.desc: Test SetPullDownRatio in VERSION_TWELVE
 * @tc.type: FUNC
 */
HWTEST_F(RefreshLayoutTestNg, SetPullDownRatio001, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    RefreshModelNG model = CreateRefresh();
    model.SetPullDownRatio(std::nullopt);
    CreateDone();
    EXPECT_EQ(pattern_->CalculatePullDownRatio(), 1.f);
    EXPECT_TRUE(pattern_->isHigherVersion_);

    model.SetPullDownRatio(AceType::RawPtr(frameNode_), 0.f);
    EXPECT_EQ(pattern_->CalculatePullDownRatio(), 0.f);

    model.SetPullDownRatio(AceType::RawPtr(frameNode_), std::nullopt);
    EXPECT_EQ(pattern_->CalculatePullDownRatio(), 1.f);

    model.SetPullDownRatio(AceType::RawPtr(frameNode_), 0.5f);
    EXPECT_EQ(pattern_->CalculatePullDownRatio(), 0.5f);
}

/**
 * @tc.name: Layout001
 * @tc.desc: Test layout in VERSION_TWELVE
 * @tc.type: FUNC
 */
HWTEST_F(RefreshLayoutTestNg, Layout001, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    CreateRefresh();
    CreateDone();
    EXPECT_EQ(frameNode_->GetTag(), "Refresh");
    EXPECT_TRUE(IsEqual(frameNode_->GetGeometryNode()->GetFrameRect(), RectF(0, 0, 32, 32)));
    EXPECT_EQ(frameNode_->GetTotalChildCount(), 1);
    EXPECT_TRUE(pattern_->isHigherVersion_);

    auto loadingProgress = GetChildFrameNode(frameNode_, 0);
    EXPECT_EQ(loadingProgress->GetTag(), "LoadingProgress");
    EXPECT_TRUE(IsEqual(loadingProgress->GetGeometryNode()->GetFrameRect(), RectF(0, 0, 32, 32)));
    EXPECT_EQ(loadingProgress->GetTotalChildCount(), 0);
}

/**
 * @tc.name: LoadingText001
 * @tc.desc: Test LoadingText
 * @tc.type: FUNC
 */
HWTEST_F(RefreshLayoutTestNg, LoadingText001, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    RefreshModelNG model = CreateRefresh();
    model.SetLoadingText("loadingText");
    CreateDone();
    EXPECT_NE(pattern_->loadingTextNode_, nullptr);
    EXPECT_TRUE(pattern_->isHigherVersion_);

    layoutProperty_->ResetLoadingText();
    frameNode_->MarkModifyDone();
    FlushUITasks();
    EXPECT_EQ(pattern_->loadingTextNode_, nullptr);
}

/**
 * @tc.name: LoadingText002
 * @tc.desc: Test LoadingText layout in VERSION_ELEVEN
 * @tc.type: FUNC
 */
HWTEST_F(RefreshLayoutTestNg, LoadingText002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. When has LoadingText
     * @tc.expected: The refresh distance become TRIGGER_REFRESH_WITH_TEXT_DISTANCE
     */
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    RefreshModelNG model = CreateRefresh();
    ViewAbstract::SetHeight(CalcLength(400));
    model.SetLoadingText("loadingText");
    CreateDone();
    EXPECT_EQ(pattern_->GetTriggerRefreshDisTance().ConvertToPx(), TRIGGER_REFRESH_WITH_TEXT_DISTANCE);
    EXPECT_TRUE(pattern_->isHigherVersion_);

    /**
     * @tc.steps: step2. Test refresh action
     * @tc.expected: Would show loading text when OVER_DRAG
     */
    pattern_->HandleDragStart();
    auto loadingTextRenderContext = pattern_->loadingTextNode_->GetRenderContext();
    EXPECT_EQ(loadingTextRenderContext->GetOpacityValue(), 0);
    pattern_->HandleDragUpdate(TRIGGER_LOADING_DISTANCE / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(loadingTextRenderContext->GetOpacityValue(), 0);
    pattern_->HandleDragUpdate(
        (TRIGGER_REFRESH_WITH_TEXT_DISTANCE - TRIGGER_LOADING_DISTANCE) / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(loadingTextRenderContext->GetOpacityValue(), 1);
    pattern_->HandleDragEnd(0.f);
    EXPECT_EQ(loadingTextRenderContext->GetOpacityValue(), 1);
}

/**
 * @tc.name: OnColorConfigurationUpdate001
 * @tc.desc: Test OnColorConfigurationUpdate function
 * @tc.type: FUNC
 */
HWTEST_F(RefreshLayoutTestNg, OnColorConfigurationUpdate001, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    RefreshModelNG model = CreateRefresh();
    model.SetLoadingText("loadingText");
    CreateDone();
    EXPECT_NE(pattern_->loadingTextNode_, nullptr);
    EXPECT_NE(pattern_->refreshTheme_, nullptr);
    EXPECT_TRUE(pattern_->isHigherVersion_);
    EXPECT_TRUE(pattern_->hasLoadingText_);
    
    pattern_->OnColorConfigurationUpdate();
    auto progressPaintProperty = pattern_->progressChild_->GetPaintProperty<LoadingProgressPaintProperty>();
    EXPECT_EQ(progressPaintProperty->GetColorValue(Color::WHITE), Color::BLACK);
    auto textLayoutProperty = pattern_->loadingTextNode_->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_EQ(textLayoutProperty->GetFontSizeValue(0.0_vp), 14.0_fp);
    EXPECT_EQ(textLayoutProperty->GetTextColorValue(Color::WHITE), Color::BLACK);
}

/**
 * @tc.name: CustomBuilderNodeVisibility001
 * @tc.desc: Test CustomBuilderNode's visibility
 * @tc.type: FUNC
 */
HWTEST_F(RefreshLayoutTestNg, CustomBuilderNodeVisibility001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. SetCustomBuilder
     * @tc.expected: custom node exists, and default visibility is visible.
     */
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto builder = CreateCustomNode();
    RefreshModelNG model = CreateRefresh();
    model.SetCustomBuilder(builder);
    model.SetIsCustomBuilderExist(true);
    CreateDone();
    EXPECT_EQ(pattern_->progressChild_, nullptr);
    EXPECT_EQ(pattern_->customBuilder_, builder);
    auto customBuilderLayoutProperty = pattern_->customBuilder_->GetLayoutProperty();
    EXPECT_EQ(customBuilderLayoutProperty->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::VISIBLE);
    EXPECT_TRUE(pattern_->isHigherVersion_);

    /**
     * @tc.steps: step2.  start Refreshing
     * @tc.expected: Update Visibility to VISIBLE
     */
    layoutProperty_->UpdateIsRefreshing(true);
    frameNode_->MarkModifyDone();
    FlushUITasks();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_EQ(customBuilderLayoutProperty->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::VISIBLE);

    /**
     * @tc.steps: step3.  end Refreshing
     * @tc.expected: Update Visibility to VISIBLE
     */
    layoutProperty_->UpdateIsRefreshing(false);
    frameNode_->MarkModifyDone();
    FlushUITasks();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_EQ(customBuilderLayoutProperty->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::VISIBLE);

    /**
     * @tc.steps: step4.  user has setted visibility and  start Refreshing
     * @tc.expected: don't change visibility
     */
    customBuilderLayoutProperty->UpdateVisibility(VisibleType::INVISIBLE, false, true);
    layoutProperty_->UpdateIsRefreshing(true);
    frameNode_->MarkModifyDone();
    FlushUITasks();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_TRUE(customBuilderLayoutProperty->IsUserSetVisibility());
    EXPECT_EQ(customBuilderLayoutProperty->GetVisibility(), VisibleType::INVISIBLE);

    /**
     * @tc.steps: step5.  user has setted visibility and  end Refreshing
     * @tc.expected: don't change visibility
     */
    customBuilderLayoutProperty->UpdateVisibility(VisibleType::VISIBLE, false, true);
    layoutProperty_->UpdateIsRefreshing(false);
    frameNode_->MarkModifyDone();
    FlushUITasks();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_TRUE(customBuilderLayoutProperty->IsUserSetVisibility());
    EXPECT_EQ(customBuilderLayoutProperty->GetVisibility(), VisibleType::VISIBLE);
}

/**
 * @tc.name: BeginAndEndTrailingTrace001
 * @tc.desc: Test BeginTrailingTrace and EndTrailingTrace function
 * @tc.type: FUNC
 */
HWTEST_F(RefreshLayoutTestNg, BeginAndEndTrailingTrace001, TestSize.Level1)
{
    RefreshModelNG model = CreateRefresh();
    CreateDone();
    EXPECT_FALSE(pattern_->hasBeginTrailingTrace_);

    pattern_->BeginTrailingTrace();
    EXPECT_TRUE(pattern_->hasBeginTrailingTrace_);
    pattern_->EndTrailingTrace();
    EXPECT_FALSE(pattern_->hasBeginTrailingTrace_);
}
} // namespace OHOS::Ace::NG
