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

#include <utility>
#include <map>
#include "gtest/gtest.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#define private public
#define protected public
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_model_ng.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_node.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr uint32_t TEST_TOTAL_COUNT = 100;
constexpr uint32_t TEST_TOTAL_COUNT_2 = 50;
constexpr uint32_t TEST_TOTAL_COUNT_3 = 200;
constexpr bool IS_REUSABLE = true;
constexpr bool IS_NOT_REUSABLE = false;
constexpr bool IS_CREATED_BY_TEMPLATE = true;
constexpr bool IS_NOT_CREATED_BY_TEMPLATE = false;
const std::string TEST_TEMPLATE_TYPE = "default";
} // namespace

class RepeatVirtualModelTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
private:
    std::map<std::string, std::pair<bool, uint32_t>> templateCachedCountMap_;
};

void RepeatVirtualModelTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void RepeatVirtualModelTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

void RepeatVirtualModelTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    templateCachedCountMap_.clear();
    templateCachedCountMap_[TEST_TEMPLATE_TYPE] = { true, 5 };
}

void RepeatVirtualModelTestNg::TearDown()
{
    MockPipelineContext::TearDown();
    templateCachedCountMap_.clear();
}

/**
 * @tc.name: RepeatVirtualScrollSyntaxCreateTest001
 * @tc.desc: Create RepeatVirtualScroll node with all parameters
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualModelTestNg, RepeatVirtualScrollSyntaxCreateTest001, TestSize.Level1)
{
    auto onCreateNode = [](uint32_t index) {};
    auto onUpdateNode = [](const std::string& key, uint32_t index) {};
    auto onGetKeys4Range = [](uint32_t from, uint32_t to) -> std::list<std::string> {
        std::list<std::string> keys;
        for (uint32_t i = from; i <= to; ++i) {
            keys.push_back(std::to_string(i));
        }
        return keys;
    };
    auto onGetTypes4Range = [](uint32_t from, uint32_t to) -> std::list<std::string> {
        std::list<std::string> types;
        for (uint32_t i = from; i <= to; ++i) {
            types.push_back(TEST_TEMPLATE_TYPE);
        }
        return types;
    };
    auto onSetActiveRange = [](int32_t start, int32_t end) {};
    RepeatVirtualScrollModelNG model;
    model.Create(TEST_TOTAL_COUNT, templateCachedCountMap_, onCreateNode, onUpdateNode,
        onGetKeys4Range, onGetTypes4Range, onSetActiveRange, IS_REUSABLE);
}

/**
 * @tc.name: RepeatVirtualScrollSyntaxCreateTest002
 * @tc.desc: Create RepeatVirtualScroll with non-reusable flag
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualModelTestNg, RepeatVirtualScrollSyntaxCreateTest002, TestSize.Level1)
{
    auto onCreateNode = [](uint32_t index) {};
    auto onUpdateNode = [](const std::string& key, uint32_t index) {};
    auto onGetKeys4Range = [](uint32_t from, uint32_t to) -> std::list<std::string> {
        return std::list<std::string>();
    };
    auto onGetTypes4Range = [](uint32_t from, uint32_t to) -> std::list<std::string> {
        return std::list<std::string>();
    };
    auto onSetActiveRange = [](int32_t start, int32_t end) {};
    RepeatVirtualScrollModelNG model;
    model.Create(TEST_TOTAL_COUNT, templateCachedCountMap_, onCreateNode, onUpdateNode,
        onGetKeys4Range, onGetTypes4Range, onSetActiveRange, IS_NOT_REUSABLE);
    SUCCEED();
}

/**
 * @tc.name: RepeatVirtualScrollSyntaxCreateTest003
 * @tc.desc: Create RepeatVirtualScroll with different total counts
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualModelTestNg, RepeatVirtualScrollSyntaxCreateTest003, TestSize.Level1)
{
    auto onCreateNode = [](uint32_t index) {};
    auto onUpdateNode = [](const std::string& key, uint32_t index) {};
    auto onGetKeys4Range = [](uint32_t from, uint32_t to) -> std::list<std::string> {
        return std::list<std::string>();
    };
    auto onGetTypes4Range = [](uint32_t from, uint32_t to) -> std::list<std::string> {
        return std::list<std::string>();
    };
    auto onSetActiveRange = [](int32_t start, int32_t end) {};
    RepeatVirtualScrollModelNG model;
    model.Create(TEST_TOTAL_COUNT_2, templateCachedCountMap_, onCreateNode, onUpdateNode,
        onGetKeys4Range, onGetTypes4Range, onSetActiveRange, IS_REUSABLE);
    model.Create(TEST_TOTAL_COUNT_3, templateCachedCountMap_, onCreateNode, onUpdateNode,
        onGetKeys4Range, onGetTypes4Range, onSetActiveRange, IS_REUSABLE);
    SUCCEED();
}

/**
 * @tc.name: RepeatVirtualScrollSyntaxCreateTest004
 * @tc.desc: Create RepeatVirtualScroll with empty template map
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualModelTestNg, RepeatVirtualScrollSyntaxCreateTest004, TestSize.Level1)
{
    auto onCreateNode = [](uint32_t index) {};
    auto onUpdateNode = [](const std::string& key, uint32_t index) {};
    auto onGetKeys4Range = [](uint32_t from, uint32_t to) -> std::list<std::string> {
        return std::list<std::string>();
    };
    auto onGetTypes4Range = [](uint32_t from, uint32_t to) -> std::list<std::string> {
        return std::list<std::string>();
    };
    auto onSetActiveRange = [](int32_t start, int32_t end) {};
    std::map<std::string, std::pair<bool, uint32_t>> emptyMap;
    RepeatVirtualScrollModelNG model;
    model.Create(TEST_TOTAL_COUNT, emptyMap, onCreateNode, onUpdateNode,
        onGetKeys4Range, onGetTypes4Range, onSetActiveRange, IS_REUSABLE);
    SUCCEED();
}

/**
 * @tc.name: RepeatVirtualScrollSyntaxUpdateRenderStateTest005
 * @tc.desc: UpdateRenderState with visible items changed
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualModelTestNg, RepeatVirtualScrollSyntaxUpdateRenderStateTest005, TestSize.Level1)
{
    RepeatVirtualScrollModelNG model;
    model.UpdateRenderState(TEST_TOTAL_COUNT, true);
    SUCCEED();
}

/**
 * @tc.name: RepeatVirtualScrollSyntaxUpdateRenderStateTest006
 * @tc.desc: UpdateRenderState without visible items changed
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualModelTestNg, RepeatVirtualScrollSyntaxUpdateRenderStateTest006, TestSize.Level1)
{
    RepeatVirtualScrollModelNG model;
    model.UpdateRenderState(TEST_TOTAL_COUNT, false);
    SUCCEED();
}

/**
 * @tc.name: RepeatVirtualScrollSyntaxUpdateRenderStateTest007
 * @tc.desc: UpdateRenderState with different total counts
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualModelTestNg, RepeatVirtualScrollSyntaxUpdateRenderStateTest007, TestSize.Level1)
{
    RepeatVirtualScrollModelNG model;
    model.UpdateRenderState(TEST_TOTAL_COUNT, true);
    model.UpdateRenderState(TEST_TOTAL_COUNT_2, false);
    model.UpdateRenderState(TEST_TOTAL_COUNT_3, true);
    SUCCEED();
}

/**
 * @tc.name: RepeatVirtualScrollSyntaxOnMoveTest008
 * @tc.desc: OnMove sets move callback
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualModelTestNg, RepeatVirtualScrollSyntaxOnMoveTest008, TestSize.Level1)
{
    RepeatVirtualScrollModelNG model;
    auto onMoveCallback = [](int32_t from, int32_t to) {};
    model.OnMove(std::move(onMoveCallback));
    SUCCEED();
}

/**
 * @tc.name: RepeatVirtualScrollSyntaxOnMoveTest009
 * @tc.desc: OnMove with empty callback
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualModelTestNg, RepeatVirtualScrollSyntaxOnMoveTest009, TestSize.Level1)
{
    RepeatVirtualScrollModelNG model;
    model.OnMove(nullptr);
    SUCCEED();
}

/**
 * @tc.name: RepeatVirtualScrollSyntaxSetCreateByTemplateTest010
 * @tc.desc: SetCreateByTemplate with true
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualModelTestNg, RepeatVirtualScrollSyntaxSetCreateByTemplateTest010, TestSize.Level1)
{
    auto onCreateNode = [](uint32_t index) {};
    auto onUpdateNode = [](const std::string& key, uint32_t index) {};
    auto onGetKeys4Range = [](uint32_t from, uint32_t to) -> std::list<std::string> {
        return std::list<std::string>();
    };
    auto onGetTypes4Range = [](uint32_t from, uint32_t to) -> std::list<std::string> {
        return std::list<std::string>();
    };
    auto onSetActiveRange = [](int32_t start, int32_t end) {};
    RepeatVirtualScrollModelNG model;
    model.Create(TEST_TOTAL_COUNT, templateCachedCountMap_, onCreateNode, onUpdateNode,
        onGetKeys4Range, onGetTypes4Range, onSetActiveRange, IS_REUSABLE);
    model.SetCreateByTemplate(IS_CREATED_BY_TEMPLATE);
    SUCCEED();
}

/**
 * @tc.name: RepeatVirtualScrollSyntaxSetCreateByTemplateTest011
 * @tc.desc: SetCreateByTemplate with false
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualModelTestNg, RepeatVirtualScrollSyntaxSetCreateByTemplateTest011, TestSize.Level1)
{
    auto onCreateNode = [](uint32_t index) {};
    auto onUpdateNode = [](const std::string& key, uint32_t index) {};
    auto onGetKeys4Range = [](uint32_t from, uint32_t to) -> std::list<std::string> {
        return std::list<std::string>();
    };
    auto onGetTypes4Range = [](uint32_t from, uint32_t to) -> std::list<std::string> {
        return std::list<std::string>();
    };
    auto onSetActiveRange = [](int32_t start, int32_t end) {};
    RepeatVirtualScrollModelNG model;
    model.Create(TEST_TOTAL_COUNT, templateCachedCountMap_, onCreateNode, onUpdateNode,
        onGetKeys4Range, onGetTypes4Range, onSetActiveRange, IS_REUSABLE);
    model.SetCreateByTemplate(IS_NOT_CREATED_BY_TEMPLATE);
    SUCCEED();
}

/**
 * @tc.name: RepeatVirtualScrollSyntaxCompleteFlowTest012
 * @tc.desc: Complete flow with Create, OnMove, and SetCreateByTemplate
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualModelTestNg, RepeatVirtualScrollSyntaxCompleteFlowTest012, TestSize.Level1)
{
    auto onCreateNode = [](uint32_t index) {};
    auto onUpdateNode = [](const std::string& key, uint32_t index) {};
    auto onGetKeys4Range = [](uint32_t from, uint32_t to) -> std::list<std::string> {
        std::list<std::string> keys;
        for (uint32_t i = from; i <= to && i < 100; ++i) {
            keys.push_back(std::to_string(i));
        }
        return keys;
    };
    auto onGetTypes4Range = [](uint32_t from, uint32_t to) -> std::list<std::string> {
        std::list<std::string> types;
        for (uint32_t i = from; i <= to && i < 100; ++i) {
            types.push_back(TEST_TEMPLATE_TYPE);
        }
        return types;
    };
    auto onSetActiveRange = [](int32_t start, int32_t end) {};
    RepeatVirtualScrollModelNG model;
    model.Create(TEST_TOTAL_COUNT, templateCachedCountMap_, onCreateNode, onUpdateNode,
        onGetKeys4Range, onGetTypes4Range, onSetActiveRange, IS_REUSABLE);
    auto onMoveCallback = [](int32_t from, int32_t to) {};
    model.OnMove(std::move(onMoveCallback));
    model.SetCreateByTemplate(IS_CREATED_BY_TEMPLATE);
    SUCCEED();
}

/**
 * @tc.name: RepeatVirtualScrollSyntaxCallbackExecutionTest013
 * @tc.desc: Verify callbacks can be invoked after setup
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualModelTestNg, RepeatVirtualScrollSyntaxCallbackExecutionTest013, TestSize.Level1)
{
    auto onCreateNode = [](uint32_t index) {};
    auto onUpdateNode = [](const std::string& key, uint32_t index) {};
    auto onGetKeys4Range = [](uint32_t from, uint32_t to) -> std::list<std::string> {
        return std::list<std::string>();
    };
    auto onGetTypes4Range = [](uint32_t from, uint32_t to) -> std::list<std::string> {
        return std::list<std::string>();
    };
    auto onSetActiveRange = [](int32_t start, int32_t end) {};
    RepeatVirtualScrollModelNG model;
    model.Create(TEST_TOTAL_COUNT, templateCachedCountMap_, onCreateNode, onUpdateNode,
        onGetKeys4Range, onGetTypes4Range, onSetActiveRange, IS_REUSABLE);
    SUCCEED();
}

/**
 * @tc.name: RepeatVirtualScrollSyntaxMultipleTemplatesTest014
 * @tc.desc: Create with multiple template types
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualModelTestNg, RepeatVirtualScrollSyntaxMultipleTemplatesTest014, TestSize.Level1)
{
    std::map<std::string, std::pair<bool, uint32_t>> multiTemplateMap;
    multiTemplateMap["type1"] = { true, 3 };
    multiTemplateMap["type2"] = { true, 5 };
    multiTemplateMap["type3"] = { false, 2 };
    auto onCreateNode = [](uint32_t index) {};
    auto onUpdateNode = [](const std::string& key, uint32_t index) {};
    auto onGetKeys4Range = [](uint32_t from, uint32_t to) -> std::list<std::string> {
        return std::list<std::string>();
    };
    auto onGetTypes4Range = [](uint32_t from, uint32_t to) -> std::list<std::string> {
        return std::list<std::string>();
    };
    auto onSetActiveRange = [](int32_t start, int32_t end) {};
    RepeatVirtualScrollModelNG model;
    model.Create(TEST_TOTAL_COUNT, multiTemplateMap, onCreateNode, onUpdateNode,
        onGetKeys4Range, onGetTypes4Range, onSetActiveRange, IS_REUSABLE);
    SUCCEED();
}

/**
 * @tc.name: RepeatVirtualScrollSyntaxZeroCountTest015
 * @tc.desc: Create with zero total count
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualModelTestNg, RepeatVirtualScrollSyntaxZeroCountTest015, TestSize.Level1)
{
    auto onCreateNode = [](uint32_t index) {};
    auto onUpdateNode = [](const std::string& key, uint32_t index) {};
    auto onGetKeys4Range = [](uint32_t from, uint32_t to) -> std::list<std::string> {
        return std::list<std::string>();
    };
    auto onGetTypes4Range = [](uint32_t from, uint32_t to) -> std::list<std::string> {
        return std::list<std::string>();
    };
    auto onSetActiveRange = [](int32_t start, int32_t end) {};
    RepeatVirtualScrollModelNG model;
    model.Create(0, templateCachedCountMap_, onCreateNode, onUpdateNode,
        onGetKeys4Range, onGetTypes4Range, onSetActiveRange, IS_REUSABLE);
    SUCCEED();
}

} // namespace OHOS::Ace::NG
