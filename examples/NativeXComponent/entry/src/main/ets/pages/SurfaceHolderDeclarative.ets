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
// [Start surface_holder_declarative_ets]
import native from 'libnativerender.so';

// [StartExclude surface_holder_declarative_ets]
@Builder
export function SurfaceHolderDeclarativeBuilder(name: string, param: Object) {
  SurfaceHolderDeclarative()
}
// [EndExclude surface_holder_declarative_ets]

@Component
export struct SurfaceHolderDeclarative {
  @State currentStatus: string = 'init';
  private xcNode: FrameNode | null = null;

  build() {
    NavDestination() {
      // [StartExclude surface_holder_declarative_ets]
      Column() {
        Row() {
          Text('SurfaceHolder Declarative Sample')
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
      // [EndExclude surface_holder_declarative_ets]
        Column({ space: 10 }) {
          // 创建XComponent组件
          // [Start surface_holder_declarative_create_ets]
          XComponent({
            type: XComponentType.SURFACE,
          })
            .id('XComponentSurfaceHolder')
            .onAttach(() => {
              this.xcNode = this.getUIContext().getAttachedFrameNodeById('XComponentSurfaceHolder');
              if (!this.xcNode) {
                return;
              }
              native.bindNode('XComponentSurfaceHolder', this.xcNode); // 跨语言调用至Native侧获取SurfaceHolder并绑定Surface生命周期回调
              this.currentStatus = 'index';
            })
            .onDetach(() => {
              native.unbindNode('XComponentSurfaceHolder');
              this.xcNode = null;
            })
          // [End surface_holder_declarative_create_ets]
          // [StartExclude surface_holder_declarative_ets]
          Text(this.currentStatus)
            .fontSize('24fp')
            .fontWeight(500)
        }
        .onClick(() => {
          let hasChangeColor: boolean = false;
          if (this.xcNode) {
            hasChangeColor = native.getStatusForSurfaceHolder(this.xcNode)?.hasChangeColor;
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
              if (this.xcNode) {
                native.drawPatternForSurfaceHolder(this.xcNode);
                let hasDraw: boolean = false;
                hasDraw = native.getStatusForSurfaceHolder(this.xcNode)?.hasDraw;
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
      // [EndExclude surface_holder_declarative_ets]
    }
  }
}
// [End surface_holder_declarative_ets]
