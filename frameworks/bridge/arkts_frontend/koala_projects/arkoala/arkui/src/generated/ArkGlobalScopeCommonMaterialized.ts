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

import { Context, AnimateParam, FinishCallbackType, ExpectedFrameRateRange } from "./ArkCommonInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { Curve, PlayMode } from "./ArkEnumsInterfaces"
import { ICurve, ICurveInternal } from "./ArkICurveMaterialized"
import { Finalizable, isResource, isInstanceOf, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, KPointer, MaterializedBase } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export class GlobalScope_common {
    public static getContext(component?: Object): Context {
        const component_casted = component as (Object | undefined)
        return GlobalScope_common.getContext_serialize(component_casted)
    }
    public static postCardAction(component: Object, action: Object): void {
        const component_casted = component as (Object)
        const action_casted = action as (Object)
        GlobalScope_common.postCardAction_serialize(component_casted, action_casted)
        return
    }
    public static dollar_r(value: string, params: Array<any>): Resource {
        const value_casted = value as (string)
        const params_casted = params as (Array<any>)
        return GlobalScope_common.dollar_r_serialize(value_casted, params_casted)
    }
    public static dollar_rawfile(value: string): Resource {
        const value_casted = value as (string)
        return GlobalScope_common.dollar_rawfile_serialize(value_casted)
    }
    public static animateTo(value: AnimateParam, event: (() => void)): void {
        const value_casted = value as (AnimateParam)
        const event_casted = event as ((() => void))
        GlobalScope_common.animateTo_serialize(value_casted, event_casted)
        return
    }
    public static animateToImmediately(value: AnimateParam, event: (() => void)): void {
        const value_casted = value as (AnimateParam)
        const event_casted = event as ((() => void))
        GlobalScope_common.animateToImmediately_serialize(value_casted, event_casted)
        return
    }
    public static vp2px(value: number): number {
        const value_casted = value as (number)
        return GlobalScope_common.vp2px_serialize(value_casted)
    }
    public static px2vp(value: number): number {
        const value_casted = value as (number)
        return GlobalScope_common.px2vp_serialize(value_casted)
    }
    public static fp2px(value: number): number {
        const value_casted = value as (number)
        return GlobalScope_common.fp2px_serialize(value_casted)
    }
    public static px2fp(value: number): number {
        const value_casted = value as (number)
        return GlobalScope_common.px2fp_serialize(value_casted)
    }
    public static lpx2px(value: number): number {
        const value_casted = value as (number)
        return GlobalScope_common.lpx2px_serialize(value_casted)
    }
    public static px2lpx(value: number): number {
        const value_casted = value as (number)
        return GlobalScope_common.px2lpx_serialize(value_casted)
    }
    private static getContext_serialize(component?: Object): Context {
        const thisSerializer: Serializer = Serializer.hold()
        let component_type: int32 = RuntimeType.UNDEFINED
        component_type = runtimeType(component)
        thisSerializer.writeInt8(component_type)
        if ((RuntimeType.UNDEFINED) != (component_type)) {
            const component_value = component!
            thisSerializer.writeCustomObject("Object", component_value)
        }
        const retval = ArkUIGeneratedNativeModule._GlobalScope_common_getContext(thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return new Deserializer(retval.buffer, retval.byteLength).readContext()
    }
    private static postCardAction_serialize(component: Object, action: Object): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeCustomObject("Object", component)
        thisSerializer.writeCustomObject("Object", action)
        ArkUIGeneratedNativeModule._GlobalScope_common_postCardAction(thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private static dollar_r_serialize(value: string, params: Array<any>): Resource {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeInt32(params.length)
        for (let i = 0; i < params.length; i++) {
            const params_element: any = params[i]
            thisSerializer.writeCustomObject("Any", params_element)
        }
        const retval = ArkUIGeneratedNativeModule._GlobalScope_common_dollar_r(value, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return new Deserializer(retval.buffer, retval.byteLength).readResource()
    }
    private static dollar_rawfile_serialize(value: string): Resource {
        const retval = ArkUIGeneratedNativeModule._GlobalScope_common_dollar_rawfile(value)
        return new Deserializer(retval.buffer, retval.byteLength).readResource()
    }
    private static animateTo_serialize(value: AnimateParam, event: (() => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeAnimateParam(value)
        thisSerializer.holdAndWriteCallback(event)
        ArkUIGeneratedNativeModule._GlobalScope_common_animateTo(thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private static animateToImmediately_serialize(value: AnimateParam, event: (() => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeAnimateParam(value)
        thisSerializer.holdAndWriteCallback(event)
        ArkUIGeneratedNativeModule._GlobalScope_common_animateToImmediately(thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private static vp2px_serialize(value: number): number {
        const retval = ArkUIGeneratedNativeModule._GlobalScope_common_vp2px(value)
        return retval
    }
    private static px2vp_serialize(value: number): number {
        const retval = ArkUIGeneratedNativeModule._GlobalScope_common_px2vp(value)
        return retval
    }
    private static fp2px_serialize(value: number): number {
        const retval = ArkUIGeneratedNativeModule._GlobalScope_common_fp2px(value)
        return retval
    }
    private static px2fp_serialize(value: number): number {
        const retval = ArkUIGeneratedNativeModule._GlobalScope_common_px2fp(value)
        return retval
    }
    private static lpx2px_serialize(value: number): number {
        const retval = ArkUIGeneratedNativeModule._GlobalScope_common_lpx2px(value)
        return retval
    }
    private static px2lpx_serialize(value: number): number {
        const retval = ArkUIGeneratedNativeModule._GlobalScope_common_px2lpx(value)
        return retval
    }
}
