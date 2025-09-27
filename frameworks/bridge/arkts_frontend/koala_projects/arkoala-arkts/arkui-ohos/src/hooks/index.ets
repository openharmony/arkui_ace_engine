import { runtimeType, RuntimeType, KPointer } from "@koalaui/interop";
import { default as image } from "@ohos.multimedia.image";
import { ColorMetrics, DrawContext, LengthMetrics, LengthMetricsUnit, Size } from "arkui.Graphics";
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
import { CanvasRenderer, ImageData, OffscreenCanvas, RenderingContextSettings, CanvasRenderingContext2D, Callback } from "#generated";
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

const DIFF: number = 1e-10
const int_MAX: number = 2147483647
const PIXEL_SIZE: int = 4
export function getCanvasDensity(peerPtr: CanvasRenderer): number {
    return ArkUIAniModule._CanvasRenderer_GetCanvasDensity(peerPtr.peer!.ptr)
}
export function getSystemDensity(): number {
    return ArkUIAniModule._GetSystemDensity()
}
export function convertDimensionStrToNumber(value: string): number {
    const regex : RegExp = new RegExp('(-?\\d+\\.?\\d+)(px|vp)?$', 'i')
    const match: RegExpMatchArray | null = value.match(regex)
    if (!match) {
        return 0
    }
    let numericValue : number = 0
    let unitPart : string = ''
    if (match.length > 1) {
        numericValue = Number.parseFloat(match[1] as string);
    }
    if (match.length > 2) {
        unitPart = match[2] as string;
    }
    if (unitPart === 'px' || !unitPart) {
        return numericValue;
    }
    if (unitPart === 'vp') {
        return numericValue * getSystemDensity();
    }
    return 0;
}
export function hookCreateImageData(peerPtr: CanvasRenderer, sw: number, sh: number): ImageData {
    const density = getCanvasDensity(peerPtr)
    const width_value: number = sw * density + DIFF
    const height_value: number = sh * density + DIFF
    if ((width_value > int_MAX) || (height_value > int_MAX) ||
        ((width_value > 0) && (height_value > (int_MAX / width_value / PIXEL_SIZE)))) {
        const resObj = new ImageData(0, 0)
        return resObj
    }
    const width_cast: int = width_value as int
    const height_cast: int = height_value as int
    const length: int = width_cast * height_cast * PIXEL_SIZE
    const arrayBuffer: ArrayBuffer = new ArrayBuffer(length)
    const uint8View = new Uint8Array(arrayBuffer)
    for (let i = 0; i < length; i++) {
        uint8View[i] = 0xffffffff
    }
    const data: Uint8ClampedArray = new Uint8ClampedArray(arrayBuffer)
    const resObj: ImageData = new ImageData(width_cast, height_cast, data, LengthMetricsUnit.PX)
    return resObj
}
export function hookCreateImageData(peerPtr: CanvasRenderer, imagedata: ImageData): ImageData {
    const width_cast: int = imagedata.width as int
    const height_cast: int = imagedata.height as int
    const length: int = width_cast * height_cast * PIXEL_SIZE
    const arrayBuffer: ArrayBuffer = new ArrayBuffer(length)
    const uint8View = new Uint8Array(arrayBuffer)
    for (let i = 0; i < length; i++) {
        uint8View[i] = 0xffffffff
    }
    const data: Uint8ClampedArray = new Uint8ClampedArray(arrayBuffer)
    const resObj: ImageData = new ImageData(width_cast, height_cast, data, LengthMetricsUnit.PX)
    return resObj
}
export function hookGetImageData(peerPtr: CanvasRenderer, sx: number, sy: number, sw: number, sh: number): ImageData {
    const data: Uint8ClampedArray = ArkUIAniModule._CanvasRenderer_GetImageData(peerPtr.peer!.ptr, sx, sy, sw, sh)
    const density = getCanvasDensity(peerPtr)
    const width_value: number = sw * density + DIFF
    const height_value: number = sh * density + DIFF
    if ((width_value > int_MAX) || (height_value > int_MAX) ||
        ((width_value > 0) && (height_value > (int_MAX / width_value / PIXEL_SIZE)))) {
        const resObj = new ImageData(0, 0)
        return resObj
    }
    const width_cast: int = width_value as int
    const height_cast: int = height_value as int
    const resObj: ImageData = new ImageData(width_cast, height_cast, data, LengthMetricsUnit.PX)
    return resObj
}
export function hookPutImageData(peerPtr: CanvasRenderer, imagedata: ImageData, dx: number | string, dy: number | string): void {
    let dx_type: int = RuntimeType.UNDEFINED
    let dy_type: int = RuntimeType.UNDEFINED
    dx_type = runtimeType(dx)
    dy_type = runtimeType(dy)
    let dx_val: number = (dx_type == RuntimeType.STRING) ? convertDimensionStrToNumber(dx as string) : (dx as number)
    let dy_val: number = (dy_type == RuntimeType.STRING) ? convertDimensionStrToNumber(dy as string) : (dy as number)
    ArkUIAniModule._CanvasRenderer_PutImageData0(peerPtr.peer!.ptr, imagedata.data, dx_val, dy_val, imagedata.width as int, imagedata.height as int)
}
export function hookPutImageData(peerPtr: CanvasRenderer, imagedata: ImageData, dx: number | string, dy: number | string, dirtyX: number | string, dirtyY: number | string, dirtyWidth: number | string, dirtyHeight: number | string): void {

    let dx_type: int = RuntimeType.UNDEFINED
    let dy_type: int = RuntimeType.UNDEFINED
    let dirtyX_type: int = RuntimeType.UNDEFINED
    let dirtyY_type: int = RuntimeType.UNDEFINED
    let dirtyWidth_type: int = RuntimeType.UNDEFINED
    let dirtyHeight_type: int = RuntimeType.UNDEFINED
    dx_type = runtimeType(dx)
    dy_type = runtimeType(dy)
    dirtyX_type = runtimeType(dirtyX)
    dirtyY_type = runtimeType(dirtyY)
    dirtyWidth_type = runtimeType(dirtyWidth)
    dirtyHeight_type = runtimeType(dirtyHeight)
    let dx_val: number = (dx_type == RuntimeType.STRING) ? convertDimensionStrToNumber(dx as string) : (dx as number)
    let dy_val: number = (dy_type == RuntimeType.STRING) ? convertDimensionStrToNumber(dy as string) : (dy as number)
    let dirtyX_val: number = (dirtyX_type == RuntimeType.STRING) ? convertDimensionStrToNumber(dirtyX as string) : (dirtyX as number)
    let dirtyY_val: number = (dirtyY_type == RuntimeType.STRING) ? convertDimensionStrToNumber(dirtyY as string) : (dirtyY as number)
    let dirtyWidth_val: number = (dirtyWidth_type == RuntimeType.STRING) ? convertDimensionStrToNumber(dirtyWidth as string) : (dirtyWidth as number)
    let dirtyHeight_val: number = (dirtyHeight_type == RuntimeType.STRING) ? convertDimensionStrToNumber(dirtyHeight as string) : (dirtyHeight as number)
    ArkUIAniModule._CanvasRenderer_PutImageData1(peerPtr.peer!.ptr, imagedata.data, dx_val, dy_val, imagedata.width as int, imagedata.height as int, dirtyX_val, dirtyY_val, dirtyWidth_val, dirtyHeight_val)
}
export function hookGetContext(peerPtr: OffscreenCanvas, contextType: string, options: RenderingContextSettings)
{
  return peerPtr.getContext2d(options)
}
export function hookOn(peerPtr: CanvasRenderingContext2D, type: string, callback_: Callback<void>): void {
    if (type == "onAttach") {
        peerPtr.onOnAttach(callback_)
    } else if (type == "onDetach") {
        peerPtr.onOnDetach(callback_)
    }
}
export function hookOff(peerPtr: CanvasRenderingContext2D, type: string, callback_?: Callback<void>): void {
    if (type == "offAttach") {
        peerPtr.offOnAttach(callback_)
    } else if (type == "offDetach") {
        peerPtr.offOnDetach(callback_)
    }
}