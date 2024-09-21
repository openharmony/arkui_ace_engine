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

export default async function dataPanelValueColorsTest_one() {
  /*
  * DataPanel组件 ValueColors属性
  * 找到画面id为dataPanelValueColors1，dataPanelValueColors2的DataPanel组件
  * 找到画面文本DataPanelValueColors1,DataPanelValueColors2的Button组件
  * 获取valueColors1的valueColors属性color与期待值[[{color:Color.Gray,offset:'0.000000'},{color:Color.Blue,offset:'1.000000'}],
  * [{color:Color.Green,offset:'0.000000'},{color:Color.Orange,offset:'1.000000'}],[{color:Color.Pink,offset:'0.000000'},
  * {color:Color.Yellow,offset:'1.000000'}][{color:Color.Red,offset:'0.000000'},{color:Color.Brown,offset:'1.000000'}]]比对
  * 获取valueColors1的valueColors属性color与期待值[[{color:"#65EEC9A3",offset:$r('app.float.data_panel_offset_min')},
  * {color:"#FFEF629F",offset:$r('app.float.data_panel_offset_max')}],[{color:"#FF67F9D4",offset:$r('app.float.data_panel_offset_min')},
  * {color:"#FFFF9554",offset:$r('app.float.data_panel_offset_max')}],[{color:"#6572B513",offset:$r('app.float.data_panel_offset_min')},
  * {color:"#6508efa6",offset: $r('app.float.data_panel_offset_max')}],[{color:"#65ed08f5",offset:$r('app.float.data_panel_offset_min')},
  * {color:"#65ef0849",offset:$r('app.float.data_panel_offset_max')}]]比对
  * 点击button1，变更valueColors1的valueColors属性为[[{color:'#FF317AF7',offset:'0.000000'},{color:'#FF5BA854',offset:'1.000000'}],[{color:'#FFE08C3A',offset:'0.000000'},
  * {color:'#FFFFA500',offset:'1.000000'}],[{color:'#FFFFFF00',offset:'0.000000'},{color:'#FF008000',offset:'1.000000'}],[{color:'#FFFFA500',offset:'0.000000'},{color:'#FFFFFF00',offset:'1.000000'}]]
  * 获取dataPanel1的ValueColors属性与期待值[[{color:'#FF317AF7',offset:'0.000000'},{color:'#FF5BA854',offset:'1.000000'}],[{color:'#FFE08C3A',offset:'0.000000'},{color:'#FFFFA500',offset:'1.000000'}],
  * [{color:'#FFFFFF00',offset:'0.000000'},{color:'#FF008000',offset:'1.000000'}],[{color:'#FFFFA500',offset:'0.000000'},{color:'#FFFFFF00',offset:'1.000000'}]]比对
  * 点击button2，变更valueColors4的valueColors[0]的colorStops[0]的属性为[[{color:$r('app.color.data_panel_resource_color2'),offset:'0.000000'},
  * {color:$r('app.color.data_panel_resource_color8'),offset:'1.000000'}],[{color:$r('app.color.data_panel_resource_color1'),offset:'0.000000'},
  * {color:$r('app.color.data_panel_resource_color5'),offset:'1.000000'}],[{color:$r('app.color.data_panel_resource_color4'),offset:'0.000000'},
  * {color:$r('app.color.data_panel_resource_color6'),offset:'1.000000'}],[{color:$r('app.color.data_panel_resource_color7'),offset:'0.000000'},
  * {color:$r('app.color.data_panel_resource_color3'),offset:'1.000000'}]]
  * 获取dataPanel1的ValueColors属性与期待值[[{color:$r('app.color.data_panel_resource_color2'),offset:'0.000000'},
  * {color:$r('app.color.data_panel_resource_color8'),offset:'1.000000'}],[{color:$r('app.color.data_panel_resource_color1'),offset:'0.000000'},
  * {color:$r('app.color.data_panel_resource_color5'),offset:'1.000000'}],[{color:$r('app.color.data_panel_resource_color4'),offset:'0.000000'},
  * {color:$r('app.color.data_panel_resource_color6'),offset:'1.000000'}],[{color:$r('app.color.data_panel_resource_color7'),offset:'0.000000'},
  * {color:$r('app.color.data_panel_resource_color3'),offset:'1.000000'}]]比对
  */
  defineTest('dataPanelValueColorsTestDemo_one', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('dataPanelValueColorsTestDemo_one running')
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
      .toLowerCase(), Color.Gray)
    assertEqual(JSON.parse(valueColors1)
      .$attrs
      .valueColors[0][0]
      .offset, '0.000000')
    assertEqual(JSON.parse(valueColors1)
      .$attrs
      .valueColors[0][1]
      .color
      .toLowerCase(), Color.Blue)
    assertEqual(JSON.parse(valueColors1)
      .$attrs
      .valueColors[0][1]
      .offset, '1.000000')
    assertEqual(JSON.parse(valueColors1)
      .$attrs
      .valueColors[1][0]
      .color
      .toLowerCase(), Color.Green)
    assertEqual(JSON.parse(valueColors1)
      .$attrs
      .valueColors[1][0]
      .offset, '0.000000')
    assertEqual(JSON.parse(valueColors1)
      .$attrs
      .valueColors[1][1]
      .color
      .toLowerCase(), Color.Orange)
    assertEqual(JSON.parse(valueColors1)
      .$attrs
      .valueColors[1][1]
      .offset, '1.000000')
    assertEqual(JSON.parse(valueColors1)
      .$attrs
      .valueColors[2][0]
      .color
      .toLowerCase(), Color.Pink)
    assertEqual(JSON.parse(valueColors1)
      .$attrs
      .valueColors[2][0]
      .offset, '0.000000')
    assertEqual(JSON.parse(valueColors1)
      .$attrs
      .valueColors[2][1]
      .color
      .toLowerCase(), Color.Yellow)
    assertEqual(JSON.parse(valueColors1)
      .$attrs
      .valueColors[2][1]
      .offset, '1.000000')
    assertEqual(JSON.parse(valueColors1)
      .$attrs
      .valueColors[3][0]
      .color
      .toLowerCase(), Color.Red)
    assertEqual(JSON.parse(valueColors1)
      .$attrs
      .valueColors[3][0]
      .offset, '0.000000')
    assertEqual(JSON.parse(valueColors1)
      .$attrs
      .valueColors[3][1]
      .color
      .toLowerCase(), Color.Brown)
    assertEqual(JSON.parse(valueColors1)
      .$attrs
      .valueColors[3][1]
      .offset, '1.000000')

    let valueColors2: string = await dataPanel2.getInspectorInfo()
    assertEqual(JSON.parse(valueColors2)
      .$attrs
      .valueColors[0][0]
      .color, "#65EEC9A3")
    assertEqual(JSON.parse(valueColors2)
      .$attrs
      .valueColors[0][0]
      .offset, $r('app.float.data_panel_offset_min'))
    assertEqual(JSON.parse(valueColors2)
      .$attrs
      .valueColors[0][1]
      .color, "#FFEF629F")
    assertEqual(JSON.parse(valueColors2)
      .$attrs
      .valueColors[0][1]
      .offset, $r('app.float.data_panel_offset_max'))
    assertEqual(JSON.parse(valueColors2)
      .$attrs
      .valueColors[1][0]
      .color, "#FF67F9D4")
    assertEqual(JSON.parse(valueColors2)
      .$attrs
      .valueColors[1][0]
      .offset, $r('app.float.data_panel_offset_min'))
    assertEqual(JSON.parse(valueColors2)
      .$attrs
      .valueColors[1][1]
      .color, "#FFFF9554")
    assertEqual(JSON.parse(valueColors2)
      .$attrs
      .valueColors[1][1]
      .offset, $r('app.float.data_panel_offset_max'))
    assertEqual(JSON.parse(valueColors2)
      .$attrs
      .valueColors[2][0]
      .color, "#6572B513")
    assertEqual(JSON.parse(valueColors2)
      .$attrs
      .valueColors[2][0]
      .offset, $r('app.float.data_panel_offset_min'))
    assertEqual(JSON.parse(valueColors2)
      .$attrs
      .valueColors[2][1]
      .color
      .toLowerCase(), "#6508efa6")
    assertEqual(JSON.parse(valueColors2)
      .$attrs
      .valueColors[2]
      .colorStops[1]
      .offset, $r('app.float.data_panel_offset_max'))
    assertEqual(JSON.parse(valueColors2)
      .$attrs
      .valueColors[3][0]
      .color
      .toLowerCase(), "#65ed08f5")
    assertEqual(JSON.parse(valueColors2)
      .$attrs
      .valueColors[3]
      .colorStops[0]
      .offset, $r('app.float.data_panel_offset_min'))
    assertEqual(JSON.parse(valueColors2)
      .$attrs
      .valueColors[3][1]
      .color
      .toLowerCase(), "#65ef0849")
    assertEqual(JSON.parse(valueColors2)
      .$attrs
      .valueColors[3]
      .colorStops[1]
      .offset, $r('app.float.data_panel_offset_max'))

    await button1.tap()
    let valueColors3: string = await dataPanel1.getInspectorInfo()
    assertEqual(JSON.parse(valueColors3)
      .$attrs
      .valueColors[0][0]
      .color, '#FF317AF7')
    assertEqual(JSON.parse(valueColors3)
      .$attrs
      .valueColors[0][0]
      .offset, '0.000000')
    assertEqual(JSON.parse(valueColors3)
      .$attrs
      .valueColors[0][1]
      .color, '#FF5BA854')
    assertEqual(JSON.parse(valueColors3)
      .$attrs
      .valueColors[0][1]
      .offset, '1.000000')
    assertEqual(JSON.parse(valueColors3)
      .$attrs
      .valueColors[1][0]
      .color, '#FFE08C3A')
    assertEqual(JSON.parse(valueColors3)
      .$attrs
      .valueColors[1][0]
      .offset, '0.000000')
    assertEqual(JSON.parse(valueColors3)
      .$attrs
      .valueColors[1][1]
      .color, '#FFFFA500')
    assertEqual(JSON.parse(valueColors3)
      .$attrs
      .valueColors[1][1]
      .offset, '1.000000')
    assertEqual(JSON.parse(valueColors3)
      .$attrs
      .valueColors[2][0]
      .color, '#FFFFFF00')
    assertEqual(JSON.parse(valueColors3)
      .$attrs
      .valueColors[2][0]
      .offset, '0.000000')
    assertEqual(JSON.parse(valueColors3)
      .$attrs
      .valueColors[2][1]
      .color, '#FF008000')
    assertEqual(JSON.parse(valueColors3)
      .$attrs
      .valueColors[2][1]
      .offset, '1.000000')
    assertEqual(JSON.parse(valueColors3)
      .$attrs
      .valueColors[3][0]
      .color, '#FFFFA500')
    assertEqual(JSON.parse(valueColors3)
      .$attrs
      .valueColors[3][0]
      .offset, '0.000000')
    assertEqual(JSON.parse(valueColors3)
      .$attrs
      .valueColors[3][1]
      .color, '#FFFFFF00')
    assertEqual(JSON.parse(valueColors3)
      .$attrs
      .valueColors[3][1]
      .offset, '1.000000')

    await button2.tap()
    let valueColors4: string = await dataPanel1.getInspectorInfo()
    assertEqual(JSON.parse(valueColors4)
      .$attrs
      .valueColors[0][0]
      .color, $r('app.color.data_panel_resource_color2'))
    assertEqual(JSON.parse(valueColors4)
      .$attrs
      .valueColors[0][0]
      .offset, '0.000000')
    assertEqual(JSON.parse(valueColors4)
      .$attrs
      .valueColors[0][1]
      .color, $r('app.color.data_panel_resource_color8'))
    assertEqual(JSON.parse(valueColors4)
      .$attrs
      .valueColors[0][1]
      .offset, '1.000000')
    assertEqual(JSON.parse(valueColors4)
      .$attrs
      .valueColors[1][0]
      .color, $r('app.color.data_panel_resource_color1'))
    assertEqual(JSON.parse(valueColors4)
      .$attrs
      .valueColors[1][0]
      .offset, '0.000000')
    assertEqual(JSON.parse(valueColors4)
      .$attrs
      .valueColors[1][1]
      .color, $r('app.color.data_panel_resource_color5'))
    assertEqual(JSON.parse(valueColors4)
      .$attrs
      .valueColors[1][1]
      .offset, '1.000000')
    assertEqual(JSON.parse(valueColors4)
      .$attrs
      .valueColors[2][0]
      .color, $r('app.color.data_panel_resource_color4'))
    assertEqual(JSON.parse(valueColors4)
      .$attrs
      .valueColors[2][0]
      .offset, '0.000000')
    assertEqual(JSON.parse(valueColors4)
      .$attrs
      .valueColors[2][1]
      .color, $r('app.color.data_panel_resource_color6'))
    assertEqual(JSON.parse(valueColors4)
      .$attrs
      .valueColors[2][1]
      .offset, '1.000000')
    assertEqual(JSON.parse(valueColors4)
      .$attrs
      .valueColors[3][0]
      .color, $r('app.color.data_panel_resource_color7'))
    assertEqual(JSON.parse(valueColors4)
      .$attrs
      .valueColors[3][0]
      .offset, '0.000000')
    assertEqual(JSON.parse(valueColors4)
      .$attrs
      .valueColors[3][1]
      .color, $r('app.color.data_panel_resource_color3'))
    assertEqual(JSON.parse(valueColors4)
      .$attrs
      .valueColors[3][1]
      .offset, '1.000000')
  }, 0)
}