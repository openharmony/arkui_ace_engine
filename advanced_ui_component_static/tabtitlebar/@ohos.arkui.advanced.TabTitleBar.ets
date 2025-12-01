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
  Column, Row, Component, Button, Text, CustomDialog, Array, $r, Flex, List, HoverEvent, ImageLoadResult,
  Canvas, BlendMode, Scroller, ForEach,AttributeModifier, GestureModifier, ListItem, BuilderParam,
  ResourceStr, UIGestureEvent, LongPressGestureHandler, PopupOptions,PopupStateChangeParam, CustomPopupOptions,
  CustomDialogController,ScrollOptions, ScrollAnimationOptions, SwiperController, ResourceColor, Area,
  RenderingContextSettings, CanvasRenderingContext2D, Builder, FontWeight, FlexAlign, KeyEvent,
  TouchEvent, ItemAlign, Stack, Alignment,EdgeEffect, Axis, BarState, BlendApplyType, Swiper, Curve,
  Color ,ButtonType, SymbolGlyph, BorderStyle, TouchType, KeyType, Placement ,GeometryInfo, Layoutable,
  ConstraintSizeOptions, focusControl, BorderOptions ,HitTestMode, SymbolEffect, ImageCompleteEvent, Resource,
  Image, Callback ,ImageFit, VerticalAlign, TextOverflow, TextAlign, ShadowStyle, BlurStyle,Margin, Padding,
  CommonMethod, ButtonOptions, ImageError, ImageOnCompleteCallback, ImageErrorCallback, SymbolGlyphModifier,
  ClassCastError, ClickEvent
} from "@ohos.arkui.component";
import { State, Observed, PropRef, StorageLink, StorageProp, Watch } from '@ohos.arkui.stateManagement';
import { Context, UIContext, MeasureUtils } from "@ohos.arkui.UIContext";
import { KeyCode } from '@ohos.multimodalInput.keyCode';
import resourceManager from '@ohos.resourceManager';
import { MeasureOptions } from '@ohos.measure';
import common from '@ohos.app.ability.common';
import window from '@ohos.window';
import hilog from '@ohos.hilog';

export class TabTitleBarMenuItem {
  value: ResourceStr = '';
  symbolStyle?: SymbolGlyphModifier;
  isEnabled?: boolean;
  action?: () => void;
  label?: ResourceStr;
  accessibilityText?: ResourceStr;
  accessibilityLevel?: string;
  accessibilityDescription?: ResourceStr;
}

export class TabTitleBarTabItem {
  title: ResourceStr = '';
  icon?: ResourceStr;
  symbolStyle?: SymbolGlyphModifier;
}
const TEXT_EDITABLE_DIALOG = '18.3fp';
const IMAGE_SIZE = '64vp';
const MAX_DIALOG = '256vp';
const MIN_DIALOG = '216vp';
const RESOURCE_TYPE_SYMBOL = 40000;
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
      )
    } else {
      event.clearGestures();
    }
  }
}

@Component
export struct TabTitleBar {
  tabItems: Array<TabTitleBarTabItem> = new Array<TabTitleBarTabItem>();
  menuItems: Array<TabTitleBarMenuItem> = new Array<TabTitleBarMenuItem>();
  @BuilderParam swiperContent: () => void = this.emptyBuilder;
  @State tabWidth: number = 0;
  @State currentIndex: number = 0;
  @State swiperCurrentIndex: int = 0;
  @State fontSize: number = 1;

  static readonly totalHeight: number = 56;
  static readonly correctionOffset: number = -40.0;
  static readonly gradientMaskWidth: number = 24;
  private static instanceCount: number = 0;

  private menuSectionWidth: number = 0;
  private tabOffsets: Array<number> = new Array<number>();
  private imageWidths: Array<number> = new Array<number>();

  private scroller: Scroller = new Scroller();
  private swiperController: SwiperController = new SwiperController();
  private settings: RenderingContextSettings = new RenderingContextSettings(true);
  private leftContext2D: CanvasRenderingContext2D = new CanvasRenderingContext2D(this.settings);
  private rightContext2D: CanvasRenderingContext2D = new CanvasRenderingContext2D(this.settings);

  @Builder
  GradientMask(context2D: CanvasRenderingContext2D, x0: number, y0: number, x1: number, y1: number) {
    Column() {
      Canvas(context2D)
        .width(TabTitleBar.gradientMaskWidth)
        .height(TabTitleBar.totalHeight)
        .onReady(() => {
          let grad = context2D.createLinearGradient(x0, y0, x1, y1);
          grad.addColorStop(0.0, '#ffffffff');
          grad.addColorStop(1, '#00ffffff');
          context2D.fillStyle = grad;
          context2D.fillRect(0, 0, TabTitleBar.gradientMaskWidth, TabTitleBar.totalHeight);
        } as () => void)
    }
    .blendMode(BlendMode.DST_OUT, BlendApplyType.FAST)
    .width(TabTitleBar.gradientMaskWidth)
    .height(TabTitleBar.totalHeight)
  }

  @Builder
  emptyBuilder() {
  }

  aboutToAppear() {
    if (!this.swiperContent) {
      this.swiperContent = this.emptyBuilder;
    }
    this.tabItems.forEach((_elem) => {
      this.imageWidths.push(0);
    })
    this.loadOffsets();
  }

  loadOffsets() {
    this.tabOffsets.length = 0;

    let tabOffset: number = 0;
    this.tabOffsets.push(tabOffset);
    tabOffset += TabContentItem.marginFirst;

    this.tabItems.forEach((tabItem: TabTitleBarTabItem, index: number) => {
      if (tabItem.icon !== undefined || tabItem.symbolStyle !== undefined) {
        if (Math.abs(this.imageWidths[index as int]) > TabContentItem.imageHotZoneWidth) {
          tabOffset += this.imageWidths[index as int];
        } else {
          tabOffset += TabContentItem.imageHotZoneWidth;
        }
      } else {
        tabOffset += TabContentItem.paddingLeft;
        let uiContextMeasure: MeasureUtils = this.getUIContext().getMeasureUtils();
        tabOffset += this.getUIContext().px2vp(uiContextMeasure.measureText({
          textContent: tabItem.title.toString(),
          fontSize: 18,
          fontWeight: FontWeight.Medium,
        } as MeasureOptions));
        tabOffset += TabContentItem.paddingRight;
      }
      this.tabOffsets.push(tabOffset);
    })
  }

  build() {
    Column() {
      Flex({
        justifyContent: FlexAlign.SpaceBetween,
        alignItems: ItemAlign.Stretch
      }) {
        Stack({ alignContent: Alignment.End }) {
          Stack({ alignContent: Alignment.Start }) { 1

            Column() {
              List({ initialIndex: 0, scroller: this.scroller, space: 0 }) {
                ForEach(this.tabItems, (tabItem: TabTitleBarTabItem, index: int) => {
                  ListItem() {
                    TabContentItem({
                      item: tabItem,
                      index: index,
                      maxIndex: this.tabItems.length - 1,
                      currentIndex: this.currentIndex,
                      onCustomClick: (itemIndex: number) => {
                        this.currentIndex = itemIndex;
                      },
                      onImageComplete: (width: number) => {
                        this.imageWidths[index.toInt()] = width;
                        this.loadOffsets();
                      }
                    })
                  }
                }, (item: TabTitleBarTabItem, index: int) => {
                  return JSON.stringify(item.title + '-' + index)
                })
              }
              .width('100%')
              .height(TabTitleBar.totalHeight)
              .constraintSize({ maxWidth: this.tabWidth })
              .edgeEffect(EdgeEffect.Spring)
              .listDirection(Axis.Horizontal)
              .scrollBar(BarState.Off)
            }
            this.GradientMask(this.leftContext2D, 0, TabTitleBar.totalHeight / 2,
              TabTitleBar.gradientMaskWidth, TabTitleBar.totalHeight / 2);
          }
          this.GradientMask(this.rightContext2D, TabTitleBar.gradientMaskWidth,
            TabTitleBar.totalHeight / 2, 0, TabTitleBar.totalHeight / 2);
        }
        .blendMode(BlendMode.SRC_OVER, BlendApplyType.OFFSCREEN)

        if (this.menuItems !== undefined && this.menuItems.length > 0) {
          CollapsibleMenuSection({
            menuItems: this.menuItems,
            index: 1 + TabTitleBar.instanceCount++,
          })
            .height(TabTitleBar.totalHeight)
            .onAreaChange((_oldValue: Area, newValue: Area) => {
              this.menuSectionWidth = Number(newValue.width as number)
            })

        }
      }
      .backgroundColor($r('sys.color.ohos_id_color_background'))
      .margin({ right: $r('sys.float.ohos_id_max_padding_end') } as Margin)
      .onAreaChange((_oldValue: Area, newValue: Area) => {
        this.tabWidth = Number(newValue.width as number) - this.menuSectionWidth;
      })

      Column() {
        Swiper(this.swiperController as SwiperController) {
          this.swiperContent();
        }
        .index(this.currentIndex as int)
        .itemSpace(0)
        .indicator(false)
        .width('100%')
        .height('100%')
        .curve(Curve.Friction)
        .onChange((index: int) => {
          if(index < this.tabOffsets.length) {
            const offset = this.tabOffsets[index] + TabTitleBar.correctionOffset;
            this.currentIndex = index;
            this.scroller.scrollTo({
              xOffset: offset > 0 ? offset : 0,
              yOffset: 0,
              animation: {
                duration: 300,
                curve: Curve.EaseInOut
              } as ScrollAnimationOptions
            } as ScrollOptions)
          }
        } as Callback<int>)
        .onAppear(() => {
          this.scroller.scrollToIndex(Double.toInt(this.currentIndex));
          this.scroller.scrollBy(TabTitleBar.correctionOffset, 0);
        })
      }
    }
  }
}

@Component
export struct CollapsibleMenuSection {

  menuItems: Array<TabTitleBarMenuItem> = new Array<TabTitleBarMenuItem>();
  index: number = 0;
  PUBLIC_MORE: Resource= $r('sys.symbol.dot_grid_2x2');
  item: TabTitleBarMenuItem = {
    value: this.PUBLIC_MORE,
    symbolStyle: new SymbolGlyphModifier(this.PUBLIC_MORE) as SymbolGlyphModifier,
    label: $r('sys.string.ohos_toolbar_more'),
  } as TabTitleBarMenuItem;
  minFontSize: number = 1.75;
  isFollowingSystemFontScale: boolean = false;
  maxFontScale: number = 1;
  systemFontScale?: number = 1;

  static readonly maxCountOfVisibleItems: number = 1;
  private static readonly focusPadding: number = 4;
  private static readonly marginsNum: number = 2;
  private firstFocusableIndex: number = -1;

  @State isPopupShown: boolean = false;
  @State isMoreIconOnFocus: boolean = false;
  @State isMoreIconOnHover: boolean = false;
  @State isMoreIconOnClick: boolean = false;
  @PropRef @Watch('onFontSizeUpdated') fontSize: number = 1;

  dialogController: CustomDialogController | null = new CustomDialogController({
    builder: TabTitleBarDialog({
      cancel: () => {
      } as () => void,
      confirm: () => {
      } as () => void,
      tabTitleDialog: this.item,
      tabTitleBarDialog: this.item.label ? this.item.label : '',
      fontSize: this.fontSize,
    }),
    maskColor: Color.Transparent,
    isModal: true,
    customStyle: true,
  });

  @Observed
  @State buttonGestureModifier: ButtonGestureModifier = new ButtonGestureModifier(this.dialogController);

  getMoreIconFgColor(): ResourceColor {
    return this.isMoreIconOnClick
      ? $r('sys.color.ohos_id_color_titlebar_icon_pressed')
      : $r('sys.color.ohos_id_color_titlebar_icon');
  }

  getMoreIconBgColor(): ResourceColor {
    if (this.isMoreIconOnClick) {
      return $r('sys.color.ohos_id_color_click_effect');
    } else if (this.isMoreIconOnHover) {
      return $r('sys.color.ohos_id_color_hover');
    } else {
      return Color.Transparent;
    }
  }

  aboutToAppear() {
    try {
      let uiContent: UIContext = this.getUIContext();
      this.isFollowingSystemFontScale = uiContent.isFollowingSystemFontScale();
      this.maxFontScale = uiContent.getMaxFontScale();
    } catch (exception) {
      let code: int | undefined = (exception as ClassCastError)?.code;
      let message: string | undefined = (exception as ClassCastError)?.message;
      hilog.error(0x3900, 'tabTitleBar', `Faild to decideFontScale,cause, code: ${code}, message: ${message}`);

    }
    this.menuItems.forEach((item, index) => {
      if (item.isEnabled && this.firstFocusableIndex === -1 &&
        index > CollapsibleMenuSection.maxCountOfVisibleItems - 2) {
        this.firstFocusableIndex = this.index * 1000 + index + 1
      }
    })
    this.fontSize = this.decideFontScale();
  }

  decideFontScale(): number {
    let uiContent: UIContext = this.getUIContext();
    if (uiContent.getHostContext()) {
      this.systemFontScale = (uiContent.getHostContext() as common.UIAbilityContext)?.config?.fontSizeScale ?? 1;
    }
    if (!this.isFollowingSystemFontScale) {
      return 1;
    }
    return Math.min(Number(this.systemFontScale), Number(this.maxFontScale));
  }

  onFontSizeUpdated(flag: String): void {
    this.buttonGestureModifier.fontSize = this.fontSize;
  }

  build() {
    Column() {
      Row() {
        if (this.menuItems.length <= CollapsibleMenuSection.maxCountOfVisibleItems) {
          ForEach(this.menuItems, (item: TabTitleBarMenuItem, index: int) => {
            ImageMenuItem({ item: item, index: this.index * 1000 + index + 1 });
          }, (item: TabTitleBarMenuItem, index: int) => {
            return JSON.stringify(item.value + '' + index)
          })
        } else {
          ForEach(this.menuItems.slice(0, CollapsibleMenuSection.maxCountOfVisibleItems.toInt() - 1),
            (item: TabTitleBarMenuItem, index: int) => {
              ImageMenuItem({ item: item, index: this.index * 1000 + index + 1 });
            }, (item: TabTitleBarMenuItem, index: int) => {
              return JSON.stringify(item.value + '' + index)
            })
          Button({ type: ButtonType.Normal, stateEffect: true } as ButtonOptions) {
            SymbolGlyph(this.PUBLIC_MORE)
              .fontSize(TabContentItem.symbolSize)
              .draggable(false)
              .fontColor([$r('sys.color.icon_primary')])
              .focusable(true)
          }
          .accessibilityText($r('sys.string.ohos_toolbar_more'))
          .width(ImageMenuItem.imageHotZoneWidth)
          .height(ImageMenuItem.imageHotZoneWidth)
          .borderRadius(ImageMenuItem.buttonBorderRadius)
          .foregroundColor(this.getMoreIconFgColor())
          .backgroundColor(this.getMoreIconBgColor())
          .stateStyles({
            focused: (instance: CommonMethod) => {
              instance.border({
                radius: $r('sys.float.ohos_id_corner_radius_clicked'),
                width: ImageMenuItem.focusBorderWidth,
                color: $r('sys.color.ohos_id_color_focused_outline'),
                style: BorderStyle.Solid
              })
            },
            normal: (instance: CommonMethod) => {
              instance.border({
                radius: $r('sys.float.ohos_id_corner_radius_clicked'),
                width: 0
              })
            }
          })
          .onFocus(() => {
            this.isMoreIconOnFocus = true;
          })
          .onBlur(() => {
            this.isMoreIconOnFocus = false;
          })
          .onHover((isOn: boolean, event: HoverEvent) => {
            this.isMoreIconOnHover = isOn;
          })
          .onKeyEvent((event: KeyEvent): boolean =>  {
            if (event.keyCode !== KeyCode.KEYCODE_ENTER && event.keyCode !== KeyCode.KEYCODE_SPACE) {
              return false;
            }
            if (event.type === KeyType.Down) {
              this.isMoreIconOnClick = true;
            }
            if (event.type === KeyType.Up) {
              this.isMoreIconOnClick = false;
            }
            return true;
          } as Callback<KeyEvent, boolean>)
          .onTouch((event: TouchEvent) => {
            if (event.type === TouchType.Down) {
              this.isMoreIconOnClick = true;
            }
            if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
              this.isMoreIconOnClick = false;
              if (this.fontSize >= this.minFontSize) {
                this.dialogController?.close();
              }
            }
          })
          .onClick((event: ClickEvent) => {
            this.isPopupShown = true;
          })
          .gestureModifier(this.buttonGestureModifier)
          .bindPopup(this.isPopupShown as boolean, {
            builder: this.popupBuilder,
            placement: Placement.Bottom,
            popupColor: Color.White,
            enableArrow: false,
            onStateChange: (e: PopupStateChangeParam) => {
              this.isPopupShown = e.isVisible;
              if (!e.isVisible) {
                this.isMoreIconOnClick = false;
              }
            }
          } as CustomPopupOptions)
        }
      }
    }
    .justifyContent(FlexAlign.Center)
  }

  onPlaceChildren(selfLayoutInfo: GeometryInfo, children: Layoutable[], constraint: ConstraintSizeOptions): void {
    children.forEach((child) => {
      child.layout({ x: 0, y: 0 });
    })
    this.fontSize = this.decideFontScale();
  }

  @Builder
  popupBuilder() {
    Column() {
      ForEach(this.menuItems.slice(CollapsibleMenuSection.maxCountOfVisibleItems.toInt() - 1, this.menuItems.length),
        (item: TabTitleBarMenuItem, index: int) => {
          ImageMenuItem({
            item: item as TabTitleBarMenuItem, index: this.index * 1000 +
            CollapsibleMenuSection.maxCountOfVisibleItems + index
          });
        }, (item: TabTitleBarMenuItem, index: int) => {
          return JSON.stringify(item.value + '' + index)
        })
    }
    .width(ImageMenuItem.imageHotZoneWidth + CollapsibleMenuSection.focusPadding * CollapsibleMenuSection.marginsNum)
    .margin({ top: CollapsibleMenuSection.focusPadding, bottom: CollapsibleMenuSection.focusPadding } as Margin)
    .onAppear(() => {
      focusControl.requestFocus(ImageMenuItem.focusablePrefix + this.firstFocusableIndex);
    })
  }
}

@Component
struct TabContentItem {
  item: TabTitleBarTabItem = { title: '' } as TabTitleBarTabItem;
  index: number = 0;
  maxIndex: number = 0;
  onCustomClick?: (index: number) => void;
  onImageComplete?: (width: number) => void;

  @PropRef currentIndex: number;

  @State isOnFocus: boolean = false;
  @State isOnHover: boolean = false;
  @State isOnClick: boolean = false;
  @State tabWidth: number = 0;

  @State imageWidth: number = 24;
  @State imageHeight: number = 24;
  static readonly imageSize: number = 24;
  static readonly symbolSize: string = '24vp';
  static readonly imageHotZoneWidth: number = 48;
  static readonly imageMagnificationFactor: number = 1.4;
  static readonly buttonBorderRadius: number = 8;
  static readonly focusBorderWidth: number = 2;
  static readonly paddingLeft: number = 8;
  static readonly paddingRight: number = 8;
  static readonly marginFirst: number = 16;

  getBgColor(): ResourceColor {
    if (this.isOnClick) {
      return $r('sys.color.ohos_id_color_click_effect');
    } else if (this.isOnHover) {
      return $r('sys.color.ohos_id_color_hover');
    } else {
      return Color.Transparent;
    }
  }

  getBorderAttr(): BorderOptions {
    if (this.isOnFocus) {
      return {
        radius: $r('sys.float.ohos_id_corner_radius_clicked'),
        width: TabContentItem.focusBorderWidth,
        color: $r('sys.color.ohos_id_color_focused_outline'),
        style: BorderStyle.Solid
      };
    }
    return { width: 0 }
  }

  getImageScaleFactor(): number {
    return this.index === this.currentIndex ? TabContentItem.imageMagnificationFactor : 1;
  }

  getImageLayoutWidth(): number {
    return TabContentItem.imageSize / Math.max(this.imageHeight, 1.0) * this.imageWidth;
  }

  private completeCallback: ImageOnCompleteCallback | undefined = (info?: ImageCompleteEvent) => {
    let onImageCompleteValue: number =
      this.getUIContext().px2vp(info?.componentWidth as int) + TabContentItem.paddingLeft + TabContentItem.paddingRight;
    this.onImageComplete?.(onImageCompleteValue);
  }

  private onErrorCallback: ImageErrorCallback | undefined = (event: ImageError) => {
    if (!this.onImageComplete) {
      return;
    }
    let onImageComplete: number =
      this.getUIContext().px2vp(event.componentWidth as int) + TabContentItem.paddingLeft + TabContentItem.paddingRight
    this.onImageComplete?.(onImageComplete);
  }

  private toStringFormat(resource: ResourceStr | undefined): string | undefined {
    if (typeof resource === 'string') {
      return resource as string;
    } else if (typeof resource === 'undefined') {
      return '';
    } else {
      let resourceString: undefined | string = '';
      try {
        resourceString = resourceManager.getSysResourceManager().getStringSync((resource as Resource).id as Long);
      } catch (exception) {
        let code: int | undefined = (exception as ClassCastError)?.code;
        let message: string | undefined = (exception as ClassCastError)?.message;
        hilog.error(0x3900, 'Ace', `Faild to TabTitleBar toStringFormat,code: ${code},message:${message}`);
      }
      return resourceString;
    }
  }

  build() {
    Stack() {
      Row() {
        Column() {
          if (this.item.icon === undefined && this.item.symbolStyle === undefined) {
            Text(this.item.title)
              .fontSize(this.index === this.currentIndex
                ? $r('sys.float.ohos_id_text_size_headline7')
                : $r('sys.float.ohos_id_text_size_headline9'))
              .fontColor(this.index === this.currentIndex
                ? $r('sys.color.ohos_id_color_titlebar_text')
                : $r('sys.color.ohos_id_color_titlebar_text_off'))
              .fontWeight(FontWeight.Medium)
              .focusable(true)
              .animation({ duration: 300 })
              .padding({
                top: this.index === this.currentIndex ? 6 : 10,
                left: TabContentItem.paddingLeft,
                bottom: 2,
                right: TabContentItem.paddingRight
              } as Padding)
              .onFocus(() => {
                this.isOnFocus = true;
              })
              .onBlur(() => {
                this.isOnFocus = false;
              })
              .onHover((isOn: boolean, event: HoverEvent) => {
                this.isOnHover = isOn;
              })
              .onKeyEvent((event: KeyEvent): boolean => {
                if (event.keyCode !== KeyCode.KEYCODE_ENTER && event.keyCode !== KeyCode.KEYCODE_SPACE) {
                  return false;
                }
                if (event.type === KeyType.Down) {
                  this.isOnClick = true;
                }
                if (event.type === KeyType.Up) {
                  this.isOnClick = false;
                }
                return true;
              } as Callback<KeyEvent, boolean>)
              .onTouch((event: TouchEvent) => {
                if (event.type === TouchType.Down) {
                  this.isOnClick = true;
                }
                if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
                  this.isOnClick = false;
                }
              })
              .onClick(() => {
                if (typeof this.onCustomClick === 'function') {
                  this.onCustomClick?.(this.index);
                }
              } as () => void)
              .accessibilitySelected(this.index === this.currentIndex)
          } else {
            Row() {
              if (this.item.symbolStyle) {
                SymbolGlyph()
                  .fontColor([$r('sys.color.icon_primary')])
                  .attributeModifier(this.item.symbolStyle)
                  .fontSize(TabContentItem.symbolSize)
                  .width(this.getImageLayoutWidth())
                  .height(TabContentItem.imageSize)
                  .accessibilityText(this.toStringFormat(this.item.title))
                  .scale({
                    x: this.getImageScaleFactor(),
                    y: this.getImageScaleFactor()
                  })
                  .animation({ duration: 300 })
                  .hitTestBehavior(HitTestMode.None)
                  .focusable(true)
                  .symbolEffect(new SymbolEffect(), false)
              } else {
                if (Util.isSymbolResource(this.item.icon)) {
                  SymbolGlyph(this.item.icon as Resource)
                    .fontColor([$r('sys.color.icon_primary')])
                    .fontSize(TabContentItem.symbolSize)
                    .width(this.getImageLayoutWidth())
                    .height(TabContentItem.imageSize)
                    .accessibilityText(this.toStringFormat(this.item.title))
                    .scale({
                      x: this.getImageScaleFactor(),
                      y: this.getImageScaleFactor()
                    })
                    .animation({ duration: 300 })
                    .hitTestBehavior(HitTestMode.None)
                    .focusable(true)
                } else {
                  Image((this.item?.icon ?? '') as ResourceStr)
                    .alt(this.item.title)
                    .width(this.getImageLayoutWidth())
                    .height(TabContentItem.imageSize)
                    .objectFit(ImageFit.Fill)
                    .accessibilityText(this.toStringFormat(this.item.title))
                    .scale({
                      x: this.getImageScaleFactor(),
                      y: this.getImageScaleFactor()
                    })
                    .animation({ duration: 300 })
                    .hitTestBehavior(HitTestMode.None)
                    .focusable(true)
                    .onComplete(this.completeCallback)
                    .onError(this.onErrorCallback)
                }
              }
            }
            .width(this.getImageLayoutWidth() * this.getImageScaleFactor() +
            TabContentItem.paddingLeft + TabContentItem.paddingRight)
            .constraintSize({
              minWidth: TabContentItem.imageHotZoneWidth,
              minHeight: TabContentItem.imageHotZoneWidth
            })
            .animation({ duration: 300 })
            .justifyContent(FlexAlign.Center)
            .onFocus(() => {
              this.isOnFocus = true;
            } as () => void)
            .onBlur(() => {
              this.isOnFocus = false;
            } as () => void)
            .onHover((isOn: boolean, event: HoverEvent) => {
              this.isOnHover = isOn;
            })
            .onKeyEvent((event: KeyEvent): boolean => {
              if (event.keyCode !== KeyCode.KEYCODE_ENTER && event.keyCode !== KeyCode.KEYCODE_SPACE) {
                return false;
              }
              if (event.type === KeyType.Down) {
                this.isOnClick = true;
              }
              if (event.type === KeyType.Up) {
                this.isOnClick = false;
              }
              return true;
            } as Callback<KeyEvent, boolean>)
            .onTouch((event: TouchEvent) => {
              if (event.type === TouchType.Down) {
                this.isOnClick = true;
              }
              if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
                this.isOnClick = false;
              }
            })
            .onClick(() => {
              if (typeof this.onCustomClick === 'function') {
                this.onCustomClick?.(this.index as number);
              }
            } as () => void)
            .accessibilitySelected(this.index === this.currentIndex)
          }
        }
        .justifyContent(FlexAlign.Center)
      }
      .height(TabTitleBar.totalHeight)
      .alignItems(VerticalAlign.Center)
      .justifyContent(FlexAlign.Center)
      .borderRadius(TabContentItem.buttonBorderRadius)
      .backgroundColor(this.getBgColor())
      .onAreaChange((_oldValue: Area, newValue: Area) => {
        this.tabWidth = newValue.width as number;
      })

      if (this.isOnFocus && this.tabWidth > 0) {
        Row()
          .width(this.tabWidth)
          .height(TabTitleBar.totalHeight)
          .hitTestBehavior(HitTestMode.None)
          .borderRadius(TabContentItem.buttonBorderRadius)
          .stateStyles({
            focused: (instance: CommonMethod) => {
              instance.border(this.getBorderAttr())
            },
            normal: (instance: CommonMethod) => {
              instance.border({
                radius: $r('sys.float.ohos_id_corner_radius_clicked'),
                width: 0
              })
            }
          })
      }
    }
    .margin({
      left: this.index === 0 ? TabContentItem.marginFirst : 0,
      right: this.index === this.maxIndex ? 12 : 0
    } as Margin)
  }
}

@Component
struct ImageMenuItem {
  item: TabTitleBarMenuItem = {
    value: ''
  } as TabTitleBarMenuItem;
  index: number = 0;

  PUBLIC_MORE: Resource= $r('sys.symbol.dot_grid_2x2');
  static readonly imageSize: number = 24;
  static readonly imageHotZoneWidth: number = 48;
  static readonly buttonBorderRadius: number = 8;
  static readonly focusBorderWidth: number = 2;
  static readonly disabledImageOpacity: number = 0.4;
  static readonly focusablePrefix: string = "Id-TabTitleBar-ImageMenuItem-";

  @State isOnFocus: boolean = false;
  @State isOnHover: boolean = false;
  @State isOnClick: boolean = false;

  getFgColor(): ResourceColor {
    return this.isOnClick
      ? $r('sys.color.ohos_id_color_titlebar_icon_pressed')
      : $r('sys.color.ohos_id_color_titlebar_icon');
  }

  getBgColor(): ResourceColor {
    if (this.isOnClick) {
      return $r('sys.color.ohos_id_color_click_effect');
    } else if (this.isOnHover) {
      return $r('sys.color.ohos_id_color_hover');
    } else {
      return Color.Transparent;
    }
  }

  private toStringFormat(resource: ResourceStr | undefined): string {
    if (typeof resource === 'string') {
      return resource as string;
    } else if (typeof resource === 'undefined') {
      return '' as string;
    } else {
      let str = (this.getUIContext().getHostContext() as common.UIAbilityContext)?.resourceManager?.
      getStringSync((this.item.accessibilityText as Resource).id as Long)
      return str as string;
    }
  }

  private getAccessibilityReadText(): string | undefined {
    if (this.item.value === this.PUBLIC_MORE) {
      try {
        return resourceManager.getSysResourceManager().getStringByNameSync('ohos_toolbar_more');
      } catch (exception) {
        let code: int | undefined = (exception as ClassCastError)?.code;
        let message: string | undefined = (exception as ClassCastError)?.message;
        hilog.error(0x3900, 'Ace', `Faild to TabTitleBar toStringFormat,code: ${code},message:${message}`);
      }
    } else if (this.item.accessibilityText) {
      if (typeof this.item.accessibilityText === 'string') {
        return this.item.accessibilityText as string;
      } else if (typeof this.item.accessibilityText === 'undefined') {
        return '' as string;
      } else {
        let str = (this.getUIContext().getHostContext() as common.UIAbilityContext)?.resourceManager?.
        getStringSync((this.item.accessibilityText as Resource).id as Long)
        return str as string;
      }
    } else if (this.item.label) {
      if (typeof this.item.label === 'string') {
        return this.item.label as string;
      } else if (typeof this.item.label === 'undefined') {
        return '' as string;
      } else {
        let str = (this.getUIContext().getHostContext() as common.UIAbilityContext)?.resourceManager?.
        getStringSync((this.item.label as Resource).id as Long)
        return str as string;
      }
    }
    return ' ';
  }

  build() {
    Button({ type: ButtonType.Normal, stateEffect: this.item.isEnabled } as ButtonOptions) {
      if (this.item.symbolStyle) {
        SymbolGlyph()
          .fontColor([$r('sys.color.font_primary')])
          .attributeModifier(this.item.symbolStyle)
          .fontSize(TabContentItem.symbolSize)
          .draggable(false)
          .focusable(this.item?.isEnabled)
          .key(ImageMenuItem.focusablePrefix + this.index)
          .symbolEffect(new SymbolEffect(), false);
      } else {
        if (Util.isSymbolResource(this.item.value)) {
          SymbolGlyph(this.item.value as Resource)
            .fontColor([$r('sys.color.font_primary')])
            .fontSize(TabContentItem.symbolSize)
            .draggable(false)
            .focusable(this.item?.isEnabled)
            .key(ImageMenuItem.focusablePrefix + this.index);
        } else {
          Image(this.item.value)
            .width(ImageMenuItem.imageSize)
            .height(ImageMenuItem.imageSize)
            .focusable(this.item.isEnabled)
            .key(ImageMenuItem.focusablePrefix + this.index)
            .draggable(false);
        }
      }
    }
    .accessibilityText(this.getAccessibilityReadText())
    .accessibilityLevel(this.item?.accessibilityLevel ?? 'auto')
    .accessibilityDescription(this.toStringFormat(this.item?.accessibilityDescription))
    .width(ImageMenuItem.imageHotZoneWidth)
    .height(ImageMenuItem.imageHotZoneWidth)
    .borderRadius(ImageMenuItem.buttonBorderRadius)
    .foregroundColor(this.getFgColor())
    .backgroundColor(this.getBgColor())
    .enabled(this.item.isEnabled ? this.item.isEnabled : false)
    .stateStyles({
      focused: (instance: CommonMethod) => {
        instance.border({
          radius: $r('sys.float.ohos_id_corner_radius_clicked'),
          width: ImageMenuItem.focusBorderWidth,
          color: $r('sys.color.ohos_id_color_focused_outline'),
          style: BorderStyle.Solid
        })
      },
      normal: (instance: CommonMethod) => {
        instance.border({
          radius: $r('sys.float.ohos_id_corner_radius_clicked'),
          width: 0
        })
      }
    })
    .onFocus(() => {
      if (!this.item.isEnabled) {
        return;
      }
      this.isOnFocus = true;
    })
    .onBlur(() => {
      this.isOnFocus = false;
    } as () => void)
    .onHover((isOn: boolean, event: HoverEvent) => {
      if (this.item.isEnabled) {
        this.isOnHover = isOn;
      }
    })
    .onKeyEvent((event: KeyEvent): boolean => {
      if (!this.item.isEnabled) {
        return false;
      }
      if (event.keyCode !== KeyCode.KEYCODE_ENTER && event.keyCode !== KeyCode.KEYCODE_SPACE) {
        return false;
      }
      if (event.type === KeyType.Down) {
        this.isOnClick = true;
      }
      if (event.type === KeyType.Up) {
        this.isOnClick = false;
      }
      return true;
    } as Callback<KeyEvent, boolean>)
    .onTouch((event: TouchEvent) => {
      if (!this.item.isEnabled) {
        return;
      }
      if (event.type === TouchType.Down) {
        this.isOnClick = true;
      }
      if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
        this.isOnClick = false;
      }
    })
    .onClick(() => {
      if (this.item.isEnabled && typeof this.item?.action === 'function') {
        (this.item?.action as () => void)();
      }
    } as () => void)
  }
}

/**
 *  TabTitleBarDialog
 */
@CustomDialog
struct TabTitleBarDialog {
  tabTitleDialog: TabTitleBarMenuItem = { value: '' } as TabTitleBarMenuItem;
  callbackId: number | undefined = undefined;
  tabTitleBarDialog?: ResourceStr = '';
  mainWindowStage: window.Window | undefined = undefined;
  controller?: CustomDialogController;
  minFontSize: number = 1.75;
  maxFontSize: number = 3.2;
  screenWidth: number = 640;
  verticalScreenLines: int = 6;
  horizontalsScreenLines: int = 1;
  @State fontSize: number = 1;
  @State maxLines: int = 1;
  @StorageProp('windowStandardHeight') windowStandardHeight: number = 0;
  cancel: () => void = () => {
  };
  confirm: () => void = () => {
  };

  build() {
    if (this.tabTitleBarDialog) {
      Column() {
        if (this.tabTitleDialog.symbolStyle) {
          SymbolGlyph()
            .fontColor([$r('sys.color.font_primary')])
            .attributeModifier(this.tabTitleDialog.symbolStyle)
            .fontSize(IMAGE_SIZE)
            .draggable(false)
            .focusable(this.tabTitleDialog?.isEnabled)
            .margin({
              top: $r('sys.float.padding_level24'),
              bottom: $r('sys.float.padding_level8'),
            } as Margin)
            .symbolEffect(new SymbolEffect(), false)
        } else if (this.tabTitleDialog.value) {
          if (Util.isSymbolResource(this.tabTitleDialog.value)) {
            SymbolGlyph(this.tabTitleDialog.value as Resource)
              .fontColor([$r('sys.color.font_primary')])
              .fontSize(IMAGE_SIZE)
              .draggable(false)
              .focusable(this.tabTitleDialog?.isEnabled)
              .margin({
                top: $r('sys.float.padding_level24'),
                bottom: $r('sys.float.padding_level8'),
              } as Margin)
          } else {
            Image(this.tabTitleDialog.value)
              .width(IMAGE_SIZE)
              .height(IMAGE_SIZE)
              .margin({
                top: $r('sys.float.padding_level24'),
                bottom: $r('sys.float.padding_level8'),
              } as Margin)
              .fillColor($r('sys.color.icon_primary'))
          }
        }
        Column() {
          Text(this.tabTitleBarDialog)
            .fontSize(TEXT_EDITABLE_DIALOG)
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
      .width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG)
      .constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG })
      .backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK, undefined, { disableSystemAdaptation: true })
      .shadow(ShadowStyle.OUTER_DEFAULT_LG)
      .borderRadius($r('sys.float.corner_radius_level10'))
    } else {
      Column() {
        if (this.tabTitleDialog.symbolStyle) {
          SymbolGlyph()
            .fontColor([$r('sys.color.font_primary')])
            .attributeModifier(this.tabTitleDialog.symbolStyle)
            .fontSize(IMAGE_SIZE)
            .draggable(false)
            .focusable(this.tabTitleDialog?.isEnabled)
            .symbolEffect(new SymbolEffect(), false)
        } else if (this.tabTitleDialog.value) {
          if (Util.isSymbolResource(this.tabTitleDialog.value)) {
            SymbolGlyph(this.tabTitleDialog.value as Resource)
              .fontColor([$r('sys.color.font_primary')])
              .fontSize(IMAGE_SIZE)
              .draggable(false)
              .focusable(this.tabTitleDialog?.isEnabled)
              .margin({
                top: $r('sys.float.padding_level24'),
                bottom: $r('sys.float.padding_level8'),
              } as Margin)
          } else {
            Image(this.tabTitleDialog.value)
              .width(IMAGE_SIZE)
              .height(IMAGE_SIZE)
              .fillColor($r('sys.color.icon_primary'))
          }
        }
      }
      .width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG)
      .constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG })
      .backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK, undefined, { disableSystemAdaptation: true })
      .shadow(ShadowStyle.OUTER_DEFAULT_LG)
      .borderRadius($r('sys.float.corner_radius_level10'))
      .justifyContent(FlexAlign.Center)
    }
  }

  aboutToAppear(): void {
    try {
      let context = this.getUIContext().getHostContext() as common.UIAbilityContext;
      this.mainWindowStage = context.windowStage.getMainWindowSync();
      let properties: window.WindowProperties = this.mainWindowStage?.getWindowProperties() as window.WindowProperties;
      let rect = properties.windowRect;
      if (this.getUIContext().px2vp(rect.height) > this.screenWidth) {
        this.maxLines = this.verticalScreenLines;
      } else {
        this.maxLines = this.horizontalsScreenLines;
      }
    } catch (exception) {
      let code: int | undefined = (exception as ClassCastError)?.code;
      let message: string | undefined = (exception as ClassCastError)?.message;
      hilog.error(0x3900, 'tabTitleBar', `Faild to getMainWindowSync,cause, code: ${code}, message: ${message}`);
    }
  }
}

class Util {
  public static isSymbolResource(resourceStr: ResourceStr | undefined | null): boolean {
    if (!Util.isResourceType(resourceStr)) {
      return false;
    }
    let resource = resourceStr as Resource;
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
