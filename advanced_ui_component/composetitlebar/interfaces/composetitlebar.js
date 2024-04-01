/*
 * Copyright (c) 2023-2023 Huawei Device Co., Ltd.
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

const KeyCode = requireNapi("multimodalInput.keyCode").KeyCode;
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
class ComposeTitleBar extends ViewPU {
  constructor(k, j, l, b = -1, m = undefined, n) {
    super(k, l, b, n);
    if (typeof m === "function") {
      this.paramsGenerator_ = m;
    }
    this.item = undefined;
    this.title = '';
    this.subtitle = '';
    this.menuItems = undefined;
    this.__titleMaxWidth = new ObservedPropertySimplePU(0, this, "titleMaxWidth");
    this.__backActive = new ObservedPropertySimplePU(false, this, "backActive");
    this.setInitiallyProvidedValue(j);
  }
  setInitiallyProvidedValue(j) {
    if (j.item !== undefined) {
      this.item = j.item;
    }
    if (j.title !== undefined) {
      this.title = j.title;
    }
    if (j.subtitle !== undefined) {
      this.subtitle = j.subtitle;
    }
    if (j.menuItems !== undefined) {
      this.menuItems = j.menuItems;
    }
    if (j.titleMaxWidth !== undefined) {
      this.titleMaxWidth = j.titleMaxWidth;
    }
    if (j.backActive !== undefined) {
      this.backActive = j.backActive;
    }
  }
  updateStateVars(j) {
  }
  purgeVariableDependenciesOnElmtId(i) {
    this.__titleMaxWidth.purgeDependencyOnElmtId(i);
    this.__backActive.purgeDependencyOnElmtId(i);
  }
  aboutToBeDeleted() {
    this.__titleMaxWidth.aboutToBeDeleted();
    this.__backActive.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get titleMaxWidth() {
    return this.__titleMaxWidth.get();
  }
  set titleMaxWidth(h) {
    this.__titleMaxWidth.set(h);
  }
  get backActive() {
    return this.__backActive.get();
  }
  set backActive(h) {
    this.__backActive.set(h);
  }
  initialRender() {
    this.observeComponentCreation((b, c) => {
      ViewStackProcessor.StartGetAccessRecordingFor(b);
      Flex.create({
        justifyContent: FlexAlign.SpaceBetween,
        alignItems: ItemAlign.Stretch
      });
      Flex.width('100%');
      Flex.height(ComposeTitleBar.totalHeight);
      Flex.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_background'], "bundleName": "", "moduleName": "" });
      Flex.onAreaChange((t, h) => {
        let u = Number(h.width);
        if (this.menuItems !== undefined) {
          let v = this.menuItems.length;
          if (v >= CollapsibleMenuSection.maxCountOfVisibleItems) {
            u = u - ImageMenuItem.imageHotZoneWidth * CollapsibleMenuSection.maxCountOfVisibleItems;
          }
          else if (v > 0) {
            u = u - ImageMenuItem.imageHotZoneWidth * v;
          }
        }
        this.titleMaxWidth = u;
        this.titleMaxWidth -= ComposeTitleBar.leftPadding;
        this.titleMaxWidth -= ImageMenuItem.imageHotZoneWidth;
        if (this.item !== undefined) {
          this.titleMaxWidth -= ComposeTitleBar.portraitImageLeftPadding
            + ComposeTitleBar.portraitImageSize
            + ComposeTitleBar.portraitImageRightPadding;
        }
        this.titleMaxWidth -= ComposeTitleBar.rightPadding;
      });
      if (!c) {
        Flex.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((b, c) => {
      ViewStackProcessor.StartGetAccessRecordingFor(b);
      Row.create();
      Row.margin({ left: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_default_padding_start'], "bundleName": "", "moduleName": "" } });
      if (!c) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((b, c) => {
      ViewStackProcessor.StartGetAccessRecordingFor(b);
      Navigator.create();
      Navigator.active(this.backActive);
      if (!c) {
        Navigator.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Navigator.pop();
    {
      this.observeComponentCreation((b, c) => {
        ViewStackProcessor.StartGetAccessRecordingFor(b);
        if (c) {
          let m = () => {
            return {
              item: {
                value: { "id": -1, "type": 20000, params: ['sys.media.ohos_ic_back'], "bundleName": "", "moduleName": "" },
                isEnabled: true,
                action: () => this.backActive = true
              },
              index: -1
            };
          };
          ViewPU.create(new ImageMenuItem(this, { item: {
            value: { "id": -1, "type": 20000, params: ['sys.media.ohos_ic_back'], "bundleName": "", "moduleName": "" },
            isEnabled: true,
            action: () => this.backActive = true
          }, index: -1 }, undefined, b, m, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 89 }));
        }
        else {
          this.updateStateVarsOfChildByElmtId(b, {});
        }
        ViewStackProcessor.StopGetAccessRecording();
      });
    }
    this.observeComponentCreation((b, c) => {
      ViewStackProcessor.StartGetAccessRecordingFor(b);
      If.create();
      if (this.item !== undefined) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((b, c) => {
            ViewStackProcessor.StartGetAccessRecordingFor(b);
            Image.create(this.item.value);
            Image.width(ComposeTitleBar.portraitImageSize);
            Image.height(ComposeTitleBar.portraitImageSize);
            Image.margin({
              left: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_paragraph_margin_xs'], "bundleName": "", "moduleName": "" },
              right: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_paragraph_margin_m'], "bundleName": "", "moduleName": "" }
            });
            Image.focusable(false);
            Image.borderRadius(ImageMenuItem.buttonBorderRadius);
            if (!c) {
              Image.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!c) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    this.observeComponentCreation((b, c) => {
      ViewStackProcessor.StartGetAccessRecordingFor(b);
      Column.create();
      Column.justifyContent(FlexAlign.Start);
      Column.alignItems(HorizontalAlign.Start);
      Column.constraintSize({ maxWidth: this.titleMaxWidth });
      if (!c) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((b, c) => {
      ViewStackProcessor.StartGetAccessRecordingFor(b);
      If.create();
      if (this.title !== undefined) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((b, c) => {
            ViewStackProcessor.StartGetAccessRecordingFor(b);
            Row.create();
            Row.justifyContent(FlexAlign.Start);
            if (!c) {
              Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.observeComponentCreation((b, c) => {
            ViewStackProcessor.StartGetAccessRecordingFor(b);
            Text.create(this.title);
            Text.fontWeight(FontWeight.Medium);
            Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_headline8'], "bundleName": "", "moduleName": "" });
            Text.fontColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_titlebar_text'], "bundleName": "", "moduleName": "" });
            Text.maxLines(this.subtitle !== undefined ? 1 : 2);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.constraintSize({ maxWidth: this.titleMaxWidth });
            if (!c) {
              Text.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          Text.pop();
          Row.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!c) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    this.observeComponentCreation((b, c) => {
      ViewStackProcessor.StartGetAccessRecordingFor(b);
      If.create();
      if (this.subtitle !== undefined) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((b, c) => {
            ViewStackProcessor.StartGetAccessRecordingFor(b);
            Row.create();
            Row.justifyContent(FlexAlign.Start);
            if (!c) {
              Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.observeComponentCreation((b, c) => {
            ViewStackProcessor.StartGetAccessRecordingFor(b);
            Text.create(this.subtitle);
            Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_over_line'], "bundleName": "", "moduleName": "" });
            Text.fontColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_titlebar_subtitle_text'], "bundleName": "", "moduleName": "" });
            Text.maxLines(1);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.constraintSize({ maxWidth: this.titleMaxWidth });
            if (!c) {
              Text.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          Text.pop();
          Row.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!c) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    Column.pop();
    Row.pop();
    this.observeComponentCreation((b, c) => {
      ViewStackProcessor.StartGetAccessRecordingFor(b);
      If.create();
      if (this.menuItems !== undefined && this.menuItems.length > 0) {
        this.ifElseBranchUpdateFunction(0, () => {
          {
            this.observeComponentCreation((b, c) => {
              ViewStackProcessor.StartGetAccessRecordingFor(b);
              if (c) {
                let m = () => {
                  return {
                    menuItems: this.menuItems,
                    index: 1 + ComposeTitleBar.instanceCount++
                  };
                };
                ViewPU.create(new CollapsibleMenuSection(this, { menuItems: this.menuItems, index: 1 + ComposeTitleBar.instanceCount++ }, undefined, b, m, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 139 }));
              }
              else {
                this.updateStateVarsOfChildByElmtId(b, {});
              }
              ViewStackProcessor.StopGetAccessRecording();
            });
          }
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!c) {
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
ComposeTitleBar.totalHeight = 56;
ComposeTitleBar.leftPadding = 12;
ComposeTitleBar.rightPadding = 12;
ComposeTitleBar.portraitImageSize = 40;
ComposeTitleBar.portraitImageLeftPadding = 4;
ComposeTitleBar.portraitImageRightPadding = 16;
ComposeTitleBar.instanceCount = 0;
class CollapsibleMenuSection extends ViewPU {
  constructor(k, j, l, b = -1, m = undefined, n) {
    super(k, l, b, n);
    if (typeof m === "function") {
      this.paramsGenerator_ = m;
    }
    this.menuItems = undefined;
    this.index = 0;
    this.firstFocusableIndex = -1;
    this.__isPopupShown = new ObservedPropertySimplePU(false, this, "isPopupShown");
    this.__isMoreIconOnFocus = new ObservedPropertySimplePU(false, this, "isMoreIconOnFocus");
    this.__isMoreIconOnHover = new ObservedPropertySimplePU(false, this, "isMoreIconOnHover");
    this.__isMoreIconOnClick = new ObservedPropertySimplePU(false, this, "isMoreIconOnClick");
    this.setInitiallyProvidedValue(j);
  }
  setInitiallyProvidedValue(j) {
    if (j.menuItems !== undefined) {
      this.menuItems = j.menuItems;
    }
    if (j.index !== undefined) {
      this.index = j.index;
    }
    if (j.firstFocusableIndex !== undefined) {
      this.firstFocusableIndex = j.firstFocusableIndex;
    }
    if (j.isPopupShown !== undefined) {
      this.isPopupShown = j.isPopupShown;
    }
    if (j.isMoreIconOnFocus !== undefined) {
      this.isMoreIconOnFocus = j.isMoreIconOnFocus;
    }
    if (j.isMoreIconOnHover !== undefined) {
      this.isMoreIconOnHover = j.isMoreIconOnHover;
    }
    if (j.isMoreIconOnClick !== undefined) {
      this.isMoreIconOnClick = j.isMoreIconOnClick;
    }
  }
  updateStateVars(j) {
  }
  purgeVariableDependenciesOnElmtId(i) {
    this.__isPopupShown.purgeDependencyOnElmtId(i);
    this.__isMoreIconOnFocus.purgeDependencyOnElmtId(i);
    this.__isMoreIconOnHover.purgeDependencyOnElmtId(i);
    this.__isMoreIconOnClick.purgeDependencyOnElmtId(i);
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
  set isPopupShown(h) {
    this.__isPopupShown.set(h);
  }
  get isMoreIconOnFocus() {
    return this.__isMoreIconOnFocus.get();
  }
  set isMoreIconOnFocus(h) {
    this.__isMoreIconOnFocus.set(h);
  }
  get isMoreIconOnHover() {
    return this.__isMoreIconOnHover.get();
  }
  set isMoreIconOnHover(h) {
    this.__isMoreIconOnHover.set(h);
  }
  get isMoreIconOnClick() {
    return this.__isMoreIconOnClick.get();
  }
  set isMoreIconOnClick(h) {
    this.__isMoreIconOnClick.set(h);
  }
  getMoreIconFgColor() {
    return this.isMoreIconOnClick
      ? { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_titlebar_icon_pressed'], "bundleName": "", "moduleName": "" } : { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_titlebar_icon'], "bundleName": "", "moduleName": "" };
  }
  getMoreIconBgColor() {
    if (this.isMoreIconOnClick) {
      return { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_click_effect'], "bundleName": "", "moduleName": "" };
    }
    else if (this.isMoreIconOnHover) {
      return { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_hover'], "bundleName": "", "moduleName": "" };
    }
    else {
      return Color.Transparent;
    }
  }
  aboutToAppear() {
    if (this.menuItems) {
      this.menuItems.forEach((r, q) => {
        if (r.isEnabled && this.firstFocusableIndex == -1 && q > CollapsibleMenuSection.maxCountOfVisibleItems - 2) {
          this.firstFocusableIndex = this.index * 1000 + q + 1;
        }
      });
    }
  }
  initialRender() {
    this.observeComponentCreation((b, c) => {
      ViewStackProcessor.StartGetAccessRecordingFor(b);
      Column.create();
      Column.height('100%');
      Column.margin({ right: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_default_padding_end'], "bundleName": "", "moduleName": "" } });
      Column.justifyContent(FlexAlign.Center);
      if (!c) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((b, c) => {
      ViewStackProcessor.StartGetAccessRecordingFor(b);
      Row.create();
      if (!c) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((b, c) => {
      ViewStackProcessor.StartGetAccessRecordingFor(b);
      If.create();
      if (this.menuItems) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((b, c) => {
            ViewStackProcessor.StartGetAccessRecordingFor(b);
            If.create();
            if (this.menuItems.length <= CollapsibleMenuSection.maxCountOfVisibleItems) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation((b, c) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(b);
                  ForEach.create();
                  const o = (p, q) => {
                    const r = p;
                    {
                      this.observeComponentCreation((b, c) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(b);
                        if (c) {
                          let m = () => {
                            return {
                              item: r,
                              index: this.index * 1000 + q + 1
                            };
                          };
                          ViewPU.create(new ImageMenuItem(this, { item: r, index: this.index * 1000 + q + 1 }, undefined, b, m, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 216 }));
                        }
                        else {
                          this.updateStateVarsOfChildByElmtId(b, {});
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                      });
                    }
                  };
                  this.forEachUpdateFunction(b, this.menuItems, o, undefined, true, false);
                  if (!c) {
                    ForEach.pop();
                  }
                  ViewStackProcessor.StopGetAccessRecording();
                });
                ForEach.pop();
              });
            }
            else {
              this.ifElseBranchUpdateFunction(1, () => {
                this.observeComponentCreation((b, c) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(b);
                  ForEach.create();
                  const o = (p, q) => {
                    const r = p;
                    {
                      this.observeComponentCreation((b, c) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(b);
                        if (c) {
                          let m = () => {
                            return {
                              item: r,
                              index: this.index * 1000 + q + 1
                            };
                          };
                          ViewPU.create(new ImageMenuItem(this, { item: r, index: this.index * 1000 + q + 1 }, undefined, b, m, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 220 }));
                        }
                        else {
                          this.updateStateVarsOfChildByElmtId(b, {});
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                      });
                    }
                  };
                  this.forEachUpdateFunction(b, this.menuItems.slice(0, CollapsibleMenuSection.maxCountOfVisibleItems - 1), o, undefined, true, false);
                  if (!c) {
                    ForEach.pop();
                  }
                  ViewStackProcessor.StopGetAccessRecording();
                });
                ForEach.pop();
                this.observeComponentCreation((b, c) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(b);
                  Row.create();
                  Row.width(ImageMenuItem.imageHotZoneWidth);
                  Row.height(ImageMenuItem.imageHotZoneWidth);
                  Row.borderRadius(ImageMenuItem.buttonBorderRadius);
                  Row.foregroundColor(this.getMoreIconFgColor());
                  Row.backgroundColor(this.getMoreIconBgColor());
                  Row.justifyContent(FlexAlign.Center);
                  ViewStackProcessor.visualState("focused");
                  Row.border({
                    radius: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "", "moduleName": "" },
                    width: ImageMenuItem.focusBorderWidth,
                    color: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_focused_outline'], "bundleName": "", "moduleName": "" },
                    style: BorderStyle.Solid
                  });
                  ViewStackProcessor.visualState("normal");
                  Row.border({
                    radius: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "", "moduleName": "" },
                    width: 0
                  });
                  ViewStackProcessor.visualState();
                  Row.onFocus(() => this.isMoreIconOnFocus = true);
                  Row.onBlur(() => this.isMoreIconOnFocus = false);
                  Row.onHover((g) => this.isMoreIconOnHover = g);
                  Row.onKeyEvent((f) => {
                    if (f.keyCode !== KeyCode.KEYCODE_ENTER && f.keyCode !== KeyCode.KEYCODE_SPACE) {
                      return;
                    }
                    if (f.type === KeyType.Down) {
                      this.isMoreIconOnClick = true;
                    }
                    if (f.type === KeyType.Up) {
                      this.isMoreIconOnClick = false;
                    }
                  });
                  Row.onTouch((f) => {
                    if (f.type === TouchType.Down) {
                      this.isMoreIconOnClick = true;
                    }
                    if (f.type === TouchType.Up) {
                      this.isMoreIconOnClick = false;
                    }
                  });
                  Row.onClick(() => this.isPopupShown = true);
                  Row.bindPopup(this.isPopupShown, {
                    builder: { builder: this.popupBuilder.bind(this) },
                    placement: Placement.Bottom,
                    popupColor: Color.White,
                    enableArrow: false,
                    onStateChange: (s) => {
                      this.isPopupShown = s.isVisible;
                      if (!s.isVisible) {
                        this.isMoreIconOnClick = false;
                      }
                    }
                  });
                  if (!c) {
                    Row.pop();
                  }
                  ViewStackProcessor.StopGetAccessRecording();
                });
                this.observeComponentCreation((b, c) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(b);
                  Image.create(PUBLIC_MORE);
                  Image.width(ImageMenuItem.imageSize);
                  Image.height(ImageMenuItem.imageSize);
                  Image.focusable(true);
                  if (!c) {
                    Image.pop();
                  }
                  ViewStackProcessor.StopGetAccessRecording();
                });
                Row.pop();
              });
            }
            if (!c) {
              If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          If.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!c) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    Row.pop();
    Column.pop();
  }
  popupBuilder(k = null) {
    this.observeComponentCreation((b, c) => {
      ViewStackProcessor.StartGetAccessRecordingFor(b);
      Column.create();
      Column.width(ImageMenuItem.imageHotZoneWidth + CollapsibleMenuSection.focusPadding * CollapsibleMenuSection.marginsNum);
      Column.margin({ top: CollapsibleMenuSection.focusPadding, bottom: CollapsibleMenuSection.focusPadding });
      Column.onAppear(() => {
        focusControl.requestFocus(ImageMenuItem.focusablePrefix + this.firstFocusableIndex);
      });
      if (!c) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((b, c) => {
      ViewStackProcessor.StartGetAccessRecordingFor(b);
      If.create();
      if (this.menuItems) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((b, c) => {
            ViewStackProcessor.StartGetAccessRecordingFor(b);
            ForEach.create();
            const o = (p, q) => {
              const r = p;
              {
                this.observeComponentCreation((b, c) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(b);
                  if (c) {
                    let m = () => {
                      return {
                        item: r,
                        index: this.index * 1000 + CollapsibleMenuSection.maxCountOfVisibleItems + q
                      };
                    };
                    ViewPU.create(new ImageMenuItem(this, { item: r, index: this.index * 1000 + CollapsibleMenuSection.maxCountOfVisibleItems + q }, undefined, b, m, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 300 }));
                  }
                  else {
                    this.updateStateVarsOfChildByElmtId(b, {});
                  }
                  ViewStackProcessor.StopGetAccessRecording();
                });
              }
            };
            this.forEachUpdateFunction(b, this.menuItems.slice(CollapsibleMenuSection.maxCountOfVisibleItems - 1, this.menuItems.length), o, undefined, true, false);
            if (!c) {
              ForEach.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          ForEach.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!c) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
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
  constructor(k, j, l, b = -1, m = undefined, n) {
    super(k, l, b, n);
    if (typeof m === "function") {
      this.paramsGenerator_ = m;
    }
    this.item = undefined;
    this.index = 0;
    this.__isOnFocus = new ObservedPropertySimplePU(false, this, "isOnFocus");
    this.__isOnHover = new ObservedPropertySimplePU(false, this, "isOnHover");
    this.__isOnClick = new ObservedPropertySimplePU(false, this, "isOnClick");
    this.setInitiallyProvidedValue(j);
  }
  setInitiallyProvidedValue(j) {
    if (j.item !== undefined) {
      this.item = j.item;
    }
    if (j.index !== undefined) {
      this.index = j.index;
    }
    if (j.isOnFocus !== undefined) {
      this.isOnFocus = j.isOnFocus;
    }
    if (j.isOnHover !== undefined) {
      this.isOnHover = j.isOnHover;
    }
    if (j.isOnClick !== undefined) {
      this.isOnClick = j.isOnClick;
    }
  }
  updateStateVars(j) {
  }
  purgeVariableDependenciesOnElmtId(i) {
    this.__isOnFocus.purgeDependencyOnElmtId(i);
    this.__isOnHover.purgeDependencyOnElmtId(i);
    this.__isOnClick.purgeDependencyOnElmtId(i);
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
  set isOnFocus(h) {
    this.__isOnFocus.set(h);
  }
  get isOnHover() {
    return this.__isOnHover.get();
  }
  set isOnHover(h) {
    this.__isOnHover.set(h);
  }
  get isOnClick() {
    return this.__isOnClick.get();
  }
  set isOnClick(h) {
    this.__isOnClick.set(h);
  }
  getFgColor() {
    return this.isOnClick
      ? { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_titlebar_icon_pressed'], "bundleName": "", "moduleName": "" } : { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_titlebar_icon'], "bundleName": "", "moduleName": "" };
  }
  getBgColor() {
    if (this.isOnClick) {
      return { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_click_effect'], "bundleName": "", "moduleName": "" };
    }
    else if (this.isOnHover) {
      return { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_hover'], "bundleName": "", "moduleName": "" };
    }
    else {
      return Color.Transparent;
    }
  }
  initialRender() {
    this.observeComponentCreation((b, c) => {
      var d;
      ViewStackProcessor.StartGetAccessRecordingFor(b);
      Row.create();
      Row.width(ImageMenuItem.imageHotZoneWidth);
      Row.height(ImageMenuItem.imageHotZoneWidth);
      Row.borderRadius(ImageMenuItem.buttonBorderRadius);
      Row.foregroundColor(this.getFgColor());
      Row.backgroundColor(this.getBgColor());
      Row.justifyContent(FlexAlign.Center);
      Row.opacity(((d = this.item) === null || d === void 0 ? void 0 : d.isEnabled) ? 1 : ImageMenuItem.disabledImageOpacity);
      ViewStackProcessor.visualState("focused");
      Row.border({
        radius: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "", "moduleName": "" },
        width: ImageMenuItem.focusBorderWidth,
        color: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_focused_outline'], "bundleName": "", "moduleName": "" },
        style: BorderStyle.Solid
      });
      ViewStackProcessor.visualState("normal");
      Row.border({
        radius: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "", "moduleName": "" },
        width: 0
      });
      ViewStackProcessor.visualState();
      Row.onFocus(() => {
        var d;
        if (!((d = this.item) === null || d === void 0 ? void 0 : d.isEnabled)) {
          return;
        }
        this.isOnFocus = true;
      });
      Row.onBlur(() => this.isOnFocus = false);
      Row.onHover((g) => {
        var d;
        if (!((d = this.item) === null || d === void 0 ? void 0 : d.isEnabled)) {
          return;
        }
        this.isOnHover = g;
      });
      Row.onKeyEvent((f) => {
        var d;
        if (!((d = this.item) === null || d === void 0 ? void 0 : d.isEnabled)) {
          return;
        }
        if (f.keyCode !== KeyCode.KEYCODE_ENTER && f.keyCode !== KeyCode.KEYCODE_SPACE) {
          return;
        }
        if (f.type === KeyType.Down) {
          this.isOnClick = true;
        }
        if (f.type === KeyType.Up) {
          this.isOnClick = false;
        }
      });
      Row.onTouch((f) => {
        var d;
        if (!((d = this.item) === null || d === void 0 ? void 0 : d.isEnabled)) {
          return;
        }
        if (f.type === TouchType.Down) {
          this.isOnClick = true;
        }
        if (f.type === TouchType.Up) {
          this.isOnClick = false;
        }
      });
      Row.onClick(() => {
        var d, e;
        if (this.item) {
          return this.item.isEnabled && ((e = (d = this.item).action) === null || e === void 0 ? void 0 : e.call(d));
        }
      });
      if (!c) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((b, c) => {
      var d, e;
      ViewStackProcessor.StartGetAccessRecordingFor(b);
      Image.create((d = this.item) === null || d === void 0 ? void 0 : d.value);
      Image.width(ImageMenuItem.imageSize);
      Image.height(ImageMenuItem.imageSize);
      Image.focusable((e = this.item) === null || e === void 0 ? void 0 : e.isEnabled);
      Image.key(ImageMenuItem.focusablePrefix + this.index);
      Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary'], "bundleName": "", "moduleName": "" });
      if (!c) {
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
ImageMenuItem.focusablePrefix = "Id-ComposeTitleBar-ImageMenuItem-";
export default {
  ComposeTitleBar: ComposeTitleBar
};
