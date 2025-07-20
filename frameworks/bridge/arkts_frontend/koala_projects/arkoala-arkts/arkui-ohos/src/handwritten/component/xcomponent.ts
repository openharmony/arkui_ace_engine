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


import { TypeChecker } from "#components"
import { ArkUIAniModule } from "arkui.ani";

export interface XComponentControllerCallbackInternal {
    onSurfaceCreated: ((surfaceId: string) => void);
    onSurfaceChanged: ((surfaceId: string, surfaceRect: SurfaceRect) => void);
    onSurfaceDestroyed: ((surfaceId: string) => void);
}

export class SurfaceRectAniInternal implements SurfaceRect {
    offsetX?: number;
    offsetY?: number;
    surfaceWidth: number;
    surfaceHeight: number;
    constructor(w: number, h: number, x: number, y: number) {
        this.offsetX = x;
        this.offsetY = y;
        this.surfaceWidth = w;
        this.surfaceHeight = h;
    }
}

export class TypedXComponentPeerInternal extends ArkXComponentPeer {
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
}

function hookSetXComponentOptions(component: ArkXComponentComponent,
    value: XComponentParameter | XComponentOptions | NativeXComponentParameters): void {
    if (TypeChecker.isXComponentOptions(value, true, false, true, true)) {
        const options_casted = value as (XComponentOptions)
        const peer = component.getPeer();
        peer?.setXComponentOptions1Attribute(options_casted)
        if (peer !== undefined) {
            const controller = options_casted.controller;
            let callback: XComponentControllerCallbackInternal = {
                onSurfaceCreated: controller.onSurfaceCreated as ((surfaceId: string) => void),
                onSurfaceChanged: controller.onSurfaceChanged as ((surfaceId: string, surfaceRect: SurfaceRect) => void),
                onSurfaceDestroyed: controller.onSurfaceDestroyed as ((surfaceId: string) => void),
            } as XComponentControllerCallbackInternal;
            ArkUIAniModule._XComponent_SetSurfaceCallback(peer.getPeerPtr(), callback);
        }
        return;
    }
}
