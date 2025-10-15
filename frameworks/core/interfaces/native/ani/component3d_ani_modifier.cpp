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

#include "component3d_ani_modifier.h"

#include "base/log/log.h"
#if defined(MODEL_COMPONENT_SUPPORTED)
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/model/model_pattern.h"
#include "core/components_ng/pattern/model/model_view_ng.h"

namespace {
OHOS::Render3D::SurfaceType CheckModelType(int32_t modelType)
{
    OHOS::Render3D::SurfaceType surfaceType = OHOS::Render3D::SurfaceType::SURFACE_TEXTURE;
    switch (modelType) {
        case 0:
            surfaceType = OHOS::Render3D::SurfaceType::SURFACE_TEXTURE;
            break;
        case 1:
            surfaceType = OHOS::Render3D::SurfaceType::SURFACE_WINDOW;
            break;
        default:
            LOGE("Unexpected enum value in ModelType: %{public}d", modelType);
    }
    return surfaceType;
}
} // namespace
#endif

namespace OHOS::Ace::NG {
void SetScene(ArkUINodeHandle node, void* scene, int32_t modelType)
{
#if defined(MODEL_COMPONENT_SUPPORTED)
    LOGD("ace_lume frameNode setScene");
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(scene);

    Render3D::SurfaceType surfaceType = CheckModelType(modelType);
    std::string bundleName;
    std::string moduleName;
    auto sceneAdapter = *(reinterpret_cast<std::shared_ptr<Render3D::ISceneAdapter>*>(scene));

    ModelViewNG::SetModelViewContext(frameNode, { bundleName, moduleName, surfaceType, sceneAdapter });
#endif
}

void SetWidget(ArkUINodeHandle node, const std::string& srcPath, int32_t modelType)
{
#if defined(MODEL_COMPONENT_SUPPORTED)
    LOGD("ace_lume frameNode setWidget");
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    Render3D::SurfaceType surfaceType = CheckModelType(modelType);
    std::string bundleName;
    std::string moduleName;

    ModelViewNG::SetModelViewContext(frameNode, { bundleName, moduleName, surfaceType, nullptr });
    std::string ohosPath = "OhosRawFile://" + srcPath;
    ModelViewNG::SetModelSource(frameNode, ohosPath);
#endif
}

const ArkUIAniComponent3DModifier* GetComponent3DModifier()
{
    static const ArkUIAniComponent3DModifier impl = {
        .setScene = OHOS::Ace::NG::SetScene,
        .setWidget = OHOS::Ace::NG::SetWidget,
    };
    return &impl;
}
} // namespace OHOS::Ace::NG