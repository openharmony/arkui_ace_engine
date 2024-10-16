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
import { RadioBlock, useEnabled, ColorBlock } from 'common';

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
  @State enableCaretColor: boolean = false;
  @State caretColor: ResourceColor | undefined = undefined;
  @State enableSelectedBackgroundColor: boolean = false;
  @State selectedBackgroundColor: ResourceColor | undefined = undefined;
  @State enableCompBackgroundColor: boolean = false;
  @State compBackgroundColor: ResourceColor | undefined = undefined;

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
          .bindSelectionMenu(
            useEnabled(this.customSelectionMenu, RichEditorSpanType.TEXT),
            this.customSelectionMenu ? this.MySelectionMenu() : undefined,
            useEnabled(this.customSelectionMenu, RichEditorResponseType.LONG_PRESS),
            this.customSelectionMenu ? {
              onDisappear: () => {
                this.sliderShow = false;
              }
            } : undefined)
          .height('100%')
          .direction(useEnabled(this.enableDirection, this.compDirection))
          .caretColor(useEnabled(this.enableCaretColor, this.caretColor))
          .selectedBackgroundColor(useEnabled(this.enableSelectedBackgroundColor, this.selectedBackgroundColor))
          .backgroundColor(useEnabled(this.enableCompBackgroundColor, this.compBackgroundColor))
      }
    }
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        RadioBlock({
          title: '布局方式',
          isEnabled: this.enableDirection,
          value: this.compDirection,
          dataSource: [
            { label: '默认布局', value: Direction.Auto },
            { label: '从右到左', value: Direction.Rtl },
            { label: '从左到右', value: Direction.Ltr }
          ]
        })
        RadioBlock({
          title: '是否设置自定义选择菜单',
          isEnabled: this.enableCustomSelectionMenu,
          value: this.customSelectionMenu,
          dataSource: [
            { label: '自定义', value: true },
            { label: '默认', value: false }
          ]
        })
        if (this.customSelectionMenu) {
          RadioBlock({
            title: '是否显示文本菜单1',
            isEnabled: this.enableTextSelectionMenu,
            value: this.textSelectionMenu,
            dataSource: [
              { label: '显示', value: true },
              { label: '隐藏', value: false }
            ]
          })
          RadioBlock({
            title: '是否显示文本菜单2',
            isEnabled: this.enableSystemSelectionMenu,
            value: this.systemSelectionMenu,
            dataSource: [
              { label: '显示', value: true },
              { label: '隐藏', value: false }
            ]
          })
        }
        ColorBlock({
          title: '光标颜色',
          isEnabled: this.enableCaretColor,
          color: this.caretColor,
        })
        ColorBlock({
          title: '选中背景颜色',
          isEnabled: this.enableSelectedBackgroundColor,
          color: this.selectedBackgroundColor,
        })
        ColorBlock({
          title: '背景颜色',
          isEnabled: this.enableCompBackgroundColor,
          color: this.compBackgroundColor,
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