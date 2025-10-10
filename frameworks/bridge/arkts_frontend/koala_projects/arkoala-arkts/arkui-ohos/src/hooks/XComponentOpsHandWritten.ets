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

import { SerializerBase, runtimeType, RuntimeType, InteropNativeModule, toPeerPtr } from "@koalaui/interop"
import { ArkXComponentComponent, XComponentOptions, XComponentParameters, NativeXComponentParameters, XComponentController, XComponentOptionsInternal, SurfaceRect } from "#generated";
import { ArkUIAniModule } from "arkui.ani";

export class XComponentOpsHandWritten {
    static hookSetXComponentOptionsImpl(component: ArkXComponentComponent, params: XComponentParameters | XComponentOptions | NativeXComponentParameters): void {
        const peer = component.getPeer();
        if (peer === undefined) {
            return;
        }
        if (params instanceof XComponentOptions) {
            const value = params as XComponentOptions
            const options: XComponentOptionsInternal = {
                onSurfaceCreated: value.controller.onSurfaceCreated as ((surfaceId: string) => void),
                onSurfaceChanged: value.controller.onSurfaceChanged as ((surfaceId: string, surfaceRect: SurfaceRect) => void),
                onSurfaceDestroyed: value.controller.onSurfaceDestroyed as ((surfaceId: string) => void)
            } as XComponentOptionsInternal;
            ArkUIAniModule._XComponent_SetXComponentControllerCallback(toPeerPtr(value.controller), options);
        }
        peer.setXComponentOptionsAttribute(params);
    }
}
