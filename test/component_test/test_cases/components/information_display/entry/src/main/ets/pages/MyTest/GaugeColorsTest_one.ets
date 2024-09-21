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

export default async function gaugeColorsTest_one() {
  /*
   * Gauge组件 Colors属性
   * 找到画面id为gaugeColors1,gaugeColors2,gaugeColors3的Gauge组件
   * 找到画面文本为GaugeColors1,GaugeColors2,GaugeColors3的Button组件
   * 获取gauge1的Colors属性与期待值Color.Green比对
   * 获取gauge2的Colors属性与期待值'#FF0000FF'比对
   * 获取gauge3的Colors属性与期待值'#201bf5df'比对
   * 点击button1，变更Colors属性值为[[[["#FF008000","0.000000"]],8],[[["#FFA52A2A","0.000000"]],5],[[["#FFFFC0CB","0.000000"]],1]]
   * 获取gauge1的Colors属性与期待值[[[["#FF008000","0.000000"]],8],[[["#FFA52A2A","0.000000"]],5],[[["#FFFFC0CB","0.000000"]],1]]比对
   * 点击button2，变更Colors属性值为[[[["#20E38C8C","0.000000"]],8],[[["#201660E0","0.000000"]],5],[[["#FF00FF00","0.000000"]],1]]
   * 获取gauge1的Colors属性与期待值[[[["#20E38C8C","0.000000"]],8],[[["#201660E0","0.000000"]],5],[[["#FF00FF00","0.000000"]],1]]比对
   * 点击button3，变更Colors属性值为[[[["#FFFFA500","0.000000"]],8],[[["#FFFFFF00","0.000000"]],5],[[["#FF00FF00","0.000000"]],1]]
   * 获取gauge1的Colors属性与期待值[[[["#FFFFA500","0.000000"]],8],[[["#FFFFFF00","0.000000"]],5],[[["#FF00FF00","0.000000"]],1]]比对
   */
  defineTest('gaugeColorsTestDemo_one', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('gaugeColorsTestDemo_one running')
    let driver: Tester = Tester.create()
    let gauge1: Component = await driver.findComponent(Matcher.create().id('gaugeColors1').enabled(true))
    let gauge2: Component = await driver.findComponent(Matcher.create().id('gaugeColors2').enabled(true))
    let gauge3: Component = await driver.findComponent(Matcher.create().id('gaugeColors3').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('GaugeColors1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('GaugeColors2').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('GaugeColors3').enabled(true))

    let colors1: string = await gauge1.getInspectorInfo()
    assertEqual(JSON.parse(colors1).$attrs.colors.toLowerCase(), Color.Green)
    let colors2: string = await gauge2.getInspectorInfo()
    assertEqual(JSON.parse(colors2).$attrs.colors, '#FF0000FF')
    let colors3: string = await gauge3.getInspectorInfo()
    assertEqual(JSON.parse(colors3).$attrs.colors.toLowerCase(), '#201bf5df')
    await button1.tap()
    let colors4: string = await gauge1.getInspectorInfo()
    assertEqual(JSON.parse(colors4).$attrs.colors,
      '[[[["#FF008000","0.000000"]],8],[[["#FFA52A2A","0.000000"]],5],[[["#FFFFC0CB","0.000000"]],1]]')

    await button2.tap()
    let colors5: string = await gauge1.getInspectorInfo()
    assertEqual(JSON.parse(colors5).$attrs.colors,
      '[[[["#20E38C8C","0.000000"]],8],[[["#201660E0","0.000000"]],5],[[["#FF00FF00","0.000000"]],1]]')

    await button3.tap()
    let colors6: string = await gauge1.getInspectorInfo()
    assertEqual(JSON.parse(colors6).$attrs.colors,
      '[[[["#FFFFA500","0.000000"]],8],[[["#FFFFFF00","0.000000"]],5],[[["#FF00FF00","0.000000"]],1]]')
  }, 0)
}