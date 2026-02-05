
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

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#define private public
#include "test/mock/core/common/mock_container.h"

#include "core/components/web/resource/web_delegate.h"
#include "core/components_ng/pattern/web/web_pattern.h"
#undef private

#include "cJSON.h"
#include "test/mock/base/mock_mouse_style.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/web/web_dom_document.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t BUFFER_SIZE = 100;
constexpr int32_t WIDTH_VALUE = 10.0;
constexpr int32_t HEIGHT_VALUE = 20.0;
constexpr int32_t RESERVED_DEVICEID1 = 0xAAAAAAFF;
constexpr int32_t RESERVED_DEVICEID2 = 0xAAAAAAFE;
constexpr int32_t COUNTER_NUMBER_TEN_HANDLE = 10;

class NWebCursorInfoTestImpl : public OHOS::NWeb::NWebCursorInfo {
public:
    int32_t GetX() override
    {
        return 0;
    }

    int32_t GetY() override
    {
        return 0;
    }

    uint8_t* GetBuff() override
    {
        return buffer_;
    }

    float GetScale() override
    {
        return 1;
    }

    int32_t GetWidth() override
    {
        return WIDTH_VALUE;
    }

    int32_t GetHeight() override
    {
        return HEIGHT_VALUE;
    }

private:
    uint8_t buffer_[BUFFER_SIZE];
};

class UnifiedDataMock : public Ace::UnifiedData {
public:
    int64_t GetSize() override
    {
        return COUNTER_NUMBER_TEN_HANDLE;
    }
};
} // namespace

class WebPatternCursorTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

    RefPtr<WebPattern> web_pattern_;
};

void WebPatternCursorTest::SetUpTestCase() {}
void WebPatternCursorTest::TearDownTestCase() {}
void WebPatternCursorTest::SetUp()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrent();
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    web_pattern_ = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(web_pattern_, nullptr);
    web_pattern_->OnModifyDone();
    ASSERT_NE(web_pattern_->delegate_, nullptr);
}
void WebPatternCursorTest::TearDown()
{
    MockContainer::TearDown();
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: OnCursorChange_001
 * @tc.desc: OnCursorChange
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternCursorTest, OnCursorChange_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    OHOS::NWeb::CursorType type = OHOS::NWeb::CursorType::CT_NONE;
    auto info = std::make_shared<NWebCursorInfoTestImpl>();
    ASSERT_NE(info, nullptr);
    MockContainer::Current()->SetIsUIExtensionWindow(false);
    web_pattern_->mouseEventDeviceId_ = RESERVED_DEVICEID1;
    web_pattern_->isHoverExit_ = true;
    bool result = web_pattern_->OnCursorChange(type, info);
    EXPECT_FALSE(result);
    web_pattern_->mouseEventDeviceId_ = RESERVED_DEVICEID2;
    result = web_pattern_->OnCursorChange(type, info);
    EXPECT_FALSE(result);
#endif
}

/**
 * @tc.name: OnCursorChange_002
 * @tc.desc: OnCursorChange
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternCursorTest, OnCursorChange_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    OHOS::NWeb::CursorType type = OHOS::NWeb::CursorType::CT_NONE;
    auto info = std::make_shared<NWebCursorInfoTestImpl>();
    ASSERT_NE(info, nullptr);
    web_pattern_->isHoverExit_ = false;
    auto mouseStyle = MouseStyle::CreateMouseStyle();
    auto mockMouseStyle = AceType::DynamicCast<MockMouseStyle>(mouseStyle);
    MockContainer::Current()->SetIsUIExtensionWindow(false);
    EXPECT_CALL(*mockMouseStyle, GetPointerStyle(::testing::_, ::testing::_)).WillOnce(Return(-1));
    EXPECT_CALL(*mockMouseStyle, SetPointerStyle(::testing::_, ::testing::_)).WillOnce(Return(true));
    bool result = web_pattern_->OnCursorChange(type, info);
    EXPECT_FALSE(result);
#endif
}

/**
 * @tc.name: OnCursorChange_003
 * @tc.desc: OnCursorChange
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternCursorTest, OnCursorChange_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    OHOS::NWeb::CursorType type = OHOS::NWeb::CursorType::CT_CONTEXTMENU;
    auto info = std::make_shared<NWebCursorInfoTestImpl>();
    ASSERT_NE(info, nullptr);
    web_pattern_->isHoverExit_ = false;
    auto mouseStyle = MouseStyle::CreateMouseStyle();
    auto mockMouseStyle = AceType::DynamicCast<MockMouseStyle>(mouseStyle);
    MockContainer::Current()->SetIsUIExtensionWindow(false);
    EXPECT_CALL(*mockMouseStyle, GetPointerStyle(::testing::_, ::testing::_)).WillOnce(Return(0));
    bool result = web_pattern_->OnCursorChange(type, info);
    EXPECT_TRUE(result);
#endif
}

/**
 * @tc.name: OnCursorChange_004
 * @tc.desc: OnCursorChange
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternCursorTest, OnCursorChange_004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    OHOS::NWeb::CursorType type = OHOS::NWeb::CursorType::CT_ALIAS;
    auto info = std::make_shared<NWebCursorInfoTestImpl>();
    ASSERT_NE(info, nullptr);
    web_pattern_->isHoverExit_ = false;
    ASSERT_FALSE(web_pattern_->isHoverExit_);
    auto mouseStyle = MouseStyle::CreateMouseStyle();
    auto mockMouseStyle = AceType::DynamicCast<MockMouseStyle>(mouseStyle);
    MockContainer::Current()->SetIsUIExtensionWindow(false);
    EXPECT_CALL(*mockMouseStyle, GetPointerStyle(::testing::_, ::testing::_)).WillOnce(Return(0));
    bool result = web_pattern_->OnCursorChange(type, info);
    EXPECT_TRUE(result);
#endif
}

/**
 * @tc.name: OnCursorChange_005
 * @tc.desc: OnCursorChange
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternCursorTest, OnCursorChange_005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    OHOS::NWeb::CursorType type = OHOS::NWeb::CursorType::CT_CUSTOM;
    auto info = std::make_shared<NWebCursorInfoTestImpl>();
    ASSERT_NE(info, nullptr);
    web_pattern_->isHoverExit_ = false;
    auto mouseStyle = MouseStyle::CreateMouseStyle();
    auto mockMouseStyle = AceType::DynamicCast<MockMouseStyle>(mouseStyle);
    MockContainer::Current()->SetIsUIExtensionWindow(false);
    EXPECT_CALL(*mockMouseStyle, GetPointerStyle(::testing::_, ::testing::_)).WillOnce(Return(0));
    bool result = web_pattern_->OnCursorChange(type, info);
    EXPECT_TRUE(result);
#endif
}

/**
 * @tc.name: OnCursorChange_006
 * @tc.desc: OnCursorChange
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternCursorTest, OnCursorChange_006, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    OHOS::NWeb::CursorType type = OHOS::NWeb::CursorType::CT_ZOOMIN;
    auto info = std::make_shared<NWebCursorInfoTestImpl>();
    ASSERT_NE(info, nullptr);
    web_pattern_->isHoverExit_ = false;
    auto mouseStyle = MouseStyle::CreateMouseStyle();
    auto mockMouseStyle = AceType::DynamicCast<MockMouseStyle>(mouseStyle);
    MockContainer::Current()->SetIsUIExtensionWindow(false);
    EXPECT_CALL(*mockMouseStyle, GetPointerStyle(::testing::_, ::testing::_)).WillRepeatedly(Return(0));
    bool result = web_pattern_->OnCursorChange(type, info);
    EXPECT_TRUE(result);
#endif
}

/**
 * @tc.name: OnCursorChange_007
 * @tc.desc: OnCursorChange
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternCursorTest, OnCursorChange_007, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    OHOS::NWeb::CursorType type = OHOS::NWeb::CursorType::CT_POINTER;
    auto info = std::make_shared<NWebCursorInfoTestImpl>();
    ASSERT_NE(info, nullptr);
    web_pattern_->isHoverExit_ = false;
    auto mouseStyle = MouseStyle::CreateMouseStyle();
    auto mockMouseStyle = AceType::DynamicCast<MockMouseStyle>(mouseStyle);
    MockContainer::Current()->SetIsUIExtensionWindow(false);
    EXPECT_CALL(*mockMouseStyle, GetPointerStyle(::testing::_, ::testing::_)).WillRepeatedly(Return(0));
    bool result = web_pattern_->OnCursorChange(type, info);
    EXPECT_TRUE(result);
#endif
}

/**
 * @tc.name: OnCursorChange_008
 * @tc.desc: OnCursorChange for UIExtension
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternCursorTest, OnCursorChange_008, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    OHOS::NWeb::CursorType type = OHOS::NWeb::CursorType::CT_POINTER;
    auto info = std::make_shared<NWebCursorInfoTestImpl>();
    ASSERT_NE(info, nullptr);
    web_pattern_->isHoverExit_ = false;
    auto mouseStyle = MouseStyle::CreateMouseStyle();
    auto mockMouseStyle = AceType::DynamicCast<MockMouseStyle>(mouseStyle);
    MockContainer::Current()->SetIsUIExtensionWindow(true);
    EXPECT_CALL(*mockMouseStyle, GetPointerStyle(::testing::_, ::testing::_)).WillRepeatedly(Return(0));
    bool result = web_pattern_->OnCursorChange(type, info);
    EXPECT_TRUE(result);
#endif
}

/**
 * @tc.name: OnCursorChange_009
 * @tc.desc: OnCursorChange for container
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternCursorTest, OnCursorChange_009, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    OHOS::NWeb::CursorType type = OHOS::NWeb::CursorType::CT_POINTER;
    auto info = std::make_shared<NWebCursorInfoTestImpl>();
    ASSERT_NE(info, nullptr);
    web_pattern_->isHoverExit_ = false;
    auto mouseStyle = MouseStyle::CreateMouseStyle();
    auto mockMouseStyle = AceType::DynamicCast<MockMouseStyle>(mouseStyle);
    MockContainer::TearDown();
    EXPECT_CALL(*mockMouseStyle, GetPointerStyle(::testing::_, ::testing::_)).WillRepeatedly(Return(0));
    bool result = web_pattern_->OnCursorChange(type, info);
    EXPECT_TRUE(result);
#endif
}

/**
 * @tc.name: OnCursorChange_010
 * @tc.desc: OnCursorChange
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternCursorTest, OnCursorChange_010, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    OHOS::NWeb::CursorType type = OHOS::NWeb::CursorType::CT_NONE;
    auto info = std::make_shared<NWebCursorInfoTestImpl>();
    ASSERT_NE(info, nullptr);
    web_pattern_->isHoverExit_ = true;
    ASSERT_TRUE(web_pattern_->isHoverExit_);
    MockContainer::Current()->SetIsUIExtensionWindow(false);
    bool ret = web_pattern_->OnCursorChange(type, info);
    ASSERT_FALSE(ret);
#endif
}

/**
 * @tc.name: OnCursorChange_011
 * @tc.desc: OnCursorChange
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternCursorTest, OnCursorChange_011, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    OHOS::NWeb::CursorType type = OHOS::NWeb::CursorType::CT_CONTEXTMENU;
    auto info = std::make_shared<NWebCursorInfoTestImpl>();
    ASSERT_NE(info, nullptr);
    web_pattern_->isHoverExit_ = true;
    ASSERT_TRUE(web_pattern_->isHoverExit_);
    MockContainer::Current()->SetIsUIExtensionWindow(false);
    bool ret = web_pattern_->OnCursorChange(type, info);
    EXPECT_FALSE(ret);
#endif
}

/**
 * @tc.name: OnCursorChange_012
 * @tc.desc: OnCursorChange
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternCursorTest, OnCursorChange_012, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    OHOS::NWeb::CursorType type = OHOS::NWeb::CursorType::CT_NONE;
    auto info = std::make_shared<NWebCursorInfoTestImpl>();
    ASSERT_NE(info, nullptr);
    web_pattern_->isHoverExit_ = false;
    ASSERT_FALSE(web_pattern_->isHoverExit_);
    auto pipelineContext = MockPipelineContext::GetCurrent();
    MockContainer::Current()->SetIsUIExtensionWindow(false);
    auto mouseStyle = MouseStyle::CreateMouseStyle();
    auto mockMouseStyle = AceType::DynamicCast<MockMouseStyle>(mouseStyle);
    EXPECT_CALL(*mockMouseStyle, SetPointerStyle(::testing::_, ::testing::_)).WillOnce(Return(true));
    bool ret = web_pattern_->OnCursorChange(type, info);
    EXPECT_TRUE(ret);
#endif
}

/**
 * @tc.name: OnCursorChange_013
 * @tc.desc: OnCursorChange
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternCursorTest, OnCursorChange_013, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    OHOS::NWeb::CursorType type = OHOS::NWeb::CursorType::CT_MAX_VALUE;
    auto info = std::make_shared<NWebCursorInfoTestImpl>();
    ASSERT_NE(info, nullptr);
    web_pattern_->isHoverExit_ = false;
    ASSERT_FALSE(web_pattern_->isHoverExit_);
    MockContainer::Current()->SetIsUIExtensionWindow(false);
    bool ret = web_pattern_->OnCursorChange(type, info);
    EXPECT_TRUE(ret);
#endif
}

/**
 * @tc.name: HandleMouseEventOnDrag_001
 * @tc.desc: OnCursorChange
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternCursorTest, HandleMouseEventOnDrag_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    web_pattern_->isDragStartFromWeb_ = true;
    RefPtr<OHOS::Ace::DragEvent> gestureHub = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    ASSERT_NE(gestureHub, nullptr);
    auto host = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, 1, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(host, nullptr);
    auto aceData = AceType::MakeRefPtr<UnifiedDataMock>();
    gestureHub->SetData(nullptr);
    auto mouseStyle = MouseStyle::CreateMouseStyle();
    auto mockMouseStyle = AceType::DynamicCast<MockMouseStyle>(mouseStyle);
    EXPECT_CALL(*mockMouseStyle, SetPointerStyle(::testing::_, ::testing::_)).WillOnce(Return(true));
    web_pattern_->HandleOnDragDrop(gestureHub);
    EXPECT_TRUE(web_pattern_->isNeedMouseMoveOnDragEnd_);
    web_pattern_->HandleDragEnd(0, 0);
    EXPECT_FALSE(web_pattern_->isNeedMouseMoveOnDragEnd_);
#endif
}
} // namespace OHOS::Ace::NG