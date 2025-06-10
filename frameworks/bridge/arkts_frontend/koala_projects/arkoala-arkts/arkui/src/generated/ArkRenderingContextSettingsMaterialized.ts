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

import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class RenderingContextSettingsInternal {
    public static fromPtr(ptr: KPointer): RenderingContextSettings {
        const obj : RenderingContextSettings = new RenderingContextSettings(undefined)
        obj.peer = new Finalizable(ptr, RenderingContextSettings.getFinalizer())
        return obj
    }
}
export class RenderingContextSettings implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get antialias(): boolean | undefined {
        return this.getAntialias()
    }
    set antialias(antialias: boolean | undefined) {
        const antialias_NonNull  = (antialias as boolean)
        this.setAntialias(antialias_NonNull)
    }
    static ctor_renderingcontextsettings(antialias?: boolean): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let antialias_type : int32 = RuntimeType.UNDEFINED
        antialias_type = runtimeType(antialias)
        thisSerializer.writeInt8(antialias_type as int32)
        if ((RuntimeType.UNDEFINED) != (antialias_type)) {
            const antialias_value  = antialias!
            thisSerializer.writeBoolean(antialias_value)
        }
        const retval  = ArkUIGeneratedNativeModule._RenderingContextSettings_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(antialias?: boolean) {
        const ctorPtr : KPointer = RenderingContextSettings.ctor_renderingcontextsettings((antialias)!)
        this.peer = new Finalizable(ctorPtr, RenderingContextSettings.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._RenderingContextSettings_getFinalizer()
    }
    private getAntialias(): boolean {
        return this.getAntialias_serialize()
    }
    private setAntialias(antialias: boolean): void {
        const antialias_casted = antialias as (boolean)
        this.setAntialias_serialize(antialias_casted)
        return
    }
    private getAntialias_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._RenderingContextSettings_getAntialias(this.peer!.ptr)
        return retval
    }
    private setAntialias_serialize(antialias: boolean): void {
        ArkUIGeneratedNativeModule._RenderingContextSettings_setAntialias(this.peer!.ptr, antialias ? 1 : 0)
    }
}
