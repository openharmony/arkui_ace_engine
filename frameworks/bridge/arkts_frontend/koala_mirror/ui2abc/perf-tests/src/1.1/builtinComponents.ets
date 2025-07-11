
/**
 * 内置组件 builtinComponents.ets
 */

@Entry
@Component
struct BuiltinComponents {
  @State message: string = 'Hello ArkTS'
  @State sliderValue: number = 50
  @State toggleValue: boolean = false
  @State pickerValue: string = 'Option1'
  @State dateValue: Date = new Date()
  @State progressValue: number = 0.3
  @State textValue: string = ''
  @State radioValue: string = 'Radio1'
  @State checkboxValues: boolean[] = [false, false, false]
  @State indexValue: number = 0

  build() {
    Column() {

// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


// 1. 文本组件
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .fontStyle(FontStyle.Normal)
        .draggable(true)
        .onClick((e:ClickEvent) => {
          this.message = 'Text clicked!'
        })

      // 2. 按钮组件
      Button('Click Me')
        .width(200)
        .height(50)
        .type(ButtonType.Capsule)
        .onClick((e:ClickEvent) => {
          this.message = 'Button clicked!'
        })

      // 3. 图片组件
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .sourceSize({width:1392, height:1080})
        .borderWidth(1)
        .objectFit(ImageFit.Contain)
        .borderRadius(50)

      // 4. 滑动条组件
      Slider({
        value: this.sliderValue,
        min: 0,
        max: 100,
        step: 1,
        style: SliderStyle.OutSet
      })
        .width('90%')
        .onChange((value) => {
          this.sliderValue = value
        })

      // 5. 开关组件
      Toggle({ type: ToggleType.Switch, isOn: this.toggleValue })
        .width(100)
        .height(40)
        .padding(15)
        .selectedColor(Color.Green)
        .onChange((isOn: boolean) => {
          this.toggleValue = isOn
        })

      // 6. 日期选择器
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2030-12-31'),
        selected: this.dateValue
      })
        .width('90%')
        .onDateChange((value: Date) => {
          this.dateValue = value
        })

      // 7. 进度条
      Progress({
        value: this.progressValue,
        total: 1.0,
        type: ProgressType.Linear
      })
        .width('90%')
        .height(100)

      // 8. 输入框
      TextInput({ placeholder: 'Enter text' })
        .width('90%')
        .height(50)
        .onChange((value: string) =>  {
          this.textValue = value
        })

      // 9. 复选框
      Row() {
        Checkbox()
          .select(this.checkboxValues[0])
          .onChange((value: boolean) => {
            this.checkboxValues[0] = value
          })
        Checkbox()
          .select(this.checkboxValues[1])
          .onChange((value: boolean) => {
            this.checkboxValues[1] = value
          } )
      }

      // 10. 列表组件
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .width('100%')
          .height(60)
          .backgroundColor('#f0f0f0')
        })
      }
      .width('100%')
      .height(200)

      // 11. 页签组件
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          Text('Tab1 Content').fontSize(20)
        }.tabBar('Tab1')

        TabContent() {
          Text('Tab2 Content')
            .fontSize(20)
        }.tabBar('Tab2')
      }
      .width('100%')
      .height(150)


    }
  }
}

