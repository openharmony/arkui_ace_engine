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

export default async function dataPanelValueColorsTest_two() {
  /*
   * DataPanel组件 ValueColors属性
   * 找到画面id为dataPanelValueColors1,dataPanelValueColors2的DataPanel组件
   * 找到画面文本为DataPanelValueColors1,DataPanelValueColors2的Button组件
   * 获取dataPanel1的ValueColors属性与期待值[Color.Green,Color.Blue,Color.Yellow,Color.Brown]比对
   * 获取dataPanel2的ValueColors属性与期待值['#FF0000FF','#FFFFA500','#FFFFFF00','#FF00FF00']比对
   * 点击button1，变更valueColors1的ValueColors属性值为['#FF00FF00','#20e38c8c','#201660e0','#201bf5df']
   * 获取dataPanel1的ValueColors属性与期待值['#FF00FF00','#20e38c8c','#201660e0','#201bf5df']比对
   * 点击button2，变更valueColors1的ValueColors属性值为[$r('app.color.data_panel_resource_color3'),$r('app.color.data_panel_resource_color5'),
   * $r('app.color.data_panel_resource_color1'),$r('app.color.data_panel_resource_color6')]
   * 获取dataPanel1的ValueColors属性与期待值[$r('app.color.data_panel_resource_color3'),$r('app.color.data_panel_resource_color5'),
   * $r('app.color.data_panel_resource_color1'),$r('app.color.data_panel_resource_color6')]比对
   */
  defineTest('dataPanelValueColorsTestDemo_two', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('dataPanelValueColorsTestDemo_two running')
    let driver: Tester = Tester.create()
    let dataPanel1: Component = await driver.findComponent(Matcher.create().id('dataPanelValueColors1').enabled(true))
    let dataPanel2: Component = await driver.findComponent(Matcher.create().id('dataPanelValueColors2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('DataPanelValueColors1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('DataPanelValueColors2').enabled(true))

    let valueColors1: string = await dataPanel1.getInspectorInfo()
    assertEqual(JSON.parse(valueColors1)
      .$attrs
      .valueColors[0][0]
      .color
      .toLowerCase(), Color.Green)
    assertEqual(JSON.parse(valueColors1)
      .$attrs
      .valueColors[1][0]
      .color
      .toLowerCase(), Color.Blue)
    assertEqual(JSON.parse(valueColors1)
      .$attrs
      .valueColors[2][0]
      .color
      .toLowerCase(), Color.Yellow)
    assertEqual(JSON.parse(valueColors1)
      .$attrs
      .valueColors[3][0]
      .color
      .toLowerCase(), Color.Brown)

    let valueColors2: string = await dataPanel2.getInspectorInfo()
    assertEqual(JSON.parse(valueColors2).$attrs.valueColors[0][0].color, '#FF0000FF')
    assertEqual(JSON.parse(valueColors2).$attrs.valueColors[1][0].color, '#FFFFA500')
    assertEqual(JSON.parse(valueColors2).$attrs.valueColors[2][0].color, '#FFFFFF00')
    assertEqual(JSON.parse(valueColors2).$attrs.valueColors[3][0].color, '#FF00FF00')

    await button1.tap()
    let valueColors3: string = await dataPanel1.getInspectorInfo()
    assertEqual(JSON.parse(valueColors3).$attrs.valueColors[0][0].color, '#FF00FF00')
    assertEqual(JSON.parse(valueColors3)
      .$attrs
      .valueColors[1][0]
      .color
      .toLowerCase(), '#20e38c8c')
    assertEqual(JSON.parse(valueColors3)
      .$attrs
      .valueColors[2][0]
      .color
      .toLowerCase(), '#201660e0')
    assertEqual(JSON.parse(valueColors3)
      .$attrs
      .valueColors[3][0]
      .color
      .toLowerCase(), '#201bf5df')

    await button2.tap()
    let valueColors4: string = await dataPanel1.getInspectorInfo()
    assertEqual(JSON.parse(valueColors4).$attrs.valueColors[0][0].color, $r('app.color.data_panel_resource_color3'))
    assertEqual(JSON.parse(valueColors4).$attrs.valueColors[1][0].color, $r('app.color.data_panel_resource_color5'))
    assertEqual(JSON.parse(valueColors4).$attrs.valueColors[2][0].color, $r('app.color.data_panel_resource_color1'))
    assertEqual(JSON.parse(valueColors4).$attrs.valueColors[3][0].color, $r('app.color.data_panel_resource_color6'))
  }, 0)
}