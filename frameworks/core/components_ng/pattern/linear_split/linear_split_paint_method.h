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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LINEAR_SPLIT_LINEAR_SPLIT_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LINEAR_SPLIT_LINEAR_SPLIT_PAINT_METHOD_H

#include <utility>

#include "base/geometry/ng/offset_t.h"
#include "core/components_ng/pattern/linear_split/linear_split_model_ng.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/components_ng/render/paint_wrapper.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT LinearSplitPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(LinearSplitPaintMethod, NodePaintMethod)
public:
    LinearSplitPaintMethod(std::vector<OffsetF> childrenOffset, float splitLength, SplitType splitType)
        : childrenOffset_(std::move(childrenOffset)), splitLength_(splitLength), splitType_(splitType)
    {}
    ~LinearSplitPaintMethod() override = default;

    CanvasDrawFunction GetContentDrawFunction(PaintWrapper* paintWrapper) override;

private:
    void PaintContent(RSCanvas& canvas);

    std::vector<OffsetF> childrenOffset_;
    float splitLength_ = 0.0f;
    SplitType splitType_;

    ACE_DISALLOW_COPY_AND_MOVE(LinearSplitPaintMethod);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LINEAR_SPLIT_LINEAR_SPLIT_PAINT_METHOD_H