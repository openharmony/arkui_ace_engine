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

#include "core/components/common/properties/border_image_edge.h"

namespace OHOS::Ace {
    BorderImageEdge::BorderImageEdge(const Dimension& slice, const Dimension& outset,
        const Dimension& width, BorderImageRepeat repeat)
        : borderImageSlice_(slice), borderImageOutset_(outset),
        borderImageWidth_(width), repeat_(repeat)
    {}

    bool BorderImageEdge::operator==(const BorderImageEdge& borderImageEdge) const
    {
        return NearEqual(borderImageEdge.GetBorderImageSlice().Value(), borderImageSlice_.Value())
               && (borderImageEdge.GetBorderImageSlice().Unit() == borderImageSlice_.Unit())
               && NearEqual(borderImageEdge.GetBorderImageOutset().Value(), borderImageOutset_.Value())
               && (borderImageEdge.GetBorderImageOutset().Unit() == borderImageOutset_.Unit())
               && NearEqual(borderImageEdge.GetBorderImageWidth().Value(), borderImageWidth_.Value())
               && (borderImageEdge.GetBorderImageWidth().Unit() == borderImageWidth_.Unit())
               && (borderImageEdge.GetBorderImageRepeat() == repeat_);
    }

    std::string BorderImageEdge::ToString()
    {
        return borderImageOutset_.ToString() + ", "+borderImageSlice_.ToString() +
            ", "+borderImageWidth_.ToString();
    }
} // namespace OHOS::Ace
