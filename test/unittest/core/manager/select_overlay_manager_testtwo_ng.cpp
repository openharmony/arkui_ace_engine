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

#include <memory>
#include <optional>

#include "gtest/gtest.h"
#define private public
#define protected public

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/manager/select_content_overlay/select_overlay_callback.h"
#include "core/components_ng/manager/select_content_overlay/select_overlay_holder.h"
#include "core/components_ng/manager/select_overlay/select_overlay_manager.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/components_ng/pattern/text/text_base.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/property/property.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string ROOT_TAG("root");
constexpr int32_t NODE_ID = 143;
const OffsetF RIGHT_CLICK_OFFSET = OffsetF(10.0f, 10.0f);
const OffsetF ROOT_OFFSET = OffsetF(10.0f, 10.0f);
} // namespace

class SelectOverlayManagerTestTwoNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    RefPtr<SelectOverlayManager> selectOverlayManager_;
    RefPtr<SelectOverlayProxy> proxy_;
    RefPtr<FrameNode> root_;
    void Init();
};

class MockSelectOverlayHolder : public SelectOverlayHolder, public SelectOverlayCallback {
    DECLARE_ACE_TYPE(MockSelectOverlayHolder, SelectOverlayHolder, SelectOverlayCallback);

public:
    MockSelectOverlayHolder() = default;
    ~MockSelectOverlayHolder() = default;

    void SetOwner(const RefPtr<FrameNode>& node)
    {
        node_ = node;
    }

    RefPtr<FrameNode> GetOwner()
    {
        return node_;
    }

    RefPtr<SelectOverlayCallback> GetCallback() override
    {
        return Claim(this);
    }

    void OnUpdateSelectOverlayInfo(SelectOverlayInfo& overlayInfo, int32_t requestCode)
    {
        overlayInfo.enableHandleLevel = true;
        overlayInfo.handleLevelMode = handleLevelMode_;
        overlayInfo.menuInfo.menuIsShow = true;
    }

    void OnHandleLevelModeChanged(HandleLevelMode mode) override
    {
        handleLevelMode_ = mode;
    }

    bool CheckSwitchToMode(HandleLevelMode mode) override
    {
        return allowSwitchMode_;
    }

    bool CheckTouchInHostNode(const PointF& touchPoint)
    {
        return false;
    }

private:
    HandleLevelMode handleLevelMode_ = HandleLevelMode::OVERLAY;
    bool allowSwitchMode_ = false;
    RefPtr<FrameNode> node_;
};

void SelectOverlayManagerTestTwoNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
}

void SelectOverlayManagerTestTwoNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void SelectOverlayManagerTestTwoNg::Init()
{
    SelectOverlayInfo selectOverlayInfo;
    selectOverlayInfo.singleLineHeight = NODE_ID;
    root_ = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    selectOverlayManager_ = AceType::MakeRefPtr<SelectOverlayManager>(root_);
    ASSERT_NE(selectOverlayManager_, nullptr);
    proxy_ = selectOverlayManager_->CreateAndShowSelectOverlay(selectOverlayInfo, nullptr);
    ASSERT_NE(proxy_, nullptr);
}

/**
 * @tc.name: RemoveHoldSelectionCallback
 * @tc.desc: test select_content_overlay_manager.cpp RemoveHoldSelectionCallback
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestTwoNg, RemoveHoldSelectionCallback001, TestSize.Level1)
{
    Init();
    auto content = SelectContentOverlayManager(root_);
    int32_t id = 1;
    auto holder = AceType::MakeRefPtr<SelectOverlayHolder>();
    HoldSelectionInfo holdSelectionInfo_;
    holdSelectionInfo_ = {};
    content.SetHolder(holder);
    content.SetHoldSelectionCallback(id, holdSelectionInfo_);
    EXPECT_EQ(content.selectionHoldId_, 1);
    content.RemoveHoldSelectionCallback(id);
    EXPECT_EQ(content.selectionHoldId_, -1);
}

/**
 * @tc.name: RemoveHoldSelectionCallback
 * @tc.desc: test select_content_overlay_manager.cpp RemoveHoldSelectionCallback
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestTwoNg, RemoveHoldSelectionCallback002, TestSize.Level1)
{
    Init();
    auto content = SelectContentOverlayManager(root_);
    int32_t id = 1;
    auto holder = AceType::MakeRefPtr<SelectOverlayHolder>();
    HoldSelectionInfo holdSelectionInfo_;
    holdSelectionInfo_ = {};
    content.SetHolder(holder);
    content.SetHoldSelectionCallback(id, holdSelectionInfo_);
    content.RemoveHoldSelectionCallback(5);
    EXPECT_EQ(content.selectionHoldId_, 1);
}

/**
 * @tc.name: RevertRectRelativeToRoot
 * @tc.desc: test select_content_overlay_manager.cpp RevertRectRelativeToRoot
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestTwoNg, RevertRectRelativeToRoot001, TestSize.Level1)
{
    Init();
    auto content = SelectContentOverlayManager(root_);
    int32_t id = 1;
    auto holder = AceType::MakeRefPtr<SelectOverlayHolder>();
    HoldSelectionInfo holdSelectionInfo_;
    holdSelectionInfo_ = {};
    content.SetHolder(holder);
    content.SetHoldSelectionCallback(id, holdSelectionInfo_);
    content.shareOverlayInfo_ = std::make_shared<SelectOverlayInfo>();
    content.shareOverlayInfo_->handleLevelMode = HandleLevelMode::EMBED;
    RectF rect(1.0f, 20.0f, 100.0f, 150.0f);
    auto rectCopy = rect.GetOffset();
    content.RevertRectRelativeToRoot(rect);
    EXPECT_EQ(rectCopy, rect.GetOffset());
}

/**
 * @tc.name: DestroySelectOverlayNodeWithAnimation001
 * @tc.desc: test select_content_overlay_manager.cpp DestroySelectOverlayNodeWithAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestTwoNg, DestroySelectOverlayNodeWithAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init SelectContentOverlayManager
     */
    Init();
    auto content = SelectContentOverlayManager(root_);
    SelectOverlayInfo selectInfo;
    selectInfo.enableHandleLevel = true;
    selectInfo.menuInfo.showCut = true;

    /**
     * @tc.steps: step2. CreateSelectOverlayNode
     */
    content.shareOverlayInfo_ = std::make_shared<SelectOverlayInfo>(selectInfo);
    ASSERT_NE(content.shareOverlayInfo_, nullptr);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(content.shareOverlayInfo_);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. call DestroySelectOverlayNodeWithAnimation
     */
    content.DestroySelectOverlayNodeWithAnimation(frameNode);
    content.ClearAllStatus();
    EXPECT_EQ(content.selectionHoldId_, -1);
}

/**
 * @tc.name: ResetSelectionRect001
 * @tc.desc: test select_content_overlay_manager.cpp ResetSelectionRect
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestTwoNg, ResetSelectionRect001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init SelectContentOverlayManager
     */
    Init();
    auto content = SelectContentOverlayManager(root_);

    /**
     * @tc.steps: step2. SetHoldSelectionCallback
     */
    int32_t id = 1;
    auto holder = AceType::MakeRefPtr<SelectOverlayHolder>();
    HoldSelectionInfo holdSelectionInfo_;
    holdSelectionInfo_ = {};
    content.SetHolder(holder);
    content.SetHoldSelectionCallback(id, holdSelectionInfo_);
    EXPECT_EQ(content.selectionHoldId_, 1);

    /**
     * @tc.steps: step3. call ResetSelectionRect
     */
    content.ResetSelectionRect();
    EXPECT_EQ(content.selectionHoldId_, -1);
}

/**
 * @tc.name: HandleSelectionEvent001
 * @tc.desc: test select_content_overlay_manager.cpp HandleSelectionEvent
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestTwoNg, HandleSelectionEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init SelectContentOverlayManager
     */
    Init();
    auto content = SelectContentOverlayManager(root_);

    /**
     * @tc.steps: step2. SetHoldSelectionCallback
     */
    int32_t id = 1;
    auto holder = AceType::MakeRefPtr<SelectOverlayHolder>();
    HoldSelectionInfo holdSelectionInfo_;
    holdSelectionInfo_ = {};
    std::function<bool(const PointF&, bool)> checkTouchInArea = [](const PointF& point, bool) { return false; };
    std::function<void()> resetSelectionCallback = []() {};
    holdSelectionInfo_.checkTouchInArea = std::move(checkTouchInArea);
    holdSelectionInfo_.resetSelectionCallback = std::move(resetSelectionCallback);

    content.SetHolder(holder);
    content.SetHoldSelectionCallback(id, holdSelectionInfo_);
    EXPECT_EQ(content.selectionHoldId_, 1);

    /**
     * @tc.steps: step3. call HandleSelectionEvent
     */
    PointF point = PointF(0.0, 0.0);
    TouchEvent rawTouchEvent;
    rawTouchEvent.sourceType = SourceType::MOUSE;
    rawTouchEvent.type = TouchType::DOWN;
    content.HandleSelectionEvent(point, rawTouchEvent);
    EXPECT_EQ(content.selectionHoldId_, -1);
}

/**
 * @tc.name: HandleSelectionEvent002
 * @tc.desc: test select_content_overlay_manager.cpp HandleSelectionEvent
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestTwoNg, HandleSelectionEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init SelectContentOverlayManager
     */
    Init();
    auto content = SelectContentOverlayManager(root_);

    /**
     * @tc.steps: step2. SetHoldSelectionCallback
     */
    int32_t id = 1;
    auto holder = AceType::MakeRefPtr<SelectOverlayHolder>();
    HoldSelectionInfo holdSelectionInfo_;
    holdSelectionInfo_ = {};
    std::function<bool(const PointF&, bool)> checkTouchInArea = [](const PointF& point, bool) { return true; };
    std::function<void()> resetSelectionCallback = []() {};
    holdSelectionInfo_.checkTouchInArea = std::move(checkTouchInArea);
    holdSelectionInfo_.resetSelectionCallback = std::move(resetSelectionCallback);

    content.SetHolder(holder);
    content.SetHoldSelectionCallback(id, holdSelectionInfo_);
    EXPECT_EQ(content.selectionHoldId_, 1);

    /**
     * @tc.steps: step3. call HandleSelectionEvent
     */
    PointF point = PointF(0.0, 0.0);
    TouchEvent rawTouchEvent;
    rawTouchEvent.sourceType = SourceType::MOUSE;
    rawTouchEvent.type = TouchType::DOWN;
    content.HandleSelectionEvent(point, rawTouchEvent);
    EXPECT_EQ(content.selectionHoldId_, 1);
}

/**
 * @tc.name: HandleSelectionEvent003
 * @tc.desc: test select_content_overlay_manager.cpp HandleSelectionEvent
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestTwoNg, HandleSelectionEvent003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init SelectContentOverlayManager
     */
    Init();
    auto content = SelectContentOverlayManager(root_);
    SelectOverlayInfo selectInfo;
    selectInfo.enableHandleLevel = true;
    selectInfo.menuInfo.showCut = true;
    content.shareOverlayInfo_ = std::make_shared<SelectOverlayInfo>(selectInfo);
    ASSERT_NE(content.shareOverlayInfo_, nullptr);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(content.shareOverlayInfo_);
    ASSERT_NE(frameNode, nullptr);
    content.menuNode_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    ASSERT_NE(content.menuNode_.Upgrade(), nullptr);

    /**
     * @tc.steps: step2. mount menuNode to root node
     */
    frameNode->SetParent(root_);

    /**
     * @tc.steps: step3. SetHoldSelectionCallback
     */
    int32_t id = 1;
    auto holder = AceType::MakeRefPtr<SelectOverlayHolder>();
    HoldSelectionInfo holdSelectionInfo_;
    holdSelectionInfo_ = {};
    std::function<bool(const PointF&, bool)> checkTouchInArea = [](const PointF& point, bool) { return false; };
    std::function<void()> resetSelectionCallback = []() {};
    holdSelectionInfo_.checkTouchInArea = std::move(checkTouchInArea);
    holdSelectionInfo_.resetSelectionCallback = std::move(resetSelectionCallback);

    content.SetHolder(holder);
    content.SetHoldSelectionCallback(id, holdSelectionInfo_);
    EXPECT_EQ(content.selectionHoldId_, 1);

    /**
     * @tc.steps: step4. call HandleSelectionEvent
     */
    PointF point = PointF(0.0, 0.0);
    TouchEvent rawTouchEvent;
    rawTouchEvent.sourceType = SourceType::MOUSE;
    rawTouchEvent.type = TouchType::DOWN;
    content.HandleSelectionEvent(point, rawTouchEvent);
    EXPECT_EQ(content.selectionHoldId_, 1);
}

/**
 * @tc.name: IsTouchInHandleLevelOverlayArea001
 * @tc.desc: test select_content_overlay_manager.cpp IsTouchInHandleLevelOverlayArea
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestTwoNg, IsTouchInHandleLevelOverlayArea001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init SelectContentOverlayManager
     */
    Init();
    auto content = SelectContentOverlayManager(root_);
    SelectOverlayInfo selectInfo;
    selectInfo.enableHandleLevel = true;
    selectInfo.menuInfo.showCut = true;

    /**
     * @tc.steps: step2. CreateSelectOverlayNode
     */
    content.shareOverlayInfo_ = std::make_shared<SelectOverlayInfo>(selectInfo);
    ASSERT_NE(content.shareOverlayInfo_, nullptr);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(content.shareOverlayInfo_);
    ASSERT_NE(frameNode, nullptr);
    content.menuNode_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    ASSERT_NE(content.menuNode_.Upgrade(), nullptr);

    /**
     * @tc.steps: step3. call IsTouchInHandleLevelOverlayArea
     */
    content.IsTouchInHandleLevelOverlayArea(PointF(0.0, 0.0));
    ASSERT_NE(content.menuNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: IsTouchInHandleLevelOverlayArea002
 * @tc.desc: test select_content_overlay_manager.cpp IsTouchInHandleLevelOverlayArea
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestTwoNg, IsTouchInHandleLevelOverlayArea002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init SelectContentOverlayManager
     */
    Init();
    auto content = SelectContentOverlayManager(root_);
    SelectOverlayInfo selectInfo;
    selectInfo.enableHandleLevel = true;
    selectInfo.menuInfo.showCut = true;

    /**
     * @tc.steps: step2. CreateSelectOverlayNode
     */
    content.shareOverlayInfo_ = std::make_shared<SelectOverlayInfo>(selectInfo);
    ASSERT_NE(content.shareOverlayInfo_, nullptr);
    auto handleNode =
        SelectOverlayNode::CreateSelectOverlayNode(content.shareOverlayInfo_, SelectOverlayMode::HANDLE_ONLY);
    ASSERT_NE(handleNode, nullptr);
    content.handleNode_ = AceType::WeakClaim(AceType::RawPtr(handleNode));
    ASSERT_NE(content.handleNode_.Upgrade(), nullptr);

    /**
     * @tc.steps: step3. call IsTouchInHandleLevelOverlayArea
     */
    content.IsTouchInHandleLevelOverlayArea(PointF(0.0, 0.0));
    ASSERT_NE(content.handleNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: MarkSelectOverlayDirty001
 * @tc.desc: test select_content_overlay_manager.cpp MarkSelectOverlayDirty
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestTwoNg, MarkSelectOverlayDirty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init SelectContentOverlayManager
     */
    Init();
    auto content = SelectContentOverlayManager(root_);
    SelectOverlayInfo selectInfo;
    selectInfo.enableHandleLevel = false;
    selectInfo.menuInfo.showCut = true;
    content.shareOverlayInfo_ = std::make_shared<SelectOverlayInfo>(selectInfo);
    ASSERT_NE(content.shareOverlayInfo_, nullptr);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(content.shareOverlayInfo_);
    ASSERT_NE(frameNode, nullptr);
    content.selectOverlayNode_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    ASSERT_NE(content.selectOverlayNode_.Upgrade(), nullptr);

    /**
     * @tc.steps: step2. mount menuNode to root node
     */
    frameNode->SetParent(root_);

    /**
     * @tc.steps: step3. call MarkSelectOverlayDirty
     */
    content.MarkSelectOverlayDirty(PROPERTY_UPDATE_MEASURE_SELF);
    ASSERT_NE(content.selectOverlayNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: MarkSelectOverlayDirty002
 * @tc.desc: test select_content_overlay_manager.cpp MarkSelectOverlayDirty
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestTwoNg, MarkSelectOverlayDirty002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init SelectContentOverlayManager
     */
    Init();
    auto content = SelectContentOverlayManager(root_);
    SelectOverlayInfo selectInfo;
    selectInfo.enableHandleLevel = false;
    selectInfo.menuInfo.showCut = true;
    content.shareOverlayInfo_ = std::make_shared<SelectOverlayInfo>(selectInfo);
    ASSERT_NE(content.shareOverlayInfo_, nullptr);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(content.shareOverlayInfo_);
    ASSERT_NE(frameNode, nullptr);
    content.selectOverlayNode_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    ASSERT_NE(content.selectOverlayNode_.Upgrade(), nullptr);

    /**
     * @tc.steps: step2. call MarkSelectOverlayDirty
     */
    content.MarkSelectOverlayDirty(PROPERTY_UPDATE_MEASURE_SELF);
    ASSERT_NE(content.selectOverlayNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: CloseWithOverlayId001
 * @tc.desc: test select_content_overlay_manager.cpp CloseWithOverlayId
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestTwoNg, CloseWithOverlayId001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init SelectContentOverlayManager
     */
    Init();
    auto content = SelectContentOverlayManager(root_);
    auto holder = AceType::MakeRefPtr<SelectOverlayHolder>();
    content.SetHolder(holder);
    SelectOverlayInfo selectInfo;
    selectInfo.enableHandleLevel = false;
    selectInfo.menuInfo.showCut = true;
    content.shareOverlayInfo_ = std::make_shared<SelectOverlayInfo>(selectInfo);
    ASSERT_NE(content.shareOverlayInfo_, nullptr);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(content.shareOverlayInfo_);
    ASSERT_NE(frameNode, nullptr);
    content.selectOverlayNode_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    ASSERT_NE(content.selectOverlayNode_.Upgrade(), nullptr);

    /**
     * @tc.steps: step2. mount menuNode to root node
     */
    frameNode->SetParent(root_);

    /**
     * @tc.steps: step3. call CloseWithOverlayId
     */
    content.CloseWithOverlayId(frameNode->GetId(), CloseReason::CLOSE_REASON_NORMAL, true);
    EXPECT_EQ(content.selectionHoldId_, -1);
}

/**
 * @tc.name: CloseWithOverlayId002
 * @tc.desc: test select_content_overlay_manager.cpp CloseWithOverlayId
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestTwoNg, CloseWithOverlayId002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init SelectContentOverlayManager
     */
    Init();
    auto content = SelectContentOverlayManager(root_);
    auto holder = AceType::MakeRefPtr<SelectOverlayHolder>();
    content.SetHolder(holder);
    SelectOverlayInfo selectInfo;
    selectInfo.enableHandleLevel = true;
    selectInfo.menuInfo.showCut = true;
    content.shareOverlayInfo_ = std::make_shared<SelectOverlayInfo>(selectInfo);
    ASSERT_NE(content.shareOverlayInfo_, nullptr);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(content.shareOverlayInfo_);
    ASSERT_NE(frameNode, nullptr);
    content.menuNode_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    ASSERT_NE(content.menuNode_.Upgrade(), nullptr);

    /**
     * @tc.steps: step2. mount menuNode to root node
     */
    frameNode->SetParent(root_);

    /**
     * @tc.steps: step3. call CloseWithOverlayId
     */
    content.CloseWithOverlayId(frameNode->GetId(), CloseReason::CLOSE_REASON_NORMAL, true);
    EXPECT_EQ(content.selectionHoldId_, -1);
}

/**
 * @tc.name: ConvertPointRelativeToNode001
 * @tc.desc: test select_content_overlay_manager.cpp ConvertPointRelativeToNode
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestTwoNg, ConvertPointRelativeToNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init SelectContentOverlayManager
     */
    Init();
    auto content = SelectContentOverlayManager(root_);
    SelectOverlayInfo selectInfo;
    selectInfo.enableHandleLevel = true;
    selectInfo.menuInfo.showCut = true;
    content.shareOverlayInfo_ = std::make_shared<SelectOverlayInfo>(selectInfo);
    ASSERT_NE(content.shareOverlayInfo_, nullptr);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(content.shareOverlayInfo_);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. mount menuNode to root node
     */
    frameNode->SetParent(root_);

    /**
     * @tc.steps: step3. call ConvertPointRelativeToNode
     */
    PointF point = PointF(0.0, 0.0);
    content.ConvertPointRelativeToNode(frameNode, point);
    EXPECT_EQ(content.selectionHoldId_, -1);
}

/**
 * @tc.name: ConvertPointRelativeToNode002
 * @tc.desc: test select_content_overlay_manager.cpp ConvertPointRelativeToNode
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestTwoNg, ConvertPointRelativeToNode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init SelectContentOverlayManager
     */
    Init();
    auto content = SelectContentOverlayManager(root_);
    SelectOverlayInfo selectInfo;
    selectInfo.enableHandleLevel = true;
    selectInfo.menuInfo.showCut = true;
    content.shareOverlayInfo_ = std::make_shared<SelectOverlayInfo>(selectInfo);
    ASSERT_NE(content.shareOverlayInfo_, nullptr);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(content.shareOverlayInfo_);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. mount menuNode to root node
     */
    frameNode->SetParent(root_);

    /**
     * @tc.steps: step3. call ConvertPointRelativeToNode
     */
    PointF point = PointF(0.0, 0.0);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    ASSERT_NE(pipeline, nullptr);
    pipeline->postEventManager_ = AceType::MakeRefPtr<PostEventManager>();
    pipeline->postEventManager_->targetNode_ = root_;
    content.ConvertPointRelativeToNode(frameNode, point);
    EXPECT_EQ(content.selectionHoldId_, -1);
}

/**
 * @tc.name: ConvertPointRelativeToNode003
 * @tc.desc: test select_content_overlay_manager.cpp ConvertPointRelativeToNode
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestTwoNg, ConvertPointRelativeToNode003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init SelectContentOverlayManager
     */
    Init();
    auto content = SelectContentOverlayManager(root_);
    SelectOverlayInfo selectInfo;
    selectInfo.enableHandleLevel = true;
    selectInfo.menuInfo.showCut = true;
    content.shareOverlayInfo_ = std::make_shared<SelectOverlayInfo>(selectInfo);
    ASSERT_NE(content.shareOverlayInfo_, nullptr);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(content.shareOverlayInfo_);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. mount menuNode to root node
     */
    frameNode->SetParent(root_);

    /**
     * @tc.steps: step3. call ConvertPointRelativeToNode
     */
    PointF point = PointF(0.0, 0.0);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    pipeline = nullptr;
    content.ConvertPointRelativeToNode(frameNode, point);
    EXPECT_EQ(content.selectionHoldId_, -1);
}

/**
 * @tc.name: ConvertPointRelativeToNode004
 * @tc.desc: test select_content_overlay_manager.cpp ConvertPointRelativeToNode
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestTwoNg, ConvertPointRelativeToNode004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init SelectContentOverlayManager
     */
    Init();
    auto content = SelectContentOverlayManager(root_);
    SelectOverlayInfo selectInfo;
    selectInfo.enableHandleLevel = true;
    selectInfo.menuInfo.showCut = true;
    content.shareOverlayInfo_ = std::make_shared<SelectOverlayInfo>(selectInfo);
    ASSERT_NE(content.shareOverlayInfo_, nullptr);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(content.shareOverlayInfo_);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. mount menuNode to root node
     */
    frameNode->SetParent(root_);

    /**
     * @tc.steps: step3. call ConvertPointRelativeToNode
     */
    PointF point = PointF(0.0, 0.0);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    ASSERT_NE(pipeline, nullptr);
    pipeline->postEventManager_ = AceType::MakeRefPtr<PostEventManager>();
    pipeline->postEventManager_->targetNode_ = nullptr;
    content.ConvertPointRelativeToNode(frameNode, point);
    EXPECT_EQ(content.selectionHoldId_, -1);
}

/**
 * @tc.name: IsTouchInNormalSelectOverlayArea001
 * @tc.desc: test select_content_overlay_manager.cpp IsTouchInNormalSelectOverlayArea
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestTwoNg, IsTouchInNormalSelectOverlayArea001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init SelectContentOverlayManager
     */
    Init();
    auto content = SelectContentOverlayManager(root_);
    SelectOverlayInfo selectInfo;
    selectInfo.enableHandleLevel = false;
    selectInfo.menuInfo.showCut = true;
    content.shareOverlayInfo_ = std::make_shared<SelectOverlayInfo>(selectInfo);
    ASSERT_NE(content.shareOverlayInfo_, nullptr);

    /**
     * @tc.steps: step2. CreateSelectOverlayNode
     */
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(content.shareOverlayInfo_);
    ASSERT_NE(frameNode, nullptr);
    content.selectOverlayNode_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    ASSERT_NE(content.selectOverlayNode_.Upgrade(), nullptr);

    /**
     * @tc.steps: step3. call IsTouchInNormalSelectOverlayArea
     */
    content.IsTouchInNormalSelectOverlayArea(PointF(0.0, 0.0));
    ASSERT_NE(content.selectOverlayNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: IsTouchInNormalSelectOverlayArea002
 * @tc.desc: test select_content_overlay_manager.cpp IsTouchInNormalSelectOverlayArea
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestTwoNg, IsTouchInNormalSelectOverlayArea002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init SelectContentOverlayManager
     */
    Init();
    auto content = SelectContentOverlayManager(root_);
    SelectOverlayInfo selectInfo;
    selectInfo.isUsingMouse = true;
    selectInfo.enableHandleLevel = false;
    selectInfo.menuInfo.showCut = true;
    content.shareOverlayInfo_ = std::make_shared<SelectOverlayInfo>(selectInfo);
    ASSERT_NE(content.shareOverlayInfo_, nullptr);

    /**
     * @tc.steps: step2. CreateSelectOverlayNode
     */
    auto wrapperNode_ = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(1));
    ASSERT_NE(wrapperNode_, nullptr);
    content.selectOverlayNode_ = AceType::WeakClaim(AceType::RawPtr(wrapperNode_));
    ASSERT_NE(content.selectOverlayNode_.Upgrade(), nullptr);

    /**
     * @tc.steps: step3. call IsTouchInNormalSelectOverlayArea
     */
    content.IsTouchInNormalSelectOverlayArea(PointF(0.0, 0.0));
    ASSERT_NE(content.selectOverlayNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: GetHandleOverlayNode001
 * @tc.desc: test select_content_overlay_manager.cpp GetHandleOverlayNode
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestTwoNg, GetHandleOverlayNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init SelectContentOverlayManager
     */
    Init();
    auto content = SelectContentOverlayManager(root_);
    SelectOverlayInfo selectInfo;
    selectInfo.enableHandleLevel = true;
    selectInfo.menuInfo.showCut = true;

    /**
     * @tc.steps: step2. CreateSelectOverlayNode
     */
    content.shareOverlayInfo_ = std::make_shared<SelectOverlayInfo>(selectInfo);
    ASSERT_NE(content.shareOverlayInfo_, nullptr);
    auto handleNode =
        SelectOverlayNode::CreateSelectOverlayNode(content.shareOverlayInfo_, SelectOverlayMode::HANDLE_ONLY);
    ASSERT_NE(handleNode, nullptr);
    content.handleNode_ = AceType::WeakClaim(AceType::RawPtr(handleNode));
    ASSERT_NE(content.handleNode_.Upgrade(), nullptr);

    /**
     * @tc.steps: step3. call GetHandleOverlayNode
     */
    auto weakHandleNode = content.GetHandleOverlayNode();
    ASSERT_NE(weakHandleNode, nullptr);
}

/**
 * @tc.name: MarkHandleDirtyNode001
 * @tc.desc: test select_content_overlay_manager.cpp MarkHandleDirtyNode
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestTwoNg, MarkHandleDirtyNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init SelectContentOverlayManager
     */
    Init();
    auto content = SelectContentOverlayManager(root_);
    SelectOverlayInfo selectInfo;
    selectInfo.enableHandleLevel = true;
    selectInfo.menuInfo.showCut = true;
    selectInfo.isUseOverlayNG = true;

    /**
     * @tc.steps: step2. CreateSelectOverlayNode
     */
    content.shareOverlayInfo_ = std::make_shared<SelectOverlayInfo>(selectInfo);
    ASSERT_NE(content.shareOverlayInfo_, nullptr);
    auto handleNode =
        SelectOverlayNode::CreateSelectOverlayNode(content.shareOverlayInfo_, SelectOverlayMode::HANDLE_ONLY);
    ASSERT_NE(handleNode, nullptr);
    content.handleNode_ = AceType::WeakClaim(AceType::RawPtr(handleNode));
    ASSERT_NE(content.handleNode_.Upgrade(), nullptr);

    /**
     * @tc.steps: step3. call MarkHandleDirtyNode
     */
    content.MarkHandleDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    ASSERT_NE(content.handleNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: UpdateRightClickSubWindowMenuProps001
 * @tc.desc: test select_content_overlay_manager.cpp UpdateRightClickSubWindowMenuProps
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestTwoNg, UpdateRightClickSubWindowMenuProps001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init SelectContentOverlayManager
     */
    Init();
    auto content = SelectContentOverlayManager(root_);
    SelectOverlayInfo selectInfo;
    selectInfo.isUsingMouse = true;
    selectInfo.enableHandleLevel = false;
    selectInfo.menuInfo.showCut = true;
    content.shareOverlayInfo_ = std::make_shared<SelectOverlayInfo>(selectInfo);
    ASSERT_NE(content.shareOverlayInfo_, nullptr);

    /**
     * @tc.steps: step2. CreateSelectOverlayNode
     */
    auto wrapperNode_ = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(1));
    ASSERT_NE(wrapperNode_, nullptr);
    content.selectOverlayNode_ = AceType::WeakClaim(AceType::RawPtr(wrapperNode_));
    auto selectoverlayNode = content.selectOverlayNode_.Upgrade();
    ASSERT_NE(selectoverlayNode, nullptr);

    /**
     * @tc.steps: step3. call UpdateRightClickSubWindowMenuProps
     */
    content.UpdateRightClickSubWindowMenuProps(selectoverlayNode);
    ASSERT_NE(content.selectOverlayNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: FocusFirstFocusableChildInMenu001
 * @tc.desc: test select_content_overlay_manager.cpp FocusFirstFocusableChildInMenu
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestTwoNg, FocusFirstFocusableChildInMenu001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init SelectContentOverlayManager
     */
    Init();
    auto content = SelectContentOverlayManager(root_);
    SelectOverlayInfo selectInfo;
    selectInfo.enableHandleLevel = true;
    selectInfo.menuInfo.showCut = true;
    
    content.shareOverlayInfo_ = std::make_shared<SelectOverlayInfo>(selectInfo);
    ASSERT_NE(content.shareOverlayInfo_, nullptr);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(content.shareOverlayInfo_);
    ASSERT_NE(frameNode, nullptr);
    content.menuNode_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    ASSERT_NE(content.menuNode_.Upgrade(), nullptr);
    content.FocusFirstFocusableChildInMenu();
    EXPECT_TRUE(frameNode->GetContext()->taskScheduler_->afterLayoutCallbacksInImplicitAnimationTask_.empty());
    EXPECT_TRUE(frameNode->GetContext()->taskScheduler_->afterLayoutTasks_.empty());
}

/**
 * @tc.name: DestroySelectOverlayNode
 * @tc.desc: test select_content_overlay_manager.cpp DestroySelectOverlayNode
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestTwoNg, DestroySelectOverlayNode, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init SelectContentOverlayManager
     */
    Init();
    auto content = SelectContentOverlayManager(root_);
    SelectOverlayInfo selectInfo;
    content.shareOverlayInfo_ = std::make_shared<SelectOverlayInfo>(selectInfo);
    ASSERT_NE(content.shareOverlayInfo_, nullptr);

    /**
     * @tc.steps: step2. CreateSelectOverlayNode
     */
    auto menuNode =
        SelectOverlayNode::CreateSelectOverlayNode(content.shareOverlayInfo_, SelectOverlayMode::MENU_ONLY);
    ASSERT_NE(menuNode, nullptr);
    menuNode->MountToParent(root_);
    /**
     * @tc.steps: step3. call DestroySelectOverlayNode
     */
    content.DestroySelectOverlayNode(menuNode);
    EXPECT_FALSE(menuNode->IsInDestroying());
}

/**
 * @tc.name: DestroySelectOverlayNode001
 * @tc.desc: test select_content_overlay_manager.cpp DestroySelectOverlayNode
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestTwoNg, DestroySelectOverlayNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init SelectContentOverlayManager
     */
    Init();
    auto content = SelectContentOverlayManager(root_);
    SelectOverlayInfo selectInfo;
    content.shareOverlayInfo_ = std::make_shared<SelectOverlayInfo>(selectInfo);
    ASSERT_NE(content.shareOverlayInfo_, nullptr);

    /**
     * @tc.steps: step2. CreateSelectOverlayNode
     */
    auto menuNode = SelectOverlayNode::CreateSelectOverlayNode(content.shareOverlayInfo_, SelectOverlayMode::MENU_ONLY);
    ASSERT_NE(menuNode, nullptr);
    menuNode->MountToParent(root_);
    auto selectOverlayPattern = menuNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(selectOverlayPattern, nullptr);
    selectOverlayPattern->SetIsMenuShowInSubWindow(true);

    /**
     * @tc.steps: step3. call DestroySelectOverlayNode
     */
    content.DestroySelectOverlayNode(menuNode);
    EXPECT_FALSE(menuNode->IsInDestroying());
}

/**
 * @tc.name: DestroySelectOverlayNode002
 * @tc.desc: test select_content_overlay_manager.cpp DestroySelectOverlayNode
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestTwoNg, DestroySelectOverlayNode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init SelectContentOverlayManager
     */
    Init();
    auto content = SelectContentOverlayManager(root_);
    SelectOverlayInfo selectInfo;
    selectInfo.enableHandleLevel = false;
    selectInfo.isUsingMouse = true;
    selectInfo.isUseOverlayNG = true;

    content.shareOverlayInfo_ = std::make_shared<SelectOverlayInfo>(selectInfo);
    ASSERT_NE(content.shareOverlayInfo_, nullptr);

    /**
     * @tc.steps: step2. CreateSelectOverlayNode
     */
    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuWrapperPattern>(1));
    ASSERT_NE(menuNode, nullptr);
    menuNode->MountToParent(root_);
    auto menuWrapperPattern = menuNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern, nullptr);
    menuWrapperPattern->SetIsSelectOverlaySubWindowWrapper(true);

    /**
     * @tc.steps: step3. call DestroySelectOverlayNode
     */
    content.DestroySelectOverlayNode(menuNode);
    EXPECT_TRUE(content.shareOverlayInfo_->isUsingMouse);
}

/**
 * @tc.name: CreateSelectOverlayNode001
 * @tc.desc: test SelectOverlayNode.cpp CreateSelectOverlayNode
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayManagerTestTwoNg, CreateSelectOverlayNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init SelectContentOverlayManager
     */
    Init();
    auto content = SelectContentOverlayManager(root_);
    SelectOverlayInfo selectInfo;
    selectInfo.enableHandleLevel = true;
    selectInfo.menuInfo.showCut = true;
    selectInfo.menuInfo.showCopyAll = true;
    selectInfo.menuInfo.showAIWrite = true;

    /**
     * @tc.steps: step2. CreateSelectOverlayNode
     */
    content.shareOverlayInfo_ = std::make_shared<SelectOverlayInfo>(selectInfo);
    ASSERT_NE(content.shareOverlayInfo_, nullptr);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(content.shareOverlayInfo_);
    ASSERT_NE(frameNode, nullptr);
    auto size = frameNode->GetChildren().size();
    EXPECT_EQ(size, 1);
}
} // namespace OHOS::Ace::NG