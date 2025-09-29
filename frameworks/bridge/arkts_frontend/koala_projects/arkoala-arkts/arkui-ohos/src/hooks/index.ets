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
import { GestureModifier } from "#generated";
import { pointer } from "@koalaui/interop";
import { ArkUIAniModule } from "arkui.ani"
import { InteropNativeModule } from "@koalaui/interop"
import { NavPathStack, NavPathInfo, NavigationOptions, PopInfo, ArkNavigationComponent } from "../component/navigation"
import { PathStackUtils } from "../base/ArkNavPathStack"
import { PageMapBuilder } from "../component/builder";
import { NavigationOpsHandWritten } from "./NavigationOpsHandWritten";

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

export function hookPushPathMethod(pathStack: NavPathStack, info: NavPathInfo, animated?: boolean | NavigationOptions | undefined): void {
  PathStackUtils.pushPath(pathStack, info, animated);
}

export function hookPushPathByNameMethod(pathStack: NavPathStack, name: string, param: Object | null | undefined, onPop?: ((parameter: PopInfo) => void) | boolean | undefined, animated?: boolean): void {
  PathStackUtils.pushPathByName(pathStack, name, param, onPop, animated);
}
export function hookReplacePathMethod(pathStack: NavPathStack, info: NavPathInfo, animated?: boolean | NavigationOptions | undefined): void {
  PathStackUtils.replacePath(pathStack, info, animated);
}
export function hookReplacePathByNameMethod(pathStack: NavPathStack, name: string, param: Object, animated?: boolean): void {
  PathStackUtils.replacePathByName(pathStack, name, param, animated);
}
export function hookPopMethod(pathStack: NavPathStack, result?: boolean | undefined | Object, animated?: boolean): NavPathInfo | undefined {
  return PathStackUtils.pop(pathStack, result, animated);
}
export function hookPopToNameMethod(pathStack: NavPathStack, name: string, result?: boolean | undefined | Object, animated?: boolean): number {
  return PathStackUtils.popToName(pathStack, name, result, animated);
}
export function hookPopToIndexMethod(pathStack: NavPathStack, index: number, result?: boolean | undefined | Object, animated?: boolean) {
  PathStackUtils.popToIndex(pathStack, index, result, animated);
}
export function hookGetParamByIndexMethod(pathStack: NavPathStack, index: number): Object | undefined {
  return PathStackUtils.getParamByIndex(pathStack, index);
}
export function hookGetParamByNameMethod(pathStack: NavPathStack, name: string): Array<Object | null | undefined> {
  return PathStackUtils.getParamByName(pathStack, name);
}
export function hookSetNavigationOptions(component: ArkNavigationComponent, pathInfos?: NavPathStack): void {
  NavigationOpsHandWritten.hookSetNavigationOptionsImpl(component, pathInfos);
}

export function hookSetNavDestination(component: ArkNavigationComponent, value: PageMapBuilder | undefined): void {
  NavigationOpsHandWritten.hookSetNavDestinationImpl(component, value);
}