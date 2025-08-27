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

import { DrawableDescriptor, DrawableDescriptorInternal } from "./ArkDrawableDescriptorMaterialized"
import { PixelMap, PixelMapInternal } from "./ArkPixelMapMaterialized"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class PixelMapDrawableDescriptorInternal {
    public static fromPtr(ptr: KPointer): PixelMapDrawableDescriptor {
        const obj : PixelMapDrawableDescriptor = new PixelMapDrawableDescriptor(undefined)
        obj.peer = new Finalizable(ptr, PixelMapDrawableDescriptor.getFinalizer())
        return obj
    }
}
export class PixelMapDrawableDescriptor extends DrawableDescriptor implements MaterializedBase {
    static ctor_pixelmapdrawabledescriptor(src?: PixelMap): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let src_type : int32 = RuntimeType.UNDEFINED
        src_type = runtimeType(src)
        thisSerializer.writeInt8(src_type as int32)
        if ((RuntimeType.UNDEFINED) != (src_type)) {
            const src_value  = src!
            thisSerializer.writePixelMap(src_value)
        }
        const retval  = ArkUIGeneratedNativeModule._PixelMapDrawableDescriptor_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(src?: PixelMap) {
        super()
        const ctorPtr : KPointer = PixelMapDrawableDescriptor.ctor_pixelmapdrawabledescriptor((src)!)
        this.peer = new Finalizable(ctorPtr, PixelMapDrawableDescriptor.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._PixelMapDrawableDescriptor_getFinalizer()
    }
}
