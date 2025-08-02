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
import { ColumnAttribute, HorizontalAlign, FlexAlign, PointLightStyle, ArkColumnPeer, ColumnOptions,
    ColumnOptionsV2 } from '../../component';
import { ArkBaseNode } from './ArkBaseNode';

export class ArkColumnNode extends ArkBaseNode implements ColumnAttribute {

    constructParam(...param: Object[]): this {
        if (param.length > 1) {
            throw new Error('more than 1 parameters');
        }
        let options_casted: ColumnOptions | ColumnOptionsV2 | undefined = undefined;
        if (param.length === 1) {
            options_casted = param[0] as (ColumnOptions | ColumnOptionsV2 | undefined);
        }
        this.getPeer()?.setColumnOptions1Attribute(options_casted);
        return this;
    }

    getPeer() : ArkColumnPeer {
        return this.peer as ArkColumnPeer;
    }

    initialize(options?: ColumnOptions | ColumnOptionsV2): this {
        const options_type = runtimeType(options)
        if ((RuntimeType.OBJECT == options_type) || (RuntimeType.UNDEFINED == options_type)) {
            const options_casted = options as (ColumnOptions | ColumnOptionsV2 | undefined);
            this.getPeer()?.setColumnOptions1Attribute(options_casted);
            return this;
        }
        throw new Error("Can not select appropriate overload");
    }

    alignItems(value: HorizontalAlign | undefined): this {
        const value_casted = value as (HorizontalAlign | undefined);
        this.getPeer()?.alignItemsAttribute(value_casted);
        return this;
    }

    justifyContent(value: FlexAlign | undefined): this {
        const value_casted = value as (FlexAlign | undefined);
        this.getPeer()?.justifyContentAttribute(value_casted);
        return this;
    }

    pointLight(value: PointLightStyle | undefined): this {
        const value_casted = value as (PointLightStyle | undefined);
        this.getPeer()?.pointLightAttribute(value_casted);
        return this;
    }

    reverse(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined);
        this.getPeer()?.reverseAttribute(value_casted);
        return this;
    }
}