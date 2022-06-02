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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_GEOMETRY_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_GEOMETRY_PROPERTY_H

#include "base/geometry/ng/rect_t.h"

namespace OHOS::Ace::NG {
class GeometryProperty {
public:
    GeometryProperty() = default;
    ~GeometryProperty() = default;

    bool operator==(const GeometryProperty& value)
    {
        return rect_ == value.rect_;
    }

    void Reset()
    {
        rect_.Reset();
    }

    const RectF& GetRect() const
    {
        return rect_;
    }

    void SetSize(const SizeF& size)
    {
        rect_.SetSize(size);
    }

    void SetOffset(const OffsetF& offset)
    {
        rect_.SetOffset(offset);
    }

    std::string ToString() const
    {
        return rect_.ToString();
    }

private:
    RectF rect_;
    friend class GeometryNode;
    friend class FrameProperty;
    friend class LayoutBox;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_GEOMETRY_PROPERTY_H