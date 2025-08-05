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
import { ImageAnalyzerConfig_serializer, ImageAnalyzerConfig, ImageAIOptions, ImageAIOptions_serializer } from "./imageCommon"
import { ColorMetrics_serializer, ColorMetrics } from "./../generated/arkui.Graphics"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethodModifier } from "./common"
import { ImageFit } from "./enums"
import { VoidCallback } from "./units"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { Resource, Resource_serializer } from "./../generated/resource"
import { image, image_PixelMap_serializer } from "./../generated/ohos.multimedia.image"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
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
    public setCurrentTime(value: number): void {
        const value_casted = value as (number)
        this.setCurrentTime0_serialize(value_casted)
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
    public setCurrentTime(value: number, seekMode: SeekMode): void {
        const value_casted = value as (number)
        const seekMode_casted = seekMode as (SeekMode)
        this.setCurrentTime1_serialize(value_casted, seekMode_casted)
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
    private requestFullscreen_serialize(value: boolean): void {
        ArkUIGeneratedNativeModule._VideoController_requestFullscreen(this.peer!.ptr, value ? 1 : 0)
    }
    private exitFullscreen_serialize(): void {
        ArkUIGeneratedNativeModule._VideoController_exitFullscreen(this.peer!.ptr)
    }
    private setCurrentTime1_serialize(value: number, seekMode: SeekMode): void {
        ArkUIGeneratedNativeModule._VideoController_setCurrentTime1(this.peer!.ptr, value, TypeChecker.SeekMode_ToNumeric(seekMode))
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
            thisSerializer.writeInt32(TypeChecker.ImageFit_ToNumeric(valueTmpValue))
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
    setOnErrorAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_setOnError(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnStopAttribute(value: (() => void) | undefined): void {
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
    previewUri?: string | image.PixelMap | Resource;
    controller?: VideoController;
    imageAIOptions?: ImageAIOptions;
    posterOptions?: PosterOptions;
}
export interface VideoAttribute extends CommonMethod {
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
    onError(value: (() => void) | undefined): this {
        throw new Error("Unimplemented method onError")
    }
    onStop(value: (() => void) | undefined): this {
        throw new Error("Unimplemented method onStop")
    }
    enableAnalyzer(value: boolean | undefined): this {
        throw new Error("Unimplemented method enableAnalyzer")
    }
    analyzerConfig(value: ImageAnalyzerConfig | undefined): this {
        throw new Error("Unimplemented method analyzerConfig")
    }
    surfaceBackgroundColor(value: ColorMetrics | undefined): this {
        throw new Error("Unimplemented method surfaceBackgroundColor")
    }
    enableShortcutKey(value: boolean | undefined): this {
        throw new Error("Unimplemented method enableShortcutKey")
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
    onError_value?: (() => void) | undefined
    onStop_value?: (() => void) | undefined
    enableAnalyzer_value?: boolean | undefined
    analyzerConfig_value?: ImageAnalyzerConfig | undefined
    surfaceBackgroundColor_value?: ColorMetrics | undefined
    enableShortcutKey_value?: boolean | undefined
    attributeModifier_value?: AttributeModifier<VideoAttribute> | AttributeModifier<CommonMethod> | undefined
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
    public onFullscreenChange(value: ((value0: FullscreenInfo) => void) | undefined): this {
        return this
    }
    public onPrepared(value: ((value0: PreparedInfo) => void) | undefined): this {
        return this
    }
    public onSeeking(value: ((value0: PlaybackInfo) => void) | undefined): this {
        return this
    }
    public onSeeked(value: ((value0: PlaybackInfo) => void) | undefined): this {
        return this
    }
    public onUpdate(value: ((value0: PlaybackInfo) => void) | undefined): this {
        return this
    }
    public onError(value: (() => void) | undefined): this {
        return this
    }
    public onStop(value: (() => void) | undefined): this {
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
    public attributeModifier(value: AttributeModifier<VideoAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
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
    public onError(value: (() => void) | undefined): this {
        if (this.checkPriority("onError")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.setOnErrorAttribute(value_casted)
            return this
        }
        return this
    }
    public onStop(value: (() => void) | undefined): this {
        if (this.checkPriority("onStop")) {
            const value_casted = value as ((() => void) | undefined)
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
            const value_casted = value as (ImageAnalyzerConfig | undefined)
            this.getPeer()?.setAnalyzerConfigAttribute(value_casted)
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
    public enableShortcutKey(value: boolean | undefined): this {
        if (this.checkPriority("enableShortcutKey")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableShortcutKeyAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<VideoAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

@memo
export function Video(
    @memo
    style: ((attributes: VideoAttribute) => void) | undefined,
    value: VideoOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkVideoComponent>((): ArkVideoComponent => {
        return new ArkVideoComponent()
    })
    NodeAttach<ArkVideoPeer>((): ArkVideoPeer => ArkVideoPeer.create(receiver), (_: ArkVideoPeer): void => {
        receiver.setVideoOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class VideoModifier extends CommonMethodModifier implements VideoAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _muted_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _muted_0_0value?: boolean | undefined
    _autoPlay_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _autoPlay_0_0value?: boolean | undefined
    _controls_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _controls_0_0value?: boolean | undefined
    _loop_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _loop_0_0value?: boolean | undefined
    _objectFit_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _objectFit_0_0value?: ImageFit | undefined
    _onStart_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onStart_0_0value?: VoidCallback | undefined
    _onPause_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onPause_0_0value?: VoidCallback | undefined
    _onFinish_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onFinish_0_0value?: VoidCallback | undefined
    _onFullscreenChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onFullscreenChange_0_0value?: ((value0: FullscreenInfo) => void) | undefined
    _onPrepared_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onPrepared_0_0value?: ((value0: PreparedInfo) => void) | undefined
    _onSeeking_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onSeeking_0_0value?: ((value0: PlaybackInfo) => void) | undefined
    _onSeeked_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onSeeked_0_0value?: ((value0: PlaybackInfo) => void) | undefined
    _onUpdate_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onUpdate_0_0value?: ((value0: PlaybackInfo) => void) | undefined
    _onError_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onError_0_0value?: (() => void) | undefined
    _onStop_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onStop_0_0value?: (() => void) | undefined
    _enableAnalyzer_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableAnalyzer_0_0value?: boolean | undefined
    _analyzerConfig_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _analyzerConfig_0_0value?: ImageAnalyzerConfig | undefined
    _surfaceBackgroundColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _surfaceBackgroundColor_0_0value?: ColorMetrics | undefined
    _enableShortcutKey_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableShortcutKey_0_0value?: boolean | undefined
    applyModifierPatch(peer: ArkVideoPeer): void {
        super.applyModifierPatch(peer)
        if (this._muted_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._muted_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMutedAttribute((this._muted_0_0value as boolean | undefined));
                    this._muted_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._muted_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._muted_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMutedAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._autoPlay_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._autoPlay_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAutoPlayAttribute((this._autoPlay_0_0value as boolean | undefined));
                    this._autoPlay_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._autoPlay_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._autoPlay_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAutoPlayAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._controls_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._controls_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setControlsAttribute((this._controls_0_0value as boolean | undefined));
                    this._controls_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._controls_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._controls_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setControlsAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._loop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._loop_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setLoopAttribute((this._loop_0_0value as boolean | undefined));
                    this._loop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._loop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._loop_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setLoopAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._objectFit_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._objectFit_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setObjectFitAttribute((this._objectFit_0_0value as ImageFit | undefined));
                    this._objectFit_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._objectFit_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._objectFit_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setObjectFitAttribute((undefined as ImageFit | undefined));
                }
            }
        }
        if (this._onStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnStartAttribute((this._onStart_0_0value as VoidCallback | undefined));
                    this._onStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onStart_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnStartAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (this._onPause_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onPause_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnPauseAttribute((this._onPause_0_0value as VoidCallback | undefined));
                    this._onPause_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onPause_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onPause_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnPauseAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (this._onFinish_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onFinish_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnFinishAttribute((this._onFinish_0_0value as VoidCallback | undefined));
                    this._onFinish_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onFinish_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onFinish_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnFinishAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (this._onFullscreenChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onFullscreenChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnFullscreenChangeAttribute((this._onFullscreenChange_0_0value as ((value0: FullscreenInfo) => void) | undefined));
                    this._onFullscreenChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onFullscreenChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onFullscreenChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnFullscreenChangeAttribute((undefined as ((value0: FullscreenInfo) => void) | undefined));
                }
            }
        }
        if (this._onPrepared_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onPrepared_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnPreparedAttribute((this._onPrepared_0_0value as ((value0: PreparedInfo) => void) | undefined));
                    this._onPrepared_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onPrepared_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onPrepared_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnPreparedAttribute((undefined as ((value0: PreparedInfo) => void) | undefined));
                }
            }
        }
        if (this._onSeeking_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onSeeking_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnSeekingAttribute((this._onSeeking_0_0value as ((value0: PlaybackInfo) => void) | undefined));
                    this._onSeeking_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onSeeking_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onSeeking_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnSeekingAttribute((undefined as ((value0: PlaybackInfo) => void) | undefined));
                }
            }
        }
        if (this._onSeeked_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onSeeked_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnSeekedAttribute((this._onSeeked_0_0value as ((value0: PlaybackInfo) => void) | undefined));
                    this._onSeeked_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onSeeked_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onSeeked_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnSeekedAttribute((undefined as ((value0: PlaybackInfo) => void) | undefined));
                }
            }
        }
        if (this._onUpdate_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onUpdate_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnUpdateAttribute((this._onUpdate_0_0value as ((value0: PlaybackInfo) => void) | undefined));
                    this._onUpdate_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onUpdate_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onUpdate_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnUpdateAttribute((undefined as ((value0: PlaybackInfo) => void) | undefined));
                }
            }
        }
        if (this._onError_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onError_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnErrorAttribute((this._onError_0_0value as (() => void) | undefined));
                    this._onError_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onError_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onError_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnErrorAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onStop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onStop_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnStopAttribute((this._onStop_0_0value as (() => void) | undefined));
                    this._onStop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onStop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onStop_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnStopAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._enableAnalyzer_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableAnalyzer_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableAnalyzerAttribute((this._enableAnalyzer_0_0value as boolean | undefined));
                    this._enableAnalyzer_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableAnalyzer_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableAnalyzer_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableAnalyzerAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._analyzerConfig_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._analyzerConfig_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAnalyzerConfigAttribute((this._analyzerConfig_0_0value as ImageAnalyzerConfig | undefined));
                    this._analyzerConfig_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._analyzerConfig_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._analyzerConfig_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAnalyzerConfigAttribute((undefined as ImageAnalyzerConfig | undefined));
                }
            }
        }
        if (this._surfaceBackgroundColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._surfaceBackgroundColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSurfaceBackgroundColorAttribute((this._surfaceBackgroundColor_0_0value as ColorMetrics | undefined));
                    this._surfaceBackgroundColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._surfaceBackgroundColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._surfaceBackgroundColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSurfaceBackgroundColorAttribute((undefined as ColorMetrics | undefined));
                }
            }
        }
        if (this._enableShortcutKey_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableShortcutKey_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableShortcutKeyAttribute((this._enableShortcutKey_0_0value as boolean | undefined));
                    this._enableShortcutKey_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableShortcutKey_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableShortcutKey_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableShortcutKeyAttribute((undefined as boolean | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: VideoModifier): void {
        super.mergeModifier(modifier)
        if (modifier._muted_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._muted_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.muted(modifier._muted_0_0value);
                    break;
                }
                default: {
                    this.muted((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._autoPlay_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._autoPlay_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.autoPlay(modifier._autoPlay_0_0value);
                    break;
                }
                default: {
                    this.autoPlay((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._controls_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._controls_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.controls(modifier._controls_0_0value);
                    break;
                }
                default: {
                    this.controls((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._loop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._loop_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.loop(modifier._loop_0_0value);
                    break;
                }
                default: {
                    this.loop((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._objectFit_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._objectFit_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.objectFit(modifier._objectFit_0_0value);
                    break;
                }
                default: {
                    this.objectFit((undefined as ImageFit | undefined));
                }
            }
        }
        if (modifier._onStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onStart(modifier._onStart_0_0value);
                    break;
                }
                default: {
                    this.onStart((undefined as VoidCallback | undefined));
                }
            }
        }
        if (modifier._onPause_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onPause_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onPause(modifier._onPause_0_0value);
                    break;
                }
                default: {
                    this.onPause((undefined as VoidCallback | undefined));
                }
            }
        }
        if (modifier._onFinish_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onFinish_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onFinish(modifier._onFinish_0_0value);
                    break;
                }
                default: {
                    this.onFinish((undefined as VoidCallback | undefined));
                }
            }
        }
        if (modifier._onFullscreenChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onFullscreenChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onFullscreenChange(modifier._onFullscreenChange_0_0value);
                    break;
                }
                default: {
                    this.onFullscreenChange((undefined as ((value0: FullscreenInfo) => void) | undefined));
                }
            }
        }
        if (modifier._onPrepared_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onPrepared_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onPrepared(modifier._onPrepared_0_0value);
                    break;
                }
                default: {
                    this.onPrepared((undefined as ((value0: PreparedInfo) => void) | undefined));
                }
            }
        }
        if (modifier._onSeeking_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onSeeking_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onSeeking(modifier._onSeeking_0_0value);
                    break;
                }
                default: {
                    this.onSeeking((undefined as ((value0: PlaybackInfo) => void) | undefined));
                }
            }
        }
        if (modifier._onSeeked_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onSeeked_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onSeeked(modifier._onSeeked_0_0value);
                    break;
                }
                default: {
                    this.onSeeked((undefined as ((value0: PlaybackInfo) => void) | undefined));
                }
            }
        }
        if (modifier._onUpdate_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onUpdate_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onUpdate(modifier._onUpdate_0_0value);
                    break;
                }
                default: {
                    this.onUpdate((undefined as ((value0: PlaybackInfo) => void) | undefined));
                }
            }
        }
        if (modifier._onError_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onError_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onError(modifier._onError_0_0value);
                    break;
                }
                default: {
                    this.onError((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onStop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onStop_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onStop(modifier._onStop_0_0value);
                    break;
                }
                default: {
                    this.onStop((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._enableAnalyzer_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableAnalyzer_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableAnalyzer(modifier._enableAnalyzer_0_0value);
                    break;
                }
                default: {
                    this.enableAnalyzer((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._analyzerConfig_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._analyzerConfig_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.analyzerConfig(modifier._analyzerConfig_0_0value);
                    break;
                }
                default: {
                    this.analyzerConfig((undefined as ImageAnalyzerConfig | undefined));
                }
            }
        }
        if (modifier._surfaceBackgroundColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._surfaceBackgroundColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.surfaceBackgroundColor(modifier._surfaceBackgroundColor_0_0value);
                    break;
                }
                default: {
                    this.surfaceBackgroundColor((undefined as ColorMetrics | undefined));
                }
            }
        }
        if (modifier._enableShortcutKey_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableShortcutKey_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableShortcutKey(modifier._enableShortcutKey_0_0value);
                    break;
                }
                default: {
                    this.enableShortcutKey((undefined as boolean | undefined));
                }
            }
        }
    }
    muted(value: boolean | undefined): this {
        if (((this._muted_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._muted_0_0value) !== (value)))
        {
            this._muted_0_flag = AttributeUpdaterFlag.UPDATE
            this._muted_0_0value = value
        } else
        {
            this._muted_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    autoPlay(value: boolean | undefined): this {
        if (((this._autoPlay_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._autoPlay_0_0value) !== (value)))
        {
            this._autoPlay_0_flag = AttributeUpdaterFlag.UPDATE
            this._autoPlay_0_0value = value
        } else
        {
            this._autoPlay_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    controls(value: boolean | undefined): this {
        if (((this._controls_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._controls_0_0value) !== (value)))
        {
            this._controls_0_flag = AttributeUpdaterFlag.UPDATE
            this._controls_0_0value = value
        } else
        {
            this._controls_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    loop(value: boolean | undefined): this {
        if (((this._loop_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._loop_0_0value) !== (value)))
        {
            this._loop_0_flag = AttributeUpdaterFlag.UPDATE
            this._loop_0_0value = value
        } else
        {
            this._loop_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    objectFit(value: ImageFit | undefined): this {
        if (((this._objectFit_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._objectFit_0_flag = AttributeUpdaterFlag.UPDATE
            this._objectFit_0_0value = value
        } else
        {
            this._objectFit_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onStart(value: VoidCallback | undefined): this {
        if (((this._onStart_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onStart_0_flag = AttributeUpdaterFlag.UPDATE
            this._onStart_0_0value = value
        } else
        {
            this._onStart_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onPause(value: VoidCallback | undefined): this {
        if (((this._onPause_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onPause_0_flag = AttributeUpdaterFlag.UPDATE
            this._onPause_0_0value = value
        } else
        {
            this._onPause_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onFinish(value: VoidCallback | undefined): this {
        if (((this._onFinish_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onFinish_0_flag = AttributeUpdaterFlag.UPDATE
            this._onFinish_0_0value = value
        } else
        {
            this._onFinish_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onFullscreenChange(value: ((value0: FullscreenInfo) => void) | undefined): this {
        if (((this._onFullscreenChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onFullscreenChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onFullscreenChange_0_0value = value
        } else
        {
            this._onFullscreenChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onPrepared(value: ((value0: PreparedInfo) => void) | undefined): this {
        if (((this._onPrepared_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onPrepared_0_flag = AttributeUpdaterFlag.UPDATE
            this._onPrepared_0_0value = value
        } else
        {
            this._onPrepared_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onSeeking(value: ((value0: PlaybackInfo) => void) | undefined): this {
        if (((this._onSeeking_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onSeeking_0_flag = AttributeUpdaterFlag.UPDATE
            this._onSeeking_0_0value = value
        } else
        {
            this._onSeeking_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onSeeked(value: ((value0: PlaybackInfo) => void) | undefined): this {
        if (((this._onSeeked_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onSeeked_0_flag = AttributeUpdaterFlag.UPDATE
            this._onSeeked_0_0value = value
        } else
        {
            this._onSeeked_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onUpdate(value: ((value0: PlaybackInfo) => void) | undefined): this {
        if (((this._onUpdate_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onUpdate_0_flag = AttributeUpdaterFlag.UPDATE
            this._onUpdate_0_0value = value
        } else
        {
            this._onUpdate_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onError(value: (() => void) | undefined): this {
        if (((this._onError_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onError_0_flag = AttributeUpdaterFlag.UPDATE
            this._onError_0_0value = value
        } else
        {
            this._onError_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onStop(value: (() => void) | undefined): this {
        if (((this._onStop_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onStop_0_flag = AttributeUpdaterFlag.UPDATE
            this._onStop_0_0value = value
        } else
        {
            this._onStop_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableAnalyzer(value: boolean | undefined): this {
        if (((this._enableAnalyzer_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableAnalyzer_0_0value) !== (value)))
        {
            this._enableAnalyzer_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableAnalyzer_0_0value = value
        } else
        {
            this._enableAnalyzer_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    analyzerConfig(value: ImageAnalyzerConfig | undefined): this {
        if (((this._analyzerConfig_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._analyzerConfig_0_flag = AttributeUpdaterFlag.UPDATE
            this._analyzerConfig_0_0value = value
        } else
        {
            this._analyzerConfig_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    surfaceBackgroundColor(value: ColorMetrics | undefined): this {
        if (((this._surfaceBackgroundColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._surfaceBackgroundColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._surfaceBackgroundColor_0_0value = value
        } else
        {
            this._surfaceBackgroundColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableShortcutKey(value: boolean | undefined): this {
        if (((this._enableShortcutKey_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableShortcutKey_0_0value) !== (value)))
        {
            this._enableShortcutKey_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableShortcutKey_0_0value = value
        } else
        {
            this._enableShortcutKey_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<VideoAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
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
        valueSerializer.writeNumber(valueHolderForTime)
    }
    public static read(buffer: DeserializerBase): PlaybackInfo {
        let valueDeserializer : DeserializerBase = buffer
        const timeTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : PlaybackInfo = ({time: timeTmpResult} as PlaybackInfo)
        return value
    }
}
export class PreparedInfo_serializer {
    public static write(buffer: SerializerBase, value: PreparedInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForDuration  = value.duration
        valueSerializer.writeNumber(valueHolderForDuration)
    }
    public static read(buffer: DeserializerBase): PreparedInfo {
        let valueDeserializer : DeserializerBase = buffer
        const durationTmpResult : number = (valueDeserializer.readNumber() as number)
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
        let showFirstFrameTmpBuf : boolean | undefined
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
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForSrcTmpValueForIdx0  = valueHolderForSrcTmpValue as string
                valueSerializer.writeString(valueHolderForSrcTmpValueForIdx0)
            } else if (valueHolderForSrcTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toChar())
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
            if (valueHolderForCurrentProgressRateTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForCurrentProgressRateTmpValueForIdx0  = valueHolderForCurrentProgressRateTmpValue as number
                valueSerializer.writeNumber(valueHolderForCurrentProgressRateTmpValueForIdx0)
            } else if (valueHolderForCurrentProgressRateTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForCurrentProgressRateTmpValueForIdx1  = valueHolderForCurrentProgressRateTmpValue as string
                valueSerializer.writeString(valueHolderForCurrentProgressRateTmpValueForIdx1)
            } else if (valueHolderForCurrentProgressRateTmpValue instanceof PlaybackSpeed) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderForCurrentProgressRateTmpValueForIdx2  = valueHolderForCurrentProgressRateTmpValue as PlaybackSpeed
                valueSerializer.writeInt32(TypeChecker.PlaybackSpeed_ToNumeric(valueHolderForCurrentProgressRateTmpValueForIdx2))
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForPreviewUri  = value.previewUri
        if (valueHolderForPreviewUri !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPreviewUriTmpValue  = valueHolderForPreviewUri!
            if (valueHolderForPreviewUriTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForPreviewUriTmpValueForIdx0  = valueHolderForPreviewUriTmpValue as string
                valueSerializer.writeString(valueHolderForPreviewUriTmpValueForIdx0)
            } else if (valueHolderForPreviewUriTmpValue instanceof image.PixelMap) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForPreviewUriTmpValueForIdx1  = valueHolderForPreviewUriTmpValue as image.PixelMap
                image_PixelMap_serializer.write(valueSerializer, valueHolderForPreviewUriTmpValueForIdx1)
            } else if (valueHolderForPreviewUriTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toChar())
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
        let srcTmpBuf : string | Resource | undefined
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
        let currentProgressRateTmpBuf : number | string | PlaybackSpeed | undefined
        if ((currentProgressRateTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const currentProgressRateTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let currentProgressRateTmpBuf_ : number | string | PlaybackSpeed | undefined
            if (currentProgressRateTmpBuf_UnionSelector == (0).toChar()) {
                currentProgressRateTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (currentProgressRateTmpBuf_UnionSelector == (1).toChar()) {
                currentProgressRateTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (currentProgressRateTmpBuf_UnionSelector == (2).toChar()) {
                currentProgressRateTmpBuf_ = TypeChecker.PlaybackSpeed_FromNumeric(valueDeserializer.readInt32())
            } else {
                throw new Error("One of the branches for currentProgressRateTmpBuf_ has to be chosen through deserialisation.")
            }
            currentProgressRateTmpBuf = (currentProgressRateTmpBuf_ as number | string | PlaybackSpeed)
        }
        const currentProgressRateTmpResult : number | string | PlaybackSpeed | undefined = currentProgressRateTmpBuf
        const previewUriTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let previewUriTmpBuf : string | image.PixelMap | Resource | undefined
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
        let controllerTmpBuf : VideoController | undefined
        if ((controllerTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            controllerTmpBuf = (VideoController_serializer.read(valueDeserializer) as VideoController)
        }
        const controllerTmpResult : VideoController | undefined = controllerTmpBuf
        const imageAIOptionsTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let imageAIOptionsTmpBuf : ImageAIOptions | undefined
        if ((imageAIOptionsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            imageAIOptionsTmpBuf = ImageAIOptions_serializer.read(valueDeserializer)
        }
        const imageAIOptionsTmpResult : ImageAIOptions | undefined = imageAIOptionsTmpBuf
        const posterOptionsTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let posterOptionsTmpBuf : PosterOptions | undefined
        if ((posterOptionsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            posterOptionsTmpBuf = PosterOptions_serializer.read(valueDeserializer)
        }
        const posterOptionsTmpResult : PosterOptions | undefined = posterOptionsTmpBuf
        let value : VideoOptions = ({src: srcTmpResult, currentProgressRate: currentProgressRateTmpResult, previewUri: previewUriTmpResult, controller: controllerTmpResult, imageAIOptions: imageAIOptionsTmpResult, posterOptions: posterOptionsTmpResult} as VideoOptions)
        return value
    }
}
