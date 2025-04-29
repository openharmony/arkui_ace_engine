/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
#include "test/mock/base/mock_drag_window.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_interaction_interface.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/image/pixel_map.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/subwindow/subwindow_manager.h"
#include "core/common/interaction/interaction_interface.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/manager/drag_drop/drag_drop_manager.h"
#include "core/components_ng/manager/drag_drop/drag_drop_proxy.h"
#include "core/components_ng/pattern/grid/grid_event_hub.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/components_ng/pattern/list/list_event_hub.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/render_node.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string NODE_TAG("custom_node");
const std::string EXTRA_INFO("extra info");
constexpr int32_t GLOBAL_1 = 1;
constexpr int32_t GLOBAL_2 = 2;
constexpr int32_t GLOBAL_3 = 3;
RefPtr<DragWindow> MOCK_DRAG_WINDOW;
} // namespace

class DragDropReportTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void DragDropReportTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MOCK_DRAG_WINDOW = DragWindow::CreateDragWindow("", 0, 0, 0, 0);
}

void DragDropReportTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
    MOCK_DRAG_WINDOW = nullptr;
}

/**
 * @tc.name: DragDropReportTest001
 * @tc.desc: Test DragEventStrictReportingEnabled
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropReportTestNg, DragDropReportTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. ReportingEnable is not set.
     * @tc.expected: reportingEnabledDefault is false.
     */
    bool reportingEnabledDefault = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledDefault);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_1, GLOBAL_1 }, frameNode);
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_1, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledDefault);
    preTargetNode.Reset();
    frameNode.Reset();

    /**
     * @tc.steps: step3. ReportingSupported is set to true.
     * @tc.expected: reportingEnabledTrue is true.
     */
    bool variableTrue = true;
    dragDropManager->SetEventStrictReportingEnabled(variableTrue);
    bool reportingEnabledTrue = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_TRUE(reportingEnabledTrue);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_1, GLOBAL_1 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_1, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_TRUE(reportingEnabledTrue);
    preTargetNode.Reset();
    frameNode.Reset();
    
    /**
     * @tc.steps: step4. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    bool variableFalse = false;
    dragDropManager->SetEventStrictReportingEnabled(variableFalse);
    bool reportingEnabledFalse = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledFalse);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_1, GLOBAL_1 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_1, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledFalse);
}

/**
 * @tc.name: DragDropReportTest002
 * @tc.desc: Test DragEventStrictReportingEnabled
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropReportTestNg, DragDropReportTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. ReportingEnable is not set.
     * @tc.expected: reportingEnabledDefault is false.
     */
    bool reportingEnabledDefault = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledDefault);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_2, GLOBAL_2 }, frameNode);
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_1, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledDefault);
    preTargetNode.Reset();
    frameNode.Reset();

    /**
     * @tc.steps: step3. ReportingSupported is set to true.
     * @tc.expected: reportingEnabledTrue is true.
     */
    bool variableTrue = true;
    dragDropManager->SetEventStrictReportingEnabled(variableTrue);
    bool reportingEnabledTrue = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_TRUE(reportingEnabledTrue);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_2, GLOBAL_2 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_1, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_TRUE(reportingEnabledTrue);
    preTargetNode.Reset();
    frameNode.Reset();
    
    /**
     * @tc.steps: step4. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    bool variableFalse = false;
    dragDropManager->SetEventStrictReportingEnabled(variableFalse);
    bool reportingEnabledFalse = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledFalse);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_2, GLOBAL_2 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_1, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledFalse);
}

/**
 * @tc.name: DragDropReportTest003
 * @tc.desc: Test DragEventStrictReportingEnabled
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropReportTestNg, DragDropReportTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. ReportingEnable is not set.
     * @tc.expected: reportingEnabledDefault is false.
     */
    bool reportingEnabledDefault = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledDefault);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_1, GLOBAL_1 }, frameNode);
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_2, GLOBAL_2 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledDefault);
    preTargetNode.Reset();
    frameNode.Reset();

    /**
     * @tc.steps: step3. ReportingSupported is set to true.
     * @tc.expected: reportingEnabledTrue is true.
     */
    bool variableTrue = true;
    dragDropManager->SetEventStrictReportingEnabled(variableTrue);
    bool reportingEnabledTrue = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_TRUE(reportingEnabledTrue);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_1, GLOBAL_1 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_2, GLOBAL_2 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_TRUE(reportingEnabledTrue);
    preTargetNode.Reset();
    frameNode.Reset();
    
    /**
     * @tc.steps: step4. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    bool variableFalse = false;
    dragDropManager->SetEventStrictReportingEnabled(variableFalse);
    bool reportingEnabledFalse = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledFalse);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_1, GLOBAL_1 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_2, GLOBAL_2 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledFalse);
}

/**
 * @tc.name: DragDropReportTest004
 * @tc.desc: Test DragEventStrictReportingEnabled
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropReportTestNg, DragDropReportTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. ReportingEnable is not set.
     * @tc.expected: reportingEnabledDefault is false.
     */
    bool reportingEnabledDefault = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledDefault);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_2, GLOBAL_2 }, frameNode);
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_2, GLOBAL_2 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledDefault);
    preTargetNode.Reset();
    frameNode.Reset();

    /**
     * @tc.steps: step3. ReportingSupported is set to true.
     * @tc.expected: reportingEnabledTrue is true.
     */
    bool variableTrue = true;
    dragDropManager->SetEventStrictReportingEnabled(variableTrue);
    bool reportingEnabledTrue = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_TRUE(reportingEnabledTrue);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_2, GLOBAL_2 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_2, GLOBAL_2 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_TRUE(reportingEnabledTrue);
    preTargetNode.Reset();
    frameNode.Reset();
    
    /**
     * @tc.steps: step4. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    bool variableFalse = false;
    dragDropManager->SetEventStrictReportingEnabled(variableFalse);
    bool reportingEnabledFalse = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledFalse);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_2, GLOBAL_2 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_2, GLOBAL_2 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledFalse);
}

/**
 * @tc.name: DragDropReportTest005
 * @tc.desc: Test DragEventStrictReportingEnabled
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropReportTestNg, DragDropReportTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. ReportingEnable is not set.
     * @tc.expected: reportingEnabledDefault is false.
     */
    bool reportingEnabledDefault = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledDefault);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_3 }, frameNode);
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_1, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledDefault);
    preTargetNode.Reset();
    frameNode.Reset();

    /**
     * @tc.steps: step3. ReportingSupported is set to true.
     * @tc.expected: reportingEnabledTrue is true.
     */
    bool variableTrue = true;
    dragDropManager->SetEventStrictReportingEnabled(variableTrue);
    bool reportingEnabledTrue = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_TRUE(reportingEnabledTrue);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_3 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_1, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_TRUE(reportingEnabledTrue);
    preTargetNode.Reset();
    frameNode.Reset();
    
    /**
     * @tc.steps: step4. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    bool variableFalse = false;
    dragDropManager->SetEventStrictReportingEnabled(variableFalse);
    bool reportingEnabledFalse = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledFalse);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_3 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_1, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledFalse);
}

/**
 * @tc.name: DragDropReportTest006
 * @tc.desc: Test DragEventStrictReportingEnabled
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropReportTestNg, DragDropReportTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. ReportingEnable is not set.
     * @tc.expected: reportingEnabledDefault is false.
     */
    bool reportingEnabledDefault = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledDefault);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_3 }, frameNode);
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_2, GLOBAL_2 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledDefault);
    preTargetNode.Reset();
    frameNode.Reset();

    /**
     * @tc.steps: step3. ReportingSupported is set to true.
     * @tc.expected: reportingEnabledTrue is true.
     */
    bool variableTrue = true;
    dragDropManager->SetEventStrictReportingEnabled(variableTrue);
    bool reportingEnabledTrue = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_TRUE(reportingEnabledTrue);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_3 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_2, GLOBAL_2 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_TRUE(reportingEnabledTrue);
    preTargetNode.Reset();
    frameNode.Reset();
    
    /**
     * @tc.steps: step4. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    bool variableFalse = false;
    dragDropManager->SetEventStrictReportingEnabled(variableFalse);
    bool reportingEnabledFalse = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledFalse);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_3 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_2, GLOBAL_2 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledFalse);
}

/**
 * @tc.name: DragDropReportTest007
 * @tc.desc: Test DragEventStrictReportingEnabled
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropReportTestNg, DragDropReportTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. ReportingEnable is not set.
     * @tc.expected: reportingEnabledDefault is false.
     */
    bool reportingEnabledDefault = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledDefault);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_3 }, frameNode);
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_3, GLOBAL_3 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledDefault);
    preTargetNode.Reset();
    frameNode.Reset();

    /**
     * @tc.steps: step3. ReportingSupported is set to true.
     * @tc.expected: reportingEnabledTrue is true.
     */
    bool variableTrue = true;
    dragDropManager->SetEventStrictReportingEnabled(variableTrue);
    bool reportingEnabledTrue = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_TRUE(reportingEnabledTrue);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_3 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_3, GLOBAL_3 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_TRUE(reportingEnabledTrue);
    preTargetNode.Reset();
    frameNode.Reset();
    
    /**
     * @tc.steps: step4. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    bool variableFalse = false;
    dragDropManager->SetEventStrictReportingEnabled(variableFalse);
    bool reportingEnabledFalse = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledFalse);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_3 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_3, GLOBAL_3 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledFalse);
}

/**
 * @tc.name: DragDropReportTest008
 * @tc.desc: Test DragEventStrictReportingEnabled
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropReportTestNg, DragDropReportTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. ReportingEnable is not set.
     * @tc.expected: reportingEnabledDefault is false.
     */
    bool reportingEnabledDefault = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledDefault);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_1, GLOBAL_1 }, frameNode);
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_3, GLOBAL_3 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledDefault);
    preTargetNode.Reset();
    frameNode.Reset();

    /**
     * @tc.steps: step3. ReportingSupported is set to true.
     * @tc.expected: reportingEnabledTrue is true.
     */
    bool variableTrue = true;
    dragDropManager->SetEventStrictReportingEnabled(variableTrue);
    bool reportingEnabledTrue = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_TRUE(reportingEnabledTrue);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_1, GLOBAL_1 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_3, GLOBAL_3 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_TRUE(reportingEnabledTrue);
    preTargetNode.Reset();
    frameNode.Reset();
    
    /**
     * @tc.steps: step4. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    bool variableFalse = false;
    dragDropManager->SetEventStrictReportingEnabled(variableFalse);
    bool reportingEnabledFalse = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledFalse);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_1, GLOBAL_1 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_3, GLOBAL_3 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledFalse);
}

/**
 * @tc.name: DragDropReportTest009
 * @tc.desc: Test DragEventStrictReportingEnabled
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropReportTestNg, DragDropReportTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. ReportingEnable is not set.
     * @tc.expected: reportingEnabledDefault is false.
     */
    bool reportingEnabledDefault = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledDefault);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_2, GLOBAL_2 }, frameNode);
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_3, GLOBAL_3 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledDefault);
    preTargetNode.Reset();
    frameNode.Reset();

    /**
     * @tc.steps: step3. ReportingSupported is set to true.
     * @tc.expected: reportingEnabledTrue is true.
     */
    bool variableTrue = true;
    dragDropManager->SetEventStrictReportingEnabled(variableTrue);
    bool reportingEnabledTrue = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_TRUE(reportingEnabledTrue);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_2, GLOBAL_2 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_3, GLOBAL_3 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_TRUE(reportingEnabledTrue);
    preTargetNode.Reset();
    frameNode.Reset();
    
    /**
     * @tc.steps: step4. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    bool variableFalse = false;
    dragDropManager->SetEventStrictReportingEnabled(variableFalse);
    bool reportingEnabledFalse = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledFalse);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_2, GLOBAL_2 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_3, GLOBAL_3 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledFalse);
}

/**
 * @tc.name: DragDropReportTest010
 * @tc.desc: Test DragEventStrictReportingEnabled
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropReportTestNg, DragDropReportTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. ReportingEnable is not set.
     * @tc.expected: reportingEnabledDefault is false.
     */
    bool reportingEnabledDefault = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledDefault);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_1, GLOBAL_2 }, frameNode);
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_1, GLOBAL_2 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledDefault);
    preTargetNode.Reset();
    frameNode.Reset();

    /**
     * @tc.steps: step3. ReportingSupported is set to true.
     * @tc.expected: reportingEnabledTrue is true.
     */
    bool variableTrue = true;
    dragDropManager->SetEventStrictReportingEnabled(variableTrue);
    bool reportingEnabledTrue = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_TRUE(reportingEnabledTrue);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_1, GLOBAL_2 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_1, GLOBAL_2 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_TRUE(reportingEnabledTrue);
    preTargetNode.Reset();
    frameNode.Reset();

    /**
     * @tc.steps: step4. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    bool variableFalse = false;
    dragDropManager->SetEventStrictReportingEnabled(variableFalse);
    bool reportingEnabledFalse = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledFalse);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_1, GLOBAL_2 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_1, GLOBAL_2 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledFalse);
}

/**
 * @tc.name: DragDropReportTest011
 * @tc.desc: Test DragEventStrictReportingEnabled
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropReportTestNg, DragDropReportTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. ReportingEnable is not set.
     * @tc.expected: reportingEnabledDefault is false.
     */
    bool reportingEnabledDefault = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledDefault);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_1, GLOBAL_3 }, frameNode);
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_1, GLOBAL_2 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledDefault);
    preTargetNode.Reset();
    frameNode.Reset();

    /**
     * @tc.steps: step3. ReportingSupported is set to true.
     * @tc.expected: reportingEnabledTrue is true.
     */
    bool variableTrue = true;
    dragDropManager->SetEventStrictReportingEnabled(variableTrue);
    bool reportingEnabledTrue = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_TRUE(reportingEnabledTrue);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_1, GLOBAL_3 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_1, GLOBAL_2 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_TRUE(reportingEnabledTrue);
    preTargetNode.Reset();
    frameNode.Reset();
    
    /**
     * @tc.steps: step4. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    bool variableFalse = false;
    dragDropManager->SetEventStrictReportingEnabled(variableFalse);
    bool reportingEnabledFalse = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledFalse);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_1, GLOBAL_3 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_1, GLOBAL_2 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledFalse);
}

/**
 * @tc.name: DragDropReportTest012
 * @tc.desc: Test DragEventStrictReportingEnabled
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropReportTestNg, DragDropReportTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. ReportingEnable is not set.
     * @tc.expected: reportingEnabledDefault is false.
     */
    bool reportingEnabledDefault = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledDefault);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_1, GLOBAL_2 }, frameNode);
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_1, GLOBAL_3 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledDefault);
    preTargetNode.Reset();
    frameNode.Reset();

    /**
     * @tc.steps: step3. ReportingSupported is set to true.
     * @tc.expected: reportingEnabledTrue is true.
     */
    bool variableTrue = true;
    dragDropManager->SetEventStrictReportingEnabled(variableTrue);
    bool reportingEnabledTrue = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_TRUE(reportingEnabledTrue);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_1, GLOBAL_2 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_1, GLOBAL_3 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_TRUE(reportingEnabledTrue);
    preTargetNode.Reset();
    frameNode.Reset();
    
    /**
     * @tc.steps: step4. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    bool variableFalse = false;
    dragDropManager->SetEventStrictReportingEnabled(variableFalse);
    bool reportingEnabledFalse = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledFalse);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_1, GLOBAL_2 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_1, GLOBAL_3 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledFalse);
}

/**
 * @tc.name: DragDropReportTest013
 * @tc.desc: Test DragEventStrictReportingEnabled
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropReportTestNg, DragDropReportTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. ReportingEnable is not set.
     * @tc.expected: reportingEnabledDefault is false.
     */
    bool reportingEnabledDefault = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledDefault);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_2, GLOBAL_1 }, frameNode);
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_1, GLOBAL_3 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledDefault);
    preTargetNode.Reset();
    frameNode.Reset();

    /**
     * @tc.steps: step3. ReportingSupported is set to true.
     * @tc.expected: reportingEnabledTrue is true.
     */
    bool variableTrue = true;
    dragDropManager->SetEventStrictReportingEnabled(variableTrue);
    bool reportingEnabledTrue = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_TRUE(reportingEnabledTrue);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_2, GLOBAL_1 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_1, GLOBAL_3 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_TRUE(reportingEnabledTrue);
    preTargetNode.Reset();
    frameNode.Reset();
    
    /**
     * @tc.steps: step4. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    bool variableFalse = false;
    dragDropManager->SetEventStrictReportingEnabled(variableFalse);
    bool reportingEnabledFalse = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledFalse);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_2, GLOBAL_1 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_1, GLOBAL_3 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledFalse);
}

/**
 * @tc.name: DragDropReportTest014
 * @tc.desc: Test DragEventStrictReportingEnabled
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropReportTestNg, DragDropReportTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. ReportingEnable is not set.
     * @tc.expected: reportingEnabledDefault is false.
     */
    bool reportingEnabledDefault = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledDefault);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_2, GLOBAL_2 }, frameNode);
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_3, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledDefault);
    preTargetNode.Reset();
    frameNode.Reset();

    /**
     * @tc.steps: step3. ReportingSupported is set to true.
     * @tc.expected: reportingEnabledTrue is true.
     */
    bool variableTrue = true;
    dragDropManager->SetEventStrictReportingEnabled(variableTrue);
    bool reportingEnabledTrue = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_TRUE(reportingEnabledTrue);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_2, GLOBAL_2 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_3, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_TRUE(reportingEnabledTrue);
    preTargetNode.Reset();
    frameNode.Reset();
    
    /**
     * @tc.steps: step4. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    bool variableFalse = false;
    dragDropManager->SetEventStrictReportingEnabled(variableFalse);
    bool reportingEnabledFalse = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledFalse);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_2, GLOBAL_2 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_3, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledFalse);
}

/**
 * @tc.name: DragDropReportTest015
 * @tc.desc: Test DragEventStrictReportingEnabled
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropReportTestNg, DragDropReportTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. ReportingEnable is not set.
     * @tc.expected: reportingEnabledDefault is false.
     */
    bool reportingEnabledDefault = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledDefault);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_2, GLOBAL_3 }, frameNode);
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_3, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledDefault);
    preTargetNode.Reset();
    frameNode.Reset();

    /**
     * @tc.steps: step3. ReportingSupported is set to true.
     * @tc.expected: reportingEnabledTrue is true.
     */
    bool variableTrue = true;
    dragDropManager->SetEventStrictReportingEnabled(variableTrue);
    bool reportingEnabledTrue = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_TRUE(reportingEnabledTrue);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_2, GLOBAL_3 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_3, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_TRUE(reportingEnabledTrue);
    preTargetNode.Reset();
    frameNode.Reset();
    
    /**
     * @tc.steps: step4. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    bool variableFalse = false;
    dragDropManager->SetEventStrictReportingEnabled(variableFalse);
    bool reportingEnabledFalse = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledFalse);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_2, GLOBAL_3 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_3, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledFalse);
}

/**
 * @tc.name: DragDropReportTest016
 * @tc.desc: Test DragEventStrictReportingEnabled
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropReportTestNg, DragDropReportTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. ReportingEnable is not set.
     * @tc.expected: reportingEnabledDefault is false.
     */
    bool reportingEnabledDefault = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledDefault);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_1, GLOBAL_3 }, frameNode);
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_2, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledDefault);
    preTargetNode.Reset();
    frameNode.Reset();

    /**
     * @tc.steps: step3. ReportingSupported is set to true.
     * @tc.expected: reportingEnabledTrue is true.
     */
    bool variableTrue = true;
    dragDropManager->SetEventStrictReportingEnabled(variableTrue);
    bool reportingEnabledTrue = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_TRUE(reportingEnabledTrue);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_1, GLOBAL_3 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_2, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_TRUE(reportingEnabledTrue);
    preTargetNode.Reset();
    frameNode.Reset();
    
    /**
     * @tc.steps: step4. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    bool variableFalse = false;
    dragDropManager->SetEventStrictReportingEnabled(variableFalse);
    bool reportingEnabledFalse = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledFalse);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_1, GLOBAL_3 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_2, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledFalse);
}

/**
 * @tc.name: DragDropReportTest017
 * @tc.desc: Test DragEventStrictReportingEnabled
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropReportTestNg, DragDropReportTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. ReportingEnable is not set.
     * @tc.expected: reportingEnabledDefault is false.
     */
    bool reportingEnabledDefault = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledDefault);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_2, GLOBAL_1 }, frameNode);
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_3, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledDefault);
    preTargetNode.Reset();
    frameNode.Reset();

    /**
     * @tc.steps: step3. ReportingSupported is set to true.
     * @tc.expected: reportingEnabledTrue is true.
     */
    bool variableTrue = true;
    dragDropManager->SetEventStrictReportingEnabled(variableTrue);
    bool reportingEnabledTrue = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_TRUE(reportingEnabledTrue);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_2, GLOBAL_1 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_3, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_TRUE(reportingEnabledTrue);
    preTargetNode.Reset();
    frameNode.Reset();
    
    /**
     * @tc.steps: step4. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    bool variableFalse = false;
    dragDropManager->SetEventStrictReportingEnabled(variableFalse);
    bool reportingEnabledFalse = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledFalse);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_2, GLOBAL_1 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_3, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledFalse);
    preTargetNode.Reset();
    frameNode.Reset();
}

/**
 * @tc.name: DragDropReportTest018
 * @tc.desc: Test DragEventStrictReportingEnabled
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropReportTestNg, DragDropReportTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. ReportingEnable is not set.
     * @tc.expected: reportingEnabledDefault is false.
     */
    bool reportingEnabledDefault = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledDefault);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_1 }, frameNode);
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_1, GLOBAL_2 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledDefault);
    preTargetNode.Reset();
    frameNode.Reset();

    /**
     * @tc.steps: step3. ReportingSupported is set to true.
     * @tc.expected: reportingEnabledTrue is true.
     */
    bool variableTrue = true;
    dragDropManager->SetEventStrictReportingEnabled(variableTrue);
    bool reportingEnabledTrue = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_TRUE(reportingEnabledTrue);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_1 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_1, GLOBAL_2 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_TRUE(reportingEnabledTrue);
    preTargetNode.Reset();
    frameNode.Reset();
    
    /**
     * @tc.steps: step4. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    bool variableFalse = false;
    dragDropManager->SetEventStrictReportingEnabled(variableFalse);
    bool reportingEnabledFalse = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledFalse);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_1 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_1, GLOBAL_2 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledFalse);
}

/**
 * @tc.name: DragDropReportTest019
 * @tc.desc: Test DragEventStrictReportingEnabled
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropReportTestNg, DragDropReportTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. ReportingEnable is not set.
     * @tc.expected: reportingEnabledDefault is false.
     */
    bool reportingEnabledDefault = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledDefault);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_2 }, frameNode);
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_1, GLOBAL_3 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledDefault);
    preTargetNode.Reset();
    frameNode.Reset();

    /**
     * @tc.steps: step3. ReportingSupported is set to true.
     * @tc.expected: reportingEnabledTrue is true.
     */
    bool variableTrue = true;
    dragDropManager->SetEventStrictReportingEnabled(variableTrue);
    bool reportingEnabledTrue = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_TRUE(reportingEnabledTrue);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_2 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_1, GLOBAL_3 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_TRUE(reportingEnabledTrue);
    preTargetNode.Reset();
    frameNode.Reset();
    
    /**
     * @tc.steps: step4. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    bool variableFalse = false;
    dragDropManager->SetEventStrictReportingEnabled(variableFalse);
    bool reportingEnabledFalse = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledFalse);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_2 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_1, GLOBAL_3 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledFalse);
}

/**
 * @tc.name: DragDropReportTest020
 * @tc.desc: Test DragEventStrictReportingEnabled
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropReportTestNg, DragDropReportTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. ReportingEnable is not set.
     * @tc.expected: reportingEnabledDefault is false.
     */
    bool reportingEnabledDefault = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledDefault);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_2, GLOBAL_1 }, frameNode);
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_2, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledDefault);
    preTargetNode.Reset();
    frameNode.Reset();

    /**
     * @tc.steps: step3. ReportingSupported is set to true.
     * @tc.expected: reportingEnabledTrue is true.
     */
    bool variableTrue = true;
    dragDropManager->SetEventStrictReportingEnabled(variableTrue);
    bool reportingEnabledTrue = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_TRUE(reportingEnabledTrue);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_2, GLOBAL_1 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_2, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_TRUE(reportingEnabledTrue);
    preTargetNode.Reset();
    frameNode.Reset();
    
    /**
     * @tc.steps: step4. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    bool variableFalse = false;
    dragDropManager->SetEventStrictReportingEnabled(variableFalse);
    bool reportingEnabledFalse = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledFalse);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_2, GLOBAL_1 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_2, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledFalse);
}

/**
 * @tc.name: DragDropReportTest021
 * @tc.desc: Test DragEventStrictReportingEnabled
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropReportTestNg, DragDropReportTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. ReportingEnable is not set.
     * @tc.expected: reportingEnabledDefault is false.
     */
    bool reportingEnabledDefault = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledDefault);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_1, GLOBAL_2 }, frameNode);
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_2, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledDefault);
    preTargetNode.Reset();
    frameNode.Reset();

    /**
     * @tc.steps: step3. ReportingSupported is set to true.
     * @tc.expected: reportingEnabledTrue is true.
     */
    bool variableTrue = true;
    dragDropManager->SetEventStrictReportingEnabled(variableTrue);
    bool reportingEnabledTrue = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_TRUE(reportingEnabledTrue);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_1, GLOBAL_2 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_2, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_TRUE(reportingEnabledTrue);
    preTargetNode.Reset();
    frameNode.Reset();
    
    /**
     * @tc.steps: step4. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    bool variableFalse = false;
    dragDropManager->SetEventStrictReportingEnabled(variableFalse);
    bool reportingEnabledFalse = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledFalse);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_1, GLOBAL_2 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_2, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledFalse);
}

/**
 * @tc.name: DragDropReportTest022
 * @tc.desc: Test DragEventStrictReportingEnabled
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropReportTestNg, DragDropReportTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. ReportingEnable is not set.
     * @tc.expected: reportingEnabledDefault is false.
     */
    bool reportingEnabledDefault = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledDefault);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_1 }, frameNode);
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_2, GLOBAL_3 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledDefault);
    preTargetNode.Reset();
    frameNode.Reset();

    /**
     * @tc.steps: step3. ReportingSupported is set to true.
     * @tc.expected: reportingEnabledTrue is true.
     */
    bool variableTrue = true;
    dragDropManager->SetEventStrictReportingEnabled(variableTrue);
    bool reportingEnabledTrue = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_TRUE(reportingEnabledTrue);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_1 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_2, GLOBAL_3 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_TRUE(reportingEnabledTrue);
    preTargetNode.Reset();
    frameNode.Reset();
    
    /**
     * @tc.steps: step4. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    bool variableFalse = false;
    dragDropManager->SetEventStrictReportingEnabled(variableFalse);
    bool reportingEnabledFalse = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledFalse);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_1 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_2, GLOBAL_3 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledFalse);
}

/**
 * @tc.name: DragDropReportTest023
 * @tc.desc: Test DragEventStrictReportingEnabled
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropReportTestNg, DragDropReportTest023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. ReportingEnable is not set.
     * @tc.expected: reportingEnabledDefault is false.
     */
    bool reportingEnabledDefault = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledDefault);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_1, GLOBAL_2 }, frameNode);
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_3, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledDefault);
    preTargetNode.Reset();
    frameNode.Reset();

    /**
     * @tc.steps: step3. ReportingSupported is set to true.
     * @tc.expected: reportingEnabledTrue is true.
     */
    bool variableTrue = true;
    ASSERT_TRUE(variableTrue);
    dragDropManager->SetEventStrictReportingEnabled(variableTrue);
    bool reportingEnabledTrue = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_TRUE(reportingEnabledTrue);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_1, GLOBAL_2 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_3, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_TRUE(reportingEnabledTrue);
    preTargetNode.Reset();
    frameNode.Reset();
    
    /**
     * @tc.steps: step4. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    bool variableFalse = false;
    ASSERT_FALSE(variableFalse);
    dragDropManager->SetEventStrictReportingEnabled(variableFalse);
    bool reportingEnabledFalse = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledFalse);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_1, GLOBAL_2 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_3, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledFalse);
}

/**
 * @tc.name: DragDropReportTest024
 * @tc.desc: Test DragEventStrictReportingEnabled
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropReportTestNg, DragDropReportTest024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. ReportingEnable is not set.
     * @tc.expected: reportingEnabledDefault is false.
     */
    bool reportingEnabledDefault = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledDefault);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_2 }, frameNode);
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_3, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledDefault);
    preTargetNode.Reset();
    frameNode.Reset();

    /**
     * @tc.steps: step3. ReportingSupported is set to true.
     * @tc.expected: reportingEnabledTrue is true.
     */
    bool variableTrue = true;
    dragDropManager->SetEventStrictReportingEnabled(variableTrue);
    bool reportingEnabledTrue = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_TRUE(reportingEnabledTrue);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_2 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_3, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_TRUE(reportingEnabledTrue);
    preTargetNode.Reset();
    frameNode.Reset();
    
    /**
     * @tc.steps: step4. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    bool variableFalse = false;
    dragDropManager->SetEventStrictReportingEnabled(variableFalse);
    bool reportingEnabledFalse = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledFalse);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_2 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_3, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledFalse);
}

/**
 * @tc.name: DragDropReportTest025
 * @tc.desc: Test DragEventStrictReportingEnabled
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropReportTestNg, DragDropReportTest025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. ReportingEnable is not set.
     * @tc.expected: reportingEnabledDefault is false.
     */
    bool reportingEnabledDefault = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledDefault);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_1, GLOBAL_3 }, frameNode);
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_3, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledDefault);
    preTargetNode.Reset();
    frameNode.Reset();

    /**
     * @tc.steps: step3. ReportingSupported is set to true.
     * @tc.expected: reportingEnabledTrue is true.
     */
    bool variableTrue = true;
    dragDropManager->SetEventStrictReportingEnabled(variableTrue);
    bool reportingEnabledTrue = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_TRUE(reportingEnabledTrue);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_1, GLOBAL_3 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_3, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_TRUE(reportingEnabledTrue);
    preTargetNode.Reset();
    frameNode.Reset();
    
    /**
     * @tc.steps: step4. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    bool variableFalse = false;
    dragDropManager->SetEventStrictReportingEnabled(variableFalse);
    bool reportingEnabledFalse = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledFalse);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_1, GLOBAL_3 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_3, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledFalse);
}

/**
 * @tc.name: DragDropReportTest026
 * @tc.desc: Test DragEventStrictReportingEnabled
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropReportTestNg, DragDropReportTest026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. ReportingEnable is not set.
     * @tc.expected: reportingEnabledDefault is false.
     */
    bool reportingEnabledDefault = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledDefault);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_2 }, frameNode);
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_3, GLOBAL_3 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledDefault);
    preTargetNode.Reset();
    frameNode.Reset();

    /**
     * @tc.steps: step3. ReportingSupported is set to true.
     * @tc.expected: reportingEnabledTrue is true.
     */
    bool variableTrue = true;
    dragDropManager->SetEventStrictReportingEnabled(variableTrue);
    bool reportingEnabledTrue = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_TRUE(reportingEnabledTrue);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_2 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_3, GLOBAL_3 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_TRUE(reportingEnabledTrue);
    preTargetNode.Reset();
    frameNode.Reset();
    
    /**
     * @tc.steps: step4. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    bool variableFalse = false;
    dragDropManager->SetEventStrictReportingEnabled(variableFalse);
    bool reportingEnabledFalse = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledFalse);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_2 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_3, GLOBAL_3 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledFalse);
}

/**
 * @tc.name: DragDropReportTest027
 * @tc.desc: Test DragEventStrictReportingEnabled
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropReportTestNg, DragDropReportTest027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. ReportingEnable is not set.
     * @tc.expected: reportingEnabledDefault is false.
     */
    bool reportingEnabledDefault = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledDefault);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_2 }, frameNode);
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_1, GLOBAL_2 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledDefault);
    preTargetNode.Reset();
    frameNode.Reset();

    /**
     * @tc.steps: step3. ReportingSupported is set to true.
     * @tc.expected: reportingEnabledTrue is true.
     */
    bool variableTrue = true;
    dragDropManager->SetEventStrictReportingEnabled(variableTrue);
    bool reportingEnabledTrue = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_TRUE(reportingEnabledTrue);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_2 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_1, GLOBAL_2 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_TRUE(reportingEnabledTrue);
    preTargetNode.Reset();
    frameNode.Reset();
    
    /**
     * @tc.steps: step4. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    bool variableFalse = false;
    dragDropManager->SetEventStrictReportingEnabled(variableFalse);
    bool reportingEnabledFalse = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledFalse);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_2 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_1, GLOBAL_2 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledFalse);
}

/**
 * @tc.name: DragDropReportTest028
 * @tc.desc: Test DragEventStrictReportingEnabled
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropReportTestNg, DragDropReportTest028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. ReportingEnable is not set.
     * @tc.expected: reportingEnabledDefault is false.
     */
    bool reportingEnabledDefault = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledDefault);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_1, GLOBAL_2 }, frameNode);
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_3, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledDefault);
    preTargetNode.Reset();
    frameNode.Reset();

    /**
     * @tc.steps: step3. ReportingSupported is set to true.
     * @tc.expected: reportingEnabledTrue is true.
     */
    bool variableTrue = true;
    dragDropManager->SetEventStrictReportingEnabled(variableTrue);
    bool reportingEnabledTrue = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_TRUE(reportingEnabledTrue);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_1, GLOBAL_2 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_3, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_TRUE(reportingEnabledTrue);
    preTargetNode.Reset();
    frameNode.Reset();
    
    /**
     * @tc.steps: step4. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    bool variableFalse = false;
    dragDropManager->SetEventStrictReportingEnabled(variableFalse);
    bool reportingEnabledFalse = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledFalse);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_1, GLOBAL_2 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_3, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledFalse);
}

/**
 * @tc.name: DragDropReportTest029
 * @tc.desc: Test DragEventStrictReportingEnabled
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropReportTestNg, DragDropReportTest029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. ReportingEnable is not set.
     * @tc.expected: reportingEnabledDefault is false.
     */
    bool reportingEnabledDefault = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledDefault);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_1, GLOBAL_1 }, frameNode);
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_2, GLOBAL_3 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledDefault);
    preTargetNode.Reset();
    frameNode.Reset();

    /**
     * @tc.steps: step3. ReportingSupported is set to true.
     * @tc.expected: reportingEnabledTrue is true.
     */
    bool variableTrue = true;
    dragDropManager->SetEventStrictReportingEnabled(variableTrue);
    bool reportingEnabledTrue = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_TRUE(reportingEnabledTrue);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_1, GLOBAL_1 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_2, GLOBAL_3 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_TRUE(reportingEnabledTrue);
    preTargetNode.Reset();
    frameNode.Reset();
    
    /**
     * @tc.steps: step4. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    bool variableFalse = false;
    dragDropManager->SetEventStrictReportingEnabled(variableFalse);
    bool reportingEnabledFalse = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledFalse);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_1, GLOBAL_1 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_2, GLOBAL_3 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledFalse);
}

/**
 * @tc.name: DragDropReportTest030
 * @tc.desc: Test DragEventStrictReportingEnabled
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropReportTestNg, DragDropReportTest030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. ReportingEnable is not set.
     * @tc.expected: reportingEnabledDefault is false.
     */
    bool reportingEnabledDefault = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledDefault);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_2, GLOBAL_1 }, frameNode);
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_1, GLOBAL_2 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledDefault);
    preTargetNode.Reset();
    frameNode.Reset();

    /**
     * @tc.steps: step3. ReportingSupported is set to true.
     * @tc.expected: reportingEnabledTrue is true.
     */
    bool variableTrue = true;
    dragDropManager->SetEventStrictReportingEnabled(variableTrue);
    bool reportingEnabledTrue = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_TRUE(reportingEnabledTrue);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_2, GLOBAL_1 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_1, GLOBAL_2 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_TRUE(reportingEnabledTrue);
    preTargetNode.Reset();
    frameNode.Reset();
    
    /**
     * @tc.steps: step4. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    bool variableFalse = false;
    dragDropManager->SetEventStrictReportingEnabled(variableFalse);
    bool reportingEnabledFalse = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledFalse);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_2, GLOBAL_1 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_1, GLOBAL_2 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledFalse);
}

/**
 * @tc.name: DragDropReportTest031
 * @tc.desc: Test DragEventStrictReportingEnabled
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropReportTestNg, DragDropReportTest031, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. ReportingEnable is not set.
     * @tc.expected: reportingEnabledDefault is false.
     */
    bool reportingEnabledDefault = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledDefault);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_2 }, frameNode);
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_2, GLOBAL_3 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledDefault);
    preTargetNode.Reset();
    frameNode.Reset();

    /**
     * @tc.steps: step3. ReportingSupported is set to true.
     * @tc.expected: reportingEnabledTrue is true.
     */
    bool variableTrue = true;
    dragDropManager->SetEventStrictReportingEnabled(variableTrue);
    bool reportingEnabledTrue = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_TRUE(reportingEnabledTrue);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_2 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_2, GLOBAL_3 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_TRUE(reportingEnabledTrue);
    preTargetNode.Reset();
    frameNode.Reset();
    
    /**
     * @tc.steps: step4. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    bool variableFalse = false;
    dragDropManager->SetEventStrictReportingEnabled(variableFalse);
    bool reportingEnabledFalse = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledFalse);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_2 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_2, GLOBAL_3 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledFalse);
}

/**
 * @tc.name: DragDropReportTest032
 * @tc.desc: Test DragEventStrictReportingEnabled
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropReportTestNg, DragDropReportTest032, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. ReportingEnable is not set.
     * @tc.expected: reportingEnabledDefault is false.
     */
    bool reportingEnabledDefault = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledDefault);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_3 }, frameNode);
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_1, GLOBAL_2 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledDefault);
    preTargetNode.Reset();
    frameNode.Reset();

    /**
     * @tc.steps: step3. ReportingSupported is set to true.
     * @tc.expected: reportingEnabledTrue is true.
     */
    bool variableTrue = true;
    dragDropManager->SetEventStrictReportingEnabled(variableTrue);
    bool reportingEnabledTrue = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_TRUE(reportingEnabledTrue);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_3 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_1, GLOBAL_2 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_TRUE(reportingEnabledTrue);
    preTargetNode.Reset();
    frameNode.Reset();
    
    /**
     * @tc.steps: step4. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    bool variableFalse = false;
    dragDropManager->SetEventStrictReportingEnabled(variableFalse);
    bool reportingEnabledFalse = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledFalse);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_3 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_1, GLOBAL_2 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledFalse);
}

/**
 * @tc.name: DragDropReportTest033
 * @tc.desc: Test DragEventStrictReportingEnabled
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropReportTestNg, DragDropReportTest033, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. ReportingEnable is not set.
     * @tc.expected: reportingEnabledDefault is false.
     */
    bool reportingEnabledDefault = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledDefault);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_3 }, frameNode);
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_2, GLOBAL_2 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledDefault);
    preTargetNode.Reset();
    frameNode.Reset();

    /**
     * @tc.steps: step3. ReportingSupported is set to true.
     * @tc.expected: reportingEnabledTrue is true.
     */
    bool variableTrue = true;
    dragDropManager->SetEventStrictReportingEnabled(variableTrue);
    bool reportingEnabledTrue = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_TRUE(reportingEnabledTrue);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_3 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_2, GLOBAL_2 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_TRUE(reportingEnabledTrue);
    preTargetNode.Reset();
    frameNode.Reset();
    
    /**
     * @tc.steps: step4. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    bool variableFalse = false;
    dragDropManager->SetEventStrictReportingEnabled(variableFalse);
    bool reportingEnabledFalse = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledFalse);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_3 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_2, GLOBAL_2 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledFalse);
}

/**
 * @tc.name: DragDropReportTest034
 * @tc.desc: Test DragEventStrictReportingEnabled
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropReportTestNg, DragDropReportTest034, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. ReportingEnable is not set.
     * @tc.expected: reportingEnabledDefault is false.
     */
    bool reportingEnabledDefault = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledDefault);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_3 }, frameNode);
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_2, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledDefault);
    preTargetNode.Reset();
    frameNode.Reset();

    /**
     * @tc.steps: step3. ReportingSupported is set to true.
     * @tc.expected: reportingEnabledTrue is true.
     */
    bool variableTrue = true;
    dragDropManager->SetEventStrictReportingEnabled(variableTrue);
    bool reportingEnabledTrue = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_TRUE(reportingEnabledTrue);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_3 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_2, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_TRUE(reportingEnabledTrue);
    preTargetNode.Reset();
    frameNode.Reset();
    
    /**
     * @tc.steps: step4. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    bool variableFalse = false;
    dragDropManager->SetEventStrictReportingEnabled(variableFalse);
    bool reportingEnabledFalse = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledFalse);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_3 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_2, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledFalse);
}

/**
 * @tc.name: DragDropReportTest035
 * @tc.desc: Test DragEventStrictReportingEnabled
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropReportTestNg, DragDropReportTest035, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. ReportingEnable is not set.
     * @tc.expected: reportingEnabledDefault is false.
     */
    bool reportingEnabledDefault = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledDefault);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_3 }, frameNode);
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_3, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledDefault);
    preTargetNode.Reset();
    frameNode.Reset();

    /**
     * @tc.steps: step3. ReportingSupported is set to true.
     * @tc.expected: reportingEnabledTrue is true.
     */
    bool variableTrue = true;
    dragDropManager->SetEventStrictReportingEnabled(variableTrue);
    bool reportingEnabledTrue = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_TRUE(reportingEnabledTrue);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_3 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_3, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_TRUE(reportingEnabledTrue);
    preTargetNode.Reset();
    frameNode.Reset();
    
    /**
     * @tc.steps: step4. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    bool variableFalse = false;
    dragDropManager->SetEventStrictReportingEnabled(variableFalse);
    bool reportingEnabledFalse = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledFalse);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_3 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_3, GLOBAL_1 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledFalse);
}

/**
 * @tc.name: DragDropReportTest036
 * @tc.desc: Test DragEventStrictReportingEnabled
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropReportTestNg, DragDropReportTest036, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. ReportingEnable is not set.
     * @tc.expected: reportingEnabledDefault is false.
     */
    bool reportingEnabledDefault = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledDefault);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_3 }, frameNode);
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_1, GLOBAL_3 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledDefault);
    preTargetNode.Reset();
    frameNode.Reset();

    /**
     * @tc.steps: step3. ReportingSupported is set to true.
     * @tc.expected: reportingEnabledTrue is true.
     */
    bool variableTrue = true;
    dragDropManager->SetEventStrictReportingEnabled(variableTrue);
    bool reportingEnabledTrue = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_TRUE(reportingEnabledTrue);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_3 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_1, GLOBAL_3 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_TRUE(reportingEnabledTrue);
    preTargetNode.Reset();
    frameNode.Reset();
    
    /**
     * @tc.steps: step4. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    bool variableFalse = false;
    dragDropManager->SetEventStrictReportingEnabled(variableFalse);
    bool reportingEnabledFalse = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledFalse);
    frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_3, GLOBAL_3 }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->FireOnDragLeave(preTargetNode, { GLOBAL_1, GLOBAL_3 }, EXTRA_INFO);
    ASSERT_TRUE(preTargetNode);
    ASSERT_FALSE(reportingEnabledFalse);
}
} // namespace OHOS::Ace::NG