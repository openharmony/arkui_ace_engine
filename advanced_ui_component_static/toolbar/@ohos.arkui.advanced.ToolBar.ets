/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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

import {
    Resource, ResourceStr, GestureModifier, CustomDialogController, UIGestureEvent, LongPressGestureHandler, $r,
    ResourceColor, AttributeModifier, ColumnAttribute, Component, TabsController, Builder, Button, ButtonType, Column,
    SymbolGlyph, Text, FontWeight, TextOverflow, TextAlign, FlexAlign, Placement, Color, SymbolEffect, Image, ImageFit,
    PX, FP, LPX, VP, GeometryInfo, Measurable, ConstraintSizeOptions, SizeResult, MeasureResult, Tabs, Visibility,
    Divider, Row, ForEach, BlurStyle, MenuOptions, Position, ColorMetrics, Rect, ShadowStyle, LocalizedPadding,
    Margin, Padding, SymbolGlyphModifier, ButtonOptions, ClickEvent, CommonMethod, MenuElement, CustomDialog,
    CustomLayout, Layoutable, ClassCastError
  } from '@ohos.arkui.component'
  import {
    State, Observed, PropRef, StorageLink, ObjectLink, StorageProp, Watch, Link
  } from '@ohos.arkui.stateManagement';
  import { LengthUnit, LengthMetrics, } from '@ohos.arkui.node';
  import { DividerModifier } from '@ohos.arkui.modifier';
  import { UIContext } from '@ohos.arkui.UIContext';
  import { Theme } from '@ohos.arkui.theme';
  import common from '@ohos.app.ability.common';
  import window from '@ohos.window';
  import hilog from '@ohos.hilog';
  
  export enum ItemState {
    ENABLE = 1,
    DISABLE = 2,
    ACTIVATE = 3,
  }
  
  // “更多”栏图标
  const PUBLIC_MORE = $r('sys.symbol.dot_grid_2x2');
  const IMAGE_SIZE: string = '24vp';
  const DEFAULT_TOOLBAR_HEIGHT: number = 56;
  const TOOLBAR_MAX_LENGTH: number = 5;
  const MAX_FONT_SIZE: number = 3.2;
  const DIALOG_IMAGE_SIZE = '64vp';
  const MAX_DIALOG = '256vp';
  const MIN_DIALOG = '216vp';
  const TEXT_TOOLBAR_DIALOG = '18.3fp';
  const FOCUS_BOX_MARGIN: number = -2;
  const FOCUS_BOX_BORDER_WIDTH: number = 2;
  const RESOURCE_TYPE_SYMBOL: number = 40000;
  
  export interface ToolBarSymbolGlyphOptions {
    normal?: SymbolGlyphModifier;
    activated?: SymbolGlyphModifier;
  }
  
  class ButtonGestureModifier implements GestureModifier {
    public static readonly longPressTime: number = 500;
    public static readonly minFontSize: number = 1.75;
    public fontSize: number = 1;
    public controller: CustomDialogController | null = null;
  
    constructor(controller: CustomDialogController | null) {
      this.controller = controller;
    }
  
    applyGesture(event: UIGestureEvent): void {
      if (this.fontSize >= ButtonGestureModifier.minFontSize) {
        event.addGesture(
          new LongPressGestureHandler({ repeat: false, duration: ButtonGestureModifier.longPressTime as int })
            .onAction(() => {
              if (event) {
                this.controller?.open();
              }
            })
            .onActionEnd(() => {
              this.controller?.close();
            })
            .onActionCancel(() => {
              this.controller?.close();
            })
        )
      } else {
        event.clearGestures();
      }
    }
  }
  
  class Util {
    public static isSymbolResource(resourceStr: ResourceStr | undefined | null): boolean {
      if (!Util.isResourceType(resourceStr)) {
        return false;
      }
      let resource: Resource = resourceStr as Resource;
      return resource.type === RESOURCE_TYPE_SYMBOL;
    }
  
    public static isResourceType(resource: ResourceStr | Resource | undefined | null): boolean {
      if (!resource) {
        return false;
      }
      if (typeof resource === 'string' || typeof resource === 'undefined') {
        return false;
      }
      return true;
    }
  }
  
  @Observed
  export class ToolBarOption {
    public content: ResourceStr = '';
    public action?: () => void = undefined;
    public icon?: Resource = undefined;
    public state?: ItemState = 1 as ItemState;
    public iconColor?: ResourceColor = $r('sys.color.icon_primary');
    public activatedIconColor?: ResourceColor = $r('sys.color.icon_emphasize');
    public textColor?: ResourceColor = $r('sys.color.font_primary');
    public activatedTextColor?: ResourceColor = $r('sys.color.font_emphasize');
    public toolBarSymbolOptions?: ToolBarSymbolGlyphOptions = undefined;
    public accessibilityText?: ResourceStr = '';
    public accessibilityDescription?: ResourceStr = '';
    public accessibilityLevel?: string = 'auto';
  }
  
  export type ToolBarOptions = Array<ToolBarOption>
  
  export class ToolBarModifier implements AttributeModifier<ColumnAttribute> {
    public backgroundColorValue?: ResourceColor = $r('sys.color.ohos_id_color_toolbar_bg');
    public heightValue?: LengthMetrics = LengthMetrics.vp(DEFAULT_TOOLBAR_HEIGHT);
    public stateEffectValue?: boolean = true;
    public paddingValue?: LengthMetrics = LengthMetrics.resource($r('sys.float.padding_level12'));
  
    applyNormalAttribute(instance: ColumnAttribute): void {
      instance.backgroundColor(this.backgroundColorValue);
    }
  
    public backgroundColor(backgroundColor: ResourceColor): ToolBarModifier {
      this.backgroundColorValue = backgroundColor;
      return this;
    }
  
    public height(height: LengthMetrics): ToolBarModifier {
      this.heightValue = height;
      return this;
    }
  
    public stateEffect(stateEffect: boolean): ToolBarModifier {
      this.stateEffectValue = stateEffect;
      return this;
    }
  
    public padding(padding: LengthMetrics): ToolBarModifier {
      this.paddingValue = padding;
      return this;
    }
  }
  
  class ToolBarTheme {
    public iconPrimaryColor: ResourceColor = $r('sys.color.icon_primary');
    public iconActivePrimaryColor: ResourceColor = $r('sys.color.icon_emphasize');
    public fontPrimaryColor: ResourceColor = $r('sys.color.font_primary');
    public fontActivatedPrimaryColor: ResourceColor = $r('sys.color.font_emphasize');
  }
  
  @CustomLayout
  @Component
  export struct ToolBar {
    @ObjectLink @Watch('onToolBarListChanged') toolBarList: Array<ToolBarOption>;
    controller: TabsController = new TabsController();
    @PropRef activateIndex: int = -1;
    @Observed
    @PropRef dividerModifier: DividerModifier | undefined;
    @Observed
    @PropRef toolBarModifier: ToolBarModifier = new ToolBarModifier();
    @Observed
    @PropRef moreText: Resource = $r('sys.string.ohos_toolbar_more') as Resource;
    @State menuContent: MenuElement[] = [] as MenuElement[];
    @State toolBarItemBackground: ResourceColor[] = [] as ResourceColor[];
    @Observed
    @State toolBarTheme: ToolBarTheme = new ToolBarTheme();
    @State fontSize: number = 1;
    isFollowSystem: boolean = false;
    maxFontSizeScale: number = 3.2;
    moreIndex: number = 4;
    moreItem: ToolBarOption = {
      content: $r('sys.string.ohos_toolbar_more'),
      icon: PUBLIC_MORE,
    } as ToolBarOption;
    isRefreshData: boolean = true;
  
    onToolBarListChanged(changedPropertyName: string): void {
      this.isRefreshData = this.refreshData();
    }
  
    onWillApplyTheme(theme: Theme) {
      this.toolBarTheme.iconPrimaryColor = theme.colors.iconPrimary;
      this.toolBarTheme.iconActivePrimaryColor = theme.colors.iconEmphasize;
      this.toolBarTheme.fontPrimaryColor = theme.colors.fontPrimary;
      this.toolBarTheme.fontActivatedPrimaryColor = theme.colors.fontEmphasize;
    }
  
    @Builder
    MoreTabBuilder(index: number) {
      Button({ type: ButtonType.Normal, stateEffect: false } as ButtonOptions) {
        Column() {
          SymbolGlyph(PUBLIC_MORE)
            .fontSize(IMAGE_SIZE)
            .fontColor([this.toolBarTheme.iconPrimaryColor])
            .draggable(false)
            .margin({ bottom: $r('sys.float.padding_level1') } as Margin)
          Text(this.moreText)
            .fontColor(this.toolBarTheme.fontPrimaryColor)
            .fontSize($r('sys.float.ohos_id_text_size_caption'))
            .fontWeight(FontWeight.Medium)
            .maxLines(1)
            .textOverflow({ overflow: TextOverflow.Ellipsis })
            .textAlign(TextAlign.Center)
            .focusable(true)
            .focusOnTouch(true)
        }
        .width('100%')
        .height('100%')
        .justifyContent(FlexAlign.Center)
        .padding({
          start: LengthMetrics.resource($r('sys.float.padding_level2')),
          end: LengthMetrics.resource($r('sys.float.padding_level2')),
        } as LocalizedPadding)
        .borderRadius($r('sys.float.ohos_id_corner_radius_clicked'))
      }
      .accessibilityGroup(true)
      .focusable(true)
      .focusOnTouch(true)
      .focusBox({
        margin: LengthMetrics.vp(FOCUS_BOX_MARGIN),
        strokeWidth: LengthMetrics.vp(FOCUS_BOX_BORDER_WIDTH),
        strokeColor: ColorMetrics.resourceColor($r('sys.color.ohos_id_color_focused_outline'))
      })
      .width('100%')
      .height('100%')
      .bindMenu(this.menuContent,
        { placement: Placement.TopRight, offset: { x: -12, y: -10 } as Position } as MenuOptions)
      .borderRadius($r('sys.float.ohos_id_corner_radius_clicked'))
      .backgroundColor(this.toolBarItemBackground[Double.toInt(index)])
      .onHover((isHover: boolean): void => {
        if (isHover) {
          this.toolBarItemBackground[Double.toInt(index)] = $r('sys.color.ohos_id_color_hover');
        } else {
          this.toolBarItemBackground[Double.toInt(index)] = Color.Transparent;
        }
      })
      .stateStyles({
        pressed: (instance: CommonMethod) => {
          instance.backgroundColor((!this.toolBarModifier?.stateEffectValue) ?
            this.toolBarItemBackground[Double.toInt(index)] : $r('sys.color.ohos_id_color_click_effect'))
        }
      })
      .gestureModifier(this.getItemGestureModifier(this.moreItem, index))
    }
  
    @Builder
    TabBuilder(index: number) {
      Button({ type: ButtonType.Normal, stateEffect: false } as ButtonOptions) {
        Column() {
          if (this.toolBarList[Double.toInt(index)]?.toolBarSymbolOptions?.normal ||
            this.toolBarList[Double.toInt(index)]?.toolBarSymbolOptions?.activated) {
            SymbolGlyph()
              .fontSize(IMAGE_SIZE)
              .symbolEffect(new SymbolEffect(), false)
              .attributeModifier(this.getToolBarSymbolModifier(index))
              .margin({ bottom: $r('sys.float.padding_level1') } as Margin)
          } else if (Util.isSymbolResource(this.toolBarList[Double.toInt(index)]?.icon)) {
            SymbolGlyph(this.toolBarList[Double.toInt(index)]?.icon)
              .fontSize(IMAGE_SIZE)
              .fontColor([this.getIconColor(index)])
              .margin({ bottom: $r('sys.float.padding_level1') } as Margin)
          } else {
            if (this.toolBarList[Double.toInt(index)]?.icon !== undefined) {
              Image(this.toolBarList[Double.toInt(index)]?.icon as Resource)
                .width(IMAGE_SIZE)
                .height(IMAGE_SIZE)
                .fillColor(this.getIconColor(index))
                .margin({ bottom: $r('sys.float.padding_level1') } as Margin)
                .objectFit(ImageFit.Contain)
                .draggable(false)
            } else {
              SymbolGlyph()
                .fontSize(IMAGE_SIZE)
                .margin({ bottom: $r('sys.float.padding_level1') } as Margin)
            }
          }
          Text(this.toolBarList[Double.toInt(index)]?.content)
            .fontColor(this.getTextColor(index))
            .fontSize($r('sys.float.ohos_id_text_size_caption'))
            .maxFontSize($r('sys.float.ohos_id_text_size_caption'))
            .minFontSize(9)
            .fontWeight(FontWeight.Medium)
            .maxLines(1)
            .textOverflow({ overflow: TextOverflow.Ellipsis })
            .textAlign(TextAlign.Center)
            .focusable(!(this.toolBarList[Double.toInt(index)]?.state === ItemState.DISABLE))
            .focusOnTouch(!(this.toolBarList[Double.toInt(index)]?.state === ItemState.DISABLE))
        }
        .justifyContent(FlexAlign.Center)
        .width('100%')
        .height('100%')
        .borderRadius($r('sys.float.ohos_id_corner_radius_clicked'))
        .padding({
          start: LengthMetrics.resource($r('sys.float.padding_level2')),
          end: LengthMetrics.resource($r('sys.float.padding_level2')),
        } as LocalizedPadding)
      }
      .accessibilityGroup(true)
      .accessibilityText(
        this.toAccessibilityText(this.toolBarList[Double.toInt(index)]?.accessibilityText, index))
      .accessibilityDescription(
        this.toStringFormat(this.toolBarList[Double.toInt(index)]?.accessibilityDescription))
      .accessibilityLevel(this.toolBarList[Double.toInt(index)]?.accessibilityLevel ?? 'auto')
      .enabled(this.toolBarList[Double.toInt(index)]?.state !== ItemState.DISABLE)
      .width('100%')
      .height('100%')
      .borderRadius($r('sys.float.ohos_id_corner_radius_clicked'))
      .focusable(!(this.toolBarList[Double.toInt(index)]?.state === ItemState.DISABLE))
      .focusOnTouch(!(this.toolBarList[Double.toInt(index)]?.state === ItemState.DISABLE))
      .focusBox({
        margin: LengthMetrics.vp(FOCUS_BOX_MARGIN),
        strokeWidth: LengthMetrics.vp(FOCUS_BOX_BORDER_WIDTH),
        strokeColor: ColorMetrics.resourceColor($r('sys.color.ohos_id_color_focused_outline'))
      })
      .backgroundColor(this.toolBarItemBackground[Double.toInt(index)])
      .onHover((isHover: boolean): void => {
        if (isHover && this.toolBarList[Double.toInt(index)]?.state !== ItemState.DISABLE) {
          this.toolBarItemBackground[Double.toInt(index)] = $r('sys.color.ohos_id_color_hover');
        } else {
          this.toolBarItemBackground[Double.toInt(index)] = Color.Transparent;
        }
      })
      .stateStyles({
        pressed: (instance: CommonMethod): void => {
          instance.backgroundColor((this.toolBarList[Double.toInt(index)]?.state === ItemState.DISABLE) ||
            (!this.toolBarModifier?.stateEffectValue) ?
            this.toolBarItemBackground[Double.toInt(index)] : $r('sys.color.ohos_id_color_click_effect'))
        }
      })
      .onClick((event: ClickEvent) => {
        this.clickEventAction(index);
      })
      .gestureModifier(this.getItemGestureModifier(this.toolBarList[Double.toInt(index)], index))
    }
  
    private toAccessibilityText(resource: ResourceStr | undefined, index: number): string | undefined {
      if (typeof resource === 'string') {
        return resource as string;
      } else if (typeof resource === 'undefined') {
        return this.toStringFormat(this.toolBarList[Double.toInt(index)]?.content);
      } else {
        let str = (this.getUIContext().getHostContext() as common.UIAbilityContext)?.resourceManager?.
        getStringSync((resource as Resource).id)
        return str as string;
      }
    }
  
    private toStringFormat(resource: ResourceStr | undefined): string | undefined {
      if (typeof resource === 'string') {
        return resource as string;
      } else if (typeof resource === 'undefined') {
        return '' as string;
      } else {
        let str = (this.getUIContext().getHostContext() as common.UIAbilityContext)?.resourceManager?.
        getStringSync((resource as Resource).id)
        return str as string;
      }
    }
  
    private getFontSizeScale(): number {
      let context = this.getUIContext();
      let fontScaleSystem: number = 1;
      if (context.getHostContext()) {
        fontScaleSystem = (context.getHostContext() as common.UIAbilityContext)?.config?.fontSizeScale ?? 1;
      }
      if (!this.isFollowSystem) {
        return 1;
      } else {
        return Math.min(fontScaleSystem, this.maxFontSizeScale);
      }
    }
  
    private getToolBarSymbolModifier(index: number): SymbolGlyphModifier | undefined {
      if ((!this.toolBarList[Double.toInt(index)]?.toolBarSymbolOptions?.activated) &&
        (!this.toolBarList[Double.toInt(index)]?.toolBarSymbolOptions?.normal)) {
        return undefined;
      }
      if (this.activateIndex === Double.toInt(index) &&
        (this.toolBarList[Double.toInt(index)]?.state === ItemState.ACTIVATE)) {
        return this.toolBarList[Double.toInt(index)]?.toolBarSymbolOptions?.activated;
      }
      return this.toolBarList[Double.toInt(index)]?.toolBarSymbolOptions?.normal;
    }
  
    private getIconColor(index: number): ResourceColor {
      if (this.activateIndex === Double.toInt(index) &&
        (this.toolBarList[Double.toInt(index)]?.state === ItemState.ACTIVATE)) {
        return this.toolBarList[Double.toInt(index)]?.activatedIconColor ?? this.toolBarTheme.iconActivePrimaryColor;
      }
      return this.toolBarList[Double.toInt(index)]?.iconColor ?? this.toolBarTheme.iconPrimaryColor;
    }
  
    private getTextColor(index: number): ResourceColor {
      if (this.activateIndex === Double.toInt(index) &&
        (this.toolBarList[Double.toInt(index)]?.state === ItemState.ACTIVATE)) {
        return this.toolBarList[Double.toInt(index)]?.activatedTextColor ?? this.toolBarTheme.fontActivatedPrimaryColor;
      }
      return this.toolBarList[Double.toInt(index)]?.textColor ?? this.toolBarTheme.fontPrimaryColor;
    }
  
    private toLengthString(value: LengthMetrics | undefined): string {
      if (value === (() => {
        (0);
        return undefined;
      })()) {
        return '';
      }
      const length: number = value!.value;
      let lengthString: string = '';
      switch (value!.unit) {
        case LengthUnit.PX:
          lengthString = `${length}px`;
          break;
        case LengthUnit.FP:
          lengthString = `${length}fp`;
          break;
        case LengthUnit.LPX:
          lengthString = `${length}lpx`;
          break;
        case LengthUnit.PERCENT:
          lengthString = `${length * 100}%`;
          break;
        case LengthUnit.VP:
          lengthString = `${length}vp`;
          break;
        default:
          lengthString = `${length}vp`;
          break;
      }
      return lengthString;
    }
  
    private clickEventAction(index: number): void {
      let toolbar = this.toolBarList[Double.toInt(index)];
      if (toolbar.state === ItemState.ACTIVATE) {
        if (this.activateIndex === Double.toInt(index)) {
          this.activateIndex = -1;
        } else {
          this.activateIndex = Double.toInt(index);
        }
      }
      if (!(toolbar.state === ItemState.DISABLE)) {
        if (typeof toolbar.action === 'function') {
          toolbar.action?.();
        }
      }
    }
  
    private getItemGestureModifier(item: ToolBarOption, index: number): ButtonGestureModifier {
      let buttonGestureModifier: ButtonGestureModifier = new ButtonGestureModifier(null);
      if (item?.icon || item?.toolBarSymbolOptions?.activated || item?.toolBarSymbolOptions?.normal) {
        let customDialogController: CustomDialogController = new CustomDialogController({
          builder: ToolBarDialog({
            itemDialog: item,
            fontSize: this.fontSize,
            itemSymbolModifier: this.getToolBarSymbolModifier(index),
          }),
          maskColor: Color.Transparent,
          isModal: true,
          customStyle: true,
        })
        buttonGestureModifier = new ButtonGestureModifier(customDialogController)
        buttonGestureModifier.fontSize = this.fontSize;
      }
      return buttonGestureModifier;
    }
  
    refreshData() {
      this.dividerModifier = this.dividerModifier ? this.dividerModifier : new DividerModifier();
      this.toolBarModifier = this.toolBarModifier ? this.toolBarModifier : new ToolBarModifier()
        .padding(LengthMetrics.resource($r('sys.float.padding_level12')))
        .stateEffect(true)
        .height(LengthMetrics.vp(DEFAULT_TOOLBAR_HEIGHT))
        .backgroundColor('sys.color.ohos_id_color_toolbar_bg');
      this.menuContent = [];
      let toolBarListCount: int = Double.toInt(this.toolBarList.length);
      for (let i: int = 0; i < toolBarListCount; i++) {
        if (i >= Double.toInt(this.moreIndex) && this.toolBarList.length > TOOLBAR_MAX_LENGTH
        ) {
          this.menuContent.push({
            value: this.toolBarList[i].content,
            action: this.toolBarList[i].action ? this.toolBarList[i].action as () => void : () => {
            },
            enabled: this.toolBarList[i].state !== ItemState.DISABLE,
          })
        } else {
          this.menuContent = [];
        }
        if (i >= this.toolBarItemBackground.length && this.toolBarItemBackground.length < this.toolBarList.length) {
          this.toolBarItemBackground.push(Color.Transparent);
        }
      }
      return true;
    }
  
    onPlaceChildren(selfLayoutInfo: GeometryInfo, children: Array<Layoutable>, constraint: ConstraintSizeOptions) {
      children.forEach((child: Layoutable) => {
        const position: Position = { x: 0, y: 0 };
        child.layout(position)
      })
    }
  
    onMeasureSize(selfLayoutInfo: GeometryInfo, children: Measurable[], constraint: ConstraintSizeOptions): SizeResult {
      this.fontSize = this.getFontSizeScale();
      let sizeResult: SizeResult = { height: 0, width: 0 };
      if (Double.toInt(children.length) > 0) {
        children.forEach((child: Measurable) => {
          const childMeasureResult: MeasureResult | undefined = child.measure(constraint);
          if (childMeasureResult) {
            sizeResult.width = childMeasureResult.width;
            sizeResult.height = childMeasureResult.height;
          }
        });
      }
      return sizeResult;
    }
  
    aboutToAppear() {
      this.isRefreshData = this.refreshData();
      try {
        let systemFontScale = this.getUIContext()?.isFollowingSystemFontScale();
        let maxFontScale = this.getUIContext()?.getMaxFontScale();
        if (systemFontScale !== undefined) {
          this.isFollowSystem = systemFontScale;
        }
        if (maxFontScale !== undefined) {
          this.maxFontSizeScale = maxFontScale;
        }
      } catch (err) {
        let code: undefined | int = (err as ClassCastError)?.code;
        let message: undefined | string = (err as ClassCastError)?.message;
        hilog.error(0x3900, 'Ace',
          `Faild to toolBar getMaxFontScale, code: ${code}, message: ${message}`);
      }
    }
  
    build() {
      Column() {
        Tabs({ controller: this.controller }) {
        }
        .visibility(Visibility.None)
  
        Divider()
          .width('100%')
          .height(1)
          .attributeModifier(this.dividerModifier)
        Row() {
          ForEach(this.toolBarList as ToolBarOption[], (item: ToolBarOption, index: int) => {
            if (this.toolBarList.length <= TOOLBAR_MAX_LENGTH || index < this.moreIndex) {
              Row() {
                this.TabBuilder(index);
              }
              .height('100%')
              .flexShrink(1)
            }
          }, (item: ToolBarOption, index: int) => {
            return `${this.getUniqueId()}__${index}}`;
          })
          if (this.isRefreshData && this.toolBarList.length > TOOLBAR_MAX_LENGTH) {
            Row() {
              this.MoreTabBuilder(this.moreIndex);
            }
            .height('100%')
            .flexShrink(1)
          }
        }
        .justifyContent(FlexAlign.Center)
        .constraintSize({
          minHeight: this.toLengthString(this.toolBarModifier?.heightValue),
          maxHeight: this.toLengthString(this.toolBarModifier?.heightValue),
        })
        .width('100%')
        .height(this.toLengthString(this.toolBarModifier?.heightValue))
        .padding({
          start: this.toolBarList.length < TOOLBAR_MAX_LENGTH ?
            this.toolBarModifier?.paddingValue : LengthMetrics.resource($r('sys.float.padding_level0')),
          end: this.toolBarList.length < TOOLBAR_MAX_LENGTH ?
            this.toolBarModifier?.paddingValue : LengthMetrics.resource($r('sys.float.padding_level0')),
        } as LocalizedPadding)
      }
      .attributeModifier(this.toolBarModifier)
    }
  }
  
  /**
   * ToolBarDialog
   *
   * @since 2024-07-23
   */
  @CustomDialog
  struct ToolBarDialog {
    itemDialog: ToolBarOption = {
      icon: undefined,
      content: '',
    } as ToolBarOption;
    itemSymbolModifier?: SymbolGlyphModifier;
    mainWindowStage: window.Window | undefined = undefined;
    controller?: CustomDialogController;
    screenWidth: number = 640;
    verticalScreenLines: int = 6;
    horizontalsScreenLines: int = 1;
    cancel: () => void = () => {
    };
    confirm: () => void = () => {
    };
    @PropRef fontSize: number = 1;
    @State maxLines: int = 1;
    @StorageProp('windowStandardHeight') windowStandardHeight: number = 0;
    @Observed
    @State symbolEffect: SymbolEffect = new SymbolEffect();
  
    build() {
      if (this.itemDialog.content) {
        Column() {
          if (this.itemDialog.toolBarSymbolOptions?.normal ||
            this.itemDialog.toolBarSymbolOptions?.activated) {
            SymbolGlyph()
              .attributeModifier(this.itemSymbolModifier)
              .symbolEffect(this.symbolEffect, false)
              .fontColor([$r('sys.color.icon_primary')])
              .fontSize(DIALOG_IMAGE_SIZE)
              .margin({
                top: $r('sys.float.padding_level24'),
                bottom: $r('sys.float.padding_level8'),
              } as Margin)
          } else if (Util.isSymbolResource(this.itemDialog.icon)) {
            SymbolGlyph(this.itemDialog?.icon)
              .fontColor([$r('sys.color.icon_primary')])
              .fontSize(DIALOG_IMAGE_SIZE)
              .margin({
                top: $r('sys.float.padding_level24'),
                bottom: $r('sys.float.padding_level8'),
              } as Margin)
          } else {
            Image(this.itemDialog.icon as Resource)
              .width(DIALOG_IMAGE_SIZE)
              .height(DIALOG_IMAGE_SIZE)
              .margin({
                top: $r('sys.float.padding_level24'),
                bottom: $r('sys.float.padding_level8'),
              } as Margin)
              .fillColor($r('sys.color.icon_primary'))
          }
          Column() {
            Text(this.itemDialog.content)
              .fontSize(TEXT_TOOLBAR_DIALOG)
              .textOverflow({ overflow: TextOverflow.Ellipsis })
              .maxLines(this.maxLines)
              .width('100%')
              .textAlign(TextAlign.Center)
              .fontColor($r('sys.color.font_primary'))
          }
          .width('100%')
          .padding({
            left: $r('sys.float.padding_level4'),
            right: $r('sys.float.padding_level4'),
            bottom: $r('sys.float.padding_level12'),
          } as Padding)
        }
        .width(this.fontSize === MAX_FONT_SIZE ? MAX_DIALOG : MIN_DIALOG)
        .constraintSize({ minHeight: this.fontSize === MAX_FONT_SIZE ? MAX_DIALOG : MIN_DIALOG })
        .backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK, undefined, { disableSystemAdaptation: true })
        .shadow(ShadowStyle.OUTER_DEFAULT_LG)
        .borderRadius(($r('sys.float.corner_radius_level10')))
      } else {
        Column() {
          if (this.itemDialog.toolBarSymbolOptions?.normal ||
            this.itemDialog.toolBarSymbolOptions?.activated) {
            SymbolGlyph()
              .attributeModifier(this.itemSymbolModifier)
              .symbolEffect(this.symbolEffect, false)
              .fontColor([$r('sys.color.icon_primary')])
              .fontSize(DIALOG_IMAGE_SIZE)
          } else if (Util.isSymbolResource(this.itemDialog.icon)) {
            SymbolGlyph(this.itemDialog?.icon)
              .fontColor([$r('sys.color.icon_primary')])
              .fontSize(DIALOG_IMAGE_SIZE)
          } else {
            Image(this.itemDialog.icon as Resource)
              .width(DIALOG_IMAGE_SIZE)
              .height(DIALOG_IMAGE_SIZE)
              .fillColor($r('sys.color.icon_primary'))
          }
        }
        .width(this.fontSize === MAX_FONT_SIZE ? MAX_DIALOG : MIN_DIALOG)
        .constraintSize({ minHeight: this.fontSize === MAX_FONT_SIZE ? MAX_DIALOG : MIN_DIALOG })
        .backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK, undefined, { disableSystemAdaptation: true })
        .shadow(ShadowStyle.OUTER_DEFAULT_LG)
        .borderRadius(($r('sys.float.corner_radius_level10')))
        .justifyContent(FlexAlign.Center)
      }
    }
  
    aboutToAppear(): void {
      try {
        let context = this.getUIContext().getHostContext();
        if (context) {
          this.mainWindowStage = (context as common.UIAbilityContext).windowStage.getMainWindowSync();
          let properties: window.WindowProperties =
            this.mainWindowStage?.getWindowProperties() as window.WindowProperties;
          let rect = properties.windowRect;
          if (this.getUIContext().px2vp(rect.height as Int) > this.screenWidth) {
            this.maxLines = this.verticalScreenLines;
          } else {
            this.maxLines = this.horizontalsScreenLines;
          }
        }
      } catch (err) {
        let code: int | undefined = (err as ClassCastError)?.code;
        let message: string | undefined = (err as ClassCastError)?.message;
        hilog.error(0x3900, 'Ace',
          `Faild to ToolBarDialog aboutToAppear, code: ${code}, message: ${message}`);
      }
    }
  }