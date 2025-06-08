/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

import { ArkAnimate, ArkRotationOptions, ArkScaleOptions, ArkTranslateOptions } from "./shared/basic"

interface AsymmetricType {
    appear: TransitionEffect,
    disappear: TransitionEffect
}

enum TransitionEffectType {
    IDENTITY = 0,
    OPACITY,
    ASYMMETRIC,
    MOVE,
    TRANSLATE,
    SCALE,
    ROTATE,
    ANIMATION
}

enum TransitionEffectScope {
    ALL = 0,
    APPEAR,
    DISAPPEAR
}

export class TransitionEffect<
Type extends keyof TransitionEffects = keyof TransitionEffects,
Effect extends TransitionEffects[Type] = TransitionEffects[Type]
> {
    type_: Type
    effect_: Effect
    animation_: AnimateParam | undefined = undefined
    successor_: any = null
    constructor(type: Type, effect: Effect) {
        this.type_ = type
        this.effect_ = effect
    }

    static get IDENTITY(): TransitionEffect {
        return new TransitionEffect('identity', undefined)
    }
    static get OPACITY(): TransitionEffect {
        return new TransitionEffect('opacity', 0);
    }
    static get SLIDE(): TransitionEffect {
        return new TransitionEffect('asymmetric', {
            appear: new TransitionEffect('move', TransitionEdge.START),
            disappear: new TransitionEffect('move', TransitionEdge.END)
          });
    }

    static translate(options: TranslateOptions): TransitionEffect {
        return new TransitionEffect('translate', options)
    }

    static rotate(options: RotateOptions): TransitionEffect {
        return new TransitionEffect('rotate', options)
    }

    static scale(options: ScaleOptions): TransitionEffect {
        return new TransitionEffect('scale', options)
    }

    static move(edge: TransitionEdge): TransitionEffect {
        return new TransitionEffect('move', edge)
    }

    static asymmetric(appearEffect: TransitionEffect, disappearEffect: TransitionEffect) {
        return new TransitionEffect('asymmetric', {
          appear: appearEffect,
          disappear: disappearEffect
        });
    }

    animation(value: AnimateParam): this {
        this.animation_ = value;
        return this;
    }

    combine(nextEffect: TransitionEffect): this {
        if (nextEffect === null || nextEffect === undefined) {
          return this;
        }
        let lastEffect = this;
        while (lastEffect.successor_ != null) {
          lastEffect = lastEffect.successor_;
        }
        lastEffect.successor_ = nextEffect;
        return this;
    }
}

export class ArkTransitionEffect {
    original: TransitionEffect
    appearTransform: Array<number> = []
    disappearTransform: Array<number> = []


    constructor(value: TransitionEffect) {
        this.original = value
        this.iteratorTransition(value)
    }

    iteratorTransition(value: TransitionEffect, scope: TransitionEffectScope = TransitionEffectScope.ALL): void {
        if (value.type_ === 'asymmetric') {
            this.iteratorTransition((value.effect_ as AsymmetricType).appear, TransitionEffectScope.APPEAR)
            this.iteratorTransition((value.effect_ as AsymmetricType).disappear, TransitionEffectScope.DISAPPEAR)
        }
        if ('move' === value.type_) {
            this.setValue(TransitionEffectType.MOVE, [value.effect_ as number], scope)
        } else if ('opacity' === value.type_) {
            this.setValue(TransitionEffectType.OPACITY, [value.effect_ as number], scope)
        } else if ('identity' === value.type_) {
            this.setValue(TransitionEffectType.IDENTITY, [], scope)
        } else if (value.type_ === 'rotate') {
            let rotateOption = new ArkRotationOptions(value.effect_ as RotateOptions).getRotateOptions();
            this.setValue(TransitionEffectType.ROTATE, this.convertToArray(rotateOption), scope)
        } else if (value.type_ === 'translate') {
            let translateOption = new ArkTranslateOptions(value.effect_ as TranslateOptions).getTranslateOptions();
            this.setValue(TransitionEffectType.TRANSLATE, this.convertToArray(translateOption), scope)
        } else if (value.type_ === 'scale') {
            let scaleOption = new ArkScaleOptions(value.effect_ as ScaleOptions).getScaleOptions();
            this.setValue(TransitionEffectType.SCALE, this.convertToArray(scaleOption), scope)
        }
        if (value.animation_) {
            let animate = new ArkAnimate(value.animation_);
            this.setValue(TransitionEffectType.ANIMATION, this.convertToArray(animate.animateOptions).concat(animate.curve), scope)
        } else {
            this.setValue(-1, [], scope)
        }
        if (value.successor_) {
            this.iteratorTransition(value.successor_, scope)
        }
    }

    setValue(type: TransitionEffectType, value: Array<number>, scope: TransitionEffectScope) {
        if (scope === TransitionEffectScope.APPEAR || scope === TransitionEffectScope.ALL) {
            this.appearTransform.push(type)
            this.appearTransform = this.appearTransform.concat(value)
        }
        if (scope === TransitionEffectScope.DISAPPEAR || scope === TransitionEffectScope.ALL) {
            this.disappearTransform.push(type)
            this.disappearTransform = this.disappearTransform.concat(value)
        }
    }

    convertToArray(value: Float32Array): Array<number> {
        let ret = new Array<number>(value.length);
        value.forEach((val, index) => ret[index] = val)
        return ret
    }

    get appearValue() {
        return new Float32Array(this.appearTransform)
    }

    get disappearValue() {
        return new Float32Array(this.disappearTransform)
    }

}