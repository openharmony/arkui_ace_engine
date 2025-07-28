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

import { Scroller, ScrollerInternal } from "./ArkScrollerMaterialized"
import { ScrollOptions, ScrollEdgeOptions, ScrollPageOptions, OffsetResult, ScrollAlign, ScrollToIndexOptions } from "./ArkScrollInterfaces"
import { Edge, Axis } from "./ArkEnumsInterfaces"
import { Literal_Boolean_next_Axis_direction } from "./SyntheticDeclarations"
import { Length } from "./ArkUnitsInterfaces"
import { RectResult } from "./ArkCommonInterfaces"
import { CloseSwipeActionOptions, VisibleListContentInfo } from "./ArkListInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class ListScrollerInternal {
    public static fromPtr(ptr: KPointer): ListScroller {
        const obj : ListScroller = new ListScroller()
        obj.peer = new Finalizable(ptr, ListScroller.getFinalizer())
        return obj
    }
}
export class ListScroller extends Scroller implements MaterializedBase {
    static ctor_listscroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._ListScroller_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = ListScroller.ctor_listscroller()
        this.peer = new Finalizable(ctorPtr, ListScroller.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ListScroller_getFinalizer()
    }
    public getItemRectInGroup(index: number, indexInGroup: number): RectResult {
        const index_casted = index as (number)
        const indexInGroup_casted = indexInGroup as (number)
        return this.getItemRectInGroup_serialize(index_casted, indexInGroup_casted)
    }
    public scrollToItemInGroup(index: number, indexInGroup: number, smooth?: boolean, align?: ScrollAlign): void {
        const index_casted = index as (number)
        const indexInGroup_casted = indexInGroup as (number)
        const smooth_casted = smooth as (boolean | undefined)
        const align_casted = align as (ScrollAlign | undefined)
        this.scrollToItemInGroup_serialize(index_casted, indexInGroup_casted, smooth_casted, align_casted)
        return
    }
    public closeAllSwipeActions(options?: CloseSwipeActionOptions): void {
        const options_casted = options as (CloseSwipeActionOptions | undefined)
        this.closeAllSwipeActions_serialize(options_casted)
        return
    }
    public getVisibleListContentInfo(x: number, y: number): VisibleListContentInfo {
        const x_casted = x as (number)
        const y_casted = y as (number)
        return this.getVisibleListContentInfo_serialize(x_casted, y_casted)
    }
    private getItemRectInGroup_serialize(index: number, indexInGroup: number): RectResult {
        const retval  = ArkUIGeneratedNativeModule._ListScroller_getItemRectInGroup(this.peer!.ptr, index, indexInGroup)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const returnResult : RectResult = retvalDeserializer.readRectResult()
        return returnResult
    }
    private scrollToItemInGroup_serialize(index: number, indexInGroup: number, smooth?: boolean, align?: ScrollAlign): void {
        const thisSerializer : Serializer = Serializer.hold()
        let smooth_type : int32 = RuntimeType.UNDEFINED
        smooth_type = runtimeType(smooth)
        thisSerializer.writeInt8(smooth_type as int32)
        if ((RuntimeType.UNDEFINED) != (smooth_type)) {
            const smooth_value  = smooth!
            thisSerializer.writeBoolean(smooth_value)
        }
        let align_type : int32 = RuntimeType.UNDEFINED
        align_type = runtimeType(align)
        thisSerializer.writeInt8(align_type as int32)
        if ((RuntimeType.UNDEFINED) != (align_type)) {
            const align_value  = (align as ScrollAlign)
            thisSerializer.writeInt32(align_value.valueOf())
        }
        ArkUIGeneratedNativeModule._ListScroller_scrollToItemInGroup(this.peer!.ptr, index, indexInGroup, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private closeAllSwipeActions_serialize(options?: CloseSwipeActionOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeCloseSwipeActionOptions(options_value)
        }
        ArkUIGeneratedNativeModule._ListScroller_closeAllSwipeActions(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getVisibleListContentInfo_serialize(x: number, y: number): VisibleListContentInfo {
        const retval  = ArkUIGeneratedNativeModule._ListScroller_getVisibleListContentInfo(this.peer!.ptr, x, y)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const returnResult : VisibleListContentInfo = retvalDeserializer.readVisibleListContentInfo()
        return returnResult
    }
}
