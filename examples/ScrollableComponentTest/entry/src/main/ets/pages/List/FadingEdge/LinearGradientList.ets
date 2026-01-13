/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

/*
 * Description: 通过linearGradient模拟实现FadingEdge的效果
 * Writer: dailihuan
 */

@Entry
@Component
struct LinearGradientList {
  @State data: string[] = ['美食','地图','理财','购物','导航','我的','买房','买车']

  build() {
    Column({space:60}){
      Text('两边文字透明渐变')
        .fontSize(20)
        .margin({bottom:20})
      Row(){
        Row(){
          List({space:20}){
            ForEach(this.data,(item:string)=>{
              ListItem(){
                Text(item)
                  .fontSize(30)
              }
            },(item:string)=>item)
          }
          .scrollBar(BarState.Off)
          .listDirection(Axis.Horizontal)
        }
        .blendMode(BlendMode.SRC_IN,BlendApplyType.OFFSCREEN)
        .backgroundColor(Color.Transparent)
      }
      .linearGradient({
        angle: 90,
        colors: [['rgba(0, 0, 0, 0)', 0], ['rgba(0, 0, 0, 1)', 0.2], ['rgba(0, 0, 0, 1)', 0.8], ['rgba(0, 0, 0, 0)', 1]]
      })
      .blendMode(BlendMode.SRC_OVER,BlendApplyType.OFFSCREEN)
      .width('100%')
      .height(40)
    }
  }
}