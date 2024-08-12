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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_SUB_MENU_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_SUB_MENU_LAYOUT_ALGORITHM_H

#include "core/components_ng/pattern/menu/menu_layout_algorithm.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT SubMenuLayoutAlgorithm : public MenuLayoutAlgorithm {
    DECLARE_ACE_TYPE(SubMenuLayoutAlgorithm, MenuLayoutAlgorithm)
public:
    SubMenuLayoutAlgorithm() = default;
    ~SubMenuLayoutAlgorithm() override = default;

    void Layout(LayoutWrapper* layoutWrapper) override;

private:
    OffsetF GetSubMenuPosition(const RefPtr<FrameNode>& parentMenuItem, bool stacked);
    float VerticalLayoutSubMenu(const SizeF& size, float position, const SizeF& menuItemSize);
    float HorizontalLayoutSubMenu(const SizeF& size, float position, const SizeF& menuItemSize,
        LayoutWrapper* layoutWrapper = nullptr);
    OffsetF MenuLayoutAvoidAlgorithm(const RefPtr<FrameNode>& parentMenuItem, const SizeF& size, bool stacked,
        LayoutWrapper* layoutWrapper = nullptr);
    float VerticalLayoutSubMenuHalfScreen(const SizeF& size, float position, const SizeF& menuItemSize);
    OffsetF GetSubMenuLayoutOffset(LayoutWrapper* layoutWrapper, const RefPtr<FrameNode>& parentMenuItem,
        const SizeF& size, bool stacked);
    void ModifySubMenuWrapper(LayoutWrapper* layoutWrapper);
    void CheckMenuPadding(LayoutWrapper* layoutWrapper);
    void InitializePadding(LayoutWrapper* layoutWrapper);
    void InitializePaddingAPI12(LayoutWrapper* layoutWrapper);
    float margin_ = 0.0f;
    float paddingStart_ = 0.0f;
    float paddingEnd_ = 0.0f;
    float paddingTop_ = 0.0f;
    float paddingBottom_ = 0.0f;

    ACE_DISALLOW_COPY_AND_MOVE(SubMenuLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_SUB_MENU_LAYOUT_ALGORITHM_H
