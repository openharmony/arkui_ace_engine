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

import { ArkUIAniModule } from "arkui.ani"

function GetStrFromResource(scene_Resource: Resource): string {
    let resStr: string = ''
    let params_type: int32 = RuntimeType.UNDEFINED
    params_type = runtimeType(scene_Resource.params)
    if ((RuntimeType.UNDEFINED) != (params_type)) {
        const params_value = scene_Resource.params!
        if (params_value.length > 0) {
            let params_0_type: int32 = RuntimeType.UNDEFINED
            params_0_type = runtimeType(params_value[0])
            if ((RuntimeType.UNDEFINED) != (params_0_type)) {
                resStr = params_value[0] as string
            }
        }
    }
    return resStr
}

function hookSetComponent3DOptions(component: ArkComponent3DComponent, value?: SceneOptions): void {
    const peer = component.getPeer()
    if (peer !== undefined) {
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const sceneOptions_value = value!

            let modelType_type: int32 = RuntimeType.UNDEFINED
            let modelType_value = ModelType.SURFACE
            modelType_type = runtimeType(sceneOptions_value.modelType)
            if ((RuntimeType.UNDEFINED) != (modelType_type)) {
                modelType_value = (sceneOptions_value.modelType as ModelType)
            }
            const modelType_Num = TypeChecker.ModelType_ToNumeric(modelType_value) as int32

            let scene_type: int32 = RuntimeType.UNDEFINED
            scene_type = runtimeType(sceneOptions_value.scene)
            if (sceneOptions_value.scene instanceof Scene) {
                const scene_Scene: Scene = sceneOptions_value.scene as Scene
                ArkUIAniModule._Component3D_SetScene(peer.getPeerPtr() as KPointer, scene_Scene, modelType_Num)
                return
            } else if (RuntimeType.STRING == scene_type) {
                const scene_string: string = sceneOptions_value.scene as string
                ArkUIAniModule._Component3D_SetWidget(peer.getPeerPtr() as KPointer, scene_string, modelType_Num)
                return
            } else if (RuntimeType.OBJECT == scene_type) {
                const scene_Resource: Resource = sceneOptions_value.scene as Resource
                const scene_string: string = GetStrFromResource(scene_Resource)
                ArkUIAniModule._Component3D_SetWidget(peer.getPeerPtr() as KPointer, scene_string, modelType_Num)
                return
            }
        } else {
            const scene_string: string = ''
            const modelType_Num = TypeChecker.ModelType_ToNumeric(ModelType.SURFACE) as int32
            ArkUIAniModule._Component3D_SetWidget(peer.getPeerPtr() as KPointer, scene_string, modelType_Num)
        }
    }
}