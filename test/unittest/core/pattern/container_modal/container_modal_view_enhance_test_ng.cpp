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

#include <optional>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "foundation/arkui/ace_engine/frameworks/base/memory/referenced.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_resource_adapter.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "base/geometry/dimension.h"
#include "base/subwindow/subwindow_manager.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components/container_modal/container_modal_element.h"
#include "core/components/theme/advanced_pattern_theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_advanced_register.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
#include "core/components_ng/pattern/container_modal/container_modal_theme.h"
#include "core/components_ng/pattern/container_modal/container_modal_view.h"
#include "core/components_ng/pattern/container_modal/enhance/container_modal_pattern_enhance.h"
#include "core/components_ng/pattern/container_modal/enhance/container_modal_view_enhance.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/relative_container/relative_container_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/event/mouse_event.h"
#include "core/pipeline/container_window_manager.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
const Dimension MENU_FLOAT_X = 226.0_vp;
const Dimension MENU_FLOAT_Y = 28.0_vp;
const Dimension MENU_ITEM_TEXT_PADDING = 8.0_vp;
class ContainerModalViewEnhanceTestNg : public testing::Test {
public:
    RefPtr<FrameNode> CreateContent();
    void CreateContainerModal();
    void GetInstance();
    static void SetUpTestCase();
    static void TearDownTestCase();
    RefPtr<PaintWrapper> FlushLayoutTask(const RefPtr<FrameNode>& frameNode);
    ContainerModalViewEnhance* viewEnhance_;
    RefPtr<FrameNode> frameNode_;
    RefPtr<LayoutProperty> layoutProperty_;
    RefPtr<ContainerModalAccessibilityProperty> accessibilityProperty_;
    RefPtr<ContainerModalPatternEnhance> pattern_;
};

void ContainerModalViewEnhanceTestNg::SetUpTestCase()
{
    MockContainer::SetUp();
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<ContainerModalTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
}

void ContainerModalViewEnhanceTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void ContainerModalViewEnhanceTestNg::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    viewEnhance_ = new ContainerModalViewEnhance();
    pattern_ = frameNode_->GetPattern<ContainerModalPatternEnhance>();
    pattern_->AttachToFrameNode(frameNode_);
    layoutProperty_ = frameNode_->GetLayoutProperty();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<ContainerModalAccessibilityProperty>();
}

void ContainerModalViewEnhanceTestNg::CreateContainerModal()
{
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::CONTAINER_MODAL_ETS_TAG, nodeId,
        []() { return AceType::MakeRefPtr<OHOS::Ace::NG::ContainerModalPatternEnhance>(); });
    ViewStackProcessor::GetInstance()->Push(frameNode);
    GetInstance();
    FlushLayoutTask(frameNode_);
    const auto windowManager = AceType::MakeRefPtr<WindowManager>();
    auto windowMode = WindowMode::WINDOW_MODE_FULLSCREEN;
    auto windowModeCallback = [windowMode]() { return windowMode; };
    windowManager->SetWindowGetModeCallBack(std::move(windowModeCallback));
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->windowManager_ = windowManager;
}

RefPtr<PaintWrapper> ContainerModalViewEnhanceTestNg::FlushLayoutTask(const RefPtr<FrameNode>& frameNode)
{
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

RefPtr<FrameNode> ContainerModalViewEnhanceTestNg ::CreateContent()
{
    return AceType::MakeRefPtr<FrameNode>("content", 0, AceType::MakeRefPtr<Pattern>());
}

/**
 * @tc.name: ContainerModalViewEnhanceTestNgTest001
 * @tc.desc: Test Create
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalViewEnhanceTestNg, ContainerModalViewEnhanceTestNgTest001, TestSize.Level1)
{
    CreateContainerModal();
    auto stagePattern = ViewAdvancedRegister::GetInstance()->GeneratePattern(V2::STAGE_ETS_TAG);
    if (!stagePattern) {
        stagePattern = AceType::MakeRefPtr<StagePattern>();
    }
    auto stageNode =
        FrameNode::CreateFrameNode(V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), stagePattern);
    RefPtr<AppBarView> appBar = AceType::MakeRefPtr<AppBarView>();
    viewEnhance_->Create(stageNode);
    SUCCEED();
}

/**
 * @tc.name: ContainerModalViewEnhanceTestNgTest002
 * @tc.desc: Test BuildTitle
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalViewEnhanceTestNg, ContainerModalViewEnhanceTestNgTest002, TestSize.Level1)
{
    CreateContainerModal();
    viewEnhance_->BuildTitle(frameNode_, false);
    SUCCEED();
}

/**
 * @tc.name: ContainerModalViewEnhanceTestNgTest003
 * @tc.desc: Test SetTapGestureEvent
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalViewEnhanceTestNg, ContainerModalViewEnhanceTestNgTest003, TestSize.Level1)
{
    CreateContainerModal();
    viewEnhance_->BuildTitle(frameNode_, false);
    SUCCEED();
}

class MockWindowManager : public WindowManager {
public:
    MOCK_METHOD(WindowMode, GetWindowMode, (), ());
    MOCK_METHOD(MaximizeMode, GetCurrentWindowMaximizeMode, (), ());
};

/**
 * @tc.name: ContainerModalViewEnhanceTestNgTest004
 * @tc.desc: Test SetTapGestureEvent
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalViewEnhanceTestNg, ContainerModalViewEnhanceTestNgTest004, TestSize.Level1)
{
    CreateContainerModal();
    auto containerModalNode = FrameNode::CreateFrameNode("ContainerModal",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto titleRow = viewEnhance_->BuildTitleContainer(containerModalNode, true);
    viewEnhance_->SetTapGestureEvent(containerModalNode, titleRow);
    SUCCEED();
    auto eventhub = titleRow->GetOrCreateGestureEventHub();
    auto pipeline = PipelineContext::GetCurrentContext();
    auto WindownMode = []() -> WindowMode { return WindowMode::WINDOW_MODE_FULLSCREEN; };
    auto windowManager = pipeline->GetWindowManager();
    windowManager->SetWindowGetModeCallBack(WindownMode);
    auto maxSize = MaximizeMode ::MODE_AVOID_SYSTEM_BAR;
    windowManager->SetCurrentWindowMaximizeMode(maxSize);
    for (auto it : eventhub->backupGestures_) {
        GestureEvent info;
        (*(it->onActionId_))(info);
    }
    auto WindownModeSecondary = []() -> WindowMode { return WindowMode::WINDOW_MODE_SPLIT_SECONDARY; };
    windowManager->SetWindowGetModeCallBack(WindownModeSecondary);
    maxSize = MaximizeMode ::MODE_FULL_FILL;
    windowManager->SetCurrentWindowMaximizeMode(maxSize);
    for (auto it : eventhub->backupGestures_) {
        GestureEvent info;
        (*(it->onActionId_))(info);
    }
    auto WindownModePrimary = []() -> WindowMode { return WindowMode::WINDOW_MODE_SPLIT_PRIMARY; };
    windowManager->SetWindowGetModeCallBack(WindownModePrimary);
    windowManager->SetCurrentWindowMaximizeMode(maxSize);
    for (auto it : eventhub->backupGestures_) {
        GestureEvent info;
        (*(it->onActionId_))(info);
    }
    auto WindownModeFloating = []() -> WindowMode { return WindowMode::WINDOW_MODE_FLOATING; };
    windowManager->SetWindowGetModeCallBack(WindownModeFloating);
    windowManager->SetCurrentWindowMaximizeMode(maxSize);
    for (auto it : eventhub->backupGestures_) {
        GestureEvent info;
        (*(it->onActionId_))(info);
    }
    auto WindownModePip = []() -> WindowMode { return WindowMode::WINDOW_MODE_PIP; };
    windowManager->SetWindowGetModeCallBack(WindownModePip);
    windowManager->SetCurrentWindowMaximizeMode(maxSize);
    for (auto it : eventhub->backupGestures_) {
        GestureEvent info;
        (*(it->onActionId_))(info);
    }
}

/**
 * @tc.name: ContainerModalViewEnhanceTestNgTest005
 * @tc.desc: Test SetTapGestureEvent
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalViewEnhanceTestNg, ContainerModalViewEnhanceTestNgTest005, TestSize.Level2)
{
    CreateContainerModal();
    auto containerModalNode = FrameNode::CreateFrameNode("ContainerModal",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto titleRow = viewEnhance_->BuildTitleContainer(containerModalNode, true);
    viewEnhance_->SetTapGestureEvent(containerModalNode, titleRow);
    SUCCEED();
    viewEnhance_->SetTapGestureEvent(containerModalNode, titleRow);
    SUCCEED();
}

/**
 * @tc.name: ContainerModalViewEnhanceTestNgTest006
 * @tc.desc: Test AddControlButtons
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalViewEnhanceTestNg, ContainerModalViewEnhanceTestNgTest006, TestSize.Level1)
{
    CreateContainerModal();
    auto containerModalNode = FrameNode::CreateFrameNode("ContainerModal",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto controlButtonsRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto fameNode = viewEnhance_->AddControlButtons(containerModalNode, controlButtonsRow);
    if (fameNode) {
        SUCCEED();
    }
}

/**
 * @tc.name: ContainerModalViewEnhanceTestNgTest007
 * @tc.desc: Test AddControlButtons
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalViewEnhanceTestNg, ContainerModalViewEnhanceTestNgTest007, TestSize.Level1)
{
    CreateContainerModal();
    auto containerModalNode = FrameNode::CreateFrameNode("ContainerModal",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto controlButtonsRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto fameNode = viewEnhance_->AddControlButtons(containerModalNode, controlButtonsRow);
    GestureEvent info;
    auto pipeline = PipelineContext::GetCurrentContext();
    auto WindownMode = []() -> WindowMode { return WindowMode::WINDOW_MODE_FULLSCREEN; };
    auto windowManager = pipeline->GetWindowManager();
    windowManager->SetWindowGetModeCallBack(WindownMode);
    auto maxSize = MaximizeMode ::MODE_AVOID_SYSTEM_BAR;
    windowManager->SetCurrentWindowMaximizeMode(maxSize);
    for (auto it : controlButtonsRow->children_) {
        auto buttonNode = AceType::DynamicCast<FrameNode>(it);
        auto gestures = buttonNode->GetOrCreateGestureEventHub()->backupGestures_;
        for (auto item : gestures) {
            (*(item->onActionId_))(info);
        }
    }
    SUCCEED();
}

/**
 * @tc.name: ContainerModalViewEnhanceTestNgTest008
 * @tc.desc: Test AddControlButtons
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalViewEnhanceTestNg, ContainerModalViewEnhanceTestNgTest008, TestSize.Level1)
{
    CreateContainerModal();
    auto containerModalNode = FrameNode::CreateFrameNode("ContainerModal",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto controlButtonsRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto fameNode = viewEnhance_->AddControlButtons(containerModalNode, controlButtonsRow);
    GestureEvent info;
    auto pipeline = PipelineContext::GetCurrentContext();
    auto WindownMode = []() -> WindowMode { return WindowMode::WINDOW_MODE_SPLIT_PRIMARY; };
    auto windowManager = pipeline->GetWindowManager();
    windowManager->SetWindowGetModeCallBack(WindownMode);
    auto maxSize = MaximizeMode ::MODE_FULL_FILL;
    windowManager->SetCurrentWindowMaximizeMode(maxSize);
    for (auto it : controlButtonsRow->children_) {
        auto buttonNode = AceType::DynamicCast<FrameNode>(it);
        auto gestures = buttonNode->GetOrCreateGestureEventHub()->backupGestures_;
        for (auto item : gestures) {
            (*(item->onActionId_))(info);
        }
    }
    SUCCEED();
}

/**
 * @tc.name: ContainerModalViewEnhanceTestNgTest009
 * @tc.desc: Test AddControlButtons
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalViewEnhanceTestNg, ContainerModalViewEnhanceTestNgTest009, TestSize.Level1)
{
    CreateContainerModal();
    auto containerModalNode = FrameNode::CreateFrameNode("ContainerModal",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto controlButtonsRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));

    auto fameNode = viewEnhance_->AddControlButtons(containerModalNode, controlButtonsRow);
    GestureEvent info;
    auto pipeline = PipelineContext::GetCurrentContext();
    auto WindownMode = []() -> WindowMode { return WindowMode::WINDOW_MODE_SPLIT_SECONDARY; };
    auto windowManager = pipeline->GetWindowManager();
    windowManager->SetWindowGetModeCallBack(WindownMode);
    auto maxSize = MaximizeMode ::MODE_FULL_FILL;
    windowManager->SetCurrentWindowMaximizeMode(maxSize);
    for (auto it : controlButtonsRow->children_) {
        auto buttonNode = AceType::DynamicCast<FrameNode>(it);
        auto gestures = buttonNode->GetOrCreateGestureEventHub()->backupGestures_;
        for (auto item : gestures) {
            (*(item->onActionId_))(info);
        }
    }
    SUCCEED();
}

/**
 * @tc.name: ContainerModalViewEnhanceTestNgTest010
 * @tc.desc: Test AddControlButtons
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalViewEnhanceTestNg, ContainerModalViewEnhanceTestNgTest010, TestSize.Level1)
{
    CreateContainerModal();
    auto containerModalNode = FrameNode::CreateFrameNode("ContainerModal",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto controlButtonsRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));

    auto fameNode = viewEnhance_->AddControlButtons(containerModalNode, controlButtonsRow);
    GestureEvent info;
    auto pipeline = PipelineContext::GetCurrentContext();
    auto WindownMode = []() -> WindowMode { return WindowMode::WINDOW_MODE_PIP; };
    auto windowManager = pipeline->GetWindowManager();
    windowManager->SetWindowGetModeCallBack(WindownMode);
    auto maxSize = MaximizeMode ::MODE_FULL_FILL;
    windowManager->SetCurrentWindowMaximizeMode(maxSize);
    for (auto it : controlButtonsRow->children_) {
        auto buttonNode = AceType::DynamicCast<FrameNode>(it);
        auto gestures = buttonNode->GetOrCreateGestureEventHub()->backupGestures_;
        for (auto item : gestures) {
            (*(item->onActionId_))(info);
        }
    }
    SUCCEED();
}

/**
 * @tc.name: ContainerModalViewEnhanceTestNgTest011
 * @tc.desc: Test AddControlButtons
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalViewEnhanceTestNg, ContainerModalViewEnhanceTestNgTest011, TestSize.Level1)
{
    CreateContainerModal();
    auto containerModalNode = FrameNode::CreateFrameNode("ContainerModal",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto controlButtonsRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto fameNode = viewEnhance_->AddControlButtons(containerModalNode, controlButtonsRow);
    GestureEvent info;
    auto pipeline = PipelineContext::GetCurrentContext();
    auto WindownMode = []() -> WindowMode { return WindowMode::WINDOW_MODE_PIP; };
    auto windowManager = pipeline->GetWindowManager();
    windowManager->SetWindowGetModeCallBack(WindownMode);
    auto maxSize = MaximizeMode ::MODE_FULL_FILL;
    windowManager->SetCurrentWindowMaximizeMode(maxSize);
    for (auto it : controlButtonsRow->children_) {
        auto buttonNode = AceType::DynamicCast<FrameNode>(it);
        auto gestures = buttonNode->GetOrCreateGestureEventHub()->backupGestures_;
        for (auto item : gestures) {
            (*(item->onActionId_))(info);
        }
    }
    SUCCEED();
}

/**
 * @tc.name: ContainerModalViewEnhanceTestNgTest012
 * @tc.desc: Test AddControlButtonsc
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalViewEnhanceTestNg, ContainerModalViewEnhanceTestNgTest012, TestSize.Level1)
{
    CreateContainerModal();
    auto containerModalNode = FrameNode::CreateFrameNode("ContainerModal",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto controlButtonsRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto fameNode = viewEnhance_->AddControlButtons(containerModalNode, controlButtonsRow);
    if (fameNode) {
        SUCCEED();
    }
}

/**
 * @tc.name: ContainerModalViewEnhanceTestNgTest013
 * @tc.desc: Test BondingMaxBtnGestureEvent
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalViewEnhanceTestNg, ContainerModalViewEnhanceTestNgTest013, TestSize.Level1)
{
    CreateContainerModal();
    auto containerModalNode = FrameNode::CreateFrameNode("ContainerModal",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto controlButtonsRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto fameNode = viewEnhance_->AddControlButtons(containerModalNode, controlButtonsRow);
    if (fameNode) {
        SUCCEED();
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    auto WindownMode = []() -> WindowMode { return WindowMode::WINDOW_MODE_PIP; };
    auto windowManager = pipeline->GetWindowManager();
    windowManager->SetWindowGetModeCallBack(WindownMode);
    for (auto it : controlButtonsRow->children_) {
        auto buttonNode = AceType::DynamicCast<FrameNode>(it);
        auto gestures = buttonNode->GetOrCreateInputEventHub()->mouseEventActuator_;
        MouseInfo info;
        info.SetButton(MouseButton::LEFT_BUTTON);
        info.SetAction(MouseAction::MOVE);
        Offset screenLocation;
        screenLocation.deltaX_ = 10.2;
        ContainerModalViewEnhance::sIsMenuPending_ = false;
        info.SetScreenLocation(screenLocation);
        for (auto item : gestures->inputEvents_) {
            (*item)(info);
        }
    }
}

/**
 * @tc.name: ContainerModalViewEnhanceTestNgTest014
 * @tc.desc: Test BondingMaxBtnInputEvent
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalViewEnhanceTestNg, ContainerModalViewEnhanceTestNgTest014, TestSize.Level1)
{
    CreateContainerModal();
    auto containerModalNode = FrameNode::CreateFrameNode("ContainerModal",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto controlButtonsRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    viewEnhance_->ResetHoverTimer();
    auto fameNode = viewEnhance_->AddControlButtons(containerModalNode, controlButtonsRow);
    if (fameNode) {
        SUCCEED();
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    auto WindownMode = []() -> WindowMode { return WindowMode::WINDOW_MODE_PIP; };
    auto windowManager = pipeline->GetWindowManager();
    windowManager->SetWindowGetModeCallBack(WindownMode);
    for (auto it : controlButtonsRow->children_) {
        auto buttonNode = AceType::DynamicCast<FrameNode>(it);
        auto gestures = buttonNode->GetOrCreateInputEventHub()->mouseEventActuator_;
        MouseInfo info;
        info.SetButton(MouseButton::LEFT_BUTTON);
        info.SetAction(MouseAction::RELEASE);
        Offset screenLocation;
        screenLocation.deltaX_ = 10.2;
        ContainerModalViewEnhance::sIsMenuPending_ = false;
        info.SetScreenLocation(screenLocation);
        for (auto item : gestures->inputEvents_) {
            (*item)(info);
        }
    }
}

/**
 * @tc.name: ContainerModalViewEnhanceTestNgTest015
 * @tc.desc: Test BondingMaxBtnInputEvent
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalViewEnhanceTestNg, ContainerModalViewEnhanceTestNgTest015, TestSize.Level1)
{
    CreateContainerModal();
    auto containerModalNode = FrameNode::CreateFrameNode("ContainerModal",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto controlButtonsRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto fameNode = viewEnhance_->AddControlButtons(containerModalNode, controlButtonsRow);
    if (fameNode) {
        SUCCEED();
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    auto WindownMode = []() -> WindowMode { return WindowMode::WINDOW_MODE_PIP; };
    auto windowManager = pipeline->GetWindowManager();
    windowManager->SetWindowGetModeCallBack(WindownMode);
    for (auto it : controlButtonsRow->children_) {
        auto buttonNode = AceType::DynamicCast<FrameNode>(it);
        auto gestures = buttonNode->GetOrCreateInputEventHub()->mouseEventActuator_;
        MouseInfo info;
        info.SetButton(MouseButton::LEFT_BUTTON);
        info.SetAction(MouseAction::RELEASE);
        Offset screenLocation;
        screenLocation.Zero();
        ContainerModalViewEnhance::sIsMenuPending_ = false;
        info.SetScreenLocation(screenLocation);
        for (auto item : gestures->inputEvents_) {
            (*item)(info);
        }
    }
}

/**
 * @tc.name: ContainerModalViewEnhanceTestNgTest016
 * @tc.desc: Test BondingMaxBtnInputEvent
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalViewEnhanceTestNg, ContainerModalViewEnhanceTestNgTest016, TestSize.Level1)
{
    CreateContainerModal();
    auto containerModalNode = FrameNode::CreateFrameNode("ContainerModal",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto controlButtonsRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto fameNode = viewEnhance_->AddControlButtons(containerModalNode, controlButtonsRow);
    auto pipeline = PipelineContext::GetCurrentContext();
    auto WindownMode = []() -> WindowMode { return WindowMode::WINDOW_MODE_PIP; };
    auto windowManager = pipeline->GetWindowManager();
    windowManager->SetWindowGetModeCallBack(WindownMode);
    for (auto it : controlButtonsRow->children_) {
        auto buttonNode = AceType::DynamicCast<FrameNode>(it);
        auto gestures = buttonNode->GetOrCreateInputEventHub()->mouseEventActuator_;
        MouseInfo info;
        info.SetButton(MouseButton::LEFT_BUTTON);
        info.SetAction(MouseAction::RELEASE);
        Offset screenLocation;
        screenLocation.Zero();
        ContainerModalViewEnhance::sIsMenuPending_ = true;
        info.SetScreenLocation(screenLocation);
        for (auto item : gestures->inputEvents_) {
            (*item)(info);
        }
    }
    SUCCEED();
}

/**
 * @tc.name: ContainerModalViewEnhanceTestNgTest017
 * @tc.desc: Test BondingMaxBtnInputEvent
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalViewEnhanceTestNg, ContainerModalViewEnhanceTestNgTest017, TestSize.Level1)
{
    CreateContainerModal();
    auto containerModalNode = FrameNode::CreateFrameNode("ContainerModal",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto controlButtonsRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto fameNode = viewEnhance_->AddControlButtons(containerModalNode, controlButtonsRow);
    for (auto it : controlButtonsRow->children_) {
        auto buttonNode = AceType::DynamicCast<FrameNode>(it);
        auto gestures = buttonNode->GetOrCreateInputEventHub()->hoverEventActuator_;
        bool hover = false;
        for (auto item : gestures->inputEvents_) {
            (*item)(hover);
        }
        hover = true;
        ContainerModalViewEnhance::sIsMenuPending_ = true;
        for (auto item : gestures->inputEvents_) {
            (*item)(hover);
        }
    }
    SUCCEED();
}

/**
 * @tc.name: ContainerModalViewEnhanceTestNgTest018
 * @tc.desc: Test BuildLeftSplitMenuItem
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalViewEnhanceTestNg, ContainerModalViewEnhanceTestNgTest018, TestSize.Level1)
{
    CreateContainerModal();
    auto frameNode = viewEnhance_->BuildLeftSplitMenuItem();
    if (frameNode) {
        SUCCEED();
    }
}

/**
 * @tc.name: ContainerModalViewEnhanceTestNgTest019
 * @tc.desc: Test BuildLeftSplitMenuItem
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalViewEnhanceTestNg, ContainerModalViewEnhanceTestNgTest019, TestSize.Level1)
{
    CreateContainerModal();
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->windowManager_ = nullptr;
    auto frameNode = viewEnhance_->BuildLeftSplitMenuItem();
    if (frameNode) {
        SUCCEED();
    }
}

/**
 * @tc.name: ContainerModalViewEnhanceTestNgTest020
 * @tc.desc: Test ShowMaxMenu
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalViewEnhanceTestNg, ContainerModalViewEnhanceTestNgTest020, TestSize.Level1)
{
    CreateContainerModal();
    MouseInfo info;
    auto menuPosX = info.GetScreenLocation().GetX() - info.GetLocalLocation().GetX() - MENU_FLOAT_X.ConvertToPx();
    auto menuPosY = info.GetScreenLocation().GetY() - info.GetLocalLocation().GetY() + MENU_FLOAT_Y.ConvertToPx();
    OffsetF menuPosition { menuPosX, menuPosY };
    viewEnhance_->CalculateMenuOffset(menuPosition);
    viewEnhance_->SetEnableSplit(false);
    auto menuList = FrameNode::CreateFrameNode(
        V2::LIST_COMPONENT_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ListPattern>());
    auto fameNode = viewEnhance_->ShowMaxMenu(menuList, menuPosition);
    EXPECT_EQ(fameNode, nullptr);
}

/**
 * @tc.name: ContainerModalViewEnhanceTestNgTest021
 * @tc.desc: Test ShowMaxMenu
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalViewEnhanceTestNg, ContainerModalViewEnhanceTestNgTest021, TestSize.Level1)
{
    CreateContainerModal();
    MouseInfo info;
    auto menuPosX = info.GetScreenLocation().GetX() - info.GetLocalLocation().GetX() - MENU_FLOAT_X.ConvertToPx();
    auto menuPosY = info.GetScreenLocation().GetY() - info.GetLocalLocation().GetY() + MENU_FLOAT_Y.ConvertToPx();
    OffsetF menuPosition { menuPosX, menuPosY };
    viewEnhance_->CalculateMenuOffset(menuPosition);
    viewEnhance_->SetEnableSplit(true);
    auto menuList = FrameNode::CreateFrameNode(
        V2::LIST_COMPONENT_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ListPattern>());
    auto fameNode = viewEnhance_->ShowMaxMenu(menuList, menuPosition);
}

/**
 * @tc.name: ContainerModalViewEnhanceTestNgTest022
 * @tc.desc: Test BuildRightSplitMenuItem
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalViewEnhanceTestNg, ContainerModalViewEnhanceTestNgTest022, TestSize.Level1)
{
    CreateContainerModal();
    auto frameNode = viewEnhance_->BuildRightSplitMenuItem();
    if (frameNode) {
        SUCCEED();
    }
}

/**
 * @tc.name: ContainerModalViewEnhanceTestNgTest023
 * @tc.desc: Test BuildRightSplitMenuItem
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalViewEnhanceTestNg, ContainerModalViewEnhanceTestNgTest023, TestSize.Level1)
{
    CreateContainerModal();
    auto frameNode = viewEnhance_->BuildRightSplitMenuItem();
    if (frameNode) {
        SUCCEED();
    }
}

/**
 * @tc.name: ContainerModalViewEnhanceTestNgTest024
 * @tc.desc: Test BondingMenuItemEvent
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalViewEnhanceTestNg, ContainerModalViewEnhanceTestNgTest024, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<ListItemTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    CreateContainerModal();
    auto leftIcon = viewEnhance_->BuildMenuItemIcon(InternalResource::ResourceId::IC_WINDOW_MENU_SCREEN_N);
    auto containerTitleRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    containerTitleRow->AddChild(leftIcon);
    auto titleLabel = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    PaddingProperty padding;
    padding.left = CalcLength(MENU_ITEM_TEXT_PADDING);
    auto text = viewEnhance_->BuildMenuItemPadding(padding, titleLabel);
    containerTitleRow->AddChild(text);
    viewEnhance_->BondingMenuItemEvent(containerTitleRow);
    auto events = containerTitleRow->GetOrCreateInputEventHub()->hoverEventActuator_->inputEvents_;
    auto mouse = containerTitleRow->GetOrCreateInputEventHub()->mouseEventActuator_->inputEvents_;
    bool ishover = true;
    for (auto it : events) {
        (*it)(ishover);
    }
    ishover = false;
    for (auto it : events) {
        (*it)(ishover);
    }
    MouseInfo info;
    info.SetAction(MouseAction::RELEASE);
    for (auto item : mouse) {
        (*item)(info);
    }
    info.SetAction(MouseAction::PRESS);
    for (auto item : mouse) {
        (*item)(info);
    }
    SUCCEED();
}

/**
 * @tc.name: ContainerModalViewEnhanceTestNgTest025
 * @tc.desc: Test BondingMenuItemEvent
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalViewEnhanceTestNg, ContainerModalViewEnhanceTestNgTest025, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<ListItemTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    CreateContainerModal();
    auto leftIcon = viewEnhance_->BuildMenuItemIcon(InternalResource::ResourceId::IC_WINDOW_MENU_SCREEN_N);
    auto containerTitleRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    containerTitleRow->AddChild(leftIcon);
    auto titleLabel = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    PaddingProperty padding;
    padding.left = CalcLength(MENU_ITEM_TEXT_PADDING);
    auto text = viewEnhance_->BuildMenuItemPadding(padding, titleLabel);
    containerTitleRow->AddChild(text);
    viewEnhance_->BondingMenuItemEvent(containerTitleRow);
    SUCCEED();
}

/**
 * @tc.name: ContainerModalViewEnhanceTestNgTest026
 * @tc.desc: Test BondingMenuItemEvent
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalViewEnhanceTestNg, ContainerModalViewEnhanceTestNgTest026, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<AdvancedPatternTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    CreateContainerModal();
    if (viewEnhance_->BuildMenuItemIcon(InternalResource::ResourceId::IC_WINDOW_MENU_SCREEN_N)) {
        SUCCEED();
    }
}

/**
 * @tc.name: ContainerModalViewEnhanceTestNgTest027
 * @tc.desc: Test BondingMenuItemEvent
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalViewEnhanceTestNg, ContainerModalViewEnhanceTestNgTest027, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<AdvancedPatternTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    CreateContainerModal();
    if (viewEnhance_->BuildMenuItemIcon(InternalResource::ResourceId::IC_WINDOW_MENU_SCREEN_N)) {
        SUCCEED();
    }
}

/**
 * @tc.name: ContainerModalViewEnhanceTestNgTest028
 * @tc.desc: Test BondingMenuItemEvent
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalViewEnhanceTestNg, ContainerModalViewEnhanceTestNgTest028, TestSize.Level1)
{
    CreateContainerModal();
    auto titleLabel = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    PaddingProperty padding;
    padding.left = CalcLength(MENU_ITEM_TEXT_PADDING);
    if (viewEnhance_->BuildMenuItemPadding(padding, titleLabel)) {
        SUCCEED();
    }
}

/**
 * @tc.name: ContainerModalViewEnhanceTestNgTest029
 * @tc.desc: Test ResetHoverTimer
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalViewEnhanceTestNg, ContainerModalViewEnhanceTestNgTest029, TestSize.Level1)
{
    CreateContainerModal();
    viewEnhance_->ResetHoverTimer();
    SUCCEED();
}

/**
 * @tc.name: ContainerModalViewEnhanceTestNgTest030
 * @tc.desc: Test ResetHoverTimer
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalViewEnhanceTestNg, ContainerModalViewEnhanceTestNgTest030, TestSize.Level1)
{
    CreateContainerModal();
    OffsetF currentOffset;
    currentOffset.SetX(0.0);
    currentOffset.SetY(0.0);
    viewEnhance_->CalculateMenuOffset(currentOffset);
    SUCCEED();
    currentOffset.SetX(100.0);
    currentOffset.SetY(100.0);
    viewEnhance_->CalculateMenuOffset(currentOffset);
    SUCCEED();
    currentOffset.SetX(-2000.0);
    currentOffset.SetY(-200.0);
    viewEnhance_->CalculateMenuOffset(currentOffset);
    SUCCEED();
}

/**
 * @tc.name: ContainerModalViewEnhanceTestNgTest031
 * @tc.desc: Test ResetHoverTimer
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalViewEnhanceTestNg, ContainerModalViewEnhanceTestNgTest031, TestSize.Level1)
{
    CreateContainerModal();
    auto containerModalNode = FrameNode::CreateFrameNode("ContainerModal",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    if (viewEnhance_->BuildGestureRow(containerModalNode)) {
        SUCCEED();
    }
}
} // namespace OHOS::Ace::NG
