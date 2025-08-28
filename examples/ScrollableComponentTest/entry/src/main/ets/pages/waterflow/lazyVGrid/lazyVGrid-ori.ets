import { BuilderNode, LengthMetrics, NodeController } from '@kit.ArkUI';
import { MyDataSource } from './BasicDataSource';

//import { WaterFlowDataSource } from './WaterFlowDataSource';


// xxx.ets
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
  @Prop columnsGap: number = 0;
  @Prop rowsGap: number = 0;
  @Prop template: string = '1fr';
  arr: MyDataSource = new MyDataSource();

  aboutToAppear(): void {
    for (let i = 0; i < 40; i++) {
      this.arr.pushData(i.toString());
    }
  }

  build() {
    LazyVGridLayout() {
      LazyForEach(this.arr, (item: string) => {
        Text('AItem' + item)
          .height(64)
          .borderColor(Color.Black)
          .width('100%')
          .borderWidth(1)
          .onAppear(() => {
            console.log('onAppear:' + item)
          })
          .onDisAppear(() => {
            console.log('onDisAppear:' + item)
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
  MyGrid({ template: params.template })
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

@Component
struct MyStack {
  build() {

    Stack() {
      Text('stack').width('100%').backgroundColor(Color.Blue)
    }
  }
}

@Entry
@Component
struct ListItemExample {
  arr: MyDataSource = new MyDataSource();
  @State rowsGap: number = 0;
  @State columnsGap: number = 0;
  @State template: string = '1fr';
  @State modifier: MyModifier = new MyModifier();
  @State isClip: boolean = true;
  @State gridHeight?: number = undefined;
  @State gridWidth?: number = undefined;
  private myNodeController: MyNodeController = new MyNodeController();
  scroller: Scroller = new Scroller();
  @State waterFlowLayoutModer: WaterFlowLayoutMode = WaterFlowLayoutMode.SLIDING_WINDOW;
  @State h: number = 64;
  @State fontColor: string = '#182431';
  @State selectedFontColor: string = '#007DFF';
  @State currentIndex: number = 0;
  @State selectedIndex: number = 0;
  private controller: TabsController = new TabsController();
  @State opacityLazy: number = 1;
  @State aspectRatioLazy: number = 1;

  @Builder
  tabBuilder(index: number, name: string) {
    Column() {
      Text(name)
        .fontColor(this.selectedIndex === index ? this.selectedFontColor : this.fontColor)
        .fontSize(16)
        .fontWeight(this.selectedIndex === index ? 500 : 400)
        .lineHeight(22)
      Divider()
        .strokeWidth(2)
        .color('#007DFF')
        .opacity(this.selectedIndex === index ? 1 : 0)
    }.width('100%')
  }

  aboutToAppear() {

    for (let i = 0; i < 50; i++) {
      this.arr.pushData(i.toString());
    }
  }

  build() {
    Column() {
      Scroll() {
        Column() {
          Row() {
            Button('mode:' + this.waterFlowLayoutModer).onClick(() => {
              this.waterFlowLayoutModer = (this.waterFlowLayoutModer == 0 ? 1 : 0);
            })
            Button('1列').onClick(() => {
              this.template = '1fr'
              this.modifier.template = this.template
              this.myNodeController.update({
                template: this.template,
                columnsGap: this.columnsGap,
                rowsGap: this.rowsGap
              })
            })
            Button('2列').onClick(() => {
              this.template = '1fr 1fr'
              this.modifier.template = this.template
              this.myNodeController.update({
                template: this.template,
                columnsGap: this.columnsGap,
                rowsGap: this.rowsGap
              })
            })
            Button('3列').onClick(() => {
              this.template = '1fr 1fr 1fr'
              this.modifier.template = this.template
              this.myNodeController.update({
                template: this.template,
                columnsGap: this.columnsGap,
                rowsGap: this.rowsGap
              })
            })
            Button('2列不等宽').onClick(() => {
              this.template = '2fr 3fr'
              this.modifier.template = this.template
              this.myNodeController.update({
                template: this.template,
                columnsGap: this.columnsGap,
                rowsGap: this.rowsGap
              })
            })
          }

          Row() {
            Button('行Gap+').onClick(() => {
              this.rowsGap = this.rowsGap + 20
              this.modifier.rowsGap = this.rowsGap
              this.myNodeController.update({
                template: this.template,
                columnsGap: this.columnsGap,
                rowsGap: this.rowsGap
              })
            })
            Text(this.rowsGap.toString())
            Button('行Gap-').onClick(() => {
              if (this.rowsGap > -2) {
                this.rowsGap = this.rowsGap - 2
                this.modifier.rowsGap = this.rowsGap
                this.myNodeController.update({
                  template: this.template,
                  columnsGap: this.columnsGap,
                  rowsGap: this.rowsGap
                })
              }
            })
            Button('列Gap+').onClick(() => {
              this.columnsGap = this.columnsGap + 2
              this.modifier.columnsGap = this.columnsGap
              this.myNodeController.update({
                template: this.template,
                columnsGap: this.columnsGap,
                rowsGap: this.rowsGap
              })
            })
            Text(this.columnsGap.toString())
            Button('列Gap-').onClick(() => {
              if (this.columnsGap > -2) {
                this.columnsGap = this.columnsGap - 2
                this.modifier.columnsGap = this.columnsGap
                this.myNodeController.update({
                  template: this.template,
                  columnsGap: this.columnsGap,
                  rowsGap: this.rowsGap
                })
              }
            })
          }

          Row() {
            Button('删除全部').onClick(() => {
              this.arr.clearData();
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
          }

          Row() {
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

          Row() {

            Button('增大第二个LazyGrid子节点高度').onClick(() => {
              this.h += 10;
            })
            Button('减小第二个LazyGrid子节点高度').onClick(() => {
              this.h -= 10;
            })


          }

          Row() {

            Button('scrollTo y 800').onClick(() => {
              this.scroller.scrollTo({ xOffset: 0, yOffset: 800 })
            })
            Button('scrollTo y 1600').onClick(() => {
              this.scroller.scrollTo({ xOffset: 0, yOffset: 1600 })
            })
            Button('opacity ++').onClick(() => {
              this.opacityLazy += 0.2;
            })
            Button('opacity --').onClick(() => {
              this.opacityLazy -= 0.2;
            })
          }

        }

      }.height('20%')

      Stack() {
        WaterFlow({ layoutMode: this.waterFlowLayoutModer, scroller: this.scroller }) {
          FlowItem() {
            NodeContainer(this.myNodeController)
          }
          .height(this.gridHeight)
          .width(this.gridWidth)

          FlowItem() {
            LazyVGridLayout() {
              LazyForEach(this.arr, (item: string) => {
                Text('Item' + item)
                  .height(this.h)
                  .onAppear(() => {
                    console.log('YYL:onAppear:' + item)
                  })
                  .onDisAppear(() => {
                    console.log('YYL:onDisAppear:' + item)
                  })
                  .borderColor(Color.Black)
                  .width('100%')
                  .borderWidth(1)
                  .backgroundColor(Color.Red)
              })
            }
            .width(400)
            .opacity(this.opacityLazy)
            .border({
              width: {
                left: 3,
                right: 6,
                top: 0,
                bottom: 15
              },
              color: {
                left: '#e3bbbb',
                right: Color.Blue,
                top: Color.Red,
                bottom: Color.Green
              },
              radius: {
                topLeft: 10,
                topRight: 20,
                bottomLeft: 40,
                bottomRight: 80
              },
              style: {
                left: BorderStyle.Dotted,
                right: BorderStyle.Dotted,
                top: BorderStyle.Solid,
                bottom: BorderStyle.Dashed
              }
            })
            .attributeModifier(this.modifier)
          }

          FlowItem() {
            MyGrid()
          }
        }
        .width('90%')
        .height(this.isClip ? '100%' : '40%')
        .clip(this.isClip)
        .scrollBar(BarState.On)
        .backgroundColor(Color.Pink)
      }
      .clip(true)
      .layoutWeight(1)
    }.width('100%').height('100%')
  }
}