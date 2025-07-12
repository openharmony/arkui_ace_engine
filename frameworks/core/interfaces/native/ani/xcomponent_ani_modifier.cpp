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

#include "xcomponent_ani_modifier.h"

#include "base/log/log.h"
#include "core/components_ng/base/frame_node.h"
#ifdef XCOMPONENT_SUPPORTED
#include "core/components_ng/pattern/xcomponent/xcomponent_model_ng.h"
#endif

namespace OHOS::Ace::NG {

void SetXComponentControllerCallback(ArkUINodeHandle node,
    std::function<void(const std::string&)>&& onSurfaceCreated,
    std::function<void(const std::string&, float, float, float, float)>&& onSurfaceChanged,
    std::function<void(const std::string&)>&& onSurfaceDestroyed)
{
#ifdef XCOMPONENT_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto onSurfaceCreatedEvent = [onSurfaceCreated](const std::string& surfaceId, const std::string xcomponentId) {
        CHECK_NULL_VOID(onSurfaceCreated);
        onSurfaceCreated(surfaceId);
        TAG_LOGI(AceLogTag::ACE_XCOMPONENT, "XComponent[%{public}s] ControllerOnCreated surfaceId:%{public}s",
            xcomponentId.c_str(), surfaceId.c_str());
    };
    auto onSurfaceChangedEvent = [onSurfaceChanged](const std::string& surfaceId, const RectF& rect) {
        CHECK_NULL_VOID(onSurfaceChanged);
        onSurfaceChanged(surfaceId, rect.Width(), rect.Height(), rect.Left(), rect.Top());
    };
    auto onSurfaceDestroyedEvent = [onSurfaceDestroyed](const std::string& surfaceId, const std::string xcomponentId) {
        CHECK_NULL_VOID(onSurfaceDestroyed);
        onSurfaceDestroyed(surfaceId);
        TAG_LOGI(AceLogTag::ACE_XCOMPONENT, "XComponent[%{public}s] ControllerOnDestroyed surfaceId:%{public}s",
            xcomponentId.c_str(), surfaceId.c_str());
    };
    XComponentModelNG::SetControllerOnCreated(frameNode, std::move(onSurfaceCreatedEvent));
    XComponentModelNG::SetControllerOnChanged(frameNode, std::move(onSurfaceChangedEvent));
    XComponentModelNG::SetControllerOnDestroyed(frameNode, std::move(onSurfaceDestroyedEvent));
#endif
}

const ArkUIAniXComponentModifier* GetXComponentAniModifier()
{
    static const ArkUIAniXComponentModifier impl = {
        .setXComponentControllerCallback = OHOS::Ace::NG::SetXComponentControllerCallback
    };
    return &impl;
}

} // namespace OHOS::Ace::NG
