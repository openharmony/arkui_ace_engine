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

import { Resource } from "global.resource"
import { Alignment } from "arkui/component/enums"
import { ResourceColor, Offset } from "arkui/component/units"
import { BlurStyle, ShadowOptions, ShadowStyle, HoverModeAreaType } from "arkui/component/common"
import { Serializer } from "arkui/component/peers/Serializer"
import { ArkUIGeneratedNativeModule } from "#components"

namespace promptAction {
    export interface ShowToastOptions {
        message: string | Resource;
        duration?: number;
        bottom?: string | number;
        showMode?: ToastShowMode;
        alignment?: Alignment;
        offset?: Offset;
        backgroundColor?: ResourceColor;
        textColor?: ResourceColor;
        backgroundBlurStyle?: BlurStyle;
        shadow?: ShadowOptions | ShadowStyle;
        enableHoverMode?: boolean;
        hoverModeArea?: HoverModeAreaType;
    }

    export enum ToastShowMode {
        DEFAULT = 0,
        TOP_MOST = 1,
        SYSTEM_TOP_MOST = 2
    }

    export function showToast(value: ShowToastOptions): void {
        const thisSerializer : Serializer = Serializer.hold();
        thisSerializer.writeShowToastOptions(value);
        ArkUIGeneratedNativeModule._PromptAction_showToast(thisSerializer.asBuffer(), thisSerializer.length());
        thisSerializer.release();
    }
}

export default promptAction