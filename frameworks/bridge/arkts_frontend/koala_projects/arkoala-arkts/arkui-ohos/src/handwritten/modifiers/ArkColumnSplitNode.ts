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
import { ColumnSplitAttribute, ArkColumnSplitPeer, ColumnSplitDividerStyle } from '../../component';
import { ArkBaseNode } from './ArkBaseNode';

export class ArkColumnSplitNode extends ArkBaseNode implements ColumnSplitAttribute {

    constructParam(...param: Object[]): this {
        InteropNativeModule._NativeLog('columnsplit constructParam enter');
        return this;
    }

    getPeer(): ArkColumnSplitPeer {
        return this.peer as ArkColumnSplitPeer;
    }

    resizeable(value: boolean | undefined): this {
        return this;
    }

    divider(value: ColumnSplitDividerStyle | undefined): this {
        return this;
    }
}