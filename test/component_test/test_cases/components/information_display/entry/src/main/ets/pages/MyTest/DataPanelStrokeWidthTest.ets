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

export default async function dataPanelStrokeWidthTest() {
  /*
   * DataPanel组件 StrokeWidth属性
   * 找到画面id为dataPanelStrokeWidth1，dataPanelStrokeWidth2，dataPanelStrokeWidth3的dataPanel组件
   * 找到画面文本为DataPanelStrokeWidth1，DataPanelStrokeWidth2的Button组件
   * 获取dataPanel1的strokeWidth属性与期待值30.00vp比对
   * 获取dataPanel2的strokeWidth属性与期待值$r('app.integer.data_panel_strokeWidth')比对
   * 获取dataPanel3的strokeWidth属性与期待值20.00vp比对
   * 点击button1，变更dataPanelStrokeWidth1的strokeWidth属性值为'24.00vp'
   * 获取dataPanel1的strokeWidth属性与期待值'24.00vp'比对
   * 点击button2，变更dataPanelStrokeWidth1的strokeWidth属性值为'24.00vp'
   * 获取dataPanel1的strokeWidth属性与期待值'24.00vp'比对
   */
  defineTest('dataPanelStrokeWidthTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('dataPanelStrokeWidthTestDemo running')
    let driver: Tester = Tester.create()
    let dataPanel1: Component = await driver.findComponent(Matcher.create().id('dataPanelStrokeWidth1').enabled(true))
    let dataPanel2: Component = await driver.findComponent(Matcher.create().id('dataPanelStrokeWidth2').enabled(true))
    let dataPanel3: Component = await driver.findComponent(Matcher.create().id('dataPanelStrokeWidth3').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('DataPanelStrokeWidth1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('DataPanelStrokeWidth2').enabled(true))

    let strokeWidth1: string = await dataPanel1.getInspectorInfo()
    assertEqual(JSON.parse(strokeWidth1).$attrs.strokeWidth, '30.00vp')
    let strokeWidth2: string = await dataPanel2.getInspectorInfo()
    assertEqual(JSON.parse(strokeWidth2).$attrs.strokeWidth, $r('app.string.data_panel_strokeWidth'))
    let strokeWidth3: string = await dataPanel3.getInspectorInfo()
    assertEqual(JSON.parse(strokeWidth3).$attrs.strokeWidth, '20.00vp')

    await button1.tap()
    let strokeWidth4: string = await dataPanel1.getInspectorInfo()
    assertEqual(JSON.parse(strokeWidth4).$attrs.strokeWidth, '24.00vp')
    await button2.tap()
    let strokeWidth5: string = await dataPanel1.getInspectorInfo()
    assertEqual(JSON.parse(strokeWidth5).$attrs.strokeWidth, '24.00vp')
  }, 0)
}