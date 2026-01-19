/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import photoAccessHelper from '@ohos.file.photoAccessHelper';
import { NodeAttach } from '@koalaui/runtime/memo/node';
import { remember } from '@koalaui/runtime/memo/remember';
import { Finalizable } from '@koalaui/interop/Finalizable';
import { int32 } from '@koalaui/common';
import { ImageAIOptions } from 'arkui.component.imageCommon';
import { ArkCommonMethodPeer, ArkCommonMethodComponent } from 'arkui/component/common';
import { CommonMethod } from 'arkui.component.common';
import { ImageFit } from 'arkui.component.enums';
import { ComponentBase } from 'arkui/ComponentBase';
import { PeerNode } from 'arkui/PeerNode';
import { memo } from '@koalaui/runtime/annotations';

type KPointer = long;

export interface MovingPhotoViewOptions {
    movingPhoto: photoAccessHelper.MovingPhoto

    controller?: MovingPhotoViewController

    imageAIOptions?: ImageAIOptions

    movingPhotoFormat?: PixelMapFormat

    dynamicRangeMode?: DynamicRangeMode

    playWithMask?: boolean
}

export enum DynamicRangeMode {
    HIGH = 0,
    CONSTRAINT = 1,
    STANDARD = 2,
}

export enum PixelMapFormat {
    UNKNOWN = 0,
    RGBA_8888 = 1,
    NV21 = 2,
    RGBA_1010102 = 3,
    YCBCR_P010 = 4,
    YCRCB_P010 = 5,
}

export class MovingPhotoViewController {
    peer?: (Finalizable | undefined) = undefined;

    static getMovingPhotoViewController(): KPointer {
        return MovingPhotoNative.createMovingPhotoController();
    }

    static getFinalizer(): KPointer {
        return MovingPhotoNative.getFinalizer();
    }

    public constructor() {
        const ctorPtr: KPointer = MovingPhotoViewController.getMovingPhotoViewController();
        const finalizerPtr: KPointer = MovingPhotoViewController.getFinalizer();
        this.peer = new Finalizable(ctorPtr, finalizerPtr);
    }
    
    public startPlayback(): void {
        MovingPhotoNative.startPlayback(this.peer!.ptr);
    }

    public stopPlayback(): void {
        MovingPhotoNative.stopPlayback(this.peer!.ptr);
    }

    public refreshMovingPhoto(): void {
        MovingPhotoNative.refreshMovingPhoto(this.peer!.ptr);
    }

    public pausePlayback(): void {
        MovingPhotoNative.pausePlayback(this.peer!.ptr);
    }

    public reset(): void {
        MovingPhotoNative.reset(this.peer!.ptr);
    }

    public restart(): void {
        MovingPhotoNative.restart(this.peer!.ptr);
    }

    public enableTransition(enabled: boolean): void {
        MovingPhotoNative.enableTransition(this.peer!.ptr, enabled);
    }

    public setPlaybackPeriod(startTime: double, endTime: double): void {
        MovingPhotoNative.setPlaybackPeriod(this.peer!.ptr, startTime, endTime);
    }

    public enableAutoPlay(enabled: boolean): void {
        MovingPhotoNative.enableAutoPlay(this.peer!.ptr, enabled);
    }
}

export class ArkMovingPhotoViewPeer extends ArkCommonMethodPeer {
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags);
    }

    public static create(component?: ComponentBase, flags: int32 = 0): ArkMovingPhotoViewPeer {
        const peerId = PeerNode.nextId();
        const _peerPtr = MovingPhotoNative.createMovingPhoto(peerId, flags);
        const _peer = new ArkMovingPhotoViewPeer(_peerPtr, peerId, "MovingPhotoView", flags);
        component?.setPeer(_peer);
        return _peer;
    }
}

export type MovingPhotoViewEventCallback = () => void;

export interface MovingPhotoViewAttribute extends CommonMethod {

    setMovingPhotoViewOptions(options: MovingPhotoViewOptions): this

    muted(isMuted: boolean): this

    objectFit(value: ImageFit): this

    onComplete(callback: MovingPhotoViewEventCallback): this

    onStart(callback: MovingPhotoViewEventCallback): this

    onStop(callback: MovingPhotoViewEventCallback): this

    onPause(callback: MovingPhotoViewEventCallback): this

    onFinish(callback: MovingPhotoViewEventCallback): this

    onError(callback: MovingPhotoViewEventCallback): this

    onPrepared(callback: MovingPhotoViewEventCallback): this

    autoPlayPeriod(startTime: double, endTime: double): this

    autoPlay(isAutoPlay: boolean): this

    repeatPlay(isRepeatPlay: boolean): this

    enableAnalyzer(enabled: boolean): this
}

export class ArkMovingPhotoViewComponent extends ArkCommonMethodComponent implements MovingPhotoViewAttribute {
    constructor() {
    }

    public getPeer():ArkMovingPhotoViewPeer {
        return (this.peer as ArkMovingPhotoViewPeer);
    }

    public setMovingPhotoViewOptions(options: MovingPhotoViewOptions | undefined): this {
        MovingPhotoNative.setMovingPhotoViewOptions(this.getPeer().peer.ptr, options);
        return this;
    }

    public muted(isMuted: boolean): this {
        MovingPhotoNative.muted(this.getPeer().peer.ptr, isMuted);
        return this;
    }

    public objectFit(value: ImageFit): this {
        let result: int = value;
        MovingPhotoNative.objectFit(this.getPeer().peer.ptr, result);
        return this;
    }

    public onComplete(callback: MovingPhotoViewEventCallback): this {
        MovingPhotoNative.onComplete(this.getPeer().peer.ptr, callback);
        return this;
    }

    public onStart(callback: MovingPhotoViewEventCallback): this {
        MovingPhotoNative.onStart(this.getPeer().peer.ptr, callback);
        return this;
    }

    public onStop(callback: MovingPhotoViewEventCallback): this {
        MovingPhotoNative.onStop(this.getPeer().peer.ptr, callback);
        return this;
    }

    public onPause(callback: MovingPhotoViewEventCallback): this {
        MovingPhotoNative.onPause(this.getPeer().peer.ptr, callback);
        return this;
    }

    public onFinish(callback: MovingPhotoViewEventCallback): this {
        MovingPhotoNative.onFinish(this.getPeer().peer.ptr, callback);
        return this;
    }

    public onError(callback: MovingPhotoViewEventCallback): this {
        MovingPhotoNative.onError(this.getPeer().peer.ptr, callback);
        return this;
    }

    public onPrepared(callback: MovingPhotoViewEventCallback): this {
        MovingPhotoNative.onPrepared(this.getPeer().peer.ptr, callback);
        return this;
    }

    public autoPlayPeriod(startTime: double, endTime: double): this {
        MovingPhotoNative.autoPlayPeriod(this.getPeer().peer.ptr, startTime, endTime);
        return this;
    }

    public autoPlay(isAutoPlay: boolean): this {
        MovingPhotoNative.autoPlay(this.getPeer().peer.ptr, isAutoPlay);
        return this;
    }

    public repeatPlay(isRepeatPlay: boolean): this {
        MovingPhotoNative.repeatPlay(this.getPeer().peer.ptr, isRepeatPlay);
        return this;
    }

    public enableAnalyzer(enabled: boolean): this {
        MovingPhotoNative.enableAnalyzer(this.getPeer().peer.ptr, enabled);
        return this;
    }

    public applyAttributesFinish(): void {
        super.applyAttributesFinish();
    }
}

@memo
export function MovingPhotoViewImpl(
    @memo
    style: ((attributes: MovingPhotoViewAttribute) => void) | undefined,
    @memo
    content_?: () => void,
) {
    const receiver = remember<ArkMovingPhotoViewComponent>((): ArkMovingPhotoViewComponent => {
        return new ArkMovingPhotoViewComponent()
    })
    NodeAttach<ArkMovingPhotoViewPeer>((): ArkMovingPhotoViewPeer => ArkMovingPhotoViewPeer.create(receiver), (peer: ArkMovingPhotoViewPeer): void => {
        style?.(receiver)
        content_?.()
    })
}

export class MovingPhotoNative {
    static {loadLibrary("movingphotoview_ani")}
    
    native static createMovingPhoto(peerId: int32, flags: int32): KPointer;
    native static setMovingPhotoViewOptions(node: KPointer, value: MovingPhotoViewOptions | undefined): void;
    native static muted(node: KPointer, value: boolean | undefined): void;
    native static objectFit(node: KPointer, value: int | undefined): void;
    native static autoPlayPeriod(node: KPointer, startTime: double, endTime: double): void;
    native static autoPlay(node: KPointer, value: boolean | undefined): void;
    native static repeatPlay(node: KPointer, value: boolean | undefined): void;
    native static enableAnalyzer(node: KPointer, value: boolean | undefined): void;
    native static onComplete(node: KPointer, value: MovingPhotoViewEventCallback | undefined): void;
    native static onStart(node: KPointer, value: MovingPhotoViewEventCallback | undefined): void;
    native static onStop(node: KPointer, value: MovingPhotoViewEventCallback | undefined): void;
    native static onPause(node: KPointer, value: MovingPhotoViewEventCallback | undefined): void;
    native static onFinish(node: KPointer, value: MovingPhotoViewEventCallback | undefined): void;
    native static onError(node: KPointer, value: MovingPhotoViewEventCallback | undefined): void;
    native static onPrepared(node: KPointer, value: MovingPhotoViewEventCallback | undefined): void;

    native static createMovingPhotoController(): KPointer;
    native static getFinalizer(): KPointer;
    native static startPlayback(controller: KPointer): KPointer;
    native static stopPlayback(controller: KPointer): KPointer;
    native static refreshMovingPhoto(controller: KPointer): KPointer;
    native static pausePlayback(controller: KPointer): KPointer;
    native static reset(controller: KPointer): KPointer;
    native static restart(controller: KPointer): KPointer;
    native static enableTransition(controller: KPointer, value: boolean): KPointer;
    native static setPlaybackPeriod(controller: KPointer, startTime: double, endTime: double): KPointer;
    native static enableAutoPlay(controller: KPointer, value: boolean): KPointer;
}