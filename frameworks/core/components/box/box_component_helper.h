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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BOX_BOX_COMPONENT_HELPER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BOX_BOX_COMPONENT_HELPER_H

#include "core/components/common/properties/color.h"
#include "core/components/common/properties/decoration.h"

// Helper class for updating of the attributes for Box Component
// Used by RenderBox and by JSViewAbstract

namespace OHOS::Ace {
class BoxComponentHelper {
public:
    static void SetBorderColor(
        RefPtr<Decoration>& backDecoration, const Color& color, const AnimationOption& option = AnimationOption())
    {
        if (!backDecoration) {
            backDecoration = AceType::MakeRefPtr<Decoration>();
        }
        Border border = backDecoration->GetBorder();
        BorderEdge edge;
        edge = border.Left();
        edge.SetColor(color, option);

        border.SetLeftEdge(edge);
        border.SetRightEdge(edge);
        border.SetTopEdge(edge);
        border.SetBottomEdge(edge);
        backDecoration->SetBorder(border);
    }

    static void SetBorderRadius(
        RefPtr<Decoration>& backDecoration, const Dimension& radius, const AnimationOption& option = AnimationOption())
    {
        if (!backDecoration) {
            backDecoration = AceType::MakeRefPtr<Decoration>();
        }
        Border border = backDecoration->GetBorder();
        border.SetBorderRadius(Radius(AnimatableDimension(radius, option)));
        backDecoration->SetBorder(border);
    }

    static void SetBorderStyle(RefPtr<Decoration>& backDecoration, BorderStyle style)
    {
        if (!backDecoration) {
            backDecoration = AceType::MakeRefPtr<Decoration>();
        }
        Border border = backDecoration->GetBorder();
        auto edge = border.Left();

        edge.SetStyle(style);
        border.SetLeftEdge(edge);
        border.SetRightEdge(edge);
        border.SetTopEdge(edge);
        border.SetBottomEdge(edge);

        backDecoration->SetBorder(border);
    }

    static void SetBorderWidth(
        RefPtr<Decoration>& backDecoration, const Dimension& width, const AnimationOption& option = AnimationOption())
    {
        if (!backDecoration) {
            backDecoration = AceType::MakeRefPtr<Decoration>();
        }
        Border border = backDecoration->GetBorder();
        border.SetWidth(width, option);
        backDecoration->SetBorder(border);
    }
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BOX_BOX_COMPONENT_HELPER_H
