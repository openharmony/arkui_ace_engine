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
import { router } from '@kit.ArkUI';
import { common, Want, AbilityConstant } from '@kit.AbilityKit';
import { hilog } from '@kit.PerformanceAnalysisKit';
import { BusinessError } from '@kit.BasicServicesKit';

const DOMAIN = 0x0000;
const TAG = 'ImageGeneratorDemo';

interface ExtensionAbilityInfoItem {
  bundleName: string;
  moduleName: string;
  name: string;
  type: string;
  label: string;
  description: string;
  exported: boolean;
}

interface ExtensionCheckResult {
  exists: boolean;
  abilityInfo?: ExtensionAbilityInfoItem;
  message: string;
}

interface AnimationConfig {
  duration: number;
  curve: Curve;
  delay: number;
  iterations: number;
  playMode: PlayMode;
}

@Entry
@Component
struct Index {
  @State message: string = 'Image Generator Demo';
  @State currentTabIndex: number = 0;

  aboutToAppear(): void {
    hilog.info(DOMAIN, TAG, 'ImageGeneratorDemo started');
  }

  @Builder
  tabBuilder0() {
    Column() {
      Text('Extension Jump')
        .fontSize(16)
        .fontWeight(this.currentTabIndex === 0 ? FontWeight.Bold : FontWeight.Normal)
        .fontColor(this.currentTabIndex === 0 ? '#2196F3' : '#888888')
    }
  }

  @Builder
  tabBuilder1() {
    Column() {
      Text('Image Animation')
        .fontSize(16)
        .fontWeight(this.currentTabIndex === 1 ? FontWeight.Bold : FontWeight.Normal)
        .fontColor(this.currentTabIndex === 1 ? '#2196F3' : '#888888')
    }
  }

  build() {
    Column() {
      Row() {
        Text(this.message)
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .fontColor('#333333')
      }
      .width('100%')
      .height(60)
      .backgroundColor('#E3F2FD')
      .justifyContent(FlexAlign.Center)

      Tabs({ index: this.currentTabIndex }) {
        TabContent() {
          ExtensionJumpComponent()
        }
        .tabBar(this.tabBuilder0())

        TabContent() {
          ImageAnimationComponent()
        }
        .tabBar(this.tabBuilder1())
      }
      .width('100%')
      .layoutWeight(1)
      .barPosition(BarPosition.Start)
      .onChange((index: number) => {
        this.currentTabIndex = index;
      })
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F0F0F0')
  }
}

@Component
struct ExtensionJumpComponent {
  @State detectedExtensions: ExtensionAbilityInfoItem[] = [];
  @State checkResult: string = '';
  @State selectedExtensionIndex: number = -1;
  @State isDetecting: boolean = false;
  @State jumpStatus: string = '';
  @State extensionTypeFilter: number = 0;
  @State bundleNameInput: string = 'com.example.imagegenerator';
  @State abilityNameInput: string = 'ImageGenerationService';
  @State autoCheckEnabled: boolean = true;
  @State imageSize: number = 180;
  @State lastCheckTime: string = '';
  @State extensionCount: number = 0;
  @State supportedTypes: string[] = ['all', 'service', 'backup', 'form', 'dataShare'];

  private context: common.UIAbilityContext = getContext(this) as common.UIAbilityContext;

  aboutToAppear(): void {
    this.initExtensionList();
    this.lastCheckTime = new Date().toLocaleTimeString();
  }

  initExtensionList(): void {
    this.detectedExtensions = [
      {
        bundleName: 'com.example.imagegenerator.demo1',
        moduleName: 'entry',
        name: 'EntryAbility',
        type: 'ability',
        label: 'Demo1 Ability',
        description: 'Ability Jump Demo',
        exported: true
      },
      {
        bundleName: 'com.example.imagegenerator.demo_combined',
        moduleName: 'entry',
        name: 'EntryAbility',
        type: 'ability',
        label: 'Demo Combined Ability',
        description: 'Image Generator Demo Combined',
        exported: true
      },
      {
        bundleName: 'com.example.backup.service',
        moduleName: 'entry',
        name: 'BackupExtensionAbility',
        type: 'backup',
        label: 'Backup Service',
        description: 'Backup Extension',
        exported: false
      },
      {
        bundleName: 'com.example.form.service',
        moduleName: 'entry',
        name: 'FormExtensionAbility',
        type: 'form',
        label: 'Form Service',
        description: 'Form Extension',
        exported: true
      }
    ];
    this.extensionCount = this.detectedExtensions.length;
    this.checkResult = `Initialized ${this.extensionCount} demo entries`;
    hilog.info(DOMAIN, TAG, 'Extension list initialized');
  }

  filterByType(): ExtensionAbilityInfoItem[] {
    if (this.extensionTypeFilter === 0) {
      return this.detectedExtensions;
    }
    const targetType = this.supportedTypes[this.extensionTypeFilter];
    return this.detectedExtensions.filter(item => item.type === targetType);
  }

  async checkExtensionAbilityExists(bundleName: string, abilityName: string): Promise<ExtensionCheckResult> {
    const result: ExtensionCheckResult = {
      exists: false,
      message: ''
    };

    const found = this.detectedExtensions.find(
      item => item.bundleName === bundleName && item.name === abilityName
    );

    if (found) {
      result.exists = true;
      result.message = 'ExtensionAbility found in list';
      result.abilityInfo = found;
    } else {
      result.message = 'ExtensionAbility not found';
    }

    return result;
  }

  async jumpToExtensionAbility(extension: ExtensionAbilityInfoItem): Promise<void> {
    this.jumpStatus = 'Checking if ExtensionAbility exists...';

    if (this.autoCheckEnabled) {
      const checkResult = await this.checkExtensionAbilityExists(extension.bundleName, extension.name);
      
      if (!checkResult.exists) {
        this.jumpStatus = `Jump cancelled: ${checkResult.message}`;
        return;
      }
      
      this.jumpStatus = 'ExtensionAbility confirmed, proceeding to jump...';
    }

    await this.executeJump(extension);
  }

  async jumpToCustomExtension(): Promise<void> {
    this.jumpStatus = 'Checking custom ExtensionAbility...';

    const checkResult = await this.checkExtensionAbilityExists(this.bundleNameInput, this.abilityNameInput);
    
    if (!checkResult.exists) {
      this.jumpStatus = `Custom extension not found: ${checkResult.message}`;
      return;
    }

    if (checkResult.abilityInfo) {
      await this.executeJump(checkResult.abilityInfo);
    }
  }

  async executeJump(extension: ExtensionAbilityInfoItem): Promise<void> {
    this.jumpStatus = 'Executing jump...';

    const want: Want = {
      bundleName: extension.bundleName,
      abilityName: extension.name,
      moduleName: extension.moduleName,
      parameters: {
        source: 'demo_combined_extension_jump',
        timestamp: Date.now().toString(),
        extensionType: extension.type
      }
    };

    try {
      await this.context.startAbility(want);
      this.jumpStatus = 'Jump successful';
      hilog.info(DOMAIN, TAG, 'Jump succeeded to %{public}s', extension.name);
    } catch (error) {
      const err = error as BusinessError;
      this.jumpStatus = `Jump failed: ${err.message}`;
      hilog.error(DOMAIN, TAG, 'Jump failed: %{public}s', JSON.stringify(err));
    }
  }

  @Builder
  detectionStatusBuilder() {
    Column() {
      Text('Extension Ability Status')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 10 })

      if (this.isDetecting) {
        LoadingProgress()
          .width(40)
          .height(40)
          .color('#2196F3')
      } else {
        Text(this.checkResult)
          .fontSize(16)
          .fontColor(this.checkResult.includes('failed') ? '#F44336' : '#4CAF50')
      }

      Row() {
        Text(`Total Extensions: ${this.extensionCount}`)
          .fontSize(14)
          .fontColor('#666666')

        Text(`Last Check: ${this.lastCheckTime}`)
          .fontSize(14)
          .fontColor('#666666')
          .margin({ left: 20 })
      }
      .width('100%')
      .justifyContent(FlexAlign.Center)
      .margin({ top: 10 })

      Button('Refresh List')
        .fontSize(14)
        .height(40)
        .backgroundColor('#2196F3')
        .onClick(() => this.initExtensionList())
        .margin({ top: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(12)
    .margin({ bottom: 15 })
  }

  @Builder
  typeFilterBuilder() {
    Column() {
      Text('Filter by Extension Type')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 10 })

      Row() {
        ForEach(this.supportedTypes, (type: string, index: number) => {
          Button(type)
            .fontSize(12)
            .height(35)
            .backgroundColor(this.extensionTypeFilter === index ? '#4CAF50' : '#CCCCCC')
            .onClick(() => this.extensionTypeFilter = index)
            .margin({ right: 5 })
        })
      }
      .width('100%')
      .justifyContent(FlexAlign.Start)
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(12)
    .margin({ bottom: 15 })
  }

  @Builder
  extensionListBuilder() {
    Column() {
      Text('Extension Ability List')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 10 })

      if (this.detectedExtensions.length === 0) {
        Text('No ExtensionAbilities detected')
          .fontSize(14)
          .fontColor('#888888')
          .textAlign(TextAlign.Center)
          .padding(20)
      } else {
        List() {
          ForEach(this.filterByType(), (extension: ExtensionAbilityInfoItem, index: number) => {
            ListItem() {
              Row() {
                Column() {
                  Text(extension.name)
                    .fontSize(16)
                    .fontWeight(FontWeight.Medium)
                  Text(`Type: ${extension.type}`)
                    .fontSize(12)
                    .fontColor('#888888')
                    .margin({ top: 3 })
                  Text(`Bundle: ${extension.bundleName}`)
                    .fontSize(12)
                    .fontColor('#888888')
                    .margin({ top: 3 })
                  Text(`Exported: ${extension.exported ? 'Yes' : 'No'}`)
                    .fontSize(12)
                    .fontColor(extension.exported ? '#4CAF50' : '#F44336')
                    .margin({ top: 3 })
                }
                .alignItems(HorizontalAlign.Start)

                Blank()

                Button('Jump')
                  .fontSize(14)
                  .height(36)
                  .backgroundColor(extension.exported ? '#4CAF50' : '#CCCCCC')
                  .enabled(extension.exported)
                  .onClick(() => {
                    this.selectedExtensionIndex = index;
                    this.jumpToExtensionAbility(extension);
                  })
              }
              .width('100%')
              .padding(15)
              .backgroundColor(this.selectedExtensionIndex === index ? '#E3F2FD' : '#F5F5F5')
              .borderRadius(8)
              .margin({ bottom: 8 })
            }
          })
        }
        .width('100%')
        .height(250)
        .listDirection(Axis.Vertical)
      }
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(12)
    .margin({ bottom: 15 })
  }

  @Builder
  customJumpBuilder() {
    Column() {
      Text('Custom ExtensionAbility Jump')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 10 })

      Column() {
        Text('Bundle Name:')
          .fontSize(14)
          .margin({ bottom: 5 })
        TextInput({ placeholder: 'Enter bundle name', text: this.bundleNameInput })
          .fontSize(14)
          .height(40)
          .backgroundColor('#F5F5F5')
          .borderRadius(8)
          .onChange((value: string) => this.bundleNameInput = value)
          .width('100%')
      }
      .width('100%')
      .margin({ bottom: 15 })

      Column() {
        Text('Ability Name:')
          .fontSize(14)
          .margin({ bottom: 5 })
        TextInput({ placeholder: 'Enter ability name', text: this.abilityNameInput })
          .fontSize(14)
          .height(40)
          .backgroundColor('#F5F5F5')
          .borderRadius(8)
          .onChange((value: string) => this.abilityNameInput = value)
          .width('100%')
      }
      .width('100%')
      .margin({ bottom: 15 })

      Row() {
        Toggle({ type: ToggleType.Checkbox, isOn: this.autoCheckEnabled })
          .onChange((isOn: boolean) => this.autoCheckEnabled = isOn)
          .margin({ right: 10 })
        Text('Auto-check before jump')
          .fontSize(14)
      }
      .width('100%')
      .margin({ bottom: 15 })

      Button('Jump to Custom Extension')
        .fontSize(14)
        .height(45)
        .backgroundColor('#FF9800')
        .onClick(() => this.jumpToCustomExtension())
        .width('100%')
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(12)
    .margin({ bottom: 15 })
  }

  @Builder
  jumpStatusBuilder() {
    Column() {
      Text('Jump Status')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 10 })

      if (this.jumpStatus.includes('Checking') || this.jumpStatus.includes('Executing')) {
        Row() {
          LoadingProgress()
            .width(30)
            .height(30)
            .color('#2196F3')
          Text(this.jumpStatus)
            .fontSize(14)
            .margin({ left: 10 })
        }
      } else {
        Text(this.jumpStatus)
          .fontSize(14)
          .fontColor(this.jumpStatus.includes('failed') || this.jumpStatus.includes('cancelled') ? '#F44336' : '#4CAF50')
          .textAlign(TextAlign.Center)
          .width('100%')
          .padding(15)
          .backgroundColor('#F5F5F5')
          .borderRadius(8)
      }
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
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
        Text('Size:')
          .fontSize(14)
        Slider({ value: this.imageSize, min: 100, max: 300, step: 10 })
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
        .backgroundColor('#F5F5F5')
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(12)
    .margin({ bottom: 15 })
  }

  @Builder
  extensionTypesInfoBuilder() {
    Column() {
      Text('ExtensionAbility Types Info')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 10 })

      Row() {
        Column() {
          Text('Service')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
            .fontColor('#2196F3')
          Text('Background services')
            .fontSize(12)
            .fontColor('#888888')
        }
        .width('25%')

        Column() {
          Text('Form')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
            .fontColor('#4CAF50')
          Text('Widget services')
            .fontSize(12)
            .fontColor('#888888')
        }
        .width('25%')

        Column() {
          Text('Backup')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
            .fontColor('#FF9800')
          Text('Data backup')
            .fontSize(12)
            .fontColor('#888888')
        }
        .width('25%')

        Column() {
          Text('DataShare')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
            .fontColor('#9C27B0')
          Text('Data sharing')
            .fontSize(12)
            .fontColor('#888888')
        }
        .width('25%')
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceAround)
      .margin({ top: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(12)
    .margin({ bottom: 15 })
  }

  @Builder
  usageGuideBuilder() {
    Column() {
      Text('ExtensionAbility Jump Guide')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 10 })

      Text('1. Extension list initialized on startup')
        .fontSize(14)
        .fontColor('#666666')
        .margin({ bottom: 5 })

      Text('2. Use filter to select specific Extension type')
        .fontSize(14)
        .fontColor('#666666')
        .margin({ bottom: 5 })

      Text('3. Click Jump to navigate to ExtensionAbility')
        .fontSize(14)
        .fontColor('#666666')
        .margin({ bottom: 5 })

      Text('4. Auto-check verifies ExtensionAbility before jump')
        .fontSize(14)
        .fontColor('#666666')
        .margin({ bottom: 5 })

      Text('Warning: Only exported ExtensionAbilities can be jumped')
        .fontSize(14)
        .fontColor('#FF9800')
        .margin({ bottom: 5 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFF3E0')
    .borderRadius(12)
    .margin({ bottom: 15 })
  }

  build() {
    Scroll() {
      Column() {
        this.detectionStatusBuilder()
        this.typeFilterBuilder()
        this.extensionTypesInfoBuilder()
        this.extensionListBuilder()
        this.customJumpBuilder()
        this.jumpStatusBuilder()
        this.demoImageBuilder()
        this.usageGuideBuilder()
      }
      .width('100%')
      .padding(15)
    }
    .width('100%')
    .height('100%')
  }
}

@Component
struct ImageAnimationComponent {
  @State imageScale: number = 1.0;
  @State imageRotation: number = 0;
  @State imageOpacity: number = 1.0;
  @State imageTranslateX: number = 0;
  @State imageTranslateY: number = 0;
  @State imageWidth: number = 200;
  @State imageHeight: number = 200;
  @State imageBorderRadius: number = 0;
  @State imageBlur: number = 0;
  @State imageShadowRadius: number = 0;
  @State animationDuration: number = 500;
  @State animationDelay: number = 0;
  @State animationIterations: number = 1;
  @State currentAnimation: string = 'None';
  @State isAnimating: boolean = false;
  @State animationHistory: string[] = [];
  @State selectedCurveIndex: number = 0;
  @State selectedPlayModeIndex: number = 0;
  @State loopAnimation: boolean = false;

  private curves: Curve[] = [Curve.Linear, Curve.Ease, Curve.EaseIn, Curve.EaseOut, Curve.EaseInOut, Curve.FastOutSlowIn, Curve.Sharp];
  private curveNames: string[] = ['Linear', 'Ease', 'EaseIn', 'EaseOut', 'EaseInOut', 'FastOutSlowIn', 'Sharp'];
  private playModes: PlayMode[] = [PlayMode.Normal, PlayMode.Reverse, PlayMode.Alternate, PlayMode.AlternateReverse];
  private playModeNames: string[] = ['Normal', 'Reverse', 'Alternate', 'AlternateReverse'];

  aboutToAppear(): void {
    this.animationHistory.push('Demo initialized');
  }

  getAnimationConfig(): AnimationConfig {
    return {
      duration: this.animationDuration,
      curve: this.curves[this.selectedCurveIndex],
      delay: this.animationDelay,
      iterations: this.loopAnimation ? -1 : this.animationIterations,
      playMode: this.playModes[this.selectedPlayModeIndex]
    };
  }

  playScaleAnimation(): void {
    this.currentAnimation = 'Scale Animation';
    this.isAnimating = true;
    this.animationHistory.push(`Started: Scale at ${new Date().toLocaleTimeString()}`);

    animateTo(this.getAnimationConfig(), () => {
      this.imageScale = 1.5;
    });

    setTimeout(() => {
      animateTo(this.getAnimationConfig(), () => {
        this.imageScale = 1.0;
        this.isAnimating = false;
      });
    }, this.animationDuration + 100);
  }

  playRotationAnimation(): void {
    this.currentAnimation = 'Rotation Animation';
    this.isAnimating = true;
    this.animationHistory.push(`Started: Rotation at ${new Date().toLocaleTimeString()}`);

    animateTo(this.getAnimationConfig(), () => {
      this.imageRotation = 360;
    });

    setTimeout(() => {
      animateTo(this.getAnimationConfig(), () => {
        this.imageRotation = 0;
        this.isAnimating = false;
      });
    }, this.animationDuration + 100);
  }

  playOpacityAnimation(): void {
    this.currentAnimation = 'Opacity Animation';
    this.isAnimating = true;
    this.animationHistory.push(`Started: Opacity at ${new Date().toLocaleTimeString()}`);

    animateTo(this.getAnimationConfig(), () => {
      this.imageOpacity = 0.2;
    });

    setTimeout(() => {
      animateTo(this.getAnimationConfig(), () => {
        this.imageOpacity = 1.0;
        this.isAnimating = false;
      });
    }, this.animationDuration + 100);
  }

  playTranslateAnimation(): void {
    this.currentAnimation = 'Translate Animation';
    this.isAnimating = true;
    this.animationHistory.push(`Started: Translate at ${new Date().toLocaleTimeString()}`);

    animateTo(this.getAnimationConfig(), () => {
      this.imageTranslateX = 50;
      this.imageTranslateY = 50;
    });

    setTimeout(() => {
      animateTo(this.getAnimationConfig(), () => {
        this.imageTranslateX = 0;
        this.imageTranslateY = 0;
        this.isAnimating = false;
      });
    }, this.animationDuration + 100);
  }

  playSizeAnimation(): void {
    this.currentAnimation = 'Size Animation';
    this.isAnimating = true;
    this.animationHistory.push(`Started: Size at ${new Date().toLocaleTimeString()}`);

    animateTo(this.getAnimationConfig(), () => {
      this.imageWidth = 300;
      this.imageHeight = 300;
    });

    setTimeout(() => {
      animateTo(this.getAnimationConfig(), () => {
        this.imageWidth = 200;
        this.imageHeight = 200;
        this.isAnimating = false;
      });
    }, this.animationDuration + 100);
  }

  playBorderRadiusAnimation(): void {
    this.currentAnimation = 'BorderRadius Animation';
    this.isAnimating = true;
    this.animationHistory.push(`Started: BorderRadius at ${new Date().toLocaleTimeString()}`);

    animateTo(this.getAnimationConfig(), () => {
      this.imageBorderRadius = 100;
    });

    setTimeout(() => {
      animateTo(this.getAnimationConfig(), () => {
        this.imageBorderRadius = 0;
        this.isAnimating = false;
      });
    }, this.animationDuration + 100);
  }

  playBlurAnimation(): void {
    this.currentAnimation = 'Blur Animation';
    this.isAnimating = true;
    this.animationHistory.push(`Started: Blur at ${new Date().toLocaleTimeString()}`);

    animateTo(this.getAnimationConfig(), () => {
      this.imageBlur = 20;
    });

    setTimeout(() => {
      animateTo(this.getAnimationConfig(), () => {
        this.imageBlur = 0;
        this.isAnimating = false;
      });
    }, this.animationDuration + 100);
  }

  playShadowAnimation(): void {
    this.currentAnimation = 'Shadow Animation';
    this.isAnimating = true;
    this.animationHistory.push(`Started: Shadow at ${new Date().toLocaleTimeString()}`);

    animateTo(this.getAnimationConfig(), () => {
      this.imageShadowRadius = 30;
    });

    setTimeout(() => {
      animateTo(this.getAnimationConfig(), () => {
        this.imageShadowRadius = 0;
        this.isAnimating = false;
      });
    }, this.animationDuration + 100);
  }

  playCombinedAnimation(): void {
    this.currentAnimation = 'Combined Animation';
    this.isAnimating = true;
    this.animationHistory.push(`Started: Combined at ${new Date().toLocaleTimeString()}`);

    animateTo(this.getAnimationConfig(), () => {
      this.imageScale = 1.3;
      this.imageRotation = 180;
      this.imageOpacity = 0.6;
      this.imageTranslateX = 30;
    });

    setTimeout(() => {
      animateTo(this.getAnimationConfig(), () => {
        this.imageScale = 1.0;
        this.imageRotation = 0;
        this.imageOpacity = 1.0;
        this.imageTranslateX = 0;
        this.isAnimating = false;
      });
    }, this.animationDuration + 100);
  }

  playSequenceAnimation(): void {
    this.currentAnimation = 'Sequence Animation';
    this.isAnimating = true;
    this.animationHistory.push(`Started: Sequence at ${new Date().toLocaleTimeString()}`);

    animateTo({ duration: 300, curve: Curve.EaseOut }, () => {
      this.imageScale = 1.5;
    });

    setTimeout(() => {
      animateTo({ duration: 300, curve: Curve.EaseInOut }, () => {
        this.imageRotation = 90;
      });
    }, 300);

    setTimeout(() => {
      animateTo({ duration: 300, curve: Curve.EaseIn }, () => {
        this.imageOpacity = 0.5;
      });
    }, 600);

    setTimeout(() => {
      animateTo({ duration: 300, curve: Curve.Linear }, () => {
        this.imageScale = 1.0;
        this.imageRotation = 0;
        this.imageOpacity = 1.0;
        this.isAnimating = false;
      });
    }, 900);
  }

  playBounceAnimation(): void {
    this.currentAnimation = 'Bounce Animation';
    this.isAnimating = true;
    this.animationHistory.push(`Started: Bounce at ${new Date().toLocaleTimeString()}`);

    animateTo({ duration: 200, curve: Curve.EaseInOut }, () => {
      this.imageTranslateY = -50;
    });

    setTimeout(() => {
      animateTo({ duration: 200, curve: Curve.EaseInOut }, () => {
        this.imageTranslateY = 0;
      });
    }, 200);

    setTimeout(() => {
      animateTo({ duration: 150, curve: Curve.EaseInOut }, () => {
        this.imageTranslateY = -25;
      });
    }, 400);

    setTimeout(() => {
      animateTo({ duration: 150, curve: Curve.EaseInOut }, () => {
        this.imageTranslateY = 0;
        this.isAnimating = false;
      });
    }, 550);
  }

  resetAllAnimations(): void {
    this.imageScale = 1.0;
    this.imageRotation = 0;
    this.imageOpacity = 1.0;
    this.imageTranslateX = 0;
    this.imageTranslateY = 0;
    this.imageWidth = 200;
    this.imageHeight = 200;
    this.imageBorderRadius = 0;
    this.imageBlur = 0;
    this.imageShadowRadius = 0;
    this.currentAnimation = 'Reset Complete';
    this.isAnimating = false;
    this.animationHistory.push(`Reset: All at ${new Date().toLocaleTimeString()}`);
  }

  @Builder
  animatedImageBuilder() {
    Column() {
      Text('Animated Image')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 10 })

      Text(`Current: ${this.currentAnimation}`)
        .fontSize(14)
        .fontColor(this.isAnimating ? '#4CAF50' : '#888888')
        .margin({ bottom: 10 })

      Stack() {
        Image($r('app.media.startIcon'))
          .width(this.imageWidth)
          .height(this.imageHeight)
          .scale({ x: this.imageScale, y: this.imageScale })
          .rotate({ angle: this.imageRotation })
          .opacity(this.imageOpacity)
          .translate({ x: this.imageTranslateX, y: this.imageTranslateY })
          .borderRadius(this.imageBorderRadius)
          .blur(this.imageBlur)
          .shadow({ radius: this.imageShadowRadius, color: '#888888', offsetX: 0, offsetY: 5 })
          .objectFit(ImageFit.Contain)
          .interpolation(ImageInterpolation.High)
          .backgroundColor('#FFFFFF')
      }
      .width(300)
      .height(300)
      .alignContent(Alignment.Center)
      .backgroundColor('#F5F5F5')
      .borderRadius(15)
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(12)
    .margin({ bottom: 15 })
  }

  @Builder
  basicAnimationsBuilder() {
    Column() {
      Text('Basic Animations')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 10 })

      Row() {
        Button('Scale')
          .fontSize(14)
          .height(40)
          .backgroundColor('#2196F3')
          .onClick(() => this.playScaleAnimation())
          .margin({ right: 5 })

        Button('Rotate')
          .fontSize(14)
          .height(40)
          .backgroundColor('#4CAF50')
          .onClick(() => this.playRotationAnimation())
          .margin({ right: 5 })

        Button('Opacity')
          .fontSize(14)
          .height(40)
          .backgroundColor('#FF9800')
          .onClick(() => this.playOpacityAnimation())
          .margin({ right: 5 })

        Button('Translate')
          .fontSize(14)
          .height(40)
          .backgroundColor('#9C27B0')
          .onClick(() => this.playTranslateAnimation())
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceAround)
      .margin({ bottom: 10 })

      Row() {
        Button('Size')
          .fontSize(14)
          .height(40)
          .backgroundColor('#F44336')
          .onClick(() => this.playSizeAnimation())
          .margin({ right: 5 })

        Button('BorderRadius')
          .fontSize(14)
          .height(40)
          .backgroundColor('#00BCD4')
          .onClick(() => this.playBorderRadiusAnimation())
          .margin({ right: 5 })

        Button('Blur')
          .fontSize(14)
          .height(40)
          .backgroundColor('#3F51B5')
          .onClick(() => this.playBlurAnimation())
          .margin({ right: 5 })

        Button('Shadow')
          .fontSize(14)
          .height(40)
          .backgroundColor('#795548')
          .onClick(() => this.playShadowAnimation())
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceAround)
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(12)
    .margin({ bottom: 15 })
  }

  @Builder
  advancedAnimationsBuilder() {
    Column() {
      Text('Advanced Animations')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 10 })

      Row() {
        Button('Combined')
          .fontSize(14)
          .height(40)
          .backgroundColor('#E91E63')
          .onClick(() => this.playCombinedAnimation())
          .margin({ right: 5 })

        Button('Sequence')
          .fontSize(14)
          .height(40)
          .backgroundColor('#673AB7')
          .onClick(() => this.playSequenceAnimation())
          .margin({ right: 5 })

        Button('Bounce')
          .fontSize(14)
          .height(40)
          .backgroundColor('#009688')
          .onClick(() => this.playBounceAnimation())
          .margin({ right: 5 })

        Button('Reset')
          .fontSize(14)
          .height(40)
          .backgroundColor('#9E9E9E')
          .onClick(() => this.resetAllAnimations())
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceAround)
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(12)
    .margin({ bottom: 15 })
  }

  @Builder
  animationSettingsBuilder() {
    Column() {
      Text('Animation Settings')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 10 })

      Row() {
        Text('Duration:')
          .fontSize(14)
        Slider({ value: this.animationDuration, min: 100, max: 2000, step: 50 })
          .width(150)
          .onChange((value: number) => this.animationDuration = value)
        Text(`${this.animationDuration}ms`)
          .fontSize(12)
      }
      .width('100%')
      .margin({ bottom: 10 })

      Row() {
        Text('Delay:')
          .fontSize(14)
        Slider({ value: this.animationDelay, min: 0, max: 500, step: 10 })
          .width(150)
          .onChange((value: number) => this.animationDelay = value)
        Text(`${this.animationDelay}ms`)
          .fontSize(12)
      }
      .width('100%')
      .margin({ bottom: 10 })

      Row() {
        Text('Iterations:')
          .fontSize(14)
        Slider({ value: this.animationIterations, min: 1, max: 10, step: 1 })
          .width(150)
          .onChange((value: number) => this.animationIterations = value)
        Text(`${this.animationIterations}`)
          .fontSize(12)
      }
      .width('100%')
      .margin({ bottom: 10 })

      Row() {
        Toggle({ type: ToggleType.Checkbox, isOn: this.loopAnimation })
          .onChange((isOn: boolean) => this.loopAnimation = isOn)
          .margin({ right: 10 })
        Text('Loop Animation')
          .fontSize(14)
      }
      .width('100%')
      .margin({ bottom: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(12)
    .margin({ bottom: 15 })
  }

  @Builder
  curveSelectionBuilder() {
    Column() {
      Text('Animation Curve')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 10 })

      Row() {
        ForEach(this.curveNames, (name: string, index: number) => {
          Button(name)
            .fontSize(12)
            .height(35)
            .backgroundColor(this.selectedCurveIndex === index ? '#2196F3' : '#CCCCCC')
            .onClick(() => this.selectedCurveIndex = index)
            .margin({ right: 3 })
        })
      }
      .width('100%')
      .justifyContent(FlexAlign.Start)
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(12)
    .margin({ bottom: 15 })
  }

  @Builder
  playModeSelectionBuilder() {
    Column() {
      Text('Play Mode')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 10 })

      Row() {
        ForEach(this.playModeNames, (name: string, index: number) => {
          Button(name)
            .fontSize(12)
            .height(35)
            .backgroundColor(this.selectedPlayModeIndex === index ? '#4CAF50' : '#CCCCCC')
            .onClick(() => this.selectedPlayModeIndex = index)
            .margin({ right: 3 })
        })
      }
      .width('100%')
      .justifyContent(FlexAlign.Start)
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(12)
    .margin({ bottom: 15 })
  }

  @Builder
  animationHistoryBuilder() {
    Column() {
      Text('Animation History')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 10 })

      List() {
        ForEach(this.animationHistory.slice(-10), (history: string, index: number) => {
          ListItem() {
            Text(history)
              .fontSize(14)
              .fontColor('#666666')
              .width('100%')
              .padding(10)
              .backgroundColor('#F5F5F5')
              .borderRadius(5)
              .margin({ bottom: 5 })
          }
        })
      }
      .width('100%')
      .height(150)
      .listDirection(Axis.Vertical)
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(12)
    .margin({ bottom: 15 })
  }

  @Builder
  usageTipsBuilder() {
    Column() {
      Text('Animation Tips')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 10 })

      Text('1. Select animation type from Basic or Advanced sections')
        .fontSize(14)
        .fontColor('#666666')
        .margin({ bottom: 5 })

      Text('2. Adjust animation settings before playing')
        .fontSize(14)
        .fontColor('#666666')
        .margin({ bottom: 5 })

      Text('3. Choose different curves for different effects')
        .fontSize(14)
        .fontColor('#666666')
        .margin({ bottom: 5 })

      Text('4. Combined animation applies multiple effects')
        .fontSize(14)
        .fontColor('#666666')
        .margin({ bottom: 5 })

      Text('Tip: Use Reset to restore initial state')
        .fontSize(14)
        .fontColor('#4CAF50')
        .margin({ bottom: 5 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFF3E0')
    .borderRadius(12)
    .margin({ bottom: 15 })
  }

  build() {
    Scroll() {
      Column() {
        this.animatedImageBuilder()
        this.basicAnimationsBuilder()
        this.advancedAnimationsBuilder()
        this.animationSettingsBuilder()
        this.curveSelectionBuilder()
        this.playModeSelectionBuilder()
        this.animationHistoryBuilder()
        this.usageTipsBuilder()
      }
      .width('100%')
      .padding(15)
    }
    .width('100%')
    .height('100%')
  }
}