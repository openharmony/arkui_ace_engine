/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { ExpectedFrameRateRange } from './arkui.component.common'
import { FillMode, PlayMode } from './arkui.component.enums'

export class SimpleAnimatorOptions {

  static { loadLibrary("animator_ani") }

  SimpleAnimatorOptionsResult:long = 0;

  public native constructor(begin: double, end: double);

  public native duration(duration: int): SimpleAnimatorOptions;

  public native easing(curve: string): SimpleAnimatorOptions;

  public native delay(delay: int): SimpleAnimatorOptions;

  public native fill(fillMode: FillMode): SimpleAnimatorOptions;

  public native direction(direction: PlayMode): SimpleAnimatorOptions;

  public native iterations(iterations: int): SimpleAnimatorOptions;
}

interface AnimatorOptions {
    duration: int;
    easing: string;
    delay: int;
    fill: "none" | "forwards" | "backwards" | "both";
    direction: "normal" | "reverse" | "alternate" | "alternate-reverse";
    iterations: int;
    begin: double;
    end: double;
}

export default class Animator {
    static { loadLibrary("animator_ani") }
    static native create(options: AnimatorOptions | SimpleAnimatorOptions): AnimatorResult;
}

export interface AnimatorResult {
    play(): void;
    reverse(): void;
    cancel(): void;
    pause(): void;
    finish(): void;
    update(options: AnimatorOptions): void;
    reset(options: AnimatorOptions | SimpleAnimatorOptions): void;
    onFinish: () => void;
    onCancel: () => void;
    onRepeat: () => void;
    onFrame: (progress: double) => void;
    setExpectedFrameRateRange(rateRange: ExpectedFrameRateRange) : void;
}

class AnimatorResultInner implements AnimatorResult {

    static {
        loadLibrary("animator_ani");
    }

    animatorResult:long = 0;
    constructor(result:long) {
        if(this.animatorResult == 0){
             this.animatorResult = result;
        }
    }
    public native play(): void;
    public native reverse(): void;
    public native cancel(): void;
    public native pause(): void;
    public native finish(): void;
    public native update(options: AnimatorOptions): void;
    public native reset(options: AnimatorOptions | SimpleAnimatorOptions): void;
    public native setExpectedFrameRateRange(rateRange: ExpectedFrameRateRange) : void;

    static animatorTransferStatic(input: Any): Object {
        return AnimatorResultInner.nativeTransferStatic(ESValue.wrap(input));
    }

    private static native nativeTransferStatic(input: ESValue): Object;

    static animatorTransferDynamic(input: Any): Any {
        let animatorRet = input as AnimatorResultInner;
        if (animatorRet) {
            let addr = animatorRet.animatorResult;
            let module = ESValue.load("@ohos.animator");
            let initFunc = module.getProperty("__createTransfer__")
            if (initFunc) {
                let animatorRet = initFunc.invoke(ESObject.wrap(addr));
                return animatorRet;
            } else {
                console.error("AceAnimation:: invoke func not exit")
            }
        }
        return undefined;
    }

    // set and get onFinish
    private native setOnFinish(value: () => void) : void;
    set onFinish(value: () => void) {
        this.setOnFinish(value);
    }
    get onFinish(): () => void {
        return this.onFinish;
    }

    // set and get onCancel
    private native setOnCancel(value: () => void) : void;
    set onCancel(value: () => void) {
        this.setOnCancel(value);
    }
    get onCancel(): () => void {
        return this.onCancel;
    }

    // set and get onRepeat
    private native setOnRepeat(value: () => void) : void;
    set onRepeat(value: () => void) {
        this.setOnRepeat(value);
    }
    get onRepeat(): () => void {
        return this.onRepeat;
    }

    // set and get onFrame
    private native setOnFrame(value: (progress: double) => void) : void;
    set onFrame(value: (progress: double) => void) {
        this.setOnFrame(value);
    }
    get onFrame(): (progress: double) => void {
        return this.onFrame;
    }
}