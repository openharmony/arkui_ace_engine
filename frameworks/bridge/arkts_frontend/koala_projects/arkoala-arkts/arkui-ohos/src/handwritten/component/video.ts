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


import { TypeChecker } from "#components"
import { runtimeType, RuntimeType } from "@koalaui/interop"
import { int32 } from "@koalaui/common"
import { PixelMap } from "#external"
import { ArkUIAniModule } from "arkui.ani"
import { ArkCommonMethodComponent, AttributeModifier, CommonMethod } from './common';
import { applyAttributeModifierBase, applyCommonModifier } from "../handwritten/modifiers/ArkCommonModifier";
import { CommonModifier } from '../CommonModifier';
import { VideoModifier } from '../VideoModifier';
import { runtimeType, RuntimeType } from "@koalaui/interop"

const PlayBackSpeedTable: number[] = [0.75, 1.0, 1.25, 1.75, 2.0];

function convertPlaybackSpeed(value: PlaybackSpeed): number {
    const index = value as number;
    return PlayBackSpeedTable[index]
}

function hookSetVideoOptionsWithPeer(peer: ArkVideoPeer, value: VideoOptions): void {
    if (peer === undefined) {
        return;
    }
    let value_currentProgressRate_type : int32 = RuntimeType.UNDEFINED
    const value_currentProgressRate  = value.currentProgressRate
    value_currentProgressRate_type = runtimeType(value_currentProgressRate)
    if ((RuntimeType.UNDEFINED) != (value_currentProgressRate_type)) {
        const value_currentProgressRate_value  = value_currentProgressRate!
        if (TypeChecker.isPlaybackSpeed(value_currentProgressRate_value)) {
            value.currentProgressRate = convertPlaybackSpeed(value_currentProgressRate_value as PlaybackSpeed);
        }
    }
    const value_previewUri  = value.previewUri
    let value_previewUri_type : int32 = RuntimeType.UNDEFINED
    value_previewUri_type = runtimeType(value_previewUri)
    if ((RuntimeType.UNDEFINED) != (value_previewUri_type) && peer !== undefined) {
        const value_previewUri_value  = value_previewUri!
        let value_previewUri_value_type : int32 = RuntimeType.UNDEFINED
        value_previewUri_value_type = runtimeType(value_previewUri_value)
        if (!TypeChecker.isResource(value_previewUri_value, false, false, false, false, false) && (RuntimeType.STRING != value_previewUri_value_type)) {
            value.previewUri = undefined;
            peer.setVideoOptionsAttribute(value);
            ArkUIAniModule._Video_Transfer_PixelMap(peer.getPeerPtr() as KPointer, value_previewUri_value as PixelMap);
            return;
        }
    }
    peer.setVideoOptionsAttribute(value);
}

function hookSetVideoOptions(component: ArkVideoComponent, value: VideoOptions): void {
    const peer = component.getPeer();
    hookSetVideoOptionsWithPeer(peer, value);
}

export function hookVideoAttributeModifier(component: ArkVideoComponent, modifier: AttributeModifier<VideoAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier === undefined) {
        return;
    }
    let isCommonModifier: boolean = modifier instanceof CommonModifier;
    if (isCommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return;
    }
    let attributeSet = (): VideoModifier => {
        let isVideoModifier: boolean = modifier instanceof VideoModifier;
        let initModifier = component.getPeer()._attributeSet ? component.getPeer()._attributeSet! : new VideoModifier();
        if (isVideoModifier) {
            let videoModifier = modifier as object as VideoModifier;
            initModifier.mergeModifier(videoModifier);
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        } else {
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        }
    }
    let constructParam = (component: ArkCommonMethodComponent, ...params: FixedArray<Object>): void => {
        if (params.length < 1) {
            return;
        }
        let peer: ArkVideoPeer = component.getPeer() as Object as ArkVideoPeer;
        const param1_type = runtimeType(params[0])
        if ((RuntimeType.UNDEFINED) !== param1_type) {
            const options_casted = params[0] as VideoOptions;
            hookSetVideoOptionsWithPeer(peer, options_casted);
        }
    };
    let updaterReceiver = (): ArkVideoComponent => {
        let componentNew: ArkVideoComponent = new ArkVideoComponent();
        componentNew.setPeer(component.getPeer());
        return componentNew;
    };
    applyAttributeModifierBase(modifier as Object as AttributeModifier<VideoAttribute>, attributeSet, constructParam, updaterReceiver, component.getPeer());
}
