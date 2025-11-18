import { int32 } from "@koalaui/common";
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
import {
  DrawableDescriptor,
  PixelMapDrawableDescriptor,
  LayeredDrawableDescriptor,
  AnimatedDrawableDescriptor
} from "@ohos.arkui.drawableDescriptor";
import {
  RectShape,
  CircleShape,
  EllipseShape,
  PathShape,
} from "@ohos.arkui.shape";
import { FrameNode } from "arkui.FrameNode";
import { RenderNode } from "arkui.RenderNode";
import { default as resourceManager } from "@ohos.resourceManager";
import { LevelOrder } from "@ohos.promptAction";
import { SymbolGlyphModifier } from "../SymbolGlyphModifier";
import { TextModifier } from "../TextModifier";
import { ImageModifier } from "../ImageModifier";
import { default as EventHub } from "application.EventHub";
import { default as UIAbilityContext } from "application.UIAbilityContext";
import { CommonMethod, StateStyles } from "#generated";
import { ArkUIAniModule } from "arkui.ani"
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
import { ArkToggleComponent, ToggleConfiguration } from "#generated";
import { pointer } from "@koalaui/interop";
import { Scene } from "graphics3d.Scene"
import { Animation, Environment } from "graphics3d.SceneResources"
import { UIContextUtil } from 'arkui/base/UIContextUtil';
import { UIContextImpl } from 'arkui/base/UIContextImpl';
import { int32 } from '@koalaui/common';
import { FrameNodeUtils, FrameNodeInternal } from './../FrameNode';
import { toPeerPtr } from '@koalaui/interop';
import { ComponentContentBase } from 'arkui/ComponentContent';
import { applySymbolGlyphModifierToNode, applyTextModifierToNode } from "./../ApplyModifierToNode"

export namespace extractors {
  export function toImagePixelMapPtr(value: image.PixelMap): KPointer {
    return ArkUIAniModule._Extractors_ToImagePixelMapPtr(value);
  }
  export function fromImagePixelMapPtr(ptr: KPointer): image.PixelMap {
    return ArkUIAniModule._Extractors_FromImagePixelMapPtr(ptr);
  }

  export function toColorMetricsPtr(value: ColorMetrics): KPointer {
    return 123;
  }
  export function fromColorMetricsPtr(ptr: KPointer): ColorMetrics {
    const x: Object = {};
    return x as ColorMetrics;
  }

  export function toComponentContentBasePtr(value: ComponentContentBase): KPointer {
    return 123;
  }
  export function fromComponentContentBasePtr(ptr: KPointer): ComponentContentBase {
    const x: Object = {};
    return x as ComponentContentBase;
  }

  export function toDrawContextPtr(ptr: DrawContext): KPointer {
    return 123;
  }
  export function fromDrawContextPtr(ptr: KPointer): DrawContext {
    return ArkUIAniModule._Extractors_FromDrawContextPtr(ptr);
  }

  export function toLengthMetricsPtr(ptr: LengthMetrics): KPointer {
    return 123;
  }
  export function fromLengthMetricsPtr(ptr: KPointer): LengthMetrics {
    const x: Object = {};
    return x as LengthMetrics;
  }

  export function toNodeControllerPtr(value: NodeController): KPointer {
    return 123;
  }
  export function fromNodeControllerPtr(ptr: KPointer): NodeController {
    const x: Object = {};
    return x as NodeController;
  }

  export function toRenderNodePtr(value: RenderNode): KPointer {
    return value.getPeer()!.ptr;
  }
  export function fromRenderNodePtr(ptr: KPointer): RenderNode {
    const x: Object = {};
    return x as RenderNode;
  }

  export function toFrameNodePtr(value: FrameNode): KPointer {
    return toPeerPtr(value);
  }
  export function fromFrameNodePtr(ptr: KPointer): FrameNode {
    let node = FrameNodeUtils.searchNodeInRegisterProxy(ptr);
    if (!node) {
        node = FrameNodeInternal.fromPtr(ptr);
    }
    return node as FrameNode;
  }

  // should be investigated and removed
  // begin
  export function toSymbolGlyphModifierPtr(
    value: SymbolGlyphModifier
  ): KPointer {
    let callBack = (node: KPointer) => {
      applySymbolGlyphModifierToNode(value, node);
    };
    return ArkUIAniModule._Extractors_ToSymbolGlyphModifierPtr(callBack, value);
  }
  export function fromSymbolGlyphModifierPtr(
    ptr: KPointer
  ): SymbolGlyphModifier {
    return ArkUIAniModule._Extractors_FromSymbolGlyphModifierPtr(ptr);
  }

  export function toTextModifierPtr(value: TextModifier): KPointer {
    let callBack = (node: KPointer) => {
      applyTextModifierToNode(value, node);
    };
    return ArkUIAniModule._Extractors_ToTextModifierPtr(callBack, value);
  }
  export function fromTextModifierPtr(ptr: KPointer): TextModifier {
    return ArkUIAniModule._Extractors_FromTextModifierPtr(ptr);
  }

  export function toImageModifierPtr(value: ImageModifier): KPointer {
    throw new Error("toImageModifierPtr is not implemented.")
  }
  export function fromImageModifierPtr(ptr: KPointer): ImageModifier {
    throw new Error("fromImageModifierPtr is not implemented.")
  }
  // end

  export function toCurvesICurvePtr(value: curves.ICurve): KPointer {
    return ArkUIAniModule._Extractors_ToICurvePtr(value);
  }
  export function fromCurvesICurvePtr(ptr: KPointer): curves.ICurve {
    throw new Error("fromCurvesICurvePtr is not implemented.")
  }

  export function toMatrix4Matrix4TransitPtr(
    value: matrix4.Matrix4Transit
  ): KPointer {
    return ArkUIAniModule._Extractors_ToMatrix4TransitPtr(value);
  }
  export function fromMatrix4Matrix4TransitPtr(
    ptr: KPointer
  ): matrix4.Matrix4Transit {
    throw new Error("fromMatrix4Matrix4TransitPtr is not implemented.")
  }

  export function toDrawingCanvasPtr(value: drawing.Canvas): KPointer {
    return ArkUIAniModule._Extractors_ToDrawingCanvasPtr(value);
  }
  export function fromDrawingCanvasPtr(ptr: KPointer): drawing.Canvas {
    const x: Object = ArkUIAniModule._Extractors_FromDrawingCanvasPtr(ptr);
    return x as drawing.Canvas;
  }

  export function toDrawingColorFilterPtr(
    value: drawing.ColorFilter
  ): KPointer {
    return ArkUIAniModule._Extractors_ToDrawingColorFilterPtr(value);
  }
  export function fromDrawingColorFilterPtr(
    ptr: KPointer
  ): drawing.ColorFilter {
    const x: Object = {};
    return x as drawing.ColorFilter;
  }

  export function toDrawingLatticePtr(value: drawing.Lattice): KPointer {
    return ArkUIAniModule._Extractors_ToDrawingLatticePtr(value);
  }
  export function fromDrawingLatticePtr(ptr: KPointer): drawing.Lattice {
    const x: Object = {};
    return x as drawing.Lattice;
  }

  export function toUiEffectFilterPtr(value: uiEffect.Filter): KPointer {
    return ArkUIAniModule._Extractors_ToUiEffectFilterPtr(value);
  }
  export function fromUiEffectFilterPtr(ptr: KPointer): uiEffect.Filter {
    throw new Error("fromUiEffectFilterPtr is not implemented.")
  }

  export function toUiEffectVisualEffectPtr(
    value: uiEffect.VisualEffect
  ): KPointer {
    return ArkUIAniModule._Extractors_ToUiEffectVisualEffectPtr(value);
  }
  export function fromUiEffectVisualEffectPtr(
    ptr: KPointer
  ): uiEffect.VisualEffect {
    throw new Error("fromUiEffectVisualEffectPtr is not implemented.")
  }

  export function toUnifiedDataChannelUnifiedDataPtr(
    value: unifiedDataChannel.UnifiedData
  ): KPointer {
    return ArkUIAniModule._Extractors_toUnifiedDataChannelUnifiedDataPtr(value);
  }
  export function fromUnifiedDataChannelUnifiedDataPtr(
    ptr: KPointer
  ): unifiedDataChannel.UnifiedData {
    const x: Object = {};
    return ArkUIAniModule._Extractors_fromUnifiedDataChannelUnifiedDataPtr(ptr);
  }

  export function toUnifiedDataChannelSummaryPtr(
    value: unifiedDataChannel.Summary
  ): KPointer {
    return 123;
  }
  export function fromUnifiedDataChannelSummaryPtr(
    ptr: KPointer
  ): unifiedDataChannel.Summary {
    const x: Object = {};
    return x as unifiedDataChannel.Summary;
  }

  export function toWantPtr(value: Want): KPointer {
    return 123;
  }
  export function fromWantPtr(ptr: KPointer): Want {
    const x: Object = {};
    return x as Want;
  }

  export function toUIContextPtr(value: UIContext): KPointer {
    let uicontextImpl = value as UIContextImpl;
    let instanceId = uicontextImpl.instanceId_;
    return instanceId as KPointer;
  }
  export function fromUIContextPtr(ptr: KPointer): UIContext {
    let instanceId: int32 = ptr as (int32);
    return UIContextUtil.getOrCreateUIContextById(instanceId);
  }

  export function toEventHubPtr(value: EventHub): KPointer {
    return 123;
  }
  export function fromEventHubPtr(ptr: KPointer): EventHub {
    const x: Object = {};
    return x as EventHub;
  }

  export function toUIAbilityContextPtr(value: UIAbilityContext): KPointer {
    return 123;
  }
  export function fromUIAbilityContextPtr(ptr: KPointer): UIAbilityContext {
    const x: Object = {};
    return x as UIAbilityContext;
  }

  export function toWebviewWebviewControllerPtr(
    value: webview.WebviewController
  ): KPointer {
    let result = ArkUIAniModule._Extractors_ToWebviewWebviewControllerPtr(value);
    return result;
  }
  export function fromWebviewWebviewControllerPtr(
    ptr: KPointer
  ): webview.WebviewController {
    return ArkUIAniModule._Extractors_FromWebviewWebviewControllerPtr(ptr);
  }
  export function toDrawableDescriptorPtr(value: DrawableDescriptor): KPointer {
    return ArkUIAniModule._Extractors_ToDrawableDescriptorPtr(value);
  }
  export function fromDrawableDescriptorPtr(ptr: KPointer): DrawableDescriptor {
    const x: Object = {};
    return x as DrawableDescriptor;
  }

  export function toRectShapePtr(value: RectShape): KPointer {
    let result = ArkUIAniModule._Extractors_ToRectShapePtr(value);
    return result;
  }
  export function fromRectShapePtr(ptr: KPointer): RectShape {
    return ArkUIAniModule._Extractors_FromRectShapePtr(ptr);
  }

  export function toCircleShapePtr(value: CircleShape): KPointer {
    let result = ArkUIAniModule._Extractors_ToCircleShapePtr(value);
    return result;
  }
  export function fromCircleShapePtr(ptr: KPointer): CircleShape {
    return ArkUIAniModule._Extractors_FromCircleShapePtr(ptr);
  }

  export function toEllipseShapePtr(value: EllipseShape): KPointer {
    let result = ArkUIAniModule._Extractors_ToEllipseShapePtr(value);
    return result;
  }
  export function fromEllipseShapePtr(ptr: KPointer): EllipseShape {
    return ArkUIAniModule._Extractors_FromEllipseShapePtr(ptr);
  }

  export function toPathShapePtr(value: PathShape): KPointer {
    let result = ArkUIAniModule._Extractors_ToPathShapePtr(value);
    return result;
  }
  export function fromPathShapePtr(ptr: KPointer): PathShape {
    return ArkUIAniModule._Extractors_FromPathShapePtr(ptr);
  }

  export function toResourceManagerResourceManagerPtr(
    value: resourceManager.ResourceManager
  ): KPointer {
    return 123;
  }
  export function fromResourceManagerResourceManagerPtr(
    ptr: KPointer
  ): resourceManager.ResourceManager {
    const x: Object = {};
    return x as resourceManager.ResourceManager;
  }

  export function toLevelOrderPtr(value: LevelOrder): KPointer {
    return toPeerPtr(value);
  }
  export function fromLevelOrderPtr(ptr: KPointer): LevelOrder {
    return new LevelOrder(ptr);
  }

  export function toWindowWindowStagePtr(value: window.WindowStage): KPointer {
    return 123;
  }
  export function fromWindowWindowStagePtr(ptr: KPointer): window.WindowStage {
    const x: Object = {};
    return x as window.WindowStage;
  }

  export function toUiObserverRouterPageInfoPtr(
    value: uiObserver.RouterPageInfo
  ): KPointer {
    return 123;
  }
  export function fromUiObserverRouterPageInfoPtr(
    ptr: KPointer
  ): uiObserver.RouterPageInfo {
    const x: Object = {};
    return x as uiObserver.RouterPageInfo;
  }

  export function toAbilityInfoPtr(value: AbilityInfo): KPointer {
    return 123;
  }
  export function fromAbilityInfoPtr(ptr: KPointer): AbilityInfo {
    const x: Object = {};
    return x as AbilityInfo;
  }

  export function toApplicationInfoPtr(value: ApplicationInfo): KPointer {
    return 123;
  }
  export function fromApplicationInfoPtr(ptr: KPointer): ApplicationInfo {
    const x: Object = {};
    return x as ApplicationInfo;
  }

  export function toDataItemPtr(value: DataItem): KPointer {
    return 123;
  }
  export function fromDataItemPtr(ptr: KPointer): DataItem {
    const x: Object = {};
    return x as DataItem;
  }

  export function toDependencyPtr(value: Dependency): KPointer {
    return 123;
  }
  export function fromDependencyPtr(ptr: KPointer): Dependency {
    const x: Object = {};
    return x as Dependency;
  }

  export function toExtensionAbilityInfoPtr(
    value: ExtensionAbilityInfo
  ): KPointer {
    return 123;
  }
  export function fromExtensionAbilityInfoPtr(
    ptr: KPointer
  ): ExtensionAbilityInfo {
    const x: Object = {};
    return x as ExtensionAbilityInfo;
  }

  export function toHapModuleInfoPtr(value: HapModuleInfo): KPointer {
    return 123;
  }
  export function fromHapModuleInfoPtr(ptr: KPointer): HapModuleInfo {
    const x: Object = {};
    return x as HapModuleInfo;
  }

  export function toMetadataPtr(value: Metadata): KPointer {
    return 123;
  }
  export function fromMetadataPtr(ptr: KPointer): Metadata {
    const x: Object = {};
    return x as Metadata;
  }

  export function toModuleMetadataPtr(value: ModuleMetadata): KPointer {
    return 123;
  }
  export function fromModuleMetadataPtr(ptr: KPointer): ModuleMetadata {
    const x: Object = {};
    return x as ModuleMetadata;
  }

  export function toMultiAppModePtr(value: MultiAppMode): KPointer {
    return 123;
  }
  export function fromMultiAppModePtr(ptr: KPointer): MultiAppMode {
    const x: Object = {};
    return x as MultiAppMode;
  }

  export function toPreloadItemPtr(value: PreloadItem): KPointer {
    return 123;
  }
  export function fromPreloadItemPtr(ptr: KPointer): PreloadItem {
    const x: Object = {};
    return x as PreloadItem;
  }

  export function toRouterItemPtr(value: RouterItem): KPointer {
    return 123;
  }
  export function fromRouterItemPtr(ptr: KPointer): RouterItem {
    const x: Object = {};
    return x as RouterItem;
  }

  export function toSizePtr(value: Size): KPointer {
    return 123;
  }
  export function fromSizePtr(ptr: KPointer): Size {
    const x: Object = {};
    return x as Size;
  }

  export function toSkillPtr(value: Skill): KPointer {
    return 123;
  }
  export function fromSkillPtr(ptr: KPointer): Skill {
    const x: Object = {};
    return x as Skill;
  }

  export function toSkillUriPtr(value: SkillUri): KPointer {
    return 123;
  }
  export function fromSkillUriPtr(ptr: KPointer): SkillUri {
    const x: Object = {};
    return x as SkillUri;
  }

  export function toUiObserverNavDestinationInfoPtr(
    value: uiObserver.NavDestinationInfo
  ): KPointer {
    return 123;
  }
  export function fromUiObserverNavDestinationInfoPtr(
    ptr: KPointer
  ): uiObserver.NavDestinationInfo {
    const x: Object = {};
    return x as uiObserver.NavDestinationInfo;
  }

  export function toUiObserverNavigationInfoPtr(
    value: uiObserver.NavigationInfo
  ): KPointer {
    return 123;
  }
  export function fromUiObserverNavigationInfoPtr(
    ptr: KPointer
  ): uiObserver.NavigationInfo {
    const x: Object = {};
    return x as uiObserver.NavigationInfo;
  }

  export function toWindowSizePtr(value: WindowSize): KPointer {
    return 123;
  }
  export function fromWindowSizePtr(ptr: KPointer): WindowSize {
    const x: Object = {};
    return x as WindowSize;
  }

  export function toWindowSystemBarStylePtr(
    value: window.SystemBarStyle
  ): KPointer {
    return 123;
  }
  export function fromWindowSystemBarStylePtr(
    ptr: KPointer
  ): window.SystemBarStyle {
    const x: Object = {};
    return x as window.SystemBarStyle;
  }

  export function toConfigurationPtr(value: Configuration): KPointer {
    return 123;
  }
  export function fromConfigurationPtr(ptr: KPointer): Configuration {
    const x: Object = {};
    return x as Configuration;
  }

  export function toScenePtr(value: Scene): KPointer {
    return ArkUIAniModule._Extractors_ToScenePtr(value);
  }
  export function fromScenePtr(ptr: KPointer): Scene {
    const x: Object = {};
    return x as Scene;
  }
  export function toAnimationPtr(value: Animation): KPointer {
    return 123;
  }
  export function fromAnimationPtr(ptr: KPointer): Animation {
    const x: Object = {};
    return x as Animation;
  }
  export function toEnvironmentPtr(value: Environment): KPointer {
    return 123;
  }
  export function fromEnvironmentPtr(ptr: KPointer): Environment {
    const x: Object = {};
    return x as Environment;
  }
}
