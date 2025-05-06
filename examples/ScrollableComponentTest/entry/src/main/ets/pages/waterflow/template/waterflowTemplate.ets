import router from '@ohos.router'
import { MyDataSource } from '../mydatasource'

@Entry
@Component
struct Test_gridTemplate_2 {
  // 每个组件颜色
  @State colors: number[] = [0xFFC0CB, 0xDA70D6, 0x6B8E23, 0x6A5ACD, 0x00FFFF, 0x00FF7F]
  // 每个组件宽度
  @State flowItemWidth: number[] = [90, 90, 90, 90]
  // 每个组件高度
  @State flowItemHeight: number[] = [100, 100, 100, 100]
  // 列数
  private columnNum: number = 4
  // 测试用例编号
  private testCaseNo: string = router.getParams()['testCase']
  // FlowItem 组件属性
  @State columnsTemplate: string = router.getParams()['columnsTemplate']
  @State rowsTemplate: string = router.getParams()['rowsTemplate']
  @State columnsGap: number = router.getParams()['columnsGap']
  @State rowsGap: number = router.getParams()['rowsGap']
  private columnsTemplateText: string = this.columnsTemplate
  private rowsTemplateText: string = this.rowsTemplate
  private columnsGapText: number = this.columnsGap
  private rowsGapText: number = this.rowsGap
  @State layoutDirection: FlexDirection = router.getParams()['layoutDirection']
  private dataSize = router.getParams()['dataSize']
  // 数据源
  datasource: MyDataSource = new MyDataSource(router.getParams()['dataSize'])
  // 滚动条
  scroller: Scroller = new Scroller()
  private imageUri: string = ''
  @State layoutDirectionIndex: number = 0

  // 页脚
  @Builder
  Footer() {
    Column() {
      Text(`Footer`)
        .backgroundColor(Color.Red)
        .fontSize(20)
        .width(50)
        .height(20)
    }
  }

  build() {
    Row() {
      Column() {
        Button('返回首页', { type: ButtonType.Normal, stateEffect: true })
          .borderRadius(8)
          .backgroundColor(0x317aff)
          .width(200)
          .onClick((event: ClickEvent) => {
            router.back()
          })

        Text('测试用例编号：' + this.testCaseNo)
          .fontSize(12)
          .fontWeight(500)


        WaterFlow({ footer: this.Footer, scroller: this.scroller }) {
          LazyForEach(this.datasource, (item1: number) => {

            if (item1 % this.columnNum == 0) {
              FlowItem() {
                Column() {
                  Text('N' + item1).fontSize(12).height('20%')
                  Image('res/waterFlowTest (' + (item1 % this.columnNum) + ').jpg').height('80%')
                }
              }
              .width(this.flowItemWidth[item1 % this.columnNum])
              .backgroundColor(this.colors[item1 % this.columnNum])
            } else if (item1 % this.columnNum == 1) {
              FlowItem() {
                Column() {
                  Text('N' + item1).fontSize(12).height('20%')
                  Image('res/waterFlowTest (' + (item1 % this.columnNum) + ').jpg').height('80%')
                }
              }
              .width(this.flowItemWidth[item1 % this.columnNum])
              .backgroundColor(this.colors[item1 % this.columnNum])
            } else if (item1 % this.columnNum == 2) {
              FlowItem() {
                Column() {
                  Text('N' + item1).fontSize(12).height('20%')
                  Image('res/waterFlowTest (' + (item1 % this.columnNum) + ').jpg').height('80%')
                }
              }
              .width(this.flowItemWidth[item1 % this.columnNum])
              .backgroundColor(this.colors[item1 % this.columnNum])
            } else if (item1 % this.columnNum == 3) {
              FlowItem() {
                Column() {
                  Text('N' + item1).fontSize(12).height('20%')
                  Image('res/waterFlowTest (' + (item1 % this.columnNum) + ').jpg').height('80%')
                }
              }
              .width(this.flowItemWidth[item1 % this.columnNum])
              .backgroundColor(this.colors[item1 % this.columnNum])
            }

          }, item1 => item1)
        }
        .width(360)
        .height(400)
        .columnsTemplate(this.columnsTemplate)
        .rowsTemplate(this.rowsTemplate)
        .layoutDirection(this.layoutDirection)
        .columnsGap(this.columnsGap)
        .rowsGap(this.rowsGap)

        Row() {
          Column() {
            TextInput({ placeholder: 'columnsTemplate', text: this.columnsTemplateText })
              .fontSize(14)
              .fontWeight(500)
              .fontColor(Color.Black)
              .backgroundColor(Color.White)
              .width(200)
              .height(40)
              .caretColor(Color.Black)
              .enterKeyType(EnterKeyType.Done)
              .type(InputType.Normal)
              .onChange((value: string) => {
                this.columnsTemplateText = value
              })
              .onSubmit((enterKey: EnterKeyType) => {
                this.columnsTemplate = this.columnsTemplateText
              })
              .borderStyle(BorderStyle.Solid)
              .borderWidth('1px')
              .borderColor(Color.Black)
              .borderRadius(0)
          }
          .width('60%')

          Column() {
            TextInput({ placeholder: 'columnsGap', text: String(this.columnsGapText) })
              .fontSize(14)
              .fontWeight(500)
              .fontColor(Color.Black)
              .backgroundColor(Color.White)
              .width(100)
              .height(40)
              .caretColor(Color.Black)
              .enterKeyType(EnterKeyType.Done)
              .type(InputType.Normal)
              .onChange((value: string) => {
                this.columnsGapText = Number(value)
              })
              .onSubmit((enterKey: EnterKeyType) => {
                this.columnsGap = this.columnsGapText
              })
              .borderStyle(BorderStyle.Solid)
              .borderWidth('1px')
              .borderColor(Color.Black)
              .borderRadius(0)
          }
          .width('30%')
        }
        .height(50)


        Row() {
          Column() {
            TextInput({ placeholder: 'rowsTemplate', text: this.rowsTemplateText })
              .fontSize(14)
              .fontWeight(500)
              .fontColor(Color.Black)
              .backgroundColor(Color.White)
              .width(200)
              .height(40)
              .caretColor(Color.Black)
              .enterKeyType(EnterKeyType.Done)
              .type(InputType.Normal)
              .onChange((value: string) => {
                this.rowsTemplateText = value
              })
              .onSubmit((enterKey: EnterKeyType) => {
                this.rowsTemplate = this.rowsTemplateText
              })
              .borderStyle(BorderStyle.Solid)
              .borderWidth('1px')
              .borderColor(Color.Black)
              .borderRadius(0)
          }
          .width('60%')

          Column() {
            TextInput({ placeholder: 'rowsGap', text: String(this.rowsGapText) })
              .fontSize(14)
              .fontWeight(500)
              .fontColor(Color.Black)
              .backgroundColor(Color.White)
              .width(100)
              .height(40)
              .caretColor(Color.Black)
              .enterKeyType(EnterKeyType.Done)
              .type(InputType.Normal)
              .onChange((value: string) => {
                this.rowsGapText = Number(value)
              })
              .onSubmit((enterKey: EnterKeyType) => {
                this.rowsGap = this.rowsGapText
              })
              .borderStyle(BorderStyle.Solid)
              .borderWidth('1px')
              .borderColor(Color.Black)
              .borderRadius(0)
          }
          .width('30%')
        }
        .height(50)


        Row() {
          Select([{ value: 'undefined', icon: this.imageUri }
            , { value: 'FlexDirection.Column', icon: this.imageUri }
            , { value: 'FlexDirection.ColumnReverse', icon: this.imageUri }
            , { value: 'FlexDirection.Row', icon: this.imageUri }
            , { value: 'FlexDirection.RowReverse', icon: this.imageUri }])
            .value('请选择布局方向')
            .selected(this.layoutDirectionIndex)
            .font({ size: 14 })
            .onSelect((index: number, value: string) => {
              this.layoutDirectionIndex = index
              if (index === 0) {
                this.layoutDirection = undefined
              } else if (index === 1) {
                this.layoutDirection = FlexDirection.Column
              } else if (index === 2) {
                this.layoutDirection = FlexDirection.ColumnReverse
              } else if (index === 3) {
                this.layoutDirection = FlexDirection.Row
              } else if (index === 4) {
                this.layoutDirection = FlexDirection.RowReverse
              }
            })
            .width(300)
            .height('100%')
            .optionFont({ size: 18, weight: 500 })

        }
        .height(50)

        Row() {
          Column() {
            Button('AddLastItem', { type: ButtonType.Normal, stateEffect: true })
              .borderRadius(8)
              .backgroundColor(0x317aff)
              .width('100%')
              .height(30)
              .onClick((event: ClickEvent) => {
                this.datasource.AddLastItem()
              })
          }.width('36%')

          Column() {
            Button('Add1stItem', { type: ButtonType.Normal, stateEffect: true })
              .borderRadius(8)
              .backgroundColor(0x317aff)
              .width('100%')
              .height(30)
              .onClick((event: ClickEvent) => {
                this.datasource.Add1stItem()
              })
          }.width('33%')

          Column() {
            Button('Reload', { type: ButtonType.Normal, stateEffect: true })
              .borderRadius(8)
              .backgroundColor(0x317aff)
              .width('100%')
              .height(30)
              .onClick((event: ClickEvent) => {
                this.datasource.Reload()
              })
          }.width('28%')
        }
        .height(36)

        Row() {
          Column() {
            Button('DeleteLastItem', { type: ButtonType.Normal, stateEffect: true })
              .borderRadius(8)
              .backgroundColor(0x317aff)
              .width('100%')
              .height(30)
              .onClick((event: ClickEvent) => {
                this.datasource.DeleteLastItem()
              })
          }.width('45%')

          Column() {
            Button('Delete2ndItem', { type: ButtonType.Normal, stateEffect: true })
              .borderRadius(8)
              .backgroundColor(0x317aff)
              .width('100%')
              .height(30)
              .onClick((event: ClickEvent) => {
                this.datasource.Delete2ndItem()
              })
          }.width('45%')
        }
        .height(36)
      }
      .width('100%')
    }
    .height('100%')
  }
}