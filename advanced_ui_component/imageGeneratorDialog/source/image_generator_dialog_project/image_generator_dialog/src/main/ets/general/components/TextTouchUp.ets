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

import { MeasureUtils } from '@kit.ArkUI';
import { AIGenerateImpl } from '../utils/AIGenerateImpl'
import { default as imageGeneration } from '@ohos.arkui.intelligence.imageGeneration'

@ComponentV2
export struct TextTouchUpComponent {
  build() {
    NavDestination() {
      TextTouchUp()
    }
    .title('文本润色')
    .backgroundImageSize({
      width: '100%',
      height: '100%'
    })
    .onBackPressed(() => {
      AIGenerateImpl.getInstance().cancelTextGenerateTask(2)
      return false;
    })
  }
}

@ComponentV2
struct TextTouchUp {
  @Local originText: string = "";
  @Local uiContext: UIContext = this.getUIContext();
  @Local uiContextMeasure: MeasureUtils = this.uiContext.getMeasureUtils();
  textSize: SizeOptions = this.uiContextMeasure.measureTextSize({
    textContent: this.originText,
    fontSize: 13
  });
  stack: NavPathStack | undefined = undefined;
  @Local aiThinkText: string = '';
  @Local aiResultText: string = '';
  @Local isDisPlayThinkProcess: boolean = true;
  @Local imgOrientation: ImageRotateOrientation = ImageRotateOrientation.UP;
  @Local symbolRes: Resource = $r('sys.symbol.chevron_up_L');
  @Local taskId: number = -1;

  aboutToAppear(): void {
    this.stack = this.queryNavigationInfo()?.pathStack;
    AIGenerateImpl.getInstance().TextAIGenerate({
      onReady: () => {
      },
      onError: () => {
      },
      onResult: (result: imageGeneration.GenerateTextTaskPartialResult) => {
        if (result.reasoningContent) {
          this.aiThinkText += result.reasoningContent;
        }

        if (result.content) {
          this.aiResultText += result.content;
        }
      },
      onComplete: (result: string[]) => {
      },
    }).then((id: number) => {
      this.taskId = id;
    })
  }

  build() {
    Column() {
      Column() {
        Scroll() {
          Column() {
            Flex({
              direction: FlexDirection.Row,
              justifyContent: FlexAlign.Start,
              alignItems: ItemAlign.Start,
            }) {
              Text('深度思考')
                .width(582)
                .height(20)
                .textAlign(TextAlign.Start)
                .fontColor("#000000")
                .fontSize(14)
                .fontWeight(500)
                .lineHeight(17)

              SymbolGlyph(this.symbolRes)
                .width(20)
                .height(20)
                .onClick(() => {
                  this.isDisPlayThinkProcess = !this.isDisPlayThinkProcess;
                  if (this.isDisPlayThinkProcess) {
                    this.imgOrientation = ImageRotateOrientation.UP;
                    this.symbolRes = $r('sys.symbol.chevron_up_L')
                  } else {
                    this.imgOrientation = ImageRotateOrientation.DOWN;
                    this.symbolRes = $r('sys.symbol.chevron_down')
                  }
                })
            }
            .width('100%')
            .height(40)
            .padding({
              top: 8,
              bottom: 12,
              left: 8,
              right: 8
            })

            Text(this.aiThinkText)
              .fontColor($r('sys.color.font_tertiary'))
              .fontSize(14)
              .fontWeight(400)
              .lineHeight(17)
              .backgroundColor(Color.Transparent)
              .padding({
                left: 8,
                right: 8
              })
              .visibility(this.imgOrientation == ImageRotateOrientation.UP ? Visibility.Visible : Visibility.None)

            Column() {
              Divider()
                .strokeWidth(0.5)
                .color($r('sys.color.comp_divider'))
            }
            .width('100%')
            .padding({
              top: 8,
              bottom: 8
            })

            Column() {
              TextArea({ text: $$this.aiResultText })
                .placeholderFont({ size: 14 })
                .fontColor('#e6000000')
                .fontSize(16)
                .fontWeight(500)
                .lineHeight(19)
                .backgroundColor("#ffffffff")
                .padding({
                  top: 0,
                  bottom: 0,
                  left: 0,
                  right: 0
                })
                .borderRadius(0)
            }
            .width('100%')
            .height(184)
            .padding({
              top: 8,
              bottom: 8,
              left: 16,
              right: 16
            })
            .borderRadius(16)
            .backgroundColor("#ffffffff")
            .shadow({
              radius: 18,
              offsetX: 0,
              offsetY: 4,
              fill: false,
              color: '#05ffffff'
            })
          }.padding({
            bottom: 6,
            left: 16
          })
        }.constraintSize({maxHeight: 358})
      }
      .height(382)
      .width('100%')
      .margin({
        top: 16,
        right: 8
      })

      Text('内容由API生成')
        .fontColor($r('sys.color.font_tertiary'))
        .fontSize(12)
        .fontWeight(400)
        .lineHeight(14)
        .textAlign(TextAlign.Center)

      Button('使用润色结果')
        .width(448)
        .height(40)
        .fontSize(16)
        .fontWeight(500)
        .margin({
          top: 20,
          bottom: 16,
          left: 101,
          right: 101
        })
        .onClick(() => {
          if (this.stack) {
            this.stack.pop(this.aiResultText);
          }
        })
    }
    .width('100%')
    .height('100%')
  }
}