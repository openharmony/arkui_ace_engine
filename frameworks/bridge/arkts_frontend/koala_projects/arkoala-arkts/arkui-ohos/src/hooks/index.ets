import { KPointer } from "@koalaui/interop";
import { default as image } from "@ohos.multimedia.image";
import { ColorMetrics, DrawContext, LengthMetrics, Size } from "arkui.Graphics";
import { NodeController } from "arkui.NodeController";
import { default as curves } from "@ohos.curves";
import { default as matrix4 } from "@ohos.matrix4";
import { default as drawing } from "@ohos.graphics.drawing";
import { default as uiEffect } from "@ohos.graphics.uiEffect";
import { default as unifiedDataChannel } from "@ohos.data.unifiedDataChannel";
import { default as webview } from "@ohos.web.webview";
import { default as Want } from "@ohos.app.ability.Want";
import { Configuration } from "@ohos.app.ability.Configuration";
import { default as window } from "@ohos.window";
import { default as uiObserver } from "@ohos.arkui.observer";
import { UIContext } from "@ohos.arkui.UIContext";
import { AbilityInfo, WindowSize } from "bundleManager.AbilityInfo";
import {
  ApplicationInfo,
  ModuleMetadata,
  MultiAppMode,
} from "bundleManager.ApplicationInfo";
import {
  DataItem,
  Dependency,
  HapModuleInfo,
  PreloadItem,
  RouterItem,
} from "bundleManager.HapModuleInfo";
import { ExtensionAbilityInfo } from "bundleManager.ExtensionAbilityInfo";
import { Metadata } from "bundleManager.Metadata";
import { Skill, SkillUri } from "bundleManager.Skill";
import { DrawableDescriptor } from "@ohos.arkui.drawableDescriptor";
import {
  RectShape,
  CircleShape,
  EllipseShape,
  PathShape,
} from "@ohos.arkui.shape";
import { FrameNode } from "arkui.FrameNode";
import { default as resourceManager } from "@ohos.resourceManager";
import { LevelOrder } from "@ohos.promptAction";
import { SymbolGlyphModifier } from "../SymbolGlyphModifier";
import { TextModifier } from "../TextModifier";
import { default as EventHub } from "application.EventHub";
import { default as UIAbilityContext } from "application.UIAbilityContext";
import { CommonMethod, StateStyles, ArkCommonMethodComponent, CustomProperty } from "#generated";

import { AnimateParam } from "#generated";
import { ArkButtonComponent, ButtonConfiguration } from "#generated";
import { ArkCheckboxComponent, CheckBoxConfiguration } from "#generated";
import { ArkDataPanelComponent, DataPanelConfiguration } from "#generated";
import { ArkGaugeComponent, GaugeConfiguration } from "#generated";
import {
  ArkLoadingProgressComponent,
  LoadingProgressConfiguration,
} from "#generated";
import { ArkProgressComponent, ProgressConfiguration } from "#generated";
import { ArkRadioComponent, RadioConfiguration } from "#generated";
import { ArkRatingComponent, RatingConfiguration } from "#generated";
import { ArkSelectComponent, MenuItemConfiguration } from "#generated";
import { ArkSliderComponent, SliderConfiguration } from "#generated";
import { ArkTextClockComponent, TextClockConfiguration } from "#generated";
import { ArkTextTimerComponent, TextTimerConfiguration } from "#generated";
import { ArkToggleComponent, ToggleConfiguration, ContentModifier, GestureModifier } from "#generated";
import { pointer } from "@koalaui/interop";
import { ArkUIAniModule } from "arkui.ani"
import { InteropNativeModule } from "@koalaui/interop"

export function hookCheckBoxContentModifier(
  receiver: ArkCheckboxComponent,
  value?: ContentModifier<CheckBoxConfiguration>
) {}
export function hookDataPanelContentModifier(
  receiver: ArkDataPanelComponent,
  value?: ContentModifier<DataPanelConfiguration>
) {}
export function hookGaugeContentModifier(
  receiver: ArkGaugeComponent,
  value?: ContentModifier<GaugeConfiguration>
) {}
export function hookLoadingProgressContentModifier(
  receiver: ArkLoadingProgressComponent,
  value?: ContentModifier<LoadingProgressConfiguration>
) {}
export function hookProgressContentModifier(
  receiver: ArkProgressComponent,
  value?: ContentModifier<ProgressConfiguration>
) {}
export function hookSelectContentModifier(
  receiver: ArkSelectComponent,
  value?: ContentModifier<MenuItemConfiguration>
) {}
export function hookTextClockContentModifier(
  receiver: ArkTextClockComponent,
  value?: ContentModifier<TextClockConfiguration>
) {}
export function hookTextTimerContentModifier(
  receiver: ArkTextTimerComponent,
  value?: ContentModifier<TextTimerConfiguration>
) {}

export function hookId(component: object, value?: string) {}

export function hookGestureModifier(
  receiver: CommonMethod,
  value: GestureModifier | undefined
) {}

export function hookStateStyleImpl(
  receiver: CommonMethod,
  value: StateStyles | undefined
) {}

export class ElementIdToCustomProperties {
    constructor() { }
    static instance_: ElementIdToCustomProperties = new ElementIdToCustomProperties();
    static _elementIdToCustomProperties = new Map<number, Map<string, CustomProperty>>();
}
export function hookCustomPropertyImpl(component: ArkCommonMethodComponent, name: string, value: CustomProperty): void {
    const nodeId = component.getPeer().getId();
    if (!ElementIdToCustomProperties._elementIdToCustomProperties.has(nodeId)) {
        ElementIdToCustomProperties._elementIdToCustomProperties.set(nodeId, new Map<string, CustomProperty>());
    }
    const customProperties = ElementIdToCustomProperties._elementIdToCustomProperties.get(nodeId);
    if (customProperties) {
        customProperties.set(name, value);
    }
    const removeCallback: () => void = () => {
        ElementIdToCustomProperties._elementIdToCustomProperties.delete(nodeId);
    };
    const getCallback: (name: string) => string | undefined = (name: string) => {
        if (ElementIdToCustomProperties._elementIdToCustomProperties.has(nodeId)) {
            const customPropertiesGet = ElementIdToCustomProperties._elementIdToCustomProperties.get(nodeId);
            if (customPropertiesGet) {
                const propertyValue = customPropertiesGet.get(name);
                return propertyValue !== undefined ? JSON.stringify(propertyValue) : undefined;
            }
        }
        return undefined;
    };
    ArkUIAniModule._Common_SetCustomPropertyCallBack(component.getPeer().getPeerPtr(), removeCallback, getCallback);
}

export * from "./modifiers";
export * from "./content_modifiers/ContentModifierHooks";
