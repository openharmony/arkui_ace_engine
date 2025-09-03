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

import { InteropNativeModule } from '@koalaui/interop';
import { ArkBaseNode } from './ArkBaseNode';
import { StackAttribute, ArkStackPeer, Alignment, PointLightStyle, StackOptions } from '../../component';

export class ArkStackNode extends ArkBaseNode implements StackAttribute {

    constructParam(...param: Object[]): this {
        if (param.length > 1) {
            throw new Error('more than 1 parameters');
        }
        let options_casted: StackOptions | undefined = undefined;
        if (param.length === 1) {
            options_casted = param[0] as (StackOptions | undefined);
        }
        this.getPeer()?.setStackOptionsAttribute(options_casted);
        return this;
    }

    getPeer(): ArkStackPeer {
        return this.peer as ArkStackPeer;
    }

    initialize(options?: StackOptions): this {
        const options_casted = options as (StackOptions | undefined);
        this.getPeer()?.setStackOptionsAttribute(options_casted);
        return this;
    }

    alignContent(value: Alignment | undefined): this {
        const value_casted = value as (Alignment | undefined);
        this.getPeer()?.alignContentAttribute(value_casted);
        return this;
    }

    pointLight(value: PointLightStyle | undefined): this {
        const value_casted = value as (PointLightStyle | undefined);
        this.getPeer()?.pointLightAttribute(value_casted);
        return this;
    }
}
