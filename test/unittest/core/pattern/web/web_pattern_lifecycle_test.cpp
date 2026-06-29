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
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/base/utils/system_properties.h"
#include "nweb.h"
#include "nweb_handler.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::NWeb;

namespace OHOS::Ace::NG {

class WebPatternLifecycleTest : public testing::Test {
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
} // namespace

HWTEST_F(WebPatternLifecycleTest, OnInActive001, TestSize.Level1)
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

HWTEST_F(WebPatternLifecycleTest, OnActive001, TestSize.Level1)
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

HWTEST_F(WebPatternLifecycleTest, GetActiveStatus001, TestSize.Level1)
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

HWTEST_F(WebPatternLifecycleTest, OnVisibleAreaChange001, TestSize.Level1)
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

HWTEST_F(WebPatternLifecycleTest, OnVisibleAreaChange002, TestSize.Level1)
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

HWTEST_F(WebPatternLifecycleTest, OnVisibleAreaChange003, TestSize.Level1)
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

HWTEST_F(WebPatternLifecycleTest, OnVisibleAreaChange004, TestSize.Level1)
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

HWTEST_F(WebPatternLifecycleTest, OnVisibleAreaChange005, TestSize.Level1)
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

HWTEST_F(WebPatternLifecycleTest, UpdateBackgroundColorRightNow001, TestSize.Level1)
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

HWTEST_F(WebPatternLifecycleTest, UpdateBackgroundColorRightNow002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = AceType::MakeRefPtr<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->UpdateBackgroundColorRightNow(0xFF000000);
#endif
}

HWTEST_F(WebPatternLifecycleTest, OnNotifyMemoryLevel001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    SetupDelegate(webPattern);
    webPattern->isMemoryLevelEnable_ = false;
    webPattern->OnNotifyMemoryLevel(5);
#endif
}

HWTEST_F(WebPatternLifecycleTest, OnNotifyMemoryLevel002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    SetupDelegate(webPattern);
    webPattern->isMemoryLevelEnable_ = true;
    webPattern->OnNotifyMemoryLevel(5);
#endif
}

HWTEST_F(WebPatternLifecycleTest, OnNotifyMemoryLevel003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->isMemoryLevelEnable_ = true;
    webPattern->OnNotifyMemoryLevel(5);
#endif
}

HWTEST_F(WebPatternLifecycleTest, GetWebId001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    SetupDelegate(webPattern);
    auto result = webPattern->GetWebId();
    EXPECT_EQ(result, 0);
#endif
}

HWTEST_F(WebPatternLifecycleTest, GetWebId002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    auto result = webPattern->GetWebId();
    EXPECT_EQ(result, -1);
#endif
}

HWTEST_F(WebPatternLifecycleTest, GetDefaultBackgroundColor001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    auto color = webPattern->GetDefaultBackgroundColor();
    EXPECT_EQ(color, Color::WHITE);
#endif
}

HWTEST_F(WebPatternLifecycleTest, EnableScrollDirectionalLock001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->EnableScrollDirectionalLock(true, ScrollDirectionalLockType::ALL);
    EXPECT_TRUE(webPattern->isDirectionalLockEnabled_);
    EXPECT_EQ(webPattern->scrollDirectionalLockType_, ScrollDirectionalLockType::ALL);
#endif
}

HWTEST_F(WebPatternLifecycleTest, EnableScrollDirectionalLock002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->EnableScrollDirectionalLock(false, ScrollDirectionalLockType::NESTED_SCROLL);
    EXPECT_FALSE(webPattern->isDirectionalLockEnabled_);
    EXPECT_EQ(webPattern->scrollDirectionalLockType_, ScrollDirectionalLockType::NESTED_SCROLL);
#endif
}

HWTEST_F(WebPatternLifecycleTest, OnNestedScroll001, TestSize.Level1)
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

HWTEST_F(WebPatternLifecycleTest, OnNestedScroll002, TestSize.Level1)
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

HWTEST_F(WebPatternLifecycleTest, OnNestedScroll003, TestSize.Level1)
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

HWTEST_F(WebPatternLifecycleTest, OnNestedScroll004, TestSize.Level1)
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

HWTEST_F(WebPatternLifecycleTest, OnNestedScrollV2001, TestSize.Level1)
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

HWTEST_F(WebPatternLifecycleTest, OnNestedScrollV2002, TestSize.Level1)
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

HWTEST_F(WebPatternLifecycleTest, OnNestedScrollV2003, TestSize.Level1)
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

HWTEST_F(WebPatternLifecycleTest, UpdateImageOverlayStatus001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->imageOverlayStatus_ = ImageOverlayStatus::NONE;
    webPattern->UpdateImageOverlayStatus(ImageOverlayEvent::TOUCH_PRESS);
    EXPECT_EQ(webPattern->imageOverlayStatus_, ImageOverlayStatus::TOUCH_HOLD);
#endif
}

HWTEST_F(WebPatternLifecycleTest, UpdateImageOverlayStatus002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->imageOverlayStatus_ = ImageOverlayStatus::TOUCH_HOLD;
    webPattern->UpdateImageOverlayStatus(ImageOverlayEvent::TOUCH_PRESS);
    EXPECT_EQ(webPattern->imageOverlayStatus_, ImageOverlayStatus::TOUCH_HOLD);
#endif
}

HWTEST_F(WebPatternLifecycleTest, UpdateImageOverlayStatus003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->imageOverlayStatus_ = ImageOverlayStatus::TOUCH_HOLD;
    webPattern->UpdateImageOverlayStatus(ImageOverlayEvent::TOUCH_RELEASE);
    EXPECT_EQ(webPattern->imageOverlayStatus_, ImageOverlayStatus::NONE);
#endif
}

HWTEST_F(WebPatternLifecycleTest, UpdateImageOverlayStatus004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->imageOverlayStatus_ = ImageOverlayStatus::TOUCH_HOLD;
    webPattern->UpdateImageOverlayStatus(ImageOverlayEvent::CREATE_OVERLAY);
    EXPECT_EQ(webPattern->imageOverlayStatus_, ImageOverlayStatus::HOLD_CREATE);
#endif
}

HWTEST_F(WebPatternLifecycleTest, UpdateImageOverlayStatus005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->imageOverlayStatus_ = ImageOverlayStatus::NONE;
    webPattern->UpdateImageOverlayStatus(ImageOverlayEvent::CREATE_OVERLAY);
    EXPECT_EQ(webPattern->imageOverlayStatus_, ImageOverlayStatus::NONE);
#endif
}

HWTEST_F(WebPatternLifecycleTest, UpdateImageOverlayStatus006, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->imageOverlayStatus_ = ImageOverlayStatus::HOLD_CREATE;
    webPattern->UpdateImageOverlayStatus(ImageOverlayEvent::CREATE_OVERLAY_RELEASE);
    EXPECT_EQ(webPattern->imageOverlayStatus_, ImageOverlayStatus::TOUCH_HOLD);
#endif
}

HWTEST_F(WebPatternLifecycleTest, UpdateImageOverlayStatus007, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->imageOverlayStatus_ = ImageOverlayStatus::NONE;
    webPattern->UpdateImageOverlayStatus(ImageOverlayEvent::CREATE_OVERLAY_RELEASE);
    EXPECT_EQ(webPattern->imageOverlayStatus_, ImageOverlayStatus::NONE);
#endif
}

HWTEST_F(WebPatternLifecycleTest, CloseImageOverlaySelection001, TestSize.Level1)
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

HWTEST_F(WebPatternLifecycleTest, CloseImageOverlaySelection002, TestSize.Level1)
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

HWTEST_F(WebPatternLifecycleTest, CloseImageOverlaySelection003, TestSize.Level1)
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

HWTEST_F(WebPatternLifecycleTest, HideHandleAndQuickMenuIfNecessary001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->webSelectOverlay_ = nullptr;
    webPattern->HideHandleAndQuickMenuIfNecessary(true, false);
#endif
}

HWTEST_F(WebPatternLifecycleTest, ChangeVisibilityOfQuickMenu001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->webSelectOverlay_ = nullptr;
    webPattern->ChangeVisibilityOfQuickMenu();
#endif
}

HWTEST_F(WebPatternLifecycleTest, IsQuickMenuShow001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->webSelectOverlay_ = nullptr;
    auto result = webPattern->IsQuickMenuShow();
    EXPECT_FALSE(result);
#endif
}

HWTEST_F(WebPatternLifecycleTest, OnEnableImageAnalyzerUpdate001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    SetupDelegate(webPattern);
    webPattern->OnEnableImageAnalyzerUpdate(true);
#endif
}

HWTEST_F(WebPatternLifecycleTest, OnEnableImageAnalyzerUpdate002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    SetupDelegate(webPattern);
    webPattern->OnEnableImageAnalyzerUpdate(false);
#endif
}

HWTEST_F(WebPatternLifecycleTest, OnEnableImageAnalyzerUpdate003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnEnableImageAnalyzerUpdate(true);
#endif
}

HWTEST_F(WebPatternLifecycleTest, GetBufferSizeByDeviceType001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    auto size = webPattern->GetBufferSizeByDeviceType();
    EXPECT_GT(size, 0);
#endif
}

HWTEST_F(WebPatternLifecycleTest, PushOverlayInfo001, TestSize.Level1)
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

HWTEST_F(WebPatternLifecycleTest, UpdateImageOverlayTouchInfo001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->overlayCreating_ = false;
    webPattern->UpdateImageOverlayTouchInfo(100, 200, TouchType::DOWN);
#endif
}

HWTEST_F(WebPatternLifecycleTest, UpdateImageOverlayTouchInfo002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->overlayCreating_ = false;
    webPattern->imageAnalyzerManager_ = nullptr;
    webPattern->UpdateImageOverlayTouchInfo(100, 200, TouchType::DOWN);
#endif
}

HWTEST_F(WebPatternLifecycleTest, GetCurrentLanguage001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    SetupDelegate(webPattern);
    auto result = webPattern->GetCurrentLanguage();
    EXPECT_EQ(result, "");
#endif
}

HWTEST_F(WebPatternLifecycleTest, GetCurrentLanguage002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    auto result = webPattern->GetCurrentLanguage();
    EXPECT_EQ(result, "");
#endif
}

HWTEST_F(WebPatternLifecycleTest, SendTranslateResult001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    SetupDelegate(webPattern);
    webPattern->SendTranslateResult(std::string("console.log('test')"));
#endif
}

HWTEST_F(WebPatternLifecycleTest, SendTranslateResult002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->SendTranslateResult(std::string("test"));
#endif
}

HWTEST_F(WebPatternLifecycleTest, FormatIndex001, TestSize.Level1)
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

HWTEST_F(WebPatternLifecycleTest, FormatIndex002, TestSize.Level1)
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

HWTEST_F(WebPatternLifecycleTest, FormatIndex003, TestSize.Level1)
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

HWTEST_F(WebPatternLifecycleTest, SendPipEvent001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    SetupDelegate(webPattern);
    webPattern->SendPipEvent(1, 2, 3, 4);
#endif
}

HWTEST_F(WebPatternLifecycleTest, SendPipEvent002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->SendPipEvent(1, 2, 3, 4);
#endif
}

HWTEST_F(WebPatternLifecycleTest, IsRtl001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = AceType::MakeRefPtr<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    auto result = webPattern->IsRtl();
    EXPECT_FALSE(result);
#endif
}

HWTEST_F(WebPatternLifecycleTest, IsRtl002, TestSize.Level1)
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

HWTEST_F(WebPatternLifecycleTest, IsRtl003, TestSize.Level1)
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

HWTEST_F(WebPatternLifecycleTest, SnapshotTouchReporter001, TestSize.Level1)
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

HWTEST_F(WebPatternLifecycleTest, SnapshotTouchReporter002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto reporter = std::make_shared<SnapshotTouchReporter>();
    ASSERT_NE(reporter, nullptr);
    reporter->OnClick();
    EXPECT_EQ(reporter->infos_, nullptr);
#endif
}

HWTEST_F(WebPatternLifecycleTest, SnapshotTouchReporter003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto reporter = std::make_shared<SnapshotTouchReporter>();
    ASSERT_NE(reporter, nullptr);
    reporter->OnPan();
    EXPECT_EQ(reporter->infos_, nullptr);
#endif
}

HWTEST_F(WebPatternLifecycleTest, SnapshotTouchReporter004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto reporter = std::make_shared<SnapshotTouchReporter>();
    ASSERT_NE(reporter, nullptr);
    reporter->OnDisappear();
    EXPECT_FALSE(reporter->appearTime_.has_value());
#endif
}

HWTEST_F(WebPatternLifecycleTest, CheckVisible001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = AceType::MakeRefPtr<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    auto result = webPattern->CheckVisible();
    EXPECT_FALSE(result);
#endif
}

HWTEST_F(WebPatternLifecycleTest, RemoveDataListNode001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->dataListNodeId_ = std::nullopt;
    webPattern->RemoveDataListNode();
#endif
}

HWTEST_F(WebPatternLifecycleTest, OnNestedScrollV2004, TestSize.Level1)
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

HWTEST_F(WebPatternLifecycleTest, OnNestedScroll005, TestSize.Level1)
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

HWTEST_F(WebPatternLifecycleTest, UpdateImageOverlayStatus008, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->imageOverlayStatus_ = ImageOverlayStatus::HOLD_CREATE;
    webPattern->UpdateImageOverlayStatus(ImageOverlayEvent::TOUCH_PRESS);
    EXPECT_EQ(webPattern->imageOverlayStatus_, ImageOverlayStatus::HOLD_CREATE);
#endif
}

HWTEST_F(WebPatternLifecycleTest, UpdateImageOverlayStatus009, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->imageOverlayStatus_ = ImageOverlayStatus::HOLD_CREATE;
    webPattern->UpdateImageOverlayStatus(ImageOverlayEvent::TOUCH_RELEASE);
    EXPECT_EQ(webPattern->imageOverlayStatus_, ImageOverlayStatus::NONE);
#endif
}

HWTEST_F(WebPatternLifecycleTest, OnEnableImageAnalyzerUpdate004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnEnableImageAnalyzerUpdate(false);
#endif
}

HWTEST_F(WebPatternLifecycleTest, PushOverlayInfo002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webPattern = CreateWebPattern();
    ASSERT_NE(webPattern, nullptr);
    EXPECT_EQ(webPattern->touchOverlayInfo_.size(), 0u);
    webPattern->PushOverlayInfo(0.0f, 0.0f, 0);
    EXPECT_EQ(webPattern->touchOverlayInfo_.size(), 1u);
#endif
}


} // namespace OHOS::Ace::NG
