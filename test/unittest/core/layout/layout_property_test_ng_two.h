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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_TEST_UNITTEST_LAYOUT_PROPERTY_TEST_NG_TWO_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_TEST_UNITTEST_LAYOUT_PROPERTY_TEST_NG_TWO_H

#include <optional>

#include "gtest/gtest.h"

#define protected public
#define private public
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"

#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/custom/custom_measure_layout_node.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components/common/properties/alignment.h"

#undef private
#undef protected

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

namespace {
LayoutConstraintF layoutConstraintF = {
    .minSize = {1, 1},
    .maxSize = {10, 10},
    .percentReference = {5, 5},
    .parentIdealSize = {2, 2},
};
constexpr Dimension WIDTH = 1.0_vp;
constexpr Dimension HEIGHT = 2.0_vp;
const CalcSize CALC_SIZE = {CalcLength(WIDTH), CalcLength(HEIGHT)};
} // namespace

struct OverlayOptionsTestCase {
    Alignment align = Alignment::TOP_LEFT;
    TextDirection direction = TextDirection::LTR;
    OffsetF expectedResult = OffsetF();
};

const std::vector<OverlayOptionsTestCase> OVERLAY_OPTIONS_TEST_CASES = {
    { Alignment::TOP_LEFT, TextDirection::LTR, OffsetF(0.0f, 0.0f) },
    { Alignment::TOP_LEFT, TextDirection::RTL, OffsetF(50.0f, 0.0f) },

    { Alignment::TOP_CENTER, TextDirection::LTR, OffsetF(25.0f, 0.0f) },
    { Alignment::TOP_CENTER, TextDirection::RTL, OffsetF(25.0f, 0.0f) },

    { Alignment::TOP_RIGHT, TextDirection::LTR, OffsetF(50.0f, 0.0f) },
    { Alignment::TOP_RIGHT, TextDirection::RTL, OffsetF(0.0f, 0.0f) },

    { Alignment::CENTER_LEFT, TextDirection::LTR, OffsetF(0.0f, 25.0f) },
    { Alignment::CENTER_LEFT, TextDirection::RTL, OffsetF(50.0f, 25.0f) },

    { Alignment::CENTER, TextDirection::LTR, OffsetF(25.0f, 25.0f) },
    { Alignment::CENTER, TextDirection::RTL, OffsetF(25.0f, 25.0f) },

    { Alignment::CENTER_RIGHT, TextDirection::LTR, OffsetF(50.0f, 25.0f) },
    { Alignment::CENTER_RIGHT, TextDirection::RTL, OffsetF(0.0f, 25.0f) },

    { Alignment::BOTTOM_LEFT, TextDirection::LTR, OffsetF(0.0f, 50.0f) },
    { Alignment::BOTTOM_LEFT, TextDirection::RTL, OffsetF(50.0f, 50.0f) },

    { Alignment::BOTTOM_CENTER, TextDirection::LTR, OffsetF(25.0f, 50.0f) },
    { Alignment::BOTTOM_CENTER, TextDirection::RTL, OffsetF(25.0f, 50.0f) },

    { Alignment::BOTTOM_RIGHT, TextDirection::LTR, OffsetF(50.0f, 50.0f) },
    { Alignment::BOTTOM_RIGHT, TextDirection::RTL, OffsetF(0.0f, 50.0f) },
};

class LayoutPropertyTestNgTwo : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
    }
    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
    }
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_TEST_UNITTEST_LAYOUT_PROPERTY_TEST_NG_TWO_H