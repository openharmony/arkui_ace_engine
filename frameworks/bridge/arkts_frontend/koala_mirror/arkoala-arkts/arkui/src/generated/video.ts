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

import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./../CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, UICommonMethod } from "./common"
import { ImageFit } from "./enums"
import { VoidCallback } from "./units"
import { Callback_Void } from "./ability_component"
import { ImageAnalyzerConfig, ImageAIOptions } from "./image_common"
import { Resource } from "./resource"
import { PixelMap } from "./arkui-pixelmap"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
export class VideoControllerInternal {
    public static fromPtr(ptr: KPointer): VideoController {
        const obj : VideoController = new VideoController()
        obj.peer = new Finalizable(ptr, VideoController.getFinalizer())
        return obj
    }
}
export class VideoController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_videocontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._VideoController_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = VideoController.ctor_videocontroller()
        this.peer = new Finalizable(ctorPtr, VideoController.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._VideoController_getFinalizer()
    }
    public start(): void {
        this.start_serialize()
        return
    }
    public pause(): void {
        this.pause_serialize()
        return
    }
    public stop(): void {
        this.stop_serialize()
        return
    }
    public setCurrentTime(value: number, seekMode?: SeekMode): void {
        const value_type = runtimeType(value)
        const seekMode_type = runtimeType(seekMode)
        if (RuntimeType.UNDEFINED == seekMode_type) {
            const value_casted = value as (number)
            this.setCurrentTime0_serialize(value_casted)
            return
        }
        if (TypeChecker.isSeekMode(seekMode)) {
            const value_casted = value as (number)
            const seekMode_casted = seekMode as (SeekMode)
            this.setCurrentTime1_serialize(value_casted, seekMode_casted)
            return
        }
        throw new Error("Can not select appropriate overload")
    }
    public requestFullscreen(value: boolean): void {
        const value_casted = value as (boolean)
        this.requestFullscreen_serialize(value_casted)
        return
    }
    public exitFullscreen(): void {
        this.exitFullscreen_serialize()
        return
    }
    public reset(): void {
        this.reset_serialize()
        return
    }
    private start_serialize(): void {
        ArkUIGeneratedNativeModule._VideoController_start(this.peer!.ptr)
    }
    private pause_serialize(): void {
        ArkUIGeneratedNativeModule._VideoController_pause(this.peer!.ptr)
    }
    private stop_serialize(): void {
        ArkUIGeneratedNativeModule._VideoController_stop(this.peer!.ptr)
    }
    private setCurrentTime0_serialize(value: number): void {
        ArkUIGeneratedNativeModule._VideoController_setCurrentTime0(this.peer!.ptr, value)
    }
    private setCurrentTime1_serialize(value: number, seekMode: SeekMode): void {
        ArkUIGeneratedNativeModule._VideoController_setCurrentTime1(this.peer!.ptr, value, TypeChecker.SeekMode_ToNumeric(seekMode))
    }
    private requestFullscreen_serialize(value: boolean): void {
        ArkUIGeneratedNativeModule._VideoController_requestFullscreen(this.peer!.ptr, value ? 1 : 0)
    }
    private exitFullscreen_serialize(): void {
        ArkUIGeneratedNativeModule._VideoController_exitFullscreen(this.peer!.ptr)
    }
    private reset_serialize(): void {
        ArkUIGeneratedNativeModule._VideoController_reset(this.peer!.ptr)
    }
}
export class ArkVideoPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkVideoPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Video_construct(peerId, flags)
        const _peer  = new ArkVideoPeer(_peerPtr, peerId, "Video", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setVideoOptionsAttribute(value: VideoOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeVideoOptions(value)
        ArkUIGeneratedNativeModule._VideoInterface_setVideoOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    mutedAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._VideoAttribute_muted(this.peer.ptr, value ? 1 : 0)
    }
    autoPlayAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._VideoAttribute_autoPlay(this.peer.ptr, value ? 1 : 0)
    }
    controlsAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._VideoAttribute_controls(this.peer.ptr, value ? 1 : 0)
    }
    loopAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._VideoAttribute_loop(this.peer.ptr, value ? 1 : 0)
    }
    objectFitAttribute(value: ImageFit): void {
        ArkUIGeneratedNativeModule._VideoAttribute_objectFit(this.peer.ptr, TypeChecker.ImageFit_ToNumeric(value))
    }
    onStartAttribute(value: VoidCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._VideoAttribute_onStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onPauseAttribute(value: VoidCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._VideoAttribute_onPause(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onFinishAttribute(value: VoidCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._VideoAttribute_onFinish(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onFullscreenChangeAttribute(value: ((parameter: FullscreenInfo) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._VideoAttribute_onFullscreenChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onPreparedAttribute(value: ((parameter: PreparedInfo) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._VideoAttribute_onPrepared(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSeekingAttribute(value: ((parameter: PlaybackInfo) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._VideoAttribute_onSeeking(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSeekedAttribute(value: ((parameter: PlaybackInfo) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._VideoAttribute_onSeeked(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onUpdateAttribute(value: ((parameter: PlaybackInfo) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._VideoAttribute_onUpdate(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onErrorAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._VideoAttribute_onError(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onStopAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._VideoAttribute_onStop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableAnalyzerAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._VideoAttribute_enableAnalyzer(this.peer.ptr, value ? 1 : 0)
    }
    analyzerConfigAttribute(value: ImageAnalyzerConfig): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeImageAnalyzerConfig(value)
        ArkUIGeneratedNativeModule._VideoAttribute_analyzerConfig(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum SeekMode {
    PREVIOUS_KEYFRAME = 0,
    PreviousKeyframe = 0,
    NEXT_KEYFRAME = 1,
    NextKeyframe = 1,
    CLOSEST_KEYFRAME = 2,
    ClosestKeyframe = 2,
    ACCURATE = 3,
    Accurate = 3
}
export enum PlaybackSpeed {
    SPEED_FORWARD_0_75_X = 0,
    Speed_Forward_0_75_X = 0,
    SPEED_FORWARD_1_00_X = 1,
    Speed_Forward_1_00_X = 1,
    SPEED_FORWARD_1_25_X = 2,
    Speed_Forward_1_25_X = 2,
    SPEED_FORWARD_1_75_X = 3,
    Speed_Forward_1_75_X = 3,
    SPEED_FORWARD_2_00_X = 4,
    Speed_Forward_2_00_X = 4
}
export interface FullscreenInfo {
    fullscreen: boolean;
}
export interface PreparedInfo {
    duration: number;
}
export interface PlaybackInfo {
    time: number;
}
export interface VideoOptions {
    src?: string | Resource;
    currentProgressRate?: number | string | PlaybackSpeed;
    previewUri?: string | PixelMap | Resource;
    controller?: VideoController;
    imageAIOptions?: ImageAIOptions;
}

export type Callback_FullscreenInfo_Void = (parameter: FullscreenInfo) => void;
export type Callback_PreparedInfo_Void = (parameter: PreparedInfo) => void;
export type Callback_PlaybackInfo_Void = (parameter: PlaybackInfo) => void;
export interface VideoAttribute extends CommonMethod {
    muted(value: boolean): this
    autoPlay(value: boolean): this
    controls(value: boolean): this
    loop(value: boolean): this
    objectFit(value: ImageFit): this
    onStart(value: VoidCallback): this
    onPause(value: VoidCallback): this
    onFinish(value: VoidCallback): this
    onFullscreenChange(value: ((parameter: FullscreenInfo) => void)): this
    onPrepared(value: ((parameter: PreparedInfo) => void)): this
    onSeeking(value: ((parameter: PlaybackInfo) => void)): this
    onSeeked(value: ((parameter: PlaybackInfo) => void)): this
    onUpdate(value: ((parameter: PlaybackInfo) => void)): this
    onError(value: (() => void)): this
    onStop(value: (() => void)): this
    enableAnalyzer(value: boolean): this
    analyzerConfig(value: ImageAnalyzerConfig): this
    attributeModifier(value: AttributeModifier<VideoAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UIVideoAttribute extends UICommonMethod {
    /** @memo */
    muted(value: boolean): this
    /** @memo */
    autoPlay(value: boolean): this
    /** @memo */
    controls(value: boolean): this
    /** @memo */
    loop(value: boolean): this
    /** @memo */
    objectFit(value: ImageFit): this
    /** @memo */
    onStart(value: VoidCallback): this
    /** @memo */
    onPause(value: VoidCallback): this
    /** @memo */
    onFinish(value: VoidCallback): this
    /** @memo */
    onFullscreenChange(value: ((parameter: FullscreenInfo) => void)): this
    /** @memo */
    onPrepared(value: ((parameter: PreparedInfo) => void)): this
    /** @memo */
    onSeeking(value: ((parameter: PlaybackInfo) => void)): this
    /** @memo */
    onSeeked(value: ((parameter: PlaybackInfo) => void)): this
    /** @memo */
    onUpdate(value: ((parameter: PlaybackInfo) => void)): this
    /** @memo */
    onError(value: (() => void)): this
    /** @memo */
    onStop(value: (() => void)): this
    /** @memo */
    enableAnalyzer(value: boolean): this
    /** @memo */
    analyzerConfig(value: ImageAnalyzerConfig): this
    /** @memo */
    attributeModifier(value: AttributeModifier<VideoAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkVideoStyle extends ArkCommonMethodStyle implements VideoAttribute {
    muted_value?: boolean
    autoPlay_value?: boolean
    controls_value?: boolean
    loop_value?: boolean
    objectFit_value?: ImageFit
    onStart_value?: VoidCallback
    onPause_value?: VoidCallback
    onFinish_value?: VoidCallback
    onFullscreenChange_value?: ((parameter: FullscreenInfo) => void)
    onPrepared_value?: ((parameter: PreparedInfo) => void)
    onSeeking_value?: ((parameter: PlaybackInfo) => void)
    onSeeked_value?: ((parameter: PlaybackInfo) => void)
    onUpdate_value?: ((parameter: PlaybackInfo) => void)
    onError_value?: (() => void)
    onStop_value?: (() => void)
    enableAnalyzer_value?: boolean
    analyzerConfig_value?: ImageAnalyzerConfig
    public muted(value: boolean): this {
        return this
    }
    public autoPlay(value: boolean): this {
        return this
    }
    public controls(value: boolean): this {
        return this
    }
    public loop(value: boolean): this {
        return this
    }
    public objectFit(value: ImageFit): this {
        return this
    }
    public onStart(value: VoidCallback): this {
        return this
    }
    public onPause(value: VoidCallback): this {
        return this
    }
    public onFinish(value: VoidCallback): this {
        return this
    }
    public onFullscreenChange(value: ((parameter: FullscreenInfo) => void)): this {
        return this
    }
    public onPrepared(value: ((parameter: PreparedInfo) => void)): this {
        return this
    }
    public onSeeking(value: ((parameter: PlaybackInfo) => void)): this {
        return this
    }
    public onSeeked(value: ((parameter: PlaybackInfo) => void)): this {
        return this
    }
    public onUpdate(value: ((parameter: PlaybackInfo) => void)): this {
        return this
    }
    public onError(value: (() => void)): this {
        return this
    }
    public onStop(value: (() => void)): this {
        return this
    }
    public enableAnalyzer(value: boolean): this {
        return this
    }
    public analyzerConfig(value: ImageAnalyzerConfig): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<VideoAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
/** @memo:stable */
export class ArkVideoComponent extends ArkCommonMethodComponent implements UIVideoAttribute {
    getPeer(): ArkVideoPeer {
        return (this.peer as ArkVideoPeer)
    }
    /** @memo */
    public setVideoOptions(value: VideoOptions): this {
        if (this.checkPriority("setVideoOptions")) {
            const value_casted = value as (VideoOptions)
            this.getPeer()?.setVideoOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public muted(value: boolean): this {
        if (this.checkPriority("muted")) {
            const value_casted = value as (boolean)
            this.getPeer()?.mutedAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public autoPlay(value: boolean): this {
        if (this.checkPriority("autoPlay")) {
            const value_casted = value as (boolean)
            this.getPeer()?.autoPlayAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public controls(value: boolean): this {
        if (this.checkPriority("controls")) {
            const value_casted = value as (boolean)
            this.getPeer()?.controlsAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public loop(value: boolean): this {
        if (this.checkPriority("loop")) {
            const value_casted = value as (boolean)
            this.getPeer()?.loopAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public objectFit(value: ImageFit): this {
        if (this.checkPriority("objectFit")) {
            const value_casted = value as (ImageFit)
            this.getPeer()?.objectFitAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onStart(value: VoidCallback): this {
        if (this.checkPriority("onStart")) {
            const value_casted = value as (VoidCallback)
            this.getPeer()?.onStartAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onPause(value: VoidCallback): this {
        if (this.checkPriority("onPause")) {
            const value_casted = value as (VoidCallback)
            this.getPeer()?.onPauseAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onFinish(value: VoidCallback): this {
        if (this.checkPriority("onFinish")) {
            const value_casted = value as (VoidCallback)
            this.getPeer()?.onFinishAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onFullscreenChange(value: ((parameter: FullscreenInfo) => void)): this {
        if (this.checkPriority("onFullscreenChange")) {
            const value_casted = value as (((parameter: FullscreenInfo) => void))
            this.getPeer()?.onFullscreenChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onPrepared(value: ((parameter: PreparedInfo) => void)): this {
        if (this.checkPriority("onPrepared")) {
            const value_casted = value as (((parameter: PreparedInfo) => void))
            this.getPeer()?.onPreparedAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onSeeking(value: ((parameter: PlaybackInfo) => void)): this {
        if (this.checkPriority("onSeeking")) {
            const value_casted = value as (((parameter: PlaybackInfo) => void))
            this.getPeer()?.onSeekingAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onSeeked(value: ((parameter: PlaybackInfo) => void)): this {
        if (this.checkPriority("onSeeked")) {
            const value_casted = value as (((parameter: PlaybackInfo) => void))
            this.getPeer()?.onSeekedAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onUpdate(value: ((parameter: PlaybackInfo) => void)): this {
        if (this.checkPriority("onUpdate")) {
            const value_casted = value as (((parameter: PlaybackInfo) => void))
            this.getPeer()?.onUpdateAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onError(value: (() => void)): this {
        if (this.checkPriority("onError")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onErrorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onStop(value: (() => void)): this {
        if (this.checkPriority("onStop")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onStopAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public enableAnalyzer(value: boolean): this {
        if (this.checkPriority("enableAnalyzer")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enableAnalyzerAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public analyzerConfig(value: ImageAnalyzerConfig): this {
        if (this.checkPriority("analyzerConfig")) {
            const value_casted = value as (ImageAnalyzerConfig)
            this.getPeer()?.analyzerConfigAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public attributeModifier(value: AttributeModifier<VideoAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function ArkVideo(
    /** @memo */
    style: ((attributes: UIVideoAttribute) => void) | undefined,
    /** @memo */
    content_: (() => void) | undefined,
    value: VideoOptions,
): void {
    const receiver = remember(() => {
        return new ArkVideoComponent()
    })
    NodeAttach<ArkVideoPeer>((): ArkVideoPeer => ArkVideoPeer.create(receiver), (_: ArkVideoPeer) => {
        receiver.setVideoOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
