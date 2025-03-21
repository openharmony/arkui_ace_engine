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

    /**
     * @brief Called before the adapter performs a jump
     *
     */
    virtual void MarkJump() = 0;

    virtual void FillMarkItem(const SizeF& viewport, Axis axis, FrameNode* node, int32_t index) = 0;

    /**
     * @brief Fill next item at the end of the viewport. Node ptr and item index are given.
     */
    virtual void FillNext(const SizeF& viewport, Axis axis, FrameNode* node, int32_t index) = 0;

    /**
     * @brief Fill previous item at the start of the viewport. Node ptr and item index are given.
     */
    virtual void FillPrev(const SizeF& viewport, Axis axis, FrameNode* node, int32_t index) = 0;

    /* for parallel mode */
    virtual bool OnSlidingOffsetUpdate(const SizeF& viewport, Axis axis, float delta)
    {
        return false;
    }

    virtual void OnSlidingOffsetUpdate(float delta) = 0;

    /**
     * @param idx index of the item just filled. Can pass in -1 if nothing was filled.
     * @return true if more items can be filled in the given @c direction
     */
    virtual bool CanFillMore(Axis axis, const SizeF& scrollWindowSize, int32_t idx, FillDirection direction) = 0;

    virtual int32_t GetMarkIndex() = 0;

    virtual std::pair<int32_t, int32_t> GetRange() const
    {
        return {};
    }
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_FILL_ALGORITHM_H
