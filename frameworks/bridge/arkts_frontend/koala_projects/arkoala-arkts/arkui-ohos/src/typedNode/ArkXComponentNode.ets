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

import { InteropNativeModule, toPeerPtr } from '@koalaui/interop';
import { ArkBaseNode } from './ArkBaseNode';
import { XComponentAttribute, ArkXComponentPeer, XComponentParameters, XComponentOptions, NativeXComponentParameters, SurfaceRect, XComponentOptionsInternal } from '../component/xcomponent';
import { VoidCallback } from '../component/units';
import { ArkUIAniModule } from "arkui.ani";

export class ArkXComponentNode extends ArkBaseNode implements XComponentAttribute {
    constructParam(...params: Object[]): this {
        return this;
    }
    getPeer() : ArkXComponentPeer {
        return this.peer as ArkXComponentPeer
    }
    initializeXComponentParameter(value: XComponentParameters): this {
        const peer = this.getPeer();
        peer?.setXComponentOptionsAttribute(value);
        return this;
    }
    initializeXComponentOptions(value: XComponentOptions): this {
        const peer = this.getPeer();
        if (peer === undefined) {
            return this;
        }
        const options: XComponentOptionsInternal = {
            onSurfaceCreated: value.controller.onSurfaceCreated as ((surfaceId: string) => void),
            onSurfaceChanged: value.controller.onSurfaceChanged as ((surfaceId: string, surfaceRect: SurfaceRect) => void),
            onSurfaceDestroyed: value.controller.onSurfaceDestroyed as ((surfaceId: string) => void)
        } as XComponentOptionsInternal;
        ArkUIAniModule._XComponent_SetXComponentControllerCallback(toPeerPtr(value.controller), options);
        peer.setXComponentOptionsAttribute(value);
        return this;
    }
    initializeNativeXComponentParameters(value: NativeXComponentParameters): this {
        const peer = this.getPeer();
        peer?.setXComponentOptionsAttribute(value);
        return this;
    }
    overload initialize { initializeXComponentParameter, initializeXComponentOptions, initializeNativeXComponentParameters }
    onLoad(value: VoidCallback | undefined): this {
        this.getPeer()?.setOnLoadAttribute(value);
        return this;
    }
    onDestroy(value: VoidCallback | undefined): this {
        this.getPeer()?.setOnDestroyAttribute(value);
        return this;
    }
    enableAnalyzer(value: boolean | undefined): this {
        this.getPeer()?.setEnableAnalyzerAttribute(value);
        return this;
    }
    enableSecure(value: boolean | undefined): this {
        this.getPeer()?.setEnableSecureAttribute(value);
        return this;
    }
    enableTransparentLayer(value: boolean | undefined): this {
        this.getPeer()?.setEnableTransparentLayerAttribute(value);
        return this;
    }
    hdrBrightness(value: number | undefined): this {
        this.getPeer()?.setHdrBrightnessAttribute(value);
        return this;
    }
}
