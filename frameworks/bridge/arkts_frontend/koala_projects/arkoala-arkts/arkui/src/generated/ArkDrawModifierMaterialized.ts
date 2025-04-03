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

import { DrawContext } from "./ArkCommonInterfaces"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class DrawModifierInternal {
    public static fromPtr(ptr: KPointer): DrawModifier {
        const obj : DrawModifier = new DrawModifier()
        obj.peer = new Finalizable(ptr, DrawModifier.getFinalizer())
        return obj
    }
}
export class DrawModifier implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_drawmodifier(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._DrawModifier_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = DrawModifier.ctor_drawmodifier()
        this.peer = new Finalizable(ctorPtr, DrawModifier.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._DrawModifier_getFinalizer()
    }
    public drawBehind(drawContext: DrawContext): void {
        const drawContext_casted = drawContext as (DrawContext)
        this.drawBehind_serialize(drawContext_casted)
        return
    }
    public drawContent(drawContext: DrawContext): void {
        const drawContext_casted = drawContext as (DrawContext)
        this.drawContent_serialize(drawContext_casted)
        return
    }
    public drawFront(drawContext: DrawContext): void {
        const drawContext_casted = drawContext as (DrawContext)
        this.drawFront_serialize(drawContext_casted)
        return
    }
    public invalidate(): void {
        this.invalidate_serialize()
        return
    }
    private drawBehind_serialize(drawContext: DrawContext): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeDrawContext(drawContext)
        ArkUIGeneratedNativeModule._DrawModifier_drawBehind(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private drawContent_serialize(drawContext: DrawContext): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeDrawContext(drawContext)
        ArkUIGeneratedNativeModule._DrawModifier_drawContent(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private drawFront_serialize(drawContext: DrawContext): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeDrawContext(drawContext)
        ArkUIGeneratedNativeModule._DrawModifier_drawFront(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private invalidate_serialize(): void {
        ArkUIGeneratedNativeModule._DrawModifier_invalidate(this.peer!.ptr)
    }
}
