
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

#include <gmock/gmock.h>

#include "gtest/gtest.h"
#define private public
#include "core/components/web/resource/web_delegate.h"
#include "core/components_ng/pattern/web/web_pattern.h"
#undef private

#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "nweb_autofill.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class NWebQuickMenuParamsMockImpl : public OHOS::NWeb::NWebQuickMenuParams {
public:
    MOCK_METHOD(int32_t, GetXCoord, (), (override));
    MOCK_METHOD(int32_t, GetYCoord, (), (override));
    MOCK_METHOD(int32_t, GetWidth, (), (override));
    MOCK_METHOD(int32_t, GetHeight, (), (override));
    MOCK_METHOD(int32_t, GetEditStateFlags, (), (override));
    MOCK_METHOD(int32_t, GetSelectX, (), (override));
    MOCK_METHOD(int32_t, GetSelectY, (), (override));
    MOCK_METHOD(int32_t, GetSelectWidth, (), (override));
    MOCK_METHOD(int32_t, GetSelectXHeight, (), (override));
    MOCK_METHOD(std::shared_ptr<OHOS::NWeb::NWebTouchHandleState>, GetTouchHandleState,
        (OHOS::NWeb::NWebTouchHandleState::TouchHandleType type), (override));
    MOCK_METHOD(bool, GetIsLongPressActived, (), (override));
};

class NWebQuickMenuParamsDummy : public OHOS::NWeb::NWebQuickMenuParams {
public:
    int32_t GetXCoord() override
    {
        return 0;
    };
    int32_t GetYCoord() override
    {
        return 0;
    };
    int32_t GetWidth() override
    {
        return 0;
    };
    int32_t GetHeight() override
    {
        return 0;
    };
    int32_t GetEditStateFlags() override
    {
        return 0;
    };
    int32_t GetSelectX() override
    {
        return selectX;
    };
    int32_t GetSelectY() override
    {
        return selectY;
    };
    int32_t GetSelectWidth() override
    {
        return width;
    };
    int32_t GetSelectXHeight() override
    {
        return height;
    };
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> GetTouchHandleState(
        OHOS::NWeb::NWebTouchHandleState::TouchHandleType type) override
    {
        return nullptr;
    }
    bool GetIsLongPressActived() override
    {
        return isLongPresseActived;
    }

private:
    int32_t selectX = 100;
    int32_t selectY = 200;
    int32_t width = 150;
    int32_t height = 50;
    bool isLongPresseActived = false;
};

class NWebTouchHandleStateMockImpl : public OHOS::NWeb::NWebTouchHandleState {
public:
    NWebTouchHandleStateMockImpl() = default;
    MOCK_METHOD(int32_t, GetTouchHandleId, (), (override));
    MOCK_METHOD(int32_t, GetX, (), (override));
    MOCK_METHOD(int32_t, GetY, (), (override));
    MOCK_METHOD(int32_t, GetViewPortX, (), (override));
    MOCK_METHOD(int32_t, GetViewPortY, (), (override));
    MOCK_METHOD(TouchHandleType, GetTouchHandleType, (), (override));
    MOCK_METHOD(bool, IsEnable, (), (override));
    MOCK_METHOD(float, GetAlpha, (), (override));
    MOCK_METHOD(float, GetEdgeHeight, (), (override));
};

class NWebTouchHandleStateDummy : public OHOS::NWeb::NWebTouchHandleState {
public:
    NWebTouchHandleStateDummy() = default;
    int32_t GetTouchHandleId() override
    {
        return -1;
    };
    int32_t GetX() override
    {
        return 0;
    };
    int32_t GetY() override
    {
        return 0;
    };
    int32_t GetViewPortX() override
    {
        return 0;
    };
    int32_t GetViewPortY() override
    {
        return 0;
    };
    TouchHandleType GetTouchHandleType() override
    {
        return TouchHandleType::SELECTION_BEGIN_HANDLE;
    };
    bool IsEnable() override
    {
        return false;
    };
    float GetAlpha() override
    {
        return 0.0;
    };
    float GetEdgeHeight() override
    {
        return 0.0;
    };
};

class NWebTouchHandleStateEndDummy : public OHOS::NWeb::NWebTouchHandleState {
public:
    NWebTouchHandleStateEndDummy() = default;
    int32_t GetTouchHandleId() override
    {
        return -1;
    };
    int32_t GetX() override
    {
        return 0;
    };
    int32_t GetY() override
    {
        return 0;
    };
    int32_t GetViewPortX() override
    {
        return 0;
    };
    int32_t GetViewPortY() override
    {
        return 0;
    };
    TouchHandleType GetTouchHandleType() override
    {
        return TouchHandleType::SELECTION_END_HANDLE;
    };
    bool IsEnable() override
    {
        return false;
    };
    float GetAlpha() override
    {
        return 0.0;
    };
    float GetEdgeHeight() override
    {
        return edgeHeight;
    };

private:
    float edgeHeight = 10.0;
};

class NWebTouchHandleStateBeginDummy : public OHOS::NWeb::NWebTouchHandleState {
public:
    NWebTouchHandleStateBeginDummy() = default;
    int32_t GetTouchHandleId() override
    {
        return -1;
    };
    int32_t GetX() override
    {
        return 0;
    };
    int32_t GetY() override
    {
        return 0;
    };
    int32_t GetViewPortX() override
    {
        return 0;
    };
    int32_t GetViewPortY() override
    {
        return 0;
    };
    TouchHandleType GetTouchHandleType() override
    {
        return TouchHandleType::SELECTION_BEGIN_HANDLE;
    };
    bool IsEnable() override
    {
        return false;
    };
    float GetAlpha() override
    {
        return 0.0;
    };
    float GetEdgeHeight() override
    {
        return edgeHeight;
    };

private:
    float edgeHeight = 10.0;
};


class WebPatternPartTwoTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void WebPatternPartTwoTest::SetUpTestCase() {}
void WebPatternPartTwoTest::TearDownTestCase() {}
void WebPatternPartTwoTest::SetUp() {}
void WebPatternPartTwoTest::TearDown() {}

/**
 * @tc.name: OnQuickMenuDismissed001
 * @tc.desc: OnQuickMenuDismissed.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, OnQuickMenuDismissed001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    webPattern->OnQuickMenuDismissed();
    EXPECT_NE(webPattern, nullptr);
#endif
}

class ViewDataWrapMock : public ViewDataWrap {
public:
    MOCK_METHOD(const std::string&, GetBundleName, (), (const, override));
    MOCK_METHOD(const std::string&, GetModuleName, (), (const, override));
    MOCK_METHOD(const std::string&, GetAbilityName, (), (const, override));
    MOCK_METHOD(const std::string&, GetPageUrl, (), (const, override));
    MOCK_METHOD(const std::vector<RefPtr<PageNodeInfoWrap>>&, GetPageNodeInfoWraps, (), ());
    MOCK_METHOD(const NG::RectF&, GetPageRect, (), (const, override));
    MOCK_METHOD(bool, GetUserSelected, (), (const, override));
    MOCK_METHOD(bool, GetOtherAccount, (), (const, override));
    MOCK_METHOD(void, SetBundleName, (const std::string& bundleName), (override));
    MOCK_METHOD(void, SetModuleName, (const std::string& moduleName), (override));
    MOCK_METHOD(void, SetAbilityName, (const std::string& abilityName), (override));
    MOCK_METHOD(void, SetPageUrl, (const std::string& pageUrl), (override));
    MOCK_METHOD(void, AddPageNodeInfoWrap, (RefPtr<PageNodeInfoWrap> pageNodeInfoWrap), (override));
    MOCK_METHOD(void, SetPageRect, (const NG::RectF& rect), (override));
    MOCK_METHOD(void, SetUserSelected, (bool isUserSelected), (override));
    MOCK_METHOD(void, SetOtherAccount, (bool isOtherAccount), (override));
};

/**
 * @tc.name: DumpViewDataPageNode001
 * @tc.desc: DumpViewDataPageNode.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, DumpViewDataPageNode001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    auto viewDataWrap = RefPtr<ViewDataWrapMock>();
    viewDataWrap = nullptr;
    bool needsRecordData = true;
    webPattern->DumpViewDataPageNode(viewDataWrap, needsRecordData);
    EXPECT_EQ(viewDataWrap, nullptr);
#endif
}

/**
 * @tc.name: DumpViewDataPageNode002
 * @tc.desc: DumpViewDataPageNode.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, DumpViewDataPageNode002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    auto viewDataWrap = RefPtr<ViewDataWrapMock>();
    bool needsRecordData = true;
    webPattern->DumpViewDataPageNode(viewDataWrap, needsRecordData);
    EXPECT_NE(webPattern, nullptr);
#endif
}

class PageNodeInfoWrapMock : public PageNodeInfoWrap {
public:
    MOCK_METHOD(void, SetId, (int32_t id), (override));
    MOCK_METHOD(int32_t, GetId, (), (const, override));
    MOCK_METHOD(void, SetDepth, (int32_t depth), (override));
    MOCK_METHOD(int32_t, GetDepth, (), (const, override));
    MOCK_METHOD(void, SetAutoFillType, (AceAutoFillType autoFillType), (override));
    MOCK_METHOD(AceAutoFillType, GetAutoFillType, (), (const, override));
    MOCK_METHOD(void, SetTag, (const std::string& tag), (override));
    MOCK_METHOD(const std::string&, GetTag, (), (const, override));
    MOCK_METHOD(void, SetValue, (const std::string& value), (override));
    MOCK_METHOD(const std::string&, GetValue, (), (const, override));
    MOCK_METHOD(void, SetPlaceholder, (const std::string& placeholder), (override));
    MOCK_METHOD(const std::string&, GetPlaceholder, (), (const, override));
    MOCK_METHOD(void, SetMetadata, (const std::string& metadata), (override));
    MOCK_METHOD(const std::string&, GetMetadata, (), (const, override));
    MOCK_METHOD(void, SetPasswordRules, (const std::string& passwordRules), (override));
    MOCK_METHOD(const std::string&, GetPasswordRules, (), (const, override));
    MOCK_METHOD(void, SetEnableAutoFill, (bool enableAutoFill), (override));
    MOCK_METHOD(bool, GetEnableAutoFill, (), (const, override));
    MOCK_METHOD(void, SetIsFocus, (bool isFocus), (override));
    MOCK_METHOD(bool, GetIsFocus, (), (const, override));
    MOCK_METHOD(void, SetPageNodeRect, (const NG::RectF& rect), (override));
    MOCK_METHOD(const NG::RectF&, GetPageNodeRect, (), (const, override));
};

/**
 * @tc.name: NotifyFillRequestSuccess001
 * @tc.desc: NotifyFillRequestSuccess.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, NotifyFillRequestSuccess001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    auto viewDataWrap = RefPtr<ViewDataWrapMock>();
    viewDataWrap = nullptr;
    RefPtr<PageNodeInfoWrapMock> nodeWrap = AceType::MakeRefPtr<PageNodeInfoWrapMock>();
    AceAutoFillType autoFillType = AceAutoFillType::ACE_DETAIL_INFO_WITHOUT_STREET;
    webPattern->NotifyFillRequestSuccess(viewDataWrap, nodeWrap, autoFillType);
    EXPECT_EQ(viewDataWrap, nullptr);
    webPattern->requestedWebOffset_ = OffsetF();
    webPattern->NotifyFillRequestSuccess(viewDataWrap, nodeWrap, autoFillType);
#endif
}

/**
 * @tc.name: NotifyFillRequestSuccess002
 * @tc.desc: NotifyFillRequestSuccess.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, NotifyFillRequestSuccess002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    auto viewDataWrap = AceType::MakeRefPtr<ViewDataWrapMock>();
    RefPtr<PageNodeInfoWrapMock> nodeWrap = AceType::MakeRefPtr<PageNodeInfoWrapMock>();
    std::vector<RefPtr<PageNodeInfoWrap>> nodeInfoWraps { nodeWrap };
    std::string pageUrl = "http://example.com";
    EXPECT_CALL(*viewDataWrap, GetPageNodeInfoWraps()).WillOnce(ReturnRef(nodeInfoWraps));
    EXPECT_CALL(*nodeWrap, GetAutoFillType()).WillOnce(Return(AceAutoFillType::ACE_UNSPECIFIED));
    EXPECT_CALL(*nodeWrap, GetIsFocus()).WillOnce(Return(false));
    EXPECT_CALL(*viewDataWrap, GetPageUrl()).WillOnce(ReturnRef(pageUrl));
    EXPECT_CALL(*viewDataWrap, GetOtherAccount()).WillOnce(Return(true));
    AceAutoFillType autoFillType = AceAutoFillType::ACE_DETAIL_INFO_WITHOUT_STREET;
    webPattern->NotifyFillRequestSuccess(viewDataWrap, nodeWrap, autoFillType);
#endif
}

/**
 * @tc.name: NotifyFillRequestSuccess003
 * @tc.desc: NotifyFillRequestSuccess.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, NotifyFillRequestSuccess003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    auto viewDataWrap = AceType::MakeRefPtr<ViewDataWrapMock>();
    auto nodeWrap = AceType::MakeRefPtr<PageNodeInfoWrapMock>();
    std::vector<RefPtr<PageNodeInfoWrap>> nodeInfoWraps { nodeWrap };
    std::string pageUrl = "http://example.com";
    std::string metadata = "metadata";
    std::string value = "value";
    EXPECT_CALL(*viewDataWrap, GetPageNodeInfoWraps()).WillOnce(ReturnRef(nodeInfoWraps));
    EXPECT_CALL(*nodeWrap, GetAutoFillType()).WillOnce(Return(AceAutoFillType::ACE_DETAIL_INFO_WITHOUT_STREET));
    EXPECT_CALL(*nodeWrap, GetIsFocus()).WillOnce(Return(true));
    EXPECT_CALL(*nodeWrap, GetMetadata()).WillOnce(ReturnRef(metadata));
    EXPECT_CALL(*nodeWrap, GetValue()).WillOnce(ReturnRef(value));
    EXPECT_CALL(*viewDataWrap, GetPageUrl()).WillOnce(ReturnRef(pageUrl));
    EXPECT_CALL(*viewDataWrap, GetOtherAccount()).WillOnce(Return(true));
    webPattern->NotifyFillRequestSuccess(viewDataWrap, nodeWrap, AceAutoFillType::ACE_UNSPECIFIED);
#endif
}

/**
 * @tc.name: NotifyFillRequestFailed001
 * @tc.desc: NotifyFillRequestFailed.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, NotifyFillRequestFailed001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    int32_t errCode = 4000;
    const std::string fillContent = "fillContent";
    bool isPopup = false;
    webPattern->isPasswordFill_ = false;
    webPattern->NotifyFillRequestFailed(errCode, fillContent, isPopup);
    EXPECT_EQ(webPattern->isPasswordFill_, false);
#endif
}

/**
 * @tc.name: NotifyFillRequestFailed002
 * @tc.desc: NotifyFillRequestFailed.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, NotifyFillRequestFailed002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    int32_t errCode = 4000;
    const std::string fillContent = "fillContent";
    bool isPopup = false;
    webPattern->isPasswordFill_ = true;
    webPattern->NotifyFillRequestFailed(errCode, fillContent, isPopup);
    EXPECT_EQ(webPattern->isPasswordFill_, true);
#endif
}

/**
 * @tc.name: ParseViewDataNumber001
 * @tc.desc: ParseViewDataNumber.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, ParseViewDataNumber001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    const std::string key = "key";
    int32_t value = 0;
    RefPtr<PageNodeInfoWrapMock> node = AceType::MakeRefPtr<PageNodeInfoWrapMock>();
    RectT<float> rect;
    float viewScale = 0;
    webPattern->ParseViewDataNumber(key, value, node, rect, viewScale);
    EXPECT_EQ(viewScale, 0);
#endif
}

/**
 * @tc.name: ParseViewDataNumber002
 * @tc.desc: ParseViewDataNumber.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, ParseViewDataNumber002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    const std::string key = "key";
    int32_t value = 0;
    RefPtr<PageNodeInfoWrapMock> node = AceType::MakeRefPtr<PageNodeInfoWrapMock>();
    node = nullptr;
    RectT<float> rect;
    float viewScale = 1;
    webPattern->ParseViewDataNumber(key, value, node, rect, viewScale);
    EXPECT_EQ(viewScale, 1);
    EXPECT_EQ(node, nullptr);
#endif
}

/**
 * @tc.name: ParseViewDataNumber003
 * @tc.desc: ParseViewDataNumber.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, ParseViewDataNumber003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    const std::string key = OHOS::NWeb::NWEB_VIEW_DATA_KEY_FOCUS;
    int32_t value = 0;
    RefPtr<NiceMock<PageNodeInfoWrapMock>> node = AceType::MakeRefPtr<NiceMock<PageNodeInfoWrapMock>>();
    RectT<float> rect;
    float viewScale = 1;
    webPattern->ParseViewDataNumber(key, value, node, rect, viewScale);
    EXPECT_EQ(viewScale, 1);
    EXPECT_NE(node, nullptr);
    EXPECT_EQ(key, OHOS::NWeb::NWEB_VIEW_DATA_KEY_FOCUS);
#endif
}

/**
 * @tc.name: ParseViewDataNumber004
 * @tc.desc: ParseViewDataNumber.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, ParseViewDataNumber004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    const std::string key = OHOS::NWeb::NWEB_VIEW_DATA_KEY_RECT_X;
    int32_t value = 0;
    RefPtr<NiceMock<PageNodeInfoWrapMock>> node = AceType::MakeRefPtr<NiceMock<PageNodeInfoWrapMock>>();
    RectT<float> rect;
    float viewScale = 1;
    webPattern->ParseViewDataNumber(key, value, node, rect, viewScale);
    EXPECT_EQ(viewScale, 1);
    EXPECT_NE(node, nullptr);
    EXPECT_EQ(key, OHOS::NWeb::NWEB_VIEW_DATA_KEY_RECT_X);
#endif
}

/**
 * @tc.name: ParseViewDataNumber005
 * @tc.desc: ParseViewDataNumber.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, ParseViewDataNumber005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    const std::string key = OHOS::NWeb::NWEB_VIEW_DATA_KEY_RECT_Y;
    int32_t value = 0;
    RefPtr<PageNodeInfoWrapMock> node = AceType::MakeRefPtr<PageNodeInfoWrapMock>();
    RectT<float> rect;
    float viewScale = 1;
    webPattern->ParseViewDataNumber(key, value, node, rect, viewScale);
    EXPECT_EQ(viewScale, 1);
    EXPECT_NE(node, nullptr);
    EXPECT_EQ(key, OHOS::NWeb::NWEB_VIEW_DATA_KEY_RECT_Y);
#endif
}

/**
 * @tc.name: ParseViewDataNumber006
 * @tc.desc: ParseViewDataNumber.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, ParseViewDataNumber006, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    const std::string key = OHOS::NWeb::NWEB_VIEW_DATA_KEY_RECT_W;
    int32_t value = 0;
    RefPtr<PageNodeInfoWrapMock> node = AceType::MakeRefPtr<PageNodeInfoWrapMock>();
    RectT<float> rect;
    float viewScale = 1;
    webPattern->ParseViewDataNumber(key, value, node, rect, viewScale);
    EXPECT_EQ(viewScale, 1);
    EXPECT_NE(node, nullptr);
    EXPECT_EQ(key, OHOS::NWeb::NWEB_VIEW_DATA_KEY_RECT_W);
#endif
}

/**
 * @tc.name: ParseViewDataNumber007
 * @tc.desc: ParseViewDataNumber.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, ParseViewDataNumber007, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    const std::string key = OHOS::NWeb::NWEB_VIEW_DATA_KEY_RECT_H;
    int32_t value = 0;
    RefPtr<PageNodeInfoWrapMock> node = AceType::MakeRefPtr<PageNodeInfoWrapMock>();
    RectT<float> rect;
    float viewScale = 1;
    webPattern->ParseViewDataNumber(key, value, node, rect, viewScale);
    EXPECT_EQ(viewScale, 1);
    EXPECT_NE(node, nullptr);
    EXPECT_EQ(key, OHOS::NWeb::NWEB_VIEW_DATA_KEY_RECT_H);
#endif
}

/**
 * @tc.name: ParseNWebViewDataNode001
 * @tc.desc: ParseNWebViewDataNode.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, ParseNWebViewDataNode001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    MockPipelineContext::SetUp();
    auto child = std::make_unique<JsonValue>();
    std::vector<RefPtr<PageNodeInfoWrap>> nodeInfos;
    int32_t nId = 1;
    webPattern->ParseNWebViewDataNode(std::move(child), nodeInfos, nId);
    MockPipelineContext::TearDown();
#endif
}

/**
 * @tc.name: GetFocusedType001
 * @tc.desc: GetFocusedType.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, GetFocusedType001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    webPattern->pageNodeInfo_.clear();
    webPattern->GetFocusedType();
    EXPECT_EQ(webPattern->GetFocusedType(), AceAutoFillType::ACE_UNSPECIFIED);
#endif
}

/**
 * @tc.name: GetFocusedType002
 * @tc.desc: GetFocusedType.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, GetFocusedType002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    RefPtr<PageNodeInfoWrapMock> pageNodeInfo = AceType::MakeRefPtr<PageNodeInfoWrapMock>();
    webPattern->pageNodeInfo_.push_back(pageNodeInfo);
    EXPECT_CALL(*pageNodeInfo, GetIsFocus()).WillRepeatedly(::testing::Return(false));
    webPattern->GetFocusedType();
    EXPECT_EQ(webPattern->GetFocusedType(), AceAutoFillType::ACE_UNSPECIFIED);
#endif
}

/**
 * @tc.name: GetFocusedType003
 * @tc.desc: GetFocusedType.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, GetFocusedType003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    RefPtr<PageNodeInfoWrapMock> pageNodeInfo = AceType::MakeRefPtr<PageNodeInfoWrapMock>();
    webPattern->pageNodeInfo_.push_back(pageNodeInfo);
    EXPECT_CALL(*pageNodeInfo, GetIsFocus()).WillRepeatedly(::testing::Return(true));
    EXPECT_CALL(*pageNodeInfo, GetAutoFillType()).WillRepeatedly(::testing::Return(AceAutoFillType::ACE_UNSPECIFIED));
    AceAutoFillType result = webPattern->GetFocusedType();
    EXPECT_EQ(result, AceAutoFillType::ACE_UNSPECIFIED);
#endif
}

/**
 * @tc.name: GetFocusedType004
 * @tc.desc: GetFocusedType.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, GetFocusedType004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    RefPtr<PageNodeInfoWrapMock> pageNodeInfo = AceType::MakeRefPtr<PageNodeInfoWrapMock>();
    RefPtr<PageNodeInfoWrapMock> pageNodeInfo_no = AceType::MakeRefPtr<PageNodeInfoWrapMock>();
    webPattern->pageNodeInfo_.push_back(pageNodeInfo);
    webPattern->pageNodeInfo_.push_back(pageNodeInfo_no);
    EXPECT_CALL(*pageNodeInfo, GetIsFocus()).WillRepeatedly(::testing::Return(true));
    EXPECT_CALL(*pageNodeInfo, GetAutoFillType()).WillRepeatedly(::testing::Return(AceAutoFillType::ACE_UNSPECIFIED));
    EXPECT_CALL(*pageNodeInfo_no, GetIsFocus()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(*pageNodeInfo, GetIsFocus()).WillRepeatedly(::testing::Return(false));
    AceAutoFillType result = webPattern->GetFocusedType();
    EXPECT_EQ(result, AceAutoFillType::ACE_UNSPECIFIED);
#endif
}

/**
 * @tc.name: RequestAutoFill001
 * @tc.desc: RequestAutoFill.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, RequestAutoFill001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    auto host = webPattern->GetHost();
    EXPECT_NE(host, nullptr);
    auto ret = webPattern->RequestAutoFill(AceAutoFillType::ACE_UNSPECIFIED);
    EXPECT_EQ(ret, false);
#endif
}

/**
 * @tc.name: RequestAutoSave001
 * @tc.desc: RequestAutoSave.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, RequestAutoSave001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    auto host = webPattern->GetHost();
    EXPECT_NE(host, nullptr);
    auto ret = webPattern->RequestAutoSave();
    EXPECT_EQ(ret, false);
#endif
}

/**
 * @tc.name: UpdateAutoFillPopup001
 * @tc.desc: UpdateAutoFillPopup.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, UpdateAutoFillPopup001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    webPattern->isAutoFillClosing_ = true;
    auto ret = webPattern->UpdateAutoFillPopup();
    EXPECT_EQ(ret, false);
#endif
}

/**
 * @tc.name: CloseAutoFillPopup001
 * @tc.desc: CloseAutoFillPopup.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, CloseAutoFillPopup001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    auto ret = webPattern->CloseAutoFillPopup();
    EXPECT_EQ(ret, false);
#endif
}

/**
 * @tc.name: IsRootNeedExportTexture_001
 * @tc.desc: IsRootNeedExportTexture.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, IsRootNeedExportTexture_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });

    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto ret = webPattern->IsRootNeedExportTexture();
    EXPECT_EQ(ret, false);

#endif
}

/**
 * @tc.name: OnOverScrollModeUpdate_001
 * @tc.desc: OnOverScrollModeUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, OnOverScrollModeUpdate_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });

    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->OnOverScrollModeUpdate(0);

#endif
}

/**
 * @tc.name: OnOverScrollModeUpdate_002
 * @tc.desc: OnOverScrollModeUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, OnOverScrollModeUpdate_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });

    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    webPattern->delegate_ = nullptr;
    webPattern->OnOverScrollModeUpdate(0);

#endif
}

/**
 * @tc.name: OnCopyOptionModeUpdate_001
 * @tc.desc: OnCopyOptionModeUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, OnCopyOptionModeUpdate_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });

    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->OnCopyOptionModeUpdate(0);

#endif
}

/**
 * @tc.name: OnCopyOptionModeUpdate_002
 * @tc.desc: OnCopyOptionModeUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, OnCopyOptionModeUpdate_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });

    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    webPattern->delegate_ = nullptr;
    webPattern->OnCopyOptionModeUpdate(0);

#endif
}

/**
 * @tc.name: OnMetaViewportUpdate_001
 * @tc.desc: OnMetaViewportUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, OnMetaViewportUpdate_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });

    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->OnMetaViewportUpdate(true);

#endif
}

/**
 * @tc.name: OnMetaViewportUpdate_002
 * @tc.desc: OnMetaViewportUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, OnMetaViewportUpdate_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });

    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    webPattern->delegate_ = nullptr;
    webPattern->OnMetaViewportUpdate(true);

#endif
}

/**
 * @tc.name: OnOverlayScrollbarEnabledUpdate_001
 * @tc.desc: OnOverlayScrollbarEnabledUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, OnOverlayScrollbarEnabledUpdate_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });

    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->OnOverlayScrollbarEnabledUpdate(true);

#endif
}

/**
 * @tc.name: OnOverlayScrollbarEnabledUpdate_002
 * @tc.desc: OnOverlayScrollbarEnabledUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, OnOverlayScrollbarEnabledUpdate_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });

    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->delegate_ = nullptr;
    webPattern->OnOverlayScrollbarEnabledUpdate(true);

#endif
}

/**
 * @tc.name: OnNativeEmbedModeEnabledUpdate_001
 * @tc.desc: OnNativeEmbedModeEnabledUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, OnNativeEmbedModeEnabledUpdate_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });

    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->OnNativeEmbedModeEnabledUpdate(true);

#endif
}

/**
 * @tc.name: OnNativeEmbedModeEnabledUpdate_002
 * @tc.desc: OnNativeEmbedModeEnabledUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, OnNativeEmbedModeEnabledUpdate_002, TestSize.Level1)

{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });

    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->delegate_ = nullptr;
    webPattern->OnNativeEmbedModeEnabledUpdate(true);

#endif
}

/**
 * @tc.name: OnNativeEmbedRuleTagUpdate_001
 * @tc.desc: OnNativeEmbedRuleTagUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, OnNativeEmbedRuleTagUpdate_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });

    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->OnNativeEmbedRuleTagUpdate("test");

#endif
}

/**
 * @tc.name: OnNativeEmbedRuleTagUpdate_002
 * @tc.desc: OnNativeEmbedRuleTagUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, OnNativeEmbedRuleTagUpdate_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });

    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->delegate_ = nullptr;
    webPattern->OnNativeEmbedRuleTagUpdate("test");

#endif
}

/**
 * @tc.name: OnNativeEmbedRuleTypeUpdate_001
 * @tc.desc: OnNativeEmbedRuleTypeUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, OnNativeEmbedRuleTypeUpdate_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });

    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->OnNativeEmbedRuleTypeUpdate("test");

#endif
}

/**
 * @tc.name: OnNativeEmbedRuleTypeUpdate_002
 * @tc.desc: OnNativeEmbedRuleTypeUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, OnNativeEmbedRuleTypeUpdate_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });

    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->delegate_ = nullptr;
    webPattern->OnNativeEmbedRuleTypeUpdate("test");

#endif
}

/**
 * @tc.name: OnTextAutosizingUpdate_001
 * @tc.desc: OnTextAutosizingUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, OnTextAutosizingUpdate_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });

    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->OnTextAutosizingUpdate(true);

#endif
}

/**
 * @tc.name: OnTextAutosizingUpdate_002
 * @tc.desc: OnTextAutosizingUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, OnTextAutosizingUpdate_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });

    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->delegate_ = nullptr;
    webPattern->OnTextAutosizingUpdate(true);

#endif
}

/**
 * @tc.name: OnKeyboardAvoidModeUpdate_001
 * @tc.desc: OnKeyboardAvoidModeUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, OnKeyboardAvoidModeUpdate_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });

    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->OnKeyboardAvoidModeUpdate(WebKeyboardAvoidMode::RESIZE_CONTENT);
    EXPECT_EQ(webPattern->keyBoardAvoidMode_, WebKeyboardAvoidMode::RESIZE_CONTENT);

#endif
}

/**
 * @tc.name: HandleScroll_001
 * @tc.desc: HandleScroll.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, HandleScroll_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });

    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->needOnFocus_ = true;
    ScrollResult result = webPattern->HandleScroll(1.f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL, 1.f);
    EXPECT_EQ(result.remain, 0.f);
    EXPECT_FALSE(result.reachEdge);

#endif
}

/**
 * @tc.name: HandleScroll_002
 * @tc.desc: HandleScroll.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, HandleScroll_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });

    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    ScrollResult result = webPattern->HandleScroll(
        webPattern->GetNestedScrollParent(), 1.f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL);
    EXPECT_EQ(result.remain, 0.f);
    EXPECT_FALSE(result.reachEdge);

#endif
}

/**
 * @tc.name: HandleScrollVelocity_001
 * @tc.desc: HandleScrollVelocity.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, HandleScrollVelocity_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });

    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto result = webPattern->HandleScrollVelocity(1.f, webPattern->GetNestedScrollParent());
    EXPECT_FALSE(result);

#endif
}

/**
 * @tc.name: HandleScrollVelocity_002
 * @tc.desc: HandleScrollVelocity.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, HandleScrollVelocity_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });

    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto result = webPattern->HandleScrollVelocity(webPattern->GetNestedScrollParent(), 1.f);
    EXPECT_FALSE(result);

#endif
}

/**
 * @tc.name: OnScrollStartRecursive_001
 * @tc.desc: OnScrollStartRecursive.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, OnScrollStartRecursive_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });

    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->OnScrollStartRecursive(webPattern, 1.f, 1.f);
    EXPECT_TRUE(webPattern->isFirstFlingScrollVelocity_);
    EXPECT_TRUE(webPattern->isScrollStarted_);

#endif
}

/**
 * @tc.name: OnScrollStartRecursive_002
 * @tc.desc: OnScrollStartRecursive.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, OnScrollStartRecursive_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });

    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->OnScrollStartRecursive(1.f);
    EXPECT_TRUE(webPattern->isFirstFlingScrollVelocity_);
    EXPECT_TRUE(webPattern->isScrollStarted_);

#endif
}

/**
 * @tc.name: OnScrollEndRecursive_001
 * @tc.desc: OnScrollEndRecursive.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, OnScrollEndRecursive_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });

    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->isScrollStarted_ = true;
    webPattern->isNestedInterrupt_ = true;
    std::optional<float> velocity = 1.f;
    webPattern->OnScrollEndRecursive(velocity);
    EXPECT_FALSE(webPattern->isScrollStarted_);
    EXPECT_FALSE(webPattern->isNestedInterrupt_);
#endif
}

/**
 * @tc.name: OnScrollEndRecursive_002
 * @tc.desc: OnScrollEndRecursive.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, OnScrollEndRecursive_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });

    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->isScrollStarted_ = false;
    webPattern->isNestedInterrupt_ = true;
    std::optional<float> velocity = 1.f;
    webPattern->OnScrollEndRecursive(velocity);
    EXPECT_FALSE(webPattern->isScrollStarted_);
    EXPECT_TRUE(webPattern->isNestedInterrupt_);

#endif
}

/**
 * @tc.name: SetLayoutMode_001
 * @tc.desc: SetLayoutMode.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, SetLayoutMode_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });

    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto mode = static_cast<OHOS::Ace::WebLayoutMode>(WebLayoutMode::FIT_CONTENT);
    webPattern->SetLayoutMode(WebLayoutMode::NONE);
    webPattern->SetLayoutMode(mode);
    EXPECT_EQ(webPattern->layoutMode_, mode);
    webPattern->SetLayoutMode(WebLayoutMode::NONE);
    EXPECT_TRUE(webPattern->isLayoutModeChanged_);
#endif
}

/**
 * @tc.name: SetRenderMode_001
 * @tc.desc: SetRenderMode.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, SetRenderMode_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });

    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto renderMode = RenderMode::ASYNC_RENDER;
    webPattern->SetRenderMode(renderMode);
    webPattern->SetRenderMode(renderMode);
    EXPECT_EQ(webPattern->renderMode_, renderMode);
#endif
}

/**
 * @tc.name: GetParentAxis_001
 * @tc.desc: GetParentAxis.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, GetParentAxis_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });

    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->axis_ = Axis::HORIZONTAL;
    webPattern->GetParentAxis();
    EXPECT_EQ(webPattern->axis_, Axis::HORIZONTAL);

#endif
}

/**
 * @tc.name: OnAttachContext_001
 * @tc.desc: OnAttachContext.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, OnAttachContext_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });

    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    MockPipelineContext::SetUp();
    auto pipelineContext = MockPipelineContext::GetCurrent();
    webPattern->OnAttachContext(Referenced::RawPtr(pipelineContext));
    MockPipelineContext::TearDown();
    EXPECT_EQ(webPattern->instanceId_, 0);

#endif
}

/**
 * @tc.name: OnAttachContext_002
 * @tc.desc: OnAttachContext.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, OnAttachContext_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });

    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->delegate_ = nullptr;
    webPattern->observer_ = nullptr;
    webPattern->updateInstanceIdCallback_ = nullptr;
    webPattern->renderSurface_ = nullptr;
    MockPipelineContext::SetUp();
    auto pipelineContext = MockPipelineContext::GetCurrent();
    webPattern->OnAttachContext(Referenced::RawPtr(pipelineContext));
    MockPipelineContext::TearDown();
    EXPECT_EQ(webPattern->instanceId_, 0);

#endif
}

/**
 * @tc.name: OnEnableFollowSystemFontWeightUpdate_001
 * @tc.desc: OnEnableFollowSystemFontWeightUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, OnEnableFollowSystemFontWeightUpdate_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });

    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->OnEnableFollowSystemFontWeightUpdate(true);

#endif
}

/**
 * @tc.name: OnEnableFollowSystemFontWeightUpdate_002
 * @tc.desc: OnEnableFollowSystemFontWeightUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, OnEnableFollowSystemFontWeightUpdate_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });

    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->delegate_ = nullptr;
    webPattern->OnEnableFollowSystemFontWeightUpdate(true);

#endif
}

/**
 * @tc.name: RunJavascriptAsync_001
 * @tc.desc: RunJavascriptAsync.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, RunJavascriptAsync_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });

    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->delegate_ = nullptr;
    auto ret = webPattern->RunJavascriptAsync("console.log('hello')", [](const std::string&) {});
    ASSERT_FALSE(ret);
#endif
}

/**
 * @tc.name: SetActiveStatusInner_001
 * @tc.desc: Set ArkWeb active or inactive, and when is force
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartTwoTest, SetActiveStatusInner_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->isVisible_ = false;
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->SetActiveStatusInner(true);
    EXPECT_TRUE(webPattern->isActive_);
    webPattern->SetActiveStatusInner(false);
    EXPECT_FALSE(webPattern->isActive_);
    webPattern->SetActiveStatusInner(true, true);
    EXPECT_TRUE(webPattern->isActive_);
    webPattern->SetActiveStatusInner(false, true);
    EXPECT_FALSE(webPattern->isActive_);
#endif
}
}