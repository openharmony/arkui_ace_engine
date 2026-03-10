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

// 'use static'
// import {
//   Entry,
//   Text,
//   Column,
//   Component,
//   Button,
//   ClickEvent,
//   Stack,
//   FontWeight,
//   Color,
//   ClickEvent,
//   Row,
//   ButtonAttribute,
//   Scroll
// } from '@ohos.arkui.component'
// import { State } from '@ohos.arkui.stateManagement'
// import hilog from '@ohos.hilog'
// import {
//   EmitterParticleOptions,
//   Particles,
//   ParticleType,
//   Particle,
//   ParticleEmitterShape,
//   ParticleUpdater,
//   Curve,
//   Padding,
//   Alignment,
//   RippleFieldOptions,
//   DisturbanceFieldShape,
//   FieldRegion,
//   Vector2T,
//   SizeT,
//   ColumnOptions,
//   ParticleAttribute,
//   ParticleOptions,
//   PositionT
// } from  '@kit.ArkUI'
//
// interface CenterPoint {
//   x: double;
//   y: double;
// }
//
//
// // xxx.ets
// @Entry
// @Component
// struct ParticleExample {
//   @State amplitudeValuesIndex:  int = 0 as int;
//   @State amplitudeValues: (double | undefined)[] = [120.0, 5.0, 0.0, -100.0, undefined];
//   @State amplitudeValuesStr: (string)[] = ['120', '5', '0', '-100', 'undefined'];
//
//   @State wavelengthValuesIndex:  int = 0 as int;
//   @State wavelengthValues: (double | undefined)[] = [5000.0, 5.0, 0.0, -100.0, undefined];
//   @State wavelengthValuesStr: (string)[] = ['5000', '5', '0', '-100', 'undefined'];
//
//   @State waveSpeedValuesIndex:  int = 0 as int;
//   @State waveSpeedValues: (double | undefined)[] = [20.0, 500.0, 0.0, -100.0, undefined];
//   @State waveSpeedValuesStr: (string)[] = ['20', '500', '0', '-100', 'undefined'];
//
//   @State centerValuesIndex:  int = 0 as int;
//   @State centerValues: Array<PositionT<Double>> = [
//     { x: 150.0, y: 150.0 }as PositionT<Double>,
//     { x: 50.0, y: 50.0 }as PositionT<Double>,
//     { x: 250.0, y: 50.0 }as PositionT<Double>,
//     { x: 0.0, y: 0.0 }as PositionT<Double>,
//     { x: -250.0, y: -250.0 }as PositionT<Double>,
//   ];
//   @State centerValuesStr: (string)[] = ['(150,150)', '(50,50)','(250,50)', '(0,0)', '(-250,-250)'];
//
//   @State shapeValuesIndex: int = 0 as int;
//   @State shapeValues: Array<DisturbanceFieldShape| undefined> = [
//     DisturbanceFieldShape.RECT,
//     DisturbanceFieldShape.CIRCLE,
//     DisturbanceFieldShape.ELLIPSE,
//     undefined
//   ];
//   @State shapeValuesStr: string[] = ['矩形(RECT)', '圆形(CIRCLE)', '椭圆(ELLIPSE)','undefined'];
//
//   @State PositionIndex: int = 0 as int;
//   @State PositionValues: Array<PositionT<Double>|undefined> = [
//     { x: 150.0, y: 150.0 } as PositionT<Double>,
//     { x: 5.0, y: 50.0 } as PositionT<Double>,
//     // { x: 250.0, y: 150.0 } as PositionT<Double>,
//     undefined,
//     { x: 0.0, y: 150.0 } as PositionT<Double>,
//     { x: -150.0, y: -250.0 } as PositionT<Double>,
//   ];
//   @State PositionStr: string[] = ['(150,150)', '(5,50)', 'undefined', '(0,150)', '(-150,-250)'];
//
//   @State sizeValuesIndex: int = 0 as int; // 尺寸选项索引
//   @State sizeOptions: Array<SizeT<double>|undefined> = [
//     { width: 300, height: 100} as SizeT<double>,
//     { width: 50, height: 500} as SizeT<double>,
//     { width: -400, height: 200} as SizeT<double>,
//     { width: 0, height: 0} as SizeT<double>,
//     undefined
//   ];
//   @State sizeOptionsStr: string[] = ['(300,100)', '(50,500)', '(-400,200)', '(0,0)','undefined'];
//
//   @State velocityFieldValuesIndex: int = 0 as int; // 尺寸选项索引
//   @State velocityFieldValues: Array<Vector2T<double>> = [
//     { x: 20, y: 10 } as Vector2T<double>,
//     { x: 0, y: 0 } as Vector2T<double>,
//     { x: 10, y: -300 } as Vector2T<double>,
//   ];
//   @State velocityFieldValuesStr: string[] = ['(20,10)', '(0,0)', '(10,-300)'];
//
//   @State count: int = 1000 as int;
//   @State particle: EmitterParticleOptions = {
//     type: ParticleType.POINT, // 粒子类型
//     config: {
//       radius: 1 // 圆点半径
//     },
//     count: this.count, // 粒子总数
//     lifetime: 120000 , // 粒子生命周期，单位ms
//     lifetimeRange: 100 // 粒子生命周期取值范围，单位ms
//   } as EmitterParticleOptions
//
//   @State attenuationValuesIndex:  int = 0 as int;
//   @State attenuationValues: (double | undefined)[] = [0.05, 1.0, -100.0, undefined];
//   @State attenuationValuesStr: (string)[] = ['0.05', '1.0', '-100', 'undefined'];
//
//   build() {
//     Scroll(){
//       Column({ space: 5 } as ColumnOptions) {
//         Text('波动场')
//           .fontSize(30)
//           .fontWeight(FontWeight.Bold)
//         Stack() {
//           Text()
//             .width(300).height(300).backgroundColor(Color.Black)
//           Particle(
//             {
//               particles: [
//                 {
//                   emitter: {
//                     particle: this.particle,
//                     emitRate: 5000, // 每秒发射粒子数
//                     position: [0, 0],
//                     shape: ParticleEmitterShape.RECTANGLE ,// 发射器形状
//                     size: ['50%','50%']
//                   },
//                   color: {
//                     range: [Color.Pink, Color.Pink], // 初始颜色范围
//                   },
//                   scale: {
//                     range: [0.2, 1.5], // 初始大小范围
//                   },
//                   opacity: {
//                     range: [0.2, 0.8], // 初始透明度范围
//                   }
//                 } as ParticleOptions
//               ]
//             } as Particles).width(300).height(300)
//             .rippleFields([
//               {
//                 amplitude: this.amplitudeValues[this.amplitudeValuesIndex], //幅值
//                 wavelength: this.wavelengthValues[this.wavelengthValuesIndex],//波长
//                 waveSpeed: this.waveSpeedValues[this.waveSpeedValuesIndex],//波速
//                 center: this.centerValues[this.centerValuesIndex],//场作用点中心的位置
//                 attenuation: this.attenuationValues[this.attenuationValuesIndex], //衰减系数
//                 region: { //波动场影响区域的区域中心
//                   shape: this.shapeValues[this.shapeValuesIndex], //波动场影响区域的形状
//                   position: this.PositionValues[this.PositionIndex],//波动场影响的区域中心
//                   size: this.sizeOptions[this.sizeValuesIndex]//波动场影响区域的大小
//                 }
//               } as RippleFieldOptions
//             ])
//
//         }
//         .width("100%")
//         .height(300)
//         .align(Alignment.Center)
//
//
//
//
//         Text('速度场')
//           .fontSize(30)
//           .fontWeight(FontWeight.Bold)
//         Stack() {
//           Text()
//             .width(300)
//             .height(300)
//             .backgroundColor(Color.Black)
//           Particle({
//             particles: [
//               {
//                 emitter: {
//                   particle: {
//                     type: ParticleType.POINT, // 粒子类型
//                     config: {
//                       radius: 2 // 圆点半径
//                     },
//                     count: 1000, // 粒子总数
//                     lifetime: 120000, // 粒子生命周期，单位ms
//                     lifetimeRange: 0 // 粒子生命周期取值范围，单位ms
//                   },
//                   emitRate: 5000, // 每秒发射粒子数
//                   position: [0, 0],
//                   size: [300, 300],
//                   shape: ParticleEmitterShape.RECTANGLE // 发射器形状
//                 },
//                 color: {
//                   range: [Color.Orange, Color.Orange], // 初始颜色范围
//                 },
//                 opacity: {
//                   range: [1.0, 1.0],
//                   updater: {
//                     type: ParticleUpdater.CURVE, // 透明度按曲线变化
//                     config: [
//                       {
//                         from: 1.0,
//                         to: 0.0,
//                         startMillis: 0,
//                         endMillis: 120000,
//                         curve: Curve.EaseIn
//                       }
//                     ]
//                   }
//                 },
//                 velocity:{
//                   speed:[5.0,20.0] ,
//                   angle:[0.5,5.0]
//                 }
//               }
//             ]
//           } as Particles)
//             .width(300)
//             .height(300)
//             .margin({ top: 30 } as Padding)
//             .velocityFields([
//               {
//                 velocity: this.velocityFieldValues[this.velocityFieldValuesIndex] as Vector2T<double>, // 速度场的速度值
//                 region: {
//                   // 速度场的影响区域
//                   shape: this.shapeValues[this.shapeValuesIndex], // 速度场影响区域的形状
//                   position:this.PositionValues[this.PositionIndex], // 速度场影响区域的区域中心
//                   size:this.sizeOptions[this.sizeValuesIndex]// 速度场影响区域的大小
//                 } as FieldRegion
//               }
//             ])
//         }.width("100%").height(300).align(Alignment.Center)
//
//         Text('velocity+velocityFields')
//           .fontSize(30)
//           .fontWeight(FontWeight.Bold)
//         Stack() {
//           Text()
//             .width(300)
//             .height(300)
//             .backgroundColor(Color.Black)
//           Particle({
//             particles: [
//               {
//                 emitter: {
//                   particle: {
//                     type: ParticleType.POINT, // 粒子类型
//                     config: {
//                       radius: 2 // 圆点半径
//                     },
//                     count: 1000, // 粒子总数
//                     lifetime: 120000, // 粒子生命周期，单位ms
//                     lifetimeRange: 0 // 粒子生命周期取值范围，单位ms
//                   },
//                   emitRate: 5000, // 每秒发射粒子数
//                   position: [0, 0],
//                   size: [300, 300],
//                   shape: ParticleEmitterShape.RECTANGLE // 发射器形状
//                 },
//                 color: {
//                   range: [Color.Orange, Color.Orange], // 初始颜色范围
//                 },
//                 opacity: {
//                   range: [1.0, 1.0],
//                   updater: {
//                     type: ParticleUpdater.CURVE, // 透明度按曲线变化
//                     config: [
//                       {
//                         from: 1.0,
//                         to: 0.0,
//                         startMillis: 0,
//                         endMillis: 120000,
//                         curve: Curve.EaseIn
//                       }
//                     ]
//                   }
//                 },
//                 velocity:{
//                   speed:[5.0,20.0] ,
//                   angle:[0.5,5.0]
//                 }
//               }
//             ]
//           } as Particles)
//             .width(300)
//             .height(300)
//             .margin({ top: 30 } as Padding)
//             .velocityFields([
//               {
//                 velocity: this.velocityFieldValues[this.velocityFieldValuesIndex] as Vector2T<double>, // 速度场的速度值
//                 region: {
//                   // 速度场的影响区域
//                   shape: this.shapeValues[this.shapeValuesIndex], // 速度场影响区域的形状
//                   position:this.PositionValues[this.PositionIndex], // 速度场影响区域的区域中心
//                   size:this.sizeOptions[this.sizeValuesIndex]// 速度场影响区域的大小
//                 } as FieldRegion
//               }
//             ])
//         }.width("100%").height(300).align(Alignment.Center)
//
//
//
//         Text('波动场+速度场')
//           .fontSize(30)
//           .fontWeight(FontWeight.Bold)
//         Stack() {
//           Text()
//             .width(300).height(300).backgroundColor(Color.Black)
//           Particle(
//             {
//               particles: [
//                 {
//                   emitter: {
//                     particle: this.particle,
//                     emitRate: 5000, // 每秒发射粒子数
//                     position: [0, 0],
//                     shape: ParticleEmitterShape.RECTANGLE ,// 发射器形状
//                     size: ['50%','50%']
//                   },
//                   color: {
//                     range: [Color.Pink, Color.Pink], // 初始颜色范围
//                   },
//                   scale: {
//                     range: [0.2, 1.5], // 初始大小范围
//                   },
//                   opacity: {
//                     range: [0.2, 0.8], // 初始透明度范围
//                   }
//                 } as ParticleOptions
//               ]
//             } as Particles).width(300).height(300)
//             .rippleFields(
//               [{
//                 amplitude: 120, // 波动场幅值
//                 wavelength: 500, // 波动场的波长
//                 waveSpeed: 20, // 波动场的波速
//                 center: { x: 150, y: 150 }, // 波动场的力的中心
//                 attenuation: 0, // 波动场随时间的衰减系数
//                 region: {
//                   // 波动场的影响区域
//                   shape: DisturbanceFieldShape.RECT, // 波动场影响区域的形状
//                   position: { x: 150, y: 150 }, // 波动场影响区域的区域中心
//                   size: { width: 300, height: 300 } // 波动场影响区域的大小
//                 }
//               } as RippleFieldOptions
//               ])
//             .velocityFields([
//               {
//                 velocity: { x: 100, y: 0 } as Vector2T<double>, // 速度场的速度值
//                 region: {
//                   // 速度场的影响区域
//                   shape: DisturbanceFieldShape.RECT, // 速度场影响区域的形状
//                   position: { x: 150, y: 150 }, // 速度场影响区域的区域中心
//                   size: { width: 200, height: 200 } // 速度场影响区域的大小
//                 } as FieldRegion
//               }
//             ])
//         }
//         .width("100%")
//         .height(300)
//         .align(Alignment.Center)
//
//         Row(){
//           Button('更改amplitude：' + this.amplitudeValuesStr[this.amplitudeValuesIndex])
//             .onClick((e:ClickEvent) => {
//               this.amplitudeValuesIndex = (this.amplitudeValuesIndex + 1) % this.amplitudeValuesStr.length;
//             })
//           Button('更改wavelength：' + this.wavelengthValuesStr[this.wavelengthValuesIndex])
//             .onClick((e:ClickEvent) => {
//               this.wavelengthValuesIndex = (this.wavelengthValuesIndex + 1) % this.wavelengthValuesStr.length;
//             })
//         }
//         Row(){
//           Button('更改waveSpeed：' + this.waveSpeedValuesStr[this.waveSpeedValuesIndex])
//             .onClick((e:ClickEvent) => {
//               this.waveSpeedValuesIndex = (this.waveSpeedValuesIndex + 1) % this.waveSpeedValuesStr.length;
//             })
//           Button('更改center:' + this.centerValuesStr[this.centerValuesIndex])
//             .onClick((e:ClickEvent) => {
//               this.centerValuesIndex = (this.centerValuesIndex + 1) % this.centerValuesStr.length;
//             })
//         }
//
//         Row(){
//           Button('shape：' + this.shapeValuesStr[this.shapeValuesIndex])
//             .onClick((e:ClickEvent) => {
//               this.shapeValuesIndex = (this.shapeValuesIndex + 1) % this.shapeValuesStr.length;
//             })
//           Button('position：' + this.PositionStr[this.PositionIndex])
//             .onClick((e:ClickEvent) => {
//               this.PositionIndex = (this.PositionIndex + 1) % this.PositionStr.length;
//             })
//         }
//         Row(){
//           Button('size：' + this.sizeOptionsStr[this.sizeValuesIndex])
//             .onClick((e:ClickEvent) => {
//               this.sizeValuesIndex = (this.sizeValuesIndex + 1) % this.sizeOptionsStr.length;
//             })
//           Button('velocityFields：' + this.velocityFieldValuesStr[this.velocityFieldValuesIndex])
//             .onClick((e:ClickEvent) => {
//               this.velocityFieldValuesIndex = (this.velocityFieldValuesIndex + 1) % this.velocityFieldValuesStr.length;
//             })
//         }
//         Row(){
//           Button('attenuation：' + this.attenuationValuesStr[this.attenuationValuesIndex])
//             .onClick((e:ClickEvent) => {
//               this.attenuationValuesIndex = (this.attenuationValuesIndex + 1) % this.attenuationValuesStr.length;
//             })
//
//         }
//         Button('to modifier')
//           .onClick((): void => {
//             this.getUIContext().getRouter().pushUrl({
//               url: 'pages/modifier',
//             });
//           })
//       }
//     }
//
//   }
// }
//
