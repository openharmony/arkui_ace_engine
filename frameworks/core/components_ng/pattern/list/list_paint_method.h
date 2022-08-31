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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_PAINT_METHOD_H

#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "base/utils/utils.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/components_v2/list/list_component.h"
#include "core/components_ng/render/divider_painter.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ListPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(ListPaintMethod, NodePaintMethod)
public:
    ListPaintMethod(const V2::ItemDivider& divider, int32_t startIndex, int32_t endIndex,
        bool vertical, const ListLayoutAlgorithm::PositionMap& itemPosition) : divider_(divider),
        startIndex_(startIndex), endIndex_(endIndex), vertical_(vertical), itemPosition_(itemPosition) {}
    ~ListPaintMethod() override = default;

    CanvasDrawFunction GetOverlayDrawFunction(PaintWrapper* paintWrapper) override;

private:
    V2::ItemDivider divider_;
    int32_t startIndex_ = 0;
    int32_t endIndex_ = 0;
    bool vertical_ = false;
    ListLayoutAlgorithm::PositionMap itemPosition_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_PAINT_METHOD_H