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

import { TransitionEffects, TranslateOptions, RotateOptions, ScaleOptions, TransitionEdge, AnimateParam } from "./ArkCommonInterfaces"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class TransitionEffectInternal {
    public static fromPtr(ptr: KPointer): TransitionEffect {
        const obj : TransitionEffect = new TransitionEffect(undefined, undefined)
        obj.peer = new Finalizable(ptr, TransitionEffect.getFinalizer())
        return obj
    }
}
export class TransitionEffect implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static get IDENTITY(): TransitionEffect {
        return TransitionEffect.getIDENTITY()
    }
    static get OPACITY(): TransitionEffect {
        return TransitionEffect.getOPACITY()
    }
    static get SLIDE(): TransitionEffect {
        return TransitionEffect.getSLIDE()
    }
    static get SLIDE_SWITCH(): TransitionEffect {
        return TransitionEffect.getSLIDE_SWITCH()
    }
    static ctor_transitioneffect(type: string, effect: TransitionEffects): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        const effect_identity  = effect.identity
        const effect_opacity  = effect.opacity
        thisSerializer.writeNumber(effect_opacity)
        const effect_slideSwitch  = effect.slideSwitch
        const effect_move  = effect.move
        thisSerializer.writeInt32(effect_move.valueOf())
        const effect_translate  = effect.translate
        thisSerializer.writeTranslateOptions(effect_translate)
        const effect_rotate  = effect.rotate
        thisSerializer.writeRotateOptions(effect_rotate)
        const effect_scale  = effect.scale
        thisSerializer.writeScaleOptions(effect_scale)
        const effect_asymmetric  = effect.asymmetric
        const effect_asymmetric_appear  = effect_asymmetric.appear
        thisSerializer.writeTransitionEffect(effect_asymmetric_appear)
        const effect_asymmetric_disappear  = effect_asymmetric.disappear
        thisSerializer.writeTransitionEffect(effect_asymmetric_disappear)
        const retval  = ArkUIGeneratedNativeModule._TransitionEffect_ctor(type, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(type?: string, effect?: TransitionEffects) {
        if (((type) !== (undefined)) || ((effect) !== (undefined)))
        {
            const ctorPtr : KPointer = TransitionEffect.ctor_transitioneffect((type)!, (effect)!)
            this.peer = new Finalizable(ctorPtr, TransitionEffect.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TransitionEffect_getFinalizer()
    }
    public static translate(options: TranslateOptions): TransitionEffect {
        const options_casted = options as (TranslateOptions)
        return TransitionEffect.translate_serialize(options_casted)
    }
    public static rotate(options: RotateOptions): TransitionEffect {
        const options_casted = options as (RotateOptions)
        return TransitionEffect.rotate_serialize(options_casted)
    }
    public static scale(options: ScaleOptions): TransitionEffect {
        const options_casted = options as (ScaleOptions)
        return TransitionEffect.scale_serialize(options_casted)
    }
    public static opacity(alpha: number): TransitionEffect {
        const alpha_casted = alpha as (number)
        return TransitionEffect.opacity_serialize(alpha_casted)
    }
    public static move(edge: TransitionEdge): TransitionEffect {
        const edge_casted = edge as (TransitionEdge)
        return TransitionEffect.move_serialize(edge_casted)
    }
    public static asymmetric(appear: TransitionEffect, disappear: TransitionEffect): TransitionEffect {
        const appear_casted = appear as (TransitionEffect)
        const disappear_casted = disappear as (TransitionEffect)
        return TransitionEffect.asymmetric_serialize(appear_casted, disappear_casted)
    }
    public animation(value: AnimateParam): TransitionEffect {
        const value_casted = value as (AnimateParam)
        return this.animation_serialize(value_casted)
    }
    public combine(transitionEffect: TransitionEffect): TransitionEffect {
        const transitionEffect_casted = transitionEffect as (TransitionEffect)
        return this.combine_serialize(transitionEffect_casted)
    }
    private static getIDENTITY(): TransitionEffect {
        return TransitionEffect.getIDENTITY_serialize()
    }
    private static getOPACITY(): TransitionEffect {
        return TransitionEffect.getOPACITY_serialize()
    }
    private static getSLIDE(): TransitionEffect {
        return TransitionEffect.getSLIDE_serialize()
    }
    private static getSLIDE_SWITCH(): TransitionEffect {
        return TransitionEffect.getSLIDE_SWITCH_serialize()
    }
    private static translate_serialize(options: TranslateOptions): TransitionEffect {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeTranslateOptions(options)
        const retval  = ArkUIGeneratedNativeModule._TransitionEffect_translate(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : TransitionEffect = TransitionEffectInternal.fromPtr(retval)
        return obj
    }
    private static rotate_serialize(options: RotateOptions): TransitionEffect {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeRotateOptions(options)
        const retval  = ArkUIGeneratedNativeModule._TransitionEffect_rotate(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : TransitionEffect = TransitionEffectInternal.fromPtr(retval)
        return obj
    }
    private static scale_serialize(options: ScaleOptions): TransitionEffect {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeScaleOptions(options)
        const retval  = ArkUIGeneratedNativeModule._TransitionEffect_scale(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : TransitionEffect = TransitionEffectInternal.fromPtr(retval)
        return obj
    }
    private static opacity_serialize(alpha: number): TransitionEffect {
        const retval  = ArkUIGeneratedNativeModule._TransitionEffect_opacity(alpha)
        const obj : TransitionEffect = TransitionEffectInternal.fromPtr(retval)
        return obj
    }
    private static move_serialize(edge: TransitionEdge): TransitionEffect {
        const retval  = ArkUIGeneratedNativeModule._TransitionEffect_move(edge.valueOf())
        const obj : TransitionEffect = TransitionEffectInternal.fromPtr(retval)
        return obj
    }
    private static asymmetric_serialize(appear: TransitionEffect, disappear: TransitionEffect): TransitionEffect {
        const retval  = ArkUIGeneratedNativeModule._TransitionEffect_asymmetric(toPeerPtr(appear), toPeerPtr(disappear))
        const obj : TransitionEffect = TransitionEffectInternal.fromPtr(retval)
        return obj
    }
    private animation_serialize(value: AnimateParam): TransitionEffect {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeAnimateParam(value)
        const retval  = ArkUIGeneratedNativeModule._TransitionEffect_animation(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : TransitionEffect = TransitionEffectInternal.fromPtr(retval)
        return obj
    }
    private combine_serialize(transitionEffect: TransitionEffect): TransitionEffect {
        const retval  = ArkUIGeneratedNativeModule._TransitionEffect_combine(this.peer!.ptr, toPeerPtr(transitionEffect))
        const obj : TransitionEffect = TransitionEffectInternal.fromPtr(retval)
        return obj
    }
    private static getIDENTITY_serialize(): TransitionEffect {
        const retval  = ArkUIGeneratedNativeModule._TransitionEffect_getIDENTITY()
        const obj : TransitionEffect = TransitionEffectInternal.fromPtr(retval)
        return obj
    }
    private static getOPACITY_serialize(): TransitionEffect {
        const retval  = ArkUIGeneratedNativeModule._TransitionEffect_getOPACITY()
        const obj : TransitionEffect = TransitionEffectInternal.fromPtr(retval)
        return obj
    }
    private static getSLIDE_serialize(): TransitionEffect {
        const retval  = ArkUIGeneratedNativeModule._TransitionEffect_getSLIDE()
        const obj : TransitionEffect = TransitionEffectInternal.fromPtr(retval)
        return obj
    }
    private static getSLIDE_SWITCH_serialize(): TransitionEffect {
        const retval  = ArkUIGeneratedNativeModule._TransitionEffect_getSLIDE_SWITCH()
        const obj : TransitionEffect = TransitionEffectInternal.fromPtr(retval)
        return obj
    }
}
