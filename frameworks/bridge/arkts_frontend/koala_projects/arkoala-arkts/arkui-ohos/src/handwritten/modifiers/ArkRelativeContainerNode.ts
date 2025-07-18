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
import { RelativeContainerAttribute, ArkRelativeContainerPeer, GuideLineStyle, BarrierStyle, LocalizedBarrierStyle } from '../../component';

/** @memo:stable */
export class ArkRelativeContainerNode extends ArkBaseNode implements RelativeContainerAttribute {

    constructParam(...param: Object[]): this {
        InteropNativeModule._NativeLog('flex constructParam enter');
        return this;
    }

    getPeer(): ArkRelativeContainerPeer {
        return this.peer as ArkRelativeContainerPeer;
    }

    guideLine(value: Array<GuideLineStyle> | undefined): this {
        return this;
    }

    barrier(value: Array<BarrierStyle> | undefined | Array<LocalizedBarrierStyle> | undefined): this {
        return this;
    }
}