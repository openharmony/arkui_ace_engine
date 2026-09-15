/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_DM_FOLD_SCREEN_INFO_H
#define FOUNDATION_DM_FOLD_SCREEN_INFO_H

#include <cstdint>
#include <vector>

#include "refbase.h"

namespace OHOS::Rosen {
struct DMRect {
    int32_t posX_ = 0;
    int32_t posY_ = 0;
    uint32_t width_ = 0;
    uint32_t height_ = 0;
};

class FoldCreaseRegion : public OHOS::RefBase {
public:
    FoldCreaseRegion() = default;
    ~FoldCreaseRegion() = default;

    void SetCreaseRects(const std::vector<DMRect>& creaseRects)
    {
        creaseRects_ = creaseRects;
    }

    std::vector<DMRect> GetCreaseRects() const
    {
        return creaseRects_;
    }

private:
    std::vector<DMRect> creaseRects_;
};
} // namespace OHOS::Rosen
#endif // FOUNDATION_DM_FOLD_SCREEN_INFO_H
