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
#include "core/components_ng/base/simplified_inspector.h"
#include "core/components_ng/pattern/stage/page_info.h"
#include "core/components_ng/pattern/stage/page_pattern.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Recorder;

namespace OHOS::Ace {
namespace {
const char* const DEFAULT_CONFIG =
    "{\"enable\":true,\"switch\":{\"page\":true,\"component\":true,\"exposure\":true},\"config\":[{\"pageUrl\":"
    "\"pages/"
    "Index\",\"shareNode\":[\"hahaha\",\"btn_TitleExpand\",\"btn_OpenSelf\",\"btn_Screenshot\",\"btn_inspect\","
    "\"btn_xxx\",\"\"],\"exposureCfg\":[{\"id\":\"btn_Grid\",\"ratio\":0.75,\"duration\":5000},{\"id\":\"btn_"
    "TitleExpand\",\"ratio\":0.9,\"duration\":1000}]},{\"pageUrl\":\"pages/"
    "ScrollPage\",\"shareNode\":[\"scroll_item_1\"],\"exposureCfg\":[{\"id\":\"scroll_item_2\",\"ratio\":0.85,"
    "\"duration\":5000},{\"id\":\"scroll_item_12\",\"ratio\":0.4,\"duration\":3000}]}]}";

} // namespace
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

    virtual void NotifyUIEvent(
        int32_t eventType, const std::shared_ptr<std::unordered_map<std::string, std::string>>& eventParams)
    {
        LOGI("NotifyUIEvent eventType %{public}d", eventType);
        eventType_ = eventType;
    }

private:
    int32_t eventType_;
};

class EventRecorderTestTwo : public testing::Test {
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
 * @tc.name: EventRecorderTest021
 * @tc.desc: Test GetFirstImageNodeChild.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTestTwo, EventRecorderTest021, TestSize.Level1)
{
    auto pageNode = CreatePageNode("pages/Index");
    auto rowId = ElementRegister::GetInstance()->MakeUniqueId();
    auto rowNode =
        NG::FrameNode::GetOrCreateFrameNode("Row", rowId, []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    pageNode->AddChild(rowNode);
    auto imgId = ElementRegister::GetInstance()->MakeUniqueId();
    auto imgNode =
        NG::FrameNode::GetOrCreateFrameNode("Image", imgId, []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    rowNode->AddChild(imgNode);

    auto ret = GetFirstImageNodeChild(pageNode);
    EXPECT_TRUE(ret != nullptr);
}
/**
 * @tc.name: ApplyExposureCfgInner001
 * @tc.desc: Test ApplyExposureCfgInner.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTestTwo, ApplyExposureCfgInner001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize configuration and observer.
     * @tc.expected: Configuration is loaded and observer is created successfully.
     */
    auto observer = std::make_shared<DemoUIEventObserver>();
    
    /**
     * @tc.steps: step2. Set up UI event client with configuration and observer.
     * @tc.expected: Client is properly configured and added to controller.
     */
    UIEventClient client;
    client.config.Init(DEFAULT_CONFIG);
    ASSERT_TRUE(client.config.IsEnable());
    client.observer = observer;
    Recorder::EventController::Get().clientList_.emplace_back(client);
    EventRecorder::Get().focusContainerId_ = 1;
    EventRecorder::Get().containerId_ = 1;

    /**
     * @tc.steps: step3. Apply exposure configuration.
     * @tc.expected: Exposure configuration is applied successfully.
     */
    bool isExposureChanged = false;
    auto configPtr = Recorder::EventController::Get().clientList_.back().config.GetConfig();
    Recorder::EventController::Get().ApplyExposureCfgInner(configPtr, isExposureChanged);

    /**
     * @tc.steps: step4. Create event manager and test key event.
     * @tc.expected: Event manager is created and key event is processed.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    KeyEvent touchPoint;
    auto container = Container::GetContainer(eventManager->instanceId_);
}

/**
 * @tc.name: GetWebJsCodeList001
 * @tc.desc: Test GetWebJsCodeList.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTestTwo, GetWebJsCodeList001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Clear client list and initialize configuration.
     * @tc.expected: Client list is cleared and configuration is loaded.
     */
    Recorder::EventController::Get().clientList_.clear();
    auto observer = std::make_shared<DemoUIEventObserver>();

    /**
     * @tc.steps: step2. Configure client with alternating switch settings.
     * @tc.expected: Client switches are set with alternating true/false values.
     */
    UIEventClient client;
    client.config.Init(DEFAULT_CONFIG);
    ASSERT_TRUE(client.config.IsEnable());
    for (int i = 0; i < 5; i++) {
        if (i % 2 == 0) {
            client.config.switches_[i] = true;
        } else {
            client.config.switches_[i] = false;
        }
    }

    /**
     * @tc.steps: step3. Register observer and get web JS code list.
     * @tc.expected: Web JS code list is empty as no code is configured.
     */
    client.observer = observer;
    Recorder::EventController::Get().clientList_.emplace_back(client);
    std::vector<std::string> codeList;
    Recorder::EventController::Get().ApplyNewestConfig(false);
    codeList = Recorder::EventController::Get().GetWebJsCodeList();
    EXPECT_TRUE(codeList.empty());
}

/**
 * @tc.name: GetWebJsCodeList002
 * @tc.desc: Test GetWebJsCodeList.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTestTwo, GetWebJsCodeList002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Clear client list and initialize configuration.
     * @tc.expected: Client list is cleared and configuration is loaded.
     */
    Recorder::EventController::Get().clientList_.clear();
    auto observer = std::make_shared<DemoUIEventObserver>();

    /**
     * @tc.steps: step2. Configure client with alternating switch settings.
     * @tc.expected: Client switches are set with alternating true/false values.
     */
    UIEventClient client;
    client.config.Init(DEFAULT_CONFIG);
    ASSERT_TRUE(client.config.IsEnable());
    for (int i = 0; i < 10; i++) {
        client.config.switches_[i] = i % 2;
    }

    /**
     * @tc.steps: step3. Set empty web JS code and get code list.
     * @tc.expected: Web JS code list is empty as code string is empty.
     */
    client.config.webJsCode_ = "";
    client.observer = observer;
    Recorder::EventController::Get().clientList_.emplace_back(client);
    std::vector<std::string> codeList;
    Recorder::EventController::Get().ApplyNewestConfig(false);
    codeList = Recorder::EventController::Get().GetWebJsCodeList();
    EXPECT_TRUE(codeList.empty());
}

/**
 * @tc.name: GetWebJsCodeList003
 * @tc.desc: Test GetWebJsCodeList.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTestTwo, GetWebJsCodeList003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Clear client list and initialize configuration.
     * @tc.expected: Client list is cleared and configuration is loaded.
     */
    Recorder::EventController::Get().clientList_.clear();
    auto observer = std::make_shared<DemoUIEventObserver>();

    /**
     * @tc.steps: step2. Configure client with alternating switch settings.
     * @tc.expected: Client switches are set with alternating true/false values.
     */
    UIEventClient client;
    client.config.Init(DEFAULT_CONFIG);
    ASSERT_TRUE(client.config.IsEnable());
    for (int i = 0; i < 10; i++) {
        client.config.switches_[i] = i % 2;
    }

    /**
     * @tc.steps: step3. Set valid web JS code and get code list.
     * @tc.expected: Web JS code list contains the configured code.
     */
    client.config.webJsCode_ = "GetWebJsCode";
    client.observer = observer;
    Recorder::EventController::Get().clientList_.emplace_back(client);
    std::vector<std::string> codeList;
    Recorder::EventController::Get().ApplyNewestConfig(false);
    codeList = Recorder::EventController::Get().GetWebJsCodeList();
    EXPECT_FALSE(codeList.empty());
}

/**
 * @tc.name: FillWebJsCode002
 * @tc.desc: Test FillWebJsCode.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTestTwo, FillWebJsCode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Clear client list and initialize configuration.
     * @tc.expected: Client list is cleared and configuration is loaded.
     */
    Recorder::EventController::Get().clientList_.clear();
    auto observer = std::make_shared<DemoUIEventObserver>();

     /**
     * @tc.steps: step2. Configure client with alternating switch settings.
     * @tc.expected: Client switches are set with alternating true/false values.
     */
    UIEventClient client;
    client.config.Init(DEFAULT_CONFIG);
    ASSERT_TRUE(client.config.IsEnable());
    for (int i = 0; i < 10; i++) {
        client.config.switches_[i] = i % 2;
    }

    /**
     * @tc.steps: step3. Set empty web JS code and fill web JS code.
     * @tc.expected: Script items remain unchanged as web JS code is empty.
     */
    client.config.webJsCode_ = "";
    client.observer = observer;
    Recorder::EventController::Get().clientList_.emplace_back(client);
    std::vector<std::string> codeList;
    std::optional<WebJsItem> scriptItems = std::nullopt;
    EventRecorder::Get().FillWebJsCode(scriptItems);
    EXPECT_FALSE(scriptItems.has_value());
}

/**
 * @tc.name: ExposureProcessor001
 * @tc.desc: Test ExposureProcessor.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTestTwo, ExposureProcessor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize configuration and register observer.
     * @tc.expected: Configuration is loaded and observer is registered.
     */
    auto observer = std::make_shared<DemoUIEventObserver>();
    Recorder::EventController::Get().Register(DEFAULT_CONFIG, observer);
    Recorder::NodeDataCache::Get().OnPageShow("pages/Index");

    /**
     * @tc.steps: step2. Create exposure processor and test basic functionality.
     * @tc.expected: Exposure processor indicates recording is not needed and observer event type is invalid.
     */
    auto exposure = AceType::MakeRefPtr<Recorder::ExposureProcessor>("pages/Index", "");
    EXPECT_FALSE(exposure->IsNeedRecord());
    EXPECT_EQ(observer->GetEventType(), static_cast<int32_t>(Recorder::EventType::INVALID));
    Recorder::EventController::Get().Unregister(observer);
}

/**
 * @tc.name: OnVisibleChange001
 * @tc.desc: Test OnVisibleChange.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTestTwo, OnVisibleChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize configuration and register observer.
     * @tc.expected: Configuration is loaded and observer is registered.
     */
    auto observer = std::make_shared<DemoUIEventObserver>();
    Recorder::EventController::Get().Register(DEFAULT_CONFIG, observer);
    Recorder::NodeDataCache::Get().OnPageShow("pages/Index");

    /**
     * @tc.steps: step2. Create exposure processor and test visibility changes.
     * @tc.expected: Exposure processing occurs correctly with visibility changes.
     */
    auto exposure = AceType::MakeRefPtr<Recorder::ExposureProcessor>("pages/Index", "btn_TitleExpand");
    exposure->cfg_.duration = 5000;
    EXPECT_TRUE(exposure->IsNeedRecord());
    EXPECT_NEAR(exposure->GetRatio(), 0.9, 0.00001f);
    exposure->OnVisibleChange(true);
    sleep(2);
    exposure->OnVisibleChange(false);

    sleep(1);
    EXPECT_NE(observer->GetEventType(), static_cast<int32_t>(Recorder::EventType::EXPOSURE));
    Recorder::EventController::Get().Unregister(observer);
}

/**
 * @tc.name: PutString005
 * @tc.desc: Test PutString.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTestTwo, PutString005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize configuration and register observer.
     * @tc.expected: Configuration is loaded and observer is registered.
     */
    auto observer = std::make_shared<DemoUIEventObserver>();
    Recorder::EventController::Get().Register(DEFAULT_CONFIG, observer);
    Recorder::NodeDataCache::Get().OnPageShow("pages/Index");

    /**
     * @tc.steps: step2. Create page node and test PutString with empty ID.
     * @tc.expected: PutString returns false as ID is empty.
     */
    auto pageNode = CreatePageNode("pages/Index");
    Recorder::NodeDataCache::Get().mergedConfig_->shareNodes.clear();
    std::string id = "";
    std::string value = "value";
    bool result = Recorder::NodeDataCache::Get().PutString(pageNode, id, value);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: PutString006
 * @tc.desc: Test PutString.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTestTwo, PutString006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize configuration and register observer.
     * @tc.expected: Configuration is loaded and observer is registered.
     */
    auto observer = std::make_shared<DemoUIEventObserver>();
    Recorder::EventController::Get().Register(DEFAULT_CONFIG, observer);
    Recorder::NodeDataCache::Get().OnPageShow("pages/Index");

    /**
     * @tc.steps: step2. Create page node and test PutString with empty value.
     * @tc.expected: PutString returns false as value is empty.
     */
    auto pageNode = CreatePageNode("pages/Index");
    Recorder::NodeDataCache::Get().mergedConfig_->shareNodes.clear();
    std::string id = "id";
    std::string value = "";
    bool result = Recorder::NodeDataCache::Get().PutString(pageNode, id, value);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: PutString007
 * @tc.desc: Test PutString.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTestTwo, PutString007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize configuration and register observer.
     * @tc.expected: Configuration is loaded and observer is registered.
     */
    auto observer = std::make_shared<DemoUIEventObserver>();
    Recorder::EventController::Get().Register(DEFAULT_CONFIG, observer);
    Recorder::NodeDataCache::Get().OnPageShow("pages/Index");

    /**
     * @tc.steps: step2. Create page node and test PutString with oversized value.
     * @tc.expected: PutString returns false as value exceeds maximum allowed length.
     */
    auto pageNode = CreatePageNode("pages/Index");
    Recorder::NodeDataCache::Get().mergedConfig_->shareNodes.clear();
    std::string id = "id";
    std::string value(101, 'a');
    bool result = Recorder::NodeDataCache::Get().PutString(pageNode, id, value);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: PutString009
 * @tc.desc: Test PutString.
 * @tc.type: FUNC
 */
HWTEST_F(EventRecorderTestTwo, PutString009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize configuration and register observer.
     * @tc.expected: Configuration is loaded and observer is registered.
     */
    auto observer = std::make_shared<DemoUIEventObserver>();
    Recorder::EventController::Get().Register(DEFAULT_CONFIG, observer);
    Recorder::NodeDataCache::Get().OnPageShow("pages/Index");

    /**
     * @tc.steps: step2. Create page node and test PutString with mismatched configuration.
     * @tc.expected: PutString returns false as page node doesn't match configuration.
     */
    auto pageNode = CreatePageNode("123");
    Recorder::NodeDataCache::Get().mergedConfig_->shareNodes["abc"] = { "element1", "element2", "element3" };
    Recorder::NodeDataCache::Get().shouldCollectFull_ = false;
    std::string id = "id";
    std::string value = "value";
    bool result = Recorder::NodeDataCache::Get().PutString(pageNode, id, value);
    EXPECT_FALSE(result);
}
} // namespace OHOS::Ace
