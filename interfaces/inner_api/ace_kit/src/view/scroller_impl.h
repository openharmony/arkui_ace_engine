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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_SRC_VIEW_SCROLLER_IMPL_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_SRC_VIEW_SCROLLER_IMPL_H

#include "interfaces/inner_api/ace_kit/include/ui/view/scroller.h"
#include "bridge/declarative_frontend/jsview/js_scroller.h"

namespace OHOS::Ace::Kit {

class ScrollerImpl : public Scroller {
    DECLARE_ACE_TYPE(ScrollerImpl, Scroller);

public:
    ScrollerImpl(const RefPtr<Framework::JSScroller>& jsScroller);
    ~ScrollerImpl() = default;

    void AddObserver(const Observer& observer, int32_t id) override;
    void RemoveObserver(int32_t id) override;
    double GetCurrentOffsetX() override;
    double GetCurrentOffsetY() override;
    bool IsAtEnd() override;
    bool IsAtStart() override;
    double GetContentBottom(const RefPtr<FrameNode>& node) override;
    double GetContentTop(const RefPtr<FrameNode>& node) override;
    bool AnimateTo(const Dimension& position, float duration,
        const RefPtr<Curve>& curve, bool smooth, bool canOverScroll) override;

    bool operator==(const Ace::RefPtr<Scroller>& other) const override;
    RefPtr<FrameNode> GetBindingFrameNode() override;

private:
    RefPtr<Framework::JSScroller> jsScroller_;
};
} // namespace OHOS::Ace::Kit

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_SRC_VIEW_SCROLLER_IMPL_H