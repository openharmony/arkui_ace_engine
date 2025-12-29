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
import { CanvasLayoutDirection, ImageGenerateState } from "../types/Declaration";
import { KeyboardAvoidMode, MeasureUtils } from '@kit.ArkUI';
import { AIGenerateOptions } from '../utils/AIGenerateOptions';
import { unifiedDataChannel } from '@kit.ArkData';

const textBaseMaxLength: number = 280;

@ComponentV2
export struct TextInputArea {
  @Event changeGenerateState: (state: ImageGenerateState) => void = (state: ImageGenerateState) => {};
  @Local isTextEdit: boolean = false;
  @Local inputText: string = '';
  @Param userPrompt: string = '';
  @Local inputController: TextAreaController = new TextAreaController();
  private setMaxLines = 7;
  @Local originText: string = '';
  @Local uiContext: UIContext = this.getUIContext();
  @Local uiContextMeasure: MeasureUtils = this.uiContext.getMeasureUtils();
  textSize: SizeOptions = this.uiContextMeasure.measureTextSize({
    textContent: this.originText,
    fontSize: 16
  });
  @Local textMaxLines: number = 1;
  @Local textOverflow: TextOverflow = TextOverflow.Ellipsis;
  private patchesStr: string = '带白色描边的贴纸效果';
  private keepLayoutStr: string = '保持输入图像的位置关系';
  @Local isSelectedPatches: boolean = false;
  @Local isClickKeepLayout: boolean = false;
  @Local inputHeight: Length = 40;
  @Param imgCounts: number = 0;
  @Local isEnableTouchUp: boolean = false;
  @Local isShowTouchUp: boolean = false;
  @Local stack: NavPathStack | undefined = undefined;
  @Local updateInputText: string = '';
  @Local textMaxLength: number = 280;
  @Consumer('globalLayoutDirection') curLayoutDirection: CanvasLayoutDirection = CanvasLayoutDirection.DEFAULT;

  private getTextMaxLength() {
    this.textMaxLength = textBaseMaxLength;
    if (this.inputText.includes(this.keepLayoutStr + '，')) {
      this.textMaxLength += (this.keepLayoutStr + '，').length;
    } else if (this.inputText.includes(this.keepLayoutStr)) {
      this.textMaxLength += this.keepLayoutStr.length;
    }

    if (this.inputText.includes(this.patchesStr + '，')) {
      this.textMaxLength += (this.patchesStr + '，').length;
    } else if (this.inputText.includes(this.patchesStr)) {
      this.textMaxLength += this.patchesStr.length;
    }
  }

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

    this.getTextMaxLength();
  }

  @Monitor('userPrompt')
  watchUserPromptChange(monitor: IMonitor) {
    this.inputText = this.userPrompt;
  }

  aboutToAppear(): void {
    this.inputText = this.userPrompt;
    this.stack = this.queryNavigationInfo()?.pathStack;
  }

  private getDataFromUdmfRetry(event: DragEvent, callback: (data: DragEvent) => void) {
    try {
      let data: UnifiedData = event.getData();
      if (!data) {
        return false;
      }
      let records: Array<unifiedDataChannel.UnifiedRecord> = data.getRecords();
      if (!records || records.length <= 0) {
        return false;
      }
      callback(event);
      return true;
    } catch (e) {
      return false;
    }
  }

  private getDataFromUdmf(event: DragEvent, callback: (data: DragEvent) => void) {
    if (this.getDataFromUdmfRetry(event, callback)) {
      return;
    }
    setTimeout(() => {
      this.getDataFromUdmfRetry(event, callback);
    }, 1500);
  }

  build() {
    Column() {
      Row({ space: 8 }) {
        Button() {
          Row({space: 4}) {
            Image($r('sys.media.maintain_layout'))
              .width('16vp')
              .height('16vp')
              .fillColor($r('sys.color.icon_primary'))
            Text('保持布局')
              .height('100%')
              .fontSize(12)
              .fontColor($r('sys.color.icon_primary'))
          }
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

        Button() {
          Row({space: 4}) {
            SymbolGlyph($r('sys.symbol.AI_pencil'))
              .width('16vp')
              .height('16vp')
              .fontColor([$r('sys.color.icon_primary')])
            Text('文本润色')
              .height('100%')
              .fontSize(12)
              .fontColor($r('sys.color.icon_primary'))
          }
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

        Button() {
          Row({space: 4}) {
            SymbolGlyph($r('sys.symbol.stickers'))
              .width('16vp')
              .height('16vp')
              .fontColor([$r('sys.color.icon_primary')])
            Text('贴纸效果')
              .height('100%')
              .fontSize(12)
              .fontColor($r('sys.color.icon_primary'))
          }
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
            .margin({ top: 9.5, bottom: 9.5, left: 16, right: 16 })
            .padding(0)
            .constraintSize({
              maxHeight: this.setMaxLines * this.getUIContext().px2vp(Number(this.textSize.height))
            })
            .placeholderFont({ size: 16 })
            .placeholderColor($r('sys.color.font_tertiary'))
            .fontSize(16)
            .textAlign(TextAlign.Start)
            .backgroundColor(Color.Transparent)
            .maxLength(this.textMaxLength)
            .maxLines(this.textMaxLines)
            .textOverflow(this.textOverflow)
            .barState(BarState.On)
            .borderRadius(0)
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
            .onEditChange((isEditing: boolean) => {
              this.isTextEdit = isEditing;
              if (isEditing) {
                this.textMaxLines = 0;
                this.textOverflow = TextOverflow.None;
                this.inputHeight = 'auto';
                this.getUIContext().setKeyboardAvoidMode(KeyboardAvoidMode.OFFSET_WITH_CARET);

                if (!this.inputText.includes(this.keepLayoutStr) && this.imgCounts > 1) {
                  this.inputText = this.keepLayoutStr + '，' + this.inputText;
                  this.isClickKeepLayout = true;
                }
              } else {
                this.textMaxLines = 1;
                this.textOverflow = TextOverflow.Ellipsis;
                this.inputHeight = 40;
                this.getUIContext().setKeyboardAvoidMode(KeyboardAvoidMode.OFFSET);
              }
            })
            .onDrop((dragEvent?: DragEvent) => {
              this.isTextEdit = false;
              this.getDataFromUdmf((dragEvent as DragEvent), (event: DragEvent) => {
                let records: Array<unifiedDataChannel.UnifiedRecord> = event.getData().getRecords();
                let plainText: unifiedDataChannel.PlainText = records[0] as unifiedDataChannel.PlainText;
                this.inputController.addText(plainText.textContent, {offset: this.inputController.getCaretOffset().index});
              })
            })
        }
        .height(this.inputHeight)
        .width(this.curLayoutDirection === CanvasLayoutDirection.HORIZONTAL ? 510 : 344)
        .backgroundColor('#99FFFFFF')
        .backdropBlur(120)
        .borderRadius(24)
        .border({width: 1, color: '#FFFFFF'})

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