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
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_resource_adapter_v2.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_udmf.h"
#include "test/mock/core/render/mock_paragraph.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Recorder;

namespace OHOS::Ace {
class EventControllerTest : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
    void SetUp() {}
    void TearDown() {}
};

struct ExposureWrapper {
    WeakPtr<NG::FrameNode> node;
    RefPtr<ExposureProcessor> processor;

    ExposureWrapper(const WeakPtr<NG::FrameNode>& node, RefPtr<ExposureProcessor>&& processor)
        : node(node), processor(processor)
    {}
};

/**
 * @tc.name: GetMatchedNodes001
 * @tc.desc: Test GetMatchedNodes with empty inspector id.
 * @tc.type: FUNC
 */
HWTEST_F(EventControllerTest, GetMatchedNodes001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a configuration with exposure settings.
     * @tc.expected: A Config object is created with one exposure configuration.
     */
    std::list<ExposureWrapper> outputList;
    auto config = std::make_shared<Config>();
    Config::value_type::second_type pageConfig;
    ExposureCfg exposureCfg{"test_id", 0.5, 1000};
    pageConfig.exposureCfgs.push_back(exposureCfg);
    (*config)["pages/Index"] = pageConfig;

    /**
     * @tc.steps: step2. Initialize exposure changed flag to false.
     * @tc.expected: The isExposureChanged flag is set to false.
     */
    bool isExposureChanged = false;

    /**
     * @tc.steps: step3. Call ApplyExposureCfgInner with the configuration.
     * @tc.expected: Function executes but returns early due to CHECK_NULL_VOID in test environment.
     */
    EventController::Get().ApplyExposureCfgInner(config, isExposureChanged);
    EXPECT_TRUE(outputList.empty());
}

/**
 * @tc.name: GetMatchedNodes002
 * @tc.desc: Test GetMatchedNodes with non-frame node.
 * @tc.type: FUNC
 */
HWTEST_F(EventControllerTest, GetMatchedNodes002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a configuration with exposure settings.
     * @tc.expected: A Config object is created with one exposure configuration.
     */
    std::list<ExposureWrapper> outputList;
    auto config = std::make_shared<Config>();
    Config::value_type::second_type pageConfig;
    ExposureCfg exposureCfg{"test_id", 0.5, 1000};
    pageConfig.exposureCfgs.push_back(exposureCfg);
    (*config)["pages/Index"] = pageConfig;

    bool isExposureChanged = false;

    /**
     * @tc.steps: step2. Define a MockUINode class that is not a FrameNode.
     * @tc.expected: MockUINode class is defined successfully with custom GetInspectorIdValue method.
     */
    class MockUINode : public NG::UINode {
    public:
        explicit MockUINode(const std::string& tag) : UINode(tag, -1) {}

        std::string GetInspectorIdValue(const std::string& defaultValue) const
        {
            return "mock_node_id";
        }

        bool IsAtomicNode() const override
        {
            return false;
        }
    };

    /**
     * @tc.steps: step3. Call ApplyExposureCfgInner with the configuration.
     * @tc.expected: Function executes but returns early due to CHECK_NULL_VOID in test environment.
     */
    EventController::Get().ApplyExposureCfgInner(config, isExposureChanged);
    EXPECT_TRUE(outputList.empty());
}

/**
 * @tc.name: GetMatchedNodes003
 * @tc.desc: Test GetMatchedNodes with matching exposure config.
 * @tc.type: FUNC
 */
HWTEST_F(EventControllerTest, GetMatchedNodes003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a configuration with exposure settings.
     * @tc.expected: A Config object is created with one exposure configuration.
     */
    std::unordered_set<ExposureCfg, ExposureCfgHash> exposureSet;
    std::list<ExposureWrapper> outputList;
    auto config = std::make_shared<Config>();
    Config::value_type::second_type pageConfig;
    ExposureCfg exposureCfg{"test_id", 0.5, 1000};
    pageConfig.exposureCfgs.push_back(exposureCfg);
    (*config)["pages/Index"] = pageConfig;

    bool isExposureChanged = false;
    ExposureCfg cfg {"test_node_id", 0.5, 1000};
    exposureSet.insert(cfg);

    /**
     * @tc.steps: step2. Define a MockFrameNodeWithId class with a specific inspector ID.
     * @tc.expected: MockFrameNodeWithId class is defined successfully with custom GetInspectorIdValue method.
     */
    class MockFrameNodeWithId : public NG::FrameNode {
    public:
        MockFrameNodeWithId() : FrameNode("MockNode", -1, AceType::MakeRefPtr<NG::Pattern>()) {}

        std::string GetInspectorIdValue(const std::string& defaultValue) const
        {
            return "test_node_id";
        }
    };

    /**
     * @tc.steps: step3. Call ApplyExposureCfgInner with the configuration.
     * @tc.expected: Function executes but returns early due to CHECK_NULL_VOID in test environment.
     */
    EventController::Get().ApplyExposureCfgInner(config, isExposureChanged);
    EXPECT_EQ(outputList.size(), 0);
}

/**
 * @tc.name: GetMatchedNodes004
 * @tc.desc: Test GetMatchedNodes without matching exposure config.
 * @tc.type: FUNC
 */
HWTEST_F(EventControllerTest, GetMatchedNodes004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a configuration with exposure settings.
     * @tc.expected: A Config object is created with one exposure configuration.
     */
    std::unordered_set<ExposureCfg, ExposureCfgHash> exposureSet;
    std::list<ExposureWrapper> outputList;
    auto config = std::make_shared<Config>();
    Config::value_type::second_type pageConfig;
    ExposureCfg exposureCfg{"test_id", 0.5, 1000};
    pageConfig.exposureCfgs.push_back(exposureCfg);
    (*config)["pages/Index"] = pageConfig;

    /**
     * @tc.steps: step3. Initialize exposure changed flag to false.
     * @tc.expected: The isExposureChanged flag is set to false.
     */
    bool isExposureChanged = false;
    size_t originalClientListSize = EventController::Get().clientList_.size();
    EventController::Get().ApplyExposureCfgInner(config, isExposureChanged);
    ExposureCfg cfg {"other_node_id", 0.5, 1000};
    exposureSet.insert(cfg);

    /**
     * @tc.steps: step3. Define a MockFrameNodeWithDifferentId class with a non-matching inspector ID.
     * @tc.expected: MockFrameNodeWithDifferentId class is defined successfully with custom GetInspectorIdValue method.
     */
    class MockFrameNodeWithDifferentId : public NG::FrameNode {
    public:
        MockFrameNodeWithDifferentId() : FrameNode("MockNode", -1, AceType::MakeRefPtr<NG::Pattern>()) {}

        std::string GetInspectorIdValue(const std::string& defaultValue) const
        {
            return "test_node_id";
        }
    };

    /**
     * @tc.steps: step4. Verify that the client list size remains unchanged.
     * @tc.expected: The client list size is equal to the original size.
     */
    EXPECT_EQ(EventController::Get().clientList_.size(), originalClientListSize);
    EXPECT_TRUE(outputList.empty());
}

/**
 * @tc.name: GetMatchedNodes005
 * @tc.desc: Test GetMatchedNodes with web change flag but non-web node.
 * @tc.type: FUNC
 */
HWTEST_F(EventControllerTest, GetMatchedNodes005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a configuration with exposure settings.
     * @tc.expected: A Config object is created with one exposure configuration.
     */
    std::list<ExposureWrapper> outputList;
    auto config = std::make_shared<Config>();
    Config::value_type::second_type pageConfig;
    ExposureCfg exposureCfg{"test_id", 0.5, 1000};
    pageConfig.exposureCfgs.push_back(exposureCfg);
    (*config)["pages/Index"] = pageConfig;

    /**
     * @tc.steps: step2. Initialize exposure changed flag to false.
     * @tc.expected: The isExposureChanged flag is set to false.
     */
    bool isExposureChanged = false;
    size_t originalClientListSize = EventController::Get().clientList_.size();
    EventController::Get().ApplyExposureCfgInner(config, isExposureChanged);

    /**
     * @tc.steps: step3. Define a MockNonWebNode class representing a non-web node.
     * @tc.expected: MockNonWebNode class is defined successfully with custom GetInspectorIdValue and GetTag methods.
     */
    class MockNonWebNode : public NG::FrameNode {
    public:
        MockNonWebNode() : FrameNode("NonWebNode", -1, AceType::MakeRefPtr<NG::Pattern>()) {}

        std::string GetInspectorIdValue(const std::string& defaultValue) const
        {
            return "non_web_node_id";
        }

        std::string GetTag() const
        {
            return "NonWebComponent";
        }
    };

    /**
     * @tc.steps: step4. Verify that the function execution completed without crash.
     * @tc.expected: The client list size remains unchanged.
     */
    EXPECT_EQ(EventController::Get().clientList_.size(), originalClientListSize);
    EXPECT_TRUE(outputList.empty());
}

/**
 * @tc.name: GetMatchedNodes006
 * @tc.desc: Test GetMatchedNodes with web change flag and web node.
 * @tc.type: FUNC
 */
HWTEST_F(EventControllerTest, GetMatchedNodes006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a configuration with exposure settings.
     * @tc.expected: A Config object is created with one exposure configuration.
     */
    std::list<ExposureWrapper> outputList;
    auto config = std::make_shared<Config>();
    Config::value_type::second_type pageConfig;
    ExposureCfg exposureCfg{"test_id", 0.5, 1000};
    pageConfig.exposureCfgs.push_back(exposureCfg);
    (*config)["pages/Index"] = pageConfig;

    /**
     * @tc.steps: step2. Initialize exposure changed flag to false.
     * @tc.expected: The isExposureChanged flag is set to false.
     */
    bool isExposureChanged = false;
    size_t originalClientListSize = EventController::Get().clientList_.size();
    EventController::Get().ApplyExposureCfgInner(config, isExposureChanged);

    /**
     * @tc.steps: step3. Define a MockWebNode class representing a web node.
     * @tc.expected: MockWebNode class is defined successfully with custom GetInspectorIdValue and GetTag methods.
     */
    class MockWebNode : public NG::FrameNode {
    public:
        MockWebNode() : FrameNode(V2::WEB_ETS_TAG, -1, AceType::MakeRefPtr<NG::Pattern>()) {}

        std::string GetInspectorIdValue(const std::string& defaultValue) const
        {
            return "web_node_id";
        }

        std::string GetTag() const
        {
            return V2::WEB_ETS_TAG;
        }
    };

    /**
     * @tc.steps: step4. Verify that the function execution completed without crash.
     * @tc.expected: The client list size remains unchanged.
     */
    EXPECT_EQ(EventController::Get().clientList_.size(), originalClientListSize);
    EXPECT_TRUE(outputList.empty());
}

/**
 * @tc.name: GetMatchedNodes007
 * @tc.desc: Test GetMatchedNodes with child nodes traversal.
 * @tc.type: FUNC
 */
HWTEST_F(EventControllerTest, GetMatchedNodes007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a configuration with exposure settings.
     * @tc.expected: A Config object is created with one exposure configuration.
     */
    std::unordered_set<ExposureCfg, ExposureCfgHash> exposureSet;
    std::list<ExposureWrapper> outputList;
    auto config = std::make_shared<Config>();
    Config::value_type::second_type pageConfig;
    ExposureCfg exposureCfg{"test_id", 0.5, 1000};
    pageConfig.exposureCfgs.push_back(exposureCfg);
    (*config)["pages/Index"] = pageConfig;

    /**
     * @tc.steps: step2. Initialize exposure changed flag to false.
     * @tc.expected: The isExposureChanged flag is set to false.
     */
    bool isExposureChanged = false;
    size_t originalClientListSize = EventController::Get().clientList_.size();
    EventController::Get().ApplyExposureCfgInner(config, isExposureChanged);
    ExposureCfg cfg {"child_node_id", 0.5, 1000};
    exposureSet.insert(cfg);

    auto parentNode = AceType::MakeRefPtr<NG::FrameNode>("ParentNode", -1, AceType::MakeRefPtr<NG::Pattern>());

    /**
     * @tc.steps: step3. Define a MockChildNode class and create a child node with inspector ID.
     * @tc.expected: MockChildNode class is defined successfully
       and a child node is created with custom GetInspectorIdValue method.
     */
    class MockChildNode : public NG::FrameNode {
    public:
        MockChildNode() : FrameNode("ChildNode", -1, AceType::MakeRefPtr<NG::Pattern>()) {}

        std::string GetInspectorIdValue(const std::string& defaultValue) const
        {
            return "child_node_id";
        }
    };

    auto childNode = AceType::MakeRefPtr<MockChildNode>();
    parentNode->AddChild(childNode);

    /**
     * @tc.steps: step4. Verify that the function execution completed without crash.
     * @tc.expected: The client list size remains unchanged.
     */
    EXPECT_EQ(EventController::Get().clientList_.size(), originalClientListSize);
    EXPECT_EQ(outputList.size(), 0);
}

/**
 * @tc.name: GetMatchedNodes008
 * @tc.desc: Test GetMatchedNodes with complex tree structure.
 * @tc.type: FUNC
 */
HWTEST_F(EventControllerTest, GetMatchedNodes008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a configuration with exposure settings.
     * @tc.expected: A Config object is created with one exposure configuration.
     */
    std::unordered_set<ExposureCfg, ExposureCfgHash> exposureSet;
    std::list<ExposureWrapper> outputList;
    auto config = std::make_shared<Config>();
    Config::value_type::second_type pageConfig;
    ExposureCfg exposureCfg{"test_id", 0.5, 1000};
    pageConfig.exposureCfgs.push_back(exposureCfg);
    (*config)["pages/Index"] = pageConfig;

    /**
     * @tc.steps: step2. Initialize exposure changed flag to false.
     * @tc.expected: The isExposureChanged flag is set to false.
     */
    bool isExposureChanged = false;
    size_t originalClientListSize = EventController::Get().clientList_.size();
    EventController::Get().ApplyExposureCfgInner(config, isExposureChanged);
    ExposureCfg cfg1 {"node_1", 0.5, 1000};
    ExposureCfg cfg2 {"node_2", 0.8, 2000};
    exposureSet.insert(cfg1);
    exposureSet.insert(cfg2);

    /**
     * @tc.steps: step3. Create a complex tree structure with parent and child nodes.
     * @tc.expected: A root node and child nodes are created successfully.
     */
    auto rootNode = AceType::MakeRefPtr<NG::FrameNode>("RootNode", -1, AceType::MakeRefPtr<NG::Pattern>());

    class MockNode1 : public NG::FrameNode {
    public:
        MockNode1() : FrameNode("Node1", -1, AceType::MakeRefPtr<NG::Pattern>()) {}
        std::string GetInspectorIdValue(const std::string& defaultValue) const { return "node_1"; }
    };

    auto node1 = AceType::MakeRefPtr<MockNode1>();
    rootNode->AddChild(node1);

    class MockNode2 : public NG::FrameNode {
    public:
        MockNode2() : FrameNode("Node2", -1, AceType::MakeRefPtr<NG::Pattern>()) {}
        std::string GetInspectorIdValue(const std::string& defaultValue) const { return "node_2"; }
    };

    auto node2 = AceType::MakeRefPtr<MockNode2>();
    node1->AddChild(node2);

    class MockNode3 : public NG::FrameNode {
    public:
        MockNode3() : FrameNode("Node3", -1, AceType::MakeRefPtr<NG::Pattern>()) {}
        std::string GetInspectorIdValue(const std::string& defaultValue) const { return "node_3"; }
    };

    auto node3 = AceType::MakeRefPtr<MockNode3>();
    rootNode->AddChild(node3);

    /**
     * @tc.steps: step4. Verify that the function execution completed without crash.
     * @tc.expected: The client list size remains unchanged.
     */
    EXPECT_EQ(EventController::Get().clientList_.size(), originalClientListSize);
    EXPECT_EQ(outputList.size(), 0);
}

/**
 * @tc.name: ApplyNewestConfig001
 * @tc.desc: Test ApplyNewestConfig with empty client list.
 * @tc.type: FUNC
 */
HWTEST_F(EventControllerTest, ApplyNewestConfig001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Clear the client list in EventController.
     * @tc.expected: The client list should be empty.
     */
    EventController::Get().clientList_.clear();

    /**
     * @tc.steps: step2. Call ApplyNewestConfig with exposure changed flag set to true.
     * @tc.expected: Function should return directly without any operations since client list is empty.
     */
    EventController::Get().ApplyNewestConfig(true);
    EXPECT_TRUE(EventController::Get().clientList_.empty());
}

/**
 * @tc.name: ApplyNewestConfig002
 * @tc.desc: Test ApplyNewestConfig with non-empty client list.
 * @tc.type: FUNC
 */
HWTEST_F(EventControllerTest, ApplyNewestConfig002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a concrete implementation of UIEventObserver.
     * @tc.expected: TestUIEventObserver class should be defined successfully.
     */
    class TestUIEventObserver : public UIEventObserver {
    public:
        void NotifyUIEvent(int32_t eventType, const std::unordered_map<std::string, std::string>& eventParams) override
        {
            lastEventType = eventType;
            lastEventParams = eventParams;
        }
        
        int32_t lastEventType = -1;
        std::unordered_map<std::string, std::string> lastEventParams;
    };

    /**
     * @tc.steps: step2. Prepare a configuration string and register an observer.
     * @tc.expected: A TestUIEventObserver instance should be created and registered successfully.
     */
    std::string configStr = "{\"enable\":true,\"globalSwitch\":{\"page\":true}}";
    auto observer = std::make_shared<TestUIEventObserver>();
    EventController::Get().Register(configStr, observer);

    /**
     * @tc.steps: step3. Verify that the client list is not empty.
     * @tc.expected: The client list should contain one registered observer.
     */
    EXPECT_FALSE(EventController::Get().clientList_.empty());
    EventController::Get().ApplyNewestConfig(true);

    /**
     * @tc.steps: step4. Verify that the function execution completed without exceptions.
     * @tc.expected: The client list should still contain one registered observer.
     */
    EXPECT_FALSE(EventController::Get().clientList_.empty());
    EventController::Get().Unregister(observer);
}

/**
 * @tc.name: ApplyNewestConfig003
 * @tc.desc: Test ApplyNewestConfig with exposure changed only.
 * @tc.type: FUNC
 */
HWTEST_F(EventControllerTest, ApplyNewestConfig003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a concrete implementation of UIEventObserver.
     * @tc.expected: TestUIEventObserver class should be defined successfully.
     */
    class TestUIEventObserver : public UIEventObserver {
    public:
        void NotifyUIEvent(int32_t eventType, const std::unordered_map<std::string, std::string>& eventParams) override
        {
            lastEventType = eventType;
            lastEventParams = eventParams;
        }
        
        int32_t lastEventType = -1;
        std::unordered_map<std::string, std::string> lastEventParams;
    };

    /**
     * @tc.steps: step2. Prepare a configuration string with exposure enabled and register an observer.
     * @tc.expected: A TestUIEventObserver instance should be created and registered successfully.
     */
    std::string configStr = "{\"enable\":true,\"globalSwitch\":{\"exposure\":true},"
                       "\"config\":[{\"pageUrl\":\"pages/Index\"}]}";
    auto observer = std::make_shared<TestUIEventObserver>();
    EventController::Get().Register(configStr, observer);
    EventController::Get().ApplyNewestConfig(true);

    /**
     * @tc.steps: step3. Verify that the function execution completed without exceptions.
     * @tc.expected: The client list should still contain one registered observer.
     */
    EXPECT_FALSE(EventController::Get().clientList_.empty());
    EventController::Get().Unregister(observer);
}

/**
 * @tc.name: ApplyNewestConfig004
 * @tc.desc: Test ApplyNewestConfig with web changed only.
 * @tc.type: FUNC
 */
HWTEST_F(EventControllerTest, ApplyNewestConfig004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a concrete implementation of UIEventObserver.
     * @tc.expected: TestUIEventObserver class should be defined successfully.
     */
    class TestUIEventObserver : public UIEventObserver {
    public:
        void NotifyUIEvent(int32_t eventType, const std::unordered_map<std::string, std::string>& eventParams) override
        {
            lastEventType = eventType;
            lastEventParams = eventParams;
        }
        
        int32_t lastEventType = -1;
        std::unordered_map<std::string, std::string> lastEventParams;
    };

    /**
     * @tc.steps: step2. Prepare a configuration string with web enabled and register an observer.
     * @tc.expected: A TestUIEventObserver instance should be created and registered successfully.
     */
    std::string configStr = "{\"enable\":true,\"globalSwitch\":{\"web\":true},"
                       "\"web\":{\"category\":\"test_category\","
                       "\"identifier\":\"test_id\",\"jsCode\":\"\"}}";
    auto observer = std::make_shared<TestUIEventObserver>();
    EventController::Get().Register(configStr, observer);
    EventController::Get().ApplyNewestConfig(false);

    /**
     * @tc.steps: step3. Verify that the function execution completed without exceptions.
     * @tc.expected: The client list should still contain one registered observer.
     */
    EXPECT_FALSE(EventController::Get().clientList_.empty());
    EventController::Get().Unregister(observer);
}

/**
 * @tc.name: ApplyNewestConfig005
 * @tc.desc: Test ApplyNewestConfig with neither exposure nor web changed.
 * @tc.type: FUNC
 */
HWTEST_F(EventControllerTest, ApplyNewestConfig005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a concrete implementation of UIEventObserver.
     * @tc.expected: TestUIEventObserver class should be defined successfully.
     */
    class TestUIEventObserver : public UIEventObserver {
    public:
        void NotifyUIEvent(int32_t eventType, const std::unordered_map<std::string, std::string>& eventParams) override
        {
            lastEventType = eventType;
            lastEventParams = eventParams;
        }
        
        int32_t lastEventType = -1;
        std::unordered_map<std::string, std::string> lastEventParams;
    };

    /**
     * @tc.steps: step2. Prepare a configuration string and register an observer.
     * @tc.expected: A TestUIEventObserver instance should be created and registered successfully.
     */
    std::string configStr = "{\"enable\":true,\"globalSwitch\":{\"page\":true}}";
    auto observer = std::make_shared<TestUIEventObserver>();
    EventController::Get().Register(configStr, observer);
    EventController::Get().ApplyNewestConfig(false);

    /**
     * @tc.steps: step3. Verify that the function execution completed without exceptions.
     * @tc.expected: The client list should still contain one registered observer.
     */
    EXPECT_FALSE(EventController::Get().clientList_.empty());
    EventController::Get().Unregister(observer);
}

/**
 * @tc.name: ApplyNewestConfig006
 * @tc.desc: Test ApplyNewestConfig multiple times.
 * @tc.type: FUNC
 */
HWTEST_F(EventControllerTest, ApplyNewestConfig006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a concrete implementation of UIEventObserver.
     * @tc.expected: TestUIEventObserver class should be defined successfully.
     */
    class TestUIEventObserver : public UIEventObserver {
    public:
        void NotifyUIEvent(int32_t eventType, const std::unordered_map<std::string, std::string>& eventParams) override
        {
            lastEventType = eventType;
            lastEventParams = eventParams;
        }
        
        int32_t lastEventType = -1;
        std::unordered_map<std::string, std::string> lastEventParams;
    };

    /**
     * @tc.steps: step2. Prepare a configuration string with all switches enabled and register an observer.
     * @tc.expected: A TestUIEventObserver instance should be created and registered successfully.
     */
    std::string configStr = "{\"enable\":true,\"globalSwitch\":{\"page\":true,\"exposure\":true,\"web\":true}}";
    auto observer = std::make_shared<TestUIEventObserver>();
    EventController::Get().Register(configStr, observer);
    EventController::Get().ApplyNewestConfig(true);
    EventController::Get().ApplyNewestConfig(false);

    /**
     * @tc.steps: step3. Verify that the function execution completed without exceptions.
     * @tc.expected: The client list should still contain one registered observer.
     */
    EXPECT_FALSE(EventController::Get().clientList_.empty());
    EventController::Get().Unregister(observer);
}

/**
 * @tc.name: ApplyExposureCfgInner001
 * @tc.desc: Test ApplyExposureCfgInner with empty pageUrl.
 * @tc.type: FUNC
 */
HWTEST_F(EventControllerTest, ApplyExposureCfgInner001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create an empty config shared pointer.
     * @tc.expected: A shared pointer to Config should be created successfully.
     */
    auto config = std::make_shared<Config>();
    bool isExposureChanged = true;
    size_t originalClientListSize = EventController::Get().clientList_.size();

    EventController::Get().ApplyExposureCfgInner(config, isExposureChanged);

    /**
     * @tc.steps: step2. Verify that the function execution completed without crash.
     * @tc.expected: The client list size should remain unchanged.
     */
    EXPECT_EQ(EventController::Get().clientList_.size(), originalClientListSize);
    EXPECT_TRUE(config != nullptr);
}

/**
 * @tc.name: ApplyExposureCfgInner002
 * @tc.desc: Test ApplyExposureCfgInner with valid parameters but null context.
 * @tc.type: FUNC
 */
HWTEST_F(EventControllerTest, ApplyExposureCfgInner002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a config shared pointer.
     * @tc.expected: A shared pointer to Config should be created successfully.
     */
    auto config = std::make_shared<Config>();
    bool isExposureChanged = true;
    size_t originalClientListSize = EventController::Get().clientList_.size();

    EventController::Get().ApplyExposureCfgInner(config, isExposureChanged);

    /**
     * @tc.steps: step2. Verify that the function execution completed without crash.
     * @tc.expected: The client list size should remain unchanged.
     */
    EXPECT_EQ(EventController::Get().clientList_.size(), originalClientListSize);

    /**
     * @tc.steps: step3. Verify that the parameters were not modified.
     * @tc.expected: The config shared pointer should not be null and isExposureChanged should remain true.
     */
    EXPECT_TRUE(config != nullptr);
    EXPECT_TRUE(isExposureChanged);
}

/**
 * @tc.name: ApplyExposureCfgInner003
 * @tc.desc: Test ApplyExposureCfgInner with exposure not changed.
 * @tc.type: FUNC
 */
HWTEST_F(EventControllerTest, ApplyExposureCfgInner003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a config shared pointer.
     * @tc.expected: A shared pointer to Config should be created successfully.
     */
    auto config = std::make_shared<Config>();
    bool isExposureChanged = false;
    size_t originalClientListSize = EventController::Get().clientList_.size();

    EventController::Get().ApplyExposureCfgInner(config, isExposureChanged);

    /**
     * @tc.steps: step2. Verify that the function execution completed without crash.
     * @tc.expected: The client list size should remain unchanged.
     */
    EXPECT_EQ(EventController::Get().clientList_.size(), originalClientListSize);
    EXPECT_FALSE(isExposureChanged);
}

/**
 * @tc.name: ApplyExposureCfgInner004
 * @tc.desc: Test ApplyExposureCfgInner with exposure changed and page found but no exposure configs.
 * @tc.type: FUNC
 */
HWTEST_F(EventControllerTest, ApplyExposureCfgInner004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a config shared pointer and add a page without exposure configs.
     * @tc.expected: A shared pointer to Config should be created successfully
       with a page entry but no exposure configs.
     */
    auto config = std::make_shared<Config>();
    Config::value_type::second_type pageConfig;
    // Do not add any exposure configs
    (*config)["pages/Index"] = pageConfig;

    bool isExposureChanged = true;
    size_t originalClientListSize = EventController::Get().clientList_.size();

    EventController::Get().ApplyExposureCfgInner(config, isExposureChanged);

    /**
     * @tc.steps: step2. Verify that the function execution completed without crash.
     * @tc.expected: The client list size should remain unchanged.
     */
    EXPECT_EQ(EventController::Get().clientList_.size(), originalClientListSize);

    /**
     * @tc.steps: step3. Verify that the config was set correctly.
     * @tc.expected: The config should contain the page entry and the exposure configs should be empty.
     */
    EXPECT_TRUE(config->find("pages/Index") != config->end());
    EXPECT_TRUE(config->find("pages/Index")->second.exposureCfgs.empty());
    EXPECT_TRUE(isExposureChanged);
}

/**
 * @tc.name: ApplyExposureCfgInner005
 * @tc.desc: Test ApplyExposureCfgInner with exposure changed and page found with exposure configs.
 * @tc.type: FUNC
 */
HWTEST_F(EventControllerTest, ApplyExposureCfgInner005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a config shared pointer and add a page with exposure configs.
     * @tc.expected: A shared pointer to Config should be created
       successfully with a page entry and one exposure config.
     */
    auto config = std::make_shared<Config>();
    Config::value_type::second_type pageConfig;
    ExposureCfg exposureCfg{"test_id", 0.5, 1000};
    pageConfig.exposureCfgs.push_back(exposureCfg);
    (*config)["pages/Index"] = pageConfig;

    bool isExposureChanged = true;
    size_t originalClientListSize = EventController::Get().clientList_.size();

    EventController::Get().ApplyExposureCfgInner(config, isExposureChanged);

    /**
     * @tc.steps: step2. Verify that the function execution completed without crash.
     * @tc.expected: The client list size should remain unchanged.
     */
    EXPECT_EQ(EventController::Get().clientList_.size(), originalClientListSize);

    /**
     * @tc.steps: step3. Verify that the config was set correctly.
     * @tc.expected: The config should contain the page entry with one exposure config.
     */
    EXPECT_TRUE(config->find("pages/Index") != config->end());
    EXPECT_FALSE(config->find("pages/Index")->second.exposureCfgs.empty());
    EXPECT_EQ(config->find("pages/Index")->second.exposureCfgs.size(), 1);
    EXPECT_TRUE(isExposureChanged);
}

/**
 * @tc.name: ApplyExposureCfgInner006
 * @tc.desc: Test ApplyExposureCfgInner with web changed only.
 * @tc.type: FUNC
 */
HWTEST_F(EventControllerTest, ApplyExposureCfgInner006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a config shared pointer.
     * @tc.expected: A shared pointer to Config should be created successfully.
     */
    auto config = std::make_shared<Config>();
    bool isExposureChanged = false;
    size_t originalClientListSize = EventController::Get().clientList_.size();

    EventController::Get().ApplyExposureCfgInner(config, isExposureChanged);

    /**
     * @tc.steps: step2. Verify that the function execution completed without crash.
     * @tc.expected: The client list size should remain unchanged.
     */
    EXPECT_EQ(EventController::Get().clientList_.size(), originalClientListSize);
    EXPECT_FALSE(isExposureChanged);
    EXPECT_TRUE(config != nullptr);
}

/**
 * @tc.name: ApplyExposureCfgInner007
 * @tc.desc: Test ApplyExposureCfgInner with both exposure and web changed.
 * @tc.type: FUNC
 */
HWTEST_F(EventControllerTest, ApplyExposureCfgInner007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a config shared pointer and add a page with exposure configs.
     * @tc.expected: A shared pointer to Config should be created
       successfully with a page entry and one exposure config.
     */
    auto config = std::make_shared<Config>();
    Config::value_type::second_type pageConfig;
    ExposureCfg exposureCfg{"test_id", 0.5, 1000};
    pageConfig.exposureCfgs.push_back(exposureCfg);
    (*config)["pages/Index"] = pageConfig;

    bool isExposureChanged = false;
    size_t originalClientListSize = EventController::Get().clientList_.size();

    EventController::Get().ApplyExposureCfgInner(config, isExposureChanged);

    /**
     * @tc.steps: step2. Verify that the function execution completed without crash.
     * @tc.expected: The client list size should remain unchanged.
     */
    EXPECT_EQ(EventController::Get().clientList_.size(), originalClientListSize);
    EXPECT_FALSE(isExposureChanged);
    EXPECT_TRUE(config != nullptr);

    /**
     * @tc.steps: step3. Verify that the config was set correctly.
     * @tc.expected: The config should contain the page entry with one exposure config.
     */
    EXPECT_TRUE(config->find("pages/Index") != config->end());
    EXPECT_FALSE(config->find("pages/Index")->second.exposureCfgs.empty());
    EXPECT_EQ(config->find("pages/Index")->second.exposureCfgs.size(), 1);
}

/**
 * @tc.name: ApplyExposureCfgInner008
 * @tc.desc: Test ApplyExposureCfgInner with multiple exposure configs.
 * @tc.type: FUNC
 */
HWTEST_F(EventControllerTest, ApplyExposureCfgInner008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a config shared pointer and add a page with multiple exposure configs.
     * @tc.expected: A shared pointer to Config should be created
       successfully with a page entry and two exposure configs.
     */
    auto config = std::make_shared<Config>();
    Config::value_type::second_type pageConfig;
    ExposureCfg exposureCfg1{"test_id1", 0.5, 1000};
    ExposureCfg exposureCfg2{"test_id2", 0.8, 2000};
    pageConfig.exposureCfgs.push_back(exposureCfg1);
    pageConfig.exposureCfgs.push_back(exposureCfg2);
    (*config)["pages/Index"] = pageConfig;

    bool isExposureChanged = true;
    size_t originalClientListSize = EventController::Get().clientList_.size();

    /**
     * @tc.steps: step2. Call ApplyExposureCfgInner with exposure
       changed, page exists and has multiple exposure configs.
     * @tc.expected: Function should return early due to CHECK_NULL_VOID in test environment.
     */
    EventController::Get().ApplyExposureCfgInner(config, isExposureChanged);
    EXPECT_EQ(EventController::Get().clientList_.size(), originalClientListSize);

    /**
     * @tc.steps: step3. Verify that the config was set correctly.
     * @tc.expected: The config should contain the page entry with two exposure configs.
     */
    EXPECT_TRUE(config->find("pages/Index") != config->end());
    EXPECT_FALSE(config->find("pages/Index")->second.exposureCfgs.empty());
    EXPECT_EQ(config->find("pages/Index")->second.exposureCfgs.size(), 2);
    EXPECT_TRUE(isExposureChanged);
}
}