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
// [Start surface_holder_ndk_ets]
import nativeNode from 'libnativerender.so';
import { NodeContent } from '@kit.ArkUI';
// [StartExclude surface_holder_ndk_ets]
@Builder
export function SurfaceHolderNDKBuilder(name: string, param: Object) {
  SurfaceHolderNDK()
}
// [EndExclude surface_holder_ndk_ets]

@Component
export struct SurfaceHolderNDK {
  @State currentStatus: string = 'init';
  private nodeContent: NodeContent = new NodeContent();

  aboutToAppear(): void {
    nativeNode.createNativeNode(this.nodeContent, 'SurfaceHolderNDK');
    this.currentStatus = 'index'
  }

  build() {
    NavDestination() {
      Column() {
        // [StartExclude surface_holder_ndk_ets]
        Row() {
          Text('SurfaceHolder NDK Sample')
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
        // [EndExclude surface_holder_ndk_ets]
        Column({ space: 10 }) {
          ContentSlot(this.nodeContent);
          // [StartExclude surface_holder_ndk_ets]
          Column().height(20)
          Text(this.currentStatus)
            .fontSize('24fp')
            .fontWeight(500)
        }
        .onClick(() => {
          let hasChangeColor: boolean = false;
          if (nativeNode.getStatus()) {
            hasChangeColor = nativeNode.getStatus('SurfaceHolderNDK').hasChangeColor;
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
              nativeNode.drawPattern('SurfaceHolderNDK');
              let hasDraw: boolean = false;
              const status = nativeNode.getStatus('SurfaceHolderNDK')
              if (status) {
                hasDraw = status.hasDraw;
              }
              if (hasDraw) {
                this.currentStatus = 'draw star';
              }
            })
            .width('53.6%')
            .height(40)
        }
        .width('100%')
        .justifyContent(FlexAlign.Center)
        .alignItems(VerticalAlign.Bottom)
        .layoutWeight(1)
        // [EndExclude surface_holder_ndk_ets]
      }
      .width('100%')
      .height('100%')
    }
  }
}
// [End surface_holder_ndk_ets]