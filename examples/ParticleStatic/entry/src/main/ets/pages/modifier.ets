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

'use static'
import {
  Entry,
  Text,
  Column,
  Component,
  Button,
  ClickEvent,
  Stack,
  FontWeight,
  Color,
  AttributeModifier,
  ParticleAttribute,
  Row,
  ClickEvent,
  Scroll
} from '@ohos.arkui.component'
import { State, Observed } from '@ohos.arkui.stateManagement'
import hilog from '@ohos.hilog'
import {
  EmitterParticleOptions,
  Particles,
  ParticleType,
  Particle,
  ParticleEmitterShape,
  ParticleUpdater,
  Curve,
  Padding,
  Alignment,
  RippleFieldOptions,
  DisturbanceFieldShape,
  FieldRegion,
  Vector2T,
  ColumnOptions,
  ParticleOptions
} from '@kit.ArkUI'
@Observed
class MyRippleFieldsModifier1 implements AttributeModifier<ParticleAttribute> {
  public isChange: boolean = false;
  applyNormalAttribute(instance: ParticleAttribute): void {
    if (this.isChange) {
      instance.rippleFields([
        {
          amplitude: 120, // 波动场幅值
          wavelength: 5000, // 波动场的波长
          waveSpeed: 20, // 波动场的波速
          center: { x: 150, y: 150 }, // 波动场的力的中心
          attenuation: 1, // 波动场随时间的衰减系数
          region: {
            // 波动场的影响区域
            shape: DisturbanceFieldShape.RECT, // 波动场影响区域的形状
            position: { x: 150, y: 150 }, // 波动场影响区域的区域中心
            size: { width: 300, height: 100 } // 波动场影响区域的大小
          }
        } as RippleFieldOptions
      ])
      console.log('rippleFields1')
    }else{
      instance.rippleFields([
        {
          amplitude: 50, // 波动场幅值
          wavelength: 1000, // 波动场的波长
          waveSpeed: 10, // 波动场的波速
          center: { x: 75, y: 75 }, // 波动场的力的中心
          attenuation: 0.05, // 波动场随时间的衰减系数
          region: {
            // 波动场的影响区域
            shape: DisturbanceFieldShape.CIRCLE, // 波动场影响区域的形状
            position: { x: 75, y: 75 }, // 波动场影响区域的区域中心
            size: { width: 100, height:300 } // 波动场影响区域的大小
          }
        } as RippleFieldOptions
      ])
      console.log('rippleFields2')
    }
    console.log('rippleFields2')
  }
}

@Observed
class MyVelocityFieldsModifier1 implements AttributeModifier<ParticleAttribute> {
  public isChange1: boolean = true;
  applyNormalAttribute(instance: ParticleAttribute): void {
    console.log('velocityFields1')
    if(this.isChange1){
      instance.velocityFields([
        {
          velocity: { x: 20, y: 10 } as Vector2T<double>, // 速度场的速度值
          region: {
            // 速度场的影响区域
            shape: DisturbanceFieldShape.RECT, // 速度场影响区域的形状
            position: { x: 150, y: 150 }, // 速度场影响区域的区域中心
            size: { width: 300, height: 100 } // 速度场影响区域的大小
          } as FieldRegion
        }
      ])
      // console.log('velocityFields2')
    }
    else{
      instance.velocityFields([
        {
          velocity: { x: 30, y: 10 } as Vector2T<double>, // 速度场的速度值
          region: {
            // 速度场的影响区域
            shape: DisturbanceFieldShape.CIRCLE, // 速度场影响区域的形状
            position: { x: 5, y: 50 }, // 速度场影响区域的区域中心
            size: { width: 100, height: 100 } // 速度场影响区域的大小
          } as FieldRegion
        }
      ])
      console.log('velocityFields2')
    }
  }
}

@Observed
class MyRippleFieldsModifier2 implements AttributeModifier<ParticleAttribute> {
  applyNormalAttribute(instance: ParticleAttribute): void {

      instance .rippleFields(
        [{
          amplitude: 120, // 波动场幅值
          wavelength: 500, // 波动场的波长
          waveSpeed: 20, // 波动场的波速
          center: { x: 150, y: 150 }, // 波动场的力的中心
          attenuation: 0, // 波动场随时间的衰减系数
          region: {
            // 波动场的影响区域
            shape: DisturbanceFieldShape.RECT, // 波动场影响区域的形状
            position: { x: 150, y: 150 }, // 波动场影响区域的区域中心
            size: { width: 300, height: 300 } // 波动场影响区域的大小
          }
        } as RippleFieldOptions
        ])
        .velocityFields([
        {
          velocity: { x: 100, y: 0 } as Vector2T<double>, // 速度场的速度值
          region: {
            // 速度场的影响区域
            shape: DisturbanceFieldShape.RECT, // 速度场影响区域的形状
            position: { x: 150, y: 150 }, // 速度场影响区域的区域中心
            size: { width: 200, height: 200 } // 速度场影响区域的大小
          } as FieldRegion
        }
      ])
      console.log('rippleFields1')

    console.log('rippleFields2')
  }
}

// @Observed
// class MyVelocityFieldsModifier2 implements AttributeModifier<ParticleAttribute> {
//   applyNormalAttribute(instance: ParticleAttribute): void {
//     console.log('velocityFields1')
//
//       instance.velocityFields([
//         {
//           velocity: { x: 100, y: 0 } as Vector2T<double>, // 速度场的速度值
//           region: {
//             // 速度场的影响区域
//             shape: DisturbanceFieldShape.RECT, // 速度场影响区域的形状
//             position: { x: 150, y: 150 }, // 速度场影响区域的区域中心
//             size: { width: 200, height: 200 } // 速度场影响区域的大小
//           } as FieldRegion
//         }
//       ])
//       // console.log('velocityFields2')
//   }
// }

@Observed
class MyVelocityFieldsModifier3 implements AttributeModifier<ParticleAttribute> {
  applyNormalAttribute(instance: ParticleAttribute): void {
      instance .velocityFields([
        {
          velocity: { x: 20, y: 10 }as Vector2T<double>, // 速度场的速度值
          region: {
            // 速度场的影响区域
            shape: DisturbanceFieldShape.RECT, // 速度场影响区域的形状
            position: { x: 150, y: 150 }, // 速度场影响区域的区域中心
            size: { width: 300, height: 100 } // 速度场影响区域的大小
          } as FieldRegion
        }
      ])
      console.log('rippleFields1')

    console.log('rippleFields2')
  }
}
// xxx.ets
@Entry
@Component
struct ParticleExample {

  @State myRippleFieldsModifier1: MyRippleFieldsModifier1 = new MyRippleFieldsModifier1();
  @State myVelocityFieldsModifier1: MyVelocityFieldsModifier1 = new MyVelocityFieldsModifier1();
  @State myRippleFieldsModifier2: MyRippleFieldsModifier2 = new MyRippleFieldsModifier2();
  // @State myVelocityFieldsModifier2: MyVelocityFieldsModifier2 = new MyVelocityFieldsModifier2();
  @State myVelocityFieldsModifier3: MyVelocityFieldsModifier3 = new MyVelocityFieldsModifier3();

  @State RippleINDEX: int = 0;
  @State VelocityINDEX: int = 0;
  @State RippleStr: string[] = ['Ripple1', 'Ripple2'];
  @State VelocityStr: string[] = ['Velocity1', 'Velocity2'];
  @State count: int = 1000
  @State particle: EmitterParticleOptions = {
    type: ParticleType.POINT, // 粒子类型
    config: {
      radius: 1 // 圆点半径
    },
    count: this.count, // 粒子总数
    lifetime: 120000, // 粒子生命周期，单位ms
    lifetimeRange: 100 // 粒子生命周期取值范围，单位ms
  } as EmitterParticleOptions

  build() {
    Scroll(){
      Column({ space: 5 } as ColumnOptions) {
        Text('modifier')
          .fontSize(30)
          .fontWeight(FontWeight.Bold)
        Text('波动场')
          .fontSize(30)
          .fontWeight(FontWeight.Bold)
        Stack() {
          Text()
            .width(300).height(300).backgroundColor(Color.Black)
          Particle({
            particles: [
              {
                emitter: {
                  particle: this.particle,
                  emitRate: 10000, // 每秒发射粒子数
                  position: [0, 0],
                  shape: ParticleEmitterShape.RECTANGLE ,// 发射器形状
                  size: ['50%','50%']
                },
                color: {
                  range: [Color.Pink, Color.Pink], // 初始颜色范围
                },
                scale: {
                  range: [0.2, 1.5], // 初始大小范围
                },
                opacity: {
                  range: [0.2, 0.8], // 初始透明度范围
                }
              }
            ]
          } as Particles)
            .width(300)
            .height(300)
            .attributeModifier(this.myRippleFieldsModifier1)
          //.attributeModifier(this.myRippleFieldsModifier[this.RippleINDEX])
          // .attributeModifier(this.myRippleFieldsModifier[0])
        }
        .width("100%")
        .height(300)
        .align(Alignment.Center)


        Text('速度场')
          .fontSize(30)
          .fontWeight(FontWeight.Bold)
        Stack() {
          Text()
            .width(300)
            .height(300)
            .backgroundColor(Color.Black)
          Particle({
            particles: [
              {
                emitter: {
                  particle: {
                    type: ParticleType.POINT, // 粒子类型
                    config: {
                      radius: 2 // 圆点半径
                    },
                    count: 1000, // 粒子总数
                    lifetime: 120000, // 粒子生命周期，单位ms
                    lifetimeRange: 0 // 粒子生命周期取值范围，单位ms
                  },
                  emitRate: 5000, // 每秒发射粒子数
                  position: [0, 0],
                  size: [300, 300],
                  shape: ParticleEmitterShape.RECTANGLE // 发射器形状
                },
                color: {
                  range:  [Color.Orange, Color.Orange], // 初始颜色范围
                },
                opacity: {
                  range: [1.0, 1.0],
                  updater: {
                    type: ParticleUpdater.CURVE, // 透明度按曲线变化
                    config: [
                      {
                        from: 1.0,
                        to: 0.0,
                        startMillis: 0,
                        endMillis: 120000,
                        curve: Curve.EaseIn
                      }
                    ]
                  }
                },
                velocity:{
                  speed:[5.0,20.0] ,
                  angle:[0.5,5.0]
                }
              }
            ]
          } as Particles)
            .attributeModifier(this.myVelocityFieldsModifier1)
            .width(300)
            .height(300)
            .margin({ top: 30 } as Padding)
        }.width("100%").height(300).align(Alignment.Center)

        Text('velocity+velocityFields')
          .fontSize(30)
          .fontWeight(FontWeight.Bold)
        Stack() {
          Text()
            .width(300)
            .height(300)
            .backgroundColor(Color.Black)
          Particle({
            particles: [
              {
                emitter: {
                  particle: {
                    type: ParticleType.POINT, // 粒子类型
                    config: {
                      radius: 2 // 圆点半径
                    },
                    count: 1000, // 粒子总数
                    lifetime: 120000, // 粒子生命周期，单位ms
                    lifetimeRange: 0 // 粒子生命周期取值范围，单位ms
                  },
                  emitRate: 5000, // 每秒发射粒子数
                  position: [0, 0],
                  size: [300, 300],
                  shape: ParticleEmitterShape.RECTANGLE // 发射器形状
                },
                color: {
                  range: [Color.Orange, Color.Orange], // 初始颜色范围
                },
                opacity: {
                  range: [1.0, 1.0],
                  updater: {
                    type: ParticleUpdater.CURVE, // 透明度按曲线变化
                    config: [
                      {
                        from: 1.0,
                        to: 0.0,
                        startMillis: 0,
                        endMillis: 120000,
                        curve: Curve.EaseIn
                      }
                    ]
                  }
                },
                velocity:{
                  speed:[5.0,20.0] ,
                  angle:[0.5,5.0]
                }
              }
            ]
          } as Particles)
            .width(300)
            .height(300)
            .margin({ top: 30 } as Padding)
            .attributeModifier(this.myVelocityFieldsModifier3)
        }.width("100%").height(300).align(Alignment.Center)


        Text('波动场+速度场')
          .fontSize(30)
          .fontWeight(FontWeight.Bold)
        Stack() {
          Text()
            .width(300).height(300).backgroundColor(Color.Black)
          Particle(
            {
              particles: [
                {
                  emitter: {
                    particle: this.particle,
                    emitRate: 5000, // 每秒发射粒子数
                    position: [0, 0],
                    shape: ParticleEmitterShape.RECTANGLE ,// 发射器形状
                    size: ['50%','50%']
                  },
                  color: {
                    range: [Color.Pink, Color.Pink], // 初始颜色范围
                  },
                  scale: {
                    range: [0.2, 1.5], // 初始大小范围
                  },
                  opacity: {
                    range: [0.2, 0.8], // 初始透明度范围
                  }
                } as ParticleOptions
              ]
            } as Particles).width(300).height(300)
            // .attributeModifier(this.myVelocityFieldsModifier2)
            .attributeModifier(this.myRippleFieldsModifier2)
        }
        .width("100%")
        .height(300)
        .align(Alignment.Center)

        Column(){
          Button('更改RippleFieldsModifier' )
            .onClick((e:ClickEvent) => {
              this.myRippleFieldsModifier1.isChange = !this.myRippleFieldsModifier1.isChange
            })
          Button('更改VelocityFieldsModifier')
            .onClick((e:ClickEvent) => {
              this.myVelocityFieldsModifier1.isChange1 = !this.myVelocityFieldsModifier1.isChange1
            })
        }
      }
    }

  }
}