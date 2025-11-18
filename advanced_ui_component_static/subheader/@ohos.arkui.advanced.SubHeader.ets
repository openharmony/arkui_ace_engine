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

import {
  Layoutable, Measurable, ResourceStr, Length, SelectOption, ResourceColor, FontWeight, SymbolEffectStrategy, Resource,
  SymbolRenderingStrategy, Alignment, AttributeModifier, RowAttribute, Component, TextModifier, BuilderParam, Column,
  LocalizedMargin, LocalizedPadding, applyStyles, KeyEvent, Flex, Builder, Button, Row, GeometryInfo, SizeResult, $r,
  ConstraintSizeOptions, TextAttribute, CommonMethod, Rectangle, TextOverflow, KeyType, ClickEvent, TouchEvent, Margin,
  TouchType, HorizontalAlign, FlexDirection, ItemAlign, ButtonOptions, HoverEffect, FlexAlign, VerticalAlign, Image,
  SymbolGlyph, Text, Select, Stack, ForEach, LoadingProgress, Padding, MeasureResult, ButtonType, ButtonStyleMode,
  CustomLayout
} from '@ohos.arkui.component';
import { PropRef, State, Provide, Consume } from '@ohos.arkui.stateManagement';
import { UIContext } from '@ohos.arkui.UIContext';
import { Theme } from '@ohos.arkui.theme';
import { ColorMetrics, LengthMetrics, LengthUnit } from '@ohos.arkui.node';
import resourceManager from '@ohos.resourceManager';
import { BusinessError } from '@ohos.base';
import hilog from '@ohos.hilog';
import common from '@ohos.app.ability.common';
import HashMap from '@ohos.util.HashMap';
import { KeyCode } from '@ohos.multimodalInput.keyCode';

const INDEX_ZERO: int = 0;
const INDEX_ONE: int = 1;
const INDEX_TWO: int = 2;
// 字体字重缩放等数值
const DEFAULT_FONT_SCALE: number = 1;
// 行数及整体高度
const SINGLE_LINE_NUM: number = 1;
const DOUBLE_LINE_NUM: int = 2;
// 资源数值
const RESOURCE_TYPE_SYMBOL: int = 40000;
// 左边尺寸常量
const LEFT_ICON_SIZE: ResourceStr = '16vp';
const LEFT_ICON_SIZE_NUMBER: number = 16;
const LEFT_TEXT_NUMBER: number = 8;
// 右边尺寸常量
const OPERATE_ITEM_LENGTH: number = 24;
const ARROW_ICON_WIDTH: number = 12;
const SINGLE_ICON_ZONE_SIZE: number = 28;
const RIGHT_SINGLE_ICON_SIZE: ResourceStr = '24vp';
const PADDING_LEVEL_2: number = 4;
const MAX_RIGHT_WIDTH: Length = '34%';
const MIN_FONT_SIZE: number = 1.75;
const MIN_HOT_AREA_LENGTH: number = 40;
const MULTI_ICON_REGION_WIDTH: number = 37;
const ICON_REGION_X: number = -9;
const ICON_REGION_Y: number = -6;
const SINGLE_ICON_REGION_X: number = -12;
const SINGLE_ICON_NUMBER: number = 1;
const PADDING_LEFT: number = 2;

export enum OperationType {
  TEXT_ARROW = 0,
  BUTTON = 1,
  ICON_GROUP = 2,
  LOADING = 3,
}

export class OperationOption {
  public value: ResourceStr = '';
  public action?: () => void;
  public accessibilityLevel?: string;
  public accessibilityText?: ResourceStr;
  public accessibilityDescription?: ResourceStr;
  public defaultFocus?: boolean;
}

export class SelectOptions {
  public options: Array<SelectOption> = [] as Array<SelectOption>;
  public selected?: int;
  public value?: ResourceStr;
  public onSelect?: (index: int, value?: string) => void;
  public defaultFocus?: boolean;
}

export class SymbolOptions {
  public fontSize?: Length;
  public fontColor?: Array<ResourceColor>;
  public fontWeight?: int | FontWeight | string;
  public effectStrategy?: SymbolEffectStrategy;
  public renderingStrategy?: SymbolRenderingStrategy;
}

interface IconOptions {
  icon?: ResourceStr;
  symbolicIconOption?: SymbolOptions | null;
}

interface ContentIconOption {
  content?: ResourceStr;
  subContent?: ResourceStr;
  iconOptions?: IconOptions;
  action?: () => void;
  accessibilityLevel?: string;
  accessibilityText?: ResourceStr;
  accessibilityDescription?: ResourceStr;
  defaultFocus?: boolean;
}

class FontStyle {
  public maxLines: int = 0;
  public fontWeight: int = 0;
  public fontColor?: ResourceColor;
  public alignment?: Alignment;
}

class SubHeaderTheme {
  public fontPrimaryColor: ResourceColor = $r('sys.color.font_primary');
  public fontSecondaryColor: ResourceColor = $r('sys.color.font_secondary');
  public fontButtonColor: ResourceColor = $r('sys.color.font_emphasize');
  public iconArrowColor: ResourceColor = $r('sys.color.icon_tertiary');
  public textArrowHoverBgColor: ResourceColor = $r('sys.color.interactive_hover');
  public borderFocusColor: ResourceColor = $r('sys.color.interactive_focus');
  public leftIconColor: ResourceColor = $r('sys.color.icon_secondary');
  public rightIconColor: ResourceColor = $r('sys.color.icon_primary');
}

function secondaryTitleStyles(this: TextAttribute, fontStyle: FontStyle): this {
  this.fontSize(`${getResourceValue('sys.float.Subtitle_S')}fp`);
  this.fontColor(fontStyle?.fontColor ?? $r('sys.color.font_secondary'));
  this.fontWeight(fontStyle?.fontWeight);
  this.maxLines(fontStyle?.maxLines);
  this.textOverflow({ overflow: TextOverflow.Ellipsis });
  this.align(fontStyle?.alignment);
  return this;
}

function primaryTitleStyles(this: TextAttribute, fontStyle: FontStyle): this {
  this.fontSize(`${getResourceValue('sys.float.subheader_title_font_size')}fp`);
  this.fontColor(fontStyle?.fontColor ?? $r('sys.color.font_primary'));
  this.fontWeight(fontStyle?.fontWeight);
  this.maxLines(fontStyle?.maxLines);
  this.textOverflow({ overflow: TextOverflow.Ellipsis });
  this.align(fontStyle?.alignment);
  return this;
}

function pressedStyle(instance: CommonMethod) {
  instance.backgroundColor($r('sys.color.interactive_pressed'))
}

function disabledStyle(instance: CommonMethod) {
  instance.opacity(getResourceValue('sys.float.interactive_disable'))
}

class SubHeaderModifier implements AttributeModifier<RowAttribute> {
  public isAgeing: boolean = false;

  applyNormalAttribute(instance: RowAttribute): void {
    if (this.isAgeing) {
      instance.width('100%')
    } else {
    }
  }
}

interface ResourceInfo {
  resourceId: long,
  defaultValue: number,
  resourceValue?: number,
}

const RESOURCE_CACHE_MAP: HashMap<string, ResourceInfo> = new HashMap<string, ResourceInfo>();
// padding_level0: 125830919, 0
RESOURCE_CACHE_MAP.set('sys.float.padding_level0', { resourceId: 125830919, defaultValue: 0 });
// padding_level1: 125830920, 2
RESOURCE_CACHE_MAP.set('sys.float.padding_level1', { resourceId: 125830920, defaultValue: 2 });
// padding_level2: 125830921, 4
RESOURCE_CACHE_MAP.set('sys.float.padding_level2', { resourceId: 125830921, defaultValue: 4 });
// padding_level3: 125830922, 6
RESOURCE_CACHE_MAP.set('sys.float.padding_level3', { resourceId: 125830922, defaultValue: 6 });
// padding_level4: 125830923, 8
RESOURCE_CACHE_MAP.set('sys.float.padding_level4', { resourceId: 125830923, defaultValue: 8 });
// padding_level6: 125830925, 12
RESOURCE_CACHE_MAP.set('sys.float.padding_level6', { resourceId: 125830925, defaultValue: 12 });
// padding_level8: 125830927, 16
RESOURCE_CACHE_MAP.set('sys.float.padding_level8', { resourceId: 125830927, defaultValue: 16 });
// margin_left: 125830936, 16
RESOURCE_CACHE_MAP.set('sys.float.margin_left', { resourceId: 125830936, defaultValue: 16 });
// margin_right: 125830937, 16
RESOURCE_CACHE_MAP.set('sys.float.margin_right', { resourceId: 125830937, defaultValue: 16 });
// outline_extra_larger: 125830951, 2
RESOURCE_CACHE_MAP.set('sys.float.outline_extra_larger', { resourceId: 125830951, defaultValue: 2 });
// corner_radius_level4: 125830909, 8
RESOURCE_CACHE_MAP.set('sys.float.corner_radius_level4', { resourceId: 125830909, defaultValue: 8 });
// Subtitle_S: 125830969, 14
RESOURCE_CACHE_MAP.set('sys.float.Subtitle_S', { resourceId: 125830969, defaultValue: 14 });
// subheader_title_font_size: 125834265, 18
RESOURCE_CACHE_MAP.set('sys.float.subheader_title_font_size', { resourceId: 125834265, defaultValue: 18 });
// Body_L: 125830970, 16
RESOURCE_CACHE_MAP.set('sys.float.Body_L', { resourceId: 125830970, defaultValue: 16 });
// interactive_disable: 125831067, 0.4
RESOURCE_CACHE_MAP.set('sys.float.interactive_disable', { resourceId: 125831067, defaultValue: 0.4 });
// subheader_single_title_height: 125834252 56
RESOURCE_CACHE_MAP.set('sys.float.subheader_single_title_height', { resourceId: 125834252, defaultValue: 56 });
// subheader_single_subtitle_height: 125834253 56
RESOURCE_CACHE_MAP.set('sys.float.subheader_single_subtitle_height', { resourceId: 125834253, defaultValue: 56 });
// subheader_double_height: 125834254 72
RESOURCE_CACHE_MAP.set('sys.float.subheader_double_height', { resourceId: 125834254, defaultValue: 72 });
// subheader_title_font_weight: 125834255 700
RESOURCE_CACHE_MAP.set('sys.float.subheader_title_font_weight', { resourceId: 125834255, defaultValue: 700 });

@CustomLayout
@Component
export struct SubHeader {
  @PropRef icon: ResourceStr | undefined = undefined;
  iconSymbolOptions?: SymbolOptions;
  @PropRef primaryTitle: ResourceStr | undefined = undefined;
  @State primaryTitleModifier: TextModifier = new TextModifier();
  @PropRef secondaryTitle: ResourceStr | undefined = undefined;
  @State secondaryTitleModifier: TextModifier = new TextModifier();
  @State subHeaderModifier: SubHeaderModifier = new SubHeaderModifier();
  select?: SelectOptions;
  @PropRef operationType?: OperationType = OperationType.BUTTON;
  operationItem: Array<OperationOption> = [] as Array<OperationOption>;
  operationSymbolOptions?: Array<SymbolOptions>;
  @State fontSize: number = 1;
  @State ageing: boolean = true;
  // 内部变量
  @State textArrowBgColor: ResourceColor = $r('sys.color.ohos_id_color_sub_background_transparent');
  @State buttonBgColor: ResourceColor = $r('sys.color.ohos_id_color_sub_background_transparent');
  @State selectedIndex: int = -1;
  @State selectValue: ResourceStr | undefined = '';
  @BuilderParam titleBuilder?: () => void;
  @PropRef contentMargin: LocalizedMargin | undefined = undefined;
  @PropRef contentPadding: LocalizedPadding | undefined = undefined;
  subHeaderMargin: LocalizedMargin = {
    start: LengthMetrics.vp(getResourceValue('sys.float.margin_left')),
    end: LengthMetrics.vp(getResourceValue('sys.float.margin_right')),
  } as LocalizedMargin;
  @Provide subHeaderTheme: SubHeaderTheme = new SubHeaderTheme();
  isFollowingSystemFontScale: boolean = false;
  appMaxFontScale: number = 3.2;

  onWillApplyTheme(theme: Theme) {
    this.subHeaderTheme.fontPrimaryColor = theme.colors.fontPrimary;
    this.subHeaderTheme.fontSecondaryColor = theme.colors.fontSecondary;
    this.subHeaderTheme.fontButtonColor = theme.colors.fontEmphasize;
    this.subHeaderTheme.iconArrowColor = theme.colors.iconTertiary;
    this.subHeaderTheme.textArrowHoverBgColor = theme.colors.interactiveHover;
    this.subHeaderTheme.borderFocusColor = theme.colors.interactiveFocus;
    this.subHeaderTheme.leftIconColor = theme.colors.iconSecondary;
    this.subHeaderTheme.rightIconColor = theme.colors.iconPrimary;
  }

  commonContentPadding(instance: CommonMethod) {
    instance.padding({
      end: LengthMetrics.vp(getResourceValue('sys.float.padding_level0')),
      top: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
        : LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
      bottom: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
        : LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
    } as LocalizedPadding)
  }

  commonListPadding(instance: CommonMethod) {
    instance.padding({
      end: LengthMetrics.vp(getResourceValue('sys.float.padding_level6')),
      top: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
        : LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
      bottom: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
        : LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
    } as LocalizedPadding)
  }

  rightAreaClickEvent(instance: CommonMethod) {
    instance.onKeyEvent((event: KeyEvent) => {
      if (!event) {
        return false;
      }
      if ((event.keyCode === KeyCode.KEYCODE_SPACE || event.keyCode === KeyCode.KEYCODE_ENTER) &&
        event.type === KeyType.Down) {
        if ((this.operationType === OperationType.TEXT_ARROW || this.operationType === OperationType.BUTTON) &&
        this.operationItem && this.operationItem.length > 0 && this.operationItem[0].action) {
          (this.operationItem[0].action as () => void)();
        }
        event.stopPropagation();
      }
    })
    instance.onClick((event: ClickEvent) => {
      if ((this.operationType === OperationType.TEXT_ARROW || this.operationType === OperationType.BUTTON) &&
      this.operationItem && this.operationItem.length > 0 && this.operationItem[0].action) {
        (this.operationItem[0].action as () => void)();
      }
    })
    instance.onTouch((event: TouchEvent) => {
      if (event.type === TouchType.Down) {
        if (this.operationType === OperationType.TEXT_ARROW) {
          this.textArrowBgColor = $r('sys.color.interactive_pressed');
        }
        if (this.operationType === OperationType.BUTTON) {
          this.buttonBgColor = $r('sys.color.interactive_pressed');
        }
      }
      if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
        if (this.operationType === OperationType.TEXT_ARROW) {
          this.textArrowBgColor = $r('sys.color.ohos_id_color_sub_background_transparent');
        }
        if (this.operationType === OperationType.BUTTON) {
          this.buttonBgColor = $r('sys.color.ohos_id_color_sub_background_transparent');
        }
      }
    })
  }

  updateFontScale(): number {
    try {
      let uiContext: UIContext = this.getUIContext();
      let systemFontScale = 1.0;
      if (uiContext.getHostContext() !== undefined) {
        systemFontScale = (uiContext.getHostContext() as common.UIAbilityContext)?.config?.fontSizeScale ?? 1;
      }
      if (!this.isFollowingSystemFontScale) {
        return 1;
      }
      return Math.min(systemFontScale, this.appMaxFontScale);
    } catch (exception) {
      let code: number = (exception as BusinessError).code;
      let message: string = (exception as BusinessError).message;
      hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${code}, message: ${message}`);
      return 1;
    }
  }

  aboutToAppear(): void {
    let uiContext: UIContext = this.getUIContext();
    this.isFollowingSystemFontScale = uiContext.isFollowingSystemFontScale();
    this.appMaxFontScale = uiContext.getMaxFontScale();
    this.fontSize = this.updateFontScale();
    if (this.isSuitableAging()) {
      this.ageing = true;
      this.subHeaderModifier.isAgeing = this.ageing;
    } else {
      this.ageing = false;
      this.subHeaderModifier.isAgeing = this.ageing;
    }
    if (this.select) {
      this.selectedIndex = this.select?.selected as int;
      this.selectValue = this.select?.value as string;
    }
  }

  private isSuitableAging(): boolean | null {
    return (this.fontSize >= MIN_FONT_SIZE) && ((this.operationType === OperationType.TEXT_ARROW) ||
      this.operationType === OperationType.BUTTON) && this.operationItem !== undefined &&
      ((this.operationItem as  OperationOption[]).length > 0) && this.operationItem[0].value !== '';
  }

  private isLeftAreaAccessibilityGroup(): boolean {
    if (this.titleBuilder || this.secondaryTitle) {
      return true;
    }
    if (this.select) {
      return false;
    }
    return true;
  }

  build() {
    if (this.isSuitableAging()) {
      Column() {
        Row() {
          this.leftArea();
        }
        .margin({
          top: LengthMetrics.vp(getResourceValue('sys.float.padding_level8')),
          bottom: LengthMetrics.vp(getResourceValue('sys.float.padding_level1')),
        } as LocalizedMargin)
        .padding({
          start: this.contentMargin ? this.contentMargin?.start :
          LengthMetrics.vp(getResourceValue('sys.float.margin_left')),
          end: this.contentMargin ? this.contentMargin?.end :
          LengthMetrics.vp(getResourceValue('sys.float.margin_right')),
        } as LocalizedPadding)
        .width('100%')
        .accessibilityGroup(this.isLeftAreaAccessibilityGroup())
        .accessibilityDescription(this.select ? '' :
          Util.getStringByResource((this.getUIContext().getHostContext() as common.Context), 125834353, ''))

        if (this.isRightAreaExists()) {
          this.rightAreaParentAging();
        }
      }
      .constraintSize({ minHeight: this.getMinHeight() })
      .padding(this.getAreaPadding())
      .alignItems(HorizontalAlign.Start)
    } else {
      Flex({ direction: FlexDirection.Row, alignItems: ItemAlign.End }) {
        Row() {
          this.leftArea();
        }
        .margin({
          top: this.fontSize >= MIN_FONT_SIZE ? getResourceValue('sys.float.padding_level8') : '',
          bottom: this.fontSize >= MIN_FONT_SIZE ? getResourceValue('sys.float.padding_level4') : '',
        } as Margin)
        .width('100%')
        .flexShrink(1)
        .accessibilityGroup(this.isLeftAreaAccessibilityGroup())
        .accessibilityDescription(this.select ? '' :
          Util.getStringByResource((this.getUIContext().getHostContext() as common.Context), 125834353, ''))

        if (this.isRightAreaExists()) {
          this.rightAreaParent();
        }
      }
      .constraintSize({ minHeight: this.getMinHeight() })
      .margin(this.contentMargin ?? this.subHeaderMargin)
      .padding(this.getAreaPadding())
    }
  }

  private isRightAreaExists(): boolean {
    if (this.operationItem && this.operationItem.length > 0) {
      return true;
    }
    if (this.operationType === OperationType.LOADING) {
      return true;
    }
    return false;
  }

  private getRightAreaAccessibilityLevel(): string {
    if (this.operationItem![0].accessibilityLevel && this.operationItem![0].accessibilityLevel !== '') {
      return this.operationItem![0].accessibilityLevel as string;
    }
    return 'yes';
  }

  rightAreaParentAgingStyles(instance: CommonMethod) {
    instance.margin({
      bottom: getResourceValue('sys.float.padding_level4'),
    } as Margin)
    instance.padding({
      // 'sys.float.margin_left' id,value: 16vp
      start: LengthMetrics.vp(((this.contentMargin ? (this.contentMargin?.start ?
        this.contentMargin?.start?.value : 0) : getResourceValue('sys.float.margin_left')) as number) - PADDING_LEFT),
      // 'sys.float.margin_right' id,value: 16vp
      end: this.contentMargin ? this.contentMargin?.end :
      LengthMetrics.vp(getResourceValue('sys.float.margin_right')),
    } as LocalizedPadding)
    instance.accessibilityLevel(this.operationType === OperationType.BUTTON ||
      this.operationType === OperationType.TEXT_ARROW ? this.getRightAreaAccessibilityLevel() : 'no')
  }

  private getRightAreaAccessibilityText(): string | undefined {
    if (!this.operationItem || this.operationItem.length <= 0) {
      return '';
    }
    if (Util.isResourceType(this.operationItem[0].accessibilityText)) {
      return (this.getUIContext().getHostContext() as common.Context).resourceManager
        .getStringSync((this.operationItem[0].accessibilityText as Resource).id);
    } else if (this.operationItem[0].accessibilityText && this.operationItem[0].accessibilityText !== '') {
      return this.operationItem[0].accessibilityText as string;
    } else {
      if (this.operationType === OperationType.TEXT_ARROW && this.operationItem[0].value.toString().length <= 0) {
        // 播报：更多、more等, 使用的字段是：sys.string.ohos_toolbar_more
        return Util.getStringByResource((this.getUIContext().getHostContext() as common.Context), 125833704, '');
      }
    }
    return '';
  }

  private getAccessibilityDescription(): string | undefined {
    if (!this.operationItem || this.operationItem.length <= 0) {
      return '';
    }
    if (Util.isResourceType(this.operationItem[0].accessibilityDescription)) {
      return (this.getUIContext().getHostContext() as common.Context).resourceManager
        .getStringSync((this.operationItem[0].accessibilityDescription as Resource).id);
    } else if (this.operationItem[0].accessibilityDescription &&
      this.operationItem[0].accessibilityDescription !== '') {
      return this.operationItem[0].accessibilityDescription as string;
    }
    return '';
  }

  @Builder
  rightAreaParentAging(): void {
    if (this.operationType === OperationType.BUTTON || this.operationType === OperationType.TEXT_ARROW) {
      Button({ type: ButtonType.Normal, stateEffect: false } as ButtonOptions) {
        this.rightArea();
      }
      .focusable(this.operationItem ? true : false)
      .align(Alignment.Start)
      .applyStyles(this.rightAreaClickEvent)
      .applyStyles(this.rightAreaParentAgingStyles)
      .backgroundColor($r('sys.color.ohos_id_color_sub_background_transparent'))
      .hoverEffect(HoverEffect.None)
      .accessibilityGroup(true)
      .accessibilityText(this.getRightAreaAccessibilityText())
      .accessibilityDescription(this.getAccessibilityDescription())
    } else {
      Row() {
        this.rightArea();
      }
      .focusable(this.operationItem && this.operationType !== OperationType.LOADING ? true : false)
      .justifyContent(FlexAlign.Start)
      .applyStyles(this.rightAreaClickEvent)
      .applyStyles(this.rightAreaParentAgingStyles)
    }
  }

  rightAreaParentStyles(instance: CommonMethod) {
    instance.constraintSize({
      maxWidth: this.getRightAreaMaxWidth(),
      minWidth: this.getRightAreaMinWidth(),
      minHeight: MIN_HOT_AREA_LENGTH,
    })
    instance.flexShrink(0)
    instance.accessibilityLevel(this.operationType === OperationType.BUTTON ||
      this.operationType === OperationType.TEXT_ARROW ? this.getRightAreaAccessibilityLevel() : 'no')
  }

  @Builder
  rightAreaParent(): void {
    if (this.operationType === OperationType.BUTTON || this.operationType === OperationType.TEXT_ARROW) {
      Button({ type: ButtonType.Normal, buttonStyle: ButtonStyleMode.TEXTUAL, stateEffect: false } as ButtonOptions) {
        this.rightArea();
      }
      .focusable(this.operationItem ? true : false)
      .margin(INDEX_ZERO)
      .padding(INDEX_ZERO)
      .align(Alignment.BottomEnd)
      .applyStyles(this.rightAreaClickEvent)
      .applyStyles(this.rightAreaParentStyles)
      .hoverEffect(HoverEffect.None)
      .backgroundColor($r('sys.color.ohos_id_color_sub_background_transparent'))
      .accessibilityGroup(true)
      .accessibilityText(this.getRightAreaAccessibilityText())
      .accessibilityDescription(this.getAccessibilityDescription())
    } else {
      Row() {
        this.rightArea();
      }
      .focusable(this.operationItem && this.operationType !== OperationType.LOADING ? true : false)
      .justifyContent(FlexAlign.End)
      .alignItems(VerticalAlign.Bottom)
      .applyStyles(this.rightAreaClickEvent)
      .applyStyles(this.rightAreaParentStyles)
    }
  }

  onMeasureSize(selfLayoutInfo: GeometryInfo, children: Measurable[], constraint: ConstraintSizeOptions): SizeResult {
    let result: SizeResult = { width: selfLayoutInfo.width, height: selfLayoutInfo.height };
    this.fontSize = this.updateFontScale();
    if (this.isSuitableAging()) {
      this.ageing = true;
      this.subHeaderModifier.isAgeing = this.ageing;
    } else {
      this.ageing = false;
      this.subHeaderModifier.isAgeing = this.ageing;
    }
    children.forEach((child) => {
      if (constraint.maxHeight !== undefined) {
        constraint.minHeight = Math.min(Number(this.getMinHeight() as number), Number(constraint.maxHeight as number));
        let childMeasureResult = child?.measure(constraint);
        if (childMeasureResult) {
          result.height = childMeasureResult.height;
        }
        result.width = Number(constraint.maxWidth as number);
      }
    })
    return result;
  }

  onPlaceChildren(selfLayoutInfo: GeometryInfo, children: Layoutable[], constraint: ConstraintSizeOptions): void {
    children.forEach((child) => {
      child.layout({ x: 0, y: 0 });
    })
  }

  private getRightAreaMaxWidth(): Length {
    if (this.operationType === OperationType.ICON_GROUP && (this.operationItem && this.operationItem.length > 0)) {
      return '100%';
    }
    return MAX_RIGHT_WIDTH;
  }

  private getRightAreaMinWidth(): Length {
    if (this.operationItem && this.operationItem.length > 0) {
      return MIN_HOT_AREA_LENGTH;
    }
    return 0;
  }

  private getMinHeight(): Length {
    if (this.secondaryTitle && this.icon) {
      return getResourceValue('sys.float.subheader_single_subtitle_height');
    } else if (this.secondaryTitle && this.primaryTitle) {
      return getResourceValue('sys.float.subheader_double_height');
    } else if (this.primaryTitle || this.select) {
      return getResourceValue('sys.float.subheader_single_title_height');
    }
    return getResourceValue('sys.float.subheader_single_subtitle_height');
  }

  private getTextArrowPaddingLeft(): LengthMetrics {
    if (this.operationItem && this.operationItem.length > 0 && this.operationItem[0].value) {
      return LengthMetrics.vp(getResourceValue('sys.float.padding_level1'));
    }
    return LengthMetrics.vp(getResourceValue('sys.float.padding_level0'));
  }

  private getTextArrowMarginRight(): LengthMetrics {
    if (this.operationItem && this.operationItem.length > 0 && this.operationItem[0].value) {
      return LengthMetrics.vp(PADDING_LEVEL_2 + ARROW_ICON_WIDTH);
    }
    return LengthMetrics.vp(ARROW_ICON_WIDTH);
  }

  private getAreaPadding(): LocalizedPadding {
    if (this.contentPadding) {
      return this.contentPadding as LocalizedPadding;
    }
    let padding: LocalizedPadding = {};
    if (!this.titleBuilder && ((this.secondaryTitle && this.icon) ||
      (!this.primaryTitle && this.secondaryTitle))) {
      padding = {
        start: LengthMetrics.vp(getResourceValue('sys.float.padding_level6')),
        end: LengthMetrics.vp(getResourceValue('sys.float.padding_level6')),
      }
    } else if (this.select) {
      padding = {
        top: LengthMetrics.vp(getResourceValue('sys.float.padding_level2')),
        bottom: LengthMetrics.vp(getResourceValue('sys.float.padding_level2')),
      }
    }
    return padding;
  }

  @Builder
  leftArea(): void {
    if (this.titleBuilder) {
      (this.titleBuilder as () => void)();
    } else if (this.secondaryTitle && this.icon) {
      this.IconSecondaryTitleStyle({
        content: this.secondaryTitle as ResourceStr,
        iconOptions: {
          icon: this.icon as ResourceStr,
          symbolicIconOption: this.iconSymbolOptions,
        } as IconOptions,
      });
    } else if (this.secondaryTitle && this.primaryTitle) {
      this.SubTitleStyle({ content: this.primaryTitle as ResourceStr, subContent: this.secondaryTitle as ResourceStr });
    } else if (this.secondaryTitle) {
      this.SecondTitleStyle({ content: this.secondaryTitle as ResourceStr });
    } else if (this.select) {
      this.SelectStyle(this.select as SelectOptions);
    } else if (this.primaryTitle) {
      this.PrimaryTitleStyle({ content: this.primaryTitle as ResourceStr });
    } else {
      // 其他不支持场景
      this.dummyFunction();
    }
  }

  @Builder
  rightArea(): void {
    if (this.operationType === OperationType.BUTTON && (this.operationItem && this.operationItem.length > 0)) {
      this.ButtonStyle(this.operationItem[0]);
    }
    if (this.operationType === OperationType.TEXT_ARROW && (this.operationItem && this.operationItem.length > 0)) {
      this.TextArrowStyle(this.operationItem[0]);
    }
    if (this.operationType === OperationType.ICON_GROUP && (this.operationItem && this.operationItem.length > 0)) {
      this.IconGroupStyle(this.operationItem);
    }
    if (this.operationType === OperationType.LOADING) {
      this.LoadingProcessStyle();
    }
    if (this.operationType === undefined && (this.operationItem && this.operationItem.length > 0)) {
      this.ButtonStyle(this.operationItem[0]);
    }
  }

  @Builder
  IconSecondaryTitleStyle($$: ContentIconOption): void {
    Flex({ direction: FlexDirection.Row, alignItems: ItemAlign.Center }) {
      if (Util.isSymbolResource($$.iconOptions?.icon)) {
        SymbolGlyph($$.iconOptions?.icon as Resource)
          .fontSize($$.iconOptions?.symbolicIconOption?.fontSize ?
          Util.symbolFontSize($$.iconOptions?.symbolicIconOption?.fontSize as Length) : LEFT_ICON_SIZE)
          .fontColor($$.iconOptions?.symbolicIconOption?.fontColor ?? [this.subHeaderTheme.leftIconColor])
          .fontWeight($$.iconOptions?.symbolicIconOption?.fontWeight)
          .renderingStrategy($$.iconOptions?.symbolicIconOption?.renderingStrategy)
          .effectStrategy($$.iconOptions?.symbolicIconOption?.effectStrategy)
          .margin({ end: LengthMetrics.vp(getResourceValue('sys.float.padding_level4')) } as LocalizedMargin)
          .flexShrink(0)
      } else {
        Image($$.iconOptions?.icon as ResourceStr)
          .fillColor(this.subHeaderTheme.leftIconColor)
          .width(LEFT_ICON_SIZE)
          .height(LEFT_ICON_SIZE)
          .margin({ end: LengthMetrics.vp(getResourceValue('sys.float.padding_level4')) } as LocalizedMargin)
          .draggable(false)
          .flexShrink(0)
      }
      Text($$.content)
        .secondaryTitleStyles({
          maxLines: DOUBLE_LINE_NUM,
          fontWeight: FontWeight.Medium,
          alignment: Alignment.Start,
          fontColor: this.subHeaderTheme.fontSecondaryColor,
        })
        .attributeModifier(this.secondaryTitleModifier)
        .flexShrink(1)
    }
    .applyStyles(this.commonListPadding)
  }

  @Builder
  SubTitleStyle($$: ContentIconOption): void {
    Column() {
      Text($$.content)
        .primaryTitleStyles({
          fontWeight: getResourceValue('sys.float.subheader_title_font_weight') as int,
          maxLines: DOUBLE_LINE_NUM,
          alignment: Alignment.Start,
          fontColor: this.subHeaderTheme.fontPrimaryColor,
        })
        .attributeModifier(this.primaryTitleModifier)
      Text($$.subContent)
        .secondaryTitleStyles({
          maxLines: DOUBLE_LINE_NUM,
          fontWeight: FontWeight.Regular,
          alignment: Alignment.Start,
          fontColor: this.subHeaderTheme.fontSecondaryColor,
        })
        .margin({
          top: getResourceValue('sys.float.padding_level1'),
        } as Margin)
        .attributeModifier(this.secondaryTitleModifier)
    }
    .width('100%')
    .applyStyles(this.commonContentPadding)
    .alignItems(HorizontalAlign.Start)
  }

  @Builder
  SecondTitleStyle($$: ContentIconOption): void {
    Text($$.content)
      .secondaryTitleStyles({
        maxLines: DOUBLE_LINE_NUM,
        fontWeight: FontWeight.Medium,
        alignment: Alignment.Start,
        fontColor: this.subHeaderTheme.fontSecondaryColor,
      })
      .attributeModifier(this.secondaryTitleModifier)
      .applyStyles(this.commonListPadding)
  }

  @Builder
  SelectStyle(selectParam: SelectOptions): void {
    Select(selectParam.options)
      .selected(this.selectedIndex)
      .value(this.selectValue)
      .defaultFocus(selectParam.defaultFocus)
      .onSelect((index: int, value?: string): void => {
        this.selectedIndex = index;
        if (value) {
          this.selectValue = value;
        }
        if (selectParam.onSelect) {
          (selectParam?.onSelect as (index: int, value?: string) => void)(index, value);
        }
      })
      .font({
        size: `${getResourceValue('sys.float.Body_L')}fp`,
        weight: FontWeight.Medium,
      })
  }

  @Builder
  PrimaryTitleStyle($$: ContentIconOption): void {
    Text($$.content)
      .primaryTitleStyles({
        fontWeight: getResourceValue('sys.float.subheader_title_font_weight') as int,
        maxLines: DOUBLE_LINE_NUM,
        alignment: Alignment.Start,
        fontColor: this.subHeaderTheme.fontPrimaryColor,
      })
      .attributeModifier(this.primaryTitleModifier)
      .applyStyles(this.commonContentPadding)
  }

  @Builder
  ButtonStyle(button: OperationOption): void {
    if (button) {
      Button({ type: ButtonType.Normal, stateEffect: false } as ButtonOptions) {
        Text(button.value)
          .secondaryTitleStyles({
            fontWeight: FontWeight.Medium,
            maxLines: DOUBLE_LINE_NUM,
            fontColor: this.subHeaderTheme.fontButtonColor,
          })
          .defaultFocus(button.defaultFocus)
          .focusable(true)
      }
      .focusable(true)
      .focusBox({
        margin: new LengthMetrics(INDEX_ZERO, LengthUnit.VP),
        strokeColor: ColorMetrics.resourceColor(this.subHeaderTheme.borderFocusColor),
        strokeWidth: LengthMetrics.vp(getResourceValue('sys.float.outline_extra_larger')),
      })
      .padding({
        start: LengthMetrics.vp(getResourceValue('sys.float.padding_level1')),
        end: LengthMetrics.vp(getResourceValue('sys.float.padding_level1')),
        top: LengthMetrics.vp(getResourceValue('sys.float.padding_level2')),
        bottom: LengthMetrics.vp(getResourceValue('sys.float.padding_level2')),
      } as LocalizedPadding)
      .margin({
        start: this.ageing ?
        LengthMetrics.vp(LengthMetrics.vp(getResourceValue('sys.float.padding_level0')).value +
        this.leftIconMargin().value) :
        LengthMetrics.vp(LengthMetrics.vp(getResourceValue('sys.float.padding_level4')).value +
        this.leftIconMargin().value),
        bottom: LengthMetrics.vp(this.ageing ? getResourceValue('sys.float.padding_level0') :
        getResourceValue('sys.float.padding_level2')),
      } as LocalizedMargin)
      .backgroundColor(this.buttonBgColor)
      .constraintSize({ minHeight: OPERATE_ITEM_LENGTH })
      .align(Alignment.End)
      .borderRadius(getResourceValue('sys.float.corner_radius_level4'))
      .onHover((isHover: boolean): void => {
        if (isHover) {
          this.buttonBgColor = this.subHeaderTheme.textArrowHoverBgColor;
        } else {
          this.buttonBgColor = $r('sys.color.ohos_id_color_sub_background_transparent');
        }
      })
      .stateStyles({
        pressed: pressedStyle,
        disabled: disabledStyle,
      })
    }
  }

  private leftIconMargin(): LengthMetrics {
    if (this.titleBuilder) {
      return LengthMetrics.vp(0);
    }
    if (this.icon && Util.isSymbolResource(this.icon as Resource)) {
      return this.ageing ? LengthMetrics.vp((this.iconSymbolOptions?.fontSize ?
      Util.numberToSize(this.iconSymbolOptions?.fontSize as Length) : LEFT_ICON_SIZE_NUMBER) +
        LEFT_TEXT_NUMBER) : LengthMetrics.vp(0);
    } else {
      return (this.ageing && this.icon) ? LengthMetrics.vp(LEFT_ICON_SIZE_NUMBER +
        LEFT_TEXT_NUMBER) : LengthMetrics.vp(0);
    }
  }

  @Builder
  TextStyle(textArrow: OperationOption): void {
    Row() {
      if (textArrow) {
        Text(textArrow.value)
          .secondaryTitleStyles({
            maxLines: DOUBLE_LINE_NUM,
            fontWeight: FontWeight.Regular,
            alignment: Alignment.End,
            fontColor: this.subHeaderTheme.fontSecondaryColor,
          })
          .focusable(true)
          .defaultFocus(textArrow.defaultFocus)
          .margin({
            end: this.getTextArrowMarginRight(),
          } as LocalizedMargin)
      }
    }
    .attributeModifier(this.subHeaderModifier)
    .alignItems(VerticalAlign.Center)
    .focusable(true)
    .constraintSize({ minHeight: OPERATE_ITEM_LENGTH })
    .padding({
      start: this.getTextArrowPaddingLeft(),
      top: this.ageing ? LengthMetrics.vp(0) : LengthMetrics.vp(getResourceValue('sys.float.padding_level2')),
      bottom: this.ageing ? LengthMetrics.vp(0) : LengthMetrics.vp(getResourceValue('sys.float.padding_level2')),
    } as LocalizedPadding)
  }

  @Builder
  ArrowStyle(): void {
    Row() {
      SymbolGlyph($r('sys.symbol.chevron_right'))
        .fontSize(RIGHT_SINGLE_ICON_SIZE)
        .fontColor([this.subHeaderTheme.iconArrowColor])
        .draggable(false)
        .width(ARROW_ICON_WIDTH)
        .height(OPERATE_ITEM_LENGTH)
    }
    .justifyContent(FlexAlign.End)
  }

  @Builder
  TextArrowStyle(textArrow: OperationOption): void {
    if (textArrow && textArrow.value && textArrow.value.toString().length > 0) {
      Stack() {
        Button({ type: ButtonType.Normal, buttonStyle: ButtonStyleMode.TEXTUAL, stateEffect: false } as ButtonOptions) {
          TextArrowLayout() {
            ForEach([INDEX_ZERO, INDEX_ONE], (item: Int, index: int) => {
              if (index === INDEX_ZERO) {
                this.TextStyle(textArrow);
              } else {
                this.ArrowStyle();
              }
            });
          }
        }
        .padding(INDEX_ZERO)
        .margin({ start: this.leftIconMargin() } as LocalizedMargin)
        .backgroundColor(this.textArrowBgColor)
        .focusBox({
          margin: new LengthMetrics(INDEX_ZERO, LengthUnit.VP),
          strokeColor: ColorMetrics.resourceColor(this.subHeaderTheme.borderFocusColor),
          strokeWidth: LengthMetrics.vp(getResourceValue('sys.float.outline_extra_larger')),
        })
        .borderRadius(getResourceValue('sys.float.corner_radius_level4'))
        .stateStyles({
          pressed: pressedStyle,
          disabled: disabledStyle,
        })
        .onHover((isHover: boolean): void => {
          if (isHover) {
            this.textArrowBgColor = this.subHeaderTheme.textArrowHoverBgColor;
          } else {
            this.textArrowBgColor = $r('sys.color.ohos_id_color_sub_background_transparent');
          }
        })
      }
      .focusable(true)
      .align(this.ageing ? Alignment.Start : Alignment.End)
      .margin({
        start: LengthMetrics.vp(this.ageing ? getResourceValue('sys.float.padding_level0') :
        getResourceValue('sys.float.padding_level4')),
        bottom: LengthMetrics.vp(this.ageing ? getResourceValue('sys.float.padding_level0') :
        getResourceValue('sys.float.padding_level2')),
      } as LocalizedMargin)
    } else {
      Row() {
        Button({ type: ButtonType.Normal, stateEffect: false } as ButtonOptions) {
          SymbolGlyph($r('sys.symbol.chevron_right'))
            .fontSize(RIGHT_SINGLE_ICON_SIZE)
            .fontColor([this.subHeaderTheme.iconArrowColor])
            .draggable(false)
            .focusable(true)
            .width(ARROW_ICON_WIDTH)
            .height(OPERATE_ITEM_LENGTH)
        }
        .width(ARROW_ICON_WIDTH)
        .height(OPERATE_ITEM_LENGTH)
        .backgroundColor(this.textArrowBgColor)
        .focusBox({
          margin: new LengthMetrics(INDEX_ZERO, LengthUnit.VP),
          strokeColor: ColorMetrics.resourceColor(this.subHeaderTheme.borderFocusColor),
          strokeWidth: LengthMetrics.vp(getResourceValue('sys.float.outline_extra_larger')),
        })
        .borderRadius(getResourceValue('sys.float.corner_radius_level4'))
        .stateStyles({
          pressed: pressedStyle,
          disabled: disabledStyle,
        })
        .onHover((isHover: boolean): void => {
          if (isHover) {
            this.textArrowBgColor = this.subHeaderTheme.textArrowHoverBgColor;
          } else {
            this.textArrowBgColor = $r('sys.color.ohos_id_color_sub_background_transparent');
          }
        })
        .focusable(true)
        .margin({
          start: LengthMetrics.vp(this.ageing ? getResourceValue('sys.float.padding_level0') :
          getResourceValue('sys.float.padding_level4')),
          bottom: LengthMetrics.vp(this.ageing ? getResourceValue('sys.float.padding_level0') :
          getResourceValue('sys.float.padding_level2')),
        } as LocalizedMargin)
      }
      .focusable(true)
      .constraintSize({ minWidth: this.getRightAreaMinWidth() })
      .justifyContent(FlexAlign.End)
    }
  }

  @Builder
  IconGroupStyle(operationItem: Array<OperationOption>): void {
    Row() {
      ForEach(operationItem, (item: OperationOption, index: int) => {
        if (index <= INDEX_TWO) {
          SingleIconStyle({
            item: {
              iconOptions: {
                icon: item.value as Resource,
                symbolicIconOption: this.operationSymbolOptions &&
                  (this.operationSymbolOptions as SymbolOptions[]).length > index ?
                (this.operationSymbolOptions as SymbolOptions[])[index.toInt()] : null,
              } as IconOptions,
              action: item.action,
              defaultFocus: item.defaultFocus,
              accessibilityLevel: item.accessibilityLevel,
              accessibilityText: item.accessibilityText,
              accessibilityDescription: item.accessibilityDescription,
            },
            isSingleIcon: this.operationItem?.length === SINGLE_ICON_NUMBER,
          })
        } else {
          // 最大支持3个ICON,此场景不支持
        }
      })
    }
    .justifyContent(FlexAlign.End)
    .focusable(true)
  }

  @Builder
  LoadingProcessStyle(): void {
    Row() {
      LoadingProgress()
        .width(OPERATE_ITEM_LENGTH)
        .height(OPERATE_ITEM_LENGTH)
        .color($r('sys.color.icon_secondary'))
    }
    .justifyContent(FlexAlign.End)
    .padding({
      top: getResourceValue('sys.float.padding_level2'),
      bottom: getResourceValue('sys.float.padding_level2'),
    } as Padding)
    .margin({
      start: LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
    } as LocalizedMargin)
  }

  @Builder
  dummyFunction(): void {
    Row() {
    }
  }
}

@Component
struct SingleIconStyle {
  @State bgColor: Resource = $r('sys.color.ohos_id_color_sub_background_transparent');
  @State isFocus: boolean = false;
  item: ContentIconOption | null = null;
  @Consume subHeaderTheme: SubHeaderTheme;
  isSingleIcon: boolean = true;

  private getRightIconAccessibilityText(): string | undefined {
    if (Util.isResourceType(this.item?.accessibilityText)) {
      return (this.getUIContext().getHostContext() as common.Context).resourceManager
        .getStringSync((this.item?.accessibilityText as Resource).id);
    } else if (this.item?.accessibilityText) {
      return this.item?.accessibilityText as string;
    }
    return '';
  }

  private getRightIconAccessibilityLevel(): string {
    if (this.item?.accessibilityLevel && this.item?.accessibilityLevel !== '') {
      return this.item?.accessibilityLevel as string;
    }
    return 'auto';
  }

  private getRightIconAccessibilityDescription(): string | undefined {
    if (Util.isResourceType(this.item?.accessibilityDescription)) {
      return (this.getUIContext().getHostContext() as common.Context).resourceManager
        .getStringSync((this.item?.accessibilityDescription as Resource).id);
    } else if (this.item?.accessibilityDescription && this.item?.accessibilityDescription !== '') {
      return this.item?.accessibilityDescription as string;
    }
    return '';
  }

  build() {
    if (this.item && this.item?.iconOptions) {
      Button({ type: ButtonType.Normal, stateEffect: false } as ButtonOptions) {
        this.IconZone();
      }
      .focusable(true)
      .defaultFocus(this.item?.defaultFocus)
      .width(SINGLE_ICON_ZONE_SIZE)
      .height(SINGLE_ICON_ZONE_SIZE)
      .padding(0)
      .align(Alignment.Center)
      .backgroundColor(this.bgColor)
      .borderRadius(getResourceValue('sys.float.corner_radius_level4'))
      .accessibilityLevel(this.getRightIconAccessibilityLevel())
      .accessibilityText(this.getRightIconAccessibilityText())
      .accessibilityDescription(this.getRightIconAccessibilityDescription())
      .focusBox({
        margin: new LengthMetrics(INDEX_ZERO, LengthUnit.VP),
        strokeColor: ColorMetrics.resourceColor(this.subHeaderTheme.borderFocusColor),
        strokeWidth: LengthMetrics.vp(getResourceValue('sys.float.outline_extra_larger')),
      })
      .stateStyles({
        pressed: pressedStyle,
        disabled: disabledStyle,
      })
      .onTouch((event: TouchEvent) => {
        if (event.type === TouchType.Down || TouchType.Cancel) {
          this.bgColor = $r('sys.color.interactive_pressed');
        }
        if (event.type === TouchType.Up) {
          this.bgColor = $r('sys.color.ohos_id_color_sub_background_transparent');
        }
      })
      .onHover((isHover: boolean): void => {
        if (isHover) {
          this.bgColor = $r('sys.color.interactive_hover');
        } else {
          this.bgColor = $r('sys.color.ohos_id_color_sub_background_transparent');
        }
      })
      .responseRegion(this.iconResponseRegion())
      .onClick((event: ClickEvent) => {
        if (this.item?.action) {
          (this.item?.action as () => void)();
        }
      })
      .margin({
        start: LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
        bottom: LengthMetrics.vp(getResourceValue('sys.float.padding_level3')),
      } as LocalizedMargin)
    }
  }

  private iconResponseRegion(): Rectangle {
    if (this.isSingleIcon) {
      return {
        x: SINGLE_ICON_REGION_X,
        y: ICON_REGION_Y,
        width: MIN_HOT_AREA_LENGTH,
        height: MIN_HOT_AREA_LENGTH,
      };
    }
    return {
      x: ICON_REGION_X,
      y: ICON_REGION_Y,
      width: MULTI_ICON_REGION_WIDTH,
      height: MIN_HOT_AREA_LENGTH,
    };
  }

  private fontSizeValue(item: ContentIconOption): Length {
    return item.iconOptions?.symbolicIconOption?.fontSize ?
    Util.symbolFontSize(item.iconOptions?.symbolicIconOption?.fontSize as Length) : RIGHT_SINGLE_ICON_SIZE;
  }

  @Builder
  IconZone(): void {
    if (this.item && this.item?.iconOptions) {
      if (Util.isSymbolResource(this.item?.iconOptions?.icon)) {
        SymbolGlyph(this.item?.iconOptions?.icon as Resource)
          .focusable(true)
          .fontSize(this.fontSizeValue(this.item as ContentIconOption))
          .fontColor(this.item?.iconOptions?.symbolicIconOption?.fontColor ?? [this.subHeaderTheme.rightIconColor])
          .fontWeight(this.item?.iconOptions?.symbolicIconOption?.fontWeight)
          .renderingStrategy(this.item?.iconOptions?.symbolicIconOption?.renderingStrategy)
          .effectStrategy(this.item?.iconOptions?.symbolicIconOption?.effectStrategy)
      } else {
        Image(this.item?.iconOptions?.icon as Resource)
          .fillColor(this.subHeaderTheme.rightIconColor)
          .width(RIGHT_SINGLE_ICON_SIZE)
          .height(RIGHT_SINGLE_ICON_SIZE)
          .focusable(true)
          .draggable(false)
      }
    }
  }
}

class Util {
  /**
   * 是否symbol资源
   * @param resourceStr  资源
   * @returns true：symbol资源；false:非symbol资源
   */
  public static isSymbolResource(resourceStr: ResourceStr | undefined): boolean {
    if (!Util.isResourceType(resourceStr)) {
      return false;
    }
    let resource = resourceStr as Resource;
    return resource?.type === RESOURCE_TYPE_SYMBOL;
  }

  /**
   * 是否Resource类型
   * @param resource 资源
   * @returns true：Resource类型；false:非Resource类型
   */
  public static isResourceType(resource: ResourceStr | Resource | undefined): boolean {
    if (!resource) {
      return false;
    }
    if (typeof resource === 'string' || typeof resource === 'undefined') {
      return false;
    }
    return true;
  }

  /**
   * get resource size
   *
   * @param resourceName resource id
   * @returns resource size
   */
  public static getNumberByResource(resourceId: long, defaultNumber: number): number {
    try {
      let resourceNumber: number = resourceManager.getSysResourceManager().getDouble(resourceId);
      if (resourceNumber === 0) {
        return defaultNumber;
      } else {
        return resourceNumber;
      }
    } catch (error) {
      let code: number = (error as BusinessError).code;
      let message: string = (error as BusinessError).message;
      hilog.error(0x3900, 'Ace', `SubHeader getNumberByResource error, code: ${code}, message: ${message}`);
      return 0;
    }
  }

  /**
   * get resource string
   *
   * @param resourceId resource id
   * @param defaultString default value
   * @returns resource string
   */
  public static getStringByResource(context: common.Context, resourceId: long, defaultString: string): string {
    try {
      let resourceString: string = context.resourceManager.getStringSync(resourceId);
      if (resourceString === '') {
        return defaultString;
      } else {
        return resourceString;
      }
    } catch (error) {
      let code: number = (error as BusinessError).code;
      let message: string = (error as BusinessError).message;
      hilog.error(0x3900, 'Ace', `SubHeader getStringByResource error, code: ${code}, message: ${message}`);
      return '';
    }
  }

  public static numberToSize(fontSize: Length): number {
    if (typeof fontSize === 'string') {
      const fontSizeNumber: number = parseInt(fontSize as string);
      return fontSizeNumber;
    } else if (typeof fontSize === 'number') {
      return fontSize as number;
    } else {
      return resourceManager.getSysResourceManager().getDouble((fontSize as Resource).id);
    }
  }

  public static symbolFontSize(fontSize: Length): Length {
    return Util.numberToSize(fontSize) + 'vp';
  }
}

function getResourceValue(resourceName: string): number {
  if (RESOURCE_CACHE_MAP.hasKey(resourceName)) {
    return (RESOURCE_CACHE_MAP.get(resourceName) as ResourceInfo).defaultValue;
  }
  return 0;
}

@CustomLayout
@Component
struct TextArrowLayout {
  @Builder
  doNothingBuilder(): void {
  };

  @BuilderParam textArrowBuilder: () => void = this.doNothingBuilder;

  onPlaceChildren(selfLayoutInfo: GeometryInfo, children: Array<Layoutable>,
    constraint: ConstraintSizeOptions) {
    if (children.length <= 0) {
      hilog.error(0x3900, 'Ace', `TextArrowLayout onPlaceChildren children is null`);
      return;
    }
    let currentX: number = 0;
    let currentY: number = 0;
    for (let index = 0; index < children.length; index++) {
      let child = children[index];
      child.layout({ x: currentX, y: currentY });
    }
  }

  onMeasureSize(selfLayoutInfo: GeometryInfo, children: Array<Measurable>,
    constraint: ConstraintSizeOptions): SizeResult {
    if (children.length <= 0) {
      hilog.error(0x3900, 'Ace', `TextArrowLayout onMeasureSize children is null`);
      return { width: 0, height: 0 };
    }
    let textArrowWidth: number = ARROW_ICON_WIDTH;
    let textArrowHeight: number = OPERATE_ITEM_LENGTH;

    let textChild: Measurable = children[INDEX_ZERO];
    let textConstraint: ConstraintSizeOptions = {
      minWidth: Math.max(textArrowWidth, Number(constraint.minWidth as number)),
      maxWidth: constraint.maxWidth,
      minHeight: Math.max(textArrowHeight, Number(constraint.minHeight as number)),
      maxHeight: constraint.maxHeight,
    };
    let textMeasureResult: MeasureResult | undefined = textChild.measure(textConstraint);
    if (textMeasureResult) {
      textArrowWidth = Math.max(textArrowWidth, textMeasureResult.width);
      textArrowHeight = Math.max(textArrowHeight, textMeasureResult.height);
    }

    let arrowChild: Measurable = children[INDEX_ONE];
    let arrowConstraint: ConstraintSizeOptions = {
      minWidth: textArrowWidth,
      maxWidth: textArrowWidth,
      minHeight: textArrowHeight,
      maxHeight: textArrowHeight,
    };
    arrowChild?.measure(arrowConstraint);
    return { width: textArrowWidth, height: textArrowHeight };
  }

  build() {
    this.textArrowBuilder();
  }
}