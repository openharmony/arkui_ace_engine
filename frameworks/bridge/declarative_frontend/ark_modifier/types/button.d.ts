/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
declare enum ButtonType {
    Capsule,
    Circle,
    Normal,
    ROUNDED_RECTANGLE = 3
}
declare enum ButtonStyleMode {
    NORMAL = 0,
    EMPHASIZED = 1,
    TEXTUAL = 2
}
declare enum ButtonRole {
    NORMAL = 0,
    ERROR = 1
}
declare type ButtonTriggerClickCallback = (xPos: number, yPos: number) => void;
declare interface ButtonConfiguration extends CommonConfiguration<ButtonConfiguration> {
    label: string;
    pressed: boolean;
    triggerClick: ButtonTriggerClickCallback;
}
declare enum ControlSize {
    SMALL = 'small',
    NORMAL = 'normal'
}
declare interface ButtonOptions {
    type?: ButtonType;
    stateEffect?: boolean;
    buttonStyle?: ButtonStyleMode;
    controlSize?: ControlSize;
    role?: ButtonRole;
}
interface ButtonInterface {
    (): ButtonAttribute;
    (options: ButtonOptions): ButtonAttribute;
    (label: ResourceStr, options?: ButtonOptions): ButtonAttribute;
}
declare interface LabelStyle {
    overflow?: TextOverflow;
    maxLines?: number;
    minFontSize?: number | ResourceStr;
    maxFontSize?: number | ResourceStr;
    heightAdaptivePolicy?: TextHeightAdaptivePolicy;
    font?: Font;
    textAlign?: TextAlign;
}
declare class ButtonAttribute extends CommonMethod<ButtonAttribute> {
    type(value: ButtonType): ButtonAttribute;
    stateEffect(value: boolean): ButtonAttribute;
    buttonStyle(value: ButtonStyleMode): ButtonAttribute;
    controlSize(value: ControlSize): ButtonAttribute;
    role(value: ButtonRole): ButtonAttribute;
    fontColor(value: ResourceColor): ButtonAttribute;
    fontSize(value: Length): ButtonAttribute;
    fontWeight(value: number | FontWeight | string): ButtonAttribute;
    fontStyle(value: FontStyle): ButtonAttribute;
    fontFamily(value: string | Resource): ButtonAttribute;
    contentModifier(modifier: ContentModifier<ButtonConfiguration>): ButtonAttribute;
    labelStyle(value: LabelStyle): ButtonAttribute;
    minFontScale(scale: number | Resource): ButtonAttribute;
    maxFontScale(scale: number | Resource): ButtonAttribute;
}
declare const Button: ButtonInterface;
declare const ButtonInstance: ButtonAttribute;
