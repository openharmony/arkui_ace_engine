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

import { AttributeModifier, CommonMethod, CommonShapeMethod, ArkCommonShapeMethodPeer } from 'arkui/component/common';
import { AttributeUpdaterFlag, CommonMethodModifier } from './CommonMethodModifier';
import { ArkPathPeer, PathAttribute } from 'arkui/component/path';
import { CommonShapeMethodModifier } from './CommonShapeMethodModifier';
import { PeerNode } from './PeerNode';

export class PathModifier extends CommonShapeMethodModifier implements PathAttribute, AttributeModifier<PathAttribute> {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    applyNormalAttribute(instance: PathAttribute): void { }
    applyPressedAttribute(instance: PathAttribute): void { }
    applyFocusedAttribute(instance: PathAttribute): void { }
    applyDisabledAttribute(instance: PathAttribute): void { }
    applySelectedAttribute(instance: PathAttribute): void { }
    _commands_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _commands_0_0value?: string | undefined
    applyModifierPatch(peerNode: PeerNode): void {
        super.applyModifierPatch(peerNode)
        const peer = peerNode as ArkPathPeer
        if (this._commands_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._commands_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.commandsAttribute((this._commands_0_0value as string | undefined));
                    this._commands_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._commands_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._commands_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.commandsAttribute(undefined);
                }
            }
        }
    }
    mergeModifier(value: CommonMethodModifier): void {
        super.mergeModifier(value)
        if (!(value instanceof PathModifier)) {
            return;
        }
        const modifier = value as PathModifier
        if (modifier._commands_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._commands_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.commands(modifier._commands_0_0value);
                    break;
                }
                default: {
                    this.commands(undefined);
                }
            }
        }
    }
    commands(value: string | undefined): this {
        if (((this._commands_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._commands_0_0value) !== (value)))
        {
            this._commands_0_flag = AttributeUpdaterFlag.UPDATE
            this._commands_0_0value = value
        }
        else
        {
            this._commands_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
}
