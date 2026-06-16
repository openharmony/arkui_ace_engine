/*
 * Copyright (c) 2021-2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/// <reference path='./../../ark_component/src/import.ts' />
type ComponentObj = { component: any }

function loadComponent(): ComponentObj | undefined {
  if (loadComponent.componentObj === undefined && globalThis.__ArkComponent__ !== undefined) {
    class ArkImageAnimatorComponent extends globalThis.__ArkComponent__ {
        constructor(nativePtr: any, classType: any) {
            super(nativePtr, classType);
        }
        images(value: Array<ImageFrameInfo>): this {
            modifierWithKey(this._modifiersWithKeys, ImageAnimatorImagesModifier.identity, ImageAnimatorImagesModifier, value);
            return this;
        }
        state(value: AnimationStatus): this {
            modifierWithKey(this._modifiersWithKeys, ImageAnimatorStateModifier.identity, ImageAnimatorStateModifier, value);
            return this;
        }
        duration(value: number): this {
            modifierWithKey(this._modifiersWithKeys, ImageAnimatorDurationModifier.identity, ImageAnimatorDurationModifier, value);
            return this;
        }
        reverse(value: boolean): this {
            modifierWithKey(this._modifiersWithKeys, ImageAnimatorReverseModifier.identity, ImageAnimatorReverseModifier, value);
            return this;
        }
        fixedSize(value: boolean): this {
            modifierWithKey(this._modifiersWithKeys, ImageAnimatorFixedSizeModifier.identity, ImageAnimatorFixedSizeModifier, value);
            return this;
        }
        preDecode(value: number): this {
            throw new BusinessError(100201, 'preDecode function not supported in attributeModifier scenario.');
        }
        fillMode(value: FillMode): this {
            modifierWithKey(this._modifiersWithKeys, ImageAnimatorFillModeModifier.identity, ImageAnimatorFillModeModifier, value);
            return this;
        }
        iterations(value: number): this {
            modifierWithKey(this._modifiersWithKeys, ImageAnimatorIterationsModifier.identity, ImageAnimatorIterationsModifier, value);
            return this;
        }
        monitorInvisibleArea(value: boolean): this {
            modifierWithKey(this._modifiersWithKeys, ImageAnimatorAutoMonitorInvisibleAreaModifier.identity,
                ImageAnimatorAutoMonitorInvisibleAreaModifier, value);
            return this;
        }
        onStart(event: Function): this {
            modifierWithKey(this._modifiersWithKeys, ImageAnimatorOnStartModifier.identity, ImageAnimatorOnStartModifier, event);
            return this;
        }
        onPause(event: Function): this {
            modifierWithKey(this._modifiersWithKeys, ImageAnimatorOnPauseModifier.identity, ImageAnimatorOnPauseModifier, event);
            return this;
        }
        onRepeat(event: Function): this {
            modifierWithKey(this._modifiersWithKeys, ImageAnimatorOnRepeatModifier.identity, ImageAnimatorOnRepeatModifier, event);
            return this;
        }
        onCancel(event: Function): this {
            modifierWithKey(this._modifiersWithKeys, ImageAnimatorOnCancelModifier.identity, ImageAnimatorOnCancelModifier, event);
            return this;
        }
        onFinish(event: Function): this {
            modifierWithKey(this._modifiersWithKeys, ImageAnimatorOnFinishModifier.identity, ImageAnimatorOnFinishModifier, event);
            return this;
        }
    }

    class ImageAnimatorImagesModifier extends ModifierWithKey<Array<ImageFrameInfo>> {
        constructor(value: Array<ImageFrameInfo>) {
            super(value);
        }
        applyPeer(node: any, reset: boolean): void {
            if (reset) {
                getUINativeModule().imageAnimator.resetImages(node);
            }
            else {
                let arkImageFrame: ArkImageFrameInfoToArray = this.convertImageFrames(this.value);
                if (!arkImageFrame) {
                    getUINativeModule().imageAnimator.resetImages(node);
                }
                else {
                    getUINativeModule().imageAnimator.setImages(node, arkImageFrame.arrSrc,
                        arkImageFrame.arrWidth, arkImageFrame.arrHeight, arkImageFrame.arrTop,
                        arkImageFrame.arrLeft, arkImageFrame.arrDuration, arkImageFrame.arrSrc.length);
                }
            }
        }
        checkObjectDiff(): boolean {
            let checkDiff = true;
            if (this.value && this.value.length > 0 &&
                this.stageValue && this.stageValue.length > 0 &&
                this.value.length === this.stageValue.length) {
                let checkItemEqual: Boolean = false;

                for (let i: number = 0; i < this.value.length; i++) {
                    checkItemEqual = this.isEqual(this.stageValue[i], this.value[i]);
                    if (!checkItemEqual) {
                        checkDiff = !checkItemEqual;
                        break;
                    }
                }
            }
            return checkDiff;
        }

        isEqual = (one: ImageFrameInfo, another: ImageFrameInfo): boolean => {
            if (!(one.width === another.width &&
                one.height === another.height &&
                one.top === another.top &&
                one.left === another.left &&
                one.duration === another.duration)) {
                return true;
            }
            else {
                return !isBaseOrResourceEqual(one.src, another.src);
            }
        }

        convertImageFrames = (value: Array<ImageFrameInfo>): ArkImageFrameInfoToArray => {
            if (value && value.length > 0) {
                let isFlag: Boolean = true;
                for (let item of value) {
                    if (item.src === undefined || item.src === null) {
                        isFlag = false;
                        break;
                    }
                }
                if (isFlag) {
                    let array: ArkImageFrameInfoToArray = new ArkImageFrameInfoToArray();
                    for (let item of value) {
                        array.arrSrc.push(item.src);
                        array.arrWidth.push((item.width === undefined || item.width === null) ? 0 : item.width);
                        array.arrHeight.push((item.height === undefined || item.height === null) ? 0 : item.height);
                        array.arrTop.push((item.top === undefined || item.top === null) ? 0 : item.top);
                        array.arrLeft.push((item.left === undefined || item.left === null) ? 0 : item.left);
                        array.arrDuration.push((item.duration === undefined || item.duration === null) ? 0 : item.duration);
                    }
                    return array;
                }
                else {
                    return undefined;
                }
            }
            else {
                return undefined;
            }
        }
    }
    (ImageAnimatorImagesModifier as any).identity = Symbol('imageAnimatorImages');

    class ImageAnimatorDurationModifier extends ModifierWithKey<number> {
        constructor(value: number) {
            super(value);
        }
        applyPeer(node: any, reset: boolean): void {
            if (reset) {
                getUINativeModule().imageAnimator.resetDuration(node);
            }
            else {
                getUINativeModule().imageAnimator.setDuration(node, this.value);
            }
        }
        checkObjectDiff(): boolean {
            return this.stageValue !== this.value;
        }
    }
    (ImageAnimatorDurationModifier as any).identity = Symbol('imageAnimatorDuration');

    class ImageAnimatorReverseModifier extends ModifierWithKey<boolean> {
        constructor(value: boolean) {
            super(value);
        }
        applyPeer(node: any, reset: boolean): void {
            if (reset) {
                getUINativeModule().imageAnimator.resetReverse(node);
            }
            else {
                getUINativeModule().imageAnimator.setReverse(node, this.value);
            }
        }
        checkObjectDiff(): boolean {
            return this.stageValue !== this.value;
        }
    }
    (ImageAnimatorReverseModifier as any).identity = Symbol('imageAnimatorReverse');

    class ImageAnimatorStateModifier extends ModifierWithKey<AnimationStatus> {
        constructor(value: AnimationStatus) {
            super(value);
        }
        applyPeer(node: any, reset: boolean): void {
            if (reset) {
                getUINativeModule().imageAnimator.resetState(node);
            }
            else {
                getUINativeModule().imageAnimator.setState(node, this.value);
            }
        }
        checkObjectDiff(): boolean {
            return this.stageValue !== this.value;
        }
    }
    (ImageAnimatorStateModifier as any).identity = Symbol('imageAnimatorState');

    class ImageAnimatorFixedSizeModifier extends ModifierWithKey<boolean> {
        constructor(value: boolean) {
            super(value);
        }
        applyPeer(node: any, reset: boolean): void {
            if (reset) {
                getUINativeModule().imageAnimator.resetFixedSize(node);
            }
            else {
                getUINativeModule().imageAnimator.setFixedSize(node, this.value);
            }
        }
        checkObjectDiff(): boolean {
            return this.stageValue !== this.value;
        }
    }
    (ImageAnimatorFixedSizeModifier as any).identity = Symbol('imageAnimatorFixedSize');

    class ImageAnimatorFillModeModifier extends ModifierWithKey<FillMode> {
        constructor(value: FillMode) {
            super(value);
        }
        applyPeer(node: any, reset: boolean): void {
            if (reset) {
                getUINativeModule().imageAnimator.resetFillMode(node);
            }
            else {
                getUINativeModule().imageAnimator.setFillMode(node, this.value);
            }
        }
        checkObjectDiff(): boolean {
            return this.stageValue !== this.value;
        }
    }
    (ImageAnimatorFillModeModifier as any).identity = Symbol('imageAnimatorFillMode');

    class ImageAnimatorIterationsModifier extends ModifierWithKey<number> {
        constructor(value: number) {
            super(value);
        }
        applyPeer(node: any, reset: boolean): void {
            if (reset) {
                getUINativeModule().imageAnimator.resetIterations(node);
            }
            else {
                getUINativeModule().imageAnimator.setIterations(node, this.value);
            }
        }
        checkObjectDiff(): boolean {
            return this.stageValue !== this.value;
        }
    }
    (ImageAnimatorIterationsModifier as any).identity = Symbol('imageAnimatorIterations');

    class ImageAnimatorOnStartModifier extends ModifierWithKey<OnStart> {
        constructor(value: OnStart) {
            super(value);
        }
        applyPeer(node: any, reset: boolean): void {
            if (reset) {
                getUINativeModule().imageAnimator.resetImageAnimatorOnStart(node);
            } else {
                getUINativeModule().imageAnimator.setImageAnimatorOnStart(node, this.value);
            }
        }
    }
    (ImageAnimatorOnStartModifier as any).identity = Symbol('imageAnimatorOnStart');

    class ImageAnimatorOnPauseModifier extends ModifierWithKey<OnPause> {
        constructor(value: OnPause) {
            super(value);
        }
        applyPeer(node: any, reset: boolean): void {
            if (reset) {
                getUINativeModule().imageAnimator.resetImageAnimatorOnPause(node);
            } else {
                getUINativeModule().imageAnimator.setImageAnimatorOnPause(node, this.value);
            }
        }
    }
    (ImageAnimatorOnPauseModifier as any).identity = Symbol('imageAnimatorOnPause');

    class ImageAnimatorOnRepeatModifier extends ModifierWithKey<OnRepeat> {
        constructor(value: OnRepeat) {
            super(value);
        }
        applyPeer(node: any, reset: boolean): void {
            if (reset) {
                getUINativeModule().imageAnimator.resetImageAnimatorOnRepeat(node);
            } else {
                getUINativeModule().imageAnimator.setImageAnimatorOnRepeat(node, this.value);
            }
        }
    }
    (ImageAnimatorOnRepeatModifier as any).identity = Symbol('imageAnimatorOnRepeat');

    class ImageAnimatorOnCancelModifier extends ModifierWithKey<OnCancel> {
        constructor(value: OnCancel) {
            super(value);
        }
        applyPeer(node: any, reset: boolean): void {
            if (reset) {
                getUINativeModule().imageAnimator.resetImageAnimatorOnCancel(node);
            } else {
                getUINativeModule().imageAnimator.setImageAnimatorOnCancel(node, this.value);
            }
        }
    }
    (ImageAnimatorOnCancelModifier as any).identity = Symbol('imageAnimatorOnCancel');

    class ImageAnimatorOnFinishModifier extends ModifierWithKey<OnFinish> {
        constructor(value: OnFinish) {
            super(value);
        }
        applyPeer(node: any, reset: boolean): void {
            if (reset) {
                getUINativeModule().imageAnimator.resetImageAnimatorOnFinish(node);
            } else {
                getUINativeModule().imageAnimator.setImageAnimatorOnFinish(node, this.value);
            }
        }
    }
    (ImageAnimatorOnFinishModifier as any).identity = Symbol('imageAnimatorOnFinish');

    class ImageAnimatorAutoMonitorInvisibleAreaModifier extends ModifierWithKey<boolean> {
        constructor(value: boolean) {
            super(value);
        }
        applyPeer(node: any, reset: boolean): void {
            if (reset) {
                getUINativeModule().imageAnimator.setAutoMonitorInvisibleArea(node, false);
            }
            else {
                getUINativeModule().imageAnimator.setAutoMonitorInvisibleArea(node, this.value);
            }
        }
        checkObjectDiff(): boolean {
            return this.stageValue !== this.value;
        }
    }
    (ImageAnimatorAutoMonitorInvisibleAreaModifier as any).identity = Symbol('autoMonitorInvisibleArea');

    loadComponent.componentObj = {'component' : ArkImageAnimatorComponent };
  }
  return loadComponent.componentObj;
}

class JSImageAnimator extends JSViewAbstract {
    static create(): void {
        getUINativeModule().imageAnimator.create();
    }
    static images(value: any): void {
        getUINativeModule().imageAnimator.setJSImages(true, value);
    }
    static state(value: any): void {
        getUINativeModule().imageAnimator.setState(true, value);
    }
    static duration(value: any): void {
        getUINativeModule().imageAnimator.setDuration(true, value);
    }
    static reverse(value: any): void {
        getUINativeModule().imageAnimator.setReverse(true, value);
    }
    static fixedSize(value: any): void {
        getUINativeModule().imageAnimator.setFixedSize(true, value);
    }
    static preDecode(value: any): void {} //This interface has been deprecated.
    static fillMode(value: any): void {
        getUINativeModule().imageAnimator.setFillMode(true, value);
    }
    static iterations(value: any): void {
        getUINativeModule().imageAnimator.setIterations(true, value);
    }
    static monitorInvisibleArea(value: any): void {
        getUINativeModule().imageAnimator.setAutoMonitorInvisibleArea(true, value);
    }
    static onStart(value: any): void {
        getUINativeModule().imageAnimator.setImageAnimatorOnStart(true, value);
    }
    static onPause(value: any): void {
        getUINativeModule().imageAnimator.setImageAnimatorOnPause(true, value);
    }
    static onRepeat(value: any): void {
        getUINativeModule().imageAnimator.setImageAnimatorOnRepeat(true, value);
    }
    static onCancel(value: any): void {
        getUINativeModule().imageAnimator.setImageAnimatorOnCancel(true, value);
    }
    static onFinish(value: any): void {
        getUINativeModule().imageAnimator.setImageAnimatorOnFinish(true, value);
    }
    static attributeModifier(modifier: any): void {
        attributeModifierFunc.call(this, modifier, (nativePtr: any) => {
            return createComponent(nativePtr);
        }, (nativePtr: any, classType: any, modifierJS: any) => {
            return new modifierJS.ImageAnimatorModifier(nativePtr, classType);
        });
    }
    static onAttach(value: any): void {
        __Common__.onAttach(value);
    }
    static onAppear(value: any): void {
        __Common__.onAppear(value);
    }
    static onDetach(value: any): void {
        __Common__.onDetach(value);
    }
    static onDisAppear(value: any): void {
        __Common__.onDisAppear(value);
    }
    static onTouch(value: any): void {
        __Common__.onTouch(value);
    }
}

function createComponent(nativePtr: any, classType: any): any {
    loadComponent();
    if (loadComponent.componentObj !== undefined) {
        return new loadComponent.componentObj.component(nativePtr, classType);
    }
    return undefined;
}

function exportComponent(): void {
    globalThis.ArkImageAnimatorComponent = (loadComponent as any).componentObj?.component;
}

function exportView(): void {
    globalThis.ImageAnimator = JSImageAnimator;
}

export default { loadComponent, createComponent, exportComponent, exportView };
