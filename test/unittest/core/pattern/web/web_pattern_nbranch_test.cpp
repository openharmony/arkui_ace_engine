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

#include <cstddef>
#include <gmock/gmock.h>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#define protected public
#define private public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/pattern/web/web_pattern.h"
#undef private
#undef protected
#include "base/json/json_util.h"
#include "core/common/ai/image_analyzer_manager.h"
#include "core/components_ng/base/ui_node.h"
#include "interfaces/inner_api/ace/ai/image_analyzer.h"
#include "test/mock/core/common/mock_container.h"
#include "cJSON.h"

#include "nweb.h"
#include "nweb_handler.h"
#include "nweb_autofill.h"
#include "core/components/web/resource/web_delegate.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/text/text_menu_extension.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/base/utils/system_properties.h"
#include "frameworks/core/components/text_overlay/text_overlay_theme.h"
#include "frameworks/core/components_ng/pattern/web/web_model_ng.h"
#include "frameworks/core/components_v2/inspector/textinput_composed_element.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::NWeb;
using ScriptItems = std::map<std::string, std::vector<std::string>>;
using WeakPtr = std::weak_ptr<OHOS::Ace::PipelineBase>;
using ErrorCallback = std::function<void(const std::string&)>;

namespace OHOS::Ace::NG {

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

class WebPatternBranchTestUT : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void WebPatternBranchTestUT::SetUpTestCase() {}
void WebPatternBranchTestUT::TearDownTestCase() {}
void WebPatternBranchTestUT::SetUp()
{
    MockPipelineContext::SetUp();
}
void WebPatternBranchTestUT::TearDown()
{
    MockPipelineContext::TearDown();
}

class NWebDateTimeChooserMock : public NWeb::NWebDateTimeChooser {
public:
    NWebDateTimeChooserMock() = default;
    NWeb::DateTimeChooserType GetType()
    {
        return NWeb::DateTimeChooserType::DTC_DATE;
    }

    double GetStep()
    {
        return 0;
    }

    NWeb::DateTime GetMinimum()
    {
        NWeb::DateTime time = {};
        return time;
    }

    NWeb::DateTime GetMaximum()
    {
        NWeb::DateTime time = {};
        return time;
    }

    NWeb::DateTime GetDialogValue()
    {
        NWeb::DateTime time = {};
        return time;
    }

    MOCK_METHOD0(GetHasSelected, bool());

    size_t GetSuggestionIndex()
    {
        size_t size = 0;
        return size;
    }
};

class WebDelegateMock : public OHOS::Ace::WebDelegate {
public:
    WebDelegateMock(const WeakPtr<PipelineBase>& context, ErrorCallback&& onError, const std::string& type, int32_t id)
        : WebDelegate(context, std::move(onError), type, id)
    {}
    MOCK_METHOD0(GetIsSmoothDragResizeEnabled, bool());
    MOCK_METHOD0(GetPendingSizeStatus, bool());
};

class FullScreenEnterEventMock : public FullScreenEnterEvent {
public:
    FullScreenEnterEventMock(
        const RefPtr<FullScreenExitHandler>& handler, int videoNaturalWidth, int videoNaturalHeight)
        : FullScreenEnterEvent(handler, videoNaturalWidth, videoNaturalHeight)
    {}
    ~FullScreenEnterEventMock() = default;
    MOCK_METHOD0(GetHandler, RefPtr<FullScreenExitHandler>());
};

class FullScreenExitHandlerMock : public FullScreenExitHandler {
public:
    FullScreenExitHandlerMock() = default;
    ~FullScreenExitHandlerMock() = default;
    void ExitFullScreen() {};
};

/**
 * @tc.name: IsRootNeedExportTexture
 * @tc.desc: IsRootNeedExportTexture.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternBranchTestUT, IsRootNeedExportTexture, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    frameNode->exportTextureInfo_ = AceType::MakeRefPtr<ExportTextureInfo>();
    frameNode->exportTextureInfo_->SetCurrentRenderType(NodeRenderType::RENDER_TYPE_DISPLAY);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    RefPtr<UINode> son = frameNode;
    RefPtr<UINode> parent =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    RefPtr<UINode> grandParent =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    parent->exportTextureInfo_ = AceType::MakeRefPtr<ExportTextureInfo>();
    grandParent->exportTextureInfo_ = AceType::MakeRefPtr<ExportTextureInfo>();
    parent->exportTextureInfo_->SetCurrentRenderType(NodeRenderType::RENDER_TYPE_DISPLAY);
    grandParent->exportTextureInfo_->SetCurrentRenderType(NodeRenderType::RENDER_TYPE_TEXTURE);
    son->SetParent(parent);
    parent->SetParent(grandParent);
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    bool flag = webPattern->IsRootNeedExportTexture();
    ASSERT_TRUE(flag);
#endif
}

/**
 * @tc.name: IsRootNeedExportTextureNull
 * @tc.desc: IsRootNeedExportTexture.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternBranchTestUT, IsRootNeedExportTextureNull, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    frameNode->exportTextureInfo_ = AceType::MakeRefPtr<ExportTextureInfo>();
    frameNode->exportTextureInfo_->SetCurrentRenderType(NodeRenderType::RENDER_TYPE_DISPLAY);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    RefPtr<UINode> son = frameNode;
    RefPtr<UINode> parent = nullptr;
    son->SetParent(parent);
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    bool flag = webPattern->IsRootNeedExportTexture();
    ASSERT_FALSE(flag);
#endif
}

/**
 * @tc.name: OnDefaultTextEncodingFormatUpdate
 * @tc.desc: OnDefaultTextEncodingFormatUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternBranchTestUT, OnDefaultTextEncodingFormatUpdate, TestSize.Level1)
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
    webPattern->delegate_ = nullptr;
    std::string tag = "value";
    webPattern->OnDefaultTextEncodingFormatUpdate(tag);
#endif
}

/**
 * @tc.name: DumpViewDataPageNode007
 * @tc.desc: DumpViewDataPageNode.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternBranchTestUT, DumpViewDataPageNode007, TestSize.Level1)
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
    auto host = webPattern->GetHost();
    EXPECT_NE(host, nullptr);
    DialogTheme::Builder builder;
    RefPtr<DialogTheme> theme = builder.Build(nullptr);
    EXPECT_NE(theme, nullptr);
    auto viewDataWrap = AceType::MakeRefPtr<ViewDataWrapMock>();
    EXPECT_CALL(*viewDataWrap, SetPageUrl(std::string("")));
    EXPECT_CALL(*viewDataWrap, SetUserSelected(false));
    EXPECT_CALL(*viewDataWrap, SetOtherAccount(false));
    MockPipelineContext::SetUp();

    auto webMsg = std::make_shared<OHOS::NWeb::NWebMessage>(NWeb::NWebValue::Type::NONE);
    webMsg->SetType(NWeb::NWebValue::Type::STRING);
    webMsg->SetString(std::string("{\"node\":{\"id\":1,\"name\":\"root\",\"children\":") +
        std::string("[{\"id\":2,\"name\":\"child1\",\"123\":\"test\"},{\"id\":3,\"name\":\"child2\"}],\"obj\":null}}"));
    webPattern->HandleAutoFillEvent(webMsg);
    bool needsRecordData = true;

    RefPtr<PageNodeInfoWrapMock> nodeWrap = AceType::MakeRefPtr<PageNodeInfoWrapMock>();
    std::vector<RefPtr<PageNodeInfoWrap>> nodeInfoWraps { nodeWrap };
    EXPECT_CALL(*viewDataWrap, AddPageNodeInfoWrap(testing::_));
    webPattern->pageNodeInfo_.push_back(nodeWrap);
    webPattern->DumpViewDataPageNode(viewDataWrap, needsRecordData);
    EXPECT_EQ(viewDataWrap, true);
    MockPipelineContext::TearDown();
#endif
}

/**
 * @tc.name: NotifyFillRequestSuccess008
 * @tc.desc: NotifyFillRequestSuccess.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternBranchTestUT, NotifyFillRequestSuccess008, TestSize.Level1)
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
    std::string metadata = "{\"isHint2Type\": true}";
    std::string value = "value";
    EXPECT_CALL(*viewDataWrap, GetPageNodeInfoWraps()).WillOnce(ReturnRef(nodeInfoWraps));
    EXPECT_CALL(*nodeWrap, GetAutoFillType()).WillOnce(Return(AceAutoFillType::ACE_DETAIL_INFO_WITHOUT_STREET));
    EXPECT_CALL(*nodeWrap, GetIsFocus()).WillOnce(Return(true));
    EXPECT_CALL(*nodeWrap, GetMetadata()).WillOnce(ReturnRef(metadata));
    EXPECT_CALL(*nodeWrap, GetValue()).WillOnce(ReturnRef(value));
    EXPECT_CALL(*nodeWrap, GetId()).WillOnce(Return(1));
    EXPECT_CALL(*viewDataWrap, GetPageUrl()).WillOnce(ReturnRef(pageUrl));
    EXPECT_CALL(*viewDataWrap, GetOtherAccount()).WillOnce(Return(true));
    webPattern->pageNodeInfo_.push_back(nodeWrap);
    webPattern->isPasswordFill_ = true;
    webPattern->NotifyFillRequestSuccess(viewDataWrap, nodeWrap, AceAutoFillType::ACE_UNSPECIFIED);
    EXPECT_EQ(webPattern->isPasswordFill_, true);
#endif
}

/**
 * @tc.name: NotifyFillRequestSuccess009
 * @tc.desc: NotifyFillRequestSuccess.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternBranchTestUT, NotifyFillRequestSuccess009, TestSize.Level1)
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
    std::string metadata = "{\"isHint2Type\": true}";
    std::string value = "value";
    NG::RectF noderect;
    EXPECT_CALL(*viewDataWrap, GetPageNodeInfoWraps()).WillOnce(ReturnRef(nodeInfoWraps));
    EXPECT_CALL(*nodeWrap, GetAutoFillType())
        .WillOnce(Return(AceAutoFillType::ACE_DETAIL_INFO_WITHOUT_STREET))
        .WillOnce(Return(AceAutoFillType::ACE_DETAIL_INFO_WITHOUT_STREET));
    EXPECT_CALL(*nodeWrap, GetIsFocus()).WillOnce(Return(true));
    EXPECT_CALL(*nodeWrap, GetMetadata()).WillOnce(ReturnRef(metadata));
    EXPECT_CALL(*nodeWrap, GetValue()).WillOnce(ReturnRef(value));
    EXPECT_CALL(*nodeWrap, GetId()).WillOnce(Return(1));
    EXPECT_CALL(*nodeWrap, GetPageNodeRect()).WillOnce(ReturnRef(noderect));

    EXPECT_CALL(*viewDataWrap, GetPageUrl()).WillOnce(ReturnRef(pageUrl));
    EXPECT_CALL(*viewDataWrap, GetOtherAccount()).WillOnce(Return(true));
    webPattern->pageNodeInfo_.push_back(nodeWrap);
    webPattern->NotifyFillRequestSuccess(viewDataWrap, nodeWrap, AceAutoFillType::ACE_UNSPECIFIED);
    EXPECT_EQ(webPattern->isPasswordFill_, false);
#endif
}

/**
 * @tc.name: GetHintTypeAndMetadata_001
 * @tc.desc: GetHintTypeAndMetadata.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternBranchTestUT, GetHintTypeAndMetadata_001, TestSize.Level1)
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

    const std::string attribute = OHOS::NWeb::NWEB_AUTOFILL_USERNAME;
    std::string value = "value";
    auto viewDataWrap = AceType::MakeRefPtr<ViewDataWrapMock>();
    auto nodeWrap = AceType::MakeRefPtr<PageNodeInfoWrapMock>();
    EXPECT_CALL(*nodeWrap, GetIsFocus()).WillOnce(Return(true));
    EXPECT_CALL(*nodeWrap, GetPlaceholder()).WillOnce(ReturnRef(value));
    webPattern->GetHintTypeAndMetadata(attribute, nodeWrap);
    EXPECT_EQ(webPattern->isPasswordFill_, true);
#endif
}

/**
 * @tc.name: GetHintTypeAndMetadata_002
 * @tc.desc: GetHintTypeAndMetadata.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternBranchTestUT, GetHintTypeAndMetadata_002, TestSize.Level1)
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

    const std::string attribute = OHOS::NWeb::NWEB_AUTOFILL_PASSWORD;
    std::string value = "value";
    auto viewDataWrap = AceType::MakeRefPtr<ViewDataWrapMock>();
    auto nodeWrap = AceType::MakeRefPtr<PageNodeInfoWrapMock>();
    EXPECT_CALL(*nodeWrap, GetIsFocus()).WillOnce(Return(true));
    EXPECT_CALL(*nodeWrap, GetPlaceholder()).WillOnce(ReturnRef(value));
    webPattern->GetHintTypeAndMetadata(attribute, nodeWrap);
    EXPECT_EQ(webPattern->isPasswordFill_, true);
#endif
}

/**
 * @tc.name: GetHintTypeAndMetadata_003
 * @tc.desc: GetHintTypeAndMetadata.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternBranchTestUT, GetHintTypeAndMetadata_003, TestSize.Level1)
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

    const std::string attribute = OHOS::NWeb::NWEB_AUTOFILL_NEW_PASSWORD;
    std::string value = "value";
    auto viewDataWrap = AceType::MakeRefPtr<ViewDataWrapMock>();
    auto nodeWrap = AceType::MakeRefPtr<PageNodeInfoWrapMock>();
    EXPECT_CALL(*nodeWrap, GetIsFocus()).WillOnce(Return(true));
    EXPECT_CALL(*nodeWrap, GetPlaceholder()).WillOnce(ReturnRef(value));
    webPattern->GetHintTypeAndMetadata(attribute, nodeWrap);
    EXPECT_EQ(webPattern->isPasswordFill_, true);
#endif
}

/**
 * @tc.name: GetHintTypeAndMetadata_004
 * @tc.desc: GetHintTypeAndMetadata.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternBranchTestUT, GetHintTypeAndMetadata_004, TestSize.Level1)
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

    const std::string attribute = "";
    std::string value = "value";
    auto viewDataWrap = AceType::MakeRefPtr<ViewDataWrapMock>();
    auto nodeWrap = AceType::MakeRefPtr<PageNodeInfoWrapMock>();
    EXPECT_CALL(*nodeWrap, GetPlaceholder()).WillOnce(ReturnRef(value));
    webPattern->GetHintTypeAndMetadata(attribute, nodeWrap);
    EXPECT_EQ(webPattern->isPasswordFill_, false);
#endif
}

/**
 * @tc.name: GetHintTypeAndMetadata_005
 * @tc.desc: GetHintTypeAndMetadata.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternBranchTestUT, GetHintTypeAndMetadata_005, TestSize.Level1)
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

    MockContainer::SetUp();
    const std::string attribute = "";
    std::string value = "value";
    auto viewDataWrap = AceType::MakeRefPtr<ViewDataWrapMock>();
    auto nodeWrap = AceType::MakeRefPtr<PageNodeInfoWrapMock>();
    EXPECT_CALL(*nodeWrap, GetPlaceholder()).WillOnce(ReturnRef(value));
    webPattern->GetHintTypeAndMetadata(attribute, nodeWrap);
    MockContainer::TearDown();
    EXPECT_EQ(webPattern->isPasswordFill_, false);
#endif
}

/**
 * @tc.name: GetHintTypeAndMetadata_006
 * @tc.desc: GetHintTypeAndMetadata.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternBranchTestUT, GetHintTypeAndMetadata_006, TestSize.Level1)
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

    const std::string attribute = OHOS::NWeb::NWEB_AUTOFILL_STREET_ADDRESS;
    std::string value = "value";
    auto viewDataWrap = AceType::MakeRefPtr<ViewDataWrapMock>();
    auto nodeWrap = AceType::MakeRefPtr<PageNodeInfoWrapMock>();
    EXPECT_CALL(*nodeWrap, GetIsFocus()).WillOnce(Return(false));
    EXPECT_CALL(*nodeWrap, GetPlaceholder()).WillOnce(ReturnRef(value));
    webPattern->GetHintTypeAndMetadata(attribute, nodeWrap);
    EXPECT_EQ(webPattern->isPasswordFill_, false);
#endif
}

/**
 * @tc.name: GetFocusedType
 * @tc.desc: GetFocusedType.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternBranchTestUT, GetFocusedType_001, TestSize.Level1)
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

    RefPtr<PageNodeInfoWrapMock> nodeWrap = AceType::MakeRefPtr<PageNodeInfoWrapMock>();
    std::vector<RefPtr<PageNodeInfoWrap>> nodeInfoWraps { nodeWrap };
    EXPECT_CALL(*nodeWrap, GetIsFocus()).WillOnce(Return(true));
    EXPECT_CALL(*nodeWrap, GetAutoFillType()).WillRepeatedly(::testing::Return(AceAutoFillType::ACE_UNSPECIFIED));
    webPattern->pageNodeInfo_.push_back(nodeWrap);
    EXPECT_EQ(webPattern->GetFocusedType(), AceAutoFillType::ACE_UNSPECIFIED);
#endif
}

/**
 * @tc.name: GetFocusedType
 * @tc.desc: GetFocusedType.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternBranchTestUT, GetFocusedType_002, TestSize.Level1)
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

    RefPtr<PageNodeInfoWrapMock> nodeWrap = AceType::MakeRefPtr<PageNodeInfoWrapMock>();
    std::vector<RefPtr<PageNodeInfoWrap>> nodeInfoWraps { nodeWrap };
    EXPECT_CALL(*nodeWrap, GetIsFocus()).WillOnce(Return(false));
    EXPECT_CALL(*nodeWrap, GetAutoFillType()).WillRepeatedly(::testing::Return(AceAutoFillType::ACE_UNSPECIFIED));
    webPattern->pageNodeInfo_.push_back(nodeWrap);

    EXPECT_EQ(webPattern->GetFocusedType(), AceAutoFillType::ACE_UNSPECIFIED);
#endif
}

/**
 * @tc.name: RequestAutoFill_001
 * @tc.desc: RequestAutoFill.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternBranchTestUT, RequestAutoFill_001, TestSize.Level1)
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

    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    MockContainer::SetUp();
    pipelineContext->instanceId_ = 1;
    pipelineContext->PipelineBase::GetCurrentContext();
    AceAutoFillType focusType = AceAutoFillType::ACE_UNSPECIFIED;
    webPattern->isPasswordFill_ = true;
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrent();
    bool flag = webPattern->RequestAutoFill(focusType);
    ASSERT_FALSE(flag);
    MockContainer::TearDown();
#endif
}

/**
 * @tc.name: RequestAutoFill_002
 * @tc.desc: RequestAutoFill.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternBranchTestUT, RequestAutoFill_002, TestSize.Level1)
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

    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    pipelineContext->instanceId_ = 1;
    pipelineContext->PipelineBase::GetCurrentContext();
    AceAutoFillType focusType = AceAutoFillType::ACE_UNSPECIFIED;
    webPattern->isPasswordFill_ = false;
    bool flag = webPattern->RequestAutoFill(focusType);
    ASSERT_FALSE(flag);
#endif
}

/**
 * @tc.name: UpdateAutoFillPopup_001
 * @tc.desc: UpdateAutoFillPopup.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternBranchTestUT, UpdateAutoFillPopup_001, TestSize.Level1)
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

    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    pipelineContext->instanceId_ = 1;
    pipelineContext->PipelineBase::GetCurrentContext();
    webPattern->isAutoFillClosing_ = false;
    bool flag = webPattern->UpdateAutoFillPopup();
    ASSERT_FALSE(flag);
#endif
}

/**
 * @tc.name: UpdateAutoFillPopup_002
 * @tc.desc: UpdateAutoFillPopup.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternBranchTestUT, UpdateAutoFillPopup_002, TestSize.Level1)
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

    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    webPattern->isAutoFillClosing_ = true;
    bool flag = webPattern->UpdateAutoFillPopup();
    ASSERT_FALSE(flag);
#endif
}

/**
 * @tc.name: UpdateAutoFillPopup_003
 * @tc.desc: UpdateAutoFillPopup.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternBranchTestUT, UpdateAutoFillPopup_003, TestSize.Level1)
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

    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    pipelineContext->instanceId_ = 1;
    pipelineContext->PipelineBase::GetCurrentContext();
    MockContainer::SetUp();
    webPattern->isAutoFillClosing_ = false;
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrent();
    bool flag = webPattern->UpdateAutoFillPopup();
    MockContainer::TearDown();
    ASSERT_FALSE(flag);
#endif
}

/**
 * @tc.name: RequestAutoSave
 * @tc.desc: RequestAutoSave.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternBranchTestUT, RequestAutoSave, TestSize.Level1)
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

    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    pipelineContext->instanceId_ = 1;
    pipelineContext->PipelineBase::GetCurrentContext();
    bool flag = webPattern->RequestAutoSave();
    ASSERT_FALSE(flag);
#endif
}

/**
 * @tc.name: RequestAutoSave_001
 * @tc.desc: RequestAutoSave.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternBranchTestUT, RequestAutoSave_001, TestSize.Level1)
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
    webPattern->nodeAttach_ = true;
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);

    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    MockContainer::SetUp();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrent();
    pipelineContext->instanceId_ = 1;
    pipelineContext->PipelineBase::GetCurrentContext();
    bool flag = webPattern->RequestAutoSave();
    MockContainer::TearDown();
    ASSERT_FALSE(flag);
#endif
}

/**
 * @tc.name: OnAttachContextDrag
 * @tc.desc: OnAttachContext.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternBranchTestUT, OnAttachContextDrag, TestSize.Level1)
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

    auto dragDropManager_ = AceType::MakeRefPtr<DragDropManager>();
    auto pipelineContext = MockPipelineContext::GetCurrent();
    pipelineContext->SetupRootElement();
    webPattern->OnAttachContext(Referenced::RawPtr(pipelineContext));
    ASSERT_NE(pipelineContext->GetDragDropManager(), nullptr);
#endif
}

/**
 * @tc.name: OnDetachContextDrag
 * @tc.desc: OnDetachContext.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternBranchTestUT, OnDetachContextDrag, TestSize.Level1)
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

    auto dragDropManager_ = AceType::MakeRefPtr<DragDropManager>();
    auto pipelineContext = MockPipelineContext::GetCurrent();
    pipelineContext->SetupRootElement();
    webPattern->tooltipId_ = 1;
    webPattern->OnDetachContext(Referenced::RawPtr(pipelineContext));
    ASSERT_NE(pipelineContext->GetDragDropManager(), nullptr);
#endif
}

/**
 * @tc.name: OnModifyDoneRendermode
 * @tc.desc: OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternBranchTestUT, OnModifyDoneRendermode, TestSize.Level1)
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

    auto pipelineContext = MockPipelineContext::GetCurrent();
    webPattern->renderMode_ = RenderMode::SYNC_RENDER;
    webPattern->layoutMode_ = WebLayoutMode::NONE;
    webPattern->OnNativeEmbedModeEnabledUpdate(true);
    webPattern->webData_ = std::make_optional<std::string>("example.com");
    webPattern->OnModifyDone();
    ASSERT_NE(pipelineContext->GetDragDropManager(), nullptr);
#endif
}

/**
 * @tc.name: ShowMagnifierAndOnColor
 * @tc.desc: ShowMagnifier.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternBranchTestUT, ShowMagnifierAndOnColor, TestSize.Level1)
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

    int centerOffsetX = 20;
    int centerOffsetY = 20;
    webPattern->magnifierController_ = AceType::MakeRefPtr<MagnifierController>(webPattern);
    webPattern->ShowMagnifier(centerOffsetX, centerOffsetY);
    webPattern->OnColorConfigurationUpdate();
    OffsetT offset(20.0f, 20.0f);
    EXPECT_EQ(webPattern->magnifierController_->GetLocalOffset(), offset);
    EXPECT_TRUE(webPattern->magnifierController_->colorModeChange_);
    webPattern->magnifierController_.Reset();
#endif
}
} // namespace OHOS::Ace::NG
