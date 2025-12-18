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
import { ArkCanvasComponent, CanvasRenderingContext2D, DrawingRenderingContext, ImageAIOptions, ImageAnalyzerConfig, CanvasParams } from "#generated"
import { ImageAIOptions_serializer, VideoOptions_serializer } from "#generated"

export class CanvasOpsHandWritten {
    static hookSetCanvasOptionsImpl(component: ArkCanvasComponent,
    context?: CanvasRenderingContext2D | DrawingRenderingContext, imageAIOptions?: ImageAIOptions): void {
        const peer = component.getPeer();
        if (peer === undefined) {
            return;
        }
        let peerPtr = peer.peer.ptr
        const context_casted = context as (CanvasRenderingContext2D | DrawingRenderingContext | undefined);
        const imageAIOptions_casted = imageAIOptions as (ImageAIOptions | undefined);
        if (imageAIOptions_casted !== undefined) {
            const imageAIOptions = imageAIOptions_casted as ImageAIOptions;
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
            const imageAIOptionsFunc = global.getProperty('wrapCanvasImageAIOptions')
            if (!(imageAIOptionsFunc.isNull() || imageAIOptionsFunc.isUndefined())) {
                imageAIOptionsFunc.invoke(ESObject.wrap(peerPtr), imageAIOptionsObj)
            }
        }
    }
    static hookSetCanvasOptionsImpl(component: ArkCanvasComponent, params: CanvasParams): void {
        const peer = component.getPeer();
        if (peer === undefined) {
            return;
        }
        let peerPtr = peer.peer.ptr
        const imageAIOptions_casted = params.imageAIOptions as (ImageAIOptions | undefined);
        if (imageAIOptions_casted !== undefined) {
            const imageAIOptions = imageAIOptions_casted as ImageAIOptions;
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
            const imageAIOptionsFunc = global.getProperty('wrapCanvasImageAIOptions')
            if (!(imageAIOptionsFunc.isNull() || imageAIOptionsFunc.isUndefined())) {
                imageAIOptionsFunc.invoke(ESObject.wrap(peerPtr), imageAIOptionsObj)
            }
        }
    }
    static hookCanvasStartImageAnalyzerImpl(
        context: CanvasRenderingContext2D, config: ImageAnalyzerConfig): Promise<void> {
        const peer = context.getPeer();
        if (peer === undefined) {
            return context.startImageAnalyzer_serialize(config);
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
        const analyzerConfigFunc = global.getProperty('hookCanvasSetAnalyzerConfig');
        if (!(analyzerConfigFunc.isNull() || analyzerConfigFunc.isUndefined())) {
            analyzerConfigFunc.invoke(ESObject.wrap(peerPtr), configObj);
        }
        return context.startImageAnalyzer_serialize(config);
    }
}
