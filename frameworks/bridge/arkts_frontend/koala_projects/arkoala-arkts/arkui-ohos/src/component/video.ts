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
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { ImageFit } from "./enums"
import { VoidCallback } from "./units"
import { ImageAnalyzerConfig, ImageAIOptions } from "./imageCommon"
import { ColorMetrics } from "../Graphics"
import { NodeAttach, remember } from "@koalaui/runtime"
import { Resource } from "global.resource"
import { PixelMap } from "./arkui-pixelmap"

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
        return this.start_serialize()
    }
    public pause(): void {
        return this.pause_serialize()
    }
    public stop(): void {
        return this.stop_serialize()
    }
    public setCurrentTime(value: number, seekMode?: SeekMode): void {
        const value_type = runtimeType(value)
        const seekMode_type = runtimeType(seekMode)
        if (RuntimeType.UNDEFINED == seekMode_type) {
            const value_casted = value as (number)
            return this.setCurrentTime0_serialize(value_casted)
        }
        if (TypeChecker.isSeekMode(seekMode)) {
            const value_casted = value as (number)
            const seekMode_casted = seekMode as (SeekMode)
            return this.setCurrentTime1_serialize(value_casted, seekMode_casted)
        }
        throw new Error("Can not select appropriate overload")
    }
    public requestFullscreen(value: boolean): void {
        const value_casted = value as (boolean)
        return this.requestFullscreen_serialize(value_casted)
    }
    public exitFullscreen(): void {
        return this.exitFullscreen_serialize()
    }
    public reset(): void {
        this.reset_serialize()
        return
    }
    private start_serialize(): void {
        const retval  = ArkUIGeneratedNativeModule._VideoController_start(this.peer!.ptr)
        return
    }
    private pause_serialize(): void {
        const retval  = ArkUIGeneratedNativeModule._VideoController_pause(this.peer!.ptr)
        return
    }
    private stop_serialize(): void {
        const retval  = ArkUIGeneratedNativeModule._VideoController_stop(this.peer!.ptr)
        return
    }
    private setCurrentTime0_serialize(value: number): void {
        const retval  = ArkUIGeneratedNativeModule._VideoController_setCurrentTime0(this.peer!.ptr, value)
        return
    }
    private setCurrentTime1_serialize(value: number, seekMode: SeekMode): void {
        const retval  = ArkUIGeneratedNativeModule._VideoController_setCurrentTime1(this.peer!.ptr, value, TypeChecker.SeekMode_ToNumeric(seekMode))
        return
    }
    private requestFullscreen_serialize(value: boolean): void {
        const retval  = ArkUIGeneratedNativeModule._VideoController_requestFullscreen(this.peer!.ptr, value ? 1 : 0)
        return
    }
    private exitFullscreen_serialize(): void {
        const retval  = ArkUIGeneratedNativeModule._VideoController_exitFullscreen(this.peer!.ptr)
        return
    }
    private reset_serialize(): void {
        ArkUIGeneratedNativeModule._VideoController_reset(this.peer!.ptr)
    }
}
export class ArkVideoPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkVideoPeer {
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
    mutedAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_muted(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    autoPlayAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_autoPlay(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    controlsAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_controls(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    loopAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_loop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    objectFitAttribute(value: ImageFit | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as ImageFit)
            thisSerializer.writeInt32(TypeChecker.ImageFit_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._VideoAttribute_objectFit(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onStartAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_onStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onPauseAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_onPause(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onFinishAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_onFinish(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onFullscreenChangeAttribute(value: ((parameter: FullscreenInfo) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_onFullscreenChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onPreparedAttribute(value: ((parameter: PreparedInfo) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_onPrepared(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSeekingAttribute(value: ((parameter: PlaybackInfo) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_onSeeking(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSeekedAttribute(value: ((parameter: PlaybackInfo) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_onSeeked(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onUpdateAttribute(value: ((parameter: PlaybackInfo) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_onUpdate(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onErrorAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_onError(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onStopAttribute(value: ((value: undefined) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_onStop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableAnalyzerAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_enableAnalyzer(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    analyzerConfigAttribute(value: ImageAnalyzerConfig | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeImageAnalyzerConfig(value_value)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_analyzerConfig(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    surfaceBackgroundColorAttribute(value: ColorMetrics | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeColorMetrics(value_value)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_surfaceBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableShortcutKeyAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_enableShortcutKey(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
export interface PosterOptions {
    showFirstFrame?: boolean;
}
export interface VideoOptions {
    src?: string | Resource;
    currentProgressRate?: number | string | PlaybackSpeed;
    previewUri?: string | PixelMap | Resource;
    controller?: VideoController;
    imageAIOptions?: ImageAIOptions;
    posterOptions?: PosterOptions;
}
export type VideoInterface = (value: VideoOptions) => VideoAttribute;
export type Callback_FullscreenInfo_Void = (parameter: FullscreenInfo) => void;
export type Callback_PreparedInfo_Void = (parameter: PreparedInfo) => void;
export type Callback_PlaybackInfo_Void = (parameter: PlaybackInfo) => void;
export interface VideoAttribute extends CommonMethod {
    muted(value: boolean | undefined): this
    autoPlay(value: boolean | undefined): this
    controls(value: boolean | undefined): this
    loop(value: boolean | undefined): this
    objectFit(value: ImageFit | undefined): this
    onStart(value: VoidCallback | undefined): this
    onPause(value: VoidCallback | undefined): this
    onFinish(value: VoidCallback | undefined): this
    onFullscreenChange(value: ((parameter: FullscreenInfo) => void) | undefined): this
    onPrepared(value: ((parameter: PreparedInfo) => void) | undefined): this
    onSeeking(value: ((parameter: PlaybackInfo) => void) | undefined): this
    onSeeked(value: ((parameter: PlaybackInfo) => void) | undefined): this
    onUpdate(value: ((parameter: PlaybackInfo) => void) | undefined): this
    onError(value: (() => void) | undefined): this
    onStop(value: ((value: undefined) => void) | undefined): this
    enableAnalyzer(value: boolean | undefined): this
    analyzerConfig(value: ImageAnalyzerConfig | undefined): this
    surfaceBackgroundColor(value: ColorMetrics | undefined): this
    enableShortcutKey(value: boolean | undefined): this
}
export class ArkVideoStyle extends ArkCommonMethodStyle implements VideoAttribute {
    muted_value?: boolean | undefined
    autoPlay_value?: boolean | undefined
    controls_value?: boolean | undefined
    loop_value?: boolean | undefined
    objectFit_value?: ImageFit | undefined
    onStart_value?: VoidCallback | undefined
    onPause_value?: VoidCallback | undefined
    onFinish_value?: VoidCallback | undefined
    onFullscreenChange_value?: ((parameter: FullscreenInfo) => void) | undefined
    onPrepared_value?: ((parameter: PreparedInfo) => void) | undefined
    onSeeking_value?: ((parameter: PlaybackInfo) => void) | undefined
    onSeeked_value?: ((parameter: PlaybackInfo) => void) | undefined
    onUpdate_value?: ((parameter: PlaybackInfo) => void) | undefined
    onError_value?: (() => void) | undefined
    onStop_value?: ((value: undefined) => void) | undefined
    enableAnalyzer_value?: boolean | undefined
    analyzerConfig_value?: ImageAnalyzerConfig | undefined
    surfaceBackgroundColor_value?: ColorMetrics | undefined
    enableShortcutKey_value?: boolean | undefined
    public muted(value: boolean | undefined): this {
        return this
    }
    public autoPlay(value: boolean | undefined): this {
        return this
    }
    public controls(value: boolean | undefined): this {
        return this
    }
    public loop(value: boolean | undefined): this {
        return this
    }
    public objectFit(value: ImageFit | undefined): this {
        return this
    }
    public onStart(value: VoidCallback | undefined): this {
        return this
    }
    public onPause(value: VoidCallback | undefined): this {
        return this
    }
    public onFinish(value: VoidCallback | undefined): this {
        return this
    }
    public onFullscreenChange(value: ((parameter: FullscreenInfo) => void) | undefined): this {
        return this
    }
    public onPrepared(value: ((parameter: PreparedInfo) => void) | undefined): this {
        return this
    }
    public onSeeking(value: ((parameter: PlaybackInfo) => void) | undefined): this {
        return this
    }
    public onSeeked(value: ((parameter: PlaybackInfo) => void) | undefined): this {
        return this
    }
    public onUpdate(value: ((parameter: PlaybackInfo) => void) | undefined): this {
        return this
    }
    public onError(value: (() => void) | undefined): this {
        return this
    }
    public onStop(value: ((value: undefined) => void) | undefined): this {
        return this
    }
    public enableAnalyzer(value: boolean | undefined): this {
        return this
    }
    public analyzerConfig(value: ImageAnalyzerConfig | undefined): this {
        return this
    }
    public surfaceBackgroundColor(value: ColorMetrics | undefined): this {
        return this
    }
    public enableShortcutKey(value: boolean | undefined): this {
        return this
        }
}
export class ArkVideoComponent extends ArkCommonMethodComponent implements VideoAttribute {
    getPeer(): ArkVideoPeer {
        return (this.peer as ArkVideoPeer)
    }
    public setVideoOptions(value: VideoOptions): this {
        if (this.checkPriority("setVideoOptions")) {
            const value_casted = value as (VideoOptions)
            this.getPeer()?.setVideoOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public muted(value: boolean | undefined): this {
        if (this.checkPriority("muted")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.mutedAttribute(value_casted)
            return this
        }
        return this
    }
    public autoPlay(value: boolean | undefined): this {
        if (this.checkPriority("autoPlay")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.autoPlayAttribute(value_casted)
            return this
        }
        return this
    }
    public controls(value: boolean | undefined): this {
        if (this.checkPriority("controls")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.controlsAttribute(value_casted)
            return this
        }
        return this
    }
    public loop(value: boolean | undefined): this {
        if (this.checkPriority("loop")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.loopAttribute(value_casted)
            return this
        }
        return this
    }
    public objectFit(value: ImageFit | undefined): this {
        if (this.checkPriority("objectFit")) {
            const value_casted = value as (ImageFit | undefined)
            this.getPeer()?.objectFitAttribute(value_casted)
            return this
        }
        return this
    }
    public onStart(value: VoidCallback | undefined): this {
        if (this.checkPriority("onStart")) {
            const value_casted = value as (VoidCallback | undefined)
            this.getPeer()?.onStartAttribute(value_casted)
            return this
        }
        return this
    }
    public onPause(value: VoidCallback | undefined): this {
        if (this.checkPriority("onPause")) {
            const value_casted = value as (VoidCallback | undefined)
            this.getPeer()?.onPauseAttribute(value_casted)
            return this
        }
        return this
    }
    public onFinish(value: VoidCallback | undefined): this {
        if (this.checkPriority("onFinish")) {
            const value_casted = value as (VoidCallback | undefined)
            this.getPeer()?.onFinishAttribute(value_casted)
            return this
        }
        return this
    }
    public onFullscreenChange(value: ((parameter: FullscreenInfo) => void) | undefined): this {
        if (this.checkPriority("onFullscreenChange")) {
            const value_casted = value as (((parameter: FullscreenInfo) => void) | undefined)
            this.getPeer()?.onFullscreenChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onPrepared(value: ((parameter: PreparedInfo) => void) | undefined): this {
        if (this.checkPriority("onPrepared")) {
            const value_casted = value as (((parameter: PreparedInfo) => void) | undefined)
            this.getPeer()?.onPreparedAttribute(value_casted)
            return this
        }
        return this
    }
    public onSeeking(value: ((parameter: PlaybackInfo) => void) | undefined): this {
        if (this.checkPriority("onSeeking")) {
            const value_casted = value as (((parameter: PlaybackInfo) => void) | undefined)
            this.getPeer()?.onSeekingAttribute(value_casted)
            return this
        }
        return this
    }
    public onSeeked(value: ((parameter: PlaybackInfo) => void) | undefined): this {
        if (this.checkPriority("onSeeked")) {
            const value_casted = value as (((parameter: PlaybackInfo) => void) | undefined)
            this.getPeer()?.onSeekedAttribute(value_casted)
            return this
        }
        return this
    }
    public onUpdate(value: ((parameter: PlaybackInfo) => void) | undefined): this {
        if (this.checkPriority("onUpdate")) {
            const value_casted = value as (((parameter: PlaybackInfo) => void) | undefined)
            this.getPeer()?.onUpdateAttribute(value_casted)
            return this
        }
        return this
    }
    public onError(value: (() => void) | undefined): this {
        if (this.checkPriority("onError")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onErrorAttribute(value_casted)
            return this
        }
        return this
    }
    public onStop(value: ((value: undefined) => void) | undefined): this {
        if (this.checkPriority("onStop")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onStopAttribute(value_casted)
            return this
        }
        return this
    }
    public enableAnalyzer(value: boolean | undefined): this {
        if (this.checkPriority("enableAnalyzer")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.enableAnalyzerAttribute(value_casted)
            return this
        }
        return this
    }
    public analyzerConfig(value: ImageAnalyzerConfig | undefined): this {
        if (this.checkPriority("analyzerConfig")) {
            const value_casted = value as (ImageAnalyzerConfig | undefined)
            this.getPeer()?.analyzerConfigAttribute(value_casted)
            return this
        }
        return this
    }
    public surfaceBackgroundColor(value: ColorMetrics | undefined): this {
        if (this.checkPriority("surfaceBackgroundColor")) {
            const value_casted = value as (ColorMetrics | undefined)
            this.getPeer()?.surfaceBackgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    public enableShortcutKey(value: boolean | undefined): this {
        if (this.checkPriority("enableShortcutKey")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.enableShortcutKeyAttribute(value_casted)
            return this
        }
        return this
    }
    
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function Video(
    /** @memo */
    style: ((attributes: VideoAttribute) => void) | undefined,
    value: VideoOptions,
    /** @memo */
    content_?: (() => void) | undefined,
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
