/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"

#define private public
#define protected public
#include "frameworks/core/pipeline/pipeline_base.h"
#include "core/components/web/web_property.h"
#include "core/components_ng/pattern/web/web_data_detector_adapter.h"
#include "core/components_ng/pattern/web/web_pattern.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components/web/resource/web_delegate.h"
#include "test/mock/core/common/mock_container.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#undef protected
#undef private

#include "interfaces/inner_api/ace/ai/data_detector_interface.h"
#include "core/common/ai/data_detector_mgr.h"

#include "core/components_ng/base/view_stack_processor.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace;

namespace OHOS::Ace::NG {
namespace {
RefPtr<WebPattern> g_webPattern = nullptr;
const std::string ALL_TEXT_DETECT_TYPES = "phoneNum,url,email,location,datetime";
}

class WebDataDetectorAdapterTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void WebDataDetectorAdapterTest::SetUpTestCase()
{
#ifdef OHOS_STANDARD_SYSTEM
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;

    std::string src = "web_test";
    RefPtr<WebController> controller = AceType::MakeRefPtr<WebController>();
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::WEB_ETS_TAG, nodeId, [src, controller]() { return AceType::MakeRefPtr<WebPattern>(src, controller); });
    stack->Push(frameNode);

    g_webPattern = frameNode->GetPattern<WebPattern>();
    CHECK_NULL_VOID(g_webPattern);
    g_webPattern->OnModifyDone();
#endif
}

void WebDataDetectorAdapterTest::TearDownTestCase()
{
#ifdef OHOS_STANDARD_SYSTEM
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
    g_webPattern = nullptr;
#endif
}
void WebDataDetectorAdapterTest::SetUp() {}
void WebDataDetectorAdapterTest::TearDown() {}

/**
 * @tc.name: SetDataDetectorConfig_001
 * @tc.desc: Test SetDataDetectorConfig.
 * @tc.type: FUNC
 */
HWTEST_F(WebDataDetectorAdapterTest, SetDataDetectorConfig_001, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto adapter = AceType::MakeRefPtr<WebDataDetectorAdapter>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)), 0);
    adapter->aiSupportStatus_ = AISupportStatus::SUPPORTED;
    EXPECT_EQ(adapter->newConfig_.types, ALL_TEXT_DETECT_TYPES);
    adapter->SetDataDetectorEnable(true);
    EXPECT_EQ(adapter->config_.enable, false);
    EXPECT_EQ(adapter->newConfig_.enable, true);
    TextDetectConfig config;
    config.types = "phoneNum";
    adapter->SetDataDetectorConfig(config);
    EXPECT_EQ(adapter->newConfig_.types, "phoneNum");
    adapter->Init();
    EXPECT_EQ(adapter->config_.enable, true);
    EXPECT_EQ(adapter->config_.types, "phoneNum");
#endif
}

/**
 * @tc.name: DataDetectorInit_001
 * @tc.desc: Test Init.
 * @tc.type: FUNC
 */
HWTEST_F(WebDataDetectorAdapterTest, DataDetectorInit_001, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto adapter = AceType::MakeRefPtr<WebDataDetectorAdapter>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)));
    adapter->Init();
    EXPECT_EQ(adapter->aiSupportStatus_, AISupportStatus::UNSUPPORTED);

    adapter->aiSupportStatus_ = AISupportStatus::SUPPORTED;
    adapter->config_.enable = false;
    adapter->newConfig_.enable = false;
    adapter->hasInit_ = true;
    adapter->Init();
    EXPECT_EQ(adapter->initDataDetectorProxy_, false);
    EXPECT_EQ(adapter->initAIMenu_ , false);

    adapter->config_.enable = false;
    adapter->newConfig_.enable = true;
    adapter->hasInit_ = false;
    adapter->Init();
    EXPECT_EQ(adapter->config_.enable, true);
    EXPECT_EQ(adapter->initDataDetectorProxy_, true);
    EXPECT_EQ(adapter->initAIMenu_ , true);
    EXPECT_EQ(adapter->hasInit_, true);

    adapter->config_.enable = true;
    adapter->newConfig_.enable = false;
    adapter->Init();
    EXPECT_EQ(adapter->config_.enable, false);
    EXPECT_EQ(adapter->initDataDetectorProxy_, false);
    // no need to clear AI menu
    EXPECT_EQ(adapter->initAIMenu_ , true);
#endif
}

/**
 * @tc.name: SetAndRemoveRequestContext_001
 * @tc.desc: Test SetRequestContext and RemoveRequestContext.
 * @tc.type: FUNC
 */
HWTEST_F(WebDataDetectorAdapterTest, SetAndRemoveRequestContext_001, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto adapter = AceType::MakeRefPtr<WebDataDetectorAdapter>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)));
    std::string requestId = "1";
    NodeData data {"1/1", "12345678901"};
    DataDetectorRequestData req {requestId, {data}};
    bool ret = adapter->SetRequestContext(requestId, std::move(req));
    EXPECT_TRUE(ret);
    auto it = adapter->contextMap_.find(requestId);
    auto ptr = it->second;
    EXPECT_EQ(ptr->requestId, requestId);
    EXPECT_EQ(ptr->nodes.size(), 1);
    EXPECT_EQ(ptr->nodes[0].path, "1/1");
    EXPECT_EQ(ptr->nodes[0].text, "12345678901");
    ret = adapter->RemoveRequestContext(requestId);
    EXPECT_TRUE(ret);
    EXPECT_EQ(adapter->contextMap_.empty(), true);
    ret = adapter->RemoveRequestContext(requestId);
    EXPECT_FALSE(ret);
#endif
}

/**
 * @tc.name: ProcessRequest_001
 * @tc.desc: Test ProcessRequest.
 * @tc.type: FUNC
 */
HWTEST_F(WebDataDetectorAdapterTest, ProcessRequest_001, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto adapter = AceType::MakeRefPtr<WebDataDetectorAdapter>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)));
    adapter->config_.enable = false;
    adapter->ProcessRequest(R"({"requestId": "1", "nodes": [{"path": "1", "text": "12345678901"}]})");
    EXPECT_EQ(adapter->contextMap_.empty(), true);

    adapter->config_.enable = true;
    adapter->ProcessRequest("{{}");
    EXPECT_EQ(adapter->contextMap_.empty(), true);

    adapter->ProcessRequest(R"({})");
    EXPECT_EQ(adapter->contextMap_.empty(), true);
    
    adapter->ProcessRequest(R"({"requestId": "1"})");
    EXPECT_EQ(adapter->contextMap_.empty(), true);
    
    adapter->ProcessRequest(R"({"requestId": "1", "nodes": []})");
    EXPECT_EQ(adapter->contextMap_.empty(), true);
    
    adapter->ProcessRequest(R"({"requestId": "1", "nodes": [1]})");
    EXPECT_EQ(adapter->contextMap_.empty(), true);
    
    adapter->ProcessRequest(R"({"requestId": "1", "nodes": [{"path": "1", "text": "12345678901"}]})");
    EXPECT_EQ(adapter->contextMap_.empty(), false);
    auto it = adapter->contextMap_.find("1");
    auto ptr = it->second;
    EXPECT_EQ(ptr->requestId, "1");
    EXPECT_EQ(ptr->nodes.size(), 1);
    EXPECT_EQ(ptr->nodes[0].path, "1");
    EXPECT_EQ(ptr->nodes[0].text, "12345678901");

    adapter->ProcessRequest(R"({"requestId": "1", "nodes": [{"path": "1", "text": "12345678901"}]})");
    EXPECT_EQ(adapter->contextMap_.size(), 1);
#endif
}

/**
 * @tc.name: PrepareDetectText_001
 * @tc.desc: Test PrepareDetectText.
 * @tc.type: FUNC
 */
HWTEST_F(WebDataDetectorAdapterTest, PrepareDetectText_001, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto adapter = AceType::MakeRefPtr<WebDataDetectorAdapter>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)));
    std::string requestId = "1";
    auto detectText = adapter->PrepareDetectText(requestId);
    EXPECT_EQ(detectText, "");
    std::string sep = "\n";
    int sep_len = sep.length();
    NodeData data1 { "1/1", "12345678901" };
    NodeData data2 { "1/2", "12345678902" };
    DataDetectorRequestData req { requestId, { data1, data2 } };
    adapter->SetRequestContext(requestId, std::move(req));

    detectText = adapter->PrepareDetectText(requestId);
    EXPECT_EQ(detectText, "12345678901" + sep + "12345678902" + sep);
    auto requestContext = adapter->GetRequestContext(requestId);
    EXPECT_NE(requestContext, nullptr);

    EXPECT_EQ(requestContext->requestId, requestId);
    EXPECT_EQ(requestContext->nodes.size(), 2);
    EXPECT_EQ(requestContext->nodes[0].text, "12345678901");
    EXPECT_EQ(requestContext->nodes[1].text, "12345678902");

    EXPECT_EQ(requestContext->detectIds, (std::vector<size_t> { 0, 1 }));
    EXPECT_EQ(requestContext->detectOffsets,
        (std::vector<std::pair<size_t, size_t>> { { 0, 11 }, { 11 + sep_len, 22 + sep_len } }));
#endif
}

/**
 * @tc.name: PrepareDetectText_002
 * @tc.desc: Test PrepareDetectText with cache.
 * @tc.type: FUNC
 */
HWTEST_F(WebDataDetectorAdapterTest, PrepareDetectText_002, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto adapter = AceType::MakeRefPtr<WebDataDetectorAdapter>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)));
    DataDetectorResult fake_result { { 0, 1, "fake", "fake" } };
    adapter->resultCache_->Put("12345678901", fake_result);
    std::string requestId = "1";
    std::string sep = "\n";
    NodeData data1 { "1/1", "12345678901" };
    NodeData data2 { "1/2", "12345678902" };
    DataDetectorRequestData req { requestId, { data1, data2 } };
    adapter->SetRequestContext(requestId, std::move(req));

    auto detectText = adapter->PrepareDetectText(requestId);
    EXPECT_EQ(detectText, "12345678902" + sep);
    auto requestContext = adapter->GetRequestContext(requestId);
    EXPECT_NE(requestContext, nullptr);

    EXPECT_EQ(requestContext->detectIds, (std::vector<size_t> { 1 }));
    EXPECT_EQ(requestContext->detectOffsets,
        (std::vector<std::pair<size_t, size_t>> { { 0, 11 } }));
    EntityMatch mat = requestContext->matches[0][0];
    EXPECT_EQ(mat.start, 0);
    EXPECT_EQ(mat.end, 1);
    EXPECT_EQ(mat.entityType, "fake");
    EXPECT_EQ(mat.clean, "fake");
#endif
}

/**
 * @tc.name: SendRequestToAI_001
 * @tc.desc: Test SendRequestToAI.
 * @tc.type: FUNC
 */
HWTEST_F(WebDataDetectorAdapterTest, SendRequestToAI_001, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto adapter = AceType::MakeRefPtr<WebDataDetectorAdapter>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)));
    std::string requestId = "1";
    std::string sep = "\n";
    NodeData data1 { "1/1", "abc@huawei.com" };
    DataDetectorRequestData req { requestId, { data1 } };
    adapter->SetRequestContext(requestId, std::move(req));

    adapter->SendRequestToAI(requestId);
    auto requestContext = adapter->GetRequestContext(requestId);
    EXPECT_NE(requestContext, nullptr);

    EXPECT_EQ(requestContext->requestId, requestId);
    EXPECT_EQ(requestContext->nodes.size(), 1);
    EXPECT_EQ(requestContext->nodes[0].text, "abc@huawei.com");

    EXPECT_EQ(requestContext->detectIds, (std::vector<size_t> { 0 }));
    EXPECT_EQ(requestContext->detectOffsets, (std::vector<std::pair<size_t, size_t>> { { 0, 14 } }));
#endif
}

/**
 * @tc.name: ParseAIResultByType_001
 * @tc.desc: Test ParseAIResultByType.
 * @tc.type: FUNC
 */
HWTEST_F(WebDataDetectorAdapterTest, ParseAIResultByType_001, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto adapter = AceType::MakeRefPtr<WebDataDetectorAdapter>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)));
    std::string requestId = "1";
    std::string sep = "\n";
    int sep_len = sep.length();
    NodeData data1 { "1/1", "mail: abc@huawei.com" };
    NodeData data2 { "1/2", "phone: 12345678901" };
    // mail: abc@huawei.com|phone: 12345678901|
    DataDetectorRequestData req { requestId, { data1, data2 } };
    auto requestContext = adapter->GetRequestContext(requestId);
    EXPECT_EQ(requestContext, nullptr);

    adapter->SetRequestContext(requestId, std::move(req));
    requestContext = adapter->GetRequestContext(requestId);
    EXPECT_NE(requestContext, nullptr);

    auto detectText = adapter->PrepareDetectText(requestId);
    EXPECT_EQ(detectText, "mail: abc@huawei.com" + sep + "phone: 12345678901" + sep);

    EXPECT_EQ(requestContext->matches.size(), 2);
    EXPECT_EQ(requestContext->detectIds, (std::vector<size_t> { 0, 1 }));
    EXPECT_EQ(requestContext->detectOffsets,
        (std::vector<std::pair<size_t, size_t>> { { 0, 20 }, { 20 + sep_len, 38 + sep_len } }));

    std::unique_ptr<JsonValue> jsonValue = JsonUtil::ParseJsonString(
        R"([{"charOffset": 6, "oriText": "abc@huawei.com"}, 666, {"charOffset": 999, "oriText": "ggg"}])");
    EXPECT_TRUE(jsonValue->IsArray());

    adapter->ParseAIResultByType(requestContext, "email", jsonValue);
    EXPECT_EQ(requestContext->matches[0].size(), 1);
    EntityMatch mat = requestContext->matches[0][0];
    EXPECT_EQ(mat.start, 6);
    EXPECT_EQ(mat.end, 20);
    EXPECT_EQ(mat.entityType, "email");
    EXPECT_EQ(mat.clean, "abc@huawei.com");

    requestContext->detectOffsets.emplace_back(std::make_pair<size_t, size_t>(990, 999));
    requestContext->detectIds.emplace_back(2);
    jsonValue = JsonUtil::ParseJsonString(
        R"([{"charOffset": 28, "oriText": "12345678901"}, {"charOffset": 992, "oriText": "ggg"}])");
    EXPECT_TRUE(jsonValue->IsArray());

    adapter->ParseAIResultByType(requestContext, "phoneNum", jsonValue);
    EXPECT_EQ(requestContext->matches[1].size(), 1);
    mat = requestContext->matches[1][0];
    EXPECT_EQ(mat.start, 7);
    EXPECT_EQ(mat.end, 18);
    EXPECT_EQ(mat.entityType, "phoneNum");
    EXPECT_EQ(mat.clean, "12345678901");
    jsonValue = JsonUtil::ParseJsonString(
        R"([{"charOffset": -1, "oriText": "12345678901"}])");
    EXPECT_TRUE(jsonValue->IsArray());
    adapter->ParseAIResultByType(requestContext, "phoneNum", jsonValue);
#endif
}

/**
 * @tc.name: HandleResultFromAI_001
 * @tc.desc: Test HandleResultFromAI.
 * @tc.type: FUNC
 */
HWTEST_F(WebDataDetectorAdapterTest, HandleResultFromAI_001, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto adapter = AceType::MakeRefPtr<WebDataDetectorAdapter>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)));
    std::string requestId = "1";
    std::string sep = "\n";
    int sep_len = sep.length();
    NodeData data1 { "1/1", "mail: abc@huawei.com" };
    NodeData data2 { "1/2", "phone: 12345678901" };
    // mail: abc@huawei.com|phone: 12345678901|
    DataDetectorRequestData req { requestId, { data1, data2 } };
    auto requestContext = adapter->GetRequestContext(requestId);
    EXPECT_EQ(requestContext, nullptr);

    adapter->SetRequestContext(requestId, std::move(req));
    requestContext = adapter->GetRequestContext(requestId);
    EXPECT_NE(requestContext, nullptr);

    auto detectText = adapter->PrepareDetectText(requestId);
    EXPECT_EQ(detectText, "mail: abc@huawei.com" + sep + "phone: 12345678901" + sep);

    EXPECT_EQ(requestContext->matches.size(), 2);
    EXPECT_EQ(requestContext->detectIds, (std::vector<size_t> { 0, 1 }));
    EXPECT_EQ(requestContext->detectOffsets,
        (std::vector<std::pair<size_t, size_t>> { { 0, 20 }, { 20 + sep_len, 38 + sep_len } }));

    TextDataDetectResult result;
    result.entity = R"({"email": [{"charOffset": 6, "oriText": "abc@huawei.com"}],
        "phoneNum": [{"charOffset": 28, "oriText": "12345678901"}]})";

    adapter->HandleResultFromAI(requestId, result);
    EXPECT_NE(adapter->resultCache_, nullptr);
    EXPECT_EQ(adapter->resultCache_->cacheMap_.size(), 2);

    EXPECT_EQ(requestContext->matches[0].size(), 1);
    EntityMatch mat = requestContext->matches[0][0];
    EXPECT_EQ(mat.start, 6);
    EXPECT_EQ(mat.end, 20);
    EXPECT_EQ(mat.entityType, "email");
    EXPECT_EQ(mat.clean, "abc@huawei.com");

    EXPECT_EQ(requestContext->matches[1].size(), 1);
    mat = requestContext->matches[1][0];
    EXPECT_EQ(mat.start, 7);
    EXPECT_EQ(mat.end, 18);
    EXPECT_EQ(mat.entityType, "phoneNum");
    EXPECT_EQ(mat.clean, "12345678901");
#endif
}

/**
 * @tc.name: HandleResultFromAI_002
 * @tc.desc: Test HandleResultFromAI without cache.
 * @tc.type: FUNC
 */
HWTEST_F(WebDataDetectorAdapterTest, HandleResultFromAI_002, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto adapter = AceType::MakeRefPtr<WebDataDetectorAdapter>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)), 0);
    std::string requestId = "1";
    std::string sep = "\n";
    NodeData data1 { "1/1", "mail: abc@huawei.com" };
    NodeData data2 { "1/2", "phone: 12345678901" };
    // mail: abc@huawei.com|phone: 12345678901|
    DataDetectorRequestData req { requestId, { data1, data2 } };
    adapter->SetRequestContext(requestId, std::move(req));
    auto requestContext = adapter->GetRequestContext(requestId);

    auto detectText = adapter->PrepareDetectText(requestId);

    TextDataDetectResult result;
    result.entity = R"({"email": [{"charOffset": 6, "oriText": "abc@huawei.com"}],
        "phoneNum": [{"charOffset": 28, "oriText": "12345678901"}]})";

    adapter->HandleResultFromAI(requestId, result);
    EXPECT_EQ(adapter->resultCache_, nullptr);

    EXPECT_EQ(requestContext->matches[0].size(), 1);
    EntityMatch mat = requestContext->matches[0][0];
    EXPECT_EQ(mat.clean, "abc@huawei.com");

    EXPECT_EQ(requestContext->matches[1].size(), 1);
    mat = requestContext->matches[1][0];
    EXPECT_EQ(mat.clean, "12345678901");
#endif
}

/**
 * @tc.name: HandleResultFromAI_003
 * @tc.desc: Test HandleResultFromAI excepetion.
 * @tc.type: FUNC
 */
HWTEST_F(WebDataDetectorAdapterTest, HandleResultFromAI_003, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto adapter = AceType::MakeRefPtr<WebDataDetectorAdapter>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)), 0);
    std::string requestId = "1";
    std::string sep = "\n";
    NodeData data1 { "1/1", "mail: abc@huawei.com" };
    NodeData data2 { "1/2", "phone: 12345678901" };
    // mail: abc@huawei.com|phone: 12345678901|
    DataDetectorRequestData req { requestId, { data1, data2 } };
    adapter->SetRequestContext(requestId, std::move(req));
    auto requestContext = adapter->GetRequestContext(requestId);

    auto detectText = adapter->PrepareDetectText(requestId);

    TextDataDetectResult result;

    result.entity = R"(666)";
    adapter->HandleResultFromAI(requestId, result);
    auto ptr = adapter->GetRequestContext(requestId);
    EXPECT_EQ(ptr, nullptr);

    requestContext->detectIds.emplace_back(2);
    result.entity = R"({"email": [{"charOffset": 6, "oriText": "abc@huawei.com"}],
        "phoneNum": [{"charOffset": 28, "oriText": "12345678901"}],
        "url": 666})";
    adapter->HandleResultFromAI(requestId, result);
    ptr = adapter->GetRequestContext(requestId);
    EXPECT_EQ(ptr, nullptr);
#endif
}

/**
 * @tc.name: MatchInOffsets_001
 * @tc.desc: Test MatchInOffsets.
 * @tc.type: FUNC
 */
HWTEST_F(WebDataDetectorAdapterTest, MatchInOffsets_001, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto adapter = AceType::MakeRefPtr<WebDataDetectorAdapter>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)), 0);
    EntityMatch mat { 0, 8, "email", "abc@huawei.com" };
    std::vector<std::pair<size_t, size_t>> offsets { { 1, 20 } };
    int32_t pos = adapter->MatchInOffsets(mat, offsets);
    EXPECT_EQ(pos, -1);
    offsets = (std::vector<std::pair<size_t, size_t>> { { 0, 14 } });
    pos = adapter->MatchInOffsets(mat, offsets);
    EXPECT_EQ(pos, 0);
    mat = EntityMatch { 9, 15, "phoneNum", "12345678901" };
    offsets = (std::vector<std::pair<size_t, size_t>> { { 1, 12 } });
    pos = adapter->MatchInOffsets(mat, offsets);
    EXPECT_EQ(pos, -1);
#endif
}

/**
 * @tc.name: SendResultToJS_001
 * @tc.desc: Test SendResultToJS.
 * @tc.type: FUNC
 */
HWTEST_F(WebDataDetectorAdapterTest, SendResultToJS_001, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto adapter = AceType::MakeRefPtr<WebDataDetectorAdapter>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)), 0);
    adapter->SendResultToJS("");
    EXPECT_FALSE(adapter->hasInit_);
#endif
}

/**
 * @tc.name: ProcessClick_001
 * @tc.desc: Test ProcessClick.
 * @tc.type: FUNC
 */
HWTEST_F(WebDataDetectorAdapterTest, ProcessClick_001, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto adapter = AceType::MakeRefPtr<WebDataDetectorAdapter>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)), 0);
    adapter->config_.enable = false;
    adapter->ProcessClick("");
    EXPECT_FALSE(adapter->hasInit_);
    adapter->config_.enable = true;
    adapter->ProcessClick("");
    adapter->ProcessClick("{}");
    adapter->ProcessClick(R"({"rect": 666})");
    adapter->ProcessClick(R"({"rect": {}})");
    adapter->ProcessClick(R"({"rect": {}, "touchTest": true})");
    EXPECT_FALSE(adapter->hasInit_);
#endif
}

/**
 * @tc.name: AIMenu_001
 * @tc.desc: Test AIMenu.
 * @tc.type: FUNC
 */
HWTEST_F(WebDataDetectorAdapterTest, AIMenu_001, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto adapter = AceType::MakeRefPtr<WebDataDetectorAdapter>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)), 0);
    AIMenuInfo info { "phoneNum", "12345678901", R"(<a href="tel:12345678901">12345678901</a>)", RectF(0, 0, 10, 10) };
    bool ret = adapter->ShowAIMenu(info);
    EXPECT_FALSE(ret);
    FuncVariant funcCopy = []() -> std::string { return "copy"; };
    FuncVariant funcSelectText = []() -> std::string { return "selectText"; };
    FuncVariant funcPhoneEmailURL = [](sptr<IRemoteObject> obj, std::string content) {};
    FuncVariant funcLocation = [](int32_t id, std::string content) {};
    FuncVariant funcDateTime = [](int32_t a, std::string b, std::string c, int32_t d, std::string e) {};

    adapter->textDetectResult_.menuOptionAndAction["email"] = { { "make email", funcPhoneEmailURL },
        { "copy", funcCopy }, { "selectText", funcSelectText } };
    ret = adapter->ShowAIMenu(info);
    EXPECT_FALSE(ret);
    adapter->textDetectResult_.menuOptionAndAction["phoneNum"] = { { "make phone", funcPhoneEmailURL },
        { "copy", funcCopy }, { "selectText", funcSelectText } };
    ret = adapter->ShowAIMenu(info);
    EXPECT_FALSE(ret); // overlay_manager always false
    adapter->CloseOtherMenu();
    adapter->OnClickAIMenuOption(info, { "", funcCopy});
    adapter->OnClickAIMenuOption(info, { "", funcSelectText});
    adapter->OnClickAIMenuOption(info, { "", funcPhoneEmailURL});
    adapter->OnClickAIMenuOption(info, { "", funcLocation});
    adapter->OnClickAIMenuOption(info, { "", funcDateTime});

    adapter->OnClickMenuItem("copy", info);
    adapter->OnClickMenuItem("selectText", info);

    EXPECT_FALSE(ret);
#endif
}

/**
 * @tc.name: OnClickAISelectMenuOption_001
 * @tc.desc: Test OnClickAISelectMenuOption.
 * @tc.type: FUNC
 */
HWTEST_F(WebDataDetectorAdapterTest, OnClickAISelectMenuOption_001, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto adapter = AceType::MakeRefPtr<WebDataDetectorAdapter>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)));
    adapter->OnClickAISelectMenuOption(TextDataDetectType::EMAIL, "example@huawei.com");
    adapter->config_.enable = true;
    adapter->OnClickAISelectMenuOption(TextDataDetectType::EMAIL, "example@huawei.com");

    FuncVariant funcCopy = []() -> std::string { return "copy"; };
    FuncVariant funcSelectText = []() -> std::string { return "selectText"; };
    FuncVariant funcPhoneEmailURL = [](sptr<IRemoteObject> obj, std::string content) {};

    adapter->textDetectResult_.menuOptionAndAction["email"] = { { "make email", funcPhoneEmailURL },
        { "copy", funcCopy }, { "selectText", funcSelectText } };
    adapter->OnClickAISelectMenuOption(TextDataDetectType::EMAIL, "example@huawei.com");
    EXPECT_FALSE(adapter->hasInit_);
#endif
}

/**
 * @tc.name: DetectSelectedText_001
 * @tc.desc: Test DetectSelectedText.
 * @tc.type: FUNC
 */
HWTEST_F(WebDataDetectorAdapterTest, DetectSelectedText_001, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto adapter = AceType::MakeRefPtr<WebDataDetectorAdapter>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)));
    adapter->DetectSelectedText("email: example@huawei.com");
    adapter->config_.enable = true;
    adapter->DetectSelectedText("email: example@huawei.com");
    DataDetectorResult fake_result { { 0, 1, "email", "fake" } };
    adapter->resultCache_->Put("email: example@huawei.com", fake_result);
    adapter->DetectSelectedText("email: example@huawei.com");

    fake_result = DataDetectorResult { { 0, 1, "fake", "fake" }, { 0, 2, "fake", "fake" } };
    adapter->resultCache_->Put("email: example@huawei.com", fake_result);
    adapter->DetectSelectedText("email: example@huawei.com");

    fake_result = DataDetectorResult { { 0, 1, "fake", "fake" } };
    adapter->resultCache_->Put("email: example@huawei.com", fake_result);
    adapter->DetectSelectedText("email: example@huawei.com");
    EXPECT_FALSE(adapter->hasInit_);
#endif
}

/**
 * @tc.name: OnDetectSelectedTextDone_001
 * @tc.desc: Test OnDetectSelectedTextDone.
 * @tc.type: FUNC
 */
HWTEST_F(WebDataDetectorAdapterTest, OnDetectSelectedTextDone_001, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto adapter = AceType::MakeRefPtr<WebDataDetectorAdapter>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)), 0);
    TextDataDetectResult result;

    result.entity = R"(666)";
    adapter->OnDetectSelectedTextDone(result);

    result.entity = R"({"email": [{"charOffset": 6, "oriText": "abc@huawei.com"}], "url": 666})";
    adapter->OnDetectSelectedTextDone(result);

    result.entity = R"({"phoneNum": [{"charOffset": -1, "oriText": "12345678901"}]})";
    adapter->OnDetectSelectedTextDone(result);
    // test UpdateAISelectMenu
    adapter->UpdateAISelectMenu("fake", "fake");
    adapter->UpdateAISelectMenu("phoneNum", "12345678901");
    EXPECT_FALSE(adapter->hasInit_);
#endif
}

/**
 * @tc.name: GetPreviewMenuNode_001
 * @tc.desc: Test GetPreviewMenuNode.
 * @tc.type: FUNC
 */
HWTEST_F(WebDataDetectorAdapterTest, GetPreviewMenuNode_001, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto adapter = AceType::MakeRefPtr<WebDataDetectorAdapter>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)), 0);
    AIMenuInfo info { "phoneNum", "12345678901", R"(<a href="tel:12345678901">12345678901</a>)", RectF(0, 0, 10, 10) };

    auto node = adapter->GetPreviewMenuNode(info);
    EXPECT_EQ(node, nullptr);

    FuncVariant funcCopy = []() -> std::string { return "copy"; };
    FuncVariant funcSelectText = []() -> std::string { return "selectText"; };
    FuncVariant funcPhoneEmailURL = [](sptr<IRemoteObject> obj, std::string content) {};
    FuncVariant funcLocation = [](int32_t id, std::string content) {};
    FuncVariant funcDateTime = [](int32_t a, std::string b, std::string c, int32_t d, std::string e) {};

    adapter->textDetectResult_.menuOptionAndAction["phoneNum"] = { { "make phone", funcPhoneEmailURL },
        { "copy", funcCopy }, { "selectText", funcSelectText } };
    adapter->textDetectResult_.menuOptionAndAction["location"] = { { "make location", funcLocation },
        { "copy", funcCopy }, { "selectText", funcSelectText } };

    node = adapter->GetPreviewMenuNode(info);
    EXPECT_NE(node, nullptr);

    AIMenuInfo info2 { "location", "here", R"(<a href="geo:here">here</a>)", RectF(0, 0, 10, 10) };
    node = adapter->GetPreviewMenuNode(info2);
    EXPECT_NE(node, nullptr);
    
    // add mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<TextOverlayTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));

    node = adapter->GetPreviewMenuNode(info);
    EXPECT_NE(node, nullptr);

    node = adapter->GetPreviewMenuNode(info2);
    EXPECT_NE(node, nullptr);
#endif
}

/**
 * @tc.name: GetPreviewMenuBuilder_001
 * @tc.desc: Test GetPreviewMenuBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(WebDataDetectorAdapterTest, GetPreviewMenuBuilder_001, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto adapter = AceType::MakeRefPtr<WebDataDetectorAdapter>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)), 0);

    FuncVariant funcCopy = []() -> std::string { return "copy"; };
    FuncVariant funcSelectText = []() -> std::string { return "selectText"; };
    FuncVariant funcPhoneEmailURL = [](sptr<IRemoteObject> obj, std::string content) {};
    FuncVariant funcLocation = [](int32_t id, std::string content) {};
    FuncVariant funcDateTime = [](int32_t a, std::string b, std::string c, int32_t d, std::string e) {};

    adapter->textDetectResult_.menuOptionAndAction["phoneNum"] = { { "make phone", funcPhoneEmailURL },
        { "copy", funcCopy }, { "selectText", funcSelectText } };
    adapter->textDetectResult_.menuOptionAndAction["location"] = { { "make location", funcLocation },
        { "copy", funcCopy }, { "selectText", funcSelectText } };
    adapter->textDetectResult_.menuOptionAndAction["url"] = { { "load url", funcPhoneEmailURL },
        { "copy", funcCopy }, { "selectText", funcSelectText } };

    std::function<void()> func1, func2;

    // also test SetPreviewMenuLink
    EXPECT_FALSE(adapter->SetPreviewMenuLink("tel:12345678901"));
    EXPECT_EQ(adapter->previewMenuType_, TextDataDetectType::INVALID);
    EXPECT_EQ(adapter->previewMenuContent_, "");

    EXPECT_FALSE(adapter->GetPreviewMenuBuilder(func1, func2));
    adapter->config_.enable = true;

    EXPECT_FALSE(adapter->GetPreviewMenuBuilder(func1, func2));

    EXPECT_TRUE(adapter->SetPreviewMenuLink("www.example.com"));
    EXPECT_EQ(adapter->previewMenuType_, TextDataDetectType::URL);
    EXPECT_EQ(adapter->previewMenuContent_, "www.example.com");

    adapter->SetPreviewMenuAttr();
    EXPECT_TRUE(adapter->SetPreviewMenuLink("tel:12345678901"));
    EXPECT_EQ(adapter->previewMenuType_, TextDataDetectType::PHONE_NUMBER);
    EXPECT_EQ(adapter->previewMenuContent_, "12345678901");

    EXPECT_TRUE(adapter->SetPreviewMenuLink("tel:12345678902"));
    EXPECT_EQ(adapter->previewMenuContent_, "12345678901");

    EXPECT_TRUE(adapter->SetPreviewMenuLink("www.example.com"));
    EXPECT_EQ(adapter->previewMenuType_, TextDataDetectType::URL);
    EXPECT_EQ(adapter->previewMenuContent_, "www.example.com");

    EXPECT_TRUE(adapter->GetPreviewMenuBuilder(func1, func2));
    EXPECT_EQ(adapter->previewMenuType_, TextDataDetectType::INVALID);
    EXPECT_EQ(adapter->previewMenuContent_, "");
#endif
}

/**
 * @tc.name: UrlDecode_001
 * @tc.desc: Test UrlDecode function with various scenarios
 * @tc.type: FUNC
 */
HWTEST_F(WebDataDetectorAdapterTest, UrlDecode_001, TestSize.Level0)
{
    // Case 1: Empty string test
    EXPECT_EQ(WebDataDetectorAdapter::UrlDecode(""), "");

    // Case 2: Normal characters pass through
    EXPECT_EQ(WebDataDetectorAdapter::UrlDecode("hello world"), "hello world");

    // Case 3: '+' decoded to space
    EXPECT_EQ(WebDataDetectorAdapter::UrlDecode("hello+world"), "hello world");

    // Case 4: Valid percent encoding
    EXPECT_EQ(WebDataDetectorAdapter::UrlDecode("%21%3F%23"), "!?#");  // !?# URL code

    // Case 5: Invalid percent encoding (single digit)
    EXPECT_EQ(WebDataDetectorAdapter::UrlDecode("%2"), "%2");

    // Case 6: Invalid percent encoding (non-hex characters)
    EXPECT_EQ(WebDataDetectorAdapter::UrlDecode("%XX"), "%XX");
    EXPECT_EQ(WebDataDetectorAdapter::UrlDecode("%2G"), "%2G");

    // Case 7: Percent sign at string end (incomplete encoding)
    EXPECT_EQ(WebDataDetectorAdapter::UrlDecode("abc%"), "abc%");
    EXPECT_EQ(WebDataDetectorAdapter::UrlDecode("%"), "%");

    // Case 8: Mixed cases
    EXPECT_EQ(WebDataDetectorAdapter::UrlDecode("a%20b%2Fc+d"), "a b/c d");
    
    // Case 9: Uppercase hex encoding
    EXPECT_EQ(WebDataDetectorAdapter::UrlDecode("%41%42%43"), "ABC");  // URL encoding of ABC

    // Case 10: Long string mixed test
    std::string longInput = "%E4%BD%A0%E5%A5%BD+%E4%B8%96%E7%95%8C";  // URL encoding of "你好 世界"
    EXPECT_EQ(WebDataDetectorAdapter::UrlDecode(longInput), "你好 世界");
}

/**
 * @tc.name: ExtraParamsTest_001
 * @tc.desc: Test extra params.
 * @tc.type: FUNC
 */
HWTEST_F(WebDataDetectorAdapterTest, ExtraParamsTest_001, TestSize.Level0)
{
    auto adapter = AceType::MakeRefPtr<WebDataDetectorAdapter>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)), 0);
    std::map<std::string, std::string> res;
    res = adapter->AttrsToParams(nullptr);
    EXPECT_TRUE(res.empty());
    res = adapter->AttrsToParams(JsonUtil::ParseJsonString("test"));
    EXPECT_TRUE(res.empty());
    res = adapter->AttrsToParams(JsonUtil::ParseJsonString("{}"));
    EXPECT_TRUE(res.empty());

    res = adapter->AttrsToParams(JsonUtil::ParseJsonString(R"({"test": "test"})"));
    EXPECT_TRUE(res.empty());

    adapter->extraParamKeys_ = {"test"};
    res = adapter->AttrsToParams(JsonUtil::ParseJsonString(R"({"example": "test"})"));
    EXPECT_TRUE(res.empty());
    res = adapter->AttrsToParams(JsonUtil::ParseJsonString(R"({"test": "test"})"));
    EXPECT_FALSE(res.empty());
}

/**
 * @tc.name: ExtraParamsTest_002
 * @tc.desc: Test extra params.
 * @tc.type: FUNC
 */
HWTEST_F(WebDataDetectorAdapterTest, ExtraParamsTest_002, TestSize.Level0)
{
    std::map<std::string, std::string> res;
    res = WebDataDetectorAdapter::ParseExtraParams("datetime", nullptr);
    EXPECT_TRUE(res.empty());
    res = WebDataDetectorAdapter::ParseExtraParams("datetime", JsonUtil::ParseJsonString(R"([])"));
    EXPECT_TRUE(res.empty());
    res = WebDataDetectorAdapter::ParseExtraParams("invalid", JsonUtil::ParseJsonString(R"({})"));
    EXPECT_TRUE(res.empty());

    // for others
    res = WebDataDetectorAdapter::ParseExtraParams("phoneNum", JsonUtil::ParseJsonString(R"({})"));
    EXPECT_TRUE(res.empty());

    // for datetime
    res = WebDataDetectorAdapter::ParseExtraParams("datetime", JsonUtil::ParseJsonString(R"({})"));
    EXPECT_TRUE(res.empty());
    res = WebDataDetectorAdapter::ParseExtraParams(
        "datetime", JsonUtil::ParseJsonString(R"({"startTimestamp": 123456})"));
    EXPECT_FALSE(res.empty());
}

/**
 * @tc.name: WebDataDetectorCacheTest001
 * @tc.desc: Test WebDataDetectorCache with different scenarios.
 * @tc.type: FUNC
 */
HWTEST_F(WebDataDetectorAdapterTest, WebDataDetectorCacheTest001, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    const size_t cacheSize = 2;
    auto cache = AceType::MakeRefPtr<WebDataDetectorCache<std::string, DataDetectorResult>>(cacheSize);
    
    DataDetectorResult result1;
    DataDetectorResult result2;
    DataDetectorResult result3;
    DataDetectorResult outResult;
    
    bool found = cache->Get("key1", outResult);
    EXPECT_FALSE(found);
    
    cache->Put("key1", result1);
    found = cache->Get("key1", outResult);
    EXPECT_TRUE(found);
    
    cache->Put("key1", result2);
    found = cache->Get("key1", outResult);
    EXPECT_TRUE(found);
    
    cache->Put("key2", result2);
    cache->Put("key3", result3);

    found = cache->Get("key1", outResult);
    EXPECT_FALSE(found);

    found = cache->Get("key2", outResult);
    EXPECT_TRUE(found);
    found = cache->Get("key3", outResult);
    EXPECT_TRUE(found);
    
    // [key3, key2]
    cache->Get("key2", outResult);
    
    DataDetectorResult result4;
    cache->Put("key4", result4);
    found = cache->Get("key3", outResult);
    EXPECT_FALSE(found);
    found = cache->Get("key2", outResult);
    EXPECT_TRUE(found);
    found = cache->Get("key4", outResult);
    EXPECT_TRUE(found);
#endif
}

} // namespace OHOS::Ace::NG