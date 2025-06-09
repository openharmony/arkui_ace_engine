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

import { TextMenuItem, TextRange } from "./ArkTextCommonInterfaces"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export interface EditMenuOptions {
    onCreateMenu(menuItems: Array<TextMenuItem>): Array<TextMenuItem>
    onMenuItemClick(menuItem: TextMenuItem, range: TextRange): boolean
}
export class EditMenuOptionsInternal implements MaterializedBase,EditMenuOptions {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_editmenuoptions(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._EditMenuOptions_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = EditMenuOptionsInternal.ctor_editmenuoptions()
        this.peer = new Finalizable(ctorPtr, EditMenuOptionsInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._EditMenuOptions_getFinalizer()
    }
    public onCreateMenu(menuItems: Array<TextMenuItem>): Array<TextMenuItem> {
        const menuItems_casted = menuItems as (Array<TextMenuItem>)
        return this.onCreateMenu_serialize(menuItems_casted)
    }
    public onMenuItemClick(menuItem: TextMenuItem, range: TextRange): boolean {
        const menuItem_casted = menuItem as (TextMenuItem)
        const range_casted = range as (TextRange)
        return this.onMenuItemClick_serialize(menuItem_casted, range_casted)
    }
    private onCreateMenu_serialize(menuItems: Array<TextMenuItem>): Array<TextMenuItem> {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(menuItems.length as int32)
        for (let i = 0; i < menuItems.length; i++) {
            const menuItems_element : TextMenuItem = menuItems[i]
            thisSerializer.writeTextMenuItem(menuItems_element)
        }
        const retval  = ArkUIGeneratedNativeModule._EditMenuOptions_onCreateMenu(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<TextMenuItem> = new Array<TextMenuItem>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = retvalDeserializer.readTextMenuItem()
        }
        const returnResult : Array<TextMenuItem> = buffer
        return returnResult
    }
    private onMenuItemClick_serialize(menuItem: TextMenuItem, range: TextRange): boolean {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeTextMenuItem(menuItem)
        thisSerializer.writeTextRange(range)
        const retval  = ArkUIGeneratedNativeModule._EditMenuOptions_onMenuItemClick(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    public static fromPtr(ptr: KPointer): EditMenuOptionsInternal {
        const obj : EditMenuOptionsInternal = new EditMenuOptionsInternal()
        obj.peer = new Finalizable(ptr, EditMenuOptionsInternal.getFinalizer())
        return obj
    }
}
