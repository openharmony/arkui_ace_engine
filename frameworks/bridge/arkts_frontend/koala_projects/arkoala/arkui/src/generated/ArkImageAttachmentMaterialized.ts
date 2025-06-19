/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { PixelMap, PixelMapInternal } from "./ArkPixelMapMaterialized"
import { SizeOptions, Length, Margin, Padding, BorderRadiuses } from "./ArkUnitsInterfaces"
import { ImageSpanAlignment, ImageFit } from "./ArkEnumsInterfaces"
import { ImageAttachmentLayoutStyle, ImageAttachmentInterface } from "./ArkStyledStringInterfaces"
import { LengthMetrics, LengthMetricsInternal } from "./ArkLengthMetricsMaterialized"
import { LengthUnit } from "./ArkArkuiExternalInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export class ImageAttachmentInternal {
    public static fromPtr(ptr: KPointer): ImageAttachment {
        const obj: ImageAttachment = new ImageAttachment(undefined)
        obj.peer = new Finalizable(ptr, ImageAttachment.getFinalizer())
        return obj
    }
}
export class ImageAttachment implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get value(): PixelMap {
        return this.getValue()
    }
    get size(): SizeOptions {
        throw new Error("Not implemented")
    }
    get verticalAlign(): ImageSpanAlignment {
        return this.getVerticalAlign()
    }
    get objectFit(): ImageFit {
        return this.getObjectFit()
    }
    get layoutStyle(): ImageAttachmentLayoutStyle {
        throw new Error("Not implemented")
    }
    static ctor_imageattachment(value: ImageAttachmentInterface): KPointer {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeImageAttachmentInterface(value)
        const retval = ArkUIGeneratedNativeModule._ImageAttachment_ctor(thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
     constructor(value?: ImageAttachmentInterface) {
        if ((value) !== (undefined))
        {
            const ctorPtr: KPointer = ImageAttachment.ctor_imageattachment((value)!)
            this.peer = new Finalizable(ctorPtr, ImageAttachment.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ImageAttachment_getFinalizer()
    }
    private getValue(): PixelMap {
        return this.getValue_serialize()
    }
    private getVerticalAlign(): ImageSpanAlignment {
        return this.getVerticalAlign_serialize()
    }
    private getObjectFit(): ImageFit {
        return this.getObjectFit_serialize()
    }
    private getValue_serialize(): PixelMap {
        const retval = ArkUIGeneratedNativeModule._ImageAttachment_getValue(this.peer!.ptr)
        const obj: PixelMap = PixelMapInternal.fromPtr(retval)
        return obj
    }
    private getVerticalAlign_serialize(): ImageSpanAlignment {
        const retval = ArkUIGeneratedNativeModule._ImageAttachment_getVerticalAlign(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private getObjectFit_serialize(): ImageFit {
        const retval = ArkUIGeneratedNativeModule._ImageAttachment_getObjectFit(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
}
