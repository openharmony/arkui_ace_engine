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

#ifndef FOUNDATION_ACE_TEST_MOCK_OHOS_MOCK_IMAGE_PIXEL_MAP_H
#define FOUNDATION_ACE_TEST_MOCK_OHOS_MOCK_IMAGE_PIXEL_MAP_H

namespace OHOS {
class MessageParcel;

namespace Media {
class PixelMap {
public:
    static PixelMap* Unmarshalling(MessageParcel& data)
    {
        return nullptr;
    }
};
} // namespace Media
} // namespace OHOS

#endif // FOUNDATION_ACE_TEST_MOCK_OHOS_MOCK_IMAGE_PIXEL_MAP_H
