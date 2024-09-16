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
  @BuilderParam parameters: () => void;
  @Consume('router') router: NavPathStack

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
          Row() {
            Text('参数列表')
              .fontSize($r('sys.float.ohos_id_text_size_headline7'))
              .fontWeight(FontWeight.Bold)

            Blank()

            IconButton($r('sys.media.ohos_ic_public_close'), () => {
              animateTo({ curve: curves.interpolatingSpring(0, 1, 328, 36) }, () => {
                this.showParameters = false;
              });
            })
          }.width('100%').height(56)

          this.parameters()
        }
        .backgroundColor($r('sys.color.ohos_id_color_dialog_bg'))
        .borderRadius({ topLeft: 30, topRight: 30 })
        .constraintSize({ maxWidth: 480, maxHeight: '70%', minHeight: '40%' })
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
    .height('100%')
    .width('100%')
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