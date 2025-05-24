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

#ifndef TEST_UNITTEST_CORE_MANAGER_DRAG_DROP_MANAGER_TEST_NG_H
#define TEST_UNITTEST_CORE_MANAGER_DRAG_DROP_MANAGER_TEST_NG_H
#include <optional>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_interaction_interface.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/image/pixel_map.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/subwindow/subwindow_manager.h"
#include "core/common/interaction/interaction_interface.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/manager/drag_drop/drag_drop_manager.h"
#include "core/components_ng/manager/drag_drop/drag_drop_proxy.h"
#include "core/components_ng/pattern/grid/grid_event_hub.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/components_ng/pattern/list/list_event_hub.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/render_node.h"
#include "core/components_ng/manager/drag_drop/drag_drop_global_controller.h"
#include "core/components_ng/manager/drag_drop/drag_drop_spring_loading/drag_drop_spring_loading_detector.h"

namespace OHOS::Ace::NG {
namespace {
const std::string ROOT_ETS_TAG("root");
const std::string GRID_TAG("grid");
const std::string LIST_TAG("list");
const std::string NODE_TAG("custom_node");
const std::string NODE_TAG_EX("custom_node_ex");
const std::string NODE_TAG_EX2("custom_node_ex2");
constexpr int32_t GLOBAL_X = 10;
constexpr int32_t GLOBAL_Y = 20;
const std::string EXTRA_INFO("extra info");
const std::string EXTRA_INFO_2("extra info 2");
const std::string EXTRA_INFO_LEAVE("extra info LEAVE");
const std::string EXTRA_INFO_MOVE("extra info MOVE");
const std::string EXTRA_INFO_ENTER("extra info ENTER");
const std::string ITEM_INFO_LEAVE("item info LEAVE");
const std::string ITEM_INFO_MOVE("item info MOVE");
const std::string ITEM_INFO_ENTER("item info ENTER");
constexpr int32_t INVALID_CURRENT_ID = -1;
// before testing CheckDragDropProxy, DragWindow has created 6 times
constexpr int32_t VALID_CURRENT_ID = 6;
const OffsetF FRAME_OFFSET(0.0f, 0.0f);
const SizeF FRAME_SIZE(GLOBAL_X * 10.0f, GLOBAL_Y * 10.0f);
constexpr int32_t DRAGGED_INDEX = 0;
const DragType DRAG_TYPE_GRID = DragType::GRID;
const DragType DRAG_TYPE_LIST = DragType::LIST;
} // namespace

class DragDropManagerTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

class DragDropManagerTestNgNew : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

class DragDropManagerTestNgCoverage : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};
} // namespace OHOS::Ace::NG

#endif //TEST_UNITTEST_CORE_MANAGER_DRAG_DROP_MANAGER_TEST_NG_H