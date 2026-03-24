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

import router from '@ohos.router';
@Entry
@Component
struct ParticleExample1 {
  build() {
    Column() {
      Column() {
        Button("返回")
          .onClick(() => {
            router.back()
          })
      }
      .width('100%')
      .height('10%')
      .backgroundColor(Color.Orange)
      .justifyContent(FlexAlign.Center)
      Stack() {
        Text()
          .width(300).height(300).backgroundColor(Color.Black)
        Particle({particles:[
          {
            emitter:{
              particle:{
                type:ParticleType.POINT,//粒子类型
                config:{
                  radius:10//圆点半径
                },
                count: 500,//粒子总数
                lifetime:10000,//粒子生命周期，单位ms
                lifetimeRange:100//粒子生命周期取值范围，单位ms
              },
              emitRate:10,//每秒发射粒子数
              position:[0,0],
              shape:ParticleEmitterShape.RECTANGLE//发射器形状
            },
            color:{
              range:[Color.Red,Color.Yellow],//初始颜色范围
              updater:{
                type:ParticleUpdater.CURVE,//变化方式为曲线变化
                config:[
                  {
                    from:Color.White,//变化起始值
                    to:Color.Pink,//变化终点值
                    startMillis:0,//开始时间
                    endMillis:3000,//结束时间
                    curve:Curve.EaseIn//变化曲线
                  },
                  {
                    from:Color.Pink,
                    to:Color.Orange,
                    startMillis:3000,
                    endMillis:5000,
                    curve:Curve.EaseIn
                  },
                  {
                    from:Color.Orange,
                    to:Color.Pink,
                    startMillis:5000,
                    endMillis:8000,
                    curve:Curve.EaseIn
                  },
                ]
              }
            },
            opacity:{
              range:[0.0,1.0],//粒子透明度的初始值从【0.0到1.0】随机产生
              updater:{
                type:ParticleUpdater.CURVE,
                config:[
                  {
                    from:0.0,
                    to:1.0,
                    startMillis:0,
                    endMillis:3000,
                    curve:Curve.EaseIn
                  },
                  {
                    from:1.0,
                    to:0.0,
                    startMillis:5000,
                    endMillis:10000,
                    curve:Curve.EaseIn
                  }
                ]
              }
            },
            scale:{
              range:[0.0,0.0],
              updater:{
                type:ParticleUpdater.CURVE,
                config:[
                  {
                    from:0.0,
                    to:0.5,
                    startMillis:0,
                    endMillis:3000,
                    curve: Curve.EaseIn
                  }
                ]
              }
            },
            acceleration:{//加速度的配置，从大小和方向两个维度变化，speed表示加速度大小，angle表示加速度方向
              speed:{
                range:[3,9],
                updater:{
                  type:ParticleUpdater.RANDOM,//Speed的变化方式是随机变化
                  config:[1,20]
                }
              },
              angle:{
                range:[90,90]
              }
            }

          }
        ]
        }).width(300).height(300)
      }.width("100%").height("90%").align(Alignment.Center)
    }
  }
}