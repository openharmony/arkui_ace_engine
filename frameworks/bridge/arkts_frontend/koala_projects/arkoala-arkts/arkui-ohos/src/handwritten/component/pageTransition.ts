import { ICurve, ScaleOptions, TranslateOptions } from './common'
import { ArkUIAniModule } from 'arkui.ani'

export class CommonTransition {
    slide(value: SlideEffect): this {
        return this;
    }
    translate(value: TranslateOptions): this {
        return this;
    }
    scale(value: ScaleOptions): this {
        return this;
    }
    opacity(value: number): this {
        return this;
    }
}
 
export class PageTransitionEnter extends CommonTransition {
    static $_invoke(value: PageTransitionOptions): PageTransitionEnter {
        let res = new PageTransitionEnter();
        ArkUIAniModule._Animation_CreatePageTransitionEnter(value);
        return res;
    }
    onEnter(event: PageTransitionCallback): this {
        ArkUIAniModule._Animation_PageTransitionSetOnEnter(event);
        return this;
    }
    slide(value: SlideEffect): this {
        ArkUIAniModule._Animation_PageTransitionSetSlide(value);
        return this;
    }
    translate(value: TranslateOptions): this {
        ArkUIAniModule._Animation_PageTransitionSetTranslate(value);
        return this;
    }
    scale(value: ScaleOptions): this {
        ArkUIAniModule._Animation_PageTransitionSetScale(value);
        return this;
    }
    opacity(value: number): this {
        ArkUIAniModule._Animation_PageTransitionSetOpacity(value);
        return this;
    }
}
 
export class PageTransitionExit extends CommonTransition {
    static $_invoke(value: PageTransitionOptions): PageTransitionExit {
        let res = new PageTransitionExit();
        ArkUIAniModule._Animation_CreatePageTransitionExit(value);
        return res;
    }
    onExit(event: PageTransitionCallback): this {
        ArkUIAniModule._Animation_PageTransitionSetOnExit(event);
        return this;
    }
    slide(value: SlideEffect): this {
        ArkUIAniModule._Animation_PageTransitionSetSlide(value);
        return this;
    }
    translate(value: TranslateOptions): this {
        ArkUIAniModule._Animation_PageTransitionSetTranslate(value);
        return this;
    }
    scale(value: ScaleOptions): this {
        ArkUIAniModule._Animation_PageTransitionSetScale(value);
        return this;
    }
    opacity(value: number): this {
        ArkUIAniModule._Animation_PageTransitionSetOpacity(value);
        return this;
    }
}
