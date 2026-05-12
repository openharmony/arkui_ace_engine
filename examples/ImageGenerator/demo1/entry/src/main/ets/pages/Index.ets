/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
import { router } from '@kit.ArkUI';
import { common, Want, AbilityConstant } from '@kit.AbilityKit';
import { hilog } from '@kit.PerformanceAnalysisKit';
import { BusinessError } from '@kit.BasicServicesKit';

const DOMAIN = 0x0000;
const TAG = 'AbilityJumpDemo';

interface AbilityInfoItem {
  bundleName: string;
  abilityName: string;
  moduleName?: string;
  description: string;
}

interface RouterParams {
  source: string;
  transitionType: number;
  fadeInDuration: number;
  fadeOutDuration: number;
  slideDirection: number;
  timestamp: number;
}

@Entry
@Component
struct Index {
  @State message: string = 'Ability Jump Demo';
  @State currentAbilityInfo: string = '';
  @State jumpResult: string = '';
  @State abilityList: AbilityInfoItem[] = [];
  @State selectedAbilityIndex: number = -1;
  @State isLoading: boolean = false;
  @State jumpMode: number = 0;
  @State transitionType: number = 0;
  @State fadeInDuration: number = 300;
  @State fadeOutDuration: number = 300;
  @State slideDirection: number = 0;
  @State imageSize: number = 200;
  @State imageSource: string = 'https://example.com/test.jpg';

  private context: common.UIAbilityContext = getContext(this) as common.UIAbilityContext;

  aboutToAppear(): void {
    this.initAbilityList();
    this.getCurrentAbilityInfo();
  }

  initAbilityList(): void {
    this.abilityList = [
      {
        bundleName: 'com.example.imagegenerator.demo2',
        abilityName: 'EntryAbility',
        moduleName: 'entry',
        description: 'Demo2 - ExtensionAbility Test'
      },
      {
        bundleName: 'com.example.imagegenerator.demo3',
        abilityName: 'EntryAbility',
        moduleName: 'entry',
        description: 'Demo3 - Image Animation'
      },
      {
        bundleName: 'com.example.imagegenerator.demo4',
        abilityName: 'EntryAbility',
        moduleName: 'entry',
        description: 'Demo4 - Image List'
      },
      {
        bundleName: 'com.example.settings',
        abilityName: 'MainAbility',
        description: 'System Settings App'
      },
      {
        bundleName: 'com.example.photos',
        abilityName: 'EntryAbility',
        description: 'Photos Gallery App'
      }
    ];
  }

  getCurrentAbilityInfo(): void {
    try {
      const abilityInfo = this.context.abilityInfo;
      this.currentAbilityInfo = `Bundle: ${abilityInfo.bundleName}\nAbility: ${abilityInfo.name}\nModule: ${abilityInfo.moduleName}`;
      hilog.info(DOMAIN, TAG, 'Current ability: %{public}s', this.currentAbilityInfo);
    } catch (error) {
      hilog.error(DOMAIN, TAG, 'Failed to get ability info');
    }
  }

  buildJumpWant(ability: AbilityInfoItem): Want {
    const want: Want = {
      bundleName: ability.bundleName,
      abilityName: ability.abilityName,
      moduleName: ability.moduleName,
      parameters: {
        sourceAbility: this.context.abilityInfo.name,
        jumpTime: Date.now().toString(),
        transitionType: this.transitionType.toString(),
        fadeInDuration: this.fadeInDuration.toString(),
        fadeOutDuration: this.fadeOutDuration.toString()
      }
    };
    return want;
  }

  async jumpToAbility(ability: AbilityInfoItem): Promise<void> {
    this.isLoading = true;
    this.jumpResult = 'Starting jump...';

    const want = this.buildJumpWant(ability);

    try {
      if (this.jumpMode === 0) {
        await this.startAbilityWithResult(want);
      } else if (this.jumpMode === 1) {
        await this.startAbilityForResult(want);
      } else {
        await this.startAbilityByCall(want);
      }
      this.jumpResult = 'Jump successful';
    } catch (error) {
      const err = error as BusinessError;
      this.jumpResult = `Jump failed: ${err.message || 'Unknown error'}`;
      hilog.error(DOMAIN, TAG, 'Jump failed: %{public}s', JSON.stringify(err));
    } finally {
      this.isLoading = false;
    }
  }

  async startAbilityWithResult(want: Want): Promise<void> {
    return new Promise((resolve, reject) => {
      this.context.startAbility(want, (err: BusinessError) => {
        if (err.code) {
          reject(err);
        } else {
          resolve();
        }
      });
    });
  }

  async startAbilityForResult(want: Want): Promise<void> {
    try {
      const result = await this.context.startAbilityForResult(want);
      this.jumpResult = `Result code: ${result.resultCode}`;
    } catch (error) {
      const err = error as BusinessError;
      this.jumpResult = `Jump failed: ${err.message}`;
    }
  }

  async startAbilityByCall(want: Want): Promise<void> {
    try {
      const caller = await this.context.startAbilityByCall(want);
      this.jumpResult = 'Ability called successfully';
      hilog.info(DOMAIN, TAG, 'Ability call succeeded');
    } catch (error) {
      const err = error as BusinessError;
      this.jumpResult = `Call failed: ${err.message}`;
    }
  }

  buildRouterParams(): RouterParams {
    return {
      source: 'demo1_ability_jump',
      transitionType: this.transitionType,
      fadeInDuration: this.fadeInDuration,
      fadeOutDuration: this.fadeOutDuration,
      slideDirection: this.slideDirection,
      timestamp: Date.now()
    };
  }

  async pushToSecondPage(): Promise<void> {
    try {
      await router.pushUrl({
        url: 'pages/SecondPage',
        params: this.buildRouterParams()
      }, router.RouterMode.Standard);
      this.jumpResult = 'Router push successful';
    } catch (error) {
      const err = error as BusinessError;
      this.jumpResult = `Router push failed: ${err.message}`;
    }
  }

  async replaceToSecondPage(): Promise<void> {
    try {
      await router.replaceUrl({
        url: 'pages/SecondPage',
        params: this.buildRouterParams()
      }, router.RouterMode.Standard);
      this.jumpResult = 'Router replace successful';
    } catch (error) {
      const err = error as BusinessError;
      this.jumpResult = `Router replace failed: ${err.message}`;
    }
  }

  async backToPreviousPage(): Promise<void> {
    try {
      router.back();
      this.jumpResult = 'Router back successful';
    } catch (error) {
      const err = error as BusinessError;
      this.jumpResult = `Router back failed: ${err.message}`;
    }
  }

  async clearRouterStack(): Promise<void> {
    try {
      router.clear();
      this.jumpResult = 'Router stack cleared';
    } catch (error) {
      const err = error as BusinessError;
      this.jumpResult = `Clear failed: ${err.message}`;
    }
  }

  getRouterLength(): string {
    return router.getLength();
  }

  getRouterState(): router.RouterState {
    return router.getState();
  }

  @Builder
  headerBuilder() {
    Row() {
      Text(this.message)
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .fontColor('#333333')
    }
    .width('100%')
    .height(60)
    .backgroundColor('#F5F5F5')
    .justifyContent(FlexAlign.Center)
  }

  @Builder
  currentAbilityInfoBuilder() {
    Column() {
      Text('Current Ability Info')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 10 })
      
      Text(this.currentAbilityInfo)
        .fontSize(14)
        .fontColor('#666666')
        .textAlign(TextAlign.Start)
        .width('100%')
        .padding(10)
        .backgroundColor('#FFFFFF')
        .borderRadius(8)
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#E8E8E8')
    .borderRadius(12)
    .margin({ bottom: 15 })
  }

  @Builder
  abilityListBuilder() {
    Column() {
      Text('Target Abilities')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 10 })

      List() {
        ForEach(this.abilityList, (ability: AbilityInfoItem, index: number) => {
          ListItem() {
            Row() {
              Column() {
                Text(ability.description)
                  .fontSize(16)
                  .fontWeight(FontWeight.Medium)
                Text(`${ability.bundleName}/${ability.abilityName}`)
                  .fontSize(12)
                  .fontColor('#888888')
                  .margin({ top: 5 })
              }
              .alignItems(HorizontalAlign.Start)

              Blank()

              Button('Jump')
                .fontSize(14)
                .height(36)
                .backgroundColor('#007DFF')
                .onClick(() => {
                  this.selectedAbilityIndex = index;
                  this.jumpToAbility(ability);
                })
            }
            .width('100%')
            .padding(15)
            .backgroundColor(this.selectedAbilityIndex === index ? '#E3F2FD' : '#FFFFFF')
            .borderRadius(8)
            .margin({ bottom: 8 })
          }
        })
      }
      .width('100%')
      .height(200)
      .listDirection(Axis.Vertical)
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#E8E8E8')
    .borderRadius(12)
    .margin({ bottom: 15 })
  }

  @Builder
  jumpModeBuilder() {
    Column() {
      Text('Jump Mode')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 10 })

      Row() {
        Button('startAbility')
          .fontSize(14)
          .height(40)
          .backgroundColor(this.jumpMode === 0 ? '#007DFF' : '#CCCCCC')
          .onClick(() => this.jumpMode = 0)
          .margin({ right: 10 })

        Button('startAbilityForResult')
          .fontSize(14)
          .height(40)
          .backgroundColor(this.jumpMode === 1 ? '#007DFF' : '#CCCCCC')
          .onClick(() => this.jumpMode = 1)
          .margin({ right: 10 })

        Button('startAbilityByCall')
          .fontSize(14)
          .height(40)
          .backgroundColor(this.jumpMode === 2 ? '#007DFF' : '#CCCCCC')
          .onClick(() => this.jumpMode = 2)
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceAround)
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#E8E8E8')
    .borderRadius(12)
    .margin({ bottom: 15 })
  }

  @Builder
  transitionSettingsBuilder() {
    Column() {
      Text('Transition Settings')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 10 })

      Row() {
        Text('Fade In Duration:')
          .fontSize(14)
        Slider({ value: this.fadeInDuration, min: 100, max: 1000, step: 50 })
          .width(150)
          .onChange((value: number) => this.fadeInDuration = value)
        Text(`${this.fadeInDuration}ms`)
          .fontSize(12)
      }
      .width('100%')
      .margin({ bottom: 10 })

      Row() {
        Text('Fade Out Duration:')
          .fontSize(14)
        Slider({ value: this.fadeOutDuration, min: 100, max: 1000, step: 50 })
          .width(150)
          .onChange((value: number) => this.fadeOutDuration = value)
        Text(`${this.fadeOutDuration}ms`)
          .fontSize(12)
      }
      .width('100%')
      .margin({ bottom: 10 })

      Row() {
        Button('Fade')
          .fontSize(14)
          .height(36)
          .backgroundColor(this.transitionType === 0 ? '#007DFF' : '#CCCCCC')
          .onClick(() => this.transitionType = 0)

        Button('Slide')
          .fontSize(14)
          .height(36)
          .backgroundColor(this.transitionType === 1 ? '#007DFF' : '#CCCCCC')
          .onClick(() => this.transitionType = 1)

        Button('None')
          .fontSize(14)
          .height(36)
          .backgroundColor(this.transitionType === 2 ? '#007DFF' : '#CCCCCC')
          .onClick(() => this.transitionType = 2)
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceAround)
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#E8E8E8')
    .borderRadius(12)
    .margin({ bottom: 15 })
  }

  @Builder
  routerOperationsBuilder() {
    Column() {
      Text('Router Operations')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 10 })

      Row() {
        Button('Push')
          .fontSize(14)
          .height(40)
          .backgroundColor('#4CAF50')
          .onClick(() => this.pushToSecondPage())
          .margin({ right: 10 })

        Button('Replace')
          .fontSize(14)
          .height(40)
          .backgroundColor('#FF9800')
          .onClick(() => this.replaceToSecondPage())
          .margin({ right: 10 })

        Button('Back')
          .fontSize(14)
          .height(40)
          .backgroundColor('#F44336')
          .onClick(() => this.backToPreviousPage())
          .margin({ right: 10 })

        Button('Clear')
          .fontSize(14)
          .height(40)
          .backgroundColor('#9E9E9E')
          .onClick(() => this.clearRouterStack())
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceAround)

      Row() {
        Text(`Stack Length: ${this.getRouterLength()}`)
          .fontSize(14)
          .margin({ top: 10 })

        Text(`Current Index: ${this.getRouterState().index}`)
          .fontSize(14)
          .margin({ top: 10, left: 20 })
      }
      .width('100%')
      .justifyContent(FlexAlign.Center)
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#E8E8E8')
    .borderRadius(12)
    .margin({ bottom: 15 })
  }

  @Builder
  resultBuilder() {
    Column() {
      Text('Jump Result')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 10 })

      if (this.isLoading) {
        LoadingProgress()
          .width(50)
          .height(50)
          .color('#007DFF')
      } else {
        Text(this.jumpResult)
          .fontSize(14)
          .fontColor(this.jumpResult.includes('failed') ? '#F44336' : '#4CAF50')
          .textAlign(TextAlign.Center)
          .width('100%')
          .padding(15)
          .backgroundColor('#FFFFFF')
          .borderRadius(8)
      }
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#E8E8E8')
    .borderRadius(12)
    .margin({ bottom: 15 })
  }

  @Builder
  demoImageBuilder() {
    Column() {
      Text('Demo Image Display')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 10 })

      Row() {
        Text('Image Size:')
          .fontSize(14)
        Slider({ value: this.imageSize, min: 100, max: 400, step: 20 })
          .width(150)
          .onChange((value: number) => this.imageSize = value)
        Text(`${this.imageSize}px`)
          .fontSize(12)
      }
      .width('100%')
      .margin({ bottom: 10 })

      Image($r('app.media.startIcon'))
        .width(this.imageSize)
        .height(this.imageSize)
        .objectFit(ImageFit.Contain)
        .borderRadius(10)
        .interpolation(ImageInterpolation.High)
        .backgroundColor('#FFFFFF')
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#E8E8E8')
    .borderRadius(12)
    .margin({ bottom: 15 })
  }

  @Builder
  abilityLifecycleDemoBuilder() {
    Column() {
      Text('Ability Lifecycle Demo')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 10 })

      Row() {
        Button('onCreate')
          .fontSize(12)
          .height(35)
          .backgroundColor('#2196F3')
          .onClick(() => {
            hilog.info(DOMAIN, TAG, 'onCreate callback demo triggered');
            this.jumpResult = 'onCreate: Ability is being created';
          })
          .margin({ right: 5 })

        Button('onDestroy')
          .fontSize(12)
          .height(35)
          .backgroundColor('#F44336')
          .onClick(() => {
            hilog.info(DOMAIN, TAG, 'onDestroy callback demo triggered');
            this.jumpResult = 'onDestroy: Ability is being destroyed';
          })
          .margin({ right: 5 })

        Button('onForeground')
          .fontSize(12)
          .height(35)
          .backgroundColor('#4CAF50')
          .onClick(() => {
            hilog.info(DOMAIN, TAG, 'onForeground callback demo triggered');
            this.jumpResult = 'onForeground: Ability is in foreground';
          })
          .margin({ right: 5 })

        Button('onBackground')
          .fontSize(12)
          .height(35)
          .backgroundColor('#9E9E9E')
          .onClick(() => {
            hilog.info(DOMAIN, TAG, 'onBackground callback demo triggered');
            this.jumpResult = 'onBackground: Ability is in background';
          })
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceAround)
      .margin({ bottom: 10 })

      Text('Lifecycle callbacks are triggered automatically by system')
        .fontSize(12)
        .fontColor('#888888')
        .textAlign(TextAlign.Center)
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#E8E8E8')
    .borderRadius(12)
    .margin({ bottom: 15 })
  }

  @Builder
  animationTransitionBuilder() {
    Column() {
      Text('Animation Transition Demo')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 10 })

      Row() {
        Button('Fade In')
          .fontSize(12)
          .height(35)
          .backgroundColor('#3F51B5')
          .onClick(() => {
            this.fadeInAnimation();
          })
          .margin({ right: 5 })

        Button('Fade Out')
          .fontSize(12)
          .height(35)
          .backgroundColor('#3F51B5')
          .onClick(() => {
            this.fadeOutAnimation();
          })
          .margin({ right: 5 })

        Button('Slide Left')
          .fontSize(12)
          .height(35)
          .backgroundColor('#009688')
          .onClick(() => {
            this.slideLeftAnimation();
          })
          .margin({ right: 5 })

        Button('Slide Right')
          .fontSize(12)
          .height(35)
          .backgroundColor('#009688')
          .onClick(() => {
            this.slideRightAnimation();
          })
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceAround)
      .margin({ bottom: 10 })

      Text('Transition animations enhance user experience during ability jumps')
        .fontSize(12)
        .fontColor('#888888')
        .textAlign(TextAlign.Center)
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#E8E8E8')
    .borderRadius(12)
    .margin({ bottom: 15 })
  }

  fadeInAnimation(): void {
    hilog.info(DOMAIN, TAG, 'Fade in animation demo');
    animateTo({ duration: this.fadeInDuration, curve: Curve.EaseInOut }, () => {
      this.imageSize = 250;
    });
  }

  fadeOutAnimation(): void {
    hilog.info(DOMAIN, TAG, 'Fade out animation demo');
    animateTo({ duration: this.fadeOutDuration, curve: Curve.EaseInOut }, () => {
      this.imageSize = 100;
    });
  }

  slideLeftAnimation(): void {
    hilog.info(DOMAIN, TAG, 'Slide left animation demo');
    animateTo({ duration: 500, curve: Curve.EaseOut }, () => {
      this.slideDirection = -1;
    });
  }

  slideRightAnimation(): void {
    hilog.info(DOMAIN, TAG, 'Slide right animation demo');
    animateTo({ duration: 500, curve: Curve.EaseOut }, () => {
      this.slideDirection = 1;
    });
  }

  @Builder
  advancedJumpOptionsBuilder() {
    Column() {
      Text('Advanced Jump Options')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 10 })

      Row() {
        Button('Jump with Flags')
          .fontSize(12)
          .height(35)
          .backgroundColor('#FF5722')
          .onClick(() => {
            this.jumpWithFlags();
          })
          .margin({ right: 5 })

        Button('Jump with Params')
          .fontSize(12)
          .height(35)
          .backgroundColor('#FF5722')
          .onClick(() => {
            this.jumpWithParams();
          })
          .margin({ right: 5 })

        Button('Jump with Uri')
          .fontSize(12)
          .height(35)
          .backgroundColor('#FF5722')
          .onClick(() => {
            this.jumpWithUri();
          })
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceAround)
      .margin({ bottom: 10 })

      Text('Advanced options allow more control over ability navigation')
        .fontSize(12)
        .fontColor('#888888')
        .textAlign(TextAlign.Center)
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#E8E8E8')
    .borderRadius(12)
    .margin({ bottom: 15 })
  }

  jumpWithFlags(): void {
    const want: Want = {
      bundleName: 'com.example.imagegenerator.demo2',
      abilityName: 'EntryAbility',
      flags: 0x00000002
    };
    this.context.startAbility(want, (err: BusinessError) => {
      if (err.code) {
        this.jumpResult = `Jump with flags failed: ${err.message}`;
      } else {
        this.jumpResult = 'Jump with flags successful';
      }
    });
  }

  jumpWithParams(): void {
    const want: Want = {
      bundleName: 'com.example.imagegenerator.demo3',
      abilityName: 'EntryAbility',
      parameters: {} as Record<string, Object>
    };
    want.parameters!['customParam1'] = 'value1';
    want.parameters!['customParam2'] = 'value2';
    want.parameters!['timestamp'] = Date.now().toString();
    this.context.startAbility(want, (err: BusinessError) => {
      if (err.code) {
        this.jumpResult = `Jump with params failed: ${err.message}`;
      } else {
        this.jumpResult = 'Jump with params successful';
      }
    });
  }

  jumpWithUri(): void {
    const want: Want = {
      bundleName: 'com.example.imagegenerator.demo4',
      abilityName: 'EntryAbility',
      uri: 'image://example/test.jpg'
    };
    this.context.startAbility(want, (err: BusinessError) => {
      if (err.code) {
        this.jumpResult = `Jump with uri failed: ${err.message}`;
      } else {
        this.jumpResult = 'Jump with uri successful';
      }
    });
  }

  @Builder
  usageTipsBuilder() {
    Column() {
      Text('Usage Tips')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 10 })

      Text('1. Select target ability from the list above')
        .fontSize(14)
        .fontColor('#666666')
        .margin({ bottom: 5 })

      Text('2. Choose jump mode (startAbility, startAbilityForResult, startAbilityByCall)')
        .fontSize(14)
        .fontColor('#666666')
        .margin({ bottom: 5 })

      Text('3. Configure transition settings if needed')
        .fontSize(14)
        .fontColor('#666666')
        .margin({ bottom: 5 })

      Text('4. Click Jump button to navigate to target ability')
        .fontSize(14)
        .fontColor('#666666')
        .margin({ bottom: 5 })

      Text('5. Use Router operations for in-app navigation')
        .fontSize(14)
        .fontColor('#666666')
        .margin({ bottom: 5 })

      Text('6. Try animation transitions for better UX')
        .fontSize(14)
        .fontColor('#666666')
        .margin({ bottom: 5 })

      Text('7. Use advanced options for more control')
        .fontSize(14)
        .fontColor('#666666')
        .margin({ bottom: 5 })

      Text('Note: Ensure target apps are installed before jumping')
        .fontSize(14)
        .fontColor('#FF9800')
        .margin({ bottom: 5 })

      Text('Warning: Do not jump to non-existent abilities')
        .fontSize(14)
        .fontColor('#F44336')
        .margin({ bottom: 5 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFF3E0')
    .borderRadius(12)
    .margin({ bottom: 15 })
  }

  build() {
    Column() {
      this.headerBuilder()

      Scroll() {
        Column() {
          this.currentAbilityInfoBuilder()
          this.abilityListBuilder()
          this.jumpModeBuilder()
          this.transitionSettingsBuilder()
          this.routerOperationsBuilder()
          this.abilityLifecycleDemoBuilder()
          this.animationTransitionBuilder()
          this.advancedJumpOptionsBuilder()
          this.resultBuilder()
          this.demoImageBuilder()
          this.usageTipsBuilder()
        }
        .width('100%')
        .padding(15)
      }
      .width('100%')
      .layoutWeight(1)
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F0F0F0')
  }
}