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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTY_CLIP_PATH_H_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTY_CLIP_PATH_H_H

#include "core/components/common/properties/clip_path.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT ClipPathNG final {

public:
    ClipPathNG() = default;
    explicit ClipPathNG(const RefPtr<BasicShape>& basicShape) : basicShape_(basicShape) {}
    ClipPathNG(GeometryBoxType geometryBoxType, const RefPtr<BasicShape>& basicShape)
        : geometryBoxType_(geometryBoxType), basicShape_(basicShape)
    {}
    ~ClipPathNG() = default;

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

    bool operator==(const ClipPathNG& other) const
    {
        return (geometryBoxType_ == other.GetGeometryBoxType() &&
                basicShape_ == other.GetBasicShape());
    }

private:
    GeometryBoxType geometryBoxType_ = GeometryBoxType::NONE;
    RefPtr<BasicShape> basicShape_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTY_CLIP_PATH_H_H