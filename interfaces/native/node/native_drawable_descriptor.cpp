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

#include "native_drawable_descriptor.h"



#include "node_extened.h"

extern "C" {

ArkUI_DrawableDescriptor* OH_ArkUI_CreateFromNapiDrawable(OHOS::Ace::Napi::DrawableDescriptor* napiDrawable)
{
    auto pixelMap = napiDrawable->GetPixelMap();
    auto drawable = std::make_shared<OHOS::Ace::Napi::DrawableDescriptor>(pixelMap);
    return new ArkUI_DrawableDescriptor { nullptr, nullptr, 0, drawable };
}

} // namespace OHOS::Ace::Drawable