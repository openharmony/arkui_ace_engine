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
import { AnimationOptions } from "./ArkArkuiDrawabledescriptorInterfaces"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class AnimatedDrawableDescriptorInternal {
    public static fromPtr(ptr: KPointer): AnimatedDrawableDescriptor {
        const obj : AnimatedDrawableDescriptor = new AnimatedDrawableDescriptor(undefined, undefined)
        obj.peer = new Finalizable(ptr, AnimatedDrawableDescriptor.getFinalizer())
        return obj
    }
}
export class AnimatedDrawableDescriptor extends DrawableDescriptor implements MaterializedBase {
    static ctor_animateddrawabledescriptor(pixelMaps: Array<PixelMap>, options?: AnimationOptions): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(pixelMaps.length as int32)
        for (let i = 0; i < pixelMaps.length; i++) {
            const pixelMaps_element : PixelMap = pixelMaps[i]
            thisSerializer.writePixelMap(pixelMaps_element)
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeAnimationOptions(options_value)
        }
        const retval  = ArkUIGeneratedNativeModule._AnimatedDrawableDescriptor_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(pixelMaps?: Array<PixelMap>, options?: AnimationOptions) {
        super()
        if (((pixelMaps) !== (undefined)) || ((options) !== (undefined)))
        {
            const ctorPtr : KPointer = AnimatedDrawableDescriptor.ctor_animateddrawabledescriptor((pixelMaps)!, (options)!)
            this.peer = new Finalizable(ctorPtr, AnimatedDrawableDescriptor.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._AnimatedDrawableDescriptor_getFinalizer()
    }
}
