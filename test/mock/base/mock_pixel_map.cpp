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
#include "mock_pixel_map.h"

#include "base/memory/ace_type.h"

namespace OHOS::Ace {
RefPtr<PixelMap> PixelMap::CreatePixelMap(void* /*rawPtr*/)
{
    return AceType::MakeRefPtr<MockPixelMap>();
}

RefPtr<PixelMap> PixelMap::DecodeTlv(std::vector<uint8_t>& buff)
{
    return AceType::MakeRefPtr<MockPixelMap>();
}

RefPtr<PixelMap> PixelMap::CreatePixelMapFromDataAbility(void* /*rawPtr*/)
{
    return AceType::MakeRefPtr<MockPixelMap>();
}

void* PixelMap::GetReleaseContext(const RefPtr<PixelMap>& pixelMap)
{
    return nullptr;
}

void PixelMap::ReleaseProc(const void* /* pixels */, void* context)
{
}
} // namespace OHOS::Ace
