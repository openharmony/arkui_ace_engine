/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { FrameNode, FrameNodeInternal } from "./generated/ArkFrameNodeMaterialized"
import { ArkUIGeneratedNativeModule, Inspector, ComponentObserver } from "#components"
import { int32 } from "@koalaui/common"
import { nullptr, KNativePointer } from "@koalaui/interop"
import { _animateTo } from "./handwritten"
import { AnimateParam } from './generated'

interface FrameRaterRangeOptions {
    min: number
    max: number
    expected: number
}

class DynamicSyncScene {
    frameRateRange_: FrameRaterRangeOptions
    nodePtr_: KNativePointer
    type_: number = 0

    constructor(nodePtr: KNativePointer, frameRateRange: FrameRaterRangeOptions) {
        this.nodePtr_ = nodePtr;
        this.frameRateRange_ = frameRateRange;
    }

    getFrameRateRange(): FrameRaterRangeOptions {
        return this.frameRateRange_;
    }
}

export class UIInspector {
    instanceId_: int32 = 100000;
    constructor(instanceId: int32) {
        this.instanceId_ = instanceId;
    }
    public createComponentObserver(id: string): ComponentObserver {
        ArkUIGeneratedNativeModule._SystemOps_syncInstanceId(this.instanceId_);
        let componentObserver = Inspector.createComponentObserver(id);
        ArkUIGeneratedNativeModule._SystemOps_restoreInstanceId();
        return componentObserver;
    }
}

export class UIContext {
    instanceId_: int32 = 10001;
    constructor(instanceId: int32) {
        this.instanceId_ = instanceId;
    }
    public getFrameNodeById(id: string): FrameNode | null {
        console.log(`TODO SHOPPING: @ohos.arkui.UIContext getFrameNodeById`);
        const id_casted = id as (string);
        ArkUIGeneratedNativeModule._SystemOps_syncInstanceId(this.instanceId_);
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getFrameNodeByKey(id_casted);
        if (retval != nullptr) {
            const obj : FrameNode = FrameNodeInternal.fromPtr(retval);
            ArkUIGeneratedNativeModule._SystemOps_restoreInstanceId();
            return obj;
        }
        ArkUIGeneratedNativeModule._SystemOps_restoreInstanceId();
        return null;
    }
    public getUIInspector(): UIInspector {
        let uiInspector = new UIInspector(this.instanceId_);
        return uiInspector;
    }

    public animateTo(param: AnimateParam, event: (() => void)): void {
        ArkUIGeneratedNativeModule._SystemOps_syncInstanceId(this.instanceId_);
        _animateTo(param, event);
        ArkUIGeneratedNativeModule._SystemOps_restoreInstanceId();
    }
}
export abstract class FrameCallback {
    abstract onFrame(frameTimeInNano: number): void;
    abstract onIdle(timeLeftInNano: number): void;
}
export class UIObserver {
}

export type CustomBuilderWithId = (id: number) => void;

export interface TargetInfo {
    id: string | number;
    componentId?: number;
}

export interface OverlayManagerOptions {
    renderRootOverlay?: boolean;
}