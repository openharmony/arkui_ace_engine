/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

import { TextModifier } from '@ohos.arkui.modifier';
import { Theme } from '@ohos.arkui.theme';
import { ColorMetrics, LengthMetrics, LengthUnit } from '@ohos.arkui.node';
import resourceManager from '@ohos.resourceManager';
import { BusinessError } from '@ohos.base';
import hilog from '@ohos.hilog';
import common from '@ohos.app.ability.common';
import { HashMap } from '@kit.ArkTS';

const INDEX_ZERO: number = 0;
const INDEX_ONE: number = 1;
const INDEX_TWO: number = 2;
// 行数及整体高度
const SINGLE_LINE_NUM: number = 1;
const DOUBLE_LINE_NUM: number = 2;
// 资源数值
const RESOURCE_TYPE_SYMBOL: number = 40000;
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

export declare class OperationOption {
  public value: ResourceStr;
  public action?: () => void;
  public accessibilityLevel?: string;
  public accessibilityText?: ResourceStr;
  public accessibilityDescription?: ResourceStr;
}

export declare class SelectOptions {
  public options: Array<SelectOption>;
  public selected?: number;
  public value?: string;
  public onSelect?: (index: number, value?: string) => void;
}

export declare class SymbolOptions {
  public fontSize?: Length;
  public fontColor?: Array<ResourceColor>;
  public fontWeight?: number | FontWeight | string;
  public effectStrategy?: SymbolEffectStrategy;
  public renderingStrategy?: SymbolRenderingStrategy;
}

class IconOptions {
  public icon?: Resource;
  public symbolicIconOption?: SymbolOptions | null;
}

class ContentIconOption {
  public content?: ResourceStr;
  public subContent?: ResourceStr;
  public iconOptions?: IconOptions;
  public action?: () => void;
  public accessibilityLevel?: string;
  public accessibilityText?: ResourceStr;
  public accessibilityDescription?: ResourceStr;
}

class FontStyle {
  public maxLines: number = 0;
  public fontWeight: number = 0;
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

@Extend(Text)
function secondaryTitleStyles(fontStyle: FontStyle) {
  .fontSize(`${getResourceValue('sys.float.Subtitle_S')}fp`)
  .fontColor(fontStyle?.fontColor ?? $r('sys.color.font_secondary'))
  .fontWeight(fontStyle?.fontWeight)
  .maxLines(fontStyle?.maxLines)
  .textOverflow({ overflow: TextOverflow.Ellipsis })
  .align(fontStyle?.alignment)
}

@Extend(Text)
function primaryTitleStyles(fontStyle: FontStyle) {
  .fontSize(`${getResourceValue('sys.float.subheader_title_font_size')}fp`)
  .fontColor(fontStyle?.fontColor ?? $r('sys.color.font_primary'))
  .fontWeight(fontStyle?.fontWeight)
  .maxLines(fontStyle?.maxLines)
  .textOverflow({ overflow: TextOverflow.Ellipsis })
  .align(fontStyle?.alignment)
}

@Styles
function pressedStyle() {
  .backgroundColor($r('sys.color.interactive_pressed'))
}

@Styles
function disabledStyle() {
  .opacity(getResourceValue('sys.float.interactive_disable'))
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

interface ResourceInfo {
  resourceId: number,
  defaultValue: number,
  resourceValue?: number,
}

const RESOURCE_CACHE_MAP: HashMap<string, ResourceInfo> = new HashMap();
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

@Component
export struct SubHeader {
  @Prop icon: Resource | null = null;
  iconSymbolOptions?: SymbolOptions | null = null;
  @Prop primaryTitle: string | null = null;
  @State primaryTitleModifier: TextModifier = new TextModifier();
  @Prop secondaryTitle: string | null = null;
  @State secondaryTitleModifier: TextModifier = new TextModifier();
  @State subHeaderModifier: SubHeaderModifier = new SubHeaderModifier();
  select: SelectOptions | null = null;
  @Prop operationType: OperationType = OperationType.BUTTON;
  operationItem: Array<OperationOption> | null = null;
  operationSymbolOptions?: Array<SymbolOptions> | null = null;
  @State fontSize: number = 1;
  @State ageing: boolean = true;
  // 内部变量
  @State textArrowBgColor: ResourceColor = $r('sys.color.ohos_id_color_sub_background_transparent');
  @State buttonBgColor: ResourceColor = $r('sys.color.ohos_id_color_sub_background_transparent');
  @State selectedIndex: number | Resource | undefined = -1;
  @State selectValue: ResourceStr | undefined = '';
  @BuilderParam titleBuilder?: () => void;
  @Prop contentMargin: LocalizedMargin;
  @Prop contentPadding: LocalizedPadding;
  subHeaderMargin: LocalizedMargin = {
    start: LengthMetrics.vp(getResourceValue('sys.float.margin_left')),
    end: LengthMetrics.vp(getResourceValue('sys.float.margin_right')),
  };
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

  @Styles
  private commonContentPadding() {
    .padding({
      end: LengthMetrics.vp(getResourceValue('sys.float.padding_level0')),
      top: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
        : LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
      bottom: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
        : LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
    })
  }

  @Styles
  private commonListPadding() {
    .padding({
      end: LengthMetrics.vp(getResourceValue('sys.float.padding_level6')),
      top: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
        : LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
      bottom: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
        : LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
    })
  }

  @Styles
  private rightAreaClickEvent() {
    .onClick(() => {
      if ((this.operationType === OperationType.TEXT_ARROW || this.operationType === OperationType.BUTTON) &&
      this.operationItem && this.operationItem.length > 0 && this.operationItem[0].action) {
        this.operationItem[0].action();
      }
    })
    .onTouch((event) => {
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
      let systemFontScale = (uiContext.getHostContext() as common.UIAbilityContext)?.config.fontSizeScale ?? 1;
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

  async aboutToAppear(): Promise<void> {
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
      this.selectedIndex = this.select.selected;
      this.selectValue = this.select.value;
    }
  }

  private isSuitableAging(): boolean | null {
    return (this.fontSize >= MIN_FONT_SIZE) && ((this.operationType === OperationType.TEXT_ARROW) ||
      this.operationType === OperationType.BUTTON) && this.operationItem &&
      (this.operationItem?.length > 0) && this.operationItem[0].value !== '';
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
        })
        .padding({
          start: this.contentMargin ? this.contentMargin.start :
          LengthMetrics.vp(getResourceValue('sys.float.margin_left')),
          end: this.contentMargin ? this.contentMargin.end :
          LengthMetrics.vp(getResourceValue('sys.float.margin_right')),
        })
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
        })
        .width('100%')
        .flexShrink(1)
        .accessibilityGroup(this.isLeftAreaAccessibilityGroup())
        .accessibilityDescription(this.select ? '' : Util.getStringByResource(125834353, ''))

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

  private toStringFormat(resource: ResourceStr | undefined): string | undefined {
    if (typeof resource === 'string' || typeof resource === 'undefined') {
      return resource;
    } else {
      let resourceString: string = '';
      try {
        resourceString = getContext()?.resourceManager?.getStringSync(resource);
      } catch (err) {
        let code: number = (err as BusinessError)?.code;
        let message: string = (err as BusinessError)?.message;
        hilog.error(0x3900, 'Ace', `Faild to subHeader toStringFormat, code: ${code}, message: ${message}`)
      }
      return resourceString;
    }
  }

  private getRightAreaAccessibilityLevel(): string {
    if (this.operationItem![0].accessibilityLevel && this.operationItem![0].accessibilityLevel !== '') {
      return this.operationItem![0].accessibilityLevel;
    }
    return 'yes';
  }

  @Styles
  private rightAreaParentAgingStyles() {
    .margin({
      bottom: getResourceValue('sys.float.padding_level4'),
    })
    .padding({
      // 'sys.float.margin_left' id,value: 16vp
      start: LengthMetrics.vp((this.contentMargin ? (this.contentMargin.start ? this.contentMargin.start.value : 0) :
      getResourceValue('sys.float.margin_left')) - PADDING_LEFT),
      // 'sys.float.margin_right' id,value: 16vp
      end: this.contentMargin ? this.contentMargin.end :
      LengthMetrics.vp(getResourceValue('sys.float.margin_right')),
    })
    .accessibilityLevel(this.operationType === OperationType.BUTTON || this.operationType === OperationType.TEXT_ARROW ?
    this.getRightAreaAccessibilityLevel() : 'no')
  }

  private getRightAreaAccessibilityText(): string | undefined {
    if (!this.operationItem || this.operationItem.length <= 0) {
      return '';
    }
    if (this.operationItem[0].accessibilityText && this.operationItem[0].accessibilityText !== '') {
      return this.toStringFormat(this.operationItem[0].accessibilityText);
    } else {
      if (this.operationType === OperationType.TEXT_ARROW && this.operationItem[0].value.toString().length <= 0) {
        // 播报：更多、more等, 使用的字段是：sys.string.ohos_toolbar_more
        return Util.getStringByResource(125833704, '');
      }
    }
    return '';
  }

  private getAccessibilityDescription(): string | undefined {
    if (!this.operationItem || this.operationItem.length <= 0) {
      return '';
    }
    if (this.operationItem[0].accessibilityDescription && this.operationItem[0].accessibilityDescription !== '') {
      return this.toStringFormat(this.operationItem[0].accessibilityDescription)
    }
    return '';
  }

  @Builder
  rightAreaParentAging(): void {
    if (this.operationType === OperationType.BUTTON || this.operationType === OperationType.TEXT_ARROW) {
      Button({ type: ButtonType.Normal, stateEffect: false }) {
        this.rightArea();
      }
      .focusable(this.operationItem ? true : false)
      .align(Alignment.Start)
      .rightAreaClickEvent()
      .rightAreaParentAgingStyles()
      .backgroundColor($r('sys.color.ohos_id_color_sub_background_transparent'))
      .hoverEffect(HoverEffect.None)
      .accessibilityText(this.getRightAreaAccessibilityText())
      .accessibilityDescription(this.getAccessibilityDescription())
    } else {
      Row() {
        this.rightArea();
      }
      .focusable(this.operationItem && this.operationType !== OperationType.LOADING ? true : false)
      .justifyContent(FlexAlign.Start)
      .rightAreaClickEvent()
      .rightAreaParentAgingStyles()
    }
  }

  @Styles
  private rightAreaParentStyles() {
    .constraintSize({
      maxWidth: this.getRightAreaMaxWidth(),
      minWidth: this.getRightAreaMinWidth(),
      minHeight: MIN_HOT_AREA_LENGTH,
    })
    .flexShrink(0)
    .accessibilityLevel(this.operationType === OperationType.BUTTON || this.operationType === OperationType.TEXT_ARROW ?
    this.getRightAreaAccessibilityLevel() : 'no')
  }

  @Builder
  rightAreaParent(): void {
    if (this.operationType === OperationType.BUTTON || this.operationType === OperationType.TEXT_ARROW) {
      Button({ type: ButtonType.Normal, stateEffect: false }) {
        this.rightArea();
      }
      .focusable(this.operationItem ? true : false)
      .margin(INDEX_ZERO)
      .padding(INDEX_ZERO)
      .align(Alignment.BottomEnd)
      .rightAreaClickEvent()
      .rightAreaParentStyles()
      .hoverEffect(HoverEffect.None)
      .backgroundColor($r('sys.color.ohos_id_color_sub_background_transparent'))
      .accessibilityText(this.getRightAreaAccessibilityText())
      .accessibilityDescription(this.getAccessibilityDescription())
    } else {
      Row() {
        this.rightArea();
      }
      .focusable(this.operationItem && this.operationType !== OperationType.LOADING ? true : false)
      .justifyContent(FlexAlign.End)
      .alignItems(VerticalAlign.Bottom)
      .rightAreaClickEvent()
      .rightAreaParentStyles()
    }
  }

  onMeasureSize(selfLayoutInfo: GeometryInfo, children: Measurable[], constraint: ConstraintSizeOptions): SizeResult {
    let result: SizeResult = { width: selfLayoutInfo.width, height: selfLayoutInfo.height };
    let context = this.getUIContext().getHostContext() as common.UIAbilityContext;
    this.fontSize = this.updateFontScale();
    if (this.isSuitableAging()) {
      this.ageing = true;
      this.subHeaderModifier.isAgeing = this.ageing;
    } else {
      this.ageing = false;
      this.subHeaderModifier.isAgeing = this.ageing;
    }
    children.forEach((child) => {
      constraint.minHeight = Math.min(Number(this.getMinHeight()), Number(constraint.maxHeight));
      result.height = child.measure(constraint).height;
      result.width = Number(constraint.maxWidth);
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
      return this.contentPadding;
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
      this.titleBuilder();
    } else if (this.secondaryTitle && this.icon) {
      this.IconSecondaryTitleStyle({
        content: this.secondaryTitle,
        iconOptions: {
          icon: this.icon,
          symbolicIconOption: this.iconSymbolOptions,
        },
      });
    } else if (this.secondaryTitle && this.primaryTitle) {
      this.SubTitleStyle({ content: this.primaryTitle, subContent: this.secondaryTitle });
    } else if (this.secondaryTitle) {
      this.SecondTitleStyle({ content: this.secondaryTitle });
    } else if (this.select) {
      this.SelectStyle(this.select);
    } else if (this.primaryTitle) {
      this.PrimaryTitleStyle({ content: this.primaryTitle });
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
  }

  @Builder
  IconSecondaryTitleStyle($$: ContentIconOption): void {
    Flex({ direction: FlexDirection.Row, alignItems: ItemAlign.Center }) {
      if (Util.isSymbolResource($$.iconOptions?.icon)) {
        SymbolGlyph($$.iconOptions?.icon)
          .fontSize($$.iconOptions?.symbolicIconOption?.fontSize ?
          Util.symbolFontSize($$.iconOptions?.symbolicIconOption?.fontSize) : LEFT_ICON_SIZE)
          .fontColor($$.iconOptions?.symbolicIconOption?.fontColor ?? [this.subHeaderTheme.leftIconColor])
          .fontWeight($$.iconOptions?.symbolicIconOption?.fontWeight)
          .renderingStrategy($$.iconOptions?.symbolicIconOption?.renderingStrategy)
          .effectStrategy($$.iconOptions?.symbolicIconOption?.effectStrategy)
          .margin({ end: LengthMetrics.vp(getResourceValue('sys.float.padding_level4')) })
          .flexShrink(0)
      } else {
        Image($$.iconOptions?.icon)
          .fillColor(this.subHeaderTheme.leftIconColor)
          .width(LEFT_ICON_SIZE)
          .height(LEFT_ICON_SIZE)
          .margin({ end: LengthMetrics.vp(getResourceValue('sys.float.padding_level4')) })
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
    .commonListPadding()
  }

  @Builder
  SubTitleStyle($$: ContentIconOption): void {
    Column() {
      Text($$.content)
        .primaryTitleStyles({
          fontWeight: getResourceValue('sys.float.subheader_title_font_weight'),
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
        })
        .attributeModifier(this.secondaryTitleModifier)
    }
    .width('100%')
    .commonContentPadding()
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
      .commonListPadding()
  }

  @Builder
  SelectStyle(selectParam: SelectOptions): void {
    Select(selectParam.options)
      .height('auto')
      .width('auto')
      .selected(this.selectedIndex)
      .value(this.selectValue)
      .onSelect((index: number, value?: string) => {
        this.selectedIndex = index;
        if (value) {
          this.selectValue = value;
        }
        if (selectParam.onSelect) {
          selectParam.onSelect(index, value);
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
        fontWeight: getResourceValue('sys.float.subheader_title_font_weight'),
        maxLines: DOUBLE_LINE_NUM,
        alignment: Alignment.Start,
        fontColor: this.subHeaderTheme.fontPrimaryColor,
      })
      .attributeModifier(this.primaryTitleModifier)
      .commonContentPadding()
  }

  @Builder
  ButtonStyle(button: OperationOption): void {
    if (button) {
      Button({ type: ButtonType.Normal, stateEffect: false }) {
        Text(button.value)
          .secondaryTitleStyles({
            fontWeight: FontWeight.Medium,
            maxLines: DOUBLE_LINE_NUM,
            fontColor: this.subHeaderTheme.fontButtonColor,
          })
          .focusable(true)
      }
      .focusable(true)
      .focusBox({
        margin: { value: INDEX_ZERO, unit: LengthUnit.VP },
        strokeColor: ColorMetrics.resourceColor(this.subHeaderTheme.borderFocusColor),
        strokeWidth: LengthMetrics.vp(getResourceValue('sys.float.outline_extra_larger')),
      })
      .padding({
        start: LengthMetrics.vp(getResourceValue('sys.float.padding_level1')),
        end: LengthMetrics.vp(getResourceValue('sys.float.padding_level1')),
        top: LengthMetrics.vp(getResourceValue('sys.float.padding_level2')),
        bottom: LengthMetrics.vp(getResourceValue('sys.float.padding_level2')),
      })
      .margin({
        start: this.ageing ?
        LengthMetrics.vp(LengthMetrics.vp(getResourceValue('sys.float.padding_level0')).value +
        this.leftIconMargin().value) :
        LengthMetrics.vp(LengthMetrics.vp(getResourceValue('sys.float.padding_level4')).value +
        this.leftIconMargin().value),
        bottom: LengthMetrics.vp(this.ageing ? getResourceValue('sys.float.padding_level0') :
        getResourceValue('sys.float.padding_level2')),
      })
      .backgroundColor(this.buttonBgColor)
      .constraintSize({ minHeight: OPERATE_ITEM_LENGTH })
      .align(Alignment.End)
      .borderRadius(getResourceValue('sys.float.corner_radius_level4'))
      .onHover((isHover: boolean) => {
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
    if (this.icon && Util.isSymbolResource(this.icon)) {
      return this.ageing ? LengthMetrics.vp((this.iconSymbolOptions?.fontSize ?
      Util.numberToSize(this.iconSymbolOptions?.fontSize) : LEFT_ICON_SIZE_NUMBER) +
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
          .margin({
            end: this.getTextArrowMarginRight(),
          })
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
    })
  }

  @Builder
  ArrowStyle(): void {
    Row() {
      Image($r('sys.media.ohos_ic_public_arrow_right'))
        .fillColor(this.subHeaderTheme.iconArrowColor)
        .width(ARROW_ICON_WIDTH)
        .height(OPERATE_ITEM_LENGTH)
        .focusable(true)
        .draggable(false)
        .matchTextDirection(true)
    }
    .justifyContent(FlexAlign.End)
  }

  @Builder
  TextArrowStyle(textArrow: OperationOption): void {
    if (textArrow && textArrow.value && textArrow.value.toString().length > 0) {
      Stack() {
        Button({ type: ButtonType.Normal, stateEffect: false }) {
          TextArrowLayout() {
            ForEach([INDEX_ZERO, INDEX_ONE], (index: number) => {
              if (index === INDEX_ZERO) {
                this.TextStyle(textArrow);
              } else {
                this.ArrowStyle();
              }
            });
          }
        }
        .padding(INDEX_ZERO)
        .margin({ start: this.leftIconMargin() })
        .backgroundColor(this.textArrowBgColor)
        .focusBox({
          margin: { value: INDEX_ZERO, unit: LengthUnit.VP },
          strokeColor: ColorMetrics.resourceColor(this.subHeaderTheme.borderFocusColor),
          strokeWidth: LengthMetrics.vp(getResourceValue('sys.float.outline_extra_larger')),
        })
        .borderRadius(getResourceValue('sys.float.corner_radius_level4'))
        .stateStyles({
          pressed: pressedStyle,
          disabled: disabledStyle,
        })
        .onHover((isHover: boolean) => {
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
      })
    } else {
      Row() {
        Button({ type: ButtonType.Normal, stateEffect: false }) {
          Image($r('sys.media.ohos_ic_public_arrow_right'))
            .fillColor(this.subHeaderTheme.iconArrowColor)
            .width(ARROW_ICON_WIDTH)
            .height(OPERATE_ITEM_LENGTH)
            .focusable(true)
            .draggable(false)
            .matchTextDirection(true)
        }
        .width(ARROW_ICON_WIDTH)
        .height(OPERATE_ITEM_LENGTH)
        .backgroundColor(this.textArrowBgColor)
        .focusBox({
          margin: { value: INDEX_ZERO, unit: LengthUnit.VP },
          strokeColor: ColorMetrics.resourceColor(this.subHeaderTheme.borderFocusColor),
          strokeWidth: LengthMetrics.vp(getResourceValue('sys.float.outline_extra_larger')),
        })
        .borderRadius(getResourceValue('sys.float.corner_radius_level4'))
        .stateStyles({
          pressed: pressedStyle,
          disabled: disabledStyle,
        })
        .onHover((isHover: boolean) => {
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
        })
      }
      .focusable(true)
      .constraintSize({ minWidth: this.getRightAreaMinWidth() })
      .justifyContent(FlexAlign.End)
    }
  }

  @Builder
  IconGroupStyle(operationItem: Array<OperationOption>): void {
    Row() {
      ForEach(operationItem, (item: OperationOption, index: number) => {
        if (Util.isResourceType(item.value)) {
          if (index <= INDEX_TWO) {
            SingleIconStyle({
              item: {
                iconOptions: {
                  icon: item.value as Resource,
                  symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > index ?
                  this.operationSymbolOptions[index] : null,
                },
                action: item.action,
                accessibilityLevel: item.accessibilityLevel,
                accessibilityText: item.accessibilityText,
                accessibilityDescription: item.accessibilityDescription,
              },
              isSingleIcon: this.operationItem?.length === SINGLE_ICON_NUMBER,
            })
              .margin({
                start: LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
                bottom: LengthMetrics.vp(getResourceValue('sys.float.padding_level3')),
              })
          } else {
            // 最大支持3个ICON,此场景不支持
          }
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
    })
    .margin({
      start: LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
    })
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
    if (this.item?.accessibilityText) {
      let iconAccessibilityText = typeof this.item.accessibilityText === 'string' ? this.item.accessibilityText :
      getContext()?.resourceManager?.getStringSync(this.item.accessibilityText)
      return iconAccessibilityText;
    }
    return '';
  }

  private getRightIconAccessibilityLevel(): string {
    if (this.item?.accessibilityLevel && this.item?.accessibilityLevel !== '') {
      return this.item.accessibilityLevel;
    }
    return 'auto';
  }

  private toStringFormat(resource: ResourceStr | undefined): string | undefined {
    if (typeof resource === 'string' || typeof resource === 'undefined') {
      return resource;
    } else {
      let resourceString: string = '';
      try {
        resourceString = getContext()?.resourceManager?.getStringSync(resource);
      } catch (err) {
        let code: number = (err as BusinessError)?.code;
        let message: string = (err as BusinessError)?.message;
        hilog.error(0x3900, 'Ace', `Faild to subHeader toStringFormat, code: ${code}, message: ${message}`)
      }
      return resourceString;
    }
  }

  private  getRightIconAccessibilityDescription(): string | undefined {
    if (this.item?.accessibilityDescription && this.item?.accessibilityDescription !== '') {
      return this.toStringFormat(this.item?.accessibilityDescription);
    }
    return '';
  }

  build() {
    if (this.item && this.item.iconOptions) {
      Button({ type: ButtonType.Normal, stateEffect: false }) {
        this.IconZone();
      }
      .focusable(true)
      .width(SINGLE_ICON_ZONE_SIZE)
      .height(SINGLE_ICON_ZONE_SIZE)
      .align(Alignment.Center)
      .backgroundColor(this.bgColor)
      .borderRadius(getResourceValue('sys.float.corner_radius_level4'))
      .accessibilityLevel(this.getRightIconAccessibilityLevel())
      .accessibilityText(this.getRightIconAccessibilityText())
      .accessibilityDescription(this.getRightIconAccessibilityDescription())
      .focusBox({
        margin: { value: INDEX_ZERO, unit: LengthUnit.VP },
        strokeColor: ColorMetrics.resourceColor(this.subHeaderTheme.borderFocusColor),
        strokeWidth: LengthMetrics.vp(getResourceValue('sys.float.outline_extra_larger')),
      })
      .stateStyles({
        pressed: pressedStyle,
        disabled: disabledStyle,
      })
      .onTouch((event) => {
        if (event.type === TouchType.Down || TouchType.Cancel) {
          this.bgColor = $r('sys.color.interactive_pressed');
        }
        if (event.type === TouchType.Up) {
          this.bgColor = $r('sys.color.ohos_id_color_sub_background_transparent');
        }
      })
      .onHover((isHover: boolean) => {
        if (isHover) {
          this.bgColor = $r('sys.color.interactive_hover');
        } else {
          this.bgColor = $r('sys.color.ohos_id_color_sub_background_transparent');
        }
      })
      .responseRegion(this.iconResponseRegion())
      .onClick((event) => {
        if (this.item?.action) {
          this.item?.action();
        }
      })
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
    Util.symbolFontSize(item.iconOptions?.symbolicIconOption?.fontSize) : RIGHT_SINGLE_ICON_SIZE;
  }

  @Builder
  IconZone(): void {
    if (this.item && this.item.iconOptions) {
      if (Util.isSymbolResource(this.item.iconOptions.icon)) {
        SymbolGlyph(this.item.iconOptions?.icon)
          .focusable(true)
          .fontSize(this.fontSizeValue(this.item))
          .fontColor(this.item.iconOptions?.symbolicIconOption?.fontColor ?? [this.subHeaderTheme.rightIconColor])
          .fontWeight(this.item.iconOptions?.symbolicIconOption?.fontWeight)
          .renderingStrategy(this.item.iconOptions?.symbolicIconOption?.renderingStrategy)
          .effectStrategy(this.item.iconOptions?.symbolicIconOption?.effectStrategy)
      } else {
        Image(this.item?.iconOptions?.icon)
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
    return resource.type === RESOURCE_TYPE_SYMBOL;
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
  public static getNumberByResource(resourceId: number, defaultNumber: number): number {
    try {
      let resourceNumber: number = resourceManager.getSystemResourceManager().getNumber(resourceId);
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
  public static getStringByResource(resourceId: number, defaultString: string): string {
    try {
      let resourceString: string = getContext().resourceManager.getStringSync(resourceId);
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
      const fontSizeNumber: number = parseInt(fontSize);
      return fontSizeNumber;
    } else if (typeof fontSize === 'number') {
      return fontSize;
    } else {
      return getContext().resourceManager.getNumber(fontSize);
    }
  }

  public static symbolFontSize(fontSize: Length): Length {
    return Util.numberToSize(fontSize) + 'vp';
  }
}

function getResourceValue(resourceName: string): number {
  if (RESOURCE_CACHE_MAP.hasKey(resourceName)) {
    let resourceValue: number | undefined = RESOURCE_CACHE_MAP.get(resourceName).resourceValue;
    if (typeof resourceValue === 'number') {
      return resourceValue;
    } else {
      resourceValue = Util.getNumberByResource(RESOURCE_CACHE_MAP.get(resourceName).resourceId,
        RESOURCE_CACHE_MAP.get(resourceName).defaultValue);
      RESOURCE_CACHE_MAP.get(resourceName).resourceValue = resourceValue;
      return resourceValue;
    }
  }
  return 0;
}

@Component
struct TextArrowLayout {
  @Builder
  doNothingBuilder(): void {
  };

  @BuilderParam textArrowBuilder: () => void = this.doNothingBuilder;

  onPlaceChildren(selfLayoutInfo: GeometryInfo, children: Array<Layoutable>,
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
    let textArrowWidth: number = ARROW_ICON_WIDTH;
    let textArrowHeight: number = OPERATE_ITEM_LENGTH;

    let textChild: Measurable = children[INDEX_ZERO];
    let textConstraint: ConstraintSizeOptions = {
      minWidth: Math.max(textArrowWidth, Number(constraint.minWidth)),
      maxWidth: constraint.maxWidth,
      minHeight: Math.max(textArrowHeight, Number(constraint.minHeight)),
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