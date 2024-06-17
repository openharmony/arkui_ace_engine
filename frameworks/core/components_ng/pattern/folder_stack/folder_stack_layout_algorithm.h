/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FOLDER_STACK_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FOLDER_STACK_LAYOUT_ALGORITHM_H

#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/group_node.h"
#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/folder_stack/folder_stack_group_node.h"
#include "core/components_ng/pattern/folder_stack/folder_stack_layout_property.h"
#include "core/components_ng/pattern/stack/stack_layout_algorithm.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT FolderStackLayoutAlgorithm : public StackLayoutAlgorithm {
    DECLARE_ACE_TYPE(FolderStackLayoutAlgorithm, StackLayoutAlgorithm);

public:
    FolderStackLayoutAlgorithm();
    ~FolderStackLayoutAlgorithm() override = default;
    void Layout(LayoutWrapper* layoutWrapper) override;
    void Measure(LayoutWrapper* layoutWrapper) override;
    const OffsetF& GetControlPartsStackRect() const
    {
        return controlPartsStackRect_;
    }

    bool GetIsIntoFolderStack() const
    {
        return isIntoFolderStack_;
    }

private:
    void LayoutHoverStack(LayoutWrapper* layoutWrapper, const RefPtr<FolderStackGroupNode>& hostNode,
        const RefPtr<FolderStackLayoutProperty>& folderStackLayoutProperty);
    void LayoutControlPartsStack(LayoutWrapper* layoutWrapper, const RefPtr<FolderStackGroupNode>& hostNode,
        const RefPtr<FolderStackLayoutProperty>& folderStackLayoutProperty);
    void MeasureHoverStack(LayoutWrapper* layoutWrapper, const RefPtr<FolderStackGroupNode>& hostNode,
        const RefPtr<FolderStackLayoutProperty>& folderStackLayoutProperty, const SizeF& size);
    void MeasureControlPartsStack(LayoutWrapper* layoutWrapper, const RefPtr<FolderStackGroupNode>& hostNode,
        const RefPtr<FolderStackLayoutProperty>& folderStackLayoutProperty, const SizeF& size);
    void RangeCalculation(const RefPtr<FolderStackGroupNode>& hostNode,
        const RefPtr<FolderStackLayoutProperty>& folderStackLayoutProperty, const SizeF& size);
    bool IsFullWindow(SizeF& frameSize, const RefPtr<FolderStackLayoutProperty>& folderStackLayoutProperty,
        LayoutWrapper* layoutWrapper);
    static NG::OffsetF CalculateStackAlignment(
        const NG::SizeF& parentSize, const NG::SizeF& childSize, const Alignment& alignment);
    void AdjustNodeTree(const RefPtr<FolderStackGroupNode>& hostNode);
    bool IsIntoFolderStack(SizeF& frameSize, const RefPtr<FolderStackLayoutProperty>& folderStackLayoutProperty,
        LayoutWrapper* layoutWrapper);
    void OnHoverStatusChange(LayoutWrapper* layoutWrapper);
    void MeasureByStack(const RefPtr<FolderStackGroupNode>& hostNode, LayoutWrapper* layoutWrapper);
    ACE_DISALLOW_COPY_AND_MOVE(FolderStackLayoutAlgorithm);
    float preHoverStackHeight_ = 0.0f;
    float preControlPartsStackHeight_ = 0.0f;
    OffsetF controlPartsStackRect_;
    bool isIntoFolderStack_ = false;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FOLDER_STACK_FOLDER_STACK_LAYOUT_ALGORITHM_H
