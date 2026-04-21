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

@Builder
export function PopupWaterFlowBuilder(name: string, param: Object) {
  PopupWaterFlowExample()
}

interface struct1 { template: string, label: string }

@Entry
@Component
struct PopupWaterFlowExample {
  pathStack: NavPathStack = new NavPathStack()
  private scroller: Scroller = new Scroller()
  
  @State showPopup: boolean = false
  @State columnsTemplate: string = '1fr 1fr 1fr'
  @State rowsTemplate: string = '1fr 1fr'
  @State columnsGap: number = 10
  @State rowsGap: number = 10
  @State scrollEnabled: boolean = true
  
  @Builder
  waterFlowPopupContent() {
    Column({ space: 15 }) {
      Text('WaterFlow Popup')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
      
      Divider()
      
      Text('WaterFlow Settings')
        .fontSize(14)
        .fontColor(Color.Gray)
      
      Row() {
        Text('Columns:')
        Blank()
        Text(this.columnsTemplate)
          .fontColor(Color.Blue)
      }
      .width('100%')
      .padding(5)
      
      Row() {
        Text('Rows:')
        Blank()
        Text(this.rowsTemplate)
          .fontColor(Color.Blue)
      }
      .width('100%')
      .padding(5)
      
      Row() {
        Text('Columns Gap: ' + this.columnsGap + 'vp')
        Blank()
        Text(this.columnsGap + 'vp')
          .fontColor(Color.Blue)
      }
      .width('100%')
      .padding(5)
      
      Row() {
        Text('Rows Gap: ' + this.rowsGap + 'vp')
        Blank()
        Text(this.rowsGap + 'vp')
          .fontColor(Color.Blue)
      }
      .width('100%')
      .padding(5)
      
      Divider()
      
      Text('WaterFlow Content')
        .fontSize(14)
        .fontColor(Color.Gray)
      
      WaterFlow({ scroller: this.scroller }) {
        ForEach([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12], (item: number) => {
          FlowItem() {
            Column({ space: 5 }) {
              Text('Item ' + item)
                .fontSize(16)
                .fontWeight(FontWeight.Bold)
                .fontColor(Color.White)
              
              Text('Content ' + item)
                .fontSize(12)
                .fontColor(Color.White)
            }
            .width('100%')
            .height('100%')
            .justifyContent(FlexAlign.Center)
            .backgroundColor(this.getItemColor(item))
            .borderRadius(8)
          }
        })
      }
      .columnsTemplate(this.columnsTemplate)
      .rowsTemplate(this.rowsTemplate)
      .columnsGap(this.columnsGap)
      .rowsGap(this.rowsGap)
      .width('100%')
      .height(300)
      .scrollBar(BarState.Auto)
      .scrollBarColor(Color.Gray)
      .scrollBarWidth(4)
      .enabled(this.scrollEnabled)
      
      Divider()
      
      Button('Close')
        .width('100%')
        .onClick(() => {
          this.showPopup = false
        })
    }
    .width(350)
    .padding(20)
    .backgroundColor(Color.White)
    .borderRadius(10)
  }
  
  getItemColor(index: number): ResourceColor {
    const colors: Array<Color> = [
      Color.Red, Color.Orange, Color.Yellow, Color.Green, 
      Color.Blue, Color.Pink, Color.Brown
    ]
    return colors[index % colors.length]
  }
  
  @Styles
  myButtonStyle() {
    .width('100%')
    .height(45)
    .borderRadius(8)
    .margin({ top: 5, bottom: 5 })
  }
  
  @Styles
  cardStyle() {
    .width('90%')
    .padding(15)
    .margin({ top: 10, bottom: 10 })
    .backgroundColor(Color.White)
    .borderRadius(10)
    .shadow({
      radius: 8,
      offsetX: 2,
      offsetY: 2,
      color: Color.Gray
    })
  }
  
  build() {
    NavDestination() {
      Column() {
        Text('Popup WaterFlow Test')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 20 })
        
        Column() {
          Text('WaterFlow Configuration')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 10 })
          
          Text('Columns Template')
            .fontSize(14)
            .margin({ top: 10 })
          
          Row({ space: 10 }) {
            ForEach([
              { template: '1fr', label: '1' },
              { template: '1fr 1fr', label: '2' },
              { template: '1fr 1fr 1fr', label: '3' },
              { template: '1fr 1fr 1fr 1fr', label: '4' }
            ], (item: struct1) => {
              Button(item.label)
                .width('23%')
                .height(40)
                .fontSize(12)
                .backgroundColor(this.columnsTemplate === item.template ? Color.Blue : Color.Gray)
                .onClick(() => {
                  this.columnsTemplate = item.template
                })
            })
          }
          .width('100%')
          
          Text('Rows Template')
            .fontSize(14)
            .margin({ top: 10 })
          
          Row({ space: 10 }) {
            ForEach([
              { template: '1fr', label: '1' },
              { template: '1fr 1fr', label: '2' },
              { template: '1fr lfr lfr', label: '3' }
            ], (item: struct1) => {
              Button(item.label)
                .width('31%')
                .height(40)
                .fontSize(12)
                .backgroundColor(this.rowsTemplate === item.template ? Color.Blue : Color.Gray)
                .onClick(() => {
                  this.rowsTemplate = item.template
                })
            })
          }
          .width('100%')
          
          Row() {
            Text('Columns Gap: ' + this.columnsGap + 'vp')
            Slider({
              min: 0,
              max: 30,
              value: this.columnsGap,
              step: 1
            })
              .width('60%')
              .onChange((value: number) => {
                this.columnsGap = value
              })
          }
          .width('100%')
          .padding(5)
          
          Row() {
            Text('Rows Gap: ' + this.rowsGap + 'vp')
            Slider({
              min: 0,
              max: 30,
              value: this.rowsGap,
              step: 1
            })
              .width('60%')
              .onChange((value: number) => {
                this.rowsGap = value
              })
            }
          .width('100%')
          .padding(5)
          
          Row() {
            Text('Scroll Enabled: ' + this.scrollEnabled)
            Toggle({ type: ToggleType.Switch, isOn: this.scrollEnabled })
              .onChange((isOn: boolean) => {
                this.scrollEnabled = isOn
              })
          }
          .width('100%')
          .padding(5)
        }
        .cardStyle()
        
        Column() {
          Text('WaterFlow Popup Demo')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 10 })
          
          Text('Popup with WaterFlow component')
            .fontSize(14)
            .fontColor(Color.Gray)
            .margin({ bottom: 10 })
          
          Button('Show WaterFlow Popup')
            .myButtonStyle()
            .onClick(() => {
              this.showPopup = true
            })
            .bindPopup(this.showPopup, {
              builder: this.waterFlowPopupContent(),
              placement: Placement.Bottom,
              mask: true,
              onStateChange: (e) => {
                if (!e.isVisible) {
                  this.showPopup = false
                }
              }
            })
        }
        .cardStyle()
        
        Column() {
          Text('WaterFlow Information')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 10 })
          
          Text('• WaterFlow supports dynamic column layout')
            .fontSize(14)
            .fontColor(Color.Gray)
          
          Text('• Items flow automatically based on template')
            .fontSize(14)
            .fontColor(Color.Gray)
          
          Text('• Supports scrolling for large content')
            .fontSize(14)
            .fontColor(Color.Gray)
          
          Text('• Configurable gaps between items')
            .fontSize(14)
            .fontColor(Color.Gray)
        }
        .cardStyle()
      }
      .width('100%')
      .padding(20)
    }
    .title('Popup WaterFlow Test')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack
    })
  }
}
