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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_LAYOUT_SECTION_INITIALIZER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_LAYOUT_SECTION_INITIALIZER_H

#include "core/components_ng/layout/section/section_data_types.h"
#include "core/components_ng/layout/layout_property.h"

namespace OHOS::Ace::NG {
class SectionInitializer {
public:
    static std::vector<Section> InitSections(
        const RefPtr<LayoutProperty>& props, const SizeF& frameSize, Axis axis, int32_t totalCnt);

    /**
     * @brief compare two sections data.
     * @return true if two sections are the same, otherwise false.
     */
    static bool Compare(const std::vector<Section>& prev, const std::vector<Section>& cur);

protected:
    SectionInitializer(const SizeF& frameSize, Axis axis, int32_t totalCnt)
        : frameSize_(frameSize), axis_(axis), totalCnt_(totalCnt)
    {}

    SizeF frameSize_;
    Axis axis_;
    int32_t totalCnt_;
};
} // namespace OHOS::Ace::NG

#endif