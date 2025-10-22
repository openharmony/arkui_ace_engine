/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef CAPIDEMO_SCROLL_COMPONENT_H
#define CAPIDEMO_SCROLL_COMPONENT_H

#include "components/component.h"

namespace ArkUICApiDemo {
class ScrollComponent : public Component {
public:
    ScrollComponent() : Component(ARKUI_NODE_SCROLL) {}
    explicit ScrollComponent(ArkUI_NodeHandle handle) : Component(handle) {}

    void SetScrollScrollBar(int32_t barState);
    void SetScrollScrollBarWidth(float width);
    void SetScrollScrollBarColor(uint32_t color);
    void SetScrollScrollable(int32_t scrollable);
    void SetScrollEdgeEffect(int32_t edgeEffect, bool alwaysEnabled);
    void SetScrollEnableScrollInteraction(bool enableScrollInteraction);
    void SetScrollFriction(float friction);
    void SetScrollScrollSnap(
        int32_t snapAlign, int32_t enableSnapToStart, int32_t enableSnapToEnd, const std::vector<float>& pagination);
    void SetScrollNestedScroll(int32_t forward, int32_t backward);
    /**
     * @brief Set the scroll position to the specified offset.
     * @param hOffset horizontal scrolling offset
     * @param vOffset vertical scrolling offset
     * @param optionalParams
     * [0] scrolling duration, in milliseconds.
     * [1] scrolling curve. The parameter type is ArkUI_AnimationCurve.
     * [2] whether to enable the default spring animation.
     * [3] sets whether scrolling can cross the boundary.
     */
    void SetScrollTo(float hOffset, float vOffset, const std::vector<int32_t>& optionalParams);
    void SetScrollEdge(int32_t type);
    void SetScrollEnablePaging(int32_t enablePaging);
    void SetScrollPage(int32_t next);
    void SetScrollPage(int32_t next, int32_t animation);
    void SetScrollBy(float hDistance, float vDistance);
    void SetScrollScrollDirection(int32_t direction);
    void AddChildWithNumber(int32_t number, ArkUI_NodeType type);
};
} // namespace ArkUICApiDemo
#endif // CAPIDEMO_SCROLL_COMPONENT_H
