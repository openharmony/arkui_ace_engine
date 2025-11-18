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

#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_GRID_ROW_BASE_TEST_NG_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_GRID_ROW_BASE_TEST_NG_H
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/pattern/grid_col/grid_col_layout_algorithm.h"
#include "core/components_ng/pattern/grid_col/grid_col_layout_pattern.h"
#include "core/components_ng/pattern/grid_col/grid_col_layout_property.h"
#include "core/components_ng/pattern/grid_col/grid_col_model_ng.h"
#include "core/components_ng/pattern/grid_row/grid_row_event_hub.h"
#include "core/components_ng/pattern/grid_row/grid_row_layout_algorithm.h"
#include "core/components_ng/pattern/grid_row/grid_row_layout_pattern.h"
#include "core/components_ng/pattern/grid_row/grid_row_layout_property.h"
#include "core/components_ng/pattern/grid_row/grid_row_model_ng.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
class GridRowBaseTestNG : public TestNG {
public:
    void CreateMeasureLayoutTask(RefPtr<FrameNode> &gridRow, std::optional<float> width = std::nullopt,
        std::optional<float> height = std::nullopt)
    {
        LayoutConstraintF constraint;
        if (width.has_value()) {
            constraint.selfIdealSize.SetWidth(width.value());
        }
        if (height.has_value()) {
            constraint.selfIdealSize.SetHeight(height.value());
        }
        auto layoutProperty = gridRow->GetLayoutProperty();
        layoutProperty->UpdateLayoutConstraint(constraint);
        layoutProperty->UpdateContentConstraint();
        GridRowLayoutAlgorithm algorithm;
        algorithm.Measure(Referenced::RawPtr(gridRow));
        algorithm.Layout(Referenced::RawPtr(gridRow));
    }

    RefPtr<FrameNode> CreateGridColWithProperty(int32_t spanVal, int32_t offsetVal, float height = 0.0f,
        FlexAlign flexAlign = FlexAlign::FLEX_START)
    {
        return CreateGridCol([this, spanVal, offsetVal, height, flexAlign](GridColModelNG model) {
            V2::GridContainerSize span(spanVal);
            V2::GridContainerSize offset(offsetVal);
            model.SetSpan(span);
            model.SetOffset(offset);
            ViewAbstract::SetHeight(CalcLength(height));
            ViewAbstract::SetAlignSelf(flexAlign);
        });
    }
    string DumpChildrenInfo(std::list<ChildrenRow>& listOfChildren)
    {
        string result;
        for (auto &row : listOfChildren) {
            for (auto &child : row) {
                result += child.second.ToString();
            }
        }
        return result;
    }

    void CreateNewLineOffset(int32_t newLineCount, int32_t offset, int32_t span, float offsetY, NewLineOffset &result)
    {
        result.newLineCount = newLineCount;
        result.offset = offset;
        result.span = span;
        result.offsetY = offsetY;
    }

    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    RefPtr<FrameNode> CreateGridRow(const std::function<void(GridRowModelNG)>& callback);
    RefPtr<FrameNode> CreateGridCol(const std::function<void(GridColModelNG)>& callback);
};
}

#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_GRID_ROW_BASE_TEST_NG_H