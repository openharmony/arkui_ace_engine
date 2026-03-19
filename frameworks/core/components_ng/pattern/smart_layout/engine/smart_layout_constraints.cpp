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

#include "smart_layout_constraints.h"

namespace OHOS::Ace::NG {

void SmartLayoutConstraints::AddSizeScaleConstraint(SmartLayoutNode& parent,
    double sumOfAllChildHeight, double maxChildWidth)
{
    auto* engine = parent.GetEngine();
    if (engine == nullptr || sumOfAllChildHeight <= 0 || maxChildWidth <= 0) {
        return;
    }
    const auto& context = parent.GetContext();

    double sizeScale = 1.0;
    bool heightOverflow = sumOfAllChildHeight > context.size.Height();
    bool widthOverflow = maxChildWidth > context.size.Width();
    if (heightOverflow && !widthOverflow) {
        sizeScale = context.size.Height() / sumOfAllChildHeight;
    } else if (!heightOverflow && widthOverflow) {
        sizeScale = context.size.Width() / maxChildWidth;
    } else if (heightOverflow && widthOverflow) {
        double heightScale = context.size.Height() / sumOfAllChildHeight;
        double widthScale = context.size.Width() / maxChildWidth;
        sizeScale = std::min(heightScale, widthScale);
    }

    engine->Add(parent.GetScaleInfo().sizeScale.expr == sizeScale);
}

void SmartLayoutConstraints::AddRowSizeScaleConstraint(SmartLayoutNode& parent,
    double sumOfAllChildWidth, double maxChildHeight)
{
    auto* engine = parent.GetEngine();
    if (engine == nullptr || sumOfAllChildWidth <= 0 || maxChildHeight <= 0) {
        return;
    }
    const auto& context = parent.GetContext();

    double sizeScale = 1.0;
    bool widthOverflow = sumOfAllChildWidth > context.size.Width();
    bool heightOverflow = maxChildHeight > context.size.Height();
    if (widthOverflow && !heightOverflow) {
        sizeScale = context.size.Width() / sumOfAllChildWidth;
    } else if (!widthOverflow && heightOverflow) {
        sizeScale = context.size.Height() / maxChildHeight;
    } else if (widthOverflow && heightOverflow) {
        double widthScale = context.size.Width() / sumOfAllChildWidth;
        double heightScale = context.size.Height() / maxChildHeight;
        sizeScale = std::min(widthScale, heightScale);
    }

    engine->Add(parent.GetScaleInfo().sizeScale.expr == sizeScale);
}

void SmartLayoutConstraints::AddChildSizeConstraints(SmartLayoutNode& parent, SmartLayoutNode& child)
{
    auto* engine = parent.GetEngine();
    if (engine == nullptr) {
        return;
    }
    const auto& scaleInfo = parent.GetScaleInfo();

    engine->Add(child.GetSize().width.expr == child.GetSize().width.value * scaleInfo.sizeScale.expr);
    engine->Add(child.GetSize().height.expr == child.GetSize().height.value * scaleInfo.sizeScale.expr);
}

void SmartLayoutConstraints::AddCrossAxisAlignmentConstraint(SmartLayoutNode& parent, SmartLayoutNode& child,
    bool isRow)
{
    auto* engine = parent.GetEngine();
    if (engine == nullptr) {
        return;
    }
    const auto& context = parent.GetContext();

    // For column: cross axis is X (width); for row: cross axis is Y (height)
    auto& childOffset = isRow ? child.GetPosition().offsetY : child.GetPosition().offsetX;
    auto& childSize = isRow ? child.GetSize().height : child.GetSize().width;
    auto& parentOffset = isRow ? parent.GetPosition().offsetY : parent.GetPosition().offsetX;
    auto& parentSize = isRow ? parent.GetSize().height : parent.GetSize().width;

    if (context.crossAxisAlign == SmartLayoutAlign::FLEX_START) {
        engine->Add(childOffset.expr == parentOffset.expr);
    } else if (context.crossAxisAlign == SmartLayoutAlign::FLEX_END) {
        engine->Add(childOffset.expr + childSize.expr == parentOffset.expr + parentSize.expr);
    } else { // CENTER
        engine->Add(childOffset.expr - parentOffset.expr == parentSize.expr - childOffset.expr - childSize.expr);
    }
}

void SmartLayoutConstraints::AddChildMainAxisPosition(SmartLayoutNode& parent, SmartLayoutNode& child,
    SmartLayoutNode* prev, size_t index, bool isRow)
{
    auto* engine = parent.GetEngine();
    if (engine == nullptr) {
        return;
    }
    const auto& scaleInfo = parent.GetScaleInfo();

    // For column: main axis is Y (vertical); for row: main axis is X (horizontal)
    auto& childOffset = isRow ? child.GetPosition().offsetX : child.GetPosition().offsetY;
    auto& parentOffset = isRow ? parent.GetPosition().offsetX : parent.GetPosition().offsetY;
    auto& childSpace = isRow ? child.GetSpace().left : child.GetSpace().top;

    if (index == 0) {
        engine->Add(childOffset.expr == parentOffset.expr + childSpace * scaleInfo.mainAxisSpaceScale.expr);
    } else if (prev != nullptr) {
        auto& prevOffset = isRow ? prev->GetPosition().offsetX : prev->GetPosition().offsetY;
        auto& prevSize = isRow ? prev->GetSize().width : prev->GetSize().height;
        auto& prevSpace = isRow ? prev->GetSpace().right : prev->GetSpace().bottom;
        engine->Add(childOffset.expr == prevOffset.expr + prevSize.expr +
            prevSpace * scaleInfo.mainAxisSpaceScale.expr);
    }
}

void SmartLayoutConstraints::AddColumnConstraints(SmartLayoutNode& parent)
{
    auto* engine = parent.GetEngine();
    if (engine == nullptr) {
        return;
    }
    AddDefaultConstraints(parent);

    double sumOfAllChildHeight = GetSumOfAllChildHeight(parent);
    double maxChildWidth = GetMaxWidthOfAllChild(parent);
    if (sumOfAllChildHeight == 0 || maxChildWidth == 0) {
        return;
    }

    AddSizeScaleConstraint(parent, sumOfAllChildHeight, maxChildWidth);

    engine->Add(parent.GetScaleInfo().mainAxisSpaceScale.expr >= 0.0);
    engine->Add(parent.GetScaleInfo().mainAxisSpaceScale.expr <= 1.0);

    const auto& children = parent.GetChildren();
    for (size_t i = 0; i < children.size(); ++i) {
        auto& child = children[i];
        if (child == nullptr) {
            continue;
        }

        AddChildSizeConstraints(parent, *child);
        AddCrossAxisAlignmentConstraint(parent, *child, false);

        SmartLayoutNode* prev = (i > 0) ? children[i - 1].get() : nullptr;
        AddChildMainAxisPosition(parent, *child, prev, i, false);
    }
}

void SmartLayoutConstraints::AddRowConstraints(SmartLayoutNode& parent)
{
    auto* engine = parent.GetEngine();
    if (engine == nullptr) {
        return;
    }
    AddDefaultConstraints(parent);

    double sumOfAllChildWidth = GetSumOfAllChildWidth(parent);
    double maxChildHeight = GetMaxHeightOfAllChild(parent);
    if (sumOfAllChildWidth == 0 || maxChildHeight == 0) {
        return;
    }

    AddRowSizeScaleConstraint(parent, sumOfAllChildWidth, maxChildHeight);

    engine->Add(parent.GetScaleInfo().mainAxisSpaceScale.expr >= 0.0);
    engine->Add(parent.GetScaleInfo().mainAxisSpaceScale.expr <= 1.0);

    const auto& children = parent.GetChildren();
    for (size_t i = 0; i < children.size(); ++i) {
        auto& child = children[i];
        if (child == nullptr) {
            continue;
        }

        AddChildSizeConstraints(parent, *child);
        AddCrossAxisAlignmentConstraint(parent, *child, true);

        SmartLayoutNode* prev = (i > 0) ? children[i - 1].get() : nullptr;
        AddChildMainAxisPosition(parent, *child, prev, i, true);
    }
}

void SmartLayoutConstraints::AddDefaultConstraints(SmartLayoutNode& parent)
{
    auto* engine = parent.GetEngine();
    if (engine == nullptr) {
        return;
    }

    // Ensure parent non-negative
    engine->Add(parent.GetSize().width.expr >= 0.0);
    engine->Add(parent.GetSize().height.expr >= 0.0);
    engine->Add(parent.GetPosition().offsetX.expr == 0.0);
    engine->Add(parent.GetPosition().offsetY.expr == 0.0);

    // For every direct child, ensure size/offset non-negative and child is inside parent
    for (const auto& child : parent.GetChildren()) {
        // non-negativity for child
        engine->Add(child->GetSize().width.expr >= 0.0);
        engine->Add(child->GetSize().height.expr >= 0.0);
        engine->Add(child->GetPosition().offsetX.expr >= 0.0);
        engine->Add(child->GetPosition().offsetY.expr >= 0.0);

        // child offset must be no less than parent offset (stay inside)
        engine->Add(child->GetPosition().offsetX.expr >= parent.GetPosition().offsetX.expr);
        engine->Add(child->GetPosition().offsetY.expr >= parent.GetPosition().offsetY.expr);

        // child end (offset + size) must not exceed parent end (parent offset + parent size)
        engine->Add(child->GetPosition().offsetX.expr + child->GetSize().width.expr <=
                           parent.GetPosition().offsetX.expr + parent.GetSize().width.expr);
        engine->Add(child->GetPosition().offsetY.expr + child->GetSize().height.expr <=
                           parent.GetPosition().offsetY.expr + parent.GetSize().height.expr);
    }
}

double SmartLayoutConstraints::GetSumOfAllChildHeight(const SmartLayoutNode& parent)
{
    double sumOfAllChildHeight = 0.0;
    for (const auto& c : parent.GetChildren()) {
        if (c != nullptr) {
            sumOfAllChildHeight += c->GetSize().height.value;
        }
    }
    return sumOfAllChildHeight;
}

double SmartLayoutConstraints::GetSumOfAllChildWidth(const SmartLayoutNode& parent)
{
    double sumOfAllChildWidth = 0.0;
    for (const auto& c : parent.GetChildren()) {
        if (c != nullptr) {
            sumOfAllChildWidth += c->GetSize().width.value;
        }
    }
    return sumOfAllChildWidth;
}

double SmartLayoutConstraints::GetMaxWidthOfAllChild(const SmartLayoutNode& parent)
{
    double maxWidth = 0.0;
    for (const auto& c : parent.GetChildren()) {
        if (c != nullptr) {
            maxWidth = std::max(maxWidth, c->GetSize().width.value);
        }
    }
    return maxWidth;
}

double SmartLayoutConstraints::GetMaxHeightOfAllChild(const SmartLayoutNode& parent)
{
    double maxHeight = 0.0;
    for (const auto& c : parent.GetChildren()) {
        if (c != nullptr) {
            maxHeight = std::max(maxHeight, c->GetSize().height.value);
        }
    }
    return maxHeight;
}

} // namespace OHOS::Ace::NG