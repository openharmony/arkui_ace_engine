/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SMART_LAYOUT_SMART_LAYOUT_TYPES_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SMART_LAYOUT_SMART_LAYOUT_TYPES_H

#include "localsmt/localsmt.h"

namespace OHOS::Ace::NG {

/**
 * @brief Layout direction type for smart layout
 */
enum class SmartLayoutType {
    UNKNOWN,
    COLUMN,
    ROW,
    FLEX
};

/**
 * @brief Alignment type for smart layout (decoupled from FlexAlign)
 */
enum class SmartLayoutAlign {
    FLEX_START,  // Start alignment
    CENTER,      // Center alignment
    FLEX_END     // End alignment
};

/**
 * @brief Size information for smart layout (decoupled from SizeF)
 */
struct SmartLayoutSize {
    double width = 0.0;
    double height = 0.0;

    SmartLayoutSize() = default;
    SmartLayoutSize(double w, double h) : width(w), height(h) {}

    double Width() const { return width; }
    double Height() const { return height; }
    void SetWidth(double w) { width = w; }
    void SetHeight(double h) { height = h; }
};

/**
 * @brief Child layout info for decoupling from external types
 */
struct ChildLayoutInfo {
    int64_t id = 0;
    double width = 0.0;
    double height = 0.0;
    double offsetX = 0.0;
    double offsetY = 0.0;
    bool isBlank = false;
};

/**
 * @brief Edge spacing information for layout nodes
 */
struct EdgesSpaces {
    double left = 0.0;
    double right = 0.0;
    double top = 0.0;
    double bottom = 0.0;
};

/**
 * @brief Expression and its corresponding value
 */
struct ExprAndValue {
    localsmt::Expr expr;
    double value = 0.0;
};

/**
 * @brief Node position with X and Y offsets
 */
struct NodePosition {
    ExprAndValue offsetX;
    ExprAndValue offsetY;
};

/**
 * @brief Node size with width and height
 */
struct NodeSize {
    ExprAndValue width;
    ExprAndValue height;
};

/**
 * @brief Scale information for space and size scaling
 */
struct ScaleInfo {
    ExprAndValue mainAxisSpaceScale;
    ExprAndValue crossAxisSpaceScale;
    ExprAndValue sizeScale;
};

/**
 * @brief Bounding box with position and size (decoupled from RectF)
 */
struct SmartLayoutRect {
    double offsetX = 0.0;
    double offsetY = 0.0;
    double width = 0.0;
    double height = 0.0;

    SmartLayoutRect() = default;
    SmartLayoutRect(double x, double y, double w, double h) : offsetX(x), offsetY(y), width(w), height(h) {}

    double Left() const { return offsetX; }
    double Top() const { return offsetY; }
    double Right() const { return offsetX + width; }
    double Bottom() const { return offsetY + height; }
    bool IsValid() const { return width > 0 && height > 0; }
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SMART_LAYOUT_SMART_LAYOUT_TYPES_H