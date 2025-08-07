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

import { BuilderNode, LengthMetrics, NodeController } from '@kit.ArkUI';
import {LazyGridDataSource} from './LazyGridDataSource'

class MyModifier implements AttributeModifier<LazyVGridLayoutAttribute> {
  public rowsGap: number = 0;
  public columnsGap: number = 0;
  public template: string = '1fr';

  applyNormalAttribute(instance: LazyVGridLayoutAttribute): void {
    instance.rowsGap(LengthMetrics.vp(this.rowsGap))
      .columnsGap(LengthMetrics.vp(this.columnsGap))
      .columnsTemplate(this.template)
  }
}

@Component
struct MyGrid {
  @Prop columnsGap:number = 0;
  @Prop rowsGap:number = 0;
  @Prop template:string = '1fr';
  arr:LazyGridDataSource = new LazyGridDataSource();

  aboutToAppear(): void {
    for (let i = 0; i < 100; i++) {
      this.arr.pushData(i.toString());
    }
  }
  build() {
    LazyVGridLayout() {
      LazyForEach(this.arr, (item: string) => {
        Text('AItem' + item)
          .height( 64)
          .borderColor(Color.Black)
          .width('100%')
          .borderWidth(1)
          .onAppear(() => {
            console.log('YYL:onAppear:' + item);
          })
          .onDisAppear(() => {
            console.log('YYL:onDisAppear:' + item);
          })
      })
    }
    .rowsGap(LengthMetrics.vp(this.rowsGap))
    .columnsGap(LengthMetrics.vp(this.columnsGap))
    .columnsTemplate(this.template)
  }
}

@Builder
function buttonBuilder(params: Params) {
  MyGrid({template:params.template, rowsGap:params.rowsGap, columnsGap:params.columnsGap})
}

class Params {
  public template: string = '1fr';
  public rowsGap: number = 0;
  public columnsGap: number = 0;
}

class MyNodeController extends NodeController {
  private myGridNode: BuilderNode<[Params]> | null = null;
  private wrapBuilder: WrappedBuilder<[Params]> = wrapBuilder(buttonBuilder);

  makeNode(uiContext: UIContext): FrameNode {
    if (this.myGridNode == null) {
      this.myGridNode = new BuilderNode(uiContext);
      this.myGridNode.build(this.wrapBuilder, { template: '1fr' });
    }
    return this.myGridNode!.getFrameNode()!;
  }

  update(param: Params): void {
    this.myGridNode?.update(param);
  }
}

@Entry
@Component
struct ListItemExample {
  arr:LazyGridDataSource = new LazyGridDataSource();
  arr2:LazyGridDataSource = new LazyGridDataSource();
  @State rowsGap:number = 0;
  @State columnsGap:number = 0;
  @State template:string = '1fr';
  @State modifier: MyModifier = new MyModifier();
  @State isClip: boolean = true;
  @State gridHeight?: number = undefined;
  @State gridWidth?: number = undefined;
  private myNodeController: MyNodeController = new MyNodeController();
  build() {
    Column() {
      Scroll() {
        Flex({ wrap: FlexWrap.Wrap }) {
          Button('1列').onClick(() => {
            this.template = '1fr';
            this.modifier.template = this.template;
            this.myNodeController.update({template:this.template, columnsGap:this.columnsGap, rowsGap:this.rowsGap});
          })
          Button('2列').onClick(() => {
            this.template = '1fr 1fr';
            this.modifier.template = this.template;
            this.myNodeController.update({template:this.template, columnsGap:this.columnsGap, rowsGap:this.rowsGap});
          })
          Button('3列').onClick(() => {
            this.template = '1fr 1fr 1fr';
            this.modifier.template = this.template;
            this.myNodeController.update({template:this.template, columnsGap:this.columnsGap, rowsGap:this.rowsGap});
          })
          Button('2列不等宽').onClick(() => {
            this.template = '2fr 3fr';
            this.modifier.template = this.template;
            this.myNodeController.update({template:this.template, columnsGap:this.columnsGap, rowsGap:this.rowsGap});
          })
          Button('auto-fit100').onClick(() => {
            this.template = 'repeat(auto-fit, 100)';
            this.modifier.template = this.template;
            this.myNodeController.update({template:this.template, columnsGap:this.columnsGap, rowsGap:this.rowsGap});
          })
          Button('auto-fit150').onClick(() => {
            this.template = 'repeat(auto-fit, 150)';
            this.modifier.template = this.template;
            this.myNodeController.update({template:this.template, columnsGap:this.columnsGap, rowsGap:this.rowsGap});
          })
          Button('auto-fill100').onClick(() => {
            this.template = 'repeat(auto-fill, 100)';
            this.modifier.template = this.template;
            this.myNodeController.update({template:this.template, columnsGap:this.columnsGap, rowsGap:this.rowsGap});
          })
          Button('auto-fill150').onClick(() => {
            this.template = 'repeat(auto-fill, 150)';
            this.modifier.template = this.template;
            this.myNodeController.update({template:this.template, columnsGap:this.columnsGap, rowsGap:this.rowsGap});
          })
          Button('auto-stretch100').onClick(() => {
            this.template = 'repeat(auto-stretch, 100)';
            this.modifier.template = this.template;
            this.myNodeController.update({template:this.template, columnsGap:this.columnsGap, rowsGap:this.rowsGap});
          })
          Button('auto-stretch150').onClick(() => {
            this.template = 'repeat(auto-stretch, 150)';
            this.modifier.template = this.template;
            this.myNodeController.update({template:this.template, columnsGap:this.columnsGap, rowsGap:this.rowsGap});
          })
          Button('行Gap+').onClick(() => {
            this.rowsGap = this.rowsGap + 2;
            this.modifier.rowsGap = this.rowsGap;
            this.myNodeController.update({template:this.template, columnsGap:this.columnsGap, rowsGap:this.rowsGap});
          })
          Text(this.rowsGap.toString())
          Button('行Gap-').onClick(() => {
            if (this.rowsGap > -2) {
              this.rowsGap = this.rowsGap - 2;
              this.modifier.rowsGap = this.rowsGap;
              this.myNodeController.update({template:this.template, columnsGap:this.columnsGap, rowsGap:this.rowsGap});
            }
          })
          Button('列Gap+').onClick(() => {
            this.columnsGap = this.columnsGap + 2;
            this.modifier.columnsGap = this.columnsGap;
            this.myNodeController.update({template:this.template, columnsGap:this.columnsGap, rowsGap:this.rowsGap});
          })
          Text(this.columnsGap.toString())
          Button('列Gap-').onClick(() => {
            if (this.columnsGap > -2) {
              this.columnsGap = this.columnsGap - 2;
              this.modifier.columnsGap = this.columnsGap;
              this.myNodeController.update({template:this.template, columnsGap:this.columnsGap, rowsGap:this.rowsGap});
            }
          })
          Button('clip').onClick(() => {
            this.isClip = !this.isClip;
          })
          Button('删除第一个').onClick(() => {
            this.arr.shiftData();
          })
          Button('删除最后个').onClick(() => {
            this.arr.popData();
          })
          Button('头插1个').onClick(() => {
            this.arr.unshiftData(this.arr.firstPrevData());
          })
          Button('追加1个').onClick(() => {
            this.arr.pushData(this.arr.lastNextData());
          })
          Button('删除全部').onClick(() => {
            this.arr.clearData();
          })
          Button('追加100').onClick(() => {
            this.arr.appendData(100);
          })
          Button('1个Item').onClick(() => {
            this.arr.clearData();
            this.arr.appendData(1);
          })
          Button('无高度').onClick(() => {
            this.gridHeight = undefined;
          })
          Button('高500').onClick(() => {
            this.gridHeight = 500;
          })
          Button('高1000').onClick(() => {
            this.gridHeight = 1000;
          })
        }
      }.height('200')
      Stack() {
        WaterFlow() {
          FlowItem() {
            NodeContainer(this.myNodeController)
          }
          .height(this.gridHeight)
          .width(this.gridWidth)
          LazyVGridLayout() {
            LazyForEach(this.arr, (item: string) => {
              Text('Item' + item)
                .height(64)
                .onAppear(() => {
                  console.log('YYL:onAppear:' + item);
                })
                .onDisAppear(() => {
                  console.log('YYL:onDisAppear:' + item);
                })
                .borderColor(Color.Black)
                .width('100%')
                .borderWidth(1)
                .backgroundColor(Color.Red)
            })
          }
          .attributeModifier(this.modifier)
          .width(200)
          LazyForEach(this.arr2, (item:string) => {
            FlowItem() {
              MyGrid().padding({ top:100, bottom:100 })
            }.padding({ top:100, bottom:100 })
          })
        }.width('90%')
        .height(this.isClip ? '100%' : '40%')
        .clip(this.isClip)
        .scrollBar(BarState.On)
        .backgroundColor(Color.Pink)
      }
      .clip(true)
      .layoutWeight(1)
    }.width('100%').height('100%')
  }

  aboutToAppear(): void {
    for (let i = 0; i < 100; i++) {
      this.arr.pushData(i.toString());
    }
    for (let i = 0; i < 1; i++) {
      this.arr2.pushData(i.toString());
    }
  }
}
