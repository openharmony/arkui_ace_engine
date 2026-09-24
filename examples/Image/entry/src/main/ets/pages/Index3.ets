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
import { matrix4 } from '@kit.ArkUI';

@Entry
@Component
struct ImgStudio {
  // ===== Source management =====
  @State src: Resource | PixelMap | string = $r('app.media.svg2_gradient_linear');
  @State idx: number = 0;
  @State srcArr: Array<string | Resource | PixelMap> = [
    $r('app.media.svg2_gradient_linear'),
    $r('app.media.svg2_gradient_radial'),
    $r('app.media.svg2_filter_complex'),
    $r('app.media.svg2_mask_pattern'),
    $r('app.media.svg2_coordinates'),
    $r('app.media.svg2_mixed'),
  ];

  // ===== Dimensional config =====
  @State w: number = 280;
  @State h: number = 200;
  @State ratio: number = 1.5;
  @State grow: number = 0;
  @State shrink: number = 1;
  @State selfAlign: ItemAlign = ItemAlign.Auto;

  // ===== Core image attributes =====
  @State fallback: Resource = $r('app.media.svg2_coordinates');
  @State fit: ImageFit = ImageFit.Cover;
  @State mtx: ImageMatrix = matrix4.identity();
  @State rpt: ImageRepeat = ImageRepeat.NoRepeat;
  @State interp: ImageInterpolation = ImageInterpolation.None;
  @State render: ImageRenderMode = ImageRenderMode.Original;
  @State autoSz: boolean = true;
  @State syncLd: boolean = false;
  @State copyOpt: CopyOptions = CopyOptions.None;
  @State fitOrigin: boolean = false;
  @State fillClr: ResourceColor = Color.Transparent;
  @State dragOn: boolean = true;

  // ===== Visual filter chain =====
  @State bright: number = 1;
  @State contra: number = 1;
  @State sat: number = 1;
  @State gray: number = 0;
  @State sepia: number = 0;
  @State invert: number = 0;
  @State hue: number = 0;
  @State blurPx: number = 0;

  // ===== Decorative styling =====
  @State corner: number = 0;
  @State strokeW: number = 0;
  @State strokeC: ResourceColor = Color.Black;
  @State shadowR: number = 0;
  @State shadowC: ResourceColor = Color.Grey;
  @State shadowX: number = 0;
  @State shadowY: number = 0;
  @State alpha: number = 1;
  @State zoom: number = 1;
  @State angle: number = 0;
  @State dx: number = 0;
  @State dy: number = 0;

  // ===== Runtime state =====
  @State loading: boolean = false;
  @State failed: boolean = false;
  @State pct: number = 0;
  @State log: string = 'Ready';
  @State tabPos: number = 0;
  @State animOn: boolean = false;
  @State overlayOn: boolean = false;
  @State overlayLabel: string = 'Live Preview';
  @State presetIdx: number = 0;
  @State gaugeVal: number = 100;

  // ===== Preset catalog =====
  private presetNames: Array<string> = ['Original', 'Vintage', 'Mono', 'Cool', 'Warm', 'Vivid', 'Dream', 'Neon'];
  private fitLabels: Array<string> = ['Cover', 'Contain', 'Fill', 'None', 'ScaleDown'];
  private rptLabels: Array<string> = ['NoRepeat', 'X', 'Y', 'XY'];
  private interpLabels: Array<string> = ['None', 'Low', 'Medium', 'High'];
  private colorSwatches: Array<string> = ['Black', 'Red', 'Blue', 'Green', 'Gray'];

  // ---------- logging helper ----------
  private trace(msg: string): void {
    console.info('[ImgStudio] ' + msg);
    this.log = msg;
  }

  // ---------- navigation ----------
  private gotoPrev(): void {
    this.idx = (this.idx - 1 + this.srcArr.length) % this.srcArr.length;
    this.src = this.srcArr[this.idx];
    this.clearChain();
    this.trace('Navigated to #' + (this.idx + 1));
  }

  private gotoNext(): void {
    this.idx = (this.idx + 1) % this.srcArr.length;
    this.src = this.srcArr[this.idx];
    this.clearChain();
    this.trace('Navigated to #' + (this.idx + 1));
  }

  private jumpTo(target: number): void {
    if (target < 0 || target >= this.srcArr.length) {
      return;
    }
    this.idx = target;
    this.src = this.srcArr[target];
    this.clearChain();
    this.trace('Jumped to slot ' + (target + 1));
  }

  // ---------- reset operations ----------
  private clearChain(): void {
    this.bright = 1;
    this.contra = 1;
    this.sat = 1;
    this.gray = 0;
    this.sepia = 0;
    this.invert = 0;
    this.hue = 0;
    this.blurPx = 0;
    this.presetIdx = 0;
  }

  private clearDecor(): void {
    this.corner = 0;
    this.strokeW = 0;
    this.strokeC = Color.Black;
    this.shadowR = 0;
    this.alpha = 1;
    this.zoom = 1;
    this.angle = 0;
    this.dx = 0;
    this.dy = 0;
    this.w = 280;
    this.h = 200;
  }

  private clearAll(): void {
    this.clearChain();
    this.clearDecor();
    this.fit = ImageFit.Cover;
    this.rpt = ImageRepeat.NoRepeat;
    this.interp = ImageInterpolation.None;
    this.overlayOn = false;
    this.animOn = false;
    this.trace('All parameters cleared');
  }

  // ---------- preset application ----------
  private applyPreset(slot: number): void {
    this.presetIdx = slot;
    const tag = this.presetNames[slot];
    switch (tag) {
      case 'Original':
        this.clearChain();
        break;
      case 'Vintage':
        this.bright = 1.1;
        this.contra = 0.85;
        this.sat = 0.7;
        this.sepia = 0.45;
        this.gray = 0;
        this.invert = 0;
        this.hue = 0;
        this.blurPx = 0;
        break;
      case 'Mono':
        this.bright = 1.0;
        this.contra = 1.15;
        this.sat = 0;
        this.gray = 1;
        this.sepia = 0;
        this.invert = 0;
        this.hue = 0;
        this.blurPx = 0;
        break;
      case 'Cool':
        this.bright = 0.95;
        this.contra = 1.1;
        this.sat = 1.2;
        this.hue = 210;
        this.sepia = 0;
        this.gray = 0;
        this.invert = 0;
        this.blurPx = 0;
        break;
      case 'Warm':
        this.bright = 1.08;
        this.contra = 1.0;
        this.sat = 1.35;
        this.hue = 25;
        this.sepia = 0.25;
        this.gray = 0;
        this.invert = 0;
        this.blurPx = 0;
        break;
      case 'Vivid':
        this.bright = 1.05;
        this.contra = 1.4;
        this.sat = 1.6;
        this.hue = 0;
        this.sepia = 0;
        this.gray = 0;
        this.invert = 0;
        this.blurPx = 0;
        break;
      case 'Dream':
        this.bright = 1.2;
        this.contra = 0.8;
        this.sat = 0.9;
        this.blurPx = 2;
        this.hue = 0;
        this.sepia = 0;
        this.gray = 0;
        this.invert = 0;
        break;
      case 'Neon':
        this.bright = 1.1;
        this.contra = 1.5;
        this.sat = 2.0;
        this.hue = 280;
        this.sepia = 0;
        this.gray = 0;
        this.invert = 0;
        this.blurPx = 0;
        break;
      default:
        break;
    }
    this.trace('Preset: ' + tag);
  }

  // ---------- async simulation ----------
  private fetchRemote(): void {
    this.loading = true;
    this.pct = 0;
    this.failed = false;
    const timer = setInterval(() => {
      this.pct += 12;
      if (this.pct >= 100) {
        clearInterval(timer);
        this.loading = false;
        this.trace('Remote fetch done');
      }
    }, 120);
  }

  private mockFail(): void {
    this.failed = true;
    this.trace('Simulated failure');
    setTimeout(() => {
      this.failed = false;
    }, 2500);
  }

  // ---------- cycling helpers ----------
  private cycleFit(): void {
    const arr: ImageFit[] = [ImageFit.Cover, ImageFit.Contain, ImageFit.Fill, ImageFit.None, ImageFit.ScaleDown];
    const pos = arr.indexOf(this.fit);
    this.fit = arr[(pos + 1) % arr.length];
    this.trace('Fit -> ' + this.fitTag());
  }

  private cycleRpt(): void {
    const arr: ImageRepeat[] = [ImageRepeat.NoRepeat, ImageRepeat.X, ImageRepeat.Y, ImageRepeat.XY];
    const pos = arr.indexOf(this.rpt);
    this.rpt = arr[(pos + 1) % arr.length];
    this.trace('Repeat -> ' + this.rptTag());
  }

  private cycleInterp(): void {
    const arr: ImageInterpolation[] = [
      ImageInterpolation.None,
      ImageInterpolation.Low,
      ImageInterpolation.Medium,
      ImageInterpolation.High
    ];
    const pos = arr.indexOf(this.interp);
    this.interp = arr[(pos + 1) % arr.length];
    this.trace('Interp -> ' + this.interpTag());
  }

  private fitTag(): string {
    return this.fitLabels[this.fit];
  }

  private rptTag(): string {
    return this.rptLabels[this.rpt];
  }

  private interpTag(): string {
    return this.interpLabels[this.interp];
  }

  private colorTag(c: ResourceColor): string {
    if (c === Color.Black) {
      return 'Black';
    }
    if (c === Color.Red) {
      return 'Red';
    }
    if (c === Color.Blue) {
      return 'Blue';
    }
    if (c === Color.Green) {
      return 'Green';
    }
    if (c === Color.Gray) {
      return 'Gray';
    }
    return 'Custom';
  }

  private resolveColor(name: string): ResourceColor {
    if (name === 'Black') {
      return Color.Black;
    }
    if (name === 'Red') {
      return Color.Red;
    }
    if (name === 'Blue') {
      return Color.Blue;
    }
    if (name === 'Green') {
      return Color.Green;
    }
    return Color.Gray;
  }

  // ---------- zoom helpers ----------
  private zoomIn(): void {
    this.zoom = Math.min(this.zoom + 0.25, 3.0);
    this.trace('Zoom ' + this.zoom.toFixed(2) + 'x');
  }

  private zoomOut(): void {
    this.zoom = Math.max(this.zoom - 0.25, 0.5);
    this.trace('Zoom ' + this.zoom.toFixed(2) + 'x');
  }

  private spinLeft(): void {
    this.angle = (this.angle - 90 + 360) % 360;
    this.trace('Rotated -90');
  }

  private spinRight(): void {
    this.angle = (this.angle + 90) % 360;
    this.trace('Rotated +90');
  }

  build() {
    Tabs({ index: this.tabPos }) {
      TabContent() {
        Scroll() {
          Column({ space: 12 }) {
            this.renderHeader()
            this.renderStage()
            this.renderNavStrip()
          }
        }
      }
      .tabBar(this.tabBuilder('Preview', 0))

      TabContent() {
        Scroll() {
          Column({ space: 12 }) {
            this.renderPresetBoard()
            this.renderFilterSliders()
          }
        }
      }
      .tabBar(this.tabBuilder('Effects', 1))

      TabContent() {
        Scroll() {
          Column({ space: 12 }) {
            this.renderTransformBoard()
            this.renderDecorBoard()
          }
        }
      }
      .tabBar(this.tabBuilder('Transform', 2))

      TabContent() {
        Scroll() {
          Column({ space: 12 }) {
            this.renderDetailPanel()
          }
        }
      }
      .tabBar(this.tabBuilder('Detail', 3))
    }
    .barPosition(BarPosition.Start)
    .onChange((pos: number) => {
      this.tabPos = pos;
      this.trace('Tab ' + pos);
    })
    .width('100%')
    .height('100%')
  }

  @Builder
  tabBuilder(label: string, pos: number) {
    Column({ space: 4 }) {
      Text(label)
        .fontSize(pos === this.tabPos ? 15 : 13)
        .fontColor(pos === this.tabPos ? '#e94560' : '#888888')
        .fontWeight(pos === this.tabPos ? FontWeight.Bold : FontWeight.Normal)
    }
    .justifyContent(FlexAlign.Center)
    .padding({ top: 8, bottom: 8 })
  }

  @Builder
  renderHeader() {
    Row({ space: 8 }) {
      Text('IMG STUDIO')
        .fontSize(22)
        .fontWeight(FontWeight.Black)
        .fontColor('#e94560')
      Text('v1.0')
        .fontSize(12)
        .fontColor('#888888')
        .margin({ bottom: 0 })
    }
    .width('100%')
    .justifyContent(FlexAlign.Center)
    .padding({ top: 16, bottom: 8 })
  }

  @Builder
  renderStage() {
    Column() {
      Stack({ alignContent: Alignment.Center }) {
        // Main render target
        Image(this.src)
          .alt(this.fallback)
          .objectFit(this.fit)
          .imageMatrix(this.mtx)
          .objectRepeat(this.rpt)
          .interpolation(this.interp)
          .renderMode(this.render)
          .autoResize(this.autoSz)
          .fitOriginalSize(this.fitOrigin)
          .fillColor(this.fillClr)
          .copyOption(this.copyOpt)
          .draggable(this.dragOn)
          .syncLoad(this.syncLd)
          .width(this.w)
          .height(this.h)
          .aspectRatio(this.ratio)
          .borderRadius(this.corner)
          .border({ width: this.strokeW, color: this.strokeC })
          .shadow({ radius: this.shadowR, color: this.shadowC, offsetX: this.shadowX, offsetY: this.shadowY })
          .opacity(this.alpha)
          .brightness(this.bright)
          .contrast(this.contra)
          .saturate(this.sat)
          .grayscale(this.gray)
          .invert(this.invert)
          .sepia(this.sepia)
          .hueRotate(this.hue)
          .blur(this.blurPx)
          .scale({ x: this.zoom, y: this.zoom })
          .rotate({ x: 0, y: 0, z: 1, angle: this.angle })
          .translate({ x: this.dx, y: this.dy })
          .flexGrow(this.grow)
          .flexShrink(this.shrink)
          .alignSelf(this.selfAlign)
          .onComplete(() => {
            this.gaugeVal = 100;
            this.trace('Load OK');
          })
          .onError(() => {
            this.failed = true;
            this.gaugeVal = 0;
            this.trace('Load FAIL');
          })

        // Overlay badge
        if (this.overlayOn) {
          this.renderMask()
        }

        // Loading gauge
        if (this.loading) {
          this.renderGauge()
        }

        // Error chip
        if (this.failed) {
          this.renderFailChip()
        }
      }
      .width('100%')
      .padding(12)
      .backgroundColor('#0f3460')
      .borderRadius(14)
    }
  }

  @Builder
  renderMask() {
    Column() {
      Text(this.overlayLabel)
        .fontSize(14)
        .fontColor('#ffffff')
        .padding(8)
        .backgroundColor('#99000000')
        .borderRadius(6)
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.End)
    .alignItems(HorizontalAlign.Center)
  }

  @Builder
  renderGauge() {
    Column({ space: 6 }) {
      Gauge({ value: this.pct, min: 0, max: 100 })
        .startAngle(210)
        .endAngle(150)
        .width(90)
        .height(90)
        .colors([['#e94560', 1.0]])
      Text(this.pct + '%')
        .fontSize(13)
        .fontColor('#ffffff')
    }
    .padding(16)
    .backgroundColor('#33000000')
    .borderRadius(12)
  }

  @Builder
  renderFailChip() {
    Row({ space: 6 }) {
      Text('!')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .fontColor('#ffffff')
      Text('Load Error')
        .fontSize(14)
        .fontColor('#ffffff')
    }
    .padding(10)
    .backgroundColor('#e94560')
    .borderRadius(8)
  }

  @Builder
  renderNavStrip() {
    Row({ space: 16 }) {
      Button('Prev')
        .onClick(() => this.gotoPrev())
        .width(90)
        .height(38)
        .backgroundColor('#16213e')
        .fontColor('#ffffff')

      Text((this.idx + 1) + '/' + this.srcArr.length)
        .fontSize(15)
        .fontColor('#16213e')
        .fontWeight(FontWeight.Bold)

      Button('Next')
        .onClick(() => this.gotoNext())
        .width(90)
        .height(38)
        .backgroundColor('#16213e')
        .fontColor('#ffffff')
    }
    .width('100%')
    .justifyContent(FlexAlign.Center)
    .margin({ top: 8, bottom: 8 })

    // Quick action toolbar
    Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap, justifyContent: FlexAlign.Center }) {
      Button('Clear')
        .onClick(() => this.clearAll())
        .backgroundColor('#2d6a4f')
        .fontColor('#ffffff')
        .fontSize(12)
        .height(34)

      Button('Fetch')
        .onClick(() => this.fetchRemote())
        .backgroundColor('#1d3557')
        .fontColor('#ffffff')
        .fontSize(12)
        .height(34)

      Button('Fail')
        .onClick(() => this.mockFail())
        .backgroundColor('#c1121f')
        .fontColor('#ffffff')
        .fontSize(12)
        .height(34)

      Button('Fit')
        .onClick(() => this.cycleFit())
        .backgroundColor('#7b2cbf')
        .fontColor('#ffffff')
        .fontSize(12)
        .height(34)

      Button('Rpt')
        .onClick(() => this.cycleRpt())
        .backgroundColor('#3a86ff')
        .fontColor('#ffffff')
        .fontSize(12)
        .height(34)

      Button('Intr')
        .onClick(() => this.cycleInterp())
        .backgroundColor('#fb5607')
        .fontColor('#ffffff')
        .fontSize(12)
        .height(34)

      Button(this.overlayOn ? 'Mask Off' : 'Mask On')
        .onClick(() => {
          this.overlayOn = !this.overlayOn;
          this.trace(this.overlayOn ? 'Overlay shown' : 'Overlay hidden');
        })
        .backgroundColor('#8338ec')
        .fontColor('#ffffff')
        .fontSize(12)
        .height(34)

      Button(this.animOn ? 'Anim Off' : 'Anim On')
        .onClick(() => {
          this.animOn = !this.animOn;
          this.trace(this.animOn ? 'Animation on' : 'Animation off');
        })
        .backgroundColor('#06d6a0')
        .fontColor('#16213e')
        .fontSize(12)
        .height(34)
    }
    .width('100%')
    .padding({ top: 8 })

    // Zoom & rotate controls
    Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap, justifyContent: FlexAlign.Center }) {
      Button('+')
        .onClick(() => this.zoomIn())
        .backgroundColor('#0096c7')
        .fontColor('#ffffff')
        .fontSize(14)
        .width(44)
        .height(34)

      Button('-')
        .onClick(() => this.zoomOut())
        .backgroundColor('#0096c7')
        .fontColor('#ffffff')
        .fontSize(14)
        .width(44)
        .height(34)

      Button('L90')
        .onClick(() => this.spinLeft())
        .backgroundColor('#ef476f')
        .fontColor('#ffffff')
        .fontSize(12)
        .width(50)
        .height(34)

      Button('R90')
        .onClick(() => this.spinRight())
        .backgroundColor('#ef476f')
        .fontColor('#ffffff')
        .fontSize(12)
        .width(50)
        .height(34)
    }
    .width('100%')
    .padding({ top: 6 })
  }

  @Builder
  renderPresetBoard() {
    Column({ space: 10 }) {
      Row({ space: 8 }) {
        Text('PRESETS')
          .fontSize(16)
          .fontWeight(FontWeight.Bold)
          .fontColor('#16213e')
        Badge({ count: this.presetIdx + 1, maxCount: 99, style: { color: '#ffffff', fontSize: 12, badgeColor: '#e94560', badgeTextColor: '#ffffff' } })
      }
      .width('100%')

      // Radio group for presets
      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap, justifyContent: FlexAlign.Start }) {
        ForEach(this.presetNames, (name: string, i: number) => {
          Row({ space: 4 }) {
            Radio({ value: name, group: 'preset' })
              .checked(this.presetIdx === i)
              .onChange((checked: boolean) => {
                if (checked) {
                  this.applyPreset(i);
                }
              })
              .width(20)
              .height(20)
            Text(name)
              .fontSize(12)
              .fontColor(this.presetIdx === i ? '#e94560' : '#16213e')
          }
          .margin(4)
          .padding(4)
          .borderRadius(6)
          .backgroundColor(this.presetIdx === i ? '#fce4ec' : '#f0f0f0')
        })
      }
      .width('100%')

      // Stepper for preset selection
      Stepper({
        index: this.presetIdx
      }) {
        ForEach(this.presetNames, (name: string, i: number) => {
          StepperItem() {
            Column({ space: 6 }) {
              Text(name)
                .fontSize(20)
                .fontWeight(FontWeight.Bold)
                .fontColor('#16213e')
              Text('Slot ' + (i + 1) + ' of ' + this.presetNames.length)
                .fontSize(12)
                .fontColor('#888888')
            }
            .width('100%')
            .padding(20)
            .justifyContent(FlexAlign.Center)
          }
        }
        )
      }
      .onFinish(() => {
        this.trace('Stepper done');
      })
      .onSkip(() => {
        this.presetIdx = this.presetNames.length - 1;
      })
      .onChange((val: number) => {
        this.applyPreset(val);
      })
      .width('100%')
      .height(120)
    }
    .padding(12)
    .backgroundColor('#ffffff')
    .borderRadius(12)
    .width('100%')
  }

  @Builder
  renderFilterSliders() {
    Column({ space: 8 }) {
      Text('FILTER CHAIN')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .fontColor('#16213e')
        .width('100%')

      // DataPanel showing current filter values
      DataPanel({
        values: [
          this.bright * 50,
          this.contra * 50,
          this.sat * 50,
          (1 - this.gray) * 100,
          this.hue / 3.6
        ],
        max: 100,
        type: DataPanelType.Circle
      })
        .width(120)
        .height(120)
        .margin({ top: 4, bottom: 8 })

      // Brightness
      this.renderSliderRow('Bright', this.bright, 0, 2, 0.1, (v) => { this.bright = v; this.presetIdx = -1; })
      // Contrast
      this.renderSliderRow('Contra', this.contra, 0, 2, 0.1, (v) => { this.contra = v; this.presetIdx = -1; })
      // Saturation
      this.renderSliderRow('Sat', this.sat, 0, 2, 0.1, (v) => { this.sat = v; this.presetIdx = -1; })
      // Hue
      this.renderSliderRow('Hue', this.hue, 0, 360, 10, (v) => { this.hue = v; this.presetIdx = -1; })
      // Sepia
      this.renderSliderRow('Sepia', this.sepia, 0, 1, 0.1, (v) => { this.sepia = v; this.presetIdx = -1; })
      // Invert
      this.renderSliderRow('Inv', this.invert, 0, 1, 0.1, (v) => { this.invert = v; this.presetIdx = -1; })
      // Blur
      this.renderSliderRow('Blur', this.blurPx, 0, 20, 0.5, (v) => { this.blurPx = v; this.presetIdx = -1; })
    }
    .padding(12)
    .backgroundColor('#f8f9fa')
    .borderRadius(12)
    .width('100%')
  }

  @Builder
  renderSliderRow(label: string, val: number, min: number, max: number, step: number, cb: (v: number) => void) {
    Row({ space: 10 }) {
      Text(label)
        .fontSize(12)
        .fontColor('#16213e')
        .width(55)
      Slider({ value: val, min: min, max: max, step: step, style: SliderStyle.OutSet })
        .onChange((v: number) => {
          cb(v);
          this.trace(label + ': ' + v.toFixed(1));
        })
        .width('55%')
        .selectedColor('#e94560')
        .trackColor('#e0e0e0')
      Text(val.toFixed(1))
        .fontSize(12)
        .fontColor('#666666')
        .width(40)
    }
    .width('100%')
  }

  @Builder
  renderTransformBoard() {
    Column({ space: 10 }) {
      Text('TRANSFORM')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .fontColor('#16213e')
        .width('100%')

      // Dimension steppers
      Row({ space: 12 }) {
        Column({ space: 4 }) {
          Text('W')
            .fontSize(11)
            .fontColor('#666666')
          Counter() {
            Text(this.w.toString())
              .fontSize(14)
              .fontColor('#16213e')
          }
          .onInc(() => {
            this.w = Math.min(this.w + 10, 500);
            this.trace('W=' + this.w);
          })
          .onDec(() => {
            this.w = Math.max(this.w - 10, 50);
            this.trace('W=' + this.w);
          })
          .width(80)
        }
        .alignItems(HorizontalAlign.Center)

        Column({ space: 4 }) {
          Text('H')
            .fontSize(11)
            .fontColor('#666666')
          Counter() {
            Text(this.h.toString())
              .fontSize(14)
              .fontColor('#16213e')
          }
          .onInc(() => {
            this.h = Math.min(this.h + 10, 400);
            this.trace('H=' + this.h);
          })
          .onDec(() => {
            this.h = Math.max(this.h - 10, 50);
            this.trace('H=' + this.h);
          })
          .width(80)
        }
        .alignItems(HorizontalAlign.Center)

        Column({ space: 4 }) {
          Text('Ratio')
            .fontSize(11)
            .fontColor('#666666')
          Counter() {
            Text(this.ratio.toFixed(1))
              .fontSize(14)
              .fontColor('#16213e')
          }
          .onInc(() => {
            this.ratio = Math.min(this.ratio + 0.1, 3);
          })
          .onDec(() => {
            this.ratio = Math.max(this.ratio - 0.1, 0.5);
          })
          .width(80)
        }
        .alignItems(HorizontalAlign.Center)
      }
      .width('100%')
      .justifyContent(FlexAlign.Center)

      // Opacity
      this.renderSliderRow('Alpha', this.alpha, 0, 1, 0.05, (v) => { this.alpha = v; })
      // Scale
      this.renderSliderRow('Zoom', this.zoom, 0.1, 3, 0.1, (v) => { this.zoom = v; })
      // Rotate
      this.renderSliderRow('Angle', this.angle, 0, 360, 5, (v) => { this.angle = v; })
      // TranslateX
      this.renderSliderRow('dX', this.dx, -100, 100, 5, (v) => { this.dx = v; })
      // TranslateY
      this.renderSliderRow('dY', this.dy, -100, 100, 5, (v) => { this.dy = v; })
    }
    .padding(12)
    .backgroundColor('#ffffff')
    .borderRadius(12)
    .width('100%')
  }

  @Builder
  renderDecorBoard() {
    Column({ space: 10 }) {
      Text('DECOR')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .fontColor('#16213e')
        .width('100%')

      // Corner radius
      this.renderSliderRow('Corner', this.corner, 0, 100, 5, (v) => { this.corner = v; })
      // Border width
      this.renderSliderRow('Stroke', this.strokeW, 0, 20, 1, (v) => { this.strokeW = v; })
      // Shadow radius
      this.renderSliderRow('ShadR', this.shadowR, 0, 50, 2, (v) => { this.shadowR = v; })

      // Border color swatches
      Row({ space: 8 }) {
        Text('Color')
          .fontSize(12)
          .fontColor('#16213e')
          .width(55)
        ForEach(this.colorSwatches, (tag: string) => {
          Stack()
            .width(28)
            .height(28)
            .borderRadius(14)
            .backgroundColor(this.resolveColor(tag))
            .border({
              width: this.colorTag(this.strokeC) === tag ? 3 : 0,
              color: '#e94560'
            })
            .onClick(() => {
              this.strokeC = this.resolveColor(tag);
              this.trace('Stroke: ' + tag);
            })
        })
      }
      .width('100%')

      // Shadow color swatches
      Row({ space: 8 }) {
        Text('ShadC')
          .fontSize(12)
          .fontColor('#16213e')
          .width(55)
        ForEach(this.colorSwatches, (tag: string) => {
          Stack()
            .width(28)
            .height(28)
            .borderRadius(14)
            .backgroundColor(this.resolveColor(tag))
            .border({
              width: this.colorTag(this.shadowC) === tag ? 3 : 0,
              color: '#e94560'
            })
            .onClick(() => {
              this.shadowC = this.resolveColor(tag);
              this.trace('ShadC: ' + tag);
            })
        })
      }
      .width('100%')

      // Shadow offsets
      this.renderSliderRow('ShdX', this.shadowX, -30, 30, 2, (v) => { this.shadowX = v; })
      this.renderSliderRow('ShdY', this.shadowY, -30, 30, 2, (v) => { this.shadowY = v; })
    }
    .padding(12)
    .backgroundColor('#f0f4f8')
    .borderRadius(12)
    .width('100%')
  }

  @Builder
  renderDetailPanel() {
    Column({ space: 10 }) {
      Text('RUNTIME DETAIL')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .fontColor('#16213e')
        .width('100%')

      // Marquee for log
      Marquee({
        start: true,
        step: 3,
        loop: -1,
        fromStart: true,
        src: this.log
      })
        .width('100%')
        .height(30)
        .fontSize(13)
        .fontColor('#e94560')
        .backgroundColor('#16213e')
        .borderRadius(8)
        .padding({ left: 8, right: 8 })

      // Detail rows using a different pattern: grid of stat cards
      Grid() {
        GridItem() {
          this.renderStatCard('Slot', (this.idx + 1) + '/' + this.srcArr.length)
        }
        GridItem() {
          this.renderStatCard('Fit', this.fitTag())
        }
        GridItem() {
          this.renderStatCard('Repeat', this.rptTag())
        }
        GridItem() {
          this.renderStatCard('Interp', this.interpTag())
        }
        GridItem() {
          this.renderStatCard('Preset', this.presetIdx >= 0 ? this.presetNames[this.presetIdx] : 'Custom')
        }
        GridItem() {
          this.renderStatCard('Size', this.w + 'x' + this.h)
        }
        GridItem() {
          this.renderStatCard('Zoom', this.zoom.toFixed(2) + 'x')
        }
        GridItem() {
          this.renderStatCard('Angle', this.angle + 'deg')
        }
        GridItem() {
          this.renderStatCard('Alpha', this.alpha.toFixed(2))
        }
        GridItem() {
          this.renderStatCard('Bright', this.bright.toFixed(1))
        }
        GridItem() {
          this.renderStatCard('Contra', this.contra.toFixed(1))
        }
        GridItem() {
          this.renderStatCard('Sat', this.sat.toFixed(1))
        }
      }
      .columnsTemplate('1fr 1fr')
      .rowsGap(8)
      .columnsGap(8)
      .width('100%')
      .height(300)

      // Status indicator
      Row({ space: 12 }) {
        Column({ space: 2 }) {
          Circle()
            .width(12)
            .height(12)
            .fill(this.loading ? '#ffd60a' : this.failed ? '#e94560' : '#06d6a0')
          Text('STATUS')
            .fontSize(9)
            .fontColor('#888888')
        }
        .alignItems(HorizontalAlign.Center)

        Text(this.loading ? 'Fetching...' : this.failed ? 'Error' : 'OK')
          .fontSize(14)
          .fontColor(this.loading ? '#ffd60a' : this.failed ? '#e94560' : '#06d6a0')
          .fontWeight(FontWeight.Bold)
      }
      .width('100%')
      .justifyContent(FlexAlign.Center)
      .padding(8)
      .backgroundColor('#16213e')
      .borderRadius(8)

      // Thumbnail strip
      Text('THUMBNAILS')
        .fontSize(14)
        .fontWeight(FontWeight.Bold)
        .fontColor('#16213e')
        .width('100%')

      Scroll() {
        Row({ space: 8 }) {
          ForEach(this.srcArr, (item: Resource | string | PixelMap, i: number) => {
            Stack({ alignContent: Alignment.Bottom }) {
              Image(item)
                .objectFit(ImageFit.Cover)
                .width(70)
                .height(70)
                .borderRadius(10)
                .opacity(i === this.idx ? 1.0 : 0.5)

              if (i === this.idx) {
                Text('')
                  .width(70)
                  .height(70)
                  .border({ width: 3, color: '#e94560' })
                  .borderRadius(10)
              }
            }
            .onClick(() => this.jumpTo(i))
          })
        }
        .padding(4)
      }
      .scrollable(ScrollDirection.Horizontal)
      .scrollBar(BarState.Auto)
      .width('100%')
      .height(80)
    }
    .padding(12)
    .backgroundColor('#ffffff')
    .borderRadius(12)
    .width('100%')
  }

  @Builder
  renderStatCard(key: string, val: string) {
    Column({ space: 4 }) {
      Text(key)
        .fontSize(10)
        .fontColor('#888888')
      Text(val)
        .fontSize(13)
        .fontColor('#16213e')
        .fontWeight(FontWeight.Bold)
    }
    .width('100%')
    .padding(10)
    .backgroundColor('#f8f9fa')
    .borderRadius(8)
    .alignItems(HorizontalAlign.Center)
  }
}
