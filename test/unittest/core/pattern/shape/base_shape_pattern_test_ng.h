/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include <array>

#include "gtest/gtest.h"
#include "include/core/SkCanvas.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/shape/shape_abstract_model_ng.h"

namespace OHOS::Ace::NG {

class BaseShapePatternTestNg : public testing::Test {
public:
    BaseShapePatternTestNg() = default;
    void CheckSize(bool hasValue);
    void CheckFill(bool hasValue);
    void CheckFillOpacity(bool hasValue);
    void CheckStroke(bool hasValue);
    void CheckStrokeWidth(bool hasValue);
    void CheckStrokeOpacity(bool hasValue);
    void CheckStrokeDashArray(bool hasValue);
    void CheckStrokeDashOffset(bool hasValue);
    void CheckStrokeLineCap(bool hasValue);
    void CheckStrokeLineJoin(bool hasValue);
    void CheckStrokeMiterLimit(bool hasValue);
    void CheckAntiAlias(bool hasValue);
    void SetSize(ShapeAbstractModelNG& shapeAbstractModelNG) const;
    virtual RefPtr<FrameNode> CreadFrameNode();
    virtual void Draw(RefPtr<FrameNode> frameNode);
    ~BaseShapePatternTestNg() = default;

    static constexpr float WIDTH = 200.0f;
    static constexpr float HEIGHT = 300.0f;
    static constexpr float OPACITY = 0.5f;
    static constexpr float STROKE_WIDTH = 3.0f;
    static constexpr bool ANTIALIAS = false;
    static constexpr float STROKE_LIMIT = 5.0f;
    static constexpr float DASHOFFSET = 3;
    static constexpr int32_t LINE_JOIN = 1;
    static constexpr int32_t LINE_CAP = 1;
    static constexpr std::array<float, 2> STROKE_DASH_ARRAY = { 3, 5 };
};

} // namespace OHOS::Ace::NG