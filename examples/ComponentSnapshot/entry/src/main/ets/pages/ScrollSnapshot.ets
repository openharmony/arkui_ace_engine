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

import { ScrollSnapshot } from '../view/ScrollSnapshot';

@Entry
@Component
struct Index {
  private navPathStack: NavPathStack = new NavPathStack();

  @Builder
  PageMap(name: string) {
    if (name === 'ScrollSnapshot') {
      ScrollSnapshot();
    }
  }

  build() {
    Navigation(this.navPathStack) {
      Column({ space: 12 }) {
        // 请将$r('app.string.title_scroll_snapshot')替换为实际资源文件，在本示例中该资源文件的value值为"Scroll Screenshot"
        Button($r('app.string.title_scroll_snapshot'))
          .width('100%')
          .onClick(() => {
            this.navPathStack.pushPathByName('ScrollSnapshot', '');
          })
      }
      .justifyContent(FlexAlign.End)
      .height('100%')
      .width('100%')
      .padding({
        bottom: (AppStorage.get<number>('naviIndicatorHeight') ?? 0) + 16,
        left: 16,
        right: 16
      });
    }
    .mode(NavigationMode.Stack)
    // 请将$r('app.string.EntryAbility_label')替换为实际资源文件，在本示例中该资源文件的value值为"LongSnapshotPractice"
    .title($r('app.string.EntryAbility_label'))
    .expandSafeArea([SafeAreaType.SYSTEM], [SafeAreaEdge.BOTTOM, SafeAreaEdge.TOP])
    // $r('sys.color.background_secondary')需要替换为开发者所需的资源文件
    .backgroundColor($r('sys.color.background_secondary'))
    .navDestination(this.PageMap)
    .padding({ top: AppStorage.get<number>('statusBarHeight') ?? 0 });
  }
}