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

import curves from '@ohos.curves';
import { LengthMetrics, SegmentButton, SegmentButtonOptions } from '@kit.ArkUI';
import { BlockTag } from '../model/BlockTag';
import { MyFullDrawModifier } from '../model/DrawFullModifier';


@Builder
function IconButton(icon: Resource, action: () => void) {
  Button({ type: ButtonType.Circle }) {
    Image(icon)
      .fillColor($r('sys.color.ohos_id_color_primary'))
      .width(24)
      .height(24)
  }
  .backgroundColor($r('sys.color.ohos_id_color_button_normal'))
  .height(40)
  .width(40)
  .onClick(action)
}

@Component
export struct Drawer {
  @Prop @Require title: ResourceStr;
  @Link showParameters: boolean
  @BuilderParam content: () => void;
  @BuilderParam generic: () => void;
  @BuilderParam parameters: () => void;
  @Consume('router') router: NavPathStack;
  @State tabSelectedIndexes: number[] = [0];
  @State tabOptions: SegmentButtonOptions = SegmentButtonOptions.tab({
    buttons: [{ text: '参数列表' },{ text: '基础属性' }, { text: '日志' }],
    textPadding: { top: 8, bottom: 8 },backgroundColor:'#E1E3E5'
  });
  @StorageProp('Block') listBlockTags: Array<BlockTag> = [];
  @State dividerHeight: number = 1;
  @State circleModifier: DrawModifier = new MyFullDrawModifier();

  build() {
    Column() {
      Row({ space: 8 }) {
        IconButton($r('sys.media.ohos_ic_back'), () => {
          this.router.pop();
        })

        Text(this.title)
          .fontSize($r('sys.float.ohos_id_text_size_headline8'))
          .fontWeight(FontWeight.Bold)

        Blank()

        IconButton($r('sys.media.ohos_ic_public_more'), () => {
          animateTo({ curve: curves.interpolatingSpring(0, 1, 328, 36) }, () => {
            this.showParameters = !this.showParameters;
          });
        })
      }
      .width('100%')
      .padding(16)
      Stack() {
        this.content()
      }.layoutWeight(1)

      if (this.showParameters) {
        Column() {
          Row(){
            SegmentButton({ options: this.tabOptions, selectedIndexes: $tabSelectedIndexes })
              .width(380)
            Row() {
              IconButton($r('sys.media.ohos_ic_public_close'), () => {
                animateTo({ curve: curves.interpolatingSpring(0, 1, 328, 36) }, () => {
                  this.showParameters = false;
                });
              })
            }
            .height('100%')
            .position({ right: 8 })
            .alignItems(VerticalAlign.Center)
          }.width('100%')
          .height(56)
          .justifyContent(FlexAlign.SpaceBetween)
          .margin({ bottom: 12, top: 8 })

          if (this.tabSelectedIndexes[0] === 0 ) {
            this.parameters()
          } else if (this.tabSelectedIndexes[0] === 1){
            this.generic()
          } else {
            Stack() {
              List() {
                ForEach(this.listBlockTags, (item: BlockTag) => {
                  ListItem() {
                    Column({ space: 12 }) {
                      Row() {
                        Text(item.time)
                          .fontSize($r('sys.float.Body_S'))
                          .fontWeight(FontWeight.Medium)
                          .fontColor($r('sys.color.font_secondary'))
                      }
                      .justifyContent(FlexAlign.Start)
                      .width('100%')

                      Row() {
                        Text(item.description)
                          .fontSize($r('sys.float.Body_L'))
                          .fontWeight(FontWeight.Medium)
                          .fontColor($r('sys.color.font_primary'))
                          .maxLines(2)
                      }
                      .align(Alignment.Top)
                      .width('100%')
                    }
                    .margin({ top: 12 })
                    .padding({ start: LengthMetrics.vp(24), bottom: LengthMetrics.vp(12) })
                    .width('100%')
                    .justifyContent(FlexAlign.Start)
                  }
                  .drawModifier(this.circleModifier)
                }, (item: string) => JSON.stringify(item))
              }
              .onSizeChange((oldValue: SizeOptions, newValue: SizeOptions) => {
                console.info(`Ace: List on area change, oldValue is ${JSON.stringify(oldValue)} value is ${JSON.stringify(newValue)}`)
                this.dividerHeight = (newValue.height as number) + 16
                console.info('Ace: on area change, dividerHeight is' + this.dividerHeight)
              })
              .width('100%')
              .zIndex(2)
              .align(Alignment.Start)
            }
            .width('100%')
            .onDisAppear(() => {
              AppStorage.setOrCreate('Block', []);
            })
          }
        }
        .backgroundColor($r('sys.color.ohos_id_color_dialog_bg'))
        .borderRadius({ topLeft: 30, topRight: 30 })
        .constraintSize({ maxWidth: 480, maxHeight: '60%', minHeight: '40%' })
        .expandSafeArea([SafeAreaType.SYSTEM], [SafeAreaEdge.BOTTOM])
        .padding({
          left: 16,
          right: 16,
          top: 8,
          bottom: 32
        })
        .transition(TransitionEffect.move(TransitionEdge.BOTTOM))
        .width('100%')
      }
    }
    .align(Alignment.Top)
    .height('100%')
    .width('100%')
    .onAppear(() => {
      AppStorage.setOrCreate('Block', []);
    })
  }
}

@Preview
@Component
struct DrawerPreviewer {
  @State isShow: boolean = true

  @Builder
  Content() {
    Text('Context')
  }

  @Builder
  Parameters() {
    Text('Parameters')
  }

  build() {
    NavDestination() {
      Drawer({
        title: '标题',
        showParameters: $isShow,
        content: this.Content,
        parameters: this.Parameters
      })
    }
  }
}