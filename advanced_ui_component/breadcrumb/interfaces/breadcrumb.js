/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

const measure = requireNapi('measure');

export class Breadcrumb extends ViewPU {
  constructor(e, t, i, s = -1) {
    super(e, i, s);
    this.selfWidth = 0;
    this.__labelInfo = new SynchedPropertyObjectTwoWayPU(t.labelInfo, this, "labelInfo");
    this.__labels = new ObservedPropertyObjectPU([], this, "labels");
    this.onLabelClick = void 0;
    this.onLabelDragStart = void 0;
    this.onLabelDragEnter = void 0;
    this.onLabelDragLeave = void 0;
    this.onLabelDrop = void 0;
    this.onLabelDragCancel = void 0;
    this.__hasMenu = new ObservedPropertySimplePU(!1, this, "hasMenu");
    this.__menuInfo = new ObservedPropertyObjectPU([], this, "menuInfo");
    this.__hiddenLabels = new ObservedPropertyObjectPU([], this, "hiddenLabels");
    this.__bgColor = new ObservedPropertyObjectPU({
      id: -1,
      type: 10001,
      params: ["sys.color.ohos_id_color_background_transparent"],
      bundleName: "",
      moduleName: ""
    }, this, "bgColor");
    this.__showMenu = new ObservedPropertySimplePU(!1, this, "showMenu");
    this.__hoverIndex = new ObservedPropertySimplePU(-1, this, "hoverIndex");
    this.timerId = -1;
    this.scroller = new Scroller;
    this.labelWidths = [];
    this.originalLabelWidth = [];
    this.firstLevelLabelWidth = 0;
    this.secondLevelLabelWidth = 0;
    this.thirdLevelLabelWidth = 0;
    this.totalFourthLevelLength = 0;
    this.menuButtonWidth = 0;
    this.idealTotalLength = 0;
    this.minLabelWidth = [];
    this.minFourthLevelLabelLength = 0;
    this.minLabelLengthWithoutFourthLevel = 0;
    this.separatorIconWidth = 20;
    this.labelPadding = 16;
    this.iconWidth = 24;
    this.labelSpace = 4;
    this.labelHeight = 40;
    this.labelBorderWidth = 2;
    this.setInitiallyProvidedValue(t);
    this.declareWatch("labelInfo", this.onInfoChanged)
  }
  setInitiallyProvidedValue(e) {
    void 0 !== e.selfWidth && (this.selfWidth = e.selfWidth);
    void 0 !== e.labels && (this.labels = e.labels);
    void 0 !== e.onLabelClick && (this.onLabelClick = e.onLabelClick);
    void 0 !== e.onLabelDragStart && (this.onLabelDragStart = e.onLabelDragStart);
    void 0 !== e.onLabelDragEnter && (this.onLabelDragEnter = e.onLabelDragEnter);
    void 0 !== e.onLabelDragLeave && (this.onLabelDragLeave = e.onLabelDragLeave);
    void 0 !== e.onLabelDrop && (this.onLabelDrop = e.onLabelDrop);
    void 0 !== e.onLabelDragCancel && (this.onLabelDragCancel = e.onLabelDragCancel);
    void 0 !== e.hasMenu && (this.hasMenu = e.hasMenu);
    void 0 !== e.menuInfo && (this.menuInfo = e.menuInfo);
    void 0 !== e.hiddenLabels && (this.hiddenLabels = e.hiddenLabels);
    void 0 !== e.bgColor && (this.bgColor = e.bgColor);
    void 0 !== e.showMenu && (this.showMenu = e.showMenu);
    void 0 !== e.hoverIndex && (this.hoverIndex = e.hoverIndex);
    void 0 !== e.timerId && (this.timerId = e.timerId);
    void 0 !== e.scroller && (this.scroller = e.scroller);
    void 0 !== e.labelWidths && (this.labelWidths = e.labelWidths);
    void 0 !== e.originalLabelWidth && (this.originalLabelWidth = e.originalLabelWidth);
    void 0 !== e.firstLevelLabelWidth && (this.firstLevelLabelWidth = e.firstLevelLabelWidth);
    void 0 !== e.secondLevelLabelWidth && (this.secondLevelLabelWidth = e.secondLevelLabelWidth);
    void 0 !== e.thirdLevelLabelWidth && (this.thirdLevelLabelWidth = e.thirdLevelLabelWidth);
    void 0 !== e.totalFourthLevelLength && (this.totalFourthLevelLength = e.totalFourthLevelLength);
    void 0 !== e.menuButtonWidth && (this.menuButtonWidth = e.menuButtonWidth);
    void 0 !== e.idealTotalLength && (this.idealTotalLength = e.idealTotalLength);
    void 0 !== e.minLabelWidth && (this.minLabelWidth = e.minLabelWidth);
    void 0 !== e.minFourthLevelLabelLength && (this.minFourthLevelLabelLength = e.minFourthLevelLabelLength);
    void 0 !== e.minLabelLengthWithoutFourthLevel && (this.minLabelLengthWithoutFourthLevel = e.minLabelLengthWithoutFourthLevel);
    void 0 !== e.separatorIconWidth && (this.separatorIconWidth = e.separatorIconWidth);
    void 0 !== e.labelPadding && (this.labelPadding = e.labelPadding);
    void 0 !== e.iconWidth && (this.iconWidth = e.iconWidth);
    void 0 !== e.labelSpace && (this.labelSpace = e.labelSpace);
    void 0 !== e.labelHeight && (this.labelHeight = e.labelHeight);
    void 0 !== e.labelBorderWidth && (this.labelBorderWidth = e.labelBorderWidth)
  }
  updateStateVars(e) {}
  purgeVariableDependenciesOnElmtId(e) {
    this.__labelInfo.purgeDependencyOnElmtId(e);
    this.__labels.purgeDependencyOnElmtId(e);
    this.__hasMenu.purgeDependencyOnElmtId(e);
    this.__menuInfo.purgeDependencyOnElmtId(e);
    this.__hiddenLabels.purgeDependencyOnElmtId(e);
    this.__bgColor.purgeDependencyOnElmtId(e);
    this.__showMenu.purgeDependencyOnElmtId(e);
    this.__hoverIndex.purgeDependencyOnElmtId(e)
  }
  aboutToBeDeleted() {
    this.__labelInfo.aboutToBeDeleted();
    this.__labels.aboutToBeDeleted();
    this.__hasMenu.aboutToBeDeleted();
    this.__menuInfo.aboutToBeDeleted();
    this.__hiddenLabels.aboutToBeDeleted();
    this.__bgColor.aboutToBeDeleted();
    this.__showMenu.aboutToBeDeleted();
    this.__hoverIndex.aboutToBeDeleted();
    SubscriberManager.Get()
      .delete(this.id__());
    this.aboutToBeDeletedInternal()
  }
  get labelInfo() {
    return this.__labelInfo.get()
  }
  set labelInfo(e) {
    this.__labelInfo.set(e)
  }
  get labels() {
    return this.__labels.get()
  }
  set labels(e) {
    this.__labels.set(e)
  }
  get hasMenu() {
    return this.__hasMenu.get()
  }
  set hasMenu(e) {
    this.__hasMenu.set(e)
  }
  get menuInfo() {
    return this.__menuInfo.get()
  }
  set menuInfo(e) {
    this.__menuInfo.set(e)
  }
  get hiddenLabels() {
    return this.__hiddenLabels.get()
  }
  set hiddenLabels(e) {
    this.__hiddenLabels.set(e)
  }
  get bgColor() {
    return this.__bgColor.get()
  }
  set bgColor(e) {
    this.__bgColor.set(e)
  }
  get showMenu() {
    return this.__showMenu.get()
  }
  set showMenu(e) {
    this.__showMenu.set(e)
  }
  get hoverIndex() {
    return this.__hoverIndex.get()
  }
  set hoverIndex(e) {
    this.__hoverIndex.set(e)
  }
  onInfoChanged() {
    if (this.labelInfo && JSON.stringify(this.labelInfo) !== JSON.stringify(this.labels)) {
      this.labels = [];
      this.labels = this.labelInfo.slice(0, this.labelInfo.length);
      this.checkLabelInfo();
      this.initData()
    }
  }
  onPlaceChildren(e, t, i) {
    let s = 0;
    let h = {
      x: -999999,
      y: -999999
    };
    t.forEach(((e, t) => {
      let i = e.measureResult.width;
      if (t % 2 != 0 || i !== 2 * this.labelBorderWidth) {
        e.layout({
          x: s,
          y: 0
        });
        s += i
      } else e.layout(h)
    }))
  }
  onMeasureSize(e, t, i) {
    let s = {
      width: e.width,
      height: e.height
    };
    if (!this.labels || this.labels.length <= 0) return s;
    this.selfWidth = e.width;
    this.clearMenu();
    1 === this.labels.length ? this.measureWithOneLabel() : 2 === this.labels.length ? this.measureWithTwoLabels() :
      3 === this.labels.length ? this.measureWithThreeLabels() : this.measureWithManyLabels();
    t.forEach(((e, t) => {
      let i = 0;
      let s = 0;
      if (0 === t) i = this.labelWidths[t];
      else if (2 === t) i = this.hasMenu ? this.menuButtonWidth : 0;
      else if (t % 2 == 0) i = this.labelWidths[t / 2 - 1];
      else {
        let e = 0;
        e = 3 === t ? this.hasMenu ? this.separatorIconWidth : 0 : 0 === this.labelWidths[(t - 3) / 2] ? 0 :
          this.separatorIconWidth;
        i = e
      }
      s = 0 === i ? 0 : this.labelHeight;
      e.measure({
        minWidth: i,
        maxWidth: i,
        minHeight: s,
        maxHeight: s
      })
    }));
    return s
  }
  measureWithManyLabels() {
    this.menuInfo = [];
    this.hiddenLabels = [];
    for (let e = 0; e < this.labels.length; e++) this.labelWidths[e] = this.originalLabelWidth[e];
    let e = this.selfWidth - (this.firstLevelLabelWidth + this.secondLevelLabelWidth + this.thirdLevelLabelWidth) - 2 *
      this.separatorIconWidth;
    this.minFourthLevelLabelLength <= e && e < this.totalFourthLevelLength ? this.compressFourthLevelLabelWithoutMenu(
        e) : this.minFourthLevelLabelLength > e && this.selfWidth > this.minLabelLengthWithoutFourthLevel + this.menuButtonWidth +
      this.separatorIconWidth ? e >= this.menuButtonWidth + this.separatorIconWidth ? this.compressFourthLevelLabelWithMenu(
        e) : this.measureWithThreeLabels() : this.selfWidth <= this.minLabelLengthWithoutFourthLevel + this.menuButtonWidth +
      this.separatorIconWidth ? this.compressToLessMinTotalWidth() : this.selfWidth >= this.idealTotalLength && this.resetToOriginalWidth()
  }
  measureWithOneLabel() {
    this.selfWidth >= this.firstLevelLabelWidth ? this.labelWidths[0] = this.firstLevelLabelWidth : this.selfWidth >=
      this.minLabelWidth[0] ? this.labelWidths[0] = this.selfWidth : this.labelWidths[0] = this.minLabelWidth[0]
  }
  measureWithTwoLabels() {
    this.labelWidths[1] = this.firstLevelLabelWidth;
    this.labelWidths[0] = this.secondLevelLabelWidth;
    let e = this.firstLevelLabelWidth + this.secondLevelLabelWidth + this.separatorIconWidth - this.selfWidth;
    let t = 0;
    if (e > 0) {
      t = this.secondLevelLabelWidth - e >= this.minLabelWidth[0] ? e : this.secondLevelLabelWidth - this.minLabelWidth[
        0];
      this.labelWidths[0] -= t;
      e -= t;
      if (e > 0) {
        t = this.firstLevelLabelWidth - e >= this.minLabelWidth[1] ? e : this.firstLevelLabelWidth - this.minLabelWidth[
          1];
        this.labelWidths[1] -= t;
        e -= t
      } else this.labelWidths[1] = this.firstLevelLabelWidth
    }
  }
  measureWithThreeLabels() {
    let e = 0;
    if (3 === this.labels.length) e = this.selfWidth;
    else {
      this.hasMenu || (this.hasMenu = !0);
      for (let e = 1; e < this.labels.length - 2; e++) {
        this.menuInfo.push(this.labels[e]);
        this.hiddenLabels.push(e);
        this.labelWidths[e] = 0
      }
      e = this.selfWidth - this.menuButtonWidth - this.separatorIconWidth
    }
    this.labelWidths[this.labels.length - 1] = this.firstLevelLabelWidth;
    this.labelWidths[this.labels.length - 2] = this.secondLevelLabelWidth;
    this.labelWidths[0] = this.thirdLevelLabelWidth;
    let t = this.thirdLevelLabelWidth + this.firstLevelLabelWidth + this.secondLevelLabelWidth + 2 * this.separatorIconWidth -
      e;
    let i = 0;
    if (t > 0) {
      i = this.thirdLevelLabelWidth - t >= this.minLabelWidth[0] ? t : this.thirdLevelLabelWidth - this.minLabelWidth[
        0];
      this.labelWidths[0] -= i;
      t -= i;
      if (t > 0) {
        i = this.secondLevelLabelWidth - t >= this.minLabelWidth[this.labels.length - 2] ? t : this.secondLevelLabelWidth -
          this.minLabelWidth[this.labels.length - 2];
        this.labelWidths[this.labels.length - 2] -= i;
        t -= i;
        if (t > 0) {
          i = this.firstLevelLabelWidth - t >= this.minLabelWidth[this.labels.length - 1] ? t : this.firstLevelLabelWidth -
            this.minLabelWidth[this.labels.length - 1];
          this.labelWidths[this.labels.length - 1] -= i;
          t -= i
        } else this.labelWidths[this.labels.length - 1] = this.firstLevelLabelWidth
      } else {
        this.labelWidths[this.labels.length - 1] = this.firstLevelLabelWidth;
        this.labelWidths[this.labels.length - 2] = this.secondLevelLabelWidth
      }
    } else {
      this.labelWidths[this.labels.length - 1] = this.firstLevelLabelWidth;
      this.labelWidths[this.labels.length - 2] = this.secondLevelLabelWidth;
      this.labelWidths[0] = this.thirdLevelLabelWidth
    }
  }
  clearMenu() {
    this.hasMenu && (this.hasMenu = !1);
    this.menuInfo = [];
    this.hiddenLabels = []
  }
  compressFourthLevelLabelWithoutMenu(e) {
    this.hasMenu && (this.hasMenu = !1);
    this.adjustFourthLevelLabelWidth(e, 1)
  }
  compressFourthLevelLabelWithMenu(e) {
    let t = 1;
    this.menuInfo.push(this.labels[t]);
    this.hiddenLabels.push(t);
    this.hasMenu || (this.hasMenu = !0);
    t++;
    let i = !1;
    let s = 0;
    let h = 0;
    for (; !i;) {
      for (let e = 1; e < t; e++) this.labelWidths[e] = 0;
      for (let e = t - 1; e < this.labels.length - 2; e++)
        if (e !== t - 1) {
          h += this.minLabelWidth[e] + this.separatorIconWidth;
          s += this.minLabelWidth[e] + this.separatorIconWidth
        } else h += this.minLabelWidth[e] + this.separatorIconWidth;
      if (t < this.labels.length - 2 && s > e - this.menuButtonWidth - this.separatorIconWidth) {
        this.menuInfo.push(this.labels[t]);
        this.labelWidths[t] = 0;
        this.hiddenLabels.push(t);
        t++;
        i = !1;
        h = 0;
        s = 0
      } else if (h < e - this.menuButtonWidth - this.separatorIconWidth && t > 2) {
        t--;
        i = !1;
        this.menuInfo.pop();
        this.hiddenLabels.pop();
        h = 0;
        s = 0
      } else i = !0
    }
    let l = 0;
    for (let e = t; e < this.labels.length - 2; e++) l += this.originalLabelWidth[e] + this.separatorIconWidth;
    if (e - this.menuButtonWidth - this.separatorIconWidth >= l)
      for (let e = t; e < this.labels.length - 2; e++) this.labelWidths[e] = this.originalLabelWidth[e];
    else this.adjustFourthLevelLabelWidth(e - this.menuButtonWidth - this.separatorIconWidth, t);
    this.labelWidths[0] = this.thirdLevelLabelWidth;
    this.labelWidths[this.labels.length - 2] = this.secondLevelLabelWidth;
    this.labelWidths[this.labels.length - 1] = this.firstLevelLabelWidth
  }
  compressToLessMinTotalWidth() {
    this.hasMenu = !0;
    this.labelWidths = [];
    for (let e = 0; e < this.labels.length; e++)
      if (0 === e || e === this.labels.length - 2 || e === this.labels.length - 1) this.labelWidths.push(this.minLabelWidth[
        e]);
      else {
        this.labelWidths.push(0);
        this.menuInfo.push(this.labels[e]);
        this.hiddenLabels.push(e)
      }
  }
  resetToOriginalWidth() {
    this.labelWidths = [];
    for (let e = 0; e < this.labels.length; e++) this.labelWidths.push(this.originalLabelWidth[e])
  }
  adjustFourthLevelLabelWidth(e, t) {
    let i = 0;
    for (let e = t; e < this.labels.length - 2; e++) {
      i += this.originalLabelWidth[e] + this.separatorIconWidth;
      this.labelWidths[e] = this.originalLabelWidth[e]
    }
    let s = [];
    let h = 0;
    let l = 0;
    for (;;) {
      for (let e = t; e < this.labels.length - 2; e++) h < this.labelWidths[e] && this.labelWidths[e] > this.minLabelWidth[
        e] && (h = this.labelWidths[e]);
      for (let e = t; e < this.labels.length - 2; e++) l < this.labelWidths[e] && this.labelWidths[e] < h && (l =
        this.labelWidths[e]);
      for (let e = t; e < this.labels.length - 2; e++) h === this.labelWidths[e] && this.labelWidths[e] > this.minLabelWidth[
        e] && s.push(e);
      if (0 === s.length) break;
      let o = h - (i - e) / s.length;
      if (o >= l)
        for (let e = 0; e < s.length; e++) o >= this.minLabelWidth[s[e]] ? this.labelWidths[s[e]] = o : this.labelWidths[
          s[e]] = this.minLabelWidth[s[e]];
      else {
        for (let e = 0; e < s.length; e++) this.labelWidths[s[e]] = l;
        h = l;
        l = 0;
        s = []
      }
      i = 0;
      for (let e = t; e < this.labelWidths.length - 2; e++) i += this.labelWidths[e] + this.separatorIconWidth;
      if (i - e <= 0) break
    }
  }
  initAllLabelWidth() {
    this.totalFourthLevelLength = 0;
    this.idealTotalLength = 0;
    this.labelWidths = [];
    this.originalLabelWidth = [];
    for (let e = 0; e < this.labels.length; e++) {
      let t = measure.measureText({
        textContent: this.labels[e].text
      });
      if (this.labels[e].icon) {
        this.labelWidths.push(px2vp(t) + this.labelPadding + this.iconWidth + this.labelSpace);
        this.originalLabelWidth.push(px2vp(t) + this.labelPadding + this.iconWidth + this.labelSpace);
        e === this.labels.length - 1 ? this.idealTotalLength += px2vp(t) + this.labelPadding + this.iconWidth + this.labelSpace :
          this.idealTotalLength += px2vp(t) + this.labelPadding + this.iconWidth + this.labelSpace + this.separatorIconWidth;
        e > 0 && e < this.labels.length - 2 && (this.totalFourthLevelLength += px2vp(t) + this.labelPadding + this.iconWidth +
          this.labelSpace + this.separatorIconWidth)
      } else {
        this.labelWidths.push(px2vp(t) + this.labelPadding);
        this.originalLabelWidth.push(px2vp(t) + this.labelPadding);
        e === this.labels.length - 1 ? this.idealTotalLength += px2vp(t) + this.labelPadding : this.idealTotalLength +=
          px2vp(t) + this.separatorIconWidth + this.labelPadding;
        e > 0 && e < this.labels.length - 2 && (this.totalFourthLevelLength += px2vp(t) + this.separatorIconWidth +
          this.labelPadding)
      }
    }
  }
  initAllMinWidth() {
    this.minFourthLevelLabelLength = 0;
    this.minLabelLengthWithoutFourthLevel = 0;
    this.minLabelWidth = [];
    let e = 0;
    for (let t = 0; t < this.labels.length; t++) {
      e = this.labels[t].icon ? this.menuButtonWidth : px2vp(measure.measureText({
        textContent: "我…"
      })) + this.labelPadding;
      this.minLabelWidth.push(e);
      t > 0 && t < this.labels.length - 2 ? this.minFourthLevelLabelLength += e + this.separatorIconWidth : this.minLabelLengthWithoutFourthLevel +=
        e + this.separatorIconWidth
    }
  }
  initNotFourthLevelWidth() {
    this.labels.length > 0 && (this.labels[this.labels.length - 1].icon ? this.firstLevelLabelWidth = px2vp(measure.measureText({
      textContent: this.labels[this.labels.length - 1].text
    })) + this.labelPadding + this.iconWidth + this.labelSpace : this.firstLevelLabelWidth = px2vp(measure.measureText({
      textContent: this.labels[this.labels.length - 1].text
    })) + this.labelPadding);
    this.labels.length > 1 && (this.labels[this.labels.length - 2].icon ? this.secondLevelLabelWidth = px2vp(measure.measureText({
      textContent: this.labels[this.labels.length - 2].text
    })) + this.labelPadding + this.iconWidth + this.labelSpace : this.secondLevelLabelWidth = px2vp(measure.measureText({
      textContent: this.labels[this.labels.length - 2].text
    })) + this.labelPadding);
    this.labels.length > 2 && (this.labels[0].icon ? this.thirdLevelLabelWidth = px2vp(measure.measureText({
      textContent: this.labels[0].text
    })) + this.labelPadding + this.iconWidth + this.labelSpace : this.thirdLevelLabelWidth = px2vp(measure.measureText({
      textContent: this.labels[0].text
    })) + this.labelPadding)
  }
  initData() {
    this.initAllLabelWidth();
    this.initAllMinWidth();
    this.initNotFourthLevelWidth()
  }
  checkLabelInfo() {
    for (let e = 0; e < this.labels.length; e++) {
      this.labels[e] || (this.labels[e] = {
        text: "undefined"
      });
      this.labels[e].text && "" !== this.labels[e].text || (this.labels[e].text = "undefined")
    }
  }
  aboutToAppear() {
    if (this.labelInfo) {
      this.labels = [];
      this.labels = this.labelInfo.slice(0, this.labelInfo.length);
      this.checkLabelInfo();
      this.menuButtonWidth = px2vp(measure.measureText({
        textContent: "···"
      })) + this.labelPadding;
      this.initData()
    }
  }
  menu(e = null) {
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Scroll.create(this.scroller);
      Scroll.onDragLeave(((e, t) => {
        this.showMenu = !1
      }));
      Scroll.onDrop((() => {}));
      Scroll.borderRadius({
        id: -1,
        type: 10002,
        params: ["sys.float.ohos_id_corner_radius_card"],
        bundleName: "",
        moduleName: ""
      });
      t || Scroll.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Menu.create();
      t || Menu.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      ForEach.create();
      this.forEachUpdateFunction(e, this.menuInfo, ((e, t) => {
        const i = e;
        this.observeComponentCreation(((e, s) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          MenuItem.create({
            startIcon: i.icon,
            content: i.text
          });
          MenuItem.key(0 === t ? "menu" : null);
          MenuItem.onClick((e => {
            if (this.onLabelClick) {
              this.onLabelClick(this.labels.indexOf(i), e);
              this.showMenu = !this.showMenu
            }
          }));
          MenuItem.onDragStart(((e, t) => {
            if (this.onLabelDragStart) return this.onLabelDragStart(this.labels.indexOf(i), e)
          }));
          MenuItem.onDragEnter(((e, t) => {
            this.onLabelDragEnter && this.onLabelDragEnter(this.labels.indexOf(i), e)
          }));
          MenuItem.onDragLeave(((e, t) => {
            this.onLabelDragLeave && this.onLabelDragLeave(this.labels.indexOf(i), e)
          }));
          MenuItem.onDrop(((e, t) => {
            this.showMenu && (this.showMenu = !1);
            this.onLabelDrop && this.onLabelDrop(this.labels.indexOf(i), e)
          }));
          s || MenuItem.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        MenuItem.pop()
      }), void 0, !0, !1);
      t || ForEach.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    ForEach.pop();
    Menu.pop();
    Scroll.pop()
  }
  breadcrumbBuilder(e = null) {
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      ForEach.create();
      this.forEachUpdateFunction(e, this.labels, ((e, t) => {
        const i = e;
        this.observeComponentCreation(((e, s) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          If.create();
          t < this.labels.length - 1 ? this.ifElseBranchUpdateFunction(0, (() => {
            this.observeComponentCreation(((e, i) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              Button.createWithChild();
              Button.borderWidth(this.labelBorderWidth);
              Button.clip(!0);
              Button.type(ButtonType.Normal);
              Button.backgroundColor(ObservedObject.GetRawObject(this.bgColor));
              Button.borderRadius({
                id: -1,
                type: 10002,
                params: ["sys.float.ohos_id_corner_radius_clicked"],
                bundleName: "",
                moduleName: ""
              });
              ViewStackProcessor.visualState("focused");
              Button.borderColor({
                id: -1,
                type: 10001,
                params: ["sys.color.ohos_id_color_focused_outline"],
                bundleName: "",
                moduleName: ""
              });
              ViewStackProcessor.visualState("normal");
              Button.borderColor(Color.Transparent);
              ViewStackProcessor.visualState();
              Button.onHover((e => {
                this.hoverIndex = e ? t : -1
              }));
              Button.onClick((e => {
                this.onLabelClick && (1 === t && this.hasMenu || this.onLabelClick(
                  t, e))
              }));
              Button.onDragStart(((e, i) => {
                if (this.onLabelDragStart) return this.onLabelDragStart(t, e)
              }));
              Button.onDragEnter(((e, i) => {
                this.showMenu && (this.showMenu = !1);
                this.onLabelDragEnter && this.onLabelDragEnter(t, e)
              }));
              Button.onDragLeave(((e, i) => {
                this.onLabelDragLeave && this.onLabelDragLeave(t, e)
              }));
              Button.onDrop(((e, i) => {
                this.onLabelDrop && (t === this.labels.length - 1 && this.onLabelDragCancel ?
                  this.onLabelDragCancel(e) : this.onLabelDrop(t, e))
              }));
              i || Button.pop();
              ViewStackProcessor.StopGetAccessRecording()
            }));
            this.observeComponentCreation(((e, t) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              Row.create({
                space: 4
              });
              Row.padding({
                left: 6,
                right: 6
              });
              Row.clip(!0);
              t || Row.pop();
              ViewStackProcessor.StopGetAccessRecording()
            }));
            this.observeComponentCreation(((e, t) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              If.create();
              i.icon ? this.ifElseBranchUpdateFunction(0, (() => {
                this.observeComponentCreation(((e, t) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(e);
                  Image.create(i.icon);
                  Image.width(24);
                  Image.height(24);
                  t || Image.pop();
                  ViewStackProcessor.StopGetAccessRecording()
                }))
              })) : this.ifElseBranchUpdateFunction(1, (() => {}));
              t || If.pop();
              ViewStackProcessor.StopGetAccessRecording()
            }));
            If.pop();
            this.observeComponentCreation(((e, s) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              Text.create(i.text);
              Text.fontSize({
                id: -1,
                type: 10002,
                params: ["sys.float.ohos_id_text_size_body1"],
                bundleName: "",
                moduleName: ""
              });
              Text.focusable(-1 === this.hiddenLabels.indexOf(t));
              Text.fontColor({
                id: -1,
                type: 10001,
                params: ["sys.color.ohos_id_color_text_secondary"],
                bundleName: "",
                moduleName: ""
              });
              Text.textOverflow({
                overflow: this.hoverIndex === t ? TextOverflow.MARQUEE : TextOverflow
                  .Ellipsis
              });
              Text.maxLines(1);
              Text.layoutWeight(1);
              s || Text.pop();
              ViewStackProcessor.StopGetAccessRecording()
            }));
            Text.pop();
            Row.pop();
            Button.pop();
            this.observeComponentCreation(((e, t) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              Stack.create();
              Stack.clip(!0);
              t || Stack.pop();
              ViewStackProcessor.StopGetAccessRecording()
            }));
            this.observeComponentCreation(((e, t) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              Image.create({
                id: -1,
                type: 2e4,
                params: ["sys.media.ohos_ic_public_arrow_right"],
                bundleName: "",
                moduleName: ""
              });
              Image.width(12);
              Image.height(24);
              Image.margin({
                top: 8,
                bottom: 8,
                left: 4,
                right: 4
              });
              Image.fillColor({
                id: -1,
                type: 10001,
                params: ["sys.color.ohos_id_color_tertiary"],
                bundleName: "",
                moduleName: ""
              });
              t || Image.pop();
              ViewStackProcessor.StopGetAccessRecording()
            }));
            Stack.pop();
            this.observeComponentCreation(((e, i) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              If.create();
              0 === t ? this.ifElseBranchUpdateFunction(0, (() => {
                this.observeComponentCreation(((e, t) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(e);
                  Button.createWithChild();
                  Button.clip(!0);
                  Button.type(ButtonType.Normal);
                  Button.borderWidth(this.labelBorderWidth);
                  Button.backgroundColor(ObservedObject.GetRawObject(this.bgColor));
                  Button.borderRadius({
                    id: -1,
                    type: 10002,
                    params: ["sys.float.ohos_id_corner_radius_clicked"],
                    bundleName: "",
                    moduleName: ""
                  });
                  ViewStackProcessor.visualState("focused");
                  Button.borderColor({
                    id: -1,
                    type: 10001,
                    params: ["sys.color.ohos_id_color_focused_outline"],
                    bundleName: "",
                    moduleName: ""
                  });
                  ViewStackProcessor.visualState("normal");
                  Button.borderColor(Color.Transparent);
                  ViewStackProcessor.visualState();
                  Button.backgroundColor(ObservedObject.GetRawObject(this.bgColor));
                  Button.borderRadius({
                    id: -1,
                    type: 10002,
                    params: ["sys.float.ohos_id_corner_radius_clicked"],
                    bundleName: "",
                    moduleName: ""
                  });
                  Button.onClick((() => {
                    this.showMenu = !this.showMenu
                  }));
                  Button.onDragEnter(((e, t) => {
                    this.showMenu || this.labels.indexOf(this.menuInfo[
                        0]) !== this.hiddenLabels[0] || this.menuInfo
                      .reverse();
                    this.timerId = setInterval((() => {
                      this.showMenu || (this.showMenu = !0);
                      clearInterval(this.timerId)
                    }), 1e3)
                  }));
                  Button.onDragLeave(((e, t) => {
                    clearInterval(this.timerId)
                  }));
                  Button.onDrop((() => {}));
                  Button.onKeyEvent((e => {
                    e.type === KeyType.Up && 2050 === e.keyCode &&
                      focusControl.requestFocus("menu")
                  }));
                  Button.bindPopup(this.showMenu, {
                    builder: {
                      builder: this.menu.bind(this)
                    },
                    enableArrow: !1,
                    popupColor: Color.Transparent,
                    onStateChange: e => {
                      if (!e.isVisible) {
                        this.labels.indexOf(this.menuInfo[0]) != this
                          .hiddenLabels[0] && this.menuInfo.reverse();
                        this.showMenu = !1
                      }
                    }
                  });
                  t || Button.pop();
                  ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((e, t) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(e);
                  Stack.create();
                  Stack.padding({
                    left: 6,
                    right: 6
                  });
                  t || Stack.pop();
                  ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((e, t) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(e);
                  Text.create("···");
                  Text.fontSize({
                    id: -1,
                    type: 10002,
                    params: ["sys.float.ohos_id_text_size_body1"],
                    bundleName: "",
                    moduleName: ""
                  });
                  Text.focusable(!!this.hasMenu);
                  Text.fontColor({
                    id: -1,
                    type: 10001,
                    params: ["sys.color.ohos_id_color_text_secondary"],
                    bundleName: "",
                    moduleName: ""
                  });
                  Text.maxLines(1);
                  t || Text.pop();
                  ViewStackProcessor.StopGetAccessRecording()
                }));
                Text.pop();
                Stack.pop();
                Button.pop();
                this.observeComponentCreation(((e, t) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(e);
                  Stack.create();
                  Stack.clip(!0);
                  t || Stack.pop();
                  ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((e, t) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(e);
                  Image.create({
                    id: -1,
                    type: 2e4,
                    params: ["sys.media.ohos_ic_public_arrow_right"],
                    bundleName: "",
                    moduleName: ""
                  });
                  Image.width(12);
                  Image.height(24);
                  Image.margin({
                    top: 8,
                    bottom: 8,
                    left: 4,
                    right: 4
                  });
                  Image.fillColor({
                    id: -1,
                    type: 10001,
                    params: ["sys.color.ohos_id_color_tertiary"],
                    bundleName: "",
                    moduleName: ""
                  });
                  t || Image.pop();
                  ViewStackProcessor.StopGetAccessRecording()
                }));
                Stack.pop()
              })) : this.ifElseBranchUpdateFunction(1, (() => {}));
              i || If.pop();
              ViewStackProcessor.StopGetAccessRecording()
            }));
            If.pop()
          })) : this.ifElseBranchUpdateFunction(1, (() => {
            this.observeComponentCreation(((e, i) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              Row.create({
                space: 4
              });
              Row.backgroundColor(ObservedObject.GetRawObject(this.bgColor));
              Row.borderRadius({
                id: -1,
                type: 10002,
                params: ["sys.float.ohos_id_corner_radius_clicked"],
                bundleName: "",
                moduleName: ""
              });
              Row.onHover((e => {
                this.hoverIndex = e ? t : -1
              }));
              Row.onDragStart(((e, i) => {
                if (this.onLabelDragStart) return this.onLabelDragStart(t, e)
              }));
              Row.onDragEnter(((e, i) => {
                this.onLabelDragEnter && this.onLabelDragEnter(t, e)
              }));
              Row.onDragLeave(((e, i) => {
                this.onLabelDragLeave && this.onLabelDragLeave(t, e)
              }));
              Row.onDrop(((e, i) => {
                this.onLabelDrop && (t === this.labels.length - 1 && this.onLabelDragCancel ?
                  this.onLabelDragCancel(e) : this.onLabelDrop(t, e))
              }));
              i || Row.pop();
              ViewStackProcessor.StopGetAccessRecording()
            }));
            this.observeComponentCreation(((e, t) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              If.create();
              i.icon ? this.ifElseBranchUpdateFunction(0, (() => {
                this.observeComponentCreation(((e, t) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(e);
                  Image.create(i.icon);
                  Image.width(24);
                  Image.height(24);
                  Image.margin({
                    left: 6
                  });
                  t || Image.pop();
                  ViewStackProcessor.StopGetAccessRecording()
                }))
              })) : this.ifElseBranchUpdateFunction(1, (() => {}));
              t || If.pop();
              ViewStackProcessor.StopGetAccessRecording()
            }));
            If.pop();
            this.observeComponentCreation(((e, s) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              Text.create(i.text);
              Text.fontSize({
                id: -1,
                type: 10002,
                params: ["sys.float.ohos_id_text_size_body1"],
                bundleName: "",
                moduleName: ""
              });
              Text.fontColor({
                id: -1,
                type: 10001,
                params: ["sys.color.ohos_id_color_text_primary"],
                bundleName: "",
                moduleName: ""
              });
              Text.textOverflow({
                overflow: this.hoverIndex === t ? TextOverflow.MARQUEE : TextOverflow
                  .Ellipsis
              });
              Text.maxLines(1);
              Text.margin({
                left: i.icon ? 0 : 8,
                right: 8
              });
              Text.layoutWeight(1);
              s || Text.pop();
              ViewStackProcessor.StopGetAccessRecording()
            }));
            Text.pop();
            Row.pop()
          }));
          s || If.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        If.pop()
      }), ((e, t) => e.text + e.icon + t), !0, !0);
      t || ForEach.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    ForEach.pop()
  }
  initialRender() {
    this.breadcrumbBuilder.bind(this)()
  }
  rerender() {
    this.updateDirtyElements()
  }
}

export default { Breadcrumb }