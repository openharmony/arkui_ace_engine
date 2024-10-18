/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest'

export default async function gaugeColorsTest_three() {
  /*
   * Gauge组件 Colors属性
   * 找到画面id为gaugeColors1,gaugeColors2,gaugeColors3的Gauge组件
   * 找到画面文本为GaugeColors1,GaugeColors2,GaugeColors3的Button组件
   * 获取gauge1的Colors属性与期待值$r('app.color.data_panel_resource_color5')比对
   * 获取gauge2的Colors属性与期待值[{color:"#FF008000",offset:"0.000000"},{color:"#FFA52A2A",offset:"1.000000"}]
   * 获取gauge3的Colors属性与期待值[{color:"#FFE84026",offset:"0.000000"},{color:"#FF64BB5C",offset:"1.000000"}]
   * 点击button1，变更gauge1的Colors属性值为[[color:$r('app.color.data_panel_resource_color6'),offset:8],
   * [color:$r('app.color.data_panel_resource_color5'),offset:5],[color:$r('app.color.data_panel_resource_color6'),offset:1]]
   * 获取gauge1的Colors属性与期待值[[color:$r('app.color.data_panel_resource_color6'),offset:8],
   * [color:$r('app.color.data_panel_resource_color5'),offset:5],[color:$r('app.color.data_panel_resource_color6'),offset:1]]比对
   * 点击button2，变更gauge1的Colors属性值为[[[{color:Color.Brown,0},{color:Color.Blue,1}],9],[[{color:Color.Pink,0},{color:Color.Yellow,1}],1]]
   * 获取gauge1的Colors属性与期待值[[[{color:Color.Brown,0},{color:Color.Blue,1}],9],[[{color:Color.Pink,0},{color:Color.Yellow,1}],1]]比对
   * 点击button3，变更gauge1的Colors属性值为[[[{color:0x317AF7,offset:0},{color:0x5BA854,offset:1}],9],[[{color:0xFFFF00,offset:0},{color:0xFFFF00,offset:1}],1]]
   * 获取gauge1的Colors属性与期待值[[[{color:0x317AF7,offset:0},{color:0x5BA854,offset:1}],9],[[{color:0xFFFF00,offset:0},{color:0xFFFF00,offset:1}],1]]比对
   */
  defineTest('gaugeColorsTestDemo_three', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('gaugeColorsTestDemo_three running')
    let driver: Tester = Tester.create()
    let gauge1: Component = await driver.findComponent(Matcher.create().id('gaugeColors1').enabled(true))
    let gauge2: Component = await driver.findComponent(Matcher.create().id('gaugeColors2').enabled(true))
    let gauge3: Component = await driver.findComponent(Matcher.create().id('gaugeColors3').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('GaugeColors1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('GaugeColors2').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('GaugeColors3').enabled(true))
    let gaugeColorsState1: string = await gauge1.getInspectorInfo()
    assertEqual(JSON.parse(gaugeColorsState1).$attrs.colors, $r('app.color.data_panel_resource_color5'))
    let gaugeColorsState2: string = await gauge2.getInspectorInfo()
    assertEqual(JSON.parse(gaugeColorsState2).$attrs.colors, '[["#FF008000","0.000000"],["#FFA52A2A","1.000000"]]')
    let gaugeColorsState3: string = await gauge3.getInspectorInfo()
    assertEqual(JSON.parse(gaugeColorsState3).$attrs.colors, '[["#FFE84026","0.000000"],["#FF64BB5C","1.000000"]]')

    await button1.tap()
    let gaugeColorsState4: string = await gauge1.getInspectorInfo()
    assertEqual(JSON.parse(gaugeColorsState4).$attrs.colors,
      '[[[["#FF3C4747","0.000000"]],8],[[["#FF08F660","0.000000"]],5],[[["#FFF89B9B","0.000000"]],1]]')

    await button2.tap()
    let gaugeColorsState5: string = await gauge1.getInspectorInfo()
    assertEqual(JSON.parse(gaugeColorsState5)
      .$attrs.colors,
      '[[[["#FFA52A2A","0.000000"],["#FF0000FF","1.000000"]],9],[[["#FFFFC0CB","0.000000"],["#FFFFFF00","1.000000"]],1]]')

    await button3.tap()
    let gaugeColorsState6: string = await gauge1.getInspectorInfo()
    assertEqual(JSON.parse(gaugeColorsState6)
      .$attrs
      .colors,
      '[[[["#FF317AF7","0.000000"],["#FF5BA854","1.000000"]],9],[[["#FFFFFF00","0.000000"],["#FF008000","1.000000"]],1]]')
  }, 0)
}