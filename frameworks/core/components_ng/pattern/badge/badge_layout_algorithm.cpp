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

#include "core/components_ng/pattern/badge/badge_layout_algorithm.h"

#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/pattern/badge/badge_layout_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

constexpr Dimension NUMERICAL_BADGE_CIRCLE_SIZE = 16.0_vp;
constexpr Dimension NUMERICAL_BADGE_PADDING = 6.0_vp;
constexpr int MAX_COUNT = 99;

void BadgeLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto children = host->GetChildren();
    if (children.empty()) {
        LOGW("Badge has no child node.");
        return;
    }
    auto childrenSize = children.size();
    auto layoutProperty = AceType::DynamicCast<BadgeLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    auto constraint = layoutProperty->GetLayoutConstraint();
    auto idealSize = CreateIdealSize(constraint.value(), Axis::HORIZONTAL, layoutProperty->GetMeasureType(), true);
    if (GreatOrEqual(idealSize.Width(), Infinity<float>()) || GreatOrEqual(idealSize.Height(), Infinity<float>())) {
        LOGW("Size is infinity.");
        geometryNode->SetFrameSize(SizeF());
        return;
    }
    geometryNode->SetFrameSize(idealSize);
    geometryNode->SetContentSize(idealSize);
    auto childLayoutConstraint = layoutProperty->CreateChildConstraint();
    childLayoutConstraint.parentIdealSize = OptionalSizeF(idealSize);
    auto textWrapper = layoutWrapper->GetOrCreateChildByIndex(childrenSize - 1);
    if (textWrapper) {
        textWrapper->Measure(childLayoutConstraint);
    }

    auto circleSize = layoutProperty->GetBadgeCircleSize();
    auto badgeCircleDiameter = circleSize.has_value() ? (circleSize->IsValid() ? circleSize->ConvertToPx() : 0)
                                                      : NUMERICAL_BADGE_CIRCLE_SIZE.ConvertToPx();
    auto badgeWidth = 0.0;
    auto badgeHeight = badgeCircleDiameter;
    auto countLimit = layoutProperty->HasBadgeMaxCount() ? layoutProperty->GetBadgeMaxCountValue() : MAX_COUNT;
    auto badgeCircleRadius = badgeCircleDiameter / 2;

    auto textLayoutProperty = DynamicCast<TextLayoutProperty>(textWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(textLayoutProperty);
    auto textGeometryNode = textWrapper->GetGeometryNode();
    CHECK_NULL_VOID(textGeometryNode);

    auto textData = textLayoutProperty->GetContentValue();
    auto messageCount = textData.size();
    auto textSize = textGeometryNode->GetContentSize();

    if (!textData.empty() || messageCount > 0) {
        if ((textData.size() <= 1 && !textData.empty()) ||
            ((messageCount < 10 && messageCount <= countLimit) && textData.empty())) {
            badgeCircleRadius = badgeCircleDiameter / 2;
            badgeWidth = badgeCircleDiameter;
        } else if (textData.size() > 1 || messageCount > countLimit) {
            badgeWidth = textSize.Width() + NUMERICAL_BADGE_PADDING.ConvertToPx() * 2;
            badgeWidth = badgeCircleDiameter > badgeWidth ? badgeCircleDiameter : badgeWidth;
            badgeCircleRadius = badgeCircleDiameter / 2;
        }
    }

    textLayoutProperty->UpdateMarginSelfIdealSize(SizeF(badgeWidth, badgeHeight));
    auto textLayoutConstraint = childLayoutConstraint;
    textLayoutConstraint.selfIdealSize = OptionalSize<float>(badgeWidth, badgeHeight);
    textWrapper->Measure(textLayoutConstraint);

    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(childrenSize - 2);
    CHECK_NULL_VOID(childWrapper);
    childWrapper->Measure(childLayoutConstraint);
}

void BadgeLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto children = host->GetChildren();
    if (children.empty()) {
        LOGW("Badge has no child node.");
        return;
    }
    auto childrenSize = children.size();

    auto geometryNode = layoutWrapper->GetGeometryNode();
    auto parentSize = geometryNode->GetFrameSize();
    auto width = parentSize.Width();
    auto height = parentSize.Height();
    auto offset = geometryNode->GetFrameOffset();

    auto layoutProperty = DynamicCast<BadgeLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto badgePosition = layoutProperty->GetBadgePosition();
    auto circleSize = layoutProperty->GetBadgeCircleSize();
    auto badgeCircleDiameter = circleSize.has_value() ? (circleSize->IsValid() ? circleSize->ConvertToPx() : 0)
                                                      : NUMERICAL_BADGE_CIRCLE_SIZE.ConvertToPx();
    auto badgeWidth = 0.0;
    auto badgeCircleRadius = badgeCircleDiameter / 2;
    auto countLimit = layoutProperty->HasBadgeMaxCount() ? layoutProperty->GetBadgeMaxCountValue() : MAX_COUNT;

    auto textWrapper = layoutWrapper->GetOrCreateChildByIndex(childrenSize - 1);
    auto textLayoutProperty = DynamicCast<TextLayoutProperty>(textWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(textLayoutProperty);
    auto textGeometryNode = textWrapper->GetGeometryNode();
    CHECK_NULL_VOID(textGeometryNode);
    auto textData = textLayoutProperty->GetContentValue();
    auto messageCount = textData.size();
    auto textSize = textGeometryNode->GetContentSize();

    if (!textData.empty() || messageCount > 0) {
        if ((textData.size() <= 1 && !textData.empty()) ||
            ((messageCount < 10 && messageCount <= countLimit) && textData.empty())) {
            badgeCircleRadius = badgeCircleDiameter / 2;
            badgeWidth = badgeCircleDiameter;
        } else if (textData.size() > 1 || messageCount > countLimit) {
            badgeWidth = textSize.Width() + NUMERICAL_BADGE_PADDING.ConvertToPx() * 2;
            badgeWidth = badgeCircleDiameter > badgeWidth ? badgeCircleDiameter : badgeWidth;
            badgeCircleRadius = badgeCircleDiameter / 2;
        }
    }

    BorderRadiusProperty radius;
    radius.SetRadius(Dimension(badgeCircleRadius));
    auto textFrameNode = textWrapper->GetHostNode();
    CHECK_NULL_VOID(textFrameNode);
    auto textRenderContext = textFrameNode->GetRenderContext();
    CHECK_NULL_VOID(textRenderContext);
    textRenderContext->UpdateBorderRadius(radius);

    textLayoutProperty->UpdateAlignment(Alignment::CENTER);

    OffsetF textOffset;
    if (textData == " ") {
        if (badgePosition == BadgeLayoutProperty::BadgePosition::RIGHT_TOP) {
            textOffset = OffsetF(offset.GetX() + width - badgeCircleDiameter, offset.GetY());
        } else if (badgePosition == BadgeLayoutProperty::BadgePosition::RIGHT) {
            textOffset =
                OffsetF(offset.GetX() + width - badgeCircleDiameter, offset.GetY() + height / 2 - badgeCircleRadius);
        } else {
            textOffset = OffsetF(offset.GetX(), offset.GetY() + height / 2 - badgeCircleRadius);
        }
    } else {
        if (badgePosition == BadgeLayoutProperty::BadgePosition::RIGHT_TOP) {
            textOffset = OffsetF(width - badgeCircleDiameter + 3, 0 - 3);
            textOffset = OffsetF(offset.GetX() + textOffset.GetX(), offset.GetY() + textOffset.GetY());
        } else if (badgePosition == BadgeLayoutProperty::BadgePosition::RIGHT) {
            textOffset = OffsetF(width - badgeCircleDiameter, height / 2 - badgeCircleRadius);
            textOffset = OffsetF(offset.GetX() + textOffset.GetX(), offset.GetY() + textOffset.GetY());
        } else {
            textOffset = OffsetF(0, height / 2 - badgeCircleRadius);
            textOffset = OffsetF(offset.GetX(), offset.GetY() + textOffset.GetY());
        }
    }

    textGeometryNode->SetMarginFrameOffset(textOffset - geometryNode->GetFrameOffset());
    textWrapper->Layout();

    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(childrenSize - 2);
    CHECK_NULL_VOID(childWrapper);
    childWrapper->Layout();
}

} // namespace OHOS::Ace::NG
