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
#ifndef TEST_UNITTEST_CORE_MANAGER_DRAG_ANIMATION_HELPER_TEST_NG_H
#define TEST_UNITTEST_CORE_MANAGER_DRAG_ANIMATION_HELPER_TEST_NG_H

#include "test/unittest/core/pattern/test_ng.h"

#define private public
#define protected public
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/manager/drag_drop/utils/drag_animation_helper.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/components_ng/pattern/grid/grid_item_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"

#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
const PanDirection DRAG_DIRECTION = { PanDirection::LEFT };
constexpr int32_t FINGERS_NUMBER = 2;
constexpr float DISTANCE = 10.5f;
} // namespace

class DragAnimationHelperTestNg : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    std::pair<RefPtr<FrameNode>, std::list<RefPtr<FrameNode>>> CreateGridNodeWithChild(
        size_t childCount, const GridItemStyle& gridItemStyle = GridItemStyle::NONE);
private:
    RefPtr<FrameNode> parentNode_;
    std::list<RefPtr<FrameNode>> childNodes_;
};
} // namespace OHOS::Ace::NG

#endif //TEST_UNITTEST_CORE_MANAGER_DRAG_ANIMATION_HELPER_TEST_NG_H