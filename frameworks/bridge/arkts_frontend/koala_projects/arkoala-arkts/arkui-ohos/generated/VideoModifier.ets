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

import { CommonMethodModifier } from './CommonMethodModifier'
import { AttributeModifier, extractors } from '#handwritten'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { ArkVideoPeer, FullscreenInfo, PreparedInfo, PlaybackInfo, VideoAttribute } from './component/video'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod, Callback as arkui_component_common_Callback } from './component/common'
import { ImageFit } from './component/enums'
import { VoidCallback, ColorMetrics as arkui_component_units_ColorMetrics } from './component/units'
import { ErrorCallback, BusinessError } from '@ohos.base'
import { ImageAnalyzerConfig } from './component/imageCommon'
import { ColorMetrics as arkui_Graphics_ColorMetrics } from '@arkui.Graphics'
export class VideoModifier extends CommonMethodModifier implements VideoAttribute,AttributeModifier<VideoAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState;
    _addr: ArrayBuffer = new ArrayBuffer(4096);
    _flagArray: Uint8Array = new Uint8Array(this._addr);
    constructor() {
        super();
        this._flagArray.fill(0);
    }
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: VideoAttribute): void { }
    applyPressedAttribute(instance: VideoAttribute): void { }
    applyFocusedAttribute(instance: VideoAttribute): void { }
    applyDisabledAttribute(instance: VideoAttribute): void { }
    applySelectedAttribute(instance: VideoAttribute): void { }
    public _muted_0_0value?: boolean | undefined
    public _autoPlay_0_0value?: boolean | undefined
    public _controls_0_0value?: boolean | undefined
    public _loop_0_0value?: boolean | undefined
    public _objectFit_0_0value?: ImageFit | undefined
    public _onStart_0_0value?: VoidCallback | undefined
    public _onPause_0_0value?: VoidCallback | undefined
    public _onFinish_0_0value?: VoidCallback | undefined
    public _onFullscreenChange_0_0value?: arkui_component_common_Callback<FullscreenInfo, void> | undefined
    public _onPrepared_0_0value?: arkui_component_common_Callback<PreparedInfo, void> | undefined
    public _onSeeking_0_0value?: arkui_component_common_Callback<PlaybackInfo, void> | undefined
    public _onSeeked_0_0value?: arkui_component_common_Callback<PlaybackInfo, void> | undefined
    public _onUpdate_0_0value?: arkui_component_common_Callback<PlaybackInfo, void> | undefined
    public _onError_0_0value?: VoidCallback | ErrorCallback<BusinessError<void>> | undefined
    public _onStop_0_0value?: VoidCallback | undefined
    public _enableAnalyzer_0_0value?: boolean | undefined
    public _analyzerConfig_0_0value?: ImageAnalyzerConfig | undefined
    public _enableShortcutKey_0_0value?: boolean | undefined
    public _surfaceBackgroundColor_0_0value?: arkui_component_units_ColorMetrics | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkVideoPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkVideoPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setMutedAttribute((this._muted_0_0value as boolean | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setMutedAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setAutoPlayAttribute((this._autoPlay_0_0value as boolean | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setAutoPlayAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setControlsAttribute((this._controls_0_0value as boolean | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setControlsAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setLoopAttribute((this._loop_0_0value as boolean | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setLoopAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1: {
                    peer.setObjectFitAttribute((this._objectFit_0_0value as ImageFit | undefined));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                    peer.setObjectFitAttribute((undefined as ImageFit | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1: {
                    peer.setOnStartAttribute((this._onStart_0_0value as VoidCallback | undefined));
                    flagArray[5] = 2;
                    break;
                }
                case 3: {
                    flagArray[5] = 2;
                    break;
                }
                default: {
                    flagArray[5] = 0;
                    peer.setOnStartAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1: {
                    peer.setOnPauseAttribute((this._onPause_0_0value as VoidCallback | undefined));
                    flagArray[6] = 2;
                    break;
                }
                case 3: {
                    flagArray[6] = 2;
                    break;
                }
                default: {
                    flagArray[6] = 0;
                    peer.setOnPauseAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1: {
                    peer.setOnFinishAttribute((this._onFinish_0_0value as VoidCallback | undefined));
                    flagArray[7] = 2;
                    break;
                }
                case 3: {
                    flagArray[7] = 2;
                    break;
                }
                default: {
                    flagArray[7] = 0;
                    peer.setOnFinishAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1: {
                    peer.setOnFullscreenChangeAttribute((this._onFullscreenChange_0_0value as arkui_component_common_Callback<FullscreenInfo, void> | undefined));
                    flagArray[8] = 2;
                    break;
                }
                case 3: {
                    flagArray[8] = 2;
                    break;
                }
                default: {
                    flagArray[8] = 0;
                    peer.setOnFullscreenChangeAttribute((undefined as arkui_component_common_Callback<FullscreenInfo, void> | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1: {
                    peer.setOnPreparedAttribute((this._onPrepared_0_0value as arkui_component_common_Callback<PreparedInfo, void> | undefined));
                    flagArray[9] = 2;
                    break;
                }
                case 3: {
                    flagArray[9] = 2;
                    break;
                }
                default: {
                    flagArray[9] = 0;
                    peer.setOnPreparedAttribute((undefined as arkui_component_common_Callback<PreparedInfo, void> | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1: {
                    peer.setOnSeekingAttribute((this._onSeeking_0_0value as arkui_component_common_Callback<PlaybackInfo, void> | undefined));
                    flagArray[10] = 2;
                    break;
                }
                case 3: {
                    flagArray[10] = 2;
                    break;
                }
                default: {
                    flagArray[10] = 0;
                    peer.setOnSeekingAttribute((undefined as arkui_component_common_Callback<PlaybackInfo, void> | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1: {
                    peer.setOnSeekedAttribute((this._onSeeked_0_0value as arkui_component_common_Callback<PlaybackInfo, void> | undefined));
                    flagArray[11] = 2;
                    break;
                }
                case 3: {
                    flagArray[11] = 2;
                    break;
                }
                default: {
                    flagArray[11] = 0;
                    peer.setOnSeekedAttribute((undefined as arkui_component_common_Callback<PlaybackInfo, void> | undefined));
                }
            }
        }
        if (flagArray[12] != 0) {
            switch (flagArray[12]) {
                case 1: {
                    peer.setOnUpdateAttribute((this._onUpdate_0_0value as arkui_component_common_Callback<PlaybackInfo, void> | undefined));
                    flagArray[12] = 2;
                    break;
                }
                case 3: {
                    flagArray[12] = 2;
                    break;
                }
                default: {
                    flagArray[12] = 0;
                    peer.setOnUpdateAttribute((undefined as arkui_component_common_Callback<PlaybackInfo, void> | undefined));
                }
            }
        }
        if (flagArray[13] != 0) {
            switch (flagArray[13]) {
                case 1: {
                    peer.setOnErrorAttribute((this._onError_0_0value as VoidCallback | ErrorCallback<BusinessError<void>> | undefined));
                    flagArray[13] = 2;
                    break;
                }
                case 3: {
                    flagArray[13] = 2;
                    break;
                }
                default: {
                    flagArray[13] = 0;
                    peer.setOnErrorAttribute((undefined as VoidCallback | ErrorCallback<BusinessError<void>> | undefined));
                }
            }
        }
        if (flagArray[14] != 0) {
            switch (flagArray[14]) {
                case 1: {
                    peer.setOnStopAttribute((this._onStop_0_0value as VoidCallback | undefined));
                    flagArray[14] = 2;
                    break;
                }
                case 3: {
                    flagArray[14] = 2;
                    break;
                }
                default: {
                    flagArray[14] = 0;
                    peer.setOnStopAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[15] != 0) {
            switch (flagArray[15]) {
                case 1: {
                    peer.setEnableAnalyzerAttribute((this._enableAnalyzer_0_0value as boolean | undefined));
                    flagArray[15] = 2;
                    break;
                }
                case 3: {
                    flagArray[15] = 2;
                    break;
                }
                default: {
                    flagArray[15] = 0;
                    peer.setEnableAnalyzerAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[16] != 0) {
            switch (flagArray[16]) {
                case 1: {
                    peer.setAnalyzerConfigAttribute((this._analyzerConfig_0_0value as ImageAnalyzerConfig | undefined));
                    flagArray[16] = 2;
                    break;
                }
                case 3: {
                    flagArray[16] = 2;
                    break;
                }
                default: {
                    flagArray[16] = 0;
                    peer.setAnalyzerConfigAttribute((undefined as ImageAnalyzerConfig | undefined));
                }
            }
        }
        if (flagArray[17] != 0) {
            switch (flagArray[17]) {
                case 1: {
                    peer.setEnableShortcutKeyAttribute((this._enableShortcutKey_0_0value as boolean | undefined));
                    flagArray[17] = 2;
                    break;
                }
                case 3: {
                    flagArray[17] = 2;
                    break;
                }
                default: {
                    flagArray[17] = 0;
                    peer.setEnableShortcutKeyAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[18] != 0) {
            switch (flagArray[18]) {
                case 1: {
                    peer.setSurfaceBackgroundColorAttribute((this._surfaceBackgroundColor_0_0value as arkui_component_units_ColorMetrics | undefined));
                    flagArray[18] = 2;
                    break;
                }
                case 3: {
                    flagArray[18] = 2;
                    break;
                }
                default: {
                    flagArray[18] = 0;
                    peer.setSurfaceBackgroundColorAttribute((undefined as arkui_component_units_ColorMetrics | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: VideoModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: VideoModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.muted(modifier._muted_0_0value);
                    break;
                }
                default: {
                    this.muted((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.autoPlay(modifier._autoPlay_0_0value);
                    break;
                }
                default: {
                    this.autoPlay((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.controls(modifier._controls_0_0value);
                    break;
                }
                default: {
                    this.controls((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.loop(modifier._loop_0_0value);
                    break;
                }
                default: {
                    this.loop((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1:
                case 3: {
                    this.objectFit(modifier._objectFit_0_0value);
                    break;
                }
                default: {
                    this.objectFit((undefined as ImageFit | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1:
                case 3: {
                    this.onStart(modifier._onStart_0_0value);
                    break;
                }
                default: {
                    this.onStart((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1:
                case 3: {
                    this.onPause(modifier._onPause_0_0value);
                    break;
                }
                default: {
                    this.onPause((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1:
                case 3: {
                    this.onFinish(modifier._onFinish_0_0value);
                    break;
                }
                default: {
                    this.onFinish((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1:
                case 3: {
                    this.onFullscreenChange(modifier._onFullscreenChange_0_0value);
                    break;
                }
                default: {
                    this.onFullscreenChange((undefined as arkui_component_common_Callback<FullscreenInfo, void> | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1:
                case 3: {
                    this.onPrepared(modifier._onPrepared_0_0value);
                    break;
                }
                default: {
                    this.onPrepared((undefined as arkui_component_common_Callback<PreparedInfo, void> | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1:
                case 3: {
                    this.onSeeking(modifier._onSeeking_0_0value);
                    break;
                }
                default: {
                    this.onSeeking((undefined as arkui_component_common_Callback<PlaybackInfo, void> | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1:
                case 3: {
                    this.onSeeked(modifier._onSeeked_0_0value);
                    break;
                }
                default: {
                    this.onSeeked((undefined as arkui_component_common_Callback<PlaybackInfo, void> | undefined));
                }
            }
        }
        if (flagArray[12] != 0) {
            switch (flagArray[12]) {
                case 1:
                case 3: {
                    this.onUpdate(modifier._onUpdate_0_0value);
                    break;
                }
                default: {
                    this.onUpdate((undefined as arkui_component_common_Callback<PlaybackInfo, void> | undefined));
                }
            }
        }
        if (flagArray[13] != 0) {
            switch (flagArray[13]) {
                case 1:
                case 3: {
                    this.onError(modifier._onError_0_0value);
                    break;
                }
                default: {
                    this.onError((undefined as VoidCallback | ErrorCallback<BusinessError<void>> | undefined));
                }
            }
        }
        if (flagArray[14] != 0) {
            switch (flagArray[14]) {
                case 1:
                case 3: {
                    this.onStop(modifier._onStop_0_0value);
                    break;
                }
                default: {
                    this.onStop((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[15] != 0) {
            switch (flagArray[15]) {
                case 1:
                case 3: {
                    this.enableAnalyzer(modifier._enableAnalyzer_0_0value);
                    break;
                }
                default: {
                    this.enableAnalyzer((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[16] != 0) {
            switch (flagArray[16]) {
                case 1:
                case 3: {
                    this.analyzerConfig(modifier._analyzerConfig_0_0value);
                    break;
                }
                default: {
                    this.analyzerConfig((undefined as ImageAnalyzerConfig | undefined));
                }
            }
        }
        if (flagArray[17] != 0) {
            switch (flagArray[17]) {
                case 1:
                case 3: {
                    this.enableShortcutKey(modifier._enableShortcutKey_0_0value);
                    break;
                }
                default: {
                    this.enableShortcutKey((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[18] != 0) {
            switch (flagArray[18]) {
                case 1:
                case 3: {
                    this.surfaceBackgroundColor(modifier._surfaceBackgroundColor_0_0value);
                    break;
                }
                default: {
                    this.surfaceBackgroundColor((undefined as arkui_component_units_ColorMetrics | undefined));
                }
            }
        }
    }
    muted(value: boolean | undefined): this {
        if (((this._flagArray[0]) == (0)) || ((this._muted_0_0value) !== (value))) {
            this._flagArray[0] = 1
            this._muted_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    autoPlay(value: boolean | undefined): this {
        if (((this._flagArray[1]) == (0)) || ((this._autoPlay_0_0value) !== (value))) {
            this._flagArray[1] = 1
            this._autoPlay_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    controls(value: boolean | undefined): this {
        if (((this._flagArray[2]) == (0)) || ((this._controls_0_0value) !== (value))) {
            this._flagArray[2] = 1
            this._controls_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    loop(value: boolean | undefined): this {
        if (((this._flagArray[3]) == (0)) || ((this._loop_0_0value) !== (value))) {
            this._flagArray[3] = 1
            this._loop_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    objectFit(value: ImageFit | undefined): this {
        if (((this._flagArray[4]) == (0)) || (true)) {
            this._flagArray[4] = 1
            this._objectFit_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[4] = 3
        }
        return this
    }
    onStart(value: VoidCallback | undefined): this {
        if (((this._flagArray[5]) == (0)) || (true)) {
            this._flagArray[5] = 1
            this._onStart_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[5] = 3
        }
        return this
    }
    onPause(value: VoidCallback | undefined): this {
        if (((this._flagArray[6]) == (0)) || (true)) {
            this._flagArray[6] = 1
            this._onPause_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[6] = 3
        }
        return this
    }
    onFinish(value: VoidCallback | undefined): this {
        if (((this._flagArray[7]) == (0)) || (true)) {
            this._flagArray[7] = 1
            this._onFinish_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[7] = 3
        }
        return this
    }
    onFullscreenChange(value: arkui_component_common_Callback<FullscreenInfo, void> | undefined): this {
        if (((this._flagArray[8]) == (0)) || (true)) {
            this._flagArray[8] = 1
            this._onFullscreenChange_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[8] = 3
        }
        return this
    }
    onPrepared(value: arkui_component_common_Callback<PreparedInfo, void> | undefined): this {
        if (((this._flagArray[9]) == (0)) || (true)) {
            this._flagArray[9] = 1
            this._onPrepared_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[9] = 3
        }
        return this
    }
    onSeeking(value: arkui_component_common_Callback<PlaybackInfo, void> | undefined): this {
        if (((this._flagArray[10]) == (0)) || (true)) {
            this._flagArray[10] = 1
            this._onSeeking_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[10] = 3
        }
        return this
    }
    onSeeked(value: arkui_component_common_Callback<PlaybackInfo, void> | undefined): this {
        if (((this._flagArray[11]) == (0)) || (true)) {
            this._flagArray[11] = 1
            this._onSeeked_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[11] = 3
        }
        return this
    }
    onUpdate(value: arkui_component_common_Callback<PlaybackInfo, void> | undefined): this {
        if (((this._flagArray[12]) == (0)) || (true)) {
            this._flagArray[12] = 1
            this._onUpdate_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[12] = 3
        }
        return this
    }
    onError(value: VoidCallback | ErrorCallback<BusinessError<void>> | undefined): this {
        if (((this._flagArray[13]) == (0)) || (true)) {
            this._flagArray[13] = 1
            this._onError_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[13] = 3
        }
        return this
    }
    onStop(value: VoidCallback | undefined): this {
        if (((this._flagArray[14]) == (0)) || (true)) {
            this._flagArray[14] = 1
            this._onStop_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[14] = 3
        }
        return this
    }
    enableAnalyzer(value: boolean | undefined): this {
        if (((this._flagArray[15]) == (0)) || ((this._enableAnalyzer_0_0value) !== (value))) {
            this._flagArray[15] = 1
            this._enableAnalyzer_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[15] = 3
        }
        return this
    }
    analyzerConfig(value: ImageAnalyzerConfig | undefined): this {
        if (((this._flagArray[16]) == (0)) || (true)) {
            this._flagArray[16] = 1
            this._analyzerConfig_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[16] = 3
        }
        return this
    }
    enableShortcutKey(value: boolean | undefined): this {
        if (((this._flagArray[17]) == (0)) || ((this._enableShortcutKey_0_0value) !== (value))) {
            this._flagArray[17] = 1
            this._enableShortcutKey_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[17] = 3
        }
        return this
    }
    surfaceBackgroundColor(value: arkui_component_units_ColorMetrics | undefined): this {
        if (((this._flagArray[18]) == (0)) || (true)) {
            this._flagArray[18] = 1
            this._surfaceBackgroundColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[18] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<VideoAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}
