/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#define AVERAGE_BASE 2

#include "core/accessibility/accessibility_utils.h"

namespace OHOS::Ace {

const char ACCESSIBILITY_TAG_DIV[] = "div";
const char ACCESSIBILITY_TAG_CALENDAR[] = "calendar";
const char ACCESSIBILITY_TAG_TEXT[] = "text";
const char ACCESSIBILITY_TAG_PICKER[] = "picker";
const char ACCESSIBILITY_TAG_OPTION[] = "option";
const char ACCESSIBILITY_TAG_POPUP[] = "popup";
const char ACCESSIBILITY_TAG_PROGRESS[] = "progress";
const char ACCESSIBILITY_TAG_SELECT[] = "select";
const char ACCESSIBILITY_TAG_MENU[] = "menu";
const char ACCESSIBILITY_TAG_SLIDER[] = "slider";
const char ACCESSIBILITY_TAG_SPAN[] = "span";
const char ACCESSIBILITY_TAG_STACK[] = "stack";
const char ACCESSIBILITY_TAG_SWIPER[] = "swiper";
const char ACCESSIBILITY_TAG_SWITCH[] = "switch";
const char ACCESSIBILITY_TAG_TABS[] = "tabs";
const char ACCESSIBILITY_TAG_TAB_BAR[] = "tab-bar";
const char ACCESSIBILITY_TAG_TAB_CONTENT[] = "tab-content";
const char ACCESSIBILITY_TAG_REFRESH[] = "refresh";
const char ACCESSIBILITY_TAG_IMAGE[] = "image";
const char ACCESSIBILITY_TAG_LIST[] = "list";
const char ACCESSIBILITY_TAG_LIST_ITEM[] = "list-item";
const char ACCESSIBILITY_TAG_LIST_ITEM_GROUP[] = "list-item-group";
const char ACCESSIBILITY_TAG_VIDEO[] = "video";
const char ACCESSIBILITY_TAG_RATING[] = "rating";
const char ACCESSIBILITY_TAG_MARQUEE[] = "marquee";
const char ACCESSIBILITY_TAG_NAVIGATION_BAR[] = "navigation-bar";
const char ACCESSIBILITY_TAG_NAVIGATION_MENU[] = "navigation-menu";
const char ACCESSIBILITY_TAG_TEXTAREA[] = "textarea";
const char ACCESSIBILITY_TAG_INPUT[] = "input";
const char ACCESSIBILITY_TAG_LABEL[] = "label";
const char ACCESSIBILITY_TAG_DIVIDER[] = "divider";
const char ACCESSIBILITY_TAG_CANVAS[] = "canvas";
const char ACCESSIBILITY_TAG_BUTTON[] = "button";
const char ACCESSIBILITY_TAG_CHART[] = "chart";
const char ACCESSIBILITY_TAG_CLOCK[] = "clock";
const char ACCESSIBILITY_TAG_DIALOG[] = "dialog";
const char ACCESSIBILITY_TAG_SEARCH[] = "search";

const int32_t WEIGHTED_VALUE = 13;
const int32_t FOCUS_DIRECTION_UP = 1;
const int32_t FOCUS_DIRECTION_DOWN = 1 << 1;
const int32_t FOCUS_DIRECTION_LEFT = 1 << 2;
const int32_t FOCUS_DIRECTION_RIGHT = 1 << 3;
const int32_t FOCUS_DIRECTION_FORWARD = 1 << 4;
const int32_t FOCUS_DIRECTION_BACKWARD = 1 << 5;

static bool CheckRectBeam(const Rect& nodeRect, const Rect& itemRect, const int direction)
{
    switch (direction) {
        case FOCUS_DIRECTION_LEFT:
        case FOCUS_DIRECTION_RIGHT:
            return nodeRect.Top() < itemRect.Bottom() && itemRect.Top() < nodeRect.Bottom();
        case FOCUS_DIRECTION_UP:
        case FOCUS_DIRECTION_DOWN:
            return nodeRect.Left() < itemRect.Right() && itemRect.Left() < nodeRect.Right();
        default:
            break;
    }
    return false;
}

static bool IsToDirectionOf(const Rect& nodeRect, const Rect& itemRect, const int direction)
{
    switch (direction) {
        case FOCUS_DIRECTION_LEFT:
            return nodeRect.Left() >= itemRect.Right();
        case FOCUS_DIRECTION_RIGHT:
            return nodeRect.Right() <= itemRect.Left();
        case FOCUS_DIRECTION_UP:
            return nodeRect.Top() >= itemRect.Bottom();
        case FOCUS_DIRECTION_DOWN:
            return nodeRect.Bottom() <= itemRect.Top();
        default:
            break;
    }
    return false;
}

static double MajorAxisDistanceToFarEdge(const Rect& nodeRect, const Rect& itemRect, const int direction)
{
    double distance = 0.0;
    switch (direction) {
        case FOCUS_DIRECTION_LEFT:
            distance = nodeRect.Left() - itemRect.Left();
            break;
        case FOCUS_DIRECTION_RIGHT:
            distance = itemRect.Right() - nodeRect.Right();
            break;
        case FOCUS_DIRECTION_UP:
            distance = nodeRect.Top() - itemRect.Top();
            break;
        case FOCUS_DIRECTION_DOWN:
            distance = itemRect.Bottom() - nodeRect.Bottom();
            break;
        default:
            break;
    }

    return distance > 1.0 ? distance : 1.0;
}

static double MajorAxisDistance(const Rect& nodeRect, const Rect& itemRect, const int direction)
{
    double distance = 0.0;
    switch (direction) {
        case FOCUS_DIRECTION_LEFT:
            distance = nodeRect.Left() - itemRect.Right();
            break;
        case FOCUS_DIRECTION_RIGHT:
            distance = itemRect.Left() - nodeRect.Right();
            break;
        case FOCUS_DIRECTION_UP:
            distance = nodeRect.Top() - itemRect.Bottom();
            break;
        case FOCUS_DIRECTION_DOWN:
            distance = itemRect.Top() - nodeRect.Bottom();
            break;
        default:
            break;
    }

    return distance > 0.0 ? distance : 0.0;
}

static double MinorAxisDistance(const Rect& nodeRect, const Rect& itemRect, const int direction)
{
    double distance = 0.0;
    switch (direction) {
        case FOCUS_DIRECTION_LEFT:
        case FOCUS_DIRECTION_RIGHT:
            distance = fabs((nodeRect.Top() + nodeRect.Bottom()) / AVERAGE_BASE -
                (itemRect.Top() + itemRect.Bottom()) / AVERAGE_BASE);
            break;
        case FOCUS_DIRECTION_UP:
        case FOCUS_DIRECTION_DOWN:
            distance = fabs((nodeRect.Left() + nodeRect.Right()) / AVERAGE_BASE -
                (itemRect.Left() + itemRect.Right()) / AVERAGE_BASE);
            break;
        default:
            break;
    }

    return distance > 0.0 ? distance : -distance;
}

static double GetWeightedDistanceFor(double majorAxisDistance, double minorAxisDistance)
{
    return WEIGHTED_VALUE * majorAxisDistance * majorAxisDistance + minorAxisDistance * minorAxisDistance;
}

static bool IsCandidateRect(const Rect& nodeRect, const Rect& itemRect, const int direction)
{
    switch (direction) {
        case FOCUS_DIRECTION_LEFT:
            return nodeRect.Left() > itemRect.Left() && nodeRect.Right() > itemRect.Right();
        case FOCUS_DIRECTION_RIGHT:
            return nodeRect.Left() < itemRect.Left() && nodeRect.Right() < itemRect.Right();
        case FOCUS_DIRECTION_UP:
            return nodeRect.Top() > itemRect.Top() && nodeRect.Bottom() > itemRect.Bottom();
        case FOCUS_DIRECTION_DOWN:
            return nodeRect.Top() < itemRect.Top() && nodeRect.Bottom() < itemRect.Bottom();
        default:
            break;
    }
    return false;
}

// Check whether rect1 is outright better than rect2.
static bool OutrightBetter(const Rect& nodeRect, const int direction, const Rect& Rect1, const Rect& Rect2)
{
    bool rect1InSrcBeam = CheckRectBeam(nodeRect, Rect1, direction);
    bool rect2InSrcBeam = CheckRectBeam(nodeRect, Rect2, direction);
    if (rect2InSrcBeam || !rect1InSrcBeam) {
        return false;
    }

    if (!IsToDirectionOf(nodeRect, Rect2, direction)) {
        return true;
    }

    // for direction left or right
    if (direction == FOCUS_DIRECTION_LEFT || direction == FOCUS_DIRECTION_RIGHT) {
        return true;
    }

    return (MajorAxisDistance(nodeRect, Rect1, direction) < MajorAxisDistanceToFarEdge(nodeRect, Rect2, direction));
}

bool CheckBetterRect(const Rect& nodeRect, const int direction, const Rect& itemRect, const Rect& tempBest)
{
    if (!IsCandidateRect(nodeRect, itemRect, direction)) {
        return false;
    }

    if (!IsCandidateRect(nodeRect, tempBest, direction)) {
        return true;
    }

    // now both of item and tempBest are all at the direction of node.
    if (OutrightBetter(nodeRect, direction, itemRect, tempBest)) {
        return true;
    }

    if (OutrightBetter(nodeRect, direction, tempBest, itemRect)) {
        return false;
    }

    // otherwise, do fudge-tastic comparison of the major and minor axis
    return (GetWeightedDistanceFor(
                MajorAxisDistance(nodeRect, itemRect, direction), MinorAxisDistance(nodeRect, itemRect, direction)) <
            GetWeightedDistanceFor(
                MajorAxisDistance(nodeRect, tempBest, direction), MinorAxisDistance(nodeRect, tempBest, direction)));
}

}  // namespace OHOS::Ace
