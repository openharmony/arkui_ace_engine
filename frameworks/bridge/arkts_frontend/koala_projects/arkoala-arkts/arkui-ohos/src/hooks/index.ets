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
import { ArkBaseNode } from '../typedNode/ArkBaseNode';
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
import { CommonMethod, StateStyles, ArkCommonMethodComponent, ArkCommonMethodPeer, CustomProperty, GestureMask, GestureType, Gesture, GestureGroup, UIGestureEvent, DragPreviewOptions, DragInteractionOptions, UniformDataType, DragEventInternal } from "#generated";
import { CommonMethodModifier } from "../CommonMethodModifier"
import { AnimateParam } from "#generated";
import { GestureModifier } from "#generated";
import { CanvasRenderer, ImageData, OffscreenCanvas, RenderingContextSettings, CanvasRenderingContext2D, OffscreenCanvasRenderingContext2D, VoidCallback } from "#generated";
import { pointer } from "@koalaui/interop";
import { ArkUIAniModule } from "arkui.ani"
import { InteropNativeModule } from "@koalaui/interop"
import { ErrorCallback } from "@ohos.base";
import { NavPathStack, NavigationModuleInfo, NavPathInfo, NavigationOptions, PopInfo, ArkNavigationComponent } from "../component/navigation"
import { NavDestinationContextInternal, RouteMapConfig } from "../component/navDestination"
import { PageMapBuilder } from "../component/builder";
import { NavigationOpsHandWritten } from "./NavigationOpsHandWritten";
import { ArkImageComponent, ResourceStr, ImageContent, ImageAIOptions, ArkTabsComponent  } from "#generated";
import { ArkWaterFlowComponent, WaterFlowOptions } from '#generated';
import { ImageOpsHandWritten } from "./ImageOpsHandWritten";
import { TabsOpsHandWritten } from "./TabsOpsHandWritten";
import { WaterFlowHandWritten } from './WaterFlowHandWritten';
import { ArkCanvasComponent, CanvasRenderingContext2D, DrawingRenderingContext } from "#generated";
import { ArkVideoComponent, ArkVideoPeer, VideoOptions } from "#generated";
import { ArkXComponentComponent, XComponentOptions, XComponentParameters, NativeXComponentParameters, XComponentController, ImageAnalyzerConfig } from "#generated";
import { CanvasOpsHandWritten } from "./CanvasOpsHandWritten";
import { VideoOpsHandWritten } from "./VideoOpsHandWritten";
import { XComponentOpsHandWritten } from "./XComponentOpsHandWritten";
import { PeerNode } from '../PeerNode';
import { int32 } from "@koalaui/common";
import { DrawModifier } from "arkui/component/common";
import { ComponentContent } from 'arkui.ComponentContent';
import { ArkTextPickerComponent, ArkTextPickerPeer, DividerOptions } from "#generated";
import { ArkSelectComponent, ArkSelectPeer, DividerOptions } from "#generated";
import { ArkSliderComponent, ArkSliderPeer, SliderExtender, SliderPrefixOptions, SliderSuffixOptions } from '#generated';
import { SelectExtender } from "#generated"
import { ArkWebComponent, JavaScriptProxy } from "#generated";
import { ArkListComponent, ArkListItemGroupComponent, ChildrenMainSize } from '#generated';
import { ListHandWritten } from "./ListHandWritten"
import { ArkWebComponent, JavaScriptProxy } from '#generated';
import { WebHandWritten } from "./WebHandWritten";

export function hookId(component: object, value?: string) {}

export function hookGesture(commonMethod: ArkCommonMethodComponent, gesture: GestureType | undefined, mask?: GestureMask): void {
    if (gesture instanceof Gesture) {
        let singleGesture = gesture as Gesture;
        singleGesture.setGesture(0, commonMethod.getPeer(), mask);
    } else {
        let gestureGroup = gesture as GestureGroup;
        gestureGroup.addGestureGroupToNode(0, commonMethod.getPeer(), mask)
    }
}

export function hookPriorityGesture(commonMethod: ArkCommonMethodComponent, gesture: GestureType | undefined, mask?: GestureMask): void {
    if (gesture instanceof Gesture) {
        let singleGesture = gesture as Gesture;
        singleGesture.setGesture(1, commonMethod.getPeer(), mask);
    } else {
        let gestureGroup = gesture as GestureGroup;
        gestureGroup.addGestureGroupToNode(1, commonMethod.getPeer(), mask)
    }
}

export function hookParallelGesture(commonMethod: ArkCommonMethodComponent, gesture: GestureType | undefined, mask?: GestureMask): void {
    if (gesture instanceof Gesture) {
        let singleGesture = gesture as Gesture;
        singleGesture.setGesture(2, commonMethod.getPeer(), mask);
    } else {
        let gestureGroup = gesture as GestureGroup;
        gestureGroup.addGestureGroupToNode(2, commonMethod.getPeer(), mask)
    }
}

export function hookGestureModifier(commonMethod: ArkCommonMethodComponent, value: GestureModifier | undefined): void {
    if (value === undefined) {
        let currentGestureEvent = commonMethod.getGestureEvent();
        if (currentGestureEvent !== undefined) {
            currentGestureEvent.clearGestures();
            commonMethod.setGestureEvent(undefined);    
        }
        return;
    }
    const value_casted = value as GestureModifier
    let gestureEvent: UIGestureEvent | undefined = undefined;
    if (commonMethod.getGestureEvent() === undefined) {
        gestureEvent = new UIGestureEvent();
        gestureEvent.setPeer(commonMethod.getPeer());
        commonMethod.setGestureEvent(gestureEvent);
    } else {
        gestureEvent = commonMethod.getGestureEvent();
    }
    gestureEvent!.clearGestures();
    value_casted.applyGesture(gestureEvent as UIGestureEvent);
}

export function hookAllowDrop(node: ArkCommonMethodComponent | ArkCommonMethodPeer, value: Array<UniformDataType> | null | Array<string> | undefined) : void {
  if (!node) {
      return
  }
  if (value === null) {
    if (node instanceof ArkCommonMethodComponent) {
      let nodeComponent = node as ArkCommonMethodComponent
      ArkUIAniModule._Drag_Set_AllowDrop_Null(nodeComponent.getPeer().getPeerPtr())
    } else if (node instanceof ArkCommonMethodPeer) {
      let nodePeer = node as ArkCommonMethodPeer
      ArkUIAniModule._Drag_Set_AllowDrop_Null(nodePeer.getPeerPtr())
    }
    return
  }
  let array = value as (Array<UniformDataType> | Array<string> | undefined)
  if (node instanceof ArkCommonMethodComponent) {
    let nodeComponent = node as ArkCommonMethodComponent
    ArkUIAniModule._Drag_Set_AllowDrop(nodeComponent.getPeer().getPeerPtr(), array)
  } else if (node instanceof ArkCommonMethodPeer) {
    let nodePeer = node as ArkCommonMethodPeer
    ArkUIAniModule._Drag_Set_AllowDrop(nodePeer.getPeerPtr(), array)
  }
}

export function hookDragPreviewOptions(node: ArkCommonMethodComponent | ArkCommonMethodPeer, value: DragPreviewOptions | undefined, options?: DragInteractionOptions) {
  if (node instanceof ArkCommonMethodComponent) {
    let nodeComponent = node as ArkCommonMethodComponent
    ArkUIAniModule._Drag_Set_DragPreviewOptions(nodeComponent.getPeer().getPeerPtr(), value, options)
  } else if (node instanceof ArkCommonMethodPeer) {
    let nodePeer = node as ArkCommonMethodPeer
    ArkUIAniModule._Drag_Set_DragPreviewOptions(nodePeer.getPeerPtr(), value, options)
  }
}

export function hookDragEventStartDataLoading(event: DragEventInternal, options: unifiedDataChannel.GetDataParams) :
  string | undefined {
  return ArkUIAniModule._DragEvent_Start_Data_Loading(event.peer!.ptr, options)
}

export function hookDragEventGetSummary(event: DragEventInternal) : unifiedDataChannel.Summary | undefined {
  return ArkUIAniModule._DragEvent_Get_Summary(event.peer!.ptr)
}

export function hookStateStyleImpl(
  receiver: ArkCommonMethodComponent,
  value: StateStyles | undefined
) {
    const UI_STATE_NORMAL = 0;
    const UI_STATE_PRESSED = 1;
    const UI_STATE_FOCUSED = 1 << 1;
    const UI_STATE_DISABLED = 1 << 2;
    const UI_STATE_SELECTED = 1 << 3;
    
    let curState = 0;
    if (value?.normal) {
        curState |= UI_STATE_NORMAL;
    }
    if (value?.pressed) {
        curState |= UI_STATE_PRESSED;
    }
    if (value?.focused) {
        curState |= UI_STATE_FOCUSED;
    }
    if (value?.disabled) {
        curState |= UI_STATE_DISABLED;
    }
    if (value?.selected) {
        curState |= UI_STATE_SELECTED;
    }

    let currentState = receiver.getPeer().getOrCreateStateStyleMutable(curState);
    if (currentState === undefined) {
      return;
    }

    let cm = new CommonMethodModifier();

    if (currentState.value === UI_STATE_NORMAL) {
        value?.normal?.(cm)
    }
    if (currentState.value & UI_STATE_PRESSED) {
        value?.clicked?.(cm)
        value?.pressed?.(cm)
    }
    if (currentState.value & UI_STATE_FOCUSED) {
        value?.focused?.(cm)
    }
    if (currentState.value & UI_STATE_DISABLED) {
        value?.disabled?.(cm)
    }
    if (currentState.value & UI_STATE_SELECTED) {
        value?.selected?.(cm)
    }

    cm.applyModifierPatch(receiver.getPeer())
}

export class ElementIdToCustomProperties {
    constructor() { }
    static instance_: ElementIdToCustomProperties = new ElementIdToCustomProperties();
    public static _elementIdToCustomProperties = new Map<number, Map<string, CustomProperty>>();
    public static _commonMethodModifierMap = new Map<CommonMethodModifier, Map<string, CustomProperty>>();
}
export function hookCustomPropertyImpl(component: ArkCommonMethodComponent | ArkCommonMethodPeer | ArkBaseNode,
    name: string, value: CustomProperty, modifier?: CommonMethodModifier | undefined): void {
    let commonMethodModifier: CommonMethodModifier;
    if (component instanceof ArkCommonMethodComponent || component instanceof ArkBaseNode) {
        const nodeId = component.getPeer().getId();
        if (!ElementIdToCustomProperties._elementIdToCustomProperties.has(nodeId)) {
            ElementIdToCustomProperties._elementIdToCustomProperties.set(nodeId, new Map<string, CustomProperty>());
        };
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
        const getAllCustomPropertiesCallback: () => string = () => {
            if (ElementIdToCustomProperties._elementIdToCustomProperties.has(nodeId)) {
                let allProperties: Record<string, CustomProperty> = new Record<string, CustomProperty>();
                const nodeCustomProperties = ElementIdToCustomProperties._elementIdToCustomProperties.get(nodeId);
                if (nodeCustomProperties === undefined || nodeCustomProperties === null) {
                    return ''
                }
                const allKeys = Array.from(nodeCustomProperties!.keys());
                for (let key of allKeys) {
                    try {
                        const propertyValue = nodeCustomProperties!.get(key);
                        if (propertyValue === undefined) {
                            allProperties.set(key, 'Unsupported Type')
                        } else {
                            allProperties.set(key, propertyValue)
                        }
                    } catch (e) {
                        allProperties.set(key, 'Unsupported Type')
                    }   
                }
                try {
                    return JSON.stringify(allProperties);
                } catch (e) {
                    return '';
                }
            }
            return '';
        };
        ArkUIAniModule._Common_SetCustomPropertyCallBack(component.getPeer().getPeerPtr(), removeCallback, getCallback,
            getAllCustomPropertiesCallback);
        return;
    } else {
        commonMethodModifier = (modifier as CommonMethodModifier)
    }

    if (!ElementIdToCustomProperties._commonMethodModifierMap.has(commonMethodModifier)) {
        return;
    }
    const commonMethodModifierMap = ElementIdToCustomProperties._commonMethodModifierMap.get(commonMethodModifier);

    let nodeId = -1;
    if (component instanceof ArkCommonMethodPeer) {
        let nodeComponent = component as ArkCommonMethodPeer
        nodeId = nodeComponent.getId();
    }
    if (!ElementIdToCustomProperties._elementIdToCustomProperties.has(nodeId)) {
        ElementIdToCustomProperties._elementIdToCustomProperties.set(nodeId, new Map<string, CustomProperty>());
    }
    const customProperties = ElementIdToCustomProperties._elementIdToCustomProperties.get(nodeId);
    if (commonMethodModifierMap) {
        if (customProperties) {
            commonMethodModifierMap.forEach((value, key)=>{
              customProperties.set(key, value);
            })
        }
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
    const getAllCustomPropertiesCallback: () => string = () => {
        if (ElementIdToCustomProperties._elementIdToCustomProperties.has(nodeId)) {
            let allProperties: Record<string, CustomProperty> = new Record<string, CustomProperty>();
            const nodeCustomProperties = ElementIdToCustomProperties._elementIdToCustomProperties.get(nodeId);
            if (nodeCustomProperties === undefined || nodeCustomProperties === null) {
                return ''
            }
            const allKeys = Array.from(nodeCustomProperties!.keys());
            for (let key of allKeys) {
                try {
                    const propertyValue = nodeCustomProperties!.get(key);
                    if (propertyValue === undefined) {
                        allProperties.set(key, 'Unsupported Type')
                    } else {
                        allProperties.set(key, propertyValue)
                    }
                } catch (e) {
                    allProperties.set(key, 'Unsupported Type')
                }   
            }
            try {
                return JSON.stringify(allProperties);
            } catch (e) {
                return '';
            }
        }
        return '';
    };
    if (component instanceof ArkCommonMethodPeer) {
        let nodeComponent = component as ArkCommonMethodPeer
        ArkUIAniModule._Common_SetCustomPropertyCallBack(nodeComponent.getPeerPtr(), removeCallback, getCallback,
            getAllCustomPropertiesCallback);
    }
}

export function hookCommonMethodModifierCustomProperty(component: CommonMethodModifier, name: string,
    value: CustomProperty): void {
    if (!ElementIdToCustomProperties._commonMethodModifierMap.has(component)) {
        ElementIdToCustomProperties._commonMethodModifierMap.set(component, new Map<string, CustomProperty>());
    }
    const customProperties = ElementIdToCustomProperties._commonMethodModifierMap.get(component);
    if (customProperties) {
        customProperties.set(name, value);
    }
}

export function hookDrawModifier(arkComponent: ArkCommonMethodComponent, value: DrawModifier | undefined): void {
  if (value === undefined) {
    return;
  }
  let classType: ClassType = (Type.of(value) as ClassType);
  let numberOfFun = classType.getMethodsNum();
  let flag: int32 = 0;
  for (let i = 0; i < numberOfFun; i++) {
    if (classType.getMethod(i)?.getName() === "drawFront") {
      flag |= (1 << 0);
    } else if (classType.getMethod(i)?.getName() === "drawContent") {
      flag |= (1 << 1);
    } else if (classType.getMethod(i)?.getName() === "drawBehind") {
      flag |= (1 << 2);
    } else if (classType.getMethod(i)?.getName() === "drawForeground") {
      flag |= (1 << 3);
    }
  }
  if (flag) {
    ArkUIAniModule._SetDrawModifier(arkComponent.getPeer().getPeerPtr(), flag, value!);
    value.weakRefOfPeerNode = new WeakRef<PeerNode>(arkComponent.getPeer());
  }
}

export * from "./modifiers";
export * from "./content_modifiers/ContentModifierHooks";
export * from "./theme";
export { NavDestinationBuilder, NavigationRouterMap } from "./NavigationOpsHandWritten";

export function hookImageSetImageOptions(component: ArkImageComponent, src: image.PixelMap | ResourceStr | DrawableDescriptor | ImageContent, imageAIOptions?: ImageAIOptions): void {
    ImageOpsHandWritten.hookImageSetImageOptionsImpl(component, src, imageAIOptions);
}

export function hookTabsApplyAttributesFinish(node: ArkTabsComponent): void  {
    TabsOpsHandWritten.hookTabsApplyAttributesFinish(node);
}

export function hookSetNavigationOptions(component: ArkNavigationComponent, pathInfos?: NavPathStack, moduleInfo?: NavigationModuleInfo): void {
  NavigationOpsHandWritten.hookSetNavigationOptionsImpl(component, pathInfos, moduleInfo);
}

export function hookSetNavDestination(component: ArkNavigationComponent, value: PageMapBuilder | undefined): void {
  NavigationOpsHandWritten.hookSetNavDestinationImpl(component, value);
}

export function hookGetConfigInRouteMap(info: NavDestinationContextInternal): RouteMapConfig | undefined {
  return NavigationOpsHandWritten.hookGetRouteConfigImpl(info);
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
export function convertDimensionStrToNumber(value: string, density: number): number {
    const regex : RegExp = new RegExp('(-?\\d+\\.?\\d+)(px|vp)?$', 'i')
    const match: RegExpMatchArray | null = value.match(regex)
    if (!match) {
        return 0
    }
    let numericValue : number = 0
    let unitPart : string = ''
    if (match.length > 1 && match[1] !== undefined) {
        numericValue = Number.parseFloat(match[1] as string);
        return numericValue
    }
    if (match.length > 2 && match[2] !== undefined) {
        unitPart = match[2] as string;
    }
    if (unitPart === 'px') {
        return numericValue;
    }
    if (unitPart === 'vp' || !unitPart) {
        return numericValue * density;
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
export function parseImageData(value: number | string, density: number): number {
    let ret_val: number
    if (value instanceof string) {
        ret_val = convertDimensionStrToNumber(value as string, density)
    } else {
        let value_casted = value as number
        ret_val = value_casted * density
    }
    return ret_val
}
export function hookPutImageData(peerPtr: CanvasRenderer,
    imagedata: ImageData, dx: number | string, dy: number | string): void {
    const density = getCanvasDensity(peerPtr)
    ArkUIAniModule._CanvasRenderer_PutImageData0(peerPtr.peer!.ptr, imagedata.data,
        parseImageData(dx, density), parseImageData(dy, density), imagedata.width as int, imagedata.height as int)
}
export function hookPutImageData(peerPtr: CanvasRenderer, imagedata: ImageData,
    dx: number | string, dy: number | string, dirtyX: number | string, dirtyY: number | string,
    dirtyWidth: number | string, dirtyHeight: number | string): void {
    const density = getCanvasDensity(peerPtr)
    ArkUIAniModule._CanvasRenderer_PutImageData1(peerPtr.peer!.ptr, imagedata.data,
        parseImageData(dx, density), parseImageData(dy, density),
        imagedata.width as int, imagedata.height as int,
        parseImageData(dirtyX, density), parseImageData(dirtyY, density),
        parseImageData(dirtyWidth, density), parseImageData(dirtyHeight, density))
}
export function hookGetContext(
  peerPtr: OffscreenCanvas,
  contextType: string,
  options: RenderingContextSettings
): OffscreenCanvasRenderingContext2D {
  return peerPtr.getContext2d(options)
}
let attachCallbackId: int = 0;
let detachCallbackId: int = 0;
const attachCallbackMap: Map<VoidCallback, int> = new Map<VoidCallback, int>()
const detachCallbackMap: Map<VoidCallback, int> = new Map<VoidCallback, int>()
export function registerAttach(peerPtr: CanvasRenderingContext2D, callback: VoidCallback): void {
  let id: int = -1
  if (attachCallbackMap.has(callback)) {
    let res = attachCallbackMap.get(callback)
    if (res !== undefined) {
      id = res as int
    }
  } else {
    id = attachCallbackId
    attachCallbackMap.set(callback, attachCallbackId++)    
  }
  ArkUIAniModule._CanvasRenderingContext_setAttachCallbackId(peerPtr.peer!.ptr, id)
}
export function unregisterAttach(peerPtr: CanvasRenderingContext2D, callback?: VoidCallback): void {
  if (callback === undefined) {
    attachCallbackMap.clear()
    return
  }
  let id: int = -1
  if (attachCallbackMap.has(callback)) {
    let res = attachCallbackMap.get(callback)
    if (res !== undefined) {
      id = res as int
    }
    attachCallbackMap.delete(callback)
  }
  ArkUIAniModule._CanvasRenderingContext_setAttachCallbackId(peerPtr.peer!.ptr, id)
}
export function registerDetach(peerPtr: CanvasRenderingContext2D, callback: VoidCallback): void {
  let id: int = -1
  if (detachCallbackMap.has(callback)) {
    let res = detachCallbackMap.get(callback)
    if (res !== undefined) {
      id = res as int
    }
  } else {
    id = detachCallbackId
    detachCallbackMap.set(callback, detachCallbackId++)    
  }
  ArkUIAniModule._CanvasRenderingContext_setDetachCallbackId(peerPtr.peer!.ptr, id)
}
export function unregisterDetach(peerPtr: CanvasRenderingContext2D, callback?: VoidCallback): void {
  if (callback === undefined) {
    detachCallbackMap.clear()
    return
  }
  let id: int = -1
  if (detachCallbackMap.has(callback)) {
    let res = detachCallbackMap.get(callback)
    if (res !== undefined) {
      id = res as int
    }
    detachCallbackMap.delete(callback)
  }
  ArkUIAniModule._CanvasRenderingContext_setDetachCallbackId(peerPtr.peer!.ptr, id)
}

export function hookSetCanvasOptions(component: ArkCanvasComponent,
  context?: CanvasRenderingContext2D | DrawingRenderingContext, imageAIOptions?: ImageAIOptions): void {
  CanvasOpsHandWritten.hookSetCanvasOptionsImpl(component, context, imageAIOptions);
}

export function hookCanvasStartImageAnalyzer(
  context: CanvasRenderingContext2D, config: ImageAnalyzerConfig): Promise<void> {
  return CanvasOpsHandWritten.hookCanvasStartImageAnalyzerImpl(context, config);
}

export function hookSetVideoOptions(component: ArkVideoComponent, value: VideoOptions): void {
  VideoOpsHandWritten.hookSetVideoOptionsImpl(component, value);
}

export function hookVideoAnalyzerConfig(
  component: ArkVideoComponent | ArkVideoPeer, config: ImageAnalyzerConfig | undefined): void {
  VideoOpsHandWritten.hookSetVideoAnalyzerConfigImpl(component, config);
}

export function hookSetXComponentOptions(component: ArkXComponentComponent,
  params: XComponentParameters | XComponentOptions | NativeXComponentParameters): void {
  XComponentOpsHandWritten.hookSetXComponentOptionsImpl(component, params);
}

export function hookXComponentStartImageAnalyzer(
  controller: XComponentController, config: ImageAnalyzerConfig): Promise<void> {
  return XComponentOpsHandWritten.hookXComponentStartImageAnalyzerImpl(controller, config);
}

export function hookSelectSetDividerMethod(
  receiver: ArkSelectComponent | ArkSelectPeer, value?: DividerOptions | null | undefined): void {
    const selectPeer: ArkSelectPeer = receiver instanceof ArkSelectComponent ? (receiver as ArkSelectComponent).getPeer() :
       (receiver as ArkSelectPeer);
    if (!selectPeer) {
      return;
    }
    let value_casted: DividerOptions | undefined;
    if (value === null) {
      value_casted = {
        strokeWidth: '0px',
        startMargin: 0,
        endMargin: 0,
        color: '#00000000',
      }
    } else {
      value_casted = value as (DividerOptions | undefined)
    }
    SelectExtender.setDivider(selectPeer.peer.ptr, value_casted)
}

export function hookSliderSetPrefixMethod(node: ArkSliderComponent | ArkSliderPeer,
  content: ComponentContent | undefined, options?: SliderPrefixOptions | undefined): void {
    const sliderPeer: ArkSliderPeer = node instanceof ArkSliderComponent ? (node as ArkSliderComponent).getPeer() :
       (node as ArkSliderPeer);
    if (!sliderPeer || !sliderPeer.peer || !sliderPeer.peer.ptr) {
      return;
    }
    let ptr: KPointer = 0;
    if (content != undefined && content.getNodePtr() !== undefined) {
        ptr = content.getNodePtr() as KPointer;
    }
    let valueCasted: SliderPrefixOptions | undefined;
    if (options === null || options === undefined) {
      valueCasted = undefined;
    } else {
        valueCasted = options as SliderPrefixOptions;
    }
    SliderExtender.setPrefix(sliderPeer.peer.ptr, ptr, valueCasted);
}

export function hookSliderSetSuffixMethod(node: ArkSliderComponent | ArkSliderPeer,
  content: ComponentContent | undefined, options?: SliderSuffixOptions | undefined): void {
    const sliderPeer: ArkSliderPeer = node instanceof ArkSliderComponent ? (node as ArkSliderComponent).getPeer() :
       (node as ArkSliderPeer);
    if (!sliderPeer || !sliderPeer.peer || !sliderPeer.peer.ptr) {
      return;
    }
    let ptr: KPointer = 0;
    if (content != undefined && content.getNodePtr() !== undefined) {
        ptr = content.getNodePtr() as KPointer;
    } 
    let valueCasted: SliderSuffixOptions | undefined;
    if (options === null || options === undefined) {
      valueCasted = undefined;
    } else {
        valueCasted = options as SliderSuffixOptions;
    }
    SliderExtender.setSuffix(sliderPeer.peer.ptr, ptr, valueCasted);
}

export function hookWaterFlowOptionsImpl(node: ArkWaterFlowComponent, options: WaterFlowOptions | undefined): void {
  WaterFlowHandWritten.hookWaterFlowOptionsImpl(node, options)
}

export function hookTextPickerDivider(receiver: ArkTextPickerComponent | ArkTextPickerPeer,
  value: DividerOptions | null | undefined): void {
  const peer: ArkTextPickerPeer =
    receiver instanceof ArkTextPickerComponent ? (receiver as ArkTextPickerComponent).getPeer() :
      (receiver as ArkTextPickerPeer);
  if (!peer) {
    return;
  }
  if (value === null) {
    const HIDDEN_DIVIDER: DividerOptions = {
      strokeWidth: '0px',
      startMargin: 0,
      endMargin: 0,
      color: '#00000000',
    }
    peer.setDividerAttribute(HIDDEN_DIVIDER)
    return
  }

  const value_casted = value as (DividerOptions | null | undefined)
  peer.setDividerAttribute(value_casted)
}

export function hookListChildrenMainSizeImpl(node: ArkListComponent, value: ChildrenMainSize | undefined): void {
  ListHandWritten.hookListChildrenMainSizeImpl(node, value)
}

export function hookListItemGroupChildrenMainSizeImpl(node: ArkListItemGroupComponent, value: ChildrenMainSize | undefined): void {
  ListHandWritten.hookListItemGroupChildrenMainSizeImpl(node, value)
}

export function hookJavaScriptProxy(
  component: ArkWebComponent, value: JavaScriptProxy | undefined): void {
  WebHandWritten.hookJavaScriptProxyImpl(component, value);
}

export function hookVideoOnError(
  component: ArkVideoComponent | ArkVideoPeer, value: VoidCallback | ErrorCallback | undefined): void {
    VideoOpsHandWritten.hookSetVideoOnErrorImpl(component, value);
}
