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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_RECT_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_RECT_PATTERN_H

#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/shape/rect_paint_method.h"
#include "core/components_ng/pattern/shape/rect_paint_property.h"
#include "core/components_ng/pattern/shape/shape_pattern.h"

namespace OHOS::Ace::NG {

class RectPattern : public ShapePattern {
    DECLARE_ACE_TYPE(RectPattern, ShapePattern);

public:
    RectPattern() = default;
    ~RectPattern() override = default;
    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        if (!shapeOverlayModifier_) {
            shapeOverlayModifier_ = MakeRefPtr<ShapeOverlayModifier>();
        }
        return MakeRefPtr<RectPaintMethod>(GetAncestorPaintProperty(), shapeOverlayModifier_);
    }
    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<RectPaintProperty>();
    }

    void OnPixelRoundFinish(const SizeF& pixelGridRoundSize) override
    {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto geometryNode = host->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        auto pixelRoundContentOffset = geometryNode->GetPixelRoundContentOffset();
        auto pixelRoundContentSize = geometryNode->GetPixelRoundContentSize();
        auto rectPaintProperty = host->GetPaintProperty<RectPaintProperty>();
        CHECK_NULL_VOID(rectPaintProperty);
        rectPaintProperty->SetContentOffset(pixelRoundContentOffset);
        rectPaintProperty->SetContentSize(pixelRoundContentSize);
    }

    void UpdatePropertyImpl(const std::string& key, RefPtr<PropertyValueBase> value) override
    {
        ShapePattern::UpdatePropertyImpl(key, value);
        auto frameNode = GetHost();
        CHECK_NULL_VOID(frameNode);
        auto property = frameNode->GetPaintPropertyPtr<RectPaintProperty>();
        CHECK_NULL_VOID(property);
        using Handler = std::function<void(RectPaintProperty*, RefPtr<PropertyValueBase>, RefPtr<FrameNode>)>;
        static const std::unordered_map<std::string, Handler> handlers = {
            { "RectRadiusWidth",
                [](RectPaintProperty* prop, RefPtr<PropertyValueBase> value, RefPtr<FrameNode> frameNode) {
                    if (auto realValue = std::get_if<CalcDimension>(&(value->GetValue()))) {
                        Radius radius;
                        realValue->IsNegative() ? radius.SetX(Dimension(DEFAULT_RADIUS_VALUE))
                                                   : radius.SetX(*realValue);
                        radius.SetY(DEFAULT_RADIUS_INVALID);
                        prop->UpdateRadius(radius);
                    }
                } },
            { "RectRadiusHeight",
                [](RectPaintProperty* prop, RefPtr<PropertyValueBase> value, RefPtr<FrameNode> frameNode) {
                    if (auto realValue = std::get_if<CalcDimension>(&(value->GetValue()))) {
                        Radius radius;
                        realValue->IsNegative() ? radius.SetY(Dimension(DEFAULT_RADIUS_VALUE))
                                                   : radius.SetY(*realValue);
                        radius.SetX(DEFAULT_RADIUS_INVALID);
                        prop->UpdateRadius(radius);
                    }
                } },
            { "RectRadius",
                [](RectPaintProperty* prop, RefPtr<PropertyValueBase> value, RefPtr<FrameNode> frameNode) {
                    if (auto realValue = std::get_if<CalcDimension>(&(value->GetValue()))) {
                        auto radiusVal = *realValue;
                        Radius radius;
                        if (radiusVal.IsNegative()) {
                            radius.SetY(Dimension(DEFAULT_RADIUS_VALUE));
                            radius.SetX(Dimension(DEFAULT_RADIUS_VALUE));
                        } else {
                            radius.SetX(radiusVal);
                            radius.SetY(radiusVal);
                        }
                        prop->UpdateRadius(radius);
                    }
                } },
        };
        auto it = handlers.find(key);
        if (it != handlers.end()) {
            it->second(property, value, frameNode);
        }
        if (frameNode->GetRerenderable()) {
            frameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
    }

private:
    ACE_DISALLOW_COPY_AND_MOVE(RectPattern);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_RECT_PATTERN_H