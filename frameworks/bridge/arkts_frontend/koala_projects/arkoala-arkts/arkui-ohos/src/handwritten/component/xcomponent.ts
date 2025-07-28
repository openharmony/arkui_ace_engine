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
import { KPointer, toPeerPtr } from "@koalaui/interop";
import { int64, int32, uint64 } from "@koalaui/common"
import { ArkUIAniModule } from "arkui.ani";

export interface XComponentOptionsInternal {
    type: int32;
    controllerPtr: KPointer;
    screenId?: uint64;
    onSurfaceCreated: ((surfaceId: string) => void);
    onSurfaceChanged: ((surfaceId: string, surfaceRect: SurfaceRect) => void);
    onSurfaceDestroyed: ((surfaceId: string) => void);
}

export interface XComponentParametersInternal {
    id: string;
    type: int32;
    nativeHandler: ((pointer: int64) => void);
    controllerPtr?: KPointer;
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

function ConvertXComponentType(type: XComponentType): int32 {
    return type == XComponentType.SURFACE ? 0 : 2;
}

export function setXComponentParametersANI(peer: ArkXComponentPeer, value: XComponentParameter): void {
    if (peer === undefined) {
        return;
    }
    let params: XComponentParametersInternal = {
            id: value.id,
            type: ConvertXComponentType(value.type),
            nativeHandler: (ptr: int64) => {},
    } as XComponentParametersInternal;
    if (value.controller !== undefined) {
        const controller = value.controller! as XComponentController;
        params.controllerPtr = toPeerPtr(controller);
    }
    ArkUIAniModule._XComponent_SetXComponentParameters(peer.getPeerPtr(), params);
}

export function setXComponentOptionsANI(peer: ArkXComponentPeer, value: XComponentOptions): void {
    if (peer === undefined) {
        return;
    }
    const options: XComponentOptionsInternal = {
        type: ConvertXComponentType(value.type),
        controllerPtr: toPeerPtr(value.controller),
        onSurfaceCreated: value.controller.onSurfaceCreated as ((surfaceId: string) => void),
        onSurfaceChanged: value.controller.onSurfaceChanged as ((surfaceId: string, surfaceRect: SurfaceRect) => void),
        onSurfaceDestroyed: value.controller.onSurfaceDestroyed as ((surfaceId: string) => void),
    } as XComponentOptionsInternal;
    if (value.screenId !== undefined) {
        options.screenId = value.screenId! as uint64;
    }
    ArkUIAniModule._XComponent_SetXComponentOptions(peer.getPeerPtr(), options);
}

function hookSetXComponentOptions(component: ArkXComponentComponent,
    value: XComponentParameter | XComponentOptions | NativeXComponentParameters): void {
    const peer = component.getPeer();
    if (value instanceof XComponentParameter) {
        const value_casted = value as XComponentParameter;
        setXComponentParametersANI(peer, value_casted);
    } else if (value instanceof XComponentOptions) {
        const value_casted = value as XComponentOptions;
        setXComponentOptionsANI(peer, value_casted);
    } else {
        const value_casted = value as NativeXComponentParameters;
        ArkUIAniModule._XComponent_SetNativeXComponentParameters(peer.getPeerPtr(), ConvertXComponentType(value.type));
    }
}
