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

#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_FOLDER_STACK_TEST_NG_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_FOLDER_STACK_TEST_NG_H

#include "gtest/gtest.h"

#define protected public
#define private public

#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/pattern/folder_stack/folder_stack_model_ng.h"
#include "core/components_ng/pattern/folder_stack/folder_stack_layout_property.h"
#include "core/components_ng/pattern/folder_stack/folder_stack_event_hub.h"
#include "core/components_ng/pattern/folder_stack/folder_stack_group_node.h"
#include "core/components_ng/pattern/folder_stack/folder_stack_pattern.h"
#include "core/components_ng/pattern/folder_stack/control_parts_stack_node.h"
#include "core/components_ng/pattern/folder_stack/hover_stack_node.h"
#include "core/components_ng/pattern/folder_stack/folder_stack_layout_algorithm.h"
#include "./mock/mock_folder_stack_layout_algorithm.h"

namespace OHOS::Ace::NG {
class FolderStackTestNG : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();

    void Create(const std::vector<std::string>& itemId,
        const std::function<void(FolderStackModelNG model)>& callback = nullptr);
    void AddChildNodeToGroup(const std::vector<std::string>& label, const std::vector<std::string>& inspectorIds);
    void GetInstance();
    void SetUp();
    void TearDown();

protected:
    RefPtr<UINode> CreateWithItem(bool enableAnimation, bool autoHalfFold, Alignment align);
    PaddingProperty CreatePadding(float left, float top, float right, float bottom);
    RefPtr<FolderStackGroupNode> frameNode_;
    RefPtr<FolderStackPattern> pattern_;
    RefPtr<FolderStackEventHub> eventHub_;
    RefPtr<FolderStackLayoutProperty> layoutProperty_;
    RefPtr<ControlPartsStackNode> controlPartsStackNode_;
    RefPtr<HoverStackNode> hoverNode_;
    RefPtr<MockFolderStackLayoutAlgorithm> mockFolderStackLayoutAlgorithm_;
};
}
#endif
