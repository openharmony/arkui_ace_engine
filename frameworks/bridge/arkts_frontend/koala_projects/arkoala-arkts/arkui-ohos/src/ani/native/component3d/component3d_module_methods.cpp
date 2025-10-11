/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "component3d_module_methods.h"

#include "base/utils/utils.h"
#include "load.h"
#include "utils/ani_utils.h"

#if defined(MODEL_COMPONENT_SUPPORTED)
#include "scene_adapter/scene_bridge_ani.h"
#endif

namespace OHOS::Ace::Ani {
void Component3DSetScene(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_object node, ani_object sceneObj, ani_int modelType)
{
#if defined(MODEL_COMPONENT_SUPPORTED)
    CHECK_NULL_VOID(env);
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(node);
    CHECK_NULL_VOID(arkNode);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto modifier3D = modifier->getComponent3DModifier();
    CHECK_NULL_VOID(modifier3D);

    auto scene = Render3D::SceneBridgeAni::UnwrapSceneFromAni(env, sceneObj);
    modifier3D->setScene(arkNode, scene, static_cast<int32_t>(modelType));
#endif
}

void Component3DSetWidget(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_object node, ani_string scenePath, ani_int modelType)
{
#if defined(MODEL_COMPONENT_SUPPORTED)
    CHECK_NULL_VOID(env);
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(node);
    CHECK_NULL_VOID(arkNode);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto modifier3D = modifier->getComponent3DModifier();
    CHECK_NULL_VOID(modifier3D);

    std::string str = AniUtils::ANIStringToStdString(env, scenePath);
    modifier3D->setWidget(arkNode, str, static_cast<int32_t>(modelType));
#endif
}

ani_long ExtractorsToScenePtr(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_object sceneObj)
{
#if defined(MODEL_COMPONENT_SUPPORTED)
    CHECK_NULL_RETURN(env, 0);
    auto sceneAdapterPtr = Render3D::SceneBridgeAni::UnwrapSceneFromAni(env, sceneObj);
    return reinterpret_cast<ani_long>(sceneAdapterPtr);
#else
    return 0;
#endif // MODEL_COMPONENT_SUPPORTED
}
} // namespace OHOS::Ace::Ani