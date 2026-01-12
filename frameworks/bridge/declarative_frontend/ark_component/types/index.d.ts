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

type ArkComponent = any;
type Resource = any;
type ResourceColor = Color | number | string | Resource;
type ArkBackground = any;
type ArkBindMenu = any;
type ArkBorder = any;
type ArkSearchAutoCapitalization = any;
type ArkTextAreaAutoCapitalization = any;
type ArkTextInputAutoCapitalization = any;
type ArkTextInputType = any;
type Length = any;
type EdgeWidths = any;
type LocalizedEdgeWidths = any;
type ArkBorderRadiusOpts = any;
type LocalizedBorderRadius = any;
type RenderStrategy = any;
type BorderRadiuses = any;
type Position = any;
type Edges = any;
type LocalizedEdges = any;
type GradientDirection = any;
type ArkOverlay = any;
type EdgeColors = any;
type LocalizedEdgeColors = any;
type Matrix4Transit = any;
type BorderStyle = any;
type EdgeStyles = any;
type ShadowOptions = any;
type ArkShadowStyle = any;
type ArkBlurOptions = any;
type InvertOptions = any;
declare interface PageInfo {}
declare interface NavigationInfo {}

type KNode = number | null;
// interface_sdk-js/api/@internal/component/ets/enums.d.ts
declare enum Color {
  White = 0,
  Black = 1,
  Blue = 2,
  Brown = 3,
  Gray = 4,
  Green = 5,
  Grey = 6,
  Orange = 7,
  Pink = 8,
  Red = 9,
  Yellow = 10,
  Transparent = 11
}

//interface_sdk-js/api/@internal/component/ets/common.d.ts
declare enum RepeatMode {
  Repeat,
  Stretch,
  Round,
  Space,
}
//interface_sdk-js/api/@internal/component/ets/common.d.ts
declare interface LinearGradient {
  angle?: number | string;
  direction?: GradientDirection;
  colors: Array<[ResourceColor, number]>;
  repeating?: boolean;
}
declare interface BorderImageOption {
  slice?: Length | EdgeWidths | LocalizedEdgeWidths,
  repeat?: RepeatMode,
  source?: string | Resource | LinearGradient,
  width?: Length | EdgeWidths | LocalizedEdgeWidths,
  outset?: Length | EdgeWidths | LocalizedEdgeWidths,
  fill?: boolean;
}
