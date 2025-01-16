/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
import pasteboard from '@ohos.pasteboard';
import { BusinessError } from '@ohos.base';
import { Drawer } from 'common/src/main/ets/components/Drawer';
import { RadioBlock, useEnabled, ColorBlock, SliderBlock } from 'common';

@Component
export struct RichEditorBootcamp {
  @Require @Prop title: ResourceStr;
  @State message: string =
    '华为UX设计规范用于指导软件界面的设计，确保给用户提供清晰一致、简单易用的使用体验，在产品组织内对齐设计语言，拉通体验设计的方向，帮助设计师统一设计品质。';
  @State sliderShow: boolean = false;
  controller: RichEditorController = new RichEditorController();
  private iconArr: Array<string> = ['剪切', '复制', '粘贴', '分享'];
  @State enablePaste: boolean = false;
  @State selectionMenuVisibilityValue: Visibility = Visibility.Visible;
  @State showParameters: boolean = false;
  @State enableCustomSelectionMenu: boolean = true;
  @State customSelectionMenu: boolean = false;
  @State enableTextSelectionMenu: boolean = true;
  @State textSelectionMenu: boolean = true;
  @State systemSelectionMenu: boolean = true;
  @State enableSystemSelectionMenu: boolean = true;
  @State enableDirection: boolean = false;
  @State compDirection: Direction = Direction.Auto;
  @State enableCompBackgroundColor: boolean = false;
  @State compBackgroundColor: ResourceColor | undefined = undefined;
  @State enableCustomKeyboardOption: boolean = false;
  @State customKeyboardOption: boolean = false;
  @State enableBindSelectionMenuSpanType: boolean = false;
  @State bindSelectionMenuSpanType: RichEditorSpanType = RichEditorSpanType.TEXT;
  @State enableBindSelectionMenuResponseType: boolean = false;
  @State bindSelectionMenuResponseType: ResponseType = ResponseType.LongPress;
  @State enableCopyOptions: boolean = false;
  @State copyOptions: CopyOptions = CopyOptions.LocalDevice;
  @State enableEnableDataDetector: boolean = false;
  @State enableDataDetector: boolean = false;
  @State enableDataDetectorConfigTypes: boolean = false;
  @State dataDetectorConfigTypes:　TextDataDetectorType|undefined = undefined
  @State enableEnablePreviewText: boolean = false;
  @State enablePreviewText: boolean = true;
  @State enablePlaceholderFontValue: boolean = false;
  @State placeholderFontValue: string | undefined = undefined;
  @State enablePlaceholderStyleFontSize: boolean = false;
  @State placeholderStyleFontSize: number = 16.0;
  @State enablePlaceholderStyleFontWeight: boolean = false;
  @State placeholderStyleFontWeight: FontWeight | number | string = FontWeight.Normal;
  @State enablePlaceholderStyleFontStyle: boolean = false;
  @State placeholderStyleFontStyle: FontStyle = FontStyle.Normal;
  @State enablePlaceholderStyleFontColor: boolean = false
  @State placeholderStyleFontColor: ResourceColor|undefined = undefined;
  @State enableCaretColor: boolean = false;
  @State caretColor: ResourceColor | undefined = '#007DFF';
  @State enableSelectedBackgroundColor: boolean = false;
  @State selectedBackgroundColor: ResourceColor | undefined = undefined;
  @State enableEnterKeyType: boolean = false;
  @State enterKeyType: EnterKeyType = EnterKeyType.NEW_LINE;
  @State enableBarState: boolean = false;
  @State barState: BarState = BarState.Auto;
  @State enableEnableHapticFeedback: boolean = false;
  @State enableHapticFeedback: boolean = true;

  build() {
    NavDestination() {
      Drawer({
        title: this.title,
        showParameters: $showParameters,
        content: () => {
          this.Content()
        },
        parameters: () => {
          this.Parameters()
        }
      })
    }
    .backgroundColor($r('sys.color.ohos_id_color_sub_background'))
    .hideTitleBar(true)
  }

  @Builder
  Content() {
    Column() {
      Column() {
        RichEditor({ controller: this.controller })
          .onReady(() => {
            this.controller.addTextSpan(this.message)
          })
          .bindSelectionMenu(
            useEnabled(this.customSelectionMenu, RichEditorSpanType.TEXT),
            this.customSelectionMenu ? this.MySelectionMenu() : undefined,
            useEnabled(this.customSelectionMenu, RichEditorResponseType.RIGHT_CLICK),
            this.customSelectionMenu ? {
              onDisappear: () => {
                this.sliderShow = false;
              }
            } : undefined)
          .customKeyboard((result: void) => {},
            { supportAvoidance: useEnabled(this.enableCustomKeyboardOption, this.customKeyboardOption) })
          .bindSelectionMenu(
            useEnabled(this.customSelectionMenu, RichEditorSpanType.TEXT),
            this.customSelectionMenu ? this.MySelectionMenu() : undefined,
            useEnabled(this.customSelectionMenu, RichEditorResponseType.LONG_PRESS),
            this.customSelectionMenu ? { onDisappear: () => {this.sliderShow = false;} } : undefined)
          .height('100%')
          .direction(useEnabled(this.enableDirection, this.compDirection))
          .backgroundColor(useEnabled(this.enableCompBackgroundColor, this.compBackgroundColor))
          .bindSelectionMenu(useEnabled(this.enableBindSelectionMenuSpanType, this.bindSelectionMenuSpanType),
            (result: void)=>{},
            useEnabled(this.enableBindSelectionMenuResponseType, this.bindSelectionMenuResponseType),
          )
          .copyOptions(useEnabled(this.enableCopyOptions,this.copyOptions))
          .enableDataDetector(useEnabled(this.enableEnableDataDetector,this.enableDataDetector))
          .dataDetectorConfig({
            types: [useEnabled(this.enableDataDetectorConfigTypes, this.dataDetectorConfigTypes)],
            onDetectResultUpdate: (result: string)=>{}
          })
          .enablePreviewText(useEnabled(this.enableEnablePreviewText,this.enablePreviewText))
          .placeholder(useEnabled(this.enablePlaceholderFontValue,this.placeholderFontValue),
            {font:{size:useEnabled(this.enablePlaceholderStyleFontSize,this.placeholderStyleFontSize),
            weight:useEnabled(this.enablePlaceholderStyleFontWeight,this.placeholderStyleFontWeight),
            style:useEnabled(this.enablePlaceholderStyleFontStyle,this.placeholderStyleFontStyle)},
              fontColor:useEnabled(this.enablePlaceholderStyleFontColor,this.placeholderStyleFontColor)
            })
          .caretColor(useEnabled(this.enableCaretColor, this.caretColor))
          .selectedBackgroundColor(useEnabled(this.enableSelectedBackgroundColor, this.selectedBackgroundColor))
          .enterKeyType(useEnabled(this.enableEnterKeyType,this.enterKeyType))

      }
    }
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        RadioBlock({
          title: 'compDirection',
          isEnabled: this.enableDirection,
          value: this.compDirection,
          dataSource: [
            { label: 'Auto', value: Direction.Auto },
            { label: 'Rtl', value: Direction.Rtl },
            { label: 'Ltr', value: Direction.Ltr }
          ]
        })
        RadioBlock({
          title: 'customSelectionMenu',
          isEnabled: this.enableCustomSelectionMenu,
          value: this.customSelectionMenu,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })
        if (this.customSelectionMenu) {
          RadioBlock({
            title: 'textSelectionMenu',
            isEnabled: this.enableTextSelectionMenu,
            value: this.textSelectionMenu,
            dataSource: [
              { label: 'true', value: true },
              { label: 'false', value: false }
            ]
          })
          RadioBlock({
            title: 'systemSelectionMenu',
            isEnabled: this.enableSystemSelectionMenu,
            value: this.systemSelectionMenu,
            dataSource: [
              { label: 'true', value: true },
              { label: 'false', value: false }
            ]
          })
        }

        ColorBlock({
          title: 'selectedBackgroundColor',
          isEnabled: this.enableSelectedBackgroundColor,
          color: this.selectedBackgroundColor,
        })
        ColorBlock({
          title: 'compBackgroundColor',
          isEnabled: this.enableCompBackgroundColor,
          color: this.compBackgroundColor,
        })

        RadioBlock({
          title: 'customKeyboard.option',
          isEnabled: this.enableCustomKeyboardOption,
          value: this.customKeyboardOption,
          dataSource: [
            { label: 'false', value: false },
            { label: 'true', value: true },
          ]
        })

        RadioBlock({
          title:'bindSelectionMenu.spanType',
          isEnabled: this.enableBindSelectionMenuSpanType,
          value: this.bindSelectionMenuSpanType,
          dataSource: [
            {label: 'TEXT', value: TextSpanType.TEXT },
            {label: 'IMAGE', value: TextSpanType.IMAGE },
            {label: 'MIXED', value: TextSpanType.MIXED },
          ]
        })

        RadioBlock({
          title:'bindSelectionMenu.responseType',
          isEnabled: this.enableBindSelectionMenuResponseType,
          value: this.bindSelectionMenuResponseType,
          dataSource: [
            {label: 'RIGHT_CLICK', value: TextResponseType.RIGHT_CLICK },
            {label: 'LONG_PRESS', value: TextResponseType.LONG_PRESS },
            {label: 'SELECT', value: TextResponseType.SELECT },
          ]
        })

        RadioBlock({
          title: 'copyOptions',
          isEnabled: this.enableCopyOptions,
          value: this.copyOptions,
          dataSource: [
            { label: 'None', value: CopyOptions.None },
            { label: 'InApp', value: CopyOptions.InApp },
            { label: 'LocalDevice', value: CopyOptions.LocalDevice },
          ]
        })

        RadioBlock({
          title: 'enableDataDetector',
          isEnabled: this.enableEnableDataDetector,
          value: this.enableDataDetector,
          dataSource: [
            { label: 'false', value: false },
            { label: 'true', value: true },
          ]
        })

        RadioBlock({
          title:'textDataDetectorConfig.types',
          isEnabled: this.enableDataDetectorConfigTypes,
          value: this.dataDetectorConfigTypes,
          dataSource: [
            {label: 'NULL', value: [] },
            {label: 'PHONE_NUMBER', value: TextDataDetectorType.PHONE_NUMBER },
            {label: 'URL', value: TextDataDetectorType.URL },
            {label: 'EMAIL', value: TextDataDetectorType.EMAIL },
            {label: 'ADDRESS', value: TextDataDetectorType.ADDRESS },
            {label: 'DATE_TIME', value: TextDataDetectorType.DATE_TIME },
          ]
        })

        RadioBlock({
          title: 'enablePreviewText',
          isEnabled: this.enableEnablePreviewText,
          value: this.enablePreviewText,
          dataSource: [
            { label: 'false', value: false },
            { label: 'true', value: true },
          ]
        })


        SliderBlock({
          title: 'placeholderStyle.font.size',
          isEnabled: this.enablePlaceholderStyleFontSize,
          value: this.placeholderStyleFontSize,
          min: 1,
          max: 200
        })

        RadioBlock({
          title:'placeholderStyle.font.weight',
          isEnabled: this.enablePlaceholderStyleFontWeight,
          value: this.placeholderStyleFontWeight,
          dataSource: [
            {label: '100', value: 100},
            {label: '200', value: 200},
            {label: '300', value: 300},
            {label: '400', value: 400},
            {label: '500', value: 500},
            {label: '600', value: 600},
            {label: '700', value: 700},
            {label: '800', value: 800},
            {label: '900', value: 900},
            {label: 'Lighter', value: FontWeight.Lighter },
            {label: 'Normal', value: FontWeight.Normal },
            {label: 'Regular', value: FontWeight.Regular },
            {label: 'Medium', value: FontWeight.Medium },
            {label: 'Bold', value: FontWeight.Bold },
            {label: 'Bolder', value: FontWeight.Bolder },
          ]
        })

        RadioBlock({
          title:'placeholderStyle.font.style',
          isEnabled: this.enablePlaceholderStyleFontStyle,
          value: this.placeholderStyleFontStyle,
          dataSource: [
            {label: 'Normal', value: FontStyle.Normal },
            {label: 'Italic', value: FontStyle.Italic },
          ]
        })

        ColorBlock({
          title: 'placeholderStyle.fontColor',
          isEnabled: this.enablePlaceholderStyleFontColor,
          color: this.placeholderStyleFontColor,
        })

        ColorBlock({
          title: 'caretColor',
          isEnabled: this.enableCaretColor,
          color: this.caretColor,
        })

        ColorBlock({
          title: 'selectedBackgroundColor',
          isEnabled: this.enableSelectedBackgroundColor,
          color: this.selectedBackgroundColor
        })

        RadioBlock({
          title: 'enterKeyType',
          isEnabled: this.enableEnterKeyType,
          value: this.enterKeyType,
          dataSource: [
            { label: 'Go', value: EnterKeyType.Go },
            { label: 'Search', value: EnterKeyType.Search },
            { label: 'Send', value: EnterKeyType.Send },
            { label: 'Next', value: EnterKeyType.Next },
            { label: 'Done', value: EnterKeyType.Done },
            { label: 'PREVIOUS', value: EnterKeyType.PREVIOUS },
            { label: 'NEW_LINE', value: EnterKeyType.NEW_LINE },
          ]
        })

      }
    }
  }

  @Builder
  MySelectionMenu() {
    Column() {
      if (this.textSelectionMenu) {
        this.TextSelectionMenu()
      }
      if (this.systemSelectionMenu) {
        this.SystemSelectionMenu()
      }
    }
  }

  @Builder
  TextSelectionMenu() {
    Column() {
      Row({ space: 2 }) {
        if (this.controller) {
          ForEach(this.iconArr, (item: string, index : number) => {

            Flex({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
              Text(item)
                .padding(6)
                .borderRadius($r('sys.float.ohos_id_corner_radius_default_m'))
            }
            .borderRadius($r('sys.float.ohos_id_corner_radius_default_m'))
            .width(50)
            .height(40)
            .onClick(() => {
              if (index as number == 0) {
                if (!this.controller) {
                  return;
                }
                let richEditorSelection = this.controller.getSelection();
                this.pushDataToPasteboard(richEditorSelection)
                this.controller.deleteSpans({
                  start: richEditorSelection.selection[0],
                  end: richEditorSelection.selection[1]
                })
              } else if (index as number == 1) {
                if (!this.controller) {
                  return
                }
                let richEditorSelection = this.controller.getSelection();
                this.pushDataToPasteboard(richEditorSelection)
                this.controller.closeSelectionMenu()
              } else if (index as number == 2) {
                if (!this.controller) {
                  return;
                }
                let richEditorSelection = this.controller.getSelection();
                this.popDataFromPasteboard(richEditorSelection)

              } else if (index as number == 3) {
                if (!this.controller) {
                  return
                }
                this.controller.setSelection(-1, -1)
                this.selectionMenuVisibilityValue = Visibility.None;
              } else if (index as number == 4) {

              }
            })
          })
        }
      }
    }
    .clip(true)
    .borderRadius($r('sys.float.ohos_id_corner_radius_card'))
    .backgroundColor($r('sys.color.ohos_id_color_dialog_bg'))
    .shadow(ShadowStyle.OUTER_DEFAULT_MD)
  }

  @Builder
  SystemSelectionMenu() {
    Column() {
      Menu() {
        if (this.controller) {
          MenuItemGroup() {
            MenuItem({
              startIcon: $r('sys.media.ohos_ic_public_cut'),
              content: '剪切',
              labelInfo: 'Ctrl+X'
            })
              .onClick(() => {
                if (!this.controller) {
                  return;
                }
                let richEditorSelection = this.controller.getSelection();
                this.pushDataToPasteboard(richEditorSelection);
                this.controller.deleteSpans({
                  start: richEditorSelection.selection[0],
                  end: richEditorSelection.selection[1]
                })
              })
            MenuItem({
              startIcon: $r('sys.media.ohos_ic_public_copy'),
              content: '复制',
              labelInfo: 'Ctrl+C'
            })
              .onClick(() => {
                if (!this.controller) {
                  return;
                }
                let richEditorSelection = this.controller.getSelection();
                this.pushDataToPasteboard(richEditorSelection);
                this.controller.closeSelectionMenu();
              })
            MenuItem({
              startIcon: $r('sys.media.ohos_ic_public_paste'),
              content: '粘贴',
              labelInfo: 'Ctrl+V'
            })
              .enabled(this.enablePaste)
              .onClick(() => {
                if (!this.controller) {
                  return;
                }
                let richEditorSelection = this.controller.getSelection();
                this.popDataFromPasteboard(richEditorSelection);
              })
            MenuItem({
              startIcon: $r('sys.media.ohos_ic_public_select_all'),
              content: '全选',
              labelInfo: 'Ctrl+A'
            })
              .visibility(this.selectionMenuVisibilityValue)
              .onClick(() => {
                if (!this.controller) {
                  return;
                }
                this.controller.setSelection(-1, -1);
                this.selectionMenuVisibilityValue = Visibility.None;
              })
            MenuItem({ startIcon: $r('sys.media.ohos_ic_public_share'), content: '分享', labelInfo: '' })
              .enabled(false)
            MenuItem({ startIcon: $r('sys.media.ohos_ic_public_translate_c2e'), content: '翻译', labelInfo: '' })
              .enabled(false)
            MenuItem({ startIcon: $r('sys.media.ohos_ic_public_search_filled'), content: '搜索', labelInfo: '' })
              .enabled(false)
          }
        }
      }
      .onVisibleAreaChange([0.0, 1.0], () => {
        if (!this.controller) {
          return;
        }
        let richEditorSelection = this.controller.getSelection();
        let start = richEditorSelection.selection[0];
        let end = richEditorSelection.selection[1];
        if (start === 0 && this.controller.getSpans({ start: end + 1, end: end + 1 }).length === 0) {
          this.selectionMenuVisibilityValue = Visibility.None;
        } else {
          this.selectionMenuVisibilityValue = Visibility.Visible;
        }
      })
      .radius($r('sys.float.ohos_id_corner_radius_card'))
      .backgroundColor(Color.White)
    }
    .margin({ top: 8 })
  }

  pushDataToPasteboard(richEditorSelection: RichEditorSelection) {
    let sysBoard = pasteboard.getSystemPasteboard();
    let pasteData = pasteboard.createData(pasteboard.MIMETYPE_TEXT_PLAIN, '');
    if (richEditorSelection.spans && richEditorSelection.spans.length > 0) {
      let count = richEditorSelection.spans.length;
      for (let i = count - 1; i >= 0; i--) {
        let item = richEditorSelection.spans[i];
        if ((item as RichEditorTextSpanResult)?.textStyle) {
          let span = item as RichEditorTextSpanResult;
          let style = span.textStyle;
          let data = pasteboard.createRecord(pasteboard.MIMETYPE_TEXT_PLAIN, span.value.substring(span.offsetInSpan[0],
            span.offsetInSpan[1]))
          let prop = pasteData.getProperty();
          let temp: Record<string, Object> = {
            'color': style.fontColor,
            'size': style.fontSize,
            'style': style.fontStyle,
            'fontFamily': style.fontFamily,
            'decorationType': style.decoration.type,
            'decorationColor': style.decoration.color
          }
          prop.additions[i] = temp;
          pasteData.addRecord(data);
          pasteData.setProperty(prop);
        }
      }
    }
    sysBoard.clearData()
    sysBoard.setData(pasteData).then(() => {
      console.info('SelectionMenu copy option, Succeeded in setting PasteData.');
      this.enablePaste = true;
    }).catch((err: BusinessError) => {
      console.error('SelectionMenu copy option, Failed to set PasteData. Cause:' + err.message);
    })
  }

  popDataFromPasteboard(richEditorSeletion: RichEditorSelection) {
    let start = richEditorSeletion.selection[0];
    let end = richEditorSeletion.selection[1];

    if (start == end && this.controller) {
      start = this.controller.getCaretOffset();
      end = this.controller.getCaretOffset();
    }
  }
}

@Preview
@Component
struct RichEditorBootcampPreviewer {
  build() {
    RichEditorBootcamp({
      title: '富文本/RichEditor'
    })
  }
}