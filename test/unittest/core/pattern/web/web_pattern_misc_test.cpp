/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include <cstddef>
#include <gmock/gmock.h>
#include <list>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#define protected public
#define private public
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/pattern/web/web_pattern.h"
#undef private
#undef protected

#include "base/json/json_util.h"
#include "core/components/web/resource/web_delegate.h"
#include "core/components/web/web_property.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/web/web_dom_document.h"
#include "core/components_ng/pattern/web/view_data_common.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/mouse_event.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/base/utils/system_properties.h"
#include "nweb.h"
#include "nweb_command_action_info.h"
#include "nweb_handler.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::NWeb;

namespace OHOS::Ace::NG {

class WebPatternMiscTest : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
    void SetUp() override
    {
        MockPipelineContext::SetUp();
    }
    void TearDown() override
    {
        ViewStackProcessor::GetInstance()->ClearStack();
        MockPipelineContext::TearDown();
    }
};

namespace {
RefPtr<WebPattern> CreateWebPattern()
{
    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_RETURN(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    CHECK_NULL_RETURN(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    return webPattern;
}

void SetupDelegate(const RefPtr<WebPattern>& webPattern)
{
    if (!webPattern) {
        return;
    }
    auto pipelineContext = MockPipelineContext::GetCurrent();
    if (!pipelineContext) {
        return;
    }
    pipelineContext->SetupRootElement();
    auto context = AceType::WeakClaim(AceType::RawPtr(pipelineContext));
    auto delegate = AceType::MakeRefPtr<WebDelegate>(context, nullptr, "web", 0);
    webPattern->delegate_ = delegate;
}

// Build a JSON object whose single field is a string, returning the root (kept alive so the
// returned child stays valid). Caller obtains the field via root->GetChild(). If the constructed
// JSON is malformed (e.g. key/value contains quotes) and parsing yields null, a safe empty object
// is returned so the caller's root->GetChild() never dereferences a null pointer.
std::unique_ptr<JsonValue> MakeStringFieldRoot(const std::string& key, const std::string& value)
{
    auto root = JsonUtil::ParseJsonString("{\"" + key + "\":\"" + value + "\"}");
    return root ? std::move(root) : JsonUtil::Create(true);
}

// Build a JSON object whose single field is a bool, returning the root. Falls back to a safe
// empty object if parsing yields null (see MakeStringFieldRoot).
std::unique_ptr<JsonValue> MakeBoolFieldRoot(const std::string& key, bool value)
{
    auto root = JsonUtil::ParseJsonString("{\"" + key + "\":" + (value ? "true" : "false") + "}");
    return root ? std::move(root) : JsonUtil::Create(true);
}
} // namespace

HWTEST_F(WebPatternMiscTest, OnInActive001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->isActive_ = true;
    SetupDelegate(webPattern);
    webPattern->OnInActive();
    EXPECT_FALSE(webPattern->isActive_);
    EXPECT_FALSE(webPattern->GetActiveStatus());
#endif
}

HWTEST_F(WebPatternMiscTest, OnActive001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->isActive_ = false;
    SetupDelegate(webPattern);
    webPattern->OnActive();
    EXPECT_TRUE(webPattern->isActive_);
    EXPECT_TRUE(webPattern->GetActiveStatus());
#endif
}

HWTEST_F(WebPatternMiscTest, GetActiveStatus001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->isActive_ = true;
    EXPECT_TRUE(webPattern->GetActiveStatus());
    webPattern->isActive_ = false;
    EXPECT_FALSE(webPattern->GetActiveStatus());
#endif
}

HWTEST_F(WebPatternMiscTest, OnVisibleAreaChange001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    SetupDelegate(webPattern);
    webPattern->isVisible_ = true;
    webPattern->OnVisibleAreaChange(true);
    EXPECT_TRUE(webPattern->isVisible_);
#endif
}

HWTEST_F(WebPatternMiscTest, OnVisibleAreaChange002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    SetupDelegate(webPattern);
    webPattern->isVisible_ = true;
    webPattern->isActive_ = true;
    webPattern->OnVisibleAreaChange(false);
    EXPECT_FALSE(webPattern->isVisible_);
    EXPECT_FALSE(webPattern->isActive_);
#endif
}

HWTEST_F(WebPatternMiscTest, OnVisibleAreaChange003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    SetupDelegate(webPattern);
    webPattern->isVisible_ = false;
    webPattern->isActive_ = false;
    webPattern->OnVisibleAreaChange(true);
    EXPECT_TRUE(webPattern->isVisible_);
    EXPECT_TRUE(webPattern->isActive_);
#endif
}

HWTEST_F(WebPatternMiscTest, OnVisibleAreaChange004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    SetupDelegate(webPattern);
    webPattern->isVisible_ = false;
    webPattern->isActive_ = false;
    webPattern->isVisibleActiveEnable_ = false;
    webPattern->OnVisibleAreaChange(true);
    EXPECT_TRUE(webPattern->isVisible_);
    EXPECT_FALSE(webPattern->isActive_);
#endif
}

HWTEST_F(WebPatternMiscTest, OnVisibleAreaChange005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->isVisible_ = true;
    webPattern->isActive_ = true;
    webPattern->OnVisibleAreaChange(false);
    EXPECT_FALSE(webPattern->isVisible_);
#endif
}

HWTEST_F(WebPatternMiscTest, UpdateBackgroundColorRightNow001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    SetupDelegate(webPattern);
    auto host = webPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto renderContext = host->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    webPattern->UpdateBackgroundColorRightNow(0xFF000000);
#endif
}

HWTEST_F(WebPatternMiscTest, UpdateBackgroundColorRightNow002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = AceType::MakeRefPtr<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->UpdateBackgroundColorRightNow(0xFF000000);
#endif
}

HWTEST_F(WebPatternMiscTest, OnNotifyMemoryLevel001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    SetupDelegate(webPattern);
    webPattern->isMemoryLevelEnable_ = false;
    webPattern->OnNotifyMemoryLevel(5);
    // Memory-level notify is disabled -> early return, state unchanged.
    EXPECT_FALSE(webPattern->isMemoryLevelEnable_);
    ASSERT_NE(webPattern->delegate_, nullptr);
#endif
}

HWTEST_F(WebPatternMiscTest, OnNotifyMemoryLevel002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    SetupDelegate(webPattern);
    webPattern->isMemoryLevelEnable_ = true;
    webPattern->OnNotifyMemoryLevel(5);
    // Enabled + delegate present -> delegate_->NotifyMemoryLevel invoked (mock no-op), state unchanged.
    EXPECT_TRUE(webPattern->isMemoryLevelEnable_);
    ASSERT_NE(webPattern->delegate_, nullptr);
#endif
}

HWTEST_F(WebPatternMiscTest, OnNotifyMemoryLevel003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->isMemoryLevelEnable_ = true;
    webPattern->OnNotifyMemoryLevel(5);
    // Enabled but no delegate -> CHECK_NULL_VOID(delegate_) early return.
    EXPECT_TRUE(webPattern->isMemoryLevelEnable_);
    EXPECT_EQ(webPattern->delegate_, nullptr);
#endif
}

HWTEST_F(WebPatternMiscTest, GetWebId001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    SetupDelegate(webPattern);
    auto result = webPattern->GetWebId();
    EXPECT_EQ(result, 0);
#endif
}

HWTEST_F(WebPatternMiscTest, GetWebId002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    auto result = webPattern->GetWebId();
    EXPECT_EQ(result, -1);
#endif
}

HWTEST_F(WebPatternMiscTest, GetDefaultBackgroundColor001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    auto color = webPattern->GetDefaultBackgroundColor();
    EXPECT_EQ(color, Color::WHITE);
#endif
}

HWTEST_F(WebPatternMiscTest, EnableScrollDirectionalLock001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->EnableScrollDirectionalLock(true, ScrollDirectionalLockType::ALL);
    EXPECT_TRUE(webPattern->isDirectionalLockEnabled_);
    EXPECT_EQ(webPattern->scrollDirectionalLockType_, ScrollDirectionalLockType::ALL);
#endif
}

HWTEST_F(WebPatternMiscTest, EnableScrollDirectionalLock002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->EnableScrollDirectionalLock(false, ScrollDirectionalLockType::NESTED_SCROLL);
    EXPECT_FALSE(webPattern->isDirectionalLockEnabled_);
    EXPECT_EQ(webPattern->scrollDirectionalLockType_, ScrollDirectionalLockType::NESTED_SCROLL);
#endif
}

HWTEST_F(WebPatternMiscTest, OnNestedScroll001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->expectedScrollAxis_ = Axis::HORIZONTAL;
    webPattern->isScrollStarted_ = true;
    webPattern->isDirectionalLockEnabled_ = true;
    webPattern->scrollDirectionalLockType_ = ScrollDirectionalLockType::ALL;
    float x = 10.0f;
    float y = 10.0f;
    float xV = 5.0f;
    float yV = 5.0f;
    bool isAvailable = false;
    webPattern->OnNestedScroll(x, y, xV, yV, isAvailable);
    EXPECT_TRUE(isAvailable);
    EXPECT_EQ(y, 0.0f);
    EXPECT_EQ(yV, 0.0f);
    EXPECT_EQ(x, 10.0f);
#endif
}

HWTEST_F(WebPatternMiscTest, OnNestedScroll002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->expectedScrollAxis_ = Axis::VERTICAL;
    webPattern->isScrollStarted_ = true;
    webPattern->isDirectionalLockEnabled_ = true;
    webPattern->scrollDirectionalLockType_ = ScrollDirectionalLockType::ALL;
    float x = 10.0f;
    float y = 10.0f;
    float xV = 5.0f;
    float yV = 5.0f;
    bool isAvailable = false;
    webPattern->OnNestedScroll(x, y, xV, yV, isAvailable);
    EXPECT_TRUE(isAvailable);
    EXPECT_EQ(x, 0.0f);
    EXPECT_EQ(xV, 0.0f);
    EXPECT_EQ(y, 10.0f);
#endif
}

HWTEST_F(WebPatternMiscTest, OnNestedScroll003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->expectedScrollAxis_ = Axis::VERTICAL;
    webPattern->isScrollStarted_ = true;
    webPattern->isDirectionalLockEnabled_ = false;
    float x = 10.0f;
    float y = 10.0f;
    float xV = 5.0f;
    float yV = 5.0f;
    bool isAvailable = false;
    webPattern->OnNestedScroll(x, y, xV, yV, isAvailable);
    EXPECT_TRUE(isAvailable);
    EXPECT_EQ(x, 10.0f);
    EXPECT_EQ(y, 10.0f);
#endif
}

HWTEST_F(WebPatternMiscTest, OnNestedScroll004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->expectedScrollAxis_ = Axis::VERTICAL;
    webPattern->isScrollStarted_ = true;
    webPattern->isDirectionalLockEnabled_ = true;
    webPattern->scrollDirectionalLockType_ = ScrollDirectionalLockType::NESTED_SCROLL;
    float x = 10.0f;
    float y = 10.0f;
    float xV = 5.0f;
    float yV = 5.0f;
    bool isAvailable = false;
    webPattern->OnNestedScroll(x, y, xV, yV, isAvailable);
    EXPECT_TRUE(isAvailable);
    EXPECT_EQ(x, 10.0f);
    EXPECT_EQ(y, 10.0f);
#endif
}

HWTEST_F(WebPatternMiscTest, OnNestedScrollV2001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->expectedScrollAxis_ = Axis::HORIZONTAL;
    webPattern->isScrollStarted_ = true;
    webPattern->isDirectionalLockEnabled_ = true;
    webPattern->scrollDirectionalLockType_ = ScrollDirectionalLockType::ALL;
    float x = 10.0f;
    float y = 10.0f;
    webPattern->OnNestedScrollV2(x, y);
    EXPECT_EQ(y, 0.0f);
    EXPECT_EQ(x, 10.0f);
#endif
}

HWTEST_F(WebPatternMiscTest, OnNestedScrollV2002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->expectedScrollAxis_ = Axis::VERTICAL;
    webPattern->isScrollStarted_ = true;
    webPattern->isDirectionalLockEnabled_ = true;
    webPattern->scrollDirectionalLockType_ = ScrollDirectionalLockType::ALL;
    float x = 10.0f;
    float y = 10.0f;
    webPattern->OnNestedScrollV2(x, y);
    EXPECT_EQ(x, 0.0f);
    EXPECT_EQ(y, 10.0f);
#endif
}

HWTEST_F(WebPatternMiscTest, OnNestedScrollV2003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->expectedScrollAxis_ = Axis::VERTICAL;
    webPattern->isScrollStarted_ = true;
    webPattern->isDirectionalLockEnabled_ = false;
    float x = 10.0f;
    float y = 10.0f;
    webPattern->OnNestedScrollV2(x, y);
    EXPECT_EQ(x, 10.0f);
    EXPECT_EQ(y, 10.0f);
#endif
}

HWTEST_F(WebPatternMiscTest, UpdateImageOverlayStatus001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->imageOverlayStatus_ = ImageOverlayStatus::NONE;
    webPattern->UpdateImageOverlayStatus(ImageOverlayEvent::TOUCH_PRESS);
    EXPECT_EQ(webPattern->imageOverlayStatus_, ImageOverlayStatus::TOUCH_HOLD);
#endif
}

HWTEST_F(WebPatternMiscTest, UpdateImageOverlayStatus002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->imageOverlayStatus_ = ImageOverlayStatus::TOUCH_HOLD;
    webPattern->UpdateImageOverlayStatus(ImageOverlayEvent::TOUCH_PRESS);
    EXPECT_EQ(webPattern->imageOverlayStatus_, ImageOverlayStatus::TOUCH_HOLD);
#endif
}

HWTEST_F(WebPatternMiscTest, UpdateImageOverlayStatus003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->imageOverlayStatus_ = ImageOverlayStatus::TOUCH_HOLD;
    webPattern->UpdateImageOverlayStatus(ImageOverlayEvent::TOUCH_RELEASE);
    EXPECT_EQ(webPattern->imageOverlayStatus_, ImageOverlayStatus::NONE);
#endif
}

HWTEST_F(WebPatternMiscTest, UpdateImageOverlayStatus004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->imageOverlayStatus_ = ImageOverlayStatus::TOUCH_HOLD;
    webPattern->UpdateImageOverlayStatus(ImageOverlayEvent::CREATE_OVERLAY);
    EXPECT_EQ(webPattern->imageOverlayStatus_, ImageOverlayStatus::HOLD_CREATE);
#endif
}

HWTEST_F(WebPatternMiscTest, UpdateImageOverlayStatus005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->imageOverlayStatus_ = ImageOverlayStatus::NONE;
    webPattern->UpdateImageOverlayStatus(ImageOverlayEvent::CREATE_OVERLAY);
    EXPECT_EQ(webPattern->imageOverlayStatus_, ImageOverlayStatus::NONE);
#endif
}

HWTEST_F(WebPatternMiscTest, UpdateImageOverlayStatus006, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->imageOverlayStatus_ = ImageOverlayStatus::HOLD_CREATE;
    webPattern->UpdateImageOverlayStatus(ImageOverlayEvent::CREATE_OVERLAY_RELEASE);
    EXPECT_EQ(webPattern->imageOverlayStatus_, ImageOverlayStatus::TOUCH_HOLD);
#endif
}

HWTEST_F(WebPatternMiscTest, UpdateImageOverlayStatus007, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->imageOverlayStatus_ = ImageOverlayStatus::NONE;
    webPattern->UpdateImageOverlayStatus(ImageOverlayEvent::CREATE_OVERLAY_RELEASE);
    EXPECT_EQ(webPattern->imageOverlayStatus_, ImageOverlayStatus::NONE);
#endif
}

HWTEST_F(WebPatternMiscTest, CloseImageOverlaySelection001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->imageOverlayIsSelected_ = true;
    webPattern->isMouseEvent_ = false;
    auto result = webPattern->CloseImageOverlaySelection();
    EXPECT_TRUE(result);
#endif
}

HWTEST_F(WebPatternMiscTest, CloseImageOverlaySelection002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->imageOverlayIsSelected_ = false;
    webPattern->isMouseEvent_ = false;
    auto result = webPattern->CloseImageOverlaySelection();
    EXPECT_FALSE(result);
#endif
}

HWTEST_F(WebPatternMiscTest, CloseImageOverlaySelection003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->imageOverlayIsSelected_ = false;
    webPattern->isMouseEvent_ = true;
    auto result = webPattern->CloseImageOverlaySelection();
    EXPECT_TRUE(result);
#endif
}

HWTEST_F(WebPatternMiscTest, HideHandleAndQuickMenuIfNecessary001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->webSelectOverlay_ = nullptr;
    webPattern->HideHandleAndQuickMenuIfNecessary(true, false);
    // No overlay -> guard skips the delegate call, overlay stays null.
    EXPECT_EQ(webPattern->webSelectOverlay_, nullptr);
#endif
}

HWTEST_F(WebPatternMiscTest, ChangeVisibilityOfQuickMenu001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->webSelectOverlay_ = nullptr;
    webPattern->ChangeVisibilityOfQuickMenu();
    // No overlay -> CHECK_NULL_VOID early return, overlay stays null.
    EXPECT_EQ(webPattern->webSelectOverlay_, nullptr);
#endif
}

HWTEST_F(WebPatternMiscTest, IsQuickMenuShow001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->webSelectOverlay_ = nullptr;
    auto result = webPattern->IsQuickMenuShow();
    EXPECT_FALSE(result);
#endif
}

HWTEST_F(WebPatternMiscTest, OnEnableImageAnalyzerUpdate001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    SetupDelegate(webPattern);
    webPattern->overlayCreating_ = true;
    webPattern->OnEnableImageAnalyzerUpdate(true);
    // isEnabled=true -> DestroyAnalyzerOverlay is NOT called, so overlayCreating_ stays set.
    EXPECT_TRUE(webPattern->overlayCreating_);
    ASSERT_NE(webPattern->delegate_, nullptr);
#endif
}

HWTEST_F(WebPatternMiscTest, OnEnableImageAnalyzerUpdate002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    SetupDelegate(webPattern);
    webPattern->overlayCreating_ = true;
    webPattern->imageOverlayIsSelected_ = true;
    webPattern->OnEnableImageAnalyzerUpdate(false);
    // isEnabled=false -> DestroyAnalyzerOverlay resets overlay flags.
    EXPECT_FALSE(webPattern->overlayCreating_);
    EXPECT_FALSE(webPattern->imageOverlayIsSelected_);
    ASSERT_NE(webPattern->delegate_, nullptr);
#endif
}

HWTEST_F(WebPatternMiscTest, OnEnableImageAnalyzerUpdate003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->overlayCreating_ = true;
    webPattern->OnEnableImageAnalyzerUpdate(true);
    // isEnabled=true with no delegate -> DestroyAnalyzerOverlay is NOT called, flag stays set.
    EXPECT_TRUE(webPattern->overlayCreating_);
    EXPECT_EQ(webPattern->delegate_, nullptr);
#endif
}

HWTEST_F(WebPatternMiscTest, GetBufferSizeByDeviceType001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    auto size = webPattern->GetBufferSizeByDeviceType();
    EXPECT_GT(size, 0);
#endif
}

HWTEST_F(WebPatternMiscTest, PushOverlayInfo001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->PushOverlayInfo(10.0f, 20.0f, 1);
    webPattern->PushOverlayInfo(30.0f, 40.0f, 2);
    ASSERT_EQ(webPattern->touchOverlayInfo_.size(), 2u);
    auto it = webPattern->touchOverlayInfo_.begin();
    EXPECT_FLOAT_EQ(it->x, 10.0f);
    EXPECT_FLOAT_EQ(it->y, 20.0f);
    EXPECT_EQ(it->id, 1);
    std::advance(it, 1);
    EXPECT_FLOAT_EQ(it->x, 30.0f);
    EXPECT_FLOAT_EQ(it->y, 40.0f);
    EXPECT_EQ(it->id, 2);
#endif
}

HWTEST_F(WebPatternMiscTest, UpdateImageOverlayTouchInfo001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->overlayCreating_ = false;
    webPattern->UpdateImageOverlayTouchInfo(100, 200, TouchType::DOWN);
#endif
}

HWTEST_F(WebPatternMiscTest, UpdateImageOverlayTouchInfo002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->overlayCreating_ = false;
    webPattern->imageAnalyzerManager_ = nullptr;
    webPattern->UpdateImageOverlayTouchInfo(100, 200, TouchType::DOWN);
#endif
}

HWTEST_F(WebPatternMiscTest, GetCurrentLanguage001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    SetupDelegate(webPattern);
    auto result = webPattern->GetCurrentLanguage();
    EXPECT_EQ(result, "");
#endif
}

HWTEST_F(WebPatternMiscTest, GetCurrentLanguage002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    auto result = webPattern->GetCurrentLanguage();
    EXPECT_EQ(result, "");
#endif
}

HWTEST_F(WebPatternMiscTest, SendTranslateResult001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    SetupDelegate(webPattern);
    webPattern->SendTranslateResult(std::string("console.log('test')"));
    // delegate present -> delegate_->ExecuteTypeScript path taken.
    ASSERT_NE(webPattern->delegate_, nullptr);
#endif
}

HWTEST_F(WebPatternMiscTest, SendTranslateResult002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->SendTranslateResult(std::string("test"));
    // No delegate -> CHECK_NULL_VOID(delegate_) early return.
    EXPECT_EQ(webPattern->delegate_, nullptr);
#endif
}

HWTEST_F(WebPatternMiscTest, FormatIndex001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->content_ = u"hello";
    int32_t start = 5;
    int32_t end = 3;
    webPattern->FormatIndex(start, end);
    EXPECT_EQ(start, 3);
    EXPECT_EQ(end, 3);
#endif
}

HWTEST_F(WebPatternMiscTest, FormatIndex002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->content_ = u"hello";
    int32_t start = -2;
    int32_t end = 20;
    webPattern->FormatIndex(start, end);
    EXPECT_EQ(start, 0);
    EXPECT_EQ(end, 5);
#endif
}

HWTEST_F(WebPatternMiscTest, FormatIndex003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->content_ = u"hello world";
    int32_t start = 2;
    int32_t end = 7;
    webPattern->FormatIndex(start, end);
    EXPECT_EQ(start, 2);
    EXPECT_EQ(end, 7);
#endif
}

HWTEST_F(WebPatternMiscTest, SendPipEvent001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    SetupDelegate(webPattern);
    webPattern->SendPipEvent(1, 2, 3, 4);
    // delegate present -> delegate_->SendPipEvent path taken.
    ASSERT_NE(webPattern->delegate_, nullptr);
#endif
}

HWTEST_F(WebPatternMiscTest, SendPipEvent002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->SendPipEvent(1, 2, 3, 4);
    // No delegate -> 'if (delegate_)' guard skips the call.
    EXPECT_EQ(webPattern->delegate_, nullptr);
#endif
}

HWTEST_F(WebPatternMiscTest, IsRtl001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = AceType::MakeRefPtr<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    auto result = webPattern->IsRtl();
    EXPECT_FALSE(result);
#endif
}

HWTEST_F(WebPatternMiscTest, IsRtl002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    auto host = webPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto layoutProperty = host->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLayoutDirection(TextDirection::LTR);
    auto result = webPattern->IsRtl();
    EXPECT_FALSE(result);
#endif
}

HWTEST_F(WebPatternMiscTest, IsRtl003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    auto host = webPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto layoutProperty = host->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLayoutDirection(TextDirection::RTL);
    auto result = webPattern->IsRtl();
    EXPECT_TRUE(result);
#endif
}

HWTEST_F(WebPatternMiscTest, SnapshotTouchReporter001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto reporter = std::make_shared<SnapshotTouchReporter>();
    ASSERT_NE(reporter, nullptr);
    reporter->OnAppear();
    EXPECT_TRUE(reporter->appearTime_.has_value());
    EXPECT_NE(reporter->infos_, nullptr);
    reporter->OnClick();
    reporter->OnPan();
    reporter->OnDisappear();
    EXPECT_FALSE(reporter->appearTime_.has_value());
    EXPECT_EQ(reporter->infos_, nullptr);
#endif
}

HWTEST_F(WebPatternMiscTest, SnapshotTouchReporter002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto reporter = std::make_shared<SnapshotTouchReporter>();
    ASSERT_NE(reporter, nullptr);
    reporter->OnClick();
    EXPECT_EQ(reporter->infos_, nullptr);
#endif
}

HWTEST_F(WebPatternMiscTest, SnapshotTouchReporter003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto reporter = std::make_shared<SnapshotTouchReporter>();
    ASSERT_NE(reporter, nullptr);
    reporter->OnPan();
    EXPECT_EQ(reporter->infos_, nullptr);
#endif
}

HWTEST_F(WebPatternMiscTest, SnapshotTouchReporter004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto reporter = std::make_shared<SnapshotTouchReporter>();
    ASSERT_NE(reporter, nullptr);
    reporter->OnDisappear();
    EXPECT_FALSE(reporter->appearTime_.has_value());
#endif
}

HWTEST_F(WebPatternMiscTest, CheckVisible001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = AceType::MakeRefPtr<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    auto result = webPattern->CheckVisible();
    EXPECT_FALSE(result);
#endif
}

HWTEST_F(WebPatternMiscTest, RemoveDataListNode001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->dataListNodeId_ = std::nullopt;
    webPattern->RemoveDataListNode();
    // No data list node id -> early return, id stays unset.
    EXPECT_FALSE(webPattern->dataListNodeId_.has_value());
#endif
}

HWTEST_F(WebPatternMiscTest, OnNestedScrollV2004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->expectedScrollAxis_ = Axis::HORIZONTAL;
    webPattern->isScrollStarted_ = false;
    webPattern->isDirectionalLockEnabled_ = true;
    webPattern->scrollDirectionalLockType_ = ScrollDirectionalLockType::ALL;
    float x = 10.0f;
    float y = 10.0f;
    webPattern->OnNestedScrollV2(x, y);
    EXPECT_EQ(x, 10.0f);
    EXPECT_EQ(y, 10.0f);
#endif
}

HWTEST_F(WebPatternMiscTest, OnNestedScroll005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->expectedScrollAxis_ = Axis::HORIZONTAL;
    webPattern->isScrollStarted_ = false;
    webPattern->isDirectionalLockEnabled_ = true;
    webPattern->scrollDirectionalLockType_ = ScrollDirectionalLockType::ALL;
    float x = 10.0f;
    float y = 10.0f;
    float xV = 5.0f;
    float yV = 5.0f;
    bool isAvailable = false;
    webPattern->OnNestedScroll(x, y, xV, yV, isAvailable);
    EXPECT_TRUE(isAvailable);
    EXPECT_EQ(x, 10.0f);
    EXPECT_EQ(y, 10.0f);
#endif
}

HWTEST_F(WebPatternMiscTest, UpdateImageOverlayStatus008, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->imageOverlayStatus_ = ImageOverlayStatus::HOLD_CREATE;
    webPattern->UpdateImageOverlayStatus(ImageOverlayEvent::TOUCH_PRESS);
    EXPECT_EQ(webPattern->imageOverlayStatus_, ImageOverlayStatus::HOLD_CREATE);
#endif
}

HWTEST_F(WebPatternMiscTest, UpdateImageOverlayStatus009, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->imageOverlayStatus_ = ImageOverlayStatus::HOLD_CREATE;
    webPattern->UpdateImageOverlayStatus(ImageOverlayEvent::TOUCH_RELEASE);
    EXPECT_EQ(webPattern->imageOverlayStatus_, ImageOverlayStatus::NONE);
#endif
}

HWTEST_F(WebPatternMiscTest, OnEnableImageAnalyzerUpdate004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->overlayCreating_ = true;
    webPattern->imageOverlayIsSelected_ = true;
    webPattern->OnEnableImageAnalyzerUpdate(false);
    // isEnabled=false with no delegate -> DestroyAnalyzerOverlay still resets overlay flags.
    EXPECT_FALSE(webPattern->overlayCreating_);
    EXPECT_FALSE(webPattern->imageOverlayIsSelected_);
    EXPECT_EQ(webPattern->delegate_, nullptr);
#endif
}

HWTEST_F(WebPatternMiscTest, PushOverlayInfo002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    EXPECT_EQ(webPattern->touchOverlayInfo_.size(), 0u);
    webPattern->PushOverlayInfo(0.0f, 0.0f, 0);
    EXPECT_EQ(webPattern->touchOverlayInfo_.size(), 1u);
#endif
}

// Covers GetAndUpdateCursorStyleInfo 'case CT_LOCK' branch (previously never hit).
HWTEST_F(WebPatternMiscTest, GetAndUpdateCursorStyleInfo001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->isMouseLocked_ = false;
    webPattern->GetAndUpdateCursorStyleInfo(OHOS::NWeb::CursorType::CT_LOCK, nullptr);
    EXPECT_TRUE(webPattern->isMouseLocked_);
#endif
}

// Covers GetAndUpdateCursorStyleInfo 'case CT_UNLOCK' branch (previously never hit).
HWTEST_F(WebPatternMiscTest, GetAndUpdateCursorStyleInfo002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->isMouseLocked_ = true;
    webPattern->cursorType_ = OHOS::NWeb::CursorType::CT_POINTER;
    webPattern->GetAndUpdateCursorStyleInfo(OHOS::NWeb::CursorType::CT_UNLOCK, nullptr);
    EXPECT_FALSE(webPattern->isMouseLocked_);
#endif
}

// Covers GetAndUpdateCursorStyleInfo 'case CT_DRAG' inner branch
// (cursorType_ == CT_CUSTOM) true path (previously only false path was hit).
HWTEST_F(WebPatternMiscTest, GetAndUpdateCursorStyleInfo003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->cursorType_ = OHOS::NWeb::CursorType::CT_CUSTOM;
    webPattern->GetAndUpdateCursorStyleInfo(OHOS::NWeb::CursorType::CT_DRAG, nullptr);
    EXPECT_EQ(webPattern->cursorType_, OHOS::NWeb::CursorType::CT_CUSTOM);
#endif
}

// Covers OnRotateRenderEffectUpdate switch 'default' branch (previously never hit).
HWTEST_F(WebPatternMiscTest, OnRotateRenderEffectUpdate001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnRotateRenderEffectUpdate(static_cast<WebRotateEffect>(999));
    EXPECT_EQ(webPattern->renderFit_, RenderFit::TOP_LEFT);
#endif
}

// Covers NeedSoftKeyboard branch 'onNeedSoftkeyboardCallback_ && !Pattern::NeedSoftKeyboard()'
// true path (previously only the false path was hit).
HWTEST_F(WebPatternMiscTest, NeedSoftKeyboard001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->onNeedSoftkeyboardCallback_ = []() { return false; };
    auto result = webPattern->NeedSoftKeyboard();
    EXPECT_FALSE(result);
#endif
}

// Covers NeedSoftKeyboard branch when callback is set but reports keyboard needed.
HWTEST_F(WebPatternMiscTest, NeedSoftKeyboard002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->onNeedSoftkeyboardCallback_ = []() { return true; };
    webPattern->NeedSoftKeyboard();
#endif
}

// Covers ExecuteInputCommand branch 'if (!delegate_)' true path (previously never reached).
HWTEST_F(WebPatternMiscTest, ExecuteInputCommand001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    auto comJson = JsonUtil::ParseJsonString(R"({"event_type":"input-date","xpath":"/html","value":"v"})");
    int result = webPattern->ExecuteInputCommand(comJson, "input-date");
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::DELEGATE_NULL));
#endif
}

// Covers ExecuteInputCommand branches 'if (!delegate_)' false + 'if (!manager)' true
// (manager is nullptr in the test mock, previously never reached).
HWTEST_F(WebPatternMiscTest, ExecuteInputCommand002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    SetupDelegate(webPattern);
    auto comJson = JsonUtil::ParseJsonString(R"({"event_type":"input-date","xpath":"/html","value":"v"})");
    int result = webPattern->ExecuteInputCommand(comJson, "input-date");
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::FAILED));
#endif
}

// Covers ExecuteSelectCommand branch 'if (!delegate_)' true path (previously never reached).
HWTEST_F(WebPatternMiscTest, ExecuteSelectCommand001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    auto comJson = JsonUtil::ParseJsonString(R"({"event_type":"select","xpath":"/html","value":["a"]})");
    int result = webPattern->ExecuteSelectCommand(comJson, "select");
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::DELEGATE_NULL));
#endif
}

// Covers ExecuteSelectCommand branches 'if (!delegate_)' false + 'if (!manager)' true
// (manager is nullptr in the test mock, previously never reached).
HWTEST_F(WebPatternMiscTest, ExecuteSelectCommand002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    SetupDelegate(webPattern);
    auto comJson = JsonUtil::ParseJsonString(R"({"event_type":"select","xpath":"/html","value":["a"]})");
    int result = webPattern->ExecuteSelectCommand(comJson, "select");
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::FAILED));
#endif
}

// Covers ExecuteGestureCommand branch 'if (!delegate_)' true path (previously only the
// false path was hit; deeper branches need a non-null manager, unreachable in the test mock).
HWTEST_F(WebPatternMiscTest, ExecuteGestureCommand001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    auto comJson = JsonUtil::ParseJsonString(R"({"event_type":"event_tap","x":1.0,"y":1.0})");
    int result = webPattern->ExecuteGestureCommand(comJson, "event_tap");
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::DELEGATE_NULL));
#endif
}

// Covers ConvertScreenToWebCoordinates branch 'outWebX < 0' true path -> returns false.
HWTEST_F(WebPatternMiscTest, ConvertScreenToWebCoordinates001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    double webX = 0.0;
    double webY = 0.0;
    bool result = webPattern->ConvertScreenToWebCoordinates(-1e9, 1e9, webX, webY);
    EXPECT_FALSE(result);
#endif
}

// Covers ConvertScreenToWebCoordinates branch 'outWebY < 0' true path (outWebX >= 0) -> false.
HWTEST_F(WebPatternMiscTest, ConvertScreenToWebCoordinates002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    double webX = 0.0;
    double webY = 0.0;
    bool result = webPattern->ConvertScreenToWebCoordinates(1e9, -1e9, webX, webY);
    EXPECT_FALSE(result);
#endif
}

// Covers ConvertScreenToWebCoordinates branch where both coordinates are valid -> true.
HWTEST_F(WebPatternMiscTest, ConvertScreenToWebCoordinates003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    double webX = -1.0;
    double webY = -1.0;
    bool result = webPattern->ConvertScreenToWebCoordinates(1e9, 1e9, webX, webY);
    EXPECT_TRUE(result);
    EXPECT_GE(webX, 0.0);
    EXPECT_GE(webY, 0.0);
#endif
}

// Covers CheckGestureCoordinatesInWebBounds out-of-bounds via screenX < webLeft.
HWTEST_F(WebPatternMiscTest, CheckGestureCoordinatesInWebBounds001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->drawSize_ = Size(100000, 100000);
    int result = webPattern->CheckGestureCoordinatesInWebBounds(-1e9, 1.0);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_GESTURE_COORDINATES));
#endif
}

// Covers CheckGestureCoordinatesInWebBounds out-of-bounds via screenX > webRight.
HWTEST_F(WebPatternMiscTest, CheckGestureCoordinatesInWebBounds002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->drawSize_ = Size(100000, 100000);
    int result = webPattern->CheckGestureCoordinatesInWebBounds(1e9, 1.0);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_GESTURE_COORDINATES));
#endif
}

// Covers CheckGestureCoordinatesInWebBounds out-of-bounds via screenY < webTop (X in bounds).
HWTEST_F(WebPatternMiscTest, CheckGestureCoordinatesInWebBounds003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->drawSize_ = Size(100000, 100000);
    int result = webPattern->CheckGestureCoordinatesInWebBounds(50000.0, -1e9);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_GESTURE_COORDINATES));
#endif
}

// Covers CheckGestureCoordinatesInWebBounds out-of-bounds via screenY > webBottom (X in bounds).
HWTEST_F(WebPatternMiscTest, CheckGestureCoordinatesInWebBounds004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->drawSize_ = Size(100000, 100000);
    int result = webPattern->CheckGestureCoordinatesInWebBounds(50000.0, 1e9);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_GESTURE_COORDINATES));
#endif
}

// Covers CheckGestureCoordinatesInWebBounds in-bounds path (all conditions false) -> SUCCESS
// (WEB_COMMAND_BUILD_SUCCESS == 0).
HWTEST_F(WebPatternMiscTest, CheckGestureCoordinatesInWebBounds005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->drawSize_ = Size(100000, 100000);
    int result = webPattern->CheckGestureCoordinatesInWebBounds(50000.0, 50000.0);
    EXPECT_EQ(result, 0);
#endif
}

// Covers HandleScrollGestureCommand branch 'invalid coordinates' -> JSON_INVALID_GESTURE_COORDINATES.
HWTEST_F(WebPatternMiscTest, HandleScrollGestureCommand001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    int result = webPattern->HandleScrollGestureCommand(-1e9, 1e9, 10.0, 10.0, 100);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_GESTURE_COORDINATES));
#endif
}

// Covers HandleScrollGestureCommand valid coordinates + delegate_ is null -> DELEGATE_NULL.
HWTEST_F(WebPatternMiscTest, HandleScrollGestureCommand002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    int result = webPattern->HandleScrollGestureCommand(1e9, 1e9, 10.0, 10.0, 100);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::DELEGATE_NULL));
#endif
}

// Covers HandleScrollGestureCommand valid coordinates + delegate set (manager null) -> FAILED.
HWTEST_F(WebPatternMiscTest, HandleScrollGestureCommand003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    SetupDelegate(webPattern);
    int result = webPattern->HandleScrollGestureCommand(1e9, 1e9, 10.0, 10.0, 100);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::FAILED));
#endif
}

// Covers HandlePinchGestureCommand branch 'invalid coordinates' -> JSON_INVALID_GESTURE_COORDINATES.
HWTEST_F(WebPatternMiscTest, HandlePinchGestureCommand001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    int result = webPattern->HandlePinchGestureCommand(-1e9, 1e9, 2.0, 100);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_GESTURE_COORDINATES));
#endif
}

// Covers HandlePinchGestureCommand valid coordinates + delegate_ is null -> DELEGATE_NULL.
HWTEST_F(WebPatternMiscTest, HandlePinchGestureCommand002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    int result = webPattern->HandlePinchGestureCommand(1e9, 1e9, 2.0, 100);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::DELEGATE_NULL));
#endif
}

// Covers HandlePinchGestureCommand valid coordinates + delegate set (manager null) -> FAILED.
HWTEST_F(WebPatternMiscTest, HandlePinchGestureCommand003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    SetupDelegate(webPattern);
    int result = webPattern->HandlePinchGestureCommand(1e9, 1e9, 2.0, 100);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::FAILED));
#endif
}

// Covers HandleLongPressCommand branch 'invalid coordinates' -> JSON_INVALID_GESTURE_COORDINATES.
HWTEST_F(WebPatternMiscTest, HandleLongPressCommand001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    int result = webPattern->HandleLongPressCommand(-1e9, 1e9);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_GESTURE_COORDINATES));
#endif
}

// Covers HandleLongPressCommand valid coordinates path (passes coordinate conversion, then
// context/taskExecutor handling -> SUCCESS or FAILED depending on the test task executor).
HWTEST_F(WebPatternMiscTest, HandleLongPressCommand002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    int result = webPattern->HandleLongPressCommand(1e9, 1e9);
    EXPECT_NE(result, static_cast<int>(WebCommandResult::JSON_INVALID_GESTURE_COORDINATES));
#endif
}

// Covers ExecuteClickScrollCommand branch 'if (!delegate_)' true path (previously only the
// false path was hit). An unrecognized event_type makes BuildClickScrollAction succeed without
// validation, so execution reaches the delegate check.
HWTEST_F(WebPatternMiscTest, ExecuteClickScrollCommand001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    auto comJson = JsonUtil::ParseJsonString("{}");
    int result = webPattern->ExecuteClickScrollCommand(comJson, "other");
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::DELEGATE_NULL));
#endif
}

// Covers ExecuteClickScrollCommand delegate-set path: build success + delegate present, then
// result-check branches evaluate (manager-independent; SendCommandActionToNWeb returns -1 here).
HWTEST_F(WebPatternMiscTest, ExecuteClickScrollCommand002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    SetupDelegate(webPattern);
    auto comJson = JsonUtil::ParseJsonString("{}");
    int result = webPattern->ExecuteClickScrollCommand(comJson, "other");
    EXPECT_EQ(result, -1);
#endif
}

// Covers ExecuteInputMethodCommand branch 'if (!delegate_)' true path (previously only the
// false path was hit). An unrecognized event_type makes BuildInputMethodAction succeed without
// validation, so execution reaches the delegate check.
HWTEST_F(WebPatternMiscTest, ExecuteInputMethodCommand001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    auto comJson = JsonUtil::ParseJsonString("{}");
    int result = webPattern->ExecuteInputMethodCommand(comJson, "inputCopy");
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::DELEGATE_NULL));
#endif
}

// Covers ExecuteInputMethodCommand delegate-set path: build success + delegate present
// (SendCommandActionToNWeb returns -1 here).
HWTEST_F(WebPatternMiscTest, ExecuteInputMethodCommand002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    SetupDelegate(webPattern);
    auto comJson = JsonUtil::ParseJsonString("{}");
    int result = webPattern->ExecuteInputMethodCommand(comJson, "inputCopy");
    EXPECT_EQ(result, -1);
#endif
}

// Covers DumpGpuInfo branch where delegate_ is null: the guard condition is false, totalSize
// stays 0, both GPU-value branches are false, and the formatting path runs.
HWTEST_F(WebPatternMiscTest, DumpGpuInfo001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->DumpGpuInfo();
#endif
}

// Covers DumpGpuInfo branch where delegate_ is set but GetNweb() is null (test mock), so the
// guard 'delegate_ != nullptr && GetNweb() != nullptr' is false via the second operand.
HWTEST_F(WebPatternMiscTest, DumpGpuInfo002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    SetupDelegate(webPattern);
    webPattern->DumpGpuInfo();
#endif
}

// Covers DumpSimplifyInfoOnlyForParamConfig branch 'config.withWeb == false': the && short-
// circuits in the if. webDomDocument_ must stay non-null (the else-if dereferences it); a default
// (invalid) document drives the else-if ReportDomTreeException path, and the json body is skipped.
HWTEST_F(WebPatternMiscTest, DumpSimplifyInfoOnlyForParamConfig001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->webDomDocument_ = std::make_unique<WebDomDocument>();
    std::shared_ptr<JsonValue> json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    ParamConfig config;
    config.withWeb = false;
    webPattern->DumpSimplifyInfoOnlyForParamConfig(json, config);
    ASSERT_NE(webPattern->webDomDocument_, nullptr);
    EXPECT_FALSE(webPattern->webDomDocument_->IsValid());
#endif
}

// Covers DumpSimplifyInfoOnlyForParamConfig branch 'withWeb == true && IsValid() == false':
// a default WebDomDocument is not valid, so the json body is skipped (no crash on deref).
HWTEST_F(WebPatternMiscTest, DumpSimplifyInfoOnlyForParamConfig002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->webDomDocument_ = std::make_unique<WebDomDocument>();
    std::shared_ptr<JsonValue> json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    ParamConfig config;
    config.withWeb = true;
    webPattern->DumpSimplifyInfoOnlyForParamConfig(json, config);
    ASSERT_NE(webPattern->webDomDocument_, nullptr);
    EXPECT_FALSE(webPattern->webDomDocument_->IsValid());
#endif
}

// Covers AddExtraInfoWithParamConfig branch 'config.withWeb == false': the && short-circuits in
// the if; webDomDocument_ must stay non-null (else-if dereferences it) and a default (invalid)
// document drives the else-if ReportDomTreeException path.
HWTEST_F(WebPatternMiscTest, AddExtraInfoWithParamConfig001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->webDomDocument_ = std::make_unique<WebDomDocument>();
    std::shared_ptr<JsonValue> json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    ParamConfig config;
    config.withWeb = false;
    webPattern->AddExtraInfoWithParamConfig(json, config);
    ASSERT_NE(webPattern->webDomDocument_, nullptr);
    EXPECT_FALSE(webPattern->webDomDocument_->IsValid());
#endif
}

// Covers AddExtraInfoWithParamConfig branch 'withWeb == true && IsValid() == false'.
HWTEST_F(WebPatternMiscTest, AddExtraInfoWithParamConfig002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->webDomDocument_ = std::make_unique<WebDomDocument>();
    std::shared_ptr<JsonValue> json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    ParamConfig config;
    config.withWeb = true;
    webPattern->AddExtraInfoWithParamConfig(json, config);
    ASSERT_NE(webPattern->webDomDocument_, nullptr);
    EXPECT_FALSE(webPattern->webDomDocument_->IsValid());
#endif
}

// Covers ParseNWebViewDataCommonField branch: child IsString && key == EVENT_TYPE, with the
// event value present in NWEB_AUTOFILL_EVENTS -> SetEventType (inner count != 0 true path).
HWTEST_F(WebPatternMiscTest, ParseNWebViewDataCommonField001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    auto viewDataCommon = std::make_shared<ViewDataCommon>();
    auto root = MakeStringFieldRoot(OHOS::NWeb::NWEB_AUTOFILL_EVENT_TYPE, OHOS::NWeb::NWEB_AUTOFILL_EVENT_SAVE);
    auto child = root->GetChild();
    webPattern->ParseNWebViewDataCommonField(std::move(child), viewDataCommon);
    EXPECT_EQ(viewDataCommon->GetEventType(), OHOS::NWeb::NWebAutofillEvent::SAVE);
#endif
}

// Covers ParseNWebViewDataCommonField branch: child IsString && key == EVENT_TYPE, but the
// event value is NOT in NWEB_AUTOFILL_EVENTS -> inner count == 0 false path (no SetEventType).
HWTEST_F(WebPatternMiscTest, ParseNWebViewDataCommonField002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    auto viewDataCommon = std::make_shared<ViewDataCommon>();
    auto root = MakeStringFieldRoot(OHOS::NWeb::NWEB_AUTOFILL_EVENT_TYPE, "unknownEvent");
    auto child = root->GetChild();
    webPattern->ParseNWebViewDataCommonField(std::move(child), viewDataCommon);
    EXPECT_EQ(viewDataCommon->GetEventType(), OHOS::NWeb::NWebAutofillEvent::UNKNOWN);
#endif
}

// Covers ParseNWebViewDataCommonField branch: child IsString && key == PAGE_URL -> SetPageUrl.
HWTEST_F(WebPatternMiscTest, ParseNWebViewDataCommonField003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    auto viewDataCommon = std::make_shared<ViewDataCommon>();
    auto root = MakeStringFieldRoot(OHOS::NWeb::NWEB_AUTOFILL_PAGE_URL, "https://example.com");
    auto child = root->GetChild();
    webPattern->ParseNWebViewDataCommonField(std::move(child), viewDataCommon);
    EXPECT_EQ(viewDataCommon->GetPageUrl(), "https://example.com");
#endif
}

// Covers ParseNWebViewDataCommonField branch: child IsBool && key == IS_USER_SELECTED.
HWTEST_F(WebPatternMiscTest, ParseNWebViewDataCommonField004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    auto viewDataCommon = std::make_shared<ViewDataCommon>();
    auto root = MakeBoolFieldRoot(OHOS::NWeb::NWEB_AUTOFILL_IS_USER_SELECTED, true);
    auto child = root->GetChild();
    webPattern->ParseNWebViewDataCommonField(std::move(child), viewDataCommon);
    EXPECT_TRUE(viewDataCommon->IsUserSelected());
#endif
}

// Covers ParseNWebViewDataCommonField branch: child IsBool && key == IS_OTHER_ACCOUNT.
HWTEST_F(WebPatternMiscTest, ParseNWebViewDataCommonField005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    auto viewDataCommon = std::make_shared<ViewDataCommon>();
    auto root = MakeBoolFieldRoot(OHOS::NWeb::NWEB_AUTOFILL_IS_OTHER_ACCOUNT, true);
    auto child = root->GetChild();
    webPattern->ParseNWebViewDataCommonField(std::move(child), viewDataCommon);
    EXPECT_TRUE(viewDataCommon->IsOtherAccount());
#endif
}

// Covers ParseNWebViewDataCommonField branch: child IsString && key == EVENT_SOURCE -> SetSource.
HWTEST_F(WebPatternMiscTest, ParseNWebViewDataCommonField006, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    auto viewDataCommon = std::make_shared<ViewDataCommon>();
    auto root = MakeStringFieldRoot(OHOS::NWeb::NWEB_AUTOFILL_EVENT_SOURCE, "src");
    auto child = root->GetChild();
    webPattern->ParseNWebViewDataCommonField(std::move(child), viewDataCommon);
    EXPECT_EQ(viewDataCommon->GetSource(), "src");
#endif
}

// Covers ConvertMouseToTouchByWhiteList branch 'mouseInfo.GetButton() != LEFT_BUTTON' true ->
// return false (non-left button is rejected before any whitelist check).
HWTEST_F(WebPatternMiscTest, ConvertMouseToTouchByWhiteList001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    OHOS::Ace::MouseInfo mouseInfo;
    mouseInfo.SetButton(MouseButton::RIGHT_BUTTON);
    OHOS::Ace::TouchEventInfo touchEventInfo("touchEvent");
    bool result = webPattern->ConvertMouseToTouchByWhiteList(mouseInfo, touchEventInfo);
    EXPECT_FALSE(result);
#endif
}

// Covers ConvertMouseToTouchByWhiteList branch 'GetButton() == LEFT_BUTTON' (proceeds past the
// button check). IsConvertByWhiteList() returns false in the unit-test environment, so the
// whitelist guard returns false. (The switch cases need IsConvertByWhiteList() == true, which is
// feature-manager gated and unreachable here.)
HWTEST_F(WebPatternMiscTest, ConvertMouseToTouchByWhiteList002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    OHOS::Ace::MouseInfo mouseInfo;
    mouseInfo.SetButton(MouseButton::LEFT_BUTTON);
    mouseInfo.SetAction(MouseAction::PRESS);
    OHOS::Ace::TouchEventInfo touchEventInfo("touchEvent");
    bool result = webPattern->ConvertMouseToTouchByWhiteList(mouseInfo, touchEventInfo);
    EXPECT_FALSE(result);
#endif
}

} // namespace OHOS::Ace::NG
