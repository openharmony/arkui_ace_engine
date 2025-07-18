import { CommonMethod, ArkCommonMethodSet, ArkCommonMethodComponent, StateStyles } from "../generated"

interface MockState {
    value: number
}

export type CustomStyles = (instance:CommonMethod) => void

export function applyStyles<T extends CommonMethod>(this: T, customStyles: CustomStyles): T {
    customStyles(this);
    return this;
}

export function hookStateStyleImpl(node: ArkCommonMethodComponent, stateStyle: StateStyles | undefined): void {
    const currentState = node.getPeer()?.getOrCreateStateStyleMutable()
    if (currentState === undefined) {
        return;
    }
    const UI_STATE_NORMAL = 0;
    const UI_STATE_PRESSED = 1;
    const UI_STATE_FOCUSED = 1 << 1;
    const UI_STATE_DISABLED = 1 << 2;
    const UI_STATE_SELECTED = 1 << 3;

    let cm = new ArkCommonMethodSet();

    if (currentState.value === UI_STATE_NORMAL) {
        stateStyle?.normal?.(cm)
    }
    if (currentState.value & UI_STATE_PRESSED) {
        stateStyle?.clicked?.(cm)
        stateStyle?.pressed?.(cm)
    }
    if (currentState.value & UI_STATE_FOCUSED) {
        stateStyle?.focused?.(cm)
    }
    if (currentState.value & UI_STATE_DISABLED) {
        stateStyle?.disabled?.(cm)
    }
    if (currentState.value & UI_STATE_SELECTED) {
        stateStyle?.selected?.(cm)
    }
    cm.applyModifierPatch(node)
}
