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

import { ArkThemeScopeManager } from "#arktheme"
import { SerializerBase, DeserializerBase, Finalizable, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { CommonConfiguration, Bindable_Boolean_serializer, ArkCommonMethodPeer, CommonMethod, Bindable, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { Resource_serializer } from "./../framework/resource"
import { MarkStyle_serializer, ResourceColor, MarkStyle } from "./units"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { Color, CheckBoxShape } from "./enums"
import { Resource } from "global.resource"
import { ContentModifier, AttributeModifier, hookCheckBoxGroupContentModifier, hookCheckboxGroupAttributeModifier, AttributeUpdater } from "#handwritten"
import { ModifierStateManager } from '../CommonModifier';
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { CheckboxGroupModifier } from "./../CheckboxGroupModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
export interface CheckBoxGroupConfiguration {
    name: string
    status: SelectStatus
    triggerChange(isSelect: boolean): void
}
export class CheckBoxGroupConfigurationInternal implements MaterializedBase,CommonConfiguration<CheckBoxGroupConfiguration>,CheckBoxGroupConfiguration {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get enabled(): boolean {
        return this.getEnabled()
    }
    set enabled(enabled: boolean) {
        this.setEnabled(enabled)
    }
    get contentModifier(): ContentModifier<CheckBoxGroupConfiguration> {
        return this.getContentModifier()
    }
    set contentModifier(contentModifier: ContentModifier<CheckBoxGroupConfiguration>) {
        this.setContentModifier(contentModifier)
    }
    get name(): string {
        return this.getName()
    }
    set name(name: string) {
        this.setName(name)
    }
    get status(): SelectStatus {
        return this.getStatus()
    }
    set status(status: SelectStatus) {
        this.setStatus(status)
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, CheckBoxGroupConfigurationInternal.getFinalizer())
    }
    constructor() {
        this(CheckBoxGroupConfigurationInternal.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._CheckBoxGroupConfiguration_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._CheckBoxGroupConfiguration_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): CheckBoxGroupConfigurationInternal {
        return new CheckBoxGroupConfigurationInternal(ptr)
    }
    public triggerChange(isSelect: boolean): void {
        const isSelect_casted = isSelect as (boolean)
        this.triggerChange_serialize(isSelect_casted)
        return
    }
    private getEnabled(): boolean {
        return this.getEnabled_serialize()
    }
    private setEnabled(enabled: boolean): void {
        const enabled_casted = enabled as (boolean)
        this.setEnabled_serialize(enabled_casted)
        return
    }
    private getContentModifier(): ContentModifier<CheckBoxGroupConfiguration> {
        return this.getContentModifier_serialize()
    }
    private setContentModifier(contentModifier: ContentModifier<CheckBoxGroupConfiguration>): void {
        const contentModifier_casted = contentModifier as (ContentModifier<CheckBoxGroupConfiguration>)
        this.setContentModifier_serialize(contentModifier_casted)
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
    private getStatus(): SelectStatus {
        return this.getStatus_serialize()
    }
    private setStatus(status: SelectStatus): void {
        const status_casted = status as (SelectStatus)
        this.setStatus_serialize(status_casted)
        return
    }
    triggerChange_serialize(isSelect: boolean): void {
        ArkUIGeneratedNativeModule._CheckBoxGroupConfiguration_triggerChange(this.peer!.ptr, isSelect ? 1 : 0)
    }
    private getEnabled_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._CheckBoxGroupConfiguration_getEnabled(this.peer!.ptr)
        return retval
    }
    private setEnabled_serialize(enabled: boolean): void {
        ArkUIGeneratedNativeModule._CheckBoxGroupConfiguration_setEnabled(this.peer!.ptr, enabled ? 1 : 0)
    }
    private getContentModifier_serialize(): ContentModifier<CheckBoxGroupConfiguration> {
        const retval  = ArkUIGeneratedNativeModule._CheckBoxGroupConfiguration_getContentModifier(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : ContentModifier<CheckBoxGroupConfiguration> = (retvalDeserializer.readObject() as ContentModifier<CheckBoxGroupConfiguration>)
        return returnResult
    }
    private setContentModifier_serialize(contentModifier: ContentModifier<CheckBoxGroupConfiguration>): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        ArkUIGeneratedNativeModule._CheckBoxGroupConfiguration_setContentModifier(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getName_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._CheckBoxGroupConfiguration_getName(this.peer!.ptr)
        return retval
    }
    private setName_serialize(name: string): void {
        ArkUIGeneratedNativeModule._CheckBoxGroupConfiguration_setName(this.peer!.ptr, name)
    }
    private getStatus_serialize(): SelectStatus {
        const retval  = ArkUIGeneratedNativeModule._CheckBoxGroupConfiguration_getStatus(this.peer!.ptr)
        return SelectStatus.fromValue(retval)
    }
    private setStatus_serialize(status: SelectStatus): void {
        ArkUIGeneratedNativeModule._CheckBoxGroupConfiguration_setStatus(this.peer!.ptr, status.valueOf())
    }
}
export class ArkCheckboxGroupPeer extends ArkCommonMethodPeer {
    attributeSet?: CheckboxGroupModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkCheckboxGroupPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._CheckboxGroup_construct(peerId, flags)
        const _peer  = new ArkCheckboxGroupPeer(_peerPtr, peerId, 'CheckboxGroup', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setCheckboxGroupOptionsAttribute(options?: CheckboxGroupOptions): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            CheckboxGroupOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CheckboxGroupInterface_setCheckboxGroupOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectAllAttribute(value: boolean | Bindable<boolean> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof boolean) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as boolean
                thisSerializer.writeBoolean(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Bindable<boolean>) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as Bindable<boolean>
                Bindable_Boolean_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CheckboxGroupAttribute_setSelectAll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(valueTmpValueForIdx0.getOrdinal())
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CheckboxGroupAttribute_setSelectedColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setUnselectedColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(valueTmpValueForIdx0.getOrdinal())
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CheckboxGroupAttribute_setUnselectedColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMarkAttribute(value: MarkStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            MarkStyle_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CheckboxGroupAttribute_setMark(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnChangeAttribute(value: OnCheckboxGroupChangeCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CheckboxGroupAttribute_setOnChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCheckboxShapeAttribute(value: CheckBoxShape | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as CheckBoxShape)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CheckboxGroupAttribute_setCheckboxShape(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum SelectStatus {
    ALL = 0,
    All = 0,
    PART = 1,
    Part = 1,
    NONE = 2,
    None = 2
}
export interface CheckboxGroupOptions {
    group?: string;
}
export interface CheckboxGroupResult {
    name: Array<string>;
    status: SelectStatus;
}
export type OnCheckboxGroupChangeCallback = (value: CheckboxGroupResult) => void;
export interface CheckboxGroupAttribute extends CommonMethod {
    setCheckboxGroupOptions(options?: CheckboxGroupOptions): this {
        throw new Error("Unimplemented method setCheckboxGroupOptions")
    }
    selectAll(value: boolean | Bindable<boolean> | undefined): this {
        throw new Error("Unimplemented method selectAll")
    }
    selectedColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method selectedColor")
    }
    unselectedColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method unselectedColor")
    }
    mark(value: MarkStyle | undefined): this {
        throw new Error("Unimplemented method mark")
    }
    onChange(value: OnCheckboxGroupChangeCallback | undefined): this {
        throw new Error("Unimplemented method onChange")
    }
    checkboxShape(value: CheckBoxShape | undefined): this {
        throw new Error("Unimplemented method checkboxShape")
    }
    contentModifier(value: ContentModifier<CheckBoxGroupConfiguration> | undefined): this {
        throw new Error("Unimplemented method contentModifier")
    }
    attributeModifier(value: AttributeModifier<CheckboxGroupAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkCheckboxGroupStyle extends ArkCommonMethodStyle implements CheckboxGroupAttribute {
    selectAll_value?: boolean | Bindable<boolean> | undefined
    selectedColor_value?: ResourceColor | undefined
    unselectedColor_value?: ResourceColor | undefined
    mark_value?: MarkStyle | undefined
    onChange_value?: OnCheckboxGroupChangeCallback | undefined
    checkboxShape_value?: CheckBoxShape | undefined
    attributeModifier_value?: AttributeModifier<CheckboxGroupAttribute> | AttributeModifier<CommonMethod> | undefined
    contentModifier_value?: ContentModifier<CheckBoxGroupConfiguration> | undefined
    setCheckboxGroupOptions(options?: CheckboxGroupOptions): this {
        return this
    }
    selectAll(value: boolean | Bindable<boolean> | undefined): this {
        return this
    }
    selectedColor(value: ResourceColor | undefined): this {
        return this
    }
    unselectedColor(value: ResourceColor | undefined): this {
        return this
    }
    mark(value: MarkStyle | undefined): this {
        return this
    }
    onChange(value: OnCheckboxGroupChangeCallback | undefined): this {
        return this
    }
    checkboxShape(value: CheckBoxShape | undefined): this {
        return this
    }
    contentModifier(value: ContentModifier<CheckBoxGroupConfiguration> | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<CheckboxGroupAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkCheckboxGroupComponent extends ArkCommonMethodComponent implements CheckboxGroupAttribute {
    getPeer(): ArkCheckboxGroupPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkCheckboxGroupPeer)
    }
    public setCheckboxGroupOptions(options?: CheckboxGroupOptions): this {
        if (this.checkPriority("setCheckboxGroupOptions")) {
            const options_casted = options as (CheckboxGroupOptions | undefined)
            this.getPeer()?.setCheckboxGroupOptionsAttribute(options_casted)
            this.applyOptionsFinish('CheckboxGroupAttribute');
            return this
        }
        return this
    }
    public selectAll(value: boolean | Bindable<boolean> | undefined): this {
        if (this.checkPriority("selectAll")) {
            const value_casted = value as (boolean | Bindable<boolean> | undefined)
            this.getPeer()?.setSelectAllAttribute(value_casted)
            return this
        }
        return this
    }
    public selectedColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("selectedColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setSelectedColorAttribute(value_casted)
            return this
        }
        return this
    }
    public unselectedColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("unselectedColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setUnselectedColorAttribute(value_casted)
            return this
        }
        return this
    }
    public mark(value: MarkStyle | undefined): this {
        if (this.checkPriority("mark")) {
            const value_casted = value as (MarkStyle | undefined)
            this.getPeer()?.setMarkAttribute(value_casted)
            return this
        }
        return this
    }
    public onChange(value: OnCheckboxGroupChangeCallback | undefined): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (OnCheckboxGroupChangeCallback | undefined)
            this.getPeer()?.setOnChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public checkboxShape(value: CheckBoxShape | undefined): this {
        if (this.checkPriority("checkboxShape")) {
            const value_casted = value as (CheckBoxShape | undefined)
            this.getPeer()?.setCheckboxShapeAttribute(value_casted)
            return this
        }
        return this
    }
    public contentModifier(value: ContentModifier<CheckBoxGroupConfiguration> | undefined): this {
        if (this.checkPriority("contentModifier")) {
            hookCheckBoxGroupContentModifier(this, value)
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<CheckboxGroupAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
          hookCheckboxGroupAttributeModifier(this, value);
        })
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
    public applyOptionsFinish(traceName: string): void {
        super.applyOptionsFinish(traceName)
    }
}

@memo
export function CheckboxGroupImpl(
    @memo
    style: ((attributes: CheckboxGroupAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkCheckboxGroupComponent>((): ArkCheckboxGroupComponent => {
        return new ArkCheckboxGroupComponent()
    })
    NodeAttach<ArkCheckboxGroupPeer>((): ArkCheckboxGroupPeer => ArkCheckboxGroupPeer.create(receiver), (peer: ArkCheckboxGroupPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

export class CheckBoxGroupConfiguration_serializer {
    public static write(buffer: SerializerBase, value: CheckBoxGroupConfiguration): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): CheckBoxGroupConfiguration {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return CheckBoxGroupConfigurationInternal.fromPtr(ptr)
    }
}
export class CheckboxGroupOptions_serializer {
    public static write(buffer: SerializerBase, value: CheckboxGroupOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForGroup  = value.group
        if (valueHolderForGroup !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForGroupTmpValue  = valueHolderForGroup!
            valueSerializer.writeString(valueHolderForGroupTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): CheckboxGroupOptions {
        let valueDeserializer : DeserializerBase = buffer
        const groupTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let groupTmpBuf : string | undefined = undefined
        if ((groupTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            groupTmpBuf = (valueDeserializer.readString() as string)
        }
        const groupTmpResult : string | undefined = groupTmpBuf
        let value : CheckboxGroupOptions = ({group: groupTmpResult} as CheckboxGroupOptions)
        return value
    }
}
export class CheckboxGroupResult_serializer {
    public static write(buffer: SerializerBase, value: CheckboxGroupResult): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForName  = value.name
        valueSerializer.writeInt32((valueHolderForName.length).toInt())
        for (let valueHolderForNameCounterI = 0; valueHolderForNameCounterI < valueHolderForName.length; valueHolderForNameCounterI++) {
            const valueHolderForNameTmpElement : string = valueHolderForName[valueHolderForNameCounterI]
            valueSerializer.writeString(valueHolderForNameTmpElement)
        }
        const valueHolderForStatus  = value.status
        valueSerializer.writeInt32(valueHolderForStatus.valueOf())
    }
    public static read(buffer: DeserializerBase): CheckboxGroupResult {
        let valueDeserializer : DeserializerBase = buffer
        const nameTmpBufLength : int32 = valueDeserializer.readInt32()
        let nameTmpBuf : Array<string> = new Array<string>(nameTmpBufLength)
        for (let nameTmpBufBufCounterI = 0; nameTmpBufBufCounterI < nameTmpBufLength; nameTmpBufBufCounterI++) {
            nameTmpBuf[nameTmpBufBufCounterI] = (valueDeserializer.readString() as string)
        }
        const nameTmpResult : Array<string> = nameTmpBuf
        const statusTmpResult : SelectStatus = SelectStatus.fromValue(valueDeserializer.readInt32())
        let value : CheckboxGroupResult = ({name: nameTmpResult, status: statusTmpResult} as CheckboxGroupResult)
        return value
    }
}
