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
interface GaugeOptions {
    value: number;
    min?: number;
    max?: number;
}
interface GaugeInterface {
    (options: GaugeOptions): GaugeAttribute;
}
declare interface GaugeShadowOptions extends MultiShadowOptions {
}
declare interface GaugeIndicatorOptions {
    icon?: ResourceStr;
    space?: Dimension;
}
declare interface GaugeConfiguration extends CommonConfiguration<GaugeConfiguration> {
    value: number;
    min: number;
    max: number;
}
declare class GaugeAttribute extends CommonMethod<GaugeAttribute> {
    value(value: number): GaugeAttribute;
    startAngle(angle: number): GaugeAttribute;
    endAngle(angle: number): GaugeAttribute;
    colors(colors: ResourceColor | LinearGradient | Array<[
        ResourceColor | LinearGradient,
        number
    ]>): GaugeAttribute;
    strokeWidth(length: Length): GaugeAttribute;
    trackShadow(value: GaugeShadowOptions): GaugeAttribute;
    indicator(value: GaugeIndicatorOptions): GaugeAttribute;
    privacySensitive(isPrivacySensitiveMode: Optional<boolean>): GaugeAttribute;
    contentModifier(modifier: ContentModifier<GaugeConfiguration>): GaugeAttribute;
}
declare const Gauge: GaugeInterface;
declare const GaugeInstance: GaugeAttribute;

interface LazyGaugeComponent {
    _modifiersWithKeys: any;

    setMap(): void;

    value(value: number): LazyGaugeComponent;
    startAngle(angle: number): LazyGaugeComponent;
    endAngle(angle: number): LazyGaugeComponent;
    colors(colors: ResourceColor | LinearGradient | Array<[ResourceColor | LinearGradient, number]>): LazyGaugeComponent;
    strokeWidth(length: Length): LazyGaugeComponent;
    description(value: CustomBuilder): LazyGaugeComponent;
    trackShadow(value: GaugeShadowOptions): LazyGaugeComponent;
    indicator(value: GaugeIndicatorOptions): LazyGaugeComponent;
    privacySensitive(value: Optional<boolean>): LazyGaugeComponent;
    contentModifier(modifier: ContentModifier<GaugeConfiguration>): LazyGaugeComponent;
}

interface GaugeComponentModule {
    createComponent(nativePtr: KNode, classType: ModifierType): LazyGaugeComponent;
}
