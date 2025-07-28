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

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/image/pixel_map.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/manager/drag_drop/drag_drop_manager.h"
#include "core/components_ng/manager/drag_drop/drag_drop_proxy.h"
#include "frameworks/core/components_ng/pattern/pattern.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr int64_t PROXY_ID = 1;
constexpr int64_t PROXY_ID_NOT_FIT = 101;
const std::string GET_EXTRA("GetExtraInfoFromClipboard");
const std::string NODE_TAG("custom_node");
const std::string EXTRA_INFO_DRAG_START("drag_start_info");
const std::string ON_DRAG_START("OnDragStart");
const std::string ITEM_DRAG_START("OnItemDragStart");
constexpr int32_t DRAGGED_INDEX = 0;
const DragType DRAG_TYPE_GRID = DragType::GRID;
} // namespace

class DragDropProxyTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
};

void DragDropProxyTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void DragDropProxyTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: DragDropProxyTest001
 * @tc.desc: Test OnDragStart
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropProxyTestNg, DragDropProxyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropProxy with unfitted proxyId
     * @tc.expected: step1. id_ = PROXY_ID_NOT_FIT
     */
    auto proxyUnFitted = AceType::MakeRefPtr<DragDropProxy>(PROXY_ID_NOT_FIT);
    EXPECT_EQ(proxyUnFitted->id_, PROXY_ID_NOT_FIT);

    /**
     * @tc.steps: step2. call onDragStart
     * @tc.expected: step2. no fatal errors happended
     *                      DragDropManager->OnDragStart() & AddDataToClipboard() will not be called
     *                      frameNode's nodeName_ not change
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    GestureEvent info;
    proxyUnFitted->OnDragStart(info, EXTRA_INFO_DRAG_START, frameNode);
    auto nodeName = frameNode->GetNodeName();
    EXPECT_EQ(nodeName, "");

    /**
     * @tc.steps: step3. construct a DragDropProxy with fitted proxyId
     * @tc.expected: step3. id_ = PROXY_ID
     */
    auto proxy = AceType::MakeRefPtr<DragDropProxy>(PROXY_ID);
    EXPECT_EQ(proxy->id_, PROXY_ID);

    /**
     * @tc.steps: step4. call onDragStart
     * @tc.expected: step4. DragDropManager->OnDragStart() & AddDataToClipboard() will be called
     *                      some logs will be print
     *                      they are defined in "mock_drag_drop_manager.cpp"
     *                      frameNode's nodeName_ not change
     */
    proxy->OnDragStart(info, EXTRA_INFO_DRAG_START, frameNode);
    nodeName = frameNode->GetNodeName();
    EXPECT_EQ(nodeName, "");
}

/**
 * @tc.name: DragDropProxyTest002
 * @tc.desc: Test OnDragMove
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropProxyTestNg, DragDropProxyTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropProxy with unfitted proxyId
     * @tc.expected: step1. id_ = PROXY_ID_NOT_FIT
     */
    auto proxyUnFitted = AceType::MakeRefPtr<DragDropProxy>(PROXY_ID_NOT_FIT);
    EXPECT_EQ(proxyUnFitted->id_, PROXY_ID_NOT_FIT);

    /**
     * @tc.steps: step2. call OnDragMove
     * @tc.expected: step2. no fatal errors happended
     *                      DragDropManager->OnDragMove() & GetExtraInfoFromClipboard() will not be called
     */
    GestureEvent info;
    proxyUnFitted->OnDragMove(info);

    /**
     * @tc.steps: step3. construct a DragDropProxy with fitted proxyId
     * @tc.expected: step3. id_ = PROXY_ID
     */
    auto proxy = AceType::MakeRefPtr<DragDropProxy>(PROXY_ID);
    EXPECT_EQ(proxy->id_, PROXY_ID);

    /**
     * @tc.steps: step4. call OnDragMove
     * @tc.expected: step4. DragDropManager->OnDragMove() & GetExtraInfoFromClipboard() will be called
     *                      some logs will be print
     *                      they are defined in "mock_drag_drop_manager.cpp"
     */
    proxy->OnDragMove(info);
}

/**
 * @tc.name: DragDropProxyTest003
 * @tc.desc: Test OnDragEnd
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropProxyTestNg, DragDropProxyTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropProxy with unfitted proxyId
     * @tc.expected: step1. id_ = PROXY_ID_NOT_FIT
     */
    auto proxyUnFitted = AceType::MakeRefPtr<DragDropProxy>(PROXY_ID_NOT_FIT);
    EXPECT_EQ(proxyUnFitted->id_, PROXY_ID_NOT_FIT);

    /**
     * @tc.steps: step2. call OnDragEnd
     * @tc.expected: step2. no fatal errors happended
     *                      DragDropManager->OnDragEnd() & GetExtraInfoFromClipboard() &
     *                      RestoreClipboardData() will not be called
     */
    GestureEvent info;
    proxyUnFitted->OnDragEnd(info);

    /**
     * @tc.steps: step3. construct a DragDropProxy with fitted proxyId
     * @tc.expected: step3. id_ = PROXY_ID
     */
    auto proxy = AceType::MakeRefPtr<DragDropProxy>(PROXY_ID);
    EXPECT_EQ(proxy->id_, PROXY_ID);

    /**
     * @tc.steps: step4. call OnDragEnd
     * @tc.expected: step4. DragDropManager->OnDragEnd() & GetExtraInfoFromClipboard() &
     *                      RestoreClipboardData() will be called
     *                      some logs will be print they are defined in "mock_drag_drop_manager.cpp"
     */
    proxy->OnDragEnd(info);
}

/**
 * @tc.name: DragDropProxyOnDragEndTest001
 * @tc.desc: Test OnDragEnd
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropProxyTestNg, DragDropProxyOnDragEndTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropProxy with unfitted proxyId
     * @tc.expected: step1. id_ = PROXY_ID_NOT_FIT
     */
    auto proxyUnFitted = AceType::MakeRefPtr<DragDropProxy>(PROXY_ID_NOT_FIT);
    EXPECT_EQ(proxyUnFitted->id_, PROXY_ID_NOT_FIT);

    /**
     * @tc.steps: step2. call OnDragEnd
     * @tc.expected: step2. no fatal errors happended
     *                      DragDropManager->OnDragEnd() & GetExtraInfoFromClipboard() &
     *                      RestoreClipboardData() will not be called
     */
    GestureEvent info;
    proxyUnFitted->OnDragEnd(info, true);

    /**
     * @tc.steps: step3. construct a DragDropProxy with fitted proxyId
     * @tc.expected: step3. id_ = PROXY_ID
     */
    auto proxy = AceType::MakeRefPtr<DragDropProxy>(PROXY_ID);
    EXPECT_EQ(proxy->id_, PROXY_ID);

    /**
     * @tc.steps: step4. call OnDragEnd
     * @tc.expected: step4. DragDropManager->OnDragEnd() & GetExtraInfoFromClipboard() &
     *                      RestoreClipboardData() will be called
     *                      some logs will be print they are defined in "mock_drag_drop_manager.cpp"
     */
    proxy->OnDragEnd(info, true);
    EXPECT_EQ(proxy->id_, PROXY_ID);
}

/**
 * @tc.name: DragDropProxyTest004
 * @tc.desc: Test onDragCancel
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropProxyTestNg, DragDropProxyTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropProxy with unfitted proxyId
     * @tc.expected: step1. id_ = PROXY_ID_NOT_FIT
     */
    auto proxyUnFitted = AceType::MakeRefPtr<DragDropProxy>(PROXY_ID_NOT_FIT);
    EXPECT_EQ(proxyUnFitted->id_, PROXY_ID_NOT_FIT);

    /**
     * @tc.steps: step2. call onDragCancel
     * @tc.expected: step2. no fatal errors happended
     *                      DragDropManager->onDragCancel() will not be called
     */
    proxyUnFitted->onDragCancel();

    /**
     * @tc.steps: step3. construct a DragDropProxy with fitted proxyId
     * @tc.expected: step3. id_ = PROXY_ID
     */
    auto proxy = AceType::MakeRefPtr<DragDropProxy>(PROXY_ID);
    EXPECT_EQ(proxy->id_, PROXY_ID);

    /**
     * @tc.steps: step4. call onDragCancel
     * @tc.expected: step4. DragDropManager->onDragCancel() will be called
     *                      some logs will be print they are defined in "mock_drag_drop_manager.cpp"
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    auto manager = pipeline->GetDragDropManager();
    manager->currentId_ = PROXY_ID;
    proxy->onDragCancel();
}

/**
 * @tc.name: DragDropProxyTest005
 * @tc.desc: Test onItemDragStart
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropProxyTestNg, DragDropProxyTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropProxy with unfitted proxyId
     * @tc.expected: step1. id_ = PROXY_ID_NOT_FIT
     */
    auto proxyUnFitted = AceType::MakeRefPtr<DragDropProxy>(PROXY_ID_NOT_FIT);
    EXPECT_EQ(proxyUnFitted->id_, PROXY_ID_NOT_FIT);

    /**
     * @tc.steps: step2. call OnItemDragStart
     * @tc.expected: step2. no fatal errors happended
     *                      DragDropManager->OnItemDragStart() will not be called
     *                      frameNode' nodeName not change
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    GestureEvent info;
    proxyUnFitted->OnItemDragStart(info, frameNode);
    auto nodeName = frameNode->GetNodeName();
    EXPECT_EQ(nodeName, "");

    /**
     * @tc.steps: step3. construct a DragDropProxy with fitted proxyId
     * @tc.expected: step3. id_ = PROXY_ID
     */
    auto proxy = AceType::MakeRefPtr<DragDropProxy>(PROXY_ID);
    EXPECT_EQ(proxy->id_, PROXY_ID);

    /**
     * @tc.steps: step4. call OnItemDragStart
     * @tc.expected: step4. DragDropManager->OnItemDragStart() will be called
     *                      some logs will be print they are defined in "mock_drag_drop_manager.cpp"
     *                      frameNode' nodeName not change
     */
    proxy->OnItemDragStart(info, frameNode);
    nodeName = frameNode->GetNodeName();
    EXPECT_EQ(nodeName, "");
}

/**
 * @tc.name: DragDropProxyTest006
 * @tc.desc: Test OnItemDragMove
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropProxyTestNg, DragDropProxyTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropProxy with unfitted proxyId
     * @tc.expected: step1. id_ = PROXY_ID_NOT_FIT
     */
    auto proxyUnFitted = AceType::MakeRefPtr<DragDropProxy>(PROXY_ID_NOT_FIT);
    EXPECT_EQ(proxyUnFitted->id_, PROXY_ID_NOT_FIT);

    /**
     * @tc.steps: step2. call OnItemDragMove
     * @tc.expected: step2. no fatal errors happended
     *                      DragDropManager->OnItemDragMove() will not be called
     */
    GestureEvent info;
    proxyUnFitted->OnItemDragMove(info, DRAGGED_INDEX, DRAG_TYPE_GRID);

    /**
     * @tc.steps: step3. construct a DragDropProxy with fitted proxyId
     * @tc.expected: step3. id_ = PROXY_ID
     */
    auto proxy = AceType::MakeRefPtr<DragDropProxy>(PROXY_ID);
    EXPECT_EQ(proxy->id_, PROXY_ID);

    /**
     * @tc.steps: step4. call OnItemDragMove
     * @tc.expected: step4. DragDropManager->OnItemDragMove() will be called
     *                      some logs will be print they are defined in "mock_drag_drop_manager.cpp"
     */
    proxy->OnItemDragMove(info, DRAGGED_INDEX, DRAG_TYPE_GRID);
}

/**
 * @tc.name: DragDropProxyTest007
 * @tc.desc: Test OnItemDragEnd
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropProxyTestNg, DragDropProxyTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropProxy with unfitted proxyId
     * @tc.expected: step1. id_ = PROXY_ID_NOT_FIT
     */
    auto proxyUnFitted = AceType::MakeRefPtr<DragDropProxy>(PROXY_ID_NOT_FIT);
    EXPECT_EQ(proxyUnFitted->id_, PROXY_ID_NOT_FIT);

    /**
     * @tc.steps: step2. call OnItemDragEnd
     * @tc.expected: step2. no fatal errors happended
     *                      DragDropManager->OnItemDragEnd() will not be called
     */
    GestureEvent info;
    proxyUnFitted->OnItemDragEnd(info, DRAGGED_INDEX, DRAG_TYPE_GRID);

    /**
     * @tc.steps: step3. construct a DragDropProxy with fitted proxyId
     * @tc.expected: step3. id_ = PROXY_ID
     */
    auto proxy = AceType::MakeRefPtr<DragDropProxy>(PROXY_ID);
    EXPECT_EQ(proxy->id_, PROXY_ID);

    /**
     * @tc.steps: step4. call OnItemDragEnd
     * @tc.expected: step4. DragDropManager->OnItemDragEnd() will be called
     *                      some logs will be print they are defined in "mock_drag_drop_manager.cpp"
     */
    proxy->OnItemDragEnd(info, DRAGGED_INDEX, DRAG_TYPE_GRID);
}

/**
 * @tc.name: DragDropProxyTest008
 * @tc.desc: Test onItemDragCancel
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropProxyTestNg, DragDropProxyTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropProxy with unfitted proxyId
     * @tc.expected: step1. id_ = PROXY_ID_NOT_FIT
     */
    auto proxyUnFitted = AceType::MakeRefPtr<DragDropProxy>(PROXY_ID_NOT_FIT);
    EXPECT_EQ(proxyUnFitted->id_, PROXY_ID_NOT_FIT);

    /**
     * @tc.steps: step2. call onItemDragCancel
     * @tc.expected: step2. no fatal errors happended
     *                      DragDropManager->onItemDragCancel() will not be called
     */
    GestureEvent info;
    proxyUnFitted->onItemDragCancel();

    /**
     * @tc.steps: step3. construct a DragDropProxy with fitted proxyId
     * @tc.expected: step3. id_ = PROXY_ID
     */
    auto proxy = AceType::MakeRefPtr<DragDropProxy>(PROXY_ID);
    EXPECT_EQ(proxy->id_, PROXY_ID);

    /**
     * @tc.steps: step4. call onItemDragCancel
     * @tc.expected: step4. DragDropManager->onItemDragCancel() will be called
     *                      some logs will be print they are defined in "mock_drag_drop_manager.cpp"
     */
    proxy->onItemDragCancel();
}

/**
 * @tc.name: DragDropProxyTest009
 * @tc.desc: Test OnTextDragStart
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropProxyTestNg, DragDropProxyTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropProxy with unfitted proxyId.
     * @tc.expected: step1. id_ is equal to PROXY_ID_NOT_FIT.
     */
    auto proxyUnFitted = AceType::MakeRefPtr<DragDropProxy>(PROXY_ID_NOT_FIT);
    EXPECT_EQ(proxyUnFitted->id_, PROXY_ID_NOT_FIT);

    /**
     * @tc.steps: step2. construct a manager and update currentId_.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    auto manager = pipeline->GetDragDropManager();
    manager->currentId_ = PROXY_ID_NOT_FIT;

    /**
     * @tc.steps: step3. call OnTextDragStart with ON_DRAG_START.
     * @tc.expected: step3. retFlag is true.
     */
    proxyUnFitted->OnTextDragStart(ON_DRAG_START);
    auto retFlag = manager->CheckDragDropProxy(PROXY_ID_NOT_FIT);
    EXPECT_TRUE(retFlag);
}

/**
 * @tc.name: DragDropProxyTest010
 * @tc.desc: Test CheckDragDropProxy out of OnDragStart is a true branch
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropProxyTestNg, DragDropProxyTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropProxy with unfitted proxyUnFitted.
     * @tc.expected: step1. id_ is equal to PROXY_ID_NOT_FIT.
     */
    auto proxyUnFitted = AceType::MakeRefPtr<DragDropProxy>(PROXY_ID_NOT_FIT);
    EXPECT_EQ(proxyUnFitted->id_, PROXY_ID_NOT_FIT);

    /**
     * @tc.steps: step2. construct a manager and update currentId_.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    auto manager = pipeline->GetDragDropManager();
    manager->currentId_ = PROXY_ID_NOT_FIT;

    /**
     * @tc.steps: step3. call onDragStart with GestureEvent and frameNode.
     * @tc.expected: step3. proxyUnFitted->id_ is equal to manager->currentId_.
     */
    GestureEvent info;
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    proxyUnFitted->OnDragStart(info, EXTRA_INFO_DRAG_START, frameNode);
    EXPECT_EQ(proxyUnFitted->id_, manager->currentId_);
}

/**
 * @tc.name: DragDropProxyTest011
 * @tc.desc: Test isTextDragEnd out of OnDragEnd is a true branch
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropProxyTestNg, DragDropProxyTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropProxy with fitted proxy.
     * @tc.expected: step1. id_ is equal to PROXY_ID.
     */
    auto proxy = AceType::MakeRefPtr<DragDropProxy>(PROXY_ID);
    EXPECT_EQ(proxy->id_, PROXY_ID);

    /**
     * @tc.steps: step2. construct a manager and update currentId_.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    auto manager = pipeline->GetDragDropManager();
    EXPECT_TRUE(manager);

    /**
     * @tc.steps: step3. call OnDragEnd with GestureEvent and true.
     * @tc.expected: step3. manager->currentId_ is equal to -1.
     */
    GestureEvent info;
    manager->currentId_ = PROXY_ID;
    proxy->OnDragEnd(info, true);
    EXPECT_EQ(manager->currentId_, -1);
}

/**
 * @tc.name: DragDropProxyTest012
 * @tc.desc: DestroyDragWindow
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropProxyTestNg, DragDropProxyTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropProxy with fitted proxy.
     * @tc.expected: step1. id_ is equal to PROXY_ID.
     */
    auto proxy = AceType::MakeRefPtr<DragDropProxy>(PROXY_ID);
    EXPECT_EQ(proxy->id_, PROXY_ID);

    /**
     * @tc.steps: step2. construct a manager and update currentId_.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    auto manager = pipeline->GetDragDropManager();
    manager->currentId_ = PROXY_ID;

    /**
     * @tc.steps: step3. call DestroyDragWindow.
     * @tc.expected: step3. manager->currentId_ is equal to proxy->id_.
     */
    proxy->DestroyDragWindow();
    EXPECT_EQ(manager->currentId_, -1);
}

/**
 * @tc.name: DragDropProxyTest013
 * @tc.desc: Test OnDragStart DragEvent information
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropProxyTestNg, DragDropProxyTest013, TestSize.Level1)
{
    /**
    * @tc.steps: step1. construct a DragDropProxy.
    */
    auto proxy = AceType::MakeRefPtr<DragDropProxy>(PROXY_ID);
    ASSERT_NE(proxy, nullptr);

    /**
    * @tc.steps: step2. construct a manager.
    */
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto manager = pipeline->GetDragDropManager();
    ASSERT_NE(manager, nullptr);
    manager->currentId_ = PROXY_ID;

    /**
    * @tc.steps: step3. call OnDragStart with GestureEvent.
    */
    GestureEvent info;
    info.SetSourceTool(SourceTool::FINGER);
    info.SetTargetDisplayId(1);
    proxy->OnDragStart(info, EXTRA_INFO_DRAG_START, nullptr);
    EXPECT_EQ(manager->preDragPointerEvent_.sourceTool, SourceTool::FINGER);
    EXPECT_EQ(manager->preDragPointerEvent_.displayId, 1);
}
} // namespace OHOS::Ace::NG
