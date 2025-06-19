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

import { FrameNode, FrameNodeInternal } from "./src/FrameNode"
import { GlobalScope_ohos_font } from "./src/generated/ArkGlobalScopeOhosFontMaterialized"
import { GlobalScope_ohos_measure_utils } from "./src/generated/ArkGlobalScopeOhosMeasureUtilsMaterialized"
import { FontOptions, FontInfo } from "@ohos.font.font"
import { MeasureOptions } from "@ohos.measure"
import { SizeOptions } from "./src/component/units"
import { ArkUIGeneratedNativeModule } from "#components"
import { int32 } from "@koalaui/common"
import { nullptr } from "@koalaui/interop"
import { _animateTo } from "./src/handwritten"
import { AnimateParam } from './src/generated'
import { AnimatorResult , AnimatorOptions, Animator} from "@ohos/animator"

export class Font {
    instanceId_: int32 = 10001;
    constructor(instanceId: int32) {
        this.instanceId_ = instanceId;
    }
    public registerFont(options: FontOptions) : void {
        ArkUIGeneratedNativeModule._SystemOps_syncInstanceId(this.instanceId_);
        GlobalScope_ohos_font.registerFont(options);
        ArkUIGeneratedNativeModule._SystemOps_restoreInstanceId();
    }
    public getSystemFontList() : Array<string> {
        ArkUIGeneratedNativeModule._SystemOps_syncInstanceId(this.instanceId_);
        let arrayResult_ = GlobalScope_ohos_font.getSystemFontList();
        ArkUIGeneratedNativeModule._SystemOps_restoreInstanceId();
        return arrayResult_;
    }
    public getFontByName(fontName : string) : FontInfo {
        ArkUIGeneratedNativeModule._SystemOps_syncInstanceId(this.instanceId_);
        let fontInfo : FontInfo = GlobalScope_ohos_font.getFontByName(fontName);
        ArkUIGeneratedNativeModule._SystemOps_restoreInstanceId();
        return fontInfo;
    }
}

export class MeasureUtils {
    instanceId_: int32 = 10001;
    constructor(instanceId: int32) {
        this.instanceId_ = instanceId;
    }
    public measureText(options: MeasureOptions) : number {
        ArkUIGeneratedNativeModule._SystemOps_syncInstanceId(this.instanceId_);
        let width = GlobalScope_ohos_measure_utils.measureText(options);
        ArkUIGeneratedNativeModule._SystemOps_restoreInstanceId();
        return width;
    }
    public measureTextSize(options: MeasureOptions) : SizeOptions {
        ArkUIGeneratedNativeModule._SystemOps_syncInstanceId(this.instanceId_);
        let sizeOptions = GlobalScope_ohos_measure_utils.measureTextSize(options);
        ArkUIGeneratedNativeModule._SystemOps_restoreInstanceId();
        return sizeOptions;
    }
}

export class UIContext {
    instanceId_: int32 = 10001;
    constructor(instanceId: int32) {
        this.instanceId_ = instanceId;
    }
    public getFont() : Font {
        let font : Font = new Font(this.instanceId_);
        return font;
    }
    public getMeasureUtils() : MeasureUtils {
        let measureUtils : MeasureUtils = new MeasureUtils(this.instanceId_);
        return measureUtils;
    }
    public getFrameNodeById(id: string): FrameNode | null {
        console.log(`TODO SHOPPING: @ohos.arkui.UIContext getFrameNodeById`);
        const id_casted = id as (string);
        ArkUIGeneratedNativeModule._SystemOps_syncInstanceId(this.instanceId_);
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getFrameNodeByKey(id_casted);
        if (retval != nullptr) {
            const obj : FrameNode = FrameNodeInternal.fromPtr(retval);
            ArkUIGeneratedNativeModule._SystemOps_restoreInstanceId();
            return obj;
        }
        ArkUIGeneratedNativeModule._SystemOps_restoreInstanceId();
        return null;
    }

    public animateTo(param: AnimateParam, event: (() => void)): void {
        ArkUIGeneratedNativeModule._SystemOps_syncInstanceId(this.instanceId_);
        _animateTo(param, event);
        ArkUIGeneratedNativeModule._SystemOps_restoreInstanceId();
    }
    public createAnimator(options: AnimatorOptions): AnimatorResult {
        ArkUIGeneratedNativeModule._SystemOps_syncInstanceId(this.instanceId_);
        let animatorRet = Animator.create(options);
        ArkUIGeneratedNativeModule._SystemOps_restoreInstanceId();
        return animatorRet;
    }
}
export abstract class FrameCallback {
    abstract onFrame(frameTimeInNano: number): void;
    abstract onIdle(timeLeftInNano: number): void;
}
export class UIObserver {
}