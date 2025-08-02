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
export class LayeredDrawableDescriptorInternal {
    public static fromPtr(ptr: KPointer): LayeredDrawableDescriptor {
        const obj : LayeredDrawableDescriptor = new LayeredDrawableDescriptor(undefined, undefined, undefined)
        obj.peer = new Finalizable(ptr, LayeredDrawableDescriptor.getFinalizer())
        return obj
    }
}
export class LayeredDrawableDescriptor extends DrawableDescriptor implements MaterializedBase {
    static ctor_layereddrawabledescriptor(foreground?: DrawableDescriptor, background?: DrawableDescriptor, mask?: DrawableDescriptor): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let foreground_type : int32 = RuntimeType.UNDEFINED
        foreground_type = runtimeType(foreground)
        thisSerializer.writeInt8(foreground_type as int32)
        if ((RuntimeType.UNDEFINED) != (foreground_type)) {
            const foreground_value  = foreground!
            thisSerializer.writeDrawableDescriptor(foreground_value)
        }
        let background_type : int32 = RuntimeType.UNDEFINED
        background_type = runtimeType(background)
        thisSerializer.writeInt8(background_type as int32)
        if ((RuntimeType.UNDEFINED) != (background_type)) {
            const background_value  = background!
            thisSerializer.writeDrawableDescriptor(background_value)
        }
        let mask_type : int32 = RuntimeType.UNDEFINED
        mask_type = runtimeType(mask)
        thisSerializer.writeInt8(mask_type as int32)
        if ((RuntimeType.UNDEFINED) != (mask_type)) {
            const mask_value  = mask!
            thisSerializer.writeDrawableDescriptor(mask_value)
        }
        const retval  = ArkUIGeneratedNativeModule._LayeredDrawableDescriptor_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(foreground?: DrawableDescriptor, background?: DrawableDescriptor, mask?: DrawableDescriptor) {
        super()
        // All constructor parameters are optional.
        // It means that the static method call invokes ctor method as well
        // when all arguments are undefined.
        const ctorPtr : KPointer = LayeredDrawableDescriptor.ctor_layereddrawabledescriptor((foreground)!, (background)!, (mask)!)
        this.peer = new Finalizable(ctorPtr, LayeredDrawableDescriptor.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._LayeredDrawableDescriptor_getFinalizer()
    }
    public getForeground(): DrawableDescriptor {
        return this.getForeground_serialize()
    }
    public getBackground(): DrawableDescriptor {
        return this.getBackground_serialize()
    }
    public getMask(): DrawableDescriptor {
        return this.getMask_serialize()
    }
    public static getMaskClipPath(): string {
        return LayeredDrawableDescriptor.getMaskClipPath_serialize()
    }
    private getForeground_serialize(): DrawableDescriptor {
        const retval  = ArkUIGeneratedNativeModule._LayeredDrawableDescriptor_getForeground(this.peer!.ptr)
        const obj : DrawableDescriptor = DrawableDescriptorInternal.fromPtr(retval)
        return obj
    }
    private getBackground_serialize(): DrawableDescriptor {
        const retval  = ArkUIGeneratedNativeModule._LayeredDrawableDescriptor_getBackground(this.peer!.ptr)
        const obj : DrawableDescriptor = DrawableDescriptorInternal.fromPtr(retval)
        return obj
    }
    private getMask_serialize(): DrawableDescriptor {
        const retval  = ArkUIGeneratedNativeModule._LayeredDrawableDescriptor_getMask(this.peer!.ptr)
        const obj : DrawableDescriptor = DrawableDescriptorInternal.fromPtr(retval)
        return obj
    }
    private static getMaskClipPath_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._LayeredDrawableDescriptor_getMaskClipPath()
        return retval
    }
}
