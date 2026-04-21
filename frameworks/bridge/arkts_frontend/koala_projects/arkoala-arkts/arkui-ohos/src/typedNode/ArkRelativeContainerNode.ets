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

import { InteropNativeModule, runtimeType, RuntimeType } from '@koalaui/interop';
import { ArkBaseNode } from './ArkBaseNode';
import { RelativeContainerAttribute, ArkRelativeContainerPeer, GuideLineStyle, BarrierStyle,
    LocalizedBarrierStyle } from '../framework';

/** @memo:stable */
export class ArkRelativeContainerNode extends ArkBaseNode implements RelativeContainerAttribute {

    constructParam(...param: Object[]): this {
        if (param.length > 0) {
            throw new Error('more than 0 parameters');
        }
        this.getPeer()?.setRelativeContainerOptionsAttribute();
        return this;
    }

    getPeer(): ArkRelativeContainerPeer {
        return this.peer as ArkRelativeContainerPeer;
    }

    initialize(): this {
        this.getPeer()?.setRelativeContainerOptionsAttribute();
        return this;
    }

    guideLine(value: Array<GuideLineStyle> | undefined): this {
        const value_casted = value as (Array<GuideLineStyle> | undefined);
        this.getPeer()?.setGuideLineAttribute(value_casted);
        return this;
    }

    barrier(value: Array<BarrierStyle> | undefined): this {
        const value_type = runtimeType(value);
        if ((RuntimeType.OBJECT == value_type && (value instanceof Array)) || (RuntimeType.UNDEFINED == value_type)) {
            const value_casted = value as (Array<BarrierStyle> | undefined);
            this.getPeer()?.setBarrierAttribute(value_casted);
            return this;
        }
        throw new Error("Can not select appropriate overload");
    }
}