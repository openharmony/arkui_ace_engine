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

namespace uiMaterial {
    export enum MaterialType {
        NONE = 0,
        SEMI_TRANSPARENT = 1,
    }
    export interface MaterialOptions {
        type?: MaterialType,
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
        private materialObj_: long = 0;
        private cleaner_: Cleaner | undefined = undefined;
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
}

export default uiMaterial;