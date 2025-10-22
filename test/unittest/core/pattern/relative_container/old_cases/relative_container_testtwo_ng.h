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

#include <optional>
#include <vector>

#include "gtest/gtest.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/relative_container/old_cases/relative_container_common_ng.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/layout/position_param.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/relative_container/relative_container_layout_property.h"
#include "core/components_ng/pattern/relative_container/relative_container_model_ng.h"
#include "core/components_ng/pattern/relative_container/relative_container_pattern.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "frameworks/core/components/common/layout/position_param.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
namespace {
const float CONTAINER_WIDTH = 300.0f;
const float CONTAINER_HEIGHT = 300.0f;
const float ZERO = 0.0f;

const float FIRST_ITEM_WIDTH = 150.0f;
const float FIRST_ITEM_HEIGHT = 75.0f;

const float THIRD_ITEM_WIDTH = 225.0f;
const float THIRD_ITEM_HEIGHT = 75.0f;

const SizeF CONTAINER_SIZE(CONTAINER_WIDTH, CONTAINER_HEIGHT);
const SizeF FIRST_ITEM_SIZE(FIRST_ITEM_WIDTH, FIRST_ITEM_HEIGHT);
const SizeF THIRD_ITEM_SIZE(THIRD_ITEM_WIDTH, THIRD_ITEM_HEIGHT);

const OffsetF OFFSET_TOP_LEFT = OffsetF(ZERO, ZERO);
const OffsetF OFFSET_TOP_MIDDLE = OffsetF(CONTAINER_WIDTH / 2.0f, ZERO);
const OffsetF OFFSET_TOP_RIGHT = OffsetF(CONTAINER_WIDTH, ZERO);

const OffsetF OFFSET_CENTER_LEFT = OffsetF(ZERO, CONTAINER_HEIGHT / 2.0f);
const OffsetF OFFSET_CENTER_MIDDLE = OffsetF(CONTAINER_WIDTH / 2.0f, CONTAINER_HEIGHT / 2.0f);
const OffsetF OFFSET_CENTER_RIGHT = OffsetF(CONTAINER_WIDTH, CONTAINER_HEIGHT / 2.0f);

const OffsetF OFFSET_BOTTOM_LEFT = OffsetF(ZERO, CONTAINER_HEIGHT);
const OffsetF OFFSET_BOTTOM_MIDDLE = OffsetF(CONTAINER_WIDTH / 2.0f, CONTAINER_HEIGHT);
const OffsetF OFFSET_BOTTOM_RIGHT = OffsetF(CONTAINER_WIDTH, CONTAINER_HEIGHT);

const std::string FIRST_ITEM_ID = "bt1";
const std::string SECOND_ITEM_ID = "bt2";
const std::string THIRD_ITEM_ID = "bt3";
const std::string FOURTH_ITEM_ID = "bt4";
const std::string FIFTH_ITEM_ID = "bt5";
const std::string CONTAINER_ID = "__container__";
} // namespace

class RelativeContainerTestTwoNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
    void CreateInstance(const std::function<void(RelativeContainerModelNG)>& callback = nullptr);
    void SetComponentParam(TextModelNG& textModelNG, std::string id, float width, float height);
    void SetContainerParam(std::string id, float width, float height);

    static void TearDownTestSuite()
    {
        TestNG::TearDownTestSuite();
    }

    static void SetUpTestCase()
    {
        MockPipelineContext::SetUp();
    }

    RefPtr<FrameNode> frameNode_;
    RefPtr<RelativeContainerPattern> pattern_;
    RefPtr<RelativeContainerLayoutProperty> layoutProperty_;
};

inline void RelativeContainerTestTwoNg::SetUp() {}

inline void RelativeContainerTestTwoNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    layoutProperty_ = nullptr;
}

inline void RelativeContainerTestTwoNg::CreateInstance(const std::function<void(RelativeContainerModelNG)>& callback)
{
    RelativeContainerModelNG model;
    model.Create();
    if (callback) {
        callback(model);
    }
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<RelativeContainerPattern>();
    layoutProperty_ = frameNode_->GetLayoutProperty<RelativeContainerLayoutProperty>();
}

inline void RelativeContainerTestTwoNg::SetComponentParam(TextModelNG& textModelNG, std::string id, float width, float height)
{
    textModelNG.Create(StringUtils::Str8ToStr16(id));
    ViewAbstract::SetWidth(CalcLength(width));
    ViewAbstract::SetHeight(CalcLength(height));
    ViewAbstract::SetInspectorId(id);
}

inline void RelativeContainerTestTwoNg::SetContainerParam(std::string id, float width, float height)
{
    ViewAbstract::SetWidth(CalcLength(width));
    ViewAbstract::SetHeight(CalcLength(height));
    ViewAbstract::SetInspectorId(id);
}
}// namespace OHOS::Ace::NG