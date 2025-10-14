// this file will be merged with component/xxx.ets by compiler pre-process script

import { WrappedBuilder, CustomBuilderT } from "./builder"

export interface AttributeModifier<T> {
    applyNormalAttribute(instance: T): void {}
    applyPressedAttribute(instance: T): void {}
    applyFocusedAttribute(instance: T): void {}
    applyDisabledAttribute(instance: T): void {}
    applySelectedAttribute(instance: T): void {}
}

export interface AnimatableArithmetic<T> {
    plus(rhs:AnimatableArithmetic<T>): AnimatableArithmetic<T>;
    subtract(rhs:AnimatableArithmetic<T>): AnimatableArithmetic<T>;
    multiply(scale:number): AnimatableArithmetic<T>;
    equals(rhs:AnimatableArithmetic<T>): boolean;
}

export interface ContentModifier<T = void> {
  applyContent(): WrappedBuilder<CustomBuilderT<T>>
}

export class UIGestureEvent {
}

export type CustomStyles =  (instance: CommonMethod) => void;

export interface GestureModifier {
    applyGesture(event: UIGestureEvent): void
}

export function applyStyles<T extends CommonMethod>(this: T, customStyles: CustomStyles): T {
    customStyles(this);
    return this;
}
