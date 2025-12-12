'use static'

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
  BackgroundBlurStyleOptions,
  BackgroundEffectOptions,
  BlurStyle,
  BorderRadiuses,
  Builder,
  Button,
  ButtonOptions,
  ButtonType,
  Callback,
  Color,
  ComponentV2,
  Curve,
  Dimension,
  Direction,
  Column,
  ColumnOptions,
  Flex,
  FlexAlign,
  FocusPriority,
  FontWeight,
  HoverEffect,
  Image,
  ItemAlign,
  Length,
  LocalizedBorderRadiuses,
  LocalizedPadding,
  MouseAction,
  Padding,
  PanGesture,
  Position,
  Repeat,
  RepeatItem,
  ResourceStr,
  Resource,
  ResourceColor,
  ScaleOptions,
  ShadowOptions,
  ShadowStyle,
  Stack,
  SymbolGlyph,
  TapGesture,
  Text,
  TextOverflow,
  TouchType,
  UIContext,
  $r,
} from '@ohos.arkui.component';
import {
  ImageModifier, SymbolGlyphModifier, TextModifier,
} from '@ohos.arkui.modifier';
import curves from '@ohos.curves';
import {
  Computed, Event, Local, ObservedV2, Param, Require, Trace,
} from '@ohos.arkui.stateManagement'
import {
  ColorMetrics, LengthMetrics, LengthUnit, PositionT, SizeT
} from '@ohos.arkui.node';
import i18n from '@ohos.i18n';
import util from '@ohos.util';

export interface SegmentButtonV2ItemOptions {
  text?: ResourceStr;
  icon?: ResourceStr;
  symbol?: Resource;
  enabled?: boolean;
  textModifier?: TextModifier;
  iconModifier?: ImageModifier;
  symbolModifier?: SymbolGlyphModifier;
  accessibilityText?: ResourceStr;
  accessibilityDescription?: ResourceStr;
  accessibilityLevel?: string;
}

export type OnSelectedIndexChange = (selectedIndex: int) => void;

export type OnSelectedIndexesChange = (selectedIndexes: int[]) => void;

interface SegmentButtonV2ContentTheme {
  itemSpace: LengthMetrics;
  itemFontSize: Dimension;
  itemFontColor: ResourceColor;
  itemFontWeight: FontWeight;
  itemSelectedFontWeight: FontWeight;
  itemSelectedFontColor: ResourceColor;
  itemIconSize: Dimension;
  itemIconFillColor: ResourceColor;
  itemSelectedIconFillColor: ResourceColor;
  itemSymbolFontSize: Dimension;
  itemSymbolFontColor: ResourceColor;
  itemSelectedSymbolFontColor: ResourceColor;
  itemMinHeight: Dimension;
  hybridItemMinHeight: Dimension;
  itemPadding: LocalizedPadding;
  itemMaxFontScale: double | Resource;
  itemMaxFontScaleSmallest: double;
  itemMaxFontScaleLargest: double;
  itemMinFontScale: double | Resource;
  itemMinFontScaleSmallest: double;
  itemMinFontScaleLargest: double;
}

interface SimpleSegmentButtonV2Theme extends SegmentButtonV2ContentTheme {
  buttonBackgroundColor: Resource;
  buttonBorderRadius: Resource;
  buttonMinHeight: Dimension;
  hybridButtonMinHeight: Dimension;
  buttonPadding: Resource;
  itemSelectedBackgroundColor: ResourceColor;
  itemBorderRadius: Resource;
  itemShadow: ShadowStyle;
}

interface SegmentButtonV2ItemRect {
  size: SizeT<double>;
  position: PositionT<double>;
  globalPosition: PositionT<double>;
}

const SMALLEST_MAX_FONT_SCALE: double = 1.0;
const LARGEST_MAX_FONT_SCALE: double = 2.0;
const SMALLEST_MIN_FONT_SCALE: double = 0.0;
const LARGEST_MIN_FONT_SCALE: double = 1.0;

const tabSimpleTheme: SimpleSegmentButtonV2Theme = {
  buttonBackgroundColor: $r('sys.color.segment_button_v2_tab_button_background'),
  buttonBorderRadius: $r('sys.float.segment_button_v2_background_corner_radius'),
  buttonMinHeight: $r('sys.float.segment_button_v2_singleline_background_height'),
  hybridButtonMinHeight: $r('sys.float.segment_button_v2_doubleline_background_height'),
  buttonPadding: $r('sys.float.padding_level1'),
  itemSelectedBackgroundColor: $r('sys.color.segment_button_v2_tab_selected_item_background'),
  itemBorderRadius: $r('sys.float.segment_button_v2_selected_corner_radius'),
  itemSpace: LengthMetrics.vp(0),
  itemFontSize: $r('sys.float.ohos_id_text_size_button2'),
  itemFontColor: $r('sys.color.font_secondary'),
  itemSelectedFontColor: $r('sys.color.font_primary'),
  itemFontWeight: FontWeight.Medium,
  itemSelectedFontWeight: FontWeight.Medium,
  itemIconSize: 24,
  itemIconFillColor: $r('sys.color.font_secondary'),
  itemSelectedIconFillColor: $r('sys.color.font_primary'),
  itemSymbolFontSize: 20,
  itemSymbolFontColor: $r('sys.color.font_secondary'),
  itemSelectedSymbolFontColor: $r('sys.color.font_primary'),
  itemMinHeight: $r('sys.float.segment_button_v2_singleline_selected_height'),
  hybridItemMinHeight: $r('sys.float.segment_button_v2_doubleline_selected_height'),
  itemPadding: {
    top: LengthMetrics.resource($r('sys.float.padding_level2')),
    bottom: LengthMetrics.resource($r('sys.float.padding_level2')),
    start: LengthMetrics.resource($r('sys.float.padding_level4')),
    end: LengthMetrics.resource($r('sys.float.padding_level4')),
  },
  itemShadow: ShadowStyle.OUTER_DEFAULT_XS,
  itemMaxFontScale: SMALLEST_MAX_FONT_SCALE,
  itemMaxFontScaleSmallest: SMALLEST_MAX_FONT_SCALE,
  itemMaxFontScaleLargest: LARGEST_MAX_FONT_SCALE,
  itemMinFontScale: SMALLEST_MIN_FONT_SCALE,
  itemMinFontScaleSmallest: SMALLEST_MIN_FONT_SCALE,
  itemMinFontScaleLargest: LARGEST_MIN_FONT_SCALE,
};

const capsuleSimpleTheme: SimpleSegmentButtonV2Theme = {
  buttonBackgroundColor: $r('sys.color.segment_button_v2_tab_button_background'),
  buttonBorderRadius: $r('sys.float.segment_button_v2_background_corner_radius'),
  buttonMinHeight: $r('sys.float.segment_button_v2_singleline_background_height'),
  hybridButtonMinHeight: $r('sys.float.segment_button_v2_doubleline_background_height'),
  buttonPadding: $r('sys.float.padding_level1'),
  itemSelectedBackgroundColor: $r('sys.color.comp_background_emphasize'),
  itemBorderRadius: $r('sys.float.segment_button_v2_selected_corner_radius'),
  itemSpace: LengthMetrics.vp(0),
  itemFontSize: $r('sys.float.ohos_id_text_size_button2'),
  itemFontColor: $r('sys.color.font_secondary'),
  itemSelectedFontColor: $r('sys.color.font_on_primary'),
  itemFontWeight: FontWeight.Medium,
  itemSelectedFontWeight: FontWeight.Medium,
  itemIconSize: 24,
  itemIconFillColor: $r('sys.color.icon_secondary'),
  itemSelectedIconFillColor: $r('sys.color.font_on_primary'),
  itemSymbolFontSize: 20,
  itemSymbolFontColor: $r('sys.color.font_secondary'),
  itemSelectedSymbolFontColor: $r('sys.color.font_on_primary'),
  itemMinHeight: $r('sys.float.segment_button_v2_singleline_selected_height'),
  hybridItemMinHeight: $r('sys.float.segment_button_v2_doubleline_selected_height'),
  itemPadding: {
    top: LengthMetrics.resource($r('sys.float.padding_level2')),
    bottom: LengthMetrics.resource($r('sys.float.padding_level2')),
    start: LengthMetrics.resource($r('sys.float.padding_level4')),
    end: LengthMetrics.resource($r('sys.float.padding_level4')),
  },
  itemShadow: ShadowStyle.OUTER_DEFAULT_XS,
  itemMaxFontScale: SMALLEST_MAX_FONT_SCALE,
  itemMaxFontScaleSmallest: SMALLEST_MAX_FONT_SCALE,
  itemMaxFontScaleLargest: LARGEST_MAX_FONT_SCALE,
  itemMinFontScale: SMALLEST_MIN_FONT_SCALE,
  itemMinFontScaleSmallest: SMALLEST_MIN_FONT_SCALE,
  itemMinFontScaleLargest: LARGEST_MIN_FONT_SCALE,
}

@ObservedV2
export class SegmentButtonV2Item {
  @Trace public text?: ResourceStr;
  @Trace public icon?: ResourceStr;
  @Trace public symbol?: Resource;
  @Trace public enabled: boolean;
  @Trace public textModifier?: TextModifier;
  @Trace public iconModifier?: ImageModifier;
  @Trace public symbolModifier?: SymbolGlyphModifier;
  @Trace public accessibilityText?: ResourceStr;
  @Trace public accessibilityDescription?: ResourceStr;
  @Trace public accessibilityLevel?: string;

  constructor(options: SegmentButtonV2ItemOptions) {
    this.text = options.text;
    this.icon = options.icon;
    this.symbol = options.symbol;
    this.enabled = options.enabled ?? true;
    this.textModifier = options.textModifier;
    this.iconModifier = options.iconModifier;
    this.symbolModifier = options.symbolModifier;
    this.accessibilityText = options.accessibilityText;
    this.accessibilityDescription = options.accessibilityDescription;
    this.accessibilityLevel = options.accessibilityLevel;
  }

  @Computed
  get isHybrid(): boolean {
    return !!this.text && (!!this.icon || !!this.symbol);
  }
}

@ObservedV2
export class SegmentButtonV2Items extends Array<SegmentButtonV2Item> {
  constructor(length: int) {
    super(length);
  }

  constructor(items: SegmentButtonV2ItemOptions[]) {
    for (let options of items) {
      this.push(new SegmentButtonV2Item(options));
    }
  }

  @Computed
  get hasHybrid(): boolean {
    return this.some((item) => item.isHybrid);
  }
}

const EMPTY_ITEMS = new SegmentButtonV2Items([]);

@ComponentV2
export struct TabSegmentButtonV2 {
  @Require @Param items: SegmentButtonV2Items;
  @Require @Param selectedIndex: int;
  @Event $selectedIndex?: OnSelectedIndexChange;
  @Event onItemClicked?: Callback<int>;
  @Param itemMinFontScale?: double | Resource = undefined;
  @Param itemMaxFontScale?: double | Resource = undefined;
  @Param itemSpace?: LengthMetrics = undefined;
  @Param itemFontSize?: LengthMetrics = undefined;
  @Param itemSelectedFontSize?: LengthMetrics = undefined;
  @Param itemFontColor?: ColorMetrics = undefined;
  @Param itemSelectedFontColor?: ColorMetrics = undefined;
  @Param itemFontWeight?: FontWeight = undefined;
  @Param itemSelectedFontWeight?: FontWeight = undefined;
  @Param itemBorderRadius?: LengthMetrics = undefined;
  @Param itemSelectedBackgroundColor?: ColorMetrics = undefined;
  @Param itemIconSize?: SizeT<LengthMetrics> = undefined;
  @Param itemIconFillColor?: ColorMetrics = undefined;
  @Param itemSelectedIconFillColor?: ColorMetrics = undefined;
  @Param itemSymbolFontSize?: LengthMetrics = undefined;
  @Param itemSymbolFontColor?: ColorMetrics = undefined;
  @Param itemSelectedSymbolFontColor?: ColorMetrics = undefined;
  @Param itemMinHeight?: LengthMetrics = undefined;
  @Param itemPadding?: LocalizedPadding = undefined;
  @Param itemShadow?: ShadowOptions | ShadowStyle = undefined;
  @Param buttonBackgroundColor?: ColorMetrics = undefined;
  @Param buttonBackgroundBlurStyle?: BlurStyle = undefined;
  @Param buttonBackgroundBlurStyleOptions?: BackgroundBlurStyleOptions = undefined;
  @Param buttonBackgroundEffect?: BackgroundEffectOptions = undefined;
  @Param buttonBorderRadius?: LengthMetrics = undefined;
  @Param buttonMinHeight?: LengthMetrics = undefined;
  @Param buttonPadding?: LengthMetrics = undefined;
  @Param languageDirection?: Direction = undefined;

  build() {
    SimpleSegmentButtonV2({
      theme: tabSimpleTheme,
      items: this.items,
      selectedIndex: this.selectedIndex,
      $selectedIndex: (selectedIndex: int) => {
        this.$selectedIndex?.(selectedIndex);
      },
      onItemClicked: this.onItemClicked,
      itemMinFontScale: this.itemMinFontScale,
      itemMaxFontScale: this.itemMaxFontScale,
      itemSpace: this.itemSpace,
      itemFontColor: this.itemFontColor,
      itemSelectedFontColor: this.itemSelectedFontColor,
      itemFontSize: this.itemFontSize,
      itemSelectedFontSize: this.itemSelectedFontSize,
      itemFontWeight: this.itemFontWeight,
      itemSelectedFontWeight: this.itemSelectedFontWeight,
      itemSelectedBackgroundColor: this.itemSelectedBackgroundColor,
      itemIconSize: this.itemIconSize,
      itemIconFillColor: this.itemIconFillColor,
      itemSelectedIconFillColor: this.itemSelectedIconFillColor,
      itemSymbolFontSize: this.itemSymbolFontSize,
      itemSymbolFontColor: this.itemSymbolFontColor,
      itemSelectedSymbolFontColor: this.itemSelectedSymbolFontColor,
      itemBorderRadius: this.itemBorderRadius,
      itemMinHeight: this.itemMinHeight,
      itemPadding: this.itemPadding,
      itemShadow: this.itemShadow,
      buttonBackgroundColor: this.buttonBackgroundColor,
      buttonBackgroundBlurStyle: this.buttonBackgroundBlurStyle,
      buttonBackgroundBlurStyleOptions: this.buttonBackgroundBlurStyleOptions,
      buttonBackgroundEffect: this.buttonBackgroundEffect,
      buttonBorderRadius: this.buttonBorderRadius,
      buttonMinHeight: this.buttonMinHeight,
      buttonPadding: this.buttonPadding,
      languageDirection: this.languageDirection,
    })
  }
}

@ComponentV2
export struct CapsuleSegmentButtonV2 {
  @Require @Param items: SegmentButtonV2Items;
  @Require @Param selectedIndex: int;
  @Event $selectedIndex?: OnSelectedIndexChange;
  @Event onItemClicked?: Callback<int>;
  @Param itemMinFontScale?: double | Resource = undefined;
  @Param itemMaxFontScale?: double | Resource = undefined;
  @Param itemSpace?: LengthMetrics = undefined;
  @Param itemFontColor?: ColorMetrics = undefined;
  @Param itemSelectedFontColor?: ColorMetrics = undefined;
  @Param itemFontSize?: LengthMetrics = undefined;
  @Param itemSelectedFontSize?: LengthMetrics = undefined;
  @Param itemFontWeight?: FontWeight = undefined;
  @Param itemSelectedFontWeight?: FontWeight = undefined;
  @Param itemBorderRadius?: LengthMetrics = undefined;
  @Param itemSelectedBackgroundColor?: ColorMetrics = undefined;
  @Param itemIconSize?: SizeT<LengthMetrics> = undefined;
  @Param itemIconFillColor?: ColorMetrics = undefined;
  @Param itemSelectedIconFillColor?: ColorMetrics = undefined;
  @Param itemSymbolFontSize?: LengthMetrics = undefined;
  @Param itemSymbolFontColor?: ColorMetrics = undefined;
  @Param itemSelectedSymbolFontColor?: ColorMetrics = undefined;
  @Param itemMinHeight?: LengthMetrics = undefined;
  @Param itemPadding?: LocalizedPadding = undefined;
  @Param itemShadow?: ShadowOptions | ShadowStyle = undefined;
  @Param buttonBackgroundColor?: ColorMetrics = undefined;
  @Param buttonBackgroundBlurStyle?: BlurStyle = undefined;
  @Param buttonBackgroundBlurStyleOptions?: BackgroundBlurStyleOptions = undefined;
  @Param buttonBackgroundEffect?: BackgroundEffectOptions = undefined;
  @Param buttonBorderRadius?: LengthMetrics = undefined;
  @Param buttonMinHeight?: LengthMetrics = undefined;
  @Param buttonPadding?: LengthMetrics = undefined;
  @Param languageDirection?: Direction = undefined;

  build() {
    SimpleSegmentButtonV2({
      theme: capsuleSimpleTheme,
      items: this.items,
      selectedIndex: this.selectedIndex,
      $selectedIndex: (selectedIndex: int) => {
        this.$selectedIndex?.(selectedIndex);
      },
      onItemClicked: this.onItemClicked,
      itemMinFontScale: this.itemMinFontScale,
      itemMaxFontScale: this.itemMaxFontScale,
      itemSpace: this.itemSpace,
      itemFontColor: this.itemFontColor,
      itemSelectedFontColor: this.itemSelectedFontColor,
      itemFontSize: this.itemFontSize,
      itemSelectedFontSize: this.itemSelectedFontSize,
      itemFontWeight: this.itemFontWeight,
      itemSelectedFontWeight: this.itemSelectedFontWeight,
      itemSelectedBackgroundColor: this.itemSelectedBackgroundColor,
      itemIconSize: this.itemIconSize,
      itemIconFillColor: this.itemIconFillColor,
      itemSelectedIconFillColor: this.itemSelectedIconFillColor,
      itemSymbolFontSize: this.itemSymbolFontSize,
      itemSymbolFontColor: this.itemSymbolFontColor,
      itemSelectedSymbolFontColor: this.itemSelectedSymbolFontColor,
      itemBorderRadius: this.itemBorderRadius,
      itemMinHeight: this.itemMinHeight,
      itemPadding: this.itemPadding,
      itemShadow: this.itemShadow,
      buttonBackgroundColor: this.buttonBackgroundColor,
      buttonBackgroundBlurStyle: this.buttonBackgroundBlurStyle,
      buttonBackgroundBlurStyleOptions: this.buttonBackgroundBlurStyleOptions,
      buttonBackgroundEffect: this.buttonBackgroundEffect,
      buttonBorderRadius: this.buttonBorderRadius,
      buttonMinHeight: this.buttonMinHeight,
      buttonPadding: this.buttonPadding,
      languageDirection: this.languageDirection,
    })
  }
}

@ComponentV2
struct SimpleSegmentButtonV2 {
  @Require @Param items: SegmentButtonV2Items;
  @Require @Param selectedIndex: int;
  @Event $selectedIndex?: OnSelectedIndexChange;
  @Require @Param theme: SimpleSegmentButtonV2Theme;
  @Event onItemClicked?: Callback<int>;
  @Require @Param itemMinFontScale?: double | Resource = undefined;
  @Require @Param itemMaxFontScale?: double | Resource = undefined;
  @Require @Param itemSpace?: LengthMetrics = undefined;
  @Require @Param itemFontColor?: ColorMetrics = undefined;
  @Require @Param itemSelectedFontColor?: ColorMetrics = undefined;
  @Require @Param itemFontSize?: LengthMetrics = undefined;
  @Require @Param itemSelectedFontSize?: LengthMetrics = undefined;
  @Require @Param itemFontWeight?: FontWeight = undefined;
  @Require @Param itemSelectedFontWeight?: FontWeight = undefined;
  @Require @Param itemBorderRadius?: LengthMetrics = undefined;
  @Require @Param itemSelectedBackgroundColor?: ColorMetrics = undefined;
  @Require @Param itemIconSize?: SizeT<LengthMetrics> = undefined;
  @Require @Param itemIconFillColor?: ColorMetrics = undefined;
  @Require @Param itemSelectedIconFillColor?: ColorMetrics = undefined;
  @Require @Param itemSymbolFontSize?: LengthMetrics = undefined;
  @Require @Param itemSymbolFontColor?: ColorMetrics = undefined;
  @Require @Param itemSelectedSymbolFontColor?: ColorMetrics = undefined;
  @Require @Param itemMinHeight?: LengthMetrics = undefined;
  @Require @Param itemPadding?: LocalizedPadding = undefined;
  @Require @Param itemShadow?: ShadowOptions | ShadowStyle = undefined;
  @Require @Param buttonBackgroundColor?: ColorMetrics = undefined;
  @Require @Param buttonBackgroundBlurStyle?: BlurStyle = undefined;
  @Require @Param buttonBackgroundBlurStyleOptions?: BackgroundBlurStyleOptions = undefined;
  @Require @Param buttonBackgroundEffect?: BackgroundEffectOptions = undefined;
  @Require @Param buttonBorderRadius?: LengthMetrics = undefined;
  @Require @Param buttonMinHeight?: LengthMetrics = undefined;
  @Require @Param buttonPadding?: LengthMetrics = undefined;
  @Require @Param languageDirection?: Direction = undefined;
  @Local itemRects: Map<int, SegmentButtonV2ItemRect> = new Map<int, SegmentButtonV2ItemRect>();
  @Local itemScale: double = 1;
  @Local hoveredItemIndex: int = -1;
  @Local mousePressedItemIndex: int = -1;
  @Local touchPressedItemIndex: int = -1;
  private isMouseWheelScroll: boolean = false;
  private isDragging: boolean = false;
  private panStartGlobalX: double = 0;
  private panStartIndex: int = -1;
  private focusGroupId: string = GroupIdGenerator.getInstance().generate();

  @Computed
  get normalizedSelectedIndex(): int {
    const items = this.getItems();
    return normalizeInt(this.selectedIndex, 0, items.length - 1);
  }

  @Computed
  get selectedItemRect(): SegmentButtonV2ItemRect | undefined {
    return this.itemRects.get(this.normalizedSelectedIndex);
  }

  @Builder
  private ContentLayer() {
    Flex({ alignItems: ItemAlign.Stretch, space: { main: this.getItemSpace() } }) {
      Repeat<SegmentButtonV2Item>(this.getItems())
        .each((repeatItem: RepeatItem<SegmentButtonV2Item>): void => {
          Button({ type: ButtonType.Normal } as ButtonOptions) {
            SegmentButtonV2ItemContent({
              theme: this.theme,
              item: repeatItem.item,
              selected: this.isSelected(repeatItem),
              itemMinFontScale: this.itemMinFontScale,
              itemMaxFontScale: this.itemMaxFontScale,
              itemFontColor: this.itemFontColor,
              itemSelectedFontColor: this.itemSelectedFontColor,
              itemFontSize: this.itemFontSize,
              itemSelectedFontSize: this.itemSelectedFontSize,
              itemFontWeight: this.itemFontWeight,
              itemSelectedFontWeight: this.itemSelectedFontWeight,
              itemIconSize: this.itemIconSize,
              itemIconFillColor: this.itemIconFillColor,
              itemSelectedIconFillColor: this.itemSelectedIconFillColor,
              itemSymbolFontSize: this.itemSymbolFontSize,
              itemSymbolFontColor: this.itemSymbolFontColor,
              itemSelectedSymbolFontColor: this.itemSelectedSymbolFontColor,
              itemMinHeight: this.itemMinHeight,
              itemPadding: this.itemPadding,
              languageDirection: this.languageDirection,
              hasHybrid: this.getItems().hasHybrid,
            })
          }
          .accessibilityGroup(true)
          .accessibilitySelected(this.isSelected(repeatItem))
          .accessibilityText(this.getItemAccessibilityText(repeatItem))
          .accessibilityDescription(this.getItemAccessibilityDescription(repeatItem))
          .accessibilityLevel(repeatItem.item.accessibilityLevel)
          .backgroundColor(Color.Transparent)
          .borderRadius(this.getItemBorderRadius())
          .direction(this.languageDirection)
          .enabled(repeatItem.item.enabled)
          .focusScopePriority(this.focusGroupId, this.getFocusPriority(repeatItem))
          .hoverEffect(HoverEffect.None)
          .layoutWeight(1)
          .padding(0)
          .scale(this.getItemScale(repeatItem.index))
          .stateEffect(false)
          .onAreaChange((_, area) => {
            const index: int = repeatItem.index;
            const itemRect: SegmentButtonV2ItemRect = {
              size: {
                width: area.width as double,
                height: area.height as double,
              },
              position: {
                x: area.position.x as double,
                y: area.position.y as double,
              },
              globalPosition: {
                x: area.globalPosition.x as double,
                y: area.globalPosition.y as double,
              }
            };
            this.itemRects.set(index, itemRect);
          })
          .gesture(
            TapGesture().onAction(() => {
              const index: int = repeatItem.index;
              this.onItemClicked?.(index);
              this.updateSelectedIndex(index);
            })
          )
          .onTouch((event) => {
            if (event.type === TouchType.Down) {
              if (this.isSelected(repeatItem)) {
                this.updateItemScale(0.95);
              }
              this.updateTouchPressedItemIndex(repeatItem.index);
            } else if ([TouchType.Up, TouchType.Cancel].includes(event.type)) {
              this.updateItemScale(1)
              this.updateTouchPressedItemIndex(-1);
            }
          })
          .onHover((isHover) => {
            if (isHover) {
              this.updateHoveredItemIndex(repeatItem.index);
            } else {
              this.updateHoveredItemIndex(-1);
            }
          })
          .onMouse((event) => {
            if (event.action === MouseAction.Press) {
              this.updateMousePressedItemIndex(repeatItem.index);
            } else if ([MouseAction.Release, MouseAction.CANCEL].includes(event.action)) {
              this.updateMousePressedItemIndex(-1);
            }
          })
        })
        .key(generateUniqueKye(this.focusGroupId))
        .virtualScroll({ disableVirtualScroll: true })
    }
    .constraintSize({
      minWidth: '100%',
      minHeight: this.getButtonMinHeight()
    })
    .clip(false)
    .direction(this.languageDirection)
    .focusScopeId(this.focusGroupId, true)
    .padding(this.getButtonPadding())
    .priorityGesture(
      PanGesture()
        .onActionStart((event) => {
          const finger = event.fingerList.find((element) => Boolean(element));
          if (!finger) {
            return;
          }
          const index = this.getIndexByPosition(finger.globalX, finger.globalY);
          if (!this.isItemEnabled(index)) {
            return;
          }
          if (event.axisHorizontal !== 0 || event.axisVertical !== 0) {
            this.isMouseWheelScroll = true;
            return;
          }
          if (index === this.normalizedSelectedIndex) {
            this.isDragging = true;
          }
          this.panStartGlobalX = finger.globalX;
          this.panStartIndex = index;
        })
        .onActionUpdate((event) => {
          if (!this.isDragging) {
            return;
          }
          const finger = event.fingerList.find((element) => Boolean(element));
          if (!finger) {
            return;
          }
          const index = this.getIndexByPosition(finger.globalX, finger.globalY);
          this.updateSelectedIndex(index);
        })
        .onActionEnd((event) => {
          if (!this.isItemEnabled(this.panStartIndex)) {
            return;
          }
          // handle mouse wheel scroll event
          if (this.isMouseWheelScroll) {
            const offset = event.offsetX !== 0 ? event.offsetX : event.offsetY;
            const deltaIndex: int = offset < 0 ? 1 : -1;
            this.updateSelectedIndex(this.normalizedSelectedIndex + deltaIndex);
            this.isMouseWheelScroll = false;
            return;
          }
          // handle drag event
          if (this.isDragging) {
            this.isDragging = false;
            return;
          }
          // handle swipe event
          if (!this.isItemEnabled(this.normalizedSelectedIndex)) {
            return;
          }
          const finger = event.fingerList.find((element) => Boolean(element));
          if (!finger) {
            return;
          }
          let deltaIndex: int = finger.globalX - this.panStartGlobalX < 0 ? -1 : 1;
          if (this.isRTL()) {
            deltaIndex = -deltaIndex;
          }
          this.updateSelectedIndex(this.normalizedSelectedIndex + deltaIndex);
        })
        .onActionCancel(() => {
          this.isDragging = false;
          this.isMouseWheelScroll = false;
          this.panStartIndex = -1;
        })
    )
  }

  private getFocusPriority(repeatItem: RepeatItem<SegmentButtonV2Item>): FocusPriority | undefined {
    return this.normalizedSelectedIndex === repeatItem.index ? FocusPriority.PREVIOUS : FocusPriority.AUTO;
  }

  private isItemEnabled(index: int): boolean {
    const items = this.getItems();
    if (index < 0 || index >= items.length) {
      return false;
    }
    return items[index].enabled;
  }

  @Builder
  private BackplateLayer() {
    if (this.selectedItemRect) {
      Stack()
        .position({
          x: this.selectedItemRect!.position.x,
          y: this.selectedItemRect!.position.y,
        } as Position)
        .animation({ curve: curves.springMotion(0.347, 0.99) })
        .backgroundColor(this.getItemSelectedBackgroundColor())
        .borderRadius(this.getItemBorderRadius())
        .scale({ x: this.itemScale, y: this.itemScale })
        .shadow(this.getItemBackplateShadow())
        .height(this.selectedItemRect!.size.height)
        .width(this.selectedItemRect!.size.width)
    }
  }

  @Builder
  private EffectLayer() {
    Repeat<SegmentButtonV2ItemRect>(this.getItemRects())
      .each((repeatItem) => {
        Stack()
          .backgroundColor(this.getEffectBackgroundColor(repeatItem))
          .borderRadius(this.getItemBorderRadius())
          .height(repeatItem.item.size.height)
          .position({
            x: repeatItem.item.position.x,
            y: repeatItem.item.position.y
          } as Position)
          .scale(this.getItemScale(repeatItem.index))
          .width(repeatItem.item.size.width)
      })
  }

  private getItemRects(): SegmentButtonV2ItemRect[] {
    if (!this.items || this.items.length !== this.itemRects.size) {
      return [];
    }
    return this.items.map(
      // todo number to int
      (_: SegmentButtonV2Item, index: double) => this.itemRects.get(index.toInt())!
    );
  }

  build() {
    Stack() {
      Stack() {
        this.EffectLayer()
        this.BackplateLayer()
        this.ContentLayer()
      }
      .borderRadius(this.getButtonBorderRadius())
      .backgroundBlurStyle(this.getButtonBackgroundBlurStyle(), this.getButtonBackgroundBlurStyleOptions(),
        { disableSystemAdaptation: true })
      .clip(false)
      .direction(this.languageDirection)
    }
    .backgroundColor(this.getButtonBackgroundColor())
    .backgroundEffect(this.buttonBackgroundEffect, { disableSystemAdaptation: true })
    .borderRadius(this.getButtonBorderRadius())
    .clip(false)
    .constraintSize({
      minWidth: '100%',
      minHeight: this.getButtonMinHeight()
    })
    .direction(this.languageDirection)
  }

  private getItems(): SegmentButtonV2Items {
    return this.items ?? EMPTY_ITEMS;
  }

  private getItemBackplateShadow(): ShadowOptions | ShadowStyle | undefined {
    return this.itemShadow ?? this.theme.itemShadow
  }

  private getButtonBackgroundBlurStyle(): BlurStyle | undefined {
    if (this.buttonBackgroundEffect) {
      return undefined;
    }
    return this.buttonBackgroundBlurStyle;
  }

  private getButtonBackgroundBlurStyleOptions(): BackgroundBlurStyleOptions | undefined {
    if (this.buttonBackgroundEffect) {
      return undefined;
    }
    return this.buttonBackgroundBlurStyleOptions;
  }

  private getItemScale(index: int): ScaleOptions {
    const pressed: boolean = this.isPressed(index);
    const scale: double = pressed ? 0.95 : 1;
    return { x: scale, y: scale, };
  }

  private isPressed(index: int): boolean {
    return this.mousePressedItemIndex === index;
  }

  private updateHoveredItemIndex(index: int) {
    if (index === this.hoveredItemIndex) {
      return;
    }
    this.getUIContext().animateTo({ duration: 250, curve: Curve.Friction }, () => {
      this.hoveredItemIndex = index;
    });
  }

  private updateMousePressedItemIndex(index: int) {
    if (index === this.mousePressedItemIndex) {
      return;
    }
    this.getUIContext().animateTo({ duration: 250, curve: Curve.Friction }, () => {
      this.mousePressedItemIndex = index;
    });
  }

  private updateTouchPressedItemIndex(index: int) {
    if (index === this.touchPressedItemIndex) {
      return;
    }
    this.getUIContext().animateTo({ duration: 250, curve: Curve.Friction }, () => {
      this.touchPressedItemIndex = index;
    });
  }

  private isRTL(): boolean {
    if (this.languageDirection || this.languageDirection === Direction.Auto) {
      return i18n.isRTL(i18n.System.getSystemLanguage());
    }
    return this.languageDirection === Direction.Rtl;
  }

  private getEffectBackgroundColor(repeatItem: RepeatItem<SegmentButtonV2ItemRect>): ResourceColor {
    if (repeatItem.index === this.mousePressedItemIndex) {
      return $r('sys.color.interactive_click');
    }
    if (repeatItem.index === this.hoveredItemIndex) {
      return $r('sys.color.interactive_hover');
    }
    return Color.Transparent;
  }

  private getItemBorderRadius(): Length | BorderRadiuses | LocalizedBorderRadiuses {
    if (this.itemBorderRadius) {
      const itemBorderRadius = this.itemBorderRadius as LengthMetrics;
      if (LengthMetricsUtils.getInstance().isNaturalNumber(itemBorderRadius)) {
        return LengthMetricsUtils.getInstance().stringify(itemBorderRadius);
      }
    }
    return this.theme.itemBorderRadius;
  }

  private getItemSelectedBackgroundColor(): ResourceColor {
    if (this.itemSelectedBackgroundColor) {
      return this.itemSelectedBackgroundColor!.color;
    }
    return this.theme.itemSelectedBackgroundColor;
  }

  private getItemSpace(): LengthMetrics {
    if (this.itemSpace) {
      const itemSpace = this.itemSpace as LengthMetrics;
      if (itemSpace.unit !== LengthUnit.PERCENT && LengthMetricsUtils.getInstance().isNaturalNumber(itemSpace)) {
        return itemSpace;
      }
    }
    return this.theme.itemSpace;
  }

  private getIndexByPosition(globalX: double, globalY: double): int {
    let index: int = 0;
    while (index < this.itemRects.size) {
      const rect = this.itemRects.get(index);
      if (rect && this.isPointOnRect(globalX, globalY, rect!)) {
        return index;
      }
      ++index;
    }
    return -1;
  }

  private isPointOnRect(globalX: double, globalY: double, rect: SegmentButtonV2ItemRect): boolean {
    return globalX >= rect.globalPosition.x && globalX <= rect.globalPosition.x + rect.size.width &&
      globalY >= rect.globalPosition.y && globalY <= rect.globalPosition.y + rect.size.height;
  }

  private updateSelectedIndex(selectedIndex: int) {
    if (!this.isItemEnabled(selectedIndex) || selectedIndex === this.selectedIndex
    ) {
      return;
    }
    this.$selectedIndex?.(selectedIndex);
  }

  private updateItemScale(scale: double) {
    if (this.itemScale === scale) {
      return;
    }
    this.getUIContext().animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
      this.itemScale = scale;
    });
  }

  private getItemAccessibilityDescription(repeatItem: RepeatItem<SegmentButtonV2Item>): Resource | string | undefined {
    return repeatItem.item.accessibilityDescription;
  }

  private getItemAccessibilityText(repeatItem: RepeatItem<SegmentButtonV2Item>): Resource | string | undefined {
    return repeatItem.item.accessibilityText;
  }

  private isSelected(repeatItem: RepeatItem<SegmentButtonV2Item>): boolean | undefined {
    return repeatItem.index === this.normalizedSelectedIndex;
  }

  private getButtonPadding(): Length | Padding | LocalizedPadding {
    if (this.buttonPadding && LengthMetricsUtils.getInstance().isNaturalNumber(this.buttonPadding!)) {
      return LengthMetricsUtils.getInstance().stringify(this.buttonPadding!);
    }
    return this.theme.buttonPadding;
  }

  private getButtonBorderRadius(): Length | BorderRadiuses | LocalizedBorderRadiuses {
    if (this.buttonBorderRadius &&
    LengthMetricsUtils.getInstance().isNaturalNumber(this.buttonBorderRadius!)) {
      return LengthMetricsUtils.getInstance().stringify(this.buttonBorderRadius!);
    }
    return this.theme.buttonBorderRadius;
  }

  private getButtonBackgroundColor(): ResourceColor {
    if (this.buttonBackgroundColor) {
      return this.buttonBackgroundColor!.color;
    }
    return this.theme.buttonBackgroundColor;
  }

  private getButtonMinHeight(): Dimension {
    if (this.buttonMinHeight &&
    LengthMetricsUtils.getInstance().isNaturalNumber(this.buttonMinHeight!)) {
      return LengthMetricsUtils.getInstance().stringify(this.buttonMinHeight!);
    }
    const items = this.getItems();
    return items.hasHybrid ? this.theme.hybridButtonMinHeight : this.theme.buttonMinHeight;
  }
}

interface MultiplySegmentButtonV2Theme extends SegmentButtonV2ContentTheme {
  itemBackgroundColor: ResourceColor;
  itemSelectedBackgroundColor: ResourceColor;
  itemBorderRadius: Resource;
}

const multiplyCapsuleTheme: MultiplySegmentButtonV2Theme = {
  itemBorderRadius: $r('sys.float.segment_button_v2_multi_corner_radius'),
  itemBackgroundColor: $r('sys.color.segment_button_v2_multi_capsule_button_background'),
  itemSelectedBackgroundColor: $r('sys.color.comp_background_emphasize'),
  itemSpace: LengthMetrics.vp(1),
  itemFontColor: $r('sys.color.font_secondary'),
  itemSelectedFontColor: $r('sys.color.font_on_primary'),
  itemFontWeight: FontWeight.Medium,
  itemSelectedFontWeight: FontWeight.Medium,
  itemIconFillColor: $r('sys.color.icon_secondary'),
  itemSelectedIconFillColor: $r('sys.color.font_on_primary'),
  itemSymbolFontColor: $r('sys.color.font_secondary'),
  itemSelectedSymbolFontColor: $r('sys.color.font_on_primary'),
  itemFontSize: $r('sys.float.ohos_id_text_size_button2'),
  itemIconSize: 24,
  itemSymbolFontSize: 20,
  itemPadding: {
    top: LengthMetrics.resource($r('sys.float.padding_level2')),
    bottom: LengthMetrics.resource($r('sys.float.padding_level2')),
    start: LengthMetrics.resource($r('sys.float.padding_level4')),
    end: LengthMetrics.resource($r('sys.float.padding_level4')),
  },
  itemMinHeight: $r('sys.float.segment_button_v2_multi_singleline_height'),
  hybridItemMinHeight: $r('sys.float.segment_button_v2_multi_doubleline_height'),
  itemMaxFontScale: SMALLEST_MAX_FONT_SCALE,
  itemMaxFontScaleSmallest: SMALLEST_MAX_FONT_SCALE,
  itemMaxFontScaleLargest: LARGEST_MAX_FONT_SCALE,
  itemMinFontScale: SMALLEST_MIN_FONT_SCALE,
  itemMinFontScaleSmallest: SMALLEST_MIN_FONT_SCALE,
  itemMinFontScaleLargest: LARGEST_MIN_FONT_SCALE,
};

@ComponentV2
export struct MultiCapsuleSegmentButtonV2 {
  @Require @Param items: SegmentButtonV2Items;
  @Require @Param selectedIndexes: int[];
  @Event $selectedIndexes: OnSelectedIndexesChange;
  @Event onItemClicked?: Callback<int>;
  @Param itemMinFontScale?: double | Resource = undefined;
  @Param itemMaxFontScale?: double | Resource = undefined;
  @Param itemSpace?: LengthMetrics = undefined;
  @Param itemFontColor?: ColorMetrics = undefined;
  @Param itemSelectedFontColor?: ColorMetrics = undefined;
  @Param itemFontSize?: LengthMetrics = undefined;
  @Param itemSelectedFontSize?: LengthMetrics = undefined;
  @Param itemFontWeight?: FontWeight = undefined;
  @Param itemSelectedFontWeight?: FontWeight = undefined;
  @Param itemBorderRadius?: LengthMetrics = undefined;
  @Param itemBackgroundColor?: ColorMetrics = undefined;
  @Param itemBackgroundEffect?: BackgroundEffectOptions = undefined;
  @Param itemBackgroundBlurStyle?: BlurStyle = undefined;
  @Param itemBackgroundBlurStyleOptions?: BackgroundBlurStyleOptions = undefined;
  @Param itemSelectedBackgroundColor?: ColorMetrics = undefined;
  @Param itemIconSize?: SizeT<LengthMetrics> = undefined;
  @Param itemIconFillColor?: ColorMetrics = undefined;
  @Param itemSelectedIconFillColor?: ColorMetrics = undefined;
  @Param itemSymbolFontSize?: LengthMetrics = undefined;
  @Param itemSymbolFontColor?: ColorMetrics = undefined;
  @Param itemSelectedSymbolFontColor?: ColorMetrics = undefined;
  @Param itemMinHeight?: LengthMetrics = undefined;
  @Param itemPadding?: LocalizedPadding = undefined;
  @Param languageDirection?: Direction = undefined;
  private theme: MultiplySegmentButtonV2Theme = multiplyCapsuleTheme;
  private focusGroupId: string = GroupIdGenerator.getInstance().generate();

  build() {
    Flex({ alignItems: ItemAlign.Stretch, space: { main: this.getItemSpace() } }) {
      Repeat<SegmentButtonV2Item>(this.getItems())
        .each((repeatItem: RepeatItem<SegmentButtonV2Item>) => {
          Button({ type: ButtonType.Normal } as ButtonOptions) {
            SegmentButtonV2ItemContent({
              theme: this.theme,
              item: repeatItem.item,
              selected: this.isSelected(repeatItem),
              hasHybrid: this.getItems().hasHybrid,
              itemMinFontScale: this.itemMinFontScale,
              itemMaxFontScale: this.itemMaxFontScale,
              itemFontColor: this.itemFontColor,
              itemSelectedFontColor: this.itemSelectedFontColor,
              itemFontSize: this.itemFontSize,
              itemSelectedFontSize: this.itemSelectedFontSize,
              itemFontWeight: this.itemFontWeight,
              itemSelectedFontWeight: this.itemSelectedFontWeight,
              itemIconSize: this.itemIconSize,
              itemIconFillColor: this.itemIconFillColor,
              itemSelectedIconFillColor: this.itemSelectedIconFillColor,
              itemSymbolFontSize: this.itemSymbolFontSize,
              itemSymbolFontColor: this.itemSymbolFontColor,
              itemSelectedSymbolFontColor: this.itemSelectedSymbolFontColor,
              itemMinHeight: this.itemMinHeight,
              itemPadding: this.itemPadding,
              languageDirection: this.languageDirection,
            })
              .borderRadius(this.getItemButtonBorderRadius(repeatItem))
              .backgroundBlurStyle(this.getItemBackgroundBlurStyle(), this.getItemBackgroundBlurStyleOptions(),
                { disableSystemAdaptation: true })
              .direction(this.languageDirection)
          }
          .accessibilityGroup(true)
          .accessibilityChecked(this.isSelected(repeatItem))
          .accessibilityText(this.getItemAccessibilityText(repeatItem))
          .accessibilityDescription(this.getItemAccessibilityDescription(repeatItem))
          .accessibilityLevel(repeatItem.item.accessibilityLevel)
          .backgroundColor(this.getItemBackgroundColor(repeatItem))
          .backgroundEffect(this.itemBackgroundEffect, { disableSystemAdaptation: true })
          .borderRadius(this.getItemButtonBorderRadius(repeatItem))
          .constraintSize({ minHeight: this.getItemMinHeight() })
          .direction(this.languageDirection)
          .enabled(repeatItem.item.enabled)
          .focusScopePriority(this.focusGroupId, this.getFocusPriority(repeatItem))
          .layoutWeight(1)
          .padding(0)
          .onClick(() => {
            this.onItemClicked?.(repeatItem.index);
            let selection: int[];
            const items = this.getItems();
            const selectedIndexes: int[] = this.selectedIndexes ?? [];
            if (this.isSelected(repeatItem)) {
              selection = selectedIndexes.filter((index) => {
                if (index < 0 || index > items.length - 1) {
                  return false;
                }
                return index !== repeatItem.index;
              });
            } else {
              selection = selectedIndexes
                .filter((index) => index >= 0 && index <= items.length - 1)
                .concat([repeatItem.index]);
            }
            this.$selectedIndexes(selection);
          })
        })
        .key(generateUniqueKye(this.focusGroupId))
        .virtualScroll({ disableVirtualScroll: true })
    }
    .clip(false)
    .direction(this.languageDirection)
    .focusScopeId(this.focusGroupId, true)
  }

  private getFocusPriority(repeatItem: RepeatItem<SegmentButtonV2Item>): FocusPriority | undefined {
    const selectedIndexes: int[] = this.selectedIndexes ?? [];
    return minInt(...selectedIndexes) === repeatItem.index ? FocusPriority.PREVIOUS : FocusPriority.AUTO;
  }

  private getItems(): SegmentButtonV2Items {
    return this.items ?? EMPTY_ITEMS;
  }

  private getItemBackgroundBlurStyleOptions(): BackgroundBlurStyleOptions | undefined {
    if (this.itemBackgroundEffect) {
      return undefined;
    }
    return this.itemBackgroundBlurStyleOptions;
  }

  private getItemBackgroundBlurStyle(): BlurStyle | undefined {
    if (this.itemBackgroundEffect) {
      return undefined;
    }
    return this.itemBackgroundBlurStyle;
  }

  private getItemAccessibilityDescription(repeatItem: RepeatItem<SegmentButtonV2Item>): Resource | string | undefined {
    return repeatItem.item.accessibilityDescription;
  }

  private getItemAccessibilityText(repeatItem: RepeatItem<SegmentButtonV2Item>): Resource | string | undefined {
    return repeatItem.item.accessibilityText;
  }

  private getItemSpace(): LengthMetrics {
    if (
      this.itemSpace &&
        this.itemSpace!.unit !== LengthUnit.PERCENT &&
      LengthMetricsUtils.getInstance().isNaturalNumber(this.itemSpace!)
    ) {
      return this.itemSpace!;
    }
    return this.theme.itemSpace;
  }

  private getItemMinHeight(): Length | undefined {
    if (this.itemMinHeight && LengthMetricsUtils.getInstance().isNaturalNumber(this.itemMinHeight!)) {
      return LengthMetricsUtils.getInstance().stringify(this.itemMinHeight!);
    }
    return this.theme.itemMinHeight;
  }

  private getItemBackgroundColor(repeatItem: RepeatItem<SegmentButtonV2Item>): ResourceColor {
    if (this.isSelected(repeatItem)) {
      return this.itemSelectedBackgroundColor?.color ?? this.theme.itemSelectedBackgroundColor;
    }
    return this.itemBackgroundColor?.color ?? this.theme.itemBackgroundColor;
  }

  private isSelected(repeatItem: RepeatItem<SegmentButtonV2Item>): boolean {
    const selectedIndexes: int[] = this.selectedIndexes ?? [];
    return selectedIndexes.includes(repeatItem.index);
  }

  private getItemButtonBorderRadius(repeatItem: RepeatItem<SegmentButtonV2Item>): LocalizedBorderRadiuses {
    const items = this.getItems();
    const noneBorderRadius: LengthMetrics = LengthMetrics.vp(0);
    const borderRadiuses: LocalizedBorderRadiuses = {
      topStart: noneBorderRadius,
      bottomStart: noneBorderRadius,
      topEnd: noneBorderRadius,
      bottomEnd: noneBorderRadius,
    };
    let borderRadius: LengthMetrics = LengthMetrics.resource(this.theme.itemBorderRadius);
    if (this.itemBorderRadius && LengthMetricsUtils.getInstance().isNaturalNumber(this.itemBorderRadius!) ) {
      borderRadius = this.itemBorderRadius!;
    }
    if (repeatItem.index === 0) {
      borderRadiuses.topStart = borderRadius;
      borderRadiuses.bottomStart = borderRadius;
    }
    if (repeatItem.index === items.length - 1) {
      borderRadiuses.topEnd = borderRadius;
      borderRadiuses.bottomEnd = borderRadius;
    }
    return borderRadiuses;
  }
}

@ComponentV2
struct SegmentButtonV2ItemContent {
  @Require @Param hasHybrid: boolean;
  @Require @Param item: SegmentButtonV2Item;
  @Require @Param selected: boolean;
  @Require @Param theme: SegmentButtonV2ContentTheme;
  @Require @Param itemMinFontScale?: double | Resource = undefined;
  @Require @Param itemMaxFontScale?: double | Resource = undefined;
  @Require @Param itemFontColor?: ColorMetrics = undefined;
  @Require @Param itemSelectedFontColor?: ColorMetrics = undefined;
  @Require @Param itemFontSize?: LengthMetrics = undefined;
  @Require @Param itemSelectedFontSize?: LengthMetrics = undefined;
  @Require @Param itemFontWeight?: FontWeight = undefined;
  @Require @Param itemSelectedFontWeight?: FontWeight = undefined;
  @Require @Param itemIconSize?: SizeT<LengthMetrics> = undefined;
  @Require @Param itemIconFillColor?: ColorMetrics = undefined;
  @Require @Param itemSelectedIconFillColor?: ColorMetrics = undefined;
  @Require @Param itemSymbolFontSize?: LengthMetrics = undefined;
  @Require @Param itemSymbolFontColor?: ColorMetrics = undefined;
  @Require @Param itemSelectedSymbolFontColor?: ColorMetrics = undefined;
  @Require @Param itemMinHeight?: LengthMetrics = undefined;
  @Require @Param itemPadding?: LocalizedPadding = undefined;
  @Require @Param languageDirection?: Direction = undefined;

  build() {
    Column({ space: 2 } as ColumnOptions) {
      if (this.item.symbol || this.item.symbolModifier) {
        SymbolGlyph(this.item.symbol)
          .fontSize(this.getSymbolFontSize())
          .fontColor([this.getItemSymbolFillColor()])
          .direction(this.languageDirection)
          .attributeModifier(this.item.symbolModifier)
      } else if (this.item.icon) {
        Image(this.item.icon)
          .fillColor(this.getItemIconFillColor())
          .width(this.getItemIconWidth())
          .height(this.getItemIconHeight())
          .direction(this.languageDirection)
          .draggable(false)
          .attributeModifier(this.item.iconModifier)
      }

      if (this.item.text) {
        Text(this.item.text)
          .direction(this.languageDirection)
          .fontSize(this.getItemFontSize())
          .fontColor(this.getItemFontColor())
          .fontWeight(this.getItemFontWeight())
          .textOverflow({ overflow: TextOverflow.Ellipsis })
          .maxLines(1)
          .maxFontScale(this.getItemMaxFontScale())
          .minFontScale(this.getItemMinFontScale())
          .attributeModifier(this.item.textModifier)
      }
    }
    .constraintSize({ minHeight: this.getItemMinHeight(), minWidth: '100%' })
    .direction(this.languageDirection)
    .justifyContent(FlexAlign.Center)
    .padding(this.getItemPadding())
  }

  private getItemFontWeight(): string | int | FontWeight {
    if (this.selected) {
      return this.itemSelectedFontWeight ?? this.theme.itemSelectedFontWeight;
    }
    return this.itemFontWeight ?? this.theme.itemFontWeight;
  }

  private getItemSymbolFillColor(): ResourceColor {
    if (this.selected) {
      return this.itemSelectedSymbolFontColor?.color ?? this.theme.itemSelectedSymbolFontColor;
    }
    return this.itemSymbolFontColor?.color ?? this.theme.itemSymbolFontColor;
  }

  private getSymbolFontSize(): Dimension {
    if (this.itemSymbolFontSize &&
    LengthMetricsUtils.getInstance().isNaturalNumber(this.itemSymbolFontSize!) &&
      this.itemSymbolFontSize!.unit !== LengthUnit.PERCENT) {
      return LengthMetricsUtils.getInstance().stringify(this.itemSymbolFontSize!);
    }
    return this.theme.itemSymbolFontSize;
  }

  private getItemMaxFontScale(): double {
    if (typeof this.itemMaxFontScale === 'double') {
      return normalize(this.itemMaxFontScale as double, this.theme.itemMaxFontScaleSmallest,
        this.theme.itemMaxFontScaleLargest);
    }
    if (typeof this.itemMaxFontScale === 'object') {
      const itemMaxFontScale: double =
        parseNumericResource(this.getUIContext(), this.itemMaxFontScale as Resource) ?? SMALLEST_MAX_FONT_SCALE;
      return normalize(itemMaxFontScale, this.theme.itemMaxFontScaleSmallest, this.theme.itemMaxFontScaleLargest);
    }
    return SMALLEST_MAX_FONT_SCALE;
  }

  private getItemMinFontScale(): double {
    if (typeof this.itemMinFontScale === 'double') {
      return normalize(this.itemMinFontScale as double, this.theme.itemMinFontScaleSmallest,
        this.theme.itemMinFontScaleLargest);
    }
    if (typeof this.itemMinFontScale === 'object') {
      const itemMinFontScale: double =
        parseNumericResource(this.getUIContext(), this.itemMinFontScale as Resource) ?? SMALLEST_MIN_FONT_SCALE;
      return normalize(itemMinFontScale, this.theme.itemMinFontScaleSmallest, this.theme.itemMinFontScaleLargest);
    }
    return SMALLEST_MIN_FONT_SCALE;
  }

  private getItemPadding(): LocalizedPadding | Length | Padding {
    const itemPadding: LocalizedPadding = {
      top: this.theme.itemPadding.top,
      bottom: this.theme.itemPadding.bottom,
      start: this.theme.itemPadding.start,
      end: this.theme.itemPadding.end,
    };

    if (
      this.itemPadding?.top && LengthMetricsUtils.getInstance().isNaturalNumber(this.itemPadding!.top!)
    ) {
      itemPadding.top = this.itemPadding!.top!;
    }

    if (
      this.itemPadding?.bottom &&
      LengthMetricsUtils.getInstance().isNaturalNumber(this.itemPadding!.bottom!)
    ) {
      itemPadding.bottom = this.itemPadding!.bottom!;
    }

    if (
      this.itemPadding?.start &&
      LengthMetricsUtils.getInstance().isNaturalNumber(this.itemPadding!.start!)
    ) {
      itemPadding.start = this.itemPadding!.start!;
    }

    if (
      this.itemPadding?.end && LengthMetricsUtils.getInstance().isNaturalNumber(this.itemPadding!.end!)
    ) {
      itemPadding.end = this.itemPadding!.end!;
    }

    return itemPadding;
  }

  private getItemMinHeight(): Length | undefined {
    if (this.itemMinHeight && LengthMetricsUtils.getInstance().isNaturalNumber(this.itemMinHeight!)) {
      return LengthMetricsUtils.getInstance().stringify(this.itemMinHeight!);
    }
    return this.hasHybrid ? this.theme.hybridItemMinHeight : this.theme.itemMinHeight;
  }

  private getItemFontColor(): ResourceColor {
    if (this.selected) {
      if (this.itemSelectedFontColor) {
        return this.itemSelectedFontColor!.color;
      }
      return this.theme.itemSelectedFontColor;
    }
    if (this.itemFontColor) {
      return this.itemFontColor!.color;
    }
    return this.theme.itemFontColor;
  }

  private getItemFontSize(): Length {
    if (this.selected) {
      if (
        this.itemSelectedFontSize &&
        LengthMetricsUtils.getInstance().isNaturalNumber(this.itemSelectedFontSize!) &&
          this.itemSelectedFontSize!.unit !== LengthUnit.PERCENT
      ) {
        return LengthMetricsUtils.getInstance().stringify(this.itemSelectedFontSize!);
      }
      return this.theme.itemFontSize;
    }
    if (
      this.itemFontSize &&
      LengthMetricsUtils.getInstance().isNaturalNumber(this.itemFontSize!) &&
        this.itemFontSize!.unit !== LengthUnit.PERCENT
    ) {
      return LengthMetricsUtils.getInstance().stringify(this.itemFontSize!);
    }
    return this.theme.itemFontSize;
  }

  private getItemIconHeight(): Length {
    if (
      this.itemIconSize?.height &&
      LengthMetricsUtils.getInstance().isNaturalNumber(this.itemIconSize!.height!)
    ) {
      return LengthMetricsUtils.getInstance().stringify(this.itemIconSize!.height!);
    }
    return this.theme.itemIconSize;
  }

  private getItemIconWidth(): Length {
    if (
      this.itemIconSize?.width &&
      LengthMetricsUtils.getInstance().isNaturalNumber(this.itemIconSize!.width!)
    ) {
      return LengthMetricsUtils.getInstance().stringify(this.itemIconSize!.width!);
    }
    return this.theme.itemIconSize;
  }

  private getItemIconFillColor(): ResourceColor {
    if (this.selected) {
      if (this.itemSelectedIconFillColor) {
        return this.itemSelectedIconFillColor!.color;
      }
      return this.theme.itemSelectedIconFillColor;
    }
    if (this.itemIconFillColor) {
      return this.itemIconFillColor!.color;
    }
    return this.theme.itemIconFillColor;
  }
}

class LengthMetricsUtils {
  private static instance?: LengthMetricsUtils;

  private constructor() {
  }

  public static getInstance(): LengthMetricsUtils {
    if (!LengthMetricsUtils.instance) {
      LengthMetricsUtils.instance = new LengthMetricsUtils();
    }
    return LengthMetricsUtils.instance!;
  }

  public stringify(metrics: LengthMetrics): Dimension {
    switch (metrics.unit) {
      case LengthUnit.PX:
        return `${metrics.value}px`;
      case LengthUnit.VP:
        return `${metrics.value}vp`;
      case LengthUnit.FP:
        return `${metrics.value}fp`;
      case LengthUnit.PERCENT:
        return `${metrics.value}%`;
      case LengthUnit.LPX:
        return `${metrics.value}lpx`;
      default:
        return `0vp`;
    }
  }

  public isNaturalNumber(metrics: LengthMetrics): boolean {
    return metrics.value >= 0;
  }
}

function parseNumericResource(context: UIContext, resource: Resource): double | undefined {
  const resourceManager = context.getHostContext()?.resourceManager;
  if (!resourceManager) {
    return undefined;
  }
  try {
    return resourceManager.getDouble(resource.id);
  } catch (err) {
    // todo log err
    return undefined;
  }
}

function normalize(value: double, min: double, max: double): double {
  return Math.min(Math.max(value, min), max);
}

function normalizeInt(value: int, min: int, max: int): int {
  return minInt(maxInt(value, min), max);
}

function generateUniqueKye(groupId: string) {
  return (item: SegmentButtonV2Item, index: int): string => {
    let key: string = groupId;
    if (item.text) {
      if (typeof item.text === 'string') {
        key += item.text;
      } else {
        key += getResourceUniqueId(item.text as Resource);
      }
    }
    if (item.icon) {
      if (typeof item.icon === 'string') {
        key += item.icon;
      } else {
        key += getResourceUniqueId(item.icon as Resource);
      }
    }
    if (item.symbol) {
      key += getResourceUniqueId(item.symbol as Resource);
    }
    return key;
  }
}

function getResourceUniqueId(resource: Resource): string {
  if (resource.id !== -1) {
    return `${resource.id}`;
  } else {
    return JSON.stringify(resource);
  }
}

class GroupIdGenerator {
  private static instance: GroupIdGenerator | null = null;
  private id: int = 0;

  private constructor() {
  }

  public static getInstance(): GroupIdGenerator {
    if (!GroupIdGenerator.instance) {
      GroupIdGenerator.instance = new GroupIdGenerator();
    }
    return GroupIdGenerator.instance!;
  }

  public generate(): string {
    return util.generateRandomUUID() || `SegmentButton-${this.id++}`;
  }
}

function minInt(...elements: int[]): int {
  let min: int = elements[0];
  for (let i = 1; i < elements.length; ++i) {
    const element = elements[i];
    if (element < min) {
      min = element;
    }
  }
  return min;
}

function maxInt(...elements: int[]): int {
  let max: int = elements[0];
  for (let i = 1; i < elements.length; ++i) {
    const element = elements[i];
    if (element > max) {
      max = element;
    }
  }
  return max;
}
