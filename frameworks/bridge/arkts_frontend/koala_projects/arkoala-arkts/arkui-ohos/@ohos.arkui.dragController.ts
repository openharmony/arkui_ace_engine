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

import { DragEvent, DragPreviewOptions, ICurve, CustomBuilder, Callback, DragItemInfo } from 'arkui/component/common';
import { TouchPoint, ResourceColor } from 'arkui/component/units';
import { Curve } from 'arkui/component/enums';
import { UnifiedData, PixelMap } from "#external";
import { ArkUIAniModule } from "arkui.ani"
import { KPointer } from '@koalaui/interop';
export namespace dragController {

    export enum DragStatus {
        STARTED = 0,
        ENDED = 1,
    }

    export enum DragBehavior {
        COPY = 0,
        MOVE = 1,
    }

    export enum DragResult {
        DRAG_SUCCESSFUL = 0,
        DRAG_FAILED = 1,
        DRAG_CANCELED = 2,
        DROP_ENABLED = 3,
        DROP_DISABLED = 4,
    }

    export enum DragStartRequestStatus {
        WAITING = 0,
        READY = 1,
    }
    
    export interface DragInfo {
        pointerId: number;
        data?: UnifiedData;
        extraParams?: string;
        touchPoint?: TouchPoint;
        previewOptions?: DragPreviewOptions;
    }

    export interface DragEventParam {
        event: DragEvent;
        extraParams: string;
    }

    export interface DragAndDropInfo {
        status: DragStatus;
        event: DragEvent;
        extraParams: string;
    }

    class DragItemInfoInner implements DragItemInfo {
        pixelMap?: PixelMap;
        builder?: CustomBuilder;
        extraInfo?: string;
    }
    
    export class DragAndDropInfoInner implements DragAndDropInfo {
        status: DragStatus;
        event: DragEvent;
        extraParams: string;
        constructor(status: DragStatus, event: DragEvent, extraParmas: string) {
            this.status = status
            this.event = event
            this.extraParams = extraParmas
        }
    }

    export class DragEventParamInner implements DragEventParam {
        event: DragEvent;
        extraParams: string;
        constructor(event: DragEvent, extraParams: string) {
            this.event = event
            this.extraParams = extraParams
        }
    }

    export interface DragEvent {
        dragBehavior: DragBehavior;
        setResult(dragResult: DragResult): void;
        getResult(): DragResult;
    }

    export class DragEventInner implements DragEvent {
        dragEvent:KPointer;
        constructor(result:KPointer) {
            this.dragEvent = result;
        }
        dragResult: DragResult
        public getResult(): DragResult {
            return this.dragResult;
        }
        public setResult(value: DragResult) {
            this.dragResult = value;
        }

        // set and get dragBehavior
        private setDragBehavior(value: DragBehavior){
            this.dragBehavior = value;
        };
        private getDragBehavior() : DragBehavior {
            return this.dragBehavior;
        }
        set dragBehavior(value: DragBehavior) {
            this.setDragBehavior(value);
        }
        get dragBehavior() : DragBehavior {
            return this.getDragBehavior();
        }
    }

    export interface DragAction {
        startDrag(): Promise<void>;
        on(type: string, callback: Callback<DragAndDropInfo>): void;
        off(type: string, callback?: Callback<DragAndDropInfo>): void;
    }

    export class DragActionInner implements DragAction {
        dragAction:KPointer;
        constructor(result:KPointer) {
            this.dragAction = result;
        }
        public startDrag(): Promise<void> {
            let promise = ArkUIAniModule._DragController_startDrag(this.dragAction);
            return promise;
        }
        public on(type: string, callback: Callback<DragAndDropInfo>) {
            ArkUIAniModule._DragController_on(type, callback, this.dragAction);
        }
        public off(type: string, callback?: Callback<DragAndDropInfo>) {
            ArkUIAniModule._DragController_off(type, callback, this.dragAction);
        }
    }

    export interface AnimationOptions {
        duration?: number;
        curve?: Curve | ICurve;
    }

    export interface DragPreview {
        setForegroundColor(color: ResourceColor): void;
        animate(options: AnimationOptions, handler: () =>void): void;
    }
}