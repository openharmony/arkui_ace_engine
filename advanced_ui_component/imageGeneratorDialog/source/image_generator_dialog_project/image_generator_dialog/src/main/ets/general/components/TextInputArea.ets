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
import { ImageGenerateState } from "../types/Declaration";
import { KeyboardAvoidMode, MeasureUtils } from '@kit.ArkUI';
import { AIGenerateOptions } from '../utils/AIGenerateOptions';

@ComponentV2
export struct TextInputArea {
  @Event changeGenerateState: (state: ImageGenerateState) => void = (state: ImageGenerateState) => {};
  @Local isTextEdit: boolean = false;
  @Local inputText: string = '';
  @Local userPrompt: string = '';
  @Local inputController: TextAreaController = new TextAreaController();
  private textAreaPadding = 12;
  private setMaxLines = 8;
  @Local originText: string = "";
  @Local uiContext: UIContext = this.getUIContext();
  @Local uiContextMeasure: MeasureUtils = this.uiContext.getMeasureUtils();
  textSize: SizeOptions = this.uiContextMeasure.measureTextSize({
    textContent: this.originText,
    fontSize: 16
  });
  @Local textMaxLines: number = 1;
  @Local textOverflow: TextOverflow = TextOverflow.Ellipsis;
  private patchesStr: string = '带白色描边的贴纸效果';
  private keepLayoutStr: string = '保持输入图形的位置关系';
  @Local isSelectedPatches: boolean = false;
  @Local isClickKeepLayout: boolean = false;
  @Local inputHeight: Length = 45;
  @Local imgCounts: number = 2;
  @Local isEnableTouchUp: boolean = false;
  @Local isShowTouchUp: boolean = false;
  @Local stack: NavPathStack | undefined = undefined;
  @Local updateInputText: string = '';

  @Monitor('imgCounts', 'isClickKeepLayout', 'updateInputText', 'isSelectedPatches')
  watchKeepLayout(monitor: IMonitor) {
    if (this.imgCounts <= 1) {
      this.isClickKeepLayout = false;
      if (this.inputText.includes(this.keepLayoutStr)) {
        let str = this.inputText.replace(this.keepLayoutStr + '，', "");
        this.inputText = str;
      }
    }

    if (this.isClickKeepLayout && !this.inputText.includes(this.keepLayoutStr)) {
      this.inputText = this.keepLayoutStr + '，' + this.inputText;
    } else if (!this.isClickKeepLayout && this.inputText.includes(this.keepLayoutStr)) {
      let replaceStr =
        this.inputText.includes(this.keepLayoutStr + '，') ? this.keepLayoutStr + '，' : this.keepLayoutStr;
      let str = this.inputText.replace(replaceStr, "");
      this.inputText = str;
    }

    if (this.isSelectedPatches && !this.inputText.includes(this.patchesStr)) {
      if (this.inputText.includes(this.keepLayoutStr)) {
        let index = this.inputText.indexOf(this.keepLayoutStr);
        let part1 = this.inputText.slice(0, index + this.keepLayoutStr.length);
        let part2 = this.inputText.slice(index + this.keepLayoutStr.length);
        this.inputText = part1.concat('，' + this.patchesStr).concat(part2);
      } else {
        this.inputText = this.patchesStr + '，' + this.inputText;
      }
    } else if (!this.isSelectedPatches && this.inputText.includes(this.patchesStr)) {
      let replaceStr = this.inputText.includes(this.patchesStr + '，') ? this.patchesStr + '，' : this.patchesStr;
      let str = this.inputText.replace(replaceStr, "");
      this.inputText = str;
    }

    if (this.updateInputText.length != 0) {
      this.inputText = this.updateInputText;
      this.updateInputText = '';
    }
  }

  @Monitor('userPrompt')
  watchUserPromptChange(monitor: IMonitor) {
    this.inputText = this.userPrompt;
  }

  aboutToAppear(): void {
    this.inputText = this.userPrompt;
    this.stack = this.queryNavigationInfo()?.pathStack;
  }

  build() {
    Column() {
      Row({ space: 8 }) {
        Row({space: 4}) {
          Image($r('sys.media.maintain_layout'))
            .width('16vp')
            .height('16vp')
          Text('保持布局')
            .height('100%')
            .fontSize(12)
        }
        .padding({
          top: 6,
          bottom: 6,
          left: 12,
          right: 12
        })
        .borderRadius(20)
        .backgroundColor(this.isClickKeepLayout ? $r('sys.color.comp_background_primary') :
          $r('sys.color.comp_background_tertiary'))
        .visibility((this.imgCounts > 1 && this.isTextEdit) ? Visibility.Visible : Visibility.None)
        .onClick(() => {
          this.isClickKeepLayout = !this.isClickKeepLayout;
        })

        Row({space: 4}) {
          SymbolGlyph($r('sys.symbol.AI_pencil'))
            .width('16vp')
            .height('16vp')
          Text('文本润色')
            .height('100%')
            .fontSize(12)
        }
        .padding({
          top: 6,
          bottom: 6,
          left: 12,
          right: 12
        })
        .borderRadius(20)
        .backgroundColor($r('sys.color.comp_background_tertiary'))
        .enabled(this.isEnableTouchUp)
        .visibility(this.isTextEdit ? Visibility.Visible : Visibility.None)
        .onClick(() => {
          this.isShowTouchUp = true;
          this.inputController.stopEditing();
          AIGenerateOptions.getInstance().updateUserPrompt(this.inputText);
          if (this.stack) {
            this.stack.pushPath({
              name: 'textTouchUp', onPop: (popInfo: PopInfo) => {
                this.inputText = popInfo.result.toString();
              }
            })
          }
        })

        Row({space: 4}) {
          SymbolGlyph($r('sys.symbol.stickers'))
            .width('16vp')
            .height('16vp')
          Text('贴纸效果')
            .height('100%')
            .fontSize(12)
        }
        .padding({
          top: 6,
          bottom: 6,
          left: 12,
          right: 12
        })
        .borderRadius(20)
        .backgroundColor(this.isSelectedPatches ? $r('sys.color.comp_background_primary') :
          $r('sys.color.comp_background_tertiary'))
        .visibility(this.isTextEdit ? Visibility.Visible : Visibility.None)
        .onClick(() => {
          this.isSelectedPatches = !this.isSelectedPatches;
        })
      }
      .width('100%')
      .height(28)
      .visibility(this.isTextEdit ? Visibility.Visible : Visibility.None)

      Row({space: 12}) {
        Column() {
          TextArea({ placeholder: '描述你想要创作的内容', text: $$this.inputText, controller: this.inputController })
            .padding({ top: this.textAreaPadding, bottom: this.textAreaPadding })
            .constraintSize({
              maxHeight: this.textAreaPadding * 2 +
                this.setMaxLines * this.getUIContext().px2vp(Number(this.textSize.height))
            })
            .placeholderFont({ size: 16 })
            .textAlign(TextAlign.Start)
            .backgroundColor(Color.Transparent)
            .maxLength(600)
            .maxLines(this.textMaxLines)
            .textOverflow(this.textOverflow)
            .barState(BarState.On)
            .onChange((value: string) => {
              this.inputText = value;
              this.isEnableTouchUp = this.inputText.length > 0 ? true : false;
              if (!this.inputText.includes(this.keepLayoutStr)) {
                this.isClickKeepLayout = false;
              } else if (this.inputText.includes(this.keepLayoutStr) && this.imgCounts > 1) {
                this.isClickKeepLayout = true;
              }
              if (!this.inputText.includes(this.patchesStr)) {
                this.isSelectedPatches = false;
              } else {
                this.isSelectedPatches = true;
              }
            })
            .onClick((event?: ClickEvent) => {
              if (!this.inputText.includes(this.keepLayoutStr) && this.imgCounts > 1) {
                this.inputText = this.keepLayoutStr + '，' + this.inputText;
                this.isClickKeepLayout = true;
              }
            })
            .onEditChange((isEditing: boolean) => {
              this.isTextEdit = isEditing;
              if (isEditing) {
                this.textMaxLines = 0;
                this.textOverflow = TextOverflow.None;
                this.inputHeight = 'auto';
                this.getUIContext().setKeyboardAvoidMode(KeyboardAvoidMode.OFFSET_WITH_CARET);
              } else {
                this.textMaxLines = 1;
                this.textOverflow = TextOverflow.Ellipsis;
                this.inputHeight = 45;
                this.getUIContext().setKeyboardAvoidMode(KeyboardAvoidMode.OFFSET);
              }
            })
        }
        .height(this.inputHeight)
        .width(510)
        .borderRadius(31.11)
        .borderWidth(0.5)

        Column()
          .borderRadius(31.11)
          .borderWidth(0.5)
          .height(40)
          .width(96)
          .onClick(() => {
            this.changeGenerateState(ImageGenerateState.GENERATING)
          })
      }
      .width('100%')
      .alignItems(VerticalAlign.Bottom)
      .padding({
        top: 12,
        bottom: 12
      })
    }
    .alignItems(HorizontalAlign.Start)
    .padding({
      left: 16,
      right: 16
    })
  }
}