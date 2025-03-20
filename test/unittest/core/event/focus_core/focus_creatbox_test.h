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

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/theme/app_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/event/state_style_manager.h"
#include "core/components_ng/event/touch_event.h"
#include "core/components_ng/manager/focus/focus_view.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/key_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
struct FocusBoxPolyMorPhismStyle {
    bool isAFocusBoxStyle;
    bool isBFocusBoxStyle;
    bool isCFocusBoxStyle;
};
struct FocusBoxDependence {
    bool isADependence;
    bool isBDependence;
};
struct FocusBoxStyleType {
    FocusStyleType focusAStyleType;
    FocusStyleType focusBStyleType;
    FocusStyleType focusCStyleType;
};
struct FocusCreatBoxTestCase {
    FocusBoxPolyMorPhismStyle style;
    FocusBoxStyleType focusStyleType;
    FocusBoxDependence isDependence;
    FocusCreatBoxTestCase(
        FocusBoxPolyMorPhismStyle style, FocusBoxStyleType focusStyleType, FocusBoxDependence isDependence)
        : style { style.isAFocusBoxStyle, style.isBFocusBoxStyle, style.isCFocusBoxStyle },
          focusStyleType { focusStyleType.focusAStyleType, focusStyleType.focusBStyleType,
              focusStyleType.focusCStyleType },
          isDependence { isDependence.isADependence, isDependence.isBDependence }
    {}
};
class FocusCreatBoxTestNG : public FocusTestBaseNg, public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    static RefPtr<FrameNode> CreatNode();
    void FocusPolyMorPhismStyle(bool testCase, const RefPtr<FocusHub>& focusHub);
    void InitFocusCreatBox();
    void SetDependence(bool testCase, const RefPtr<FocusHub>& focusHub);
};

} // namespace OHOS::Ace::NG

#endif // TEST_UNITTEST_CORE_EVENT_FOCUS_WINDOW_TEST_H