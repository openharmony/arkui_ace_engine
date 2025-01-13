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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_FILL_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_FILL_ALGORITHM_H

#include "base/geometry/axis.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
namespace OHOS::Ace::NG {
class FrameNode;

enum class FillDirection { START, END, INITIAL };

class FillAlgorithm : public virtual AceType {
    DECLARE_ACE_TYPE(FillAlgorithm, AceType);

public:
    /**
     * @brief called before filling starts. A chance to prepare relevant data.
     */
    virtual void PreFill(const SizeF& viewport, Axis axis, int32_t totalCnt) {}

    virtual RectF CalcMarkItemRect(const SizeF& viewport, Axis axis, FrameNode* node, int32_t index,
        const std::optional<OffsetF>& slidingOffset) = 0;

    virtual RectF CalcItemRectAfterMarkItem(
        const SizeF& viewport, Axis axis, FrameNode* node, int32_t index, const RectF& markItem) = 0;

    virtual RectF CalcItemRectBeforeMarkItem(
        const SizeF& viewport, Axis axis, FrameNode* node, int32_t index, const RectF& markItem) = 0;

    virtual void OnSlidingOffsetUpdate(float x, float y) {}

    virtual bool CanFillMore(const SizeF& scrollWindowSize, const RectF& markItemRect, FillDirection direction) = 0;

    virtual bool IsReady() const
    {
        return false;
    }
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_FILL_ALGORITHM_H
