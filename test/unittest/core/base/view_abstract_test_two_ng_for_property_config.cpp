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

#include "test/unittest/core/base/view_abstract_test_ng.h"

#include "base/subwindow/subwindow_manager.h"
#include "test/mock/base/mock_system_properties.h"
#include "test/mock/base/mock_task_executor.h"


#include "core/common/resource/resource_manager.h"
#include "core/common/resource/resource_wrapper.h"
#include "core/common/resource/resource_parse_utils.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float APPEARINGTIME = 300.0f;
constexpr float CONTINUOUSTIME = 300.0f;
}
/**
 * @tc.name: ViewAbstractTest031
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */

/**
 * @tc.name: ViewAbstractAddHoverEventForTipsTest002
 * @tc.desc: Test the AddHoverEventForTips of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractAddHoverEventForTipsTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create some FrameNode and params.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("two", 2, AceType::MakeRefPtr<Pattern>());
    auto param = AceType::MakeRefPtr<PopupParam>();
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);

    auto popupInfo = overlayManager->GetPopupInfo(targetNode->GetId());
    param->SetAnchorType(TipsAnchorType::CURSOR);
    ViewAbstract::AddHoverEventForTips(param, targetNode, popupInfo, false);
    auto eventHub = targetNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto inputHub = eventHub->GetOrCreateInputEventHub();
    ASSERT_NE(inputHub, nullptr);
    auto hoverEventActuator = inputHub->hoverEventActuator_;
    ASSERT_NE(hoverEventActuator, nullptr);
    auto Events = hoverEventActuator->inputEvents_;
    bool ishover = true;
    for (const auto& callback : Events) {
        (*callback)(ishover);
    }
    ishover = false;
    for (const auto& callback : Events) {
        (*callback)(ishover);
    }
    EXPECT_NE(overlayManager->GetPopupInfo(targetNode->GetId()).popupNode, nullptr);
    EXPECT_EQ(Events.size(), 1);
}

/**
 * @tc.name: ViewAbstractAddMouseEventForTipsTest001
 * @tc.desc: Test the AddMouseEventForTips of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractAddMouseEventForTipsTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create some FrameNode and params.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("two", -2, AceType::MakeRefPtr<Pattern>());
    auto param = AceType::MakeRefPtr<PopupParam>();
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);

    auto popupInfo = overlayManager->GetPopupInfo(targetNode->GetId());
    popupInfo.isTips = true;
    popupInfo.popupNode = FrameNode::CreateFrameNode(
        V2::POPUP_ETS_TAG, -1, AceType::MakeRefPtr<BubblePattern>(targetNode->GetId(), targetNode->GetTag()));
    EXPECT_EQ(param->GetAnchorType(), TipsAnchorType::TARGET);
    param->SetAnchorType(TipsAnchorType::CURSOR);
    EXPECT_EQ(param->GetAnchorType(), TipsAnchorType::CURSOR);
    ViewAbstract::AddMouseEventForTips(targetNode, popupInfo);
    auto eventHub = targetNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto inputHub = eventHub->GetOrCreateInputEventHub();
    ASSERT_NE(inputHub, nullptr);
    auto mouseEventActuator = inputHub->mouseEventActuator_;
    ASSERT_NE(mouseEventActuator, nullptr);
    auto events = mouseEventActuator->inputEvents_;
    EXPECT_EQ(events.size(), 1);
    EXPECT_NE(popupInfo.popupNode, nullptr);
    MouseInfo info;
    info.SetScreenLocation(Offset(100.0, 100.0));
    for (const auto& callback : events) {
        if (callback && callback->GetIstips() && callback->GetTipsFollowCursor()) {
            (*callback)(info);
        }
    }
    auto pattern = popupInfo.popupNode->GetPattern<BubblePattern>();
    EXPECT_EQ(pattern->mouseOffset_, Offset(100.0, 100.0));
}

/**
 * @tc.name: ViewAbstractHandleHoverTipsInfoTest001
 * @tc.desc: Test the handleHoverTipsInfo of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractHandleHoverTipsInfoTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create some FrameNode and params.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("two", 2, AceType::MakeRefPtr<Pattern>());
    auto param = AceType::MakeRefPtr<PopupParam>();
    auto spanString = AceType::MakeRefPtr<SpanString>(u"tipTest");
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);

    auto popupInfo = overlayManager->GetPopupInfo(targetNode->GetId());
    popupInfo.isTips = true;
    ViewAbstract::HandleHoverTipsInfo(param, targetNode, popupInfo, false, spanString);
    for (const auto& destroyCallback : targetNode->destroyCallbacksMap_) {
        if (destroyCallback.second) {
            destroyCallback.second();
        }
    }
    ViewAbstract::HandleHoverTipsInfo(param, targetNode, popupInfo, true, spanString);
    for (const auto& destroyCallback : targetNode->destroyCallbacksMap_) {
        if (destroyCallback.second) {
            destroyCallback.second();
        }
    }
    EXPECT_EQ(overlayManager->GetPopupInfo(targetNode->GetId()).popupNode, nullptr);
}

/**
 * @tc.name: ViewAbstractBindTipsTest002
 * @tc.desc: Test the BindTips of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractBindTipsTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create some FrameNode and params.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("two", 2, AceType::MakeRefPtr<Pattern>());
    const RefPtr<FrameNode> targetNode2 = FrameNode::CreateFrameNode("three", 3, AceType::MakeRefPtr<Pattern>());
    auto param = AceType::MakeRefPtr<PopupParam>();
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto nodeId = targetNode->GetId();
    PopupInfo info = overlayManager->GetPopupInfo(nodeId);
    info.isCurrentOnShow = true;
    info.popupId = 1;
    auto popupNode1 = FrameNode::CreateFrameNode(
        V2::POPUP_ETS_TAG, info.popupId, AceType::MakeRefPtr<BubblePattern>(targetNode->GetId(), targetNode->GetTag()));
    info.popupNode = popupNode1;
    info.target = targetNode2;
    overlayManager->ShowTips(targetNode->GetId(), info, APPEARINGTIME, CONTINUOUSTIME, true);
    auto pattern = popupNode1->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_NE(pattern->IsTipsAppearing(), true);
    EXPECT_NE(overlayManager->GetTipsStatus(targetNode->GetId()), true);
}

/**
 * @tc.name: BackgroundResourceTest001
 * @tc.desc: Test set
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, BackgroundResourceTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Test backgroundColor.
     */
    auto resourceObject = AceType::MakeRefPtr<ResourceObject>();
    auto instance = ViewStackProcessor::GetInstance();
    instance->ClearVisualState();
    EXPECT_TRUE(instance->IsCurrentVisualStateProcess());
    auto frameNode = instance->GetMainFrameNode();
    EXPECT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<Pattern>();
    EXPECT_TRUE(pattern);
    pattern->resourceMgr_ = AceType::MakeRefPtr<PatternResourceManager>();
    EXPECT_TRUE(pattern->resourceMgr_);
    auto resMap = pattern->resourceMgr_->resMap_;
    ViewAbstract::SetBackgroundColorWithResourceObj(BLUE, resourceObject);
    pattern->resourceMgr_->ReloadResources();
    MockPipelineContext::pipeline_ = nullptr;
    pattern->resourceMgr_->ReloadResources();
    MockPipelineContext::SetUp();
    ViewAbstract::SetBackgroundColorWithResourceObj(BLUE, nullptr);
    EXPECT_TRUE(resMap.find("backgroundColor") == resMap.end());
    ViewAbstract::SetBackgroundColor(nullptr, BLUE, resourceObject);

    /**
     * @tc.expected: Return expected results..
     */
    EXPECT_NE(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}
 
/**
 * @tc.name: BackgroundResourceTest002
 * @tc.desc: Test SetBackgroundImageWithResourceObj
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, BackgroundResourceTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Test SetBackgroundImageWithResourceObj.
     */
    auto resourceObject = AceType::MakeRefPtr<ResourceObject>();
    auto instance = ViewStackProcessor::GetInstance();
    instance->ClearVisualState();
    EXPECT_TRUE(instance->IsCurrentVisualStateProcess());
    auto frameNode = instance->GetMainFrameNode();
    EXPECT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<Pattern>();
    EXPECT_TRUE(pattern);
    pattern->resourceMgr_ = AceType::MakeRefPtr<PatternResourceManager>();
    EXPECT_TRUE(pattern->resourceMgr_);
    auto resMap = pattern->resourceMgr_->resMap_;
    ViewAbstract::SetBackgroundImageWithResourceObj(resourceObject, imageSourceInfo);
    auto pipeline = frameNode->GetContext();
    EXPECT_TRUE(pipeline);
    pipeline->SetIsFormRender(true);
    pattern->resourceMgr_->ReloadResources();
    pipeline->SetIsFormRender(false);
    pattern->resourceMgr_->ReloadResources();
    MockPipelineContext::pipeline_ = nullptr;
    pattern->resourceMgr_->ReloadResources();
    frameNode->renderContext_ = nullptr;
    pattern->resourceMgr_->ReloadResources();
    MockPipelineContext::SetUp();
    frameNode->renderContext_ = RenderContext::Create();
    ViewAbstract::SetBackgroundImageWithResourceObj(nullptr, imageSourceInfo);
    EXPECT_TRUE(resMap.find("backgroundImageSrc") == resMap.end());
    ViewAbstract::SetBackgroundImage(nullptr, imageSourceInfo, resourceObject);

    /**
     * @tc.expected: Return expected results..
     */
    EXPECT_NE(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}

/**
 * @tc.name: BackgroundResourceTest003
 * @tc.desc: Test SetBackgroundImageSizeUpdateFunc
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, BackgroundResourceTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Test SetBackgroundImageSizeUpdateFunc.
     */
    auto resourceObject = AceType::MakeRefPtr<ResourceObject>();
    auto instance = ViewStackProcessor::GetInstance();
    ASSERT_NE(instance, nullptr);
    instance->ClearVisualState();
    EXPECT_TRUE(instance->IsCurrentVisualStateProcess());
    auto frameNode = instance->GetMainFrameNode();
    EXPECT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<Pattern>();
    EXPECT_TRUE(pattern);
    pattern->resourceMgr_ = AceType::MakeRefPtr<PatternResourceManager>();
    EXPECT_TRUE(pattern->resourceMgr_);
    auto resMap = pattern->resourceMgr_->resMap_;
    ViewAbstract::SetBackgroundImageSizeUpdateFunc(BACKGROUNDSIZE, resourceObject, "");
    ViewAbstract::SetBackgroundImageSizeUpdateFunc(BACKGROUNDSIZE, resourceObject, "width");
    ViewAbstract::SetBackgroundImageSizeUpdateFunc(BACKGROUNDSIZE, resourceObject, "height");
    pattern->resourceMgr_->ReloadResources();
    ViewAbstract::SetBackgroundImageSizeUpdateFunc(BACKGROUNDSIZE, nullptr, "width");
    ViewAbstract::SetBackgroundImageSizeUpdateFunc(BACKGROUNDSIZE, nullptr, "height");
    EXPECT_TRUE(resMap.find("backgroundImageSizeWidth") == resMap.end());
}

/**
 * @tc.name: CustomBackgroundResourceTest001
 * @tc.desc: Test set
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, CustomBackgroundResourceTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Test customBackgroundColor.
     */
    auto resourceObject = AceType::MakeRefPtr<ResourceObject>();
    auto instance = ViewStackProcessor::GetInstance();
    instance->ClearVisualState();
    EXPECT_TRUE(instance->IsCurrentVisualStateProcess());
    auto frameNode = instance->GetMainFrameNode();
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_TRUE(pattern);
    pattern->resourceMgr_ = AceType::MakeRefPtr<PatternResourceManager>();
    ASSERT_TRUE(pattern->resourceMgr_);
    ViewAbstract::SetCustomBackgroundColorWithResourceObj(BLUE, resourceObject);
    EXPECT_TRUE(pattern->resourceMgr_->resMap_.find("customBackgroundColor") != pattern->resourceMgr_->resMap_.end());
    pattern->resourceMgr_->ReloadResources();
    MockPipelineContext::pipeline_ = nullptr;
    pattern->resourceMgr_->ReloadResources();
    MockPipelineContext::SetUp();
    ViewAbstract::SetCustomBackgroundColorWithResourceObj(BLUE, nullptr);
    EXPECT_TRUE(pattern->resourceMgr_->resMap_.find("customBackgroundColor") == pattern->resourceMgr_->resMap_.end());
    ViewAbstract::SetCustomBackgroundColor(BLUE);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_NE(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}

/**
 * @tc.name: ViewAbstractClearJSFrameNodeOnClickTest001
 * @tc.desc: Test ClearJsFrameNodeOnClick.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractClearJSFrameNodeOnClickTest001, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a FrameNode and set a native onClick event via SetFrameNodeCommonOnClick.
     * @tc.expected: The nodeEventRegistered should be true.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(frameNode, nullptr);
    GestureEventFunc onClick = [](GestureEvent&) {};
    ViewAbstract::SetFrameNodeCommonOnClick(AceType::RawPtr(frameNode), std::move(onClick));

    auto* uiNode = reinterpret_cast<UINode*>(AceType::RawPtr(frameNode));
    ASSERT_NE(uiNode, nullptr);
    auto currentInfo = uiNode->GetInteractionEventBindingInfo();
    EXPECT_EQ(currentInfo.nodeEventRegistered, true);

    /**
     * @tc.steps2: ClearJSFrameNodeOnClick.
     * @tc.expected: The nodeEventRegistered should be false.
     */
    ViewAbstract::ClearJSFrameNodeOnClick(AceType::RawPtr(frameNode));
    currentInfo = uiNode->GetInteractionEventBindingInfo();
    EXPECT_EQ(currentInfo.nodeEventRegistered, false);
}

/**
 * @tc.name: FocusBoxTest001
 * @tc.desc: Test SetFocusBoxStyle
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, FocusBoxTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Test SetFocusBoxStyle.
     */
    auto resourceObject = AceType::MakeRefPtr<ResourceObject>();
    auto instance = ViewStackProcessor::GetInstance();
    ASSERT_NE(instance, nullptr);
    instance->ClearVisualState();
    EXPECT_TRUE(instance->IsCurrentVisualStateProcess());
    auto frameNode = instance->GetMainFrameNode();
    EXPECT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<Pattern>();
    EXPECT_TRUE(pattern);
    pattern->resourceMgr_ = AceType::MakeRefPtr<PatternResourceManager>();
    EXPECT_TRUE(pattern->resourceMgr_);
    auto resMap = pattern->resourceMgr_->resMap_;
    NG::FocusBoxStyle style;
    g_isConfigChangePerform = true;
    ViewAbstract::SetFocusBoxStyle(style);
    pattern->resourceMgr_->ReloadResources();
    EXPECT_TRUE(resMap.find("focusBox") == resMap.end());

    ViewAbstract::SetFocusBoxStyle(frameNode, style, false);
    ViewAbstract::SetFocusBoxStyle(frameNode, style, true);
    EXPECT_TRUE(resMap.find("focusBox") == resMap.end());

    /**
     * @tc.steps: step2.Test SetFocusBoxStyleUpdateFunc.
     */
    ViewAbstract::SetFocusBoxStyleUpdateFunc(style, resourceObject, "");
    ViewAbstract::SetFocusBoxStyleUpdateFunc(style, resourceObject, "focusBoxStyleColor");
    ViewAbstract::SetFocusBoxStyleUpdateFunc(style, resourceObject, "focusBoxStyleMargin");
    ViewAbstract::SetFocusBoxStyleUpdateFunc(style, resourceObject, "focusBoxStyleWidth");
    style.ReloadResources();
    ViewAbstract::SetFocusBoxStyleUpdateFunc(style, nullptr, "focusBoxStyleColor");
    ViewAbstract::SetFocusBoxStyleUpdateFunc(style, nullptr, "focusBoxStyleMargin");
    ViewAbstract::SetFocusBoxStyleUpdateFunc(style, nullptr, "focusBoxStyleWidth");
    EXPECT_TRUE(resMap.find("focusBox") == resMap.end());
}

/**
 * @tc.name: ViewAbstractAddHoverEventForTipsTest001
 * @tc.desc: Test the AddHoverEventForTips of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractAddHoverEventForTipsTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create some FrameNode and params.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("two", 2, AceType::MakeRefPtr<Pattern>());
    auto param = AceType::MakeRefPtr<PopupParam>();
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);

    auto popupInfo = overlayManager->GetPopupInfo(targetNode->GetId());
    ViewAbstract::AddHoverEventForTips(param, targetNode, popupInfo, true);
    auto eventHub = targetNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto inputHub = eventHub->GetOrCreateInputEventHub();
    ASSERT_NE(inputHub, nullptr);
    auto hoverEventActuator = inputHub->hoverEventActuator_;
    ASSERT_NE(hoverEventActuator, nullptr);
    auto Events = hoverEventActuator->inputEvents_;
    bool ishover = true;
    for (const auto& callback : Events) {
        (*callback)(ishover);
    }
    ishover = false;
    for (const auto& callback : Events) {
        (*callback)(ishover);
    }
    EXPECT_NE(overlayManager->GetPopupInfo(targetNode->GetId()).popupNode, nullptr);
    EXPECT_EQ(Events.size(), 1);
}
} // namespace OHOS::Ace::NG