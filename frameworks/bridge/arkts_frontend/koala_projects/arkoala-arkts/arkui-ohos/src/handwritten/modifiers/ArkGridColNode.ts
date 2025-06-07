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
import { GridColAttribute, ArkGridColPeer, GridColColumnOption } from '../../component';

export class ArkGridColNode extends ArkBaseNode implements GridColAttribute {

    constructParam(...param: Object[]): this {
        InteropNativeModule._NativeLog('gridcol constructParam enter');
        return this;
    }

    getPeer(): ArkGridColPeer {
        return this.peer as ArkGridColPeer;
    }

    span(value: number | GridColColumnOption | undefined): this {
        return this;
    }

    gridColOffset(value: number | GridColColumnOption | undefined): this {
        return this;
    }

    order(value: number | GridColColumnOption | undefined): this {
        return this;
    }
}