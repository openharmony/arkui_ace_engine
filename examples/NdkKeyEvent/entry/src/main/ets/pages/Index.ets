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

import nativeNode from 'libnativeNode.so';

@Entry
@Component
struct KeyEventSample {
  @State lastKeyEvent: string = '';
  @State keyEventCount: number = 0;

  build() {
    Column() {
      // 标题区域
      Row() {
        Text($r('app.string.demo_title'))
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .fontColor(Color.White)
          .textAlign(TextAlign.Center)
      }
      .width('100%')
      .height(80)
      .backgroundColor('#4A90E2')
      .justifyContent(FlexAlign.Center)
      .alignItems(VerticalAlign.Center)

      Scroll() {
        Column({ space: 20 }) {
          // 说明区域
          Column({ space: 10 }) {
            Text($r('app.string.demo_introduce'))
              .fontSize(14)
              .fontColor('#666666')
              .textAlign(TextAlign.Start)
            
            Column({ space: 5 }) {
              Text($r('app.string.demo_introduce_item1'))
                .fontSize(12)
                .fontColor('#888888')
                .textAlign(TextAlign.Start)
              Text($r('app.string.demo_introduce_item2'))
                .fontSize(12)
                .fontColor('#888888')
                .textAlign(TextAlign.Start)
              Text($r('app.string.demo_introduce_item3'))
                .fontSize(12)
                .fontColor('#888888')
                .textAlign(TextAlign.Start)
              Text($r('app.string.demo_introduce_item4'))
                .fontSize(12)
                .fontColor('#FF6B6B')
                .textAlign(TextAlign.Start)
                .fontWeight(FontWeight.Medium)
            }
            .alignItems(HorizontalAlign.Start)
            .width('100%')
          }
          .width('95%')
          .padding(15)
          .backgroundColor('#F8F9FA')
          .borderRadius(12)
          .alignItems(HorizontalAlign.Start)

          // 统计信息
          Row() {
            Column() {
              Text(this.keyEventCount.toString())
                .fontSize(20)
                .fontWeight(FontWeight.Bold)
                .fontColor('#4A90E2')
              Text($r('app.string.key_count'))
                .fontSize(12)
                .fontColor('#666666')
            }
            .justifyContent(FlexAlign.Center)
            
            Divider()
              .vertical(true)
              .height(40)
              .color('#E0E0E0')
            
            Column() {
              Text(this.lastKeyEvent || 'None')
                .fontSize(16)
                .fontWeight(FontWeight.Medium)
                .fontColor('#FF6B6B')
                .maxLines(1)
                .textOverflow({ overflow: TextOverflow.Ellipsis })
              Text($r('app.string.last_key'))
                .fontSize(12)
                .fontColor('#666666')
            }
            .justifyContent(FlexAlign.Center)
            .layoutWeight(1)
          }
          .width('95%')
          .height(70)
          .padding(15)
          .backgroundColor(Color.White)
          .borderRadius(12)
          .shadow({ radius: 5, color: '#E0E0E0', offsetX: 2, offsetY: 2 })
          .justifyContent(FlexAlign.SpaceEvenly)

          // Native组件区域
          Column() {
            Text($r('app.string.native_component'))
              .fontSize(16)
              .fontWeight(FontWeight.Medium)
              .fontColor('#333333')
              .margin({ bottom: 10 })

            XComponent({
              id: 'keyEventSample',
              type: XComponentType.NODE,
              libraryname: 'nativeNode'
            })
              .onAppear(() => {
                nativeNode.createNativeNode("keyEventSample", this.getUIContext());
              })
              .width('100%')
              .height(600)
              .backgroundColor('#FFFFFF')
              .borderRadius(12)
              .border({
                width: 2,
                color: '#4A90E2',
                style: BorderStyle.Dashed
              })
              .focusable(true)
              .onKeyEvent((event) => {
                this.handleKeyEvent(event);
              })
          }
          .id('testKeyEvent')
          .width('95%')
          .padding(15)
          .backgroundColor('#F0F8FF')
          .borderRadius(12)
          .alignItems(HorizontalAlign.Start)

          // 使用说明
          Column({ space: 8 }) {
            Text($r('app.string.use_direction'))
              .fontSize(16)
              .fontWeight(FontWeight.Medium)
              .fontColor('#333333')

            Text($r('app.string.basic_test'))
              .fontSize(13)
              .fontColor('#4A90E2')
              .fontWeight(FontWeight.Medium)
            Text($r('app.string.test_step1'))
              .fontSize(12)
              .fontColor('#666666')
            Text($r('app.string.test_step2'))
              .fontSize(12)
              .fontColor('#666666')
            Text($r('app.string.test_step3'))
              .fontSize(12)
              .fontColor('#666666')

            Text($r('app.string.other_test'))
              .fontSize(13)
              .fontColor('#FF6B6B')
              .fontWeight(FontWeight.Medium)
            Text($r('app.string.test_step4'))
              .fontSize(12)
              .fontColor('#666666')
            Text($r('app.string.test_step4_1'))
              .fontSize(12)
              .fontColor('#666666')
            Text($r('app.string.test_step4_2'))
              .fontSize(12)
              .fontColor('#666666')
            Text($r('app.string.test_step4_3'))
              .fontSize(12)
              .fontColor('#666666')
            Text($r('app.string.test_step5'))
              .fontSize(12)
              .fontColor('#666666')
          }
          .width('95%')
          .padding(15)
          .backgroundColor('#FFF9E6')
          .borderRadius(12)
          .alignItems(HorizontalAlign.Start)

        }
      }
      .id('testScroll')
      .layoutWeight(1)
      .width('100%')
      .padding({ top: 20, bottom: 20 })

    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F5F5F5')
  }

  private handleKeyEvent(event: KeyEvent) {
    this.keyEventCount++;
    
    // 获取按键名称
    let keyName = this.getKeyName(event.keyCode);
    this.lastKeyEvent = keyName;
    
    // 更新事件信息
    let eventType = this.getEventTypeName(event.type);
    let timestamp = new Date().toLocaleTimeString();
  }

  private getKeyName(keyCode: number): string {
    const keyMap: Record<number, string> = {
      2000: 'KEY_0', 2001: 'KEY_1', 2002: 'KEY_2', 2003: 'KEY_3', 2004: 'KEY_4',
      2005: 'KEY_5', 2006: 'KEY_6', 2007: 'KEY_7', 2008: 'KEY_8', 2009: 'KEY_9',
      2017: 'KEY_A', 2018: 'KEY_B', 2019: 'KEY_C', 2020: 'KEY_D', 2021: 'KEY_E',
      2022: 'KEY_F', 2023: 'KEY_G', 2024: 'KEY_H', 2025: 'KEY_I', 2026: 'KEY_J',
      2027: 'KEY_K', 2028: 'KEY_L', 2029: 'KEY_M', 2030: 'KEY_N', 2031: 'KEY_O',
      2032: 'KEY_P', 2033: 'KEY_Q', 2034: 'KEY_R', 2035: 'KEY_S', 2036: 'KEY_T',
      2037: 'KEY_U', 2038: 'KEY_V', 2039: 'KEY_W', 2040: 'KEY_X', 2041: 'KEY_Y',
      2042: 'KEY_Z', 2050: 'SPACE', 2054: 'ENTER', 2055: 'BACKSPACE', 2070: 'ESCAPE',
      2012: 'DPAD_UP', 2013: 'DPAD_DOWN', 2014: 'DPAD_LEFT', 2015: 'DPAD_RIGHT',
      2090: 'F1', 2091: 'F2', 2092: 'F3', 2093: 'F4', 2094: 'F5', 2095: 'F6',
      2096: 'F7', 2097: 'F8', 2098: 'F9', 2099: 'F10', 2100: 'F11', 2101: 'F12'
    };
    
    return keyMap[keyCode] || `UNKNOWN(${keyCode})`;
  }

  private getEventTypeName(type: KeyType): string {
    switch (type) {
      case KeyType.Down:
        return 'KEY_DOWN';
      case KeyType.Up:
        return 'KEY_UP';
      default:
        return 'UNKNOWN_TYPE';
    }
  }
}
