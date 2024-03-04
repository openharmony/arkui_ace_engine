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

#include "gtest/gtest.h"

#include "base/log/log.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/common/recorder/event_controller.h"
#include "core/common/recorder/event_recorder.h"
#include "core/common/recorder/event_config.h"
#include "core/common/recorder/exposure_processor.h"
#include "core/common/recorder/node_data_cache.h"
#include "core/components_ng/pattern/stage/page_info.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "interfaces/inner_api/ace/ui_event_observer.h"

using namespace testing;
using namespace testing::ext;

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
    std::vector<std::string> values = {"a", "b", "c"};
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
    std::vector<std::string> values = {"a", "b", "c"};
    Recorder::NodeDataCache::Get().PutMultiple(pageNode, "hahaha", "xixi", values);

    /**
     * @tc.steps: step1. test scroll page.
     * @tc.expected: step1. get value success.
     */
    Recorder::NodeDataCache::Get().OnPageShow("pages/ScrollPage");
    auto pageNode2 = CreatePageNode("pages/ScrollPage");

    std::vector<std::string> values2 = {"x", "y", "z"};
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
    std::vector<std::string> values = {"a", "b", "c"};
    Recorder::NodeDataCache::Get().PutMultiple(pageNode, "hahaha", "xixi", values);

    Recorder::NodeDataCache::Get().OnPageShow("pages/ScrollPage");
    auto pageNode2 = CreatePageNode("pages/ScrollPage");

    std::vector<std::string> values2 = {"x", "y", "z"};
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
    std::vector<std::string> values = {"a", "b", "c"};
    Recorder::NodeDataCache::Get().PutMultiple(pageNode, "hahaha", "xixi", values);

    Recorder::NodeDataCache::Get().OnPageShow("pages/ScrollPage");
    auto pageNode2 = CreatePageNode("pages/ScrollPage");

    std::vector<std::string> values2 = {"x", "y", "z"};
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
    std::vector<std::string> values = {"a", "b", "c"};
    Recorder::NodeDataCache::Get().PutMultiple(pageNode, "hahaha", "xixi", values);

    Recorder::NodeDataCache::Get().OnPageShow("pages/ScrollPage");
    auto pageNode2 = CreatePageNode("pages/ScrollPage");

    std::vector<std::string> values2 = {"x", "y", "z"};
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
    std::vector<std::string> values = {"a", "b", "c"};
    Recorder::NodeDataCache::Get().PutMultiple(pageNode, "hahaha", "xixi", values);

    Recorder::NodeDataCache::Get().OnPageShow("pages/ScrollPage");
    auto pageNode2 = CreatePageNode("pages/ScrollPage");

    std::vector<std::string> values2 = {"x", "y", "z"};
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
    builder5.SetText("tom");
    Recorder::EventRecorder::Get().OnNavDstHide(std::move(builder5));
    sleep(1);
    EXPECT_EQ(observer->GetEventType(), static_cast<int32_t>(Recorder::EventType::PAGE_HIDE));

    Recorder::EventController::Get().Unregister(observer);
}
} // namespace OHOS::Ace
