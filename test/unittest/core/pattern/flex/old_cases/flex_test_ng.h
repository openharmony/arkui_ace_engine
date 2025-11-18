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

#include "gtest/gtest.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"

#define private public
#define protectd public
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/flex/flex_layout_pattern.h"
#include "core/components_ng/pattern/flex/flex_layout_property.h"
#include "core/components_ng/pattern/flex/flex_model_ng.h"
#include "core/components_ng/pattern/flex/wrap_layout_algorithm.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

namespace {
const float OFFSET_TOP = 20.0f;
const float OFFSET_LEFT = 0.0f;
const float CONTAINER_WIDTH = 300.0f;
const float CONTAINER_HEIGHT = 300.0f;
const float FIRST_ITEM_WIDTH = 150.0f;
const float FIRST_ITEM_HEIGHT = 75.0f;
const SizeF FIRST_ITEM_SIZE(FIRST_ITEM_WIDTH, FIRST_ITEM_HEIGHT);
const int START_INDEX = 0;
const int THREE_ITEM_SIZE = 3;
const int FOUR_ITEM_SIZE = 4;

const float RK356_WIDTH = 720.0f;
const float RK356_HEIGHT = 1136.0f;
const float ZERO = 0.0f;

const float SMALL_ITEM_WIDTH = 150.0f;
const float SMALL_ITEM_HEIGHT = 60.0f;

const float BIG_ITEM_WIDTH = 180.0f;
const float BIG_ITEM_HEIGHT = 75.0f;

const float ROW_HEIGHT = 120.0f;
const float COLUMN_HEIGHT = 150.0f;

const float TWENTY_PERCENT_WIDTH = 0.2f * RK356_WIDTH;
const float TWENTY_PERCENT_COLUMN_HEIGHT = 0.2f * COLUMN_HEIGHT;

const SizeF CONTAINER_SIZE(RK356_WIDTH, RK356_HEIGHT);
const SizeF SMALL_ITEM_SIZE(SMALL_ITEM_WIDTH, SMALL_ITEM_HEIGHT);
const SizeF BIG_ITEM_SIZE(BIG_ITEM_WIDTH, BIG_ITEM_HEIGHT);

const OffsetF OFFSET_TOP_LEFT = OffsetF(ZERO, ZERO);
const OffsetF OFFSET_TOP_MIDDLE = OffsetF(RK356_WIDTH / 2.0f, ZERO);
const OffsetF OFFSET_TOP_RIGHT = OffsetF(RK356_WIDTH, ZERO);

const OffsetF OFFSET_CENTER_LEFT = OffsetF(ZERO, RK356_HEIGHT / 2.0f);
const OffsetF OFFSET_CENTER_MIDDLE = OffsetF(RK356_WIDTH / 2.0f, RK356_HEIGHT / 2.0f);
const OffsetF OFFSET_CENTER_RIGHT = OffsetF(RK356_WIDTH, RK356_HEIGHT / 2.0f);

const OffsetF OFFSET_BOTTOM_LEFT = OffsetF(ZERO, RK356_HEIGHT);
const OffsetF OFFSET_BOTTOM_MIDDLE = OffsetF(RK356_WIDTH / 2.0f, RK356_HEIGHT);
const OffsetF OFFSET_BOTTOM_RIGHT = OffsetF(RK356_WIDTH, RK356_HEIGHT);

const float NOPADDING = 0.0f;
constexpr int32_t FLEX_NODE_ID = 12;
} // namespace
class FlexTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

inline void FlexTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}

inline void FlexTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

struct WrapProperties {
    WrapDirection wrapDirection = WrapDirection::HORIZONTAL;
    WrapAlignment wrapAlignment = WrapAlignment::START;
    WrapAlignment wrapMainAxisAlignment = WrapAlignment::START;
    WrapAlignment wrapCrossAxisAlignment = WrapAlignment::START;
    Dimension mainSpace = Dimension(20.0, DimensionUnit::VP);
    Dimension crossSpace = Dimension(20.0, DimensionUnit::VP);
};

inline void UpdateWrapProperties(const RefPtr<FlexLayoutProperty>& layoutProperty, const WrapProperties& wrapProperty)
{
    EXPECT_EQ(layoutProperty == nullptr, false);
    layoutProperty->UpdateWrapDirection(wrapProperty.wrapDirection);
    layoutProperty->UpdateAlignment(wrapProperty.wrapAlignment);
    layoutProperty->UpdateMainAlignment(wrapProperty.wrapMainAxisAlignment);
    layoutProperty->UpdateCrossAlignment(wrapProperty.wrapCrossAxisAlignment);
    layoutProperty->UpdateSpace(wrapProperty.mainSpace);
    layoutProperty->UpdateCrossSpace(wrapProperty.crossSpace);
}

struct FlexProperties {
    FlexDirection flexDirection = FlexDirection::ROW;
    FlexAlign flexAlign = FlexAlign::FLEX_START;
};

inline void UpdateFlexProperties(const RefPtr<FlexLayoutProperty>& layoutProperty, const FlexProperties& flexProperty)
{
    EXPECT_FALSE(layoutProperty == nullptr);
    layoutProperty->UpdateFlexDirection(flexProperty.flexDirection);
    layoutProperty->UpdateMainAxisAlign(flexProperty.flexAlign);
    layoutProperty->UpdateCrossAxisAlign(flexProperty.flexAlign);
}
} // namespace OHOS::Ace::NG