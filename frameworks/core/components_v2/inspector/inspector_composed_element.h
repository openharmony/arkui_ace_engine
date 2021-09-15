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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_INSPECTOR_INSPECTOR_COMPOSED_ELEMENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_INSPECTOR_INSPECTOR_COMPOSED_ELEMENT_H

#include <tuple>

#include "base/geometry/dimension_offset.h"
#include "base/geometry/matrix4.h"
#include "base/json/json_util.h"
#include "core/animation/animatable_transform_operation.h"
#include "core/components/box/mask.h"
#include "core/components/box/render_box.h"
#include "core/components/common/layout/grid_column_info.h"
#include "core/components/common/properties/clip_path.h"
#include "core/components/display/display_component.h"
#include "core/pipeline/base/composed_element.h"

namespace OHOS::Ace::V2 {

class InspectorComposedElement;

using DoubleJsonFunc = std::function<double(const InspectorComposedElement&)>;
using StringJsonFunc = std::function<std::string(const InspectorComposedElement&)>;
using BoolJsonFunc = std::function<bool(const InspectorComposedElement&)>;
using IntJsonFunc = std::function<int32_t(const InspectorComposedElement&)>;
using JsonValueJsonFunc = std::function<std::unique_ptr<JsonValue>(const InspectorComposedElement&)>;

struct RotateParam {
    float x;
    float y;
    float z;
    float angle;
    Dimension centerX;
    Dimension centerY;
};

struct ScaleParam {
    float x;
    float y;
    float z;
    Dimension centerX;
    Dimension centerY;
};

class ACE_EXPORT InspectorComposedElement : public ComposedElement {
    DECLARE_ACE_TYPE(InspectorComposedElement, ComposedElement)

public:
    explicit InspectorComposedElement(const ComposeId& id) : ComposedElement(id) {}
    ~InspectorComposedElement() override = default;

    bool CanUpdate(const RefPtr<Component>& newComponent) override;
    RefPtr<RenderNode> GetInspectorNode(IdType typeId) const;

    template<class T>
    RefPtr<T> GetContentElement(IdType typeId) const
    {
        auto child = children_.empty() ? nullptr : children_.front();
        while (child) {
            if (AceType::TypeId(child) == typeId) {
                return AceType::DynamicCast<T>(child);
            }
            child = child->GetChildren().empty() ? nullptr : child->GetChildren().front();
        }
        return nullptr;
    }

    template<class T>
    RefPtr<T> GetContentRender(IdType typeId) const
    {
        auto child = children_.empty() ? nullptr : children_.front();
        while (child) {
            if (AceType::TypeId(child) == typeId) {
                return AceType::DynamicCast<T>(child->GetRenderNode());
            }
            child = child->GetChildren().empty() ? nullptr : child->GetChildren().front();
        }
        return nullptr;
    }

    // dimension settings
    virtual double GetWidth() const;
    virtual double GetHeight() const;
    virtual Dimension GetPadding(OHOS::Ace::AnimatableType type) const;
    virtual Dimension GetMargin(OHOS::Ace::AnimatableType type) const;
    virtual std::string GetConstraintSize() const;
    virtual int32_t GetLayoutPriority() const;
    virtual int32_t GetLayoutWeight() const;

    // position settings
    virtual std::string GetAlign() const;
    virtual TextDirection GetDirection() const;
    virtual std::unique_ptr<JsonValue> GetPosition() const;
    virtual std::unique_ptr<JsonValue> GetOffset() const;
    virtual std::string GetRect() const;
    virtual Rect GetParentRect() const;

    // layout constraint
    virtual double GetAspectRatio() const;
    virtual int32_t GetDisplayPriority() const;

    // flex layout
    virtual double GetFlexBasis() const;
    virtual double GetFlexGrow() const;
    virtual double GetFlexShrink() const;
    virtual std::string GetAlignSelf() const;

    // border settings
    virtual Border GetBorder() const;
    virtual std::string GetBorderStyle() const;
    virtual std::string GetBorderWidth() const;
    virtual uint32_t GetBorderColor() const;

    // background settings
    virtual RefPtr<Decoration> GetBackDecoration() const;
    virtual std::string GetBackgroundImage() const;
    virtual std::unique_ptr<JsonValue> GetBackgroundImageSize() const;
    virtual std::unique_ptr<JsonValue> GetBackgroundImagePosition() const;

    // front decoration settings
    virtual RefPtr<Decoration> GetFrontDecoration() const;

    // opacity settings
    virtual double GetOpacity() const;

    // visibility settings
    virtual std::string GetVisibility() const;

    // enable settings
    virtual bool GetEnabled() const;

    // zindex settings
    virtual int32_t GetZIndex() const;

    // graphical transformation
    virtual DimensionOffset GetOriginPoint() const;
    virtual std::unique_ptr<JsonValue> GetTransformEffect() const;

    virtual double GetBlur() const;
    virtual double GetBackDropBlur() const;
    virtual std::unique_ptr<JsonValue> GetWindowBlur() const;
    virtual std::unique_ptr<JsonValue> GetShadow() const;

    // shape clip
    virtual RefPtr<ClipPath> GetClip() const;
    virtual bool GetBoxClipFlag() const;
    virtual RefPtr<Mask> GetMask() const;

    // grid setting
    virtual int32_t GetGridSpan() const;
    virtual int32_t GetGridOffset() const;
    virtual std::unique_ptr<JsonValue> GetUseSizeType() const;
    virtual RefPtr<GridColumnInfo> GetGridColumnInfo() const;

    virtual std::unique_ptr<JsonValue> ToJsonObject() const;
    virtual AceType::IdType GetTargetTypeId() const
    {
        return AceType::TypeId(this);
    }

private:
    RefPtr<RenderBox> GetRenderBox() const;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_INSPECTOR_INSPECTOR_COMPOSED_ELEMENT_H