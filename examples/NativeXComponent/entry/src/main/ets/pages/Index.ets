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

@Entry
@Component
struct Index {
  pageInfos: NavPathStack = new NavPathStack();
  isUseInterception: boolean = false;

  build() {
    Navigation(this.pageInfos) {
      Tabs() {
        TabContent() {
          Column() {
            Button('点击此处进入', { stateEffect: true, type: ButtonType.Capsule })
              .width('80%')
              .height(40)
              .margin(20)
              .onClick(() => {
                this.pageInfos.pushPath({ name: 'SurfaceHolderDeclarative' });
              })
            Text('  使用ArkTS声明式方法创建XComponent，并使用SurfaceHolder相关接口')
          }
          .width('100%')
          .height('100%')
          .justifyContent(FlexAlign.Start)
        }
        .tabBar(SubTabBarStyle.of('声明式 SurfaceHolder')
          .labelStyle({
            overflow: TextOverflow.Clip,
            maxLines: 2,
            minFontSize: 10,
            maxFontSize: 10,
            heightAdaptivePolicy: TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST,
            font: { size: 20 }
          }))

        TabContent() {
          Column() {
            Button('点击此处进入', { stateEffect: true, type: ButtonType.Capsule })
              .width('80%')
              .height(40)
              .margin(20)
              .onClick(() => {
                this.pageInfos.pushPath({ name: 'SurfaceHolderTypeNode' });
              })
            Text('  使用自定义节点创建XComponent，并使用SurfaceHolder相关接口')
          }
          .width('100%')
          .height('100%')
          .justifyContent(FlexAlign.Start)
        }
        .tabBar(SubTabBarStyle.of('自定义节点 SurfaceHolder')
          .labelStyle({
            overflow: TextOverflow.Clip,
            maxLines: 2,
            minFontSize: 10,
            maxFontSize: 10,
            heightAdaptivePolicy: TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST,
            font: { size: 20 }
          }))

        TabContent() {
          Column() {
            Button('点击此处进入', { stateEffect: true, type: ButtonType.Capsule })
              .width('80%')
              .height(40)
              .margin(20)
              .onClick(() => {
                this.pageInfos.pushPath({ name: 'SurfaceHolderNDK' });
              })
            Text('  使用NDK接口创建XComponent，并使用SurfaceHolder相关接口')
          }
          .width('100%')
          .height('100%')
          .justifyContent(FlexAlign.Start)
        }
        .tabBar(SubTabBarStyle.of('NDK SurfaceHolder')
          .labelStyle({
            overflow: TextOverflow.Clip,
            maxLines: 2,
            minFontSize: 10,
            maxFontSize: 10,
            heightAdaptivePolicy: TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST,
            font: { size: 20 }
          }))

        TabContent() {
          Column() {
            Button('点击此处进入', { stateEffect: true, type: ButtonType.Capsule })
              .width('80%')
              .height(40)
              .margin(20)
              .onClick(() => {
                this.pageInfos.pushPath({ name: 'NativeXComponentDeclarative' });
              })
            Text('  使用ArkTS声明式方法创建XComponent，并使用NativeXComponent相关接口')
          }
          .width('100%')
          .height('100%')
          .justifyContent(FlexAlign.Start)
        }
        .tabBar(SubTabBarStyle.of('声明式 NativeXComponent')
          .labelStyle({
            overflow: TextOverflow.Clip,
            maxLines: 2,
            minFontSize: 10,
            maxFontSize: 10,
            heightAdaptivePolicy: TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST,
            font: { size: 20 }
          }))

        TabContent() {
          Column() {
            Button('点击此处进入', { stateEffect: true, type: ButtonType.Capsule })
              .width('80%')
              .height(40)
              .margin(20)
              .onClick(() => {
                this.pageInfos.pushPath({ name: 'NativeXComponentNDK' });
              })
            Text('  使用NDK接口创建XComponent，并使用NativeXComponent相关接口')
          }
          .width('100%')
          .height('100%')
          .justifyContent(FlexAlign.Start)
        }
        .tabBar(SubTabBarStyle.of('NDK NativeXComponent')
          .labelStyle({
            overflow: TextOverflow.Clip,
            maxLines: 2,
            minFontSize: 10,
            maxFontSize: 10,
            heightAdaptivePolicy: TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST,
            font: { size: 20 }
          }))
      }
    }.title('XComponent')
  }
}
