/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

/// <reference path='./../../ark_component/src/import.ts' />

type ComponentObj = { component: any }
function loadComponent(): ComponentObj | undefined {
	if (loadComponent.componentObj === undefined && globalThis.__ArkComponent__ !== undefined) {
		class ImageSpanObjectFitModifier extends ModifierWithKey<any> {
			constructor(value: any) {
				super(value);
			}
			applyPeer(node: any, reset: boolean): void {
				if (reset) {
					getUINativeModule().imageSpan.resetObjectFit(node);
				}
				else {
					getUINativeModule().imageSpan.setObjectFit(node, this.value);
				}
			}
			checkObjectDiff(): boolean {
				return this.stageValue !== this.value;
			}
		}
		(ImageSpanObjectFitModifier as any).identity = Symbol('imageSpanObjectFit');

		class ImageSpanVerticalAlignModifier extends ModifierWithKey<any> {
			constructor(value: any) {
				super(value);
			}
			applyPeer(node: any, reset: boolean): void {
				if (reset) {
					getUINativeModule().imageSpan.resetVerticalAlign(node);
				}
				else {
					getUINativeModule().imageSpan.setVerticalAlign(node, this.value);
				}
			}
			checkObjectDiff(): boolean {
				return this.stageValue !== this.value;
			}
		}
		(ImageSpanVerticalAlignModifier as any).identity = Symbol('imageSpanVerticalAlign');

		class ImageSpanTextBackgroundStyleModifier extends ModifierWithKey<any> {
			constructor(value: any) {
				super(value);
			}
			applyPeer(node: any, reset: boolean): void {
				if (reset) {
					getUINativeModule().imageSpan.resetTextBackgroundStyle(node);
				}
				else {
					let textBackgroundStyle = new ArkTextBackGroundStyle();
					if (!textBackgroundStyle.convertTextBackGroundStyleOptions(this.value)) {
						getUINativeModule().imageSpan.resetTextBackgroundStyle(node);
					}
					else {
						getUINativeModule().imageSpan.setTextBackgroundStyle(node, textBackgroundStyle.color,
							textBackgroundStyle.radius.topLeft, textBackgroundStyle.radius.topRight,
							textBackgroundStyle.radius.bottomLeft, textBackgroundStyle.radius.bottomRight);
					}
				}
			}
			checkObjectDiff(): boolean {
				let textBackgroundStyle = new ArkTextBackGroundStyle();
				let stageTextBackGroundStyle = new ArkTextBackGroundStyle();
				if (!textBackgroundStyle.convertTextBackGroundStyleOptions(this.value) ||
					!stageTextBackGroundStyle.convertTextBackGroundStyleOptions(this.stageValue)) {
					return false;
				}
				return textBackgroundStyle.checkObjectDiff(stageTextBackGroundStyle);
			}
		}
		(ImageSpanTextBackgroundStyleModifier as any).identity = Symbol('imageSpanTextBackgroundStyle');

		class ImageSpanBaselineOffsetModifier extends ModifierWithKey<any> {
			constructor(value: any) {
				super(value);
			}
			applyPeer(node: any, reset: boolean): void {
				if (reset) {
					getUINativeModule().imageSpan.resetBaselineOffset(node);
				}
				else {
					getUINativeModule().imageSpan.setBaselineOffset(node, this.value);
				}
			}
		}
		(ImageSpanBaselineOffsetModifier as any).identity = Symbol('imageSpanBaselineOffset');

		class ImageSpanAltModifier extends ModifierWithKey<any> {
			constructor(value: any) {
				super(value);
			}
			applyPeer(node: any, reset: boolean): void {
				if (reset) {
					getUINativeModule().imageSpan.resetAlt(node);
				}
				else {
					getUINativeModule().imageSpan.setAlt(node, this.value);
				}
			}
		}
		(ImageSpanAltModifier as any).identity = Symbol('imageSpanAlt');

		class ImageSpanOnCompleteModifier extends ModifierWithKey<any> {
			constructor(value: any) {
				super(value);
			}
			applyPeer(node: any, reset: boolean): void {
				if (reset) {
					getUINativeModule().imageSpan.resetOnComplete(node);
				}
				else {
					getUINativeModule().imageSpan.setOnComplete(node, this.value);
				}
			}
		}
		(ImageSpanOnCompleteModifier as any).identity = Symbol('imageSpanOnComplete');

		class ImageSpanOnErrorModifier extends ModifierWithKey<any> {
			constructor(value: any) {
				super(value);
			}
			applyPeer(node: any, reset: boolean): void {
				if (reset) {
					getUINativeModule().imageSpan.resetOnError(node);
				}
				else {
					getUINativeModule().imageSpan.setOnError(node, this.value);
				}
			}
		}
		(ImageSpanOnErrorModifier as any).identity = Symbol('imageSpanOnError');

		class ImageSpanColorFilterModifier extends ModifierWithKey<any> {
			constructor(value: any) {
				super(value);
			}
			applyPeer(node: any, reset: boolean): void {
				if (reset) {
					getUINativeModule().imageSpan.resetColorFilter(node);
				} else {
					getUINativeModule().imageSpan.setColorFilter(node, this.value);
				}
			}
			checkObjectDiff(): boolean {
				return true;
			}
		}
		(ImageSpanColorFilterModifier as any).identity = Symbol('ImageSpanColorFilter');

		class ImageSpanSupportSvg2Modifier extends ModifierWithKey<any> {
			constructor(value: any) {
				super(value);
			}
			applyPeer(node: any, reset: boolean): void {
				if (reset) {
					getUINativeModule().imageSpan.resetSupportSvg2(node);
				}
				else {
					getUINativeModule().imageSpan.setSupportSvg2(node, this.value);
				}
			}
			checkObjectDiff(): boolean {
				return this.stageValue !== this.value;
			}
		}
		(ImageSpanSupportSvg2Modifier as any).identity = Symbol('supportSvg2');

		class ImageSpanBorderRadiusModifier extends ModifierWithKey<any> {
			constructor(value: any) {
				super(value);
			}
			applyPeer(node: any, reset: boolean): void {
				if (reset) {
					getUINativeModule().imageSpan.resetBorderRadius(node);
				} else {
					if (isNumber(this.value) || isString(this.value) || isResource(this.value)) {
						getUINativeModule().imageSpan.setBorderRadius(node, this.value, this.value, this.value, this.value);
					} else {
						let keys = Object.keys(this.value);
						if (Utils.isApiVersionEQAbove(20) &&
							(keys.indexOf('topStart') >= 0 || keys.indexOf('topEnd') >= 0 ||
								keys.indexOf('bottomStart') >= 0 || keys.indexOf('bottomEnd') >= 0)) {
							let localizedBorderRadius = this.value;
							getUINativeModule().imageSpan.setBorderRadius(node, localizedBorderRadius.topStart,
								localizedBorderRadius.topEnd, localizedBorderRadius.bottomStart, localizedBorderRadius.bottomEnd);
						} else {
							getUINativeModule().imageSpan.setBorderRadius(node, this.value.topLeft, this.value.topRight,
								this.value.bottomLeft, this.value.bottomRight);
						}
					}
				}
			}
			checkObjectDiff(): boolean {
				if (!isResource(this.stageValue) && !isResource(this.value)) {
					return !(this.stageValue.topLeft === this.value.topLeft &&
						this.stageValue.topRight === this.value.topRight &&
						this.stageValue.bottomLeft === this.value.bottomLeft &&
						this.stageValue.bottomRight === this.value.bottomRight);
				}
				return true;
			}
		}
		(ImageSpanBorderRadiusModifier as any).identity = Symbol('imageSpanBorderRadius');

		class ImageSpanSrcModifier extends ModifierWithKey<any> {
			constructor(value: any) {
				super(value);
			}
			applyPeer(node: any, reset: boolean): void {
				if (reset) {
					getUINativeModule().imageSpan.setImageSpanSrc(node, '');
				} else {
					getUINativeModule().imageSpan.setImageSpanSrc(node, this.value);
				}
			}
		}
		(ImageSpanSrcModifier as any).identity = Symbol('imageSpanShowSrc');

		class ArkImageSpanComponent extends globalThis.__ArkComponent__ {
			constructor(nativePtr: any, classType: any) {
				super(nativePtr, classType);
			}
			initialize(value: Object[]): this {
				modifierWithKey(this._modifiersWithKeys, ImageSpanSrcModifier.identity, ImageSpanSrcModifier, value[0]);
				return this;
			}
			objectFit(value: ImageFit): this {
				modifierWithKey(this._modifiersWithKeys, ImageSpanObjectFitModifier.identity, ImageSpanObjectFitModifier, value);
				return this;
			}
			verticalAlign(value: ImageVerticalAlign): this {
				modifierWithKey(this._modifiersWithKeys, ImageSpanVerticalAlignModifier.identity, ImageSpanVerticalAlignModifier, value);
				return this;
			}
			textBackgroundStyle(value: ImageTextBackgroundStyle): this {
				modifierWithKey(this._modifiersWithKeys, ImageSpanTextBackgroundStyleModifier.identity, ImageSpanTextBackgroundStyleModifier, value);
				return this;
			}
			baselineOffset(value: LengthMetrics): this {
				modifierWithKey(this._modifiersWithKeys, ImageSpanBaselineOffsetModifier.identity, ImageSpanBaselineOffsetModifier, value);
				return this;
			}
			alt(value: PixelMap): this {
				modifierWithKey(this._modifiersWithKeys, ImageSpanAltModifier.identity, ImageSpanAltModifier, value);
				return this;
			}
			onComplete(
				callback: (result: {
					width: number;
					height: number;
					componentWidth: number;
					componentHeight: number;
					loadingStatus: number;
					contentWidth: number;
					contentHeight: number;
					contentOffsetX: number;
					contentOffsetY: number;
				}) => void): this {
				modifierWithKey(this._modifiersWithKeys, ImageSpanOnCompleteModifier.identity, ImageSpanOnCompleteModifier, callback);
				return this;
			}
			onError(callback: (error: {
				componentWidth: number;
				componentHeight: number;
				message: string;
			}) => void): this {
				modifierWithKey(this._modifiersWithKeys, ImageSpanOnErrorModifier.identity, ImageSpanOnErrorModifier, callback);
				return this;
			}
			colorFilter(value: ColorFilter | DrawingColorFilter): this {
				modifierWithKey(this._modifiersWithKeys, ImageSpanColorFilterModifier.identity, ImageSpanColorFilterModifier, value);
				return this;
			}
			supportSvg2(value: boolean): this {
				modifierWithKey(this._modifiersWithKeys, ImageSpanSupportSvg2Modifier.identity, ImageSpanSupportSvg2Modifier, value);
				return this;
			}
			borderRadius(value: Length | BorderRadiuses): this {
				modifierWithKey(this._modifiersWithKeys, ImageSpanBorderRadiusModifier.identity, ImageSpanBorderRadiusModifier, value);
				return this;
			}
		}
		loadComponent.componentObj = {
			'component': ArkImageSpanComponent,
		};
	}
	return loadComponent.componentObj;
}

class JSImageSpan extends JSViewAbstract {
	static create(value: any): void {
		if (!ViewStackProcessor.UsesNewPipeline()) {
			return;
		}
		Image.createImageSpan(value);
		getUINativeModule().imageSpan.create();
	}

	static alt(value: any): void {
		if (!ViewStackProcessor.UsesNewPipeline()) {
			return;
		}
		Image.alt(value);
	}

	static objectFit(value: any): void {
		getUINativeModule().imageSpan.setObjectFit(true, value);
	}

	static verticalAlign(value: any): void {
		getUINativeModule().imageSpan.setVerticalAlign(true, value);
	}

	static textBackgroundStyle(value: any): void {
		getUINativeModule().imageSpan.setTextBackgroundStyle(true, value);
	}

	static onComplete(value: any): void {
		getUINativeModule().imageSpan.setOnComplete(true, value);
	}

	static onError(value: any): void {
		getUINativeModule().imageSpan.setOnError(true, value);
	}

	static border(value: any): void {
		Image.border(value);
	}

	static borderRadius(value: any): void {
		Image.borderRadius(value);
	}

	static colorFilter(value: any): void {
		getUINativeModule().imageSpan.setColorFilter(true, value);
	}

	static baselineOffset(value: any): void {
		getUINativeModule().imageSpan.setBaselineOffset(true, value);
	}

	static supportSvg2(value: any): void {
		getUINativeModule().imageSpan.setSupportSvg2(true, value);
	}

	static attributeModifier(modifier: any): void {
		attributeModifierFunc.call(this, modifier, (nativePtr: any) => {
			return createComponent(nativePtr);
		}, (nativePtr: any, classType: any, modifierJS: any) => {
			return new modifierJS.ImageSpanModifier(nativePtr, classType);
		});
	}
}

function createComponent(nativePtr: any, classType: any): any {
	loadComponent();
	if (loadComponent.componentObj !== undefined) {
		return new loadComponent.componentObj.component(nativePtr, classType);
	}
	return undefined;
}

function exportComponent(): void {
	globalThis.ArkImageSpanComponent = (loadComponent as any).componentObj?.component;
}

function exportView(): void {
	globalThis.ImageSpan = JSImageSpan;
}

export default { loadComponent, createComponent, exportComponent, exportView };
