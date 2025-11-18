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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_TEST_UNITTEST_LAYOUT_PROPERTY_TEST_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_TEST_UNITTEST_LAYOUT_PROPERTY_TEST_NG_H

#include <optional>

#include "gtest/gtest.h"

#define protected public
#define private public
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components_ng/property/position_property.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/safe_area_insets.h"
#include "core/components_ng/property/grid_property.h"
#include "core/pipeline/base/element_register.h"

#undef private
#undef protected

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
namespace {

const InspectorFilter filter;
const std::optional<float> ZERO { 0.0 };
const std::optional<int32_t> SPAN_ONE { -1 };
const std::optional<int32_t> OFFSET_ONE { -1 };
const std::optional<int> WIDTH_OPT { 10 };
const std::optional<int> HEIGHT_OPT { 5 };
const std::optional<int32_t> SPAN;
const std::optional<int32_t> OFFSET;

constexpr Dimension WIDTH = 1.0_vp;
constexpr Dimension HEIGHT = 2.0_vp;
constexpr Dimension TOPONE = 3.0_vp;
constexpr Dimension BOTTOMONE = 4.0_vp;

const std::string VALUE_TEST = "test";
const std::string STRING_TEST = "{\"top\":\"3.00vp\",\"right\":\"2.00vp\",\"bottom\":\"4.00vp\",\"left\":\"1.00vp\"}";

const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode("root", 1, AceType::MakeRefPtr<Pattern>(), true);
const auto FRAME_NODE_TEST = FrameNode::CreateFrameNode("test", 0, AceType::MakeRefPtr<Pattern>(), true);

const CalcSize CALC_SIZE = { CalcLength(WIDTH), CalcLength(HEIGHT) };

LayoutConstraintF layoutConstraintF = {
    .minSize = { 1, 1 },
    .maxSize = { 10, 10 },
    .percentReference = { 5, 5 },
    .parentIdealSize = { 2, 2 },
};

SafeAreaExpandOpts expandOpts = {
    .edges = SAFE_AREA_TYPE_SYSTEM,
    .type = SAFE_AREA_EDGE_TOP,
};

SafeAreaInsets::Inset inset = {
    .start = 0,
    .end = 1,
};

SafeAreaInsets safeAreaInset(inset, inset, inset, inset);

inline void MakeProperty(RefPtr<LayoutProperty> layoutProperty)
{
    layoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    layoutProperty->positionProperty_ = std::make_unique<PositionProperty>();
    layoutProperty->flexItemProperty_ = std::make_unique<FlexItemProperty>();
    layoutProperty->borderWidth_ = std::make_unique<BorderWidthProperty>();
    layoutProperty->gridProperty_ = std::make_unique<GridProperty>();
    layoutProperty->padding_ = std::make_unique<PaddingProperty>();
    layoutProperty->margin_ = std::make_unique<MarginProperty>();
    layoutProperty->safeAreaInsets_ = std::make_unique<SafeAreaInsets>();
    layoutProperty->safeAreaExpandOpts_ = std::make_unique<SafeAreaExpandOpts>();
}

inline PaddingPropertyT<CalcLength> MakePadding()
{
    PaddingPropertyT<CalcLength> paddingProperty;
    paddingProperty.left = { CalcLength(WIDTH) };
    paddingProperty.right = { CalcLength(HEIGHT) };
    paddingProperty.top = { CalcLength(TOPONE) };
    paddingProperty.bottom = { CalcLength(BOTTOMONE) };

    return paddingProperty;
}

} // namespace

class LayoutPropertyTestNg : public testing::Test {
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

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_TEST_UNITTEST_LAYOUT_PROPERTY_TEST_NG_H