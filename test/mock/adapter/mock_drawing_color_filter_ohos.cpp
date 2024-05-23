/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "adapter/ohos/osal/drawing_color_filter_ohos.h"

#include "core/components_ng/render/drawing_mock.h"

namespace OHOS::Ace {
RefPtr<DrawingColorFilter> DrawingColorFilter::CreateDrawingColorFilter(void* sptrAddr)
{
    return nullptr;
}

RefPtr<DrawingColorFilter> DrawingColorFilter::CreateDrawingColorFilter(const std::vector<float>& matrix)
{
    return nullptr;
}

RefPtr<DrawingColorFilter> DrawingColorFilter::CreateDrawingColorFilterFromNative(void* sptrAddr)
{
    return nullptr;
}

void* DrawingColorFilterOhos::GetDrawingColorFilterSptrAddr()
{
    auto colorFilter = std::make_shared<RSColorFilter>();
    return static_cast<void*>(&colorFilter);
}
} // namespace OHOS::Ace
