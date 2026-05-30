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
import { XComponentControllerNative, XComponentControllerWrapper } from "./idlize"
import { hookXComponentStartImageAnalyzer } from "../hooks"
import { ImageAnalyzerConfig } from "./imageCommon"
import { DrawingCanvas } from "./units"

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

export class XComponentController {
    public nativeObj: XComponentControllerNative;
    constructor() {
        this.nativeObj = new XComponentControllerNative();
    }
    getXComponentSurfaceId(): string {
        return this.nativeObj.getXComponentSurfaceId()
    }
    setXComponentSurfaceRect(rect: SurfaceRect): void {
        this.nativeObj.setXComponentSurfaceRect(rect)
    }
    getXComponentSurfaceRect(): SurfaceRect {
        return this.nativeObj.getXComponentSurfaceRect()
    }
    setXComponentSurfaceRotation(rotationOptions: SurfaceRotationOptions): void {
        this.nativeObj.setXComponentSurfaceRotation(rotationOptions)
    }
    getXComponentSurfaceRotation(): Required<SurfaceRotationOptions> {
        return this.nativeObj.getXComponentSurfaceRotation() as Required<SurfaceRotationOptions>
    }
    startImageAnalyzer(config: ImageAnalyzerConfig): Promise<void> {
        return hookXComponentStartImageAnalyzer(this, config)
    }
    stopImageAnalyzer(): void {
        return this.nativeObj.stopImageAnalyzer()
    }
    lockCanvas(): DrawingCanvas | null {
        return this.nativeObj.lockCanvas()
    }
    unlockCanvasAndPost(canvas: DrawingCanvas):void {
        this.nativeObj.unlockCanvasAndPost(canvas)
    }
    setXComponentSurfaceConfig(config: SurfaceConfig):void {
        this.nativeObj.setXComponentSurfaceConfig(config)
    }

    onSurfaceCreated(surfaceId: string): void {}
    onSurfaceChanged(surfaceId: string, rect: SurfaceRect): void {}
    onSurfaceDestroyed(surfaceId: string): void {}
}
