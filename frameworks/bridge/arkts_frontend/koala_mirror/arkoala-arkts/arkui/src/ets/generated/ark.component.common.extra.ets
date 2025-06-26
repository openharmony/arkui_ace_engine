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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, nullptr, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { ConstraintSizeOptions_serializer, Position_serializer, Position, ConstraintSizeOptions } from "./units"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { TransitionType } from "./enums"
import { TranslateOptions, ScaleOptions, RotateOptions } from "./common"
export interface LayoutChild {
    name: string
    id: string
    position: Position
    measure(childConstraint: ConstraintSizeOptions): void
}
export class LayoutChildInternal implements MaterializedBase,LayoutChild {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get name(): string {
        return this.getName()
    }
    set name(name: string) {
        this.setName(name)
    }
    get id(): string {
        return this.getId()
    }
    set id(id: string) {
        this.setId(id)
    }
    get position(): Position {
        return this.getPosition()
    }
    set position(position: Position) {
        this.setPosition(position)
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, LayoutChildInternal.getFinalizer())
    }
    static ctor(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._LayoutChild_ctor()
        return retval
    }
    constructor() {
        this(LayoutChildInternal.ctor())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._LayoutChild_getFinalizer()
    }
    public measure(childConstraint: ConstraintSizeOptions): void {
        const childConstraint_casted = childConstraint as (ConstraintSizeOptions)
        this.measure_serialize(childConstraint_casted)
        return
    }
    private getName(): string {
        return this.getName_serialize()
    }
    private setName(name: string): void {
        const name_casted = name as (string)
        this.setName_serialize(name_casted)
        return
    }
    private getId(): string {
        return this.getId_serialize()
    }
    private setId(id: string): void {
        const id_casted = id as (string)
        this.setId_serialize(id_casted)
        return
    }
    private getPosition(): Position {
        return this.getPosition_serialize()
    }
    private setPosition(position: Position): void {
        const position_casted = position as (Position)
        this.setPosition_serialize(position_casted)
        return
    }
    private measure_serialize(childConstraint: ConstraintSizeOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        ConstraintSizeOptions_serializer.write(thisSerializer, childConstraint)
        ArkUIGeneratedNativeModule._LayoutChild_measure(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getName_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._LayoutChild_getName(this.peer!.ptr)
        return retval
    }
    private setName_serialize(name: string): void {
        ArkUIGeneratedNativeModule._LayoutChild_setName(this.peer!.ptr, name)
    }
    private getId_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._LayoutChild_getId(this.peer!.ptr)
        return retval
    }
    private setId_serialize(id: string): void {
        ArkUIGeneratedNativeModule._LayoutChild_setId(this.peer!.ptr, id)
    }
    private getPosition_serialize(): Position {
        const retval  = ArkUIGeneratedNativeModule._LayoutChild_getPosition(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : Position = Position_serializer.read(retvalDeserializer)
        return returnResult
    }
    private setPosition_serialize(position: Position): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Position_serializer.write(thisSerializer, position)
        ArkUIGeneratedNativeModule._LayoutChild_setPosition(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static fromPtr(ptr: KPointer): LayoutChildInternal {
        return new LayoutChildInternal(ptr)
    }
}
export interface TransitionOptions {
    type?: TransitionType;
    opacity?: number;
    translate?: TranslateOptions;
    scale?: ScaleOptions;
    rotate?: RotateOptions;
}
export class LayoutChild_serializer {
    public static write(buffer: SerializerBase, value: LayoutChild): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): LayoutChild {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return LayoutChildInternal.fromPtr(ptr)
    }
}
