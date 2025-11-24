/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
  ComponentV2, ResourceStr, Builder, SelectOption, ResourceColor, Alignment, $r, TextAttribute, FlexDirection, Resource,
  TextOverflow, AttributeModifier, RowAttribute, BuilderParam, LocalizedMargin, KeyType, CommonMethod, ItemAlign, Image,
  Text, LocalizedPadding, applyStyles, Length, Flex, FontWeight, Select, Margin, Column, HorizontalAlign, KeyEvent, Row,
  ClickEvent, Array, TouchType, GeometryInfo, SymbolGlyph, Measurable, ConstraintSizeOptions, SizeResult, Button, Stack,
  ButtonType, ButtonOptions, VerticalAlign, TouchEvent, FlexAlign, ForEach, HoverEffect, LoadingProgress, Padding,
  Rectangle, Layoutable, Component, MeasureResult, CustomLayout, ClassCastError
} from '@ohos.arkui.component';
import {
  ObservedV2, Trace, Param, Local, Provider, Monitor, IMonitor, IMonitorValue, Require, Event, Consumer
} from '@ohos.arkui.stateManagement';
import { SymbolGlyphModifier, TextModifier } from '@ohos.arkui.modifier';
import resourceManager from '@ohos.resourceManager';
import hilog from '@ohos.hilog';
import HashMap from '@ohos.util.HashMap';
import { LengthMetrics, LengthUnit, ColorMetrics } from '@ohos.arkui.node';
import { Theme } from '@ohos.arkui.theme';
import common from '@ohos.app.ability.common';
import { UIContext } from '@ohos.arkui.UIContext';
import { KeyCode } from '@ohos.multimodalInput.keyCode';

const INDEX_ZERO: int = 0;
const INDEX_ONE: int = 1;
const INDEX_TWO: int = 2;
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

export declare type SubHeaderV2IconType = ResourceStr | SymbolGlyphModifier;

export interface SubHeaderV2TitleOptions {
  primaryTitle?: ResourceStr;
  primaryTitleModifier?: TextModifier;
  secondaryTitle?: ResourceStr;
  secondaryTitleModifier?: TextModifier;
}

@ObservedV2
export class SubHeaderV2Title {
  @Trace
  public primaryTitle?: ResourceStr;
  @Trace
  public primaryTitleModifier?: TextModifier;
  @Trace
  public secondaryTitle?: ResourceStr;
  @Trace
  public secondaryTitleModifier?: TextModifier;

  constructor(options: SubHeaderV2TitleOptions) {
    this.primaryTitle = options.primaryTitle;
    this.primaryTitleModifier = options.primaryTitleModifier;
    this.secondaryTitle = options.secondaryTitle;
    this.secondaryTitleModifier = options.secondaryTitleModifier;
  }
}

export type SubHeaderV2SelectOnSelect = (selectedIndex: int, selectedContent?: string) => void;

export interface SubHeaderV2SelectOptions {
  options: SelectOption[];
  selectedIndex?: int;
  selectedContent?: ResourceStr;
  onSelect?: SubHeaderV2SelectOnSelect;
  defaultFocus?: boolean;
}

export interface BuildSelectOptions {
  params: SubHeaderV2Select;
}

@ObservedV2
export class SubHeaderV2Select {
  @Trace
  public options: SelectOption[];
  @Trace
  public selectedIndex?: int;
  @Trace
  public selectedContent?: ResourceStr;
  @Trace
  public onSelect?: SubHeaderV2SelectOnSelect;
  @Trace
  public defaultFocus?: boolean;

  constructor(options: SubHeaderV2SelectOptions) {
    this.options = options.options;
    this.selectedIndex = options.selectedIndex;
    this.selectedContent = options.selectedContent;
    this.onSelect = options.onSelect;
    this.defaultFocus = options.defaultFocus;
  }
}

export enum SubHeaderV2OperationType {
  TEXT_ARROW = 0,
  BUTTON = 1,
  ICON_GROUP = 2,
  LOADING = 3,
}

export type SubHeaderV2OperationItemAction = () => void;

declare type SubHeaderV2OperationItemType = ResourceStr | SymbolGlyphModifier;

export interface SubHeaderV2OperationItemOptions {
  content: SubHeaderV2OperationItemType;
  action?: SubHeaderV2OperationItemAction;
  accessibilityText?: ResourceStr;
  accessibilityDescription?: ResourceStr;
  accessibilityLevel?: string;
  defaultFocus?: boolean;
}

@ObservedV2
export class SubHeaderV2OperationItem {
  @Trace
  public content: SubHeaderV2OperationItemType;
  @Trace
  public action?: SubHeaderV2OperationItemAction;
  @Trace
  public accessibilityText?: ResourceStr;
  @Trace
  public accessibilityDescription?: ResourceStr;
  @Trace
  public accessibilityLevel?: string;
  @Trace
  public defaultFocus?: boolean;

  constructor(options: SubHeaderV2OperationItemOptions) {
    this.content = options.content;
    this.action = options.action;
    this.accessibilityText = options.accessibilityText;
    this.accessibilityDescription = options.accessibilityDescription;
    this.accessibilityLevel = options.accessibilityLevel;
    this.defaultFocus = options.defaultFocus;
  }
}

interface ContentIconOption {
  content?: ResourceStr;
  subContent?: ResourceStr;
  iconOptions?: SubHeaderV2IconType;
  action?: () => void;
  accessibilityLevel?: string;
  accessibilityText?: ResourceStr;
  accessibilityDescription?: ResourceStr;
  defaultFocus?: boolean;
}

@ObservedV2
class FontStyle {
  @Trace
  public maxLines: int = 0;
  @Trace
  public fontWeight: int = 0;
  @Trace
  public fontColor?: ResourceColor;
  @Trace
  public alignment?: Alignment;
}

@ObservedV2
class SubHeaderTheme {
  @Trace
  public fontPrimaryColor: ResourceColor = $r('sys.color.font_primary');
  @Trace
  public fontSecondaryColor: ResourceColor = $r('sys.color.font_secondary');
  @Trace
  public fontButtonColor: ResourceColor = $r('sys.color.font_emphasize');
  @Trace
  public iconArrowColor: ResourceColor = $r('sys.color.icon_tertiary');
  @Trace
  public textArrowHoverBgColor: ResourceColor = $r('sys.color.interactive_hover');
  @Trace
  public borderFocusColor: ResourceColor = $r('sys.color.interactive_focus');
  @Trace
  public leftIconColor: ResourceColor = $r('sys.color.icon_secondary');
  @Trace
  public rightIconColor: ResourceColor = $r('sys.color.icon_primary');
}

function secondaryTitleStyles(this: TextAttribute, fontStyle: FontStyle): this {
  this.fontSize(`${getResourceValue('sys.float.Subtitle_S')}fp`)
  this.fontColor(fontStyle?.fontColor ?? $r('sys.color.font_secondary'))
  this.fontWeight(fontStyle?.fontWeight)
  this.maxLines(fontStyle?.maxLines)
  this.textOverflow({ overflow: TextOverflow.Ellipsis })
  this.align(fontStyle?.alignment)
  return this
}

function primaryTitleStyles(this: TextAttribute, fontStyle: FontStyle): this {
  this.fontSize(`${getResourceValue('sys.float.subheader_title_font_size')}fp`)
  this.fontColor(fontStyle?.fontColor ?? $r('sys.color.font_primary'))
  this.fontWeight(fontStyle?.fontWeight)
  this.maxLines(fontStyle?.maxLines)
  this.textOverflow({ overflow: TextOverflow.Ellipsis })
  this.align(fontStyle?.alignment)
  return this
}

function pressedStyle(instance: CommonMethod) {
  instance.backgroundColor($r('sys.color.interactive_pressed'))
}

function disabledStyle(instance: CommonMethod) {
  instance.opacity(getResourceValue('sys.float.interactive_disable'))
}

class SubHeaderModifier implements AttributeModifier<RowAttribute> {
  public isAgeing: boolean = false

  applyNormalAttribute(instance: RowAttribute): void {
    if (this.isAgeing) {
      instance.width('100%')
    } else {
    }
  }
}

@Builder
export type SubHeaderV2TitleBuilder = () => void;

@CustomLayout
@ComponentV2
export struct SubHeaderV2 {
  @Param
  icon?: SubHeaderV2IconType = undefined;
  @Param
  title?: SubHeaderV2Title | undefined = undefined;
  @Param
  select?: SubHeaderV2Select | undefined = undefined;
  @Param
  operationType?: SubHeaderV2OperationType = SubHeaderV2OperationType.BUTTON;
  @Param
  operationItems: Array<SubHeaderV2OperationItem> = [] as Array<SubHeaderV2OperationItem>;
  @BuilderParam
  titleBuilder?: SubHeaderV2TitleBuilder;
  @Local
  fontSize: number = 1;
  @Local
  ageing: boolean = true;
  // 内部变量
  @Local
  textArrowBgColor: ResourceColor = $r('sys.color.ohos_id_color_sub_background_transparent');
  @Local
  buttonBgColor: ResourceColor = $r('sys.color.ohos_id_color_sub_background_transparent');
  @Local
  selectedIndex: int | Resource | undefined = -1;
  @Local
  selectedContent: ResourceStr | undefined = '';
  @Local
  symbolWidth: number = LEFT_ICON_SIZE_NUMBER + LEFT_TEXT_NUMBER;
  @Local
  subHeaderModifier: SubHeaderModifier = new SubHeaderModifier();
  isFollowingSystemFontScale: boolean = false;
  appMaxFontScale: number = 3.2;
  @Provider('subHeaderV2Theme') subHeaderV2Theme: SubHeaderTheme = new SubHeaderTheme();
  subHeaderMargin: LocalizedMargin = {
    start: LengthMetrics.vp(getResourceValue('sys.float.margin_left')),
    end: LengthMetrics.vp(getResourceValue('sys.float.margin_right')),
  } as LocalizedMargin;

  onWillApplyTheme(theme: Theme) {
    this.subHeaderV2Theme.fontPrimaryColor = theme.colors.fontPrimary;
    this.subHeaderV2Theme.fontSecondaryColor = theme.colors.fontSecondary;
    this.subHeaderV2Theme.fontButtonColor = theme.colors.fontEmphasize;
    this.subHeaderV2Theme.iconArrowColor = theme.colors.iconTertiary;
    this.subHeaderV2Theme.textArrowHoverBgColor = theme.colors.interactiveHover;
    this.subHeaderV2Theme.borderFocusColor = theme.colors.interactiveFocus;
    this.subHeaderV2Theme.leftIconColor = theme.colors.iconSecondary;
    this.subHeaderV2Theme.rightIconColor = theme.colors.iconPrimary;
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
      this.selectedIndex = this.select?.selectedIndex;
      this.selectedContent = this.select?.selectedContent;
    }
  }

  updateFontScale(): number {
    try {
      let uiContext: UIContext = this.getUIContext();
      let systemFontScale: number = (uiContext.getHostContext() as common.UIAbilityContext)?.config?.fontSizeScale ?? 1;
      if (!this.isFollowingSystemFontScale) {
        return 1;
      }
      return Math.min(systemFontScale, this.appMaxFontScale);
    } catch (exception) {
      let code: number = (exception as ClassCastError).code;
      let message: string = (exception as ClassCastError).message;
      hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${code}, message: ${message}`);
      return 1;
    }
  }

  @Builder
  IconSecondaryTitleStyle($$: ContentIconOption): void {
    Flex({ direction: FlexDirection.Row, alignItems: ItemAlign.Center }) {
      if (Util.isSymbolResource($$.iconOptions)) {
        SymbolGlyphChild({
          icon: $$.iconOptions,
          fontColor: this.subHeaderV2Theme.leftIconColor,
          changeSymbolWidth: (result: SizeResult) => {
            this.symbolWidth = result.width;
          }
        })
      } else {
        Image($$.iconOptions as ResourceStr)
          .fillColor(this.subHeaderV2Theme.leftIconColor)
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
          fontColor: this.subHeaderV2Theme.fontSecondaryColor,
        })
        .attributeModifier(this.title?.secondaryTitleModifier)
        .flexShrink(1)
    }
    .applyStyles(this.commonListPadding)
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

  private isSuitableAging(): boolean | null {
    return (this.fontSize >= MIN_FONT_SIZE) && ((this.operationType === SubHeaderV2OperationType.TEXT_ARROW) ||
      this.operationType === SubHeaderV2OperationType.BUTTON) && this.operationItems !== undefined &&
      (this.operationItems.length > 0) && this.operationItems[0].content !== '';
  }

  private isLeftAreaAccessibilityGroup(): boolean {
    if (this.titleBuilder || this.title?.secondaryTitle) {
      return true;
    }
    if (this.select) {
      return false;
    }
    return true;
  }

  @Monitor(['select'])
  infoChange(monitor: IMonitor) {
    monitor.dirty.forEach((path: string) => {
      if ('select' === path) {
        this.selectedIndex = (monitor.value(path) as IMonitorValue<SubHeaderV2Select>).now?.selectedIndex;
        this.selectedContent = (monitor.value(path) as IMonitorValue<SubHeaderV2Select>).now ?.selectedContent;
      }
    })
  }

  @Builder
  SelectStyle(selectParam: BuildSelectOptions): void {
    Select(selectParam.params.options)
      .selected(this.selectedIndex)
      .value(this.selectedContent)
      .defaultFocus(this.select?.defaultFocus)
      .onSelect((index: int, value?: string) => {
        this.selectedIndex = index;
        if (value) {
          this.selectedContent = value;
        }
        if (selectParam.params.onSelect) {
          (selectParam?.params.onSelect as (index: int, value?: string) => void)(index, value);
        }
      })
      .font({
        size: `${getResourceValue('sys.float.Body_L')}fp`,
        weight: FontWeight.Medium,
      })
  }

  @Builder
  SubTitleStyle($$: ContentIconOption): void {
    Column() {
      Text($$.content)
        .primaryTitleStyles({
          fontWeight: getResourceValue('sys.float.subheader_title_font_weight') as int,
          maxLines: DOUBLE_LINE_NUM,
          alignment: Alignment.Start,
          fontColor: this.subHeaderV2Theme.fontPrimaryColor,
        })
        .attributeModifier(this.title?.primaryTitleModifier)
      Text($$.subContent)
        .secondaryTitleStyles({
          maxLines: DOUBLE_LINE_NUM,
          fontWeight: FontWeight.Regular,
          alignment: Alignment.Start,
          fontColor: this.subHeaderV2Theme.fontSecondaryColor,
        })
        .margin({
          top: getResourceValue('sys.float.padding_level1'),
        } as Margin)
        .attributeModifier(this.title?.secondaryTitleModifier)
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
        fontColor: this.subHeaderV2Theme.fontSecondaryColor,
      })
      .attributeModifier(this.title?.secondaryTitleModifier)
      .applyStyles(this.commonListPadding)
  }

  @Builder
  PrimaryTitleStyle($$: ContentIconOption): void {
    Text($$.content)
      .primaryTitleStyles({
        fontWeight: getResourceValue('sys.float.subheader_title_font_weight') as int,
        maxLines: DOUBLE_LINE_NUM,
        alignment: Alignment.Start,
        fontColor: this.subHeaderV2Theme.fontPrimaryColor,
      })
      .attributeModifier(this.title?.primaryTitleModifier)
      .applyStyles(this.commonContentPadding)
  }

  @Builder
  leftArea(): void {
    if (this.titleBuilder) {
      (this.titleBuilder as () => void)();
    } else if (this.title?.secondaryTitle && this.icon) {
      this.IconSecondaryTitleStyle({
        content: this.title?.secondaryTitle,
        iconOptions: this.icon,
      });
    } else if (this.title?.secondaryTitle && this.title?.primaryTitle) {
      this.SubTitleStyle({ content: this.title?.primaryTitle, subContent: this.title?.secondaryTitle });
    } else if (this.title?.secondaryTitle) {
      this.SecondTitleStyle({ content: this.title?.secondaryTitle });
    } else if (this.select) {
      this.SelectStyle({ params: this.select as SubHeaderV2Select });
    } else if (this.title?.primaryTitle) {
      this.PrimaryTitleStyle({ content: this.title?.primaryTitle });
    } else {
      // 其他不支持场景
      this.dummyFunction();
    }
  }

  private isRightAreaExists(): boolean {
    if (this.operationItems && this.operationItems.length > 0) {
      return true;
    }
    if (this.operationType === SubHeaderV2OperationType.LOADING) {
      return true;
    }
    return false;
  }

  rightAreaClickEvent(instance: CommonMethod) {
    instance.onKeyEvent((event: KeyEvent) => {
      if (!event) {
        return false;
      }
      if ((event.keyCode === KeyCode.KEYCODE_SPACE || event.keyCode === KeyCode.KEYCODE_ENTER) &&
        event.type === KeyType.Down) {
        if ((this.operationType === SubHeaderV2OperationType.TEXT_ARROW ||
          this.operationType === SubHeaderV2OperationType.BUTTON) &&
          this.operationItems !== undefined && this.operationItems.length > 0 && this.operationItems[0].action) {
          (this.operationItems[0].action as () => void)();
        }
        event.stopPropagation();
      }
    })
    instance.onClick((event: ClickEvent) => {
      if ((this.operationType === SubHeaderV2OperationType.TEXT_ARROW ||
        this.operationType === SubHeaderV2OperationType.BUTTON) &&
        this.operationItems !== undefined && this.operationItems.length > 0 && this.operationItems [0].action) {
        (this.operationItems[0].action as () => void)();
      }
    })
    instance.onTouch((event: TouchEvent) => {
      if (event.type === TouchType.Down) {
        if (this.operationType === SubHeaderV2OperationType.TEXT_ARROW) {
          this.textArrowBgColor = $r('sys.color.interactive_pressed');
        }
        if (this.operationType === SubHeaderV2OperationType.BUTTON) {
          this.buttonBgColor = $r('sys.color.interactive_pressed');
        }
      }
      if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
        if (this.operationType === SubHeaderV2OperationType.TEXT_ARROW) {
          this.textArrowBgColor = $r('sys.color.ohos_id_color_sub_background_transparent');
        }
        if (this.operationType === SubHeaderV2OperationType.BUTTON) {
          this.buttonBgColor = $r('sys.color.ohos_id_color_sub_background_transparent');
        }
      }
    })
  }

  private getRightAreaMaxWidth(): Length {
    if (this.operationType === SubHeaderV2OperationType.ICON_GROUP &&
      (this.operationItems && this.operationItems.length > 0)) {
      return '100%';
    }
    return MAX_RIGHT_WIDTH;
  }

  private getRightAreaMinWidth(): Length {
    if (this.operationItems && this.operationItems.length > 0) {
      return MIN_HOT_AREA_LENGTH;
    }
    return 0;
  }

  rightAreaParentStyles(instance: CommonMethod) {
    instance.constraintSize({
      maxWidth: this.getRightAreaMaxWidth(),
      minWidth: this.getRightAreaMinWidth(),
      minHeight: MIN_HOT_AREA_LENGTH,
    })
    instance.flexShrink(0)
    instance.accessibilityLevel(this.operationType === SubHeaderV2OperationType.BUTTON ||
      this.operationType === SubHeaderV2OperationType.TEXT_ARROW ?
      this.getRightAreaAccessibilityLevel() : 'no')
  }

  private getAccessibilityDescription(): string | undefined {
    if (!this.operationItems || this.operationItems.length <= 0) {
      return '';
    }
    if (Util.isResourceType(this.operationItems[0].accessibilityDescription)) {
      return (this.getUIContext().getHostContext() as common.Context).resourceManager.getStringSync(
        (this.operationItems[0].accessibilityDescription as Resource).id);
    } else if (this.operationItems[0].accessibilityDescription &&
      this.operationItems[0].accessibilityDescription !== '') {
      return this.operationItems[0].accessibilityDescription as string;
    }
    return '';
  }

  private leftIconMargin(): LengthMetrics {
    if (this.titleBuilder) {
      return LengthMetrics.vp(0);
    }
    if (this.icon && Util.isSymbolResource(this.icon)) {
      return this.ageing ?
        LengthMetrics.vp(this.symbolWidth) :
        LengthMetrics.vp(0);
    } else {
      return (this.ageing && this.icon) ? LengthMetrics.vp(LEFT_ICON_SIZE_NUMBER +
        LEFT_TEXT_NUMBER) : LengthMetrics.vp(0);
    }
  }

  onPlaceChildren(selfLayoutInfo: GeometryInfo, children: Layoutable[],
    constraint: ConstraintSizeOptions) {
    let currentX: number = 0;
    let currentY: number = 0;
    for (let index = 0; index < children.length; index++) {
      let child = children[index];
      child.layout({ x: currentX, y: currentY });
    }
  }

  onMeasureSize(selfLayoutInfo: GeometryInfo, children: Measurable[], constraint: ConstraintSizeOptions): SizeResult {
    if (children.length <= 0) {
      hilog.error(0x3900, 'Ace', 'SubHeader onMeasureSize children is null');
      return { width: 0, height: 0 };
    }
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
      constraint.minHeight = Math.min(Number(this.getMinHeight() as number), Number(constraint.maxHeight as number));
      result.height = child.measure(constraint).height;
      result.width = Number(constraint.maxWidth as number);
    })
    return result;
  }

  getText(content: SubHeaderV2OperationItemType): ResourceStr {
    if (typeof content === 'SymbolGlyphModifier' || typeof content === 'undefined') {
      return '';
    }
    return content as ResourceStr;
  }

  @Builder
  ButtonStyle(): void {
    if (this.operationItems) {
      Button({ type: ButtonType.Normal, stateEffect: false } as ButtonOptions) {
        Text(this.getText(this.operationItems[0].content))
          .secondaryTitleStyles({
            fontWeight: FontWeight.Medium,
            maxLines: DOUBLE_LINE_NUM,
            fontColor: this.subHeaderV2Theme.fontButtonColor,
          })
          .defaultFocus(this.operationItems[0].defaultFocus)
          .focusable(true)
      }
      .focusable(true)
      .focusBox({
        margin: new LengthMetrics(INDEX_ZERO, LengthUnit.VP),
        strokeColor: ColorMetrics.resourceColor(this.subHeaderV2Theme.borderFocusColor),
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
          this.buttonBgColor = this.subHeaderV2Theme.textArrowHoverBgColor;
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

  private getTextArrowPaddingLeft(): LengthMetrics {
    if (this.operationItems && (this.operationItems.length > 0) && this.operationItems[0].content) {
      return LengthMetrics.vp(getResourceValue('sys.float.padding_level1'));
    }
    return LengthMetrics.vp(getResourceValue('sys.float.padding_level0'));
  }

  private getTextArrowMarginRight(): LengthMetrics {
    if (this.operationItems && (this.operationItems.length > 0) && this.operationItems[0].content) {
      return LengthMetrics.vp(PADDING_LEVEL_2 + ARROW_ICON_WIDTH);
    }
    return LengthMetrics.vp(ARROW_ICON_WIDTH);
  }

  @Builder
  TextStyle(): void {
    Row() {
      if (this.operationItems && this.operationItems[0]) {
        Text(this.getText(this.operationItems[0].content))
          .secondaryTitleStyles({
            maxLines: DOUBLE_LINE_NUM,
            fontWeight: FontWeight.Regular,
            alignment: Alignment.End,
            fontColor: this.subHeaderV2Theme.fontSecondaryColor,
          })
          .focusable(true)
          .defaultFocus(this.operationItems[0].defaultFocus)
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
        .fontColor([this.subHeaderV2Theme.iconArrowColor])
        .draggable(false)
        .width(ARROW_ICON_WIDTH)
        .height(OPERATE_ITEM_LENGTH)
    }
    .justifyContent(FlexAlign.End)
  }

  @Builder
  TextArrowStyle(): void {
    if (this.operationItems && this.operationItems[0] && this.operationItems[0].content &&
      this.operationItems[0].content.toString().length > 0) {
      Stack() {
        Button({ type: ButtonType.Normal, stateEffect: false } as ButtonOptions) {
          TextArrowLayout() {
            ForEach([INDEX_ZERO, INDEX_ONE], (item: Int, index: int) => {
              if (index === INDEX_ZERO) {
                this.TextStyle();
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
          strokeColor: ColorMetrics.resourceColor(this.subHeaderV2Theme.borderFocusColor),
          strokeWidth: LengthMetrics.vp(getResourceValue('sys.float.outline_extra_larger')),
        })
        .borderRadius(getResourceValue('sys.float.corner_radius_level4'))
        .stateStyles({
          pressed: pressedStyle,
          disabled: disabledStyle,
        })
        .onHover((isHover: boolean): void => {
          if (isHover) {
            this.textArrowBgColor = this.subHeaderV2Theme.textArrowHoverBgColor;
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
            .fontColor([this.subHeaderV2Theme.iconArrowColor])
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
          strokeColor: ColorMetrics.resourceColor(this.subHeaderV2Theme.borderFocusColor),
          strokeWidth: LengthMetrics.vp(getResourceValue('sys.float.outline_extra_larger')),
        })
        .borderRadius(getResourceValue('sys.float.corner_radius_level4'))
        .stateStyles({
          pressed: pressedStyle,
          disabled: disabledStyle,
        })
        .onHover((isHover: boolean): void => {
          if (isHover) {
            this.textArrowBgColor = this.subHeaderV2Theme.textArrowHoverBgColor;
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
  IconGroupStyle(): void {
    Row() {
      ForEach(this.operationItems, (item: SubHeaderV2OperationItem, index: int) => {
        if (index <= INDEX_TWO) {
          SingleIconStyle({
            item: {
              iconOptions: this.operationItems?.[index.toInt()].content,
              action: this.operationItems?.[index.toInt()].action,
              defaultFocus: this.operationItems?.[index.toInt()].defaultFocus,
              accessibilityLevel: this.operationItems?.[index.toInt()].accessibilityLevel,
              accessibilityText: this.operationItems?.[index.toInt()].accessibilityText,
              accessibilityDescription: this.operationItems?.[index.toInt()].accessibilityDescription
            },
            isSingleIcon: this.operationItems?.length === SINGLE_ICON_NUMBER,
          })
        } else {
          // 最大支持3个ICON,此场景不支持
        }
      }, (item: SubHeaderV2OperationItem, index: int) => {
        return `${index}`;
      })
    }
    .justifyContent(FlexAlign.End)
    .focusable(true)
  }

  @Builder
  rightArea(): void {
    if (this.operationType === SubHeaderV2OperationType.BUTTON && this.operationItems &&
      (this.operationItems.length > 0)) {
      this.ButtonStyle();
    }
    if (this.operationType === SubHeaderV2OperationType.TEXT_ARROW && this.operationItems &&
      (this.operationItems.length > 0)) {
      this.TextArrowStyle();
    }
    if (this.operationType === SubHeaderV2OperationType.ICON_GROUP && this.operationItems &&
      (this.operationItems.length > 0)) {
      this.IconGroupStyle();
    }
    if (this.operationType === SubHeaderV2OperationType.LOADING) {
      this.LoadingProcessStyle();
    }
    if (this.operationType === undefined && this.operationItems && (this.operationItems.length > 0)) {
      this.ButtonStyle();
    }
  }

  @Builder
  rightAreaParent(): void {
    if (this.operationType === SubHeaderV2OperationType.BUTTON ||
      this.operationType === SubHeaderV2OperationType.TEXT_ARROW) {
      Button({ type: ButtonType.Normal, stateEffect: false } as ButtonOptions) {
        this.rightArea();
      }
      .focusable(this.operationItems ? true : false)
      .margin(INDEX_ZERO)
      .padding(INDEX_ZERO)
      .align(Alignment.BottomEnd)
      .applyStyles(this.rightAreaClickEvent)
      .applyStyles(this.rightAreaParentStyles)
      .constraintSize({
        maxWidth: this.getRightAreaMaxWidth(),
        minWidth: this.getRightAreaMinWidth(),
        minHeight: MIN_HOT_AREA_LENGTH,
      })
      .flexShrink(0)
      .hoverEffect(HoverEffect.None)
      .backgroundColor($r('sys.color.ohos_id_color_sub_background_transparent'))
      .accessibilityGroup(true)
      .accessibilityText(this.getRightAreaAccessibilityText())
      .accessibilityDescription(this.getAccessibilityDescription())
    } else {
      Row() {
        this.rightArea();
      }
      .focusable(this.operationItems && this.operationType !== SubHeaderV2OperationType.LOADING ? true : false)
      .justifyContent(FlexAlign.End)
      .alignItems(VerticalAlign.Bottom)
      .applyStyles(this.rightAreaClickEvent)
      .applyStyles(this.rightAreaParentStyles)
    }
  }

  @Builder
  rightAreaParentAging(): void {
    if (this.operationType === SubHeaderV2OperationType.BUTTON ||
      this.operationType === SubHeaderV2OperationType.TEXT_ARROW) {
      Button({ type: ButtonType.Normal, stateEffect: false } as ButtonOptions) {
        this.rightArea();
      }
      .focusable(this.operationItems ? true : false)
      .align(Alignment.Start)
      .applyStyles(this.rightAreaClickEvent)
      .applyStyles(this.rightAreaParentAgingStyles)
      .margin({
        bottom: getResourceValue('sys.float.padding_level4'),
      } as Margin)
      .padding({
        // 'sys.float.margin_left' id,value: 16vp
        start: LengthMetrics.vp(getResourceValue('sys.float.margin_left') - PADDING_LEFT),
        // 'sys.float.margin_right' id,value: 16vp
        end: LengthMetrics.vp(getResourceValue('sys.float.margin_right')),
      } as LocalizedPadding)
      .backgroundColor($r('sys.color.ohos_id_color_sub_background_transparent'))
      .hoverEffect(HoverEffect.None)
      .accessibilityGroup(true)
      .accessibilityText(this.getRightAreaAccessibilityText())
      .accessibilityDescription(this.getAccessibilityDescription())
    } else {
      Row() {
        this.rightArea();
      }
      .focusable(this.operationItems && this.operationType !== SubHeaderV2OperationType.LOADING ? true : false)
      .justifyContent(FlexAlign.Start)
      .applyStyles(this.rightAreaClickEvent)
      .applyStyles(this.rightAreaParentAgingStyles)
      .margin({
        bottom: getResourceValue('sys.float.padding_level4'),
      } as Margin)
      .padding({
        // 'sys.float.margin_left' id,value: 16vp
        start: LengthMetrics.vp(getResourceValue('sys.float.margin_left') - PADDING_LEFT),
        // 'sys.float.margin_right' id,value: 16vp
        end: LengthMetrics.vp(getResourceValue('sys.float.margin_right')),
      } as LocalizedPadding)
    }
  }

  rightAreaParentAgingStyles(instance: CommonMethod) {
    instance.margin({
      bottom: getResourceValue('sys.float.padding_level4'),
    } as Margin)
    instance.padding({
      // 'sys.float.margin_left' id,value: 16vp
      start: LengthMetrics.vp(getResourceValue('sys.float.margin_left') - PADDING_LEFT),
      // 'sys.float.margin_right' id,value: 16vp
      end: LengthMetrics.vp(getResourceValue('sys.float.margin_right')),
    } as LocalizedPadding)
    instance.accessibilityLevel(this.operationType === SubHeaderV2OperationType.BUTTON ||
      this.operationType === SubHeaderV2OperationType.TEXT_ARROW ? this.getRightAreaAccessibilityLevel() : 'no')
  }

  private getRightAreaAccessibilityText(): string | undefined {
    if (!this.operationItems || (this.operationItems.length <= 0)) {
      return '';
    }
    if (Util.isResourceType(this.operationItems[0].accessibilityText)) {
      return (this.getUIContext().getHostContext() as common.Context).resourceManager
        .getStringSync((this.operationItems[0].accessibilityText as Resource).id);
    } else if (this.operationItems[0].accessibilityText) {
      return this.operationItems[0].accessibilityText as string;
    } else {
      if (this.operationType === SubHeaderV2OperationType.TEXT_ARROW &&
        this.operationItems[0].content.toString().length <= 0) {
        // 播报：更多、more等, 使用的字段是：sys.string.ohos_toolbar_more
        return Util.getStringByResource(125833704, '');
      }
    }
    return '';
  }

  private getMinHeight(): Length {
    if (this.title?.secondaryTitle && this.icon) {
      return getResourceValue('sys.float.subheader_single_subtitle_height');
    } else if (this.title?.secondaryTitle && this.title?.primaryTitle) {
      return getResourceValue('sys.float.subheader_double_height');
    } else if (this.title?.primaryTitle || this.select) {
      return getResourceValue('sys.float.subheader_single_title_height');
    }
    return getResourceValue('sys.float.subheader_single_subtitle_height');
  }

  private getAreaPadding(): LocalizedPadding {
    let padding: LocalizedPadding = {};
    if (!this.titleBuilder && ((this.title?.secondaryTitle && this.icon) ||
      (!this.title?.primaryTitle && this.title?.secondaryTitle))) {
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
          start: LengthMetrics.vp(getResourceValue('sys.float.margin_left')),
          end: LengthMetrics.vp(getResourceValue('sys.float.margin_right')),
        } as LocalizedPadding)
        .width('100%')
        .accessibilityGroup(this.isLeftAreaAccessibilityGroup())
        .accessibilityDescription(this.select ? '' : Util.getStringByResource(125834353, ''))

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
        .accessibilityDescription(this.select ? '' : Util.getStringByResource(125834353, ''))

        if (this.isRightAreaExists()) {
          this.rightAreaParent();
        }
      }
      .constraintSize({ minHeight: this.getMinHeight() })
      .margin(this.subHeaderMargin)
      .padding(this.getAreaPadding())
    }
  }

  private getRightAreaAccessibilityLevel(): string {
    if (this.operationItems[0].accessibilityLevel && this.operationItems[0].accessibilityLevel !== '') {
      return this.operationItems[0].accessibilityLevel as string;
    }
    return 'yes';
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

@CustomLayout
@ComponentV2
struct SymbolGlyphChild {
  @Param @Require icon: SubHeaderV2IconType;
  @Param @Require fontColor: ResourceColor;
  @Event changeSymbolWidth: (result: SizeResult) => void = () => {
  };
  result: SizeResult = {
    width: 0,
    height: 0
  } as SizeResult;

  onPlaceChildren(selfLayoutInfo: GeometryInfo, children: Layoutable[],
    constraint: ConstraintSizeOptions) {
    let currentX: number = 0;
    let currentY: number = 0;
    for (let index = 0; index < children.length; index++) {
      let child = children[index];
      child.layout({ x: currentX, y: currentY });
    }
  }

  onMeasureSize(selfLayoutInfo: GeometryInfo, children: Array<Measurable>,
    constraint: ConstraintSizeOptions): SizeResult {
    children.forEach((child) => {
      this.result = child.measure(constraint);
    })
    console.log(`zzzz Child onMeasureSize ${JSON.stringify(this.result)}`)
    this.changeSymbolWidth(this.result)
    return this.result;
  }

  getSymbolGlyphResource(): Resource | undefined {
    if (this.icon && (this.icon instanceof Resource)) {
      return this.icon as Resource;
    }
    return undefined;
  }

  getSymbolGlyphModifier(): SymbolGlyphModifier | undefined {
    if (this.icon && (this.icon instanceof SymbolGlyphModifier)) {
      return this.icon as SymbolGlyphModifier;
    }
    return undefined;
  }

  build() {
    Column() {
      SymbolGlyph(this.getSymbolGlyphResource())
        .fontSize(LEFT_ICON_SIZE)
        .fontColor([this.fontColor])
        .attributeModifier(this.getSymbolGlyphModifier())
        .margin({ end: LengthMetrics.vp(getResourceValue('sys.float.padding_level4')) } as LocalizedMargin)
        .flexShrink(0)
    }
  }
}

@ComponentV2
struct SingleIconStyle {
  @Local bgColor: Resource = $r('sys.color.ohos_id_color_sub_background_transparent');
  @Local isFocus: boolean = false;
  @Param item: ContentIconOption | undefined = undefined;
  @Consumer('subHeaderV2Theme') subHeaderTheme: SubHeaderTheme = new SubHeaderTheme();
  @Param isSingleIcon: boolean = true;

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
    if (this.item?.iconOptions) {
      Button({ type: ButtonType.Normal, stateEffect: false } as ButtonOptions) {
        this.IconZone();
      }
      .focusable(true)
      .defaultFocus(this.item?.defaultFocus)
      .width(SINGLE_ICON_ZONE_SIZE)
      .height(SINGLE_ICON_ZONE_SIZE)
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

  private getSymbolGlyphResource(): Resource | undefined {
    if (this.item?.iconOptions && (this.item?.iconOptions instanceof Resource)) {
      return this.item?.iconOptions as Resource;
    }
    return undefined;
  }

  private getSymbolGlyphModifier(): SymbolGlyphModifier | undefined {
    if (this.item?.iconOptions && (this.item?.iconOptions instanceof SymbolGlyphModifier)) {
      return this.item?.iconOptions as SymbolGlyphModifier;
    }
    return undefined;
  }

  @Builder
  IconZone(): void {
    if (this.item?.iconOptions) {
      if (Util.isSymbolResource(this.item?.iconOptions)) {
        SymbolGlyph(this.getSymbolGlyphResource())
          .fontSize(RIGHT_SINGLE_ICON_SIZE)
          .fontColor([this.subHeaderTheme.rightIconColor])
          .attributeModifier(this.getSymbolGlyphModifier())
          .focusable(true)
      } else {
        Image(this.item?.iconOptions as ResourceStr)
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
   * @Param resourceStr  资源
   * @returns true：symbol资源；false:非symbol资源
   */
  public static isSymbolResource(resourceStr: SubHeaderV2IconType | undefined): boolean {
    if (!Util.isResourceType(resourceStr)) {
      return false;
    }
    if (resourceStr instanceof SymbolGlyphModifier) {
      return resourceStr instanceof SymbolGlyphModifier;
    }
    let resource = resourceStr as Resource;
    return resource.type === RESOURCE_TYPE_SYMBOL;
  }

  /**
   * 是否Resource类型
   * @Param resource 资源
   * @returns true：Resource类型；false:非Resource类型
   */
  public static isResourceType(resource: SubHeaderV2IconType | undefined): boolean {
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
   * @Param resourceName resource id
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
      let code: number = (error as ClassCastError).code;
      let message: string = (error as ClassCastError).message;
      hilog.error(0x3900, 'Ace', `SubHeader getNumberByResource error, code: ${code}, message: ${message}`);
      return 0;
    }
  }

  /**
   * get resource string
   *
   * @Param resourceId resource id
   * @Param defaultString default value
   * @returns resource string
   */
  public static getStringByResource(resourceId: long, defaultString: string): string {
    try {
      let resourceString: string = resourceManager.getSysResourceManager().getStringSync(resourceId);
      if (resourceString === '') {
        return defaultString;
      } else {
        return resourceString;
      }
    } catch (error) {
      let code: number = (error as ClassCastError).code;
      let message: string = (error as ClassCastError).message;
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

  onPlaceChildren(selfLayoutInfo: GeometryInfo, children: Layoutable[],
    constraint: ConstraintSizeOptions) {
    let currentX: number = 0;
    let currentY: number = 0;
    for (let index = 0; index < children.length; index++) {
      let child = children[index];
      child.layout({ x: currentX, y: currentY });
    }
  }

  onMeasureSize(selfLayoutInfo: GeometryInfo, children: Measurable[],
    constraint: ConstraintSizeOptions): SizeResult {
    if (children.length <= 0) {
      hilog.error(0x3900, 'Ace', 'TextArrowLayout onMeasureSize children is null');
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
    let textMeasureResult: MeasureResult = textChild.measure(textConstraint);
    textArrowWidth = Math.max(textArrowWidth, textMeasureResult.width);
    textArrowHeight = Math.max(textArrowHeight, textMeasureResult.height);

    let arrowChild: Measurable = children[INDEX_ONE];
    let arrowConstraint: ConstraintSizeOptions = {
      minWidth: textArrowWidth,
      maxWidth: textArrowWidth,
      minHeight: textArrowHeight,
      maxHeight: textArrowHeight,
    };
    arrowChild.measure(arrowConstraint);
    return { width: textArrowWidth, height: textArrowHeight };
  }

  build() {
    this.textArrowBuilder();
  }
}