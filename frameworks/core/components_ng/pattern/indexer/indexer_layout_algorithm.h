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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_INDEXER_INDEXER_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_INDEXER_INDEXER_LAYOUT_ALGORITHM_H

#include "base/memory/referenced.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/indexer/indexer_layout_property.h"

namespace OHOS::Ace::NG {
class PipelineContext;

class ACE_EXPORT IndexerLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(IndexerLayoutAlgorithm, LayoutAlgorithm);

public:
    IndexerLayoutAlgorithm() {}

    ~IndexerLayoutAlgorithm() override = default;

    bool GetIsInitialized() const
    {
        return isInitialized_;
    }

    void SetIsInitialized(bool isInitialized)
    {
        isInitialized_ = isInitialized;
    }

    int32_t GetSelected() const
    {
        return selected_;
    }

    void SetSelected(int32_t selected)
    {
        selected_ = selected;
    }
    
    float GetItemSizeRender() const
    {
        return itemSizeRender_;
    }

    void Measure(LayoutWrapper* layoutWrapper) override;

    void Layout(LayoutWrapper* layoutWrapper) override;

private:
    void InitializeIndexer(LayoutWrapper* layoutWrapper);

    std::vector<std::string> arrayValue_;
    bool isInitialized_ = false;
    int32_t itemCount_ = 0;
    int32_t selected_ = 0;
    Color color_ = Color::BLACK;
    Color selectedColor_ = Color::BLACK;
    Color popupColor_ = Color::BLACK;
    Color selectedBackgroundColor_ = Color::BLACK;
    Color popupBackground_ = Color::BLACK;
    bool usingPopup_ = false;
    TextStyle selectedFont_;
    TextStyle popupFont_;
    TextStyle font_;
    float itemSize_ = 0.0f;
    float itemSizeRender_ = 0.0f;
    V2::AlignStyle alignStyle_ = V2::AlignStyle::RIGHT;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_INDEXER_INDEXER_LAYOUT_ALGORITHM_H
