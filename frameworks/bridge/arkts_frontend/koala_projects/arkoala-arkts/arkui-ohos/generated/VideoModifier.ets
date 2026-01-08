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

import { CommonMethodModifier } from "./CommonMethodModifier"
import { ModifierState } from './CommonModifier'
import { AttributeModifier, hookVideoOnError, hookVideoAnalyzerConfig } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkVideoPeer, FullscreenInfo, PreparedInfo, PlaybackInfo, VideoAttribute } from "./component/video"
import { int32 } from "@koalaui/common"
import { CommonMethod } from "./component/common"
import { ImageFit } from "./component/enums"
import { VoidCallback } from "./component/units"
import { ErrorCallback } from "@ohos.base"
import { ImageAnalyzerConfig } from "./component/imageCommon"
import { ColorMetrics } from "arkui.Graphics"
export class VideoModifier extends CommonMethodModifier implements VideoAttribute,AttributeModifier<VideoAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: VideoAttribute): void { }
    applyPressedAttribute(instance: VideoAttribute): void { }
    applyFocusedAttribute(instance: VideoAttribute): void { }
    applyDisabledAttribute(instance: VideoAttribute): void { }
    applySelectedAttribute(instance: VideoAttribute): void { }
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
    _onError_0_0value?: VoidCallback | ErrorCallback | undefined
    _onStop_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onStop_0_0value?: VoidCallback | undefined
    _enableAnalyzer_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableAnalyzer_0_0value?: boolean | undefined
    _analyzerConfig_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _analyzerConfig_0_0value?: ImageAnalyzerConfig | undefined
    _enableShortcutKey_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableShortcutKey_0_0value?: boolean | undefined
    _surfaceBackgroundColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _surfaceBackgroundColor_0_0value?: ColorMetrics | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkVideoPeer;
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
                    hookVideoOnError(peer, (this._onError_0_0value as VoidCallback | ErrorCallback | undefined));
                    this._onError_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onError_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onError_0_flag = AttributeUpdaterFlag.INITIAL;
                    hookVideoOnError(peer, (undefined as VoidCallback | ErrorCallback | undefined));
                }
            }
        }
        if (this._onStop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onStop_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnStopAttribute((this._onStop_0_0value as VoidCallback | undefined));
                    this._onStop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onStop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onStop_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnStopAttribute((undefined as VoidCallback | undefined));
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
                    hookVideoAnalyzerConfig(peer, (this._analyzerConfig_0_0value as ImageAnalyzerConfig | undefined));
                    this._analyzerConfig_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._analyzerConfig_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._analyzerConfig_0_flag = AttributeUpdaterFlag.INITIAL;
                    hookVideoAnalyzerConfig(peer, (undefined as ImageAnalyzerConfig | undefined));
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
    }
    mergeModifier(modifier: VideoModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
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
                    this.onError((undefined as VoidCallback | ErrorCallback | undefined));
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
                    this.onStop((undefined as VoidCallback | undefined));
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
    }
    muted(value: boolean | undefined): this {
        if (((this._muted_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._muted_0_0value) !== (value)))
        {
            this._muted_0_flag = AttributeUpdaterFlag.UPDATE
            this._muted_0_0value = value
            this._state.fireChange()
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
            this._state.fireChange()
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
            this._state.fireChange()
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
            this._state.fireChange()
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
            this._state.fireChange()
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
            this._state.fireChange()
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
            this._state.fireChange()
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
            this._state.fireChange()
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
            this._state.fireChange()
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
            this._state.fireChange()
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
            this._state.fireChange()
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
            this._state.fireChange()
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
            this._state.fireChange()
        } else
        {
            this._onUpdate_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onError(value: VoidCallback | ErrorCallback | undefined): this {
        if (((this._onError_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onError_0_flag = AttributeUpdaterFlag.UPDATE
            this._onError_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onError_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onStop(value: VoidCallback | undefined): this {
        if (((this._onStop_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onStop_0_flag = AttributeUpdaterFlag.UPDATE
            this._onStop_0_0value = value
            this._state.fireChange()
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
            this._state.fireChange()
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
            this._state.fireChange()
        } else
        {
            this._analyzerConfig_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableShortcutKey(value: boolean | undefined): this {
        if (((this._enableShortcutKey_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableShortcutKey_0_0value) !== (value)))
        {
            this._enableShortcutKey_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableShortcutKey_0_0value = value
            this._state.fireChange()
        } else
        {
            this._enableShortcutKey_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    surfaceBackgroundColor(value: ColorMetrics | undefined): this {
        if (((this._surfaceBackgroundColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._surfaceBackgroundColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._surfaceBackgroundColor_0_0value = value
            this._state.fireChange()
        } else
        {
            this._surfaceBackgroundColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<VideoAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
