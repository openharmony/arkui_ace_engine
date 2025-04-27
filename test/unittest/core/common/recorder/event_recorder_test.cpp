/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#define protected public
#include "interfaces/inner_api/ace/ui_event_observer.h"

#include "base/log/log.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/common/recorder/event_config.h"
#include "core/common/recorder/event_controller.h"
#include "core/common/recorder/event_definition.h"
#include "core/common/recorder/event_recorder.h"
#include "core/common/recorder/exposure_processor.h"
#include "core/common/recorder/inspector_tree_collector.h"
#include "core/common/recorder/node_data_cache.h"
#include "core/components_ng/pattern/stage/page_info.h"
#include "core/components_ng/pattern/stage/page_pattern.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Recorder;

namespace OHOS::Ace {
class DemoUIEventObserver : public UIEventObserver {
public:
    DemoUIEventObserver() = default;
    ~DemoUIEventObserver() override = default;

    int32_t GetEventType() const
    {
        return eventType_;
    }

    virtual void NotifyUIEvent(int32_t eventType, const std::unordered_map<std::string, std::string>& eventParams)
    {
        LOGI("NotifyUIEvent eventType %{public}d", eventType);
        eventType_ = eventType;
    }

private:
    int32_t eventType_;
};

class EventRecorderTest : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
    void SetUp() {}
    void TearDown() {}
};

void GetConfig(std::string& config)
{
    config =
        "{\"enable\":true,\"switch\":{\"page\":true,\"component\":true,\"exposure\":true},\"config\":[{\"pageUrl\":"
        "\"pages/"
        "Index\",\"shareNode\":[\"hahaha\",\"btn_TitleExpand\",\"btn_OpenSelf\",\"btn_Screenshot\",\"btn_inspect\","
        "\"btn_xxx\",\"\"],\"exposureCfg\":[{\"id\":\"btn_Grid\",\"ratio\":0.75,\"duration\":5000},{\"id\":\"btn_"
        "TitleExpand\",\"ratio\":0.9,\"duration\":1000}]},{\"pageUrl\":\"pages/"
        "ScrollPage\",\"shareNode\":[\"scroll_item_1\"],\"exposureCfg\":[{\"id\":\"scroll_item_2\",\"ratio\":0.85,"
        "\"duration\":5000},{\"id\":\"scroll_item_12\",\"ratio\":0.4,\"duration\":3000}]}]}";
}

void GetConfigDisable(std::string& config)
{
    config =
        "{\"enable\":false,\"switch\":{\"page\":true,\"component\":true,\"exposure\":true},\"config\":[{\"pageUrl\":"
        "\"pages/"
        "Index\",\"shareNode\":[\"hahaha\",\"btn_TitleExpand\",\"btn_OpenSelf\",\"btn_Screenshot\",\"btn_inspect\","
        "\"btn_xxx\",\"\"],\"exposureCfg\":[{\"id\":\"btn_Grid\",\"ratio\":0.75,\"duration\":5000},{\"id\":\"btn_"
        "TitleExpand\",\"ratio\":0.9,\"duration\":1000}]},{\"pageUrl\":\"pages/"
        "ScrollPage\",\"shareNode\":[\"scroll_item_1\"],\"exposureCfg\":[{\"id\":\"scroll_item_2\",\"ratio\":0.85,"
        "\"duration\":5000},{\"id\":\"scroll_item_12\",\"ratio\":0.4,\"duration\":3000}]}]}";
}

void GetConfigTest(std::string& config)
{
    config =
        "{\"enable\":false,\"switch\":{\"page\":true,\"component\":true,\"exposure\":true},\"x\":[{\"pageUrl\":"
        "\"pages/"
        "Index\",\"shareNode\":[\"hahaha\",\"btn_TitleExpand\",\"btn_OpenSelf\",\"btn_Screenshot\",\"btn_inspect\","
        "\"btn_xxx\",\"\"],\"exposureCfg\":[{\"id\":\"btn_Grid\",\"ratio\":0.75,\"duration\":5000},{\"id\":\"btn_"
        "TitleExpand\",\"ratio\":0.9,\"duration\":1000}]},{\"pageUrl\":\"pages/"
        "ScrollPage\",\"shareNode\":[\"scroll_item_1\"],\"exposureCfg\":[{\"id\":\"scroll_item_2\",\"ratio\":0.85,"
        "\"duration\":5000},{\"id\":\"scroll_item_12\",\"ratio\":0.4,\"duration\":3000}]}]}";
}

void GetConfigTest2(std::string& config)
{
    config = "{\"enable\":true,\"switch\":{\"page\":true,\"component\":true,\"exposure\":true},\"config\":[{"
             "\"shareNode\":[\"hahaha\",\"btn_TitleExpand\",\"btn_OpenSelf\",\"btn_Screenshot\",\"btn_inspect\","
             "\"btn_xxx\",\"\"],\"exposureCfg\":[{\"id\":\"btn_Grid\",\"ratio\":0.75,\"duration\":5000},{\"id\":\"btn_"
             "TitleExpand\",\"ratio\":0.9,\"duration\":1000}]},{\"shareNode\":[\"scroll_item_1\"],\"exposureCfg\":[{"
             "\"id\":\"scroll_item_2\",\"ratio\":0.85,"
             "\"duration\":5000},{\"id\":\"scroll_item_12\",\"ratio\":0.4,\"duration\":3000}]}]}";
}

void GetConfigTest3(std::string& config)
{
    config =
        "{\"enable\":true,\"switch\":{\"page\":true,\"component\":true,\"exposure\":true},\"config\":[{\"pageUrl\":"
        "\"pages/"
        "Index\"},{\"pageUrl\":\"pages/"
        "ScrollPage\"}]}";
}

void GetConfigTest4(std::string& config)
{
    config =
        "{\"enable\":true,\"globalSwitch\":{\"page\":true,\"component\":true,\"exposure\":true},\"config\":[{"
        "\"pageUrl\":"
        "\"pages/"
        "Index\",\"shareNode\":[\"hahaha\",\"btn_TitleExpand\",\"btn_OpenSelf\",\"btn_Screenshot\",\"btn_inspect\","
        "\"btn_xxx\",\"\"],\"exposureCfg\":[{\"id\":\"btn_Grid\",\"ratio\":0.75,\"duration\":5000},{\"id\":\"btn_"
        "TitleExpand\",\"ratio\":0.9,\"duration\":1000}]},{\"pageUrl\":\"pages/"
        "ScrollPage\",\"shareNode\":[\"scroll_item_1\"],\"exposureCfg\":[{\"id\":\"scroll_item_2\",\"ratio\":0.85,"
        "\"duration\":5000},{\"id\":\"scroll_item_12\",\"ratio\":0.4,\"duration\":3000}]}]}";
}

void GetConfigTest5(std::string& config)
{
    config = "{\"enable\":true,\"switch\":{\"page\":true,\"component\":true,\"exposure\":true,\"pageParam\":true,"
             "\"scroll\":true,\"animation\":true,\"rect\":true,\"web\":true,\"textInput\":true,\"clickGesture\":true},"
             "\"webCategory\":\"test\",\"webIdentifier\":\"abc\",\"webActionJs\":\"hello\"}";
}

RefPtr<NG::FrameNode> CreatePageNode(const std::string pageUrl)
{
    auto pageNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    return NG::FrameNode::GetOrCreateFrameNode("page", pageNodeId, [pageUrl]() {
        return AceType::MakeRefPtr<NG::PagePattern>(AceType::MakeRefPtr<NG::PageInfo>(1, pageUrl, pageUrl + ".js"));
    });
}

/**
 * @tc.name: EventRecorderTest001
 * @tc.desc: Test register.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, EventRecorderTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call the Register first.
     * @tc.expected: step1. register success.
     */
    std::string config;
    GetConfig(config);
    auto observer = std::make_shared<DemoUIEventObserver>();
    Recorder::EventController::Get().Register(config, observer);

    Recorder::NodeDataCache::Get().OnPageShow("pages/Index");

    Recorder::ExposureCfg exposureCfg = { "", 0.0, 0 };
    Recorder::NodeDataCache::Get().GetExposureCfg("pages/Index", "btn_Grid", exposureCfg);
    EXPECT_EQ(exposureCfg.id, "btn_Grid");
    EXPECT_EQ(exposureCfg.duration, 5000);

    exposureCfg = { "", 0.0, 0 };
    Recorder::NodeDataCache::Get().GetExposureCfg("pages/Index", "", exposureCfg);
    EXPECT_EQ(exposureCfg.id, "");

    exposureCfg = { "", 0.0, 0 };
    Recorder::NodeDataCache::Get().GetExposureCfg("pages/Index", "xyz", exposureCfg);
    EXPECT_EQ(exposureCfg.id, "");

    Recorder::NodeDataCache::Get().OnPageShow("pages/ScrollPage");
    exposureCfg = { "", 0.0, 0 };
    Recorder::NodeDataCache::Get().GetExposureCfg("pages/ScrollPage", "btn_Grid", exposureCfg);
    EXPECT_EQ(exposureCfg.id, "");

    exposureCfg = { "", 0.0, 0 };
    Recorder::NodeDataCache::Get().GetExposureCfg("pages/ScrollPage", "scroll_item_2", exposureCfg);
    EXPECT_EQ(exposureCfg.id, "scroll_item_2");
    EXPECT_NEAR(exposureCfg.ratio, 0.85, 0.00001f);

    /**
     * @tc.steps: step2. call the Unregister first.
     * @tc.expected: step2. unregister success.
     */
    Recorder::EventController::Get().Unregister(observer);
    exposureCfg = { "", 0.0, 0 };
    Recorder::NodeDataCache::Get().GetExposureCfg("pages/ScrollPage", "scroll_item_2", exposureCfg);
    EXPECT_EQ(exposureCfg.id, "");
}

/**
 * @tc.name: EventRecorderTest002
 * @tc.desc: Test node data cache.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, EventRecorderTest002, TestSize.Level1)
{
    std::string config;
    GetConfig(config);
    auto observer = std::make_shared<DemoUIEventObserver>();
    Recorder::EventController::Get().Register(config, observer);

    /**
     * @tc.steps: step1. test index page.
     * @tc.expected: step1. get value success.
     */
    Recorder::NodeDataCache::Get().OnPageShow("pages/Index");
    auto pageNode = CreatePageNode("pages/Index");

    Recorder::NodeDataCache::Get().PutString(pageNode, "btn_TitleExpand", "abc");
    Recorder::NodeDataCache::Get().PutInt(pageNode, "btn_OpenSelf", 2);
    Recorder::NodeDataCache::Get().PutBool(pageNode, "btn_Screenshot", true);
    Recorder::NodeDataCache::Get().PutMultiple(pageNode, "btn_inspect", "inspect", 11);
    Recorder::NodeDataCache::Get().PutMultiple(pageNode, "btn_xxx", "xxx", true);
    std::vector<std::string> values = { "a", "b", "c" };
    Recorder::NodeDataCache::Get().PutMultiple(pageNode, "hahaha", "xixi", values);
    auto nodeValues = std::unordered_map<std::string, std::string>();
    nodeValues.emplace("btn_TitleExpand", "");
    nodeValues.emplace("btn_OpenSelf", "");
    nodeValues.emplace("btn_Screenshot", "");
    nodeValues.emplace("btn_inspect", "");
    nodeValues.emplace("btn_xxx", "");
    nodeValues.emplace("hahaha", "");
    nodeValues.emplace("hello", "");
    nodeValues.emplace("world", "xyz");
    Recorder::NodeDataCache::Get().GetNodeData("pages/Index", nodeValues);

    auto iter = nodeValues.find("btn_TitleExpand");
    EXPECT_EQ(iter->second, "abc");

    iter = nodeValues.find("btn_OpenSelf");
    EXPECT_EQ(iter->second, "2");

    iter = nodeValues.find("btn_Screenshot");
    EXPECT_EQ(iter->second, "true");

    iter = nodeValues.find("btn_inspect");
    EXPECT_EQ(iter->second, "{\"text\":\"inspect\",\"index\":11}");

    iter = nodeValues.find("btn_xxx");
    EXPECT_EQ(iter->second, "{\"text\":\"xxx\",\"checked\":true}");

    iter = nodeValues.find("hahaha");
    EXPECT_EQ(iter->second, "{\"text\":\"xixi\",\"textArray\":[\"a\",\"b\",\"c\"]}");

    iter = nodeValues.find("hello");
    EXPECT_EQ(iter->second, "");

    iter = nodeValues.find("world");
    EXPECT_EQ(iter->second, "xyz");

    Recorder::EventController::Get().Unregister(observer);
}

/**
 * @tc.name: EventRecorderTest003
 * @tc.desc: Test node data cache.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, EventRecorderTest003, TestSize.Level1)
{
    std::string config;
    GetConfig(config);
    auto observer = std::make_shared<DemoUIEventObserver>();
    Recorder::EventController::Get().Register(config, observer);

    Recorder::NodeDataCache::Get().OnPageShow("pages/Index");
    auto pageNode = CreatePageNode("pages/Index");

    Recorder::NodeDataCache::Get().PutString(pageNode, "btn_TitleExpand", "abc");
    Recorder::NodeDataCache::Get().PutInt(pageNode, "btn_OpenSelf", 2);
    Recorder::NodeDataCache::Get().PutBool(pageNode, "btn_Screenshot", true);
    Recorder::NodeDataCache::Get().PutMultiple(pageNode, "btn_inspect", "inspect", 11);
    Recorder::NodeDataCache::Get().PutMultiple(pageNode, "btn_xxx", "xxx", true);
    std::vector<std::string> values = { "a", "b", "c" };
    Recorder::NodeDataCache::Get().PutMultiple(pageNode, "hahaha", "xixi", values);

    /**
     * @tc.steps: step1. test scroll page.
     * @tc.expected: step1. get value success.
     */
    Recorder::NodeDataCache::Get().OnPageShow("pages/ScrollPage");
    auto pageNode2 = CreatePageNode("pages/ScrollPage");

    std::vector<std::string> values2 = { "x", "y", "z" };
    Recorder::NodeDataCache::Get().PutStringArray(pageNode2, "scroll_item_1", values2);
    auto nodeValues2 = std::unordered_map<std::string, std::string>();
    nodeValues2.emplace("btn_TitleExpand", "");
    nodeValues2.emplace("scroll_item_1", "");
    Recorder::NodeDataCache::Get().GetNodeData("pages/ScrollPage", nodeValues2);

    auto iter2 = nodeValues2.find("btn_TitleExpand");
    EXPECT_NE(iter2->second, "abc");

    iter2 = nodeValues2.find("scroll_item_1");
    EXPECT_EQ(iter2->second, "[\"x\",\"y\",\"z\"]");

    Recorder::EventController::Get().Unregister(observer);
}

/**
 * @tc.name: EventRecorderTest004
 * @tc.desc: Test node data cache.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, EventRecorderTest004, TestSize.Level1)
{
    std::string config;
    GetConfig(config);
    auto observer = std::make_shared<DemoUIEventObserver>();
    Recorder::EventController::Get().Register(config, observer);

    Recorder::NodeDataCache::Get().OnPageShow("pages/Index");
    auto pageNode = CreatePageNode("pages/Index");

    Recorder::NodeDataCache::Get().PutString(pageNode, "btn_TitleExpand", "abc");
    Recorder::NodeDataCache::Get().PutInt(pageNode, "btn_OpenSelf", 2);
    Recorder::NodeDataCache::Get().PutBool(pageNode, "btn_Screenshot", true);
    Recorder::NodeDataCache::Get().PutMultiple(pageNode, "btn_inspect", "inspect", 11);
    Recorder::NodeDataCache::Get().PutMultiple(pageNode, "btn_xxx", "xxx", true);
    std::vector<std::string> values = { "a", "b", "c" };
    Recorder::NodeDataCache::Get().PutMultiple(pageNode, "hahaha", "xixi", values);

    Recorder::NodeDataCache::Get().OnPageShow("pages/ScrollPage");
    auto pageNode2 = CreatePageNode("pages/ScrollPage");

    std::vector<std::string> values2 = { "x", "y", "z" };
    Recorder::NodeDataCache::Get().PutStringArray(pageNode2, "scroll_item_1", values2);

    /**
     * @tc.steps: step1. test pop scroll page.
     * @tc.expected: step1. get value success.
     */
    Recorder::NodeDataCache::Get().OnBeforePagePop();

    auto nodeValues3 = std::unordered_map<std::string, std::string>();
    nodeValues3.emplace("btn_TitleExpand", "");
    nodeValues3.emplace("scroll_item_1", "");
    Recorder::NodeDataCache::Get().GetNodeData("pages/ScrollPage", nodeValues3);

    auto iter3 = nodeValues3.find("scroll_item_1");
    EXPECT_EQ(iter3->second, "");

    iter3 = nodeValues3.find("btn_TitleExpand");
    EXPECT_EQ(iter3->second, "");

    Recorder::EventController::Get().Unregister(observer);
}

/**
 * @tc.name: EventRecorderTest005
 * @tc.desc: Test node data cache.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, EventRecorderTest005, TestSize.Level1)
{
    std::string config;
    GetConfig(config);
    auto observer = std::make_shared<DemoUIEventObserver>();
    Recorder::EventController::Get().Register(config, observer);

    /**
     * @tc.steps: step1. test index page.
     * @tc.expected: step1. get value success.
     */
    Recorder::NodeDataCache::Get().OnPageShow("pages/Index");
    auto pageNode = CreatePageNode("pages/Index");

    Recorder::NodeDataCache::Get().PutString(pageNode, "btn_TitleExpand", "abc");
    Recorder::NodeDataCache::Get().PutInt(pageNode, "btn_OpenSelf", 2);
    Recorder::NodeDataCache::Get().PutBool(pageNode, "btn_Screenshot", true);
    Recorder::NodeDataCache::Get().PutMultiple(pageNode, "btn_inspect", "inspect", 11);
    Recorder::NodeDataCache::Get().PutMultiple(pageNode, "btn_xxx", "xxx", true);
    std::vector<std::string> values = { "a", "b", "c" };
    Recorder::NodeDataCache::Get().PutMultiple(pageNode, "hahaha", "xixi", values);

    Recorder::NodeDataCache::Get().OnPageShow("pages/ScrollPage");
    auto pageNode2 = CreatePageNode("pages/ScrollPage");

    std::vector<std::string> values2 = { "x", "y", "z" };
    Recorder::NodeDataCache::Get().PutStringArray(pageNode2, "scroll_item_1", values2);

    Recorder::NodeDataCache::Get().OnBeforePagePop();

    /**
     * @tc.steps: step1. test index page.
     * @tc.expected: step1. get value success.
     */
    auto nodeValues4 = std::unordered_map<std::string, std::string>();
    nodeValues4.emplace("btn_TitleExpand", "");
    nodeValues4.emplace("btn_OpenSelf", "");
    nodeValues4.emplace("btn_Screenshot", "");
    Recorder::NodeDataCache::Get().GetNodeData("pages/Index", nodeValues4);

    auto iter4 = nodeValues4.find("btn_TitleExpand");
    EXPECT_EQ(iter4->second, "abc");

    iter4 = nodeValues4.find("btn_OpenSelf");
    EXPECT_EQ(iter4->second, "2");

    iter4 = nodeValues4.find("btn_Screenshot");
    EXPECT_EQ(iter4->second, "true");

    Recorder::EventController::Get().Unregister(observer);
}

/**
 * @tc.name: EventRecorderTest006
 * @tc.desc: Test node data cache.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, EventRecorderTest006, TestSize.Level1)
{
    std::string config;
    GetConfig(config);
    auto observer = std::make_shared<DemoUIEventObserver>();
    Recorder::EventController::Get().Register(config, observer);

    /**
     * @tc.steps: step1. test index page.
     * @tc.expected: step1. get value success.
     */
    Recorder::NodeDataCache::Get().OnPageShow("pages/Index");
    auto pageNode = CreatePageNode("pages/Index");

    Recorder::NodeDataCache::Get().PutString(pageNode, "btn_TitleExpand", "abc");
    Recorder::NodeDataCache::Get().PutInt(pageNode, "btn_OpenSelf", 2);
    Recorder::NodeDataCache::Get().PutBool(pageNode, "btn_Screenshot", true);
    Recorder::NodeDataCache::Get().PutMultiple(pageNode, "btn_inspect", "inspect", 11);
    Recorder::NodeDataCache::Get().PutMultiple(pageNode, "btn_xxx", "xxx", true);
    std::vector<std::string> values = { "a", "b", "c" };
    Recorder::NodeDataCache::Get().PutMultiple(pageNode, "hahaha", "xixi", values);

    Recorder::NodeDataCache::Get().OnPageShow("pages/ScrollPage");
    auto pageNode2 = CreatePageNode("pages/ScrollPage");

    std::vector<std::string> values2 = { "x", "y", "z" };
    Recorder::NodeDataCache::Get().PutStringArray(pageNode2, "scroll_item_1", values2);

    Recorder::NodeDataCache::Get().OnBeforePagePop();
    Recorder::NodeDataCache::Get().OnPageShow("pages/Index");

    /**
     * @tc.steps: step1. test update value.
     * @tc.expected: step1. get value success.
     */
    Recorder::NodeDataCache::Get().PutString(pageNode, "btn_TitleExpand", "hello");
    auto nodeValues5 = std::unordered_map<std::string, std::string>();
    nodeValues5.emplace("btn_TitleExpand", "");
    Recorder::NodeDataCache::Get().GetNodeData("pages/Index", nodeValues5);

    auto iter5 = nodeValues5.find("btn_TitleExpand");
    EXPECT_EQ(iter5->second, "hello");

    Recorder::EventController::Get().Unregister(observer);
}

/**
 * @tc.name: EventRecorderTest007
 * @tc.desc: Test node data cache.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, EventRecorderTest007, TestSize.Level1)
{
    std::string config;
    GetConfig(config);
    auto observer = std::make_shared<DemoUIEventObserver>();
    Recorder::EventController::Get().Register(config, observer);

    Recorder::NodeDataCache::Get().OnPageShow("pages/Index");
    auto pageNode = CreatePageNode("pages/Index");

    Recorder::NodeDataCache::Get().PutString(pageNode, "btn_TitleExpand", "abc");
    Recorder::NodeDataCache::Get().PutInt(pageNode, "btn_OpenSelf", 2);
    Recorder::NodeDataCache::Get().PutBool(pageNode, "btn_Screenshot", true);
    Recorder::NodeDataCache::Get().PutMultiple(pageNode, "btn_inspect", "inspect", 11);
    Recorder::NodeDataCache::Get().PutMultiple(pageNode, "btn_xxx", "xxx", true);
    std::vector<std::string> values = { "a", "b", "c" };
    Recorder::NodeDataCache::Get().PutMultiple(pageNode, "hahaha", "xixi", values);

    Recorder::NodeDataCache::Get().OnPageShow("pages/ScrollPage");
    auto pageNode2 = CreatePageNode("pages/ScrollPage");

    std::vector<std::string> values2 = { "x", "y", "z" };
    Recorder::NodeDataCache::Get().PutStringArray(pageNode2, "scroll_item_1", values2);

    Recorder::NodeDataCache::Get().OnBeforePagePop();

    Recorder::NodeDataCache::Get().PutString(pageNode, "btn_TitleExpand", "hello");

    /**
     * @tc.steps: step1. test clear.
     * @tc.expected: step1. get value success.
     */
    Recorder::NodeDataCache::Get().Clear("pages/Index");
    auto nodeValues6 = std::unordered_map<std::string, std::string>();
    nodeValues6.emplace("btn_TitleExpand", "");
    auto iter6 = nodeValues6.find("btn_TitleExpand");
    EXPECT_EQ(iter6->second, "");

    Recorder::EventController::Get().Unregister(observer);
}

/**
 * @tc.name: EventRecorderTest008
 * @tc.desc: Test node exposure.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, EventRecorderTest008, TestSize.Level1)
{
    std::string config;
    GetConfig(config);
    auto observer = std::make_shared<DemoUIEventObserver>();
    Recorder::EventController::Get().Register(config, observer);
    Recorder::NodeDataCache::Get().OnPageShow("pages/Index");
    auto exposure = AceType::MakeRefPtr<Recorder::ExposureProcessor>("pages/Index", "btn_TitleExpand");
    EXPECT_TRUE(exposure->IsNeedRecord());
    EXPECT_NEAR(exposure->GetRatio(), 0.9, 0.00001f);
    exposure->OnVisibleChange(true);
    sleep(2);
    exposure->OnVisibleChange(false);

    sleep(1);
    EXPECT_EQ(observer->GetEventType(), static_cast<int32_t>(Recorder::EventType::EXPOSURE));
    Recorder::EventController::Get().Unregister(observer);
}

/**
 * @tc.name: EventRecorderTest009
 * @tc.desc: Test node recorder.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, EventRecorderTest009, TestSize.Level1)
{
    std::string config;
    GetConfig(config);
    auto observer = std::make_shared<DemoUIEventObserver>();
    Recorder::EventController::Get().Register(config, observer);

    Recorder::EventParamsBuilder builder1;
    builder1.SetId("hello").SetPageUrl("pages/Index").SetText("world");
    LOGI("OnClick");
    Recorder::EventRecorder::Get().OnClick(std::move(builder1));
    sleep(1);

    Recorder::EventParamsBuilder builder2;
    builder2.SetId("hello").SetPageUrl("pages/Index").SetText("world").SetChecked(true);
    LOGI("OnChange");
    Recorder::EventRecorder::Get().OnChange(std::move(builder2));
    sleep(1);
    EXPECT_EQ(observer->GetEventType(), static_cast<int32_t>(Recorder::EventType::CHANGE));

    Recorder::EventParamsBuilder builder3;
    builder3.SetId("hello")
        .SetPageUrl("pages/Index")
        .SetText("weather")
        .SetEventType(Recorder::EventType::SEARCH_SUBMIT);
    LOGI("OnEvent");
    Recorder::EventRecorder::Get().OnEvent(std::move(builder3));
    sleep(1);
    EXPECT_EQ(observer->GetEventType(), static_cast<int32_t>(Recorder::EventType::SEARCH_SUBMIT));

    Recorder::EventRecorder::Get().OnPageShow("pages/Index", "from moon");
    sleep(1);
    EXPECT_EQ(observer->GetEventType(), static_cast<int32_t>(Recorder::EventType::PAGE_SHOW));

    Recorder::EventRecorder::Get().OnPageHide("pages/Index", 10000);
    sleep(1);
    EXPECT_EQ(observer->GetEventType(), static_cast<int32_t>(Recorder::EventType::PAGE_HIDE));

    Recorder::EventParamsBuilder builder4;
    builder4.SetText("tom");
    Recorder::EventRecorder::Get().OnNavDstShow(std::move(builder4));
    sleep(1);
    EXPECT_EQ(observer->GetEventType(), static_cast<int32_t>(Recorder::EventType::PAGE_SHOW));

    Recorder::EventParamsBuilder builder5;
    builder5.SetText("");
    builder5.SetText("tom");
    Recorder::EventRecorder::Get().OnNavDstHide(std::move(builder5));
    sleep(1);
    EXPECT_EQ(observer->GetEventType(), static_cast<int32_t>(Recorder::EventType::PAGE_HIDE));

    Recorder::EventController::Get().Unregister(observer);
}

/**
 * @tc.name: EventRecorderTest010
 * @tc.desc: Test ToString MapToString
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, EventRecorderTest010, TestSize.Level1)
{
    Recorder::EventParamsBuilder eventBuilder;
    std::string ret = eventBuilder.ToString();
    EXPECT_EQ(ret, "{}");
    std::string ret2 = eventBuilder.SetEventType(Recorder::EventType::PAGE_SHOW).ToString();
    EXPECT_EQ(ret2, "{eventType:1, }");
    const std::shared_ptr<std::unordered_map<std::string, std::string>> input = nullptr;
    std::string ret3 = Recorder::MapToString(input);
    EXPECT_EQ(ret3, "");
    const std::shared_ptr<std::unordered_map<std::string, std::string>> input2 =
        std::make_shared<std::unordered_map<std::string, std::string>>();
    input2->emplace("key1", "value1");
    std::string ret4 = Recorder::MapToString(input2);
    EXPECT_EQ(ret4, "{key1:value1, }");
}

/**
 * @tc.name: EventRecorderTest011
 * @tc.desc: Test SetContainerInfo
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, EventRecorderTest011, TestSize.Level1)
{
    // windowName = "$HA_FLOAT_WINDOW$"
    std::string windowName = "$HA_FLOAT_WINDOW$";
    int32_t id = 1;
    bool foreground = true;
    Recorder::EventRecorder::Get().SetContainerInfo(windowName, id, foreground);
    EXPECT_EQ(Recorder::EventRecorder::Get().GetContainerId() == -1, true);
    Recorder::EventRecorder::Get().SetFocusContainerInfo(windowName, id);
    EXPECT_EQ(Recorder::EventRecorder::Get().GetContainerId() == -1, true);
    // windowName = "pages/Index",foreground = true
    windowName = "pages/Index";
    Recorder::EventRecorder::Get().SetContainerInfo(windowName, id, true);
    EXPECT_EQ(Recorder::EventRecorder::Get().GetContainerId() == -1, true);
    Recorder::EventRecorder::Get().SetFocusContainerInfo(windowName, 2);
    EXPECT_EQ(Recorder::EventRecorder::Get().GetContainerId() == 2, true);
    // windowName = "pages/Index",foreground = false
    Recorder::EventRecorder::Get().SetContainerInfo(windowName, id, false);
    EXPECT_EQ(Recorder::EventRecorder::Get().GetContainerId() == 2, true);
}

/**
 * @tc.name: EventRecorderTest012
 * @tc.desc: Test SetDescription/SetNavDst
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, EventRecorderTest012, TestSize.Level1)
{
    Recorder::EventParamsBuilder eventBuilder;
    std::string desc = "desc";
    std::shared_ptr<std::unordered_map<std::string, std::string>> ret = eventBuilder.SetDescription(desc).build();
    EXPECT_EQ(ret->size(), 2);
    std::string dstName = "dstName";
    std::shared_ptr<std::unordered_map<std::string, std::string>> ret2 = eventBuilder.SetNavDst(dstName).build();
    EXPECT_EQ(ret2->size(), 3);
}

/**
 * @tc.name: SetContainerInfo001
 * @tc.desc: Test SetContainerInfo.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, SetContainerInfo001, TestSize.Level1)
{
    Recorder::EventRecorder::Get().containerId_ = 1;
    Recorder::EventRecorder::Get().focusContainerId_ = 2;
    std::string windowName = "$HA_FLOAT_WINDOW$";
    Recorder::EventRecorder::Get().SetContainerInfo(windowName, 0, true);
    EXPECT_EQ(Recorder::EventRecorder::Get().GetContainerId(), 2);
    EXPECT_EQ(Recorder::EventRecorder::Get().GetContainerId(false), 1);
}

/**
 * @tc.name: SetContainerInfo002
 * @tc.desc: Test SetContainerInfo.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, SetContainerInfo002, TestSize.Level1)
{
    std::string windowName = "";
    Recorder::EventRecorder::Get().SetContainerInfo(windowName, 0, true);
    EXPECT_NE(Recorder::EventRecorder::Get().GetContainerId(), 0);
}

/**
 * @tc.name: SetContainerInfo003
 * @tc.desc: Test SetContainerInfo.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, SetContainerInfo003, TestSize.Level1)
{
    Recorder::EventRecorder::Get().containerId_ = 1;
    Recorder::EventRecorder::Get().focusContainerId_ = 2;
    std::string windowName = "";
    Recorder::EventRecorder::Get().SetContainerInfo(windowName, 0, false);
    EXPECT_EQ(Recorder::EventRecorder::Get().GetContainerId(), 2);
}

/**
 * @tc.name: SetFocusContainerInfo001
 * @tc.desc: Test SetFocusContainerInfo.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, SetFocusContainerInfo001, TestSize.Level1)
{
    Recorder::EventRecorder::Get().containerId_ = 1;
    Recorder::EventRecorder::Get().focusContainerId_ = 2;
    std::string windowName = "$HA_FLOAT_WINDOW$";
    Recorder::EventRecorder::Get().SetFocusContainerInfo(windowName, 0);
    EXPECT_EQ(Recorder::EventRecorder::Get().GetContainerId(), 2);
}

/**
 * @tc.name: SetFocusContainerInfo002
 * @tc.desc: Test SetFocusContainerInfo.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, SetFocusContainerInfo002, TestSize.Level1)
{
    Recorder::EventRecorder::Get().containerId_ = 1;
    Recorder::EventRecorder::Get().focusContainerId_ = 2;
    std::string windowName = "";
    Recorder::EventRecorder::Get().SetFocusContainerInfo(windowName, 0);
    EXPECT_EQ(Recorder::EventRecorder::Get().GetContainerId(), 0);
}

/**
 * @tc.name: Init001
 * @tc.desc: Test Init.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, Init001, TestSize.Level1)
{
    std::string str = "";
    Recorder::EventConfig* config = new Recorder::EventConfig();
    config->Init(str);
    EXPECT_EQ(str, "");
    delete config;
}

/**
 * @tc.name: Init002
 * @tc.desc: Test Init.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, Init002, TestSize.Level1)
{
    std::string str;
    GetConfigTest(str);
    Recorder::EventConfig* config = new Recorder::EventConfig();
    config->Init(str);
    EXPECT_NE(str, "");
    delete config;
}

/**
 * @tc.name: Init003
 * @tc.desc: Test Init.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, Init003, TestSize.Level1)
{
    std::string str;
    GetConfigTest2(str);
    Recorder::EventConfig* config = new Recorder::EventConfig();
    config->Init(str);
    EXPECT_NE(str, "");
    delete config;
}

/**
 * @tc.name: Init004
 * @tc.desc: Test Init.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, Init004, TestSize.Level1)
{
    std::string str;
    GetConfigTest3(str);
    Recorder::EventConfig* config = new Recorder::EventConfig();
    config->Init(str);
    EXPECT_NE(str, "");
    delete config;
}

/**
 * @tc.name: Init005
 * @tc.desc: Test Init.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, Init005, TestSize.Level1)
{
    std::string str;
    GetConfigTest4(str);
    Recorder::EventConfig* config = new Recorder::EventConfig();
    config->Init(str);
    EXPECT_NE(str, "");
    delete config;
}

/**
 * @tc.name: IsPageRecordEnable001
 * @tc.desc: Test IsPageRecordEnable.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, IsPageRecordEnable001, TestSize.Level1)
{
    EXPECT_TRUE(Recorder::EventRecorder::Get().IsPageRecordEnable());
}

/**
 * @tc.name: IsPageRecordEnable002
 * @tc.desc: Test IsPageRecordEnable.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, IsPageRecordEnable002, TestSize.Level1)
{
    int32_t index = static_cast<int32_t>(Recorder::EventCategory::CATEGORY_PAGE);
    Recorder::EventRecorder::Get().globalSwitch_[index] = false;
    Recorder::EventRecorder::Get().eventSwitch_[index] = true;
    EXPECT_FALSE(Recorder::EventRecorder::Get().IsPageRecordEnable());
}

/**
 * @tc.name: IsPageRecordEnable003
 * @tc.desc: Test IsPageRecordEnable.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, IsPageRecordEnable003, TestSize.Level1)
{
    int32_t index = static_cast<int32_t>(Recorder::EventCategory::CATEGORY_PAGE);
    Recorder::EventRecorder::Get().globalSwitch_[index] = true;
    Recorder::EventRecorder::Get().eventSwitch_[index] = false;
    EXPECT_FALSE(Recorder::EventRecorder::Get().IsPageRecordEnable());
}

/**
 * @tc.name: IsPageRecordEnable004
 * @tc.desc: Test IsPageRecordEnable.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, IsPageRecordEnable004, TestSize.Level1)
{
    int32_t index = static_cast<int32_t>(Recorder::EventCategory::CATEGORY_PAGE);
    Recorder::EventRecorder::Get().globalSwitch_[index] = false;
    Recorder::EventRecorder::Get().eventSwitch_[index] = false;
    EXPECT_FALSE(Recorder::EventRecorder::Get().IsPageRecordEnable());
}

/**
 * @tc.name: IsComponentRecordEnable001
 * @tc.desc: Test IsComponentRecordEnable.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, IsComponentRecordEnable001, TestSize.Level1)
{
    EXPECT_FALSE(Recorder::EventRecorder::Get().IsComponentRecordEnable());
}

/**
 * @tc.name: IsComponentRecordEnable002
 * @tc.desc: Test IsComponentRecordEnable.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, IsComponentRecordEnable002, TestSize.Level1)
{
    int32_t index = static_cast<int32_t>(Recorder::EventCategory::CATEGORY_COMPONENT);
    Recorder::EventRecorder::Get().globalSwitch_[index] = true;
    Recorder::EventRecorder::Get().eventSwitch_[index] = false;
    EXPECT_FALSE(Recorder::EventRecorder::Get().IsComponentRecordEnable());
}

/**
 * @tc.name: IsComponentRecordEnable003
 * @tc.desc: Test IsComponentRecordEnable.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, IsComponentRecordEnable003, TestSize.Level1)
{
    int32_t index = static_cast<int32_t>(Recorder::EventCategory::CATEGORY_COMPONENT);
    Recorder::EventRecorder::Get().globalSwitch_[index] = false;
    Recorder::EventRecorder::Get().eventSwitch_[index] = true;
    EXPECT_FALSE(Recorder::EventRecorder::Get().IsComponentRecordEnable());
}

/**
 * @tc.name: IsComponentRecordEnable004
 * @tc.desc: Test IsComponentRecordEnable.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, IsComponentRecordEnable004, TestSize.Level1)
{
    int32_t index = static_cast<int32_t>(Recorder::EventCategory::CATEGORY_COMPONENT);
    Recorder::EventRecorder::Get().globalSwitch_[index] = false;
    Recorder::EventRecorder::Get().eventSwitch_[index] = false;
    EXPECT_FALSE(Recorder::EventRecorder::Get().IsComponentRecordEnable());
}

/**
 * @tc.name: IsRecordEnable001
 * @tc.desc: Test IsRecordEnable.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, IsRecordEnable001, TestSize.Level1)
{
    int32_t index = static_cast<int32_t>(Recorder::EventCategory::CATEGORY_WEB);
    Recorder::EventRecorder::Get().globalSwitch_[index] = false;
    Recorder::EventRecorder::Get().eventSwitch_[index] = false;
    EXPECT_FALSE(Recorder::EventRecorder::Get().IsRecordEnable(Recorder::EventCategory::CATEGORY_WEB));
}

/**
 * @tc.name: IsCacheAvaliable001
 * @tc.desc: Test IsCacheAvaliable.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, IsCacheAvaliable001, TestSize.Level1)
{
    EXPECT_FALSE(Recorder::IsCacheAvaliable());
}

/**
 * @tc.name: IsCacheAvaliable002
 * @tc.desc: Test IsCacheAvaliable.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, IsCacheAvaliable002, TestSize.Level1)
{
    int32_t index = static_cast<int32_t>(Recorder::EventCategory::CATEGORY_COMPONENT);
    Recorder::EventRecorder::Get().globalSwitch_[index] = true;
    Recorder::EventRecorder::Get().eventSwitch_[index] = true;
    Recorder::NodeDataCache::Get().mergedConfig_->shareNodes["element"] = { "element1", "element2", "element3" };
    Recorder::IsCacheAvaliable();
    Recorder::EventRecorder::Get().globalSwitch_[index] = false;
    Recorder::EventRecorder::Get().eventSwitch_[index] = false;
    Recorder::NodeDataCache::Get().mergedConfig_->shareNodes.clear();
    EXPECT_FALSE(Recorder::IsCacheAvaliable());
}

/**
 * @tc.name: PutString001
 * @tc.desc: Test PutString.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, PutString001, TestSize.Level1)
{
    Recorder::ExposureCfg cfg;
    Recorder::NodeDataCache::Get().Clear("");
    auto pageNode = CreatePageNode("pages/Index");
    bool result = Recorder::NodeDataCache::Get().PutString(pageNode, "", "1");
    std::unordered_map<std::string, std::string> nodes;
    Recorder::NodeDataCache::Get().GetNodeData("", nodes);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: PutString002
 * @tc.desc: Test PutString.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, PutString002, TestSize.Level1)
{
    auto pageNode = CreatePageNode("pages/Index");
    std::string value;
    bool result = Recorder::NodeDataCache::Get().PutString(pageNode, "", value);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: PutString003
 * @tc.desc: Test PutString.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, PutString003, TestSize.Level1)
{
    std::string config;
    GetConfig(config);
    auto observer = std::make_shared<DemoUIEventObserver>();
    Recorder::EventController::Get().Register(config, observer);
    Recorder::NodeDataCache::Get().OnPageShow("pages/Index");
    auto pageNode = CreatePageNode("pages/Index");
    Recorder::NodeDataCache::Get().mergedConfig_->shareNodes["element"] = { "element1", "element2", "element3" };
    bool result = Recorder::NodeDataCache::Get().PutString(pageNode, "1", "1");
    EXPECT_TRUE(result);
}

/**
 * @tc.name: PutString004
 * @tc.desc: Test PutString.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, PutString004, TestSize.Level1)
{
    std::string config;
    GetConfig(config);
    auto observer = std::make_shared<DemoUIEventObserver>();
    Recorder::EventController::Get().Register(config, observer);
    Recorder::NodeDataCache::Get().OnPageShow("pages/Index");
    auto pageNode = CreatePageNode("pages/Index");
    Recorder::NodeDataCache::Get().mergedConfig_->shareNodes.clear();
    bool result = Recorder::NodeDataCache::Get().PutString(pageNode, "1", "1");
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnBeforePagePop001
 * @tc.desc: Test OnBeforePagePop.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, OnBeforePagePop001, TestSize.Level1)
{
    Recorder::NodeDataCache::Get().OnBeforePagePop(true);
    EXPECT_FALSE(Recorder::NodeDataCache::Get().ShouldCollectData());
}

/**
 * @tc.name: GetExposureCfg001
 * @tc.desc: Test GetExposureCfg.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, GetExposureCfg001, TestSize.Level1)
{
    Recorder::ExposureCfg cfg;
    std::string pageUrl = "";
    Recorder::NodeDataCache::Get().GetExposureCfg(pageUrl, "", cfg);
    EXPECT_TRUE(pageUrl.empty());
}

/**
 * @tc.name: SetExtra001
 * @tc.desc: Test SetExtra.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, SetExtra001, TestSize.Level1)
{
    std::string key = "";
    std::string value = "";
    Recorder::EventParamsBuilder builder1;
    builder1.SetExtra(key, value);
    std::string result = builder1.GetValue("text");
    EXPECT_EQ(result, "");
}

/**
 * @tc.name: SetExtra002
 * @tc.desc: Test SetExtra.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, SetExtra002, TestSize.Level1)
{
    std::string key = "123";
    std::string value = "";
    Recorder::EventParamsBuilder builder1;
    builder1.SetExtra(key, value);
    EXPECT_TRUE(builder1.params_->empty());
}

/**
 * @tc.name: SetExtra003
 * @tc.desc: Test SetExtra.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, SetExtra003, TestSize.Level1)
{
    std::string key = "";
    std::string value = "123";
    Recorder::EventParamsBuilder builder1;
    builder1.SetExtra(key, value);
    EXPECT_TRUE(builder1.params_->empty());
}

/**
 * @tc.name: SetExtra004
 * @tc.desc: Test SetExtra.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, SetExtra004, TestSize.Level1)
{
    std::string key = "123";
    std::string value = "123";
    Recorder::EventParamsBuilder builder1;
    builder1.SetExtra(key, value);
    std::string result = builder1.ToString();
    EXPECT_NE(result, "");
}

/**
 * @tc.name: SetTextArray001
 * @tc.desc: Test SetTextArray.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, SetTextArray001, TestSize.Level1)
{
    std::vector<std::string> value = { "50", "100", "200", "300" };
    Recorder::EventParamsBuilder builder1;
    builder1.SetTextArray(value);
    EXPECT_FALSE(builder1.params_->empty());
}

/**
 * @tc.name: SetId001
 * @tc.desc: Test SetId.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, SetId001, TestSize.Level1)
{
    std::vector<std::string> value = { "50", "100", "200", "300" };
    Recorder::EventParamsBuilder builder1;
    builder1.SetId("");
    EXPECT_TRUE(builder1.params_->empty());
}

/**
 * @tc.name: OnNavDstHide001
 * @tc.desc: Test OnNavDstHide.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, OnNavDstHide001, TestSize.Level1)
{
    Recorder::EventParamsBuilder builder1;
    builder1.SetExtra("1", "1");
    builder1.SetNavDst("1");
    Recorder::EventRecorder::Get().navShowTime_ = 0;
    Recorder::EventRecorder::Get().OnNavDstHide(std::move(builder1));
    EXPECT_EQ(builder1.GetValue("1"), "1");
    EXPECT_EQ(Recorder::EventRecorder::Get().GetNavDstName(), "");
}

/**
 * @tc.name: OnNavDstHide002
 * @tc.desc: Test OnNavDstHide.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, OnNavDstHide002, TestSize.Level1)
{
    Recorder::EventParamsBuilder builder1;
    builder1.SetText("1");
    Recorder::EventRecorder::Get().navDstName_ = "";
    Recorder::EventRecorder::Get().OnNavDstHide(std::move(builder1));
    EXPECT_NE(Recorder::EventRecorder::Get().GetNavDstName(), builder1.GetValue("text"));
}

/**
 * @tc.name: IsCategoryEnable001
 * @tc.desc: Test IsCategoryEnable
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, IsCategoryEnable001, TestSize.Level1)
{
    int32_t index = static_cast<int32_t>(Recorder::EventCategory::CATEGORY_COMPONENT);
    Recorder::EventConfig* config = new Recorder::EventConfig();
    config->switches_[index] = false;
    index = static_cast<int32_t>(Recorder::EventCategory::CATEGORY_PAGE);
    bool result = config->IsCategoryEnable(index);
    EXPECT_FALSE(result);
    delete config;
}

/**
 * @tc.name: Register001
 * @tc.desc: Test register.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, Register001, TestSize.Level1)
{
    std::string config;
    GetConfigDisable(config);
    auto observer = std::make_shared<DemoUIEventObserver>();
    Recorder::EventController::Get().Register(config, observer);
    Recorder::EventController::Get().NotifyConfigChange();
    EXPECT_FALSE(Recorder::EventController::Get().clientList_.empty());
}

/**
 * @tc.name: ApplyNewestConfig001
 * @tc.desc: Test ApplyNewestConfig.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, ApplyNewestConfig001, TestSize.Level1)
{
    Recorder::EventParamsBuilder builder1;
    builder1.SetId("hello").SetPageUrl("pages/Index").SetText("world");
    auto params = builder1.build();
    Recorder::EventController::Get().clientList_.clear();
    Recorder::EventController::Get().ApplyNewestConfig(false);
    Recorder::EventController::Get().NotifyEvent(
        Recorder::EventCategory::CATEGORY_COMPONENT, Recorder::EventType::CHANGE, std::move(params));
    EXPECT_TRUE(Recorder::EventController::Get().clientList_.empty());
}

/**
 * @tc.name: IsExposureRecordEnable001
 * @tc.desc: Test IsExposureRecordEnable.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, IsExposureRecordEnable001, TestSize.Level1)
{
    int32_t index = static_cast<int32_t>(Recorder::EventCategory::CATEGORY_EXPOSURE);
    Recorder::EventRecorder::Get().globalSwitch_[index] = true;
    Recorder::EventRecorder::Get().eventSwitch_[index] = true;
    EXPECT_TRUE(Recorder::EventRecorder::Get().IsExposureRecordEnable());
}

/**
 * @tc.name: IsExposureRecordEnable002
 * @tc.desc: Test IsExposureRecordEnable.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, IsExposureRecordEnable002, TestSize.Level1)
{
    int32_t index = static_cast<int32_t>(Recorder::EventCategory::CATEGORY_EXPOSURE);
    Recorder::EventRecorder::Get().globalSwitch_[index] = false;
    Recorder::EventRecorder::Get().eventSwitch_[index] = true;
    EXPECT_FALSE(Recorder::EventRecorder::Get().IsExposureRecordEnable());
}

/**
 * @tc.name: IsExposureRecordEnable003
 * @tc.desc: Test IsExposureRecordEnable.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, IsExposureRecordEnable003, TestSize.Level1)
{
    int32_t index = static_cast<int32_t>(Recorder::EventCategory::CATEGORY_EXPOSURE);
    Recorder::EventRecorder::Get().globalSwitch_[index] = true;
    Recorder::EventRecorder::Get().eventSwitch_[index] = false;
    EXPECT_FALSE(Recorder::EventRecorder::Get().IsExposureRecordEnable());
}

/**
 * @tc.name: IsExposureRecordEnable004
 * @tc.desc: Test IsExposureRecordEnable.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, IsExposureRecordEnable004, TestSize.Level1)
{
    int32_t index = static_cast<int32_t>(Recorder::EventCategory::CATEGORY_EXPOSURE);
    Recorder::EventRecorder::Get().globalSwitch_[index] = false;
    Recorder::EventRecorder::Get().eventSwitch_[index] = false;
    EXPECT_FALSE(Recorder::EventRecorder::Get().IsExposureRecordEnable());
}

/**
 * @tc.name: GetPageUrl001
 * @tc.desc: Test GetPageUrl.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, GetPageUrl001, TestSize.Level1)
{
    Recorder::EventRecorder::Get().pageUrl_ = "url";
    Recorder::EventRecorder::Get().isFocusContainerChanged_ = false;
    std::string url = Recorder::EventRecorder::Get().GetPageUrl();
    EXPECT_NE(url, "");
}

/**
 * @tc.name: IsPageParamRecordEnable001
 * @tc.desc: Test IsPageParamRecordEnable.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, IsPageParamRecordEnable001, TestSize.Level1)
{
    int32_t index = static_cast<int32_t>(EventCategory::CATEGORY_PAGE_PARAM);
    EventRecorder::Get().globalSwitch_[index] = true;
    EventRecorder::Get().eventSwitch_[index] = false;
    EXPECT_FALSE(EventRecorder::Get().IsPageParamRecordEnable());
    index = static_cast<int32_t>(EventCategory::CATEGORY_WEB);
    EventRecorder::Get().globalSwitch_[index] = true;
    EventRecorder::Get().eventSwitch_[index] = true;
    EXPECT_FALSE(EventRecorder::Get().IsComponentRecordEnable());

    std::string str;
    GetConfigTest5(str);
    EventConfig* config = new EventConfig();
    config->Init(str);
    EXPECT_FALSE(config->GetWebJsCode().empty());
    EXPECT_FALSE(config->GetWebCategory().empty());
    EXPECT_TRUE(config->IsCategoryEnable(index));
    delete config;
}

/**
 * @tc.name: FillWebJsCode001
 * @tc.desc: Test FillWebJsCode.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, FillWebJsCode001, TestSize.Level1)
{
    int32_t index = static_cast<int32_t>(EventCategory::CATEGORY_WEB);
    EventRecorder::Get().globalSwitch_[index] = true;
    EventRecorder::Get().eventSwitch_[index] = true;
    std::string config;
    GetConfigTest5(config);
    auto observer = std::make_shared<DemoUIEventObserver>();
    EventController::Get().Register(config, observer);
    std::optional<WebJsItem> scriptItems = std::nullopt;
    EventRecorder::Get().FillWebJsCode(scriptItems);
    EXPECT_TRUE(scriptItems.has_value());
    scriptItems = std::make_optional<WebJsItem>();
    EventRecorder::Get().FillWebJsCode(scriptItems);
    EXPECT_TRUE(scriptItems.has_value());

    EXPECT_TRUE(EventRecorder::Get().IsMessageValid("test", "abc"));
    EXPECT_FALSE(EventRecorder::Get().IsMessageValid("", "abc"));
    EXPECT_FALSE(EventRecorder::Get().IsMessageValid("ttt", "abc"));
}

/**
 * @tc.name: InspectorTreeCollectorTest001
 * @tc.desc: Test register.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, InspectorTreeCollectorTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call the Constructor.
     * @tc.expected: step1. Constructor success.
     */
    InspectorTreeCollector collector([](const std::shared_ptr<std::string> tree) {}, false);
    EXPECT_TRUE(collector.root_ != nullptr);
}

/**
 * @tc.name: InspectorTreeCollectorTest002
 * @tc.desc: Test node data cache.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, InspectorTreeCollectorTest002, TestSize.Level1)
{
    InspectorTreeCollector collector([](const std::shared_ptr<std::string> tree) {}, false);
    collector.taskNum_ = 0;
    /**
     * @tc.steps: step1. call the IncreaseTaskNum.
     * @tc.expected: step1. IncreaseTaskNum success.
     */
    collector.IncreaseTaskNum();
    EXPECT_EQ(collector.taskNum_, 1);
    /**
     * @tc.steps: step2. call the DecreaseTaskNum.
     * @tc.expected: step2. DecreaseTaskNum success.
     */
    collector.DecreaseTaskNum();
    EXPECT_EQ(collector.taskNum_, 0);
    /**
     * @tc.steps: step3. call the UpdateTaskNum.
     * @tc.expected: step3. UpdateTaskNum success.
     */
    collector.UpdateTaskNum(2);
    EXPECT_EQ(collector.taskNum_, 2);
}

/**
 * @tc.name: AddApiTest001
 * @tc.desc: FillExtraTextIfNeed
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, AddApiTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare the environment variables for the function.
     */
    Recorder::EventParamsBuilder builder;
    string value = "";
    builder.params_->emplace(KEY_TEXT, value);
    auto pageNode = CreatePageNode("pages/Index");
    builder.eventType_ = Recorder::EventType::CLICK;
    builder.SetHost(pageNode);

    /**
     * @tc.steps: step2. set different variables to meet the conditional values and test OnWebEvent.
     */
    EventRecorder::Get().globalSwitch_[10] = true;
    EventRecorder::Get().eventSwitch_[10] = true;
    builder.SetHost(pageNode);

    /**
     * @tc.steps: step2. set the different variables to test.
     */
    auto pageNode2 = CreatePageNode("pages/Index2");
    pageNode->AddChild(pageNode2, 1, false);
    builder.SetHost(pageNode);
    EXPECT_EQ(builder.params_->empty(), false);
}

/**
 * @tc.name: AddApiTest002
 * @tc.desc: SetHostOnWebEvent
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTest, AddApiTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare the environment variables for the function.
     */
    Recorder::EventParamsBuilder builder;
    auto pageNode = CreatePageNode("pages/Index");
    EventRecorder::Get().globalSwitch_[6] = true;
    EventRecorder::Get().eventSwitch_[6] = true;

    /**
     * @tc.steps: step2. test SetHost.
     */
    builder.SetHost(pageNode);

    /**
     * @tc.steps: step3. set the variables to meet the conditional values and test OnWebEvent.
     */
    auto pageNode2 = CreatePageNode("pages/Index");
    vector<std::string> params;
    Recorder::EventRecorder::Get().OnWebEvent(pageNode2, params);
    vector<std::string> params2 = {"df", "rfds", "fd"};
    EventRecorder::Get().globalSwitch_[7] = true;
    Recorder::EventRecorder::Get().OnWebEvent(pageNode2, params2);
    EXPECT_EQ(builder.params_->empty(), false);
}
} // namespace OHOS::Ace
