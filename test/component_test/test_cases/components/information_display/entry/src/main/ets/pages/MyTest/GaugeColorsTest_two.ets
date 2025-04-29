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

export default async function gaugeColorsTest_two() {
  /*
   * Gauge组件 Colors属性
   * 找到画面id为gaugeColors1,gaugeColors2的Gauge组件
   * 找到画面文本'GaugeColors1,GaugeColors2的Button组件
   * 获取gauge1的Colors属性与期待值[[color:0xFFA500,offset:$r('app.float.data_panel_offset_min')],[color:0xFFFF00,offset:$r('app.float.data_panel_offset_max')]]比对
   * 获取gauge2的Colors属性与期待值[[color:$r('app.color.data_panel_resource_color5'),offset:0],[color:$r('app.color.data_panel_resource_color3'),offset:1]]比对
   * 点击button1，变更gauge1的Colors属性值为[[[{color:"#deb6fb",offset:0},{color:"#ac49f5",offset:1}],9],[[{color:"#dbefa5",offset:0},{color:"#a5d61d",offset:1}],1]]
   * 获取gauge1的Colors属性与期待值[[[{color:"#deb6fb",offset:0},{color:"#ac49f5",offset:1}],9],[[{color:"#dbefa5",offset:0},{color:"#a5d61d",offset:1}],1]]比对
   * 点击button2，变更gauge1的Colors属性值为[[[{color:$r('app.color.data_panel_resource_color1'),offset:0},
   * {color:$r('app.color.data_panel_resource_color3'),offset:1}],9],[[[{color:$r('app.color.data_panel_resource_color5'),offset:0},{color:$r('app.color.data_panel_resource_color7'),offset:1}],1]]
   * 获取gauge1的Colors属性与期待值[[[{color:$r('app.color.data_panel_resource_color1'),offset:0},{color:$r('app.color.data_panel_resource_color3'),offset:1}],9],
   * [[[{color:$r('app.color.data_panel_resource_color5'),offset:0},{color:$r('app.color.data_panel_resource_color7'),offset:1}],1]]比对
   */
  defineTest('gaugeColorsTestDemo_two', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('gaugeColorsTestDemo_two running')
    let driver: Tester = Tester.create()
    let gauge1: Component = await driver.findComponent(Matcher.create().id('gaugeColors1').enabled(true))
    let gauge2: Component = await driver.findComponent(Matcher.create().id('gaugeColors2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('GaugeColors1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('GaugeColors2').enabled(true))
    let colors1: string = await gauge1.getInspectorInfo()
    assertEqual(JSON.parse(colors1)
      .$attrs.colors
      , '[["#FFFFA500","0.100000"],["#FFFFFF00","0.800000"]]')
    let colors2: string = await gauge2.getInspectorInfo()
    assertEqual(JSON.parse(colors2)
      .$attrs
      .colors
      , '[["#FF08F660","0.000000"],["#FFEEEE4A","1.000000"]]')

    await button1.tap()
    let colors3: string = await gauge1.getInspectorInfo()
    assertEqual(JSON.parse(colors3)
      .$attrs.colors,
      '[[[["#FFDEB6FB","0.000000"],["#FFAC49F5","1.000000"]],9],[[["#FFB5E0F4","0.000000"],["#FF46B1E3","1.000000"]],1]]')

    await button2.tap()
    let colors4: string = await gauge1.getInspectorInfo()
    assertEqual(JSON.parse(colors4)
      .$attrs.colors,
      '[[[["#FFF89B9B","0.000000"],["#FFEEEE4A","1.000000"]],9],[[["#1AF15D07","0.000000"],["#FF3C4747","1.000000"]],1]]')
  }, 0)
}