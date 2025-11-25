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

import { SerializerBase, runtimeType, RuntimeType } from "@koalaui/interop"
import { ArkUIGeneratedNativeModule } from "#components"
import { ArkVideoComponent, ArkVideoPeer, VideoOptions, ImageAIOptions, ImageAnalyzerConfig, VoidCallback } from "#generated"
import { ImageAIOptions_serializer, VideoOptions_serializer } from "#generated"
import { ArkUIAniModule } from "arkui.ani";
import { ErrorCallback } from "@ohos.base";

export class VideoOpsHandWritten {
    static hookSetVideoOptionsImpl(component: ArkVideoComponent, value: VideoOptions): void {
        const peer = component.getPeer();
        if (peer === undefined) {
            return;
        }
        let peerPtr = peer.peer.ptr;
        const value_casted = value as VideoOptions;
        const optImageAIOptions = value_casted.imageAIOptions;
        if (optImageAIOptions !== undefined) {
            const imageAIOptions = optImageAIOptions as ImageAIOptions;
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
            const imageAIOptionsFunc = global.getProperty('wrapVideoImageAIOptions')
            if (!(imageAIOptionsFunc.isNull() || imageAIOptionsFunc.isUndefined())) {
                imageAIOptionsFunc.invoke(ESObject.wrap(peerPtr), imageAIOptionsObj)
            }
        }
    }
    static hookSetVideoAnalyzerConfigImpl(
        component: ArkVideoComponent | ArkVideoPeer, config: ImageAnalyzerConfig | undefined): void {
        const peer = (component instanceof ArkVideoComponent) ? component.getPeer() : component;
        if (peer === undefined || config === undefined) {
            return;
        }
        let peerPtr = peer.peer.ptr;
        const value_casted = config as ImageAnalyzerConfig;
        let configObj = ESValue.instantiateEmptyObject();
        let types = value_casted.types;
        if (types !== undefined) {
            let typesObj = ESValue.instantiateEmptyArray();
            for (let i = 0; i < types.length; i++) {
                typesObj.setProperty(i, Number(types[i]));
            }
            configObj.setProperty('types', typesObj);
        }
        const global = ESValue.getGlobal();
        const analyzerConfigFunc = global.getProperty('hookVideoSetAnalyzerConfig');
        if (!(analyzerConfigFunc.isNull() || analyzerConfigFunc.isUndefined())) {
            analyzerConfigFunc.invoke(ESObject.wrap(peerPtr), configObj);
        }
    }
    static hookSetVideoOnErrorImpl(
        component: ArkVideoComponent | ArkVideoPeer,
        value: VoidCallback | ErrorCallback | undefined): void {
        const peer = (component instanceof ArkVideoComponent) ? component.getPeer() : component;
        if (peer === undefined) {
            return;
        }
        let peerPtr = peer.peer.ptr;
        if (value === undefined) {
            ArkUIAniModule._Video_SetVoidCallback(peerPtr, () => {});
            return;
        }
        const valueTmpValue = value!;
        if (valueTmpValue instanceof VoidCallback) {
            ArkUIAniModule._Video_SetVoidCallback(peerPtr, valueTmpValue as VoidCallback);
        } else if (valueTmpValue instanceof ErrorCallback) {
            ArkUIAniModule._Video_SetErrorCallback(peerPtr, valueTmpValue as ErrorCallback);
        }
    }
}