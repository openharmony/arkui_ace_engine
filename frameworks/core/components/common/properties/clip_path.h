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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_CLIP_PATH_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_CLIP_PATH_H

#include <string>
#include <vector>

#include "base/geometry/dimension.h"
#include "base/geometry/dimension_offset.h"
#include "base/geometry/shape.h"
#include "base/memory/ace_type.h"
#include "core/components/common/properties/color.h"

namespace OHOS::Ace {

enum class GeometryBoxType {
    NONE,
    MARGIN_BOX,
    BORDER_BOX,
    PADDING_BOX,
    CONTENT_BOX,
};


enum class LengthMode {
    HORIZONTAL,
    VERTICAL,
    OTHER,
};

class ACE_EXPORT ClipPath final : public AceType {
    DECLARE_ACE_TYPE(ClipPath, AceType);

public:
    ClipPath() = default;
    explicit ClipPath(const RefPtr<BasicShape>& basicShape) : basicShape_(basicShape) {}
    ClipPath(GeometryBoxType geometryBoxType, const RefPtr<BasicShape>& basicShape)
        : geometryBoxType_(geometryBoxType), basicShape_(basicShape)
    {}
    ~ClipPath() override = default;

    static GeometryBoxType GetGeometryBoxType(const std::string& value);
    static void GetBasicShapeInfo(const std::string& value, BasicShapeType& basicShapeType, std::string& data);
    static RefPtr<ClipPath> CreateShape(const std::string& value);

    void SetGeometryBoxType(GeometryBoxType geometryBoxType)
    {
        geometryBoxType_ = geometryBoxType;
    }

    GeometryBoxType GetGeometryBoxType() const
    {
        return geometryBoxType_;
    }

    void SetBasicShape(const RefPtr<BasicShape>& basicShape)
    {
        basicShape_ = basicShape;
    }

    const RefPtr<BasicShape>& GetBasicShape() const
    {
        return basicShape_;
    }

    bool NeedClip() const
    {
        return (basicShape_ && basicShape_->GetBasicShapeType() != BasicShapeType::NONE) ||
               geometryBoxType_ != GeometryBoxType::NONE;
    }

private:
    static RefPtr<Circle> CreateCircle(const std::string& data);
    static RefPtr<Ellipse> CreateEllipse(const std::string& data);
    static RefPtr<Ellipse> CreateEllipseSize(const std::string& data);
    static RefPtr<Inset> CreateInset(const std::string& data);
    static RefPtr<Inset> CreateInsetSize(const std::string& data);
    static RefPtr<Polygon> CreatePolygon(const std::string& value);
    static RefPtr<Path> CreatePath(const std::string& value);

    GeometryBoxType geometryBoxType_ = GeometryBoxType::NONE;
    RefPtr<BasicShape> basicShape_;
};

class ACE_EXPORT MaskPath final : public AceType {
    DECLARE_ACE_TYPE(MaskPath, AceType);

public:
    MaskPath() = default;
    explicit MaskPath(const RefPtr<BasicShape>& basicShape) : basicShape_(basicShape) {}
    MaskPath(GeometryBoxType geometryBoxType, const RefPtr<BasicShape>& basicShape)
        : geometryBoxType_(geometryBoxType), basicShape_(basicShape)
    {}
    ~MaskPath() override = default;

    void SetGeometryBoxType(GeometryBoxType geometryBoxType)
    {
        geometryBoxType_ = geometryBoxType;
    }

    GeometryBoxType GetGeometryBoxType() const
    {
        return geometryBoxType_;
    }

    void SetBasicShape(const RefPtr<BasicShape>& basicShape)
    {
        basicShape_ = basicShape;
    }

    const RefPtr<BasicShape>& GetBasicShape() const
    {
        return basicShape_;
    }

private:
    GeometryBoxType geometryBoxType_ = GeometryBoxType::NONE;
    RefPtr<BasicShape> basicShape_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_CLIP_PATH_H
