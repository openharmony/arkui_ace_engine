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

import { ComponentContent, UIContext } from '@kit.ArkUI';
import { WaterFlowDataSource } from './WaterFlowNoDataSource';

class Params {
  text: string = '';

  constructor(text: string) {
    this.text = text;
  }
}

// Builder函数：构建尾部组件的UI结构
@Builder
function buildText(params: Params) {
  Column() {
    Text(params.text)
      .fontSize(20)
      .fontWeight(FontWeight.Bold)
      .margin(20)
  }
}

@Entry
@Component
struct waterFlowNoIndex {
  @State message1: string = '已经到底了';
  @State message2: string = '加载更多';
  @State colors: number[] = [0xD5D5D5, 0x7F7F7F, 0xF7F7F7];
  @State minSize: number = 80;
  @State maxSize: number = 180;

  // UI上下文：用于创建ComponentContent
  context: UIContext = this.getUIContext();

  // 动态尾部组件：使用ComponentContent创建可更新的尾部组件
  // ComponentContent<Params>：泛型指定参数类型
  // wrapBuilder<[Params]>(buildText)：包装Builder函数
  // new Params(this.message1)：初始参数，显示'已经到底了'
  footerContent: ComponentContent<Params> = new ComponentContent<Params>(
    this.context,
    wrapBuilder<[Params]>(buildText),
    new Params(this.message1)
  );

  dataSource: WaterFlowDataSource = new WaterFlowDataSource();
  private itemWidthArray: number[] = [];
  private itemHeightArray: number[] = [];

  // 计算FlowItem宽/高
  getSize() {
    let ret = Math.floor(Math.random() * this.maxSize);
    return (ret > this.minSize ? ret : this.minSize);
  }

  // 设置FlowItem宽/高数组
  setItemSizeArray() {
    for (let i = 0; i < 1; i++) {
      this.itemWidthArray.push(this.getSize());
      this.itemHeightArray.push(this.getSize());
    }
  }

  // 组件生命周期：在组件即将出现时初始化尺寸数组
  aboutToAppear() {
    this.setItemSizeArray();
  }

  build() {
    Row() {
      Column() {
        WaterFlow({ footerContent: this.footerContent }) {
          LazyForEach(this.dataSource, (item: number) => {
            FlowItem() {
              Column() {
                Text('N' + item).fontSize(12).height('16')
              }
              .width('100%')
              .height(this.itemHeightArray[item % 100])
              .backgroundColor(this.colors[item % 3])
              .justifyContent(FlexAlign.Center)
              .alignItems(HorizontalAlign.Center)
            }
          }, (item: number) => item.toString())
        }
        .columnsTemplate('1fr')
        .height('90%')
      }
      .width('100%')
      .height('100%')
    }
    .height('100%')
  }
}
