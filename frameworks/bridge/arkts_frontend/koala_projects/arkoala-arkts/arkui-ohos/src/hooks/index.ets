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
import { CommonMethod, StateStyles, ArkCommonMethodComponent, ArkCommonMethodPeer, CustomProperty, GestureMask, GestureType, Gesture, GestureGroup, UIGestureEvent, DragPreviewOptions, DragInteractionOptions, UniformDataType, DragEventInternal } from "#generated";
import { CommonMethodModifier } from "../CommonMethodModifier"
import { AnimateParam } from "#generated";
import { GestureModifier } from "#generated";
import { pointer } from "@koalaui/interop";
import { ArkUIAniModule } from "arkui.ani"
import { InteropNativeModule } from "@koalaui/interop"
import { NavPathStack, NavigationModuleInfo, NavPathInfo, NavigationOptions, PopInfo, ArkNavigationComponent } from "../component/navigation"
import { PathStackUtils } from "../base/ArkNavPathStack"
import { PageMapBuilder } from "../component/builder";
import { NavigationOpsHandWritten } from "./NavigationOpsHandWritten";
import { ArkImageComponent, ResourceStr, ImageContent, ImageAIOptions, ArkTabsComponent  } from "#generated";
import { ArkWaterFlowComponent, WaterFlowOptions } from "#generated";
import { ImageOpsHandWritten } from "./ImageOpsHandWritten";
import { TabsOpsHandWritten } from "./TabsOpsHandWritten";
import { WaterFlowHandWritten } from "./WaterFlowHandWritten";
import { ArkCanvasComponent, CanvasRenderingContext2D, DrawingRenderingContext } from "#generated";
import { ArkVideoComponent, VideoOptions } from "#generated";
import { ArkXComponentComponent, XComponentOptions, XComponentParameters, NativeXComponentParameters, XComponentController, ImageAnalyzerConfig } from "#generated";
import { CanvasOpsHandWritten } from "./CanvasOpsHandWritten";
import { VideoOpsHandWritten } from "./VideoOpsHandWritten";
import { XComponentOpsHandWritten } from "./XComponentOpsHandWritten";
import { PeerNode } from '../PeerNode';
import { int32 } from "@koalaui/common";
import { DrawModifier } from "arkui/component/common";
import { ArkSelectComponent, ArkSelectPeer, DividerOptions } from "#generated";
import { SelectExtender } from "#generated"
import { ArkWebComponent, JavaScriptProxy } from "#generated";
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

export function hookAllowDrop(node: ArkCommonMethodComponent | ArkCommonMethodPeer, value: Array<UniformDataType> | null | undefined) : void {
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
  let array = value as (Array<UniformDataType> | undefined)
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

export function hookDragEventStartDataLoading(event: DragEventInternal, options: unifiedDataChannel.GetDataParams) : string {
  return ArkUIAniModule._DragEvent_Start_Data_Loading(event.peer!.ptr, options)
}

export function hookDragEventGetSummary(event: DragEventInternal) : unifiedDataChannel.Summary {
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
    const getAllCustomPropertiesCallback: () => string = () => {
        if (ElementIdToCustomProperties._elementIdToCustomProperties.has(nodeId)) {
            let allProperties: Record<string, CustomProperty> = new Record<string, CustomProperty>();
            const nodeCustomProperties = ElementIdToCustomProperties._elementIdToCustomProperties.get(nodeId);
            if (nodeCustomProperties === undefined || nodeCustomProperties === null) {
                return ""
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
                return "";
            }
        }
        return "";
    };
    ArkUIAniModule._Common_SetCustomPropertyCallBack(component.getPeer().getPeerPtr(), removeCallback, getCallback,
        getAllCustomPropertiesCallback);
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
export function hookPopToNameMethod(pathStack: NavPathStack, name: string, result?: boolean | undefined | Object, animated?: boolean): int32 {
  return PathStackUtils.popToName(pathStack, name, result, animated);
}
export function hookPopToIndexMethod(pathStack: NavPathStack, index: int32, result?: boolean | undefined | Object, animated?: boolean) {
  PathStackUtils.popToIndex(pathStack, index, result, animated);
}
export function hookGetParamByIndexMethod(pathStack: NavPathStack, index: int32): Object | undefined {
  return PathStackUtils.getParamByIndex(pathStack, index);
}
export function hookGetParamByNameMethod(pathStack: NavPathStack, name: string): Array<Object | null | undefined> {
  return PathStackUtils.getParamByName(pathStack, name);
}
export function hookSetNavigationOptions(component: ArkNavigationComponent, pathInfos?: NavPathStack, moduleInfo?: NavigationModuleInfo): void {
  NavigationOpsHandWritten.hookSetNavigationOptionsImpl(component, pathInfos, moduleInfo);
}

export function hookSetNavDestination(component: ArkNavigationComponent, value: PageMapBuilder | undefined): void {
  NavigationOpsHandWritten.hookSetNavDestinationImpl(component, value);
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

export function hookVideoAnalyzerConfig(component: ArkVideoComponent, config: ImageAnalyzerConfig | undefined): void {
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

export function hookWaterFlowOptionsImpl(node: ArkWaterFlowComponent, options: WaterFlowOptions | undefined): void {
  WaterFlowHandWritten.hookWaterFlowOptionsImpl(node, options)
}

export function hookJavaScriptProxy(
  component: ArkWebComponent, value: JavaScriptProxy | undefined): void {
  WebHandWritten.hookJavaScriptProxyImpl(component, value);
}
