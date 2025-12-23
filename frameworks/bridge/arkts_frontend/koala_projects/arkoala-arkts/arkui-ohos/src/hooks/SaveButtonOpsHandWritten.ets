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

import { SerializerBase, runtimeType, RuntimeType, pointer } from '@koalaui/interop';
import { ArkUIGeneratedNativeModule } from '#components';
import { ModifierKeyStateGetter, InteractionHand, SourceType, SourceTool, ArkSaveButtonComponent, ResourceStr, ArkSaveButtonPeer, SaveButtonCallback, ClickEvent, SaveButtonOnClickResult, EventTarget, Area, Position, Length } from '#generated';
import { int32, int64 } from '@koalaui/common';
import { BusinessError } from '#external';
import { ArkUIAniModule } from 'arkui.ani';

class PositionImpl implements Position {
    public x?: Length;
    public y?: Length;
    constructor() { };
}

class AreaImpl implements Area {
    public width: Length = 0;
    public height: Length = 0;
    public position: Position = {};
    public globalPosition: Position = {};
    constructor() { };
}

class EventTargetImpl implements EventTarget {
    public area: Area = new AreaImpl();
    public id?: string;
    constructor() { };
}

class ClickEventImpl implements ClickEvent {
    public displayX: double;
    public displayY: double;
    public windowX: double;
    public windowY: double;
    public x: double;
    public y: double;
    public hand?: InteractionHand;
    public globalDisplayX?: double | undefined;
    public globalDisplayY?: double | undefined;
    public preventDefault() { };
    public target: EventTarget = new EventTargetImpl();
    public timestamp: int64;
    public source: SourceType = SourceType.UNKNOWN;
    public axisHorizontal?: double;
    public axisVertical?: double;
    public pressure: double;
    public tiltX: double;
    public tiltY: double;
    public rollAngle?: double;
    public sourceTool: SourceTool = SourceTool.UNKNOWN;
    public getModifierKeyState?: ModifierKeyStateGetter;
    public deviceId?: int32;
    public targetDisplayId?: int32;
    constructor() { };
}

export class SaveButtonOpsHandWritten {
    static hookSaveButtonOnClickImpl(
        receiver: ArkSaveButtonComponent | ArkSaveButtonPeer, value: SaveButtonCallback | undefined): void {
        let peerPtr: pointer;
        if (receiver instanceof ArkSaveButtonComponent) {
            peerPtr = receiver.getPeer().peer.ptr;
        } else if (receiver instanceof ArkSaveButtonPeer) {
            peerPtr = receiver.peer.ptr;
        }
        if (peerPtr === undefined) {
            return;
        }
        ArkUIAniModule._SaveButton_SetOnClickCallback(peerPtr, value);
    }
}