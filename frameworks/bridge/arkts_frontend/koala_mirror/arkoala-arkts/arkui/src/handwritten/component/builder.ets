package arkui.component.builder

import { memo } from "@koalaui/runtime/annotations"

export class WrappedBuilder<T> {
    @memo builder: T;
    constructor(t: T) {
        this.builder = t;
    }
}

export function wrapBuilder<T>(builder: T): WrappedBuilder<T> {
    return new WrappedBuilder<T>(builder);
}