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

export interface XComponentOptionsInternal {
    onSurfaceCreated: ((surfaceId: string) => void);
    onSurfaceChanged: ((surfaceId: string, surfaceRect: SurfaceRect) => void);
    onSurfaceDestroyed: ((surfaceId: string) => void);
}

export interface XComponentParametersInternal {
    
}
