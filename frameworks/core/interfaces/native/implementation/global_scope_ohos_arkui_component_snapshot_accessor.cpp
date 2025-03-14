/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/implementation/pixel_map_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "frameworks/base/error/error_code.h"
#include "frameworks/core/components_ng/render/adapter/component_snapshot.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG {
namespace Converter {
template<>
SnapshotOptions Convert(const Ark_SnapshotOptions& src)
{
    SnapshotOptions ret;
    ret.scale = Converter::OptConvert<float>(src.scale).value_or(1.0f);
    ret.waitUntilRenderFinished = Converter::OptConvert<bool>(src.waitUntilRenderFinished).value_or(false);
    return ret;
}
}
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace GlobalScope_ohos_arkui_componentSnapshotAccessor {
void GetImpl(const Ark_String* id,
             const AsyncCallback_image_PixelMap_Void* callback,
             const Opt_SnapshotOptions* options)
{
    CHECK_NULL_VOID(id);
    CHECK_NULL_VOID(callback);
    auto opts = options ? Converter::OptConvert<SnapshotOptions>(*options) : std::nullopt;
    auto componentId = Converter::Convert<std::string>(*id);
    auto onDone = [arkCallback = CallbackHelper(*callback)](
        std::shared_ptr<Media::PixelMap> mediaPixelMap, int32_t errorCode, std::function<void()> inCallback) {
        if (errorCode != ERROR_CODE_NO_ERROR || !mediaPixelMap) {
            return;
        }
        RefPtr<PixelMap> pixelMapRef = PixelMap::CreatePixelMap(&mediaPixelMap);
        static PixelMapPeer peer;
        peer.pixelMap = pixelMapRef;
        arkCallback.Invoke(&peer);
    };
    ComponentSnapshot::Get(componentId, std::move(onDone), opts.value_or(SnapshotOptions()));
}
} // GlobalScope_ohos_arkui_componentSnapshotAccessor
const GENERATED_ArkUIGlobalScope_ohos_arkui_componentSnapshotAccessor* GetGlobalScope_ohos_arkui_componentSnapshotAccessor()
{
    static const GENERATED_ArkUIGlobalScope_ohos_arkui_componentSnapshotAccessor GlobalScope_ohos_arkui_componentSnapshotAccessorImpl {
        GlobalScope_ohos_arkui_componentSnapshotAccessor::GetImpl,
    };
    return &GlobalScope_ohos_arkui_componentSnapshotAccessorImpl;
}

}
