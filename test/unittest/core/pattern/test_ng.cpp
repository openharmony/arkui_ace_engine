/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#include "test_ng.h"

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/animation/mock_animation_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#define private public
#define protected public
#include "test/mock/core/common/mock_container.h"

#include "core/components_ng/base/view_stack_processor.h"
#undef private
#undef protected

namespace OHOS::Ace::NG {
void TestNG::SetUpTestSuite()
{
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->SetUseNewPipeline();
    MockPipelineContext::SetUp();
    testing::FLAGS_gmock_verbose = "error";
    auto rootNode = MockPipelineContext::GetCurrent()->GetRootElement();
    auto stageNode = AceType::DynamicCast<FrameNode>(rootNode->GetChildAtIndex(0));
    stageNode->GetLayoutProperty()->UpdateAlignment(Alignment::TOP_LEFT);
}

void TestNG::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
    MockAnimationManager::Enable(false);
}

void TestNG::FlushUITasks()
{
    auto currentNode = GetStageNode()->GetChildAtIndex(0);
    currentNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    MockPipelineContext::GetCurrent()->FlushUITasks();
}

void TestNG::FlushUITasks(const RefPtr<FrameNode>& frameNode)
{
    frameNode->SetActive();
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    MockPipelineContext::GetCurrent()->FlushUITasks();
}

void TestNG::FlushExpandSafeAreaTask()
{
    auto pipeline = MockPipelineContext::GetCurrent();
    CHECK_NULL_VOID(pipeline);
    auto safeAreaManager = pipeline->GetSafeAreaManager();
    CHECK_NULL_VOID(safeAreaManager);
    safeAreaManager->ExpandSafeArea();
}

void TestNG::CreateDone()
{
    auto& elementsStack = ViewStackProcessor::GetInstance()->elementsStack_;
    while (elementsStack.size() > 1) {
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto currentNode = AceType::DynamicCast<FrameNode>(element);
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    // rootNode > stageNode > currentNode
    MountToStageNode(currentNode);
    FlushUITasks();
}

void TestNG::CreateLayoutTask(const RefPtr<FrameNode>& frameNode)
{
    frameNode->SetActive();
    frameNode->SetLayoutDirtyMarked(true);
    frameNode->CreateLayoutTask();
}

RefPtr<FrameNode> TestNG::GetStageNode()
{
    auto rootNode = MockPipelineContext::GetCurrent()->GetRootElement();
    auto stageNode = rootNode->GetChildAtIndex(0);
    return AceType::DynamicCast<FrameNode>(stageNode);
}

void TestNG::MountToStageNode(const RefPtr<FrameNode>& currentNode)
{
    auto stageNode = GetStageNode();
    auto oldNode = stageNode->GetChildAtIndex(0);
    stageNode->ReplaceChild(oldNode, currentNode);
}

void TestNG::RemoveFromStageNode()
{
    GetStageNode()->RemoveChildAtIndex(0);
}

uint64_t TestNG::GetActions(const RefPtr<AccessibilityProperty>& accessibilityProperty)
{
    std::unordered_set<AceAction> supportAceActions = accessibilityProperty->GetSupportAction();
    uint64_t actions = 0;
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    return actions;
}

TouchEventInfo TestNG::CreateTouchEventInfo(TouchType touchType, Offset location)
{
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(touchType);
    touchLocationInfo.SetLocalLocation(location);
    TouchEventInfo touchEventInfo("touch");
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo));
    return touchEventInfo;
}

RefPtr<ThemeConstants> TestNG::CreateThemeConstants(const std::string& patternName)
{
    auto resAdapter = RefPtr<ResourceAdapter>();
    auto themeConstants = AceType::MakeRefPtr<ThemeConstants>(resAdapter);
    std::unordered_map<std::string, ResValueWrapper> attributes;
    ResValueWrapper resValueWrapper;
    resValueWrapper.type = ThemeConstantsType::THEME;
    resValueWrapper.value = AceType::MakeRefPtr<ThemeStyle>();
    attributes.insert(std::pair<std::string, ResValueWrapper>(patternName, resValueWrapper));
    themeConstants->currentThemeStyle_ = AceType::MakeRefPtr<ThemeStyle>();
    themeConstants->currentThemeStyle_->SetAttributes(attributes);
    return themeConstants;
}

RefPtr<FrameNode> TestNG::CreateText(const std::u16string& content, const std::function<void(TextModelNG)>& callback)
{
    TextModelNG model;
    model.Create(content);
    if (callback) {
        callback(model);
    }
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    ViewStackProcessor::GetInstance()->PopContainer();
    return AceType::DynamicCast<FrameNode>(element);
}

RefPtr<FrameNode> TestNG::CreateRow(const std::function<void(RowModelNG)>& callback)
{
    RowModelNG model;
    model.Create(std::nullopt, nullptr, "");
    if (callback) {
        callback(model);
    }
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    ViewStackProcessor::GetInstance()->PopContainer();
    return AceType::DynamicCast<FrameNode>(element);
}

RefPtr<FrameNode> TestNG::CreateColumn(const std::function<void(ColumnModelNG)>& callback)
{
    ColumnModelNG model;
    model.Create(std::nullopt, nullptr, "");
    if (callback) {
        callback(model);
    }
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    ViewStackProcessor::GetInstance()->PopContainer();
    return AceType::DynamicCast<FrameNode>(element);
}

void TestNG::SetSize(std::optional<Axis> axis, const CalcLength& crossSize, const CalcLength& mainSize)
{
    if (axis.has_value() && axis.value() == Axis::HORIZONTAL) {
        ViewAbstract::SetWidth(mainSize);
        ViewAbstract::SetHeight(crossSize);
    } else {
        ViewAbstract::SetWidth(crossSize);
        ViewAbstract::SetHeight(mainSize);
    }
}

AssertionResult TestNG::IsExist(const RefPtr<FrameNode>& frameNode, int32_t index)
{
    auto childNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildByIndex(index, true));
    if (childNode) {
        return AssertionSuccess();
    }
    return AssertionFailure();
}

AssertionResult TestNG::IsExistAndActive(const RefPtr<FrameNode>& frameNode, int32_t index)
{
    auto childNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildByIndex(index, true));
    if (!childNode) {
        return AssertionFailure();
    }
    if (childNode->IsActive()) {
        return AssertionSuccess();
    }
    return AssertionFailure();
}

AssertionResult TestNG::IsExistAndInActive(const RefPtr<FrameNode>& frameNode, int32_t index)
{
    auto childNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildByIndex(index, true));
    if (!childNode) {
        return AssertionFailure();
    }
    if (childNode->IsActive()) {
        return AssertionFailure();
    }
    return AssertionSuccess();
}
} // namespace OHOS::Ace::NG
