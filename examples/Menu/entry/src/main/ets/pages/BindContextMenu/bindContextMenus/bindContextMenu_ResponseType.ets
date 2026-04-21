/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

@Entry
@Component
struct BindContextMenu_23 {
  @State longPress: string = 'LONG_PRESS';
  @State rightClick: string = 'RIGHT_CLICK';
  @State type: ResponseType = ResponseType.LongPress;

  @Builder
  MenuBuilderWithParam() {
    Flex({ direction: FlexDirection.Column, justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
      Text('Current ResponseType = ' + (this.type === 0 ? 'RIGHT_CLICK' : 'LONG_PRESS'))
      Divider().height(10)
      if (this.type === ResponseType.LongPress) {
        Text('Item: ' + this.longPress)
          .fontSize(20)
          .width(200)
          .height(20)
          .textAlign(TextAlign.Center)
      }
      if (this.type === ResponseType.RightClick) {
        Text('Item: ' + this.rightClick)
          .fontSize(20)
          .width(200)
          .height(20)
          .textAlign(TextAlign.Center)
      }
    }
  }
  @Builder
  MyPreview() {
    Column() {
      Image($r('app.media.app_icon'))
        .width(800)
        .height(800)
    }
  }
  build() {
    Column() {
      Button('BindContextMenu长按和右键点击触发菜单')
        .bindContextMenu(this.MenuBuilderWithParam, this.type, {
          enableArrow: true,
          transition: TransitionEffect.asymmetric(TransitionEffect.OPACITY
            .animation({ duration: 3000, curve: Curve.Sharp })
            .combine(TransitionEffect.scale({ x: 1.5, y: 1.5 })
              .animation({ duration: 3000, curve: Curve.Sharp })),
            TransitionEffect.OPACITY.animation({ duration: 100, curve: Curve.Smooth })
              .combine(TransitionEffect.scale({ x: 0.5, y: 0.5 })
                .animation({ duration: 100, curve: Curve.Smooth })))
        })
      Button('preview')
        .bindContextMenu(this.MenuBuilderWithParam, this.type, {
          preview: this.MyPreview,
          enableArrow: true,
          transition: TransitionEffect.asymmetric(TransitionEffect.OPACITY
            .animation({ duration: 3000, curve: Curve.Sharp })
            .combine(TransitionEffect.scale({ x: 1.5, y: 1.5 })
              .animation({ duration: 3000, curve: Curve.Sharp })),
            TransitionEffect.OPACITY.animation({ duration: 100, curve: Curve.Smooth })
              .combine(TransitionEffect.scale({ x: 0.5, y: 0.5 })
                .animation({ duration: 100, curve: Curve.Smooth })))
        })
    }
    .height('100%')
    .width('100%')
    .backgroundColor('#f0f0f0')
  }
}