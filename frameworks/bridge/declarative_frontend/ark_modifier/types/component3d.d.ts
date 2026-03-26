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
declare type Scene = import('../api/@ohos.graphics.scene').Scene;
declare enum ModelType {
    TEXTURE = 0,
    SURFACE = 1
}
declare interface SceneOptions {
    scene?: ResourceStr | Scene;
    modelType?: ModelType;
}
interface Component3DInterface {
    (sceneOptions?: SceneOptions): Component3DAttribute;
}
declare class Component3DAttribute extends CommonMethod<Component3DAttribute> {
}
declare const Component3D: Component3DInterface;
declare const Component3DInstance: Component3DAttribute;
