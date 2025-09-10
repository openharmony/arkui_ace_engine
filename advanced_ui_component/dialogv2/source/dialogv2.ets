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

import { BusinessError, Callback } from '@ohos.base';
import display from '@ohos.display';
import hilog from '@ohos.hilog';
import measure from '@ohos.measure';
import resourceManager from '@ohos.resourceManager';
import { Theme } from '@ohos.arkui.theme';
import { ColorMetrics, LengthMetrics, LengthUnit } from '@ohos.arkui.node';
import common from '@ohos.app.ability.common';
import accessibility from '@ohos.accessibility';
import { KeyCode } from '@ohos.multimodalInput.keyCode';
import { i18n } from '@kit.LocalizationKit';

const TITLE_MAX_LINES: number = 2;
const HORIZON_BUTTON_MAX_COUNT: number = 2;
const VERTICAL_BUTTON_MAX_COUNT: number = 4;
const BUTTON_LAYOUT_WEIGHT: number = 1;
const CHECKBOX_CONTAINER_HEIGHT: number = 48;
const CONTENT_MAX_LINES: number = 2;
const LOADING_PROGRESS_WIDTH: number = 40;
const LOADING_PROGRESS_HEIGHT: number = 40;
const LOADING_MAX_LINES: number = 10;
const LOADING_MAX_LINES_BIG_FONT: number = 4;
const LOADING_TEXT_LAYOUT_WEIGHT: number = 1;
const LOADING_TEXT_MARGIN_LEFT: number = 12;
const LOADING_MIN_HEIGHT: number = 48;
const LIST_MIN_HEIGHT: number = 48;
const CHECKBOX_CONTAINER_LENGTH: number = 20;
const TEXT_MIN_HEIGHT: number = 48;
const DEFAULT_IMAGE_SIZE: number = 64;
const MIN_CONTENT_HEIGHT: number = 100;
const MAX_CONTENT_HEIGHT: number = 30000;
const KEYCODE_UP: number = 2012;
const KEYCODE_DOWN: number = 2013;
const IGNORE_KEY_EVENT_TYPE: number = 1;
const FIRST_ITEM_INDEX: number = 0;
const VERSION_TWELVE: number = 50000012;
const BUTTON_MIN_FONT_SIZE = 9;
const MAX_FONT_SCALE: number = 2;
// 'sys.float.alert_container_max_width'
const MAX_DIALOG_WIDTH: number = getNumberByResourceId(125831042, 400);
// 'sys.float.alert_right_padding_horizontal'
const BUTTON_HORIZONTAL_MARGIN: number = getNumberByResourceId(125831054, 16);
// 'sys.float.padding_level8'
const BUTTON_HORIZONTAL_PADDING: number = getNumberByResourceId(125830927, 16);
// 'sys.float.padding_level4'
const CHECK_BOX_MARGIN_END: number = getNumberByResourceId(125830923, 8);
// 'sys.float.alert_button_horizontal_space'
const BUTTON_HORIZONTAL_SPACE: number = getNumberByResourceId(125831051, 8);
// 'sys.float.Body_L'
const BODY_L: number = getNumberByResourceId(125830970, 16);
// 'sys.float.Body_M'
const BODY_M: number = getNumberByResourceId(125830971, 14);
// 'sys.float.Body_S'
const BODY_S: number = getNumberByResourceId(125830972, 12);
// 'sys.float.Title_S'
const TITLE_S: number = getNumberByResourceId(125830966, 20);
// 'sys.float.Subtitle_S'
const SUBTITLE_S: number = getNumberByResourceId(125830969, 14);
// 'sys.float.padding_level8'
const PADDING_LEVEL_8: number = getNumberByResourceId(125830927, 16);
// 'sys.float.dialog_divider_show'
const DIALOG_DIVIDER_SHOW: number = getNumberByResourceId(125831202, 1, true);
// 'sys.float.alert_button_style'
const ALERT_BUTTON_STYLE: number = getNumberByResourceId(125831085, 2, true);
// 'sys.float.alert_title_alignment'
const ALERT_TITLE_ALIGNMENT: number = getEnumNumberByResourceId(125831126, 1);
// 'sys.float.dialog_content_font_size'
const CONTENT_FONT_SIZE = getNumberByResourceId(125835677, BODY_L);
const SCROLL_BAR_OFFSET: number = 20;
const SELECT_DIALOG_SCROLL_BAR_OFFSET: number = 4;

export type AdvancedDialogV2OnCheckedChange = (checked: boolean) => void;

export type AdvancedDialogV2ButtonAction = () => void;

@ObservedV2
export class AdvancedDialogV2Button {
  @Trace
  public content: ResourceStr = '';
  @Trace
  public action?: AdvancedDialogV2ButtonAction;
  @Trace
  public background?: ColorMetrics;
  @Trace
  public fontColor?: ColorMetrics;
  @Trace
  public buttonStyle?: ButtonStyleMode;
  @Trace
  public role?: ButtonRole;
  @Trace
  public defaultFocus?: boolean;
  @Trace
  public enabled?: boolean;
  constructor(options: AdvancedDialogV2ButtonOptions) {
    this.content = options.content;
    this.action = options.action;
    this.background = options.background;
    this.fontColor = options.fontColor;
    this.buttonStyle = options.buttonStyle;
    this.role = options.role;
    this.defaultFocus = options.defaultFocus;
    this.enabled = options.enabled;
  };
}

export declare interface AdvancedDialogV2ButtonOptions {
  content: ResourceStr;
  action?: AdvancedDialogV2ButtonAction;
  background?: ColorMetrics;
  fontColor?: ColorMetrics;
  buttonStyle?: ButtonStyleMode;
  role?: ButtonRole;
  defaultFocus?: boolean;
  enabled?: boolean;
}

@ComponentV2
export struct TipsDialogV2 {
  @Require @Param imageRes: ResourceStr | PixelMap;
  @Param imageSize?: SizeOptions = { width: DEFAULT_IMAGE_SIZE, height: DEFAULT_IMAGE_SIZE };
  @Param imageBorderColor?: ColorMetrics = undefined;
  @Param imageBorderWidth?: LengthMetrics = undefined;
  @Param title?: ResourceStr | null = null;
  @Param content?: ResourceStr | null = null;
  @Param onCheckedChange?: AdvancedDialogV2OnCheckedChange = undefined;
  @Param checkTips?: ResourceStr | null = null;
  @Param checked?: boolean = false;
  @Local checkedInner?: boolean = false;

  @Monitor('checked')
  checkedChangeMonitor(monitor: IMonitor) {
    this.checkedInner = monitor.value<boolean>('checked')?.now;
  }

  @Computed
  get buttons(): AdvancedDialogV2Button[] | undefined {
    if (!this.primaryButton && !this.secondaryButton) {
      return undefined;
    }
    let buttons: AdvancedDialogV2Button[] = [];
    if (this.primaryButton) {
      buttons.push(this.primaryButton);
    }
    if (this.secondaryButton) {
      buttons.push(this.secondaryButton);
    }
    return buttons;
  }

  @Param primaryButton?: AdvancedDialogV2Button | null = null;
  @Param secondaryButton?: AdvancedDialogV2Button | null = null;
  private marginOffset: number = 0 - PADDING_LEVEL_8;
  // the controller of content area scroll
  private contentScroller: Scroller = new Scroller();
  @Local fontColorWithTheme: ResourceColor = $r('sys.color.font_primary');
  // themeColorMode?: ThemeColorMode = ThemeColorMode.SYSTEM;
  @Provider() fontSizeScale: number = 1;
  @Local minContentHeight: number = 160;
  private imageIndex: number = 0;
  private textIndex: number = 1;
  private checkBoxIndex: number = 2;
  private appMaxFontScale: number = 3.2;

  onWillApplyTheme(theme: Theme): void {
    this.fontColorWithTheme = theme.colors.fontPrimary;
  }

  build() {
    CustomDialogContentComponent({
      contentBuilder: () => {
        this.contentBuilder();
      },
      buttons: this.buttons,
      minContentHeight: this.minContentHeight!!,
    }).constraintSize({ maxHeight: '100%' });
  }

  @Builder
  contentBuilder(): void {
    TipsDialogContentLayout({
      title: this.title,
      content: this.content,
      checkTips: this.checkTips,
      minContentHeight: this.minContentHeight!!,
    }) {
      ForEach([this.imageIndex, this.textIndex, this.checkBoxIndex], (index: number) => {
        if (index === this.imageIndex) {
          this.imagePart();
        } else if (index === this.textIndex) {
          Column() {
            this.textPart();
          }
          .padding({ top: $r('sys.float.padding_level8') })
        } else {
          this.checkBoxPart();
        }
      });
    }
  }

  @Builder
  checkBoxPart(): void {
    Row() {
      if (this.checkTips !== null && this.checkTips !== undefined) {
        Checkbox({ name: '', group: 'checkboxGroup' }).select(this.checkedInner)
          .onChange((checked: boolean) => {
            this.checkedInner = checked;
            this.onCheckedChange?.(checked);
          })
          .margin({ start: LengthMetrics.vp(0), end: LengthMetrics.vp(CHECK_BOX_MARGIN_END) })
        Text(this.checkTips)
          .fontSize(`${CONTENT_FONT_SIZE}fp`)
          .fontWeight(FontWeight.Regular)
          .fontColor(this.fontColorWithTheme)
          .maxLines(CONTENT_MAX_LINES)
          .layoutWeight(1)
          .focusable(false)
          .textOverflow({ overflow: TextOverflow.Ellipsis })
      }
    }
    .accessibilityGroup(true)
    .accessibilityText(getCheckTipsAccessibilityText(this.checkTips, this.checkedInner))
    .accessibilityDescription(this.checkedInner ? $r('sys.string.advanced_dialog_accessibility_cancel_checked_desc') :
    $r('sys.string.slider_accessibility_unselectedDesc'))
    .onClick(() => {
      this.checkedInner = !this.checkedInner;
      try {
        let hostContext: Context | undefined = this.getUIContext()?.getHostContext();
        let resourceManager: resourceManager.ResourceManager | undefined = hostContext?.resourceManager;
        let bundleName: string = (hostContext as common.UIAbilityContext)?.abilityInfo?.bundleName ??
          (hostContext as common.UIExtensionContext)?.extensionAbilityInfo?.bundleName;
        let eventInfo: accessibility.EventInfo = ({
          type: 'announceForAccessibility',
          bundleName: bundleName,
          triggerAction: 'common',
          textAnnouncedForAccessibility: this.checkedInner ?
            resourceManager?.getStringSync(125833934) :
            resourceManager?.getStringSync(125833935)
        });
        accessibility.sendAccessibilityEvent(eventInfo);
      } catch (exception) {
        let code: number = (exception as BusinessError).code;
        let message: string = (exception as BusinessError).message;
        hilog.error(0x3900, 'Ace', `Faild to send event, cause, code: ${code}, message: ${message}`);
      }
    })
    .padding({ top: 8, bottom: 8 })
    .constraintSize({ minHeight: CHECKBOX_CONTAINER_HEIGHT })
    .width('100%')
  }

  @Builder
  imagePart(): void {
    Column() {
      Image(this.imageRes)
        .objectFit(ImageFit.Contain)
        .borderRadius($r('sys.float.corner_radius_level6'))
        .constraintSize({
          maxWidth: this.imageSize?.width ?? DEFAULT_IMAGE_SIZE,
          maxHeight: this.imageSize?.height ?? DEFAULT_IMAGE_SIZE
        })
        .outline({
          width: `${lengthMetricsToPX(this.imageBorderWidth)}px`,
          radius: `${lengthMetricsToPX(LengthMetrics.resource($r('sys.float.corner_radius_level6'))) +
          lengthMetricsToPX(this.imageBorderWidth)}px`,
          color: this.imageBorderColor?.color
        })
    }
    .width('100%')
  }

  @Builder
  textPart(): void {
    Scroll(this.contentScroller) {
      Column() {
        if (this.title !== null) {
          Row() {
            Text(this.title)
              .fontSize(`${TITLE_S}fp`)
              .maxFontScale(Math.min(this.appMaxFontScale, MAX_FONT_SCALE))
              .fontWeight(FontWeight.Bold)
              .fontColor(this.fontColorWithTheme)
              .textAlign(TextAlign.Center)
              .maxLines(CONTENT_MAX_LINES)
              .textOverflow({ overflow: TextOverflow.Ellipsis })
              .width('100%')
          }
          .padding({ bottom: $r('sys.float.padding_level8') })
        }
        if (this.content !== null) {
          Row() {
            Text(this.content)
              .focusable(true)
              .defaultFocus(!(this.primaryButton || this.secondaryButton))
              .focusBox({
                strokeWidth: LengthMetrics.px(0)
              })
              .fontSize(this.getContentFontSize())
              .fontWeight(FontWeight.Medium)
              .fontColor(this.fontColorWithTheme)
              .textAlign(TextAlign.Center)
              .width('100%')
              .onKeyEvent((event: KeyEvent) => {
                if (event) {
                  resolveKeyEvent(event, this.contentScroller);
                }
              })
          }
        }
      }
      .margin({ end: LengthMetrics.vp(SCROLL_BAR_OFFSET) })
      .width(`calc(100% - ${SCROLL_BAR_OFFSET}vp)`)
    }
    .nestedScroll({ scrollForward: NestedScrollMode.PARALLEL, scrollBackward: NestedScrollMode.PARALLEL })
    .margin({ end: LengthMetrics.vp(0 - SCROLL_BAR_OFFSET) })
  }

  aboutToAppear(): void {
    let uiContext: UIContext = this.getUIContext();
    this.appMaxFontScale = uiContext.getMaxFontScale();
    this.checkedInner = this.checked;
  }

  private getContentFontSize(): Length {
    return CONTENT_FONT_SIZE + 'fp';
  }
}

@ComponentV2
struct TipsDialogContentLayout {
  @Builder
  doNothingBuilder() {
  };

  @Param title?: ResourceStr | null = null;
  @Param content?: ResourceStr | null = null;
  @Param checkTips?: ResourceStr | null = null;
  @Param minContentHeight: number = 0;
  @Event $minContentHeight?: (val: number) => void = undefined;
  @BuilderParam dialogBuilder: () => void = this.doNothingBuilder;
  private imageIndex: number = 0;
  private textIndex: number = 1;
  private checkBoxIndex: number = 2;
  private childrenSize: number = 3;

  onPlaceChildren(selfLayoutInfo: GeometryInfo, children: Array<Layoutable>,
    constraint: ConstraintSizeOptions) {
    let currentX: number = 0;
    let currentY: number = 0;
    for (let index = 0; index < children.length; index++) {
      let child = children[index];
      child.layout({ x: currentX, y: currentY });
      currentY += child.measureResult.height;
    }
  }

  onMeasureSize(selfLayoutInfo: GeometryInfo, children: Array<Measurable>,
    constraint: ConstraintSizeOptions): SizeResult {
    let sizeResult: SizeResult = { width: Number(constraint.maxWidth), height: 0 };
    if (children.length < this.childrenSize) {
      return sizeResult;
    }
    let height: number = 0;
    let checkBoxHeight: number = 0;
    if (this.checkTips !== null && this.checkTips !== undefined) {
      let checkboxChild: Measurable = children[this.checkBoxIndex];
      let checkboxConstraint: ConstraintSizeOptions = {
        maxWidth: constraint.maxWidth,
        minHeight: CHECKBOX_CONTAINER_HEIGHT,
        maxHeight: constraint.maxHeight
      }
      let checkBoxMeasureResult: MeasureResult = checkboxChild.measure(checkboxConstraint);
      checkBoxHeight = checkBoxMeasureResult.height;
      height += checkBoxHeight;
    }

    let imageChild: Measurable = children[this.imageIndex];
    let textMinHeight: number = 0;
    if (this.title !== null || this.content !== null) {
      textMinHeight = TEXT_MIN_HEIGHT + PADDING_LEVEL_8;
    }
    let imageMaxHeight = Number(constraint.maxHeight) - checkBoxHeight - textMinHeight;
    let imageConstraint: ConstraintSizeOptions = {
      maxWidth: constraint.maxWidth,
      maxHeight: imageMaxHeight
    }
    let imageMeasureResult: MeasureResult = imageChild.measure(imageConstraint);
    height += imageMeasureResult.height;

    if (this.title !== null || this.content !== null) {
      let textChild: Measurable = children[this.textIndex];
      let contentMaxHeight: number = Number(constraint.maxHeight) - imageMeasureResult.height - checkBoxHeight;
      let contentConstraint: ConstraintSizeOptions =
        {
          maxWidth: constraint.maxWidth,
          maxHeight: Math.max(contentMaxHeight, TEXT_MIN_HEIGHT)
        };
      let contentMeasureResult: MeasureResult = textChild.measure(contentConstraint);
      height += contentMeasureResult.height;
    }
    sizeResult.height = height;
    this.$minContentHeight?.(Math.max(checkBoxHeight + imageMeasureResult.height + textMinHeight, MIN_CONTENT_HEIGHT));
    return sizeResult;
  }

  build() {
    this.dialogBuilder();
  }
}

@ComponentV2
export struct SelectDialogV2 {
  @Require @Param title: ResourceStr = '';
  @Param content?: ResourceStr = '';
  @Param confirm?: AdvancedDialogV2Button | null = null;
  @Require @Param radioContent: SheetInfo[] = [];
  @Param selectedIndex?: number = -1;
  @Local selectedIndexInner?: number = -1;

  @Monitor('selectedIndex')
  selectedIndexMonitor(monitor: IMonitor) {
    this.selectedIndexInner = monitor.value<number>('selectedIndex')?.now;
  }

  @Local isFocus: boolean = false;
  @Local currentFocusIndex?: number = -1;
  @Local radioHeight: number = 0;
  @Local itemHeight: number = 0;
  @BuilderParam contentBuilder: () => void = this.buildContent;
  @Local fontColorWithTheme: ResourceColor = $r('sys.color.font_primary');
  @Local dividerColorWithTheme: ResourceColor = $r('sys.color.comp_divider');
  // the controller of content list
  private contentScroller: Scroller = new Scroller();
  @Provider() fontSizeScale: number = 1;
  @Local minContentHeight: number = MIN_CONTENT_HEIGHT;

  @Computed
  get buttons(): AdvancedDialogV2Button[] | undefined {
    let buttons: AdvancedDialogV2Button[] = [];
    if (this.confirm) {
      buttons.push(this.confirm);
    }
    return buttons
  }

  @Computed
  get contentPadding(): Padding | undefined {
    if (!this.title && !this.confirm) {
      return {
        top: $r('sys.float.padding_level12'),
        bottom: $r('sys.float.padding_level12')
      }
    }

    if (!this.title) {
      return {
        top: $r('sys.float.padding_level12')
      }
    } else if (!this.confirm) {
      return {
        bottom: $r('sys.float.padding_level12')
      }
    }
    return {
      left: $r('sys.float.padding_level0'),
      right: $r('sys.float.padding_level0')
    }
  }

  @Styles
  paddingContentStyle() {
    .padding({
      left: $r('sys.float.padding_level12'),
      right: $r('sys.float.padding_level12'),
      bottom: $r('sys.float.padding_level4')
    })
  }

  @Styles
  paddingStyle() {
    .padding({
      left: $r('sys.float.padding_level6'),
      right: $r('sys.float.padding_level6')
    })
  }

  @Builder
  buildContent(): void {
    Scroll(this.contentScroller) {
      Column() {
        if (this.content) {
          Row() {
            Text(this.content)
              .fontSize(`${BODY_M}fp`)
              .fontWeight(FontWeight.Regular)
              .fontColor(this.fontColorWithTheme)
              .textOverflow({ overflow: TextOverflow.Ellipsis })
          }.paddingContentStyle().width('100%')
        }
        List() {
          ForEach(this.radioContent, (item: SheetInfo, index: number) => {
            ListItem() {
              Column() {
                Button() {
                  Row() {
                    Text(item.title)
                      .fontSize(`${BODY_L}fp`)
                      .fontWeight(FontWeight.Medium)
                      .fontColor(this.fontColorWithTheme)
                      .layoutWeight(1)
                      .direction(i18n.isRTL(i18n.System.getSystemLanguage()) ? Direction.Rtl : Direction.Ltr)
                    Radio({ value: 'item.title', group: 'radioGroup' })
                      .size({ width: CHECKBOX_CONTAINER_LENGTH, height: CHECKBOX_CONTAINER_LENGTH })
                      .checked(this.selectedIndexInner === index)
                      .hitTestBehavior(HitTestMode.None)
                      .id(String(index))
                      .focusable(false)
                      .accessibilityLevel('no')
                      .visibility(this.selectedIndex === index ? Visibility.Visible : Visibility.Hidden)
                      .radioStyle({ uncheckedBorderColor: Color.Transparent })
                      .onFocus(() => {
                        this.isFocus = true;
                        this.currentFocusIndex = index;
                        if (index === FIRST_ITEM_INDEX) {
                          this.contentScroller.scrollEdge(Edge.Top);
                        } else if (index === this.radioContent.length - 1) {
                          this.contentScroller.scrollEdge(Edge.Bottom);
                        }
                      })
                      .onSizeChange((oldValue: SizeOptions, newValue: SizeOptions) => {
                        this.radioHeight = Number(newValue.height)
                      })
                  }.constraintSize({ minHeight: LIST_MIN_HEIGHT }).clip(false)
                  .padding({ top: $r('sys.float.padding_level4'), bottom: $r('sys.float.padding_level4') })
                }
                .type(ButtonType.Normal)
                .borderRadius($r('sys.float.corner_radius_level8'))
                .buttonStyle(ButtonStyleMode.TEXTUAL)
                .paddingStyle()

                if (index < this.radioContent.length - 1) {
                  Divider().color(this.dividerColorWithTheme).paddingStyle();
                }
              }
              .borderRadius($r('sys.float.corner_radius_level8'))
              .focusBox({
                margin: { value: -2, unit: LengthUnit.VP }
              })
              .accessibilityText(getAccessibilityText(item.title, this.selectedIndexInner === index))
              .onClick(() => {
                this.selectedIndexInner = index;
                item.action && item.action();
                closeDialog(this.getDialogController(), 'onClick');
              })
            }
            .paddingStyle()
            .onSizeChange((oldValue: SizeOptions, newValue: SizeOptions) => {
              this.itemHeight = Number(newValue.height)
            })
          })
        }.width('100%').clip(false)
        .onFocus(() => {
          if (!this.contentScroller.isAtEnd()) {
            this.contentScroller.scrollEdge(Edge.Top);
            focusControl.requestFocus(String(FIRST_ITEM_INDEX));
          }
        })
        .defaultFocus(this.buttons?.length === 0 ? true : false)
      }
    }.scrollBar(BarState.Auto)
    .nestedScroll({ scrollForward: NestedScrollMode.PARALLEL, scrollBackward: NestedScrollMode.PARALLEL })
    .onDidScroll((xOffset: number, yOffset: number) => {
      let scrollHeight: number = (this.itemHeight - this.radioHeight) / 2
      if (this.isFocus) {
        if (this.currentFocusIndex === this.radioContent.length - 1) {
          this.contentScroller.scrollEdge(Edge.Bottom);
          this.currentFocusIndex = -1;
        } else if (this.currentFocusIndex === FIRST_ITEM_INDEX) {
          this.contentScroller.scrollEdge(Edge.Top);
          this.currentFocusIndex = -1;
        } else {
          if (yOffset > 0) {
            this.contentScroller.scrollBy(0, scrollHeight)
          } else if (yOffset < 0) {
            this.contentScroller.scrollBy(0, 0 - scrollHeight)
          }
        }
        this.isFocus = false;
      }
    })
    .margin({ end: LengthMetrics.vp(SELECT_DIALOG_SCROLL_BAR_OFFSET) })
  }

  build() {
    CustomDialogContentComponent({
      primaryTitle: this.title,
      contentBuilder: () => {
        this.contentBuilder();
      },
      buttons: this.buttons,
      contentAreaPadding: this.contentPadding,
      minContentHeight: this.minContentHeight!!,
    }).constraintSize({ maxHeight: '100%' });
  }

  onWillApplyTheme(theme: Theme): void {
    this.fontColorWithTheme = theme.colors.fontPrimary;
    this.dividerColorWithTheme = theme.colors.compDivider;
  }

  aboutToAppear(): void {
    this.selectedIndexInner = this.selectedIndex;
  }
}

@ComponentV2
struct ConfirmDialogContentLayout {
  private textIndex: number = 0;
  private checkboxIndex: number = 1;
  @Param minContentHeight: number = 0;
  @Event $minContentHeight?: (val: number) => void = undefined;

  @Builder
  doNothingBuilder() {
  };

  @BuilderParam dialogBuilder: () => void = this.doNothingBuilder;

  onPlaceChildren(selfLayoutInfo: GeometryInfo, children: Array<Layoutable>,
    constraint: ConstraintSizeOptions) {
    let currentX: number = 0;
    let currentY: number = 0;
    for (let index = 0; index < children.length; index++) {
      let child = children[index];
      child.layout({ x: currentX, y: currentY });
      currentY += child.measureResult.height;
    }
  }

  onMeasureSize(selfLayoutInfo: GeometryInfo, children: Array<Measurable>,
    constraint: ConstraintSizeOptions): SizeResult {
    let sizeResult: SizeResult = { width: Number(constraint.maxWidth), height: 0 };
    let childrenSize: number = 2;
    if (children.length < childrenSize) {
      return sizeResult;
    }
    let height: number = 0;
    let checkboxChild: Measurable = children[this.checkboxIndex];
    let checkboxConstraint: ConstraintSizeOptions = {
      maxWidth: constraint.maxWidth,
      minHeight: CHECKBOX_CONTAINER_HEIGHT,
      maxHeight: constraint.maxHeight
    }
    let checkBoxMeasureResult: MeasureResult = checkboxChild.measure(checkboxConstraint);
    height += checkBoxMeasureResult.height;

    let textChild: Measurable = children[this.textIndex];
    let textConstraint: ConstraintSizeOptions = {
      maxWidth: constraint.maxWidth,
      maxHeight: Number(constraint.maxHeight) - height
    }
    let textMeasureResult: MeasureResult = textChild.measure(textConstraint);
    height += textMeasureResult.height;
    sizeResult.height = height;
    this.$minContentHeight?.(Math.max(checkBoxMeasureResult.height + TEXT_MIN_HEIGHT, MIN_CONTENT_HEIGHT));
    return sizeResult;
  }

  build() {
    this.dialogBuilder();
  }
}

@ComponentV2
export struct ConfirmDialogV2 {
  @Require @Param title: ResourceStr = '';
  @Param content?: ResourceStr = '';
  @Param checkTips?: ResourceStr = '';
  @Param checked?: boolean = false;
  @Local checkedInner?: boolean = this.checked;

  @Monitor('checked')
  checkedMonitor(monitor: IMonitor) {
    this.checkedInner = monitor.value<boolean>('checked')?.now;
  }

  @Param primaryButton?: AdvancedDialogV2Button = new AdvancedDialogV2Button({ content: '' });
  @Param secondaryButton?: AdvancedDialogV2Button = new AdvancedDialogV2Button({ content: '' });
  @Local fontColorWithTheme: ResourceColor = $r('sys.color.font_primary');
  @Param onCheckedChange?: AdvancedDialogV2OnCheckedChange = undefined;
  private contentScroller: Scroller = new Scroller();
  private marginOffset: number = 0 - PADDING_LEVEL_8;
  @Provider() fontSizeScale: number = 1;
  @Local minContentHeight: number = MIN_CONTENT_HEIGHT;
  private textIndex: number = 0;
  private checkboxIndex: number = 1;

  @Computed
  get buttons(): AdvancedDialogV2Button[] | undefined {
    if (!this.primaryButton && !this.secondaryButton) {
      return undefined;
    }
    let buttons: AdvancedDialogV2Button[] = [];
    if (this.primaryButton) {
      buttons.push(this.primaryButton);
    }
    if (this.secondaryButton) {
      buttons.push(this.secondaryButton);
    }
    return buttons;
  }

  @Builder
  textBuilder(): void {
    Column() {
      Scroll(this.contentScroller) {
        Column() {
          Text(this.content)
            .focusable(true)
            .defaultFocus(!(this.primaryButton?.content || this.secondaryButton?.content))
            .focusBox({
              strokeWidth: LengthMetrics.px(0)
            })
            .fontSize(`${CONTENT_FONT_SIZE}fp`)
            .fontWeight(FontWeight.Medium)
            .fontColor(this.fontColorWithTheme)
            .textAlign(TextAlign.Center)
            .onKeyEvent((event: KeyEvent) => {
              if (event) {
                resolveKeyEvent(event, this.contentScroller);
              }
            })
            .width('100%')
        }
        .margin({ end: LengthMetrics.vp(SCROLL_BAR_OFFSET) })
        .width(`calc(100% - ${SCROLL_BAR_OFFSET}vp)`)
      }
      .nestedScroll({ scrollForward: NestedScrollMode.PARALLEL, scrollBackward: NestedScrollMode.PARALLEL })
      .margin({ end: LengthMetrics.vp(0 - SCROLL_BAR_OFFSET) })
    }
  }

  @Builder
  checkBoxBuilder(): void {
    Row() {
      Checkbox({ name: '', group: 'checkboxGroup' })
        .select(this.checkedInner)
        .onChange((checked: boolean) => {
          this.checkedInner = checked;
          if (this.onCheckedChange) {
            this.onCheckedChange(this.checkedInner);
          }
        })
        .hitTestBehavior(HitTestMode.Block)
        .margin({ start: LengthMetrics.vp(0), end: LengthMetrics.vp(CHECK_BOX_MARGIN_END) })

      Text(this.checkTips)
        .fontSize(`${BODY_M}fp`)
        .fontWeight(FontWeight.Medium)
        .fontColor(this.fontColorWithTheme)
        .maxLines(CONTENT_MAX_LINES)
        .focusable(false)
        .layoutWeight(1)
        .textOverflow({ overflow: TextOverflow.Ellipsis })
    }
    .accessibilityGroup(true)
    .accessibilityText(getCheckTipsAccessibilityText(this.checkTips, this.checkedInner))
    .accessibilityDescription(this.checkedInner ? $r('sys.string.advanced_dialog_accessibility_cancel_checked_desc') :
    $r('sys.string.slider_accessibility_unselectedDesc'))
    .onClick(() => {
      this.checkedInner = !this.checkedInner;
      try {
        let hostContext: Context | undefined = this.getUIContext()?.getHostContext();
        let resourceManager: resourceManager.ResourceManager | undefined = hostContext?.resourceManager;
        let bundleName: string = (hostContext as common.UIAbilityContext)?.abilityInfo?.bundleName ??
          (hostContext as common.UIExtensionContext)?.extensionAbilityInfo?.bundleName;
        let eventInfo: accessibility.EventInfo = ({
          type: 'announceForAccessibility',
          bundleName: bundleName,
          triggerAction: 'common',
          textAnnouncedForAccessibility: this.checkedInner ?
            resourceManager?.getStringSync(125833934) :
            resourceManager?.getStringSync(125833935)
        });
        accessibility.sendAccessibilityEvent(eventInfo);
      } catch (exception) {
        let code: number = (exception as BusinessError).code;
        let message: string = (exception as BusinessError).message;
        hilog.error(0x3900, 'Ace', `Faild to send event, cause, code: ${code}, message: ${message}`);
      }
    })
    .width('100%')
    .padding({ top: 8, bottom: 8 })
  }

  @Builder
  buildContent(): void {
    ConfirmDialogContentLayout({ minContentHeight: this.minContentHeight!! }) {
      ForEach([this.textIndex, this.checkboxIndex], (index: number) => {
        if (index === this.textIndex) {
          this.textBuilder();
        } else if (index === this.checkboxIndex) {
          this.checkBoxBuilder();
        }
      });
    }
  }

  build() {
    CustomDialogContentComponent({
      primaryTitle: this.title,
      contentBuilder: () => {
        this.buildContent();
      },
      minContentHeight: this.minContentHeight!!,
      buttons: this.buttons,
    }).constraintSize({ maxHeight: '100%' });
  }

  onWillApplyTheme(theme: Theme): void {
    this.fontColorWithTheme = theme.colors.fontPrimary;
  }
}

@ComponentV2
export struct AlertDialogV2 {
  @Param primaryTitle?: ResourceStr = undefined;
  @Param secondaryTitle?: ResourceStr = undefined;
  @Require @Param content: ResourceStr = '';
  @Param primaryButton?: AdvancedDialogV2Button | null = null;
  @Param secondaryButton?: AdvancedDialogV2Button | null = null;
  private textAlign: TextAlign = TextAlign.Center;
  // the controller of content area
  private contentScroller: Scroller = new Scroller();
  @Local fontColorWithTheme: ResourceColor = $r('sys.color.font_primary');
  @Provider() fontSizeScale: number = 1;
  @Local minContentHeight: number = MIN_CONTENT_HEIGHT;

  @Computed
  get buttons(): AdvancedDialogV2Button[] | undefined {
    if (!this.primaryButton && !this.secondaryButton) {
      return undefined;
    }
    let buttons: AdvancedDialogV2Button[] = [];
    if (this.primaryButton) {
      buttons.push(this.primaryButton);
    }
    if (this.secondaryButton) {
      buttons.push(this.secondaryButton);
    }
    return buttons;
  }

  build() {
    CustomDialogContentComponent({
      primaryTitle: this.primaryTitle,
      secondaryTitle: this.secondaryTitle,
      contentBuilder: () => {
        this.AlertDialogContentBuilder();
      },
      buttons: this.buttons,
      minContentHeight: this.minContentHeight!!,
    }).constraintSize({ maxHeight: '100%' });
  }

  @Builder
  AlertDialogContentBuilder(): void {
    Column() {
      Scroll(this.contentScroller) {
        Text(this.content)
          .focusable(true)
          .defaultFocus(!(this.primaryButton || this.secondaryButton))
          .focusBox({
            strokeWidth: LengthMetrics.px(0)
          })
          .fontSize(`${CONTENT_FONT_SIZE}fp`)
          .fontWeight(this.getFontWeight())
          .fontColor(this.fontColorWithTheme)
          .margin({ end: LengthMetrics.vp(SCROLL_BAR_OFFSET) })
          .width(`calc(100% - ${SCROLL_BAR_OFFSET}vp)`)
          .textAlign(this.textAlign)
          .onKeyEvent((event: KeyEvent) => {
            if (event) {
              resolveKeyEvent(event, this.contentScroller);
            }
          })
      }
      .nestedScroll({ scrollForward: NestedScrollMode.PARALLEL, scrollBackward: NestedScrollMode.PARALLEL })
      .width('100%')
    }
    .margin({ end: LengthMetrics.vp(0 - SCROLL_BAR_OFFSET) })
  }

  onWillApplyTheme(theme: Theme): void {
    this.fontColorWithTheme = theme.colors.fontPrimary;
  }

  private getFontWeight(): number {
    if (this.primaryTitle || this.secondaryTitle) {
      return FontWeight.Regular;
    }
    return FontWeight.Medium;
  }
}

@ComponentV2
export struct CustomContentDialogV2 {
  @Param primaryTitle?: ResourceStr = undefined;
  @Param secondaryTitle?: ResourceStr = undefined;
  @BuilderParam contentBuilder: CustomBuilder;
  @Param contentAreaPadding?: LocalizedPadding = undefined;
  @Param buttons?: AdvancedDialogV2Button[] = undefined;
  @Provider() fontSizeScale: number = 1;
  @Local minContentHeight: number = MIN_CONTENT_HEIGHT;

  build() {
    CustomDialogContentComponent({
      primaryTitle: this.primaryTitle,
      secondaryTitle: this.secondaryTitle,
      contentBuilder: () => {
        if (typeof this.contentBuilder === 'function') {
          this.contentBuilder();
        }
      },
      contentAreaPadding: this.contentAreaPadding,
      buttons: this.buttons,
      minContentHeight: this.minContentHeight!!,
    }).constraintSize({ maxHeight: '100%' });
  }
}

@ComponentV2
struct CustomDialogLayout {
  @Builder
  doNothingBuilder(): void {
  };

  @Param
  titleHeight: number = 0;
  @Event
  $titleHeight?: (val: number) => void = undefined;
  @Param
  buttonHeight: number = 0;
  @Event
  $buttonHeight?: (val: number) => void = undefined;
  @Param
  titleMinHeight: Length = 0;
  @BuilderParam
  dialogBuilder: () => void = this.doNothingBuilder;
  private titleIndex: number = 0;
  private contentIndex: number = 1;
  private buttonIndex: number = 2;

  onPlaceChildren(selfLayoutInfo: GeometryInfo, children: Array<Layoutable>,
    constraint: ConstraintSizeOptions) {
    let currentX: number = 0;
    let currentY: number = 0;
    for (let index = 0; index < children.length; index++) {
      let child = children[index];
      child.layout({ x: currentX, y: currentY });
      currentY += child.measureResult.height;
    }
  }

  onMeasureSize(selfLayoutInfo: GeometryInfo, children: Array<Measurable>,
    constraint: ConstraintSizeOptions): SizeResult {
    let sizeResult: SizeResult = { width: Number(constraint.maxWidth), height: 0 };
    let childrenSize: number = 3;
    if (children.length < childrenSize) {
      return sizeResult;
    }
    let height: number = 0;
    let titleChild: Measurable = children[this.titleIndex];
    let titleConstraint: ConstraintSizeOptions = {
      maxWidth: constraint.maxWidth,
      minHeight: this.titleMinHeight,
      maxHeight: constraint.maxHeight
    };
    let titleMeasureResult: MeasureResult = titleChild.measure(titleConstraint);
    this.$titleHeight?.(titleMeasureResult.height);
    height += titleMeasureResult.height;

    let buttonChild: Measurable = children[this.buttonIndex];
    let buttonMeasureResult: MeasureResult = buttonChild.measure(constraint);
    this.$buttonHeight?.(buttonMeasureResult.height);
    height += buttonMeasureResult.height;

    let contentChild: Measurable = children[this.contentIndex];
    let contentConstraint: ConstraintSizeOptions = {
      maxWidth: constraint.maxWidth,
      maxHeight: Number(constraint.maxHeight) - height
    };

    let contentMeasureResult: MeasureResult = contentChild.measure(contentConstraint);
    height += contentMeasureResult.height;
    sizeResult.height = height;
    return sizeResult;
  }

  build() {
    this.dialogBuilder();
  }
}


@ComponentV2
struct CustomDialogContentComponent {
  @Param
  primaryTitle?: ResourceStr = undefined;
  @Param
  secondaryTitle?: ResourceStr = undefined;
  @BuilderParam
  contentBuilder: () => void = this.defaultContentBuilder;
  @Param
  buttons?: AdvancedDialogV2Button[] = undefined;
  @Param
  contentAreaPadding?: LocalizedPadding | Padding = undefined;
  @Require
  @Param
  minContentHeight: number;
  @Event $minContentHeight?: (val: number) => void = undefined;
  private keyIndex: number = 0;

  @Builder
  defaultContentBuilder(): void {
  }

  @Local titleHeight: number = 0;
  @Local buttonHeight: number = 0;
  @Local contentMaxHeight: Length = '100%';
  @Consumer() fontSizeScale: number = -1;
  @Local customStyle: boolean | undefined = undefined;
  @Local buttonMaxFontSize: Length = `${BODY_L}fp`;
  @Local buttonMinFontSize: Length = 9;
  @Local primaryTitleFontColorWithTheme: ResourceColor = $r('sys.color.font_primary');
  @Local secondaryTitleFontColorWithTheme: ResourceColor = $r('sys.color.font_secondary');
  @Local titleTextAlign: TextAlign = TextAlign.Center;
  @Local isButtonVertical: boolean = false;
  private isFollowingSystemFontScale: boolean = false;
  private appMaxFontScale: number = 3.2;
  private titleIndex: number = 0;
  private contentIndex: number = 1;
  private buttonIndex: number = 2;
  private primaryTitleFontSize: Length = `${TITLE_S}fp`;
  private secondaryTitleFontSize: Length = `${SUBTITLE_S}fp`;
  private scroller: Scroller = new Scroller();
  @Param@Once isHasDefaultFocus: boolean = false;
  @Param@Once isAllFocusFalse: boolean = false;

  build() {
    RelativeContainer() {
      Scroll(this.scroller) {
        Column() {
          CustomDialogLayout({
            buttonHeight: this.buttonHeight!!,
            titleHeight: this.titleHeight!!,
            titleMinHeight: this.getTitleAreaMinHeight(),
          }) {
            ForEach([this.titleIndex, this.contentIndex, this.buttonIndex], (index: number) => {
              if (index === this.titleIndex) {
                this.titleBuilder();
              } else if (index === this.contentIndex) {
                Column() {
                  this.contentBuilder();
                }.padding(this.getContentPadding())
              } else {
                this.ButtonBuilder();
              }
            });
          }
        }
        .constraintSize({ maxHeight: this.contentMaxHeight })
        .backgroundBlurStyle(this.customStyle ?
        BlurStyle.Thick : BlurStyle.NONE, undefined, { disableSystemAdaptation: true })
        .borderRadius(this.customStyle ? $r('sys.float.ohos_id_corner_radius_dialog') : 0)
        .margin(this.customStyle ? {
          start: LengthMetrics.resource($r('sys.float.ohos_id_dialog_margin_start')),
          end: LengthMetrics.resource($r('sys.float.ohos_id_dialog_margin_end')),
          bottom: LengthMetrics.resource($r('sys.float.ohos_id_dialog_margin_bottom')),
        } : { left: 0, right: 0, bottom: 0 })
        .backgroundColor(this.customStyle ? $r('sys.color.ohos_id_color_dialog_bg') : Color.Transparent)
      }
      .scrollBar(BarState.Off)
      .id('CustomDialogContentComponent')
      .edgeEffect(EdgeEffect.None, { alwaysEnabled: false })
      .backgroundColor(Color.Transparent)

      ScrollBar({scroller: this.scroller})
        .alignRules({
          top: { anchor: 'CustomDialogContentComponent', align: VerticalAlign.Top },
          bottom: { anchor: 'CustomDialogContentComponent', align: VerticalAlign.Bottom },
          end: { anchor: 'CustomDialogContentComponent', align: HorizontalAlign.End }
        })
        .margin({ top: $r('sys.float.alert_container_shape'), bottom: $r('sys.float.alert_container_shape')})
        .enableNestedScroll(true)
        .hitTestBehavior(HitTestMode.Transparent)
        .onGestureRecognizerJudgeBegin((event: BaseGestureEvent, current: GestureRecognizer,
          others: Array<GestureRecognizer>) => {
          if (current) {
            if (current.getType() == GestureControl.GestureType.LONG_PRESS_GESTURE) {
              return GestureJudgeResult.REJECT;
            }
          }
          return GestureJudgeResult.CONTINUE;
        })
    }.height('auto')
  }

  onMeasureSize(selfLayoutInfo: GeometryInfo, children: Array<Measurable>,
    constraint: ConstraintSizeOptions): SizeResult {
    let sizeResult: SizeResult = { width: selfLayoutInfo.width, height: selfLayoutInfo.height };
    let maxWidth: number = Number(constraint.maxWidth);
    let maxHeight: number = Number(constraint.maxHeight);
    this.fontSizeScale = this.updateFontScale();
    this.updateFontSize();
    this.isButtonVertical = this.isVerticalAlignButton(maxWidth - BUTTON_HORIZONTAL_MARGIN * 2);
    let height: number = 0;
    children.forEach((child) => {
      this.contentMaxHeight = '100%';
      let measureResult: MeasureResult = child.measure(constraint);
      if (maxHeight - this.buttonHeight - this.titleHeight < this.minContentHeight) {
        this.contentMaxHeight = MAX_CONTENT_HEIGHT;
        measureResult = child.measure(constraint);
      }
      height += measureResult.height;
    });
    sizeResult.height = height;
    sizeResult.width = maxWidth;
    return sizeResult;
  }

  onWillApplyTheme(theme: Theme): void {
    this.primaryTitleFontColorWithTheme = theme.colors.fontPrimary;
    this.secondaryTitleFontColorWithTheme = theme.colors.fontSecondary;
  }

  aboutToAppear(): void {
    try {
      let uiContext: UIContext = this.getUIContext();
      this.isFollowingSystemFontScale = uiContext?.isFollowingSystemFontScale();
      this.appMaxFontScale = uiContext?.getMaxFontScale();
    } catch (err) {
      let code: number = (err as BusinessError)?.code;
      let message: string = (err as BusinessError)?.message;
      hilog.error(0x3900, 'Ace', `Faild to dialog getUIContext, code: ${code}, message: ${message}`);
    }
    this.fontSizeScale = this.updateFontScale();
    this.initTitleTextAlign();
    this.setDefaultFocusState(this.buttons);
  }

  private updateFontSize(): void {
    if (this.fontSizeScale > MAX_FONT_SCALE) {
      this.buttonMaxFontSize = BODY_L * MAX_FONT_SCALE + 'vp';
      this.buttonMinFontSize = BUTTON_MIN_FONT_SIZE * MAX_FONT_SCALE + 'vp';
    } else {
      this.buttonMaxFontSize = BODY_L + 'fp';
      this.buttonMinFontSize = BUTTON_MIN_FONT_SIZE + 'fp';
    }
  }

  updateFontScale(): number {
    try {
      let uiContext: UIContext = this.getUIContext();
      let systemFontScale = (uiContext.getHostContext() as common.UIAbilityContext)?.config?.fontSizeScale ?? 1;
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

  /**
   * set state of button focus
   */
  private setDefaultFocusState(buttonList?: AdvancedDialogV2Button[]): void {
    if (!buttonList) {
      return;
    }
    let falseNum: number = 0;
    buttonList.forEach((button: AdvancedDialogV2Button) => {
      // 遍历查询按钮中存在是否存在默认按钮
      if (button.defaultFocus) {
        this.isHasDefaultFocus = true;
      }
      if (button.defaultFocus === false) {
        falseNum++;
      }
    });
    // 所有按钮defaultFocus都设置为false
    if (falseNum === buttonList.length) {
      this.isAllFocusFalse = true;
    }
  }

  /**
   * get dialog content padding
   *
   * @returns content padding
   */
  private getContentPadding(): Padding | LocalizedPadding {
    if (this.contentAreaPadding) {
      return this.contentAreaPadding;
    }
    if ((this.primaryTitle || this.secondaryTitle) && this.buttons && this.buttons.length > 0) {
      return {
        top: 0,
        right: $r('sys.float.alert_content_default_padding'),
        bottom: 0,
        left: $r('sys.float.alert_content_default_padding'),
      };
    } else if (this.primaryTitle || this.secondaryTitle) {
      return {
        top: 0,
        right: $r('sys.float.alert_content_default_padding'),
        bottom: $r('sys.float.alert_content_default_padding'),
        left: $r('sys.float.alert_content_default_padding'),
      };
    } else if (this.buttons && this.buttons.length > 0) {
      return {
        top: $r('sys.float.alert_content_default_padding'),
        right: $r('sys.float.alert_content_default_padding'),
        bottom: 0,
        left: $r('sys.float.alert_content_default_padding'),
      };
    } else {
      return {
        top: $r('sys.float.alert_content_default_padding'),
        right: $r('sys.float.alert_content_default_padding'),
        bottom: $r('sys.float.alert_content_default_padding'),
        left: $r('sys.float.alert_content_default_padding'),
      };
    }
  }

  @Builder
  titleBuilder() {
    Column() {
      Row() {
        Text(this.primaryTitle)
          .fontWeight(FontWeight.Bold)
          .fontColor(this.primaryTitleFontColorWithTheme)
          .textAlign(this.titleTextAlign)
          .fontSize(this.primaryTitleFontSize)
          .maxFontScale(Math.min(this.appMaxFontScale, MAX_FONT_SCALE))
          .maxLines(TITLE_MAX_LINES)
          .heightAdaptivePolicy(TextHeightAdaptivePolicy.MAX_LINES_FIRST)
          .textOverflow({ overflow: TextOverflow.Ellipsis })
          .width('100%')
      }
      .width('100%')

      if (this.primaryTitle && this.secondaryTitle) {
        Row() {
        }.height($r('sys.float.padding_level1'))
      }

      Row() {
        Text(this.secondaryTitle)
          .fontWeight(FontWeight.Regular)
          .fontColor(this.secondaryTitleFontColorWithTheme)
          .textAlign(this.titleTextAlign)
          .fontSize(this.secondaryTitleFontSize)
          .maxFontScale(Math.min(this.appMaxFontScale, MAX_FONT_SCALE))
          .maxLines(TITLE_MAX_LINES)
          .heightAdaptivePolicy(TextHeightAdaptivePolicy.MAX_LINES_FIRST)
          .textOverflow({ overflow: TextOverflow.Ellipsis })
          .width('100%')
      }
      .width('100%')
    }
    .justifyContent(FlexAlign.Center)
    .width('100%')
    .padding(this.getTitleAreaPadding())
  }

  /**
   * get title area padding
   *
   * @returns padding
   */
  private getTitleAreaPadding(): Padding {
    if (this.primaryTitle || this.secondaryTitle) {
      return {
        top: $r('sys.float.alert_title_padding_top'),
        right: $r('sys.float.alert_title_padding_right'),
        left: $r('sys.float.alert_title_padding_left'),
        bottom: $r('sys.float.alert_title_padding_bottom'),
      };
    }

    return {
      top: 0,
      right: $r('sys.float.alert_title_padding_right'),
      left: $r('sys.float.alert_title_padding_left'),
      bottom: 0,
    };
  }

  /**
   * get tile TextAlign
   * @returns TextAlign
   */
  private initTitleTextAlign(): void {
    let textAlign: number = ALERT_TITLE_ALIGNMENT;
    if (textAlign === TextAlign.Start) {
      this.titleTextAlign = TextAlign.Start;
    } else if (textAlign === TextAlign.Center) {
      this.titleTextAlign = TextAlign.Center;
    } else if (textAlign === TextAlign.End) {
      this.titleTextAlign = TextAlign.End;
    } else if (textAlign === TextAlign.JUSTIFY) {
      this.titleTextAlign = TextAlign.JUSTIFY;
    } else {
      this.titleTextAlign = TextAlign.Center;
    }
  }

  /**
   * get title area min height
   *
   * @returns min height
   */
  private getTitleAreaMinHeight(): ResourceStr | number {
    if (this.secondaryTitle) {
      return $r('sys.float.alert_title_secondary_height');
    } else if (this.primaryTitle) {
      return $r('sys.float.alert_title_primary_height');
    } else {
      return 0;
    }
  }

  @Builder
  ButtonBuilder(): void {
    Column() {
      if (this.buttons && this.buttons.length > 0) {
        if (this.isButtonVertical) {
          this.buildVerticalAlignButtons();
        } else {
          this.buildHorizontalAlignButtons();
        }
      }
    }
    .width('100%')
    .padding(this.getOperationAreaPadding());
  }

  /**
   * get operation area padding
   *
   * @returns padding
   */
  private getOperationAreaPadding(): Padding {
    if (this.isButtonVertical) {
      return {
        top: $r('sys.float.alert_button_top_padding'),
        right: $r('sys.float.alert_right_padding_vertical'),
        left: $r('sys.float.alert_left_padding_vertical'),
        bottom: $r('sys.float.alert_button_bottom_padding_vertical'),
      };
    }

    return {
      top: $r('sys.float.alert_button_top_padding'),
      right: $r('sys.float.alert_right_padding_horizontal'),
      left: $r('sys.float.alert_left_padding_horizontal'),
      bottom: $r('sys.float.alert_button_bottom_padding_horizontal'),
    };
  }

  @Builder
  buildSingleButton(index: number): void {
    if (this.isNewPropertiesHighPriority(index)) {
      Button(this.buttons?.[index].content)
        .setButtonProperties(this.buttons?.[index], this.isHasDefaultFocus, 
          this.isAllFocusFalse, this.getDialogController())
        .role(this.buttons?.[index].role ?? ButtonRole.NORMAL)
        .key(`advanced_dialog_button_${this.keyIndex++}`)
        .labelStyle({ maxLines: 1, maxFontSize: this.buttonMaxFontSize, minFontSize: this.buttonMinFontSize })
    } else if (this.buttons?.[index].background !== undefined && this.buttons?.[index].fontColor !== undefined) {
      Button(this.buttons?.[index].content)
        .setButtonProperties(this.buttons?.[index], this.isHasDefaultFocus, 
          this.isAllFocusFalse, this.getDialogController())
        .backgroundColor(this.buttons?.[index].background?.color)
        .fontColor(this.buttons?.[index].fontColor?.color)
        .key(`advanced_dialog_button_${this.keyIndex++}`)
        .labelStyle({ maxLines: 1, maxFontSize: this.buttonMaxFontSize, minFontSize: this.buttonMinFontSize })
    } else if (this.buttons?.[index].background !== undefined) {
      Button(this.buttons?.[index].content)
        .setButtonProperties(this.buttons?.[index], this.isHasDefaultFocus, 
          this.isAllFocusFalse, this.getDialogController())
        .backgroundColor(this.buttons?.[index].background?.color)
        .key(`advanced_dialog_button_${this.keyIndex++}`)
        .labelStyle({ maxLines: 1, maxFontSize: this.buttonMaxFontSize, minFontSize: this.buttonMinFontSize })
    } else {
      Button(this.buttons?.[index].content)
        .setButtonProperties(this.buttons?.[index], this.isHasDefaultFocus, 
          this.isAllFocusFalse, this.getDialogController())
        .fontColor(this.buttons?.[index]?.fontColor?.color)
        .key(`advanced_dialog_button_${this.keyIndex++}`)
        .labelStyle({ maxLines: 1, maxFontSize: this.buttonMaxFontSize, minFontSize: this.buttonMinFontSize })
    }
  }

  @Builder
  buildHorizontalAlignButtons(): void {
    if (this.buttons && this.buttons.length > 0) {
      Row() {
        this.buildSingleButton(0);
        if (this.buttons.length === HORIZON_BUTTON_MAX_COUNT) {
          Row() {
            Divider()
              .width($r('sys.float.alert_divider_width'))
              .height($r('sys.float.alert_divider_height'))
              .color(this.getDividerColor())
              .vertical(true)
          }
          .width(BUTTON_HORIZONTAL_SPACE * 2)
          .justifyContent(FlexAlign.Center)

          this.buildSingleButton(HORIZON_BUTTON_MAX_COUNT - 1);
        }
      }
    }
  }

  @Builder
  buildVerticalAlignButtons(): void {
    if (this.buttons) {
      Column() {
        ForEach(this.buttons.slice(0, VERTICAL_BUTTON_MAX_COUNT), (item: AdvancedDialogV2Button, index: number) => {
          this.buildButtonWithDivider(this.buttons?.length === HORIZON_BUTTON_MAX_COUNT ?
            HORIZON_BUTTON_MAX_COUNT - index - 1 : index);
        }, (item: AdvancedDialogV2Button) => item.content.toString());
      }
    }
  }

  /**
   * get divider color
   *
   * @returns divider color
   */
  private getDividerColor(): ResourceColor {
    if (!this.buttons || this.buttons.length === 0 || !DIALOG_DIVIDER_SHOW) {
      return Color.Transparent;
    }

    if (this.buttons[0].buttonStyle === ButtonStyleMode.TEXTUAL || this.buttons[0].buttonStyle === undefined) {
      if (this.buttons[HORIZON_BUTTON_MAX_COUNT - 1].buttonStyle === ButtonStyleMode.TEXTUAL ||
        this.buttons[HORIZON_BUTTON_MAX_COUNT - 1].buttonStyle === undefined) {
        return $r('sys.color.alert_divider_color');
      }
    }
    return Color.Transparent;
  }

  /**
   * is button buttonStyle and role properties high priority
   *
   * @param buttonOptions button properties
   * @returns check result
   */
  private isNewPropertiesHighPriority(index: number): boolean {
    if (this.buttons?.[index].role === ButtonRole.ERROR) {
      return true;
    }
    if (this.buttons?.[index].buttonStyle !== undefined &&
      this.buttons?.[index].buttonStyle !== ALERT_BUTTON_STYLE) {
      return true;
    }
    if (this.buttons?.[index].background === undefined && this.buttons?.[index].fontColor === undefined) {
      return true;
    }
    return false;
  }

  @Builder
  buildButtonWithDivider(index: number): void {
    if (this.buttons && this.buttons[index]) {
      Row() {
        this.buildSingleButton(index);
      }

      if ((this.buttons.length === HORIZON_BUTTON_MAX_COUNT ? HORIZON_BUTTON_MAX_COUNT - index - 1 : index) <
        Math.min(this.buttons.length, VERTICAL_BUTTON_MAX_COUNT) - 1) {
        Row() {
        }
        .height($r('sys.float.alert_button_vertical_space'))
      }
    }
  }

  private isVerticalAlignButton(width: number): boolean {
    if (this.buttons) {
      if (this.buttons.length === 1) {
        return false;
      }
      if (this.buttons.length !== HORIZON_BUTTON_MAX_COUNT) {
        return true;
      }
      let isVertical: boolean = false;
      let maxButtonTextSize = vp2px(width / HORIZON_BUTTON_MAX_COUNT - BUTTON_HORIZONTAL_MARGIN -
        BUTTON_HORIZONTAL_SPACE - 2 * BUTTON_HORIZONTAL_PADDING);
      this.buttons.forEach((button) => {
        let contentSize: SizeOptions = measure.measureTextSize({
          textContent: button.content,
          fontSize: this.buttonMaxFontSize
        });
        if (Number(contentSize.width) > maxButtonTextSize) {
          isVertical = true;
        }
      });
      return isVertical;
    }
    return false;
  }
}

@Extend(Button)
function setButtonProperties(buttonOptions?: AdvancedDialogV2Button,
  isHasDefaultFocus?: boolean, isAllFocusFalse?: boolean,
  controller?: PromptActionDialogController) {
  .onKeyEvent((event: KeyEvent) => {
    if (!event) {
      return;
    }
    if ((event.keyCode === KeyCode.KEYCODE_SPACE || event.keyCode === KeyCode.KEYCODE_ENTER) &&
      event.type === KeyType.Down) {
      if (buttonOptions?.action) {
        buttonOptions.action();
      }
      closeDialog(controller, 'onKeyEvent');
      event.stopPropagation();
    }
  })
  .onClick(() => {
    if (buttonOptions?.action) {
      buttonOptions.action();
    }
    closeDialog(controller, 'onClick');
  })
  .defaultFocus(isDefaultFocus(buttonOptions, isHasDefaultFocus, isAllFocusFalse))
  .buttonStyle(buttonOptions?.buttonStyle ?? ALERT_BUTTON_STYLE)
  .layoutWeight(BUTTON_LAYOUT_WEIGHT)
  .type(ButtonType.ROUNDED_RECTANGLE)
  .enabled(buttonOptions?.enabled ?? true)
}

function closeDialog(controller: CustomDialogController | undefined, funcName: string) {
  if (controller) {
    hilog?.info(0x3900,'Ace',`AdvancedDialog button ${funcName} controller true`);
    controller?.close();
  } else {
    hilog?.info(0x3900,'Ace',`AdvancedDialog button ${funcName} controller false`);
  }
}

/**
 * is button set default focus
 *
 * @param singleButton button options
 * @param isHasDefaultFocus is button list has default focus button
 * @param isAllFocusFalse is all button in button list default focus false
 * @returns boolean
 */
function isDefaultFocus(singleButton?: AdvancedDialogV2Button, isHasDefaultFocus?: boolean,
  isAllFocusFalse?: boolean): boolean {
  try {
    // 当前按钮为默认按钮
    if (singleButton?.defaultFocus) {
      return true;
    }
    let isDefaultFocus: boolean = false;
    if (isHasDefaultFocus || isAllFocusFalse) {
      isDefaultFocus = false; // 存在默认按钮或者所有按钮的defaultFocus都为false
    } else {
      isDefaultFocus = true; // 默认第一个按钮获焦
    }
    return isDefaultFocus;
  } catch (error) {
    let code: number = (error as BusinessError).code;
    let message: string = (error as BusinessError).message;
    hilog.error(0x3900, 'Ace', `get defaultFocus exist error, code: ${code}, message: ${message}`);
    return true;
  }
}

/**
 * get resource size
 *
 * @param resourceId resource id
 * @param defaultValue default value
 * @returns resource size
 */
function getNumberByResourceId(resourceId: number, defaultValue: number, allowZero?: boolean): number {
  try {
    let sourceValue: number = resourceManager.getSystemResourceManager().getNumber(resourceId);
    if (sourceValue > 0 || allowZero) {
      return sourceValue;
    } else {
      return defaultValue;
    }
  } catch (error) {
    let code: number = (error as BusinessError).code;
    let message: string = (error as BusinessError).message;
    hilog.error(0x3900, 'Ace', `CustomContentDialog getNumberByResourceId error, code: ${code}, message: ${message}`);
    return defaultValue;
  }
}

/**
 * get enum number
 *
 * @param resourceId resource id
 * @param defaultValue default value
 * @returns number
 */
function getEnumNumberByResourceId(resourceId: number, defaultValue: number): number {
  try {
    let sourceValue: number = getContext().resourceManager.getNumber(resourceId);
    if (sourceValue > 0) {
      return sourceValue;
    } else {
      return defaultValue;
    }
  } catch (error) {
    let code: number = (error as BusinessError).code;
    let message: string = (error as BusinessError).message;
    hilog.error(0x3900, 'Ace', `getEnumNumberByResourceId error, code: ${code}, message: ${message}`);
    return defaultValue;
  }
}

/**
 * 获取SelectDialog无障碍文本
 *
 * @param resource 资源
 * @param selected select state
 * @returns string
 */
function getAccessibilityText(resource: ResourceStr, selected: boolean): string {
  try {
    let selectText: string = getContext().resourceManager.getStringSync(125833934);
    let resourceString: string = '';
    if (typeof resource === 'string') {
      resourceString = resource;
    } else {
      resourceString = getContext().resourceManager.getStringSync(resource);
    }
    return selected ? `${selectText},${resourceString}` : resourceString;
  } catch (error) {
    let code: number = (error as BusinessError).code;
    let message: string = (error as BusinessError).message;
    hilog.error(0x3900, 'Ace', `getAccessibilityText error, code: ${code}, message: ${message}`);
    return '';
  }
}

/**
 * resolve content area keyEvent
 *
 * @param event keyEvent
 * @param controller the controller of content area
 * @returns undefined
 */
function resolveKeyEvent(event: KeyEvent, controller: Scroller) {
  if (event.type === IGNORE_KEY_EVENT_TYPE) {
    return;
  }

  if (event.keyCode === KEYCODE_UP) {
    controller.scrollPage({ next: false });
    event.stopPropagation();
  } else if (event.keyCode === KEYCODE_DOWN) {
    if (controller.isAtEnd()) {
      return;
    } else {
      controller.scrollPage({ next: true });
      event.stopPropagation();
    }
  }
}

/**
 * 获取checkTips无障碍文本
 *
 * @param resource 资源
 * @param selected select state
 * @returns string
 */
function getCheckTipsAccessibilityText(resource: ResourceStr | null | undefined, selected?: boolean): string {
  try {
    // 'sys.string.slider_accessibility_selected'
    let selectText: string = getContext().resourceManager.getStringSync(125833934);
    // 'sys.string.slider_accessibility_unselected'
    let unselectText: string = getContext().resourceManager.getStringSync(125833935);
    // 'sys.string.advanced_dialog_accessibility_checkbox'
    let checkBoxText: string = getContext().resourceManager.getStringSync(125834354);
    let resourceString: string = '';
    if (typeof resource === 'string') {
      resourceString = resource
    } else {
      resourceString = getContext().resourceManager.getStringSync(resource);
    }
    return selected ? `${selectText},${resourceString},${checkBoxText}` :
      `${unselectText},${resourceString},${checkBoxText}`;
  } catch (error) {
    let code: number = (error as BusinessError).code;
    let message: string = (error as BusinessError).message;
    hilog.error(0x3900, 'Ace', `getCheckTipsAccessibilityText error, code: ${code}, message: ${message}`);
    return '';
  }
}

@ComponentV2
export struct LoadingDialogV2 {
  @Param content?: ResourceStr = '';
  @Local fontColorWithTheme: ResourceColor = $r('sys.color.font_primary');
  @Local loadingProgressIconColorWithTheme: ResourceColor = $r('sys.color.icon_secondary');
  @Provider() fontSizeScale: number = 1;
  @Local minContentHeight: number = MIN_CONTENT_HEIGHT;

  build() {
    Column() {
      CustomDialogContentComponent({
        contentBuilder: () => {
          this.contentBuilder();
        },
        minContentHeight: this.minContentHeight!!,
      }).constraintSize({ maxHeight: '100%' });
    }
  }

  @Builder
  contentBuilder(): void {
    Column() {
      Row() {
        Text(this.content)
          .fontSize(`${CONTENT_FONT_SIZE}fp`)
          .fontWeight(FontWeight.Regular)
          .fontColor(this.fontColorWithTheme)
          .layoutWeight(LOADING_TEXT_LAYOUT_WEIGHT)
          .maxLines(this.fontSizeScale > MAX_FONT_SCALE ? LOADING_MAX_LINES_BIG_FONT : LOADING_MAX_LINES)
          .focusable(true)
          .defaultFocus(true)
          .focusBox({
            strokeWidth: LengthMetrics.px(0)
          })
          .textOverflow({ overflow: TextOverflow.Ellipsis })
        LoadingProgress()
          .color(this.loadingProgressIconColorWithTheme)
          .width(LOADING_PROGRESS_WIDTH)
          .height(LOADING_PROGRESS_HEIGHT)
          .margin({ start: LengthMetrics.vp(LOADING_TEXT_MARGIN_LEFT) })
      }
      .constraintSize({ minHeight: LOADING_MIN_HEIGHT })
    }
  }

  onWillApplyTheme(theme: Theme): void {
    this.fontColorWithTheme = theme.colors.fontPrimary;
    this.loadingProgressIconColorWithTheme = theme.colors.iconSecondary;
  }
}

export type PopoverDialogV2OnVisibleChange = (visible: boolean) => void;

@ComponentV2
export struct PopoverDialogV2 {
  @Require @Param
  visible: boolean = false;
  @Event
  $visible?: PopoverDialogV2OnVisibleChange;
  @Require @Param
  popover: PopoverDialogV2Options = {
    builder: undefined
  };
  @BuilderParam
  targetBuilder: Callback<void>;
  @Local
  dialogWidth: Dimension | undefined = this.popover?.width;

  @Builder
  emptyBuilder() {
  }

  aboutToAppear(): void {
    if (this.targetBuilder === undefined || this.targetBuilder === null) {
      this.targetBuilder = this.emptyBuilder;
    }
  }

  build() {
    Column() {
      this.targetBuilder();
    }
    .onClick(() => {
      try {
        let screenSize: display.Display = display.getDefaultDisplaySync();
        let screenWidth: number = px2vp(screenSize.width);
        if (screenWidth - BUTTON_HORIZONTAL_MARGIN - BUTTON_HORIZONTAL_MARGIN > MAX_DIALOG_WIDTH) {
          this.popover.width = this.popover?.width ?? MAX_DIALOG_WIDTH;
        } else {
          this.popover.width = this.dialogWidth;
        }
        this.$visible?.(!this.visible);
      } catch (error) {
        let code: number = (error as BusinessError).code;
        let message: string = (error as BusinessError).message;
        hilog.error(0x3900, 'Ace', `dialog popup error, code: ${code}, message: ${message}`);
      }
    })
    .bindPopup(this.visible, {
      builder: this.popover?.builder,
      placement: this.popover?.placement ?? Placement.Bottom,
      popupColor: this.popover?.popupColor,
      enableArrow: this.popover?.enableArrow ?? true,
      autoCancel: this.popover?.autoCancel,
      onStateChange: this.popover?.onStateChange ?? ((e) => {
        if (!e.isVisible) {
          this.$visible?.(false);
        }
      }),
      arrowOffset: this.popover?.arrowOffset,
      showInSubWindow: this.popover?.showInSubWindow,
      mask: this.popover?.mask,
      targetSpace: this.popover?.targetSpace,
      offset: this.popover?.offset,
      width: this.popover?.width,
      arrowPointPosition: this.popover?.arrowPointPosition,
      arrowWidth: this.popover?.arrowWidth,
      arrowHeight: this.popover?.arrowHeight,
      radius: this.popover?.radius ?? $r('sys.float.corner_radius_level16'),
      shadow: this.popover?.shadow ?? ShadowStyle.OUTER_DEFAULT_MD,
      backgroundBlurStyle: this.popover?.backgroundBlurStyle ?? BlurStyle.COMPONENT_ULTRA_THICK,
      focusable: this.popover?.focusable,
      transition: this.popover?.transition,
      onWillDismiss: this.popover?.onWillDismiss
    })
  }
}

function toLengthString(value?: LengthMetrics): string | undefined {
  if (!value) {
    return undefined;
  }
  const length: number = value.value;
  let lengthString: string = '';
  switch (value.unit) {
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

function lengthMetricsToPX(value?: LengthMetrics): number {
  if (!value) {
    return 0;
  }
  const length: number = value.value;
  switch (value.unit) {
    case LengthUnit.PX:
      return length;
    case LengthUnit.FP:
      return fp2px(length);
    case LengthUnit.LPX:
      return lpx2px(length);
    case LengthUnit.VP:
      return vp2px(length);
    default:
      return 0;
  }
}

export declare interface PopoverDialogV2Options extends CustomPopupOptions {}