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
export default namespace promptAction {
    loadLibrary("promptAction_ani");
    export enum ShadowStyle {
        OUTER_DEFAULT_XS = 0,
        OUTER_DEFAULT_SM = 1,
        OUTER_DEFAULT_MD = 2,
        OUTER_DEFAULT_LG = 3,
        OUTER_FLOATING_SM = 4,
        OUTER_FLOATING_MD = 5
    }

    export enum Color {
        WHITE = 0,
        BLACK = 1,
        BLUE = 2,
        BROWN = 3,
        GRAY = 4,
        GREEN = 5,
        GREY = 6,
        ORANGE = 7,
        PINK = 8,
        RED = 9,
        YELLOW = 10,
        TRANSPARENT = 11
    }

    export enum BlurStyle {
        Thin = 0,
        Regular = 1,
        Thick = 2,
        BACKGROUND_THIN = 3,
        BACKGROUND_REGULAR = 4,
        BACKGROUND_THICK = 5,
        BACKGROUND_ULTRA_THICK = 6,
        NONE = 7,
        COMPONENT_ULTRA_THIN = 8,
        COMPONENT_THIN = 9,
        COMPONENT_REGULAR = 10,
        COMPONENT_THICK = 11,
        COMPONENT_ULTRA_THICK = 12,
    }

    export enum Alignment {
        TOP_START = "TopStart",
        TOP = "Top",
        TOP_END = "TopEnd",
        START = "Start",
        CENTER = "Center",
        END = "End",
        BOTTOM_START = "BottomStart",
        BOTTOM = "Bottom",
        BOTTOM_END = "BottomEnd",
    }

    export enum ToastShowMode {
        DEFAULT = 0,
        TOP_MOST = 1,
        SYSTEM_TOP_MOST = 2
    }

    export enum ShadowType {
        COLOR = 0,
        BLUR = 1,
    }

    export enum ColoringStrategy {
        INVERT = "invert",
        AVERAGE = "average",
        PRIMARY = "primary",
    }

    export enum HoverModeAreaType {
        TOP_SCREEN = 0,
        BOTTOM_SCREEN = 1,
    }

    export interface Resource {

        id: number;
        bundleName: string;
        moduleName: string;
        params?: Array<String>;
        type?: number;
    };

    export type ResourceColor = Color | number | string | Resource;
    export type Length = number | string | Resource;

    export interface Offset {
        dx: Length;
        dy: Length;
    }

    export interface ShadowOptions {
        radius: number | Resource;
        type?: ShadowType;
        color?: Color | string | Resource| ColoringStrategy;
        offsetX?: number | Resource;
        offsetY?: number | Resource;
        fill?: boolean;
    }

    export default interface ShowToastOptions
    {
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
    export native function showToast(options: ShowToastOptions):void;
}