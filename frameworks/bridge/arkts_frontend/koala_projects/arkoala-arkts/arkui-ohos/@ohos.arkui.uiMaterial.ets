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

import { ArkUIAniModule } from 'arkui.ani';
import { ResourceColor } from '/arkui/component/units';
import { ImmersiveHelper, ImmersiveOptionsInner, LightEffectOptionsInner } from "arkui/component/idlize"

namespace uiMaterial {
    export enum MaterialType {
        NONE = 0,
        SEMI_TRANSPARENT = 1,
        IMMERSIVE = 2,
    }
    export interface MaterialOptions {
        type?: MaterialType,
    }
    export enum ImmersiveStyle {
        ULTRA_THIN = 0,
        THIN = 1,
        REGULAR = 2,
        THICK = 3,
        ULTRA_THICK = 4,
    }
    export interface LightEffectOptions {
        color?: ResourceColor,
    }
    export interface ImmersiveOptions {
        style?: ImmersiveStyle,
        materialColor?: ResourceColor,
        colorInvert?: boolean,
        applyShadow?: boolean,
        interactive?: boolean,
        lightEffect?: LightEffectOptions | null,
    }
    class Cleaner {
        private ptr: long = 0;
        constructor(ptr: long) {
            this.ptr = ptr;
        }
        clean(): void {
            if (this.ptr != 0) {
                ArkUIAniModule._UiMaterial_DestroyMaterial(this.ptr);
                this.ptr = 0;
            }
        }
    }
    export function cleanCallback(cleaner: Cleaner): void {
        cleaner.clean()
    }
    let destroyRegister = new FinalizationRegistry<Cleaner>(cleanCallback)
    let unregisterToken = new object()
    export class Material {
        protected materialObj_: long = 0;
        protected cleaner_: Cleaner | undefined = undefined;
        constructor(options?: MaterialOptions) {
            let options_cast = options as MaterialOptions | undefined;
            this.materialObj_ = ArkUIAniModule._UiMaterial_ConstructMaterial(options_cast);
            this.registerCleaner(this.materialObj_);
        }
        registerCleaner(ptr: long): void {
            this.cleaner_ = new Cleaner(ptr)
            destroyRegister.register(this, this.cleaner_!, unregisterToken);
        }
        unregisterCleaner(): void {
            destroyRegister.unregister(unregisterToken);
        }
        getNativeObject(): long {
            return this.materialObj_;
        }
    }
    export class ImmersiveMaterial extends Material {
        constructor(options?: ImmersiveOptions) {
            let val: ImmersiveOptionsInner | undefined = undefined;
            if (options != undefined) {
                let options_cast = options as ImmersiveOptions;
                val = {
                    style: (options_cast.style === undefined) ? undefined : (options_cast.style as ImmersiveStyle).valueOf(),
                    materialColor: options_cast.materialColor,
                    colorInvert: options_cast.colorInvert,
                    applyShadow: options_cast.applyShadow,
                    interactive: options_cast.interactive,
                    lightEffect: ImmersiveMaterial.ConvertLightEffectOptions(options_cast.lightEffect),
                } as ImmersiveOptionsInner;
            }
            this.materialObj_ = ImmersiveHelper.ImmersiveConstruct(val);
            this.registerCleaner(this.materialObj_);
        }
        static ConvertLightEffectOptions(input: LightEffectOptions | null | undefined): LightEffectOptionsInner | null | undefined {
            if (input === undefined) {
                return null;
            }
            if (input === null) {
                return null;
            }
            let val = input as LightEffectOptions;
            return { color: val.color } as LightEffectOptionsInner;
        }
    }
}

export default uiMaterial;