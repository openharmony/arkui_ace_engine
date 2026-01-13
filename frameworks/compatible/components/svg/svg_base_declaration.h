/*
 * Copyright (c) 2021-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_SVG_SVG_BASE_DECLARATION_H
#define FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_SVG_SVG_BASE_DECLARATION_H

#include "core/components/common/properties/svg_paint_state.h"
#include "core/components/declaration/common/declaration.h"

namespace OHOS::Ace {

const char VALUE_NONE[] = "none";
ACE_EXPORT extern const char DOM_VALUE[];
ACE_EXPORT extern const char DOM_SVG_ID[];
ACE_EXPORT extern const char DOM_SVG_ANIMATION_BEGIN[];
ACE_EXPORT extern const char DOM_SVG_ANIMATION_DUR[];
ACE_EXPORT extern const char DOM_SVG_ANIMATION_END[];
ACE_EXPORT extern const char DOM_SVG_ANIMATION_MIN[];
ACE_EXPORT extern const char DOM_SVG_ANIMATION_MAX[];
ACE_EXPORT extern const char DOM_SVG_ANIMATION_RESTART[];
ACE_EXPORT extern const char DOM_SVG_ANIMATION_REPEAT_COUNT[];
ACE_EXPORT extern const char DOM_SVG_ANIMATION_REPEAT_DUR[];
ACE_EXPORT extern const char DOM_SVG_ANIMATION_FILL[];
ACE_EXPORT extern const char DOM_SVG_ANIMATION_CALC_MODE[];
ACE_EXPORT extern const char DOM_SVG_ANIMATION_VALUES[];
ACE_EXPORT extern const char DOM_SVG_ANIMATION_KEY_TIMES[];
ACE_EXPORT extern const char DOM_SVG_ANIMATION_KEY_SPLINES[];
ACE_EXPORT extern const char DOM_SVG_ANIMATION_FROM[];
ACE_EXPORT extern const char DOM_SVG_ANIMATION_TO[];
ACE_EXPORT extern const char DOM_SVG_ANIMATION_BY[];
ACE_EXPORT extern const char DOM_SVG_ANIMATION_ATTRIBUTE_NAME[];
ACE_EXPORT extern const char DOM_SVG_ANIMATION_ADDITIVE[];
ACE_EXPORT extern const char DOM_SVG_ANIMATION_ACCUMULATE[];
ACE_EXPORT extern const char DOM_SVG_ANIMATION_TYPE[];
ACE_EXPORT extern const char DOM_SVG_ANIMATION_KEY_POINTS[];
ACE_EXPORT extern const char DOM_SVG_ANIMATION_PATH[];
ACE_EXPORT extern const char DOM_SVG_ANIMATION_ROTATE[];
ACE_EXPORT extern const char DOM_SVG_ATTR_PATH[];
ACE_EXPORT extern const char DOM_SVG_START_OFFSET[];
ACE_EXPORT extern const char DOM_SVG_FILL[];
ACE_EXPORT extern const char DOM_SVG_FILL_OPACITY[];
ACE_EXPORT extern const char DOM_SVG_FILL_RULE[];
ACE_EXPORT extern const char DOM_SVG_FILTER[];
ACE_EXPORT extern const char DOM_SVG_FONT_FAMILY[];
ACE_EXPORT extern const char DOM_SVG_FONT_SIZE[];
ACE_EXPORT extern const char DOM_SVG_FONT_STYLE[];
ACE_EXPORT extern const char DOM_SVG_FONT_WEIGHT[];
ACE_EXPORT extern const char DOM_SVG_LETTER_SPACING[];
ACE_EXPORT extern const char DOM_SVG_MASK[];
ACE_EXPORT extern const char DOM_SVG_TEXT_DECORATION[];
ACE_EXPORT extern const char DOM_SVG_TEXT_LENGTH[];
ACE_EXPORT extern const char DOM_SVG_STROKE[];
ACE_EXPORT extern const char DOM_SVG_STROKE_DASHARRAY[];
ACE_EXPORT extern const char DOM_SVG_STROKE_DASHOFFSET[];
ACE_EXPORT extern const char DOM_SVG_STROKE_LINECAP[];
ACE_EXPORT extern const char DOM_SVG_STROKE_LINEJOIN[];
ACE_EXPORT extern const char DOM_SVG_STROKE_MITERLIMIT[];
ACE_EXPORT extern const char DOM_SVG_STROKE_OPACITY[];
ACE_EXPORT extern const char DOM_SVG_STROKE_WIDTH[];
ACE_EXPORT extern const char DOM_SVG_OPACITY[];
ACE_EXPORT extern const char DOM_SVG_VIEW_BOX[];
ACE_EXPORT extern const char DOM_SVG_X[];
ACE_EXPORT extern const char DOM_SVG_Y[];
ACE_EXPORT extern const char DOM_SVG_WIDTH[];
ACE_EXPORT extern const char DOM_SVG_HEIGHT[];
ACE_EXPORT extern const char DOM_SVG_DX[];
ACE_EXPORT extern const char DOM_SVG_DY[];
ACE_EXPORT extern const char DOM_SVG_RX[];
ACE_EXPORT extern const char DOM_SVG_RY[];
ACE_EXPORT extern const char DOM_SVG_D[];
ACE_EXPORT extern const char DOM_SVG_X1[];
ACE_EXPORT extern const char DOM_SVG_X2[];
ACE_EXPORT extern const char DOM_SVG_Y1[];
ACE_EXPORT extern const char DOM_SVG_Y2[];
ACE_EXPORT extern const char DOM_SVG_POINTS[];
ACE_EXPORT extern const char DOM_SVG_CX[];
ACE_EXPORT extern const char DOM_SVG_CY[];
ACE_EXPORT extern const char DOM_SVG_R[];
ACE_EXPORT extern const char DOM_SVG_ROTATE[];
ACE_EXPORT extern const char DOM_SVG_LENGTH_ADJUST[];
ACE_EXPORT extern const char DOM_SVG_MIRROR[];
ACE_EXPORT extern const char DOM_SVG_MASK_CONTENT_UNITS[];
ACE_EXPORT extern const char DOM_SVG_MASK_UNITS[];
ACE_EXPORT extern const char DOM_SVG_PATTERN_CONTENT_UNITS[];
ACE_EXPORT extern const char DOM_SVG_PATTERN_UNITS[];
ACE_EXPORT extern const char DOM_SVG_PATTERN_TRANSFORM[];
ACE_EXPORT extern const char DOM_SVG_OFFSET[];
ACE_EXPORT extern const char DOM_SVG_STOP_COLOR[];
ACE_EXPORT extern const char DOM_SVG_STOP_OPACITY[];
ACE_EXPORT extern const char DOM_SVG_GRADIENT_TRANSFORM[];
ACE_EXPORT extern const char DOM_SVG_SPREAD_METHOD[];
ACE_EXPORT extern const char DOM_SVG_FX[];
ACE_EXPORT extern const char DOM_SVG_FY[];
ACE_EXPORT extern const char DOM_SVG_FR[];
ACE_EXPORT extern const char DOM_SVG_HREF[];
ACE_EXPORT extern const char DOM_SVG_XLINK_HREF[];
ACE_EXPORT extern const char DOM_SVG_CLIP_RULE[];
ACE_EXPORT extern const char DOM_SVG_FE_IN[];
ACE_EXPORT extern const char DOM_SVG_FE_IN2[];
ACE_EXPORT extern const char DOM_SVG_FE_MODE[];
ACE_EXPORT extern const char DOM_SVG_FE_RESULT[];
ACE_EXPORT extern const char DOM_SVG_FE_COLOR_INTERPOLATION_FILTERS[];
ACE_EXPORT extern const char DOM_SVG_FE_TYPE[];
ACE_EXPORT extern const char DOM_SVG_FE_VALUES[];
ACE_EXPORT extern const char DOM_SVG_FE_FLOOD_COLOR[];
ACE_EXPORT extern const char DOM_SVG_FE_FLOOD_OPACITY[];
ACE_EXPORT extern const char DOM_SVG_FE_EDGE_MODE[];
ACE_EXPORT extern const char DOM_SVG_FE_STD_DEVIATION[];
ACE_EXPORT extern const char DOM_SVG_FE_AMPLITUDE[];
ACE_EXPORT extern const char DOM_SVG_FE_EXPONENT[];
ACE_EXPORT extern const char DOM_SVG_FE_INTERCEPT[];
ACE_EXPORT extern const char DOM_SVG_FE_SLOPE[];
ACE_EXPORT extern const char DOM_SVG_FE_TABLE_VALUES[];
ACE_EXPORT extern const char DOM_SVG_FE_K1[];
ACE_EXPORT extern const char DOM_SVG_FE_K2[];
ACE_EXPORT extern const char DOM_SVG_FE_K3[];
ACE_EXPORT extern const char DOM_SVG_FE_K4[];
ACE_EXPORT extern const char DOM_SVG_FE_OPERATOR_TYPE[];
ACE_EXPORT extern const char DOM_OVERFLOW_STYLE[];
ACE_EXPORT extern const char DOM_TRANSFORM[];
ACE_EXPORT extern const char DOM_ID[];
ACE_EXPORT extern const char DOM_CLIP_PATH[];

struct SvgBaseAttribute : Attribute {
    bool hasOpacity = false;
    double opacity = 1.0;
    FillState fillState;
    StrokeState strokeState;
    SvgTextStyle textStyle;
    std::string transform;
    std::string transformOrigin;
    std::string filterId;
    std::string maskId;
    std::string href;
    std::string id;
    ClipState clipState;

    void InheritFromUse(const SvgBaseAttribute& parent)
    {
        if (!hasOpacity) {
            if (parent.hasOpacity) {
                fillState.SetOpacity(parent.opacity);
                opacity = parent.opacity;
            } else {
                opacity = 1.0; // default opacity is 1.0
            }
        }
        fillState.Inherit(parent.fillState);
        strokeState.Inherit(parent.strokeState);
        clipState.Inherit(parent.clipState);
    }

    void Inherit(const SvgBaseAttribute& parent)
    {
        if (!hasOpacity) {
            if (parent.hasOpacity) {
                opacity = parent.opacity;
            } else {
                opacity = 1.0; // default opacity is 1.0
            }
        }
        fillState.Inherit(parent.fillState);
        strokeState.Inherit(parent.strokeState);
        clipState.Inherit(parent.clipState);
    }
};

class SvgBaseDeclaration : public Declaration {
    DECLARE_ACE_TYPE(SvgBaseDeclaration, Declaration);

public:
    SvgBaseDeclaration() = default;
    ~SvgBaseDeclaration() override = default;

    const FillState& GetFillState() const
    {
        auto& attribute = static_cast<SvgBaseAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
        return attribute.fillState;
    }

    const StrokeState& GetStrokeState() const
    {
        auto& attribute = static_cast<SvgBaseAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
        return attribute.strokeState;
    }

    const SvgTextStyle& GetSvgTextStyle() const
    {
        auto& attribute = static_cast<SvgBaseAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
        return attribute.textStyle;
    }

    const std::string& GetTransform() const
    {
        auto& attribute = static_cast<SvgBaseAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
        return attribute.transform;
    }

    const std::string& GetMaskId() const
    {
        auto& attribute = static_cast<SvgBaseAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
        return attribute.maskId;
    }

    const std::string& GetFilterId() const
    {
        auto& attribute = static_cast<SvgBaseAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
        return attribute.filterId;
    }

    const std::string& GetTransformOrigin() const
    {
        auto& attribute = static_cast<SvgBaseAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
        return attribute.transformOrigin;
    }

    bool HasOpacity() const
    {
        auto& attribute = static_cast<SvgBaseAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
        return attribute.hasOpacity;
    }

    double GetOpacity() const
    {
        auto& attribute = static_cast<SvgBaseAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
        return attribute.opacity;
    }

    void Inherit(const RefPtr<Declaration>& parent);

    void SetGradient(const Gradient& gradient)
    {
        auto& attribute = static_cast<SvgBaseAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
        attribute.fillState.SetGradient(gradient);
    }

    const std::string& GetClipPathHref() const
    {
        auto& attribute = static_cast<SvgBaseAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
        return attribute.clipState.GetHref();
    }

    void SetHref(const std::string& href)
    {
        auto& attribute = static_cast<SvgBaseAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
        attribute.href = href;
    }

    const std::string& GetHref() const
    {
        auto& attribute = static_cast<SvgBaseAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
        return attribute.href;
    }

    const ClipState& GetClipState() const
    {
        auto& attribute = static_cast<SvgBaseAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
        return attribute.clipState;
    }

    const std::string& GetId()
    {
        auto& commonAttr = MaybeResetAttribute<CommonAttribute>(AttributeTag::COMMON_ATTR);
        return commonAttr.id;
    }

    LineCapStyle GetLineCapStyle(const std::string& val) const;
    LineJoinStyle GetLineJoinStyle(const std::string& val) const;
    Color GetColor(const std::string& value) const;

    bool SetSpecializedAttr(const std::pair<std::string, std::string>& attr) override;

    void ReplaceAttributes(const SvgBaseAttribute& attr);

protected:
    void InitSpecialized() override;
    bool SetSpecializedStyle(const std::pair<std::string, std::string>& style) override;
    bool SetPresentationAttr(const std::pair<std::string, std::string>& attr);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_SVG_SVG_BASE_DECLARATION_H
