/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import nativeEngine from 'libentry.so';

import { A2UIMessage, A2UIMessageType } from './A2UIMessage';
import { Catalog } from './Catalog';
import { RenderIdGenerator } from './RenderIdGenerator';
import { FunctionBridge } from '../functions/FunctionBridge';

import { NodeContent } from '@kit.ArkUI';

export declare type ActionReceiver = (action: string) => void;
export declare type ErrorCallback = (code: SurfaceErrorType, errorMsg: string) => void;
export declare type SurfaceEventCallback = (eventType: SurfaceEventType, controller: SurfaceController) => void;

export enum SurfaceErrorType {
    NO_ERROR = 0,
    ERROR_NO_SURFACE_MATCHED = 1
}

export enum SurfaceEventType {
    UNKNOWN = -1,
    SURFACE_CREATED = 0,
    SURFACE_COMPONENTS_UPDATED = 1,
    SURFACE_DATA_MODEL_UPDATED = 2,
    SURFACE_DELETED = 3
}

export class SurfaceController {
    private catalog: Catalog;
    private surfaceBelongsTo?: string;
    // used to notify the caller about the user action to send
    private onAction?: ActionReceiver;
    // used to notify the caller about the handling error
    private onError?: ErrorCallback;
    // used to notify the caller about the message handling result
    private onSurfaceEvent: SurfaceEventCallback;

    private currentRootSlot?: NodeContent;

    // Unique render ID for this SurfaceController instance
    private readonly renderId: number;

    // 构造函数，指定可以使用的能力集，以及是否开启 schema 校验
    constructor(catalog: Catalog, eventCallback: SurfaceEventCallback, checkSchema: boolean = true) {
        this.catalog = catalog;
        this.onSurfaceEvent = eventCallback;

        // Generate unique render ID
        this.renderId = RenderIdGenerator.getInstance().generateId();
        console.log(`SurfaceController: Constructor - Generated renderId=${this.renderId}`);

        // Initialize RenderSlot in C++ layer
        this.initRenderSlot();
        FunctionBridge.install();
        FunctionBridge.registerCatalog(catalog);
    }

    /**
     * Initialize RenderSlot in C++ layer
     */
    private initRenderSlot(): void {
        console.log(`SurfaceController: initRenderSlot - renderId=${this.renderId}`);
        nativeEngine.initRenderSlot(this.renderId);
    }

    // A2UI 协议消息接收函数
    public onReceive(dsl: string): void  {
        // TODO: check if the dsl string is valid (not empty and not too long)
        let a2uiMessage: A2UIMessage | null = A2UIMessage.fromDSL(dsl);
        if (a2uiMessage === null) {
            console.error('[SurfaceManager] dsl message parse failed:', dsl);
            // notify error
            this.onError?.(SurfaceErrorType.ERROR_NO_SURFACE_MATCHED, 'dsl message parse failed');
            return;
        }
        console.log("SurfaceController processMessage: ", dsl);
        // Pass renderId instead of currentRootSlot to decouple DSL parsing from UI binding
        nativeEngine.processMessage(this.renderId, a2uiMessage, this.catalog);
        // if success, notify host
        this.notifyHandlingResult(a2uiMessage.type);
        this.surfaceBelongsTo = a2uiMessage.surfaceId;
        // TODO: if failed, need to notify and do something

        // TODO: need to implement the logic before the
    }

    public registerActionReceiver(onAction: ActionReceiver): void {
        this.onAction = onAction;
    }

    public registerErrorCallback(onError: ErrorCallback): void {
        this.onError = onError;
    }

    public bindToRender(rootSlot: NodeContent): void {
        this.currentRootSlot = rootSlot;
        console.log(`SurfaceController bindToRender - renderId=${this.renderId}`);
        // Bind the latest surface to the root slot through renderId
        nativeEngine.bindSurfaceToRender(this.renderId, rootSlot);
        if (this.surfaceBelongsTo !== undefined) {
            // surfaceId presents, it means current controller already received
            // the a2ui message before the binding
            // The binding will be handled by bindSurfaceToRender in C++ layer
        }
    }

    /**
     * Go back to the previous surface
     * Removes the current (latest) surface and displays the previous one
     */
    public back(): void {
        console.log(`SurfaceController back - renderId=${this.renderId}`);
        nativeEngine.backSurface(this.renderId);
    }

    /**
     * Get the current latest surface ID
     * @return The latest surface ID, or empty string if no surface exists
     */
    public getLatestSurfaceId(): string {
        console.log(`SurfaceController getLatestSurfaceId - renderId=${this.renderId}`);
        return nativeEngine.getLatestSurfaceId(this.renderId);
    }

    private notifyHandlingResult(messageType: A2UIMessageType): void {
        if (this.onSurfaceEvent === undefined) {
            return;
        }

        switch (messageType) {
            case A2UIMessageType.CREATE_SURFACE:
                this.onSurfaceEvent?.(SurfaceEventType.SURFACE_CREATED, this);
                return;
            case A2UIMessageType.UPDATE_COMPONENTS:
                this.onSurfaceEvent?.(SurfaceEventType.SURFACE_COMPONENTS_UPDATED, this);
                return;
            case A2UIMessageType.UPDATE_DATA_MODEL:
                this.onSurfaceEvent?.(SurfaceEventType.SURFACE_DATA_MODEL_UPDATED, this);
                return;
            case A2UIMessageType.DELETE_SURFACE:
                this.onSurfaceEvent?.(SurfaceEventType.SURFACE_DELETED, this);
                return;
            default:
                return;
        }
    }
}
