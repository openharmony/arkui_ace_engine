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

export default async function gaugeTrackShadowTest() {
  /*
   * Gauge组件 TrackShadow属性
   * 找到画面id为gaugeTrackShadow的Gauge组件
   * 找到画面文本为GaugeTrackShadow1,GaugeTrackShadow2的Button组件
   * 获取gauge的trackShadow属性与期待值{radius:100,offsetX:30,offsetY:30}比对
   * 点击button1，变更trackShadow2的trackShadow的属性值为{radius:$r('app.integer.data_panel_Number'),offsetX:$r('app.integer.data_panel_Number'),offsetY:$r('app.integer.data_panel_Number')}
   * 获取gauge的trackShadow属性与期待值{radius:$r('app.integer.data_panel_Number'),offsetX:$r('app.integer.data_panel_Number'),offsetY:$r('app.integer.data_panel_Number')}比对
   * 点击button2，变更trackShadow3的trackShadow的属性值为null
   * 获取gauge的trackShadow属性与期待值null比对
   */
  defineTest('gaugeTrackShadowTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('gaugeTrackShadowTestDemo running')
    let driver: Tester = Tester.create()
    let gauge: Component = await driver.findComponent(Matcher.create().id('gaugeTrackShadow').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('GaugeTrackShadow1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('GaugeTrackShadow2').enabled(true))
    let trackShadow1: string = await gauge.getInspectorInfo()
    assertEqual(JSON.parse(trackShadow1).$attrs.trackShadow.radius, '100.000000')
    assertEqual(JSON.parse(trackShadow1).$attrs.trackShadow.offsetX, '30.000000')
    assertEqual(JSON.parse(trackShadow1).$attrs.trackShadow.offsetY, '30.000000')
    await button1.tap()
    let trackShadow2: string = await gauge.getInspectorInfo()
    assertEqual(JSON.parse(trackShadow2).$attrs.trackShadow.radius, $r("app.string.data_panel_number"))
    assertEqual(JSON.parse(trackShadow2).$attrs.trackShadow.offsetX, $r("app.string.data_panel_number"))
    assertEqual(JSON.parse(trackShadow2).$attrs.trackShadow.offsetY, $r("app.string.data_panel_number"))
    await button2.tap()
    let trackShadow3: string = await gauge.getInspectorInfo()
    assertEqual(JSON.parse(trackShadow3).$attrs.trackShadow, 'null')
  }, 0)
}