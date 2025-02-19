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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_LAYOUT_STAGGERED_FILL_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_LAYOUT_STAGGERED_FILL_ALGORITHM_H

#include <algorithm>
#include <cstdint>

#include "item_measurer.h"
#include "sections_initializer.h"

#include "base/geometry/axis.h"
#include "base/geometry/ng/offset_t.h"
#include "core/components_ng/base/fill_algorithm.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/layout/section/section_data_types.h"

namespace OHOS::Ace::NG {

class StaggeredFillAlgorithm : public FillAlgorithm {
    DECLARE_ACE_TYPE(StaggeredFillAlgorithm, FillAlgorithm);

public:
    explicit StaggeredFillAlgorithm(const RefPtr<LayoutProperty>& props) : props_(props) {}

    void FillMarkItem(const SizeF& viewport, Axis axis, FrameNode* node, int32_t index) override;

    void FillNext(const SizeF& viewport, Axis axis, FrameNode* node, int32_t index) override;

    void FillPrev(const SizeF& viewport, Axis axis, FrameNode* node, int32_t index) override;

    void OnSlidingOffsetUpdate(float delta) override;

    bool CanFillMore(Axis axis, const SizeF& scrollWindowSize, int32_t idx, FillDirection direction) override;

    void PreFill(const SizeF& viewport, Axis axis, int32_t totalCnt) override;

    int32_t GetMarkIndex() override;

    void MarkJump() override;

private:
    bool CanFillMoreAtEnd(float viewportBound, Axis axis);

    bool CanFillMoreAtStart(Axis axis);

    void InitSections(int32_t totalCnt, Axis axis, const SizeF& frameSize);

    /**
     * @brief update syncCacheCnt_ from LayoutProperty
     *
     */
    void UpdateSyncCachedCnt();

    std::optional<int32_t> StartIdx() const;
    std::optional<int32_t> EndIdx() const;

    Section& GetSection(int32_t item);

    std::vector<Section> sections_;
    const RefPtr<LayoutProperty> props_;
    RefPtr<Measurer> measurer_;

    int32_t syncCacheCnt_ = 0; // cache items to load synchronously
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_LAYOUT_STAGGERED_FILL_ALGORITHM_H
