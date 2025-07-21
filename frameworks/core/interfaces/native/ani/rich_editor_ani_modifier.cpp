/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
 
#include "image_ani_modifier.h"
 
#include "base/image/pixel_map.h"
#include "base/log/log.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/image/image_source_info.h"
 
namespace OHOS::Ace::NG {
ani_long TransferPixelMap(void* pixelMap)
{
    CHECK_NULL_RETURN(pixelMap, 0);
    auto pixelMapPtr = PixelMap::CreatePixelMap(pixelMap);
    if (!pixelMapPtr) {
        return 0;
    }
    pixelMapPtr->IncRefCount();
    return reinterpret_cast<ani_long>(AceType::RawPtr(pixelMapPtr));
}
 
const ArkUIAniRichEditorModifier* GetRichEditorAniModifier()
{
    static const ArkUIAniRichEditorModifier impl = {
        .transferPixelMap = OHOS::Ace::NG::TransferPixelMap
    };
    return &impl;
}
 
} // namespace OHOS::Ace::NG