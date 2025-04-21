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

#ifndef TEST_UNITTEST_CORE_EVENT_REQUEST_FOCUS_TEST_H
#define TEST_UNITTEST_CORE_EVENT_REQUEST_FOCUS_TEST_H
#include <cstddef>
#include <cstdint>

#include "gtest/gtest.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/event/focus_core/focus_test_base.h"
#include "test/unittest/core/event/frame_node_on_tree.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/theme/app_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/event/touch_event.h"
#include "core/components_ng/manager/focus/focus_view.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/key_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

struct LinearFocusingCase {
    std::string goFocusStartPoint;
    bool isGoFocusActivityStatus;
    bool isConfigurationTabindexNode;
    bool isBrotherNodeGetFocus;
    bool isChildNodeGetFocus;
    std::string inputValue;
    std::string expectResults;
    LinearFocusingCase(const std::string& goFocusStartPoint, bool isGoFocusActivityStatus,
        bool isConfigurationTabindexNode, bool isBrotherNodeGetFocus, bool isChildNodeGetFocus,
        const std::string& inputValue, const std::string& expectResults)
        : goFocusStartPoint(goFocusStartPoint), isGoFocusActivityStatus(isGoFocusActivityStatus),
          isConfigurationTabindexNode(isConfigurationTabindexNode), isBrotherNodeGetFocus(isBrotherNodeGetFocus),
          isChildNodeGetFocus(isChildNodeGetFocus), inputValue(inputValue), expectResults(expectResults)
    {}
};
struct LinearFocusingDirectCase {
    std::string goFocusStartPoint;
    bool isGoFocusActivityStatus;
    bool isparentCanDealCurrentOperation;
    bool isBrotherNodeGetFocus;
    bool isChildNodeGetFocus;
    std::string inputValue;
    std::string expectResults;
    LinearFocusingDirectCase(const std::string& goFocusStartPoint, bool isGoFocusActivityStatus,
        bool isparentCanDealCurrentOperation, bool isBrotherNodeGetFocus, bool isChildNodeGetFocus,
        const std::string& inputValue, const std::string& expectResults)
        : goFocusStartPoint(goFocusStartPoint), isGoFocusActivityStatus(isGoFocusActivityStatus),
          isparentCanDealCurrentOperation(isparentCanDealCurrentOperation),
          isBrotherNodeGetFocus(isBrotherNodeGetFocus), isChildNodeGetFocus(isChildNodeGetFocus),
          inputValue(inputValue), expectResults(expectResults)
    {}
};

struct LinearFocusingHomeCase {
    std::string goFocusStartPoint;
    bool isGoFocusActivityStatus;
    bool isparentNodeHandleLeftRightFocus;
    bool isparentNodeHandleUpOrDownFocus;
    std::string inputValue;
    std::string expectResults;
    LinearFocusingHomeCase(const std::string& goFocusStartPoint, bool isGoFocusActivityStatus,
        bool isparentNodeHandleLeftRightFocus, bool isparentNodeHandleUpOrDownFocus, const std::string& inputValue,
        const std::string& expectResults)
        : goFocusStartPoint(goFocusStartPoint), isGoFocusActivityStatus(isGoFocusActivityStatus),
          isparentNodeHandleLeftRightFocus(isparentNodeHandleLeftRightFocus),
          isparentNodeHandleUpOrDownFocus(isparentNodeHandleUpOrDownFocus), inputValue(inputValue),
          expectResults(expectResults)
    {}
};
const std::vector<LinearFocusingCase> LINEAR_FOCUSING_CASES = { LinearFocusingCase(
    { "A", true, false, false, false, "Tab走焦", "A" }) };

const std::vector<LinearFocusingDirectCase> LINEAR_FOCUSING_DIRECT_CASES = { LinearFocusingDirectCase(
    { "B", false, false, false, false, "上键走焦", "B" }) };

const std::vector<LinearFocusingHomeCase> LINEAR_FOCUSING_HOME_CASES = { LinearFocusingHomeCase(
    { "C", false, false, false, "HOME键走焦", "C" }) };

class LinearFocusingTestNG : public FocusTestBaseNg, public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void CreatNodeHandleUpDownFocus(int caseNum, const LinearFocusingHomeCase& testCase);
    void CreatNodeHandleLeftRightFocus(int caseNum, const LinearFocusingHomeCase& testCase);
    void HomeOrTabFocus(int caseNum, const LinearFocusingCase& testCase, RefPtr<FocusHub> focusHub);
    void HomeOrTabFocusExpect(int caseNum, const LinearFocusingCase& testCase, RefPtr<FocusHub> focusHub);
    void Test02Focus(int caseNum, const LinearFocusingDirectCase& testCase, RefPtr<FocusHub> focusHub);
    void Test02FocusExpect(int caseNum, const LinearFocusingDirectCase& testCase, RefPtr<FocusHub> focusHub);
    void HandleFocusAndExecuteTest(int32_t caseNum, const LinearFocusingDirectCase& testCase,
        RefPtr<FocusHub> focusHubB, RefPtr<FocusHub> focusHubC, RefPtr<FocusHub> focusHubD, RefPtr<FocusHub> focusHubE,
        RefPtr<FocusHub> focusHubF);
    void CreateAndInitNodes(RefPtr<FrameNode>& rootNode, RefPtr<FocusHub>& rootNodeFocusHub, RefPtr<FrameNode>& nodeA,
        RefPtr<FocusHub>& focusHubA, RefPtr<FrameNode>& nodeB, RefPtr<FocusHub>& focusHubB, RefPtr<FrameNode>& nodeC,
        RefPtr<FocusHub>& focusHubC, RefPtr<FrameNode>& nodeD, RefPtr<FocusHub>& focusHubD, RefPtr<FrameNode>& nodeE,
        RefPtr<FocusHub>& focusHubE, RefPtr<FrameNode>& nodeF, RefPtr<FocusHub>& focusHubF);
};
} // namespace OHOS::Ace::NG

#endif