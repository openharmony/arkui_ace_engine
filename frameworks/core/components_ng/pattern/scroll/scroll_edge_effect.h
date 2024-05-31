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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLL_SCROLL_EDGE_EFFECT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLL_SCROLL_EDGE_EFFECT_H

#include "core/components_ng/pattern/scroll/scroll_edge_effect_base.h"
#include "core/components_ng/render/render_context.h"

namespace OHOS::Ace::NG {

using HandleOverScrollCallback = std::function<void()>;

class ScrollEdgeEffect : public ScrollEdgeEffectBase {
    DECLARE_ACE_TYPE(ScrollEdgeEffect, ScrollEdgeEffectBase);

public:
    explicit ScrollEdgeEffect(EdgeEffect edgeEffect) : ScrollEdgeEffectBase(edgeEffect) {}

    ScrollEdgeEffect() = default;

    ~ScrollEdgeEffect() override = default;

    virtual void HandleOverScroll(Axis axis, float overScroll, const SizeF& viewPort,
        bool isScrollFromUpdate = false, bool isNotPositiveScrollableDistance = false) {}

    virtual void Paint(RSCanvas& canvas, const SizeF& viewPort, const OffsetF& offset) {}

    virtual void SetHandleOverScrollCallback(const HandleOverScrollCallback& callback) {}
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLL_SCROLL_EDGE_EFFECT_H
