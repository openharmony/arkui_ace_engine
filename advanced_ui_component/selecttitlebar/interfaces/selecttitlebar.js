/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

if (!('finalizeConstruction' in ViewPU.prototype)) {
  Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => { });
}
const KeyCode = requireNapi('multimodalInput.keyCode').KeyCode;
const PUBLIC_MORE = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAMAAAADACAY' +
  'AAABS3GwHAAAAIGNIUk0AAHomAACAhAAA+gAAAIDoAAB1MAAA6mAAADqYAAAXcJy6UTwAAAAEZ0FNQQAAsY58+1GTAAA' +
  'AAXNSR0IArs4c6QAAAAZiS0dEAP8A/wD/oL2nkwAAAAlwSFlzAAAOxAAADsQBlSsOGwAABEZJREFUeNrt3D1rFFEUBuA' +
  'xhmAhFlYpUohYiYWFRcAmKAhWK2pjo1iKf8BCMIKFf8BarCyMhVj4VZhGSKEg2FqJyCKWIhYWnstMINgYsh+cmfs88BI' +
  'Cydxw7jmzu2HvNg0AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAADBN+3r6dx+LXIqsRpa7FF8j48hm5Fn3Peo9mAEYRdY' +
  'jJ3f582Vj7nZfUe/eDsCRyMPI2h5/fyNyI/JDT6v3Tvt7sBllE15ETkxwjeORi5G3ke/6W737MgBnI68jh6ZwrcORq5H' +
  'nhkC9+zAA5YXXy8jBKV5zKXIu8jjyS7+rd+YBeNVtyrSVO9PRyBM9r94LSTfjWuTUDK9/eYIXeENUbb0zDsBi5PYc1rm' +
  'j79U74wCszuih+F/ljrSi/+uud8YBGA10rayqrnfGAVgb6FpZVV3vjAOwPNC1sqq63hkHYGWga2VVdb0XKt/8Rf1fd70' +
  'zDsB4jmt5u3Tl9a59AMb6v+56ZxyArYGulVXV9c44ABtzXOup/q+73hkH4N2cHio/Rj7r/7rrnXEAfkfuz2Gddb2v3ln' +
  '/DfpgxneLzaY9xE3l9c46AH8iVyI/Z3Dt8nB/Xc+rd5H5QMy3yJemPVs6zY0edc9HUe/0Z4I/dQ/N5Vjd0oTXKp9QcKF' +
  'pD2qj3r0YgO1NeRM507TH6/bifeR85IMeV++d+vTBWOV9JDcjt5rdv6uw3M3uRR7pa/Xu+wBsOxA53bTnTP/3UX1b3fN' +
  'Q1BsAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAKqyr6d/97HIpchqZLlL8TUyjmxGnnX' +
  'fo96DGYBRZD1ycpc/XzbmbvcV9e7tAByJPIys7fH3NyI3Ij/0tHrvtL8Hm1E24UXkxATXOB65GHkb+a6/1bsvA3A28jp' +
  'yaArXOhy5GnluCNS7DwNQXni9jByc4jWXIucijyO/9Lt6Zx6AV92mTFu5Mx2NPNHz6r2QdDOuRU7N8PqXJ3iBN0TV1jv' +
  'jACxGbs9hnTv6Xr0zDsDqjB6K/1XuSCv6v+56ZxyA0UDXyqrqemccgLWBrpVV1fXOOADLA10rq6rrnXEAVga6VlZV13u' +
  'h8s1f1P911zvjAIznuJa3S1de79oHYKz/6653xgHYGuhaWVVd74wDsDHHtZ7q/7rrnXEA3s3pofJj5LP+r7veGQfgd+T' +
  '+HNZZ1/vqnfXfoA9mfLfYbNpD3FRe76wD8CdyJfJzBtcuD/fX9bx6F5kPxHyLfGnas6XT3OhR93wU9U5/JvhT99BcjtU' +
  'tTXit8gkFF5r2oDbq3YsB2N6UN5EzTXu8bi/eR85HPuhx9d6pTx+MVd5HcjNyq9n9uwrL3exe5JG+Vu++D8C2A5HTTXv' +
  'O9H8f1bfVPQ9FvQEAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAgCn7C9HjBtwWfXpKAAAAAElFTkSuQmCC';
const PUBLIC_BACK = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAMAAAADACAY' +
  'AAABS3GwHAAAAIGNIUk0AAHomAACAhAAA+gAAAIDoAAB1MAAA6mAAADqYAAAXcJy6UTwAAAAEZ0FNQQAAsY58+1GTAAAAA' +
  'XNSR0IArs4c6QAAAAZiS0dEAP8A/wD/oL2nkwAAAAlwSFlzAAAOxAAADsQBlSsOGwAAA8VJREFUeNrt3LFLlHEYwPFXz0G' +
  'iIZpEoikkwsFRIiK3gqCigxIC/4Kmhv6OoChouaGoqKCgCKducGh0cDAIamhwiCaHCIeelztpUszee/vl8/nAM3Vd8nufr' +
  '+fddVYVAAAAAAAAAAAAAAAAAAAAAABQijFH0KhrMd2Y2ZitmNWYRzHLjkYAB9lUzMOYizv8eS/mZsymoypLxxE0svzvY07' +
  'vcpu5mOmY145LAAdx+U/u4bZzwx+JPjq2cow7glaWf1vXsQkg6/JvPwoggJTLjwDSL/8nRyiAzN/5nzpGAWRd/n7MM0cpg' +
  'IzLvx6z6CjL453gdpZ/IWbDcQrA8iMAy48ALD8CsPwIwPIjAMuPACw/ArD8CMDyIwDLjwAsPwKw/AjA8iMAy48ALD8CsPw' +
  'IwPIjAMuPACw/ArD85A3A8pM2AMtP2gAsP2kDsPykDcDykzYAy0/aACw/aQOw/KQNwPKTNgDLT9oALD9pA7D8pA3A8pM2A' +
  'MtP2gAsP2kDsPykDcDykzYAy0/aACw/aQOw/KQNwPKTNgDLT9oALD9pA7D8pA3A8pM2AMtP2gAsP2kDsPykDcDykzYAy0/' +
  'aACw/aQOw/KQNwPLz3xlv6H4mYp5YfrI+AizF9BwnI/AlZi3mbsxy03feaeh+HsQcc60YgSMxMzE3YmZj3sX8LOlHoPoLn' +
  'HedaEE35n5pzwF856dN9SPBpZICmHRNaNnlkgL46nrQsvmSAqhftlx1TWjR4ZICqPVcE1q0XloA96rBa7XQhl5pAWzFXKm' +
  '8i8vo9WMeN3VnnQa/sO8xL2POxEy7Toxo+RdjNpu6w1F9HuBqNXi99lw1eKMM9utHzIeYV8MftbccCQAAAAAAsBdt/XLc+s' +
  'Py9W+MmPqL+1iJuVA1+C4gdFr6d77FvK0GH2nb739lPR5zNuZ51eBnQhFAJQIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIE' +
  'IAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAI' +
  'EIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIE8M8jmBlGgABSRnAqZiXms+MUQNYIDnkUKMu4I/gj6z' +
  'ELMRv7/PsnHKEAMkcw6fgEkDmCNUcngMwRvHFsngRnfWJcL/9tRyaAgxrB+ZijO9ymH7MUs+m4yjLmCBozEXMr5nr1+9We1' +
  'ZgXMXccDwAAAAAAAAAAAAAAAAAAAAAAwO5+AfVgtqHKRnawAAAAAElFTkSuQmCC';
export class SelectTitleBar extends ViewPU {
  constructor(q7, r7, s7, t7 = -1, u7 = undefined, v7) {
    super(q7, s7, t7, v7);
    if (typeof u7 === 'function') {
      this.paramsGenerator_ = u7;
    }
    this.__selected = new ObservedPropertySimplePU(0, this, 'selected');
    this.options = [];
    this.menuItems = [];
    this.subtitle = '';
    this.badgeValue = 0;
    this.hidesBackButton = false;
    this.onSelected = () => { };
    this.__selectMaxWidth = new ObservedPropertySimplePU(0, this, 'selectMaxWidth');
    this.__backActive = new ObservedPropertySimplePU(false, this, 'backActive');
    this.setInitiallyProvidedValue(r7);
    this.finalizeConstruction();
  }

  setInitiallyProvidedValue(p7) {
    if (p7.selected !== undefined) {
      this.selected = p7.selected;
    }
    if (p7.options !== undefined) {
      this.options = p7.options;
    }
    if (p7.menuItems !== undefined) {
      this.menuItems = p7.menuItems;
    }
    if (p7.subtitle !== undefined) {
      this.subtitle = p7.subtitle;
    }
    if (p7.badgeValue !== undefined) {
      this.badgeValue = p7.badgeValue;
    }
    if (p7.hidesBackButton !== undefined) {
      this.hidesBackButton = p7.hidesBackButton;
    }
    if (p7.onSelected !== undefined) {
      this.onSelected = p7.onSelected;
    }
    if (p7.selectMaxWidth !== undefined) {
      this.selectMaxWidth = p7.selectMaxWidth;
    }
    if (p7.backActive !== undefined) {
      this.backActive = p7.backActive;
    }
  }

  updateStateVars(o7) {
  }

  purgeVariableDependenciesOnElmtId(n7) {
    this.__selected.purgeDependencyOnElmtId(n7);
    this.__selectMaxWidth.purgeDependencyOnElmtId(n7);
    this.__backActive.purgeDependencyOnElmtId(n7);
  }

  aboutToBeDeleted() {
    this.__selected.aboutToBeDeleted();
    this.__selectMaxWidth.aboutToBeDeleted();
    this.__backActive.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }

  get selected() {
    return this.__selected.get();
  }

  set selected(m7) {
    this.__selected.set(m7);
  }

  get selectMaxWidth() {
    return this.__selectMaxWidth.get();
  }

  set selectMaxWidth(l7) {
    this.__selectMaxWidth.set(l7);
  }

  get backActive() {
    return this.__backActive.get();
  }

  set backActive(k7) {
    this.__backActive.set(k7);
  }

  initialRender() {
    this.observeComponentCreation((d7, e7) => {
      ViewStackProcessor.StartGetAccessRecordingFor(d7);
      Flex.create({
        justifyContent: FlexAlign.SpaceBetween,
        alignItems: ItemAlign.Stretch,
      });
      Flex.width('100%');
      Flex.height(SelectTitleBar.totalHeight);
      Flex.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
      Flex.onAreaChange((g7, h7) => {
        let i7 = Number(h7.width);
        if (!this.hidesBackButton) {
          i7 -= ImageMenuItem.imageHotZoneWidth;
          i7 += SelectTitleBar.leftPadding;
          i7 -= SelectTitleBar.leftPaddingWithBack;
        }
        if (this.menuItems !== undefined) {
          let j7 = this.menuItems.length;
          if (j7 >= CollapsibleMenuSection.maxCountOfVisibleItems) {
            i7 -= ImageMenuItem.imageHotZoneWidth * CollapsibleMenuSection.maxCountOfVisibleItems;
          } else if (j7 > 0) {
            i7 -= ImageMenuItem.imageHotZoneWidth * j7;
          }
        }
        if (this.badgeValue) {
          this.selectMaxWidth = i7 - SelectTitleBar.badgeSize - SelectTitleBar.leftPadding -
          SelectTitleBar.rightPadding - SelectTitleBar.badgePadding;
        } else {
          this.selectMaxWidth = i7 - SelectTitleBar.leftPadding - SelectTitleBar.rightPadding;
        }
      });
      if (!e7) {
        Flex.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((b7, c7) => {
      ViewStackProcessor.StartGetAccessRecordingFor(b7);
      Row.create();
      Row.margin({ left: this.hidesBackButton ? { 'id': -1, 'type': 10002,
        params: ['sys.float.ohos_id_max_padding_start'], 'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__' } : { 'id': -1, 'type': 10002,
        params: ['sys.float.ohos_id_default_padding_start'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
      if (!c7) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((n6, o6) => {
      ViewStackProcessor.StartGetAccessRecordingFor(n6);
      If.create();
      if (!this.hidesBackButton) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((z6, a7) => {
            ViewStackProcessor.StartGetAccessRecordingFor(z6);
            Navigator.create();
            Navigator.active(this.backActive);
            if (!a7) {
              Navigator.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          Navigator.pop();
          {
            this.observeComponentCreation((t6, u6) => {
              ViewStackProcessor.StartGetAccessRecordingFor(t6);
              if (u6) {
                let v6 = new ImageMenuItem(this, { item: {
                  value: PUBLIC_BACK,
                  isEnabled: true,
                  action: () => this.backActive = true,
                }, index: -1 }, undefined, t6, () => { },
                  { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 97 });
                ViewPU.create(v6);
                let w6 = () => {
                  return {
                    item: {
                      value: PUBLIC_BACK,
                      isEnabled: true,
                      action: () => this.backActive = true,
                    },
                    index: -1,
                  };
                };
                v6.paramsGenerator_ = w6;
              } else {
                this.updateStateVarsOfChildByElmtId(t6, {});
              }
              ViewStackProcessor.StopGetAccessRecording();
            });
          }
        });
      } else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!o6) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    this.observeComponentCreation((l6, m6) => {
      ViewStackProcessor.StartGetAccessRecordingFor(l6);
      Column.create();
      Column.justifyContent(FlexAlign.Start);
      Column.alignItems(HorizontalAlign.Start);
      Column.constraintSize({ maxWidth: this.selectMaxWidth });
      if (!m6) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((s5, t5) => {
      ViewStackProcessor.StartGetAccessRecordingFor(s5);
      If.create();
      if (this.badgeValue) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((j6, k6) => {
            ViewStackProcessor.StartGetAccessRecordingFor(j6);
            Badge.create({
              count: this.badgeValue,
              position: BadgePosition.Right,
              style: {
                badgeSize: SelectTitleBar.badgeSize,
                badgeColor: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_emphasize'],
                  'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                borderColor: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_emphasize'],
                  'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                borderWidth: 0,
              },
            });
            if (!k6) {
              Badge.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.observeComponentCreation((h6, i6) => {
            ViewStackProcessor.StartGetAccessRecordingFor(h6);
            Row.create();
            Row.justifyContent(FlexAlign.Start);
            Row.margin({ right: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_elements_margin_horizontal_l'],
              'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
            if (!i6) {
              Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.observeComponentCreation((f6, g6) => {
            ViewStackProcessor.StartGetAccessRecordingFor(f6);
            Select.create(this.options);
            Select.selected(this.selected);
            Select.value(this.selected < this.options.length ? this.options[this.selected].value.toString() : '');
            Select.font({ size: this.hidesBackButton && !this.subtitle ?
              { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_headline7'],
                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } :
              { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_headline8'],
                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
            Select.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_text'],
              'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Select.backgroundColor(Color.Transparent);
            Select.onSelect(this.onSelected);
            Select.constraintSize({ maxWidth: this.selectMaxWidth });
            Select.offset({ x: -4 });
            if (!g6) {
              Select.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          Select.pop();
          Row.pop();
          Badge.pop();
        });
      } else {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation((z5, a6) => {
            ViewStackProcessor.StartGetAccessRecordingFor(z5);
            Row.create();
            Row.justifyContent(FlexAlign.Start);
            if (!a6) {
              Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.observeComponentCreation((x5, y5) => {
            ViewStackProcessor.StartGetAccessRecordingFor(x5);
            Select.create(this.options);
            Select.selected(this.selected);
            Select.value(this.selected < this.options.length ? this.options[this.selected].value.toString() : '');
            Select.font({ size: this.hidesBackButton && !this.subtitle ?
              { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_headline7'],
                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } :
              { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_headline8'],
                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
            Select.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_text'],
              'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Select.backgroundColor(Color.Transparent);
            Select.onSelect(this.onSelected);
            Select.constraintSize({ maxWidth: this.selectMaxWidth });
            Select.offset({ x: -4 });
            if (!y5) {
              Select.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          Select.pop();
          Row.pop();
        });
      }
      if (!t5) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    this.observeComponentCreation((i5, j5) => {
      ViewStackProcessor.StartGetAccessRecordingFor(i5);
      If.create();
      if (this.subtitle !== undefined) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((q5, r5) => {
            ViewStackProcessor.StartGetAccessRecordingFor(q5);
            Row.create();
            Row.justifyContent(FlexAlign.Start);
            Row.margin({ left: SelectTitleBar.subtitleLeftPadding });
            if (!r5) {
              Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.observeComponentCreation((o5, p5) => {
            ViewStackProcessor.StartGetAccessRecordingFor(o5);
            Text.create(this.subtitle);
            Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_over_line'],
              'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_subtitle_text'],
              'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Text.maxLines(1);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.constraintSize({ maxWidth: this.selectMaxWidth });
            Text.offset({ y: -4 });
            if (!p5) {
              Text.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          Text.pop();
          Row.pop();
        });
      } else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!j5) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    Column.pop();
    Row.pop();
    this.observeComponentCreation((x4, y4) => {
      ViewStackProcessor.StartGetAccessRecordingFor(x4);
      If.create();
      if (this.menuItems !== undefined && this.menuItems.length > 0) {
        this.ifElseBranchUpdateFunction(0, () => {
          {
            this.observeComponentCreation((c5, d5) => {
              ViewStackProcessor.StartGetAccessRecordingFor(c5);
              if (d5) {
                let e5 = new CollapsibleMenuSection(this, { menuItems: this.menuItems,
                  index: 1 + SelectTitleBar.instanceCount++ }, undefined, c5, () => { },
                  { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 169 });
                ViewPU.create(e5);
                let f5 = () => {
                  return {
                    menuItems: this.menuItems,
                    index: 1 + SelectTitleBar.instanceCount++,
                  };
                };
                e5.paramsGenerator_ = f5;
              } else {
                this.updateStateVarsOfChildByElmtId(c5, {});
              }
              ViewStackProcessor.StopGetAccessRecording();
            });
          }
        });
      } else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!y4) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    Flex.pop();
  }

  rerender() {
    this.updateDirtyElements();
  }
}
SelectTitleBar.badgeSize = 16;
SelectTitleBar.totalHeight = 56;
SelectTitleBar.leftPadding = 24;
SelectTitleBar.leftPaddingWithBack = 12;
SelectTitleBar.rightPadding = 24;
SelectTitleBar.badgePadding = 16;
SelectTitleBar.subtitleLeftPadding = 4;
SelectTitleBar.instanceCount = 0;
class CollapsibleMenuSection extends ViewPU {
  constructor(k4, l4, m4, n4 = -1, o4 = undefined, p4) {
    super(k4, m4, n4, p4);
    if (typeof o4 === 'function') {
      this.paramsGenerator_ = o4;
    }
    this.menuItems = [];
    this.index = 0;
    this.firstFocusableIndex = -1;
    this.__isPopupShown = new ObservedPropertySimplePU(false, this, 'isPopupShown');
    this.__isMoreIconOnFocus = new ObservedPropertySimplePU(false, this, 'isMoreIconOnFocus');
    this.__isMoreIconOnHover = new ObservedPropertySimplePU(false, this, 'isMoreIconOnHover');
    this.__isMoreIconOnClick = new ObservedPropertySimplePU(false, this, 'isMoreIconOnClick');
    this.setInitiallyProvidedValue(l4);
    this.finalizeConstruction();
  }

  setInitiallyProvidedValue(j4) {
    if (j4.menuItems !== undefined) {
      this.menuItems = j4.menuItems;
    }
    if (j4.index !== undefined) {
      this.index = j4.index;
    }
    if (j4.firstFocusableIndex !== undefined) {
      this.firstFocusableIndex = j4.firstFocusableIndex;
    }
    if (j4.isPopupShown !== undefined) {
      this.isPopupShown = j4.isPopupShown;
    }
    if (j4.isMoreIconOnFocus !== undefined) {
      this.isMoreIconOnFocus = j4.isMoreIconOnFocus;
    }
    if (j4.isMoreIconOnHover !== undefined) {
      this.isMoreIconOnHover = j4.isMoreIconOnHover;
    }
    if (j4.isMoreIconOnClick !== undefined) {
      this.isMoreIconOnClick = j4.isMoreIconOnClick;
    }
  }

  updateStateVars(i4) {
  }

  purgeVariableDependenciesOnElmtId(h4) {
    this.__isPopupShown.purgeDependencyOnElmtId(h4);
    this.__isMoreIconOnFocus.purgeDependencyOnElmtId(h4);
    this.__isMoreIconOnHover.purgeDependencyOnElmtId(h4);
    this.__isMoreIconOnClick.purgeDependencyOnElmtId(h4);
  }

  aboutToBeDeleted() {
    this.__isPopupShown.aboutToBeDeleted();
    this.__isMoreIconOnFocus.aboutToBeDeleted();
    this.__isMoreIconOnHover.aboutToBeDeleted();
    this.__isMoreIconOnClick.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }

  get isPopupShown() {
    return this.__isPopupShown.get();
  }

  set isPopupShown(g4) {
    this.__isPopupShown.set(g4);
  }

  get isMoreIconOnFocus() {
    return this.__isMoreIconOnFocus.get();
  }

  set isMoreIconOnFocus(f4) {
    this.__isMoreIconOnFocus.set(f4);
  }

  get isMoreIconOnHover() {
    return this.__isMoreIconOnHover.get();
  }

  set isMoreIconOnHover(e4) {
    this.__isMoreIconOnHover.set(e4);
  }

  get isMoreIconOnClick() {
    return this.__isMoreIconOnClick.get();
  }

  set isMoreIconOnClick(d4) {
    this.__isMoreIconOnClick.set(d4);
  }

  getMoreIconFgColor() {
    return this.isMoreIconOnClick ?
      { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_icon_pressed'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } :
      { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_icon'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
  }

  getMoreIconBgColor() {
    if (this.isMoreIconOnClick) {
      return { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_click_effect'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    } else if (this.isMoreIconOnHover) {
      return { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_hover'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    } else {
      return Color.Transparent;
    }
  }

  aboutToAppear() {
    this.menuItems.forEach((b4, c4) => {
      if (b4.isEnabled && this.firstFocusableIndex === -1 && c4 > CollapsibleMenuSection.maxCountOfVisibleItems - 2) {
        this.firstFocusableIndex = this.index * 1000 + c4 + 1;
      }
    });
  }

  initialRender() {
    this.observeComponentCreation((y3, z3) => {
      ViewStackProcessor.StartGetAccessRecordingFor(y3);
      Column.create();
      Column.height('100%');
      Column.margin({ right: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_default_padding_end'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
      Column.justifyContent(FlexAlign.Center);
      if (!z3) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((w3, x3) => {
      ViewStackProcessor.StartGetAccessRecordingFor(w3);
      Row.create();
      if (!x3) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((y1, z1) => {
      ViewStackProcessor.StartGetAccessRecordingFor(y1);
      If.create();
      if (this.menuItems.length <= CollapsibleMenuSection.maxCountOfVisibleItems) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((i3, j3) => {
            ViewStackProcessor.StartGetAccessRecordingFor(i3);
            ForEach.create();
            const k3 = (m3, n3) => {
              const o3 = m3;
              {
                this.observeComponentCreation((q3, r3) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(q3);
                  if (r3) {
                    let s3 = new ImageMenuItem(this, { item: o3, index: this.index * 1000 + n3 + 1 }, undefined, q3,
                      () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 244 });
                    ViewPU.create(s3);
                    let t3 = () => {
                      return {
                        item: o3,
                        index: this.index * 1000 + n3 + 1,
                      };
                    };
                    s3.paramsGenerator_ = t3;
                  } else {
                    this.updateStateVarsOfChildByElmtId(q3, {});
                  }
                  ViewStackProcessor.StopGetAccessRecording();
                });
              }
            };
            this.forEachUpdateFunction(i3, this.menuItems, k3, undefined, true, false);
            if (!j3) {
              ForEach.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          ForEach.pop();
        });
      } else {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation((s2, t2) => {
            ViewStackProcessor.StartGetAccessRecordingFor(s2);
            ForEach.create();
            const u2 = (w2, x2) => {
              const y2 = w2;
              {
                this.observeComponentCreation((a3, b3) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(a3);
                  if (b3) {
                    let c3 = new ImageMenuItem(this, { item: y2, index: this.index * 1000 + x2 + 1 }, undefined, a3,
                      () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 248 });
                    ViewPU.create(c3);
                    let d3 = () => {
                      return {
                        item: y2,
                        index: this.index * 1000 + x2 + 1,
                      };
                    };
                    c3.paramsGenerator_ = d3;
                  } else {
                    this.updateStateVarsOfChildByElmtId(a3, {});
                  }
                  ViewStackProcessor.StopGetAccessRecording();
                });
              }
            };
            this.forEachUpdateFunction(s2, this.menuItems.slice(0, CollapsibleMenuSection.maxCountOfVisibleItems - 1),
              u2, undefined, true, false);
            if (!t2) {
              ForEach.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          ForEach.pop();
          this.observeComponentCreation((g2, h2) => {
            ViewStackProcessor.StartGetAccessRecordingFor(g2);
            Row.create();
            Row.width(ImageMenuItem.imageHotZoneWidth);
            Row.height(ImageMenuItem.imageHotZoneWidth);
            Row.borderRadius(ImageMenuItem.buttonBorderRadius);
            Row.foregroundColor(this.getMoreIconFgColor());
            Row.backgroundColor(this.getMoreIconBgColor());
            Row.justifyContent(FlexAlign.Center);
            ViewStackProcessor.visualState('focused');
            Row.border({
              radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'],
                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
              width: ImageMenuItem.focusBorderWidth,
              color: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_focused_outline'],
                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
              style: BorderStyle.Solid,
            });
            ViewStackProcessor.visualState('normal');
            Row.border({
              radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'],
                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
              width: 0,
            });
            ViewStackProcessor.visualState();
            Row.onFocus(() => this.isMoreIconOnFocus = true);
            Row.onBlur(() => this.isMoreIconOnFocus = false);
            Row.onHover((r2) => this.isMoreIconOnHover = r2);
            Row.onKeyEvent((q2) => {
              if (q2.keyCode !== KeyCode.KEYCODE_ENTER && q2.keyCode !== KeyCode.KEYCODE_SPACE) {
                return;
              }
              if (q2.type === KeyType.Down) {
                this.isMoreIconOnClick = true;
              }
              if (q2.type === KeyType.Up) {
                this.isMoreIconOnClick = false;
              }
            });
            Row.onTouch((p2) => {
              if (p2.type === TouchType.Down) {
                this.isMoreIconOnClick = true;
              }
              if (p2.type === TouchType.Up) {
                this.isMoreIconOnClick = false;
              }
            });
            Row.onClick(() => this.isPopupShown = true);
            Row.bindPopup(this.isPopupShown, {
              builder: { builder: this.popupBuilder.bind(this) },
              placement: Placement.Bottom,
              popupColor: Color.White,
              enableArrow: false,
              onStateChange: (o2) => {
                this.isPopupShown = o2.isVisible;
                if (!o2.isVisible) {
                  this.isMoreIconOnClick = false;
                }
              },
            });
            if (!h2) {
              Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.observeComponentCreation((e2, f2) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e2);
            Image.create(PUBLIC_MORE);
            Image.width(ImageMenuItem.imageSize);
            Image.height(ImageMenuItem.imageSize);
            Image.focusable(true);
            if (!f2) {
              Image.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          Row.pop();
        });
      }
      if (!z1) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    Row.pop();
    Column.pop();
  }

  popupBuilder(b1 = null) {
    this.observeComponentCreation((s1, t1) => {
      ViewStackProcessor.StartGetAccessRecordingFor(s1);
      Column.create();
      Column.width(
        ImageMenuItem.imageHotZoneWidth + CollapsibleMenuSection.focusPadding * CollapsibleMenuSection.marginsNum
      );
      Column.margin({ top: CollapsibleMenuSection.focusPadding, bottom: CollapsibleMenuSection.focusPadding });
      Column.onAppear(() => {
        focusControl.requestFocus(ImageMenuItem.focusablePrefix + this.firstFocusableIndex);
      });
      if (!t1) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((e1, f1) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e1);
      ForEach.create();
      const g1 = (i1, j1) => {
        const k1 = i1;
        {
          this.observeComponentCreation((m1, n1) => {
            ViewStackProcessor.StartGetAccessRecordingFor(m1);
            if (n1) {
              let o1 = new ImageMenuItem(this, { item: k1,
                index: this.index * 1000 + CollapsibleMenuSection.maxCountOfVisibleItems + j1 }, undefined, m1,
                () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 326 });
              ViewPU.create(o1);
              let p1 = () => {
                return {
                  item: k1,
                  index: this.index * 1000 + CollapsibleMenuSection.maxCountOfVisibleItems + j1,
                };
              };
              o1.paramsGenerator_ = p1;
            } else {
              this.updateStateVarsOfChildByElmtId(m1, {});
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
        }
      };
      this.forEachUpdateFunction(e1, this.menuItems.slice(CollapsibleMenuSection.maxCountOfVisibleItems - 1,
        this.menuItems.length), g1, undefined, true, false);
      if (!f1) {
        ForEach.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    ForEach.pop();
    Column.pop();
  }

  rerender() {
    this.updateDirtyElements();
  }
}
CollapsibleMenuSection.maxCountOfVisibleItems = 3;
CollapsibleMenuSection.focusPadding = 4;
CollapsibleMenuSection.marginsNum = 2;
class ImageMenuItem extends ViewPU {
  constructor(v, w, x, y = -1, z = undefined, a1) {
    super(v, x, y, a1);
    if (typeof z === 'function') {
      this.paramsGenerator_ = z;
    }
    this.item = {};
    this.index = 0;
    this.__isOnFocus = new ObservedPropertySimplePU(false, this, 'isOnFocus');
    this.__isOnHover = new ObservedPropertySimplePU(false, this, 'isOnHover');
    this.__isOnClick = new ObservedPropertySimplePU(false, this, 'isOnClick');
    this.setInitiallyProvidedValue(w);
    this.finalizeConstruction();
  }

  setInitiallyProvidedValue(u) {
    if (u.item !== undefined) {
      this.item = u.item;
    }
    if (u.index !== undefined) {
      this.index = u.index;
    }
    if (u.isOnFocus !== undefined) {
      this.isOnFocus = u.isOnFocus;
    }
    if (u.isOnHover !== undefined) {
      this.isOnHover = u.isOnHover;
    }
    if (u.isOnClick !== undefined) {
      this.isOnClick = u.isOnClick;
    }
  }

  updateStateVars(t) {
  }

  purgeVariableDependenciesOnElmtId(s) {
    this.__isOnFocus.purgeDependencyOnElmtId(s);
    this.__isOnHover.purgeDependencyOnElmtId(s);
    this.__isOnClick.purgeDependencyOnElmtId(s);
  }

  aboutToBeDeleted() {
    this.__isOnFocus.aboutToBeDeleted();
    this.__isOnHover.aboutToBeDeleted();
    this.__isOnClick.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }

  get isOnFocus() {
    return this.__isOnFocus.get();
  }

  set isOnFocus(r) {
    this.__isOnFocus.set(r);
  }

  get isOnHover() {
    return this.__isOnHover.get();
  }

  set isOnHover(q) {
    this.__isOnHover.set(q);
  }

  get isOnClick() {
    return this.__isOnClick.get();
  }

  set isOnClick(p) {
    this.__isOnClick.set(p);
  }

  getFgColor() {
    return this.isOnClick ?
      { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_icon_pressed'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } :
      { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_icon'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
  }

  getBgColor() {
    if (this.isOnClick) {
      return { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_click_effect'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    } else if (this.isOnHover) {
      return { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_hover'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    } else {
      return Color.Transparent;
    }
  }

  initialRender() {
    this.observeComponentCreation((e, f) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Row.create();
      Row.width(ImageMenuItem.imageHotZoneWidth);
      Row.height(ImageMenuItem.imageHotZoneWidth);
      Row.borderRadius(ImageMenuItem.buttonBorderRadius);
      Row.foregroundColor(this.getFgColor());
      Row.backgroundColor(this.getBgColor());
      Row.justifyContent(FlexAlign.Center);
      Row.opacity(this.item.isEnabled ? 1 : ImageMenuItem.disabledImageOpacity);
      ViewStackProcessor.visualState('focused');
      Row.border({
        radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'],
          'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
        width: ImageMenuItem.focusBorderWidth,
        color: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_focused_outline'],
          'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
        style: BorderStyle.Solid,
      });
      ViewStackProcessor.visualState('normal');
      Row.border({
        radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'],
          'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
        width: 0,
      });
      ViewStackProcessor.visualState();
      Row.onFocus(() => {
        if (!this.item.isEnabled) {
          return;
        }
        this.isOnFocus = true;
      });
      Row.onBlur(() => this.isOnFocus = false);
      Row.onHover((o) => {
        if (!this.item.isEnabled) {
          return;
        }
        this.isOnHover = o;
      });
      Row.onKeyEvent((n) => {
        if (!this.item.isEnabled) {
          return;
        }
        if (n.keyCode !== KeyCode.KEYCODE_ENTER && n.keyCode !== KeyCode.KEYCODE_SPACE) {
          return;
        }
        if (n.type === KeyType.Down) {
          this.isOnClick = true;
        }
        if (n.type === KeyType.Up) {
          this.isOnClick = false;
        }
      });
      Row.onTouch((m) => {
        if (!this.item.isEnabled) {
          return;
        }
        if (m.type === TouchType.Down) {
          this.isOnClick = true;
        }
        if (m.type === TouchType.Up) {
          this.isOnClick = false;
        }
      });
      Row.onClick(() => this.item.isEnabled && this.item.action && this.item.action());
      if (!f) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((c, d) => {
      ViewStackProcessor.StartGetAccessRecordingFor(c);
      Image.create(this.item.value);
      Image.width(ImageMenuItem.imageSize);
      Image.height(ImageMenuItem.imageSize);
      Image.focusable(this.item.isEnabled);
      Image.key(ImageMenuItem.focusablePrefix + this.index);
      if (!d) {
        Image.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Row.pop();
  }

  rerender() {
    this.updateDirtyElements();
  }
}
ImageMenuItem.imageSize = 24;
ImageMenuItem.imageHotZoneWidth = 48;
ImageMenuItem.buttonBorderRadius = 8;
ImageMenuItem.focusBorderWidth = 2;
ImageMenuItem.disabledImageOpacity = 0.4;
ImageMenuItem.focusablePrefix = 'Id-SelectTitleBar-ImageMenuItem-';
export default {
  SelectTitleBar: SelectTitleBar,
};