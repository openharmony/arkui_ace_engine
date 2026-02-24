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
import { int64, int32 } from '@koalaui/common'
import { TouchPoint, ResourceColor } from 'arkui/framework'
import { Curve } from 'arkui/framework'
import { UnifiedData, PixelMap } from "#external";
import { ArkUIAniModule } from "arkui.ani"
import { KPointer } from '@koalaui/interop';
import { DragUtils } from '#generated'
import { default as unifiedDataChannel } from "@ohos.data.unifiedDataChannel"
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
            if (this.className === 'DragAction') {
                ArkUIAniModule._DragController_cleanDragAction(this.ptr);
            } else if (this.className === 'DragPreview') {
                ArkUIAniModule._DragController_cleanDragPreview(this.ptr);
            } else if (this.className == "SpringLoadingContext") {
                ArkUIAniModule._DragController_cleanSpringLoadingContext(this.ptr);
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
            let colorValue : int64 = DragUtils.GetForegroundColorValue(color);
            ArkUIAniModule._DragController_setForegroundColor(colorValue, this.dragPreview);
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
        dataLoadParams?: unifiedDataChannel.DataLoadParams;
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
        startDrag(): Promise<void> | null;
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
        public startDrag(): Promise<void> | null {
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

    export enum DragSpringLoadingState {
        BEGIN = 0,
        UPDATE = 1,
        END = 2,
        CANCEL = 3
    }

    export interface DragSpringLoadingConfiguration {
        stillTimeLimit?: int32;
        updateInterval?: int32;
        updateNotifyCount?: int32;
        updateToFinishInterval?: int32;
    }

    export class DragSpringLoadingConfigurationInner implements DragSpringLoadingConfiguration {
        _stillTimeLimit?: int32;
        _updateInterval?: int32;
        _updateNotifyCount?: int32;
        _updateToFinishInterval?: int32;
        constructor(stillTimeLimit: int32, updateInterval: int32, updateNotifyCount: int32, updateToFinishInterval: int32) {
            this._stillTimeLimit = stillTimeLimit;
            this._updateInterval = updateInterval;
            this._updateNotifyCount = updateNotifyCount;
            this._updateToFinishInterval = updateToFinishInterval;
        }
        set stillTimeLimit(value: int32 | undefined) {
            this._stillTimeLimit = value;
        }
        get stillTimeLimit() : int32 | undefined {
            return this._stillTimeLimit;
        }
        set updateInterval(value: int32 | undefined) {
            this._updateInterval = value;
        }
        get updateInterval() : int32 | undefined {
            return this._updateInterval;
        }
        set updateNotifyCount(value: int32 | undefined) {
            this._updateNotifyCount = value;
        }
        get updateNotifyCount() : int32 | undefined {
            return this._updateNotifyCount;
        }
        set updateToFinishInterval(value: int32 | undefined) {
            this._updateToFinishInterval = value;
        }
        get updateToFinishInterval() : int32 | undefined {
            return this._updateToFinishInterval;
        }
    }

    export interface SpringLoadingDragInfos {
        dataSummary?: unifiedDataChannel.Summary;
        extraInfos?: string;
    }

    export class SpringLoadingDragInfosInner implements SpringLoadingDragInfos {
        _dataSummary?: unifiedDataChannel.Summary;
        _extraInfos?: string;
        constructor(stillTimeLimit?: unifiedDataChannel.Summary, extraInfos?: string) {
            this._dataSummary = stillTimeLimit;
            this._extraInfos = extraInfos;
        }
        set dataSummary(value: unifiedDataChannel.Summary | undefined) {
            this._dataSummary = value;
        }
        get dataSummary() : unifiedDataChannel.Summary | undefined {
            return this._dataSummary;
        }
        set extraInfos(value: string | undefined) {
            this._extraInfos = value;
        }
        get extraInfos() : string | undefined {
            return this._extraInfos;
        }
    }
    
    export class SpringLoadingContext {
        state: DragSpringLoadingState;
        currentNotifySequence: int32;
        dragInfos?: SpringLoadingDragInfos;
        currentConfig?: DragSpringLoadingConfiguration;
        peer: KPointer;
        private cleaner: Cleaner | null = null;
        constructor(result:KPointer) {
            this.peer = result;
            this.registerCleaner(this.peer)
            this.state = ArkUIAniModule._DragSpringLoadingContext_get_state(this.peer)
            this.currentNotifySequence = ArkUIAniModule._DragSpringLoadingContext_get_currentNotifySequence(this.peer)
            this.dragInfos = ArkUIAniModule._DragSpringLoadingContext_get_dragInfos(this.peer)
            this.currentConfig = ArkUIAniModule._DragSpringLoadingContext_get_currentConfig(this.peer)
        }
        registerCleaner(ptr: KPointer) {
            this.cleaner = new Cleaner("SpringLoadingContext", ptr);
            destroyRegister.register(this, this.cleaner!, unregisterToken);
        }
        unregisterCleaner() {
            destroyRegister.unregister(unregisterToken);
        }
        public abort():void {
            ArkUIAniModule._DragSpringLoadingContext_abort(this.peer)
        }
        public updateConfiguration(config: DragSpringLoadingConfiguration) {
            ArkUIAniModule._DragSpringLoadingContext_updateConfiguration(this.peer, config)
        }
    }
}
export default dragController;