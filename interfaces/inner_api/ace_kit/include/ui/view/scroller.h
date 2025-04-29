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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_VIEW_SCROLLER_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_VIEW_SCROLLER_H

#include "ui/animation/curve.h"
#include "ui/base/ace_type.h"
#include "ui/base/geometry/dimension.h"
#include "ui/properties/scrollable_properties.h"
#include "ui/view/frame_node.h"

namespace OHOS::Ace::Kit {
class Scroller : public AceType {
    DECLARE_ACE_TYPE(Scroller, AceType);

public:
    using OnReachEvent = std::function<void()>;
    using OnScrollStartEvent = std::function<void()>;
    using OnScrollStopEvent = std::function<void()>;
    using OnDidScrollEvent = std::function<void(Dimension, ScrollSource, bool, bool)>;
    struct Observer {
        OnReachEvent onReachStartEvent;
        OnReachEvent onReachEndEvent;
        OnScrollStartEvent onScrollStartEvent;
        OnScrollStopEvent onScrollStopEvent;
        OnDidScrollEvent onDidScrollEvent;
    };
    Scroller() = default;
    virtual ~Scroller() = default;

    virtual void AddObserver(const Observer& observer, int32_t id) = 0;
    virtual void RemoveObserver(int32_t id) = 0;
    virtual double GetCurrentOffsetX() = 0;
    virtual double GetCurrentOffsetY() = 0;
    virtual bool IsAtEnd() = 0;
    virtual bool IsAtStart() = 0;
    virtual double GetContentBottom(const RefPtr<FrameNode>& node) = 0;
    virtual double GetContentTop(const RefPtr<FrameNode>& node) = 0;
    virtual bool AnimateTo(const Dimension& position, float duration,
        const RefPtr<Curve>& curve, bool smooth, bool canOverScroll = false) = 0;

    virtual bool operator==(const Ace::RefPtr<Scroller>& other) const = 0;
};

} // namespace OHOS::Ace::Kit
#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_VIEW_SCROLLER_H