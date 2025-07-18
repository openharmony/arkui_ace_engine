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
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, DeserializerBase, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { ImageAnalyzerConfig_serializer, ImageAnalyzerConfig, ImageAIOptions, ImageAIOptions_serializer } from "./imageCommon"
import { ColorMetrics_serializer, ColorMetrics } from "./../generated/arkui.Graphics"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { ImageFit } from "./enums"
import { VoidCallback } from "./units"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { Resource, Resource_serializer } from "./../generated/resource"
import { image, image_PixelMap_serializer } from "./../generated/ohos.multimedia.image"
import { NodeAttach, remember } from "@koalaui/runtime"
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
        const _peer  = new ArkVideoPeer(_peerPtr, peerId, "Video", flags)
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
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_setMuted(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAutoPlayAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_setAutoPlay(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setControlsAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_setControls(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLoopAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_setLoop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setObjectFitAttribute(value: ImageFit | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as ImageFit)
            thisSerializer.writeInt32(TypeChecker.ImageFit_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._VideoAttribute_setObjectFit(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnStartAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_setOnStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnPauseAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_setOnPause(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnFinishAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_setOnFinish(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnFullscreenChangeAttribute(value: ((value0: FullscreenInfo) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_setOnFullscreenChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnPreparedAttribute(value: ((value0: PreparedInfo) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_setOnPrepared(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnSeekingAttribute(value: ((value0: PlaybackInfo) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_setOnSeeking(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnSeekedAttribute(value: ((value0: PlaybackInfo) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_setOnSeeked(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnUpdateAttribute(value: ((value0: PlaybackInfo) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_setOnUpdate(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnErrorAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_setOnError(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnStopAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_setOnStop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableAnalyzerAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_setEnableAnalyzer(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAnalyzerConfigAttribute(value: ImageAnalyzerConfig | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            ImageAnalyzerConfig_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_setAnalyzerConfig(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSurfaceBackgroundColorAttribute(value: ColorMetrics | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            ColorMetrics_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._VideoAttribute_setSurfaceBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableShortcutKeyAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
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
    public apply(target: VideoAttribute): void {
        super.apply(target)
        if (this.muted_value !== undefined)
            target.muted(this.muted_value!)
        if (this.autoPlay_value !== undefined)
            target.autoPlay(this.autoPlay_value!)
        if (this.controls_value !== undefined)
            target.controls(this.controls_value!)
        if (this.loop_value !== undefined)
            target.loop(this.loop_value!)
        if (this.objectFit_value !== undefined)
            target.objectFit(this.objectFit_value!)
        if (this.onStart_value !== undefined)
            target.onStart(this.onStart_value!)
        if (this.onPause_value !== undefined)
            target.onPause(this.onPause_value!)
        if (this.onFinish_value !== undefined)
            target.onFinish(this.onFinish_value!)
        if (this.onFullscreenChange_value !== undefined)
            target.onFullscreenChange(this.onFullscreenChange_value!)
        if (this.onPrepared_value !== undefined)
            target.onPrepared(this.onPrepared_value!)
        if (this.onSeeking_value !== undefined)
            target.onSeeking(this.onSeeking_value!)
        if (this.onSeeked_value !== undefined)
            target.onSeeked(this.onSeeked_value!)
        if (this.onUpdate_value !== undefined)
            target.onUpdate(this.onUpdate_value!)
        if (this.onError_value !== undefined)
            target.onError(this.onError_value!)
        if (this.onStop_value !== undefined)
            target.onStop(this.onStop_value!)
        if (this.enableAnalyzer_value !== undefined)
            target.enableAnalyzer(this.enableAnalyzer_value!)
        if (this.analyzerConfig_value !== undefined)
            target.analyzerConfig(this.analyzerConfig_value!)
        if (this.surfaceBackgroundColor_value !== undefined)
            target.surfaceBackgroundColor(this.surfaceBackgroundColor_value!)
        if (this.enableShortcutKey_value !== undefined)
            target.enableShortcutKey(this.enableShortcutKey_value!)
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
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withVideoStyle(receiver: VideoAttribute, modifier: AttributeModifier<VideoAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkVideoStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("Video")
// export function Video(
//     value: VideoOptions,
//     @memo
//     content_?: () => void,
// ): VideoAttribute {
//     throw new Error("Not implemented")
// }

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
        withVideoStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkVideoSet extends ArkCommonMethodSet implements VideoAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _muted_flag?: boolean
    _muted0_value?: boolean | undefined
    _autoPlay_flag?: boolean
    _autoPlay0_value?: boolean | undefined
    _controls_flag?: boolean
    _controls0_value?: boolean | undefined
    _loop_flag?: boolean
    _loop0_value?: boolean | undefined
    _objectFit_flag?: boolean
    _objectFit0_value?: ImageFit | undefined
    _onStart_flag?: boolean
    _onStart0_value?: VoidCallback | undefined
    _onPause_flag?: boolean
    _onPause0_value?: VoidCallback | undefined
    _onFinish_flag?: boolean
    _onFinish0_value?: VoidCallback | undefined
    _onFullscreenChange_flag?: boolean
    _onFullscreenChange0_value?: ((value0: FullscreenInfo) => void) | undefined
    _onPrepared_flag?: boolean
    _onPrepared0_value?: ((value0: PreparedInfo) => void) | undefined
    _onSeeking_flag?: boolean
    _onSeeking0_value?: ((value0: PlaybackInfo) => void) | undefined
    _onSeeked_flag?: boolean
    _onSeeked0_value?: ((value0: PlaybackInfo) => void) | undefined
    _onUpdate_flag?: boolean
    _onUpdate0_value?: ((value0: PlaybackInfo) => void) | undefined
    _onError_flag?: boolean
    _onError0_value?: (() => void) | undefined
    _onStop_flag?: boolean
    _onStop0_value?: (() => void) | undefined
    _enableAnalyzer_flag?: boolean
    _enableAnalyzer0_value?: boolean | undefined
    _analyzerConfig_flag?: boolean
    _analyzerConfig0_value?: ImageAnalyzerConfig | undefined
    _surfaceBackgroundColor_flag?: boolean
    _surfaceBackgroundColor0_value?: ColorMetrics | undefined
    _enableShortcutKey_flag?: boolean
    _enableShortcutKey0_value?: boolean | undefined
    applyModifierPatch(component: VideoAttribute): void {
        if (this._muted_flag)
            component.muted((this._muted0_value as boolean | undefined))
        if (this._autoPlay_flag)
            component.autoPlay((this._autoPlay0_value as boolean | undefined))
        if (this._controls_flag)
            component.controls((this._controls0_value as boolean | undefined))
        if (this._loop_flag)
            component.loop((this._loop0_value as boolean | undefined))
        if (this._objectFit_flag)
            component.objectFit((this._objectFit0_value as ImageFit | undefined))
        if (this._onStart_flag)
            component.onStart((this._onStart0_value as VoidCallback | undefined))
        if (this._onPause_flag)
            component.onPause((this._onPause0_value as VoidCallback | undefined))
        if (this._onFinish_flag)
            component.onFinish((this._onFinish0_value as VoidCallback | undefined))
        if (this._onFullscreenChange_flag)
            component.onFullscreenChange((this._onFullscreenChange0_value as ((value0: FullscreenInfo) => void) | undefined))
        if (this._onPrepared_flag)
            component.onPrepared((this._onPrepared0_value as ((value0: PreparedInfo) => void) | undefined))
        if (this._onSeeking_flag)
            component.onSeeking((this._onSeeking0_value as ((value0: PlaybackInfo) => void) | undefined))
        if (this._onSeeked_flag)
            component.onSeeked((this._onSeeked0_value as ((value0: PlaybackInfo) => void) | undefined))
        if (this._onUpdate_flag)
            component.onUpdate((this._onUpdate0_value as ((value0: PlaybackInfo) => void) | undefined))
        if (this._onError_flag)
            component.onError((this._onError0_value as (() => void) | undefined))
        if (this._onStop_flag)
            component.onStop((this._onStop0_value as (() => void) | undefined))
        if (this._enableAnalyzer_flag)
            component.enableAnalyzer((this._enableAnalyzer0_value as boolean | undefined))
        if (this._analyzerConfig_flag)
            component.analyzerConfig((this._analyzerConfig0_value as ImageAnalyzerConfig | undefined))
        if (this._surfaceBackgroundColor_flag)
            component.surfaceBackgroundColor((this._surfaceBackgroundColor0_value as ColorMetrics | undefined))
        if (this._enableShortcutKey_flag)
            component.enableShortcutKey((this._enableShortcutKey0_value as boolean | undefined))
    }
    public muted(value: boolean | undefined): this {
        this._muted_flag = true
        this._muted0_value = value
        return this
    }
    public autoPlay(value: boolean | undefined): this {
        this._autoPlay_flag = true
        this._autoPlay0_value = value
        return this
    }
    public controls(value: boolean | undefined): this {
        this._controls_flag = true
        this._controls0_value = value
        return this
    }
    public loop(value: boolean | undefined): this {
        this._loop_flag = true
        this._loop0_value = value
        return this
    }
    public objectFit(value: ImageFit | undefined): this {
        this._objectFit_flag = true
        this._objectFit0_value = value
        return this
    }
    public onStart(value: VoidCallback | undefined): this {
        this._onStart_flag = true
        this._onStart0_value = value
        return this
    }
    public onPause(value: VoidCallback | undefined): this {
        this._onPause_flag = true
        this._onPause0_value = value
        return this
    }
    public onFinish(value: VoidCallback | undefined): this {
        this._onFinish_flag = true
        this._onFinish0_value = value
        return this
    }
    public onFullscreenChange(value: ((value0: FullscreenInfo) => void) | undefined): this {
        this._onFullscreenChange_flag = true
        this._onFullscreenChange0_value = value
        return this
    }
    public onPrepared(value: ((value0: PreparedInfo) => void) | undefined): this {
        this._onPrepared_flag = true
        this._onPrepared0_value = value
        return this
    }
    public onSeeking(value: ((value0: PlaybackInfo) => void) | undefined): this {
        this._onSeeking_flag = true
        this._onSeeking0_value = value
        return this
    }
    public onSeeked(value: ((value0: PlaybackInfo) => void) | undefined): this {
        this._onSeeked_flag = true
        this._onSeeked0_value = value
        return this
    }
    public onUpdate(value: ((value0: PlaybackInfo) => void) | undefined): this {
        this._onUpdate_flag = true
        this._onUpdate0_value = value
        return this
    }
    public onError(value: (() => void) | undefined): this {
        this._onError_flag = true
        this._onError0_value = value
        return this
    }
    public onStop(value: (() => void) | undefined): this {
        this._onStop_flag = true
        this._onStop0_value = value
        return this
    }
    public enableAnalyzer(value: boolean | undefined): this {
        this._enableAnalyzer_flag = true
        this._enableAnalyzer0_value = value
        return this
    }
    public analyzerConfig(value: ImageAnalyzerConfig | undefined): this {
        this._analyzerConfig_flag = true
        this._analyzerConfig0_value = value
        return this
    }
    public surfaceBackgroundColor(value: ColorMetrics | undefined): this {
        this._surfaceBackgroundColor_flag = true
        this._surfaceBackgroundColor0_value = value
        return this
    }
    public enableShortcutKey(value: boolean | undefined): this {
        this._enableShortcutKey_flag = true
        this._enableShortcutKey0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<VideoAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class FullscreenInfo_serializer {
    public static write(buffer: SerializerBase, value: FullscreenInfo): void {
        let valueSerializer : SerializerBase = buffer
        const value_fullscreen  = value.fullscreen
        valueSerializer.writeBoolean(value_fullscreen)
    }
    public static read(buffer: DeserializerBase): FullscreenInfo {
        let valueDeserializer : DeserializerBase = buffer
        const fullscreen_result : boolean = valueDeserializer.readBoolean()
        let value : FullscreenInfo = ({fullscreen: fullscreen_result} as FullscreenInfo)
        return value
    }
}
export class PlaybackInfo_serializer {
    public static write(buffer: SerializerBase, value: PlaybackInfo): void {
        let valueSerializer : SerializerBase = buffer
        const value_time  = value.time
        valueSerializer.writeNumber(value_time)
    }
    public static read(buffer: DeserializerBase): PlaybackInfo {
        let valueDeserializer : DeserializerBase = buffer
        const time_result : number = (valueDeserializer.readNumber() as number)
        let value : PlaybackInfo = ({time: time_result} as PlaybackInfo)
        return value
    }
}
export class PreparedInfo_serializer {
    public static write(buffer: SerializerBase, value: PreparedInfo): void {
        let valueSerializer : SerializerBase = buffer
        const value_duration  = value.duration
        valueSerializer.writeNumber(value_duration)
    }
    public static read(buffer: DeserializerBase): PreparedInfo {
        let valueDeserializer : DeserializerBase = buffer
        const duration_result : number = (valueDeserializer.readNumber() as number)
        let value : PreparedInfo = ({duration: duration_result} as PreparedInfo)
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
        const value_showFirstFrame  = value.showFirstFrame
        let value_showFirstFrame_type : int32 = RuntimeType.UNDEFINED
        value_showFirstFrame_type = runtimeType(value_showFirstFrame)
        valueSerializer.writeInt8((value_showFirstFrame_type).toChar())
        if ((value_showFirstFrame_type) != (RuntimeType.UNDEFINED)) {
            const value_showFirstFrame_value  = value_showFirstFrame!
            valueSerializer.writeBoolean(value_showFirstFrame_value)
        }
    }
    public static read(buffer: DeserializerBase): PosterOptions {
        let valueDeserializer : DeserializerBase = buffer
        const showFirstFrame_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let showFirstFrame_buf : boolean | undefined
        if ((showFirstFrame_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            showFirstFrame_buf = valueDeserializer.readBoolean()
        }
        const showFirstFrame_result : boolean | undefined = showFirstFrame_buf
        let value : PosterOptions = ({showFirstFrame: showFirstFrame_result} as PosterOptions)
        return value
    }
}
export class VideoOptions_serializer {
    public static write(buffer: SerializerBase, value: VideoOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_src  = value.src
        let value_src_type : int32 = RuntimeType.UNDEFINED
        value_src_type = runtimeType(value_src)
        valueSerializer.writeInt8((value_src_type).toChar())
        if ((value_src_type) != (RuntimeType.UNDEFINED)) {
            const value_src_value  = value_src!
            let value_src_value_type : int32 = RuntimeType.UNDEFINED
            value_src_value_type = runtimeType(value_src_value)
            if (RuntimeType.STRING == value_src_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_src_value_0  = value_src_value as string
                valueSerializer.writeString(value_src_value_0)
            }
            else if (RuntimeType.OBJECT == value_src_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_src_value_1  = value_src_value as Resource
                Resource_serializer.write(valueSerializer, value_src_value_1)
            }
        }
        const value_currentProgressRate  = value.currentProgressRate
        let value_currentProgressRate_type : int32 = RuntimeType.UNDEFINED
        value_currentProgressRate_type = runtimeType(value_currentProgressRate)
        valueSerializer.writeInt8((value_currentProgressRate_type).toChar())
        if ((value_currentProgressRate_type) != (RuntimeType.UNDEFINED)) {
            const value_currentProgressRate_value  = value_currentProgressRate!
            let value_currentProgressRate_value_type : int32 = RuntimeType.UNDEFINED
            value_currentProgressRate_value_type = runtimeType(value_currentProgressRate_value)
            if (RuntimeType.NUMBER == value_currentProgressRate_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_currentProgressRate_value_0  = value_currentProgressRate_value as number
                valueSerializer.writeNumber(value_currentProgressRate_value_0)
            }
            else if (RuntimeType.STRING == value_currentProgressRate_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_currentProgressRate_value_1  = value_currentProgressRate_value as string
                valueSerializer.writeString(value_currentProgressRate_value_1)
            }
            else if (TypeChecker.isPlaybackSpeed(value_currentProgressRate_value)) {
                valueSerializer.writeInt8((2).toChar())
                const value_currentProgressRate_value_2  = value_currentProgressRate_value as PlaybackSpeed
                valueSerializer.writeInt32(TypeChecker.PlaybackSpeed_ToNumeric(value_currentProgressRate_value_2))
            }
        }
        const value_previewUri  = value.previewUri
        let value_previewUri_type : int32 = RuntimeType.UNDEFINED
        value_previewUri_type = runtimeType(value_previewUri)
        valueSerializer.writeInt8((value_previewUri_type).toChar())
        if ((value_previewUri_type) != (RuntimeType.UNDEFINED)) {
            const value_previewUri_value  = value_previewUri!
            let value_previewUri_value_type : int32 = RuntimeType.UNDEFINED
            value_previewUri_value_type = runtimeType(value_previewUri_value)
            if (RuntimeType.STRING == value_previewUri_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_previewUri_value_0  = value_previewUri_value as string
                valueSerializer.writeString(value_previewUri_value_0)
            }
            else if (TypeChecker.isimage_PixelMap(value_previewUri_value, false, false)) {
                valueSerializer.writeInt8((1).toChar())
                const value_previewUri_value_1  = value_previewUri_value as image.PixelMap
                image_PixelMap_serializer.write(valueSerializer, value_previewUri_value_1)
            }
            else if (TypeChecker.isResource(value_previewUri_value, false, false, false, false, false)) {
                valueSerializer.writeInt8((2).toChar())
                const value_previewUri_value_2  = value_previewUri_value as Resource
                Resource_serializer.write(valueSerializer, value_previewUri_value_2)
            }
        }
        const value_controller  = value.controller
        let value_controller_type : int32 = RuntimeType.UNDEFINED
        value_controller_type = runtimeType(value_controller)
        valueSerializer.writeInt8((value_controller_type).toChar())
        if ((value_controller_type) != (RuntimeType.UNDEFINED)) {
            const value_controller_value  = value_controller!
            VideoController_serializer.write(valueSerializer, value_controller_value)
        }
        const value_imageAIOptions  = value.imageAIOptions
        let value_imageAIOptions_type : int32 = RuntimeType.UNDEFINED
        value_imageAIOptions_type = runtimeType(value_imageAIOptions)
        valueSerializer.writeInt8((value_imageAIOptions_type).toChar())
        if ((value_imageAIOptions_type) != (RuntimeType.UNDEFINED)) {
            const value_imageAIOptions_value  = value_imageAIOptions!
            ImageAIOptions_serializer.write(valueSerializer, value_imageAIOptions_value)
        }
        const value_posterOptions  = value.posterOptions
        let value_posterOptions_type : int32 = RuntimeType.UNDEFINED
        value_posterOptions_type = runtimeType(value_posterOptions)
        valueSerializer.writeInt8((value_posterOptions_type).toChar())
        if ((value_posterOptions_type) != (RuntimeType.UNDEFINED)) {
            const value_posterOptions_value  = value_posterOptions!
            PosterOptions_serializer.write(valueSerializer, value_posterOptions_value)
        }
    }
    public static read(buffer: DeserializerBase): VideoOptions {
        let valueDeserializer : DeserializerBase = buffer
        const src_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let src_buf : string | Resource | undefined
        if ((src_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const src_buf__selector : int32 = valueDeserializer.readInt8()
            let src_buf_ : string | Resource | undefined
            if (src_buf__selector == (0).toChar()) {
                src_buf_ = (valueDeserializer.readString() as string)
            }
            else if (src_buf__selector == (1).toChar()) {
                src_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for src_buf_ has to be chosen through deserialisation.")
            }
            src_buf = (src_buf_ as string | Resource)
        }
        const src_result : string | Resource | undefined = src_buf
        const currentProgressRate_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let currentProgressRate_buf : number | string | PlaybackSpeed | undefined
        if ((currentProgressRate_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const currentProgressRate_buf__selector : int32 = valueDeserializer.readInt8()
            let currentProgressRate_buf_ : number | string | PlaybackSpeed | undefined
            if (currentProgressRate_buf__selector == (0).toChar()) {
                currentProgressRate_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (currentProgressRate_buf__selector == (1).toChar()) {
                currentProgressRate_buf_ = (valueDeserializer.readString() as string)
            }
            else if (currentProgressRate_buf__selector == (2).toChar()) {
                currentProgressRate_buf_ = TypeChecker.PlaybackSpeed_FromNumeric(valueDeserializer.readInt32())
            }
            else {
                throw new Error("One of the branches for currentProgressRate_buf_ has to be chosen through deserialisation.")
            }
            currentProgressRate_buf = (currentProgressRate_buf_ as number | string | PlaybackSpeed)
        }
        const currentProgressRate_result : number | string | PlaybackSpeed | undefined = currentProgressRate_buf
        const previewUri_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let previewUri_buf : string | image.PixelMap | Resource | undefined
        if ((previewUri_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const previewUri_buf__selector : int32 = valueDeserializer.readInt8()
            let previewUri_buf_ : string | image.PixelMap | Resource | undefined
            if (previewUri_buf__selector == (0).toChar()) {
                previewUri_buf_ = (valueDeserializer.readString() as string)
            }
            else if (previewUri_buf__selector == (1).toChar()) {
                previewUri_buf_ = (image_PixelMap_serializer.read(valueDeserializer) as image.PixelMap)
            }
            else if (previewUri_buf__selector == (2).toChar()) {
                previewUri_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for previewUri_buf_ has to be chosen through deserialisation.")
            }
            previewUri_buf = (previewUri_buf_ as string | image.PixelMap | Resource)
        }
        const previewUri_result : string | image.PixelMap | Resource | undefined = previewUri_buf
        const controller_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let controller_buf : VideoController | undefined
        if ((controller_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            controller_buf = (VideoController_serializer.read(valueDeserializer) as VideoController)
        }
        const controller_result : VideoController | undefined = controller_buf
        const imageAIOptions_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let imageAIOptions_buf : ImageAIOptions | undefined
        if ((imageAIOptions_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            imageAIOptions_buf = ImageAIOptions_serializer.read(valueDeserializer)
        }
        const imageAIOptions_result : ImageAIOptions | undefined = imageAIOptions_buf
        const posterOptions_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let posterOptions_buf : PosterOptions | undefined
        if ((posterOptions_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            posterOptions_buf = PosterOptions_serializer.read(valueDeserializer)
        }
        const posterOptions_result : PosterOptions | undefined = posterOptions_buf
        let value : VideoOptions = ({src: src_result, currentProgressRate: currentProgressRate_result, previewUri: previewUri_result, controller: controller_result, imageAIOptions: imageAIOptions_result, posterOptions: posterOptions_result} as VideoOptions)
        return value
    }
}
