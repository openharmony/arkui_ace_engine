/// <reference path="./import.ts" />

class RatingStarsModifier extends Modifier<number> {
    static identity: Symbol = Symbol("ratingStars");
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().rating.resetStars(node);
        }
        else {
            GetUINativeModule().rating.setStars(node, this.value);
        }
    }
}

class RatingStepSizeModifier extends Modifier<number> {
    static identity: Symbol = Symbol("ratingStepSize");
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().rating.resetStepSize(node);
        }
        else {
            GetUINativeModule().rating.setStepSize(node, this.value);
        }
    }
}

class RatingStarStyleModifier extends Modifier<ArkStarStyle> {
    static identity: Symbol = Symbol("ratingStarStyle");
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().rating.resetStarStyle(node);
        }
        else {
            GetUINativeModule().rating.setStarStyle(node,
                this.value?.backgroundUri, this.value?.foregroundUri, this.value?.secondaryUri);
        }
    }
}

class ArkRatingComponent extends ArkComponent implements RatingAttribute {
    onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this {
        throw new Error("Method not implemented.");
    }
    stars(value: number): this {
        if (isUndefined(value)) {
            let stars = 0;
            if (isNumber (value) && value > 0) {
                stars = value;
            }
            modifier(this._modifiers, RatingStarsModifier, stars);
        } else {
            modifier(this._modifiers, RatingStarsModifier, undefined);
        }
        return this;
    }
    stepSize(value: number): this {
        if (isNumber (value) && value >= 0.1) {
            modifier(this._modifiers, RatingStepSizeModifier, value);
        } else {
            modifier(this._modifiers, RatingStepSizeModifier, undefined);
        }
        return this;
    }
    starStyle(value: { backgroundUri: string; foregroundUri: string; secondaryUri?: string | undefined; }): this {
        let starStyle = new ArkStarStyle();
        if (value !== undefined && isObject(value)) {
            starStyle.backgroundUri = value.backgroundUri;
            starStyle.foregroundUri = value.foregroundUri;
            starStyle.secondaryUri = value.secondaryUri;

            modifier(this._modifiers, RatingStarStyleModifier, starStyle);
        } else {
            modifier(this._modifiers, RatingStarStyleModifier, undefined);
        }
        return this;
    }
    onChange(callback: (value: number) => void): this {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.Rating.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    var nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, ()=> {
      return new ArkRatingComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
}
