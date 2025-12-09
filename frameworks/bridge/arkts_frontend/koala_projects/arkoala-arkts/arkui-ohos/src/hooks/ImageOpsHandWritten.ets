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

import { SerializerBase, runtimeType, RuntimeType, pointer } from "@koalaui/interop"
import { ArkUIGeneratedNativeModule } from "#components"
import { ArkImageComponent, ResourceStr, ImageContent, ImageAIOptions, ArkImagePeer, ImageErrorCallback, ImageError, BusinessError } from "#generated"
import { default as image } from "@ohos.multimedia.image"
import { Resource } from "global.resource"
import { DrawableDescriptor } from "@ohos.arkui.drawableDescriptor"
import { DrawableDescriptor_serializer, image_PixelMap_serializer, Resource_serializer, ImageAIOptions_serializer } from "#generated"
import { ArkUIAniModule } from "arkui.ani";
import { int32 } from "@koalaui/common";

class ImageErrorImpl implements ImageError {
    componentWidth: int32;
    componentHeight: int32;
    message: string = "";
    error?: BusinessError;
    constructor() { }
}

export class ImageOpsHandWritten {
    static hookImageSetImageOptionsImpl(component: ArkImageComponent,
        src: image.PixelMap | ResourceStr | DrawableDescriptor | ImageContent, imageAIOptions?: ImageAIOptions): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (src instanceof image.PixelMap) {
            thisSerializer.writeInt8((0).toByte())
            const srcForIdx0 = src as image.PixelMap
            image_PixelMap_serializer.write(thisSerializer, srcForIdx0)
        } else if (src instanceof ResourceStr) {
            thisSerializer.writeInt8((1).toByte())
            const srcForIdx1 = src as ResourceStr
            if (srcForIdx1 instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const srcForIdx1ForIdx0 = srcForIdx1 as string
                thisSerializer.writeString(srcForIdx1ForIdx0)
            } else if (srcForIdx1 instanceof Resource) {
                thisSerializer.writeInt8((1).toByte())
                const srcForIdx1ForIdx1 = srcForIdx1 as Resource
                Resource_serializer.write(thisSerializer, srcForIdx1ForIdx1)
            }
        } else if (src instanceof DrawableDescriptor) {
            thisSerializer.writeInt8((2).toByte())
            const srcForIdx2 = src as DrawableDescriptor
            DrawableDescriptor_serializer.write(thisSerializer, srcForIdx2)
        } else if (src instanceof ImageContent) {
            thisSerializer.writeInt8((3).toByte())
            const srcForIdx3 = src as ImageContent
            thisSerializer.writeInt32(srcForIdx3.valueOf())
        }
        let peerPtr = component.getPeer().peer.ptr
        if (imageAIOptions !== undefined) {
            if (imageAIOptions.aiController instanceof ESValue) {
                thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        
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
                const imageAIOptionsFunc = global.getProperty('wrapImageAIOptions')
                if (!(imageAIOptionsFunc.isNull() || imageAIOptionsFunc.isUndefined())) {
                    imageAIOptionsFunc.invoke(ESObject.wrap(peerPtr), imageAIOptionsObj)
                }
            } else {
                thisSerializer.writeInt8(RuntimeType.OBJECT)
                const imageAIOptionsTmpValue = imageAIOptions!
                ImageAIOptions_serializer.write(thisSerializer, imageAIOptionsTmpValue)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageInterface_setImageOptions(peerPtr, thisSerializer.asBuffer(),
            thisSerializer.length())
        thisSerializer.release()
    }

    static hookImageOnErrorImpl(receiver: ArkImageComponent | ArkImagePeer, value: ImageErrorCallback | undefined): void {
        let peerPtr: pointer;
        if (receiver instanceof ArkImageComponent) {
            peerPtr = receiver.getPeer().peer.ptr
        } else if (receiver instanceof ArkImagePeer) {
            peerPtr = receiver.peer.ptr
        }
        if (peerPtr === undefined) {
            return;
        }
        ArkUIAniModule._Image_SetOnErrorCallback(peerPtr, value);
    }
}