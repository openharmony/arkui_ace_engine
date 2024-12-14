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
}