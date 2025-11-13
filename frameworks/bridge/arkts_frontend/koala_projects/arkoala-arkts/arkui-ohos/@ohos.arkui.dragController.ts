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

import { DragEvent, DragPreviewOptions, ICurve, CustomBuilder, Callback, DragItemInfo } from 'arkui/framework'
import { TouchPoint, ResourceColor } from 'arkui/framework'
import { Curve } from 'arkui/framework'
import { UnifiedData, PixelMap } from "#external";
import { ArkUIAniModule } from "arkui.ani"
import { KPointer } from '@koalaui/interop';
export namespace dragController {

    export enum DragStatus {
        STARTED = 0,
        ENDED = 1,
    }

    export enum DragStartRequestStatus {
        WAITING = 0,
        READY = 1,
    }

    export interface AnimationOptions {
        duration?: int;
        curve?: Curve | ICurve;
    }

    export interface DragPreview {
        setForegroundColor(color: ResourceColor): void;
        animate(options: AnimationOptions, handler: () =>void): void;
    }

    class Cleaner {
        private ptr: KPointer = 0;
        private className: string;
        constructor(className: string, ptr: KPointer) {
            this.ptr = ptr;
            this.className = className;
        }
        public clean(): void {
            if (this.className == "DragAction") {
                ArkUIAniModule._DragController_cleanDragAction(this.ptr);
            } else if (this.className == "DragPreview") {
                ArkUIAniModule._DragController_cleanDragPreview(this.ptr);
            }
        }
    }

    export function callback(cleaner: Cleaner): void {
        cleaner.clean()
    }

    let destroyRegister = new FinalizationRegistry<Cleaner>(callback)
    let unregisterToken = new object()

    class DragPreviewInner implements DragPreview {
        dragPreview:KPointer = 0;
        private cleaner: Cleaner | null = null;
        constructor(result:KPointer) {
            this.dragPreview = result;
            this.registerCleaner(this.dragPreview)
        }
        public setForegroundColor(color: ResourceColor) {
            ArkUIAniModule._DragController_setForegroundColor(color, this.dragPreview);
        }
        public animate(options: AnimationOptions, handler: () =>void) {
            ArkUIAniModule._DragController_animate(options, handler, this.dragPreview);
        }

        registerCleaner(ptr: KPointer): void {
            this.cleaner = new Cleaner("DragPreview", ptr);
            destroyRegister.register(this, this.cleaner!, unregisterToken);
        }
        unregisterCleaner(): void {
            destroyRegister.unregister(unregisterToken);
        }
    }
    
    export interface DragInfo {
        pointerId: int;
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
    
    export class DragAndDropInfoInner implements DragAndDropInfo {
        status: DragStatus;
        _event: DragEvent;
        extraParams: string;
        constructor(status: DragStatus, event: DragEvent, extraParmas: string) {
            this.status = status
            this._event = event
            this.extraParams = extraParmas
        }
        set event(value: DragEvent) {
            this._event = value;
        }
        get event() : DragEvent {
            return this._event;
        }
    }

    export class DragEventParamInner implements DragEventParam {
        _event: DragEvent;
        extraParams: string;
        constructor(event: DragEvent, extraParams: string) {
            this._event = event
            this.extraParams = extraParams
        }
        set event(value: DragEvent) {
            this._event = value;
        }
        get event() : DragEvent {
            return this._event;
        }
    }

    export interface DragAction {
        startDrag(): Promise<void>;
        onStatusChange(callback: Callback<DragAndDropInfo>): void;
        offStatusChange(callback?: Callback<DragAndDropInfo>): void;
    }

    export class DragActionInner implements DragAction {
        dragAction:KPointer;
        private cleaner: Cleaner | null = null;
        constructor(result:KPointer) {
            this.dragAction = result;
            this.registerCleaner(this.dragAction)
        }
        public startDrag(): Promise<void> {
            let promise = ArkUIAniModule._DragController_startDrag(this.dragAction);
            return promise;
        }
        public onStatusChange(callback: Callback<DragAndDropInfo>) {
            ArkUIAniModule._DragController_on(callback, this.dragAction);
        }
        public offStatusChange(callback?: Callback<DragAndDropInfo>) {
            ArkUIAniModule._DragController_off(callback, this.dragAction);
        }
        registerCleaner(ptr: KPointer): void {
            this.cleaner = new Cleaner("DragAction", ptr);
            destroyRegister.register(this, this.cleaner!, unregisterToken);
        }
        unregisterCleaner(): void {
            destroyRegister.unregister(unregisterToken);
        }
    }
}