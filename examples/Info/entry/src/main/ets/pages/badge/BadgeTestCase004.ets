import { MyComponent } from './MyComponent'

export class Model1 {
  public position?: BadgePosition | Position = undefined
  public color?: ResourceColor = undefined
  public badgeColor?: ResourceColor = undefined
  public borderColor?: ResourceColor = undefined
  public fontSize?: number | string = undefined
  public badgeSize?: number | string = undefined
  public fontWeight?: number | FontWeight | string = undefined
  public borderWidth?: Length = undefined

  constructor(
    position?: BadgePosition | Position,
    color?: ResourceColor,
    badgeColor?: ResourceColor,
    borderColor?: ResourceColor,
    fontSize?: number | string,
    badgeSize?: number | string,
    fontWeight?: number | FontWeight | string,
    borderWidth?: Length
  ) {
    this.position = position
    this.color = color
    this.badgeColor = badgeColor
    this.borderColor = borderColor
    this.fontSize = fontSize
    this.badgeSize = badgeSize
    this.fontWeight = fontWeight
    this.borderWidth = borderWidth
  }
}

interface testCase1Item {
  count?: number
  position?: BadgePosition | Position,
  maxCount?: number
  value?: string
  color?: ResourceColor,
  fontSize?: number | string,
  fontWeight?: number | string,
  badgeSize?: number | string,
  badgeColor?: ResourceColor,
  borderColor?: ResourceColor,
  borderWidth?: number
}

interface caseVisitsItem {
  title?: string
  visit?: Visibility
}

@Entry
@Component
struct BadgeTestCase004 {
  @State count?: number = undefined
  @State maxCount?: number = undefined
  @State value?: string = undefined
  @State model1: Model1 = new Model1()
  @State text?: string = undefined
  @State text1: string = 'text'
  @State clip1: boolean = false
  @State showText: boolean = false
  private index1: number = 0
  @State visible?: Visibility = undefined
  @State show: boolean = true
  @State direction1?: Direction | null = undefined

  @Builder
  myBuilder(value: string) {
    Column({ space: 2 }) {
      Text('自定义组件')
        .backgroundColor(Color.White)
        .key('nav10')
      TextInput({ placeholder: 'input' })
        .width(100)
        .caretColor(Color.White)
        .enabled(false)
    }
  }

  private testCase1: testCase1Item[] = [
    {
      count: 0,
      position: BadgePosition.Right,
      maxCount: 30,
      value: ''
    },
    {
      count: 150,
      position: BadgePosition.Right,
      maxCount: 30,
      value: 'info',
      color: Color.Yellow,
      fontSize: 16,
      fontWeight: FontWeight.Lighter,
      badgeSize: 20,
      badgeColor: Color.Green,
      borderColor: Color.Blue,
      borderWidth: 1
    },
    {
      count: 10.5,//小数取整
      position: BadgePosition.Left,
      maxCount: 10,
      value: 'infoqwertyuiopasdfghj',
      color: 0x5BA854,
      fontSize: 32,
      fontWeight: FontWeight.Regular,
      badgeSize: 25,
      badgeColor: 0xcc3333,
      borderColor: 0x9933cc,
      borderWidth: 0.8
    },
    {
      count: 100,
      position: BadgePosition.RightTop,
      maxCount: 10,
      value: '中文',//中文
      color: 0x5BA854,
      fontSize: 32,
      fontWeight: FontWeight.Regular,
      badgeSize: 25,
      badgeColor: 0xcc3333,
      borderColor: 0x9933cc,
      borderWidth: 0.8
    },
    {
      count: 100,
      position: BadgePosition.RightTop,
      maxCount: 30.4,//小数取整
      value: '123',
      color: 0x5BA854,
      fontSize: 32,
      fontWeight: FontWeight.Regular,
      badgeSize: 25,
      badgeColor: 0xcc3333,
      borderColor: 0x9933cc,
      borderWidth: 0.8
    },
    {
      count: 100,
      position: BadgePosition.RightTop,
      maxCount: 30,
      value: '123',
      color: 0x5BA854,
      fontSize: 32,
      fontWeight: FontWeight.Regular,
      badgeSize: 25,
      badgeColor: 'rgb(0, 255, 0)',//不同类型的颜色
      borderColor: 0x9933cc,
      borderWidth: 0.8
    },
    {
      count: 100,
      position: BadgePosition.RightTop,
      maxCount: 30000000,//超大max
      value: '123',
      color: 0x5BA854,
      fontSize: 32,
      fontWeight: FontWeight.Regular,
      badgeSize: 25,
      badgeColor: 0xcc3333,
      borderColor: 0x9933cc,
      borderWidth: 0.8
    }
  ]

  private setParam1(): void {
    this.count = this.testCase1[this.index1].count
    this.maxCount = this.testCase1[this.index1].maxCount
    this.value = this.testCase1[this.index1].value

    this.model1.position = this.testCase1[this.index1].position
    this.model1.color = this.testCase1[this.index1].color
    this.model1.badgeColor = this.testCase1[this.index1].badgeColor
    this.model1.borderColor = this.testCase1[this.index1].borderColor
    this.model1.fontSize = this.testCase1[this.index1].fontSize
    this.model1.badgeSize = this.testCase1[this.index1].badgeSize
    this.model1.fontWeight = this.testCase1[this.index1].fontWeight
    this.model1.borderWidth = this.testCase1[this.index1].borderWidth
  }

  private caseVisits: caseVisitsItem[] = [
    {
      title: 'Hidden',
      visit: Visibility.Hidden
    },
    {
      title: 'None',
      visit: Visibility.None
    },
    {
      title: 'Visible',
      visit: Visibility.Visible
    }
  ]

  build() {
    Scroll() {
      Column({ space: 5 }) {
        Column({ space: 5 }) {
          Text('Badge接口参数动态修改测试')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
            .margin({ top: 10 })
            .height(this.showText ? 'auto' : 0)
          Badge({
            count: this.count!,
            position: this.model1.position,
            maxCount: this.maxCount,
            style: {
              color: this.model1.color,
              fontSize: this.model1.fontSize,
              fontWeight: this.model1.fontWeight,
              badgeSize: this.model1.badgeSize,
              badgeColor: this.model1.badgeColor,
              borderColor: this.model1.borderColor,
              borderWidth: this.model1.borderWidth
            }
          }) {
            Text('message1')
              .width(100)
              .height(30)
              .fontSize(14)
              .fontColor('#182431')
              .backgroundColor(Color.Gray)
              .textAlign(TextAlign.Center)
              .borderRadius(5)
          }
          .margin({ top: 20 })
          .direction(this.direction1)


          Text('方法一')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .height(this.showText ? 'auto' : 0)

          Badge({
            value: this.value!,
            position: this.model1.position,
            style: {
              color: this.model1.color,
              fontSize: this.model1.fontSize,
              fontWeight: this.model1.fontWeight,
              badgeSize: this.model1.badgeSize,
              badgeColor: this.model1.badgeColor,
              borderColor: this.model1.borderColor,
              borderWidth: this.model1.borderWidth
            }
          }) {
            Text('message1')
              .width(100)
              .height(30)
              .fontSize(14)
              .fontColor('#182431')
              .backgroundColor(Color.Gray)
              .textAlign(TextAlign.Center)
              .borderRadius(5)
          }
          .margin({ top: 20 })
          .direction(this.direction1)

          Text('方法二')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .height(this.showText ? 'auto' : 0)

          Divider()
            .strokeWidth('1px')
            .margin({ top: 5 })

          Text('Badge作为容器')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
            .height(this.showText ? 'auto' : 0)
            .margin({ top: 10 })

          Row({ space: 2 }) {
            Row() {
              Badge({
                value: '',
                style: {
                  badgeSize: 6,
                  badgeColor: '#FA2A2D'
                }
              }) {
                Image($r('app.media.startIcon'))
                  .width(40)
                  .height(40)
              }
              .borderWidth(1)
            }
            .borderWidth(1)
            .width(50)
            .height(50)

            Badge({
              value: '',
              style: {
                badgeSize: 6,
                badgeColor: '#FA2A2D'
              }
            }) {
              this.myBuilder('1')
            }
            .borderWidth(1)

            Badge({
              value: '',
              style: {
                badgeSize: 6,
                badgeColor: '#FA2A2D'
              }
            }) {
              MyComponent({
                title: 'MyComponent'
              })
                .width(50)
            }
            .borderWidth(1)

            Badge({
              value: '',
              style: {
                badgeSize: 6,
                badgeColor: '#FA2A2D'
              }
            }) {
              Text('Item1')
                .width(50)
              Image($r('app.media.startIcon'))
                .width(40)
                .height(40)
            }
            .borderWidth(1)

            Badge({
              value: '',
              style: {
                badgeSize: 6,
                badgeColor: '#FA2A2D'
              }
            })
              .borderWidth(1)
              .width(30)
              .height(30)
          }

          Row({ space: 2 }) {
            Badge({
              value: '',
              style: {
                badgeSize: 6,
                badgeColor: '#FA2A2D'
              }
            }) {
              Text(this.text1)
                .key('Badge_text1')
                .onClick(() => {
                  this.text1 = this.text1 + 'text'
                })
            }
            .borderWidth(1)

            Badge({
              value: '',
              style: {
                badgeSize: 6,
                badgeColor: '#FA2A2D'
              }
            }) {
              Text('Item123456')
                .width(100)
                .key('Badge_text2')
                .onClick(() => {
                  this.clip1 = !this.clip1
                })
            }
            .borderWidth(1)
            .width(50)
            .clip(this.clip1)
          }

          Divider()
            .strokeWidth('1px')
            .margin({ top: 5 })

          Text('Badge和布局相关通用属性组合')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
            .height(this.showText ? 'auto' : 0)
            .margin({ top: 10 })

          Row({ space: 2 }) {
            Row() {
              Badge({
                value: '',
                style: {
                  badgeSize: 6,
                  badgeColor: '#FA2A2D'
                }
              }) {
                Image($r('app.media.startIcon'))
                  .borderWidth(1)
              }
              .borderWidth(1)
              .padding(5)
              .margin(5)
              .width(40)
            }
            .borderWidth(1)

            Badge({
              value: '',
              style: {
                badgeSize: 6,
                badgeColor: '#FA2A2D'
              }
            }) {
              Image($r('app.media.startIcon'))
                .borderWidth(1)
            }
            .borderWidth(1)
            .width('20%')

            Stack() {
              Badge({
                value: '',
                style: {
                  badgeSize: 6,
                  badgeColor: '#FA2A2D'
                }
              }) {
                Image($r('app.media.startIcon'))
                  .borderWidth(1)
              }
              .borderWidth(1)
              .size({
                width: 30,
                height: 30
              })
            }
            .width(300)
            .height(70)
            .backgroundColor(0xFFE4C4)
            .align(Alignment.TopStart)

            Badge({
              value: '',
              style: {
                badgeSize: 6,
                badgeColor: '#FA2A2D'
              }
            }) {
              Image($r('app.media.startIcon'))
                .borderWidth(1)
                .width(40)
            }
            .borderWidth(1)
            .position({
              x: 210,
              y: 0
            })
          }

          Row() {
            Badge({
              value: '',
              style: {
                badgeSize: 6,
                badgeColor: '#FA2A2D'
              }
            }) {
              Image($r('app.media.startIcon'))
                .borderWidth(1)
                .width(40)
            }
            .borderWidth(1)
            .layoutWeight(2)

            Badge({
              value: '',
              style: {
                badgeSize: 6,
                badgeColor: '#FA2A2D'
              }
            }) {
              Image($r('app.media.startIcon'))
                .borderWidth(1)
                .width(40)
            }
            .borderWidth(1)
            .layoutWeight(3)

            Badge({
              value: '',
              style: {
                badgeSize: 6,
                badgeColor: '#FA2A2D'
              }
            }) {
              Image($r('app.media.startIcon'))
                .borderWidth(1)
                .width(40)
            }
            .borderWidth(1)
            .layoutWeight(5)
            .aspectRatio(2)
          }
          .borderWidth(1)
          .width(250)

          Divider()
            .strokeWidth('1px')
            .margin({ top: 5 })
          Text('Badge和颜色以及边框相关通用属性组合')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
            .height(this.showText ? 'auto' : 0)
            .margin({ top: 10 })
          Badge({
            value: 'test',
            style: {
              badgeSize: 6,
              badgeColor: '#FA2A2D'
            }
          }) {
            Text('text').width(50)
          }
          .borderWidth(1)
          .backgroundColor(Color.Pink)
          .foregroundColor(Color.Green)
          .borderColor(Color.Blue)

          Divider()
            .strokeWidth('1px')
            .margin({ top: 5 })
          Text('Badge和显隐相关通用属性组合')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
            .height(this.showText ? 'auto' : 0)
            .margin({ top: 10 })
          Row({ space: 5 }) {
            Badge({
              value: '',
              style: {
                badgeSize: 6,
                badgeColor: '#FA2A2D'
              }
            }) {
              Image($r('app.media.startIcon'))
                .borderWidth(1)
                .width(40)
                .visibility(this.visible)
            }
            .borderWidth(1)

            Badge({
              value: '',
              style: {
                badgeSize: 6,
                badgeColor: '#FA2A2D'
              }
            }) {
              Image($r('app.media.startIcon'))
                .borderWidth(1)
                .width(40)
            }
            .borderWidth(1)
            .visibility(this.visible)
          }
        }
        .key('testArea')

        Blank().height('10%')

        Text('切换参数')
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .width('100%')
          .onClick(() => {
            this.showText = !this.showText
          })

        Row({ space: 2 }) {
          Text(`${this.testCase1.length}`).key('Badge00_cyckes')
          Text('Test++')
            .fontSize(10)
            .backgroundColor(0x0000FF)
            .fontColor(0xffffff)
            .padding(5)
            .onClick(() => {
              this.setParam1()
              this.text = 'index1 = ' + this.index1
              this.index1++
              if (this.index1 == this.testCase1.length) {
                this.index1 = 0
              }
            })

          Text('Test++')
            .fontSize(10)
            .backgroundColor(0x0000FF)
            .fontColor(0xffffff)
            .padding(5)
            .onClick(() => {
              this.index1--
              if (this.index1 == -1) {
                this.index1 = this.testCase1.length - 1
              }

              this.setParam1()
              this.text = 'index1 = ' + this.index1
            })
        }

        if (this.showText) {
          Text(this.text)
        }

        Text('控制组件显隐')
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .width('100%')
        Row({ space: 2 }) {
          ForEach(this.caseVisits, (item: caseVisitsItem) => {
            MyComponent({
              title: item.title, func: () => {
                this.visible = item.visit
              }
            })
          }, (item: caseVisitsItem) => item.title)
        }

        Text('Direction:' + this.direction1)
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .width('100%')
        Row({ space: 2 }) {
          MyComponent({
            title: 'Ltr', func: () => {
              this.direction1 = Direction.Ltr
            }
          })
          MyComponent({
            title: 'Rtl', func: () => {
              this.direction1 = Direction.Rtl
            }
          })
          MyComponent({
            title: 'Auto', func: () => {
              this.direction1 = Direction.Auto
            }
          })
          MyComponent({
            title: 'null', func: () => {
              this.direction1 = null
            }
          })
        }

      }.borderWidth(2).margin(5)
    }
    .height('100%')
    .width('100%')
    .align(Alignment.Top)
  }
}