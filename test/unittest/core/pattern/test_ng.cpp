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
}

void TestNG::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
    MockAnimationManager::Enable(false);
}

RefPtr<PaintWrapper> TestNG::FlushLayoutTask(const RefPtr<FrameNode>& frameNode, bool markDirty)
{
    if (markDirty) {
        frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
    frameNode->SetActive();
    frameNode->isLayoutDirtyMarked_ = true;
    frameNode->CreateLayoutTask();
    auto paintProperty = frameNode->GetPaintProperty<PaintProperty>();
    auto wrapper = frameNode->CreatePaintWrapper();
    if (wrapper != nullptr) {
        wrapper->FlushRender();
    }
    paintProperty->CleanDirty();
    frameNode->SetActive(false);
    return wrapper;
}

void TestNG::FlushExpandSafeAreaTask()
{
    auto pipeline = MockPipelineContext::GetCurrent();
    CHECK_NULL_VOID(pipeline);
    auto safeAreaManager = pipeline->GetSafeAreaManager();
    CHECK_NULL_VOID(safeAreaManager);
    safeAreaManager->ExpandSafeArea();
}

RefPtr<PaintWrapper> TestNG::CreateDone(const RefPtr<FrameNode>& frameNode)
{
    auto& elementsStack = ViewStackProcessor::GetInstance()->elementsStack_;
    while (elementsStack.size() > 1) {
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto rootNode = AceType::DynamicCast<FrameNode>(element);
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    auto layoutNode = frameNode ? frameNode : rootNode;
    layoutNode->MarkModifyDone();
    return FlushLayoutTask(layoutNode);
}

void TestNG::CreateLayoutTask(const RefPtr<FrameNode>& frameNode)
{
    frameNode->SetActive();
    frameNode->SetLayoutDirtyMarked(true);
    frameNode->CreateLayoutTask();
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

RefPtr<FrameNode> TestNG::CreateText(const std::string& content, const std::function<void(TextModelNG)>& callback)
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

void TestNG::DragStart(const RefPtr<FrameNode>& frameNode, Offset startOffset)
{
    rootNode_ = FindRootNode(frameNode);
    dragNode_ = FindScrollableNode(frameNode);
    GestureEvent gesture;
    dragInfo_ = gesture;
    auto pattern = dragNode_->GetPattern<ScrollablePattern>();
    auto scrollable = pattern->GetScrollableEvent()->GetScrollable();
    dragInfo_.SetSourceTool(SourceTool::FINGER);
    dragInfo_.SetInputEventType(InputEventType::TOUCH_SCREEN);
    dragInfo_.SetGlobalPoint(Point() + startOffset);
    dragInfo_.SetGlobalLocation(startOffset);
    dragInfo_.SetLocalLocation(startOffset);
    scrollable->HandleTouchDown();
    scrollable->isDragging_ = true;
    scrollable->HandleDragStart(dragInfo_);
}

void TestNG::DragUpdate(float delta)
{
    auto pattern = dragNode_->GetPattern<ScrollablePattern>();
    auto scrollable = pattern->GetScrollableEvent()->GetScrollable();
    double velocity = delta > 0 ? 200 : -200;
    dragInfo_.SetMainVelocity(velocity);
    dragInfo_.SetMainDelta(delta);
    dragInfo_.SetGlobalPoint(Point(0, delta));
    dragInfo_.SetGlobalLocation(Offset(0, delta));
    dragInfo_.SetLocalLocation(Offset(0, delta));
    scrollable->HandleDragUpdate(dragInfo_);
    FlushLayoutTask(rootNode_);
    FlushLayoutTask(dragNode_);
}

void TestNG::DragEnd(float velocityDelta)
{
    auto pattern = dragNode_->GetPattern<ScrollablePattern>();
    auto scrollable = pattern->GetScrollableEvent()->GetScrollable();
    float velocity = velocityDelta * FRICTION * -FRICTION_SCALE;
    dragInfo_.SetMainDelta(0);
    dragInfo_.SetMainVelocity(velocity);
    dragInfo_.SetGlobalPoint(dragInfo_.GetGlobalPoint());
    dragInfo_.SetGlobalLocation(dragInfo_.GetGlobalLocation());
    dragInfo_.SetLocalLocation(dragInfo_.GetLocalLocation());
    scrollable->HandleTouchUp();
    scrollable->HandleDragEnd(dragInfo_);
    scrollable->isDragging_ = false;
    FlushLayoutTask(rootNode_);
    FlushLayoutTask(dragNode_);
    rootNode_ = nullptr;
    dragNode_ = nullptr;
}

void TestNG::DragAction(const RefPtr<FrameNode>& frameNode, Offset startOffset, float dragDelta, float velocityDelta)
{
    DragStart(frameNode, startOffset);
    DragUpdate(dragDelta);
    DragEnd(velocityDelta);
}

RefPtr<FrameNode> TestNG::FindRootNode(const RefPtr<FrameNode>& frameNode)
{
    auto rootNode = frameNode;
    while (rootNode && !rootNode->IsRootNode()) {
        if (!rootNode->GetParent()) {
            break;
        }
        rootNode = AceType::DynamicCast<FrameNode>(rootNode->GetParent());
    }
    return rootNode;
}

RefPtr<FrameNode> TestNG::FindScrollableNode(const RefPtr<FrameNode>& frameNode)
{
    auto scrollableNode = frameNode;
    while (scrollableNode) {
        if (AceType::InstanceOf<ScrollablePattern>(scrollableNode->GetPattern())) {
            return scrollableNode;
        }
        scrollableNode = AceType::DynamicCast<FrameNode>(scrollableNode->GetParent());
    }
    return scrollableNode;
}
} // namespace OHOS::Ace::NG