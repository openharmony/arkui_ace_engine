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
import { RowAttribute, ArkRowPeer, VerticalAlign, FlexAlign, PointLightStyle } from '../../component';

export class ArkRowNode extends ArkBaseNode implements RowAttribute {

    constructParam(...param: Object[]): this {
        InteropNativeModule._NativeLog('row constructParam enter');
        return this;
    }

    getPeer(): ArkRowPeer {
        return this.peer as ArkRowPeer;
    }

    alignItems(value: VerticalAlign | undefined): this {
        return this;
    }

    justifyContent(value: FlexAlign | undefined): this {
        return this;
    }

    pointLight(value: PointLightStyle | undefined): this {
        return this;
    }

    reverse(value: boolean | undefined): this {
        return this;
    }
}