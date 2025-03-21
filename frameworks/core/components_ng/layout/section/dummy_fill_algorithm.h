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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_LAYOUT_DUMMY_FILL_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_LAYOUT_DUMMY_FILL_ALGORITHM_H

#include "core/components_ng/base/fill_algorithm.h"

namespace OHOS::Ace::NG {
/**
 * @brief dummy algorithm that always load all elements
 *
 */
class DummyFillAlgorithm : public FillAlgorithm {
public:
    void FillMarkItem(const SizeF& viewport, Axis axis, FrameNode* node, int32_t index) override {}

    void FillNext(const SizeF& viewport, Axis axis, FrameNode* node, int32_t index) override {}

    void FillPrev(const SizeF& viewport, Axis axis, FrameNode* node, int32_t index) override {}

    void OnSlidingOffsetUpdate(float delta) override {}

    bool CanFillMore(Axis axis, const SizeF& scrollWindowSize, int32_t idx, FillDirection direction) override
    {
        return true;
    }

    void PreFill(const SizeF& viewport, Axis axis, int32_t totalCnt) override {}

    int32_t GetMarkIndex() override
    {
        return 0;
    }

    void MarkJump() override {}
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_LAYOUT_DUMMY_FILL_ALGORITHM_H
