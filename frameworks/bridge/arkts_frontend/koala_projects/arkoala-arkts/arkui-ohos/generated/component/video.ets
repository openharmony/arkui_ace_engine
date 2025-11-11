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
import { Finalizable, runtimeType, RuntimeType, SerializerBase, DeserializerBase, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackTransformer } from "./../CallbackTransformer"
import { ColorMetrics_serializer } from "./../Graphics"
import { ImageAnalyzerConfig_serializer, ImageAnalyzerConfig, ImageAIOptions, ImageAIOptions_serializer } from "./imageCommon"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { ImageFit } from "./enums"
import { VoidCallback } from "./units"
import { ErrorCallback } from "@ohos.base"
import { AttributeModifier, extractors, hookVideoAttributeModifier, AttributeUpdater, hookSetVideoOptions, hookVideoAnalyzerConfig } from "#handwritten"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { ColorMetrics } from "arkui.Graphics"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { Resource } from "global.resource"
import { default as image } from "@ohos.multimedia.image"
import { VideoModifier } from "./../VideoModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
import { Resource_serializer } from "./../framework/resource"
import { image_PixelMap_serializer } from "./../framework/ohos.multimedia.image"
export class VideoControllerInternal {
    public static fromPtr(ptr: KPointer): VideoController {
        return new VideoController(ptr)
    }
}
export class VideoController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, VideoController.getFinalizer())
    }
    constructor() {
        this(VideoController.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._VideoController_construct()
        return retval
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
    public requestFullscreen(value: boolean): void {
        const value_casted = value as (boolean)
        this.requestFullscreen_serialize(value_casted)
        return
    }
    public exitFullscreen(): void {
        this.exitFullscreen_serialize()
        return
    }
    public setCurrentTime(value: double, seekMode?: SeekMode): void {
        const value_casted = value as (double)
        const seekMode_casted = seekMode as (SeekMode | undefined)
        this.setCurrentTime_serialize(value_casted, seekMode_casted)
        return
    }
    public reset(): void {
        this.reset_serialize()
        return
    }
    start_serialize(): void {
        ArkUIGeneratedNativeModule._VideoController_start(this.peer!.ptr)
    }
    pause_serialize(): void {
        ArkUIGeneratedNativeModule._VideoController_pause(this.peer!.ptr)
    }
    stop_serialize(): void {
        ArkUIGeneratedNativeModule._VideoController_stop(this.peer!.ptr)
    }
    requestFullscreen_serialize(value: boolean): void {
        ArkUIGeneratedNativeModule._VideoController_requestFullscreen(this.peer!.ptr, value ? 1 : 0)
    }
    exitFullscreen_serialize(): void {
        ArkUIGeneratedNativeModule._VideoController_exitFullscreen(this.peer!.ptr)
    }
    setCurrentTime_serialize(value: double, seekMode?: SeekMode): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (seekMode !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const seekModeTmpValue  = (seekMode as SeekMode)
            thisSerializer.writeInt32(seekModeTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._VideoController_setCurrentTime(this.peer!.ptr, value, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    reset_serialize(): void {
        ArkUIGeneratedNativeModule._VideoController_reset(this.peer!.ptr)
    }
}
export class ArkVideoPeer extends ArkCommonMethodPeer {
    attributeSet?: VideoModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkVideoPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Video_construct(peerId, flags)
        const _peer  = new ArkVideoPeer(_peerPtr, peerId, 'Video', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setVideoOptionsAttribute(value: VideoOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        VideoOptions_serializer.write(thisSerializer, value)
        ArkUIGeneratedNativeModule._VideoInterface_setVideoOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMutedAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_setMuted(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAutoPlayAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_setAutoPlay(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setControlsAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_setControls(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLoopAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_setLoop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setObjectFitAttribute(value: ImageFit | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as ImageFit)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_setObjectFit(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnStartAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_setOnStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnPauseAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_setOnPause(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnFinishAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_setOnFinish(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnFullscreenChangeAttribute(value: ((value0: FullscreenInfo) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_setOnFullscreenChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnPreparedAttribute(value: ((value0: PreparedInfo) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_setOnPrepared(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnSeekingAttribute(value: ((value0: PlaybackInfo) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_setOnSeeking(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnSeekedAttribute(value: ((value0: PlaybackInfo) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_setOnSeeked(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnUpdateAttribute(value: ((value0: PlaybackInfo) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_setOnUpdate(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnErrorAttribute(value: VoidCallback | ErrorCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof VoidCallback) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as VoidCallback
                thisSerializer.holdAndWriteCallback(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof ErrorCallback) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as ErrorCallback
                thisSerializer.holdAndWriteCallback(valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_setOnError(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnStopAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_setOnStop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableAnalyzerAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_setEnableAnalyzer(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAnalyzerConfigAttribute(value: ImageAnalyzerConfig | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            ImageAnalyzerConfig_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_setAnalyzerConfig(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableShortcutKeyAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_setEnableShortcutKey(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSurfaceBackgroundColorAttribute(value: ColorMetrics | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            ColorMetrics_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_setSurfaceBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    duration: int32;
}
export interface PlaybackInfo {
    time: int32;
}
export interface PosterOptions {
    showFirstFrame?: boolean;
}
export interface VideoOptions {
    src?: string | Resource;
    currentProgressRate?: double | string | PlaybackSpeed;
    previewUri?: string | image.PixelMap | Resource;
    controller?: VideoController;
    imageAIOptions?: ImageAIOptions;
    posterOptions?: PosterOptions;
}
export interface VideoAttribute extends CommonMethod {
    setVideoOptions(value: VideoOptions): this {
        throw new Error("Unimplemented method setVideoOptions")
    }
    muted(value: boolean | undefined): this {
        throw new Error("Unimplemented method muted")
    }
    autoPlay(value: boolean | undefined): this {
        throw new Error("Unimplemented method autoPlay")
    }
    controls(value: boolean | undefined): this {
        throw new Error("Unimplemented method controls")
    }
    loop(value: boolean | undefined): this {
        throw new Error("Unimplemented method loop")
    }
    objectFit(value: ImageFit | undefined): this {
        throw new Error("Unimplemented method objectFit")
    }
    onStart(value: VoidCallback | undefined): this {
        throw new Error("Unimplemented method onStart")
    }
    onPause(value: VoidCallback | undefined): this {
        throw new Error("Unimplemented method onPause")
    }
    onFinish(value: VoidCallback | undefined): this {
        throw new Error("Unimplemented method onFinish")
    }
    onFullscreenChange(value: ((value0: FullscreenInfo) => void) | undefined): this {
        throw new Error("Unimplemented method onFullscreenChange")
    }
    onPrepared(value: ((value0: PreparedInfo) => void) | undefined): this {
        throw new Error("Unimplemented method onPrepared")
    }
    onSeeking(value: ((value0: PlaybackInfo) => void) | undefined): this {
        throw new Error("Unimplemented method onSeeking")
    }
    onSeeked(value: ((value0: PlaybackInfo) => void) | undefined): this {
        throw new Error("Unimplemented method onSeeked")
    }
    onUpdate(value: ((value0: PlaybackInfo) => void) | undefined): this {
        throw new Error("Unimplemented method onUpdate")
    }
    onError(value: VoidCallback | ErrorCallback | undefined): this {
        throw new Error("Unimplemented method onError")
    }
    onStop(value: VoidCallback | undefined): this {
        throw new Error("Unimplemented method onStop")
    }
    enableAnalyzer(value: boolean | undefined): this {
        throw new Error("Unimplemented method enableAnalyzer")
    }
    analyzerConfig(value: ImageAnalyzerConfig | undefined): this {
        throw new Error("Unimplemented method analyzerConfig")
    }
    enableShortcutKey(value: boolean | undefined): this {
        throw new Error("Unimplemented method enableShortcutKey")
    }
    surfaceBackgroundColor(value: ColorMetrics | undefined): this {
        throw new Error("Unimplemented method surfaceBackgroundColor")
    }
    attributeModifier(value: AttributeModifier<VideoAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
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
    onFullscreenChange_value?: ((value0: FullscreenInfo) => void) | undefined
    onPrepared_value?: ((value0: PreparedInfo) => void) | undefined
    onSeeking_value?: ((value0: PlaybackInfo) => void) | undefined
    onSeeked_value?: ((value0: PlaybackInfo) => void) | undefined
    onUpdate_value?: ((value0: PlaybackInfo) => void) | undefined
    onError_value?: VoidCallback | ErrorCallback | undefined
    onStop_value?: VoidCallback | undefined
    enableAnalyzer_value?: boolean | undefined
    analyzerConfig_value?: ImageAnalyzerConfig | undefined
    enableShortcutKey_value?: boolean | undefined
    surfaceBackgroundColor_value?: ColorMetrics | undefined
    attributeModifier_value?: AttributeModifier<VideoAttribute> | AttributeModifier<CommonMethod> | undefined
    setVideoOptions(value: VideoOptions): this {
        return this
    }
    muted(value: boolean | undefined): this {
        return this
    }
    autoPlay(value: boolean | undefined): this {
        return this
    }
    controls(value: boolean | undefined): this {
        return this
    }
    loop(value: boolean | undefined): this {
        return this
    }
    objectFit(value: ImageFit | undefined): this {
        return this
    }
    onStart(value: VoidCallback | undefined): this {
        return this
    }
    onPause(value: VoidCallback | undefined): this {
        return this
    }
    onFinish(value: VoidCallback | undefined): this {
        return this
    }
    onFullscreenChange(value: ((value0: FullscreenInfo) => void) | undefined): this {
        return this
    }
    onPrepared(value: ((value0: PreparedInfo) => void) | undefined): this {
        return this
    }
    onSeeking(value: ((value0: PlaybackInfo) => void) | undefined): this {
        return this
    }
    onSeeked(value: ((value0: PlaybackInfo) => void) | undefined): this {
        return this
    }
    onUpdate(value: ((value0: PlaybackInfo) => void) | undefined): this {
        return this
    }
    onError(value: VoidCallback | ErrorCallback | undefined): this {
        return this
    }
    onStop(value: VoidCallback | undefined): this {
        return this
    }
    enableAnalyzer(value: boolean | undefined): this {
        return this
    }
    analyzerConfig(value: ImageAnalyzerConfig | undefined): this {
        return this
    }
    enableShortcutKey(value: boolean | undefined): this {
        return this
    }
    surfaceBackgroundColor(value: ColorMetrics | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<VideoAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkVideoComponent extends ArkCommonMethodComponent implements VideoAttribute {
    getPeer(): ArkVideoPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkVideoPeer)
    }
    public setVideoOptions(value: VideoOptions): this {
        if (this.checkPriority("setVideoOptions")) {
            hookSetVideoOptions(this, value)
            const value_casted = value as (VideoOptions)
            this.getPeer()?.setVideoOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public muted(value: boolean | undefined): this {
        if (this.checkPriority("muted")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setMutedAttribute(value_casted)
            return this
        }
        return this
    }
    public autoPlay(value: boolean | undefined): this {
        if (this.checkPriority("autoPlay")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setAutoPlayAttribute(value_casted)
            return this
        }
        return this
    }
    public controls(value: boolean | undefined): this {
        if (this.checkPriority("controls")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setControlsAttribute(value_casted)
            return this
        }
        return this
    }
    public loop(value: boolean | undefined): this {
        if (this.checkPriority("loop")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setLoopAttribute(value_casted)
            return this
        }
        return this
    }
    public objectFit(value: ImageFit | undefined): this {
        if (this.checkPriority("objectFit")) {
            const value_casted = value as (ImageFit | undefined)
            this.getPeer()?.setObjectFitAttribute(value_casted)
            return this
        }
        return this
    }
    public onStart(value: VoidCallback | undefined): this {
        if (this.checkPriority("onStart")) {
            const value_casted = value as (VoidCallback | undefined)
            this.getPeer()?.setOnStartAttribute(value_casted)
            return this
        }
        return this
    }
    public onPause(value: VoidCallback | undefined): this {
        if (this.checkPriority("onPause")) {
            const value_casted = value as (VoidCallback | undefined)
            this.getPeer()?.setOnPauseAttribute(value_casted)
            return this
        }
        return this
    }
    public onFinish(value: VoidCallback | undefined): this {
        if (this.checkPriority("onFinish")) {
            const value_casted = value as (VoidCallback | undefined)
            this.getPeer()?.setOnFinishAttribute(value_casted)
            return this
        }
        return this
    }
    public onFullscreenChange(value: ((value0: FullscreenInfo) => void) | undefined): this {
        if (this.checkPriority("onFullscreenChange")) {
            const value_casted = value as (((value0: FullscreenInfo) => void) | undefined)
            this.getPeer()?.setOnFullscreenChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onPrepared(value: ((value0: PreparedInfo) => void) | undefined): this {
        if (this.checkPriority("onPrepared")) {
            const value_casted = value as (((value0: PreparedInfo) => void) | undefined)
            this.getPeer()?.setOnPreparedAttribute(value_casted)
            return this
        }
        return this
    }
    public onSeeking(value: ((value0: PlaybackInfo) => void) | undefined): this {
        if (this.checkPriority("onSeeking")) {
            const value_casted = value as (((value0: PlaybackInfo) => void) | undefined)
            this.getPeer()?.setOnSeekingAttribute(value_casted)
            return this
        }
        return this
    }
    public onSeeked(value: ((value0: PlaybackInfo) => void) | undefined): this {
        if (this.checkPriority("onSeeked")) {
            const value_casted = value as (((value0: PlaybackInfo) => void) | undefined)
            this.getPeer()?.setOnSeekedAttribute(value_casted)
            return this
        }
        return this
    }
    public onUpdate(value: ((value0: PlaybackInfo) => void) | undefined): this {
        if (this.checkPriority("onUpdate")) {
            const value_casted = value as (((value0: PlaybackInfo) => void) | undefined)
            this.getPeer()?.setOnUpdateAttribute(value_casted)
            return this
        }
        return this
    }
    public onError(value: VoidCallback | ErrorCallback | undefined): this {
        if (this.checkPriority("onError")) {
            const value_casted = value as (VoidCallback | ErrorCallback | undefined)
            this.getPeer()?.setOnErrorAttribute(value_casted)
            return this
        }
        return this
    }
    public onStop(value: VoidCallback | undefined): this {
        if (this.checkPriority("onStop")) {
            const value_casted = value as (VoidCallback | undefined)
            this.getPeer()?.setOnStopAttribute(value_casted)
            return this
        }
        return this
    }
    public enableAnalyzer(value: boolean | undefined): this {
        if (this.checkPriority("enableAnalyzer")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableAnalyzerAttribute(value_casted)
            return this
        }
        return this
    }
    public analyzerConfig(value: ImageAnalyzerConfig | undefined): this {
        if (this.checkPriority("analyzerConfig")) {
            hookVideoAnalyzerConfig(this, value)
        }
        return this
    }
    public enableShortcutKey(value: boolean | undefined): this {
        if (this.checkPriority("enableShortcutKey")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableShortcutKeyAttribute(value_casted)
            return this
        }
        return this
    }
    public surfaceBackgroundColor(value: ColorMetrics | undefined): this {
        if (this.checkPriority("surfaceBackgroundColor")) {
            const value_casted = value as (ColorMetrics | undefined)
            this.getPeer()?.setSurfaceBackgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<VideoAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        hookVideoAttributeModifier(this, value);
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

@memo
export function VideoImpl(
    @memo
    style: ((attributes: VideoAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkVideoComponent>((): ArkVideoComponent => {
        return new ArkVideoComponent()
    })
    NodeAttach<ArkVideoPeer>((): ArkVideoPeer => ArkVideoPeer.create(receiver), (peer: ArkVideoPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

export class FullscreenInfo_serializer {
    public static write(buffer: SerializerBase, value: FullscreenInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForFullscreen  = value.fullscreen
        valueSerializer.writeBoolean(valueHolderForFullscreen)
    }
    public static read(buffer: DeserializerBase): FullscreenInfo {
        let valueDeserializer : DeserializerBase = buffer
        const fullscreenTmpResult : boolean = valueDeserializer.readBoolean()
        let value : FullscreenInfo = ({fullscreen: fullscreenTmpResult} as FullscreenInfo)
        return value
    }
}
export class PlaybackInfo_serializer {
    public static write(buffer: SerializerBase, value: PlaybackInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTime  = value.time
        valueSerializer.writeInt32(valueHolderForTime)
    }
    public static read(buffer: DeserializerBase): PlaybackInfo {
        let valueDeserializer : DeserializerBase = buffer
        const timeTmpResult : int32 = valueDeserializer.readInt32()
        let value : PlaybackInfo = ({time: timeTmpResult} as PlaybackInfo)
        return value
    }
}
export class PreparedInfo_serializer {
    public static write(buffer: SerializerBase, value: PreparedInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForDuration  = value.duration
        valueSerializer.writeInt32(valueHolderForDuration)
    }
    public static read(buffer: DeserializerBase): PreparedInfo {
        let valueDeserializer : DeserializerBase = buffer
        const durationTmpResult : int32 = valueDeserializer.readInt32()
        let value : PreparedInfo = ({duration: durationTmpResult} as PreparedInfo)
        return value
    }
}
export class VideoController_serializer {
    public static write(buffer: SerializerBase, value: VideoController): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): VideoController {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return VideoControllerInternal.fromPtr(ptr)
    }
}
export class PosterOptions_serializer {
    public static write(buffer: SerializerBase, value: PosterOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForShowFirstFrame  = value.showFirstFrame
        if (valueHolderForShowFirstFrame !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForShowFirstFrameTmpValue  = valueHolderForShowFirstFrame!
            valueSerializer.writeBoolean(valueHolderForShowFirstFrameTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): PosterOptions {
        let valueDeserializer : DeserializerBase = buffer
        const showFirstFrameTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let showFirstFrameTmpBuf : boolean | undefined = undefined
        if ((showFirstFrameTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            showFirstFrameTmpBuf = valueDeserializer.readBoolean()
        }
        const showFirstFrameTmpResult : boolean | undefined = showFirstFrameTmpBuf
        let value : PosterOptions = ({showFirstFrame: showFirstFrameTmpResult} as PosterOptions)
        return value
    }
}
export class VideoOptions_serializer {
    public static write(buffer: SerializerBase, value: VideoOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForSrc  = value.src
        if (valueHolderForSrc !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSrcTmpValue  = valueHolderForSrc!
            if (valueHolderForSrcTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForSrcTmpValueForIdx0  = valueHolderForSrcTmpValue as string
                valueSerializer.writeString(valueHolderForSrcTmpValueForIdx0)
            } else if (valueHolderForSrcTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForSrcTmpValueForIdx1  = valueHolderForSrcTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForSrcTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForCurrentProgressRate  = value.currentProgressRate
        if (valueHolderForCurrentProgressRate !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCurrentProgressRateTmpValue  = valueHolderForCurrentProgressRate!
            if (valueHolderForCurrentProgressRateTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForCurrentProgressRateTmpValueForIdx0  = valueHolderForCurrentProgressRateTmpValue as double
                valueSerializer.writeFloat64(valueHolderForCurrentProgressRateTmpValueForIdx0)
            } else if (valueHolderForCurrentProgressRateTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForCurrentProgressRateTmpValueForIdx1  = valueHolderForCurrentProgressRateTmpValue as string
                valueSerializer.writeString(valueHolderForCurrentProgressRateTmpValueForIdx1)
            } else if (valueHolderForCurrentProgressRateTmpValue instanceof PlaybackSpeed) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForCurrentProgressRateTmpValueForIdx2  = valueHolderForCurrentProgressRateTmpValue as PlaybackSpeed
                valueSerializer.writeInt32(valueHolderForCurrentProgressRateTmpValueForIdx2.valueOf())
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForPreviewUri  = value.previewUri
        if (valueHolderForPreviewUri !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPreviewUriTmpValue  = valueHolderForPreviewUri!
            if (valueHolderForPreviewUriTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForPreviewUriTmpValueForIdx0  = valueHolderForPreviewUriTmpValue as string
                valueSerializer.writeString(valueHolderForPreviewUriTmpValueForIdx0)
            } else if (valueHolderForPreviewUriTmpValue instanceof image.PixelMap) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForPreviewUriTmpValueForIdx1  = valueHolderForPreviewUriTmpValue as image.PixelMap
                image_PixelMap_serializer.write(valueSerializer, valueHolderForPreviewUriTmpValueForIdx1)
            } else if (valueHolderForPreviewUriTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForPreviewUriTmpValueForIdx2  = valueHolderForPreviewUriTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForPreviewUriTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForController  = value.controller
        if (valueHolderForController !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForControllerTmpValue  = valueHolderForController!
            VideoController_serializer.write(valueSerializer, valueHolderForControllerTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForImageAIOptions  = value.imageAIOptions
        if (valueHolderForImageAIOptions !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForImageAIOptionsTmpValue  = valueHolderForImageAIOptions!
            ImageAIOptions_serializer.write(valueSerializer, valueHolderForImageAIOptionsTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForPosterOptions  = value.posterOptions
        if (valueHolderForPosterOptions !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPosterOptionsTmpValue  = valueHolderForPosterOptions!
            PosterOptions_serializer.write(valueSerializer, valueHolderForPosterOptionsTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): VideoOptions {
        let valueDeserializer : DeserializerBase = buffer
        const srcTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let srcTmpBuf : string | Resource | undefined = undefined
        if ((srcTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const srcTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let srcTmpBuf_ : string | Resource | undefined
            if (srcTmpBuf_UnionSelector == (0).toChar()) {
                srcTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (srcTmpBuf_UnionSelector == (1).toChar()) {
                srcTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for srcTmpBuf_ has to be chosen through deserialisation.")
            }
            srcTmpBuf = (srcTmpBuf_ as string | Resource)
        }
        const srcTmpResult : string | Resource | undefined = srcTmpBuf
        const currentProgressRateTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let currentProgressRateTmpBuf : double | string | PlaybackSpeed | undefined = undefined
        if ((currentProgressRateTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const currentProgressRateTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let currentProgressRateTmpBuf_ : double | string | PlaybackSpeed | undefined
            if (currentProgressRateTmpBuf_UnionSelector == (0).toChar()) {
                currentProgressRateTmpBuf_ = valueDeserializer.readFloat64()
            } else if (currentProgressRateTmpBuf_UnionSelector == (1).toChar()) {
                currentProgressRateTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (currentProgressRateTmpBuf_UnionSelector == (2).toChar()) {
                currentProgressRateTmpBuf_ = PlaybackSpeed.fromValue(valueDeserializer.readInt32())
            } else {
                throw new Error("One of the branches for currentProgressRateTmpBuf_ has to be chosen through deserialisation.")
            }
            currentProgressRateTmpBuf = (currentProgressRateTmpBuf_ as double | string | PlaybackSpeed)
        }
        const currentProgressRateTmpResult : double | string | PlaybackSpeed | undefined = currentProgressRateTmpBuf
        const previewUriTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let previewUriTmpBuf : string | image.PixelMap | Resource | undefined = undefined
        if ((previewUriTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const previewUriTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let previewUriTmpBuf_ : string | image.PixelMap | Resource | undefined
            if (previewUriTmpBuf_UnionSelector == (0).toChar()) {
                previewUriTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (previewUriTmpBuf_UnionSelector == (1).toChar()) {
                previewUriTmpBuf_ = (image_PixelMap_serializer.read(valueDeserializer) as image.PixelMap)
            } else if (previewUriTmpBuf_UnionSelector == (2).toChar()) {
                previewUriTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for previewUriTmpBuf_ has to be chosen through deserialisation.")
            }
            previewUriTmpBuf = (previewUriTmpBuf_ as string | image.PixelMap | Resource)
        }
        const previewUriTmpResult : string | image.PixelMap | Resource | undefined = previewUriTmpBuf
        const controllerTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let controllerTmpBuf : VideoController | undefined = undefined
        if ((controllerTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            controllerTmpBuf = (VideoController_serializer.read(valueDeserializer) as VideoController)
        }
        const controllerTmpResult : VideoController | undefined = controllerTmpBuf
        const imageAIOptionsTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let imageAIOptionsTmpBuf : ImageAIOptions | undefined = undefined
        if ((imageAIOptionsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            imageAIOptionsTmpBuf = ImageAIOptions_serializer.read(valueDeserializer)
        }
        const imageAIOptionsTmpResult : ImageAIOptions | undefined = imageAIOptionsTmpBuf
        const posterOptionsTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let posterOptionsTmpBuf : PosterOptions | undefined = undefined
        if ((posterOptionsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            posterOptionsTmpBuf = PosterOptions_serializer.read(valueDeserializer)
        }
        const posterOptionsTmpResult : PosterOptions | undefined = posterOptionsTmpBuf
        let value : VideoOptions = ({src: srcTmpResult, currentProgressRate: currentProgressRateTmpResult, previewUri: previewUriTmpResult, controller: controllerTmpResult, imageAIOptions: imageAIOptionsTmpResult, posterOptions: posterOptionsTmpResult} as VideoOptions)
        return value
    }
}
