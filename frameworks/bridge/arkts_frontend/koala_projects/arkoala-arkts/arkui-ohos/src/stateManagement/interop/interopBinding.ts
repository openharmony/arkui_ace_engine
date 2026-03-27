import { MutableBinding, Binding } from '../utils';
import { MutableState } from '@koalaui/runtime';
import { int32 } from '@koalaui/common';

export class InteropTransferMutableBinding<T> extends MutableBinding<T> {
    private dynamicBinding: ESValue;
    private interopState: MutableState<int32> | undefined = undefined;

    constructor(dynamicBinding: ESValue) {
        super(
            () => {
                throw new Error('getter is not implemented');
            },
            (newValue: T) => {
                throw new Error('setter is not implemented');
            }
        );
        this.dynamicBinding = dynamicBinding;
    }

    get value(): T {
        if (this.interopState !== undefined) {
            this.interopState!.value;
        }
        return this.dynamicBinding.getProperty('value').unwrap() as T;
    }

    set value(newValue: T) {
        this.dynamicBinding.setProperty('value', ESValue.wrap(newValue));
    }

    interopAddState(state: MutableState<int32>): void {
        this.interopState = state;
    }
}

export class InteropTransferBinding<T> extends Binding<T> {
    private dynamicBinding: ESValue;
    private interopState: MutableState<int32> | undefined = undefined;

    constructor(dynamicBinding: ESValue) {
        super(() => {
            throw new Error('getter is not implemented');
        });
        this.dynamicBinding = dynamicBinding;
    }

    get value(): T {
        if (this.interopState !== undefined) {
            this.interopState!.value;
        }
        return this.dynamicBinding.getProperty('value').unwrap() as T;
    }

    interopAddState(state: MutableState<int32>): void {
        this.interopState = state;
    }
}
