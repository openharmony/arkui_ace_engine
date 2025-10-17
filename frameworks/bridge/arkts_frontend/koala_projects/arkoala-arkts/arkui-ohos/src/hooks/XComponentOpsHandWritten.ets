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

import { SerializerBase, runtimeType, RuntimeType, InteropNativeModule, toPeerPtr, KPointer } from "@koalaui/interop"
import { ArkXComponentComponent, ImageAIOptions, XComponentOptions, XComponentParameters, NativeXComponentParameters, XComponentController, XComponentOptionsInternal, SurfaceRect, ImageAnalyzerConfig } from "#generated";
import { ArkUIAniModule } from "arkui.ani";

function wrapXComponentImageAIOptions(peerPtr: KPointer, imageAIOptions: ImageAIOptions): void{
    let imageAIOptionsObj = ESValue.instantiateEmptyObject()
    let types = imageAIOptions.types
    if (types !== undefined) {
        let typesObj = ESValue.instantiateEmptyArray()
        for (let i = 0; i < types.length; i++) {
            typesObj.setProperty(i, Number(types[i]))
        }
        imageAIOptionsObj.setProperty('types', typesObj)
    }
    let aiController = imageAIOptions.aiController
    if ((aiController !== undefined) && (aiController instanceof ESValue)) {
        imageAIOptionsObj.setProperty('aiController', aiController)
    }
    const global = ESValue.getGlobal()
    const imageAIOptionsFunc = global.getProperty('wrapXComponentImageAIOptions')
    if (!(imageAIOptionsFunc.isNull() || imageAIOptionsFunc.isUndefined())) {
        imageAIOptionsFunc.invoke(ESObject.wrap(peerPtr), imageAIOptionsObj)
    }
}

export class XComponentOpsHandWritten {
    static hookSetXComponentOptionsImpl(component: ArkXComponentComponent,
        params: XComponentParameters | XComponentOptions | NativeXComponentParameters): void {
        const peer = component.getPeer();
        if (peer === undefined) {
            return;
        }
        let peerPtr = peer.peer.ptr
        if (params instanceof XComponentOptions) {
            let value_casted = params as XComponentOptions
            const options: XComponentOptionsInternal = {
                onSurfaceCreated: value_casted.controller.onSurfaceCreated as ((surfaceId: string) => void),
                onSurfaceChanged: value_casted.controller.onSurfaceChanged as ((surfaceId: string, surfaceRect: SurfaceRect) => void),
                onSurfaceDestroyed: value_casted.controller.onSurfaceDestroyed as ((surfaceId: string) => void)
            } as XComponentOptionsInternal;
            ArkUIAniModule._XComponent_SetXComponentControllerCallback(toPeerPtr(value_casted.controller), options);

            // wrap imageAIOptions
            const optImageAIOptions = value_casted.imageAIOptions;
            if (optImageAIOptions !== undefined) {
                const imageAIOptions = optImageAIOptions as ImageAIOptions;
                wrapXComponentImageAIOptions(peerPtr, imageAIOptions);
            }
        }
        if (params instanceof NativeXComponentParameters) {
            let value_casted = params as NativeXComponentParameters
            // wrap imageAIOptions
            const optImageAIOptions = value_casted.imageAIOptions;
            if (optImageAIOptions !== undefined) {
                const imageAIOptions = optImageAIOptions as ImageAIOptions;
                wrapXComponentImageAIOptions(peerPtr, imageAIOptions);
            }
        }
    }
    static hookXComponentStartImageAnalyzerImpl(
        controller: XComponentController, config: ImageAnalyzerConfig): Promise<void> {
        const peer = controller.getPeer();
        if (peer === undefined) {
            return controller.startImageAnalyzer_serialize(config);
        }
        const peerPtr = peer.ptr;
        let configObj = ESValue.instantiateEmptyObject();
        let types = config.types;
        if (types !== undefined) {
            let typesObj = ESValue.instantiateEmptyArray();
            for (let i = 0; i < types.length; i++) {
                typesObj.setProperty(i, Number(types[i]));
            }
            configObj.setProperty('types', typesObj);
        }
        const global = ESValue.getGlobal();
        const analyzerConfigFunc = global.getProperty('hookXComponentSetAnalyzerConfig');
        if (!(analyzerConfigFunc.isNull() || analyzerConfigFunc.isUndefined())) {
            analyzerConfigFunc.invoke(ESObject.wrap(peerPtr), configObj);
        }
        return controller.startImageAnalyzer_serialize(config);
    }
}
