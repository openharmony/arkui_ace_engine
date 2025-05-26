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

#ifndef TEST_UNITTEST_CORE_EVENT_FOCUS_WINDOW_TEST_H
#define TEST_UNITTEST_CORE_EVENT_FOCUS_WINDOW_TEST_H
#include <cstddef>
#include <cstdint>

#include "gtest/gtest.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/event/focus_core/focus_test_base.h"
#include "test/unittest/core/event/frame_node_on_tree.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/log/log_wrapper.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components/theme/app_theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/focus_box.h"
#include "core/components_ng/event/focus_event_handler.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/event/focus_state.h"
#include "core/components_ng/event/touch_event.h"
#include "core/components_ng/manager/focus/focus_manager.h"
#include "core/components_ng/manager/focus/focus_view.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
#include "core/components_ng/pattern/container_modal/container_modal_theme.h"
#include "core/components_ng/pattern/container_modal/container_modal_view.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/key_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

class FocusHierarchicalPageTestNG : public FocusTestBaseNg, public testing::Test {
public:
 static void SetUpTestSuite();
 static void TearDownTestSuite();
};
enum class FocusHierarchicalCase { NODEC = 0, NODEE = 1, NONE = 2 };

void SetDefaultFocus(bool isDefaultFocus, bool isDefaultFocusAble, const RefPtr<FocusHub>& focusHub);
void IsCAlreadyFocus(bool isCAlreadyFocus, const RefPtr<FocusHub>& focusHub);
void IsCFirstFocus(bool isCFirstFocus, const RefPtr<FocusHub>& focusHub);
void IsDependence(bool isDependence, const RefPtr<FocusHub>& focusHub);
void JudgMentDefaultFocus(
 bool isDependenceC, RefPtr<FocusHub>& focusHub1, RefPtr<FocusHub>& focusHub2, RefPtr<FocusView>& focusView);
} // namespace OHOS::Ace::NG

#endif // TEST_UNITTEST_CORE_EVENT_FOCUS_WINDOW_TEST_H
