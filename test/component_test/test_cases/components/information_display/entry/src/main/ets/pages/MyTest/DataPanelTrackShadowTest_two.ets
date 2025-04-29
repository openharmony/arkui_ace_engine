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

export default async function dataPanelTrackShadowTest_two() {
  /*
   * DataPanel组件 TrackShadow属性
   * 找到画面id为dataPanelInput1，dataPanelInput2的DataPanel组件
   * 找到画面文本为DataPanelValueColors1,DataPanelValueColors2的Button组件
   * 获取trackShadow1的trackShadow属性与期待值{radius:'50.000000',[color:Color.White, color:Color.Blue, color:Color.Yellow, color:Color.Brown], offsetX:$r('app.integer.data_panel_Number'), offsetY:$r('app.integer.data_panel_Number'))}比对
   * 获取trackShadow2的trackShadow属性与期待值{radius:$r('app.integer.data_panel_Number'),[color:'#FF00FF00',color:'#20e38c8c',color:'#201660e0',color:'#201bf5df'], offsetX:'100.000000', offsetY:'100.000000'}比对
   * 点击button1，变更trackShadow3的trackShadow的radius属性值为{radius:'50.000000',[color:'#FFFFFFFF',color:'#FFFFA500',color:'#FFFFFF00',color:'#FF00FF00'],offsetX:$r('app.integer.data_panel_Number'),offsetY:$r('app.integer.data_panel_Number')}
   * 获取dataPanel1的TrackShadow属性与期待值{radius:'50.000000',[color:'#FFFFFFFF',color:'#FFFFA500',color:'#FFFFFF00',color:'#FF00FF00'],offsetX:$r('app.integer.data_panel_Number'),offsetY:$r('app.integer.data_panel_Number')}比对
   * 点击button2，变更trackShadow4的trackShadow的radius属性值为{radius:'50.000000',[colors:$r('app.color.data_panel_resource_color8'),colors:$r('app.color.data_panel_resource_color3'),colors:$r('app.color.data_panel_resource_color5')],offsetX:$r('app.integer.data_panel_Number'),offsetY:$r('app.integer.data_panel_Number')}
   * 获取dataPanel1的TrackShadow属性与期待值{radius:'50.000000',[colors:$r('app.color.data_panel_resource_color8'),colors:$r('app.color.data_panel_resource_color3'),colors:$r('app.color.data_panel_resource_color5')],offsetX:$r('app.integer.data_panel_Number'),offsetY:$r('app.integer.data_panel_Number')}比对
   * 点击button3，变更trackShadow5的trackShadow的属性值为'null'
   * 获取dataPanel1的TrackShadow属性与期待值'null'比对
   */
  defineTest('dataPanelTrackShadowTest_twoDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('dataPanelTrackShadowTest_twoDemo running')
    let driver: Tester = Tester.create()
    let dataPanel1: Component = await driver.findComponent(Matcher.create().id('dataPanelTrackShadow1').enabled(true))
    let dataPanel2: Component = await driver.findComponent(Matcher.create().id('dataPanelTrackShadow2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('DataPanelTrackShadow1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('DataPanelTrackShadow2').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('DataPanelTrackShadow3').enabled(true))

    let trackShadow1: string = await dataPanel1.getInspectorInfo()
    assertEqual(JSON.parse(trackShadow1).$attrs.trackShadow.radius, '50.000000')
    assertEqual(JSON.parse(trackShadow1)
      .$attrs
      .trackShadow
      .colors[0][0]
      .color
      .toLowerCase(), Color.White)
    assertEqual(JSON.parse(trackShadow1)
      .$attrs
      .trackShadow
      .colors[1][0]
      .color
      .toLowerCase(), Color.Blue)
    assertEqual(JSON.parse(trackShadow1)
      .$attrs
      .trackShadow
      .colors[2][0]
      .color
      .toLowerCase(), Color.Yellow)
    assertEqual(JSON.parse(trackShadow1)
      .$attrs
      .trackShadow
      .colors[3][0]
      .color
      .toLowerCase(), Color.Brown)
    assertEqual(JSON.parse(trackShadow1).$attrs.trackShadow.offsetX, $r("app.string.data_panel_number"))
    assertEqual(JSON.parse(trackShadow1).$attrs.trackShadow.offsetY, $r("app.string.data_panel_number"))

    let trackShadow2: string = await dataPanel2.getInspectorInfo()
    assertEqual(JSON.parse(trackShadow2).$attrs.trackShadow.radius, $r("app.string.data_panel_number"))
    assertEqual(JSON.parse(trackShadow2)
      .$attrs
      .trackShadow
      .colors[0][0]
      .color, '#FF00FF00')
    assertEqual(JSON.parse(trackShadow2)
      .$attrs
      .trackShadow
      .colors[1][0]
      .color
      .toLowerCase(), '#20e38c8c')
    assertEqual(JSON.parse(trackShadow2)
      .$attrs
      .trackShadow
      .colors[2][0]
      .color
      .toLowerCase(), '#201660e0')
    assertEqual(JSON.parse(trackShadow2)
      .$attrs
      .trackShadow
      .colors[3][0]
      .color
      .toLowerCase(), '#201bf5df')
    assertEqual(JSON.parse(trackShadow2).$attrs.trackShadow.offsetX, '100.000000')
    assertEqual(JSON.parse(trackShadow2).$attrs.trackShadow.offsetY, '100.000000')

    await button1.tap()
    let trackShadow3: string = await dataPanel1.getInspectorInfo()
    assertEqual(JSON.parse(trackShadow3).$attrs.trackShadow.radius, '50.000000')
    assertEqual(JSON.parse(trackShadow3)
      .$attrs
      .trackShadow
      .colors[0][0]
      .color, '#FFFFFFFF')
    assertEqual(JSON.parse(trackShadow3)
      .$attrs
      .trackShadow
      .colors[1][0]
      .color, '#FFFFA500')
    assertEqual(JSON.parse(trackShadow3)
      .$attrs
      .trackShadow
      .colors[2][0]
      .color, '#FFFFFF00')
    assertEqual(JSON.parse(trackShadow3)
      .$attrs
      .trackShadow
      .colors[3][0]
      .color, '#FF00FF00')
    assertEqual(JSON.parse(trackShadow3).$attrs.trackShadow.offsetX, $r("app.string.data_panel_number"))
    assertEqual(JSON.parse(trackShadow3).$attrs.trackShadow.offsetY, $r("app.string.data_panel_number"))

    await button2.tap()
    let trackShadow4: string = await dataPanel1.getInspectorInfo()
    assertEqual(JSON.parse(trackShadow4).$attrs.trackShadow.radius, '50.000000')
    assertEqual(JSON.parse(trackShadow4)
      .$attrs
      .trackShadow
      .colors[0][0]
      .color, $r('app.color.data_panel_resource_color8'))
    assertEqual(JSON.parse(trackShadow4)
      .$attrs
      .trackShadow
      .colors[1][0]
      .color, $r('app.color.data_panel_resource_color3'))
    assertEqual(JSON.parse(trackShadow4)
      .$attrs
      .trackShadow
      .colors[2][0]
      .color, $r('app.color.data_panel_resource_color5'))
    assertEqual(JSON.parse(trackShadow4).$attrs.trackShadow.offsetX, $r("app.string.data_panel_number"))
    assertEqual(JSON.parse(trackShadow4).$attrs.trackShadow.offsetY, $r("app.string.data_panel_number"))

    await button3.tap()
    let trackShadow5: string = await dataPanel1.getInspectorInfo()
    assertEqual(JSON.parse(trackShadow5).$attrs.trackShadow, 'null')
  }, 0)
}