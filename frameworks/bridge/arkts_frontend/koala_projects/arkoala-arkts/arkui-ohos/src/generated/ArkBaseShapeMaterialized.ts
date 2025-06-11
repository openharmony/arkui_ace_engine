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

import { Length, SizeOptions } from "./../component/units"
import { Resource } from "global/resource";
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class BaseShapeInternal {
    public static fromPtr(ptr: KPointer): BaseShape {
        const obj : BaseShape = new BaseShape()
        obj.peer = new Finalizable(ptr, BaseShape.getFinalizer())
        return obj
    }
}
export class BaseShape implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_baseshape(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._BaseShape_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = BaseShape.ctor_baseshape()
        this.peer = new Finalizable(ctorPtr, BaseShape.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._BaseShape_getFinalizer()
    }
    public width(width: Length): BaseShape {
        const width_casted = width as (Length)
        return this.width_serialize(width_casted)
    }
    public height(height: Length): BaseShape {
        const height_casted = height as (Length)
        return this.height_serialize(height_casted)
    }
    public size(size: SizeOptions): BaseShape {
        const size_casted = size as (SizeOptions)
        return this.size_serialize(size_casted)
    }
    private width_serialize(width: Length): BaseShape {
        const retval  = ArkUIGeneratedNativeModule._BaseShape_width(this.peer!.ptr, width)
        const obj : BaseShape = BaseShapeInternal.fromPtr(retval)
        return obj
    }
    private height_serialize(height: Length): BaseShape {
        const retval  = ArkUIGeneratedNativeModule._BaseShape_height(this.peer!.ptr, height)
        const obj : BaseShape = BaseShapeInternal.fromPtr(retval)
        return obj
    }
    private size_serialize(size: SizeOptions): BaseShape {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeSizeOptions(size)
        const retval  = ArkUIGeneratedNativeModule._BaseShape_size(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : BaseShape = BaseShapeInternal.fromPtr(retval)
        return obj
    }
}
