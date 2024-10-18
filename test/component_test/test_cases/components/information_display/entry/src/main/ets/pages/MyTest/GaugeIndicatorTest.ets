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

export default async function gaugeIndicatorTest() {
  /*
  * Gauge组件 Indicator属性
  * 找到画面id为gaugeIndicator1,gaugeIndicator2,gaugeIndicator3的Gauge组件
  * 找到画面文本为'GaugeIndicator1','GaugeIndicator2','GaugeIndicator3'的Button组件
  * 获取gauge1的Indicator属性与期待值'10px'比对
  * 获取gauge2的Indicator属性与期待值{icon:$rawfile('Gauge.svg'),space:'40vp'}比对
  * 获取gauge3的Indicator属性与期待值'40fp'比对
  * 点击button1，变更gauge1的Indicator属性值为'50lpx'
  * 获取gauge1的Indicator属性与期待值'50lpx'比对
  * 点击button2，变更gauge1的Indicator属性值为$r('app.string.gauge_dimension')
  * 获取gauge1的Indicator属性与期待值$r('app.string.gauge_dimension')比对
  * 点击button3，变更gauge1的Indicator属性值为null
  * 获取gauge1的Indicator属性与期待值null比对
  */
  defineTest('gaugeIndicatorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('gaugeIndicatorTestDemo running')
    let driver: Tester = Tester.create()
    let gauge1: Component = await driver.findComponent(Matcher.create().id('gaugeIndicator1').enabled(true))
    let gauge2: Component = await driver.findComponent(Matcher.create().id('gaugeIndicator2').enabled(true))
    let gauge3: Component = await driver.findComponent(Matcher.create().id('gaugeIndicator3').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('GaugeIndicator1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('GaugeIndicator2').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('GaugeIndicator3').enabled(true))
    let indicator1: string = await gauge1.getInspectorInfo()
    assertEqual(JSON.parse(indicator1).$attrs.indicator.space, '10.00px')
    let indicator2: string = await gauge2.getInspectorInfo()
    assertEqual(JSON.parse(indicator2).$attrs.indicator.icon, $rawfile('Gauge.svg'))
    assertEqual(JSON.parse(indicator2).$attrs.indicator.space, '40.00vp')
    let indicator3: string = await gauge3.getInspectorInfo()
    assertEqual(JSON.parse(indicator3).$attrs.indicator.space, '40.00fp')
    await button1.tap()
    let indicator4: string = await gauge1.getInspectorInfo()
    assertEqual(JSON.parse(indicator4).$attrs.indicator.space, '50.00lpx')
    await button2.tap()
    let indicator5: string = await gauge1.getInspectorInfo()
    assertEqual(JSON.parse(indicator5).$attrs.indicator.space, $r('app.string.gauge_dimension'))
    await button3.tap()
    let indicator6: string = await gauge1.getInspectorInfo()
    assertEqual(JSON.parse(indicator6).$attrs.indicator, 'null')
  }, 0)
}