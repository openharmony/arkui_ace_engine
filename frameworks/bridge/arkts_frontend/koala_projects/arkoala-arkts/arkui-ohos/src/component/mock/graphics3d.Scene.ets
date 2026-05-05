/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

// Stub module for graphics3d.Scene — previewer only.
// ArTS strict mode: all params and return types require annotations.
// NOTE: This is a simplified mock for previewer; return types are intentionally
// simplified to Scene for ease of implementation.
export class Scene {
    static getDefaultRenderContext(): Scene { return new Scene() }
    static load(uri: string): Promise<Scene> {
        return new Promise<Scene>((resolve: (v: Scene) => void) => { resolve(new Scene()) })
    }
    get environment(): Scene { return new Scene() }
    set environment(value: Scene) {}
    get animations(): Scene[] { return new Array<Scene>() }
    get root(): Scene { return new Scene() }
    getNodeByPath(path: string, type: number): Scene { return new Scene() }
    getResourceFactory(): Scene { return new Scene() }
    destroy(): void {}
    importNode(name: string, node: Scene, parent: Scene): Scene { return new Scene() }
    importScene(name: string, scene: Scene, parent: Scene): Scene { return new Scene() }
    renderFrame(params: string): boolean { return false }
    createComponent(node: Scene, name: string): Promise<Scene> {
        return new Promise<Scene>((resolve: (v: Scene) => void) => { resolve(new Scene()) })
    }
    get renderConfiguration(): Scene { return new Scene() }
    getComponent(node: Scene, name: string): Scene { return new Scene() }
    cloneNode(node: Scene, parent: Scene, name: string): Scene { return new Scene() }
}
