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

export default async function dataPanelTrackShadowTest_one() {
  /*
   * DataPanel组件 TrackShadow属性
   * 找到画面id为dataPanelTrackShadow1，dataPanelTrackShadow2的DataPanel组件
   * 找到画面文本为DataPanelTrackShadow1,DataPanelTrackShadow2的Button组件
   * 获取dataPanel1的TrackShadow属性与期待值{radius:'50.000000',[[{color:Color.Gray,offset:'0.000000'},{color:Color.Blue,offset:'1.000000'}],
   * [{color:Color.Green,offset:'0.000000'},{color:Color.Orange,offset:'1.000000'}],[{color:Color.Pink,offset:'0.000000'},{color:Color.Yellow,offset:'1.000000'}],
   * [{color:Color.Red,offset:'0.000000'},{color:Color.Brown,offset:'1.000000'}]],offsetX:$r('app.integer.data_panel_Number'),
   * offsetY:$r('app.integer.data_panel_Number')}比对
   * 获取dataPanel2的TrackShadow属性与期待值{radius:$r('app.integer.data_panel_number'),[[{color:"#65EEC9A3",offset:$r('app.float.data_panel_offset_min')},
   * {color:"#FFEF629F",offset:$r('app.float.data_panel_offset_max')}],[{color:"#FF67F9D4",offset:$r('app.float.data_panel_offset_min')},
   * {color:"#FFFF9554",offset:$r('app.float.data_panel_offset_max')}],[{color:"#6572B513",offset:$r('app.float.data_panel_offset_min')},
   * {color:"#6508efa6",offset:$r('app.float.data_panel_offset_max')}],[{color:"#65ed08f5",offset:$r('app.float.data_panel_offset_min')},
   * {color:"#65ef0849",offset:$r('app.float.data_panel_offset_max')}]],offsetX:'100.000000',offsetY:'100.000000' }比对
   * 点击button1，变更dataPanel1的TrackShadow属性值为{radius:'10.000000',[[{color:0x317AF7,offset:'0.000000'},{color:0x5BA854,offset:'1.000000'}],[{color:0xE08C3A,offset:'0.000000'},
   * {color:0xFFA500,offset:'1.000000'}],[{color:0xFFFF00,offset:'0.000000'},{color:0x008000,offset:'1.000000'}],[{color:0xFFA500,offset:'0.000000'},{color:0xFFFF00,offset:'1.000000'}]],offsetX:'10.000000',offsetY:'20.000000'}
   * 获取dataPanel1的TrackShadow属性与期待值{radius:'10.000000',[[{color:0x317AF7,offset:'0.000000'},{color:0x5BA854,offset:'1.000000'}],[{color:0xE08C3A,offset:'0.000000'},{color:0xFFA500,offset:'1.000000'}],
   * [{color:0xFFFF00,offset:'0.000000'},{color:0x008000,offset:'1.000000'}],[{color:0xFFA500,offset:'0.000000'},{color:0xFFFF00,offset:'1.000000'}]],offsetX:'10.000000',offsetY:'20.000000'}比对
   * 点击button2，变更dataPanel1的TrackShadow属性值为{radius:'10.000000',[[{color:$r('app.color.data_panel_resource_color2'),offset:'0.000000'},
   * {color:$r('app.color.data_panel_resource_color8'),offset:'1.000000'}], [{color:$r('app.color.data_panel_resource_color1'),offset:'0.000000'},
   * {color:$r('app.color.data_panel_resource_color5'),offset:'1.000000'}],[{color:$r('app.color.data_panel_resource_color4')offset:'0.000000'},
   * {color:$r('app.color.data_panel_resource_color6'),offset:'1.000000'}],[{color:$r('app.color.data_panel_resource_color7'),offset:'0.000000'},
   * {color:$r('app.color.data_panel_resource_color3'),offset:'1.000000'}]],trackShadow.offsetX:'20.000000',trackShadow.offsetY:'10.000000'}
   * 获取dataPanel1的TrackShadow属性与期待值{radius:'10.000000',[[{color:$r('app.color.data_panel_resource_color2'),offset:'0.000000'},
   * {color:$r('app.color.data_panel_resource_color8'),offset:'1.000000'}],[{color:$r('app.color.data_panel_resource_color1'),offset:'0.000000'},
   * {color:$r('app.color.data_panel_resource_color5'),offset:'1.000000'}],[{color:$r('app.color.data_panel_resource_color4')offset:'0.000000'},
   * {color:$r('app.color.data_panel_resource_color6'),offset:'1.000000'}],[{color:$r('app.color.data_panel_resource_color7'),offset:'0.000000'},
   * {color:$r('app.color.data_panel_resource_color3'),offset:'1.000000'}]],trackShadow.offsetX:'20.000000',trackShadow.offsetY:'10.000000'}比对
   */
  defineTest('dataPanelTrackShadowTestDemo_one', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('dataPanelTrackShadowTestDemo_one running')
    let driver: Tester = Tester.create()
    let dataPanel1: Component = await driver.findComponent(Matcher.create().id('dataPanelTrackShadow1').enabled(true))
    let dataPanel2: Component = await driver.findComponent(Matcher.create().id('dataPanelTrackShadow2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('DataPanelTrackShadow1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('DataPanelTrackShadow2').enabled(true))

    let trackShadow1: string = await dataPanel1.getInspectorInfo()
    assertEqual(JSON.parse(trackShadow1).$attrs.trackShadow.radius, '50.000000')
    assertEqual(JSON.parse(trackShadow1)
      .$attrs
      .trackShadow
      .colors[0][0]
      .color
      .toLowerCase(), Color.Gray)
    assertEqual(JSON.parse(trackShadow1)
      .$attrs
      .trackShadow
      .colors[0][0]
      .offset, '0.000000')
    assertEqual(JSON.parse(trackShadow1)
      .$attrs
      .trackShadow
      .colors[0][1]
      .color
      .toLowerCase(), Color.Blue)
    assertEqual(JSON.parse(trackShadow1)
      .$attrs
      .trackShadow
      .colors[0][1]
      .offset, '1.000000')
    assertEqual(JSON.parse(trackShadow1)
      .$attrs
      .trackShadow
      .colors[1][0]
      .color
      .toLowerCase(), Color.Green)
    assertEqual(JSON.parse(trackShadow1)
      .$attrs
      .trackShadow
      .colors[1][0]
      .offset, '0.000000')
    assertEqual(JSON.parse(trackShadow1)
      .$attrs
      .trackShadow
      .colors[1][1]
      .color
      .toLowerCase(), Color.Orange)
    assertEqual(JSON.parse(trackShadow1)
      .$attrs
      .trackShadow
      .colors[1][1]
      .offset, '1.000000')
    assertEqual(JSON.parse(trackShadow1)
      .$attrs
      .trackShadow
      .colors[2][0]
      .color
      .toLowerCase(), Color.Pink)
    assertEqual(JSON.parse(trackShadow1)
      .$attrs
      .trackShadow
      .colors[2][0]
      .offset, '0.000000')
    assertEqual(JSON.parse(trackShadow1)
      .$attrs
      .trackShadow
      .colors[2][1]
      .color
      .toLowerCase(), Color.Yellow)
    assertEqual(JSON.parse(trackShadow1)
      .$attrs
      .trackShadow
      .colors[2][1]
      .offset, '1.000000')
    assertEqual(JSON.parse(trackShadow1)
      .$attrs
      .trackShadow
      .colors[3][0]
      .color
      .toLowerCase(), Color.Red)
    assertEqual(JSON.parse(trackShadow1)
      .$attrs
      .trackShadow
      .colors[3][0]
      .offset, '0.000000')
    assertEqual(JSON.parse(trackShadow1)
      .$attrs
      .trackShadow
      .colors[3][1]
      .color
      .toLowerCase(), Color.Brown)
    assertEqual(JSON.parse(trackShadow1)
      .$attrs
      .trackShadow
      .colors[3][1]
      .offset, '1.000000')
    assertEqual(JSON.parse(trackShadow1).$attrs.trackShadow.offsetX, $r("app.string.data_panel_number"))
    assertEqual(JSON.parse(trackShadow1).$attrs.trackShadow.offsetY, $r("app.string.data_panel_number"))

    let trackShadow2: string = await dataPanel2.getInspectorInfo()
    assertEqual(JSON.parse(trackShadow2).$attrs.trackShadow.radius, $r("app.string.data_panel_number"))
    assertEqual(JSON.parse(trackShadow2)
      .$attrs
      .trackShadow
      .colors[0][0]
      .color, "#65EEC9A3")
    assertEqual(JSON.parse(trackShadow2)
      .$attrs
      .trackShadow
      .colors[0][0]
      .offset, $r('app.float.data_panel_offset_min'))
    assertEqual(JSON.parse(trackShadow2)
      .$attrs
      .trackShadow
      .colors[0][1]
      .color, "#FFEF629F")
    assertEqual(JSON.parse(trackShadow2)
      .$attrs
      .trackShadow
      .colors[0][1]
      .offset, $r('app.float.data_panel_offset_max'))
    assertEqual(JSON.parse(trackShadow2)
      .$attrs
      .trackShadow
      .colors[1][0]
      .color, "#FF67F9D4")
    assertEqual(JSON.parse(trackShadow2)
      .$attrs
      .trackShadow
      .colors[1][0]
      .offset, $r('app.float.data_panel_offset_min'))
    assertEqual(JSON.parse(trackShadow2)
      .$attrs
      .trackShadow
      .colors[1][1]
      .color, "#FFFF9554")
    assertEqual(JSON.parse(trackShadow2)
      .$attrs
      .trackShadow
      .colors[1][1]
      .offset, $r('app.float.data_panel_offset_max'))
    assertEqual(JSON.parse(trackShadow2)
      .$attrs
      .trackShadow
      .colors[2][0]
      .color, "#6572B513")
    assertEqual(JSON.parse(trackShadow2)
      .$attrs
      .trackShadow
      .colors[2][0]
      .offset, $r('app.float.data_panel_offset_min'))
    assertEqual(JSON.parse(trackShadow2)
      .$attrs
      .trackShadow
      .colors[2][1]
      .color
      .toLowerCase(), "#6508efa6")
    assertEqual(JSON.parse(trackShadow2)
      .$attrs
      .trackShadow
      .colors[2][1]
      .offset, $r('app.float.data_panel_offset_max'))
    assertEqual(JSON.parse(trackShadow2)
      .$attrs
      .trackShadow
      .colors[3][0]
      .color
      .toLowerCase(), "#65ed08f5")
    assertEqual(JSON.parse(trackShadow2)
      .$attrs
      .trackShadow
      .colors[3][0]
      .offset, $r('app.float.data_panel_offset_min'))
    assertEqual(JSON.parse(trackShadow2)
      .$attrs
      .trackShadow
      .colors[3][1]
      .color
      .toLowerCase(), "#65ef0849")
    assertEqual(JSON.parse(trackShadow2)
      .$attrs
      .trackShadow
      .colors[3][1]
      .offset, $r('app.float.data_panel_offset_max'))
    assertEqual(JSON.parse(trackShadow2).$attrs.trackShadow.offsetX, '100.000000')
    assertEqual(JSON.parse(trackShadow2).$attrs.trackShadow.offsetY, '100.000000')

    await button1.tap()
    let trackShadow3: string = await dataPanel1.getInspectorInfo()
    assertEqual(JSON.parse(trackShadow3).$attrs.trackShow.radius, '10.000000')
    assertEqual(JSON.parse(trackShadow3)
      .$attrs
      .trackShadow
      .colors[0][0]
      .color, 0x317AF7)
    assertEqual(JSON.parse(trackShadow3)
      .$attrs
      .trackShadow
      .colors[0][0]
      .offset, '0.000000')
    assertEqual(JSON.parse(trackShadow3)
      .$attrs
      .trackShadow
      .colors[0][1]
      .color, 0x5BA854)
    assertEqual(JSON.parse(trackShadow3)
      .$attrs
      .trackShadow
      .colors[0][1]
      .offset, '1.000000')
    assertEqual(JSON.parse(trackShadow3)
      .$attrs
      .trackShadow
      .colors[1][0]
      .color, 0xE08C3A)
    assertEqual(JSON.parse(trackShadow3)
      .$attrs
      .trackShadow
      .colors[1][0]
      .offset, '0.000000')
    assertEqual(JSON.parse(trackShadow3)
      .$attrs
      .trackShadow
      .colors[1][1]
      .color, 0xFFA500)
    assertEqual(JSON.parse(trackShadow3)
      .$attrs
      .trackShadow
      .colors[1][1]
      .offset, '1.000000')
    assertEqual(JSON.parse(trackShadow3)
      .$attrs
      .trackShadow
      .colors[2][0]
      .color
      .toLowerCase(), '0xFFFF00')
    assertEqual(JSON.parse(trackShadow3)
      .$attrs
      .trackShadow
      .colors[2][0]
      .offset, '0.000000')
    assertEqual(JSON.parse(trackShadow3)
      .$attrs
      .trackShadow
      .colors[2][1]
      .color, 0x008000)
    assertEqual(JSON.parse(trackShadow3)
      .$attrs
      .trackShadow
      .colors[2][1]
      .offset, '1.000000')
    assertEqual(JSON.parse(trackShadow3)
      .$attrs
      .trackShadow
      .colors[3][0]
      .color, '0xFFA500')
    assertEqual(JSON.parse(trackShadow3)
      .$attrs
      .trackShadow
      .colors[3][0]
      .offset, '0.000000')
    assertEqual(JSON.parse(trackShadow3)
      .$attrs
      .trackShadow
      .colors[3][1]
      .color
      .toLowerCase(), '0xFFFF00')
    assertEqual(JSON.parse(trackShadow3)
      .$attrs
      .trackShadow
      .colors[3][1]
      .offset, '1.000000')
    assertEqual(JSON.parse(trackShadow3).$attrs.trackShadow.offsetX, '10.000000')
    assertEqual(JSON.parse(trackShadow3).$attrs.trackShadow.offsetY, '20.000000')

    await button2.tap()
    let trackShadow4: string = await dataPanel1.getInspectorInfo()
    assertEqual(JSON.parse(trackShadow4).$attrs.trackShadow.radius, '10.000000')
    assertEqual(JSON.parse(trackShadow4)
      .$attrs
      .trackShadow
      .colors[0][0]
      .color, $r('app.color.data_panel_resource_color2'))
    assertEqual(JSON.parse(trackShadow4)
      .$attrs
      .trackShadow
      .colors[0][0]
      .offset, '0.000000')
    assertEqual(JSON.parse(trackShadow4)
      .$attrs
      .trackShadow
      .colors[0][1]
      .color, $r('app.color.data_panel_resource_color8'))
    assertEqual(JSON.parse(trackShadow4)
      .$attrs
      .trackShadow
      .colors[0][1]
      .offset, '1.000000')
    assertEqual(JSON.parse(trackShadow4)
      .$attrs
      .trackShadow
      .colors[1][0]
      .color, $r('app.color.data_panel_resource_color1'))
    assertEqual(JSON.parse(trackShadow4)
      .$attrs
      .trackShadow
      .colors[1][0]
      .offset, '0.000000')
    assertEqual(JSON.parse(trackShadow4)
      .$attrs
      .trackShadow
      .colors[1][1]
      .color, $r('app.color.data_panel_resource_color5'))
    assertEqual(JSON.parse(trackShadow4)
      .$attrs
      .trackShadow
      .colors[1][1]
      .offset, '1.000000')
    assertEqual(JSON.parse(trackShadow4)
      .$attrs
      .trackShadow
      .colors[2][0]
      .color, $r('app.color.data_panel_resource_color4'))
    assertEqual(JSON.parse(trackShadow4)
      .$attrs
      .trackShadow
      .colors[2][0]
      .offset, '0.000000')
    assertEqual(JSON.parse(trackShadow4)
      .$attrs
      .trackShadow
      .colors[2][1]
      .color, $r('app.color.data_panel_resource_color6'))
    assertEqual(JSON.parse(trackShadow4)
      .$attrs
      .trackShadow
      .colors[2][1]
      .offset, '1.000000')
    assertEqual(JSON.parse(trackShadow4)
      .$attrs
      .trackShadow
      .colors[3][0]
      .color, $r('app.color.data_panel_resource_color7'))
    assertEqual(JSON.parse(trackShadow4)
      .$attrs
      .trackShadow
      .colors[3][0]
      .offset, '0.000000')
    assertEqual(JSON.parse(trackShadow4)
      .$attrs
      .trackShadow
      .colors[3][1]
      .color, $r('app.color.data_panel_resource_color3'))
    assertEqual(JSON.parse(trackShadow4)
      .$attrs
      .trackShadow
      .colors[3][1]
      .offset, '1.000000')
    assertEqual(JSON.parse(trackShadow4).$attrs.trackShadow.offsetX, '20.000000')
    assertEqual(JSON.parse(trackShadow4).$attrs.trackShadow.offsetY, '10.000000')
  }, 0)
}