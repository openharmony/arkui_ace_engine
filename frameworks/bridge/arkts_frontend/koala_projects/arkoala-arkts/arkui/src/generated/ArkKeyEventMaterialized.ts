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

import { KeyType, KeySource } from "./ArkEnumsInterfaces"
import { Callback_Void } from "./SyntheticDeclarations"
import { IntentionCode } from "./ArkCommonInterfaces"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export interface KeyEvent {
    type: KeyType
    keyCode: number
    keyText: string
    keySource: KeySource
    deviceId: number
    metaKey: number
    timestamp: number
    stopPropagation: (() => void)
    intentionCode: IntentionCode
    unicode?: number | undefined
    getModifierKeyState(keys: Array<string>): boolean
}
export class KeyEventInternal implements MaterializedBase,KeyEvent {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get type(): KeyType {
        return this.getType()
    }
    set type(type: KeyType) {
        this.setType(type)
    }
    get keyCode(): number {
        return this.getKeyCode()
    }
    set keyCode(keyCode: number) {
        this.setKeyCode(keyCode)
    }
    get keyText(): string {
        return this.getKeyText()
    }
    set keyText(keyText: string) {
        this.setKeyText(keyText)
    }
    get keySource(): KeySource {
        return this.getKeySource()
    }
    set keySource(keySource: KeySource) {
        this.setKeySource(keySource)
    }
    get deviceId(): number {
        return this.getDeviceId()
    }
    set deviceId(deviceId: number) {
        this.setDeviceId(deviceId)
    }
    get metaKey(): number {
        return this.getMetaKey()
    }
    set metaKey(metaKey: number) {
        this.setMetaKey(metaKey)
    }
    get timestamp(): number {
        return this.getTimestamp()
    }
    set timestamp(timestamp: number) {
        this.setTimestamp(timestamp)
    }
    get stopPropagation(): (() => void) {
        throw new Error("Not implemented")
    }
    set stopPropagation(stopPropagation: (() => void)) {
        this.setStopPropagation(stopPropagation)
    }
    get intentionCode(): IntentionCode {
        throw new Error("Not implemented")
    }
    set intentionCode(intentionCode: IntentionCode) {
        this.setIntentionCode(intentionCode)
    }
    get unicode(): number | undefined {
        return this.getUnicode()
    }
    set unicode(unicode: number | undefined) {
        const unicode_NonNull  = (unicode as number)
        this.setUnicode(unicode_NonNull)
    }
    static ctor_keyevent(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._KeyEvent_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = KeyEventInternal.ctor_keyevent()
        this.peer = new Finalizable(ctorPtr, KeyEventInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._KeyEvent_getFinalizer()
    }
    public getModifierKeyState(keys: Array<string>): boolean {
        const keys_casted = keys as (Array<string>)
        return this.getModifierKeyState_serialize(keys_casted)
    }
    private getType(): KeyType {
        return this.getType_serialize()
    }
    private setType(type: KeyType): void {
        const type_casted = type as (KeyType)
        this.setType_serialize(type_casted)
        return
    }
    private getKeyCode(): number {
        return this.getKeyCode_serialize()
    }
    private setKeyCode(keyCode: number): void {
        const keyCode_casted = keyCode as (number)
        this.setKeyCode_serialize(keyCode_casted)
        return
    }
    private getKeyText(): string {
        return this.getKeyText_serialize()
    }
    private setKeyText(keyText: string): void {
        const keyText_casted = keyText as (string)
        this.setKeyText_serialize(keyText_casted)
        return
    }
    private getKeySource(): KeySource {
        return this.getKeySource_serialize()
    }
    private setKeySource(keySource: KeySource): void {
        const keySource_casted = keySource as (KeySource)
        this.setKeySource_serialize(keySource_casted)
        return
    }
    private getDeviceId(): number {
        return this.getDeviceId_serialize()
    }
    private setDeviceId(deviceId: number): void {
        const deviceId_casted = deviceId as (number)
        this.setDeviceId_serialize(deviceId_casted)
        return
    }
    private getMetaKey(): number {
        return this.getMetaKey_serialize()
    }
    private setMetaKey(metaKey: number): void {
        const metaKey_casted = metaKey as (number)
        this.setMetaKey_serialize(metaKey_casted)
        return
    }
    private getTimestamp(): number {
        return this.getTimestamp_serialize()
    }
    private setTimestamp(timestamp: number): void {
        const timestamp_casted = timestamp as (number)
        this.setTimestamp_serialize(timestamp_casted)
        return
    }
    private getStopPropagation(): (() => void) {
        return this.getStopPropagation_serialize()
    }
    private setStopPropagation(stopPropagation: (() => void)): void {
        const stopPropagation_casted = stopPropagation as ((() => void))
        this.setStopPropagation_serialize(stopPropagation_casted)
        return
    }
    private getIntentionCode(): IntentionCode {
        return this.getIntentionCode_serialize()
    }
    private setIntentionCode(intentionCode: IntentionCode): void {
        const intentionCode_casted = intentionCode as (IntentionCode)
        this.setIntentionCode_serialize(intentionCode_casted)
        return
    }
    private getUnicode(): number {
        return this.getUnicode_serialize()
    }
    private setUnicode(unicode: number): void {
        const unicode_casted = unicode as (number)
        this.setUnicode_serialize(unicode_casted)
        return
    }
    private getModifierKeyState_serialize(keys: Array<string>): boolean {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(keys.length as int32)
        for (let i = 0; i < keys.length; i++) {
            const keys_element : string = keys[i]
            thisSerializer.writeString(keys_element)
        }
        const retval  = ArkUIGeneratedNativeModule._KeyEvent_getModifierKeyState(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private getType_serialize(): KeyType {
        const retval  = ArkUIGeneratedNativeModule._KeyEvent_getType(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setType_serialize(type: KeyType): void {
        ArkUIGeneratedNativeModule._KeyEvent_setType(this.peer!.ptr, type.valueOf())
    }
    private getKeyCode_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._KeyEvent_getKeyCode(this.peer!.ptr)
        return retval
    }
    private setKeyCode_serialize(keyCode: number): void {
        ArkUIGeneratedNativeModule._KeyEvent_setKeyCode(this.peer!.ptr, keyCode)
    }
    private getKeyText_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._KeyEvent_getKeyText(this.peer!.ptr)
        return retval
    }
    private setKeyText_serialize(keyText: string): void {
        ArkUIGeneratedNativeModule._KeyEvent_setKeyText(this.peer!.ptr, keyText)
    }
    private getKeySource_serialize(): KeySource {
        const retval  = ArkUIGeneratedNativeModule._KeyEvent_getKeySource(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setKeySource_serialize(keySource: KeySource): void {
        ArkUIGeneratedNativeModule._KeyEvent_setKeySource(this.peer!.ptr, keySource.valueOf())
    }
    private getDeviceId_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._KeyEvent_getDeviceId(this.peer!.ptr)
        return retval
    }
    private setDeviceId_serialize(deviceId: number): void {
        ArkUIGeneratedNativeModule._KeyEvent_setDeviceId(this.peer!.ptr, deviceId)
    }
    private getMetaKey_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._KeyEvent_getMetaKey(this.peer!.ptr)
        return retval
    }
    private setMetaKey_serialize(metaKey: number): void {
        ArkUIGeneratedNativeModule._KeyEvent_setMetaKey(this.peer!.ptr, metaKey)
    }
    private getTimestamp_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._KeyEvent_getTimestamp(this.peer!.ptr)
        return retval
    }
    private setTimestamp_serialize(timestamp: number): void {
        ArkUIGeneratedNativeModule._KeyEvent_setTimestamp(this.peer!.ptr, timestamp)
    }
    private getStopPropagation_serialize(): (() => void) {
        const retval  = ArkUIGeneratedNativeModule._KeyEvent_getStopPropagation(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setStopPropagation_serialize(stopPropagation: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(stopPropagation)
        ArkUIGeneratedNativeModule._KeyEvent_setStopPropagation(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getIntentionCode_serialize(): IntentionCode {
        const retval  = ArkUIGeneratedNativeModule._KeyEvent_getIntentionCode(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
        const returnResult : IntentionCode = retvalDeserializer.readIntentionCode()
        return returnResult
    }
    private setIntentionCode_serialize(intentionCode: IntentionCode): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeIntentionCode(intentionCode)
        ArkUIGeneratedNativeModule._KeyEvent_setIntentionCode(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getUnicode_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._KeyEvent_getUnicode(this.peer!.ptr)
        return retval
    }
    private setUnicode_serialize(unicode: number): void {
        ArkUIGeneratedNativeModule._KeyEvent_setUnicode(this.peer!.ptr, unicode)
    }
    public static fromPtr(ptr: KPointer): KeyEventInternal {
        const obj : KeyEventInternal = new KeyEventInternal()
        obj.peer = new Finalizable(ptr, KeyEventInternal.getFinalizer())
        return obj
    }
}
