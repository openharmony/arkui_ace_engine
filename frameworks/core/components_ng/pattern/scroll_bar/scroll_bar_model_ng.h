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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLL_BAR_SCROLL_BAR_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLL_BAR_SCROLL_BAR_MODEL_NG_H

#include "core/components_ng/pattern/scroll_bar/scroll_bar_model.h"
#include "frameworks/base/utils/macros.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ScrollBarModelNG : public OHOS::Ace::ScrollBarModel {
public:
    RefPtr<ScrollProxy> GetScrollBarProxy(const  RefPtr<ScrollProxy>& scrollProxy) override;
    void Create(const RefPtr<ScrollProxy>& proxy, bool infoflag, bool proxyFlag,
        int directionValue, int stateValue, bool isCreateArc = false) override;
    void SetEnableNestedScroll(bool enableNestedSroll) override;
    static void SetEnableNestedScroll(FrameNode* frameNode, bool enableNestedSroll);
    static void SetNestedScroll(RefPtr<FrameNode>& frameNode, RefPtr<ScrollablePattern>& pattern);
    static void UnSetNestedScroll(RefPtr<FrameNode>& frameNode, RefPtr<ScrollablePattern>& pattern);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLL_BAR_SCROLL_BAR_MODEL_NG_H
