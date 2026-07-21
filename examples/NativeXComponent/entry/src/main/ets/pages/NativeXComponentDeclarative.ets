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

import XComponentContext from '../interface/XComponentContext';

@Builder
export function NativeXComponentDeclarativeBuilder(name: string, param: Object) {
  NativeXComponentDeclarative()
}

@Component
export struct NativeXComponentDeclarative {
  @State currentStatus: string = 'init';
  private xComponentContext: XComponentContext | undefined = undefined;

  build() {
    NavDestination() {
      Column() {
        Row() {
          Text('NativeXComponent Declarative Sample')
            .fontSize('24fp')
            .fontWeight(500)
            .margin({
              left: 24,
              top: 12
            })
        }
        .margin({ top: 24 })
        .width('100%')
        .height(56)

        Column({ space: 10 }) {
          // [Start native_xcomponent_declarative_create_ets]
          XComponent({
            id: 'xcomponentId',
            type: XComponentType.SURFACE,
            libraryname: 'nativerender' // 利用id和libraryname属性在Native侧获取NativeXcomponent并绑定Surface生命周期
          })
            .onLoad((xComponentContext) => {
              this.xComponentContext = xComponentContext as XComponentContext;
              this.currentStatus = 'index';
            })
            .onDestroy(() => {
              console.info('onDestroy');
            })
            .id('xcomponent')
          // [End native_xcomponent_declarative_create_ets]

          Text(this.currentStatus)
            .fontSize('24fp')
            .fontWeight(500)
        }
        .onClick(() => {
          let hasChangeColor: boolean = false;
          if (this.xComponentContext && this.xComponentContext.getStatusX()) {
            hasChangeColor = this.xComponentContext.getStatusX().hasChangeColor;
          }
          if (hasChangeColor) {
            this.currentStatus = 'change color';
          }
        })
        .margin({
          top: 27,
          left: 12,
          right: 12
        })
        .height('40%')
        .width('90%')

        Row() {
          Button('Draw Star')
            .fontSize('16fp')
            .fontWeight(500)
            .margin({ bottom: 24 })
            .onClick(() => {
              if (this.xComponentContext) {
                this.xComponentContext.drawPatternX();
                let hasDraw: boolean = false;
                if (this.xComponentContext.getStatusX()) {
                  hasDraw = this.xComponentContext.getStatusX().hasDraw;
                }
                if (hasDraw) {
                  this.currentStatus = 'draw star';
                }
              }
            })
            .width('53.6%')
            .height(40)
        }
        .width('100%')
        .justifyContent(FlexAlign.Center)
        .alignItems(VerticalAlign.Bottom)
        .layoutWeight(1)
      }
      .width('100%')
      .height('100%')
    }
  }
}