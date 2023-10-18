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

#include "core/components_ng/pattern/list/list_position_controller.h"

#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "core/animation/curves.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {

void ListPositionController::JumpTo(int32_t index, bool smooth, ScrollAlign align, int32_t source)
{
    auto pattern = scroll_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto listPattern = AceType::DynamicCast<ListPattern>(pattern);
    CHECK_NULL_VOID(listPattern);
    LOGW("jumpTo is not supported now");
    if (align == ScrollAlign::NONE) {
        align = ScrollAlign::START;
    }
    listPattern->ScrollToIndex(index, smooth, align);
}

void ListPositionController::ScrollBy(double pixelX, double pixelY, bool smooth)
{
    auto pattern = scroll_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto listPattern = AceType::DynamicCast<ListPattern>(pattern);
    CHECK_NULL_VOID(listPattern);
    auto offset = listPattern->GetAxis() == Axis::VERTICAL ? pixelY : pixelX;
    listPattern->ScrollBy(static_cast<float>(offset));
}

void ListPositionController::ScrollToEdge(ScrollEdgeType scrollEdgeType, bool smooth)
{
    auto pattern = scroll_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto listPattern = AceType::DynamicCast<ListPattern>(pattern);
    if (listPattern && listPattern->GetAxis() != Axis::NONE) {
        listPattern->ScrollToEdge(scrollEdgeType);
    }
}

void ListPositionController::ScrollPage(bool reverse, bool smooth)
{
    auto pattern = scroll_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto listPattern = AceType::DynamicCast<ListPattern>(pattern);
    if (listPattern && listPattern->GetAxis() != Axis::NONE) {
        listPattern->ScrollPage(reverse);
    }
}

bool ListPositionController::IsAtEnd() const
{
    auto listPattern = AceType::DynamicCast<ListPattern>(scroll_.Upgrade());
    CHECK_NULL_RETURN(listPattern, false);
    return listPattern->IsAtBottom();
}
} // namespace OHOS::Ace::NG
