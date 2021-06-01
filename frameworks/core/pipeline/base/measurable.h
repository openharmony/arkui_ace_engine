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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_MEASURABLE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_MEASURABLE_H

#include "base/memory/ace_type.h"
#include "frameworks/base/geometry/dimension.h"

namespace OHOS::Ace {

class Measurable : public virtual AceType {
    DECLARE_ACE_TYPE(Measurable, AceType);

public:
    virtual const Dimension& GetWidth() const
    {
        return width_;
    }

    virtual void SetWidth(const Dimension& dimension)
    {
        width_ = dimension;
    }

    virtual void SetWidth(double width, DimensionUnit unit = DimensionUnit::PX)
    {
        width_ = Dimension(width, unit);
    }

    virtual const Dimension& GetHeight() const
    {
        return height_;
    }

    virtual void SetHeight(const Dimension& dimension)
    {
        height_ = dimension;
    }

    virtual void SetHeight(double height, DimensionUnit unit = DimensionUnit::PX)
    {
        height_ = Dimension(height, unit);
    }

protected:
    Dimension width_ {-1.0, DimensionUnit::PX};
    Dimension height_ {-1.0, DimensionUnit::PX};
};

}  // namespace OHOS::Ace

#endif  // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_MEASURABLE_H